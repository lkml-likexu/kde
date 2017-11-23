#!/bin/bash
while read line
do
i=`cat ~/.procmailrc| grep ${line} | wc -l`
if [ $i=0 ]; then  
echo ${line} >> target
fi
done < tmp


#:0
#* ^TOlwn@lwn.net
#lwn/

while read line
do
echo ":0" >> demo
i=`echo ${line} | awk -F "@" '{print $1}'`
echo "${line}" >> demo
echo "${i}/" >> demo
echo "\n" >> demo
done < target