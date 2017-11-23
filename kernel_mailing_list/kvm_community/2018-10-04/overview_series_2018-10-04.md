#### [PATCH] ARM: KVM: Correctly order SGI register entries in the cp15 array
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
The ICC_ASGI1R and ICC_SGI0R register entries in the cp15 array
are not correctly ordered, leading to a BUG() at boot time.

Move them to their natural location.

Fixes: 3e8a8a50c7ef ("KVM: arm: vgic-v3: Add support for ICC_SGI0R and ICC_ASGI1R accesses")
Reported-by: Florian Fainelli <f.fainelli@gmail.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
Paolo, Radim,

Could you please send this patch directly to Greg so that it makes it
into 4.19? I thought I had it fixed long before the merge window, and
obviously didn't...

Thanks,

	M.

 arch/arm/kvm/coproc.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### 
##### 

```c
```
#### [Patch v3 1/3] KVM: x86: rename pte_list_remove to __pte_list_remove
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
This is a patch preparing for further change.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/kvm/mmu.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH] iommu/amd: Clear memory encryption mask from physical addressThread-Topic: [PATCH] iommu/amd: Clear memory encryption mask from physical
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
Boris Ostrovsky reported a memory leak with device passthrough when SME
is active.

The VFIO driver uses iommu_iova_to_phys() to get the physical address for
an iova. This physical address is later passed into vfio_unmap_unpin() to
unpin the memory. The vfio_unmap_unpin() uses pfn_valid() before unpinning
the memory. The pfn_valid() check was failing because encryption mask was
part of the physical address returned. This resulted in the memory not
being unpinned and therefore leaked after the guest terminates.

The memory encryption mask must be cleared from the physical address in
iommu_iova_to_phys().

Fixes: 2543a786aa25 ("iommu/amd: Allow the AMD IOMMU to work with memory encryption")
Reported-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: <iommu@lists.linux-foundation.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: <stable@vger.kernel.org> # 4.14+
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 drivers/iommu/amd_iommu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Avoid crash from THP collapse during radix page fault
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Commit 71d29f43b633 ("KVM: PPC: Book3S HV: Don't use compound_order to
determine host mapping size", 2018-09-11) added a call to
__find_linux_pte() and a dereference of the returned PTE pointer to the
radix page fault path in the common case where the page is normal
system memory.  Previously, __find_linux_pte() was only called for
mappings to physical addresses which don't have a page struct (e.g.
memory-mapped I/O) or where the page struct is marked as reserved
memory.

This exposes us to the possibility that the returned PTE pointer
could be NULL, for example in the case of a concurrent THP collapse
operation.  Dereferencing the returned NULL pointer causes a host
crash.

To fix this, we check for NULL, and if it is NULL, we retry the
operation by returning to the guest, with the expectation that it
will generate the same page fault again (unless of course it has
been fixed up by another CPU in the meantime).

Fixes: 71d29f43b633 ("KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH v4 01/32] powerpc: Turn off CPU_FTR_P9_TM_HV_ASSIST in non-hypervisor mode
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
When doing nested virtualization, it is only necessary to do the
transactional memory hypervisor assist at level 0, that is, when
we are in hypervisor mode.  Nested hypervisors can just use the TM
facilities as architected.  Therefore we should clear the
CPU_FTR_P9_TM_HV_ASSIST bit when we are not in hypervisor mode,
along with the CPU_FTR_HVMODE bit.

Doing this will not change anything at this stage because the only
code that tests CPU_FTR_P9_TM_HV_ASSIST is in HV KVM, which currently
can only be used when when CPU_FTR_HVMODE is set.

Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kernel/cpu_setup_power.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/1] KVM: s390: fix locking for crypto setting error path
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
We need to unlock the kvm->lock mutex in the error case.

Reported-by: smatch
Fixes: 37940fb0b6a2c4bf101 ("KVM: s390: device attrs to enable/disable AP interpretation")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 16 ++++++++++++----
 1 file changed, 12 insertions(+), 4 deletions(-)

```
#### [PATCH]  kvm/x86 : avoid shifting signed 32-bit value by 31 bits
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

  modify AVIC_LOGICAL_ID_ENTRY_VALID_MASK to unsigned

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH]  kvm/x86 : fix some typo
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/mmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [Patch v2 1/3] KVM: x86: rename pte_list_remove to __pte_list_remove
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
This is a patch preparing for further change.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/kvm/mmu.c | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [PATCH 01/11] x86/entry: remove _TIF_ALLWORK_MASK
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
There is no user of _TIF_ALLWORK_MASK since commit 21d375b6b34ff
("x86/entry/64: Remove the SYSCALL64 fast path").
Remove unused define _TIF_ALLWORK_MASK.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/include/asm/thread_info.h | 8 --------
 1 file changed, 8 deletions(-)

```
