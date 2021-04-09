
#include "reweight_HH.C"

class CMSReweighter{
  public:
  ReweightMandrik *rm_mg, *rm_pw ;
  vector<string>   bms;
  vector<double> xsec_pw, xsec_mg, xsec_nlo_pw;
  vector< vector<double> > couplings_pw;
  
  double xsec_start;
  vector<double> couplings_start;
  bool start_bm_madgraph, start_nlo;

  CMSReweighter(string year){
    bms = {"SM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "cHHH0", "cHHH2", "cHHH5", "8a", "1b", "2b", "3b", "4b", "5b", "6b", "7b"};
    rm_mg = new ReweightMandrik("", "pm_mg_LO-Ais-13TeV_V2.txt");
    rm_pw = new ReweightMandrik("", "pm_pw_LO-Ais-13TeV_V2.txt", "pm_pw_NLO_Ais_13TeV_V2.txt");
    
   for(int i = 0; i < bms.size(); i++){
    string bm = bms.at( i );
    xsec_pw.push_back( get_eft_xsec_13TeV(bm, "lo", year, false) );   
    xsec_mg.push_back( get_eft_xsec_13TeV(bm, "lo_MadGraph", year, false) );   
    xsec_nlo_pw.push_back( get_eft_xsec_13TeV(bm, "nlo", year, false) );
    couplings_pw.push_back( rm_pw->GetEFTBenchmark(bm, year, false) );
   }
  }
  
  void InitStartPoint(int start_eft_bm_id, bool is_it_madgraph=true, bool is_it_nlo_powheg=false, bool is_it_cms_fake=true, string year="2017", bool if_year_is_2016_are_the_old_version_of_gridpacks_is_used=false){
    string bm = bms.at( start_eft_bm_id );
    if(if_year_is_2016_are_the_old_version_of_gridpacks_is_used) year = "2017"; // switch to the old one
    
    if(is_it_madgraph){
      start_bm_madgraph = true;
      xsec_start = get_eft_xsec_13TeV( bm , "lo_MadGraph" , year, is_it_cms_fake );
      couplings_start = rm_mg->GetEFTBenchmark(bm, year, is_it_cms_fake) ;
      cout << "CMSReweighter(): start from MadGraph " << bm << " " << year << " " << xsec_start << "pb" << endl;
      for(int i = 0; i < couplings_start.size(); i++) cout << couplings_start[i] << " ";
      cout << endl; 
      return;
    }
    
    start_bm_madgraph = false;
    start_nlo = is_it_nlo_powheg;
    
    xsec_start = get_eft_xsec_13TeV( bm , "lo" , "2017", false );
    if( is_it_nlo_powheg ) xsec_start = get_eft_xsec_13TeV( bm , "nlo" , "2017", false );
    couplings_start = rm_pw->GetEFTBenchmark(bm, "2017", false) ;
    cout << "CMSReweighter(): start from Powheg " << bm << " " << year << " " << xsec_start << "pb" << endl;
    for(int i = 0; i < couplings_start.size(); i++) cout << couplings_start[i] << " ";
    cout << endl; 
  }

  double GetWeight(double genMhh, double genAbsCosThetaStar_CS, int end_bm, bool is_powheg=true, string mode="nlo"){
    if( genMhh > 4999 ) genMhh = 4999;
    
    double dXsec_start;
    if( start_bm_madgraph ){
      dXsec_start = rm_mg->GetDiffXsection( genMhh, genAbsCosThetaStar_CS, couplings_start, "lo"  );
    } else {
      if(not start_nlo) dXsec_start = rm_pw->GetDiffXsection( genMhh, genAbsCosThetaStar_CS, couplings_start, "lo"  );
      else              dXsec_start = rm_pw->GetDiffXsection( genMhh, genAbsCosThetaStar_CS, couplings_start, "nlo"  );
    }

    if( dXsec_start <= 0 ) return 0;
    double dXsec_end = 0, xsec_end  = 0;
    auto couplings_end = couplings_pw.at( end_bm );
    if(is_powheg){
      dXsec_end    = rm_pw->GetDiffXsection( genMhh, genAbsCosThetaStar_CS, couplings_end, mode );
      if( mode == "nlo" ) xsec_end = xsec_nlo_pw.at( end_bm );
      else                xsec_end = xsec_pw.at( end_bm );
    }
    
    return (dXsec_end / xsec_end) / (dXsec_start  / xsec_start) ;
  }
};

CMSReweighter * reweighter;
int MAX_EVENTS = 999999999;

TTree * CloneReweightTTree( TTree * T ){
  TTree *newT =  T->CloneTree(-1, "fast");

  Float_t genMhh                ;
  Float_t genAbsCosThetaStar_CS ;
  newT->SetBranchAddress("genMhh",                &genMhh );
  newT->SetBranchAddress("genAbsCosThetaStar_CS", &genAbsCosThetaStar_CS );

  vector<TBranch*> branches_nlo, branches_lo, branches_lo_mg;
  vector<Float_t*> weight_values_NLO;
  vector<Float_t*> weight_values_LO;
  for(auto bm : reweighter->bms){
    weight_values_NLO.push_back( new Float_t() );
    string wname = "weight_NLO_" + bm;
    branches_nlo.push_back( newT->Branch(wname.c_str(), weight_values_NLO[ weight_values_NLO.size()-1 ] ) ); 

    weight_values_LO.push_back( new Float_t() );
    wname = "weight_LO_" + bm;
    branches_lo.push_back( newT->Branch(wname.c_str(), weight_values_LO[ weight_values_LO.size()-1 ] ) ); 
  }

  for(int i = 0, N = newT->GetEntries(); i < N; i++){
    newT->GetEntry(i);
    if(i > MAX_EVENTS) break;
    
    for(int j = 0; j < reweighter->bms.size(); j++){
      (*(weight_values_NLO[j])) = reweighter->GetWeight(genMhh, genAbsCosThetaStar_CS, j, true, "nlo");
      branches_nlo[j]->Fill();
      
      (*(weight_values_LO[j]))  = reweighter->GetWeight(genMhh, genAbsCosThetaStar_CS, j, true, "lo");
      branches_lo[j]->Fill();
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

/*
TH1D* GetMhhPlot(TFile * t1, string name, string wname, strin tree_name){
  TTree* T = (TTree*) t1->Get( tree_name.c_str() );
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

void CheckReweighting(string oname, string input_1, string tname_1, string wname_1, string input_2, string tname_2,  string wname_2, string tree_name){
  TFile * f1 = TFile::Open(input_1.c_str());
  TH1D * h0 = GetMhhPlot( f1 , tname_1, "1" );
  TH1D * h1 = GetMhhPlot( f1 , tname_1, wname_1 );

  TFile * f2 = TFile::Open(input_2.c_str());
  TH1D * h2 = GetMhhPlot( f2 , tname_2, wname_2, tree_name );

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
*/

// "SM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "cHHH0", "cHHH0", "cHHH2", "cHHH5"
void reweight_samples(string input="", string output="", string bm_id_name="SM"){
  string year = "2016" ;
  if( input.find("2016") != std::string::npos ) year="2016" ;
  if( input.find("2017") != std::string::npos ) year="2017" ;
  if( input.find("2018") != std::string::npos ) year="2018" ;
  
  string mode="SL";
  if( input.find("2G2Qlnu") != std::string::npos ) mode="SL" ;
  if( input.find("2G4Q")    != std::string::npos ) mode="FH" ;
  if( input.find("2G2l2nu") != std::string::npos ) mode="FL" ;

  if( bm_id_name == "cHHH2p45") bm_id_name = "cHHH2";
  bool mc_powheg = false, mc_nlo = false, cms_fake = true;
  if( bm_id_name == "cHHH2" or bm_id_name == "cHHH0" or bm_id_name == "cHHH5" or bm_id_name == "cHHH1") { 
    mc_powheg = true; mc_nlo = true; cms_fake = false; 
  };
  if( bm_id_name == "cHHH1" ) bm_id_name = "SM";

  cout << mode << " " << bm_id_name << " ... " << endl;
  
  reweighter = new CMSReweighter( year );
  cout << "!!!" << bm_id_name << endl;
  auto it = std::find(reweighter->bms.begin(), reweighter->bms.end(), bm_id_name);
  int start_eft_bm_id = std::distance(reweighter->bms.begin(), it);
  // InitStartPoint(int start_eft_bm_id, bool is_it_madgraph=true, bool is_it_nlo_powheg=false, bool is_it_cms_fake=true, string year="2017", bool if_year_is_2016_are_the_old_version_of_gridpacks_is_used=false)
  reweighter->InitStartPoint(start_eft_bm_id, not mc_powheg, mc_nlo, cms_fake, year, false);

  TFile * inpf = TFile::Open(input.c_str());
  TFile * oupf = TFile::Open(output.c_str(), "RECREATE");

  oupf->cd();
  if( mode == "SL" ) CopyDir( inpf, oupf, "HHWWggTag_0" );
  if( mode == "FH" ) CopyDir( inpf, oupf, "HHWWggTag_1" );
  if( mode == "FL" ) CopyDir( inpf, oupf, "HHWWggTag_2" );
}



