#### [PATCH 01/59] KVM: arm64: Migrate _elx sysreg accessors to msr_s/mrs_s
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Dave Martin <Dave.Martin@arm.com>

Currently, the {read,write}_sysreg_el*() accessors for accessing
particular ELs' sysregs in the presence of VHE rely on some local
hacks and define their system register encodings in a way that is
inconsistent with the core definitions in <asm/sysreg.h>.

As a result, it is necessary to add duplicate definitions for any
system register that already needs a definition in sysreg.h for
other reasons.

This is a bit of a maintenance headache, and the reasons for the
_el*() accessors working the way they do is a bit historical.

This patch gets rid of the shadow sysreg definitions in
<asm/kvm_hyp.h>, converts the _el*() accessors to use the core
__msr_s/__mrs_s interface, and converts all call sites to use the
standard sysreg #define names (i.e., upper case, with SYS_ prefix).

This patch will conflict heavily anyway, so the opportunity taken
to clean up some bad whitespace in the context of the changes is
taken.

The change exposes a few system registers that have no sysreg.h
definition, due to msr_s/mrs_s being used in place of msr/mrs:
additions are made in order to fill in the gaps.

Signed-off-by: Dave Martin <Dave.Martin@arm.com>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Link: https://www.spinics.net/lists/kvm-arm/msg31717.html
[Rebased to v4.21-rc1]
Signed-off-by: Sudeep Holla <sudeep.holla@arm.com>
[Rebased to v5.2-rc5, changelog updates]
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_hyp.h           | 13 ++--
 arch/arm64/include/asm/kvm_emulate.h     | 16 ++---
 arch/arm64/include/asm/kvm_hyp.h         | 50 ++-------------
 arch/arm64/include/asm/sysreg.h          | 35 ++++++++++-
 arch/arm64/kvm/hyp/switch.c              | 14 ++---
 arch/arm64/kvm/hyp/sysreg-sr.c           | 78 ++++++++++++------------
 arch/arm64/kvm/hyp/tlb.c                 | 12 ++--
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c |  2 +-
 arch/arm64/kvm/regmap.c                  |  4 +-
 arch/arm64/kvm/sys_regs.c                | 56 ++++++++---------
 virt/kvm/arm/arch_timer.c                | 24 ++++----
 11 files changed, 148 insertions(+), 156 deletions(-)

```
#### [PATCH v5 1/4] KVM: LAPIC: Make lapic timer unpinned
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Commit 61abdbe0bcc2 ("kvm: x86: make lapic hrtimer pinned") pinned the 
lapic timer to avoid to wait until the next kvm exit for the guest to 
see KVM_REQ_PENDING_TIMER set. There is another solution to give a kick 
after setting the KVM_REQ_PENDING_TIMER bit, make lapic timer unpinned 
will be used in follow up patches.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 8 ++++----
 arch/x86/kvm/x86.c   | 6 +-----
 2 files changed, 5 insertions(+), 9 deletions(-)

```
#### [PATCH v6 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Reviewed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

No changes in v6
---
 arch/x86/include/asm/vmx.h | 1 +
 arch/x86/kvm/cpuid.c       | 2 +-
 arch/x86/kvm/vmx/vmx.c     | 4 ++++
 3 files changed, 6 insertions(+), 1 deletion(-)

```
#### [PULL 01/14] s390/cio: Squash cp_free() and cp_unpin_free()
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Eric Farman <farman@linux.ibm.com>

The routine cp_free() does nothing but call cp_unpin_free(), and while
most places call cp_free() there is one caller of cp_unpin_free() used
when the cp is guaranteed to have not been marked initialized.

This seems like a dubious way to make a distinction, so let's combine
these routines and make cp_free() do all the work.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <20190606202831.44135-2-farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 36 +++++++++++++++-------------------
 1 file changed, 16 insertions(+), 20 deletions(-)

```
#### [PATCH] push: make "HEAD:tags/my-tag" consistently push to a branch
##### From: =?utf-8?b?w4Z2YXIgQXJuZmrDtnLDsCBCamFybWFzb24=?=  <avarab@gmail.com>

```c
When a refspec like "HEAD:tags/my-tag" is pushed where "HEAD" is a
branch, we'll push a *branch* that'll be located at
"refs/heads/tags/my-tag". This is part of the rather straightforward
rules I documented in 2219c09e23 ("push doc: document the DWYM
behavior pushing to unqualified <dst>", 2018-11-13).

However, if there exists a "refs/tags/my-tag" on the remote the
count_refspec_match() logic will, as a result of calling
refname_match(), match partially-qualified RHS of the refspec
"refs/tags/my-tag", because it's in a loop where it tries to match
"tags/my-tag" to "refs/tags/my-tag', then "refs/tags/tags/my-tag" etc.

This resulted in a case[1] where someone on LKML did:

    git push kvm +HEAD:tags/for-linus

Which would have created a new "refs/heads/tags/for-linus" branch in
their "kvm" repository. But since they happened to have an existing
"refs/tags/for-linus" reference we pushed there instead, and replaced
an annotated tag with a lightweight tag.

We do want a RHS ref like "master" to match "refs/heads/master", but
it's confusing and dangerous that the DWYM behavior for matching
partial RHS refspecs acts differently when the start of the RHS
happens to be a second-level namespace under "refs/" namespace like
"tags".

Now we'll print out the following advice when this happens, and act
differently as described therein:

    hint: The <dst> part of the refspec matched both of:
    hint:
    hint:   1. tags/my-tag -> refs/tags/my-tag
    hint:   2. tags/my-tag -> refs/heads/tags/my-tag
    hint:
    hint: Earlier versions of git would have picked (1) as the RHS starts
    hint: with a second-level ref prefix which could be fully-qualified by
    hint: adding 'refs/' in front of it. We now pick (2) which uses the prefix
    hint: inferred from the <src> part of the refspec.
    hint:
    hint: See the "<refspec>..." rules  discussed in 'git help push'.

An earlier version of this patch[2] used the much more heavy-handed
approach of changing this logic in refname_match(). As shown from the
tests that patch needed to modify that results in changes that are
overzealous for fixing this push-specific issue.

The right place to fix this is in match_explicit(). There we can see
if we have both a DWYM match and a match based on the prefix of the
LHS of the refspec, in those cases the match based on the LHS's ref
prefix should win.

1. https://lore.kernel.org/lkml/2d55fd2a-afbf-1b7c-ca82-8bffaa18e0d0@redhat.com/
2. https://public-inbox.org/git/20190526225445.21618-1-avarab@gmail.com/

Signed-off-by: Ævar Arnfjörð Bjarmason <avarab@gmail.com>
---

Now that the 2.22.0 release is out I cleaned this up into a more
sensible patch.

 Documentation/config/advice.txt |  7 +++++++
 Documentation/git-push.txt      | 13 +++++++++++++
 advice.c                        |  2 ++
 advice.h                        |  1 +
 remote.c                        | 23 ++++++++++++++++++++++-
 t/t5505-remote.sh               | 18 ++++++++++++++++++
 6 files changed, 63 insertions(+), 1 deletion(-)

```
#### [PATCH v14 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
#### [PATCH RESEND v3 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

changes in v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
	Resend to update the dependcy KVM link:
	https://lkml.org/lkml/2019/6/21/23
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
