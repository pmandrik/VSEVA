
#include "mRoot.cpp"
#include "mRootAnalyser.cpp"
#include "mRootAnalyseAlgo.cpp"
#include "mRootThread.cpp"

#include "../vseva.hh"

using namespace mRoot;

vseva::DataSet* get_dataset(string process_name, string latex_name, string short_name, double xsec, double weight_sum, string dataset_type){
  string wpath = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/";
  vseva::DataSet* answer = new vseva::DataSet(process_name, latex_name, short_name, dataset_type);
  answer->xsec   = xsec;
  answer->weight_sum = weight_sum;
  answer->dataset_ttree_name = "";

  string fpath = wpath + "/" + process_name + ".root";

  answer->AddFile( fpath );
  return answer;
}

vector<vseva::DataSet*> get_datasets(bool calc_weights = true){
/*
  vector<vseva::DataSet*> answer = {
      get_dataset("hzura_2017_data_v0",          "DATA 2017",        "data2017",             1.,            1., "D"),
      get_dataset("hzura_2017_EFT2_v1",          "EFT 2",                "EFT2",             1.,            1., "S"),
      get_dataset("hzura_2017_EFT9_v1",          "EFT 9",                "EFT9",             1.,            1., "S"),
      get_dataset("GJets_v2",                    "#gamma+jets",         "GJets",   16792*0.0514,    224817201., "B"), // [0]
      get_dataset("GGJets_v2",                   "#gamma#gamma+jets",  "GGJets",          82.79,     79243357., "B"), // After filter: final cross section = 8.279e+01 +- 1.072e-01 pb [0]
  };
*/
  vector<vseva::DataSet*> answer = {
      // DATA
      get_dataset( "hzura_2017_data_v4",          "CMS 2017",             "data2017",         1.,            1., "D" ),
      // EFT signals
      get_dataset( "hzura_2017_EFT2_v4",          "EFT 3",                "EFT3",             1.,            1., "S" ),
      get_dataset( "hzura_2017_EFT9_v4",          "EFT 10",               "EFT10",            1.,            1., "S" ),
      // ZH
      // get_dataset("hzura_2017_ggZH_HToGG_ZToLL_v3",     "ZH #rightarrow #gamma #gamma ll",        "ZH_ggll",     0.1057 * 2.28E-03 * (3.363 + 3.366 + 3.370)/100.,   300000.0, "B"), // [1]
      // get_dataset("hzura_2017_ggZH_HToGG_ZToNuNu_v3",   "ZH #rightarrow #gamma #gamma #nu #nu",   "ZH_ggnunu",   0.1057 * 2.28E-03 * (20.00)/100.                ,   300000.0, "B"), // [1]
      // get_dataset("hzura_2017_ggZH_HToGG_ZToQQ_v3",     "ZH #rightarrow #gamma #gamma qq",        "ZH_ggqq",     0.1057 * 2.28E-03 * (69.91)/100.                ,   300000.0, "B"), // [1]
      // H
      // get_dataset("hzura_2017_GluGluHToGG_v3",     "H #rightarrow #gamma #gamma",   "H",   48.58 * 1.06 * 0.00227,   219403548.0, "B"),
      //
  };
  // [0] https://twiki.cern.ch/twiki/bin/view/CMS/StopHiggsino13TeV
  // reset lumiWeight to  7.77214014881 84.4 10859.2998047 1000.0 /GJets_v2   0.00383915819319 = xsec * lumi / sumWeights => 21564623.24132803
  // reset lumiWeight to  35.9965565303 878.1 24394.0 1000.0      /GGJets_v2  0.0110810550341 878.1 79243357.0 1000.0
  
  // [1] https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt1314TeV2014
  // 0.1057 pb X 2.28E-03 X 
  // 48.58 * 1.06 * 0.00227 * 44.98 * 1000

  vector<string> sys_ttres = {"FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp",
"JERUp", "JERDown", "JECUp", "JECDown", "UnclusteredMETUp", "UnclusteredMETDown"};

  for(auto dataset : answer){
    dataset->dataset_ttree_name = "Def_Events";
    // continue;
    for(auto ttree_name : sys_ttres){
      if( dataset->IsData() ) continue;
      vseva::DataSet* new_dataset     = new vseva::DataSet( *dataset );
      new_dataset->dataset_ttree_name = ttree_name + "_Events";
      new_dataset->process_name      += "_X_" + ttree_name;
      new_dataset->latex_name         = new_dataset->latex_name + " " + ttree_name;
      new_dataset->short_name         = new_dataset->short_name + "_X_" + ttree_name;
      new_dataset->sys = true;
      answer.push_back( new_dataset );
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

  return answer;
}






