#### [kvm-unit-tests PATCH 2/2] x86: svm: Add test for L2 change of CR4.OSXSAVE
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11866919
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 40CDAC2D0A3
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:10:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5C6120759
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:10:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="X9H8n8Jo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727468AbgJ2RKf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 13:10:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34094 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725957AbgJ2RKe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 13:10:34 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 21E5DC0613CF
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:10:34 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id b7so3268447ybn.3
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:10:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=Nu3N33BP5UwHRfyIOYQtPvew2pFcbwX2S1cOPNYDlBY=;
        b=X9H8n8JoVENHK4YSrSCWhQBf8clRY1gs0iuDOSWA8jdyxtZm9llfAthBRh+zuHGxJ8
         dwEuTu4i+ylLwlpgXS0sGfMjYpuGNOcl4kpdSktizLd7zs0ZemGlFUqQgmAGyKgKGQPq
         WseIgI7sL+FrC2uLum0+UAkEFZbdbFy3US6PDpj/kcgo9rCjywIzXn+GyuMrsy1ddba7
         9sPN8m9zuAwd3qJOCLUUypAgYbRCc1n1l9Hydt0vlJuws0ylWLoY+7B9jsVCprzNll5i
         9WsJRahWgwJZMQxVgiSw2yPl0P6847jF3XAmElxHdFLdDpUnT2AYouzT6g4CiatQlXnX
         uxUA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Nu3N33BP5UwHRfyIOYQtPvew2pFcbwX2S1cOPNYDlBY=;
        b=q2iC0mjtIUKwD7wYnucOAlsGLQ55FX0pJ+d/UuV32DO5KuGySXr2n6CS/1dlqI3VSm
         Hf8mzcWZ3F3GlZUG1QYdlipy5fD6E1ovNIZ8gzt+/6PgcT7Q679RiTDtOvG67MVMU3JW
         Ray42wSPye8MwQDz0/CwCoVG3UfWua1YNOynq04TD4mTbu8l0NS94I3iv8YaY49ZNfzh
         59TTwVzpg11iEZ0awbo6/WJ0vgRQyOfEf5KV1Hctomk2Bk4yZCB5GYjvvY+DLhEBDjS/
         kDwyoZP4ySpXqcThILARvD5fBKVnFr1b5miHELiJ6ckROZJulWmFzfbnwvRfPcViVtKQ
         hqOg==
X-Gm-Message-State: AOAM530m3vK5IFy5fCBIVmkSDP+E6VOnbc2GvgTWEYWTYXx9Hb8txXQ2
        a1QJ6CC4zMAvG3blTCl3gzzV71h0xjOmMsFfvicdN8muVS34JnJP1y7oHTh7xwTkh0t81n/QK0F
        yx4Bn2n4PSnEfyNCTCriAGFvsCc2JDSNn4syJyWM3UECloJsaqc6WcQqNeCmWLnM=
X-Google-Smtp-Source: 
 ABdhPJyCEfkc/lPnaZyIa/LjrJWxYS+tQuONWAujA4GaTTu37TerHuh1a1sM8oBhy3NfPGONtPoFKnfYBS4Ifw==
Sender: "jmattson via sendgmr" <jmattson@turtle.sea.corp.google.com>
X-Received: from turtle.sea.corp.google.com
 ([2620:15c:100:202:725a:fff:fe43:64b1])
 (user=jmattson job=sendgmr) by 2002:a5b:888:: with SMTP id
 e8mr7172137ybq.436.1603991433335; Thu, 29 Oct 2020 10:10:33 -0700 (PDT)
Date: Thu, 29 Oct 2020 10:10:24 -0700
In-Reply-To: <20201029171024.486256-1-jmattson@google.com>
Message-Id: <20201029171024.486256-2-jmattson@google.com>
Mime-Version: 1.0
References: <20201029171024.486256-1-jmattson@google.com>
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [kvm-unit-tests PATCH 2/2] x86: svm: Add test for L2 change of
 CR4.OSXSAVE
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Ricardo Koller <ricarkol@google.com>,
        Peter Shier <pshier@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If L1 allows L2 to modify CR4.OSXSAVE, then L0 kvm recalculates the
guest's CPUID.01H:ECX.OSXSAVE bit when the L2 guest changes
CR4.OSXSAVE via MOV-to-CR4. Verify that kvm also recalculates this
CPUID bit when loading L1's CR4 from the save.cr4 field of the
hsave area.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 x86/svm_tests.c | 35 +++++++++++++++++++++++++++++++++++
 1 file changed, 35 insertions(+)

```
#### [PATCH] KVM: arm64: Fix AArch32 handling of DBGD{CCINT,SCRext} and DBGVCR
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11867007
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2AB58C4363A
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:24:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97F0E20796
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:24:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603992269;
	bh=gfxtWHBGo7NtfP7tLPK6RFZyeD7tCsd/8WBmZ+nR6YY=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=w5phggnKeTXJqYA3uSVIVlwLwxQtL6uDyYaN9f73DP3lu7CAFT04YswnZUGzBqzW6
	 PY4kSSbQywe2rnrDTyV3KPcPvf/NNU6WtZH33XHq/3runXCOd09F85vArR6NsuYOWe
	 cZlHE4kiow5/1YaO10tZjed3bjwAgSlTfAOS5pCs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726960AbgJ2RY2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 13:24:28 -0400
Received: from mail.kernel.org ([198.145.29.99]:42790 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726591AbgJ2RY1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 13:24:27 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 30652206CB;
        Thu, 29 Oct 2020 17:24:26 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603992266;
        bh=gfxtWHBGo7NtfP7tLPK6RFZyeD7tCsd/8WBmZ+nR6YY=;
        h=From:To:Cc:Subject:Date:From;
        b=Qz0o8Qs612ufqKClnWj5umhRrwTci7gM4hnRQjVEiEngEZTKd1kT2bJkOJZTZnmRd
         cYpPPMcTZPPWQ8qifnSDSbJRDyBlL4iufRqh/FGZPu0aLgFdpXkFMz2igZQPLDc+bi
         2kvULfEEvoSwm5EV7cccDt4jDS//UDtakQZfcIcc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kYBex-005VVb-Py; Thu, 29 Oct 2020 17:24:23 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH] KVM: arm64: Fix AArch32 handling of DBGD{CCINT,SCRext} and
 DBGVCR
Date: Thu, 29 Oct 2020 17:24:09 +0000
Message-Id: <20201029172409.2768336-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The DBGD{CCINT,SCRext} and DBGVCR register entries in the cp14 array
are missing their target register, resulting in all accesses being
targetted at the guard sysreg (indexed by __INVALID_SYSREG__).

Point the emulation code at the actual register entries.

Cc: stable@vger.kernel.org
Fixes: bdfb4b389c8d ("arm64: KVM: add trap handlers for AArch32 debug registers")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 1 +
 arch/arm64/kvm/sys_regs.c         | 6 +++---
 2 files changed, 4 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11866445
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0975C56201
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 13:43:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 68D1120759
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 13:43:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="P9SZ8r3M"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726354AbgJ2Nmd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 09:42:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57732 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725765AbgJ2Nmc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 09:42:32 -0400
Received: from mail-ed1-x542.google.com (mail-ed1-x542.google.com
 [IPv6:2a00:1450:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D959AC0613D3
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 06:41:50 -0700 (PDT)
Received: by mail-ed1-x542.google.com with SMTP id v4so3126142edi.0
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 06:41:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=iwibPJxeDmGnHQbnigiBzcULAYXQt3uTqFbHqr06h6g=;
        b=P9SZ8r3MgSXoP5asOTto/xazlIYsr/rQCL7CmXnICDGMbfbR/hB1pPlFwNo3dtyKhT
         sy10py2hMH4u8OQnEyFN37S0tvFA8N/pGe2vCqzS9aBKcCaeRFESmxLr116sg2g2/O6j
         jqBThR+hPNQwUlu0shmquwW+7WRQtUMbZE7loywZDa0ddZdstNANiPyRwYLYu3Y3l8Ia
         SgAaw4PUH7U6CGrBNfv9eN6IoylbCnQZzifNi8rjfKWQMKVJD/99KsjRoxdFJiENT8Iv
         a3y8/Nj9KtXl//WJ9KcXzEy1TqtJet4yoIhwggjYvdM2VoH7DTocXs2rBrVJ6GfDHVE0
         3eUg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=iwibPJxeDmGnHQbnigiBzcULAYXQt3uTqFbHqr06h6g=;
        b=O91TGwN6m9x01dmuk9/Th1rwDRBdlSKCIauNkGRMKa5h4OcL/Ldto4PtBUzWJUrSh6
         L/j+EHdexazYPmVulWEWlAeCmbFT/2RRizrs1p6sbA9X57deftpvI1wM4zzjm3Tu8p6N
         w7bXkT06kc4VZSO97QHbXC8ONDFDFDfufzd4vfJt/CiHwv073AHMdzZQ9MPaWcQKPNc8
         tGWmouliUV3yawvjXn+wRU7K/eCifIsO8cB8+XjLC/MZ+gLMhdJQV08xqjMWrnJz+TMo
         OA+AUK4utqBI0dK64N9pycX+rtiuKEaPQ8nvu0OekjPS4qPPGPkkhsj/eit4BAv/89kW
         bV+A==
X-Gm-Message-State: AOAM530nurdxZjRgws3nJOvKX04PSQbRQCAmU56n732OFhR0CDbOKAEX
        SFercqF0BuVgnXpeTGyOV5HiavBFfFpwJQ==
X-Google-Smtp-Source: 
 ABdhPJzRtm4iV5bUSOGpNtq9Oh0riLDfgOMeb4SijPgCz5JCXklMECGm4sA01JfwNWHs24+DlcKU9Q==
X-Received: by 2002:a05:6402:b87:: with SMTP id
 cf7mr4180523edb.137.1603978909105;
        Thu, 29 Oct 2020 06:41:49 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 z20sm1525837edq.90.2020.10.29.06.41.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Oct 2020 06:41:48 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw
Date: Thu, 29 Oct 2020 14:41:45 +0100
Message-Id: <20201029134145.107560-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace inline assembly in nested_vmx_check_vmentry_hw
with a call to __vmx_vcpu_run.  The function is not
performance critical, so (double) GPR save/restore
in __vmx_vcpu_run can be tolerated, as far as performance
effects are concerned.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/nested.c | 32 +++-----------------------------
 arch/x86/kvm/vmx/vmx.c    |  2 --
 arch/x86/kvm/vmx/vmx.h    |  1 +
 3 files changed, 4 insertions(+), 31 deletions(-)

```
#### [PATCH 1/4] KVM: selftests: Don't require THP to run tests
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11867497
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9496C55178
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 20:17:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E13820720
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 20:17:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KMwAy9E0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726529AbgJ2URY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 16:17:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35232 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726509AbgJ2URW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Oct 2020 16:17:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604002641;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=a/Ga9qLMXiSt+t8rm7ErthD7fYkO9+JKlbonBWSv1No=;
        b=KMwAy9E0+Bb3epJ2DFZQKKSZcKIObV055JdYlMjBuu7PjsYOFYBzHwP1PaV0htvgV9CDxb
        Vf1pC//zTU7AocFnDZtPhRolZMbzlej9qjcbkux0reYqzBIfrRCEDSoW4cxJDdCU6PpgqP
        ZUYYvqf9AQPYXSlhweXeuCi9oIuQ8fo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-73-w33TEpelOZCARxjcKf71Lg-1; Thu, 29 Oct 2020 16:17:14 -0400
X-MC-Unique: w33TEpelOZCARxjcKf71Lg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D09C98030A3;
        Thu, 29 Oct 2020 20:17:12 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BD7776EF68;
        Thu, 29 Oct 2020 20:17:10 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, Dave.Martin@arm.com,
        peter.maydell@linaro.org, eric.auger@redhat.com
Subject: [PATCH 1/4] KVM: selftests: Don't require THP to run tests
Date: Thu, 29 Oct 2020 21:17:00 +0100
Message-Id: <20201029201703.102716-2-drjones@redhat.com>
In-Reply-To: <20201029201703.102716-1-drjones@redhat.com>
References: <20201029201703.102716-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unless we want to test with THP, then we shouldn't require it to be
configured by the host kernel. Unfortunately, even advising with
MADV_NOHUGEPAGE does require it, so check for THP first in order
to avoid madvise failing with EINVAL.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 23 +++++++++++++++-------
 1 file changed, 16 insertions(+), 7 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] x86: vmx: Add test for L2 change of CR4.OSXSAVE
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11866917
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 722C8C55179
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:10:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D08121481
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:10:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="YgaPoj/X"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727344AbgJ2RKd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 13:10:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34088 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725957AbgJ2RKc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 13:10:32 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 979E3C0613CF
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:10:32 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id 189so3274867ybp.12
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:10:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=l8eIoaaUnZd6d2xO5UkZkCplg4SEHOvTFFZSknr9hKw=;
        b=YgaPoj/XrpsdPD7VRiwTVLQf2cSGa65dkmUuHrmnobnDUgJfRP71xV5RtV/nvJymuq
         olBm5ifdxU/tr1tQOL7aj5Pr0n7u6RO4RUuZOGliuyKEtWjIRklDbjNaOqGJVhvwsiPN
         fLePFdlmA/WP1mI8iLSoaLMCwJOFN1e3RpFCx52mvYdgcEqHkE07jGtmAiUagkasLpuW
         8DByqdKa0oSJQe8CoDOkidtuOSf1I5LbIWls20/1l6CCwqx4ig7v08D5lMSuE3LTe8lj
         cSpkN3pc7EqRhYcy5A13dngfOMZm/9pudMxToAaqsxOWRCBLvj3ScboMwZSUWOeqzPG1
         t4sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=l8eIoaaUnZd6d2xO5UkZkCplg4SEHOvTFFZSknr9hKw=;
        b=tNFKoYbA2fEPz0XZJAuq0MIWP4Id8jsx7IV1yqJufbfriT0MnYAdtxMU/Gyfn9dgrA
         EdoP6iYd0mnIHZ0ZPzKooPyc+Srg7UtwlO2/WNtsRdZCA9YjaZdFW8sq5KGDw3ty4YRZ
         Sz5IXaBthaTAYCDhuCzOwimeQPSiLvE7QThfTNP9zXz4rIvwdaQfT+gM34G8Gb9s+vA1
         QZOa4G61k8Z8KvVuhbDJSk6zOqIir3vRN1RUam/AULCmjVv1YsHb0/mKbhNLE7ONeyri
         QXcnmYE1QKaBJFOcSJfWsOge0FPV0hGK1d3MYBS2O4DB90ANUPCniC/d81gh5aim4zCO
         Ry9g==
X-Gm-Message-State: AOAM532Qsfa8k+Jzz4448McvYak+LsO6NUnNw0Mf1oh1SyzW9phJyB8W
        Aw0rKk6QmzaSoF3S4jAZ/E6EdwhYcCss5mTDUh+qeLmuF+WOx9w+NP7nKG++Lb8onP/JvH5+jb9
        oxg7uZjeeZGiuiUr7oxD+nOZ+d0yVgUylKyVYAGaR+m2icFAbKzJieMlBuM7JaWQ=
X-Google-Smtp-Source: 
 ABdhPJxxovbfs/W4E5Fg9eCPn1dymlqPWtmG/deCMqhh3eaQJguiLOfXNdGn3knHNelJ4xRMSclrjJRtzBbtGg==
Sender: "jmattson via sendgmr" <jmattson@turtle.sea.corp.google.com>
X-Received: from turtle.sea.corp.google.com
 ([2620:15c:100:202:725a:fff:fe43:64b1])
 (user=jmattson job=sendgmr) by 2002:a25:d345:: with SMTP id
 e66mr7065387ybf.307.1603991431788; Thu, 29 Oct 2020 10:10:31 -0700 (PDT)
Date: Thu, 29 Oct 2020 10:10:23 -0700
Message-Id: <20201029171024.486256-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [kvm-unit-tests PATCH 1/2] x86: vmx: Add test for L2 change of
 CR4.OSXSAVE
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Ricardo Koller <ricarkol@google.com>,
        Peter Shier <pshier@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If L1 allows L2 to modify CR4.OSXSAVE, then L0 kvm recalculates the
guest's CPUID.01H:ECX.OSXSAVE bit when the L2 guest changes
CR4.OSXSAVE via MOV-to-CR4. Verify that kvm also recalculates this
CPUID bit when loading L1's CR4 from the "host CR4" field of the
VMCS12.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 lib/x86/processor.h | 52 +++++++++++++++++++++++++--------------------
 x86/vmx_tests.c     | 34 +++++++++++++++++++++++++++++
 2 files changed, 63 insertions(+), 23 deletions(-)

```
#### [kvm-unit-tests PATCH] arm64: Add support for configuring the translation granule
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11866739
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A0F1EC4363A
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 15:53:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CF83206B2
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 15:53:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=armh.onmicrosoft.com
 header.i=@armh.onmicrosoft.com header.b="3Jy+dA5h";
	dkim=pass (1024-bit key) header.d=armh.onmicrosoft.com
 header.i=@armh.onmicrosoft.com header.b="3Jy+dA5h"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728467AbgJ2Pw7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 11:52:59 -0400
Received: from mail-eopbgr40062.outbound.protection.outlook.com
 ([40.107.4.62]:50403
        "EHLO EUR03-DB5-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728459AbgJ2Pw7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 11:52:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=armh.onmicrosoft.com;
 s=selector2-armh-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ke6dLF2QgLBSdOv05hjNSZSOpmhELO3Bgg3EEK00Jwc=;
 b=3Jy+dA5hsDXfRnlt7MHRke/pfNcWnqnhWrXmLw23/Yz3XynqF7hkzSVgUcXrEL1k4MGG3S5JBU5D9nIPyLG1XsXjbuutfuT1XiyeMLoTXWrI/GPWpbNyywaNdsmShLH7N2KxgBFfmV+yidG+1s/GmSl8QYLGZdDb0TCmr2MfWys=
Received: from DB7PR05CA0023.eurprd05.prod.outlook.com (2603:10a6:10:36::36)
 by AM9PR08MB6241.eurprd08.prod.outlook.com (2603:10a6:20b:281::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.18; Thu, 29 Oct
 2020 15:52:51 +0000
Received: from DB5EUR03FT003.eop-EUR03.prod.protection.outlook.com
 (2603:10a6:10:36:cafe::4) by DB7PR05CA0023.outlook.office365.com
 (2603:10a6:10:36::36) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.18 via Frontend
 Transport; Thu, 29 Oct 2020 15:52:50 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 63.35.35.123)
 smtp.mailfrom=arm.com; vger.kernel.org; dkim=pass (signature was verified)
 header.d=armh.onmicrosoft.com;vger.kernel.org; dmarc=pass action=none
 header.from=arm.com;
Received-SPF: Pass (protection.outlook.com: domain of arm.com designates
 63.35.35.123 as permitted sender) receiver=protection.outlook.com;
 client-ip=63.35.35.123; helo=64aa7808-outbound-1.mta.getcheckrecipient.com;
Received: from 64aa7808-outbound-1.mta.getcheckrecipient.com (63.35.35.123) by
 DB5EUR03FT003.mail.protection.outlook.com (10.152.20.157) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3520.15 via Frontend Transport; Thu, 29 Oct 2020 15:52:50 +0000
Received: ("Tessian outbound a64c3afb6fc9:v64");
 Thu, 29 Oct 2020 15:52:50 +0000
X-CheckRecipientChecked: true
X-CR-MTA-CID: 19902f423d57cee3
X-CR-MTA-TID: 64aa7808
Received: from 87b761ea14f9.1
        by 64aa7808-outbound-1.mta.getcheckrecipient.com id
 60A64232-C721-4701-B08E-A39CFD9BAFC3.1;
        Thu, 29 Oct 2020 15:52:43 +0000
Received: from EUR04-DB3-obe.outbound.protection.outlook.com
    by 64aa7808-outbound-1.mta.getcheckrecipient.com with ESMTPS id
 87b761ea14f9.1
    (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384);
    Thu, 29 Oct 2020 15:52:43 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=CGYYK081E983J7U7DZF/79mwbU9keQ64avMHoM3AaoXZgXjaUt7lbYLwgV0omKVEZa5jxqjA/oKyvPSTPeUliRm32h0WL/E7fBmpbgE2l5jYGuYL9mn8+4fmafaKTjkAOo9Edxr4KV/zTaCMdOFHUTtil2vDhVBXbfYEEVqKadrTBUzmcZFicwnxTy1HvdnVTyOFBud75rhYiTRl1XQKx43gtd8RsV168eNHNvFVTtN6bC3Y4fDovfRK9UvdloM/4RzwY+Ua+Q7ZwuafOsfp3VuKgVYuyeYfS4SkRUIa4dQYrsf3EeeZuU4R2UvTDOIjoxLIg5TyJ6D7b71K1A94Tw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ke6dLF2QgLBSdOv05hjNSZSOpmhELO3Bgg3EEK00Jwc=;
 b=SQnjGnncvGNROXYCC9qeQE50D/ooXORe3nl82Wvp8F/B1FyKky3huKFkrIWpGMEXf110VJRHKcEsVTn2Dm+Q9p2fRxIs5WNt26G61iFNKs01NHL5b3SHJsHfLaHnuwnmEaD9plxjtJJhekucdlDzNmBLbQt4gVkhokRkugeAIwLwlyIg2AkuO2pRA460JVkHaGLVPzZIqfXdx2j1RxGiuzpwo6c/Bm8O1Nd/dM0p3dsQZ+E0ylMwEZ0zjQ/aShOhwEoLKbhSP2nN4vf+P8jAoRvyC2SpMQ/5Snm8S05zlFbNODzqyL/qvC8UC1vfPJ3twXNr7/V2JCD2GIoLFJaVLA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=arm.com; dmarc=pass action=none header.from=arm.com; dkim=pass
 header.d=arm.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=armh.onmicrosoft.com;
 s=selector2-armh-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ke6dLF2QgLBSdOv05hjNSZSOpmhELO3Bgg3EEK00Jwc=;
 b=3Jy+dA5hsDXfRnlt7MHRke/pfNcWnqnhWrXmLw23/Yz3XynqF7hkzSVgUcXrEL1k4MGG3S5JBU5D9nIPyLG1XsXjbuutfuT1XiyeMLoTXWrI/GPWpbNyywaNdsmShLH7N2KxgBFfmV+yidG+1s/GmSl8QYLGZdDb0TCmr2MfWys=
Authentication-Results-Original: vger.kernel.org; dkim=none (message not
 signed) header.d=none;vger.kernel.org; dmarc=none action=none
 header.from=arm.com;
Received: from DB8PR08MB5339.eurprd08.prod.outlook.com (2603:10a6:10:114::19)
 by DBBPR08MB4645.eurprd08.prod.outlook.com (2603:10a6:10:dc::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3477.25; Thu, 29 Oct
 2020 15:52:42 +0000
Received: from DB8PR08MB5339.eurprd08.prod.outlook.com
 ([fe80::f848:3db5:1e63:69a7]) by DB8PR08MB5339.eurprd08.prod.outlook.com
 ([fe80::f848:3db5:1e63:69a7%9]) with mapi id 15.20.3455.040; Thu, 29 Oct 2020
 15:52:42 +0000
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, nd@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH] arm64: Add support for configuring the
 translation granule
Date: Thu, 29 Oct 2020 15:52:29 +0000
Message-Id: <20201029155229.7518-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [217.140.106.49]
X-ClientProxiedBy: SN4PR0801CA0001.namprd08.prod.outlook.com
 (2603:10b6:803:29::11) To DB8PR08MB5339.eurprd08.prod.outlook.com
 (2603:10a6:10:114::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from camtx2.cambridge.arm.com (217.140.106.49) by
 SN4PR0801CA0001.namprd08.prod.outlook.com (2603:10b6:803:29::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.18 via Frontend
 Transport; Thu, 29 Oct 2020 15:52:40 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9ee518c2-2ebc-4277-cc07-08d87c22b0bf
X-MS-TrafficTypeDiagnostic: DBBPR08MB4645:|AM9PR08MB6241:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM9PR08MB62415A23F2E442F5F2303856F7140@AM9PR08MB6241.eurprd08.prod.outlook.com>
x-checkrecipientrouted: true
NoDisclaimer: true
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam-Untrusted: BCL:0;
X-Microsoft-Antispam-Message-Info-Original: 
 jMuegNps9kYxb79lolis5liDmPuZYM7JHaKuVNq54XlAIHO9K6DDFifo/4Zw1T8u7vW0v395Lf+x1t9aqK6WSgVgCFQmfGYKmRytLN9PkYW6JMWPii4C/7kmvuvtRlaC5gJ582cwZmf3dS1sNPvcE4tkfNl1DNAjkKTi3BUg4M5uB69coma3BgJPpiZY7ESDa22B+cvBpbqg+hIPDTf7kiSgX7CBR4P6przE2UDCJFjvra+9zn3/kIErWN9dgeQAsskxeFCo9lmV/KYIgnFPEl6+9KT+ZxIV0UJJ6ioxq7W/lOhJd9MCP4PvOHj5FvYf
X-Forefront-Antispam-Report-Untrusted: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DB8PR08MB5339.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(39860400002)(366004)(396003)(346002)(376002)(2906002)(6666004)(8676002)(16526019)(186003)(26005)(6916009)(36756003)(4326008)(7696005)(52116002)(6486002)(83380400001)(956004)(2616005)(86362001)(5660300002)(30864003)(316002)(66946007)(66556008)(478600001)(66476007)(1076003)(8936002)(44832011);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 +vmTGSmlmqYiN2/4ghwM1kl9C4/abUQ3CDuUpax4TupuJheKOQMk8YMOavA8zYQ1fQYUKfy87VYXENT8PtMfHHtpFYXGGhT3c5wgdItRlKmiEfJswARWpSl7BDqaRjRWVzlbRbpLzXoChZmio5MjVr5UFE43f4/K8EaUnIkEXPKeS8l1L8r3c6ZdvStBkeClMPCVjdbOUTxEufVewCgHgdc893BLVU8fV+RbO20bEDK5XcYuYnN14rNDas0mPpA71J/9PaNIAt5cNDOAPn22A5lVG05+M4obF2VCxQEXCkg377fzX1YJbyKe5A4BWshREkkQdwfWVkjk00X2lknYZLfVh5NwUuBTID0x+U8QZdyQley7KG4obgWXHTL3iUFRcMGl7jnkKLVUZ8JB5Suo3BMZU7vdzcirOF0VmsxTvF95p6gzbBS1RkGd4uXFl4SGt8hE67Zu+PrtobgyY3vgWUe14wHloV7yZz4ql9NSSa+75mIJPK6rtq49TyMuJ6dQGcyHx9Er6rq3CKQvtS/hOFdnfIdhphjPZHnU8BmmKh37Z+ltrOqAGy6KtTzHDmPFWNC7g2/aNv3K6Ls4gtcI4SHTZV3NK8Um+NRxH0OkeHYkPdAei55RhMx09z7xqGwCTCbnBM2tmO3Lo2NAWRZxwg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DBBPR08MB4645
Original-Authentication-Results: vger.kernel.org;
 dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=arm.com;
X-EOPAttributedMessage: 0
X-MS-Exchange-Transport-CrossTenantHeadersStripped: 
 DB5EUR03FT003.eop-EUR03.prod.protection.outlook.com
X-MS-Office365-Filtering-Correlation-Id-Prvs: 
 82701f55-6578-4860-9692-08d87c22ab7d
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 osswuIam2sEt77pHFNDlYjnRqsr3LS7B4adRjfeh3PgKUTaiZOAP5W8CVYOC5c31WFIkGWvvTxeJA/MtxUKtJlu2eYwDMe5DVsE436UabKBTPczQsj7r9KXSEnAR5ltSCx7NQnl4rgdLxulH3ADnHHycGPM+hhubSlfh8aprXHSDarWVa4Rm4r4TF2AI0UL64n5HI9ZsfG4RUI96+YrZF6qtSzTbTwHWVtFdn/j+wpPNcQUZQhsANPU1OaEbe/kGR8N4HQrwLW9/b54kne4aemq6whYcwUA710HhynuGWwX0BCqzDVqrCFOuHpd9eSTy/ZoDX2tYj2svkVudap9FXwz9pUjJJucqXYI5hdQKgforeozdnlxYU3EYBL3n2Np35BvKV14oTmqsEVYOw/xo1Q==
X-Forefront-Antispam-Report: 
 CIP:63.35.35.123;CTRY:IE;LANG:en;SCL:1;SRV:;IPV:CAL;SFV:NSPM;H:64aa7808-outbound-1.mta.getcheckrecipient.com;PTR:ec2-63-35-35-123.eu-west-1.compute.amazonaws.com;CAT:NONE;SFS:(4636009)(376002)(346002)(396003)(136003)(39860400002)(46966005)(70206006)(4326008)(8676002)(36756003)(70586007)(6916009)(2616005)(356005)(107886003)(81166007)(478600001)(83380400001)(956004)(7696005)(1076003)(82740400003)(82310400003)(6486002)(47076004)(186003)(316002)(44832011)(336012)(5660300002)(6666004)(26005)(16526019)(86362001)(8936002)(2906002)(30864003);DIR:OUT;SFP:1101;
X-OriginatorOrg: arm.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Oct 2020 15:52:50.8937
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9ee518c2-2ebc-4277-cc07-08d87c22b0bf
X-MS-Exchange-CrossTenant-Id: f34e5979-57d9-4aaa-ad4d-b122a662184d
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=f34e5979-57d9-4aaa-ad4d-b122a662184d;Ip=[63.35.35.123];Helo=[64aa7808-outbound-1.mta.getcheckrecipient.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DB5EUR03FT003.eop-EUR03.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM9PR08MB6241
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make the translation granule configurable for arm64. arm64 supports
page sizes of 4K, 16K and 64K. By default, arm64 is configured with
64K pages. configure has been extended with a new argument:

 --page-shift=(12|14|16)

which allows the user to set the page shift and therefore the page
size for arm64. Using the --page-shift for any other architecture
results an error message.

To allow for smaller page sizes and 42b VA, this change adds support
for 4-level and 3-level page tables. At compile time, we determine how
many levels in the page tables we needed.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 configure                     | 21 +++++++++++
 lib/arm/asm/page.h            |  4 ++
 lib/arm/asm/pgtable-hwdef.h   |  4 ++
 lib/arm/asm/pgtable.h         |  6 +++
 lib/arm/asm/thread_info.h     |  4 +-
 lib/arm64/asm/page.h          | 17 ++++++---
 lib/arm64/asm/pgtable-hwdef.h | 38 +++++++++++++------
 lib/arm64/asm/pgtable.h       | 69 +++++++++++++++++++++++++++++++++--
 lib/arm/mmu.c                 | 26 ++++++++-----
 arm/cstart64.S                | 12 +++++-
 10 files changed, 169 insertions(+), 32 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: apic: test self-IPI in xAPIC modeFrom: Ricardo Koller <ricarkol@google.com>
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 11867859
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0CBECC4742C
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 22:56:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E13720756
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 22:56:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="TWwamgbG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725854AbgJ2W4r (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 18:56:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59786 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725372AbgJ2W4r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 18:56:47 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7BF8DC0613CF
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 15:56:45 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id ec4so2654116qvb.21
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 15:56:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=cqVgUVr6NeVX3r2LoQl/czy6TdP/4mqDcQgIRYvpbWI=;
        b=TWwamgbGQnyjUTyUyW7/1azLQxnvAt4S4NKNq4rHAkqhkpoVmi37xSrkFilNd6LfT+
         T8hdXvhqw+Z73XExAgDgxS/JKHbsQ/4oJzJCQVLKNLy0ZeQBRltEjSkC3fZdT9bShTp7
         +LDsJ3IrkkUaJpuzhtj69MJQCXSt/RUSIJcjENRomlape/TJt9uwRpZT8x4MnL9Hc72y
         7UD+29oQYQOfz26Gpf+9ueC5RGBcJ06szXuPWNeubb8gQc5WwtlSThrof4k+SrPNNSSr
         m/1wPkD3UmDNBtoD69KWPSqxKHKi7947djwQzkwqdzCXmtMFhVigzH/RFQXTaqHma8/B
         QCUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=cqVgUVr6NeVX3r2LoQl/czy6TdP/4mqDcQgIRYvpbWI=;
        b=iIcpf3sYI9kebVgU99fN8Z3OQhocKQSu7kY4bl3Z8RFy05A/30EvF3KM1d3AlMnyqg
         BTfsc6PnWSwJWGv08m6GLjPQNnId0uNp5icxCkKvu3bue3i/X8TAcwwQyDKZdesbkRRQ
         HZrXyMdyE8jPlb9OoRH7JeG8CVrfcAwiAhpBm/qu6wSCxzmPFWQyUkq+qui6Pc4XEp+2
         +LF2sSUaswRlbhIiJZPrnj/R9PD9cyWlCsIYr3gXp2lkyFvERwdrDOBpLz3iw8xcw40Z
         t3xXqCnV1V1gJOzErbXX0fk9SVketH4+XjdZEpQ9+KxpPXuPXIpSdfoYc0huSMkDuhqP
         ofxA==
X-Gm-Message-State: AOAM533Ef+i2kG1SdOPqGH6L+IlP/MDy5R0GZ7Ou3waZDLRban15RPmb
        E9AFQ4GTPXbHNbwQINPqoR5rV84mBTyD5hqPjcjIIMdxUhm8/Q2sYOls+yfa+Jn2yx5HQme3Rfw
        y9A8cbwInNwb0wIffTb0d52AUg4I7ZWYHTo5nxl9p0wVi4I0kLtsuzbRexah9ei8=
X-Google-Smtp-Source: 
 ABdhPJxLhTVejee5OE8CtXcZdDhRgYHXmo4T7W6vtmMjAc3X8MC64SP4E6ojKgHQTXvyQqPn6r7MTPC7afaVkQ==
Sender: "ricarkol via sendgmr" <ricarkol@ricarkol3.c.googlers.com>
X-Received: from ricarkol3.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:6596])
 (user=ricarkol job=sendgmr) by 2002:a05:6214:125:: with SMTP id
 w5mr6429587qvs.3.1604012204594; Thu, 29 Oct 2020 15:56:44 -0700 (PDT)
Date: Thu, 29 Oct 2020 22:56:42 +0000
Message-Id: <20201029225642.1130237-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [kvm-unit-tests PATCH] x86: apic: test self-IPI in xAPIC mode
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org
Cc: Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ricardo Koller <ricarkol@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add self-IPI checks for both xAPIC and x2APIC explicitly as two separate
tests.  Both tests try to set up their respective mode (xAPIC or x2APIC)
and reset the mode to what was enabled before. If x2APIC is unsupported,
the x2APIC test is just skipped.

There was already a self-IPI test, test_self_ipi, that used x2APIC mode
if supported, and xAPIC otherwise.  This happened because test_self_ipi
used whatever mode was enabled before, and test_enable_x2apic (which
runs before) tries to enable x2APIC mode but falls back to legacy xAPIC
mode when x2APIC is unsupported.

Tested the case where x2apic is unsupported with:
./x86-run ./x86/apic.flat -smp 2 -cpu qemu64,-x2apic

Signed-off-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 x86/apic.c | 50 ++++++++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 48 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM/VMX/SVM: Move kvm_machine_check function to x86.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11866483
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1CC2C4363A
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 13:56:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 731DE20791
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 13:56:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="vXEhrLtE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727614AbgJ2N4G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 09:56:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59968 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726184AbgJ2N4G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 09:56:06 -0400
Received: from mail-ej1-x641.google.com (mail-ej1-x641.google.com
 [IPv6:2a00:1450:4864:20::641])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A1CF2C0613CF
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 06:56:05 -0700 (PDT)
Received: by mail-ej1-x641.google.com with SMTP id t25so3879314ejd.13
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 06:56:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0c1+bR9T+IplOpKDV6RvsAZ3ZFdVzQUrH0NfTUm42po=;
        b=vXEhrLtERJ9KdvJrljvr86XAWaPWGWu/mpmmOiBfg29cKmexUAH9RuzLZOZrvy+Wm8
         Jw3qPzVBGH/6jSVWIRq9cHNIJ1yCBiVPEjzwqqKw/SjFoCZjcyGZGTUsUGOTRMIeWylW
         nUt60iBERHk8ZrVY4t2ABYkEUQkc8Fi3qFu5tTnxwS/ZxHh4LNbDcYXuV7S51To2sY4t
         SFZuLc4ROkO+GH5tqattr0nhu5jmzi8OIVXB0Sku3YSzvHpGMo9mueuzpwEDu/uvvpnF
         i5Jcsa7p5wiRyzhcJXRX0ksFQB/Tmq7fWZV4iAmJcs3KuV8Tqtr0+zwLC/4xhC3S/GYz
         15tg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0c1+bR9T+IplOpKDV6RvsAZ3ZFdVzQUrH0NfTUm42po=;
        b=BLSdHI8akYC8q5YCVjtTqWJGwnehT96D0oZOHMeZzN0wH4e7poJ/QnObzxBxRkge1j
         nf21gViwA6SX+3/KfTQVdRmTpSziqJrspRsZalt5XddDOV88HpKwQi5ujevwzVcCuh1Q
         /AaPhSxwdTz9oM6QoRnB1hpLXGd2KX628PFgww8WHowt9hXLWb+lgd7DGSAfvUM8NbQl
         MQScHQOSUsdH5hQ0BlZyyt143s3844xSx1e6+8kgCX+iHA3i6lZ+uivRUuoDI5WFr/xP
         Mb0sPaOSL5yUGXe6wz91XKy+6zUySR9SiW2x+JlxAGmnEwbDLiuGXIFhg1+vOunDALse
         QDaw==
X-Gm-Message-State: AOAM533y2JNXrFIL5y4WGobQ33aaCgW/CJgr+JIyc3SgBf7tE5jFJxNU
        KzEzIpJuEEBH+onrFYMBKZPdrM8+XQ5CYw==
X-Google-Smtp-Source: 
 ABdhPJxZ2KNY34o2P1qMFC7JpDPTt0TXSskEiJdDyPhiBdzaOQAT1QkjlkGegDZ4uxVw2/hcjVZqkQ==
X-Received: by 2002:a17:906:fca:: with SMTP id
 c10mr4346402ejk.128.1603979763889;
        Thu, 29 Oct 2020 06:56:03 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 j20sm1591453edt.4.2020.10.29.06.56.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Oct 2020 06:56:03 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM/VMX/SVM: Move kvm_machine_check function to x86.h
Date: Thu, 29 Oct 2020 14:56:00 +0100
Message-Id: <20201029135600.122392-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move kvm_machine_check to x86.h to avoid two exact copies
of the same function in kvm.c and svm.c.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/svm.c | 20 --------------------
 arch/x86/kvm/vmx/vmx.c | 20 --------------------
 arch/x86/kvm/x86.h     | 20 ++++++++++++++++++++
 3 files changed, 20 insertions(+), 40 deletions(-)

```
#### [PATCH] KVM/VMX: Use TEST %REG,%REG instead of CMP $0,%REG in vmenter.S
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11866489
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 680C7C4363A
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 14:05:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F01DD2076B
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 14:05:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="NUtVMLv4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725848AbgJ2OFF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 10:05:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33128 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725710AbgJ2OFE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 10:05:04 -0400
Received: from mail-ed1-x541.google.com (mail-ed1-x541.google.com
 [IPv6:2a00:1450:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 247A0C0613D3
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 07:05:04 -0700 (PDT)
Received: by mail-ed1-x541.google.com with SMTP id l24so3140840edj.8
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 07:05:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/zaI+f/txWOZ0xKOmo7GdxyYlTLY1JVfc3R7UeR/0Es=;
        b=NUtVMLv4Bw7ze5Ck+7us9te0gtcg1z4NRTZNEWPgyk/T2jMCyV9AUI9YICZITwZxxa
         DZCM/DQum2kGGYx33N9OA3m5cVXOLukr9kIsetNG3I5duYRuOsXVHkooHjCQMQMZpb6S
         QPkgTI8WqqSJEU4Oit1abBpgv4Sp700qQd0df/zuLN2VL4wEOhIOZPe/8M0FduGQlHJA
         Yu3D7Fhke592NYsAxHlsKNDyFMaQVNrEdMcw/PCVr5fmMMt79nBeW47sixhNSgCZ335A
         9KLETq/nTN9Z6AiBWV0D80IjXDkubykVmZXT2+t/GcpMu81ANSQN3i0MnbLrdaHn4bVl
         MZ+g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/zaI+f/txWOZ0xKOmo7GdxyYlTLY1JVfc3R7UeR/0Es=;
        b=btWhCh14fq2nkK8WUPXXF30WsJ47G4V0qALoY7ze+C2ffa/rBvBkGhac/GEeeHucr9
         qENMBrfpryhMpai8FOMwq2u4EsQ6fYiJRPTD+QcZpyrlplbDEu/KWBmpkPu4fHP5nRVl
         37Gp2FSZEHP593uhjmB7euJlxPDh8L0NLU+4efCZRoejdPkeSPBrRJQ+PCOToZxR1iSh
         swJY+y9SvVoblLVdpTOIbLkK19PJI/jk+uB8YXGsdP/xqr39jTIU8Ow1uHNLM8DS0/Ld
         9xOp5zWD4geP2gGcWPo7rcTuiP6fCBOfb7Jt4i+KQu/N/a7tNguh1co9yubk4ww6f+5/
         PLJQ==
X-Gm-Message-State: AOAM533ZY7C5JN6vTuFetD36Je/FZgp0HcGDqeepzCOCgQxeld0FEBj/
        Lh5815xC9y9nQB5BSgyCrg9OKmxviCZ2eQ==
X-Google-Smtp-Source: 
 ABdhPJxwb7oKIvHT9vRy1RoHHsA6AkMv8uH5TUVNJM0gxmq1bUNDVbeL243iCPUrY6wPUDId2h7F8g==
X-Received: by 2002:a05:6402:207c:: with SMTP id
 bd28mr4016747edb.316.1603980302527;
        Thu, 29 Oct 2020 07:05:02 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 u23sm1531809ejy.87.2020.10.29.07.05.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Oct 2020 07:05:01 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM/VMX: Use TEST %REG,%REG instead of CMP $0,%REG in
 vmenter.S
Date: Thu, 29 Oct 2020 15:04:57 +0100
Message-Id: <20201029140457.126965-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Saves one byte in __vmx_vcpu_run for the same functionality.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmenter.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: x86: Sink cpuid update into vendor-specific set_cr4 functions
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11866895
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3E676C4363A
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:07:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56BB82087E
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:07:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="t20WR8sb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727344AbgJ2RHB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 13:07:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727324AbgJ2RHB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 13:07:01 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D4004C0613CF
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:07:00 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id x9so2485761pll.2
        for <kvm@vger.kernel.org>; Thu, 29 Oct 2020 10:07:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=3KRaFeCn8cu3srAmF4IqkMbqw53L1XtWTUY3QLwzm8A=;
        b=t20WR8sbbc0t+hHqP0qvWHo0kcugXLSSIbgMij7zHAdObBFxCOrZS7wMjsh8SjzAEb
         A5Ao8fR9DuTUL535/I7Ze9/amqAJnrRqT0oNP7yhcvA9ZIpgAHlu0JSBHiGs1lxRc7xL
         Ces2Br8g37lUCaoPk+V4hDXhkvEYBdn3mju0c/Nvw2eB9KeSRrC/ZwA84JLLXw8/JFSn
         LemE+nsNBMndPGfuBfcFJ4XjWnXVbRQou2ckzZiceJhOgCyjfBvT3QVWh42sOHsdmBmR
         Dgucjd1lGPxCppc1ANudQMSLcBRFXzogAEprxJwJQ4Wb9nCDwaxzY52tDUUSOZX7Q2dc
         g06A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=3KRaFeCn8cu3srAmF4IqkMbqw53L1XtWTUY3QLwzm8A=;
        b=MCDXOrxskRbNb1ZFkWIt87TSza/8ZwKgNSPPtY62wHSJcgfYd5LsycCYQna07SFi3u
         N4CN6uRQ9qz8Jgh5FbN3pIi4OXqaTNhnZI3rmLZYaAjF27CV3N4p62q2GEKr5HUfWbHj
         7q1zhJD4ccMLpfMQ0ExGN/HyEVsbbekehqen8Fq5AVDWVd4h9IPQHLSl6LJt9SAJIXKx
         jbSqd6IvGmE6WrktrjT8ogR37H5/429iusX6Pxx+ykJD2Ra83U2ZPHxLbJQH/gUXElNC
         D9Xd7qBh00Af1UbcDJWkXVlcNifp7k6/AgofP/5rKGwGeZz1p7YYBSGUdebqsZMolnGR
         rlGA==
X-Gm-Message-State: AOAM5301hXZB4z+Esig7YJ/MMGB/OQNgPmXu4A40GL3ogZJR7QtsVTYW
        F6yCaLGsJgBjxlvzo8NgqbMvPBc8xEgsGYNep0XTlRBzop7oTgGZqr8k4fU3UZTJneaX6anLon0
        K1GiMPGCWrBp8y9A0sshEVwc6EGZFVpYQmuDo9Ik8OOrPhiSuFpCSZD09ZPFKxHA=
X-Google-Smtp-Source: 
 ABdhPJzdyBN0vZRnYTUtU26tvuqbi86yZG9jcd8CaZWXaoCe2HyeE+Po353hIfl1Zu2xtw1wBwUAIToKGay+Ww==
Sender: "jmattson via sendgmr" <jmattson@turtle.sea.corp.google.com>
X-Received: from turtle.sea.corp.google.com
 ([2620:15c:100:202:725a:fff:fe43:64b1])
 (user=jmattson job=sendgmr) by 2002:a17:90a:3fcb:: with SMTP id
 u11mr735876pjm.128.1603991220167; Thu, 29 Oct 2020 10:07:00 -0700 (PDT)
Date: Thu, 29 Oct 2020 10:06:48 -0700
Message-Id: <20201029170648.483210-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [PATCH] kvm: x86: Sink cpuid update into vendor-specific set_cr4
 functions
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Abhiroop Dabral <adabral@paloaltonetworks.com>,
        Ricardo Koller <ricarkol@google.com>,
        Peter Shier <pshier@google.com>,
        Haozhong Zhang <haozhong.zhang@intel.com>,
        Dexuan Cui <dexuan.cui@intel.com>,
        Huaitong Han <huaitong.han@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On emulated VM-entry and VM-exit, update the CPUID bits that reflect
CR4.OSXSAVE and CR4.PKE.

This fixes a bug where the CPUID bits could continue to reflect L2 CR4
values after emulated VM-exit to L1. It also fixes a related bug where
the CPUID bits could continue to reflect L1 CR4 values after emulated
VM-entry to L2. The latter bug is mainly relevant to SVM, wherein
CPUID is not a required intercept. However, it could also be relevant
to VMX, because the code to conditionally update these CPUID bits
assumes that the guest CPUID and the guest CR4 are always in sync.

Fixes: 8eb3f87d903168 ("KVM: nVMX: fix guest CR4 loading when emulating L2 to L1 exit")
Fixes: 2acf923e38fb6a ("KVM: VMX: Enable XSAVE/XRSTOR for guest")
Fixes: b9baba86148904 ("KVM, pkeys: expose CPUID/CR4 to guest")
Reported-by: Abhiroop Dabral <adabral@paloaltonetworks.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Cc: Haozhong Zhang <haozhong.zhang@intel.com>
Cc: Dexuan Cui <dexuan.cui@intel.com>
Cc: Huaitong Han <huaitong.han@intel.com>
---
 arch/x86/kvm/cpuid.c   | 1 +
 arch/x86/kvm/svm/svm.c | 4 ++++
 arch/x86/kvm/vmx/vmx.c | 5 +++++
 arch/x86/kvm/x86.c     | 8 --------
 4 files changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH] vhost/vsock: add IOTLB API support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11867087
Return-Path: <SRS0=4CpW=EE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62442C55179
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:44:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 04D1C2076E
	for <kvm@archiver.kernel.org>; Thu, 29 Oct 2020 17:44:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z44pUfL3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728158AbgJ2RoL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 13:44:11 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:54441 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728117AbgJ2RoK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Oct 2020 13:44:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603993447;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Pjo8YSkHLXchtWdVeTir70/vnoiG4H+b+MtOTmowgww=;
        b=Z44pUfL3+jB0wPDatCtuD+MKl4niDOEH0dK+ow0bu5LlhBrL6y1/dxYyy9f1/PteQ6BCUG
        wEaeSZ0zlAuTR9sqk3loudCWV1lKK/3vf5T5kbIJYCVEikwRLaPJyP0vDF2Qu8YqTgc7ty
        sKJgdnjHtDiafS4Xo6gg4tcvLf0AC6Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-277-DsQ1-Sx3MUuz0_woJFWwFw-1; Thu, 29 Oct 2020 13:44:01 -0400
X-MC-Unique: DsQ1-Sx3MUuz0_woJFWwFw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06E401084D76;
        Thu, 29 Oct 2020 17:44:00 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-112-127.ams2.redhat.com
 [10.36.112.127])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 334C25B4B5;
        Thu, 29 Oct 2020 17:43:51 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: mst@redhat.com
Cc: netdev@vger.kernel.org, Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>, kvm@vger.kernel.org,
        Jason Wang <jasowang@redhat.com>,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vhost/vsock: add IOTLB API support
Date: Thu, 29 Oct 2020 18:43:51 +0100
Message-Id: <20201029174351.134173-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch enables the IOTLB API support for vhost-vsock devices,
allowing the userspace to emulate an IOMMU for the guest.

These changes were made following vhost-net, in details this patch:
- exposes VIRTIO_F_ACCESS_PLATFORM feature and inits the iotlb
  device if the feature is acked
- implements VHOST_GET_BACKEND_FEATURES and
  VHOST_SET_BACKEND_FEATURES ioctls
- calls vq_meta_prefetch() before vq processing to prefetch vq
  metadata address in IOTLB
- provides .read_iter, .write_iter, and .poll callbacks for the
  chardev; they are used by the userspace to exchange IOTLB messages

This patch was tested with QEMU and a patch applied [1] to fix a
simple issue:
    $ qemu -M q35,accel=kvm,kernel-irqchip=split \
           -drive file=fedora.qcow2,format=qcow2,if=virtio \
           -device intel-iommu,intremap=on \
           -device vhost-vsock-pci,guest-cid=3,iommu_platform=on

[1] https://lists.gnu.org/archive/html/qemu-devel/2020-10/msg09077.html

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 drivers/vhost/vsock.c | 68 +++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 65 insertions(+), 3 deletions(-)

```
