#### Can we boot a 512U kvm guest?
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Hi folks,

Since commit e25028c8ded0 ("KVM: arm/arm64: Bump VGIC_V3_MAX_CPUS to
512"), we seemed to be allowed to boot a 512U guest.  But I failed to
start it up with the latest QEMU.  I guess there are at least *two*
reasons (limitations).

First I got a QEMU abort:
	"kvm_set_irq: Invalid argument"

Enable the trace_kvm_irq_line() under debugfs, when it comed with
vcpu-256, I got:
	"Inject UNKNOWN interrupt (3), vcpu->idx: 0, num: 23, level: 0"
and kvm_vm_ioctl_irq_line() returns -EINVAL to user-space...

So the thing is that we only have 8 bits for vcpu_index field ([23:16])
in KVM_IRQ_LINE ioctl.  irq_type field will be corrupted if we inject a
PPI to vcpu-256, whose vcpu_index will take 9 bits.

I temporarily patched the KVM and QEMU with the following diff:

---8<---
---8<---

It makes things a bit better, it also immediately BREAKs the api with
old versions.


Next comes one more QEMU abort (with the "fix" above):
	"Failed to set device address: No space left on device"

We register two io devices (rd_dev and sgi_dev) on KVM_MMIO_BUS for
each redistributor. 512 vcpus take 1024 io devices, which is beyond the
maximum limitation of the current kernel - NR_IOBUS_DEVS (1000).
So we get a ENOSPC error here.


I don't know if the similar problems have been discussed before in ML.
Is it time to really support the 512U guest?


Thanks,
zenghui

diff --git a/arch/arm64/include/uapi/asm/kvm.h 
```
#### [PATCH] KVM: nVMX: Check that HLT activity state is supported
##### From: Nikita Leshenko <nikita.leshchenko@oracle.com>

```c
Fail VM entry if GUEST_ACTIVITY_HLT is unsupported. According to "SDM A.6 -
Miscellaneous Data", VM entry should fail if the HLT activity is not marked as
supported on IA32_VMX_MISC MSR.

Usermode might disable GUEST_ACTIVITY_HLT support in the vCPU with
vmx_restore_vmx_misc(). Before this commit VM entries would have succeeded
anyway.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 16 ++++++++++++----
 arch/x86/kvm/vmx/nested.h |  5 +++++
 2 files changed, 17 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/3] KVM: PPC: Book3S HV: Fix race in re-enabling XIVE escalation interrupts
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Escalation interrupts are interrupts sent to the host by the XIVE
hardware when it has an interrupt to deliver to a guest VCPU but that
VCPU is not running anywhere in the system.  Hence we disable the
escalation interrupt for the VCPU being run when we enter the guest
and re-enable it when the guest does an H_CEDE hypercall indicating
it is idle.

It is possible that an escalation interrupt gets generated just as we
are entering the guest.  In that case the escalation interrupt may be
using a queue entry in one of the interrupt queues, and that queue
entry may not have been processed when the guest exits with an H_CEDE.
The existing entry code detects this situation and does not clear the
vcpu->arch.xive_esc_on flag as an indication that there is a pending
queue entry (if the queue entry gets processed, xive_esc_irq() will
clear the flag).  There is a comment in the code saying that if the
flag is still set on H_CEDE, we have to abort the cede rather than
re-enabling the escalation interrupt, lest we end up with two
occurrences of the escalation interrupt in the interrupt queue.

However, the exit code doesn't do that; it aborts the cede in the sense
that vcpu->arch.ceded gets cleared, but it still enables the escalation
interrupt by setting the source's PQ bits to 00.  Instead we need to
set the PQ bits to 10, indicating that an interrupt has been triggered.
We also need to avoid setting vcpu->arch.xive_esc_on in this case
(i.e. vcpu->arch.xive_esc_on seen to be set on H_CEDE) because
xive_esc_irq() will run at some point and clear it, and if we race with
that we may end up with an incorrect result (i.e. xive_esc_on set when
the escalation interrupt has just been handled).

It is extremely unlikely that having two queue entries would cause
observable problems; theoretically it could cause queue overflow, but
the CPU would have to have thousands of interrupts targetted to it for
that to be possible.  However, this fix will also make it possible to
determine accurately whether there is an unhandled escalation
interrupt in the queue, which will be needed by the following patch.

Cc: stable@vger.kernel.org # v4.16+
Fixes: 9b9b13a6d153 ("KVM: PPC: Book3S HV: Keep XIVE escalation interrupt masked unless ceded")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: don't set xive_esc_on if we're not using a XIVE escalation
interrupt.

 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 36 +++++++++++++++++++++------------
 1 file changed, 23 insertions(+), 13 deletions(-)

```
#### [PATCH v4 1/7] x86: KVM: svm: don't pretend to advance RIP in case wrmsr_interception() results in #GP
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
svm->next_rip is only used by skip_emulated_instruction() and in case
kvm_set_msr() fails we rightfully don't do that. Move svm->next_rip
advancement to 'else' branch to avoid creating false impression that
it's always advanced (and make it look like rdmsr_interception()).

This is a preparatory change to removing hardcoded RIP advancement
from instruction intercepts, no functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
