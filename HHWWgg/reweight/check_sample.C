











TH1D* get_hist( TTree * t, string wname,  int MAX_EVENTS=99999999){

  cout << "Entries = " << t->GetEntries() << endl;

  Float_t genMhh                ;
  Float_t genAbsCosThetaStar_CS ;
  t->SetBranchAddress("genMhh",                &genMhh );
  t->SetBranchAddress("genAbsCosThetaStar_CS", &genAbsCosThetaStar_CS );
  TTreeFormula * tform = new TTreeFormula(wname.c_str(), wname.c_str(), t);
  
  TH1D * h = new TH1D(wname.c_str(), wname.c_str(), 50, 250, 1500);
  for(int i = 0, N = min((int)t->GetEntries(), (int)MAX_EVENTS); i < N; i++){
    t->GetEntry(i);
    h->Fill( genMhh, tform->EvalInstance() );
  }
  return h;
}

TTree * FindInDir(TDirectory *source,  string tag="HHWWggTag_0") {

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
         TTree * answer = FindInDir(subdir, tag);
         if( answer ) return answer;
      } else if (cl->InheritsFrom(TTree::Class())) {
         if( string(key->GetName()).find( tag ) == string::npos ) continue;
         cout << "find " << key->GetName() << endl;
         TTree *T = (TTree*)source->Get(key->GetName());
         return T;
      }
  }
  return nullptr;
}

void check_sample(string fname){

  std::string token = fname.substr( fname.find("node_") + string("node_").size(), fname.size() );
  token = token.substr( 0,  token.find("_"));
  cout << "bmark = " << token << endl;

  string year = "2016" ;
  if( fname.find("2016") != std::string::npos ) year="2016" ;
  if( fname.find("2017") != std::string::npos ) year="2017" ;
  if( fname.find("2018") != std::string::npos ) year="2018" ;
  
  string mode="SL";
  if( fname.find("2G2Qlnu") != std::string::npos ) mode="SL" ;
  if( fname.find("2G4Q")    != std::string::npos ) mode="FH" ;
  if( fname.find("2G2l2nu") != std::string::npos ) mode="FL" ;

  TTree * tree;
  TFile * inpf = TFile::Open( fname.c_str() );
  if( mode == "SL" ) tree = FindInDir( inpf,  "HHWWggTag_0" );
  if( mode == "FH" ) tree = FindInDir( inpf,  "HHWWggTag_1" );
  if( mode == "FL" ) tree = FindInDir( inpf,  "HHWWggTag_2" );

  vector<string> bms = {"SM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "cHHH0", "cHHH2", "cHHH5", "8a", "1b", "2b", "3b", "4b", "5b", "6b", "7b"};
  TH1D* hist_nom     = get_hist(tree, "1", 99999999);
  hist_nom->SetLineColor(2);
  hist_nom->SetLineWidth(2);

  for(string bm : bms){
    string wname = "weight_NLO_" + bm;

    TCanvas * canv = new TCanvas("", "", 640, 480);
    hist_nom->Draw("hist");

    TH1D* hist = get_hist(tree, wname, 99999999);
    hist->Draw("hist same");
    hist->SetTitle( (wname).c_str() );
    hist->SetLineWidth(2);

    canv->BuildLegend();
    canv->Print( ("SC_out/" + token + "_" + year + "_" + mode + "_" + bm + ".png").c_str() );
  }
}

