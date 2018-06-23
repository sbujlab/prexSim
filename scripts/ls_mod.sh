#!/bin/bash
if [ "$#" -eq 2 ]; then
  mod=$1
  par=$2
  unit="mm"
else
  read -p "job name: " mod
  read -p "job parameter: " par 
  read -p "unit: " unit 
fi
echo "ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_improved_tests/prexII_${mod}_${par}${unit}*/*.root > list_${mod}_${par}${unit}.txt"
ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_improved_tests/prexII_${mod}_${par}${unit}*/*.root > list_${mod}_${par}${unit}.txt 
./hallRad --infile list_${mod}_${par}${unit}.txt
