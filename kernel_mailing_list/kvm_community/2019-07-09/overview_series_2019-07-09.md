#### [PATCH 01/18] arm64: assembler: Switch ESB-instruction with a vanilla nop if !ARM64_HAS_RAS
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: James Morse <james.morse@arm.com>

The ESB-instruction is a nop on CPUs that don't implement the RAS
extensions. This lets us use it in places like the vectors without
having to use alternatives.

If someone disables CONFIG_ARM64_RAS_EXTN, this instruction still has
its RAS extensions behaviour, but we no longer read DISR_EL1 as this
register does depend on alternatives.

This could go wrong if we want to synchronize an SError from a KVM
guest. On a CPU that has the RAS extensions, but the KConfig option
was disabled, we consume the pending SError with no chance of ever
reading it.

Hide the ESB-instruction behind the CONFIG_ARM64_RAS_EXTN option,
outputting a regular nop if the feature has been disabled.

Reported-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: James Morse <james.morse@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/include/asm/assembler.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2 1/3] Documentation: kvm: Convert cpuid.txt to .rst
##### From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

```c
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Convert cpuid.txt to .rst format to be parsable by sphinx.

Change format and spacing to make function definitions and return values
much more clear. Also added a table that is parsable by sphinx and makes
the information much more clean. Updated Author email to their new
active email address. Added license identifier with the consent of the
author. 

Signed-off-by: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
---
 Changes since v2: 
 + added updated Author email address
 + changed table to simpler format
 - removed function bolding from v1
 Changes since v1:
 + Converted doc to .rst format
 
 Documentation/virtual/kvm/cpuid.rst | 99 +++++++++++++++++++++++++++++
 Documentation/virtual/kvm/cpuid.txt | 83 ------------------------
 2 files changed, 99 insertions(+), 83 deletions(-)
 create mode 100644 Documentation/virtual/kvm/cpuid.rst
 delete mode 100644 Documentation/virtual/kvm/cpuid.txt

diff --git a/Documentation/virtual/kvm/cpuid.rst b/Documentation/virtual/kvm/cpuid.rst
new file mode 100644
index 000000000000..644c53687861
--- /dev/null
+++ b/Documentation/virtual/kvm/cpuid.rst
@@ -0,0 +1,99 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+==============
+KVM CPUID bits
+==============
+
+:Author: Glauber Costa <glommer@gmail.com>
+
+A guest running on a kvm host, can check some of its features using
+cpuid. This is not always guaranteed to work, since userspace can
+mask-out some, or even all KVM-related cpuid features before launching
+a guest.
+
+KVM cpuid functions are:
+
+function: KVM_CPUID_SIGNATURE (0x40000000)
+
+returns::
+
+   eax = 0x40000001
+   ebx = 0x4b4d564b
+   ecx = 0x564b4d56
+   edx = 0x4d
+
+Note that this value in ebx, ecx and edx corresponds to the string "KVMKVMKVM".
+The value in eax corresponds to the maximum cpuid function present in this leaf,
+and will be updated if more functions are added in the future.
+Note also that old hosts set eax value to 0x0. This should
+be interpreted as if the value was 0x40000001.
+This function queries the presence of KVM cpuid leafs.
+
+function: define KVM_CPUID_FEATURES (0x40000001)
+
+returns::
+
+          ebx, ecx
+          eax = an OR'ed group of (1 << flag)
+
+where ``flag`` is defined as below:
+
+================================= =========== ================================
+flag                              value       meaning
+================================= =========== ================================
+KVM_FEATURE_CLOCKSOURCE           0           kvmclock available at msrs
+                                              0x11 and 0x12
+
+KVM_FEATURE_NOP_IO_DELAY          1           not necessary to perform delays 
+                                              on PIO operations
+
+KVM_FEATURE_MMU_OP                2           deprecated
+
+KVM_FEATURE_CLOCKSOURCE2          3           kvmclock available at msrs
+
+                                              0x4b564d00 and 0x4b564d01
+KVM_FEATURE_ASYNC_PF              4           async pf can be enabled by
+                                              writing to msr 0x4b564d02
+
+KVM_FEATURE_STEAL_TIME            5           steal time can be enabled by
+                                              writing to msr 0x4b564d03
+
+KVM_FEATURE_PV_EOI                6           paravirtualized end of interrupt
+                                              handler can be enabled by
+                                              writing to msr 0x4b564d04
+
+KVM_FEATURE_PV_UNHAULT            7           guest checks this feature bit
+                                              before enabling paravirtualized
+                                              spinlock support
+
+KVM_FEATURE_PV_TLB_FLUSH          9           guest checks this feature bit
+                                              before enabling paravirtualized
+                                              tlb flush
+
+KVM_FEATURE_ASYNC_PF_VMEXIT       10          paravirtualized async PF VM EXIT
+                                              can be enabled by setting bit 2
+                                              when writing to msr 0x4b564d02
+
+KVM_FEATURE_PV_SEND_IPI           11          guest checks this feature bit
+                                              before enabling paravirtualized 
+                                              sebd IPIs
+
+KVM_FEATURE_CLOCSOURCE_STABLE_BIT 24          host will warn if no guest-side
+                                              per-cpu warps are expeced in
+                                              kvmclock
+================================= =========== ================================
+
+::
+
+      edx = an OR'ed group of (1 << flag)
+
+Where ``flag`` here is defined as below:
+
+================== ============ =================================
+flag               value        meaning
+================== ============ =================================
+KVM_HINTS_REALTIME 0            guest checks this feature bit to
+                                determine that vCPUs are never
+                                preempted for an unlimited time
+                                allowing optimizations
+================== ============ =================================
diff --git a/Documentation/virtual/kvm/cpuid.txt b/Documentation/virtual/kvm/cpuid.txt
```
#### [GIT PULL] KVM/arm updates for Linux 5.3
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Radim, Paolo,

This is the (slightly delayed) KVM/arm updates for 5.3. This time
around, some PMU emulation improvements, the ability to save/restore
the Spectre mitigation state, better SError handling that double as
the workaround for a N1 erratum, a 32bit fix for a corrupted MPIDR,
and yet another pre-NV cleanup.

Please pull,

	M.

The following changes since commit 4b972a01a7da614b4796475f933094751a295a2f:

  Linux 5.2-rc6 (2019-06-22 16:01:36 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvm-arm-for-5.3

for you to fetch changes up to 1e0cf16cdad1ba53e9eeee8746fe57de42f20c97:

  KVM: arm/arm64: Initialise host's MPIDRs by reading the actual register (2019-07-08 16:29:48 +0100)

----------------------------------------------------------------
KVM/arm updates for 5.3

- Add support for chained PMU counters in guests
- Improve SError handling
- Handle Neoverse N1 erratum #1349291
- Allow side-channel mitigation status to be migrated
- Standardise most AArch64 system register accesses to msr_s/mrs_s
- Fix host MPIDR corruption on 32bit

----------------------------------------------------------------
Andre Przywara (3):
      arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
      KVM: arm/arm64: Add save/restore support for firmware workaround state
      KVM: doc: Add API documentation on the KVM_REG_ARM_WORKAROUNDS register

Andrew Murray (5):
      KVM: arm/arm64: Rename kvm_pmu_{enable/disable}_counter functions
      KVM: arm/arm64: Extract duplicated code to own function
      KVM: arm/arm64: Re-create event when setting counter value
      KVM: arm/arm64: Remove pmc->bitmask
      KVM: arm/arm64: Support chained PMU counters

Dave Martin (1):
      KVM: arm64: Migrate _elx sysreg accessors to msr_s/mrs_s

James Morse (8):
      arm64: assembler: Switch ESB-instruction with a vanilla nop if !ARM64_HAS_RAS
      KVM: arm64: Abstract the size of the HYP vectors pre-amble
      KVM: arm64: Make indirect vectors preamble behaviour symmetric
      KVM: arm64: Consume pending SError as early as possible
      KVM: arm64: Defer guest entry when an asynchronous exception is pending
      arm64: Update silicon-errata.txt for Neoverse-N1 #1349291
      KVM: arm64: Re-mask SError after the one instruction window
      KVM: arm64: Skip more of the SError vaxorcism

Marc Zyngier (1):
      KVM: arm/arm64: Initialise host's MPIDRs by reading the actual register

 Documentation/arm64/silicon-errata.txt   |   1 +
 Documentation/virtual/kvm/arm/psci.txt   |  31 +++
 arch/arm/include/asm/kvm_emulate.h       |  10 +
 arch/arm/include/asm/kvm_host.h          |  18 +-
 arch/arm/include/asm/kvm_hyp.h           |  13 +-
 arch/arm/include/uapi/asm/kvm.h          |  12 ++
 arch/arm64/include/asm/assembler.h       |   4 +
 arch/arm64/include/asm/cpufeature.h      |   6 +
 arch/arm64/include/asm/kvm_asm.h         |   6 +
 arch/arm64/include/asm/kvm_emulate.h     |  30 ++-
 arch/arm64/include/asm/kvm_host.h        |  23 +-
 arch/arm64/include/asm/kvm_hyp.h         |  50 +----
 arch/arm64/include/asm/sysreg.h          |  35 +++-
 arch/arm64/include/uapi/asm/kvm.h        |  10 +
 arch/arm64/kernel/cpu_errata.c           |  23 +-
 arch/arm64/kernel/traps.c                |   4 +
 arch/arm64/kvm/hyp/entry.S               |  36 +++-
 arch/arm64/kvm/hyp/hyp-entry.S           |  30 ++-
 arch/arm64/kvm/hyp/switch.c              |  14 +-
 arch/arm64/kvm/hyp/sysreg-sr.c           |  78 +++----
 arch/arm64/kvm/hyp/tlb.c                 |  12 +-
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c |   2 +-
 arch/arm64/kvm/regmap.c                  |   4 +-
 arch/arm64/kvm/sys_regs.c                |  60 +++---
 arch/arm64/kvm/va_layout.c               |   7 +-
 include/kvm/arm_pmu.h                    |  11 +-
 virt/kvm/arm/arch_timer.c                |  24 +--
 virt/kvm/arm/arm.c                       |   3 +-
 virt/kvm/arm/pmu.c                       | 350 +++++++++++++++++++++++++------
 virt/kvm/arm/psci.c                      | 149 +++++++++++--
 30 files changed, 775 insertions(+), 281 deletions(-)

From patchwork Tue Jul  9 12:24:51 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 11036889
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D89D138B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jul 2019 12:25:26 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 6C66F27FB1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jul 2019 12:25:26 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 602C52873E; Tue,  9 Jul 2019 12:25:26 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id E5F6B27FB1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  9 Jul 2019 12:25:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726618AbfGIMZZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 9 Jul 2019 08:25:25 -0400
Received: from foss.arm.com ([217.140.110.172]:42656 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726591AbfGIMZZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Jul 2019 08:25:25 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2A59ACFC;
        Tue,  9 Jul 2019 05:25:24 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com (unknown [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 5F1B33F59C;
        Tue,  9 Jul 2019 05:25:22 -0700 (PDT)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andre Przywara <andre.przywara@arm.com>,
        Andrew Murray <andrew.murray@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Steven Price <steven.price@arm.com>,
        Sudeep Holla <sudeep.holla@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 02/18] KVM: arm64: Abstract the size of the HYP vectors
 pre-amble
Date: Tue,  9 Jul 2019 13:24:51 +0100
Message-Id: <20190709122507.214494-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190709122507.214494-1-marc.zyngier@arm.com>
References: <20190709122507.214494-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: James Morse <james.morse@arm.com>

The EL2 vector hardening feature causes KVM to generate vectors for
each type of CPU present in the system. The generated sequences already
do some of the early guest-exit work (i.e. saving registers). To avoid
duplication the generated vectors branch to the original vector just
after the preamble. This size is hard coded.

Adding new instructions to the HYP vector causes strange side effects,
which are difficult to debug as the affected code is patched in at
runtime.

Add KVM_VECTOR_PREAMBLE to tell kvm_patch_vector_branch() how big
the preamble is. The valid_vect macro can then validate this at
build time.

Reviewed-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: James Morse <james.morse@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/include/asm/kvm_asm.h |  6 ++++++
 arch/arm64/kvm/hyp/hyp-entry.S   | 18 +++++++++++++++++-
 arch/arm64/kvm/va_layout.c       |  7 +++----
 3 files changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/2] KVM: nVMX: add tracepoint for failed nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Debugging a failed VM-Enter is often like searching for a needle in a
haystack, e.g. there are over 80 consistency checks that funnel into
the "invalid control field" error code.  One way to expedite debug is
to run the buggy code as an L1 guest under KVM (and pray that the
failing check is detected by KVM).  However, extracting useful debug
information out of L0 KVM requires attaching a debugger to KVM and/or
modifying the source, e.g. to log which check is failing.

Make life a little less painful for VMM developers and add a tracepoint
for failed VM-Enter consistency checks.  Ideally the tracepoint would
capture both what check failed and precisely why it failed, but logging
why a checked failed is difficult to do in a generic tracepoint without
resorting to invasive techniques, e.g. generating a custom string on
failure.  That being said, for the vast majority of VM-Enter failures
the most difficult step is figuring out exactly what to look at, e.g.
figuring out which bit was incorrectly set in a control field is usually
not too painful once the guilty field as been identified.

To reach a happy medium between precision and ease of use, simply log
the code that detected a failed check, using a macro to execute the
check and log the trace event on failure.  This approach enables tracing
arbitrary code, e.g. it's not limited to function calls or specific
formats of checks, and the changes to the existing code are minimally
invasive.  A macro with a two-character name is desirable as usage of
the macro doesn't result in overly long lines or confusing alignment,
while still retaining some amount of readability.  I.e. a one-character
name is a little too terse, and a three-character name results in the
contents being passed to the macro aligning with an indented line when
the macro is used an in if-statement, e.g.:

        if (VCC(nested_vmx_check_long_line_one(...) &&
                nested_vmx_check_long_line_two(...)))
                return -EINVAL;

And that is the story of how the CC(), a.k.a. Consistency Check, macro
got its name.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/trace.h      |  19 +++
 arch/x86/kvm/vmx/nested.c | 258 ++++++++++++++++++++------------------
 arch/x86/kvm/x86.c        |   1 +
 3 files changed, 154 insertions(+), 124 deletions(-)

```
#### [PATCH] vhost: fix null pointer dereference in vhost_del_umem_range
##### From: Denis Kirjanov <kda@linux-powerpc.org>

```c
> UBSAN: Undefined behaviour in ../drivers/vhost/vhost.c:52:1
> member access within null pointer of type 'struct rb_root'
> CPU: 2 PID: 1450 Comm: syz-executor493 Not tainted
> 4.12.14-525.g4d6309b-default #1 SLE15 (unreleased)
> Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS
> 1.0.0-prebuilt.qemu-project.org 04/01/2014
> Call Trace:
>  __dump_stack lib/dump_stack.c:16 [inline]
>  dump_stack+0xc6/0x159 lib/dump_stack.c:52
>  ubsan_epilogue+0xe/0x81 lib/ubsan.c:164
>  handle_missaligned_access lib/ubsan.c:299 [inline]
>  __ubsan_handle_type_mismatch+0x2ed/0x44e lib/ubsan.c:325
>  vhost_chr_write_iter+0x103e/0x1330 [vhost]
>  call_write_iter include/linux/fs.h:1764 [inline]
>  new_sync_write fs/read_write.c:497 [inline]
>  __vfs_write+0x67c/0x9b0 fs/read_write.c:510
>  vfs_write+0x1a2/0x610 fs/read_write.c:558
>  SYSC_write fs/read_write.c:605 [inline]
>  SyS_write+0xd8/0x1f0 fs/read_write.c:597
>  do_syscall_64+0x26b/0x6e0 arch/x86/entry/common.c:284
>  entry_SYSCALL_64_after_hwframe+0x3d/0xa2
> RIP: 0033:0x7fdb7687a739
> RSP: 002b:00007ffd48719f38 EFLAGS: 00000213 ORIG_RAX: 0000000000000001
> RAX: ffffffffffffffda RBX: 0000000000000000 RCX: 00007fdb7687a739
> RDX: 0000000000000068 RSI: 0000000020000300 RDI: 0000000000000003
> RBP: 00000000004006f0 R08: 0000000000000000 R09: 0000000000000000
> R10: 0000000000000000 R11: 0000000000000213 R12: 00000000004004a0
> R13: 00007ffd4871a020 R14: 0000000000000000 R15: 0000000000000000
> ================================================================================
> kasan: CONFIG_KASAN_INLINE enabled
> kasan: GPF could be caused by NULL-ptr deref or user memory access
> general protection fault: 0000 [#1] SMP KASAN PTI
> Modules linked in: vhost_net tun vhost tap af_packet iscsi_ibft
> iscsi_boot_sysfs bochs_drm ttm ppdev drm_kms_helper drm
> drm_panel_orientation_quirks joydev e1000 syscopyarea sysfillrect
> pcspkr sysimgblt fb_sys_fops i2c_piix4 parport_pc parport qemu_fw_cfg
> button ext4 crc16 jbd2 mbcache sr_mod cdrom sd_mod ata_generic
> ata_piix ahci libahci libata serio_raw floppy sg dm_multipath dm_mod
> scsi_dh_rdac scsi_dh_emc scsi_dh_alua scsi_mod autofs4
> Supported: No, Unreleased kernel
> CPU: 2 PID: 1450 Comm: syz-executor493 Not tainted
> 4.12.14-525.g4d6309b-default #1 SLE15 (unreleased)
> Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS
> 1.0.0-prebuilt.qemu-project.org 04/01/2014
> task: ffff88004b858040 task.stack: ffff88004a820000
> RIP: 0010:vhost_chr_write_iter+0x525/0x1330 [vhost]
> RSP: 0018:ffff88004a827a38 EFLAGS: 00010246
> RAX: dffffc0000000000 RBX: 1ffff10009504f51 RCX: 0000000000000000
> RDX: 0000000000000000 RSI: 0000000000000202 RDI: ffffed0009504f40
> RBP: 0000000000000000 R08: 0000000000000000 R09: 0000000000000000
> R10: 1ffff10009504ec1 R11: 0000000000000000 R12: 0000000020000040
> R13: dffffc0000000000 R14: ffff8800352f0000 R15: ffffed0006a5e005
> FS:  00007fdb76f79740(0000) GS:ffff880060d00000(0000)
> knlGS:0000000000000000
> CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
> CR2: 000055b42161d980 CR3: 000000003422c000 CR4: 00000000000006e0
> Call Trace:
>  call_write_iter include/linux/fs.h:1764 [inline]
>  new_sync_write fs/read_write.c:497 [inline]
>  __vfs_write+0x67c/0x9b0 fs/read_write.c:510
>  vfs_write+0x1a2/0x610 fs/read_write.c:558
>  SYSC_write fs/read_write.c:605 [inline]
>  SyS_write+0xd8/0x1f0 fs/read_write.c:597
>  do_syscall_64+0x26b/0x6e0 arch/x86/entry/common.c:284
>  entry_SYSCALL_64_after_hwframe+0x3d/0xa2
> RIP: 0033:0x7fdb7687a739
> RSP: 002b:00007ffd48719f38 EFLAGS: 00000213 ORIG_RAX: 0000000000000001
> RAX: ffffffffffffffda RBX: 0000000000000000 RCX: 00007fdb7687a739
> RDX: 0000000000000068 RSI: 0000000020000300 RDI: 0000000000000003
> RBP: 00000000004006f0 R08: 0000000000000000 R09: 0000000000000000
> R10: 0000000000000000 R11: 0000000000000213 R12: 00000000004004a0
> R13: 00007ffd4871a020 R14: 0000000000000000 R15: 0000000000000000
> Code: fc ff df 80 3c 02 00 0f 85 3c 0b 00 00 49 8b 6e 60 48 85 ed 0f
> 84 1c 0b 00 00 48 89 ea 48 b8 00 00 00 00 00 fc ff df 48 c1 ea 03 <80>
> 3c 02 00 0f 85 f4 0a 00 00 4c 8b 7d 00 4d 85 ff 0f 84 e7 06
> RIP: vhost_chr_write_iter+0x525/0x1330 [vhost] RSP: ffff88004a827a38
> ---[ end trace 49849730b5255f76 ]---

Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")

Signed-off-by: Denis Kirjanov <kda@linux-powerpc.org>
---
 drivers/vhost/vhost.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
