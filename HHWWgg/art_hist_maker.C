
#include "../vseva.hh"
#include "analyse_cfg.C"

using namespace vseva;

vector<TH1D*> fill_hists( string fname, TTree * tree, vector<PlotVariable> * variables, string weight_expression ){
  vector<TH1D*> hists;
  for(int i = 0; i < variables->size(); i++){
    variables->at(i).value_f  = new TTreeFormula(variables->at(i).expression.c_str(), variables->at(i).expression.c_str(), tree);
    hists.push_back( new TH1D( (fname + "_" + variables->at(i).expression).c_str(), variables->at(i).label.c_str(), variables->at(i).nbins, variables->at(i).min, variables->at(i).max ) );
  }
  TTreeFormula weight_f(weight_expression.c_str(), weight_expression.c_str(), tree);

  // tree->Print();
  for(int i = 0; i < tree->GetEntries(); i++){
    tree->GetEntry(i); 
    for(int i = 0; i < variables->size(); i++){
      hists.at(i)->Fill( variables->at(i).value_f->EvalInstance(), weight_f.EvalInstance() );
      if( fname == "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/dy.root" ) cout << weight_f.EvalInstance() << endl;
    }
  }

  return hists;
}

struct dataset {
  dataset(string f, string we, string ln, string t, string tn=""){
    fname = f;
    weight_expression = we;
    latex_name = ln;
    type = t;
    tree_name = tn;
  }

  string fname, type;
  string weight_expression;
  string latex_name, tree_name;
};

void process_datasets(vector<dataset> datasets, vector<PlotVariable> variables, string postfix=""){
  vector<vector<TH1D*>> all_hists;
  for(auto dataset : datasets){
    string fname     = dataset.fname;
    string tree_name = "Def_Events";
    TFile * file = TFile::Open(fname.c_str(), "READ");
    TTree * tree = (TTree*) gDirectory->Get( tree_name.c_str() );

    string bdt_cut = "";

    cout << "Process " << fname << " " << dataset.weight_expression << endl;
    vector<TH1D*> hists = fill_hists( fname, tree, &variables, dataset.weight_expression + bdt_cut );
    for(auto hist : hists) hist->SetTitle( dataset.latex_name.c_str() );
    all_hists.push_back( hists );
  }
  

  for(int i = 0; i < variables.size(); i++){
    HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
    for(int j = 0; j < datasets.size(); j++){
      drawer->AddProcess( all_hists.at(j).at(i) , datasets.at(j).type, datasets.at(j).latex_name );
    }
    draw_hists_CMS( drawer, "output_test/", postfix + to_string(i) + ".pdf", variables.at(i).label, "", "tmva" );
  }
}

#include "/afs/cern.ch/user/p/pmandrik/public/PMANDRIK_LIBRARY/pmlib_root_hist_drawer.hh"
void make_correlation_plot(vector<dataset> datasets, vector<PlotVariable> variables, string type, string postfix){
  vector<CorrParameter*> parameters;

  for(auto var : variables){
    parameters.push_back( new CorrParameter( var.label ) );
  }

  for(auto dataset : datasets){
    if(dataset.type != type) continue;

    string fname     = dataset.fname;
    string tree_name = "Def_Events";
    string weight_expression = dataset.weight_expression;
    TFile * file = TFile::Open(fname.c_str(), "READ");
    TTree * tree = (TTree*) gDirectory->Get( tree_name.c_str() );

    cout << "Process " << fname << " " << dataset.weight_expression << endl;
    for(int i = 0; i < variables.size(); i++)
      variables.at(i).value_f  = new TTreeFormula(variables.at(i).expression.c_str(), variables.at(i).expression.c_str(), tree);
    TTreeFormula weight_f(weight_expression.c_str(), weight_expression.c_str(), tree);

    for(int i = 0; i < tree->GetEntries(); i++){
      tree->GetEntry(i); 
      for(int i = 0; i < variables.size(); i++){
       parameters.at(i)->AddEvent( variables.at(i).value_f->EvalInstance(), weight_f.EvalInstance() );
      }
    }
  }

  TH2D * hist_cor = new TH2D("Correlation", "", parameters.size(), 0, parameters.size(), parameters.size(), 0, parameters.size());
  for(int i=1; i <= hist_cor->GetNbinsX(); i++) hist_cor->GetXaxis()->SetBinLabel(i, parameters.at(i-1)->name.c_str() );
  for(int i=1; i <= hist_cor->GetNbinsX(); i++) hist_cor->GetYaxis()->SetBinLabel(i, parameters.at(i-1)->name.c_str() );
  for(int x = 0; x < parameters.size(); x++){
    for(int y = 0; y < parameters.size(); y++){
      double variance = parameters.at(y)->GetCorrelation( parameters.at(x) );
      // cout << x << " " << y << " " << variance << " " << round(variance*100) << endl;
      hist_cor->Fill(x, y, round(variance*100) );
    }
  }

  TCanvas * canv = get_canvas(640, 640);
    canv->SetLeftMargin(0.25);
    canv->SetRightMargin(0.15);
    canv->SetTopMargin(0.05);
    canv->SetBottomMargin(0.25);

    hist_cor->Draw("COLZ");
    hist_cor->SetStats(0);
    hist_cor->GetXaxis()->LabelsOption("v");

    if(true){
      TH2D* hist_copy = new TH2D(*hist_cor);
      hist_copy->Draw("TEXT SAME");
      hist_copy->SetMarkerColor(kBlack);
      hist_copy->SetMarkerSize(1.2);
    }
  canv->SetTitle("");
  canv->Update();
  canv->Print( ("output_test/Cor" + postfix + ".png").c_str() );
  canv->Print( ("output_test/Cor" + postfix + ".pdf").c_str() );
}

void art_hist_maker_2017(){
  string blind_cut   = " * (m_yy < 115 || m_yy > 135)";
  string lumi_weight = " * 41.05";

  string b_weight = "mc_weight * TMath::Abs(mc_raw_weight) * weight" + lumi_weight + blind_cut;
  // lumi_weight = xsection / sum_of_raw_weights
  // mc_weight   = lumi_weight * sign( mc_raw_weight )

  // string key, string lab, int nbins, double min, double max, string process_name = "", string expression, string weight_expression
  vector<PlotVariable> variables = {
    PlotVariable("m_yy", "m_{#gamma#gamma}", 25, 100, 160),
    PlotVariable("H_WW_tlv->M()", "m_{WW}",  20, 125, 500),
    PlotVariable("dR_yy * H_yy_tlv->Pt() / m_yy", "#Delta R(#gamma,#gamma) p_{T}^{H_{#gamma#gamma}} / m_{#gamma#gamma}", 25, 0., 5.),
    PlotVariable("dR_jj", "#Delta R(j,j)", 25, 0., 5.),
    PlotVariable("dR_WW", "#Delta R(W,W)", 25, 0., 5.),
    PlotVariable("dR_HH", "#Delta R(H,H)", 25, 0., 5.),
    PlotVariable("TMath::Abs( dPhi_nuL )", "|#Delta#phi(#nu,l)|", 25, 0., 3.14),
    PlotVariable("y1_tlv->Et()/m_yy", "E_{T}^{#gamma_{1}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("y2_tlv->Et()/m_yy", "E_{T}^{#gamma_{2}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("yy_mva", "flashgg MVA_{#gamma#gamma}", 25, 0., 1),
    PlotVariable("TMath::Abs( H_yy_tlv->CosTheta() )", "H cos #theta", 25, 0., 1),
    PlotVariable("TMath::Abs( lep_leading_tlv->Eta() )", "|#eta_{l}|", 25, 0., 2.5),
    PlotVariable("TMath::Abs( y1_tlv->Eta() )+TMath::Abs( y2_tlv->Eta() )+TMath::Abs( ljet1_tlv->Eta() )+TMath::Abs( ljet2_tlv->Eta() )", "|#eta_{#gamma_{1}}|+|#eta_{#gamma_{2}}|+|#eta_{j_{1}}|+|#eta_{j_{2}}|", 25, 0., 9.),
    PlotVariable("weight_TMVA_2017_trainFULLSIMv1_sm_BDT_b2_020", "BDT score", 25, -1, 1.),
  };

  vector<dataset> datasets = {
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/hzura_2017_sm_fsim_v2.root", "weight * reweight_factor_nlo_sm",  "SM",     "S"),
  /*dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_0 / weight_initial_v0",   "EFT 0",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_1 / weight_initial_v0",   "EFT 1",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_2 / weight_initial_v0",   "EFT 2",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_3 / weight_initial_v0",   "EFT 3",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_4 / weight_initial_v0",   "EFT 4",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_5 / weight_initial_v0",   "EFT 5",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_6 / weight_initial_v0",   "EFT 6",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_7 / weight_initial_v0",   "EFT 7",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_8 / weight_initial_v0",   "EFT 8",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_9 / weight_initial_v0",   "EFT 9",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_10 / weight_initial_v0",  "EFT 10", "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_11 / weight_initial_v0",  "EFT 11", "S"),*/
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/vh_2017_v2.root",  b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/vbf_2017_v2.root", b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ttH_2017_v2.root", b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ggh_2017_v2.root", b_weight, "SM H", "B"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ggjets_2017_v2.root", b_weight, "#gamma#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/gjets_2017_v2.root", b_weight, "#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/zgjets.root",  b_weight, "V#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/wgjets.root",  b_weight, "V#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/wgg.root",     b_weight, "V#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ttjets.root",  b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ttgg.root",    b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/ttgjets.root", b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/dy.root", b_weight, "DY", "B"),
 // dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/qcd.root", b_weight, "QCD", "B"),
 // dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/data_2017_v2.root",    "1" + blind_cut, "Data 2017", "D"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/data_2017_plusF.root", "1" + blind_cut, "Data 2017", "D"),
  };


  // make_correlation_plot(datasets, variables, "S", "S2017");
  // make_correlation_plot(datasets, variables, "B", "B2017");
  process_datasets(datasets, variables, "vars2017");
}

void art_hist_maker_vs(){ // 2018-2017 comp
  vector<dataset> datasets = {
 // dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_c0/hzura_2018_cHHH1_fsim_v0.root", "weight",  "SM 2018",     "S", "Def_Events"),
 // dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_SM / weight_initial_v0",  "SM 2017",     "S", "data"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_c0/hzura_2018_cHHH1_fsim_v0.root", "weight",  "SM 2018",     "S", "Def_Events"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_SM / weight_initial_v0",  "SM 2017",     "S", "data")
  };

  vector<PlotVariable> variables = {
    PlotVariable("ljet1_tlv->Pt()", "ljet1_tlv->Pt()", 100, 0, 200),
    PlotVariable("ljet2_tlv->Pt()", "ljet2_tlv->Pt()", 100, 0, 200),
    
    PlotVariable("ljet1_tlv->Eta()", "ljet1_tlv->Eta()", 100, -5, 5),
    PlotVariable("ljet2_tlv->Eta()", "ljet2_tlv->Eta()", 100, -5, 5),
  };
  
  process_datasets(datasets, variables);
}

void art_hist_maker_2018(){ // 2018

  string blind_cut = " * (m_yy < 115 || m_yy > 135)";
  string lumi_weight = " * 54.4";
  string b_weight = "mc_weight * TMath::Abs(mc_raw_weight) * weight" + lumi_weight + blind_cut;

  // string key, string lab, int nbins, double min, double max, string process_name = "", string expression, string weight_expression
  vector<PlotVariable> variables = {
    PlotVariable("m_yy", "m_{#gamma#gamma}", 25, 100, 160),
    PlotVariable("H_WW_tlv->M()", "m_{WW}",  20, 125, 500),
    PlotVariable("dR_yy * H_yy_tlv->Pt() / m_yy", "#Delta R(#gamma,#gamma) p_{T}^{H_{#gamma#gamma}} / m_{#gamma#gamma}", 25, 0., 5.),
    PlotVariable("dR_jj", "#Delta R(j,j)", 25, 0., 5.),
    PlotVariable("dR_WW", "#Delta R(W,W)", 25, 0., 5.),
    PlotVariable("dR_HH", "#Delta R(H,H)", 25, 0., 5.),
    PlotVariable("TMath::Abs( dPhi_nuL )", "|#Delta#phi(#nu,l)|", 25, 0., 3.14),
    PlotVariable("y1_tlv->Et()/m_yy", "E_{T}^{#gamma_{1}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("y2_tlv->Et()/m_yy", "E_{T}^{#gamma_{2}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("yy_mva", "flashgg MVA_{#gamma#gamma}", 25, 0., 1),
    PlotVariable("TMath::Abs( H_yy_tlv->CosTheta() )", "H cos #theta", 25, 0., 1),
    PlotVariable("TMath::Abs( lep_leading_tlv->Eta() )", "|#eta_{l}|", 25, 0., 2.5),
    PlotVariable("TMath::Abs( y1_tlv->Eta() )+TMath::Abs( y2_tlv->Eta() )+TMath::Abs( ljet1_tlv->Eta() )+TMath::Abs( ljet2_tlv->Eta() )", "|#eta_{#gamma_{1}}|+|#eta_{#gamma_{2}}|+|#eta_{j_{1}}|+|#eta_{j_{2}}|", 25, 0., 9.)
  };
  
  vector<dataset> datasets = {
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/hzura_2018_cHHH1_fsim_v2.root", "mc_weight * TMath::Abs(mc_raw_weight) * weight",  "SM NLO Powheg",     "S"),
  /*dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_0 / weight_initial_v0",   "EFT 0",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_1 / weight_initial_v0",   "EFT 1",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_2 / weight_initial_v0",   "EFT 2",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_3 / weight_initial_v0",   "EFT 3",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_4 / weight_initial_v0",   "EFT 4",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_5 / weight_initial_v0",   "EFT 5",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_6 / weight_initial_v0",   "EFT 6",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_7 / weight_initial_v0",   "EFT 7",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_8 / weight_initial_v0",   "EFT 8",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_9 / weight_initial_v0",   "EFT 9",  "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_10 / weight_initial_v0",  "EFT 10", "S"),
    dataset("./output/chanels_split_2017/hzura_2017_all_fsim_v0.root", "weight * weight_nlo_11 / weight_initial_v0",  "EFT 11", "S"),*/
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/2018_ggjets_v2.root", b_weight, "#gamma#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/2018_gjets1_v2.root", b_weight, "#gamma+jets", "B"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/zgjets.root",  b_weight, "Z#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/wgjets.root",  b_weight, "W#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/ttjets.root",  b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/ttgg.root",    b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/ttgjets.root", b_weight, "tt+0,1,2#gamma+jets", "B"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/data_2018_v2.root", "1" + blind_cut, "2018", "D"),
  };
  
  vector<string> benchmarks = {"sm"};
  for(auto mark : benchmarks){
    datasets.push_back( dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/hzura_2018_" + mark + "_fsim_v2.root", "weight * reweight_factor_nlo_sm",  "SM MadGraph",    "S") );
  }

  process_datasets(datasets, variables, "vars2018");
}

void art_hist_maker_2016_vs_2016NEW(){ // 2018

  string blind_cut = " * (m_yy < 115 || m_yy > 135)";
  string lumi_weight = " * 35.91765";
  string b_weight = "mc_weight * TMath::Abs(mc_raw_weight) * weight" + lumi_weight + blind_cut;

  // string key, string lab, int nbins, double min, double max, string process_name = "", string expression, string weight_expression
  vector<PlotVariable> variables = {
    PlotVariable("m_yy", "m_{#gamma#gamma}", 25, 100, 160),
    PlotVariable("H_WW_tlv->M()", "m_{WW}",  20, 125, 500),
    PlotVariable("gen_HHi_tlv->M()", "m_{HH}^{gen}",  25, 125, 800),
    PlotVariable("dR_yy * H_yy_tlv->Pt() / m_yy", "#Delta R(#gamma,#gamma) p_{T}^{H_{#gamma#gamma}} / m_{#gamma#gamma}", 25, 0., 5.),
    PlotVariable("dR_jj", "#Delta R(j,j)", 25, 0., 5.),
    PlotVariable("dR_WW", "#Delta R(W,W)", 25, 0., 5.),
    PlotVariable("dR_HH", "#Delta R(H,H)", 25, 0., 5.),
    PlotVariable("TMath::Abs( dPhi_nuL )", "|#Delta#phi(#nu,l)|", 25, 0., 3.14),
    PlotVariable("y1_tlv->Et()/m_yy", "E_{T}^{#gamma_{1}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("y2_tlv->Et()/m_yy", "E_{T}^{#gamma_{2}} / m_{#gamma#gamma}", 25, 0., 3),
    PlotVariable("yy_mva", "flashgg MVA_{#gamma#gamma}", 25, 0., 1),
    PlotVariable("TMath::Abs( H_yy_tlv->CosTheta() )", "H cos #theta", 25, 0., 1),
    PlotVariable("TMath::Abs( lep_leading_tlv->Eta() )", "|#eta_{l}|", 25, 0., 2.5),
    PlotVariable("TMath::Abs( y1_tlv->Eta() )+TMath::Abs( y2_tlv->Eta() )+TMath::Abs( ljet1_tlv->Eta() )+TMath::Abs( ljet2_tlv->Eta() )", "|#eta_{#gamma_{1}}|+|#eta_{#gamma_{2}}|+|#eta_{j_{1}}|+|#eta_{j_{2}}|", 25, 0., 9.)
  };
  
  vector<dataset> datasets = {
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/cHHH1.root", "mc_weight * TMath::Abs(mc_raw_weight) * weight",  "SM NLO Powheg",     "S"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/sm.root",    "mc_weight * TMath::Abs(mc_raw_weight) * weight",  "SM LO MadGraph",    "S"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v2_SYS/hzura_cHHH1_v2.root", "mc_weight * TMath::Abs(mc_raw_weight) * weight",  "SM NLO Powheg OLD PHOTON MVA SF",     "S"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ggjets.root", b_weight, "#gamma#gamma+jets", "B"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ttgg.root",    b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ttgjets.root", b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ttjets.root",  b_weight, "tt+0,1,2#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/zgjets.root",  b_weight, "V#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/wgjets.root",  b_weight, "V#gamma+jets", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/dy.root",  b_weight, "DY",   "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/vbf.root", b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/vh.root",  b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ttH.root", b_weight, "SM H", "B"),
    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/ggh.root", b_weight, "SM H", "B"),

    dataset("/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/data_2016.root", "1" + blind_cut, "CMS 2016", "D"),
  };

  process_datasets(datasets, variables, "vars2016_vs");
}

/*
void make_tmva_hist(
  string file_name, 
  string tree_name, 
  string weight_expressions,
  TMVA::Reader * tmva_reader, 
  TMVA::IMethod * tmva_method, 
  vector<float*> & values_f,
  TH1D * hist,
  int max_events = -1
){
  cout << "make_tmva_hist() : " << endl;
  cout << "  file : " << file_name << endl;
  cout << "  tree : " << tree_name << endl;

  TFile * file = TFile::Open(file_name.c_str());
  TTree * tree = (TTree*) gDirectory->Get( tree_name.c_str() );

  vector<TTreeFormula*> weights_f;
  for(string weight_expression : weight_expressions)
    weights_f.push_back( new TTreeFormula(weight_expression.c_str(), weight_expression.c_str(), tree) );

  auto variables = get_variables_train();
  vector<TTreeFormula*> values;
  for(auto var : variables){
    string vname = var.expression;
    values.push_back( new TTreeFormula(vname.c_str(), vname.c_str(), tree) );
  }

  double tmva_value;
  int nevents = tree->GetEntries();
  int used_events = 0;
  for(int i = 0; i < nevents; i++){
    tree->GetEntry(i);

    for(int j = 0; j < values_f.size(); j++) *(values_f[j]) = values.at(j)->EvalInstance();
    tmva_value = tmva_method->GetMvaValue();

    for(int j = 0; j < weights_f.size(); j++){
      double r_weight = 1;

      if(TMVA_TRANSFORMATION != nullptr) tmva_value = TMVA_TRANSFORMATION->GetScore( tmva_value );
      
      hist->Fill( tmva_value, weights_f.at(j)->EvalInstance() * r_weight );
    }

    used_events++;
    if(max_events > 0 and i >= max_events) break;
  }

  if(max_events > 0){
    cout << "  Scale : " << tree->GetEntries()/used_events << endl;
    hist->Scale( tree->GetEntries()/used_events );
  }

  for(int i = 0; i < weight_expressions.size(); i++)
    delete weights_f.at(i);

  for(int i = 0; i < values.size(); i++)
    delete values.at(i);

  file->Close();
}


void art_tmva_hist_maker(string year = "2017"){
  TMVA::Reader  * tmva_reader = new TMVA::Reader( "<options>" );
  auto variables = get_variables_train();
  vector<float*> values_f;
  for(auto var : variables){
    string vname = var.expression;
    values_f.push_back( new float );
    tmva_reader->AddVariable( vname.c_str(), (values_f.at( values_f.size() - 1 )) );
  }
  TMVA::IMethod * tmva_method = tmva_reader->BookMVA( tmva_name.c_str(), tmva_input.c_str() );

    HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
    for(int j = 0; j < datasets.size(); j++){
      dataset ds = datasets.at(j);
      TH1D * hist = new TH1D( datasets.at(j).name, datasets.at(j).latex_name );
      make_tmva_hist("", "Def_Events", "1", tmva_reader, tmva_method, values_f, hist );
      drawer->AddProcess( hist, datasets.at(j).type, datasets.at(j).latex_name );
    }
    draw_hists_CMS( drawer, "output_test/tmva_out.png", "BDT score", "", "tmva" );
}*/

void make_model_hists_(string year, vector<string> files){
  TFile * fdata = TFile::Open( files[0].c_str() );
  TFile * fmc = TFile::Open( files[1].c_str() );

  HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
  TH1D * dhist = (TH1D*)fdata->Get("CH_S_data");
  if(true){
    for(int i = 115; i <= 135; i++){
      dhist->SetBinContent( dhist->GetXaxis()->FindBin( i ), 0 );
    }
  }
  drawer->Add( dhist, "D", "CMS " + year );
  drawer->Add( (TH1D*)fdata->Get("CH_S_background"), "B", "Continuum background" );
  drawer->Add( (TH1D*)fmc->Get("CH_S_H_tmvasm"), "B", "ggF H" );
  drawer->Add( (TH1D*)fmc->Get("CH_S_VH_tmvasm"), "B", "VH" );
  drawer->Add( (TH1D*)fmc->Get("CH_S_VBFH_tmvasm"), "B", "VBF H" );
  drawer->Add( (TH1D*)fmc->Get("CH_S_ttH_tmvasm"), "B", "ttH" );
  drawer->Add( (TH1D*)fmc->Get("CH_S_HH_tmvasm"), "S", "SM HH" );
  draw_hists_CMS( drawer, "output_test/", "model_S" + year + ".pdf", "m_{#gamma#gamma} [GeV]", "", "tmva" );

  HistDrawer<TH1D> * drawer1 = new HistDrawer<TH1D>();
  TH1D * dhist1 = (TH1D*)fdata->Get("CH_B_data");
  if(true){
    for(int i = 115; i <= 135; i++){
      dhist1->SetBinContent( dhist->GetXaxis()->FindBin( i ), 0 );
    }
  }
  drawer1->Add( dhist1, "D", "CMS " + year );
  drawer1->Add( (TH1D*)fdata->Get("CH_B_background"), "B", "Continuum background" );
  drawer1->Add( (TH1D*)fmc->Get("CH_B_H_tmvasm"), "B", "ggF H" );
  drawer1->Add( (TH1D*)fmc->Get("CH_B_VH_tmvasm"), "B", "VH" );
  drawer1->Add( (TH1D*)fmc->Get("CH_B_VBFH_tmvasm"), "B", "VBF H" );
  drawer1->Add( (TH1D*)fmc->Get("CH_B_ttH_tmvasm"), "B", "ttH" );
  drawer1->Add( (TH1D*)fmc->Get("CH_B_HH_tmvasm"), "S", "SM HH" );
  draw_hists_CMS( drawer1, "output_test/", "model_B" + year + ".pdf", "m_{#gamma#gamma} [GeV]", "", "tmva" );
}

void make_model_hists(){

  vector<string> files_2018 = {"/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2018_DATA_sm_123.root", "/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2018_all_123_123j_0.root"};

  vector<string> files_2017 = {"/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2017_DATA_sm_120.root", "/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2017_all_120_120j_0.root"};

  vector<string> files_2016 = {"/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2016_DATA_sm_117.root", "/afs/cern.ch/user/p/pmandrik/public/temp/combo_cards/hists_2016_all_117_117j_0.root"};

  make_model_hists_("2018", files_2018);
  make_model_hists_("2017", files_2017);
  make_model_hists_("2016", files_2016);
}

void art_hist_maker(){
  // art_hist_maker_2017();
  // make_model_hists();
  // art_tmva_hist_maker("2017");

  art_hist_maker_2016_vs_2016NEW();
}










