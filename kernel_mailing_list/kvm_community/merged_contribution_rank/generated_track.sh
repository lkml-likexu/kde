#!/bin/bash
cat report.txt | awk -F "--" '{ print $1 }' | grep -v "tag: " | awk '{for(i=2;i<=NF;i++) printf $i""FS;print ""}' | grep -v "^$" |sort | uniq > names.txt
rm track.txt
cd contributors_by_tag
while read line
do
echo "${line}:" >> ../track.txt
grep -Fw "${line}" *  >> ../track.txt
echo "" >> ../track.txt
done < ../names.txt
cd ..
rm names.txt

cat track.txt | sed 's/contributors_/  git log /g' | sed 's/.txt://g' | sed 's/_/../g' > .tmp
mv .tmp track.txt

echo "demo usage: git log v3.18..v3.19 --author=\"wanghaibin.wang@huawei.com\""
