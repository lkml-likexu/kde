#!/bin/bash
cd $HUB/../intel/commit-changes-today
list=(`cat daily-news.txt | grep Updating -B 1| awk '{ print $2 }' | tr -s '\n'`)
len=${#list[@]}
for i in `seq 0 2 $len`; do  
if [ -d "$HUB/${list[$i]}" ]; then
    echo "\n${list[$i]}" >> $HUB/../intel/commit-changes-today/details.txt
    cd $HUB/${list[$i]}
    j=i+1
    git log --pretty=oneline ${list[$j]} >> $HUB/../intel/commit-changes-today/details.txt
    PROJ=${list[$i]}
    git diff ${list[$j]} >> $HUB/../intel/commit-changes-today/${PROJ%%/*}-"$(date +%Y%m%d)".patch
fi
done 
cd $HUB/../intel/commit-changes-today
rm ./-*.patch
mv *.patch $HUB/kde/code-review/
cd $HUB/kde/code-review/
#git add .
#git commit -m "[code review]updated"
#git push
