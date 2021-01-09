#### 
##### 

```c
```
#### [RESEND v5 1/4] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12005879
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D4F02C433E6
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:53:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8AF6023741
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:53:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727260AbhAHGxT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 01:53:19 -0500
Received: from mga02.intel.com ([134.134.136.20]:45892 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727077AbhAHGxS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 01:53:18 -0500
IronPort-SDR: 
 Xr4mcCK9ChUoudh672tB7XWYtQ0AlBNs9T82wUNxO4fFd7Ka1RDQxcHLljOjLM61CApq/tMbOp
 QDePhI1LJDjw==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="164628715"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="164628715"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:52:36 -0800
IronPort-SDR: 
 QRDDLzEby/SvrB0whZYNUA/uYFTNjSercX8dfqFiJzouNUDrcgKahi2UJiTJbRorDrRkOQOyC3
 Tile5fnuMyQw==
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="570660429"
Received: from chenyi-pc.sh.intel.com ([10.239.159.137])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:52:33 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v5 1/4] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Fri,  8 Jan 2021 14:55:27 +0800
Message-Id: <20210108065530.2135-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210108065530.2135-1-chenyi.qiang@intel.com>
References: <20210108065530.2135-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Convert vcpu_vmx.exit_reason from a u32 to a union (of size u32).  The
full VM_EXIT_REASON field is comprised of a 16-bit basic exit reason in
bits 15:0, and single-bit modifiers in bits 31:16.

Historically, KVM has only had to worry about handling the "failed
VM-Entry" modifier, which could only be set in very specific flows and
required dedicated handling.  I.e. manually stripping the FAILED_VMENTRY
bit was a somewhat viable approach.  But even with only a single bit to
worry about, KVM has had several bugs related to comparing a basic exit
reason against the full exit reason store in vcpu_vmx.

Upcoming Intel features, e.g. SGX, will add new modifier bits that can
be set on more or less any VM-Exit, as opposed to the significantly more
restricted FAILED_VMENTRY, i.e. correctly handling everything in one-off
flows isn't scalable.  Tracking exit reason in a union forces code to
explicitly choose between consuming the full exit reason and the basic
exit, and is a convenient way to document and access the modifiers.

No functional change intended.

Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 42 +++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    | 68 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 +++++++++++++-
 3 files changed, 86 insertions(+), 49 deletions(-)

```
#### [RESEND PATCH 1/2] KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12005869
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF58AC4332D
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:47:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E5B7233FB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:47:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726830AbhAHGrQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 01:47:16 -0500
Received: from mga11.intel.com ([192.55.52.93]:46175 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725308AbhAHGrO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 01:47:14 -0500
IronPort-SDR: 
 nafCskYcMw6I6adIwWBu9aDYWdtgqQyVBRj5WkEXDNr5e4zbYy+c2QeX+rke7ezKCWXteu8IZ3
 qj9bgOHYl4tg==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="174042917"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="174042917"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:46:34 -0800
IronPort-SDR: 
 TytmMYEXLqVpEop+outPHixqKQfMi7K994j5B+vZse2ZETFK/+47KrB90FAKHINIlIQK9Mhbmn
 3lbZZHUsJrng==
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="380017287"
Received: from chenyi-pc.sh.intel.com ([10.239.159.137])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:46:31 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND PATCH 1/2] KVM: X86: Add support for the emulation of
 DR6_BUS_LOCK bit
Date: Fri,  8 Jan 2021 14:49:23 +0800
Message-Id: <20210108064924.1677-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210108064924.1677-1-chenyi.qiang@intel.com>
References: <20210108064924.1677-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To avoid breaking the CPUs without bus lock detection, activate the
DR6_BUS_LOCK bit (bit 11) conditionally in DR6_FIXED_1 bits.

The set/clear of DR6_BUS_LOCK is similar to the DR6_RTM in DR6
register. The processor clears DR6_BUS_LOCK when bus lock debug
exception is generated. (For all other #DB the processor sets this bit
to 1.) Software #DB handler should set this bit before returning to the
interrupted task.

For VM exit caused by debug exception, bit 11 of the exit qualification
is set to indicate that a bus lock debug exception condition was
detected. The VMM should emulate the exception by clearing bit 11 of the
guest DR6.

Co-developed-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  5 +++--
 arch/x86/kvm/emulate.c          |  2 +-
 arch/x86/kvm/svm/svm.c          |  6 +++---
 arch/x86/kvm/vmx/nested.c       |  2 +-
 arch/x86/kvm/vmx/vmx.c          |  6 ++++--
 arch/x86/kvm/x86.c              | 28 +++++++++++++++++-----------
 6 files changed, 29 insertions(+), 20 deletions(-)

```
#### [Patch v4 1/2] cgroup: svm: Add Encryption ID controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12005531
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE1DDC433E0
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:30:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B27AE236FB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:30:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729835AbhAHB35 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 20:29:57 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47112 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729667AbhAHB35 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 20:29:57 -0500
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8F853C0612FE
        for <kvm@vger.kernel.org>; Thu,  7 Jan 2021 17:29:03 -0800 (PST)
Received: by mail-pf1-x449.google.com with SMTP id e4so5452973pfc.11
        for <kvm@vger.kernel.org>; Thu, 07 Jan 2021 17:29:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=DXx0S1ptKQMILkVNuphldfQ2Z2JYHkkk6kOOr0iwLok=;
        b=FOysrnw5Slu+eQKAyu8EBbBuqh2arzUyvcUxM6HtFc8FbvP2Bc2VbLbbqCjbKA4RuH
         lFXl6nuXbQQKMkhjDlPXELirfCOnE/hXyidn3hu8pAl44Gea9x+mblByOkw3wcOz7IfD
         wPraGippmQ16XcIniksPaANUhCAzPE9FvFHIfg9X6DPbOSj4j7hH72TokSxNJbNl2seY
         OdTuWqOUbTDpHy7BEgnzKwv33mvRBeUzuLYl1viZPZlU5OVeRhl8WR2npspk+LBA1htp
         5tSJ71j4s01LYvDNo2RJ/NX7d0H81CC9OtvhTy1L3GTEN1CsRQgNU2voRahAHq9R02Ot
         pMtA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=DXx0S1ptKQMILkVNuphldfQ2Z2JYHkkk6kOOr0iwLok=;
        b=q64OlwsA1GEdOUPlXDODhWPoDS1dPrsUSbw7qP57XbWrGaHCoGQQfcJb3nzO/Fjcqt
         Moynp/BHtsPzUW7UI7U4A8WvbIzIczQqGYSQ6QCP9UP3Md0/u8npD5BN2kH1E1S6qEBu
         U3dY3zGUJYn7AIoZPGXZLT+O9nFFmqckqvMFw3AjAXoLOTH6e0ItrJ7/x/2STabwfcMM
         7oRRdlht51aUVXafrdFGmzwNcrne045M7+jJNM2iU8YF15WtZH9F1gCPva8dvC1YPult
         sb81lndyqObdVdioE7qCdL5nYtUNxqLMkapmM1euCNlf4k2jg3tfC12UObmB+6WApO+A
         APbw==
X-Gm-Message-State: AOAM530GNgwAcHA2+zj3juuk3/TnLEqk3cg+LmzG6HeQcQIFpOIef791
        1ash6aBURz2rhbzXPXX6GPhBY27+I3+8
X-Google-Smtp-Source: 
 ABdhPJy/kev/UDE66eTWMSnLrqKogv16wm/Li0Fv01Dl8vMP4md7YpElp3nuZiKfDvRmkhAHoBCfa1+UXyNC
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a05:6a00:44:b029:19d:e250:1355 with SMTP
 id i4-20020a056a000044b029019de2501355mr4548405pfk.36.1610069343029; Thu, 07
 Jan 2021 17:29:03 -0800 (PST)
Date: Thu,  7 Jan 2021 17:28:45 -0800
In-Reply-To: <20210108012846.4134815-1-vipinsh@google.com>
Message-Id: <20210108012846.4134815-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20210108012846.4134815-1-vipinsh@google.com>
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [Patch v4 1/2] cgroup: svm: Add Encryption ID controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardware memory encryption is available on multiple generic CPUs. For
example AMD has Secure Encrypted Virtualization (SEV) and SEV -
Encrypted State (SEV-ES).

These memory encryptions are useful in creating encrypted virtual
machines (VMs) and user space programs.

There are limited number of encryption IDs that can be used
simultaneously on a machine for encryption. This generates a need for
the system admin to track, limit, allocate resources, and optimally
schedule VMs and user workloads in the cloud infrastructure. Some
malicious programs can exhaust all of these resources on a host causing
starvation of other workloads.

Encryption ID controller allows control of these resources using
Cgroups.

Controller is enabled by CGROUP_ENCRYPTION_IDS config option.
Encryption controller provide 3 interface files for each encryption ID
type. For example, in SEV:

1. encrpytion_ids.sev.max
	Sets the maximum usage of SEV IDs in the cgroup.
2. encryption_ids.sev.current
	Current usage of SEV IDs in the cgroup and its children.
3. encryption_ids.sev.stat
	Shown only at the root cgroup. Displays total SEV IDs available
	on the platform and current usage count.

Other ID types can be easily added in the controller in the same way.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
Reviewed-by: Dionna Glaze <dionnaglaze@google.com>
---
 arch/x86/kvm/svm/sev.c                |  52 +++-
 include/linux/cgroup_subsys.h         |   4 +
 include/linux/encryption_ids_cgroup.h |  72 +++++
 include/linux/kvm_host.h              |   4 +
 init/Kconfig                          |  14 +
 kernel/cgroup/Makefile                |   1 +
 kernel/cgroup/encryption_ids.c        | 422 ++++++++++++++++++++++++++
 7 files changed, 557 insertions(+), 12 deletions(-)
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c

```
#### [GIT PULL] KVM fixes for 5.11-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12006963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D6771C433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 16:30:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1518238EA
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 16:30:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728009AbhAHQaW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 11:30:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56993 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726386AbhAHQaW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 Jan 2021 11:30:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610123335;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=S8FoM+RpRgtpip5lz5oEOsceIPoTtMA/todm6XH5iAs=;
        b=WN+si0Kma2CJgFYAB3FJOvfNzMpSNQxf4XBr0EaS0U8RXSsVpObednpcHMOkXzJCtN2y2x
        B7fs3y2pQU93Mqq+LmLbxxARvkaDZ4v1A7q7XlBMt4aL7s4qGB11GwfdIC603uSemrsm5h
        nkNLIzpStFz8uB96zX81AeevXF2Tuu8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-233-5xcr-r1tMDOhWtfWYCq-zQ-1; Fri, 08 Jan 2021 11:28:51 -0500
X-MC-Unique: 5xcr-r1tMDOhWtfWYCq-zQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3D5938030A2;
        Fri,  8 Jan 2021 16:28:50 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E17CD5C8AA;
        Fri,  8 Jan 2021 16:28:49 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for 5.11-rc3
Date: Fri,  8 Jan 2021 11:28:49 -0500
Message-Id: <20210108162849.49465-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit d45f89f7437d0f2c8275b4434096164db106384d:

  KVM: SVM: fix 32-bit compilation (2020-12-16 13:08:21 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 872f36eb0b0f4f0e3a81ea1e51a6bdf58ccfdc6e:

  KVM: x86: __kvm_vcpu_halt can be static (2021-01-08 05:54:44 -0500)

----------------------------------------------------------------
x86:
* Fixes for the new scalable MMU
* Fixes for migration of nested hypervisors on AMD
* Fix for clang integrated assembler
* Fix for left shift by 64 (UBSAN)
* Small cleanups
* Straggler SEV-ES patch

ARM:
* VM init cleanups
* PSCI relay cleanups
* Kill CONFIG_KVM_ARM_PMU
* Fixup __init annotations
* Fixup reg_to_encoding()
* Fix spurious PMCR_EL0 access

* selftests cleanups

----------------------------------------------------------------
Alexandru Elisei (5):
      KVM: Documentation: Add arm64 KVM_RUN error codes
      KVM: arm64: arch_timer: Remove VGIC initialization check
      KVM: arm64: Move double-checked lock to kvm_vgic_map_resources()
      KVM: arm64: Update comment in kvm_vgic_map_resources()
      KVM: arm64: Remove redundant call to kvm_pmu_vcpu_reset()

Andrew Jones (3):
      KVM: selftests: Factor out guest mode code
      KVM: selftests: Use vm_create_with_vcpus in create_vm
      KVM: selftests: Implement perf_test_util more conventionally

Ben Gardon (2):
      KVM: x86/mmu: Ensure TDP MMU roots are freed after yield
      KVM: x86/mmu: Clarify TDP MMU page list invariants

David Brazdil (6):
      KVM: arm64: Prevent use of invalid PSCI v0.1 function IDs
      KVM: arm64: Use lm_alias in nVHE-only VA conversion
      KVM: arm64: Skip computing hyp VA layout for VHE
      KVM: arm64: Minor cleanup of hyp variables used in host
      KVM: arm64: Remove unused includes in psci-relay.c
      KVM: arm64: Move skip_host_instruction to adjust_pc.h

Lai Jiangshan (1):
      kvm: check tlbs_dirty directly

Marc Zyngier (6):
      KVM: arm64: Don't access PMCR_EL0 when no PMU is available
      KVM: arm64: Declutter host PSCI 0.1 handling
      KVM: arm64: Consolidate dist->ready setting into kvm_vgic_map_resources()
      KVM: arm64: Fix hyp_cpu_pm_{init,exit} __init annotation
      KVM: arm64: Remove spurious semicolon in reg_to_encoding()
      KVM: arm64: Replace KVM_ARM_PMU with HW_PERF_EVENTS

Maxim Levitsky (3):
      KVM: nSVM: correctly restore nested_run_pending on migration
      KVM: nSVM: mark vmcb as dirty when forcingly leaving the guest mode
      KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit

Nathan Chancellor (1):
      KVM: SVM: Add register operand to vmsave call in sev_es_vcpu_load

Paolo Bonzini (4):
      Merge branch 'kvm-master' into kvm-next
      KVM: x86: fix shift out of bounds reported by UBSAN
      Merge tag 'kvmarm-fixes-5.11-1' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: x86: __kvm_vcpu_halt can be static

Sean Christopherson (5):
      KVM: x86/mmu: Use -1 to flag an undefined spte in get_mmio_spte()
      KVM: x86/mmu: Get root level from walkers when retrieving MMIO SPTE
      KVM: x86/mmu: Use raw level to index into MMIO walks' sptes array
      KVM: x86/mmu: Optimize not-present/MMIO SPTE check in get_mmio_spte()
      MAINTAINERS: Really update email address for Sean Christopherson

Shannon Zhao (1):
      arm64: cpufeature: remove non-exist CONFIG_KVM_ARM_HOST

Stephen Zhang (1):
      KVM: x86: change in pv_eoi_get_pending() to make code more readable

Tom Lendacky (1):
      KVM: SVM: Add support for booting APs in an SEV-ES guest

Uros Bizjak (1):
      KVM/SVM: Remove leftover __svm_vcpu_run prototype from svm.c

 Documentation/virt/kvm/api.rst                     |   9 +-
 MAINTAINERS                                        |   2 +-
 arch/arm64/include/asm/kvm_host.h                  |  23 +++
 arch/arm64/kernel/cpufeature.c                     |   2 +-
 arch/arm64/kernel/smp.c                            |   2 +-
 arch/arm64/kvm/Kconfig                             |   8 -
 arch/arm64/kvm/Makefile                            |   2 +-
 arch/arm64/kvm/arch_timer.c                        |   7 +-
 arch/arm64/kvm/arm.c                               |  32 ++--
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h         |   9 ++
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 |  12 +-
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |   6 +-
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               |  59 +++-----
 arch/arm64/kvm/pmu-emul.c                          |   2 -
 arch/arm64/kvm/sys_regs.c                          |   6 +-
 arch/arm64/kvm/va_layout.c                         |   7 +-
 arch/arm64/kvm/vgic/vgic-init.c                    |  11 +-
 arch/arm64/kvm/vgic/vgic-v2.c                      |  20 +--
 arch/arm64/kvm/vgic/vgic-v3.c                      |  21 +--
 arch/x86/include/asm/kvm_host.h                    |  19 ++-
 arch/x86/kvm/lapic.c                               |   4 +-
 arch/x86/kvm/mmu.h                                 |   2 +-
 arch/x86/kvm/mmu/mmu.c                             |  53 ++++---
 arch/x86/kvm/mmu/tdp_mmu.c                         | 113 +++++++-------
 arch/x86/kvm/mmu/tdp_mmu.h                         |   4 +-
 arch/x86/kvm/svm/nested.c                          |   8 +
 arch/x86/kvm/svm/sev.c                             |  24 ++-
 arch/x86/kvm/svm/svm.c                             |  12 +-
 arch/x86/kvm/svm/svm.h                             |   2 +
 arch/x86/kvm/vmx/nested.c                          |   2 +
 arch/x86/kvm/vmx/vmx.c                             |   2 +
 arch/x86/kvm/x86.c                                 |  30 +++-
 include/kvm/arm_pmu.h                              |   2 +-
 include/uapi/linux/kvm.h                           |   2 +
 tools/testing/selftests/kvm/Makefile               |   2 +-
 tools/testing/selftests/kvm/demand_paging_test.c   | 118 ++++-----------
 tools/testing/selftests/kvm/dirty_log_perf_test.c  | 145 ++++++------------
 tools/testing/selftests/kvm/dirty_log_test.c       | 125 +++++----------
 tools/testing/selftests/kvm/include/guest_modes.h  |  21 +++
 tools/testing/selftests/kvm/include/kvm_util.h     |   9 ++
 .../testing/selftests/kvm/include/perf_test_util.h | 167 ++-------------------
 tools/testing/selftests/kvm/lib/guest_modes.c      |  70 +++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   9 +-
 tools/testing/selftests/kvm/lib/perf_test_util.c   | 134 +++++++++++++++++
 virt/kvm/kvm_main.c                                |   3 +-
 45 files changed, 667 insertions(+), 655 deletions(-)
```
#### [PATCH] KVM: Documentation: Fix spec for KVM_CAP_ENABLE_CAP_VMFrom: Quentin Perret <qperret@google.com>
##### From: Quentin Perret <qperret@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Quentin Perret <qperret@google.com>
X-Patchwork-Id: 12007021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4086EC433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 16:55:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F348C23A03
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 16:55:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728234AbhAHQyk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 11:54:40 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49166 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727242AbhAHQyj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 11:54:39 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AD4B0C061380
        for <kvm@vger.kernel.org>; Fri,  8 Jan 2021 08:53:59 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id f33so8736963qtb.1
        for <kvm@vger.kernel.org>; Fri, 08 Jan 2021 08:53:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=B4cmagUJvqsvM8KJ5vcfLLw3GzVKlYfhlZ7WKpaii2Q=;
        b=g2ySYlslVFQEhuaHS7k+EtkU/c4zzrCRoDUa5ArebteqUm80XrjjPCM4k5ePja3PTf
         qMSdK4AimLDRv70ypB97L9lzMmDlMKy8CQa20AuroYeZ77AgtpjzOVnSrBBIENWRCiRc
         elogZg/UOmOgI7nNL130bYIZLGwLdXGrrlet16+9hTkz8+KIIm61s7BR7QTYN4jiyT4q
         FKyIvCM9A5g8Pb3dSmMJ1wdl+FpqLtZSAmz+n+MOu9VkEs4exSOPOL2S0nyTe6ZpKd1G
         4WrFtJwhRkmCU0w9t4p8S+zYE3EcshcBme0wKw0umqaH7oY8YeIYWFYShcjhV37gYQM+
         RNhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=B4cmagUJvqsvM8KJ5vcfLLw3GzVKlYfhlZ7WKpaii2Q=;
        b=YbfweHOi2Tz+s2wXm4d/Li2WaVleLC4DC69RdcXy/rLrSze5/hdkN/8gbAMxmHrXdd
         Lii1o1SxlArwNaqkK62O+Zwmxht/NC1JtLxYDmCRaaPse9PINALJdtCCUUZFvkvuhHFM
         CvxaHAGVIWPZ11a3KwGIncQTLsZyMUyURimOTtQ5Bf7mF0NG4gfe5C+WBHixOzuGkoGB
         vEf4Wi0Eyhw5BxGBpnNH83znVO0Lb1aD0vHK2RMHS1BdbgAQKZ2YS09k7J+uP5s336G3
         4r7a7+9VLhVPXcM4YOYltVjZrWrbhXQkASq7JLYsbkUlnqnL1qRQsuPAwGtWyZ+ezVxA
         8GrQ==
X-Gm-Message-State: AOAM532fJdY1Hwk4XOeDHVv99N8vFxnJiC1f7n4my1vo1+1Qv/dTnQ7k
        9syzw+XZPpgJS9a+nUofHn60JioiWQ8V
X-Google-Smtp-Source: 
 ABdhPJz0ATVlqOcvXwgcYlNfRWv/oEcTQtMpwLVM4J6J727f8fSNNP+cR7MOSfTNDQ2kHT21jmqtIgkIu85h
Sender: "qperret via sendgmr" <qperret@r2d2-qp.c.googlers.com>
X-Received: from r2d2-qp.c.googlers.com
 ([fda3:e722:ac3:cc00:28:9cb1:c0a8:1652])
 (user=qperret job=sendgmr) by 2002:ad4:4f41:: with SMTP id
 eu1mr4188454qvb.1.1610124838785; Fri, 08 Jan 2021 08:53:58 -0800 (PST)
Date: Fri,  8 Jan 2021 16:53:49 +0000
Message-Id: <20210108165349.747359-1-qperret@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH] KVM: Documentation: Fix spec for KVM_CAP_ENABLE_CAP_VM
From: Quentin Perret <qperret@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        "open list:KERNEL VIRTUAL MACHINE (KVM)" <kvm@vger.kernel.org>,
        "open list:DOCUMENTATION" <linux-doc@vger.kernel.org>,
        open list <linux-kernel@vger.kernel.org>
Cc: android-kvm@google.com, kernel-team@android.com,
        Quentin Perret <qperret@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The documentation classifies KVM_ENABLE_CAP with KVM_CAP_ENABLE_CAP_VM
as a vcpu ioctl, which is incorrect. Fix it by specifying it as a VM
ioctl.

Fixes: e5d83c74a580 ("kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic")
Signed-off-by: Quentin Perret <qperret@google.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: __kvm_vcpu_halt can be static
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12006347
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 996C8C433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 10:56:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5000423977
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 10:56:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728183AbhAHK4S (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 05:56:18 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:34570 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727646AbhAHK4R (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 Jan 2021 05:56:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610103291;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=UoWmJXSbQgP5GKJxH0Tujf7dGsDbgivX1oOEbaf2iwM=;
        b=Kk+AkL0BOFXATreSCJoiHhfuVGcDch4X3nPchMMFI3IF977/gKGy69+eJgd90ZKCBCvOKC
        yXgiPkl/8UPS1ePoOqsbWXUo0gCCQdpzX5tlMoyi7Mj5pjdNL1dcU/2YSwzLTB5OTGClZF
        tgcmdfJ31wvUWcn+dfGrCZwiltdrnyA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-532-imqUcbM9OqyMTgXQMTMqwg-1; Fri, 08 Jan 2021 05:54:49 -0500
X-MC-Unique: imqUcbM9OqyMTgXQMTMqwg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 884B710054FF;
        Fri,  8 Jan 2021 10:54:48 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3A0D75D9C0;
        Fri,  8 Jan 2021 10:54:48 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: __kvm_vcpu_halt can be static
Date: Fri,  8 Jan 2021 05:54:47 -0500
Message-Id: <20210108105447.37906-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RESEND v13 01/10] KVM: x86: Move common set/get handler of MSR_IA32_DEBUGCTLMSR to VMX
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12005535
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB15FC433E6
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:45:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B1E082376F
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:45:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729839AbhAHBox (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 20:44:53 -0500
Received: from mga09.intel.com ([134.134.136.24]:27995 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727634AbhAHBow (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 20:44:52 -0500
IronPort-SDR: 
 r3kZaOV3eb1wCpUjQmMdY5JteWHyMpwONl2aMpt9v86WU6bVUL71H1hFEinob5vQAELsXSlBKB
 tJY7CrDV1Sqw==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="177672373"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="177672373"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 17:43:06 -0800
IronPort-SDR: 
 IiVdmPrNfR8tCmm1dCXV3J6sO4HudquLXC/+/skJNlCoZI++9680SGYcjdSeF3eiG02ECHZQ1N
 zhKImGW8G+lg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="379938023"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 07 Jan 2021 17:43:03 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>, ak@linux.intel.com,
        wei.w.wang@intel.com, kan.liang@intel.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v13 01/10] KVM: x86: Move common set/get handler of
 MSR_IA32_DEBUGCTLMSR to VMX
Date: Fri,  8 Jan 2021 09:36:55 +0800
Message-Id: <20210108013704.134985-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210108013704.134985-1-like.xu@linux.intel.com>
References: <20210108013704.134985-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SVM already has specific handlers of MSR_IA32_DEBUGCTLMSR in the
svm_get/set_msr, so the x86 common part can be safely moved to VMX.

Add vmx_supported_debugctl() to refactor the throwing logic of #GP.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/kvm/vmx/capabilities.h |  5 +++++
 arch/x86/kvm/vmx/vmx.c          | 19 ++++++++++++++++---
 arch/x86/kvm/x86.c              | 13 -------------
 3 files changed, 21 insertions(+), 16 deletions(-)

```
