#### [PATCH v22 1/9] hw/arm/virt: Introduce a RAS machine option
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11323263
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60D3A138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 11:32:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 47D9F206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 11:32:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726486AbgAHLce (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jan 2020 06:32:34 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:9128 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726098AbgAHLce (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jan 2020 06:32:34 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 9367E28A300D5AB3394B;
        Wed,  8 Jan 2020 19:32:32 +0800 (CST)
Received: from localhost.localdomain (10.151.151.249) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.439.0; Wed, 8 Jan 2020 19:32:25 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <pbonzini@redhat.com>, <gengdongjiu@huawei.com>, <mst@redhat.com>,
        <imammedo@redhat.com>, <shannon.zhaosl@gmail.com>,
        <peter.maydell@linaro.org>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>, <xuwei5@huawei.com>,
        <jonathan.cameron@huawei.com>, <james.morse@arm.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>
CC: <zhengxiang9@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v22 1/9] hw/arm/virt: Introduce a RAS machine option
Date: Wed, 8 Jan 2020 19:32:15 +0800
Message-ID: <1578483143-14905-2-git-send-email-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1578483143-14905-1-git-send-email-gengdongjiu@huawei.com>
References: <1578483143-14905-1-git-send-email-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.249]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

RAS Virtualization feature is not supported now, so add a RAS machine
option and disable it by default.

Reviewed-by: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
Acked-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/arm/virt.c         | 23 +++++++++++++++++++++++
 include/hw/arm/virt.h |  1 +
 2 files changed, 24 insertions(+)

```
#### [PATCH] KVM: x86/mmu: Apply max PA check for MMIO sptes to 32-bit KVM
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11322409
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3935109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 00:12:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 928A52072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 00:12:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726837AbgAHAMM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 19:12:12 -0500
Received: from mga03.intel.com ([134.134.136.65]:19849 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726462AbgAHAML (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 19:12:11 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Jan 2020 16:12:11 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,407,1571727600";
   d="scan'208";a="395574291"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga005.jf.intel.com with ESMTP; 07 Jan 2020 16:12:11 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Apply max PA check for MMIO sptes to 32-bit KVM
Date: Tue,  7 Jan 2020 16:12:10 -0800
Message-Id: <20200108001210.12913-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the bogus 64-bit only condition from the check that disables MMIO
spte optimization when the system supports the max PA, i.e. doesn't have
any reserved PA bits.  32-bit KVM always uses PAE paging for the shadow
MMU, and per Intel's SDM:

  PAE paging translates 32-bit linear addresses to 52-bit physical
  addresses.

The kernel's restrictions on max physical addresses are limits on how
much memory the kernel can reasonably use, not what physical addresses
are supported by hardware.

Fixes: ce88decffd17 ("KVM: MMU: mmio page fault support")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/mmu: Fix a benign Bitwise vs. Logical OR mixup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11322411
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF9B7109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 00:19:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C316B20656
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 00:19:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726906AbgAHATB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 19:19:01 -0500
Received: from mga09.intel.com ([134.134.136.24]:45392 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726537AbgAHATA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 19:19:00 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Jan 2020 16:19:00 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,407,1571727600";
   d="scan'208";a="211360872"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 07 Jan 2020 16:19:00 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Fix a benign Bitwise vs. Logical OR mixup
Date: Tue,  7 Jan 2020 16:18:59 -0800
Message-Id: <20200108001859.25254-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use a Logical OR in __is_rsvd_bits_set() to combine the two reserved bit
checks, which are obviously intended to be logical statements.  Switching
to a Logical OR is functionally a nop, but allows the compiler to better
optimize the checks.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 01/14] KVM: x86/mmu: Enforce max_level on HugeTLB mappings
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11324667
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60ADA1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 20:27:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4569520692
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 20:27:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727275AbgAHU1H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jan 2020 15:27:07 -0500
Received: from mga01.intel.com ([192.55.52.88]:57134 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725446AbgAHU1G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jan 2020 15:27:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 08 Jan 2020 12:27:05 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,411,1571727600";
   d="scan'208";a="211658356"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 08 Jan 2020 12:27:05 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        syzbot+c9d1fb51ac9d0d10c39d@syzkaller.appspotmail.com,
        Andrea Arcangeli <aarcange@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Barret Rhoden <brho@google.com>,
        David Hildenbrand <david@redhat.com>,
        Jason Zeng <jason.zeng@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liran Alon <liran.alon@oracle.com>,
        linux-nvdimm <linux-nvdimm@lists.01.org>
Subject: [PATCH 01/14] KVM: x86/mmu: Enforce max_level on HugeTLB mappings
Date: Wed,  8 Jan 2020 12:24:35 -0800
Message-Id: <20200108202448.9669-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200108202448.9669-1-sean.j.christopherson@intel.com>
References: <20200108202448.9669-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Limit KVM's mapping level for HugeTLB based on its calculated max_level.
The max_level check prior to invoking host_mapping_level() only filters
out the case where KVM cannot create a 2mb mapping, it doesn't handle
the scenario where KVM can create a 2mb but not 1gb mapping, and the
host is using a 1gb HugeTLB mapping.

Fixes: ad163aa8903d ("KVM: x86/mmu: Persist gfn_lpage_is_disallowed() to max_level")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH RFC] sched/fair: Penalty the cfs task which executes mwait/hlt
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11322453
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B6F6138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 01:50:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 23FC9206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 01:50:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ZM3lGfmD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726346AbgAHBuX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jan 2020 20:50:23 -0500
Received: from mail-pg1-f194.google.com ([209.85.215.194]:40293 "EHLO
        mail-pg1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726111AbgAHBuX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jan 2020 20:50:23 -0500
Received: by mail-pg1-f194.google.com with SMTP id k25so745749pgt.7;
        Tue, 07 Jan 2020 17:50:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=k/xLHVr+E3Mm0ZHWLILeml/rw0rkew9DOHcx6ajd5sk=;
        b=ZM3lGfmDx3evcWkdgiQL85j5d0lPcXoM1Q6+yAhQO2N2Uamr6u/T72rhsBCuOhlokr
         p66L+m6lonmCQDVQA1uQi12ZbBpMWZjgmeW6liYuCqVyuRp5ueCA/EKfUttJVvwIM/El
         6AqAJa3YmhumJ/hkEld5Y6AIjo3q1GhWHamGKkiA85nh0XPTb87txaxYJj03GrapnoAs
         HpR4AHrljcMRB6AElLeBTnOSsAu/DpvuVFMSQy1UQYTpeNKUfBGdii74qNxwYMi5L+oi
         52QUPUnaC/bOOl3ZZ0xeYnxvCd6hkjo9LzUd9gGBc4BMpeItOGH6GrKY2Sl7enbUm33q
         2n1Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=k/xLHVr+E3Mm0ZHWLILeml/rw0rkew9DOHcx6ajd5sk=;
        b=Pt9JXscrESLyNG51SRACjBOsdo0PthP9F7Ci4APGveBuDv9/Ku0sWAUDZaUyHSmZxz
         sxUGdW6maEMEI1ZU8GLMCAM9woWzPEkC6GOP6QKE3qiexMlWSJYE/P/ylmo3dRsfyl7y
         0IsWwnYPrrZ6yizT+MaLR/lO0u1xBQ2uzJG5747kj6o8UUBOITd7eUvjHlC/mcKLJepd
         YtqwSJGsOWRn/j0FjXUbnqC3n/qxIU+y1mSWIo97frF+0lHujNeynImF0Sgt7cpaCA8E
         kZbY6GRt+WhTLFZeQ6jA5SzgMQOr7TluopahDwlQvyRoDdmmCnNJ9IR+tWh7pF6HfV+X
         d5QA==
X-Gm-Message-State: APjAAAXlkGTohXyztmD2D+bdq8bQjhOYNtezIDd9jFD+MUuUs69yX6LA
        Pnk81atwhvHsr11MpyR/JwOKjTVo
X-Google-Smtp-Source: 
 APXvYqzhfG7ey2jgclGz8NpZCi23qZJLxeejPX1VOBywZUKXya5K8TE0j4F9XRbtYzi3xMa22VorQg==
X-Received: by 2002:a62:7883:: with SMTP id
 t125mr2520413pfc.141.1578448222147;
        Tue, 07 Jan 2020 17:50:22 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 w8sm825747pfn.186.2020.01.07.17.50.19
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 07 Jan 2020 17:50:21 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        KarimAllah <karahmed@amazon.de>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Ingo Molnar <mingo@kernel.org>,
        Ankur Arora <ankur.a.arora@oracle.com>
Subject: [PATCH RFC] sched/fair: Penalty the cfs task which executes mwait/hlt
Date: Wed,  8 Jan 2020 09:50:01 +0800
Message-Id: <1578448201-28218-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

To deliver all of the resources of a server to instances in cloud, there are no 
housekeeping cpus reserved. libvirtd, qemu main loop, kthreads, and other agent/tools 
etc which can't be offloaded to other hardware like smart nic, these stuff will 
contend with vCPUs even if MWAIT/HLT instructions executed in the guest.

The is no trap and yield the pCPU after we expose mwait/hlt to the guest [1][2],
the top command on host still observe 100% cpu utilization since qemu process is 
running even though guest who has the power management capability executes mwait. 
Actually we can observe the physical cpu has already enter deeper cstate by 
powertop on host.

For virtualization, there is a HLT activity state in CPU VMCS field which indicates 
the logical processor is inactive because it executed the HLT instruction, but 
SDM 24.4.2 mentioned that execution of the MWAIT instruction may put a logical 
processor into an inactive state, however, this VMCS field never reflects this 
state.

This patch avoids fine granularity intercept and reschedule vCPU if MWAIT/HLT
instructions executed, because it can worse the message-passing workloads which 
will switch between idle and running frequently in the guest. Lets penalty the 
vCPU which is long idle through tick-based sampling and preemption.

Bind unixbench to one idle pCPU:
Dhrystone 2 using register variables            26445969.1  (base)

Bind unixbench and one vCPU which is idle to one pCPU:

Before patch:

Dhrystone 2 using register variables            21248475.1  (80% of base)

After patch:

Dhrystone 2 using register variables            24839863.6  (94% of base)

[1] https://lists.gnu.org/archive/html/qemu-devel/2018-06/msg06794.html
[2] https://lkml.org/lkml/2018/3/12/359

Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: KarimAllah <karahmed@amazon.de>
Cc: Vincent Guittot <vincent.guittot@linaro.org>
Cc: Ingo Molnar <mingo@kernel.org>
Cc: Ankur Arora <ankur.a.arora@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/smp.h      |  1 +
 arch/x86/include/asm/topology.h |  7 ++++++
 arch/x86/kernel/smpboot.c       | 53 ++++++++++++++++++++++++++++++++++++++++-
 kernel/sched/core.c             |  1 +
 kernel/sched/fair.c             | 10 +++++++-
 kernel/sched/features.h         |  5 ++++
 kernel/sched/sched.h            |  7 ++++++
 7 files changed, 82 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v5 1/4] s390x: export sclp_setup_int
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11324023
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4420109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 16:13:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBD6B206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 16:13:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729385AbgAHQN0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jan 2020 11:13:26 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:6746 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729193AbgAHQN0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jan 2020 11:13:26 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 008GCwsU010584
        for <kvm@vger.kernel.org>; Wed, 8 Jan 2020 11:13:25 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xdhch268f-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 08 Jan 2020 11:13:25 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Wed, 8 Jan 2020 16:13:23 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 8 Jan 2020 16:13:20 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 008GDIhO44499236
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 8 Jan 2020 16:13:18 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 91E7EAE045;
        Wed,  8 Jan 2020 16:13:18 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4C60BAE053;
        Wed,  8 Jan 2020 16:13:18 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed,  8 Jan 2020 16:13:18 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v5 1/4] s390x: export sclp_setup_int
Date: Wed,  8 Jan 2020 17:13:14 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200108161317.268928-1-imbrenda@linux.ibm.com>
References: <20200108161317.268928-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20010816-0028-0000-0000-000003CF6031
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20010816-0029-0000-0000-00002493735D
Message-Id: <20200108161317.268928-2-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-08_04:2020-01-08,2020-01-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 clxscore=1015
 mlxscore=0 spamscore=0 priorityscore=1501 impostorscore=0
 lowpriorityscore=0 adultscore=0 malwarescore=0 phishscore=0
 mlxlogscore=999 suspectscore=1 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-1910280000 definitions=main-2001080133
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export sclp_setup_int() so that it can be used in tests.

Needed for an upcoming unit test.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/sclp.h | 1 +
 lib/s390x/sclp.c | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v3] KVM: SVM: Override default MMIO mask if memory encryption is enabled
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11324287
Return-Path: <SRS0=A2Rt=25=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1C49921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 18:40:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AD5BC2067D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jan 2020 18:40:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="PhrqTw3C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726591AbgAHSky (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jan 2020 13:40:54 -0500
Received: from mail-dm6nam10on2054.outbound.protection.outlook.com
 ([40.107.93.54]:54738
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725941AbgAHSky (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jan 2020 13:40:54 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jFQjH/NJXbiBDtqIDY3dyYbglN+fBe9xnunSh3oc7xGU6t0ScGgSL3ynK7X8FDb8DECsW/YZ/lDjftG+ax6pClXgAJ2mVyQrP7Rrux8Ty9IRi9jZAKw0dudljIltB4gkG7w4INFzme2OZ1XWBevlRDpUY18ax3p9oIj//JNAWs4f9lhztEsCjtuRMixWChs1IwTDLSzNkeeQer/iago6rxT/bWScWR8CW8rSsA+8o1hhN57jD8IkCdSrltq0UOGJLNJJZXwTWh6ULr5+hZ7OBXhqIX9B7MbiJp4KrUCnJUv+1BV43WeG4BY2gKbMC3syFHaEFPGQKQZhD1TwVkqoRw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=tGzsz3IV8YFq3xOEnx52bEb4Qddzsj9SnhSRU95OvUo=;
 b=XWIwLyGxwDG3/K+6qtLVvhd0Tz+wIT7pOsZaMqfazA1nVB2QjKV4M5N8YKffw/ZJy/7Ge3MDAGEx+lFJJPbqMU1Q51kqI0RyJbaJ/1iAvVnlgqqHK7XorLg5SZxNlUYMR8Z8FiC4QiHZsuKXWMFcmWu7WS8ij7Da5x9Fk+fCGR3vYiXiGkdJ6+3RXdgljMsgogqXk5xsIGByUVYfaJgccTY4H8Br7OpFU1ccxpKSCQgRnlZrlpvXjumZwDmf8PMMgphPJhR+QodVrGaxoXFJ7qV81VPNkMj2Fsz3LUpW48aNzHfSFrUikceMz+ychtRb99QjlmxH/3umBk9C5K3hog==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=tGzsz3IV8YFq3xOEnx52bEb4Qddzsj9SnhSRU95OvUo=;
 b=PhrqTw3CJSetQ2nKHCVusGY5D1G6k8fblQvZCf6HHs3wqpt222CLO7dmGm1Uv9hUkQdmewyKu3x9lS0L2WY2dbP/WKkPIZlbtA4x7En6JzWMY719EhKpCRwhrqgdPaziZC5MXqk+o598ojbG/rhIr+jlgTrB12gD/LhcN5JYmcU=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.71.154) by
 DM6PR12MB3179.namprd12.prod.outlook.com (20.179.104.210) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2602.12; Wed, 8 Jan 2020 18:40:38 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270%7]) with mapi id 15.20.2602.017; Wed, 8 Jan 2020
 18:40:38 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v3] KVM: SVM: Override default MMIO mask if memory encryption
 is enabled
Date: Wed,  8 Jan 2020 12:40:16 -0600
Message-Id: 
 <6d2b7e37ca4dca92fadd1f3df93803fd17aa70ad.1578508816.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: SN1PR12CA0092.namprd12.prod.outlook.com
 (2603:10b6:802:21::27) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:15e::26)
MIME-Version: 1.0
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN1PR12CA0092.namprd12.prod.outlook.com (2603:10b6:802:21::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2581.12 via Frontend
 Transport; Wed, 8 Jan 2020 18:40:37 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 35b363c4-64e0-44ec-2a73-08d7946a4185
X-MS-TrafficTypeDiagnostic: DM6PR12MB3179:|DM6PR12MB3179:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3179E83617B1A3AA86DADA8AEC3E0@DM6PR12MB3179.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-Forefront-PRVS: 02760F0D1C
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(346002)(396003)(366004)(376002)(136003)(199004)(189003)(6486002)(2616005)(2906002)(4326008)(86362001)(316002)(956004)(5660300002)(54906003)(36756003)(6666004)(7696005)(52116002)(478600001)(16526019)(8676002)(81166006)(186003)(8936002)(81156014)(26005)(66476007)(66556008)(66946007);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3179;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 4v6qukUTdFbQxX7khjK4rC9MTiSxWAzT+u91eJdPpbDwAkwASM2ZWx1PSeU8qSUWKl43IRdyv9buLFlGFUMfIBKE0XyxLffDBpaj9mfVg1bOvZdndAW97OQEAR8wpvdA0853BRC18APGWDz1bbqQKh9+0swGqp4oCuOE5qCYK0o5099RUzkcVlISP1stke59KOslG1kB4Uagv4XsPvaKD+Xtp4Vec/z15mSJsKT0T1XjnZjpczjaPKLKyVKCS7x7U4hWtFeXu03gES4hZ5V4c7dyFtM8GaAaS+CoVbS0PxQcHpSbsWCtr3xx0vOdAJxAAXdW3L5Ab15Z7bMkgkHq+/xiqpJ5M8Wib313soQlQD5TIWy8rzJ8jwbVjYaxfepUBbbBp/ARv5rDzc7JPhui1zszlTzDKgR1du8WgCBAhS1r9kkZCWLUIwnd3Z7famq/
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 35b363c4-64e0-44ec-2a73-08d7946a4185
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 Jan 2020 18:40:38.5033
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 zYRlq0oa/GRlNFskQXHkANVJbvZTTVg0a1DPsKfxY/9hXriJV6dJCETHEM2KiQLyQNDZHcXEbaTBaNvzP6fa+A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3179
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM MMIO support uses bit 51 as the reserved bit to cause nested page
faults when a guest performs MMIO. The AMD memory encryption support uses
a CPUID function to define the encryption bit position. Given this, it is
possible that these bits can conflict.

Use svm_hardware_setup() to override the MMIO mask if memory encryption
support is enabled. Various checks are performed to ensure that the mask
is properly defined and rsvd_bits() is used to generate the new mask (as
was done prior to the change that necessitated this patch).

Fixes: 28a1f3ac1d0c ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Changes in v3:
- Add additional checks to ensure there are no conflicts between the
  encryption bit position and physical address setting.
- Use rsvd_bits() generated mask (as was previously used) instead of
  setting a single bit.

Changes in v2:
- Use of svm_hardware_setup() to override MMIO mask rather than adding an
  override callback routine.
---
 arch/x86/kvm/svm.c | 51 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 51 insertions(+)

```
