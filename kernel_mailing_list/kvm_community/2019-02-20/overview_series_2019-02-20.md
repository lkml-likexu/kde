#### [PATCH 1/2] KVM: PPC: Book3S HV: Simplify machine check handling
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This makes the handling of machine check interrupts that occur inside
a guest simpler and more robust, with less done in assembler code and
in real mode.

Now, when a machine check occurs inside a guest, we always get the
machine check event struct and put a copy in the vcpu struct for the
vcpu where the machine check occurred.  We no longer call
machine_check_queue_event() from kvmppc_realmode_mc_power7(), because
on POWER8, when a vcpu is running on an offline secondary thread and
we call machine_check_queue_event(), that calls irq_work_queue(),
which doesn't work because the CPU is offline, but instead triggers
the WARN_ON(lazy_irq_pending()) in pnv_smp_cpu_kill_self() (which
fires again and again because nothing clears the condition).

All that machine_check_queue_event() actually does is to cause the
event to be printed to the console.  For a machine check occurring in
the guest, we now print the event in kvmppc_handle_exit_hv()
instead.

The assembly code at label machine_check_realmode now just calls C
code and then continues exiting the guest.  We no longer either
synthesize a machine check for the guest in assembly code or return
to the guest without a machine check.

The code in kvmppc_handle_exit_hv() is extended to handle the case
where the guest is not FWNMI-capable.  In that case we now always
synthesize a machine check interrupt for the guest.  Previously, if
the host thinks it has recovered the machine check fully, it would
return to the guest without any notification that the machine check
had occurred.  If the machine check was caused by some action of the
guest (such as creating duplicate SLB entries), it is much better to
tell the guest that it has caused a problem.  Therefore we now always
generate a machine check interrupt for guests that are not
FWNMI-capable.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: Aravinda Prasad <aravinda@linux.vnet.ibm.com>
Reviewed-by: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
---
 arch/powerpc/include/asm/kvm_ppc.h      |  3 +-
 arch/powerpc/kvm/book3s.c               |  7 +++++
 arch/powerpc/kvm/book3s_hv.c            | 18 +++++++++--
 arch/powerpc/kvm/book3s_hv_ras.c        | 56 +++++++++------------------------
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 40 ++---------------------
 5 files changed, 42 insertions(+), 82 deletions(-)

```
#### [RESEND PATCH 1/7] mm/gup: Replace get_user_pages_longterm() with FOLL_LONGTERM
##### From: ira.weiny@intel.com

```c
From: Ira Weiny <ira.weiny@intel.com>

Rather than have a separate get_user_pages_longterm() call,
introduce FOLL_LONGTERM and change the longterm callers to use
it.

This patch does not change any functionality.

FOLL_LONGTERM can only be supported with get_user_pages() as it
requires vmas to determine if DAX is in use.

Signed-off-by: Ira Weiny <ira.weiny@intel.com>
---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   8 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   9 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c  |   6 +-
 drivers/vfio/vfio_iommu_type1.c            |   3 +-
 include/linux/mm.h                         |  13 +-
 mm/gup.c                                   | 138 ++++++++++++---------
 mm/gup_benchmark.c                         |   5 +-
 8 files changed, 101 insertions(+), 86 deletions(-)

```
#### [PATCH kvm-unit-tests] Update AMD instructions to conform to LLVM assembler
##### From: Peter Shier <pshier@google.com>

```c
The GNU assembler (gas) allows omitting operands where there is only a
single choice e.g. "VMRUN rAX".The LLVM assembler requires those operands
even though they are the default and only choice.

In addition, LLVM does not allow a CLGI instruction with a terminating
\n\t. Adding a ; separator after the instruction is a workaround.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/svm.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH RFC 01/39] KVM: x86: fix Xen hypercall page msr handling
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Xen usually places its MSR at 0x4000000 or 0x4000200 depending on
whether it is running in viridian mode or not. Note that this is not
ABI guaranteed, so it is possible for Xen to advertise the MSR some
place else.

Given the way xen_hvm_config() is handled, if the former address is
selected, this will conflict with HyperV's MSR
(HV_X64_MSR_GUEST_OS_ID) which uses the same address.

Given that the MSR location is arbitrary, move the xen_hvm_config()
handling to the top of kvm_set_msr_common() before falling through.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
---
 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
