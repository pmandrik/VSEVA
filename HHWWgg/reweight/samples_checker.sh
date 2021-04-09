





for f in $( find /eos/user/p/pmandrik/HHWWgg_central/January_2021_Production_v2/* -name '*2G2l2nu*.root' ); do
  echo $f
  root -l -b -q "check_sample.C(\""$f"\")"
done;


