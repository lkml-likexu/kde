#### [PATCH] KVM: nVMX: reorganize initial steps of vmx_set_nested_state
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Commit 332d079735f5 ("KVM: nVMX: KVM_SET_NESTED_STATE - Tear down old EVMCS
state before setting new state", 2019-05-02) broke evmcs_test because the
eVMCS setup must be performed even if there is no VMXON region defined,
as long as the eVMCS bit is set in the assist page.

While the simplest possible fix would be to add a check on
kvm_state->flags & KVM_STATE_NESTED_EVMCS in the initial "if" that
covers kvm_state->hdr.vmx.vmxon_pa == -1ull, that is quite ugly.

Instead, this patch moves checks earlier in the function and
conditionalizes them on kvm_state->hdr.vmx.vmxon_pa, so that
vmx_set_nested_state always goes through vmx_leave_nested
and nested_enable_evmcs.

Fixes: 332d079735f5
Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c                          | 26 ++++++++++--------
 .../kvm/x86_64/vmx_set_nested_state_test.c         | 32 ++++++++++++++--------
 2 files changed, 35 insertions(+), 23 deletions(-)

```
#### [PATCH v4 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

no changes in v4.
---
 arch/x86/include/asm/vmx.h      | 1 +
 arch/x86/kvm/cpuid.c            | 2 +-
 arch/x86/kvm/vmx/capabilities.h | 6 ++++++
 arch/x86/kvm/vmx/vmx.c          | 4 ++++
 4 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH v1 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

This patch is meant to move the head/tail adding logic out of the shuffle
code and into the __free_one_page function since ultimately that is where
it is really needed anyway. By doing this we should be able to reduce the
overhead and can consolidate all of the list addition bits in one spot.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   70 +++++++++++++++++++++++++++---------------------
 mm/shuffle.c           |   24 ----------------
 mm/shuffle.h           |   35 ++++++++++++++++++++++++
 4 files changed, 74 insertions(+), 67 deletions(-)

```
#### [PATCH 1/1] kvm: selftests: add selftest for SPP feature
##### From: Weijiang Yang <weijiang.yang@intel.com>

```c
From: Yang Weijiang <weijiang.yang@intel.com>

Sub-Page Permission(SPP) is to protect finer granularity subpages
(128Byte each) within a 4KB page. It's not enabled in KVM by default,
the test first initializes the SPP runtime environment with
KVM_INIT_SPP ioctl, then sets protection with KVM_SUBPAGES_SET_ACCESS
for the target guest page, check permissions with KVM_SUBPAGES_GET_ACCESS
to make sure they are set as expected.

There're two steps in guest code to very whether SPP is working:
1) protect all 128byte subpages, write data to each subpage
to see if SPP induced EPT violation happening. 2)unprotect all
subpages, again write data to each subpage to see if SPP still
works or not.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 tools/testing/selftests/kvm/Makefile          |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/x86_64/spp_test.c | 206 ++++++++++++++++++
 3 files changed, 208 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/spp_test.c

```
#### [QEMU PATCH v4 01/10] target/i386: kvm: Delete VMX migration blocker on vCPU init failure
##### From: Liran Alon <liran.alon@oracle.com>

```c
Commit d98f26073beb ("target/i386: kvm: add VMX migration blocker")
added migration blocker for vCPU exposed with Intel VMX because QEMU
doesn't yet contain code to support migration of nested virtualization
workloads.

However, that commit missed adding deletion of the migration blocker in
case init of vCPU failed. Similar to invtsc_mig_blocker. This commit fix
that issue.

Fixes: d98f26073beb ("target/i386: kvm: add VMX migration blocker")
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Maran Wilson <maran.wilson@oracle.com>
---
 target/i386/kvm.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v1 QEMU] QEMU: Provide a interface for hinting based off of the balloon infrastructure
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "bubble hinting". Basically the
idea is to function very similar to how the balloon works in that we
basically end up madvising the page as not being used. However we don't
really need to bother with any deflate type logic since the page will be
faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/trace-events                          |    1 
 hw/virtio/virtio-balloon.c                      |   73 +++++++++++++++++++++++
 include/hw/virtio/virtio-balloon.h              |    2 -
 include/standard-headers/linux/virtio_balloon.h |    1 
 4 files changed, 76 insertions(+), 1 deletion(-)

```
#### [PATCH v3] KVM: PPC: Report single stepping capability
##### From: Fabiano Rosas <farosas@linux.ibm.com>

```c
When calling the KVM_SET_GUEST_DEBUG ioctl, userspace might request
the next instruction to be single stepped via the
KVM_GUESTDBG_SINGLESTEP control bit of the kvm_guest_debug structure.

This patch adds the KVM_CAP_PPC_GUEST_DEBUG_SSTEP capability in order
to inform userspace about the state of single stepping support.

We currently don't have support for guest single stepping implemented
in Book3S HV so the capability is only present for Book3S PR and
BookE.

Signed-off-by: Fabiano Rosas <farosas@linux.ibm.com>
---

v1 -> v2:
 - add capability description to Documentation/virtual/kvm/api.txt

v2 -> v3:
 - be explicit in the commit message about when the capability is
   present
 - remove unnecessary check for CONFIG_BOOKE

 Documentation/virtual/kvm/api.txt | 3 +++
 arch/powerpc/kvm/powerpc.c        | 2 ++
 include/uapi/linux/kvm.h          | 1 +
 3 files changed, 6 insertions(+)

--
2.20.1

```
