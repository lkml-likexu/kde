#### [GIT PULL] KVM changes for 5.12-rc7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12190881
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D583C433B4
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 12:12:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 27A3B61107
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 12:12:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231235AbhDHMMv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 08:12:51 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:57758 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229741AbhDHMMu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 8 Apr 2021 08:12:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617883959;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Xu44vmvXtcO0C+M0wE7HV+vWKAd+2q5v3EmKc9PruFU=;
        b=R4puSq5z39PnLAYbYcr45IIrGzxdRImjesL4AlzwDx6gBuBZBWuZzwqg5whKZOJNy3PxRM
        wBSXo1GalaY7WYyXV79pqd6Y+DJrT5MoODBuSEWEJY6D2cGCKw4zwnPZ2xoQJrlYjmTYLo
        h/oTAmgsW8dtyw7v0OKBlfBexggu9JI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-214-cOT3QhC2NvOluW83TzJeYg-1; Thu, 08 Apr 2021 08:12:37 -0400
X-MC-Unique: cOT3QhC2NvOluW83TzJeYg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 998B8107ACC7;
        Thu,  8 Apr 2021 12:12:36 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 469E910013C1;
        Thu,  8 Apr 2021 12:12:36 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for 5.12-rc7
Date: Thu,  8 Apr 2021 08:12:34 -0400
Message-Id: <20210408121234.3895999-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 55626ca9c6909d077eca71bccbe15fef6e5ad917:

  selftests: kvm: Check that TSC page value is small after KVM_SET_CLOCK(0) (2021-04-01 05:14:19 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 315f02c60d9425b38eb8ad7f21b8a35e40db23f9:

  KVM: x86/mmu: preserve pending TLB flush across calls to kvm_tdp_mmu_zap_sp (2021-04-08 07:48:18 -0400)

----------------------------------------------------------------
A lone x86 patch, for a bug found while developing a backport to
stable versions.

----------------------------------------------------------------
Paolo Bonzini (1):
      KVM: x86/mmu: preserve pending TLB flush across calls to kvm_tdp_mmu_zap_sp

 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
#### [PATCH v4 1/4] KVM: x86: Fix a spurious -E2BIG in KVM_GET_EMULATED_CPUID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12190781
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A9FA9C433B4
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 11:43:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FBD061155
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 11:43:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229803AbhDHLnr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 07:43:47 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:30091 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231132AbhDHLnp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 8 Apr 2021 07:43:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617882214;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+OOkthL+koEr5R8pUMKCXf6426WciB8ikuZyFtZRx7o=;
        b=M4wvA6ee4pt6Sc5NuAF2bnwN1ycnBINkKKzl+OiVj08feSbCe3bxLahf8qLHlEXBVMuv3n
        Qru/NwLwbrPB3RK6MF+aQb2k7mUCzYNgMSzGk6Hw8pClEKMcmRu0WKrynzRxNRdV5/Dc9Z
        uwTteNf18kT+9R69QLtwLnbsUOHNRY4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-532-NXKLR0kxOXyBL5yjGG989g-1; Thu, 08 Apr 2021 07:43:32 -0400
X-MC-Unique: NXKLR0kxOXyBL5yjGG989g-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1B3A4801814;
        Thu,  8 Apr 2021 11:43:31 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-155.ams2.redhat.com
 [10.36.113.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A15E05B4A8;
        Thu,  8 Apr 2021 11:43:12 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v4 1/4] KVM: x86: Fix a spurious -E2BIG in
 KVM_GET_EMULATED_CPUID
Date: Thu,  8 Apr 2021 13:43:00 +0200
Message-Id: <20210408114303.30310-2-eesposit@redhat.com>
In-Reply-To: <20210408114303.30310-1-eesposit@redhat.com>
References: <20210408114303.30310-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When retrieving emulated CPUID entries, check for an insufficient array
size if and only if KVM is actually inserting an entry.
If userspace has a priori knowledge of the exact array size,
KVM_GET_EMULATED_CPUID will incorrectly fail due to effectively requiring
an extra, unused entry.

Fixes: 433f4ba19041 ("KVM: x86: fix out-of-bounds write in KVM_GET_EMULATED_CPUID (CVE-2019-19332)")
Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/cpuid.c | 33 ++++++++++++++++-----------------
 1 file changed, 16 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: vmx: add mismatched size in vmcs_check32
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12190219
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F2D16C433ED
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 07:54:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B23E961155
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 07:54:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230470AbhDHHzA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 03:55:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49738 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229623AbhDHHy7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 03:54:59 -0400
Received: from mail-pf1-x430.google.com (mail-pf1-x430.google.com
 [IPv6:2607:f8b0:4864:20::430])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 12A26C061760;
        Thu,  8 Apr 2021 00:54:49 -0700 (PDT)
Received: by mail-pf1-x430.google.com with SMTP id y16so1208531pfc.5;
        Thu, 08 Apr 2021 00:54:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CoS1npLzHqbBGhM1kld5Nqvh9c2M3eNx2lB/qJCxtRg=;
        b=g8mMLsKHXqOfy+etT+ceR1zg7Uac4PbVYYHN0IyHbTXJGvNOgMR60Fszav5yaXR+9N
         QOp6nvRugEqzMhpUlJaqkjQqYIAqpTUpuZ7VSyjL79Y/sxO55LTYbndhu4neak44/TZw
         GOFB5Iyi9hCijyOWHc/WT/OoD+zg37e/+Q6gds6Mj9wGZ/BK5M2z8zMDQdcy0YVf+rla
         oaLwZVsxnp7fpxOTDMYkQD9jjugR0B93O6D1Eajg7wUZRggu+NFrHht0Arj9b48SMXnI
         59Ed2cscQrrqZPVlfcfVdATvvObQfmN8+GcV/KfLIrU5XfGHClbcja0us+G1IH4Y8zAu
         jAdg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CoS1npLzHqbBGhM1kld5Nqvh9c2M3eNx2lB/qJCxtRg=;
        b=ZJdyL5WLVEDuDrIugIZpahlG07jW+EIa7dM2xhLEmdyZ9Ow0K/pB/pjZzDhpjwg185
         JXBDTjvppRJ0sD8tskHf5nd6D30cdX/y85J8cQho2Oa/sgahGsaPNGtk2ZsJBUWt70wm
         n+Huh14D+AMW0zh3Wru46pHiVjMjok5aKTQpc45J0Cr3UK9ypUVLu2zME0Zgm+EG8vdz
         YVO4O0Yu3f6GAEPLeWT+lYgDhDoaMUz9RzTPsRqGTyo1g2t9qhh+CSrmvIYUk9Veewme
         5DByOBfWTOa5n+4PrfzIi/SrerGpRXCQslYCQcNdjBNLqw8AmtBIftFoGyiMF12b1uui
         kvpw==
X-Gm-Message-State: AOAM532EZiU3114kXtZaCOmWDLKA0cZhfSUm45hw+nf1QG0hZXS3wzGM
        oLX1Vb/5ObGQsXK0P7MKdcVG/7Y2sg==
X-Google-Smtp-Source: 
 ABdhPJyL9NiJ1vzRx75BEIMSlr75VDg4PHTVbX/6J1Esa6o3xxp9dTbKUmXRTm5vHVkjXOa/SSTlzg==
X-Received: by 2002:a65:6844:: with SMTP id q4mr7051917pgt.48.1617868488196;
        Thu, 08 Apr 2021 00:54:48 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 x125sm22912637pfd.124.2021.04.08.00.54.45
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 08 Apr 2021 00:54:47 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: vmx: add mismatched size in vmcs_check32
Date: Thu,  8 Apr 2021 15:54:36 +0800
Message-Id: <20210408075436.13829-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

vmcs_check32 misses the check for 64-bit and 64-bit high.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/vmx/vmx_ops.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: X86: Do not yield to self
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12190673
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 79239C433ED
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 11:23:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2393861132
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 11:23:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231221AbhDHLXd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 07:23:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39028 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231150AbhDHLXc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 07:23:32 -0400
Received: from mail-pj1-x1030.google.com (mail-pj1-x1030.google.com
 [IPv6:2607:f8b0:4864:20::1030])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C74F1C061760;
        Thu,  8 Apr 2021 04:23:19 -0700 (PDT)
Received: by mail-pj1-x1030.google.com with SMTP id
 f2-20020a17090a4a82b02900c67bf8dc69so2985007pjh.1;
        Thu, 08 Apr 2021 04:23:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=xN23vtsUui78zFVIDa0Dk7gGB3uEJ15TDF6m5eb0sa4=;
        b=BGgrcLiojG0/5XAY5tjzrhoIggAjsF2yCnAsgSPeqsE8U76tc1oE9CuR0NZuRwoGyv
         UX4xfumImuwq5NGSO2I46/jC2ST+jTj44RJz+k5ROa5vjctjQSeZBt0cjy/cnnxPRhBc
         UERyBONKc2PrIWZzWvlfcj2TBR2QkItdl7XhOl17k+ApxHZ4qteZ536yOjUvD7Y2sTcX
         gpT/SYh6Ol9Gp9BzR/kVNpnIH8UYxz/G3JLOWav1q5EAoJom/pDIJ7PYfIRsFt7Ktkqv
         aOecs3P13VuD8jK/KWkqoRHEzVwhfyiZZLVWFyXhSvMm/UfoXjJoWjvh70LbXp0V8Z+t
         Yc3g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=xN23vtsUui78zFVIDa0Dk7gGB3uEJ15TDF6m5eb0sa4=;
        b=bdqtNJhibSxUm61YzNIQodxxiJ3AWrtvuCIbO9HRamAMlPWSN5AabJ3bmRJivekiyH
         nkQbTj2YHqi5IRrEHy/keJShrV4rv+xSHlEHhhRDl4P8Mx2vuJOv5sZAYxepiRMDMeim
         8pget4yUK+7hZlRi1WWhExJx8hW6EXRcAqE02TFaKnBYG8pkiEVzZHP3GIGCi4BfF6Jj
         vrrk2kFIzDTV9h2uvEjVk4grLkXjqACI2Cm+mvwiuGYsIFNJabG70nBGnZwxFybrtf0o
         kHkahTMQTG4nX2cVApSZMCfXa74s/ilPtjR3jSHWniMv6GAFLGfpNyfGf7FfNRLByHVB
         1X7w==
X-Gm-Message-State: AOAM532BkwcuBM/YXSH4UoxLZ8vjs4FeEol1k9Tu0XsIoUKoz8SQjUJE
        YaKoYUh8BkLL5nIGThHhxa97ot7D4qg=
X-Google-Smtp-Source: 
 ABdhPJzRJVZc05Oz40yXMNEf6v8DsOolGdsV41bBXXPCQWk2d4bJZxJ5JyOJSiDfBMJqLb2HhkY5eA==
X-Received: by 2002:a17:902:e8cf:b029:e7:1db1:e7e4 with SMTP id
 v15-20020a170902e8cfb02900e71db1e7e4mr7237422plg.81.1617880999132;
        Thu, 08 Apr 2021 04:23:19 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 a13sm23961055pgm.43.2021.04.08.04.23.16
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 08 Apr 2021 04:23:18 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Do not yield to self
Date: Thu,  8 Apr 2021 19:23:09 +0800
Message-Id: <1617880989-8019-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

If the target is self we do not need to yield, we can avoid malicious 
guest to play this.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Rebased on https://lore.kernel.org/kvm/1617697935-4158-1-git-send-email-wanpengli@tencent.com/

 arch/x86/kvm/x86.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2 1/3] virtio: update reset callback to return status
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12190229
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4ED3EC433B4
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 08:11:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00B9B61158
	for <kvm@archiver.kernel.org>; Thu,  8 Apr 2021 08:11:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229686AbhDHIL1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 04:11:27 -0400
Received: from mail-eopbgr680076.outbound.protection.outlook.com
 ([40.107.68.76]:27904
        "EHLO NAM04-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229586AbhDHIL1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 04:11:27 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=O46Q38GA48wbDNxDsM99Aek2zg4RN0zkhYolSvUyYp6i4L4JSKTDS2A5UaUSeKYNECnAsywoxDL5bbrr6h/gEl9gOxXhH4hpNV6qtb73b2ZMitI2Ba7iB/PZr9RwmK1L59/wBnxiNlakdmcXLRcYowrd6VayoVFEGRXfAsDROOukue6Tolw5ZaQdOipeOX+6g9Tq6w2jnXZRx3EikQ+swpRcndDP0h/p/fDeFU+EHEoM95ab1X2/DktCqnnHHUxqNIwsGGhqnKOsJu0Oi0MhPOaQV/oiWRl9VGE4XwBy3GSZXQsWNjHHI9duNEdonwMdl/2eqnBTGyxEuPc46EC/kg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=P1mwYaM6JmQW45V9+z7rNmoVf8/o0ooE41rlJ7DO/uU=;
 b=aJmcRjyokVvlyFkoD3JsBYUilVy5wwKkyo95Ljru194np1aH6L2N9YVPi8WwCMz7YBvxbtNLGQsw9lQWP+Ktow+pFvCAj7QqO7abYE1D4WktCPIT5JlD5FYwgLBgROmjbjCpCLbZhxaGxuAMo4CmcjeutEhbfPxGGpy6gL74y7Q6wQ98hssYJ0Q0cmSg10YYRPJjYWpxdp60Hw4WjifmAaFlCcjQUPCQAmd3/Jg8AJikLLspgfqRoiNOYgrb+jM64no0byxe65WLaKo+BEPwYrrUnB3UiXRFdeM2VifuvbWuv6LcYY2nsJHi2sSLvVXsz9ipnkOnD5IV7xcARRgsqQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.32) smtp.rcpttodomain=redhat.com smtp.mailfrom=nvidia.com;
 dmarc=pass (p=none sp=none pct=100) action=none header.from=nvidia.com;
 dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=P1mwYaM6JmQW45V9+z7rNmoVf8/o0ooE41rlJ7DO/uU=;
 b=Bv0uANrlaJy6LlLKrDfmRPQWEnHxA5PG7mCb9sWihhoZmYJy7l9jQ9T4OCdKRe2lmQTZbbcn9ZLnhiSF1YeAMrQbGfwti2fEUtsVRzDsTUpH+2XxlA66nWBO13xkB/rbPwW6oZFDtlcvNgKrUY3sSFa0yCyqAo58ql3b/Tyi5sZd6wBzbIrn3sYn0ZUZdLjF51gw80VZbZCwXYxrTzRCaLWSsWS8wbFUXZr6tjkQrkkXxLJtzzAisIbwkIPxguQZyq4ubAxHVX8ktstwyOBmgWyYGeSgQbK5nnw6ncDLm3TZmm8RqLVJQZyNsXZpdE7o/6elSvKV2mMsBvpybSC6MA==
Received: from BN6PR13CA0027.namprd13.prod.outlook.com (2603:10b6:404:13e::13)
 by BYAPR12MB2949.namprd12.prod.outlook.com (2603:10b6:a03:12f::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.32; Thu, 8 Apr
 2021 08:11:13 +0000
Received: from BN8NAM11FT029.eop-nam11.prod.protection.outlook.com
 (2603:10b6:404:13e:cafe::7a) by BN6PR13CA0027.outlook.office365.com
 (2603:10b6:404:13e::13) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.8 via Frontend
 Transport; Thu, 8 Apr 2021 08:11:13 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.32)
 smtp.mailfrom=nvidia.com; redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=pass action=none header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.32 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.32; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.32) by
 BN8NAM11FT029.mail.protection.outlook.com (10.13.177.68) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4020.17 via Frontend Transport; Thu, 8 Apr 2021 08:11:13 +0000
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Thu, 8 Apr
 2021 01:11:12 -0700
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Thu, 8 Apr 2021 01:11:10 -0700
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <mst@redhat.com>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>, <jasowang@redhat.com>
CC: <oren@nvidia.com>, <nitzanc@nvidia.com>, <cohuck@redhat.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH v2 1/3] virtio: update reset callback to return status
Date: Thu, 8 Apr 2021 08:11:07 +0000
Message-ID: <20210408081109.56537-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: af8c6e37-7640-4fc4-659f-08d8fa65e060
X-MS-TrafficTypeDiagnostic: BYAPR12MB2949:
X-Microsoft-Antispam-PRVS: 
 <BYAPR12MB2949CB171BD35E536D81A345DE749@BYAPR12MB2949.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 H1xl8awJlhTgDxhyIQmAQxvww1gB8EPzN0EARpPt2nQnhDLIaJ2Q1+IcfJxCE42uRpaP6gEiH2qQJeXR0TEd/vZ5/mtYmamMlKtrovCoi6kZigClO1w2msy0BBxlrdcSYSmVfZ+jnFj+8uCy5V6Kl1wI61RQloEkFhH/A5N1SE/LGhf4Di7BohEN4qFYaMVJFB6Ah9AdS8dpo2LgGp3QyNmNqjsx8/mydk75jBDDavWpvDR6V8gXJZerWV6QR4WRsSQzYoEU5VP0svSM34GUGI21qswExHkFu5M98W40UMiubQXBZg5jhYJPvhap6FraCRhdJolb29UbASaMzbhxApfWt17DoplAUEUNB7okmMs1TihgIBhi9yFWlWrzc8ljKS3rtSOKBDBF6sLquuSuBl9FnZJL1VVBfe5PvRAJpyTG+OkkcEyyvErTYJ5IHfEBFAFo37rWUFNkzayVrPNdtp5sBv1WoUG+mlr5wvUjMD88P+V8rH4MO5AWiaY1tnlzHVqmDK+XjZSSL0jkgRwbSClj7+22ksbt+enOhN00KvlGFWLYj7G1XdlLJ1cIIicywmRrLMdVlsAHeIJa1Dcu7iFDeYvQoWnBx3lghj3u7cX8Ull0SMaMh8zkC0VvJ6F+ppNNy+wWNmjFizhJ/jPZx50ax2jhUSVVJs7ifjDUT6c=
X-Forefront-Antispam-Report: 
 CIP:216.228.112.32;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid01.nvidia.com;CAT:NONE;SFS:(4636009)(136003)(396003)(346002)(39860400002)(376002)(36840700001)(46966006)(82740400003)(54906003)(7636003)(36756003)(110136005)(186003)(426003)(336012)(356005)(107886003)(2616005)(4326008)(86362001)(8676002)(6666004)(70586007)(47076005)(8936002)(2906002)(36860700001)(82310400003)(70206006)(1076003)(83380400001)(15650500001)(478600001)(5660300002)(26005)(316002);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 Apr 2021 08:11:13.3471
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 af8c6e37-7640-4fc4-659f-08d8fa65e060
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.32];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 BN8NAM11FT029.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BYAPR12MB2949
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The reset device operation, usually is an operation that might fail from
various reasons. For example, the controller might be in a bad state and
can't answer to any request. Usually, the paravirt SW based virtio
devices always succeed in reset operation but this is not the case for
HW based virtio devices.

This commit is also a preparation for adding a timeout mechanism for
resetting virtio devices.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---

changes from v1:
 - update virtio_ccw.c (Cornelia)
 - update virtio_uml.c
 - update mlxbf-tmfifo.c

---
 arch/um/drivers/virtio_uml.c             |  4 +++-
 drivers/platform/mellanox/mlxbf-tmfifo.c |  4 +++-
 drivers/remoteproc/remoteproc_virtio.c   |  4 +++-
 drivers/s390/virtio/virtio_ccw.c         |  9 ++++++---
 drivers/virtio/virtio.c                  | 22 +++++++++++++++-------
 drivers/virtio/virtio_mmio.c             |  3 ++-
 drivers/virtio/virtio_pci_legacy.c       |  4 +++-
 drivers/virtio/virtio_pci_modern.c       |  3 ++-
 drivers/virtio/virtio_vdpa.c             |  4 +++-
 include/linux/virtio_config.h            |  5 +++--
 10 files changed, 43 insertions(+), 19 deletions(-)

```
