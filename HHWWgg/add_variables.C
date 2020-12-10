

#include "tmva_train.C"

vector<string> list_files(const char *dirname="C:/root/folder/", const char *ext=".root") { 
  vector<string> answer;
  TSystemDirectory dir(dirname, dirname); 
  TList *files = dir.GetListOfFiles(); 
  if (files) { 
    TSystemFile *file; 
    TString fname; 
    TIter next(files); 
    while( (file=(TSystemFile*)next()) ) { 
      fname = file->GetName(); 
      if( !file->IsDirectory() && fname.EndsWith(ext) ) { 
        answer.push_back( fname.Data() ); 
      } 
    } 
  } 
  return answer;
}

void tmva_add(string input_file, vector<string> tmva_inputs, vector<string> tmva_names, string tree_name = "data", string postfix_in_tree="_000"){
  // setup reader
  TMVA::Reader* tmva_reader = new TMVA::Reader( "<options>" );
  auto variables = get_variables_train();
  vector<float*> values_f;
  for(auto var : variables){
    string vname = var.expression;
    values_f.push_back( new float );
    tmva_reader->AddVariable( vname.c_str(), (values_f.at( values_f.size() - 1 )) );
  }

  vector<TMVA::IMethod *> tmva_methods;
  for(int i = 0; i < tmva_inputs.size(); i++){
    TMVA::IMethod * tmva_method = tmva_reader->BookMVA( tmva_names.at(i).c_str(), tmva_inputs.at(i).c_str() );
    cout << tmva_method << endl;
    cout << tmva_method->GetMvaValue() << endl;
    tmva_methods.push_back( tmva_method );
  }

  cout << tmva_reader->GetMVAError() << endl;

  // setup file to update 
  TFile *f = new TFile(input_file.c_str(),"update");

  cout << "Input file to update " << f << endl;

  // vector<TTree*> trees = {(TTree*)f->Get("data"), (TTree*)f->Get("train")};
  TTree* tree = (TTree*)f->Get( tree_name.c_str() );

    cout << "Tree to update " << tree << " " << input_file << endl;
    if(not tree){
      cout << " ... Skip " << tree_name << " " << input_file << endl;
      f ->ls();
      f->Close();
      return;
    }
    vector<double*> tmva_values;
    vector<TBranch*> branches;
    for(auto tmva_name : tmva_names){
      tmva_values.push_back( new double() );

      string bname = "weight_" + tmva_name + postfix_in_tree;
      TBranch* br = (TBranch*)(tree->GetListOfBranches()->FindObject( bname.c_str() ));
      if( br ) continue;
      branches.push_back( tree->Branch(bname.c_str(), tmva_values[ tmva_values.size()-1 ] ) ); 
    }

    if( not branches.size() ){
      cout << " ... Skip (all in)" << tree_name << " " << input_file << endl;
      f->Close();
      return;
    }

    vector<TTreeFormula*> values;
    for(int i = 0; i < variables.size(); i++)
      values.push_back( new TTreeFormula(variables.at(i).expression.c_str(), variables.at(i).expression.c_str(), tree) );

    for(int i = 0; i < tree->GetEntries(); i++){
      tree->GetEntry(i); 
      for(int j = 0; j < values_f.size(); j++) *(values_f[j]) = values.at(j)->EvalInstance();

      for(int j = 0; j < tmva_names.size(); j++){
        *(tmva_values[j]) = tmva_methods[j]->GetMvaValue();
        // cout << tmva_names[i] << " " << *(tmva_values[i]) << endl;
      }

      for(int j = 0; j < branches.size(); j++){
        branches[j]->Fill();
      }
    }
    tree->Write();

  f->Close();
}

struct tmva_add_args{
  string input_file;
   vector<string>tmva_inputs;
  string submode;
  vector<string> tmva_names;
  string postfix_in_tree;
  string tree_name;
};

void * tmva_add_wrapper(void * a){
  tmva_add_args * args = (tmva_add_args*) a; 
  cout << "Start with " << args->input_file << endl;
  tmva_add(args->input_file, args->tmva_inputs, args->tmva_names, args->tree_name, args->postfix_in_tree);
  cout << "Done with " << args->input_file << endl;
  // TThread::Exit(0);
  return 0;
}

void add_variables(string postfix_in_tree="_0"){ // "TMVA_2017_trainFULLSIMv1_SM_BDT_b2_020"

  string YEAR = "2016"; // "_021"
  vector<string> node_names = { "sm", "cHHH0", "cHHH1", "cHHH2", "cHHH5" };
  for(int i = 1; i <= 12; i++) node_names.push_back( to_string(i) );
  vector<string> datasets, tree_names;
  vector<string> tmva_names, tmva_input_files;
  
  if(YEAR == "2018"){
    for(auto node : node_names){
      tmva_names.push_back( "TMVA_" + YEAR + "_t5_" + node + "_BDT_b2" );
      tmva_input_files.push_back( "./weights/" + tmva_names.at( tmva_names.size()-1) + ".weights.xml" );
    }

    vector<string> sys_datasets = list_files( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v5_SYS/", ".root" );
    for(auto dataset : sys_datasets ){
      datasets.push_back( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v5_SYS/" + dataset );
      tree_names.push_back("Def_Events");
    }
  }
  if(YEAR == "2017"){
    for(auto node : node_names){
      tmva_names.push_back( "TMVA_" + YEAR + "_t5_" + node + "_BDT_b2" );
      tmva_input_files.push_back( "./weights/" + tmva_names.at( tmva_names.size()-1) + ".weights.xml" );
    }

    vector<string> sys_datasets = list_files( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v5_SYS/", ".root" );
    for(auto dataset : sys_datasets ){
      datasets.push_back( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v5_SYS/" + dataset );
      tree_names.push_back("Def_Events");
    }
  }
  if(YEAR == "2016"){
    for(auto node : node_names){
      tmva_names.push_back( "TMVA_" + YEAR + "_t5_" + node + "_BDT_b2" );
      tmva_input_files.push_back( "./weights/" + tmva_names.at( tmva_names.size()-1) + ".weights.xml" );
    }

    vector<string> sys_datasets = list_files( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/", ".root" );
    for(auto dataset : sys_datasets ){
      datasets.push_back( "/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/" + dataset );
      tree_names.push_back("Def_Events");
    }
  }

    vector<TThread*> threads;
    for(int i = 0; i < datasets.size(); i++){
      string dataset = datasets.at(i);
      string tname   = tree_names.at(i);
      // string tmva_path      = "./weights";
      // string tmva_file_name = tmva_name + ".weights.xml";

      cout << dataset << " " << tname  << endl;

      tmva_add_args * args   = new tmva_add_args();
      args->input_file       = dataset;
      args->tmva_inputs      = tmva_input_files;
      args->tmva_names       = tmva_names;
      args->postfix_in_tree  = postfix_in_tree;
      args->tree_name        = tname;
      // args->data             = channel->IsData();
      TThread* new_thread = new TThread( dataset.c_str(), &tmva_add_wrapper, (void*) args);
      threads.push_back( new_thread );
  }
  threads_care( threads, 10 );
}







