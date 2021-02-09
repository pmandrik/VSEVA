
#include "reweight_HH.C"

class CMSReweighter{
  public:
  ReweightGudrun  *rg   ;
  ReweightMandrik *rm   ;
  vector<string>   bms;
  vector<double> xsec_mg, xsec_pw;
  vector< vector<double> > couplings_mg, couplings_pw;
  int start_bm;
  double xsec_dataset;

  CMSReweighter(string year){
    bms = {"SM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "cHHH0", "cHHH2", "cHHH5"};
    rm   = new ReweightMandrik("pm_mg_LO-Ais-13TeV.txt");
    rg   = new ReweightGudrun();

    for(int i = 0; i < bms.size(); i++){
      string bm = bms.at(i);
      xsec_mg.push_back( get_eft_xsec_13TeV(bm, "lo_MadGraph" , year, true  ) );
      couplings_mg.push_back( rm->GetEFTBenchmark(bm, year, true) );

      xsec_pw.push_back( get_eft_xsec_13TeV(bm, "nlo", year, false)  );
      couplings_pw.push_back( rg->GetEFTBenchmark(bm, year, false) );
    }
  }

  double GetWeight(double genMhh, double genAbsCosThetaStar_CS, int end_bm){
    if( genMhh > 4999 ) genMhh = 4999;
    double xsec_start = xsec_mg.at( start_bm );
    vector<double> c1 = couplings_mg.at( start_bm );
    double dXsec_start   = rm->GetDiffXsection( genMhh, genAbsCosThetaStar_CS, c1, "lo"  );

    if( dXsec_start <= 0 ) return 0;

    if( genMhh > 1039 ) genMhh = 1039;
    double xsec_end   = xsec_pw.at( end_bm );
    vector<double> c2 = couplings_pw.at( end_bm );
    double dXsec_end     = rg->GetDiffXsection( genMhh, c2, "nlo"  );

    // cout << genMhh << " " << genAbsCosThetaStar_CS << endl;
    // cout << xsec_start << " " << xsec_end << " " << dXsec_end / xsec_end << " " << dXsec_start/xsec_start << endl;
    // cout << (dXsec_end / xsec_end) / (dXsec_start  / xsec_start) << endl;

    return (dXsec_end / xsec_end) / (dXsec_start  / xsec_start) ;
  }
};

CMSReweighter * reweighter;
int MAX_EVENTS = 99999999;

TTree * CloneReweightTTree( TTree * T ){
  TTree *newT =  T->CloneTree(-1, "fast");

  Float_t genMhh                ;
  Float_t genAbsCosThetaStar_CS ;
  newT->SetBranchAddress("genMhh",                &genMhh );
  newT->SetBranchAddress("genAbsCosThetaStar_CS", &genAbsCosThetaStar_CS );

  vector<TBranch*> branches;
  vector<Float_t*> weight_values;
  for(auto bm : reweighter->bms){
    weight_values.push_back( new Float_t() );
    string wname = "weight_NLO_" + bm;
    branches.push_back( newT->Branch(wname.c_str(), weight_values[ weight_values.size()-1 ] ) ); 
  }

  for(int i = 0, N = newT->GetEntries(); i < N; i++){
    newT->GetEntry(i);
    if(i > MAX_EVENTS) break;
    
    for(int j = 0; j < branches.size(); j++){
      // if(j != 15) continue; 
      (*(weight_values[j])) = reweighter->GetWeight(genMhh, genAbsCosThetaStar_CS, j);
      branches[j]->Fill();
    }
  }
  cout << newT->GetEntries() << endl;

  return newT;
}

void CopyDir(TDirectory *source, TDirectory *savdir, string tag="HHWWggTag_0") {
   //copy all objects and subdirs of directory source as a subdir of the current directory   
   //source->ls();
   TDirectory *adir = savdir;
   adir->cd();
   //loop on all entries of this directory
   TKey *key;
   TIter nextkey(source->GetListOfKeys());
   while ((key = (TKey*)nextkey())) {
      // cout << "!" << key->GetName() << " " << key->GetClassName() << endl;
      const char *classname = key->GetClassName();
      TClass *cl = gROOT->GetClass(classname);
      if (!cl) continue;
      if (cl->InheritsFrom(TDirectory::Class())) {
         cout << "check dir " << key->GetName() << endl;
         source->cd(key->GetName());
         TDirectory *subdir = gDirectory;
         TDirectory * new_adir = adir->mkdir( key->GetName() );
         new_adir->cd();
         CopyDir(subdir, new_adir, tag);
         adir->cd();
      } else if (cl->InheritsFrom(TTree::Class())) {
         if( string(key->GetName()).find( tag ) == string::npos ) continue;
         // if( string(key->GetName()).find("sigma") != string::npos ) continue;
         cout << "reweight " << key->GetName() << endl;
         TTree *T = (TTree*)source->Get(key->GetName());
         adir->cd();
         TTree *newT = CloneReweightTTree( T );
         newT->Write();
      } else {
         source->cd();
         TObject *obj = key->ReadObj();
         adir->cd();
         obj->Write();
         delete obj;
     }
  }
  adir->SaveSelf(kTRUE);
  savdir->cd();
}

TH1D* GetMhhPlot(TFile * t1, string name, string wname){
  TTree* T = (TTree*) t1->Get( ("tagsDumper/trees/GluGluToHHTo2G2Qlnu_node_" + name + "_13TeV_HHWWggTag_0").c_str() );
  cout << name << " " << wname << " " << T << endl;
  cout << "Entries = " << T->GetEntries() << endl;

  Float_t genMhh                ;
  Float_t genAbsCosThetaStar_CS ;
  T->SetBranchAddress("genMhh",                &genMhh );
  T->SetBranchAddress("genAbsCosThetaStar_CS", &genAbsCosThetaStar_CS );
  TTreeFormula * tform = new TTreeFormula(wname.c_str(), wname.c_str(), T);

  TH1D * h = new TH1D("", "", 50, 250, 1500);
  cout << "Entries = " << T->GetEntries() << endl;
  for(int i = 0, N = T->GetEntries(); i < N; i++){
    if(i > MAX_EVENTS) break;
    T->GetEntry(i);
    h->Fill( genMhh, tform->EvalInstance() );
  }
  h->Scale( 1./h->Integral() );
  return h;
}

void CheckReweighting(string oname, string input_1, string tname_1, string wname_1, string input_2, string tname_2,  string wname_2){
  TFile * f1 = TFile::Open(input_1.c_str());
  TH1D * h0 = GetMhhPlot( f1 , tname_1, "1" );
  TH1D * h1 = GetMhhPlot( f1 , tname_1, wname_1 );

  TFile * f2 = TFile::Open(input_2.c_str());
  TH1D * h2 = GetMhhPlot( f2 , tname_2, wname_2 );

  TCanvas * canv = new TCanvas("", "", 640, 480);
  h1->Draw("hist");
  h2->Draw("hist same");
  h0->Draw("hist same");
  h2->SetLineWidth(2);

  h1->GetXaxis()->SetTitle("m_{HH} [GeV]");
  h2->SetLineColor(2);
  h2->SetLineWidth(2);

  h0->SetLineColor(3);
  h0->SetLineWidth(2);

  h0->SetTitle( ("MadGraph MC " + tname_1     ).c_str() );
  h1->SetTitle( ("Reweighted to "   + tname_2 ).c_str() );
  h2->SetTitle( ("Powheg MC " + tname_2       ).c_str() );

  canv->BuildLegend();

  canv->Print( (oname).c_str() );
}

// "SM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "cHHH0", "cHHH0", "cHHH2", "cHHH5"
void reweight_samples(string mode="SL", string input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_LO_2017_noPdfWeight_hadded/GluGluToHHTo2G2Qlnu_node_SM_2017.root", string output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production/2017/Signal/SL_LO_2017_noPdfWeight_hadded/GluGluToHHTo2G2Qlnu_node_SM_2017.root", string bm_id_name="SM", string year="2017",
  string ch1="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_NLO_2017_hadded/GluGluToHHTo2G2Qlnu_node_cHHH1_2017.root", string ch0="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_NLO_2017_hadded/GluGluToHHTo2G2Qlnu_node_cHHH0_2017.root", string ch2="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_NLO_2017_hadded/GluGluToHHTo2G2Qlnu_node_cHHH2p45_2017.root", string ch5="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_NLO_2017_hadded/GluGluToHHTo2G2Qlnu_node_cHHH5_2017.root"){

  reweighter = new CMSReweighter( year );
  auto it = std::find(reweighter->bms.begin(), reweighter->bms.end(), bm_id_name);
  reweighter->start_bm = std::distance(reweighter->bms.begin(), it);
  reweighter->xsec_dataset = 0.01;

  TFile * inpf = TFile::Open(input.c_str());
  TFile * oupf = TFile::Open(output.c_str(), "RECREATE");

  oupf->cd();
  if( mode == "SL" ) CopyDir( inpf, oupf, "HHWWggTag_0" );
  if( mode == "FH" ) CopyDir( inpf, oupf, "HHWWggTag_1" );
  if( mode == "FL" ) CopyDir( inpf, oupf, "HHWWggTag_2" );

  string out_node = bm_id_name;

  CheckReweighting(mode + "EFT"+out_node + "_vs_cHHH1_check_" + year + ".png",
                   output, out_node, "weight_NLO_SM", 
                   ch1, "cHHH1", "1" 
  );
  CheckReweighting(mode + "EFT"+out_node + "_vs_cHHH0_check_" + year + ".png", 
                   output, out_node, "weight_NLO_cHHH0", 
                   ch0, "cHHH0", "1" 
  );
  CheckReweighting(mode + "EFT"+out_node + "_vs_cHHH2_check_" + year + ".png", 
                   output, out_node, "weight_NLO_cHHH2", 
                   ch2, "cHHH2p45", "1" 
  );
  CheckReweighting(mode + "EFT"+out_node + "_vs_cHHH5_check_" + year + ".png", 
                   output, out_node, "weight_NLO_cHHH5", 
                   ch5, "cHHH5", "1" 
  );
}





