
#include "../../vseva.hh"

using namespace vseva;

void comp_hists_0(){ // different CMSSW versions

  TFile * file_1 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v6/hzura_2017_SM_v6.root");
  TFile * file_2 = TFile::Open("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7/hzura_2017_SM_v7.root");

  TTree * tree_1 = (TTree*) file_1->Get("Def_Events");
  TTree * tree_2 = (TTree*) file_2->Get("Def_Events");

  draw_hists_from_two_ttrees( tree_1, tree_2, "flashgg CMSSW_10_5_0", "flashgg CMSSW_10_6_8" );
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

void comp_hists(){ // different CMSSW versions

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













