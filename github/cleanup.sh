#!/bin/bash

rm -rf projects.20*

# cat projects.total| awk '{print $1}' | sort | uniq > tmp
# mv tmp projects.total
# cat users.total | awk '{print $1}' | sort | uniq > tmp
# mv tmp users.total

cat projects_urls.20* | sort | uniq | awk -F 'github.com/' '{print $2}' >> projects.total

cat projects.total | awk '{ print $1 }' | sed 's/"//g' | sort | uniq > tmp
mv tmp projects.total

rm projects_urls.20*

cat users.20* | sort | uniq | awk -F 'github.com/' '{print $2}' >> users.total
cat users.total | awk '{ print $1 }' | sed 's/"//g' | sort | uniq > tmp
mv tmp users.total

rm -rf users.20*