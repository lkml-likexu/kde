#!/bin/bash
cd /root/nfs/linux-museum/linux
cat MAINTAINERS | grep "M:" | awk -F "@" '{print $2}' | sort | uniq | sed 's/>//g' | grep -v "^$"> todo

while read line
do
name=`echo ${line} | sed 's/\./_/g' `_maintainers_up_to_v4.20.txt
echo "" > ${name}
echo "First Name\tLast Name\tDisplay Name\tNickname\tPrimary Email\tSecondary Email\tScreen Name\tWork Phone\tHome Phone\tFax Number\tPager Number\tMobile Number\tHome Address\tHome Address 2\tHome City\tHome State\tHome ZipCode\tHome Country\tWork Address\tWork Address 2\tWork City\tWork State\tWork ZipCode\tWork Country\tJob Title\tDepartment\tOrganization\tWeb Page 1\tWeb Page 2\tBirth Year\tBirth Month\tBirth Day\tCustom 1\tCustom 2\tCustom 3\tCustom 4\tNotes\t" >> ${name}
cat MAINTAINERS | grep "${line}" | grep "M:" | sort | uniq | sed 's/M:\t/\t\t/g' | sed 's/"//g' | sed 's/ </\t\t/g' >> ${name}
done < todo

rm -rf todo
