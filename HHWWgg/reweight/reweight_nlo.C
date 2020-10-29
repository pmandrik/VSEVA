
// INPUT DATA FOR REWEIGHT CARVALHO ==================================================================================================
vector<double> get_CMS_EFT_benchmarks( string name, string year, bool cms ){
  vector<double> answer;
  if( name == "SM" or name == "sm" ) answer = {1, 1, 0, 0, 0};
  if( name == "box" or name == "BOX" ) answer = {0, 1, 0, 0, 0};
  if( name ==  "1" ) answer = {7.5, 1, -1, 0, 0};
  if( name ==  "2" ) answer = {1.0, 1.0, 0.5, -0.8, 0.6};
  if( name ==  "3" ) answer = {1.0, 1.0, -1.5, 0.0, -0.8};
  if( name ==  "4" ) answer = {-3.5, 1.5, -3.0, 0.0, 0.0};
  if( name ==  "5" ) answer = {1.0, 1.0, 0.0, 0.8, -1.0};
  if( name ==  "6" ) answer = {2.4, 1.0, 0.0, 0.2, -0.2};
  if( name ==  "7" ) answer = {5.0, 1.0, 0.0, 0.2, -0.2};
  if( name ==  "8" ) answer = {15.0, 1.0, 0.0, -1.0, 1.0};
  if( name ==  "9" ) answer = {1.0, 1.0, 1.0, -0.6, 0.6};
  if( name ==  "10" ) answer = {10.0, 1.5, -1.0, 0.0, 0.0};
  if( name ==  "11" ) answer = {2.4, 1.0, 0.0, 1.0, -1.0};
  if( name ==  "12" ) answer = {15.0, 1.0, 1.0, 0.0, 0.0};

  if( (year == "2017" or year == "2018") and answer.size() and cms )
    answer[4] = 1.0;
    double tr = answer[0];
    answer[0] = answer[1];
    answer[1] = tr;
  return answer;
}

double get_eft_xsec(string mark, string order, int year, bool cms_fake){
    vector<double> answer = get_CMS_EFT_benchmarks(mark, to_string(year), cms_fake);
    double ct  = answer[1];
    double ctt = answer[2];
    double c3  = answer[0];
    double cg  = answer[3] * 2. / 3.;
    double cgg = answer[4] * (-1.) / 3.;

    vector<double> A_values_lo  = {2.08059, 10.2011, 0.27814, 0.314043, 12.2731, -8.49307, -1.35873, 2.80251, 2.48018, 14.6908, -1.15916, -5.51183, 0.560503, 2.47982, 2.89431};
    vector<double> A_values_nlo  = {2.23389, 12.4598, 0.342248, 0.346822, 13.0087, -9.6455, -1.57553, 3.43849, 2.86694, 16.6912, -1.25293, -5.81216, 0.649714, 2.85933, 3.14475, -0.00816241, 0.0208652, 0.0168157, 0.0298576, -0.0270253, 0.0726921, 0.0145232, 0.123291};
    
    vector<double> couplings = { pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
                  ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
                  ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
                  pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
                  pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg };

    double sm_xsection_lo  = 16.60711696;
    double sm_xsection_nlo = 32.95;
    double answer_xsection = 0;
    
    if( order == "lo" ){
      for(int i = 0; i < A_values_lo.size(); i++)
        answer_xsection += A_values_lo.at(i) * couplings.at(i);
      return answer_xsection * sm_xsection_lo;
    }
    
    for(int i = 0; i < A_values_nlo.size(); i++)
      answer_xsection += A_values_nlo.at(i) * couplings.at(i);
    return answer_xsection * sm_xsection_nlo;
}

void get_A_values( string input_name, vector< vector<double>> & answer ){
  std::string line;
  std::ifstream infile( input_name );
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    answer.push_back( vector<double>() );
    string value;
    while (std::getline(iss, value, ',')) {
      answer[ answer.size()-1 ].push_back( atof(value.c_str()) );
    }
  }

  /*
  for(int i = 0 ; i < answer.size(); i++){
    for(int j = 0 ; j < answer.at(i).size(); j++){
      cout << answer.at(i).at(j) << " ";
    }
    cout << endl;
  }
  */

  return answer;
}

class ReweightGudrin {
  double bin_step;
  vector< vector<double>> A_values_lo, A_values_nlo;

  public:
  // https://arxiv.org/abs/1806.05162 based
  ReweightGudrin(string input_lo="LO-Ais-13TeV.csv", string input_nlo="NLO-Ais-13TeV.csv", int bin_step=20){
    get_A_values( input_lo, A_values_lo );;
    get_A_values( input_nlo, A_values_nlo );
    this->bin_step = bin_step;
  }

  vector<double> CouplingsToEWChL(double k_lambda, double k_t, double c2, double cg_, double c2g){
    double ct  = k_t;
    double ctt = c2;
    double c3  = k_lambda;
    double cg  = cg_ * 2. / 3.;
    double cgg = c2g * (-1.) / 3.;
    vector<double> answer = { c3, ct, ctt, cg, cgg };
    return answer;
  }

  vector<double> GetEFTBenchmark(string name, string year, bool cms = true){
    vector<double> couplings = get_CMS_EFT_benchmarks( name, year, cms );
    return CouplingsToEWChL(couplings[0], couplings[1], couplings[2], couplings[3], couplings[4]);
  }

  double GetDiffXsection(double m_hh, vector<double> eft_parameters, string order="nlo"){
    if(m_hh < 250) return 0;
    double c3 , ct, ctt, cg, cgg;
    c3 = eft_parameters[0];
    ct = eft_parameters[1];
    ctt = eft_parameters[2];
    cg = eft_parameters[3];
    cgg = eft_parameters[4];

    // cout << c3 << " " <<  ct << " " << ctt << " " << cg << " " << cgg << endl;
    vector<double> couplings = { pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
                  ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
                  ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
                  pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
                  pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg };
    
    vector< vector<double> > * A_map = & A_values_nlo;
    if(order=="lo"){
      A_map = & A_values_lo;
    }

    for(int i = 0; i < A_map->size(); i++){
      vector<double> & values = A_map->at(i);
      double mass = values.at(0) + bin_step/2;
      // cout << m_hh << " " << mass << endl;
      if(m_hh > mass) continue;
      double weight = 0;
      for( int j = 1; j < values.size(); j++ ){
        // cout << values.at(j) << " " << couplings.at(j-1) << " " << values.at(j) * couplings.at(j-1) << endl;
        weight += values.at(j) * couplings.at(j-1);
      }
      return weight;
    }
    return 0;
  }
};

void reweight_file(string inp_path, vector<string> inp_file_names, string inp_tree_name, string inp_order, vector<string> inp_benchmarks, vector<double> inp_factors, string out_path, string out_file_name){
  ReweightGudrin r_gudrin = ReweightGudrin();
  string files_to_merge = "";
  for(int i = 0; i < inp_file_names.size(); i++){
    string inp_file_name = inp_file_names.at(i);
    // string inp_tree_name = inp_tree_names.at(i);
    // string inp_order = inp_orders.at(i);
    string inp_benchmark = inp_benchmarks.at(i);
    double factor = inp_factors.at(i);

    vector<double> inp_benchmark_couplings   = r_gudrin.GetEFTBenchmark( inp_benchmark, "2017" );
    string input_file_name_tmp = out_path + "/tmp_" + inp_file_name;
    files_to_merge += input_file_name_tmp + " ";

    TFile * inp_file = new TFile( (inp_path + inp_file_name).c_str(), "READ");
    TTree * inp_tree = (TTree*)inp_file->Get( inp_tree_name.c_str() );

    cout << " ... add " << inp_file_name << " " << inp_tree_name << endl;

    inp_tree->SetBranchStatus("*", 0);
    inp_tree->SetBranchStatus("weight*", 1);
    vector<string> vars_to_use = {"channel", "gen_Hi_yy_tlv", "gen_HHi_tlv", "m_yy", "mc_weight", "lumiWeight", "weight", "dR_yy", "y1_tlv", "y2_tlv", "dR_jj", "dR_WW", "dR_HH", "dPhi_nuL", "H_yy_tlv", "ljet1_tlv", "ljet2_tlv", "yy_mva", "H_WW_tlv", "lep_leading_tlv"};
    for(string var : vars_to_use){
      inp_tree->SetBranchStatus( var.c_str(), 1);
    }

    TFile * out_file = new TFile( input_file_name_tmp.c_str(), "RECREATE");
    TTree * out_tree = inp_tree->CopyTree("", "");
    out_tree->SetName( "data" );

    vector<string> out_benchmars = {"SM", "box", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    vector<vector<double>> out_benchmars_couplings;
    vector<double*> weight_lo, weight_nlo;
    vector<TBranch*>  br_weight_lo, br_weight_nlo;
    for(int j = 0; j < out_benchmars.size(); j++){
      weight_lo.push_back( new double() );
      weight_nlo.push_back( new double() );
      br_weight_lo.push_back(  out_tree->Branch( ("weight_lo_" + out_benchmars.at(j)).c_str(),  weight_lo.at(j) )); 
      br_weight_nlo.push_back( out_tree->Branch( ("weight_nlo_" + out_benchmars.at(j)).c_str(), weight_nlo.at(j) )); 
      out_benchmars_couplings.push_back( r_gudrin.GetEFTBenchmark( out_benchmars.at(j), "2017" ) );
    }

    TTreeFormula m_HH_f("gen_HHi_tlv.M()", "gen_HHi_tlv.M()", inp_tree);
    // TTreeFormula cos_f("TMath::Abs( gen_Hi_yy_tlv.CosTheta() )", "TMath::Abs( gen_Hi_yy_tlv.CosTheta() )", inp_tree);

    for(int j = 0; j < out_tree->GetEntries(); j++){
      out_tree->GetEntry(j); 

      double m_HH = m_HH_f.EvalInstance();
      double dx_inp = r_gudrin.GetDiffXsection( m_HH, inp_benchmark_couplings, inp_order );
      for(int j = 0; j < out_benchmars.size(); j++){
        double dx_lo  = r_gudrin.GetDiffXsection( m_HH, out_benchmars_couplings[j], "lo" );
        double dx_nlo = r_gudrin.GetDiffXsection( m_HH, out_benchmars_couplings[j], "nlo" );

        if(dx_inp < 0.00000001){
          *(weight_lo[j]) = 0;
          *(weight_nlo[j]) = 0;
        }
        else {
          *(weight_lo[j]) = dx_lo / dx_inp * factor;
          *(weight_nlo[j]) = dx_nlo / dx_inp * factor;
        }
        br_weight_lo[j]->Fill();
        br_weight_nlo[j]->Fill();
      }
    }
    out_tree->Write();
    out_file->Close();
    inp_file->Close();
  }

  cout << "hadd -f " + out_path + "/" + out_file_name + " " + files_to_merge << endl;
  system( ("hadd -f " + out_path + "/" + out_file_name + " " + files_to_merge).c_str() );
  system( ("rm " + files_to_merge).c_str() );
}

void update_file(string inp_path, string inp_file_name, string inp_tree_name, string inp_order, string inp_benchmark, double factor){
  ReweightGudrin r_gudrin = ReweightGudrin();

  vector<double> inp_benchmark_couplings   = r_gudrin.GetEFTBenchmark( inp_benchmark, "2017" );
  TFile * inp_file = new TFile( (inp_path + inp_file_name).c_str(), "UPDATE");
  TTree * inp_tree = (TTree*)inp_file->Get( inp_tree_name.c_str() );
  cout << " ... add " << inp_file_name << " " << inp_tree_name << endl;

  vector<string> out_benchmars = {"SM", "box", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
  vector<vector<double>> out_benchmars_couplings;
  vector<double*> weight_lo, weight_nlo;
  vector<TBranch*>  br_weight_lo, br_weight_nlo;
  for(int j = 0; j < out_benchmars.size(); j++){
    weight_lo.push_back( new double() );
    weight_nlo.push_back( new double() );
    br_weight_lo.push_back(  inp_tree->Branch( ("weight_lo_" + out_benchmars.at(j)).c_str(),  weight_lo.at(j) )); 
    br_weight_nlo.push_back( inp_tree->Branch( ("weight_nlo_" + out_benchmars.at(j)).c_str(), weight_nlo.at(j) )); 
    out_benchmars_couplings.push_back( r_gudrin.GetEFTBenchmark( out_benchmars.at(j), "2017" ) );
  }

  TTreeFormula m_HH_f("gen_HHi_tlv.M()", "gen_HHi_tlv.M()", inp_tree);
  // TTreeFormula cos_f("TMath::Abs( gen_Hi_yy_tlv.CosTheta() )", "TMath::Abs( gen_Hi_yy_tlv.CosTheta() )", inp_tree);

    for(int j = 0; j < inp_tree->GetEntries(); j++){
      inp_tree->GetEntry(j); 

      double m_HH = m_HH_f.EvalInstance();
      double dx_inp = r_gudrin.GetDiffXsection( m_HH, inp_benchmark_couplings, inp_order );
      for(int j = 0; j < out_benchmars.size(); j++){
        double dx_lo  = r_gudrin.GetDiffXsection( m_HH, out_benchmars_couplings[j], "lo" );
        double dx_nlo = r_gudrin.GetDiffXsection( m_HH, out_benchmars_couplings[j], "nlo" );

        if(dx_inp < 0.00000001){
          *(weight_lo[j]) = 0;
          *(weight_nlo[j]) = 0;
        }
        else {
          *(weight_lo[j]) = dx_lo / dx_inp * factor;
          *(weight_nlo[j]) = dx_nlo / dx_inp * factor;
        }
        br_weight_lo[j]->Fill();
        br_weight_nlo[j]->Fill();
      }
    }
    inp_tree->Write();
    inp_file->Close();
}


void reweight_nlo(){



  vector<string> inp_files  = {"hzura_2017_SM_fsim_v0.root", "hzura_2017_1_fsim_v0.root", "hzura_2017_2_fsim_v0.root", "hzura_2017_3_fsim_v0.root", "hzura_2017_4_fsim_v0.root", "hzura_2017_5_fsim_v0.root", "hzura_2017_6_fsim_v0.root", "hzura_2017_7_fsim_v0.root", "hzura_2017_9_fsim_v0.root", "hzura_2017_10_fsim_v0.root", "hzura_2017_11_fsim_v0.root", "hzura_2017_12_fsim_v0.root"};
  vector<string> benchmarks = {"SM", "0", "1", "2", "3", "4", "5", "6", "8", "9", "10", "11"};
  vector<double> factors    = {399773/1000000., 387757/1000000., 399742/1000000., 399780/1000000., 399752/1000000., 365791/1000000., 373777/1000000., 377789/1000000., 399735/1000000.,365788/1000000., 399751/1000000., 399752/1000000.};

  string inp_path="/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_c1/";
  string out_path="/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted_2017/";

  vector<string> systematics_all = {"FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp","JEC_AbsoluteUp", "JEC_AbsoluteDown", "JEC_Absolute_2017Up", "JEC_Absolute_2017Down", "JEC_BBEC1Up", "JEC_BBEC1Down", "JEC_BBEC1_2017Up", "JEC_BBEC1_2017Down", "JEC_EC2Up", "JEC_EC2Down", "JEC_EC2_2017Up", "JEC_EC2_2017Down", "JEC_FlavorQCDUp", "JEC_FlavorQCDDown", "JEC_HFUp", "JEC_HFDown", "JEC_HF_2017Up", "JEC_HF_2017Down", "JEC_RelativeBalUp", "JEC_RelativeBalDown", "JEC_RelativeSample_2017Up", "JEC_RelativeSample_2017Down", "UnclusteredMETUp", "UnclusteredMETDown"};
  for(auto systematic : systematics_all){
    for(int i = 0; i < inp_files.size(); i++){
      cout << inp_files.at(i) << " ... " << systematic << endl;
      update_file(inp_path, inp_files.at(i), systematic + "_Events", "lo", benchmarks.at(i), factors.at(i));
      cout << inp_files.at(i) << " ... done! " << systematic << endl;
    }
  }

  return;

  vector<string> systematics = {"Def"};
  for(auto systematic : systematics){
    string fname = "hzura_2017_EFT_all_v1_" + systematic + "_Events_ch78.root";
    cout << fname << " ..." << endl;
    reweight_file(inp_path, inp_files, systematic + "_Events", "lo", benchmarks, factors, out_path, fname);
    cout << fname << " ... done!" << endl;
  }

}

















