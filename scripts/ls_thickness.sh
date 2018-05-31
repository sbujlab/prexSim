#!/bin/bash
if [ "$#" -eq 1 ]; then
  thickness=$1
else
  read -p "job thickness amount (in mm, from 0 to 13): " thickness
fi
ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_thickness_tests/prexII_SAMs_*_${thickness}mm*/*.root > list_thickness_${thickness}mm.txt 
./hallRad --infile list_thickness_${thickness}mm.txt
