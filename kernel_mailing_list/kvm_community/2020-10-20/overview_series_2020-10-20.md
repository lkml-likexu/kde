#### [PATCH 1/2] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON when vPMU is enabled
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11847185
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62C99C388F2
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 15:02:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BD7C21481
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 15:02:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406956AbgJTPCW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 11:02:22 -0400
Received: from mga06.intel.com ([134.134.136.31]:19882 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405917AbgJTPCV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 11:02:21 -0400
IronPort-SDR: 
 46untAN8+2JQILsBWGwtbxzP1i2uAoqziEjAT2r4chyviY3CjlHxg2uh1u0d8+/18PuPmSOg6k
 OrBAQ/IcMeRw==
X-IronPort-AV: E=McAfee;i="6000,8403,9779"; a="228851185"
X-IronPort-AV: E=Sophos;i="5.77,397,1596524400";
   d="scan'208";a="228851185"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 08:02:20 -0700
IronPort-SDR: 
 nNCBEpHhd0zpQmNwiJUP5M5g6ce2a1I459p2Lx776XxNZVx+WRtl9io7EwY9zj3AFVRQ8+SMDT
 EWe/qPObeGcA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,397,1596524400";
   d="scan'208";a="301755401"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga007.fm.intel.com with ESMTP; 20 Oct 2020 08:02:16 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON when vPMU is
 enabled
Date: Tue, 20 Oct 2020 22:57:54 +0800
Message-Id: <20201020145755.122333-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Intel platforms, software may uses IA32_MISC_ENABLE[7]
bit to detect whether the performance monitoring facility
is supported in the processor.

A write to this PMU available bit will be ignored.

Cc: Yao Yuan <yuan.yao@intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 2 ++
 arch/x86/kvm/x86.c           | 1 +
 2 files changed, 3 insertions(+)

```
#### [PATCH 1/2] linux-headers: Add support for reads in ioeventfd
##### From: Amey Narkhede <ameynarkhede03@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Amey Narkhede <ameynarkhede03@gmail.com>
X-Patchwork-Id: 11847445
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D27DC4363A
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 17:01:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1DC1B2222D
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 17:01:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tXJEuhUh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395096AbgJTRBJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 13:01:09 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35596 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2395094AbgJTRBJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 13:01:09 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9EB5EC0613CE
        for <kvm@vger.kernel.org>; Tue, 20 Oct 2020 10:01:07 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id a17so1207882pju.1
        for <kvm@vger.kernel.org>; Tue, 20 Oct 2020 10:01:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=eaYqmjcMx802IYh8As8yQQI4HZLzXd0/F879o5VXjTg=;
        b=tXJEuhUh/jBCkoIm18hk/J+QQErGA6dM6aodvpm5zAjpd0SMaC9cj5NzSsVeomWwdb
         uMISMjUWoDPDuNAFVKlYOEfjlphlNV77EnuuF/VObOBaIsCnq0kxkm1iqywQmpNaxH7s
         RakE6JuJh9Yeru7KCeiEDvMZlJ1ZHkPPdjt2auaANrVz8k8PotKbJibCkHe+VM/CQG/t
         YyalaEC9NvE8uiwSmit9I57v0mAWMyknlHFF5bNd9XGOeEJ/whGazNu0uiM/t4PgAyvK
         i+LjYHhxFKarkk6JTNrJKpMFGFJotDXrai7JIvgo6GXWnYfoAmY+DfG4gmom9gteZ5Xu
         uuQA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=eaYqmjcMx802IYh8As8yQQI4HZLzXd0/F879o5VXjTg=;
        b=Q/VUMq3D67vb+64j3zh46UUvRQtCq9Diqhs9S+tW+PK3KwXVVLr6iFpdtKzg0oqHuo
         19DITorkmpjs+5W4jUdG04UNrn7RKgYwDdgBnlmD47w0qRi1YK1dPSkay8lpbbpTHQ4f
         xgQhOoxVx44APowa/hoqELqDO7T//aKhu68cCKxPMym2BJVsgRkSGHSRKrZXWZf9euYn
         ii6Qo00yfNK2W/KeqwNCQpkzgwHFDiYZ26HtTxOS8f2czgfdklFrmyC8gNSDaNrYhS+R
         J+oX7SdXG6NuKrBGTUzwrHD9VjP1WXy12WnI9hMAgfgpD0mU9dy7GTRl6hhdlf+xs6CF
         kaMw==
X-Gm-Message-State: AOAM530CIHC2FhebHVsxwHBUm1Yv04uoNUW7ytrRjDmWGF7AJS/u1mtR
        QAa3MuknRMyvGbIG+VZHhmk=
X-Google-Smtp-Source: 
 ABdhPJyrIZ0jrQpUiVQiMr6asT4wMDG/t4eFF26d8JnKNK5AR8/YFD8r+JrSG6otU6RLsyXjrWbfiQ==
X-Received: by 2002:a17:902:c24b:b029:d5:f14a:318d with SMTP id
 11-20020a170902c24bb02900d5f14a318dmr932875plg.4.1603213267195;
        Tue, 20 Oct 2020 10:01:07 -0700 (PDT)
Received: from localhost.localdomain ([103.248.31.132])
        by smtp.googlemail.com with ESMTPSA id
 x29sm2766161pfp.152.2020.10.20.10.01.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 20 Oct 2020 10:01:06 -0700 (PDT)
From: Amey Narkhede <ameynarkhede03@gmail.com>
To: qemu-devel@nongnu.org, ameynarkhede03@gmail.com
Cc: "Michael S. Tsirkin" <mst@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 1/2] linux-headers: Add support for reads in ioeventfd
Date: Tue, 20 Oct 2020 22:30:55 +0530
Message-Id: <20201020170056.433528-2-ameynarkhede03@gmail.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020170056.433528-1-ameynarkhede03@gmail.com>
References: <20201020170056.433528-1-ameynarkhede03@gmail.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a new flag KVM_IOEVENTFD_FLAG_DATAREAD
in ioeventfd to enable receiving a notification when a
guest reads from registered PIO/MMIO address.

Signed-off-by: Amey Narkhede <ameynarkhede03@gmail.com>
---
 linux-headers/linux/kvm.h | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [RFCv2 01/16] x86/mm: Move force_dma_unencrypted() to common code
##### From: "Kirill A. Shutemov" <kirill@shutemov.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Patchwork-Id: 11845819
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45C75C433DF
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 06:21:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F0B98222C8
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 06:21:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=shutemov-name.20150623.gappssmtp.com
 header.i=@shutemov-name.20150623.gappssmtp.com header.b="ZaPL1QB9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403943AbgJTGV0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 02:21:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48540 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2403846AbgJTGTJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 02:19:09 -0400
Received: from mail-lf1-x143.google.com (mail-lf1-x143.google.com
 [IPv6:2a00:1450:4864:20::143])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8BA7EC061755
        for <kvm@vger.kernel.org>; Mon, 19 Oct 2020 23:19:07 -0700 (PDT)
Received: by mail-lf1-x143.google.com with SMTP id b1so645703lfp.11
        for <kvm@vger.kernel.org>; Mon, 19 Oct 2020 23:19:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=shutemov-name.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=gw0cyONCYVO4XOfg8B3Kq+78eeAkNdUf+c9fS1LSrP0=;
        b=ZaPL1QB9kI9ElMTPNqOmGOLmic4Yaj0wvYPOX2hSKZhYJ6S6JOdvkbyRVMBgSA1ePH
         qOo/e7bIhHOzulxvaz6DHor4XhXlHsL5b7g5c09qtmluVioDR8vcoAyGjqCFoVC09MMW
         GuNcpOQzcaxyfJZunY6z+/ByvKC9FlCQWmIV4WiycPHzcFhvsOs/5C+BuYShVEdGRMri
         7OSVKYs0jmkMmgS7omvohDxhGLSz34Ql6fQ7jd47EHkBHeLwtkRMuOWgHTbOVl1NgB0b
         /2XFnbu+/jdrX5vywxVIT4SmeaBDOr0iF1arjlf9XcIHkiXzQJqcBu9f3jCIDoJD398Z
         eFdA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=gw0cyONCYVO4XOfg8B3Kq+78eeAkNdUf+c9fS1LSrP0=;
        b=uK4GzIYpvePeFkyevnpi38TEXF2jiE3e6ovb3A/1yfHfpvJIwJ+PkNFJX2Wjqh8s4F
         ocXLDJRfrGlOwM/Q/N67g5HX3M7nioJvmIvWKqT63KZd0MJulLfurAkudfvMeZxZEY3R
         fpPKGSlJDd9qVhb6xQFWaBy9DpOnWO3ky+BxUUKvhH2gSmgvojEE/TdUTx7xSX9KoLjB
         t4kd9c4A7b2NlMmzbnJ0l01eC/7TNmdry5LByn1Az8X0+hDvFUK2PTuzlBJS538srcay
         P/+QwnlvEVPyka/wp+VLuRP2V7bhi3B4zP23RrZRiTa/lekN1CY/XQaHCrC3CZz4IP45
         rXfQ==
X-Gm-Message-State: AOAM5334TJhmvb/sywszj495k6Gg78sP9xsVIAGbQhYg3D1H61HZ8kHG
        kghHS2ty4hOac3gU45FRpAXNcw==
X-Google-Smtp-Source: 
 ABdhPJxgAcS39rh9YdwtTC/8H4DgRISiHr+0k6ljiQIlbDwDcfbprOE9I0s2eFZWV5EzSucg+VEbOg==
X-Received: by 2002:a19:64b:: with SMTP id 72mr395811lfg.47.1603174745124;
        Mon, 19 Oct 2020 23:19:05 -0700 (PDT)
Received: from box.localdomain ([86.57.175.117])
        by smtp.gmail.com with ESMTPSA id
 t21sm137904lfl.64.2020.10.19.23.19.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 19 Oct 2020 23:19:04 -0700 (PDT)
From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Received: by box.localdomain (Postfix, from userid 1000)
        id B7950102017; Tue, 20 Oct 2020 09:19:01 +0300 (+03)
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: David Rientjes <rientjes@google.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        Kees Cook <keescook@chromium.org>,
        Will Drewry <wad@chromium.org>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        Liran Alon <liran.alon@oracle.com>,
        Mike Rapoport <rppt@kernel.org>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv2 01/16] x86/mm: Move force_dma_unencrypted() to common code
Date: Tue, 20 Oct 2020 09:18:44 +0300
Message-Id: <20201020061859.18385-2-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201020061859.18385-1-kirill.shutemov@linux.intel.com>
References: <20201020061859.18385-1-kirill.shutemov@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

force_dma_unencrypted() has to return true for KVM guest with the memory
protected enabled. Move it out of AMD SME code.

Introduce new config option X86_MEM_ENCRYPT_COMMON that has to be
selected by all x86 memory encryption features.

This is preparation for the following patches.

Signed-off-by: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
---
 arch/x86/Kconfig                 |  8 +++++--
 arch/x86/include/asm/io.h        |  4 +++-
 arch/x86/mm/Makefile             |  2 ++
 arch/x86/mm/mem_encrypt.c        | 30 -------------------------
 arch/x86/mm/mem_encrypt_common.c | 38 ++++++++++++++++++++++++++++++++
 5 files changed, 49 insertions(+), 33 deletions(-)
 create mode 100644 arch/x86/mm/mem_encrypt_common.c

```
#### [PATCH kvmtool] arm64: Determine kernel offset even on non-seekable file descriptors
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11846713
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76FBBC433DF
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 12:30:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 142FE22282
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 12:30:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394293AbgJTMaj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 08:30:39 -0400
Received: from foss.arm.com ([217.140.110.172]:50944 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405998AbgJTMaj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 08:30:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id F0E4030E;
        Tue, 20 Oct 2020 05:30:37 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.195.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D544F3F66E;
        Tue, 20 Oct 2020 05:30:36 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Marc Zyngier <maz@kernel.org>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvmtool] arm64: Determine kernel offset even on non-seekable
 file descriptors
Date: Tue, 20 Oct 2020 13:30:32 +0100
Message-Id: <20201020123032.167234-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c9acdae1d2e7 ("arm64: Use default kernel offset when the image
file can't be seeked") "guessed" the arm64 kernel offset to be the old
default of 512K if the file descriptor for the kernel image could not
be seeked. This mostly works today because most modern kernels are
somewhat forgiving when loaded at the wrong offset, but emit a warning:

[Firmware Bug]: Kernel image misaligned at boot, please fix your bootloader!

To fix this properly, let's drop the seek operation altogether, instead
give the kernel header parsing function a memory buffer, containing the
first 64 bytes of the kernel file. We read the rest of the file into the
right location after this function has decoded the proper kernel offset.

This brings back proper loading even for kernels loaded via pipes.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/aarch64/include/kvm/kvm-arch.h |  3 ++-
 arm/aarch64/kvm.c                  | 26 ++++++++------------------
 arm/kvm.c                          | 13 ++++++++++---
 3 files changed, 20 insertions(+), 22 deletions(-)

```
#### [PATCH v2 03/10] KVM: VMX: Fold Hyper-V EPTP checking into it's only caller
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847975
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ABC51C4363A
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B9F022247
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438951AbgJTV5E (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:57:04 -0400
Received: from mga12.intel.com ([192.55.52.136]:61052 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438819AbgJTV4Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:16 -0400
IronPort-SDR: 
 HYyWoVspMZxoz3ZJgvc0/kXH7bZoI6wH5W9FbykeMJjvIvMorHd4YBqh6ZZwlmsr0ox/FyD/4w
 w5EsBJgKUXsg==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576325"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576325"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:15 -0700
IronPort-SDR: 
 GlOXmRNn550G3EsI+dEiEhXtcZxA+2lgMaropeBr/0FxWV75WlmvL8l8vbuXgzkZIcbOT//OXP
 NwQO4KCR5Q9w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827730"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 03/10] KVM: VMX: Fold Hyper-V EPTP checking into it's only
 caller
Date: Tue, 20 Oct 2020 14:56:06 -0700
Message-Id: <20201020215613.8972-4-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fold check_ept_pointer_match() into hv_remote_flush_tlb_with_range() in
preparation for combining the kvm_for_each_vcpu loops of the ==CHECK and
!=MATCH statements.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 42 +++++++++++++++++++-----------------------
 1 file changed, 19 insertions(+), 23 deletions(-)

```
#### [PATCH v2 10/10] KVM: VMX: Track PGD instead of EPTP for paravirt Hyper-V TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847959
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4BAA9C388F2
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A7FF223BF
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438865AbgJTV4k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:40 -0400
Received: from mga12.intel.com ([192.55.52.136]:61055 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438840AbgJTV4T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:19 -0400
IronPort-SDR: 
 Lc7BWW8YtSVgcrgC5uK8cW8zJF6NAOe+pZ7IetIvYPqzQYysRAaO5pQF5x44v2ryD5DtlFnct0
 yiqRwRZvbLKQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576334"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576334"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:17 -0700
IronPort-SDR: 
 1TIZV8BOJVbsQzZODv96b8HrIpMMIQAcnQqLPdRjW8l2XIR/iq6vYH8BReydnrfwJZcpciGXYX
 OpZXP9Csi1ng==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827761"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:17 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 10/10] KVM: VMX: Track PGD instead of EPTP for paravirt
 Hyper-V TLB flush
Date: Tue, 20 Oct 2020 14:56:13 -0700
Message-Id: <20201020215613.8972-11-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track the address of the top-level EPT struct, a.k.a. the PGD, instead
of the EPTP itself for Hyper-V's paravirt TLB flush.  The paravirt API
takes the PGD, not the EPTP, and in theory tracking the EPTP could lead
to false negatives, e.g. if the PGD matched but the attributes in the
EPTP do not.  In practice, such a mismatch is extremely unlikely, if not
flat out impossible, given how KVM generates the EPTP.

Opportunistically rename the related fields to use the 'pgd'
nomenclature, and to prefix them with 'hv_tlb' to connect them to
Hyper-V's paravirt TLB flushing.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 53 +++++++++++++++++++-----------------------
 arch/x86/kvm/vmx/vmx.h |  6 ++---
 2 files changed, 27 insertions(+), 32 deletions(-)

```
#### [PATCH v2 05/10] KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP mismatch
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847963
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8CE6AC388F2
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46253223FB
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438849AbgJTV4U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:20 -0400
Received: from mga12.intel.com ([192.55.52.136]:61052 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438824AbgJTV4R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:17 -0400
IronPort-SDR: 
 m1pwwiwuFP8pf40EaZDAWRBkHr64VWva6ebVdXxzJXQcBJcLHvvJVerwfqRLo/AcF+QLlB6NFS
 C0y6nopyOHfw==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576328"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576328"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:16 -0700
IronPort-SDR: 
 uJzPh5WPII/Cn1CseZFrZXN5T7+iUBREMjq8DT2exYhRR4s9rbt8j1ncQD9ARAMH0gGQq4dSei
 4fD7mo1UnmEw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827741"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:16 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 05/10] KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP
 mismatch
Date: Tue, 20 Oct 2020 14:56:08 -0700
Message-Id: <20201020215613.8972-6-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop the dedicated 'ept_pointers_match' field in favor of stuffing
'hv_tlb_eptp' with INVALID_PAGE to mark it as invalid, i.e. to denote
that there is at least one EPTP mismatch.  Use a local variable to
track whether or not a mismatch is detected so that hv_tlb_eptp can be
used to skip redundant flushes.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 16 ++++++++--------
 arch/x86/kvm/vmx/vmx.h |  7 -------
 2 files changed, 8 insertions(+), 15 deletions(-)

```
#### [PATCH v2 02/10] KVM: VMX: Stash kvm_vmx in a local variable for Hyper-V paravirt TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847965
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DEEBC4363A
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 353AA2237B
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438833AbgJTV4S (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:18 -0400
Received: from mga12.intel.com ([192.55.52.136]:61050 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2392476AbgJTV4Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:16 -0400
IronPort-SDR: 
 V11oMn/zLBjIkPDMJ4PSCyDefQnh4FsSaKzbfzwoP6+uoG5G2fvd39IQr1QNTCruAmV37dyJLP
 /IYbqkcsAMYg==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576324"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576324"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:15 -0700
IronPort-SDR: 
 /3u1ANp75pizzhzNZXNb1oQHcCF+T1JqO8o4BFaAhy1F6ryM2G9cN9oH+bEEm9Vk2lcGEpbdzQ
 LqHXlk8Ey7RQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827725"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 02/10] KVM: VMX: Stash kvm_vmx in a local variable for
 Hyper-V paravirt TLB flush
Date: Tue, 20 Oct 2020 14:56:05 -0700
Message-Id: <20201020215613.8972-3-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Capture kvm_vmx in a local variable instead of polluting
hv_remote_flush_tlb_with_range() with to_kvm_vmx(kvm).

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH v2 06/10] KVM: VMX: Don't invalidate hv_tlb_eptp if the new EPTP matches
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847967
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF973C388F2
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73EAE2237B
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438927AbgJTV4w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:52 -0400
Received: from mga12.intel.com ([192.55.52.136]:61055 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438830AbgJTV4R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:17 -0400
IronPort-SDR: 
 8/ZCuackIyQ9Xj4ar4YNUxfnxcVI9ED4WI+9x/4l/GEyzeqVC+Kz/7WSpuz3Z0GgQ43jPubfgW
 6N/xitoNWssA==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576329"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576329"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:16 -0700
IronPort-SDR: 
 7mCi+CStn72T7erjpK83s/MWZS2sKT6C+dYb6+w84pIzYANid/1CY8LfJIqK+JIqg2hZDihP65
 80FQcZZuEYbA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827746"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:16 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 06/10] KVM: VMX: Don't invalidate hv_tlb_eptp if the new
 EPTP matches
Date: Tue, 20 Oct 2020 14:56:09 -0700
Message-Id: <20201020215613.8972-7-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't invalidate the common EPTP, and thus trigger rechecking of EPTPs
across all vCPUs, if the new EPTP matches the old/common EPTP.  In all
likelihood this is a meaningless optimization, but there are (uncommon)
scenarios where KVM can reload the same EPTP.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/10] KVM: VMX: Track common EPTP for Hyper-V's paravirt TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847961
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 04972C4363D
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADC5E2237B
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:56:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438825AbgJTV4Q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:16 -0400
Received: from mga12.intel.com ([192.55.52.136]:61050 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2438807AbgJTV4P (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:15 -0400
IronPort-SDR: 
 DgidWhlLCBLF7+k4p74s2OuFdrhjW+Fjzs2QHeYgewr7HTDRoxPsgoP3ujbuYcy4Wy9aXHLhvl
 PqfSfoQdNLaA==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576323"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576323"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:15 -0700
IronPort-SDR: 
 cOUZ6k3xd/1OjjHJci/Y239nTI5oJaJQAJtOg4YdcQ8HxkLyBG5dpNAkcRKdqlPn7A/hDxiCts
 LKO/gnnJGhRw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827717"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:14 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/10] KVM: VMX: Track common EPTP for Hyper-V's paravirt
 TLB flush
Date: Tue, 20 Oct 2020 14:56:04 -0700
Message-Id: <20201020215613.8972-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201020215613.8972-1-sean.j.christopherson@intel.com>
References: <20201020215613.8972-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly track the EPTP that is common to all vCPUs instead of
grabbing vCPU0's EPTP when invoking Hyper-V's paravirt TLB flush.
Tracking the EPTP will allow optimizing the checks when loading a new
EPTP and will also allow dropping ept_pointer_match, e.g. by marking
the common EPTP as invalid.

This also technically fixes a bug where KVM could theoretically flush an
invalid GPA if all vCPUs have an invalid root.  In practice, it's likely
impossible to trigger a remote TLB flush in such a scenario.  In any
case, the superfluous flush is completely benign.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 19 ++++++++-----------
 arch/x86/kvm/vmx/vmx.h |  1 +
 2 files changed, 9 insertions(+), 11 deletions(-)

```
