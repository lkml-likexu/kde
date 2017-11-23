#### [PATCH kvm-unit-tests 1/2] arm/arm64: prepare to compile arm64 tests relocatable
##### From: Andrew Jones <drjones@redhat.com>

```c
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/Makefile.arm    |  6 +++++-
 arm/Makefile.arm64  |  6 +++++-
 arm/Makefile.common | 19 +++++++------------
 3 files changed, 17 insertions(+), 14 deletions(-)

```
#### [PATCH V3 1/4] target-i386: introduce coalesced_pio kvm header update
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced_pio's struct and KVM_CAP_COALESCED_PIO.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 linux-headers/linux/kvm.h | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: arm/arm64: Clean dcache to PoC when changing PTE due to CoW
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
When triggering a CoW, we unmap the RO page via an MMU notifier
(invalidate_range_start), and then populate the new PTE using another
one (change_pte). In the meantime, we'll have copied the old page
into the new one.

The problem is that the data for the new page is sitting in the
cache, and should the guest have an uncached mapping to that page
(or its MMU off), following accesses will bypass the cache.

In a way, this is similar to what happens on a translation fault:
We need to clean the page to the PoC before mapping it. So let's just
do that.

This fixes a KVM unit test regression observed on a HiSilicon platform,
and subsequently reproduced on Seattle.

Fixes: a9c0e12ebee5 ("KVM: arm/arm64: Only clean the dcache on translation fault")
Reported-by: Mike Galbraith <efault@gmx.de>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 virt/kvm/arm/mmu.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Set fault_dsisr on H_INST_STORAGE interrupts
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When a page fault is handled the bits in fault_dsisr are used to
determine the cause of the fault. In the H_DATA_STORAGE interrupt
case these bits come from the HDSISR register and are stored in
fault_dsisr on vm exit. However for a H_INST_STORAGE interrupt
fault_dsisr is set to zero.

Currently we handle the page fault anyway, even if fault_dsisr is set
to zero. However it means we can never update the RC bits of a pte on
an instruction fault since the corresponding bit to indicate this is
needed will never be set.

On a H_INST_STORAGE interrupt the fault bits are in HSRR1 which is
stored in the guest_msr on vm exit. So to correct this we mask the
appropriate bits from the guest_msr and set it in fault_dsisr.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: Remove obsolete kvm_unmap_hva notifier backend
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
kvm_unmap_hva is long gone, and we only have kvm_unmap_hva_range to
deal with. Drop the now obsolete code.

Fixes: fb1522e099f0 ("KVM: update to new mmu_notifier semantic v2")
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/arm/include/asm/kvm_host.h   |  1 -
 arch/arm64/include/asm/kvm_host.h |  1 -
 arch/mips/include/asm/kvm_host.h  |  1 -
 arch/mips/kvm/mmu.c               | 10 ----------
 arch/x86/include/asm/kvm_host.h   |  1 -
 arch/x86/kvm/mmu.c                |  5 -----
 virt/kvm/arm/mmu.c                | 12 ------------
 virt/kvm/arm/trace.h              | 15 ---------------
 8 files changed, 46 deletions(-)

```
#### [PATCH v3 1/3] KVM: s390: vsie: copy wrapping keys to right place
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Copy the key mask to the right offset inside the shadow CRYCB

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/vsie.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/8] KVM: VMX: Do not allow reexecute_instruction() when skipping MMIO instr
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Re-execution after an emulation decode failure is only intended to
handle a case where two or vCPUs race to write a shadowed page, i.e.
we should never re-execute an instruction as part of MMIO emulation.
As handle_ept_misconfig() is only used for MMIO emulation, it should
pass EMULTYPE_NO_REEXECUTE when using the emulator to skip an instr
in the fast-MMIO case where VM_EXIT_INSTRUCTION_LEN is invalid.

And because the cr2 value passed to x86_emulate_instruction() is only
destined for use when retrying or reexecuting, we can simply call
emulate_instruction().

Fixes: d391f1207067 ("x86/kvm/vmx: do not use vm-exit instruction length
                      for fast MMIO when running nested")
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL] virtio,vhost: fixes, tweaks
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit 94710cac0ef4ee177a63b5227664b38c95bbf703:

  Linux 4.18 (2018-08-12 13:41:04 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 864d39df09b43f9d09d80bc29d8e8888294b3c4b:

  vhost/scsi: increase VHOST_SCSI_PREALLOC_PROT_SGLS to 2048 (2018-08-22 01:01:47 +0300)

----------------------------------------------------------------
virtio, vhost: fixes, tweaks

No new features but a bunch of tweaks such as
switching balloon from oom notifier to shrinker.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Greg Edwards (2):
      vhost: allow vhost-scsi driver to be built-in
      vhost/scsi: increase VHOST_SCSI_PREALLOC_PROT_SGLS to 2048

Suzuki K Poulose (2):
      virtio: mmio-v1: Validate queue PFN
      virtio: pci-legacy: Validate queue pfn

Wei Wang (3):
      virtio-balloon: remove BUG() in init_vqs
      virtio-balloon: kzalloc the vb struct
      virtio_balloon: replace oom notifier with shrinker

 drivers/vhost/Kconfig              |   2 +-
 drivers/vhost/scsi.c               |   2 +-
 drivers/virtio/virtio_balloon.c    | 125 ++++++++++++++++++++-----------------
 drivers/virtio/virtio_mmio.c       |  20 +++++-
 drivers/virtio/virtio_pci_legacy.c |  14 ++++-
 5 files changed, 99 insertions(+), 64 deletions(-)
```
#### [PATCH] scsi/virio_scsi.c: do not call virtscsi_remove_vqs() in virtscsi_init() to avoid crash bug
##### From: piaojun <piaojun@huawei.com>

```c
If some error happened before find_vqs, error branch will goto
virtscsi_remove_vqs to free vqs. Actually the vqs have not been allocated
successfully, so this will cause wild-pointer-free problem. So
virtscsi_remove_vqs could be deleted as no error will happen after
find_vqs.

Signed-off-by: Jun Piao <piaojun@huawei.com>
---
 drivers/scsi/virtio_scsi.c | 2 --
 1 file changed, 2 deletions(-)

--

```
#### [PATCH] x86/kvm/nVMX: avoid redundant double assignment of nested_run_pending
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
nested_run_pending is set 20 lines above and check_vmentry_prereqs()/
check_vmentry_postreqs() don't seem to be resetting it (the later, however,
checks it).

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Eduardo Valentin <eduval@amazon.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx.c | 3 ---
 1 file changed, 3 deletions(-)

```
