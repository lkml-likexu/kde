#### [PATCH V5 1/4]  target-i386: introduce coalesced_pio kvm header update
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced_pio's struct and KVM_CAP_COALESCED_PIO header.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
---
 accel/kvm/kvm-all.c       |  4 ++--
 linux-headers/linux/kvm.h | 11 +++++++++--
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH V4 1/2]   kvm/x86 : add coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 include/uapi/linux/kvm.h  | 11 +++++++++--
 virt/kvm/coalesced_mmio.c | 12 +++++++++---
 virt/kvm/kvm_main.c       |  2 ++
 3 files changed, 20 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: nVMX: Unrestricted guest mode requires EPTFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
As specified in Intel's SDM, do not allow the L1 hypervisor to launch
an L2 guest with the VM-execution controls for "unrestricted guest" or
"mode-based execute control for EPT" set and the VM-execution control
for "enable EPT" clear.

Note that the VM-execution control for "mode-based execute control for
EPT" is not yet virtualized by kvm.

Reported-by: Andrew Thornton <andrewth@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/vmx.h |  1 +
 arch/x86/kvm/vmx.c         | 13 +++++++++++++
 2 files changed, 14 insertions(+)

```
#### [kvm-unit-tests PULL 1/5] s390x: user ctl_set/clear_bit for low address protection
##### From: David Hildenbrand <david@redhat.com>

```c
Use the provided helper functions now.

Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/asm/interrupt.h | 12 ++----------
 1 file changed, 2 insertions(+), 10 deletions(-)

```
#### [PATCH kvm-unit-tests 1/2] arm/arm64: add GICD_IIDR definition
##### From: Andrew Jones <drjones@redhat.com>

```c
From: Shih-Wei Li <shihwei@cs.columbia.edu>

Signed-off-by: Shih-Wei Li <shihwei@cs.columbia.edu>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm/asm/gic.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v1] KVM: SVM: Switch to bitmap_zalloc()
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
Switch to bitmap_zalloc() to show clearly what we are allocating.
Besides that it returns pointer of bitmap type instead of opaque void *.

Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
---
 arch/x86/kvm/svm.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH v2] KVM: LAPIC: Fix pv ipis out-of-bounds access
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Dan Carpenter reported that the untrusted data returns from kvm_register_read()
results in the following static checker warning:
  arch/x86/kvm/lapic.c:576 kvm_pv_send_ipi()
  error: buffer underflow 'map->phys_map' 's32min-s32max'

KVM guest can easily trigger this by executing the following assembly sequence 
in Ring0:

mov $10, %rax
mov $0xFFFFFFFF, %rbx
mov $0xFFFFFFFF, %rdx
mov $0, %rsi
vmcall

As this will cause KVM to execute the following code-path:
vmx_handle_exit() -> handle_vmcall() -> kvm_emulate_hypercall() -> kvm_pv_send_ipi()
which will reach out-of-bounds access.

This patch fixes it by adding a check to kvm_pv_send_ipi() against map->max_apic_id, 
ignoring destinations that are not present and delivering the rest. We also check 
whether or not map->phys_map[min + i] is NULL since the max_apic_id is set to the 
max apic id, some phys_map maybe NULL when apic id is sparse, especially kvm 
unconditionally set max_apic_id to 255 to reserve enough space for any xAPIC ID.

Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * add min > map->max_apic_id check
 * change min to u32
 * add min((u32)BITS_PER_LONG, (map->max_apic_id - min + 1))

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/lapic.c            | 23 ++++++++++++++++-------
 2 files changed, 17 insertions(+), 8 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Fix loss of pending IRQ/NMI before entering L2
##### From: Liran Alon <liran.alon@oracle.com>

```c
Consider the case L1 had a IRQ/NMI event until it executed
VMLAUNCH/VMRESUME which wasn't delivered because it was disallowed
(e.g. interrupts disabled). When L1 executes VMLAUNCH/VMRESUME,
L0 needs to evaluate if this pending event should cause an exit from
L2 to L1 or delivered directly to L2 (e.g. In case L1 don't intercept
EXTERNAL_INTERRUPT).

Usually this would be handled by L0 requesting a IRQ/NMI window
by setting VMCS accordingly. However, this setting was done on
VMCS01 and now VMCS02 is active instead. Thus, when L1 executes
VMLAUNCH/VMRESUME we force L0 to perform pending event evaluation by
requesting a KVM_REQ_EVENT.

Note that above scenario exists when L1 KVM is about to enter L2 but
requests an "immediate-exit". As in this case, L1 will
disable-interrupts and then send a self-IPI before entering L2.

Co-authored-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 25 ++++++++++++++++++++++++-
 1 file changed, 24 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: Remove CREATE_IRQCHIP/SET_PIT2 raceFrom: Peter Shier <pshier@google.com>
##### From: Peter Shier <pshier@google.com>

```c
From: Steve Rutherford <srutherford@google.com>

Fixes a NULL pointer dereference, caused by the PIT firing an interrupt
before the interrupt table has been initialized.

SET_PIT2 can race with the creation of the IRQchip. In particular,
if SET_PIT2 is called with a low PIT timer period (after the creation of
the IOAPIC, but before the instantiation of the irq routes), the PIT can
fire an interrupt at an uninitialized table.

Signed-off-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [RFC PATCH v2 01/10] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, all DMA requests out of or to a subset of
a physical PCI device can be protected by the IOMMU. As a
result, there is a request in software to attach multiple
domains to a physical PCI device. One example of such use
model is the Intel Scalable IOV [1] [2]. The Intel vt-d
3.0 spec [3] introduces the scalable mode which enables
PASID granularity DMA isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs includes:

* iommu_capable(IOMMU_CAP_AUX_DOMAIN)
  - Represents the ability of supporting multiple domains
    per device.

* iommu_en(dis)able_aux_domain(struct device *dev)
  - Enable/disable the multiple domains capability for a
    device referenced by @dev.

* iommu_auxiliary_id(struct iommu_domain *domain)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalalbe IOV needs
    to writes this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

Many people involved in discussions of this design. They're

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

and some discussions can be found here [4].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 29 +++++++++++++++++++++++++++++
 include/linux/iommu.h | 13 +++++++++++++
 2 files changed, 42 insertions(+)

```
