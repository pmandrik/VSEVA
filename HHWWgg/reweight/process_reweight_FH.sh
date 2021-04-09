
input="/eos/user/l/lipe/ntuple/2017/Signal/FH_LO_2017_Hadded"
output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2017/Signal/FH_LO_2017_Hadded/"

year=$1
sub=$2

if [ "$year" = "2017" ]; then
  input="/eos/user/l/lipe/ntuple/2017/Signal/FH_LO_2017_Hadded"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2017/Signal/FH_LO_2017_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    inp=$input/"node"$fix"_GluGluToHHTo2G4Q.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2017.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2017ZZ" ]; then
  input="/eos/user/l/lipe/ntuple/2017/Signal/FHZZ_LO_2017_Hadded"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2017/Signal/FHZZ_LO_2017_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    inp=$input/"node"$fix"_GluGluToHHTo2G2ZTo2G4Q.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2017.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2016ZZ" ]; then
  input="/eos/user/r/rasharma/post_doc_ihep/double-higgs/ntuples/January_2021_Production/2016/Signal/FHZZ_LO_2016_noPdfWeight_Hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/FHZZ_LO_2016_noPdfWeight_Hadded/"

  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do 
    echo $fix
    inp=$input/"GluGluToHHTo2G2ZTo2G4Q_node_"$fix"_2016.root"
    oup=$output/"GluGluToHHTo2G2ZTo2G4Q_node_"$fix"_2016.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2018" ]; then
  input="/eos/user/r/rasharma/post_doc_ihep/double-higgs/ntuples/January_2021_Production/2018/Signal/FHWW_LO_2018_Hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2018/Signal/FHWW_LO_2018_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do 
    echo $fix
    inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2018ZZ" ]; then
  input="/eos/user/r/rasharma/post_doc_ihep/double-higgs/ntuples/January_2021_Production/2018/Signal/FHZZ_LO_2018_Hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2018/Signal/FHZZ_LO_2018_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do 
    echo $fix
    inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2016" ]; then
  input="/eos/user/r/rasharma/post_doc_ihep/double-higgs/ntuples/January_2021_Production/2016/Signal/FHWW_LO_2016_noPdfWeight_Hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/FHWW_LO_2016_noPdfWeight_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2016ZZ" ]; then
  input="/eos/user/r/rasharma/post_doc_ihep/double-higgs/ntuples/January_2021_Production/2016/Signal/FHZZ_LO_2016_noPdfWeight_Hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/FHZZ_LO_2016_noPdfWeight_Hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
    oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi
