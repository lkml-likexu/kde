#!/bin/bash
# example bash sync_golang_repo.sh
# https://github.com/golang?utf8=✓&q=%5Bmirror%5D&type=&language=

cd $GOPATH/src/golang.org/x

list=(
    "tools"
    "mobile"
    "net"
    "crypto"
    "tour"
    "vgo"
    "playground"
    "text"
    "exp"
    "image"
    "sync"
    "lint"
    "debug"
    "time"
    "build"
    "arch"
    "sys"
    "perf"
    "review"
    "scratch"
    "deb"
    "lint"
    "protobuf"
)

len=${#list[@]}
for i in `seq 0 1 $len`; do  
    echo ${list[$i]}
    echo $len
    echo $i
    if [ "$len" -eq "$i" ]; then
      break
    fi
    if [ -d "${list[$i]}" ]; then
        cd ${list[$i]}
        echo `pwd`
        git checkout master > /dev/null
        git pull > /dev/null
        cd ..
    else
        git clone https://github.com/golang/${list[$i]}.git
    fi
done