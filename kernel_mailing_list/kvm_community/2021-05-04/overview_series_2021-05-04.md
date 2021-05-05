#### [PATCH] docs: vfio: fix typo
##### From: Alyssa Ross <hi@alyssa.is>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alyssa Ross <hi@alyssa.is>
X-Patchwork-Id: 12238567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C18BC433ED
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 21:07:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3042A613DB
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 21:07:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232785AbhEDVIP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 17:08:15 -0400
Received: from out3-smtp.messagingengine.com ([66.111.4.27]:60431 "EHLO
        out3-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231445AbhEDVIO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 May 2021 17:08:14 -0400
Received: from compute2.internal (compute2.nyi.internal [10.202.2.42])
        by mailout.nyi.internal (Postfix) with ESMTP id 5A0635C004F;
        Tue,  4 May 2021 17:07:18 -0400 (EDT)
Received: from mailfrontend2 ([10.202.2.163])
  by compute2.internal (MEProxy); Tue, 04 May 2021 17:07:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=alyssa.is; h=
        from:to:cc:subject:date:message-id:mime-version
        :content-transfer-encoding; s=fm3; bh=iFFbmOLf/h3Zw+C5EIJiz80rZk
        Y5zLat2o7ZrmaK1cc=; b=Q7ej9+PvuQ3oXGi4D+XbGDejqO44VkHTuGljHe2rcw
        bTC6WYqRQFGco289+KoqT0w9hgth/kRImKRV0sAjFaeQXEUlklk7owidPZ/PEmlv
        BkjJXMaFOMY6guEOKslP8wq38cLmfM9nIFT+O395AMC0f+rpv8ApfQBB9VEO6zz+
        ryG66Wme+Q2OmKmtIxO7wQtx21b6fLnISG+RnmXheL2nFJ0glVcDp1ImlpVDIYAK
        aVq0zUL6BTMt/NRIklOVcqJ9ImfSiUfVRR0DrxfHyXQ/M0Mwkr5Dbsf7VBVh+/iH
        mCSLtYb7b/oO6H7qtoXglHjkJyxCGMnxW8bFfa4M2DuQ==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm2; bh=iFFbmOLf/h3Zw+C5E
        IJiz80rZkY5zLat2o7ZrmaK1cc=; b=UkDJwjvkBtiX39fUA295U7alLlZsSepnB
        P8f2YjDyPob6vN84nc+EEP+Wf86LiVlly/S//EATIm9VVeVW+uYgtA/2UuqGIqq9
        5BQogUDMjiZ51uiCdthWVzVygjQxMsECCquaypYP7c7f8YANozLZ5lKkrvaXOeki
        02Vq6U4+6AkhIt3w/H8UeWQJQiUe1pUBQhZxeZF/Gu8udQTm0Ybz5YcQbpjRCFbv
        KUi1P9Jq1pSSe8taqEfGLMRKfcSyAbLZpNOp/6g9nO9rFADFYO03fXu9QpBAAhmu
        FcOiW4RgP0EKWftfp7rzHsomuDgdCNGKB6jQSDYAQp/zoFHY+Vv9g==
X-ME-Sender: <xms:hbeRYJGOI0qrHwYbZyKdmkPSWbNMCwIhxiL8fnCR3-ThPAxCUQzT2w>
    <xme:hbeRYOUV3PaoiANeUGR1CpPDCe0msHlmIeGAAr_vXL81rrQm5hvgUhgcqWcZl6Ebz
    23yKKKYX2z1HnHSfg>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrvdefiedgudehkecutefuodetggdotefrod
    ftvfcurfhrohhfihhlvgemucfhrghsthforghilhdpqfgfvfdpuffrtefokffrpgfnqfgh
    necuuegrihhlohhuthemuceftddtnecusecvtfgvtghiphhivghnthhsucdlqddutddtmd
    enucfjughrpefhvffufffkofgggfestdekredtredttdenucfhrhhomheptehlhihsshgr
    ucftohhsshcuoehhihesrghlhihsshgrrdhisheqnecuggftrfgrthhtvghrnhephedvff
    fghfetieejgfetfedtgffhvdehueehvdejudfggefgleejgfelfeevgfefnecukfhppeek
    gedrudekgedrvddviedrkedunecuvehluhhsthgvrhfuihiivgeptdenucfrrghrrghmpe
    hmrghilhhfrhhomhepqhihlhhishhssegvvhgvrdhqhihlihhsshdrnhgvth
X-ME-Proxy: <xmx:hbeRYLJo3ZON7V_Tcgx-5GONWLSVw2t5r5MYqOghosaMrKLK9z7lnw>
    <xmx:hbeRYPHrUAYY9gLWaytsrOFewkDKyp7MQetXuz6Zcs7IyhG1NXmoZQ>
    <xmx:hbeRYPW_3iAQOlrcUMSXtzZs_MrnpWChoFkgGDz6NNJUMZFrb0xmXQ>
    <xmx:hreRYGckJfd9BxlqkY68kPb9ZcKiEWGVmC4KatYDRlIDKkGthInCMw>
Received: from eve.qyliss.net (p54b8e251.dip0.t-ipconnect.de [84.184.226.81])
        by mail.messagingengine.com (Postfix) with ESMTPA;
        Tue,  4 May 2021 17:07:17 -0400 (EDT)
Received: by eve.qyliss.net (Postfix, from userid 1000)
        id B6ADB1122; Tue,  4 May 2021 21:07:15 +0000 (UTC)
From: Alyssa Ross <hi@alyssa.is>
To: Alex Williamson <alex.williamson@redhat.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Subject: [PATCH] docs: vfio: fix typo
Date: Tue,  4 May 2021 21:06:51 +0000
Message-Id: <20210504210651.1316078-1-hi@alyssa.is>
X-Mailer: git-send-email 2.31.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Alyssa Ross <hi@alyssa.is>
---
 Documentation/driver-api/vfio.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: nSVM: always restore the L1's GIF on migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12238163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 810F4C433B4
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 14:40:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56B67613C0
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 14:40:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231526AbhEDOli (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 10:41:38 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31434 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231490AbhEDOla (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 May 2021 10:41:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620139235;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=r9Ktu9if4V7oYPGEWrItYebb+UdxeR5QQrWuE47aGr4=;
        b=BdbLzF69wyeT2hpxY9phusAO0C30W1F3lQh05FjX5V4oVw6axmYe8t8ikXl3jbjLG17EAT
        zsM+9X8UBgmZ1WNsrmLocWiVZhETWyelEUqW3dCHJvWd5yYmbh+oQkKAaDbynqx84KEq2r
        BHiubu+V0ZtmW5PBZXW0lXMhcEoikwM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-447-TwrWjQkAPnWtLzHtGrT70g-1; Tue, 04 May 2021 10:40:31 -0400
X-MC-Unique: TwrWjQkAPnWtLzHtGrT70g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0814D1009606;
        Tue,  4 May 2021 14:40:30 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.193.27])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B8FE25D9F2;
        Tue,  4 May 2021 14:40:23 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org, Cathy Avery <cavery@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/2] KVM: nSVM: always restore the L1's GIF on migration
Date: Tue,  4 May 2021 17:39:35 +0300
Message-Id: <20210504143936.1644378-2-mlevitsk@redhat.com>
In-Reply-To: <20210504143936.1644378-1-mlevitsk@redhat.com>
References: <20210504143936.1644378-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While usually the L1's GIF is set while L2 runs, and usually
migration nested state is loaded after a vCPU reset which
also sets L1's GIF to true, this is not guaranteed.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 01/15] KVM: VMX: Do not adverise RDPID if ENABLE_RDTSCP control is unsupported
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12238341
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12FC9C433ED
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 17:17:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB615613BC
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 17:17:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232082AbhEDRSn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 13:18:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39548 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232048AbhEDRSk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 13:18:40 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 88C7FC061574
        for <kvm@vger.kernel.org>; Tue,  4 May 2021 10:17:45 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 n129-20020a2527870000b02904ed02e1aab5so12566066ybn.21
        for <kvm@vger.kernel.org>; Tue, 04 May 2021 10:17:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=GQeYPNBasLogl534ND9Q7MqGb65bHRch8YH0hNcQgdE=;
        b=Ojd4yjrIuWqLjcbV/Te/47XOZv/fcPnbpUUqoPh30f3y+iIiXxDPItFNyUrNyDYDh9
         0iNgVWksjbSECQHZUKcdEhJPFncNrqDVrdGJwBXHUia2e34lFnP5Ip4hsPAmdJvd+RA+
         2i9yloFDGIZVo10i5Pp3hn/Z7G8jh/W6zNmh3+bco+SFOrOYqegQ3BQirXlgUSWXaW+X
         KitiQ0UW+swuGRkFbepxHXx2yzzXEaGvPsnRuUKF/cZqVWvSVD+ezisiIXbDPLDLVDjB
         r0t5vcEHZhRSGqZJja1qf7r11kzkptlCj6VgLav0iBk8LHrDVhmu54dicOvxlqKCstL5
         /Vfw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=GQeYPNBasLogl534ND9Q7MqGb65bHRch8YH0hNcQgdE=;
        b=JdQk4Oz1itdNfI36NJXoYVWRvL2HywpUjKaipFHdWvGnwFIfTnJztnI/jjeAgYlGNE
         cSRSqcnElxcfp+Z3MU5wonRh1MXf6StIsyU0qmFmgjkyU7mtAg4YRo4Tvd5LCxDz0D+R
         e1s7LbdFhqIbaKopwdaEeOq2lJEC/7HfJf26eqWEdFFoN7qZ4R/6PRBGvdjQ26gZpNBD
         xXtz38n6DoUt7M4OiRhfrLcetZ8ycHMGJPvt16bTAWTlZFNnrACImKhn7t+YMjSJnVC3
         iW+VCfA2+hAiWYwDynFBQPg8GoDXvlNNICATmolrROl04sh8yQU8m3LLaR7mlyEXVo5Y
         HH0w==
X-Gm-Message-State: AOAM53153Q0RWdWOVfCQF6V17uwB4sFaSUEIao+P5iQX3t8pZyJsxMGL
        WfFXLMvGPDih92xwnWKUrPKAklddk0Q=
X-Google-Smtp-Source: 
 ABdhPJxlSOlcX5fvKMS9Z8Y/32xdFNS3BueN6Hhz6HUJ3ejXJluoaat8wBgsB528Ps/FO0WpSewliWx1IYg=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:df57:48cb:ea33:a156])
 (user=seanjc job=sendgmr) by 2002:a5b:c52:: with SMTP id
 d18mr34112608ybr.401.1620148664836;
 Tue, 04 May 2021 10:17:44 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  4 May 2021 10:17:20 -0700
In-Reply-To: <20210504171734.1434054-1-seanjc@google.com>
Message-Id: <20210504171734.1434054-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210504171734.1434054-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH 01/15] KVM: VMX: Do not adverise RDPID if ENABLE_RDTSCP
 control is unsupported
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>,
        Reiji Watanabe <reijiw@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clear KVM's RDPID capability if the ENABLE_RDTSCP secondary exec control is
unsupported.  Despite being enumerated in a separate CPUID flag, RDPID is
bundled under the same VMCS control as RDTSCP and will #UD in VMX non-root
if ENABLE_RDTSCP is not enabled.

Fixes: 41cd02c6f7f6 ("kvm: x86: Expose RDPID in KVM_GET_SUPPORTED_CPUID")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v7 1/1] qapi: introduce 'query-cpu-model-cpuid' action
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12238019
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 172BAC433B4
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 12:26:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4C38613B4
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 12:26:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230346AbhEDM1w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 08:27:52 -0400
Received: from mail-db8eur05on2133.outbound.protection.outlook.com
 ([40.107.20.133]:27872
        "EHLO EUR05-DB8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230335AbhEDM1v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 08:27:51 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Z7+BD5wdiOZqrbp6UFcM//sdMozu9RvKvgO+g5Y4G0QdheAPKqsZ8MFeqY0wKA613ODhhyI4GK3uzCXOVKvNv/855padBUpYZL588Ydy9TmG+pSFZtDYBp1OoltiUwzC1UzZfIW9liyJovLI0RWhRQ+W/XRvNapNg/On7yX/GwDizLru9DDKWnCoq79Z/+0WT4u5X255tTLHVu/J5zNQhQEeIh3cb5m3GpwYcp2VLYwkbRJqgJHWdk+Dqz+HlcnnjeWXw9g47mZPWyNdR8rVZSEB8LYsJgKZlKGXqJ5c/oztUdvBfzLmMd4tZav6pt7Wj3Oysdk3eXDAiWkxxd4o6Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xyKdb9RB858dBu3Xc9FpJzvVe1/Dzs41jGTz3K/xyS0=;
 b=Grzm25ehsaLxu8atVy1UvCB43kOVET+prCvAAr9D0YkhwGgEXloG08DJ7PNe8p6jqlsOlk5b0FQ4bVsEEikARKcJAVY4ncw2pEvnFgwVyoPplW9U+zOrEn2mOxJbMyLrAm/7h8bPyQT1N4HEz3OLz+x0akDdEdPMVIhLYNQoN8Mc4rYpP+GHY4nOSL+YVhj2XopvtmzAnBMncdRmGAD9ZULK6yesvjjtT/2J54Ubd+RDMVV/kqrJhylmhjv660e+mo0XMsCyoJUQ/EWKNbuj0HGqJtvkqpaNNkHX9klIbggQfsuIq66hJ9FyybHPsvbrapBbDCA2WkS2DEN9ZWhEhw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xyKdb9RB858dBu3Xc9FpJzvVe1/Dzs41jGTz3K/xyS0=;
 b=JsQ2Jru5l37fWetc0+CQ2g7caRk0q71OvvLF+fX9FAHFvk2o6dPhXq0a0P6DqHF/Bd90LEBfmLSq8HBkzImd3X8eeAsk3T3cvbppwfTw/yci/ljLArzyAzrwoP9AclxfrSOY8iWGRdg/sXmP1kjRntwmIRx5Sp9KP6p4Udq0XVU=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM0PR08MB3860.eurprd08.prod.outlook.com (2603:10a6:208:10b::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.40; Tue, 4 May
 2021 12:26:55 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4087.044; Tue, 4 May 2021
 12:26:55 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: qemu-devel@nongnu.org
Cc: Eduardo Habkost <ehabkost@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Eric Blake <eblake@redhat.com>,
        Markus Armbruster <armbru@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Richard Henderson <richard.henderson@linaro.org>,
        Thomas Huth <thuth@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>, kvm@vger.kernel.org,
        Denis Lunev <den@openvz.org>,
        Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>,
        Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
Subject: [PATCH v7 1/1] qapi: introduce 'query-cpu-model-cpuid' action
Date: Tue,  4 May 2021 15:26:39 +0300
Message-Id: <20210504122639.18342-2-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210504122639.18342-1-valeriy.vdovin@virtuozzo.com>
References: <20210504122639.18342-1-valeriy.vdovin@virtuozzo.com>
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM0P190CA0027.EURP190.PROD.OUTLOOK.COM
 (2603:10a6:208:190::37) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM0P190CA0027.EURP190.PROD.OUTLOOK.COM (2603:10a6:208:190::37) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.24 via Frontend
 Transport; Tue, 4 May 2021 12:26:54 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: d66b66f9-f320-4fd0-33fa-08d90ef7e737
X-MS-TrafficTypeDiagnostic: AM0PR08MB3860:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM0PR08MB38608F5F3BEF81EF4D5DD1AF875A9@AM0PR08MB3860.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 V6sWe/01D1LKwLICbOxscjcLwEkQBaA6jLlavQ6oHUvuz3BIS4mzZc2xxNgx5/It1ZTbtJDb6TWNmNZju8N8k5+eIkGW6xEUqoMCfy4NIv5gQNuYq4KHB7/tDZlyxkwy59dZ2KRnzZ8AC20Gsi7y3WHOlE4hatu2PUXuhU2gv86zfk5vy45nE/bMioH1Rzpuh2NqNKfyQSO24BW27jb7qj92yL0KxcdhpTs9o/3jh7Ct761JtPcl+W26KC1fBg/yKb8CaRNA+5KAy2lVZYeCfy2ePuzM0/eavxsn7/VD6YWEt2aFiN087G0TF7jYvMsmGLkVI+mrWGt4R9DLNRS8hDuVoqwxMuHmLrd746Nq/tOoMuTV+QMG2jhjmV/eTEhDPRlexg4yJTpj/+HiRLuI+GyF8dRE1PQTRN/hk4dU6omFefeNANGSL7OO3W5DdpTvtrf3/iyQXzmRcNJ09+ZgG7M5Z2tvcpsyvvM4RtpcR1LXRIRQZPwo3hE51jsOTuue/lL4QsqeS2KdL3rRVCpPZlnxqaDha7kZ4UwgKppp11EMBtQXsq6mk9S35sleJZw6cFio5zACMb7bGq1BE8u0LkVIT8JTkbqFFwrYpxyq/jt4qt/ztYIfL8wG+u0KfV8Fyu2vwGItJwjdANBD8/FFcuNTrIiAroXZmxnedb9TlDcG9i7cQTRG9WRfZP0nHE5X
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(346002)(136003)(396003)(39830400003)(366004)(186003)(26005)(16526019)(36756003)(6916009)(7416002)(956004)(8676002)(6486002)(6512007)(8936002)(1076003)(5660300002)(6666004)(2616005)(44832011)(66476007)(66556008)(86362001)(38100700002)(52116002)(6506007)(54906003)(38350700002)(2906002)(83380400001)(107886003)(478600001)(316002)(4326008)(66946007)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 nql+L/2h0aSoDyJlAkggTdQa+phCZQNpZBjJ8NkP2pSLWHvKiplEsd/v9InoK6ZZTm/t7SiyzwdBiHXmniMeoLHxQ/rBRFkuh24O1+nVsW+vAQU9hboFC8uWR9wrbOdiJg7fiN+mlhkSv+OQ/KmL+CNAu66bnnPqf58hFIAieVTXBZSJkLDzO5zW4vHS/yW6M0KzKsaBcOC2i2EgIqmcw8MxIHpdpgPyRUpoNi++PbbAOvAIUf+S1CfxF7+OZ/m2anMaSjGFl77lbl8MCsEC7478kVb7uaxzaz2yLMC+Ld6y9HikDoU5ZQLu3LfVAxxq5dTzY+zoiCQdgkTUCS5PUp33PkQfxDrxqchfqg9geFNJdG4XKwVUwGp2R+yJCTXmKLxq3m0hhcv2ozej5wVOuQPY5AvOThPZuNUAte+SarCfmCo1C7wXdfky3hKuWRdYJRySuLXAkwiSOwR9F8EF33KHHlS8Ccfn/VPAfBlpX1QW+9Pd94Ix+tcK//rVz5yr17jS+U8X73Hz7EeYU5iUVR39H84HN2KEll4ldLtrTlPiWmkHu+im285/Xd6ER6d9us6c4bRNf/OmocVi+ss1QxCMd1LSM2auw677+51UOtFpdOAuNNlrAzJ7R71+HMM2Sn+Kw0ecngM5B01+cAKPiAvdOGtzUa5KRD4kskv3X/XFRusYlnYS5Mty9PAChoFr2uDH/2TuPU1hLFIHpheIeELBHhm7NviwbKNttZwyGdjooIoFo2iKQD1JJXUdk31lUpzQrI7DUFWQb+tzlXI8BcF7zeraZbXIJufjBPQt0SElFPKled312OgMAnaqj8pvCanP/gMJgfZfMETPrtwkfzrZotQcVITkSdkKMWwIJp3/bLbACU2rS8qXhd6WEpsQYTylfeQ86N7Dg6YCwV0VZrWjisP9/M30nD/H4ifPc4b9JU4dYnOKB3paHpvKefpI7oI07TbWGoKJvv52Z94bohKeI1ECjzAZpDh57C1W5F2WtNoTJThGIlXIzy3Q55plNX4nz9mweAw3HXs3kJ3OY7U5W8ZQzjPEk6n6ZhsT5DDD91hsHLfCkWMWowfb0rXqlnCEKzWZ1UB4LHGcEXf1bABPFaagyQH3zyflLJqwuKQdTiqBB0FoZy2lqbd5R1nOsqeLcVdOkvmTFlLqCMbjSCKjgPSE3W/esZFNkC2Fp2hT5iFUCYKkWsEZwJiT6jBhpQkgcPyFyDKAhhc4bGMU1wEwrbXKTaAKEQITQ6SGEz8x2tj2ND7PoLUEFMtZ7QcFjr53/CRCaMW25JF1r4R49TYZs4aqgdcXrQfzRcSWL/gDuH3AxhtCHXgEF7wiUgq4
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d66b66f9-f320-4fd0-33fa-08d90ef7e737
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 May 2021 12:26:54.9805
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 uUI7zdmxIXx31OIbiIQFYn+oeE+CtNPsnZ+3O7munxlFVmt0uEzSvxxrMgAYnnrF2zddNRgexaZE5XaulGBfUa7tYHhG20JrOm7jxw0Nsf0=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM0PR08MB3860
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introducing new qapi method 'query-cpu-model-cpuid'. This method can be used to
get virtualized cpu model info generated by QEMU during VM initialization in
the form of cpuid representation.

Diving into more details about virtual cpu generation: QEMU first parses '-cpu'
command line option. From there it takes the name of the model as the basis for
feature set of the new virtual cpu. After that it uses trailing '-cpu' options,
that state if additional cpu features should be present on the virtual cpu or
excluded from it (tokens '+'/'-' or '=on'/'=off').
After that QEMU checks if the host's cpu can actually support the derived
feature set and applies host limitations to it.
After this initialization procedure, virtual cpu has it's model and
vendor names, and a working feature set and is ready for identification
instructions such as CPUID.

Currently full output for this method is only supported for x86 cpus.

To learn exactly how virtual cpu is presented to the guest machine via CPUID
instruction, new qapi method can be used. By calling 'query-cpu-model-cpuid'
method, one can get a full listing of all CPUID leafs with subleafs which are
supported by the initialized virtual cpu.

Other than debug, the method is useful in cases when we would like to
utilize QEMU's virtual cpu initialization routines and put the retrieved
values into kernel CPUID overriding mechanics for more precise control
over how various processes perceive its underlying hardware with
container processes as a good example.

Output format:
The output is a plain list of leaf/subleaf agrument combinations, that
return 4 words in registers EAX, EBX, ECX, EDX.

Use example:
qmp_request: {
  "execute": "query-cpu-model-cpuid"
}

qmp_response: [
  {
    "eax": 1073741825,
    "edx": 77,
    "leaf": 1073741824,
    "ecx": 1447775574,
    "ebx": 1263359563,
    "subleaf": 0
  },
  {
    "eax": 16777339,
    "edx": 0,
    "leaf": 1073741825,
    "ecx": 0,
    "ebx": 0,
    "subleaf": 0
  },
  {
    "eax": 13,
    "edx": 1231384169,
    "leaf": 0,
    "ecx": 1818588270,
    "ebx": 1970169159,
    "subleaf": 0
  },
  {
    "eax": 198354,
    "edx": 126614527,
  ....

Signed-off-by: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
---
v2: - Removed leaf/subleaf iterators.
    - Modified cpu_x86_cpuid to return false in cases when count is
      greater than supported subleaves.
v3: - Fixed structure name coding style.
    - Added more comments
    - Ensured buildability for non-x86 targets.
v4: - Fixed cpu_x86_cpuid return value logic and handling of 0xA leaf.
    - Fixed comments.
    - Removed target check in qmp_query_cpu_model_cpuid.
v5: - Added error handling code in qmp_query_cpu_model_cpuid
v6: - Fixed error handling code. Added method to query_error_class
v7: - Changed implementation in favor of cached cpuid_data for
KVM_SET_CPUID2
 qapi/machine-target.json   | 51 ++++++++++++++++++++++++++++++++++++++
 target/i386/kvm/kvm.c      | 45 ++++++++++++++++++++++++++++++---
 tests/qtest/qmp-cmd-test.c |  1 +
 3 files changed, 93 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: x86: Hoist input checks in kvm_add_msr_filter()
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12237571
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F23ABC433ED
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 08:26:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6C2F613BA
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 08:26:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230103AbhEDI1k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 04:27:40 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:21893 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229875AbhEDI1j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 04:27:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1620116805; x=1651652805;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=31dOGfcg2GObswIUd+iAQCyOWXV3Asmut6GnIm4jpIg=;
  b=O1UXWtmUAQWlo8bueA+5YyzToydGDmoenp0mpVcoHs0RM8eiAT8HVJQU
   z1w9U08H6YdnSlwfRCHsxWrCNUHHbipUEjcR4nQgyELi8jqgZ61qLO0Dr
   uweln/w4LEPSmUBwbu/ivrmpp/KUw/tzlpiu7uZdmWx043e8mb1uM0JQp
   0=;
X-IronPort-AV: E=Sophos;i="5.82,271,1613433600";
   d="scan'208";a="132862651"
Received: from pdx4-co-svc-p1-lb2-vlan2.amazon.com (HELO
 email-inbound-relay-2b-baacba05.us-west-2.amazon.com) ([10.25.36.210])
  by smtp-border-fw-9102.sea19.amazon.com with ESMTP;
 04 May 2021 08:26:27 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan2.pdx.amazon.com [10.236.137.194])
        by email-inbound-relay-2b-baacba05.us-west-2.amazon.com (Postfix) with
 ESMTPS id 34731A1CDB;
        Tue,  4 May 2021 08:26:26 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.85) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 4 May 2021 08:26:20 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH v2] KVM: x86: Hoist input checks in kvm_add_msr_filter()
Date: Tue, 4 May 2021 10:25:59 +0200
Message-ID: <20210504082600.3668-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.85]
X-ClientProxiedBy: EX13D35UWB001.ant.amazon.com (10.43.161.47) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In ioctl KVM_X86_SET_MSR_FILTER, input from user space is validated
after a memdup_user(). For invalid inputs we'd memdup and then call
kfree unnecessarily. Hoist input validation to avoid kfree altogether.

Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
---
 arch/x86/kvm/x86.c | 26 +++++++-------------------
 1 file changed, 7 insertions(+), 19 deletions(-)

```
#### [PATCH] vfio/pci: Revert nvlink removal uAPI breakageFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12238211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 394FFC433ED
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 15:52:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0BF7660241
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 15:52:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231502AbhEDPxP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 11:53:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:28830 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231396AbhEDPxK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 May 2021 11:53:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620143535;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=+a+ZchBSphuAXQvcuIUOn9Rh82lP2Y2KDctoB7uZ/q8=;
        b=iIwrKLcvqi4UuU2BSzWG5/Zjb42BQEjXGjh/tkqLH47/pCQt708Op/ZbijuE2PhISECEmi
        fnJjy7mcOuWyL4SNkSoBbwzThc2I+t/jX0FowURqZIjuTFyAHPSYNenxAE3G10zcCUn9IN
        VXXQUaclyMauCUxogpp24l/aPLEtM+g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-406-NU7xVnh-M1OmVkmm_ha7eA-1; Tue, 04 May 2021 11:52:11 -0400
X-MC-Unique: NU7xVnh-M1OmVkmm_ha7eA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0CD041074640;
        Tue,  4 May 2021 15:52:10 +0000 (UTC)
Received: from [172.30.42.188] (ovpn-113-225.phx2.redhat.com [10.3.113.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0064C60C0F;
        Tue,  4 May 2021 15:52:02 +0000 (UTC)
Subject: [PATCH] vfio/pci: Revert nvlink removal uAPI breakage
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org, groug@kaod.org, hch@lst.de,
        gregkh@linuxfoundation.org, daniel@ffwll.ch
Cc: linux-kernel@vger.kernel.org, linux-api@vger.kernel.org,
        qemu-devel@nongnu.org, linuxppc-dev@lists.ozlabs.org,
        qemu-ppc@nongnu.org
Date: Tue, 04 May 2021 09:52:02 -0600
Message-ID: <162014341432.3807030.11054087109120670135.stgit@omen>
User-Agent: StGit/1.0-8-g6af9-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Revert the uAPI changes from the below commit with notice that these
regions and capabilities are no longer provided.

Fixes: b392a1989170 ("vfio/pci: remove vfio_pci_nvlink2")
Reported-by: Greg Kurz <groug@kaod.org>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Greg Kurz <groug@kaod.org>
Tested-by: Greg Kurz <groug@kaod.org>
---

Greg (Kurz), please double check this resolves the issue.  Thanks!

 include/uapi/linux/vfio.h |   46 +++++++++++++++++++++++++++++++++++++++++----
 1 file changed, 42 insertions(+), 4 deletions(-)

```
#### [PATCH] vhost-iotlb: fix vhost_iotlb_del_range() documentation
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12238113
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D42C2C43460
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 13:54:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B78161183
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 13:54:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231358AbhEDNzs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 09:55:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:35596 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231262AbhEDNzs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 May 2021 09:55:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620136493;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=sYJMcb7M+srNSdjRHy6DuLOfiiwc1W8bmdN+X3kOy+Y=;
        b=KfJU34WkDIYRzlOtIbFrUgosQ9coFwRiTSvd6uBwRbkg9nYlgPIgY+imieoQuV5P50Bk1D
        nxrFw2lPx3opjwpg1IMjYYKEjchDUvhkoN4Ygn9X878G+C7iY+GFkc0ZiURP9JdvaiDWjN
        OK9fDCd/hhNsmb3KtpMvk0hpzg9VzA0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-232-TDqT2_DMPJ6x83Hqvy81cg-1; Tue, 04 May 2021 09:54:51 -0400
X-MC-Unique: TDqT2_DMPJ6x83Hqvy81cg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C593107ACCA;
        Tue,  4 May 2021 13:54:50 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-107.ams2.redhat.com
 [10.36.114.107])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3CF7F10016F8;
        Tue,  4 May 2021 13:54:45 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] vhost-iotlb: fix vhost_iotlb_del_range() documentation
Date: Tue,  4 May 2021 15:54:44 +0200
Message-Id: <20210504135444.158716-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Trivial change for the vhost_iotlb_del_range() documentation,
fixing the function name in the comment block.

Discovered with `make C=2 M=drivers/vhost`:
../drivers/vhost/iotlb.c:92: warning: expecting prototype for vring_iotlb_del_range(). Prototype was for vhost_iotlb_del_range() instead

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/iotlb.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
