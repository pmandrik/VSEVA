
#include "../../vseva.hh"

using namespace vseva;

void comp_hists_0(){ // different CMSSW versions
  // TFile * file_2 = TFile::Open("/eos/user/p/pmandrik/HHWWgg_hzura/output_TMP/data_2017_v0.root");
  // TFile * file_1 = TFile::Open("/eos/user/p/pmandrik/HHWWgg_hzura/output_TMP/data_2018_v0.root");

  TFile * file_1 = TFile::Open("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v2/hzura_2017_sm_fsim_v2.root");
  TFile * file_2 = TFile::Open("/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v2/hzura_2017_sm_fsim_v2.root");

  TTree * tree_1 = (TTree*) file_1->Get("Def_Events");
  TTree * tree_2 = (TTree*) file_2->Get("Def_Events");

  draw_hists_from_two_ttrees( tree_1, tree_2, "2017 new", "2017", "1.", "1." );
}

void comp_hists_1(){ // correlation betweeen m_yy and other variables

  TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels/hzura_2017_SM_v7_Def_Events_ch78.root");
  TFile * file_2 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels/hzura_2017_ggjets_mgg80toInf_v7_Def_Events_ch78.root");

  TTree * tree_1 = (TTree*) file_1->Get("Def_Events");
  TTree * tree_2 = (TTree*) file_2->Get("Def_Events");

  vector<string> variables = { 
            "m_yy",
            // dR
            "dR_yy", "dR_jj", "dR_WL", "dR_WW", "dR_HH", "TMath::Abs( dPhi_nuL )",
            // M
            "W_jj_tlv->M()", "W_elnu_tlv->M()", "H_WW_tlv->M()",
            // HH
            "TMath::Abs( HH_tlv->CosTheta() )", "HH_tlv->M()",
            // pT
            "y1_tlv->Et()/m_yy", "y2_tlv->Et()/m_yy", 
            "nu_reco_tlv->Et()", "lep_leading_tlv->Pt()", 
            "ljet1_tlv->Pt()", "ljet2_tlv->Pt()", 
            "W_elnu_tlv->Pt()", "W_jj_tlv->Pt()", 
            "H_yy_tlv->Pt()", "H_WW_tlv->Pt()", 
            "HH_tlv->Pt()",
            // Eta
            "y1_tlv->Eta()", "y2_tlv->Eta()", 
            "nu_reco_tlv->Eta()", "lep_leading_tlv->Eta()", 
            "ljet1_tlv->Eta()", "ljet2_tlv->Eta()", 
            "W_elnu_tlv->Eta()", "W_jj_tlv->Eta()", 
            "H_yy_tlv->Eta()", "H_WW_tlv->Eta()", 
            "HH_tlv->Eta()",
            // MVA
            "ljet1_btag", "ljet2_btag", 
            "y1_mva", "y2_mva",
            "yy_mva",
            // CosTheta
            // "CosTheta_y1_Hyy", "CosTheta_j1_Wjj", "CosTheta_Hww_W_jj"
           };

    vector<string> labels = { 
            "M_{#gamma#gamma} [GeV]",
            // dR
            "#Delta R(#gamma,#gamma)", "#Delta R(j,j)", "#Delta R(W_{l#nu},l_{leading})", "#Delta R(W,W)", "#Delta R(H,H)", "#Delta #phi(#nu,l_{leading})",
            // M
            "M_{W_{jj}} [GeV]", "M_{W_{l#nu}} [GeV]", "M_{H_{WW}} [GeV]",
            // HH
            "H cos{#theta}", "M_{HH} [GeV]",
            // pT
            "#frac{E_{T}^{#gamma_{leading}}}{M_{#gamma#gamma}}", "#frac{E_{T}^{#gamma_{second}}}{M_{#gamma#gamma}}", 
            "E_{T}^{#nu} [GeV]", "p_{T}^{l} [GeV]", 
            "p_{T}^{leading jet} [GeV]", "p_{T}^{second jet} [GeV]", 
            "p_{T}^{W_{l#nu}} [GeV]", "p_{T}^{W_{jj}} [GeV]", 
            "p_{T}^{H_{#gamma#gamma}} [GeV]", "p_{T}^{H_{WW}} [GeV]",
            "p_{T}^{HH}",
            // Eta
            "y1_tlv->Eta()", "y2_tlv->Eta()", 
            "nu_reco_tlv->Eta()", "lep_leading_tlv->Eta()", 
            "ljet1_tlv->Eta()", "ljet2_tlv->Eta()", 
            "W_elnu_tlv->Eta()", "W_jj_tlv->Eta()", 
            "H_yy_tlv->Eta()", "H_WW_tlv->Eta()", 
            "HH_tlv->Eta()",
            // MVA
            "b-tag score leading jet", "b-tag score second jet", 
            "flashgg MVA score #gamma_{leading}", "flashgg MVA #gamma_{second}",
            "flashgg MVA score diphoton",
            // CosTheta
            "CosTheta_y1_Hyy", "CosTheta_j1_Wjj", "CosTheta_Hww_W_jj"
           };

  variables = { "m_yy", "dR_yy * H_yy_tlv->Pt() / m_yy", "dR_jj", "dR_WW", "dR_HH", "TMath::Abs( dPhi_nuL )",
            "H_WW_tlv->M()",
            "TMath::Abs( HH_tlv->CosTheta() )", "HH_tlv->M()",
            "y1_tlv->Et()/m_yy", "y2_tlv->Et()/m_yy", 
            "TMath::Abs( y1_tlv->Eta() )+TMath::Abs( y2_tlv->Eta() )+TMath::Abs( ljet1_tlv->Eta() )+TMath::Abs( ljet2_tlv->Eta() )",
            "TMath::Abs( lep_leading_tlv->Eta() )",
            "yy_mva" };
  labels = {"M_{#gamma#gamma} [GeV]", "#Delta R(#gamma,#gamma) * p_{T}^{H_{#gamma#gamma}} / m_{#gamma#gamma} ", "#Delta R(j,j)", /*"#Delta R(W,l)",*/ "#Delta R(W,W)", "#Delta R(H,H)", "|#Delta#phi(#nu,l)|",
    "M_{H_{WW}} [GeV]", 
    "cos_{H} #theta^{*}", "M_{HH} [GeV]", 
    "E_{T}^{#gamma_{1}} / m_{#gamma#gamma}", "E_{T}^{#gamma_{2}} / m_{#gamma#gamma}",
    "|#eta_{#gamma_{1}}|+|#eta_{#gamma_{2}}|+|#eta_{j_{1}}|+|#eta_{j_{2}}|",
    "|#eta_{l}|",
    "flashgg MVA_{#gamma#gamma}"
  };

  draw_correlations_from_two_ttrees(tree_1, tree_2, variables, labels);
}


void comp_hists_2(){ // different CMSSW versions

  TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7a/hzura_2017_SM_v7a.root");
  TFile * file_2 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7/hzura_2017_SM_v7.root");

  TTree * tree_1 = (TTree*) file_1->Get("Def_Events");
  TTree * tree_2 = (TTree*) file_2->Get("Def_Events");

  draw_hists_from_two_ttrees( tree_1, tree_2, "smallest m_{WW}", "smallest |p_{z}|" );
}

double get_sum_of_variable(TTree * ttree, string expr){
  TTreeFormula weight_f(expr.c_str(), expr.c_str(), ttree);
  double sum = 0;
  int nevents = ttree->GetEntries();
  for(int i = 0; i < nevents; i++){
    ttree->GetEntry(i);
    sum += weight_f.EvalInstance();
  }
  return sum;
}

void comp_hists_3(){ // different CMSSW versions

  TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys/hzura_2017_EFT9_v7_Def_Events_ch78.root");
  TFile * file_2 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted/hzura_2017_9_v7_Def_Events_ch78.root");

  TTree * tree_1 = (TTree*) file_1->Get("data");
  TTree * tree_2 = (TTree*) file_2->Get("data");

  double sum_1 = get_sum_of_variable(tree_1, "weight");
  double sum_2 = get_sum_of_variable(tree_2, "weight * weight_lo");

  draw_hists_from_two_ttrees( tree_1, tree_2, "EFT 9 LO", "EFT 9 LO (reweight)", "weight / " + to_string(sum_1), "weight * weight_lo / " + to_string(sum_2) );
}

void comp_hists_4(){ // different CMSSW versions

  vector<string> names = {"SM", "box"};
  vector<string> samples;
  samples.push_back( "/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted/hzura_2017_SM_v7_Def_Events_ch78.root" );
  samples.push_back( "/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted/hzura_2017_box_v7_Def_Events_ch78.root" );

  for(int i = 0; i < 12; i++){
    names.push_back( to_string(i) );
    samples.push_back( "/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted/hzura_2017_EFT" + to_string(i) + "_v7_Def_Events_ch78.root" );
  }

  for(int i = 0; i < names.size(); i++){
    string name = names.at(i);
    string inp_name = samples.at(i);
    TFile * file = TFile::Open( inp_name.c_str() );
    TTree * tree = (TTree*) file->Get("data");

    double sum_d = get_sum_of_variable(tree, "weight");
    double sum_0 = get_sum_of_variable(tree, "weight*weight_lo");
    double sum_1 = get_sum_of_variable(tree, "weight*weight_nlo");
    double sum_2 = get_sum_of_variable(tree, "weight*weight_lo_carv");

    
    TTreeFormula weight_f("weight_lo_carv", "weight_lo_carv", tree);
    int nevents = tree->GetEntries();
    for(int i = 0; i < nevents; i++){
      tree->GetEntry(i);
      // cout << i << " " << weight_f.EvalInstance() << endl;;
    }
    // break;

    TH1D* hd = new TH1D("hd", "Origin SM", 20, 250, 1200);
    TH1D* h0 = new TH1D("h0", "Reweight LO II", 20, 250, 1200);
    TH1D* h1 = new TH1D("h1", "Reweight NLO II", 20, 250, 1200);
    TH1D* h2 = new TH1D("h2", "Reweight LO I", 20, 250, 1200);

    tree->Draw( "gen_HHi_tlv.M() >> hd", ("weight /" + to_string(sum_d) ).c_str() );
    tree->Draw( "gen_HHi_tlv.M() >> h0", ("weight * weight_lo /" + to_string(sum_0) ).c_str() );
    tree->Draw( "gen_HHi_tlv.M() >> h1", ("weight * weight_nlo /" + to_string(sum_1) ).c_str() );
    tree->Draw( "gen_HHi_tlv.M() >> h2", ("weight * weight_lo_carv /" + to_string(sum_2) ).c_str() );

    HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
    drawer->Add(hd, "S");
    drawer->Add(h2, "S");
    drawer->Add(h0, "S");
    drawer->Add(h1, "S");

    if(name == "2"){
      TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys/hzura_2017_EFT2_v7_Def_Events_ch78.root");
      TTree * tree_1 = (TTree*) file_1->Get("data");
      double sum = get_sum_of_variable(tree_1, "weight");
      TH1D* halt = new TH1D("halt", "EFT 2", 20, 250, 1200);
      tree_1->Draw( "gen_HHi_tlv.M() >> halt", ("weight / " + to_string(sum)).c_str() );
      drawer->Add(halt, "S");

      TH1D* halt1 = new TH1D("halt1", "EFT 2 Reco", 20, 250, 1200);
      tree_1->Draw( "HH_tlv.M() >> halt1", ("weight / " + to_string(sum)).c_str() );
      drawer->Add(halt1, "S");
    }

    if(name == "9"){
      TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys/hzura_2017_EFT9_v7_Def_Events_ch78.root");
      TTree * tree_1 = (TTree*) file_1->Get("data");
      double sum = get_sum_of_variable(tree_1, "weight");
      TH1D* halt = new TH1D("halt", "EFT 9", 20, 250, 1200);
      tree_1->Draw( "gen_HHi_tlv.M() >> halt", ("weight / " + to_string(sum)).c_str() );
      drawer->Add(halt, "S");

      TH1D* halt1 = new TH1D("halt1", "EFT 9 Reco", 20, 250, 1200);
      tree_1->Draw( "HH_tlv.M() >> halt1", ("weight / " + to_string(sum)).c_str() );
      drawer->Add(halt1, "S");
    }

    drawer->label_y = "";

    draw_hists_CMS(drawer, ".", "EFT_"+ name +".png", "M_{HH}", "EFT " + name, "tmva");

    file->Close();
  }
}

TH1D* get_cut_plot(string name, TH1D * h_11, TH1D * h_12){
  h_11->Scale( 1./h_11->Integral() );
  h_12->Scale( 1./h_12->Integral() );

  double sum_b = 1;
  double sum_s = 1;
  TH1D * h_a1 = new TH1D( name.c_str(), "signal",     100, -1, 1);
  for(int i = 1; i < 100; i++){
    sum_s -= h_11->GetBinContent( i );
    sum_b -= h_12->GetBinContent( i );
    if( sum_b + sum_s < 0.0001) break;
    cout << i << " " << sum_s / TMath::Sqrt(sum_b + sum_s) << endl;
    h_a1->SetBinContent( i, sum_s / TMath::Sqrt(sum_b + sum_s) );
  }
  return h_a1;
}


void comp_hists_5(){ 
  int index = 1;

  TFile * file_b = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys_2017/hzura_2017_ggjets_mgg80toInf_v0_Def_Events_ch78.root");
  TTree * tree_b = (TTree*) file_b->Get("data");

  TFile * file = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted_2017/hzura_2017_EFT_all_v0_Def_Events_ch78.root");
  TTree * tree = (TTree*) file->Get("data");

  TH1D * h_hh = new TH1D("hh", "signal",     100, 0, 1000);
  tree->Draw( "HH_tlv->M() >> hh", ("weight_nlo_" + to_string(index)).c_str() ); // weight_TMVA_2017_train5_SM_BDT_b2_037
  TCanvas * c = new TCanvas("canv", "canv", 640, 480);
  h_hh->Draw();
  c->Print("hh_m_test.png");
  return;

  TH1D * h_11 = new TH1D("s1", "signal",     100, -1, 1);
  TH1D * h_12 = new TH1D("b1", "background", 100, -1, 1);
  tree->Draw(   "weight_TMVA_2017_train5_SM_BDT_b2_037 >> s1", ("weight * weight_nlo_" + to_string(index)).c_str() ); // weight_TMVA_2017_train5_SM_BDT_b2_037
  tree_b->Draw( "weight_TMVA_2017_train5_SM_BDT_b2_037 >> b1", "weight" );

  TH1D * h_21 = new TH1D("s2", "signal",     100, -1, 1);
  TH1D * h_22 = new TH1D("b2", "background", 100, -1, 1);
  tree->Draw(   ("weight_TMVA_2017_train5_" + to_string(index) + "_BDT_b2_037 >> s2").c_str(), ("weight * weight_nlo_" + to_string(index)).c_str() ); // weight_TMVA_2017_train5_SM_BDT_b2_037
  tree_b->Draw( ("weight_TMVA_2017_train5_" + to_string(index) + "_BDT_b2_037 >> b2").c_str(), "weight" );

  TH1D * h_a1 = get_cut_plot("SM", h_11, h_12);
  TH1D * h_a2 = get_cut_plot("5", h_21, h_22);

  h_a1->SetTitle("TMVA SM");
  h_a2->SetTitle( ("TMVA EFT " + to_string(index) ).c_str() );


  TCanvas * canv = new TCanvas("canv", "canv", 640, 480);
  h_a1->GetXaxis()->SetTitle("MVA cut");
  h_a1->GetYaxis()->SetTitle("S / #sqrt{S+B}");

  h_a1->Draw();
  h_a2->Draw("same");
  h_a2->SetLineColor(2);

        // canv->BuildLegend(); /cvmfs/cms.cern.ch/phys_generator/gridpacks/pre2017/13TeV/madgraph/V5_2.6.5/GF_HH_10/v1/GF_HH_10_slc6_amd64_gcc630_CMSSW_9_3_16_tarball.tar.xz
  canv->Print("Test.png");
}






















void comp_hists(){ 
  comp_hists_0();
}











