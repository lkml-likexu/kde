#### [PATCH v5 1/3] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11705831
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5BECC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 15:57:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CC7F2075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 15:57:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="XrKWKOYg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726787AbgHGP5N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 11:57:13 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:31753 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725934AbgHGP5M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 11:57:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596815830; x=1628351830;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=Bg7hRp7sRiWFUZtCI5+UC7qe4/5M/mFKmMXNc5u3nv8=;
  b=XrKWKOYg/Rwy2/uKOz0ApwAuo/Z6Y0MpMsCD/oZP4oDx1CYZKxbn1KJL
   SoVW/SdjXebVgXuEuA0JNWyNF7mt1moJ+I0wJJlU9MO/xJIOfUKKAQGax
   4uQ+OwFNL6w7COVOk5J3jO/3MT2nLafi+2n+Pcb29zf9nf58RHrvUqC+j
   0=;
IronPort-SDR: 
 9eJVMCWx6l7tfnv/Bn7yrtWDGkA3M18GePK1LN+SHvnPs3HNMfXFKXn1nq9/tStLOid1wLY/hk
 bVWLYjUindng==
X-IronPort-AV: E=Sophos;i="5.75,446,1589241600";
   d="scan'208";a="66368473"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 07 Aug 2020 15:57:07 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com (Postfix) with
 ESMTPS id C8952A201F;
        Fri,  7 Aug 2020 15:57:02 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 7 Aug 2020 15:57:01 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.140) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 7 Aug 2020 15:56:58 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v5 1/3] KVM: x86: Deflect unknown MSR accesses to user space
Date: Fri, 7 Aug 2020 17:56:46 +0200
Message-ID: <20200807155648.8602-2-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200807155648.8602-1-graf@amazon.com>
References: <20200807155648.8602-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.162.140]
X-ClientProxiedBy: EX13D29UWA001.ant.amazon.com (10.43.160.187) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSRs are weird. Some of them are normal control registers, such as EFER.
Some however are registers that really are model specific, not very
interesting to virtualization workloads, and not performance critical.
Others again are really just windows into package configuration.

Out of these MSRs, only the first category is necessary to implement in
kernel space. Rarely accessed MSRs, MSRs that should be fine tunes against
certain CPU models and MSRs that contain information on the package level
are much better suited for user space to process. However, over time we have
accumulated a lot of MSRs that are not the first category, but still handled
by in-kernel KVM code.

This patch adds a generic interface to handle WRMSR and RDMSR from user
space. With this, any future MSR that is part of the latter categories can
be handled in user space.

Furthermore, it allows us to replace the existing "ignore_msrs" logic with
something that applies per-VM rather than on the full system. That way you
can run productive VMs in parallel to experimental ones where you don't care
about proper MSR handling.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code

v3 -> v4:

  - Mention exit reasons in re-inter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
---
 Documentation/virt/kvm/api.rst  |  66 +++++++++++++++++++-
 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/emulate.c          |  18 +++++-
 arch/x86/kvm/x86.c              | 106 ++++++++++++++++++++++++++++++--
 include/trace/events/kvm.h      |   2 +-
 include/uapi/linux/kvm.h        |  10 +++
 6 files changed, 196 insertions(+), 9 deletions(-)

```
#### [RFC 1/7] KVM: VMX: Introduce PKS VMCS fields
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11705167
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12DC7913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:46:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 084BE206B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:46:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727843AbgHGIqs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 04:46:48 -0400
Received: from mga06.intel.com ([134.134.136.31]:65145 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726382AbgHGIqr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 04:46:47 -0400
IronPort-SDR: 
 9lUVoQ61V38JDQuZP/R0iCzRx94K6gKM0LbYE3q/Tzc0JnJAjY5tx/EDUw5PNnivqRTYb22y8C
 1+kdfYdB0TpQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9705"; a="214565718"
X-IronPort-AV: E=Sophos;i="5.75,445,1589266800";
   d="scan'208";a="214565718"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Aug 2020 01:46:46 -0700
IronPort-SDR: 
 95lBwmMTRHBuGxcPLquYgJLSzAWQtRulQ1T7PQhLt3uMioPI148jKqrntGjoyKziS0e8AFeB2V
 Fljic4D8ECSw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,445,1589266800";
   d="scan'208";a="307317144"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga002.jf.intel.com with ESMTP; 07 Aug 2020 01:46:44 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC 1/7] KVM: VMX: Introduce PKS VMCS fields
Date: Fri,  7 Aug 2020 16:48:35 +0800
Message-Id: <20200807084841.7112-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200807084841.7112-1-chenyi.qiang@intel.com>
References: <20200807084841.7112-1-chenyi.qiang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PKS(Protection Keys for Supervisor Pages) is a feature that extends the
Protection Key architecture to support thread-specific permission
restrictions on supervisor pages.

A new PKS MSR(PKRS) is defined in kernel to support PKS, which holds a
set of permissions associated with each protection domian.

Two VMCS fields {HOST,GUEST}_IA32_PKRS are introduced in
{host,guest}-state area to store the value of PKRS.

Every VM exit saves PKRS into guest-state area.
If VM_EXIT_LOAD_IA32_PKRS = 1, VM exit loads PKRS from the host-state
area.
If VM_ENTRY_LOAD_IA32_PKRS = 1, VM entry loads PKRS from the guest-state
area.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/include/asm/vmx.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: SVM: Mark SEV launch secret pages as dirty.From: Cfir Cohen <cfir@google.com>
##### From: Cfir Cohen <cfir@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cfir Cohen <cfir@google.com>
X-Patchwork-Id: 11704611
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E155138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 01:23:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78A5822CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 01:23:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dbhUZ4Ad"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726242AbgHGBXZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 21:23:25 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37812 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725947AbgHGBXY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 21:23:24 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B38C1C061574
        for <kvm@vger.kernel.org>; Thu,  6 Aug 2020 18:23:23 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id b11so227415plx.21
        for <kvm@vger.kernel.org>; Thu, 06 Aug 2020 18:23:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=yC5jYNAZ2LkpJAay2cVTHRBar69NJbTlP8o5uIXB6/g=;
        b=dbhUZ4AdddRmmfM5MZeqGAPEKz9pXzfFnWWvVwOcBdaX6SgkOX4BLQ1qmjaI2Vv/RE
         lI810NuPrU8cba8i0YMXSkn1Ohkr+DXWdTHizneQgoirhCfkZmKKIefeuWQqwM6d5p46
         5ScI/Z3lLN/VuwpppPg52ErsiS6PbguN4Kopt6kIWm0mDIDHjOFb1h27WrIDbRLRHP2v
         z/Nof0CVwzKkv+LKjBfCzacBwcSdazISEWZKgHJuaT4pwK6Fsdwez25g9dP4eiWSO7hC
         qCfmyEflLkUT16wBzHw+kRlqSt1miYrr3Hnn1UbC94AfE7oJaTUr/YGJlqf9blZYhnkg
         PqRA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=yC5jYNAZ2LkpJAay2cVTHRBar69NJbTlP8o5uIXB6/g=;
        b=JSyk+ndIwfESRaL3c74JocAnxhrhf7/ndlk+YLV2/IG2zKS4D+r/zmF6lG6V+tk3Qu
         J0CjaLfX8ZaZSq/AKqf+IDgzFk2XP2YylMQOsImpvnkU+tgTSyn/ciXd7aV1tQH7R4Qy
         Scc6WAoJ0opLeNL2g6gL8lJS2OU4Tf0LEP57z+8W1evrCxJQcxKb1bhHMt0gW1V0T7yk
         kXPekYn0h6fDTk9r2cM5EcM5Uy7n2V1/bq0v8LgklihDkMSA64GJ0zS1NglPaWDLBJfI
         SRhSInxxHVP1il6dpsd7zayjg1gIwOJnmk1cNiCpe8cfqJ7BZqMzdSBrk+kQAwhLDjMO
         YPJw==
X-Gm-Message-State: AOAM531YIfqDVm1POBTq8wwYeK2yRbIT20bXKkzVhh6HtA23i/X5O9mD
        JhkrxlIkAYB3PYAzSA6fP1rP08YrFNVdYiV97xe6XoFADuy+twl087F7eAgYH3PNb+aUtw0s8UQ
        Wg1xZuRWmOTeFY24Oa34Z34KBQ5jdFaMAKdjCQngFVIkeF0qEav5T
X-Google-Smtp-Source: 
 ABdhPJzX3Q/EZzrTsL+psZOfV6Qe3oGEelBpSTkxN0LrcRBxKGusOhF5mZvdOdGnh5l977FkZGlm/weK
X-Received: by 2002:a17:90a:6343:: with SMTP id
 v3mr11046672pjs.163.1596763402902;
 Thu, 06 Aug 2020 18:23:22 -0700 (PDT)
Date: Thu,  6 Aug 2020 18:23:03 -0700
Message-Id: <20200807012303.3769170-1-cfir@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH] KVM: SVM: Mark SEV launch secret pages as dirty.
From: Cfir Cohen <cfir@google.com>
To: "kvm @ vger . kernel . org" <kvm@vger.kernel.org>,
        Lendacky Thomas <thomas.lendacky@amd.com>,
        Singh Brijesh <brijesh.singh@amd.com>
Cc: Grimm Jon <Jon.Grimm@amd.com>,
        David Rientjes <rientjes@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        linux-kernel@vger.kernel.org, Cfir Cohen <cfir@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The LAUNCH_SECRET command performs encryption of the
launch secret memory contents. Mark pinned pages as
dirty, before unpinning them.
This matches the logic in sev_launch_update().

Signed-off-by: Cfir Cohen <cfir@google.com>
Acked-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm/sev.c | 15 ++++++++++++++-
 1 file changed, 14 insertions(+), 1 deletion(-)

```
#### [PATCH 1/7] KVM: x86: hyper-v: Mention SynDBG CPUID leaves in api.rst
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11705143
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B88BB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:40:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2C3822D00
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:40:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MZaFLJp5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728118AbgHGIkD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 04:40:03 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51394 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726382AbgHGIkA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 04:40:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596789599;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zLsimUENgNb67dJ1BSePNKQb18HkvtcGc8WNRYHR/BI=;
        b=MZaFLJp5IywEqjHjEv1uKJtAvfPy6e8gIKR7ghEqCZH0kfIidPCvMR9cXR/OELNYPQ03AD
        PDvbeaOVzWj3VvhBBLmUk/YSmIWqh8SlaMFKK6WRbeppxE2SzDfm5L3thHpMB5e0ApetDg
        2/8bk0rRLJI6ORXLCt/KqvAFo2uOWbE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-431-T2YarCzVPo-0UtI9C0swcg-1; Fri, 07 Aug 2020 04:39:56 -0400
X-MC-Unique: T2YarCzVPo-0UtI9C0swcg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9FE6C80046C;
        Fri,  7 Aug 2020 08:39:54 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.139])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4C6F75C1D2;
        Fri,  7 Aug 2020 08:39:52 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/7] KVM: x86: hyper-v: Mention SynDBG CPUID leaves in api.rst
Date: Fri,  7 Aug 2020 10:39:40 +0200
Message-Id: <20200807083946.377654-2-vkuznets@redhat.com>
In-Reply-To: <20200807083946.377654-1-vkuznets@redhat.com>
References: <20200807083946.377654-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We forgot to update KVM_GET_SUPPORTED_HV_CPUID's documentation in api.rst
when SynDBG leaves were added.

While on it, fix 'KVM_GET_SUPPORTED_CPUID' copy-paste error.

Fixes: f97f5a56f597 ("x86/kvm/hyper-v: Add support for synthetic debugger interface")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 Documentation/virt/kvm/api.rst | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: x86: move kvm_vcpu_gfn_to_memslot() out of try_async_pf()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11705775
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88639138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 14:12:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70D6522D00
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 14:12:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bJwbqW1V"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726577AbgHGOMz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 10:12:55 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:56305 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726186AbgHGOMw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 10:12:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596809570;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=z8FPKtVhC2Cz+23jVlMU7obiTXtmibbxlAC2Ps134PI=;
        b=bJwbqW1V6xahskgZ5BnFyhTYNvl+c0kcmlveScX+5a/haLARxwjUxN5E7+Nct5ANlDOHJo
        xvyKR5OCk3pO7amoj+qBRyGHMmpxC9vsB499rT2ywSrL5TbTWSAnrF9DjfpLEhIraboE/b
        DWbix0I1X9+wQHk0erjUeAcoSleafUo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-445-_4Wtm20vPi2xsr1euBK3ZA-1; Fri, 07 Aug 2020 10:12:48 -0400
X-MC-Unique: _4Wtm20vPi2xsr1euBK3ZA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5656B8C99E3;
        Fri,  7 Aug 2020 14:12:47 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.139])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 72D4A5C1D3;
        Fri,  7 Aug 2020 14:12:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Xu <peterx@redhat.com>, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Andrew Jones <drjones@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: x86: move kvm_vcpu_gfn_to_memslot() out of
 try_async_pf()
Date: Fri,  7 Aug 2020 16:12:30 +0200
Message-Id: <20200807141232.402895-2-vkuznets@redhat.com>
In-Reply-To: <20200807141232.402895-1-vkuznets@redhat.com>
References: <20200807141232.402895-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended. Slot flags will need to be analyzed
prior to try_async_pf() when KVM_MEM_PCI_HOLE is implemented.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c         | 14 ++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 13 insertions(+), 8 deletions(-)

```
#### [RFC PATCH 1/7] core/metricfs: Create metricfs, standardized files under debugfs.
##### From: Jonathan Adams <jwadams@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jonathan Adams <jwadams@google.com>
X-Patchwork-Id: 11706089
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D5E013B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 21:29:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E277A2224D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 21:29:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Bngt9Nvk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727079AbgHGV3o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 17:29:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53460 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727021AbgHGV3h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 17:29:37 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 167AFC061A27
        for <kvm@vger.kernel.org>; Fri,  7 Aug 2020 14:29:37 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id y13so4455856ybs.0
        for <kvm@vger.kernel.org>; Fri, 07 Aug 2020 14:29:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=DZ1XcM0cED77A7RVE0g/4nios57x9MDZZ5ZxcwQdk5E=;
        b=Bngt9NvknU55LdIMiX02eLN0o6LUzdbtvKXpG+3i0enAKsG8Pk6E/ngdI7IfsJSmDs
         WRdoM/DYrGwjDP5fkQPscla5JCIplKStX7e0zktn6xNUNqd/cHHVqPkZnjkkULa7jAbM
         Ezv/VFLfZAmXLRHOZ+Q/VY4w/7BCOcOISosmV7RA4F7egwzg4noTxcKuJFREVEmtJSIX
         giddv8Mr0Sa2EMpEhiS4+oj9wmTRUSkhnDgnK2GWqKk1v1Q7eJXJ3cRMIHdDOfcIhog1
         8X2s/Ep8pLvxSyFsvZXx3w4taCawiNwIU1j19lSPuP7GM/FZ0vE90yzQUhn077tXy8Sx
         wf5g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=DZ1XcM0cED77A7RVE0g/4nios57x9MDZZ5ZxcwQdk5E=;
        b=G4ZuydfRmfnwQT0ud9m2TmogobdajqCg5D54150dEpqDC1E2jh55bjynEztbrAFDWH
         +JOmJQhMAn3Y9pkuc05snQOUrHL3t21JVqhh0nFB+7pFb72SIBDta5gbA72hXwKCnDL+
         IlD1RVL57gUhcgMe0y9qQAl2UZtPIEQ+dnfiVuhq9Qr/CiANwIYGsMF3oaFmjy4Bds2e
         XXPmdimKZVBNEBu6+OB76Jclsuzn1NaeZSNqiUHKUKfhaNzeoNA3PiE3BGUY6vMH3UiQ
         u+neRMJkXkvAuldqsfJnVa+5xp9szGQGZce53Ko0ypzNL20cppEqq6wApX5aYFqi755o
         6gCw==
X-Gm-Message-State: AOAM531furZX7Rhhjyl3I6cYFTV1C2lSBe3STF3f2+RDKIG3fzBYaw/3
        BXhs0LGCZ0tiHm3tcUiHgiIWKlgbrto=
X-Google-Smtp-Source: 
 ABdhPJzRbMgMO+xhrxQ92IW1rQZZD11iWBKacVFoF1vhmUHoAFABKi3OC7+XbcCrftSj+4u2ofvEujECnYpN
X-Received: by 2002:a5b:5c5:: with SMTP id w5mr22848625ybp.102.1596835776257;
 Fri, 07 Aug 2020 14:29:36 -0700 (PDT)
Date: Fri,  7 Aug 2020 14:29:10 -0700
In-Reply-To: <20200807212916.2883031-1-jwadams@google.com>
Message-Id: <20200807212916.2883031-2-jwadams@google.com>
Mime-Version: 1.0
References: <20200807212916.2883031-1-jwadams@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [RFC PATCH 1/7] core/metricfs: Create metricfs, standardized files
 under debugfs.
From: Jonathan Adams <jwadams@google.com>
To: linux-kernel@vger.kernel.org, linux-fsdevel@vger.kernel.org
Cc: netdev@vger.kernel.org, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Greg KH <gregkh@linuxfoundation.org>,
        Jim Mattson <jmattson@google.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>,
        Justin TerAvest <teravest@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Justin TerAvest <teravest@google.com>

Metricfs is a standardized set of files and directories under debugfs,
with a kernel API designed to be simpler than exporting new files under
sysfs. Type and field information is reported so that a userspace daemon
can easily process the information.

The statistics live under debugfs, in a tree rooted at:

	/sys/kernel/debug/metricfs

Each metric is a directory, with four files in it.  This patch includes
a single "metricfs_presence" metric, whose files look like:
/sys/kernel/debug/metricfs:
 metricfs_presence/annotations
  DESCRIPTION A\ basic\ presence\ metric.
 metricfs_presence/fields
  value
  int
 metricfs_presence/values
  1
 metricfs_presence/version
  1

Statistics can have zero, one, or two 'fields', which are keys for the
table of metric values.  With no fields, you have a simple statistic as
above, with one field you have a 1-dimensional table of string -> value,
and with two fields you have a 2-dimensional table of
{string, string} -> value.

When a statistic's 'values' file is opened, we pre-allocate a 64k buffer
and call the statistic's callback to fill it with data, truncating if
the buffer overflows.

Statistic creators can create a hierarchy for their statistics using
metricfs_create_subsys().

Signed-off-by: Justin TerAvest <teravest@google.com>
[jwadams@google.com: Forward ported to v5.8, cleaned up and modernized
	code significantly]
Signed-off-by: Jonathan Adams <jwadams@google.com>
---

notes:
* To go upstream, this will need documentation and a MAINTAINERS update.
* It's not clear what the "version" file is for; it's vestigial and
should probably be removed.

jwadams@google.com: Forward ported to v5.8, removed some google-isms and
    cleaned up some anachronisms (atomic->refcount, moving to
    kvmalloc(), using POISON_POINTER_DELTA, made more functions static,
    made 'emitter_fn' into an explicit union instead of a void *),
    renamed 'struct emitter -> metric_emitter' and renamed
    some funcs for consistency.
---
 include/linux/metricfs.h   | 103 ++++++
 kernel/Makefile            |   2 +
 kernel/metricfs.c          | 727 +++++++++++++++++++++++++++++++++++++
 kernel/metricfs_examples.c | 151 ++++++++
 lib/Kconfig.debug          |  18 +
 5 files changed, 1001 insertions(+)
 create mode 100644 include/linux/metricfs.h
 create mode 100644 kernel/metricfs.c
 create mode 100644 kernel/metricfs_examples.c

diff --git a/include/linux/metricfs.h b/include/linux/metricfs.h
new file mode 100644
index 000000000000..65a1baa8e8c1
--- /dev/null
+++ b/include/linux/metricfs.h
@@ -0,0 +1,103 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _METRICFS_H_
+#define _METRICFS_H_
+
+#include <linux/kernel.h>
+#include <linux/module.h>
+#include <linux/stringify.h>
+
+struct metric;
+struct metricfs_subsys;
+
+#define METRIC_EXPORT_GENERIC(name, desc, fname0, fname1, fn, is_str, cumulative) \
+static struct metric *metric_##name; \
+void metric_init_##name(struct metricfs_subsys *parent) \
+{ \
+	metric_##name = metric_register(__stringify(name), (parent), (desc), \
+					(fname0), (fname1), (fn), (is_str), \
+					(cumulative), THIS_MODULE); \
+} \
+void metric_exit_##name(void) \
+{ \
+	metric_unregister(metric_##name); \
+}
+
+/*
+ * Metricfs only deals with two types: int64_t and const char*.
+ *
+ * If a metric has fewer than two fields, pass NULL for the field name
+ * arguments.
+ *
+ * The metric does not take ownership of any of the strings passed in.
+ *
+ * See kernel/metricfs_examples.c for a set of example metrics, with
+ * corresponding output.
+ *
+ * METRIC_EXPORT_INT - An integer-valued metric.
+ * METRIC_EXPORT_COUNTER - An integer-valued cumulative metric.
+ * METRIC_EXPORT_STR - A string-valued metric.
+ */
+#define METRIC_EXPORT_INT(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				false, false)
+#define METRIC_EXPORT_COUNTER(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				false, true)
+#define METRIC_EXPORT_STR(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				true, false)
+
+/* Subsystem support. */
+/* Pass NULL as 'parent' to create a new top-level subsystem. */
+struct metricfs_subsys *metricfs_create_subsys(const char *name,
+						struct metricfs_subsys *parent);
+void metricfs_destroy_subsys(struct metricfs_subsys *d);
+
+/*
+ * An opaque struct that metric emit functions use to keep our internal
+ * state.
+ */
+struct metric_emitter;
+
+/* The number of non-NULL arguments passed to EMIT macros must match the number
+ * of arguments passed to the EXPORT macro for a given metric.
+ *
+ * Failure to do so will cause data to be mangled (or dropped) by userspace or
+ * Monarch.
+ */
+#define METRIC_EMIT_INT(e, v, f0, f1) \
+	metric_emit_int_value((e), (v), (f0), (f1))
+#define METRIC_EMIT_STR(e, v, f0, f1) \
+	metric_emit_str_value((e), (v), (f0), (f1))
+
+/* Users don't have to call any functions below;
+ * use the macro definitions above instead.
+ */
+void metric_emit_int_value(struct metric_emitter *e,
+			   int64_t v, const char *f0, const char *f1);
+void metric_emit_str_value(struct metric_emitter *e,
+			   const char *v, const char *f0, const char *f1);
+
+struct metric *metric_register(const char *name,
+			       struct metricfs_subsys *parent,
+			       const char *description,
+			       const char *fname0, const char *fname1,
+			       void (*fn)(struct metric_emitter *e),
+			       bool is_string,
+			       bool is_cumulative,
+			       struct module *owner);
+
+struct metric *metric_register_parm(const char *name,
+				    struct metricfs_subsys *parent,
+			  const char *description,
+				    const char *fname0, const char *fname1,
+				    void (*fn)(struct metric_emitter *e,
+					       void *parm),
+				    void *parm,
+				    bool is_string,
+				    bool is_cumulative,
+				    struct module *owner);
+
+void metric_unregister(struct metric *m);
+
+#endif /* _METRICFS_H_ */
```
#### [kvm-unit-tests PATCH v2 1/3] s390x: Add custom pgm cleanup function
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11705529
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ED3CB138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 11:16:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D770B22C9F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 11:16:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="H7mkflrp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727814AbgHGLQZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 07:16:25 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3082 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726226AbgHGLQG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Aug 2020 07:16:06 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 077B3RL1169762;
        Fri, 7 Aug 2020 07:16:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=M5gGijiGYAWuEfTOjLXZEguj1KdFU0EOt0KK6twlmG0=;
 b=H7mkflrpKmnbIrt3eBUDdbsJqc2iXv4XS/PhJQsZE/CDXlTvgbrtmxXFjtHiszWSyFAb
 oV/8A2iKXVUcnDrqAq8PIG/3qgh808laS7zDw73yREnwoA3vBXAu34IUMvHFIhVmmAV/
 hv8RfD/A5AHHp5VZH0xRIDxPAuwmXdbSrhmUPY2fx7z+DrAJNhvW6T7qaB/2R3Ao2Lay
 EGDccPkricodVJkZyHjM3fCpUqYoIXt2COVFG+RCB37lcceVuaLlrKrCYX8rhov6ffo9
 IpdFFH9/+sZ/90Xx2isifkstKGQ1gFqKG2dqasnxgCQsXrQO6X7qXRxaEGjEPIu/05oF xQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32ra0sm9qy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 07:16:05 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 077B5Cp5176989;
        Fri, 7 Aug 2020 07:16:05 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32ra0sm9q1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 07:16:05 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 077BG2VU026764;
        Fri, 7 Aug 2020 11:16:02 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04ams.nl.ibm.com with ESMTP id 32n0186kct-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 11:16:02 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 077BFxhQ28967350
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 7 Aug 2020 11:15:59 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4CDE4AE051;
        Fri,  7 Aug 2020 11:15:59 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 89E34AE055;
        Fri,  7 Aug 2020 11:15:58 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  7 Aug 2020 11:15:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/3] s390x: Add custom pgm cleanup function
Date: Fri,  7 Aug 2020 07:15:53 -0400
Message-Id: <20200807111555.11169-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200807111555.11169-1-frankja@linux.ibm.com>
References: <20200807111555.11169-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-07_06:2020-08-06,2020-08-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 adultscore=0
 mlxlogscore=999 lowpriorityscore=0 suspectscore=1 bulkscore=0
 clxscore=1015 spamscore=0 priorityscore=1501 impostorscore=0 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008070079
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sometimes we need to do cleanup which we don't necessarily want to add
to interrupt.c, so let's add a way to register a cleanup function.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/interrupt.h |  1 +
 lib/s390x/interrupt.c     | 12 +++++++++++-
 2 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH v4 01/12] KVM: SVM: Introduce vmcb_set_intercept, vmcb_clr_intercept and vmcb_is_intercept
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11704577
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51DFC138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 00:46:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 522F92075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 00:46:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="sJa92ZZ/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726490AbgHGAqe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 20:46:34 -0400
Received: from mail-dm6nam12on2046.outbound.protection.outlook.com
 ([40.107.243.46]:19169
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726011AbgHGAqd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 20:46:33 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=P8gmW0Eo7GjSnGNbE/i+0usv/YxBzYRsKAbE6mFEmNHDqnlOWIC/HyvgHod7XD3TmQ6wY8lpNmbGyLVsuQCudPBC7zjJ76rVXoTCV+lQ0Lo/+dpXQ+L+oTH54bjPkP6Ciz0b2Xd8FojZwGF/JrCdkeYCiYf1xGQA1NvRQyDzG23BQy1lDXhQIY1Dcoa2Y2ddoWfSZ7vi5+z+MYboGgUbvZ00nio1XpmoQ67A4FCag43zBpCiFoHhQCWNQItw8byJxWcOK/s/Ja+vOiVj+V1ceZgjMez0z6mEGMaMxQsETjL7+8jxycz0ElvqINNL0L8rion30l5L48wK6A61EmJ61g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MLHr1P/78y+aHbvdJT3nm6q4XPc5Zv8AvX3Ih1p4e2s=;
 b=LBzKGs9CrR6FYBEc3yaBQfh1gEclcvnmSy0uxUgUbtHlFGzxZsQsn8KKA9cQL+1f7Ntr6+DhDR0yNxYUtcDOOGHvKaVhoJl7pVGBF6V0vfwWNWORuyFpXtsyD06TzsV/Jz6nfKJKja+IhR9srBGCas68Be06Gs1pI1sl4vvMI6PtK/hJG/zOK/bQ/OKO7HPD75x2lnsVdcauYA7817tnEFjV9dN+RZoT4GJoBsF4BrDxX0xlwMByx3pC7SQldZ+r/fDqF8G29Lo9VLNbB+4yahbWler4F+RslJjhP25PW419OoUyCzeq4As6yLN9vjyeIy+hCde0+Fo9Ez8g/qFOMw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MLHr1P/78y+aHbvdJT3nm6q4XPc5Zv8AvX3Ih1p4e2s=;
 b=sJa92ZZ/361HCVcre0vLVHFxixDDxh4Zf7a3L9UZ9Czt4Xc1BqfgeaQmAZSjsCW/Xga4KYJ1PU67LgdnMyUwCjaMoPNuggJ00tjy382J8xjFQ24XSOTEfVvplKaK2DEyyhKR4+UeV64aSzcBZBP/xD2syvr453ZB+2r4yfqNJ9c=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4479.namprd12.prod.outlook.com (2603:10b6:806:95::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3261.19; Fri, 7 Aug
 2020 00:46:30 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::691c:c75:7cc2:7f2c]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::691c:c75:7cc2:7f2c%6]) with mapi id 15.20.3239.023; Fri, 7 Aug 2020
 00:46:30 +0000
Subject: [PATCH v4 01/12] KVM: SVM: Introduce vmcb_set_intercept,
 vmcb_clr_intercept and vmcb_is_intercept
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, wanpengli@tencent.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: kvm@vger.kernel.org, joro@8bytes.org, x86@kernel.org,
        linux-kernel@vger.kernel.org, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de
Date: Thu, 06 Aug 2020 19:46:28 -0500
Message-ID: <159676118836.12805.4817403954662511426.stgit@bmoger-ubuntu>
In-Reply-To: <159676101387.12805.18038347880482984693.stgit@bmoger-ubuntu>
References: <159676101387.12805.18038347880482984693.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: SN4PR0501CA0092.namprd05.prod.outlook.com
 (2603:10b6:803:22::30) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0092.namprd05.prod.outlook.com (2603:10b6:803:22::30) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3283.7 via Frontend
 Transport; Fri, 7 Aug 2020 00:46:29 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 733b359f-7d37-4ca2-9574-08d83a6b532d
X-MS-TrafficTypeDiagnostic: SA0PR12MB4479:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4479ECD7255D87D1BF2FF65B95490@SA0PR12MB4479.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2449;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 tZFlDbDoACf2SfQlE5MGWF8L7EM7CziQPuc/ecXGl7ljr9AtwtPg7xV+wQUEkz1wcFrfaGxGtbSkWPb7wi7NnAN0A4MLFJJj4DZv+cDyimsjY7LGzrFHktJ5UMulkvv3PVss+sSk7WZfgsKhyMzGxhOjM2aPpMBjnjGQ5utN+xVQiBwoFKdjt55DJVD3SDk7eScDf833fddBa2h3lDSReA/tOvGLWTmwiUYbYh7LJBoeYM+OHm+h36juctfAymt20Mj0i7HlprNNUZYC9Eu6QPXje2Lz6fHa/hi7mJ1ehYxmqFDOJFw3PLb3Pr3ieBoyq6Op+U+C4g2xVMLDt9PN7A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(7916004)(39860400002)(396003)(376002)(346002)(136003)(366004)(5660300002)(6486002)(52116002)(2906002)(16576012)(4326008)(7416002)(956004)(44832011)(33716001)(26005)(9686003)(8676002)(66476007)(66556008)(103116003)(66946007)(8936002)(86362001)(16526019)(186003)(478600001)(316002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 MQ6H6b2AiVCK/0jzZF/oEdC41B3xYT+pkn5ytHuku5GqMDu+gHKlEaE2Dwb34sJmlCvlXWLF4TILRSZBh8ogSylSCEv5Bj5jH/xGKviAT5H+d5gLA4QMJvGvmn/x2ekQkBH4Q5RXPBcrFcZuyLjGI4lQbY8oeUYmOvU78slpAc5YL7eYYLPO7nVqRPLt6tgW41frZloBz5Z1B3H+I2XsHZLSpSiavukKKqOwRBsOXLud1ARm796VwCAafZTg/13Z6zkyQWGBGD0nWubXZZ3iT07OpsMARqA7xiNZDU9hyyU89sh7l6GwmyNU8DhrKhs5VlVJ1HKN9pNhvx5/N+oJYsd+kZbDqh7rFG3CRgp/SrAWo5KpnX9WqQ/Vj1cbaPkl6vwmmdZ+v7IzXb5XYEkNXN4xtNephgiztGUAO7IFiXN+OJkNRUMpLAur4iSVNwNEUtYvsEI19QVzeMw2bqulpir5Lm9gb4Z/pvIXbyHDt8H4OMlwyYsSolFWk2xe25omzyTy8MnSLYowVt1PyysUYdf+89htoxnLQmKsbf8MQoJ9rp3DFS/WCe30IlKv6xmFsacGvGVgg+IeagrcF+IiGNU7lvyuoMhue/73ulVmN3QXdz41zXniJL33xEygRIo8v43y0XXuobG2cU/NVia9Gg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 733b359f-7d37-4ca2-9574-08d83a6b532d
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Aug 2020 00:46:30.5722
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 EiWojceaHJg5MTfYuzggx0IG4prWwPAsYWEjZoCg0AWItk9E5NzxOJeA7lURFsjx
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4479
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is in preparation for the future intercept vector additions.

Add new functions vmcb_set_intercept, vmcb_clr_intercept and vmcb_is_intercept
using kernel APIs __set_bit, __clear_bit and test_bit espectively.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/kvm/svm/svm.h |   15 +++++++++++++++
 1 file changed, 15 insertions(+)

```
#### [PATCH] vfio/type1: Add proper error unwind for vfio_iommu_replay()From: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11706059
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12C2B13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 20:15:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4D272224D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 20:14:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gbhLZdiZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726202AbgHGUO4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 16:14:56 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:28751 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725893AbgHGUO4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Aug 2020 16:14:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596831294;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=QsmSdkCrL05ggCwSUu92b6yNnGSlgdi5jfgLpMXvbbI=;
        b=gbhLZdiZP3Iq6eDlfqe1zGo4Yvoc3rWpZ91B4E7kiT3tGznwDwrQrS8a8K+uh/ehzNwKVd
        X4f1zJI/t0BNd/gdT3HsMtEswGK+1A6Vo+LLzCbT7WthgeAvBQSCuy/N2/X1HJq2ypuD9J
        SgDlM1AUwmIf7cYMGFUfpUjHKK3nbx4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-327-OpsRlMl1MaagiEOmJ52jiw-1; Fri, 07 Aug 2020 16:14:52 -0400
X-MC-Unique: OpsRlMl1MaagiEOmJ52jiw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BF5BD57;
        Fri,  7 Aug 2020 20:14:51 +0000 (UTC)
Received: from gimli.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 69A605F207;
        Fri,  7 Aug 2020 20:14:48 +0000 (UTC)
Subject: [PATCH] vfio/type1: Add proper error unwind for vfio_iommu_replay()
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Date: Fri, 07 Aug 2020 14:14:48 -0600
Message-ID: <159683127474.1965.16929121291974112960.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_iommu_replay() function does not currently unwind on error,
yet it does pin pages, perform IOMMU mapping, and modify the vfio_dma
structure to indicate IOMMU mapping.  The IOMMU mappings are torn down
when the domain is destroyed, but the other actions go on to cause
trouble later.  For example, the iommu->domain_list can be empty if we
only have a non-IOMMU backed mdev attached.  We don't currently check
if the list is empty before getting the first entry in the list, which
leads to a bogus domain pointer.  If a vfio_dma entry is erroneously
marked as iommu_mapped, we'll attempt to use that bogus pointer to
retrieve the existing physical page addresses.

This is the scenario that uncovered this issue, attempting to hot-add
a vfio-pci device to a container with an existing mdev device and DMA
mappings, one of which could not be pinned, causing a failure adding
the new group to the existing container and setting the conditions
for a subsequent attempt to explode.

To resolve this, we can first check if the domain_list is empty so
that we can reject replay of a bogus domain, should we ever encounter
this inconsistent state again in the future.  The real fix though is
to add the necessary unwind support, which means cleaning up the
current pinning if an IOMMU mapping fails, then walking back through
the r-b tree of DMA entries, reading from the IOMMU which ranges are
mapped, and unmapping and unpinning those ranges.  To be able to do
this, we also defer marking the DMA entry as IOMMU mapped until all
entries are processed, in order to allow the unwind to know the
disposition of each entry.

Fixes: a54eb55045ae ("vfio iommu type1: Add support for mediated devices")
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c |   71 ++++++++++++++++++++++++++++++++++++---
 1 file changed, 66 insertions(+), 5 deletions(-)

```
#### [PATCH v2 03/20] virtio: Add get_shm_region method
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11706045
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F100D138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 19:57:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D7FA82224D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 19:57:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CUDN28Yo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727932AbgHGT5E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 15:57:04 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47129 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726821AbgHGTzx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 15:55:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596830151;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=jtqR2toNUH2Oj21nmtYHpQK7dk5daGIfHgim40Hd9n0=;
        b=CUDN28Yo5KP6BXDiqiNH6Z9WBLPo5cvxV4ilVQPrMcLzSPfQq31JU9HuwTtxV9POXg8nLU
        rFAoXEehR8FSxT8xnaWfWWcNrKWqYxTGi2BNuZhoKxGmsTevsBzqomivwdDgvuH8ccSLRZ
        ViHns5S+5A/HE8A/JN3zcMt+zLB5MfM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-281-P-RKb71IPeOz8SfGDnbULQ-1; Fri, 07 Aug 2020 15:55:49 -0400
X-MC-Unique: P-RKb71IPeOz8SfGDnbULQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06EEC1005510;
        Fri,  7 Aug 2020 19:55:48 +0000 (UTC)
Received: from horse.redhat.com (ovpn-113-142.rdu2.redhat.com [10.10.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 226C260BE2;
        Fri,  7 Aug 2020 19:55:39 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id B171C222E45; Fri,  7 Aug 2020 15:55:38 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        virtio-fs@redhat.com
Cc: vgoyal@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, Sebastien Boeuf <sebastien.boeuf@intel.com>,
        kvm@vger.kernel.org, "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v2 03/20] virtio: Add get_shm_region method
Date: Fri,  7 Aug 2020 15:55:09 -0400
Message-Id: <20200807195526.426056-4-vgoyal@redhat.com>
In-Reply-To: <20200807195526.426056-1-vgoyal@redhat.com>
References: <20200807195526.426056-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sebastien Boeuf <sebastien.boeuf@intel.com>

Virtio defines 'shared memory regions' that provide a continuously
shared region between the host and guest.

Provide a method to find a particular region on a device.

Signed-off-by: Sebastien Boeuf <sebastien.boeuf@intel.com>
Signed-off-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Cc: kvm@vger.kernel.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>
---
 include/linux/virtio_config.h | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
