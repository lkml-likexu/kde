

#### [PATCH v5 00/12] Guest LBR Enabling
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Last Branch Recording (LBR) is a performance monitor unit (PMU) feature
on Intel CPUs that captures branch related info. This patch series enables
this feature to KVM guests.

Here is a conclusion of the fundamental methods that we use:
1) the LBR feature is enabled per guest via QEMU setting of
   KVM_CAP_X86_GUEST_LBR;
2) the LBR stack is passed through to the guest for direct accesses after
   the guest's first access to any of the lbr related MSRs;
3) the host will help save/resotre the LBR stack when the vCPU is
   scheduled out/in.

ChangeLog:
    - KVM/x86:
        - patch 4: enable guest lbr when guest lbr msr index and host
          lbr msr index matches;
        - patch 5: change kvm_pmu_get_msr to get the msr_data struct;
	- patch 8: remove the PF_VCPU and is_kernel_event check;
	- patch 10:
          - move the lbr virtualization code from vmx.c to pmu_intel.c;
          - save the lbr stack even when the guest is not using the user
            callstack mode in case some tools (e.g. autofdo) complain
            for bogus samples;
        - patch 11: remove the common handling of the debugctl;
        - patch 12: support to report GLOBAL_STATUS_LBRS_FROZEN.
previous:
https://lkml.org/lkml/2018/12/26/82

Like Xu (1):
  KVM/x86/vPMU: Add APIs to support host save/restore the guest lbr
    stack

Wei Wang (11):
  perf/x86: fix the variable type of the LBR MSRs
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: intel_pmu_lbr_enable
  KVM/x86/vPMU: tweak kvm_pmu_get_msr
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  perf/x86: no counter allocation support
  perf/x86: save/restore LBR_SELECT on vCPU switching
  KVM/x86/lbr: lazy save the guest lbr stack
  KVM/x86: remove the common handling of the debugctl msr
  KVM/VMX/vPMU: support to report GLOBAL_STATUS_LBRS_FROZEN

 arch/x86/events/core.c            |  12 ++
 arch/x86/events/intel/lbr.c       |  42 +++-
 arch/x86/events/perf_event.h      |   6 +-
 arch/x86/include/asm/kvm_host.h   |   5 +
 arch/x86/include/asm/perf_event.h |  16 ++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/cpuid.h              |   8 +
 arch/x86/kvm/pmu.c                |  18 +-
 arch/x86/kvm/pmu.h                |  11 +-
 arch/x86/kvm/pmu_amd.c            |   7 +-
 arch/x86/kvm/vmx/pmu_intel.c      | 398 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |   4 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  33 ++--
 include/linux/perf_event.h        |   5 +
 include/uapi/linux/kvm.h          |   1 +
 include/uapi/linux/perf_event.h   |   3 +-
 17 files changed, 535 insertions(+), 38 deletions(-)
```
#### [PATCH v3 0/9] [RFC] vfio: ap: ioctl definitions for AP Queue
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

This patch implement PQAP/AQIC interception in KVM.

To implement this we need to add a new structure, vfio_ap_queue,to be
able to retrieve the mediated device associated with a queue and specific
values needed to register/unregister the interrupt structures:
 - APQN: to be able to issue the commands and search for queue structures
 - NIB : to unpin the NIB on clear IRQ
 - ISC : to unregister with the GIB interface
 - MATRIX: a pointer to the matrix mediated device
 - DEV: a pointer to the AP queue device from AP bus.


1) Phase 1, probe and remove from vfio_ap_queue

The vfio_ap_queue structures are dynamically allocated when a queue
is probed by the ap_vfio_driver.
It is linked to the ap_queue device as the driver data.
We store the APQN of the ap_queue device inside the vfio_ap_queue.
The vfio_ap_queue are free during remove.


2) Phase 2, assignment of vfio_ap_queue to a mediated device

When the VFIO device is opened the queues are associated to
the mediated device, at the same time the CRYCB is setup.

When the device is closed or if a queue is removed the queue is
dissociated from the mediated device, as the same time the
CRYCB is cleared.

Two new functions are used for this: associate/disassociate.


3) Phase 3 intercepting the PQAP/AQIC instruction

On interception of the PQAP/AQIC instruction, the interception code
makes sure the pqap_hook is initialized and allowed to be called
and call it.
Otherwise it reports the usual -EOPNOTSUPP return code to let
QEMU handle the fault.
  
the pqap callback search for the queue asociated with the APQN
stored in the register 0, setting the code to "illegal APQN"
if the vfio_ap_queue can not be found.

Depending on the "i" bit of the register 1, the pqap callback
setup or clear the interruption by calling the host format PQAP/AQIC
instruction.
When seting up the interruption it uses the NIB and the guest ISC
provided by the guest and the host ISC provided by the registration
to the GIB code, pin the NIB and also stores ISC and NIB inside
the vfio_ap_queue structure.
When clearing the interrupt it retrieves the host ISC to unregister
with the GIB code and unpin the NIB.

There is a QEMU patch which is needed to enable the PQAP/AQIC
facility in the guest.

Posted in qemu-devel@nongnu.org as:
Message-Id: <1550146494-21085-1-git-send-email-pmorel@linux.ibm.com>


4) Phase 4 clean dissociation from the mediated device on remove

On removing of the AP device the remove callback is called.
To be sure that the guest will not access the queue anymore
we clear the APID CRYCB bit.
Cleaning the APID, over the APQI, is chosen because the architecture
specifies that only the APID can be dynamically changed outside IPL.
After this the queue is zeroes, care is taken to correctly wait until
the queue is empty.



Pierre Morel (9):
  s390: vfio_ap: link the vfio_ap devices to the vfio_ap bus subsystem
  s390: ap: kvm: setting a hook for PQAP instructions
  s390: ap: new vfio_ap_queue structure
  s390: ap: tools to find a queue with a specific APQN
  s390: ap: tools to associate a queue to a matrix
  vfio: ap: register IOMMU VFIO notifier
  s390: ap: implement PAPQ AQIC interception in kernel
  s390: ap: Cleanup on removing the AP device
  s390: ap: kvm: add AP Queue Interruption Control facility

 arch/s390/include/asm/kvm_host.h      |   1 +
 arch/s390/kvm/priv.c                  |  50 +++++
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/ap_bus.h          |   1 +
 drivers/s390/crypto/vfio_ap_drv.c     | 178 ++++++++++++++++-
 drivers/s390/crypto/vfio_ap_ops.c     | 363 +++++++++++++++++++++++++++++++++-
 drivers/s390/crypto/vfio_ap_private.h |  12 ++
 7 files changed, 593 insertions(+), 13 deletions(-)
```
