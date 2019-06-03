

#### [PATCH v2 00/20] hw/i386/pc: Do not restrict the fw_cfg functions to
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c

Hi,

This is my take at salvaging some NEMU good work.
Samuel worked in adding the fw_cfg device to the x86-virt NEMU machine.
This series is inspired by NEMU's commit 3cb92d080835 [*] and adapted
to upstream style. The result makes the upstream codebase more
modularizable.
There are very little logical changes, this is mostly a cleanup
refactor.

Since v1:
- Addressed Li and MST comments

$ git backport-diff -u v1
Key:
[----] : patches are identical
[####] : number of functional differences between upstream/downstream patch
[down] : patch is downstream-only
The flags [FC] indicate (F)unctional and (C)ontextual differences, respectively

001/20:[----] [-C] 'hw/i386/pc: Use unsigned type to index arrays'
002/20:[----] [-C] 'hw/i386/pc: Use size_t type to hold/return a size of array'
003/20:[----] [--] 'hw/i386/pc: Let e820_add_entry() return a ssize_t type'
004/20:[0008] [FC] 'hw/i386/pc: Add the E820Type enum type'
005/20:[----] [-C] 'hw/i386/pc: Add documentation to the e820_*() functions'
006/20:[----] [--] 'hw/i386/pc: Use e820_get_num_entries() to access e820_entries'
007/20:[0016] [FC] 'hw/i386/pc: Extract e820 memory layout code'
008/20:[----] [--] 'hw/i386/pc: Use address_space_memory in place'
009/20:[down] 'hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create'
010/20:[0009] [FC] 'hw/i386/pc: Pass the boot_cpus value by argument'
011/20:[0010] [FC] 'hw/i386/pc: Pass the apic_id_limit value by argument'
012/20:[0009] [FC] 'hw/i386/pc: Pass the CPUArchIdList array by argument'
013/20:[0008] [FC] 'hw/i386/pc: Let fw_cfg_init() use the generic MachineState'
014/20:[----] [--] 'hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument'
015/20:[----] [--] 'hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument'
016/20:[----] [--] 'hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()'
017/20:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument'
018/20:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a MachineState argument'
019/20:[----] [--] 'hw/i386/pc: Rename pc_build_feature_control() as generic fw_cfg_build_*'
020/20:[0132] [FC] 'hw/i386/pc: Extract the x86 generic fw_cfg code'
Do you want to view the diffs using meld? y/[n]:

Regards,

Phil.

[*] https://github.com/intel/nemu/commit/3cb92d080835ac8d47c8b713156338afa33cff5c

Philippe Mathieu-Daudé (20):
  hw/i386/pc: Use unsigned type to index arrays
  hw/i386/pc: Use size_t type to hold/return a size of array
  hw/i386/pc: Let e820_add_entry() return a ssize_t type
  hw/i386/pc: Add the E820Type enum type
  hw/i386/pc: Add documentation to the e820_*() functions
  hw/i386/pc: Use e820_get_num_entries() to access e820_entries
  hw/i386/pc: Extract e820 memory layout code
  hw/i386/pc: Use address_space_memory in place
  hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create
  hw/i386/pc: Pass the boot_cpus value by argument
  hw/i386/pc: Pass the apic_id_limit value by argument
  hw/i386/pc: Pass the CPUArchIdList array by argument
  hw/i386/pc: Let fw_cfg_init() use the generic MachineState
  hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument
  hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument
  hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()
  hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument
  hw/i386/pc: Let pc_build_feature_control() take a MachineState
    argument
  hw/i386/pc: Rename pc_build_feature_control() as generic
    fw_cfg_build_*
  hw/i386/pc: Extract the x86 generic fw_cfg code

 hw/i386/Makefile.objs        |   2 +-
 hw/i386/e820_memory_layout.c |  60 +++++++++++
 hw/i386/e820_memory_layout.h |  76 +++++++++++++
 hw/i386/fw_cfg.c             | 137 ++++++++++++++++++++++++
 hw/i386/fw_cfg.h             |   8 ++
 hw/i386/pc.c                 | 201 ++---------------------------------
 include/hw/i386/pc.h         |  11 --
 target/i386/kvm.c            |   1 +
 8 files changed, 291 insertions(+), 205 deletions(-)
 create mode 100644 hw/i386/e820_memory_layout.c
 create mode 100644 hw/i386/e820_memory_layout.h
```
#### [PATCH 00/43] VMX optimizations
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

This is the outcome of the review of Sean's VMX optimization series,
with some coding style improvements (at least according to me :)
and conflicts resolved between the various series that he sent.

The result on nested vmexit.flat is about a 12% improvement on
vmexit speed:

                                   before   after
    cpuid                          14886    13142
    vmcall                         14918    13189
    inl_from_pmtimer               47277    45536
    inl_from_qemu                  46747    44826
    inl_from_kernel                15218    13518
    outl_to_kernel                 15184    13436
    self_ipi_sti_nop               16458    14858
    self_ipi_sti_hlt               31876    28348
    self_ipi_tpr                   16603    15003
    self_ipi_tpr_sti_nop           16509    15048
    self_ipi_tpr_sti_hlt           32027    28386
    x2apic_self_ipi_sti_hlt        16386    14788
    x2apic_self_ipi_tpr_sti_hlt    16479    14881


Patches 1-6 were posted as "KVM: VMX: INTR, NMI and #MC cleanup".

Patches 7-13 were posted as "KVM: nVMX: Optimize VMCS data copying".

Patches 15-30 were posted as "KVM: nVMX: Optimize nested VM-Entry".

Patches 31-43 were posted as "KVM: VMX: Reduce VMWRITEs to VMCS controls".

Paolo Bonzini (5):
  kvm: nVMX: small cleanup in handle_exception
  KVM: nVMX: Rename prepare_vmcs02_*_full to prepare_vmcs02_*_rare
  KVM: VMX: simplify vmx_prepare_switch_to_{guest,host}
  KVM: x86: introduce is_pae_paging
  KVM: nVMX: shadow pin based execution controls

Sean Christopherson (38):
  KVM: VMX: Fix handling of #MC that occurs during VM-Entry
  KVM: VMX: Read cached VM-Exit reason to detect external interrupt
  KVM: VMX: Store the host kernel's IDT base in a global variable
  KVM: x86: Move kvm_{before,after}_interrupt() calls to vendor code
  KVM: VMX: Handle NMIs, #MCs and async #PFs in common irqs-disabled fn
  KVM: nVMX: Intercept VMWRITEs to read-only shadow VMCS fields
  KVM: nVMX: Intercept VMWRITEs to GUEST_{CS,SS}_AR_BYTES
  KVM: nVMX: Track vmcs12 offsets for shadowed VMCS fields
  KVM: nVMX: Lift sync_vmcs12() out of prepare_vmcs12()
  KVM: nVMX: Use descriptive names for VMCS sync functions and flags
  KVM: nVMX: Add helpers to identify shadowed VMCS fields
  KVM: nVMX: Sync rarely accessed guest fields only when needed
  KVM: VMX: Always signal #GP on WRMSR to MSR_IA32_CR_PAT with bad value
  KVM: nVMX: Always sync GUEST_BNDCFGS when it comes from vmcs01
  KVM: nVMX: Write ENCLS-exiting bitmap once per vmcs02
  KVM: nVMX: Don't rewrite GUEST_PML_INDEX during nested VM-Entry
  KVM: nVMX: Don't "put" vCPU or host state when switching VMCS
  KVM: nVMX: Don't reread VMCS-agnostic state when switching VMCS
  KVM: nVMX: Don't dump VMCS if virtual APIC page can't be mapped
  KVM: nVMX: Don't speculatively write virtual-APIC page address
  KVM: nVMX: Don't speculatively write APIC-access page address
  KVM: nVMX: Update vmcs12 for MSR_IA32_CR_PAT when it's written
  KVM: nVMX: Update vmcs12 for SYSENTER MSRs when they're written
  KVM: nVMX: Update vmcs12 for MSR_IA32_DEBUGCTLMSR when it's written
  KVM: nVMX: Don't update GUEST_BNDCFGS if it's clean in HV eVMCS
  KVM: nVMX: Copy PDPTRs to/from vmcs12 only when necessary
  KVM: nVMX: Use adjusted pin controls for vmcs02
  KVM: VMX: Add builder macros for shadowing controls
  KVM: VMX: Shadow VMCS pin controls
  KVM: VMX: Shadow VMCS primary execution controls
  KVM: VMX: Shadow VMCS secondary execution controls
  KVM: nVMX: Shadow VMCS controls on a per-VMCS basis
  KVM: nVMX: Don't reset VMCS controls shadow on VMCS switch
  KVM: VMX: Explicitly initialize controls shadow at VMCS allocation
  KVM: nVMX: Preserve last USE_MSR_BITMAPS when preparing vmcs02
  KVM: nVMX: Preset *DT exiting in vmcs02 when emulating UMIP
  KVM: VMX: Drop hv_timer_armed from 'struct loaded_vmcs'
  KVM: VMX: Leave preemption timer running when it's disabled

 arch/x86/include/asm/kvm_host.h       |   2 +-
 arch/x86/kvm/svm.c                    |   6 +-
 arch/x86/kvm/vmx/nested.c             | 591 +++++++++++++++++++++-------------
 arch/x86/kvm/vmx/nested.h             |   2 +-
 arch/x86/kvm/vmx/vmcs.h               |  17 +-
 arch/x86/kvm/vmx/vmcs12.h             |  57 ++--
 arch/x86/kvm/vmx/vmcs_shadow_fields.h |  79 ++---
 arch/x86/kvm/vmx/vmx.c                | 408 ++++++++++++-----------
 arch/x86/kvm/vmx/vmx.h                | 122 +++----
 arch/x86/kvm/x86.c                    |  12 +-
 arch/x86/kvm/x86.h                    |   5 +
 11 files changed, 733 insertions(+), 568 deletions(-)
```
#### [PATCH v4 0/7] s390: vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in three deficiencies
this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP configuration
   becomes available to the guest when it is subsequently restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to either
   mask can result in AP queue devices being unbound from the vfio_ap
   device driver and bound to a zcrypt device driver even if a guest is
   using the queues, thus giving the host access to the guest's private
   crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   an AP queue device bound to the vfio_ap device driver. 

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement more
of the AP architecture:

1. A root user will be prevented from making changes to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the ownership of an APQN
   changes from the vfio_ap device driver to a zcrypt driver if the APQN is
   assigned to a matrix mdev.

2. The sysfs bind/unbind interfaces will be disabled for the vfio_ap device
   driver.

3. Allow AP resources to be assigned to or removed from a matrix mdev
   while a guest is using it and hot plug the resource into or hot unplug
   the resource from the running guest.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if it
   results in assignment of an APQN that does not reference an AP queue
   device bound to the vfio_ap device driver, as long as the APQN is owned
   by the vfio_ap driver. Allowing over-provisioning of AP resources
   better models the architecture which does not preclude assigning AP
   resources that are not yet available in the system.

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source. It is not out of the ordinary for the kernel to prevent a root
user from performing an action under certain circumstances; for example,
a root user is prevented from removing a module until all references to it
are given up. An even more pertinent example is the device driver bind
interface. Binding a device to a driver that does not meet the match
criteria will be rejected by the kernel.

2. Rationale for disabling bind/unbind interfaces for vfio_ap driver:
-----------------------------------------------------------------
By disabling the bind/unbind interfaces for the vfio_ap device driver, 
the user is forced to use the AP bus's apmask/aqmask interfaces to control
the probing and removing of AP queues. There are two primary reasons for
disabling the bind/unbind interfaces for the vfio_ap device driver:

* The device architecture does not provide a means to prevent unbinding
  a device from a device driver, so an AP queue device can be unbound
  from the vfio_ap driver even the queue is in use by a guest. By
  disabling the unbind interface, the user is forced to use the AP bus's
  apmask/aqmask interfaces which will prevent this.

* Binding of AP queues is controlled by the AP bus /sys/bus/ap/apmask and
  /sys/bus/ap/aqmask interfaces. If the masks indicate that an APQN is
  owned by zcrypt, trying to bind it to the vfio_ap device driver will
  fail; therefore, the bind interface is somewhat redundant and certainly
  unnecessary.        
  
3. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes 
reconfiguring a guest's AP matrix much less disruptive.

4. Rationale for allowing over-provisioning of AP resources:
----------------------------------------------------------- 
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will automatically acquire access to it. If an APQN
is dynamically unassigned from the underlying host system, it will 
automatically become unavailable to the guest.

Note: This patch series is rebased on top of the patch series for
      'vfio: ap: AP Queue Interrupt Control' (v9) to make merging of the
      two series simpler. 
 

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (7):
  s390: vfio-ap: Refactor vfio_ap driver probe and remove callbacks
  s390: vfio-ap: wait for queue empty on queue reset
  s390: zcrypt: driver callback to indicate resource in use
  s390: vfio-ap: implement in-use callback for vfio_ap driver
  s390: vfio-ap: allow assignment of unavailable AP resources to mdev
    device
  s390: vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390: vfio-ap: update documentation

 Documentation/s390/vfio-ap.txt        | 292 +++++++++++++++++++--------
 drivers/s390/crypto/ap_bus.c          | 138 ++++++++++++-
 drivers/s390/crypto/ap_bus.h          |   3 +
 drivers/s390/crypto/vfio_ap_drv.c     |  51 +++--
 drivers/s390/crypto/vfio_ap_ops.c     | 370 +++++++++++++---------------------
 drivers/s390/crypto/vfio_ap_private.h |   6 +-
 6 files changed, 526 insertions(+), 334 deletions(-)
```
#### [patch 0/5] cpuidle haltpoll driver and governor (v4)
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

The cpuidle-haltpoll driver with haltpoll governor allows the guest
vcpus to poll for a specified amount of time before halting. 
This provides the following benefits to host side polling:

         1) The POLL flag is set while polling is performed, which allows
            a remote vCPU to avoid sending an IPI (and the associated
            cost of handling the IPI) when performing a wakeup.

         2) The VM-exit cost can be avoided.

The downside of guest side polling is that polling is performed
even with other runnable tasks in the host.

Results comparing halt_poll_ns and server/client application
where a small packet is ping-ponged:

host                                        --> 31.33
halt_poll_ns=300000 / no guest busy spin    --> 33.40   (93.8%)
halt_poll_ns=0 / guest_halt_poll_ns=300000  --> 32.73   (95.7%)

For the SAP HANA benchmarks (where idle_spin is a parameter
of the previous version of the patch, results should be the
same):

hpns == halt_poll_ns

                           idle_spin=0/   idle_spin=800/    idle_spin=0/
                           hpns=200000    hpns=0            hpns=800000
DeleteC06T03 (100 thread) 1.76           1.71 (-3%)        1.78   (+1%)
InsertC16T02 (100 thread) 2.14           2.07 (-3%)        2.18   (+1.8%)
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)      1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)       4.53   (-5%)

V2:

- Move from x86 to generic code (Paolo/Christian)
- Add auto-tuning logic (Paolo)
- Add MSR to disable host side polling (Paolo)

V3:

- Do not be specific about HLT VM-exit in the documentation (Ankur Arora)
- Mark tuning parameters static and __read_mostly (Andrea Arcangeli)
- Add WARN_ON if host does not support poll control (Joao Martins)
- Use sched_clock and cleanup haltpoll_enter_idle (Peter Zijlstra)
- Mark certain functions in kvm.c as static (kernel test robot)
- Remove tracepoints as they use RCU from extended quiescent state (kernel
test robot)

V4:
- Use a haltpoll governor, use poll_state.c poll code (Rafael J. Wysocki)
```
