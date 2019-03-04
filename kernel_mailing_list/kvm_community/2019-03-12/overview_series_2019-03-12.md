#### [PATCH] KVM: x86: update %rip after emulating IO
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Most (all?) x86 platforms provide a port IO based reset mechanism, e.g.
OUT 92h or CF9h.  Userspace may emulate said mechanism, i.e. reset a
vCPU in response to KVM_EXIT_IO, without explicitly announcing to KVM
that it is doing a reset, e.g. Qemu jams vCPU state and resumes running.

To avoid corruping %rip after such a reset, commit 0967b7bf1c22 ("KVM:
Skip pio instruction when it is emulated, not executed") changed the
behavior of PIO handlers, i.e. today's "fast" PIO handling to skip the
instruction prior to exiting to userspace.  Full emulation doesn't need
such tricks becase re-emulating the instruction will naturally handle
%rip being changed to point at the reset vector.

Updating %rip prior to executing to userspace has several drawbacks:

  - Userspace sees the wrong %rip on the exit, e.g. if PIO emulation
    fails it will likely yell about the wrong address.
  - Single step exits to userspace for are effectively dropped as
    KVM_EXIT_DEBUG is overwritten with KVM_EXIT_IO.
  - Behavior of PIO emulation is different depending on whether it
    goes down the fast path or the slow path.

Rather than skip the PIO instruction before exiting to userspace,
snapshot the linear %rip and cancel PIO completion if the current
value does not match the snapshot.  For a 64-bit vCPU, i.e. the most
common scenario, the snapshot and comparison has negligible overhead
as VMCS.GUEST_RIP will be cached regardless, i.e. there is no extra
VMREAD in this case.

All other alternatives to snapshotting the linear %rip that don't
rely on an explicit reset announcenment suffer from one corner case
or another.  For example, canceling PIO completion on any write to
%rip fails if userspace does a save/restore of %rip, and attempting to
avoid that issue by canceling PIO only if %rip changed then fails if PIO
collides with the reset %rip.  Attempting to zero in on the exact reset
vector won't work for APs, which means adding more hooks such as the
vCPU's MP_STATE, and so on and so forth.

Checking for a linear %rip match technically suffers from corner cases,
e.g. userspace could theoretically rewrite the underlying code page and
expect a different instruction to execute, or the guest hardcodes a PIO
reset at 0xfffffff0, but those are far, far outside of what can be
considered normal operation.

Fixes: 432baf60eee3 ("KVM: VMX: use kvm_fast_pio_in for handling IN I/O")
Cc: <stable@vger.kernel.org>
Reported-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Although technically the "buggy" behavior goes back 10+ years, I used
the recent VMX change for Fixes since that was the commit that actually
led to a complaint.  Arguably the commit that re-introduced fast IN for
SVM (8370c3d08bd9 "kvm: svm: Add kvm_fast_pio_in support") should be
blamed, but given that his is more along the lines of "that's weird" as
opposed to "the world is burning", err on the side of cuation.

That being said, odds are good that userspace won't even exercise the
rip checks.  Qemu has intentionally re-entered KVM to complete I/O since
commit 9ccfac9ea4 ("kvm: Unconditionally reenter kernel after IO exits")
in early 2011, i.e. testing this required modifying Qemu to not re-enter
the kernel.  And AFIAK no other userspace emulates port-based resets.

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/x86.c              | 36 ++++++++++++++++++++++++---------
 2 files changed, 27 insertions(+), 10 deletions(-)

```
