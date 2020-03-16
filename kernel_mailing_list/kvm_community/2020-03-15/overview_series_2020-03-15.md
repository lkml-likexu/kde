#### [PATCH 1/2] kvm: selftests: Fix no directory error when OUTPUT specified
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11438799
Return-Path: <SRS0=vYwd=5A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA09A1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 09:52:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA82720738
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 09:52:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728222AbgCOJwU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 15 Mar 2020 05:52:20 -0400
Received: from mga17.intel.com ([192.55.52.151]:35235 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728108AbgCOJwS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 15 Mar 2020 05:52:18 -0400
IronPort-SDR: 
 dIffU8Q2LOE5vcyXK1LVWzC56NaARurmpf4b217Vp3nt8S0U0cjKuOMPfvv/mjZwnEchbEuHKV
 nm7hGB22a0MQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Mar 2020 02:52:18 -0700
IronPort-SDR: 
 bG92V6x9NMRAyU/obRt+rtVwK/dscnZrlXiJ1BPqlcGSGDAPg6yUzQKXE0UvHpwWxBlsQAWWy1
 Kj1411CZnb/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,556,1574150400";
   d="scan'208";a="416800340"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.160])
  by orsmga005.jf.intel.com with ESMTP; 15 Mar 2020 02:52:16 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Shuah Khan <shuah@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 1/2] kvm: selftests: Fix no directory error when OUTPUT
 specified
Date: Sun, 15 Mar 2020 17:34:24 +0800
Message-Id: <20200315093425.33600-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200315093425.33600-1-xiaoyao.li@intel.com>
References: <20200315093425.33600-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When build kvm selftests to an specified directory with

	make OUTPUT=~/kvm-selftests

it encouters following error：

/usr/bin/ld: cannot open output file
/home/lxy/kvm-selftests/x86_64/cr4_cpuid_sync_test: No such file or
directory
collect2: error: ld returned 1 exit status
make: *** [../lib.mk:141:
/home/lxy/kvm-selftests/x86_64/cr4_cpuid_sync_test] Error 1

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 tools/testing/selftests/kvm/Makefile | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5 1/9] x86/split_lock: Rework the initialization flow of split lock detection
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11438703
Return-Path: <SRS0=vYwd=5A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B8BC1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 05:23:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2BBFB20724
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 15 Mar 2020 05:23:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727129AbgCOFW4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 15 Mar 2020 01:22:56 -0400
Received: from mga18.intel.com ([134.134.136.126]:47872 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726648AbgCOFWz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 15 Mar 2020 01:22:55 -0400
IronPort-SDR: 
 JcdQ7hEigbK7k7y2UMeM4ge9xNObCXa6QFBvUuwy5J9fjrtYUXD/eT4NlyamLpxfzaSud34sMW
 4KIyYqFPwLfg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Mar 2020 22:22:54 -0700
IronPort-SDR: 
 5ZZBy/ze+bNVXCPSicXdAZR15vF4VahmFUoNh2WCQiNTZLac3pcO/zbZG7pkJW+Zejf3TM8hP5
 192nc8WwOmYg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,555,1574150400";
   d="scan'208";a="267194204"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.160])
  by fmsmga004.fm.intel.com with ESMTP; 14 Mar 2020 22:22:51 -0700
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
Subject: [PATCH v5 1/9] x86/split_lock: Rework the initialization flow of
 split lock detection
Date: Sun, 15 Mar 2020 13:05:09 +0800
Message-Id: <20200315050517.127446-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200315050517.127446-1-xiaoyao.li@intel.com>
References: <20200315050517.127446-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current initialization flow of split lock detection has following issues:
1. It assumes the initial value of MSR_TEST_CTRL.SPLIT_LOCK_DETECT to be
   zero. However, it's possible that BIOS/firmware has set it.

2. X86_FEATURE_SPLIT_LOCK_DETECT flag is unconditionally set even if
   there is a virtualization flaw that FMS indicates the existence while
   it's actually not supported.

3. Because of #2, KVM cannot rely on X86_FEATURE_SPLIT_LOCK_DETECT flag
   to check verify if feature does exist, so cannot expose it to guest.

To solve these issues, introducing a new sld_state, "sld_not_exist", as
the default value. It will be switched to other value if CORE_CAPABILITIES
or FMS enumerate split lock detection.

Only when sld_state != sld_not_exist, it goes to initialization flow.

In initialization flow, it explicitly accesses MSR_TEST_CTRL and
SPLIT_LOCK_DETECT bit to ensure there is no virtualization flaw, i.e.,
feature split lock detection does supported. In detail,
 1. sld_off,   verify SPLIT_LOCK_DETECT bit can be cleared, and clear it;
 2. sld_warn,  verify SPLIT_LOCK_DETECT bit can be cleared and set,
               and set it;
 3. sld_fatal, verify SPLIT_LOCK_DETECT bit can be set, and set it;

Only when no MSR aceessing failure, can X86_FEATURE_SPLIT_LOCK_DETECT be
set. So kvm can use X86_FEATURE_SPLIT_LOCK_DETECT to check the existence
of feature.

Also, since MSR and bit are checked when split_lock_init(), there
is no need to use safe version RDMSR/WRMSR at runtime.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kernel/cpu/intel.c | 64 +++++++++++++++++++++++++------------
 1 file changed, 44 insertions(+), 20 deletions(-)

```
