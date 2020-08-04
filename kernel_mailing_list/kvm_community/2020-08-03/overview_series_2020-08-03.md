#### [PATCH 1/6] RISC-V: Add a non-void return for sbi v02 functions
##### From: Atish Patra <atish.patra@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Atish Patra <atish.patra@wdc.com>
X-Patchwork-Id: 11698507
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D16D613B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 17:59:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DBB7422BF3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 17:59:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="ldIiBbwi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728597AbgHCR7S (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 13:59:18 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:64728 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726802AbgHCR7R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 13:59:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1596477556; x=1628013556;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=/WuBKKqQJ2DS9gLpxSbna82b/Rj8bNfTeDN1/MeY4to=;
  b=ldIiBbwi01R8GjOrznEfGRVF91p35hAR0FPw2lTYTs87y9JjAOW15NkB
   zfyVA7JENPYaSmcW78RjzjLvNySUBxiaOoM4ujX844OelayDqOVWeKNRl
   nPr5lo7oaRjyprQrTKhrxY/7xtnIMDL3N2vz+mh9bgdtEErFB8K1J5Do5
   qynOt+d22XVMr72LyZrMnWXiMPcWGJaavLqI4IVG4aj8ATlMOVa8j79Es
   d6sH/IIeKr9QXm8iyiWxtNWxjiJjNSS1WFphXXwCxoJCJrbxbz0iAOxIP
   AI61/mvIhUHuWEbaOqow0NOVuHQpDndAmt/6SD2Pv9tylBY//Gv4SULXl
   w==;
IronPort-SDR: 
 hjvCoNLI7Qmdt/N/TBHIluW8PrnS1zVkC7z/tsj0dJ2B4JyjoyiVDlrc/9rm1P6iFo/UhOD0s1
 gq81Aei+iE4DNGTNP6gdHw1g9ehNc48cB7Et9I4z4OgvxMqM8/OsIvd3QbX8DQRaegDuuhTlXu
 QsrP7VPZEQob2+xQuVB3gipO+jY8oY6uTWGeXSC8pe2h/8db0uSSqmt91UHK0yZyg7nUChEccY
 ObL2I/dAf5aKkZRDW97N6a9EfPnKwDB92V6JCM5bLwDBYdlG8ReMEx+lguWmqW00fkS8f2+Hrr
 nMs=
X-IronPort-AV: E=Sophos;i="5.75,430,1589212800";
   d="scan'208";a="144033181"
Received: from h199-255-45-14.hgst.com (HELO uls-op-cesaep01.wdc.com)
 ([199.255.45.14])
  by ob1.hgst.iphmx.com with ESMTP; 04 Aug 2020 01:59:04 +0800
IronPort-SDR: 
 4VAC0m8TM8E3fJxPustvPVkRIyVs3DuwvS4bCPK7ne4qP583hDFvVWsO+RdpJnSZdbnFBoifzF
 u6y28LnvxXiw==
Received: from uls-op-cesaip01.wdc.com ([10.248.3.36])
  by uls-op-cesaep01.wdc.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Aug 2020 10:47:06 -0700
IronPort-SDR: 
 b+L5ix2uhA5t3rcfUs2Aw7nrz9gwA9OaAzaqQxbJ4RQos5fVRvplQWg6A9RrXVtMjAiNbZUBpf
 aiMRiMpi9kvA==
WDCIronportException: Internal
Received: from cnf007830.ad.shared (HELO jedi-01.hgst.com) ([10.86.58.196])
  by uls-op-cesaip01.wdc.com with ESMTP; 03 Aug 2020 10:59:03 -0700
From: Atish Patra <atish.patra@wdc.com>
To: kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org
Cc: Atish Patra <atish.patra@wdc.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Anup Patel <anup.patel@wdc.com>,
        Kefeng Wang <wangkefeng.wang@huawei.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Alistair Francis <Alistair.Francis@wdc.com>
Subject: [PATCH 1/6] RISC-V: Add a non-void return for sbi v02 functions
Date: Mon,  3 Aug 2020 10:58:41 -0700
Message-Id: <20200803175846.26272-2-atish.patra@wdc.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20200803175846.26272-1-atish.patra@wdc.com>
References: <20200803175846.26272-1-atish.patra@wdc.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SBI v0.2 functions can return an error code from SBI implementation.
We are already processing the SBI error code and coverts it to the Linux
error code.

Propagate to the error code to the caller as well. As of now, kvm is the
only user of these error codes.

Signed-off-by: Atish Patra <atish.patra@wdc.com>
---
 arch/riscv/include/asm/sbi.h |  8 ++++----
 arch/riscv/kernel/sbi.c      | 32 ++++++++++++++++----------------
 2 files changed, 20 insertions(+), 20 deletions(-)

```
#### [PATCH v4 1/3] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11699185
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8D3B14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:15:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0699422CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:15:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="KbV9GEfn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729211AbgHCVO7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 17:14:59 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:7237 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729177AbgHCVO5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 17:14:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596489294; x=1628025294;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=qdwzlFqSs011PwSP9OouF95I4cXaDgftnH/m6CTUpvk=;
  b=KbV9GEfnK2FslQtXGMJGDN5oo30IBatyQljE8k3Nvjdw75O5p7hghnQL
   0/BFBMyuufRKt35EOejV2XolAyZu9aAO0hUASZw4DdfQ9RLkmP/ih5AZp
   7qQQRfrj1WIZr+bTTf47Ja4lpwLjx4XHOR2Nh762mGhjQw9pTYDYknLij
   g=;
IronPort-SDR: 
 w8j/mdB/Oq3LegnGL0ggI3TobcuAA4294JqZ7x8zT/NZz/njjYPK1bR5I/yFCieugjkC051f87
 S+9eeJwEfzTw==
X-IronPort-AV: E=Sophos;i="5.75,431,1589241600";
   d="scan'208";a="65228583"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 03 Aug 2020 21:14:42 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-303d0b0e.us-east-1.amazon.com (Postfix) with
 ESMTPS id CB195A1F9A;
        Mon,  3 Aug 2020 21:14:38 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 Aug 2020 21:14:38 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.145) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 Aug 2020 21:14:34 +0000
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
Subject: [PATCH v4 1/3] KVM: x86: Deflect unknown MSR accesses to user space
Date: Mon, 3 Aug 2020 23:14:21 +0200
Message-ID: <20200803211423.29398-2-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200803211423.29398-1-graf@amazon.com>
References: <20200803211423.29398-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D36UWB001.ant.amazon.com (10.43.161.84) To
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

  - Mention exit reasons in re-enter mandatory section of API documentation
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
#### [PATCH v3 1/4] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11697939
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 25F3F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 12:27:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 18082207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 12:27:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728551AbgHCM13 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 08:27:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42466 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728546AbgHCM11 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 08:27:27 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2B8A3C061756;
        Mon,  3 Aug 2020 05:27:27 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 1F2E74CB; Mon,  3 Aug 2020 14:27:24 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH v3 1/4] KVM: SVM: nested: Don't allocate VMCB structures on
 stack
Date: Mon,  3 Aug 2020 14:27:05 +0200
Message-Id: <20200803122708.5942-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200803122708.5942-1-joro@8bytes.org>
References: <20200803122708.5942-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Do not allocate a vmcb_control_area and a vmcb_save_area on the stack,
as these structures will become larger with future extenstions of
SVM and thus the svm_set_nested_state() function will become a too large
stack frame.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/nested.c | 47 +++++++++++++++++++++++++++------------
 1 file changed, 33 insertions(+), 14 deletions(-)

```
#### [PATCH v4 1/4] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11698819
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A81A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:00:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4A2522CAF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:00:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729299AbgHCVAk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 17:00:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36998 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729285AbgHCVAj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 17:00:39 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ED7EEC061756;
        Mon,  3 Aug 2020 14:00:38 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 21E0F1F0; Mon,  3 Aug 2020 23:00:36 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH v4 1/4] KVM: SVM: nested: Don't allocate VMCB structures on
 stack
Date: Mon,  3 Aug 2020 23:00:31 +0200
Message-Id: <20200803210034.26386-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200803210034.26386-1-joro@8bytes.org>
References: <20200803210034.26386-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Do not allocate a vmcb_control_area and a vmcb_save_area on the stack,
as these structures will become larger with future extenstions of
SVM and thus the svm_set_nested_state() function will become a too large
stack frame.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/nested.c | 47 +++++++++++++++++++++++++++------------
 1 file changed, 33 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: tscdeadline timer testing when apic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11697535
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA81C1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 08:02:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C25F820738
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 08:02:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mOXLUEYd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725992AbgHCICP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 04:02:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57958 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725831AbgHCICN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 04:02:13 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1388FC06174A
        for <kvm@vger.kernel.org>; Mon,  3 Aug 2020 01:02:12 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id d4so1046050pjx.5
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 01:02:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=L2PblpgL3CGwc/wlyAeS1CF9qVtD8Duc1V7eteOfD0U=;
        b=mOXLUEYdmnWZcV98Jw0+r95FfC3RTrAUzbxzD/ODbkZ2fiK22TAC8JJiDYRK5iwOiC
         3kbSNZ2LhwU1B1C/Zeh/O8UtF4+bw0QCcLxjBB/e84ZmllmU4a1Gpr+ZPNr02pxF/qgS
         emwiRlPR7qbTee7oWplOYjf4U9oHHf5th8B2oHKpx2Iv9uViBltXLLYJqlJh9h912g44
         O3N9mqitQ1p6z2UJpUoPbq9yvPdmr1WquwNKSztcXW208RScxgE6agx0QFceY/A9VHt1
         bjjSkHUtrndnVpRgtvvp2mjpdW2NY63Lic01maMZpzyS8NaBCie3LXRvs4GwMeW1sIze
         kB7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=L2PblpgL3CGwc/wlyAeS1CF9qVtD8Duc1V7eteOfD0U=;
        b=GzQdO0CsQbtrr2m6vllxjpWxdhFm1HXQGxfCeLfcAJ3bDGrIZt112/rVStkFzAa6yD
         l2Yz+domCbYqFhvocj7cU9gonGT3GeDhG6ZF4g4Mbb1KutZzC+2GydU3VoCrZxtSLe4Z
         5gbqBnqszmMjJAji4aWOvI7k6XHZm/2T1VufsnykkovvGC8BMCS5GKyp3ZqDYZoexAbq
         kHMNHhlcWhamuT2HN5RbaZb1MKry3FN9ljSncb4svL3wDK7dbeVnl253ZnzcSEHc8ijF
         04rR0KbcCsa+yp0x0l4acQK3gdN6OhgwJttzFAR+XCM5dsCBlHcQBTQMHlAtP21paGEP
         Ok8Q==
X-Gm-Message-State: AOAM530JF9eB9wwlyXz26QLZntF+R5mmdjYmKBDmoyCUnau2EuOnLMQx
        XTZiFMyRtKylilvkviPxKArUBDek
X-Google-Smtp-Source: 
 ABdhPJyJBtb19IzBZaRClC1AVH+IuYPskgQrTu0+lcIy//03kBTQqkCSDq5etJT2sWp/+bLf46iThA==
X-Received: by 2002:a17:90b:4a4e:: with SMTP id
 lb14mr3938431pjb.228.1596441731500;
        Mon, 03 Aug 2020 01:02:11 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 h63sm16559661pjb.29.2020.08.03.01.02.09
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 03 Aug 2020 01:02:10 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [kvm-unit-tests PATCH] x86: tscdeadline timer testing when apic is hw
 disabled
Date: Mon,  3 Aug 2020 16:01:55 +0800
Message-Id: <1596441715-14959-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch adds tscdeadline timer testing when apic is hw disabled.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 x86/apic.c | 27 +++++++++++++++++++++------
 1 file changed, 21 insertions(+), 6 deletions(-)

```
#### [PATCH v2 20/24] vhost/vdpa: switch to new helpers
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11698817
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3881613B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:00:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78ADA22CAD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:00:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I2Cy6OZF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729216AbgHCVAW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 17:00:22 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:57340 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729206AbgHCVAW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 17:00:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596488420;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=f1A99Kan+ToYvUmOMuODkd0BFkRSjBNq3WkT2nA5570=;
        b=I2Cy6OZFp44adUcSURPKsc2f308oqyHjBVbCF86tsq9zgdzWGr2757+z7888M6qjHFWpXd
        F4SNu6cg0fdfb0DjLU+qbBUWLK69LtYVJlt4ScUYhLO22EX9Sf5FWHpB/irckFQuaOsZKT
        AjB6qe0WS4AcODfnwhzh+cxf7z9gbdA=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-210-MIW-VOxgMZ6-40XLWko8wA-1; Mon, 03 Aug 2020 17:00:16 -0400
X-MC-Unique: MIW-VOxgMZ6-40XLWko8wA-1
Received: by mail-qk1-f200.google.com with SMTP id 1so13762517qki.22
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 14:00:16 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=f1A99Kan+ToYvUmOMuODkd0BFkRSjBNq3WkT2nA5570=;
        b=HRWMukSTCwRX+m8fcneTiwFm+1nGEOhtVyY2+yWZ+PGCe0f2d1/Dg6hyqqHS9PwVkp
         6tvFqnj4ZvgG9Cah9K/92Jt68hApaWW6yCPp68pdJ+unQdOUXqjkdVdkvzGAkmmJhGfY
         DvcZAzd0voTizQc9IMPD76Jp5HDYyANU/cmvXVr5S+rDUJG/j2HMrukJmZO08NdGqQJ9
         L2tT/YlaLRxfgcYOU94AUpKagkdv5nU2KKf7NbkWW3S5+xRN8rc0+S90e93or0KGA/3d
         AsP5bD9Q1tGWRj81nGYWbkYqUQa7KBHXAxrZ3tmPfjdTjLRcfyzSEAkynBXnAGzUPjDK
         oK3g==
X-Gm-Message-State: AOAM530jibLmkD5a+U8eIePZ6bo6yxiWljeI3I7Nf7tCOElSXs/LPQ94
        Q0I3fS7ofsqLC8+qzIleCJS5RRoy7gnLn3EBGG8LSWbsHxmwyZ1V+qSM4yX7/+a2lFjfgDEPLbx
        8L66nF/Jwn4r5
X-Received: by 2002:ae9:f409:: with SMTP id y9mr17081844qkl.383.1596488415784;
        Mon, 03 Aug 2020 14:00:15 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyOLsF2kRKHhVMrVuK1ExTkYEV3u00bvHZC77i72ooYLjKbjM4TmW/w7ndizuS2cvXbLFA8ag==
X-Received: by 2002:ae9:f409:: with SMTP id y9mr17081819qkl.383.1596488415580;
        Mon, 03 Aug 2020 14:00:15 -0700 (PDT)
Received: from redhat.com (bzq-79-177-102-128.red.bezeqint.net.
 [79.177.102.128])
        by smtp.gmail.com with ESMTPSA id
 x137sm20654324qkb.47.2020.08.03.14.00.13
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 03 Aug 2020 14:00:15 -0700 (PDT)
Date: Mon, 3 Aug 2020 17:00:11 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH v2 20/24] vhost/vdpa: switch to new helpers
Message-ID: <20200803205814.540410-21-mst@redhat.com>
References: <20200803205814.540410-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200803205814.540410-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For new helpers handling legacy features to be effective,
vhost needs to invoke them. Tie them in.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vdpa.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
