#### [PATCH 1/2] kvm: vmx: Add IA32_FLUSH_CMD guest supportFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Expose IA32_FLUSH_CMD to the guest if the guest CPUID enumerates
support for this MSR. As with IA32_PRED_CMD, permission for
unintercepted writes to this MSR will be granted to the guest after
the first non-zero write.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ben Serebrin <serebrin@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx.c | 44 +++++++++++++++++++++++++++++++++++---------
 1 file changed, 35 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Use correct pagesize in kvm_unmap_radix()
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Since commit e641a317830b ("KVM: PPC: Book3S HV: Unify dirty page map
between HPT and radix", 2017-10-26), kvm_unmap_radix() computes the
number of PAGE_SIZEd pages being unmapped and passes it to
kvmppc_update_dirty_map(), which expects to be passed the page size
instead.  Consequently it will only mark one system page dirty even
when a large page (for example a THP page) is being unmapped.  The
consequence of this is that part of the THP page might not get copied
during live migration, resulting in memory corruption for the guest.

This fixes it by computing and passing the page size in kvm_unmap_radix().

Cc: stable@vger.kernel.org # v4.15+
Fixes: e641a317830b (KVM: PPC: Book3S HV: Unify dirty page map between HPT and radix)
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH 2/2] KVM: vmx: Inject #UD for SGX ENCLS instruction in guest
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Virtualization of Intel SGX depends on Enclave Page Cache (EPC)
management that is not yet available in the kernel, i.e. KVM support
for exposing SGX to a guest cannot be added until basic support
for SGX is upstreamed, which is a WIP[1].

Until SGX is properly supported in KVM, ensure a guest sees expected
behavior for ENCLS, i.e. all ENCLS #UD.  Because SGX does not have a
true software enable bit, e.g. there is no CR4.SGXE bit, the ENCLS
instruction can be executed[1] by the guest if SGX is supported by the
system.  Intercept all ENCLS leafs (via the ENCLS- exiting control and
field) and unconditionally inject #UD.

[1] https://www.spinics.net/lists/kvm/msg171333.html or
    https://lkml.org/lkml/2018/7/3/879

[2] A guest can execute ENCLS in the sense that ENCLS will not take
    an immediate #UD, but no ENCLS will ever succeed in a guest
    without explicit support from KVM (map EPC memory into the guest),
    unless KVM has a *very* egregious bug, e.g. accidentally mapped
    EPC memory into the guest SPTEs.  In other words this patch is
    needed only to prevent the guest from seeing inconsistent behavior,
    e.g. #GP (SGX not enabled in Feature Control MSR) or #PF (leaf
    operand(s) does not point at EPC memory) instead of #UD on ENCLS.
    Intercepting ENCLS is not required to prevent the guest from truly
    utilizing SGX.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 30 +++++++++++++++++++++++++++++-
 1 file changed, 29 insertions(+), 1 deletion(-)

```
#### [PATCH RESEND 1/2] KVM: vmx: Add defines for SGX ENCLS exiting
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Hardware support for basic SGX virtualization adds a new execution
control (ENCLS_EXITING), VMCS field (ENCLS_EXITING_BITMAP) and exit
reason (ENCLS), that enables a VMM to intercept specific ENCLS leaf
functions, e.g. to inject faults when the VMM isn't exposing SGX to
a VM.  When ENCLS_EXITING is enabled, the VMM can set/clear bits in
the bitmap to intercept/allow ENCLS leaf functions in non-root, e.g.
setting bit 2 in the ENCLS_EXITING_BITMAP will cause ENCLS[EINIT]
to VMExit(ENCLS).

Note: EXIT_REASON_ENCLS was previously added by commit 1f5199927034
("KVM: VMX: add missing exit reasons").

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/vmx.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] kvm: x86: Set highest physical address bits in non-present/reserved SPTEs
##### From: Junaid Shahid <junaids@google.com>

```c
Always set the 5 upper-most supported physical address bits to 1 for SPTEs
that are marked as non-present or reserved, to make them unusable for
L1TF attacks from the guest. Currently, this just applies to MMIO SPTEs.
(We do not need to mark PTEs that are completely 0 as physical page 0
is already reserved.)

This allows mitigation of L1TF without disabling hyper-threading by using
shadow paging mode instead of EPT.

Signed-off-by: Junaid Shahid <junaids@google.com>
---
 arch/x86/kvm/mmu.c | 43 ++++++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c |  8 ++++++--
 2 files changed, 44 insertions(+), 7 deletions(-)

```
