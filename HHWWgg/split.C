
#include "analyse_cfg.C"

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

  void split_tree_(TTree * tree, string out_name, vector<string> tree_names, vector<double> fractions){
    int last_entries = 0;
    int total_entries = tree->GetEntries();
    TFile *newfile = new TFile(out_name.c_str(), "RECREATE");
    for(int i = 0; i < tree_names.size(); i++){
      int entries_to_copy = total_entries * fractions.at(i);
      TTree * new_tree = tree->CopyTree("", "", entries_to_copy, last_entries);
      new_tree->SetName( tree_names.at(i).c_str() );
      // new_tree->Print();
      last_entries += entries_to_copy;
    }
    newfile->Write();
    newfile->Close();
  }

  void split_tree_tmva_(string inp_name, string out_name, string tree_name, double train_fraction=0.1, int min_events_to_split=1000){
    TFile * file = TFile::Open( inp_name.c_str() );
    if(!file or file->IsZombie()){
      cerr << __FUNCTION__ << ": can't open file name \"" << inp_name << "\", skip ... " << endl;
      return;
    }

    TTree * oldtree = (TTree*) find_in_dir_(file, tree_name);
    if(oldtree == nullptr){
      cerr << __FUNCTION__ << ": can't open tree with name \"" << tree_name << "\", skip ... " << endl;
      return;
    }

    int total_entries = oldtree->GetEntries();
    // if(total_entries < min_events_to_split) train_fraction = 0.0;

    vector<string> names = {"train", "data"};
    vector<double> fracs = {train_fraction, 1.0-train_fraction};

    split_tree_(oldtree, out_name, names, fracs);

    file->Close();
  }


struct split_args{
  string inp_name;
  string out_name;
  string inp_tree;
  double train_frac;
};

void * split_wrapper(void * a){
  split_args * args = (split_args*) a; 
  cout << "Start with " << args->inp_name << " " << args->train_frac << endl;
  split_tree_tmva_(args->inp_name, args->out_name, args->inp_tree, args->train_frac, 100);
  cout << "Done with " << args->inp_name << endl;
  // TThread::Exit(0);
  return 0;
}

  void dump_file_info(string inp_name, string tree_name, string out_name){
    TFile * file = TFile::Open( inp_name.c_str() );
    if(!file or file->IsZombie()){
      cerr << __FUNCTION__ << ": can't open file name \"" << inp_name << "\", skip ... " << endl;
      return;
    }

    TTree * oldtree = (TTree*) find_in_dir_(file, tree_name);
    if(oldtree == nullptr){
      file->Close();
      return;
    }

    TFile * newfile = TFile::Open( out_name.c_str() );
    if(!newfile or newfile->IsZombie()){
      cerr << __FUNCTION__ << ": can't open file name \"" << out_name << "\", skip ... " << endl;
      file->Close();
      return;
    }

    TTree * train_tree = (TTree*) find_in_dir_(newfile, "train");
    TTree * data_tree = (TTree*) find_in_dir_(newfile, "data");

    cout << inp_name << " " << train_tree->GetEntries() << "+" << data_tree->GetEntries() << "/" << oldtree->GetEntries() << endl;

    newfile->Close();
    file->Close();
  }

bool check_dataset(string dataset, vector<string> datasets_for_train){
  for(auto val : datasets_for_train){
    size_t found = dataset.find( val ); 
    if (found != string::npos) return true;
  }
  return false;
}

void split(){
  vector<TThread*> threads;
  vector<split_args *> all_args;
  string INPUT_PATH, OUTPUT_PATH;

  int year = 2016;
  // 2016 == == ==
  if(year == 2016){
    OUTPUT_PATH = "./output/chanels_split_2016/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v2_SYS/";

    OUTPUT_PATH = "./output/chanels_split_2016_v2/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2016_v5_SYS/";
  }

  // 2017 == == ==
  if(year == 2017){
    OUTPUT_PATH = "./output/chanels_split_2017_c2/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v2_noSYS/";

    OUTPUT_PATH = "./output/chanels_split_2017_v2/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2017_v5_SYS/";
  }

  // 2018 == == ==
  if(year == 2018){
    OUTPUT_PATH = "./output/chanels_split_2018/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_c0/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v3_noSYS/";

    OUTPUT_PATH = "./output/chanels_split_2018_v2/";
    INPUT_PATH  = "/eos/user/p/pmandrik/HHWWgg_hzura/output_2018_v5_SYS/";
  }

  vector<string> datasets = list_files( INPUT_PATH.c_str(), ".root" );
  for(auto dataset : datasets){
    split_args * args = new split_args();
    args->inp_name = INPUT_PATH + dataset;
    args->out_name = OUTPUT_PATH + dataset;
    args->inp_tree = "Def_Events";

    args->train_frac = 0.9;
    vector<string> signals = {"cHHH0.root", "cHHH1.root", "cHHH2.root", "cHHH5.root", "sm.root"};
    for(int i = 0; i < 15; i++) signals.push_back( to_string(i) + ".root" );
    for(string ss : signals){
      if(ss != dataset) continue;
      args->train_frac = 0.4;
    }

    // if( dataset.find("gjets") != string::npos  ) args->train_frac = 0.9;
    TThread* new_thread = new TThread( dataset.c_str(), &split_wrapper, (void*) args );
    threads.push_back( new_thread );
    all_args.push_back( args );
  }

  threads_care( threads, 10 );

  for(split_args * args : all_args){
    dump_file_info( args->inp_name, args->inp_tree, args->out_name );
  }
}

/*
-rw-r--r--. 1 pmandrik zh 3.4G Oct 29 09:33 hzura_2017_10_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.3G Oct 29 09:33 hzura_2017_2_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.7G Oct 29 09:37 hzura_2017_12_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 4.1G Oct 29 09:41 hzura_2017_6_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 4.0G Oct 29 09:41 hzura_2017_4_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 4.0G Oct 29 09:42 hzura_2017_8_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 4.2G Oct 29 09:45 hzura_2017_sm_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 4.0G Oct 29 10:24 hzura_2017_3_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.7G Oct 29 10:24 hzura_2017_11_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.9G Oct 29 10:29 hzura_2017_7_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 2.5G Oct 29 10:29 hzura_cHHH0_v2.root
-rw-r--r--. 1 pmandrik zh 3.8G Oct 29 10:29 hzura_2017_5_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.9G Oct 29 10:32 hzura_2017_9_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 3.6G Oct 29 10:32 hzura_2017_1_fsim_v2.root
-rw-r--r--. 1 pmandrik zh 2.2G Oct 29 10:47 hzura_cHHH2_v2.root
-rw-r--r--. 1 pmandrik zh 3.2G Oct 29 11:14 hzura_cHHH5_v2.root

*/



