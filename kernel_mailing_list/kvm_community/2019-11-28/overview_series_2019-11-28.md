#### [kvm-unit-tests PATCH v2 01/18] lib: arm/arm64: Remove unnecessary dcache maintenance operations
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11266475
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DDA3921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 18:04:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4FB6221771
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 18:04:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726610AbfK1SEc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 13:04:32 -0500
Received: from foss.arm.com ([217.140.110.172]:39304 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726401AbfK1SEc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 13:04:32 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id D6BC631B;
        Thu, 28 Nov 2019 10:04:31 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 BB6DF3F6C4;
        Thu, 28 Nov 2019 10:04:30 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, drjones@redhat.com,
        maz@kernel.org, andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH v2 01/18] lib: arm/arm64: Remove unnecessary
 dcache maintenance operations
Date: Thu, 28 Nov 2019 18:04:01 +0000
Message-Id: <20191128180418.6938-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191128180418.6938-1-alexandru.elisei@arm.com>
References: <20191128180418.6938-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On ARMv7 with multiprocessing extensions (which are mandated by the
virtualization extensions [1]), and on ARMv8, translation table walks are
coherent [2][3], which means that no dcache maintenance operations are
required when changing the tables. Remove the maintenance operations so
that we do only the minimum required to ensure correctness.

Translation table walks are coherent if the memory where the tables
themselves reside have the same shareability and cacheability attributes
as the translation table walks. For ARMv8, this is already the case, and
it is only a matter of removing the cache operations.

However, for ARMv7, translation table walks were being configured as
Non-shareable (TTBCR.SH0 = 0b00) and Non-cacheable
(TTBCR.{I,O}RGN0 = 0b00). Fix that by marking them as Inner Shareable,
Normal memory, Inner and Outer Write-Back Write-Allocate Cacheable.

The ARM ARM uses a DSB ISH in the example code for updating a
translation table entry [4], however we use a DSB ISHST. It turns out
that the ARM ARM is being overly cautious and our approach is similar to
what the Linux kernel does (see commit 98f7685ee69f ("arm64: barriers:
make use of barrier options with explicit barriers")); it also makes
sense to use a store DSB barrier to make sure the new value is seen by
by the next table walk, which is not a memory operation and not affected
by a DMB.

Because translation table walks are now coherent on arm, replace the
TLBIMVAA operation with TLBIMVAAIS in flush_tlb_page, which acts on the
Inner Shareable domain instead of being private to the PE.

The functions that update the translation table are called when the MMU
is off, or to modify permissions, in the case of the cache test, so
break-before-make is not necessary.

[1] ARM DDI 0406C.d, section B1.7
[2] ARM DDI 0406C.d, section B3.3.1
[3] ARM DDI 0487E.a, section D13.2.72
[4] ARM DDI 0487E.a, section K11.5.3

Reported-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu.h           |  4 ++--
 lib/arm/asm/pgtable-hwdef.h |  8 ++++++++
 lib/arm/mmu.c               | 18 +++++-------------
 arm/cstart.S                |  7 +++++--
 4 files changed, 20 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: arm64: eliminate unnecessary var err and jump label in set_core_reg()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11265365
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF9A8138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:10:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B8D78206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:10:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727773AbfK1DKH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 22:10:07 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:53054 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727113AbfK1DKH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 22:10:07 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 351A96ADCDBDC841C9DC;
        Thu, 28 Nov 2019 11:10:05 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Thu, 28 Nov 2019
 11:09:55 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: arm64: eliminate unnecessary var err and jump label in
 set_core_reg()
Date: Thu, 28 Nov 2019 11:09:58 +0800
Message-ID: <1574910598-14468-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The var err and jump label out isn't really needed in
set_core_reg(). Clean them up.
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arch/arm64/kvm/guest.c | 13 ++++---------
 1 file changed, 4 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: arm64: get rid of var ret and out jump label in kvm_arch_vcpu_ioctl_set_guest_debug()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11265361
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A53F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:09:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6383121739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:09:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727673AbfK1DJs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 22:09:48 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:37220 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727616AbfK1DJs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 22:09:48 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 856BAF4DD1C48B2C5754;
        Thu, 28 Nov 2019 11:09:46 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.439.0; Thu, 28 Nov 2019
 11:09:39 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: arm64: get rid of var ret and out jump label in
 kvm_arch_vcpu_ioctl_set_guest_debug()
Date: Thu, 28 Nov 2019 11:09:42 +0800
Message-ID: <1574910582-14405-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The var ret and out jump label is not really needed. Clean them
up.
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arch/arm64/kvm/guest.c | 11 +++--------
 1 file changed, 3 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: nVMX: Use SET_MSR_OR_WARN() to simplify failure loggingFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11265659
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38131139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:46:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 12EC221741
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:46:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="jV7G0pZk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726881AbfK1Jq2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 04:46:28 -0500
Received: from mail-pf1-f201.google.com ([209.85.210.201]:52556 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726227AbfK1Jq1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 04:46:27 -0500
Received: by mail-pf1-f201.google.com with SMTP id f20so15853427pfn.19
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 01:46:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=pMpbhX7gfy9Upeye3hmpdgvCu57jS/7Jbp2nWuR8Ix8=;
        b=jV7G0pZkgX0Gq1u7LGJWyTrdDYkCRHdGD1P7Yx3+CrvVP+25wPkq8WGG6yKoJzWP0P
         HpV4Rfa60SZnRjWSqNtLPNGkt+INQdkuy7iWFoCAAlX275UkmfT4aDHsgvK2iG+7iNfK
         PY60hr23kuyHLF4qxY0dyLAyKSqNG/rnr0/lGckREldFuoITCpm6YH100TOaDNKoPxgq
         xxYtxR6EO1EtxTHpGrU4upSfNfV05akLcgz/+WzOezZw39SHSHi5GLlb89ik/L+PHz7u
         vh1A5cviZVPk8bwfP8RzB6x8P1JZivupj3WIZcWYbVB2PQ1nq+s9FqrfRlmaNj3e2QCN
         TiWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=pMpbhX7gfy9Upeye3hmpdgvCu57jS/7Jbp2nWuR8Ix8=;
        b=dTk4a4wL/9lmC8JKdYjK9SDGkYwsrViil38rmiguJC/fK7xEKaDawjj7nBzMrIloDd
         eEuMYUi8dpsdBF2blwylHuM0A2L7yqwFjigs1SgN8EYZ3/qdzIWM4g06BV7Eei+aqEZL
         8nzWY++SC3NdxVRwAD0wyLCe1mt9N38fpbwzwSyCAuuVEPdurp42TD1ae3bw/dTpdIPo
         bWj44Bia4sXNBkTpeHCF19P3w6yCKnXCY7G1+LvFjTLhmlSM5G+YSuTdR7AUhACoYtE8
         SpIScd0NQltX8+gnoKn7ql3kqUEUfP1ej5jBF+nT+v4ldenWQ2z9tjd/ehfk23UcCkAf
         sQHw==
X-Gm-Message-State: APjAAAVxxRRrF9JmEYprP4pgFZsKPyJnIOoj9ikhj7s0lTunWbk2aofp
        p4ycmxuhDw4a+mmtKezFxz7sJShh0magzwkJHc6zV5nuILeF2jPzgekCgGf8/c/cgCncnugPlIx
        zGH7DHK8q/ZDOrhzNnDwgAjEyLeCz6iZpB0mdyqpTSYqrfBRNAaVysqd++w==
X-Google-Smtp-Source: 
 APXvYqzctch60s0NfGoMaAPOgKUzLb/zCG+jArUq8L0tPz23ID9L/C6m5aI1U592QiXKB745Htz/GgWx8B8=
X-Received: by 2002:a63:4387:: with SMTP id
 q129mr10279326pga.428.1574934387052;
 Thu, 28 Nov 2019 01:46:27 -0800 (PST)
Date: Thu, 28 Nov 2019 01:46:09 -0800
Message-Id: <20191128094609.22161-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH] KVM: nVMX: Use SET_MSR_OR_WARN() to simplify failure logging
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 " =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>,
 Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 458151f65b4d ("KVM: nVMX: Use kvm_set_msr to load
IA32_PERF_GLOBAL_CTRL on VM-Exit") introduced the SET_MSR_OR_WARN()
macro to WARN when kvm_set_msr() fails. Replace other occurences of this
pattern with the macro to remove the need of printing on failure.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/vmx/nested.c | 12 ++----------
 1 file changed, 2 insertions(+), 10 deletions(-)

```
#### [PATCH kvm-unit-tests] arm/arm64: PL031: Fix check_rtc_irq
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11266311
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE99613B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:55:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CE547217BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:55:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="c3/How7g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727060AbfK1PzY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 10:55:24 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:29751 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726446AbfK1PzY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 10:55:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574956523;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=LNRtx2eKuvnZpDiZLFUivmjg1FNYd4r9ipgtCcuMY/A=;
        b=c3/How7g/CWIXLrM86SQ8UwCPoQPS+zhkPeblVZWjMeICUZ1ivJprI8MQbxNSOrwq69AN2
        scVBWcjRFTUX6cisoZ7qoqIzgsc19gNWMrzKTNKEabDVd62MKgjlFrbw1rEyE+uhdxiXe+
        0ctUyqx0sCFvJQmcOspgNDVs+DB/uio=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-104-iyWJQaPYPIOma8rkjdpifw-1; Thu, 28 Nov 2019 10:55:19 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06D86100A162;
        Thu, 28 Nov 2019 15:55:18 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C85925C1B0;
        Thu, 28 Nov 2019 15:55:16 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, Alexander Graf <graf@amazon.com>
Subject: [PATCH kvm-unit-tests] arm/arm64: PL031: Fix check_rtc_irq
Date: Thu, 28 Nov 2019 16:55:15 +0100
Message-Id: <20191128155515.19013-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: iyWJQaPYPIOma8rkjdpifw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since QEMU commit 83ad95957c7e ("pl031: Expose RTCICR as proper WC
register") the PL031 test gets into an infinite loop. Now we must
write bit zero of RTCICR to clear the IRQ status. Before, writing
anything to RTCICR would work. As '1' is a member of 'anything'
writing it should work for old QEMU as well.

Cc: Alexander Graf <graf@amazon.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arm/pl031.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] arm: Enable the VFP
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11266093
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A10917F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 14:34:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1A8762071F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 14:34:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="T4nxUxGd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726696AbfK1Oe3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 09:34:29 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:49225 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726401AbfK1Oe3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 09:34:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574951668;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=3ypLLmy7uIRdZ2ESXpMXZa2LOjKZgb/771ocPNYrRmk=;
        b=T4nxUxGdmeZqEKr/WBy1u5BaCqRhkYj4fpI+LRHKaWYwEJLNvRUXlPA+1PC6CfFNAu6Rgb
        aOP+7rlGjflGsFbRx+4w6mGWOxtNjW7xwfixGt0LvXFfCdUW1uN556j10yXS2hrGtC2Qvp
        PIahxO6N6oyOOXqUaXedp1vp104lQb8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-136-rEEgGoYSMsaDEemHK1Gl6w-1; Thu, 28 Nov 2019 09:34:25 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5EFFC1800D52;
        Thu, 28 Nov 2019 14:34:24 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2991E5C1B0;
        Thu, 28 Nov 2019 14:34:23 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: thuth@redhat.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] arm: Enable the VFP
Date: Thu, 28 Nov 2019 15:34:21 +0100
Message-Id: <20191128143421.13815-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: rEEgGoYSMsaDEemHK1Gl6w-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Variable argument macros frequently depend on floating point
registers. Indeed we needed to enable the VFP for arm64 since its
introduction in order to use printf and the like. Somehow we
didn't need to do that for arm32 until recently when compiling
with GCC 9.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Tested-by: Thomas Huth <thuth@redhat.com>
---

CC'ing Thomas because I think he had to workaround travis tests
failing due to this issue once. Maybe travis can now be
un-worked-around?


 arm/cstart.S | 14 +++++++++++++-
 1 file changed, 13 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v2] arm: Enable the VFP
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11266233
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 772F613B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:09:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 56C0621771
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:09:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aEfMbS37"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726520AbfK1PJx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 10:09:53 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:39712 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726401AbfK1PJx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 10:09:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574953791;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=zfCwKwf1qQnxszU4MATj1+UFG4UOmnvAEgBHepQ9IM4=;
        b=aEfMbS37+RME8R4Xp9eOuxHCbGAjAyhzN3q4HbnjJY3cJKDB8nnFn2Q+6uHj4m8j5eXIdt
        ElleCcorSnpVCEZG4BJKPVSEJHIB3cohOwLl9+nkW4nb1IupwpX8UHykbzA+P1hj+9dibG
        d+l/NUAyU3tKwSIQAyMoQV9VNlr7v/0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-99-fm-CBMAuPZekwbgiC5X58A-1; Thu, 28 Nov 2019 10:09:48 -0500
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A57EC10054E3;
        Thu, 28 Nov 2019 15:09:47 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 754A4608AC;
        Thu, 28 Nov 2019 15:09:46 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: thuth@redhat.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2] arm: Enable the VFP
Date: Thu, 28 Nov 2019 16:09:45 +0100
Message-Id: <20191128150945.3851-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-MC-Unique: fm-CBMAuPZekwbgiC5X58A-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Variable argument macros frequently depend on floating point
registers. Indeed we needed to enable the VFP for arm64 since its
introduction in order to use printf and the like. Somehow we
didn't need to do that for arm32 until recently when compiling
with GCC 9.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---

v2: Added '-mfpu=vfp' cflag to deal with older compilers

CC'ing Thomas because I think he had to workaround travis tests
failing due to this issue once. Maybe travis can now be
un-worked-around?


 arm/Makefile.arm |  2 +-
 arm/cstart.S     | 14 +++++++++++++-
 2 files changed, 14 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests v3] arm: Enable the VFP
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11266305
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 642DB17F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:44:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 43D752178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 15:44:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ONHGFhVC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726558AbfK1Pn7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 10:43:59 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:51023 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726401AbfK1Pn7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 10:43:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574955837;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=vz34xy23I34V6t61KJptUN9zqdocHEiTDJU+6y5GpJM=;
        b=ONHGFhVCx4xF9AeqmfSViXdv3hl5ot8kKhXJ/0FUEhd7+LPqR+jm7g+wlwB2ptGYyEsYqR
        jt6ro5nCrOFINHu3z1rIqFX4+5tbK1xjm5bTu9thbujfdfiiS3fLqBOIqLJZfRefqWOCU2
        ZIV4MdOgXZb1jBIrNIiVfQHj5idHIFI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-258-gZADEEkKO2aoopNos3i5XQ-1; Thu, 28 Nov 2019 10:43:54 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4997C107B7E8;
        Thu, 28 Nov 2019 15:43:53 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1B18E600CD;
        Thu, 28 Nov 2019 15:43:51 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: thuth@redhat.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v3] arm: Enable the VFP
Date: Thu, 28 Nov 2019 16:43:50 +0100
Message-Id: <20191128154350.9650-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: gZADEEkKO2aoopNos3i5XQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Variable argument macros frequently depend on floating point
registers. Indeed we needed to enable the VFP for arm64 since its
introduction in order to use printf and the like. Somehow we
didn't need to do that for arm32 until recently when compiling
with GCC 9.

Tested-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---

v3: Added Thomas' t-b and suggested .gitlab-ci.yml change.
v2: Added '-mfpu=vfp' cflag to deal with older compilers

 .gitlab-ci.yml   |  2 +-
 arm/Makefile.arm |  2 +-
 arm/cstart.S     | 14 +++++++++++++-
 3 files changed, 15 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: VMX: Check EPT AD bits when enabled in ept_access_paddr()
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11265667
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15649921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:54:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E71E421774
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:54:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qS997Ioy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726716AbfK1Jy3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 04:54:29 -0500
Received: from mail-pf1-f202.google.com ([209.85.210.202]:39203 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726448AbfK1Jy2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 04:54:28 -0500
Received: by mail-pf1-f202.google.com with SMTP id z2so15871321pfg.6
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 01:54:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=73thCkBPX2FDaxemBtAwlsmt1YdFFahmNunbm6OlhXA=;
        b=qS997IoyaKyuX8vAeEwryNr0YQfCT2kQsW6fDAbJSRDys/1RJ4FSh7/GuPkbWh2r5+
         CH9giMeuYCNfTHVFsA0shUhiNtlLoIb87rX6CEJrU++U5jKFFQnIR8u+8QAVXHeeCYtH
         ulxQB7BXNJsUfEsnA1xOriRJNMaroM5sXsUQPi4n8OMWD+AVLHbG9/rm0gAg0V5PD+7M
         DztF0T+YOhiYwiEdAwDky9hBYxIezR/t6mq7REndeljx7WnomwEAdORBhog/yVmPErgD
         oQLhpfIafi7ix+UNmjJcUWfZDRe3pAYxfINv8JCmnVLaIIcQROfM/CPctR2v8myf1E8Y
         Ho1w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=73thCkBPX2FDaxemBtAwlsmt1YdFFahmNunbm6OlhXA=;
        b=QHVfnjtFO4Amxnyli+tiaTquT2DwQCFLdNM0oZY7lSfVEgAslGwcvJ7VlvU0whUAWP
         ym9ABwy+uMI9vckEJ8W103aeEZPiR5oRSAJ17qQgb2PDo1VKhYHJkqCCULMkuHhUeYnV
         tYIB6d7rLXMHyPbJCoQsLR7EJKUKhXHFCsJb3bjqXetgRZcpa+Pq2tZwBmfX5ULq3qYm
         cQsETwr9wHGtUYCQmoSR3Oe9jj+WwM5lhrH/c0XMsee2e0fDa5kzlTLOx10uSs3Kj4Wu
         ClcbVywJy62eQzYYycsVqlLxF3AW3BVgGDZe7V1HQLo3EgtV/rD5PsIpPsLJ6ClppiRQ
         ZbMQ==
X-Gm-Message-State: APjAAAW907Zzr61/ztBcyNdF8yHkEB/+sZrTz5NUF9ObHmCr62JplK1b
        tg+WiUeANe9QWhHiCRyhy4TuIRw/1JbfvJ9QY3r6AJusPphhT/+9eIPhby9JK9kvrVBabvM2fWu
        ZXB6nDWn0L0ejP/zc/wv0u7I7MMKLV+ekBN9PcHpZ3YlAqtKT8S6N58PXpQ==
X-Google-Smtp-Source: 
 APXvYqwxYbkRGasT2EvGWOZ4/ON7b3DquXQZsXKljp3ze2dB3SXF3hn3mg272YlBsCB4oa67PN9s29cpOOM=
X-Received: by 2002:a63:1a22:: with SMTP id a34mr9728712pga.403.1574934866510;
 Thu, 28 Nov 2019 01:54:26 -0800 (PST)
Date: Thu, 28 Nov 2019 01:54:22 -0800
Message-Id: <20191128095422.26757-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [kvm-unit-tests PATCH] x86: VMX: Check EPT AD bits when enabled in
 ept_access_paddr()
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 " =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>,
 Peter Shier <pshier@google.com>, Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Modify the test helper, ept_access_paddr(), to test the correctness
of the L1's EPT AD bits when enabled. After a successful guest access,
assert that the accessed bit (bit 8) has been set on all EPT entries
which were used in the translation of the guest-physical address.

Since ept_access_paddr() tests an EPT mapping that backs a guest paging
structure, processor accesses are treated as writes and the dirty bit
(bit 9) is set accordingly. Assert that the dirty bit is set on the leaf
EPT entry.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 x86/vmx_tests.c | 18 ++++++++++++++++++
 1 file changed, 18 insertions(+)

```
#### [PATCH] KVM: vgic: Fix potential double free dist->spis in __kvm_vgic_destroy()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11265427
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D632015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 06:38:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BEC24215F2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 06:38:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726670AbfK1Gi4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 01:38:56 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:7173 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726301AbfK1Gi4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 01:38:56 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 697B7D7E59EC32DF0DB2;
        Thu, 28 Nov 2019 14:38:53 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Thu, 28 Nov 2019
 14:38:45 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: vgic: Fix potential double free dist->spis in
 __kvm_vgic_destroy()
Date: Thu, 28 Nov 2019 14:38:48 +0800
Message-ID: <1574923128-19956-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

In kvm_vgic_dist_init() called from kvm_vgic_map_resources(), if
dist->vgic_model is invalid, dist->spis will be freed without set
dist->spis = NULL. And in vgicv2 resources clean up path,
__kvm_vgic_destroy() will be called to free allocated resources.
And dist->spis will be freed again in clean up chain because we
forget to set dist->spis = NULL in kvm_vgic_dist_init() failed
path. So double free would happen.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 virt/kvm/arm/vgic/vgic-init.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: vgic: Use warpper function to lock/unlock all vcpus in kvm_vgic_create()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11265357
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BCB33138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:09:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9CF492168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 03:09:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727299AbfK1DJV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 22:09:21 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:52262 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727088AbfK1DJV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 22:09:21 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id CCF043E07834170A7368;
        Thu, 28 Nov 2019 11:09:18 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Thu, 28 Nov 2019
 11:09:08 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: vgic: Use warpper function to lock/unlock all vcpus in
 kvm_vgic_create()
Date: Thu, 28 Nov 2019 11:09:11 +0800
Message-ID: <1574910551-14351-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Use warpper function lock_all_vcpus()/unlock_all_vcpus()
in kvm_vgic_create() to remove duplicated code dealing
with locking and unlocking all vcpus in a vm.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 virt/kvm/arm/vgic/vgic-init.c | 14 ++++----------
 1 file changed, 4 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: X86: Use APIC_DEST_* macros properly
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11266531
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DB788109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 19:32:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A965921787
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 19:32:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hLcSWRs/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726609AbfK1TcS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 14:32:18 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:47044 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726545AbfK1TcS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 14:32:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574969536;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=XMgsSwZQeQUSGV+wli5DvraayuJweYcClot3naZXyqM=;
        b=hLcSWRs/n1CdxLodM7SxyCgkHCxx1D5x0WHnUgzavxQkp+GGWu1LnUHYInTLd+0j5OjCA0
        iM24ABE73V/DSa6E8nVzYKgu70dk33tRKzS6dONCNr/xL74n4IaYZ4sQubBWvePC+CE6HV
        gFH61NBJofk3hl06UNxHZImPdaeZz+4=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-202-TJJdfkETMuCvt7jnbv7ZNQ-1; Thu, 28 Nov 2019 14:32:14 -0500
Received: by mail-qt1-f197.google.com with SMTP id l25so745708qtu.0
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 11:32:14 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=UsdxgTYnGq5qlzCPxK2R/zyMAt8PsfASdePTB4mVfio=;
        b=uXeLn40O4I0EyfZiaGzkoScUSX5hN5BwZsukPFUnvoDfMczEDOMmMK3Pc0dJkeTIxw
         LJW+iWpKWc3rz/JpenJrgWUGuDkmIIcbRAchgoLa0GxZVO3HpHEPTwQ4KeecCj+AGF/f
         Xz2mg6Pk0Xp5q1VzMKbMDEpN3CNhY+u4RGreBgcgLVUgrIJDDJavGrmrrR/pAElqGqt3
         VxuXezhFMvqhpaJIEhoY950txoVE5dnQRqu5VTCLdU+0HRXrFFg7P/PKG/a87CEA/dQs
         FJIKxZVPoasrCS6T6f4S2fBllJSV1BZCHnXjGD1xjKEC90xnywfJ7g1n+z+7JbJhL2us
         gArw==
X-Gm-Message-State: APjAAAUIem6H7oLGEfOUJAb9AQS13NFXOwsns6fVQtdnTzAQBk816CNs
        4AZAZuvF7RIxX0MjYcjAf6IyH04NIgOK4LgWhjcAjhhP+K4UVVGMJ8oYD7blNt6+2vChDwFfvUe
        xz2nre3tjZKae
X-Received: by 2002:a37:5942:: with SMTP id
 n63mr11663947qkb.432.1574969534100;
        Thu, 28 Nov 2019 11:32:14 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqx2kY7sAyhyavXxVXch1pzKTwKJrrOIiaxnEiIEDCsPRfNWlBYZUpXZzMOMBRn088FhlV7mjA==
X-Received: by 2002:a37:5942:: with SMTP id
 n63mr11663920qkb.432.1574969533797;
        Thu, 28 Nov 2019 11:32:13 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 x6sm2273178qke.127.2019.11.28.11.32.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 28 Nov 2019 11:32:12 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Nitesh Narayan Lal <nitesh@redhat.com>
Subject: [PATCH] KVM: X86: Use APIC_DEST_* macros properly
Date: Thu, 28 Nov 2019 14:32:11 -0500
Message-Id: <20191128193211.32684-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-MC-Unique: TJJdfkETMuCvt7jnbv7ZNQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously we were using either APIC_DEST_PHYSICAL|APIC_DEST_LOGICAL
or 0|1 to fill in kvm_lapic_irq.dest_mode, and it's done in an adhoc
way.  It's fine imho only because in most cases when we check against
dest_mode it's against APIC_DEST_PHYSICAL (which equals to 0).
However, that's not consistent, majorly because APIC_DEST_LOGICAL does
not equals to 1, so if one day we check irq.dest_mode against
APIC_DEST_LOGICAL we'll probably always get a false returned.

This patch replaces the 0/1 settings of irq.dest_mode with the macros
to make them consistent.

CC: Paolo Bonzini <pbonzini@redhat.com>
CC: Sean Christopherson <sean.j.christopherson@intel.com>
CC: Vitaly Kuznetsov <vkuznets@redhat.com>
CC: Nitesh Narayan Lal <nitesh@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/ioapic.c   | 9 ++++++---
 arch/x86/kvm/irq_comm.c | 7 ++++---
 arch/x86/kvm/x86.c      | 2 +-
 3 files changed, 11 insertions(+), 7 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11265917
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4278A112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 12:46:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2BB11215A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 12:46:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726569AbfK1MqR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 07:46:17 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21438 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726281AbfK1MqQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 07:46:16 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xASCgwNl058759
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 07:46:15 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2whcxs2jfc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 07:46:15 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Thu, 28 Nov 2019 12:46:13 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 28 Nov 2019 12:46:11 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xASCkAqr43188466
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 28 Nov 2019 12:46:10 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0BAD5AE045;
        Thu, 28 Nov 2019 12:46:10 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A51ACAE055;
        Thu, 28 Nov 2019 12:46:09 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.185.119])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 28 Nov 2019 12:46:09 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/9] s390x: saving regs for interrupts
Date: Thu, 28 Nov 2019 13:45:59 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1574945167-29677-1-git-send-email-pmorel@linux.ibm.com>
References: <1574945167-29677-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19112812-0012-0000-0000-0000036D6301
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19112812-0013-0000-0000-000021A90FEB
Message-Id: <1574945167-29677-2-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-28_03:2019-11-28,2019-11-28 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 mlxlogscore=643 lowpriorityscore=0 priorityscore=1501 impostorscore=0
 mlxscore=0 malwarescore=0 adultscore=0 phishscore=0 suspectscore=1
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911280112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for exemple, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers and the floating point registers on the stack.

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 25 +++++++++++++++++++++++--
 1 file changed, 23 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/8] iommu/vt-d: Add per domain page table ops
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11265279
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD80313A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 02:30:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C811021739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 02:30:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728014AbfK1CaA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 21:30:00 -0500
Received: from mga18.intel.com ([134.134.136.126]:17935 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726695AbfK1C37 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 21:29:59 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 18:29:59 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,251,1571727600";
   d="scan'208";a="221176111"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by orsmga002.jf.intel.com with ESMTP; 27 Nov 2019 18:29:57 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v2 1/8] iommu/vt-d: Add per domain page table ops
Date: Thu, 28 Nov 2019 10:25:43 +0800
Message-Id: <20191128022550.9832-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191128022550.9832-1-baolu.lu@linux.intel.com>
References: <20191128022550.9832-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Intel VT-d in scalable mode supports two types of
page talbes for DMA translation: the first level page
table and the second level page table. The IOMMU driver
is able to choose one of them for DMA remapping according
to the use case. The first level page table uses the same
format as the CPU page table, while the second level page
table keeps compatible with previous formats.

This abstracts the page tables used in Intel IOMMU driver
by defining a per domain page table ops structure which
contains callbacks for various page table operations.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 include/linux/intel-iommu.h | 24 ++++++++++++++++++++++++
 1 file changed, 24 insertions(+)

```
#### [PATCH v2] KVM: vgic: Use wrapper function to lock/unlock all vcpus in kvm_vgic_create()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11265649
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 617AF112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:27:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49879216F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 09:27:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726926AbfK1J06 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 04:26:58 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6727 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726252AbfK1J05 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 04:26:57 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 1F597E295C216E7C7B78;
        Thu, 28 Nov 2019 17:26:56 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.439.0; Thu, 28 Nov 2019
 17:26:45 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v2] KVM: vgic: Use wrapper function to lock/unlock all vcpus
 in kvm_vgic_create()
Date: Thu, 28 Nov 2019 17:26:48 +0800
Message-ID: <1574933208-24911-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Use wrapper function lock_all_vcpus()/unlock_all_vcpus()
in kvm_vgic_create() to remove duplicated code dealing
with locking and unlocking all vcpus in a vm.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Steven Price <steven.price@arm.com>
---
-v2:
	Fix some spelling mistake in patch title and commit log.
---
 virt/kvm/arm/vgic/vgic-init.c | 14 ++++----------
 1 file changed, 4 insertions(+), 10 deletions(-)

```
#### [RFC PATCH 1/3] vsock: add network namespace support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11266427
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F064C921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 17:15:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BE18F217AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 17:15:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WoZ35YLm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727005AbfK1RPh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 12:15:37 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23778 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726937AbfK1RPg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 12:15:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574961334;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=EJ8wmKVAVGzwQy9RJeA/HRES3+N97aoUgTm4JmySAyU=;
        b=WoZ35YLmpIA4mLtYJWzHwdpbUazCzX7k9wt8k+F7+0OucWXABbt+wb6PJJuvqHvzQTbvUl
        kHwe3ugfUK7zk/I5Z2Rgs7reiXmOSVHHDp9LLWg08tYEtlkID1LywYMsnhmgHxUu4taSLc
        bmiScLYcPl+Q9QDSrF4uGORWBjSMnhw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-2--QKnLjt9PjOK2AeJ3ke5Mw-1; Thu, 28 Nov 2019 12:15:32 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2B7C3107ACC4;
        Thu, 28 Nov 2019 17:15:31 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-168.ams2.redhat.com
 [10.36.117.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9CB89600C8;
        Thu, 28 Nov 2019 17:15:28 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Dexuan Cui <decui@microsoft.com>,
        Jason Wang <jasowang@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jorgen Hansen <jhansen@vmware.com>
Subject: [RFC PATCH 1/3] vsock: add network namespace support
Date: Thu, 28 Nov 2019 18:15:17 +0100
Message-Id: <20191128171519.203979-2-sgarzare@redhat.com>
In-Reply-To: <20191128171519.203979-1-sgarzare@redhat.com>
References: <20191128171519.203979-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: -QKnLjt9PjOK2AeJ3ke5Mw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds a check of the "net" assigned to a socket during
the vsock_find_bound_socket() and vsock_find_connected_socket()
to support network namespace, allowing to share the same address
(cid, port) across different network namespaces.

G2H transports will use the default network namepsace (init_net).
H2G transports can use different network namespace for different
VMs.

This patch uses default network namepsace (init_net) in all
transports.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 include/net/af_vsock.h                  |  6 +++--
 net/vmw_vsock/af_vsock.c                | 31 ++++++++++++++++++-------
 net/vmw_vsock/hyperv_transport.c        |  5 ++--
 net/vmw_vsock/virtio_transport_common.c |  5 ++--
 net/vmw_vsock/vmci_transport.c          |  5 ++--
 5 files changed, 35 insertions(+), 17 deletions(-)

```
#### [PATCH v4 01/19] x86/msr-index: Clean up bit defines for IA32_FEATURE_CONTROL MSR
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11265233
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E0A91921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 01:42:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CB0AE2166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 01:42:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727279AbfK1BkU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 20:40:20 -0500
Received: from mga02.intel.com ([134.134.136.20]:10954 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727088AbfK1BkU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 20:40:20 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 17:40:19 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,251,1571727600";
   d="scan'208";a="221166465"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga002.jf.intel.com with ESMTP; 27 Nov 2019 17:40:18 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Mark Rutland <mark.rutland@arm.com>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Jiri Olsa <jolsa@redhat.com>, Namhyung Kim <namhyung@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>,
 Len Brown <lenb@kernel.org>, Shuah Khan <shuah@kernel.org>,
 linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
 linux-edac@vger.kernel.org, linux-pm@vger.kernel.org,
 linux-kselftest@vger.kernel.org, Borislav Petkov <bp@suse.de>,
 Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH v4 01/19] x86/msr-index: Clean up bit defines for
 IA32_FEATURE_CONTROL MSR
Date: Wed, 27 Nov 2019 17:39:58 -0800
Message-Id: <20191128014016.4389-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191128014016.4389-1-sean.j.christopherson@intel.com>
References: <20191128014016.4389-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As pointed out by Boris, the defines for bits in IA32_FEATURE_CONTROL
are quite a mouthful, especially the VMX bits which must differentiate
between enabling VMX inside and outside SMX (TXT) operation.  Rename the
MSR and its bit defines to abbreviate FEATURE_CONTROL as FEAT_CTL to
make them a little friendlier on the eyes.

Arguably the MSR itself should keep the full IA32_FEATURE_CONTROL name
to match Intel's SDM, but a future patch will add a dedicated Kconfig,
file and functions for the MSR.  Using the full name for those assets is
rather unwieldy, so bite the bullet and use IA32_FEAT_CTL so that its
nomenclature is consistent throughout the kernel.

Opportunistically fix a few other annoyances with the defines:

  - Relocate the bit defines so that they immediately follow the MSR
    define, e.g. aren't mistaken as belonging to MISC_FEATURE_CONTROL.
  - Add whitespace around the block of feature control defines to make
    it clear they're all related.
  - Use BIT() instead of manually encoding the bit shift.
  - Use "VMX" instead of "VMXON" to match the SDM.
  - Append "_ENABLED" to the LMCE (Local Machine Check Exception) bit to
    be consistent with the kernel's verbiage used for all other feature
    control bits.  Note, the SDM refers to the LMCE bit as LMCE_ON,
    likely to differentiate it from IA32_MCG_EXT_CTL.LMCE_EN.  Ignore
    the (literal) one-off usage of _ON, the SDM is simply "wrong".

Cc: Borislav Petkov <bp@alien8.de>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reported-by: kbuild test robot <lkp@intel.com>
---
 arch/x86/include/asm/msr-index.h | 14 +++++-----
 arch/x86/kernel/cpu/mce/intel.c  | 10 +++----
 arch/x86/kvm/vmx/nested.c        |  4 +--
 arch/x86/kvm/vmx/vmx.c           | 46 ++++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h           |  2 +-
 arch/x86/kvm/x86.c               |  2 +-
 6 files changed, 40 insertions(+), 38 deletions(-)

```
