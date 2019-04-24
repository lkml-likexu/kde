#### [PATCH v2] KVM: PPC: Book3S HV: XIVE: Prevent races when releasing device
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Now that we have the possibility of a XIVE or XICS-on-XIVE device being
released while the VM is still running, we need to be careful about
races and potential use-after-free bugs.  Although the kvmppc_xive
struct is not freed, but kept around for re-use, the kvmppc_xive_vcpu
structs are freed, and they are used extensively in both the XIVE native
and XICS-on-XIVE code.

There are various ways in which XIVE code gets invoked:

- VCPU entry and exit, which do push and pull operations on the XIVE hardware
- one_reg get and set functions (vcpu->mutex is held)
- XICS hypercalls (but only inside guest execution, not from
  kvmppc_pseries_do_hcall)
- device creation calls (kvm->lock is held)
- device callbacks - get/set attribute, mmap, pagefault, release/destroy
- set_mapped/clr_mapped calls (kvm->lock is held)
- connect_vcpu calls
- debugfs file read callbacks

Inside a device release function, we know that userspace cannot have an
open file descriptor referring to the device, nor can it have any mmapped
regions from the device.  Therefore the device callbacks are excluded,
as are the connect_vcpu calls (since they need a fd for the device).
Further, since the caller holds the kvm->lock mutex, no other device
creation calls or set/clr_mapped calls can be executing concurrently.

To exclude VCPU execution and XICS hypercalls, we temporarily set
kvm->arch.mmu_ready to 0.  This forces any VCPU task that is trying to
enter the guest to take the kvm->lock mutex, which is held by the caller
of the release function.  Then, sending an IPI to all other CPUs forces
any VCPU currently executing in the guest to exit.

Finally, we take the vcpu->mutex for each VCPU around the process of
cleaning up and freeing its XIVE data structures, in order to exclude
any one_reg get/set calls.

To exclude the debugfs read callbacks, we just need to ensure that
debugfs_remove is called before freeing any data structures.  Once it
returns we know that no CPU can be executing the callbacks (for our
kvmppc_xive instance).

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: move debugfs_remove call to eliminate race

 arch/powerpc/kvm/book3s_xive.c        | 51 ++++++++++++++++++++++++++++-------
 arch/powerpc/kvm/book3s_xive_native.c | 43 ++++++++++++++++++++++++-----
 2 files changed, 78 insertions(+), 16 deletions(-)

```
