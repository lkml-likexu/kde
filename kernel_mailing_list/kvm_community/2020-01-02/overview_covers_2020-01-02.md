

#### [RESEND PATCH v10 00/10] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Thu Jan  2 05:18:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11315347
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B725138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 05:15:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3A827215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 05:15:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726026AbgABFPI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 00:15:08 -0500
Received: from mga12.intel.com ([192.55.52.136]:22040 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725788AbgABFPI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 00:15:08 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Jan 2020 21:15:07 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,385,1571727600";
   d="scan'208";a="369236511"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga004.jf.intel.com with ESMTP; 01 Jan 2020 21:15:05 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v10 00/10] Enable Sub-Page Write Protection Support
Date: Thu,  2 Jan 2020 13:18:54 +0800
Message-Id: <20200102051904.32090-1-weijiang.yang@intel.com>
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
  3. Fixed a few code issues reported by Intel test robot.

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
#### [RESEND PATCH v10 00/10] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Thu Jan  2 06:13:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11315391
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 18B921395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:10:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00E5421655
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:10:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726103AbgABGJX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 01:09:23 -0500
Received: from mga07.intel.com ([134.134.136.100]:3898 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725788AbgABGJX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 01:09:23 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Jan 2020 22:09:22 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,385,1571727600";
   d="scan'208";a="224706697"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 01 Jan 2020 22:09:20 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v10 00/10] Enable Sub-Page Write Protection Support
Date: Thu,  2 Jan 2020 14:13:09 +0800
Message-Id: <20200102061319.10077-1-weijiang.yang@intel.com>
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
  3. Fixed a few code issues reported by Intel test robot.

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
#### [kvm-unit-tests RFC PATCH v3 0/7] arm64: Run at EL2
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Jan  2 13:46:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11315783
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B9996C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 13:47:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 789DA20866
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 13:47:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728370AbgABNrE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 08:47:04 -0500
Received: from foss.arm.com ([217.140.110.172]:47272 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728342AbgABNrE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 08:47:04 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id F1C641FB;
        Thu,  2 Jan 2020 05:47:03 -0800 (PST)
Received: from e121566-lin.arm.com,emea.arm.com,asiapac.arm.com,usa.arm.com
 (unknown [10.37.9.21])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 88C243F68F;
        Thu,  2 Jan 2020 05:47:02 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, maz@kernel.org,
        andre.przywara@arm.com
Subject: [kvm-unit-tests RFC PATCH v3 0/7] arm64: Run at EL2
Date: Thu,  2 Jan 2020 13:46:39 +0000
Message-Id: <1577972806-16184-1-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARMv8.3 added support for nested virtualization, which makes it possible
for a hypervisor to run another hypervisor as a guest. Support for nested
virtualization is being worked on in KVM [1].

This patch series aims to make it possible for kvm-unit-tests to run at EL2
under KVM. The focus has been on having all the infrastructure in place to
run at EL2, and not on adding comprehensive tests for this Exception Level.
All existing tests that fulfill KVM's requirements for a nested guest (the
architecture is arm64 and they use GICv3) will be able to be run at EL2.

To keep the changes minimal, kvm-unit-tests will run with VHE enabled when
it detects that has been booted at EL2. Functions for enabling and
disabling VHE have been added, with the aim to let the user specify to
disable VHE for a given test via command-line parameters. At the moment,
only the timer test has been modified to run with VHE disabled.

The series are firmly an RFC because:
* The patches that implement KVM nested support are themselves in the RFC
  phase.
* Some tests don't complete because of bugs in the current version of the
  KVM patches. Where appropriate, I will provide fixes to allow the tests
  to finish, however those fixes are my own and have not been reviewed in
  any way. Use at your own risk.

To run the tests, one obviously needs KVM with nested virtualization
support from [2]. These patches have been tested from commit
78c66132035c ("arm64: KVM: nv: Allow userspace to request
KVM_ARM_VCPU_NESTED_VIRT"), on top of which the following patches have been
cherry-picked from upstream Linux:
* b4a1583abc83 ("KVM: arm/arm64: Fix emulated ptimer irq injection")
* 16e604a437c8 ("KVM: arm/arm64: vgic: Reevaluate level sensitive
  interrupts on enable")

Without those two patches some timer tests will fail.

A version of kvmtool that knows about nested virtualization is also
needed [3]. The kvmtool --nested parameter is required for releasing a
guest at EL2. For example, to run the newly added selftest-el2 test:

lkvm -f selftest.flat -c 2 -m 128 -p el2 --nested --irqchip gicv3

The patches have been lightly tested on FVP by running the 64 bit tests at
EL1 and EL2, under kvmtool and with GICv3.

Changes in v3:
* Removed patches 1-12 and sent them as a separate series (currently at v3
  [4]). This series have been modified to apply on top of them. Hopefully,
  this split will make reviewing easier and help get the fixes merged
  sooner rather than later.
* Minor changes here and there, mostly cosmetical.

Changes in v2:
* Gathered Reviewed-by tags.
* Implemented review comments (more details in the specific patches).
* Patch #1 was remove and I've added 4 new patches: #1 removes the obsolete
  CPU_OFF parameter; #4 implements a TODO from arm's flush_tlb_all; #10
  fixes asm_mmu_enable; #11 replaces an expensive and unnecessary TLBI with
  the correct one.

Summary of the patches:
* Patch 1 is a trivial enhancement.
* Patches 2-4 add support for running at EL2. A basic selftest-el2 test
  is added that targets EL2.
* Patches 5-7 add support for disabling VHE. The timer and selftest-el2
  tests are modified to use this feature.

[1] https://www.spinics.net/lists/arm-kernel/msg736687.html
[2] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-wip-5.2-rc5
[3] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5
[4] https://www.spinics.net/lists/kvm/msg203477.html

Alexandru Elisei (7):
  lib: Add _UL and _ULL definitions to linux/const.h
  lib: arm64: Run existing tests at EL2
  arm64: timer: Add test for EL2 timers
  arm64: selftest: Add basic test for EL2
  lib: arm64: Add support for disabling and re-enabling VHE
  arm64: selftest: Expand EL2 test to disable and re-enable VHE
  arm64: timer: Run tests with VHE disabled

 lib/linux/const.h             |   7 +-
 lib/asm-generic/page.h        |   2 +-
 lib/arm/asm/page.h            |   2 +-
 lib/arm/asm/pgtable-hwdef.h   |  22 +--
 lib/arm/asm/psci.h            |   1 +
 lib/arm/asm/thread_info.h     |   3 +-
 lib/arm64/asm/esr.h           |   2 +
 lib/arm64/asm/mmu.h           |  11 +-
 lib/arm64/asm/page.h          |   2 +-
 lib/arm64/asm/pgtable-hwdef.h |  79 +++++++----
 lib/arm64/asm/processor.h     |  28 ++++
 lib/arm64/asm/sysreg.h        |  28 ++++
 lib/x86/asm/page.h            |   2 +-
 lib/arm/psci.c                |  43 +++++-
 lib/arm/setup.c               |   4 +
 lib/arm64/processor.c         |  39 +++++-
 arm/cstart64.S                | 232 +++++++++++++++++++++++++++++++-
 arm/micro-bench.c             |  17 ++-
 arm/selftest.c                |  79 ++++++++++-
 arm/timer.c                   | 302 +++++++++++++++++++++++++++++++++++++++---
 arm/unittests.cfg             |   8 ++
 21 files changed, 830 insertions(+), 83 deletions(-)
```
