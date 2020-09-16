#### [PATCH v2 1/2] KVM: arm64: Assume write fault on S1PTW permission fault on instruction fetch
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11776075
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DA996CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 10:49:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1098220B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 10:49:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1600166986;
	bh=wkKxKhlybGBntyOg1hln2NHkcNdtK4PSZdl0LvY4Ww0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=l0NqwF8i49+raZr0TywpK4YsLIebzxQL1VWOgYTuUp2YbMSNJcLyRV1AfA9w1Z8WC
	 qYuFAztOpWP0hWWZM8FXtTt4/IvpjJBtDKzza6CG+MbAs5RRqmYVuygbMMhjB5iDuE
	 O3o2rKaVLO1CzdhsJGIhrPzHgdGuEPxC5zxDUdk4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726380AbgIOKtJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 06:49:09 -0400
Received: from mail.kernel.org ([198.145.29.99]:46124 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726372AbgIOKmm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 06:42:42 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5855B2078D;
        Tue, 15 Sep 2020 10:42:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1600166561;
        bh=wkKxKhlybGBntyOg1hln2NHkcNdtK4PSZdl0LvY4Ww0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=cXqnxHVC/lNwsdNTXzNrQrUQ41aUYV5aTt9D/LVneBanDT+iQJ8Tjb8oidrX/Pq2a
         wV6fP6Pk9ZiH1lEghDHBiaetqE2r4ynVODp0mupOC7dhNCELdLeCvuwZUthDP3e7v3
         7YjKkhAzX/x++0pukuKXN80BlhOhPLYLgN6MitZ0=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1kI8Q3-00ByDU-SC; Tue, 15 Sep 2020 11:42:40 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: kernel-team@android.com, Will Deacon <will@kernel.org>,
        stable@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: arm64: Assume write fault on S1PTW permission
 fault on instruction fetch
Date: Tue, 15 Sep 2020 11:42:17 +0100
Message-Id: <20200915104218.1284701-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200915104218.1284701-1-maz@kernel.org>
References: <20200915104218.1284701-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com,
 will@kernel.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM currently assumes that an instruction abort can never be a write.
This is in general true, except when the abort is triggered by
a S1PTW on instruction fetch that tries to update the S1 page tables
(to set AF, for example).

This can happen if the page tables have been paged out and brought
back in without seeing a direct write to them (they are thus marked
read only), and the fault handling code will make the PT executable(!)
instead of writable. The guest gets stuck forever.

In these conditions, the permission fault must be considered as
a write so that the Stage-1 update can take place. This is essentially
the I-side equivalent of the problem fixed by 60e21a0ef54c ("arm64: KVM:
Take S1 walks into account when determining S2 write faults").

Update kvm_is_write_fault() to return true on IABT+S1PTW, and introduce
kvm_vcpu_trap_is_exec_fault() that only return true when no faulting
on a S1 fault. Additionally, kvm_vcpu_dabt_iss1tw() is renamed to
kvm_vcpu_abt_iss1tw(), as the above makes it plain that it isn't
specific to data abort.

Cc: stable@vger.kernel.org
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_emulate.h    | 12 ++++++++++--
 arch/arm64/kvm/hyp/include/hyp/switch.h |  2 +-
 arch/arm64/kvm/mmu.c                    |  4 ++--
 3 files changed, 13 insertions(+), 5 deletions(-)

```
#### [PATCH kvmtool] virtio: add support for vsock
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11775945
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A448F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 09:44:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D12221D1B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 09:44:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726423AbgIOJoM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 05:44:12 -0400
Received: from out30-54.freemail.mail.aliyun.com ([115.124.30.54]:46823 "EHLO
        out30-54.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726157AbgIOJoG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 05:44:06 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R151e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04395;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=4;SR=0;TI=SMTPD_---0U90piu2_1600163042;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0U90piu2_1600163042)
          by smtp.aliyun-inc.com(127.0.0.1);
          Tue, 15 Sep 2020 17:44:02 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: Will Deacon <will@kernel.org>,
        "G . Campana" <gcampana+kvm@quarkslab.com>, kvm@vger.kernel.org
Cc: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Subject: [PATCH kvmtool] virtio: add support for vsock
Date: Tue, 15 Sep 2020 17:44:02 +0800
Message-Id: <20200915094402.107988-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.19.1.3.ge56e4f7
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "run" command accepts a new option (--vsock <cid>) which specify the
guest CID. For instance:

  $ lkvm run --kernel ./bzImage --disk test --vsock 3

One can easily test by: https://github.com/stefanha/nc-vsock.

In the guest:

  # modprobe vsock
  # nc-vsock -l 1234

In the host:

  # modprobe vhost_vsock
  # nc-vsock 3 1234

This patch comes from the early submission of G. Campana. On this basis,
I fixed the compilation errors and runtime crashes. Thanks for the work
done by G. Campana.
https://patchwork.kernel.org/patch/9542313/

Signed-off-by: G. Campana <gcampana+kvm@quarkslab.com>
Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 Makefile                     |   1 +
 builtin-run.c                |   2 +
 include/kvm/kvm-config.h     |   1 +
 include/kvm/virtio-pci-dev.h |   2 +
 include/kvm/virtio-vsock.h   |   9 +
 include/linux/vhost.h        |  53 ++++++
 include/linux/virtio_ids.h   |   1 +
 include/linux/virtio_vsock.h |  94 ++++++++++
 virtio/vsock.c               | 340 +++++++++++++++++++++++++++++++++++
 9 files changed, 503 insertions(+)
 create mode 100644 include/kvm/virtio-vsock.h
 create mode 100644 include/linux/virtio_vsock.h
 create mode 100644 virtio/vsock.c

```
#### [PATCH v2 1/2] KVM: VMX: Move IRQ invocation to assembly subroutine
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11777623
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 542F4746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:26:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3EDB72078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:26:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727871AbgIOT0U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 15:26:20 -0400
Received: from mga18.intel.com ([134.134.136.126]:37595 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727960AbgIOTPN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 15:15:13 -0400
IronPort-SDR: 
 jQUEd+vJEx4SA4+KQiX//vem2dBP/Bnkm0zMzEC3/wdRruho8EjTin/22NYy+Vm2yDmv3PpNXT
 +ky70b3YSe8g==
X-IronPort-AV: E=McAfee;i="6000,8403,9745"; a="147082731"
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="147082731"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Sep 2020 12:15:08 -0700
IronPort-SDR: 
 x9f57plf7ZJ+OJ3I5thAEF0Uu3RcSCDq9uNYiOAqtWE5H3fbDBbIf2u41HmvS6Wo0n+msAQ7Ao
 0I4NCQqJ+c4A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,430,1592895600";
   d="scan'208";a="507694446"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga005.fm.intel.com with ESMTP; 15 Sep 2020 12:15:07 -0700
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
Subject: [PATCH v2 1/2] KVM: VMX: Move IRQ invocation to assembly subroutine
Date: Tue, 15 Sep 2020 12:15:04 -0700
Message-Id: <20200915191505.10355-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200915191505.10355-1-sean.j.christopherson@intel.com>
References: <20200915191505.10355-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the asm blob that invokes the appropriate IRQ handler after VM-Exit
into a proper subroutine.  Unconditionally create a stack frame in the
subroutine so that, as objtool sees things, the function has standard
stack behavior.  The dynamic stack adjustment makes using unwind hints
problematic.

Suggested-by: Josh Poimboeuf <jpoimboe@redhat.com>
Cc: Uros Bizjak <ubizjak@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Josh Poimboeuf <jpoimboe@redhat.com>
Acked-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmenter.S | 34 ++++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c     | 33 +++------------------------------
 2 files changed, 37 insertions(+), 30 deletions(-)

```
#### [PATCH RFC 1/2] KVM: x86: allocate vcpu->arch.cpuid_entries dynamically
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11778153
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2101618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 22:49:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A338820B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 22:49:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="il0gFn7F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727639AbgIOWtp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 18:49:45 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:29612 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727459AbgIOPnt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 11:43:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600184610;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=XXFy/q65vk1jisWRQyxPpPLWskYCS/ybqHocfTlHIhM=;
        b=il0gFn7FVD2it0uil+cFzYmlpK6yDm4WO5HNfYBnopbt2gikMTNTYSFF8kxlw+im9NEPFJ
        m3+G+yLl3kMJO8+CclUsP3PQM5z1nqsWB564RpHqiCHSzbfKYdI7dq4SQRq7OkagYamAv0
        pG+bSIUyp7ebEGOjoyZ5age3Lfyw3ms=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-585-6yHQjql2OuyEZgQS79cm9w-1; Tue, 15 Sep 2020 11:43:25 -0400
X-MC-Unique: 6yHQjql2OuyEZgQS79cm9w-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6856C1963FE6;
        Tue, 15 Sep 2020 15:43:13 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 23E9C1992D;
        Tue, 15 Sep 2020 15:43:10 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Wei Huang <whuang2@amd.com>, linux-kernel@vger.kernel.org
Subject: [PATCH RFC 1/2] KVM: x86: allocate vcpu->arch.cpuid_entries
 dynamically
Date: Tue, 15 Sep 2020 17:43:05 +0200
Message-Id: <20200915154306.724953-2-vkuznets@redhat.com>
In-Reply-To: <20200915154306.724953-1-vkuznets@redhat.com>
References: <20200915154306.724953-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current limit for guest CPUID leaves (KVM_MAX_CPUID_ENTRIES, 80)
is reported to be insufficient but before we bump it let's switch to
allocating vcpu->arch.cpuid_entries dynamically. Currenly,
'struct kvm_cpuid_entry2' is 40 bytes so vcpu->arch.cpuid_entries is
3200 bytes which accounts for 1/4 of the whole 'struct kvm_vcpu_arch'
but having it pre-allocated (for all vCPUs which we also pre-allocate)
gives us no benefits.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/cpuid.c            | 55 ++++++++++++++++++++++++---------
 arch/x86/kvm/x86.c              |  1 +
 3 files changed, 42 insertions(+), 16 deletions(-)

```
#### [PATCH v3 1/5] sev/i386: Add initial support for SEV-ES
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11777883
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3678B6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 21:45:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D4EC2078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 21:45:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="0exTJDH5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728071AbgIOVo5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 17:44:57 -0400
Received: from mail-dm6nam10on2059.outbound.protection.outlook.com
 ([40.107.93.59]:21344
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727999AbgIOVas (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Sep 2020 17:30:48 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=aNjYlSLEaXVAWq7mHbyJR92EYSjvUnLlW2/isflj+vwY8Mg5q3bxOwrf8nxSnF5BhfD3zK3y+671ZBsyzEdP28aRSByF2TP5SwBX/6m4i5uVXfWWRVlfKw7jEBoBL3IbGuyVixrlI5AGSJpx+qHRgl1y1kZIHl4OTII9Mh87D2WL6IdRzf1cdTuLgpfotErpjuTBpiOcdE+lONycrNB571a1cet56l7L0l3oI/oBJoh2FiKqp8R1w6SOPP8Ce8PaxEJbJFlyqF6UpDMaL5ZXxERF/FuBmljDq7axfXjqcMBIq70/GEVvdvWBBkIkx/hd38BwFr11ZYIHLvJ7GvQchg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=bfwY3oY3hj8nfswS/j2xKnUzgMi7NPWmwJbieQaGJiMcze+lTPgCKqjIMowIR6Ib1aCrBpZ11E7PDPEMsJ7EyRIeFg25r4LQBRszH/oQIUK6b1y4Galh9HVQzhwUK5pWwgTnmxF7T3WlT7RW/jjj1QI8GM3GY8ICsGZyUVPnv4tCqCIKqq7lanq8D1d5Wg6nI31wVjAhccjzvDmVuWw098n4iJjQ//7cSPwmM+5NUN6w+TORJeCxNVfDmFqjo6PdGF/nHqefPeSH/cCKE9OfCGHuYbVGh2Crxboh/OjYLIo0bQQnGmEn8uT4VTXOs9GFP50HSdw503qMIpJ9CRR/fg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=0exTJDH5sq9zBSGZtUC2wPy38PRzvE4az0GJIFUHwASHOsbf89iGW4bYdBmef54a2zCF6MOLfqwlyFW9uPHGYetS1psxUp6mTeIjjEQbr19rHTYePfAoCmy/ZaBBFGzZYYWFAmiG+jhVCfpHSJzOJ8HWlC2k1sOAmmRIjoSHPU0=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR12MB1607.namprd12.prod.outlook.com (2603:10b6:910:b::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3370.16; Tue, 15 Sep
 2020 21:30:08 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::989b:b1b2:464c:443]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::989b:b1b2:464c:443%10]) with mapi id 15.20.3370.019; Tue, 15 Sep 2020
 21:30:08 +0000
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
Subject: [PATCH v3 1/5] sev/i386: Add initial support for SEV-ES
Date: Tue, 15 Sep 2020 16:29:40 -0500
Message-Id: 
 <e2456cc461f329f52aa6eb3fcd0d0ce9451b8fa7.1600205384.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1600205384.git.thomas.lendacky@amd.com>
References: <cover.1600205384.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: DM5PR21CA0022.namprd21.prod.outlook.com
 (2603:10b6:3:ac::32) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR21CA0022.namprd21.prod.outlook.com (2603:10b6:3:ac::32) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3412.0 via Frontend
 Transport; Tue, 15 Sep 2020 21:30:07 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 7be9caef-abf7-4671-d990-08d859be84b6
X-MS-TrafficTypeDiagnostic: CY4PR12MB1607:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB16078003DCFFEDF511B73192EC200@CY4PR12MB1607.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 42NvKcwMhV+hkZ6a2o5icitj4a+1HG/0kwvwHUR5mq3zfejADqEhR/WTrUuvRQubbEbmEdMxGADIn1G/cY+fl7VPtH+np3xsl8zvlBYKOe8Pxk8tiADOA0BCOMZWhRf7KkvI3xc3vCn3OnIMc94lnCuH1/u1jUR2s9wToHMpy7Xmdw3ajG18vT0wKFfEiaKgAWPf1OnpbwpIbKkKDC6Mp0MJkij+G8H9sDVF00rja/OIPwzI5pfJ8HRIgJfv4Bn2M/dJ/+ib/VH+WJ+VLofALNQ8Q6YXcLtX/oWt5xxQ4DZQnWgKdkiwqLimF2ikzP/F/wFSoVfLLOru8X9y8G7KLKYKsXaGfpY5u1wnTiELRrKDXecHRH9KJPWOq3HF9XvX
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(346002)(136003)(39860400002)(376002)(5660300002)(956004)(478600001)(6666004)(86362001)(52116002)(2616005)(2906002)(7696005)(36756003)(66476007)(8936002)(66556008)(66946007)(316002)(54906003)(7416002)(26005)(6486002)(4326008)(8676002)(16526019)(83380400001)(186003)(309714004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 I051YFqFnSwiRy6dax9lhZVvzOPLBskuC1xd9oE2mwmBBsvAA4dp0MGUiIfTsYzRY8/pc8rR3DgrnfmiGocgjVCsHcQ/M1rOYQ1VLywqnktyNQWihODVBxywhFC7PI+9w38mmo5gVsJH2Sn3/PlkZ+fq+aWGlXRFJDVQ9jKBM1iCBW8y3jXj8hzOQSymcSc1QW9ANXtWIivN3IS9hU3CKTFzaCo5In9/j6+kk1i0+KLgEWiUZ54RITxlmoqwpi2pefMhBVrxYR81Rh9Fc3mndayjE4ZFY9vv6Y/RuzYnqiJqu872gBglBlo6O5L4mbguFp2B30zQxKLtAj9u1FXTnBS9Ao+w0l6mJ7i2eAD3uCm782dHuiiR6Ec76SbuYGJ562u+TBGiIe1cAohXxW5RbLO6lqZLvEeFRnBc2q8uAdDyvwBLEOJvDeQ6h71B1BgB15qk/ZNAdv9NYBnRc7ZJK7iVHghaY+Ld9I6BTOiB8Dc6IURZt2oiXFvJVlNNBKn+DQd/hUBmq97BG9F0fzc7rVX5U4tZ6vL+yvxew5fhb74EQrpn2w6rLY32AqEVCvEj+ZeaDsAvaulSBq8CPJrha709wxpitDtki4EyD9jm1iw9C+fProVruraDH/IMu6rqH1lLNrL5iNhFhrBoZnLkPQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7be9caef-abf7-4671-d990-08d859be84b6
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Sep 2020 21:30:08.0318
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 m3FA5ZZ4wdtW26EPYDOsjn4RbhO0jjfzZyMcQaABeu7xWAoBkyqxfreJxS9WXzZ85CW2kfqMHp/h253jxV108Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1607
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
#### [PATCH v3 1/5] linux-headers: update against 5.9-rc5
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11777619
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A067746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:25:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6432520735
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:25:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="PdSDEujn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727716AbgIOTWB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 15:22:01 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44296 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727997AbgIOTPU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 15:15:20 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08FIXik1032819;
        Tue, 15 Sep 2020 15:14:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=9OEVq9GR0dWFU4woffCFVhYENDP3UoRI7DXeNT+evTM=;
 b=PdSDEujn5Qb6x1VQAu0o6CqrHjZEY+U0Cvuo4jINrLZ0sAvK+udMRSDQ4IfiSiYl4yrw
 SdNcR7ak4gca3VLHVFfZJ0cTWsTIBXYoox4pDbHedBVZ+BLytyI6vj4gBrgBH/5e/IVr
 WsNuTOW49kXfxkkvYGp6SvvktZUWXD76u6K7NppSVl6RVvA8ofGzo1Vc6ygLNuSVVtQo
 v7Vn1pgSc669pCbDHHrbOeK5ty6PayqxNvlbPq0v6UkdRbqJER6feLBHqnlP6XiOxrrz
 enUTJkcjAgYcdo00qEYM1NOSAgKr9wF2N9IZ7GI1IFYj0hch6eZYO/RxnYRCojewM6fY Mw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33k2q8sh79-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:14:56 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08FIYmM7036442;
        Tue, 15 Sep 2020 15:14:55 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33k2q8sh71-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:14:55 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08FJ7lWd002857;
        Tue, 15 Sep 2020 19:14:54 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma04wdc.us.ibm.com with ESMTP id 33jgrgxv2u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 19:14:54 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 08FJErlC54722984
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Sep 2020 19:14:54 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DC55E112065;
        Tue, 15 Sep 2020 19:14:53 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 81E55112064;
        Tue, 15 Sep 2020 19:14:51 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.85.51])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 15 Sep 2020 19:14:51 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, thuth@redhat.com, pasic@linux.ibm.com,
        borntraeger@de.ibm.com, mst@redhat.com, pbonzini@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v3 1/5] linux-headers: update against 5.9-rc5
Date: Tue, 15 Sep 2020 15:14:39 -0400
Message-Id: <1600197283-25274-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1600197283-25274-1-git-send-email-mjrosato@linux.ibm.com>
References: <1600197283-25274-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-15_12:2020-09-15,2020-09-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 impostorscore=0
 malwarescore=0 suspectscore=0 phishscore=0 clxscore=1015 spamscore=0
 bulkscore=0 adultscore=0 mlxlogscore=999 priorityscore=1501
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009150147
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PLACEHOLDER as the kernel patch driving the need for this ("vfio iommu: Add
dma available capability") is not merged yet.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
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
 26 files changed, 328 insertions(+), 43 deletions(-)

```
#### [PATCH v3] vfio iommu: Add dma available capability
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11777595
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2C3192C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:10:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C599120756
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 19:10:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="eaCGTvAI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727941AbgIOTKa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Sep 2020 15:10:30 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:61928 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727976AbgIOTFg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Sep 2020 15:05:36 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08FIXi1v032846;
        Tue, 15 Sep 2020 15:05:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=sjt/S6np6D4/53bKdF+p/e8fPp0Y4PQPdKkW3dJL2fs=;
 b=eaCGTvAIdJpMsxQ+XhIMCwXW1jv2Sd71kMNcypHrjbp2gvUi7L9KolDJikOUsr+Uv4th
 6dF2RqqMNtrEsvCb4i60wQpheGTUujSp2LDYFm0W5K8o0I2iLaU7D44Am0Qx7zHvszgg
 niwfDqZDaEGhgjuwcpT7xrqsHLW/FLG8xPhDkUzxLVKumBBS/mqluUVbIUX0yeyStXJg
 1tyOJvaeeCbORKwJaXWmYluONZNoRy01QhKsK9mlzzkUEc13f2tZCTTQvC3q93qi3LSs
 p5fImLLwrdaFB8RlYF03jFnSqSquRjfguXkjntnf2rlnXzapbuItIKT1LGcXByVvIx4M Yw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33k2q8s9en-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:05:25 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08FIXwlG033569;
        Tue, 15 Sep 2020 15:05:25 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33k2q8s9e9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 15:05:25 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08FIuZcp022125;
        Tue, 15 Sep 2020 19:05:24 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma03dal.us.ibm.com with ESMTP id 33gny9g1y4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 15 Sep 2020 19:05:24 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08FJ5NfO63898042
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Sep 2020 19:05:23 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3074F7805C;
        Tue, 15 Sep 2020 19:05:23 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5A0027805F;
        Tue, 15 Sep 2020 19:05:22 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.85.51])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue, 15 Sep 2020 19:05:22 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3] vfio iommu: Add dma available capability
Date: Tue, 15 Sep 2020 15:05:18 -0400
Message-Id: <1600196718-23238-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1600196718-23238-1-git-send-email-mjrosato@linux.ibm.com>
References: <1600196718-23238-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-15_12:2020-09-15,2020-09-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 impostorscore=0
 malwarescore=0 suspectscore=0 phishscore=0 clxscore=1015 spamscore=0
 bulkscore=0 adultscore=0 mlxlogscore=739 priorityscore=1501
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009150147
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 492855939bdb ("vfio/type1: Limit DMA mappings per container")
added the ability to limit the number of memory backed DMA mappings.
However on s390x, when lazy mapping is in use, we use a very large
number of concurrent mappings.  Let's provide the current allowable
number of DMA mappings to userspace via the IOMMU info chain so that
userspace can take appropriate mitigation.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 drivers/vfio/vfio_iommu_type1.c | 17 +++++++++++++++++
 include/uapi/linux/vfio.h       | 15 +++++++++++++++
 2 files changed, 32 insertions(+)

```
#### [PATCH] vfio: add a singleton check for vfio_group_pin_pages
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11775169
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C20759D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:42:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C570212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:42:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726087AbgIOAl4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 20:41:56 -0400
Received: from mga06.intel.com ([134.134.136.31]:7242 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726057AbgIOAls (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 20:41:48 -0400
IronPort-SDR: 
 IiWUILalpR7mKwqG4MjOQsNs/3M1AdZJEBoAGjLF8oF7770rIhRt92ohp+KEht3UsB9wW6H6Og
 lRAoDvC/QAIQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9744"; a="220737094"
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="220737094"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Sep 2020 17:41:47 -0700
IronPort-SDR: 
 UHdHRSDT6ynMHG/BOqPGJGlYkT48sgCUB/JPojSv8IWSFV7CfCxbwPvaIXCwiJMFSa8tjwsgxh
 JEgDLY7zLqiA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="335468034"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 14 Sep 2020 17:41:45 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH] vfio: add a singleton check for vfio_group_pin_pages
Date: Tue, 15 Sep 2020 08:30:42 +0800
Message-Id: <20200915003042.14273-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pin_pages() and vfio_group_pin_pages() are used purely to mark dirty
pages to devices with IOMMU backend as they already have all VM pages
pinned at VM startup.
when there're multiple devices in the vfio group, the dirty pages
marked through pin_pages interface by one device is not useful as the
other devices may access and dirty any VM pages.

So added a check such that only singleton IOMMU groups can pin pages
in vfio_group_pin_pages. for mdevs, there's always only one dev in a
vfio group.
This is a fix to the commit below that added a singleton IOMMU group
check in vfio_pin_pages.

Fixes: 95fc87b44104 (vfio: Selective dirty page tracking if IOMMU backed
device pins pages)

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] vfio: fix a missed vfio group put in vfio_pin_pages
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11775173
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 833E1112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:49:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6863F212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:49:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726057AbgIOAto (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 20:49:44 -0400
Received: from mga01.intel.com ([192.55.52.88]:10400 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726024AbgIOAtn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 20:49:43 -0400
IronPort-SDR: 
 FgxZiRVI0Oq4RloF2GSFUVi7G7oUjbjf9k03uRElGor7x8v/FTOa1Zl2Sqyeq11laBx1gmMV13
 2rZS4O+PpOwQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9744"; a="177247509"
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="177247509"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Sep 2020 17:49:43 -0700
IronPort-SDR: 
 /fkne7Pfn08NMotXs+5OLleNTbxIsHOEIAl1ai4D+qVgvt1HhV17ywU2d7E8QUJHp//QZb+KHr
 Rb5UjavQTjTw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="335469854"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 14 Sep 2020 17:49:41 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH] vfio: fix a missed vfio group put in vfio_pin_pages
Date: Tue, 15 Sep 2020 08:28:35 +0800
Message-Id: <20200915002835.14213-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when error occurs, need to put vfio group after a successful get.

Fixes: 95fc87b44104 (vfio: Selective dirty page tracking if IOMMU backed
device pins pages)

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/vfio.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] vfio/type1: fix dirty bitmap calculation in vfio_dma_rw
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11775171
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6217659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:44:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CF67212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:44:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726068AbgIOAoC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 20:44:02 -0400
Received: from mga04.intel.com ([192.55.52.120]:45263 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726019AbgIOAn6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 20:43:58 -0400
IronPort-SDR: 
 1Up+GFju8envoAmLu3FoFsfvzgqvXumtNijq0y3iGibMAnvIiZKf7N2iVQFVg5QQz8Wvz6OZbh
 sIn+ZS/eW4bQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9744"; a="156573620"
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="156573620"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Sep 2020 17:43:55 -0700
IronPort-SDR: 
 Sqrps9y2ydj609JLDQUfGitBQvgcxizdUXcJzRbozyNTCBtT1qTGIA+afnTIcv8tjcyHAojjK+
 OQXg9UpjAHtA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,427,1592895600";
   d="scan'208";a="335468562"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 14 Sep 2020 17:43:53 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH] vfio/type1: fix dirty bitmap calculation in vfio_dma_rw
Date: Tue, 15 Sep 2020 08:32:51 +0800
Message-Id: <20200915003251.14343-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

the count of dirtied pages is not only determined by count of copied
pages, but also by the start offset.

e.g. if offset = PAGE_SIZE - 1, and *copied=2, the dirty pages count is
2, instead of 0.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty
pages tracking")

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost_vdpa: Fix duplicate included kernel.h
##### From: Tian Tao <tiantao6@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tian Tao <tiantao6@hisilicon.com>
X-Patchwork-Id: 11775175
Return-Path: <SRS0=V1hm=CY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 992C3618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:54:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EECC20897
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Sep 2020 00:54:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726066AbgIOAyT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Sep 2020 20:54:19 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:57754 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726024AbgIOAyT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Sep 2020 20:54:19 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id EE18CED4246D061D6D95;
        Tue, 15 Sep 2020 08:54:14 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Tue, 15 Sep 2020 08:54:04 +0800
From: Tian Tao <tiantao6@hisilicon.com>
To: <mst@redhat.com>, <jasowang@redhat.com>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>
CC: <linuxarm@huawei.com>
Subject: [PATCH] vhost_vdpa: Fix duplicate included kernel.h
Date: Tue, 15 Sep 2020 08:51:42 +0800
Message-ID: <1600131102-24672-1-git-send-email-tiantao6@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

linux/kernel.h is included more than once, Remove the one that isn't
necessary.

Signed-off-by: Tian Tao <tiantao6@hisilicon.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 1 -
 1 file changed, 1 deletion(-)

```
