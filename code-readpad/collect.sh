#! /bin/bash

# demo bash collect.sh result `pwd`

result=$1
t_path=$2

ls -1 ${t_path}/${result} > ${t_path}/files.list

rm ${t_path}/${result}/*/.tmp
cat ${t_path}/${result}/*/target_name.txt > target.list

cat ${t_path}/files.list | while read var
do
    cp ${t_path}/${result}/${var}/changelog.patch ${t_path}/${var}-changelog.patch
    cp ${t_path}/${result}/${var}/change-size.txt ${t_path}/${var}-changesize.txt
done

rm ${t_path}/files.list
