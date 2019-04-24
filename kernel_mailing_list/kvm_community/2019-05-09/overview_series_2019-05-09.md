#### [PATCH 1/3] KVM: LAPIC: Extract adaptive tune timer advancement logic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Extract adaptive tune timer advancement logic to a single function.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 57 ++++++++++++++++++++++++++++++----------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [RFC PATCH V2] vhost: don't use kmap() to log dirty pages
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost log dirty pages directly to a userspace bitmap through GUP and
kmap_atomic() since kernel doesn't have a set_bit_to_user()
helper. This will cause issues for the arch that has virtually tagged
caches. The way to fix is to keep using userspace virtual
address. Fortunately, futex has arch_futex_atomic_op_inuser() which
could be used for setting a bit to user.

Note:
- There're archs (few non popular ones) that don't implement futex
  helper, we can't log dirty pages. We can fix them e.g for non
  virtually tagged archs implement a kmap fallback on top or simply
  disable LOG_ALL features of vhost.
- The helper also requires userspace pointer is located at 4-byte
  boundary, need to check during dirty log setting

Cc: Christoph Hellwig <hch@infradead.org>
Cc: James Bottomley <James.Bottomley@HansenPartnership.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Darren Hart <dvhart@infradead.org>
Fixes: 3a4d5c94e9593 ("vhost_net: a kernel-level virtio server")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
Changes from V1:
- switch to use arch_futex_atomic_op_inuser()
---
 drivers/vhost/vhost.c | 35 +++++++++++++++++------------------
 1 file changed, 17 insertions(+), 18 deletions(-)

```
#### [PATCH 1/4][kvm-unit-test nVMX]: Rename guest_pat_main to guest_state_test_main
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
...so that it can be re-used by other tests.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 x86/vmx_tests.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: Remove useless checks in 'release' method of KVM device
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
There is no need to test for the device pointer validity when releasing
a KVM device. The file descriptor should identify it safely.

Fixes: 2bde9b3ec8bd ("KVM: Introduce a 'release' method for KVM devices")
Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---

 Changes since v1:

 - better commit log title.
 
 virt/kvm/kvm_main.c | 6 ------
 1 file changed, 6 deletions(-)

```
#### [PATCH v2] [next] KVM: lapic: allow set apic debug dynamically
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
There are many functions invoke apic_debug(), which is defined
a null function by default, and that's incovenient for debuging
lapic.

This patch allows setting apic debug according to add a apic_dbg
parameter of kvm.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
v2: change apic_dbg to bool and tag __read_mostly. Thanks to Sean.

 arch/x86/kvm/lapic.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
