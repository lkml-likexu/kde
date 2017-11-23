#### [PATCH] KVM: LAPIC: Fix pv ipis use-before-initialization
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Reported by syzkaller:

 BUG: unable to handle kernel NULL pointer dereference at 0000000000000014
 PGD 800000040410c067 P4D 800000040410c067 PUD 40410d067 PMD 0 
 Oops: 0000 [#1] PREEMPT SMP PTI
 CPU: 3 PID: 2567 Comm: poc Tainted: G           OE     4.19.0-rc5 #16
 RIP: 0010:kvm_pv_send_ipi+0x94/0x350 [kvm]
 Call Trace:
  kvm_emulate_hypercall+0x3cc/0x700 [kvm]
  handle_vmcall+0xe/0x10 [kvm_intel]
  vmx_handle_exit+0xc1/0x11b0 [kvm_intel]
  vcpu_enter_guest+0x9fb/0x1910 [kvm]
  kvm_arch_vcpu_ioctl_run+0x35c/0x610 [kvm]
  kvm_vcpu_ioctl+0x3e9/0x6d0 [kvm]
  do_vfs_ioctl+0xa5/0x690
  ksys_ioctl+0x6d/0x80
  __x64_sys_ioctl+0x1a/0x20
  do_syscall_64+0x83/0x6e0
  entry_SYSCALL_64_after_hwframe+0x49/0xbe

The reason is that the apic map has not yet been initialized, the testcase 
triggers pv_send_ipi interface by vmcall which results in kvm->arch.apic_map
is dereferenced. This patch fixes it by checking whether or not apic map is 
NULL and bailing out immediately if that is the case.

Fixes: 4180bf1b65 (KVM: X86: Implement "send IPI" hypercall)
Reported-by: Wei Wu <ww9210@gmail.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Wei Wu <ww9210@gmail.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 5 +++++
 1 file changed, 5 insertions(+)

```
