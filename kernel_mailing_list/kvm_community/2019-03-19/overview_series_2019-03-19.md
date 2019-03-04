#### [PATCH 1/3] KVM: PPC: Implement kvmppc_copy_guest() to perform in place copy of guest memory
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Implement the function kvmppc_copy_guest() to be used to perform a memory
copy from one guest physical address to another of a variable length.

This performs similar functionality as the kvm_read_guest() and
kvm_write_guest() functions, except both addresses point to guest memory.
This performs a copy in place using raw_copy_in_user() to avoid having to
buffer the data.

The guest memory can reside in different memslots and the copy length
can span memslots.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 69 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 69 insertions(+)

```
#### [PATCH 1/3][KVM nVMX]: Check "load IA32_PAT" VM-exit control on vmentry of L2 guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on Host Control Registers and MSRs" in Intel
SDM vol 3C, the following check is performed on vmentry of L2 guests:

    If the "load IA32_PAT" VM-exit control is 1, the value of the field
    for the IA32_PAT MSR must be one that could be written by WRMSR
    without fault at CPL 0. Specifically, each of the 8 bytes in the
    field must have one of the values 0 (UC), 1 (WC), 4 (WT), 5 (WP),
    6 (WB), or 7 (UC-).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 24 ++++++++++++++++++++++++
 1 file changed, 24 insertions(+)

```
#### [PATCH 1/9] vfio/mdev: add .request callback
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
This will allow the hotplug to be enabled for mediated devices

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 drivers/vfio/mdev/vfio_mdev.c | 11 +++++++++++
 include/linux/mdev.h          |  4 ++++
 2 files changed, 15 insertions(+)

```
#### [PATCH 1/2] KVM: arm/arm64: vgic-its: Take the srcu lock when writing to guest memory
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
When halting a guest, QEMU flushes the virtual ITS caches, which
amounts to writing to the various tables that the guest has allocated.

When doing this, we fail to take the srcu lock, and the kernel
shouts loudly if running a lockdep kernel:

[   69.680416] =============================
[   69.680819] WARNING: suspicious RCU usage
[   69.681526] 5.1.0-rc1-00008-g600025238f51-dirty #18 Not tainted
[   69.682096] -----------------------------
[   69.682501] ./include/linux/kvm_host.h:605 suspicious rcu_dereference_check() usage!
[   69.683225]
[   69.683225] other info that might help us debug this:
[   69.683225]
[   69.683975]
[   69.683975] rcu_scheduler_active = 2, debug_locks = 1
[   69.684598] 6 locks held by qemu-system-aar/4097:
[   69.685059]  #0: 0000000034196013 (&kvm->lock){+.+.}, at: vgic_its_set_attr+0x244/0x3a0
[   69.686087]  #1: 00000000f2ed935e (&its->its_lock){+.+.}, at: vgic_its_set_attr+0x250/0x3a0
[   69.686919]  #2: 000000005e71ea54 (&vcpu->mutex){+.+.}, at: lock_all_vcpus+0x64/0xd0
[   69.687698]  #3: 00000000c17e548d (&vcpu->mutex){+.+.}, at: lock_all_vcpus+0x64/0xd0
[   69.688475]  #4: 00000000ba386017 (&vcpu->mutex){+.+.}, at: lock_all_vcpus+0x64/0xd0
[   69.689978]  #5: 00000000c2c3c335 (&vcpu->mutex){+.+.}, at: lock_all_vcpus+0x64/0xd0
[   69.690729]
[   69.690729] stack backtrace:
[   69.691151] CPU: 2 PID: 4097 Comm: qemu-system-aar Not tainted 5.1.0-rc1-00008-g600025238f51-dirty #18
[   69.691984] Hardware name: rockchip evb_rk3399/evb_rk3399, BIOS 2019.04-rc3-00124-g2feec69fb1 03/15/2019
[   69.692831] Call trace:
[   69.694072]  lockdep_rcu_suspicious+0xcc/0x110
[   69.694490]  gfn_to_memslot+0x174/0x190
[   69.694853]  kvm_write_guest+0x50/0xb0
[   69.695209]  vgic_its_save_tables_v0+0x248/0x330
[   69.695639]  vgic_its_set_attr+0x298/0x3a0
[   69.696024]  kvm_device_ioctl_attr+0x9c/0xd8
[   69.696424]  kvm_device_ioctl+0x8c/0xf8
[   69.696788]  do_vfs_ioctl+0xc8/0x960
[   69.697128]  ksys_ioctl+0x8c/0xa0
[   69.697445]  __arm64_sys_ioctl+0x28/0x38
[   69.697817]  el0_svc_common+0xd8/0x138
[   69.698173]  el0_svc_handler+0x38/0x78
[   69.698528]  el0_svc+0x8/0xc

The fix is to obviously take the srcu lock, just like we do on the
read side of things since bf308242ab98. One wonders why this wasn't
fixed at the same time, but hey...

Fixes: bf308242ab98 ("KVM: arm/arm64: VGIC/ITS: protect kvm_read_guest() calls with SRCU lock")
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_mmu.h   | 11 +++++++++++
 arch/arm64/include/asm/kvm_mmu.h | 11 +++++++++++
 virt/kvm/arm/vgic/vgic-its.c     |  8 ++++----
 3 files changed, 26 insertions(+), 4 deletions(-)

```
#### [PATCH] kvm: arm: Fix handling of stage2 huge mappings
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
Cc: Zhengui Yu <yuzenghui@huawei.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 virt/kvm/arm/mmu.c | 63 ++++++++++++++++++++++++++++++++++++++----------------
 1 file changed, 45 insertions(+), 18 deletions(-)

```
#### [patch] kvm: svm: fix potential get_num_contig_pages overflow
##### From: David Rientjes <rientjes@google.com>

```c
get_num_contig_pages() could potentially overflow int so make its type 
consistent with its usage.

Reported-by: Cfir Cohen <cfir@google.com>
Signed-off-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)
```
#### 
##### 

```c
```
