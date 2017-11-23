#### [PATCH] KVM: x86: never trap MSR_KERNEL_GS_BASE
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
KVM has an old optimization whereby accesses to the kernel GS base MSR
are trapped when the guest is in 32-bit and not when it is in 64-bit mode.
The idea is that swapgs is not available in 32-bit mode and thus the
guest has no reason to access the MSR unless in 64-bit mode.  Therefore
32-bit applications need not pay the price of switching the kernel GS
base between the host and the guest values, 64-bit applications.

However, this optimization adds complexity to the code for little
benefit (these days most guests are going to be 64-bit anyway) and in fact
broke after commit 678e315e78a7 ("KVM: vmx: add dedicated utility to
access guest's kernel_gs_base", 2018-08-06); the guest kernel GS base
is not restored correctly by the RSM instruction and UEFI Secure Boot
was broken.  This patch just removes the optimization; the kernel
GS base MSR is now never trapped by KVM, similarly to the FS and GS
base MSRs.

Fixes: 678e315e78a780dbef384b92339c8414309dbc11
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx.c | 47 ++++++++++-------------------------------------
 1 file changed, 10 insertions(+), 37 deletions(-)

```
