#### [PATCH v4 1/1] KVM: s390: diag9c (directed yield) forwarding
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12098543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3420FC433DB
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 13:04:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D2B8864E4B
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 13:04:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231163AbhBVNDt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 08:03:49 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:57174 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231710AbhBVNCd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 08:02:33 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11MCu72w036763;
        Mon, 22 Feb 2021 08:01:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=/dx7gXr7W6eqWre/v+YmsB4pd9UnY7Jmi/X7eOln7b8=;
 b=h55ljubKKdfYhNkt4mJwr34dLqSmkrnBJ9Dym5S509Lam0z4FCWsLm6qGt4bVJa1CmxA
 pWUQQQ7acoiNQTI2CWk8Ws2KkhfXXk/OhsK5NI0HYQ4VsVy2gKfOUEfMg6y73iOzJHer
 dd84fA4/pcnlm0uuifagNrzkGH2cY6vbRcbySFSGa8FxC3LJZKLza2OmRJ3P4jVu/c6M
 x7SSx+QfmhSL2VLhlVwC5q92E9hEQePD3vwRTBQ5F/66Dimp7sBjot5g9ey25Ws8tWIn
 yytEiJgDyhvJhaSQVwvrwUAZ9gTV8nmw3ybhifRDZ7wswTgbiUn+c4+FG+Vt30MZHv48 5g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vd2288wx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 08:01:50 -0500
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11MCvUqD060467;
        Mon, 22 Feb 2021 08:01:39 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36vd2287ps-17
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 08:01:39 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11MCS4Ae017061;
        Mon, 22 Feb 2021 12:41:06 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04ams.nl.ibm.com with ESMTP id 36tt289mjv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 12:41:06 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11MCep3i26607876
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Feb 2021 12:40:51 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D44E4AE04D;
        Mon, 22 Feb 2021 12:41:03 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6BC05AE045;
        Mon, 22 Feb 2021 12:41:03 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.71.218])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Feb 2021 12:41:03 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v4 1/1] KVM: s390: diag9c (directed yield) forwarding
Date: Mon, 22 Feb 2021 13:41:01 +0100
Message-Id: <1613997661-22525-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1613997661-22525-1-git-send-email-pmorel@linux.ibm.com>
References: <1613997661-22525-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-22_02:2021-02-22,2021-02-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 priorityscore=1501 mlxscore=0 suspectscore=0 clxscore=1015 phishscore=0
 impostorscore=0 mlxlogscore=999 adultscore=0 spamscore=0 bulkscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102220115
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we intercept a DIAG_9C from the guest we verify that the
target real CPU associated with the virtual CPU designated by
the guest is running and if not we forward the DIAG_9C to the
target real CPU.

To avoid a diag9c storm we allow a maximal rate of diag9c forwarding.

The rate is calculated as a count per second defined as a new
parameter of the s390 kvm module: diag9c_forwarding_hz .

The default value of 0 is to not forward diag9c.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 Documentation/virt/kvm/s390-diag.rst | 33 ++++++++++++++++++++++++++++
 arch/s390/include/asm/kvm_host.h     |  1 +
 arch/s390/include/asm/smp.h          |  1 +
 arch/s390/kernel/smp.c               |  1 +
 arch/s390/kvm/diag.c                 | 31 +++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c             |  6 +++++
 arch/s390/kvm/kvm-s390.h             |  8 +++++++
 7 files changed, 78 insertions(+), 3 deletions(-)

```
#### [PATCH v4 1/2] KVM: x86/mmu: Skip mmu_notifier check when handling MMIO page fault
##### From: David Stevens <stevensd@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12097861
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B2327C433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 02:47:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B70064EEC
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 02:47:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231848AbhBVCrE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 21 Feb 2021 21:47:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49984 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231825AbhBVCrA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 21 Feb 2021 21:47:00 -0500
Received: from mail-pl1-x631.google.com (mail-pl1-x631.google.com
 [IPv6:2607:f8b0:4864:20::631])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6797AC061793
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 18:45:48 -0800 (PST)
Received: by mail-pl1-x631.google.com with SMTP id k22so6838703pll.6
        for <kvm@vger.kernel.org>; Sun, 21 Feb 2021 18:45:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=YI7HyzDG3owLPU4UQfa7tiUEs9jP6yMxkdlolNtJ+LQ=;
        b=oFZXsVYacLQwXAQgBXWMVNd4tYXERP+aOxK5JtlWHh10GwD8sUEk2xy3lHQcfTdxNJ
         A6c9eWv3q8ddSG8D4h1LqOoseHnCbmYkxklZ6Xfy3SnqUUMRHonQ6E6OabJC+EI947OM
         +XuAC7e32rEtYRhECOHtBOFGA47fYnVe624N4=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=YI7HyzDG3owLPU4UQfa7tiUEs9jP6yMxkdlolNtJ+LQ=;
        b=nQFCG3iY+2gI59Gyl9dG2CvBFaqRQjy1NCLloTZQ8E1rC4HgGsWJVzzno7ZETDDSYn
         6h5TNL0VQpa3Ekp9zGtXoZDncyGOEtETGfzbj5qkTJbU/muhnKWCUsniH0JVGTtb8TJ4
         2LpC+9966CJvZOrqXTDa1OPFiwcZozCYWSEbgT7b9LEGk6xzIHJ14zenVd7Tf8KHtAkN
         6e+BvHfNUD4m1nTAft36tV/zUfO9zC0XTauUnMuR7sccfTp56DnhmW4KlL22LSboBvU6
         ichJ9xUXOP/Y4mPPdl5aHxpjfzqZch12bA0fc2KFXDnTORSfLgA5wpXbj2x8IktC3NS4
         4rtA==
X-Gm-Message-State: AOAM531k1HFEfj5peJzNEouU9G9zVygz12YCy0gi1HqxOzrFFnZ5AgNM
        14w+0EiXnnviuPEPPk9taSU1/g==
X-Google-Smtp-Source: 
 ABdhPJx0ONsyfWmAv6BuRaUkUpIoDCKbgVlmXVQvduvaRKvsylbKwcg3SupTc3g+xjmq0KI028TOMQ==
X-Received: by 2002:a17:90a:4882:: with SMTP id
 b2mr20682824pjh.78.1613961947967;
        Sun, 21 Feb 2021 18:45:47 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:11b3:5e1a:7cb:7e1f])
        by smtp.gmail.com with UTF8SMTPSA id
 y2sm15413682pjw.36.2021.02.21.18.45.43
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Sun, 21 Feb 2021 18:45:47 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [PATCH v4 1/2] KVM: x86/mmu: Skip mmu_notifier check when handling
 MMIO page fault
Date: Mon, 22 Feb 2021 11:45:21 +0900
Message-Id: <20210222024522.1751719-2-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
In-Reply-To: <20210222024522.1751719-1-stevensd@google.com>
References: <20210222024522.1751719-1-stevensd@google.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <seanjc@google.com>

Don't retry a page fault due to an mmu_notifier invalidation when
handling a page fault for a GPA that did not resolve to a memslot, i.e.
an MMIO page fault.  Invalidations from the mmu_notifier signal a change
in a host virtual address (HVA) mapping; without a memslot, there is no
HVA and thus no possibility that the invalidation is relevant to the
page fault being handled.

Note, the MMIO vs. memslot generation checks handle the case where a
pending memslot will create a memslot overlapping the faulting GPA.  The
mmu_notifier checks are orthogonal to memslot updates.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c         | 2 +-
 arch/x86/kvm/mmu/paging_tmpl.h | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/7] s390x: Fix fpc store address in RESTORE_REGS_STACK
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12098133
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DBED9C433E9
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:00:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90A6B64E61
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:00:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230099AbhBVJAE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 04:00:04 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:8764 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229934AbhBVJAA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 04:00:00 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 11M8whfB141485;
        Mon, 22 Feb 2021 03:59:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=vuRLhnrN0FZn6h/Va0uxgrip9AUObOGa8pIcB5cKFpY=;
 b=Uk4+MlTJ3sCIHdSGLsoMSKZsYFBAvHilEnzQ3jEuga8Lc4tL3fuOYLHwgtYVGIgT8SOW
 KICz+xVSkWbvlUtpa4SFJYAPyQ/OFM/NUeQkFvpUee3icFmOwzw2VfLzHnisf84HkBBp
 AbGNPKyb96QF19Hl5qCEvn+TPbFjOdibrHj3Ydh7N39JoIFiUucejQTbNUzCKTSTTbDE
 i6HhQh4rLADLb+rbhcuX5WwFkI3+sIJ8PU8977zCeNqWfyK4/OxC1NmjVfhFIZQbnETi
 h21EzVxIpj1K1RFqq+Ehw6GJTbEDG+ecXznBlkLvtn6zC5uvQW6W9JEAGVf5cmaLRUUP og==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36v9jt81eg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 03:59:18 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 11M8x2Pc143321;
        Mon, 22 Feb 2021 03:59:16 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36v9jt81c5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 03:59:16 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11M8wDdO029103;
        Mon, 22 Feb 2021 08:59:12 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 36tt281exx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 22 Feb 2021 08:59:12 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11M8wvMK14025056
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 22 Feb 2021 08:58:57 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 69559AE04D;
        Mon, 22 Feb 2021 08:59:09 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AA9ECAE053;
        Mon, 22 Feb 2021 08:59:08 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 22 Feb 2021 08:59:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        pmorel@linux.ibm.com, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/7] s390x: Fix fpc store address in
 RESTORE_REGS_STACK
Date: Mon, 22 Feb 2021 03:57:50 -0500
Message-Id: <20210222085756.14396-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210222085756.14396-1-frankja@linux.ibm.com>
References: <20210222085756.14396-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-22_02:2021-02-18,2021-02-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxlogscore=999
 impostorscore=0 lowpriorityscore=0 priorityscore=1501 bulkscore=0
 mlxscore=0 malwarescore=0 suspectscore=0 phishscore=0 clxscore=1015
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102220076
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The efpc stores in bits 32-63 of a register and we store a full 8
bytes to have the stack 8 byte aligned. This means that the fpc is
stored at offset 4 but we load it from offset 0. Lets replace efpc
with stfpc and get rid of the stg to store at offset 0.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/macros.S | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v6 1/2] drivers/misc: sysgenid: add system generation id driver
##### From: Adrian Catangiu <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12098211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DEEE0C4332B
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:44:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B48C464E44
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 09:44:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230135AbhBVJnl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 04:43:41 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:41129 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230053AbhBVJnI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Feb 2021 04:43:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1613986983; x=1645522983;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=GoFiHmkiRLqGpatl14iXFUQWsHeBd/6RoTe4MpnGs+M=;
  b=uIbCzHnfAnbgJUykkem4JnXQvFjGev2lboEQqYYySOI3/rd125dNMz01
   tqdiZEGwTq1RV6+Fcgtm9F4b+hyeX50yeqBLrWKyC2YutEUH3Bxv7lPRm
   00EGZCaP5l5k/EJFYtFqDedFJV0bz676i6N44VwcjoPCJHzSwx2+yMH5J
   o=;
X-IronPort-AV: E=Sophos;i="5.81,196,1610409600";
   d="scan'208";a="86462559"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2a-c5104f52.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 22 Feb 2021 09:42:12 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2a-c5104f52.us-west-2.amazon.com (Postfix) with
 ESMTPS id 006C2A1E92;
        Mon, 22 Feb 2021 09:42:09 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.87) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 22 Feb 2021 09:41:55 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, <acatan@amazon.com>
Subject: [PATCH v6 1/2] drivers/misc: sysgenid: add system generation id
 driver
Date: Mon, 22 Feb 2021 11:41:25 +0200
Message-ID: <1613986886-29493-2-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1613986886-29493-1-git-send-email-acatan@amazon.com>
References: <1613986886-29493-1-git-send-email-acatan@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.87]
X-ClientProxiedBy: EX13D41UWC004.ant.amazon.com (10.43.162.31) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background and problem

The System Generation ID feature is required in virtualized or
containerized environments by applications that work with local copies
or caches of world-unique data such as random values, uuids,
monotonically increasing counters, etc.
Such applications can be negatively affected by VM or container
snapshotting when the VM or container is either cloned or returned to
an earlier point in time.

Furthermore, simply finding out about a system generation change is
only the starting point of a process to renew internal states of
possibly multiple applications across the system. This process requires
a standard interface that applications can rely on and through which
orchestration can be easily done.

- Solution

The System Generation ID is meant to help in these scenarios by
providing a monotonically increasing u32 counter that changes each time
the VM or container is restored from a snapshot.

The `sysgenid` driver exposes a monotonic incremental System Generation
u32 counter via a char-dev filesystem interface accessible
through `/dev/sysgenid`. It provides synchronous and asynchronous SysGen
counter update notifications, as well as counter retrieval and
confirmation mechanisms.
The counter starts from zero when the driver is initialized and
monotonically increments every time the system generation changes.

Userspace applications or libraries can (a)synchronously consume the
system generation counter through the provided filesystem interface, to
make any necessary internal adjustments following a system generation
update.

The provided filesystem interface operations can be used to build a
system level safe workflow that guest software can follow to protect
itself from negative system snapshot effects.

The `sysgenid` driver exports the `void sysgenid_bump_generation()`
symbol which can be used by backend drivers to drive system generation
changes based on hardware events.
System generation changes can also be driven by userspace software
through a dedicated driver ioctl.

The driver also generates a `SYSGENID=%u` uevent containing the new
system generation counter/id value every time it changes. Unlike the
filesystem interface, the uevent has no synchronization guarantees
therefore it should not be used by any sensitive system components.

**Please note**, SysGenID alone does not guarantee complete snapshot
safety to applications using it. A certain workflow needs to be
followed at the system level, in order to make the system
snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
section in the included documentation.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
 Documentation/misc-devices/sysgenid.rst            | 234 ++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 MAINTAINERS                                        |   8 +
 drivers/misc/Kconfig                               |  15 +
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 338 +++++++++++++++++++++
 include/uapi/linux/sysgenid.h                      |  18 ++
 7 files changed, 615 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h

diff --git a/Documentation/misc-devices/sysgenid.rst b/Documentation/misc-devices/sysgenid.rst
new file mode 100644
index 0000000..4c24559
--- /dev/null
+++ b/Documentation/misc-devices/sysgenid.rst
@@ -0,0 +1,234 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+========
+SYSGENID
+========
+
+The System Generation ID feature is required in virtualized or
+containerized environments by applications that work with local copies
+or caches of world-unique data such as random values, UUIDs,
+monotonically increasing counters, etc.
+Such applications can be negatively affected by VM or container
+snapshotting when the VM or container is either cloned or returned to
+an earlier point in time.
+
+The System Generation ID is meant to help in these scenarios by
+providing a monotonically increasing counter that changes each time the
+VM or container is restored from a snapshot. The driver for it lives at
+``drivers/misc/sysgenid.c``.
+
+The ``sysgenid`` driver exposes a monotonic incremental System
+Generation u32 counter via a char-dev filesystem interface accessible
+through ``/dev/sysgenid`` that provides sync and async SysGen counter
+update notifications. It also provides SysGen counter retrieval and
+confirmation mechanisms.
+
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the system generation changes.
+
+The ``sysgenid`` driver exports the ``void sysgenid_bump_generation()``
+symbol which can be used by backend drivers to drive system generation
+changes based on hardware events.
+System generation changes can also be driven by userspace software
+through a dedicated driver ioctl.
+
+Userspace applications or libraries can (a)synchronously consume the
+system generation counter through the provided filesystem interface, to
+make any necessary internal adjustments following a system generation
+update.
+
+The driver also generates a ``SYSGENID=%u`` uevent containing the new
+system generation counter/id value every time it changes. Unlike the
+filesystem interface, the uevent has no synchronization guarantees
+therefore it should not be used by any sensitive system components.
+
+**Please note**, SysGenID alone does not guarantee complete snapshot
+safety to applications using it. A certain workflow needs to be
+followed at the system level, in order to make the system
+snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
+section below.
+
+Driver filesystem interface
+===========================
+
+``open()``:
+  When the device is opened, a copy of the current SysGenID (counter)
+  is associated with the open file descriptor. Every open file
+  descriptor will have readable data available (EPOLLIN) while its
+  current copy of the SysGenID is outdated. Reading from the fd will
+  provide the latest SysGenID, while writing to the fd will update the
+  fd-local copy of the SysGenID and is used as a confirmation
+  mechanism.
+
+``read()``:
+  Read is meant to provide the *new* system generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date, at which point the new
+  counter is provided/returned.  Nonblocking ``read()`` returns
+  ``EAGAIN`` to signal that there is no *new* counter value available.
+  The generation counter is considered *new* for each open file
+  descriptor that hasn't confirmed the new value following a generation
+  change. Therefore, once a generation change takes place, all
+  ``read()`` calls will immediately return the new generation counter
+  and will continue to do so until the new value is confirmed back to
+  the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  32 bits in size.
+
+``write()``:
+  Write is used to confirm the up-to-date SysGenID counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` containing the new up-to-date generation
+  counter is used as an update confirmation mechanism.
+  Partial writes are not allowed - write buffer should be exactly
+  32 bits in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for waiting on open file descriptors
+  that haven't acknowledged a generation counter update, as well as a
+  mechanism for userspace to *trigger* a generation update:
+
+  - SYSGENID_SET_WATCHER_TRACKING: takes a bool argument to set tracking
+    status for current file descriptor. When watcher tracking is
+    enabled, the driver tracks this file descriptor as an independent
+    *watcher*. The driver keeps accounting of how many watchers have
+    confirmed the latest Sys-Gen-Id counter and how many of them are
+    *outdated*; an outdated watcher is a *tracked* open file descriptor
+    that has lived through a Sys-Gen-Id change but has not yet confirmed
+    the new generation counter.
+    Software that wants to be waited on by the system while it adjusts
+    to generation changes, should turn tracking on. The sysgenid driver
+    then keeps track of it and can block system-level adjustment process
+    until the software has finished adjusting and confirmed it through a
+    ``write()``.
+    Tracking is disabled by default and file descriptors need to
+    explicitly opt-in using this IOCTL.
+  - SYSGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    tracked watchers or, if a ``timeout`` argument is provided, until
+    the timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - SYSGENID_TRIGGER_GEN_UPDATE: triggers a generation counter increment.
+    It takes a ``minimum-generation`` argument which represents the
+    minimum value the generation counter will be set to. For example if
+    current generation is ``5`` and ``SYSGENID_TRIGGER_GEN_UPDATE(8)``
+    is called, the generation counter will increment to ``8``.
+    This IOCTL can only be used by processes with CAP_CHECKPOINT_RESTORE
+    or CAP_SYS_ADMIN capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date u32 copy of the system generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections.
+  The mmap() interface is targeted at libraries or code that needs to
+  check for generation changes in-line, where an event loop is not
+  available or read()/write() syscalls are too expensive.
+  In such cases, logic can be added in-line with the sensitive code to
+  check and trigger on-demand/just-in-time readjustments when changes
+  are detected on the memory mapped generation counter.
+  Users of this interface that plan to lazily adjust should not enable
+  watcher tracking, since waiting on them doesn't make sense.
+
+``close()``:
+  Removes the file descriptor as a system generation counter *watcher*.
+
+Snapshot Safety Prerequisites
+=============================
+
+If VM, container or other system-level snapshots happen asynchronously,
+at arbitrary times during an active workload there is no practical way
+to ensure that in-flight local copies or caches of world-unique data
+such as random values, secrets, UUIDs, etc are properly scrubbed and
+regenerated.
+The challenge stems from the fact that the categorization of data as
+snapshot-sensitive is only known to the software working with it, and
+this software has no logical control over the moment in time when an
+external system snapshot occurs.
+
+Let's take an OpenSSL session token for example. Even if the library
+code is made 100% snapshot-safe, meaning the library guarantees that
+the session token is unique (any snapshot that happened during the
+library call did not duplicate or leak the token), the token is still
+vulnerable to snapshot events while it transits the various layers of
+the library caller, then the various layers of the OS before leaving
+the system.
+
+To catch a secret while it's in-flight, we'd have to validate system
+generation at every layer, every step of the way. Even if that would
+be deemed the right solution, it would be a long road and a whole
+universe to patch before we get there.
+
+Bottom line is we don't have a way to track all of these in-flight
+secrets and dynamically scrub them from existence with snapshot
+events happening arbitrarily.
+
+Simplifyng assumption - safety prerequisite
+-------------------------------------------
+
+**Control the snapshot flow**, disallow snapshots coming at arbitrary
+moments in the workload lifetime.
+
+Use a system-level overseer entity that quiesces the system before
+snapshot, and post-snapshot-resume oversees that software components
+have readjusted to new environment, to the new generation. Only after,
+will the overseer un-quiesce the system and allow active workloads.
+
+Software components can choose whether they want to be tracked and
+waited on by the overseer by using the ``SYSGENID_SET_WATCHER_TRACKING``
+IOCTL.
+
+The sysgenid framework standardizes the API for system software to
+find out about needing to readjust and at the same time provides a
+mechanism for the overseer entity to wait for everyone to be done, the
+system to have readjusted, so it can un-quiesce.
+
+Example snapshot-safe workflow
+------------------------------
+
+1) Before taking a snapshot, quiesce the VM/container/system. Exactly
+   how this is achieved is very workload-specific, but the general
+   description is to get all software to an expected state where their
+   event loops dry up and they are effectively quiesced.
+2) Take snapshot.
+3) Resume the VM/container/system from said snapshot.
+4) SysGenID counter will either automatically increment if there is
+   a vmgenid backend (hw-driven), or overseer will trigger generation
+   bump using ``SYSGENID_TRIGGER_GEN_UPDATE`` IOCLT (sw-driven).
+5) Software components which have ``/dev/sysgenid`` in their event
+   loops (either using ``poll()`` or ``read()``) are notified of the
+   generation change.
+   They do their specific internal adjustments. Some may have requested
+   to be tracked and waited on by the overseer, others might choose to
+   do their adjustments out of band and not block the overseer.
+   Tracked ones *must* signal when they are done/ready with a ``write()``
+   while the rest *should* also do so for cleanliness, but it's not
+   mandatory.
+6) Overseer will block and wait for all tracked watchers by using the
+   ``SYSGENID_WAIT_WATCHERS`` IOCTL. Once all tracked watchers are done
+   in step 5, this overseer will return from this blocking ioctl knowing
+   that the system has readjusted and is ready for active workload.
+7) Overseer un-quiesces system.
+8) There is a class of software, usually libraries, most notably PRNGs
+   or SSLs, that don't fit the event-loop model and also have strict
+   latency requirements. These can take advantage of the ``mmap()``
+   interface and lazily adjust on-demand whenever they are called after
+   un-quiesce.
+   For a well-designed service stack, these libraries should not be
+   called while system is quiesced. When workload is resumed by the
+   overseer, on the first call into these libs, they will safely JIT
+   readjust.
+   Users of this lazy on-demand readjustment model should not enable
+   watcher tracking since doing so would introduce a logical deadlock:
+   lazy adjustments happen only after un-quiesce, but un-quiesce is
+   blocked until all tracked watchers are up-to-date.
```
#### [PATCH v2] use pr_warn_ratelimited() for vq_err()
##### From: John Levon <john.levon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Levon <john.levon@nutanix.com>
X-Patchwork-Id: 12098429
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61611C433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 12:05:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1B30364E24
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 12:05:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230141AbhBVMFF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 07:05:05 -0500
Received: from 88-98-93-30.dsl.in-addr.zen.co.uk ([88.98.93.30]:44242 "EHLO
        sent" rhost-flags-OK-FAIL-OK-FAIL) by vger.kernel.org with ESMTP
        id S230101AbhBVMEz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Feb 2021 07:04:55 -0500
X-Greylist: delayed 2046 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 22 Feb 2021 07:04:55 EST
Received: from jlevon by sent with local (Exim 4.93)
        (envelope-from <john.levon@nutanix.com>)
        id 1lE9PZ-00FW15-Uu; Mon, 22 Feb 2021 11:29:57 +0000
From: John Levon <john.levon@nutanix.com>
To: john.levon@nutanix.com
Cc: jasowang@redhat.com, kvm@vger.kernel.org, levon@movementarian.org,
        mst@redhat.com, virtualization@lists.linux-foundation.org
Subject: [PATCH v2] use pr_warn_ratelimited() for vq_err()
Date: Mon, 22 Feb 2021 11:29:47 +0000
Message-Id: <20210222112947.3697927-1-john.levon@nutanix.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210115173741.2628737-1-john.levon@nutanix.com>
References: <20210115173741.2628737-1-john.levon@nutanix.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vq_err() is used to report various failure states in vhost code, but by
default uses pr_debug(), and as a result doesn't record anything unless
enabled via dynamic debug. We'll change this so we get something recorded
in the log in these failure cases. Guest VMs (and userspace) can trigger
some of these messages, so we want to use the pr_warn_ratelimited()
variant. However, on DEBUG kernels, we'd like to get everything, so we use
pr_warn() then.

Signed-off-by: John Levon <john.levon@nutanix.com>
---
v2: use pr_warn() for DEBUG kernels
---
 drivers/vhost/vhost.h | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
#### [RFC PATCH 01/10] vfio: Create vfio_fs_type with inode per deviceFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12099173
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12E4EC433E0
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 16:52:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CBD4764F04
	for <kvm@archiver.kernel.org>; Mon, 22 Feb 2021 16:52:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231312AbhBVQw0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Feb 2021 11:52:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43337 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231261AbhBVQwO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 22 Feb 2021 11:52:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614012646;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QBaujFxExGLh2CQgduXZKM8P6MRyUxKv108wObRTJvA=;
        b=CJ5By3aAylgMLnmKRDXakaljJ8yE2BtD9PNl+UMdN+KhB77Xw9J6q50RySo1KKBat1vPbr
        Sb0aOlcAFhGFt1Mm2GpOlE5+7HL2QqiCGOo9JfhrPZjQY1deFJzvPHf60HqK0BW/ins1FL
        c+Wrouf3GVyeAXdpxuKbZZhStRSELJA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-366-40sXcic-NSuS7zqAYZdLNg-1; Mon, 22 Feb 2021 11:50:43 -0500
X-MC-Unique: 40sXcic-NSuS7zqAYZdLNg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 45AE9CC620;
        Mon, 22 Feb 2021 16:50:42 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 877C25C1BD;
        Mon, 22 Feb 2021 16:50:35 +0000 (UTC)
Subject: [RFC PATCH 01/10] vfio: Create vfio_fs_type with inode per device
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Mon, 22 Feb 2021 09:50:35 -0700
Message-ID: <161401263517.16443.7534035240372538844.stgit@gimli.home>
In-Reply-To: <161401167013.16443.8389863523766611711.stgit@gimli.home>
References: <161401167013.16443.8389863523766611711.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By linking all the device fds we provide to userspace to an
address space through a new pseudo fs, we can use tools like
unmap_mapping_range() to zap all vmas associated with a device.

Suggested-by: Jason Gunthorpe <jgg@nvidia.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c |   54 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 54 insertions(+)

```
