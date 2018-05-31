#!/bin/bash
if [ $1 == "-h" ]; then
  echo "usage: ./hallrad_parser ../../prexSim/scripts/list_config.txt"
else
  user_list=${1}
  while read p; do
    #arr=(${p//${2}/ })
    strippedFront=${p//${2}/}
    number=${strippedFront//${3}/}
    ./ls_${3}.sh $number
    #echo $number
  done <$user_list
fi
