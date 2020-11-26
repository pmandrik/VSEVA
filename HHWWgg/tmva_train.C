
#include "analyse_cfg.C"

struct Variable{
  Variable(){}
  Variable(string expression, string title="", string unit=""){
    this->expression = expression;
    this->title = title;
    this->unit  = unit;
  }

  string expression, title, unit;
  double xmin, xmax;
};

vector<Variable> get_variables_train(){
  vector<string> exps;
  exps = { 
            //--X "m_yy",
            // dR
            "dR_yy * H_yy_tlv->Pt() / m_yy", "dR_jj", /*"dR_WL",*/ "dR_WW", "dR_HH", "TMath::Abs( dPhi_nuL )",
            // M
            /*"W_jj_tlv->M()", "W_elnu_tlv->M()",*/ "H_WW_tlv->M()",
            // HH
            "TMath::Abs( H_yy_tlv->CosTheta() )", // "HH_tlv->M()",
            // pT
            "y1_tlv->Et()/m_yy", "y2_tlv->Et()/m_yy", 
            //"(y1_tlv->Et() - y2_tlv->Et())/(y1_tlv->Et()+y2_tlv->Et())", 
            //"nu_reco_tlv->Et() / W_elnu_tlv->M()", // "lep_leading_tlv->Pt() / W_elnu_tlv->M()", 
            //"TMath::Abs( nu_reco_tlv->Et() - lep_leading_tlv->Pt() ) / ( nu_reco_tlv->Et() + lep_leading_tlv->Pt() )", 
            //"ljet1_tlv->Pt() / W_jj_tlv->M()", "ljet2_tlv->Pt() / W_jj_tlv->M()", 
            //"(ljet1_tlv->Pt() - ljet2_tlv->Pt()) / ( ljet1_tlv->Pt() + ljet2_tlv->Pt() )", 
            /*--X"W_elnu_tlv->Pt()", "W_jj_tlv->Pt()", */
            /*--X"H_yy_tlv->Pt()", "H_WW_tlv->Pt()", */
            //"HH_tlv->Pt()",
            // Eta
            "TMath::Abs( y1_tlv->Eta() )+TMath::Abs( y2_tlv->Eta() )+TMath::Abs( ljet1_tlv->Eta() )+TMath::Abs( ljet2_tlv->Eta() )",
            //"TMath::Abs( y1_tlv->Eta() )", "TMath::Abs( y2_tlv->Eta() )", 
            /*"TMath::Abs( nu_reco_tlv->Eta() )",*/ "TMath::Abs( lep_leading_tlv->Eta() )", 
            //"TMath::Abs( ljet1_tlv->Eta() )", "TMath::Abs( ljet2_tlv->Eta() )", 
            //--X "W_elnu_tlv->Eta()", "W_jj_tlv->Eta()", 
            //--X "H_yy_tlv->Eta()", "H_WW_tlv->Eta()", 
            //--X "HH_tlv->Eta()",
            // MVA
            //"ljet1_btag", "ljet2_btag", 
            //"y1_mva", "y2_mva",
            "yy_mva",
            // CosTheta
            // "CosTheta_y1_Hyy", "CosTheta_j1_Wjj", "CosTheta_Hww_W_jj"
           };

  vector<string> titles = {
    "#Delta R(#gamma,#gamma) * p_{T}^{H_{#gamma#gamma}} / m_{#gamma#gamma} ", "#Delta R(j,j)", "#Delta R(W,W)", "#Delta R(H,H)", "|#Delta#phi(#nu,l)|",
    "M_{WW} [GeV]",
    "H cos #theta", // "M_{HH} [GeV]", 
    "E_{T}^{#gamma_{1}} / m_{#gamma#gamma}", "E_{T}^{#gamma_{2}} / m_{#gamma#gamma}",
    "|#eta_{#gamma_{1}}|+|#eta_{#gamma_{2}}|+|#eta_{j_{1}}|+|#eta_{j_{2}}|",
    "|#eta_{l}|",
    "flashgg MVA_{#gamma#gamma}"
  };

  vector<Variable> vanswer;
  for(int i = 0; i < exps.size(); i++){
      
    string s = exps.at( i );
    string t = s;
    if( titles.size() == exps.size() ) t = titles.at(i);
    vanswer.push_back( Variable(s, t) );
  }
  return vanswer;
}

TTree * get_tree(string file_name, string tree_name){
  TFile * file = TFile::Open( file_name.c_str() );
  if(not file) return nullptr;
  auto tree = (TTree*) file->Get(tree_name.c_str());
  return (TTree*) file->Get(tree_name.c_str());
}

vector<vseva::DataSet*> get_train_datasets(){
  vector<vseva::DataSet*> answer = {
    get_dataset( "hzura_2017_SM_v7",            "SM",                     "SM",             1.,            1., "S" ),
    get_dataset( "hzura_2017_ggjets_mgg80toInf_v7",        "#gamma#gamma+jets",    "ggjets",           1.,            1., "B" )
  };
  return answer;
}

struct TrainDataset{
  bool signal;
  string input_path;
  string train_tree_name;
  string data_tree_name;
  string weight_exp;
};

struct TrainCfg{
  string year;
  string name;
  vector<TrainDataset> datasets;
  string s_cut_exp, b_cut_exp;
};

void tmva_train(){

  (TMVA::gConfig().GetVariablePlotting()).fMaxNumOfAllowedVariablesForScatterPlots = 0;
  string CHANNEL = "78";

  vector<string> node_names = {"sm", "cHHH0", "cHHH1", "cHHH2", "cHHH5"};
  for(int i = 1; i <= 12; i++) node_names.push_back( to_string(i) );
  // vector<string> years = {"2016", "2017", "2018"};
  vector<string> years = {"2018"} ;

  vector<TrainCfg> node_cfgs;
  for(auto year : years){
    for(auto node_name : node_names){
      TrainCfg cfg;
      cfg.year = year;
      cfg.name = node_name;

      if(year == "2016"){
        TrainDataset ggjets_dataset;
        ggjets_dataset.input_path      = "./output/chanels_split_2016/ggjets_v2.root";
        ggjets_dataset.signal          = false;
        ggjets_dataset.train_tree_name = "train";
        ggjets_dataset.data_tree_name  = "data";
        ggjets_dataset.weight_exp      = "weight * mc_weight";
        cfg.datasets.push_back( ggjets_dataset );

        if( node_name.find("cHHH") != string::npos ){
          TrainDataset node_dataset;
          node_dataset.signal          = true;
          node_dataset.input_path      = "./output/chanels_split_2016/hzura_" + node_name + "_v2.root";
          node_dataset.train_tree_name = "train";
          node_dataset.data_tree_name  = "data";
          node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight";
          cfg.datasets.push_back( node_dataset );
        } else { 
          vector<string> benchmarks = {"sm", "1", "2", "3", "4", "5", "6", "7", "8", "9", "12"};
          for(auto benchmark : benchmarks){
            TrainDataset node_dataset;
            node_dataset.signal          = true;
            node_dataset.input_path      = "./output/chanels_split_2016/hzura_2017_" + benchmark + "_fsim_v2.root";
            node_dataset.train_tree_name = "train";
            node_dataset.data_tree_name  = "data";
            node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight * reweight_factor_nlo_" + node_name;
            cfg.datasets.push_back( node_dataset );
          }
        }
      }

      if(year == "2017"){
        vector<string> b_datasets = { "dy.root", "wgg.root", "zgjets.root", "wgjets.root", "ttjets.root", "ttgjets.root", "ttgg.root", "ggjets.root", "gjets.root" };
        for( string bname :  b_datasets ){
          TrainDataset ggjets_dataset;
          ggjets_dataset.input_path      = "./output/chanels_split_2017_v2/" + bname;
          ggjets_dataset.signal          = false;
          ggjets_dataset.train_tree_name = "train";
          ggjets_dataset.data_tree_name  = "data";
          ggjets_dataset.weight_exp      = "mc_weight * TMath::Abs(mc_raw_weight) * weight";
          cfg.datasets.push_back( ggjets_dataset );
        }

        if( node_name.find("cHHH") != string::npos ){
          TrainDataset node_dataset;
          node_dataset.signal          = true;
          node_dataset.input_path      = "./output/chanels_split_2017_v2/" + node_name + ".root";
          node_dataset.train_tree_name = "train";
          node_dataset.data_tree_name  = "data";
          node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight";
          cfg.datasets.push_back( node_dataset );
        } else { 
          vector<string> benchmarks = {"sm", "1", "2", "3", "4", "5", "6", "7", "9", "12"};
          for(auto benchmark : benchmarks){
            TrainDataset node_dataset;
            node_dataset.signal          = true;
            node_dataset.input_path      = "./output/chanels_split_2017_v2/" + benchmark + ".root";
            node_dataset.train_tree_name = "train";
            node_dataset.data_tree_name  = "data";
            node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight * reweight_factor_nlo_" + node_name;
            cfg.datasets.push_back( node_dataset );
          }
        }
      }
      if(year == "2018"){
        vector<string> b_datasets = { "dy.root", "zgjets.root", "wgjets.root", "ttjets.root", "ttgjets.root", "ttgg.root", "ggjets.root", "gjets.root" };
        for( string bname :  b_datasets ){
          TrainDataset ggjets_dataset;
          ggjets_dataset.input_path      = "./output/chanels_split_2018_v2/" + bname;
          ggjets_dataset.signal          = false;
          ggjets_dataset.train_tree_name = "train";
          ggjets_dataset.data_tree_name  = "data";
          ggjets_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight";
          cfg.datasets.push_back( ggjets_dataset );
        }

        if( node_name.find("cHHH") != string::npos ){
          TrainDataset node_dataset;
          node_dataset.signal          = true;
          node_dataset.input_path      = "./output/chanels_split_2018_v2/" + node_name + ".root";
          node_dataset.train_tree_name = "train";
          node_dataset.data_tree_name  = "data";
          node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight";
          cfg.datasets.push_back( node_dataset );
        } else { 
          vector<string> benchmarks = {"sm", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
          for(auto benchmark : benchmarks){
            TrainDataset node_dataset;
            node_dataset.signal          = true;
            node_dataset.input_path      = "./output/chanels_split_2018_v2/" + benchmark + ".root";
            node_dataset.train_tree_name = "train";
            node_dataset.data_tree_name  = "data";
            node_dataset.weight_exp      = "TMath::Abs(mc_raw_weight) * weight * mc_weight * reweight_factor_nlo_" + node_name;
            cfg.datasets.push_back( node_dataset );
          }
        }
      }

      node_cfgs.push_back( cfg );
    }
  }

  for(int i = 0; i < node_cfgs.size(); i++){
    TrainCfg cfg = node_cfgs.at(i);

    string output_dir = "./output/tmva_" + cfg.year + "/";
    string postfix = "trainFULLSIMv2_" + cfg.name;
    postfix = "t5_" + cfg.name;

    TFile* outputFile = TFile::Open( (output_dir + "/TMVA_" + cfg.year + "_" + postfix + ".root").c_str(), "RECREATE" );
    TMVA::Factory *factory = new TMVA::Factory( "TMVA_" + cfg.year + "_" + postfix, outputFile, "" );

    double extra_weight = 1;
    bool skip_flag = false;
    for( auto channel : cfg.datasets ){
      auto tree      = get_tree( channel.input_path,     channel.train_tree_name );
      auto tree_data = get_tree( channel.input_path,     channel.data_tree_name  );
      cout << channel.input_path << " " << tree << " " << tree_data << endl;
      if(not tree or not tree_data){
        cout << "Skip ..." << endl;
        skip_flag = true;
        break;
      }
      cout << channel.input_path << " " << tree ->GetEntries() << " " << tree_data->GetEntries() << endl;
      if(tree->GetEntries() == 0) continue;
      
      if(channel.signal){
        // tree->Print();
        factory->AddSignalTree    (tree, extra_weight, TMVA::Types::kTraining);
        factory->AddSignalTree    (tree_data, extra_weight, TMVA::Types::kTesting);
        factory->SetWeightExpression( channel.weight_exp, "Signal");
      }
      if(not channel.signal){
        factory->AddBackgroundTree(tree, extra_weight, TMVA::Types::kTraining);
        factory->AddBackgroundTree(tree_data, extra_weight, TMVA::Types::kTesting);
        factory->SetWeightExpression( channel.weight_exp, "Background");
      }
    }
    if( skip_flag ) continue;

    auto variables = get_variables_train();
    for(auto var : variables){
      cout << "will use variable ... " << var.title << " " << var.expression << endl;
      factory->AddVariable( var.expression.c_str(), var.title.c_str(), var.unit.c_str(), 'D' );
    }

    factory->PrepareTrainingAndTestTree("", "");
  //factory->AddCut( cfg.s_cut_exp, "Signal" );
  //factory->AddCut( cfg.b_cut_exp, "Background" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_a2", "BoostType=Grad:nCuts=10:MaxDepth=2:NTrees=100" ); // V
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_a5", "BoostType=Grad:nCuts=5:MaxDepth=2:NTrees=100" ); // V
    factory->BookMethod( TMVA::Types::kBDT, "BDT_b2", "BoostType=AdaBoost:nCuts=10:MaxDepth=2:NTrees=150" ); // V
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
  }
}


/*
  answer = { 
            "m_yy",
            // dR
            "dR_yy", "dR_jj", "dR_WL", "dR_WW", "dR_HH", "dPhi_nuL",
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
            "CosTheta_y1_Hyy", "CosTheta_j1_Wjj", "CosTheta_Hww_W_jj"
           };
*/

/*
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a0", "BoostType=Grad:nCuts=10:MaxDepth=2:NTrees=50" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a1", "BoostType=Grad:nCuts=10:MaxDepth=2:NTrees=75" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a2", "BoostType=Grad:nCuts=10:MaxDepth=2:NTrees=100" ); // V
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a3", "BoostType=Grad:nCuts=15:MaxDepth=2:NTrees=100" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a4", "BoostType=Grad:nCuts=20:MaxDepth=2:NTrees=100" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_a5", "BoostType=Grad:nCuts=5:MaxDepth=2:NTrees=100" ); // V

    factory->BookMethod( TMVA::Types::kBDT, "BDT_b0", "BoostType=AdaBoost:nCuts=50:MaxDepth=3:NTrees=50" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_b1", "BoostType=AdaBoost:nCuts=20:MaxDepth=2:NTrees=150" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_b2", "BoostType=AdaBoost:nCuts=10:MaxDepth=2:NTrees=150" ); // V
    factory->BookMethod( TMVA::Types::kBDT, "BDT_b3", "BoostType=AdaBoost:nCuts=10:MaxDepth=2:NTrees=100" );

    vector<string> btypes = {"AdaBoost", "Grad", "RealAdaBoost"};
    vector<string> mdepths = {"2", "3"};
    vector<string> NTrees = {"50", "100", "150", "200", "300", "500", "800"};
    vector<string> NCuts = {"10", "20", "50", "100"};

    for( auto btype : btypes)
      for( auto mdepth : mdepths )
        for( auto ntree : NTrees )
          for( auto ncut : NCuts ){
            string name = "BDT_" + btype + "_MaxDepth" + mdepth + "_NTrees" + ntree + "_nCuts" + ncut;
            string options = "BoostType=" + btype + ":nCuts=" + ncut + ":MaxDepth=" + mdepth + ":NTrees=" + ntree;
            factory->BookMethod( TMVA::Types::kBDT, name.c_str(), options.c_str() );
          }
    */

  /*
    factory->BookMethod( TMVA::Types::kBDT, "BDT_0a", "BoostType=AdaBoost:nCuts=100:MaxDepth=2:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_1a", "BoostType=Bagging:nCuts=100:MaxDepth=2:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_3a", "BoostType=RealAdaBoost:nCuts=100:MaxDepth=2:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_4a", "BoostType=Grad:nCuts=100:MaxDepth=2:NTrees=200" );

    // factory->BookMethod( TMVA::Types::kBDT, "BDT_1a", "nCuts=100:MaxDepth=3:NTrees=500" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_0a", "nCuts=100:MaxDepth=5:NTrees=100" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_1a", "nCuts=100:MaxDepth=5:NTrees=175" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_2a", "nCuts=100:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_3a", "nCuts=100:MaxDepth=5:NTrees=250" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_4a", "nCuts=100:MaxDepth=5:NTrees=500" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT_0b", "nCuts=50:MaxDepth=5:NTrees=100" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_1b", "nCuts=150:MaxDepth=5:NTrees=175" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_2b", "nCuts=200:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_3b", "nCuts=300:MaxDepth=5:NTrees=250" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_4b", "nCuts=500:MaxDepth=5:NTrees=500" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT_0c", "nCuts=50:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_1c", "nCuts=150:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_2c", "nCuts=200:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_3c", "nCuts=300:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_4c", "nCuts=500:MaxDepth=5:NTrees=200" );

    factory->BookMethod( TMVA::Types::kBDT, "BDT_0d", "nCuts=100:MaxDepth=2:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_1d", "nCuts=100:MaxDepth=3:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_2d", "nCuts=100:MaxDepth=4:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_3d", "nCuts=100:MaxDepth=5:NTrees=200" );
    factory->BookMethod( TMVA::Types::kBDT, "BDT_4d", "nCuts=100:MaxDepth=6:NTrees=200" );
  */











