
input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FH_LO_2016_hadded/"
output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production/2016/Signal/FH_LO_2016_hadded/"
c1=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FH_NLO_2016_hadded/GluGluToHHTo2G4Q_node_cHHH1_2016.root
c0=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FH_NLO_2016_hadded/GluGluToHHTo2G4Q_node_cHHH0_2016.root
c2=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FH_NLO_2016_hadded/GluGluToHHTo2G4Q_node_cHHH2p45_2016.root
c5=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FH_NLO_2016_hadded/GluGluToHHTo2G4Q_node_cHHH5_2016.root
for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
  echo $fix
  mkdir -p $output
  inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
  oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2016.root"
  time root -l -b -q "reweight_samples.C(\"FH\", \""$inp"\", \""$oup"\", \""$fix"\", \"2016\", \"$c1\", \"$c0\", \"$c2\", \"$c5\")"
done

input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2017/Signal/FH_LO_2017_hadded/"
output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production/2017/Signal/FH_LO_2017_hadded/"
c1=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FH_NLO_2017_hadded/GluGluToHHTo2G4Q_node_cHHH1_2017.root
c0=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FH_NLO_2017_hadded/GluGluToHHTo2G4Q_node_cHHH0_2017.root
c2=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FH_NLO_2017_hadded/GluGluToHHTo2G4Q_node_cHHH2p45_2017.root
c5=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2016/Signal/FH_NLO_2017_hadded/GluGluToHHTo2G4Q_node_cHHH5_2017.root
for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
  echo $fix
  mkdir -p $output
  inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2017.root"
  oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2017.root"
  time root -l -b -q "reweight_samples.C(\"FH\", \""$inp"\", \""$oup"\", \""$fix"\", \"2017\", \"$c1\", \"$c0\", \"$c2\", \"$c5\")"
done

input="/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FH_LO_2018_hadded/"
output="/eos/user/p/pmandrik/HHWWgg_central/January_2021_Production/2018/Signal/FH_LO_2018_hadded/"
c1=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FH_NLO_2018_hadded/GluGluToHHTo2G4Q_node_cHHH1_2018.root
c0=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FH_NLO_2018_hadded/GluGluToHHTo2G4Q_node_cHHH0_2018.root
c2=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FH_NLO_2018_hadded/GluGluToHHTo2G4Q_node_cHHH2p45_2018.root
c5=/eos/user/a/atishelm/ntuples/HHWWgg_flashgg/January_2021_Production/2018/Signal/FH_NLO_2018_hadded/GluGluToHHTo2G4Q_node_cHHH5_2018.root
for fix in SM 1 2 3 4 5 6 7 8 9 10 11 12; do
  echo $fix
  mkdir -p $output
  inp=$input/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
  oup=$output/"GluGluToHHTo2G4Q_node_"$fix"_2018.root"
  time root -l -b -q "reweight_samples.C(\"FH\", \""$inp"\", \""$oup"\", \""$fix"\", \"2018\", \"$c1\", \"$c0\", \"$c2\", \"$c5\")"
done
exit
