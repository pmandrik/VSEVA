
year=$1

if [ "$year" = "2018" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FL_LO_2018_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2018/Signal/FL_LO_2018_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    mkdir -p $output
    inp=$input/"GluGluToHHTo2G2l2nu_node_"$fix"_2018.root"
    oup=$output/"GluGluToHHTo2G2l2nu_node_"$fix"_2018.root"
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2017" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FL_LO_2017_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2017/Signal/FL_LO_2017_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    mkdir -p $output
    inp=$input/"GluGluToHHTo2G2l2nu_node_"$fix"_2017.root"
    oup=$output/"GluGluToHHTo2G2l2nu_node_"$fix"_2017.root"
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2016" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FL_LO_2016_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/FL_LO_2016_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    mkdir -p $output
    inp=$input/"GluGluToHHTo2G2l2nu_node_"$fix"_2016.root"
    oup=$output/"GluGluToHHTo2G2l2nu_node_"$fix"_2016.root"
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi
