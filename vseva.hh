
#ifndef vseva_hh
#define vseva_hh 1

namespace vseva {

  class DataSet {
    public:
    DataSet(){}

    DataSet(string process_name, string latex_name, string short_name, string type){
      this->process_name = process_name;
      this->latex_name   = latex_name;
      this->short_name   = short_name;
      this->type         = type;
      nevents = 0;
      weight_sum = 0;
      sys = false;
    }

    string process_name, latex_name, short_name, type, dataset_ttree_name;
    vector<string> files;
    long long int nevents;
    double weight_sum, xsec;
    bool sys;

    void AddFile(string path){
      files.push_back( path );
    }

    bool IsData(){ return (type == "D" or type == "Data"); }
    bool IsSignal(){ return (type == "S" or type == "Signal"); }
    bool IsBackground(){ return (type == "B" or type == "Background"); }

    vector<TH1D*> hists;
  };

  class PlotVariable{
    public:
    PlotVariable(){}
    PlotVariable(string key, double min, double max){
      this->key = key;
      this->min = min;
      this->max = max;
      this->label = "";
      this->draw_type = "";
    }

    PlotVariable(string key, string lab, double min, double max, string process_name = ""){
      this->key = key;
      this->min = min;
      this->max = max;
      this->label = lab;
      this->draw_type = "";
      this->process_name   = process_name;
    }

    bool CheckProcess(std::string name){
      cout << processes_include.size() << " " << processes_exclude.size() << endl;
      if( processes_include.size() ){
        auto it = find( processes_include.begin(), processes_include.end(), name );
        if( it != processes_include.end() ) return true;
        return false;
      }
      if( processes_exclude.size() ){
        auto it = find( processes_exclude.begin(), processes_exclude.end(), name );
        if( it != processes_exclude.end() ) return false;
      }
      return true;
    }

    std::string GetOutputName(){
      if(output_name.size() ) return output_name;
      return key;
    }

    string key, label, draw_type, output_name, process_name;
    double min, max;
    vector<string> processes_include, processes_exclude;
  };

  class CustomPlotVariables{
    public:
    std::vector<PlotVariable> variables;
    std::string weight;
    std::string draw_option, label, output_name;
  };



  // STYLES & COLORS ======================================================================================================================================================================
  inline Color_t FindFreeCustomColorIndex(Color_t start = 1000){
    for (Color_t i = std::max(start, Color_t(1000)), e = 10000; i < e; ++i)
      if (!gROOT->GetColor(i)) return i;
    return -1;
  }

  class FakeTColor : public TColor{
    public : 
      FakeTColor(double r, double g, double b) : TColor(FindFreeCustomColorIndex(), r/255., g/255., b/255.){}
      int GetIndex(){ return this->fNumber; }
  };

  vector <int> global_nice_colors;
  std::vector <int> getNiceColors(int values = 25){
    if( not global_nice_colors.size() ){
      std::vector <FakeTColor*> colors = { new FakeTColor( 75., 122., 192. ),
                                           new FakeTColor( 241., 72., 75. ),
                                           new FakeTColor( 31., 140., 61.  ),
                                           new FakeTColor( 241., 121., 41. ),
                                           new FakeTColor( 170., 143., 104. ),
                                           new FakeTColor( 180., 212., 79. ),
                                           new FakeTColor( 169., 169., 169. ),
                                           new FakeTColor( 233., 90.,  154.  ),
                                           new FakeTColor( 34.,  148., 232. ),
                                           new FakeTColor( 253., 205.,  74. ),
                                           new FakeTColor( 81., 179., 157. ),
                                           new FakeTColor( 107., 76., 154. ),
                                           new FakeTColor( 255., 15., 15. ),
                                           new FakeTColor( 15., 255., 15. ),
                                           new FakeTColor( 15., 15., 255. ),
                                           new FakeTColor( 255.,  15., 255. ),
                                           new FakeTColor( 255., 255., 15.  ),
                                           new FakeTColor( 15.,  255., 255. ),
                                           new FakeTColor( 242., 203., 110. ),
                                           new FakeTColor( 220., 119., 31.  ),
                                           new FakeTColor( 148., 58.,  48.  ),
                                           new FakeTColor( 174., 124., 145. ),
                                           new FakeTColor( 105., 175., 132. ),
                                           new FakeTColor( 137., 148., 242. ),
                                           new FakeTColor( 56.,  114., 221. ),
                                           new FakeTColor( 31.,  147., 138. ),
                                           new FakeTColor( 124., 32.,  148. ),
                                           new FakeTColor( 125., 105., 174. ),
                                           new FakeTColor( 222., 56.,  135. ),
                                           new FakeTColor( 174., 174., 174. ),
                                           new FakeTColor( 125., 147.,  77. ),
                                           new FakeTColor( 211., 242., 220. ),
                                           new FakeTColor( 123., 220., 127. ) };
      for(auto color : colors)
        global_nice_colors.push_back( color->GetIndex() );
    }

    std::vector <int> colors_ids = global_nice_colors;
    values -= colors_ids.size();
    for(int i = 0; i < values; i++){
      colors_ids.push_back( i+1 );
    }
    return colors_ids;
  }

  void PrintNiceColors(){
    std::vector <int> colors = getNiceColors();
    for(auto color : colors) std::cout << color << std::endl;
  }

  void set_style_FCC(){
    int font = 132;
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);

    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameFillStyle(0);

    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetTitleColor(1);
    gStyle->SetStatColor(0);

    gStyle->SetLegendBorderSize(0);
    gStyle->SetLegendFillColor(0);
    gStyle->SetLegendFont(font);
    
    gStyle->SetOptStat(0000000);
    gStyle->SetTextFont(font);
    gStyle->SetTextSize(0.05);
    gStyle->SetLabelFont(font,"XYZ");
    gStyle->SetTitleFont(font,"XYZ");
    gStyle->SetLabelSize(0.05,"XYZ"); //0.035
    gStyle->SetTitleSize(0.05,"XYZ");
    
    gStyle->SetTitleOffset(1.25,"X");
    gStyle->SetTitleOffset(2.05,"Y");
    gStyle->SetLabelOffset(0.02,"XY");
    
    // use bold lines and markers
    gStyle->SetMarkerStyle(8);
    gStyle->SetHistLineWidth(3);
    gStyle->SetLineWidth(1);

    gStyle->SetNdivisions(510,"xy");

    // do not display any of the standard histogram decorations
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0); //("m")
    gStyle->SetOptFit(0);
    
    //gStyle->SetPalette(1,0)
    gStyle->cd();
    gROOT->ForceStyle();
  }

  // HIST DRAWING ======================================================================================================================================================================
  template<class TMP_hist_type = TH1D> class HistDrawer {
    public:
      HistDrawer(){
        font = 132;
        logY = false;
        label_x = "X";
        label_y = "Events";
        xmin = 0; xmax = 0; 
        ymin = 0; ymax = 0;
        signal_scale = 1;
      }

      vector<TMP_hist_type*> signals, backgrounds, datas;
      int font;
      bool logY;
      string label_x, label_y;
      double xmin, xmax, ymin, ymax;
      double signal_scale;

      void Print(){
        cout << "mRoot::HistDrawer.Print() " << endl;
        cout << "signals = " << signals.size() << endl;
        for(auto hist : signals) hist->Print();
        cout << " backgroudns = " << backgrounds.size() << endl;
        for(auto hist : backgrounds) hist->Print();
        cout << " datas = " << datas.size() << endl;
        for(auto hist : datas) hist->Print();
      }

      bool IsEmpty(){
        return ((signals.size() + backgrounds.size() + datas.size()) == 0);
      }

      void SetStyleHist(TH1 * hist){
        hist->GetYaxis()->SetTitle( label_y.c_str() );
        hist->GetXaxis()->SetTitle( label_x.c_str() );

        hist->GetYaxis()->CenterTitle();
        hist->GetYaxis()->SetNdivisions(510);

        hist->GetYaxis()->SetLabelFont(132);
        hist->GetYaxis()->SetLabelOffset(0.02);
        hist->GetYaxis()->SetLabelSize(0.04);
        hist->GetYaxis()->SetTitleFont(132);
        hist->GetYaxis()->SetTitleOffset(1.5);
        hist->GetYaxis()->SetTitleSize(0.045);

        hist->GetXaxis()->SetLabelFont(132);
        hist->GetXaxis()->SetLabelOffset(0.02);
        hist->GetXaxis()->SetLabelSize(0.04);
        hist->GetXaxis()->SetTitleFont(132);
        hist->GetXaxis()->SetTitleOffset(1.5);
        hist->GetXaxis()->SetTitleSize(0.045);
        hist->SetStats(false);
      }

      void SetStyle(){
        std::vector <int> colors = getNiceColors();
        int color = 0;
        int signal_color = 2;

        for(auto hist : signals){
          hist->SetLineColor( signal_color++ );
          hist->SetLineWidth( 5 );
          hist->SetLineStyle( 7 );
          SetStyleHist(hist);

          if(xmin != xmax) hist->GetXaxis()->SetRangeUser(xmin, xmax);
          else             hist->GetXaxis()->UnZoom();
        }

        for(auto hist : backgrounds){
          hist->SetLineColor( colors.at(color++) );
          hist->SetLineWidth( 3 );
          SetStyleHist(hist);

          if(xmin != xmax) hist->GetXaxis()->SetRangeUser(xmin, xmax);
          else             hist->GetXaxis()->UnZoom();
        }

        int datastyle_index = 20;
        for(auto hist : datas){
          SetStyleHist(hist);
          hist->SetMarkerStyle( datastyle_index++ );

          if(xmin != xmax) hist->GetXaxis()->SetRangeUser(xmin, xmax);
          else             hist->GetXaxis()->UnZoom();
        }
      }

      void SetMinMax(double minh_v, double maxh_v){
        for(auto hist : signals     ){ 
          hist->SetMaximum( maxh_v );
          hist->SetMinimum( minh_v );
        }
        for(auto hist : backgrounds ) {
          hist->SetMaximum( maxh_v );
          hist->SetMinimum( minh_v );
        }
        for(auto hist : datas ) {
          hist->SetMaximum( maxh_v );
          hist->SetMinimum( minh_v );
        }
      }

      void SetMaximum(){
        double maxh_v = -1.0;
        double minh_v = -1.0;
        for(auto hist : signals     ) maxh_v = TMath::Max(maxh_v, hist->GetBinContent(hist->GetMaximumBin()));
        for(auto hist : backgrounds ) maxh_v = TMath::Max(maxh_v, hist->GetBinContent(hist->GetMaximumBin()));
        for(auto hist : datas       ) maxh_v = TMath::Max(maxh_v, hist->GetBinContent(hist->GetMaximumBin()));
        if( logY ) {
          // minh_v = 0.000001*maxh_v;
          // maxh_v = 100000*maxh_v;
          minh_v = 0.0000001*maxh_v;
          maxh_v = 10000*maxh_v;
        }
        else {
          minh_v = 0.;
          maxh_v = 1.5*maxh_v;
        }
        SetMinMax(minh_v, maxh_v);
      }

      void SetMaximumStack(THStack * hs){
        double maxh_v =  0.0;
        double minh_v = -1.0;
        for(auto hist : backgrounds ) maxh_v += hist->GetBinContent(hist->GetMaximumBin());
        for(auto hist : signals     ) maxh_v = TMath::Max(maxh_v, hist->GetBinContent(hist->GetMaximumBin()));
        for(auto hist : datas       ) maxh_v = TMath::Max(maxh_v, hist->GetBinContent(hist->GetMaximumBin()));
        if( logY ) {
          minh_v = 0.000001*maxh_v;
          maxh_v = 100000*maxh_v;
        }
        else {
          minh_v = 0.;
          maxh_v = 1.5*maxh_v;
        }
        SetMinMax(minh_v, maxh_v);
        if( not hs->GetXaxis() or not hs->GetYaxis() or not hs->GetHistogram() ) return;
        hs->SetMinimum( minh_v );
        hs->SetMaximum( maxh_v );
      }

      void DrawHists(){
        SetMaximum();
             if(backgrounds.size())  backgrounds.at(0)->Draw("hist");
        else if( signals.size()   )      signals.at(0)->Draw("hist");
        else if( datas.size()     )        datas.at(0)->Draw("hist");
        for(auto hist : backgrounds) hist->Draw("same hist");
        for(auto hist : signals)     hist->Draw("same hist");
        for(auto hist : datas)       hist->Draw("same E1");
      }

      void DrawHistsStack(){
        THStack * hs = new THStack("stack", "stack");
        for(auto hist : backgrounds){
          hist->SetFillColor( hist->GetLineColor() );
          hs->Add(hist);
        }
        SetMaximumStack( hs );
        hs->Draw("hist");
        for(auto hist : signals) hist->Draw("same hist");

        if( not hs->GetXaxis() or not hs->GetYaxis() or not hs->GetHistogram() ) return;
        SetStyleHist( hs->GetHistogram() );
        if( signals.size() ){
          hs->GetXaxis()->SetTitle( signals.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( signals.at(0)->GetYaxis()->GetTitle() );
        }
        else if( backgrounds.size() ){
          hs->GetXaxis()->SetTitle( backgrounds.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( backgrounds.at(0)->GetYaxis()->GetTitle() );
        }
        else if( datas.size() ){
          hs->GetXaxis()->SetTitle( datas.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( datas.at(0)->GetYaxis()->GetTitle() );
        }
      }

      void DrawHistsTMVA(){
        THStack * hs = new THStack();
        double sum_integral = 0;
        for(auto hist : backgrounds){
          sum_integral += hist->Integral();
          hist->SetFillColor( hist->GetLineColor() );
          hist->Print();
          hs->Add(hist);
        }
        double alt_sum_integral = 0;
        for(auto hist : datas){
          alt_sum_integral += hist->Integral();
        }
        sum_integral = TMath::Max(sum_integral, alt_sum_integral);
        if( backgrounds.size() + datas.size() < 1 and signals.size() > 0){
          sum_integral = signals.at(0)->Integral();
        }
        //for(auto hist : backgrounds)
        //  hist->Scale(1./sum_integral);
        for(auto hist : signals)
          hist->Scale( 0.50*sum_integral / hist->Integral() );

        SetMaximumStack( hs );
        if( not hs->GetXaxis() or not hs->GetYaxis() or not hs->GetHistogram() ){
          if( signals.size()   )      signals.at(0)->Draw("hist");
          else if( datas.size()     )   datas.at(0)->Draw("hist");
          else return; // FIXME
        } else {
          hs->Draw("hist");
        }

        for(auto hist : signals)
          hist->Draw("same hist");
        for(auto hist : datas)
          hist->Draw("same E1");

        if( not hs->GetXaxis() or not hs->GetYaxis() or not hs->GetHistogram() ) return;
        SetStyleHist( hs->GetHistogram() );
        if( signals.size() ){
          hs->GetXaxis()->SetTitle( signals.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( signals.at(0)->GetYaxis()->GetTitle() );
        }
        else if( backgrounds.size() ){
          hs->GetXaxis()->SetTitle( backgrounds.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( backgrounds.at(0)->GetYaxis()->GetTitle() );
        }
        else if( datas.size() ){
          hs->GetXaxis()->SetTitle( datas.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( datas.at(0)->GetYaxis()->GetTitle() );
        }
      }

      void DrawHistsOverset(){
        THStack * hs = new THStack();
        double sum_integral = 0;
        for(auto hist : backgrounds){
          sum_integral += hist->Integral();
          hist->SetFillColor( hist->GetLineColor() );
          hist->Print();
          hs->Add(hist);
        }
        //for(auto hist : backgrounds)
        //  hist->Scale(1./sum_integral);
        vector<TH1D *> hs_signals;

        for(auto hist : signals){
          hist->Scale( signal_scale );

          TH1D * hs_signal = (TH1D *) hist->Clone();
          for(auto hist : backgrounds) hs_signal->Add(hist);
          hs_signals.push_back( hs_signal );
        }

        SetMaximumStack( hs );
        hs->Draw("hist");

        for(auto hist : hs_signals){
          hist->Draw("same hist");
        }
        for(auto hist : datas)
          hist->Draw("same E1");

        if( not hs->GetXaxis() or not hs->GetYaxis() or not hs->GetHistogram() ) return;
        SetStyleHist( hs->GetHistogram() );
        if( signals.size() ){
          hs->GetXaxis()->SetTitle( signals.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( signals.at(0)->GetYaxis()->GetTitle() );
        }
        else if( backgrounds.size() ){
          hs->GetXaxis()->SetTitle( backgrounds.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( backgrounds.at(0)->GetYaxis()->GetTitle() );
        }
        else if( datas.size() ){
          hs->GetXaxis()->SetTitle( datas.at(0)->GetXaxis()->GetTitle() );
          hs->GetYaxis()->SetTitle( datas.at(0)->GetYaxis()->GetTitle() );
        }
      }

      void DrawHists2D(){
        for(auto hist : backgrounds){
          hist->SetMarkerColor( 1 );
          hist->SetLineColor( 1 );
        }
        for(auto hist : signals)
          hist->SetMarkerColor( hist->GetLineColor() );

             if(backgrounds.size()) backgrounds.at(0)->Draw("SCAT");
        else if( signals.size())    signals.at(0)->Draw("SCAT");

        for(auto hist : backgrounds) hist->Draw("same SCAT");
        for(auto hist : signals) hist->Draw("same SCAT");
        // TODO data ?
      }

      TLegend * GetLegend(float x1=0.55, float y1=0.65, float x2=0.90, float y2=0.88){
        TLegend * legend = new TLegend(x1,y1,x2,y2);
        legend->SetFillColor(0);
        legend->SetFillStyle(3001);
        legend->SetLineColor(0);
        legend->SetTextFont(font) ;
        for(auto hist : datas)
          legend->AddEntry(hist, hist->GetTitle(), "p");
        for(auto hist : signals)
          legend->AddEntry(hist, hist->GetTitle(), "l");
        for(auto hist : backgrounds)
          legend->AddEntry(hist, hist->GetTitle(), "f");
        return legend;
      }

      TLegend * GetLegend2D(float x1=0.55, float y1=0.75, float x2=0.90, float y2=0.88){
        TLegend * legend = new TLegend(x1,y1,x2,y2);
        legend->SetLineColor(1);
        legend->SetLineWidth(3);
        legend->SetTextFont(font) ;
        gStyle->SetLegendBorderSize(3);
        for(auto hist : signals)
          legend->AddEntry(hist, hist->GetTitle(), "lp");
        if(backgrounds.size())
          legend->AddEntry(backgrounds.at(0), "background", "lp");
        return legend;
      }

      TLegend * GetLegendCutStyle(string cut_text, float x1=0.55, float y1=0.65, float x2=0.90, float y2=0.88){
        TLegend * legend = new TLegend(x1,y1,x2,y2);
        legend->SetFillColor(0);
        legend->SetFillStyle(3001);
        legend->SetLineColor(0);
        legend->SetTextFont(font) ;
        legend->AddEntry(signals.at(0), signals.at(0)->GetTitle(), "l");
        legend->AddEntry(backgrounds.at(0), backgrounds.at(0)->GetTitle(), "l");
        legend->AddEntry((TObject*)0, cut_text.c_str(), "");
        legend->AddEntry(signals.at(1), signals.at(1)->GetTitle(), "l");
        legend->AddEntry(backgrounds.at(1), backgrounds.at(1)->GetTitle(), "l");
        return legend;
      }

      TLatex * GetText(string text_src, float x = 0.23, float y = 0.82, float text_size = 0.044){
        cout << "THIS " << endl;
        TLatex * text = new TLatex(x, y, text_src.c_str());
        text->SetNDC(kTRUE) ;
        text->SetTextSize(text_size) ;
        text->SetTextFont(font) ;
        return text;
      }

      TLatex * GetLeftText(string text_src){  return GetText(text_src, 0.16, 0.82, 0.034); }
      TLatex * GetRightText(string text_src){ return GetText(text_src, 0.45, 0.92, 0.040); }

      TCanvas * GetCanvas(string name, int size_x = 600, int size_y = 600){
        TCanvas * canvas = new TCanvas(name.c_str(), name.c_str(), size_x, size_y);
        canvas->SetTicks(1,1);
        canvas->SetLeftMargin(0.14); 
        canvas->SetRightMargin(0.08); 
        canvas->SetBottomMargin(0.20); 
        gStyle->SetOptStat(0000000);
        gStyle->SetTextFont(font);
        gStyle->SetOptTitle(0);
        if(logY) canvas->SetLogy();
        return canvas;
      }

      TCanvas * GetCanvas2D(string name, int size_x = 800, int size_y = 600){
        TCanvas * canvas = new TCanvas(name.c_str(), name.c_str(), size_x, size_y);
        canvas->SetRightMargin(0.18);
        canvas->SetLeftMargin(0.22);
        canvas->SetBottomMargin(0.18);
        canvas->SetTopMargin(0.12);
        return canvas;
      }


      void Add(TMP_hist_type* hist, string type){
        if(type == "S")   signals.push_back( hist );
        else if(type == "B") backgrounds.push_back( hist );
        else if(type == "D") datas.push_back( hist );
      }

      void AddCummulative(TMP_hist_type* hist, string type, int index=0){
        if(type == "S"){ 
          if(index >= signals.size()) signals.push_back( hist ); 
          else                        signals.at(index)->Add( hist );
        }
        else if(type == "B"){ 
          if(index >= backgrounds.size()) backgrounds.push_back( hist ); 
          else                            backgrounds.at(index)->Add( hist );
        }
        else if(type == "D"){ 
          if(index >= datas.size()) datas.push_back( hist ); 
          else                      datas.at(index)->Add( hist );
        }
      }
  };

  template<class T> TCanvas * draw_hists_CMS( HistDrawer<T> * drawer, string path, string name, string label, string extra_title = "", string mode = "default"){
    set_style_FCC();
    string leftText  = "";
    string rightText = "";
           rightText = "CMS Preliminary";
  
    cout << name << endl;
    drawer->Print();

    TCanvas * canvas;
    if(mode == "default" or mode == "default nolog"){
      drawer->logY = true;
      if(mode == "default nolog") drawer->logY = false;
      drawer->label_x = label;
      drawer->SetStyle();
      canvas = drawer->GetCanvas( name );
      drawer->DrawHists();
      auto legend = drawer->GetLegend();
      auto ltext  = drawer->GetLeftText( leftText );
      auto rtext  = drawer->GetRightText( rightText );
      auto etext  = drawer->GetText(extra_title, 0.23, 0.92);
      legend->Draw();
      ltext->Draw() ;
      rtext->Draw() ;
      etext->Draw() ;
    } else if(mode == "tmva"){
      drawer->logY = false;
      drawer->label_x = label;
      cout << " .... set style" << endl;
      drawer->SetStyle();
      cout << " .... get canvas" << endl;
      canvas = drawer->GetCanvas( name );
      cout << " .... DRAW" << endl;
      drawer->DrawHistsTMVA();
      cout << " .... DRAW ok" << endl;
      auto legend = drawer->GetLegend();
      auto ltext  = drawer->GetLeftText( leftText );
      auto rtext  = drawer->GetRightText( rightText );
      auto etext  = drawer->GetText(extra_title, 0.23, 0.92);
      legend->Draw();
      ltext->Draw() ;
      rtext->Draw() ;
      etext->Draw() ;
    } else if(mode == "overset"){
      drawer->logY = false;
      drawer->label_x = label;
      drawer->SetStyle();
      canvas = drawer->GetCanvas( name );
      drawer->DrawHistsOverset();
      auto legend = drawer->GetLegend();
      auto ltext  = drawer->GetLeftText( leftText );
      auto rtext  = drawer->GetRightText( rightText );
      auto etext  = drawer->GetText(extra_title, 0.23, 0.92);
      legend->Draw();
      ltext->Draw() ;
      rtext->Draw() ;
      etext->Draw() ;
    } else if (mode == "correlation"){
      drawer->logY = false;
      drawer->SetStyle();
      canvas = drawer->GetCanvas2D( name );
      drawer->DrawHists2D();
      auto legend = drawer->GetLegend2D();
      auto ltext  = drawer->GetLeftText( extra_title );
      auto rtext  = drawer->GetRightText( rightText );
      auto etext  = drawer->GetText("", 0.23, 0.92);
      legend->Draw();
      ltext->Draw() ;
      rtext->Draw() ;
      etext->Draw() ;
    } else if (mode == "cut"){
      drawer->logY = true;
      drawer->label_x = label;
      drawer->SetStyle();
      canvas = drawer->GetCanvas( name );
      drawer->DrawHists();
      auto legend = drawer->GetLegendCutStyle( extra_title );
      auto ltext  = drawer->GetLeftText( leftText );
      auto rtext  = drawer->GetRightText( rightText );
      // auto etext  = drawer->GetText(extra_title, 0.23, 0.92);
      legend->Draw();
      ltext->Draw() ;
      rtext->Draw() ;
      //etext->Draw() ;
    } else {
      cout << "draw_hists_FCC(): wrong draw mode = " << mode << endl;;
    }
    canvas->SetTicks(1,1);

    canvas->RedrawAxis();
    canvas->GetFrame()->SetBorderSize( 12 );
    canvas->Modified();
    canvas->Update();
    canvas->Print( (path + "/" + name).c_str() );
    return canvas;
  }

};

#endif



