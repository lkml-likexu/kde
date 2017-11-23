#!/bin/sh 
for i in `ls -d */`
do
   cd $i
   echo `pwd` 
   git checkout master > /dev/null
   git pull > /dev/null
   cd ..
done