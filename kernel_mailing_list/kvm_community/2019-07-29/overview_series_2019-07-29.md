#### [RFC PATCH 01/16] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
We will be using ONE_REG interface accessing VCPU registers from
user-space hence we add KVM_REG_RISCV for RISC-V VCPU registers.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] arm: timer: Fix potential deadlock when waiting for interrupt
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Commit 204e85aa9352 ("arm64: timer: a few test improvements") added a call
to report_info after enabling the timer and before the wfi instruction. The
uart that printf uses is emulated by userspace and is slow, which makes it
more likely that the timer interrupt will fire before executing the wfi
instruction, which leads to a deadlock.

An interrupt can wake up a CPU out of wfi, regardless of the
PSTATE.{A, I, F} bits. Fix the deadlock by masking interrupts on the CPU
before enabling the timer and unmasking them after the wfi returns so the
CPU can execute the timer interrupt handler.

Suggested-by: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 arm/timer.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/3] KVM: X86: Trace vcpu_id for vmexit
##### From: Peter Xu <zhexu@redhat.com>

```c
It helps to pair vmenters and vmexis with multi-core systems.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/trace.h | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PULL] vhost,virtio: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit 5f9e832c137075045d15cd6899ab0505cfb2ca4b:

  Linus 5.3-rc1 (2019-07-21 14:05:38 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 73f628ec9e6bcc45b77c53fe6d0c0ec55eaf82af:

  vhost: disable metadata prefetch optimization (2019-07-26 07:49:29 -0400)

----------------------------------------------------------------
virtio, vhost: bugfixes

Fixes in the iommu and balloon devices.
Disable the meta-data optimization for now - I hope we can get it fixed
shortly, but there's no point in making users suffer crashes while we
are working on that.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Jean-Philippe Brucker (1):
      iommu/virtio: Update to most recent specification

Michael S. Tsirkin (2):
      balloon: fix up comments
      vhost: disable metadata prefetch optimization

Wei Wang (1):
      mm/balloon_compaction: avoid duplicate page removal

 drivers/iommu/virtio-iommu.c      | 40 ++++++++++++++++-------
 drivers/vhost/vhost.h             |  2 +-
 include/uapi/linux/virtio_iommu.h | 32 ++++++++++--------
 mm/balloon_compaction.c           | 69 +++++++++++++++++++++++----------------
 4 files changed, 89 insertions(+), 54 deletions(-)
```
