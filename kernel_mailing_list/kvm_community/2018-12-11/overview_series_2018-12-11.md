#### [PATCH v10 1/8] KVM: arm/arm64: Share common code in user_mem_abort()
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
From: Punit Agrawal <punit.agrawal@arm.com>

The code for operations such as marking the pfn as dirty, and
dcache/icache maintenance during stage 2 fault handling is duplicated
between normal pages and PMD hugepages.

Instead of creating another copy of the operations when we introduce
PUD hugepages, let's share them across the different pagesizes.

Signed-off-by: Punit Agrawal <punit.agrawal@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 virt/kvm/arm/mmu.c | 49 ++++++++++++++++++++++++++++++-------------------
 1 file changed, 30 insertions(+), 19 deletions(-)

```
#### [PATCH] KVM: arm/arm64: Fix VMID alloc race by reverting to lock-less
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
We recently addressed a VMID generation race by introducing a read/write
lock around accesses and updates to the vmid generation values.

However, kvm_arch_vcpu_ioctl_run() also calls need_new_vmid_gen() but
does so without taking the read lock.

As far as I can tell, this can lead to the same kind of race:

  VM 0, VCPU 0			VM 0, VCPU 1
  ------------			------------
  update_vttbr (vmid 254)
  				update_vttbr (vmid 1) // roll over
				read_lock(kvm_vmid_lock);
				force_vm_exit()
  local_irq_disable
  need_new_vmid_gen == false //because vmid gen matches

  enter_guest (vmid 254)
  				kvm_arch.vttbr = <PGD>:<VMID 1>
				read_unlock(kvm_vmid_lock);

  				enter_guest (vmid 1)

Which results in running two VCPUs in the same VM with different VMIDs
and (even worse) other VCPUs from other VMs could now allocate clashing
VMID 254 from the new generation as long as VCPU 0 is not exiting.

Attempt to solve this by making sure vttbr is updated before another CPU
can observe the updated VMID generation.

Cc: stable@vger.kernel.org
Fixes: f0cf47d939d0 "KVM: arm/arm64: Close VMID generation race"
Reviewed-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 virt/kvm/arm/arm.c | 23 +++++++++++------------
 1 file changed, 11 insertions(+), 12 deletions(-)

```
#### [PATCH] KVM: arm/arm64: vgic-v2: Set active_source to 0 when restoring state
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
When restoring the active state from userspace, we don't know which CPU
was the source for the active state, and this is not architecturally
exposed in any of the register state.

Set the active_source to 0 in this case.  In the future, we can expand
on this and exposse the information as additional information to
userspace for GICv2 if anyone cares.

Cc: stable@vger.kernel.org
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 virt/kvm/arm/vgic/vgic-mmio.c | 17 ++++++++++++++++-
 1 file changed, 16 insertions(+), 1 deletion(-)

```
#### [PULL 1/4] x86/cpu: Enable MOVDIRI cpu feature
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
From: Liu Jingqi <jingqi.liu@intel.com>

MOVDIRI moves doubleword or quadword from register to memory through
direct store which is implemented by using write combining (WC) for
writing data directly into memory without caching the data.

The bit definition:
CPUID.(EAX=7,ECX=0):ECX[bit 27] MOVDIRI

The release document ref below link:
https://software.intel.com/sites/default/files/managed/c5/15/\
architecture-instruction-set-extensions-programming-reference.pdf

Cc: Xu Tao <tao3.xu@intel.com>
Signed-off-by: Liu Jingqi <jingqi.liu@intel.com>
Message-Id: <1541488407-17045-2-git-send-email-jingqi.liu@intel.com>
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/cpu.h | 1 +
 target/i386/cpu.c | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] target-i386: Reenable RDTSCP support on Opteron_G[345] CPU models
##### From: Borislav Petkov <bp@alien8.de>

```c
+ qemu-devel.

On Tue, Dec 11, 2018 at 03:30:17PM +0000, Daniel P. Berrangé wrote:
> Great, then, this is a non-issue - we just need to mention that fact
> in the commit that sets the min version for the kernel

Ok, here's a first draft ontop of Eduardo's machine-next branch from
http://github.com/ehabkost/qemu

Also, thanks for the help Eduardo! :-)
---
From: Borislav Petkov <bp@suse.de>
Date: Tue, 11 Dec 2018 17:01:00 +0100

The missing functionality was added ~3 years ago with the Linux commit

  46896c73c1a4 ("KVM: svm: add support for RDTSCP")

so reenable RDTSCP support on those CPU models.

Opteron_G2 - being family 15, model 6, doesn't have RDTSCP support
(the real hardware doesn't have it. K8 got RDTSCP support with the NPT
models, i.e., models >= 0x40).

Document the host's minimum required kernel version, while at it.

Signed-off-by: Borislav Petkov <bp@suse.de>
---
 include/hw/i386/pc.h | 17 +++++++++++++----
 qemu-doc.texi        | 13 +++++++++++++
 target/i386/cpu.c    | 11 ++++-------
 3 files changed, 30 insertions(+), 11 deletions(-)

```
