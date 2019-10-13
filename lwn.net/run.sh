#!/bin/bash
# run.sh

wget https://lwn.net/Kernel/Index/ -O index.html
cat index.html| grep -oE "<a name=\".*?\"><a href=\"|<a href=\"/Articles/.*?/\">" | awk -F '"' '{print $2}' > Kernel-Index-url.txt.2
rm index.html

wget https://lwn.net/Archives/GuestIndex/ -O index.html
cat index.html| grep -oE "<a name=\".*?\"><a href=\"|<a href=\"/Articles/.*?/\">" | awk -F '"' '{print $2}' > Guest-Index-url.txt.2
rm index.html
