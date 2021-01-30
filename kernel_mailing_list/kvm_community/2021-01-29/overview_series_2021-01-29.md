#### [kvm-unit-tests PATCH v3 01/11] lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12056029
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 13B1FC433E6
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9E0E64DEB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:38:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231335AbhA2QiP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 11:38:15 -0500
Received: from foss.arm.com ([217.140.110.172]:51060 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230249AbhA2Qh4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 11:37:56 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 51AAE1424;
        Fri, 29 Jan 2021 08:37:10 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 5B78A3F71B;
        Fri, 29 Jan 2021 08:37:09 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com, Eric Auger <eric.auger@redhat.com>
Subject: [kvm-unit-tests PATCH v3 01/11] lib: arm/arm64: gicv3: Add missing
 barrier when sending IPIs
Date: Fri, 29 Jan 2021 16:36:37 +0000
Message-Id: <20210129163647.91564-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210129163647.91564-1-alexandru.elisei@arm.com>
References: <20210129163647.91564-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

One common usage for IPIs is for one CPU to write to a shared memory
location, send the IPI to kick another CPU, and the receiver to read from
the same location. Proper synchronization is needed to make sure that the
IPI receiver reads the most recent value and not stale data (for example,
the write from the sender CPU might still be in a store buffer).

For GICv3, IPIs are generated with a write to the ICC_SGI1R_EL1 register.
To make sure the memory stores are observable by other CPUs, we need a
wmb() barrier (DSB ST), which waits for stores to complete.

From the definition of DSB from ARM DDI 0487F.b, page B2-139:

"In addition, no instruction that appears in program order after the DSB
instruction can alter any state of the system or perform any part of its
functionality until the DSB completes other than:

- Being fetched from memory and decoded.
- Reading the general-purpose, SIMD and floating-point, Special-purpose, or
System registers that are directly or indirectly read without causing
side-effects."

Similar definition for armv7 (ARM DDI 0406C.d, page A3-150).

The DSB instruction is enough to prevent reordering of the GIC register
write which comes in program order after the memory access.

This also matches what the Linux GICv3 irqchip driver does (commit
21ec30c0ef52 ("irqchip/gic-v3: Use wmb() instead of smb_wmb() in
gic_raise_softirq()")).

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/gic-v3.c | 6 ++++++
 arm/gic.c        | 5 +++++
 2 files changed, 11 insertions(+)

```
#### [RFC v4 1/3] vfio/platform: add support for msi
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 12056213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,
	SPF_HELO_NONE,SPF_PASS,T_TVD_MIME_NO_HEADERS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 285C7C433DB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D80DD64E02
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232492AbhA2RZt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 12:25:49 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50338 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232418AbhA2RZV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 12:25:21 -0500
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B411FC06174A
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 09:24:41 -0800 (PST)
Received: by mail-pf1-x444.google.com with SMTP id y205so6635991pfc.5
        for <kvm@vger.kernel.org>; Fri, 29 Jan 2021 09:24:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=POtj3/lfdVAatOz+3UWgLmFqHV2ZKe94zk3hNOwyyoY=;
        b=RO8yD/jw7byCI2jWRY2k6IC0NgHPqt5aBtis+tMqm09Q/jbmT/BfmZevxZxSXm7xCH
         iZRLvUqmmvTHdDDdRQgBwXTRVJfgoSe5TdNdisT98Xss6zgtVikwV58fAYTazdP8uvMn
         vupXIy2hY7yQQzx+7Wc0thD/+nExU9w9mjGWw=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=POtj3/lfdVAatOz+3UWgLmFqHV2ZKe94zk3hNOwyyoY=;
        b=ZyFh/l2Q0ePcGuvaTLSprGkOgx+Zbsc5Hxsnp7HPk3UFuFg7ckEyV9OasHFc5UhO01
         ZM6wOiwxB5jdoy+7NXWb3YejyB8BqtrgFwke/ZH15yCbfT7hdZeAnWSihPd++7Qh2Qjd
         pb+9QC87s2nb73V3v4Au5WqFUPRKzNew0lvm9Gr8Btys6skWhjr/i/i1kFGl+nZl/3OM
         pVSkp0WGc0oE1YojCHrqTgeihmXWNf18aW70jIzMzGxaZlBMpkoQl4OCQ9XjlbRznUQi
         rRpg/dUl2TBQOHm9BuE8z/oQMmB8ZqBkFgTj7KwxkyvaRYIxovwCBLsXuPTS7ozN8Wyc
         YzLQ==
X-Gm-Message-State: AOAM531izhsYNh8dHVOkg7nS4UsXyKq1oncaz/pL7UJb3aaQLYvaKiS+
        scermWBPreqn/fMJuC6/EV01fg==
X-Google-Smtp-Source: 
 ABdhPJz1xHFhalJwgQpRsOh6aBRd1jc4JPmpAvYMGE0iehFeBEbbof5H6cBxTO+KDZYRinaQkBk3ZQ==
X-Received: by 2002:a62:5881:0:b029:1c9:d72d:34d5 with SMTP id
 m123-20020a6258810000b02901c9d72d34d5mr5365191pfb.68.1611941080824;
        Fri, 29 Jan 2021 09:24:40 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 w11sm9739016pge.28.2021.01.29.09.24.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 29 Jan 2021 09:24:40 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC v4 1/3] vfio/platform: add support for msi
Date: Fri, 29 Jan 2021 22:54:19 +0530
Message-Id: <20210129172421.43299-2-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210129172421.43299-1-vikas.gupta@broadcom.com>
References: <20201214174514.22006-1-vikas.gupta@broadcom.com>
 <20210129172421.43299-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSI support for platform devices. MSI is added
as a single 'index' with 'count' as the number of
MSI(s) supported by the devices.

Signed-off-by: Vikas Gupta <vikas.gupta@broadcom.com>
---
 drivers/vfio/platform/Kconfig                 |   1 +
 drivers/vfio/platform/vfio_platform_common.c  |  95 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 253 ++++++++++++++++--
 drivers/vfio/platform/vfio_platform_private.h |  29 ++
 include/uapi/linux/vfio.h                     |  24 ++
 5 files changed, 373 insertions(+), 29 deletions(-)

```
#### [PATCH] selftest: kvm: x86: test KVM_GET_CPUID2 and guest visible CPUIDs against KVM_GET_SUPPORTED_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12056021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C06D9C433DB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:37:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89E5A64D9D
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 16:37:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231195AbhA2Qhh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 11:37:37 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60529 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231758AbhA2Qgc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 Jan 2021 11:36:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611938104;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=d4EkjZHv3aQhO7MDtkrDXoF3N3i9BK5sLlGFVxdQjkQ=;
        b=Y0VAHAbb8aPQwFGqoN0VZkepisg8Wx5ajCpW9bHlzrt5+NgyO/bEMZjynIBdHizuI1CMY2
        D0XweAsvKwlO0tzaM8J+M/reF48SwIeTDgV9FZy53H8r+WvmasGs6YT7u89wr2UnsrUugW
        jgua/sxP06s2UaHxPKQBI6ksKk7iO9U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-334-q9_cCUFnPlSr4sRE8dQp_w-1; Fri, 29 Jan 2021 11:18:26 -0500
X-MC-Unique: q9_cCUFnPlSr4sRE8dQp_w-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3B31784A5E4;
        Fri, 29 Jan 2021 16:18:25 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.151])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 10CF55C290;
        Fri, 29 Jan 2021 16:18:22 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Michael Roth <michael.roth@amd.com>
Subject: [PATCH] selftest: kvm: x86: test KVM_GET_CPUID2 and guest visible
 CPUIDs against KVM_GET_SUPPORTED_CPUID
Date: Fri, 29 Jan 2021 17:18:21 +0100
Message-Id: <20210129161821.74635-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 181f494888d5 ("KVM: x86: fix CPUID entries returned by
KVM_GET_CPUID2 ioctl") revealed that we're not testing KVM_GET_CPUID2
ioctl at all. Add a test for it and also check that from inside the guest
visible CPUIDs are equal to it's output.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore        |   5 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |  14 ++
 .../selftests/kvm/lib/x86_64/processor.c      |  42 +++++
 .../selftests/kvm/x86_64/get_cpuid_test.c     | 175 ++++++++++++++++++
 5 files changed, 237 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/get_cpuid_test.c

```
#### [PATCH v2] KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if tsx=off
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12055885
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 001B3C433E6
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 11:57:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B00EE65014
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 11:57:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232180AbhA2L5Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 06:57:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:51764 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232349AbhA2L42 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 29 Jan 2021 06:56:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611921001;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=cMS/7pknUs0YwtKE5mir0RQEvSlJ4gZuoZK/GL0Bh2Y=;
        b=V+Np74pZDHBoxkmgbxmuV5QR72nl7GYRg1cmm1E6F80+/vlw9SAxt4axUwlmR6YcUSy2Th
        882wWKdPVpIlxmFqNRgN0hksybcJSqaPokw4oXjKHkNZ4d9330R317eXQTEprVMF3dc1sr
        aVzMJloSOHcCwj07URmM//MbxvF/pJc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-351--eV7d5yzP3q2OGNv-XIFLQ-1; Fri, 29 Jan 2021 05:19:15 -0500
X-MC-Unique: -eV7d5yzP3q2OGNv-XIFLQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ECCB418C8C01;
        Fri, 29 Jan 2021 10:19:13 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7317B60C04;
        Fri, 29 Jan 2021 10:19:13 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com, seanjc@google.com, stable@vger.kernel.org
Subject: [PATCH v2] KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if
 tsx=off
Date: Fri, 29 Jan 2021 05:19:12 -0500
Message-Id: <20210129101912.1857809-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userspace that does not know about KVM_GET_MSR_FEATURE_INDEX_LIST
will generally use the default value for MSR_IA32_ARCH_CAPABILITIES.
When this happens and the host has tsx=on, it is possible to end up with
virtual machines that have HLE and RTM disabled, but TSX_CTRL available.

If the fleet is then switched to tsx=off, kvm_get_arch_capabilities()
will clear the ARCH_CAP_TSX_CTRL_MSR bit and it will not be possible to
use the tsx=off hosts as migration destinations, even though the guests
do not have TSX enabled.

To allow this migration, allow guests to write to their TSX_CTRL MSR,
while keeping the host MSR unchanged for the entire life of the guests.
This ensures that TSX remains disabled and also saves MSR reads and
writes, and it's okay to do because with tsx=off we know that guests will
not have the HLE and RTM features in their CPUID.  (If userspace sets
bogus CPUID data, we do not expect HLE and RTM to work in guests anyway).

Cc: stable@vger.kernel.org
Fixes: cbbaa2727aa3 ("KVM: x86: fix presentation of TSX feature in ARCH_CAPABILITIES")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 17 +++++++++++++----
 arch/x86/kvm/x86.c     |  2 +-
 2 files changed, 14 insertions(+), 5 deletions(-)

```
#### [PATCH V3 1/9] vfio: option to unmap all
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 12056205
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5AF84C433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2849164E00
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 17:25:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232392AbhA2RZI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 29 Jan 2021 12:25:08 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:40434 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231511AbhA2RZF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Jan 2021 12:25:05 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10THO6CI066205;
        Fri, 29 Jan 2021 17:24:22 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=Jht8y0GDOpOhrB/UuJl9RZfl5NEsnAsBx4Quts4qYrY=;
 b=zELMBsmOQWEBn/zDBYbc6Hopw4hRvdR6v66cSCojomSAuOPdvTojJ+HclIhUhA5VoEgH
 NklqPVv0U4cg/X3IbQfvR45rzaGLeyEgBRAAbSISbpMEgAY5u8HG6flV0vV75l1vqH+i
 fYncaj+n5G+CLVO+2GQPQLq0LqqD0lbGf47RmBH11XxCFz6L+ST48SZp0vYyT7Huoekh
 xumnL+URivKh+GY0VcUciQJBfDzyhn8TORfjI/fPTpYuo/oSeUIrd8iUh9TwpoHvIIgK
 Fz6LLuZEtJowQ7/kPEYwyhyJZYNWClZtHAJG1qhdoWAdWvNXcvAfSyMpMsb7DyqV7SU4 2g==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 368b7rafbh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 29 Jan 2021 17:24:22 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10TH5IpQ077004;
        Fri, 29 Jan 2021 17:22:20 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 368wcsfkn0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 29 Jan 2021 17:22:20 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 10THMJXn019219;
        Fri, 29 Jan 2021 17:22:19 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 29 Jan 2021 09:22:19 -0800
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V3 1/9] vfio: option to unmap all
Date: Fri, 29 Jan 2021 08:54:04 -0800
Message-Id: <1611939252-7240-2-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611939252-7240-1-git-send-email-steven.sistare@oracle.com>
References: <1611939252-7240-1-git-send-email-steven.sistare@oracle.com>
X-Proofpoint-IMR: 1
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9879
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 suspectscore=0
 phishscore=0 mlxlogscore=999 bulkscore=0 malwarescore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101290084
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9879
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 spamscore=0 phishscore=0
 adultscore=1 impostorscore=0 malwarescore=0 lowpriorityscore=0 bulkscore=0
 priorityscore=1501 mlxscore=0 clxscore=1015 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101290085
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For the UNMAP_DMA ioctl, delete all mappings if VFIO_DMA_UNMAP_FLAG_ALL
is set.  Define the corresponding VFIO_UNMAP_ALL extension.

Signed-off-by: Steve Sistare <steven.sistare@oracle.com>
---
 include/uapi/linux/vfio.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v4 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL featureFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12054811
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69159C433DB
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:46:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2988264DEC
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:46:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231604AbhA2AqC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 19:46:02 -0500
Received: from mail-dm6nam11on2040.outbound.protection.outlook.com
 ([40.107.223.40]:41665
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231459AbhA2Aos (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 19:44:48 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=TKq6Vka/tWULRoKEe/S6DQG5AgkBeemdA6TxOI2Y6rBHB/LW826etPHHCrJhDUYN1Oe9mjisX9Ks5Dwm4NTpGUfqpbHE6EqsdqXs10E7zztYInAuIMCcnTeCF0cVMNHleG+RjP6B9UP7wF+r9s9ZpIeCjcku8+xoB6Dgo0IAA/HvNrdzyEhOlwbIgrvtFb5EmWgWcd6OZYgGbrlGsWiduH5IwQDGRBQAPuwhIfWVDRbY8xp5m2807Rc3BUkzrMOOhsLs76e3nsH/EQrbz5PehrTqmg+N9iYgpcyfsvcjlBuNo8u8d1pqr5EGeAwiDUVEG2yNbX+p7dY6EviV9wmI0w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CF4J1hbbttjCvzB0KcY0I9jxXx45BP3e7FK7pX8dQ8Q=;
 b=BFB2HfBMAGQUBBSkPimiOcSl6T+fp/ERYjjHh8hNoAkLOh20GjKZXTzOF8X5PYlPFV9TjVpULLR1CJtbXPi3hDQCZ4I72p+La5eXVKKcFX2OQT/Y2X4riSftIYyZ4uncqTDRlB6pZZEtoZ5sn+bPIbDOGWiJv5DPR+pMUQ7zU7ToYdZfZdNBJ80ZcLohpR+di2oEFQIKpTedc4PM8H65Dj+xfpvsX5RVgpPPj9H02PE7EdgAyDPBTjCb/yZIJOIUK8XKrn9RvE649g1akyMoXYX6+BDE48IDNEzP6eR1BpFPJdi9tlmTQAx/zFYDCAEvpCpVRfqnU2mgtQO8HmUnjw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CF4J1hbbttjCvzB0KcY0I9jxXx45BP3e7FK7pX8dQ8Q=;
 b=V5P7WmaDwYwn9qNupGJpOVVaOJtpW4QONnSpUSvrQh18Z7t7nyhZ81HjX0MBFC3xdrbhjevQSdrkgTFdcmvZFsTAjMNtHzh8BMhJO1AcBo+2RREVKxEijKUdG9vBBYSfV1GpgYQwaALYwomwfe+OKMrPrN/86IxST5ameSZia/E=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Fri, 29 Jan
 2021 00:43:24 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3805.019; Fri, 29 Jan 2021
 00:43:24 +0000
Subject: [PATCH v4 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL feature
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Thu, 28 Jan 2021 18:43:22 -0600
Message-ID: <161188100272.28787.4097272856384825024.stgit@bmoger-ubuntu>
In-Reply-To: <161188083424.28787.9510741752032213167.stgit@bmoger-ubuntu>
References: <161188083424.28787.9510741752032213167.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA9PR13CA0236.namprd13.prod.outlook.com
 (2603:10b6:806:25::31) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SA9PR13CA0236.namprd13.prod.outlook.com (2603:10b6:806:25::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.8 via Frontend
 Transport; Fri, 29 Jan 2021 00:43:23 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: de15430a-e38a-48c1-bd4f-08d8c3eee278
X-MS-TrafficTypeDiagnostic: SN1PR12MB2560:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2560658094386A689B8A41E995B99@SN1PR12MB2560.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1388;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 w/gjyunOwikS2pHW0YuWutY7hq++DPgcetead33dAtVgSGHt903e/Rmt49qEv3bbXY3tNMWbkwA+Wzx7EsYLxqLpV/ptrbIEpWzLGs7/JD8Ralby8koqSBim5Xlxm4xnDdFEVyusl4o+1MqAerrmXSSsRtpw2fJZC29ZPuydABpwI/5ZCnW2IB/iajtl2UaueZ6W4qMctprDuHuq5WvXfedkdAIh5Yi3xmfdApGWfPfoJf4CRMW+rQTfg2GMWdyD3cKio1vNap1+Cd3ba0FQQ3aC5vLm/seM+9TWShp21RqE1CPnw75/jvZV6b9EFfaHJOvc6IhVs2VUgMTAuxq0c4Y/1A5gB15+uKBB2eLbOGAGE50eeRtiNrXLo/VQP5q2rEheAKWomjE+f3/ekjvRwjkttM9kAIosHehuyn3kqjUwdyEjAFAgR6D70FV65HaWp2858Cae/HXwgt+qn0PVH9H3XDHaVohHrdVk/n6VR8wptZhvizKcheOS/2zy+PGg3Y9npJXWQVikmKsn+wBMDw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(396003)(39860400002)(136003)(366004)(346002)(376002)(956004)(16576012)(52116002)(7416002)(8936002)(8676002)(316002)(86362001)(103116003)(44832011)(16526019)(186003)(33716001)(4326008)(478600001)(6486002)(9686003)(66476007)(66556008)(5660300002)(26005)(2906002)(66946007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?vyjDI32oYpxnmwtUyivdqnNFP4w0HF?=
	=?utf-8?q?xr3WCS5NUZlM3xPlI7SBCzH9JypTOkQykTgMVw6L0FMxwU14ck1J6Jt6FEoyiBNaD?=
	=?utf-8?q?LIulIK+Sivh0078coqTrXXrUMx1dPfIcKW0WDxHijJ+htGnJZb97sgDlZNnU1YlQv?=
	=?utf-8?q?/cJ7gEwwVekllaih3S9BllF7hcNboaJC7Gy3GWjEf+paJ8iRnLU1YWRG3bLkEf1eA?=
	=?utf-8?q?u84XOqcicKOWgytwoTE6sP4olw2SO39CaSFe1X/vw1ZLk761m3uLSkHs0hiL42EpQ?=
	=?utf-8?q?8RXAe8+hXxvU/EU8kL4XRh9REoSqGSEq9WndgPAQQjP9m0GJWFG0tr/tOBgJ2yuEb?=
	=?utf-8?q?TjYQLXxKC931koJJHMhfm8rQUpldn2+51TWRzXslxnJQA6JMnqNy/KSd990ciBxP6?=
	=?utf-8?q?S9nT9eB95HKsSGe/S5sOOMUxiJ2pkG+0vOLAjeWDmGtVZSvc3YTiWgVW3HrefRMH8?=
	=?utf-8?q?Qx2KiEsfe2fJFslUY/MQDowITCcUbPHtpZKn/ubqiXPjYfFJcx2ydnVK3ToC6FvCU?=
	=?utf-8?q?MpwHr25oT138c6qHC7CbzSfeD1KWPtVUaezon2XmgQ7/Xi/R9BDwhTan65zK/JxTT?=
	=?utf-8?q?leHlwc03SuTQoue71nkyL6X/IE+nq6U3jBQXDduEb2H6AewE1Nw14JzenhtHXqO/A?=
	=?utf-8?q?xGgblWm9O8lblWNdvYnJFfkYMs3BrlRLc4xBdUd6ZezRqgQDi/6oJNlZn1IZvHHmj?=
	=?utf-8?q?jZQmgobsnJZEPY0dqlSlmfwtyjeBwyqXrjMRlafh6k+Uo/pziSC52uLs5TV+3bPNI?=
	=?utf-8?q?zQzg2FmvY8R/1wnk/2SXn7Bu1nPwge5IxuLgXb/frnfqvvAHVnGhvShqpdNjVtLi4?=
	=?utf-8?q?hZm/9xKQ0J3j+mM3pfNcCWWhByPzSivEG86YEwjwbveOTWdzx968L87ETz7FNV/EE?=
	=?utf-8?q?K9sME4fUrwH0yqwUxb4mO2hoyE8WRVi5lTZ226YMmP3DR8jhpC1nwt2CQyAUarZzD?=
	=?utf-8?q?2q5TNBBehzcMbyBYVaIb7PvQN2GDOutYbcZBBGRY2Rnh9AIqdmu25EtehIxufUeOD?=
	=?utf-8?q?zHCTJkkR0Tlca0qFqN?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 de15430a-e38a-48c1-bd4f-08d8c3eee278
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Jan 2021 00:43:24.3610
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 uSSRzNK0lfttjnTULG947f13wFC1Bgli6ByHLmsZnMjfjINJAN49gJ/d7nbdMFbR
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2560
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of the
SPEC_CTRL MSR. Presence of this feature is indicated via CPUID
function 0x8000000A_EDX[20]: GuestSpecCtrl. When present, the
SPEC_CTRL MSR is automatically virtualized.

Signed-off-by: Babu Moger <babu.moger@amd.com>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/cpufeatures.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH v2 1/2] x86: Add SPEC CTRL detection testsFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12054805
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFF9FC433E0
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:39:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C45D61481
	for <kvm@archiver.kernel.org>; Fri, 29 Jan 2021 00:39:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231394AbhA2AjK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 19:39:10 -0500
Received: from mail-mw2nam10on2052.outbound.protection.outlook.com
 ([40.107.94.52]:39681
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231387AbhA2Ah5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 19:37:57 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=LBKiDkDt1bMNL6gFOJ7acDvmgQc7ssDhaf317CLZJD4SqliseZbHfJXF17jK+TIfz1X3P1zclr9+kjgH109k0VQACKIY4km4eQig4obp0NbdYtJt/IMrTVT4e0yk6ik4jXWOybT07yHDKvxaDfmOjHAjW6E6047uPb45mhOKK4KbqhldGzSC3tSeQYkVfbp+zyU6f+ISs/JHs23PnOtZHIMRlnmnZ2nAwG5h0xgyulAnmnjEIfliqlBri5wx5+lxUqI0C2AQEHus06jncfZtHL7W5rEK6PhOO5I+LUwu03CHh6rka74ZdGukFhlEAbKi1LydHpGLr4DgomasKBen+g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LroqR7U1lDdU3oQnauGVHLHLnWXk3xAM7TJ0lqnX5Qo=;
 b=cKvqhEQJg2s1ZAnMmlkOTBak6rsyWi1G2Ic9m3gIS3EmdD8p9oibv/nk0xH21Le+nhGxXXWpAN2UGABmGhjuR3W4EHA8ptrQ989UVM1Cb9xkJTMGu9hsZim9lVk/ThOjZGCdYFvu3NPri/h7S4EtFEBwfKmoiFme9N3f8X/uPVcOUlfxaaEfDsebx5YETuUTfLT+vjoIcH8GjqEfY9Uru0hoWYILlXmm3nDHQHJFlQl8tGd7XHK8f/Kqi6fBHoE6BPlnPCN0k8phrrE4+YPpnMNZylJ2pa2ky5C/UYmecgHwYkrppBUzad94e6n3sePTd2s1IydD3yZ3g1QRp2b1aA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LroqR7U1lDdU3oQnauGVHLHLnWXk3xAM7TJ0lqnX5Qo=;
 b=t/uNLI5dfmhOBAXKKLQb7C+kuZNSPPEyK1IIu3hiLAs9+i0PD0YS89aAKNqYKZ6jv/GNqlR2IZf6TECsSJkn2IwjsnIy8NuzOoYly7OPDQBAVjyq2FwJejXCMc/4X+yGU/URVVWGPUcwt2L8N4yQEgXzeo4HIQ4qt0fZGeYbWxI=
Authentication-Results: amd.com; dkim=none (message not signed)
 header.d=none;amd.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2525.namprd12.prod.outlook.com (2603:10b6:802:29::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.17; Fri, 29 Jan
 2021 00:36:20 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3805.019; Fri, 29 Jan 2021
 00:36:20 +0000
Subject: [kvm-unit-tests PATCH v2 1/2] x86: Add SPEC CTRL detection tests
From: Babu Moger <babu.moger@amd.com>
Cc: kvm@vger.kernel.org
Date: Thu, 28 Jan 2021 18:36:19 -0600
Message-ID: <161188057905.28708.10578820564970956832.stgit@bmoger-ubuntu>
In-Reply-To: <161188044937.28708.9182196001493811398.stgit@bmoger-ubuntu>
References: <161188044937.28708.9182196001493811398.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0052.namprd11.prod.outlook.com
 (2603:10b6:806:d0::27) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SA0PR11CA0052.namprd11.prod.outlook.com (2603:10b6:806:d0::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Fri, 29 Jan 2021 00:36:20 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: e6e041d1-cbff-44fa-7c36-08d8c3ede5b1
X-MS-TrafficTypeDiagnostic: SN1PR12MB2525:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB25255EED357F61F8755948AE95B99@SN1PR12MB2525.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1388;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 gb3WompLLSYOkYCz5cUpx2iNOIS9yYZSt7IuHVrIK/wmM8fjQRjRrYQdS30cp47TcSImj+xV1d3cMWWYWdOS8Ixuft8PXYawUpgAnb86B9m7dwj2B6dUmbpT72MfPfnbWNlso05I04utVmhBomA6LRv3+hYJChb268yDsSdcBhH5g36h2f6+B84FglXdS3AE1ehauizmcA/aRsIXLyc9iy67HOeRU0MhIDEflV6qHHed7KIsYix6LI2F+FKIU3B0MHKRX1A/q9c5Zon7XzbjnBkb4zsetZgg+o8mutHNYU1Kzt5EotSOWGsPLm8x6pYGqTfoIq40SXZiiiLJ80zmitExKT4DhHREOQtm6aMlQC/IOXasU1zpAH3HN/B+85Y4GPT2XSK6PUJ2sgBDaktDk501XsjnaezHpgLHTRU5oWntcZFDRpega5tJhEZQG9E1kaW9z5SNX9Ye0o7+nrT1J93oWjAfgMvVZWY+fkXPrqZP94T7stW8gRpy2bwyWa3vv+pQdgx+YJTVCzGmUdqrnA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(396003)(346002)(39860400002)(366004)(136003)(376002)(83380400001)(2906002)(103116003)(66946007)(8936002)(8676002)(52116002)(4326008)(86362001)(66476007)(66556008)(109986005)(186003)(6486002)(478600001)(16526019)(26005)(5660300002)(33716001)(44832011)(316002)(16576012)(9686003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?drrdcVCIm0jCcmp70z/U+cVRL8cZQY?=
	=?utf-8?q?7UVYttDpiXnhdcMcLSUSLDQTCOsnHwuIWwY8k4y+dMz9o7O94mPF16S4MKEe5jskd?=
	=?utf-8?q?DulucOKx6g69URbj0LlZGjVWSkbhpOR2xY6SKB5jg+6Fq0kvC7CxJQ2IlqR8vygAE?=
	=?utf-8?q?GW9DRayY2VhTHLBu67chAIYzgv3Npt86BCVZaOUIT0v9KIOlnwCwkDScc5wc76kN4?=
	=?utf-8?q?WoniDDVVUGUSmVMaNSSS2EBBrRMHhBxdbar+obEil/amVHTzMbjlI9nPGsQ742gAC?=
	=?utf-8?q?t+mZF1LfXh8FK8mKvf8QU2Vjb/TlFYAAICsekgw7Cc/yiJ2JEFvWLQBhnLD5IwFR7?=
	=?utf-8?q?9hivhDNQ6kRnYrHA9nwHceaCth4K/MdZphR6a+ND+9OzSHIB0Cwy30h3lDscyxeLl?=
	=?utf-8?q?JZCkN7SQLWMyu54vthLCImffxVEdeJqx6OQZslzRmuLn4xcSXea22hZTi32v3XzAt?=
	=?utf-8?q?0gANL4eNQ06Q+4DEYCjZA1U7XqwZGWn9rfPWSnL94dP27z9d/hAZsz0lEpJSQFkkl?=
	=?utf-8?q?a5hu7F+cqII5VOWfjFl1cmCiLEDGUlqAPdQBrysY5pLeE5KVTWC9TR/VMyUvJzxgH?=
	=?utf-8?q?w8tjEScH5mFSvqnT/BJ1Hs0xIx9QssdJbkWWaV7O+GVJnvz3Tl9DGPrT/jH3Wsh0X?=
	=?utf-8?q?73gDXsEH9uWOdOyIbYNPOXXlFkcJpc0XD2klVgQLW+fAop1AW0vEV2+S4U7v1I2YM?=
	=?utf-8?q?R8XOO0XEAB9ewNzOF/zxPmetxNiUEJzW3k8HFmLzc992KPcPYpFt9UHJVxPNNquJt?=
	=?utf-8?q?2ob3s4Ig27WdtxCX08F9/0gY7CYD/6AyhbmPF5immnEKQCtf5Gr050a0DS6hjb/jV?=
	=?utf-8?q?KMkr2BcF8JNrxuXthzdKOIQifhmWZV4bcM9Ndi7PNFqLyA4gN4CtZPKZetsCmx6Rh?=
	=?utf-8?q?fh5mMEhhgi+zIZFErh5H0zIf5vddZQonFRKiXgQm6yRSLUMUw5g1fBh1nOsAmfHfY?=
	=?utf-8?q?mbBwiPgzijOPr6jcawcYLcNxfbEIXh2GVMBKli+FV1QeUVAkpoz89mp/vRt/4XsuQ?=
	=?utf-8?q?jSxTKiLaS27G1WSPma?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e6e041d1-cbff-44fa-7c36-08d8c3ede5b1
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Jan 2021 00:36:20.5192
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 AYRY3A05VyWaYpjbhg5WnBzlOvK0RVX5zcT9YrS3j5oJk9UVBEhbrEgGd5/MuAKf
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2525
To: unlisted-recipients:; (no To-header on input)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Detect the available SPEC CTRL settings on the host.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 lib/x86/processor.h |    5 +++++
 x86/Makefile.x86_64 |    1 +
 x86/spec_ctrl.c     |   30 ++++++++++++++++++++++++++++++
 x86/unittests.cfg   |    5 +++++
 4 files changed, 41 insertions(+)
 create mode 100644 x86/spec_ctrl.c

```
