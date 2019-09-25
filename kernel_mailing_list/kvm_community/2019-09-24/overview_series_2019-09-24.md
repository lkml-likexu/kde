#### [RFC PATCH 1/2] kvm/arm: add capability to forward hypercall to user space
##### From: Heyi Guo <guoheyi@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Heyi Guo <guoheyi@huawei.com>
X-Patchwork-Id: 11159073
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFB3714ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:22:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE63E217D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:22:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732590AbfIXPWb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 11:22:31 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:46846 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727382AbfIXPWa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 11:22:30 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 3D655AAB33C626A11C05;
        Tue, 24 Sep 2019 23:22:29 +0800 (CST)
Received: from linux-Bxxcye.huawei.com (10.175.104.222) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.439.0; Tue, 24 Sep 2019 23:22:20 +0800
From: Heyi Guo <guoheyi@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <wanghaibin.wang@huawei.com>, Heyi Guo <guoheyi@huawei.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Dave Martin <Dave.Martin@arm.com>,
        Marc Zyngier <marc.zyngier@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>
Subject: [RFC PATCH 1/2] kvm/arm: add capability to forward hypercall to user
 space
Date: Tue, 24 Sep 2019 23:20:53 +0800
Message-ID: <1569338454-26202-2-git-send-email-guoheyi@huawei.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1569338454-26202-1-git-send-email-guoheyi@huawei.com>
References: <1569338454-26202-1-git-send-email-guoheyi@huawei.com>
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.175.104.222]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As more SMC/HVC usages emerge on arm64 platforms, like SDEI, it makes
sense for kvm to have the capability of forwarding such calls to user
space for further emulation.

We reuse the existing term "hypercall" for SMC/HVC, as well as the
hypercall structure in kvm_run to exchange arguments and return
values. The definition on arm64 is as below:

exit_reason: KVM_EXIT_HYPERCALL

Input:
  nr: the immediate value of SMC/HVC calls; not really used today.
  args[6]: x0..x5 (This is not fully conform with SMCCC which requires
           x6 as argument as well, but use space can use GET_ONE_REG
           ioctl for such rare case).

Return:
  args[0..3]: x0..x3 as defined in SMCCC. We need to extract
              args[0..3] and write them to x0..x3 when hypercall exit
              returns.

Flag hypercall_forward is added to turn on/off hypercall forwarding
and the default is false. Another flag hypercall_excl_psci is to
exclude PSCI from forwarding for backward compatible, and it only
makes sense to check its value when hypercall_forward is enabled.

Signed-off-by: Heyi Guo <guoheyi@huawei.com>
Cc: Peter Maydell <peter.maydell@linaro.org>
Cc: Dave Martin <Dave.Martin@arm.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: James Morse <james.morse@arm.com>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Suzuki K Poulose <suzuki.poulose@arm.com>
CC: Russell King <linux@armlinux.org.uk>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: Will Deacon <will@kernel.org>
---
 arch/arm/include/asm/kvm_host.h   |  5 +++++
 arch/arm64/include/asm/kvm_host.h |  5 +++++
 include/kvm/arm_psci.h            |  1 +
 virt/kvm/arm/arm.c                |  2 ++
 virt/kvm/arm/psci.c               | 30 ++++++++++++++++++++++++++++--
 5 files changed, 41 insertions(+), 2 deletions(-)

```
#### [PATCH v6 1/6] vfio: Define device specific irq type capability
##### From: Tina Zhang <tina.zhang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tina Zhang <tina.zhang@intel.com>
X-Patchwork-Id: 11157977
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB2811599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 06:43:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B2DC220665
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 06:43:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2440568AbfIXGnI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 02:43:08 -0400
Received: from mga02.intel.com ([134.134.136.20]:25186 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389156AbfIXGnI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 02:43:08 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Sep 2019 23:43:07 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,543,1559545200";
   d="scan'208";a="203306303"
Received: from gvt.bj.intel.com ([10.238.158.180])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2019 23:43:05 -0700
From: Tina Zhang <tina.zhang@intel.com>
To: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Tina Zhang <tina.zhang@intel.com>, kraxel@redhat.com,
        zhenyuw@linux.intel.com, zhiyuan.lv@intel.com,
        zhi.a.wang@intel.com, kevin.tian@intel.com, hang.yuan@intel.com,
        alex.williamson@redhat.com, yi.l.liu@intel.com,
        Eric Auger <eric.auger@redhat.com>
Subject: [PATCH v6 1/6] vfio: Define device specific irq type capability
Date: Tue, 24 Sep 2019 14:41:38 +0800
Message-Id: <20190924064143.9282-2-tina.zhang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190924064143.9282-1-tina.zhang@intel.com>
References: <20190924064143.9282-1-tina.zhang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cap the number of irqs with fixed indexes and use capability chains
to chain device specific irqs.

v2:
- Irq capability index starts from 1.

Signed-off-by: Tina Zhang <tina.zhang@intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 include/uapi/linux/vfio.h | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/8] hw/i386: Factorize PVH related functions
##### From: Sergio Lopez <slp@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sergio Lopez <slp@redhat.com>
X-Patchwork-Id: 11158637
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0363D1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 12:45:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD37E2168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 12:45:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395313AbfIXMpL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 08:45:11 -0400
Received: from mx1.redhat.com ([209.132.183.28]:44890 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2395292AbfIXMpL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 08:45:11 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id CE74030860CB;
        Tue, 24 Sep 2019 12:45:10 +0000 (UTC)
Received: from dritchie.redhat.com (unknown [10.33.36.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8135160852;
        Tue, 24 Sep 2019 12:45:04 +0000 (UTC)
From: Sergio Lopez <slp@redhat.com>
To: qemu-devel@nongnu.org
Cc: mst@redhat.com, imammedo@redhat.com, marcel.apfelbaum@gmail.com,
        pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        philmd@redhat.com, lersek@redhat.com, kraxel@redhat.com,
        mtosatti@redhat.com, kvm@vger.kernel.org,
        Sergio Lopez <slp@redhat.com>
Subject: [PATCH v4 1/8] hw/i386: Factorize PVH related functions
Date: Tue, 24 Sep 2019 14:44:26 +0200
Message-Id: <20190924124433.96810-2-slp@redhat.com>
In-Reply-To: <20190924124433.96810-1-slp@redhat.com>
References: <20190924124433.96810-1-slp@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Tue, 24 Sep 2019 12:45:10 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Extract PVH related functions from pc.c, and put them in pvh.c, so
they can be shared with other components.

Signed-off-by: Sergio Lopez <slp@redhat.com>
---
 hw/i386/Makefile.objs |   1 +
 hw/i386/pc.c          | 120 +++++-------------------------------------
 hw/i386/pvh.c         | 113 +++++++++++++++++++++++++++++++++++++++
 hw/i386/pvh.h         |  10 ++++
 4 files changed, 136 insertions(+), 108 deletions(-)
 create mode 100644 hw/i386/pvh.c
 create mode 100644 hw/i386/pvh.h

```
#### [PATCH] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11159117
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A2FC13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:30:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7896521783
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 15:30:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389574AbfIXPao (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 11:30:44 -0400
Received: from mga18.intel.com ([134.134.136.126]:47824 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389524AbfIXPao (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 11:30:44 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Sep 2019 08:30:43 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,544,1559545200";
   d="scan'208";a="195727916"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by FMSMGA003.fm.intel.com with ESMTP; 24 Sep 2019 08:30:42 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
Date: Tue, 24 Sep 2019 23:32:50 +0800
Message-Id: <20190924153250.20315-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The control bits in IA32_XSS MSR are being used for new features,
but current CPUID(0xd,i) enumeration code doesn't support them, so
fix existing code first.

The supervisor states in IA32_XSS haven't been used in public
KVM code, so set KVM_SUPPORTED_XSS to 0 now, anyone who's developing
IA32_XSS related feature may expand the macro to add the CPUID support,
otherwise, CPUID(0xd,i>1) always reports 0 of the subleaf to guest.

Extracted old code into a new filter and keep it same flavor as others.

This patch passed selftest on a few Intel platforms.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            | 94 +++++++++++++++++++++------------
 arch/x86/kvm/svm.c              |  7 +++
 arch/x86/kvm/vmx/vmx.c          |  6 +++
 arch/x86/kvm/x86.h              |  7 +++
 5 files changed, 82 insertions(+), 33 deletions(-)

```
#### [PATCH] kvm: x86: Enumerate support for CLZERO instructionFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11159587
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04CE114ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 20:51:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9D1E214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 20:51:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="UJEfQGqx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388292AbfIXUvO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 16:51:14 -0400
Received: from mail-pg1-f201.google.com ([209.85.215.201]:39335 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731288AbfIXUvN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 16:51:13 -0400
Received: by mail-pg1-f201.google.com with SMTP id t19so2069292pgh.6
        for <kvm@vger.kernel.org>; Tue, 24 Sep 2019 13:51:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=cK0rz6GPB8sFkc3B+fwwxTP1+0Eh134HuJh0fwsbwJg=;
        b=UJEfQGqxAA6lLw1NEwRj33/BhnUqc6DRlpLj4yz+I+mQaomwE6CDA6TqoPJ9XGQuOF
         yy/B9uXMuXxEP0X+IL+rciL8EHjdTBX44eFYmun9ZqIYl8466kRzd2da9gC4IbRSwElz
         CRcg16dVaGWccDBdmeWnQ8CDGUXTA8DmmrzyZ3DZgv1JqAxB718KxjTR9XBJsvyl7VS1
         nRfFFa2UqLqk1hYSQD1EPywlLRmWXk4rUe1FTGL28OKMnBM0mSNP8Z4+AVqYfST2oeFm
         sxPAzRZoXY9fHs0y0kPEAjQl8BFB5YWaZEgXLeBCxuGmM54RHo+hmptlSXPVqfRxhlFd
         kEcA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=cK0rz6GPB8sFkc3B+fwwxTP1+0Eh134HuJh0fwsbwJg=;
        b=M2GQVtEIP6iqy9CrmMCL79Ar8K0Y/fR0lr0SckVvVBzPMbtz5q7XdHOpPDUoj3RoJJ
         Oqx8CYbDEFX6ELG2bRhJdN651TVRBeTZ+2J42G+R5MBF+XYiLYz0Uv5PgTzDqOfwEGVA
         qBcG5i69CS1Wk/fg7nQMygZxaEIs5cqM5VaanuSJXKbnPSicEta+s6Up8kwhwz190AbV
         ZJIk4VNXd9kchhaJv8PiEyC0U6rMWBsMyFmtiv2ECFuMGkMJFKbH/fSkHSH2q8lwOBqC
         dcx9qRPpHtwiTo+/FJPDfx8EZtt2Xzrrm1TlNK9k6RM8s2faYvi4lYBmPrxmzo7hLXqo
         KuIQ==
X-Gm-Message-State: APjAAAWQD3iMy5btbH1OOdvKdQmgWyJgQiHsZHYwLP99vrVuMbPYVJ6u
        fT/Wco/srHfd1IA7eAy55+oVpJKzJifct7tzvcSzJ3QVfxaOOwljFfnhD/mvhCUtGyn/stzz7ew
        Fu8TGGAYIzRJ02BpBBtHEmjWIqa5H2969vaDOmxa8Zsr+jTTt2hbpbvxlqv+9hAs=
X-Google-Smtp-Source: 
 APXvYqxXsQDeUlr1+fAdznIO2UuQLxYD1je6XT/Xaj6VskWVdZaj6xldEmjZ58rZGoFPMTNOAtb3f7/RvMSbTg==
X-Received: by 2002:a63:d60:: with SMTP id 32mr4984367pgn.316.1569358272664;
 Tue, 24 Sep 2019 13:51:12 -0700 (PDT)
Date: Tue, 24 Sep 2019 13:51:08 -0700
Message-Id: <20190924205108.241657-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [PATCH] kvm: x86: Enumerate support for CLZERO instruction
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Jim Mattson <jmattson@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CLZERO is available to the guest if it is supported on the
host. Therefore, enumerate support for the instruction in
KVM_GET_SUPPORTED_CPUID whenever it is supported on the host.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH V2 1/8] vringh: fix copy direction of vringh_iov_push_kern()
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11158871
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DCB8617D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 13:54:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C5B06214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 13:54:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441178AbfIXNyc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 09:54:32 -0400
Received: from mx1.redhat.com ([209.132.183.28]:60834 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2441151AbfIXNyc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 09:54:32 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7D05A796ED;
        Tue, 24 Sep 2019 13:54:31 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-44.pek2.redhat.com [10.72.12.44])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 220B75B6A5;
        Tue, 24 Sep 2019 13:54:09 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V2 1/8] vringh: fix copy direction of vringh_iov_push_kern()
Date: Tue, 24 Sep 2019 21:53:25 +0800
Message-Id: <20190924135332.14160-2-jasowang@redhat.com>
In-Reply-To: <20190924135332.14160-1-jasowang@redhat.com>
References: <20190924135332.14160-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.25]);
 Tue, 24 Sep 2019 13:54:31 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to copy from iov to buf, so the direction was wrong.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vringh.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH] selftests: kvm: Fix libkvm build error
##### From: Shuah Khan <skhan@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shuah Khan <skhan@linuxfoundation.org>
X-Patchwork-Id: 11159535
Return-Path: <SRS0=xKXW=XT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3411814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 20:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 12131214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Sep 2019 20:15:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1569356104;
	bh=PIr3J2WXwkx+wpU0dlBJzmksVzKJERCXc7/EfKF5olI=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=DVzOByBHjSTViq5Yv/L1HiV0wR04GqHBOpwEboM963mpZjbpt2mrmAT8YItw0y2IW
	 wRnSxWci5bH16JqheEh6MvTsAR09ypzBqqBQFWDveVntLq/VJMvGnwIH0h5TDcNeOS
	 OP/hwVGq1GCp/dVKnFMH+KXNsyRoL7MTmzxqaZfU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726254AbfIXUPB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 16:15:01 -0400
Received: from mail-io1-f65.google.com ([209.85.166.65]:44549 "EHLO
        mail-io1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732269AbfIXUPB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 16:15:01 -0400
Received: by mail-io1-f65.google.com with SMTP id j4so7604831iog.11
        for <kvm@vger.kernel.org>; Tue, 24 Sep 2019 13:15:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linuxfoundation.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=DI0egddMaTlmXPpI6j4ITK90qBcGxWnZ/Lc990IvF2Y=;
        b=JTMndQ+nYpdyNF5MJOGWUHZv+QevSaM0HzuyG4IdtM+xtvoSK1XA6X5CBcgkwcsFmA
         3GUTDUHSWAunyQPQX5jfxq+rvzj+h6POMg142essaWiGeLpd6xri8wEzS2VNPNctGHcg
         +xxXg9XTK7XRkzjGWbajAgkQlVoz2vQx7NuKI=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=DI0egddMaTlmXPpI6j4ITK90qBcGxWnZ/Lc990IvF2Y=;
        b=a8VSIe7inf0shLOtOBtLKnAtiSFBpTJDwvO5ue0sxm2mi5dDWu/lcaZp4YryScK5gM
         b8Pn6whRr9dLxSipcTZY2YuAoCnK41mTukMbMO4875NiPzzt5x/cUaWo67Q1hk6VUln1
         ArSVF6uERgbFqilYxKB9c0Aez95ovJaTxfvmoogFufgZcmetHvRjucl7QRN+cwdqQigC
         CncsE6pr3fVde7+Y3I1/dXCXOmchzsrEp2JKhvRgATQbLhfb5Z7Vtwe7s336jYPKc2C2
         2SEowzH64meC7s/SD9vE43HVzCfENYtgKRy/oeCUbDDx6NRiKKspyoniAGworMbjfM+W
         bWwg==
X-Gm-Message-State: APjAAAVKopMId+pA6RZsIpVzfX/fKyQK/lLQ8HTWcYM9/x9YS/GYyLbj
        qes+bM5lOJNqiGYd3Beu/YmI2w==
X-Google-Smtp-Source: 
 APXvYqxn6tRAr9RxU9eibq7Mfj2KW3OBHKsrpfR/gHKH+DusHXd6HU+er1lZb6yRz3aWg8YmGuURRw==
X-Received: by 2002:a02:cd8d:: with SMTP id l13mr744030jap.138.1569356100138;
        Tue, 24 Sep 2019 13:15:00 -0700 (PDT)
Received: from shuah-t480s.internal (c-24-9-64-241.hsd1.co.comcast.net.
 [24.9.64.241])
        by smtp.gmail.com with ESMTPSA id
 b24sm2007733iob.2.2019.09.24.13.14.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 24 Sep 2019 13:14:59 -0700 (PDT)
From: Shuah Khan <skhan@linuxfoundation.org>
To: pbonzini@redhat.com, rkrcmar@redhat.com, shuah@kernel.org
Cc: Shuah Khan <skhan@linuxfoundation.org>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] selftests: kvm: Fix libkvm build error
Date: Tue, 24 Sep 2019 14:14:51 -0600
Message-Id: <20190924201451.31977-1-skhan@linuxfoundation.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following build error:

libkvm.a(assert.o): relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a PIE object; recompile with -fPIC

Add -fPIC to CFLAGS to fix it.

Signed-off-by: Shuah Khan <skhan@linuxfoundation.org>
---
 tools/testing/selftests/kvm/Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
