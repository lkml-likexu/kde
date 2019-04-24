

#### [PATCH v16 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c

In the ARMv8 platform, the CPU error type are synchronous external
abort(SEA) and SError Interrupt (SEI). If exception happens to guest,
sometimes guest itself do the recovery is better, because host 
does not know guest's detailed information. For example, if a guest
user-space application happen exception, host does not which application
encounter errors.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify user
space. After user space gets  the notification, it will record the CPER
to guest GHES buffer for guest and inject a exception or IRQ to guest.

In the current implement, if the SIGBUS is BUS_MCEERR_AR, we will
treat it as synchronous exception, and use ARMv8 SEA notification type
to notify guest after recording CPER for guest;

This series patches are based on Qemu 4.0, which have two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill into guest memory,
   then according to SIGBUS type to notify guest.

Whole solution was suggested by James(james.morse@arm.com); APEI part solution is suggested by
Laszlo(lersek@redhat.com). Shown some discussion in [1].


This series patches have already tested on ARM64 platform with RAS feature enabled:
Show the APEI part verification result in [2]
Show the BUS_MCEERR_AR SIGBUS handling verification result in [3]
---
Change since v15:
1. Add a doc-comment in the proper format for 'include/exec/ram_addr.h'
2. Remove write_part_cpustate_to_list() because there is another bug fix patch
   has been merged "arm: Allow system registers for KVM guests to be changed by QEMU code"
3. Add some comments for kvm_inject_arm_sea() in 'target/arm/kvm64.c'
4. Compare the arm_current_el() return value to 0,1,2,3, not to PSTATE_MODE_* constants.
5. Change the RAS support wasn't introduced before 4.1 QEMU version.
6. Move the no_ras flag  patch to begin in this series

Change since v14:
1. Remove the BUS_MCEERR_AO handling logic because this asynchronous signal was masked by main thread 
2. Address some Igor Mammedov's comments(ACPI part)
   1) change the comments for the enum AcpiHestNotifyType definition and remove ditto in patch 1
   2) change some patch commit messages and separate "APEI GHES table generation" patch to more patches.
3. Address some peter's comments(arm64 Synchronous External Abort injection)
   1) change some code notes
   2) using arm_current_el() for current EL
   2) use the helper functions for those (syn_data_abort_*).

Change since v13:
1. Move the patches that set guest ESR and inject virtual SError out of this series
2. Clean and optimize the APEI part patches 
3. Update the commit messages and add some comments for the code

Change since v12:
1. Address Paolo's comments to move HWPoisonPage definition to accel/kvm/kvm-all.c
2. Only call kvm_cpu_synchronize_state() when get the BUS_MCEERR_AR signal
3. Only add and enable GPIO-Signal and ARMv8 SEA two hardware error sources
4. Address Michael's comments to not sync SPDX from Linux kernel header file 

Change since v11:
Address James's comments(james.morse@arm.com)
1. Check whether KVM has the capability to to set ESR instead of detecting host CPU RAS capability
2. For SIGBUS_MCEERR_AR SIGBUS, use Synchronous-External-Abort(SEA) notification type
   for SIGBUS_MCEERR_AO SIGBUS, use GPIO-Signal notification


Address Shannon's comments(for ACPI part):
1. Unify hest_ghes.c and hest_ghes.h license declaration
2. Remove unnecessary including "qmp-commands.h" in hest_ghes.c
3. Unconditionally add guest APEI table based on James's comments(james.morse@arm.com) 
4. Add a option to virt machine for migration compatibility. On new virt machine it's on
   by default while off for old ones, we enabled it since 2.12
5. Refer to the ACPI spec version which introduces Hardware Error Notification first time
6. Add ACPI_HEST_NOTIFY_RESERVED notification type

Address Igor's comments(for ACPI part):
1. Add doc patch first which will describe how it's supposed to work between QEMU/firmware/guest
   OS with expected flows.
2. Move APEI diagrams into doc/spec patch
3. Remove redundant g_malloc in ghes_record_cper()
4. Use build_append_int_noprefix() API to compose whole error status block and whole APEI table, 
   and try to get rid of most structures in patch 1, as they will be left unused after that
5. Reuse something like https://github.com/imammedo/qemu/commit/3d2fd6d13a3ea298d2ee814835495ce6241d085c
   to build GAS
6. Remove much offsetof() in the function
7. Build independent tables first and only then build dependent tables passing to it pointers
   to previously build table if necessary.
8. Redefine macro GHES_ACPI_HEST_NOTIFY_RESERVED to ACPI_HEST_ERROR_SOURCE_COUNT to avoid confusion


Address Peter Maydell's comments
1. linux-headers is done as a patch of their own created using scripts/update-linux-headers.sh run against a
   mainline kernel tree 
2. Tested whether this patchset builds OK on aarch32  
3. Abstract Hwpoison page adding code  out properly into a cpu-independent source file from target/i386/kvm.c,
   such as kvm-all.c
4. Add doc-comment formatted documentation comment for new globally-visible function prototype in a header

---
[1]:
https://lkml.org/lkml/2017/2/27/246
https://patchwork.kernel.org/patch/9633105/
https://patchwork.kernel.org/patch/9925227/

[2]:
Note: the UEFI(QEMU_EFI.fd) is needed if guest want to use ACPI table.

After guest boot up, dump the APEI table, then can see the initialized table
(1) # iasl -p ./HEST -d /sys/firmware/acpi/tables/HEST
(2) # cat HEST.dsl
    /*
     * Intel ACPI Component Architecture
     * AML/ASL+ Disassembler version 20170728 (64-bit version)
     * Copyright (c) 2000 - 2017 Intel Corporation
     *
     * Disassembly of /sys/firmware/acpi/tables/HEST, Mon Sep  5 07:59:17 2016
     *
     * ACPI Data Table [HEST]
     *
     * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
     */

    ..................................................................................
    [308h 0776   2]                Subtable Type : 000A [Generic Hardware Error Source V2]
    [30Ah 0778   2]                    Source Id : 0001
    [30Ch 0780   2]            Related Source Id : FFFF
    [30Eh 0782   1]                     Reserved : 00
    [30Fh 0783   1]                      Enabled : 01
    [310h 0784   4]       Records To Preallocate : 00000001
    [314h 0788   4]      Max Sections Per Record : 00000001
    [318h 0792   4]          Max Raw Data Length : 00001000

    [31Ch 0796  12]         Error Status Address : [Generic Address Structure]
    [31Ch 0796   1]                     Space ID : 00 [SystemMemory]
    [31Dh 0797   1]                    Bit Width : 40
    [31Eh 0798   1]                   Bit Offset : 00
    [31Fh 0799   1]         Encoded Access Width : 04 [QWord Access:64]
    [320h 0800   8]                      Address : 00000000785D0040

    [328h 0808  28]                       Notify : [Hardware Error Notification Structure]
    [328h 0808   1]                  Notify Type : 08 [SEA]
    [329h 0809   1]                Notify Length : 1C
    [32Ah 0810   2]   Configuration Write Enable : 0000
    [32Ch 0812   4]                 PollInterval : 00000000
    [330h 0816   4]                       Vector : 00000000
    [334h 0820   4]      Polling Threshold Value : 00000000
    [338h 0824   4]     Polling Threshold Window : 00000000
    [33Ch 0828   4]        Error Threshold Value : 00000000
    [340h 0832   4]       Error Threshold Window : 00000000

    [344h 0836   4]    Error Status Block Length : 00001000
    [348h 0840  12]            Read Ack Register : [Generic Address Structure]
    [348h 0840   1]                     Space ID : 00 [SystemMemory]
    [349h 0841   1]                    Bit Width : 40
    [34Ah 0842   1]                   Bit Offset : 00
    [34Bh 0843   1]         Encoded Access Width : 04 [QWord Access:64]
    [34Ch 0844   8]                      Address : 00000000785D0098

    [354h 0852   8]            Read Ack Preserve : 00000000FFFFFFFE
    [35Ch 0860   8]               Read Ack Write : 0000000000000001

    .....................................................................................

(3) After a synchronous external abort(SEA) happen, Qemu receive a SIGBUS and 
    filled the CPER into guest GHES memory.  For example, according to above table,
    the address that contains the physical address of a block of memory that holds
    the error status data for this abort is 0x00000000785D0040
(4) the address for SEA notification error source is 0x785d80b0
    (qemu) xp /1 0x00000000785D0040
    00000000785d0040: 0x785d80b0

(5) check the content of generic error status block and generic error data entry
    (qemu) xp /100x 0x785d80b0
    00000000785d80b0: 0x00000001 0x00000000 0x00000000 0x00000098
    00000000785d80c0: 0x00000000 0xa5bc1114 0x4ede6f64 0x833e63b8
    00000000785d80d0: 0xb1837ced 0x00000000 0x00000300 0x00000050
    00000000785d80e0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d80f0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d8100: 0x00000000 0x00000000 0x00000000 0x00004002
(6) check the OSPM's ACK value(for example SEA)
    /* Before OSPM acknowledges the error, check the ACK value */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000000

    /* After OSPM acknowledges the error, check the ACK value, it change to 1 from 0 */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000001

[3]: KVM deliver "BUS_MCEERR_AR" to Qemu, Qemu record the guest CPER and inject
    synchronous external abort to notify guest, then guest do the recovery.

[ 1552.516170] Synchronous External Abort: synchronous external abort (0x92000410) at 0x000000003751c6b4
[ 1553.074073] {1}[Hardware Error]: Hardware error from APEI Generic Hardware Error Source: 8
[ 1553.081654] {1}[Hardware Error]: event severity: recoverable
[ 1554.034191] {1}[Hardware Error]:  Error 0, type: recoverable
[ 1554.037934] {1}[Hardware Error]:   section_type: memory error
[ 1554.513261] {1}[Hardware Error]:   physical_address: 0x0000000040fa6000
[ 1554.513944] {1}[Hardware Error]:   error_type: 0, unknown
[ 1555.041451] Memory failure: 0x40fa6: Killing mca-recover:1296 due to hardware memory corruption
[ 1555.373116] Memory failure: 0x40fa6: recovery action for dirty LRU page: Recovered

Dongjiu Geng (10):
  hw/arm/virt: Add RAS platform version for migration
  ACPI: add some GHES structures and macros definition
  acpi: add build_append_ghes_notify() helper for Hardware Error
    Notification
  acpi: add build_append_ghes_generic_data() helper for Generic Error
    Data Entry
  acpi: add build_append_ghes_generic_status() helper for Generic Error
    Status Block
  docs: APEI GHES generation and CPER record description
  ACPI: Add APEI GHES table generation support
  KVM: Move related hwpoison page functions to accel/kvm/ folder
  target-arm: kvm64: inject synchronous External Abort
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM

 accel/kvm/kvm-all.c             |  33 ++++
 default-configs/arm-softmmu.mak |   1 +
 docs/specs/acpi_hest_ghes.txt   |  97 +++++++++++
 hw/acpi/Kconfig                 |   4 +
 hw/acpi/Makefile.objs           |   1 +
 hw/acpi/acpi_ghes.c             | 348 ++++++++++++++++++++++++++++++++++++++++
 hw/acpi/aml-build.c             |  70 ++++++++
 hw/arm/virt-acpi-build.c        |  12 ++
 hw/arm/virt.c                   |   6 +
 include/exec/ram_addr.h         |  24 +++
 include/hw/acpi/acpi-defs.h     |  52 ++++++
 include/hw/acpi/acpi_ghes.h     |  83 ++++++++++
 include/hw/acpi/aml-build.h     |  21 +++
 include/hw/arm/virt.h           |   1 +
 include/sysemu/kvm.h            |   2 +-
 target/arm/internals.h          |   5 +-
 target/arm/kvm.c                |   3 +
 target/arm/kvm64.c              |  74 +++++++++
 target/arm/op_helper.c          |   2 +-
 target/i386/kvm.c               |  34 +---
 20 files changed, 836 insertions(+), 37 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.txt
 create mode 100644 hw/acpi/acpi_ghes.c
 create mode 100644 include/hw/acpi/acpi_ghes.h
```
#### [RFC KVM 00/27] KVM Address Space Isolation
##### From: Alexandre Chartre <alexandre.chartre@oracle.com>

```c

Hi,

This series aims to introduce the concept of KVM address space isolation.
This is done as part of the upstream community effort to have exploit
mitigations for CPU info-leaks vulnerabilities such as L1TF. 

These patches are based on an original patches from Liran Alon, completed
with additional patches to effectively create KVM address space different
from the full kernel address space.

The current code is just an early POC, and it is not fully stable at the
moment (unfortunately you can expect crashes/hangs, see the "Issues"
section below). However I would like to start a discussion get feedback
and opinions about this approach.

Context
=======

The most naive approach to handle L1TF SMT-variant exploit is to just disable
hyper-threading. But that is not practical for public cloud providers. As a
second next best alternative, there is an approach to combine coscheduling
together with flushing L1D cache on every VMEntry. By coscheduling I refer
to some mechanism which on every VMExit from guest, kicks all sibling
hyperthreads from guest aswell.

However, this approach have some open issues:

1. Kicking all sibling hyperthreads for every VMExit have significant
   performance hit for some compute shapes (e.g. Emulated and PV).

2. It assumes only CPU core resource which could be leaked by some
   vulnerability is L1D cache. But future vulnerabilities may also be able
   to leak other CPU core resources. Therefore, we would prefer to have a
   mechanism which prevents these resources to be able to be loaded with
   sensitive data to begin with.

To better address (2), upstream community has discussed some mechanisms
related to reducing data that is mapped on kernel virtual address space.
Specifically:

a. XPFO: Removes from physmap pages that currently should only be accessed
   by userspace.

b. Process-local memory allocations: Allows having a memory area in kernel
   virtual address space that maps different content per-process. Then,
   allocations made on this memory area can be hidden from other tasks in
   the system running in kernel space. Most obvious use it to allocate
   there per-vCPU and per-VM KVM structures.

However, both (a)+(b) work in a black-list approach (where we decide which
data is considered dangerous and remove it from kernel virtual address
space) and don't address performance hit described at (1).


Proposal
========

To handle both these points, this series introduce the mechanism of KVM
address space isolation. Note that this mechanism completes (a)+(b) and
don't contradict. In case this mechanism is also applied, (a)+(b) should
still be applied to the full virtual address space as a defence-in-depth).

The idea is that most of KVM #VMExit handlers code will run in a special
KVM isolated address space which maps only KVM required code and per-VM
information. Only once KVM needs to architectually access other (sensitive)
data, it will switch from KVM isolated address space to full standard
host address space. At this point, KVM will also need to kick all sibling
hyperthreads to get out of guest (note that kicking all sibling hyperthreads
is not implemented in this serie).

Basically, we will have the following flow:

  - qemu issues KVM_RUN ioctl
  - KVM handles the ioctl and calls vcpu_run():
    . KVM switches from the kernel address to the KVM address space
    . KVM transfers control to VM (VMLAUNCH/VMRESUME)
    . VM returns to KVM
    . KVM handles VM-Exit:
      . if handling need full kernel then switch to kernel address space
      . else continues with KVM address space
    . KVM loops in vcpu_run() or return
  - KVM_RUN ioctl returns

So, the KVM_RUN core function will mainly be executed using the KVM address
space. The handling of a VM-Exit can require access to the kernel space
and, in that case, we will switch back to the kernel address space.

The high-level idea of how this is implemented is to create a separate
struct_mm for KVM such that a vCPU thread will switch active_mm between
it's original active_mm and kvm_mm when needed as described above. The
idea is very similar to how kernel switches between task active_mm and
efi_mm when calling EFI Runtime Services.

Note that because we use the kernel TLB Manager to switch between kvm_mm
and host_mm, we will effectively use TLB with PCID if enabled to make
these switches fast. As all of this is managed internally in TLB Manager's
switch_mm().


Patches
=======

The proposed patches implement the necessary framework for creating kvm_mm
and switching between host_mm and kvm_mm at appropriate times. They also
provide functions for populating the KVM address space, and implement an
actual KVM address space much smaller than the full kernel address space.

- 01-08: add framework for switching between the kernel address space and
  the KVM address space at appropriate times. Note that these patches do
  not create or switch the address space yet. Address space switching is
  implemented in patch 25.

- 09-18: add a framework for populating and managing the KVM page table;
  this also include mechanisms to ensure changes are effectively limited
  to the KVM page table and no change is mistakenly propagated to the
  kernel page table.

- 19-23: populate the KVM page table.

- 24: add page fault handler to handle and report missing mappings when
  running with the KVM address space. This is based on an original idea
  from Paul Turner.

- 25: implement the actual switch between the kernel address space and
  the KVM address space.

- 26-27: populate the KVM page table with more data.


If a fault occurs while running with the KVM address space, it will be
reported on the console like this:

[ 4840.727476] KVM isolation: page fault #0 (0) at fast_page_fault+0x13e/0x3e0 [kvm] on ffffea00005331f0 (0xffffea00005331f0)

If the KVM page_fault_stack module parameter is set to non-zero (that's
the default) then the stack of the fault will also be reported:

[ 5025.630374] KVM isolation: page fault #0 (0) at fast_page_fault+0x100/0x3e0 [kvm] on ffff88003c718000 (0xffff88003c718000)
[ 5025.631918] Call Trace:
[ 5025.632782]  tdp_page_fault+0xec/0x260 [kvm]
[ 5025.633395]  kvm_mmu_page_fault+0x74/0x5f0 [kvm]
[ 5025.644467]  handle_ept_violation+0xc3/0x1a0 [kvm_intel]
[ 5025.645218]  vmx_handle_exit+0xb9/0x600 [kvm_intel]
[ 5025.645917]  vcpu_enter_guest+0xb88/0x1580 [kvm]
[ 5025.646577]  kvm_arch_vcpu_ioctl_run+0x403/0x610 [kvm]
[ 5025.647313]  kvm_vcpu_ioctl+0x3d5/0x650 [kvm]
[ 5025.648538]  do_vfs_ioctl+0xaa/0x602
[ 5025.650502]  SyS_ioctl+0x79/0x84
[ 5025.650966]  do_syscall_64+0x79/0x1ae
[ 5025.651487]  entry_SYSCALL_64_after_hwframe+0x151/0x0
[ 5025.652200] RIP: 0033:0x7f74a2f1d997
[ 5025.652710] RSP: 002b:00007f749f3ec998 EFLAGS: 00000246 ORIG_RAX: 0000000000000010
[ 5025.653769] RAX: ffffffffffffffda RBX: 0000562caa83e110 RCX: 00007f74a2f1d997
[ 5025.654769] RDX: 0000000000000000 RSI: 000000000000ae80 RDI: 000000000000000c
[ 5025.655769] RBP: 0000562caa83e1b3 R08: 0000562ca9b6fa50 R09: 0000000000000006
[ 5025.656766] R10: 0000000000000000 R11: 0000000000000246 R12: 0000562ca9b552c0
[ 5025.657764] R13: 0000000000801000 R14: 00007f74a59d4000 R15: 0000562caa83e110

This allows to find out what is missing in the KVM address space.


Issues
======

Limited tests have been done so far, and mostly with an empty single-vcpu
VM (i.e. qemu-system-i386 -enable-kvm -smp 1). Single-vcpu VM is able to
start and run a full OS but the system will eventually crash/hang at some
point. Multiple vcpus will crash/hang much faster.


Performance Impact
==================

As this is a RFC, the effective performance impact hasn't been measured
yet. Current patches introduce two additional context switches (kernel to
KVM, and KVM to kernel) on each KVM_RUN ioctl. Also additional context
switches are added if a VM-Exit has to be handled using the full kernel
address space.

I expect that the KVM address space can eventually be expanded to include
the ioctl syscall entries. By doing so, and also adding the KVM page table
to the process userland page table (which should be safe to do because the
KVM address space doesn't have any secret), we could potentially handle the
KVM ioctl without having to switch to the kernel pagetable (thus effectively
eliminating KPTI for KVM). Then the only overhead would be if a VM-Exit has
to be handled using the full kernel address space.


Thanks,

alex.
---

Alexandre Chartre (18):
  kvm/isolation: function to track buffers allocated for the KVM page
    table
  kvm/isolation: add KVM page table entry free functions
  kvm/isolation: add KVM page table entry offset functions
  kvm/isolation: add KVM page table entry allocation functions
  kvm/isolation: add KVM page table entry set functions
  kvm/isolation: functions to copy page table entries for a VA range
  kvm/isolation: keep track of VA range mapped in KVM address space
  kvm/isolation: functions to clear page table entries for a VA range
  kvm/isolation: improve mapping copy when mapping is already present
  kvm/isolation: function to copy page table entries for percpu buffer
  kvm/isolation: initialize the KVM page table with core mappings
  kvm/isolation: initialize the KVM page table with vmx specific data
  kvm/isolation: initialize the KVM page table with vmx VM data
  kvm/isolation: initialize the KVM page table with vmx cpu data
  kvm/isolation: initialize the KVM page table with the vcpu tasks
  kvm/isolation: KVM page fault handler
  kvm/isolation: initialize the KVM page table with KVM memslots
  kvm/isolation: initialize the KVM page table with KVM buses

Liran Alon (9):
  kernel: Export memory-management symbols required for KVM address
    space isolation
  KVM: x86: Introduce address_space_isolation module parameter
  KVM: x86: Introduce KVM separate virtual address space
  KVM: x86: Switch to KVM address space on entry to guest
  KVM: x86: Add handler to exit kvm isolation
  KVM: x86: Exit KVM isolation on IRQ entry
  KVM: x86: Switch to host address space when may access sensitive data
  KVM: x86: Optimize branches which checks if address space isolation
    enabled
  kvm/isolation: implement actual KVM isolation enter/exit

 arch/x86/include/asm/apic.h    |    4 +-
 arch/x86/include/asm/hardirq.h |   10 +
 arch/x86/include/asm/irq.h     |    1 +
 arch/x86/kernel/cpu/common.c   |    2 +
 arch/x86/kernel/dumpstack.c    |    1 +
 arch/x86/kernel/irq.c          |   11 +
 arch/x86/kernel/ldt.c          |    1 +
 arch/x86/kernel/smp.c          |    2 +-
 arch/x86/kvm/Makefile          |    2 +-
 arch/x86/kvm/isolation.c       | 1773 ++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/isolation.h       |   40 +
 arch/x86/kvm/mmu.c             |    3 +-
 arch/x86/kvm/vmx/vmx.c         |  123 +++-
 arch/x86/kvm/x86.c             |   44 +-
 arch/x86/mm/fault.c            |   12 +
 arch/x86/mm/tlb.c              |    4 +-
 arch/x86/platform/uv/tlb_uv.c  |    2 +-
 include/linux/kvm_host.h       |    2 +
 include/linux/percpu.h         |    2 +
 include/linux/sched.h          |    6 +
 mm/memory.c                    |    5 +
 mm/percpu.c                    |    6 +-
 virt/kvm/arm/arm.c             |    4 +
 virt/kvm/kvm_main.c            |    4 +-
 24 files changed, 2051 insertions(+), 13 deletions(-)
 create mode 100644 arch/x86/kvm/isolation.c
 create mode 100644 arch/x86/kvm/isolation.h
```
