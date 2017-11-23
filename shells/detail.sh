#!/bin/bash
cd $HUB/../intel/commit-changes-today
list=(`cat daily-news.txt | grep Updating -B 1| awk '{ print $2 }' | tr -s '\n'`)
len=${#list[@]}
for i in `seq 0 2 $len`; do  
if [ -d "$HUB/${list[$i]}" ]; then
    echo "\n${list[$i]}" >> $HUB/../intel/commit-changes-today/daily-news-details.txt
    cd $HUB/${list[$i]}
    j=i+1
    git log --pretty=oneline ${list[$j]} >> $HUB/../intel/commit-changes-today/daily-news-details.txt
fi
done 
cd $HUB/../intel/commit-changes-today