#### [PATCH 01/16] lib: fix match_string() helper when array size is positive
##### From: Alexandru Ardelean <alexandru.ardelean@analog.com>

```c
The documentation the `_match_string()` helper mentions that `n`
(size of the given array) should be:
 * @n: number of strings in the array or -1 for NULL terminated arrays

The behavior of the function is different, in the sense that it exits on
the first NULL element in the array, regardless of whether `n` is -1 or a
positive number.

This patch changes the behavior, to exit the loop when a NULL element is
found and n == -1. Essentially, this aligns the behavior with the
doc-string.

There are currently many users of `match_string()`, and so, in order to go
through them, the next patches in the series will focus on doing some
cosmetic changes, which are aimed at grouping the users of
`match_string()`.

Signed-off-by: Alexandru Ardelean <alexandru.ardelean@analog.com>
---
 lib/string.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH, RFC 01/62] mm: Do no merge VMAs with different encryption KeyIDs
##### From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c
VMAs with different KeyID do not mix together. Only VMAs with the same
KeyID are compatible.

Signed-off-by: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
---
 fs/userfaultfd.c   |  7 ++++---
 include/linux/mm.h |  9 ++++++++-
 mm/madvise.c       |  2 +-
 mm/mempolicy.c     |  3 ++-
 mm/mlock.c         |  2 +-
 mm/mmap.c          | 31 +++++++++++++++++++------------
 mm/mprotect.c      |  2 +-
 7 files changed, 36 insertions(+), 20 deletions(-)

```
#### [PATCH] KVM: lapic: Reuse auto-adjusted timer advance of first stable vCPU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Wanpeng pointed out that auto-tuning the advancement time for every vCPU
can lead to inaccurate wait times, e.g. if the advancement is calculated
while an overcommitted host is under heavy load, then KVM will waste a
lot of time busy waiting if the load decreases, e.g. when neighbour VMs
are idle.

Sidestep this issue and reduce time spent adjusting the advancement by
saving the first stable advancement value and reusing that value for all
*new* vCPUs.  This provides a safe way to auto-adjust the advancement,
minimizes the potential for a poor calculation due to system load, and
preserves the ability for userspace to change the advancement on the fly
(the module parameter is writable when KVM is loaded), as the value set
by userspace takes priority.

Regarding changing the advancement on the fly, doing so is likely less
useful with auto-adjusting, especially now that recognizing a change
requires restarting the VM.  Allowing the two concepts to coexist is
theoretically possible, but would be ugly and slow.  Auto-tuning needs
to track advancement time on a per-vCPU basis (because adjusments are
done relative to the last advancement), so supporting both approaches
would require additional code and conditionals, i.e. overhead, but would
only provide marginal value.  That being said, keep the ability to
change the module param without a reload as it's useful for debug and
testing.

Note, the comment from commit 39497d7660d9 ("KVM: lapic: Track lapic
timer advance per vCPU") about TSC scaling:

  And because virtual_tsc_khz and tsc_scaling_ratio are per-vCPU, the
  correct calibration for a given vCPU may not apply to all vCPUs.

was effectively resolved by commit b6aa57c69cb2 ("KVM: lapic: Convert
guest TSC to host time domain if necessary").  The timer advancement is
calculated and stored in nanoseconds, and operates in the host time
domain, i.e. calculates *host* overhead.  In short, reusing an
advancement time for vCPUs with different TSC scaling is ok.

Fixes: 39497d7660d9 ("KVM: lapic: Track lapic timer advance per vCPU")
Cc: Wanpeng Li <kernellwp@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/lapic.c | 22 ++++++++++++++++++----
 1 file changed, 18 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] kvm: Fix the bitmap range to copy during clear dirty
##### From: Peter Xu <peterx@redhat.com>

```c
kvm_dirty_bitmap_bytes() will return the size of the dirty bitmap of
the memslot rather than the size of bitmap passed over from the ioctl.
Here for KVM_CLEAR_DIRTY_LOG we should only copy exactly the size of
bitmap that covers kvm_clear_dirty_log.num_pages.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: Fix the bitmap range to copy during clear dirty
##### From: Peter Xu <peterx@redhat.com>

```c
kvm_dirty_bitmap_bytes() will return the size of the dirty bitmap of
the memslot rather than the size of bitmap passed over from the ioctl.
Here for KVM_CLEAR_DIRTY_LOG we should only copy exactly the size of
bitmap that covers kvm_clear_dirty_log.num_pages.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] Revert "KVM: nVMX: Expose RDPMC-exiting only when guest supports PMU"
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The RDPMC-exiting control is dependent on the existence of the RDPMC
instruction itself, i.e. is not tied to the "Architectural Performance
Monitoring" feature.  For all intents and purposes, the control exists
on all CPUs with VMX support since RDPMC also exists on all VCPUs with
VMX supported.  Per Intel's SDM:

  The RDPMC instruction was introduced into the IA-32 Architecture in
  the Pentium Pro processor and the Pentium processor with MMX technology.
  The earlier Pentium processors have performance-monitoring counters, but
  they must be read with the RDMSR instruction.

Because RDPMC-exiting always exists, KVM requires the control and refuses
to load if it's not available.  As a result, hiding the PMU from a guest
breaks nested virtualization if the guest attemts to use KVM.

While it's not explicitly stated in the RDPMC pseudocode, the VM-Exit
check for RDPMC-exiting follows standard fault vs. VM-Exit prioritization
for privileged instructions, e.g. occurs after the CPL/CR0.PE/CR4.PCE
checks, but before the counter referenced in ECX is checked for validity.

In other words, the original KVM behavior of injecting a #GP was correct,
and the KVM unit test needs to be adjusted accordingly, e.g. eat the #GP
when the unit test guest (L3 in this case) executes RDPMC without
RDPMC-exiting set in the unit test host (L2).

This reverts commit e51bfdb68725dc052d16241ace40ea3140f938aa.

Fixes: e51bfdb68725 ("KVM: nVMX: Expose RDPMC-exiting only when guest supports PMU")
Reported-by: David Hill <hilld@binarystorm.net>
Cc: Saar Amar <saaramar@microsoft.com>
Cc: Mihai Carabas <mihai.carabas@oracle.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 25 -------------------------
 1 file changed, 25 deletions(-)

```
#### [PATCH 01/16] lib: fix match_string() helper on -1 array size
##### From: Alexandru Ardelean <alexandru.ardelean@analog.com>

```c
The documentation the `_match_string()` helper mentions that `n`
should be:
 * @n: number of strings in the array or -1 for NULL terminated arrays

The behavior of the function is different, in the sense that it exits on
the first NULL element in the array, regardless of whether `n` is -1 or a
positive number.

This patch changes the behavior, to exit the loop when a NULL element is
found and n == -1. Essentially, this aligns the behavior with the
doc-string.

There are currently many users of `match_string()`, and so, in order to go
through them, the next patches in the series will focus on doing some
cosmetic changes, which are aimed at grouping the users of
`match_string()`.

Signed-off-by: Alexandru Ardelean <alexandru.ardelean@analog.com>
---
 lib/string.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2] kvm: nVMX: Set nested_run_pending in vmx_set_nested_state after checks complete
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Aaron Lewis <aaronlewis@google.com>

nested_run_pending=1 implies we have successfully entered guest mode.
Move setting from external state in vmx_set_nested_state() until after
all other checks are complete.

Based on a patch by Aaron Lewis.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com> 
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reported-by: Aaron Lewis <aaronlewis@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Tested-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx/nested.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio: add myself as reviewer
##### From: Cornelia Huck <cohuck@redhat.com>

```c
I'm trying to look at vfio patches, and it's easier if
I'm cc:ed.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] x86/kvm/pmu: Set AMD's virt PMU version to 1
##### From: Borislav Petkov <bp@alien8.de>

```c
From: Borislav Petkov <bp@suse.de>

After commit:

  672ff6cff80c ("KVM: x86: Raise #GP when guest vCPU do not support PMU")

my AMD guests started #GPing like this:

  general protection fault: 0000 [#1] PREEMPT SMP
  CPU: 1 PID: 4355 Comm: bash Not tainted 5.1.0-rc6+ #3
  Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS 1.12.0-1 04/01/2014
  RIP: 0010:x86_perf_event_update+0x3b/0xa0

with Code: pointing to RDPMC. It is RDPMC because the guest has the
hardware watchdog CONFIG_HARDLOCKUP_DETECTOR_PERF enabled which uses
perf. Instrumenting kvm_pmu_rdpmc() some, showed that it fails due to:

  if (!pmu->version)
  	return 1;

which the above commit added. Since AMD's PMU leaves the version at 0,
that causes the #GP injection into the guest.

Set pmu->version arbitrarily to 1 and move it above the non-applicable
struct kvm_pmu members.

Signed-off-by: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Janakarajan Natarajan <Janakarajan.Natarajan@amd.com>
Cc: kvm@vger.kernel.org
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Mihai Carabas <mihai.carabas@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
---
 arch/x86/kvm/pmu_amd.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 1/2] x86: nVMX: Use #DB in nmi and intr tests
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to Intel SDM 26.3.1.5 "Checks on Guest Non-Register State", if
the activity state is HLT, the only events that can be injected are NMI,
MTF and "Those with interruption type hardware exception and vector 1
(debug exception) or vector 18 (machine-check exception)."

Two tests, verify_nmi_window_exit() and verify_intr_window_exit(), try
to do something that real hardware disallows (i.e., fail the VM-entry)
by injecting #UD in HLT-state.  Inject #DB instead as the injection
should succeed in these tests.

Cc: Jim Mattson <jmattson@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx_tests.c | 72 ++++++++++++++++++++++++-------------------------
 1 file changed, 36 insertions(+), 36 deletions(-)

```
