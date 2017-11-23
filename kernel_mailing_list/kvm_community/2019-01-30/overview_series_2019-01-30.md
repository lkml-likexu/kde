#### [PATCH] kvm: x86: Add memcg accounting to KVM allocationsFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
There are many KVM kernel memory allocations which are tied to the life of
the VM process and should be charged to the VM process's cgroup. If the
allocations aren't tied to the process, the OOM killer will not know
that killing the process will free the associated kernel memory.
Add __GFP_ACCOUNT flags to many of the allocations which are not yet being
charged to the VM process's cgroup.

Tested:
	Ran all kvm-unit-tests on a 64 bit Haswell machine, the patch
	introduced no new failures.
	Ran a kernel memory accounting test which creates a VM to touch
	memory and then checks that the kernel memory is within ceratin
	bounds.
	With this patch that memory accounting is more (see below)
	correct.

There remain a few allocations which should be charged to the VM's
cgroup but are not. In x86, they include:
	vcpu->run
	vcpu->arch.pio_data
	kvm->coalesced_mmio_ring
There allocations are unaccounted in this patch because they are mapped
to userspace, and accounting them to a cgroup causes problems. This
should be addressed in a future patch.

Signed-off-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Shakeel Butt <shakeelb@google.com>
---
 arch/x86/kvm/hyperv.c     |  2 +-
 arch/x86/kvm/i8254.c      |  2 +-
 arch/x86/kvm/i8259.c      |  2 +-
 arch/x86/kvm/ioapic.c     |  2 +-
 arch/x86/kvm/lapic.c      |  7 ++++---
 arch/x86/kvm/mmu.c        |  6 +++---
 arch/x86/kvm/page_track.c |  2 +-
 arch/x86/kvm/svm.c        | 23 ++++++++++++-----------
 arch/x86/kvm/vmx/nested.c |  9 +++++++--
 arch/x86/kvm/vmx/vmx.c    | 23 +++++++++++++++++------
 arch/x86/kvm/x86.c        | 16 +++++++++-------
 virt/kvm/coalesced_mmio.c |  3 ++-
 virt/kvm/eventfd.c        |  7 ++++---
 virt/kvm/irqchip.c        |  4 ++--
 virt/kvm/kvm_main.c       | 18 +++++++++---------
 virt/kvm/vfio.c           |  4 ++--
 16 files changed, 76 insertions(+), 54 deletions(-)

```
#### [PATCH v2] cpu/hotplug: Fix "SMT disabled by BIOS" detection for KVM
##### From: Josh Poimboeuf <jpoimboe@redhat.com>

```c
With the following commit:

  73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")

... the hotplug code attempted to detect when SMT was disabled by BIOS,
in which case it reported SMT as permanently disabled.  However, that
code broke a virt hotplug scenario, where the guest is booted with only
primary CPU threads, and a sibling is brought online later.

The problem is that there doesn't seem to be a way to reliably
distinguish between the HW "SMT disabled by BIOS" case and the virt
"sibling not yet brought online" case.  So the above-mentioned commit
was a bit misguided, as it permanently disabled SMT for both cases,
preventing future virt sibling hotplugs.

Going back and reviewing the original problems which were attempted to
be solved by that commit, when SMT was disabled in BIOS:

  1) /sys/devices/system/cpu/smt/control showed "on" instead of
     "notsupported"; and

  2) vmx_vm_init() was incorrectly showing the L1TF_MSG_SMT warning.

I'd propose that we instead consider #1 above to not actually be a
problem.  Because, at least in the virt case, it's possible that SMT
wasn't disabled by BIOS and a sibling thread could be brought online
later.  So it makes sense to just always default the smt control to "on"
to allow for that possibility (assuming cpuid indicates that the CPU
supports SMT).

The real problem is #2, which has a simple fix: change vmx_vm_init() to
query the actual current SMT state -- i.e., whether any siblings are
currently online -- instead of looking at the SMT "control" sysfs value.

So fix it by:

  a) reverting the original "fix" and its followup fix:

     73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")
     bc2d8d262cba ("cpu/hotplug: Fix SMT supported evaluation")

     and

  b) changing vmx_vm_init() to query the actual current SMT state --
     instead of the sysfs control value -- to determine whether the L1TF
     warning is needed.  This also requires the 'sched_smt_present'
     variable to exported, instead of 'cpu_smt_control'.

Fixes: 73d5e2b47264 ("cpu/hotplug: detect SMT disabled by BIOS")
Reported-by: Igor Mammedov <imammedo@redhat.com>
Signed-off-by: Josh Poimboeuf <jpoimboe@redhat.com>
---
v2: export sched_smt_present; unexport cpu_smt_control

 arch/x86/kernel/cpu/bugs.c |  2 +-
 arch/x86/kvm/vmx/vmx.c     |  3 ++-
 include/linux/cpu.h        |  2 --
 kernel/cpu.c               | 33 ++++-----------------------------
 kernel/sched/fair.c        |  1 +
 kernel/smp.c               |  2 --
 6 files changed, 8 insertions(+), 35 deletions(-)

```
#### [PATCH v2 for-4.14-stable] x86,kvm: remove extra kvm_{get,put}_guest_fpu
##### From: Daniel Verkamp <dverkamp@chromium.org>

```c
Commit 4124a4cff344 ("x86,kvm: move qemu/guest FPU switching out
to vcpu_run") applied a patch from upstream, but it appears that it
wasn't backported correctly to 4.14.  The extra out_fpu label and
kvm_put_guest_fpu() added in kvm_arch_vcpu_ioctl_run() result in calling
kvm_put_guest_fpu() twice in a row, corrupting guest state.
Additionally, a duplicate kvm_load_guest_fpu() is added in the middle of
the function.

Fixes: 4124a4cff344 ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")
Signed-off-by: Daniel Verkamp <dverkamp@chromium.org>
---

v2: removed additional redundant kvm_load_guest_fpu()

I'm unsure if this is the right way to send this fix - there is no
corresponding mainline commit to reference, since the code there is
already correct, and the problem was introduced in the cherry-picked
stable backport.  Please let me know if there's a different process for
fixes to stable-only issues.

---

 arch/x86/kvm/x86.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH v2] KVM: x86: Sync the pending Posted-Interrupts
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Some Posted-Interrupts from passthrough devices may be lost or
overwritten when the vCPU is in runnable state.

The SN (Suppress Notification) of PID (Posted Interrupt Descriptor) will
be set when the vCPU is preempted (vCPU in KVM_MP_STATE_RUNNABLE state
but not running on physical CPU). If a posted interrupt coming at this
time, the irq remmaping facility will set the bit of PIR (Posted
Interrupt Requests) without ON (Outstanding Notification).
So this interrupt can't be sync to APIC virtualization register and
will not be handled by Guest because ON is zero.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 arch/x86/kvm/x86.c     | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/6] vfio-ccw: make it safe to access channel programs
##### From: Cornelia Huck <cohuck@redhat.com>

```c
When we get a solicited interrupt, the start function may have
been cleared by a csch, but we still have a channel program
structure allocated. Make it safe to call the cp accessors in
any case, so we can call them unconditionally.

While at it, also make sure that functions called from other parts
of the code return gracefully if the channel program structure
has not been initialized (even though that is a bug in the caller).

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c  | 20 +++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_cp.h  |  2 ++
 drivers/s390/cio/vfio_ccw_fsm.c |  5 +++++
 3 files changed, 26 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio: platform: reset: fix up include directives to remove ccflags-y
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
For the include directive with double-quotes "", the preprocessor
searches the header in the relative path to the current file.

Fix them up, and remove the header search path option.

Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
Acked-by: Eric Auger <eric.auger@redhat.com>
---

 drivers/vfio/platform/reset/Makefile                     | 2 --
 drivers/vfio/platform/reset/vfio_platform_amdxgbe.c      | 2 +-
 drivers/vfio/platform/reset/vfio_platform_bcmflexrm.c    | 2 +-
 drivers/vfio/platform/reset/vfio_platform_calxedaxgmac.c | 2 +-
 4 files changed, 3 insertions(+), 5 deletions(-)

```
