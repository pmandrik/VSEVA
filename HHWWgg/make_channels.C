
#include "analyse_cfg.C"

  vector<string> list_files(string dirname="C:/root/folder/", const char *ext=".root") { 
    vector<string> answer;
    TSystemDirectory dir(dirname.c_str(), dirname.c_str()); 
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

  std::string get_file_name(std::string filePath, bool withExtension = true, char seperator = '/'){
      std::size_t dotPos = filePath.rfind('.');
      std::size_t sepPos = filePath.rfind(seperator);

      if(sepPos != std::string::npos){
          return filePath.substr(sepPos + 1, dotPos - sepPos - 1 );
      }
      return "";
  }

  template<typename T>
  void get_all_with_type_(vector<T*> * objs, TDirectory * dir, string type){
    auto keys = dir->GetListOfKeys();
    for(int i = 0; i < keys->GetSize(); i++){
      auto obj =  ((TKey*) keys->At(i))->ReadObj();
      if( string(obj->ClassName()) == type) objs->push_back( (T*)obj );
    }
  }

  TObject * find_in_dir_(TDirectory *dir, string name) {
    TIter next (dir->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
      if(key->GetName() == name) {
        return key->ReadObj();
      }
      if( string( key->GetClassName() ) == "TDirectory" ) {
        dir->cd(key->GetName());
        TDirectory *subdir = gDirectory;
        TObject * answer = find_in_dir(subdir, name);
        if(answer != nullptr) return answer;
        dir->cd();
      }
    }
    return nullptr;
  }

  vector<string> vars_to_use = {"channel", "gen_Hi_yy_tlv", "gen_HHi_tlv", "m_yy", "mc_weight", "lumiWeight", "weight", "dR_yy", "y1_tlv", "y2_tlv", "dR_jj", "dR_WW", "dR_HH", "dPhi_nuL", "H_yy_tlv", "ljet1_tlv", "ljet2_tlv", "yy_mva", "H_WW_tlv", "lep_leading_tlv"};

  void make_chanel_(string inp_name, string tree_cut, string channel, string output_path){
    TFile * file = TFile::Open( inp_name.c_str() );
    if(!file or file->IsZombie()){
      cerr << __FUNCTION__ << ": can't open file name \"" << inp_name << "\", skip ... " << endl;
      return;
    }

    vector<string> tree_names = {"Def", "FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp","JEC_AbsoluteUp", "JEC_AbsoluteDown", "JEC_Absolute_2017Up", "JEC_Absolute_2017Down", "JEC_BBEC1Up", "JEC_BBEC1Down", "JEC_BBEC1_2017Up", "JEC_BBEC1_2017Down", "JEC_EC2Up", "JEC_EC2Down", "JEC_EC2_2017Up", "JEC_EC2_2017Down", "JEC_FlavorQCDUp", "JEC_FlavorQCDDown", "JEC_HFUp", "JEC_HFDown", "JEC_HF_2017Up", "JEC_HF_2017Down", "JEC_RelativeBalUp", "JEC_RelativeBalDown", "JEC_RelativeSample_2017Up", "JEC_RelativeSample_2017Down", "UnclusteredMETUp", "UnclusteredMETDown"};
    // tree_names = {"Def"};

    //vector<TTree*> trees;
    //get_all_with_type_( &trees, (TDirectory*)file, "TTree");
    //for(TTree* oldtree : trees){
    for(string name : tree_names){
      TTree* oldtree = (TTree*) file->Get( (name + "_Events").c_str() );
      cout << oldtree << " " << name << " " << inp_name  << endl;
      string out_name = output_path + "/" + get_file_name(inp_name) + "_" + string(oldtree->GetName()) + "_" + channel + ".root";
      cout << "  process " << out_name << " " << oldtree->GetEntries() << endl;

      oldtree->SetBranchStatus("*", 0);
      oldtree->SetBranchStatus("weight*", 1);
      for(string var : vars_to_use){
        oldtree->SetBranchStatus( var.c_str(), 1);
      }

      cout << out_name.c_str() << " RECREATE" << endl;
      TFile * newfile  = new TFile( out_name.c_str(), "RECREATE" );
      TTree * new_tree = oldtree->CopyTree(tree_cut.c_str(), "");

      //cout << "  process " << out_name << " -> " << new_tree->GetEntries() << endl;
      new_tree->SetName( "data" );
      //new_tree->Write();
      newfile->Write();
      newfile->Close();
    }
    cout << "Close " << file->GetName() << endl;
    file->Close();
  }

struct split_args{
  string inp_name;
  string output_path;
  vector<string> ch_cuts;
  vector<string> ch_names;
};

void * make_chanel_wrapper(void * a){
  split_args * args = (split_args*) a; 
  for(int i = 0; i < args->ch_cuts.size(); i++){
    make_chanel_(args->inp_name, args->ch_cuts.at(i), args->ch_names.at(i), args->output_path );
  }
  // TThread::Exit(0);
  return 0;
}

void make_channels(){
  //string OUTPUT_PATH = "./output/chanels_2017/";
  //string input_path  = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7/"

  //string OUTPUT_PATH = "./output/chanels_sys_2017/";
  //string input_path  = "/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output_v7_sys/" ;

  string OUTPUT_PATH = "./output/chanels_sys_2017/";
  string input_path  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_c1" ;

  // vector<string> chanels = { "ch13", "ch24", "ch7", "ch8", "ch78" } ;
  // vector<string> cuts = { "(int(channel)==1)+(int(channel)==3)", "(int(channel)==2)+(int(channel)==4)", "(int(channel)==7)", "(int(channel)==8)", "(int(channel)==7)+(int(channel)==8)" } ;
  vector<string> chanels = { "ch78" } ;
  vector<string> cuts    = { "1" } ;

  vector<string> datasets = list_files( input_path, ".root" ) ;
  vector<TThread*> threads;
  for( auto dataset : datasets ){
    // if( dataset.find("_9_") == string::npos and dataset.find("_SM_") == string::npos ) continue;
    split_args * args = new split_args();
    args->inp_name = input_path + "/" + dataset;
    args->output_path = OUTPUT_PATH ;

    args->ch_cuts = cuts;
    args->ch_names = chanels;

    cout << dataset << endl;
    //continue;
    //TFile * file = TFile::Open( args->inp_name.c_str() );
    //file->ls();
    //continue;
    //vector<TTree*> trees;
    //get_all_with_type_( &trees, (TDirectory*)file, "TTree");
    //for(TTree* oldtree : trees){ cout << oldtree->GetName() << " " << oldtree->GetEntries() << endl; }
    //continue;

    TThread* new_thread = new TThread( dataset.c_str(), &make_chanel_wrapper, (void*) args );
    threads.push_back( new_thread );

    //if( threads.size() > 5 ) break;
  }

  threads_care( threads, 8 );
}







