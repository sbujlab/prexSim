#!/bin/bash
read -p "job input list.txt file name: " list
while read p; do 
  /site/bin/swif add-jsub -workflow offsets -script $p 
done <$list
