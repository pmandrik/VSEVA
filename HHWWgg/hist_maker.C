
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
    systematics = []
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
      var.xfactor = "weight * (m_yy < 115 || m_yy > 135) * ( int(channel)==7 || int(channel)==8 )"
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
      break
      for name in ["weight_" + sys + "_up", "weight_" + sys + "_down"]:
        cog.outl( "Double_t " + name + "   = 1;" )
        cog.outl( "if( tree->GetBranch( \"" + name + "\") ){" )
        cog.outl( "tree->SetBranchAddress(\"" + name + "\", &" + name + ");" )
        cog.outl("} else cout << \"DontHave a branch with name = " + name + "\" << endl;" )
  ]]]*/
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
      if( not dataset->IsSignal() )
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














