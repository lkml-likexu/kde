#### [PATCH net 1/4] vhost: make sure used idx is seen before log in vhost_add_used_n()
##### From: Jason Wang <jasowang@redhat.com>

```c
We miss a write barrier that guarantees used idx is updated and seen
before log. This will let userspace sync and copy used ring before
used idx is update. Fix this by adding a barrier before log_write().

Fixes: 8dd014adfea6f ("vhost-net: mergeable buffers support")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH V2 1/8] KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
The kvm capability KVM_CAP_SPAPR_TCE_VFIO is used to indicate the
availability of in kernel tce acceleration for vfio. However it is
currently the case that this is only available on a powernv machine,
not for a pseries machine.

Thus make this capability dependent on having the cpu feature
CPU_FTR_HVMODE.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/powerpc.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH v9 1/7] xen/pvh: Split CONFIG_XEN_PVH into CONFIG_PVH and CONFIG_XEN_PVH
##### From: Maran Wilson <maran.wilson@oracle.com>

```c
In order to pave the way for hypervisors other than Xen to use the PVH
entry point for VMs, we need to factor the PVH entry code into Xen specific
and hypervisor agnostic components. The first step in doing that, is to
create a new config option for PVH entry that can be enabled
independently from CONFIG_XEN.

Signed-off-by: Maran Wilson <maran.wilson@oracle.com>
Reviewed-by: Juergen Gross <jgross@suse.com>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/Kconfig          | 6 ++++++
 arch/x86/kernel/head_64.S | 2 +-
 arch/x86/xen/Kconfig      | 3 ++-
 3 files changed, 9 insertions(+), 2 deletions(-)

```
#### [PATCH] target/i386/kvm.c: Don't mark cpuid_data as QEMU_PACKED
##### From: Peter Maydell <peter.maydell@linaro.org>

```c
clang complains about taking the address of a packed
member of a struct:

target/i386/kvm.c:1245:27: warning: taking address of packed member 'cpuid' of class or structure '' may result in an unaligned pointer value [-Waddress-of-packed-member]
    c = cpuid_find_entry(&cpuid_data.cpuid, 1, 0);
                          ^~~~~~~~~~~~~~~~
target/i386/kvm.c:1297:31: warning: taking address of packed member 'cpuid' of class or structure '' may result in an unaligned pointer value [-Waddress-of-packed-member]
        c = cpuid_find_entry(&cpuid_data.cpuid, kvm_base, 0);
                              ^~~~~~~~~~~~~~~~

The kernel's definitions of struct kvm_cpuid2 and struct
kvm_cpuid_entry2 are carefully set up with padding fields
so that there is no between-struct padding anyway, so
the QEMU_PACKED annotation is unnecessary and might result
in the compiler generating worse code. Drop it, and instead
assert at build time that there is no stray padding.

Signed-off-by: Peter Maydell <peter.maydell@linaro.org>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
---
 target/i386/kvm.c | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)

```
#### [PATCH 01/52] fuse: add skeleton virtio_fs.ko module
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
From: Stefan Hajnoczi <stefanha@redhat.com>

Add a basic file system module for virtio-fs.

Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 fs/fuse/Kconfig     | 10 ++++++++++
 fs/fuse/Makefile    |  1 +
 fs/fuse/virtio_fs.c | 33 +++++++++++++++++++++++++++++++++
 3 files changed, 44 insertions(+)
 create mode 100644 fs/fuse/virtio_fs.c

```
#### [PATCH 1/2] x86: kvm: hyperv: simplify SynIC message deliveryThread-Topic: [PATCH 1/2] x86: kvm: hyperv: simplify SynIC message delivery
##### From: Roman Kagan <rkagan@virtuozzo.com>

```c
SynIC message delivery is somewhat overengineered: it pretends to follow
the ordering rules when grabbing the message slot, using atomic
operations and all that, but does it incorrectly and unnecessarily.

The correct order would be to first set .msg_pending, then atomically
replace .message_type if it was zero, and then clear .msg_pending if
the previous step was successful.  But this all is done in vcpu context
so the whole update looks atomic to the guest (it's assumed to only
access the message page from this cpu), and therefore can be done in
whatever order is most convenient (and is also the reason why the
incorrect order didn't trigger any bugs so far).

While at this, also switch to kvm_vcpu_{read,write}_guest_page, and drop
the no longer needed synic_clear_sint_msg_pending.

Signed-off-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/kvm/hyperv.c | 100 ++++++++++++++++++------------------------
 1 file changed, 42 insertions(+), 58 deletions(-)

```
#### [PATCH v2 1/7] x86/hyper-v: Do some housekeeping in hyperv-tlfs.h
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
hyperv-tlfs.h is a bit messy: CPUID feature bits are not always sorted,
it's hard to get which CPUID they belong to, some items are duplicated
(e.g. HV_X64_MSR_CRASH_CTL_NOTIFY/HV_CRASH_CTL_CRASH_NOTIFY).

Do some housekeeping work. While on it, replace all (1 << X) with BIT(X)
macro.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
---
 arch/x86/include/asm/hyperv-tlfs.h | 186 ++++++++++++++---------------
 arch/x86/kvm/hyperv.c              |   4 +-
 2 files changed, 93 insertions(+), 97 deletions(-)

```
