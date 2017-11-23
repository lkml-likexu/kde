

#### [PATCH v3 0/3] virtio-balloon: tweak config_changed
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Since virtio-ccw doesn't work with accessing to the config space
inside an interrupt context, this patch series avoids that issue by
moving the config register accesses to the related workqueue contexts.

v2->v3 ChangeLog:
    - rename cmd_id_received to cmd_id_received_cache, and have call sites
      read the latest value via virtio_balloon_cmd_id_received. (Still
      kept Cornelia and Halil's reviewed-by as it's a minor change)
    - remove zeroing vb->num_free_page_blocks in probe since vb is
      allocated via kzalloc.
v1->v2 ChangeLog:
    - add config_read_bitmap to indicate to the workqueue callbacks about
      the necessity of reading the related config fields.

Wei Wang (3):
  virtio-balloon: tweak config_changed implementation
  virtio-balloon: improve update_balloon_size_func
  virtio_balloon: remove the unnecessary 0-initialization

 drivers/virtio/virtio_balloon.c | 104 ++++++++++++++++++++++++++--------------
 1 file changed, 69 insertions(+), 35 deletions(-)
```
#### [PATCH 0/2] KVM: arm/arm64: Add VCPU workarounds firmware register
##### From: Andre Przywara <andre.przywara@arm.com>

```c

Workarounds for Spectre variant 2 or 4 vulnerabilities require some help
from the firmware, so KVM implements an interface to provide that for
guests. When such a guest is migrated, we want to make sure we don't
loose the protection the guest relies on.

This introduces two new firmware registers in KVM's GET/SET_ONE_REG
interface, so userland can save the level of protection implemented by
the hypervisor and used by the guest. Upon restoring these registers,
we make sure we don't downgrade and reject any values that would mean
weaker protection.
There is some table in the code to describe the valid combinations.

Patch 1 implements the two firmware registers, patch 2 adds the
documentation.

This solution is using two hardcoded firmware registers for that. Not
sure if we should introduce something based on SMCCC instead, which
would allow us to report implementation of any SMCCC based service in a
generic way, or if this would be too generic.

ARM(32) is a bit of a pain (again), as the firmware register interface
is shared, but 32-bit does not implement all the workarounds.
For now I stuffed two wrappers into kvm_emulate.h, which doesn't sound
like the best solution. Happy to hear about better ideas.

This has been tested with a hack to allow faking the protection level
via a debugfs knob, then saving/restoring via some userland tool calling
the GET_ONE_REG/SET_ONE_REG ioctls.

Please have a look and comment!

Cheers,
Andre

Andre Przywara (2):
  KVM: arm/arm64: Add save/restore support for firmware workaround state
  KVM: doc: add API documentation on the KVM_REG_ARM_WORKAROUNDS
    register

 Documentation/virtual/kvm/arm/psci.txt |  20 ++++
 arch/arm/include/asm/kvm_emulate.h     |  10 ++
 arch/arm/include/uapi/asm/kvm.h        |   9 ++
 arch/arm64/include/asm/kvm_emulate.h   |  14 +++
 arch/arm64/include/uapi/asm/kvm.h      |   9 ++
 virt/kvm/arm/psci.c                    | 138 ++++++++++++++++++++++++-
 6 files changed, 198 insertions(+), 2 deletions(-)
```
#### [PATCH 00/19] KVM: PPC: Book3S HV: add XIVE native exploitation mode
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIO to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter subengine.

PowerNV/baremetal Linux runs natively under XIVE but sPAPR guests need
special support from the hypervisor to do the same. This is called the
XIVE native exploitation mode and today, it can be activated under the
PowerPC Hypervisor, pHyp. However, Linux/KVM lacks XIVE native support
and still offers the old interrupt mode interface using a
XICS-over-XIVE glue which implements the XICS hcalls.

The following series is proposal to add the same support under KVM.

A new KVM device is introduced for the XIVE native exploitation
mode. It reuses most of the XICS-over-XIVE glue implementation
structures which are internal to KVM but has a completely different
interface. A set of Hypervisor calls configures the sources and the
event queues and from there, all control is done by the guest through
MMIOs.

These MMIO regions (ESB and TIMA) are exposed to guests in QEMU,
similarly to VFIO, and the associated VMAs are populated dynamically
with the appropriate pages using a fault handler. This is implemented
with a couple of KVM device ioctls.

On a POWER9 sPAPR machine, the Client Architecture Support (CAS)
negotiation process determines whether the guest operates with a
interrupt controller using the XICS legacy model, as found on POWER8,
or in XIVE exploitation mode. Which means that the KVM interrupt
device should be created at runtime, after the machine as started.
This requires extra KVM support to create/destroy KVM devices. The
last patches are an attempt to solve that problem.

Migration has its own specific needs. The patchset provides the
necessary routines to quiesce XIVE, to capture and restore the state
of the different structures used by KVM, OPAL and HW. Extra OPAL
support is required for these.

GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.0

OPAL:

  https://github.com/legoater/skiboot/commits/xive

Best wishes for 2019 !

C.


Cédric Le Goater (19):
  powerpc/xive: export flags for the XIVE native exploitation mode
    hcalls
  powerpc/xive: add OPAL extensions for the XIVE native exploitation
    support
  KVM: PPC: Book3S HV: check the IRQ controller type
  KVM: PPC: Book3S HV: export services for the XIVE native exploitation
    device
  KVM: PPC: Book3S HV: add a new KVM device for the XIVE native
    exploitation mode
  KVM: PPC: Book3S HV: add a GET_ESB_FD control to the XIVE native
    device
  KVM: PPC: Book3S HV: add a GET_TIMA_FD control to XIVE native device
  KVM: PPC: Book3S HV: add a VC_BASE control to the XIVE native device
  KVM: PPC: Book3S HV: add a SET_SOURCE control to the XIVE native
    device
  KVM: PPC: Book3S HV: add a EISN attribute to kvmppc_xive_irq_state
  KVM: PPC: Book3S HV: add support for the XIVE native exploitation mode
    hcalls
  KVM: PPC: Book3S HV: record guest queue page address
  KVM: PPC: Book3S HV: add a SYNC control for the XIVE native migration
  KVM: PPC: Book3S HV: add a control to make the XIVE EQ pages dirty
  KVM: PPC: Book3S HV: add get/set accessors for the source
    configuration
  KVM: PPC: Book3S HV: add get/set accessors for the EQ configuration
  KVM: PPC: Book3S HV: add get/set accessors for the VP XIVE state
  KVM: PPC: Book3S HV: add passthrough support
  KVM: introduce a KVM_DELETE_DEVICE ioctl

 arch/powerpc/include/asm/kvm_host.h           |    2 +
 arch/powerpc/include/asm/kvm_ppc.h            |   69 +
 arch/powerpc/include/asm/opal-api.h           |   11 +-
 arch/powerpc/include/asm/opal.h               |    7 +
 arch/powerpc/include/asm/xive.h               |   40 +
 arch/powerpc/include/uapi/asm/kvm.h           |   47 +
 arch/powerpc/kvm/book3s_xive.h                |   82 +
 include/linux/kvm_host.h                      |    2 +
 include/uapi/linux/kvm.h                      |    5 +
 arch/powerpc/kvm/book3s.c                     |   31 +-
 arch/powerpc/kvm/book3s_hv.c                  |   29 +
 arch/powerpc/kvm/book3s_hv_builtin.c          |  196 +++
 arch/powerpc/kvm/book3s_hv_rm_xive_native.c   |   47 +
 arch/powerpc/kvm/book3s_xive.c                |  149 +-
 arch/powerpc/kvm/book3s_xive_native.c         | 1406 +++++++++++++++++
 .../powerpc/kvm/book3s_xive_native_template.c |  398 +++++
 arch/powerpc/kvm/powerpc.c                    |   30 +
 arch/powerpc/sysdev/xive/native.c             |  110 ++
 arch/powerpc/sysdev/xive/spapr.c              |   28 +-
 virt/kvm/kvm_main.c                           |   39 +
 arch/powerpc/kvm/Makefile                     |    4 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S       |   52 +
 .../powerpc/platforms/powernv/opal-wrappers.S |    3 +
 23 files changed, 2722 insertions(+), 65 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_hv_rm_xive_native.c
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 arch/powerpc/kvm/book3s_xive_native_template.c
```
