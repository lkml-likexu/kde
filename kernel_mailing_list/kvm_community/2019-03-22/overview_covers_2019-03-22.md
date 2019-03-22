

#### [PATCH 0/6] KVM/x86: Add workaround to support ExtINT with AVIC
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c

This series is one of the prerequisites for supporting AMD AVIC with
in-kernel irqchip (kernel_irqchip=on).

Since AVIC does not support ExtINT interrupt, which is required during
the booting phase of Windows and FreeBSD VMs (e.g. PIT -> PIC -> ExtInt).
This results in VM hang in the boot loader with kernel_irqchip=on mode.

This series provides workaround by temporary deactivate AVIC and fallback
to use legacy interrupt injection (w/ vINTR and interrupt window).
Then re-activate AVIC once the intrrupts are handled.

Thanks,
Suravee

Suravee Suthikulpanit (6):
  KVM: x86: Add callback functions for handling APIC ID, DFR and LDR
    update
  svm: Add AMD AVIC handlers for APIC ID, DFR and LDR update
  svm: Add support for APIC_ACCESS_PAGE_PRIVATE_MEMSLOT setup/destroy
  kvm: lapic: Add apicv activate/deactivate helper function
  KVM: x86: Add interface for run-time activate/de-activate APIC
    virtualization
  svm: Temporary deactivate AVIC during ExtINT handling

 arch/x86/include/asm/kvm_host.h |  11 ++++
 arch/x86/kvm/lapic.c            |  29 +++++++--
 arch/x86/kvm/lapic.h            |   1 +
 arch/x86/kvm/svm.c              | 106 ++++++++++++++++++++++++++++++--
 arch/x86/kvm/x86.c              |  48 +++++++++++++++
 5 files changed, 185 insertions(+), 10 deletions(-)
```
#### [PATCH v6 0/7] vfio: ap: AP Queue Interrupt Control
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
 - LIST: the list_head to handle the vfio_queue life cycle

Having this structure and the list management greatly ease the handling
of the AP queues and diminues the LOCs needed in the vfio_ap driver by
more than 150 lines in comparison with the previous version.


0) Queues life cycle

vfio_ap_queues are created on probe

We define one bucket on the matrix device to store the free vfio_ap_queues,
the queues not assign to any matrix mediated device.

We define one bucket on each matrix mediated device to hold the
vfio_ap_queues belonging to it.

vfio_ap_queues are deleted on remove

This makes the search for a queue easy and the detection of assignent
incoherency obvious (the queue is not avilable) and simplifies assignment.


1) Phase 1, probe and remove from vfio_ap_queue

The vfio_ap_queue structures are dynamically allocated and setup
when a queue is probed by the ap_vfio_driver.
The vfio_ap_queue is linked to the ap_queue device as the driver data.

The new The vfio_ap_queue is put on a free_list belonging to the
matrix device.

The vfio_ap_queue are free during remove.


2) Phase 2, assignment of vfio_ap_queue to a mediated device

When a APID is assigned we look for APQI already assigned to
the matrix mediated device and associate all the queue with the
APQN = (APID,APQI) to the mediated device by adding them to
the mediated device queue list.
We do the same when a APQI is assigned.

If any queue with a matching APQN can not be found on the matrix
device free list it means it is already associated to another matrix
mediated device and no queue is added to the matrix mediated device.

3) Phase 3, starting the guest

When the VFIO device is opened the PQAP callback and a pointer to
the matrix mediated device are set inside KVM during the open callback.

When the device is closed or if a queue is removed, the vfio_ap_queue is
dissociated from the mediated device.


4) Phase 3 intercepting the PQAP/AQIC instruction

On interception of the PQAP/AQIC instruction, the interception code
verifies that AP instructions are available on hardware and in the
guest and retrun the usual -EOPNOTSUPP return code to let
QEMU handle the fault if it is not the case.

If instructions are allowed but intercepted it can only be due to
specifications errors in instruction usage or to the valid 
interception of PQAP/AQIC.

In this case, we make sure the pqap_hook is initialized and call it.
Otherwise, if the hook is not initialize, we assume that there is
no VFIO AP driver to handle the CRYCB which is consequently empty
and setup a response as AP queue unavailable.
 
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

We take care when enabling GISA that the guest may have issued a
reset and will not need to disable the interuptions before
re-enabling interruptions.

To make sure that the module holding the callback does not disapear
we use a module reference counting in the structure containing the
callback.


5) Phase 4 clean dissociation from the mediated device on remove

On removing of the AP device the remove callback is called.
To be sure that the guest will not access the queue anymore
we clear the APID CRYCB bit.
Cleaning the APID, over the APQI, is chosen because the architecture
specifies that only the APID can be dynamically changed outside IPL.

To be sure that the IRQ is cleared before the GISA is free we use
the KVM reference counting, raise it in open, lower it on release.


6) Associated QEMU patch

There is a QEMU patch which is needed to enable the PQAP/AQIC
facility in the guest.

Posted in qemu-devel@nongnu.org as:
Message-Id: <1550146494-21085-1-git-send-email-pmorel@linux.ibm.com>



Pierre Morel (7):
  s390: ap: kvm: add PQAP interception for AQIC
  s390: ap: new vfio_ap_queue structure
  s390: ap: setup relation betwen KVM and mediated device
  vfio: ap: register IOMMU VFIO notifier
  s390: ap: implement PAPQ AQIC interception in kernel
  s390: ap: Cleanup on removing the AP device
  s390: ap: kvm: Enable PQAP/AQIC facility for the guest

 arch/s390/include/asm/kvm_host.h      |   8 +
 arch/s390/kvm/priv.c                  |  90 ++++
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/ap_bus.h          |   1 +
 drivers/s390/crypto/vfio_ap_drv.c     |  69 ++-
 drivers/s390/crypto/vfio_ap_ops.c     | 784 +++++++++++++++++++++++-----------
 drivers/s390/crypto/vfio_ap_private.h |  20 +
 7 files changed, 728 insertions(+), 245 deletions(-)
```
