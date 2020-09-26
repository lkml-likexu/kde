#### 
##### 

```c
```
#### [PATCH v8 1/8] KVM: x86: Return -ENOENT on unimplemented MSRs
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11799923
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55CCF1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:34:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 302292311D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:34:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="qDKTgJ+4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728858AbgIYOeq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 10:34:46 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:40262 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728431AbgIYOeq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 10:34:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1601044486; x=1632580486;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=sfZL+fYteYafFZgtkEQwRvIq4yeNSzLylDLTNYYN9Qs=;
  b=qDKTgJ+4VgmsMDsQquvCtqOphLoTtfwN7KKQnsq2Wg75RdM5afpK1WiU
   Kr3Ceu25llH2aBnwmC5Dl6cRlYYDaH3REmzX8eLdXjhQAwz6ac4sPQuQs
   zbkCNCOvvFs9xgHpc3R2MEnnaYYB8XKQ8eMA3r+NEmNppfSpIw5kUkbyN
   Q=;
X-IronPort-AV: E=Sophos;i="5.77,302,1596499200";
   d="scan'208";a="56284047"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1e-a70de69e.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 25 Sep 2020 14:34:42 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1e-a70de69e.us-east-1.amazon.com (Postfix) with
 ESMTPS id BC09BA17D3;
        Fri, 25 Sep 2020 14:34:37 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 25 Sep 2020 14:34:37 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.221) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 25 Sep 2020 14:34:33 +0000
From: Alexander Graf <graf@amazon.com>
To: kvm list <kvm@vger.kernel.org>
CC: Aaron Lewis <aaronlewis@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        "Dan Carpenter" <dan.carpenter@oracle.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v8 1/8] KVM: x86: Return -ENOENT on unimplemented MSRs
Date: Fri, 25 Sep 2020 16:34:15 +0200
Message-ID: <20200925143422.21718-2-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
In-Reply-To: <20200925143422.21718-1-graf@amazon.com>
References: <20200925143422.21718-1-graf@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.162.221]
X-ClientProxiedBy: EX13D08UWC002.ant.amazon.com (10.43.162.168) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we find an MSR that we can not handle, bubble up that error code as
MSR error return code. Follow up patches will use that to expose the fact
that an MSR is not handled by KVM to user space.

Suggested-by: Aaron Lewis <aaronlewis@google.com>
Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 01/22] kvm: mmu: Separate making SPTEs from set_spteFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11800781
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DB3F16CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 21:23:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD0E621D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 21:23:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Ba8vZCGd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728171AbgIYVXM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 17:23:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33530 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726687AbgIYVXK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 17:23:10 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8EF34C0613CE
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 14:23:10 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id s4so3254407pgk.17
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 14:23:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=Ua7W65/d+eys6TkCdCKyUD20UsOP9zKnnrEciCir1oA=;
        b=Ba8vZCGd6BVlQ3ApTWbLnydXdozDtsK//xKSkkcRq0/GVpiouAAKjNjX7g4wF3RHFh
         cm5pVnHUV72MHz50fFJTsAvMnamSUg8AVwiSAeq5C9/d8lvMDSrVhmJ7zjsVAPZhwAXx
         ok7JapD/Nia/Sd55oRtc2pYiYuZxpbjV6n029qzPHEdB+TcXZ5lhD5rhMQCoVfJ9eDFM
         vyk3DEF8RNUUn4UAgLXIiI54oE+o55wAly4tB+unfNR85PQwZO7r18osoAV7JRb7iY/7
         5HoFJ0A6IIgZGQWwvH97D+IQ9OTkR9YgWOU1suPLe6xQypWfPomWfLrz+3Um8Ful6DUT
         B8MQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Ua7W65/d+eys6TkCdCKyUD20UsOP9zKnnrEciCir1oA=;
        b=F7MuyPkKzQbiKweOlAZWD5aK8odXSj0h9lLuNEiuFeHqNBCOWo/BTAWkt2i+LmYdKT
         6ZIt/qeBWKEggHAqHadBqSk8kkt+05Rf76yrD87OELgs+OyaaJyP7v0X1HAlFpkrhsBJ
         xtB5s1FS57HssJpJFktVI2YjCTzVcsag/rGx6gl/0TdF8LEAAW9tzzJmjER5ocCclk45
         wYv2H76ryhOWEdizXwF7h9WHwYEdPSWxfz4L2qQvaA9EWyqXqZj+lxL98Yo5HBoOR8Xt
         cw2quOsmGWcL8JhMMQ0Bo50yx1fyGwgxCBohDlLVAUMZ82ZAHN4mnBnoFgMppy1xsiwk
         AXCA==
X-Gm-Message-State: AOAM5338+rDQllQiiaHg1FI+D7HnvhPa5NqvGVgH5R+2Z4Z2co6wHHI0
        mUGxBfU4CJb9XCh6qMD86+Z3p2tAapD1
X-Google-Smtp-Source: 
 ABdhPJwH0e7NUIaLBoXcIY3Ow2PsHnPi1TLNqHlvGwApDUSsvb4M85/q+KEi4+WBsGf9fCmKb47sSKwNYysg
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a17:90a:f298:: with SMTP id
 fs24mr475139pjb.4.1601068990014; Fri, 25 Sep 2020 14:23:10 -0700 (PDT)
Date: Fri, 25 Sep 2020 14:22:41 -0700
In-Reply-To: <20200925212302.3979661-1-bgardon@google.com>
Message-Id: <20200925212302.3979661-2-bgardon@google.com>
Mime-Version: 1.0
References: <20200925212302.3979661-1-bgardon@google.com>
X-Mailer: git-send-email 2.28.0.709.gb0816b6eb0-goog
Subject: [PATCH 01/22] kvm: mmu: Separate making SPTEs from set_spte
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cannon Matthews <cannonmatthews@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Separate the functions for generating leaf page table entries from the
function that inserts them into the paging structure. This refactoring
will facilitate changes to the MMU sychronization model to use atomic
compare / exchanges (which are not guaranteed to succeed) instead of a
monolithic MMU lock.

No functional change expected.

Tested by running kvm-unit-tests and KVM selftests on an Intel Haswell
machine. This commit introduced no new failures.

This series can be viewed in Gerrit at:
	https://linux-review.googlesource.com/c/virt/kvm/kvm/+/2538

Signed-off-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 52 +++++++++++++++++++++++++++---------------
 1 file changed, 34 insertions(+), 18 deletions(-)

```
#### [PATCH] KVM: SVM: Mark SEV launch secret pages as dirty.From: Cfir Cohen <cfir@google.com>
##### From: Cfir Cohen <cfir@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cfir Cohen <cfir@google.com>
X-Patchwork-Id: 11798659
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D2436CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 02:00:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 80F1320888
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 02:00:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="GXfea3Qo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726843AbgIYCAi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 22:00:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51348 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726730AbgIYCAi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 22:00:38 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0608FC0613D4
        for <kvm@vger.kernel.org>; Thu, 24 Sep 2020 19:00:38 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id x1so1266406ybi.4
        for <kvm@vger.kernel.org>; Thu, 24 Sep 2020 19:00:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=Y06C3d8gRlVIiH+a/DZUSriRyLlq/Qy1nRNdUsM+sAw=;
        b=GXfea3Qo5SPVCB6zPnPqFml4mMW4ETxCYvtg6DkSi8qUGa1Zwf9u6NLZJsEukeZZLO
         9ozz3hSeWFxj2yzhjImj8k1WGGPrJq+u+ncjP0sWrEb1gSFusuBGk1k/JQFIwfVlxYbb
         nopXxvAEt2X3V6ShgrPyWnxP23jSmaAbt4En49JyFwCYca6Smxa1V37vrwXa8eKDhuE+
         jZeIdWLYYapx1aH+qtubvC3Gzc76YFMhbNMl47t3s43mmYU5K7XD4QERdLROZUwhI/Pv
         3R1nJ/KXxngXUsjI4UpazW297HMCdW3XBTGhx2NjcC+7NRbfPExV1pzqYCDjcjWO1Ws5
         JThA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Y06C3d8gRlVIiH+a/DZUSriRyLlq/Qy1nRNdUsM+sAw=;
        b=I93R/KJ8YSEuuAkPWv1FMnsaQ5IWETdhoXPPR1BVyS+hmvDDv7/hGSRSDvAfs20FGB
         gSO89mn62SZtosLsOQAn/oyq7qh/By8XKwDPDlIi/CQC+52Nve59Fp2FOwFP6ndh/0OW
         FcddXbCT0/QqDCmHjp78yea0QRSglCnaohT08W0+E3S7lpY0QaZgwaW3yCjdu2/PS99Z
         /SBlqo+J/ha32kVQS8a65sfVV/O3XLcJe7TCUAKxgCjkxuSlFD6dmgJRNgMfyNocOTri
         nF95nCKYnRzF/APP+nim331h07ALsJ5VdLJjD4mBWZ2gbSSm0N9gMFazsAA0RsCIZdWW
         VG5Q==
X-Gm-Message-State: AOAM532wadchfz7XIVyCob7TiDePlZQHEpZ03p5GBA6S3+98tF6umx8Y
        1umvjDgkL2s8yNq8+RA4xPHP6O/VIASFymjOgTJM9xYJu7GijzzW21HrkzzI43DiWI1ykHxxMEN
        tLftkX4FR0qQnpfFj1W4BehtG/+WgixrFywrU7omd0W5zTsKsX8mv
X-Google-Smtp-Source: 
 ABdhPJz5rQ1t0pb1JJRyVoLVT/N/+7t6zAsJOr3F9AwPqot8pRccyoYZLojtSZ41PDH3NySyRqTRfjIN
Sender: "cfir via sendgmr" <cfir@cfir.sea.corp.google.com>
X-Received: from cfir.sea.corp.google.com
 ([2620:15c:158:202:a6ae:11ff:fe11:da08])
 (user=cfir job=sendgmr) by 2002:a25:e80d:: with SMTP id
 k13mr2135631ybd.179.1600999237042;
 Thu, 24 Sep 2020 19:00:37 -0700 (PDT)
Date: Thu, 24 Sep 2020 19:00:11 -0700
In-Reply-To: <20200807012303.3769170-1-cfir@google.com>
Message-Id: <20200925020011.1159247-1-cfir@google.com>
Mime-Version: 1.0
References: <20200807012303.3769170-1-cfir@google.com>
X-Mailer: git-send-email 2.28.0.681.g6f77f65b4e-goog
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
        linux-kernel@vger.kernel.org, stable@vger.kernel.org,
        Cfir Cohen <cfir@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The LAUNCH_SECRET command performs encryption of the
launch secret memory contents. Mark pinned pages as
dirty, before unpinning them.
This matches the logic in sev_launch_update_data().

Fixes: 9c5e0afaf157 ("KVM: SVM: Add support for SEV LAUNCH_SECRET command")
Signed-off-by: Cfir Cohen <cfir@google.com>
---
Changelog since v2:
 - Added 'Fixes' tag, updated comments.
Changelog since v1:
 - Updated commit message.

 arch/x86/kvm/svm/sev.c | 26 +++++++++++++++++---------
 1 file changed, 17 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] configure: Add a check for the bash version
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11799941
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78966112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:39:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5488F22B2D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:39:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YfJ9lAO7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729009AbgIYOjE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 10:39:04 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:47014 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728802AbgIYOjE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Sep 2020 10:39:04 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601044743;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=Lt1j6BM1xEtBjnoIfN9ATzwZj+difO86HoNV3rPN9XU=;
        b=YfJ9lAO7+xP9mIX7LYUr1WY9+E8ebuIViPVZmkwY5QfPbAs0hJpmb199uhmV5tr4Yr1yQv
        emSvRp10FlJaNCrnYGShW2K2tq3fEP3ZmlDL/fIq8BFCkVgQgHJWJSrjDpxgoiIx2SxppG
        Vq2yXROmmUYwanMIS7dfSqPLByhC6NQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-299-0dB5dzNsP6CZXW2-u3PkHA-1; Fri, 25 Sep 2020 10:39:01 -0400
X-MC-Unique: 0dB5dzNsP6CZXW2-u3PkHA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 27B231017DE4
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 14:39:00 +0000 (UTC)
Received: from thuth.com (ovpn-112-251.ams2.redhat.com [10.36.112.251])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 661C26198B;
        Fri, 25 Sep 2020 14:38:54 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com
Subject: [kvm-unit-tests PATCH] configure: Add a check for the bash version
Date: Fri, 25 Sep 2020 16:38:52 +0200
Message-Id: <20200925143852.227908-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Our scripts do not work with older versions of the bash, like the
default Bash 3 from macOS (e.g. we use the "|&" operator which has
been introduced in Bash 4.0). Add a check to make sure that we use
at least version 4 to avoid that the users run into problems later.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 configure | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [kvm-unit-tests PATCH] travis.yml: Use TRAVIS_BUILD_DIR to refer to the top directory
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11799293
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 53F3B92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 07:11:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EB5520759
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 07:11:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Ajh01co4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727324AbgIYHLy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 03:11:54 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28408 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726990AbgIYHLx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Sep 2020 03:11:53 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601017913;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=httEJJ6m33HzqvzspuI8t33ctSQx1l0sZsHnr2kz/So=;
        b=Ajh01co4cOfBVOoLCqrkWnfmc2qjbif33+664/jcjX4bGfr49YoJnsj1SiPiyKKZIpfkGS
        E9Qmxgd+LgN0Lneq9Qq6K7/rOOv3+SlqJtiRZx15NrGscIT6VUz/nUOnrrvqya1DzheHzH
        JzQ++Gpyw1CWyJTw4I28iwXARu/Vo6g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-564-zGktOluDMNyhYgkcZDV1WQ-1; Fri, 25 Sep 2020 03:11:50 -0400
X-MC-Unique: zGktOluDMNyhYgkcZDV1WQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1709910060C3
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 07:11:50 +0000 (UTC)
Received: from thuth.com (ovpn-112-251.ams2.redhat.com [10.36.112.251])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C0994061;
        Fri, 25 Sep 2020 07:11:49 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH] travis.yml: Use TRAVIS_BUILD_DIR to refer to
 the top directory
Date: Fri, 25 Sep 2020 09:11:47 +0200
Message-Id: <20200925071147.149406-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Travis already has an environment variable that points to the top of
the checked-out source code, TRAVIS_BUILD_DIR. We can use it to avoid
the guessing of the right location of the configure script.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: cover emulation of reduced MAXPHYADDR
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11800945
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 070D3112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 22:44:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DACA220BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 22:44:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="H0VJOJkj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726744AbgIYWoa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 18:44:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43947 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726636AbgIYWoa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Sep 2020 18:44:30 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601073869;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mOIyCgY/IoGKS+vL+syjQpfoJXSV5VORDkFB2B1OxTk=;
        b=H0VJOJkjbIEb3hrAqKOo3c3meB1nyKm0FV8ZTg8BsK73FvBwaTFybUpReHJydBVIRqwzPK
        WDp28jy8PlXSVzNDYQaiViUE1fBayIV7HdhAF1XzWMhOWEwUzwIoQodMRo5ymJitXn7i+f
        pryV5d3voADDkdcPHYyBklm3RSPCbWs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-401-cRG3j9lePA2oIC6tBNZvBQ-1; Fri, 25 Sep 2020 18:44:27 -0400
X-MC-Unique: cRG3j9lePA2oIC6tBNZvBQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 64E6A1DDFB
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 22:44:26 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 281707367E
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 22:44:26 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: cover emulation of reduced MAXPHYADDR
Date: Fri, 25 Sep 2020 18:44:25 -0400
Message-Id: <20200925224425.2178862-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a variant of x86/access.flat that covers the emulation
of guest-MAXPHYADDR < host-MAXPHYADDR.  Use an old-ish
CPU model because to speed up the test, as Ivy Bridge did
not have SMEP and PKU.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/unittests.cfg | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: vmx: Add test for SIPI signal processing
##### From: yadong.qi@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Qi, Yadong" <yadong.qi@intel.com>
X-Patchwork-Id: 11799305
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98B8692C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 07:49:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EE30208B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 07:49:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727201AbgIYHtn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 03:49:43 -0400
Received: from mga01.intel.com ([192.55.52.88]:1027 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726990AbgIYHtn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 03:49:43 -0400
IronPort-SDR: 
 VWVG6dYUdkDj8A+M49SoVMTc5cfJtHOnPspx5c0fupaNo9ifpbsbGDCKn0MfAQuglp7i9s9JrP
 LzSx60AEq8Tg==
X-IronPort-AV: E=McAfee;i="6000,8403,9754"; a="179549932"
X-IronPort-AV: E=Sophos;i="5.77,301,1596524400";
   d="scan'208";a="179549932"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Sep 2020 00:36:40 -0700
IronPort-SDR: 
 v0JNZ2kPgKyEGuUFxrezrdcDS9weHkNrQ48xyt9gP3NehIRlSTyFodjRVAzdsFsTJn2UwtxN74
 R5T+EBlMxKDw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,301,1596524400";
   d="scan'208";a="306187525"
Received: from yadong-antec.sh.intel.com ([10.239.158.61])
  by orsmga003.jf.intel.com with ESMTP; 25 Sep 2020 00:36:38 -0700
From: yadong.qi@intel.com
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Yadong Qi <yadong.qi@intel.com>
Subject: [kvm-unit-tests PATCH] x86: vmx: Add test for SIPI signal processing
Date: Fri, 25 Sep 2020 15:36:24 +0800
Message-Id: <20200925073624.245578-1-yadong.qi@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yadong Qi <yadong.qi@intel.com>

The test verifies the following functionality:
A SIPI signal received when CPU is in VMX non-root mode:
    if ACTIVITY_STATE == WAIT_SIPI
        VMExit with (reason == 4)
    else
        SIPI signal is ignored

The test cases depends on IA32_VMX_MISC:bit(8), if this bit is 1
then the test cases would be executed, otherwise the test cases
would be skiped.

Signed-off-by: Yadong Qi <yadong.qi@intel.com>
---
 lib/x86/msr.h     |   1 +
 x86/unittests.cfg |   8 +++
 x86/vmx.c         |   2 +-
 x86/vmx.h         |   3 ++
 x86/vmx_tests.c   | 134 ++++++++++++++++++++++++++++++++++++++++++++++
 5 files changed, 147 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/6] sev/i386: Add initial support for SEV-ES
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11800615
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 43F1C112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 19:04:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0898121D42
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 19:04:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="PFOcTaEr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729745AbgIYTE2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 15:04:28 -0400
Received: from mail-bn8nam11on2077.outbound.protection.outlook.com
 ([40.107.236.77]:28641
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728069AbgIYTE1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 15:04:27 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=iMlp+NnyQYMHni7mJpzT6sqRMDbSTaYdOoL1QMk2pml+xqo1Su83I14WwKI9NmhG2dmFL3cHGQ0rUWpbNu/YFSG5juZbk9t0kvXPXYlyoljTVEtQ6sztDgzmACEvKUtfpVlOu2bAVa50dFNG+rp5C5FIM1PXXUhsvph5IHgV/UcRibvVuNT4BJwTqIG5fgnkzEbkf+l3Kp5SFmOhS0QnljANA7cRR5u7Ele12StoW7NOPGSWhDjhNcyVFVVrwwdGwsKi4gHrzW+U/CgeDLBI4y3Dpln9yfENhxgPy07m45mIjMXEaSyzj8L0Yhb3HryfFfH8TPZZl+8NYeSbCeqyGw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qnGr0S8uGAzeDpWKwoRpwkcNUvB3BEpyqXdIK+1wAC4=;
 b=ifdZ2bBRpSmPydYx7h+A7vmB5YKKd9eVzEUr31QFwECc7nZfvbcU+4xAG2Ny8gBuqUlFvva/EdH2N1uBkxrFwvmIXFEKnUzYbhfXYmy2kYrUex5nnQ3pEk6by6tQJE+zhxg8UJXuaQ61wdPuqrE/ez1VfOjcaQgcWfSmBP1PPRhbH0nSPoxmJPCd+vbpMd8ZdLhDSZ+HOz6DOSFu6dADsUTqsEdWK1YS9yUgVGf1BUqES7iyaQ0Jpr+H14kqiyDs/TJMW8D+onCIuy4WmM51Kqeoz5zO4/eXjrpQDAxI2Bh/0btB3jFCyyS/SyWR3Qdx9kuPvOU2asmL2hTN+ew4ww==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qnGr0S8uGAzeDpWKwoRpwkcNUvB3BEpyqXdIK+1wAC4=;
 b=PFOcTaErpmUzYeeRWBZksAj+KhoCRBw8nbtbdOwamdIK9qcfVt8ceG47HVpZCZs3DxDKt4kq7FtRcl2R7tBINBUWjl3Hvzs5k03xXvYDTKZF4Xi5wtnSPMX5AGI5rP02A9MnQUuNWIgOZJ1VctCqda/Z6API0bY0Ct4kKBsrWRg=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4297.namprd12.prod.outlook.com (2603:10b6:5:211::20) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.22; Fri, 25 Sep 2020 19:04:25 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3391.024; Fri, 25 Sep 2020
 19:04:25 +0000
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
Subject: [PATCH v4 1/6] sev/i386: Add initial support for SEV-ES
Date: Fri, 25 Sep 2020 14:03:35 -0500
Message-Id: 
 <29ff1690a9f84536ccd303cda9f105814e117f45.1601060620.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1601060620.git.thomas.lendacky@amd.com>
References: <cover.1601060620.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: DM5PR15CA0032.namprd15.prod.outlook.com
 (2603:10b6:4:4b::18) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR15CA0032.namprd15.prod.outlook.com (2603:10b6:4:4b::18) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3412.20 via Frontend
 Transport; Fri, 25 Sep 2020 19:04:24 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: cb7633e1-5362-4627-6c89-08d86185d1c0
X-MS-TrafficTypeDiagnostic: DM6PR12MB4297:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB42975FAABACF8B8C51B55C29EC360@DM6PR12MB4297.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 W6h2JHIx4sslAl+7ApPXQleOuljSoufIHXrMJt0F226KXT+NWHdDuPoMnbvQwvNjz1Adv9eI9iUyreQ1Eeo8bg2xdscmRaWx0c8+V+jRbfqidlYb428Ic0U2taPP/QyzqCzdJvmm86mF2De0uuEYPMNMNmThkWMxvW8Mp8K0Ud2cQ/3gjarY52OBr7ZflCVXLOgjsqWEOZSnju8ghu6qrqp1ATWrOc9nEcPg2gOyMzLzK2vl0qLX164j5LEcSSFqdISDkbriQVFJGHtMEnwST38tDrdUZ2pJZcqgFGLKEQVvw9SnUQl8YTwiOXin4Q9RDC1BZJLrlqIQvxdX3KwJMsevc94EBNczU7sugUNIlPXKjnt3W0TT7ZbzrCST2clTPLbpfNimY9HgL780flyg0IdaL0TOky9fpOacvNh9rHw=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(136003)(396003)(376002)(39860400002)(26005)(7416002)(956004)(186003)(6666004)(16526019)(54906003)(2616005)(6486002)(66556008)(66946007)(36756003)(8936002)(66476007)(86362001)(316002)(478600001)(7696005)(52116002)(2906002)(5660300002)(4326008)(83380400001)(8676002)(309714004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 75N56JZPgwqEk1hgORCezZDfTSlBrEKkYfrIQvkeAsTfgAW84DYcfuz5Q7sVQxCiYAqvXN0wN1T90wpHbT1OYjavfII2IBgf5G/OCP9QHKTDIjZKtrL4ob4th7mMehz0HWY8dU0v+xf3iLYVSIc3q19oLaaJa+nvXHRTI87cIxaby99bnR3CkHn4LcFdJ4LY/XxD9MEPwd5akB1inNOMK5Zl7jfsCe6zIpU/ZMPAAirdDlD8imBDm99MIvcQU61mwSZRIQ5ih09/mZnB5HU1S/RDekCymVGLWzNtlWB2ne0hNpIkagT4X3o+krC3cDgnTWJ6ROHtQrYOh3ZP6jBjRFUTKvkFvfni/nn4C20ya8pmZBb+Yzq0fwIiMK1nOXuv//hOKPwKEmipuIUKEXzXSJ7M1UmgZAezVnXUnCCTGN+Qz2eYZYwUseT7WIv5kh/1cniL5WrR6g7ZbksivwXzv1eGiszdeKT0BMeeuNtrni7hUhduyGTQiHYzAo+t4WhTaCJNRAg4ow58YEc/ve2IaQTZ6RwU2/s0Fd/LKxGxRfmru17DMzS137CJeDVaeCBf3cr+N6bW6t9e0CwVtRTLJep+vw87XPMjJvRVlreVHEFoyoNh/51dYLZOM8w1ECEBXU7fZLig43Y6htFItzdMjw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 cb7633e1-5362-4627-6c89-08d86185d1c0
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 25 Sep 2020 19:04:25.3077
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 fd5aSg4bFPy2ESMgDvjr7+cOKV11ZrEvYuWOytDJNUJUL9vlTt3PEFUOmyGASKhI2KuXie/EPoaYPdX0wyrQ3g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4297
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
 target/i386/sev.c      | 44 ++++++++++++++++++++++++++++++++++++++++--
 target/i386/sev_i386.h |  1 +
 4 files changed, 49 insertions(+), 2 deletions(-)

```
#### [PATCH v1 1/4] memory: allocation in low memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11800199
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1E5092C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 16:02:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4872120759
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 16:02:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Dr2kkros"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728492AbgIYQCx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 12:02:53 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:30696 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727201AbgIYQCw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Sep 2020 12:02:52 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08PG1tVC138146;
        Fri, 25 Sep 2020 12:02:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Etdk7PsqeLaD3Vusxf283pn0UpNfftluNM0Nl0Hj960=;
 b=Dr2kkrosiZlfGK2ingIVQlJsmmoocA+ZlvWqpno42OC/wGbMztC4QEW0ktKCE1T2zSKW
 bw6TUNHhrhDbbdg04d0hrCft3jeqIWrr8J9gcltyLZRauYxI8KZQJNYpxUuYx2L+LzyA
 bwDCgVWEBw+PWWmlpBmwExQdXJSV24E/w0B2EblvbuA9MFW4/IbNrlcDSui7Kq9Y3/yq
 SwJhVANVZO7LUV1IVm9sfMWsaJYEFsmog1e5uJkWCStpPVB7nKpv2NJSJBZyUMBSHtO1
 f9MJkzWx/oRAvoYwGMZWuahsNqsE+Yq8/2wDWegpEdWJRzayy6MecBMRxcD1vCeZubNp oQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33skhp0bf1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 12:02:51 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08PG24X6139218;
        Fri, 25 Sep 2020 12:02:51 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33skhp0bd4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 12:02:51 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08PG2jXK024957;
        Fri, 25 Sep 2020 16:02:49 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03fra.de.ibm.com with ESMTP id 33s5a98cms-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 16:02:49 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08PG2kHc30474522
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 25 Sep 2020 16:02:46 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 80EEFA405B;
        Fri, 25 Sep 2020 16:02:46 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1730FA4054;
        Fri, 25 Sep 2020 16:02:46 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.49.151])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 25 Sep 2020 16:02:46 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com
Subject: [PATCH v1 1/4] memory: allocation in low memory
Date: Fri, 25 Sep 2020 18:02:41 +0200
Message-Id: <1601049764-11784-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1601049764-11784-1-git-send-email-pmorel@linux.ibm.com>
References: <1601049764-11784-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-25_14:2020-09-24,2020-09-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 clxscore=1015 spamscore=0 bulkscore=0 phishscore=0 lowpriorityscore=0
 mlxscore=0 malwarescore=0 suspectscore=1 adultscore=0 mlxlogscore=999
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009250109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some architectures need allocations to be done under a
specific address limit to allow DMA from I/O.

We propose here a very simple page allocator to get
pages allocated under this specific limit.

The DMA page allocator will only use part of the available memory
under the DMA address limit to let room for the standard allocator.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 lib/alloc_dma_page.c | 57 ++++++++++++++++++++++++++++++++++++++++++++
 lib/alloc_dma_page.h | 24 +++++++++++++++++++
 lib/s390x/sclp.c     |  2 ++
 s390x/Makefile       |  1 +
 4 files changed, 84 insertions(+)
 create mode 100644 lib/alloc_dma_page.c
 create mode 100644 lib/alloc_dma_page.h

diff --git a/lib/alloc_dma_page.c b/lib/alloc_dma_page.c
new file mode 100644
index 0000000..6a16e38
--- /dev/null
+++ b/lib/alloc_dma_page.c
@@ -0,0 +1,57 @@
+/*
+ * Page allocator for DMA
+ *
+ * Copyright (c) IBM, Corp. 2020
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#include <libcflat.h>
+#include <asm/spinlock.h>
+#include <alloc_dma_page.h>
+
+static struct spinlock lock;
+static void *dma_freelist = 0;
+
+void put_dma_page(void *dma_page)
+{
+	spin_lock(&lock);
+	*(void **)dma_page = dma_freelist;
+	dma_freelist = dma_page;
+	spin_unlock(&lock);
+}
+
+void *get_dma_page(void)
+{
+	void *p = NULL;
+
+	spin_lock(&lock);
+	if (!dma_freelist)
+		goto end_unlock;
+
+	p = dma_freelist;
+	dma_freelist = *(void **)dma_freelist;
+
+end_unlock:
+	spin_unlock(&lock);
+	return p;
+}
+
+phys_addr_t dma_page_alloc_init(phys_addr_t start, phys_addr_t end)
+{
+	int start_pfn = start >> PAGE_SHIFT;
+	int nb_pfn = ((end - start) >> PAGE_SHIFT) - 1;
+	int max, pfn;
+
+	max = start_pfn + nb_pfn / DMA_ALLOC_RATIO;
+	if (max > DMA_MAX_PFN)
+		max = DMA_MAX_PFN;
+
+	for (pfn = start_pfn; pfn < max; pfn++)
+		put_dma_page((void *)((unsigned long) pfn << PAGE_SHIFT));
+
+	return (phys_addr_t)pfn << PAGE_SHIFT;
+}
diff --git a/lib/alloc_dma_page.h b/lib/alloc_dma_page.h
new file mode 100644
index 0000000..85e1d2f
--- /dev/null
+++ b/lib/alloc_dma_page.h
@@ -0,0 +1,24 @@
+/*
+ * Page allocator for DMA definitions
+ *
+ * Copyright (c) IBM, Corp. 2020
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#ifndef _ALLOC_DMA_PAGE_H_
+#define _ALLOC_DMA_PAGE_H_
+
+#include <asm/page.h>
+
+void put_dma_page(void *dma_page);
+void *get_dma_page(void);
+phys_addr_t dma_page_alloc_init(phys_addr_t start_pfn, phys_addr_t nb_pages);
+
+#define DMA_MAX_PFN	(0x80000000 >> PAGE_SHIFT)
+#define DMA_ALLOC_RATIO	8
+
+#endif /* _ALLOC_DMA_PAGE_H_ */
```
#### [PATCH v3] KVM: Check the allocation of pv cpu mask
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11800483
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0270D139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 18:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D140022B2D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 18:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tZdsuSUs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729631AbgIYSHz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 14:07:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59590 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726368AbgIYSHz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 14:07:55 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6CA1AC0613CE;
        Fri, 25 Sep 2020 11:07:55 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id x16so2465669pgj.3;
        Fri, 25 Sep 2020 11:07:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=JsCppV/bmsXZUBRfSaY9SL27S9Ub2HG1i6C0hRa6EVE=;
        b=tZdsuSUsj0ng7HTsKzxvOHVBb5mFFSSEzLq0L+JGhTu918YqYGnycwGT26nyT7SiTj
         wM275tJEa40Upp3J35MGnNt1tpE6uev0CFw2oSdL3vJAHiTkgqKfNoPur1JQ+Pf+8B0z
         Y9igeHsm83sQuWywKLlC/VCKMi4ov7baF9YjQfmUclyLlZ9i6dWYTNrv4gWdCY7/pdhb
         dJ3WYvo8tbjydhobEbtVgFNVA5lWKW8YWRzXbKMgsJsJ8xWEXZiv3CH1+58/wHIa2ocz
         Sa8SjIv2Y4gmRrJPVbRqWQhi23rMDf9zHqBg7FhN46rFg8EHXqpwHLFnLxsGnOu9hlMv
         XMBA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=JsCppV/bmsXZUBRfSaY9SL27S9Ub2HG1i6C0hRa6EVE=;
        b=gO73vZnWpyCweDNlUJeI1oxlC4q0mr0ppCjYI0qXmIBo8rINSvKwm2LYSrbQdcRqdN
         2gvWoauYXxH5oLS4SG0XWy1xQOEnc8o02KcKXYbTypXsU6kCMQCP1AQTtf5/m7QrRuIY
         pSYiMmSgfgajsD+0vBbu0M+Vs5jUPyG9SKVNVw/j4s5CxkxXSQ4R1K+WolEO71qs+21m
         QqLWW6LlIXNuR1gSZLahpSmjoIJ9vHyJB0rkg4golbCXsJ/241/37Ois4WFtnwraf+VD
         TCafPMllHm870XBHp6QR6/1qaBY6FBZFYvA7c3JcOjxrC5rlYfA4kpe0K7GEkzgbb9Uv
         jouA==
X-Gm-Message-State: AOAM531vxWyVl1+43CqpeqeZ3kCb0lQl4bbm+Ab7VQtLUGwjh0tFx0zs
        GMOX6LCHtdvAQA2dzTxTA3eYHiv0x5/V
X-Google-Smtp-Source: 
 ABdhPJy1/0rKu+54wFhxJYw5dahCMg3cJvq7kuvb+TbDH6a/hXEP5JwMHA2BI2v7o2jCmtEpz5KiHg==
X-Received: by 2002:a63:5102:: with SMTP id f2mr151366pgb.15.1601057265909;
        Fri, 25 Sep 2020 11:07:45 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 ie13sm2700535pjb.5.2020.09.25.11.07.42
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 25 Sep 2020 11:07:45 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v3] KVM: Check the allocation of pv cpu mask
Date: Sat, 26 Sep 2020 02:07:38 +0800
Message-Id: <20200925180738.4426-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

check the allocation of per-cpu __pv_cpu_mask.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
v1 -> v2:
 * add CONFIG_SMP for kvm_send_ipi_mask_allbutself to prevent build error
v2 -> v3:
 * always check the allocation of __pv_cpu_mask in kvm_flush_tlb_others

 arch/x86/kernel/kvm.c | 27 ++++++++++++++++++++++++---
 1 file changed, 24 insertions(+), 3 deletions(-)

```
