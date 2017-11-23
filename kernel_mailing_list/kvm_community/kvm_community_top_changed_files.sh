#!/bin/bash
# sh kvm_community_top_changed_files.sh
cd /root/kde/kernel_mailing_list/kvm_community
cat `find . -name "*.patch"` | grep -E "\-\-\- |\+\+\+ " | sed 's/\-\-\- a\///g' | sed 's/\+\+\+ b\///g' | grep -Ev "/dev/null|\+|\-" | sort | uniq -c | sort -nr > kvm_community_top_changed_files.txt

cat kvm_community_top_changed_files.txt | awk '{ print $2 }'  > feature-structure-uncheck.txt
