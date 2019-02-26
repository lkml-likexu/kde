#!/bin/bash
# demo sh batch.sh
 
for i in `seq 2 1 2`
do
    for j in `seq 21 1 26`
    do
    echo "sh get_kvm_patch_series_today.sh -d 2019-`printf "%02d\n" $i`-`printf "%02d\n" $j`"
    sh get_kvm_patch_series_today.sh -d 2019-`printf "%02d\n" $i`-`printf "%02d\n" $j` &
    sleep 0.5
    done
done
