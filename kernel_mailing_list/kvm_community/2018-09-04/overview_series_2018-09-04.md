#### [PATCH] KVM: nVMX: Wake blocked vCPU in guest-mode if pending interrupt in virtual APICv
##### From: Liran Alon <liran.alon@oracle.com>

```c
In case L1 do not intercept L2 HLT or enter L2 in HLT activity-state,
it is possible for a vCPU to be blocked while it is in guest-mode.

According to Intel SDM 26.6.5 Interrupt-Window Exiting and
Virtual-Interrupt Delivery: "These events wake the logical processor
if it just entered the HLT state because of a VM entry".
Therefore, if L1 enters L2 in HLT activity-state and L2 has a pending
deliverable interrupt in vmcs12->guest_intr_status.RVI, then the vCPU
should be waken from the HLT state and injected with the interrupt.

In addition, if while the vCPU is blocked (while it is in guest-mode),
it receives a nested posted-interrupt, then the vCPU should also be
waken and injected with the posted interrupt.

To handle these cases, this patch enhances kvm_vcpu_has_events() to also
check if there is a pending interrupt in L2 virtual APICv provided by
L1. That is, it evaluates if there is a pending virtual interrupt for L2
by checking RVI[7:4] > VPPR[7:4] as specified in Intel SDM 29.2.1
Evaluation of Pending Interrupts.

Note that this also handles the case of nested posted-interrupt by the
fact RVI is updated in vmx_complete_nested_posted_interrupt() which is
called from kvm_vcpu_check_block() -> kvm_arch_vcpu_runnable() ->
kvm_vcpu_running() -> vmx_check_nested_events() ->
vmx_complete_nested_posted_interrupt().

Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx.c              | 22 ++++++++++++++++++++++
 arch/x86/kvm/x86.c              | 10 +++++++++-
 3 files changed, 32 insertions(+), 1 deletion(-)

```
#### [RFC PATCH] vfio: vfio_sdmdev_groups[] can be static
##### From: kbuild test robot <lkp@intel.com>

```c
Fixes: 1e47d5e60865 ("vfio: add sdmdev support")
Signed-off-by: kbuild test robot <fengguang.wu@intel.com>
---
 vfio_sdmdev.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] target-i386: add q35 0xcf8 port as coalesced_pio
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
after coalesced pio series patches, the patch is a supplement to
q35 pci-host config port.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 hw/pci-host/q35.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v4 1/4] x86/mm: Restructure sme_encrypt_kernel()
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Re-arrange the sme_encrypt_kernel() by moving the workarea map/unmap
logic in a separate static function. There are no logical changes in this
patch. The restructuring will allow us to expand the sme_encrypt_kernel
in future.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
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
#### [kvm-unit-tests PATCH 1/3] x86: VMX: Introduce util to disable intercept on x2APIC MSRs
##### From: Liran Alon <liran.alon@oracle.com>

```c
Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 x86/vmx_tests.c | 50 ++++++++++++++++++++++++++++++++++++--------------
 1 file changed, 36 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] x86: VMX: Verify do not lose pending interrupt queued before entering guest
##### From: Liran Alon <liran.alon@oracle.com>

```c
This patch test the issue fixed by KVM commit "KVM: nVMX: Fix loss of
pending event before entering L2". The test aim to verify that a pending
interrupt while interrupts are disabled is dispatched when we enter into
VMX guest instead of being lost.

The test configures VMCS to intercept external-interrupts and then
queue an interrupt by disabling interrupts and issue a self-IPI.
At this point, we enter guest and we expect CPU to immediately exit
guest on external-interrupt. To complete the test, we then re-enable
interrupts, verify interrupt is dispatched and re-enter guest to verify
it completes execution.

Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 x86/unittests.cfg |  6 ++++++
 x86/vmx_tests.c   | 48 ++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 54 insertions(+)

```
