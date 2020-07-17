#### [patch V3 01/13] entry: Provide generic syscall entry functionalityReferences: <20200716182208.180916541@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11668373
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 068A213A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:51:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9F28207BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:51:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="OnDYOzRm";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="6KRLHLBQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729662AbgGPTus (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 15:50:48 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:35246 "EHLO
        galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729506AbgGPTur (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jul 2020 15:50:47 -0400
Message-Id: <20200716185424.011950288@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1594929043;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=IR3XLMzlMIVsyZTFeP3Anvt5KzF7MuEmK/Q7BPDXqmc=;
        b=OnDYOzRmeE7nqK/J2OoONv6Zsdr+FwRdTOZLnGKBgHoGoVE1tKlBmGjRIvUUfYRqzMVHWV
        VCECtSa+Ab91J3CDrU+Idkwki/N+LruCBPiT6qujD5GWVicP6rIgPpU3/QecRhX82l0GdY
        d17gkrFn0L4Qnb7V9guJZvMRXNuYZqMLjXqqQys0y0QQNhNMV1BwjYDOqU5YqNPZA1O6UU
        7tczlkfYItK8kWJS/mXPrD30Bq5NDj2nGWPT1ce7UCQYkHAH39H9spJrNsch3QL2dzYHFc
        agkdmG2zqkP8E8c01rE/uveDKbqEeUzF4zgQQnNQ1hVEtU5z9EIfPBpUWpzh+Q==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1594929043;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=IR3XLMzlMIVsyZTFeP3Anvt5KzF7MuEmK/Q7BPDXqmc=;
        b=6KRLHLBQ90TMjrFTaI0Ux1Clquu8kJ1lvIiEmlWKLz/rWHXCig8p0+VKnCvm7qHU4aJVpQ
        haTNazrp8vNCwAAA==
Date: Thu, 16 Jul 2020 20:22:09 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [patch V3 01/13] entry: Provide generic syscall entry functionality
References: <20200716182208.180916541@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

On syscall entry certain work needs to be done:

   - Establish state (lockdep, context tracking, tracing)
   - Conditional work (ptrace, seccomp, audit...)

This code is needlessly duplicated and  different in all
architectures.

Provide a generic version based on the x86 implementation which has all the
RCU and instrumentation bits right.

As interrupt/exception entry from user space needs parts of the same
functionality, provide a function for this as well.

syscall_enter_from_user_mode() and irqentry_enter_from_user_mode() must be
called right after the low level ASM entry. The calling code must be
non-instrumentable. After the functions returns state is correct and the
subsequent functions can be instrumented.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
---
V3: Adapt to noinstr changes. Add interrupt/exception entry function.

V2: Fix function documentation (Mike)
    Add comment about return value (Andy)
---
 arch/Kconfig                 |    3 
 include/linux/entry-common.h |  156 +++++++++++++++++++++++++++++++++++++++++++
 kernel/Makefile              |    1 
 kernel/entry/Makefile        |    3 
 kernel/entry/common.c        |   78 +++++++++++++++++++++
```
#### [RESEND v13 01/11] KVM: x86: Include CET definitions for KVM test purpose
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11666567
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B42F722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:17:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D6E120775
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:17:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728199AbgGPDQ7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:16:59 -0400
Received: from mga06.intel.com ([134.134.136.31]:8147 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726770AbgGPDQ5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:16:57 -0400
IronPort-SDR: 
 sgQybs7i+MF/9gGXs6AlB2uLUlkxnLrZq1je4JpvisQxg2b1bIiC6NYCrDsV/Df+fezVtcu7dS
 owPl2ZVdnqUg==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="210844831"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="210844831"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:16:57 -0700
IronPort-SDR: 
 bTOUrYvWWf/ceKqf+FwF8rnI090LMkr1t4DERq+nqOYbHvnvacPhaBW+Uyy5H01tvck1+gY4QK
 6+W9weU20zsg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="360910412"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga001.jf.intel.com with ESMTP; 15 Jul 2020 20:16:55 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND v13 01/11] KVM: x86: Include CET definitions for KVM test
 purpose
Date: Thu, 16 Jul 2020 11:16:17 +0800
Message-Id: <20200716031627.11492-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200716031627.11492-1-weijiang.yang@intel.com>
References: <20200716031627.11492-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These definitions are added by CET kernel patch and referenced by KVM,
if the CET KVM patches are tested without CET kernel patches, this patch
should be included.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 include/linux/kvm_host.h | 32 ++++++++++++++++++++++++++++++++
 1 file changed, 32 insertions(+)

```
#### [PATCH V2 1/6] vhost: introduce vhost_call_ctx
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11667181
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE832722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 11:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BDCF32074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 11:27:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728234AbgGPL1u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 07:27:50 -0400
Received: from mga02.intel.com ([134.134.136.20]:52577 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728150AbgGPL1p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jul 2020 07:27:45 -0400
IronPort-SDR: 
 KEsK0Pj49w3oPpzmfhI7nLfTcc6k/c7Zp3M0NyYWsYsOaHMdj+jN1TnLeRuk6DHtVYuvvpcVVk
 yCvTMZWFgnWQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="137485044"
X-IronPort-AV: E=Sophos;i="5.75,359,1589266800";
   d="scan'208";a="137485044"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Jul 2020 04:27:44 -0700
IronPort-SDR: 
 rDjzjtE8pDP8pqFEC1rFywyE99795wV54ExGHJcd/0JerAtFPtnD4G3gl6R4uXJ7Y9Fp91i53s
 cOUEs0MOI0eA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,359,1589266800";
   d="scan'208";a="460442808"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga005.jf.intel.com with ESMTP; 16 Jul 2020 04:27:42 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, alex.williamson@redhat.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 1/6] vhost: introduce vhost_call_ctx
Date: Thu, 16 Jul 2020 19:23:44 +0800
Message-Id: <1594898629-18790-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594898629-18790-1-git-send-email-lingshan.zhu@intel.com>
References: <1594898629-18790-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduces struct vhost_call_ctx which replaced
raw struct eventfd_ctx *call_ctx in struct vhost_virtqueue.
Besides eventfd_ctx, it contains a spin lock and an
irq_bypass_producer in its structure.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Suggested-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c  |  4 ++--
 drivers/vhost/vhost.c | 22 ++++++++++++++++------
 drivers/vhost/vhost.h |  9 ++++++++-
 3 files changed, 26 insertions(+), 9 deletions(-)

```
#### [PATCH 1/3] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11666625
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F0AEE60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:44:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E23902075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:44:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728314AbgGPDoN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:44:13 -0400
Received: from mga09.intel.com ([134.134.136.24]:54949 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728267AbgGPDoL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:44:11 -0400
IronPort-SDR: 
 pbNN2uINWfgaHKnRsAL7IUhDiRlECRX/p41XDtF/uj7zfl3420sNfC8/oFY7zrRMsZb5GnLfWt
 d+1IWDqkVJ7g==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="150699762"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="150699762"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:44:10 -0700
IronPort-SDR: 
 tvy9nyPPeitGruJNQhYxoKw9S2CoFzNA4pJ8ATrid6IesBtWQu4a5E3xnoMDrVLUYg/TQN9xLk
 xjsmWp8wL74A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="282314261"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga003.jf.intel.com with ESMTP; 15 Jul 2020 20:44:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR
 check
Date: Wed, 15 Jul 2020 20:44:06 -0700
Message-Id: <20200716034408.6342-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200716034408.6342-1-sean.j.christopherson@intel.com>
References: <20200716034408.6342-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use cpuid_maxphyaddr() instead of cpuid_query_maxphyaddr() for the
RTIT base MSR check.  There is no reason to recompute MAXPHYADDR as the
precomputed version is synchronized with CPUID updates, and
MSR_IA32_RTIT_OUTPUT_BASE is not written between stuffing CPUID and
refreshing vcpu->arch.maxphyaddr.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/9] KVM: nSVM: Correctly set the shadow NPT root level in its MMU role
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11666599
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C01760D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:41:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6E3362076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:41:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728232AbgGPDl1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:41:27 -0400
Received: from mga11.intel.com ([192.55.52.93]:49384 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727825AbgGPDlZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:41:25 -0400
IronPort-SDR: 
 o2z56twEMc573M5VCWIdM1T/z81SYz8Ecfgs6kfhJG/X/2qow+B9CJEftnvYhJk7L052vOilyQ
 d+BlHOes5PZQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="147310948"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="147310948"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:41:25 -0700
IronPort-SDR: 
 Eq7vSGi50vAzlkVRA/w3Ky5hkrfcwwmwP61S/b/Y2Flz4ni732GYXOvuFaspE6EaL/8OTdMPMP
 9v9oo4ejb76Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="316905470"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga008.jf.intel.com with ESMTP; 15 Jul 2020 20:41:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/9] KVM: nSVM: Correctly set the shadow NPT root level in its
 MMU role
Date: Wed, 15 Jul 2020 20:41:14 -0700
Message-Id: <20200716034122.5998-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200716034122.5998-1-sean.j.christopherson@intel.com>
References: <20200716034122.5998-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the initialization of shadow NPT MMU's shadow_root_level into
kvm_init_shadow_npt_mmu() and explicitly set the level in the shadow NPT
MMU's role to be the TDP level.  This ensures the role and MMU levels
are synchronized and also initialized before __kvm_mmu_new_pgd(), which
consumes the level when attempting a fast PGD switch.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Fixes: 9fa72119b24db ("kvm: x86: Introduce kvm_mmu_calc_root_page_role()")
Fixes: a506fdd223426 ("KVM: nSVM: implement nested_svm_load_cr3() and use it for host->guest switch")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c    | 3 +++
 arch/x86/kvm/svm/nested.c | 1 -
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v14 6/9] s390x: Library resources for CSS tests
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11667423
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 412281392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 13:04:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 279E22074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 13:04:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728669AbgGPNEC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 09:04:02 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:56328 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728237AbgGPNEC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jul 2020 09:04:02 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06GD3V4W046251;
        Thu, 16 Jul 2020 09:03:59 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32a7hnkb5g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 09:03:59 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06GD3itK047458;
        Thu, 16 Jul 2020 09:03:58 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32a7hnkb42-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 09:03:58 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06GCxrY1023884;
        Thu, 16 Jul 2020 13:03:56 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma02fra.de.ibm.com with ESMTP id 327527ws4d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 13:03:56 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06GD2dhE2425302
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jul 2020 13:02:39 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0D0214C044;
        Thu, 16 Jul 2020 13:02:39 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7F1444C046;
        Thu, 16 Jul 2020 13:02:38 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.61.186])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 16 Jul 2020 13:02:38 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [PATCH v14 6/9] s390x: Library resources for CSS tests
Date: Thu, 16 Jul 2020 15:02:29 +0200
Message-Id: <1594904550-32273-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <7eda888a-88e9-98fe-96ac-d6c7ee1160bf@linux.ibm.com>
References: <7eda888a-88e9-98fe-96ac-d6c7ee1160bf@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-16_06:2020-07-16,2020-07-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 impostorscore=0 malwarescore=0 adultscore=0 phishscore=0
 priorityscore=1501 mlxlogscore=999 bulkscore=0 suspectscore=1
 lowpriorityscore=0 mlxscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2007160102
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Provide some definitions and library routines that can be used by
tests targeting the channel subsystem.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Janosch Frank <frankja@de.ibm.com>
---
 lib/s390x/css.h      | 256 +++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c | 152 +++++++++++++++++++++++++
 s390x/Makefile       |   1 +
 3 files changed, 409 insertions(+)
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c

diff --git a/lib/s390x/css.h b/lib/s390x/css.h
new file mode 100644
index 0000000..0ddceb1
--- /dev/null
+++ b/lib/s390x/css.h
@@ -0,0 +1,256 @@
+/*
+ * CSS definitions
+ *
+ * Copyright IBM, Corp. 2020
+ * Author: Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU General Public License version 2.
+ */
+
+#ifndef CSS_H
+#define CSS_H
+
+/* subchannel ID bit 16 must always be one */
+#define SCHID_ONE	0x00010000
+
+#define CCW_F_CD	0x80
+#define CCW_F_CC	0x40
+#define CCW_F_SLI	0x20
+#define CCW_F_SKP	0x10
+#define CCW_F_PCI	0x08
+#define CCW_F_IDA	0x04
+#define CCW_F_S		0x02
+#define CCW_F_MIDA	0x01
+
+#define CCW_C_NOP	0x03
+#define CCW_C_TIC	0x08
+
+struct ccw1 {
+	uint8_t code;
+	uint8_t flags;
+	uint16_t count;
+	uint32_t data_address;
+} __attribute__ ((aligned(8)));
+
+#define ORB_CTRL_KEY	0xf0000000
+#define ORB_CTRL_SPND	0x08000000
+#define ORB_CTRL_STR	0x04000000
+#define ORB_CTRL_MOD	0x02000000
+#define ORB_CTRL_SYNC	0x01000000
+#define ORB_CTRL_FMT	0x00800000
+#define ORB_CTRL_PFCH	0x00400000
+#define ORB_CTRL_ISIC	0x00200000
+#define ORB_CTRL_ALCC	0x00100000
+#define ORB_CTRL_SSIC	0x00080000
+#define ORB_CTRL_CPTC	0x00040000
+#define ORB_CTRL_C64	0x00020000
+#define ORB_CTRL_I2K	0x00010000
+#define ORB_CTRL_LPM	0x0000ff00
+#define ORB_CTRL_ILS	0x00000080
+#define ORB_CTRL_MIDAW	0x00000040
+#define ORB_CTRL_ORBX	0x00000001
+
+#define ORB_LPM_DFLT	0x00008000
+
+struct orb {
+	uint32_t intparm;
+	uint32_t ctrl;
+	uint32_t cpa;
+	uint32_t prio;
+	uint32_t reserved[4];
+} __attribute__ ((aligned(4)));
+
+struct scsw {
+	uint32_t ctrl;
+	uint32_t ccw_addr;
+	uint8_t  dev_stat;
+	uint8_t  sch_stat;
+	uint16_t count;
+};
+
+struct pmcw {
+	uint32_t intparm;
+#define PMCW_DNV        0x0001
+#define PMCW_ENABLE     0x0080
+	uint16_t flags;
+	uint16_t devnum;
+	uint8_t  lpm;
+	uint8_t  pnom;
+	uint8_t  lpum;
+	uint8_t  pim;
+	uint16_t mbi;
+	uint8_t  pom;
+	uint8_t  pam;
+	uint8_t  chpid[8];
+	uint32_t flags2;
+};
+#define PMCW_CHANNEL_TYPE(pmcw) (pmcw->flags2 >> 21)
+
+struct schib {
+	struct pmcw pmcw;
+	struct scsw scsw;
+	uint8_t  md[12];
+} __attribute__ ((aligned(4)));
+
+struct irb {
+	struct scsw scsw;
+	uint32_t esw[5];
+	uint32_t ecw[8];
+	uint32_t emw[8];
+} __attribute__ ((aligned(4)));
+
+/* CSS low level access functions */
+
+static inline int ssch(unsigned long schid, struct orb *addr)
+{
+	register long long reg1 asm("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	ssch	0(%2)\n"
+		"	ipm	%0\n"
+		"	srl	%0,28\n"
+		: "=d" (cc)
+		: "d" (reg1), "a" (addr), "m" (*addr)
+		: "cc", "memory");
+	return cc;
+}
+
+static inline int stsch(unsigned long schid, struct schib *addr)
+{
+	register unsigned long reg1 asm ("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	stsch	0(%3)\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc), "=m" (*addr)
+		: "d" (reg1), "a" (addr)
+		: "cc");
+	return cc;
+}
+
+static inline int msch(unsigned long schid, struct schib *addr)
+{
+	register unsigned long reg1 asm ("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	msch	0(%3)\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1), "m" (*addr), "a" (addr)
+		: "cc");
+	return cc;
+}
+
+static inline int tsch(unsigned long schid, struct irb *addr)
+{
+	register unsigned long reg1 asm ("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	tsch	0(%3)\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc), "=m" (*addr)
+		: "d" (reg1), "a" (addr)
+		: "cc");
+	return cc;
+}
+
+static inline int hsch(unsigned long schid)
+{
+	register unsigned long reg1 asm("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	hsch\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1)
+		: "cc");
+	return cc;
+}
+
+static inline int xsch(unsigned long schid)
+{
+	register unsigned long reg1 asm("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	xsch\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1)
+		: "cc");
+	return cc;
+}
+
+static inline int csch(unsigned long schid)
+{
+	register unsigned long reg1 asm("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	csch\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1)
+		: "cc");
+	return cc;
+}
+
+static inline int rsch(unsigned long schid)
+{
+	register unsigned long reg1 asm("1") = schid;
+	int cc;
+
+	asm volatile(
+		"	rsch\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1)
+		: "cc");
+	return cc;
+}
+
+static inline int rchp(unsigned long chpid)
+{
+	register unsigned long reg1 asm("1") = chpid;
+	int cc;
+
+	asm volatile(
+		"	rchp\n"
+		"	ipm	%0\n"
+		"	srl	%0,28"
+		: "=d" (cc)
+		: "d" (reg1)
+		: "cc");
+	return cc;
+}
+
+/* Debug functions */
+char *dump_pmcw_flags(uint16_t f);
+char *dump_scsw_flags(uint32_t f);
+
+void dump_scsw(struct scsw *scsw);
+void dump_irb(struct irb *irbp);
+void dump_schib(struct schib *sch);
+struct ccw1 *dump_ccw(struct ccw1 *cp);
+void dump_irb(struct irb *irbp);
+void dump_pmcw(struct pmcw *p);
+void dump_orb(struct orb *op);
+
+int css_enumerate(void);
+#define MAX_ENABLE_RETRIES      5
+int css_enable(int schid);
+
+#endif
diff --git a/lib/s390x/css_dump.c b/lib/s390x/css_dump.c
new file mode 100644
index 0000000..1266f04
--- /dev/null
+++ b/lib/s390x/css_dump.c
@@ -0,0 +1,152 @@
+/*
+ * Channel subsystem structures dumping
+ *
+ * Copyright (c) 2020 IBM Corp.
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU General Public License version 2.
+ *
+ * Description:
+ * Provides the dumping functions for various structures used by subchannels:
+ * - ORB  : Operation request block, describes the I/O operation and points to
+ *          a CCW chain
+ * - CCW  : Channel Command Word, describes the command, data and flow control
+ * - IRB  : Interuption response Block, describes the result of an operation;
+ *          holds a SCSW and model-dependent data.
+ * - SCHIB: SubCHannel Information Block composed of:
+ *   - SCSW: SubChannel Status Word, status of the channel.
+ *   - PMCW: Path Management Control Word
+ * You need the QEMU ccw-pong device in QEMU to answer the I/O transfers.
+ */
+
+#include <libcflat.h>
+#include <stdint.h>
+#include <string.h>
+
+#include <css.h>
+
+/*
+ * Try to have a more human representation of the SCSW flags:
+ * each letter in the two strings represents the first
+ * letter of the associated bit in the flag fields.
+ */
+static const char *scsw_str = "kkkkslccfpixuzen";
+static const char *scsw_str2 = "1SHCrshcsdsAIPSs";
+static char scsw_line[64] = {};
+
+char *dump_scsw_flags(uint32_t f)
+{
+	int i;
+
+	for (i = 0; i < 16; i++) {
+		if ((f << i) & 0x80000000)
+			scsw_line[i] = scsw_str[i];
+		else
+			scsw_line[i] = '_';
+	}
+	scsw_line[i] = ' ';
+	for (; i < 32; i++) {
+		if ((f << i) & 0x80000000)
+			scsw_line[i + 1] = scsw_str2[i - 16];
+		else
+			scsw_line[i + 1] = '_';
+	}
+	return scsw_line;
+}
+
+/*
+ * Try to have a more human representation of the PMCW flags
+ * each letter in the string represents the first
+ * letter of the associated bit in the flag fields.
+ */
+static const char *pmcw_str = "11iii111ellmmdtv";
+static char pcmw_line[32] = {};
+char *dump_pmcw_flags(uint16_t f)
+{
+	int i;
+
+	for (i = 0; i < 16; i++) {
+		if ((f << i) & 0x8000)
+			pcmw_line[i] = pmcw_str[i];
+		else
+			pcmw_line[i] = '_';
+	}
+	return pcmw_line;
+}
+
+void dump_scsw(struct scsw *s)
+{
+	dump_scsw_flags(s->ctrl);
+	printf("scsw->flags: %s\n", scsw_line);
+	printf("scsw->addr : %08x\n", s->ccw_addr);
+	printf("scsw->devs : %02x\n", s->dev_stat);
+	printf("scsw->schs : %02x\n", s->sch_stat);
+	printf("scsw->count: %04x\n", s->count);
+}
+
+void dump_irb(struct irb *irbp)
+{
+	int i;
+	uint32_t *p = (uint32_t *)irbp;
+
+	dump_scsw(&irbp->scsw);
+	for (i = 0; i < sizeof(*irbp)/sizeof(*p); i++, p++)
+		printf("irb[%02x] : %08x\n", i, *p);
+}
+
+void dump_pmcw(struct pmcw *p)
+{
+	int i;
+
+	printf("pmcw->intparm  : %08x\n", p->intparm);
+	printf("pmcw->flags    : %04x\n", p->flags);
+	dump_pmcw_flags(p->flags);
+	printf("pmcw->devnum   : %04x\n", p->devnum);
+	printf("pmcw->lpm      : %02x\n", p->lpm);
+	printf("pmcw->pnom     : %02x\n", p->pnom);
+	printf("pmcw->lpum     : %02x\n", p->lpum);
+	printf("pmcw->pim      : %02x\n", p->pim);
+	printf("pmcw->mbi      : %04x\n", p->mbi);
+	printf("pmcw->pom      : %02x\n", p->pom);
+	printf("pmcw->pam      : %02x\n", p->pam);
+	printf("pmcw->mbi      : %04x\n", p->mbi);
+	for (i = 0; i < 8; i++)
+		printf("pmcw->chpid[%d]: %02x\n", i, p->chpid[i]);
+	printf("pmcw->flags2  : %08x\n", p->flags2);
+}
+
+void dump_schib(struct schib *sch)
+{
+	struct pmcw *p = &sch->pmcw;
+	struct scsw *s = &sch->scsw;
+
+	printf("--SCHIB--\n");
+	dump_pmcw(p);
+	dump_scsw(s);
+}
+
+struct ccw1 *dump_ccw(struct ccw1 *cp)
+{
+	printf("CCW: code: %02x flags: %02x count: %04x data: %08x\n", cp->code,
+	    cp->flags, cp->count, cp->data_address);
+
+	if (cp->code == CCW_C_TIC)
+		return (struct ccw1 *)(long)cp->data_address;
+
+	return (cp->flags & CCW_F_CC) ? cp + 1 : NULL;
+}
+
+void dump_orb(struct orb *op)
+{
+	struct ccw1 *cp;
+
+	printf("ORB: intparm : %08x\n", op->intparm);
+	printf("ORB: ctrl    : %08x\n", op->ctrl);
+	printf("ORB: prio    : %08x\n", op->prio);
+	cp = (struct ccw1 *)(long) (op->cpa);
+	while (cp)
+		cp = dump_ccw(cp);
+}
```
#### [kvm-unit-tests PATCH v13 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11666857
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20DE860D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 08:23:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1268420775
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 08:23:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727058AbgGPIXj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 04:23:39 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:37870 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726547AbgGPIXi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jul 2020 04:23:38 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06G82ioi184311;
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32aj742fnw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06G82ooM184867;
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32aj742fn9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06G8JdAY015867;
        Thu, 16 Jul 2020 08:23:34 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma02fra.de.ibm.com with ESMTP id 327527wgha-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 08:23:34 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06G8NWEi22479220
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jul 2020 08:23:32 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32AD04C044;
        Thu, 16 Jul 2020 08:23:32 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BAB464C05E;
        Thu, 16 Jul 2020 08:23:31 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.61.186])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 16 Jul 2020 08:23:31 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v13 1/9] s390x: saving regs for interrupts
Date: Thu, 16 Jul 2020 10:23:21 +0200
Message-Id: <1594887809-10521-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594887809-10521-1-git-send-email-pmorel@linux.ibm.com>
References: <1594887809-10521-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-16_04:2020-07-16,2020-07-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 mlxscore=0 impostorscore=0 clxscore=1015 malwarescore=0 lowpriorityscore=0
 adultscore=0 suspectscore=1 priorityscore=1501 mlxlogscore=999 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007160058
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers, the floating point registers and the floating point
control register on the stack in case of I/O interrupts

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/cstart64.S | 41 +++++++++++++++++++++++++++++++++++++++--
 1 file changed, 39 insertions(+), 2 deletions(-)

```
#### [PATCH v2] x86/bugs/multihit: Fix mitigation reporting when VMX is not in use
##### From: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
X-Patchwork-Id: 11668345
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D8C8B13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:29:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5F402088E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:29:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729595AbgGPT34 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 15:29:56 -0400
Received: from mga01.intel.com ([192.55.52.88]:62386 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728788AbgGPT34 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jul 2020 15:29:56 -0400
IronPort-SDR: 
 dXX6OC5CoOkqakY0NaniPr/XTx4mAwfVa9u4jRPr/O9/lNSXcNWnwWxTISVfjsWdBdvGGOMzqi
 VrTEmm8eRHNg==
X-IronPort-AV: E=McAfee;i="6000,8403,9684"; a="167616024"
X-IronPort-AV: E=Sophos;i="5.75,360,1589266800";
   d="scan'208";a="167616024"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Jul 2020 12:29:55 -0700
IronPort-SDR: 
 Rw/CNHn192L0+R8y7GGaKRMKcHlm3dB/wEHRSknCC3Mzc7hl/2FGCndwvsfD2gY3p6lsaNLv7p
 pEUq9GnywRMQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,360,1589266800";
   d="scan'208";a="486217234"
Received: from guptapadev.jf.intel.com (HELO guptapadev.amr) ([10.54.74.188])
  by fmsmga006.fm.intel.com with ESMTP; 16 Jul 2020 12:29:54 -0700
Date: Thu, 16 Jul 2020 12:23:59 -0700
From: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
To: Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>
Cc: Jonathan Corbet <corbet@lwn.net>, x86@kernel.org,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tony Luck <tony.luck@intel.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        "Gomez Iglesias, Antonio" <antonio.gomez.iglesias@intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Vincenzo Frascino <vincenzo.frascino@arm.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Waiman Long <longman@redhat.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Mark Gross <mgross@linux.intel.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH v2] x86/bugs/multihit: Fix mitigation reporting when VMX is
 not in use
Message-ID: 
 <0ba029932a816179b9d14a30db38f0f11ef1f166.1594925782.git.pawan.kumar.gupta@linux.intel.com>
MIME-Version: 1.0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On systems that have virtualization disabled or unsupported, sysfs
mitigation for X86_BUG_ITLB_MULTIHIT is reported incorrectly as:

  $ cat /sys/devices/system/cpu/vulnerabilities/itlb_multihit
  KVM: Vulnerable

System is not vulnerable to DoS attack from a rogue guest when
virtualization is disabled or unsupported in the hardware. Change the
mitigation reporting for these cases.

Fixes: b8e8c8303ff2 ("kvm: mmu: ITLB_MULTIHIT mitigation")
Reported-by: Nelson Dsouza <nelson.dsouza@linux.intel.com>
Co-developed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
---
v2:
 - Change mitigation reporting as per the state on VMX feature.

v1: https://lore.kernel.org/lkml/267631f4db4fd7e9f7ca789c2efaeab44103f68e.1594689154.git.pawan.kumar.gupta@linux.intel.com/

 Documentation/admin-guide/hw-vuln/multihit.rst | 4 ++++
 arch/x86/kernel/cpu/bugs.c                     | 8 +++++++-
 2 files changed, 11 insertions(+), 1 deletion(-)

```
