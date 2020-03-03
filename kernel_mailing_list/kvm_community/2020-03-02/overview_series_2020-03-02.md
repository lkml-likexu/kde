#### [PATCH] KVM: SVM: Fix svm the vmexit error_code of WRMSRTo: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11415415
Return-Path: <SRS0=eKZH=4T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34150138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 12:19:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 135DC214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 12:19:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="KXBL9v6w"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727851AbgCBMTl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 07:19:41 -0500
Received: from mail-ed1-f66.google.com ([209.85.208.66]:44062 "EHLO
        mail-ed1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727267AbgCBMTl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Mar 2020 07:19:41 -0500
Received: by mail-ed1-f66.google.com with SMTP id g19so13005657eds.11;
        Mon, 02 Mar 2020 04:19:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=G/f6M+HBAL4DqhW0c1p6bk4sytP2vYJy/i55zifn5Jk=;
        b=KXBL9v6wyp6mGHBavSEyUHPC7wdx5NE9+19vaHLaQPb6Ln6uPjQLYM6gkPhEIy7LbZ
         zjR/je8Rualwm5StcN/6KtHwZAygVAPkHHufletcymi5MBwT/JtvVTlBQWkvNxgSNWL2
         btjgci44eHkrXqZiKqqZfO3ukli+j6gc/3T8FBnUiWRVo+WqVppV/tJQt2sxxYp5C8oO
         3jbk8nBHvrTVAcYJUqq9YuKyNbzeBUpcgEnXMkj6sZGJDxshQ7fHBufzvj2RV5QUQezE
         YHZKOkuTpDhTfQjSOToHoFC6hMFj4FSPWJr3ByOOsOVQ2EN6obPxD0dSknI1n4UP2vZ7
         dF8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=G/f6M+HBAL4DqhW0c1p6bk4sytP2vYJy/i55zifn5Jk=;
        b=UbMQ4oTzgR/gYkh++TPlHcpQnMnwV17CcgKRWhsJzehuYpZNlTYmDCWF7ru3I7KIZY
         njxb54aVV5NUaQo+O/dzGOwI0co68EUDsrKlqbiig6BqlMFBnULCeEwcZySXsHZdWI53
         rJbEt1kJCzN9rq/kA+IsO/DiWNQHFs8LuCNFtD+EtcE9ZU+I5bIsDcKfYqzaSq7dsb00
         JQCzVLBZsSCEfE5u/old56Hf3alvEImB0mYnIpK3Dm0drAgT491Oh7RZTmDG6LWxZfo8
         oX22uSGWo48HdqiVdCv+6iitKYTH62iigvEmZbSnDTqXPY0gBbKhElMgpBG/pVVqbuED
         hsMw==
X-Gm-Message-State: ANhLgQ1jAVYEDBUrzGkKxJE2+BT7/iv5Lb9CwhJreZDEwOj9mUicl+Os
        xThhA8oAPLsorpwBZnirz7DzF9woevK2sJyZs18+
X-Google-Smtp-Source: 
 ADFU+vvc/UCNpbkJV2EIc9o+6JskdV54r70wFEAdITkyCL/3CMdTefLpyOzqHlscsZu6AjkA+qVd42CsAvWgIimb5x4=
X-Received: by 2002:a50:9f68:: with SMTP id b95mr770815edf.96.1583151579669;
 Mon, 02 Mar 2020 04:19:39 -0800 (PST)
MIME-Version: 1.0
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Date: Mon, 2 Mar 2020 20:19:28 +0800
Message-ID: 
 <CAB5KdOZwZUvgmHX5C53SBU0WttEF4wBFpgqiGahD2OkojQJZ-Q@mail.gmail.com>
Subject: [PATCH] KVM: SVM: Fix svm the vmexit error_code of WRMSR
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        kvm@vger.kernel.org, x86@kernel.org
Cc: hpa@zytor.com, bp@alien8.de, "mingo@redhat.com" <mingo@redhat.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "joro@8bytes.org" <joro@8bytes.org>, jmattson@google.com,
        wanpengli@tencent.com, "vkuznets@redhat.com" <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From 1f755f75dfd73ad7cabb0e0f43e9993dd9f69120 Mon Sep 17 00:00:00 2001
From: Haiwei Li <lihaiwei@tencent.com>
Date: Mon, 2 Mar 2020 19:19:59 +0800
Subject: [PATCH] KVM: SVM: Fix svm the vmexit error_code of WRMSR

In svm, exit_code of write_msr is not EXIT_REASON_MSR_WRITE which
belongs to vmx.

According to amd manual, SVM_EXIT_MSR(7ch) is the exit_code of VMEXIT_MSR
due to RDMSR or WRMSR access to protected MSR. Additionally, the processor
indicates in the VMCB's EXITINFO1 whether a RDMSR(EXITINFO1=0) or
WRMSR(EXITINFO1=1) was intercepted.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
  arch/x86/kvm/svm.c | 3 ++-
  1 file changed, 2 insertions(+), 1 deletion(-)

  }

--
1.8.3.1

```
#### [PATCH 1/6] KVM: x86: Fix tracing of CPUID.function when function is out-of-range
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11416235
Return-Path: <SRS0=eKZH=4T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADC5E924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 19:58:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9581722B48
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 19:58:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726773AbgCBT5i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 14:57:38 -0500
Received: from mga05.intel.com ([192.55.52.43]:30422 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726661AbgCBT5i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Mar 2020 14:57:38 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Mar 2020 11:57:37 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,508,1574150400";
   d="scan'208";a="438404973"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 02 Mar 2020 11:57:37 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Jan Kiszka <jan.kiszka@siemens.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 1/6] KVM: x86: Fix tracing of CPUID.function when function is
 out-of-range
Date: Mon,  2 Mar 2020 11:57:31 -0800
Message-Id: <20200302195736.24777-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200302195736.24777-1-sean.j.christopherson@intel.com>
References: <20200302195736.24777-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework kvm_cpuid() to query entry->function when adjusting the output
values so that the original function (in the aptly named "function") is
preserved for tracing.  This fixes a bug where trace_kvm_cpuid() will
trace the max function for a range instead of the requested function if
the requested function is out-of-range and an entry for the max function
exists.

Fixes: 43561123ab37 ("kvm: x86: Improve emulation of CPUID leaves 0BH and 1FH")
Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: X86: Fix dereference null cpufreq policy
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11414845
Return-Path: <SRS0=eKZH=4T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 680E1924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 07:18:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 45E9B24699
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 07:18:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="d794cEm4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726313AbgCBHSg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 02:18:36 -0500
Received: from mail-pf1-f194.google.com ([209.85.210.194]:45404 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726204AbgCBHSf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Mar 2020 02:18:35 -0500
Received: by mail-pf1-f194.google.com with SMTP id 2so5111780pfg.12;
        Sun, 01 Mar 2020 23:18:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=SGYHPYDByh3jgM9qVULEcWknYrO2Uv9Ry5lUP1fq0cU=;
        b=d794cEm4/jGpeACslEH4kzP+y3+j3IKtTRsaga+yf8sTnlUAOHBn9tuqwJ0yTx7dYD
         Vs5dCBO3yx1zEVc5/S/paU18egxiByiViTHUPoYsgMntp9MzgkDYYhpeke8BwVAUzn0S
         mYwv/3Umhk0keqQOdcZNCw6dr2xV4gj3fcytzBnAgN5xdfZFUMSrWJlD0cqJn5JKqk0c
         wiZrpC9JrH8n83UN/39qy5xXjxooSWLv7ccsoyFQZoS5ajgtks7vD7Rnt9M4ZoJ02q3T
         Uha1nYWlfu+/3rQzkUrK4LjW5Yi2jWtSMYEmF0Pc3CdiE1SVp2qGy75z2ub0IwNdf7WM
         hJ7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=SGYHPYDByh3jgM9qVULEcWknYrO2Uv9Ry5lUP1fq0cU=;
        b=mssg4U1Yxc+oVIpkVigBfNHDcps/e0VIAECCo1Pe2m1ZEoUfkfrjChvklC9HwNVQjO
         hrVvcrI+TItLBLw3yhcXzZXFjhv2Q25mpagOQbEkblQv+UftYUkIUwucpOvhIPqEYJCG
         ZjLfGgCmJ7HgZBqIsT9GSyCJJc2+CRez3tMQBlaB4CRV4sSI+0Vsst9EAFfS1qAE4RPW
         Ytb9EXDyPK13iPdi9l/1X8MwEwPgk39KHTJ7A55Xle4pHgQ8xssz02RfzCzQ3G8eOG+8
         VLJS2oNq0wX282XmQZmFyBnPicmbZcQLKZN/x60lERz1BxIURaQd1MPtWA2p9UE2RikU
         tQCg==
X-Gm-Message-State: APjAAAVK3aN/9s7gEj51oJmjKSb9SUvKrklhnmcEkiUuNSdyiUnKn+mO
        3h6iLISPKOUsx6rgBRAbXFNP221pNS9t7w==
X-Google-Smtp-Source: 
 APXvYqxUxPCh2zTtls/G8B2nA/ioRKUNFEaXw0JBRt/6l+WtrYbNC0mZhQKV8wWHP7GixIC12DR/8g==
X-Received: by 2002:a63:2c50:: with SMTP id
 s77mr17537810pgs.182.1583133514798;
        Sun, 01 Mar 2020 23:18:34 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.54])
        by smtp.googlemail.com with ESMTPSA id
 z127sm19257989pgb.64.2020.03.01.23.18.10
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Sun, 01 Mar 2020 23:18:33 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Naresh Kamboju <naresh.kamboju@linaro.org>
Subject: [PATCH] KVM: X86: Fix dereference null cpufreq policy
Date: Mon,  2 Mar 2020 15:15:36 +0800
Message-Id: <1583133336-7832-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Naresh Kamboju reported:

   Linux version 5.6.0-rc4 (oe-user@oe-host) (gcc version
  (GCC)) #1 SMP Sun Mar 1 22:59:08 UTC 2020
   kvm: no hardware support
   BUG: kernel NULL pointer dereference, address: 000000000000028c
   #PF: supervisor read access in kernel mode
   #PF: error_code(0x0000) - not-present page
   PGD 0 P4D 0
   Oops: 0000 [#1] SMP NOPTI
   CPU: 0 PID: 1 Comm: swapper/0 Not tainted 5.6.0-rc4 #1
   Hardware name: QEMU Standard PC (i440FX + PIIX, 1996),
  04/01/2014
   RIP: 0010:kobject_put+0x12/0x1c0
   Call Trace:
    cpufreq_cpu_put+0x15/0x20
    kvm_arch_init+0x1f6/0x2b0
    kvm_init+0x31/0x290
    ? svm_check_processor_compat+0xd/0xd
    ? svm_check_processor_compat+0xd/0xd
    svm_init+0x21/0x23
    do_one_initcall+0x61/0x2f0
    ? rdinit_setup+0x30/0x30
    ? rcu_read_lock_sched_held+0x4f/0x80
    kernel_init_freeable+0x219/0x279
    ? rest_init+0x250/0x250
    kernel_init+0xe/0x110
    ret_from_fork+0x27/0x50
   Modules linked in:
   CR2: 000000000000028c
   ---[ end trace 239abf40c55c409b ]---
   RIP: 0010:kobject_put+0x12/0x1c0

cpufreq policy which is get by cpufreq_cpu_get() can be NULL if it is failure,
this patch takes care of it.

Fixes: aaec7c03de (KVM: x86: avoid useless copy of cpufreq policy)
Reported-by: Naresh Kamboju <naresh.kamboju@linaro.org>
Cc: Naresh Kamboju <naresh.kamboju@linaro.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Tested-by: Naresh Kamboju <naresh.kamboju@linaro.org>
---
 arch/x86/kvm/x86.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] vfio: platform: Switch to platform_get_irq_optional()
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11416343
Return-Path: <SRS0=eKZH=4T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2DDE924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 20:37:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D11222465D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 20:37:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="S0v6yfLq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726791AbgCBUhc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 15:37:32 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23498 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726778AbgCBUhc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Mar 2020 15:37:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583181451;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zqvrLEQk5BMgju+RSyn/5B7EOYMlf2EShnIdivH2s10=;
        b=S0v6yfLq492eJgoGqghjFJDuFhWVEqZHP1Cfw83ioab3FDqMtt0v48jWRXcQMhlb9QXcW3
        M0NlY6Cu+IBIieFQWUDFgyV9mGxWGcHsMR5amqKERAG8zj9Piz0fX10ApYNBkOoTBzKVsP
        PKxfM2CP0O9WfDXxtEihwGoC5de1dnQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-342-bC9Ty_ouO8GLgdEtXWVwHg-1; Mon, 02 Mar 2020 15:37:27 -0500
X-MC-Unique: bC9Ty_ouO8GLgdEtXWVwHg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6328D13E5;
        Mon,  2 Mar 2020 20:37:26 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-59.ams2.redhat.com [10.36.116.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B5045DD73;
        Mon,  2 Mar 2020 20:37:19 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        alex.williamson@redhat.com
Cc: andre.przywara@arm.com, stable@vger.kernel.org, cohuck@redhat.com
Subject: [PATCH] vfio: platform: Switch to platform_get_irq_optional()
Date: Mon,  2 Mar 2020 21:37:15 +0100
Message-Id: <20200302203715.13889-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 7723f4c5ecdb ("driver core: platform: Add an error
message to platform_get_irq*()"), platform_get_irq() calls dev_err()
on an error. As we enumerate all interrupts until platform_get_irq()
fails, we now systematically get a message such as:
"vfio-platform fff51000.ethernet: IRQ index 3 not found" which is
a false positive.

Let's use platform_get_irq_optional() instead.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Cc: stable@vger.kernel.org # v5.3+
---
 drivers/vfio/platform/vfio_platform.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v1 01/11] ACPI: NUMA: export pxm_to_node
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11415593
Return-Path: <SRS0=eKZH=4T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4A852924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 13:50:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D66A20870
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Mar 2020 13:50:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L5+vmAIE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726953AbgCBNum (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 08:50:42 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:32850 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726935AbgCBNul (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Mar 2020 08:50:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583157040;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=x+esorcsOTdydQ/iR1D9mTLbAkiYHJj6EfvHsmJOWIA=;
        b=L5+vmAIEHNkjZ+6aAWO+YyN5Lr2pj84qx1YI4VDwZj2sn/vWo3cuIME1vgT9Q0q+gg9DGq
        fjmoh3n8VeR+6mZiB0uTVBDk+E1xaBpQujAyfjT0qFUiIkDsrUiJcgBJKvixlwMk6PacxR
        A1pz4kco54iRM9aobCwxiaCjYW2N5u8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-428-AB3ShGiNO7Kd_SwpwvvNrA-1; Mon, 02 Mar 2020 08:50:38 -0500
X-MC-Unique: AB3ShGiNO7Kd_SwpwvvNrA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 05E7E1005512;
        Mon,  2 Mar 2020 13:50:37 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-116-114.ams2.redhat.com [10.36.116.114])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4D0C6385;
        Mon,  2 Mar 2020 13:50:26 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        Len Brown <lenb@kernel.org>, linux-acpi@vger.kernel.org
Subject: [PATCH v1 01/11] ACPI: NUMA: export pxm_to_node
Date: Mon,  2 Mar 2020 14:49:31 +0100
Message-Id: <20200302134941.315212-2-david@redhat.com>
In-Reply-To: <20200302134941.315212-1-david@redhat.com>
References: <20200302134941.315212-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Will be needed by virtio-mem to identify the node from a pxm.

Acked-by: "Rafael J. Wysocki" <rafael@kernel.org>
Cc: Len Brown <lenb@kernel.org>
Cc: linux-acpi@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
Acked-by: Michal Hocko <mhocko@suse.com> # for the export
---
 drivers/acpi/numa/srat.c | 1 +
 1 file changed, 1 insertion(+)

```
