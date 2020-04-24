#### [PATCH v10 01/11] perf/x86: Fix variable type for LBR registers
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11505253
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74495912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 08:17:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61FF521655
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 08:17:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726522AbgDWIRk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 04:17:40 -0400
Received: from mga18.intel.com ([134.134.136.126]:57581 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725863AbgDWIRj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Apr 2020 04:17:39 -0400
IronPort-SDR: 
 WjMp5FdaUMxQVfGMIiPqo7F9MzI2Ltpfw5DetEmJmLmHysw/MRXCPVfQwAbINjm6POyFaLECIU
 wr6XkkM/tjcg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Apr 2020 01:17:39 -0700
IronPort-SDR: 
 FXEmfdYw4hyTRvdP0+eXfiwXur70+zIL0Sr8sRUBswK26SVCS21NQKqeMV7QXKq1o6u5UwVc+Q
 5owA0xeJ/ReA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,306,1583222400";
   d="scan'208";a="255910036"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga003.jf.intel.com with ESMTP; 23 Apr 2020 01:17:36 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, wei.w.wang@intel.com,
        ak@linux.intel.com, Peter Zijlstra <peterz@infradead.org>
Subject: [PATCH v10 01/11] perf/x86: Fix variable type for LBR registers
Date: Thu, 23 Apr 2020 16:14:02 +0800
Message-Id: <20200423081412.164863-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200423081412.164863-1-like.xu@linux.intel.com>
References: <20200423081412.164863-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

The msr variable type can be 'unsigned int', which uses less memory than
the longer 'unsigned long'. Fix 'struct x86_pmu' for that. The lbr_nr won't
be a negative number, so make it 'unsigned int' as well.

Cc: Peter Zijlstra (Intel) <peterz@infradead.org>
Suggested-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: Store vmcs.EXIT_QUALIFICATION as an unsigned long, not u32
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11504755
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 681441392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 00:11:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A6B72077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 00:11:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726071AbgDWAL2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 20:11:28 -0400
Received: from mga03.intel.com ([134.134.136.65]:6055 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725854AbgDWAL2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 20:11:28 -0400
IronPort-SDR: 
 gy3VN51eNd25JeobTjYQZ769UXTcwbCyT40YQfq1i6JSL6bvUHxyzPmuiBxCbtr4mLDl8zUkWU
 TzaPwYdFE6Bw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2020 17:11:28 -0700
IronPort-SDR: 
 aQf708tzHhWl8yKzEOn23sd8LSUIxgWzWyapz5K++6BLe7JwWgMWyWraZtXBo1PN8ML/OOkKLE
 7wTom2pwMHuQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,305,1583222400";
   d="scan'208";a="334793040"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 22 Apr 2020 17:11:28 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Store vmcs.EXIT_QUALIFICATION as an unsigned long,
 not u32
Date: Wed, 22 Apr 2020 17:11:27 -0700
Message-Id: <20200423001127.13490-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use an unsigned long for 'exit_qual' in nested_vmx_reflect_vmexit(), the
EXIT_QUALIFICATION field is naturally sized, not a 32-bit field.

The bug is most easily observed by doing VMXON (or any VMX instruction)
in L2 with a negative displacement, in which case dropping the upper
bits on nested VM-Exit results in L1 calculating the wrong virtual
address for the memory operand, e.g. "vmxon -0x8(%rbp)" yields:

  Unhandled cpu exception 14 #PF at ip 0000000000400553
  rbp=0000000000537000 cr2=0000000100536ff8

Fixes: fbdd50250396d ("KVM: nVMX: Move VM-Fail check out of nested_vmx_exit_reflected()")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Sadly (for me), I can't blame a mishandled merge on this one.  Even more
embarassing is that this is actually the second instance where I botched
the size for exit_qual, you'd think I'd have double-checked everything
after the first one...

 arch/x86/kvm/vmx/nested.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/5] KVM: LAPIC: Introduce interrupt delivery fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11505315
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D0D5B112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:02:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B20702084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:02:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="kJGDKGA9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726796AbgDWJCB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 05:02:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49216 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725854AbgDWJCA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Apr 2020 05:02:00 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B3C27C03C1AF;
        Thu, 23 Apr 2020 02:02:00 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id t4so2094883plq.12;
        Thu, 23 Apr 2020 02:02:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=ESURTorcFnpn5TvjjZllV4zzCIxjIoPMUCqGGCximXw=;
        b=kJGDKGA9Tu+m8vwFrYBIORtoWH+KfW08OJdXIr9vnUypoQpeoQ8zh/NXBjgpVUsr7o
         sgAai14b5R5ctAO1ImEHpkKmgUc7O7Lvchan2szxDWe2jh58+l8hL2k4yUcN1p1kCWK6
         EmFQuidd9/4QSox+waZl6OKMFeas539fQnOt1dTx1x/Qw1aM8WOMOL314AtlclBQVTF8
         RHWBByOSzwaj0VXHEUvi/luyDkvQ5XpLwDKCQXhYy+WagQXPPR6FfkllT+ZWWsIPp/s+
         m0Jh8D0CZAnbklPxSc7w4MmOKlamkoMj1IaI6yTGfIHWZCm7b1GvGNCsrLK3CFI2076R
         pusg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=ESURTorcFnpn5TvjjZllV4zzCIxjIoPMUCqGGCximXw=;
        b=CdBbf/ilAgqJquttKFk2Cpqc8R/pgE6qCiiDlFjSs0Ss/cJL14qCWRvLEEYcRqu6eV
         rQhik/DWVfDTGKJ/cDXlj7TDumtzZW2RX7FATBKBuaBuEurBfRWRK+xlbxqx4qHFk29l
         Q/GS1Vi8SYYGLTamMbfWDMlBfXPtcvUX8SrAe1TgZUSyC0ghLS30rg1IZtkPCnIk9fTK
         0Dw4Yoe1Zllg0pemW7MNfM8otGbXHByo3KQ5EKkr8BDsxq8vFd3DED3iH+dQCXTdIitM
         X+EeutYmbbJ92fFN0UcQKz0iM5J2psU37t9Y1K9iLFrYW93jyVE7rVaGgjhmCmWKcxu8
         DEMA==
X-Gm-Message-State: AGi0PuZCU84wNKeXJfWFfk/I20yYj/6ftuS3/TP/sC3oE68fk7ADG6x8
        blUOzFEeOvCvFzincbcEg3U6cVK/
X-Google-Smtp-Source: 
 APiQypKfBaqbDg+Yz2gbo5NHqSf75C7jaaiMFf3mS5+J+ZuxM8zZTyGtNmKVLqgJPvDaJbhwfqoU2Q==
X-Received: by 2002:a17:902:ed13:: with SMTP id
 b19mr2908841pld.254.1587632520035;
        Thu, 23 Apr 2020 02:02:00 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 w28sm1574204pgc.26.2020.04.23.02.01.57
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 23 Apr 2020 02:01:59 -0700 (PDT)
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
Subject: [PATCH v2 1/5] KVM: LAPIC: Introduce interrupt delivery fastpath
Date: Thu, 23 Apr 2020 17:01:43 +0800
Message-Id: <1587632507-18997-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1587632507-18997-1-git-send-email-wanpengli@tencent.com>
References: <1587632507-18997-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce interrupt delivery fastpath, I observe kvm_x86_ops.deliver_posted_interrupt() 
has more latency then vmx_sync_pir_to_irr in my case, since it needs to wait 
vmentry, after that it can handle external interrupt, ack the notification 
vector, read posted-interrupt desciptor etc, it is slower than evaluate and 
delivery during vmentry method. For non-APICv, inject directly since we will 
not go though inject_pending_event().

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/lapic.c            | 32 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/svm/avic.c         |  5 +++++
 arch/x86/kvm/svm/svm.c          |  1 +
 arch/x86/kvm/svm/svm.h          |  1 +
 arch/x86/kvm/vmx/vmx.c          | 23 +++++++++++++++++------
 6 files changed, 57 insertions(+), 6 deletions(-)

```
#### [PATCH 01/13] KVM: nVMX: Preserve exception priority irrespective of exiting behavior
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11504889
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2CF3159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 02:27:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D54D4208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 02:27:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726545AbgDWCZ4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 22:25:56 -0400
Received: from mga05.intel.com ([192.55.52.43]:43420 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726046AbgDWCZz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 22:25:55 -0400
IronPort-SDR: 
 PBtXlPbCYjHb5PWE2+UKniXZQP0fwMd80Rn55KecCtOjSdBBCa8ZXnNNgYGdavfMRW0ZhWKMLX
 bka5aVbcKS9Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2020 19:25:54 -0700
IronPort-SDR: 
 d4SYGUjyFo0ArnHT9KsSbY4ttXZC48ZmHxFFgQYMg8axD1qCJoGlYChMUaQ/JOlTOtM4X7m7rr
 kg2WlQY4qTCg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,305,1583222400";
   d="scan'208";a="259273932"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 22 Apr 2020 19:25:54 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH 01/13] KVM: nVMX: Preserve exception priority irrespective of
 exiting behavior
Date: Wed, 22 Apr 2020 19:25:38 -0700
Message-Id: <20200423022550.15113-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200423022550.15113-1-sean.j.christopherson@intel.com>
References: <20200423022550.15113-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Short circuit vmx_check_nested_events() if an exception is pending and
needs to be injected into L2, priority between coincident events is not
dependent on exiting behavior.  This fixes a bug where a single-step #DB
that is not intercepted by L1 is incorrectly dropped due to servicing a
VMX Preemption Timer VM-Exit.

Injected exceptions also need to be blocked if nested VM-Enter is
pending or an exception was already injected, otherwise injecting the
exception could overwrite an existing event injection from L1.
Technically, this scenario should be impossible, i.e. KVM shouldn't
inject its own exception during nested VM-Enter.  This will be addressed
in a future patch.

Note, event priority between SMI, NMI and INTR is incorrect for L2, e.g.
SMI should take priority over VM-Exit on NMI/INTR, and NMI that is
injected into L2 should take priority over VM-Exit INTR.  This will also
be addressed in a future patch.

Fixes: b6b8a1451fc4 ("KVM: nVMX: Rework interception of IRQs and NMIs")
Reported-by: Jim Mattson <jmattson@google.com>
Cc: Oliver Upton <oupton@google.com>
Cc: Peter Shier <pshier@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH v2 01/10] s390x: smp: Test all CRs on initial reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11505341
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E058213B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:10:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D3FCD2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:10:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726508AbgDWJK2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 05:10:28 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:42862 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725884AbgDWJK1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Apr 2020 05:10:27 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03N93Vo6025785
        for <kvm@vger.kernel.org>; Thu, 23 Apr 2020 05:10:26 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30k3xu7b91-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 23 Apr 2020 05:10:25 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 23 Apr 2020 10:09:37 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 23 Apr 2020 10:09:34 +0100
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03N9AKQe60424394
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Apr 2020 09:10:20 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6B94B4C046;
        Thu, 23 Apr 2020 09:10:20 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BC0A14C040;
        Thu, 23 Apr 2020 09:10:19 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Apr 2020 09:10:19 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com
Subject: [PATCH v2 01/10] s390x: smp: Test all CRs on initial reset
Date: Thu, 23 Apr 2020 05:10:04 -0400
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200423091013.11587-1-frankja@linux.ibm.com>
References: <20200423091013.11587-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20042309-4275-0000-0000-000003C51E00
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20042309-4276-0000-0000-000038DAA822
Message-Id: <20200423091013.11587-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-23_06:2020-04-22,2020-04-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 mlxscore=0
 impostorscore=0 adultscore=0 priorityscore=1501 bulkscore=0 clxscore=1015
 malwarescore=0 mlxlogscore=898 lowpriorityscore=0 suspectscore=1
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004230066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All CRs are set to 0 and CRs 0 and 14 are set to pre-defined values,
so we also need to test 1-13 and 15 for 0.

And while we're at it, let's also set some values to cr 1, 7 and 13, so
we can actually be sure that they will be zeroed.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 s390x/smp.c | 16 +++++++++++++++-
 1 file changed, 15 insertions(+), 1 deletion(-)

```
