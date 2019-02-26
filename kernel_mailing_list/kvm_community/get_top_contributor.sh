#!/bin/bash

cd /root/kde/kernel_mailing_list/kvm_community
find . -name "*.patch" > target.list

while read line
do
cat ${line} | grep -E "^([a-zA-Z0-9_\-\.\+]+)" | grep -E "^From: " | sed 's/\"//g' | sed 's/From: //g' >> output
done < target.list

cat output | sort |uniq -c|sort -nr > contributors_output.txt

rm target.list output
