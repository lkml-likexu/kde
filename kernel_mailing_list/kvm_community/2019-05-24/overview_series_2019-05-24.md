#### [PATCH 1/3] MAINTAINERS: KVM: arm/arm64: Remove myself as maintainer
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Christoffer Dall <christoffer.dall@arm.com>

I no longer have time to actively review patches and manage the tree and
it's time to make that official.

Huge thanks to the incredible Linux community and all the contributors
who have put up with me over the past years.

I also take this opportunity to remove the website link to the Columbia
web page, as that information is no longer up to date and I don't know
who manages that anymore.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 MAINTAINERS | 2 --
 1 file changed, 2 deletions(-)

```
#### [GIT PULL] KVM/arm updates for 5.2-rc2
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

This is the first batch of KVM/arm fixes for 5.2. The biggest item on
the menu is Christoffer removing himself from the MAINTAINERS
file. He'll be missed. The rest is a set of fixes moving some code
around to prevent KASAN and co from crashing the kernel on non-VHE
systems.

Please pull,

	M.

The following changes since commit a188339ca5a396acc588e5851ed7e19f66b0ebd9:

  Linux 5.2-rc1 (2019-05-19 15:47:09 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.2

for you to fetch changes up to 623e1528d4090bd1abaf93ec46f047dee9a6fb32:

  KVM: arm/arm64: Move cc/it checks under hyp's Makefile to avoid instrumentation (2019-05-24 14:53:20 +0100)

----------------------------------------------------------------
KVM/arm updates for 5.2-rc2

- Correctly annotate HYP-callable code to be non-traceable
- Remove Christoffer from the MAINTAINERS file as his request

----------------------------------------------------------------
Christoffer Dall (1):
      MAINTAINERS: KVM: arm/arm64: Remove myself as maintainer

James Morse (2):
      KVM: arm64: Move pmu hyp code under hyp's Makefile to avoid instrumentation
      KVM: arm/arm64: Move cc/it checks under hyp's Makefile to avoid instrumentation

 MAINTAINERS                       |   2 -
 arch/arm/kvm/hyp/Makefile         |   1 +
 arch/arm64/include/asm/kvm_host.h |   3 -
 arch/arm64/kvm/hyp/Makefile       |   1 +
 arch/arm64/kvm/hyp/switch.c       |  39 +++++++++++
 arch/arm64/kvm/pmu.c              |  38 -----------
 virt/kvm/arm/aarch32.c            | 121 ---------------------------------
 virt/kvm/arm/hyp/aarch32.c        | 136 ++++++++++++++++++++++++++++++++++++++
 8 files changed, 177 insertions(+), 164 deletions(-)
 create mode 100644 virt/kvm/arm/hyp/aarch32.c

From patchwork Fri May 24 14:47:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 10959989
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B14F3933
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 May 2019 14:48:05 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 9FD792887B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 May 2019 14:48:05 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 9405128942; Fri, 24 May 2019 14:48:05 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 0886F28887
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 May 2019 14:48:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404202AbfEXOsE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 May 2019 10:48:04 -0400
Received: from usa-sjc-mx-foss1.foss.arm.com ([217.140.101.70]:44500 "EHLO
        foss.arm.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404198AbfEXOsD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 May 2019 10:48:03 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.72.51.249])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5A32D1682;
        Fri, 24 May 2019 07:48:03 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B133B3F575;
        Fri, 24 May 2019 07:48:01 -0700 (PDT)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/3] KVM: arm64: Move pmu hyp code under hyp's Makefile to
 avoid instrumentation
Date: Fri, 24 May 2019 15:47:44 +0100
Message-Id: <20190524144745.227242-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190524144745.227242-1-marc.zyngier@arm.com>
References: <20190524144745.227242-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: James Morse <james.morse@arm.com>

KVM's pmu.c contains the __hyp_text needed to switch the pmu registers
between host and guest. Because this isn't covered by the 'hyp' Makefile,
it can be built with kasan and friends when these are enabled in Kconfig.

When starting a guest, this results in:
| Kernel panic - not syncing: HYP panic:
| PS:a00003c9 PC:000083000028ada0 ESR:86000007
| FAR:000083000028ada0 HPFAR:0000000029df5300 PAR:0000000000000000
| VCPU:000000004e10b7d6
| CPU: 0 PID: 3088 Comm: qemu-system-aar Not tainted 5.2.0-rc1 #11026
| Hardware name: ARM LTD ARM Juno Development Platform/ARM Juno Development Plat
| Call trace:
|  dump_backtrace+0x0/0x200
|  show_stack+0x20/0x30
|  dump_stack+0xec/0x158
|  panic+0x1ec/0x420
|  panic+0x0/0x420
| SMP: stopping secondary CPUs
| Kernel Offset: disabled
| CPU features: 0x002,25006082
| Memory Limit: none
| ---[ end Kernel panic - not syncing: HYP panic:

This is caused by functions in pmu.c calling the instrumented
code, which isn't mapped to hyp. From objdump -r:
| RELOCATION RECORDS FOR [.hyp.text]:
| OFFSET           TYPE              VALUE
| 0000000000000010 R_AARCH64_CALL26  __sanitizer_cov_trace_pc
| 0000000000000018 R_AARCH64_CALL26  __asan_load4_noabort
| 0000000000000024 R_AARCH64_CALL26  __asan_load4_noabort

Move the affected code to a new file under 'hyp's Makefile.

Fixes: 3d91befbb3a0 ("arm64: KVM: Enable !VHE support for :G/:H perf event modifiers")
Cc: Andrew Murray <Andrew.Murray@arm.com>
Signed-off-by: James Morse <james.morse@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/include/asm/kvm_host.h |  3 ---
 arch/arm64/kvm/hyp/switch.c       | 39 +++++++++++++++++++++++++++++++
 arch/arm64/kvm/pmu.c              | 38 ------------------------------
 3 files changed, 39 insertions(+), 41 deletions(-)

```
#### [PATCH] kvm: fix compilation on s390
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
s390 does not have memremap, even though in this particular case it
would be useful.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: XIVE: introduce a KVM device lock
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The XICS-on-XIVE KVM device needs to allocate XIVE event queues when a
priority is used by the OS. This is referred as EQ provisioning and it
is done under the hood when :

  1. a CPU is hot-plugged in the VM
  2. the "set-xive" is called at VM startup
  3. sources are restored at VM restore

The kvm->lock mutex is used to protect the different XIVE structures
being modified but in some contextes, kvm->lock is taken under the
vcpu->mutex which is a forbidden sequence by KVM.

Introduce a new mutex 'lock' for the KVM devices for them to
synchronize accesses to the XIVE device structures.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/kvm/book3s_xive.h        |  1 +
 arch/powerpc/kvm/book3s_xive.c        | 23 +++++++++++++----------
 arch/powerpc/kvm/book3s_xive_native.c | 15 ++++++++-------
 3 files changed, 22 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: s390: fix memory slot handling for KVM_SET_USER_MEMORY_REGION
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
kselftests exposed a problem in the s390 handling for memory slots.
Right now we only do proper memory slot handling for creation of new
memory slots. Neither MOVE, nor DELETION are handled properly. Let us
implement those.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 35 +++++++++++++++++++++--------------
 1 file changed, 21 insertions(+), 14 deletions(-)

```
#### [PATCH] KVM: selftests: enable pgste option for the linker on s390
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
To avoid testcase failures we need to enable the pgstes. This can be
done with /proc/sys/vm/allocate_pgste or with a linker option that
creates an  S390_PGSTE program header.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 tools/testing/selftests/kvm/Makefile | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
This patch adds support for UMONITOR, UMWAIT and TPAUSE instructions
in kvm, and by default dont't expose it to kvm and provide a capability
to enable it.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 Documentation/virtual/kvm/api.txt | 12 ++++++++++++
 arch/x86/include/asm/kvm_host.h   |  1 +
 arch/x86/include/asm/vmx.h        |  1 +
 arch/x86/kvm/cpuid.c              |  2 +-
 arch/x86/kvm/vmx/vmx.c            |  4 ++++
 arch/x86/kvm/x86.c                |  7 +++++++
 arch/x86/kvm/x86.h                |  5 +++++
 include/uapi/linux/kvm.h          |  1 +
 8 files changed, 32 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: fix return value for reserved EFER
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Commit 11988499e62b ("KVM: x86: Skip EFER vs. guest CPUID checks for
host-initiated writes", 2019-04-02) introduced a "return false" in a
function returning int, and anyway set_efer has a "nonzero on error"
conventon so it should be returning 1.

Reported-by: Pavel Machek <pavel@denx.de>
Fixes: 11988499e62b ("KVM: x86: Skip EFER vs. guest CPUID checks for host-initiated writes")
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### mm/compaction: BUG: NULL pointer dereference
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
Hi,

We are hitting NULL pointer dereferences while running stress tests with KVM.
See splat [0]. The test is to spawn 100 VMs all doing standard debian
installation (Thanks to Marc's automated scripts, available here [1] ).
The problem has been reproduced with a better rate of success from 5.1-rc6
onwards.

The issue is only reproducible with swapping enabled and the entire
memory is used up, when swapping heavily. Also this issue is only reproducible
on only one server with 128GB, which has the following memory layout:

[32GB@4GB, hole , 96GB@544GB]

Here is my non-expert analysis of the issue so far.

Under extreme memory pressure, the kswapd could trigger reset_isolation_suitable()
to figure out the cached values for migrate/free pfn for a zone, by scanning through
the entire zone. On our server it does so in the range of [ 0x10_0000, 0xa00_0000 ],
with the following area of holes : [ 0x20_0000, 0x880_0000 ].
In the failing case, we end up setting the cached migrate pfn as : 0x508_0000, which
is right in the center of the zone pfn range. i.e ( 0x10_0000 + 0xa00_0000 ) / 2,
with reset_migrate = 0x88_4e00, reset_free = 0x10_0000.

Now these cached values are used by the fast_isolate_freepages() to find a pfn. However,
since we cant find anything during the search we fall back to using the page belonging
to the min_pfn (which is the migrate_pfn), without proper checks to see if that is valid
PFN or not. This is then passed on to fast_isolate_around() which tries to do :
set_pageblock_skip(page) on the page which blows up due to an NULL mem_section pointer.

The following patch seems to fix the issue for me, but I am not quite convinced that
it is the right fix. Thoughts ?




Suzuki


[ 0 ] Kernel splat
 Unable to handle kernel NULL pointer dereference at virtual address 0000000000000008 [47/1825]
 Mem abort info:
   ESR = 0x96000004
   Exception class = DABT (current EL), IL = 32 bits
   SET = 0, FnV = 0
   EA = 0, S1PTW = 0
 Data abort info:
   ISV = 0, ISS = 0x00000004
   CM = 0, WnR = 0
 user pgtable: 4k pages, 48-bit VAs, pgdp = 0000000082f94ae9
 [0000000000000008] pgd=0000000000000000
 Internal error: Oops: 96000004 [#1] SMP
 ...
 CPU: 10 PID: 6080 Comm: qemu-system-aar Not tainted 510-rc1+ #6
 Hardware name: AmpereComputing(R) OSPREY EV-883832-X3-0001/OSPREY, BIOS 4819 09/25/2018
 pstate: 60000005 (nZCv daif -PAN -UAO)
 pc : set_pfnblock_flags_mask+0x58/0xe8
 lr : compaction_alloc+0x300/0x950
 sp : ffff00001fc03010
 x29: ffff00001fc03010 x28: 0000000000000000 
 x27: 0000000000000000 x26: ffff000010bf7000 
 x25: 0000000006445000 x24: 0000000006444e00 
 x23: ffff7e018f138000 x22: 0000000000000003 
 x21: 0000000000000001 x20: 0000000006444e00 
 x19: 0000000000000001 x18: 0000000000000000 
 x17: 0000000000000000 x16: ffff809f7fe97268 
 x15: 0000000191138000 x14: 0000000000000000 
 x13: 0000000000000070 x12: 0000000000000000 
 x11: ffff00001fc03108 x10: 0000000000000000 
 x9 : 0000000009222400 x8 : 0000000000000187 
 x7 : 00000000063c4e00 x6 : 0000000006444e00 
 x5 : 0000000000080000 x4 : 0000000000000001 
 x3 : 0000000000000003 x2 : ffff809f7fe92840 
 x1 : 0000000000000220 x0 : 0000000000000000 
 Process qemu-system-aar (pid: 6080, stack limit = 0x0000000095070da5)
 Call trace:
  set_pfnblock_flags_mask+0x58/0xe8
  compaction_alloc+0x300/0x950
  migrate_pages+0x1a4/0xbb0
  compact_zone+0x750/0xde8
  compact_zone_order+0xd8/0x118
  try_to_compact_pages+0xb4/0x290
  __alloc_pages_direct_compact+0x84/0x1e0
  __alloc_pages_nodemask+0x5e0/0xe18
  alloc_pages_vma+0x1cc/0x210
  do_huge_pmd_anonymous_page+0x108/0x7c8
  __handle_mm_fault+0xdd4/0x1190
  handle_mm_fault+0x114/0x1c0
  __get_user_pages+0x198/0x3c0
  get_user_pages_unlocked+0xb4/0x1d8
  __gfn_to_pfn_memslot+0x12c/0x3b8
  gfn_to_pfn_prot+0x4c/0x60
  kvm_handle_guest_abort+0x4b0/0xcd8
  handle_exit+0x140/0x1b8
  kvm_arch_vcpu_ioctl_run+0x260/0x768
  kvm_vcpu_ioctl+0x490/0x898
  do_vfs_ioctl+0xc4/0x898
  ksys_ioctl+0x8c/0xa0
  __arm64_sys_ioctl+0x28/0x38
  el0_svc_common+0x74/0x118
  el0_svc_handler+0x38/0x78
  el0_svc+0x8/0xc
 Code: f8607840 f100001f 8b011401 9a801020 (f9400400) 
 ---[ end trace af6a35219325a9b6 ]---


[1] https://git.kernel.org/pub/scm/linux/kernel/git/maz/vminstall.git/
Reviewed-by: Mel Gorman <mgorman@techsingularity.net>

```
#### [PATCH] mm, compaction: Make sure we isolate a valid PFN
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
When we have holes in a normal memory zone, we could endup having
cached_migrate_pfns which may not necessarily be valid, under heavy memory
pressure with swapping enabled ( via __reset_isolation_suitable(), triggered
by kswapd).

Later if we fail to find a page via fast_isolate_freepages(), we may
end up using the migrate_pfn we started the search with, as valid
page. This could lead to accessing NULL pointer derefernces like below,
due to an invalid mem_section pointer.

Unable to handle kernel NULL pointer dereference at virtual address 0000000000000008 [47/1825]
 Mem abort info:
   ESR = 0x96000004
   Exception class = DABT (current EL), IL = 32 bits
   SET = 0, FnV = 0
   EA = 0, S1PTW = 0
 Data abort info:
   ISV = 0, ISS = 0x00000004
   CM = 0, WnR = 0
 user pgtable: 4k pages, 48-bit VAs, pgdp = 0000000082f94ae9
 [0000000000000008] pgd=0000000000000000
 Internal error: Oops: 96000004 [#1] SMP
 ...
 CPU: 10 PID: 6080 Comm: qemu-system-aar Not tainted 510-rc1+ #6
 Hardware name: AmpereComputing(R) OSPREY EV-883832-X3-0001/OSPREY, BIOS 4819 09/25/2018
 pstate: 60000005 (nZCv daif -PAN -UAO)
 pc : set_pfnblock_flags_mask+0x58/0xe8
 lr : compaction_alloc+0x300/0x950
 [...]
 Process qemu-system-aar (pid: 6080, stack limit = 0x0000000095070da5)
 Call trace:
  set_pfnblock_flags_mask+0x58/0xe8
  compaction_alloc+0x300/0x950
  migrate_pages+0x1a4/0xbb0
  compact_zone+0x750/0xde8
  compact_zone_order+0xd8/0x118
  try_to_compact_pages+0xb4/0x290
  __alloc_pages_direct_compact+0x84/0x1e0
  __alloc_pages_nodemask+0x5e0/0xe18
  alloc_pages_vma+0x1cc/0x210
  do_huge_pmd_anonymous_page+0x108/0x7c8
  __handle_mm_fault+0xdd4/0x1190
  handle_mm_fault+0x114/0x1c0
  __get_user_pages+0x198/0x3c0
  get_user_pages_unlocked+0xb4/0x1d8
  __gfn_to_pfn_memslot+0x12c/0x3b8
  gfn_to_pfn_prot+0x4c/0x60
  kvm_handle_guest_abort+0x4b0/0xcd8
  handle_exit+0x140/0x1b8
  kvm_arch_vcpu_ioctl_run+0x260/0x768
  kvm_vcpu_ioctl+0x490/0x898
  do_vfs_ioctl+0xc4/0x898
  ksys_ioctl+0x8c/0xa0
  __arm64_sys_ioctl+0x28/0x38
  el0_svc_common+0x74/0x118
  el0_svc_handler+0x38/0x78
  el0_svc+0x8/0xc
 Code: f8607840 f100001f 8b011401 9a801020 (f9400400)
 ---[ end trace af6a35219325a9b6 ]---

The issue was reported on an arm64 server with 128GB with holes in the zone
(e.g, [32GB@4GB, 96GB@544GB]), with a swap device enabled, while running 100 KVM
guest instances.

This patch fixes the issue by ensuring that the page belongs to a valid PFN
when we fallback to using the lower limit of the scan range upon failure in
fast_isolate_freepages().

Fixes: 5a811889de10f1eb ("mm, compaction: use free lists to quickly locate a migration target")
Reported-by: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Reviewed-by: Mel Gorman <mgorman@techsingularity.net>
---
 mm/compaction.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 07/20] hw/i386/pc: Extract e820 memory layout code
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Suggested-by: Samuel Ortiz <sameo@linux.intel.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/i386/Makefile.objs        |  2 +-
 hw/i386/e820_memory_layout.c | 62 +++++++++++++++++++++++++++++
 hw/i386/e820_memory_layout.h | 76 ++++++++++++++++++++++++++++++++++++
 hw/i386/pc.c                 | 64 +-----------------------------
 include/hw/i386/pc.h         | 48 -----------------------
 target/i386/kvm.c            |  1 +
 6 files changed, 141 insertions(+), 112 deletions(-)
 create mode 100644 hw/i386/e820_memory_layout.c
 create mode 100644 hw/i386/e820_memory_layout.h

```
#### [PATCH v2] mm: add account_locked_vm utility function
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
locked_vm accounting is done roughly the same way in five places, so
unify them in a helper.  Standardize the debug prints, which vary
slightly, but include the helper's caller to disambiguate between
callsites.

Error codes stay the same, so user-visible behavior does too.  The one
exception is that the -EPERM case in tce_account_locked_vm is removed
because Alexey has never seen it triggered.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
Tested-by: Alexey Kardashevskiy <aik@ozlabs.ru>
Cc: Alan Tull <atull@kernel.org>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Christoph Lameter <cl@linux.com>
Cc: Christophe Leroy <christophe.leroy@c-s.fr>
Cc: Davidlohr Bueso <dave@stgolabs.net>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Moritz Fischer <mdf@kernel.org>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Steve Sistare <steven.sistare@oracle.com>
Cc: Wu Hao <hao.wu@intel.com>
Cc: linux-mm@kvack.org
Cc: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Cc: linuxppc-dev@lists.ozlabs.org
Cc: linux-fpga@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
---

Against v5.2-rc1.

v2:
 - applied review comments from Alexey
 - added _RET_IP_ to debug print to disambiguate callers

 arch/powerpc/kvm/book3s_64_vio.c     | 44 +++--------------------
 arch/powerpc/mm/book3s64/iommu_api.c | 41 +++------------------
 drivers/fpga/dfl-afu-dma-region.c    | 53 +++------------------------
 drivers/vfio/vfio_iommu_spapr_tce.c  | 54 +++-------------------------
 drivers/vfio/vfio_iommu_type1.c      | 17 ++-------
 include/linux/mm.h                   | 19 ++++++++++
 mm/util.c                            | 46 ++++++++++++++++++++++++
 7 files changed, 84 insertions(+), 190 deletions(-)


base-commit: a188339ca5a396acc588e5851ed7e19f66b0ebd9

```
#### [PATCHv4 1/3] vfio/mdev: Improve the create/remove sequence
##### From: Parav Pandit <parav@mellanox.com>

```c
This patch addresses below two issues and prepares the code to address
3rd issue listed below.

1. mdev device is placed on the mdev bus before it is created in the
vendor driver. Once a device is placed on the mdev bus without creating
its supporting underlying vendor device, mdev driver's probe() gets triggered.
However there isn't a stable mdev available to work on.

   create_store()
     mdev_create_device()
       device_register()
          ...
         vfio_mdev_probe()
        [...]
        parent->ops->create()
          vfio_ap_mdev_create()
            mdev_set_drvdata(mdev, matrix_mdev);
            /* Valid pointer set above */

Due to this way of initialization, mdev driver who wants to use the mdev,
doesn't have a valid mdev to work on.

2. Current creation sequence is,
   parent->ops_create()
   groups_register()

Remove sequence is,
   parent->ops->remove()
   groups_unregister()

However, remove sequence should be exact mirror of creation sequence.
Once this is achieved, all users of the mdev will be terminated first
before removing underlying vendor device.
(Follow standard linux driver model).
At that point vendor's remove() ops shouldn't fail because taking the
device off the bus should terminate any usage.

3. When remove operation fails, mdev sysfs removal attempts to add the
file back on already removed device. Following call trace [1] is observed.

[1] call trace:
kernel: WARNING: CPU: 2 PID: 9348 at fs/sysfs/file.c:327 sysfs_create_file_ns+0x7f/0x90
kernel: CPU: 2 PID: 9348 Comm: bash Kdump: loaded Not tainted 5.1.0-rc6-vdevbus+ #6
kernel: Hardware name: Supermicro SYS-6028U-TR4+/X10DRU-i+, BIOS 2.0b 08/09/2016
kernel: RIP: 0010:sysfs_create_file_ns+0x7f/0x90
kernel: Call Trace:
kernel: remove_store+0xdc/0x100 [mdev]
kernel: kernfs_fop_write+0x113/0x1a0
kernel: vfs_write+0xad/0x1b0
kernel: ksys_write+0x5a/0xe0
kernel: do_syscall_64+0x5a/0x210
kernel: entry_SYSCALL_64_after_hwframe+0x49/0xbe

Therefore, mdev core is improved in following ways.

1. Split the device registration/deregistration sequence so that some
things can be done between initialization of the device and
hooking it up to the bus respectively after deregistering it
from the bus but before giving up our final reference.
In particular, this means invoking the ->create and ->remove
callbacks in those new windows. This gives the vendor driver an
initialized mdev device to work with during creation.
At the same time, a bus driver who wish to bind to mdev driver also
gets initialized mdev device.

This follows standard Linux kernel bus and device model.

2. During remove flow, first remove the device from the bus. This
ensures that any bus specific devices are removed.
Once device is taken off the mdev bus, invoke remove() of mdev
from the vendor driver.

3. The driver core device model provides way to register and auto
unregister the device sysfs attribute groups at dev->groups.
Make use of dev->groups to let core create the groups and eliminate
code to avoid explicit groups creation and removal.

To ensure, that new sequence is solid, a below stack dump of a
process is taken who attempts to remove the device while device is in
use by vfio driver and user application.
This stack dump validates that vfio driver guards against such device
removal when device is in use.

 cat /proc/21962/stack
[<0>] vfio_del_group_dev+0x216/0x3c0 [vfio]
[<0>] mdev_remove+0x21/0x40 [mdev]
[<0>] device_release_driver_internal+0xe8/0x1b0
[<0>] bus_remove_device+0xf9/0x170
[<0>] device_del+0x168/0x350
[<0>] mdev_device_remove_common+0x1d/0x50 [mdev]
[<0>] mdev_device_remove+0x8c/0xd0 [mdev]
[<0>] remove_store+0x71/0x90 [mdev]
[<0>] kernfs_fop_write+0x113/0x1a0
[<0>] vfs_write+0xad/0x1b0
[<0>] ksys_write+0x5a/0xe0
[<0>] do_syscall_64+0x5a/0x210
[<0>] entry_SYSCALL_64_after_hwframe+0x49/0xbe
[<0>] 0xffffffffffffffff

This prepares the code to eliminate calling device_create_file() in
subsequent patch.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c    | 94 +++++++++-----------------------
 drivers/vfio/mdev/mdev_private.h |  2 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  2 +-
 3 files changed, 27 insertions(+), 71 deletions(-)

```
#### [PATCH net-next 1/6] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain
accessors. About 2% improvement of PPS were seen during vitio-user
txonly test.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
#### [PATCH v2 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
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
 linux-headers/linux/kvm.h |  1 +
 target/i386/cpu.c         |  3 ++-
 target/i386/cpu.h         |  1 +
 target/i386/kvm.c         | 13 +++++++++++++
 4 files changed, 17 insertions(+), 1 deletion(-)

```
