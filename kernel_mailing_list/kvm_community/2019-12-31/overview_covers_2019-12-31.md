

#### [PATCH v10 00/10] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Tue Dec 31 06:50:33 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11313783
Return-Path: <SRS0=Z6yu=2V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0205C1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 06:47:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DBB5C206E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 06:47:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725875AbfLaGqn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Dec 2019 01:46:43 -0500
Received: from mga04.intel.com ([192.55.52.120]:16543 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725497AbfLaGqn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Dec 2019 01:46:43 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Dec 2019 22:46:42 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,378,1571727600";
   d="scan'208";a="224368469"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 30 Dec 2019 22:46:41 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v10 00/10] Enable Sub-Page Write Protection Support
Date: Tue, 31 Dec 2019 14:50:33 +0800
Message-Id: <20191231065043.2209-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EPT-Based Sub-Page write Protection(SPP) allows Virtual Machine Monitor(VMM)
specify write-permission for guest physical memory at a sub-page(128 byte)
granularity. When SPP works, HW enforces write-access check for sub-pages
within a protected 4KB page.

The feature targets to provide fine-grained memory protection for
usages such as memory guard and VM introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), and subpage permission vector is stored in the
leaf entry of SPPT. The root page is referenced via a Sub-Page Permission
Table Pointer (SPPTP) in VMCS.

To enable SPP for guest memory, the guest page should be first mapped
to a 4KB EPT entry, then set SPP bit 61 of the corresponding entry. 
While HW walks EPT, it traverses SPPT with the gpa to look up the sub-page
permission vector within SPPT leaf entry. If the corresponding bit is set,
write to sub-page is permitted, otherwise, SPP induced EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Patch 1: Documentation for SPP and related API.
Patch 2: Add control flags for Sub-Page Protection(SPP).
Patch 3: Add SPP Table setup functions.
Patch 4: Add functions to create/destroy SPP bitmap block.
Patch 5: Introduce user-space SPP IOCTLs.
Patch 6: Set up SPP paging table at vmentry/vmexit.
Patch 7: Enable Lazy mode SPP protection.
Patch 8: Handle SPP protected pages when VM memory changes.
Patch 9: Add SPP protection check in emulation case.
Patch 10: SPP selftest.

Change logs:

v9 ->v10
  1. Cleared SPP active flag on VM resetting.
  2. Added trancepoints on subpage setup and SPP induced vmexits.
  3. Other minor code fix.

v8 ->v9:
  1. Added SPP protection check in pte prefetch case.
  2. Flushed EPT rmap to remove existing mappings of the target gfns.
  3. Modified documentation to reflect recent changes.
  4. Other minor code refactor.

v7 -> v8:
  1. Changed ioctl interface definition per Paolo's comments.
  2. Replaced SPP_INIT ioctl funciton with KVM_ENABLE_CAP.
  3. Removed SPP bit from X86 feature word.
  4. Returned instruction length to user-space when SPP induced EPT
     violation happens, this is to provide flexibility to use SPP,
     revert write or track write.
  5. Modified selftest application and added into this serial.
  6. Simplified SPP permission vector check.
  7. Moved spp.c and spp.h to kvm/mmu folder.
  8. Other code fix according to Paolo's feedback and testing.

v6 -> v7:
  1. Configured all available protected pages once SPP induced vmexit
     happens since there's no PRESENT bit in SPPT leaf entry.
  2. Changed SPP protection check flow in tdp_page_fault().
  3. Code refactor and minior fixes.

v5 -> v6:
  1. Added SPP protection patch for emulation cases per Jim's review.
  2. Modified documentation and added API description per Jim's review.
  3. Other minior changes suggested by Jim.

v4 -> v5:
  1. Enable SPP support for Hugepage(1GB/2MB) to extend application.
  2. Make SPP miss vm-exit handler as the unified place to set up SPPT.
  3. If SPP protected pages are access-tracked or dirty-page-tracked,
     store SPP flag in reserved address bit, restore it in
     fast_page_fault() handler.
  4. Move SPP specific functions to vmx/spp.c and vmx/spp.h
  5. Rebased code to kernel v5.3
  6. Other change suggested by KVM community.
  
v3 -> v4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

v2 -> v3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

v2 -> v1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 

Yang Weijiang (10):
  Documentation: Add EPT based Subpage Protection and related APIs
  vmx: spp: Add control flags for Sub-Page Protection(SPP)
  mmu: spp: Add SPP Table setup functions
  mmu: spp: Add functions to operate SPP access bitmap
  x86: spp: Introduce user-space SPP IOCTLs
  vmx: spp: Set up SPP paging table at vmentry/vmexit
  mmu: spp: Enable Lazy mode SPP protection
  mmu: spp: Handle SPP protected pages when VM memory changes
  x86: spp: Add SPP protection check in emulation
  kvm: selftests: selftest for Sub-Page protection

 Documentation/virt/kvm/api.txt                |  39 ++
 Documentation/virtual/kvm/spp_kvm.txt         | 179 +++++
 arch/x86/include/asm/kvm_host.h               |  11 +-
 arch/x86/include/asm/vmx.h                    |  10 +
 arch/x86/include/uapi/asm/vmx.h               |   2 +
 arch/x86/kvm/mmu.h                            |   2 +
 arch/x86/kvm/mmu/mmu.c                        | 106 ++-
 arch/x86/kvm/mmu/spp.c                        | 660 ++++++++++++++++++
 arch/x86/kvm/mmu/spp.h                        |  35 +
 arch/x86/kvm/trace.h                          |  66 ++
 arch/x86/kvm/vmx/capabilities.h               |   5 +
 arch/x86/kvm/vmx/vmx.c                        | 104 ++-
 arch/x86/kvm/x86.c                            | 136 +++-
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/x86_64/spp_test.c | 234 +++++++
 17 files changed, 1599 insertions(+), 10 deletions(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
 create mode 100644 arch/x86/kvm/mmu/spp.c
 create mode 100644 arch/x86/kvm/mmu/spp.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/spp_test.c
```
#### [kvm-unit-tests PATCH v3 00/18] arm/arm64: Various fixes
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Tue Dec 31 16:09:31 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11314287
Return-Path: <SRS0=Z6yu=2V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AF631398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 16:10:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76350206EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Dec 2019 16:10:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727104AbfLaQKL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Dec 2019 11:10:11 -0500
Received: from foss.arm.com ([217.140.110.172]:35442 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726060AbfLaQKL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Dec 2019 11:10:11 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DA42F328;
        Tue, 31 Dec 2019 08:10:08 -0800 (PST)
Received: from e121566-lin.arm.com,emea.arm.com,asiapac.arm.com,usa.arm.com
 (unknown [10.37.8.41])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 C43A33F68F;
        Tue, 31 Dec 2019 08:10:06 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, maz@kernel.org,
        andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH v3 00/18] arm/arm64: Various fixes
Date: Tue, 31 Dec 2019 16:09:31 +0000
Message-Id: <1577808589-31892-1-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a combination of the fixes from my EL2 series [1] and other new
fixes. I've rebased the series on top of 2c6589bc4e8b ("Update AMD
instructions to conform to LLVM assembler"), which means that I had to
switch the order of parameters for the report function.

This time around I tried to do a better job at testing. I've ran
kvm-unit-tests in the following configurations:

- with kvmtool, on an arm64 host kernel: 64 and 32 bit tests, with GICv3
  (on an Ampere eMAG) and GICv2 (on a AMD Seattle box).

- with qemu, on an arm64 host kernel:
    a. with accel=kvm, 64 and 32 bit tests, with GICv3 (Ampere eMAG) and
       GICv2 (Seattle).
    b. with accel=tcg, 64 and 32 bit tests, on the Ampere eMAG machine.

I didn't run the 32 bit tests under a 32 bit host kernel because I don't
have a 32 bit arm board at hand at the moment. It's also worth noting that
when I tried running the selftest-vectors-kernel tests on an ancient
version of qemu (QEMU emulator version 2.5.0 (Debian
1:2.5+dfsg-5ubuntu10.42)) I got the following error:

 $ arm/run arm/selftest.flat -append vectors-kernel
/usr/bin/qemu-system-aarch64 -nodefaults -machine virt,accel=tcg -cpu cortex-a57 -device virtio-serial-device -device virtconsole,chardev=ctd -chardev testdev,id=ctd -device pci-testdev -display none -serial stdio -kernel arm/selftest.flat -append vectors-kernel # -initrd /tmp/tmp.zNO1kWtmuM
PASS: selftest: vectors-kernel: und
PASS: selftest: vectors-kernel: svc
qemu: fatal: Trying to execute code outside RAM or ROM at 0x0000003fffff0000

PC=0000003fffff0000  SP=00000000400aff70
X00=00000000400805a0 X01=0000000040092f20 X02=0000003fffff0000 X03=0000000040092f20
X04=0000000000000010 X05=00000000400aff40 X06=00000000400aff70 X07=00000000400aff70
X08=00000000400afde0 X09=ffffff80ffffffc8 X10=00000000400afe20 X11=00000000400afe20
X12=00000000400b0000 X13=00000000400afeac X14=00000000400b0000 X15=0000000000000000
X16=0000000000000000 X17=0000000000000000 X18=0000000000000000 X19=0000000040092000
X20=0000000000000004 X21=0000000040092e98 X22=0000000040092f20 X23=0000000000000000
X24=0000000000000000 X25=0000000000000000 X26=0000000000000000 X27=0000000000000000
X28=0000000000000000 X29=0000000000000000 X30=000000004008052c 
PSTATE=800003c5 N--- EL1h
q00=0000000000000000:0000000000000000 q01=0000000000000000:0000000000000000
q02=0000000000000000:0000000000000000 q03=0000000000000000:0000000000000000
q04=0000000000000000:0000000000000000 q05=0000000000000000:0000000000000000
q06=0000000000000000:0000000000000000 q07=0000000000000000:0000000000000000
q08=0000000000000000:0000000000000000 q09=0000000000000000:0000000000000000
q10=0000000000000000:0000000000000000 q11=0000000000000000:0000000000000000
q12=0000000000000000:0000000000000000 q13=0000000000000000:0000000000000000
q14=0000000000000000:0000000000000000 q15=0000000000000000:0000000000000000
q16=0000000000000000:0000000000000000 q17=0000000000000000:0000000000000000
q18=0000000000000000:0000000000000000 q19=0000000000000000:0000000000000000
q20=0000000000000000:0000000000000000 q21=0000000000000000:0000000000000000
q22=0000000000000000:0000000000000000 q23=0000000000000000:0000000000000000
q24=0000000000000000:0000000000000000 q25=0000000000000000:0000000000000000
q26=0000000000000000:0000000000000000 q27=0000000000000000:0000000000000000
q28=0000000000000000:0000000000000000 q29=0000000000000000:0000000000000000
q30=0000000000000000:0000000000000000 q31=0000000000000000:0000000000000000
FPCR: 00000000  FPSR: 00000000
QEMU Aborted

I'm not sure if we support such an old version of qemu. If we do, please
let me know, and I'll try to come up with a solution. I am reluctant to
drop the prefetch abort test because it uncovered a bug in the nested
virtualization patches.

Summary of the patches:
* Patch 1 adds coherent translation table walks for ARMv7 and removes
  unneeded dcache maintenance.
* Patches 2-4 make translation table updates more robust.
* Patches 5-6 fix a pretty serious bug in our PSCI test, which was causing
  an infinite loop of prefetch aborts.
* Patches 7-10 add a proper test for prefetch aborts. The test now uses
  mmu_clear_user.
* Patches 11-13 are fixes for the timer test.
* Patches 14-15 fix turning the MMU off.
* Patches 16-18 are small fixes to make the code more robust, and perhaps
  more important, remove unnecessary operations that might hide real bugs
  in KVM.

Patches 1-4, 9, 18 are new. The rest are taken from the EL2 series, and
I've kept the Reviewed-by tag where appropriate.

Changes in v3:
* Implemented review comments.
* Minor cosmetic changes to the commit messages here and there.
* Removed the duplicate DSB ISHST that I had added to mmu.c in patch #1.
  flush_tlb_page already has the needed barriers.
* Replaced patch #2 "lib: arm64: Remove barriers before TLB operations"
  with "lib: arm: Add proper data synchronization barriers for TLBIs".
  I've decided to keep the needed barriers in the flush_tlb_* functions, to
  match what the kernel does.
* Added a missing DSB ISHST in flush_tlb_all in patch #8 "lib: arm:
  Implement flush_tlb_all"
* The address for the prefetch abort test is now in hexadecimal to prevent
  a compile error.
* Added information about the KVM bug that patch #13 "arm64: timer: Test
  behavior when timer disabled or masked" helped find.
* Explained in the commit message for #15 how to reproduce some of the
  errors that I was seeing without the patch.

Changes in v2:
* Fixed the prefetch abort test on QEMU by changing the address used to
  cause the abort.

[1] https://www.spinics.net/lists/kvm/msg196797.html

Alexandru Elisei (18):
  lib: arm/arm64: Remove unnecessary dcache maintenance operations
  lib: arm: Add proper data synchronization barriers for TLBIs
  lib: Add WRITE_ONCE and READ_ONCE implementations in compiler.h
  lib: arm/arm64: Use WRITE_ONCE to update the translation tables
  lib: arm/arm64: Remove unused CPU_OFF parameter
  arm/arm64: psci: Don't run C code without stack or vectors
  lib: arm/arm64: Add missing include for alloc_page.h in pgtable.h
  lib: arm: Implement flush_tlb_all
  lib: arm/arm64: Teach mmu_clear_user about block mappings
  arm/arm64: selftest: Add prefetch abort test
  arm64: timer: Write to ICENABLER to disable timer IRQ
  arm64: timer: EOIR the interrupt after masking the timer
  arm64: timer: Test behavior when timer disabled or masked
  lib: arm/arm64: Refuse to disable the MMU with non-identity stack
    pointer
  arm/arm64: Perform dcache clean + invalidate after turning MMU off
  arm: cstart64.S: Downgrade TLBI to non-shareable in asm_mmu_enable
  arm/arm64: Invalidate TLB before enabling MMU
  arm: cstart64.S: Remove icache invalidation from asm_mmu_enable

 lib/linux/compiler.h          |  83 +++++++++++++++++++++++++++++++
 lib/arm/asm/gic-v3.h          |   1 +
 lib/arm/asm/gic.h             |   1 +
 lib/arm/asm/mmu-api.h         |   2 +-
 lib/arm/asm/mmu.h             |  18 ++++---
 lib/arm/asm/pgtable-hwdef.h   |  11 +++++
 lib/arm/asm/pgtable.h         |  20 ++++++--
 lib/arm/asm/processor.h       |   6 +++
 lib/arm64/asm/esr.h           |   3 ++
 lib/arm64/asm/pgtable-hwdef.h |   3 ++
 lib/arm64/asm/pgtable.h       |  15 +++++-
 lib/arm64/asm/processor.h     |   6 +++
 lib/arm/mmu.c                 |  60 ++++++++++++----------
 lib/arm/processor.c           |  10 ++++
 lib/arm/psci.c                |   4 +-
 lib/arm/setup.c               |   2 +
 lib/arm64/processor.c         |  11 +++++
 arm/cstart.S                  |  40 ++++++++++++++-
 arm/cstart64.S                |  35 +++++++++++--
 arm/cache.c                   |   3 +-
 arm/psci.c                    |   5 +-
 arm/selftest.c                | 112 +++++++++++++++++++++++++++++++++++++++++-
 arm/timer.c                   |  38 +++++++++-----
 23 files changed, 425 insertions(+), 64 deletions(-)
 create mode 100644 lib/linux/compiler.h
```
