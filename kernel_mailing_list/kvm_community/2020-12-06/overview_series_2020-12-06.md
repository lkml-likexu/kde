#### [PATCH 1/8] gitlab-ci: Replace YAML anchors by extends (cross_system_build_job)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11954277
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-23.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0BA19C197BF
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 18:57:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0C7F22D08
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 18:57:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727714AbgLFS4s (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 6 Dec 2020 13:56:48 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33922 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726440AbgLFS4r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 6 Dec 2020 13:56:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607280920;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=J0caE/rg850u7bwr+Q+jKihpcnbP+o9Z+fIMhlSMarg=;
        b=P4Z0ATzxM3uQDdwrsK6NPVownN6Vh+jBf4n3ODAK1USO/vJkWtEq1fS3XVAStP9lHUi67h
        DXQhgJabcFgtRXmBgqWLIvkq4K7qDiYSc9Ir4b2KnA2+74GOqu4ghOJFX4Ov6GhvlNy0mq
        EOgAjr9IyO3oJOxUL+q/I8fiNahWczg=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-405-xQnfcX6bN-WR8heqSQl_GA-1; Sun, 06 Dec 2020 13:55:18 -0500
X-MC-Unique: xQnfcX6bN-WR8heqSQl_GA-1
Received: by mail-wm1-f71.google.com with SMTP id l5so3280988wmi.4
        for <kvm@vger.kernel.org>; Sun, 06 Dec 2020 10:55:18 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=J0caE/rg850u7bwr+Q+jKihpcnbP+o9Z+fIMhlSMarg=;
        b=hpmOoKPMHoscwijxkyJ1Ih0D4ejKgTvzwj+PQlNSeNdro+vYr8rUjRQI2wL5A9qvpZ
         8WFbtZFf4kxzrQVll/o7CaLBk0q1OsXmnSN/3cOfPyu8hC0fMT/JL6YWF7u3b/P/eYLT
         iRaZUNcFOLPQboo7EvHNCcforeFtNK6ENsH6tkD2MtL6P7pQsG6iI1ockyP2Q0frxwZw
         EkJJ2DE4UpLGsIv9bPJivRBRHzZU23Gdrh+tGJMlWUs3qR6yIWDcuHxofbMYzrIgfybp
         r8e5ZNRZykRcoforVf6L4l1s28tRUTDPsJsValwDljUne70RkmTZo+L9M2KLo2mRN/gr
         n8Yw==
X-Gm-Message-State: AOAM532M8D3e472/yjJRJPnvRX5XqflHmcXJS/CoYmkuzhkSvSV9BvVo
        U0J9JNYxiqiuoxmOXXBELSWMNnYK+P/H0yvKJmLEfibiO9NNIqw58uT3VdinOW3lssYG80qKxG3
        GBhsTK8fX6Zui
X-Received: by 2002:a5d:6447:: with SMTP id d7mr15842839wrw.96.1607280917540;
        Sun, 06 Dec 2020 10:55:17 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJy5Mv3+kYooSf15r+r2aJLz/Qnqkoua9wFQmOH5L1QMkE6WgvTm77oljoy/QdNzxy3aicjEtQ==
X-Received: by 2002:a5d:6447:: with SMTP id d7mr15842818wrw.96.1607280917387;
        Sun, 06 Dec 2020 10:55:17 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 v7sm11353163wma.26.2020.12.06.10.55.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 06 Dec 2020 10:55:16 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, =?utf-8?q?A?=
	=?utf-8?q?lex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 xen-devel@lists.xenproject.org, kvm@vger.kernel.org,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Willian Rampazzo <wrampazz@redhat.com>, Paul Durrant <paul@xen.org>,
 Huacai Chen <chenhc@lemote.com>, Anthony Perard <anthony.perard@citrix.com>,
 Marcelo Tosatti <mtosatti@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Claudio Fontana <cfontana@suse.de>, Halil Pasic <pasic@linux.ibm.com>,
 Peter Maydell <peter.maydell@linaro.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Thomas Huth <thuth@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, qemu-s390x@nongnu.org,
 Aurelien Jarno <aurelien@aurel32.net>, qemu-arm@nongnu.org
Subject: [PATCH 1/8] gitlab-ci: Replace YAML anchors by extends
 (cross_system_build_job)
Date: Sun,  6 Dec 2020 19:55:01 +0100
Message-Id: <20201206185508.3545711-2-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201206185508.3545711-1-philmd@redhat.com>
References: <20201206185508.3545711-1-philmd@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

'extends' is an alternative to using YAML anchors
and is a little more flexible and readable. See:
https://docs.gitlab.com/ee/ci/yaml/#extends

More importantly it allows exploding YAML jobs.

Reviewed-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 .gitlab-ci.d/crossbuilds.yml | 40 ++++++++++++++++++------------------
 1 file changed, 20 insertions(+), 20 deletions(-)

```
#### [PATCH v2 01/16] KVM: Fix arguments to kvm_{un,}map_gfn()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11953981
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1AB1C4361B
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 11:05:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C987D22E03
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 11:05:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727357AbgLFLE6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 6 Dec 2020 06:04:58 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41902 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727222AbgLFLE4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 6 Dec 2020 06:04:56 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B81D5C08E85E
        for <kvm@vger.kernel.org>; Sun,  6 Dec 2020 03:03:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=nlfk7fo9/eeQqoeGTfsdj4FxMlsVP85cXV+6FJSJYMM=;
 b=O2x6d4bPmJGITcMUN77cll6T7y
        02NWycxomf8VGEz2y2nzo0WLpbDrUtYORtFqNi0ZDpjWYJuEcLMdLbnSEVob6Nxr79jIHxVqzTG0O
        8vevSkUhEAYeN4LHA3cLpuMCtzwGFM/J0NM8e5wWwElkx6QdZdatJ3vWnfsI6dt45IboOs7dl9qJv
        +E3aCEi3cYG1hN88WA5V33zVa2gZ7h8x4UNv0VpazwHo3ucuMi11cXNmJ70vKFv3axaYadFy9ViXn
        MJOcwIkTmuSDQBAgQWpoD/JO/bfE942n7RAONqWUqtfzmM6xvejtnudLj7MIGx9+mpEroe3T8Ip64
        HvZ89Rgw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1klrpE-0006Fo-0H; Sun, 06 Dec 2020 11:03:37 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1klrpD-000jpA-JD; Sun, 06 Dec 2020 11:03:31 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de
Subject: [PATCH v2 01/16] KVM: Fix arguments to kvm_{un,}map_gfn()
Date: Sun,  6 Dec 2020 11:03:12 +0000
Message-Id: <20201206110327.175629-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201206110327.175629-1-dwmw2@infradead.org>
References: <20201206110327.175629-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

It shouldn't take a vcpu.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c       | 8 ++++----
 include/linux/kvm_host.h | 4 ++--
 virt/kvm/kvm_main.c      | 8 ++++----
 3 files changed, 10 insertions(+), 10 deletions(-)

```
