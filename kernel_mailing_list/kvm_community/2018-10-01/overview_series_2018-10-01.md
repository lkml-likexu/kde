#### [PATCH 1/2] KVM: arm/arm64: Rename kvm_arm_config_vm to kvm_arm_setup_stage2
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
VM tends to be a very overloaded term in KVM, so let's keep it
to describe the virtual machine. For the virtual memory setup,
let's use the "stage2" suffix.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arch/arm/include/asm/kvm_host.h   | 6 +++++-
 arch/arm64/include/asm/kvm_arm.h  | 2 +-
 arch/arm64/include/asm/kvm_host.h | 2 +-
 arch/arm64/kvm/reset.c            | 2 +-
 virt/kvm/arm/arm.c                | 2 +-
 5 files changed, 9 insertions(+), 5 deletions(-)

```
#### [PATCH 1/2] KVM: VMX: remove kvm-intel.flexpriority module parameter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Many moons ago, commit 4c9fc8ef5017 ("KVM: VMX: Add module option to
disable flexpriority") introduced kvm-intel.flexpriority as it was
"Useful for debugging".  At that time, kvm-intel.flexpriority only
determined whether or not KVM would enable VIRTUALIZE_APIC_ACCESSES.
In short, it was intended as a way to disable virtualization of APIC
accesses for debug purposes.  Nowadays, kvm-intel.flexpriority is a
haphazard param that is inconsistently honored by KVM, e.g. it still
controls VIRTUALIZE_APIC_ACCESSES but not TPR_SHADOW, CR8-exiting or
VIRTUALIZE_X2APIC_MODE, and only for non-nested guests.  Disabling
the param also announces support for KVM_TPR_ACCESS_REPORTING (via
KVM_CAP_VAPIC), which may be functionally desirable, e.g. Qemu uses
KVM_TPR_ACCESS_REPORTING only to patch MMIO APIC access, but isn't
exactly accurate given its name since KVM may not intercept/report
TPR accesses via CR8 or MSR.

Remove kvm-intel.flexpriority as its usefulness for debug is dubious
given the current code base, while its existence is confusing and
can complicate code changes and/or lead to new bugs being introduced.
For example, as of commit 8d860bbeedef ("kvm: vmx: Basic APIC
virtualization controls have three settings"), KVM will disable
VIRTUALIZE_APIC_ACCESSES when a nested guest writes APIC_BASE MSR and
kvm-intel.flexpriority=0, whereas previously KVM would allow a nested
guest to enable VIRTUALIZE_APIC_ACCESSES so long as it's supported in
hardware.  I.e. KVM now advertises VIRTUALIZE_APIC_ACCESSES to a guest
but doesn't (always) allow setting it when kvm-intel.flexpriority=0,
and may even initially allow the control and then clear it when the
nested guest writes APIC_BASE MSR, which is decidedly odd even if it
doesn't cause functional issues.

Fixes: 8d860bbeedef ("kvm: vmx: Basic APIC virtualization controls have three settings")
Cc: Jim Mattson <jmattson@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 .../admin-guide/kernel-parameters.txt         |  4 ----
 arch/x86/kvm/vmx.c                            | 19 ++++---------------
 2 files changed, 4 insertions(+), 19 deletions(-)

```
#### [PULL 1/2] s390/cio: Convert ccw_io_region to pointer
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Eric Farman <farman@linux.ibm.com>

In the event that we want to change the layout of the ccw_io_region in the
future[1], it might be easier to work with it as a pointer within the
vfio_ccw_private struct rather than an embedded struct.

[1] https://patchwork.kernel.org/comment/22228541/

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Message-Id: <20180921204013.95804-2-farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c     | 12 +++++++++++-
 drivers/s390/cio/vfio_ccw_fsm.c     |  6 +++---
 drivers/s390/cio/vfio_ccw_ops.c     |  4 ++--
 drivers/s390/cio/vfio_ccw_private.h |  2 +-
 4 files changed, 17 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/9] x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
As a preparation to full MMU split between L1 and L2 make vcpu->arch.mmu
a pointer to the currently used mmu. For now, this is always
vcpu->arch.root_mmu. No functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/mmu.c              | 165 ++++++++++++++++----------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +--
 arch/x86/kvm/paging_tmpl.h      |  15 +--
 arch/x86/kvm/svm.c              |  14 +--
 arch/x86/kvm/vmx.c              |  15 +--
 arch/x86/kvm/x86.c              |  20 ++--
 8 files changed, 130 insertions(+), 124 deletions(-)

```
