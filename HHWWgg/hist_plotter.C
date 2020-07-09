
#include "analyse_cfg.C"

#include "/afs/cern.ch/user/p/pmandrik/public/PMANDRIK_LIBRARY/pmlib_root_hist_drawer.hh"
using namespace mRoot;

// source /cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
// source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

/*

source /cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh
*/

using namespace vseva;

vector<vseva::DataSet*> get_processes(const vector<vseva::DataSet*> & channels, vector<string> usefull_channels){
  vector<vseva::DataSet*> answer;

  for(auto ch : channels){
    int ifind = -1;
    for(int i = 0; i < answer.size(); i++)
      if(answer.at(i)->latex_name == ch->latex_name) ifind = i;

    if( usefull_channels.size() ){
      int jfind = -1;
      for(int i = 0; i < usefull_channels.size(); i++)
        if(usefull_channels.at(i) == ch->latex_name) jfind = i;
      if(jfind == -1) continue;
    }
    
    if(ifind != -1){
      vseva::DataSet * old_ch = answer.at(ifind);
      old_ch->files.push_back( ch->process_name );

      for(TH1D* hist_new : ch->hists){
        for(TH1D* hist_old : old_ch->hists){
          if( string(hist_old->GetTitle()) == string(hist_new->GetTitle()) ){
            hist_old->Add( hist_new );
          }
        }
      }
    } else { 
      vseva::DataSet * new_ch = new vseva::DataSet( * ch );    

      for(TH1D* hist : new_ch->hists){
        hist->SetName( (ch->short_name + "_" + hist->GetTitle()).c_str() );
      }

      answer.push_back( new_ch );  
    }
  }

  return answer;
}

vector<PlotVariable> get_sys_variables(){
  vector<PlotVariable> answer = { 
    PlotVariable("m_yy", "M_{#gamma#gamma} [GeV]", 100, 160),
    PlotVariable("H_WW_tlv_M", "M_{WW} [GeV]" , 0, 1000),
   };
  return answer;
}

vector<PlotVariable> get_variables(){
    vector<PlotVariable> subanswer = { PlotVariable("m_yy", "M_{#gamma#gamma} [GeV]", 100, 160),
        PlotVariable("y1_Et_div_m_yy", "#frac{E_{T}^{#gamma_{leading}}}{M_{#gamma#gamma}}", 0, 2),
        PlotVariable("y2_Et_div_m_y",  "#frac{E_{T}^{#gamma_{second}}}{M_{#gamma#gamma}}", 0, 2),
        PlotVariable("dR_yy", "#Delta R(#gamma,#gamma)", 0, 5),
        PlotVariable("dR_jj", "#Delta R(j,j)", 0, 5),
        PlotVariable("dR_WL", "#Delta R(W_{l#nu},l_{leading})", 0, 5),
        PlotVariable("dR_WW", "#Delta R(W,W)", 0, 5),
        PlotVariable("dR_HH", "#Delta R(H,H)", 0, 5),
        PlotVariable("W_jj_tlv_M", "M_{W_{jj}} [GeV]", 0, 100),
        PlotVariable("W_elnu_tlv_M", "M_{W_{l#nu}} [GeV]", 0, 100),
        PlotVariable("H_WW_tlv_M", "M_{WW} [GeV]" , 0, 1000),

        PlotVariable("W_elnu_tlv_M", "M_{W_{#ell#nu}} [GeV]", 0, 400),
        PlotVariable("H_WW_tlv_M", "M_{WW} [GeV]" , 0, 1000),

        // PlotVariable("gen_HH_tlv_Pt", "p^{MC}_T(HH), [GeV]", 0, 400],
        // PlotVariable("gen_HH_tlv_M",  "M^{MC}_{HH}, [GeV]", 0, 800],
    };

  for(int i = 0; i < subanswer.size(); i++){
    for(int j = 0; j < 13; j++){
      subanswer[i].processes_exclude.push_back( "EFT3_" + to_string(j) + "_rw" );
      subanswer[i].processes_exclude.push_back( "EFT10_" + to_string(j) + "_rw" );
    }
  }

  vector<PlotVariable> signal_only_vars = {
        PlotVariable("dR_genreco_H_yy",   "#Delta R(H_{#gamma#gamma}, H_{#gamma#gamma}^{gen})" , 0, 5),
        PlotVariable("dR_genreco_H_WW",   "#Delta R(H_{WW}, H_{WW}^{gen})" , 0, 5),
        PlotVariable("dR_genreco_nu",     "#Delta R(#nu, #nu^{gen})" , 0, 5),
        PlotVariable("dR_genreco_W_elnu", "#Delta R(W_{l#nu}, W_{l#nu})" , 0, 5),
        PlotVariable("dP_genreco_H_yy",   "|#vec{p}(H_{#gamma#gamma}) - #vec{p}(H_{#gamma#gamma}^{gen})|" , 0, 400),
        PlotVariable("dP_genreco_H_WW",   "|#vec{p}(H_{WW}) - #vec{p}(H_{WW}^{gen})|" , 0, 400),
        PlotVariable("dP_genreco_nu",     "|#vec{p}(#nu) - #vec{p}(#nu^{gen})|" , 0, 400),
        PlotVariable("dP_genreco_W_elnu", "|#vec{p}(W_{l#nu}) - #vec{p}(W_{l#nu}^{gen})|", 0, 400),
  };
  for(auto item : signal_only_vars){
    item.processes_include.push_back( "EFT3"  );
    item.processes_include.push_back( "EFT10" );
    subanswer.push_back( item );
  }

  for(int i = 0; i < 13; i++){
    break;
    auto p1 = PlotVariable("gen_HHi_tlv_M", "M_{HH} [GeV]", 0, 1200);
    auto p2 = PlotVariable("gen_Hi_yy_tlv_CosTheta", "|cos#theta^{*}|", 0, 1);
    p1.output_name = "gen_HHi_tlv_M"+ to_string(i);
    p2.output_name = "gen_Hi_yy_tlv_CosTheta"+ to_string(i);
    p1.processes_include.push_back( "EFT3_" + to_string(i) + "_rw" );
    p2.processes_include.push_back( "EFT3_" + to_string(i) + "_rw" );
    p1.processes_include.push_back( "EFT10_" + to_string(i) + "_rw" );
    p2.processes_include.push_back( "EFT10_" + to_string(i) + "_rw" );
    if(i == 3 or i == 10){
      p1.processes_include.push_back( "EFT" + to_string(i) );
      p2.processes_include.push_back( "EFT" + to_string(i) );
    }
    subanswer.push_back( p1 );
    subanswer.push_back( p2 );
  }

  vector<PlotVariable> answer = { };
  for(PlotVariable var : subanswer){
    PlotVariable v0 = var;
    v0.key += "_weight";
    answer.push_back( v0 );
  }
  return answer;
}

CustomPlotVariables get_compare_variables( vector<string> names, vector<string> titles, string label, double xmin, double xmax, string dataset ){
  CustomPlotVariables answer;
  for(int i = 0 ; i < names.size(); i++){
    string name  = names.at(i);
    string title = titles.at(i);
    PlotVariable p = PlotVariable( name ,         title, xmin, xmax, dataset);
    answer.variables.push_back( p );
  }
  answer.label = label;
  return answer; 
}

vector<CustomPlotVariables> get_variables_custome(){
  vector<CustomPlotVariables> subanswers = {
    get_compare_variables( {"dR_genreco_W_jj", "dR_genreco_W_jj_leading"},  {"selected jets", "leading jets"}, "#Delta R (W_{jj}, W_{jj}^{gen})",           0, 5, "EFT3"),
    get_compare_variables( {"dP_genreco_W_jj", "dP_genreco_W_jj_leading"},  {"selected jets", "leading jets"}, "|#vec{p}(W_{jj}) - #vec{p}(W_{jj}^{gen})|", 0, 5, "EFT3"),
    get_compare_variables( {"gen_W_jj_tlv_M", "W_jj_tlv_M", "W_jj_tlv_leading_M"},  {"gen jets", "selected jets", "leading jets"}, "M W_{jj} [GeV]", 10, 300, "EFT3"),
    get_compare_variables( {"gen_dR_jj", "dR_jj", "dR_jj_leading"}, {"gen jets",  "selected jets", "leading jets"}, "#Delta R (j, j)", 0, 5, "EFT3"),
  };

  for(int i = 0; i < subanswers.size(); i++){
    subanswers[i].weight      = "weight";
    subanswers[i].draw_option = "tmva";
    subanswers[i].output_name     = to_string(i);
  }

  return subanswers;
}

void hist_plotter(){
  vector<vseva::DataSet*> datasets  = get_datasets( false );
  vector<vseva::DataSet*> processes = get_processes( datasets, {});
  map<string, string> name_x_latexn_processes;
  map<string, vseva::DataSet*> name_x_process;
  for( auto process : processes ){
    name_x_latexn_processes[ process->short_name ] = process->latex_name;
    name_x_process[ process->short_name ] = process;
  }

  string out_file_name = "./output/total_plots.root";
  TFile * file_out = TFile::Open( out_file_name.c_str(), "RECREATE");

  string inp_file_name = "./output/total.root";
  TFile * file_inp = TFile::Open( inp_file_name.c_str(), "READ");

  vector<TH1D*> * hists = get_all_with_type<TH1D>(file_inp, "TH1D");
  map< string, TH1D*> hists_map;
  for(auto hist: *hists){
    // cout << "add hist " << hist->GetName()  << endl; 
    hists_map[ hist->GetName() ] = hist;
  }

/*
  vector<CustomPlotVariables> cust_variables = get_variables_custome();
  for(auto var : cust_variables){
    file_inp->cd();
    HistDrawer<> drawer = HistDrawer<>();
    for( auto svar : var.variables ){
      string name = svar.process_name + "_" + svar.key + "_" + var.weight;
      cout << "add ... "   << name << endl;
      auto hist_find = hists_map.find( name );
      if( hist_find == hists_map.end() ){
        cout << "can't find this hist" << endl;
        continue;
      }
      TH1D* hist = hist_find->second;

      string title = svar.label;
      string type  = "D";
      auto it = name_x_process.find( svar.process_name );
      if ( it != name_x_process.end() ){
        title += " " + it->second->latex_name;
        type   = it->second->type;
      }
      else{                        
        title += " " + svar.process_name;
      }
      cout <<  hist << " " << svar.process_name << " (" << title << ") " << type << endl;

      hist->SetTitle( title.c_str() );
      drawer.Add( hist, type );
    }
    
    if( drawer.IsEmpty() ) continue;
    TCanvas* canv = vseva::draw_hists_CMS( & drawer, "./output/", "CUST_" + var.output_name + ".png", var.label, "", var.draw_option );
  }

  vector<PlotVariable> variables = get_variables();
  for(auto variable : variables){
    cout << "process variable " << variable.key << endl;
    file_inp->cd();
    HistDrawer<> drawer = HistDrawer<>();
    
    // cout << "QQQ" << endl;
    for(auto process : processes){
      if( process->sys ) continue;
      cout << "   check ... " << process->short_name << " " << variable.CheckProcess( process->short_name ) << endl;
      if( not variable.CheckProcess( process->short_name ) ) continue;

      string name = process->short_name + "_" + variable.key;
      cout << name << endl;
      TH1D* hist = hists_map.find( name )->second;
      cout <<  hist << " " << process->latex_name << " " << process->process_name << endl;

      // if( process->signal ) hist->Scale( 2.0 );
      // if( variable.label == string("BDT") ) hist->Rebin(2000);
      // cout <<  process->latex_name << endl;

      hist->SetTitle( process->latex_name.c_str() );
      drawer.Add( hist, process->type);
    }
    
    // cout << variable.label << " >>> " << variable.key << endl;

    string option = "tmva";
    cout << variable.key << endl;
    if( variable.key == "H_m_xfactor") option = "overset";
    // else continue;

    cout << " ==== > " << option << endl;
    // TCanvas* canv = mRoot::draw_hists_FCC(& drawer, "./output/plots/", "B_" + variable.key + "_tmva_fcc.png", variable.label, "", option);
    // TCanvas* canv = mRoot::draw_hists_FCC(& drawer, "./output/", "B_" + variable.key + ".png", variable.label, "", option);
    
    if( drawer.IsEmpty() ) continue;
    TCanvas* canv = vseva::draw_hists_CMS(& drawer, "./output/", "B_" + variable.GetOutputName() + ".png", variable.label, "", option);
    file_out->cd();
    canv->SetName( variable.key.c_str() );
    canv->Write();
  }
*/

  vector <int> indexes = getNiceColors(200);
  vector<PlotVariable> sys_variables = get_sys_variables();
  for(auto variable : sys_variables){
    file_inp->cd();

    for(auto process : processes){
      if(process->sys) continue;
      if(process->IsData()) continue;
      string name = process->short_name + "_" + variable.key + "_weight";
      cout << "process central variable = " << name << endl;
      TH1D* h = hists_map.find( name )->second;
      
      cout << h << endl;

      int color_i = 0;
      h->SetLineColor( 1 );
      h->SetLineWidth( 3 );

      // ===--===--===--===--===--===--===--===--===--===--===
      vector<TH1D*> hists_others;
      // vector<string> alt_sys = {"sf_photons", "sf_electrons", "sf_muons_id", "sf_muons_iso", "sf_ljets_id", "sf_ljets_btag", "sf_bjets_id", "sf_bjets_btag", "sf_pileup", "FracRV", "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF"};
      vector<string> alt_sys = {"sf_electrons", "sf_pileup", "FracRV", "LooseMvaSF", "PreselSF", "Trigger",  "electronVetoSF"};
      vector<string>  fixes = {"up", "down"};
      for( auto alt : alt_sys ){
        for( auto fix : fixes ){
          string name       = process->short_name + "_" + variable.key + "_weight_" + alt + "_" + fix;
          cout << "process alt variable = " << name << endl;
          auto find = hists_map.find( name );
          if( find == hists_map.end() ) cout << "!!!" << endl;
          TH1D* hists_other = hists_map.find( name )->second;
          hists_other->SetName( name.c_str() );
          hists_other->SetTitle( (alt + " " + fix).c_str() );
          hists_others.push_back( hists_other );
        }
      }

      // ===--===--===--===--===--===--===--===--===--===--===
      vector<string> sys_ttres = {"FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp",
"JERUp", "JERDown", "JECUp", "JECDown", "UnclusteredMETUp", "UnclusteredMETDown"};
      for( auto alt : sys_ttres ){
        string name = process->short_name + "_X_" + alt + "_" + variable.key + "_weight";
        cout << "process alt variable = " << name << endl;
        auto find = hists_map.find( name );
        if( find == hists_map.end() ) cout << "!!!" << endl;
        TH1D* hists_other = hists_map.find( name )->second;
        hists_other->SetName( name.c_str() );
        hists_other->SetTitle( (alt).c_str() );
        hists_others.push_back( hists_other );
      }

      // ===--===--===--===--===--===--===--===--===--===--===
      for(int i = 0; i < hists_others.size(); i++){
        auto hs = hists_others.at( i );
        hs->SetLineColor( indexes.at(color_i++) );
        hs->SetLineWidth( 2 );
        if(color_i > 30) color_i = 1;
      }

      int N_cells = 4;
      TCanvas * canv_1 = new TCanvas( (string("SYS1_") + h->GetName()).c_str(), (string("SYS1_") + h->GetName()).c_str(), 640 * N_cells, 640 * N_cells);
      TCanvas * canv_2 = new TCanvas( (string("SYS2_") + h->GetName()).c_str(), (string("SYS2_") + h->GetName()).c_str(), 640 * N_cells, 640 * N_cells);
      TCanvas * canv_3 = new TCanvas( (string("SYS3_") + h->GetName()).c_str(), (string("SYS3_") + h->GetName()).c_str(), 640 * N_cells, 640 * N_cells);
      TCanvas * canv_comp = new TCanvas( (string("SYS_comp_") + h->GetName()).c_str(), (string("SYS_comp_") + h->GetName()).c_str(), 640*2, 640);
      canv_1->Divide(N_cells, N_cells);
      canv_2->Divide(N_cells, N_cells);
      canv_3->Divide(N_cells, N_cells);
      canv_comp->Divide(2, 1);
      for(int i = 1; i <= N_cells*N_cells; i ++){
        vector<TH1*> hists_other_i;
        for(int j = (i-1) * hists_others.size() / (N_cells*N_cells); j < i * hists_others.size() / (N_cells*N_cells) ; j++ )
          hists_other_i.push_back( hists_others.at(j) );

        canv_1->cd( i );
        pm::draw_hists_difference( h, hists_other_i, "" );

        canv_2->cd( i );
        pm::draw_hists_difference( h, hists_other_i, "diff" );

        canv_3->cd( i );
        pm::draw_hists_difference( h, hists_other_i, "diff percent" );
      }

      list<TH1D*> herrs;
      string lname = "";
      color_i = 0;
      for(int i = 0; i < hists_others.size(); i++){
        TH1D* h        = hists_others.at(i);
        lname.size() < string(h->GetTitle()).size() ? lname = string(h->GetTitle()) : lname;
        TH1D* hist_err = (TH1D*)h->Clone();
        hist_err->Add( h, -1. );
        hist_err->Divide( h );
        hist_err->SetMarkerStyle( 30 + color_i );
        hist_err->SetFillStyle( 3000+color_i );
        color_i++;
        for(int i = 1; i < hist_err->GetNbinsX()+1; i++){
          hist_err->SetBinContent(i, abs(hist_err->GetBinContent(i)));
        }

        for(auto it = herrs.begin(); it!=herrs.end(); ++it){
          if( (*it)->Integral() < hist_err->Integral() ){
            herrs.insert(it, hist_err);
            goto skipp_add;
          }
        }
        herrs.push_back(hist_err);
        skipp_add: ;
      }


      canv_1->Print( ("./output/SYS1_" + variable.GetOutputName() + "_X_" + process->short_name + ".png").c_str() );
      canv_2->Print( ("./output/SYS2_" + variable.GetOutputName() + "_X_" + process->short_name + ".png").c_str() );
      canv_3->Print( ("./output/SYS3_" + variable.GetOutputName() + "_X_" + process->short_name + ".png").c_str() );

      THStack * stack = new THStack(TString(h->GetName()) + "_stack", TString(h->GetName()) + "_stack");
      TLegend * legend = new TLegend(0.05,0.05,0.95,0.95);
      for(auto it = herrs.begin(); it!=herrs.end(); ++it){
        stack->Add( (*it) );
        
        string title = string((*it)->GetTitle());
        for(int i = (lname.size() - title.size())*1.3; i>=0; i--) title += " ";
        title += " - " + to_string( (*it)->Integral()/(*it)->GetNbinsX() );
        legend->AddEntry(*it,  title.c_str(), "lf");
      }

      canv_comp->cd(2);
      legend->Draw();
      canv_comp->cd(1);
      stack->Draw("hist f");
      canv_comp->Print( ("./output/SYS_comp_" + variable.GetOutputName() + "_X_" + process->short_name + ".png").c_str() );
    }

    
  }

}













