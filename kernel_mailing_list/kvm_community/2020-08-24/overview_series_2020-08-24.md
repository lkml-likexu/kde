#### [PATCH] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11732617
Return-Path: <SRS0=RwC+=CC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3424314F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 09:18:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A88C20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 09:18:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="AnqeJkTd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728928AbgHXJSK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Aug 2020 05:18:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41222 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727790AbgHXJSC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Aug 2020 05:18:02 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D4318C061573;
        Mon, 24 Aug 2020 02:18:02 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id x25so4501391pff.4;
        Mon, 24 Aug 2020 02:18:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rMbx9PJ3DCBK5KCbc3Tq72JFtt/jZJ3a0mHSBLV/+uA=;
        b=AnqeJkTdPwAVQxkz4xsNAtHq1yAHzh39+X/LXN7tfivOxU91cTAYJkDJJEjAHalmTR
         JZlcvmT0jYOFVX6LkmIh6yFcYtztGmbUR6o6yzTt2BxiUbPXknRCADhyi23jcFSPn4uw
         M71l9lbogTqNOdr1bUTHbUybuPAn+BIlK1zzCStEEaaRqb7iMr0gqZvvHFJO39zu68h7
         3y9YUX1d1+rSQqgmOEVJ5qdyprOkA23HJUvmKtbuFOwVLNgYGmxJLg6a+sS7/fE7N5Eq
         mksxmBPLx7hej4N+hF4XWBKcKl1DxvAZHPO+gnF2uzOwJWB6Lgc0gxCpW6QyWAHddreL
         MUQQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rMbx9PJ3DCBK5KCbc3Tq72JFtt/jZJ3a0mHSBLV/+uA=;
        b=OHIupXePxRwVVrsdOC5YHTAS+bM7EKbiHE1B37fZI+imbKYAVEj3WKQohJeUDMPaPF
         OicXOl4AqJwYKuMS7pOWf3LlNVBnIGtt2MVEIEcIML82dDTmaMfWDeFJm/Z2jcdMouW5
         KBVJOUVu2u/sHDRAvOLJpcnNt1tAHKD27RF+tThMYR/y6g9EBydAfM9excyMkKP3lCQW
         IqozGWVg40NtKNhf09s+ga41o5cyyWGSRZDp+fbXFm6kpVbNYWRWMrmqXzBfxFCuhPDB
         VT3PZyhLZvKZiZBag62tZqAY2GnsU6aVRGM0Xc5+3zZE0gIE4F4QcTBDID9hPTm3EE6S
         e86Q==
X-Gm-Message-State: AOAM532VmLXjOzxpDUbNSIegrEXvH6Z5tTKv9Kep1OiRYyuC5GI2hX0U
        +R2yvjtVSBhA6UQRwWChB7xQgY2MCVQnpg==
X-Google-Smtp-Source: 
 ABdhPJwH15eOuacRsnIJtiFTkzCC9mVtco/DG7gF2PFLarQs3vCzzD3G4wVhpqSTXi5lRLlEgpy9XQ==
X-Received: by 2002:a63:4b63:: with SMTP id k35mr2965491pgl.235.1598260682241;
        Mon, 24 Aug 2020 02:18:02 -0700 (PDT)
Received: from localhost ([121.0.29.56])
        by smtp.gmail.com with ESMTPSA id
 62sm10342504pfx.47.2020.08.24.02.18.01
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 24 Aug 2020 02:18:01 -0700 (PDT)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org
Cc: Lai Jiangshan <laijs@linux.alibaba.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org
Subject: [PATCH] kvm x86/mmu: use KVM_REQ_MMU_SYNC to sync when needed
Date: Mon, 24 Aug 2020 18:18:25 +0800
Message-Id: <20200824101825.4106-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

8c8560b83390("KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for MMU specific flushes)
changed it without giving any reason in the changelog.

In theory, the syncing is needed, and need to be fixed by reverting
this part of change.

Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: LAPIC: Narrow down the kick target vCPU
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11732029
Return-Path: <SRS0=RwC+=CC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D649C14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 01:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7CBB20774
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 01:03:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XWfhn3tb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727108AbgHXBDf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Aug 2020 21:03:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49142 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726765AbgHXBDd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Aug 2020 21:03:33 -0400
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 42C42C061573;
        Sun, 23 Aug 2020 18:03:32 -0700 (PDT)
Received: by mail-pj1-x1042.google.com with SMTP id kr4so3363836pjb.2;
        Sun, 23 Aug 2020 18:03:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=mHdg7ZAGw/S9rL1jLVYu4KEglhQVBa3kE+9qg01kLDU=;
        b=XWfhn3tb/CT6dh4iItrfklOil+TX8ZdWg2R1Mze0W7ts71wK/IveEYyUgjoCK6Lu7c
         ENdIeHaH2bBs+qqFLVWcp/8ghnM00i0uiXy8LH4mI1aezmmrv7l3WcmoL9bQ3G8DK+kb
         3sSscsg8Y9omBA4dR5y+1r70JNX/HPaWI+uHoEjBhiYRg6pXR3AzPU9XgNAYblEgB6pb
         TZOUXlBlZD41CIEDGVB9zoZoROZFQ1Lg8I0zBe8dalmsAqpQ44borkSpOsgGVmmRbVzI
         AGp9cVX3RCpifZqblRpUkm9VaPYvJ043/BLB00xq4Uiu/krE7QzdskGQvJvyZpKv9Hsn
         /O6Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=mHdg7ZAGw/S9rL1jLVYu4KEglhQVBa3kE+9qg01kLDU=;
        b=V/zohNHmaArYbNB+yat7SbOHDChCeXI2U4h6cE4+EZUnmzq27ahv08bHHa5Umdaj+o
         nTCo952d0LlzfcRMOKngjqD9z/etMWA3Iip4Pd3C6/ltzrxmj2kFLoOfmAyJyMr5le31
         331mG7CGOs3H2PgkBNJpislDN3buVHKV+jV+kQ6tT3Q4cSzC+bF/UG1K2DHkgTKgxTTP
         oCYVM9HQ+5P7AmPFHPx32jQ1XW8CYfL+w/ChyROUM67FWFJePpIhGY5vl/d+Trol/dHU
         y70FRqW8kFhe1cqKRBqnsIuDWCO4BxOowwqbvgVy89kyoabY7889E0tLOwtMAAoUJKGP
         gL5A==
X-Gm-Message-State: AOAM532im/gaj8KV3838mSYf4nkNheXkG805frmYamRKHw5tcU0zHgiC
        9ZAWgHwzvJjleSMeR/SbhahvcWAsXys=
X-Google-Smtp-Source: 
 ABdhPJzKxBkrzyOs7RXrO1VIvMRJJzcj3jMGwFNlbqEuthPA+17ztNMBGXVB6n/zkyuHfWY96ZeCPQ==
X-Received: by 2002:a17:902:121:: with SMTP id
 30mr2179592plb.205.1598231012076;
        Sun, 23 Aug 2020 18:03:32 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 ml18sm7699823pjb.43.2020.08.23.18.03.29
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 23 Aug 2020 18:03:31 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: LAPIC: Narrow down the kick target vCPU
Date: Mon, 24 Aug 2020 09:03:16 +0800
Message-Id: <1598230996-17097-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The kick after setting KVM_REQ_PENDING_TIMER is used to handle the timer 
fires on a different pCPU which vCPU is running on, this kick is expensive 
since memory barrier, rcu, preemption disable/enable operations. We don't 
need this kick when injecting already-expired timer, we also should call 
out the VMX preemption timer case, which also passes from_timer_fn=false 
but doesn't need a kick because kvm_lapic_expired_hv_timer() is called 
from the target vCPU.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v1 -> v2:
 * update patch subject and changelog
 * open code kvm_set_pending_timer()

 arch/x86/kvm/lapic.c | 4 +++-
 arch/x86/kvm/x86.c   | 6 ------
 arch/x86/kvm/x86.h   | 1 -
 3 files changed, 3 insertions(+), 8 deletions(-)

```
#### [PATCH v6 01/76] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11732631
Return-Path: <SRS0=RwC+=CC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F8C614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 09:19:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 206D8206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Aug 2020 09:19:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729172AbgHXJTo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Aug 2020 05:19:44 -0400
Received: from 8bytes.org ([81.169.241.247]:36882 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730267AbgHXIzv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Aug 2020 04:55:51 -0400
Received: from cap.home.8bytes.org (p4ff2bb8d.dip0.t-ipconnect.de
 [79.242.187.141])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id A722585;
        Mon, 24 Aug 2020 10:55:46 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v6 01/76] KVM: SVM: nested: Don't allocate VMCB structures on
 stack
Date: Mon, 24 Aug 2020 10:53:56 +0200
Message-Id: <20200824085511.7553-2-joro@8bytes.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200824085511.7553-1-joro@8bytes.org>
References: <20200824085511.7553-1-joro@8bytes.org>
MIME-Version: 1.0
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
