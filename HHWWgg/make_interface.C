void make_interface( string input_file = string("grinder_out.root") ){
  TFile * file = TFile::Open( input_file.c_str() );
  //gDirectory->cd("GrinderflashggHHWWggTag");

  TTree * t = (TTree*) gDirectory->Get("Def_Events");
  t->MakeClass();
}

