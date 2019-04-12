

#### [PATCH v6 00/17] KVM: PPC: Book3S HV: add XIVE native exploitation
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIOs to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter sub-engine.

PowerNV/baremetal Linux runs natively under XIVE but sPAPR guests need
special support from the hypervisor to do the same. This is called the
XIVE native exploitation mode and today, it can be activated under the
PowerPC Hypervisor, pHyp. However, Linux/KVM lacks XIVE native support
and still offers the old interrupt mode interface using a KVM device
implementing the XICS hcalls over XIVE.

The following series is proposal to add the same support under KVM.

A new KVM device is introduced for the XIVE native exploitation
mode. It reuses most of the XICS-over-XIVE glue implementation
structures which are internal to KVM but has a completely different
interface. A set of KVM device ioctls provide support for the
hypervisor calls, all handled in QEMU, to configure the sources and
the event queues. From there, all interrupt control is transferred to
the guest which can use MMIOs.

These MMIO regions (ESB and TIMA) are exposed to guests in QEMU,
similarly to VFIO, and the associated VMAs are populated dynamically
with the appropriate pages using a fault handler. These are now
implemented using mmap()s of the KVM device fd.

Migration has its own specific needs regarding memory. The patchset
provides a specific control to quiesce XIVE before capturing the
memory. The save and restore of the internal state is based on the
same ioctls used for the hcalls.

On a POWER9 sPAPR machine, the Client Architecture Support (CAS)
negotiation process determines whether the guest operates with a
interrupt controller using the XICS legacy model, as found on POWER8,
or in XIVE exploitation mode. Which means that the KVM interrupt
device should be created at run-time, after the machine has started.
This requires extra support from KVM to destroy KVM devices. It is
introduced at the end of the patchset and requires some attention.

This is based on Linux 5.1-rc5 and is a candidate for 5.2. The OPAL
patches have been merged now.


GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.1

Thanks,

C.

Possible future todos :

 - We should introduce a set of definitions common to the XIVE and
   XICS-on-XIVE devices
 - The XICS-on-XIVE device file book3s_xive.c could be renamed to
   book3s_xics_on_xive.c or book3s_xics_p9.c   
 - The XICS-on-XIVE device still has some locking issues. 
 - xc->valid is not useful
 - xc->xive is not very useful either. only used in xive_provision_queue()
 
 - The XICS-on-XIVE device provisions XIVE resources "automagically"
   and QEMU needs to follow the same execution path regarding KVM else
   resources are not allocated correctly. This is a bit fragile and
   needs clarification. Compatibility might be complex to handle


Changes since v5:

 - replaced the kvmppc_xive device array with named kvmppc_xive structs.
 - in kvmppc_xive_cleanup_vcpu(), replaced xc->xive by vcpu->kvm->arch.xive
   which is always valid in this context
 - in kvmppc_xive_release(), removed the comment on the race. The
   device being destroyed when the fd is closed, dev->private should
   always be valid when used. Also removed the kick_all_cpus_sync() to
   flush the IPIs.   
 - in the both release operation, removed the test on &kvm->online_vcpus.
 - devices are now freed when the machine exits.

Changes since v4:

 - add check on EQ page alignment
 - add requirement on KVM_XIVE_EQ_ALWAYS_NOTIFY
 - add documentation in Documentation/virtual/kvm/api.txt
 - remove 'destroy' method
 - introduce a 'release' device operation called when device fd is
   closed.
 - introduce a 'xive_devices' array under the VM to store kvmppc_xive
   objects until VM is destroyed.
 
Changes since v3:

 - removed a couple of useless includes
 - fix the test ont the initial setting of the EQ toggle bit : 0 -> 1
 - renamed qsize to qshift
 - renamed qpage to qaddr
 - checked host page size
 - limited flags to KVM_XIVE_EQ_ALWAYS_NOTIFY to fit sPAPR specs
 - Fixed xive_timaval description in documentation

Changes since v2:

 - removed extra OPAL call definitions
 - removed ->q_order setting. Only useful in the XICS-on-XIVE KVM
   device which allocates the EQs on behalf of the guest.
 - returned -ENXIO when VP base is invalid
 - made use of the xive_vp() macro to compute VP identifiers
 - reworked locking in kvmppc_xive_native_connect_vcpu() to fix races 
 - stop advertising KVM_CAP_PPC_IRQ_XIVE as support is not fully
   available yet
 - fixed comment on XIVE IRQ number space
 - removed usage of the __x_* macros
 - fixed locking on source block
 - fixed comments on the KVM device attribute definitions
 - handled MASKED EAS configuration
 - fixed check on supported EQ size to restrict to 64K pages
 - checked kvm_eq.flags that need to be zero
 - removed the OPAL call when EQ qtoggle bit and index are zero. 
 - reduced the size of kvmppc_one_reg timaval attribute to two u64s
 - stopped returning of the OS CAM line value
 
Changes since v1:

 - Better documentation (was missing)
 - Nested support. XIVE not advertised on non PowerNV platforms. This
   is a good way to test the fallback on QEMU emulated devices.
 - ESB and TIMA special mapping done using the KVM device fd
 - All hcalls moved to QEMU. Dropped the patch moving the hcall flags.
 - Reworked of the KVM device ioctl controls to support hcalls and
   migration needs to capture/save states
 - Merged the control syncing XIVE and marking the EQ page dirty
 - Fixed passthrough support using the KVM device file address_space
   to clear the ESB pages from the mapping
 - Misc enhancements and fixes 


Cédric Le Goater (17):
  powerpc/xive: add OPAL extensions for the XIVE native exploitation
    support
  KVM: PPC: Book3S HV: add a new KVM device for the XIVE native
    exploitation mode
  KVM: PPC: Book3S HV: XIVE: introduce a new capability
    KVM_CAP_PPC_IRQ_XIVE
  KVM: PPC: Book3S HV: XIVE: add a control to initialize a source
  KVM: PPC: Book3S HV: XIVE: add a control to configure a source
  KVM: PPC: Book3S HV: XIVE: add controls for the EQ configuration
  KVM: PPC: Book3S HV: XIVE: add a global reset control
  KVM: PPC: Book3S HV: XIVE: add a control to sync the sources
  KVM: PPC: Book3S HV: XIVE: add a control to dirty the XIVE EQ pages
  KVM: PPC: Book3S HV: XIVE: add get/set accessors for the VP XIVE state
  KVM: introduce a 'mmap' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: add a TIMA mapping
  KVM: PPC: Book3S HV: XIVE: add a mapping for the source ESB pages
  KVM: PPC: Book3S HV: XIVE: add passthrough support
  KVM: PPC: Book3S HV: XIVE: activate XIVE exploitation mode
  KVM: introduce a 'release' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: replace the 'destroy' method by a 'release'
    method

 arch/powerpc/include/asm/kvm_host.h        |    8 +-
 arch/powerpc/include/asm/kvm_ppc.h         |   32 +
 arch/powerpc/include/asm/opal-api.h        |    7 +-
 arch/powerpc/include/asm/opal.h            |    7 +
 arch/powerpc/include/asm/xive.h            |   17 +
 arch/powerpc/include/uapi/asm/kvm.h        |   46 +
 arch/powerpc/kvm/book3s_xive.h             |   37 +
 include/linux/kvm_host.h                   |   10 +
 include/uapi/linux/kvm.h                   |    3 +
 arch/powerpc/kvm/book3s.c                  |   31 +-
 arch/powerpc/kvm/book3s_xive.c             |  198 +++-
 arch/powerpc/kvm/book3s_xive_native.c      | 1218 ++++++++++++++++++++
 arch/powerpc/kvm/powerpc.c                 |   46 +
 arch/powerpc/platforms/powernv/opal-call.c |    3 +
 arch/powerpc/sysdev/xive/native.c          |  110 ++
 virt/kvm/kvm_main.c                        |   24 +
 Documentation/virtual/kvm/api.txt          |   10 +
 Documentation/virtual/kvm/devices/xive.txt |  197 ++++
 arch/powerpc/kvm/Makefile                  |    2 +-
 19 files changed, 1941 insertions(+), 65 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
```
