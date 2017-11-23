#### [PATCH] KVM: x86: Trace changes to active TSC offset regardless if vCPU in guest-mode
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
For some reason, kvm_x86_ops->write_l1_tsc_offset() skipped trace
of change to active TSC offset in case vCPU is in guest-mode.
This patch changes write_l1_tsc_offset() behavior to trace any change
to active TSC offset to aid debugging.  The VMX code is changed to
look more similar to SVM, which is in my opinion nicer.

Based on a patch by Liran Alon.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
	Untested still, but throwing it out because it seems pretty
	obvious...

 arch/x86/kvm/svm.c |  9 +++++----
 arch/x86/kvm/vmx.c | 34 +++++++++++++++++-----------------
 2 files changed, 22 insertions(+), 21 deletions(-)

```
