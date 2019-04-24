#### [GIT PULL] KVM changes for Linux 5.2-rc2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit a188339ca5a396acc588e5851ed7e19f66b0ebd9:

  Linux 5.2-rc1 (2019-05-19 15:47:09 -0700)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 66f61c92889ff3ca365161fb29dd36d6354682ba:

  KVM: x86: fix return value for reserved EFER (2019-05-24 21:55:02 +0200)

----------------------------------------------------------------
The usual smattering of fixes and tunings that came in too late for the
merge window, but should not wait four months before they appear in
a release.  I also travelled a bit more than usual in the first part
of May, which didn't help with picking up patches and reports promptly.

----------------------------------------------------------------
Andrew Jones (3):
      kvm: selftests: aarch64: dirty_log_test: fix unaligned memslot size
      kvm: selftests: aarch64: fix default vm mode
      kvm: selftests: aarch64: compile with warnings on

Borislav Petkov (1):
      x86/kvm/pmu: Set AMD's virt PMU version to 1

Christian Borntraeger (2):
      KVM: s390: change default halt poll time to 50us
      KVM: s390: fix memory slot handling for KVM_SET_USER_MEMORY_REGION

Christoffer Dall (1):
      MAINTAINERS: KVM: arm/arm64: Remove myself as maintainer

Dan Carpenter (1):
      KVM: selftests: Fix a condition in test_hv_cpuid()

James Morse (2):
      KVM: arm64: Move pmu hyp code under hyp's Makefile to avoid instrumentation
      KVM: arm/arm64: Move cc/it checks under hyp's Makefile to avoid instrumentation

Jim Mattson (2):
      kvm: x86: Include multiple indices with CPUID leaf 0x8000001d
      kvm: x86: Include CPUID leaf 0x8000001e in kvm's supported CPUID

Paolo Bonzini (10):
      Merge tag 'kvm-s390-master-5.2-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      Merge tag 'kvmarm-fixes-for-5.2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: nVMX: really fix the size checks on KVM_SET_NESTED_STATE
      kvm: selftests: avoid type punning
      kvm: fix compilation on s390
      KVM: selftests: do not blindly clobber registers in guest asm
      KVM: x86: do not spam dmesg with VMCS/VMCB dumps
      KVM: x86/pmu: mask the result of rdpmc according to the width of the counters
      KVM: x86/pmu: do not mask the value that is written to fixed PMUs
      KVM: x86: fix return value for reserved EFER

Peter Xu (1):
      kvm: Check irqchip mode before assign irqfd

Sean Christopherson (1):
      KVM: nVMX: Clear nested_run_pending if setting nested state fails

Stefan Raspl (1):
      tools/kvm_stat: fix fields filter for child events

Suthikulpanit, Suravee (1):
      kvm: svm/avic: fix off-by-one in checking host APIC ID

Thomas Huth (3):
      KVM: selftests: Compile code with warnings enabled
      KVM: selftests: Remove duplicated TEST_ASSERT in hyperv_cpuid.c
      KVM: selftests: Wrap vcpu_nested_state_get/set functions with x86 guard

Wanpeng Li (4):
      KVM: Fix spinlock taken warning during host resume
      KVM: nVMX: Fix using __this_cpu_read() in preemptible context
      KVM: LAPIC: Fix lapic_timer_advance_ns parameter overflow
      KVM: LAPIC: Expose per-vCPU timer_advance_ns to userspace

Wei Yongjun (1):
      KVM: s390: fix typo in parameter description

Yi Wang (1):
      kvm: vmx: Fix -Wmissing-prototypes warnings

 MAINTAINERS                                        |   2 -
 arch/arm/kvm/hyp/Makefile                          |   1 +
 arch/arm64/include/asm/kvm_host.h                  |   3 -
 arch/arm64/kvm/hyp/Makefile                        |   1 +
 arch/arm64/kvm/hyp/switch.c                        |  39 ++++++
 arch/arm64/kvm/pmu.c                               |  38 ------
 arch/s390/include/asm/kvm_host.h                   |   2 +-
 arch/s390/kvm/kvm-s390.c                           |  37 +++---
 arch/x86/kvm/cpuid.c                               |   8 +-
 arch/x86/kvm/debugfs.c                             |  18 +++
 arch/x86/kvm/irq.c                                 |   7 ++
 arch/x86/kvm/irq.h                                 |   1 +
 arch/x86/kvm/pmu.c                                 |  10 +-
 arch/x86/kvm/pmu.h                                 |   3 +-
 arch/x86/kvm/pmu_amd.c                             |   4 +-
 arch/x86/kvm/svm.c                                 |  15 ++-
 arch/x86/kvm/vmx/nested.c                          |  35 +++---
 arch/x86/kvm/vmx/pmu_intel.c                       |  26 ++--
 arch/x86/kvm/vmx/vmx.c                             |  26 ++--
 arch/x86/kvm/vmx/vmx.h                             |   1 +
 arch/x86/kvm/x86.c                                 |   4 +-
 tools/kvm/kvm_stat/kvm_stat                        |  16 ++-
 tools/kvm/kvm_stat/kvm_stat.txt                    |   2 +
 tools/testing/selftests/kvm/Makefile               |   4 +-
 tools/testing/selftests/kvm/dirty_log_test.c       |   8 +-
 tools/testing/selftests/kvm/include/kvm_util.h     |   2 +
 .../testing/selftests/kvm/lib/aarch64/processor.c  |  11 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |   5 +-
 tools/testing/selftests/kvm/lib/ucall.c            |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c |   4 +-
 .../selftests/kvm/x86_64/cr4_cpuid_sync_test.c     |   1 +
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   7 +-
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  |   9 +-
 .../selftests/kvm/x86_64/platform_info_test.c      |   1 -
 tools/testing/selftests/kvm/x86_64/smm_test.c      |   3 +-
 tools/testing/selftests/kvm/x86_64/state_test.c    |   7 +-
 .../testing/selftests/kvm/x86_64/sync_regs_test.c  |  54 ++++----
 .../kvm/x86_64/vmx_close_while_nested_test.c       |   5 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c         |   2 +-
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c     |   5 +-
 virt/kvm/arm/aarch32.c                             | 121 ------------------
 virt/kvm/arm/hyp/aarch32.c                         | 136 +++++++++++++++++++++
 virt/kvm/eventfd.c                                 |   9 ++
 virt/kvm/kvm_main.c                                |   7 +-
 44 files changed, 399 insertions(+), 303 deletions(-)
 create mode 100644 virt/kvm/arm/hyp/aarch32.c
```
#### [RESEND PATCH v3] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Add support to expose Intel V2 Extended Topology Enumeration Leaf for
some new systems with multiple software-visible die within each package.

Per Intel's SDM, when CPUID executes with EAX set to 1FH, the processor
returns information about extended topology enumeration data. Software
must detect the presence of CPUID leaf 1FH by verifying (a) the highest
leaf index supported by CPUID is >= 1FH, and (b) CPUID.1FH:EBX[15:0]
reports a non-zero value.

Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
==changelog==
v3:
- Refine commit message and comment

v2: https://lkml.org/lkml/2019/4/25/1246

- Apply cpuid.1f check rule on Intel SDM page 3-222 Vol.2A
- Add comment to handle 0x1f anf 0xb in common code
- Reduce check time in a descending-break style

v1: https://lkml.org/lkml/2019/4/22/28

 arch/x86/kvm/cpuid.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [RFC/PATCH] refs: tone down the dwimmery in refname_match() for {heads,tags,remotes}/*
##### From: =?utf-8?b?w4Z2YXIgQXJuZmrDtnLDsCBCamFybWFzb24=?=  <avarab@gmail.com>

```c
When a refspec like HEAD:tags/x is pushed where HEAD is a branch,
we'll push a *branch* that'll be located at "refs/heads/tags/x". This
is part of the rather straightforward rules I documented in
2219c09e23 ("push doc: document the DWYM behavior pushing to
unqualified <dst>", 2018-11-13).

However, if there exists a refs/tags/x on the remote the
count_refspec_match() logic will, as a result of calling
refname_match() match the detected branch type of the LHS of the
refspec to refs/tags/x, because it's in a loop where it tries to match
"tags/x" to "refs/tags/X', then "refs/tags/tags/x" etc.

This resulted in a case[1] where someone on LKML did:

    git push kvm +HEAD:tags/for-linus

Which would have created a new "tags/for-linus" branch in their "kvm"
repository, except because they happened to have an existing
"refs/tags/for-linus" reference we pushed there instead, and replaced
an annotated tag with a lightweight tag.

Let's tone this down a bit and not match the more general expansions
if they'd overlap with later expansions.

This patch is a hack, and should not be applied. We probably want to
fix this for "push", but we use refname_match() all over the place. We
probably want to start by undoing part of
54457fe509 ("refname_match(): always use the rules in
ref_rev_parse_rules", 2014-01-14) and having special rules just for
push.

Furthermore ref_rev_parse_rules is used elsewhere, should we be doing
this in other places? I think not if we undo most of 54457fe509 and
can just have a custom matcher just for count_refspec_match(). That
one shouldn't need any sort of magic, because elsewhere in the remote
push DWYM code we try to add implicit refs/{tags,heads}/ prefixes.

As the t/t5150-request-pull.sh change shows this results in a failing
test where a local "full" branch is being pushed to a remote
"refs/tags/full". So maybe this is something LKML people actually want
for some reason.

1. https://lore.kernel.org/lkml/2d55fd2a-afbf-1b7c-ca82-8bffaa18e0d0@redhat.com/

Signed-off-by: Ævar Arnfjörð Bjarmason <avarab@gmail.com>
---

On Sun, May 26 2019, Linus Torvalds wrote:

> On Sun, May 26, 2019 at 10:53 AM Paolo Bonzini <pbonzini@redhat.com> wrote:
>>
>> The interesting thing is that not only git will treat lightweight tags
>> like, well, tags:
>
> Yeah, that's very much by design - lightweight tags are very
> comvenient for local temporary stuff where you don't want signing etc
> (think automated test infrastructure, or just local reminders).
>
>> In addition, because I _locally_ had a tag object that
>> pointed to the same commit and had the same name, git-request-pull
>> included my local tag's message in its output!  I wonder if this could
>> be considered a bug.
>
> Yeah, I think git request-pull should at least *warn* about the tag
> not being the same object locally as in the remote you're asking me to
> pull.
>
> Are you sure you didn't get a warning, and just missed it? But adding
> Junio and the Git list just as a possible heads-up for this in case
> git request-pull really only compares the object the tag points to,
> rather than the SHA1 of the tag itself.

This behavior looks like a bug to me. This RFC-quality patch is an
initial stab at fixing it, and is all I had time for today.

 refs.c                   |  8 +++++++-
 t/t5150-request-pull.sh  |  2 +-
 t/t5505-remote.sh        | 17 +++++++++++++++++
 t/t9101-git-svn-props.sh | 12 ++++++------
 4 files changed, 31 insertions(+), 8 deletions(-)

```
#### [PATCH v8 01/29] driver core: Add per device iommu param
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

DMA faults can be detected by IOMMU at device level. Adding a pointer
to struct device allows IOMMU subsystem to report relevant faults
back to the device driver for further handling.
For direct assigned device (or user space drivers), guest OS holds
responsibility to handle and respond per device IOMMU fault.
Therefore we need fault reporting mechanism to propagate faults beyond
IOMMU subsystem.

There are two other IOMMU data pointers under struct device today, here
we introduce iommu_param as a parent pointer such that all device IOMMU
data can be consolidated here. The idea was suggested here by Greg KH
and Joerg. The name iommu_param is chosen here since iommu_data has been used.

Suggested-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Reviewed-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Link: https://lkml.org/lkml/2017/10/6/81
---
 include/linux/device.h | 3 +++
 1 file changed, 3 insertions(+)

```
