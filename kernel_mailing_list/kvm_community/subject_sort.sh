#!/bin/bash

cd /root/kde/kernel_mailing_list
cp -r kvm_community/ target
cd target

rm -rf 2018* 2019* 2020-01* 2020-02*
for i in `seq 1 1 8`
do
rm -rf 2020-03-0${i}
done

# for i in `seq 10 1 31`
# do
# rm -rf 2020-03-${i}
# done

rm ../kvm_community/cover_letters.txt
for i in `ls 2020*/overview_covers_*.md`
do
echo ${i}
# sed '/\`\`\`c/,/X-Mailing-List/d' ${i} | grep -v "\`\`\`" >> cover_letters.txt
sed '/```c/,/X-Mailing-List/d' ${i} | grep -v "\`\`\`" >> ../kvm_community/cover_letters.txt
done

# cat cover_letters.txt | grep -i "Subject:" | sed s/Subject://g > subjects.txt
cat ../kvm_community/cover_letters.txt | grep -wi "#### " | sed 's/#### //g' | sort | uniq > ../kvm_community/subjects.txt

rm ../kvm_community/series_letters.txt
for i in `ls 2020*/overview_series_*.md`
do
echo ${i}
sed '/```c/,/X-Mailing-List/d' ${i} | grep -v "\`\`\`" >> ../kvm_community/series_letters.txt
done

cat ../kvm_community/series_letters.txt | grep -wi "#### " | sed 's/#### //g' | grep -v "\[.*/.*]"| grep -v "^#" | grep -v "^$" >> ../kvm_community/subjects.txt

cd ../kvm_community/

echo ""
echo "x86"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -i "x86"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -i " vmx"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -Ei "CET|VM introspectio"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -i SVM

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm| grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -i SEV

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR|pmu" | grep -iv SELinux | grep -iv virtio-mem | grep -iv "powerpc" | grep -i "Dirty ring"

echo ""
echo "vfio|iommu"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -i vfio

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -i iommu

echo ""
echo "vhost|virtio"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -i vhost

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -i vDPA

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR|pmu" | grep -iv SELinux | grep -i virtio-mem

echo ""
echo "pmu"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -iE "PEBS|Last Branch Recording|LBR|pmu"

echo ""
echo "nVMX"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -i nVMX

echo ""
echo "hyper-v|arm|RISC|s390|powerpc"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep hyper-v

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -v -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -i RISC

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -i arm

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm| grep s390

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR|pmu" | grep -iv SELinux | grep -iv virtio-mem | grep -i "powerpc"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR|pmu" | grep -iv SELinux | grep -iv virtio-mem | grep -iv "powerpc" | grep -iv "Dirty ring"

echo ""
echo "SELinux"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR|pmu" | grep -i SELinux

echo ""
echo "kvm-unit-test|selftest"
echo ""

cat subjects.txt | grep kvm-unit-test
cat subjects.txt | grep -v kvm-unit-test | grep selftest

echo ""
echo "tool"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -iE "tools|kvmtool"

rm -rf subjects.txt series_letters.txt ../target/