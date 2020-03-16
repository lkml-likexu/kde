

#### [PATCH v5 0/9] x86/split_lock: Add feature split lock detection
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Sun Mar 15 05:05:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11438701
Return-Path: <SRS0=vYwd=5A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2216B14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 05:23:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0AEA120722
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 05:23:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726924AbgCOFWw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 15 Mar 2020 01:22:52 -0400
Received: from mga18.intel.com ([134.134.136.126]:47872 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726648AbgCOFWw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 15 Mar 2020 01:22:52 -0400
IronPort-SDR: 
 shfi8IrWR+MfHV7aMo+c+nuQq5zwfGkLptUmJK+Xpsjy2zMy/vhEMPuNAcuHGHwu+yL5+k/W6S
 ysYgaE0Q6Vew==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Mar 2020 22:22:51 -0700
IronPort-SDR: 
 Wx4fi8F+f85aXxZT0DhhIKXnwUcDXqKKzoQQL+P7Cg82WU15mt5BzYm20FmZGuC+aEaNTaACjN
 DBLO6XyLPULA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,555,1574150400";
   d="scan'208";a="267194195"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.160])
  by fmsmga004.fm.intel.com with ESMTP; 14 Mar 2020 22:22:47 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        hpa@zytor.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org
Cc: Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v5 0/9] x86/split_lock: Add feature split lock detection
Date: Sun, 15 Mar 2020 13:05:08 +0800
Message-Id: <20200315050517.127446-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to add the virtualization of split lock detection for
guest, while containing some fixes of native kernel split lock handling. 

Note, this series is based on the kernel patch[1].

Patch 1 is the fix and enhancement for kernel split lock detction. It
ensures X86_FEATURE_SPLIT_LOCK_DETECT flag is set after verifying the
feature is really supported. And it explicitly turn off split lock when
sld_off instead of assuming BIOS/firmware leaves it cleared.

Patch 2 optimizes the runtime MSR accessing.

Patch 3-4 are the preparation for enabling split lock detection
virtualization in KVM.

Patch 5 fixes the issue tht malicious guest may exploit kvm emulator to
attcact host kernel.

Patch 6 handles guest's split lock when host truns split lock detect on.

Patch 7-9 implement the virtualization of split lock detection in kvm.

[1]: https://lore.kernel.org/lkml/158031147976.396.8941798847364718785.tip-bot2@tip-bot2/ 

v5:
 - Use X86_FEATURE_SPLIT_LOCK_DETECT flag in kvm to ensure split lock
   detection is really supported.
 - Add and export sld related helper functions in their related usecase 
   kvm patches.

v4:
 - Add patch 1 to rework the initialization flow of split lock
   detection.
 - Drop percpu MSR_TEST_CTRL cache, just use a static variable to cache
   the reserved/unused bit of MSR_TEST_CTRL. [Sean]
 - Add new option for split_lock_detect kernel param.
 - Changlog refinement. [Sean]
 - Add a new patch to enable MSR_TEST_CTRL for intel guest. [Sean]

Xiaoyao Li (9):
  x86/split_lock: Rework the initialization flow of split lock detection
  x86/split_lock: Avoid runtime reads of the TEST_CTRL MSR
  x86/split_lock: Re-define the kernel param option for
    split_lock_detect
  x86/split_lock: Export handle_user_split_lock()
  kvm: x86: Emulate split-lock access as a write
  kvm: vmx: Extend VMX's #AC interceptor to handle split lock #AC
    happens in guest
  kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
  kvm: vmx: Enable MSR_TEST_CTRL for intel guest
  x86: vmx: virtualize split lock detection

 .../admin-guide/kernel-parameters.txt         |   5 +-
 arch/x86/include/asm/cpu.h                    |  23 +++-
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/kernel/cpu/intel.c                   | 119 +++++++++++++-----
 arch/x86/kernel/traps.c                       |   2 +-
 arch/x86/kvm/cpuid.c                          |   7 +-
 arch/x86/kvm/vmx/vmx.c                        |  75 ++++++++++-
 arch/x86/kvm/vmx/vmx.h                        |   1 +
 arch/x86/kvm/x86.c                            |  42 ++++++-
 9 files changed, 229 insertions(+), 46 deletions(-)
```
#### [PATCH 0/2] Fix errors when try to build kvm selftests on
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Sun Mar 15 09:34:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11438797
Return-Path: <SRS0=vYwd=5A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C76B159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 09:52:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5612420738
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 09:52:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728204AbgCOJwR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 15 Mar 2020 05:52:17 -0400
Received: from mga17.intel.com ([192.55.52.151]:35235 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728108AbgCOJwR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 15 Mar 2020 05:52:17 -0400
IronPort-SDR: 
 HChpFelIJng41hdn2vxch5buzBS3a9o6bVvl3+U2mcGDDvesItcWJkwaWkQ4yoC8aTkzjMIBHy
 /3BMTf11vVgA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2020 02:52:16 -0700
IronPort-SDR: 
 cuxcG9ERSYwCjvd61maY4zMtxSP5zttqBeHAybX768mImW+t4oxgyWF4bz4w1dRLN2ujMXQQnc
 l5XF4a8P1Abg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,556,1574150400";
   d="scan'208";a="416800326"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.160])
  by orsmga005.jf.intel.com with ESMTP; 15 Mar 2020 02:52:15 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Shuah Khan <shuah@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 0/2] Fix errors when try to build kvm selftests on
Date: Sun, 15 Mar 2020 17:34:23 +0800
Message-Id: <20200315093425.33600-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I attempted to build KVM selftests on a specified dir, unfortunately
neither	"make O=~/mydir TARGETS=kvm" in tools/testing/selftests, nor
"make OUTPUT=~/mydir" in tools/testing/selftests/kvm work.

This series aims to make both work.

Xiaoyao Li (2):
  kvm: selftests: Fix no directory error when OUTPUT specified
  selftests: export INSTALL_HDR_PATH if using "O" to specify output dir

 tools/testing/selftests/Makefile     | 6 +++++-
 tools/testing/selftests/kvm/Makefile | 3 ++-
 2 files changed, 7 insertions(+), 2 deletions(-)
```
