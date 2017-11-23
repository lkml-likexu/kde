#!/bin/bash
cat */*.patch | grep "|" | awk -F "|" '{ print $1 }' | sed 's/ //g' | grep -v "s390" | grep -v "arm" | grep -v "mips" | grep -v "power" | grep -v "amd" | grep -Ev "^$|#" | grep -v "\.\.\."| grep "\/" | grep -Ev "\t" | sort | uniq > changed_files.txt
