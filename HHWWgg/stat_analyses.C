
//=========================================================================================================================== EXTERNAL
TRandom3 *RandomGen = new TRandom3();

map<string,RooRealVar*> params;
map<string,RooFormulaVar*> prods;
map<string,RooAbsPdf*> utilities;

RooAbsPdf* getExponentialSingle(RooRealVar *obs_var, string prefix, int order){

  if (order%2==0){
    cerr << "ERROR -- addExponential -- only odd number of params allowed" << endl;
    return NULL;
  }
  int nfracs=(order-1)/2;
  int nexps=order-nfracs;
  assert(nfracs==nexps-1);
  RooArgList *fracs = new RooArgList();
  RooArgList *exps = new RooArgList();
  for (int i=1; i<=nfracs; i++){
    string name =  Form("%s_f%d",prefix.c_str(),i);
    params.insert(pair<string,RooRealVar*>(name, new RooRealVar(name.c_str(),name.c_str(),0.9-float(i-1)*1./nfracs,0.0001,0.9999)));
    fracs->add(*params[name]);
  }
  for (int i=1; i<=nexps; i++){
    string name =  Form("%s_p%d",prefix.c_str(),i);
    string ename =  Form("%s_e%d",prefix.c_str(),i);
    params.insert(pair<string,RooRealVar*>(name, new RooRealVar(name.c_str(),name.c_str(),TMath::Max(-1.,-0.04*(i+1)),-1.,0.)));
    utilities.insert(pair<string,RooAbsPdf*>(ename, new RooExponential(ename.c_str(),ename.c_str(),*obs_var,*params[name])));
    exps->add(*utilities[ename]);
  }
  RooAbsPdf *exp = new RooAddPdf(prefix.c_str(),prefix.c_str(),*exps,*fracs,true);
  exp->Print("v");
  cout << "--------------------------" << endl;
  return exp;
}

RooAbsPdf* getPowerLawSingle(RooRealVar *obs_var, string prefix, int order){
  if (order%2==0){
    cerr << "ERROR -- addPowerLaw -- only odd number of params allowed" << endl;
    return NULL;
  }
  int nfracs=(order-1)/2;
  int npows=order-nfracs;
  assert(nfracs==npows-1);
  RooArgList *fracs = new RooArgList();
  RooArgList *pows = new RooArgList();
  for (int i=1; i<=nfracs; i++){
    string name =  Form("%s_f%d",prefix.c_str(),i);
    params.insert(pair<string,RooRealVar*>(name, new RooRealVar(name.c_str(),name.c_str(),0.9-float(i-1)*1./nfracs,0.,1.)));
    fracs->add(*params[name]);
  }
  for (int i=1; i<=npows; i++){
    string name =  Form("%s_p%d",prefix.c_str(),i);
    string ename =  Form("%s_e%d",prefix.c_str(),i);
    params.insert(pair<string,RooRealVar*>(name, new RooRealVar(name.c_str(),name.c_str(),TMath::Max(-9.,-1.*(i+1)),-9.,1.)));
    utilities.insert(pair<string,RooAbsPdf*>(ename, new RooPower(ename.c_str(),ename.c_str(),*obs_var,*params[name])));
    pows->add(*utilities[ename]);
  }
  RooAbsPdf *pow = new RooAddPdf(prefix.c_str(),prefix.c_str(),*pows,*fracs,true); 
  pow->Print("v");
  return pow;
}

RooAbsPdf* getPdf(RooRealVar *obs_var, string type, int order, const char* ext=""){
  
  //if (type=="Bernstein") return pdfsModel.getBernstein(Form("%s_bern%d",ext,order),order); 
  //else if (type=="Chebychev") return pdfsModel.getChebychev(Form("%s_cheb%d",ext,order),order); 
  if (type=="Exponential") return getExponentialSingle(obs_var, Form("%s_exp%d",ext,order),order); 
  else if (type=="PowerLaw") return getPowerLawSingle(obs_var, Form("%s_pow%d",ext,order),order); 
  //else if (type=="Laurent") return pdfsModel.getLaurentSeries(Form("%s_lau%d",ext,order),order); 
  else {
    cerr << "[ERROR] -- getPdf() -- type " << type << " not recognised." << endl;
    return NULL;
  }
}

void plot(RooRealVar *mass, map<string,RooAbsPdf*> pdfs, RooDataSet *data, string name){
  int mgg_low  = 100;
  int mgg_high = 180;
  bool BLIND = true;

  int color[7] = {kBlue,kRed,kMagenta,kGreen+1,kOrange+7,kAzure+10,kBlack};
  TCanvas *canv = new TCanvas();
  TLegend *leg = new TLegend(0.6,0.65,0.88,0.88);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  RooPlot *plot = mass->frame();

  mass->setRange("unblindReg_1",mgg_low,115);
  mass->setRange("unblindReg_2",135,mgg_high);
  if (BLIND) {
    data->plotOn(plot,Binning(mgg_high-mgg_low),CutRange("unblindReg_1"));
    data->plotOn(plot,Binning(mgg_high-mgg_low),CutRange("unblindReg_2"));
    data->plotOn(plot,Binning(mgg_high-mgg_low),Invisible());
  }
  else data->plotOn(plot,Binning(mgg_high-mgg_low));

  TObject *datLeg = plot->getObject(int(plot->numItems()-1));
  leg->AddEntry(datLeg,"Data 2017","LEP");

  int i=0;
  int style=1;
  for (map<string,RooAbsPdf*>::iterator it=pdfs.begin(); it!=pdfs.end(); it++){
    int col;
    if (i<=6) col=color[i];
    else {col=kBlack; style++;}
    it->second->plotOn(plot,LineColor(col),LineStyle(style));//,RooFit::NormRange("fitdata_1,fitdata_2"));
    TObject *pdfLeg = plot->getObject(int(plot->numItems()-1));
    std::string ext = "";
    // if (bestFitPdf==i) ext=" (Best Fit Pdf) ";
    leg->AddEntry(pdfLeg,Form("%s%s",it->first.c_str(),ext.c_str()),"L");
    i++;
  }
  // plot->SetTitle(Form(" %s",flashggCats_[cat].c_str()));
  if (BLIND) plot->SetMinimum(0.0001);
  plot->Draw();
  leg->Draw("same");
  // CMS_lumi( canv, 0, 0);
  canv->SaveAs(Form("%s.pdf",name.c_str()));
  canv->SaveAs(Form("%s.png",name.c_str()));
  delete canv;
}






//=========================================================================================================================== INTERNAL

TH1D * get_MH_hist(TTree * ttree, string name, int NBins, double tot_min, double tot_max, double cut_min, double cut_max, std::string weight_name="" ){
  TH1D * hist = new TH1D(name.c_str(), name.c_str(), NBins, tot_min, tot_max);

  cout << "tree = " << ttree << endl;
  int nevents = ttree->GetEntries();

  Double_t m_yy;
  if( ttree->GetBranch( "m_yy") ){
    ttree->SetBranchAddress( "m_yy", &m_yy);
  } else cout << "DontHave a branch with name = m_yy" << endl;

  Double_t weight = 1;
  if(weight_name.size() ){
    if( ttree->GetBranch( weight_name.c_str() ) ){
      ttree->SetBranchAddress( weight_name.c_str(), &weight);
    } else cout << "DontHave a branch with name = m_yy" << endl;
  }

  for(int i = 0; i < nevents; i++){
    ttree->GetEntry(i);

    if( m_yy > cut_max or m_yy < cut_min) continue;
    hist->Fill( m_yy, weight );
  }

  return hist;
}

struct Process{
  Process(string f, string n, string t, string w){
      file = f;
      name = n;
      ttree = t;  
      weight = w;
    }
  string file, name, ttree, weight;
};

void stat_analyses(){

  std::string input_data_file_name = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_data_v4.root";
  double h_width = 10;
  int nbins_fit = 80/4; // 0 - 115, 135 - 180
  int nbins_stat = nbins_fit; // 20;
  TFile * output_data_file = TFile::Open( "stat_output/hists.root", "RECREATE" );

  /*
    TODO:
      V 1. create bandwidth hist
      - 2. fit it
      - 3. make histogram from it
      - 4. create signal/mc histogramms with uncertanties
      - 5. combaine everythin together in the file
      - 6. create datacard for the fit
      - 7. find CLs limits
  */

  // 1. Create bandwidth hist
  TFile * input_data_file = TFile::Open( input_data_file_name.c_str() );
  TTree * tree = (TTree*) gDirectory->Get( "Def_Events" );
  output_data_file->cd();
  // TH1D* h1_bw = get_MH_hist(tree, "bw1", nbins_fit, 100, 180, 100, 125-h_width);
  // TH1D* h2_bw = get_MH_hist(tree, "bw2", nbins_fit, 100, 180, 125+h_width, 180);
  // h1_bw->Add(h2_bw, 1);
  TH1D* h_bf = get_MH_hist(tree, "bf", nbins_fit, 100, 180, 100, 180);

  // 2. Fit bandwidth hist
  RooWorkspace w("w");
  RooRealVar  mgg_var("m_yy","m_{#gamma#gamma} [GeV]", 100, 180) ;
  RooDataHist mgg_hist("dh","dh", mgg_var, RooFit::Import(*h_bf)) ;
  RooDataSet *mgg_data = new RooDataSet( "data_bg", "data SM bkg", tree, RooArgSet( mgg_var ) );

  mgg_var.setRange("bw1",100, 125-h_width);
  mgg_var.setRange("bw2",125+h_width, 180);

  RooPlot* frame = mgg_var.frame(RooFit::Title("data fit")) ;
  mgg_hist.plotOn(frame, RooFit::Range("bw1,bw2")) ; 

  RooAbsPdf * exp_background_pdf = getPdf(&mgg_var, "Exponential", 1, "");
  // exp_background_pdf->fitTo( mgg_hist, RooFit::Range("bw1,bw2") );
  exp_background_pdf->fitTo( *mgg_data, RooFit::Range("bw1,bw2") );
  exp_background_pdf->plotOn(frame) ; 

  RooAbsPdf * pow_background_pdf = getPdf(&mgg_var, "PowerLaw", 1, "");
  // pow_background_pdf->fitTo( mgg_hist, RooFit::Range("bw1,bw2") );
  pow_background_pdf->fitTo( *mgg_data, RooFit::Range("bw1,bw2") );
  pow_background_pdf->plotOn(frame, RooFit::LineColor(kGreen) ) ; 
  
  // 3. Make histogram after bandwidth fit
  int ndata = h_bf->GetEntries();
  int nToyEvents = ndata; // RandomGen->Poisson(ndata);
  mgg_var.setBins( nbins_stat );
  cout << "data N events = " << nToyEvents << endl;
  // RooDataSet * genData     = pow_background_pdf->generateBinned( RooArgSet(mgg_var), 0, 1, 1);
  // RooDataHist* genDataHist = genData->binnedClone() ;
  RooDataHist* genDataHist = pow_background_pdf->generateBinned( RooArgSet(mgg_var), nToyEvents, true, false);
  genDataHist->plotOn(frame, RooFit::LineColor(kRed), RooFit::MarkerColor(kRed) ) ; 

  TCanvas* c = new TCanvas("data fit", "data fit", 800, 800) ;
  frame->Draw();
  c->Print("stat_output/data_fit.png");

  map<string,RooAbsPdf*> pdfs;
  pdfs["Exponential 1"] = exp_background_pdf;
  pdfs["PowerLaw 1"] = pow_background_pdf;
  plot(&mgg_var, pdfs, mgg_data, "");

  // 4. Create signal/mc histogramms with uncertanties
  std::string path = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/";
  vector<Process> processes = {
      Process(path+"hzura_2017_EFT2_v4.root", "EFT2",  "Def_Events", "weight" ),
      Process(path+"hzura_2017_EFT9_v4.root", "EFT10", "Def_Events", "weight" ),
    };
  for(int i = 0; i < processes.size(); i++){
    Process process = processes.at( i );
    string file  = process.file;
    string pname = process.name;
    string ttree = process.ttree;
    string weight_name = process.weight;

    TFile * input_data_file = TFile::Open( file.c_str() );
    TTree * tree            = (TTree*) gDirectory->Get( ttree.c_str() );
    output_data_file->cd();
    TH1D  * h               = get_MH_hist(tree, pname, nbins_stat, 100, 180, -999, 999, weight_name);
  }

  // 5. combaine everythin together in the file
  output_data_file->Write();
  output_data_file->Close();
}















