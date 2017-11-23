#!/bin/bash
# demo sh batch.sh
for i in `seq 6 1 9`
do
    for j in `seq 1 1 31`
    do
    echo "sh get_kvm_patch_series_today.sh -d 2018-`printf "%02d\n" $i`-`printf "%02d\n" $j`"
    sh get_kvm_patch_series_today.sh -d 2018-`printf "%02d\n" $i`-`printf "%02d\n" $j` &
    sleep 0.5
    done
done