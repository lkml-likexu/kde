#### [PATCH 01/17] iommu: remove the unused domain_window_disable method
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12109031
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73D91C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 08:44:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B19B64DF2
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 08:44:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233087AbhCAIoZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 03:44:25 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49588 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233266AbhCAIoE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 03:44:04 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 59951C061786;
        Mon,  1 Mar 2021 00:43:23 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=rQsKH4kOlnBYzeuylC3iIA96x0IvpstTKPzNzAs/+t4=;
 b=cMfnM1kb22wRpVDlsVe2pkdmQG
        /HstTcDL2PF7nulB45FskjiPIrr+eZ+sZrWliZX2WNd2rBRQcHpMv1VpDyw5LvJgBFSYh3BQkBJnY
        55vXdUKAchr0xzT7WO0f9ekFbpcutgsAOtGsxhJQdWt3xwoOhAdadjDZ/EhXATg9f33BSgDAxE380
        B41JladYlAGT6HF/Ok7UhGQMWQYRTwwcQiKrbGEYnL0SMy8ShCQsU3T5361vlmA0sGpml8KYO6e8T
        LK/1QMOWrNSFtzUgIIFG6jn6JN2/5o+IqD2Lhm8mwFUMlB+rtsJzmzjTAXnFFnlk7M7s9ML3BnN5M
        Uoow/QXA==;
Received: from [2001:4bb8:19b:e4b7:cdf9:733f:4874:8eb4] (helo=localhost)
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lGe8t-00FUV8-Tq; Mon, 01 Mar 2021 08:43:05 +0000
From: Christoph Hellwig <hch@lst.de>
To: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Li Yang <leoyang.li@nxp.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        linuxppc-dev@lists.ozlabs.org, linux-arm-msm@vger.kernel.org,
        dri-devel@lists.freedesktop.org, freedreno@lists.freedesktop.org,
        iommu@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH 01/17] iommu: remove the unused domain_window_disable method
Date: Mon,  1 Mar 2021 09:42:41 +0100
Message-Id: <20210301084257.945454-2-hch@lst.de>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210301084257.945454-1-hch@lst.de>
References: <20210301084257.945454-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

domain_window_disable is wired up by fsl_pamu, but never actually called.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 drivers/iommu/fsl_pamu_domain.c | 48 ---------------------------------
 include/linux/iommu.h           |  2 --
 2 files changed, 50 deletions(-)

```
#### [PATCH 1/2] KVM: x86/xen: Fix return code when clearing vcpu_info and vcpu_time_info
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12109621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 779AFC433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 12:54:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B20A64E68
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 12:54:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233519AbhCAMyM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 07:54:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47032 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235218AbhCAMyK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 07:54:10 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0051BC06178A
        for <kvm@vger.kernel.org>; Mon,  1 Mar 2021 04:53:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:Content-Type:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=xmz93cwfIQjZW14w+D3D6/AQJx8CfakKLGheckDukRs=;
 b=nttHqTn+ONxCuveGmoN9bUPk4r
        HiFG3gCVMZjdAev2lrWWcT33saCKgFJBK7XUOPzSGBQTdfZkCFWJ8IuaBWZ42vwJtszxt+j50dFME
        LwRO1aq/gtQ2k8vwgBHnBmPq9K85s2XeW8z5aSVF71I5S2pugGiKkcJK6sLwkDOcqiqLWU9OEGaRR
        mffz5dkLd9ah1bfpm6XkIN1nY1Z9nJK1U5G11o0erGPmtZ+bONluYS3pjd7utyR2ASB0HLlEa224C
        pWtMl8dTi3lcyd1nWiFA9SaK9u0yGSUYW3yGsm5WadN8ri8D5E9ZD3NtuRSXoMVUrEpmnTd/KOeFi
        f/rm1R5g==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lGi2y-00Fiya-3P; Mon, 01 Mar 2021 12:53:16 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1lGi2w-003fcu-0J; Mon, 01 Mar 2021 12:53:10 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH 1/2] KVM: x86/xen: Fix return code when clearing vcpu_info and
 vcpu_time_info
Date: Mon,  1 Mar 2021 12:53:08 +0000
Message-Id: <20210301125309.874953-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

When clearing the per-vCPU shared regions, set the return value to zero
to indicate success. This was causing spurious errors to be returned to
userspace on soft reset.

Also add a paranoid BUILD_BUG_ON() for compat structure compatibility.

Fixes: 0c165b3c01fe ("KVM: x86/xen: Allow reset of Xen attributes")
Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/xen.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/2] samples/vfio-mdev/mdpy: use remap_vmalloc_range
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12108979
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CBB50C433E9
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 08:23:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AD0064DD3
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 08:23:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230459AbhCAIXu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 03:23:50 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45188 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232860AbhCAIXp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 03:23:45 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 76C76C061756;
        Mon,  1 Mar 2021 00:23:04 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=ZJ0mfKKiDbtOHzYkThItWPT9FVUPlFxXRW4kC39qdzY=;
 b=akuYuScZTOm/ePhqN+lw6tAh+X
        EeA0ICEb9zGHyikYeCvJg7Wvh1O70JU3poaBuBIZNXXf5truxXDrdhnwWiLpTOTCRedeSWhL6hW5A
        jfq3x1EZl+WkPvIP+iwJjd5o2+bN8PhaDW8q0GstVPsHEFKmJttf/FG5ftPnhGG+Ik6EeH/fB1fuF
        lKBIIbrYQNSEOcHppQHkklDe9a5F4ucZKtuI1x91Dho/SvWCDZtFwAkla83CbArIJ+gkouPw3nIap
        OwuaSwyXevJZowcBYIQgpNN4sU59W5uf1UpvdT9ybQTb16t1s9iJ1n8S/WEWZMKBPX0t46rRPkiFl
        eWIOnrgg==;
Received: from [2001:4bb8:19b:e4b7:cdf9:733f:4874:8eb4] (helo=localhost)
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lGdpD-00FTKm-Cy; Mon, 01 Mar 2021 08:22:49 +0000
From: Christoph Hellwig <hch@lst.de>
To: Andrew Morton <akpm@linux-foundation.org>
Cc: Kirti Wankhede <kwankhede@nvidia.com>, linux-mm@kvack.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] samples/vfio-mdev/mdpy: use remap_vmalloc_range
Date: Mon,  1 Mar 2021 09:22:34 +0100
Message-Id: <20210301082235.932968-2-hch@lst.de>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210301082235.932968-1-hch@lst.de>
References: <20210301082235.932968-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use remap_vmalloc_range instead of open coding it using
remap_vmalloc_range_partial.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 samples/vfio-mdev/mdpy.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH v4 1/6] s390x: css: Store CSS Characteristics
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12109529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1D8AC433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 11:48:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99DF064E22
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 11:48:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234263AbhCALsd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 06:48:33 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24442 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234188AbhCALr5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 06:47:57 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 121BXuZK061562
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 06:47:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=v/wonPWmwERnt8dYDvIELVtp/cOUxOzPo8zX5zdUDo8=;
 b=oF3WWQu72K41uZS0abnOeMu7UPMbo2Mjve4LKdm/5McQQQd25Q/O1qwRIQ7PrHnHSyiO
 eoSe5Lm13g7fBjNz+BUuEMc8x5G2rCyBG2P4HppxBKa/QfMpkjvFNqiWDpq1rxSpQY7d
 x2ptBTt16+2esoVQFZWhf82wXETVBn0fh0ostmfvH2smBIupEJ4ywrntRSk2to1TvUD9
 wq14pCAp07U9UoiTPVFbZyf+25svvXGgMRRSf87IEb+n0q6ivchdiqD4jWrJTbIDt3TU
 +/VA+7rKLevQESymDQRqAxUmJKCTV95syrRo+u5EPIch3/j6/otLxER3DwsaRZxnsL5e SQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 370xxa1c2g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 06:47:13 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 121BY5DQ061811
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 06:47:12 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 370xxa1c1a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 06:47:12 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 121Bhr3C025923;
        Mon, 1 Mar 2021 11:47:10 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03fra.de.ibm.com with ESMTP id 36ydq80xue-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 11:47:10 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 121Bl7dm36045096
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 1 Mar 2021 11:47:07 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 598CBAE045;
        Mon,  1 Mar 2021 11:47:07 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F1AD3AE051;
        Mon,  1 Mar 2021 11:47:06 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.52.26])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  1 Mar 2021 11:47:06 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v4 1/6] s390x: css: Store CSS Characteristics
Date: Mon,  1 Mar 2021 12:47:00 +0100
Message-Id: <1614599225-17734-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1614599225-17734-1-git-send-email-pmorel@linux.ibm.com>
References: <1614599225-17734-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-01_06:2021-02-26,2021-03-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxscore=0
 lowpriorityscore=0 spamscore=0 mlxlogscore=999 bulkscore=0 impostorscore=0
 priorityscore=1501 clxscore=1015 malwarescore=0 phishscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103010098
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
 lib/s390x/css.h     | 67 ++++++++++++++++++++++++++++++++
 lib/s390x/css_lib.c | 93 ++++++++++++++++++++++++++++++++++++++++++++-
 s390x/css.c         |  8 ++++
 3 files changed, 167 insertions(+), 1 deletion(-)

```
#### [PATCH] docs: kvm: Fix a typo ("althought")
##### From: =?utf-8?q?Jonathan_Neusch=C3=A4fer?= <j.neuschaefer@gmx.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Jonathan_Neusch=C3=A4fer?=
 <j.neuschaefer@gmx.net>
X-Patchwork-Id: 12110691
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF299C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 21:51:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E88660231
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 21:51:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241346AbhCAVvh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 16:51:37 -0500
Received: from mout.gmx.net ([212.227.17.21]:56533 "EHLO mout.gmx.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S244758AbhCAVtO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 16:49:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=gmx.net;
        s=badeba3b8450; t=1614635257;
        bh=zVBUFtB0XtjblJmNjnmM9zPfSHxzFzcx47GazfY4lCs=;
        h=X-UI-Sender-Class:From:To:Cc:Subject:Date;
        b=K3qP7lBlbIxtPiyoA9XsWkp/BmZ0qYxL9h5wTaFTHFazh1hHJaoBazJwsrwigX42S
         6H9pcaIUJqLwF+P9V8+HS6dLvbPeHSHRY0hvVLxlhm969EXH+dwf8Sl1JB4gBQcPW3
         tkc4MKgFxacoSBDzyTzOCL3Z/1fi55A/UmFrkZIM=
X-UI-Sender-Class: 01bb95c1-4bf8-414a-932a-4f6e2808ef9c
Received: from longitude ([37.201.215.134]) by mail.gmx.net (mrgmx104
 [212.227.17.168]) with ESMTPSA (Nemesis) id 1Mq2jC-1ldVwg3Tgg-00n6Zy; Mon, 01
 Mar 2021 22:47:36 +0100
From: =?utf-8?q?Jonathan_Neusch=C3=A4fer?= <j.neuschaefer@gmx.net>
To: linux-doc@vger.kernel.org
Cc: =?utf-8?q?Jonathan_Neusch=C3=A4fer?= <j.neuschaefer@gmx.net>,
 Paolo Bonzini <pbonzini@redhat.com>, Jonathan Corbet <corbet@lwn.net>,
 kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] docs: kvm: Fix a typo ("althought")
Date: Mon,  1 Mar 2021 22:47:21 +0100
Message-Id: <20210301214722.2310911-1-j.neuschaefer@gmx.net>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
X-Provags-ID: V03:K1:CTe05Txa0fPqrncPyK6o5poGV4/BtQtlMFSSGCyT/OugiTbOCbh
 3NZYAXQHyNJXS55FNFx/wjmhy1mlerNfAyoM0gXWrMpAhWKe7qJsQ8J5Buz+pT8BLcRyvat
 COANMF/m46XMhZSfasCOq+V+XBUXdc5tm4BaGFwq+84HA75nhH0DZGL0Ws0Vy7f8TMff0yn
 TB/Aw3Q9Vcjw++OGw4p0w==
X-UI-Out-Filterresults: notjunk:1;V03:K0:gUfQ4K6LBMI=:g+cu8vMnkgzt7iERrau4n5
 Uzu8J1C5DNojCKpw8gMQ7Ci/ZmiE3ji9FZduOOZmNf6TUpCqVjbqjKMH7z5f3UkA2AZvFM/WM
 jgzjMpWBVG4pzPuRUgSEB3XU/ourAI5wKFz5udaOFtj3tX4dPayKlIxA1i0LUlI5zaVHLxx+v
 t3zLIipzs1X6/jjgvdeWEnz9iGSyV+JMdGPWY9/k9lTwHmAfr3Xm02A8NC8Kd5r485UtWbrSd
 DBKi0cE/HN9549g+v5rZx2kHrLU2XtzxGvvPqSSRSUrTKrFm+tuOUyOpQ5jiAYhHmHZnMZBAS
 Tyd6+2o651tJEo4ClGo69L2r3KyKMB9ys/Rl9iMTZjbBxvoYsmTE01n9XVCb/45QJCAclKV83
 B6ygez7ESh0LqZGwS5PWIJ5DN+3+VTXqH8n4GYisJqp6JWj7oIPUNq7T/vyv3SejQbNpGitMP
 2LZhP/DAoMc0yxnt5loZsLqAc+Uq5v3PhrpYHqyUKCH3mOv/GLADfavrQyK0bNZElKmkpaKKe
 GqJRJDywIA5PtKemlAdkDJFA0k70csgNosf/oIy5DumILtYLxyaycmo/T9koQ901RwYdmium/
 7numv9IgphhAw5AmseCsH7mZz4S6Ct2NKARvruckcPEnAjgMa5owtpySvE3KqCeGNjC8otxZG
 FeyPMXeFD98HgSuZxaUKGhmqmq0oX25O0izJBq22eQHmNKzpUEQj523sWtuSZHgHoiacMAVHu
 k+iwwe8cNuyZhsubYAxQ+ZPNmhiKRSdHyz9XS8Cgi9WA49KFWbHnwrzNARmMvagklzr1GPW+H
 Deo6mU8TN2oDIVLIvKqxMV2Ke5V+kvk9vYfiZfNi9jYoVKgit1lqV6GNYsQNULOdXVMZKe7lW
 f/+1Na6efeE5g0d4659A==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jonathan Neuschäfer <j.neuschaefer@gmx.net>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.30.1

```
#### [PATCH] KVM: nSVM: Optimize L12 to L2 vmcb.save copies
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12110615
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DC977C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 20:16:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADD1664DDF
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 20:16:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239067AbhCAUQF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 15:16:05 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:49949 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241170AbhCAUKV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 15:10:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614629329;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=DeZRAZaCcq5fOAnPyHfLItpaonWuUNdGVglPpA6ptmQ=;
        b=NoDoisBQX8cueJ+5Fl8Y38EmJEAtj1Ylzz+pM0KXsMJLzyLGGk3wHfIzaRUX5QgJ5hgsVX
        TK1MmktRjxVfUJIa2Sw9dwEo9svK8HHyLNVVNvnQbqZ2oByXG63YqJkN7pU3X2lsl9Il5m
        C9cczjmCW+irc03PIDRfDkB8JTH3g1Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-332-JYFXC9iyNFCbyNZVNyRsNQ-1; Mon, 01 Mar 2021 15:08:46 -0500
X-MC-Unique: JYFXC9iyNFCbyNZVNyRsNQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C355D801978;
        Mon,  1 Mar 2021 20:08:45 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 45FEF5C1C4;
        Mon,  1 Mar 2021 20:08:45 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH] KVM: nSVM: Optimize L12 to L2 vmcb.save copies
Date: Mon,  1 Mar 2021 15:08:44 -0500
Message-Id: <20210301200844.2000-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the vmcb12 control clean field to determine which vmcb12.save
registers were marked dirty in order to minimize register copies
when switching from L1 to L2. Those L12 registers marked as dirty need
to be copied to L2's vmcb as they will be used to update the vmcb
state cache for the L2 VMRUN.  In the case where we have a different
vmcb12 from the last L2 VMRUN all vmcb12.save registers must be
copied over to L2.save.

Tested:
kvm-unit-tests
kvm selftests
Fedora L1 L2

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 43 ++++++++++++++++++++++++++-------------
 arch/x86/kvm/svm/svm.c    |  1 +
 arch/x86/kvm/svm/svm.h    |  6 ++++++
 3 files changed, 36 insertions(+), 14 deletions(-)

```
#### [RFC PATCH v3 1/8] tools headers: sync headers of asm-generic/hugetlb_encode.h
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12108851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9CC46C433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 07:19:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7236064E40
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 07:19:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232426AbhCAHTY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 02:19:24 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:13396 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232395AbhCAHTX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 02:19:23 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4Dprgc5gKwzjSjx;
        Mon,  1 Mar 2021 14:58:04 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Mon, 1 Mar 2021 14:59:20 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ingo Molnar <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        "Arnaldo Carvalho de Melo" <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v3 1/8] tools headers: sync headers of
 asm-generic/hugetlb_encode.h
Date: Mon, 1 Mar 2021 14:59:09 +0800
Message-ID: <20210301065916.11484-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210301065916.11484-1-wangyanan55@huawei.com>
References: <20210301065916.11484-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch syncs contents of tools/include/asm-generic/hugetlb_encode.h
and include/uapi/asm-generic/hugetlb_encode.h. Arch powerpc supports 16KB
hugepages and ARM64 supports 32MB/512MB hugepages. The corresponding mmap
flags have already been added in include/uapi/asm-generic/hugetlb_encode.h,
but not tools/include/asm-generic/hugetlb_encode.h.

Cc: Ingo Molnar <mingo@kernel.org>
Cc: Adrian Hunter <adrian.hunter@intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@redhat.com>
Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 tools/include/asm-generic/hugetlb_encode.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12109285
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8886AC433E9
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 09:46:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D02464E3F
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 09:46:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234123AbhCAJqO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 04:46:14 -0500
Received: from mga02.intel.com ([134.134.136.20]:12500 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234094AbhCAJpe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 04:45:34 -0500
IronPort-SDR: 
 c6ryIvsKaEkMSXrM2VHkkvYLiA9Pkeik0sls8k3vXzGjw6uu4CxI0Ug2ihW8XsnHWEdxoGVO7H
 4SPv9Hc6ye/w==
X-IronPort-AV: E=McAfee;i="6000,8403,9909"; a="173542477"
X-IronPort-AV: E=Sophos;i="5.81,215,1610438400";
   d="scan'208";a="173542477"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Mar 2021 01:44:48 -0800
IronPort-SDR: 
 fC+0gOq3VyKRbjdhb6WYiOI8P7X7d9wTmSDebKKgDgNAxb1BTpskmXglh4hgq4AMahBMVFHikW
 PAHwGB7ffLgA==
X-IronPort-AV: E=Sophos;i="5.81,215,1610438400";
   d="scan'208";a="599267315"
Received: from jscomeax-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.139.76])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Mar 2021 01:44:42 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on SGX
 bit
Date: Mon,  1 Mar 2021 22:44:28 +1300
Message-Id: 
 <0f5c13b8d89355626c343ad78f60807b321baf6f.1614590788.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1614590788.git.kai.huang@intel.com>
References: <cover.1614590788.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: X86: Fix __x86_set_memory_region() sparse warning
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 12109723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE5A9C433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 13:36:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE64364D90
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 13:36:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235715AbhCANgX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 08:36:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:25518 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235804AbhCANgJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 08:36:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614605683;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ybf+ggtfILCNltr1swxw8VOdjmkBkmS5pZZjWFFS29c=;
        b=dXhdrFWR0AvmUuUiL+E4OMWKR4BP0JNRprjKROm3kgNbnGUq+WbHCyrPOOXH9p7YsKGje6
        6PtVupHy1LfQSZGvBKQtHh5gseOxPez84op1jbBHA4k2b0PC+B7QEvL63nIdxkWP0tvwpz
        6bTKsnMnCe37gWkaJIsLI7tTd/2Hp30=
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-448--qj2q5pFOi2wMK4GRCfuxQ-1; Mon, 01 Mar 2021 08:34:42 -0500
X-MC-Unique: -qj2q5pFOi2wMK4GRCfuxQ-1
Received: by mail-qt1-f198.google.com with SMTP id t5so10623936qti.5
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 05:34:41 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=ybf+ggtfILCNltr1swxw8VOdjmkBkmS5pZZjWFFS29c=;
        b=swLZ8ZkwaaIrmVHvHgZvKSib30QlIVu1eqm7r5u0j8uYtbyR97XoIv1A4PZh+0ahQp
         /OXbdqPctPteHKM2lksNs37haxYvQOvueN0NkpceE0tNbcN0W2Gs1b4nQau2cEGJgAX+
         KR0IUYvKdZWlzMHQdWdzmxfNOC4wUx5Ee1EgHc0o7TA7LcpYiY/3Knku0HzW9qIK7qQ5
         NyuPvotAYgVECpDr7xrRsCPCc8SnJCtGCnPqs+EP+GgzI7Y34ylrCUXKOjlcS/eei8gM
         vLnOWUmkp6Rd6Ro3kvDXAwdj+1FzZ4HWmBtkuHi5x6jfwcMz54ylCELl0gaWUcB1+nO3
         3dKA==
X-Gm-Message-State: AOAM5324P5La143g4vpVzHVHPXLbrJRu48lWHe3sDIU5SB7KytX2ghlY
        Jn/dpZjYkjBaoj7dJZLmLZq27pgOVNlYZK7CWLdmOqBN7L3wShe17337/okJ6UhDOL72yjZMnde
        0bNNOtZeGzdFCLWDkmX1znYwOFZOtS1xuDkssSHtbGn0z/U4RsZecMnxJSJEIvA==
X-Received: by 2002:a05:622a:42:: with SMTP id
 y2mr12949619qtw.186.1614605681281;
        Mon, 01 Mar 2021 05:34:41 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJzbUlZvZ75QwyBB04IJg5lkgSwuMY2dUKh/WmZDmHG/CWukZ7M0cNmCw70cjtan5HBTOp18BQ==
X-Received: by 2002:a05:622a:42:: with SMTP id
 y2mr12949580qtw.186.1614605680734;
        Mon, 01 Mar 2021 05:34:40 -0800 (PST)
Received: from xz-x1.redhat.com
 (bras-vprn-toroon474qw-lp130-25-174-95-95-253.dsl.bell.ca. [174.95.95.253])
        by smtp.gmail.com with ESMTPSA id
 73sm6609609qkk.131.2021.03.01.05.34.39
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 01 Mar 2021 05:34:40 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kernel test robot <lkp@intel.com>
Subject: [PATCH] KVM: X86: Fix __x86_set_memory_region() sparse warning
Date: Mon,  1 Mar 2021 08:34:38 -0500
Message-Id: <20210301133438.396869-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <202102280402.c6iev2Xp-lkp@intel.com>
References: <202102280402.c6iev2Xp-lkp@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Force ERR_PTR_USR() cast even if the return value is meaningless when deleting
slots, just to pass the sparse check.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Fixes: ff5a983cbb3746d371de2cc95ea7dcfd982b4084
Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RFC] hw/misc/pc-testdev: add support for ioregionfd testing
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12109695
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0D25BC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 13:24:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5EAD64DE8
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 13:24:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235619AbhCANYA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 08:24:00 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53446 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235344AbhCANX7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 08:23:59 -0500
Received: from mail-lf1-x12b.google.com (mail-lf1-x12b.google.com
 [IPv6:2a00:1450:4864:20::12b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EFFDFC061756
        for <kvm@vger.kernel.org>; Mon,  1 Mar 2021 05:23:18 -0800 (PST)
Received: by mail-lf1-x12b.google.com with SMTP id p21so25417286lfu.11
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 05:23:18 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KbNn16NW2voIZnb30QSq1tkvME8A5PE6xaA6lY++9bM=;
        b=Mcb9Sel/Cij671Jq3Mp6O1ajs8csB043sivwyFBDKNS4fY2ti2iYcoe/poPnGqaCbn
         +xyG86Jebl+2OR2EJgCHyxZllJuZgWi9ZiJY21LNajSuUlpwsDNpCQ5Q9QAFYv0sEjpr
         c4HBLuTtsJAZGJUlPTWSF9ki/ekzTIkvvQwL6N1NFTgEnLNXC1hm6BC4Vy3TguUsXvJH
         Ubi9/0DNbGe4lDqGfnp7Rau7IqjryIrr1EcqOhHIUUEDONibp5zBaNctPQGwgGYJp9oQ
         s6LxzN+jN9Cyg2ygWqlsV32MZF1Aiz4dK8nx1boFp0PzPob9rzKpVvd8AYajXxwtqKSy
         BG4A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KbNn16NW2voIZnb30QSq1tkvME8A5PE6xaA6lY++9bM=;
        b=mPFPoC8ss1iFoIXqZkENGNI8qBEzWIKvefDLAKm2FUpXJKpTIkqUVYPL7o1FTIxW72
         CNJzPD6ok245A/SB0In3YITBgYkr7RAFCrhRwaL+oYQ/10VUsPuT5iOclsFrd5XQcOCE
         /hMqn1Twil38tbMbw/OESoDQ9B3i+d73RoNOwfF8JzU3hiPZmPf1Jcd5RfOmxShCawHO
         TUv8yS4SIBo8VbjWsjnFFKP9RTgixYktPEP9GXazA5vWp7ijM380vMlpDwYEMtihaxmk
         wD3sqo6CnaRscRo2vnvXyZplzCG/W1Ha0KYXStje+NG0IkM5NxHDc9RM16qs8/10/+g+
         6ylQ==
X-Gm-Message-State: AOAM530M9SfD1DhD4aooUZA/69bcTN6hMja0f1Tiu0sKcUnP5iPeRWZf
        JcE63tXqmQdKMvklwfLUwW4=
X-Google-Smtp-Source: 
 ABdhPJy5AUaM9OlJQciR8h4OFDb96hBCTYCCzbhLuie3Bf1IQqD3idGVjViOAwhytBIVbXlTFy8lgQ==
X-Received: by 2002:ac2:420b:: with SMTP id y11mr9462077lfh.215.1614604997409;
        Mon, 01 Mar 2021 05:23:17 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 w26sm2291420lfr.186.2021.03.01.05.23.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 01 Mar 2021 05:23:17 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [PATCH RFC] hw/misc/pc-testdev: add support for ioregionfd testing
Date: Mon,  1 Mar 2021 16:16:28 +0300
Message-Id: <20210301131628.5211-1-eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
---
 hw/misc/pc-testdev.c      | 74 +++++++++++++++++++++++++++++++++++++++
 include/sysemu/kvm.h      |  4 +--
 linux-headers/linux/kvm.h | 24 +++++++++++++
 3 files changed, 100 insertions(+), 2 deletions(-)

```
#### [RFC PATCH kvm-unit-tests] x86: add ioregionfd fast PIO test
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12110493
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3CC7BC433E6
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:44:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D817F60232
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:44:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239965AbhCASoZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 13:44:25 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36908 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239157AbhCASlY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 13:41:24 -0500
Received: from mail-lj1-x233.google.com (mail-lj1-x233.google.com
 [IPv6:2a00:1450:4864:20::233])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 435BAC06178A
        for <kvm@vger.kernel.org>; Mon,  1 Mar 2021 10:40:29 -0800 (PST)
Received: by mail-lj1-x233.google.com with SMTP id e2so13516992ljo.7
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 10:40:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XVzUhQp6eXREgIfc0wMPWIfpm6zGqEG1kwboLqi5P7c=;
        b=NW1m2PMF3tWGdvQJFfkz0NbP8LDG0wWxUAUvUpOzM2KM2pm16Zo1TWnJmOqTahjNM2
         rPZTMUE1NPEw90skwzhOeKGtIsQVOvRok0P06LvuNP8oQ+imRTWCxmxNCVmZdTUXNecj
         i+C8YeSqVw/4MjkkbqUTHuJGLQGCGz3iVibgjqvmSCSF6CZAK5aAdW86QI4XqVa4kG8k
         XEGWswaWIliQ/q99Q6cMu9/dzIKlILZfO/Z+b5hV1MVBXTXdY2CZIHCR+zoQaaKt2Pg8
         gu+Ob5TufGrus73LW8wUNqwy+qE9ixG+qQuvj29S85I2ZhnS1JuPbbOOceM6D2tY1QR8
         gzKg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XVzUhQp6eXREgIfc0wMPWIfpm6zGqEG1kwboLqi5P7c=;
        b=hdyU8WKlZ4E0bSg0e6RMunksrtz7ZFa6756v+j9OtGRnYMaxuyUso9pIthp2VFX/YI
         ubOqeqwgz91Gf296k7OukSivDn3CjrhlWV05ucAS+S3pYOVg/ZZdgN9QRMDr7l+EE2Sz
         Hctfb2bYsqd3N2BQtMRC+t6U5qnBoPKSa7I92sIhBqNRm4Zcr+EM5THtJUpNmqjxczOP
         xR870FK5kVXXn8Gz02YG/8bx7uk7uf6BtYLBhPjqfRQx7iwyTYABdC/PgRXlpYvAKArh
         fIIuvAHaesa8BuKA4fnV2VDsze/3/czdOxfOOXtfq+dgBfks1qBbjmPOaoOOBzpdMKnL
         YHow==
X-Gm-Message-State: AOAM533t4yTPOu7ecWeE7gc/RKTblzCKxjlsVF7WXszUbRQJ6YxZtY9/
        AA71S41QsjPq0rUg+kiUh+Ev5XydNGqnAQ==
X-Google-Smtp-Source: 
 ABdhPJxTNI1yJNRkzV+13Iwf3XYo1/XECSScrRGpTqqLCJ3K8GTks5BNo1rPpTZetpC07+C0kCojwg==
X-Received: by 2002:a2e:b888:: with SMTP id r8mr9661635ljp.505.1614624027037;
        Mon, 01 Mar 2021 10:40:27 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 w12sm2209410lft.281.2021.03.01.10.40.26
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 01 Mar 2021 10:40:26 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC PATCH kvm-unit-tests] x86: add ioregionfd fast PIO test
Date: Mon,  1 Mar 2021 21:33:19 +0300
Message-Id: <20210301183319.12370-1-eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
---
 scripts/common.bash   | 12 +++++--
 scripts/runtime.bash  |  9 +++++
 x86/Makefile.common   |  5 ++-
 x86/Makefile.x86_64   |  2 ++
 x86/ioregionfd-test.c | 84 +++++++++++++++++++++++++++++++++++++++++++
 x86/ioregionfd_pio.c  | 24 +++++++++++++
 x86/unittests.cfg     |  7 ++++
 7 files changed, 140 insertions(+), 3 deletions(-)
 create mode 100644 x86/ioregionfd-test.c
 create mode 100644 x86/ioregionfd_pio.c

```
#### [PATCH] s390: cio: Return -EFAULT if copy_to_user() fails
##### From: Wang Qing <wangqing@vivo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wang Qing <wangqing@vivo.com>
X-Patchwork-Id: 12109587
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 92810C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 12:09:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E36B64E38
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 12:09:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232934AbhCAMJX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 07:09:23 -0500
Received: from mail-m121143.qiye.163.com ([115.236.121.143]:38234 "EHLO
        mail-m121143.qiye.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232890AbhCAMJV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 07:09:21 -0500
X-Greylist: delayed 374 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 01 Mar 2021 07:09:20 EST
Received: from vivo-HP-ProDesk-680-G4-PCI-MT.vivo.xyz (unknown
 [58.251.74.231])
        by mail-m121143.qiye.163.com (Hmail) with ESMTPA id 0EDF654031F;
        Mon,  1 Mar 2021 20:01:43 +0800 (CST)
From: Wang Qing <wangqing@vivo.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Peter Oberparleiter <oberpar@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Wang Qing <wangqing@vivo.com>
Subject: [PATCH] s390: cio: Return -EFAULT if copy_to_user() fails
Date: Mon,  1 Mar 2021 20:01:33 +0800
Message-Id: <1614600093-13992-1-git-send-email-wangqing@vivo.com>
X-Mailer: git-send-email 2.7.4
X-HM-Spam-Status: e1kfGhgUHx5ZQUtXWQgYFAkeWUFZS1VLWVdZKFlBSE83V1ktWUFJV1kPCR
        oVCBIfWUFZHU4fSxhOSEhKGktJVkpNSk9NS0tKS0hOTkNVEwETFhoSFyQUDg9ZV1kWGg8SFR0UWU
        FZT0tIVUpKS0hNSlVLWQY+
X-HM-Sender-Digest: e1kMHhlZQR0aFwgeV1kSHx4VD1lBWUc6Ngg6EAw6Nj8XMRAUQxoBHBg#
        Kk4aC0pVSlVKTUpPTUtLSktPSklLVTMWGhIXVQwaFRwKEhUcOw0SDRRVGBQWRVlXWRILWUFZTkNV
        SU5KVUxPVUlISllXWQgBWUFJSExJNwY+
X-HM-Tid: 0a77edaa6635b038kuuu0edf654031f
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The copy_to_user() function returns the number of bytes remaining to be
copied, but we want to return -EFAULT if the copy doesn't complete.

Signed-off-by: Wang Qing <wangqing@vivo.com>
---
 drivers/s390/cio/vfio_ccw_ops.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/3] s390x: introduce leave_pstate to leave userspace
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12110465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB1FCC43381
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:32:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B52AC64F2A
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:32:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235758AbhCAScJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 13:32:09 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44634 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238540AbhCAS3T (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 13:29:19 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 121I4wnS121994
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 13:28:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=9bwW9CGbrMMECf0xReKEszexMRFCxQ3x7BNBULSikm8=;
 b=rEJW8UQbbssuC1/YYdzNcn845FU/8PwOpo+r3Yw+LQ3uXNNYntG68jbYFTXuubi0dyIn
 Wc7t8tQUP/9o9Cs+kKr/FiRLxLhpIgCNjueQGRxVfmKdS+oHM8d4aDVaGarfbTnt9hb0
 u66hN5cdpSk+/a1iLQb4a/qCojxeAL9rfzqtu12XZgX21GV9oBtZEMzsdJshLuoLpv6p
 /Hs7vPEEmv0z1qoBPMuHb72t+AJnV4JgAtoNITDyKT4AP91z9q1l4K1tUo0L+ZFmswTz
 YbzgNzy96w8SELl/LCZjh/ETsUU49R84gg+ytPBXiy4d86zFXaKlXFnVt8DjV4L3NgqT Nw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3713uv3k53-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 13:28:37 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 121I5blX131303
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 13:28:37 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3713uv3k4j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 13:28:37 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 121IRPms005013;
        Mon, 1 Mar 2021 18:28:34 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 371162g5nw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 18:28:34 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 121ISVJc42271042
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 1 Mar 2021 18:28:31 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 999D74203F;
        Mon,  1 Mar 2021 18:28:31 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 38D1542042;
        Mon,  1 Mar 2021 18:28:31 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.194])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  1 Mar 2021 18:28:31 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v3 1/3] s390x: introduce leave_pstate to leave
 userspace
Date: Mon,  1 Mar 2021 19:28:28 +0100
Message-Id: <20210301182830.478145-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210301182830.478145-1-imbrenda@linux.ibm.com>
References: <20210301182830.478145-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-01_12:2021-03-01,2021-03-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 mlxlogscore=999
 spamscore=0 impostorscore=0 suspectscore=0 priorityscore=1501 phishscore=0
 clxscore=1015 lowpriorityscore=0 malwarescore=0 bulkscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103010146
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In most testcases, we enter problem state (userspace) just to test if a
privileged instruction causes a fault. In some cases, though, we need
to test if an instruction works properly in userspace. This means that
we do not expect a fault, and we need an orderly way to leave problem
state afterwards.

This patch introduces a simple system based on the SVC instruction.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/arch_def.h |  7 +++++++
 lib/s390x/interrupt.c    | 12 ++++++++++--
 2 files changed, 17 insertions(+), 2 deletions(-)

```
