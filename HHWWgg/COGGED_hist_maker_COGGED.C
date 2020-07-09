
#include "analyse_cfg.C"

#include "Def_Events.C"

#include "../vseva.hh"

// root -l -b -q "make_interface.C(\"/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_EFT2_v3.root\")"
// python -m cogapp.__main__ -o COGGED_hist_maker_COGGED.C hist_maker.C; root -l -b -q COGGED_hist_maker_COGGED.C

map<string, vseva::PlotVariable> get_variables(){
  map<string, vseva::PlotVariable> custom_variables;

  /*[[[cog
    from mRootCOG import *
    from mRootCOGAnalyser import *
    from AnalyseHEPPY import *

    systematics = ["sf_photons", "sf_electrons", "sf_muons_id", "sf_muons_iso", "sf_ljets_id", "sf_ljets_btag", "sf_bjets_id", "sf_pileup", "FracRV", "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF"]
    #systematics = []

    def_variables = [
        PlotVariable("m_yy", 100, 160, "Double_t"),
        PlotVariable("y1_Et_div_m_yy", 0, 2, "Double_t"),
        PlotVariable("y2_Et_div_m_y", 0, 2, "Double_t"),
        PlotVariable("dR_yy", 0, 5, "Double_t"),
        PlotVariable("dR_jj", 0, 5, "Double_t"),
        PlotVariable("dR_WL", 0, 5, "Double_t"),
        PlotVariable("dR_WW", 0, 5, "Double_t"),
        PlotVariable("dR_HH", 0, 5, "Double_t"),
        PlotVariable("W_elnu_tlv", 10,  300, "TLorentzVector", expr="W_elnu_tlv->M()"),
        PlotVariable("W_jj_tlv",   10,  300, "TLorentzVector", expr="W_jj_tlv->M()"  ),
        PlotVariable("H_WW_tlv",   10, 1000, "TLorentzVector", expr="H_WW_tlv->M()"  ),

        PlotVariable("gen_HHi_tlv", 0, 1200, "TLorentzVector", expr="gen_HHi_tlv->M()"),
        PlotVariable("gen_Hi_yy_tlv", 0,  1, "TLorentzVector", expr="gen_Hi_yy_tlv->CosTheta()"),

        PlotVariable("dR_genreco_W_jj"        , 0,   5, "Double_t"),
        PlotVariable("dR_genreco_W_jj_leading", 0,   5, "Double_t"),
        PlotVariable("dP_genreco_W_jj"        , 0, 600, "Double_t"),
        PlotVariable("dP_genreco_W_jj_leading", 0, 600, "Double_t"),
        PlotVariable("W_jj_tlv_leading",       10, 300, "TLorentzVector", expr="W_jj_tlv_leading->M()" ),

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
        PlotVariable("gen_W_jj_tlv", 10, 300, "TLorentzVector", expr="gen_W_jj_tlv->M()" ),
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
      var.sys_factors = systematics
      var.sys_hist_names = []
    
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

      for sys in var.sys_factors:
        for sysfactor in ["weight_" + sys + "_up", "weight_" + sys + "_down"]:
          name = "(dataset->process_name + \"" + "_" + var.key + "_" + sysfactor + "\").c_str()"
          title = "\"" + var.key + "_" + sysfactor + "\""
          var.sys_hist_names += [ cpp_TH1(name, title, var.nbins, var.xmin, var.xmax, type="D") ]
  ]]]*/
  TH1D hist_0 = TH1D((dataset->process_name + "_m_yy_weight").c_str(), "m_yy_weight", 20, 100, 160);
  TH1D hist_1 = TH1D((dataset->process_name + "_m_yy_weight_sf_photons_up").c_str(), "m_yy_weight_sf_photons_up", 20, 100, 160);
  TH1D hist_2 = TH1D((dataset->process_name + "_m_yy_weight_sf_photons_down").c_str(), "m_yy_weight_sf_photons_down", 20, 100, 160);
  TH1D hist_3 = TH1D((dataset->process_name + "_m_yy_weight_sf_electrons_up").c_str(), "m_yy_weight_sf_electrons_up", 20, 100, 160);
  TH1D hist_4 = TH1D((dataset->process_name + "_m_yy_weight_sf_electrons_down").c_str(), "m_yy_weight_sf_electrons_down", 20, 100, 160);
  TH1D hist_5 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_id_up").c_str(), "m_yy_weight_sf_muons_id_up", 20, 100, 160);
  TH1D hist_6 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_id_down").c_str(), "m_yy_weight_sf_muons_id_down", 20, 100, 160);
  TH1D hist_7 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_iso_up").c_str(), "m_yy_weight_sf_muons_iso_up", 20, 100, 160);
  TH1D hist_8 = TH1D((dataset->process_name + "_m_yy_weight_sf_muons_iso_down").c_str(), "m_yy_weight_sf_muons_iso_down", 20, 100, 160);
  TH1D hist_9 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_id_up").c_str(), "m_yy_weight_sf_ljets_id_up", 20, 100, 160);
  TH1D hist_10 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_id_down").c_str(), "m_yy_weight_sf_ljets_id_down", 20, 100, 160);
  TH1D hist_11 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_btag_up").c_str(), "m_yy_weight_sf_ljets_btag_up", 20, 100, 160);
  TH1D hist_12 = TH1D((dataset->process_name + "_m_yy_weight_sf_ljets_btag_down").c_str(), "m_yy_weight_sf_ljets_btag_down", 20, 100, 160);
  TH1D hist_13 = TH1D((dataset->process_name + "_m_yy_weight_sf_bjets_id_up").c_str(), "m_yy_weight_sf_bjets_id_up", 20, 100, 160);
  TH1D hist_14 = TH1D((dataset->process_name + "_m_yy_weight_sf_bjets_id_down").c_str(), "m_yy_weight_sf_bjets_id_down", 20, 100, 160);
  TH1D hist_15 = TH1D((dataset->process_name + "_m_yy_weight_sf_pileup_up").c_str(), "m_yy_weight_sf_pileup_up", 20, 100, 160);
  TH1D hist_16 = TH1D((dataset->process_name + "_m_yy_weight_sf_pileup_down").c_str(), "m_yy_weight_sf_pileup_down", 20, 100, 160);
  TH1D hist_17 = TH1D((dataset->process_name + "_m_yy_weight_FracRV_up").c_str(), "m_yy_weight_FracRV_up", 20, 100, 160);
  TH1D hist_18 = TH1D((dataset->process_name + "_m_yy_weight_FracRV_down").c_str(), "m_yy_weight_FracRV_down", 20, 100, 160);
  TH1D hist_19 = TH1D((dataset->process_name + "_m_yy_weight_LooseMvaSF_up").c_str(), "m_yy_weight_LooseMvaSF_up", 20, 100, 160);
  TH1D hist_20 = TH1D((dataset->process_name + "_m_yy_weight_LooseMvaSF_down").c_str(), "m_yy_weight_LooseMvaSF_down", 20, 100, 160);
  TH1D hist_21 = TH1D((dataset->process_name + "_m_yy_weight_PreselSF_up").c_str(), "m_yy_weight_PreselSF_up", 20, 100, 160);
  TH1D hist_22 = TH1D((dataset->process_name + "_m_yy_weight_PreselSF_down").c_str(), "m_yy_weight_PreselSF_down", 20, 100, 160);
  TH1D hist_23 = TH1D((dataset->process_name + "_m_yy_weight_Trigger_up").c_str(), "m_yy_weight_Trigger_up", 20, 100, 160);
  TH1D hist_24 = TH1D((dataset->process_name + "_m_yy_weight_Trigger_down").c_str(), "m_yy_weight_Trigger_down", 20, 100, 160);
  TH1D hist_25 = TH1D((dataset->process_name + "_m_yy_weight_electronVetoSF_up").c_str(), "m_yy_weight_electronVetoSF_up", 20, 100, 160);
  TH1D hist_26 = TH1D((dataset->process_name + "_m_yy_weight_electronVetoSF_down").c_str(), "m_yy_weight_electronVetoSF_down", 20, 100, 160);
  TH1D hist_27 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight").c_str(), "y1_Et_div_m_yy_weight", 20, 0, 2);
  TH1D hist_28 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_photons_up").c_str(), "y1_Et_div_m_yy_weight_sf_photons_up", 20, 0, 2);
  TH1D hist_29 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_photons_down").c_str(), "y1_Et_div_m_yy_weight_sf_photons_down", 20, 0, 2);
  TH1D hist_30 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_electrons_up").c_str(), "y1_Et_div_m_yy_weight_sf_electrons_up", 20, 0, 2);
  TH1D hist_31 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_electrons_down").c_str(), "y1_Et_div_m_yy_weight_sf_electrons_down", 20, 0, 2);
  TH1D hist_32 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_muons_id_up").c_str(), "y1_Et_div_m_yy_weight_sf_muons_id_up", 20, 0, 2);
  TH1D hist_33 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_muons_id_down").c_str(), "y1_Et_div_m_yy_weight_sf_muons_id_down", 20, 0, 2);
  TH1D hist_34 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_muons_iso_up").c_str(), "y1_Et_div_m_yy_weight_sf_muons_iso_up", 20, 0, 2);
  TH1D hist_35 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_muons_iso_down").c_str(), "y1_Et_div_m_yy_weight_sf_muons_iso_down", 20, 0, 2);
  TH1D hist_36 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_ljets_id_up").c_str(), "y1_Et_div_m_yy_weight_sf_ljets_id_up", 20, 0, 2);
  TH1D hist_37 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_ljets_id_down").c_str(), "y1_Et_div_m_yy_weight_sf_ljets_id_down", 20, 0, 2);
  TH1D hist_38 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_ljets_btag_up").c_str(), "y1_Et_div_m_yy_weight_sf_ljets_btag_up", 20, 0, 2);
  TH1D hist_39 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_ljets_btag_down").c_str(), "y1_Et_div_m_yy_weight_sf_ljets_btag_down", 20, 0, 2);
  TH1D hist_40 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_bjets_id_up").c_str(), "y1_Et_div_m_yy_weight_sf_bjets_id_up", 20, 0, 2);
  TH1D hist_41 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_bjets_id_down").c_str(), "y1_Et_div_m_yy_weight_sf_bjets_id_down", 20, 0, 2);
  TH1D hist_42 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_pileup_up").c_str(), "y1_Et_div_m_yy_weight_sf_pileup_up", 20, 0, 2);
  TH1D hist_43 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_sf_pileup_down").c_str(), "y1_Et_div_m_yy_weight_sf_pileup_down", 20, 0, 2);
  TH1D hist_44 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_FracRV_up").c_str(), "y1_Et_div_m_yy_weight_FracRV_up", 20, 0, 2);
  TH1D hist_45 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_FracRV_down").c_str(), "y1_Et_div_m_yy_weight_FracRV_down", 20, 0, 2);
  TH1D hist_46 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_LooseMvaSF_up").c_str(), "y1_Et_div_m_yy_weight_LooseMvaSF_up", 20, 0, 2);
  TH1D hist_47 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_LooseMvaSF_down").c_str(), "y1_Et_div_m_yy_weight_LooseMvaSF_down", 20, 0, 2);
  TH1D hist_48 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_PreselSF_up").c_str(), "y1_Et_div_m_yy_weight_PreselSF_up", 20, 0, 2);
  TH1D hist_49 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_PreselSF_down").c_str(), "y1_Et_div_m_yy_weight_PreselSF_down", 20, 0, 2);
  TH1D hist_50 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_Trigger_up").c_str(), "y1_Et_div_m_yy_weight_Trigger_up", 20, 0, 2);
  TH1D hist_51 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_Trigger_down").c_str(), "y1_Et_div_m_yy_weight_Trigger_down", 20, 0, 2);
  TH1D hist_52 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_electronVetoSF_up").c_str(), "y1_Et_div_m_yy_weight_electronVetoSF_up", 20, 0, 2);
  TH1D hist_53 = TH1D((dataset->process_name + "_y1_Et_div_m_yy_weight_electronVetoSF_down").c_str(), "y1_Et_div_m_yy_weight_electronVetoSF_down", 20, 0, 2);
  TH1D hist_54 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight").c_str(), "y2_Et_div_m_y_weight", 20, 0, 2);
  TH1D hist_55 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_photons_up").c_str(), "y2_Et_div_m_y_weight_sf_photons_up", 20, 0, 2);
  TH1D hist_56 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_photons_down").c_str(), "y2_Et_div_m_y_weight_sf_photons_down", 20, 0, 2);
  TH1D hist_57 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_electrons_up").c_str(), "y2_Et_div_m_y_weight_sf_electrons_up", 20, 0, 2);
  TH1D hist_58 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_electrons_down").c_str(), "y2_Et_div_m_y_weight_sf_electrons_down", 20, 0, 2);
  TH1D hist_59 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_muons_id_up").c_str(), "y2_Et_div_m_y_weight_sf_muons_id_up", 20, 0, 2);
  TH1D hist_60 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_muons_id_down").c_str(), "y2_Et_div_m_y_weight_sf_muons_id_down", 20, 0, 2);
  TH1D hist_61 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_muons_iso_up").c_str(), "y2_Et_div_m_y_weight_sf_muons_iso_up", 20, 0, 2);
  TH1D hist_62 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_muons_iso_down").c_str(), "y2_Et_div_m_y_weight_sf_muons_iso_down", 20, 0, 2);
  TH1D hist_63 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_ljets_id_up").c_str(), "y2_Et_div_m_y_weight_sf_ljets_id_up", 20, 0, 2);
  TH1D hist_64 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_ljets_id_down").c_str(), "y2_Et_div_m_y_weight_sf_ljets_id_down", 20, 0, 2);
  TH1D hist_65 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_ljets_btag_up").c_str(), "y2_Et_div_m_y_weight_sf_ljets_btag_up", 20, 0, 2);
  TH1D hist_66 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_ljets_btag_down").c_str(), "y2_Et_div_m_y_weight_sf_ljets_btag_down", 20, 0, 2);
  TH1D hist_67 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_bjets_id_up").c_str(), "y2_Et_div_m_y_weight_sf_bjets_id_up", 20, 0, 2);
  TH1D hist_68 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_bjets_id_down").c_str(), "y2_Et_div_m_y_weight_sf_bjets_id_down", 20, 0, 2);
  TH1D hist_69 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_pileup_up").c_str(), "y2_Et_div_m_y_weight_sf_pileup_up", 20, 0, 2);
  TH1D hist_70 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_sf_pileup_down").c_str(), "y2_Et_div_m_y_weight_sf_pileup_down", 20, 0, 2);
  TH1D hist_71 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_FracRV_up").c_str(), "y2_Et_div_m_y_weight_FracRV_up", 20, 0, 2);
  TH1D hist_72 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_FracRV_down").c_str(), "y2_Et_div_m_y_weight_FracRV_down", 20, 0, 2);
  TH1D hist_73 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_LooseMvaSF_up").c_str(), "y2_Et_div_m_y_weight_LooseMvaSF_up", 20, 0, 2);
  TH1D hist_74 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_LooseMvaSF_down").c_str(), "y2_Et_div_m_y_weight_LooseMvaSF_down", 20, 0, 2);
  TH1D hist_75 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_PreselSF_up").c_str(), "y2_Et_div_m_y_weight_PreselSF_up", 20, 0, 2);
  TH1D hist_76 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_PreselSF_down").c_str(), "y2_Et_div_m_y_weight_PreselSF_down", 20, 0, 2);
  TH1D hist_77 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_Trigger_up").c_str(), "y2_Et_div_m_y_weight_Trigger_up", 20, 0, 2);
  TH1D hist_78 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_Trigger_down").c_str(), "y2_Et_div_m_y_weight_Trigger_down", 20, 0, 2);
  TH1D hist_79 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_electronVetoSF_up").c_str(), "y2_Et_div_m_y_weight_electronVetoSF_up", 20, 0, 2);
  TH1D hist_80 = TH1D((dataset->process_name + "_y2_Et_div_m_y_weight_electronVetoSF_down").c_str(), "y2_Et_div_m_y_weight_electronVetoSF_down", 20, 0, 2);
  TH1D hist_81 = TH1D((dataset->process_name + "_dR_yy_weight").c_str(), "dR_yy_weight", 20, 0, 5);
  TH1D hist_82 = TH1D((dataset->process_name + "_dR_yy_weight_sf_photons_up").c_str(), "dR_yy_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_83 = TH1D((dataset->process_name + "_dR_yy_weight_sf_photons_down").c_str(), "dR_yy_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_84 = TH1D((dataset->process_name + "_dR_yy_weight_sf_electrons_up").c_str(), "dR_yy_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_85 = TH1D((dataset->process_name + "_dR_yy_weight_sf_electrons_down").c_str(), "dR_yy_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_86 = TH1D((dataset->process_name + "_dR_yy_weight_sf_muons_id_up").c_str(), "dR_yy_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_87 = TH1D((dataset->process_name + "_dR_yy_weight_sf_muons_id_down").c_str(), "dR_yy_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_88 = TH1D((dataset->process_name + "_dR_yy_weight_sf_muons_iso_up").c_str(), "dR_yy_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_89 = TH1D((dataset->process_name + "_dR_yy_weight_sf_muons_iso_down").c_str(), "dR_yy_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_90 = TH1D((dataset->process_name + "_dR_yy_weight_sf_ljets_id_up").c_str(), "dR_yy_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_91 = TH1D((dataset->process_name + "_dR_yy_weight_sf_ljets_id_down").c_str(), "dR_yy_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_92 = TH1D((dataset->process_name + "_dR_yy_weight_sf_ljets_btag_up").c_str(), "dR_yy_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_93 = TH1D((dataset->process_name + "_dR_yy_weight_sf_ljets_btag_down").c_str(), "dR_yy_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_94 = TH1D((dataset->process_name + "_dR_yy_weight_sf_bjets_id_up").c_str(), "dR_yy_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_95 = TH1D((dataset->process_name + "_dR_yy_weight_sf_bjets_id_down").c_str(), "dR_yy_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_96 = TH1D((dataset->process_name + "_dR_yy_weight_sf_pileup_up").c_str(), "dR_yy_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_97 = TH1D((dataset->process_name + "_dR_yy_weight_sf_pileup_down").c_str(), "dR_yy_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_98 = TH1D((dataset->process_name + "_dR_yy_weight_FracRV_up").c_str(), "dR_yy_weight_FracRV_up", 20, 0, 5);
  TH1D hist_99 = TH1D((dataset->process_name + "_dR_yy_weight_FracRV_down").c_str(), "dR_yy_weight_FracRV_down", 20, 0, 5);
  TH1D hist_100 = TH1D((dataset->process_name + "_dR_yy_weight_LooseMvaSF_up").c_str(), "dR_yy_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_101 = TH1D((dataset->process_name + "_dR_yy_weight_LooseMvaSF_down").c_str(), "dR_yy_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_102 = TH1D((dataset->process_name + "_dR_yy_weight_PreselSF_up").c_str(), "dR_yy_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_103 = TH1D((dataset->process_name + "_dR_yy_weight_PreselSF_down").c_str(), "dR_yy_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_104 = TH1D((dataset->process_name + "_dR_yy_weight_Trigger_up").c_str(), "dR_yy_weight_Trigger_up", 20, 0, 5);
  TH1D hist_105 = TH1D((dataset->process_name + "_dR_yy_weight_Trigger_down").c_str(), "dR_yy_weight_Trigger_down", 20, 0, 5);
  TH1D hist_106 = TH1D((dataset->process_name + "_dR_yy_weight_electronVetoSF_up").c_str(), "dR_yy_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_107 = TH1D((dataset->process_name + "_dR_yy_weight_electronVetoSF_down").c_str(), "dR_yy_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_108 = TH1D((dataset->process_name + "_dR_jj_weight").c_str(), "dR_jj_weight", 20, 0, 5);
  TH1D hist_109 = TH1D((dataset->process_name + "_dR_jj_weight_sf_photons_up").c_str(), "dR_jj_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_110 = TH1D((dataset->process_name + "_dR_jj_weight_sf_photons_down").c_str(), "dR_jj_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_111 = TH1D((dataset->process_name + "_dR_jj_weight_sf_electrons_up").c_str(), "dR_jj_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_112 = TH1D((dataset->process_name + "_dR_jj_weight_sf_electrons_down").c_str(), "dR_jj_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_113 = TH1D((dataset->process_name + "_dR_jj_weight_sf_muons_id_up").c_str(), "dR_jj_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_114 = TH1D((dataset->process_name + "_dR_jj_weight_sf_muons_id_down").c_str(), "dR_jj_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_115 = TH1D((dataset->process_name + "_dR_jj_weight_sf_muons_iso_up").c_str(), "dR_jj_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_116 = TH1D((dataset->process_name + "_dR_jj_weight_sf_muons_iso_down").c_str(), "dR_jj_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_117 = TH1D((dataset->process_name + "_dR_jj_weight_sf_ljets_id_up").c_str(), "dR_jj_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_118 = TH1D((dataset->process_name + "_dR_jj_weight_sf_ljets_id_down").c_str(), "dR_jj_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_119 = TH1D((dataset->process_name + "_dR_jj_weight_sf_ljets_btag_up").c_str(), "dR_jj_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_120 = TH1D((dataset->process_name + "_dR_jj_weight_sf_ljets_btag_down").c_str(), "dR_jj_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_121 = TH1D((dataset->process_name + "_dR_jj_weight_sf_bjets_id_up").c_str(), "dR_jj_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_122 = TH1D((dataset->process_name + "_dR_jj_weight_sf_bjets_id_down").c_str(), "dR_jj_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_123 = TH1D((dataset->process_name + "_dR_jj_weight_sf_pileup_up").c_str(), "dR_jj_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_124 = TH1D((dataset->process_name + "_dR_jj_weight_sf_pileup_down").c_str(), "dR_jj_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_125 = TH1D((dataset->process_name + "_dR_jj_weight_FracRV_up").c_str(), "dR_jj_weight_FracRV_up", 20, 0, 5);
  TH1D hist_126 = TH1D((dataset->process_name + "_dR_jj_weight_FracRV_down").c_str(), "dR_jj_weight_FracRV_down", 20, 0, 5);
  TH1D hist_127 = TH1D((dataset->process_name + "_dR_jj_weight_LooseMvaSF_up").c_str(), "dR_jj_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_128 = TH1D((dataset->process_name + "_dR_jj_weight_LooseMvaSF_down").c_str(), "dR_jj_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_129 = TH1D((dataset->process_name + "_dR_jj_weight_PreselSF_up").c_str(), "dR_jj_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_130 = TH1D((dataset->process_name + "_dR_jj_weight_PreselSF_down").c_str(), "dR_jj_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_131 = TH1D((dataset->process_name + "_dR_jj_weight_Trigger_up").c_str(), "dR_jj_weight_Trigger_up", 20, 0, 5);
  TH1D hist_132 = TH1D((dataset->process_name + "_dR_jj_weight_Trigger_down").c_str(), "dR_jj_weight_Trigger_down", 20, 0, 5);
  TH1D hist_133 = TH1D((dataset->process_name + "_dR_jj_weight_electronVetoSF_up").c_str(), "dR_jj_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_134 = TH1D((dataset->process_name + "_dR_jj_weight_electronVetoSF_down").c_str(), "dR_jj_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_135 = TH1D((dataset->process_name + "_dR_WL_weight").c_str(), "dR_WL_weight", 20, 0, 5);
  TH1D hist_136 = TH1D((dataset->process_name + "_dR_WL_weight_sf_photons_up").c_str(), "dR_WL_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_137 = TH1D((dataset->process_name + "_dR_WL_weight_sf_photons_down").c_str(), "dR_WL_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_138 = TH1D((dataset->process_name + "_dR_WL_weight_sf_electrons_up").c_str(), "dR_WL_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_139 = TH1D((dataset->process_name + "_dR_WL_weight_sf_electrons_down").c_str(), "dR_WL_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_140 = TH1D((dataset->process_name + "_dR_WL_weight_sf_muons_id_up").c_str(), "dR_WL_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_141 = TH1D((dataset->process_name + "_dR_WL_weight_sf_muons_id_down").c_str(), "dR_WL_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_142 = TH1D((dataset->process_name + "_dR_WL_weight_sf_muons_iso_up").c_str(), "dR_WL_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_143 = TH1D((dataset->process_name + "_dR_WL_weight_sf_muons_iso_down").c_str(), "dR_WL_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_144 = TH1D((dataset->process_name + "_dR_WL_weight_sf_ljets_id_up").c_str(), "dR_WL_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_145 = TH1D((dataset->process_name + "_dR_WL_weight_sf_ljets_id_down").c_str(), "dR_WL_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_146 = TH1D((dataset->process_name + "_dR_WL_weight_sf_ljets_btag_up").c_str(), "dR_WL_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_147 = TH1D((dataset->process_name + "_dR_WL_weight_sf_ljets_btag_down").c_str(), "dR_WL_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_148 = TH1D((dataset->process_name + "_dR_WL_weight_sf_bjets_id_up").c_str(), "dR_WL_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_149 = TH1D((dataset->process_name + "_dR_WL_weight_sf_bjets_id_down").c_str(), "dR_WL_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_150 = TH1D((dataset->process_name + "_dR_WL_weight_sf_pileup_up").c_str(), "dR_WL_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_151 = TH1D((dataset->process_name + "_dR_WL_weight_sf_pileup_down").c_str(), "dR_WL_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_152 = TH1D((dataset->process_name + "_dR_WL_weight_FracRV_up").c_str(), "dR_WL_weight_FracRV_up", 20, 0, 5);
  TH1D hist_153 = TH1D((dataset->process_name + "_dR_WL_weight_FracRV_down").c_str(), "dR_WL_weight_FracRV_down", 20, 0, 5);
  TH1D hist_154 = TH1D((dataset->process_name + "_dR_WL_weight_LooseMvaSF_up").c_str(), "dR_WL_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_155 = TH1D((dataset->process_name + "_dR_WL_weight_LooseMvaSF_down").c_str(), "dR_WL_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_156 = TH1D((dataset->process_name + "_dR_WL_weight_PreselSF_up").c_str(), "dR_WL_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_157 = TH1D((dataset->process_name + "_dR_WL_weight_PreselSF_down").c_str(), "dR_WL_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_158 = TH1D((dataset->process_name + "_dR_WL_weight_Trigger_up").c_str(), "dR_WL_weight_Trigger_up", 20, 0, 5);
  TH1D hist_159 = TH1D((dataset->process_name + "_dR_WL_weight_Trigger_down").c_str(), "dR_WL_weight_Trigger_down", 20, 0, 5);
  TH1D hist_160 = TH1D((dataset->process_name + "_dR_WL_weight_electronVetoSF_up").c_str(), "dR_WL_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_161 = TH1D((dataset->process_name + "_dR_WL_weight_electronVetoSF_down").c_str(), "dR_WL_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_162 = TH1D((dataset->process_name + "_dR_WW_weight").c_str(), "dR_WW_weight", 20, 0, 5);
  TH1D hist_163 = TH1D((dataset->process_name + "_dR_WW_weight_sf_photons_up").c_str(), "dR_WW_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_164 = TH1D((dataset->process_name + "_dR_WW_weight_sf_photons_down").c_str(), "dR_WW_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_165 = TH1D((dataset->process_name + "_dR_WW_weight_sf_electrons_up").c_str(), "dR_WW_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_166 = TH1D((dataset->process_name + "_dR_WW_weight_sf_electrons_down").c_str(), "dR_WW_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_167 = TH1D((dataset->process_name + "_dR_WW_weight_sf_muons_id_up").c_str(), "dR_WW_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_168 = TH1D((dataset->process_name + "_dR_WW_weight_sf_muons_id_down").c_str(), "dR_WW_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_169 = TH1D((dataset->process_name + "_dR_WW_weight_sf_muons_iso_up").c_str(), "dR_WW_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_170 = TH1D((dataset->process_name + "_dR_WW_weight_sf_muons_iso_down").c_str(), "dR_WW_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_171 = TH1D((dataset->process_name + "_dR_WW_weight_sf_ljets_id_up").c_str(), "dR_WW_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_172 = TH1D((dataset->process_name + "_dR_WW_weight_sf_ljets_id_down").c_str(), "dR_WW_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_173 = TH1D((dataset->process_name + "_dR_WW_weight_sf_ljets_btag_up").c_str(), "dR_WW_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_174 = TH1D((dataset->process_name + "_dR_WW_weight_sf_ljets_btag_down").c_str(), "dR_WW_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_175 = TH1D((dataset->process_name + "_dR_WW_weight_sf_bjets_id_up").c_str(), "dR_WW_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_176 = TH1D((dataset->process_name + "_dR_WW_weight_sf_bjets_id_down").c_str(), "dR_WW_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_177 = TH1D((dataset->process_name + "_dR_WW_weight_sf_pileup_up").c_str(), "dR_WW_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_178 = TH1D((dataset->process_name + "_dR_WW_weight_sf_pileup_down").c_str(), "dR_WW_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_179 = TH1D((dataset->process_name + "_dR_WW_weight_FracRV_up").c_str(), "dR_WW_weight_FracRV_up", 20, 0, 5);
  TH1D hist_180 = TH1D((dataset->process_name + "_dR_WW_weight_FracRV_down").c_str(), "dR_WW_weight_FracRV_down", 20, 0, 5);
  TH1D hist_181 = TH1D((dataset->process_name + "_dR_WW_weight_LooseMvaSF_up").c_str(), "dR_WW_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_182 = TH1D((dataset->process_name + "_dR_WW_weight_LooseMvaSF_down").c_str(), "dR_WW_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_183 = TH1D((dataset->process_name + "_dR_WW_weight_PreselSF_up").c_str(), "dR_WW_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_184 = TH1D((dataset->process_name + "_dR_WW_weight_PreselSF_down").c_str(), "dR_WW_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_185 = TH1D((dataset->process_name + "_dR_WW_weight_Trigger_up").c_str(), "dR_WW_weight_Trigger_up", 20, 0, 5);
  TH1D hist_186 = TH1D((dataset->process_name + "_dR_WW_weight_Trigger_down").c_str(), "dR_WW_weight_Trigger_down", 20, 0, 5);
  TH1D hist_187 = TH1D((dataset->process_name + "_dR_WW_weight_electronVetoSF_up").c_str(), "dR_WW_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_188 = TH1D((dataset->process_name + "_dR_WW_weight_electronVetoSF_down").c_str(), "dR_WW_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_189 = TH1D((dataset->process_name + "_dR_HH_weight").c_str(), "dR_HH_weight", 20, 0, 5);
  TH1D hist_190 = TH1D((dataset->process_name + "_dR_HH_weight_sf_photons_up").c_str(), "dR_HH_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_191 = TH1D((dataset->process_name + "_dR_HH_weight_sf_photons_down").c_str(), "dR_HH_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_192 = TH1D((dataset->process_name + "_dR_HH_weight_sf_electrons_up").c_str(), "dR_HH_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_193 = TH1D((dataset->process_name + "_dR_HH_weight_sf_electrons_down").c_str(), "dR_HH_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_194 = TH1D((dataset->process_name + "_dR_HH_weight_sf_muons_id_up").c_str(), "dR_HH_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_195 = TH1D((dataset->process_name + "_dR_HH_weight_sf_muons_id_down").c_str(), "dR_HH_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_196 = TH1D((dataset->process_name + "_dR_HH_weight_sf_muons_iso_up").c_str(), "dR_HH_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_197 = TH1D((dataset->process_name + "_dR_HH_weight_sf_muons_iso_down").c_str(), "dR_HH_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_198 = TH1D((dataset->process_name + "_dR_HH_weight_sf_ljets_id_up").c_str(), "dR_HH_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_199 = TH1D((dataset->process_name + "_dR_HH_weight_sf_ljets_id_down").c_str(), "dR_HH_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_200 = TH1D((dataset->process_name + "_dR_HH_weight_sf_ljets_btag_up").c_str(), "dR_HH_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_201 = TH1D((dataset->process_name + "_dR_HH_weight_sf_ljets_btag_down").c_str(), "dR_HH_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_202 = TH1D((dataset->process_name + "_dR_HH_weight_sf_bjets_id_up").c_str(), "dR_HH_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_203 = TH1D((dataset->process_name + "_dR_HH_weight_sf_bjets_id_down").c_str(), "dR_HH_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_204 = TH1D((dataset->process_name + "_dR_HH_weight_sf_pileup_up").c_str(), "dR_HH_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_205 = TH1D((dataset->process_name + "_dR_HH_weight_sf_pileup_down").c_str(), "dR_HH_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_206 = TH1D((dataset->process_name + "_dR_HH_weight_FracRV_up").c_str(), "dR_HH_weight_FracRV_up", 20, 0, 5);
  TH1D hist_207 = TH1D((dataset->process_name + "_dR_HH_weight_FracRV_down").c_str(), "dR_HH_weight_FracRV_down", 20, 0, 5);
  TH1D hist_208 = TH1D((dataset->process_name + "_dR_HH_weight_LooseMvaSF_up").c_str(), "dR_HH_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_209 = TH1D((dataset->process_name + "_dR_HH_weight_LooseMvaSF_down").c_str(), "dR_HH_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_210 = TH1D((dataset->process_name + "_dR_HH_weight_PreselSF_up").c_str(), "dR_HH_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_211 = TH1D((dataset->process_name + "_dR_HH_weight_PreselSF_down").c_str(), "dR_HH_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_212 = TH1D((dataset->process_name + "_dR_HH_weight_Trigger_up").c_str(), "dR_HH_weight_Trigger_up", 20, 0, 5);
  TH1D hist_213 = TH1D((dataset->process_name + "_dR_HH_weight_Trigger_down").c_str(), "dR_HH_weight_Trigger_down", 20, 0, 5);
  TH1D hist_214 = TH1D((dataset->process_name + "_dR_HH_weight_electronVetoSF_up").c_str(), "dR_HH_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_215 = TH1D((dataset->process_name + "_dR_HH_weight_electronVetoSF_down").c_str(), "dR_HH_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_216 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight").c_str(), "W_elnu_tlv_M_weight", 20, 10, 300);
  TH1D hist_217 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_photons_up").c_str(), "W_elnu_tlv_M_weight_sf_photons_up", 20, 10, 300);
  TH1D hist_218 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_photons_down").c_str(), "W_elnu_tlv_M_weight_sf_photons_down", 20, 10, 300);
  TH1D hist_219 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_electrons_up").c_str(), "W_elnu_tlv_M_weight_sf_electrons_up", 20, 10, 300);
  TH1D hist_220 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_electrons_down").c_str(), "W_elnu_tlv_M_weight_sf_electrons_down", 20, 10, 300);
  TH1D hist_221 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_muons_id_up").c_str(), "W_elnu_tlv_M_weight_sf_muons_id_up", 20, 10, 300);
  TH1D hist_222 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_muons_id_down").c_str(), "W_elnu_tlv_M_weight_sf_muons_id_down", 20, 10, 300);
  TH1D hist_223 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_muons_iso_up").c_str(), "W_elnu_tlv_M_weight_sf_muons_iso_up", 20, 10, 300);
  TH1D hist_224 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_muons_iso_down").c_str(), "W_elnu_tlv_M_weight_sf_muons_iso_down", 20, 10, 300);
  TH1D hist_225 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_ljets_id_up").c_str(), "W_elnu_tlv_M_weight_sf_ljets_id_up", 20, 10, 300);
  TH1D hist_226 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_ljets_id_down").c_str(), "W_elnu_tlv_M_weight_sf_ljets_id_down", 20, 10, 300);
  TH1D hist_227 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_ljets_btag_up").c_str(), "W_elnu_tlv_M_weight_sf_ljets_btag_up", 20, 10, 300);
  TH1D hist_228 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_ljets_btag_down").c_str(), "W_elnu_tlv_M_weight_sf_ljets_btag_down", 20, 10, 300);
  TH1D hist_229 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_bjets_id_up").c_str(), "W_elnu_tlv_M_weight_sf_bjets_id_up", 20, 10, 300);
  TH1D hist_230 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_bjets_id_down").c_str(), "W_elnu_tlv_M_weight_sf_bjets_id_down", 20, 10, 300);
  TH1D hist_231 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_pileup_up").c_str(), "W_elnu_tlv_M_weight_sf_pileup_up", 20, 10, 300);
  TH1D hist_232 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_sf_pileup_down").c_str(), "W_elnu_tlv_M_weight_sf_pileup_down", 20, 10, 300);
  TH1D hist_233 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_FracRV_up").c_str(), "W_elnu_tlv_M_weight_FracRV_up", 20, 10, 300);
  TH1D hist_234 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_FracRV_down").c_str(), "W_elnu_tlv_M_weight_FracRV_down", 20, 10, 300);
  TH1D hist_235 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_LooseMvaSF_up").c_str(), "W_elnu_tlv_M_weight_LooseMvaSF_up", 20, 10, 300);
  TH1D hist_236 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_LooseMvaSF_down").c_str(), "W_elnu_tlv_M_weight_LooseMvaSF_down", 20, 10, 300);
  TH1D hist_237 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_PreselSF_up").c_str(), "W_elnu_tlv_M_weight_PreselSF_up", 20, 10, 300);
  TH1D hist_238 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_PreselSF_down").c_str(), "W_elnu_tlv_M_weight_PreselSF_down", 20, 10, 300);
  TH1D hist_239 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_Trigger_up").c_str(), "W_elnu_tlv_M_weight_Trigger_up", 20, 10, 300);
  TH1D hist_240 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_Trigger_down").c_str(), "W_elnu_tlv_M_weight_Trigger_down", 20, 10, 300);
  TH1D hist_241 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_electronVetoSF_up").c_str(), "W_elnu_tlv_M_weight_electronVetoSF_up", 20, 10, 300);
  TH1D hist_242 = TH1D((dataset->process_name + "_W_elnu_tlv_M_weight_electronVetoSF_down").c_str(), "W_elnu_tlv_M_weight_electronVetoSF_down", 20, 10, 300);
  TH1D hist_243 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight").c_str(), "W_jj_tlv_M_weight", 20, 10, 300);
  TH1D hist_244 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_photons_up").c_str(), "W_jj_tlv_M_weight_sf_photons_up", 20, 10, 300);
  TH1D hist_245 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_photons_down").c_str(), "W_jj_tlv_M_weight_sf_photons_down", 20, 10, 300);
  TH1D hist_246 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_electrons_up").c_str(), "W_jj_tlv_M_weight_sf_electrons_up", 20, 10, 300);
  TH1D hist_247 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_electrons_down").c_str(), "W_jj_tlv_M_weight_sf_electrons_down", 20, 10, 300);
  TH1D hist_248 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_muons_id_up").c_str(), "W_jj_tlv_M_weight_sf_muons_id_up", 20, 10, 300);
  TH1D hist_249 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_muons_id_down").c_str(), "W_jj_tlv_M_weight_sf_muons_id_down", 20, 10, 300);
  TH1D hist_250 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_muons_iso_up").c_str(), "W_jj_tlv_M_weight_sf_muons_iso_up", 20, 10, 300);
  TH1D hist_251 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_muons_iso_down").c_str(), "W_jj_tlv_M_weight_sf_muons_iso_down", 20, 10, 300);
  TH1D hist_252 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_ljets_id_up").c_str(), "W_jj_tlv_M_weight_sf_ljets_id_up", 20, 10, 300);
  TH1D hist_253 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_ljets_id_down").c_str(), "W_jj_tlv_M_weight_sf_ljets_id_down", 20, 10, 300);
  TH1D hist_254 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_ljets_btag_up").c_str(), "W_jj_tlv_M_weight_sf_ljets_btag_up", 20, 10, 300);
  TH1D hist_255 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_ljets_btag_down").c_str(), "W_jj_tlv_M_weight_sf_ljets_btag_down", 20, 10, 300);
  TH1D hist_256 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_bjets_id_up").c_str(), "W_jj_tlv_M_weight_sf_bjets_id_up", 20, 10, 300);
  TH1D hist_257 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_bjets_id_down").c_str(), "W_jj_tlv_M_weight_sf_bjets_id_down", 20, 10, 300);
  TH1D hist_258 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_pileup_up").c_str(), "W_jj_tlv_M_weight_sf_pileup_up", 20, 10, 300);
  TH1D hist_259 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_sf_pileup_down").c_str(), "W_jj_tlv_M_weight_sf_pileup_down", 20, 10, 300);
  TH1D hist_260 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_FracRV_up").c_str(), "W_jj_tlv_M_weight_FracRV_up", 20, 10, 300);
  TH1D hist_261 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_FracRV_down").c_str(), "W_jj_tlv_M_weight_FracRV_down", 20, 10, 300);
  TH1D hist_262 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_LooseMvaSF_up").c_str(), "W_jj_tlv_M_weight_LooseMvaSF_up", 20, 10, 300);
  TH1D hist_263 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_LooseMvaSF_down").c_str(), "W_jj_tlv_M_weight_LooseMvaSF_down", 20, 10, 300);
  TH1D hist_264 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_PreselSF_up").c_str(), "W_jj_tlv_M_weight_PreselSF_up", 20, 10, 300);
  TH1D hist_265 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_PreselSF_down").c_str(), "W_jj_tlv_M_weight_PreselSF_down", 20, 10, 300);
  TH1D hist_266 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_Trigger_up").c_str(), "W_jj_tlv_M_weight_Trigger_up", 20, 10, 300);
  TH1D hist_267 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_Trigger_down").c_str(), "W_jj_tlv_M_weight_Trigger_down", 20, 10, 300);
  TH1D hist_268 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_electronVetoSF_up").c_str(), "W_jj_tlv_M_weight_electronVetoSF_up", 20, 10, 300);
  TH1D hist_269 = TH1D((dataset->process_name + "_W_jj_tlv_M_weight_electronVetoSF_down").c_str(), "W_jj_tlv_M_weight_electronVetoSF_down", 20, 10, 300);
  TH1D hist_270 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight").c_str(), "H_WW_tlv_M_weight", 20, 10, 1000);
  TH1D hist_271 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_photons_up").c_str(), "H_WW_tlv_M_weight_sf_photons_up", 20, 10, 1000);
  TH1D hist_272 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_photons_down").c_str(), "H_WW_tlv_M_weight_sf_photons_down", 20, 10, 1000);
  TH1D hist_273 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_electrons_up").c_str(), "H_WW_tlv_M_weight_sf_electrons_up", 20, 10, 1000);
  TH1D hist_274 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_electrons_down").c_str(), "H_WW_tlv_M_weight_sf_electrons_down", 20, 10, 1000);
  TH1D hist_275 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_id_up").c_str(), "H_WW_tlv_M_weight_sf_muons_id_up", 20, 10, 1000);
  TH1D hist_276 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_id_down").c_str(), "H_WW_tlv_M_weight_sf_muons_id_down", 20, 10, 1000);
  TH1D hist_277 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_iso_up").c_str(), "H_WW_tlv_M_weight_sf_muons_iso_up", 20, 10, 1000);
  TH1D hist_278 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_muons_iso_down").c_str(), "H_WW_tlv_M_weight_sf_muons_iso_down", 20, 10, 1000);
  TH1D hist_279 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_id_up").c_str(), "H_WW_tlv_M_weight_sf_ljets_id_up", 20, 10, 1000);
  TH1D hist_280 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_id_down").c_str(), "H_WW_tlv_M_weight_sf_ljets_id_down", 20, 10, 1000);
  TH1D hist_281 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_btag_up").c_str(), "H_WW_tlv_M_weight_sf_ljets_btag_up", 20, 10, 1000);
  TH1D hist_282 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_ljets_btag_down").c_str(), "H_WW_tlv_M_weight_sf_ljets_btag_down", 20, 10, 1000);
  TH1D hist_283 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_bjets_id_up").c_str(), "H_WW_tlv_M_weight_sf_bjets_id_up", 20, 10, 1000);
  TH1D hist_284 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_bjets_id_down").c_str(), "H_WW_tlv_M_weight_sf_bjets_id_down", 20, 10, 1000);
  TH1D hist_285 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_pileup_up").c_str(), "H_WW_tlv_M_weight_sf_pileup_up", 20, 10, 1000);
  TH1D hist_286 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_sf_pileup_down").c_str(), "H_WW_tlv_M_weight_sf_pileup_down", 20, 10, 1000);
  TH1D hist_287 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_FracRV_up").c_str(), "H_WW_tlv_M_weight_FracRV_up", 20, 10, 1000);
  TH1D hist_288 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_FracRV_down").c_str(), "H_WW_tlv_M_weight_FracRV_down", 20, 10, 1000);
  TH1D hist_289 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_LooseMvaSF_up").c_str(), "H_WW_tlv_M_weight_LooseMvaSF_up", 20, 10, 1000);
  TH1D hist_290 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_LooseMvaSF_down").c_str(), "H_WW_tlv_M_weight_LooseMvaSF_down", 20, 10, 1000);
  TH1D hist_291 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_PreselSF_up").c_str(), "H_WW_tlv_M_weight_PreselSF_up", 20, 10, 1000);
  TH1D hist_292 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_PreselSF_down").c_str(), "H_WW_tlv_M_weight_PreselSF_down", 20, 10, 1000);
  TH1D hist_293 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_Trigger_up").c_str(), "H_WW_tlv_M_weight_Trigger_up", 20, 10, 1000);
  TH1D hist_294 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_Trigger_down").c_str(), "H_WW_tlv_M_weight_Trigger_down", 20, 10, 1000);
  TH1D hist_295 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_electronVetoSF_up").c_str(), "H_WW_tlv_M_weight_electronVetoSF_up", 20, 10, 1000);
  TH1D hist_296 = TH1D((dataset->process_name + "_H_WW_tlv_M_weight_electronVetoSF_down").c_str(), "H_WW_tlv_M_weight_electronVetoSF_down", 20, 10, 1000);
  TH1D hist_297 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight").c_str(), "gen_HHi_tlv_M_weight", 20, 0, 1200);
  TH1D hist_298 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_photons_up").c_str(), "gen_HHi_tlv_M_weight_sf_photons_up", 20, 0, 1200);
  TH1D hist_299 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_photons_down").c_str(), "gen_HHi_tlv_M_weight_sf_photons_down", 20, 0, 1200);
  TH1D hist_300 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_electrons_up").c_str(), "gen_HHi_tlv_M_weight_sf_electrons_up", 20, 0, 1200);
  TH1D hist_301 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_electrons_down").c_str(), "gen_HHi_tlv_M_weight_sf_electrons_down", 20, 0, 1200);
  TH1D hist_302 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_muons_id_up").c_str(), "gen_HHi_tlv_M_weight_sf_muons_id_up", 20, 0, 1200);
  TH1D hist_303 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_muons_id_down").c_str(), "gen_HHi_tlv_M_weight_sf_muons_id_down", 20, 0, 1200);
  TH1D hist_304 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_muons_iso_up").c_str(), "gen_HHi_tlv_M_weight_sf_muons_iso_up", 20, 0, 1200);
  TH1D hist_305 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_muons_iso_down").c_str(), "gen_HHi_tlv_M_weight_sf_muons_iso_down", 20, 0, 1200);
  TH1D hist_306 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_ljets_id_up").c_str(), "gen_HHi_tlv_M_weight_sf_ljets_id_up", 20, 0, 1200);
  TH1D hist_307 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_ljets_id_down").c_str(), "gen_HHi_tlv_M_weight_sf_ljets_id_down", 20, 0, 1200);
  TH1D hist_308 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_ljets_btag_up").c_str(), "gen_HHi_tlv_M_weight_sf_ljets_btag_up", 20, 0, 1200);
  TH1D hist_309 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_ljets_btag_down").c_str(), "gen_HHi_tlv_M_weight_sf_ljets_btag_down", 20, 0, 1200);
  TH1D hist_310 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_bjets_id_up").c_str(), "gen_HHi_tlv_M_weight_sf_bjets_id_up", 20, 0, 1200);
  TH1D hist_311 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_bjets_id_down").c_str(), "gen_HHi_tlv_M_weight_sf_bjets_id_down", 20, 0, 1200);
  TH1D hist_312 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_pileup_up").c_str(), "gen_HHi_tlv_M_weight_sf_pileup_up", 20, 0, 1200);
  TH1D hist_313 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_sf_pileup_down").c_str(), "gen_HHi_tlv_M_weight_sf_pileup_down", 20, 0, 1200);
  TH1D hist_314 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_FracRV_up").c_str(), "gen_HHi_tlv_M_weight_FracRV_up", 20, 0, 1200);
  TH1D hist_315 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_FracRV_down").c_str(), "gen_HHi_tlv_M_weight_FracRV_down", 20, 0, 1200);
  TH1D hist_316 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_LooseMvaSF_up").c_str(), "gen_HHi_tlv_M_weight_LooseMvaSF_up", 20, 0, 1200);
  TH1D hist_317 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_LooseMvaSF_down").c_str(), "gen_HHi_tlv_M_weight_LooseMvaSF_down", 20, 0, 1200);
  TH1D hist_318 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_PreselSF_up").c_str(), "gen_HHi_tlv_M_weight_PreselSF_up", 20, 0, 1200);
  TH1D hist_319 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_PreselSF_down").c_str(), "gen_HHi_tlv_M_weight_PreselSF_down", 20, 0, 1200);
  TH1D hist_320 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_Trigger_up").c_str(), "gen_HHi_tlv_M_weight_Trigger_up", 20, 0, 1200);
  TH1D hist_321 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_Trigger_down").c_str(), "gen_HHi_tlv_M_weight_Trigger_down", 20, 0, 1200);
  TH1D hist_322 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_electronVetoSF_up").c_str(), "gen_HHi_tlv_M_weight_electronVetoSF_up", 20, 0, 1200);
  TH1D hist_323 = TH1D((dataset->process_name + "_gen_HHi_tlv_M_weight_electronVetoSF_down").c_str(), "gen_HHi_tlv_M_weight_electronVetoSF_down", 20, 0, 1200);
  TH1D hist_324 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight").c_str(), "gen_Hi_yy_tlv_CosTheta_weight", 20, 0, 1);
  TH1D hist_325 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_photons_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_photons_up", 20, 0, 1);
  TH1D hist_326 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_photons_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_photons_down", 20, 0, 1);
  TH1D hist_327 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_electrons_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_electrons_up", 20, 0, 1);
  TH1D hist_328 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_electrons_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_electrons_down", 20, 0, 1);
  TH1D hist_329 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_muons_id_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_muons_id_up", 20, 0, 1);
  TH1D hist_330 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_muons_id_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_muons_id_down", 20, 0, 1);
  TH1D hist_331 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_muons_iso_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_muons_iso_up", 20, 0, 1);
  TH1D hist_332 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_muons_iso_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_muons_iso_down", 20, 0, 1);
  TH1D hist_333 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_id_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_id_up", 20, 0, 1);
  TH1D hist_334 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_id_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_id_down", 20, 0, 1);
  TH1D hist_335 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_btag_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_btag_up", 20, 0, 1);
  TH1D hist_336 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_btag_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_ljets_btag_down", 20, 0, 1);
  TH1D hist_337 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_bjets_id_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_bjets_id_up", 20, 0, 1);
  TH1D hist_338 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_bjets_id_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_bjets_id_down", 20, 0, 1);
  TH1D hist_339 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_pileup_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_pileup_up", 20, 0, 1);
  TH1D hist_340 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_sf_pileup_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_sf_pileup_down", 20, 0, 1);
  TH1D hist_341 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_FracRV_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_FracRV_up", 20, 0, 1);
  TH1D hist_342 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_FracRV_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_FracRV_down", 20, 0, 1);
  TH1D hist_343 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_LooseMvaSF_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_LooseMvaSF_up", 20, 0, 1);
  TH1D hist_344 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_LooseMvaSF_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_LooseMvaSF_down", 20, 0, 1);
  TH1D hist_345 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_PreselSF_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_PreselSF_up", 20, 0, 1);
  TH1D hist_346 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_PreselSF_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_PreselSF_down", 20, 0, 1);
  TH1D hist_347 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_Trigger_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_Trigger_up", 20, 0, 1);
  TH1D hist_348 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_Trigger_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_Trigger_down", 20, 0, 1);
  TH1D hist_349 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_electronVetoSF_up").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_electronVetoSF_up", 20, 0, 1);
  TH1D hist_350 = TH1D((dataset->process_name + "_gen_Hi_yy_tlv_CosTheta_weight_electronVetoSF_down").c_str(), "gen_Hi_yy_tlv_CosTheta_weight_electronVetoSF_down", 20, 0, 1);
  TH1D hist_351 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight").c_str(), "dR_genreco_W_jj_weight", 20, 0, 5);
  TH1D hist_352 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_photons_up").c_str(), "dR_genreco_W_jj_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_353 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_photons_down").c_str(), "dR_genreco_W_jj_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_354 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_electrons_up").c_str(), "dR_genreco_W_jj_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_355 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_electrons_down").c_str(), "dR_genreco_W_jj_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_356 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_muons_id_up").c_str(), "dR_genreco_W_jj_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_357 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_muons_id_down").c_str(), "dR_genreco_W_jj_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_358 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_muons_iso_up").c_str(), "dR_genreco_W_jj_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_359 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_muons_iso_down").c_str(), "dR_genreco_W_jj_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_360 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_ljets_id_up").c_str(), "dR_genreco_W_jj_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_361 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_ljets_id_down").c_str(), "dR_genreco_W_jj_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_362 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_ljets_btag_up").c_str(), "dR_genreco_W_jj_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_363 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_ljets_btag_down").c_str(), "dR_genreco_W_jj_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_364 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_bjets_id_up").c_str(), "dR_genreco_W_jj_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_365 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_bjets_id_down").c_str(), "dR_genreco_W_jj_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_366 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_pileup_up").c_str(), "dR_genreco_W_jj_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_367 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_sf_pileup_down").c_str(), "dR_genreco_W_jj_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_368 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_FracRV_up").c_str(), "dR_genreco_W_jj_weight_FracRV_up", 20, 0, 5);
  TH1D hist_369 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_FracRV_down").c_str(), "dR_genreco_W_jj_weight_FracRV_down", 20, 0, 5);
  TH1D hist_370 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_LooseMvaSF_up").c_str(), "dR_genreco_W_jj_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_371 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_LooseMvaSF_down").c_str(), "dR_genreco_W_jj_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_372 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_PreselSF_up").c_str(), "dR_genreco_W_jj_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_373 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_PreselSF_down").c_str(), "dR_genreco_W_jj_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_374 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_Trigger_up").c_str(), "dR_genreco_W_jj_weight_Trigger_up", 20, 0, 5);
  TH1D hist_375 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_Trigger_down").c_str(), "dR_genreco_W_jj_weight_Trigger_down", 20, 0, 5);
  TH1D hist_376 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_electronVetoSF_up").c_str(), "dR_genreco_W_jj_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_377 = TH1D((dataset->process_name + "_dR_genreco_W_jj_weight_electronVetoSF_down").c_str(), "dR_genreco_W_jj_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_378 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight").c_str(), "dR_genreco_W_jj_leading_weight", 20, 0, 5);
  TH1D hist_379 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_photons_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_380 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_photons_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_381 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_electrons_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_382 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_electrons_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_383 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_muons_id_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_384 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_muons_id_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_385 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_muons_iso_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_386 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_muons_iso_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_387 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_ljets_id_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_388 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_ljets_id_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_389 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_ljets_btag_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_390 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_ljets_btag_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_391 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_bjets_id_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_392 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_bjets_id_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_393 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_pileup_up").c_str(), "dR_genreco_W_jj_leading_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_394 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_sf_pileup_down").c_str(), "dR_genreco_W_jj_leading_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_395 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_FracRV_up").c_str(), "dR_genreco_W_jj_leading_weight_FracRV_up", 20, 0, 5);
  TH1D hist_396 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_FracRV_down").c_str(), "dR_genreco_W_jj_leading_weight_FracRV_down", 20, 0, 5);
  TH1D hist_397 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_LooseMvaSF_up").c_str(), "dR_genreco_W_jj_leading_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_398 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_LooseMvaSF_down").c_str(), "dR_genreco_W_jj_leading_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_399 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_PreselSF_up").c_str(), "dR_genreco_W_jj_leading_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_400 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_PreselSF_down").c_str(), "dR_genreco_W_jj_leading_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_401 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_Trigger_up").c_str(), "dR_genreco_W_jj_leading_weight_Trigger_up", 20, 0, 5);
  TH1D hist_402 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_Trigger_down").c_str(), "dR_genreco_W_jj_leading_weight_Trigger_down", 20, 0, 5);
  TH1D hist_403 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_electronVetoSF_up").c_str(), "dR_genreco_W_jj_leading_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_404 = TH1D((dataset->process_name + "_dR_genreco_W_jj_leading_weight_electronVetoSF_down").c_str(), "dR_genreco_W_jj_leading_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_405 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight").c_str(), "dP_genreco_W_jj_weight", 20, 0, 600);
  TH1D hist_406 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_photons_up").c_str(), "dP_genreco_W_jj_weight_sf_photons_up", 20, 0, 600);
  TH1D hist_407 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_photons_down").c_str(), "dP_genreco_W_jj_weight_sf_photons_down", 20, 0, 600);
  TH1D hist_408 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_electrons_up").c_str(), "dP_genreco_W_jj_weight_sf_electrons_up", 20, 0, 600);
  TH1D hist_409 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_electrons_down").c_str(), "dP_genreco_W_jj_weight_sf_electrons_down", 20, 0, 600);
  TH1D hist_410 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_muons_id_up").c_str(), "dP_genreco_W_jj_weight_sf_muons_id_up", 20, 0, 600);
  TH1D hist_411 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_muons_id_down").c_str(), "dP_genreco_W_jj_weight_sf_muons_id_down", 20, 0, 600);
  TH1D hist_412 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_muons_iso_up").c_str(), "dP_genreco_W_jj_weight_sf_muons_iso_up", 20, 0, 600);
  TH1D hist_413 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_muons_iso_down").c_str(), "dP_genreco_W_jj_weight_sf_muons_iso_down", 20, 0, 600);
  TH1D hist_414 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_ljets_id_up").c_str(), "dP_genreco_W_jj_weight_sf_ljets_id_up", 20, 0, 600);
  TH1D hist_415 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_ljets_id_down").c_str(), "dP_genreco_W_jj_weight_sf_ljets_id_down", 20, 0, 600);
  TH1D hist_416 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_ljets_btag_up").c_str(), "dP_genreco_W_jj_weight_sf_ljets_btag_up", 20, 0, 600);
  TH1D hist_417 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_ljets_btag_down").c_str(), "dP_genreco_W_jj_weight_sf_ljets_btag_down", 20, 0, 600);
  TH1D hist_418 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_bjets_id_up").c_str(), "dP_genreco_W_jj_weight_sf_bjets_id_up", 20, 0, 600);
  TH1D hist_419 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_bjets_id_down").c_str(), "dP_genreco_W_jj_weight_sf_bjets_id_down", 20, 0, 600);
  TH1D hist_420 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_pileup_up").c_str(), "dP_genreco_W_jj_weight_sf_pileup_up", 20, 0, 600);
  TH1D hist_421 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_sf_pileup_down").c_str(), "dP_genreco_W_jj_weight_sf_pileup_down", 20, 0, 600);
  TH1D hist_422 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_FracRV_up").c_str(), "dP_genreco_W_jj_weight_FracRV_up", 20, 0, 600);
  TH1D hist_423 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_FracRV_down").c_str(), "dP_genreco_W_jj_weight_FracRV_down", 20, 0, 600);
  TH1D hist_424 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_LooseMvaSF_up").c_str(), "dP_genreco_W_jj_weight_LooseMvaSF_up", 20, 0, 600);
  TH1D hist_425 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_LooseMvaSF_down").c_str(), "dP_genreco_W_jj_weight_LooseMvaSF_down", 20, 0, 600);
  TH1D hist_426 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_PreselSF_up").c_str(), "dP_genreco_W_jj_weight_PreselSF_up", 20, 0, 600);
  TH1D hist_427 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_PreselSF_down").c_str(), "dP_genreco_W_jj_weight_PreselSF_down", 20, 0, 600);
  TH1D hist_428 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_Trigger_up").c_str(), "dP_genreco_W_jj_weight_Trigger_up", 20, 0, 600);
  TH1D hist_429 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_Trigger_down").c_str(), "dP_genreco_W_jj_weight_Trigger_down", 20, 0, 600);
  TH1D hist_430 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_electronVetoSF_up").c_str(), "dP_genreco_W_jj_weight_electronVetoSF_up", 20, 0, 600);
  TH1D hist_431 = TH1D((dataset->process_name + "_dP_genreco_W_jj_weight_electronVetoSF_down").c_str(), "dP_genreco_W_jj_weight_electronVetoSF_down", 20, 0, 600);
  TH1D hist_432 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight").c_str(), "dP_genreco_W_jj_leading_weight", 20, 0, 600);
  TH1D hist_433 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_photons_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_photons_up", 20, 0, 600);
  TH1D hist_434 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_photons_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_photons_down", 20, 0, 600);
  TH1D hist_435 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_electrons_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_electrons_up", 20, 0, 600);
  TH1D hist_436 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_electrons_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_electrons_down", 20, 0, 600);
  TH1D hist_437 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_muons_id_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_muons_id_up", 20, 0, 600);
  TH1D hist_438 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_muons_id_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_muons_id_down", 20, 0, 600);
  TH1D hist_439 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_muons_iso_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_muons_iso_up", 20, 0, 600);
  TH1D hist_440 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_muons_iso_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_muons_iso_down", 20, 0, 600);
  TH1D hist_441 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_ljets_id_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_ljets_id_up", 20, 0, 600);
  TH1D hist_442 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_ljets_id_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_ljets_id_down", 20, 0, 600);
  TH1D hist_443 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_ljets_btag_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_ljets_btag_up", 20, 0, 600);
  TH1D hist_444 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_ljets_btag_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_ljets_btag_down", 20, 0, 600);
  TH1D hist_445 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_bjets_id_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_bjets_id_up", 20, 0, 600);
  TH1D hist_446 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_bjets_id_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_bjets_id_down", 20, 0, 600);
  TH1D hist_447 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_pileup_up").c_str(), "dP_genreco_W_jj_leading_weight_sf_pileup_up", 20, 0, 600);
  TH1D hist_448 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_sf_pileup_down").c_str(), "dP_genreco_W_jj_leading_weight_sf_pileup_down", 20, 0, 600);
  TH1D hist_449 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_FracRV_up").c_str(), "dP_genreco_W_jj_leading_weight_FracRV_up", 20, 0, 600);
  TH1D hist_450 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_FracRV_down").c_str(), "dP_genreco_W_jj_leading_weight_FracRV_down", 20, 0, 600);
  TH1D hist_451 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_LooseMvaSF_up").c_str(), "dP_genreco_W_jj_leading_weight_LooseMvaSF_up", 20, 0, 600);
  TH1D hist_452 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_LooseMvaSF_down").c_str(), "dP_genreco_W_jj_leading_weight_LooseMvaSF_down", 20, 0, 600);
  TH1D hist_453 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_PreselSF_up").c_str(), "dP_genreco_W_jj_leading_weight_PreselSF_up", 20, 0, 600);
  TH1D hist_454 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_PreselSF_down").c_str(), "dP_genreco_W_jj_leading_weight_PreselSF_down", 20, 0, 600);
  TH1D hist_455 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_Trigger_up").c_str(), "dP_genreco_W_jj_leading_weight_Trigger_up", 20, 0, 600);
  TH1D hist_456 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_Trigger_down").c_str(), "dP_genreco_W_jj_leading_weight_Trigger_down", 20, 0, 600);
  TH1D hist_457 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_electronVetoSF_up").c_str(), "dP_genreco_W_jj_leading_weight_electronVetoSF_up", 20, 0, 600);
  TH1D hist_458 = TH1D((dataset->process_name + "_dP_genreco_W_jj_leading_weight_electronVetoSF_down").c_str(), "dP_genreco_W_jj_leading_weight_electronVetoSF_down", 20, 0, 600);
  TH1D hist_459 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight").c_str(), "W_jj_tlv_leading_M_weight", 20, 10, 300);
  TH1D hist_460 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_photons_up").c_str(), "W_jj_tlv_leading_M_weight_sf_photons_up", 20, 10, 300);
  TH1D hist_461 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_photons_down").c_str(), "W_jj_tlv_leading_M_weight_sf_photons_down", 20, 10, 300);
  TH1D hist_462 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_electrons_up").c_str(), "W_jj_tlv_leading_M_weight_sf_electrons_up", 20, 10, 300);
  TH1D hist_463 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_electrons_down").c_str(), "W_jj_tlv_leading_M_weight_sf_electrons_down", 20, 10, 300);
  TH1D hist_464 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_muons_id_up").c_str(), "W_jj_tlv_leading_M_weight_sf_muons_id_up", 20, 10, 300);
  TH1D hist_465 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_muons_id_down").c_str(), "W_jj_tlv_leading_M_weight_sf_muons_id_down", 20, 10, 300);
  TH1D hist_466 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_muons_iso_up").c_str(), "W_jj_tlv_leading_M_weight_sf_muons_iso_up", 20, 10, 300);
  TH1D hist_467 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_muons_iso_down").c_str(), "W_jj_tlv_leading_M_weight_sf_muons_iso_down", 20, 10, 300);
  TH1D hist_468 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_ljets_id_up").c_str(), "W_jj_tlv_leading_M_weight_sf_ljets_id_up", 20, 10, 300);
  TH1D hist_469 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_ljets_id_down").c_str(), "W_jj_tlv_leading_M_weight_sf_ljets_id_down", 20, 10, 300);
  TH1D hist_470 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_ljets_btag_up").c_str(), "W_jj_tlv_leading_M_weight_sf_ljets_btag_up", 20, 10, 300);
  TH1D hist_471 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_ljets_btag_down").c_str(), "W_jj_tlv_leading_M_weight_sf_ljets_btag_down", 20, 10, 300);
  TH1D hist_472 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_bjets_id_up").c_str(), "W_jj_tlv_leading_M_weight_sf_bjets_id_up", 20, 10, 300);
  TH1D hist_473 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_bjets_id_down").c_str(), "W_jj_tlv_leading_M_weight_sf_bjets_id_down", 20, 10, 300);
  TH1D hist_474 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_pileup_up").c_str(), "W_jj_tlv_leading_M_weight_sf_pileup_up", 20, 10, 300);
  TH1D hist_475 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_sf_pileup_down").c_str(), "W_jj_tlv_leading_M_weight_sf_pileup_down", 20, 10, 300);
  TH1D hist_476 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_FracRV_up").c_str(), "W_jj_tlv_leading_M_weight_FracRV_up", 20, 10, 300);
  TH1D hist_477 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_FracRV_down").c_str(), "W_jj_tlv_leading_M_weight_FracRV_down", 20, 10, 300);
  TH1D hist_478 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_LooseMvaSF_up").c_str(), "W_jj_tlv_leading_M_weight_LooseMvaSF_up", 20, 10, 300);
  TH1D hist_479 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_LooseMvaSF_down").c_str(), "W_jj_tlv_leading_M_weight_LooseMvaSF_down", 20, 10, 300);
  TH1D hist_480 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_PreselSF_up").c_str(), "W_jj_tlv_leading_M_weight_PreselSF_up", 20, 10, 300);
  TH1D hist_481 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_PreselSF_down").c_str(), "W_jj_tlv_leading_M_weight_PreselSF_down", 20, 10, 300);
  TH1D hist_482 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_Trigger_up").c_str(), "W_jj_tlv_leading_M_weight_Trigger_up", 20, 10, 300);
  TH1D hist_483 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_Trigger_down").c_str(), "W_jj_tlv_leading_M_weight_Trigger_down", 20, 10, 300);
  TH1D hist_484 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_electronVetoSF_up").c_str(), "W_jj_tlv_leading_M_weight_electronVetoSF_up", 20, 10, 300);
  TH1D hist_485 = TH1D((dataset->process_name + "_W_jj_tlv_leading_M_weight_electronVetoSF_down").c_str(), "W_jj_tlv_leading_M_weight_electronVetoSF_down", 20, 10, 300);
  TH1D hist_486 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight").c_str(), "dR_genreco_H_yy_weight", 20, 0, 2);
  TH1D hist_487 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_photons_up").c_str(), "dR_genreco_H_yy_weight_sf_photons_up", 20, 0, 2);
  TH1D hist_488 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_photons_down").c_str(), "dR_genreco_H_yy_weight_sf_photons_down", 20, 0, 2);
  TH1D hist_489 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_electrons_up").c_str(), "dR_genreco_H_yy_weight_sf_electrons_up", 20, 0, 2);
  TH1D hist_490 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_electrons_down").c_str(), "dR_genreco_H_yy_weight_sf_electrons_down", 20, 0, 2);
  TH1D hist_491 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_muons_id_up").c_str(), "dR_genreco_H_yy_weight_sf_muons_id_up", 20, 0, 2);
  TH1D hist_492 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_muons_id_down").c_str(), "dR_genreco_H_yy_weight_sf_muons_id_down", 20, 0, 2);
  TH1D hist_493 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_muons_iso_up").c_str(), "dR_genreco_H_yy_weight_sf_muons_iso_up", 20, 0, 2);
  TH1D hist_494 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_muons_iso_down").c_str(), "dR_genreco_H_yy_weight_sf_muons_iso_down", 20, 0, 2);
  TH1D hist_495 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_ljets_id_up").c_str(), "dR_genreco_H_yy_weight_sf_ljets_id_up", 20, 0, 2);
  TH1D hist_496 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_ljets_id_down").c_str(), "dR_genreco_H_yy_weight_sf_ljets_id_down", 20, 0, 2);
  TH1D hist_497 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_ljets_btag_up").c_str(), "dR_genreco_H_yy_weight_sf_ljets_btag_up", 20, 0, 2);
  TH1D hist_498 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_ljets_btag_down").c_str(), "dR_genreco_H_yy_weight_sf_ljets_btag_down", 20, 0, 2);
  TH1D hist_499 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_bjets_id_up").c_str(), "dR_genreco_H_yy_weight_sf_bjets_id_up", 20, 0, 2);
  TH1D hist_500 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_bjets_id_down").c_str(), "dR_genreco_H_yy_weight_sf_bjets_id_down", 20, 0, 2);
  TH1D hist_501 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_pileup_up").c_str(), "dR_genreco_H_yy_weight_sf_pileup_up", 20, 0, 2);
  TH1D hist_502 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_sf_pileup_down").c_str(), "dR_genreco_H_yy_weight_sf_pileup_down", 20, 0, 2);
  TH1D hist_503 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_FracRV_up").c_str(), "dR_genreco_H_yy_weight_FracRV_up", 20, 0, 2);
  TH1D hist_504 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_FracRV_down").c_str(), "dR_genreco_H_yy_weight_FracRV_down", 20, 0, 2);
  TH1D hist_505 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_LooseMvaSF_up").c_str(), "dR_genreco_H_yy_weight_LooseMvaSF_up", 20, 0, 2);
  TH1D hist_506 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_LooseMvaSF_down").c_str(), "dR_genreco_H_yy_weight_LooseMvaSF_down", 20, 0, 2);
  TH1D hist_507 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_PreselSF_up").c_str(), "dR_genreco_H_yy_weight_PreselSF_up", 20, 0, 2);
  TH1D hist_508 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_PreselSF_down").c_str(), "dR_genreco_H_yy_weight_PreselSF_down", 20, 0, 2);
  TH1D hist_509 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_Trigger_up").c_str(), "dR_genreco_H_yy_weight_Trigger_up", 20, 0, 2);
  TH1D hist_510 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_Trigger_down").c_str(), "dR_genreco_H_yy_weight_Trigger_down", 20, 0, 2);
  TH1D hist_511 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_electronVetoSF_up").c_str(), "dR_genreco_H_yy_weight_electronVetoSF_up", 20, 0, 2);
  TH1D hist_512 = TH1D((dataset->process_name + "_dR_genreco_H_yy_weight_electronVetoSF_down").c_str(), "dR_genreco_H_yy_weight_electronVetoSF_down", 20, 0, 2);
  TH1D hist_513 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight").c_str(), "dR_genreco_H_WW_weight", 20, 0, 5);
  TH1D hist_514 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_photons_up").c_str(), "dR_genreco_H_WW_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_515 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_photons_down").c_str(), "dR_genreco_H_WW_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_516 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_electrons_up").c_str(), "dR_genreco_H_WW_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_517 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_electrons_down").c_str(), "dR_genreco_H_WW_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_518 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_muons_id_up").c_str(), "dR_genreco_H_WW_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_519 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_muons_id_down").c_str(), "dR_genreco_H_WW_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_520 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_muons_iso_up").c_str(), "dR_genreco_H_WW_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_521 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_muons_iso_down").c_str(), "dR_genreco_H_WW_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_522 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_ljets_id_up").c_str(), "dR_genreco_H_WW_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_523 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_ljets_id_down").c_str(), "dR_genreco_H_WW_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_524 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_ljets_btag_up").c_str(), "dR_genreco_H_WW_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_525 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_ljets_btag_down").c_str(), "dR_genreco_H_WW_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_526 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_bjets_id_up").c_str(), "dR_genreco_H_WW_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_527 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_bjets_id_down").c_str(), "dR_genreco_H_WW_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_528 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_pileup_up").c_str(), "dR_genreco_H_WW_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_529 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_sf_pileup_down").c_str(), "dR_genreco_H_WW_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_530 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_FracRV_up").c_str(), "dR_genreco_H_WW_weight_FracRV_up", 20, 0, 5);
  TH1D hist_531 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_FracRV_down").c_str(), "dR_genreco_H_WW_weight_FracRV_down", 20, 0, 5);
  TH1D hist_532 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_LooseMvaSF_up").c_str(), "dR_genreco_H_WW_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_533 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_LooseMvaSF_down").c_str(), "dR_genreco_H_WW_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_534 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_PreselSF_up").c_str(), "dR_genreco_H_WW_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_535 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_PreselSF_down").c_str(), "dR_genreco_H_WW_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_536 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_Trigger_up").c_str(), "dR_genreco_H_WW_weight_Trigger_up", 20, 0, 5);
  TH1D hist_537 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_Trigger_down").c_str(), "dR_genreco_H_WW_weight_Trigger_down", 20, 0, 5);
  TH1D hist_538 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_electronVetoSF_up").c_str(), "dR_genreco_H_WW_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_539 = TH1D((dataset->process_name + "_dR_genreco_H_WW_weight_electronVetoSF_down").c_str(), "dR_genreco_H_WW_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_540 = TH1D((dataset->process_name + "_dR_genreco_nu_weight").c_str(), "dR_genreco_nu_weight", 20, 0, 5);
  TH1D hist_541 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_photons_up").c_str(), "dR_genreco_nu_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_542 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_photons_down").c_str(), "dR_genreco_nu_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_543 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_electrons_up").c_str(), "dR_genreco_nu_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_544 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_electrons_down").c_str(), "dR_genreco_nu_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_545 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_muons_id_up").c_str(), "dR_genreco_nu_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_546 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_muons_id_down").c_str(), "dR_genreco_nu_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_547 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_muons_iso_up").c_str(), "dR_genreco_nu_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_548 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_muons_iso_down").c_str(), "dR_genreco_nu_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_549 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_ljets_id_up").c_str(), "dR_genreco_nu_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_550 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_ljets_id_down").c_str(), "dR_genreco_nu_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_551 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_ljets_btag_up").c_str(), "dR_genreco_nu_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_552 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_ljets_btag_down").c_str(), "dR_genreco_nu_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_553 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_bjets_id_up").c_str(), "dR_genreco_nu_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_554 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_bjets_id_down").c_str(), "dR_genreco_nu_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_555 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_pileup_up").c_str(), "dR_genreco_nu_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_556 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_sf_pileup_down").c_str(), "dR_genreco_nu_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_557 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_FracRV_up").c_str(), "dR_genreco_nu_weight_FracRV_up", 20, 0, 5);
  TH1D hist_558 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_FracRV_down").c_str(), "dR_genreco_nu_weight_FracRV_down", 20, 0, 5);
  TH1D hist_559 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_LooseMvaSF_up").c_str(), "dR_genreco_nu_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_560 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_LooseMvaSF_down").c_str(), "dR_genreco_nu_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_561 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_PreselSF_up").c_str(), "dR_genreco_nu_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_562 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_PreselSF_down").c_str(), "dR_genreco_nu_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_563 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_Trigger_up").c_str(), "dR_genreco_nu_weight_Trigger_up", 20, 0, 5);
  TH1D hist_564 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_Trigger_down").c_str(), "dR_genreco_nu_weight_Trigger_down", 20, 0, 5);
  TH1D hist_565 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_electronVetoSF_up").c_str(), "dR_genreco_nu_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_566 = TH1D((dataset->process_name + "_dR_genreco_nu_weight_electronVetoSF_down").c_str(), "dR_genreco_nu_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_567 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight").c_str(), "dR_genreco_W_elnu_weight", 20, 0, 5);
  TH1D hist_568 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_photons_up").c_str(), "dR_genreco_W_elnu_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_569 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_photons_down").c_str(), "dR_genreco_W_elnu_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_570 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_electrons_up").c_str(), "dR_genreco_W_elnu_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_571 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_electrons_down").c_str(), "dR_genreco_W_elnu_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_572 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_muons_id_up").c_str(), "dR_genreco_W_elnu_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_573 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_muons_id_down").c_str(), "dR_genreco_W_elnu_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_574 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_muons_iso_up").c_str(), "dR_genreco_W_elnu_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_575 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_muons_iso_down").c_str(), "dR_genreco_W_elnu_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_576 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_ljets_id_up").c_str(), "dR_genreco_W_elnu_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_577 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_ljets_id_down").c_str(), "dR_genreco_W_elnu_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_578 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_ljets_btag_up").c_str(), "dR_genreco_W_elnu_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_579 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_ljets_btag_down").c_str(), "dR_genreco_W_elnu_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_580 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_bjets_id_up").c_str(), "dR_genreco_W_elnu_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_581 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_bjets_id_down").c_str(), "dR_genreco_W_elnu_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_582 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_pileup_up").c_str(), "dR_genreco_W_elnu_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_583 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_sf_pileup_down").c_str(), "dR_genreco_W_elnu_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_584 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_FracRV_up").c_str(), "dR_genreco_W_elnu_weight_FracRV_up", 20, 0, 5);
  TH1D hist_585 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_FracRV_down").c_str(), "dR_genreco_W_elnu_weight_FracRV_down", 20, 0, 5);
  TH1D hist_586 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_LooseMvaSF_up").c_str(), "dR_genreco_W_elnu_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_587 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_LooseMvaSF_down").c_str(), "dR_genreco_W_elnu_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_588 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_PreselSF_up").c_str(), "dR_genreco_W_elnu_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_589 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_PreselSF_down").c_str(), "dR_genreco_W_elnu_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_590 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_Trigger_up").c_str(), "dR_genreco_W_elnu_weight_Trigger_up", 20, 0, 5);
  TH1D hist_591 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_Trigger_down").c_str(), "dR_genreco_W_elnu_weight_Trigger_down", 20, 0, 5);
  TH1D hist_592 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_electronVetoSF_up").c_str(), "dR_genreco_W_elnu_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_593 = TH1D((dataset->process_name + "_dR_genreco_W_elnu_weight_electronVetoSF_down").c_str(), "dR_genreco_W_elnu_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_594 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight").c_str(), "dP_genreco_H_yy_weight", 20, 0, 100);
  TH1D hist_595 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_photons_up").c_str(), "dP_genreco_H_yy_weight_sf_photons_up", 20, 0, 100);
  TH1D hist_596 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_photons_down").c_str(), "dP_genreco_H_yy_weight_sf_photons_down", 20, 0, 100);
  TH1D hist_597 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_electrons_up").c_str(), "dP_genreco_H_yy_weight_sf_electrons_up", 20, 0, 100);
  TH1D hist_598 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_electrons_down").c_str(), "dP_genreco_H_yy_weight_sf_electrons_down", 20, 0, 100);
  TH1D hist_599 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_muons_id_up").c_str(), "dP_genreco_H_yy_weight_sf_muons_id_up", 20, 0, 100);
  TH1D hist_600 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_muons_id_down").c_str(), "dP_genreco_H_yy_weight_sf_muons_id_down", 20, 0, 100);
  TH1D hist_601 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_muons_iso_up").c_str(), "dP_genreco_H_yy_weight_sf_muons_iso_up", 20, 0, 100);
  TH1D hist_602 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_muons_iso_down").c_str(), "dP_genreco_H_yy_weight_sf_muons_iso_down", 20, 0, 100);
  TH1D hist_603 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_ljets_id_up").c_str(), "dP_genreco_H_yy_weight_sf_ljets_id_up", 20, 0, 100);
  TH1D hist_604 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_ljets_id_down").c_str(), "dP_genreco_H_yy_weight_sf_ljets_id_down", 20, 0, 100);
  TH1D hist_605 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_ljets_btag_up").c_str(), "dP_genreco_H_yy_weight_sf_ljets_btag_up", 20, 0, 100);
  TH1D hist_606 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_ljets_btag_down").c_str(), "dP_genreco_H_yy_weight_sf_ljets_btag_down", 20, 0, 100);
  TH1D hist_607 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_bjets_id_up").c_str(), "dP_genreco_H_yy_weight_sf_bjets_id_up", 20, 0, 100);
  TH1D hist_608 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_bjets_id_down").c_str(), "dP_genreco_H_yy_weight_sf_bjets_id_down", 20, 0, 100);
  TH1D hist_609 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_pileup_up").c_str(), "dP_genreco_H_yy_weight_sf_pileup_up", 20, 0, 100);
  TH1D hist_610 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_sf_pileup_down").c_str(), "dP_genreco_H_yy_weight_sf_pileup_down", 20, 0, 100);
  TH1D hist_611 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_FracRV_up").c_str(), "dP_genreco_H_yy_weight_FracRV_up", 20, 0, 100);
  TH1D hist_612 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_FracRV_down").c_str(), "dP_genreco_H_yy_weight_FracRV_down", 20, 0, 100);
  TH1D hist_613 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_LooseMvaSF_up").c_str(), "dP_genreco_H_yy_weight_LooseMvaSF_up", 20, 0, 100);
  TH1D hist_614 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_LooseMvaSF_down").c_str(), "dP_genreco_H_yy_weight_LooseMvaSF_down", 20, 0, 100);
  TH1D hist_615 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_PreselSF_up").c_str(), "dP_genreco_H_yy_weight_PreselSF_up", 20, 0, 100);
  TH1D hist_616 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_PreselSF_down").c_str(), "dP_genreco_H_yy_weight_PreselSF_down", 20, 0, 100);
  TH1D hist_617 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_Trigger_up").c_str(), "dP_genreco_H_yy_weight_Trigger_up", 20, 0, 100);
  TH1D hist_618 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_Trigger_down").c_str(), "dP_genreco_H_yy_weight_Trigger_down", 20, 0, 100);
  TH1D hist_619 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_electronVetoSF_up").c_str(), "dP_genreco_H_yy_weight_electronVetoSF_up", 20, 0, 100);
  TH1D hist_620 = TH1D((dataset->process_name + "_dP_genreco_H_yy_weight_electronVetoSF_down").c_str(), "dP_genreco_H_yy_weight_electronVetoSF_down", 20, 0, 100);
  TH1D hist_621 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight").c_str(), "dP_genreco_H_WW_weight", 20, 0, 400);
  TH1D hist_622 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_photons_up").c_str(), "dP_genreco_H_WW_weight_sf_photons_up", 20, 0, 400);
  TH1D hist_623 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_photons_down").c_str(), "dP_genreco_H_WW_weight_sf_photons_down", 20, 0, 400);
  TH1D hist_624 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_electrons_up").c_str(), "dP_genreco_H_WW_weight_sf_electrons_up", 20, 0, 400);
  TH1D hist_625 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_electrons_down").c_str(), "dP_genreco_H_WW_weight_sf_electrons_down", 20, 0, 400);
  TH1D hist_626 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_muons_id_up").c_str(), "dP_genreco_H_WW_weight_sf_muons_id_up", 20, 0, 400);
  TH1D hist_627 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_muons_id_down").c_str(), "dP_genreco_H_WW_weight_sf_muons_id_down", 20, 0, 400);
  TH1D hist_628 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_muons_iso_up").c_str(), "dP_genreco_H_WW_weight_sf_muons_iso_up", 20, 0, 400);
  TH1D hist_629 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_muons_iso_down").c_str(), "dP_genreco_H_WW_weight_sf_muons_iso_down", 20, 0, 400);
  TH1D hist_630 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_ljets_id_up").c_str(), "dP_genreco_H_WW_weight_sf_ljets_id_up", 20, 0, 400);
  TH1D hist_631 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_ljets_id_down").c_str(), "dP_genreco_H_WW_weight_sf_ljets_id_down", 20, 0, 400);
  TH1D hist_632 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_ljets_btag_up").c_str(), "dP_genreco_H_WW_weight_sf_ljets_btag_up", 20, 0, 400);
  TH1D hist_633 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_ljets_btag_down").c_str(), "dP_genreco_H_WW_weight_sf_ljets_btag_down", 20, 0, 400);
  TH1D hist_634 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_bjets_id_up").c_str(), "dP_genreco_H_WW_weight_sf_bjets_id_up", 20, 0, 400);
  TH1D hist_635 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_bjets_id_down").c_str(), "dP_genreco_H_WW_weight_sf_bjets_id_down", 20, 0, 400);
  TH1D hist_636 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_pileup_up").c_str(), "dP_genreco_H_WW_weight_sf_pileup_up", 20, 0, 400);
  TH1D hist_637 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_sf_pileup_down").c_str(), "dP_genreco_H_WW_weight_sf_pileup_down", 20, 0, 400);
  TH1D hist_638 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_FracRV_up").c_str(), "dP_genreco_H_WW_weight_FracRV_up", 20, 0, 400);
  TH1D hist_639 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_FracRV_down").c_str(), "dP_genreco_H_WW_weight_FracRV_down", 20, 0, 400);
  TH1D hist_640 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_LooseMvaSF_up").c_str(), "dP_genreco_H_WW_weight_LooseMvaSF_up", 20, 0, 400);
  TH1D hist_641 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_LooseMvaSF_down").c_str(), "dP_genreco_H_WW_weight_LooseMvaSF_down", 20, 0, 400);
  TH1D hist_642 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_PreselSF_up").c_str(), "dP_genreco_H_WW_weight_PreselSF_up", 20, 0, 400);
  TH1D hist_643 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_PreselSF_down").c_str(), "dP_genreco_H_WW_weight_PreselSF_down", 20, 0, 400);
  TH1D hist_644 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_Trigger_up").c_str(), "dP_genreco_H_WW_weight_Trigger_up", 20, 0, 400);
  TH1D hist_645 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_Trigger_down").c_str(), "dP_genreco_H_WW_weight_Trigger_down", 20, 0, 400);
  TH1D hist_646 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_electronVetoSF_up").c_str(), "dP_genreco_H_WW_weight_electronVetoSF_up", 20, 0, 400);
  TH1D hist_647 = TH1D((dataset->process_name + "_dP_genreco_H_WW_weight_electronVetoSF_down").c_str(), "dP_genreco_H_WW_weight_electronVetoSF_down", 20, 0, 400);
  TH1D hist_648 = TH1D((dataset->process_name + "_dP_genreco_nu_weight").c_str(), "dP_genreco_nu_weight", 20, 0, 400);
  TH1D hist_649 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_photons_up").c_str(), "dP_genreco_nu_weight_sf_photons_up", 20, 0, 400);
  TH1D hist_650 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_photons_down").c_str(), "dP_genreco_nu_weight_sf_photons_down", 20, 0, 400);
  TH1D hist_651 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_electrons_up").c_str(), "dP_genreco_nu_weight_sf_electrons_up", 20, 0, 400);
  TH1D hist_652 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_electrons_down").c_str(), "dP_genreco_nu_weight_sf_electrons_down", 20, 0, 400);
  TH1D hist_653 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_muons_id_up").c_str(), "dP_genreco_nu_weight_sf_muons_id_up", 20, 0, 400);
  TH1D hist_654 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_muons_id_down").c_str(), "dP_genreco_nu_weight_sf_muons_id_down", 20, 0, 400);
  TH1D hist_655 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_muons_iso_up").c_str(), "dP_genreco_nu_weight_sf_muons_iso_up", 20, 0, 400);
  TH1D hist_656 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_muons_iso_down").c_str(), "dP_genreco_nu_weight_sf_muons_iso_down", 20, 0, 400);
  TH1D hist_657 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_ljets_id_up").c_str(), "dP_genreco_nu_weight_sf_ljets_id_up", 20, 0, 400);
  TH1D hist_658 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_ljets_id_down").c_str(), "dP_genreco_nu_weight_sf_ljets_id_down", 20, 0, 400);
  TH1D hist_659 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_ljets_btag_up").c_str(), "dP_genreco_nu_weight_sf_ljets_btag_up", 20, 0, 400);
  TH1D hist_660 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_ljets_btag_down").c_str(), "dP_genreco_nu_weight_sf_ljets_btag_down", 20, 0, 400);
  TH1D hist_661 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_bjets_id_up").c_str(), "dP_genreco_nu_weight_sf_bjets_id_up", 20, 0, 400);
  TH1D hist_662 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_bjets_id_down").c_str(), "dP_genreco_nu_weight_sf_bjets_id_down", 20, 0, 400);
  TH1D hist_663 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_pileup_up").c_str(), "dP_genreco_nu_weight_sf_pileup_up", 20, 0, 400);
  TH1D hist_664 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_sf_pileup_down").c_str(), "dP_genreco_nu_weight_sf_pileup_down", 20, 0, 400);
  TH1D hist_665 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_FracRV_up").c_str(), "dP_genreco_nu_weight_FracRV_up", 20, 0, 400);
  TH1D hist_666 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_FracRV_down").c_str(), "dP_genreco_nu_weight_FracRV_down", 20, 0, 400);
  TH1D hist_667 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_LooseMvaSF_up").c_str(), "dP_genreco_nu_weight_LooseMvaSF_up", 20, 0, 400);
  TH1D hist_668 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_LooseMvaSF_down").c_str(), "dP_genreco_nu_weight_LooseMvaSF_down", 20, 0, 400);
  TH1D hist_669 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_PreselSF_up").c_str(), "dP_genreco_nu_weight_PreselSF_up", 20, 0, 400);
  TH1D hist_670 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_PreselSF_down").c_str(), "dP_genreco_nu_weight_PreselSF_down", 20, 0, 400);
  TH1D hist_671 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_Trigger_up").c_str(), "dP_genreco_nu_weight_Trigger_up", 20, 0, 400);
  TH1D hist_672 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_Trigger_down").c_str(), "dP_genreco_nu_weight_Trigger_down", 20, 0, 400);
  TH1D hist_673 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_electronVetoSF_up").c_str(), "dP_genreco_nu_weight_electronVetoSF_up", 20, 0, 400);
  TH1D hist_674 = TH1D((dataset->process_name + "_dP_genreco_nu_weight_electronVetoSF_down").c_str(), "dP_genreco_nu_weight_electronVetoSF_down", 20, 0, 400);
  TH1D hist_675 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight").c_str(), "dP_genreco_W_elnu_weight", 20, 0, 400);
  TH1D hist_676 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_photons_up").c_str(), "dP_genreco_W_elnu_weight_sf_photons_up", 20, 0, 400);
  TH1D hist_677 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_photons_down").c_str(), "dP_genreco_W_elnu_weight_sf_photons_down", 20, 0, 400);
  TH1D hist_678 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_electrons_up").c_str(), "dP_genreco_W_elnu_weight_sf_electrons_up", 20, 0, 400);
  TH1D hist_679 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_electrons_down").c_str(), "dP_genreco_W_elnu_weight_sf_electrons_down", 20, 0, 400);
  TH1D hist_680 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_muons_id_up").c_str(), "dP_genreco_W_elnu_weight_sf_muons_id_up", 20, 0, 400);
  TH1D hist_681 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_muons_id_down").c_str(), "dP_genreco_W_elnu_weight_sf_muons_id_down", 20, 0, 400);
  TH1D hist_682 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_muons_iso_up").c_str(), "dP_genreco_W_elnu_weight_sf_muons_iso_up", 20, 0, 400);
  TH1D hist_683 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_muons_iso_down").c_str(), "dP_genreco_W_elnu_weight_sf_muons_iso_down", 20, 0, 400);
  TH1D hist_684 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_ljets_id_up").c_str(), "dP_genreco_W_elnu_weight_sf_ljets_id_up", 20, 0, 400);
  TH1D hist_685 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_ljets_id_down").c_str(), "dP_genreco_W_elnu_weight_sf_ljets_id_down", 20, 0, 400);
  TH1D hist_686 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_ljets_btag_up").c_str(), "dP_genreco_W_elnu_weight_sf_ljets_btag_up", 20, 0, 400);
  TH1D hist_687 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_ljets_btag_down").c_str(), "dP_genreco_W_elnu_weight_sf_ljets_btag_down", 20, 0, 400);
  TH1D hist_688 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_bjets_id_up").c_str(), "dP_genreco_W_elnu_weight_sf_bjets_id_up", 20, 0, 400);
  TH1D hist_689 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_bjets_id_down").c_str(), "dP_genreco_W_elnu_weight_sf_bjets_id_down", 20, 0, 400);
  TH1D hist_690 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_pileup_up").c_str(), "dP_genreco_W_elnu_weight_sf_pileup_up", 20, 0, 400);
  TH1D hist_691 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_sf_pileup_down").c_str(), "dP_genreco_W_elnu_weight_sf_pileup_down", 20, 0, 400);
  TH1D hist_692 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_FracRV_up").c_str(), "dP_genreco_W_elnu_weight_FracRV_up", 20, 0, 400);
  TH1D hist_693 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_FracRV_down").c_str(), "dP_genreco_W_elnu_weight_FracRV_down", 20, 0, 400);
  TH1D hist_694 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_LooseMvaSF_up").c_str(), "dP_genreco_W_elnu_weight_LooseMvaSF_up", 20, 0, 400);
  TH1D hist_695 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_LooseMvaSF_down").c_str(), "dP_genreco_W_elnu_weight_LooseMvaSF_down", 20, 0, 400);
  TH1D hist_696 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_PreselSF_up").c_str(), "dP_genreco_W_elnu_weight_PreselSF_up", 20, 0, 400);
  TH1D hist_697 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_PreselSF_down").c_str(), "dP_genreco_W_elnu_weight_PreselSF_down", 20, 0, 400);
  TH1D hist_698 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_Trigger_up").c_str(), "dP_genreco_W_elnu_weight_Trigger_up", 20, 0, 400);
  TH1D hist_699 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_Trigger_down").c_str(), "dP_genreco_W_elnu_weight_Trigger_down", 20, 0, 400);
  TH1D hist_700 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_electronVetoSF_up").c_str(), "dP_genreco_W_elnu_weight_electronVetoSF_up", 20, 0, 400);
  TH1D hist_701 = TH1D((dataset->process_name + "_dP_genreco_W_elnu_weight_electronVetoSF_down").c_str(), "dP_genreco_W_elnu_weight_electronVetoSF_down", 20, 0, 400);
  TH1D hist_702 = TH1D((dataset->process_name + "_gen_dR_jj_weight").c_str(), "gen_dR_jj_weight", 20, 0, 5);
  TH1D hist_703 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_photons_up").c_str(), "gen_dR_jj_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_704 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_photons_down").c_str(), "gen_dR_jj_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_705 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_electrons_up").c_str(), "gen_dR_jj_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_706 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_electrons_down").c_str(), "gen_dR_jj_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_707 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_muons_id_up").c_str(), "gen_dR_jj_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_708 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_muons_id_down").c_str(), "gen_dR_jj_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_709 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_muons_iso_up").c_str(), "gen_dR_jj_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_710 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_muons_iso_down").c_str(), "gen_dR_jj_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_711 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_ljets_id_up").c_str(), "gen_dR_jj_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_712 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_ljets_id_down").c_str(), "gen_dR_jj_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_713 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_ljets_btag_up").c_str(), "gen_dR_jj_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_714 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_ljets_btag_down").c_str(), "gen_dR_jj_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_715 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_bjets_id_up").c_str(), "gen_dR_jj_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_716 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_bjets_id_down").c_str(), "gen_dR_jj_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_717 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_pileup_up").c_str(), "gen_dR_jj_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_718 = TH1D((dataset->process_name + "_gen_dR_jj_weight_sf_pileup_down").c_str(), "gen_dR_jj_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_719 = TH1D((dataset->process_name + "_gen_dR_jj_weight_FracRV_up").c_str(), "gen_dR_jj_weight_FracRV_up", 20, 0, 5);
  TH1D hist_720 = TH1D((dataset->process_name + "_gen_dR_jj_weight_FracRV_down").c_str(), "gen_dR_jj_weight_FracRV_down", 20, 0, 5);
  TH1D hist_721 = TH1D((dataset->process_name + "_gen_dR_jj_weight_LooseMvaSF_up").c_str(), "gen_dR_jj_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_722 = TH1D((dataset->process_name + "_gen_dR_jj_weight_LooseMvaSF_down").c_str(), "gen_dR_jj_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_723 = TH1D((dataset->process_name + "_gen_dR_jj_weight_PreselSF_up").c_str(), "gen_dR_jj_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_724 = TH1D((dataset->process_name + "_gen_dR_jj_weight_PreselSF_down").c_str(), "gen_dR_jj_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_725 = TH1D((dataset->process_name + "_gen_dR_jj_weight_Trigger_up").c_str(), "gen_dR_jj_weight_Trigger_up", 20, 0, 5);
  TH1D hist_726 = TH1D((dataset->process_name + "_gen_dR_jj_weight_Trigger_down").c_str(), "gen_dR_jj_weight_Trigger_down", 20, 0, 5);
  TH1D hist_727 = TH1D((dataset->process_name + "_gen_dR_jj_weight_electronVetoSF_up").c_str(), "gen_dR_jj_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_728 = TH1D((dataset->process_name + "_gen_dR_jj_weight_electronVetoSF_down").c_str(), "gen_dR_jj_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_729 = TH1D((dataset->process_name + "_dR_jj_leading_weight").c_str(), "dR_jj_leading_weight", 20, 0, 5);
  TH1D hist_730 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_photons_up").c_str(), "dR_jj_leading_weight_sf_photons_up", 20, 0, 5);
  TH1D hist_731 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_photons_down").c_str(), "dR_jj_leading_weight_sf_photons_down", 20, 0, 5);
  TH1D hist_732 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_electrons_up").c_str(), "dR_jj_leading_weight_sf_electrons_up", 20, 0, 5);
  TH1D hist_733 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_electrons_down").c_str(), "dR_jj_leading_weight_sf_electrons_down", 20, 0, 5);
  TH1D hist_734 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_muons_id_up").c_str(), "dR_jj_leading_weight_sf_muons_id_up", 20, 0, 5);
  TH1D hist_735 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_muons_id_down").c_str(), "dR_jj_leading_weight_sf_muons_id_down", 20, 0, 5);
  TH1D hist_736 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_muons_iso_up").c_str(), "dR_jj_leading_weight_sf_muons_iso_up", 20, 0, 5);
  TH1D hist_737 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_muons_iso_down").c_str(), "dR_jj_leading_weight_sf_muons_iso_down", 20, 0, 5);
  TH1D hist_738 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_ljets_id_up").c_str(), "dR_jj_leading_weight_sf_ljets_id_up", 20, 0, 5);
  TH1D hist_739 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_ljets_id_down").c_str(), "dR_jj_leading_weight_sf_ljets_id_down", 20, 0, 5);
  TH1D hist_740 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_ljets_btag_up").c_str(), "dR_jj_leading_weight_sf_ljets_btag_up", 20, 0, 5);
  TH1D hist_741 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_ljets_btag_down").c_str(), "dR_jj_leading_weight_sf_ljets_btag_down", 20, 0, 5);
  TH1D hist_742 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_bjets_id_up").c_str(), "dR_jj_leading_weight_sf_bjets_id_up", 20, 0, 5);
  TH1D hist_743 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_bjets_id_down").c_str(), "dR_jj_leading_weight_sf_bjets_id_down", 20, 0, 5);
  TH1D hist_744 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_pileup_up").c_str(), "dR_jj_leading_weight_sf_pileup_up", 20, 0, 5);
  TH1D hist_745 = TH1D((dataset->process_name + "_dR_jj_leading_weight_sf_pileup_down").c_str(), "dR_jj_leading_weight_sf_pileup_down", 20, 0, 5);
  TH1D hist_746 = TH1D((dataset->process_name + "_dR_jj_leading_weight_FracRV_up").c_str(), "dR_jj_leading_weight_FracRV_up", 20, 0, 5);
  TH1D hist_747 = TH1D((dataset->process_name + "_dR_jj_leading_weight_FracRV_down").c_str(), "dR_jj_leading_weight_FracRV_down", 20, 0, 5);
  TH1D hist_748 = TH1D((dataset->process_name + "_dR_jj_leading_weight_LooseMvaSF_up").c_str(), "dR_jj_leading_weight_LooseMvaSF_up", 20, 0, 5);
  TH1D hist_749 = TH1D((dataset->process_name + "_dR_jj_leading_weight_LooseMvaSF_down").c_str(), "dR_jj_leading_weight_LooseMvaSF_down", 20, 0, 5);
  TH1D hist_750 = TH1D((dataset->process_name + "_dR_jj_leading_weight_PreselSF_up").c_str(), "dR_jj_leading_weight_PreselSF_up", 20, 0, 5);
  TH1D hist_751 = TH1D((dataset->process_name + "_dR_jj_leading_weight_PreselSF_down").c_str(), "dR_jj_leading_weight_PreselSF_down", 20, 0, 5);
  TH1D hist_752 = TH1D((dataset->process_name + "_dR_jj_leading_weight_Trigger_up").c_str(), "dR_jj_leading_weight_Trigger_up", 20, 0, 5);
  TH1D hist_753 = TH1D((dataset->process_name + "_dR_jj_leading_weight_Trigger_down").c_str(), "dR_jj_leading_weight_Trigger_down", 20, 0, 5);
  TH1D hist_754 = TH1D((dataset->process_name + "_dR_jj_leading_weight_electronVetoSF_up").c_str(), "dR_jj_leading_weight_electronVetoSF_up", 20, 0, 5);
  TH1D hist_755 = TH1D((dataset->process_name + "_dR_jj_leading_weight_electronVetoSF_down").c_str(), "dR_jj_leading_weight_electronVetoSF_down", 20, 0, 5);
  TH1D hist_756 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight").c_str(), "gen_W_jj_tlv_M_weight", 20, 10, 300);
  TH1D hist_757 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_photons_up").c_str(), "gen_W_jj_tlv_M_weight_sf_photons_up", 20, 10, 300);
  TH1D hist_758 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_photons_down").c_str(), "gen_W_jj_tlv_M_weight_sf_photons_down", 20, 10, 300);
  TH1D hist_759 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_electrons_up").c_str(), "gen_W_jj_tlv_M_weight_sf_electrons_up", 20, 10, 300);
  TH1D hist_760 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_electrons_down").c_str(), "gen_W_jj_tlv_M_weight_sf_electrons_down", 20, 10, 300);
  TH1D hist_761 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_muons_id_up").c_str(), "gen_W_jj_tlv_M_weight_sf_muons_id_up", 20, 10, 300);
  TH1D hist_762 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_muons_id_down").c_str(), "gen_W_jj_tlv_M_weight_sf_muons_id_down", 20, 10, 300);
  TH1D hist_763 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_muons_iso_up").c_str(), "gen_W_jj_tlv_M_weight_sf_muons_iso_up", 20, 10, 300);
  TH1D hist_764 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_muons_iso_down").c_str(), "gen_W_jj_tlv_M_weight_sf_muons_iso_down", 20, 10, 300);
  TH1D hist_765 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_ljets_id_up").c_str(), "gen_W_jj_tlv_M_weight_sf_ljets_id_up", 20, 10, 300);
  TH1D hist_766 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_ljets_id_down").c_str(), "gen_W_jj_tlv_M_weight_sf_ljets_id_down", 20, 10, 300);
  TH1D hist_767 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_ljets_btag_up").c_str(), "gen_W_jj_tlv_M_weight_sf_ljets_btag_up", 20, 10, 300);
  TH1D hist_768 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_ljets_btag_down").c_str(), "gen_W_jj_tlv_M_weight_sf_ljets_btag_down", 20, 10, 300);
  TH1D hist_769 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_bjets_id_up").c_str(), "gen_W_jj_tlv_M_weight_sf_bjets_id_up", 20, 10, 300);
  TH1D hist_770 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_bjets_id_down").c_str(), "gen_W_jj_tlv_M_weight_sf_bjets_id_down", 20, 10, 300);
  TH1D hist_771 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_pileup_up").c_str(), "gen_W_jj_tlv_M_weight_sf_pileup_up", 20, 10, 300);
  TH1D hist_772 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_sf_pileup_down").c_str(), "gen_W_jj_tlv_M_weight_sf_pileup_down", 20, 10, 300);
  TH1D hist_773 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_FracRV_up").c_str(), "gen_W_jj_tlv_M_weight_FracRV_up", 20, 10, 300);
  TH1D hist_774 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_FracRV_down").c_str(), "gen_W_jj_tlv_M_weight_FracRV_down", 20, 10, 300);
  TH1D hist_775 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_LooseMvaSF_up").c_str(), "gen_W_jj_tlv_M_weight_LooseMvaSF_up", 20, 10, 300);
  TH1D hist_776 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_LooseMvaSF_down").c_str(), "gen_W_jj_tlv_M_weight_LooseMvaSF_down", 20, 10, 300);
  TH1D hist_777 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_PreselSF_up").c_str(), "gen_W_jj_tlv_M_weight_PreselSF_up", 20, 10, 300);
  TH1D hist_778 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_PreselSF_down").c_str(), "gen_W_jj_tlv_M_weight_PreselSF_down", 20, 10, 300);
  TH1D hist_779 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_Trigger_up").c_str(), "gen_W_jj_tlv_M_weight_Trigger_up", 20, 10, 300);
  TH1D hist_780 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_Trigger_down").c_str(), "gen_W_jj_tlv_M_weight_Trigger_down", 20, 10, 300);
  TH1D hist_781 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_electronVetoSF_up").c_str(), "gen_W_jj_tlv_M_weight_electronVetoSF_up", 20, 10, 300);
  TH1D hist_782 = TH1D((dataset->process_name + "_gen_W_jj_tlv_M_weight_electronVetoSF_down").c_str(), "gen_W_jj_tlv_M_weight_electronVetoSF_down", 20, 10, 300);
  //[[[end]]]

  cout << input_file << " Step I." <<  endl;
  TFile * file = TFile::Open(input_file.c_str(), "READ");
  TTree * tree = (TTree*) gDirectory->Get( dataset->dataset_ttree_name.c_str() );
  cout << "tree = " << tree << " " << input_file.c_str() << " " << dataset->dataset_ttree_name.c_str() << endl;

  if(not tree){
    cout << "\n====\nERROR ====================== tree = " << tree << " " << input_file.c_str() << " " << dataset->dataset_ttree_name.c_str() << "\n====\n" << endl;
  }

  // Def_Events * event  = new Def_Events( tree );
  /*[[[cog
    for var in variables :
      if var.frozen : continue

      bname = var.bname
      if not bname : bname = var.key
      vname = bname

      if var.type in ["Double_t", "Float_t", "Int_t"]:
        cog.outl( var.type + " " + bname + ";" )
      else : 
        cog.outl( var.type + " * " + bname + ";" )

      cog.outl( "if( tree->GetBranch( \"" + bname + "\") ){" )
      cog.outl( "tree->SetBranchAddress( \"" + bname + "\", &" + bname + ");" )    
      cog.outl("} else cout << \"DontHave a branch with name = " + bname + "\" << endl;" )
  ]]]*/
  Double_t m_yy;
  if( tree->GetBranch( "m_yy") ){
  tree->SetBranchAddress( "m_yy", &m_yy);
  } else cout << "DontHave a branch with name = m_yy" << endl;
  Double_t y1_Et_div_m_yy;
  if( tree->GetBranch( "y1_Et_div_m_yy") ){
  tree->SetBranchAddress( "y1_Et_div_m_yy", &y1_Et_div_m_yy);
  } else cout << "DontHave a branch with name = y1_Et_div_m_yy" << endl;
  Double_t y2_Et_div_m_y;
  if( tree->GetBranch( "y2_Et_div_m_y") ){
  tree->SetBranchAddress( "y2_Et_div_m_y", &y2_Et_div_m_y);
  } else cout << "DontHave a branch with name = y2_Et_div_m_y" << endl;
  Double_t dR_yy;
  if( tree->GetBranch( "dR_yy") ){
  tree->SetBranchAddress( "dR_yy", &dR_yy);
  } else cout << "DontHave a branch with name = dR_yy" << endl;
  Double_t dR_jj;
  if( tree->GetBranch( "dR_jj") ){
  tree->SetBranchAddress( "dR_jj", &dR_jj);
  } else cout << "DontHave a branch with name = dR_jj" << endl;
  Double_t dR_WL;
  if( tree->GetBranch( "dR_WL") ){
  tree->SetBranchAddress( "dR_WL", &dR_WL);
  } else cout << "DontHave a branch with name = dR_WL" << endl;
  Double_t dR_WW;
  if( tree->GetBranch( "dR_WW") ){
  tree->SetBranchAddress( "dR_WW", &dR_WW);
  } else cout << "DontHave a branch with name = dR_WW" << endl;
  Double_t dR_HH;
  if( tree->GetBranch( "dR_HH") ){
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
  TLorentzVector * gen_HHi_tlv;
  if( tree->GetBranch( "gen_HHi_tlv") ){
  tree->SetBranchAddress( "gen_HHi_tlv", &gen_HHi_tlv);
  } else cout << "DontHave a branch with name = gen_HHi_tlv" << endl;
  TLorentzVector * gen_Hi_yy_tlv;
  if( tree->GetBranch( "gen_Hi_yy_tlv") ){
  tree->SetBranchAddress( "gen_Hi_yy_tlv", &gen_Hi_yy_tlv);
  } else cout << "DontHave a branch with name = gen_Hi_yy_tlv" << endl;
  Double_t dR_genreco_W_jj;
  if( tree->GetBranch( "dR_genreco_W_jj") ){
  tree->SetBranchAddress( "dR_genreco_W_jj", &dR_genreco_W_jj);
  } else cout << "DontHave a branch with name = dR_genreco_W_jj" << endl;
  Double_t dR_genreco_W_jj_leading;
  if( tree->GetBranch( "dR_genreco_W_jj_leading") ){
  tree->SetBranchAddress( "dR_genreco_W_jj_leading", &dR_genreco_W_jj_leading);
  } else cout << "DontHave a branch with name = dR_genreco_W_jj_leading" << endl;
  Double_t dP_genreco_W_jj;
  if( tree->GetBranch( "dP_genreco_W_jj") ){
  tree->SetBranchAddress( "dP_genreco_W_jj", &dP_genreco_W_jj);
  } else cout << "DontHave a branch with name = dP_genreco_W_jj" << endl;
  Double_t dP_genreco_W_jj_leading;
  if( tree->GetBranch( "dP_genreco_W_jj_leading") ){
  tree->SetBranchAddress( "dP_genreco_W_jj_leading", &dP_genreco_W_jj_leading);
  } else cout << "DontHave a branch with name = dP_genreco_W_jj_leading" << endl;
  TLorentzVector * W_jj_tlv_leading;
  if( tree->GetBranch( "W_jj_tlv_leading") ){
  tree->SetBranchAddress( "W_jj_tlv_leading", &W_jj_tlv_leading);
  } else cout << "DontHave a branch with name = W_jj_tlv_leading" << endl;
  Double_t dR_genreco_H_yy;
  if( tree->GetBranch( "dR_genreco_H_yy") ){
  tree->SetBranchAddress( "dR_genreco_H_yy", &dR_genreco_H_yy);
  } else cout << "DontHave a branch with name = dR_genreco_H_yy" << endl;
  Double_t dR_genreco_H_WW;
  if( tree->GetBranch( "dR_genreco_H_WW") ){
  tree->SetBranchAddress( "dR_genreco_H_WW", &dR_genreco_H_WW);
  } else cout << "DontHave a branch with name = dR_genreco_H_WW" << endl;
  Double_t dR_genreco_nu;
  if( tree->GetBranch( "dR_genreco_nu") ){
  tree->SetBranchAddress( "dR_genreco_nu", &dR_genreco_nu);
  } else cout << "DontHave a branch with name = dR_genreco_nu" << endl;
  Double_t dR_genreco_W_elnu;
  if( tree->GetBranch( "dR_genreco_W_elnu") ){
  tree->SetBranchAddress( "dR_genreco_W_elnu", &dR_genreco_W_elnu);
  } else cout << "DontHave a branch with name = dR_genreco_W_elnu" << endl;
  Double_t dP_genreco_H_yy;
  if( tree->GetBranch( "dP_genreco_H_yy") ){
  tree->SetBranchAddress( "dP_genreco_H_yy", &dP_genreco_H_yy);
  } else cout << "DontHave a branch with name = dP_genreco_H_yy" << endl;
  Double_t dP_genreco_H_WW;
  if( tree->GetBranch( "dP_genreco_H_WW") ){
  tree->SetBranchAddress( "dP_genreco_H_WW", &dP_genreco_H_WW);
  } else cout << "DontHave a branch with name = dP_genreco_H_WW" << endl;
  Double_t dP_genreco_nu;
  if( tree->GetBranch( "dP_genreco_nu") ){
  tree->SetBranchAddress( "dP_genreco_nu", &dP_genreco_nu);
  } else cout << "DontHave a branch with name = dP_genreco_nu" << endl;
  Double_t dP_genreco_W_elnu;
  if( tree->GetBranch( "dP_genreco_W_elnu") ){
  tree->SetBranchAddress( "dP_genreco_W_elnu", &dP_genreco_W_elnu);
  } else cout << "DontHave a branch with name = dP_genreco_W_elnu" << endl;
  Double_t gen_dR_jj;
  if( tree->GetBranch( "gen_dR_jj") ){
  tree->SetBranchAddress( "gen_dR_jj", &gen_dR_jj);
  } else cout << "DontHave a branch with name = gen_dR_jj" << endl;
  Double_t dR_jj_leading;
  if( tree->GetBranch( "dR_jj_leading") ){
  tree->SetBranchAddress( "dR_jj_leading", &dR_jj_leading);
  } else cout << "DontHave a branch with name = dR_jj_leading" << endl;
  TLorentzVector * gen_W_jj_tlv;
  if( tree->GetBranch( "gen_W_jj_tlv") ){
  tree->SetBranchAddress( "gen_W_jj_tlv", &gen_W_jj_tlv);
  } else cout << "DontHave a branch with name = gen_W_jj_tlv" << endl;
  //[[[end]]]

  // reweight due to train
  int nevents = tree->GetEntries();
  cout << "step II." <<  endl;
  
  double lumi_2017 = 44.98 * 1000; // pb-1
  Double_t weight_EFT = 1, weight = 1;
  bool print_weights = false;
  if( tree->GetBranch("weight_EFT") ){
    print_weights = true;
    tree->SetBranchAddress("weight_EFT", &weight_EFT);
  }
  tree->SetBranchAddress("weight", &weight);


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
  Double_t weight_sf_ljets_id_up   = 1;
  if( tree->GetBranch( "weight_sf_ljets_id_up") ){
  tree->SetBranchAddress("weight_sf_ljets_id_up", &weight_sf_ljets_id_up);
  } else cout << "DontHave a branch with name = weight_sf_ljets_id_up" << endl;
  Double_t weight_sf_ljets_id_down   = 1;
  if( tree->GetBranch( "weight_sf_ljets_id_down") ){
  tree->SetBranchAddress("weight_sf_ljets_id_down", &weight_sf_ljets_id_down);
  } else cout << "DontHave a branch with name = weight_sf_ljets_id_down" << endl;
  Double_t weight_sf_ljets_btag_up   = 1;
  if( tree->GetBranch( "weight_sf_ljets_btag_up") ){
  tree->SetBranchAddress("weight_sf_ljets_btag_up", &weight_sf_ljets_btag_up);
  } else cout << "DontHave a branch with name = weight_sf_ljets_btag_up" << endl;
  Double_t weight_sf_ljets_btag_down   = 1;
  if( tree->GetBranch( "weight_sf_ljets_btag_down") ){
  tree->SetBranchAddress("weight_sf_ljets_btag_down", &weight_sf_ljets_btag_down);
  } else cout << "DontHave a branch with name = weight_sf_ljets_btag_down" << endl;
  Double_t weight_sf_bjets_id_up   = 1;
  if( tree->GetBranch( "weight_sf_bjets_id_up") ){
  tree->SetBranchAddress("weight_sf_bjets_id_up", &weight_sf_bjets_id_up);
  } else cout << "DontHave a branch with name = weight_sf_bjets_id_up" << endl;
  Double_t weight_sf_bjets_id_down   = 1;
  if( tree->GetBranch( "weight_sf_bjets_id_down") ){
  tree->SetBranchAddress("weight_sf_bjets_id_down", &weight_sf_bjets_id_down);
  } else cout << "DontHave a branch with name = weight_sf_bjets_id_down" << endl;
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
        xfactor = lumi_2017 * dataset->xsec / dataset->weight_sum;
      } else if ( dataset->IsData() ){
        weight  = 1;
        weight_EFT = 1;
      }

      //cout << xfactor << endl;
      //xfactor   = (*weight      ) * lumi * train_reweight_factor * extra_weight;
      //xfactor_1 = (*weight_sel_1) * lumi * train_reweight_factor * extra_weight;
      //xfactor_2 = (*weight_sel_2) * lumi * train_reweight_factor * extra_weight;
      //xfactor_3 = (*weight_sel_3) * lumi * train_reweight_factor * extra_weight;
      //cout << weight << " sf=" << weight_sf_photons_up << " " <<  xfactor << " " <<  weight_EFT << endl;

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
      hist_0.Fill( m_yy, weight * xfactor * weight_EFT );
      hist_1.Fill( m_yy, weight_sf_photons_up * xfactor * weight_EFT );
      hist_2.Fill( m_yy, weight_sf_photons_down * xfactor * weight_EFT );
      hist_3.Fill( m_yy, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_4.Fill( m_yy, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_5.Fill( m_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_6.Fill( m_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_7.Fill( m_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_8.Fill( m_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_9.Fill( m_yy, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_10.Fill( m_yy, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_11.Fill( m_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_12.Fill( m_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_13.Fill( m_yy, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_14.Fill( m_yy, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_15.Fill( m_yy, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_16.Fill( m_yy, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_17.Fill( m_yy, weight_FracRV_up * xfactor * weight_EFT );
      hist_18.Fill( m_yy, weight_FracRV_down * xfactor * weight_EFT );
      hist_19.Fill( m_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_20.Fill( m_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_21.Fill( m_yy, weight_PreselSF_up * xfactor * weight_EFT );
      hist_22.Fill( m_yy, weight_PreselSF_down * xfactor * weight_EFT );
      hist_23.Fill( m_yy, weight_Trigger_up * xfactor * weight_EFT );
      hist_24.Fill( m_yy, weight_Trigger_down * xfactor * weight_EFT );
      hist_25.Fill( m_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_26.Fill( m_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_27.Fill( y1_Et_div_m_yy, weight * xfactor * weight_EFT );
      hist_28.Fill( y1_Et_div_m_yy, weight_sf_photons_up * xfactor * weight_EFT );
      hist_29.Fill( y1_Et_div_m_yy, weight_sf_photons_down * xfactor * weight_EFT );
      hist_30.Fill( y1_Et_div_m_yy, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_31.Fill( y1_Et_div_m_yy, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_32.Fill( y1_Et_div_m_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_33.Fill( y1_Et_div_m_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_34.Fill( y1_Et_div_m_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_35.Fill( y1_Et_div_m_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_36.Fill( y1_Et_div_m_yy, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_37.Fill( y1_Et_div_m_yy, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_38.Fill( y1_Et_div_m_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_39.Fill( y1_Et_div_m_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_40.Fill( y1_Et_div_m_yy, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_41.Fill( y1_Et_div_m_yy, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_42.Fill( y1_Et_div_m_yy, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_43.Fill( y1_Et_div_m_yy, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_44.Fill( y1_Et_div_m_yy, weight_FracRV_up * xfactor * weight_EFT );
      hist_45.Fill( y1_Et_div_m_yy, weight_FracRV_down * xfactor * weight_EFT );
      hist_46.Fill( y1_Et_div_m_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_47.Fill( y1_Et_div_m_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_48.Fill( y1_Et_div_m_yy, weight_PreselSF_up * xfactor * weight_EFT );
      hist_49.Fill( y1_Et_div_m_yy, weight_PreselSF_down * xfactor * weight_EFT );
      hist_50.Fill( y1_Et_div_m_yy, weight_Trigger_up * xfactor * weight_EFT );
      hist_51.Fill( y1_Et_div_m_yy, weight_Trigger_down * xfactor * weight_EFT );
      hist_52.Fill( y1_Et_div_m_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_53.Fill( y1_Et_div_m_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_54.Fill( y2_Et_div_m_y, weight * xfactor * weight_EFT );
      hist_55.Fill( y2_Et_div_m_y, weight_sf_photons_up * xfactor * weight_EFT );
      hist_56.Fill( y2_Et_div_m_y, weight_sf_photons_down * xfactor * weight_EFT );
      hist_57.Fill( y2_Et_div_m_y, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_58.Fill( y2_Et_div_m_y, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_59.Fill( y2_Et_div_m_y, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_60.Fill( y2_Et_div_m_y, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_61.Fill( y2_Et_div_m_y, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_62.Fill( y2_Et_div_m_y, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_63.Fill( y2_Et_div_m_y, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_64.Fill( y2_Et_div_m_y, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_65.Fill( y2_Et_div_m_y, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_66.Fill( y2_Et_div_m_y, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_67.Fill( y2_Et_div_m_y, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_68.Fill( y2_Et_div_m_y, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_69.Fill( y2_Et_div_m_y, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_70.Fill( y2_Et_div_m_y, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_71.Fill( y2_Et_div_m_y, weight_FracRV_up * xfactor * weight_EFT );
      hist_72.Fill( y2_Et_div_m_y, weight_FracRV_down * xfactor * weight_EFT );
      hist_73.Fill( y2_Et_div_m_y, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_74.Fill( y2_Et_div_m_y, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_75.Fill( y2_Et_div_m_y, weight_PreselSF_up * xfactor * weight_EFT );
      hist_76.Fill( y2_Et_div_m_y, weight_PreselSF_down * xfactor * weight_EFT );
      hist_77.Fill( y2_Et_div_m_y, weight_Trigger_up * xfactor * weight_EFT );
      hist_78.Fill( y2_Et_div_m_y, weight_Trigger_down * xfactor * weight_EFT );
      hist_79.Fill( y2_Et_div_m_y, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_80.Fill( y2_Et_div_m_y, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_81.Fill( dR_yy, weight * xfactor * weight_EFT );
      hist_82.Fill( dR_yy, weight_sf_photons_up * xfactor * weight_EFT );
      hist_83.Fill( dR_yy, weight_sf_photons_down * xfactor * weight_EFT );
      hist_84.Fill( dR_yy, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_85.Fill( dR_yy, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_86.Fill( dR_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_87.Fill( dR_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_88.Fill( dR_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_89.Fill( dR_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_90.Fill( dR_yy, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_91.Fill( dR_yy, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_92.Fill( dR_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_93.Fill( dR_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_94.Fill( dR_yy, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_95.Fill( dR_yy, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_96.Fill( dR_yy, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_97.Fill( dR_yy, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_98.Fill( dR_yy, weight_FracRV_up * xfactor * weight_EFT );
      hist_99.Fill( dR_yy, weight_FracRV_down * xfactor * weight_EFT );
      hist_100.Fill( dR_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_101.Fill( dR_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_102.Fill( dR_yy, weight_PreselSF_up * xfactor * weight_EFT );
      hist_103.Fill( dR_yy, weight_PreselSF_down * xfactor * weight_EFT );
      hist_104.Fill( dR_yy, weight_Trigger_up * xfactor * weight_EFT );
      hist_105.Fill( dR_yy, weight_Trigger_down * xfactor * weight_EFT );
      hist_106.Fill( dR_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_107.Fill( dR_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_108.Fill( dR_jj, weight * xfactor * weight_EFT );
      hist_109.Fill( dR_jj, weight_sf_photons_up * xfactor * weight_EFT );
      hist_110.Fill( dR_jj, weight_sf_photons_down * xfactor * weight_EFT );
      hist_111.Fill( dR_jj, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_112.Fill( dR_jj, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_113.Fill( dR_jj, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_114.Fill( dR_jj, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_115.Fill( dR_jj, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_116.Fill( dR_jj, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_117.Fill( dR_jj, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_118.Fill( dR_jj, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_119.Fill( dR_jj, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_120.Fill( dR_jj, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_121.Fill( dR_jj, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_122.Fill( dR_jj, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_123.Fill( dR_jj, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_124.Fill( dR_jj, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_125.Fill( dR_jj, weight_FracRV_up * xfactor * weight_EFT );
      hist_126.Fill( dR_jj, weight_FracRV_down * xfactor * weight_EFT );
      hist_127.Fill( dR_jj, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_128.Fill( dR_jj, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_129.Fill( dR_jj, weight_PreselSF_up * xfactor * weight_EFT );
      hist_130.Fill( dR_jj, weight_PreselSF_down * xfactor * weight_EFT );
      hist_131.Fill( dR_jj, weight_Trigger_up * xfactor * weight_EFT );
      hist_132.Fill( dR_jj, weight_Trigger_down * xfactor * weight_EFT );
      hist_133.Fill( dR_jj, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_134.Fill( dR_jj, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_135.Fill( dR_WL, weight * xfactor * weight_EFT );
      hist_136.Fill( dR_WL, weight_sf_photons_up * xfactor * weight_EFT );
      hist_137.Fill( dR_WL, weight_sf_photons_down * xfactor * weight_EFT );
      hist_138.Fill( dR_WL, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_139.Fill( dR_WL, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_140.Fill( dR_WL, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_141.Fill( dR_WL, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_142.Fill( dR_WL, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_143.Fill( dR_WL, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_144.Fill( dR_WL, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_145.Fill( dR_WL, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_146.Fill( dR_WL, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_147.Fill( dR_WL, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_148.Fill( dR_WL, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_149.Fill( dR_WL, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_150.Fill( dR_WL, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_151.Fill( dR_WL, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_152.Fill( dR_WL, weight_FracRV_up * xfactor * weight_EFT );
      hist_153.Fill( dR_WL, weight_FracRV_down * xfactor * weight_EFT );
      hist_154.Fill( dR_WL, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_155.Fill( dR_WL, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_156.Fill( dR_WL, weight_PreselSF_up * xfactor * weight_EFT );
      hist_157.Fill( dR_WL, weight_PreselSF_down * xfactor * weight_EFT );
      hist_158.Fill( dR_WL, weight_Trigger_up * xfactor * weight_EFT );
      hist_159.Fill( dR_WL, weight_Trigger_down * xfactor * weight_EFT );
      hist_160.Fill( dR_WL, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_161.Fill( dR_WL, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_162.Fill( dR_WW, weight * xfactor * weight_EFT );
      hist_163.Fill( dR_WW, weight_sf_photons_up * xfactor * weight_EFT );
      hist_164.Fill( dR_WW, weight_sf_photons_down * xfactor * weight_EFT );
      hist_165.Fill( dR_WW, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_166.Fill( dR_WW, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_167.Fill( dR_WW, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_168.Fill( dR_WW, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_169.Fill( dR_WW, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_170.Fill( dR_WW, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_171.Fill( dR_WW, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_172.Fill( dR_WW, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_173.Fill( dR_WW, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_174.Fill( dR_WW, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_175.Fill( dR_WW, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_176.Fill( dR_WW, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_177.Fill( dR_WW, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_178.Fill( dR_WW, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_179.Fill( dR_WW, weight_FracRV_up * xfactor * weight_EFT );
      hist_180.Fill( dR_WW, weight_FracRV_down * xfactor * weight_EFT );
      hist_181.Fill( dR_WW, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_182.Fill( dR_WW, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_183.Fill( dR_WW, weight_PreselSF_up * xfactor * weight_EFT );
      hist_184.Fill( dR_WW, weight_PreselSF_down * xfactor * weight_EFT );
      hist_185.Fill( dR_WW, weight_Trigger_up * xfactor * weight_EFT );
      hist_186.Fill( dR_WW, weight_Trigger_down * xfactor * weight_EFT );
      hist_187.Fill( dR_WW, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_188.Fill( dR_WW, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_189.Fill( dR_HH, weight * xfactor * weight_EFT );
      hist_190.Fill( dR_HH, weight_sf_photons_up * xfactor * weight_EFT );
      hist_191.Fill( dR_HH, weight_sf_photons_down * xfactor * weight_EFT );
      hist_192.Fill( dR_HH, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_193.Fill( dR_HH, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_194.Fill( dR_HH, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_195.Fill( dR_HH, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_196.Fill( dR_HH, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_197.Fill( dR_HH, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_198.Fill( dR_HH, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_199.Fill( dR_HH, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_200.Fill( dR_HH, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_201.Fill( dR_HH, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_202.Fill( dR_HH, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_203.Fill( dR_HH, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_204.Fill( dR_HH, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_205.Fill( dR_HH, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_206.Fill( dR_HH, weight_FracRV_up * xfactor * weight_EFT );
      hist_207.Fill( dR_HH, weight_FracRV_down * xfactor * weight_EFT );
      hist_208.Fill( dR_HH, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_209.Fill( dR_HH, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_210.Fill( dR_HH, weight_PreselSF_up * xfactor * weight_EFT );
      hist_211.Fill( dR_HH, weight_PreselSF_down * xfactor * weight_EFT );
      hist_212.Fill( dR_HH, weight_Trigger_up * xfactor * weight_EFT );
      hist_213.Fill( dR_HH, weight_Trigger_down * xfactor * weight_EFT );
      hist_214.Fill( dR_HH, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_215.Fill( dR_HH, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_216.Fill( W_elnu_tlv->M(), weight * xfactor * weight_EFT );
      hist_217.Fill( W_elnu_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_218.Fill( W_elnu_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_219.Fill( W_elnu_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_220.Fill( W_elnu_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_221.Fill( W_elnu_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_222.Fill( W_elnu_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_223.Fill( W_elnu_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_224.Fill( W_elnu_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_225.Fill( W_elnu_tlv->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_226.Fill( W_elnu_tlv->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_227.Fill( W_elnu_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_228.Fill( W_elnu_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_229.Fill( W_elnu_tlv->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_230.Fill( W_elnu_tlv->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_231.Fill( W_elnu_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_232.Fill( W_elnu_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_233.Fill( W_elnu_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_234.Fill( W_elnu_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_235.Fill( W_elnu_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_236.Fill( W_elnu_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_237.Fill( W_elnu_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_238.Fill( W_elnu_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_239.Fill( W_elnu_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_240.Fill( W_elnu_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_241.Fill( W_elnu_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_242.Fill( W_elnu_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_243.Fill( W_jj_tlv->M(), weight * xfactor * weight_EFT );
      hist_244.Fill( W_jj_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_245.Fill( W_jj_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_246.Fill( W_jj_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_247.Fill( W_jj_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_248.Fill( W_jj_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_249.Fill( W_jj_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_250.Fill( W_jj_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_251.Fill( W_jj_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_252.Fill( W_jj_tlv->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_253.Fill( W_jj_tlv->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_254.Fill( W_jj_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_255.Fill( W_jj_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_256.Fill( W_jj_tlv->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_257.Fill( W_jj_tlv->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_258.Fill( W_jj_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_259.Fill( W_jj_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_260.Fill( W_jj_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_261.Fill( W_jj_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_262.Fill( W_jj_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_263.Fill( W_jj_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_264.Fill( W_jj_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_265.Fill( W_jj_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_266.Fill( W_jj_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_267.Fill( W_jj_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_268.Fill( W_jj_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_269.Fill( W_jj_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_270.Fill( H_WW_tlv->M(), weight * xfactor * weight_EFT );
      hist_271.Fill( H_WW_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_272.Fill( H_WW_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_273.Fill( H_WW_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_274.Fill( H_WW_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_275.Fill( H_WW_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_276.Fill( H_WW_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_277.Fill( H_WW_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_278.Fill( H_WW_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_279.Fill( H_WW_tlv->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_280.Fill( H_WW_tlv->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_281.Fill( H_WW_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_282.Fill( H_WW_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_283.Fill( H_WW_tlv->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_284.Fill( H_WW_tlv->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_285.Fill( H_WW_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_286.Fill( H_WW_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_287.Fill( H_WW_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_288.Fill( H_WW_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_289.Fill( H_WW_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_290.Fill( H_WW_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_291.Fill( H_WW_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_292.Fill( H_WW_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_293.Fill( H_WW_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_294.Fill( H_WW_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_295.Fill( H_WW_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_296.Fill( H_WW_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_297.Fill( gen_HHi_tlv->M(), weight * xfactor * weight_EFT );
      hist_298.Fill( gen_HHi_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_299.Fill( gen_HHi_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_300.Fill( gen_HHi_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_301.Fill( gen_HHi_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_302.Fill( gen_HHi_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_303.Fill( gen_HHi_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_304.Fill( gen_HHi_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_305.Fill( gen_HHi_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_306.Fill( gen_HHi_tlv->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_307.Fill( gen_HHi_tlv->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_308.Fill( gen_HHi_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_309.Fill( gen_HHi_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_310.Fill( gen_HHi_tlv->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_311.Fill( gen_HHi_tlv->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_312.Fill( gen_HHi_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_313.Fill( gen_HHi_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_314.Fill( gen_HHi_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_315.Fill( gen_HHi_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_316.Fill( gen_HHi_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_317.Fill( gen_HHi_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_318.Fill( gen_HHi_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_319.Fill( gen_HHi_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_320.Fill( gen_HHi_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_321.Fill( gen_HHi_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_322.Fill( gen_HHi_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_323.Fill( gen_HHi_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_324.Fill( gen_Hi_yy_tlv->CosTheta(), weight * xfactor * weight_EFT );
      hist_325.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_326.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_327.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_328.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_329.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_330.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_331.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_332.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_333.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_334.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_335.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_336.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_337.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_338.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_339.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_340.Fill( gen_Hi_yy_tlv->CosTheta(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_341.Fill( gen_Hi_yy_tlv->CosTheta(), weight_FracRV_up * xfactor * weight_EFT );
      hist_342.Fill( gen_Hi_yy_tlv->CosTheta(), weight_FracRV_down * xfactor * weight_EFT );
      hist_343.Fill( gen_Hi_yy_tlv->CosTheta(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_344.Fill( gen_Hi_yy_tlv->CosTheta(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_345.Fill( gen_Hi_yy_tlv->CosTheta(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_346.Fill( gen_Hi_yy_tlv->CosTheta(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_347.Fill( gen_Hi_yy_tlv->CosTheta(), weight_Trigger_up * xfactor * weight_EFT );
      hist_348.Fill( gen_Hi_yy_tlv->CosTheta(), weight_Trigger_down * xfactor * weight_EFT );
      hist_349.Fill( gen_Hi_yy_tlv->CosTheta(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_350.Fill( gen_Hi_yy_tlv->CosTheta(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_351.Fill( dR_genreco_W_jj, weight * xfactor * weight_EFT );
      hist_352.Fill( dR_genreco_W_jj, weight_sf_photons_up * xfactor * weight_EFT );
      hist_353.Fill( dR_genreco_W_jj, weight_sf_photons_down * xfactor * weight_EFT );
      hist_354.Fill( dR_genreco_W_jj, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_355.Fill( dR_genreco_W_jj, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_356.Fill( dR_genreco_W_jj, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_357.Fill( dR_genreco_W_jj, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_358.Fill( dR_genreco_W_jj, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_359.Fill( dR_genreco_W_jj, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_360.Fill( dR_genreco_W_jj, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_361.Fill( dR_genreco_W_jj, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_362.Fill( dR_genreco_W_jj, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_363.Fill( dR_genreco_W_jj, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_364.Fill( dR_genreco_W_jj, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_365.Fill( dR_genreco_W_jj, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_366.Fill( dR_genreco_W_jj, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_367.Fill( dR_genreco_W_jj, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_368.Fill( dR_genreco_W_jj, weight_FracRV_up * xfactor * weight_EFT );
      hist_369.Fill( dR_genreco_W_jj, weight_FracRV_down * xfactor * weight_EFT );
      hist_370.Fill( dR_genreco_W_jj, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_371.Fill( dR_genreco_W_jj, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_372.Fill( dR_genreco_W_jj, weight_PreselSF_up * xfactor * weight_EFT );
      hist_373.Fill( dR_genreco_W_jj, weight_PreselSF_down * xfactor * weight_EFT );
      hist_374.Fill( dR_genreco_W_jj, weight_Trigger_up * xfactor * weight_EFT );
      hist_375.Fill( dR_genreco_W_jj, weight_Trigger_down * xfactor * weight_EFT );
      hist_376.Fill( dR_genreco_W_jj, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_377.Fill( dR_genreco_W_jj, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_378.Fill( dR_genreco_W_jj_leading, weight * xfactor * weight_EFT );
      hist_379.Fill( dR_genreco_W_jj_leading, weight_sf_photons_up * xfactor * weight_EFT );
      hist_380.Fill( dR_genreco_W_jj_leading, weight_sf_photons_down * xfactor * weight_EFT );
      hist_381.Fill( dR_genreco_W_jj_leading, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_382.Fill( dR_genreco_W_jj_leading, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_383.Fill( dR_genreco_W_jj_leading, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_384.Fill( dR_genreco_W_jj_leading, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_385.Fill( dR_genreco_W_jj_leading, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_386.Fill( dR_genreco_W_jj_leading, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_387.Fill( dR_genreco_W_jj_leading, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_388.Fill( dR_genreco_W_jj_leading, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_389.Fill( dR_genreco_W_jj_leading, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_390.Fill( dR_genreco_W_jj_leading, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_391.Fill( dR_genreco_W_jj_leading, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_392.Fill( dR_genreco_W_jj_leading, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_393.Fill( dR_genreco_W_jj_leading, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_394.Fill( dR_genreco_W_jj_leading, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_395.Fill( dR_genreco_W_jj_leading, weight_FracRV_up * xfactor * weight_EFT );
      hist_396.Fill( dR_genreco_W_jj_leading, weight_FracRV_down * xfactor * weight_EFT );
      hist_397.Fill( dR_genreco_W_jj_leading, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_398.Fill( dR_genreco_W_jj_leading, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_399.Fill( dR_genreco_W_jj_leading, weight_PreselSF_up * xfactor * weight_EFT );
      hist_400.Fill( dR_genreco_W_jj_leading, weight_PreselSF_down * xfactor * weight_EFT );
      hist_401.Fill( dR_genreco_W_jj_leading, weight_Trigger_up * xfactor * weight_EFT );
      hist_402.Fill( dR_genreco_W_jj_leading, weight_Trigger_down * xfactor * weight_EFT );
      hist_403.Fill( dR_genreco_W_jj_leading, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_404.Fill( dR_genreco_W_jj_leading, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_405.Fill( dP_genreco_W_jj, weight * xfactor * weight_EFT );
      hist_406.Fill( dP_genreco_W_jj, weight_sf_photons_up * xfactor * weight_EFT );
      hist_407.Fill( dP_genreco_W_jj, weight_sf_photons_down * xfactor * weight_EFT );
      hist_408.Fill( dP_genreco_W_jj, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_409.Fill( dP_genreco_W_jj, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_410.Fill( dP_genreco_W_jj, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_411.Fill( dP_genreco_W_jj, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_412.Fill( dP_genreco_W_jj, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_413.Fill( dP_genreco_W_jj, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_414.Fill( dP_genreco_W_jj, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_415.Fill( dP_genreco_W_jj, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_416.Fill( dP_genreco_W_jj, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_417.Fill( dP_genreco_W_jj, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_418.Fill( dP_genreco_W_jj, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_419.Fill( dP_genreco_W_jj, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_420.Fill( dP_genreco_W_jj, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_421.Fill( dP_genreco_W_jj, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_422.Fill( dP_genreco_W_jj, weight_FracRV_up * xfactor * weight_EFT );
      hist_423.Fill( dP_genreco_W_jj, weight_FracRV_down * xfactor * weight_EFT );
      hist_424.Fill( dP_genreco_W_jj, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_425.Fill( dP_genreco_W_jj, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_426.Fill( dP_genreco_W_jj, weight_PreselSF_up * xfactor * weight_EFT );
      hist_427.Fill( dP_genreco_W_jj, weight_PreselSF_down * xfactor * weight_EFT );
      hist_428.Fill( dP_genreco_W_jj, weight_Trigger_up * xfactor * weight_EFT );
      hist_429.Fill( dP_genreco_W_jj, weight_Trigger_down * xfactor * weight_EFT );
      hist_430.Fill( dP_genreco_W_jj, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_431.Fill( dP_genreco_W_jj, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_432.Fill( dP_genreco_W_jj_leading, weight * xfactor * weight_EFT );
      hist_433.Fill( dP_genreco_W_jj_leading, weight_sf_photons_up * xfactor * weight_EFT );
      hist_434.Fill( dP_genreco_W_jj_leading, weight_sf_photons_down * xfactor * weight_EFT );
      hist_435.Fill( dP_genreco_W_jj_leading, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_436.Fill( dP_genreco_W_jj_leading, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_437.Fill( dP_genreco_W_jj_leading, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_438.Fill( dP_genreco_W_jj_leading, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_439.Fill( dP_genreco_W_jj_leading, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_440.Fill( dP_genreco_W_jj_leading, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_441.Fill( dP_genreco_W_jj_leading, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_442.Fill( dP_genreco_W_jj_leading, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_443.Fill( dP_genreco_W_jj_leading, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_444.Fill( dP_genreco_W_jj_leading, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_445.Fill( dP_genreco_W_jj_leading, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_446.Fill( dP_genreco_W_jj_leading, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_447.Fill( dP_genreco_W_jj_leading, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_448.Fill( dP_genreco_W_jj_leading, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_449.Fill( dP_genreco_W_jj_leading, weight_FracRV_up * xfactor * weight_EFT );
      hist_450.Fill( dP_genreco_W_jj_leading, weight_FracRV_down * xfactor * weight_EFT );
      hist_451.Fill( dP_genreco_W_jj_leading, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_452.Fill( dP_genreco_W_jj_leading, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_453.Fill( dP_genreco_W_jj_leading, weight_PreselSF_up * xfactor * weight_EFT );
      hist_454.Fill( dP_genreco_W_jj_leading, weight_PreselSF_down * xfactor * weight_EFT );
      hist_455.Fill( dP_genreco_W_jj_leading, weight_Trigger_up * xfactor * weight_EFT );
      hist_456.Fill( dP_genreco_W_jj_leading, weight_Trigger_down * xfactor * weight_EFT );
      hist_457.Fill( dP_genreco_W_jj_leading, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_458.Fill( dP_genreco_W_jj_leading, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_459.Fill( W_jj_tlv_leading->M(), weight * xfactor * weight_EFT );
      hist_460.Fill( W_jj_tlv_leading->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_461.Fill( W_jj_tlv_leading->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_462.Fill( W_jj_tlv_leading->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_463.Fill( W_jj_tlv_leading->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_464.Fill( W_jj_tlv_leading->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_465.Fill( W_jj_tlv_leading->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_466.Fill( W_jj_tlv_leading->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_467.Fill( W_jj_tlv_leading->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_468.Fill( W_jj_tlv_leading->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_469.Fill( W_jj_tlv_leading->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_470.Fill( W_jj_tlv_leading->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_471.Fill( W_jj_tlv_leading->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_472.Fill( W_jj_tlv_leading->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_473.Fill( W_jj_tlv_leading->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_474.Fill( W_jj_tlv_leading->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_475.Fill( W_jj_tlv_leading->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_476.Fill( W_jj_tlv_leading->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_477.Fill( W_jj_tlv_leading->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_478.Fill( W_jj_tlv_leading->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_479.Fill( W_jj_tlv_leading->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_480.Fill( W_jj_tlv_leading->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_481.Fill( W_jj_tlv_leading->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_482.Fill( W_jj_tlv_leading->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_483.Fill( W_jj_tlv_leading->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_484.Fill( W_jj_tlv_leading->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_485.Fill( W_jj_tlv_leading->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_486.Fill( dR_genreco_H_yy, weight * xfactor * weight_EFT );
      hist_487.Fill( dR_genreco_H_yy, weight_sf_photons_up * xfactor * weight_EFT );
      hist_488.Fill( dR_genreco_H_yy, weight_sf_photons_down * xfactor * weight_EFT );
      hist_489.Fill( dR_genreco_H_yy, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_490.Fill( dR_genreco_H_yy, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_491.Fill( dR_genreco_H_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_492.Fill( dR_genreco_H_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_493.Fill( dR_genreco_H_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_494.Fill( dR_genreco_H_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_495.Fill( dR_genreco_H_yy, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_496.Fill( dR_genreco_H_yy, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_497.Fill( dR_genreco_H_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_498.Fill( dR_genreco_H_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_499.Fill( dR_genreco_H_yy, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_500.Fill( dR_genreco_H_yy, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_501.Fill( dR_genreco_H_yy, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_502.Fill( dR_genreco_H_yy, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_503.Fill( dR_genreco_H_yy, weight_FracRV_up * xfactor * weight_EFT );
      hist_504.Fill( dR_genreco_H_yy, weight_FracRV_down * xfactor * weight_EFT );
      hist_505.Fill( dR_genreco_H_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_506.Fill( dR_genreco_H_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_507.Fill( dR_genreco_H_yy, weight_PreselSF_up * xfactor * weight_EFT );
      hist_508.Fill( dR_genreco_H_yy, weight_PreselSF_down * xfactor * weight_EFT );
      hist_509.Fill( dR_genreco_H_yy, weight_Trigger_up * xfactor * weight_EFT );
      hist_510.Fill( dR_genreco_H_yy, weight_Trigger_down * xfactor * weight_EFT );
      hist_511.Fill( dR_genreco_H_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_512.Fill( dR_genreco_H_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_513.Fill( dR_genreco_H_WW, weight * xfactor * weight_EFT );
      hist_514.Fill( dR_genreco_H_WW, weight_sf_photons_up * xfactor * weight_EFT );
      hist_515.Fill( dR_genreco_H_WW, weight_sf_photons_down * xfactor * weight_EFT );
      hist_516.Fill( dR_genreco_H_WW, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_517.Fill( dR_genreco_H_WW, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_518.Fill( dR_genreco_H_WW, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_519.Fill( dR_genreco_H_WW, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_520.Fill( dR_genreco_H_WW, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_521.Fill( dR_genreco_H_WW, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_522.Fill( dR_genreco_H_WW, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_523.Fill( dR_genreco_H_WW, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_524.Fill( dR_genreco_H_WW, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_525.Fill( dR_genreco_H_WW, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_526.Fill( dR_genreco_H_WW, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_527.Fill( dR_genreco_H_WW, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_528.Fill( dR_genreco_H_WW, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_529.Fill( dR_genreco_H_WW, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_530.Fill( dR_genreco_H_WW, weight_FracRV_up * xfactor * weight_EFT );
      hist_531.Fill( dR_genreco_H_WW, weight_FracRV_down * xfactor * weight_EFT );
      hist_532.Fill( dR_genreco_H_WW, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_533.Fill( dR_genreco_H_WW, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_534.Fill( dR_genreco_H_WW, weight_PreselSF_up * xfactor * weight_EFT );
      hist_535.Fill( dR_genreco_H_WW, weight_PreselSF_down * xfactor * weight_EFT );
      hist_536.Fill( dR_genreco_H_WW, weight_Trigger_up * xfactor * weight_EFT );
      hist_537.Fill( dR_genreco_H_WW, weight_Trigger_down * xfactor * weight_EFT );
      hist_538.Fill( dR_genreco_H_WW, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_539.Fill( dR_genreco_H_WW, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_540.Fill( dR_genreco_nu, weight * xfactor * weight_EFT );
      hist_541.Fill( dR_genreco_nu, weight_sf_photons_up * xfactor * weight_EFT );
      hist_542.Fill( dR_genreco_nu, weight_sf_photons_down * xfactor * weight_EFT );
      hist_543.Fill( dR_genreco_nu, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_544.Fill( dR_genreco_nu, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_545.Fill( dR_genreco_nu, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_546.Fill( dR_genreco_nu, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_547.Fill( dR_genreco_nu, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_548.Fill( dR_genreco_nu, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_549.Fill( dR_genreco_nu, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_550.Fill( dR_genreco_nu, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_551.Fill( dR_genreco_nu, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_552.Fill( dR_genreco_nu, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_553.Fill( dR_genreco_nu, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_554.Fill( dR_genreco_nu, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_555.Fill( dR_genreco_nu, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_556.Fill( dR_genreco_nu, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_557.Fill( dR_genreco_nu, weight_FracRV_up * xfactor * weight_EFT );
      hist_558.Fill( dR_genreco_nu, weight_FracRV_down * xfactor * weight_EFT );
      hist_559.Fill( dR_genreco_nu, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_560.Fill( dR_genreco_nu, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_561.Fill( dR_genreco_nu, weight_PreselSF_up * xfactor * weight_EFT );
      hist_562.Fill( dR_genreco_nu, weight_PreselSF_down * xfactor * weight_EFT );
      hist_563.Fill( dR_genreco_nu, weight_Trigger_up * xfactor * weight_EFT );
      hist_564.Fill( dR_genreco_nu, weight_Trigger_down * xfactor * weight_EFT );
      hist_565.Fill( dR_genreco_nu, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_566.Fill( dR_genreco_nu, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_567.Fill( dR_genreco_W_elnu, weight * xfactor * weight_EFT );
      hist_568.Fill( dR_genreco_W_elnu, weight_sf_photons_up * xfactor * weight_EFT );
      hist_569.Fill( dR_genreco_W_elnu, weight_sf_photons_down * xfactor * weight_EFT );
      hist_570.Fill( dR_genreco_W_elnu, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_571.Fill( dR_genreco_W_elnu, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_572.Fill( dR_genreco_W_elnu, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_573.Fill( dR_genreco_W_elnu, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_574.Fill( dR_genreco_W_elnu, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_575.Fill( dR_genreco_W_elnu, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_576.Fill( dR_genreco_W_elnu, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_577.Fill( dR_genreco_W_elnu, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_578.Fill( dR_genreco_W_elnu, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_579.Fill( dR_genreco_W_elnu, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_580.Fill( dR_genreco_W_elnu, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_581.Fill( dR_genreco_W_elnu, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_582.Fill( dR_genreco_W_elnu, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_583.Fill( dR_genreco_W_elnu, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_584.Fill( dR_genreco_W_elnu, weight_FracRV_up * xfactor * weight_EFT );
      hist_585.Fill( dR_genreco_W_elnu, weight_FracRV_down * xfactor * weight_EFT );
      hist_586.Fill( dR_genreco_W_elnu, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_587.Fill( dR_genreco_W_elnu, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_588.Fill( dR_genreco_W_elnu, weight_PreselSF_up * xfactor * weight_EFT );
      hist_589.Fill( dR_genreco_W_elnu, weight_PreselSF_down * xfactor * weight_EFT );
      hist_590.Fill( dR_genreco_W_elnu, weight_Trigger_up * xfactor * weight_EFT );
      hist_591.Fill( dR_genreco_W_elnu, weight_Trigger_down * xfactor * weight_EFT );
      hist_592.Fill( dR_genreco_W_elnu, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_593.Fill( dR_genreco_W_elnu, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_594.Fill( dP_genreco_H_yy, weight * xfactor * weight_EFT );
      hist_595.Fill( dP_genreco_H_yy, weight_sf_photons_up * xfactor * weight_EFT );
      hist_596.Fill( dP_genreco_H_yy, weight_sf_photons_down * xfactor * weight_EFT );
      hist_597.Fill( dP_genreco_H_yy, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_598.Fill( dP_genreco_H_yy, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_599.Fill( dP_genreco_H_yy, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_600.Fill( dP_genreco_H_yy, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_601.Fill( dP_genreco_H_yy, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_602.Fill( dP_genreco_H_yy, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_603.Fill( dP_genreco_H_yy, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_604.Fill( dP_genreco_H_yy, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_605.Fill( dP_genreco_H_yy, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_606.Fill( dP_genreco_H_yy, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_607.Fill( dP_genreco_H_yy, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_608.Fill( dP_genreco_H_yy, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_609.Fill( dP_genreco_H_yy, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_610.Fill( dP_genreco_H_yy, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_611.Fill( dP_genreco_H_yy, weight_FracRV_up * xfactor * weight_EFT );
      hist_612.Fill( dP_genreco_H_yy, weight_FracRV_down * xfactor * weight_EFT );
      hist_613.Fill( dP_genreco_H_yy, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_614.Fill( dP_genreco_H_yy, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_615.Fill( dP_genreco_H_yy, weight_PreselSF_up * xfactor * weight_EFT );
      hist_616.Fill( dP_genreco_H_yy, weight_PreselSF_down * xfactor * weight_EFT );
      hist_617.Fill( dP_genreco_H_yy, weight_Trigger_up * xfactor * weight_EFT );
      hist_618.Fill( dP_genreco_H_yy, weight_Trigger_down * xfactor * weight_EFT );
      hist_619.Fill( dP_genreco_H_yy, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_620.Fill( dP_genreco_H_yy, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_621.Fill( dP_genreco_H_WW, weight * xfactor * weight_EFT );
      hist_622.Fill( dP_genreco_H_WW, weight_sf_photons_up * xfactor * weight_EFT );
      hist_623.Fill( dP_genreco_H_WW, weight_sf_photons_down * xfactor * weight_EFT );
      hist_624.Fill( dP_genreco_H_WW, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_625.Fill( dP_genreco_H_WW, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_626.Fill( dP_genreco_H_WW, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_627.Fill( dP_genreco_H_WW, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_628.Fill( dP_genreco_H_WW, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_629.Fill( dP_genreco_H_WW, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_630.Fill( dP_genreco_H_WW, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_631.Fill( dP_genreco_H_WW, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_632.Fill( dP_genreco_H_WW, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_633.Fill( dP_genreco_H_WW, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_634.Fill( dP_genreco_H_WW, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_635.Fill( dP_genreco_H_WW, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_636.Fill( dP_genreco_H_WW, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_637.Fill( dP_genreco_H_WW, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_638.Fill( dP_genreco_H_WW, weight_FracRV_up * xfactor * weight_EFT );
      hist_639.Fill( dP_genreco_H_WW, weight_FracRV_down * xfactor * weight_EFT );
      hist_640.Fill( dP_genreco_H_WW, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_641.Fill( dP_genreco_H_WW, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_642.Fill( dP_genreco_H_WW, weight_PreselSF_up * xfactor * weight_EFT );
      hist_643.Fill( dP_genreco_H_WW, weight_PreselSF_down * xfactor * weight_EFT );
      hist_644.Fill( dP_genreco_H_WW, weight_Trigger_up * xfactor * weight_EFT );
      hist_645.Fill( dP_genreco_H_WW, weight_Trigger_down * xfactor * weight_EFT );
      hist_646.Fill( dP_genreco_H_WW, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_647.Fill( dP_genreco_H_WW, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_648.Fill( dP_genreco_nu, weight * xfactor * weight_EFT );
      hist_649.Fill( dP_genreco_nu, weight_sf_photons_up * xfactor * weight_EFT );
      hist_650.Fill( dP_genreco_nu, weight_sf_photons_down * xfactor * weight_EFT );
      hist_651.Fill( dP_genreco_nu, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_652.Fill( dP_genreco_nu, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_653.Fill( dP_genreco_nu, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_654.Fill( dP_genreco_nu, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_655.Fill( dP_genreco_nu, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_656.Fill( dP_genreco_nu, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_657.Fill( dP_genreco_nu, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_658.Fill( dP_genreco_nu, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_659.Fill( dP_genreco_nu, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_660.Fill( dP_genreco_nu, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_661.Fill( dP_genreco_nu, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_662.Fill( dP_genreco_nu, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_663.Fill( dP_genreco_nu, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_664.Fill( dP_genreco_nu, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_665.Fill( dP_genreco_nu, weight_FracRV_up * xfactor * weight_EFT );
      hist_666.Fill( dP_genreco_nu, weight_FracRV_down * xfactor * weight_EFT );
      hist_667.Fill( dP_genreco_nu, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_668.Fill( dP_genreco_nu, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_669.Fill( dP_genreco_nu, weight_PreselSF_up * xfactor * weight_EFT );
      hist_670.Fill( dP_genreco_nu, weight_PreselSF_down * xfactor * weight_EFT );
      hist_671.Fill( dP_genreco_nu, weight_Trigger_up * xfactor * weight_EFT );
      hist_672.Fill( dP_genreco_nu, weight_Trigger_down * xfactor * weight_EFT );
      hist_673.Fill( dP_genreco_nu, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_674.Fill( dP_genreco_nu, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_675.Fill( dP_genreco_W_elnu, weight * xfactor * weight_EFT );
      hist_676.Fill( dP_genreco_W_elnu, weight_sf_photons_up * xfactor * weight_EFT );
      hist_677.Fill( dP_genreco_W_elnu, weight_sf_photons_down * xfactor * weight_EFT );
      hist_678.Fill( dP_genreco_W_elnu, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_679.Fill( dP_genreco_W_elnu, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_680.Fill( dP_genreco_W_elnu, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_681.Fill( dP_genreco_W_elnu, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_682.Fill( dP_genreco_W_elnu, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_683.Fill( dP_genreco_W_elnu, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_684.Fill( dP_genreco_W_elnu, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_685.Fill( dP_genreco_W_elnu, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_686.Fill( dP_genreco_W_elnu, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_687.Fill( dP_genreco_W_elnu, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_688.Fill( dP_genreco_W_elnu, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_689.Fill( dP_genreco_W_elnu, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_690.Fill( dP_genreco_W_elnu, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_691.Fill( dP_genreco_W_elnu, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_692.Fill( dP_genreco_W_elnu, weight_FracRV_up * xfactor * weight_EFT );
      hist_693.Fill( dP_genreco_W_elnu, weight_FracRV_down * xfactor * weight_EFT );
      hist_694.Fill( dP_genreco_W_elnu, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_695.Fill( dP_genreco_W_elnu, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_696.Fill( dP_genreco_W_elnu, weight_PreselSF_up * xfactor * weight_EFT );
      hist_697.Fill( dP_genreco_W_elnu, weight_PreselSF_down * xfactor * weight_EFT );
      hist_698.Fill( dP_genreco_W_elnu, weight_Trigger_up * xfactor * weight_EFT );
      hist_699.Fill( dP_genreco_W_elnu, weight_Trigger_down * xfactor * weight_EFT );
      hist_700.Fill( dP_genreco_W_elnu, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_701.Fill( dP_genreco_W_elnu, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_702.Fill( gen_dR_jj, weight * xfactor * weight_EFT );
      hist_703.Fill( gen_dR_jj, weight_sf_photons_up * xfactor * weight_EFT );
      hist_704.Fill( gen_dR_jj, weight_sf_photons_down * xfactor * weight_EFT );
      hist_705.Fill( gen_dR_jj, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_706.Fill( gen_dR_jj, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_707.Fill( gen_dR_jj, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_708.Fill( gen_dR_jj, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_709.Fill( gen_dR_jj, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_710.Fill( gen_dR_jj, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_711.Fill( gen_dR_jj, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_712.Fill( gen_dR_jj, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_713.Fill( gen_dR_jj, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_714.Fill( gen_dR_jj, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_715.Fill( gen_dR_jj, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_716.Fill( gen_dR_jj, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_717.Fill( gen_dR_jj, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_718.Fill( gen_dR_jj, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_719.Fill( gen_dR_jj, weight_FracRV_up * xfactor * weight_EFT );
      hist_720.Fill( gen_dR_jj, weight_FracRV_down * xfactor * weight_EFT );
      hist_721.Fill( gen_dR_jj, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_722.Fill( gen_dR_jj, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_723.Fill( gen_dR_jj, weight_PreselSF_up * xfactor * weight_EFT );
      hist_724.Fill( gen_dR_jj, weight_PreselSF_down * xfactor * weight_EFT );
      hist_725.Fill( gen_dR_jj, weight_Trigger_up * xfactor * weight_EFT );
      hist_726.Fill( gen_dR_jj, weight_Trigger_down * xfactor * weight_EFT );
      hist_727.Fill( gen_dR_jj, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_728.Fill( gen_dR_jj, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_729.Fill( dR_jj_leading, weight * xfactor * weight_EFT );
      hist_730.Fill( dR_jj_leading, weight_sf_photons_up * xfactor * weight_EFT );
      hist_731.Fill( dR_jj_leading, weight_sf_photons_down * xfactor * weight_EFT );
      hist_732.Fill( dR_jj_leading, weight_sf_electrons_up * xfactor * weight_EFT );
      hist_733.Fill( dR_jj_leading, weight_sf_electrons_down * xfactor * weight_EFT );
      hist_734.Fill( dR_jj_leading, weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_735.Fill( dR_jj_leading, weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_736.Fill( dR_jj_leading, weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_737.Fill( dR_jj_leading, weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_738.Fill( dR_jj_leading, weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_739.Fill( dR_jj_leading, weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_740.Fill( dR_jj_leading, weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_741.Fill( dR_jj_leading, weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_742.Fill( dR_jj_leading, weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_743.Fill( dR_jj_leading, weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_744.Fill( dR_jj_leading, weight_sf_pileup_up * xfactor * weight_EFT );
      hist_745.Fill( dR_jj_leading, weight_sf_pileup_down * xfactor * weight_EFT );
      hist_746.Fill( dR_jj_leading, weight_FracRV_up * xfactor * weight_EFT );
      hist_747.Fill( dR_jj_leading, weight_FracRV_down * xfactor * weight_EFT );
      hist_748.Fill( dR_jj_leading, weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_749.Fill( dR_jj_leading, weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_750.Fill( dR_jj_leading, weight_PreselSF_up * xfactor * weight_EFT );
      hist_751.Fill( dR_jj_leading, weight_PreselSF_down * xfactor * weight_EFT );
      hist_752.Fill( dR_jj_leading, weight_Trigger_up * xfactor * weight_EFT );
      hist_753.Fill( dR_jj_leading, weight_Trigger_down * xfactor * weight_EFT );
      hist_754.Fill( dR_jj_leading, weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_755.Fill( dR_jj_leading, weight_electronVetoSF_down * xfactor * weight_EFT );
      hist_756.Fill( gen_W_jj_tlv->M(), weight * xfactor * weight_EFT );
      hist_757.Fill( gen_W_jj_tlv->M(), weight_sf_photons_up * xfactor * weight_EFT );
      hist_758.Fill( gen_W_jj_tlv->M(), weight_sf_photons_down * xfactor * weight_EFT );
      hist_759.Fill( gen_W_jj_tlv->M(), weight_sf_electrons_up * xfactor * weight_EFT );
      hist_760.Fill( gen_W_jj_tlv->M(), weight_sf_electrons_down * xfactor * weight_EFT );
      hist_761.Fill( gen_W_jj_tlv->M(), weight_sf_muons_id_up * xfactor * weight_EFT );
      hist_762.Fill( gen_W_jj_tlv->M(), weight_sf_muons_id_down * xfactor * weight_EFT );
      hist_763.Fill( gen_W_jj_tlv->M(), weight_sf_muons_iso_up * xfactor * weight_EFT );
      hist_764.Fill( gen_W_jj_tlv->M(), weight_sf_muons_iso_down * xfactor * weight_EFT );
      hist_765.Fill( gen_W_jj_tlv->M(), weight_sf_ljets_id_up * xfactor * weight_EFT );
      hist_766.Fill( gen_W_jj_tlv->M(), weight_sf_ljets_id_down * xfactor * weight_EFT );
      hist_767.Fill( gen_W_jj_tlv->M(), weight_sf_ljets_btag_up * xfactor * weight_EFT );
      hist_768.Fill( gen_W_jj_tlv->M(), weight_sf_ljets_btag_down * xfactor * weight_EFT );
      hist_769.Fill( gen_W_jj_tlv->M(), weight_sf_bjets_id_up * xfactor * weight_EFT );
      hist_770.Fill( gen_W_jj_tlv->M(), weight_sf_bjets_id_down * xfactor * weight_EFT );
      hist_771.Fill( gen_W_jj_tlv->M(), weight_sf_pileup_up * xfactor * weight_EFT );
      hist_772.Fill( gen_W_jj_tlv->M(), weight_sf_pileup_down * xfactor * weight_EFT );
      hist_773.Fill( gen_W_jj_tlv->M(), weight_FracRV_up * xfactor * weight_EFT );
      hist_774.Fill( gen_W_jj_tlv->M(), weight_FracRV_down * xfactor * weight_EFT );
      hist_775.Fill( gen_W_jj_tlv->M(), weight_LooseMvaSF_up * xfactor * weight_EFT );
      hist_776.Fill( gen_W_jj_tlv->M(), weight_LooseMvaSF_down * xfactor * weight_EFT );
      hist_777.Fill( gen_W_jj_tlv->M(), weight_PreselSF_up * xfactor * weight_EFT );
      hist_778.Fill( gen_W_jj_tlv->M(), weight_PreselSF_down * xfactor * weight_EFT );
      hist_779.Fill( gen_W_jj_tlv->M(), weight_Trigger_up * xfactor * weight_EFT );
      hist_780.Fill( gen_W_jj_tlv->M(), weight_Trigger_down * xfactor * weight_EFT );
      hist_781.Fill( gen_W_jj_tlv->M(), weight_electronVetoSF_up * xfactor * weight_EFT );
      hist_782.Fill( gen_W_jj_tlv->M(), weight_electronVetoSF_down * xfactor * weight_EFT );
      //[[[end]]]

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
  vector<vseva::DataSet*> datasets = get_datasets( false );

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














