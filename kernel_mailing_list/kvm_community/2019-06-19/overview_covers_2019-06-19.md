

#### [PATCH 0/1] selftest for SPP feature
##### From: Weijiang Yang <weijiang.yang@intel.com>
From: Yang Weijiang <weijiang.yang@intel.com>

```c

From: Yang Weijiang <weijiang.yang@intel.com>

Sub-Page Permission(SPP) is to protect finer granularity subpages
(128Byte each) within a 4KB page. 
There're three specific ioctls for the feature in KVM:
KVM_INIT_SPP - initialize SPP runtime environment 
KVM_SUBPAGES_SET_ACCESS - set SPP protection for guest page
KVM_SUBPAGES_GET_ACCESS - get SPP permission bits for guest page
This selftest uses these ioctls to verify whether SPP is working
on SPP powered platforms.

test results:
--------------------------------------------------------------------------
SPP protected zone: size = 4096, gva = 0x700000, gpa = 0x10001000, hva =
0x0x7f6ff3b92000
SPP initialized successfully.
set spp protection info: gfn = 0x10001, access = 0x0, npages = 1
get spp protection info: gfn = 0x10001, access = 0x0, npages = 1
got matched subpage permission vector.
expect VM exits caused by SPP below.
1 - exit reason: SPP
2 - exit reason: SPP
3 - exit reason: SPP
4 - exit reason: SPP
5 - exit reason: SPP
6 - exit reason: SPP
7 - exit reason: SPP
8 - exit reason: SPP
9 - exit reason: SPP
10 - exit reason: SPP
11 - exit reason: SPP
12 - exit reason: SPP
13 - exit reason: SPP
14 - exit reason: SPP
15 - exit reason: SPP
16 - exit reason: SPP
17 - exit reason: SPP
18 - exit reason: SPP
19 - exit reason: SPP
20 - exit reason: SPP
21 - exit reason: SPP
22 - exit reason: SPP
23 - exit reason: SPP
24 - exit reason: SPP
25 - exit reason: SPP
26 - exit reason: SPP
27 - exit reason: SPP
28 - exit reason: SPP
29 - exit reason: SPP
30 - exit reason: SPP
31 - exit reason: SPP
32 - exit reason: SPP
total EPT violation count: 32
unset SPP protection at gfn: 0x10001
expect NO VM exits caused by SPP below.
completed SPP test successfully!
------------------------------------------------------------------------


Yang Weijiang (1):
  kvm: selftests: add selftest for SPP feature

 tools/testing/selftests/kvm/Makefile          |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/x86_64/spp_test.c | 206 ++++++++++++++++++
 3 files changed, 208 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/spp_test.c
```
#### [PATCH v4 0/3] KVM: x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. If the instruction causes a delay, the amount
of time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay (the time to delay
relative to the VM’s timestamp counter). 

The release document ref below link:
Intel 64 and IA-32 Architectures Software Developer's Manual,
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf
This patch has a dependency on https://lkml.org/lkml/2019/6/7/1206

Changelog:
v4:
    Set msr of IA32_UMWAIT_CONTROL can be 0 and add the check of
    reserved bit 1 (Radim and Xiaoyao)
    Use umwait_control_cached directly and add the IA32_UMWAIT_CONTROL
    in msrs_to_save[] to support migration (Xiaoyao)
v3:
	Simplify the patches, expose user wait instructions when the
	guest has CPUID (Paolo)
	Use mwait_control_cached to avoid frequently rdmsr of
	IA32_UMWAIT_CONTROL (Paolo and Xiaoyao)
	Handle vm-exit for UMWAIT and TPAUSE as "never happen" (Paolo)
v2:
	Separated from the series https://lkml.org/lkml/2018/7/10/160
	Add provide a capability to enable UMONITOR, UMWAIT and TPAUSE 
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 +++-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h |  6 ++++
 arch/x86/kvm/vmx/vmx.c          | 53 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              |  1 +
 arch/x86/power/umwait.c         |  3 +-
 8 files changed, 72 insertions(+), 3 deletions(-)
```
#### [QEMU PATCH v4 0/10]: target/i386: kvm: Add support for save and
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to add support for QEMU to be able to migrate VMs that
are running nested hypervisors. In order to do so, it utilizes the new
IOCTLs introduced in KVM commit 8fcc4b5923af ("kvm: nVMX: Introduce
KVM_CAP_NESTED_STATE") which was created for this purpose.

1st patch add a missed cleanup for deleting VMX migration blocker in
case vCPU init fails.

2st patch introduce kvm_arch_destroy_vcpu() to perform per-vCPU
destruction logic that is arch-dependent.

3st patch is just refactoring to use symbolic constants instead of hard-coded
numbers.

4st patch fixes QEMU to update DR6 when QEMU re-inject #DB to guest after
it was intercepted by KVM when guest is debugged.

5th patch adds migration blocker for vCPU exposed with either Intel VMX
or AMD SVM. Until now it was blocked only for Intel VMX.

6rd patch updates linux-headers to have updated struct kvm_nested_state.
The updated struct now have explicit fields for the data portion.

7rd patch add vmstate support for saving/restoring kernel integer types (e.g. __u16).

8th patch adds support for saving and restoring nested state in order to migrate
guests which run a nested hypervisor.

9th patch add support for KVM_CAP_EXCEPTION_PAYLOAD. This new KVM capability
allows userspace to properly distingiush between pending and injecting exceptions.

10th patch changes the nested virtualization migration blocker to only
be added when kernel lack support for one of the capabilities required
for correct nested migration. i.e. Either KVM_CAP_NESTED_STATE or
KVM_CAP_EXCEPTION_PAYLOAD.

Regards,
-Liran

v1->v2 changes:
* Add patch to fix bug when re-inject #DB to guest.
* Add support for KVM_CAP_EXCEPTION_PAYLOAD.
* Use explicit fields for struct kvm_nested_state data portion.
* Use vmstate subsections to save/restore nested state in order to properly
* support forward & backwards migration compatability.
* Remove VMX migration blocker.

v2->v3 changes:
* Add kvm_arch_destroy_vcpu().
* Use DR6_BS where appropriate.
* Add cpu_pre_save() logic to convert pending exception to injected
  exception if guest is running L2.
* Converted max_nested_state_len to int instead of uint32_t.
* Use kvm_arch_destroy_vcpu() to free nested_state.
* Add migration blocker for vCPU exposed with AMD SVM.
* Don't rely on CR4 or MSR_EFER to know if it is required to
migrate new VMState subsections.
* Signal if vCPU is in guest-mode in hflags as original intention by Paolo.

v3->v4 changes:
* Add delete of nested migration blocker in case vCPU init fail.
* Change detection of VMX/SVM to not consider CPU vendor.
* Modify linux-headers to not have SVM stubs and use constant for vmcs12 size.
* Wrapped definition of kernel integer vmstate macros with #ifdef CONFIG_LINUX.
* Add migration blocker in case vCPU is exposed with VMX/SVM and kernel
  is lacking one of the KVM caps required to migrate nested workloads.
```
#### [PATCH v1 0/6] mm / virtio: Provide support for paravirtual waste
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This series provides an asynchronous means of hinting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as waste page treatment.

I have based many of the terms and functionality off of waste water
treatment, the idea for the similarity occurred to me after I had reached
the point of referring to the hints as "bubbles", as the hints used the
same approach as the balloon functionality but would disappear if they
were touched, as a result I started to think of the virtio device as an
aerator. The general idea with all of this is that the guest should be
treating the unused pages so that when they end up heading "downstream"
to either another guest, or back at the host they will not need to be
written to swap.

When the number of "dirty" pages in a given free_area exceeds our high
water mark, which is currently 32, we will schedule the aeration task to
start going through and scrubbing the zone. While the scrubbing is taking
place a boundary will be defined that we use to seperate the "aerated"
pages from the "dirty" ones. We use the ZONE_AERATION_ACTIVE bit to flag
when these boundaries are in place.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what batch size it wants to allocate to process the hints.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 32g in the guest and watching the total free
memory via /proc/meminfo on the host. With this I have verified most of
the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. With that I have seen a less than 1% difference between the
base kernel without these patches, with the patches and virtio-balloon
disabled, and with the patches and virtio-balloon enabled with hinting.

Changes from the RFC:
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.
Restructured the patch set to reduce patches from 11 to 6.
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce "aerated" pages
      mm: Add logic for separating "aerated" pages from "raw" pages
      virtio-balloon: Add support for aerating memory via hinting


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |  110 ++++++++++++++
 include/linux/memory_aeration.h     |  118 +++++++++++++++
 include/linux/mmzone.h              |  113 +++++++++------
 include/linux/page-flags.h          |    8 +
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/aeration.c                       |  270 +++++++++++++++++++++++++++++++++++
 mm/page_alloc.c                     |  203 ++++++++++++++++++--------
 mm/shuffle.c                        |   24 ---
 mm/shuffle.h                        |   35 +++++
 12 files changed, 753 insertions(+), 136 deletions(-)
 create mode 100644 include/linux/memory_aeration.h
 create mode 100644 mm/aeration.c

--
```
