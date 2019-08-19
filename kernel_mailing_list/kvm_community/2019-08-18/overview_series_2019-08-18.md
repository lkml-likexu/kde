#### [PATCH v4 01/15] hw/i386/pc: Use e820_get_num_entries() to access e820_entries
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
To be able to extract the e820* code out of this file (in the next
patch), access e820_entries with its correct helper.

Reviewed-by: Li Qiang <liq3ea@gmail.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/i386/pc.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: arm/arm64: vgic: Allow more than 256 vcpus for KVM_IRQ_LINE
##### From: Marc Zyngier <maz@kernel.org>

```c
While parts of the VGIC support a large number of vcpus (we
bravely allow up to 512), other parts are more limited.

One of these limits is visible in the KVM_IRQ_LINE ioctl, which
only allows 256 vcpus to be signalled when using the CPU or PPI
types. Unfortunately, we've cornered ourselves badly by allocating
all the bits in the irq field.

Since the irq_type subfield (8 bit wide) is currently only taking
the values 0, 1 and 2 (and we have been careful not to allow anything
else), let's reduce this field to only 4 bits, and allocate the
remaining 4 bits to a vcpu2_index, which acts as a multiplier:

  vcpu_id = 256 * vcpu2_index + vcpu_index

With that, and a new capability (KVM_CAP_ARM_IRQ_LINE_LAYOUT_2)
allowing this to be discovered, it becomes possible to inject
PPIs to up to 4096 vcpus. But please just don't.

Reported-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 Documentation/virt/kvm/api.txt    | 8 ++++++--
 arch/arm/include/uapi/asm/kvm.h   | 4 +++-
 arch/arm64/include/uapi/asm/kvm.h | 4 +++-
 include/uapi/linux/kvm.h          | 1 +
 virt/kvm/arm/arm.c                | 2 ++
 5 files changed, 15 insertions(+), 4 deletions(-)

```
