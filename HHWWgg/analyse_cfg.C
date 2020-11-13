
#include "mRoot.cpp"
#include "mRootAnalyser.cpp"
#include "mRootAnalyseAlgo.cpp"
#include "mRootThread.cpp"

#include "../vseva.hh"

using namespace mRoot;
using namespace vseva;

//==================================================================================================== HHWWgg configuration 2020-11-03
void set_input_files(string node, string year, string & TMVA_NAME, string & input_data_file_name){
  if(year == "2018"){
    TMVA_NAME = "weight_TMVA_2018_t2_" + node + "_BDT_b2_0";
    input_data_file_name = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/data_2018_v2.root";
  }
  if(year == "2017"){
    TMVA_NAME = "weight_TMVA_2017_trainFULLSIMv1_" + node + "_BDT_b2_021";
    input_data_file_name = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/data_2017_plusF.root";
  }
  if(year == "2016"){
    TMVA_NAME = "weight_TMVA_2016_trainFULLSIMv1_" + node + "_BDT_b2_020";
    input_data_file_name = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v2_SYS/data_2016_v2.root";
  }
}

TMVATransformer * TMVA_TRANSFORMATION;
TMVATransformer * get_tmva(string node, string year){
  TMVATransformer * answer = new TMVATransformer();

  string file_name, tree_name, tmva_name;
  tree_name = "Def_Events";
  set_input_files( node, year, tmva_name, file_name );

  TFile * file = TFile::Open( file_name.c_str() );
  TTree * tree = (TTree *)file->Get( tree_name.c_str() );

  answer->AddTree( tree, tmva_name.c_str() );
  answer->Transform( 1 );

  file->Close();
  return answer;
}


//====================================================================================================



















vector<string> get_sysWeights(){
  // vector<string> alt_sys = {"sf_photons", "sf_electrons", "sf_muons_id", "sf_muons_iso", "sf_ljets_id", "sf_ljets_btag", "sf_bjets_id", "sf_bjets_btag", "sf_pileup", "FracRV", "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF"};
  vector<string> sys_weights, sys_weights_ = {"sf_electrons", "sf_pileup", "sf_muons_id", "sf_muons_iso", "sf_ljets_btag", /*"FracRV",*/ "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF", "PrefireSF"};
  vector<string>  fixes = {"up", "down"};
  for(auto sys : sys_weights_){
    for(auto fix : fixes){
      sys_weights.push_back( sys + "_" + fix );
    }
  }
  return sys_weights;
}

vector<string> get_sysWeights_names(){
  vector<string> sys_weights, sys_weights_ = {"sf_electrons", "sf_pileup", "sf_muons_id", "sf_muons_iso", "sf_ljets_btag", /*"FracRV",*/ "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF", "PrefireSF"};
  vector<string>  fixes = {"Up", "Down"};
  for(auto sys : sys_weights_){
    for(auto fix : fixes){
      sys_weights.push_back( sys + fix );
    }
  }
  return sys_weights;
}

vector<string> get_sysTrees(){
  vector<string> sys_ttres = {"FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp",
"JERUp", "JERDown", "JECUp", "JECDown", "UnclusteredMETUp", "UnclusteredMETDown"};

  return sys_ttres;
}

vseva::DataSet* get_dataset(string process_name, string latex_name, string short_name, double xsec, double weight_sum, string dataset_type){
  string wpath = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7/";
  vseva::DataSet* answer = new vseva::DataSet(process_name, latex_name, short_name, dataset_type);
  answer->xsec   = xsec;
  answer->weight_sum = weight_sum;
  answer->dataset_ttree_name = "";

  string fpath = wpath + "/" + process_name + ".root";

  answer->AddFile( fpath );
  return answer;
}

vector<vseva::DataSet*> get_datasets(bool sys = false){

  cout << "get_datasets() ... " << endl;
  vector<vseva::DataSet*> answer = {
      // DATA
      get_dataset( "hzura_2017_data_v7",          "CMS 2017",             "data2017",         1.,            1., "D" ),
      // Signals
      get_dataset( "hzura_2017_SM_v7",            "SM",                     "SM",             1.,            1., "S" ),
      get_dataset( "hzura_2017_EFT2_v7",          "EFT 3",                "EFT3",             1.,            1., "S" ),
      get_dataset( "hzura_2017_EFT9_v7",          "EFT 10",               "EFT10",            1.,            1., "S" ),
      // QCD
      get_dataset( "hzura_2017_ggjets_mgg80toInf_v7",        "#gamma#gamma+jets",    "ggjets",           1.,            1., "B" ),
      get_dataset( "hzura_2017_GJet_Pt_20to40_DoubleEMEnriched_MGG_80toInf_v7",          "#gamma+jets",          "gjets Pt_20to40",            1.,            1., "B" ),
      get_dataset( "hzura_2017_GJet_Pt_40toInf_DoubleEMEnriched_MGG_80toInf_v7",         "#gamma+jets",          "gjets Pt_40toInf",            1.,            1., "B" ),
      // H
      get_dataset( "hzura_2017_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_v7",        "SM H",    "ggH",           1.,            1., "B" ),
      get_dataset( "hzura_2017_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v7", "SM H",    "ttH",           1.,            1., "B" ),
      get_dataset( "hzura_2017_VBFHToGG_M125_13TeV_amcatnlo_pythia8_v7",               "SM H",  "VBF H",           1.,            1., "B" ),
      get_dataset( "hzura_2017_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v7",     "SM H",     "VH",           1.,            1., "B" ),
      /*
      // DATA
      get_dataset( "hzura_2017_data_v6",          "CMS 2017",             "data2017",         1.,            1., "D" ),
      // EFT signals
      get_dataset( "hzura_2017_SM_v6",            "SM",                     "SM",             1.,            1., "S" ),
      get_dataset( "hzura_2017_EFT2_v6",          "EFT 3",                "EFT3",             1.,            1., "S" ),
      get_dataset( "hzura_2017_EFT9_v6",          "EFT 10",               "EFT10",            1.,            1., "S" ),
      // QCD
      get_dataset( "hzura_2017_ggjets_mgg80toInf_v6",        "#gamma#gamma+jets",    "ggjets",           1.,            1., "B" ),
      get_dataset( "hzura_2017_gjet_mgg80toInf_v6",          "#gamma+jets",          "gjets",            1.,            1., "B" ),
      get_dataset( "hzura_2017_GJet_Pt_20to40_DoubleEMEnriched_MGG_80toInf_v6",   "#gamma+jets",    "gjets_pt",       1.,            1., "B" ),
      // get_dataset( "hzura_2017_QCD_Pt_30to40_DoubleEMEnriched_MGG_80toInf_v6",    "QCD Pt 30-40",            "qcd_pt",         1.,            1., "B" ),
      // get_dataset( "hzura_2017_QCD_Pt_40toInf_DoubleEMEnriched_MGG_80toInf_v6",   "QCD" ,                    "qcd",            1.,            1., "B" ),
      // H
      get_dataset( "hzura_2017_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_v6",        "SM H",    "ggH",           1.,            1., "B" ),
      get_dataset( "hzura_2017_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v6", "SM H",    "ttH",           1.,            1., "B" ),
      get_dataset( "hzura_2017_VBFHToGG_M125_13TeV_amcatnlo_pythia8_v6",               "SM H",  "VBF H",         1.,            1., "B" ),
      get_dataset( "hzura_2017_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v6",     "SM H",     "VH",            1.,            1., "B" ),
      //DY
      get_dataset( "hzura_2017_DYJetsToLL_M_50_TuneCP5_13TeV_amcatnloFXFX_pythia8_v6",               "DY",  "DY",         1.,            1., "B" ),
      //TTbar
      get_dataset( "hzura_2017_TTJets_TuneCP5_13TeV_amcatnloFXFX_pythia8_v6",  "t#bar{t}+0,1,2#gamma",     "tt",            1.,            1., "B" ),
      get_dataset( "hzura_2017_TTGJets_v6",                                    "t#bar{t}+0,1,2#gamma",     "ttg",            1.,            1., "B" ),
      get_dataset( "hzura_2017_TTGG_0Jets_v6",                                 "t#bar{t}+0,1,2#gamma",     "ttgg",           1.,            1., "B" ),
      //V+#gamma+jets
      get_dataset( "hzura_2017_WGToLNuG_01J_v6",                          "W/Z+#gamma",      "Wgjets",            1.,            1., "B" ),
      get_dataset( "hzura_2017_ZGToLLG_01J_v6",                           "W/Z+#gamma",      "Zgjets",            1.,            1., "B" ),
      */
  };
  
  // [1] https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt1314TeV2014
  // 0.1057 pb X 2.28E-03 X 
  // 48.58 * 1.06 * 0.00227 * 44.98 * 1000

  vector<string> sys_ttres = get_sysTrees();
  vector<vseva::DataSet*> answer_f;

  for(auto dataset : answer){
    dataset->dataset_ttree_name = "Def_Events";
    answer_f.emplace_back( dataset );
    if(not sys) continue;
    if( dataset->IsData() ) continue;
    if( dataset->IsBackground() ) continue;
    dataset->sys_dataset_ttree_name = sys_ttres;
  }

  return answer_f;

  for(auto dataset : answer){
    dataset->dataset_ttree_name = "Def_Events";
    answer_f.emplace_back( dataset );
    if(not sys) continue;
    for(auto ttree_name : sys_ttres){
      if( dataset->IsData() ) continue;
      if( dataset->IsBackground() ) continue;
      vseva::DataSet* new_dataset     = new vseva::DataSet( *dataset );
      new_dataset->dataset_ttree_name = ttree_name + "_Events";
      new_dataset->process_name      += "_X_" + ttree_name;
      new_dataset->latex_name         = new_dataset->latex_name + " " + ttree_name;
      new_dataset->short_name         = new_dataset->short_name + "_X_" + ttree_name;
      new_dataset->sys = true;
      answer_f.emplace_back( new_dataset );
    }
  }

  /*
  for(int i = 0; i < 13; i ++){
    string fname = "hzura_2017_EFT" + to_string(i) + "_REWEIGHT2_v3";
    auto dataset = get_dataset(fname, "EFT reweight 3 to " + to_string(i), "EFT3_" + to_string(i) + "_rw", 1., 1., "S");
    dataset->dataset_ttree_name = "Def_Events";
    answer.push_back( dataset );
    fname = "hzura_2017_EFT" + to_string(i) + "_REWEIGHT9_v3";
    auto dataset2 = get_dataset(fname, "EFT reweight 10 to "+ to_string(i), "EFT10_" + to_string(i) + "_rw", 1., 1., "S");
    dataset2->dataset_ttree_name = "Def_Events";
    answer.push_back( dataset2 );
  }
  */
  cout << "get_datasets() ... ok" << endl;
  return answer_f;
}

vector<vseva::DataSet*> get_datasets_spl(){
  vector<vseva::DataSet*> answer = get_datasets();
  for(int i = 0; i < answer.size(); ++i){
    vseva::DataSet* dataset = answer.at( i );
    dataset->dataset_ttree_name = "data";
    for(int j = 0; j < dataset->files.size(); ++j){
      dataset->files[j] = "/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/datas/H_" + dataset->process_name + "_split.root";
    }
  }
  return answer;
}




