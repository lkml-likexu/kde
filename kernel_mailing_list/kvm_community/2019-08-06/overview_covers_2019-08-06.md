

#### [PATCH v2 0/5] x86: KVM: svm: get rid of hardcoded instructions
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v1:
- Clear interrupt shadow in x86_emulate_instruction() instead of SVM's
  skip_emulated_instruction() to generalize the fix [Sean Christopherson]

Original description:

Jim rightfully complains that hardcoding instuctions lengths is not always
correct: additional (redundant) prefixes can be used. Luckily, the ugliness
is mostly harmless: modern AMD CPUs support NRIP_SAVE feature but I'd like
to clean things up and sacrifice speed in favor of correctness.

Vitaly Kuznetsov (5):
  x86: KVM: svm: don't pretend to advance RIP in case
    wrmsr_interception() results in #GP
  x86: KVM: svm: avoid flooding logs when skip_emulated_instruction()
    fails
  x86: KVM: clear interrupt shadow on EMULTYPE_SKIP
  x86: KVM: add xsetbv to the emulator
  x86: KVM: svm: remove hardcoded instruction length from intercepts

 arch/x86/include/asm/kvm_emulate.h |  3 ++-
 arch/x86/kvm/emulate.c             | 23 ++++++++++++++++++++++-
 arch/x86/kvm/svm.c                 | 19 +++++--------------
 arch/x86/kvm/x86.c                 |  7 +++++++
 4 files changed, 36 insertions(+), 16 deletions(-)
```
#### [PATCH v8 00/14] Guest LBR Enabling
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Last Branch Recording (LBR) is a performance monitor unit (PMU) feature
on Intel CPUs that captures branch related info. This patch series enables
this feature to KVM guests.

Each guest can be configured to expose this LBR feature to the guest via
userspace setting the enabling param in KVM_CAP_X86_GUEST_LBR (patch 3).

About the lbr emulation method:
Since the vcpu get scheduled in, the lbr related msrs are made
interceptible. This makes guest first access to a lbr related msr always
vm-exit to kvm, so that kvm can know whether the lbr feature is used
during the vcpu time slice. The kvm lbr msr handler does the following
things:
  - create an lbr perf event (task pinned) for the vcpu thread.
    The perf event mainly serves 2 purposes:
      -- follow the host perf scheduling rules to manage the vcpu's usage
         of lbr (e.g. a cpu pinned lbr event could reclaim lbr and thus
         stopping the vcpu's use);
      -- have the host perf do context switching of the lbr state on the
         vcpu thread switching.
  - pass the lbr related msrs through to the guest.
    This enables the following guest accesses to the lbr related msrs
    without vm-exit, as long as the vcpu's lbr event owns the lbr feature.
    A cpu pinned lbr event on the host could come and take over the lbr
    feature via IPI calls. In this case, the pass-through will be
    cancelled (patch 13), and the guest following accesses to the lbr msrs
    will vm-exit to kvm and accesses will be forbidden in the handler.

If the guest doesn't touch any of the lbr related msrs (likely the guest
doesn't need to run lbr in the near future), the vcpu's lbr perf event
will be freed (please see patch 12 commit for more details).

* Tests
Conclusion: the profiling results on the guest are similar to that on the host.

Run: ./perf -b ./test_program

- Test on the host:
Overhead  Command  Source Shared Object  Source Symbol    Target Symbol   
  22.35%  ftest    libc-2.23.so          [.] __random     [.] __random        
   8.20%  ftest    ftest                 [.] qux          [.] qux             
   5.88%  ftest    ftest                 [.] random@plt   [.] __random        
   5.88%  ftest    libc-2.23.so          [.] __random     [.] __random_r  
   5.79%  ftest    ftest                 [.] main         [.] random@plt  
   5.60%  ftest    ftest                 [.] main         [.] foo             
   5.24%  ftest    libc-2.23.so          [.] __random     [.] main            
   5.20%  ftest    libc-2.23.so          [.] __random_r   [.] __random        
   5.00%  ftest    ftest                 [.] foo          [.] qux             
   4.91%  ftest    ftest                 [.] main         [.] bar             
   4.83%  ftest    ftest                 [.] bar          [.] qux             
   4.57%  ftest    ftest                 [.] main         [.] main            
   4.38%  ftest    ftest                 [.] foo          [.] main            
   4.13%  ftest    ftest                 [.] qux          [.] foo             
   3.89%  ftest    ftest                 [.] qux          [.] bar             
   3.86%  ftest    ftest                 [.] bar          [.] main            

- Test on the guest:
Overhead  Command  Source Shaged Object  Source Symbol    Target Symbol
  22.36%  ftest    libc-2.23.so          [.] random       [.] random  
   8.55%  ftest    ftest                 [.] qux          [.] qux                    
   5.79%  ftest    libc-2.23.so          [.] random       [.] random_r                     
   5.64%  ftest    ftest                 [.] random@plt   [.] random                     
   5.58%  ftest    ftest                 [.] main         [.] random@plt                       
   5.55%  ftest    ftest                 [.] main         [.] foo                       
   5.41%  ftest    libc-2.23.so          [.] random       [.] main                 
   5.31%  ftest    libc-2.23.so          [.] random_r     [.] random                      
   5.11%  ftest    ftest                 [.] foo          [.] qux                     
   4.93%  ftest    ftest                 [.] main         [.] main                     
   4.59%  ftest    ftest                 [.] qux          [.] bar                       
   4.49%  ftest    ftest                 [.] bar          [.] main                       
   4.42%  ftest    ftest                 [.] bar          [.] qux                       
   4.16%  ftest    ftest                 [.] main         [.] bar                       
   3.95%  ftest    ftest                 [.] qux          [.] foo                        
   3.79%  ftest    ftest                 [.] foo          [.] main
(due to the lib version difference, "random" is equavlent to __random above)

v7->v8 Changelog:
  - Patch 3:
    -- document KVM_CAP_X86_GUEST_LBR in api.txt
    -- make the check of KVM_CAP_X86_GUEST_LBR return the size of
       struct x86_perf_lbr_stack, to let userspace do a compatibility
       check.
  - Patch 7:
    -- support perf scheduler to not assign a counter for the perf event
       that has PERF_EV_CAP_NO_COUNTER set (rather than skipping the perf
       scheduler). This allows the scheduler to detect lbr usage conflicts
       via get_event_constraints, and lower priority events will finally
       fail to use lbr.
    -- define X86_PMC_IDX_NA as "-1", which represents a never assigned
       counter id. There are other places that use "-1", but could be
       updated to use the new macro in another patch series.
  - Patch 8:
    -- move the event->owner assignment into perf_event_alloc to have it
       set before event_init is called. Please see this patch's commit for
       reasons.
  - Patch 9:
    -- use "exclude_host" and "is_kernel_event" to decide if the lbr event
       is used for the vcpu lbr emulation, which doesn't need a counter,
       and removes the usage of the previous new perf_event_create API.
    -- remove the unused attr fields.
  - Patch 10:
    -- set a hardware reserved bit (bit 62 of LBR_SELECT) to reg->config
       for the vcpu lbr emulation event. This makes the config different
       from other host lbr event, so that they don't share the lbr.
       Please see the comments in the patch for the reasons why they
       shouldn't share.
  - Patch 12:
    -- disable interrupt and check if the vcpu lbr event owns the lbr
       feature before kvm writing to the lbr related msr. This avoids kvm
       updating the lbr msrs after lbr has been reclaimed by other events
       via ipi.
    -- remove arch v4 related support.
  - Patch 13:
    -- double check if the vcpu lbr event owns the lbr feature before
       vm-entry into the guest. The lbr pass-through will be cancelled if
       lbr feature has been reclaimed by a cpu pinned lbr event.

Previous:
https://lkml.kernel.org/r/1562548999-37095-1-git-send-email-wei.w.wang@intel.com

Wei Wang (14):
  perf/x86: fix the variable type of the lbr msrs
  perf/x86: add a function to get the addresses of the lbr stack msrs
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: intel_pmu_lbr_enable
  KVM/x86/vPMU: tweak kvm_pmu_get_msr
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  perf/x86: support to create a perf event without counter allocation
  perf/core: set the event->owner before event_init
  KVM/x86/vPMU: APIs to create/free lbr perf event for a vcpu thread
  perf/x86/lbr: don't share lbr for the vcpu usage case
  perf/x86: save/restore LBR_SELECT on vcpu switching
  KVM/x86/lbr: lbr emulation
  KVM/x86/vPMU: check the lbr feature before entering guest
  KVM/x86: remove the common handling of the debugctl msr

 Documentation/virt/kvm/api.txt    |  26 +++
 arch/x86/events/core.c            |  36 ++-
 arch/x86/events/intel/core.c      |   3 +
 arch/x86/events/intel/lbr.c       |  95 +++++++-
 arch/x86/events/perf_event.h      |   6 +-
 arch/x86/include/asm/kvm_host.h   |   5 +
 arch/x86/include/asm/perf_event.h |  17 ++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/pmu.c                |  24 +-
 arch/x86/kvm/pmu.h                |  11 +-
 arch/x86/kvm/pmu_amd.c            |   7 +-
 arch/x86/kvm/vmx/pmu_intel.c      | 476 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |   4 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  47 ++--
 include/linux/perf_event.h        |  18 ++
 include/uapi/linux/kvm.h          |   1 +
 kernel/events/core.c              |  19 +-
 18 files changed, 738 insertions(+), 61 deletions(-)
```
#### [PATCH v1 0/2] Simplify mtty driver and mdev core
##### From: Parav Pandit <parav@mellanox.com>

```c

Currently mtty sample driver uses mdev state and UUID in convoluated way to
generate an interrupt.
It uses several translations from mdev_state to mdev_device to mdev uuid.
After which it does linear search of long uuid comparision to
find out mdev_state in mtty_trigger_interrupt().
mdev_state is already available while generating interrupt from which all
such translations are done to reach back to mdev_state.

This translations are done during interrupt generation path.
This is unnecessary and reduandant.

Hence,
Patch-1 simplifies mtty sample driver to directly use mdev_state.

Patch-2, Since no production driver uses mdev_uuid() and mdev's name
(derived from UUID) is already available using core kernel dev_name(),
this patch simplifies and removes redandant mdev_uuid() exported symbol.

Parav Pandit (2):
  vfio-mdev/mtty: Simplify interrupt generation
  vfio/mdev: Removed unused and redundant API for mdev UUID

 drivers/vfio/mdev/mdev_core.c |  6 ------
 include/linux/mdev.h          |  1 -
 samples/vfio-mdev/mtty.c      | 39 +++++++----------------------------
 3 files changed, 8 insertions(+), 38 deletions(-)
```
#### [RFC PATCH 00/20] i386: Add support for Intel SGX
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

This series enables exposing Intel Software Guard Extensions (SGX) to KVM
guests.  This series is firmly RFC due to SGX support not yet being
accepted into the Linux kernel, let alone KVM.

The primary goal of this RFC is to get feedback on the overall approach,
especially with respect to Enclave Page Cache (EPC) handling, but any
feedback whatsoever would be greatly appreciated.  Please don't hesitate
to ask for more details and/or clarification.

The code is based on 'https://github.com/ehabkost/qemu.git x86-next',
which currently points at commit:

  ff656fcd33 ("i386: Fix Snowridge CPU model name and features")


Brief arch blurb (providing useful documentation in a cover letter is
impractical due to scope of SGX):

  SGX is a set of instructions and mechanisms that enable ring 3
  applications to set aside private regions of code and data for the
  purpose of establishing and running enclaves.  An enclave is a secure
  entity whose private memory can only be accessed by code running within
  the enclave.  Accesses from outside the enclave, including software
  running at a higher privilege level and other enclaves, are disallowed
  by hardware.

Overviews and details:

  SGX arch kernel doc - https://patchwork.kernel.org/patch/11043125/

  SGX arch overview   - https://www.youtube.com/watch?v=mPT_vJrlHlg

Gory details on SGX are also available in all recent versions of Intel's
SDM, e.g. chapters 37-42 in Vol. 3 of the May 2019 version of the SDM.


Linux kernel and KVM enabling:

  SGX kernel enabling - https://lkml.kernel.org/r/20190713170804.2340-1-jarkko.sakkinen@linux.intel.com

  SGX KVM enabling    - https://lkml.kernel.org/r/20190727055214.9282-1-sean.j.christopherson@intel.com


QEMU points of interest:

Basics - SGX is exposed the guest if and only if KVM is enabled and
         supports virtualization of SGX, and the kernel provides access
         to "raw" EPC.  Because SGX uses a hardware-based root of trust,
         the attestation aspects of SGX cannot be emulated in software,
         i.e. ultimately emulation will fail as software cannot generate
         a valid quote/report.  The complexity of partially emulating SGX
         in Qemu far outweighs the value added, e.g. an SGX specific
         simulator for userspace applications can emulate SGX for
         development and testing purposes.

EPC - Because of its unique requirements, the kernel manages EPC separately
      from normal memory.  Similar to memfd, the device /dev/sgx/virt_epc
      can be opened to obtain a file descriptor which can in turn be used
      to mmap() EPC memory.

      The notable quirk with EPC from QEMU's perspective is that EPC is
      enumerated via CPUID, which complicates realizing EPC as a normal
      device due to vCPU creation depending on the location/size of EPC
      sections.

Migration - Physical EPC is encrypted with an ephemeral key that is
            (re)generated at CPU reset, i.e. is platform specific.  Thus,
            migrating EPC contents between physical platforms is
            infeasible.  However, live migration is not blocked by SGX as
            kernels and applications are conditioned to gracefully handle
            EPC invalidation due to the EPC being zapped on power state
            transitions that power down the CPU, e.g. S3.  I.e. from the
            guest's perspective, live migration appears and is handled
            like an unannounced suspend/resume cycle.

NUMA - How EPC NUMA affinity will be enumerated to the kernel is not yet
       defined (initial hardware support for SGX was limited to single
       socket systems).

Sean Christopherson (20):
  hostmem: Add hostmem-epc as a backend for SGX EPC
  i386: Add 'sgx-epc' device to expose EPC sections to guest
  vl: Add "sgx-epc" option to expose SGX EPC sections to guest
  i386: Add primary SGX CPUID and MSR defines
  i386: Add SGX CPUID leaf FEAT_SGX_12_0_EAX
  i386: Add SGX CPUID leaf FEAT_SGX_12_1_EAX
  i386: Add SGX CPUID leaf FEAT_SGX_12_1_EBX
  i386: Add get/set/migrate support for SGX LE public key hash MSRs
  i386: Add feature control MSR dependency when SGX is enabled
  i386: Update SGX CPUID info according to hardware/KVM/user input
  linux-headers: Add temporary placeholder for KVM_CAP_SGX_ATTRIBUTE
  i386: kvm: Add support for exposing PROVISIONKEY to guest
  i386: Propagate SGX CPUID sub-leafs to KVM
  i386: Adjust min CPUID level to 0x12 when SGX is enabled
  hw/i386/pc: Set SGX bits in feature control fw_cfg accordingly
  hw/i386/pc: Account for SGX EPC sections when calculating device
    memory
  i386/pc: Add e820 entry for SGX EPC section(s)
  i386: acpi: Add SGX EPC entry to ACPI tables
  q35: Add support for SGX EPC
  i440fx: Add support for SGX EPC

 backends/Makefile.objs    |   1 +
 backends/hostmem-epc.c    |  91 ++++++++++++
 hw/i386/Makefile.objs     |   1 +
 hw/i386/acpi-build.c      |  22 +++
 hw/i386/pc.c              |  23 ++-
 hw/i386/pc_piix.c         |   3 +
 hw/i386/pc_q35.c          |   2 +
 hw/i386/sgx-epc.c         | 291 ++++++++++++++++++++++++++++++++++++++
 include/hw/i386/pc.h      |   3 +
 include/hw/i386/sgx-epc.h |  75 ++++++++++
 linux-headers/linux/kvm.h |   1 +
 qapi/misc.json            |  32 ++++-
 qemu-options.hx           |  12 ++
 target/i386/cpu.c         | 148 ++++++++++++++++++-
 target/i386/cpu.h         |  14 ++
 target/i386/kvm-stub.c    |   5 +
 target/i386/kvm.c         |  70 +++++++++
 target/i386/kvm_i386.h    |   3 +
 target/i386/machine.c     |  20 +++
 vl.c                      |   9 ++
 20 files changed, 820 insertions(+), 6 deletions(-)
 create mode 100644 backends/hostmem-epc.c
 create mode 100644 hw/i386/sgx-epc.c
 create mode 100644 include/hw/i386/sgx-epc.h
```
