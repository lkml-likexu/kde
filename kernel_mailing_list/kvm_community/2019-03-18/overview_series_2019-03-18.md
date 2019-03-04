#### [PATCH v2 1/2] kvm/vmx: avoid CPUID faulting leaking to guest
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
cpuid faulting is a feature about CPUID instruction. When cpuif faulting
is enabled, all execution of the CPUID instruction outside system-management
mode (SMM) cause a general-protection (#GP) if the CPL > 0.

About this feature, detailed information can be found at
https://www.intel.com/content/dam/www/public/us/en/documents/application-notes/virtualization-technology-flexmigration-application-note.pdf

Current KVM provides software emulation of this feature for guest.
However, because cpuid faulting takes higher priority over CPUID vm exit (Intel
SDM vol3.25.1.1), there is a risk of leaking cpuid faulting to guest when host
enables it. If host enables cpuid faulting by setting the bit 0 of
MSR_MISC_FEATURES_ENABLES, it will pass to guest since there is no handling of
MSR_MISC_FEATURES_ENABLES yet. As a result, when guest calls CPUID instruction
in CPL > 0, it will generate a #GP instead of CPUID vm eixt.

This issue will cause guest boot failure when guest uses *modprobe*
to load modules. *modprobe* calls CPUID instruction, thus causing #GP in
guest. Since there is no handling of cpuid faulting in #GP handler, guest
fails boot.

To fix this issue, we should switch cpuid faulting bit between host and guest.
Since MSR_MISC_FEATURES_ENABLES is intel-specific, this patch implement the
switching only in vmx. It clears the cpuid faulting bit and save host's
value before switching to guest, and restores the cpuid faulting settings of
host before switching to host.

Because kvm provides the software emulation of cpuid faulting, we can
just clear the cpuid faulting bit in hardware MSR when switching to
guest.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
Changes in v2:
- move the save/restore of cpuid faulting bit to
vmx_prepare_swich_to_guest/vmx_prepare_swich_to_host to avoid every
vmentry RDMSR, based on Paolo's comment.

---
 arch/x86/kvm/vmx/vmx.c | 34 ++++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h |  2 ++
 2 files changed, 36 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: Perserve PSSCR FAKE_SUSPEND bit on guest exit
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
There is a hardware bug in some POWER9 processors where a treclaim in
fake suspend mode can cause an inconsistency in the XER[SO] bit across
the threads of a core, the workaround being to force the core into SMT4
when doing the treclaim.

The FAKE_SUSPEND bit (bit 10) in the PSSCR is used to control whether a
thread is in fake suspend or real suspend. The important difference here
being that thread reconfiguration is blocked in real suspend but not
fake suspend mode.

When we exit a guest which was in fake suspend mode, we force the core
into SMT4 while we do the treclaim in kvmppc_save_tm_hv().
However on the new exit path introduced with the function
kvmhv_run_single_vcpu() we restore the host PSSCR before calling
kvmppc_save_tm_hv() which means that if we were in fake suspend mode we
put the thread into real suspend mode when we clear the
PSSCR[FAKE_SUSPEND] bit. This means that we block thread reconfiguration
and the thread which is trying to get the core into SMT4 before it can
do the treclaim spins forever since it itself is blocking thread
reconfiguration. The result is that that core is essentially lost.

This results in a trace such as:
[   93.512904] CPU: 7 PID: 13352 Comm: qemu-system-ppc Not tainted 5.0.0 #4
[   93.512905] NIP:  c000000000098a04 LR: c0000000000cc59c CTR: 0000000000000000
[   93.512908] REGS: c000003fffd2bd70 TRAP: 0100   Not tainted  (5.0.0)
[   93.512908] MSR:  9000000302883033 <SF,HV,VEC,VSX,FP,ME,IR,DR,RI,LE,TM[SE]>  CR: 22222444  XER: 00000000
[   93.512914] CFAR: c000000000098a5c IRQMASK: 3
[   93.512915] PACATMSCRATCH: 0000000000000001
[   93.512916] GPR00: 0000000000000001 c000003f6cc1b830 c000000001033100 0000000000000004
[   93.512928] GPR04: 0000000000000004 0000000000000002 0000000000000004 0000000000000007
[   93.512930] GPR08: 0000000000000000 0000000000000004 0000000000000000 0000000000000004
[   93.512932] GPR12: c000203fff7fc000 c000003fffff9500 0000000000000000 0000000000000000
[   93.512935] GPR16: 2000000000300375 000000000000059f 0000000000000000 0000000000000000
[   93.512951] GPR20: 0000000000000000 0000000000080053 004000000256f41f c000003f6aa88ef0
[   93.512953] GPR24: c000003f6aa89100 0000000000000010 0000000000000000 0000000000000000
[   93.512956] GPR28: c000003f9e9a0800 0000000000000000 0000000000000001 c000203fff7fc000
[   93.512959] NIP [c000000000098a04] pnv_power9_force_smt4_catch+0x1b4/0x2c0
[   93.512960] LR [c0000000000cc59c] kvmppc_save_tm_hv+0x40/0x88
[   93.512960] Call Trace:
[   93.512961] [c000003f6cc1b830] [0000000000080053] 0x80053 (unreliable)
[   93.512965] [c000003f6cc1b8a0] [c00800001e9cb030] kvmhv_p9_guest_entry+0x508/0x6b0 [kvm_hv]
[   93.512967] [c000003f6cc1b940] [c00800001e9cba44] kvmhv_run_single_vcpu+0x2dc/0xb90 [kvm_hv]
[   93.512968] [c000003f6cc1ba10] [c00800001e9cc948] kvmppc_vcpu_run_hv+0x650/0xb90 [kvm_hv]
[   93.512969] [c000003f6cc1bae0] [c00800001e8f620c] kvmppc_vcpu_run+0x34/0x48 [kvm]
[   93.512971] [c000003f6cc1bb00] [c00800001e8f2d4c] kvm_arch_vcpu_ioctl_run+0x2f4/0x400 [kvm]
[   93.512972] [c000003f6cc1bb90] [c00800001e8e3918] kvm_vcpu_ioctl+0x460/0x7d0 [kvm]
[   93.512974] [c000003f6cc1bd00] [c0000000003ae2c0] do_vfs_ioctl+0xe0/0x8e0
[   93.512975] [c000003f6cc1bdb0] [c0000000003aeb24] ksys_ioctl+0x64/0xe0
[   93.512978] [c000003f6cc1be00] [c0000000003aebc8] sys_ioctl+0x28/0x80
[   93.512981] [c000003f6cc1be20] [c00000000000b3a4] system_call+0x5c/0x70
[   93.512983] Instruction dump:
[   93.512986] 419dffbc e98c0000 2e8b0000 38000001 60000000 60000000 60000000 40950068
[   93.512993] 392bffff 39400000 79290020 39290001 <7d2903a6> 60000000 60000000 7d235214

To fix this we preserve the PSSCR[FAKE_SUSPEND] bit until we call
kvmppc_save_tm_hv() which will mean the core can get into SMT4 and
perform the treclaim. Note kvmppc_save_tm_hv() clears the
PSSCR[FAKE_SUSPEND] bit again so there is no need to explicitly do that.

Fixes: 95a6432ce9038 ("KVM: PPC: Book3S HV: Streamlined guest entry/exit path on P9 for radix guests")

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: export <linux/kvm_para.h> and <asm/kvm_para.h> iif KVM is supported
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
I do not see any consistency about headers_install of <linux/kvm_para.h>
and <asm/kvm_para.h>.

According to my analysis of Linux 5.1-rc1, there are 3 groups:

 [1] Both <linux/kvm_para.h> and <asm/kvm_para.h> are exported

    alpha, arm, hexagon, mips, powerpc, s390, sparc, x86

 [2] <asm/kvm_para.h> is exported, but <linux/kvm_para.h> is not

    arc, arm64, c6x, h8300, ia64, m68k, microblaze, nios2, openrisc,
    parisc, sh, unicore32, xtensa

 [3] Neither <linux/kvm_para.h> nor <asm/kvm_para.h> is exported

    csky, nds32, riscv

This does not match to the actual KVM support. At least, [2] is
half-baked.

Nor do arch maintainers look like they care about this. For example,
commit 0add53713b1c ("microblaze: Add missing kvm_para.h to Kbuild")
exported <asm/kvm_para.h> to user-space in order to fix an in-kernel
build error.

We have two ways to make this consistent:

 [A] export both <linux/kvm_para.h> and <asm/kvm_para.h> for all
     architectures, irrespective of the KVM support

 [B] Match the header export of <linux/kvm_para.h> and <asm/kvm_para.h>
     to the KVM support

My first attempt was [A] because the code looks cleaner, but Paolo
suggested [B].

So, this commit goes with [B].

For most architectures, <asm/kvm_para.h> was moved to the kernel-space.
I changed include/uapi/linux/Kbuild so that it checks generated
asm/kvm_para.h as well as check-in ones.

After this commit, there will be two groups:

 [1] Both <linux/kvm_para.h> and <asm/kvm_para.h> are exported

    arm, arm64, mips, powerpc, s390, x86

 [2] Neither <linux/kvm_para.h> nor <asm/kvm_para.h> is exported

    alpha, arc, c6x, csky, h8300, hexagon, ia64, m68k, microblaze,
    nds32, nios2, openrisc, parisc, riscv, sh, sparc, unicore32, xtensa

Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---

Changes in v2:
 - Fix build error for mips and s390
 - Rebase on top of v5.1-rc1
 - Correct my anylisis of v5.1-rc1

 arch/alpha/include/asm/Kbuild            | 1 +
 arch/alpha/include/uapi/asm/kvm_para.h   | 2 --
 arch/arc/include/asm/Kbuild              | 1 +
 arch/arc/include/uapi/asm/Kbuild         | 1 -
 arch/arm/include/uapi/asm/Kbuild         | 1 +
 arch/arm/include/uapi/asm/kvm_para.h     | 2 --
 arch/c6x/include/asm/Kbuild              | 1 +
 arch/c6x/include/uapi/asm/Kbuild         | 1 -
 arch/h8300/include/asm/Kbuild            | 1 +
 arch/h8300/include/uapi/asm/Kbuild       | 1 -
 arch/hexagon/include/asm/Kbuild          | 1 +
 arch/hexagon/include/uapi/asm/kvm_para.h | 2 --
 arch/ia64/include/asm/Kbuild             | 1 +
 arch/ia64/include/uapi/asm/Kbuild        | 1 -
 arch/m68k/include/asm/Kbuild             | 1 +
 arch/m68k/include/uapi/asm/Kbuild        | 1 -
 arch/microblaze/include/asm/Kbuild       | 1 +
 arch/microblaze/include/uapi/asm/Kbuild  | 1 -
 arch/nios2/include/asm/Kbuild            | 1 +
 arch/nios2/include/uapi/asm/Kbuild       | 1 -
 arch/openrisc/include/asm/Kbuild         | 1 +
 arch/openrisc/include/uapi/asm/Kbuild    | 1 -
 arch/parisc/include/asm/Kbuild           | 1 +
 arch/parisc/include/uapi/asm/Kbuild      | 1 -
 arch/sh/include/asm/Kbuild               | 1 +
 arch/sh/include/uapi/asm/Kbuild          | 1 -
 arch/sparc/include/asm/Kbuild            | 1 +
 arch/sparc/include/uapi/asm/kvm_para.h   | 2 --
 arch/unicore32/include/asm/Kbuild        | 1 +
 arch/unicore32/include/uapi/asm/Kbuild   | 1 -
 arch/xtensa/include/asm/Kbuild           | 1 +
 arch/xtensa/include/uapi/asm/Kbuild      | 1 -
 include/uapi/linux/Kbuild                | 2 ++
 33 files changed, 18 insertions(+), 20 deletions(-)
 delete mode 100644 arch/alpha/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/hexagon/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/sparc/include/uapi/asm/kvm_para.h

```
#### [PATCH][V2] KVM: svm: merge incomplete IPI emulation handling
##### From: Li RongQing <lirongqing@baidu.com>

```c
Invalid int type emulation and target not running emulation have
same codes, which update APIC ICR high/low registers, and emulate
sending the IPI.

so fall through this switch cases to reduce duplicate codes and
wide the comment out to 80 columns

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v1->v2: make cases statements are back-to-back and wide the comment out
        to 80 columns as suggested by Sean Christopherson

 arch/x86/kvm/svm.c | 28 ++++++++++------------------
 1 file changed, 10 insertions(+), 18 deletions(-)

```
