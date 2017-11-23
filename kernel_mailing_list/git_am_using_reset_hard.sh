#!/bin/bash

while getopts "f:r:" arg #选项后面的冒号表示该选项需要参数
do
    case $arg in
        f)
            echo "The arg is : $OPTARG" #参数存在$OPTARG中
            target_patch=$OPTARG
            day=`cat ${target_patch} | grep "Date" | head -n1 | sed "s/Date: //g"`
            DATE=`date -d "${day}" "+%Y-%m-%d"`
            branch_name=`echo ${target_patch} | sed "s/\[//g" | sed "s/\]//g" | \
                    sed "s/://g" | sed "s/\///g" | sed "s/ /_/g" | sed "s/\./_/g"`   
            git checkout -b ${branch_name} master
            for i in `git log --before="${DATE}" | grep "commit " | head -n10 | awk '{ print $2 }'`
            do
                echo ${i}
                git reset --hard ${i}
                git am ${target_patch}
                if [ ! -f ".git/rebase-apply/patch" ]; then
                    echo "git am SUCCESS on commit ${i}"
                    exit
                fi
                echo "git am FAILED on commit ${i}"
                git am --abort
            done
            git am ${target_patch}
            ;;
        r)
            echo "The arg is : $OPTARG" #参数存在$OPTARG中
            git am --abort
            target_patch=$OPTARG
            day=`cat ${target_patch} | grep "Date" | head -n1 | sed "s/Date: //g"`
            DATE=`date -d "${day}" "+%Y-%m-%d"`
            branch_name=`echo ${target_patch} | sed "s/\[//g" | sed "s/\]//g" | \
                    sed "s/://g" | sed "s/\///g" | sed "s/ /_/g" | sed "s/\./_/g"`
            git checkout master
            git branch -D ${branch_name}
            ;;
        ?)  #当有不认识的选项的时候arg为?
        echo "unkonw argument"
    exit 1
    ;;
    esac
done