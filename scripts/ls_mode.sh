#!/bin/bash
if [ "$#" -eq 3 ]; then
  mod=$1
  par=$2
  unit="mm"
  mode=$3
else
  read -p "job name: " mod
  read -p "offset amount: " par 
  read -p "unit: " unit 
  read -p "mode: " mode 
fi
ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_${mode}_tests/prexII_cadSAMs_${mod}_${par}${unit}*/*.root > list_cadSAMs_${mod}_${par}${unit}.txt 
./hallRad --infile list_cadSAMs_${mod}_${par}${unit}.txt
