#!/bin/bash
rm achievement_*.txt
path2=`pwd`
list=(`cat details.txt | grep -v 'Merge tag' | grep -v 'Merge branch' | awk '{print $1}'`)
len=${#list[@]}
for i in `seq 1 2 $len`; do  
cd $HUB/${list[0]}
echo `git show --pretty=oneline ${list[$i]} | head -n 1 | awk '{print $2}'` \
    `git show ${list[$i]} | grep "Author:" | grep -o "[^<]*@[^>]*"` ${list[$i]} >> $path2/tmp.txt
done
cd $path2
cat tmp.txt | sort >> achievement_${list[1]:0:8}_${list[$len-1]:0:8}.txt
rm tmp.txt