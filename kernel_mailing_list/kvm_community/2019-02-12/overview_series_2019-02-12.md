#### [PATCH 1/3] Revert "contrib/vhost-user-blk: fix the compilation issue"
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Commit a56de056c91f8 squashed the following two unrelated commits
at once:

- "contrib/vhost-user-blk: fix the compilation issue"
  (Message-Id: 1547615970-23545-2-git-send-email-changpeng.liu@intel.com)
- "i386/kvm: ignore masked irqs when update msi routes"
  (Message-Id: 20190116030815.27273-5-peterx@redhat.com)

While the git history remains bisectable, having a commit that changes
MSI/MSIX code but describes it as "fix vhost-user-blk compilation" is
rather confusing.
Revert the offending commit to properly apply both patches separately.

Reported-by: Peter Xu <peterx@redhat.com>
Fixes: a56de056c91f8
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 contrib/vhost-user-blk/vhost-user-blk.c |  6 +-----
 target/i386/kvm.c                       | 14 +++-----------
 2 files changed, 4 insertions(+), 16 deletions(-)

```
#### [PATCH 1/4] vfio: expand minor range when registering chrdev region
##### From: Chengguang Xu <cgxu519@gmx.com>

```c
Actually, total amount of available minor number
for a single major is MINORMARK + 1. So expand
minor range when registering chrdev region.

Signed-off-by: Chengguang Xu <cgxu519@gmx.com>
---
 drivers/vfio/vfio.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: arm/arm64: Update MAINTAINERS entries
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
For historical reasons, KVM/arm and KVM/arm64 have had different
entries in the MAINTAINER file. This makes little sense, as they are
maintained together.

On top of that, we have a bunch of talented people helping with
the reviewing, and they deserve to be mentionned in the consolidated
entry.

Acked-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Acked-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Acked-by: James Morse <james.morse@arm.com>
---
 MAINTAINERS | 18 +++++++-----------
 1 file changed, 7 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH 01/15] KVM: Add a "-t" option to run a specific test
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
x86's nested-VMX test space is massive, to the point where the group
option, "-g", does not provide sufficient granularity, e.g. a user may
want to run the core VMX tests but not the VMCS shadow tests, which take
an absurdly long time to run due to exhuastively testing all VMCS field
values.

Note that x86's config is currently a bit of a train wreck as far as VMX
is concerned; the "-t" option is of limited value until the config is
revamped.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 run_tests.sh         | 6 +++++-
 scripts/runtime.bash | 6 +++---
 2 files changed, 8 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] KVM: nVMX: Remove redundant masking with allowed exec controls mask
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
setup_ept() explicitly checks that it can enable EPT and the starting
values for the controls are pulled from the VMCS.  The only way the
masking has any effect is if hardware (or a lower VMM) reads out a
value that conflicts with its allowed settings, i.e. hardware is
seriously borked.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 x86/vmx_tests.c | 11 ++---------
 1 file changed, 2 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
Errata#1090:

On a nested data page fault when CR.SMAP=1 and the guest data read
generates a SMAP violation, GuestInstrBytes field of the VMCB on a
VMEXIT will incorrectly return 0h instead the correct guest
instruction bytes .

Recommend Workaround:

To determine what instruction the guest was executing the hypervisor
will have to decode the instruction at the instruction pointer.

The recommended workaround can not be implemented for the SEV
guest because guest memory is encrypted with the guest specific key,
and instruction decoder will not be able to decode the instruction
bytes. If we hit this errata in the SEV guest then inject #GP into
the guest and log the message.

Cc: Jim Mattson <jmattson@google.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Reported-by: Venkatesh Srinivas <venkateshs@google.com>
---

Errata link:
https://www.amd.com/system/files/TechDocs/55449_Fam_17h_M_00h-0Fh_Rev_Guide.pdf

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu.c              |  6 ++++--
 arch/x86/kvm/svm.c              | 32 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 4 files changed, 44 insertions(+), 2 deletions(-)

```
#### [PATCH kvmtool] setup: Add /etc/alternatives to host mirrors dirs
##### From: Dmitry Monakhov <dmonakhov@openvz.org>

```c
From: Dmitry Monakhov <dmtrmonakhov@yandex-team.ru>

Many general purpose binaries in Ubuntu depens on /etc/alternatives directory
Example:
$ ls -lh /usr/bin/awk
lrwxrwxrwx 1 root root 21 апр 14  2017 /usr/bin/awk -> /etc/alternatives/awk
So such binaries will not works inside guest
$ echo 'awk -v' >  t.sh ; lkvm run -c 2 --sandbox t.sh
 /virt/sandbox.sh: 1: /virt/sandbox.sh: awk: not found

Let's forward this dir to guest-fs and make life easier for ubuntu users.
This will not break anything even if this directory not exits.
---
 builtin-setup.c | 1 +
 1 file changed, 1 insertion(+)

```
