#### [PATCH v2 1/9] configure: Add sys/timex.h to probe clock_adjtime
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 12026641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0DC3C433DB
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 06:39:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E1562225E
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 06:39:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732630AbhARGjj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 01:39:39 -0500
Received: from wnew4-smtp.messagingengine.com ([64.147.123.18]:57479 "EHLO
        wnew4-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730636AbhARGjf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Jan 2021 01:39:35 -0500
Received: from compute6.internal (compute6.nyi.internal [10.202.2.46])
        by mailnew.west.internal (Postfix) with ESMTP id 53B0E167A;
        Mon, 18 Jan 2021 01:38:27 -0500 (EST)
Received: from mailfrontend1 ([10.202.2.162])
  by compute6.internal (MEProxy); Mon, 18 Jan 2021 01:38:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=flygoat.com; h=
        from:to:cc:subject:date:message-id:in-reply-to:references
        :mime-version:content-transfer-encoding; s=fm1; bh=JkDA4Wi2GI0B3
        bcDDU6/HuHDUW1caUijozfHO0X7odA=; b=Q2f63C4OvLf+Cic/HcnyLKb3GIU6n
        6JkVvAbnISPFBLJmqTJdPsntzLxIAIRu7tnVX661Ee9aUJ7tEYF0yYScMpHPuuT3
        gWpf+/VrJtKDFqPj459Rffq067mbK5/MDc5NYosp0sYlTHn21QqKnlnBgAeT9f6p
        g0NwnO2+b5Vu7xRWItwSG8+5gueF0xALnMdTbnngFDdJGznY0SvEu3GKnQLYRwQA
        TqtBsTB5Rws0rwFArRbt9XBqYozNr8RHPrmXublRcYfl2Rfx10v5Qlmd9DTQ9zrt
        YAVbUlq9v5KKn6/2+vdZ6FXMQiP0EMOA49V+jsIeRSsC/pbTEoksi0bow==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :in-reply-to:message-id:mime-version:references:subject:to
        :x-me-proxy:x-me-proxy:x-me-sender:x-me-sender:x-sasl-enc; s=
        fm1; bh=JkDA4Wi2GI0B3bcDDU6/HuHDUW1caUijozfHO0X7odA=; b=PsIhX8CC
        RKPW5WVS7OnLCtCD1JoI026OW7rEzsL+F2E6QHadrxlUBunyW387gYeAw6Olrxx1
        FemT9C6kWu8FaxEL5eAOQth89mEiv9bF0XmvPSYgIqoXas4JbJt0iwXli3Jg9Ipm
        05FlyQRIYdXf/yDl61PsSqHYarQwdeugt76OEuFnCM8sIofYFr0R5+DQNki0ec0a
        lXnYabCnDbzMrQnnwgU07GQdmFhW+6ZjDyIGd9QSyLJvHWcXuHV01NNhg5WDr5TS
        dx1tAe5yhTWXwPEUIolfEOCNbR7mW5nVbKSkg232MWzTlKZ73xMXxvgOa2dTdExr
        gWJ4/lwaNAaNwQ==
X-ME-Sender: <xms:4iwFYDQpTlWEeiJgIe9hTFeiJ5cDoMSakyBOdRBDwQKMeMLmyCuGwQ>
    <xme:4iwFYExfMudvoI-3dFmx9hDlkAN_7hTMjvFKawqBoJlHNqfxttHk0PRQUxozntgaU
    nOkLwY--S7XwviKVG8>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrtdejgdeliecutefuodetggdotefrodftvf
    curfhrohhfihhlvgemucfhrghsthforghilhdpqfgfvfdpuffrtefokffrpgfnqfghnecu
    uegrihhlohhuthemuceftddtnecusecvtfgvtghiphhivghnthhsucdlqddutddtmdenuc
    fjughrpefhvffufffkofgjfhgggfestdekredtredttdenucfhrhhomheplfhirgiguhhn
    ucgjrghnghcuoehjihgrgihunhdrhigrnhhgsehflhihghhorghtrdgtohhmqeenucggtf
    frrghtthgvrhhnpeejiefhgfetleekleffudektdehvedujedvgeekkeejfefhhffhtedu
    tefgtdffueenucfkphepudduiedrvddvkedrkeegrddvnecuvehluhhsthgvrhfuihiivg
    eptdenucfrrghrrghmpehmrghilhhfrhhomhepjhhirgiguhhnrdihrghnghesfhhlhihg
    ohgrthdrtghomh
X-ME-Proxy: <xmx:4iwFYI0zgWu2O_l4Y7dcl-I3w48Yem2suJCZIB2qR4LYE1E1Z9pauQ>
    <xmx:4iwFYDANM-uBbpiR4KsbV4Om1xovQjBTQs1VBA8-thlIA5-gNbFyOQ>
    <xmx:4iwFYMiBGQcq69O9tnHOXLp1gt_8qNUJpTc8B_SjKhgXHKppv0JH5g>
    <xmx:4iwFYIxps6-GK580Z8dKBTLw3OfR4Ce4SJwhVLbqk2Wh16mPRTl2ZEe9UA4brLFj>
Received: from strike.U-LINK.com (unknown [116.228.84.2])
        by mail.messagingengine.com (Postfix) with ESMTPA id A3E5424005C;
        Mon, 18 Jan 2021 01:38:20 -0500 (EST)
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: qemu-devel@nongnu.org
Cc: David Gibson <david@gibson.dropbear.id.au>, qemu-ppc@nongnu.org,
 Greg Kurz <groug@kaod.org>, Max Reitz <mreitz@redhat.com>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Fam Zheng <fam@euphon.net>,
 Viktor Prutyanov <viktor.prutyanov@phystech.edu>,
 Alistair Francis <alistair@alistair23.me>, Thomas Huth <thuth@redhat.com>,
 Laurent Vivier <lvivier@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, qemu-block@nongnu.org,
 Kevin Wolf <kwolf@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH v2 1/9] configure: Add sys/timex.h to probe clock_adjtime
Date: Mon, 18 Jan 2021 14:38:00 +0800
Message-Id: <20210118063808.12471-2-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210118063808.12471-1-jiaxun.yang@flygoat.com>
References: <20210118063808.12471-1-jiaxun.yang@flygoat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is not a part of standard time.h. Glibc put it under
time.h however musl treat it as a sys timex extension.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 configure | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/1] KVM: s390: diag9c forwarding
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 12027323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77C03C433E0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 13:19:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 42D6B22B4E
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 13:19:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404328AbhARNSw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 08:18:52 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:54542 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2392127AbhARNSh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Jan 2021 08:18:37 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10ID4MEQ007820;
        Mon, 18 Jan 2021 08:17:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=W9sqsEtTP6PItH65+OwFBh0MNe+PTRnI9qdXb17xej8=;
 b=P/KIHlAaN9fLFymvLT3ZupKtA2AOxObf0F/FqSsWeU6G/rxMEZ4eXBWbgnXyGwjj4KN9
 Nj21YzIbHEDj5e0pEyVW2+zx11wJSqctFoUx09JRGMxq5dNFkxkGUoERLbxxSK5qb2wj
 pcLbpsElnm/eHaadNIk1alS4w8bynZbuoxYZ1tyYJibkN7yH4jqfaMpot9FIhlg96/VF
 rmfGcpBo6cXF/oqF7vty/l+cL9YhuNrfPFfDDOWDRw7z5vJZsMXPZz6Awh98xCzlibXD
 jrpnElOa/waFJyGQllKJ2N53wgwz2FVUqia6eyXQGpdrxRvZqDAoqMKwEsCCt8QFSw9s CQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3657y35e7k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 08:17:46 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10ID4rA5010176;
        Mon, 18 Jan 2021 08:17:45 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3657y35e6q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 08:17:45 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10IDHGDu030835;
        Mon, 18 Jan 2021 13:17:43 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 363qs7j2sn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 13:17:43 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10IDHefr37552638
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Jan 2021 13:17:40 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 41DDF42041;
        Mon, 18 Jan 2021 13:17:40 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 27D1742049;
        Mon, 18 Jan 2021 13:17:40 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 18 Jan 2021 13:17:40 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id D74A5E0A39; Mon, 18 Jan 2021 14:17:39 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH 1/1] KVM: s390: diag9c forwarding
Date: Mon, 18 Jan 2021 14:17:39 +0100
Message-Id: <20210118131739.7272-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20210118131739.7272-1-borntraeger@de.ibm.com>
References: <20210118131739.7272-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-18_11:2021-01-18,2021-01-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 lowpriorityscore=0 phishscore=0 priorityscore=1501 mlxscore=0
 clxscore=1015 spamscore=0 malwarescore=0 mlxlogscore=999 suspectscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101180077
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pierre Morel <pmorel@linux.ibm.com>

When we receive intercept a DIAG_9C from the guest we verify
that the target real CPU associated with the virtual CPU
designated by the guest is running and if not we forward the
DIAG_9C to the target real CPU.

To avoid a diag9c storm we allow a maximal rate of diag9c forwarding.

The rate is calculated as a count per second defined as a
new parameter of the s390 kvm module: diag9c_forwarding_hz .

The default value is to not forward diag9c.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/include/asm/smp.h      |  1 +
 arch/s390/kernel/smp.c           |  1 +
 arch/s390/kvm/diag.c             | 31 ++++++++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c         |  6 ++++++
 arch/s390/kvm/kvm-s390.h         |  8 ++++++++
 6 files changed, 45 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v2 01/26] x86/cpufeatures: Add SGX1 and SGX2 sub-features
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12026357
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DE6EEC433E6
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:27:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B5217224B1
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:27:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731590AbhARD1t (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 17 Jan 2021 22:27:49 -0500
Received: from mga14.intel.com ([192.55.52.115]:9511 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728602AbhARD1r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Jan 2021 22:27:47 -0500
IronPort-SDR: 
 OJuk4Nwu1M0ONch/pRl+yUJSAxTVlgr/ujhBCw7cvFVsGjD3R4Sln9tpRy+1LLv1w9OBWuR7RP
 9XjLptxuzk2g==
X-IronPort-AV: E=McAfee;i="6000,8403,9867"; a="177975324"
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="177975324"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 19:27:04 -0800
IronPort-SDR: 
 CTq0FajyKyTvJ09uqyQEFk5C/TJOb38s49qlC/sX6tOmybNm78qzyfzaEiSJwWrEi47u2XA336
 ClHSGHMO+0eQ==
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="573150713"
Received: from amrahman-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.142.253])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 19:27:01 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH v2 01/26] x86/cpufeatures: Add SGX1 and SGX2 sub-features
Date: Mon, 18 Jan 2021 16:26:49 +1300
Message-Id: 
 <87385f646120a3b5b34dc20480dbce77b8005acd.1610935432.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1610935432.git.kai.huang@intel.com>
References: <cover.1610935432.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <seanjc@google.com>

Add SGX1 and SGX2 feature flags, via CPUID.0x12.0x0.EAX, as scattered
features.  As part of virtualizing SGX, KVM will expose the SGX CPUID
leafs to its guest, and to do so correctly needs to query hardware and
kernel support for SGX1 and SGX2.

Also add SGX related feature bits to CPUID dependency table to make
clearing SGX feature easier.

Signed-off-by: Sean Christopherson <seanjc@google.com>
Co-developed-by: Kai Huang <kai.huang@intel.com>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 2 ++
 arch/x86/kernel/cpu/cpuid-deps.c   | 3 +++
 arch/x86/kernel/cpu/feat_ctl.c     | 1 -
 arch/x86/kernel/cpu/scattered.c    | 2 ++
 4 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: get smi pending status correctly
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 12026787
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 29FDFC433DB
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 08:49:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4B0A221E3
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 08:49:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388017AbhARIsv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 03:48:51 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11108 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387957AbhARIsS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Jan 2021 03:48:18 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DK5413sQLz15vJr;
        Mon, 18 Jan 2021 16:46:25 +0800 (CST)
Received: from localhost (10.174.150.219) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.498.0; Mon, 18 Jan 2021
 16:47:22 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>, <pbonzini@redhat.com>
CC: <linux-kernel@vger.kernel.org>, <seanjc@google.com>,
        <vkuznets@redhat.com>, <weidong.huang@huawei.com>,
        <wangxinxin.wang@huawei.com>, <jianjay.zhou@huawei.com>,
        <zhuangshengen@huawei.com>
Subject: [PATCH] KVM: x86: get smi pending status correctly
Date: Mon, 18 Jan 2021 16:47:20 +0800
Message-ID: <20210118084720.1585-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.28.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.150.219]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The injection process of smi has two steps:

    Qemu                        KVM
Step1:
    cpu->interrupt_request &= \
        ~CPU_INTERRUPT_SMI;
    kvm_vcpu_ioctl(cpu, KVM_SMI)

                                call kvm_vcpu_ioctl_smi() and
                                kvm_make_request(KVM_REQ_SMI, vcpu);

Step2:
    kvm_vcpu_ioctl(cpu, KVM_RUN, 0)

                                call process_smi() if
                                kvm_check_request(KVM_REQ_SMI, vcpu) is
                                true, mark vcpu->arch.smi_pending = true;

The vcpu->arch.smi_pending will be set true in step2, unfortunately if
vcpu paused between step1 and step2, the kvm_run->immediate_exit will be
set and vcpu has to exit to Qemu immediately during step2 before mark
vcpu->arch.smi_pending true.
During VM migration, Qemu will get the smi pending status from KVM using
KVM_GET_VCPU_EVENTS ioctl at the downtime, then the smi pending status
will be lost.

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
Signed-off-by: Shengen Zhuang <zhuangshengen@huawei.com>
---
 arch/x86/kvm/x86.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12026845
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 87933C433DB
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 09:47:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3791522B2E
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 09:47:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388236AbhARJjc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 04:39:32 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41492 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388359AbhARJIy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Jan 2021 04:08:54 -0500
Received: from mail-pj1-x102c.google.com (mail-pj1-x102c.google.com
 [IPv6:2607:f8b0:4864:20::102c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B0658C061573;
        Mon, 18 Jan 2021 01:08:13 -0800 (PST)
Received: by mail-pj1-x102c.google.com with SMTP id l23so9371226pjg.1;
        Mon, 18 Jan 2021 01:08:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=oQRRXCmQGQuZCQYLuXtxMPDteVSg+sjt+B2CXlJY5uY=;
        b=mFLSEyB+WhWxpHiQ5SDX8AgkmO6t61ZxQLrGeseRTFKcpVG2KYbZOvC1IcKSb9UB8n
         FbsEINhEJ6SYW4NHfcFQdk2qC3jwlv9imhbzy+v2yhCaaN8k9lqJ+oxu4M8Y1Xrl9+Nd
         LAfYKUDdeeqRQ8u9/FIaMuHJBqXBGE79t56lFKYtluKT5RweAdMZHTUxYQedhejjDBnK
         vk9I8Bie++azRpZ9WBspDKbAcjLmhrabBfJ18dBpsOdmKzRgqdrwlbtoC7wZiWli79rL
         eC5Y4LuRFjsWKdlE+lTeeREMjoz58xz/D2EP8vc+nqY6Pm9gq5g6Wh8PXC7w8IWmPv5E
         oNMg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=oQRRXCmQGQuZCQYLuXtxMPDteVSg+sjt+B2CXlJY5uY=;
        b=FasCIC4z8+SXxWpaVb4otPe4+DHTIFXtcocfV2q+C71j26iped/0cODaVeUAgddU+e
         gooz/kDnkE6v8xH0Fz4Z4WcYA7nR1Wb2F6RK6r7411JPlasUcTUFwlsZITLgLauRM5rr
         8mOVVd/MBTxJjHpVfAkLLAyjgsO5/hLkgsFzXq7kqXndo00huLsu7WnKszESsr/Gb7dl
         PKTgFdXBygIlHVhX+tmobxjdYild0HMlayDEogQrs0F9+WwqxS8tRgabSag+CzRAkWyM
         +Y7mB+/3wC88J5e1ZhCGfIB4n5hjM9cxP3FMlLa+cnuvj/9V+l/F5rJ69FmRPtEE1+z1
         Lmcg==
X-Gm-Message-State: AOAM531erOsz0yc5RRvdRWUOhicGGA1Kjp8xRSJyu0h12u6rbZy5kLoa
        l3MQNf5HZ5BnMzICPIrH3pNlmQHUMHk=
X-Google-Smtp-Source: 
 ABdhPJxJBsHPSINp5FR+JCVHGdC/tIYhE5D4jiNCxl3I8JYQyucDZzbeiNFS3GArZSdv6WjL08yZfA==
X-Received: by 2002:a17:902:8a8a:b029:db:e003:4044 with SMTP id
 p10-20020a1709028a8ab02900dbe0034044mr25859233plo.19.1610960892926;
        Mon, 18 Jan 2021 01:08:12 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 s23sm15186928pgj.29.2021.01.18.01.08.09
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 18 Jan 2021 01:08:12 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v2] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
Date: Mon, 18 Jan 2021 17:07:53 +0800
Message-Id: <1610960877-3110-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The per-cpu vsyscall pvclock data pointer assigns either an element of the 
static array hv_clock_boot (#vCPU <= 64) or dynamically allocated memory 
hvclock_mem (vCPU > 64), the dynamically memory will not be allocated if 
kvmclock vsyscall is disabled, this can result in cpu hotpluged fails in 
kvmclock_setup_percpu() which returns -ENOMEM. This patch fixes it by not 
assigning vsyscall pvclock data pointer if kvmclock vdso_clock_mode is not 
VDSO_CLOCKMODE_PVCLOCK.

Fixes: 6a1cac56f4 ("x86/kvm: Use __bss_decrypted attribute in shared variables")
Reported-by: Zelin Deng <zelin.deng@linux.alibaba.com>
Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: stable@vger.kernel.org#v4.19-rc5+
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * add code comments

 arch/x86/kernel/kvmclock.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86/pmu: Fix UBSAN shift-out-of-bounds warning in intel_pmu_refresh()
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12026271
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B1022C433E0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:06:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75A38223E8
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:06:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731238AbhARDF4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 17 Jan 2021 22:05:56 -0500
Received: from mga05.intel.com ([192.55.52.43]:45162 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731147AbhARDFy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Jan 2021 22:05:54 -0500
IronPort-SDR: 
 KzMC1EBT+Shiac1PsXCwcfeCHSmSNUPa7gTWeajuBk2I9yL836enUMYSKbuIUS3uj4JYblPN/h
 P9gfNBwO5F+A==
X-IronPort-AV: E=McAfee;i="6000,8403,9867"; a="263556039"
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="263556039"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 19:04:08 -0800
IronPort-SDR: 
 2QFC9SFjxHtjPSyFEPzw1mF522hlQsr3r54tSaeChFAQ8611TZpql+9smSqfvxmLgircbAbIFL
 0NhhCrHfcKiw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="466222499"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga001.fm.intel.com with ESMTP; 17 Jan 2021 19:04:06 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: x86/pmu: Fix UBSAN shift-out-of-bounds warning in
 intel_pmu_refresh()
Date: Mon, 18 Jan 2021 10:58:00 +0800
Message-Id: <20210118025800.34620-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since we know vPMU will not work properly when (1) the guest bit_width(s)
of the [gp|fixed] counters are greater than the host ones, or (2) guest
requested architectural events exceeds the range supported by the host, so
we can setup a smaller left shift value and refresh the guest cpuid entry,
thus fixing the following UBSAN shift-out-of-bounds warning:

shift exponent 197 is too large for 64-bit type 'long long unsigned int'

Call Trace:
 __dump_stack lib/dump_stack.c:79 [inline]
 dump_stack+0x107/0x163 lib/dump_stack.c:120
 ubsan_epilogue+0xb/0x5a lib/ubsan.c:148
 __ubsan_handle_shift_out_of_bounds.cold+0xb1/0x181 lib/ubsan.c:395
 intel_pmu_refresh.cold+0x75/0x99 arch/x86/kvm/vmx/pmu_intel.c:348
 kvm_vcpu_after_set_cpuid+0x65a/0xf80 arch/x86/kvm/cpuid.c:177
 kvm_vcpu_ioctl_set_cpuid2+0x160/0x440 arch/x86/kvm/cpuid.c:308
 kvm_arch_vcpu_ioctl+0x11b6/0x2d70 arch/x86/kvm/x86.c:4709
 kvm_vcpu_ioctl+0x7b9/0xdb0 arch/x86/kvm/../../../virt/kvm/kvm_main.c:3386
 vfs_ioctl fs/ioctl.c:48 [inline]
 __do_sys_ioctl fs/ioctl.c:753 [inline]
 __se_sys_ioctl fs/ioctl.c:739 [inline]
 __x64_sys_ioctl+0x193/0x200 fs/ioctl.c:739
 do_syscall_64+0x2d/0x70 arch/x86/entry/common.c:46
 entry_SYSCALL_64_after_hwframe+0x44/0xa9

Reported-by: syzbot+ae488dc136a4cc6ba32b@syzkaller.appspotmail.com
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
v1->v2 Changelog:
- Add similar treatment for eax.split.mask_length (Sean)

 arch/x86/kvm/vmx/pmu_intel.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2] vfio/pci: Add support for opregion v2.0+
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 12026463
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4934DC433E0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 04:46:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24A37224B0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 04:46:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731452AbhAREqj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 17 Jan 2021 23:46:39 -0500
Received: from mga01.intel.com ([192.55.52.88]:8149 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730255AbhAREqf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Jan 2021 23:46:35 -0500
IronPort-SDR: 
 vk1rKmgDxCkOYownFZrjwh7/wwpU9gLaJItegkdz2dH6FGAVlRhdxqFceR7GItJ0Cfc2uqTAuC
 bA9Km5mZ7i6Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9867"; a="197450259"
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="197450259"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 20:45:54 -0800
IronPort-SDR: 
 2U6qZl/cfuHUmxeg0XNanDjty97TPf77gX62Si/NIw7L3m7bXMLOlA4qi9EzeySvB5Te39cN2U
 S9r2TyMXE5jg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="355056230"
Received: from cfl-host.sh.intel.com ([10.239.158.59])
  by fmsmga008.fm.intel.com with ESMTP; 17 Jan 2021 20:45:52 -0800
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Swee Yee Fonn <swee.yee.fonn@intel.com>
Subject: [PATCH v2] vfio/pci: Add support for opregion v2.0+
Date: Mon, 18 Jan 2021 20:38:34 +0800
Message-Id: <20210118123834.5991-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
In-Reply-To: <20201202171249.17083-1-fred.gao@intel.com>
References: <20201202171249.17083-1-fred.gao@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before opregion version 2.0 VBT data is stored in opregion mailbox #4,
However, When VBT data exceeds 6KB size and cannot be within mailbox #4
starting from opregion v2.0+, Extended VBT region, next to opregion, is
used to hold the VBT data, so the total size will be opregion size plus
extended VBT region size.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Signed-off-by: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci_igd.c | 59 +++++++++++++++++++++++++++++++++
 1 file changed, 59 insertions(+)

```
