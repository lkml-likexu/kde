#### [PATCH 1/2] mips: replace deprecated EXTRA_CFLAGS with ccflags-y
##### From: Masahiro Yamada <masahiroy@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Masahiro Yamada <masahiroy@kernel.org>
X-Patchwork-Id: 12175581
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B87DEC433ED
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:18:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D25661025
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:18:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236270AbhCaPSB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 11:18:01 -0400
Received: from condef-08.nifty.com ([202.248.20.73]:45436 "EHLO
        condef-08.nifty.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236342AbhCaPRj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 11:17:39 -0400
X-Greylist: delayed 398 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 31 Mar 2021 11:17:38 EDT
Received: from conuserg-08.nifty.com ([10.126.8.71])by condef-08.nifty.com
 with ESMTP id 12VF7Uew010895
        for <kvm@vger.kernel.org>; Thu, 1 Apr 2021 00:07:51 +0900
Received: from localhost.localdomain (133-32-232-101.west.xps.vectant.ne.jp
 [133.32.232.101]) (authenticated)
        by conuserg-08.nifty.com with ESMTP id 12VF77DF021201;
        Thu, 1 Apr 2021 00:07:08 +0900
DKIM-Filter: OpenDKIM Filter v2.10.3 conuserg-08.nifty.com 12VF77DF021201
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nifty.com;
        s=dec2015msa; t=1617203228;
        bh=ARbRFUFLNuhizfOq+rbCISdwf0ZvC9EkFJQtTKtjlps=;
        h=From:To:Cc:Subject:Date:From;
        b=0BXLesIP5v+3wtn3FQqyG2ppqrZdnq9H6gl0+IA5olp+NBiyCMNfCxmwDLQuR2eEI
         fl2kirvxTPzE5h+DkZRpO+kgavsmYNHxX6EA9+PAyIdGzYus1o3X6twC+Trr1bC9sJ
         XLYKukwdDHj7ON3/wu+41FoyMeD6G34UM93Cwa18iw8q+lICyienKgDyKE0iANeqDk
         bYfB0qMC99jkoUkhkEVUxfJIepDIsm7lV3ru0xALDquISA9GngQcrMXyd8ON/31gSm
         RzLmoIJDGR3HGPhB9AUota4bXQ/Tuswa/CExOvGPjpK9qDD5SNrH5OA6LSyNzF/uMV
         GY0ArNoN6PO3Q==
X-Nifty-SrcIP: [133.32.232.101]
From: Masahiro Yamada <masahiroy@kernel.org>
To: linux-mips@linux-mips.org
Cc: Masahiro Yamada <masahiroy@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Huacai Chen <chenhuacai@kernel.org>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-mips@vger.kernel.org
Subject: [PATCH 1/2] mips: replace deprecated EXTRA_CFLAGS with ccflags-y
Date: Thu,  1 Apr 2021 00:06:56 +0900
Message-Id: <20210331150658.38919-1-masahiroy@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As Documentation/kbuild/makefiles.rst says, EXTRA_CFLAGS is deprecated.
Replace it with ccflags-y.

Signed-off-by: Masahiro Yamada <masahiroy@kernel.org>
---

 arch/mips/kvm/Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v6 01/10] file: Export receive_fd() to modules
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yongji Xie <xieyongji@bytedance.com>
X-Patchwork-Id: 12174625
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73ED9C433E0
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 08:07:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 381D7619D7
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 08:07:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234063AbhCaIGu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 04:06:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47362 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234075AbhCaIGX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 04:06:23 -0400
Received: from mail-pj1-x1029.google.com (mail-pj1-x1029.google.com
 [IPv6:2607:f8b0:4864:20::1029])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C2939C06175F
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 01:06:21 -0700 (PDT)
Received: by mail-pj1-x1029.google.com with SMTP id
 q6-20020a17090a4306b02900c42a012202so806693pjg.5
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 01:06:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Qd7q0+7mMIaCO7kNrN03miiLmUUotvU02ar15rGLAYA=;
        b=TC4wgya5iSyGQZApckwILsZ07cID8JY+wSUKJkkjSK6QenG/Nmjt6rFLbaVUVwLWuR
         qZUC8Y0GjUhiGVid8GxHZKbu9gf4fU+lvhfmVfPgGy+5jgQjVK7BNWsvr6SfgOEkycaZ
         5vq2ipI4hpOZ0O2rO+5j+j/r4ClYjWkyP2C+gZCHd4C/hmSUIOJRWa8irRXib6jNL6bu
         kD4W62kB3IbxjCgNwxzpm1RKEIwtcxPZUTI1DX3Y9RXd+XOhqYwQUafQpdnDpvkcgH0M
         D8Gqf8VvrAIYcVLhc6Mm5fymUe/OERG1iFMO5tcrA4RGKFIGu9cfuHfcaCK9xR+LNdNI
         8BIQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Qd7q0+7mMIaCO7kNrN03miiLmUUotvU02ar15rGLAYA=;
        b=pMEv7Z3xnS7aTMVBM0VmihVyL+/sH+GZa4xIJ7XPDfCbyy7oF5HFMbsywB/qeu7lNS
         fr4ZoPbiRDmfZfctijBkWHsGNICEr60ByZ6oQyOOWcRKbxcNsg7CparkCKXCcafkbSDE
         x+QDYW25sZ7YfDjDLaKHqwYeohhHsuD7IjVAlRnnCaj5VY0WBKX1EKE84DRx91fgPLsP
         9rlLTZCnGJK50nXCdlL2GqC1YtREvyAvC2YoOJzQlYuE5qs9czsqk1bJubEkNFU1n2V7
         WUnoLAvBw/kJV77WhoGF+N0zUS0ZXrJ3P8OaFsAFSh1xSwiewo5RTXXR7WzPmAmpSrv/
         u+sg==
X-Gm-Message-State: AOAM530E+CHlG6XDW8ArT4Yr5ojG591KXmNdHwBroMgLL69/14Te912c
        kJ0AIMEF7225LFtsHV7W/xhg
X-Google-Smtp-Source: 
 ABdhPJydrF0nk0d3cE3vx8KgidDGa8Zfry5KovS8f39HDenv+8gD9ih8HKxbhTFZ2J9TJmZpWj0qlg==
X-Received: by 2002:a17:90a:fb83:: with SMTP id
 cp3mr2363661pjb.33.1617177981360;
        Wed, 31 Mar 2021 01:06:21 -0700 (PDT)
Received: from localhost ([139.177.225.243])
        by smtp.gmail.com with ESMTPSA id
 23sm1644744pgo.53.2021.03.31.01.06.20
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 31 Mar 2021 01:06:20 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, hch@infradead.org,
        christian.brauner@canonical.com, rdunlap@infradead.org,
        willy@infradead.org, viro@zeniv.linux.org.uk, axboe@kernel.dk,
        bcrl@kvack.org, corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org
Subject: [PATCH v6 01/10] file: Export receive_fd() to modules
Date: Wed, 31 Mar 2021 16:05:10 +0800
Message-Id: <20210331080519.172-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210331080519.172-1-xieyongji@bytedance.com>
References: <20210331080519.172-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export receive_fd() so that some modules can use
it to pass file descriptor between processes without
missing any security stuffs.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 fs/file.c            | 6 ++++++
 include/linux/file.h | 7 +++----
 2 files changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: arm64: Elect Alexandru as a replacement for Julien as a reviewer
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12175445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 369A2C433ED
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 13:17:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E826361968
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 13:17:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235618AbhCaNQ6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 09:16:58 -0400
Received: from mail.kernel.org ([198.145.29.99]:54328 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235728AbhCaNQ0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 09:16:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1A30761968;
        Wed, 31 Mar 2021 13:16:26 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lRahs-004uEN-1m; Wed, 31 Mar 2021 14:16:24 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Subject: [PATCH] KVM: arm64: Elect Alexandru as a replacement for Julien as a
 reviewer
Date: Wed, 31 Mar 2021 14:16:20 +0100
Message-Id: <20210331131620.4005931-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 suzuki.poulose@arm.com, alexandru.elisei@arm.com, kernel-team@android.com,
 julien.thierry.kdev@gmail.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Julien's bandwidth for KVM reviewing has been pretty low lately,
and Alexandru has accepted to step in and help with the reviewing.

Many thanks to both!

Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/4] kvm: cpuid: adjust the returned nent field of kvm_cpuid2 for KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12175407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1035C001B4
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:33:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2ADC619FA
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:28:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235566AbhCaM1p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 08:27:45 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53946 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235525AbhCaM1K (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 08:27:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617193629;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tIbQKQiXIoTeHIEctRDJOzv7hWKMM1QPTTDvevPM1vE=;
        b=UUiKRxNe0dcn9V2WSu8GK3pimthKIroduRUzIQ914/YxGj1RXEIn6nLnErYdrSPiqKfG0t
        nkIMKRc8Ah48WMsEWnglXeUQqqT/+LmEIiflP1wd0R0mv4XtKN8upfIY6q+7b9nN/QqYgL
        u/uBKcLC89F+wJ7E/Boc8R9olxhT5ls=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-410-B8Jnwc57PViAsuTEdAVRxg-1; Wed, 31 Mar 2021 08:27:06 -0400
X-MC-Unique: B8Jnwc57PViAsuTEdAVRxg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 71F521922961;
        Wed, 31 Mar 2021 12:27:05 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-218.ams2.redhat.com
 [10.36.114.218])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2307F51C39;
        Wed, 31 Mar 2021 12:26:57 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v2 1/4] kvm: cpuid: adjust the returned nent field of
 kvm_cpuid2 for KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
Date: Wed, 31 Mar 2021 14:26:46 +0200
Message-Id: <20210331122649.38323-2-eesposit@redhat.com>
In-Reply-To: <20210331122649.38323-1-eesposit@redhat.com>
References: <20210331122649.38323-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Calling the kvm KVM_GET_[SUPPORTED/EMULATED]_CPUID ioctl requires
a nent field inside the kvm_cpuid2 struct to be big enough to contain
all entries that will be set by kvm.
Therefore if the nent field is too high, kvm will adjust it to the
right value. If too low, -E2BIG is returned.

However, when filling the entries do_cpuid_func() requires an
additional entry, so if the right nent is known in advance,
giving the exact number of entries won't work because it has to be 
increased by one.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 arch/x86/kvm/cpuid.c | 35 ++++++++++++++++++-----------------
 1 file changed, 18 insertions(+), 17 deletions(-)

```
#### [PATCH 1/2] KVM: Account memory allocations for 'struct kvm_vcpu'From: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174151
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C37EC433DB
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 02:31:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E0FEA619BB
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 02:31:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233240AbhCaCbC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 22:31:02 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59908 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233069AbhCaCab (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 22:30:31 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BECD4C06175F
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 19:30:31 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id o129so646823ybg.23
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 19:30:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=uV4x6+EdkMXZhg7wMEUNEc/cXMhh5NFoJhoLXAZa4XA=;
        b=hyxAm79V1CoNeCcaWjPRj6j5vKrjB66hHPXwlccvH/3YB10lOq1utFmsZxYp8F3HpG
         WOVVmSaroJAJOzz4lNDIbz7ei9dCL3cKP4c17RXAj462cjZTMs8oecds+x1bGGRaLRVE
         vmKYsAvI44f3RBbPqlZk3+kcxA5yCOsa4zYDyKO9Y6bRuhE8JVlAQhJa+kJ+6Wv/2Ghz
         4xMYiQHQSD02fcexUHEgrkqc/uqoNUwmNr9s/ylUQx15EFvA2VaXTuppXEfG0Eg2XXWz
         B2M6KfrdkALt0ZTB/hRS7drJULF5z50LaOIqMSYoWDCtbYm31kQwZ7CcI9NMzcJM3792
         c7fw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=uV4x6+EdkMXZhg7wMEUNEc/cXMhh5NFoJhoLXAZa4XA=;
        b=lmGLfYDLavfy7gaEUnAvl6FN7lABcK2nA2nNYGiNUR4XCd5TGgzGWclz4wicK/GRE5
         Eu+vGWFbW5TNpcnUrMLNMBoLf25pPt7FOO/smbztMc6LN3B+iuokijY2R7DX4b0lms9T
         NxABHKIjPWP0z+pzmQDAhU57OCOdYlyZDAGYB1yziHH03gBKVJPKLnFIM5+4m/RXgSD9
         v5daLAA77gXD3CVLxm84t9eqcdPbz8K9SYZJ/13KMDdDJGlTIe3jSP1QrfIuEWa1g+YS
         h8hZLeqoTI+zsif/98B0vRU8I/RFzgrUcL+XYe94HgaZ31agbc2yeBbXaNMMA9pjEGRw
         Dd2A==
X-Gm-Message-State: AOAM532bbf4YAueqHvJ+z4tDhIgJaTifb6+rtuRdYiciFs6vI/QIZAG+
        kgT3mLvyi5AnXPERdeFdG5IPVRIJ86E=
X-Google-Smtp-Source: 
 ABdhPJyoJU2Rdi/to8R+u7+o3IMo1VtUs59XwyVJUPXLriy3TmcY1tCAqdD1U35l7io8CdK4mvxxJmJF+eM=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a25:c588:: with SMTP id
 v130mr1592057ybe.312.1617157831002;
 Tue, 30 Mar 2021 19:30:31 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 19:30:24 -0700
In-Reply-To: <20210331023025.2485960-1-seanjc@google.com>
Message-Id: <20210331023025.2485960-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210331023025.2485960-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 1/2] KVM: Account memory allocations for 'struct kvm_vcpu'
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use GFP_KERNEL_ACCOUNT for the vCPU allocations, the vCPUs are very much
tied to a single task/VM.  For x86, the allocations were accounted up
until the allocation code was moved to common KVM.  For all other
architectures, vCPU allocations were never previously accounted, but only
because most architectures lack accounting in general (for KVM).

Fixes: e529ef66e6b5 ("KVM: Move vcpu alloc and init invocation to common code")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: SVM: Use online_vcpus, not created_vcpus, to iterate over vCPUs
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174261
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3903BC433E1
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 03:20:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14106619BD
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 03:20:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233482AbhCaDTt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 23:19:49 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42336 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233368AbhCaDTp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 23:19:45 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7BC15C061574
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 20:19:45 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id k189so773429ybb.17
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 20:19:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=VqSy53IyDnNL/CdQDhT4nMQIBeIb4g0Xh5NCqPSTxiY=;
        b=L3vxRku6tHP9GMz0/JT4UHLAicdp9dcZ+g2J1/dysm0wZpJgxaAjfxTZRGvOqRDoJ5
         5GG5sUkB9HTsjhb7ZcW+2cqWXHS02dQP1cU9Jq70424h6LdhCvBWTWi2Qkb61lFbCmHO
         QF6c6Ih9rAr2eQdCd2pJtRZYC0dBaI0kSCdr+sMMgAg5/lzXj6+0d07tR1OA1a34arnU
         0DF79I759sgJdeCnkcU7kKJCHSg3fuFJRaVtnpmrXCuZnuaRW3w4dGNmlSBalHYxoaW9
         BhI2lgbinJfb1IVflxdD8n2URlBSoiGN/Kq7x1JDvwfuCVb0nwKe97+7cLSKniU4BIdS
         E+2g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=VqSy53IyDnNL/CdQDhT4nMQIBeIb4g0Xh5NCqPSTxiY=;
        b=SP32Lk8AKf2UMaqNSJZV4HMbzup++f89Fhu8LsEkjQBPfUe+bvo/daxbTJ50xglTzI
         8zOuh++kPoleuNFfN5Pd5ueuK6sBz+TDQT4WqiISHhYVBLdWY5rLV3m2SA6BHHrGd3fr
         6HfkhDqAG2KqjDu+/ClZZvCZygQlscaz3sdcSzxOYlFlG5tN1tQxHuJcfy/XuOzkwLgx
         cSNrXzdBsgRkwinUZMUea9FQAm92mmTqmKiMEnt0GmJPb5HjKw2DUgyfPske0ywgQ5n6
         PgP3LP09iulKLwI750TyrvFqpUzSqxfA8f2bs9DRTlM96g9shw00uvWKhX4+c2Re+z2B
         MdQg==
X-Gm-Message-State: AOAM531Rex02CDk/DGgevJruoksRF6pVOis3q8PXfmERhXzArMwdpmDV
        TUJDryvvjy0NIS/HNIAk/gRn6s327V8=
X-Google-Smtp-Source: 
 ABdhPJwPfX1ZIe9KPSZ+B/9YfLJdMnVqXzEt0iRHW7WxV7gQCnqgXa6cZFbf1Pufpv66ADvtJZu7i2zqXv8=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a25:9ac6:: with SMTP id
 t6mr1707731ybo.287.1617160784800;
 Tue, 30 Mar 2021 20:19:44 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 20:19:34 -0700
In-Reply-To: <20210331031936.2495277-1-seanjc@google.com>
Message-Id: <20210331031936.2495277-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210331031936.2495277-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 1/3] KVM: SVM: Use online_vcpus, not created_vcpus, to iterate
 over vCPUs
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the kvm_for_each_vcpu() helper to iterate over vCPUs when encrypting
VMSAs for SEV, which effectively switches to use online_vcpus instead of
created_vcpus.  This fixes a possible null-pointer dereference as
created_vcpus does not guarantee a vCPU exists, since it is updated at
the very beginning of KVM_CREATE_VCPU.  created_vcpus exists to allow the
bulk of vCPU creation to run in parallel, while still correctly
restricting the max number of max vCPUs.

Fixes: ad73109ae7ec ("KVM: SVM: Provide support to launch and run an SEV-ES guest")
Cc: stable@vger.kernel.org
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/sev.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Fix potential memory access error
##### From: Yang Li <yang.lee@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Li <yang.lee@linux.alibaba.com>
X-Patchwork-Id: 12174849
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67C1EC433DB
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 09:16:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30796619D8
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 09:16:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234661AbhCaJPh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 05:15:37 -0400
Received: from out30-44.freemail.mail.aliyun.com ([115.124.30.44]:47953 "EHLO
        out30-44.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234349AbhCaJP0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 05:15:26 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R861e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04426;MF=yang.lee@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0UTwZ0zg_1617182123;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:yang.lee@linux.alibaba.com
 fp:SMTPD_---0UTwZ0zg_1617182123)
          by smtp.aliyun-inc.com(127.0.0.1);
          Wed, 31 Mar 2021 17:15:24 +0800
From: Yang Li <yang.lee@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Yang Li <yang.lee@linux.alibaba.com>
Subject: [PATCH] KVM: x86: Fix potential memory access error
Date: Wed, 31 Mar 2021 17:15:22 +0800
Message-Id: <1617182122-112315-1-git-send-email-yang.lee@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using __set_bit() to set a bit in an integer is not a good idea, since
the function expects an unsigned long as argument, which can be 64bit wide.
Coverity reports this problem as

High:Out-of-bounds access(INCOMPATIBLE_CAST)
CWE119: Out-of-bounds access to a scalar
Pointer "&vcpu->arch.regs_avail" points to an object whose effective
type is "unsigned int" (32 bits, unsigned) but is dereferenced as a
wider "unsigned long" (64 bits, unsigned). This may lead to memory
corruption.

/home/heyuan.shy/git-repo/linux/arch/x86/kvm/kvm_cache_regs.h:
kvm_register_is_available

Just use BIT instead.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Yang Li <yang.lee@linux.alibaba.com>
---
 arch/x86/kvm/kvm_cache_regs.h | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/2] KVM: x86: Prevent 'hv_clock->system_time' from going negative in kvm_guest_time_update()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12175421
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7771BC43600
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:42:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 365DA61959
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 12:42:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235665AbhCaMmO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 08:42:14 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57978 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235613AbhCaMll (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 08:41:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617194500;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=CJ7CAhfyI891QLLS7moyInEYvvulvtUZ6HJ9gvElXsM=;
        b=bwburUgPmMENYMuplvzqS4fjGg+Wt/ylsj7E84waA6iyBgk83tz5moy6nvmOJkesT3/GFF
        6FZ81rCB+4/MCXPbXDnfD60hTUVFRy+ri75oHB/ujHkK7yLGmzKCkmz/RkYMOp8994pkPg
        gJiixwGYW2Z6t8yeH8sA32KFwWpcwP4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-473-oLRSX5A8OnyGFcPonUWJWg-1; Wed, 31 Mar 2021 08:41:39 -0400
X-MC-Unique: oLRSX5A8OnyGFcPonUWJWg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 97D178143FE;
        Wed, 31 Mar 2021 12:41:37 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 64BC360861;
        Wed, 31 Mar 2021 12:41:35 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/2] KVM: x86: Prevent 'hv_clock->system_time' from going
 negative in kvm_guest_time_update()
Date: Wed, 31 Mar 2021 14:41:29 +0200
Message-Id: <20210331124130.337992-2-vkuznets@redhat.com>
In-Reply-To: <20210331124130.337992-1-vkuznets@redhat.com>
References: <20210331124130.337992-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When guest time is reset with KVM_SET_CLOCK(0), it is possible for
'hv_clock->system_time' to become a small negative number. This happens
because in KVM_SET_CLOCK handling we set 'kvm->arch.kvmclock_offset' based
on get_kvmclock_ns(kvm) but when KVM_REQ_CLOCK_UPDATE is handled,
kvm_guest_time_update() does (masterclock in use case):

hv_clock.system_time = ka->master_kernel_ns + v->kvm->arch.kvmclock_offset;

And 'master_kernel_ns' represents the last time when masterclock
got updated, it can precede KVM_SET_CLOCK() call. Normally, this is not a
problem, the difference is very small, e.g. I'm observing
hv_clock.system_time = -70 ns. The issue comes from the fact that
'hv_clock.system_time' is stored as unsigned and 'system_time / 100' in
compute_tsc_page_parameters() becomes a very big number.

Use 'master_kernel_ns' instead of get_kvmclock_ns() when masterclock is in
use and get_kvmclock_base_ns() when it's not to prevent 'system_time' from
going negative.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 19 +++++++++++++++++--
 1 file changed, 17 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: x86/mmu: Remove spurious clearing of dirty bit from TDP MMU SPTE
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12174041
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8F5C2C433E0
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 00:50:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63730619D7
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 00:50:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232789AbhCaAuB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 20:50:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38404 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232467AbhCaAts (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 20:49:48 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 82BF6C061574
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 17:49:48 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id g9so449525ybc.19
        for <kvm@vger.kernel.org>; Tue, 30 Mar 2021 17:49:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=UCRZL7KtC6hAv8hxA1ExjdbtxqOT/SBsALkv1r7beao=;
        b=uHMg0cFT+fEKMEWK8V5K3WzXglXjI7x+kKFOaGNsIsv6Vfn2zin+T7x/d2lJP90lXT
         Bd1LehSBMHPCt+dMCElqKJ435JiFDEPP/E1af1DpZu+HvHCNlqiu/IapnYDDR0EA2TwT
         sJr6BMcANM2brzI7xSGl54UIt91ICOe4/F77wckB7rBaClqSgedxGaIQELnAa1dB+tjj
         55AViueUvUML00898EUsCCegs92b1Z+UjyBpXAOY7gA9zmxB48mrQLhBpeVUrgebJROs
         PVxtivTaY/poRr1idiyOd7KpyqVI2wMRPKjz1plIXwAZoO4ys6OKSG7sJXs0NMq91n+A
         pQ5Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=UCRZL7KtC6hAv8hxA1ExjdbtxqOT/SBsALkv1r7beao=;
        b=o77qG0ONT50uMZrCNQPQXeRaWbErG7jLPxs/Ndo560AC5FMeJulor5eBDb3UaLma1e
         X235/ti5fE6TOizR9dztbMVbwqTc9ClH36IV8HPGq3YqSySMBPGaCcEGLIhwUs+slkRN
         V+ikRTaNZrm6IHJCE5R4yx3NMUNVQ1BM0HQa3+04a1YZkGE+PjvmcksF89lYcVYSx+dc
         6APhKVGnX80kysO5008lZJ79QWMNx9M8dhNVDickLIK7hMqKP8MO1BaYvV84VZalC7cY
         1rmg0z1f/uSws+POCteWF7/UiBYXfujixSBQFrrlIrx6uveVyC+L6miPDs/eYtqbUwu1
         tf2Q==
X-Gm-Message-State: AOAM5336ROKFEbu3LBWcaaO8qMxfTwIsHYaPwfrWBjsQMxpRUtY7aaTv
        CHRs0JwgQh0GHkHeTu0kfSJpHt4FATA=
X-Google-Smtp-Source: 
 ABdhPJzeaxpSyGdpS0Vl6Xq9PRSLWwR78jRGbWUD35V9+T1hq4V+hfns3QOfQm1DNxUu3k8upa50kpXs6ps=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c6b:5d63:9b3b:4a77])
 (user=seanjc job=sendgmr) by 2002:a05:6902:70e:: with SMTP id
 k14mr1263170ybt.286.1617151787807; Tue, 30 Mar 2021 17:49:47 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 30 Mar 2021 17:49:41 -0700
In-Reply-To: <20210331004942.2444916-1-seanjc@google.com>
Message-Id: <20210331004942.2444916-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210331004942.2444916-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 1/2] KVM: x86/mmu: Remove spurious clearing of dirty bit from
 TDP MMU SPTE
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't clear the dirty bit when aging a TDP MMU SPTE (in response to a MMU
notifier event).  Prematurely clearing the dirty bit could cause spurious
PML updates if aging a page happened to coincide with dirty logging.

Note, tdp_mmu_set_spte_no_acc_track() flows into __handle_changed_spte(),
so the host PFN will be marked dirty, i.e. there is no potential for data
corruption.

Fixes: a6a0b05da9f3 ("kvm: x86/mmu: Support dirty logging for the TDP MMU")
Cc: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 01/13] KVM: x86/mmu: Re-add const qualifier in kvm_tdp_mmu_zap_collapsible_sptes
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12176329
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 06F3DC43460
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 21:09:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0EB86108B
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 21:09:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232763AbhCaVJ2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 17:09:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47580 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232698AbhCaVJE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Mar 2021 17:09:04 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BEDE0C061574
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 14:09:03 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id c1so2347755qke.8
        for <kvm@vger.kernel.org>; Wed, 31 Mar 2021 14:09:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=shAgYfqF+cypy0/KRQK7wirhgcU0wHOuMRYUsNPex7o=;
        b=rQ0sJ7kmvyis0+Nu0wXg39UJkTyoKd5AR460peD4kAaJQY7hv028MU+6T3yUeV7aGY
         KsRRnH4PJIN6B5U2WoY/utuUlgrCKLdnBY/0FLbP34F2KCXkwWEj3Wsdh+BNM/mMvZXF
         mLLiV4x/eZ1tdOxm3ODWvVGalustQiSQfcgDLGrt67EVJ9Zm1xzN/oyNlrWxw2jfTHTo
         O42JEKWWBMt6c6guXYYqM9G4eFUP4Qbx0lwB87CRa8ggm/QvwDgbb2fQERyrE4x1jgkL
         oGO++kcbGEYdFbrjkgFIKt10dEKK5q+ZSrMX7qDX3gp+7nV6/syHZSQYlSpaOt2jWu8N
         1eBA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=shAgYfqF+cypy0/KRQK7wirhgcU0wHOuMRYUsNPex7o=;
        b=cW5QQHUM8yeL2jEoTRIfwDZSiebE6ADY78FGC/S73URpk+7VcGfF3IS/PYPF/QP1LF
         MZ2xIdZLQmqjfIXpEVvb93OlY6Ix8vj/DGg7C39Tg3W+sOtNjSVx7l59CNk5WQUxhlRT
         fzdI17uynF77Im/vY/bi2c6DqUqg7XctsIediFEu0bsx/zhWCX4N+jtixqQT90NB9m/q
         Gr0Vx8JyVJpTbIWNVUk8cBgwGSWHWdjQtRsB0e0IJ3N5AoijtoE2qTf1/XD2cjTkVMus
         QxUq4ftovVrcc7eIfqht5w2xP2Br6IltOwt9SKEUq3LC91NinaaDf13+g8XfehZ9W0+C
         QPnQ==
X-Gm-Message-State: AOAM5316CYih+p73N2Orw/ScKz7rogqhLNmP/q65AUImGCfRseK96CZ3
        68H/OF1/QmfeArxAI5l18FYERWntXo6/
X-Google-Smtp-Source: 
 ABdhPJzHLA2UAcsevKJygjkqztrpxd2hRINkIpoVNWxeuBp/FZPAb45lJOMhylWdILYORIDxrpW7yvxIyNEH
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:8026:6888:3d55:3842])
 (user=bgardon job=sendgmr) by 2002:ad4:5a14:: with SMTP id
 ei20mr4994453qvb.1.1617224942887; Wed, 31 Mar 2021 14:09:02 -0700 (PDT)
Date: Wed, 31 Mar 2021 14:08:29 -0700
In-Reply-To: <20210331210841.3996155-1-bgardon@google.com>
Message-Id: <20210331210841.3996155-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210331210841.3996155-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 01/13] KVM: x86/mmu: Re-add const qualifier in
 kvm_tdp_mmu_zap_collapsible_sptes
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
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

kvm_tdp_mmu_zap_collapsible_sptes unnecessarily removes the const
qualifier from its memlsot argument, leading to a compiler warning. Add
the const annotation and pass it to subsequent functions.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/mmu.c          | 10 +++++-----
 arch/x86/kvm/mmu/mmu_internal.h |  5 +++--
 arch/x86/kvm/mmu/tdp_mmu.c      |  4 ++--
 arch/x86/kvm/mmu/tdp_mmu.h      |  2 +-
 include/linux/kvm_host.h        |  2 +-
 5 files changed, 12 insertions(+), 11 deletions(-)

```
#### [PATCH v14 01/13] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12175587
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D55D7C4360C
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:23:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A738461026
	for <kvm@archiver.kernel.org>; Wed, 31 Mar 2021 15:23:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236289AbhCaPX3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 31 Mar 2021 11:23:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50436 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236256AbhCaPXT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 31 Mar 2021 11:23:19 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12VF3Ia3031141;
        Wed, 31 Mar 2021 11:23:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=eddZYayLgbK9LT7a0g2otyK+KzhpC5hr6wrwydXZlus=;
 b=oLJKsDjzbNxZoRh05dCZBui73giOP9ggH/N/7gX+UqMae7vwtCwJ/KyFt47meCFFn+w8
 v2uJo2KzEriNdaDVN7grqID/1YGTW6PHDpLXefRYkL+H240H2FgV6XLWGWKfDpmWwMTn
 nxAMeN968YGXfkkncgIZXnRGPPjR5fCHslJ/wh5bCl/0azSJvUl8koViib8ThrC0ef2w
 kvdsrOOZzxnhVvFAZc0dOESjSrQMzZF/AFONOdgJionLJL/b8926ta41+C298KwUVEU+
 JbTtIic+s2WHmI0taGub8qBIP/wsICIkZJ/CcVFeuzKHfGbryFEmwRDD2JURz3wyKs9D NQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37mu4u9d4a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 11:23:17 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12VF3rmP033896;
        Wed, 31 Mar 2021 11:23:17 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37mu4u9d3t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 11:23:17 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12VF2ARQ012103;
        Wed, 31 Mar 2021 15:23:16 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma01dal.us.ibm.com with ESMTP id 37maawfd6w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 31 Mar 2021 15:23:16 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12VFNCUX8257814
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 31 Mar 2021 15:23:12 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9F5616E05B;
        Wed, 31 Mar 2021 15:23:12 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9C48C6E04E;
        Wed, 31 Mar 2021 15:23:10 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.146.149])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed, 31 Mar 2021 15:23:10 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>, stable@vger.kernel.org
Subject: [PATCH v14 01/13] s390/vfio-ap: fix circular lockdep when
 setting/clearing crypto masks
Date: Wed, 31 Mar 2021 11:22:44 -0400
Message-Id: <20210331152256.28129-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20210331152256.28129-1-akrowiak@linux.ibm.com>
References: <20210331152256.28129-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: K5X4BCybdBzZMQPtflRUigGsJwY4_CMc
X-Proofpoint-GUID: oPgbMmxDQYHXPxfGLkWPG6P_xMLQAv8Y
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-31_06:2021-03-31,2021-03-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 impostorscore=0
 adultscore=0 malwarescore=0 lowpriorityscore=0 bulkscore=0 mlxlogscore=999
 priorityscore=1501 phishscore=0 mlxscore=0 clxscore=1015 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103300000
 definitions=main-2103310107
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch fixes a lockdep splat introduced by commit f21916ec4826
("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated").
The lockdep splat only occurs when starting a Secure Execution guest.
Crypto virtualization (vfio_ap) is not yet supported for SE guests;
however, in order to avoid this problem when support becomes available,
this fix is being provided.

The circular locking dependency was introduced when the setting of the
masks in the guest's APCB was executed while holding the matrix_dev->lock.
While the lock is definitely needed to protect the setting/unsetting of the
matrix_mdev->kvm pointer, it is not necessarily critical for setting the
masks; so, the matrix_dev->lock will be released while the masks are being
set or cleared.

Keep in mind, however, that another process that takes the matrix_dev->lock
can get control while the masks in the guest's APCB are being set or
cleared as a result of the driver being notified that the KVM pointer
has been set or unset. This could result in invalid access to the
matrix_mdev->kvm pointer by the intervening process. To avoid this
scenario, two new fields are being added to the ap_matrix_mdev struct:

struct ap_matrix_mdev {
	...
	bool kvm_busy;
	wait_queue_head_t wait_for_kvm;
   ...
};

The functions that handle notification that the KVM pointer value has
been set or cleared will set the kvm_busy flag to true until they are done
processing at which time they will set it to false and wake up the tasks on
the matrix_mdev->wait_for_kvm wait queue. Functions that require
access to matrix_mdev->kvm will sleep on the wait queue until they are
awakened at which time they can safely access the matrix_mdev->kvm
field.

Fixes: f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c     | 308 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 95 deletions(-)

```
