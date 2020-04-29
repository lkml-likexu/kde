

#### [PATCH 0/3] KVM: x86/mmu: Use kernel's PG_LEVEL_* enums
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Apr 28 00:54:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11513543
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA6D314B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:54:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA88E2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 00:54:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726335AbgD1AyX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 20:54:23 -0400
Received: from mga05.intel.com ([192.55.52.43]:42479 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726263AbgD1AyX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 20:54:23 -0400
IronPort-SDR: 
 gsMD55yMjEWbZ8fYZbBny4aLLBGzT+ECLwt+Q4tuuWvovupcIPNPYHUr98ZLlq6lBxgS+66gs5
 PdYXVFRWiZEQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Apr 2020 17:54:23 -0700
IronPort-SDR: 
 JQc3L9gG3VS4FzygtcdMVJkwfH3re0P7lqJ0dd+sbvkg+lU+h6U12rlxgp/ISB1DbRQuLCenlT
 w1W8bT4J7AFA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,325,1583222400";
   d="scan'208";a="260920803"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 27 Apr 2020 17:54:23 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Barret Rhoden <brho@google.com>
Subject: [PATCH 0/3] KVM: x86/mmu: Use kernel's PG_LEVEL_* enums
Date: Mon, 27 Apr 2020 17:54:19 -0700
Message-Id: <20200428005422.4235-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop KVM's PT_{PAGE_TABLE,DIRECTORY,PDPE}_LEVEL KVM enums in favor of the
kernel's PG_LEVEL_{4K,2M,1G} enums, which have far more user friendly
names.

The KVM names were presumably intended to abstract away the page size.  In
practice, the abstraction is only useful for a single line of code, a PSE
paging related large page check.  For everything else, the abstract names
do nothing but obfuscate the code.

Boot tested a PSE kernel under 32-bit KVM and 64-bit KVM, with and without
EPT enabled.  Patches 2 and 3 generate no binary difference relative to
patch 1 when compared via "objdump -d".

Sean Christopherson (3):
  KVM: x86/mmu: Tweak PSE hugepage handling to avoid 2M vs 4M conundrum
  KVM: x86/mmu: Move max hugepage level to a separate #define
  KVM: x86/mmu: Drop KVM's hugepage enums in favor of the kernel's enums

 arch/x86/include/asm/kvm_host.h |  13 +---
 arch/x86/kvm/mmu/mmu.c          | 118 +++++++++++++++-----------------
 arch/x86/kvm/mmu/page_track.c   |   4 +-
 arch/x86/kvm/mmu/paging_tmpl.h  |  18 ++---
 arch/x86/kvm/mmu_audit.c        |   6 +-
 arch/x86/kvm/svm/svm.c          |   2 +-
 arch/x86/kvm/vmx/vmx.c          |   6 +-
 arch/x86/kvm/x86.c              |   4 +-
 8 files changed, 79 insertions(+), 92 deletions(-)
Reviewed-by: Barret Rhoden <brho@google.com>
```
#### [PATCH v4 0/7] KVM: VMX: Tscdeadline timer emulation fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Tue Apr 28 06:23:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11513885
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E01214DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:23:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 851C6206D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 06:23:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bT0f3Lxw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726338AbgD1GXk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 02:23:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42648 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726042AbgD1GXk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Apr 2020 02:23:40 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0E0A0C03C1A9;
        Mon, 27 Apr 2020 23:23:40 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id w65so10167644pfc.12;
        Mon, 27 Apr 2020 23:23:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=Rg/qLxiNVWfFmoRhGooaCspQ06LzLm65xMpP+49aITo=;
        b=bT0f3LxwO8Wi5DI7F28YPePPQo3wDrPpjG6Z7eWzzlW/9SesYyzKkuW37K9Au8//he
         TJydnm3o0UhAtfOXKz+cx0hcQ/z6U2WJjWrGTvkX4fdfdIGH3NEg6JMIlwGW6nZtD2/I
         fVRRAkox95aPwbuubMx74r+vjBUspp77S7AMj3mYFzzd0PYf3o+kHkcxleB7oJeU26NV
         yztRJNbOwq+j/3VsdsxLt/qzuyHTnGH3xj+rZJgbR2QMk2TpVjMqcKF2M+8HKMNmWPzB
         vNOcOew2+OqmKPHvcKdAD788A8XoYm404jF82NdVvWnwGTUJUT7QmR7jzQyNoNJD2LR2
         KQhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=Rg/qLxiNVWfFmoRhGooaCspQ06LzLm65xMpP+49aITo=;
        b=U7kslQhYc31FKrp9SenphdbWtkb5gwcz4pURCzQMAW8+FNud2L9rhJw8O9Mp8n4LSe
         6p6n84dOnbqcSo/m6iqn/aSHEmibHd1KiWzOgB68gHc2pP80pJ3OI4fJZ2qv+kPUqopq
         Ef/LxRck+L4UzHvgHS1340py2Vi1ELAnB3EpWlXdb1dq+NXwrbsgz6W6oeForpe15C+8
         AG0q36iCL0cQrJxMbr/IRVYB30TCfMKTRhONZOtNNXOfBEaVTEauAlWeEe49tseR2jPk
         47Nhe09me+CWSSlklzitzWOBEMi+OzfAP9tBP75Kgya1UtaVaCRV1YiA3mt4qwCTOfEY
         zCjA==
X-Gm-Message-State: AGi0PuaKwRk5cF3IEUS36AX5iA38EI+ZS9zz/QNkkQudtQVAvPVj1EIM
        xpMvSNDdWBF7bwiV7O3Qz52b0Php
X-Google-Smtp-Source: 
 APiQypKx447iCNYPNvDT17BVFLgzVIFOyg3nZ+i5OqMFjvdBwiERmw/EydV78/66W3kQT5sqS2DBWQ==
X-Received: by 2002:a62:e80e:: with SMTP id c14mr27294464pfi.83.1588055019397;
        Mon, 27 Apr 2020 23:23:39 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 u188sm14183071pfu.33.2020.04.27.23.23.36
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 27 Apr 2020 23:23:38 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v4 0/7] KVM: VMX: Tscdeadline timer emulation fastpath
Date: Tue, 28 Apr 2020 14:23:22 +0800
Message-Id: <1588055009-12677-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IPI and Timer cause the main vmexits in cloud environment observation, 
after single target IPI fastpath, let's optimize tscdeadline timer 
latency by introducing tscdeadline timer emulation fastpath, it will 
skip various KVM related checks when possible. i.e. after vmexit due 
to tscdeadline timer emulation, handle it and vmentry immediately 
without checking various kvm stuff when possible. 

Testing on SKX Server.

cyclictest in guest(w/o mwait exposed, adaptive advance lapic timer is default -1):

5540.5ns -> 4602ns       17%

kvm-unit-test/vmexit.flat:

w/o avanced timer:
tscdeadline_immed: 3028.5  -> 2494.75  17.6%
tscdeadline:       5765.7  -> 5285      8.3%

w/ adaptive advance timer default -1:
tscdeadline_immed: 3123.75 -> 2583     17.3%
tscdeadline:       4663.75 -> 4537      2.7%

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>

v3 -> v4:
 * fix bad indentation
 * rename CONT_RUN to REENTER_GUEST
 * rename kvm_need_cancel_enter_guest to kvm_vcpu_exit_request
 * rename EXIT_FASTPATH_CONT_RUN to EXIT_FASTPATH_REENTER_GUEST 
 * introduce EXIT_FASTPATH_NOP 
 * don't squish several stuffs to one patch
 * REENTER_GUEST be introduced with its first usage
 * introduce __handle_preemption_timer subfunction

v2 -> v3:
 * skip interrupt notify and use vmx_sync_pir_to_irr before each cont_run
 * add from_timer_fn argument to apic_timer_expired
 * remove all kinds of duplicate codes

v1 -> v2:
 * move more stuff from vmx.c to lapic.c
 * remove redundant checking
 * check more conditions to bail out CONT_RUN
 * not break AMD
 * not handle LVTT sepecial
 * cleanup codes

Wanpeng Li (7):
  KVM: VMX: Introduce generic fastpath handler
  KVM: X86: Enable fastpath when APICv is enabled
  KVM: X86: Introduce more exit_fastpath_completion enum values
  KVM: X86: Introduce kvm_vcpu_exit_request() helper
  KVM: VMX: Optimize posted-interrupt delivery for timer fastpath
  KVM: X86: TSCDEADLINE MSR emulation fastpath
  KVM: VMX: Handle preemption timer fastpath

 arch/x86/include/asm/kvm_host.h |  3 ++
 arch/x86/kvm/lapic.c            | 18 +++++++----
 arch/x86/kvm/svm/svm.c          | 11 ++++---
 arch/x86/kvm/vmx/vmx.c          | 66 +++++++++++++++++++++++++++++++++--------
 arch/x86/kvm/x86.c              | 44 ++++++++++++++++++++-------
 arch/x86/kvm/x86.h              |  3 +-
 virt/kvm/kvm_main.c             |  1 +
 7 files changed, 110 insertions(+), 36 deletions(-)
```
#### [PATCH v12 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Tue Apr 28 07:32:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11513971
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 938461392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 07:33:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 66590206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 07:33:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="ZS+ifRL3";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="aUAy1nUQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726508AbgD1Hdr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 03:33:47 -0400
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:57139 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726253AbgD1Hdq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Apr 2020 03:33:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1588059265; x=1619595265;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=K2ObMqTtR+ub5JWRiFnyxSpi8EEPvM1ecrOMfRGOYT4=;
  b=ZS+ifRL3yvaNWOpyf+KboBQnwbWUOuGBfdnTAXaeqFlfuL5NY1DlTfiK
   fbvuWbgt+PQ3289I8s3Usj2NrJTd2UKhcvQsqgHKkhAhy3rHA/6CVnMJY
   K6K9icqAWNnfBrcpojIQHcvsxORuwPwXiKu3Ve8auEe+dZuLmy7mq6HSM
   pqC7E34hJaT4xTbvyipbjGcgIQfB39I5ZnwFybKbLmfhovlhR1wC+sE3R
   rO7Jk2O9o6Jiz9yXab81jrrewE8QCUQGmrkFox8tUsgCkX4Xb+ZgGWf8g
   gDVg0QIhem4zl37N+3xqfWKSceHJyNUoRTfrszG9Ddalyp/1rP/5eSW3n
   g==;
IronPort-SDR: 
 6UOk4dP4EPmb/mS4lgz3/GEtQlRG4uo6dAv7Ev2F9EthIgu3bfzGOEcJ1WOHMcPLr1YjIy9wMr
 hVWbgEfH4YQOmnQeoC+zhNSmjlxYpFTmiNHxklZr7/ZUOEWbiEkIMRlCfTTEguy7IrETIbOaW6
 eH76IPBub5DKTRi5s47LjJWu1uOfDX9XlEvAAQBvGpLmiJXxDlZdhDoPgkGnzciP+YuineivMB
 +JSXwV8SlUphzbiCEwEPvmpFpKX7jDptZQfhlWiy+zgRn3Z3XHgMjK8ZIR9kut+WrLV+VJdDZk
 AKM=
X-IronPort-AV: E=Sophos;i="5.73,327,1583164800";
   d="scan'208";a="238865785"
Received: from mail-co1nam04lp2052.outbound.protection.outlook.com (HELO
 NAM04-CO1-obe.outbound.protection.outlook.com) ([104.47.45.52])
  by ob1.hgst.iphmx.com with ESMTP; 28 Apr 2020 15:34:22 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jzQGpuTYgtoXhT+sEz1q9o+dJd28lSU/s8nbddhTyItKcCoosjvVmXPaDXlOKGn3C91MFROPWvvXo2IzSw4LUVfIaTMYJvSWxQomM1m3hZA5c88J96/Hmq56DT4ebO+FzSFJxhPQehz/nxHVvKw04hVN0Vsc8H3oqXaElvuKtvHrc+7sqA0qHB51dPRO3hFMnCtCIQSHZcZYysStYd2mvGYtvpY1XQKaBqWXWDNrSYLZzysvxq5xBlG7eCmRqWNd9yvziMIz5/2m4dfwRSSaCk/wAfY7JI06xTuvFuQzbPbuaKfeNHvo2UUve6hbri1zI7ktsPZJEX3tB6fqTT/92Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=piwHsz7eOuE/EHPtZVN3i3H74CFot424Bo5imRr8R34=;
 b=dfHqWji5vZXEwUvkLmPs3O+qvAehfEEeJqPTvwm7j12l9+24CvAlE3gW/A8lzvn/HT7VbeLE/Dm56Fw0BUvtn3X1UyORK9+ISqGG78j1C3vcmnHBPbkfrajcDA6QwkzTqQzD9dGYInB4CQhngUn/YcEKZJ289VSykUvGlwpGrGbaWgArXrmf/5FNYi16K6psu7aXCD4/+9sPevfcKQXSkGPOKCvNIoW5YedppVU19HpPkTDz+fpKuwJCoL3SpQNyFJrsWnNKUQzVATb0iZNFmMzXZfwZcOPBs2x2A1oOGczxQSiIJt5ReJKfj/TlvTx5W/KaQwvhkXezZB+aukI23A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=piwHsz7eOuE/EHPtZVN3i3H74CFot424Bo5imRr8R34=;
 b=aUAy1nUQteb95ksZNPVjCskhd9Xo7fn5LgiQS8GPMzwbkQaPKzPnxIDWXdI0R4nqdgmBKviTuNpaLUsKFdbqFw5ruWENbYYkbmWigojf5TxFbrj8jyFsESy7C6LGJw3E/lrOzBnIJ3SGO71SrY6p51CVI/a6dYjgCia+9BldNuk=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB4538.namprd04.prod.outlook.com (2603:10b6:5:21::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.22; Tue, 28 Apr
 2020 07:33:43 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0%5]) with mapi id 15.20.2937.023; Tue, 28 Apr 2020
 07:33:43 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v12 00/17] KVM RISC-V Support
Date: Tue, 28 Apr 2020 13:02:55 +0530
Message-Id: <20200428073312.324684-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: MAXPR01CA0073.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:49::15) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (106.51.31.156) by
 MAXPR01CA0073.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:49::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.19 via Frontend
 Transport; Tue, 28 Apr 2020 07:33:38 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [106.51.31.156]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c1bd5aaf-8719-41e6-490f-08d7eb467a79
X-MS-TrafficTypeDiagnostic: DM6PR04MB4538:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB45385629BC6BBE3638437D7B8DAC0@DM6PR04MB4538.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:133;
X-Forefront-PRVS: 0387D64A71
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(136003)(396003)(346002)(376002)(55016002)(6666004)(1006002)(8886007)(55236004)(956004)(2906002)(966005)(1076003)(2616005)(44832011)(86362001)(8676002)(5660300002)(16526019)(7416002)(478600001)(36756003)(66476007)(54906003)(26005)(186003)(4326008)(43170500005)(110136005)(66946007)(66556008)(8936002)(7696005)(316002)(52116002)(81156014)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 B9Nagv9jPhduMZSJsV/NMV4NavqqS5AX3iebDyKPJ96tDA7x6cACdBkEvCblrJH7vLIcgTF2itvUEER0G9bFFrFsBTgFyF6aCqZrBPtiENDF0vsbDTn29K31V2oLj8ig0nykscw6mvXqWx4dKs0Nu1HiqKY9joDvIXD09zSe2DLAxGWabIlBsDabp/CN18KG6MHZCITGzSt+smvNs/82xAsmLKJj2suOLGPoXRt/kogGnYAaJyq/qtllOYPV2AM85UAb7ZDRS8KiPiepxqzLVNIF2SCubH6wDKI8+OnrZmZxa59bqkyIZ7duTX+9aicsrbVhJx7fqfga3PWTN79iwKZr340CtAbo30QBwQ6DuzU71nejZZqMWH2NVj97yBMxdKph0vCCaMxKrRDa8ai8B5t0SRza2YCn4q/6X0RSmkO/5fuP0jkF4Zw0AGWnu6i1XRG+D8m7bZsK+90Ih4nUhhmx3SRxGM7AsRZnqOFjWKZEJB3xI+MraggZpEVOVWn+SUBAIpopsPszwskf85T9WskuZwmI+WIzyt8dBhA3LCBJ6BTfB/AqJIRXw36mGaB9jbsV3edcic63eVPkf/mXWsv+vuV8cd3fTWAoITOEwY0=
X-MS-Exchange-AntiSpam-MessageData: 
 /TfhKQ+Q40xZztxOzCP0sekXDWKRZTkrO16iBwNjllxXaXHOPXoFX3vFBgS6/J51fDHx9uAaL8m7KFGBfMjABH7nTMP9AWh4BgDnY3eR3jDwNGOa+EcwGjTg2jVH/OMI+ivTGKmUH3btWGYivaAZTC2bL0d8bjLr4pg+gCes5SnUzgSoSd3TzoaUQHWVFwGEZXXjZx8UOjfpf+KNlbciofNeurKgfLC3TD7H3OabTbrXW07OJHQodP3ciJ1neTwQba9La8MD+Ph79bKQJy2/EFiZB9GQ/IBrFIlG89gCpL7JokkvQTGUrybX4KnhDGDHQI8CLjC1tvFnMtqwOUMv7br28bPROB+3DFgrrEE4jUvtOg4f8RHa4m2ke8/1ZHMMaYcuoCGzKxrxnGmqmShQJP/fRoj4Z2Lb2aqJmnw/tGUrI6WWi1SCmyWizdYHyzKNXZUiWr3X+v2u18p0Yg9sFqgdwcCXWRIVadxvJAnDZRjfz1T2RHOnw5ZVnApVc/oY3/CRXPGhWdP+x/GBI2uUk5PWONDAv19EG7TpPEDTTahHxalERL21L3DOqB/E2AJue4ldsPptK1t4a9KrTdfYG5D4oLubAcClZ6rINMOcgPaU0ZWnL6FXBzXnK41z6E3Lfrm8aKo2AmvCFudki99b5D4W4JUOtd1zMfG5YJgwFn5oBRP/4esYVbRuAjRKXcv/A3UX45+GBZ4c6I/QA8jmjbSCd3fj34anWYbpnXXD5Y9EKvh4Zr38ndfEh7viOjM7ST9iJ4Q7GImnOvT2S/zfy+nEIC2raB80pQI9+CCaX6I=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c1bd5aaf-8719-41e6-490f-08d7eb467a79
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 Apr 2020 07:33:43.2890
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 F1Tk+cWX6rw6H8ylr8oEp3PBlPYEOGpDnzv1KdOLRRYqDyA5W36rUzcgjEAkBQI1oALb8/u9N2rjWpi0v7vb8g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB4538
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.
9. Forward unhandled SBI calls to KVM userspace.
10. Hugepage support for Guest/VM

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v12 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v3 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/anup/riscv-hyp-ext-v0.6 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
- Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
- Removed PATCH1, PATCH3, and PATCH20 because these already merged
- Use kernel doc style comments for ISA bitmap functions
- Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
  be added in-future
- Mark KVM RISC-V kconfig option as EXPERIMENTAL
- Typo fix in commit description of PATCH6 of v7 series
- Use separate structs for CORE and CSR registers of ONE_REG interface
- Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
- Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
- No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
- Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
- Added defines for checking/decoding instruction length
- Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
- Rebased patches on Linux-5.3-rc7
- Added "return_handled" in struct kvm_mmio_decode to ensure that
  kvm_riscv_vcpu_mmio_return() updates SEPC only once
- Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
- Updated git repo URL in MAINTAINERS entry

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          | 193 ++++-
 MAINTAINERS                             |  11 +
 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/include/asm/csr.h            |  85 ++
 arch/riscv/include/asm/kvm_host.h       | 272 +++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  44 ++
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 127 +++
 arch/riscv/kernel/asm-offsets.c         | 154 ++++
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  97 +++
 arch/riscv/kvm/mmu.c                    | 775 ++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  43 +
 arch/riscv/kvm/vcpu.c                   | 996 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 654 ++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 172 ++++
 arch/riscv/kvm/vcpu_switch.S            | 391 ++++++++++
 arch/riscv/kvm/vcpu_timer.c             | 225 ++++++
 arch/riscv/kvm/vm.c                     |  86 ++
 arch/riscv/kvm/vmid.c                   | 120 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   8 +
 25 files changed, 4521 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [PATCH v3 00/75] x86: SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Tue Apr 28 15:16:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11514997
Return-Path: <SRS0=1gOX=6M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85C421575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:25:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F3E6206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Apr 2020 15:25:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727969AbgD1PRq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Apr 2020 11:17:46 -0400
Received: from 8bytes.org ([81.169.241.247]:37248 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727875AbgD1PRp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Apr 2020 11:17:45 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 3C9966A7; Tue, 28 Apr 2020 17:17:42 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v3 00/75] x86: SEV-ES Guest Support
Date: Tue, 28 Apr 2020 17:16:10 +0200
Message-Id: <20200428151725.31091-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

here is the next version of changes to enable Linux to run as an SEV-ES
guest. The code was rebased to v5.7-rc3 and got a fair number of changes
since the last version.

What is SEV-ES
==============

SEV-ES is an acronym for 'Secure Encrypted Virtualization - Encrypted
State' and means a hardware feature of AMD processors which hides the
register state of VCPUs to the hypervisor by encrypting it. The
hypervisor can't read or make changes to the guests register state.

Most intercepts set by the hypervisor do not cause a #VMEXIT of the
guest anymore, but turn into a VMM Communication Exception (#VC
exception, vector 29) inside the guest. The error-code of this exception
is the intercept exit-code that caused the exception.  The guest handles
the #VC exception by communicating with the hypervisor through a shared
data structure, the 'Guest-Hypervisor-Communication-Block'.

With SEV-ES an untrusted hypervisor can no longer steal secrets from a
guest via inspecting guest memory or guest register contents. A
malicious hypervisor can still interfere with guest operations, but the
SEV-ES client code does its best to detect such situations and crash the
VM if it happens. 

More information about the implementation details can be found in the
cover letter of the initial post of these patches:

	https://lore.kernel.org/lkml/20200211135256.24617-1-joro@8bytes.org/

Current State of the Patches
============================

The patches posted here are considered feature complete and survived a
good amount of functional testing:

	1) Booting an SEV-ES guest VM to the graphical desktop.

	2) Running a 16-vcpu SEV-ES VM with 'perf top' and the x86
	   selftests shipped with the kernel source in a loop in
	   parallel for 18 hours showed no issues.

	3) Various compile testing has been done, including
	   allno/allmod/allyes/defconfig for x86-64 and i386.

	4) Compiled every single commit (single .config only) to check
	   if they build and do not introduce new warnings.

	5) Boot-tested the changes on various machines, including
	   bare-metal on an AMD (with and without mem_encrypt=on) and
	   Intel machine.

A git-tree with these patches applied can be found here:

	https://git.kernel.org/pub/scm/linux/kernel/git/joro/linux.git/log/?h=sev-es-client-v5.7-rc3

Changes to the previous version
===============================

Here is an incomplete list of changes to the previous version of this
patch-set. There have been so many small changes that I havn't kept
track of all, but the most important ones are listed:


	- Rebased to v5.7-rc3

	- Changes the #VC exception handler to use an IST stack. This
	  includes a couple of additional patches to set up and map the
	  IST stack, to make dumpstack aware of them and to fix a race
	  with the NMI handler when shifting the #VC handlers IST entry.

	- The NMI_Complete message to the hypervisor the re-open the NMI
	  window is now sent at the very beginning of do_nmi().

	- The GHCB used in the pre-decompression code is now re-mapped
	  encrypted and flushed from the cache before jumping to the
	  decompressed kernel image. This is needed to make sure the
	  running kernel can safely re-use the page. Actually the page
	  is also unmapped after being re-encrypted to catch any
	  use-after-remap.

	- Added CPUID caching.

	- Mapped the GHCBs to the EFI page-tables as the UEFI BIOS
	  expects to be able to re-use the OS GHCBs.

	- RDTSC and RDTSCP are now also handled in the pre-decompression
	  boot code. These instructions are used by KASLR and some
	  hypervisors might intercept them.

	- Re-implemented nested GHCB handling by keeping a backup GHCB
	  around. This supports one level of GHCB nesting, which is
	  sufficient for now.

	- Moved all SEV-ES related per-cpu data into
	  'struct sev_es_runtime_data'. This struct is allocated and
	  initialized at boot per cpu.

	- Correctly set the protocol and ghcb_usage information when
	  talking to the hypervisor.

The previous version of the patch-set can be found here:

	https://lore.kernel.org/lkml/20200319091407.1481-1-joro@8bytes.org/

Please review.


Thanks,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Doug Covelli (1):
  x86/vmware: Add VMware specific handling for VMMCALL under SEV-ES

Joerg Roedel (53):
  KVM: SVM: Add GHCB Accessor functions
  x86/traps: Move some definitions to <asm/trap_defs.h>
  x86/insn: Make inat-tables.c suitable for pre-decompression code
  x86/umip: Factor out instruction fetch
  x86/umip: Factor out instruction decoding
  x86/insn: Add insn_get_modrm_reg_off()
  x86/insn: Add insn_rep_prefix() helper
  x86/boot/compressed/64: Disable red-zone usage
  x86/boot/compressed/64: Switch to __KERNEL_CS after GDT is loaded
  x86/boot/compressed/64: Add IDT Infrastructure
  x86/boot/compressed/64: Rename kaslr_64.c to ident_map_64.c
  x86/boot/compressed/64: Add page-fault handler
  x86/boot/compressed/64: Always switch to own page-table
  x86/boot/compressed/64: Don't pre-map memory in KASLR code
  x86/boot/compressed/64: Change add_identity_map() to take start and
    end
  x86/boot/compressed/64: Add stage1 #VC handler
  x86/boot/compressed/64: Call set_sev_encryption_mask earlier
  x86/boot/compressed/64: Check return value of
    kernel_ident_mapping_init()
  x86/boot/compressed/64: Add set_page_en/decrypted() helpers
  x86/boot/compressed/64: Setup GHCB Based VC Exception handler
  x86/boot/compressed/64: Unmap GHCB page before booting the kernel
  x86/fpu: Move xgetbv()/xsetbv() into separate header
  x86/idt: Move IDT to data segment
  x86/idt: Split idt_data setup out of set_intr_gate()
  x86/idt: Move two function from k/idt.c to i/a/desc.h
  x86/head/64: Install boot GDT
  x86/head/64: Reload GDT after switch to virtual addresses
  x86/head/64: Load segment registers earlier
  x86/head/64: Switch to initial stack earlier
  x86/head/64: Build k/head64.c with -fno-stack-protector
  x86/head/64: Load IDT earlier
  x86/head/64: Move early exception dispatch to C code
  x86/sev-es: Add SEV-ES Feature Detection
  x86/sev-es: Print SEV-ES info into kernel log
  x86/sev-es: Compile early handler code into kernel image
  x86/sev-es: Setup early #VC handler
  x86/sev-es: Setup GHCB based boot #VC handler
  x86/sev-es: Allocate and Map IST stacks for #VC handler
  x86/dumpstack/64: Handle #VC exception stacks
  x86/sev-es: Shift #VC IST Stack in nmi_enter()/nmi_exit()
  x86/sev-es: Wire up existing #VC exit-code handlers
  x86/sev-es: Handle instruction fetches from user-space
  x86/sev-es: Do not crash on #VC exceptions from user-space
  x86/sev-es: Handle MMIO String Instructions
  x86/sev-es: Handle #AC Events
  x86/sev-es: Handle #DB Events
  x86/paravirt: Allow hypervisor specific VMMCALL handling under SEV-ES
  x86/realmode: Add SEV-ES specific trampoline entry point
  x86/head/64: Setup TSS early for secondary CPUs
  x86/head/64: Don't call verify_cpu() on starting APs
  x86/head/64: Rename start_cpu0
  x86/sev-es: Support CPU offline/online
  x86/sev-es: Handle NMI State

Mike Stunes (1):
  x86/sev-es: Cache CPUID results for improved performance

Tom Lendacky (19):
  KVM: SVM: Add GHCB definitions
  x86/cpufeatures: Add SEV-ES CPU feature
  x86/sev-es: Add support for handling IOIO exceptions
  x86/sev-es: Add CPUID handling to #VC handler
  x86/sev-es: Setup per-cpu GHCBs for the runtime handler
  x86/sev-es: Add Runtime #VC Exception Handler
  x86/sev-es: Handle MMIO events
  x86/sev-es: Handle MSR events
  x86/sev-es: Handle DR7 read/write events
  x86/sev-es: Handle WBINVD Events
  x86/sev-es: Handle RDTSC(P) Events
  x86/sev-es: Handle RDPMC Events
  x86/sev-es: Handle INVD Events
  x86/sev-es: Handle MONITOR/MONITORX Events
  x86/sev-es: Handle MWAIT/MWAITX Events
  x86/sev-es: Handle VMMCALL Events
  x86/kvm: Add KVM specific VMMCALL handling under SEV-ES
  x86/realmode: Setup AP jump table
  x86/efi: Add GHCB mappings when SEV-ES is active

 arch/x86/Kconfig                           |    1 +
 arch/x86/boot/Makefile                     |    2 +-
 arch/x86/boot/compressed/Makefile          |    9 +-
 arch/x86/boot/compressed/head_64.S         |   40 +-
 arch/x86/boot/compressed/ident_map_64.c    |  339 +++++
 arch/x86/boot/compressed/idt_64.c          |   53 +
 arch/x86/boot/compressed/idt_handlers_64.S |   76 ++
 arch/x86/boot/compressed/kaslr.c           |   36 +-
 arch/x86/boot/compressed/kaslr_64.c        |  153 ---
 arch/x86/boot/compressed/misc.c            |    7 +
 arch/x86/boot/compressed/misc.h            |   45 +-
 arch/x86/boot/compressed/sev-es.c          |  210 +++
 arch/x86/entry/entry_64.S                  |    4 +
 arch/x86/include/asm/cpu.h                 |    2 +-
 arch/x86/include/asm/cpu_entry_area.h      |   62 +
 arch/x86/include/asm/cpufeatures.h         |    1 +
 arch/x86/include/asm/desc.h                |   30 +
 arch/x86/include/asm/desc_defs.h           |   10 +
 arch/x86/include/asm/fpu/internal.h        |   29 +-
 arch/x86/include/asm/fpu/xcr.h             |   32 +
 arch/x86/include/asm/hardirq.h             |   14 +
 arch/x86/include/asm/insn-eval.h           |    6 +
 arch/x86/include/asm/mem_encrypt.h         |    5 +
 arch/x86/include/asm/msr-index.h           |    3 +
 arch/x86/include/asm/page_64_types.h       |    1 +
 arch/x86/include/asm/pgtable.h             |    2 +-
 arch/x86/include/asm/processor.h           |    1 +
 arch/x86/include/asm/realmode.h            |    4 +
 arch/x86/include/asm/segment.h             |    2 +-
 arch/x86/include/asm/setup.h               |    1 -
 arch/x86/include/asm/sev-es.h              |  107 ++
 arch/x86/include/asm/stacktrace.h          |    4 +
 arch/x86/include/asm/svm.h                 |  115 +-
 arch/x86/include/asm/trap_defs.h           |   50 +
 arch/x86/include/asm/traps.h               |   51 +-
 arch/x86/include/asm/x86_init.h            |   16 +-
 arch/x86/include/uapi/asm/svm.h            |   11 +
 arch/x86/kernel/Makefile                   |    5 +
 arch/x86/kernel/asm-offsets_64.c           |    1 +
 arch/x86/kernel/cpu/amd.c                  |    3 +-
 arch/x86/kernel/cpu/common.c               |    1 +
 arch/x86/kernel/cpu/scattered.c            |    1 +
 arch/x86/kernel/cpu/vmware.c               |   50 +-
 arch/x86/kernel/dumpstack_64.c             |   47 +
 arch/x86/kernel/head64.c                   |   70 +-
 arch/x86/kernel/head_32.S                  |    4 +-
 arch/x86/kernel/head_64.S                  |  176 ++-
 arch/x86/kernel/idt.c                      |   52 +-
 arch/x86/kernel/kvm.c                      |   35 +-
 arch/x86/kernel/nmi.c                      |    8 +
 arch/x86/kernel/sev-es-shared.c            |  479 +++++++
 arch/x86/kernel/sev-es.c                   | 1428 ++++++++++++++++++++
 arch/x86/kernel/smpboot.c                  |    4 +-
 arch/x86/kernel/traps.c                    |    3 +
 arch/x86/kernel/umip.c                     |   49 +-
 arch/x86/lib/insn-eval.c                   |  130 ++
 arch/x86/mm/extable.c                      |    1 +
 arch/x86/mm/mem_encrypt.c                  |   39 +-
 arch/x86/mm/mem_encrypt_identity.c         |    3 +
 arch/x86/platform/efi/efi_64.c             |   10 +
 arch/x86/realmode/init.c                   |   12 +
 arch/x86/realmode/rm/header.S              |    3 +
 arch/x86/realmode/rm/trampoline_64.S       |   20 +
 arch/x86/tools/gen-insn-attr-x86.awk       |   50 +-
 tools/arch/x86/tools/gen-insn-attr-x86.awk |   50 +-
 65 files changed, 3842 insertions(+), 426 deletions(-)
 create mode 100644 arch/x86/boot/compressed/ident_map_64.c
 create mode 100644 arch/x86/boot/compressed/idt_64.c
 create mode 100644 arch/x86/boot/compressed/idt_handlers_64.S
 delete mode 100644 arch/x86/boot/compressed/kaslr_64.c
 create mode 100644 arch/x86/boot/compressed/sev-es.c
 create mode 100644 arch/x86/include/asm/fpu/xcr.h
 create mode 100644 arch/x86/include/asm/sev-es.h
 create mode 100644 arch/x86/include/asm/trap_defs.h
 create mode 100644 arch/x86/kernel/sev-es-shared.c
 create mode 100644 arch/x86/kernel/sev-es.c
```
