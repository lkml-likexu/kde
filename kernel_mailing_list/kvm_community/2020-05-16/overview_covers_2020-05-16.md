

#### [PATCH 0/6] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Sat May 16 10:11:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11553425
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95E34697
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:11:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 84D302076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 10:11:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726275AbgEPKLN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 06:11:13 -0400
Received: from mga12.intel.com ([192.55.52.136]:36845 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725792AbgEPKLM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 06:11:12 -0400
IronPort-SDR: 
 0SRmrP/0Mpcx1779BeoB8gcYhmnBJfKz49nlAPjHO4RRvZS2l64UU/1k9U3PXl3pyq2ksZ+383
 LikHoqsDmtQA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 May 2020 03:11:11 -0700
IronPort-SDR: 
 03dWaqsXdpDzWN7Oa9pHZFvzEXoel2BZjYmTkqM5J2N8WtgYMyReHi5yTPeYZmgzllhSVKj+Tp
 UUy0h0BGJzRA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,398,1583222400";
   d="scan'208";a="281484323"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.249.40.45])
  by orsmga002.jf.intel.com with ESMTP; 16 May 2020 03:11:10 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>
Subject: [PATCH 0/6] Add a vhost RPMsg API
Date: Sat, 16 May 2020 12:11:03 +0200
Message-Id: <20200516101109.2624-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linux supports RPMsg over VirtIO for "remote processor" /AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits
A further patch for the ADSP vhost RPMsg driver will be sent
separately for review only since it cannot be merged without audio
patches being upstreamed first.

Thanks
Guennadi

Guennadi Liakhovetski (6):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  vhost: (cosmetic) remove a superfluous variable initialisation
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an rpmsg API
  rpmsg: add a device ID to also bind to the ADSP device

 Documentation/rpmsg.txt          |   2 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  79 +--------
 drivers/vhost/Kconfig            |   8 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 372 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c            |   2 +-
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++++
 include/linux/virtio_rpmsg.h     |  81 +++++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 10 files changed, 549 insertions(+), 79 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/virtio_rpmsg.h
```
#### [PATCH v12 00/11] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Sat May 16 12:54:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11553495
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E50B459D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:53:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0CDF206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 12:53:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726360AbgEPMxs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 08:53:48 -0400
Received: from mga07.intel.com ([134.134.136.100]:47556 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726237AbgEPMxr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 May 2020 08:53:47 -0400
IronPort-SDR: 
 fbGNjuqPOCNK8gyThPPJKkJJVV4eh7p4APUP/NpYBSSkLsR04Cw9cJWFlzV/Pd8zvfmIB7xqni
 SObLca9w1oJw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 May 2020 05:53:47 -0700
IronPort-SDR: 
 sbqftmmVcFc4D2SXw3rJvdnHw3nAKdoS2uFgfy0l/AKikOds0lLzau6antuX5/fcUMvMW1c/3V
 VuqJXpkChfsA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,398,1583222400";
   d="scan'208";a="288076556"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga004.fm.intel.com with ESMTP; 16 May 2020 05:53:44 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, ssicleru@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v12 00/11] Enable Sub-Page Write Protection Support
Date: Sat, 16 May 2020 20:54:56 +0800
Message-Id: <20200516125507.5277-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EPT-Based Sub-Page write Protection(SPP) allows Virtual Machine Monitor(VMM)
specify write-permission for guest physical memory at a sub-page(128 byte)
granularity. When SPP works, HW enforces write-access check for sub-pages
within a protected 4KB page.

The feature targets to provide fine-grained memory protection for usages such
as memory guard and VM introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is set in Secondary
VM-Execution Controls. The feature is backed with a Sub-Page Permission Table(SPPT).
The subpage permission vector is stored in the leaf entry of SPPT. The root page
is referenced via a Sub-Page Permission Table Pointer (SPPTP) in VMCS.

To enable SPP for guest memory, the guest page should be first mapped in a 4KB EPT
entry, then set SPP bit 61 of the corresponding entry. While HW walks EPT, it traverses
SPPT with the gpa to look up the sub-page permission vector within SPPT leaf entry.
If the corresponding bit is set, write to sub-page is permitted, otherwise, SPP induced
EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Patch 1: Documentation for SPP and related API.
Patch 2: Put MMU/SSP shared definitions to a new mmu_internal.h file.
Patch 3: SPPT setup functions
Patch 4: Functions to {get|set}_subpage permission
Patch 5: Introduce user-space SPP IOCTLs
Patch 6: Handle SPP induced vmexit and EPT violation
Patch 7: Enable Lazy mode SPP protection
Patch 8: Re-enable SPP if EPT mapping changes
Patch 9: Enable SPP in instruction emulation
Patch 10: Initialize SPP related data structures.
Patch 11: selftest for SPP.


Change logs:
v12:
  1. Put MMU/SPP shared definitions/prototypes into a new mmu_internal.h per
     maintainers' comments.
  2. Changed fast_page_fault()'s return type from bool to RET_PF_* per Paolo's
     suggestion.
  3. Re-allocate SPPT root page if the root is allocated in an early spp_init()
     but is freed accompanied with EPT root page release.
     The issue is reported by Stefan Sicleru <ssicleru@bitdefender.com>.
  4. Other refactor per above changes.
  5. Rebased patches to 5.7-rc5.
  6. Fixed a virtual address mapping issue of selftest.

v11:
  1. Refactored patches Per Sean's review feedback.
  2. Added HW/KVM capabilities check before initializes SPP.
  3. Combined a few functions having similar usages.
  4. Removed unecessary functions in kvm_x86_ops.
  5. Other code fix according to testing.

v10:
  1. Cleared SPP active flag on VM resetting.
  2. Added trancepoints on subpage setup and SPP induced vmexits.
  3. Fixed a few code issues reported by Intel test robot.

v9:
  1. Added SPP protection check in pte prefetch case.
  2. Flushed EPT rmap to remove existing mappings of the target gfns.
  3. Modified documentation to reflect recent changes.
  4. Other minor code refactor.

v8:
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

v7:
  1. Configured all available protected pages once SPP induced vmexit
     happens since there's no PRESENT bit in SPPT leaf entry.
  2. Changed SPP protection check flow in tdp_page_fault().
  3. Code refactor and minior fixes.

v6:
  1. Added SPP protection patch for emulation cases per Jim's review.
  2. Modified documentation and added API description per Jim's review.
  3. Other minior changes suggested by Jim.

v5:
  1. Enable SPP support for Hugepage(1GB/2MB) to extend application.
  2. Make SPP miss vm-exit handler as the unified place to set up SPPT.
  3. If SPP protected pages are access-tracked or dirty-page-tracked,
     store SPP flag in reserved address bit, restore it in
     fast_page_fault() handler.
  4. Move SPP specific functions to vmx/spp.c and vmx/spp.h
  5. Rebased code to kernel v5.3
  6. Other change suggested by KVM community.
  
v4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

v3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

v1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 

Yang Weijiang (11):
  Documentation: Add EPT based Subpage Protection and related APIs
  mmu: spp: Add a new header file to put definitions shared by MMU and
    SPP
  mmu: spp: Implement SPPT setup functions
  mmu: spp: Implement functions to {get|set}_subpage permission
  x86: spp: Introduce user-space SPP IOCTLs
  vmx: spp: Handle SPP induced vmexit and EPT violation
  mmu: spp: Enable Lazy mode SPP protection
  mmu: spp: Re-enable SPP protection when EPT mapping changes
  x86: spp: Add SPP protection check in instruction emulation
  vmx: spp: Initialize SPP bitmap and SPP protection
  kvm: selftests: selftest for Sub-Page protection

 Documentation/virt/kvm/api.rst                |  38 ++
 Documentation/virtual/kvm/spp_kvm.txt         | 179 +++++
 arch/x86/include/asm/kvm_host.h               |  11 +-
 arch/x86/include/asm/vmx.h                    |  10 +
 arch/x86/include/asm/vmxfeatures.h            |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   2 +
 arch/x86/kvm/Makefile                         |   2 +-
 arch/x86/kvm/mmu.h                            |   9 +-
 arch/x86/kvm/mmu/mmu.c                        | 287 ++++----
 arch/x86/kvm/mmu/spp.c                        | 621 ++++++++++++++++++
 arch/x86/kvm/mmu/spp.h                        |  39 ++
 arch/x86/kvm/mmu_internal.h                   | 147 +++++
 arch/x86/kvm/mmutrace.h                       |  10 +-
 arch/x86/kvm/trace.h                          |  66 ++
 arch/x86/kvm/vmx/capabilities.h               |   5 +
 arch/x86/kvm/vmx/vmx.c                        | 110 ++++
 arch/x86/kvm/x86.c                            | 135 ++++
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/x86_64/spp_test.c | 235 +++++++
 21 files changed, 1793 insertions(+), 133 deletions(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
 create mode 100644 arch/x86/kvm/mmu/spp.c
 create mode 100644 arch/x86/kvm/mmu/spp.h
 create mode 100644 arch/x86/kvm/mmu_internal.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/spp_test.c
```
#### [PATCH 0/4] KVM: nSVM: more svm_check_nested_events work
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Sat May 16 13:53:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11553545
Return-Path: <SRS0=97JA=66=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 242E659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 043DD207D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 16 May 2020 13:53:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FPbXjX7U"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726632AbgEPNxT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 16 May 2020 09:53:19 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:23485 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726266AbgEPNxS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 16 May 2020 09:53:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589637197;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=ep9D2qqK6+qK8aTeKNlThkLGrmRLOSgUAyG+oSRZmkg=;
        b=FPbXjX7UN5gLrFERnkJyp5O4j0d5qXeb9bGDx8FXhYTcLdiU4cNhYyToQ0ZEJGFByAyWXN
        zUPlyAr3zSroj6eTvqAE86wnKVr4HDwI5Jf6Qam7iXlWzhS3+49qnHY3NKGqtY9/kxOZJp
        ty6x/UoCySZ1C4eouDpaMuKB7NuQfsk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-479-7Y79A0jqPZWvj67vgBJgtQ-1; Sat, 16 May 2020 09:53:16 -0400
X-MC-Unique: 7Y79A0jqPZWvj67vgBJgtQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 390F91005510;
        Sat, 16 May 2020 13:53:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3036F5D9D3;
        Sat, 16 May 2020 13:53:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH 0/4] KVM: nSVM: more svm_check_nested_events work
Date: Sat, 16 May 2020 09:53:07 -0400
Message-Id: <20200516135311.704878-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This moves exception injection to svm_check_nested_events, which is very
pleasing: it cleans up the recently introduced #DB handling, removes
exit_required, and fixes #UD trapping in the guest (for example
from an RSM instruction, as tested in kvm-unit-tests).

As a bonus, the last patch adds INIT vmexit injection to
svm_check_nested_events as well.  Note that there is no test case for
that yet.

The patches have small conflicts with those I posted yesterday, so
they are on top of them.

Paolo

Paolo Bonzini (4):
  KVM: nSVM: fix condition for filtering async PF
  KVM: nSVM: inject exceptions via svm_check_nested_events
  KVM: nSVM: remove exit_required
  KVM: nSVM: correctly inject INIT vmexits

 arch/x86/kvm/svm/nested.c | 159 ++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.c    |  23 ------
 arch/x86/kvm/svm/svm.h    |   4 +-
 3 files changed, 75 insertions(+), 111 deletions(-)
```
