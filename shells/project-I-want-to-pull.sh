#!/bin/bash

path="/Volumes/hardcore/intel/commit-changes-today"
cd $HUB

path2=`pwd`
echo "["`date`"]" >> $path/tmp.txt

for i in `ls -d */`
do
cd $path2/$i
pwd
echo "===> "$i >> $path/tmp.txt
git checkout master > /dev/null   
git pull >> $path/tmp.txt
echo "[last updated] "`git log -p -1 | grep Date | head -n 1` >> $path/tmp.txt
echo "["$i"]""[#commit in 07 days]" `git log --relative-date -7 | grep commit | wc -l` >> $path/tmp.txt
echo "["$i"]""[#commit in 30 days]" `git log --relative-date -30 | grep commit | wc -l` >> $path/tmp.txt
echo "["$i"]""[#commit in 60 days]" `git log --relative-date -60 | grep commit | wc -l` >> $path/tmp.txt
done

cat $path/tmp.txt | grep -v "Already up-to-date." > $path/daily-news.txt
rm $path/tmp.txt