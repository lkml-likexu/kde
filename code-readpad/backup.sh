#!/bin/bash

# demo: bash run.sh target.list /root/nfs/auto-git-log /root/nfs/linux-museum

file=$1
t_path=$2
f_path=$3

cd {f_path}
git add .
git reset --hard v4.17.0

cd ${t_path}
chmod -w ${t_path}/${file}

cat ${t_path}/${file} | while read var
do
    echo "Dealing with ${var}"
    echo ${var} > .tmp
    sed -i "s/\///g" .tmp
    target=`cat .tmp`
    mkdir `cat .tmp`
    cd ${target}

    git init
    echo ${var} > target_name.txt
    git add .
    git commit -m "target source code file : ${var}"
    
    cd ${f_path}
    git for-each-ref --sort=taggerdate --format='%(refname)' > ${t_path}/tags.txt

    cd ${t_path}
    cat tags.txt | grep tags > .tmp
    mv .tmp tags.txt
    sed -i "s/refs\/tags\/v//g" tags.txt

    cat tags.txt | while read tag
    do
        cd ${t_path}/${target}
        if [ -f "${t_path}/${target}/${var}" ]; then
            echo "rm ${t_path}/${target}/${var}"
            rm ${t_path}/${target}/${var}
        fi

        cd ${f_path}
        git add .
        git reset --hard v${tag}
           
        if [ ! -f "${t_path}/${target}/${var}" ]; then
            echo "acquire ${var}"
            rsync -R ${var} ${t_path}/${target}/
        else
            echo "do nothing about ${var}"
        fi

        cd ${t_path}/${target}

        git add .
        git commit -m "v${tag}"
    done
done

git log --pretty=oneline --shortstat > ${t_path}/${target}/change-size.txt
git show `git log --pretty=oneline | awk '{ print $1 }'` > ${t_path}/${target}/changelog.patch

chmod +w ${t_path}/${file}

exit 0
