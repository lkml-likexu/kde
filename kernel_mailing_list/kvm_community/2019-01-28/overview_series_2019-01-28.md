#### [PATCH 1/2] kvm: x86: IA32_ARCH_CAPABILITIES is only emulated for Intel
##### From: Jim Mattson <jmattson@google.com>

```c
This MSR is not emulated on AMD hosts.

Fixes: 1eaafe91a0df ("kvm: x86: IA32_ARCH_CAPABILITIES is always supported")
Reported-by: Eduardo Habkost <ehabkost@redhat.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Tested-by: Eduardo Habkost <ehabkost@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 3 ++-
 arch/x86/kvm/cpuid.c            | 7 +------
 arch/x86/kvm/svm.c              | 3 ++-
 arch/x86/kvm/vmx/vmx.c          | 9 ++++++++-
 4 files changed, 13 insertions(+), 9 deletions(-)

```
#### [PATCH] cpu/hotplug: Fix "SMT disabled by BIOS" detection for KVM
##### From: Josh Poimboeuf <jpoimboe@redhat.com>

```c
With the following commit:

  73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")

... the hotplug code attempted to detect when SMT was disabled by BIOS,
in which case it reported SMT as permanently disabled.  However, that
code broke a virt hotplug scenario, where the guest is booted with only
primary CPU threads, and a sibling is brought online later.

The problem is that there doesn't seem to be a way to reliably
distinguish between the HW "SMT disabled by BIOS" case and the virt
"sibling not yet brought online" case.  So the above-mentioned commit
was a bit misguided, as it permanently disabled SMT for both cases,
preventing future virt sibling hotplugs.

Going back and reviewing the original problems which were attempted to
be solved by that commit, when SMT was disabled in BIOS:

  1) /sys/devices/system/cpu/smt/control showed "on" instead of
     "notsupported"; and

  2) vmx_vm_init() was incorrectly showing the L1TF_MSG_SMT warning.

I'd propose that we instead consider #1 above to not actually be a
problem.  Because, at least in the virt case, it's possible that SMT
wasn't disabled by BIOS and a sibling thread could be brought online
later.  So it makes sense to just always default the smt control to "on"
to allow for that possibility (assuming cpuid indicates that the CPU
supports SMT).

The real problem is #2, which has a simple fix: change vmx_vm_init() to
query the actual current SMT state -- i.e., whether any siblings are
currently online -- instead of looking at the SMT "control" sysfs value.

So fix it by:

  a) reverting the original "fix" and its followup fix:

     73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")
     bc2d8d262cba ("cpu/hotplug: Fix SMT supported evaluation")

     and

  b) changing vmx_vm_init() to query the actual current SMT state --
     instead of the sysfs control value -- to determine whether the L1TF
     warning is needed.

Fixes: 73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")
Reported-by: Igor Mammedov <imammedo@redhat.com>
Signed-off-by: Josh Poimboeuf <jpoimboe@redhat.com>
---
 arch/x86/kernel/cpu/bugs.c |  2 +-
 arch/x86/kvm/vmx/vmx.c     |  3 ++-
 include/linux/cpu.h        |  2 --
 kernel/cpu.c               | 32 ++++----------------------------
 kernel/smp.c               |  2 --
 5 files changed, 7 insertions(+), 34 deletions(-)

```
#### [PATCH] KVM: Ignore LBR MSRs with no effect
##### From: Anton Kuchin <antonkuchin@yandex-team.ru>

```c
Win10 attempts to save these registers during KiSaveDebugRegisterState
if LBR or BTF bits are set in MSR_IA32_DEBUGCTLMSR. It uses DR7 GE and LE
flags for per-thread switching of these these features so zero value that
is returned for MSR_IA32_DEBUGCTLMSR has no effect.

These registers are used for debugging and shouldn't cause #GP and
guest crash so just return zeroes just like we do for common x86 LBR
MSRs (DEBUGCTLMSR, LAST[BRANCH|INT][TO|FROM]IP).

Signed-off-by: Anton Kuchin <antonkuchin@yandex-team.ru>
---
 arch/x86/kvm/vmx/vmx.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH 1/3] KVM: x86: Move mmu_memory_cache functions to common code
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
We are currently duplicating the mmu memory cache functionality quite
heavily between the architectures that support KVM.  As a first step,
move the x86 implementation (which seems to have the most recently
maintained version of the mmu memory cache) to common code.

We rename the functions and data types to have a kvm_ prefix for
anything exported as a symbol to the rest of the kernel and take the
chance to rename memory_cache to memcache to avoid overly long lines.
This is a bit tedious on the callsites but ends up looking more
palatable.

We also introduce an arch-specific kvm_types.h which can be used to
define the architecture-specific GFP flags for allocating memory to the
memory cache, and to specify how many objects are required in the memory
cache.  These are the two points where the current implementations
diverge across architectures.  Since kvm_host.h defines structures with
fields of the memcache object, we define the memcache structure in
kvm_types.h, and we include the architecture-specific kvm_types.h to
know the size of object in kvm_host.h.

This patch currently only defines the structure and requires valid
defines in the architecture-specific kvm_types.h when KVM_NR_MEM_OBJS is
defined.  As we move each architecture to the common implementation,
this condition will eventually go away.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/include/asm/kvm_types.h     |  5 ++
 arch/arm64/include/asm/kvm_types.h   |  6 ++
 arch/mips/include/asm/kvm_types.h    |  5 ++
 arch/powerpc/include/asm/kvm_types.h |  5 ++
 arch/s390/include/asm/kvm_types.h    |  5 ++
 arch/x86/include/asm/kvm_host.h      | 17 +----
 arch/x86/include/asm/kvm_types.h     | 10 +++
 arch/x86/kvm/mmu.c                   | 97 ++++++----------------------
 arch/x86/kvm/paging_tmpl.h           |  4 +-
 include/linux/kvm_host.h             |  9 +++
 include/linux/kvm_types.h            | 12 ++++
 virt/kvm/kvm_main.c                  | 58 +++++++++++++++++
 12 files changed, 139 insertions(+), 94 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_types.h
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h

diff --git a/arch/arm/include/asm/kvm_types.h b/arch/arm/include/asm/kvm_types.h
new file mode 100644
index 000000000000..bc389f82e88d
--- /dev/null
+++ b/arch/arm/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_ARM_KVM_TYPES_H
+#define _ASM_ARM_KVM_TYPES_H
+
+#endif /* _ASM_ARM_KVM_TYPES_H */
diff --git a/arch/arm64/include/asm/kvm_types.h b/arch/arm64/include/asm/kvm_types.h
new file mode 100644
index 000000000000..d0987007d581
--- /dev/null
+++ b/arch/arm64/include/asm/kvm_types.h
@@ -0,0 +1,6 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_ARM64_KVM_TYPES_H
+#define _ASM_ARM64_KVM_TYPES_H
+
+#endif /* _ASM_ARM64_KVM_TYPES_H */
+
diff --git a/arch/mips/include/asm/kvm_types.h b/arch/mips/include/asm/kvm_types.h
new file mode 100644
index 000000000000..5efeb32a5926
--- /dev/null
+++ b/arch/mips/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_MIPS_KVM_TYPES_H
+#define _ASM_MIPS_KVM_TYPES_H
+
+#endif /* _ASM_MIPS_KVM_TYPES_H */
diff --git a/arch/powerpc/include/asm/kvm_types.h b/arch/powerpc/include/asm/kvm_types.h
new file mode 100644
index 000000000000..f627eceaa314
--- /dev/null
+++ b/arch/powerpc/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_POWERPC_KVM_TYPES_H
+#define _ASM_POWERPC_KVM_TYPES_H
+
+#endif /* _ASM_POWERPC_KVM_TYPES_H */
diff --git a/arch/s390/include/asm/kvm_types.h b/arch/s390/include/asm/kvm_types.h
new file mode 100644
index 000000000000..b66a81f8a354
--- /dev/null
+++ b/arch/s390/include/asm/kvm_types.h
@@ -0,0 +1,5 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ASM_S390_KVM_TYPES_H
+#define _ASM_S390_KVM_TYPES_H
+
+#endif /* _ASM_S390_KVM_TYPES_H */
```
#### [PATCH] KVM: x86: Fix a 4.14 backport regression related to userspace/guest FPU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Upstream commit:

    f775b13eedee ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")

introduced a bug, which was later fixed by upstream commit:

    5663d8f9bbe4 ("kvm: x86: fix WARN due to uninitialized guest FPU state")

For reasons unknown, both commits were initially passed-over for
inclusion in the 4.14 stable branch despite being tagged for stable.
Eventually, someone noticed that the fixup, commit 5663d8f9bbe4, was
missing from stable[1], and so it was queued up for 4.14 and included in
release v4.14.79.

Even later, the original buggy patch, commit f775b13eedee, was also
applied to the 4.14 stable branch.  Through an unlucky coincidence, the
incorrect ordering did not generate a conflict between the two patches,
and led to v4.14.94 and later releases containing a spurious call to
kvm_load_guest_fpu() in kvm_arch_vcpu_ioctl_run().  As a result, KVM may
reload stale guest FPU state, e.g. after accepting in INIT event.  This
can manifest as crashes during boot, segfaults, failed checksums and so
on and so forth.

Remove the unwanted kvm_{load,put}_guest_fpu() calls, i.e. make
kvm_arch_vcpu_ioctl_run() look like commit 5663d8f9bbe4 was backported
after commit f775b13eedee.

[1] https://www.spinics.net/lists/stable/msg263931.html

Fixes: 4124a4cff344 ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")
Cc: stable@vger.kernel.org
Cc: Sasha Levin <sashal@kernel.org>
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Peter Xu <peterx@redhat.com>
Cc: Rik van Riel <riel@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Reported-by: Roman Mamedov
Reported-by: Thomas Lindroth <thomas.lindroth@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH net] vhost: fix OOB in get_rx_bufs()
##### From: Jason Wang <jasowang@redhat.com>

```c
After batched used ring updating was introduced in commit e2b3b35eb989
("vhost_net: batch used ring update in rx"). We tend to batch heads in
vq->heads for more than one packet. But the quota passed to
get_rx_bufs() was not correctly limited, which can result a OOB write
in vq->heads.

        headcount = get_rx_bufs(vq, vq->heads + nvq->done_idx,
                    vhost_len, &in, vq_log, &log,
                    likely(mergeable) ? UIO_MAXIOV : 1);

UIO_MAXIOV was still used which is wrong since we could have batched
used in vq->heads, this will cause OOB if the next buffer needs more
than 960 (1024 (UIO_MAXIOV) - 64 (VHOST_NET_BATCH)) heads after we've
batched 64 (VHOST_NET_BATCH) heads:
Acked-by: Stefan Hajnoczi <stefanha@redhat.com>

=============================================================================
BUG kmalloc-8k (Tainted: G    B            ): Redzone overwritten
-----------------------------------------------------------------------------

INFO: 0x00000000fd93b7a2-0x00000000f0713384. First byte 0xa9 instead of 0xcc
INFO: Allocated in alloc_pd+0x22/0x60 age=3933677 cpu=2 pid=2674
    kmem_cache_alloc_trace+0xbb/0x140
    alloc_pd+0x22/0x60
    gen8_ppgtt_create+0x11d/0x5f0
    i915_ppgtt_create+0x16/0x80
    i915_gem_create_context+0x248/0x390
    i915_gem_context_create_ioctl+0x4b/0xe0
    drm_ioctl_kernel+0xa5/0xf0
    drm_ioctl+0x2ed/0x3a0
    do_vfs_ioctl+0x9f/0x620
    ksys_ioctl+0x6b/0x80
    __x64_sys_ioctl+0x11/0x20
    do_syscall_64+0x43/0xf0
    entry_SYSCALL_64_after_hwframe+0x44/0xa9
INFO: Slab 0x00000000d13e87af objects=3 used=3 fp=0x          (null) flags=0x200000000010201
INFO: Object 0x0000000003278802 @offset=17064 fp=0x00000000e2e6652b

Fixing this by allocating UIO_MAXIOV + VHOST_NET_BATCH iovs for
vhost-net. This is done through set the limitation through
vhost_dev_init(), then set_owner can allocate the number of iov in a
per device manner.

This fixes CVE-2018-16880.

Fixes: e2b3b35eb989 ("vhost_net: batch used ring update in rx")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/net.c   | 3 ++-
 drivers/vhost/scsi.c  | 2 +-
 drivers/vhost/vhost.c | 7 ++++---
 drivers/vhost/vhost.h | 4 +++-
 drivers/vhost/vsock.c | 2 +-
 5 files changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH RESEND] KVM: MMU: Introduce single thread to zap collapsible sptes
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Last year guys from huawei reported that the call of memory_global_dirty_log_start/stop() 
takes 13s for 4T memory and cause guest freeze too long which increases the unacceptable 
migration downtime. [1] [2]

Guangrong pointed out:

| collapsible_sptes zaps 4k mappings to make memory-read happy, it is not
| required by the semanteme of KVM_SET_USER_MEMORY_REGION and it is not
| urgent for vCPU's running, it could be done in a separate thread and use
| lock-break technology.

Several TB memory guest is common now after NVDIMM is deployed in cloud environment.
This patch utilizes worker thread to zap collapsible sptes in order to lazy collapse 
small sptes into large sptes during roll-back after live migration fails.

[1] https://lists.gnu.org/archive/html/qemu-devel/2017-04/msg05249.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg449994.html

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note:
I ever consider to add a list of memslots to be zapped, delete from the list
and add in kvm_mmu_zap_collapsible_sptes(). However, i observe a lot of races 
here, the memslot can disappear/modify underneath before the worker thread
start to zap even if i introduce lock to protect the list. This patch delays 
the worker thread by 60s(to assume memory_global_dirty_log_stop can absolutely 
complete) to coalesce all the zap requirements after live migration fails.

 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/mmu.c              | 37 ++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c              |  4 ++++
 3 files changed, 39 insertions(+), 5 deletions(-)

```
