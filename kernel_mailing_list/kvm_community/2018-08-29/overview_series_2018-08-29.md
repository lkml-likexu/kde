#### [PATCH v5 11/16] x86/kvm: enable Hygon support to KVM infrastructure
##### From: Pu Wen <puwen@hygon.cn>

```c
Hygon Dhyana CPU has the SVM feature as AMD family 17h does.
Add Hygon support in the KVM infrastructure.

Signed-off-by: Pu Wen <puwen@hygon.cn>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/kvm_emulate.h |  4 ++++
 arch/x86/include/asm/virtext.h     |  5 +++--
 arch/x86/kvm/emulate.c             | 11 ++++++++++-
 3 files changed, 17 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: LAPIC: Fix pv ipis out-of-bounds access
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

This patch fixes it by adding a check to kvm_pv_send_ipi() against map->max_apic_id 
and also checking whether or not map->phys_map[min + i] is NULL since the max_apic_id 
is set according to the max apic id, however, some phys_map maybe NULL when apic id 
is sparse, in addition, kvm also unconditionally set max_apic_id to 255 to reserve 
enough space for any xAPIC ID.

Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 17 +++++++++++++----
 1 file changed, 13 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: LAPIC: Fix pv ipis out-of-bounds access
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

This patch fixes it by adding a check to kvm_pv_send_ipi() against map->max_apic_id 
and also checking whether or not map->phys_map[min + i] is NULL since the max_apic_id 
is set according to the max apic id, however, some phys_map maybe NULL when apic id 
is sparse, in addition, kvm also unconditionally set max_apic_id to 255 to reserve 
enough space for any xAPIC ID.

Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-By: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/lapic.c | 17 +++++++++++++----
 1 file changed, 13 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: nVMX: Fix loss of pending event before entering L2
##### From: Liran Alon <liran.alon@oracle.com>

```c
Consider the case L1 had a pending event until it executed
VMLAUNCH/VMRESUME which wasn't delivered because it was disallowed
(e.g. interrupts disabled). When L1 executes VMLAUNCH/VMRESUME,
L0 needs to evaluate if this pending event should cause an exit from
L2 to L1 or delivered directly to L2 (In case L1 don't intercept
EXTERNAL_INTERRUPT).

Usually this would be handled by L0 requesting a window (e.g. IRQ
window) by setting VMCS accordingly. However, this setting was done on
VMCS01 and now VMCS02 is active instead. Thus, when L1 executes
VMLAUNCH/VMRESUME we force L0 to perform pending event evaluation by
requesting a KVM_REQ_EVENT.

Note that above scenario exists when L1 KVM is about to enter L2 but
requests an "immediate-exit". As in this case, L1 will
disable-interrupts and then send a self-IPI before entering L2.

Signed-off-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [PATCH kvm-unit-tests] x86: apic: pv ipis out-of-bounds access testing
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Adds pv ipis out-of-bounds acess testing. 

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-By: Liran Alon <liran.alon@oracle.com>
---
 x86/apic.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH 1/2] kvm: x86: propagate KVM_GET/SET_MSRS failures to userspace
##### From: Peter Shier <pshier@google.com>

```c
These IOCTLs return the number of MSRS successfully read/written but lose
error info in case of failure. Rename kvm_msrs.pad to kvm_msrs.errno and
use it to return cause of first failure.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 Documentation/virtual/kvm/api.txt | 12 +++++++++---
 arch/x86/include/uapi/asm/kvm.h   |  2 +-
 arch/x86/kvm/x86.c                | 26 +++++++++++++++++---------
 3 files changed, 27 insertions(+), 13 deletions(-)

```
#### [PATCH RFC] migration: make sure to run iterate precopy during the bulk stage
##### From: Quan Xu <quan.xu0@gmail.com>

```c
From 8dbf7370e7ea1caab0b769d0d4dcdd072d14d421 Mon Sep 17 00:00:00 2001
From: Quan Xu <quan.xu0@gmail.com>
Date: Wed, 29 Aug 2018 21:33:14 +0800
Subject: [PATCH RFC] migration: make sure to run iterate precopy during the
  bulk stage

Since the bulk stage assumes in (migration_bitmap_find_dirty) that every
page is dirty, return a rough total ram as pending size to make sure that
migration thread continues to run iterate precopy during the bulk stage.

Otherwise the downtime grows unpredictably, as migration thread needs to
send both the rest of pages and dirty pages during complete precopy.

Signed-off-by: Quan Xu <quan.xu0@gmail.com>
---
  migration/ram.c | 3 ++-
  1 file changed, 2 insertions(+), 1 deletion(-)


--
1.8.3.1

```
#### [kvm-unit-tests PATCH v2 1/5] s390x: user ctl_set/clear_bit for low address protection
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
#### [PATCH v2] x86: apic: pv ipis out-of-bounds access testing
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

This patch adds the testcase to kvm-unit-tests.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Reviewed-By: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * add more changelog
 * arguments are documented in Documentation/virtual/kvm/hypercalls.txt
 * Define KVM_HC_SEND_IPI instead of using hard-coded

 x86/apic.c | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [PATCH v3 1/4] x86/mm: Restructure sme_encrypt_kernel()
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Re-arrange the sme_encrypt_kernel() by moving the workarea map/unmap
logic in a separate static function. There are no logical changes in this
patch. The restructuring will allow us to expand the sme_encrypt_kernel
in future.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: kvm@vger.kernel.org
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
---
 arch/x86/mm/mem_encrypt_identity.c | 160 ++++++++++++++++++++++++-------------
 1 file changed, 104 insertions(+), 56 deletions(-)

```
