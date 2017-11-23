#### [PATCH 1/7] vfio/sdmdev: Add documents for WarpDrive framework
##### From: Kenneth Lee <nek.in.cn@gmail.com>

```c
From: Kenneth Lee <liguozhu@hisilicon.com>

WarpDrive is a common user space accelerator framework.  Its main component
in Kernel is called sdmdev, Share Domain Mediated Device. It exposes
the hardware capabilities to the user space via vfio-mdev. So processes in
user land can obtain a "queue" by open the device and direct access the
hardware MMIO space or do DMA operation via VFIO interface.

WarpDrive is intended to be used with Jean Philippe Brucker's SVA
patchset to support multi-process. But This is not a must.  Without the
SVA patches, WarpDrive can still work for one process for every hardware
device.

This patch add detail documents for the framework.

Signed-off-by: Kenneth Lee <liguozhu@hisilicon.com>
---
 Documentation/00-INDEX                |   2 +
 Documentation/warpdrive/warpdrive.rst | 100 ++++
 Documentation/warpdrive/wd-arch.svg   | 728 ++++++++++++++++++++++++++
 3 files changed, 830 insertions(+)
 create mode 100644 Documentation/warpdrive/warpdrive.rst
 create mode 100644 Documentation/warpdrive/wd-arch.svg

```
#### [PATCH kvm-unit-tests] scripts: Speedup MAX_SMP check
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
The current MAX_SMP check launches QEMU for every value of the SMP
parameter to check if the SMP parameter based on the native is higher
than the QEMU maximum supported configuration.

On something like a TX2, which has 224 threads, this takes a very long
time where the test script just sits there with no output.

Reduce the wait time by taking the log2 of MAX_SMP in each iteration of
the loop instead.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: don't reset root in kvm_mmu_setup()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Here is the code path which shows kvm_mmu_setup() is invoked after
kvm_mmu_create(). Since kvm_mmu_setup() is only invoked in this code path,
this means the root_hpa and prev_roots are setup properly. And it is not
necessary to reset it again.

    kvm_vm_ioctl_create_vcpu()
        kvm_arch_vcpu_create()
            vmx_create_vcpu()
                kvm_vcpu_init()
                    kvm_arch_vcpu_init()
                        kvm_mmu_create()
        kvm_arch_vcpu_setup()
            kvm_mmu_setup()
                kvm_init_mmu()

This patch set reset_roots to false in kmv_mmu_setup().

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v5 1/4] migration: do not flush_compressed_data at the end of each iteration
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

flush_compressed_data() needs to wait all compression threads to
finish their work, after that all threads are free until the
migration feeds new request to them, reducing its call can improve
the throughput and use CPU resource more effectively

We do not need to flush all threads at the end of iteration, the
data can be kept locally until the memory block is changed or
memory migration starts over in that case we will meet a dirtied
page which may still exists in compression threads's ring

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 migration/ram.c | 14 +++++++++++++-
 1 file changed, 13 insertions(+), 1 deletion(-)

```
#### [PULL 1/4] KVM: arm/arm64: Clean dcache to PoC when changing PTE due to CoW
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
From: Marc Zyngier <marc.zyngier@arm.com>

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
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 virt/kvm/arm/mmu.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v2 1/2] arm/arm64: add GICD_IIDR definition
##### From: Andrew Jones <drjones@redhat.com>

```c
From: Shih-Wei Li <shihwei@cs.columbia.edu>

Signed-off-by: Shih-Wei Li <shihwei@cs.columbia.edu>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm/asm/gic.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3] KVM: nVMX: Fix loss of pending IRQ/NMI before entering L2
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

Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Co-developed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 22 ++++++++++++++++++++++
 1 file changed, 22 insertions(+)

```
#### [PATCH] vhost: fix VHOST_GET_BACKEND_FEATURES ioctl request definition
##### From: Gleb Fotengauer-Malinovskiy <glebfm@altlinux.org>

```c
The _IOC_READ flag fits this ioctl request more because this request
actually only writes to, but doesn't read from userspace.
See NOTEs in include/uapi/asm-generic/ioctl.h for more information.

Fixes: 429711aec282 ("vhost: switch to use new message format")
Signed-off-by: Gleb Fotengauer-Malinovskiy <glebfm@altlinux.org>
Acked-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 include/uapi/linux/vhost.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
