#### [PATCH 1/3] KVM/x86: Fix invvpid and invept register operand size in 64-bit mode
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Register operand size of invvpid and invept instruction in 64-bit mode
has always 64 bits. Adjust inline function argument type to reflect
correct size.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: unconditionally cancel preemption timer in free_nested
##### From: Peter Shier <pshier@google.com>

```c
There are multiple code paths where an hrtimer may have been started to
emulate an L1 VMX preemption timer that can result in a call to free_nested
without an intervening L2 exit where the hrtimer is normally
cancelled. Unconditionally cancel in free_nested to cover all cases.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reported-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: vmx: hyper-v: don't pass EPT configuration info to vmx_hv_remote_flush_tlb()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
I'm observing random crashes in multi-vCPU L2 guests running on KVM on
Hyper-V. I bisected the issue to the commit 877ad952be3d ("KVM: vmx: Add
tlb_remote_flush callback support"). Hyper-V TLFS states:

"AddressSpace specifies an address space ID (an EPT PML4 table pointer)"

So apparently, Hyper-V doesn't expect us to pass naked EPTP, only PML4
pointer should be used. Strip off EPT configuration information before
calling into vmx_hv_remote_flush_tlb().

Fixes: 877ad952be3d ("KVM: vmx: Add tlb_remote_flush callback support")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] arm/arm64: KVM: rename function kvm_arch_dev_ioctl_check_extension()
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Rename kvm_arch_dev_ioctl_check_extension() to
kvm_arch_vm_ioctl_check_extension(), because it does
not have any relationship with device.

Renaming this function can make code readable.

Cc: James Morse <james.morse@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Acked-by: James Morse <james.morse@arm.com>
---
I remeber James also mentioned that rename this function.
---
 arch/arm/include/asm/kvm_host.h   | 2 +-
 arch/arm64/include/asm/kvm_host.h | 2 +-
 arch/arm64/kvm/reset.c            | 4 ++--
 virt/kvm/arm/arm.c                | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
