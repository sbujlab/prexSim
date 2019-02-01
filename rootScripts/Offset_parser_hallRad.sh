#!/bin/bash
#if [ $1 == "-h" ]; then
#  echo "usage: -m ./parser_hallrad_root ../prexSim/scripts/list_config.txt stuff_to_strip_from_front_of_number stuff_..._back_of_number"
#  echo "usage: ./parser_hallrad config"
#elif [ $1 == "-m" ]; then
#  user_list=${2}
#  while read p; do
#    strippedFront=${p//${3}/}
#    number=${strippedFront//${4}/}
#    #./ls_${3}.sh $number
#    #echo $number
#  done <$user_list
#else
  user_list=../prexSim/scripts/list_${1}.txt
  while read p; do
    #front="jobs\/prexII_SAMs_cyl_${1}_"
    front="jobs\/prexII_${1}_"
    echo $front
    #jobs/prexII_SAMs_sph_improved_offset_125mm_900kEv.xml
    #strippedFront=${p//$front/}
    strippedFront=$(echo -n $p | tail -c -30)
    #-28)
    numberm=${strippedFront//'ff_thickness_6mm_900kEv.xml'/}
    numberUnits="mm"
    #numberUnits=${strippedFront//'_900kEv.xml'/}
    number=$(echo -n $numberm | head -c -1)
    units=$(echo -n $numberUnits | tail -c -2)
    #./ls_${1}.sh $number
    #echo $number
    root -b -q -l `printf "rootScripts/SAM_rad_calc.C(\"%s\",\"%s\",%s)" "${1}" "${units}" "${number}"`
  done <$user_list
#fi
