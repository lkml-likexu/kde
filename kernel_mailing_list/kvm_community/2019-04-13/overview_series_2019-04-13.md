#### [PATCH] KVM: x86/mmu: Fix an inverted list_empty() check when zapping sptes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A recently introduced helper for handling zap vs. remote flush
incorrectly bails early, effectively leaking defunct shadow pages.
Manifests as a slab BUG when exiting KVM due to the shadow pages
being alive when their associated cache is destroyed.

==========================================================================
BUG kvm_mmu_page_header: Objects remaining in kvm_mmu_page_header on ...
--------------------------------------------------------------------------
Disabling lock debugging due to kernel taint
INFO: Slab 0x00000000fc436387 objects=26 used=23 fp=0x00000000d023caee ...
CPU: 6 PID: 4315 Comm: rmmod Tainted: G    B             5.1.0-rc2+ #19
Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS 0.0.0 02/06/2015
Call Trace:
 dump_stack+0x46/0x5b
 slab_err+0xad/0xd0
 ? on_each_cpu_mask+0x3c/0x50
 ? ksm_migrate_page+0x60/0x60
 ? on_each_cpu_cond_mask+0x7c/0xa0
 ? __kmalloc+0x1ca/0x1e0
 __kmem_cache_shutdown+0x13a/0x310
 shutdown_cache+0xf/0x130
 kmem_cache_destroy+0x1d5/0x200
 kvm_mmu_module_exit+0xa/0x30 [kvm]
 kvm_arch_exit+0x45/0x60 [kvm]
 kvm_exit+0x6f/0x80 [kvm]
 vmx_exit+0x1a/0x50 [kvm_intel]
 __x64_sys_delete_module+0x153/0x1f0
 ? exit_to_usermode_loop+0x88/0xc0
 do_syscall_64+0x4f/0x100
 entry_SYSCALL_64_after_hwframe+0x44/0xa9

Fixes: a21136345cb6f ("KVM: x86/mmu: Split remote_flush+zap case out of kvm_mmu_flush_or_zap()")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
