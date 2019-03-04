#### [PATCH v13 01/20] uaccess: add untagged_addr definition for other arches
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
To allow arm64 syscalls to accept tagged pointers from userspace, we must
untag them when they are passed to the kernel. Since untagging is done in
generic parts of the kernel, the untagged_addr macro needs to be defined
for all architectures.

Define it as a noop for architectures other than arm64.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 include/linux/mm.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v4 01/17] powerpc/xive: add OPAL extensions for the XIVE native exploitation support
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The support for XIVE native exploitation mode in Linux/KVM needs a
couple more OPAL calls to get and set the state of the XIVE internal
structures being used by a sPAPR guest.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---

 Changes since v3:
 
 - rebased on 5.1-rc1 
 
 Changes since v2:
 
 - remove extra OPAL call definitions
 
 arch/powerpc/include/asm/opal-api.h        |  7 +-
 arch/powerpc/include/asm/opal.h            |  7 ++
 arch/powerpc/include/asm/xive.h            | 14 +++
 arch/powerpc/platforms/powernv/opal-call.c |  3 +
 arch/powerpc/sysdev/xive/native.c          | 99 ++++++++++++++++++++++
 5 files changed, 127 insertions(+), 3 deletions(-)

```
#### [RFC PATCH 1/1] KVM: PPC: Report single stepping capability
##### From: Fabiano Rosas <farosas@linux.ibm.com>

```c
When calling the KVM_SET_GUEST_DEBUG ioctl, userspace might request
the next instruction to be single stepped via the
KVM_GUESTDBG_SINGLESTEP control bit of the kvm_guest_debug structure.

We currently don't have support for guest single stepping implemented
in Book3S HV.

This patch adds the KVM_CAP_PPC_GUEST_DEBUG_SSTEP capability in order
to inform userspace about the state of single stepping support.

Signed-off-by: Fabiano Rosas <farosas@linux.ibm.com>
---
 arch/powerpc/kvm/powerpc.c | 5 +++++
 include/uapi/linux/kvm.h   | 1 +
 2 files changed, 6 insertions(+)

```
#### [PATCH] Revert "svm: Fix AVIC incomplete IPI emulation"Thread-Topic: [PATCH] Revert "svm: Fix AVIC incomplete IPI emulation"
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
This reverts commit bb218fbcfaaa3b115d4cd7a43c0ca164f3a96e57.

As Oren Twaig pointed out the old discussion:

  https://patchwork.kernel.org/patch/8292231/

that the change coud potentially cause an extra IPI to be sent to
the destination vcpu because the AVIC hardware already set the IRR bit
before the incomplete IPI #VMEXIT with id=1 (target vcpu is not running).
Since writting to ICR and ICR2 will also set the IRR. If something triggers
the destination vcpu to get scheduled before the emulation finishes, then
this could result in an additional IPI.

Also, the issue mentioned in the commit bb218fbcfaaa was misdiagnosed.

Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Reported-by: Oren Twaig <oren@scalemp.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 19 +++++++++++++++----
 1 file changed, 15 insertions(+), 4 deletions(-)

```
#### [PATCH] svm/avic: iommu/amd: Flush IOMMU IRT after update all entriesThread-Topic: [PATCH] svm/avic: iommu/amd: Flush IOMMU IRT after update all
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
When AVIC is enabled and the VM has discrete device assignment,
the interrupt remapping table (IRT) is used to keep track of which
destination APIC ID the IOMMU will inject the device interrput to.

This means every time a vcpu is blocked or context-switched (i.e.
vcpu_blocking/unblocking() and vcpu_load/put()), the information
in IRT must be updated and the IOMMU IRT flush command must be
issued.

The current implementation flushes IOMMU IRT every time an entry
is modified. If the assigned device has large number of interrupts
(hence large number of entries), this would add large amount of
overhead to vcpu context-switch. Instead, this can be optmized by
only flush IRT once per vcpu context-switch per device after all
IRT entries are modified.

The function amd_iommu_update_ga() is refactored to only update
IRT entry, while the amd_iommu_sync_ga() is introduced to allow
IRT flushing to be done separately.

Cc: Joerg Roedel <joro@8bytes.org>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c        | 35 ++++++++++++++++++++++++++++++++++-
 drivers/iommu/amd_iommu.c | 20 +++++++++++++++++---
 include/linux/amd-iommu.h | 13 ++++++++++---
 3 files changed, 61 insertions(+), 7 deletions(-)

```
#### [PATCH v2] kvm: arm: Fix handling of stage2 huge mappings
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
We rely on the mmu_notifier call backs to handle the split/merge
of huge pages and thus we are guaranteed that, while creating a
block mapping, either the entire block is unmapped at stage2 or it
is missing permission.

However, we miss a case where the block mapping is split for dirty
logging case and then could later be made block mapping, if we cancel the
dirty logging. This not only creates inconsistent TLB entries for
the pages in the the block, but also leakes the table pages for
PMD level.

Handle this corner case for the huge mappings at stage2 by
unmapping the non-huge mapping for the block. This could potentially
release the upper level table. So we need to restart the table walk
once we unmap the range.

Fixes : ad361f093c1e31d ("KVM: ARM: Support hugetlbfs backed huge pages")
Reported-by: Zheng Xiang <zhengxiang9@huawei.com>
Cc: Zheng Xiang <zhengxiang9@huawei.com>
Cc: Zhenghui Yu <yuzenghui@huawei.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---

Changes since v1:
 - Fix build break on arm32
   - Add missing definitions for S2_PUD_*
   - Use kvm_pud_pfn() instead of pud_pfn()
 - Make PUD handling similar to PMD, by dropping the else case

 arch/arm/include/asm/stage2_pgtable.h |  2 ++
 virt/kvm/arm/mmu.c                    | 59 +++++++++++++++++++++++++----------
 2 files changed, 45 insertions(+), 16 deletions(-)

```
#### [PATCH V3] cpufreq: Call transition notifier only once for each policy
##### From: Viresh Kumar <viresh.kumar@linaro.org>

```c
Currently we call these notifiers once for each CPU of the policy->cpus
cpumask. It would be more optimal if the notifier can be called only
once and all the relevant information be provided to it. Out of the 23
drivers that register for the transition notifiers today, only 4 of them
do per-cpu updates and the callback for the rest can be called only once
for the policy without any impact.

This would also avoid multiple function calls to the notifier callbacks
and reduce multiple iterations of notifier core's code (which does
locking as well).

This patch adds pointer to the cpufreq policy to the struct
cpufreq_freqs, so the notifier callback has all the information
available to it with a single call. The five drivers which perform
per-cpu updates are updated to use the cpufreq policy. The freqs->cpu
field is redundant now and is removed.

Acked-by: David S. Miller <davem@davemloft.net> (sparc)
Signed-off-by: Viresh Kumar <viresh.kumar@linaro.org>
---

V2->V3:

- Drop changes for arch/arm/kernel/smp_twd.c as the notifier is removed
  in 5.1-rc1.
- Changed implementation in tsc.c as suggested by Rafael and Peterz. We
  now WARN if more than one CPU is present in the policy.
- Rebased over 5.1-rc1.

 arch/arm/kernel/smp.c       | 24 +++++++++++++++---------
 arch/sparc/kernel/time_64.c | 28 ++++++++++++++++------------
 arch/x86/kernel/tsc.c       |  9 +++++++--
 arch/x86/kvm/x86.c          | 31 ++++++++++++++++++++-----------
 drivers/cpufreq/cpufreq.c   | 19 ++++++++++---------
 include/linux/cpufreq.h     | 14 +++++++-------
 6 files changed, 75 insertions(+), 50 deletions(-)

```
#### [PATCH][V3] KVM: svm: merge incomplete IPI emulation handling
##### From: Li RongQing <lirongqing@baidu.com>

```c
Invalid int type emulation and target not running emulation have
same codes, which update APIC ICR high/low registers, and emulate
sending the IPI.

so fall through this switch cases to reduce duplicate codes and
wide the comment out to 80 columns

Co-developed-by: Zhang Yu <zhangyu31@baidu.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
v2->v3: use Co-developed-by, instead of Signed-off-by
v1->v2: make cases statements are back-to-back and wide the comment out
        to 80 columns as suggested by Sean Christopherson

 arch/x86/kvm/svm.c | 28 ++++++++++------------------
 1 file changed, 10 insertions(+), 18 deletions(-)

```
#### [PATCH kvmtool v2 1/3] vfio-pci: Release INTx's unmask eventfd properly
##### From: Leo Yan <leo.yan@linaro.org>

```c
The PCI device INTx uses event fd 'unmask_fd' to signal the deassertion
of the line from guest to host; but this eventfd isn't released properly
when disable INTx.

This patch firstly adds field 'unmask_fd' in struct vfio_pci_device for
storing unmask eventfd and close it when disable INTx.

Signed-off-by: Leo Yan <leo.yan@linaro.org>
---
 include/kvm/vfio.h | 1 +
 vfio/pci.c         | 2 ++
 2 files changed, 3 insertions(+)

```
#### [PATCH] vfio/spapr_tce: Make symbol 'tce_iommu_driver_ops' static
##### From: Wang Hai <wanghai26@huawei.com>

```c
Fixes the following sparse warning:

drivers/vfio/vfio_iommu_spapr_tce.c:1401:36: warning:
 symbol 'tce_iommu_driver_ops' was not declared. Should it be static?

Fixes: 5ffd229c0273 ("powerpc/vfio: Implement IOMMU driver for VFIO")
Signed-off-by: Wang Hai <wanghai26@huawei.com>
Reviewed-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 drivers/vfio/vfio_iommu_spapr_tce.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86: kvm: hyper-v: deal with buggy TLB flush requests from WS2012
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
It was reported that with some special Multi Processor Group configuration,
e.g:
 bcdedit.exe /set groupsize 1
 bcdedit.exe /set maxgroup on
 bcdedit.exe /set groupaware on
for a 16-vCPU guest WS2012 shows BSOD on boot when PV TLB flush mechanism
is in use.

Tracing kvm_hv_flush_tlb immediately reveals the issue:

 kvm_hv_flush_tlb: processor_mask 0x0 address_space 0x0 flags 0x2

The only flag set in this request is HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES,
however, processor_mask is 0x0 and no HV_FLUSH_ALL_PROCESSORS is specified.
We don't flush anything and apparently it's not what Windows expects.

TLFS doesn't say anything about such requests and newer Windows versions
seem to be unaffected. This all feels like a WS2012 bug, which is, however,
easy to workaround in KVM: let's flush everything when we see an empty
flush request, over-flushing doesn't hurt.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
