#### [PATCH 1/6] KVM: x86: Add callback functions for handling APIC ID, DFR and LDR update
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Add hooks for handling the case when guest VM update APIC ID, DFR and LDR.
This is needed during AMD AVIC is temporary deactivated.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 3 +++
 arch/x86/kvm/lapic.c            | 6 ++++++
 2 files changed, 9 insertions(+)

```
#### [PATCH] svm/avic: Fix invalidate logical APIC id entryThread-Topic: [PATCH] svm/avic: Fix invalidate logical APIC id entry
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Only clear the valid bit when invalidate logical APIC id entry.
The current logic clear the valid bit, but also set the rest of
the bits (including reserved bits) to 1.

Fixes: 98d90582be2e ('svm: Fix AVIC DFR and LDR handling')
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: PPC: Book3S HV: Implement virtual mode H_PAGE_INIT handler
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Implement a virtual mode handler for the H_CALL H_PAGE_INIT which can be
used to zero or copy a guest page. The page is defined to be 4k and must
be 4k aligned.

The in-kernel handler halves the time to handle this H_CALL compared to
handling it in userspace for a radix guest.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

V1 -> V2:

- Rolled the patch to introduce kvmppc_copy_guest() into this one
- kvmppc_copy_guest() can only copy within a memslot
- Use SZ_4K for page size
- Use long for hcall return params
- Only perform copy or zero not both, and reorder so copy done if both set
---
 arch/powerpc/kvm/book3s_hv.c | 80 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 80 insertions(+)

```
#### [PATCH v2] KVM: PPC: Book3S HV: Load LPID and Flush TLB on Secondary Radix Threads
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When running with independent threads off the main thread is responsible
for collecting secondary threads on the core and giving them vcpus to
run. These secondary threads spin in kvm_no_guest until they are given a
vcore to run and then take the kvmppc_hv_entry entry path from
kvm_secondary_got_guest. However this entry path doesn't load the guest
LPID for a radix guest, assuming it has already been loaded in
kvmppc_radix_check_need_tlb_flush() which would be called from
kvmppc_run_core when running in independent threads on mode. This means
that the guest runs with the host LPID which leads to an unhandleable mmu
fault giving:

KVM: Got unsupported MMU fault
error: kvm run failed Bad address
NIP c000000000028d50   LR c00000000004cad4 CTR 0000000000000000 XER 0000000000000000 CPU#0
MSR 8000000002089033 HID0 0000000000000000  HF 8000000000000000 iidx 3 didx 3
TB 00000000 00000000 DECR 0
GPR00 c00000000004cad4 c00000003e543a10 c00000000105ea00 000000000000c800
GPR04 0000000000000002 0000000000000000 0000000000000000 0000000000000000
GPR08 0000000000000000 000000000000a001 00000000a77784ea 0000000002001001
GPR12 0000000000000000 c000000001240000 c000000000010b50 0000000000000000
GPR16 0000000000000000 0000000000000000 0000000000000000 0000000000000000
GPR20 0000000000000000 0000000000000000 0000000000000000 c00000003fe7c800
GPR24 0000000000000000 0000000000000004 c0000000011044f8 0000000000000001
GPR28 0000000000000001 0000000000000000 c0000000011044fc 000000000000c336
CR 48000424  [ G  L  -  -  -  G  E  G  ]             RES ffffffffffffffff
 SRR0 c00000000000e708  SRR1 8000000002009033    PVR 00000000004e1202 VRSAVE 0000000000000000
SPRG0 0000000000000000 SPRG1 c000000001240000  SPRG2 0000000000000000  SPRG3 0000000000000000
SPRG4 0000000000000000 SPRG5 0000000000000000  SPRG6 0000000000000000  SPRG7 0000000000000000
HSRR0 0000000000000000 HSRR1 0000000000000000
 CFAR 0000000000000000
 LPCR 0000000003d6f41f
 PTCR 0000000000000000   DAR 0000000000000000  DSISR 0000000000000000

Also we fail to perform the tlb flush if this vcpu has moved to this
core from another physical core which could result in stale tlb entries
being used.

To fix this we call kvmppc_radix_check_need_tlb_flush() from the
secondary entry path as well. This will both set the guest LPID and
check if the tlb needs to be flushed. This means moving this function to
book3s_hv_builtin.c. The only change to the function other than moving
it is to use cpu_first_thread_sibling rather than a mask from a
hardcoded value. Also call kvmppc_prepare_radix_vcpu with the pcpu id
where the thread will run rather than just the pcpu id of the first
sibling thread in the core, which for now has the same result.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

V1 -> V2:
- Drop changes to kvmppc_prepare_radix_vcpu() function as they had no
  effect
- Use PACAINDEX to determine physical cpu id rather than accessing vcore
  field
---
 arch/powerpc/include/asm/kvm_ppc.h      |  2 ++
 arch/powerpc/kvm/book3s_hv.c            | 33 +--------------------------------
 arch/powerpc/kvm/book3s_hv_builtin.c    | 32 ++++++++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 25 ++++++++++++++++---------
 4 files changed, 51 insertions(+), 41 deletions(-)

```
#### [PATCH v3] KVM: PPC: Book3S HV: Load LPID and Flush TLB on Secondary Radix Threads
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When running with independent threads off the main thread is responsible
for collecting secondary threads on the core and giving them vcpus to
run. These secondary threads spin in kvm_no_guest until they are given a
vcore to run and then take the kvmppc_hv_entry entry path from
kvm_secondary_got_guest. However this entry path doesn't load the guest
LPID for a radix guest, assuming it has already been loaded in
kvmppc_radix_check_need_tlb_flush() which would be called from
kvmppc_run_core when running in independent threads on mode. This means
that the guest runs with the host LPID which leads to an unhandleable mmu
fault giving:

KVM: Got unsupported MMU fault
error: kvm run failed Bad address
NIP c000000000028d50   LR c00000000004cad4 CTR 0000000000000000 XER 0000000000000000 CPU#0
MSR 8000000002089033 HID0 0000000000000000  HF 8000000000000000 iidx 3 didx 3
TB 00000000 00000000 DECR 0
GPR00 c00000000004cad4 c00000003e543a10 c00000000105ea00 000000000000c800
GPR04 0000000000000002 0000000000000000 0000000000000000 0000000000000000
GPR08 0000000000000000 000000000000a001 00000000a77784ea 0000000002001001
GPR12 0000000000000000 c000000001240000 c000000000010b50 0000000000000000
GPR16 0000000000000000 0000000000000000 0000000000000000 0000000000000000
GPR20 0000000000000000 0000000000000000 0000000000000000 c00000003fe7c800
GPR24 0000000000000000 0000000000000004 c0000000011044f8 0000000000000001
GPR28 0000000000000001 0000000000000000 c0000000011044fc 000000000000c336
CR 48000424  [ G  L  -  -  -  G  E  G  ]             RES ffffffffffffffff
 SRR0 c00000000000e708  SRR1 8000000002009033    PVR 00000000004e1202 VRSAVE 0000000000000000
SPRG0 0000000000000000 SPRG1 c000000001240000  SPRG2 0000000000000000  SPRG3 0000000000000000
SPRG4 0000000000000000 SPRG5 0000000000000000  SPRG6 0000000000000000  SPRG7 0000000000000000
HSRR0 0000000000000000 HSRR1 0000000000000000
 CFAR 0000000000000000
 LPCR 0000000003d6f41f
 PTCR 0000000000000000   DAR 0000000000000000  DSISR 0000000000000000

Also we fail to perform the tlb flush if this vcpu has moved to this
core from another physical core which could result in stale tlb entries
being used.

To fix this we call kvmppc_radix_check_need_tlb_flush() from the
secondary entry path as well. This will both set the guest LPID and
check if the tlb needs to be flushed. This means moving this function to
book3s_hv_builtin.c. The only change to the function other than moving
it is to use cpu_first_thread_sibling rather than a mask from a
hardcoded value. Also call kvmppc_prepare_radix_vcpu with the pcpu id
where the thread will run rather than just the pcpu id of the first
sibling thread in the core, which for now has the same result.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

V2 -> V3:
- Only call kvmppc_radix_check_need_tlb_flush on radix

V1 -> V2:
- Drop changes to kvmppc_prepare_radix_vcpu() function as they had no
  effect
- Use PACAINDEX to determine physical cpu id rather than accessing vcore
  field
---
 arch/powerpc/include/asm/kvm_ppc.h      |  2 ++
 arch/powerpc/kvm/book3s_hv.c            | 33 +--------------------------------
 arch/powerpc/kvm/book3s_hv_builtin.c    | 32 ++++++++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 28 +++++++++++++++++++---------
 4 files changed, 54 insertions(+), 41 deletions(-)

```
#### [PATCH v6 1/7] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

First of all we do not want to change existing behavior when
intercepting AP instructions without the SIE allowing the guest
to use AP instructions.

In this patch we only handle the AQIC interception allowed by
facility 65 which will be enabled when the complete interception
infrastructure will be present.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command and only this command.

But we want to be able to return a correct answer to the guest
even there is no VFIO AP driver in the kernel.
Therefor, we inject the correct exceptions from inside KVM for the
case the callback is not initialized, which happens when the vfio_ap
driver is not loaded.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.
If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h      |  8 ++++
 arch/s390/kvm/priv.c                  | 90 +++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  2 +
 3 files changed, 100 insertions(+)

```
#### [PATCH] vfio-pci: Fix MSI IRQ forwarding for without per-vector masking
##### From: Leo Yan <leo.yan@linaro.org>

```c
If MSI doesn't support per-vector masking capability and
PCI_MSI_FLAGS_MASKBIT isn't set in message control field, the function
vfio_pci_msi_vector_write() will directly bail out for this case and
every vector's 'virt_state' keeps setting bit VFIO_PCI_MSI_STATE_MASKED.

This results in the state maintained in 'virt_state' cannot really
reflect the MSI hardware state; finally it will mislead the function
vfio_pci_update_msi_entry() to skip IRQ forwarding with below flow:

vfio_pci_update_msi_entry() {

  [...]

  if (msi_is_masked(entry->virt_state) == msi_is_masked(entry->phys_state))
      return 0;  ==> skip IRQ forwarding

  [...]
}

To fix this issue, when detect PCI_MSI_FLAGS_MASKBIT is not set in the
message control field, this patch simply clears bit
VFIO_PCI_MSI_STATE_MASKED for all vectors 'virt_state'; at the end
vfio_pci_update_msi_entry() can forward MSI IRQ successfully.

Signed-off-by: Leo Yan <leo.yan@linaro.org>
---
 vfio/pci.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
