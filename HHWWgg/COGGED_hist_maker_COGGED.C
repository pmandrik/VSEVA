
#include "analyse_cfg.C"

#include "Def_Events.C"

#include "../vseva.hh"

// root -l -b -q "make_interface.C(\"/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_EFT2_v3.root\")"
// python -m cogapp.__main__ -o COGGED_hist_maker_COGGED.C hist_maker.C; root -l -b -q COGGED_hist_maker_COGGED.C

/*
python -m cogapp.__main__ -o COGGED_hist_maker_COGGED.C hist_maker.C; root -l -b -q COGGED_hist_maker_COGGED.C;
root -l -b -q hist_combainer.C; root -l -b -q hist_plotter.C;

*/

bool TMVA_DATASETS = false; 

map<string, vseva::PlotVariable> get_variables(){
  map<string, vseva::PlotVariable> custom_variables;

  /*[[[cog
    from mRootCOG import *
    from mRootCOGAnalyser import *
    from AnalyseHEPPY import *

    systematics = ["sf_photons", "sf_electrons", "sf_muons_id", "sf_muons_iso", "sf_ljets_btag", "sf_pileup", "FracRV", "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF"]
    #systematics = []
    vars_with_sys_weights  = [ "m_yy", "H_WW_tlv_M" ]
    vars_with_sys_dataset  = [ "nu_tlv_Pt", "nu_tlv_Phi", "nu_reco_tlv_Pt", "nu_reco_tlv_Phi", "nu_reco_tlv_Eta", "gen_nu_tlv_Pt", "gen_nu_tlv_Phi", "gen_nu_tlv_Eta", "W_elnu_tlv_M" ]
    vars_with_sys_dataset += [ "W_jj_tlv_M", "gen_ljet1_tlv_Pt", "ljet1_tlv_Pt", "ljet2_tlv_Pt", "H_WW_tlv_M" ]
    vars_with_sys_all = vars_with_sys_weights + vars_with_sys_dataset

    def_variables = [
        # MAIN VARS ================ ================ ================ ================ ================ ================
        PlotVariable("N_leptons",   0, 2, "Int_t"),
        PlotVariable("N_muons",     0, 2, "Int_t"),
        PlotVariable("N_electrons", 0, 2, "Int_t"),

        PlotVariable("m_yy", 100, 160, "Double_t"),
        PlotVariable("y1_Et_div_m_yy", 0, 2, "Double_t"),
        PlotVariable("y2_Et_div_m_y", 0, 2, "Double_t"),
        PlotVariable("dR_yy", 0, 5, "Double_t"),
        PlotVariable("dR_jj", 0, 5, "Double_t"),
        PlotVariable("dR_WL", 0, 5, "Double_t"),
        PlotVariable("dR_WW", 0, 5, "Double_t"),
        PlotVariable("dR_HH", 0, 5, "Double_t"),
        PlotVariable("W_elnu_tlv", 10,  200, "TLorentzVector", expr="W_elnu_tlv->M()"),
        PlotVariable("W_jj_tlv",   10,  200, "TLorentzVector", expr="W_jj_tlv->M()"  ),
        PlotVariable("H_WW_tlv",   10,  500, "TLorentzVector", expr="H_WW_tlv->M()"  ),

        PlotVariable("HH_tlv",     0,  500, "TLorentzVector", expr="HH_tlv->Pt()"   ),
        PlotVariable("HH_tlv",     0,  1,   "TLorentzVector", expr="HH_tlv->CosTheta()"),
        PlotVariable("HH_tlv",     0,  1200,   "TLorentzVector", expr="HH_tlv->M()"),

        PlotVariable("y1_tlv",     0,  300, "TLorentzVector", expr="y1_tlv->Pt()"   ),
        PlotVariable("y2_tlv",     0,  300, "TLorentzVector", expr="y2_tlv->Pt()"   ),
        PlotVariable("H_yy_tlv",   0,  500, "TLorentzVector", expr="H_yy_tlv->Pt()"   ),
        PlotVariable("H_WW_tlv",   0,  500, "TLorentzVector", expr="H_WW_tlv->Pt()"   ),
        PlotVariable("W_elnu_tlv", 0,  300, "TLorentzVector", expr="W_elnu_tlv->Pt()" ),
        PlotVariable("W_jj_tlv",   0,  300, "TLorentzVector", expr="W_jj_tlv->Pt()"   ),

        # GENRECO VARS ================ ================ ================ ================ ================ ================
        PlotVariable("gen_HHi_tlv", 0, 1200, "TLorentzVector", expr="gen_HHi_tlv->M()"),
        PlotVariable("gen_Hi_yy_tlv", 0,  1, "TLorentzVector", expr="gen_Hi_yy_tlv->CosTheta()"),
        PlotVariable("dR_genreco_W_jj"        , 0,   5, "Double_t"),
        PlotVariable("dR_genreco_W_jj_leading", 0,   5, "Double_t"),
        PlotVariable("dP_genreco_W_jj"        , 0, 600, "Double_t"),
        PlotVariable("dP_genreco_W_jj_leading", 0, 600, "Double_t"),
        PlotVariable("W_jj_tlv_leading",       10, 200, "TLorentzVector", expr="W_jj_tlv_leading->M()" ),
        PlotVariable("dR_genreco_H_yy", 0,     2, "Double_t"),
        PlotVariable("dR_genreco_H_WW", 0,     5, "Double_t"),
        PlotVariable("dR_genreco_nu", 0,       5, "Double_t"),
        PlotVariable("dR_genreco_W_elnu", 0,   5, "Double_t"),
        PlotVariable("dP_genreco_H_yy", 0,     100, "Double_t"),
        PlotVariable("dP_genreco_H_WW", 0,     400, "Double_t"),
        PlotVariable("dP_genreco_nu", 0,       400, "Double_t"),
        PlotVariable("dP_genreco_W_elnu", 0,   400, "Double_t"),
        PlotVariable("gen_dR_jj", 0,   5, "Double_t"),
        PlotVariable("dR_jj_leading", 0,   5, "Double_t"),
        PlotVariable("gen_W_jj_tlv", 10, 200, "TLorentzVector", expr="gen_W_jj_tlv->M()" ),

        # XY-CORR ================ ================ ================ ================ ================ ================
        PlotVariable("nu_tlv",            0,      300,  "TLorentzVector", expr="nu_tlv->Pt()" ),
        PlotVariable("nu_tlv",          -3.14,   3.14,  "TLorentzVector", expr="nu_tlv->Phi()" ),
        PlotVariable("nu_reco_tlv",       0,      300,  "TLorentzVector", expr="nu_reco_tlv->Pt()" ),
        PlotVariable("nu_reco_tlv",     -3.14,   3.14,  "TLorentzVector", expr="nu_reco_tlv->Phi()" ),
        PlotVariable("nu_reco_tlv",         -5,   5,  "TLorentzVector", expr="nu_reco_tlv->Eta()" ),
        PlotVariable("gen_nu_tlv",        0,      300,  "TLorentzVector", expr="gen_nu_tlv->Pt()" ),
        PlotVariable("gen_nu_tlv",      -3.14,   3.14,  "TLorentzVector", expr="gen_nu_tlv->Phi()" ),
        PlotVariable("gen_nu_tlv",          -5,   5,  "TLorentzVector", expr="gen_nu_tlv->Eta()" ),

        # PUJID ================ ================ ================ ================ ================ ================
        PlotVariable("gen_ljet1_tlv",            0,      500,  "TLorentzVector", expr="gen_ljet1_tlv->Pt()" ),
        PlotVariable("ljet1_tlv",                0,      500,  "TLorentzVector", expr="ljet1_tlv->Pt()" ),
        PlotVariable("ljet2_tlv",                0,      500,  "TLorentzVector", expr="ljet2_tlv->Pt()" ),

        # BDTs ================ ================ ================ ================ ================ ================
        # PlotVariable("weight_BDT_3b_001",        -1,       1, "Double_t" ),
    ]

    variables = def_variables

    for var in variables:
      if var.type == "TLorentzVector":
        pfix = var.exp.split("->")[1]
        pfix = pfix.replace("()", "")
        var.bname = var.key
        var.key  += "_" + pfix

    import copy
    for var in variables[:]:
      var.xfactor = "weight"
      var.sys_factors = []
      var.sys_hist_names = []
      if var.key in vars_with_sys_weights : var.sys_factors = systematics
    
    #for var in variables:
    #  cog.outl( 'custom_variables["' + var.key + '"] = vseva::PlotVariable("' + var.key + '", ' + str(var.xmin) + ', ' + str(var.xmax) +');')
  ]]]*/
  //[[[end]]]

  return custom_variables;
};

int plot_from_file(vseva::DataSet * dataset, string input_file, string output_file_name){
  cout << input_file << " Step 0." <<  endl;
  TFile * output_file = TFile::Open(output_file_name.c_str(), "RECREATE");

  /*[[[cog
    for var in variables :
      if var.frozen : continue
      name = "(dataset->process_name + \"" + "_" + var.key + "_" + var.xfactor + "\").c_str()"
      title = "\"" + var.key + "_" + var.xfactor + "\""
      var.hist_name = cpp_TH1(name, title, var.nbins, var.xmin, var.xmax, type="D")

      if var.key not in vars_with_sys_dataset :
        cog.outl( "if( dataset->sys ) " + var.hist_name + ".SetDirectory(0);" )

      for sys in var.sys_factors:
        if var.key not in vars_with_sys_weights : continue
        for sysfactor in ["weight_" + sys + "_up", "weight_" + sys + "_down"]:
          name = "(dataset->process_name + \"" + "_" + var.key + "_" + sysfactor + "\").c_str()"
          title = "\"" + var.key + "_" + sysfactor + "\""
          var.sys_hist_names += [ cpp_TH1(name, title, var.nbins, var.xmin, var.xmax, type="D") ]
          cog.outl( "if( dataset->sys ) " + var.sys_hist_names[-1] + ".SetDirectory(0);" )
  ]]]*/
  TH1D hist_0 = TH1D((dataset->process_name + "_N_leptons_weight").c_str(), "N_leptons_weight", 20, 0, 2);
  if( dataset->sys ) hist_0.SetDirectory(0);
  TH1D hist_1 = TH1D((dataset->process_name + "_N_muons_weight").c_str(), "N_muons_weight", 20, 0, 2);
  if( dataset->sys ) hist_1.SetDirectory(0);
  TH1D hist_2 = TH1D((dataset->process_name + "_N_electrons_weight").c_str(), "N_electrons_weight", 20, 0, 2);
  if( dataset->sys ) hist_2.SetDirectory(0);
  TH1D hist_3 = TH1D((dataset->process_name + "_m_yy_weight").c_str(), "m_yy_weight", 20, 100, 160);
  if( dataset->sys ) hist_3.SetDirectory(0);
  TH1D hist_4 = TH1D((dataset->process_name + "_m_yy_weight_sf_photons_up").c_str(), "m_yy_weight_sf_photons_up", 20, 100, 160);
  if( dataset->sys ) hist_4.SetDirectory(0);
  TH1D hist_5 = TH1D((dataset->process_name + "_m_yy_weight_sf_photons_down").c_str(), "m_yy_weight_sf_photons_down", 20, 100, 160);
  if( dataset->sys ) hist_5.SetDirectory(0);
  TH1D hist_6 = TH1D((dataset->process_name + "_m_yy_weight_sf_electrons_up").c_str(), "m_yy_weight_sf_electrons_up", 20, 100, 160);
  if( dataset->sys ) hist_6.SetDirectory(0);
  TH1D hist_7 = TH1D((dataset->process_name + "_m_yy_weight_sf_electrons_down").c_str(), "m_yy_weight_sf_electrons_down", 20, 100, 160);
  if( dataset->sys ) hist_7.SetDirectory(0);
  TH1D hist_8 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_id_up").c_str(), "m_yy_weight_sf_muons_id_up", 20, 100, 160);
  if( dataset->sys ) hist_8.SetDirectory(0);
  TH1D hist_9 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_id_down").c_str(), "m_yy_weight_sf_muons_id_down", 20, 100, 160);
  if( dataset->sys ) hist_9.SetDirectory(0);
  TH1D hist_10 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_iso_up").c_str(), "m_yy_weight_sf_muons_iso_up", 20, 100, 160);
  if( dataset->sys ) hist_10.SetDirectory(0);
  TH1D hist_11 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_iso_down").c_str(), "m_yy_weight_sf_muons_iso_down", 20, 100, 160);
  if( dataset->sys ) hist_11.SetDirectory(0);
  TH1D hist_12 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_btag_up").c_str(), "m_yy_weight_sf_ljets_btag_up", 20, 100, 160);
  if( dataset->sys ) hist_12.SetDirectory(0);
  TH1D hist_13 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_btag_down").c_str(), "m_yy_weight_sf_ljets_btag_down", 20, 100, 160);
  if( dataset->sys ) hist_13.SetDirectory(0);
  TH1D hist_14 = TH1D((dataset->process_name + "_m_yy_weight_sf_pileup_up").c_str(), "m_yy_weight_sf_pileup_up", 20, 100, 160);
  if( dataset->sys ) hist_14.SetDirectory(0);
  TH1D hist_15 = TH1D((dataset->process_name + "_m_yy_weight_sf_pileup_down").c_str(), "m_yy_weight_sf_pileup_down", 20, 100, 160);
  if( dataset->sys ) hist_15.SetDirectory(0);
  TH1D hist_16 = TH1D((dataset->process_name + "_m_yy_weight_FracRV_up").c_str(), "m_yy_weight_FracRV_up", 20, 100, 160);
  if( dataset->sys ) hist_16.SetDirectory(0);
  TH1D hist_17 = TH1D((dataset->process_name + "_m_yy_weight_FracRV_down").c_str(), "m_yy_weight_FracRV_down", 20, 100, 160);
  if( dataset->sys ) hist_17.SetDirectory(0);
  TH1D hist_18 = TH1D((dataset->process_name + "_m_yy_weight_LooseMvaSF_up").c_str(), "m_yy_weight_LooseMvaSF_up", 20, 100, 160);
  if( dataset->sys ) hist_18.SetDirectory(0);
  TH1D hist_19 = TH1D((dataset->process_name + "_m_yy_weight_LooseMvaSF_down").c_str(), "m_yy_weight_LooseMvaSF_down", 20, 100, 160);
  if( dataset->sys ) hist_19.SetDirectory(0);
  TH1D hist_20 = TH1D((dataset->process_name + "_m_yy_weight_PreselSF_up").c_str(), "m_yy_weight_PreselSF_up", 20, 100, 160);
  if( dataset->sys ) hist_20.SetDirectory(0);
  TH1D hist_21 = TH1D((dataset->process_name + "_m_yy_weight_PreselSF_down").c_str(), "m_yy_weight_PreselSF_down", 20, 100, 160);
  if( dataset->sys ) hist_21.SetDirectory(0);
  TH1D hist_22 = TH1D((dataset->process_name + "_m_yy_weight_Trigger_up").c_str(), "m_yy_weight_Trigger_up", 20, 100, 160);
  if( dataset->sys ) hist_22.SetDirectory(0);
  TH1D hist_23 = TH1D((dataset->process_name + "_m_yy_weight_Trigger_down").c_str(), "m_yy_weight_Trigger_down", 20, 100, 160);
  if( dataset->sys ) hist_23.SetDirectory(0);
  TH1D hist_24 = TH1D((dataset->process_name + "_m_yy_weight_electronVetoSF_up").c_str(), "m_yy_weight_electronVetoSF_up", 20, 100, 160);
  if( dataset->sys ) hist_24.SetDirectory(0);
  TH1D hist_25 = TH1D((dataset->process_name + "_m_yy_weight_electronVetoSF_down").c_str(), "m_yy_weight_electronVetoSF_down", 20, 100, 160);
  if( dataset->sys ) hist_25.SetDirectory(0);
  TH1D hist_26 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight").c_str(), "y1_Et_div_m_yy_weight", 20, 0, 2);
  if( dataset->sys ) hist_26.SetDirectory(0);
  TH1D hist_27 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight").c_str(), "y2_Et_div_m_y_weight", 20, 0, 2);
  if( dataset->sys ) hist_27.SetDirectory(0);
  TH1D hist_28 = TH1D((dataset->process_name + "_dR_yy_weight").c_str(), "dR_yy_weight", 20, 0, 5);
  if( dataset->sys ) hist_28.SetDirectory(0);
  TH1D hist_29 = TH1D((dataset->process_name + "_dR_jj_weight").c_str(), "dR_jj_weight", 20, 0, 5);
  if( dataset->sys ) hist_29.SetDirectory(0);
  TH1D hist_30 = TH1D((dataset->process_name + "_dR_WL_weight").c_str(), "dR_WL_weight", 20, 0, 5);
  if( dataset->sys ) hist_30.SetDirectory(0);
  TH1D hist_31 = TH1D((dataset->process_name + "_dR_WW_weight").c_str(), "dR_WW_weight", 20, 0, 5);
  if( dataset->sys ) hist_31.SetDirectory(0);
  TH1D hist_32 = TH1D((dataset->process_name + "_dR_HH_weight").c_str(), "dR_HH_weight", 20, 0, 5);
  if( dataset->sys ) hist_32.SetDirectory(0);
  TH1D hist_33 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight").c_str(), "W_elnu_tlv_M_weight", 20, 10, 200);
  TH1D hist_34 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight").c_str(), "W_jj_tlv_M_weight", 20, 10, 200);
  TH1D hist_35 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight").c_str(), "H_WW_tlv_M_weight", 20, 10, 500);
  TH1D hist_36 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_photons_up").c_str(), "H_WW_tlv_M_weight_sf_photons_up", 20, 10, 500);
  if( dataset->sys ) hist_36.SetDirectory(0);
  TH1D hist_37 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_photons_down").c_str(), "H_WW_tlv_M_weight_sf_photons_down", 20, 10, 500);
  if( dataset->sys ) hist_37.SetDirectory(0);
  TH1D hist_38 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_electrons_up").c_str(), "H_WW_tlv_M_weight_sf_electrons_up", 20, 10, 500);
  if( dataset->sys ) hist_38.SetDirectory(0);
  TH1D hist_39 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_electrons_down").c_str(), "H_WW_tlv_M_weight_sf_electrons_down", 20, 10, 500);
  if( dataset->sys ) hist_39.SetDirectory(0);
  TH1D hist_40 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_id_up").c_str(), "H_WW_tlv_M_weight_sf_muons_id_up", 20, 10, 500);
  if( dataset->sys ) hist_40.SetDirectory(0);
  TH1D hist_41 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_id_down").c_str(), "H_WW_tlv_M_weight_sf_muons_id_down", 20, 10, 500);
  if( dataset->sys ) hist_41.SetDirectory(0);
  TH1D hist_42 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_iso_up").c_str(), "H_WW_tlv_M_weight_sf_muons_iso_up", 20, 10, 500);
  if( dataset->sys ) hist_42.SetDirectory(0);
  TH1D hist_43 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_iso_down").c_str(), "H_WW_tlv_M_weight_sf_muons_iso_down", 20, 10, 500);
  if( dataset->sys ) hist_43.SetDirectory(0);
  TH1D hist_44 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_btag_up").c_str(), "H_WW_tlv_M_weight_sf_ljets_btag_up", 20, 10, 500);
  if( dataset->sys ) hist_44.SetDirectory(0);
  TH1D hist_45 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_btag_down").c_str(), "H_WW_tlv_M_weight_sf_ljets_btag_down", 20, 10, 500);
  if( dataset->sys ) hist_45.SetDirectory(0);
  TH1D hist_46 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_pileup_up").c_str(), "H_WW_tlv_M_weight_sf_pileup_up", 20, 10, 500);
  if( dataset->sys ) hist_46.SetDirectory(0);
  TH1D hist_47 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_pileup_down").c_str(), "H_WW_tlv_M_weight_sf_pileup_down", 20, 10, 500);
  if( dataset->sys ) hist_47.SetDirectory(0);
  TH1D hist_48 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_FracRV_up").c_str(), "H_WW_tlv_M_weight_FracRV_up", 20, 10, 500);
  if( dataset->sys ) hist_48.SetDirectory(0);
  TH1D hist_49 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_FracRV_down").c_str(), "H_WW_tlv_M_weight_FracRV_down", 20, 10, 500);
  if( dataset->sys ) hist_49.SetDirectory(0);
  TH1D hist_50 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_LooseMvaSF_up").c_str(), "H_WW_tlv_M_weight_LooseMvaSF_up", 20, 10, 500);
  if( dataset->sys ) hist_50.SetDirectory(0);
  TH1D hist_51 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_LooseMvaSF_down").c_str(), "H_WW_tlv_M_weight_LooseMvaSF_down", 20, 10, 500);
  if( dataset->sys ) hist_51.SetDirectory(0);
  TH1D hist_52 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_PreselSF_up").c_str(), "H_WW_tlv_M_weight_PreselSF_up", 20, 10, 500);
  if( dataset->sys ) hist_52.SetDirectory(0);
  TH1D hist_53 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_PreselSF_down").c_str(), "H_WW_tlv_M_weight_PreselSF_down", 20, 10, 500);
  if( dataset->sys ) hist_53.SetDirectory(0);
  TH1D hist_54 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_Trigger_up").c_str(), "H_WW_tlv_M_weight_Trigger_up", 20, 10, 500);
  if( dataset->sys ) hist_54.SetDirectory(0);
  TH1D hist_55 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_Trigger_down").c_str(), "H_WW_tlv_M_weight_Trigger_down", 20, 10, 500);
  if( dataset->sys ) hist_55.SetDirectory(0);
  TH1D hist_56 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_electronVetoSF_up").c_str(), "H_WW_tlv_M_weight_electronVetoSF_up", 20, 10, 500);
  if( dataset->sys ) hist_56.SetDirectory(0);
  TH1D hist_57 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_electronVetoSF_down").c_str(), "H_WW_tlv_M_weight_electronVetoSF_down", 20, 10, 500);
  if( dataset->sys ) hist_57.SetDirectory(0);
  TH1D hist_58 = TH1D((dataset->process_name + "_HH_tlv_Pt_weight").c_str(), "HH_tlv_Pt_weight", 20, 0, 500);
  if( dataset->sys ) hist_58.SetDirectory(0);
  TH1D hist_59 = TH1D((dataset->process_name + "_HH_tlv_CosTheta_weight").c_str(), "HH_tlv_CosTheta_weight", 20, 0, 1);
  if( dataset->sys ) hist_59.SetDirectory(0);
  TH1D hist_60 = TH1D((dataset->process_name + "_HH_tlv_M_weight").c_str(), "HH_tlv_M_weight", 20, 0, 1200);
  if( dataset->sys ) hist_60.SetDirectory(0);
  TH1D hist_61 = TH1D((dataset->process_name + "_y1_tlv_Pt_weight").c_str(), "y1_tlv_Pt_weight", 20, 0, 300);
  if( dataset->sys ) hist_61.SetDirectory(0);
  TH1D hist_62 = TH1D((dataset->process_name + "_y2_tlv_Pt_weight").c_str(), "y2_tlv_Pt_weight", 20, 0, 300);
  if( dataset->sys ) hist_62.SetDirectory(0);
  TH1D hist_63 = TH1D((dataset->process_name + "_H_yy_tlv_Pt_weight").c_str(), "H_yy_tlv_Pt_weight", 20, 0, 500);
  if( dataset->sys ) hist_63.SetDirectory(0);
  TH1D hist_64 = TH1D((dataset->process_name + "_H_WW_tlv_Pt_weight").c_str(), "H_WW_tlv_Pt_weight", 20, 0, 500);
  if( dataset->sys ) hist_64.SetDirectory(0);
  TH1D hist_65 = TH1D((dataset->process_name + "_W_elnu_tlv_Pt_weight").c_str(), "W_elnu_tlv_Pt_weight", 20, 0, 300);
  if( dataset->sys ) hist_65.SetDirectory(0);
  TH1D hist_66 = TH1D((dataset->process_name + "_W_jj_tlv_Pt_weight").c_str(), "W_jj_tlv_Pt_weight", 20, 0, 300);
  if( dataset->sys ) hist_66.SetDirectory(0);
  TH1D hist_67 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight").c_str(), "gen_HHi_tlv_M_weight", 20, 0, 1200);
  if( dataset->sys ) hist_67.SetDirectory(0);
  TH1D hist_68 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight").c_str(), "gen_Hi_yy_tlv_CosTheta_weight", 20, 0, 1);
  if( dataset->sys ) hist_68.SetDirectory(0);
  TH1D hist_69 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight").c_str(), "dR_genreco_W_jj_weight", 20, 0, 5);
  if( dataset->sys ) hist_69.SetDirectory(0);
  TH1D hist_70 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight").c_str(), "dR_genreco_W_jj_leading_weight", 20, 0, 5);
  if( dataset->sys ) hist_70.SetDirectory(0);
  TH1D hist_71 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight").c_str(), "dP_genreco_W_jj_weight", 20, 0, 600);
  if( dataset->sys ) hist_71.SetDirectory(0);
  TH1D hist_72 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight").c_str(), "dP_genreco_W_jj_leading_weight", 20, 0, 600);
  if( dataset->sys ) hist_72.SetDirectory(0);
  TH1D hist_73 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight").c_str(), "W_jj_tlv_leading_M_weight", 20, 10, 200);
  if( dataset->sys ) hist_73.SetDirectory(0);
  TH1D hist_74 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight").c_str(), "dR_genreco_H_yy_weight", 20, 0, 2);
  if( dataset->sys ) hist_74.SetDirectory(0);
  TH1D hist_75 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight").c_str(), "dR_genreco_H_WW_weight", 20, 0, 5);
  if( dataset->sys ) hist_75.SetDirectory(0);
  TH1D hist_76 = TH1D((dataset->process_name + "_dR_genreco_nu_weight").c_str(), "dR_genreco_nu_weight", 20, 0, 5);
  if( dataset->sys ) hist_76.SetDirectory(0);
  TH1D hist_77 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight").c_str(), "dR_genreco_W_elnu_weight", 20, 0, 5);
  if( dataset->sys ) hist_77.SetDirectory(0);
  TH1D hist_78 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight").c_str(), "dP_genreco_H_yy_weight", 20, 0, 100);
  if( dataset->sys ) hist_78.SetDirectory(0);
  TH1D hist_79 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight").c_str(), "dP_genreco_H_WW_weight", 20, 0, 400);
  if( dataset->sys ) hist_79.SetDirectory(0);
  TH1D hist_80 = TH1D((dataset->process_name + "_dP_genreco_nu_weight").c_str(), "dP_genreco_nu_weight", 20, 0, 400);
  if( dataset->sys ) hist_80.SetDirectory(0);
  TH1D hist_81 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight").c_str(), "dP_genreco_W_elnu_weight", 20, 0, 400);
  if( dataset->sys ) hist_81.SetDirectory(0);
  TH1D hist_82 = TH1D((dataset->process_name + "_gen_dR_jj_weight").c_str(), "gen_dR_jj_weight", 20, 0, 5);
  if( dataset->sys ) hist_82.SetDirectory(0);
  TH1D hist_83 = TH1D((dataset->process_name + "_dR_jj_leading_weight").c_str(), "dR_jj_leading_weight", 20, 0, 5);
  if( dataset->sys ) hist_83.SetDirectory(0);
  TH1D hist_84 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight").c_str(), "gen_W_jj_tlv_M_weight", 20, 10, 200);
  if( dataset->sys ) hist_84.SetDirectory(0);
  TH1D hist_85 = TH1D((dataset->process_name + "_nu_tlv_Pt_weight").c_str(), "nu_tlv_Pt_weight", 20, 0, 300);
  TH1D hist_86 = TH1D((dataset->process_name + "_nu_tlv_Phi_weight").c_str(), "nu_tlv_Phi_weight", 20, -3.14, 3.14);
  TH1D hist_87 = TH1D((dataset->process_name + "_nu_reco_tlv_Pt_weight").c_str(), "nu_reco_tlv_Pt_weight", 20, 0, 300);
  TH1D hist_88 = TH1D((dataset->process_name + "_nu_reco_tlv_Phi_weight").c_str(), "nu_reco_tlv_Phi_weight", 20, -3.14, 3.14);
  TH1D hist_89 = TH1D((dataset->process_name + "_nu_reco_tlv_Eta_weight").c_str(), "nu_reco_tlv_Eta_weight", 20, -5, 5);
  TH1D hist_90 = TH1D((dataset->process_name + "_gen_nu_tlv_Pt_weight").c_str(), "gen_nu_tlv_Pt_weight", 20, 0, 300);
  TH1D hist_91 = TH1D((dataset->process_name + "_gen_nu_tlv_Phi_weight").c_str(), "gen_nu_tlv_Phi_weight", 20, -3.14, 3.14);
  TH1D hist_92 = TH1D((dataset->process_name + "_gen_nu_tlv_Eta_weight").c_str(), "gen_nu_tlv_Eta_weight", 20, -5, 5);
  TH1D hist_93 = TH1D((dataset->process_name + "_gen_ljet1_tlv_Pt_weight").c_str(), "gen_ljet1_tlv_Pt_weight", 20, 0, 500);
  TH1D hist_94 = TH1D((dataset->process_name + "_ljet1_tlv_Pt_weight").c_str(), "ljet1_tlv_Pt_weight", 20, 0, 500);
  TH1D hist_95 = TH1D((dataset->process_name + "_ljet2_tlv_Pt_weight").c_str(), "ljet2_tlv_Pt_weight", 20, 0, 500);
  //[[[end]]]

  cout << input_file << " Step I." <<  endl;
  TFile * file = TFile::Open(input_file.c_str(), "READ");
  TTree * tree = (TTree*) gDirectory->Get( dataset->dataset_ttree_name.c_str() );
  cout << "tree = " << tree << " " << input_file.c_str() << " " << dataset->dataset_ttree_name.c_str() << endl;

  if(not tree){
    cout << "\n====\nERROR ====================== tree = " << tree << " " << input_file.c_str() << " " << dataset->dataset_ttree_name.c_str() << "\n====\n" << endl;
  }

    /*[[[cog
      processed_branches = []
      for var in variables :
        if var.frozen : continue

        bname = var.bname
        if not bname : bname = var.key
        vname = bname
        if vname in processed_branches : continue
        processed_branches += [ bname ]

        if var.type in ["Double_t", "Float_t", "Int_t"]:
          cog.outl( var.type + " " + bname + ";" )
        else : 
          cog.outl( var.type + " * " + bname + ";" )

        cog.outl( "if( tree->GetBranch( \"" + bname + "\") ){" )
        if var.key not in vars_with_sys_dataset : 
          cog.outl( "if( not dataset->sys )" )
        cog.outl( "tree->SetBranchAddress( \"" + bname + "\", &" + bname + ");" )    
        cog.outl("} else cout << \"DontHave a branch with name = " + bname + "\" << endl;" )
    ]]]*/
    Int_t N_leptons;
    if( tree->GetBranch( "N_leptons") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "N_leptons", &N_leptons);
    } else cout << "DontHave a branch with name = N_leptons" << endl;
    Int_t N_muons;
    if( tree->GetBranch( "N_muons") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "N_muons", &N_muons);
    } else cout << "DontHave a branch with name = N_muons" << endl;
    Int_t N_electrons;
    if( tree->GetBranch( "N_electrons") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "N_electrons", &N_electrons);
    } else cout << "DontHave a branch with name = N_electrons" << endl;
    Double_t m_yy;
    if( tree->GetBranch( "m_yy") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "m_yy", &m_yy);
    } else cout << "DontHave a branch with name = m_yy" << endl;
    Double_t y1_Et_div_m_yy;
    if( tree->GetBranch( "y1_Et_div_m_yy") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "y1_Et_div_m_yy", &y1_Et_div_m_yy);
    } else cout << "DontHave a branch with name = y1_Et_div_m_yy" << endl;
    Double_t y2_Et_div_m_y;
    if( tree->GetBranch( "y2_Et_div_m_y") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "y2_Et_div_m_y", &y2_Et_div_m_y);
    } else cout << "DontHave a branch with name = y2_Et_div_m_y" << endl;
    Double_t dR_yy;
    if( tree->GetBranch( "dR_yy") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_yy", &dR_yy);
    } else cout << "DontHave a branch with name = dR_yy" << endl;
    Double_t dR_jj;
    if( tree->GetBranch( "dR_jj") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_jj", &dR_jj);
    } else cout << "DontHave a branch with name = dR_jj" << endl;
    Double_t dR_WL;
    if( tree->GetBranch( "dR_WL") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_WL", &dR_WL);
    } else cout << "DontHave a branch with name = dR_WL" << endl;
    Double_t dR_WW;
    if( tree->GetBranch( "dR_WW") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_WW", &dR_WW);
    } else cout << "DontHave a branch with name = dR_WW" << endl;
    Double_t dR_HH;
    if( tree->GetBranch( "dR_HH") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_HH", &dR_HH);
    } else cout << "DontHave a branch with name = dR_HH" << endl;
    TLorentzVector * W_elnu_tlv;
    if( tree->GetBranch( "W_elnu_tlv") ){
    tree->SetBranchAddress( "W_elnu_tlv", &W_elnu_tlv);
    } else cout << "DontHave a branch with name = W_elnu_tlv" << endl;
    TLorentzVector * W_jj_tlv;
    if( tree->GetBranch( "W_jj_tlv") ){
    tree->SetBranchAddress( "W_jj_tlv", &W_jj_tlv);
    } else cout << "DontHave a branch with name = W_jj_tlv" << endl;
    TLorentzVector * H_WW_tlv;
    if( tree->GetBranch( "H_WW_tlv") ){
    tree->SetBranchAddress( "H_WW_tlv", &H_WW_tlv);
    } else cout << "DontHave a branch with name = H_WW_tlv" << endl;
    TLorentzVector * HH_tlv;
    if( tree->GetBranch( "HH_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "HH_tlv", &HH_tlv);
    } else cout << "DontHave a branch with name = HH_tlv" << endl;
    TLorentzVector * y1_tlv;
    if( tree->GetBranch( "y1_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "y1_tlv", &y1_tlv);
    } else cout << "DontHave a branch with name = y1_tlv" << endl;
    TLorentzVector * y2_tlv;
    if( tree->GetBranch( "y2_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "y2_tlv", &y2_tlv);
    } else cout << "DontHave a branch with name = y2_tlv" << endl;
    TLorentzVector * H_yy_tlv;
    if( tree->GetBranch( "H_yy_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "H_yy_tlv", &H_yy_tlv);
    } else cout << "DontHave a branch with name = H_yy_tlv" << endl;
    TLorentzVector * gen_HHi_tlv;
    if( tree->GetBranch( "gen_HHi_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "gen_HHi_tlv", &gen_HHi_tlv);
    } else cout << "DontHave a branch with name = gen_HHi_tlv" << endl;
    TLorentzVector * gen_Hi_yy_tlv;
    if( tree->GetBranch( "gen_Hi_yy_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "gen_Hi_yy_tlv", &gen_Hi_yy_tlv);
    } else cout << "DontHave a branch with name = gen_Hi_yy_tlv" << endl;
    Double_t dR_genreco_W_jj;
    if( tree->GetBranch( "dR_genreco_W_jj") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_W_jj", &dR_genreco_W_jj);
    } else cout << "DontHave a branch with name = dR_genreco_W_jj" << endl;
    Double_t dR_genreco_W_jj_leading;
    if( tree->GetBranch( "dR_genreco_W_jj_leading") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_W_jj_leading", &dR_genreco_W_jj_leading);
    } else cout << "DontHave a branch with name = dR_genreco_W_jj_leading" << endl;
    Double_t dP_genreco_W_jj;
    if( tree->GetBranch( "dP_genreco_W_jj") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_W_jj", &dP_genreco_W_jj);
    } else cout << "DontHave a branch with name = dP_genreco_W_jj" << endl;
    Double_t dP_genreco_W_jj_leading;
    if( tree->GetBranch( "dP_genreco_W_jj_leading") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_W_jj_leading", &dP_genreco_W_jj_leading);
    } else cout << "DontHave a branch with name = dP_genreco_W_jj_leading" << endl;
    TLorentzVector * W_jj_tlv_leading;
    if( tree->GetBranch( "W_jj_tlv_leading") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "W_jj_tlv_leading", &W_jj_tlv_leading);
    } else cout << "DontHave a branch with name = W_jj_tlv_leading" << endl;
    Double_t dR_genreco_H_yy;
    if( tree->GetBranch( "dR_genreco_H_yy") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_H_yy", &dR_genreco_H_yy);
    } else cout << "DontHave a branch with name = dR_genreco_H_yy" << endl;
    Double_t dR_genreco_H_WW;
    if( tree->GetBranch( "dR_genreco_H_WW") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_H_WW", &dR_genreco_H_WW);
    } else cout << "DontHave a branch with name = dR_genreco_H_WW" << endl;
    Double_t dR_genreco_nu;
    if( tree->GetBranch( "dR_genreco_nu") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_nu", &dR_genreco_nu);
    } else cout << "DontHave a branch with name = dR_genreco_nu" << endl;
    Double_t dR_genreco_W_elnu;
    if( tree->GetBranch( "dR_genreco_W_elnu") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_genreco_W_elnu", &dR_genreco_W_elnu);
    } else cout << "DontHave a branch with name = dR_genreco_W_elnu" << endl;
    Double_t dP_genreco_H_yy;
    if( tree->GetBranch( "dP_genreco_H_yy") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_H_yy", &dP_genreco_H_yy);
    } else cout << "DontHave a branch with name = dP_genreco_H_yy" << endl;
    Double_t dP_genreco_H_WW;
    if( tree->GetBranch( "dP_genreco_H_WW") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_H_WW", &dP_genreco_H_WW);
    } else cout << "DontHave a branch with name = dP_genreco_H_WW" << endl;
    Double_t dP_genreco_nu;
    if( tree->GetBranch( "dP_genreco_nu") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_nu", &dP_genreco_nu);
    } else cout << "DontHave a branch with name = dP_genreco_nu" << endl;
    Double_t dP_genreco_W_elnu;
    if( tree->GetBranch( "dP_genreco_W_elnu") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dP_genreco_W_elnu", &dP_genreco_W_elnu);
    } else cout << "DontHave a branch with name = dP_genreco_W_elnu" << endl;
    Double_t gen_dR_jj;
    if( tree->GetBranch( "gen_dR_jj") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "gen_dR_jj", &gen_dR_jj);
    } else cout << "DontHave a branch with name = gen_dR_jj" << endl;
    Double_t dR_jj_leading;
    if( tree->GetBranch( "dR_jj_leading") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "dR_jj_leading", &dR_jj_leading);
    } else cout << "DontHave a branch with name = dR_jj_leading" << endl;
    TLorentzVector * gen_W_jj_tlv;
    if( tree->GetBranch( "gen_W_jj_tlv") ){
    if( not dataset->sys )
    tree->SetBranchAddress( "gen_W_jj_tlv", &gen_W_jj_tlv);
    } else cout << "DontHave a branch with name = gen_W_jj_tlv" << endl;
    TLorentzVector * nu_tlv;
    if( tree->GetBranch( "nu_tlv") ){
    tree->SetBranchAddress( "nu_tlv", &nu_tlv);
    } else cout << "DontHave a branch with name = nu_tlv" << endl;
    TLorentzVector * nu_reco_tlv;
    if( tree->GetBranch( "nu_reco_tlv") ){
    tree->SetBranchAddress( "nu_reco_tlv", &nu_reco_tlv);
    } else cout << "DontHave a branch with name = nu_reco_tlv" << endl;
    TLorentzVector * gen_nu_tlv;
    if( tree->GetBranch( "gen_nu_tlv") ){
    tree->SetBranchAddress( "gen_nu_tlv", &gen_nu_tlv);
    } else cout << "DontHave a branch with name = gen_nu_tlv" << endl;
    TLorentzVector * gen_ljet1_tlv;
    if( tree->GetBranch( "gen_ljet1_tlv") ){
    tree->SetBranchAddress( "gen_ljet1_tlv", &gen_ljet1_tlv);
    } else cout << "DontHave a branch with name = gen_ljet1_tlv" << endl;
    TLorentzVector * ljet1_tlv;
    if( tree->GetBranch( "ljet1_tlv") ){
    tree->SetBranchAddress( "ljet1_tlv", &ljet1_tlv);
    } else cout << "DontHave a branch with name = ljet1_tlv" << endl;
    TLorentzVector * ljet2_tlv;
    if( tree->GetBranch( "ljet2_tlv") ){
    tree->SetBranchAddress( "ljet2_tlv", &ljet2_tlv);
    } else cout << "DontHave a branch with name = ljet2_tlv" << endl;
    //[[[end]]]

  // reweight due to train
  int nevents = tree->GetEntries();
  cout << "step II." <<  endl;
  
  double lumi_2017 = 44.98 * 1000; // pb-1
  double flashgg_targetLumi = 1000.0;

  Double_t weight_EFT = 1, weight = 1, mc_weight = 1;
  bool print_weights = false;
  if( tree->GetBranch("weight_EFT") ){
    print_weights = true;
    tree->SetBranchAddress("weight_EFT", &weight_EFT);
  }
  tree->SetBranchAddress("weight", &weight);
  tree->SetBranchAddress("mc_weight", &mc_weight);


  /*[[[cog
    for sys in systematics :
      for name in ["weight_" + sys + "_up", "weight_" + sys + "_down"]:
        cog.outl( "Double_t " + name + "   = 1;" )
        cog.outl( "if( tree->GetBranch( \"" + name + "\") ){" )
        cog.outl( "tree->SetBranchAddress(\"" + name + "\", &" + name + ");" )
        cog.outl("} else cout << \"DontHave a branch with name = " + name + "\" << endl;" )
  ]]]*/
  Double_t weight_sf_photons_up   = 1;
  if( tree->GetBranch( "weight_sf_photons_up") ){
  tree->SetBranchAddress("weight_sf_photons_up", &weight_sf_photons_up);
  } else cout << "DontHave a branch with name = weight_sf_photons_up" << endl;
  Double_t weight_sf_photons_down   = 1;
  if( tree->GetBranch( "weight_sf_photons_down") ){
  tree->SetBranchAddress("weight_sf_photons_down", &weight_sf_photons_down);
  } else cout << "DontHave a branch with name = weight_sf_photons_down" << endl;
  Double_t weight_sf_electrons_up   = 1;
  if( tree->GetBranch( "weight_sf_electrons_up") ){
  tree->SetBranchAddress("weight_sf_electrons_up", &weight_sf_electrons_up);
  } else cout << "DontHave a branch with name = weight_sf_electrons_up" << endl;
  Double_t weight_sf_electrons_down   = 1;
  if( tree->GetBranch( "weight_sf_electrons_down") ){
  tree->SetBranchAddress("weight_sf_electrons_down", &weight_sf_electrons_down);
  } else cout << "DontHave a branch with name = weight_sf_electrons_down" << endl;
  Double_t weight_sf_muons_id_up   = 1;
  if( tree->GetBranch( "weight_sf_muons_id_up") ){
  tree->SetBranchAddress("weight_sf_muons_id_up", &weight_sf_muons_id_up);
  } else cout << "DontHave a branch with name = weight_sf_muons_id_up" << endl;
  Double_t weight_sf_muons_id_down   = 1;
  if( tree->GetBranch( "weight_sf_muons_id_down") ){
  tree->SetBranchAddress("weight_sf_muons_id_down", &weight_sf_muons_id_down);
  } else cout << "DontHave a branch with name = weight_sf_muons_id_down" << endl;
  Double_t weight_sf_muons_iso_up   = 1;
  if( tree->GetBranch( "weight_sf_muons_iso_up") ){
  tree->SetBranchAddress("weight_sf_muons_iso_up", &weight_sf_muons_iso_up);
  } else cout << "DontHave a branch with name = weight_sf_muons_iso_up" << endl;
  Double_t weight_sf_muons_iso_down   = 1;
  if( tree->GetBranch( "weight_sf_muons_iso_down") ){
  tree->SetBranchAddress("weight_sf_muons_iso_down", &weight_sf_muons_iso_down);
  } else cout << "DontHave a branch with name = weight_sf_muons_iso_down" << endl;
  Double_t weight_sf_ljets_btag_up   = 1;
  if( tree->GetBranch( "weight_sf_ljets_btag_up") ){
  tree->SetBranchAddress("weight_sf_ljets_btag_up", &weight_sf_ljets_btag_up);
  } else cout << "DontHave a branch with name = weight_sf_ljets_btag_up" << endl;
  Double_t weight_sf_ljets_btag_down   = 1;
  if( tree->GetBranch( "weight_sf_ljets_btag_down") ){
  tree->SetBranchAddress("weight_sf_ljets_btag_down", &weight_sf_ljets_btag_down);
  } else cout << "DontHave a branch with name = weight_sf_ljets_btag_down" << endl;
  Double_t weight_sf_pileup_up   = 1;
  if( tree->GetBranch( "weight_sf_pileup_up") ){
  tree->SetBranchAddress("weight_sf_pileup_up", &weight_sf_pileup_up);
  } else cout << "DontHave a branch with name = weight_sf_pileup_up" << endl;
  Double_t weight_sf_pileup_down   = 1;
  if( tree->GetBranch( "weight_sf_pileup_down") ){
  tree->SetBranchAddress("weight_sf_pileup_down", &weight_sf_pileup_down);
  } else cout << "DontHave a branch with name = weight_sf_pileup_down" << endl;
  Double_t weight_FracRV_up   = 1;
  if( tree->GetBranch( "weight_FracRV_up") ){
  tree->SetBranchAddress("weight_FracRV_up", &weight_FracRV_up);
  } else cout << "DontHave a branch with name = weight_FracRV_up" << endl;
  Double_t weight_FracRV_down   = 1;
  if( tree->GetBranch( "weight_FracRV_down") ){
  tree->SetBranchAddress("weight_FracRV_down", &weight_FracRV_down);
  } else cout << "DontHave a branch with name = weight_FracRV_down" << endl;
  Double_t weight_LooseMvaSF_up   = 1;
  if( tree->GetBranch( "weight_LooseMvaSF_up") ){
  tree->SetBranchAddress("weight_LooseMvaSF_up", &weight_LooseMvaSF_up);
  } else cout << "DontHave a branch with name = weight_LooseMvaSF_up" << endl;
  Double_t weight_LooseMvaSF_down   = 1;
  if( tree->GetBranch( "weight_LooseMvaSF_down") ){
  tree->SetBranchAddress("weight_LooseMvaSF_down", &weight_LooseMvaSF_down);
  } else cout << "DontHave a branch with name = weight_LooseMvaSF_down" << endl;
  Double_t weight_PreselSF_up   = 1;
  if( tree->GetBranch( "weight_PreselSF_up") ){
  tree->SetBranchAddress("weight_PreselSF_up", &weight_PreselSF_up);
  } else cout << "DontHave a branch with name = weight_PreselSF_up" << endl;
  Double_t weight_PreselSF_down   = 1;
  if( tree->GetBranch( "weight_PreselSF_down") ){
  tree->SetBranchAddress("weight_PreselSF_down", &weight_PreselSF_down);
  } else cout << "DontHave a branch with name = weight_PreselSF_down" << endl;
  Double_t weight_Trigger_up   = 1;
  if( tree->GetBranch( "weight_Trigger_up") ){
  tree->SetBranchAddress("weight_Trigger_up", &weight_Trigger_up);
  } else cout << "DontHave a branch with name = weight_Trigger_up" << endl;
  Double_t weight_Trigger_down   = 1;
  if( tree->GetBranch( "weight_Trigger_down") ){
  tree->SetBranchAddress("weight_Trigger_down", &weight_Trigger_down);
  } else cout << "DontHave a branch with name = weight_Trigger_down" << endl;
  Double_t weight_electronVetoSF_up   = 1;
  if( tree->GetBranch( "weight_electronVetoSF_up") ){
  tree->SetBranchAddress("weight_electronVetoSF_up", &weight_electronVetoSF_up);
  } else cout << "DontHave a branch with name = weight_electronVetoSF_up" << endl;
  Double_t weight_electronVetoSF_down   = 1;
  if( tree->GetBranch( "weight_electronVetoSF_down") ){
  tree->SetBranchAddress("weight_electronVetoSF_down", &weight_electronVetoSF_down);
  } else cout << "DontHave a branch with name = weight_electronVetoSF_down" << endl;
  //[[[end]]]

  for(int i = 0; i < nevents; i++){
      if(not (i%TMath::Max(int(0.1*nevents), 1))) cout << input_file << " " << i << "/" << nevents << endl;
      tree->GetEntry(i);
    
      double xfactor = 1, xfactor_1 = 1, xfactor_2 = 1, xfactor_3 = 1;

      if( dataset->IsBackground() ){
        xfactor = mc_weight * lumi_2017 * dataset->xsec / dataset->weight_sum / flashgg_targetLumi;
      } else if ( dataset->IsData() ){
        weight  = 1;
        weight_EFT = 1;
      }
      if( not dataset->IsSignal())
        if( m_yy > 125 - 10 and m_yy < 125 + 10 ) weight = 0;

      // cout << dataset->dataset_ttree_name << " " << weight << " " << weight_sf_muons_id_up << " " <<  weight_sf_muons_iso_up << endl;
      if( weight_sf_muons_id_up != weight_sf_muons_id_up ) weight_sf_muons_id_up = 0;
      if( weight_sf_muons_iso_up != weight_sf_muons_iso_up ) weight_sf_muons_iso_up = 0;
      if( weight_sf_muons_id_down != weight_sf_muons_id_down ) weight_sf_muons_id_down = 0;
      if( weight_sf_muons_iso_down != weight_sf_muons_iso_down ) weight_sf_muons_iso_down = 0;

      //cout << xfactor << endl;
      //xfactor   = (*weight      ) * lumi * train_reweight_factor * extra_weight;
      //xfactor_1 = (*weight_sel_1) * lumi * train_reweight_factor * extra_weight;
      //xfactor_2 = (*weight_sel_2) * lumi * train_reweight_factor * extra_weight;
      //xfactor_3 = (*weight_sel_3) * lumi * train_reweight_factor * extra_weight;
      //cout << weight << " sf=" << weight_sf_photons_up << " " <<  xfactor << " " <<  weight_EFT << endl;

      if( dataset->sys ){
        /*[[[cog
          for var in variables :
            if var.frozen : continue
            if var.key not in vars_with_sys_dataset : continue
            string = var.hist_name + ".Fill( " + var.exp + ", " + var.xfactor + " * xfactor * weight_EFT );"
            cog.outl( string )
        ]]]*/
        hist_33.Fill( W_elnu_tlv->M(), weight * xfactor * weight_EFT );
        hist_34.Fill( W_jj_tlv->M(), weight * xfactor * weight_EFT );
        hist_35.Fill( H_WW_tlv->M(), weight * xfactor * weight_EFT );
        hist_85.Fill( nu_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_86.Fill( nu_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_87.Fill( nu_reco_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_88.Fill( nu_reco_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_89.Fill( nu_reco_tlv->Eta(), weight * xfactor * weight_EFT );
        hist_90.Fill( gen_nu_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_91.Fill( gen_nu_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_92.Fill( gen_nu_tlv->Eta(), weight * xfactor * weight_EFT );
        hist_93.Fill( gen_ljet1_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_94.Fill( ljet1_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_95.Fill( ljet2_tlv->Pt(), weight * xfactor * weight_EFT );
        //[[[end]]]
      } else {
        /*[[[cog
          for var in variables :
            if var.frozen : continue
            string = var.hist_name + ".Fill( " + var.exp + ", " + var.xfactor + " * xfactor * weight_EFT );"
            cog.outl( string )

            sys_vars = []
            for sys in var.sys_factors:
              for sysfactor in ["weight_" + sys + "_up", "weight_" + sys + "_down"]:
                sys_vars += [ sysfactor ]

            for hname, vname in zip(var.sys_hist_names , sys_vars):
              string = hname + ".Fill( " + var.exp + ", " + vname + " * xfactor * weight_EFT );"
              cog.outl( string )
        ]]]*/
        hist_0.Fill( N_leptons, weight * xfactor * weight_EFT );
        hist_1.Fill( N_muons, weight * xfactor * weight_EFT );
        hist_2.Fill( N_electrons, weight * xfactor * weight_EFT );
        hist_3.Fill( m_yy, weight * xfactor * weight_EFT );
        hist_4.Fill( m_yy, weight_sf_photons_up * xfactor * weight_EFT );
        hist_5.Fill( m_yy, weight_sf_photons_down * xfactor * weight_EFT );
        hist_6.Fill( m_yy, weight_sf_electrons_up * xfactor * weight_EFT );
        hist_7.Fill( m_yy, weight_sf_electrons_down * xfactor * weight_EFT );
        hist_8.Fill( m_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
        hist_9.Fill( m_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
        hist_10.Fill( m_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
        hist_11.Fill( m_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
        hist_12.Fill( m_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
        hist_13.Fill( m_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
        hist_14.Fill( m_yy, weight_sf_pileup_up * xfactor * weight_EFT );
        hist_15.Fill( m_yy, weight_sf_pileup_down * xfactor * weight_EFT );
        hist_16.Fill( m_yy, weight_FracRV_up * xfactor * weight_EFT );
        hist_17.Fill( m_yy, weight_FracRV_down * xfactor * weight_EFT );
        hist_18.Fill( m_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
        hist_19.Fill( m_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
        hist_20.Fill( m_yy, weight_PreselSF_up * xfactor * weight_EFT );
        hist_21.Fill( m_yy, weight_PreselSF_down * xfactor * weight_EFT );
        hist_22.Fill( m_yy, weight_Trigger_up * xfactor * weight_EFT );
        hist_23.Fill( m_yy, weight_Trigger_down * xfactor * weight_EFT );
        hist_24.Fill( m_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
        hist_25.Fill( m_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
        hist_26.Fill( y1_Et_div_m_yy, weight * xfactor * weight_EFT );
        hist_27.Fill( y2_Et_div_m_y, weight * xfactor * weight_EFT );
        hist_28.Fill( dR_yy, weight * xfactor * weight_EFT );
        hist_29.Fill( dR_jj, weight * xfactor * weight_EFT );
        hist_30.Fill( dR_WL, weight * xfactor * weight_EFT );
        hist_31.Fill( dR_WW, weight * xfactor * weight_EFT );
        hist_32.Fill( dR_HH, weight * xfactor * weight_EFT );
        hist_33.Fill( W_elnu_tlv->M(), weight * xfactor * weight_EFT );
        hist_34.Fill( W_jj_tlv->M(), weight * xfactor * weight_EFT );
        hist_35.Fill( H_WW_tlv->M(), weight * xfactor * weight_EFT );
        hist_36.Fill( H_WW_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
        hist_37.Fill( H_WW_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
        hist_38.Fill( H_WW_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
        hist_39.Fill( H_WW_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
        hist_40.Fill( H_WW_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
        hist_41.Fill( H_WW_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
        hist_42.Fill( H_WW_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
        hist_43.Fill( H_WW_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
        hist_44.Fill( H_WW_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
        hist_45.Fill( H_WW_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
        hist_46.Fill( H_WW_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
        hist_47.Fill( H_WW_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
        hist_48.Fill( H_WW_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
        hist_49.Fill( H_WW_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
        hist_50.Fill( H_WW_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
        hist_51.Fill( H_WW_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
        hist_52.Fill( H_WW_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
        hist_53.Fill( H_WW_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
        hist_54.Fill( H_WW_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
        hist_55.Fill( H_WW_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
        hist_56.Fill( H_WW_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
        hist_57.Fill( H_WW_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
        hist_58.Fill( HH_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_59.Fill( HH_tlv->CosTheta(), weight * xfactor * weight_EFT );
        hist_60.Fill( HH_tlv->M(), weight * xfactor * weight_EFT );
        hist_61.Fill( y1_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_62.Fill( y2_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_63.Fill( H_yy_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_64.Fill( H_WW_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_65.Fill( W_elnu_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_66.Fill( W_jj_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_67.Fill( gen_HHi_tlv->M(), weight * xfactor * weight_EFT );
        hist_68.Fill( gen_Hi_yy_tlv->CosTheta(), weight * xfactor * weight_EFT );
        hist_69.Fill( dR_genreco_W_jj, weight * xfactor * weight_EFT );
        hist_70.Fill( dR_genreco_W_jj_leading, weight * xfactor * weight_EFT );
        hist_71.Fill( dP_genreco_W_jj, weight * xfactor * weight_EFT );
        hist_72.Fill( dP_genreco_W_jj_leading, weight * xfactor * weight_EFT );
        hist_73.Fill( W_jj_tlv_leading->M(), weight * xfactor * weight_EFT );
        hist_74.Fill( dR_genreco_H_yy, weight * xfactor * weight_EFT );
        hist_75.Fill( dR_genreco_H_WW, weight * xfactor * weight_EFT );
        hist_76.Fill( dR_genreco_nu, weight * xfactor * weight_EFT );
        hist_77.Fill( dR_genreco_W_elnu, weight * xfactor * weight_EFT );
        hist_78.Fill( dP_genreco_H_yy, weight * xfactor * weight_EFT );
        hist_79.Fill( dP_genreco_H_WW, weight * xfactor * weight_EFT );
        hist_80.Fill( dP_genreco_nu, weight * xfactor * weight_EFT );
        hist_81.Fill( dP_genreco_W_elnu, weight * xfactor * weight_EFT );
        hist_82.Fill( gen_dR_jj, weight * xfactor * weight_EFT );
        hist_83.Fill( dR_jj_leading, weight * xfactor * weight_EFT );
        hist_84.Fill( gen_W_jj_tlv->M(), weight * xfactor * weight_EFT );
        hist_85.Fill( nu_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_86.Fill( nu_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_87.Fill( nu_reco_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_88.Fill( nu_reco_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_89.Fill( nu_reco_tlv->Eta(), weight * xfactor * weight_EFT );
        hist_90.Fill( gen_nu_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_91.Fill( gen_nu_tlv->Phi(), weight * xfactor * weight_EFT );
        hist_92.Fill( gen_nu_tlv->Eta(), weight * xfactor * weight_EFT );
        hist_93.Fill( gen_ljet1_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_94.Fill( ljet1_tlv->Pt(), weight * xfactor * weight_EFT );
        hist_95.Fill( ljet2_tlv->Pt(), weight * xfactor * weight_EFT );
        //[[[end]]]
      }

      //if(i > 1000) break;
  }

  output_file->cd();
  output_file->Write();
  output_file->Close();

  file->Close();

  return 0;
}

struct plot_from_file_args{
  string output_file_name;
  string input_file_name;
  vseva::DataSet * dataset;
};

void * plot_from_file_wrapper(void * a){
  plot_from_file_args * args = (plot_from_file_args*) a; 
  cout << "Start with " << args->input_file_name << endl;
  plot_from_file(args->dataset, args->input_file_name, args->output_file_name);
  cout << "Done with "  << args->input_file_name << endl;
  // TThread::Exit(0);
  return 0;
}

int COGGED_hist_maker_COGGED(){
  cout << "hist_maker_TMP() ... init" << endl;

  vector<vseva::DataSet*> datasets = get_datasets();
  if( TMVA_DATASETS ) datasets = get_datasets_spl();

  map<string, vseva::PlotVariable> variables = get_variables();

  // TFile * file = TFile::Open( datasets.at(0)->files.at(0).c_str() );
  // TTree * tree = (TTree*) gDirectory->Get("Def_Events");
  // tree->MakeClass();

  cout << "hist_maker_TMP() ... make treads " << endl;
  vector<TThread*> threads;
  for(auto dataset : datasets){
    plot_from_file_args * args   = new plot_from_file_args();
    args->output_file_name = "./output/" + dataset->process_name + "_hists.root";
    args->input_file_name  = dataset->files.at(0);
    args->dataset = dataset;

    cout << "THREAD ... " << args->output_file_name << " " << args->input_file_name << endl;
    TThread* new_thread = new TThread(dataset->process_name.c_str(), &plot_from_file_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  cout << "hist_maker_TMP() ... submit treads " << endl;
  threads_care( threads, 10 );
  return 0;
}














