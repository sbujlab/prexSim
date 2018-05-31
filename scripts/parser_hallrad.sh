#!/bin/bash
if [ $1 == "-h" ]; then
  echo "usage: -m ./parser_hallrad ../../prexSim/scripts/list_config.txt stuff_to_strip_from_front_of_number stuff_..._back_of_number"
  echo "usage: ./parser_hallrad config"
elif [ $1 == "-m" ]; then
  user_list=${2}
  while read p; do
    strippedFront=${p//${3}/}
    number=${strippedFront//${4}/}
    ./ls_${3}.sh $number
    #echo $number
  done <$user_list
else
  user_list=../../prexSim/scripts/list_${1}.txt
  while read p; do
    front="jobs\/prexII_SAMs_cyl_${1}_"
    strippedFront=${p//$front/}
    numberm=${strippedFront//'m_900kEv.xml'/}
    number=$(echo -n $numberm | head -c -1)
    ./ls_${3}.sh $number
    #echo $number
  done <$user_list
fi
