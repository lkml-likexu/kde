

#### [PATCH v2 0/2] KVM: arm64: Fix handling of S1PTW
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Sep 15 10:42:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11776069
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65BEF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 10:49:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B99421D24
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 10:49:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1600166947;
	bh=+f+XJhOhIVIVtwBYBolA4BBiPSB/0HpuyUUu4Y/SScw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=fyS1JXstLkWV/E9HZamtrq4vTcFycUftoRtOBfnlepzHgkSaZXHrKcdrXljVz0Cpm
	 ocum1NHsBvge6uBETQlhmMmf/FML9tK9mUSKGJ+JHICXI52xdrXmMOxjN7JJyai8Ov
	 9ysk9ghqHF1s5ZFnDwrVVtiMzq1uxhsiyjmel4l0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726361AbgIOKtB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 06:49:01 -0400
Received: from mail.kernel.org ([198.145.29.99]:46114 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726371AbgIOKmm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 06:42:42 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5163720735;
        Tue, 15 Sep 2020 10:42:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1600166561;
        bh=+f+XJhOhIVIVtwBYBolA4BBiPSB/0HpuyUUu4Y/SScw=;
        h=From:To:Cc:Subject:Date:From;
        b=OhQNwqQjsQqHgf+XtrZADhkQ8kIaELoQHZIkKRxF/yTjNoFhYellzfFrT7KdU/cVH
         g3SV4OLUKvTnoR9MRA3SymLaLC1wz4qhd5QNkf5jSJZ6ABi2rnhXEazzR0rFMeBSqi
         XegQfYfquryYLFgl1cEq67QW7a/CQ1R66jKqwpeA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kI8Q3-00ByDU-Ci; Tue, 15 Sep 2020 11:42:39 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: kernel-team@android.com, Will Deacon <will@kernel.org>
Subject: [PATCH v2 0/2] KVM: arm64: Fix handling of S1PTW
Date: Tue, 15 Sep 2020 11:42:16 +0100
Message-Id: <20200915104218.1284701-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com,
 will@kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I recently managed to trigger an interesting failure mode, where a
guest would be stuck on an instruction abort due to a permission
fault. Interestingly enough, this IABT had S1PTW set in the ESR,
indicating that it was trying to *write* to the PT. We fix it by
adding the execute permission (it's an IABT, after all...), and going
nowhere fast.

Note that it can only happen on a system that can perform automatic
updates of the page table flags.

This small series fixes the issue by revamping the S1PTW handling in
the context of execution faults. The first patch fixes the bug, and is
definitely a stable candidate. The second patch is merely a cleanup,
which can wait.

Tested on an A55-based board.

* From v1:
  - Rename kvm_vcpu_dabt_iss1tw() to kvm_vcpu_abt_iss1tw()
  - Don't overload kvm_vcpu_trap_is_iabt()
  - Introduce kvm_vcpu_trap_is_exec_fault()

Marc Zyngier (2):
  KVM: arm64: Assume write fault on S1PTW permission fault on
    instruction fetch
  KVM: arm64: Remove S1PTW check from kvm_vcpu_dabt_iswrite()

 arch/arm64/include/asm/kvm_emulate.h    | 14 +++++++++++---
 arch/arm64/kvm/hyp/include/hyp/switch.h |  2 +-
 arch/arm64/kvm/mmu.c                    |  4 ++--
 3 files changed, 14 insertions(+), 6 deletions(-)
```
#### [PATCH RFC 0/2] KVM: x86: allow for more CPUID entries
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Sep 15 15:43:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11777119
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAA8D14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 15:51:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C80C720936
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 15:51:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LLEva9hW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727495AbgIOPrP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 11:47:15 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:30008 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727455AbgIOPnp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 11:43:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600184596;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=S7LOvCl7XUVBU80Y/PU+FTVOH70oxm6JnXxMde/HKVE=;
        b=LLEva9hWSkYksK8FihM07TdSQcZklvlTOQpA+T2fUuK1hpZykRTeUdtSDU6gZstkduG2W3
        p1wHp/AcpDx0LicFCwmP7xLy0y3LYP9Etrst9GCnjuMAa1/cjyyIqdwS0JWXcrJi5IRq6g
        JFkW/j492lmhRNz5Xi5xgUJ7NIAxdjY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-409-HNLXfCHwMlOI095IlUogdg-1; Tue, 15 Sep 2020 11:43:12 -0400
X-MC-Unique: HNLXfCHwMlOI095IlUogdg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA9D2CF983;
        Tue, 15 Sep 2020 15:43:10 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 120A119D61;
        Tue, 15 Sep 2020 15:43:07 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Wei Huang <whuang2@amd.com>, linux-kernel@vger.kernel.org
Subject: [PATCH RFC 0/2] KVM: x86: allow for more CPUID entries
Date: Tue, 15 Sep 2020 17:43:04 +0200
Message-Id: <20200915154306.724953-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With QEMU and newer AMD CPUs (namely: Epyc 'Rome') the current limit for
KVM_MAX_CPUID_ENTRIES(80) is reported to be hit. Last time it was raised
from '40' in 2010. We can, of course, just bump it a little bit to fix
the immediate issue but the report made me wonder why we need to pre-
allocate vcpu->arch.cpuid_entries array instead of sizing it dynamically.
This RFC is intended to feed my curiosity.

Very mildly tested with selftests/kvm-unit-tests and nothing seems to
break. I also don't have access to the system where the original issue
was reported but chances we're fixing it are very good IMO as just the
second patch alone was reported to be sufficient.

Reported-by: Dr. David Alan Gilbert <dgilbert@redhat.com>

Vitaly Kuznetsov (2):
  KVM: x86: allocate vcpu->arch.cpuid_entries dynamically
  KVM: x86: bump KVM_MAX_CPUID_ENTRIES

 arch/x86/include/asm/kvm_host.h |  4 +--
 arch/x86/kvm/cpuid.c            | 55 ++++++++++++++++++++++++---------
 arch/x86/kvm/x86.c              |  1 +
 3 files changed, 43 insertions(+), 17 deletions(-)
Tested-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
```
#### [PATCH v2 0/2] KVM: VMX: Clean up IRQ/NMI handling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Sep 15 19:15:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11777607
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88EC1618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:19:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74A6F206B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:19:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726454AbgIOTTc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 15:19:32 -0400
Received: from mga18.intel.com ([134.134.136.126]:37628 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728002AbgIOTPU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 15:15:20 -0400
IronPort-SDR: 
 jpu6sbgfgarRvochp2TdkCIwnWBE9evbVdFpNcCQMcb/fthZ4t9rILwK9HUCiJXY9sWDe2HbGf
 qqhb3YSUS00Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9745"; a="147082733"
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="147082733"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Sep 2020 12:15:08 -0700
IronPort-SDR: 
 +QXOI6frlxKJqQT9QSK1/luWh9YStL/bPt1O4xifBlSTe5DlR1HQRd9PoXNv+wbD3QBZBeMu28
 oI2xAZlhyhdg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="507694459"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga005.fm.intel.com with ESMTP; 15 Sep 2020 12:15:06 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Josh Poimboeuf <jpoimboe@redhat.com>,
        Uros Bizjak <ubizjak@gmail.com>,
        Andi Kleen <ak@linux.intel.com>
Subject: [PATCH v2 0/2] KVM: VMX: Clean up IRQ/NMI handling
Date: Tue, 15 Sep 2020 12:15:03 -0700
Message-Id: <20200915191505.10355-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up KVM's handling of IRQ and NMI exits to move the invocation of the
IRQ handler to a standalone assembly routine, and to then consolidate the
NMI handling to use the same indirect call approach instead of using INTn.

The IRQ cleanup was suggested by Josh Poimboeuf in the context of a false
postive objtool warning[*].  I believe Josh intended to use UNWIND hints
instead of trickery to avoid objtool complaints.  I opted for trickery in
the form of a redundant, but explicit, restoration of RSP after the hidden
IRET.  AFAICT, there are no existing UNWIND hints that would let objtool
know that the stack is magically being restored, and adding a new hint to
save a single MOV <reg>, <reg> instruction seemed like overkill.

The NMI consolidation was loosely suggested by Andi Kleen.  Andi's actual
suggestion was to export and directly call the NMI handler, but that's a
more involved change (unless I'm misunderstanding the wants of the NMI
handler), whereas piggybacking the IRQ code is simple and seems like a
worthwhile intermediate step.

Sean Christopherson (2):
  KVM: VMX: Move IRQ invocation to assembly subroutine
  KVM: VMX: Invoke NMI handler via indirect call instead of INTn

 arch/x86/kvm/vmx/vmenter.S | 34 +++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c     | 61 +++++++++++---------------------------
 2 files changed, 51 insertions(+), 44 deletions(-)
```
#### [PATCH v3 0/5] s390x/pci: Accomodate vfio DMA limiting
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Tue Sep 15 19:14:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11777631
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE49E618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:30:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C9C620770
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:30:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="jlF6v3ym"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727835AbgIOTaq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 15:30:46 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:31576 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727755AbgIOTPN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 15:15:13 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08FJ2j49135732;
        Tue, 15 Sep 2020 15:14:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=20j6JrlEXmgHFapWnNr7/wYljvTENuSaVZCZUOeT8vQ=;
 b=jlF6v3ymvM000XPqoimQKJ/i7TVHjI/Y9vrq/RyjseBIYlY07urZBp1vtJwe0AZz2Khf
 0qJSl1oeLwnjQQubpMtm3cwb1ZQHk/mCojQqwKP/THh+8roJ8UCEUsiQuLrTDOpO43SS
 dsKfW5zGyXGFFhFfU5P0bKvcrrGpTFUXOJZSO6b8cQYtCdXtFizUAlY3PEFJ4nau31Vj
 VBBZtBdvo0ayDN7QY1Jm8lRdRoYsh8Q1O2Qx9IgK7GjsJ5E0DYMgy8RxUcJFEkCImpsh
 kqQG9yq1phYCr4P4KCXk2qC6iNqfL9oL7k5B4ex8QVFDoHI5EalPMsxp33XCMy+kL7Po aw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33k2pp1ewx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:14:52 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08FJ2peZ136533;
        Tue, 15 Sep 2020 15:14:52 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33k2pp1ewn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:14:52 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08FJ7mXs002872;
        Tue, 15 Sep 2020 19:14:51 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma04wdc.us.ibm.com with ESMTP id 33jgrgxv2p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 19:14:51 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 08FJEpwp28246444
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Sep 2020 19:14:51 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3EA4D112064;
        Tue, 15 Sep 2020 19:14:51 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 41AE2112061;
        Tue, 15 Sep 2020 19:14:47 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.85.51])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 15 Sep 2020 19:14:46 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, thuth@redhat.com, pasic@linux.ibm.com,
        borntraeger@de.ibm.com, mst@redhat.com, pbonzini@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v3 0/5] s390x/pci: Accomodate vfio DMA limiting
Date: Tue, 15 Sep 2020 15:14:38 -0400
Message-Id: <1600197283-25274-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-15_12:2020-09-15,2020-09-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 lowpriorityscore=0 mlxscore=0 bulkscore=0 suspectscore=0 adultscore=0
 priorityscore=1501 spamscore=0 impostorscore=0 clxscore=1015
 mlxlogscore=999 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009150147
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Kernel commit 492855939bdb added a limit to the number of outstanding DMA
requests for a type1 vfio container.  However, lazy unmapping in s390 can 
in fact cause quite a large number of outstanding DMA requests to build up
prior to being purged, potentially the entire guest DMA space.  This
results in unexpected 'VFIO_MAP_DMA failed: No space left on device'
conditions seen in QEMU.

This patchset adds support to qemu to retrieve the number of allowable DMA
requests via the VFIO_IOMMU_GET_INFO ioctl.  The patches are separated into
vfio hits which add support for reading in VFIO_IOMMU_GET_INFO capability
chains and getting the per-container dma_avail value, and s390 hits to 
track DMA usage on a per-container basis.

Associated kernel patch:
https://marc.info/?l=kvm&m=160019703922812&w=2

Changes from v2:
- Patch 1 (new): Added a placeholder linux-headers sync
- Patch 2: Re-arranged so that this patch that adds a shared routine for
  finding info capabilities is first
- Patch 3: Adjusted vfio_get_info_dma_avail() logic to be able to return
  true when the capability exists but the caller did not provide a buffer
  on input.
- Patch 4 (new): Introduce hw/s390x/s390-pci-vfio.* to better-separate PCI
  emulation code from code that interfaces with vfio
- Patch 4: s/s390_sync_dma_avail/s390_pci_update_dma_avail/ - Since it's
  now moved into a different file it can't be static so I added '_pci'.
- Patch 4: Use g_autofree as suggested - drop the goto/out as a result
- Patch 4+5: Added asserts() in a few locations per suggestion
- Patch 5: lowercase inline function names
- Patch 5: fix dma_avail initialization in rpcit_service_call() and ensure
  we still allow unmaps to call s390_pci_update_iotlb when dma_avail == 0

Matthew Rosato (5):
  linux-headers: update against 5.9-rc5
  vfio: Create shared routine for scanning info capabilities
  vfio: Find DMA available capability
  s390x/pci: Add routine to get the vfio dma available count
  s390x/pci: Honor DMA limits set by vfio

 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  56 ++++++++-
 hw/s390x/s390-pci-bus.h                            |   9 ++
 hw/s390x/s390-pci-inst.c                           |  34 ++++-
 hw/s390x/s390-pci-inst.h                           |   3 +
 hw/s390x/s390-pci-vfio.c                           |  54 ++++++++
 hw/s390x/s390-pci-vfio.h                           |  17 +++
 hw/vfio/common.c                                   |  52 ++++++--
 include/hw/vfio/vfio-common.h                      |   2 +
 include/standard-headers/drm/drm_fourcc.h          | 140 +++++++++++++++++++++
 include/standard-headers/linux/ethtool.h           |  87 +++++++++++++
 include/standard-headers/linux/input-event-codes.h |   3 +-
 include/standard-headers/linux/vhost_types.h       |  11 ++
 include/standard-headers/linux/virtio_9p.h         |   4 +-
 include/standard-headers/linux/virtio_blk.h        |  26 ++--
 include/standard-headers/linux/virtio_config.h     |   8 +-
 include/standard-headers/linux/virtio_console.h    |   8 +-
 include/standard-headers/linux/virtio_net.h        |   6 +-
 include/standard-headers/linux/virtio_scsi.h       |  20 +--
 linux-headers/asm-generic/unistd.h                 |   6 +-
 linux-headers/asm-mips/unistd_n32.h                |   1 +
 linux-headers/asm-mips/unistd_n64.h                |   1 +
 linux-headers/asm-mips/unistd_o32.h                |   1 +
 linux-headers/asm-powerpc/kvm.h                    |   5 +
 linux-headers/asm-powerpc/unistd_32.h              |   1 +
 linux-headers/asm-powerpc/unistd_64.h              |   1 +
 linux-headers/asm-s390/kvm.h                       |   7 +-
 linux-headers/asm-s390/unistd_32.h                 |   1 +
 linux-headers/asm-s390/unistd_64.h                 |   1 +
 linux-headers/asm-x86/unistd_32.h                  |   1 +
 linux-headers/asm-x86/unistd_64.h                  |   1 +
 linux-headers/asm-x86/unistd_x32.h                 |   1 +
 linux-headers/linux/kvm.h                          |  10 +-
 linux-headers/linux/vfio.h                         |  18 ++-
 linux-headers/linux/vhost.h                        |   2 +
 35 files changed, 537 insertions(+), 62 deletions(-)
 create mode 100644 hw/s390x/s390-pci-vfio.c
 create mode 100644 hw/s390x/s390-pci-vfio.h
```
#### [PATCH v3 0/5] Qemu SEV-ES guest support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Tue Sep 15 21:29:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11777849
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A45CF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 21:31:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 763CC21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 21:31:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="25iEgd2C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727709AbgIOVa4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 17:30:56 -0400
Received: from mail-bn8nam08on2083.outbound.protection.outlook.com
 ([40.107.100.83]:29249
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728085AbgIOVaS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 17:30:18 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mMcg3cicsTTc2uYuQ0tSZbz3Ws5QSKxKCmb/dTX80RxxEtE+Io/+F2TI6VJ1vzVPX4FN43bIrcSYqBoIg4SEres5USOdnDj/kOtctCP6RzOeMIWykDd0RQSn1C5/PcIg8ggsGkOYbaFpFN7tgfK2cQRDZr9sz7sX1XX1rALOCILsHnxSy9wU5dyeVYqPeVbICBxj8WtQxTfeY58KE+ejbcne1H9YXae5sRupyBeyh690E86u5c9IIwO0M4ls3y+39b5ENK4BCB78tkY0lkGXdcenL2rD6AxSiNXMQzSMrd6e0P2/JP2a209+yW/1yFDCWGCEXVRnvLE2tVbnacODLw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=USmlxAFyX1tiqZMcVVg3IFWaDI1hfi9wypUsGGyCTxI=;
 b=J6vaWRQLOIqyVKhavcwXAXw4z/K22MlzDIiaFx3IXsWoaT+P2fZ1i0K/JMqCT8wDzHC20rgXHy1SbyQd5CMbvGqofbyufH/eKGmOSkXLZz3lAV04rHfvJmRY6u9mimnRhN22xZOin8FIOsP++ZWQ1coKtHLPayC8UKoleFk2je0T+/vIlKIHxrp3jVBHOrNkTMFMkgxGudrBx7jwdvnpOoN0yMn9qdeB/lGmCfdl98eT7UfDhRW0KhY6I7olc41O5S1p7glNH1ozHHJ3YYPlT/RuLcgoh80jqmm1x9TIQUu7LF1v+pQFu/Uk6wKAQwgBoa2vLjhcjSc5JHk02JzKuQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=USmlxAFyX1tiqZMcVVg3IFWaDI1hfi9wypUsGGyCTxI=;
 b=25iEgd2C+2alBq62A2wG3ZgtS7YQFoVESILULoZsgMM0pJK1Grf7X+ku+eBjeCD8b3BH5ANXu5ABn7/uuZCjChx7A4NXoM4lC6fxHgNgGfbUxmYbx4njMp/UT65I/xhMOf7p+fSC4NeajkYSkMz3yC4vBOsIoKw//X3APxq5cz8=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR12MB1607.namprd12.prod.outlook.com (2603:10b6:910:b::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3370.16; Tue, 15 Sep
 2020 21:29:59 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::989b:b1b2:464c:443]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::989b:b1b2:464c:443%10]) with mapi id 15.20.3370.019; Tue, 15 Sep 2020
 21:29:59 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v3 0/5] Qemu SEV-ES guest support
Date: Tue, 15 Sep 2020 16:29:39 -0500
Message-Id: <cover.1600205384.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: DM5PR07CA0132.namprd07.prod.outlook.com
 (2603:10b6:3:13e::22) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR07CA0132.namprd07.prod.outlook.com (2603:10b6:3:13e::22) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3391.11 via Frontend
 Transport; Tue, 15 Sep 2020 21:29:58 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 3c21e423-2610-4feb-97ae-08d859be7f9a
X-MS-TrafficTypeDiagnostic: CY4PR12MB1607:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB1607D34A05FB4F5EA65CB3B6EC200@CY4PR12MB1607.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 r7gnvV24pj58z87c0MBJ8cLfB+rQy8hNR01Qr3a8fqI+9+Qv7hFy37VwRdxAmBd1PVhchfOVV+dFJN2dSom9mCg0gexdzER58JclvkZbJ/T+XTKqchT5wul1wvLkAw1ZzlSw8SoRME65r4FXClIShWvUGH6Jv/Nn6Z9u5Zi9HhBNQGhWCFlwIsfOUlHDYgsn5478WnDBE31KLPI6mIBejvydlquwFJV4fYhWHNFCEdMuq7d24GBqAF9hfqwmFYSJFXR7zRbLuTQDH7LCOEVv2lD9ICZN0I6oVB/LZxgj+LNk5ZLZSxWHB/R6eaMDQRiSx73uxnu1haIOSBn806tmcbwgH+cNRO3Fl9zl2Bk7TD/5JmjMH+CPGGv3JbKSWP5aU4dcYv+WQNWPMB5+9/b2HA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(346002)(136003)(39860400002)(376002)(5660300002)(956004)(478600001)(6666004)(966005)(86362001)(52116002)(2616005)(2906002)(7696005)(36756003)(66476007)(8936002)(66556008)(66946007)(316002)(54906003)(7416002)(26005)(6486002)(4326008)(8676002)(16526019)(83380400001)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Sek8TuZ/oxG+Pox3CziOsvqdD9sZ/HOvqx6vUQkXo9dtrPL09E8BmFnZsrWLqIrajqnhbTqDvR3yfqdu1NQv+pEzBzbUKAp6OyylxGO6XqaQHBZujvcERNQCKjVLvyb2Do76v33SOXQl7+UmjHjSY8y+qw6M3/MyIA84iI1ysaOf9CTreJ3vQl0jf3p0AG9kEe+BV7WfZ+hHjykC6HrmbABXsYalgvuFS0WCBt576eRst+S91LSAAWbPUEHZRZYgzOyE1WDdpxIPL54t+EKKhivJmJazdZWwQdTCtF4uEXyu0i/MSmKbZZCdiMFlE3lglHNrJq1naG8Gd77mooRgUg5eTe13Hhv5izdPWy+Xv4PewDxskDQHdpyehKK1zNMC/TrKwDh9++zZYmNo8eR3vDZPOvKTFCzOspN0CjHfrJHWGO4aPVKrxAQG+lEsab9mhB1LDayPz3S9cincUMU+XKG3irF1Qy5AveOk5lKLyp2Rmnf5eZoDKlsaqoGGzFYqEKhM8YSO3C242IWCCP26hq8TXAz6s6KmR++n7DhZs6UeStilzE/AI2FWNiUy3tqVzEdEbZY1b51iQ1DGUHPLYVAbkmVs+54B3RlDBx6bEtJ287Xa6NZOa5D4ug8FCqjCl+Pm6Hxwmy02z4kdQpR2Tg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3c21e423-2610-4feb-97ae-08d859be7f9a
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Sep 2020 21:29:59.5339
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 yead7xBxnOcJokr3lTJ3NRg2ta4LpW12xGMOw5y9+BFJqL6dsXKQtjOWZhTWWGloe08W7baFvXTLt3qxHYZSUg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1607
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for launching an SEV-ES guest.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

The main areas of the Qemu code that are updated to support SEV-ES are
around the SEV guest launch process and AP booting in order to support
booting multiple vCPUs.

There are no new command line switches required. Instead, the desire for
SEV-ES is presented using the SEV policy object. Bit 2 of the SEV policy
object indicates that SEV-ES is required.

The SEV launch process is updated in two ways. The first is that a the
KVM_SEV_ES_INIT ioctl is used to initialize the guest instead of the
standard KVM_SEV_INIT ioctl. The second is that before the SEV launch
measurement is calculated, the LAUNCH_UPDATE_VMSA SEV API is invoked for
each vCPU that Qemu has created. Once the LAUNCH_UPDATE_VMSA API has been
invoked, no direct changes to the guest register state can be made.

AP booting poses some interesting challenges. The INIT-SIPI-SIPI sequence
is typically used to boot the APs. However, the hypervisor is not allowed
to update the guest registers. For the APs, the reset vector must be known
in advance. An OVMF method to provide a known reset vector address exists
by providing an SEV information block, identified by UUID, near the end of
the firmware [3]. OVMF will program the jump to the actual reset vector in
this area of memory. Since the memory location is known in advance, an AP
can be created with the known reset vector address as its starting CS:IP.
The GHCB document [2] talks about how SMP booting under SEV-ES is
performed. SEV-ES also requires the use of the in-kernel irqchip support
in order to minimize the changes required to Qemu to support AP booting.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
[3] 30937f2f98c4 ("OvmfPkg: Use the SEV-ES work area for the SEV-ES AP reset vector")
    https://github.com/tianocore/edk2/commit/30937f2f98c42496f2f143fe8374ae7f7e684847
---

These patches are based on commit:
d0ed6a69d3 ("Update version for v5.1.0 release")

(I tried basing on the latest Qemu commit, but I was having build issues
that level)

A version of the tree can be found at:
https://github.com/AMDESE/qemu/tree/sev-es-v11

Changes since v2:
- Add in-kernel irqchip requirement for SEV-ES guests

Changes since v1:
- Fixed checkpatch.pl errors/warnings

Tom Lendacky (5):
  sev/i386: Add initial support for SEV-ES
  sev/i386: Require in-kernel irqchip support for SEV-ES guests
  sev/i386: Allow AP booting under SEV-ES
  sev/i386: Don't allow a system reset under an SEV-ES guest
  sev/i386: Enable an SEV-ES guest based on SEV policy

 accel/kvm/kvm-all.c       |  73 ++++++++++++++++++++++++++
 accel/stubs/kvm-stub.c    |   5 ++
 hw/i386/pc_sysfw.c        |  10 +++-
 include/sysemu/cpus.h     |   2 +
 include/sysemu/hw_accel.h |   5 ++
 include/sysemu/kvm.h      |  18 +++++++
 include/sysemu/sev.h      |   3 ++
 softmmu/cpus.c            |   5 ++
 softmmu/vl.c              |   5 +-
 target/i386/cpu.c         |   1 +
 target/i386/kvm.c         |   2 +
 target/i386/sev-stub.c    |   5 ++
 target/i386/sev.c         | 105 +++++++++++++++++++++++++++++++++++++-
 target/i386/sev_i386.h    |   1 +
 14 files changed, 236 insertions(+), 4 deletions(-)
```
