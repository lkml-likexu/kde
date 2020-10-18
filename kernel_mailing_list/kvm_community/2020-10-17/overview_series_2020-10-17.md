#### [PATCH 1/2] KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11842621
Return-Path: <SRS0=FmXH=DY=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D16AC433DF
	for <kvm@archiver.kernel.org>; Sat, 17 Oct 2020 06:04:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B4E52072C
	for <kvm@archiver.kernel.org>; Sat, 17 Oct 2020 06:04:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="hz839BBm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2411688AbgJQGEH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 17 Oct 2020 02:04:07 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:52364 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2436799AbgJQGEH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 17 Oct 2020 02:04:07 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09H00iio150291;
        Sat, 17 Oct 2020 00:02:56 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=WuWq34kkxX2RV/tWqIFlgyd5ZnXq0sK9LT4MF9ifw/g=;
 b=hz839BBmMF5MR2rHZ9cnCY+qzkls+CwUiWlQPt6i9tLFL591zxNS0yIGp879M1zj5qBB
 kz70YBVM4HNRKEmJCuHFRxCYN6mJVijHsHS8IGyn8QZtTE5Cm3mB0SMowg47GjCjozLd
 h7Hbzv6H7oVuNMpHQ8n2RDgUk/GnZuvB4pW5x5gr32rZQrNpeB++yZcCylH404m/b/sx
 fJzcmgOUxEmVGP9z6Nq2NA3KwNJN7zmVVaK2ODzg7vWyoPnpnaBeMrBHThsvFtUlM3KQ
 1xMGeC2N3guq5vZ+qzTexm4fbZZculPu/Mq40STnV3tfHNE7L2NVnMBmCx3LLRNuJvdk GA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 3434wm44vp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 17 Oct 2020 00:02:55 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09H02leV042922;
        Sat, 17 Oct 2020 00:02:55 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 347nqrg01y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 17 Oct 2020 00:02:55 +0000
Received: from abhmp0004.oracle.com (abhmp0004.oracle.com [141.146.116.10])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 09H02sLc022733;
        Sat, 17 Oct 2020 00:02:54 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 16 Oct 2020 17:02:53 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/2] KVM: nSVM: Check reserved values for 'Type' and invalid
 vectors in EVENTINJ
Date: Sat, 17 Oct 2020 00:02:33 +0000
Message-Id: <20201017000234.42326-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20201017000234.42326-1-krish.sadhukhan@oracle.com>
References: <20201017000234.42326-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9776
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxscore=0 spamscore=0
 mlxlogscore=999 adultscore=0 phishscore=0 malwarescore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010160169
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9776
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxscore=0
 malwarescore=0 phishscore=0 suspectscore=1 impostorscore=0 clxscore=1015
 spamscore=0 priorityscore=1501 bulkscore=0 adultscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010160169
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

```
#### [PATCH v4] KVM: Check the allocation of pv cpu mask
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11842911
Return-Path: <SRS0=FmXH=DY=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BB488C433DF
	for <kvm@archiver.kernel.org>; Sat, 17 Oct 2020 17:54:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 798CE20760
	for <kvm@archiver.kernel.org>; Sat, 17 Oct 2020 17:54:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UZMxJgpw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438714AbgJQRyo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 17 Oct 2020 13:54:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53464 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2438689AbgJQRyo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 17 Oct 2020 13:54:44 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2906EC061755;
        Sat, 17 Oct 2020 10:54:44 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id hk7so3243215pjb.2;
        Sat, 17 Oct 2020 10:54:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ywf91qFk4g7sz+DlmxxY8d4Lv3wU4S3rRm5J3fQEk4I=;
        b=UZMxJgpw2+g0COQ0LZ330jX8puaeXgFg86Yfbu4RbU2DBTTg61lxtelBciP6dNan4K
         UmV5FoIhzK7ibnO9G4ii5EDKh+HWCsi/8+eVxGxEXcfOlfsoPHFlQtT0k2AV3QOLVu+1
         hny/0fnCMOeS8dsZYnwWypgG56VNHBgALMCJz2mazB5ia2xo8EfX4q3QaNqv23qcxw/f
         Ou7X+Aab1THgbP9vdSrkyxJv2Cuo/5gwXIanzJ/UrkrxvJxX3Edc8yXReN3FI98DLDNb
         sPfjeqEgDsNMzEu+28ZHFJRJ/4yim5X2H/xv/0RPHSAu5p/SFtwvcblfr28DbnKO+/sh
         h+IA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ywf91qFk4g7sz+DlmxxY8d4Lv3wU4S3rRm5J3fQEk4I=;
        b=WWDJ0cgOKzT7gsW6KUgK7dhrOfmTvQLEW+sCFBPYCEioNs3Tmdy/pP3kP/HWbZV7v6
         1W0C4VnuL1bR2GRKMSfYslISTDJbuvxTXefn6aZs+XeK1w7nk+7sBkCwgSyH9yn4QR6j
         l3jP8117sZCqgm4ok7j/vjnG8Zkmhlx2B34tzhjres/GFAzZ/axdIVG+8baw6IQ4jykC
         q2vSuphUlkZeWKXHyjzUOiiFreSQQGtFFDiYoqPr5UplTR4lNG7PGzJLGIHrb2cnRoRH
         lnAkCE+QVYB/zAuOlXBqUxTDPNlm1RX2Unflt6zoCC9KkLjn2aNWZMz0/HEvbeEMPWJx
         +PPw==
X-Gm-Message-State: AOAM531HQWwsMGmTxDpv5PVINzamsiEGm4ijpTgRDoFV1+x3Lr3GXAtr
        pw0wFq78311oRb00E/T6E2inYzP2Tdmp
X-Google-Smtp-Source: 
 ABdhPJzWAzu9OVUFxwRwXzu0nwufS/0UacK/dYlj/pcYUHlETMRaHkFvdxPLGJ4p+Q9uF4gGoYpj2A==
X-Received: by 2002:a17:902:8508:b029:d5:af79:8b40 with SMTP id
 bj8-20020a1709028508b02900d5af798b40mr9886951plb.28.1602957283250;
        Sat, 17 Oct 2020 10:54:43 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 b3sm6309041pfd.66.2020.10.17.10.54.40
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 17 Oct 2020 10:54:42 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v4] KVM: Check the allocation of pv cpu mask
Date: Sun, 18 Oct 2020 01:54:36 +0800
Message-Id: <20201017175436.17116-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

check the allocation of per-cpu __pv_cpu_mask. Init
'send_IPI_mask_allbutself' only when successful and check the allocation
of __pv_cpu_mask in 'kvm_flush_tlb_others'.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
v1 -> v2:
 * add CONFIG_SMP for kvm_send_ipi_mask_allbutself to prevent build error
v2 -> v3:
 * always check the allocation of __pv_cpu_mask in kvm_flush_tlb_others
v3 -> v4:
 * mov kvm_setup_pv_ipi to kvm_alloc_cpumask and get rid of kvm_apic_init

 arch/x86/kernel/kvm.c | 53 +++++++++++++++++++++++++++++--------------
 1 file changed, 36 insertions(+), 17 deletions(-)

```
