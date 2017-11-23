#### [PATCH] KVM: PPC: Book3S HV: Optimise mmio emulation for devices on FAST_MMIO_BUS
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Devices on the KVM_FAST_MMIO_BUS by definition have length zero and are
thus used for notification purposes rather than data transfer. For
example eventfd for virtio devices.

This means that when emulating mmio instructions which target devices on
this bus we can immediately handle them and return without needing to load
the instruction from guest memory.

For now we restrict this to stores as this is the only use case at
present.

For a normal guest the effect is negligible, however for a nested guest
we save on the order of 5us per access.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c | 18 ++++++++++++++++++
 1 file changed, 18 insertions(+)

```
