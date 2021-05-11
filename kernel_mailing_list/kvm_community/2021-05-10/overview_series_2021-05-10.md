#### [PATCH 1/6] iommu: remove the unused dev_has_feat method
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12247029
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81338C43461
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 06:54:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 567DE6143C
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 06:54:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230135AbhEJGzi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 02:55:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46336 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230098AbhEJGzf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 02:55:35 -0400
Received: from bombadil.infradead.org (bombadil.infradead.org
 [IPv6:2607:7c80:54:e::133])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BEA10C061573
        for <kvm@vger.kernel.org>; Sun,  9 May 2021 23:54:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20210309; h=Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender
        :Reply-To:Content-Type:Content-ID:Content-Description;
        bh=0VMSk2WoZ7U5DtJ0FPU/Vhd6vJz43QHbgxIeBWhNb/I=;
 b=KFyjDO1zPsK6JPBlXOAElYMkwI
        KQzyEp3R7D5caVRr1N0oJ2D2CUAqaQAoEb4FUeqm6numcnbXvftlVFFu+Qx2DprmftXow1bpkwRpr
        FCw9/Peq73NhBWMt7///LEEBCn58efP6ITA3zURBLg5rt8ivstn41DWHbhzur9273Y7y8SUPr00td
        3G59w9MS8E7jhRNYehv5MASC8AUJBOUJjw5TMYtIX44aHXInsvZI8GnbUVJ3TgDTRzfl14dsv81Ev
        x3NZjmxNebU+sYoOjebp8qey508RCAP6LMXHhiK+b/q5rtLDeIVGwWGgZ5TvjbV7Xw1E6wM435xux
        lwXARPlg==;
Received: from [2001:4bb8:198:fbc8:e179:16d2:93d1:8e1] (helo=localhost)
        by bombadil.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lfznu-008Lo5-Bp; Mon, 10 May 2021 06:54:10 +0000
From: Christoph Hellwig <hch@lst.de>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Will Deacon <will@kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Jason Gunthorpe <jgg@ziepe.ca>,
        linux-arm-kernel@lists.infradead.org,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH 1/6] iommu: remove the unused dev_has_feat method
Date: Mon, 10 May 2021 08:54:00 +0200
Message-Id: <20210510065405.2334771-2-hch@lst.de>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210510065405.2334771-1-hch@lst.de>
References: <20210510065405.2334771-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 bombadil.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This method is never actually called.  Simplify the instance in
intel-iommu that is directly called by inlining the relevant code.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c |  1 -
 drivers/iommu/intel/iommu.c                 | 67 ++-------------------
 include/linux/iommu.h                       |  4 +-
 3 files changed, 7 insertions(+), 65 deletions(-)

```
#### [PATCH v6 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12248501
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id B618EC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:19:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96F286101B
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:19:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234947AbhEJPUU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 11:20:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45420 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234648AbhEJPSy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 11:18:54 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B7502C06175F
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 07:48:41 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id
 o14-20020a05620a130eb02902ea53a6ef80so11709100qkj.6
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 07:48:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=pXf+wxEHe7OgFZweagRPX8zYZei+f+6Ny/B00rMUo8Y=;
        b=kdxiaN5tbOjVAa/SmKd17sTlrKysTv+CTVq7HDDGmRnKvOknp7DCMROGUuxsuYbMgJ
         hmtkw84JovY2kusL7hmM7XMii4LrevXiRtv528IiVINfN+2hYtl2na+zo+F2mar1TXAw
         R9T/wG0yWvAYo7s8p66FhH3OmJs2/X5huT7g6vc7bqnCo8GiuJnigtoAZU5DmdoWNIkv
         Q7Qf2vhrulnU0GRsTGQ/uO4O65nOVrcqHt+RW6Da2zzWjsIwx3QZ6ei+5MxDs3amkFR8
         LgjNj0AIcCORaVvf3n6qOwhhkuYAmzqAQYvKf57wj8VuwoWfQoGnF45P2WvEd9vwlJmg
         3wgg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=pXf+wxEHe7OgFZweagRPX8zYZei+f+6Ny/B00rMUo8Y=;
        b=nIsKkS++AkIGIFzC2w7JGVGYMpLqurN2bGiiLedpnxjg+DxKsNzOUvJ2yZqJd2OCDd
         ZlSmH2Hk4iLcxc+HgyWgmISrwcNWZMBvw79o71iZuxqP/GVBpvcXu5igevctqalg1p4X
         bY3QsakwTfoWeCGjFWkUoj2Lz5Nfwm/rK0ZusJWhog3+l4xk3m/F+UOB17FZ+Ioo9ywN
         39r1fe4QCNfprUwwuH6wiizotlOCkFPrOjBrKnoeyzcpWxHDTQ89sS2U+ptOlipYjlep
         MHfleysQ72/pBfEkUmu8GJTo2ZeW9zo1yPrN+DQrQWTUI63HLXPjHRrvo8ePC3ppTJzQ
         perg==
X-Gm-Message-State: AOAM531Cey4kraLBAXXE/olVUndmHztdbfYeNh2NA+mg2/O+Zz9dI1TK
        WSDrP+yxnU/J0snaieXAzOk4NB8Jh7GQtnkE
X-Google-Smtp-Source: 
 ABdhPJwVpttdjaULEKJDQIArIBE5aXJOXZGGdyJ3sSezasaeoOCNo+3rXOaYTQWzCE144HM78JTFpH23eeAlzni9
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:3396:9513:fac0:8ec7])
 (user=aaronlewis job=sendgmr) by 2002:a0c:e30c:: with SMTP id
 s12mr24109312qvl.47.1620658120802; Mon, 10 May 2021 07:48:40 -0700 (PDT)
Date: Mon, 10 May 2021 07:48:33 -0700
In-Reply-To: <20210510144834.658457-1-aaronlewis@google.com>
Message-Id: <20210510144834.658457-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20210510144834.658457-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v6 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: David Edmondson <david.edmondson@oracle.com>
---
 Documentation/virt/kvm/api.rst  | 19 +++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 37 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++
 5 files changed, 104 insertions(+), 4 deletions(-)

```
#### [PATCH 52/53] docs: virt: kvm: avoid using UTF-8 chars
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12247597
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9CD1C43470
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 10:34:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFC566191D
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 10:34:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231552AbhEJKfr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 06:35:47 -0400
Received: from mail.kernel.org ([198.145.29.99]:41942 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232394AbhEJKea (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 06:34:30 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 937936191F;
        Mon, 10 May 2021 10:28:12 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1620642492;
        bh=FKJ2BSwW7gr1uZrtyjei+5LqG3f0DEatUOETKXaA9GU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=VB4LDqHWa0jICnzjz6LZ8EPfuGQiGos/TUnZer+Q7Cns5TyW0eko830dk0vao5Gxh
         ur9RgxRQNl7i8qBqhdxZI528ZDztPyzP4BLYGVyv3zjFBv3UDFfGpg/nRkyRRG+Ztx
         OtAbXlomPxG8gQvr4sSupinHn/8qM+yN26+Ez/0pr23gaVlsgZV8+SF8+mUzmyFDbS
         O3UC5XfmjGjFn+2RINooSZluHbfAn4cNULRUlmudessoCnNQBi/ll2MdYScMKjitOb
         /+6YqywSgdDQEW5rrwuzBxhD5Zqvsbsr4+PugQEq9VL5dS6Iwu162pqZzZz39wPsZe
         QrxRPJLbpjxPg==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1lg38z-000UYW-NH; Mon, 10 May 2021 12:28:09 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 52/53] docs: virt: kvm: avoid using UTF-8 chars
Date: Mon, 10 May 2021 12:27:04 +0200
Message-Id: 
 <5dae95d7e1cc267c3de9499e3962b97dd998049a.1620641727.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1620641727.git.mchehab+huawei@kernel.org>
References: <cover.1620641727.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While UTF-8 characters can be used at the Linux documentation,
the best is to use them only when ASCII doesn't offer a good replacement.
So, replace the occurences of the following UTF-8 characters:

	- U+00a0 (' '): NO-BREAK SPACE
	- U+2013 ('–'): EN DASH
	- U+2014 ('—'): EM DASH

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/api.rst                | 28 +++++++++----------
 .../virt/kvm/running-nested-guests.rst        | 12 ++++----
 2 files changed, 20 insertions(+), 20 deletions(-)

```
#### [GIT PULL] KVM updates for Linux 5.13-rc2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12249205
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6408CC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 18:14:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3148661469
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 18:14:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231271AbhEJSPw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 14:15:52 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35651 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230165AbhEJSPv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 14:15:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620670485;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=DpuazqPXEj5SkAFURKacNphDW7TZ+kvKc2tK8caPseU=;
        b=Cxeyzr97BUqd7oCdqKCClBsQSC6I+Hqj5gjyqOiekF9zTBtSgCftXmahP2pKCpfAz5gGqM
        gbOAQ+QHF+YaN1PK5xOnGnHP7Qi5BDfirYIASGEt7XmhHuQt5LaLZK1pZmV8O15Fx8tpOR
        QZU9adZsvsR7vBbcfx/v1jAatBcXLuI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-549-Pei9L6tuNg6vPzbftl4s-Q-1; Mon, 10 May 2021 14:14:43 -0400
X-MC-Unique: Pei9L6tuNg6vPzbftl4s-Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 983BA195D560;
        Mon, 10 May 2021 18:14:42 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4A18D14103;
        Mon, 10 May 2021 18:14:42 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM updates for Linux 5.13-rc2
Date: Mon, 10 May 2021 14:14:41 -0400
Message-Id: <20210510181441.351452-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9ccce092fc64d19504fa54de4fd659e279cc92e7:

  Merge tag 'for-linus-5.13-ofs-1' of git://git.kernel.org/pub/scm/linux/kernel/git/hubcap/linux (2021-05-02 14:13:46 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to ce7ea0cfdc2e9ff31d12da31c3226deddb9644f5:

  KVM: SVM: Move GHCB unmapping to fix RCU warning (2021-05-07 06:06:23 -0400)

Thomas Gleixner and Michael Ellerman had some KVM changes in their
late merge window pull requests, but there are no conflicts.

----------------------------------------------------------------
* Lots of bug fixes.

* Fix virtualization of RDPID

* Virtualization of DR6_BUS_LOCK, which on bare metal is new in
  the 5.13 merge window

* More nested virtualization migration fixes (nSVM and eVMCS)

* Fix for KVM guest hibernation

* Fix for warning in SEV-ES SRCU usage

* Block KVM from loading on AMD machines with 5-level page tables,
  due to the APM not mentioning how host CR4.LA57 exactly impacts
  the guest.

----------------------------------------------------------------
Benjamin Segall (1):
      kvm: exit halt polling on need_resched() as well

Bill Wendling (1):
      selftests: kvm: remove reassignment of non-absolute variables

Chenyi Qiang (1):
      KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit

Colin Ian King (1):
      KVM: x86: Fix potential fput on a null source_kvm_file

David Matlack (1):
      kvm: Cap halt polling at kvm->max_halt_poll_ns

Kai Huang (2):
      KVM: x86/mmu: Avoid unnecessary page table allocation in kvm_tdp_mmu_map()
      KVM: x86/mmu: Fix kdoc of __handle_changed_spte

Maxim Levitsky (5):
      KVM: nSVM: fix a typo in svm_leave_nested
      KVM: nSVM: fix few bugs in the vmcb02 caching logic
      KVM: nSVM: leave the guest mode prior to loading a nested state
      KVM: nSVM: always restore the L1's GIF on migration
      KVM: nSVM: remove a warning about vmcb01 VM exit reason

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Fix conversion to gfn-based MMU notifier callbacks

Paolo Bonzini (1):
      KVM: X86: Expose bus lock debug exception to guest

Sean Christopherson (17):
      KVM: VMX: Do not advertise RDPID if ENABLE_RDTSCP control is unsupported
      KVM: x86: Emulate RDPID only if RDTSCP is supported
      KVM: SVM: Inject #UD on RDTSCP when it should be disabled in the guest
      KVM: x86: Move RDPID emulation intercept to its own enum
      KVM: VMX: Disable preemption when probing user return MSRs
      KVM: SVM: Probe and load MSR_TSC_AUX regardless of RDTSCP support in host
      KVM: x86: Add support for RDPID without RDTSCP
      KVM: VMX: Configure list of user return MSRs at module init
      KVM: VMX: Use flag to indicate "active" uret MSRs instead of sorting list
      KVM: VMX: Use common x86's uret MSR list as the one true list
      KVM: VMX: Disable loading of TSX_CTRL MSR the more conventional way
      KVM: x86: Export the number of uret MSRs to vendor modules
      KVM: x86: Move uret MSR slot management to common x86
      KVM: x86: Tie Intel and AMD behavior for MSR_TSC_AUX to guest CPU model
      KVM: x86: Hide RDTSCP and RDPID if MSR_TSC_AUX probing failed
      KVM: x86: Prevent KVM SVM from loading on kernels with 5-level paging
      KVM: SVM: Invert user pointer casting in SEV {en,de}crypt helpers

Shahin, Md Shahadat Hossain (1):
      kvm/x86: Fix 'lpages' kvm stat for TDM MMU

Siddharth Chandrasekaran (2):
      doc/kvm: Fix wrong entry for KVM_CAP_X86_MSR_FILTER
      KVM: x86: Hoist input checks in kvm_add_msr_filter()

Stefan Raspl (1):
      tools/kvm_stat: Fix documentation typo

Thomas Gleixner (2):
      KVM: x86: Cancel pvclock_gtod_work on module removal
      KVM: x86: Prevent deadlock against tk_core.seq

Tom Lendacky (1):
      KVM: SVM: Move GHCB unmapping to fix RCU warning

Vitaly Kuznetsov (9):
      x86/kvm: Fix pr_info() for async PF setup/teardown
      x86/kvm: Teardown PV features on boot CPU as well
      x86/kvm: Disable kvmclock on all CPUs on shutdown
      x86/kvm: Disable all PV features on crash
      x86/kvm: Unify kvm_pv_guest_cpu_reboot() with kvm_guest_cpu_offline()
      KVM: nVMX: Always make an attempt to map eVMCS after migration
      KVM: selftests: evmcs_test: Check that VMLAUNCH with bogus EVMPTR is causing #UD
      KVM: selftests: evmcs_test: Check that VMCS12 is alway properly synced to eVMCS after restore
      KVM: nVMX: Properly pad 'struct kvm_vmx_nested_state_hdr'

Wanpeng Li (1):
      KVM: LAPIC: Accurately guarantee busy wait for timer to expire when using hv_timer

 Documentation/virt/kvm/api.rst                    |   4 +-
 arch/powerpc/include/asm/kvm_book3s.h             |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c               |  46 +++--
 arch/powerpc/kvm/book3s_64_mmu_radix.c            |   5 +-
 arch/x86/include/asm/kvm_host.h                   |  15 +-
 arch/x86/include/asm/kvm_para.h                   |  10 +-
 arch/x86/include/uapi/asm/kvm.h                   |   2 +
 arch/x86/kernel/kvm.c                             | 129 ++++++++-----
 arch/x86/kernel/kvmclock.c                        |  26 +--
 arch/x86/kvm/cpuid.c                              |  20 +-
 arch/x86/kvm/emulate.c                            |   2 +-
 arch/x86/kvm/kvm_emulate.h                        |   1 +
 arch/x86/kvm/lapic.c                              |   2 +-
 arch/x86/kvm/mmu/mmu.c                            |  20 +-
 arch/x86/kvm/mmu/tdp_mmu.c                        |  17 +-
 arch/x86/kvm/svm/nested.c                         |  23 ++-
 arch/x86/kvm/svm/sev.c                            |  32 ++--
 arch/x86/kvm/svm/svm.c                            |  62 +++---
 arch/x86/kvm/svm/svm.h                            |   1 +
 arch/x86/kvm/vmx/capabilities.h                   |   3 +
 arch/x86/kvm/vmx/nested.c                         |  29 ++-
 arch/x86/kvm/vmx/vmx.c                            | 220 +++++++++++-----------
 arch/x86/kvm/vmx/vmx.h                            |  12 +-
 arch/x86/kvm/x86.c                                | 153 +++++++++++----
 tools/kvm/kvm_stat/kvm_stat.txt                   |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/handlers.S |   4 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c   |  88 +++++++--
 virt/kvm/kvm_main.c                               |   7 +-
 28 files changed, 578 insertions(+), 359 deletions(-)
```
#### [PATCH v4 01/66] arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12248795
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56B12C43461
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:59:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B085611CE
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:59:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231781AbhEJRAs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:00:48 -0400
Received: from mail.kernel.org ([198.145.29.99]:52780 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230152AbhEJRAq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 13:00:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 254B1611F0;
        Mon, 10 May 2021 16:59:41 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg9Fr-000Uqg-GE; Mon, 10 May 2021 17:59:39 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Haibo Xu <haibo.xu@linaro.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com, Jintack Lim <jintack.lim@linaro.org>
Subject: [PATCH v4 01/66] arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
Date: Mon, 10 May 2021 17:58:15 +0100
Message-Id: <20210510165920.1913477-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210510165920.1913477-1-maz@kernel.org>
References: <20210510165920.1913477-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, jintack@cs.columbia.edu, haibo.xu@linaro.org,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com, jintack.lim@linaro.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jintack Lim <jintack.lim@linaro.org>

Add a new ARM64_HAS_NESTED_VIRT feature to indicate that the
CPU has the ARMv8.3 nested virtualization capability.

This will be used to support nested virtualization in KVM.

Signed-off-by: Jintack Lim <jintack.lim@linaro.org>
Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 .../admin-guide/kernel-parameters.txt         |  4 +++
 arch/arm64/include/asm/cpucaps.h              |  1 +
 arch/arm64/kernel/cpufeature.c                | 25 +++++++++++++++++++
 3 files changed, 30 insertions(+)

```
#### [PATCH 1/2] KVM: arm64: Move __adjust_pc out of line
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12247429
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7B830C43470
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 09:49:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5731B61469
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 09:49:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230299AbhEJJuo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 05:50:44 -0400
Received: from mail.kernel.org ([198.145.29.99]:35666 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230103AbhEJJun (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 05:50:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2A47461042;
        Mon, 10 May 2021 09:49:35 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg2Xd-000LFh-BX; Mon, 10 May 2021 10:49:33 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: arm64: Move __adjust_pc out of line
Date: Mon, 10 May 2021 10:49:14 +0100
Message-Id: <20210510094915.1909484-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210510094915.1909484-1-maz@kernel.org>
References: <20210510094915.1909484-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, yuzenghui@huawei.com,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to make it easy to call __adjust_pc() from the EL1 code
(in the case of nVHE), rename it to __kvm_adjust_pc() and move
it out of line.

No expected functional change.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Cc: stable@vger.kernel.org # 5.11
---
 arch/arm64/include/asm/kvm_asm.h           |  2 ++
 arch/arm64/kvm/hyp/exception.c             | 18 +++++++++++++++++-
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h | 18 ------------------
 arch/arm64/kvm/hyp/nvhe/switch.c           |  2 +-
 arch/arm64/kvm/hyp/vhe/switch.c            |  2 +-
 5 files changed, 21 insertions(+), 21 deletions(-)

```
#### [PATCH v3 1/9] irqchip/gic: Split vGIC probing information from the GIC code
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12248251
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4E9F3C433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:51:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3414261106
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:51:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239035AbhEJNwl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 09:52:41 -0400
Received: from mail.kernel.org ([198.145.29.99]:51580 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S242712AbhEJNu0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 09:50:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 09179610C9;
        Mon, 10 May 2021 13:49:22 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg6Hg-000Rol-72; Mon, 10 May 2021 14:49:20 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Hector Martin <marcan@marcan.st>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com
Subject: [PATCH v3 1/9] irqchip/gic: Split vGIC probing information from the
 GIC code
Date: Mon, 10 May 2021 14:48:16 +0100
Message-Id: <20210510134824.1910399-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210510134824.1910399-1-maz@kernel.org>
References: <20210510134824.1910399-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, marcan@marcan.st,
 mark.rutland@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vGIC advertising code is unsurprisingly very much tied to
the GIC implementations. However, we are about to extend the
support to lesser implementations.

Let's dissociate the vgic registration from the GIC code and
move it into KVM, where it makes a bit more sense. This also
allows us to mark the gic_kvm_info structures as __initdata.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/vgic/vgic-init.c        | 18 +++++++++--
 drivers/irqchip/irq-gic-common.c       | 13 --------
 drivers/irqchip/irq-gic-common.h       |  2 --
 drivers/irqchip/irq-gic-v3.c           |  6 ++--
 drivers/irqchip/irq-gic.c              |  6 ++--
 include/linux/irqchip/arm-gic-common.h | 25 +---------------
 include/linux/irqchip/arm-vgic-info.h  | 41 ++++++++++++++++++++++++++
 7 files changed, 63 insertions(+), 48 deletions(-)
 create mode 100644 include/linux/irqchip/arm-vgic-info.h

```
#### [PATCH] KVM: x86: hyper-v: Task srcu lock when accessing kvm_memslots()
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12247179
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 920C8C433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:22:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56DE16101B
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:22:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230203AbhEJIXP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:23:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37774 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230118AbhEJIXO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:23:14 -0400
Received: from mail-pg1-x52b.google.com (mail-pg1-x52b.google.com
 [IPv6:2607:f8b0:4864:20::52b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A012BC061573;
        Mon, 10 May 2021 01:22:10 -0700 (PDT)
Received: by mail-pg1-x52b.google.com with SMTP id t193so216643pgb.4;
        Mon, 10 May 2021 01:22:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=dhMvoxMJAO0uO8IA2H0TKE6ifTGSTb7TdUN9wUYY1wY=;
        b=rF+VTgtqNWExfkHPyubomVntp5D64QNIvFRhbWNDq6JUqR6drFXxO2hUq73WoOb4A+
         SXOJgOFxNcvt44dK+celf8J3digKOAsuPwycGLvcaaHB/tHudcZcGzYjb+ce+eNCEm5Y
         w1w7mnQROzs825bb6dI+/Ueisd7QaGmUSyyHHzsOrxhPaFiyt2PlTlOrvpueeDTt24Pz
         waUwUJhvvCcbpGEmlvPq6YugzUH0ga9pv4L/PLrps/YtrJPioHxChF4RezJHTP89GA54
         XVo5oXSsoj8GaAu8br8RIuD/SSQuPkATQhlrx3Ga5B2ACa6PpiZiE5By+lDUoVaUWz1K
         BkqA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=dhMvoxMJAO0uO8IA2H0TKE6ifTGSTb7TdUN9wUYY1wY=;
        b=jqnXwF3gIcCmTusClvtZ4CmQItUK73p7FS9NTQ9S/tR3WqsJma1s5ZU3I+2sfmH1Rf
         DiG99sU+YBUuIpRH0CDh5Fe19N8Jf5Unao4v5CeSkG0kkp8p8SQlDhAKhWIsUKLUVBIi
         6pXnuOCKp/WZeNhPigiDetAh9giY5yUt8oT7h0fyZGDPBx5McXx9g/NSz66YKhhLhQlQ
         MGF+kf7q7mYuXJXH75TTghw2tPQSWYPR72lMMqnx+2GgqxyGF75+KW8pyy+exaR8f+RU
         TNzkT8mTBsDAMzxLuSR/udvKjOvrP6LGh0R/YhOby/nxTfx4ptA7czExYQainqZXl1U/
         2/UQ==
X-Gm-Message-State: AOAM532bU/sMZu1SbSgMAEaoHJrNUqaj3/aG+UI1TsKMHryihT+00noM
        fsEgMcqRTYXHqjU6YIYpzj93fr19DV0=
X-Google-Smtp-Source: 
 ABdhPJzIP+6jHymcpdNkCuuBGSX0Azj04jxYye7z94O7cf+ud4WEkbUhx8ymwUTMtSHpOCMpQk7ZVg==
X-Received: by 2002:a63:8f17:: with SMTP id n23mr24343609pgd.82.1620634929917;
        Mon, 10 May 2021 01:22:09 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 n8sm10477853pgm.7.2021.05.10.01.22.07
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 10 May 2021 01:22:09 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: x86: hyper-v: Task srcu lock when accessing
 kvm_memslots()
Date: Mon, 10 May 2021 16:21:59 +0800
Message-Id: <1620634919-4563-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

 WARNING: suspicious RCU usage
 5.13.0-rc1 #4 Not tainted
 -----------------------------
 ./include/linux/kvm_host.h:710 suspicious rcu_dereference_check() usage!
 
other info that might help us debug this:

rcu_scheduler_active = 2, debug_locks = 1
 1 lock held by hyperv_clock/8318:
  #0: ffffb6b8cb05a7d8 (&hv->hv_lock){+.+.}-{3:3}, at: kvm_hv_invalidate_tsc_page+0x3e/0xa0 [kvm]
 
stack backtrace:
CPU: 3 PID: 8318 Comm: hyperv_clock Not tainted 5.13.0-rc1 #4
Call Trace:
 dump_stack+0x87/0xb7
 lockdep_rcu_suspicious+0xce/0xf0
 kvm_write_guest_page+0x1c1/0x1d0 [kvm]
 kvm_write_guest+0x50/0x90 [kvm]
 kvm_hv_invalidate_tsc_page+0x79/0xa0 [kvm]
 kvm_gen_update_masterclock+0x1d/0x110 [kvm]
 kvm_arch_vm_ioctl+0x2a7/0xc50 [kvm]
 kvm_vm_ioctl+0x123/0x11d0 [kvm]
 __x64_sys_ioctl+0x3ed/0x9d0
 do_syscall_64+0x3d/0x80
 entry_SYSCALL_64_after_hwframe+0x44/0xae

kvm_memslots() will be called by kvm_write_guest(), so we should take the srcu lock.

Fixes: e880c6ea5 (KVM: x86: hyper-v: Prevent using not-yet-updated TSC page by secondary CPUs)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [RESEND PATCH v4 01/10] perf/x86/intel: Fix the comment about guest LBR support on KVM
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12247151
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0E5EC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:16:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C8FA61363
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:16:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230289AbhEJIR0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:17:26 -0400
Received: from mga12.intel.com ([192.55.52.136]:42716 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230247AbhEJIRW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:17:22 -0400
IronPort-SDR: 
 9qwGzIWPLXjRmc6axNEsIp0//+m0HPNeoPQxLmfuebVtC+0TXg4UWNj1zeDQJZ3GivbhzO4D/O
 WFCuou+l5+ig==
X-IronPort-AV: E=McAfee;i="6200,9189,9979"; a="178727692"
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="178727692"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:16:18 -0700
IronPort-SDR: 
 A8O24rmZPMITHaXTHS0g7m9BXC0WTkqwm3V1YI0XUwBk5fle9Ddoeydih1v/U3dUn6YYtesOb5
 kfnPuvfGxihQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="408250826"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga002.jf.intel.com with ESMTP; 10 May 2021 01:16:15 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        wei.w.wang@intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RESEND PATCH v4 01/10] perf/x86/intel: Fix the comment about guest
 LBR support on KVM
Date: Mon, 10 May 2021 16:15:25 +0800
Message-Id: <20210510081535.94184-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210510081535.94184-1-like.xu@linux.intel.com>
References: <20210510081535.94184-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Starting from v5.12, KVM reports guest LBR and extra_regs support
when the host has relevant support. Just delete this part of the
comment and fix a typo incidentally.

Cc: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Kan Liang <kan.liang@linux.intel.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
I personally recommend this patch to hit the mainline through the KVM tree.

 arch/x86/events/intel/core.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [RESEND kvm-unit-tests PATCH v2] x86: Update guest LBR tests for Architectural LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12247171
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8F797C43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:17:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7276F613C9
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:17:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230418AbhEJISM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:18:12 -0400
Received: from mga12.intel.com ([192.55.52.136]:42733 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230331AbhEJISF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:18:05 -0400
IronPort-SDR: 
 /XGzkQGVQV2BJNpY165EhKlNdY/wwdnxxAg7RyFYyTdrm3tLt1mFfCgDBtxedoNug5eaSHkuR4
 Mj11kG0G8BLA==
X-IronPort-AV: E=McAfee;i="6200,9189,9979"; a="178727881"
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="178727881"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:16:45 -0700
IronPort-SDR: 
 P2M3+YHXwHkX5cD1X+feZBZomgYx+G/uOKZDGLhArqa13V51r1biWQ88bXUYHTvzz1/75N6ZGq
 g8xqjFxo/wAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="408250982"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga002.jf.intel.com with ESMTP; 10 May 2021 01:16:41 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        wei.w.wang@intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RESEND kvm-unit-tests PATCH v2] x86: Update guest LBR tests for
 Architectural LBR
Date: Mon, 10 May 2021 16:15:35 +0800
Message-Id: <20210510081535.94184-12-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210510081535.94184-1-like.xu@linux.intel.com>
References: <20210510081535.94184-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test the basic KVM's support for
Architectural LBRs which is a Architectural performance monitor
unit (PMU) feature on Intel processors including negative testing
on the MSR LBR_DEPTH values.

If the LBR bit is set to 1 in the MSR_ARCH_LBR_CTL, the processor
will record a running trace of the most recent branches guest
taken in the LBR entries for guest to read.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Thomas Huth <thuth@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 x86/pmu_lbr.c | 88 +++++++++++++++++++++++++++++++++++++++++++++------
 1 file changed, 79 insertions(+), 9 deletions(-)

```
#### [PATCH v16 01/14] s390/vfio-ap: fix memory leak in mdev remove callback
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12248749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6154DC43600
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:44:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40D406147E
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:44:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231873AbhEJQpp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 12:45:45 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:56636 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231736AbhEJQpo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 12:45:44 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AGZJ7Q115336;
        Mon, 10 May 2021 12:44:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=vnAYmSre0cOZDcxrTRW9FEGmvaFURp4YtQVfXpnn4d0=;
 b=eJYXg2emET8lP6XiXTs1ErkAJ2zXrS0Ak4yu2eqomjxMzLXTZ4QPSWrSTLNzgtZlJ8wl
 E1kGRzzXTSU4j6Qjj+PnF0sM2d2xh6jjzPfFWauoFenyYPLpJ2pFPYMiSOW2JDKVWn5s
 E1TZhEQZlOQuIDwCxa5RqOqJH/T+Vjox2jX4sqrFK1x9CaqJE5i5rVpX6btyCebAjYQZ
 TSmXIgIvlV8fZofjrrU+wo/cgulsB4G1fQHxr7fMJIT64d3kOQdziCKSmI0TtsDRL0Fr
 DSRsDB6P/0hG4PpG4tvhIodnGmc71A4NkhduxcrGQbU3W1dZMx3LFSey15oJ1Q43G4dP OA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f7ha9ytb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 12:44:37 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AGZT2b116620;
        Mon, 10 May 2021 12:44:36 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f7ha9yse-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 12:44:36 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AGh0Y7021538;
        Mon, 10 May 2021 16:44:34 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma03dal.us.ibm.com with ESMTP id 38dj993hv7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:44:34 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 14AGiWx830736834
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 16:44:32 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5327DAE064;
        Mon, 10 May 2021 16:44:32 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1133DAE05F;
        Mon, 10 May 2021 16:44:31 +0000 (GMT)
Received: from cpe-172-100-179-72.stny.res.rr.com.com (unknown [9.85.140.234])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 16:44:30 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>, stable@vger.kernel.org,
        Tony Krowiak <akrowiak@stny.rr.com>
Subject: [PATCH v16 01/14] s390/vfio-ap: fix memory leak in mdev remove
 callback
Date: Mon, 10 May 2021 12:44:10 -0400
Message-Id: <20210510164423.346858-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210510164423.346858-1-akrowiak@linux.ibm.com>
References: <20210510164423.346858-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: sj-owWYLxgvi1eCc--2z6vfYwjqFjfqc
X-Proofpoint-ORIG-GUID: en8IrDvmBzIHIC1B4KkillZeqIqnPQJn
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_09:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 bulkscore=0
 lowpriorityscore=0 malwarescore=0 suspectscore=0 adultscore=0
 mlxlogscore=999 phishscore=0 priorityscore=1501 clxscore=1015 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105100113
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The mdev remove callback for the vfio_ap device driver bails out with
-EBUSY if the mdev is in use by a KVM guest. The intended purpose was
to prevent the mdev from being removed while in use; however, returning a
non-zero rc does not prevent removal. This could result in a memory leak
of the resources allocated when the mdev was created. In addition, the
KVM guest will still have access to the AP devices assigned to the mdev
even though the mdev no longer exists.

To prevent this scenario, cleanup will be done - including unplugging the
AP adapters, domains and control domains - regardless of whether the mdev
is in use by a KVM guest or not.

Fixes: 258287c994de ("s390: vfio-ap: implement mediated device open callback")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@stny.rr.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 39 +++++++++++++++++++++++--------
 1 file changed, 29 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] s390x: sclp: Only fetch read info byte 134 if cpu entries are above it
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12248429
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0AFEC43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:05:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C83EB61421
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:05:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240731AbhEJPGn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 11:06:43 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:29329 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231168AbhEJPDI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 11:03:08 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AEcRPN060494;
        Mon, 10 May 2021 11:02:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XUtLXsdceggkbafQ9KIgtpEUlAgSHZJIwuYsMj2R5/0=;
 b=QGt8506qLMt9viOMpiOCw+dEHp2NCRk98bf6ScZazEYvLNSMiWr4mzyglRvKbGyldVzp
 EJvL1uI/sX1fxuYyiKlJp4bBc65sBZTxvxL6ERMUqIXhKnbvijfGxgmDnqcUGQYeMirl
 /FpwxNEU10Ou3Gt0S1hpApEK0WfIq+qqfW53gV4qKU3EinNS12Q5cVoUBO8c/KqXL8tU
 vhCxBXwLq+MXYYi68G4TcrbInmp9ZzIRjDg9RjkoO7pNnYmjIDo5UwvMCK1t3IbBwlUn
 ewiUfBGM9aFz9LpdlV6RSjz0GoI31AXafImj4+kGfn3BC5Fbf4QEND/WyXQ+HIjAFs1/ Bw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f21t9m7t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 11:02:02 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AEco5s063044;
        Mon, 10 May 2021 11:02:02 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f21t9m5b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 11:02:02 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AEtLdr010361;
        Mon, 10 May 2021 15:01:59 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06fra.de.ibm.com with ESMTP id 38dhwh0jmu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 15:01:59 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14AF1ULF22610254
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 15:01:30 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9C625AE053;
        Mon, 10 May 2021 15:01:56 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DA08DAE061;
        Mon, 10 May 2021 15:01:55 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 15:01:55 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH 1/4] s390x: sclp: Only fetch read info byte 134
 if cpu entries are above it
Date: Mon, 10 May 2021 15:00:12 +0000
Message-Id: <20210510150015.11119-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210510150015.11119-1-frankja@linux.ibm.com>
References: <20210510150015.11119-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: bLkBwzht5fgRW-Z3tJOLscCymLBxoN-t
X-Proofpoint-ORIG-GUID: laD1Mo8X8BLZYjn_SlO6cVPRX5kS5AqP
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_09:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 priorityscore=1501 mlxscore=0 spamscore=0 lowpriorityscore=0 adultscore=0
 mlxlogscore=999 bulkscore=0 suspectscore=0 clxscore=1015 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105100105
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The cpu offset tells us where the cpu entries are in the sclp read
info structure.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/s390x/sclp.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/6] s390x: uv-guest: Add invalid share location test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12248289
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4DE63C43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:56:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BB6860720
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:56:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240315AbhEJN53 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 09:57:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44790 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237019AbhEJNxQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 09:53:16 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14ADWic0009795;
        Mon, 10 May 2021 09:52:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=3uZmSI77E5TGNyfkRuQlpsM6Hja+QeN+kVV0qwniZ1M=;
 b=DiUp2kV0DgerFvFHiHsR9sn9aESMgjcZutrLRyI6v5mdAc3tIlT9FB4TIEtzzVvWFvQ9
 H89Jv8pKLfDTQPdN53q4Nc8ExoKXAW+25iBD3WbB9BaNRdNlzm+mvsDqIowZV+qo/+cY
 9r0YB4ys5nygKUSoqRjLZR5Mvi9hrj44M7ycLFfmVBtDHeBu6dqMa1mSj/S3goh39UuE
 STVOqAOCq1FcPuqp0+OcTr+7WRG1g6YYRDiej06feIkFs4kibDJvnE+LDro39wDA8645
 TrWwoTv0KQEdvihgAVzqR/Kn/4PdTDgefLGdBnXGcbO+3kgbIY3mCc3jFKblNgfgUrwI Sg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f3s44xuy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 09:52:08 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14ADWxD8010911;
        Mon, 10 May 2021 09:52:08 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f3s44xu4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 09:52:07 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14ADggrl006433;
        Mon, 10 May 2021 13:52:05 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03fra.de.ibm.com with ESMTP id 38dj988hpd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 13:52:05 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14ADq28m54133182
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 13:52:02 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A3FDEA4059;
        Mon, 10 May 2021 13:52:02 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D84DDA4055;
        Mon, 10 May 2021 13:52:01 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 13:52:01 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/6] s390x: uv-guest: Add invalid share
 location test
Date: Mon, 10 May 2021 13:51:43 +0000
Message-Id: <20210510135148.1904-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210510135148.1904-1-frankja@linux.ibm.com>
References: <20210510135148.1904-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: AEnDYgOtnMfhnwDXmQ60d_cfyrzDe_gQ
X-Proofpoint-GUID: Bs1GzVKTzmTRmInuUKNpajyOo938glOG
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_07:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 clxscore=1015 impostorscore=0 mlxlogscore=999 priorityscore=1501
 phishscore=0 suspectscore=0 bulkscore=0 mlxscore=0 spamscore=0
 adultscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2104190000 definitions=main-2105100096
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's also test sharing unavailable memory.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/uv-guest.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH 1/2] virtio: update virtio id table, add transitional ids
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhu, Lingshan" <lingshan.zhu@intel.com>
X-Patchwork-Id: 12247145
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9D8ECC43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:15:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83AEE613C9
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:15:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230231AbhEJIQt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:16:49 -0400
Received: from mga18.intel.com ([134.134.136.126]:57585 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230045AbhEJIQt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:16:49 -0400
IronPort-SDR: 
 mAAhpM5gbz3qEYm3ZdUOcE2DWCIViTqcvesNLUwX8Jg4t29j2vSDXeX9T+Q7TmJNkqyoj05x1e
 e/cF8MUqlkiA==
X-IronPort-AV: E=McAfee;i="6200,9189,9979"; a="186587922"
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="186587922"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:15:45 -0700
IronPort-SDR: 
 ozlSm+ri35isq/tHio7nFJ+DSY5PXYei4Z6ianR6ucuIttq8SpeG5S8uNpJZL6PrbxbLazS7Pr
 BlXYLLL8WwHw==
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="436040628"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:15:42 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] virtio: update virtio id table, add transitional ids
Date: Mon, 10 May 2021 16:10:14 +0800
Message-Id: <20210510081015.4212-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210510081015.4212-1-lingshan.zhu@intel.com>
References: <20210510081015.4212-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit updates virtio id table by adding transitional device
ids

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 include/uapi/linux/virtio_ids.h | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [PATCH v3] KVM: selftests: Print a message if /dev/kvm is missingFrom: David Matlack <dmatlack@google.com>
##### From: David Matlack <dmatlack@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Matlack <dmatlack@google.com>
X-Patchwork-Id: 12249137
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9A719C43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:46:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D7EF6112F
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:46:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231610AbhEJRrw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:47:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52018 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231187AbhEJRrv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 13:47:51 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EB2A6C061761
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 10:46:42 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id
 mw15-20020a17090b4d0fb0290157199aadbaso11815974pjb.7
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 10:46:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=BFlO1gMJbRT63RTuthNx6rSz00kF87hnvs4FWUfg+4s=;
        b=gYeYufRarPQNxGNRz1sL+Qb2a0BPFSa4I/QL6G0s5UPbd1rUxl+/cXino3Koe4VK5C
         jxtYztGdGUW2eauhxOQhAb2Sk37B9dP9IPeL90uspcZ+oV/aa+6SFkKXVaqsuS/5yrIZ
         Yvaw36IwZBcFA8tcI+uVW0k2imxno51IMrg9tdcM/wJslyO+/x/pY6Ds5yyEAew6IpaN
         h9mOuSiOWwCOSXRPNumM2NhH7Nro3KcwH31jZpr3nSSzBNZAfa/SNtknP/7l4ysouKSZ
         IeDEqirYVB2OwG5p4AL3avotV3O7jVXpeO7G+4aPqOI3IIKiYYlUPWDLvNlBVa4TnCJQ
         gKFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=BFlO1gMJbRT63RTuthNx6rSz00kF87hnvs4FWUfg+4s=;
        b=R9R5ew+xDk/dLLMTnf3rkNyafC3m1887IA9MhpmLBCDQAHFWS5Ieei6xxVUKab6Eia
         ovR5580aeug+0YDsE/PmTVMZF0S+IoECUW6uVZXUdYyz+gaHzWZoXerS+qb5BSkxZ6UD
         iSHqTkoUQO5EaorIAKJKZx4Oc4RU9isN4tywD+vpwr/m0xrPIf4kjmCw9rRtKOqYtjfQ
         kFk3MFHTolXorUl15CI/Hl6XLpcYWCKvuQrCRHMZ5JZvKA5tSHM5dvHBMcQ1s5Rl1Vjw
         1CVgIAW3O0TiXfweC0Y/UW64DEZ7uqcS0ZoeZ1+uvQ+DRlEidIC4fRl9SIzf47nHd8o7
         wSfw==
X-Gm-Message-State: AOAM533HE+HRt0dWUY6FyZdghKWQ4KB56Qe6cwhOuEFSbsPygUeAqxuK
        o3ZcZL6C5gCTuaMq1nslNsLEEcN8xURwqq8oS/t7PtICPlckC+/ePdb2wh+et+Ben7OLgmT4C0L
        KQMdXBtzVVjzfuXwQsWgV8pTHPsWJKz7q8po4uWHmwYiGxE3aoKU142nyE+AiAQw=
X-Google-Smtp-Source: 
 ABdhPJx7KA+U/Cn5I6doSCk+a0suPvjTs5rgYa3oxEoctKrDzh0Qv7OSpOXOunz9ifQyiBQe1gb4zfLmIHbg+A==
X-Received: from dmatlack-heavy.c.googlers.com
 ([fda3:e722:ac3:10:7f:e700:c0a8:19cd])
 (user=dmatlack job=sendgmr) by 2002:a62:8c45:0:b029:272:e091:cda5 with SMTP
 id m66-20020a628c450000b0290272e091cda5mr25875205pfd.59.1620668802302; Mon,
 10 May 2021 10:46:42 -0700 (PDT)
Date: Mon, 10 May 2021 17:46:39 +0000
Message-Id: <20210510174639.1130344-1-dmatlack@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v3] KVM: selftests: Print a message if /dev/kvm is missing
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
 tools/testing/selftests/kvm/lib/kvm_util.c    | 45 +++++++++++++------
 .../selftests/kvm/lib/x86_64/processor.c      | 16 ++-----
 .../kvm/x86_64/get_msr_index_features.c       |  8 +---
 4 files changed, 38 insertions(+), 32 deletions(-)

```
#### [RFC PATCH v5 1/3] vfio-ccw: Check initialized flag in cp_init()
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12249317
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB9DEC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 20:56:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A269361264
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 20:56:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232965AbhEJU6C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 16:58:02 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:53878 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232831AbhEJU6A (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 16:58:00 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AKYTs0165979;
        Mon, 10 May 2021 16:56:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=6Ji2N+g5BEfEKgFOPSitgWqnRCwc0MS0b5j0S+cgxRA=;
 b=Nnh86e5uVSApHODvjnvTHYN2M/HTzI9dr9f+BdDWUa3Fphz+DiGAmud7MtzE+lF77hRw
 sQpKex5SG1C9wBNJgaF/Fq8dxTIoN/9/T7dbEhb98CAEU1PQ/Hzz+FkieSWpKhl1+tqG
 i0i+m5qUVbswqRDQ1jujjYoakuafinA7TZLG+e7K6ndijZnXnd0T93zlmotGUW8MARip
 MxJliWcZcWOf5If/vQMEa+QRO0SQ/jCcLcuTg9IbSUq7mZIUOzvEWT82ntkpXf+2o6N6
 ZVEHW8CTOY2j1a35TC9F+88lvTNiqVwQ1uU2mMX/0MbRoCLdUAYyGO2npXZtxO210p7w 6Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fatrtxjm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:56:54 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AKZEd6168055;
        Mon, 10 May 2021 16:56:53 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fatrtxhu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:56:53 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AKulMc025733;
        Mon, 10 May 2021 20:56:51 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03fra.de.ibm.com with ESMTP id 38dj988pgx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 20:56:51 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14AKummR23331152
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 20:56:48 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9D86F4C050;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8ACB24C046;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 2D21FE0322; Mon, 10 May 2021 22:56:48 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v5 1/3] vfio-ccw: Check initialized flag in cp_init()
Date: Mon, 10 May 2021 22:56:44 +0200
Message-Id: <20210510205646.1845844-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210510205646.1845844-1-farman@linux.ibm.com>
References: <20210510205646.1845844-1-farman@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: hEPbuEAmc3v0JmYrqTxLBzkEB1nWjYob
X-Proofpoint-ORIG-GUID: 5LRcVOx_A-WpkI-4TH7RQY3fYqgyxHMJ
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_12:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 spamscore=0 suspectscore=0 phishscore=0 mlxscore=0 lowpriorityscore=0
 priorityscore=1501 adultscore=0 malwarescore=0 mlxlogscore=999
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105100140
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We have a really nice flag in the channel_program struct that
indicates if it had been initialized by cp_init(), and use it
as a guard in the other cp accessor routines, but not for a
duplicate call into cp_init(). The possibility of this occurring
is low, because that flow is protected by the private->io_mutex
and FSM CP_PROCESSING state. But then why bother checking it
in (for example) cp_prefetch() then?

Let's just be consistent and check for that in cp_init() too.

Fixes: 71189f263f8a3 ("vfio-ccw: make it safe to access channel programs")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [for-6.1 v3 2/3] virtiofsd: Track mounts
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 12248615
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95615C433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:55:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 746E26161E
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:55:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231653AbhEJP5D convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Mon, 10 May 2021 11:57:03 -0400
Received: from us-smtp-delivery-44.mimecast.com ([207.211.30.44]:52650 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230492AbhEJP5B (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 11:57:01 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-549-cfmBLbnrNRe3SC-TApJOzA-1; Mon, 10 May 2021 11:55:51 -0400
X-MC-Unique: cfmBLbnrNRe3SC-TApJOzA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 763616408E;
        Mon, 10 May 2021 15:55:49 +0000 (UTC)
Received: from bahia.redhat.com (ovpn-112-152.ams2.redhat.com [10.36.112.152])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 271A519C44;
        Mon, 10 May 2021 15:55:46 +0000 (UTC)
From: Greg Kurz <groug@kaod.org>
To: qemu-devel@nongnu.org
Cc: Vivek Goyal <vgoyal@redhat.com>, virtio-fs@redhat.com,
        "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Miklos Szeredi <miklos@szeredi.hu>, Greg Kurz <groug@kaod.org>
Subject: [for-6.1 v3 2/3] virtiofsd: Track mounts
Date: Mon, 10 May 2021 17:55:38 +0200
Message-Id: <20210510155539.998747-3-groug@kaod.org>
In-Reply-To: <20210510155539.998747-1-groug@kaod.org>
References: <20210510155539.998747-1-groug@kaod.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The upcoming implementation of ->sync_fs() needs to know about all
submounts in order to call syncfs() on all of them.

Track every inode that comes up with a new mount id in a GHashTable.
If the mount id isn't available, e.g. no statx() on the host, fallback
on the device id for the key. This is done during lookup because we
only care for the submounts that the client knows about. The inode
is removed from the hash table when ultimately unreferenced. This
can happen on a per-mount basis when the client posts a FUSE_FORGET
request or for all submounts at once with FUSE_DESTROY.

Signed-off-by: Greg Kurz <groug@kaod.org>
---
 tools/virtiofsd/passthrough_ll.c | 42 +++++++++++++++++++++++++++++---
 1 file changed, 39 insertions(+), 3 deletions(-)

```
#### [patch 1/4] KVM: x86: add start_assignment hook to kvm_x86_opsReferences: <20210510172646.930550753@redhat.com>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12249179
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A6F7C43461
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21606611BD
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233269AbhEJRzt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:55:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25362 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231512AbhEJRzf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 13:55:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620669270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=T6XQ723YNp2P/eb+4YbFfQ3fMPYItgFEaCDeufUV3/E=;
        b=eqfSEdivSrF7DdfVwntfcuenOlDxLBJdAV1PtqQPH5b3hp+KJhfWoTc1ztw2lSzn2BEDFB
        WPYLOVvbOXOTJCZTxyD3STcSae785lkyU0Y5D/MuvMAt8jYwTf1hetdJ7raHybnIm6pyXq
        wphT6ihHsuCDYZEO7beif916hmbGAlY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-471-aIG9LxA6OPGjAdsL0hnV3w-1; Mon, 10 May 2021 13:54:28 -0400
X-MC-Unique: aIG9LxA6OPGjAdsL0hnV3w-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5446683DB69;
        Mon, 10 May 2021 17:54:27 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 2F3EA421F;
        Mon, 10 May 2021 17:54:20 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 7858D440187A; Mon, 10 May 2021 14:54:15 -0300 (-03)
Message-ID: <20210510172817.934490238@redhat.com>
User-Agent: quilt/0.66
Date: Mon, 10 May 2021 14:26:47 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Xu <peterx@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 1/4] KVM: x86: add start_assignment hook to kvm_x86_ops
References: <20210510172646.930550753@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
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
+	void (*start_assignment)(struct kvm *kvm);
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
@@ -11295,7 +11295,11 @@ bool kvm_arch_can_dequeue_async_page_pre
 
 void kvm_arch_start_assignment(struct kvm *kvm)
 {
-	atomic_inc(&kvm->arch.assigned_device_count);
+	int ret;
+
+	ret = atomic_inc_return(&kvm->arch.assigned_device_count);
+	if (ret == 1)
+		static_call_cond(kvm_x86_start_assignment)(kvm);
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

From patchwork Mon May 10 17:26:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12249173
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90E2FC43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6E70B611F0
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233265AbhEJRzr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:55:47 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:57656 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233263AbhEJRze (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 13:55:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620669269;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=3szDupmhb5P3gzH2roiv5CqgjhCLQjU+Y1Q5biEIpRs=;
        b=JP0fRh0ls3hoUEDftKfxecYsf4u/0ySeiiNj47gJWDKtJbsuSXoS4ed5k3YPeYd7DvTFnS
        LpDNk/FXIx2wsH/ZkDv0lIN++J0xwSPbx9Yv/FMO9c/rHVaEZlcfdPOY6vLlIJ/ySWkBsu
        FuGSkR+y1kdzdActnBL4cMMiR0MKL1I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-376-iRbL6Cd1OAOhbzRvYYpeHA-1; Mon, 10 May 2021 13:54:28 -0400
X-MC-Unique: iRbL6Cd1OAOhbzRvYYpeHA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 41B9D6D254;
        Mon, 10 May 2021 17:54:27 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 2F66360FC2;
        Mon, 10 May 2021 17:54:20 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 7CAA3440187B; Mon, 10 May 2021 14:54:15 -0300 (-03)
Message-ID: <20210510172817.964478800@redhat.com>
User-Agent: quilt/0.66
Date: Mon, 10 May 2021 14:26:48 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Xu <peterx@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 2/4] KVM: add arch specific vcpu_check_block callback
References: <20210510172646.930550753@redhat.com>
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

From patchwork Mon May 10 17:26:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12249175
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 581BCC43462
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3647B611F0
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233264AbhEJRzt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:55:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:22148 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233202AbhEJRzg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 13:55:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620669271;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=+SqBR60U/QBsCk2Imhxb5S4zSqBj0ElVA682Wmxx+xQ=;
        b=QHdMz47wzf7bx2clKfNMf/m/BXge0XiA+Iyj9HnxvA4ua3tm3FjLseVoBidzaaTv6u1s2A
        QI8KpzS3rTMm4+xEODrFb8xX3aGLb0l3CtdUi5Mb4xlNwNyC4YQ8ZEM95nj56ZuXyYkrwG
        rI6qfc3Dsr+F6a+1HVt2pLcgPlNNj04=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-250-nCcLRB3rPvWfxIhzkyfdeQ-1; Mon, 10 May 2021 13:54:27 -0400
X-MC-Unique: nCcLRB3rPvWfxIhzkyfdeQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A404F107ACC7;
        Mon, 10 May 2021 17:54:26 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 5BD2119C45;
        Mon, 10 May 2021 17:54:20 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 8022B4401881; Mon, 10 May 2021 14:54:15 -0300 (-03)
Message-ID: <20210510172817.994523393@redhat.com>
User-Agent: quilt/0.66
Date: Mon, 10 May 2021 14:26:49 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Xu <peterx@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 3/4] KVM: x86: implement kvm_arch_vcpu_check_block callback
References: <20210510172646.930550753@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
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
 	void (*start_assignment)(struct kvm *kvm);
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

From patchwork Mon May 10 17:26:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12249177
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0AEDAC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9080611F0
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233266AbhEJRzn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:55:43 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:21051 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233258AbhEJRze (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 13:55:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620669269;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         references:references;
 bh=tTRqfX0l0K+r+0j2GyFDtK8NMSba2t7HpOpFLFds5Q8=;
        b=Ut4da1+ildEtDQVBSjO2riXLdXoyXZ0hUbKMf/9BAVSSbDaY6Bh/YGr27msOb4F0Wy7h+e
        lC59Dw0uNTmQSGwZyIQrae7Xpkei7yiD13dP+4EtFKKaur5H+wXWqtMXNEsw2vQilYBkfx
        dAsgECx0TrN4MeBw4f6o9kcZamX3FiA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-40-G1Eq-2NcOdqDEBDKqr3zHw-1; Mon, 10 May 2021 13:54:28 -0400
X-MC-Unique: G1Eq-2NcOdqDEBDKqr3zHw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2550A8015F7;
        Mon, 10 May 2021 17:54:27 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 4E9A35D6D1;
        Mon, 10 May 2021 17:54:20 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 847114401883; Mon, 10 May 2021 14:54:15 -0300 (-03)
Message-ID: <20210510172818.025080848@redhat.com>
User-Agent: quilt/0.66
Date: Mon, 10 May 2021 14:26:50 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Xu <peterx@redhat.com>, Pei Zhang <pezhang@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 4/4] KVM: VMX: update vcpu posted-interrupt descriptor when
 assigning device
References: <20210510172646.930550753@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
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

Index: kvm/arch/x86/kvm/vmx/posted_intr.c
===================================================================
--- kvm.orig/arch/x86/kvm/vmx/posted_intr.c
+++ kvm/arch/x86/kvm/vmx/posted_intr.c
@@ -204,6 +204,32 @@ void pi_post_block(struct kvm_vcpu *vcpu
 }
 
 /*
+ * Bail out of the block loop if the VM has an assigned
+ * device, but the blocking vCPU didn't reconfigure the
+ * PI.NV to the wakeup vector, i.e. the assigned device
+ * came along after the initial check in vcpu_block().
+ */
+
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
+/*
  * Handler for POSTED_INTERRUPT_WAKEUP_VECTOR.
  */
 void pi_wakeup_handler(void)
@@ -236,6 +262,25 @@ bool pi_has_pending_interrupt(struct kvm
 		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
 }
 
+void vmx_pi_start_assignment(struct kvm *kvm)
+{
+	struct kvm_vcpu *vcpu;
+	int i;
+
+	if (!irq_remapping_cap(IRQ_POSTING_CAP))
+		return;
+
+	/*
+	 * Wakeup will cause the vCPU to bail out of kvm_vcpu_block() and
+	 * go back through vcpu_block().
+	 */
+	kvm_for_each_vcpu(i, vcpu, kvm) {
+		if (!kvm_vcpu_apicv_active(vcpu))
+			continue;
+
+		kvm_vcpu_wake_up(vcpu);
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
+void vmx_pi_start_assignment(struct kvm *kvm);
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
