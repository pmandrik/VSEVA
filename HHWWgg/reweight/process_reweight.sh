
year=$1

if [ "$year" = "2018" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/SL_LO_2018_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2018/Signal/SL_LO_2018_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    mkdir -p $output
    inp=$input/"GluGluToHHTo2G2Qlnu_node_"$fix"_2018.root"
    oup=$output/"GluGluToHHTo2G2Qlnu_node_"$fix"_2018.root"
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi

if [ "$year" = "2016" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/SL_LO_2016_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/SL_LO_2016_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    echo $fix
    mkdir -p $output
    inp=$input/"GluGluToHHTo2G2Qlnu_node_"$fix"_2016.root"
    oup=$output/"GluGluToHHTo2G2Qlnu_node_"$fix"_2016.root"
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
fi

if [ "$year" = "NLO" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/SL_NLO_2016_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2016/Signal/SL_NLO_2016_hadded/"
  #for fix in cHHH0 cHHH1 cHHH2p45 cHHH5; do
  #  inp=$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2016.root"
  #  oup=$output"GluGluToHHTo2G2Qlnu_node_"$fix"_2016.root"
  #  echo "process "$inp" ... "$oup
  #  mkdir -p $oup
  #  time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  #done

  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/SL_NLO_2018_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2018/Signal/SL_NLO_2018_hadded/"
  for fix in cHHH0 cHHH1 cHHH2p45 cHHH5; do
    inp=$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2018.root"
    oup=$output"GluGluToHHTo2G2Qlnu_node_"$fix"_2018.root"
    echo "process "$inp" ... "$oup
    mkdir -p $oup
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit

  for fix in cHHH0 cHHH1 cHHH2p45 cHHH5; do
    inp=$input_global$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    oup=$output_global$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    echo "process "$inp" ... "$oup
    mkdir -p $oup
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
fi


if [ "$year" = "2017" ]; then
  input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/SL_LO_2017_noPdfWeight_hadded/"
  output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/2017/Signal/SL_LO_2017_noPdfWeight_hadded/"
  for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
    inp=$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    oup=$output"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    echo "process "$inp" ... "$oup
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit

  input="/2017/Signal/SL_NLO_2017_hadded/"
  #for fix in cHHH1 cHHH0 cHHH2p45 cHHH5; do
  for fix in cHHH0 cHHH2p45 cHHH5; do
    inp=$input_global$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    oup=$output_global$input"GluGluToHHTo2G2Qlnu_node_"$fix"_2017.root"
    echo "process "$inp" ... "$oup
    mkdir -p $output
    time root -l -b -q "reweight_samples.C(\""$inp"\", \""$oup"\", \""$fix"\")"
  done
  exit
fi
