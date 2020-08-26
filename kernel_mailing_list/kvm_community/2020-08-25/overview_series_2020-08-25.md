#### [PATCH v3 41/74] kvm: Move QOM macros to kvm.h
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11736297
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60E841575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:22:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 49164207DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:22:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WxfUEgHk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726975AbgHYTWs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 15:22:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51947 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726734AbgHYTWq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 25 Aug 2020 15:22:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598383365;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=b3i9Dto6wylUbRr2eIO0FnAXXH86Fg9jKOhIqiNdyqs=;
        b=WxfUEgHkEkXWoxn+McU4eh6/FY6A6HRgNJmjWwOPFlQYx4MpUIsThb6zxDDDCeEmDDFW/Y
        7garwIU5W9YaooikltL6Np8KMLHRFUt+xOmrx87i87jlCeRtWZgJMgkUSXr8dspLdFP4Uu
        3pNHfXK1zfSxbfnJYwyOz/ueBwID4FQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-14-94J20PfpM62dnTnVgTsdjA-1; Tue, 25 Aug 2020 15:22:43 -0400
X-MC-Unique: 94J20PfpM62dnTnVgTsdjA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B42A01DDE0;
        Tue, 25 Aug 2020 19:22:42 +0000 (UTC)
Received: from localhost (unknown [10.10.67.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7568A5D9D3;
        Tue, 25 Aug 2020 19:22:42 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "Daniel P. Berrange" <berrange@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v3 41/74] kvm: Move QOM macros to kvm.h
Date: Tue, 25 Aug 2020 15:20:37 -0400
Message-Id: <20200825192110.3528606-42-ehabkost@redhat.com>
In-Reply-To: <20200825192110.3528606-1-ehabkost@redhat.com>
References: <20200825192110.3528606-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move QOM macros close to the KVMState typedef.

This will make future conversion to OBJECT_DECLARE* easier.

Reviewed-by: Daniel P. Berrangé <berrange@redhat.com>
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
Changes v2 -> v3: none

Changes series v1 -> v2: new patch in series v2

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Cc: qemu-devel@nongnu.org
---
 include/sysemu/kvm.h     | 6 ++++++
 include/sysemu/kvm_int.h | 5 -----
 2 files changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH v4 1/2] x86/cpufeatures: Enumerate TSX suspend load address tracking instructions
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11734583
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C56A5739
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 00:54:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B74AD21741
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 00:54:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728298AbgHYAx6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Aug 2020 20:53:58 -0400
Received: from mga07.intel.com ([134.134.136.100]:44396 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726090AbgHYAx5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Aug 2020 20:53:57 -0400
IronPort-SDR: 
 eEKKEPnG26OHp9W1S7axK2BgdVUetKgcbKa6xPud2DD1JG0MNn6s462v8n0SpSsH6VOGdJ1GmR
 bny+b+hDENbg==
X-IronPort-AV: E=McAfee;i="6000,8403,9723"; a="220284886"
X-IronPort-AV: E=Sophos;i="5.76,350,1592895600";
   d="scan'208";a="220284886"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Aug 2020 17:53:57 -0700
IronPort-SDR: 
 RkzjqVXa4XtddFfE0FLjtOwfipdWaiXtJo6k/WMnOGWBl6I0QXHA/AMuQ64IFcyspZ3kBZE5Hr
 K4RSBuancGOg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,350,1592895600";
   d="scan'208";a="281351924"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by fmsmga008.fm.intel.com with ESMTP; 24 Aug 2020 17:53:52 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        gregkh@linuxfoundation.org, tglx@linutronix.de,
        tony.luck@intel.com, dave.hansen@intel.com,
        kyung.min.park@intel.com, ricardo.neri-calderon@linux.intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        jpoimboe@redhat.com, ak@linux.intel.com, ravi.v.shankar@intel.com,
        Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH v4 1/2] x86/cpufeatures: Enumerate TSX suspend load address
 tracking instructions
Date: Tue, 25 Aug 2020 08:47:57 +0800
Message-Id: <1598316478-23337-2-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1598316478-23337-1-git-send-email-cathy.zhang@intel.com>
References: <1598316478-23337-1-git-send-email-cathy.zhang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kyung Min Park <kyung.min.park@intel.com>

Intel TSX suspend load tracking instructions aim to give a way to
choose which memory accesses do not need to be tracked in the TSX
read set. Add TSX suspend load tracking CPUID feature flag TSXLDTRK
for enumeration.

A processor supports Intel TSX suspend load address tracking if
CPUID.0x07.0x0:EDX[16] is present. Two instructions XSUSLDTRK, XRESLDTRK
are available when this feature is present.

The CPU feature flag is shown as "tsxldtrk" in /proc/cpuinfo.

This instruction is currently documented in the the latest "extensions"
manual (ISE). It will appear in the "main" manual (SDM) in the future.

Signed-off-by: Kyung Min Park <kyung.min.park@intel.com>
Signed-off-by: Cathy Zhang <cathy.zhang@intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
---
Changes since v3:
 * N/A

Changes since v2:
 * Shorten documentation names for readability. Links to documentation
   can be found in the cover letter. (Dave Hansen)
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [patch] KVM: SVM: Periodically schedule when unregistering regions on destroy
##### From: David Rientjes <rientjes@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Rientjes <rientjes@google.com>
X-Patchwork-Id: 11736689
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E37FF913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:56:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA0952075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:56:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="wFmNSi8y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726610AbgHYT4b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 15:56:31 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56212 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726090AbgHYT4a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 25 Aug 2020 15:56:30 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78758C061574
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 12:56:30 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id d19so7554845pgl.10
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 12:56:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:from:to:cc:subject:message-id:user-agent:mime-version;
        bh=sS77HQ4aya/R9+vXtuPXPPA3LGWcRr4UTPM1NZ5LFJo=;
        b=wFmNSi8y7ndowYmkzhO96cnde/aYx+LgT6cp1qz1Kn3sDPyZeoeRq2yLrP0RrQk5Uz
         XjXTP3I1Ck+j7qelCC3Oe4hGzqwrVEzur3WGQ9MINjrdNgOv7zia7qi5tupIzziaMrUR
         AJCV084DG+NT7kD88XWSOK1uLIJALQrtIbHg00FUWqMwB1+Mw8KRQZotqG7PE2SNSkcE
         RsvlGw73T5m2K648JIVrC+wPaXDVwy1kof2fP9x6AB5Wd26iJ9zicyv0GtqKIJQPU3zm
         e5RoU5h5rCrAUEfIH/fyH4MXlpCUtV/mmRMbx6Uq22naGNtrgMzu22XKaKB36ozWVzQI
         XBhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:user-agent
         :mime-version;
        bh=sS77HQ4aya/R9+vXtuPXPPA3LGWcRr4UTPM1NZ5LFJo=;
        b=d6JpwGxaNIf9p2dYjmmKhz/XiApD1eRo0m1tMu1Jun7CTM0ryCHhMsNT/5A7atCh2E
         HUkVc043S4YjJFl4nLMSqDaT4R1jStvr5GtE1BDQxqy4OSvyuyBfTOlHlxNa7VvEisQ8
         khraktxuzEnWdP/RbzP+MLT26bpPJlAvZd8/E5CbGlD2GN4B0bdyUmMbsOFSCcvdCFKJ
         QJS6+KT2RL/Vium4j+Rm/uYdTQjNDxpezZgG4p2lavXAcJNM9JScL67CfJTLHrvRDLOC
         iHmh/DxXVMoZWIS53ysDHLyW2e7p0JqqP+HIiw61jgXgvzXbqv/cwBGLUrsU+QSfmH2P
         e+Qw==
X-Gm-Message-State: AOAM5337WCL6yubA4MEtHZCzWFmvRMZgaOWAUoQoFVQa0Et4KR+dEKGn
        cexGZ2Zi0D++jH1/iQAtkaWiqg==
X-Google-Smtp-Source: 
 ABdhPJzHObK6L0TlqwcnOFpTs7CbD6BXhwqr4tVz7e7Mc4oesBdNTSmF3uDyVkHSXbZ7Gp6t02oiZw==
X-Received: by 2002:a62:79c5:: with SMTP id
 u188mr9229706pfc.270.1598385389588;
        Tue, 25 Aug 2020 12:56:29 -0700 (PDT)
Received: from [2620:15c:17:3:4a0f:cfff:fe51:6667]
 ([2620:15c:17:3:4a0f:cfff:fe51:6667])
        by smtp.gmail.com with ESMTPSA id e65sm31886pjk.45.2020.08.25.12.56.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 25 Aug 2020 12:56:29 -0700 (PDT)
Date: Tue, 25 Aug 2020 12:56:28 -0700 (PDT)
From: David Rientjes <rientjes@google.com>
X-X-Sender: rientjes@chino.kir.corp.google.com
To: Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
cc: Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        x86@kernel.org, kvm@vger.kernel.org
Subject: [patch] KVM: SVM: Periodically schedule when unregistering regions
 on destroy
Message-ID: 
 <alpine.DEB.2.23.453.2008251255240.2987727@chino.kir.corp.google.com>
User-Agent: Alpine 2.23 (DEB 453 2020-06-18)
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There may be many encrypted regions that need to be unregistered when a
SEV VM is destroyed.  This can lead to soft lockups.  For example, on a
host running 4.15:

watchdog: BUG: soft lockup - CPU#206 stuck for 11s! [t_virtual_machi:194348]
CPU: 206 PID: 194348 Comm: t_virtual_machi
RIP: 0010:free_unref_page_list+0x105/0x170
...
Call Trace:
 [<0>] release_pages+0x159/0x3d0
 [<0>] sev_unpin_memory+0x2c/0x50 [kvm_amd]
 [<0>] __unregister_enc_region_locked+0x2f/0x70 [kvm_amd]
 [<0>] svm_vm_destroy+0xa9/0x200 [kvm_amd]
 [<0>] kvm_arch_destroy_vm+0x47/0x200
 [<0>] kvm_put_kvm+0x1a8/0x2f0
 [<0>] kvm_vm_release+0x25/0x30
 [<0>] do_exit+0x335/0xc10
 [<0>] do_group_exit+0x3f/0xa0
 [<0>] get_signal+0x1bc/0x670
 [<0>] do_signal+0x31/0x130

Although the CLFLUSH is no longer issued on every encrypted region to be
unregistered, there are no other changes that can prevent soft lockups for
very large SEV VMs in the latest kernel.

Periodically schedule if necessary.  This still holds kvm->lock across the
resched, but since this only happens when the VM is destroyed this is
assumed to be acceptable.

Signed-off-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm/sev.c | 1 +
 1 file changed, 1 insertion(+)
```
#### [PATCH 1/4] sev/i386: Add initial support for SEV-ES
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11736265
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E831159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:06:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3213D2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:06:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="M82Qy+3a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726556AbgHYTGL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 15:06:11 -0400
Received: from mail-co1nam11on2079.outbound.protection.outlook.com
 ([40.107.220.79]:49711
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726303AbgHYTGJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 25 Aug 2020 15:06:09 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=dNTUSg/BzxrQJeQN1Lk0yWyn1flm6UQuwvT+YtlKEkKqJVDXB3sKTvULP7DwIIvx7ZHDybGTF7b1AG/YBkvhGPVq1MUidIu5JtrIvGGD8gjzS8xK3+94e4tVspUrxGEE4KRezcgvSEyNjmZmLXngAM1mJ60kpPoFvd7j7Ct4BQ9r/sj4mkpdqWoMQHv6xt4VB94TPwBYzCnTdzh645mSG9pBmn4DsWy+7GiT9MFNTWjjQr+1lfBGOY4X3hnAW361PurD1xdf911lJpW9VX/eZJn17Gudafj6oE0thqeZ4j5mVlzWOnXT6amGqRsu+sr07VPDmV0GL/bcW1XxNBoqkA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=DEV843dJZ+BpWDH+gOM/8Io6mBBUm7EKKcCObNRwnOkNxG4VXfTnfH12V/rrkbbnRqTQ1hCQ+3vCGM7GSq0RMxNwJgVb7KVWNLRCwuAWr+vCgzDq2L8yxIIoX/uNXBJCs1EgxMg3HxhRJ7GYyqk6Nfnoibpumx7w5WyvU9YPJQeC3o65BUDtOgeuuFIR/lhRAZcB2tcQibmRtwxV2mbwwVuD1LzQMDKlReDiOsTcEihk1FPebmoXJ/exkecxlHpH3EfoLz8IUMet1wPl8GpJX/0sKr9cXrEAajP15/Ig4giorT1+CjQNI22EB+iP4mSfx7XZR8EMvXmz37Md+zR1mQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=M82Qy+3a5osu+M9iWrXfWqCt4Q6ovsq/0fY57AimJmUc45CHCL2+EqLxJGArbzRQF52vABdFVPBzhdMNPHKvugfitsqfQ/cmw3y3ZxebeS9JNpgoNCfCz8O5HWGM2hCzQvCOn0wPAE1XcsamneEG1H3Whockj4xdMTQQQy+0UBM=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR1201MB0219.namprd12.prod.outlook.com (2603:10b6:4:56::19) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3305.25; Tue, 25 Aug 2020 19:06:06 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3305.026; Tue, 25 Aug 2020
 19:06:06 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>
Subject: [PATCH 1/4] sev/i386: Add initial support for SEV-ES
Date: Tue, 25 Aug 2020 14:05:40 -0500
Message-Id: 
 <88dc46aaedd17a3509d7546a622a9754dad895cb.1598382343.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1598382343.git.thomas.lendacky@amd.com>
References: <cover.1598382343.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: DM5PR12CA0056.namprd12.prod.outlook.com
 (2603:10b6:3:103::18) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 DM5PR12CA0056.namprd12.prod.outlook.com (2603:10b6:3:103::18) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.19 via Frontend
 Transport; Tue, 25 Aug 2020 19:06:05 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0ddc2d9c-82a0-433d-cdcc-08d84929eb1c
X-MS-TrafficTypeDiagnostic: DM5PR1201MB0219:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1201MB02194578774DFC92EFC06EDCEC570@DM5PR1201MB0219.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 DkWYuh3DAgGbkwvY6N0zDEGGnLrPTiyttB/aPom7rWNyU6KhXoCa+JES7AlQzbwpzX9CB4FtARrf37o57ANQtO648QaPdyhzw7kbzy+olcSh1Rju2lpQwzDxrf7PlTWuytO7krX68r+7zMHGx8dpQ4Jf6sihgFBboZW3MMzThwiaMn5tK/7yaHeEgCKPD58j4Msg9z+XTbgi9uy2jFS/dZ6/ra5U5HYWEPQIF/Lm+KFjDyVRSZv4DCb+1l987Od8VFTRs/STRoQI+FfEpkroRBuxQGtuVXm48fhQld1uYYAEusMNSq00BYAecSpn4ru2GCbDINHYBp4EsPM73bBiAxva7ygdFgVBEePoSxQhqkgxz7i+YnRJL3ZuJCPW4Xet3iALUsA3K+kpThZsjLaCpRqHK8rpm8KkGKPxJm4eqn8=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(136003)(376002)(39860400002)(366004)(346002)(4326008)(186003)(86362001)(8676002)(83380400001)(54906003)(16576012)(8936002)(6486002)(316002)(478600001)(36756003)(52116002)(26005)(6666004)(66556008)(2616005)(66476007)(66946007)(956004)(2906002)(5660300002)(136400200001)(309714004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 p7myolQbTVCGy+rCIbIy9j9eW4HKvjP0mF9pvwIJ0vIAI7rjWGvlwYeNraOpydLV6YdigRW34S15Z02gFF3np6IASPUPrhB3myGJypURXtQanDErxeA2tPpGO6X/8leH3/yAaMZWT3bviziLv2nAB36etu2ocv9eP0ebCxhvhRLoeccTIaYaZK5P+k2vSfMz9I1EigeQnH1hErw6NNaSAkU2rmNK8OZqNXwI4f0JOPJRioXX/w94NsXvOUqssy/IY5CsqsNG8HUJOy2pBeY7/N8dcJi4xB1RmLbGneBkwipWFSFpDJBIzHRiK5DAkh2RT+7Ki8zFT6oSZGkszLcQE5+LipGb0l2+hH6zKCKoSXM9wmWdQWpa7LJLbW8nLXi/sckD6gyN3ruMLAlMDyhm1uXxPnWl3OWjodAK1U0v0xtpwoB9Dxu6DYziEn91N8YOvii38PD7EtxMg2hoGyWmtwDK29CzCtm9SJ6SBbKQFwS4FMP/vv1AFAUINU0gJt4/ZlTw5Z5nPVE4NH2fVuAzxdMcgezlP0m1HMJmCXEDDurcllYA/AvllReLMlD2WB+SN8TA27970wPC3GYzprq5bTP9Y0G2Ze6RC8JVcFDpFfzWrpuhGsJs1IP4tF2lfY8TbR5tU48WmpXqN+E3cFYr0Q==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0ddc2d9c-82a0-433d-cdcc-08d84929eb1c
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 25 Aug 2020 19:06:06.2874
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 y8XaMQylx0Z9UlituBiJIcmFv2XuzITUrNwiRXmh2Jqu24apH7ziFH2W4KQvyZO1ifj4m9tbCw8LpJcpdDebCw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1201MB0219
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Provide initial support for SEV-ES. This includes creating a function to
indicate the guest is an SEV-ES guest (which will return false until all
support is in place), performing the proper SEV initialization and
ensuring that the guest CPU state is measured as part of the launch.

Co-developed-by: Jiri Slaby <jslaby@suse.cz>
Signed-off-by: Jiri Slaby <jslaby@suse.cz>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 target/i386/cpu.c      |  1 +
 target/i386/sev-stub.c |  5 +++++
 target/i386/sev.c      | 46 ++++++++++++++++++++++++++++++++++++++++--
 target/i386/sev_i386.h |  1 +
 4 files changed, 51 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/2] runtime.bash: remove outdated comment
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11735481
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48EA4722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 10:21:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 320662068F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 10:21:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="GEK0fDXg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729803AbgHYKVB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 06:21:01 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3988 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729653AbgHYKVA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 25 Aug 2020 06:21:00 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07PA1xGj169229
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=s6jg51TymRoMGZ3NFB7GYH4/t2bnpPS6wJ6yvbwFgd4=;
 b=GEK0fDXg1AFxZmrLXRpOVeo9afBI+ko0kgThBKg/e5xO+zjL+KpIPl2LS+vCraP9S3tC
 2o+JkxZfsEw1zV8RlbQFkobafYOJSD3giTNqal62wHbUFmBTHiglevrUUnbtKmfMqHdf
 pw31qR3Job6Pi5zPO9QQRvDS0aLeg0bhZH+4Vc3IeiDUGFlhFRG04/KAim3HS4UYTyr3
 Q05z7Ta3mjthMeVIvfGaIYJNwj9sDLL+UEZKIAt3PHNecQOe110zzh2Dfe2GOjarjHKC
 E0SsefNkadwPvly6RvXMQrX3+XnJNus8GrgxO8kbiSCETH8krejruLeAdnRxor+KLYkE yg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 334xpm3f8m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:59 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07PA2ZDm171021
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:58 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 334xpm3f87-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 25 Aug 2020 06:20:58 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07PAF3qN022643;
        Tue, 25 Aug 2020 10:20:56 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06ams.nl.ibm.com with ESMTP id 332uk6baka-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 25 Aug 2020 10:20:56 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07PAKsaZ31523304
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 25 Aug 2020 10:20:54 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2E3DEA405B;
        Tue, 25 Aug 2020 10:20:54 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BA3FCA4057;
        Tue, 25 Aug 2020 10:20:53 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.56.167])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 25 Aug 2020 10:20:53 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH v2 1/2] runtime.bash: remove outdated comment
Date: Tue, 25 Aug 2020 12:20:35 +0200
Message-Id: <20200825102036.17232-2-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200825102036.17232-1-mhartmay@linux.ibm.com>
References: <20200825102036.17232-1-mhartmay@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-25_02:2020-08-24,2020-08-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxscore=0
 mlxlogscore=999 suspectscore=0 bulkscore=0 clxscore=1015
 lowpriorityscore=0 impostorscore=0 spamscore=0 adultscore=0
 priorityscore=1501 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2008250073
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 6e1d3752d7ca ("tap13: list testcases individually") the
comment is no longer valid. Therefore let's remove it.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 scripts/runtime.bash | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH] vhost-iotlb: fix vhost_iotlb_itree_next() documentation
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11735703
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8714A1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 13:05:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67BE420738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 13:05:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QLEDpf1d"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727781AbgHYNFx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 09:05:53 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:27411 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725792AbgHYNFw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 25 Aug 2020 09:05:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598360751;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=44/rFMQFZre8hi2KWPAM7jK3g3yR2EVE42MjQnT9WTk=;
        b=QLEDpf1dXoLdUO9KKLWclsZuqPUxNZg06Ora59qIv1iAtJw66brvSeUbq16AEvb2gqg9hM
        9qq3uODIT4YAdgcbvaCu9VSnc/vz1z2lwK88+tEUrbV9aV29lChsJNeTWa5Pwroh84Z0xc
        K1plRjekP6Em3nA72ayJkHxo+k3rquQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-uof_C0V9OaSdF-Gh1snzxw-1; Tue, 25 Aug 2020 09:05:50 -0400
X-MC-Unique: uof_C0V9OaSdF-Gh1snzxw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 21FBD84639C;
        Tue, 25 Aug 2020 13:05:49 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-152.ams2.redhat.com
 [10.36.113.152])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 053F960C0F;
        Tue, 25 Aug 2020 13:05:44 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH] vhost-iotlb: fix vhost_iotlb_itree_next() documentation
Date: Tue, 25 Aug 2020 15:05:43 +0200
Message-Id: <20200825130543.43308-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch contains trivial changes for the vhost_iotlb_itree_next()
documentation, fixing the function name and the description of
first argument (@map).

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/iotlb.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
