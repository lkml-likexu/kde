#!/bin/bash

cd /root/kde/kernel_mailing_list/target
find . -name "*.patch" > target.list

while read line
do
cat ${line} | grep -E "^([a-zA-Z0-9_\-\.\+]+)" | grep -E "^From: " | sed 's/\"//g' | sed 's/From: //g' >> output
done < target.list

cat output | sort |uniq -c|sort -nr > contributors_output.txt

# https://www.it610.com/article/3096642.htm
cat output | awk -F '@' '{print $2}' | sed 's/>//g' | \
sort| uniq -c | awk '{a[$1" "$2]+=$3}END{for (i in a){print i" "a[i]}}'|sort -nr > company_output.txt

rm target.list output
