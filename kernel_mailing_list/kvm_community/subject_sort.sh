#!/bin/bash

# rm cover_letters.txt
# for i in `ls 2020*/overview_covers_*.md`
# do
# echo ${i}
# sed '/\`\`\`c/,/X-Mailing-List/d' ${i} | grep -v "\`\`\`" >> cover_letters.txt
# done

# cat cover_letters.txt | grep -i "Subject:" | sed s/Subject://g > subjects.txt

echo ""
echo "x86"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -i "x86"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -i " vmx"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -Ei "CET|VM introspectio"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -i SVM

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm| grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -i SEV

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR" | grep -iv SELinux | grep -iv virtio-mem | grep -iv "powerpc" | grep -i "Dirty ring"

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

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR" | grep -iv SELinux | grep -i virtio-mem

echo ""
echo "pmu"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -iE "PEBS|Last Branch Recording|LBR"

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

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR" | grep -iv SELinux | grep -iv virtio-mem | grep -i "powerpc"

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR" | grep -iv SELinux | grep -iv virtio-mem | grep -iv "powerpc" | grep -iv "Dirty ring"

echo ""
echo "SELinux"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -Evi "tools|kvmtool" | grep -iv SVM | grep -iv SEV | grep -iv nVMX | grep -iv vDPA | grep -viE "CET|VM introspectio" | grep -viE "PEBS|Last Branch Recording|LBR" | grep -i SELinux

echo ""
echo "kvm-unit-test|selftest"
echo ""

cat subjects.txt | grep kvm-unit-test
cat subjects.txt | grep -v kvm-unit-test | grep selftest

echo ""
echo "tool"
echo ""

cat subjects.txt | grep -v kvm-unit-test | grep -v selftests | grep -v hyper-v | grep -vi "x86" | grep -vi arm | grep -v s390 | grep -vi vfio | grep -vi " vmx" | grep -iv vhost | grep -iv RISC | grep -vi iommu | grep -iE "tools|kvmtool"