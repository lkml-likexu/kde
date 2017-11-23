#!/bin/bash

# demo: bash run.sh target.list /root/nfs/kde/code-readpad /root/nfs/linux-museum

file=$1
t_path=$2
f_path=$3

cd ${f_path}
git add .
git reset --hard v4.17.0
git for-each-ref --sort=taggerdate --format='%(refname)' > ${t_path}/tags.txt

echo -e "generating tags.txt\n"
cd ${t_path}
chmod -w ${t_path}/${file}
cat ${t_path}/tags.txt | grep tags > ${t_path}/.tmp
mv ${t_path}/.tmp ${t_path}/tags.txt
sed -i "s/refs\/tags\/v//g" ${t_path}/tags.txt

echo -e "mkdir for target_files\n"
cd ${t_path}
cat ${t_path}/${file} | while read var
do
    echo "${var}"
    echo ${var} > ${t_path}/.tmp
    sed -i "s/\///g" ${t_path}/.tmp
    target=`cat ${t_path}/.tmp`

    cd ${t_path}
    mkdir ${target}
    
    cd ${t_path}/${target}
    git init
    echo ${var} > target_name.txt
    git add .
    git commit -m "target source code file : ${var}"
done

cd ${t_path}
cat ${t_path}/tags.txt | while read tag
do
    cd ${f_path}
    git add .
    git reset --hard v${tag}

    cd ${t_path}
    cat ${t_path}/${file} | while read var
    do
        echo ${var} > ${t_path}/.tmp
        sed -i "s/\///g" ${t_path}/.tmp
        target=`cat ${t_path}/.tmp`

        cd ${t_path}/${target}
        if [ -f "${t_path}/${target}/${var}" ]; then
            echo "rm ${t_path}/${target}/${var}"
            rm ${t_path}/${target}/${var}
        fi
    
        echo "acquire ${var}"
        cd ${f_path}
        rsync -R ${var} ${t_path}/${target}/

        cd ${t_path}/${target}
        git add --all .
        git commit -m "v${tag}"
    done  
done

cd ${t_path}
cat ${t_path}/${file} | while read var
do
    echo ${var} > .tmp
    sed -i "s/\///g" .tmp
    target=`cat .tmp`
    cd ${t_path}/${target}

    git log --pretty=oneline --shortstat > ${t_path}/${target}/change-size.txt
    git show `git log --pretty=oneline | awk '{ print $1 }'` > ${t_path}/${target}/changelog.patch
done

cd ${t_path}
chmod +w ${t_path}/${file}

exit 0
