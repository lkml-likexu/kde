#### [PATCH] KVM: PPC: Book3S HV: Don't do ultravisor calls on systems without ultravisor
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11299535
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ACAF913B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 05:11:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7EB2B206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 05:11:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="Sf+V97fQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726212AbfLRFLk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 00:11:40 -0500
Received: from ozlabs.org ([203.11.71.1]:51191 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725797AbfLRFLk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 00:11:40 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 47d35Q0Hx6z9sRl; Wed, 18 Dec 2019 16:11:37 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1576645898; bh=93N8VOo8SCifT0RoMTSN2PKiLco93mZr6cUDSYI7iGY=;
        h=Date:From:To:Subject:From;
        b=Sf+V97fQIP+xjVTfXjs7QkPY6KUzLk6WUv1oXQAOBYy6EjkoxncqrxBgGe8uyoqlO
         zOHjE/FaRl3eVq1L0RC82EYbBbDI3TSkYmR3ehw59Ux9gptGj06yuK8nepILjhsXQP
         OrplO34urCMEM1VWcqzH12kTWwvEP6YLzPguMCznTb4EDf5W7SKrI7n3QsZ/XJbBkS
         QkvYcuSYaiiUZAw3cPpQEwoVzFFaUYkunNGIMGAEqA0blCcrC5FtZZAj9B3vvvjGWy
         Xotr5chWd51m+6TB3oyyGN9jkq73n0jqo783Hk4dMccFwZtcoRG9/6/MbAaXllELIG
         mMvqpTcqK2dGA==
Date: Wed, 18 Dec 2019 16:11:30 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org, kvm-ppc@vger.kernel.org
Subject: [PATCH] KVM: PPC: Book3S HV: Don't do ultravisor calls on systems
 without ultravisor
Message-ID: <20191218051130.GA29890@oak.ozlabs.ibm.com>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 22945688acd4 ("KVM: PPC: Book3S HV: Support reset of secure
guest") added a call to uv_svm_terminate, which is an ultravisor
call, without any check that the guest is a secure guest or even that
the system has an ultravisor.  On a system without an ultravisor,
the ultracall will degenerate to a hypercall, but since we are not
in KVM guest context, the hypercall will get treated as a system
call, which could have random effects depending on what happens to
be in r0, and could also corrupt the current task's kernel stack.
Hence this adds a test for the guest being a secure guest before
doing uv_svm_terminate().

Fixes: 22945688acd4 ("KVM: PPC: Book3S HV: Support reset of secure guest")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/45] KVM: PPC: Book3S HV: Uninit vCPU if vcore creation fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11302045
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15E1E6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 21:55:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F10B424680
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 21:55:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726694AbfLRVze (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 16:55:34 -0500
Received: from mga02.intel.com ([134.134.136.20]:54823 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726530AbfLRVze (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 16:55:34 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Dec 2019 13:55:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,330,1571727600";
   d="scan'208";a="222108004"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 18 Dec 2019 13:55:32 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, James Hogan <jhogan@kernel.org>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Greg Kurz <groug@kaod.org>
Subject: [PATCH v2 01/45] KVM: PPC: Book3S HV: Uninit vCPU if vcore creation
 fails
Date: Wed, 18 Dec 2019 13:54:46 -0800
Message-Id: <20191218215530.2280-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191218215530.2280-1-sean.j.christopherson@intel.com>
References: <20191218215530.2280-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Call kvm_vcpu_uninit() if vcore creation fails to avoid leaking any
resources allocated by kvm_vcpu_init(), i.e. the vcpu->run page.

Fixes: 371fefd6f2dc4 ("KVM: PPC: Allow book3s_hv guests to use SMT processor modes")
Cc: stable@vger.kernel.org
Reviewed-by: Greg Kurz <groug@kaod.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/powerpc/kvm/book3s_hv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Clean up the spaces redundant.
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11299665
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B40B1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 07:37:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1922A24679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 07:37:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="DKDNn88w"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726545AbfLRHg6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 02:36:58 -0500
Received: from mail-pf1-f194.google.com ([209.85.210.194]:46803 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725799AbfLRHg6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 02:36:58 -0500
Received: by mail-pf1-f194.google.com with SMTP id y14so719504pfm.13;
        Tue, 17 Dec 2019 23:36:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=pg4QWq+v6GL4Rqi0KrNkbBy7ChOwtldNf1BCqo0xgwg=;
        b=DKDNn88wkruXoKMY1NzZ+hXIuRTXdUdicFpgelALcHp9N4xyLCsxLi5GwVSTFTLFPB
         NuNjJZNsFTtBWqAQybCg4hv2eZJQJiLs+Cn4EsUzKfXBsMTbWLkxKopWRDO+7AYORErt
         na5p8Q0Y3ZEbZPYoHMFBGk/lNnBJoADJdIj+ootuVfG0vnS8BhysFdAV/xR2rZ4rJV8f
         ND46h0fXkMgjBGmS1t5Uc9YeVJdu3koRvqxoxTO/NsC/k6uQxmki3l0lR6S1HX9b8b0h
         ofkdTxibe6A7We+wtvJNjjVyfeyVIceOjFHj29uVo6fWWi5hi9WgGbB2AE3kvPje6ZNx
         ZfUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=pg4QWq+v6GL4Rqi0KrNkbBy7ChOwtldNf1BCqo0xgwg=;
        b=X1hNL8Paq0bO7Vzb1aled7yUT8pbjl9iQ9EvVsBJO7x946+Q2krN6m3YoApF6aY2Td
         TuPUU6TK56FswjlVwUJKmTNNTDpwsrfi4sJz6pQwPTw2cEQig5e9DFQUZebjmr86dVJ1
         TQZz9qtqnl3VtuddftoPo776HHc4NJs3Vgp0ii186gx09wdx5XVwCcGNtDqL4P8wTx+f
         YjAmomH0llsB9RtnLSPlhOIUIyjAl9uvZvwkMAKZHyR8ZnSMtzzt2AaN5lWudGVOBfRj
         q5pJj2trekDNAvUWc2s6E/DSLdjFkIqJ5A7mFHZdqBUXEiqA63ielbtNDOq/sm3qsOyw
         9H+A==
X-Gm-Message-State: APjAAAXY9V8cPTlGzIHWwIQDlR6HuE6OQbkJJNS0hLSicd8hieY0x/+t
        RiXC+8Sh5nWbojTpUXiZiQ==
X-Google-Smtp-Source: 
 APXvYqykzcjQaYHwHiQ0EjzUn6HtCHp8hGSiRRNg6WpcmmBHBfrcz8LxD6SEJ0MBpJ8PhtL88V8d/w==
X-Received: by 2002:a62:1857:: with SMTP id 84mr1485263pfy.257.1576654617070;
        Tue, 17 Dec 2019 23:36:57 -0800 (PST)
Received: from [127.0.0.1] ([203.205.141.36])
        by smtp.gmail.com with ESMTPSA id j3sm1697366pfi.8.2019.12.17.23.36.52
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Tue, 17 Dec 2019 23:36:56 -0800 (PST)
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, hpa@zytor.com
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: VMX: Clean up the spaces redundant.
Message-ID: <5c33f601-0bee-7958-7295-541b87b95138@gmail.com>
Date: Wed, 18 Dec 2019 15:36:35 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.3.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From 6b2634f16cfd5d48896a7c0a094b59410ce078c5 Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Wed, 18 Dec 2019 15:21:10 +0800
Subject: [PATCH] Clean up the spaces redundant.

Clean up the spaces redundant in vmx.c.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
  arch/x86/kvm/vmx/vmx.c | 2 +-
  1 file changed, 1 insertion(+), 1 deletion(-)

--
1.8.3.1

```
#### [PATCH v1 1/2] KVM: x86/mmu: Allow for overriding MMIO SPTE mask
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11301811
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 984E3109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 19:46:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62579227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 19:46:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="vvHo6vw/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727526AbfLRTqF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 14:46:05 -0500
Received: from mail-dm6nam11on2076.outbound.protection.outlook.com
 ([40.107.223.76]:1696
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726831AbfLRTqD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 14:46:03 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=m1jhN/CsMzbEf3V5BSXymJz15qm6iUzjPCx3Kv36wLE6CLNAiV6x2XZAw+MyRk3El5vyOd9fhTExPpz6qJqv2sncAPI0bKSoLVuj7Uj3wimFqeXDKOOf4lVgPrwv9fecD0NOQYkh169PHKGc+qXeWYGSlfGo2p42ycOeo7CEmRMQKEdDgckqd3kxpkjU0gMa72Z/Rb8Rh0Z3zX/aXD/ORRmUGgIWRZM7ZITWhuabzP2D4+Bsl1ylK23jJ7Vl3lDpmxXQrSimtxXu8K3FIuyEUkHLRibSIx4+JoeBJCPUv8T+8xb2sj9LOiFujMzkrraMJHOTjcT7Yqq7nukwpQQ7Ww==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4n7QwQXGNQ6ppLI/MVD8trVnB8lmkWVFEwS1QvP80UQ=;
 b=Z/OAhSHgiW0naw7ncY1svQJtOy5wYvGH5+2lS3hbjJmdIEHJUphoyDRfdf4g6kJju9wO4Rswzb/p/v8z5HDVQNlqcim3G7L6mYs82ShHMyaP+Pela4j9VYfwbDhYrqOzraO1QoyGLeCay0cgSwBD49e4HTjlSZkLbWfa7V2CjSyh1anHePTd3RDT9Iau985SwOi0MKmdUtSH+kabYraWfZ7hnn9vLoA0U70wV73S7xJzDWP8z53vsDvjTn7rxFECuFXEYlQySB2GLxu8FrrjxQZiiwzZl8lGocUh5WlcT6qbac10IBKlKFC1fbFgYOs9t6IfvuZY6MFivTz6gg9tDw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4n7QwQXGNQ6ppLI/MVD8trVnB8lmkWVFEwS1QvP80UQ=;
 b=vvHo6vw/4bB19Ct2RXOKIqrXhcuxef4DSNpfwaK3P+nQM8QAU9LgA2X6b23zklEWKP5G1ZvcNhPoCFCJCkiTH0RYu0hYESjkG1Oc5SekXo8jazHqmTQSsJ6RCMWvIm2Y2G2zfhyUBP/XwWZ3fiSE7dazgQlGiyQnez+ttc7vNus=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.71.154) by
 DM6PR12MB2876.namprd12.prod.outlook.com (20.179.71.85) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2559.14; Wed, 18 Dec 2019 19:46:01 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270%7]) with mapi id 15.20.2538.019; Wed, 18 Dec 2019
 19:46:01 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v1 1/2] KVM: x86/mmu: Allow for overriding MMIO SPTE mask
Date: Wed, 18 Dec 2019 13:45:46 -0600
Message-Id: 
 <10fdb77c9b6795f68137cf4315571ab791ab6feb.1576698347.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1576698347.git.thomas.lendacky@amd.com>
References: <cover.1576698347.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: DM6PR21CA0007.namprd21.prod.outlook.com
 (2603:10b6:5:174::17) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:15e::26)
MIME-Version: 1.0
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 8b8ce194-c421-47db-80da-08d783f2e8e0
X-MS-TrafficTypeDiagnostic: DM6PR12MB2876:|DM6PR12MB2876:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB28767ED9BED1F9AD881F1B28EC530@DM6PR12MB2876.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-Forefront-PRVS: 0255DF69B9
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(136003)(376002)(346002)(39860400002)(366004)(189003)(199004)(478600001)(5660300002)(81156014)(66946007)(81166006)(6486002)(6512007)(186003)(52116002)(54906003)(36756003)(86362001)(6666004)(4326008)(8676002)(66476007)(8936002)(66556008)(2616005)(6506007)(2906002)(26005)(316002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB2876;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 vAZCAzc2kqxErVv/335x8QtK+oyaJTgp0fCoY3B6Pc5kD4rb2GP2KqBlTXZVGF0rUEvEVyF46V7aZ7qP8GVqMLjglQBdGODEweSsNQUIm+OVBACFUW66RcVJRK3sBkBlp7lJp+e3asK8nH3KsQCN6n5SvkaWNGrVZrg5XQLOvMjL9RJxChvTD9kgzMOgAEBQnreUGvk0zFCl2XqlOnqJeNx4pXcTHH1yjiAJ+EFibriIjd3QDCNSnq90zZb0mNzZNaZJv7O+OmIx5kY7GqgwaR5GBGZt9EKCivJmm01Jr6Pnpc6hpc90XS94FdYRt3RuI3NZH3X8OozRQB4m2Q1CEJ3Ld32qXXVVgHbD0Xp7LxgB6gVvZW/p8Ny0W7BwutSvYFrWVJn0PiGS5VbtUgXb0G1ay4AjedEHC76NwKZanMD2R5p45VLTim0togeoldl/
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8b8ce194-c421-47db-80da-08d783f2e8e0
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 18 Dec 2019 19:46:01.0684
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 pS9fcRgxUbjg9ob29U0vR1XSjbg+dMX3ppBwuUfkUrRTGuJpNJ2DGoE8gGQFSn0K6SzmPa1qL89VZiS45xAK8w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2876
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM MMIO support uses bit 51 as the reserved bit to cause nested page
faults when a guest performs MMIO. The AMD memory encryption support uses
CPUID functions to define the encryption bit position. Given this, KVM
can't assume that bit 51 will be safe all the time.

Add a callback to return a reserved bit(s) mask that can be used for the
MMIO pagetable entries. The callback is not responsible for setting the
present bit.

If a callback is registered:
  - any non-zero mask returned is updated with the present bit and used
    as the MMIO SPTE mask.
  - a zero mask returned results in a mask with only bit 51 set (i.e. no
    present bit) as the MMIO SPTE mask, similar to the way 52-bit physical
    addressing is handled.

If no callback is registered, the current method of setting the MMIO SPTE
mask is used.

Fixes: 28a1f3ac1d0c ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/kvm_host.h |  4 ++-
 arch/x86/kvm/mmu/mmu.c          | 54 +++++++++++++++++++++------------
 arch/x86/kvm/x86.c              |  2 +-
 3 files changed, 38 insertions(+), 22 deletions(-)

```
#### [RFC PATCH] KVM: x86: Disallow KVM_SET_CPUID{2} if the vCPU is in guest mode
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11301535
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60DF7139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:43:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 47D002082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:43:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727188AbfLRRnB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 12:43:01 -0500
Received: from mga05.intel.com ([192.55.52.43]:57072 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726939AbfLRRnB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 12:43:01 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Dec 2019 09:42:56 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,330,1571727600";
   d="scan'208";a="298450983"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 18 Dec 2019 09:42:56 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Weijiang Yang <weijiang.yang@intel.com>
Subject: [RFC PATCH] KVM: x86: Disallow KVM_SET_CPUID{2} if the vCPU is in
 guest mode
Date: Wed, 18 Dec 2019 09:42:55 -0800
Message-Id: <20191218174255.30773-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reject KVM_SET_CPUID{2} with -EBUSY if the vCPU is in guest mode (L2) to
avoid complications and potentially undesirable KVM behavior.  Allowing
userspace to change a guest's capabilities while L2 is active would at
best result in unexpected behavior in the guest (L1 or L2), and at worst
induce bad KVM behavior by breaking fundamental assumptions regarding
transitions between L0, L1 and L2.

Cc: Jim Mattson <jmattson@google.com>
Cc: Weijiang Yang <weijiang.yang@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

This came up in the context of the CET series, where passing through MSRs
to L1 depends on the CPUID-based capabilities of the guest[*].  The CET
problem is solvable, but IMO unnecessarily complex.   And I'm more
concerned that userspace would be able to induce bad behavior in KVM by
changing core capabilites while L2 is active, e.g. VMX, LM, LA57, etc...

Tagged RFC as this is an ABI change, though I highly doubt it actually
affects a real world VMM.

[*] https://lkml.kernel.org/r/20191218160228.GB25201@linux.intel.com/

 arch/x86/kvm/x86.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH kvm-unit-tests 1/2] svm: introduce prepare_gif_clear callback
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11301519
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF03D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:33:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 893A62146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:33:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="HWE0bK2g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727262AbfLRRdK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 12:33:10 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:37481 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727025AbfLRRdK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 12:33:10 -0500
Received: by mail-wr1-f67.google.com with SMTP id w15so3209599wru.4
        for <kvm@vger.kernel.org>; Wed, 18 Dec 2019 09:33:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=5H1LnabRffeELO1OACrfjCbx1g2hP9mrXvmG6Zih1E8=;
        b=HWE0bK2g50SjgkayGbT22suu7Ebcza0C05oksNWz9YVd+PEhRn3Tjzz2o7wncEUq0n
         4QMOZ/aKZuFEg9XUVh+oEYAyMPg3KsY6L+0qSPHZ7T4K5z0ULoamF8s8V4aSa/yudMBY
         QUUDSxdW7P4IMXFBr10xKw1hcGw01lwtucaH38zOZ+Lt6XM9OyV1A2YpU9Ezln6G8Fgk
         Ijxw6zsB90Wu2mmgbc+sbY6iqDU8dOcEb8OICcTgnkewxF4EufKvPUb7RTe9DQT8cWsm
         dFw9HSPX1/p2mTIx6nCqratzjNxs+/HO9flb/Y9DUf7VmkSz2SNdBbYhcUJvOKRbNcFc
         je9A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=5H1LnabRffeELO1OACrfjCbx1g2hP9mrXvmG6Zih1E8=;
        b=tlphhBfKXvbgVgXARjNl8+l9/JAWa2CHEdUPfsYu3ARJU/nVBdNcVRmRwFvX7r0dqH
         5K5POaiG8MlmMNJzXVGZ0vlh64XUSnc/4BpXW4mKhE+6/yYnRyyaIaHYVFvj36/ZTaY7
         Q/TcE5d4FoFs+Jj/i175t8wxYqzsXtTxUW8CVF5BCK0PItPqx2P8qJEUZ/712vMYDnSs
         org5vxVLG0HAMgHO3eP5ac87sUJmND/kt8zvKK6G02xKddbC6sEVcHQ48PkhA93XmM53
         o7IZLOWOgNQHK3xrAJSbQjd6jENwmolYkuS5eYjLLdTZpMmvznxfYX8IhrCjD91kNfID
         +GhQ==
X-Gm-Message-State: APjAAAXKO/7xRY1fQ7b7o6krvg9ND0grxM5tUcRClhSaVktTycsigTAH
        1ieKZHtMxk9s4hT3GdWXl2T/vxJr
X-Google-Smtp-Source: 
 APXvYqxSrz78wE88ROaOoh8bNKTp7NJ5SyEMphWt3ZBo84VCD1H3ZM4XmjTbg9JhY4cwruC4qA/fSg==
X-Received: by 2002:adf:f78d:: with SMTP id q13mr4124961wrp.365.1576690386995;
        Wed, 18 Dec 2019 09:33:06 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 u22sm3411362wru.30.2019.12.18.09.33.06
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Dec 2019 09:33:06 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] svm: introduce prepare_gif_clear callback
Date: Wed, 18 Dec 2019 18:33:02 +0100
Message-Id: <1576690383-16170-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1576690383-16170-1-git-send-email-pbonzini@redhat.com>
References: <1576690383-16170-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Generalize the set_host_if flag that was added recently, by introducing
a new callback that is called with GIF=0 && IF=1.  This is useful to
inject events that will trigger right after VMRUN.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.c | 124 ++++++++++++++++++++++++++++++++++++++++----------------------
 1 file changed, 81 insertions(+), 43 deletions(-)

```
#### [PATCH] vfio/mdev: make create attribute static
##### From: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>
X-Patchwork-Id: 11300521
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E614313A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 12:31:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CDA202176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 12:31:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726824AbfLRMbb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 07:31:31 -0500
Received: from imap2.colo.codethink.co.uk ([78.40.148.184]:40550 "EHLO
        imap2.colo.codethink.co.uk" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726029AbfLRMbb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Dec 2019 07:31:31 -0500
Received: from [167.98.27.226] (helo=rainbowdash.codethink.co.uk)
        by imap2.colo.codethink.co.uk with esmtpsa  (Exim 4.92 #3 (Debian))
        id 1ihYU4-0002im-NY; Wed, 18 Dec 2019 12:31:20 +0000
Received: from ben by rainbowdash.codethink.co.uk with local (Exim 4.92.3)
        (envelope-from <ben@rainbowdash.codethink.co.uk>)
        id 1ihYU4-00Apur-7O; Wed, 18 Dec 2019 12:31:20 +0000
From: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>
To: ben.dooks@codethink.co.uk
Cc: Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vfio/mdev: make create attribute static
Date: Wed, 18 Dec 2019 12:31:19 +0000
Message-Id: <20191218123119.2582802-1-ben.dooks@codethink.co.uk>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The create attribute is not exported, so make it
static to avoid the following sparse warning:

drivers/vfio/mdev/mdev_sysfs.c:77:1: warning: symbol 'mdev_type_attr_create' was not declared. Should it be static?

Signed-off-by: Ben Dooks (Codethink) <ben.dooks@codethink.co.uk>
---
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
---
 drivers/vfio/mdev/mdev_sysfs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio: platform: fix __iomem in vfio_platform_amdxgbe.c
##### From: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>
X-Patchwork-Id: 11300791
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C73AD6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 13:35:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE28C227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 13:35:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727145AbfLRNfg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 08:35:36 -0500
Received: from imap2.colo.codethink.co.uk ([78.40.148.184]:43398 "EHLO
        imap2.colo.codethink.co.uk" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726735AbfLRNfg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Dec 2019 08:35:36 -0500
Received: from [167.98.27.226] (helo=rainbowdash.codethink.co.uk)
        by imap2.colo.codethink.co.uk with esmtpsa  (Exim 4.92 #3 (Debian))
        id 1ihZU8-0004Uz-Ll; Wed, 18 Dec 2019 13:35:28 +0000
Received: from ben by rainbowdash.codethink.co.uk with local (Exim 4.92.3)
        (envelope-from <ben@rainbowdash.codethink.co.uk>)
        id 1ihZU6-00Awcg-Pc; Wed, 18 Dec 2019 13:35:26 +0000
From: "Ben Dooks (Codethink)" <ben.dooks@codethink.co.uk>
To: ben.dooks@codethink.co.uk
Cc: Eric Auger <eric.auger@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Allison Randal <allison@lohutok.net>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vfio: platform: fix __iomem in vfio_platform_amdxgbe.c
Date: Wed, 18 Dec 2019 13:35:25 +0000
Message-Id: <20191218133525.2608583-1-ben.dooks@codethink.co.uk>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ioaddr should have __iomem marker on it, so add that to fix
the following sparse warnings:

drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:33:44: warning: incorrect type in argument 2 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:33:44:    expected void volatile [noderef] <asn:2> *addr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:33:44:    got void *
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:34:33: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:34:33:    expected void const volatile [noderef] <asn:2> *addr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:34:33:    got void *
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:44:44: warning: incorrect type in argument 2 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:44:44:    expected void volatile [noderef] <asn:2> *addr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:44:44:    got void *
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:45:33: warning: incorrect type in argument 2 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:45:33:    expected void volatile [noderef] <asn:2> *addr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:45:33:    got void *
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:69:41: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:69:41:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:69:41:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:71:30: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:71:30:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:71:30:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:76:49: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:76:49:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:76:49:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:85:37: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:85:37:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:85:37:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:87:30: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:87:30:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:87:30:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:90:30: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:90:30:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:90:30:    got void [noderef] <asn:2> *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:93:30: warning: incorrect type in argument 1 (different address spaces)
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:93:30:    expected void *ioaddr
drivers/vfio/platform/reset/vfio_platform_amdxgbe.c:93:30:    got void [noderef] <asn:2> *ioaddr

Signed-off-by: Ben Dooks (Codethink) <ben.dooks@codethink.co.uk>
Acked-by: Eric Auger <eric.auger@redhat.com>
---
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Allison Randal <allison@lohutok.net>
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
---
 drivers/vfio/platform/reset/vfio_platform_amdxgbe.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH net-next v3 01/11] VSOCK: fix header include in vsock_diag_test
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11301571
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52944139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 18:07:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 308BB2072B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 18:07:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VmpakIWa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727380AbfLRSHY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 13:07:24 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:52929 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727346AbfLRSHY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 13:07:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576692443;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Ak7zDmp1/cfdOQnn19i2bAKVAQPiklhpPuuaiXWuaLc=;
        b=VmpakIWa/jcrYN620jT3HHVjYB/8IVFpU9v95zWIy4/XsMolDr4DSEHSyFN8t5DcUPHXjy
        0bIvgcTl4ysMykcCtIR0y59SrhPVj4fMbRxarX2hf0cWRxpqn7IUMzCpc8mZlaV4ZsEdVk
        lEnf6NZQAFHLzFbsa9Du5EZSy+kqBUU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-411-WFFPBcoKMuGlKOSiuW5jFg-1; Wed, 18 Dec 2019 13:07:20 -0500
X-MC-Unique: WFFPBcoKMuGlKOSiuW5jFg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 896C6100726C;
        Wed, 18 Dec 2019 18:07:18 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-218.ams2.redhat.com
 [10.36.117.218])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6E5F45D9E2;
        Wed, 18 Dec 2019 18:07:16 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Jorgen Hansen <jhansen@vmware.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Dexuan Cui <decui@microsoft.com>, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Stefano Garzarella <sgarzare@redhat.com>
Subject: [PATCH net-next v3 01/11] VSOCK: fix header include in
 vsock_diag_test
Date: Wed, 18 Dec 2019 19:06:58 +0100
Message-Id: <20191218180708.120337-2-sgarzare@redhat.com>
In-Reply-To: <20191218180708.120337-1-sgarzare@redhat.com>
References: <20191218180708.120337-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Stefan Hajnoczi <stefanha@redhat.com>

The vsock_diag_test program directly included ../../../include/uapi/
headers from the source tree.  Tests are supposed to use the
usr/include/linux/ headers that have been prepared with make
headers_install instead.

Suggested-by: David S. Miller <davem@davemloft.net>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 tools/testing/vsock/Makefile          | 2 +-
 tools/testing/vsock/README            | 2 +-
 tools/testing/vsock/vsock_diag_test.c | 5 ++---
 3 files changed, 4 insertions(+), 5 deletions(-)

```
