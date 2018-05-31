#!/bin/bash
if [ "$#" -eq 1 ]; then
  offset=$1
else
  read -p "job offset amount (in mm, from 0 to 360): " offset
fi
ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_offset_tests/prexII_SAMs_*_${offset}mm*/*.root > list_offset_${offset}mm.txt 
./hallRad --infile list_offset_${offset}mm.txt
