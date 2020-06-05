#### [PATCH 1/3] KVM: arm64: Save the host's PtrAuth keys in non-preemptible context
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11587961
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC276739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 13:34:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0E9220772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 13:34:08 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591277648;
	bh=oTpdh0V2Z95uY3LBT8s4QiNnX2wWztmbveBiUjivoGs=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=X0mGr0U9aURgMUJBkqpRckti2Wa3MeHfvdCKtNnGfN9OHW8rC89UmvK4fA06x7Wu3
	 TCbZP6OsI5inMN2gLwk6W8qTjYlIN+aklNmHbe/f1/CSsV+srD29FPFKuSPEu6018z
	 Szw9yUw63nvgK1fmUSaZLCBhy//dBesLX3Z0x0jA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728639AbgFDNeH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 09:34:07 -0400
Received: from mail.kernel.org ([198.145.29.99]:36190 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728617AbgFDNeG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Jun 2020 09:34:06 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B0BDC207F5;
        Thu,  4 Jun 2020 13:34:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591277645;
        bh=oTpdh0V2Z95uY3LBT8s4QiNnX2wWztmbveBiUjivoGs=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=YR6CZ4InhWsUIB0fnTVAgtFWHZM0Q9V817LIfrnpJkEIN3cbTWbaHSqpkaGScFNAF
         dKit3INlFzUfog/sqPThe1V17GKxiCOkAU+HJ0Mj9RSzznP/Zn8zAOQKvR/mHDmhIa
         6qEZ+dO3rA3gYktLJj6oAvywWHIrYTn7S/Cnk4OM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jgq0S-000G3O-6u; Thu, 04 Jun 2020 14:34:04 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com,
        stable@vger.kernel.org
Subject: [PATCH 1/3] KVM: arm64: Save the host's PtrAuth keys in
 non-preemptible context
Date: Thu,  4 Jun 2020 14:33:52 +0100
Message-Id: <20200604133354.1279412-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200604133354.1279412-1-maz@kernel.org>
References: <20200604133354.1279412-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 catalin.marinas@arm.com, mark.rutland@arm.com, kernel-team@android.com,
 stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using the PtrAuth feature in a guest, we need to save the host's
keys before allowing the guest to program them. For that, we dump
them in a per-CPU data structure (the so called host context).

But both call sites that do this are in preemptible context,
which may end up in disaster should the vcpu thread get preempted
before reentering the guest.

Instead, save the keys eagerly on each vcpu_load(). This has an
increased overhead, but is at least safe.

Cc: stable@vger.kernel.org
Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Mark Rutland <mark.rutland@arm.com>
---
 arch/arm64/include/asm/kvm_emulate.h |  6 ------
 arch/arm64/kvm/arm.c                 | 18 +++++++++++++++++-
 arch/arm64/kvm/handle_exit.c         | 19 ++-----------------
 3 files changed, 19 insertions(+), 24 deletions(-)

```
#### [PATCH] KVM: nVMX: Inject #GP when nested_vmx_get_vmptr() fails to read guest memory
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11588079
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07E7A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 14:32:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3020207DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 14:32:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Csgr9ZYN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728990AbgFDOcX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 10:32:23 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:44992 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728919AbgFDOcX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Jun 2020 10:32:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591281142;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=h9M1fLh8Ru9H4w+WFRAfiLMCmRmx0L8dSLxiYIXuu4E=;
        b=Csgr9ZYNuGxpyogb4pKIA22w6EqtVTG9gg/1Uh8UVvOy9mHelu/iQ8yxLTs2Ic1BYsdUkQ
        1gAhlvHDwZG8P2LToCUgGcyHXpfDz8RIhfhgJXeTF1zBN+8FL3d+vbTeYUAOdiy1FdDbJw
        HAEuoqADy31TJco5nWIrrTMlwL1WHjA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-238-QJFS2nS7OyOa-MMajM20aw-1; Thu, 04 Jun 2020 10:32:20 -0400
X-MC-Unique: QJFS2nS7OyOa-MMajM20aw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7B75B1800D42;
        Thu,  4 Jun 2020 14:32:02 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.49])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C6FB7CCC1;
        Thu,  4 Jun 2020 14:32:00 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Inject #GP when nested_vmx_get_vmptr() fails to
 read guest memory
Date: Thu,  4 Jun 2020 16:31:58 +0200
Message-Id: <20200604143158.484651-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Syzbot reports the following issue:

WARNING: CPU: 0 PID: 6819 at arch/x86/kvm/x86.c:618 kvm_inject_emulated_page_fault+0x210/0x290 arch/x86/kvm/x86.c:618
...
Call Trace:
...
RIP: 0010:kvm_inject_emulated_page_fault+0x210/0x290 arch/x86/kvm/x86.c:618
...
 nested_vmx_get_vmptr+0x1f9/0x2a0 arch/x86/kvm/vmx/nested.c:4638
 handle_vmon arch/x86/kvm/vmx/nested.c:4767 [inline]
 handle_vmon+0x168/0x3a0 arch/x86/kvm/vmx/nested.c:4728
 vmx_handle_exit+0x29c/0x1260 arch/x86/kvm/vmx/vmx.c:6067

'exception' we're trying to inject with kvm_inject_emulated_page_fault() comes from
  nested_vmx_get_vmptr()
   kvm_read_guest_virt()
     kvm_read_guest_virt_helper()
       vcpu->arch.walk_mmu->gva_to_gpa()

but it is only set when GVA to GPA conversion fails. In case it doesn't but
we still fail kvm_vcpu_read_guest_page(), X86EMUL_IO_NEEDED is returned and
nested_vmx_get_vmptr() calls kvm_inject_emulated_page_fault() with zeroed
'exception'. This happen when e.g. VMXON/VMPTRLD/VMCLEAR argument is MMIO.

KVM could've handled the request correctly by going to userspace and
performing I/O but there doesn't seem to be a good need for such requests
in the first place. Sane guests should not call VMXON/VMPTRLD/VMCLEAR with
anything but normal memory. Just inject #GP to find insane ones.

Reported-by: syzbot+2a7156e11dc199bdbd8a@syzkaller.appspotmail.com
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 19 +++++++++++++++++--
 1 file changed, 17 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Assign correct value to array.maxnent
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11586857
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1353159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 02:43:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD4A120657
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 02:43:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726853AbgFDCnO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 3 Jun 2020 22:43:14 -0400
Received: from mga04.intel.com ([192.55.52.120]:46889 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725946AbgFDCnO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Jun 2020 22:43:14 -0400
IronPort-SDR: 
 hjdir4Z+gMysQacx1M3TC3DWxl5U9n+aAubNzoOCNDb6isU2OrIa+ZVsOu0PvVo/XtjwEW3LPk
 Q+DosVcEIOgA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Jun 2020 19:43:13 -0700
IronPort-SDR: 
 DMUHMEnWDRklmY95LvDL49LiNPEhLY0j5aBlXnFuymzxcclPQ0W7K8iq9sRmao+y2ZCW0h8oBZ
 Prw2wBpmEtlA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,470,1583222400";
   d="scan'208";a="304571640"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by fmsmga002.fm.intel.com with ESMTP; 03 Jun 2020 19:43:11 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH] KVM: x86: Assign correct value to array.maxnent
Date: Thu,  4 Jun 2020 10:43:04 +0800
Message-Id: <20200604024304.14643-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delay the assignment of array.maxnent to use correct value for the case
cpuid->nent > KVM_MAX_CPUID_ENTRIES.

Fixes: e53c95e8d41e ("KVM: x86: Encapsulate CPUID entries and metadata in struct")
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: Assign correct value to array.maxnent
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11586905
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24B02912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 04:17:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0689C20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 04:17:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726260AbgFDERJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 00:17:09 -0400
Received: from mga05.intel.com ([192.55.52.43]:16104 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725959AbgFDERI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Jun 2020 00:17:08 -0400
IronPort-SDR: 
 UtNw6hvOlDZdYbt12xOlrfJfSWOBksFqXNVKHxUawtL/IyEtVn0biCoTJ0Y8i+PmWiGyteyjie
 MiQnqlMDMecg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Jun 2020 21:17:08 -0700
IronPort-SDR: 
 pT9a6wKXzrM+ieidBq3xAmrP+FCuj7BAtH3eZh6VKon148ga1t7N9JD1jIjMENjgD2ReP1SSvH
 euQ9AdxBkgNg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,471,1583222400";
   d="scan'208";a="416782285"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga004.jf.intel.com with ESMTP; 03 Jun 2020 21:17:06 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2] KVM: x86: Assign correct value to array.maxnent
Date: Thu,  4 Jun 2020 12:16:36 +0800
Message-Id: <20200604041636.1187-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Reply-To: <20200604024304.14643-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delay the assignment of array.maxnent to use correct value for the case
cpuid->nent > KVM_MAX_CPUID_ENTRIES.

Fixes: e53c95e8d41e ("KVM: x86: Encapsulate CPUID entries and metadata in struct")
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
v2:
   - remove "const" of maxnent to fix build error.
---
 arch/x86/kvm/cpuid.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] vfio-ccw: make vfio_ccw_regops variables declarations static
##### From: Vasily Gorbik <gor@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vasily Gorbik <gor@linux.ibm.com>
X-Patchwork-Id: 11587803
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 693A560D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 11:20:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A1C92077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 11:20:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727110AbgFDLUz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 07:20:55 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:50194 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727097AbgFDLUy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Jun 2020 07:20:54 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 054B31La176109;
        Thu, 4 Jun 2020 07:20:52 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31eu6q1c5x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 04 Jun 2020 07:20:52 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 054B320S176182;
        Thu, 4 Jun 2020 07:20:52 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31eu6q1c5b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 04 Jun 2020 07:20:52 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 054BFJJ4030094;
        Thu, 4 Jun 2020 11:20:50 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04fra.de.ibm.com with ESMTP id 31bf4840yp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 04 Jun 2020 11:20:50 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 054BKldR18678224
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 4 Jun 2020 11:20:47 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 994E55204F;
        Thu,  4 Jun 2020 11:20:47 +0000 (GMT)
Received: from localhost (unknown [9.145.37.112])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 2E01152052;
        Thu,  4 Jun 2020 11:20:47 +0000 (GMT)
Date: Thu, 4 Jun 2020 13:20:45 +0200
From: Vasily Gorbik <gor@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH] vfio-ccw: make vfio_ccw_regops variables declarations static
Message-ID: 
 <patch.git-a34be7aede18.your-ad-here.call-01591269421-ext-5655@work.hours>
References: <20200603112716.332801-1-cohuck@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200603112716.332801-1-cohuck@redhat.com>
X-Patchwork-Bot: notify
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-04_07:2020-06-02,2020-06-04 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=1 malwarescore=0 adultscore=0 spamscore=0 mlxlogscore=837
 bulkscore=0 clxscore=1015 priorityscore=1501 cotscore=-2147483648
 phishscore=0 impostorscore=0 mlxscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006040076
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes the following sparse warnings:
drivers/s390/cio/vfio_ccw_chp.c:62:30: warning: symbol 'vfio_ccw_schib_region_ops' was not declared. Should it be static?
drivers/s390/cio/vfio_ccw_chp.c:117:30: warning: symbol 'vfio_ccw_crw_region_ops' was not declared. Should it be static?

Signed-off-by: Vasily Gorbik <gor@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_chp.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
