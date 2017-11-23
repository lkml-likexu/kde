#!/bin/bash

F=$1
FILE=$1.tmp
OUTPUT=`echo $1 | sed 's/\//_/g'`
echo "" > ${OUTPUT}.h
cat ${F} | grep "EXPORT_SYMBOL_GPL" | grep -v "^$" >> ${OUTPUT}.h
# echo "\n" >> ${OUTPUT}.h
cat ${F} | grep -v "#if" | grep -v "#else" > ${FILE}
cat ${FILE} | grep -n "^{" | awk -F ":" '{ print $1 }' > lines

if [ `cat lines | wc -l` -eq 0 ];then
rm lines
rm ${FILE}
echo "The file $1 has none funtions."
cat ${F} | grep "struct" | grep -v "\*" | sed 's/\t//g' | sed 's/{//g' | sed 's/;//g' | grep -v "^$" | sort | uniq >> ${OUTPUT}.h
exit
fi

while read line
do
i=`expr ${line} - 1`
cond=`sed -n "${i},${i}p" ${FILE} | grep "^$" | wc -l`
while [ "${cond}" -ne 1 ]
do
i=`expr ${i} - 1`
cond=`sed -n "${i},${i}p" ${FILE} | grep "^$" | wc -l`
done
sed -n "${i},${line}p" ${FILE} | grep -v "{" | grep -v "^$" >> ${OUTPUT}
done < lines

# macos x
# echo "\n" >> ${OUTPUT}.h
sh $HUB/kde/shells/remove_comment.sh ${OUTPUT} | tr "\t" " " | tr "\n" " " | tr " " "#" | \
    sed 's/##//g' | sed 's/#/ /g' | sed 's/,/, /g' | \
    sed 's/  / /g' | sed -e 's/)/)\'$'\n/g' | sed 's/^ //g' | grep -v '^$' >> ${OUTPUT}.h

# linux
# sh /root/kde/shells/remove_comment.sh ${OUTPUT} | tr "\t" " " | tr "\n" " " | tr " " "#" | \
#     sed 's/##//g' | sed 's/#/ /g' | sed 's/,/, /g' | \
#     sed 's/  / /g' | sed -e 's/)/)\n/g' | sed 's/^ //g' >> ${OUTPUT}.h
# echo "\n" >> ${OUTPUT}.h

cat ${OUTPUT}.h | grep -o "(.*)" | tr "," "\n" | sed 's/(//g' | sed 's/)//g' | sed 's/^ //g' | grep -v '^$' |sort | uniq -c| sort -nr >> ${OUTPUT}.h

rm ${OUTPUT}
rm lines
rm ${FILE}

mv ${OUTPUT}.h /Volumes/hardcore/git-clone-repo/kde/code-readpad/kernel-schema/

# linux: cat arch_x86_kvm_cpuid.c.h | tr "\n" " " | tr "\t" " " | tr " " "#" | sed 's/##//g'  |  sed 's/#/ /g' | sed 's/  //g' |sed 's/,/, /g'|sed 's/  / /g'|sed 's/)/);\n/g'
