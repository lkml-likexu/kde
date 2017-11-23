

#### [PATCH v8 0/7] KVM: x86: Allow Qemu/KVM to use PVH entry point
##### From: Maran Wilson <maran.wilson@oracle.com>

```c

For certain applications it is desirable to rapidly boot a KVM virtual
machine. In cases where legacy hardware and software support within the
guest is not needed, Qemu should be able to boot directly into the
uncompressed Linux kernel binary without the need to run firmware.

There already exists an ABI to allow this for Xen PVH guests and the ABI
is supported by Linux and FreeBSD:

   https://xenbits.xen.org/docs/unstable/misc/pvh.html

This patch series would enable Qemu to use that same entry point for
booting KVM guests.

Changes from v7:

 (No functional changes from v7 other than rebasing to latest upstream) 
 * Added Review-by tags as provided by Juergen Gross (1,2,3,6,7)
 * Rebasing to upstream 4.18 caused a minor conflict in patch 4 that had
   to be hand merged due to this patch:
      1fe8388 xen: share start flags between PV and PVH
   I just had to make sure we were accounting for the xen_start_flags
   in the new code path.
 * Rebasing to upstream 4.20-rc4 caused a few minor conflicts in patches
   2,3,5,7 that needed to be resolved by hand. The conflicts were due to
   upstream non-functional code cleanup changes in arch/x86/xen/Makefile
   and arch/x86/platform/pvh/enlighten.c due to these patches:
      28c11b0 x86/xen: Move pv irq related functions under CONFIG_XEN_PV
              umbrella
      357d291 x86/xen: Fix boot loader version reported for PVH guests
      3cfa210 xen: don't include <xen/xen.h> from <asm/io.h> and
              <asm/dma-mapping.h>
 * Qemu and qboot RFC patches have been posted to show one example of how
   this functionality can be used. Some preliminary numbers are available
   in those cover letters showing the KVM guest boot time improvement.
      Qemu:
      http://lists.nongnu.org/archive/html/qemu-devel/2018-12/msg00957.html
      qboot:
      http://lists.nongnu.org/archive/html/qemu-devel/2018-12/msg00953.html

Changes from v6:

 * Addressed issues caught by the kbuild test robot:
    - Restored an #include line that had been dropped by mistake (patch 4)
    - Removed a pair of #include lines that were no longer needed in a
      common code file and causing problems for certain 32-bit configs
      (patchs 4 and 7)

Changes from v5:

 * The interface changes to the x86/HVM start info layout have
   now been accepted into the Xen tree.
 * Rebase and merge upstream PVH file changes.
 * (Patch 6) Synced up to the final version of the header file that was
             acked and pulled into the Xen tree.
 * (Patch 1) Fixed typo and removed redundant "def_bool n" line.

Changes from v4:

Note: I've withheld Juergen's earlier "Reviewed-by" tags from patches
1 and 7 since there were minor changes (mostly just addition of
CONFIG_KVM_GUEST_PVH as requested) that came afterwards.

 * Changed subject prefix from RFC to PATCH
 * Added CONFIG_KVM_GUEST_PVH as suggested
 * Relocated the PVH common files to
   arch/x86/platform/pvh/{enlighten.c,head.S}
 * Realized I also needed to move the objtool override for those files
 * Updated a few code comments per reviewer feedback
 * Sent out a patch of the hvm_start_info struct changes against the Xen
   tree since that is the canonical copy of the header. Discussions on
   that thread have resulted in some (non-functional) updates to
   start_info.h (patch 6/7) and those changes are reflected here as well
   in order to keep the files in sync. The header file has since been
   ack'ed for the Xen tree by Jan Beulich.

Changes from v3:

 * Implemented Juergen's suggestion for refactoring and moving the PVH
   code so that CONFIG_XEN is no longer required for booting KVM guests
   via the PVH entry point.
   Functionally, nothing has changed from V3 really, but the patches
   look completely different now because of all the code movement and
   refactoring. Some of these patches can be combined, but I've left
   them very small in some cases to make the refactoring and code
   movement easier to review.
   My approach for refactoring has been to create a PVH entry layer that
   still has understanding and knowledge about Xen vs non-Xen guest types
   so that it can make run time decisions to handle either case, as
   opposed to going all the way and re-writing it to be a completely
   hypervisor agnostic and architecturally pure layer that is separate
   from guest type details. The latter seemed a bit overkill in this
   situation. And I've handled the complexity of having to support
   Qemu/KVM boot of kernels compiled with or without CONFIG_XEN via a
   pair of xen specific __weak routines that can be overridden in kernels
   that support Xen guests. Importantly, the __weak routines are for
   xen specific code only (not generic "guest type" specific code) so
   there is no clashing between xen version of the strong routine and,
   say, a KVM version of the same routine. But I'm sure there are many
   ways to skin this cat, so I'm open to alternate suggestions if there
   is a compelling reason for not using __weak in this situation.

Changes from v2:

 * All structures (including memory map table entries) are padded and
   aligned to an 8 byte boundary.

 * Removed the "packed" attributes and made changes to comments as
   suggested by Jan.

Changes from v1:

 * Adopted Paolo's suggestion for defining a v2 PVH ABI that includes the
   e820 map instead of using the second module entry to pass the table.

 * Cleaned things up a bit to reduce the number of xen vs non-xen special
   cases.


Maran Wilson (7):
  xen/pvh: Split CONFIG_XEN_PVH into CONFIG_PVH and CONFIG_XEN_PVH
  xen/pvh: Move PVH entry code out of Xen specific tree
  xen/pvh: Create a new file for Xen specific PVH code
  xen/pvh: Move Xen specific PVH VM initialization out of common file
  xen/pvh: Move Xen code for getting mem map via hcall out of common
    file
  xen/pvh: Add memory map pointer to hvm_start_info struct
  KVM: x86: Allow Qemu/KVM to use PVH entry point

 MAINTAINERS                                     |   1 +
 arch/x86/Kbuild                                 |   2 +
 arch/x86/Kconfig                                |  14 +++
 arch/x86/kernel/head_64.S                       |   2 +-
 arch/x86/platform/pvh/Makefile                  |   5 +
 arch/x86/platform/pvh/enlighten.c               | 137 ++++++++++++++++++++++++
 arch/x86/{xen/xen-pvh.S => platform/pvh/head.S} |   0
 arch/x86/xen/Kconfig                            |   3 +-
 arch/x86/xen/Makefile                           |   2 -
 arch/x86/xen/enlighten_pvh.c                    |  94 ++++------------
 include/xen/interface/hvm/start_info.h          |  63 ++++++++++-
 include/xen/xen.h                               |   3 +
 12 files changed, 245 insertions(+), 81 deletions(-)
 create mode 100644 arch/x86/platform/pvh/Makefile
 create mode 100644 arch/x86/platform/pvh/enlighten.c
 rename arch/x86/{xen/xen-pvh.S => platform/pvh/head.S} (100%)
```
#### [Resend PATCH V5 0/10] x86/KVM/Hyper-v: Add HV ept tlb range flush
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

```c

From: Lan Tianyu <Tianyu.Lan@microsoft.com>

For nested memory virtualization, Hyper-v doesn't set write-protect
L1 hypervisor EPT page directory and page table node to track changes 
while it relies on guest to tell it changes via HvFlushGuestAddressLlist
hypercall. HvFlushGuestAddressLlist hypercall provides a way to flush
EPT page table with ranges which are specified by L1 hypervisor.

If L1 hypervisor uses INVEPT or HvFlushGuestAddressSpace hypercall to
flush EPT tlb, Hyper-V will invalidate associated EPT shadow page table
and sync L1's EPT table when next EPT page fault is triggered.
HvFlushGuestAddressLlist hypercall helps to avoid such redundant EPT
page fault and synchronization of shadow page table.

This patchset is based on the Patch "KVM/VMX: Check ept_pointer before
flushing ept tlb"(https://marc.info/?l=kvm&m=154408169705686&w=2).

Change since v4:
       1) Split flush address and flush list patches. This patchset only contains
       flush address patches. Will post flush list patches later.
       2) Expose function hyperv_fill_flush_guest_mapping_list()
       out of hyperv file
       3) Adjust parameter of hyperv_flush_guest_mapping_range()
       4) Reorder patchset and move Hyper-V and VMX changes ahead.

Change since v3:
        1) Remove code of updating "tlbs_dirty" in kvm_flush_remote_tlbs_with_range()
        2) Remove directly tlb flush in the kvm_handle_hva_range()
        3) Move tlb flush in kvm_set_pte_rmapp() to kvm_mmu_notifier_change_pte()
        4) Combine Vitaly's "don't pass EPT configuration info to
vmx_hv_remote_flush_tlb()" fix

Change since v2:
       1) Fix comment in the kvm_flush_remote_tlbs_with_range()
       2) Move HV_MAX_FLUSH_PAGES and HV_MAX_FLUSH_REP_COUNT to
        hyperv-tlfs.h.
       3) Calculate HV_MAX_FLUSH_REP_COUNT in the macro definition
       4) Use HV_MAX_FLUSH_REP_COUNT to define length of gpa_list in
        struct hv_guest_mapping_flush_list.

Change since v1:
       1) Convert "end_gfn" of struct kvm_tlb_range to "pages" in order
          to avoid confusion as to whether "end_gfn" is inclusive or exlusive.
       2) Add hyperv tlb range struct and replace kvm tlb range struct
          with new struct in order to avoid using kvm struct in the hyperv
          code directly.



Lan Tianyu (10):
  KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
  x86/hyper-v: Add HvFlushGuestAddressList hypercall support
  x86/Hyper-v: Add trace in the
    hyperv_nested_flush_guest_mapping_range()
  KVM/VMX: Add hv tlb range flush support
  KVM/MMU: Add tlb flush with range helper function
  KVM: Replace old tlb flush function with new one to flush a specified
    range.
  KVM: Make kvm_set_spte_hva() return int
  KVM/MMU: Move tlb flush in kvm_set_pte_rmapp() to
    kvm_mmu_notifier_change_pte()
  KVM/MMU: Flush tlb directly in the kvm_set_pte_rmapp()
  KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()

 arch/arm/include/asm/kvm_host.h     |  2 +-
 arch/arm64/include/asm/kvm_host.h   |  2 +-
 arch/mips/include/asm/kvm_host.h    |  2 +-
 arch/mips/kvm/mmu.c                 |  3 +-
 arch/powerpc/include/asm/kvm_host.h |  2 +-
 arch/powerpc/kvm/book3s.c           |  3 +-
 arch/powerpc/kvm/e500_mmu_host.c    |  3 +-
 arch/x86/hyperv/nested.c            | 80 +++++++++++++++++++++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h  | 32 +++++++++++++
 arch/x86/include/asm/kvm_host.h     |  9 +++-
 arch/x86/include/asm/mshyperv.h     | 15 ++++++
 arch/x86/include/asm/trace/hyperv.h | 14 ++++++
 arch/x86/kvm/mmu.c                  | 96 +++++++++++++++++++++++++++++--------
 arch/x86/kvm/paging_tmpl.h          |  3 +-
 arch/x86/kvm/vmx.c                  | 63 +++++++++++++++++-------
 virt/kvm/arm/mmu.c                  |  6 ++-
 virt/kvm/kvm_main.c                 |  5 +-
 17 files changed, 292 insertions(+), 48 deletions(-)
```
#### [PATCH 0/6] x86/kvm/hyper-v: Implement KVM_GET_SUPPORTED_HV_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

As suggested by Paolo, introduce new KVM_GET_SUPPORTED_HV_CPUID returning
all Hyper-V CPUID feature leaves, this way we won't need to add a new
KVM_CAP_HYPERV_* for every new Hyper-V enlightenment we implement in
KVM.

(Using the existing KVM_GET_SUPPORTED_CPUID doesn't seem to be possible:
Hyper-V CPUID feature leaves intersect with KVM's (e.g. 0x40000000,
0x40000001) and we would probably confuse userspace in case we decide to
return these twice).

This patch series also does some housekeeping work in hyperv-tlfs.h, adds a
simple selftest (that's how I actually checked that the newly added ioctl
works) and removes recently added KVM_CAP_HYPERV_STIMER_DIRECT before it's
too late.

Vitaly Kuznetsov (6):
  x86/hyper-v: Do some housekeeping in hyperv-tlfs.h
  x86/hyper-v: Drop HV_X64_CONFIGURE_PROFILER definition
  x86/kvm/hyper-v: Introduce nested_get_evmcs_version() helper
  x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID
  x86/kvm/hyper-v: Drop KVM_CAP_HYPERV_STIMER_DIRECT
  KVM: selftests: Add hyperv_cpuid test

 arch/x86/include/asm/hyperv-tlfs.h            | 185 +++++++++---------
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/kvm/hyperv.c                         | 131 ++++++++++++-
 arch/x86/kvm/hyperv.h                         |   2 +
 arch/x86/kvm/svm.c                            |   7 +
 arch/x86/kvm/vmx.c                            |  24 ++-
 arch/x86/kvm/x86.c                            |  21 +-
 include/uapi/linux/kvm.h                      |   5 +-
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 142 ++++++++++++++
 10 files changed, 413 insertions(+), 106 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c
```
#### [PATCH v3 0/8] Workaround for Cortex-A76 erratum 1165522
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

Early Cortex-A76 suffer from an erratum that can result in invalid
TLBs when the CPU speculatively executes an AT instruction in the
middle of a guest world switch, while the guest virtual memory
configuration is in an inconsistent state.

We handle this issue by mandating the use of VHE and making sure that
the guest context is fully installed before switching HCR_EL2.TGE to
zero. This ensures that a speculated AT instruction is either executed
on the host context (TGE set) or the guest context (TGE clear), and
that there is no intermediate state.

There is some additional complexity in the TLB invalidation code,
where we most make sure that a speculated AT instruction cannot mess
the stage-1 TLBs.

* From v2:
  - Dropped a bunch of spurious ISBs after James review
  - Added James RBs.

* From v1:
  - VHE TLB invalidation now atomic
  - Avoid speculated AT during TLB invalidation
  - Addressed most comments from Christoffer
  - Resplit to ease reviewing

Marc Zyngier (8):
  arm64: KVM: Make VHE Stage-2 TLB invalidation operations
    non-interruptible
  KVM: arm64: Rework detection of SVE, !VHE systems
  arm64: KVM: Install stage-2 translation before enabling traps
  arm64: Add TCR_EPD{0,1} definitions
  arm64: KVM: Force VHE for systems affected by erratum 1165522
  arm64: KVM: Add synchronization on translation regime change for
    erratum 1165522
  arm64: KVM: Handle ARM erratum 1165522 in TLB invalidation
  arm64: Add configuration/documentation for Cortex-A76 erratum 1165522

 Documentation/arm64/silicon-errata.txt |  1 +
 arch/arm/include/asm/kvm_host.h        |  2 +-
 arch/arm64/Kconfig                     | 12 +++++
 arch/arm64/include/asm/cpucaps.h       |  3 +-
 arch/arm64/include/asm/kvm_host.h      | 10 ++--
 arch/arm64/include/asm/kvm_hyp.h       |  8 +++
 arch/arm64/include/asm/pgtable-hwdef.h |  4 ++
 arch/arm64/kernel/cpu_errata.c         |  8 +++
 arch/arm64/kvm/hyp/switch.c            | 23 ++++++++-
 arch/arm64/kvm/hyp/tlb.c               | 71 ++++++++++++++++++++++----
 virt/kvm/arm/arm.c                     |  8 +--
 11 files changed, 129 insertions(+), 21 deletions(-)
Reviewed-by: James Morse <james.morse@arm.com>
```
#### [PATCH v2 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c

Changelog

    RFC -> v1
        - set distro_id to 0 for now and will be introduced properly as a follow-on
            patch with further details wrt its usage
        - created diag318 union structure to contain CPC data in kvm
        - removed VCPU_EVENT from diag318 handler (we still see a VM_EVENT)

     v1 -> v2
        - set_cpc now uses kvm_block_all
        - s/VM_MISC/VM_MACHINE
        - SCB shadowing / unshadowing of cpnc
        - added r-b's to patch 1

A new diagnose instruction, 318, allows the kernel to set an 8-byte "Control 
Program Code" (CPC) that is composed of:

    1-byte Control Program Name Code (CPNC)
    7-byte Control Program Version Code (CPVC) composed of:
        3-bytes for Linux Kernel version (determined at build-time)
        3-bytes for *Distribution Identifier (currently set to 0)
        1-byte trailing NULL

*The distribution identifier will be introduced as a follow-on patch.

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read SCP Info byte 134, bit 0.
Diagnose318's functionality is also emulated by KVM, which means we can 
enable this feature for a guest even if the host kernel cannot support it.

The CPNC and CPVC are used for problem diagnosis and allows IBM to identify 
control program information by answering the following questions:

    "What environment is this guest running in?" (CPNC)
    "What linux version is this guest running?" (CPVC)

Collin Walling (2):
  s390/setup: set control program code via diag 318
  s390/kvm: handle diagnose 318 instruction call

 arch/s390/include/asm/diag.h     | 12 ++++++
 arch/s390/include/asm/kvm_host.h | 13 +++++-
 arch/s390/include/asm/sclp.h     |  1 +
 arch/s390/include/uapi/asm/kvm.h |  5 +++
 arch/s390/kernel/diag.c          |  1 +
 arch/s390/kernel/setup.c         | 21 +++++++++
 arch/s390/kvm/diag.c             | 12 ++++++
 arch/s390/kvm/kvm-s390.c         | 92 ++++++++++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h         |  1 +
 arch/s390/kvm/vsie.c             |  7 +++
 drivers/s390/char/sclp.h         |  4 +-
 drivers/s390/char/sclp_early.c   |  2 +
 12 files changed, 169 insertions(+), 2 deletions(-)
```
