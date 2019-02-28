#!/bin/bash
rm report.txt
tags=($(git for-each-ref --sort=taggerdate refs/tags | grep -v "rc" | awk '{ print $3}'))
length=${#tags[@]}
COUNT=`expr $length - 1`
for var in `seq 0 1 $COUNT`
do
from=`echo ${tags[$var]} | sed 's/refs\/tags\///g'`
next=`expr $var + 1`
to=`echo ${tags[${next}]} | sed 's/refs\/tags\///g'`
echo "tag: ${from} --" `git log -1 --format=%ci ${from}` >> report.txt
echo "" >> report.txt
cat contributors_${from}_${to}.txt >> report.txt
echo "" >> report.txt
done

from="v4.20"
echo "tag: ${from} --" `git log -1 --format=%ci ${from}` >> report.txt
