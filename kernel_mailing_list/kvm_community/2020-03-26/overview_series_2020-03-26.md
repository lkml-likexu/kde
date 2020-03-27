#### [PATCH v3 kvmtool 01/32] Makefile: Use correct objcopy binary when cross-compiling for x86_64
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11460461
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1A1692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 15:24:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D2D472076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 15:24:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727856AbgCZPY4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 11:24:56 -0400
Received: from foss.arm.com ([217.140.110.172]:33672 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726034AbgCZPYz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 11:24:55 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 52BB51045;
        Thu, 26 Mar 2020 08:24:55 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 647C83F71E;
        Thu, 26 Mar 2020 08:24:54 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH v3 kvmtool 01/32] Makefile: Use correct objcopy binary when
 cross-compiling for x86_64
Date: Thu, 26 Mar 2020 15:24:07 +0000
Message-Id: <20200326152438.6218-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200326152438.6218-1-alexandru.elisei@arm.com>
References: <20200326152438.6218-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the compiler toolchain version of objcopy instead of the native one
when cross-compiling for the x86_64 architecture.

Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Tested-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [RFC v3 1/3] kvm: selftests: Fix no directory error when OUTPUT specified
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11459157
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1DE517EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:25:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D2D7C208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:25:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728076AbgCZDZd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 23:25:33 -0400
Received: from mga18.intel.com ([134.134.136.126]:53303 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727655AbgCZDZb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 23:25:31 -0400
IronPort-SDR: 
 A0ca+m0uqk9CJSzqnYPy6jmOuyV3xfxzkHJ1fPWbxxVjBOo++XfBqmPbPq0iJfsmkH63Oc/0lr
 m8r2mBIHAuZg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 20:25:30 -0700
IronPort-SDR: 
 QUWJw+k2SY1p2euzekEuWODO1srN4VcPBN5w3SVYTpBm5hdqfTmPNWSMrZB6PcwIzxiMLBhgGB
 6bFumWCvIg/w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,306,1580803200";
   d="scan'208";a="446842817"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by fmsmga005.fm.intel.com with ESMTP; 25 Mar 2020 20:25:29 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>
Cc: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [RFC v3 1/3] kvm: selftests: Fix no directory error when OUTPUT
 specified
Date: Thu, 26 Mar 2020 11:07:48 +0800
Message-Id: <20200326030750.173972-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200326030750.173972-1-xiaoyao.li@intel.com>
References: <20200326030750.173972-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When build kvm selftests to an specified directory with

	make OUTPUT=/home/lxy/kvm-selftests

it encouters following error：

  /usr/bin/ld: cannot open output file
  /home/lxy/kvm-selftests/x86_64/cr4_cpuid_sync_test: No such file or
  directory
  collect2: error: ld returned 1 exit status
  make: *** [../lib.mk:141:
  /home/lxy/kvm-selftests/x86_64/cr4_cpuid_sync_test] Error 1

Use "mkdir -p" to create the directory to fix this issue.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 tools/testing/selftests/kvm/Makefile | 1 +
 1 file changed, 1 insertion(+)

```
#### [GIT PULL] KVM fixes for Linux 5.6 final (or -rc8)
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11460959
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BBAB159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:03:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2C5A52070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:03:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FcYx2KNs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728636AbgCZUDV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 16:03:21 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:38986 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727851AbgCZUDV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Mar 2020 16:03:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585253000;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=IKJXvHsw2viIBMjcPMcNthSEpAPOCGzoH1WTxzpDB7k=;
        b=FcYx2KNs1tT3NRjtXdPH+l7+1PQKleMS8X8RMUCjQnipORIMn043LOC+PW0bKbjRj0jRWx
        GgmsLHmZM3tWhgzyFof3H0NkzDJhY3PWNXzF3jZ/AsPNhsXLC7RPqBL4WFkUp0Mk2i20V8
        NOhyIzriba7sfjzzG4gvzOcOTuHjrGQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-49-0uD2s0BPO4-KlYUbF5eL5A-1; Thu, 26 Mar 2020 16:03:13 -0400
X-MC-Unique: 0uD2s0BPO4-KlYUbF5eL5A-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C3AE61007268;
        Thu, 26 Mar 2020 20:03:12 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4F41B60BF3;
        Thu, 26 Mar 2020 20:03:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.6 final (or -rc8)
Date: Thu, 26 Mar 2020 16:03:11 -0400
Message-Id: <20200326200311.28222-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 018cabb694e3923998fdc2908af5268f1d89f48f:

  Merge branch 'kvm-null-pointer-fix' into kvm-master (2020-03-14 12:49:37 +0100)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e1be9ac8e6014a9b0a216aebae7250f9863e9fc3:

  KVM: X86: Narrow down the IPI fastpath to single target IPI (2020-03-26 05:44:21 -0400)

----------------------------------------------------------------
x86 bug fixes.

----------------------------------------------------------------
He Zhe (1):
      KVM: LAPIC: Mark hrtimer for period or oneshot mode to expire in hard interrupt context

Nick Desaulniers (1):
      KVM: VMX: don't allow memory operands for inline asm that modifies SP

Paolo Bonzini (2):
      KVM: x86: remove bogus user-triggerable WARN_ON
      KVM: SVM: document KVM_MEM_ENCRYPT_OP, let userspace detect if SEV is available

Tom Lendacky (1):
      KVM: SVM: Issue WBINVD after deactivating an SEV guest

Wanpeng Li (2):
      KVM: LAPIC: Also cancel preemption timer when disarm LAPIC timer
      KVM: X86: Narrow down the IPI fastpath to single target IPI

 Documentation/virt/kvm/amd-memory-encryption.rst | 25 ++++++++++++++++++++++++
 arch/x86/kvm/lapic.c                             |  8 +++++++-
 arch/x86/kvm/svm.c                               | 25 ++++++++++++++++--------
 arch/x86/kvm/vmx/vmx.c                           |  2 +-
 arch/x86/kvm/x86.c                               |  6 ++++--
 5 files changed, 54 insertions(+), 12 deletions(-)
```
#### [PATCH v11 1/9] KVM: VMX: Introduce CET VMX fields and flags
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11459565
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3DD7F81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1FE0F20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727725AbgCZIQC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 04:16:02 -0400
Received: from mga02.intel.com ([134.134.136.20]:27555 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726298AbgCZIQB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 04:16:01 -0400
IronPort-SDR: 
 7hAwDOgrA1G5ibx2L4iUCSktXmCxth0PjDxWwIdWdRjOCMjgJOcT7b1+LDz0YKUDZ03vKD6f2o
 NwTZ1UYNzWsQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Mar 2020 01:16:01 -0700
IronPort-SDR: 
 IA7xC5rvkLfqXy48PyIvj6KCU4/as/vZVGHY6Bv09oSS6ekYciXQsbso7y3t2LtymVgt7585iN
 3/aBjsuFPNBA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,307,1580803200";
   d="scan'208";a="393898816"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga004.jf.intel.com with ESMTP; 26 Mar 2020 01:15:57 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v11 1/9] KVM: VMX: Introduce CET VMX fields and flags
Date: Thu, 26 Mar 2020 16:18:38 +0800
Message-Id: <20200326081847.5870-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200326081847.5870-1-weijiang.yang@intel.com>
References: <20200326081847.5870-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CET(Control-flow Enforcement Technology) is a CPU feature
used to prevent Return/Jump-Oriented Programming(ROP/JOP)
attacks. It provides the following sub-features to defend
against ROP/JOP style control-flow subversion attacks:

Shadow Stack (SHSTK):
  A second stack for program which is used exclusively for
  control transfer operations.

Indirect Branch Tracking (IBT):
  Code branching protection to defend against jump/call oriented
  programming.

Several new CET MSRs are defined in kernel to support CET:
  MSR_IA32_{U,S}_CET: Controls the CET settings for user
                      mode and kernel mode respectively.

  MSR_IA32_PL{0,1,2,3}_SSP: Stores shadow stack pointers for
                            CPL-0,1,2,3 protection respectively.

  MSR_IA32_INT_SSP_TAB: Stores base address of shadow stack
                        pointer table.

Two XSAVES state bits are introduced for CET:
  IA32_XSS:[bit 11]: Control saving/restoring user mode CET states
  IA32_XSS:[bit 12]: Control saving/restoring kernel mode CET states.

Six VMCS fields are introduced for CET:
  {HOST,GUEST}_S_CET: Stores CET settings for kernel mode.
  {HOST,GUEST}_SSP: Stores shadow stack pointer of current task/thread.
  {HOST,GUEST}_INTR_SSP_TABLE: Stores base address of shadow stack pointer
                               table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host CET states are restored
from below VMCS fields at VM-Exit:
  HOST_S_CET
  HOST_SSP
  HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest CET states are loaded
from below VMCS fields at VM-Entry:
  GUEST_S_CET
  GUEST_SSP
  GUEST_INTR_SSP_TABLE

Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h      | 8 ++++++++
 arch/x86/include/uapi/asm/kvm.h | 1 +
 arch/x86/kvm/x86.c              | 4 ++++
 arch/x86/kvm/x86.h              | 2 +-
 4 files changed, 14 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11459575
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22DE21668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F1EC92083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727927AbgCZIQZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 04:16:25 -0400
Received: from mga02.intel.com ([134.134.136.20]:27564 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727905AbgCZIQV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 04:16:21 -0400
IronPort-SDR: 
 BYHcyGoMEeXPVXtCfu5egkjnZMBQHH4fTi/WtQOE2SA/jDCtC+g90Fnb3YZjl03x3Tr5zE/F9G
 xXzjB10GIqpA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Mar 2020 01:16:20 -0700
IronPort-SDR: 
 dkzzAtz017rk8RyDRB+3vRjPK7HXpo0cY0FFN+XhnlFPTk9CTr+1CkmtgnpbdCTBejU7XWlNqY
 mFDDqSlPcQJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,307,1580803200";
   d="scan'208";a="393899043"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga004.jf.intel.com with ESMTP; 26 Mar 2020 01:16:18 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [kvm-unit-tests PATCH] x86: Add tests for user-mode CET
Date: Thu, 26 Mar 2020 16:18:47 +0800
Message-Id: <20200326081847.5870-11-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200326081847.5870-1-weijiang.yang@intel.com>
References: <20200326081847.5870-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test user-mode CET support of KVM,
it's tested on Intel new platform. Two CET features: Shadow Stack
Protection(SHSTK) and Indirect-Branch Tracking(IBT) are enclosed.

In SHSTK test, if the function return-address in normal stack is
tampered with a value not equal to the one on shadow-stack, #CP
(Control Protection Exception)will generated on function returning.
This feature is supported by processor itself, no compiler/link
option is required.

However, to enabled IBT, we need to add -fcf-protection=full in
compiler options, this makes the compiler insert endbr64 at the
very beginning of each jmp/call target given the binary is for
x86_64.

To get PASS results, the following conditions must be met:
1) The processor is powered with CET feature.
2) The kernel is patched with the latest CET kernel patches.
3) The KVM and QEMU are patched with the latest CET patches.
4) Use CET-enabled gcc to compile the test app.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 lib/x86/desc.c      |   2 +
 lib/x86/msr.h       |   2 +
 lib/x86/processor.h |   3 +
 x86/Makefile.common |   3 +-
 x86/Makefile.x86_64 |   3 +-
 x86/cet.c           | 212 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   6 ++
 7 files changed, 229 insertions(+), 2 deletions(-)
 create mode 100644 x86/cet.c

```
#### [PATCH] KVM: VMX: Add a trampoline to fix VMREAD error handling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11460583
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 253F113A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 16:07:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 06DE020A8B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 16:07:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728495AbgCZQHh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 12:07:37 -0400
Received: from mga18.intel.com ([134.134.136.126]:30493 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726296AbgCZQHh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 12:07:37 -0400
IronPort-SDR: 
 FGBz2xMdMIi+o/OCF5qQySPSeZ12Gg8g3cRRzWIL73yfO7JzcX6ze28KenGVvCk3/iCGD6KS0B
 Srmhc1ms8Alw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Mar 2020 09:07:14 -0700
IronPort-SDR: 
 60DD6ASrQKnWWSECPVfEjeSbkN5gTk45rYzmuNG77KnGiv+UN8YRKtQ5Dvi3vOf2aRMLVgoo4/
 Iv+gAKAm3bpA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,309,1580803200";
   d="scan'208";a="358191585"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 26 Mar 2020 09:07:14 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Add a trampoline to fix VMREAD error handling
Date: Thu, 26 Mar 2020 09:07:12 -0700
Message-Id: <20200326160712.28803-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a hand coded assembly trampoline to preserve volatile registers
across vmread_error(), and to handle the calling convention differences
between 64-bit and 32-bit due to asmlinkage on vmread_error().  Pass
@field and @fault on the stack when invoking the trampoline to avoid
clobbering volatile registers in the context of the inline assembly.

Calling vmread_error() directly from inline assembly is partially broken
on 64-bit, and completely broken on 32-bit.  On 64-bit, it will clobber
%rdi and %rsi (used to pass @field and @fault) and any volatile regs
written by vmread_error().  On 32-bit, asmlinkage means vmread_error()
expects the parameters to be passed on the stack, not via regs.

Opportunistically zero out the result in the trampoline to save a few
bytes of code for every VMREAD.  A happy side effect of the trampoline
is that the inline code footprint is reduced by three bytes on 64-bit
due to PUSH/POP being more efficent (in terms of opcode bytes) than MOV.

Fixes: 6e2020977e3e6 ("KVM: VMX: Add error handling to VMREAD helper")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Becuase there just isn't enough custom assembly in VMX :-)

Simply reverting isn't a great option because we'd lose error reporting
for VMREAD failure, i.e. it'd return garbage with no other indication that
something went awry.

Tested all paths (fail, fault w/o rebooting, fault w/ rebooting) on both
64-bit and 32-bit.

 arch/x86/kvm/vmx/ops.h     | 28 +++++++++++++-----
 arch/x86/kvm/vmx/vmenter.S | 58 ++++++++++++++++++++++++++++++++++++++
 2 files changed, 79 insertions(+), 7 deletions(-)

```
#### [PATCH 1/3] KVM: X86: Delay read msr data iff writes ICR MSR
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11458991
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A74781
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 02:20:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1B4212073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 02:20:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="F1LxSMfi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727733AbgCZCUR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 22:20:17 -0400
Received: from mail-pj1-f67.google.com ([209.85.216.67]:34980 "EHLO
        mail-pj1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727590AbgCZCUR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 22:20:17 -0400
Received: by mail-pj1-f67.google.com with SMTP id g9so1805504pjp.0;
        Wed, 25 Mar 2020 19:20:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=qDBMnluBEIKHHnYAEDKv+uJNUJGj8Te28Rln44SHO8E=;
        b=F1LxSMfimwN3imJWkTMpv1Ri55oBYP5f5KoUR6cLAlBzGPJ7PeGsjDP/ps2VHuexyk
         N1hgmnpHVwXNPv7gU5xMpmJ8N0APDSLOc12OUdtaOpWxNEMKrLpNA2fJ+oF9aF8oqL1Z
         DC8r7yDGm6mXPIOporC8Bb7e+kKM4Job5dMn+9pYU3G/gjeRFiCcvxsUbpw9nx+Oa+U4
         bc9lQSgKmMew7NSY0rd6PxTJ0BWkipCoJA3mHdQ2TBdeS3ndNIj/644nizmPJxZLWdPN
         nyYpp2YTC9vJ4/aIiRRaMkXthP7fIy06FBukde5WhwA5hBIUvkInfiqIZdFy5G5s83Fu
         m1UQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=qDBMnluBEIKHHnYAEDKv+uJNUJGj8Te28Rln44SHO8E=;
        b=gaPSxDUjgfZ54TtZxLjrPungrxBAFHVUodN+Ly3np9myaJXm9XsNMJVtEbid+luVxY
         Js2do5Ampc6XMR/oftQpu8x/ydlIjOt7fyMErsRoTFwbHNb9wm0w1S4GCzwne/lwsB+o
         mr7DSQi0lfo7+p8XIi3d1l8LnckLAwRrZG1rNJEs4AEz+MniPdN9BXRgClZm8XbZoDhv
         UtjxRqR0Yor+GGYvxnFLA2sISUKOPsQzl0Fd9IemRto1kTHjZ4F0r68BE0c+olJfvJ1e
         eCzw1RIuKF/8qRIJVmsQkzyMkGxVgllTKTl7Ocr4wv6wUWP7qM1VthQGaoUXID84zuQM
         o0fg==
X-Gm-Message-State: ANhLgQ0MwtYUKgQFrhp+c8vpXctQefao7QY8K6qTWLgWWnKYbTfgNOqZ
        SWOEQ/pq+USUidRFrWQM334T34c9
X-Google-Smtp-Source: 
 ADFU+vsDOt+koJGV7OQZXsBtSoSJra3SJ5LO8pyMovhgNC5OYrs0HUtc61ROfkcpYLJHgnUt49SfZQ==
X-Received: by 2002:a17:902:70cb:: with SMTP id
 l11mr6118046plt.127.1585189216114;
        Wed, 25 Mar 2020 19:20:16 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 mq18sm452975pjb.6.2020.03.25.19.20.13
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 25 Mar 2020 19:20:15 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/3] KVM: X86: Delay read msr data iff writes ICR MSR
Date: Thu, 26 Mar 2020 10:20:00 +0800
Message-Id: <1585189202-1708-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1585189202-1708-1-git-send-email-wanpengli@tencent.com>
References: <1585189202-1708-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Delay read msr data until we identify guest accesses ICR MSR to avoid
to penalize all other MSR writes.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: x86: introduce kvm_mmu_invalidate_gva
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11459741
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1642913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 09:35:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C8B7220775
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 09:35:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d9Iw1FZV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727866AbgCZJfW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 05:35:22 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:39204 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726540AbgCZJfW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Mar 2020 05:35:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585215321;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=m/avxIP9KlrNmDBgwKdf8OcnP23o4V4eI0nLWWAsZqw=;
        b=d9Iw1FZVeGukWPYaQqDuDsrML6cWW2phrdisaCSRHwr2I3faqLkBGH4aTxTbN5PwwyvOE+
        PVtYPelUDxwuvF9wP9bVAufo34j3EYGt3a0yAi6Y4vVl/PF+PPigDLsUQ4ma+EUo2CANwf
        HCrupVgvZaeBrCZhzRJIx2ao/jFWnwk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-30-IOMi7zyVOYy1nC_VcSIAFg-1; Thu, 26 Mar 2020 05:35:19 -0400
X-MC-Unique: IOMi7zyVOYy1nC_VcSIAFg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8378D100550D;
        Thu, 26 Mar 2020 09:35:18 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D14129CA3;
        Thu, 26 Mar 2020 09:35:17 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Junaid Shahid <junaids@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 1/3] KVM: x86: introduce kvm_mmu_invalidate_gva
Date: Thu, 26 Mar 2020 05:35:14 -0400
Message-Id: <20200326093516.24215-2-pbonzini@redhat.com>
In-Reply-To: <20200326093516.24215-1-pbonzini@redhat.com>
References: <20200326093516.24215-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Wrap the combination of mmu->invlpg and kvm_x86_ops->tlb_flush_gva
into a new function.  This function also lets us specify the host PGD to
invalidate and also the MMU, both of which will be useful in fixing and
simplifying kvm_inject_emulated_page_fault.

A nested guest's MMU however has g_context->invlpg == NULL.  Instead of
setting it to nonpaging_invlpg, make kvm_mmu_invalidate_gva the only
entry point to mmu->invlpg and make a NULL invlpg pointer equivalent
to nonpaging_invlpg, saving a retpoline.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +
 arch/x86/kvm/mmu/mmu.c          | 71 +++++++++++++++++++++------------
 2 files changed, 47 insertions(+), 26 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the spdx tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11459171
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F85E161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:27:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4EA402074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:27:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="c+9Ubtkw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727703AbgCZD1d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 23:27:33 -0400
Received: from ozlabs.org ([203.11.71.1]:40923 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727612AbgCZD1d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 23:27:33 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 48nr5Z0XdJz9sSH;
        Thu, 26 Mar 2020 14:27:30 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1585193250;
        bh=ZKW7qcECKhZTwsefzZv3KK0kIUy8HwxrSNINue5nCKs=;
        h=Date:From:To:Cc:Subject:From;
        b=c+9UbtkwAW96p6Br+QzTYW/T3AyEVUODTofZrCm+Oi/BqcS9TH4rVDEiSjp8pm8o9
         QEYb7n637GWve85Hp9VM47n9U53DdxkvtvnF2FvzWOivdVbmo5P2WygjIwnBTdsfd3
         nZ42XDPTVdTBLiISrip/t0ZF0gYQxHYOJ6KmMBz9vT2Na3gXbmfv9fLG7QjTImzei8
         1p6xBOoneIYOfwGx/g92bMlxQ+DXrMxY/eL0A7gzM6ECbZeOEFawSDhrRHwXcp9G5N
         TgxK6zi+TixVFKl0q7U2oKzyrrKFtRcp2lRjfOllDZM2EedTmjQzsorYzN3XUKrCqm
         QLzY+A7TgYlDQ==
Date: Thu, 26 Mar 2020 14:27:27 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Greg KH <greg@kroah.com>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Masahiro Yamada <masahiroy@kernel.org>,
        Andrew Jones <drjones@redhat.com>
Subject: linux-next: manual merge of the kvm tree with the spdx tree
Message-ID: <20200326142727.6991104f@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  tools/testing/selftests/kvm/.gitignore

between commit:

  d198b34f3855 (".gitignore: add SPDX License Identifier")

from the spdx tree and commit:

  1914f624f5e3 ("selftests: KVM: SVM: Add vmcall test to gitignore")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH v3 1/3] Add a new LSM-supporting anonymous inode interfaceFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11460779
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A75B115AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 18:15:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6DEC020719
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 18:15:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="DIe/HSz3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728248AbgCZSPV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 14:15:21 -0400
Received: from mail-vk1-f202.google.com ([209.85.221.202]:44417 "EHLO
        mail-vk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727192AbgCZSPU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 14:15:20 -0400
Received: by mail-vk1-f202.google.com with SMTP id k67so1935183vka.11
        for <kvm@vger.kernel.org>; Thu, 26 Mar 2020 11:15:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=zFlM70MP3VetVuidGZ5oQERxbIVr8cobPoAE2yMCfNg=;
        b=DIe/HSz3irSSjaq32QsfyjZI/YZ3Y7vKLJPlkid+ENQBy0og6XLoK/vsn393qwwoTa
         QFd3ZB1IxgsRAm3ncm8AX3wTCR3ToobhMfvuvW0NwQezsbkcGhDoa6HoGpnGxb9kA4+T
         q9V45m609izFt/ZOBtAtAx/fcsEUEMCXq+NqRB4gy+4tfEZO+e03R9/7sAk7hH8qSYU6
         QBsvcJH+C+HWowVgYv64k+YM1aZ3PD+ANsYurxvBnUS/cv+mesubXbYxu1FqlDMHllJn
         DQJthAmCQS+80bo/ZN7lAE2DRzq7gpXjB0BJaFB+me2ciOnEr8QlKDb69nWPXOheNANn
         eE5Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=zFlM70MP3VetVuidGZ5oQERxbIVr8cobPoAE2yMCfNg=;
        b=GnhoDeiUNQNYBd9n9s58d6BINaYm4OxI9uEm6lxX5ArTpgt3zsZJ8Vhm6bWB47i10R
         BkGHs/m5QXDDY21B9rO8Td8XDjVLKIr3g5nJZ4rZCyV/mERs51khCmYfQ65tuds9agIW
         rqtiIxheMESRhZSp2GzxfW08QQswFktleu+gYhcnix/WsN377AmGOnZdQggat9d260zK
         067qc39YWJER8aihL1FHVIOFQiO+hAX/CadP+cd2kdz9IVUnH6Ij+Y82wd3MkIiq2Dng
         T6CpgAdsVu56AfYqpzaQy48g/8Rs2BH5AkqhdMQDDQvWLBazVVGSBg3H0xSMZOMc3ybS
         AZ1Q==
X-Gm-Message-State: ANhLgQ3mtrHqUBySVsCC21kF0XEv869LSHpQiD1LI5I5134odwCkdwJQ
        a/o5h9ayZFddmC7CIiOE41XPCPYYCOc=
X-Google-Smtp-Source: 
 ADFU+vtOQynXnyAgy9V5Y3E9NRdRmPltZtqWbmU5iARuCklYCp+PHmqraq7XO7in4i4C6bM9MYUrjhTH4s0=
X-Received: by 2002:a67:f953:: with SMTP id u19mr8213724vsq.8.1585246516747;
 Thu, 26 Mar 2020 11:15:16 -0700 (PDT)
Date: Thu, 26 Mar 2020 11:14:54 -0700
In-Reply-To: <20200326181456.132742-1-dancol@google.com>
Message-Id: <20200326181456.132742-2-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
 <20200326181456.132742-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v3 1/3] Add a new LSM-supporting anonymous inode interface
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two new functions, anon_inode_getfile_secure and
anon_inode_getfd_secure, that create anonymous-node files with
individual non-S_PRIVATE inodes to which security modules can apply
policy. Existing callers continue using the original singleton-inode
kind of anonymous-inode file. We can transition anonymous inode users
to the new kind of anonymous inode in individual patches for the sake
of bisection and review.

The new functions accept an optional context_inode parameter that
callers can use to provide additional contextual information to
security modules, e.g., indicating that one anonymous struct file is a
logical child of another, allowing a security model to propagate
security information from one to the other.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/anon_inodes.c            | 196 ++++++++++++++++++++++++++++--------
 fs/userfaultfd.c            |   4 +-
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |   9 ++
 include/linux/security.h    |   4 +
 security/security.c         |  10 ++
 6 files changed, 191 insertions(+), 45 deletions(-)

```
#### [PATCH v4 1/3] Add a new LSM-supporting anonymous inode interfaceFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11460997
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 80507159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:07:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 593AE2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:07:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fAshHZ+Q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728733AbgCZUGv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 16:06:51 -0400
Received: from mail-pj1-f73.google.com ([209.85.216.73]:54411 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728671AbgCZUGu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 16:06:50 -0400
Received: by mail-pj1-f73.google.com with SMTP id p14so5488138pjo.4
        for <kvm@vger.kernel.org>; Thu, 26 Mar 2020 13:06:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=PVSwrvgjQE4kHOREjmYboSRHDQEjtQZz+pfSq1QNzRM=;
        b=fAshHZ+QfAUpjSsm5LB2GCuEMSmaI+uOd0OSFMcRdZduS8R1Vw5QlKd88PdqNbgyof
         2MPjdW97zMnbMoDplPGnYp1Saf/M48cZX8x4zFxI+sCdYFTYe4vEF1iiQIKLSso3SVCq
         cCdtJBaDYgAWo6TrZpbO2y1mVzqUCPaAKdsUzxphGQo0hiwxw19StHR7BBK10y1909hE
         +5PbEbs9c1xkbjh9g6DU5oHZNphxlAYLZvA42WDzF5V9CZLF1rbOdBhCaEYCskTS05/j
         gdOL0nEvKp+84wcrsj3x/i4MRkM6j+THLcZ8eWKlyAHiBvEACHn6TgmRWxMM54EHfSbr
         KfPw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=PVSwrvgjQE4kHOREjmYboSRHDQEjtQZz+pfSq1QNzRM=;
        b=UjZhTpdhVXRgCmwSdETX+nZCQ2fBk8ZbkfjhC4RMgz6cm3ymA0QvF38UlKUFTtb3PL
         Wiok+xk+dt0rh+A0fSBL6hKYL4Qbgk1t5R5OLloT1i9Th6mEBY7WQb4JaGvhSD5lqOu3
         yRhZW7AMNFbvmp31LJQ2oiFeFN8h9EM0RO05R3eXNXnnTJBK4ee8yY2VGhnwevlAUqkv
         WIoONrkpI3II8sauOxf2lSMO7CwT/kV6shokEPlO+I562+De05VPT6inYD/CK1jB5hKQ
         2okUOm/m0claucDm2CIltzb0BYVl4ipM2OXT2PqZZ5feq9cZTS9okK59o57AKojjX4bH
         fPfg==
X-Gm-Message-State: ANhLgQ0q0OwLIa7K5KDVo6+M3s7UJcpFfoySdCnaGgDlVgw0sv4+CVpI
        4GoMQ/GZ3JyJzOJX4hRZCuxLe78JDQ0=
X-Google-Smtp-Source: 
 ADFU+vt2nsyHQf4Ri/E3096WPwNm/QjrzhH0m1BcyB4bLSACpbtYLSr4OT7XeJlvWX3iesfKdXFwG3Vd4v8=
X-Received: by 2002:a63:7409:: with SMTP id p9mr10150468pgc.206.1585253206759;
 Thu, 26 Mar 2020 13:06:46 -0700 (PDT)
Date: Thu, 26 Mar 2020 13:06:32 -0700
In-Reply-To: <20200326200634.222009-1-dancol@google.com>
Message-Id: <20200326200634.222009-2-dancol@google.com>
Mime-Version: 1.0
References: <20200326181456.132742-1-dancol@google.com>
 <20200326200634.222009-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v4 1/3] Add a new LSM-supporting anonymous inode interface
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two new functions, anon_inode_getfile_secure and
anon_inode_getfd_secure, that create anonymous-node files with
individual non-S_PRIVATE inodes to which security modules can apply
policy. Existing callers continue using the original singleton-inode
kind of anonymous-inode file. We can transition anonymous inode users
to the new kind of anonymous inode in individual patches for the sake
of bisection and review.

The new functions accept an optional context_inode parameter that
callers can use to provide additional contextual information to
security modules, e.g., indicating that one anonymous struct file is a
logical child of another, allowing a security model to propagate
security information from one to the other.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/anon_inodes.c            | 196 ++++++++++++++++++++++++++++--------
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |  11 ++
 include/linux/security.h    |   3 +
 security/security.c         |   9 ++
 5 files changed, 190 insertions(+), 42 deletions(-)

```
#### [PATCH V9 1/9] vhost: refine vhost and vringh kconfig
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11460173
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BF3C161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 14:02:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 64E752073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 14:02:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cjiuNJQH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728132AbgCZOCn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 10:02:43 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:21867 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728081AbgCZOCn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Mar 2020 10:02:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585231362;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=cQAMj9E7pnEO97gxazN0awVnwRs79iDcGQ6g5ZjNfoc=;
        b=cjiuNJQHzwa7g1popzfDBlqOY4HSXzYexLeC8kq9PTUrTiw9uZAO/KNqnKGetk3VCsIwp2
        Gxjk1s+uJtRlVVvCY7zKFwykdv8Oyzi7rZpIOeHuL3XLuR7rK4CZa6aclrsduPt3sQZaE9
        neJKBQpfjp16dBMA58zhjqMTX3jyXIA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-78-TzKs58iZNRmrNGCxYJF2Cw-1; Thu, 26 Mar 2020 10:02:36 -0400
X-MC-Unique: TzKs58iZNRmrNGCxYJF2Cw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89193100FB30;
        Thu, 26 Mar 2020 14:02:28 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-19.pek2.redhat.com [10.72.12.19])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B6EDE60C80;
        Thu, 26 Mar 2020 14:01:59 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, zhangweining@ruijie.com.cn,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V9 1/9] vhost: refine vhost and vringh kconfig
Date: Thu, 26 Mar 2020 22:01:17 +0800
Message-Id: <20200326140125.19794-2-jasowang@redhat.com>
In-Reply-To: <20200326140125.19794-1-jasowang@redhat.com>
References: <20200326140125.19794-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, CONFIG_VHOST depends on CONFIG_VIRTUALIZATION. But vhost is
not necessarily for VM since it's a generic userspace and kernel
communication protocol. Such dependency may prevent archs without
virtualization support from using vhost.

To solve this, a dedicated vhost menu is created under drivers so
CONIFG_VHOST can be decoupled out of CONFIG_VIRTUALIZATION.

While at it, also squash Kconfig.vringh into vhost Kconfig file. This
avoids the trick of conditional inclusion from VOP or CAIF. Then it
will be easier to introduce new vringh users and common dependency for
both vringh and vhost.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 arch/arm/kvm/Kconfig         |  2 --
 arch/arm64/kvm/Kconfig       |  2 --
 arch/mips/kvm/Kconfig        |  2 --
 arch/powerpc/kvm/Kconfig     |  2 --
 arch/s390/kvm/Kconfig        |  4 ----
 arch/x86/kvm/Kconfig         |  4 ----
 drivers/Kconfig              |  2 ++
 drivers/misc/mic/Kconfig     |  4 ----
 drivers/net/caif/Kconfig     |  4 ----
 drivers/vhost/Kconfig        | 23 ++++++++++++++---------
 drivers/vhost/Kconfig.vringh |  6 ------
 11 files changed, 16 insertions(+), 39 deletions(-)
 delete mode 100644 drivers/vhost/Kconfig.vringh

```
#### [PATCH v2 1/2] Documentation/driver-api/vfio-mediated-device.rst: update for aggregation support
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11459305
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26F18913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 05:41:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 016732078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 05:41:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726163AbgCZFll (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 01:41:41 -0400
Received: from mga14.intel.com ([192.55.52.115]:26877 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725819AbgCZFlk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 01:41:40 -0400
IronPort-SDR: 
 5HZHFUDl52leJJNQvJ2lPmtA/9E4zm1X9P1OMI9snd3Ky0tdDM+8m+i5FsCEs26BVRnnYvVMDk
 +9TYy7xAVv3A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 22:41:40 -0700
IronPort-SDR: 
 sFznkQhR+w+6OcLtC/sm6RMZ1bl5a3O1T3PyMuBYlLSeNP+h21TgDIHDcNTDkgXRsVCVqf6W2x
 1ptFnUhGLHyg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,307,1580803200";
   d="scan'208";a="393862307"
Received: from zhaji-mobl3.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.174.174])
  by orsmga004.jf.intel.com with ESMTP; 25 Mar 2020 22:41:38 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, kevin.tian@intel.com,
        intel-gvt-dev@lists.freedesktop.org,
        "Jiang, Dave" <dave.jiang@intel.com>
Subject: [PATCH v2 1/2] Documentation/driver-api/vfio-mediated-device.rst:
 update for aggregation support
Date: Thu, 26 Mar 2020 13:41:35 +0800
Message-Id: <20200326054136.2543-2-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200326054136.2543-1-zhenyuw@linux.intel.com>
References: <20200326054136.2543-1-zhenyuw@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update doc for mdev aggregation support. Describe mdev generic
parameter directory under mdev device directory.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: "Jiang, Dave" <dave.jiang@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 .../driver-api/vfio-mediated-device.rst       | 19 +++++++++++++++++++
 1 file changed, 19 insertions(+)

```
