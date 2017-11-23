#### [PATCH] svm: Fix improper check when deactivate AVICThread-Topic: [PATCH] svm: Fix improper check when deactivate AVIC
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
The function svm_refresh_apicv_exec_ctrl() always returning prematurely
as kvm_vcpu_apicv_active() always return false when calling from
the function arch/x86/kvm/x86.c:kvm_vcpu_deactivate_apicv().
This is because the apicv_active is set to false just before calling
refresh_apicv_exec_ctrl().

Also, we need to mark VMCB_AVIC bit as dirty instead of VMCB_INTR.

So, fix svm_refresh_apicv_exec_ctrl() to properly deactivate AVIC.

Fixes: 67034bb9dd5e ('KVM: SVM: Add irqchip_split() checks before enabling AVIC')
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 22 ++++++++++++++++++----
 1 file changed, 18 insertions(+), 4 deletions(-)

```
