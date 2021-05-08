#### [PATCH 1/6] KVM: arm64: selftests: get-reg-list: Factor out printing
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12245167
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 35DC7C433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 20:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 029C56145A
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 20:04:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230048AbhEGUFb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 16:05:31 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:34632 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230021AbhEGUFa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 16:05:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620417869;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=L5HDSKGvyrRWSdAILh2m5YfuLdjo3ynQDCxiblsihEE=;
        b=Ty6XR4Z8BftjutQvNFjA8up1NCMCEF0X2mutQhJD4Izdilf6rc8FOmZ2vT5S2KEohdMFBT
        66ZWpbNXaDhnv5KJseoncatrapz1n/CD/hKs/2suQtK/4vnTP3dZmuXVgZTeWR1H8gGZ5I
        vsRtCiQKLNxEZOfUyh9DW8pT/CGk6IE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-429-2PappjDtOrORx5A-YqW9jw-1; Fri, 07 May 2021 16:04:28 -0400
X-MC-Unique: 2PappjDtOrORx5A-YqW9jw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CC7AB8014D8;
        Fri,  7 May 2021 20:04:26 +0000 (UTC)
Received: from gator.home (unknown [10.40.192.135])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B964B19D61;
        Fri,  7 May 2021 20:04:24 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, ricarkol@google.com, eric.auger@redhat.com,
        alexandru.elisei@arm.com, pbonzini@redhat.com
Subject: [PATCH 1/6] KVM: arm64: selftests: get-reg-list: Factor out printing
Date: Fri,  7 May 2021 22:04:11 +0200
Message-Id: <20210507200416.198055-2-drjones@redhat.com>
In-Reply-To: <20210507200416.198055-1-drjones@redhat.com>
References: <20210507200416.198055-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A later patch will need the printing to be factored out of the test
code. To factor out the printing we also factor out the reg-list
initialization.

No functional change intended.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 .../selftests/kvm/aarch64/get-reg-list.c      | 62 +++++++++++++------
 1 file changed, 42 insertions(+), 20 deletions(-)

```
#### [PATCH v5 1/2] kvm/arm64: Remove the creation time's mapping of MMIO regions
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12244393
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5056BC433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 11:04:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28B7261464
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 11:04:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234416AbhEGLFt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 07:05:49 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:18790 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232796AbhEGLFq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 07:05:46 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4Fc6wJ5cqlzCqry;
        Fri,  7 May 2021 19:02:08 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Fri, 7 May 2021 19:04:38 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v5 1/2] kvm/arm64: Remove the creation time's mapping of MMIO
 regions
Date: Fri, 7 May 2021 19:03:21 +0800
Message-ID: <20210507110322.23348-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210507110322.23348-1-zhukeqian1@huawei.com>
References: <20210507110322.23348-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MMIO regions may be unmapped for many reasons and can be remapped
by stage2 fault path. Map MMIO regions at creation time becomes a
minor optimization and makes these two mapping path hard to sync.

Remove the mapping code while keep the useful sanity check.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kvm/mmu.c | 38 +++-----------------------------------
 1 file changed, 3 insertions(+), 35 deletions(-)

```
#### [PATCH] KVM: selftests: Print a message if /dev/kvm is missingFrom: David Matlack <dmatlack@google.com>
##### From: David Matlack <dmatlack@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Matlack <dmatlack@google.com>
X-Patchwork-Id: 12245129
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 589D1C433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 19:06:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EC6B60232
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 19:06:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229512AbhEGTHD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 15:07:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33018 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229470AbhEGTHD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 15:07:03 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 14A4EC061574
        for <kvm@vger.kernel.org>; Fri,  7 May 2021 12:06:02 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id
 l35-20020a635b630000b029020f1edbc5dfso5997549pgm.22
        for <kvm@vger.kernel.org>; Fri, 07 May 2021 12:06:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=ZU5o8YBMuCGWkq6Z2zz819KL/+PmcDt40fIKeJxGjYo=;
        b=mNIW3Ba3qaS/89b/hgFwdshzU3o7/8/quvZ/pP+WrBYaIYEVJFc4fpd1Y/2YUPvc0L
         IZkg0PqAUpbAy7bMF1DxpYV1SrfoAUj64PFtAU7DC+/sDZH7KadVjzO4r84CIarfA3gI
         pisNVGWQdIidxi+DdhqGbEiGbYCsPP0A/X41WTiarpx+M28nKSmiGgnosAxwlZkuIQ2R
         Y+Jxu9QvxxDE1pkSDOaY0US3DanOyK98uryPkZrNQBL7b4ZXkl4PcuDtV7+IOGW09tHD
         Eu84Rg8pPPeiDB0h6A9m2HWoUp/EnlKhOVj10YdiQ6PfrLaSj3w98uwtVr02kooZARQo
         KRHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=ZU5o8YBMuCGWkq6Z2zz819KL/+PmcDt40fIKeJxGjYo=;
        b=qkpIKNKlQoD17dL5CHUS1JfsJkTw9Gi9TNYgJrh9zWlX+oSqmVEqvATkGMUcVDBK5G
         yILPSS1r2O73MrYD2U4ZKqfNXcsAtO5/SCeyCqAJMxJpfCOFPERzfk2uoalgZQZkSj4M
         D5Hs2v7ohAo5LZaG01ITYCe7o1rwyAl1+YGa04jXpl1SqdwvtOyXzIqP9OohoHx19/+h
         nTjirGys9/hdp38OnRDCKJbwf46GgIRtaIfGUVGv2tpYyBte9ISWPGwZlu8itlmwP52p
         7zlflLr6PQ9kCxT7gLdVSS3pkWL8NSLW4Mv/wv5z0iNOxpD1XMmGgnpNf1AaQg7+HGdN
         WQ+A==
X-Gm-Message-State: AOAM530Yt10myRPQ2g2dh00ZKs5Qpz89cBrReWIJbbWz4U8mJDVm78ib
        xNIGQrNrY8pHjTb6gdyTj74VquM2O/A7v5Z3tv6hl8hDodpwkdgXo21U9riiAMUWv4ffOOWTFeM
        rtEtB7/ydTTSa6OChxXQn5qaYBUsSWR0kRiZ0hPpeUaNIB+8fwKm3+pYLSO7uL8o=
X-Google-Smtp-Source: 
 ABdhPJzAPMcK3bt+MrIm0zgWis1JF5rwpp/dhzo84blc54eWoxqs2R0wbfUD/wz6Xp2RvQVF9C+PQq3zLGXluw==
X-Received: from dmatlack-heavy.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:19cd])
 (user=dmatlack job=sendgmr) by 2002:aa7:904e:0:b029:28f:da01:1a5f with SMTP
 id n14-20020aa7904e0000b029028fda011a5fmr11556437pfo.67.1620414361458; Fri,
 07 May 2021 12:06:01 -0700 (PDT)
Date: Fri,  7 May 2021 19:05:59 +0000
Message-Id: <20210507190559.425518-1-dmatlack@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH] KVM: selftests: Print a message if /dev/kvm is missing
From: David Matlack <dmatlack@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>,
        David Matlack <dmatlack@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a KVM selftest is run on a machine without /dev/kvm, it will exit
silently. Make it easy to tell what's happening by printing an error
message.

Opportunistically consolidate all codepaths that open /dev/kvm into a
single function so they all print the same message.

This slightly changes the semantics of vm_is_unrestricted_guest() by
changing a TEST_ASSERT() to exit(KSFT_SKIP). However
vm_is_unrestricted_guest() is only called in one place
(x86_64/mmio_warning_test.c) and that is to determine if the test should
be skipped or not.

Signed-off-by: David Matlack <dmatlack@google.com>
---
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 35 +++++++++++--------
 .../selftests/kvm/lib/x86_64/processor.c      | 16 +++------
 .../kvm/x86_64/get_msr_index_features.c       |  8 ++---
 4 files changed, 28 insertions(+), 32 deletions(-)

```
#### [PATCH] KVM: x86: add hint to skip hidden rdpkru under kvm_load_host_xsave_state
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12244951
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.5 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BA8B7C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:46:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75D9461431
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:46:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238383AbhEGQre (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 12:47:34 -0400
Received: from mx0a-002c1b01.pphosted.com ([148.163.151.68]:35754 "EHLO
        mx0a-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236774AbhEGQrd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 12:47:33 -0400
Received: from pps.filterd (m0127840.ppops.net [127.0.0.1])
        by mx0a-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 147GMEHn031757;
        Fri, 7 May 2021 09:45:19 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=0LW5GjAXtRRVZwkKDoHSlJ3Ibe4GdwJsb5u0mA3mWV0=;
 b=mwN18iMEzqASzDA0xnLAlsldc42oKS7Ld+LYtS1A/nfKGWEjcNKZlEcNDT+8kr8S7xm+
 Ix6mY+RGNHcpyQWmAYsrhaEdDzq7Gd8toFmpc5EiFyegAiFf3v/zED/Uk8PCmflfbVzH
 uSnDNPlAyj/JNy5vGEeJCBtKfzsUtTFYHMv2HOqPg6QJLpvf8xsYlOPVqbRjSCn7vB5+
 k/696kiKqoeS0kzuChQbjazDlbZN4jATS/eySQ/oCvUjkC+ROUW5XARUpkhSSAoBv+UX
 thu5C1x+Wazvrz1aGDg6tMHfdZImWAtPhEcJAtEMrsh+D+9xFGuhY3TdHuGn0A7rpaAL rw==
Received: from nam12-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam12lp2176.outbound.protection.outlook.com [104.47.59.176])
        by mx0a-002c1b01.pphosted.com with ESMTP id 38csqr9pap-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 May 2021 09:45:19 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=C7nADrjX04nafDMhhSkWfVxL4HmS8hz4wCnKYTgVd2uohSk3/MCNWJanQHy9oVrQaVOVjizy4HQ3yXLt4x+Hie3u+VdrvmL33g+xMmUC3VMvSqdACupFVzGUdbbu3IkFfscvoPE7w2FmmuEv/K2Xfx3whLc2sM5+HOSZq1YAAf1qPbu6dJDRGfj20cx1aTXK7J6tpduDtzTTwWrvqlz55s1mOH7L8UrAh3kdt4rgDvCBmS4GjFC++PlvbSdMaFzIAXyDfvkWg65lR3kezJCaL2KVqLyC9oM1dNuoORhFL0UJEcSEpg8BvHkQlSRotNeP0KzPm07jbnyxB7QbpUAkWQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=0LW5GjAXtRRVZwkKDoHSlJ3Ibe4GdwJsb5u0mA3mWV0=;
 b=Ld4PFPrDN6FpwDI8RZRe/wlZl6sblg6p3JadkY+ZOrxZ0HucMEXR2o3BS/Q/zB6qdah3SV03fe73mLGoHuBLoaTYJtYaApY/dHCewE5XYo6BDdV0TqjQtesrVPm7MJc0KF5sjkCO8xVX2chh5iKTyn1/zsV9s+GGbJ8NQGLfMyaicc6KPGie07ahe+9AkbqBTX+94Lje7P+XPAcXhnDH/g1q8KBDpF/spMdaR4E/g+EENklLNTumgStZdE+k92uU4EAUAeuci4GW5ZpFZ8DZZVMNHLrRdVb5AffUBDTMC8F9+ESdBSUZn8dsn2vBMCJrfxTa20+CEQTmy0nODJYjng==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by BL3PR02MB7938.namprd02.prod.outlook.com (2603:10b6:208:355::20) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25; Fri, 7 May
 2021 16:45:17 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4108.029; Fri, 7 May 2021
 16:45:17 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>, Babu Moger <babu.moger@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Dave Hansen <dave.hansen@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Yu-cheng Yu <yu-cheng.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Uros Bizjak <ubizjak@gmail.com>,
        Petteri Aimonen <jpa@git.mail.kapsi.fi>,
        Kan Liang <kan.liang@linux.intel.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Mike Rapoport <rppt@kernel.org>,
        Benjamin Thiel <b.thiel@posteo.de>,
        Fan Yang <Fan_Yang@sjtu.edu.cn>,
        Juergen Gross <jgross@suse.com>,
        Dave Jiang <dave.jiang@intel.com>,
        "Peter Zijlstra (Intel)" <peterz@infradead.org>,
        Ricardo Neri <ricardo.neri-calderon@linux.intel.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: add hint to skip hidden rdpkru under
 kvm_load_host_xsave_state
Date: Fri,  7 May 2021 12:44:50 -0400
Message-Id: <20210507164456.1033-1-jon@nutanix.com>
X-Mailer: git-send-email 2.30.1 (Apple Git-130)
X-Originating-IP: [2601:19b:c501:64d0:a9a2:6149:85cc:8a4]
X-ClientProxiedBy: BYAPR01CA0054.prod.exchangelabs.com (2603:10b6:a03:94::31)
 To BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:a9a2:6149:85cc:8a4) by
 BYAPR01CA0054.prod.exchangelabs.com (2603:10b6:a03:94::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Fri, 7 May 2021 16:45:11 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: aa6f606d-cb5f-44f3-3997-08d911777e75
X-MS-TrafficTypeDiagnostic: BL3PR02MB7938:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BL3PR02MB79386FA5DBCCA5DD4A1D7855AF579@BL3PR02MB7938.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 uQED+3U6AIU6irycietPGrJX4f/kdVSaWKJDJMDW88JdcHtuxxNTpZ3v9SfJI0UzCoexqvpLrW9IHH5U8weVEa6vmrujAX43bWJzGeYesSIwAG5nLIBT+sMRHKNvEhgcQJSS82Qgwhcf/n8EFce3xda5gJnz27Bm5jCCFTxxAMMy5PzBSLZFN1NFYqU9kUrzXNwA5EbWTkLIkC1yzHqi5/J+R66bIq6/x13WRlb61d/qwP09QGTeq/3ev784AFN3jXQ7D5KVvAfc+L6JjR9tBdjxyBMpl41YxbcuSyAWrHYyqzEoTCGComN2iWpX7cOSMiQ0tyd7F+p+qZb1eh9xIF9zDxAgDdWwbHruemQhXqOWjlxZITK5wcJ/PfzljkKNyPcbCXqq/JZTJ26fTMNxc0WIRwPuw4cqN2F8hDX1EILXN4EdOz8+1CQaN/0u6/pphBCR6ud/Yn24Cox6gKHOvbietM1CSMiKIvi/B2AT2fdpcjmI1LsMLwOmSSJavEJgq8kwsg1pahZ0NBruSQ5PpKdE20oO4If2CXncmXhG1+TVsKvGoFyBcgEJbIyyO3jIKxOYmy5aNH/C85PwmeZorVTKeS0yvaYQZjTz9kfH7K5ULwOEFp8d4o5Crve1sQf8A2As9bXHDqnBNDjCn5XkDg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(366004)(39860400002)(376002)(346002)(396003)(316002)(54906003)(6486002)(8936002)(8676002)(16526019)(2906002)(6666004)(186003)(83380400001)(36756003)(4326008)(52116002)(86362001)(38100700002)(66476007)(109986005)(66556008)(66946007)(7406005)(1076003)(7696005)(7416002)(2616005)(5660300002)(478600001)(266003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData-ChunkCount: 1
X-MS-Exchange-AntiSpam-MessageData-0: 
 kOwgKbSM4l0UQQvJ6NCAt3aMwfNBc3CSKkzsNUCeOtRdim8ClSfFjEy1tvp/5R8oBcd85eiRCs6IHMr75S8sRwvh0EudLmh642lZ1iDJ9iDjk9vZe7gUk+h/0ETqfMucy6Hh5pRqo8t/AC7EZfXjxQuiTApCjrE3Wov9R0wBxtrL70NBY9gyuBNua130gVUBlzEU6Jfyo6onztr3VNzAed5hDng5VggVN0P00zhfD2TdvgPfdoEZ7i0kIliZ3W105fp4SaiRHdBg/aIQ2pEJuyY0JDMrSmNK2ptG/DX3sZOtKReUWdHhmdRO1IZF+f9Kc7sAgvtV+dbYJi6mvT9hMwW72HtDuD6d4Mc0LNGfyZUG7ZWhghouw3mJMXxekdF9bwH1vTwkAGLXzVADIyv15rnXpv4AKhm/ycVkdVNP8BgTfMLRAaKLEp3yQ07BP78kUrcGNcRYrJK0UDO0MHdw/8jgu75eZy/JVr4mTgouXRdUOn1HbIrnRlEqrqOTptJdZcKsu/sO0YaKwLPyNUsA63nUdCKu2aRE/s6eZwLyI7iTE3QeSfuMgRlF72koqNoIuA4nDubxEpsd9H7FFujpzhwq8pMl0DSAjH4uWuRSYuITwmo5DOzXuiTazQF5bTbv48QY3FNdzPqXjOtGDqk8chEECSM/v7QcSOnUNgasdb5Iux5dHbdkKnMZe+vSp32Z1LjINPQlpbKIQqqzs12Wgb1JA8lrXuUwbPQJ4RGukHrvt92gftbzYPLNvBhliLSbYo/EbM0zXG3d5OnvNCt6pL7cwSLwCP+SdI3ppVbEJ4ReGkfa6VayM5aspaqTWyGPfVX+2sDtZoCX1mYHKTJu6ah969RD3EmjPYaTys6rA4h5heEI1g01SGQ0+jYaZdvJoxsu9orw1Uwewt6CKBLMC1/a/O+Zr6QboeCgb/WirPVUJ91ilbbiNgc6gefiUNM+9peXQ0VFIYE9UjjpjUVjJe5QRZtlsWNruglLmSaw5QD10ow/rgia4m2m8/fNagAgY4EYmKB+lL0AlOsVaOrJiSPVUuy6Crn5hh6AqioQXLu1EeEjRhDF7htlS5rau6+Kvb4fUoCaw45a3wLVcGL6HPmO8RAPpp2A9gn5NfaHRYVswxzZstd+ltvX1MkeE3eXSacIveM1d/qRmaFhIK7Pyk0BdI+rkjWzykBXahzcVCnwRSMqSzVsIzRPyTlwwmJADVvYJ7e3HRxw2AJU1A2Kb0U+RVpyIpX5k9Zxd8rq/r7AG/29O0+Bf5nlRRg+wTbjAk6j/iic/i8pQ/RylpmCEwcuuk13Ugiatv07LgAnnEwoK424XjQbtqMqXegRpdGh7DTv8SwfSNkKikOLPlDKHlKdwD0K4MPWWxa36JNNI+ZZB+t0nxtmQOIVIk0tuOEU
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 aa6f606d-cb5f-44f3-3997-08d911777e75
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 May 2021 16:45:17.3755
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 k2zxhHs6NHbmc/A+GcJa+V7nbN7yg76UxeHogJQIOQsWPkDbBPF6OEmkMTCz/dT/6aKbbr576ppq7h7y1VFR84bWqa1pzz7JdElo9ngCeBA=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL3PR02MB7938
X-Proofpoint-ORIG-GUID: 2LyWATrpTl0zdgWaiN3mCI9C_-WSRbkO
X-Proofpoint-GUID: 2LyWATrpTl0zdgWaiN3mCI9C_-WSRbkO
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-07_06:2021-05-06,2021-05-07 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_load_host_xsave_state handles xsave on vm exit, part of which is
managing memory protection key state. The latest arch.pkru is updated
with a rdpkru, and if that doesn't match the base host_pkru (which
about 70% of the time), we issue a __write_pkru.

__write_pkru issues another rdpkru internally to try to avoid the
wrpkru, so we're reading the same value back to back when we 100% of
the time know that we need to go directly to wrpkru. This is a 100%
branch miss and extra work that can be skipped.

To improve performance, add a hint to __write_pkru so that callers
can specify if they've already done the check themselves. The
compiler seems to filter this branch this out completely when the hint
is true, so incrementally tighter code is generated as well.

While we're in this section of code, optimize if condition ordering
prior to __write_pkru in both kvm_load_{guest|host}_xsave_state.

For both functions, flip the ordering of the || condition so that
arch.xcr0 & XFEATURE_MASK_PKRU is checked first, which when
instrumented in our evironment appeared to be always true and less
overall work than kvm_read_cr4_bits.

For kvm_load_guest_xsave_state, hoist arch.pkru != host_pkru ahead
one position. When instrumented, I saw this be true roughly ~70% of
the time vs the other conditions which were almost always true.
With this change, we will avoid 3rd condition check ~30% of the time.

Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Jon Kohler <jon@nutanix.com>
---
 arch/x86/include/asm/fpu/internal.h  |  2 +-
 arch/x86/include/asm/pgtable.h       |  2 +-
 arch/x86/include/asm/special_insns.h | 10 ++++++----
 arch/x86/kvm/x86.c                   | 14 +++++++-------
 4 files changed, 15 insertions(+), 13 deletions(-)

--
2.30.1 (Apple Git-130)

```
#### [PATCH 1/2] KVM: SVM: Update EFER software model on CR0 trap for SEV-ES
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12244965
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 192B5C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:59:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC5FD61464
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:59:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238469AbhEGRA4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 13:00:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33620 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238463AbhEGRAz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 13:00:55 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 99714C061574
        for <kvm@vger.kernel.org>; Fri,  7 May 2021 09:59:55 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id
 e13-20020ac8598d0000b02901cde66f0e26so6112303qte.16
        for <kvm@vger.kernel.org>; Fri, 07 May 2021 09:59:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=VEqazMRlmbfIIn+WG70+8s+sSnlsOL4Ks0sRraeMi3w=;
        b=KoPzAD/24Udvfs3SJG4WetUnaKKUe3D0ar4Ivq2GQhThmRCDu9l3O7QsQNtw++wfHh
         65iBehtJpcXdNz3xkh/Ix9UCiyymzFgug1Sg+w/mb0ROVv7JPh5UYcyQti4LU6jfe7g7
         dtGAhaS6Sdo4ly9Q4bDmaT2UK0xrMhaghZ4W6ykzK5nrIdB8+UzANZ9GUfXcQl648dw9
         R7NFiAxmDheyavR+Pr4wT+sSwHDWTZAaDA+96U7yikIbrtBk7mha0v3DzFR3CjcSm/rc
         tBSFA94qgJnk3ayhcLFDYQJaZf2MJOeEO8pVot6E2fQd8w99wXF/+Zkjmb3dhWAVuY+R
         exnA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=VEqazMRlmbfIIn+WG70+8s+sSnlsOL4Ks0sRraeMi3w=;
        b=owDRI9/eIyqdUfuybtUPzJL5uwTeMV54uaEl1c7FDFTMPBLhBoW2mKDtlCESxFfVhG
         GTH5GLV5gwtHZ/DRNvjxk42HUj8aqxOuBu5EVBHPfgravAeMc8YJzGTNuga/Vv3mq6lc
         YzZiWzYUIfOt3jYBeI3vIcaEfTYkeE3fZ4cdL/Q8LPhaXB5JekwSzSjVxdfvFkaktdvn
         4+fFjzhBfY+3K/7dx8qSyWypBkQHE2QDA6wGL6psOYB2VrbxJ34k+n4M3GmVf0ZkGG15
         cNXxLbDeL2XnUQomD2SNKPW6secmcK+ykSsz76XkFlbgCLBl4WBNYuXUA4Yv6SF7BqyA
         U2pA==
X-Gm-Message-State: AOAM5318SUHhVCIg3HMASH4WE7svQz8vewTnCbptmf+npBZSjcbB3i2f
        y1aK2AUCvavXoO7rh4U3+zKWuMnFnfw=
X-Google-Smtp-Source: 
 ABdhPJw6zN0EFivUJ5aFuE1VE0FDRIzkiTdsJFLSDUACFvRn3SazAnoaxoqkJWhO97XADtkBnhJNB/aZ9FA=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:7352:5279:7518:418f])
 (user=seanjc job=sendgmr) by 2002:ad4:4e44:: with SMTP id
 eb4mr10683142qvb.3.1620406794805;
 Fri, 07 May 2021 09:59:54 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  7 May 2021 09:59:46 -0700
In-Reply-To: <20210507165947.2502412-1-seanjc@google.com>
Message-Id: <20210507165947.2502412-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210507165947.2502412-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH 1/2] KVM: SVM: Update EFER software model on CR0 trap for
 SEV-ES
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Gonda <pgonda@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For protected guests, a.k.a. SEV-ES guests, update KVM's model of EFER
when processing the side effect of the CPU entering long mode when paging
is enabled.  The whole point of intercepting CR0/CR4/EFER is to keep
KVM's software model up-to-date.

Fixes: f1c6366e3043 ("KVM: SVM: Add required changes to support intercepts under SEV-ES")
Reported-by: Peter Gonda <pgonda@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: use X86_FEATURE_RSB_CTXSW for RSB stuffing in vmexit
##### From: Jon Kohler <jon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Kohler <jon@nutanix.com>
X-Patchwork-Id: 12244863
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.5 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CC1EC433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 15:08:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 495B861480
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 15:08:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233726AbhEGPJS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 11:09:18 -0400
Received: from mx0a-002c1b01.pphosted.com ([148.163.151.68]:21764 "EHLO
        mx0a-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233414AbhEGPJQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 11:09:16 -0400
Received: from pps.filterd (m0127837.ppops.net [127.0.0.1])
        by mx0a-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 147F2j6b032110;
        Fri, 7 May 2021 08:07:16 -0700
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=proofpoint20171006;
 bh=T+U6BfE1UIgocRpHqU11DfVFJaofIYhYh8JQiAHx7J0=;
 b=OG1e9s06olZLQBwy4OcmXmfimId6zTdDVpeWgTXCLRK8+2yJB+OzPahVn9s/srAEKJpI
 0QcckeBKdhGgPNYKiNU3wMJFuX7phX/YbnshA17KzVs/GdgXpfQVWenYVvOwqSAgzcfN
 pps8A5Au+NFqumI+fdzJNu75r+1UlbG7+awiQZ6AhoxQWMe46H5G2brChzs7BbKwKPhr
 lzGlE+IrqOJcucFZRxP4myhaL+cFVosQ0eDSXGavsFUp5W1X6aDVq4oUFfhljaq9W9gn
 fO00mMn0fCwQ81D8XozY+P8F2YAKjxndySDUWbJ6T1HTLpZMOlcDCk8s5Wejyipx770B NA==
Received: from nam02-bn1-obe.outbound.protection.outlook.com
 (mail-bn1nam07lp2040.outbound.protection.outlook.com [104.47.51.40])
        by mx0a-002c1b01.pphosted.com with ESMTP id 38csqr1gmp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 May 2021 08:07:15 -0700
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=C6Q/ch+DH+hVvmIqhlehjJHDxQLSs9lBzN6q/aF5vWvBNwVo2igVplZxEis6Q6+q0KlEoGUrX1jZQaVs2Lcoc3r63qPYEzoHWKbEiYpiiu4r/cPbfVab7ugs1w8hap/OhciFKtuLvAjxwm2d8Hjs0CqO2lAxYAFHR/YW/kNJ1BKJAi6DqGCMsmwgWOpm9ZZydj2DHJxVcOUIPisOlMhEDauKY/o1+reRu4iUA/ca7YD3M7rrn2zqiwNG1It/dhv39Ca8LTU6ZactPQ7n28qv1nAip4eiBzEqAd5jdVScmBmxU94vqIYq6kECmO3VDvhC93KE9UVqaSkgQ1q1CxdhcA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=T+U6BfE1UIgocRpHqU11DfVFJaofIYhYh8JQiAHx7J0=;
 b=V69dAu9BMHYrWToIda6pCpUPxvBAJULN7JbgXa/lTQg+pRHtYmsHQBFMaw4dAHV/rUCPjvhHbV+iel4rLDZkW/4hjWcydprZjCXhwcE5EIZe5YrTmMa6EF3day+hGSNWIQXff3DYJdEtY/cF1USeqv/P8IDxM6+oIzSjJooGtt8671+yCdFr7zu9zbQmQcNi/klYPaADm13Im9sIpNEDX2ge1Z17MkyBvnpd1A7Lk6edGj4GBltmJQmjwOLGdMW86FVvY6+JD+IO7Oc+MPfOZcct04BXKy07RxooTjXHgkEKois+fr3JUZVe3M2xrJEaJ/oANdErbEvHNNHHIEaTJg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Authentication-Results: nutanix.com; dkim=none (message not signed)
 header.d=none;nutanix.com; dmarc=none action=none header.from=nutanix.com;
Received: from BL0PR02MB4579.namprd02.prod.outlook.com (2603:10b6:208:4b::10)
 by BL0PR02MB4883.namprd02.prod.outlook.com (2603:10b6:208:54::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.26; Fri, 7 May
 2021 15:07:13 +0000
Received: from BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07]) by BL0PR02MB4579.namprd02.prod.outlook.com
 ([fe80::75cf:5b99:f963:cc07%5]) with mapi id 15.20.4108.029; Fri, 7 May 2021
 15:07:13 +0000
From: Jon Kohler <jon@nutanix.com>
Cc: Jon Kohler <jon@nutanix.com>, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: use X86_FEATURE_RSB_CTXSW for RSB stuffing in
 vmexit
Date: Fri,  7 May 2021 11:06:36 -0400
Message-Id: <20210507150636.94389-1-jon@nutanix.com>
X-Mailer: git-send-email 2.30.1 (Apple Git-130)
X-Originating-IP: [2601:19b:c501:64d0:a9a2:6149:85cc:8a4]
X-ClientProxiedBy: BY3PR05CA0037.namprd05.prod.outlook.com
 (2603:10b6:a03:39b::12) To BL0PR02MB4579.namprd02.prod.outlook.com
 (2603:10b6:208:4b::10)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from C02F13YVQ05N.corp.nutanix.com
 (2601:19b:c501:64d0:a9a2:6149:85cc:8a4) by
 BY3PR05CA0037.namprd05.prod.outlook.com (2603:10b6:a03:39b::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.12 via Frontend
 Transport; Fri, 7 May 2021 15:07:10 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 6ae1a3d3-5d77-4ac9-67e4-08d91169cb96
X-MS-TrafficTypeDiagnostic: BL0PR02MB4883:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BL0PR02MB4883D77AF0FC04445A959DA0AF579@BL0PR02MB4883.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
X-MS-Oob-TLC-OOBClassifiers: OLM:294;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 5+IRvV9slExiGbcPFeBmK1XqdbfsePZMxG2REDeWKjb0gvoecUkfk11SN2RPg70mD96KhQ+2TIXemf67nVjatQnfEOb83DGonJj2tj2vYIfQX+RQrX8XoDr3l4bMqkG1DchLD5JKgMiAqQYXlBdtZVjLjr2ecSzePjRz3GoEx3FRpiNt/clkXVmeFYpQL7cvcPmMZ2Mf99dyeqpRugk99vo2rvQst2tQKVNDeO1kgvSjR9Wk/c+RMs2hAOmbOkUVevjT/ywint+IhlEV7XAPf7+HoNOjmzdS4MV7eccTDH5OxMCB/27AO0qgQum7OnxQGk4VaVgbBZv3zNLENp8w52oF6iuy9eV2180KMS/ehoVuvDL7/6lNAfMlltKL/VyTwIFRBkkpDdgJly7+uwkxev1UO+i5Mk9LfB9HqkuSB39oxzXdrhSMG3aphR8Hr9Wbp4dfvLVWY7SlzXkVgQrKPtIq0ertSZbTAtxiWtSSawsFksK45ET/UU3uz8B92/8aSneXvYjHubDfHjS+n50HvX9BG+UbdizIiOuqFQ8aGFS9VLT8gLyrCUgG0LFslM10OX3N6wJl+hePlbQ3iDNT1iFyETgLA3RmG+iVNtBdNbG7cUCL7uJaOlOtCGVFs1Km/zOdlK4XIBkXa4QwZB8EUQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4579.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(346002)(376002)(136003)(39850400004)(396003)(66946007)(2616005)(5660300002)(2906002)(1076003)(8676002)(83380400001)(52116002)(38100700002)(7696005)(186003)(66556008)(16526019)(66476007)(478600001)(109986005)(36756003)(4326008)(86362001)(8936002)(316002)(7416002)(6486002)(6666004)(54906003)(266003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData-ChunkCount: 1
X-MS-Exchange-AntiSpam-MessageData-0: 
 fHpegl5EbwqyrFO6uq6+H9fJRiluDYzAbelcarEuNP8XYLkQfLi51RZNkXRkE02Ad/38b3jqK82XslgxLFvMvxxAVzP7ScTq2d/fPcdMo6rw5FaAphpi4bBnFDmQCG+W7kavmLyFcXOcNQkn9n40rdCnWGAUpiwCxvVZyNbooAuOmIHXh8auN+txl5nvLpwWncWpAuD/GCsKn6RshkaQT6d8GlPTavDrGx7FQxbkZYhqftEnmxYY1oXyHSPrOAKTnw7aYCmkUTTe0cwZWIjRb8wG4x28iPk5DB9BkXOvNRxGfbRpl6/iISYYzh59kZF3stSZIGaX2GvJLulW7ifo4BO4p3bMvbE/AogWLIgtRnbBjWOrP92hGqqHjG3lsYZ2rp7gT2NWmaNC3P1lWR77H4lxnLtgMm4BoLOjEIkjpsyu3BZ+M1WUrgLQRI2PRkbDWjymFxXRRAEOhiPsdUxHDnuJ+VL55nPrCN7fB+qBR7r8bCi3HIfhZefUHO2TZVijJdPdn21ftcKOhkkHaRspVkVYqQISi9X1Sj9reM6IRIbaRRpaAWPEtq+iYEx8koBmEj1evOhMRs97wH1aBEhxxyaVEQvcRaDrq0W2XoXV7QrG8VuWK/RmaNxe9t+TN6RPyRQSazNz/DBc/q9fTb6IsEaW5tp39Bj8ffCnrEy1oOedRf0X6Q7XGS0jK1YjK4t69+99gG8+Pkk0EMDAq5BS+jYyWtzMSulwmrKgBPWqW/sY2mkN/cs5sjiU38EoaMxRFFCvqjbKj6zUAr9n8yh9D+LmOjwAbsmstjAiz7srvma9nNHJtTPOwdO1+Rey0i8S9gMs9r73UcmCGuqwHLk3p+EopLJysvCcGA5MBTqyQNXbtCadw1dVGridjKt1Cl4kZiqsJoikMyydyU+ll79qk2/8RTCIIAHSimE5HaQqzcXEXpZwxX+gcEixCfLiI6xPMzvwp2QL2eI5P01+sVKuykB1/asxUQYpA6xyYzg3oFcDgt51F+SPKst65v5I2z7SK+8oBJCOvNa4jhcLZL1FSCAOF5xiSTYJPC68NrgcUYz922jXOPgOLbSSrg1wjyjQInJwEIo2/KP3tNxKgmeLcJI4ADZ19SwwrWeEyvMuq8QP3Ed0juSYAu43SzbjL51vLBKvzIyC0Q6a5UPMh0RUDEJH5ocyTahep6rqdsQ70tVKWQ3AUy/a4gAgx0Tdagnu34Hbq8dCTv0UOSDl/LU1QF12e++jMrqUI0cjSY8J4U3EkT4677VYfP4BY5zLnjqhsgHqNFk4rRFatzQGwLz0KpmyXEGqoMSv6rhsVJKLGFadCdIjLC277Pn+4k1nF2+cUFLV7v2DxL1A+l/NPM8m24r1Xh7Ikbl++BUeZnwcoqpODKA1NXmNlNMOIE+L2Nxk
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6ae1a3d3-5d77-4ac9-67e4-08d91169cb96
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4579.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 May 2021 15:07:13.7464
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 lEmoCS/JavAiCgixedtEJKtJ7jtl4ACtv/NpFJaSud0XFBaLsaE7jJVpTO8h72jte0YEsQCTVGZ83g7Y43xB5D84NrMlB5wP7+GsQoBu0iE=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL0PR02MB4883
X-Proofpoint-ORIG-GUID: N5Fo_JGjmZw932CpxCuTmD72cjGf-0qO
X-Proofpoint-GUID: N5Fo_JGjmZw932CpxCuTmD72cjGf-0qO
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-07_06:2021-05-06,2021-05-07 signatures=0
X-Proofpoint-Spam-Reason: safe
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

cpufeatures.h defines X86_FEATURE_RSB_CTXSW as "Fill RSB on context
switches" which seems more accurate than using X86_FEATURE_RETPOLINE
in the vmxexit path for RSB stuffing.

X86_FEATURE_RSB_CTXSW is used for FILL_RETURN_BUFFER in
arch/x86/entry/entry_{32|64}.S. This change makes KVM vmx and svm
follow that same pattern. This pairs up nicely with the language in
bugs.c, where this cpu_cap is enabled, which indicates that RSB
stuffing should be unconditional with spectrev2 enabled.
	/*
	 * If spectre v2 protection has been enabled, unconditionally fill
	 * RSB during a context switch; this protects against two independent
	 * issues:
	 *
	 *	- RSB underflow (and switch to BTB) on Skylake+
	 *	- SpectreRSB variant of spectre v2 on X86_BUG_SPECTRE_V2 CPUs
	 */
	setup_force_cpu_cap(X86_FEATURE_RSB_CTXSW);

Furthermore, on X86_FEATURE_IBRS_ENHANCED CPUs && SPECTRE_V2_CMD_AUTO,
we're bypassing setting X86_FEATURE_RETPOLINE, where as far as I could
find, we should still be doing RSB stuffing no matter what when
CONFIG_RETPOLINE is enabled and spectrev2 is set to auto.

Signed-off-by: Jon Kohler <jon@nutanix.com>
---
 arch/x86/kvm/svm/vmenter.S | 4 ++--
 arch/x86/kvm/vmx/vmenter.S | 4 ++--
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v3 15/17] target/ppc/kvm: Replace alloca() by g_malloc()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12244761
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43C7CC433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 14:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC04961414
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 14:44:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237692AbhEGOpd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 10:45:33 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53977 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234601AbhEGOpd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 10:45:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620398673;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=C+MYJWIsLohbCHlMSEIGcZQyDaEDuU9Kl0ow5213YNc=;
        b=T9bqPQ1iOCtOKzHERhU/iTCRz0QU+fJrVF7VtsJtQ1CCf+nD5fiCd3UL4Tf5Pug+hnXn0A
        iS6taGJK/KAqmDWOLanVYHlyKIuW8EShZq3IPNpUd9MsmnZ1qhfip1w63fLcuGeZLzqRD3
        urf2/VDDc9L3+6oZq7q/Vf4Cs3vKot0=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-302-r851SfVcOGyO7fkQu3389g-1; Fri, 07 May 2021 10:44:31 -0400
X-MC-Unique: r851SfVcOGyO7fkQu3389g-1
Received: by mail-wr1-f69.google.com with SMTP id
 65-20020adf82c70000b0290107593a42c3so3701426wrc.5
        for <kvm@vger.kernel.org>; Fri, 07 May 2021 07:44:31 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=C+MYJWIsLohbCHlMSEIGcZQyDaEDuU9Kl0ow5213YNc=;
        b=R4U2iQ07ssxn8xm2HOpcowGBxbc3YE+hzR3/7iIgPAGbMWKBXSzyY8fQWqfl0qLro7
         JRgBKbCssBvJl//giwX8CcvSekj2MSBxxtRZ2UN5pmPT5XpcZSoZML4C76jOjo+j1T3s
         tR81lIKvA77fwo3/rP+risfZbFMefuztjIoRNMZgkiUEnPQCzz0D3+pQUQEBG4uJ4Vz4
         ClSEd4xz+nRkKdNhPj2BublaR9WvPRXjLXWAbn4ahZBLO54q5d+s8FBYpfdu0lT3dbMt
         2IGNHs7vnfPPeRrol/gmSMKcfCmcdOnmnC9qEIfnNW329JVWuD5TVA68t5Z6ErhrtFnC
         qejA==
X-Gm-Message-State: AOAM5334ELiildZYAUKIPjKGROmsPD3zE8D5gF5lmfhYqkPkDSuTAwpQ
        ttFq+cQBPwnkvZF++y+ZjzIwkuLlUQyqJCxLCjc/ohR6odNKbw3HOEbZhvyobyZChVMV3D1hOXa
        66xFlpJUct8hg
X-Received: by 2002:adf:f80f:: with SMTP id
 s15mr12876030wrp.341.1620398670260;
        Fri, 07 May 2021 07:44:30 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyV3LXdgDeT9W3nPy2PYFEyT0xnL/c2fIbnfgtcygElbhUWgwrD2nI+U4GtCxZ9QE5ZsaU17g==
X-Received: by 2002:adf:f80f:: with SMTP id
 s15mr12876009wrp.341.1620398670157;
        Fri, 07 May 2021 07:44:30 -0700 (PDT)
Received: from localhost.localdomain
 (astrasbourg-652-1-219-60.w90-40.abo.wanadoo.fr. [90.40.114.60])
        by smtp.gmail.com with ESMTPSA id
 r13sm8833726wrn.2.2021.05.07.07.44.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 07 May 2021 07:44:29 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Laurent Vivier <laurent@vivier.eu>, Paolo Bonzini <pbonzini@redhat.com>,
 qemu-ppc@nongnu.org, Peter Maydell <peter.maydell@linaro.org>, =?utf-8?q?Al?=
	=?utf-8?q?ex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Gerd Hoffmann <kraxel@redhat.com>, qemu-arm@nongnu.org, =?utf-8?q?Philippe_?=
	=?utf-8?q?Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Greg Kurz <groug@kaod.org>, David Gibson <david@gibson.dropbear.id.au>,
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PATCH v3 15/17] target/ppc/kvm: Replace alloca() by g_malloc()
Date: Fri,  7 May 2021 16:43:13 +0200
Message-Id: <20210507144315.1994337-16-philmd@redhat.com>
X-Mailer: git-send-email 2.26.3
In-Reply-To: <20210507144315.1994337-1-philmd@redhat.com>
References: <20210507144315.1994337-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ALLOCA(3) man-page mentions its "use is discouraged".

Use autofree heap allocation instead, replacing it by a g_malloc call.

Reviewed-by: Greg Kurz <groug@kaod.org>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/ppc/kvm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC PATCH v2 1/3] vfio/iommu_type1: Add HWDBM status maintenance
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12244361
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89502C43460
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 10:37:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A03661431
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 10:37:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236965AbhEGKiI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 06:38:08 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:18352 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236949AbhEGKiC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 06:38:02 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4Fc6JH4R8yzCr6t;
        Fri,  7 May 2021 18:34:23 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Fri, 7 May 2021 18:36:50 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Tian Kevin <kevin.tian@intel.com>
CC: Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Will Deacon <will@kernel.org>, Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 1/3] vfio/iommu_type1: Add HWDBM status maintenance
Date: Fri, 7 May 2021 18:36:06 +0800
Message-ID: <20210507103608.39440-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210507103608.39440-1-zhukeqian1@huawei.com>
References: <20210507103608.39440-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kunkun Jiang <jiangkunkun@huawei.com>

We are going to optimize dirty log tracking based on iommu dirty
log tracking, but the dirty log from iommu is useful only when
all iommu backed domains support it.

This maintains a counter in vfio_iommu, which is used for dirty
bitmap population in next patch.

This also maintains a boolean flag in vfio_domain, which is used
in the policy of switch dirty log in next patch.

Co-developed-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Kunkun Jiang <jiangkunkun@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 25 +++++++++++++++++++++++++
 1 file changed, 25 insertions(+)

```
#### [PATCH] vfio/pci: Sanity check IGD OpRegion SizeFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12245073
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E9ADC433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 18:53:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47405613C0
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 18:53:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229635AbhEGSyV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 14:54:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:45596 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229488AbhEGSyV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 14:54:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620413600;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=to4F3RSSacx66bqGoR4rednsO9qjieECmlHxCX3pgUA=;
        b=Tx1412wWo3TLsN86I5AvfRVIERuv1hZfBKuDtKnb77n9hufjvfRFKGu3XeVBNok9ep2nRR
        2bhP0KgO3uMo9uuGNLi3Z55etIosO15TC3XFRU7La32JHQXsD/jmD39rI6oVsfWGtYmHi/
        PUEq1C+Pn1MEEiJSRMmuvmiTDMUKwVs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-575-taiXcfulPziogsO5EiL8Vg-1; Fri, 07 May 2021 14:53:18 -0400
X-MC-Unique: taiXcfulPziogsO5EiL8Vg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C3097100A67C;
        Fri,  7 May 2021 18:53:17 +0000 (UTC)
Received: from [172.30.42.188] (ovpn-113-225.phx2.redhat.com [10.3.113.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 96C805D74A;
        Fri,  7 May 2021 18:53:17 +0000 (UTC)
Subject: [PATCH] vfio/pci: Sanity check IGD OpRegion Size
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: tkffaul@outlook.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Date: Fri, 07 May 2021 12:53:17 -0600
Message-ID: <162041357421.21800.16214130780777455390.stgit@omen>
User-Agent: StGit/1.0-8-g6af9-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The size field of the IGD OpRegion table is supposed to indicate table
size in KB, but we've seen at least one report of a BIOS that appears
to incorrectly report size in bytes.  The default size is 8 (*1024 =
8KB), but an incorrect implementation may report 8192 (*1024 = 8MB)
and can cause a variety of mapping errors.

It's believed that 8MB would be an implausible, if not absurd, actual
size, so we can probably be pretty safe in assuming this is a BIOS bug
where the intended size is likely 8KB.

Reported-by: Travis Faulhaber <tkffaul@outlook.com>
Tested-by: Travis Faulhaber <tkffaul@outlook.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_igd.c |   11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [patch 1/4] KVM: x86: add start_assignment hook to kvm_x86_opsReferences: <20210507130609.269153197@redhat.com>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12244549
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B865C433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D968561466
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236743AbhEGNLW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 09:11:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:44833 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236434AbhEGNLT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 09:11:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620393019;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=yZmXVCCtQd+G9YWj0HVU+KdVOSHrhwSnoYMJJQ0B04w=;
        b=BUWYgA7sTe5A+ytt2V2DA2EspZ4ierxMWWeOklolacJrE+Sa54J6XAqJ08pofUVjOg61oT
        eKOLbbOLQ967FGr6NXr/PHzQxXIlqymNCEOfE9jWMBZTgFwQYYyGCoOZ2dgw4Jf6NPEO7R
        te1HDVzFq00rIXR+w2Gr+QE74vqatFE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-442-nqxt_hWAMvKorCU_9QPP1Q-1; Fri, 07 May 2021 09:10:17 -0400
X-MC-Unique: nqxt_hWAMvKorCU_9QPP1Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DF4A3107ACC7;
        Fri,  7 May 2021 13:10:16 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id D8EE536E0;
        Fri,  7 May 2021 13:10:12 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id A01B941486FD; Fri,  7 May 2021 10:10:07 -0300 (-03)
Message-ID: <20210507130923.438255076@redhat.com>
User-Agent: quilt/0.66
Date: Fri, 07 May 2021 10:06:10 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 1/4] KVM: x86: add start_assignment hook to kvm_x86_ops
References: <20210507130609.269153197@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a start_assignment hook to kvm_x86_ops, which is called when 
kvm_arch_start_assignment is done.

The hook is required to update the wakeup vector of a sleeping vCPU
when a device is assigned to the guest.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

Index: kvm/arch/x86/include/asm/kvm_host.h
===================================================================
--- kvm.orig/arch/x86/include/asm/kvm_host.h
+++ kvm/arch/x86/include/asm/kvm_host.h
@@ -1322,6 +1322,7 @@ struct kvm_x86_ops {
 
 	int (*update_pi_irte)(struct kvm *kvm, unsigned int host_irq,
 			      uint32_t guest_irq, bool set);
+	void (*start_assignment)(struct kvm *kvm, int device_count);
 	void (*apicv_post_state_restore)(struct kvm_vcpu *vcpu);
 	bool (*dy_apicv_has_pending_interrupt)(struct kvm_vcpu *vcpu);
 
Index: kvm/arch/x86/kvm/svm/svm.c
===================================================================
--- kvm.orig/arch/x86/kvm/svm/svm.c
+++ kvm/arch/x86/kvm/svm/svm.c
@@ -4601,6 +4601,7 @@ static struct kvm_x86_ops svm_x86_ops __
 	.deliver_posted_interrupt = svm_deliver_avic_intr,
 	.dy_apicv_has_pending_interrupt = svm_dy_apicv_has_pending_interrupt,
 	.update_pi_irte = svm_update_pi_irte,
+	.start_assignment = NULL,
 	.setup_mce = svm_setup_mce,
 
 	.smi_allowed = svm_smi_allowed,
Index: kvm/arch/x86/kvm/vmx/vmx.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.c
+++ kvm/arch/x86/kvm/vmx/vmx.c
@@ -7732,6 +7732,7 @@ static struct kvm_x86_ops vmx_x86_ops __
 	.nested_ops = &vmx_nested_ops,
 
 	.update_pi_irte = pi_update_irte,
+	.start_assignment = NULL,
 
 #ifdef CONFIG_X86_64
 	.set_hv_timer = vmx_set_hv_timer,
Index: kvm/arch/x86/kvm/x86.c
===================================================================
--- kvm.orig/arch/x86/kvm/x86.c
+++ kvm/arch/x86/kvm/x86.c
@@ -11295,7 +11295,10 @@ bool kvm_arch_can_dequeue_async_page_pre
 
 void kvm_arch_start_assignment(struct kvm *kvm)
 {
-	atomic_inc(&kvm->arch.assigned_device_count);
+	int ret;
+
+	ret = atomic_inc_return(&kvm->arch.assigned_device_count);
+	static_call_cond(kvm_x86_start_assignment)(kvm, ret);
 }
 EXPORT_SYMBOL_GPL(kvm_arch_start_assignment);
 
Index: kvm/arch/x86/include/asm/kvm-x86-ops.h
===================================================================
--- kvm.orig/arch/x86/include/asm/kvm-x86-ops.h
+++ kvm/arch/x86/include/asm/kvm-x86-ops.h
@@ -99,6 +99,7 @@ KVM_X86_OP_NULL(post_block)
 KVM_X86_OP_NULL(vcpu_blocking)
 KVM_X86_OP_NULL(vcpu_unblocking)
 KVM_X86_OP_NULL(update_pi_irte)
+KVM_X86_OP_NULL(start_assignment)
 KVM_X86_OP_NULL(apicv_post_state_restore)
 KVM_X86_OP_NULL(dy_apicv_has_pending_interrupt)
 KVM_X86_OP_NULL(set_hv_timer)

From patchwork Fri May  7 13:06:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12244547
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 94F2BC433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E80461464
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236726AbhEGNLV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 09:11:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:35598 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232140AbhEGNLT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 09:11:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620393019;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=3szDupmhb5P3gzH2roiv5CqgjhCLQjU+Y1Q5biEIpRs=;
        b=SSLvvI0fK5jIbF5ALwRwj8SUF4ZPhKeuXRQ18RvkcVRy86IY30h45e/wfT1uFuektmTdNZ
        ebcqx+4qkjb6Nrh9f4UEW/hRo1D6NmAcYuuFwwAZhjCYtIpxZnGC4nTc/n0mSgPHpVyYHa
        0kFy0JFHPdLSuIVOldkEwnDrXSvaeUI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-242-Xa6uYFsgMjuSOm6-ga3jVQ-1; Fri, 07 May 2021 09:10:17 -0400
X-MC-Unique: Xa6uYFsgMjuSOm6-ga3jVQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DED0A64149;
        Fri,  7 May 2021 13:10:16 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id F128B13487;
        Fri,  7 May 2021 13:10:12 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id A29D640E6DFB; Fri,  7 May 2021 10:10:07 -0300 (-03)
Message-ID: <20210507130923.468254904@redhat.com>
User-Agent: quilt/0.66
Date: Fri, 07 May 2021 10:06:11 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 2/4] KVM: add arch specific vcpu_check_block callback
References: <20210507130609.269153197@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add callback in kvm_vcpu_check_block, so that architectures
can direct a vcpu to exit the vcpu block loop without requiring
events that would unhalt it.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

Index: kvm/include/linux/kvm_host.h
===================================================================
--- kvm.orig/include/linux/kvm_host.h
+++ kvm/include/linux/kvm_host.h
@@ -971,6 +971,13 @@ static inline int kvm_arch_flush_remote_
 }
 #endif
 
+#ifndef __KVM_HAVE_ARCH_VCPU_CHECK_BLOCK
+static inline int kvm_arch_vcpu_check_block(struct kvm_vcpu *vcpu)
+{
+	return 0;
+}
+#endif
+
 #ifdef __KVM_HAVE_ARCH_NONCOHERENT_DMA
 void kvm_arch_register_noncoherent_dma(struct kvm *kvm);
 void kvm_arch_unregister_noncoherent_dma(struct kvm *kvm);
Index: kvm/virt/kvm/kvm_main.c
===================================================================
--- kvm.orig/virt/kvm/kvm_main.c
+++ kvm/virt/kvm/kvm_main.c
@@ -2794,6 +2794,8 @@ static int kvm_vcpu_check_block(struct k
 		goto out;
 	if (signal_pending(current))
 		goto out;
+	if (kvm_arch_vcpu_check_block(vcpu))
+		goto out;
 
 	ret = 0;
 out:

From patchwork Fri May  7 13:06:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12244551
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 672C2C43462
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 27C8F6145D
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236821AbhEGNLX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 09:11:23 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40708 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236480AbhEGNLV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 09:11:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620393021;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=0FISU66+bSzKWpxBjhGrO1Tlhi9U0QwtDOlzrc6O7DQ=;
        b=CNABv+0g3KaGtuL62LCbV6WFzQHgonfCeYHGciRH90bO0QRgUnro1Anmtlcg4SOpEdKdim
        stl9XiiVyRBXSz+I+GpOtupval/Aap8UwQSjHJmckVZmlE8fwNKZUZvq8owXY64ak4uaJc
        x296V2+D/JUndBXCJXXG6dp9n//FPGo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-401-ZErEkDUlNwqGgWd_f8nj1g-1; Fri, 07 May 2021 09:10:17 -0400
X-MC-Unique: ZErEkDUlNwqGgWd_f8nj1g-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E4DAF10066E6;
        Fri,  7 May 2021 13:10:16 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id E6595100164A;
        Fri,  7 May 2021 13:10:12 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id A776F40B1EB1; Fri,  7 May 2021 10:10:07 -0300 (-03)
Message-ID: <20210507130923.498207045@redhat.com>
User-Agent: quilt/0.66
Date: Fri, 07 May 2021 10:06:12 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 3/4] KVM: x86: implement kvm_arch_vcpu_check_block callback
References: <20210507130609.269153197@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Implement kvm_arch_vcpu_check_block for x86. Next patch will add
implementation of kvm_x86_ops.vcpu_check_block for VMX.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

Index: kvm/arch/x86/include/asm/kvm_host.h
===================================================================
--- kvm.orig/arch/x86/include/asm/kvm_host.h
+++ kvm/arch/x86/include/asm/kvm_host.h
@@ -1320,6 +1320,8 @@ struct kvm_x86_ops {
 	void (*vcpu_blocking)(struct kvm_vcpu *vcpu);
 	void (*vcpu_unblocking)(struct kvm_vcpu *vcpu);
 
+	int (*vcpu_check_block)(struct kvm_vcpu *vcpu);
+
 	int (*update_pi_irte)(struct kvm *kvm, unsigned int host_irq,
 			      uint32_t guest_irq, bool set);
 	void (*start_assignment)(struct kvm *kvm, int device_count);
@@ -1801,6 +1803,15 @@ static inline bool kvm_irq_is_postable(s
 		irq->delivery_mode == APIC_DM_LOWEST);
 }
 
+#define __KVM_HAVE_ARCH_VCPU_CHECK_BLOCK
+static inline int kvm_arch_vcpu_check_block(struct kvm_vcpu *vcpu)
+{
+	if (kvm_x86_ops.vcpu_check_block)
+		return static_call(kvm_x86_vcpu_check_block)(vcpu);
+
+	return 0;
+}
+
 static inline void kvm_arch_vcpu_blocking(struct kvm_vcpu *vcpu)
 {
 	static_call_cond(kvm_x86_vcpu_blocking)(vcpu);
Index: kvm/arch/x86/kvm/vmx/vmx.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.c
+++ kvm/arch/x86/kvm/vmx/vmx.c
@@ -7727,6 +7727,7 @@ static struct kvm_x86_ops vmx_x86_ops __
 
 	.pre_block = vmx_pre_block,
 	.post_block = vmx_post_block,
+	.vcpu_check_block = NULL,
 
 	.pmu_ops = &intel_pmu_ops,
 	.nested_ops = &vmx_nested_ops,
Index: kvm/arch/x86/include/asm/kvm-x86-ops.h
===================================================================
--- kvm.orig/arch/x86/include/asm/kvm-x86-ops.h
+++ kvm/arch/x86/include/asm/kvm-x86-ops.h
@@ -98,6 +98,7 @@ KVM_X86_OP_NULL(pre_block)
 KVM_X86_OP_NULL(post_block)
 KVM_X86_OP_NULL(vcpu_blocking)
 KVM_X86_OP_NULL(vcpu_unblocking)
+KVM_X86_OP_NULL(vcpu_check_block)
 KVM_X86_OP_NULL(update_pi_irte)
 KVM_X86_OP_NULL(start_assignment)
 KVM_X86_OP_NULL(apicv_post_state_restore)
Index: kvm/arch/x86/kvm/svm/svm.c
===================================================================
--- kvm.orig/arch/x86/kvm/svm/svm.c
+++ kvm/arch/x86/kvm/svm/svm.c
@@ -4517,6 +4517,7 @@ static struct kvm_x86_ops svm_x86_ops __
 	.vcpu_put = svm_vcpu_put,
 	.vcpu_blocking = svm_vcpu_blocking,
 	.vcpu_unblocking = svm_vcpu_unblocking,
+	.vcpu_check_block = NULL,
 
 	.update_exception_bitmap = svm_update_exception_bitmap,
 	.get_msr_feature = svm_get_msr_feature,

From patchwork Fri May  7 13:06:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12244555
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CAF18C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 932C66145A
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237126AbhEGNLY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 09:11:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21140 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236544AbhEGNLV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 09:11:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620393021;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=OzNZ8fsZP5SyHIdVZ/cRlR2nzmpijUfIpMsfTWcEav0=;
        b=U0xy1KI9k+El0CQgvgd11hgL1nAtrBMnoWxjztu4S0C/0vThF89kWH7p9djiwEtnUKiaWb
        cFThFdj1cl9e3iSiNfouL58xmQJUudRW4byen8+l/8kjc15iBgoWuf4sMoehqF1xMF2OuW
        SQy74EatT0cD8TBtaOiEpwbhy0nIzmI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-163-scAvktjpMAqONfvlLHsVMw-1; Fri, 07 May 2021 09:10:20 -0400
X-MC-Unique: scAvktjpMAqONfvlLHsVMw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 188D0107ACC7;
        Fri,  7 May 2021 13:10:19 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 1611B19D61;
        Fri,  7 May 2021 13:10:13 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id ABE5540B1EB2; Fri,  7 May 2021 10:10:07 -0300 (-03)
Message-ID: <20210507130923.528132061@redhat.com>
User-Agent: quilt/0.66
Date: Fri, 07 May 2021 10:06:13 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Pei Zhang <pezhang@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 4/4] KVM: VMX: update vcpu posted-interrupt descriptor when
 assigning device
References: <20210507130609.269153197@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For VMX, when a vcpu enters HLT emulation, pi_post_block will:

1) Add vcpu to per-cpu list of blocked vcpus.

2) Program the posted-interrupt descriptor "notification vector" 
to POSTED_INTR_WAKEUP_VECTOR

With interrupt remapping, an interrupt will set the PIR bit for the 
vector programmed for the device on the CPU, test-and-set the 
ON bit on the posted interrupt descriptor, and if the ON bit is clear
generate an interrupt for the notification vector.

This way, the target CPU wakes upon a device interrupt and wakes up
the target vcpu.

Problem is that pi_post_block only programs the notification vector
if kvm_arch_has_assigned_device() is true. Its possible for the
following to happen:

1) vcpu V HLTs on pcpu P, kvm_arch_has_assigned_device is false,
notification vector is not programmed
2) device is assigned to VM
3) device interrupts vcpu V, sets ON bit
(notification vector not programmed, so pcpu P remains in idle)
4) vcpu 0 IPIs vcpu V (in guest), but since pi descriptor ON bit is set,
kvm_vcpu_kick is skipped
5) vcpu 0 busy spins on vcpu V's response for several seconds, until
RCU watchdog NMIs all vCPUs.

To fix this, use the start_assignment kvm_x86_ops callback to kick
vcpus out of the halt loop, so the notification vector is 
properly reprogrammed to the wakeup vector.

Reported-by: Pei Zhang <pezhang@redhat.com>
Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---

v2: add vmx_pi_start_assignment to vmx's kvm_x86_ops

Index: kvm/arch/x86/kvm/vmx/posted_intr.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.c
+++ kvm/arch/x86/kvm/vmx/posted_intr.c
@@ -203,6 +203,25 @@ void pi_post_block(struct kvm_vcpu *vcpu
 	local_irq_enable();
 }
 
+int vmx_vcpu_check_block(struct kvm_vcpu *vcpu)
+{
+	struct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
+
+	if (!irq_remapping_cap(IRQ_POSTING_CAP))
+		return 0;
+
+	if (!kvm_vcpu_apicv_active(vcpu))
+		return 0;
+
+	if (!kvm_arch_has_assigned_device(vcpu->kvm))
+		return 0;
+
+	if (pi_desc->nv == POSTED_INTR_WAKEUP_VECTOR)
+		return 0;
+
+	return 1;
+}
+
 /*
  * Handler for POSTED_INTERRUPT_WAKEUP_VECTOR.
  */
@@ -236,6 +255,26 @@ bool pi_has_pending_interrupt(struct kvm
 		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
 }
 
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count)
+{
+	struct kvm_vcpu *vcpu;
+	int i;
+
+	if (!irq_remapping_cap(IRQ_POSTING_CAP))
+		return;
+
+	/* only care about first device assignment */
+	if (device_count != 1)
+		return;
+
+	/* Update wakeup vector and add vcpu to blocked_vcpu_list */
+	kvm_for_each_vcpu(i, vcpu, kvm) {
+		if (!kvm_vcpu_apicv_active(vcpu))
+			continue;
+
+		kvm_vcpu_kick(vcpu);
+	}
+}
 
 /*
  * pi_update_irte - set IRTE for Posted-Interrupts
Index: kvm/arch/x86/kvm/vmx/posted_intr.h
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.h
+++ kvm/arch/x86/kvm/vmx/posted_intr.h
@@ -95,5 +95,7 @@ void __init pi_init_cpu(int cpu);
 bool pi_has_pending_interrupt(struct kvm_vcpu *vcpu);
 int pi_update_irte(struct kvm *kvm, unsigned int host_irq, uint32_t guest_irq,
 		   bool set);
+void vmx_pi_start_assignment(struct kvm *kvm, int device_count);
+int vmx_vcpu_check_block(struct kvm_vcpu *vcpu);
 
 #endif /* __KVM_X86_VMX_POSTED_INTR_H */
Index: kvm/arch/x86/kvm/vmx/vmx.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/vmx.c
+++ kvm/arch/x86/kvm/vmx/vmx.c
@@ -7727,13 +7727,13 @@ static struct kvm_x86_ops vmx_x86_ops __
 
 	.pre_block = vmx_pre_block,
 	.post_block = vmx_post_block,
-	.vcpu_check_block = NULL,
+	.vcpu_check_block = vmx_vcpu_check_block,
 
 	.pmu_ops = &intel_pmu_ops,
 	.nested_ops = &vmx_nested_ops,
 
 	.update_pi_irte = pi_update_irte,
-	.start_assignment = NULL,
+	.start_assignment = vmx_pi_start_assignment,
 
 #ifdef CONFIG_X86_64
 	.set_hv_timer = vmx_set_hv_timer,
```
