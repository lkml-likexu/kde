#### [kvm-unit-tests PATCH 1/7] lib: arm: Discover ns16550a UART
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Add support for discovering the ns16550a UART from the device tree. This
particular UART model is emulated by kvmtool.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Andre Przywara <andre.przywara@arm.com>
---
 lib/arm/io.c | 18 +++++++++++-------
 1 file changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH 01/14] arm/arm64: KVM: Introduce kvm_call_hyp_ret()
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
From: Marc Zyngier <marc.zyngier@arm.com>

Until now, we haven't differentiated between HYP calls that
have a return value and those who don't. As we're about to
change this, introduce kvm_call_hyp_ret(), and change all
call sites that actually make use of a return value.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/include/asm/kvm_host.h   | 3 +++
 arch/arm64/include/asm/kvm_host.h | 1 +
 arch/arm64/kvm/debug.c            | 2 +-
 virt/kvm/arm/arm.c                | 2 +-
 virt/kvm/arm/vgic/vgic-v3.c       | 4 ++--
 5 files changed, 8 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/3] KVM: MMU: introduce possible_writable_spte_bitmap
##### From: Zhuangyanying <ann.zhuangyanying@huawei.com>

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

It is used to track possible writable sptes on the shadow page on
which the bit is set to 1 for the sptes that are already writable
or can be locklessly updated to writable on the fast_page_fault
path, also a counter for the number of possible writable sptes is
introduced to speed up bitmap walking.

This works very efficiently as usually only one entry in
PML4 ( < 512 G)，few entries in PDPT (only entry indicates 1G
memory), PDEs and PTEs need to be write protected for the worst case.

Later patch will benefit good performance by using this bitmap and
counter to fast figure out writable sptes and write protect them.

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
Signed-off-by: Zhuang Yanying <ann.zhuangyanying@huawei.com>
---
 arch/x86/include/asm/kvm_host.h |  5 +++-
 arch/x86/kvm/mmu.c              | 53 +++++++++++++++++++++++++++++++++++++++--
 2 files changed, 55 insertions(+), 3 deletions(-)

```
#### [PATCH v6 01/13] KVM: s390: drop obsolete else path
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
The explicit else path specified in set_intercept_indicators_io
is not required as the function returns in case the first branch
is taken anyway.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 arch/s390/kvm/interrupt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 01/29] KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The vCPU-run asm blob does a manual comparison of a VMCS' launched
status to execute the correct VM-Enter instruction, i.e. VMLAUNCH vs.
VMRESUME.  The launched flag is a bool, which is a typedef of _Bool.
C99 does not define an exact size for _Bool, stating only that is must
be large enough to hold '0' and '1'.  Most, if not all, compilers use
a single byte for _Bool, including gcc[1].

Originally, 'launched' was of type 'int' and so the asm blob used 'cmpl'
to check the launch status.  When 'launched' was moved to be stored on a
per-VMCS basis, struct vcpu_vmx's "temporary" __launched flag was added
in order to avoid having to pass the current VMCS into the asm blob.
The new  '__launched' was defined as a 'bool' and not an 'int', but the
'cmp' instruction was not updated.

This has not caused any known problems, likely due to compilers aligning
variables to 4-byte or 8-byte boundaries and KVM zeroing out struct
vcpu_vmx during allocation.  I.e. vCPU-run accesses "junk" data, it just
happens to always be zero and so doesn't affect the result.

[1] https://gcc.gnu.org/ml/gcc-patches/2000-10/msg01127.html

Fixes: d462b8192368 ("KVM: VMX: Keep list of loaded VMCSs, instead of vcpus")
Cc: <stable@vger.kernel.org>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] kvm: x86/vmx: Use kzalloc for cached_vmcs12From: Tom Roeder <tmroeder@google.com>
##### From: Tom Roeder <tmroeder@google.com>

```c
This changes the allocation of cached_vmcs12 to use kzalloc instead of
kmalloc. This removes the information leak found by Syzkaller (see
Reported-by) in this case and prevents similar leaks from happening
based on cached_vmcs12.

It also changes vmx_get_nested_state to copy out the full 4k VMCS12_SIZE
in copy_to_user rather than only the size of the struct.

Tested: rebuilt against head, booted, and ran the syszkaller repro
  https://syzkaller.appspot.com/text?tag=ReproC&x=174efca3400000 without
  observing any problems.

Reported-by: syzbot+ded1696f6b50b615b630@syzkaller.appspotmail.com
Signed-off-by: Tom Roeder <tmroeder@google.com>
---
Changelog since v1:
- Changed the copy_to_user calls in vmx_get_nested_state to copy the
  full 4k buffer.

 arch/x86/kvm/vmx/nested.c | 12 ++++++++----
 1 file changed, 8 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/kvm/hyper-v: don't announce GUEST IDLE MSR support
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
HV_X64_MSR_GUEST_IDLE_AVAILABLE appeared in kvm_vcpu_ioctl_get_hv_cpuid()
by mistake: it announces support for HV_X64_MSR_GUEST_IDLE (0x400000F0)
which we don't support in KVM (yet).

Fixes: 2bc39970e932 ("x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] x86/kvm/hyper-v: tweak HYPERV_CPUID_ENLIGHTMENT_INFO
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
We shouldn't probably be suggesting using Enlightened VMCS when it's not
enabled (not supported from guest's point of view). System reset through
synthetic MSR is not recommended neither by genuine Hyper-V nor my QEMU.

Windows seems to be fine either way but let's be consistent.

Fixes: 2bc39970e932 ("x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
