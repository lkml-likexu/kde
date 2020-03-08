#!/bin/bash
# why 60? you need define the max value of your subscriptions,
# the default value is 30 entries per page

for i in `seq 48 1 60`
do
curl "https://api.github.com/user/subscriptions?page=${i}" \
-H "Accept: application/vnd.github.beta+json" \
-u username:password >> "${i}_this_time_subscriptions".txt &
done

cat demo | grep -vi qemu | grep -vi kvm | grep -vi Unikernel | grep -vi Virtualization | grep -iv sgx | grep -iv Container | grep -iv Microcode | grep -iv bpf | grep -iv Kubernetes | grep -iv risc-v | grep -vi LLVM | grep -vi Android | grep -iv osx | grep -vi macos | grep -iv "Operating System" | grep -viE "Real-time|Real time" | grep -vi Compiler | grep -vi x86 | grep -vi "Virtual Machine" | grep -viE "Linux-Kernel|Linux Kernel" | grep -iv Lisp | grep -vi hypervisor | less