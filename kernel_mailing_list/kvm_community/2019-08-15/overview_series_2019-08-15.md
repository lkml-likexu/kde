#### [PATCH] KVM: arm/arm64: vgic: Make function comments match function declarations
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Since commit 503a62862e8f ("KVM: arm/arm64: vgic: Rely on the GIC driver to
parse the firmware tables"), the vgic_v{2,3}_probe functions stopped using
a DT node. Commit 909777324588 ("KVM: arm/arm64: vgic-new: vgic_init:
implement kvm_vgic_hyp_init") changed the functions again, and now they
require exactly one argument, a struct gic_kvm_info populated by the GIC
driver. Unfortunately the comments regressed and state that a DT node is
used instead. Change the function comments to reflect the current
prototypes.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 virt/kvm/arm/vgic/vgic-v2.c | 7 ++++---
 virt/kvm/arm/vgic/vgic-v3.c | 7 ++++---
 2 files changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: Assert that struct kvm_vcpu is always as offset zero
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
KVM implementations that wrap struct kvm_vcpu with a vendor specific
struct, e.g. struct vcpu_vmx, must place the vcpu member at offset 0,
otherwise the usercopy region intended to encompass struct kvm_vcpu_arch
will instead overlap random chunks of the vendor specific struct.
E.g. padding a large number of bytes before struct kvm_vcpu triggers
a usercopy warn when running with CONFIG_HARDENED_USERCOPY=y.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Note, the PowerPC change is completely untested.

 arch/powerpc/kvm/e500.c | 3 +++
 arch/x86/kvm/svm.c      | 3 +++
 arch/x86/kvm/vmx/vmx.c  | 3 +++
 3 files changed, 9 insertions(+)

```
#### [PATCH] KVM: VMX: Fix and tweak the comments for VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Fix an incorrect/stale comment regarding the vmx_vcpu pointer, as guest
registers are now loaded using a direct pointer to the start of the
register array.

Opportunistically add a comment to document why the vmx_vcpu pointer is
needed, its consumption via 'call vmx_update_host_rsp' is rather subtle.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmenter.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: x86: fix reporting of AMD speculation bug CPUID leaf
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The AMD_* bits have to be set from the vendor-independent
feature and bug flags, because KVM_GET_SUPPORTED_CPUID does not care
about the vendor and they should be set on Intel processors as well.
On top of this, SSBD, STIBP and AMD_SSB_NO bit were not set, and
VIRT_SSBD does not have to be added manually because it is a
cpufeature that comes directly from the host's CPUID bit.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/cpuid.c | 17 +++++++++++------
 1 file changed, 11 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: Fix x86_decode_insn() return when fetching insn bytes fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Jump to the common error handling in x86_decode_insn() if
__do_insn_fetch_bytes() fails so that its error code is converted to the
appropriate return type.  Although the various helpers used by
x86_decode_insn() return X86EMUL_* values, x86_decode_insn() itself
returns EMULATION_FAILED or EMULATION_OK.

This doesn't cause a functional issue as the sole caller,
x86_emulate_instruction(), currently only cares about success vs.
failure, and success is indicated by '0' for both types
(X86EMUL_CONTINUE and EMULATION_OK).

Fixes: 285ca9e948fa ("KVM: emulate: speed up do_insn_fetch")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/MMU: Zap all when removing memslot if VM has assigned device
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Alex Williamson reported regressions with device assignment when KVM
changed its memslot removal logic to zap only the SPTEs for the memslot
being removed.  The source of the bug is unknown at this time, and root
causing the issue will likely be a slow process.  In the short term, fix
the regression by zapping all SPTEs when removing a memslot from a VM
with assigned device(s).

Fixes: 4e103134b862 ("KVM: x86/mmu: Zap only the relevant pages when removing a memslot", 2019-02-05)
Reported-by: Alex Willamson <alex.williamson@redhat.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

An alternative idea to a full revert.  I assume this would be easy to
backport, and also easy to revert or quirk depending on where the bug
is hiding.

 arch/x86/kvm/mmu.c | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v2 1/3] KVM: X86: Trace vcpu_id for vmexit
##### From: Peter Xu <peterx@redhat.com>

```c
Tracing the ID helps to pair vmenters and vmexits for guests with
multiple vCPUs.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/trace.h | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/15] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Generally, APICv for all vcpus in the VM are enable/disable in the same
manner. So, get_enable_apicv() should represent APICv status of the VM
instead of each VCPU.

Modify kvm_x86_ops.get_enable_apicv() to take struct kvm as parameter
instead of struct kvm_vcpu.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/svm.c              | 5 +++--
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 arch/x86/kvm/x86.c              | 2 +-
 4 files changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH] Revert "KVM: x86/mmu: Zap only the relevant pages when removing a memslot"
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This reverts commit 4e103134b862314dc2f2f18f2fb0ab972adc3f5f.
Alex Williamson reported regressions with device assignment with
this patch.  Even though the bug is probably elsewhere and still
latent, this is needed to fix the regression.

Fixes: 4e103134b862 ("KVM: x86/mmu: Zap only the relevant pages when removing a memslot", 2019-02-05)
Reported-by: Alex Willamson <alex.williamson@redhat.com>
Cc: stable@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.c | 33 +--------------------------------
 1 file changed, 1 insertion(+), 32 deletions(-)

```
#### [PATCH v2] KVM: LAPIC: Periodically revaluate to get conservative lapic_timer_advance_ns
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Even if for realtime CPUs, cache line bounces, frequency scaling, presence 
of higher-priority RT tasks, etc can still cause different response. These 
interferences should be considered and periodically revaluate whether 
or not the lapic_timer_advance_ns value is the best, do nothing if it is,
otherwise recaluate again. Set lapic_timer_advance_ns to the minimal 
conservative value from all the estimated values.

Testing on Skylake server, cat vcpu*/lapic_timer_advance_ns, before patch:
1628
4161
4321
3236
...

Testing on Skylake server, cat vcpu*/lapic_timer_advance_ns, after patch:
1553
1499
1509
1489
...

Testing on Haswell desktop, cat vcpu*/lapic_timer_advance_ns, before patch:
4617
3641
4102
4577
...
Testing on Haswell desktop, cat vcpu*/lapic_timer_advance_ns, after patch:
2775
2892
2764
2775
...

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 34 ++++++++++++++++++++++++++++------
 arch/x86/kvm/lapic.h |  2 ++
 2 files changed, 30 insertions(+), 6 deletions(-)

```
