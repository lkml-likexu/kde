#### [PATCH 1/1] Fix potential bitmap corruption in ksm_msr_allowed()
##### From: Yuan Yao <yaoyuan0329os@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuan Yao <yaoyuan0329os@gmail.com>
X-Patchwork-Id: 12133941
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,HK_RANDOM_FROM,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 372D4C433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 08:32:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E780564FB3
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 08:32:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232274AbhCLIcC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 03:32:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38122 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231764AbhCLIcC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 03:32:02 -0500
Received: from mail-pj1-x1031.google.com (mail-pj1-x1031.google.com
 [IPv6:2607:f8b0:4864:20::1031])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D9250C061574
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 00:32:01 -0800 (PST)
Received: by mail-pj1-x1031.google.com with SMTP id
 mz6-20020a17090b3786b02900c16cb41d63so10730362pjb.2
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 00:32:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CXpW0jwlizj8GYTWHzwU8bAHHZKAdwaecc1NswSz/OE=;
        b=Ccj25YDTPKU/57oEL/GyBbzdoG3Cad1MC5quVjSh1ZoLeLYp/oRlBjJJWGKN2QAFlP
         8299qZp3bQJMvvbvg1UTV+zydy/b2Hzgexu50JBiylyqKEq46bc3pxUCPDFH3O36/LFX
         kJ+br9H0Eb+q7AWaSuzrLYEOlgZTmA5nHPPYPoRt2LjDcOCsvEhsiwDSpQOONFpBj6Go
         lJyzEU4SzgXRLk2vkkV6B0KiscdvSAgwj+n3cN2FQBeBE4YQHa/XEJpZ1m7pXyy5owU2
         fc+DgjWfaINp1NjLkCk0FcGg5htcxCPhikvIYN9Plw+biynveEp+496yv3vFkoYHUetv
         h+kA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CXpW0jwlizj8GYTWHzwU8bAHHZKAdwaecc1NswSz/OE=;
        b=nQQMPoO+mKl8QDA2Rp+sTebfGaDdU/aUsZ2n7IqL6PYITbDRlaff+fNwiROoZ9wJYs
         Njza0wHrzo39bIZ0VV4eNKc5dbQf6NZkZ34xH45+JSBhRIoEC3KNpOvbg/aLQshBRx5m
         24jp6zyMgjQd1kaiQSKll4wRl5Ef5aXFqWcR+GF/G7QocgKNrNHS0q+nXeDd6Gk257Qd
         eQ6rQHq1FKzc41G+D0D5mhcC3e4pDi3yJ9QNQGn0QBeAluUSRPYpUmRKhTUwA0442PQV
         jd2ISV5gBHzs6eNGt28MHPY15iF41l5dsskgNkyFhRtuv7W7PtRfGt/lHkfiClFpZ/W+
         Txdg==
X-Gm-Message-State: AOAM531mTeWJpx3S7ciDe3xPEKbWrVwvpLK/YFTOzbyTXIzRi5q0/iMZ
        PpE5opFOSSLekm75biyMxuI=
X-Google-Smtp-Source: 
 ABdhPJwP36IB34Owww3eDhkOSn0CtURJiGKPlguqyhIT5PdyQT3VFZJB4jFJR0/0jvVLyHI542wg2A==
X-Received: by 2002:a17:90a:c389:: with SMTP id
 h9mr13158014pjt.226.1615537921339;
        Fri, 12 Mar 2021 00:32:01 -0800 (PST)
Received: from localhost (176.222.229.35.bc.googleusercontent.com.
 [35.229.222.176])
        by smtp.gmail.com with ESMTPSA id
 c25sm4340198pfo.101.2021.03.12.00.31.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 12 Mar 2021 00:32:00 -0800 (PST)
From: Yuan Yao <yaoyuan0329os@gmail.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: Yuan Yao <yaoyuan0329os@gmail.com>
Subject: [PATCH 1/1] Fix potential bitmap corruption in ksm_msr_allowed()
Date: Fri, 12 Mar 2021 16:31:57 +0800
Message-Id: <20210312083157.25403-1-yaoyuan0329os@gmail.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In ksm_msr_allowed() we read "count" out of the SRCU read section,
this may cause access to corrupted bitmap in ksm_msr_allowed()
due to kfree() by kvm_clear_msr_filter() in very small ratio.

We can fix this by reading "count" value in the SRCU read
section. The big comment block below shows detail of this
issue:

===== Details =====
bool kvm_msr_allowed(struct kvm_vcpu *vcpu, u32 index, u32 type)
{
	struct kvm *kvm = vcpu->kvm;
	struct msr_bitmap_range *ranges = kvm->arch.msr_filter.ranges;
	u32 count = kvm->arch.msr_filter.count;

    /*
       Schedule out happenes at this point, but before the
       kvm_clear_msr_filter() run "kvm->arch.msr_filter.count = 0;"
       on another CPU, so we get the "old" count value which should
       be > 0 if QEMU already set the MSR filter before.
    */

	u32 i;
	bool r = kvm->arch.msr_filter.default_allow;
	int idx;

	/* MSR filtering not set up or x2APIC enabled, allow everything */
	if (!count || (index >= 0x800 && index <= 0x8ff))
		return true;

    /*
       Schedule in at this point later, now it has very small
       ratio that the kvm_clear_msr_filter() run on another CPU is
       doing "kfree(ranges[i].bitmap)" due to no exist srcu read
       sections of kvm->srcu, then the below code will access
       to a currupted(kfreed) bitmap, we already got count > 0
       before.
    */

	/* Prevent collision with set_msr_filter */
	idx = srcu_read_lock(&kvm->srcu);

	for (i = 0; i < count; i++) {
		u32 start = ranges[i].base;
		u32 end = start + ranges[i].nmsrs;
		u32 flags = ranges[i].flags;
		unsigned long *bitmap = ranges[i].bitmap;

		if ((index >= start) && (index < end) && (flags & type)) {
			r = !!test_bit(index - start, bitmap);
			break;
		}
	}

	srcu_read_unlock(&kvm->srcu, idx);

	return r;
}
---
 arch/x86/kvm/x86.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v6 1/6] s390x: css: Store CSS Characteristics
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12134263
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A557DC43381
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 10:42:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F7D065031
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 10:42:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233201AbhCLKmS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 05:42:18 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:63676 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232988AbhCLKmC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 05:42:02 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12CAWvm1173108
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:02 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=1Kg072U2s1o8UXNvR+hjpC6LwL5yeTNbwooihYMf9Bw=;
 b=Cgprlpvqvdcx7RTTzzpAxX7uLvbyc4Y1HiqvBtEWHcRvQDV63WCSI4/3NhQQAJ95MotL
 TyKHk3zNAY1ccrHQDcFlL53OW9jLn8Gqlzijue8qGnt8Aqz1RoiatnytGesHpdg3fT+X
 sDRje5YVtZ/svfGyL6zhACOShrMEWyGeBhQJIbHgoyw5ofVwY6mr3Ku2lTe/4hmtoJc1
 ClQsKYI24iS1X92EHB9bmI1nmpnK+UbR5GlzAuE/VFNF9EbAAXDXD3fZrl80Lx6e2w7J
 rd5gTrqQLqTLMJDiignO1gNamlaLoAgFus7lzA4wizhovwy9JHA/+qDZpWEo0X1IPDY4 /w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774mfe6f1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:01 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12CAXFwh173949
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:01 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774mfe6da-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 05:42:01 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12CAcRYf019528;
        Fri, 12 Mar 2021 10:41:59 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03fra.de.ibm.com with ESMTP id 3768mpsfpk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 10:41:59 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12CAfuLR13697302
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 12 Mar 2021 10:41:56 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 17A87AE045;
        Fri, 12 Mar 2021 10:41:56 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B07E3AE051;
        Fri, 12 Mar 2021 10:41:55 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.32.251])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 12 Mar 2021 10:41:55 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v6 1/6] s390x: css: Store CSS Characteristics
Date: Fri, 12 Mar 2021 11:41:49 +0100
Message-Id: <1615545714-13747-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1615545714-13747-1-git-send-email-pmorel@linux.ibm.com>
References: <1615545714-13747-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-12_03:2021-03-10,2021-03-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 spamscore=0 mlxscore=0 lowpriorityscore=0 adultscore=0 mlxlogscore=999
 bulkscore=0 malwarescore=0 clxscore=1015 priorityscore=1501 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103120072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CSS characteristics exposes the features of the Channel SubSystem.
Let's use Store Channel Subsystem Characteristics to retrieve
the features of the CSS.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/css.h     | 66 ++++++++++++++++++++++++++++++++
 lib/s390x/css_lib.c | 93 ++++++++++++++++++++++++++++++++++++++++++++-
 s390x/css.c         |  8 ++++
 3 files changed, 166 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.12, take #2
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12135141
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 925CEC433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 16:01:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C9C364FF5
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 16:01:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231636AbhCLQAh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 11:00:37 -0500
Received: from mail.kernel.org ([198.145.29.99]:36812 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232043AbhCLQAe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 11:00:34 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0F1F564FFE;
        Fri, 12 Mar 2021 16:00:34 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lKkDH-001GDF-Qt; Fri, 12 Mar 2021 16:00:31 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Kees Cook <keescook@chromium.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Sami Tolvanen <samitolvanen@google.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm64 fixes for 5.12, take #2
Date: Fri, 12 Mar 2021 16:00:03 +0000
Message-Id: <20210312160003.3920996-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com, ardb@kernel.org,
 catalin.marinas@arm.com, eric.auger@redhat.com, keescook@chromium.org,
 nathan@kernel.org, samitolvanen@google.com, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the second batch of KVM/arm64 fixes for 5.12. The most notable
item is the tidying up of the way we deal with the guest physical
space, which had a couple of warts. The other patches address i-cache
isolation between vcpus (they are supposed to be vcpu-private, but can
not being so...), and a fix for a link-time issue that can occur with
LTO.

Note that this time around, this pull request is on top of kvm/next,
right after the patches you applied last week.

Please pull,

	M.

The following changes since commit 357ad203d45c0f9d76a8feadbd5a1c5d460c638b:

  KVM: arm64: Fix range alignment when walking page tables (2021-03-06 04:18:41 -0500)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.12-2

for you to fetch changes up to 262b003d059c6671601a19057e9fe1a5e7f23722:

  KVM: arm64: Fix exclusive limit for IPA size (2021-03-12 15:43:22 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.12, take #2

- Fix a couple of branches that could be impossible to resolve at
  link time when objects are far apart, such as with LTO
- Mandate i-cache invalidation when two vcpus are sharing a physical CPU
- Fail VM creation if the implicit IPA size isn't supported
- Don't reject memslots that reach the IPA limit without breaching it

----------------------------------------------------------------
Marc Zyngier (3):
      KVM: arm64: Ensure I-cache isolation between vcpus of a same VM
      KVM: arm64: Reject VM creation when the default IPA size is unsupported
      KVM: arm64: Fix exclusive limit for IPA size

Sami Tolvanen (1):
      KVM: arm64: Don't use cbz/adr with external symbols

 Documentation/virt/kvm/api.rst     |  3 +++
 arch/arm64/include/asm/kvm_asm.h   |  4 ++--
 arch/arm64/kvm/arm.c               |  7 ++++++-
 arch/arm64/kvm/hyp/entry.S         |  6 ++++--
 arch/arm64/kvm/hyp/nvhe/hyp-main.c |  6 +++---
 arch/arm64/kvm/hyp/nvhe/tlb.c      |  3 ++-
 arch/arm64/kvm/hyp/vhe/tlb.c       |  3 ++-
 arch/arm64/kvm/mmu.c               |  3 +--
 arch/arm64/kvm/reset.c             | 12 ++++++++----
 9 files changed, 31 insertions(+), 16 deletions(-)
```
#### [PATCH v3 1/8] KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12135547
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 16B16C433E6
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 17:33:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DECBA64FB3
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 17:33:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231557AbhCLRch (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 12:32:37 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:55266 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231928AbhCLRcU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 12:32:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615570340;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=C7rQ5JvwHZU2XBncrE7tSoBDfZg7trh611M/+N48Z8Y=;
        b=jLN3GtK82Xx9Fcg8m9RpQVHYpdzMYmDdnInp97I7FAqkv1UJwwZLhMwuGc8Gk7xMrIpOJ6
        ReMxA47oeW9tWJJ/ndzg88wyOnIunz1mWPV5i+3QyBmuOp6wV8Zz/NBm7gdCe9DZTSOg/y
        6q5z9XnTEl0xo/CRrM2wHyQ4qw2bnm4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-506-SS01kqT_PZqmkhf2MiCfgA-1; Fri, 12 Mar 2021 12:32:18 -0500
X-MC-Unique: SS01kqT_PZqmkhf2MiCfgA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E8B1493920;
        Fri, 12 Mar 2021 17:32:16 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BF2EF1002388;
        Fri, 12 Mar 2021 17:32:13 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com
Cc: james.morse@arm.com, julien.thierry.kdev@gmail.com,
        suzuki.poulose@arm.com, shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH v3 1/8] KVM: arm64: vgic-v3: Fix some error codes when setting
 RDIST base
Date: Fri, 12 Mar 2021 18:31:55 +0100
Message-Id: <20210312173202.89576-2-eric.auger@redhat.com>
In-Reply-To: <20210312173202.89576-1-eric.auger@redhat.com>
References: <20210312173202.89576-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_DEV_ARM_VGIC_GRP_ADDR group doc says we should return
-EEXIST in case the base address of the redist is already set.
We currently return -EINVAL.

However we need to return -EINVAL in case a legacy REDIST address
is attempted to be set while REDIST_REGIONS were set. This case
is discriminated by looking at the count field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v1 -> v2:
- simplify the check sequence
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/1] s390x: mvpg: add checks for op_acc_id
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12134561
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E58C5C433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:48:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B327E64FF5
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:48:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231166AbhCLMrb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 07:47:31 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:16258 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229900AbhCLMrH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 07:47:07 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12CCYFjf019596
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 07:47:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=fuFxI0zE17AgK4O8TVsv8+frJRvi6NDBOTC0fETYWtc=;
 b=GpIp7LLIr2yir5PF74yeUwgzeMbbxZ2l17mqcpgbXRucAEKGhGvphicz88JJ7THh5YhR
 YTkGaYOLz4EiAUy38nXUjzhozKMwsINYm7HTjgg261oLBuN77iZ8lr8hvg4uVG94hPtU
 MqnG/69rEsyhmRPEnyHYGbIBfKfp5adauDr7/Jr6YVB0wTA8pf0+csbb2csFPOB6lXof
 UXo3KwFZN8I/Dz/yKwONPrpF+rwgXyCrpNPvPo4ikyR2WEEBkSN8UYDJr45nhXgqZCGp
 jTYtdaLR75EwOdE05+lV6CRdlQbKE1iJ8IFCffSLv3Ols+1BNs/qwM0z7JZlVRYG/8yF Mw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774m3xud6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 07:47:07 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12CCZcjH024820
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 07:47:07 -0500
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774m3xuca-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 07:47:06 -0500
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12CCgVOf020062;
        Fri, 12 Mar 2021 12:47:04 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma01fra.de.ibm.com with ESMTP id 376agr1fmw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 12:47:04 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12CCl1Gu36766182
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 12 Mar 2021 12:47:01 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 79E83A405F;
        Fri, 12 Mar 2021 12:47:01 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 289E4A4066;
        Fri, 12 Mar 2021 12:47:01 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.13.246])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 12 Mar 2021 12:47:01 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/1] s390x: mvpg: add checks for op_acc_id
Date: Fri, 12 Mar 2021 13:47:00 +0100
Message-Id: <20210312124700.142269-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-12_03:2021-03-10,2021-03-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 bulkscore=0 impostorscore=0 malwarescore=0 mlxscore=0 mlxlogscore=999
 clxscore=1015 suspectscore=0 phishscore=0 adultscore=0 spamscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103120088
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check the operand access identification when MVPG causes a page fault.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/mvpg.c | 28 ++++++++++++++++++++++++++--
 1 file changed, 26 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: X86: Fix missing local pCPU when executing wbinvd on all dirty pCPUs
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12133605
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6230DC4361A
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 02:46:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E55964F91
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 02:46:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231776AbhCLCqH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 21:46:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48908 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231720AbhCLCqD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Mar 2021 21:46:03 -0500
Received: from mail-pf1-x435.google.com (mail-pf1-x435.google.com
 [IPv6:2607:f8b0:4864:20::435])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E9402C061574;
        Thu, 11 Mar 2021 18:46:02 -0800 (PST)
Received: by mail-pf1-x435.google.com with SMTP id 18so867950pfo.6;
        Thu, 11 Mar 2021 18:46:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=d9YsZjl8KPcCfohTLaB3vMCTcxLud525kwliSzoLjSM=;
        b=PsXU7Bu7iJYGWMkIU7bQZJG8iQo65W9qCJRD/PlehbjzcXSjFIKvERxI5eoVvfN8iA
         UyByTpcv7sPtQOz7myde90AQcpD+gyt+35aN5lTZFjjcATXdx4zr9b/AHKZQK/FRjLQe
         ckOON81qhUkKVvHbfjzNq+XcZD9cm6ZHWXuJvZqbeQmwnfo1PohATwr4XXtGjHE/DcVe
         rLoW2wgMKzFiGmfO4izQty2BnCRtJgr6aWRmprh11dTA/4Bvvvy2DEEM3PUwxD1xO669
         Xllr7o1C3I8bBHBRADfjnBGKHiljHC7NGTpJ1kW7CkiW/8DR3ymAT0w3AwM9T3Gko8jk
         lgBA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=d9YsZjl8KPcCfohTLaB3vMCTcxLud525kwliSzoLjSM=;
        b=qFTGZm9fz1satnak4oe50sMbfUlv73nNRYBLKKtD+7tygRGyZ7Vpqpb9Cnxw+wkewM
         VWvEx2Z2nLkDFjuvHNV+zRSWDIUtEhmxOmCUgtDKjD0x9SztlFRyOVBhh32h6pWs139W
         4Y+Nmxs+tYzvyhP6CU0aBQ9pdZWa0EvVgFEIaPmfQCl9mRDMP7knpjdTxEGZcM8kjYjN
         cnsIgbxt1vzS3VEkUxmx9mSGFqGtXajUUmJrH6/Vu0j8DDABB9ucpKIs91UQHfind5l7
         JSGviQ0Ie0yn0mSHux0XHlNasz5wMJuGicQ0wzROp8NKAPIUGP/wgGli+X5CJK3QWLWR
         i4VQ==
X-Gm-Message-State: AOAM533XJ0rI/OxP4lqbfid6rQixDoBL6nLcC3upJr+Txb3mO5j1De6r
        qFGF/g8oQQpkgz0ZMRBlZ+xkC2BUCgE=
X-Google-Smtp-Source: 
 ABdhPJz7xn4dMO2nJjEuZRgkchyM6In2oxsC1ik61xXs99EpuD2rJGq8V6jjGLXAlGM+kunJkU61AA==
X-Received: by 2002:a63:5645:: with SMTP id g5mr9386911pgm.387.1615517162247;
        Thu, 11 Mar 2021 18:46:02 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 e20sm3476846pgm.1.2021.03.11.18.45.59
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 11 Mar 2021 18:46:01 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Nadav Amit <namit@vmware.com>
Subject: [PATCH] KVM: X86: Fix missing local pCPU when executing wbinvd on all
 dirty pCPUs
Date: Fri, 12 Mar 2021 10:45:51 +0800
Message-Id: <1615517151-7465-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

We should execute wbinvd on all dirty pCPUs when guest wbinvd exits 
to maintain datat consistency in order to deal with noncoherent DMA.
smp_call_function_many() does not execute the provided function on 
the local core, this patch replaces it by on_each_cpu_mask().

Reported-by: Nadav Amit <namit@vmware.com>
Cc: Nadav Amit <namit@vmware.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vhost: Fix vhost_vq_reset()
##### From: Laurent Vivier <lvivier@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Laurent Vivier <lvivier@redhat.com>
X-Patchwork-Id: 12134713
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F2EBC4332B
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 14:10:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B63464FDD
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 14:10:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231865AbhCLOJw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 09:09:52 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:60346 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231781AbhCLOJY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 09:09:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615558164;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=sQYoIfj5WQ3gNxzaMGVHtAJ8toU1d/6LwVnCduC2jYw=;
        b=IhmfNMZcSsb9g2B4uedENSRp0A7SHol/bhmJgEC69s0yIZcm8Ey+3L8BMvvueAyo/yM+5c
        gHQ0igu7NFgiVIlJwz2m9EGTcnIk4BSMtRaDg/JFi0vTidxBOS1+V3lIYlxTbu/5pMmVxJ
        JvN1IADDOCHNaghyd+3mGMbOoSNm38k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-340-A4vm1f_pNRqwjRFzk--NuQ-1; Fri, 12 Mar 2021 09:09:20 -0500
X-MC-Unique: A4vm1f_pNRqwjRFzk--NuQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3D392EC1A0;
        Fri, 12 Mar 2021 14:09:19 +0000 (UTC)
Received: from thinkpad.redhat.com (ovpn-112-75.ams2.redhat.com
 [10.36.112.75])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9B52F60877;
        Fri, 12 Mar 2021 14:09:14 +0000 (UTC)
From: Laurent Vivier <lvivier@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        Jason Wang <jasowang@redhat.com>, netdev@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH] vhost: Fix vhost_vq_reset()
Date: Fri, 12 Mar 2021 15:09:13 +0100
Message-Id: <20210312140913.788592-1-lvivier@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost_reset_is_le() is vhost_init_is_le(), and in the case of
cross-endian legacy, vhost_init_is_le() depends on vq->user_be.

vq->user_be is set by vhost_disable_cross_endian().

But in vhost_vq_reset(), we have:

    vhost_reset_is_le(vq);
    vhost_disable_cross_endian(vq);

And so user_be is used before being set.

To fix that, reverse the lines order as there is no other dependency
between them.

Signed-off-by: Laurent Vivier <lvivier@redhat.com>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/8] x86/boot/compressed/64: Cleanup exception handling before booting kernel
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12134539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ABC28C43603
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:39:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 86F4664F0B
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:39:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231500AbhCLMjD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 07:39:03 -0500
Received: from 8bytes.org ([81.169.241.247]:58712 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230127AbhCLMih (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 07:38:37 -0500
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 001EC39B;
        Fri, 12 Mar 2021 13:38:30 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v3 1/8] x86/boot/compressed/64: Cleanup exception handling
 before booting kernel
Date: Fri, 12 Mar 2021 13:38:17 +0100
Message-Id: <20210312123824.306-2-joro@8bytes.org>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210312123824.306-1-joro@8bytes.org>
References: <20210312123824.306-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Disable the exception handling before booting the kernel to make sure
any exceptions that happen during early kernel boot are not directed to
the pre-decompression code.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/boot/compressed/idt_64.c | 14 ++++++++++++++
 arch/x86/boot/compressed/misc.c   |  7 ++-----
 arch/x86/boot/compressed/misc.h   |  6 ++++++
 3 files changed, 22 insertions(+), 5 deletions(-)

```
