#### [RFC PATCH 1/5] iommu: Add APIs for IOMMU PASID management
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
This adds APIs for IOMMU drivers and device drivers to manage
the PASIDs used for DMA transfer and translation. It bases on
I/O ASID allocator for PASID namespace management and relies
on vendor specific IOMMU drivers for paravirtual PASIDs.

Below APIs are added:

* iommu_pasid_init(pasid)
  - Initialize a PASID consumer. The vendor specific IOMMU
    drivers are able to set the PASID range imposed by IOMMU
    hardware through a callback in iommu_ops.

* iommu_pasid_exit(pasid)
  - The PASID consumer stops consuming any PASID.

* iommu_pasid_alloc(pasid, min, max, private, *ioasid)
  - Allocate a PASID and associate a @private data with this
    PASID. The PASID value is stored in @ioaisd if returning
    success.

* iommu_pasid_free(pasid, ioasid)
  - Free a PASID to the pool so that it could be consumed by
    others.

This also adds below helpers to lookup or iterate PASID items
associated with a consumer.

* iommu_pasid_for_each(pasid, func, data)
  - Iterate PASID items of the consumer identified by @pasid,
    and call @func() against each item. An error returned from
    @func() will break the iteration.

* iommu_pasid_find(pasid, ioasid)
  - Retrieve the private data associated with @ioasid.

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/Kconfig |  1 +
 drivers/iommu/iommu.c | 89 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 73 +++++++++++++++++++++++++++++++++++
 3 files changed, 163 insertions(+)

```
#### [PATCH] svm: Add mutex_lock to protect apic_access_page_done on AMD systems
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
From: Wei Wang <wawei@amazon.de>

There is a race condition when accessing kvm->arch.apic_access_page_done.
Due to it, x86_set_memory_region will fail when creating the second vcpu
for a svm guest.

Add a mutex_lock to serialize the accesses to apic_access_page_done.
This lock is also used by vmx for the same purpose.

Signed-off-by: Wei Wang <wawei@amazon.de>
Signed-off-by: Amadeusz Juskowiak <ajusk@amazon.de>
Signed-off-by: Julian Stecklina <jsteckli@amazon.de>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Reviewed-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH v3 1/4] kvm: vmx: Set IA32_TSC_AUX for legacy mode guestsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
RDTSCP is supported in legacy mode as well as long mode. The
IA32_TSC_AUX MSR should be set to the correct guest value before
entering any guest that supports RDTSCP.

Fixes: 4e47c7a6d714 ("KVM: VMX: Add instruction rdtscp support for guest")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] x86/fpu: Disable BH while while loading FPU registers in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The sequence
   fpu->initialized = 1;
   preempt_disable();
   fpu__restore(fpu);
   preempt_enable();

is racy in regard to a context switch. A context switch after the first
line would save the `actual' content of the FPU registers and trash away
the state that has been prepared (since fpu__drop()).

Use local_bh_disable() around the restore sequence to avoid the race. BH
needs to be disabled because BH is allowed to run (even with preemption
disabled) and might invoke kernel_fpu_begin().

This possible race has been reported by the Kernel Test Robot in FEB
2016 while there still was lazy FPU support.

Link: https://lkml.kernel.org/r/20160226074940.GA28911@pd.tnic
Cc: stable@vger.kernel.org
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/kernel/fpu/signal.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
