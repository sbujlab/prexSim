#!/bin/bash
if [ "$#" -eq 1 ]; then
  canthick=$1
else
  read -p "job canthick amount (in um, from 0 to 1651 in um): " canthick
fi
ls /lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_canthick_tests/prexII_SAMs_*_${canthick}um*/*.root > list_canthick_${canthick}um.txt 
./hallRad --infile list_canthick_${canthick}um.txt
