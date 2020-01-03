#### [kvm-unit-tests RFC PATCH v3 1/7] lib: Add _UL and _ULL definitions to linux/const.h
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11315785
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9CB306C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 13:47:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7B6B221D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 13:47:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728393AbgABNrH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 08:47:07 -0500
Received: from foss.arm.com ([217.140.110.172]:47280 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728342AbgABNrH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 08:47:07 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 94E911FB;
        Thu,  2 Jan 2020 05:47:06 -0800 (PST)
Received: from e121566-lin.arm.com,emea.arm.com,asiapac.arm.com,usa.arm.com
 (unknown [10.37.9.21])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 5B4263F68F;
        Thu,  2 Jan 2020 05:47:04 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, maz@kernel.org,
        andre.przywara@arm.com, Laurent Vivier <lvivier@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests RFC PATCH v3 1/7] lib: Add _UL and _ULL definitions
 to linux/const.h
Date: Thu,  2 Jan 2020 13:46:40 +0000
Message-Id: <1577972806-16184-2-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1577972806-16184-1-git-send-email-alexandru.elisei@arm.com>
References: <1577972806-16184-1-git-send-email-alexandru.elisei@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is an UL macro defined in lib/arm64/asm/pgtable-hwdef.h.  Replace
it with the _UL macro and put it in lib/linux/const.h, where it can be
used in other files. To keep things consistent with Linux's
include/uapi/linux/const.h file, also add an _ULL macro.

Cc: Drew Jones <drjones@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>
Cc: Thomas Huth <thuth@redhat.com>
Cc: David Hildenbrand <david@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/linux/const.h             |  7 ++++--
 lib/asm-generic/page.h        |  2 +-
 lib/arm/asm/page.h            |  2 +-
 lib/arm/asm/pgtable-hwdef.h   | 22 ++++++++++---------
 lib/arm/asm/thread_info.h     |  3 ++-
 lib/arm64/asm/page.h          |  2 +-
 lib/arm64/asm/pgtable-hwdef.h | 50 +++++++++++++++++++++----------------------
 lib/x86/asm/page.h            |  2 +-
 8 files changed, 48 insertions(+), 42 deletions(-)

```
#### [RESEND PATCH v10 01/10] Documentation: Add EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11315349
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D41B17EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 05:15:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5C0B321734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 05:15:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726232AbgABFPM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 00:15:12 -0500
Received: from mga12.intel.com ([192.55.52.136]:22040 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725788AbgABFPL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 00:15:11 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Jan 2020 21:15:09 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,385,1571727600";
   d="scan'208";a="369236547"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga004.jf.intel.com with ESMTP; 01 Jan 2020 21:15:07 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v10 01/10] Documentation: Add EPT based Subpage
 Protection and related APIs
Date: Thu,  2 Jan 2020 13:18:55 +0800
Message-Id: <20200102051904.32090-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200102051904.32090-1-weijiang.yang@intel.com>
References: <20200102051904.32090-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  39 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 179 ++++++++++++++++++++++++++
 2 files changed, 218 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [RESEND PATCH v10 01/10] Documentation: Add EPT based Subpage Protection and related APIs
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11315389
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 793BF1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:10:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57A9D217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:10:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726380AbgABGJZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 01:09:25 -0500
Received: from mga07.intel.com ([134.134.136.100]:3898 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725788AbgABGJY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 01:09:24 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Jan 2020 22:09:23 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,385,1571727600";
   d="scan'208";a="224706704"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 01 Jan 2020 22:09:22 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v10 01/10] Documentation: Add EPT based Subpage
 Protection and related APIs
Date: Thu,  2 Jan 2020 14:13:10 +0800
Message-Id: <20200102061319.10077-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200102061319.10077-1-weijiang.yang@intel.com>
References: <20200102061319.10077-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virt/kvm/api.txt        |  39 ++++++
 Documentation/virtual/kvm/spp_kvm.txt | 179 ++++++++++++++++++++++++++
 2 files changed, 218 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

```
#### [PATCH] KVM: SVM: Fix potential memory leak in svm_cpu_init()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11315247
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02A1A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 02:19:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D328121734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 02:19:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727538AbgABCTN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jan 2020 21:19:13 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8657 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727511AbgABCTN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jan 2020 21:19:13 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 4477357E9891A67129BA;
        Thu,  2 Jan 2020 10:19:10 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.439.0; Thu, 2 Jan 2020
 10:19:03 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <liran.alon@oracle.com>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <x86@kernel.org>
Subject: [PATCH] KVM: SVM: Fix potential memory leak in svm_cpu_init()
Date: Thu, 2 Jan 2020 10:20:40 +0800
Message-ID: <1577931640-29420-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When kmalloc memory for sd->sev_vmcbs failed, we forget to free the page
held by sd->save_area.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [RESEND PATCH v10 04/10] mmu: spp: Add functions to operate SPP access bitmap
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11315373
Return-Path: <SRS0=nIe0=2X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 272C2930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:09:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 05B962053B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jan 2020 06:09:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727718AbgABGJe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 01:09:34 -0500
Received: from mga07.intel.com ([134.134.136.100]:3898 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726207AbgABGJ3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 01:09:29 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Jan 2020 22:09:29 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,385,1571727600";
   d="scan'208";a="224706732"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga001.fm.intel.com with ESMTP; 01 Jan 2020 22:09:27 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v10 04/10] mmu: spp: Add functions to operate SPP
 access bitmap
Date: Thu,  2 Jan 2020 14:13:13 +0800
Message-Id: <20200102061319.10077-5-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200102061319.10077-1-weijiang.yang@intel.com>
References: <20200102061319.10077-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Create access bitmap for SPP subpages, the bitmap can
be accessed with a gfn. The initial access bitmap for each
physical page is 0xFFFFFFFF, meaning SPP is not enabled for the
subpages.

Co-developed-by: He Chen <he.chen@linux.intel.com>
Signed-off-by: He Chen <he.chen@linux.intel.com>
Co-developed-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   2 +
 arch/x86/kvm/mmu/spp.c          | 332 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/mmu/spp.h          |  12 ++
 include/uapi/linux/kvm.h        |   8 +
 4 files changed, 354 insertions(+)

```
