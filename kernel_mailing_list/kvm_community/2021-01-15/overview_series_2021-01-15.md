#### [kvm-unit-tests PATCH v2 01/11] lib/x86: fix page.h to include the generic header
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12022541
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 897D0C433E9
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:43:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6950C221F7
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:43:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732919AbhAOMn1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:43:27 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34356 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388381AbhAOMnZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Jan 2021 07:43:25 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10FCYQ1g011718;
        Fri, 15 Jan 2021 07:37:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XMrSdkBO6H0bhPZj+2/Gi75A7sr3FfvZntzURITiK5I=;
 b=bRkXjY/OyDMhDquKHRG5/K4GMDINWNXzcia1Atqt+lipPGztoGoaFn95UrxTwsX4VeMa
 QEZY2lVJ0X7o7FFCC+jEjiQRRfULDqPG8jk+HFSImMWgyasH2T5hu9EPbr6UeqFWFqva
 aXSCr4yYd1mGuS67qYR4ZcIbfMmWEPtll9dYjQJ//BfmyRLpUuqVYH3BD2Oj15od0TCZ
 JfZDl2gmKa/lxoUmvoEL8y8doXhZSx1+PwjLozEfkZVmEHSMKLmqcuHNtgcmD8ykQeRM
 lNV+T1j9Fa0UZIL+Kc8VY9rpiPgH33SMcR0LE3qXak521OKBFroh1713lT1vyzJ3mrI9 Fw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 363aux0m31-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 07:37:37 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10FCavhb028309;
        Fri, 15 Jan 2021 07:37:36 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 363aux0m2a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 07:37:36 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10FC8Cmq014079;
        Fri, 15 Jan 2021 12:37:34 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 35ydrdf9nd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 12:37:34 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10FCbWW846137764
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 Jan 2021 12:37:32 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 29CABAE051;
        Fri, 15 Jan 2021 12:37:32 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B2AC3AE055;
        Fri, 15 Jan 2021 12:37:31 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.4.167])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 15 Jan 2021 12:37:31 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        pbonzini@redhat.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com, krish.sadhukhan@oracle.com
Subject: [kvm-unit-tests PATCH v2 01/11] lib/x86: fix page.h to include the
 generic header
Date: Fri, 15 Jan 2021 13:37:20 +0100
Message-Id: <20210115123730.381612-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210115123730.381612-1-imbrenda@linux.ibm.com>
References: <20210115123730.381612-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_07:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 clxscore=1015 suspectscore=0 spamscore=0 mlxlogscore=999
 impostorscore=0 priorityscore=1501 malwarescore=0 bulkscore=0 phishscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101150075
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bring x86 in line with the other architectures and include the generic header
at asm-generic/page.h .
This provides the macros PAGE_SHIFT, PAGE_SIZE, PAGE_MASK, virt_to_pfn, and
pfn_to_virt.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/x86/asm/page.h | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH] kvm: arm64: Properly align the end address of table walk
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12022087
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43713C433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:54:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB03023772
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:54:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730380AbhAOJyK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 04:54:10 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:11539 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725917AbhAOJyJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 04:54:09 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DHGgC2fHkzMKkq;
        Fri, 15 Jan 2021 17:52:07 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Fri, 15 Jan 2021 17:53:16 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Will Deacon <will@kernel.org>,
        Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH] kvm: arm64: Properly align the end address of table walk
Date: Fri, 15 Jan 2021 17:53:07 +0800
Message-ID: <20210115095307.12912-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When align the end address, ought to use its original value.

Fixes: b1e57de62cfb ("KVM: arm64: Add stand-alone page-table walker infrastructure")
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kvm/hyp/pgtable.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v16 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12022445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E1FBC4332E
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:21:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69EEF23884
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:21:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730410AbhAOMVJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:21:09 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:38938 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729635AbhAOMVG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 07:21:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1610713265; x=1642249265;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=EK/5efwN5ctponF7YeDfvp60Cq6LVz8yReJHQCaEMVs=;
  b=U9fSlhZjvQFXKsVqk82LB6qhtQszgS4IJXWvKUACxcXrz1dr5NJO5BB+
   DuejPKjtWishrZGlKzS8/DVR40j9CpSyMrHwWT7tFuBKxoWDLszijpwiU
   o31ewLv0CIv7/uRT8+uqfYKT8me2+JJUSXSZcpag/k172yY8xlhfAUtWa
   Tgb/AJLvxd59ANgCP00tVdH3mPzmTTqDNDK3HYrRzf9lknkUobn3e0BzO
   P412TCypPh9gn2z+ie9R3oY/YoywP2RmXBZ4rSI5bYbInOt8Ka+mqdqFz
   XCiJwxemXwhrsO3jrtQ+uMgxXrk2lVfu0AtylQobYEgyf+KWtujKPgiEa
   g==;
IronPort-SDR: 
 9zftEn3V3tzAh30fceNg3ZPLbO8BYYo29z/uA+UpDSkQBl3eOnnb0MqxRhp7c4pinX908c7aW6
 kdhlku42Lk5JbTp5fODcZSnXw5kgRfBm+kqAQ6QUOmX1JHvhYo2QPl2pMrW1pDcb1hcADkRL3D
 8f7TXq5upBZ9Xx0oFgMnQ+tB5KKHD3chT6wzKsvQ/XcgyVLnMy/uanA0ahLErovFrhU+6g1lJH
 bp0PyuJvCpPalW0bToZhnaSXlnN/Nd1c4eu5in2yRzmUMVvJTxKbYxIBQLFkFnlFlYqWBIxPnv
 jSM=
X-IronPort-AV: E=Sophos;i="5.79,349,1602518400";
   d="scan'208";a="157514087"
Received: from mail-bl2nam02lp2058.outbound.protection.outlook.com (HELO
 NAM02-BL2-obe.outbound.protection.outlook.com) ([104.47.38.58])
  by ob1.hgst.iphmx.com with ESMTP; 15 Jan 2021 20:19:20 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Icplgw49VxPjecKhiwrsZVv1GmwF8N5dYWmBx+3Qen3haLfbtwYw+TOCZaoDFvfqaKDJB8LwUdkKrlU4WRBDQPRnSqk4ImCnUWB1Jx/3VG/AzAFK7JxWJK4J3PKAJSO8QTSxdFnBisnLz2sR73Ae/lwiKEPQxUqnJkovn4ftW0BYT9E39BViJSao+XvPH6TOeQEJgXRmgT9KB3aCgJj/fTQGRPmEFO9LWGaBB3hvCoR+rx+Juo89dk2BSSSDHxxLkcDuiWWW5l3nDyPhfRca31/GQXEpcMuZZx+R1VU3/KY5ac1GdHhhHPkWcKp9bmcF+97jQcj1nnQuydhxvDHFnA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=irNFiSkJu25dlsZjIbFwjDJ9G5RJKyNh39vsd3T/W4hjmlssF+ehS5IWONW5DyJQt7ScEWQm7TPwaKjy102GR783h0bvEMqeOAYKFcLIX0UMemo1wxt+oguT17hAr+3ZgcscER1R7SxVaea+3EokxfyqUVlz0knf8iaG71wZwni2qxLlpchgRUsSKrnUNiErktjDShhsMch4LisNlEQrAF8WsXjwFzcDkRZPJldnPU7mWt6G5iKFxHosGWmlbUmb9ujEOVVwTegYimJIAr8wAFg7jyq3evCgw2GDXhq6mRFOuh0cnu8E2Cjb0YbGXR7KaC88Q5jQpwpqTZWk6dkdOQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=zAUvQg8zLdkUTSOg++apmAAblKjnikmW93XDwCXwWwZFZVVlI5tzDIdKgdNn4IK92dVXAqDIFKjedTRsXzZRGtv1LYkHrQHuLMfb0JIfa66tCpb99we74VsR0lrGZRqQh8SgacSy5/wfPHzl/lw/E71hmx1ELU7FcBgUOQyIAew=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB3769.namprd04.prod.outlook.com (2603:10b6:3:fc::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10; Fri, 15 Jan
 2021 12:19:20 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97%5]) with mapi id 15.20.3742.012; Fri, 15 Jan 2021
 12:19:20 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v16 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Fri, 15 Jan 2021 17:48:30 +0530
Message-Id: <20210115121846.114528-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210115121846.114528-1-anup.patel@wdc.com>
References: <20210115121846.114528-1-anup.patel@wdc.com>
X-Originating-IP: [122.167.152.18]
X-ClientProxiedBy: MAXPR0101CA0024.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:c::34) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.167.152.18) by
 MAXPR0101CA0024.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:c::34) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10 via Frontend
 Transport; Fri, 15 Jan 2021 12:19:15 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d573e2c9-f162-490a-24b7-08d8b94fc8d9
X-MS-TrafficTypeDiagnostic: DM5PR04MB3769:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB37692F49C79B995C68D715008DA70@DM5PR04MB3769.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ZiWRh2n7KzNb9GHMQupnEwe+heOb5YLQEcT9czc9s/5hmXVa2C4vTnXHhZC/jaVM/wcupl5PoUyZSb6RPun59RpaRDC/SH6/2HUpPeOBoQFV8iKpSg9tiNFNSSPDB+zuVws5lXt7UTlshnUREwFlgDkqe52bpBYbGx1U6o8DjN22ksztWzmEbKwFvmXMYOb4oFWR21unhvR2NMxUnG+XFcnh4DqNta2v6WX/D3npILA8PDE3mvWelUW9rb4IMytJgxIQ+w+JJhCBeBcq4EPLprhuKrwaNDIV1bTgXESRbXKCMeVmENGyyiwR26GlawD1aSrVVOUhTiKFY4cEZPidRKXdTsGtxJydHjJ2+pR12JCU95xYffBB5jI19la/ZUG77+bC4JWUALMpGpGMOyKcsw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(346002)(136003)(366004)(376002)(396003)(66476007)(6666004)(55016002)(7696005)(54906003)(66946007)(110136005)(956004)(5660300002)(2616005)(186003)(52116002)(44832011)(478600001)(66556008)(8936002)(26005)(86362001)(2906002)(83380400001)(7416002)(16526019)(8676002)(316002)(4326008)(36756003)(8886007)(1076003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 cnZXS1B9nNaHnETMZpPoSdTGA9Hssdga7OqayLZaF5SELN3cKw5L2kTYTQoBfMJfhucRBIh/JowKhouHPmMGxEq7nG/yvwBdf9TT/ZLApbt0GWmf01LNZzRDbNQcwaIDpKrC7Qicn8XlSV1ac733lFKA7ODlbEG3TYjkT9OvHbHIaAlP0TrY79cJTELvC/Lt1z5fy7+VnamrYBBW5tmb9URQvJkN6SUg8L5TDS25mTMHgSQJTNstOtI8CQ4MeWlQ+Q47v1xb8864njunUGSHI1NH14Iz90nMohzpBldoqKdgCYlXS0ZZrjq2QlGSLfOaJorLd+N+R83kKq25si0vAo5WxSDRAIb6mIsfR7eyny8wUc7zX4zyIqyzDiEmFRt8j0PlgJ2sS3nmVpmVNHOca9BqX6BWTq2sVHhW6MtokYLirY0Aaiaunrutk7/5Nx+3sn+lDL6ColirwcUscV9Fd0IbWDLNRXqZ46CCG6DP68407ybs0B1vPHsMyqniOsZzOrp28zUwcm7hKhRA7L5NDtW2istiLv/Ga3lztSnh4wuaYdz0x1MMj7eByJzAuGwkHpcOi3mUNFWMRbPTEW4XfRBke9A8smDGI9Ly0g2P3LlQQmh5ZA901nDC2QgQLWRcITuEuxksRGNasRdnggE7rNWDv96dX5sxGjPAci9IGgZ0pNv5KKjs//Nw9mOaYoBOvBCuv/gbVwBDgI+tUBcWgiZXUs1USYiN+2BhpEgKjKHTOV50J7IguX60CBdWC2Vb5SpDYmobfIxBWvGuxptV9HNbBSmoO/GEuoUNSCQAjDnxjyZuPoF+OXZznFpujsBPsJ9gE5AjsDOB8pWB5uvVTRzg38xgeCpRvovuPd7kx3u1kVvEaoHUPpzRSGVtTQde6EtGqBjJY3hFnI/HslR5JpceT2rkWNUAXkgKjhzVnhw0uEg6zeFqek3JQvSJFn4EExSVgv62ycK3G8yYWGOCjy5CohO877L4SelNBHy0vQQXb0297JCyiJoZDFJy6gS5
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d573e2c9-f162-490a-24b7-08d8b94fc8d9
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 12:19:20.0851
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 n2kwh1VwUBUZNtpvwodcZ65f6ngdxbQMm/u2F1rsii5QmOIZrRmeIn8pnZkFh/niU7ZZzcXDqxHtqFpNJaBR7A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB3769
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch extends asm/csr.h by adding RISC-V hypervisor extension
related defines.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/csr.h | 89 ++++++++++++++++++++++++++++++++++++
 1 file changed, 89 insertions(+)

```
#### [PATCH v6 1/8] update_headers: Sync-up ABI headers with Linux-5.11-rc3
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12022495
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9DD5CC433E9
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:23:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BF5D238E3
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 12:23:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731077AbhAOMXj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 07:23:39 -0500
Received: from esa2.hgst.iphmx.com ([68.232.143.124]:36065 "EHLO
        esa2.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729700AbhAOMXh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 07:23:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1610713916; x=1642249916;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=+g+pxIba3Xb1nZveSswid/KRiTRuNSZnso/mFQTNdPs=;
  b=Jn+q0MhSH2NLXy9eCygO29De8nnztwTtaX0HWgoGppiUH+4qGQaZIBa0
   N40/mzuS/utcZ71m7K8l2u1yn1UpnM2aHVhIf0nMNDM3b76fRb1NrIQyq
   pClhN5SKQ6PB4irEHaaT2uTyI7YeO/Af+c8Cuiez3ENKtVnr6IU1iaZfJ
   fKOefk41vKKGOqKQXgDVZKKB9Pna3Z5vYzZ55mZurL41xCHoNVb9FhxZj
   ayN5fqlxg4D+MHJvtqehPRVC7piJH0qyfbvAly5fTo/goTh4mtZ572lUy
   1sPc1YsNwK7PPMfTfYpCl958H3qByzuuuWEppJDZYmPdB6Wyj8q+gTm1G
   g==;
IronPort-SDR: 
 XgP1kyLLsE0WOd5ndwyGBhzh4TlQNOia0BR/pKGBiRUXtX9HHG5jySUVYVEfy7TXCkerW4Yych
 qbrcLZeQUNa407AtB27CRqZkhIX+15PhGDUH5sm0d8IA6zzr+nsmee23DC08KEJMgvh3gucVp8
 QQUxYiEwXaIXqVmI1ENnwY3aEsFTtVGn+xK0FrgeDKW+j1YfDiedW/ItDZDccBk/STEtRhbLpQ
 fFxCwmqJpdvvzok5YNHJgW0tBR1VPfSoWKEPMnyz6e7hv3c1lE6/d7uwwfxAOCaPotm0/FRF/V
 pW8=
X-IronPort-AV: E=Sophos;i="5.79,349,1602518400";
   d="scan'208";a="261441485"
Received: from mail-dm6nam12lp2171.outbound.protection.outlook.com (HELO
 NAM12-DM6-obe.outbound.protection.outlook.com) ([104.47.59.171])
  by ob1.hgst.iphmx.com with ESMTP; 15 Jan 2021 20:30:15 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nx2thz0QSgzqm4frQnokRpiN0fEI02k48A1N+Qu0QMbhrgGpsSt4GB9I7MrZ7qgmOrTY4lhyxQBG4Arn2kMuzvzstJjKRVeLB0J8FxF16pbxQ4y58JYxwxecci9NlavgGhT+0X8VbFkaxFB9w+gNphwrmj+TKGAC785yOWhbT1Pbo3HqYnqKGhBUO2IJK8maQrdXrfvCTXP1ihbG5Q8IUHjpHU9FtOlrAEBRl6d/VT0D6j3W84+rXC/NBGhbR2ajX7bni/Wsn/SZRLqtE88q4lU5jrVCMk6CCZi2BBATjOm2ojpbnXfMump1bvo5hC1+fPFW3KDAvR8eLcvpEdhf7A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Jh7FJSOyEO51lobgl6+cOKQmqToV0FjIolnysvKD2lI=;
 b=Vk9vyfkPpr2BYKOi4hc9zH6USgj/FAdC3+Gi12L/Nd4EFfuD8qQ+OL42a7Gd8I02fWYRBKa4q81h2vpgfudjy/CnI5E9gEsQ5FXcXWhcVv2um/Pip3u/RmEURnsaFTf+SeMYc3fG64/R8PgLb4T4Ac1WedgUH1deESR9wk5id57DJ/1c2v/zv+cRDydrN6tyYiMhd3LaJQ0bloFJeKV7Ko4aXrE7GAPCsVqKfOOyfBUdi5ik9hdLsEVmJRAmhrohY3/Qm30A4b7ppBxVUjHwo7TzrBZ//VzX8oFqY0OussQyoKyF9ca4EuZ4ali31lTXBeYcuXnuMAHQDUsN2B3GPg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Jh7FJSOyEO51lobgl6+cOKQmqToV0FjIolnysvKD2lI=;
 b=L9dMjOgHJEBenlrNM5V4GmuYCZCgt3qOKXbNqb+ed9cmCep+Y505rlKGKM9TbrIg8Hs8tbK59mXw0dW+mq8bA9jiyroF1pJVEquSmX0imb1Xx4GkeYQYONADSyiUMK8ZBJbdeHxun8jJTw7cJva2fXZuqYAMN+eQs0FeC8o1IAQ=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB4330.namprd04.prod.outlook.com (2603:10b6:5:a0::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6; Fri, 15 Jan
 2021 12:22:28 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::2513:b200:bdc8:b97%5]) with mapi id 15.20.3742.012; Fri, 15 Jan 2021
 12:22:28 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v6 1/8] update_headers: Sync-up ABI headers with
 Linux-5.11-rc3
Date: Fri, 15 Jan 2021 17:51:53 +0530
Message-Id: <20210115122200.114625-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210115122200.114625-1-anup.patel@wdc.com>
References: <20210115122200.114625-1-anup.patel@wdc.com>
X-Originating-IP: [122.167.152.18]
X-ClientProxiedBy: MA1PR0101CA0031.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:22::17) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.167.152.18) by
 MA1PR0101CA0031.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:22::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10 via Frontend
 Transport; Fri, 15 Jan 2021 12:22:25 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d2de1213-5f2a-4c7a-4e68-08d8b9503940
X-MS-TrafficTypeDiagnostic: DM6PR04MB4330:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB4330AF824FA6C4AAC5D8899E8DA70@DM6PR04MB4330.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:2150;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 sCydaAsbEjsXD3/adfK3KD7MvhArrLTpBbWIiPr4u5iHJDIiu+oaAErn83v2KKt3b1STjGlh2U5S/W2naAxjjBv0C73M+pVMStf0tdJVmYgOJNa23e6MCBENs+J+dTdpfYk/wc6KF8Qz5lIwETriPJxSsdZY+BPNJHuAMSqovCcn04jb1caaVelPDpLtgcgMSNKauOAIV/TRpCcb1YlJ6/XTpritGZSzBwYYoYKfPbNwuxI+ne2D9J+EXsnJUWCAYFUJkaHjvMjeb5k9brI2Q2gpX6zLX6kLF1JN/xY9+5YJJc9Iid4LnPGePpPM5noS/xC5LaJOosTUm7XDlglMW2YVGgf4xQmvC4ssFAk7lsduyXSx1ptVC1jzJDyPE0/D6JqWpTTMCQOOQE0JjEU1Lg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(346002)(39860400002)(376002)(366004)(396003)(66946007)(316002)(1076003)(66476007)(8936002)(186003)(66556008)(86362001)(16526019)(36756003)(6916009)(44832011)(6666004)(7696005)(4326008)(26005)(52116002)(30864003)(8676002)(2616005)(478600001)(2906002)(54906003)(956004)(8886007)(55016002)(83380400001)(5660300002);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 fPD+CmXk6X/cpyZdGmtj/f3QzawI4QYh2gfpvf6BkvC+XiNhTnRShE/EjZj8sbPrDUJEx9KzYmbROg12mig08VjIiLfpkcOSiK+nJ2dPULSCJ3T+24nChypDaOVrfZNCndgBf5SeXB50nMXQHUxxVxhRn/MWQeREAgkeIUBGjvQJRq1sAhTmPH64Wyb1k+Ec45kQDMPpFEN5yukyQrzWKN92K4dexJtV0QiTSKUSng8lpyeNeTLsbwuhoG79KGP0eHfxDUHfIPeSSVFzibJCQi1zKwog6Cxn9Pg6hckNDUhyYtTJPR0VXHsIzhWF2exJdYk3zOz7fYUlV9bFikKdxESIZzl+CpmRLaZT+HoZ8e1x45MK0GVuGaOInoBouKKqclY5MfjHKD7itfnPedMZSJaVU5/+W7rAFLSQxqXcp07njmWbT7OJTzBTIMxrSneN6M/Bi+RajFpHvTeAi9OFUYBxM9j7b1cEslD/P17omUAVQp6vtweG/hhIKwfYc+NPbc66KeksFxOgX/56j+AYnOmB7LBBIntg/WDajqWyi7Jx5NAgpWoYuj2V9OvSpBC52JMq3BHlG2IIHPsMbgslkXw9z840A/sG8qLC0uPHnryQERFLCXEpviu/rXKXHs2d4SdtOAYERXscj8qS5uGx0vMs1WxT5No0wzGBvQLX5geUBP0RtJNI6diWPn5x+nxCQX5Ypz9/9abGX0y/UhoDuoPBFIDEUCkrSTdMGaY3xV24QuS6yxXfayaW30ZMI+89+V0mQa9mOwVFkHtSZDpa6izQdiNIlj0cigpqLQpobDBSYMn20B3rCxDVwMY5v6NPmwYY2k+PCRzjmaU0e7FA3DX5R27+tMjW5sXyNLfGRjewp4ddBKzFFPJNyHqke9yooQkWJvCsJhwqgvoXI3LMnY3tGKsMIzWveTfcuROrmpT/MxMoWQEtouvcFrcaU87m05/Z/U9b7z3SefZCVQD0NJfhW7gtCCre1P1syNlf3kTxIwW1HE7Ckdyo8KBVmyFC
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d2de1213-5f2a-4c7a-4e68-08d8b9503940
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 12:22:28.8039
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 0ddaYrdyVboghlxT8/KGjAvJ7Kes2kPSVW9qfbFGMXCFYQOf+1McqTg+e/E7CjWbpQv8LV+198sLerWigfrl0A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB4330
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.11-rc3 so that RISC-V
specfic changes in include/linux/kvm.h are available.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch64/include/asm/kvm.h |  45 ++++++++-
 include/linux/kvm.h           | 182 ++++++++++++++++++++++++++++++++--
 powerpc/include/asm/kvm.h     |   8 ++
 x86/include/asm/kvm.h         |  43 +++++++-
 4 files changed, 265 insertions(+), 13 deletions(-)

```
#### [kvm-unit-tests PATCH] gitlab-ci.yml: Run test with KVM and macOS via cirrus-run
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 12024269
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1026C433E0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:32:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D9E520DD4
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:32:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727293AbhAOWbw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 17:31:52 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33147 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727257AbhAOWbv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Jan 2021 17:31:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610749825;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IeUvLT/gh534WCxJ77kQH0u+G3n/xrfvtouSuqL1Q5I=;
        b=igG9MrmljaPe7YsQHeI2IpbWS21AkYKVb1EBYYcB6YtnR5gB9O5+wkCVegeX9xhXKzLgI3
        2gf4HQlxQTqkLFnkixetHV8zNYrubT6riVzQ2DtmJdoDEfy+btOGYGxFAw2R1gdZTfFkgX
        xzcy3a2og7a3qaIN4UbnYpvQzHQ+q2w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-581-5ngi5WOAPi2P_yvLvNDw3Q-1; Fri, 15 Jan 2021 17:30:22 -0500
X-MC-Unique: 5ngi5WOAPi2P_yvLvNDw3Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4A3BF80A5C0
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 22:30:21 +0000 (UTC)
Received: from thuth.com (ovpn-112-32.ams2.redhat.com [10.36.112.32])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6E75C6B8DD;
        Fri, 15 Jan 2021 22:30:20 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH] gitlab-ci.yml: Run test with KVM and macOS via
 cirrus-run
Date: Fri, 15 Jan 2021 23:30:17 +0100
Message-Id: <20210115223017.271339-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since Travis changed their policy, we soon cannot use it for the
kvm-unit-tests anymore, thus we lose the CI testing with KVM enabled
and the compilation jobs on macOS. Fortunately there is an alternative:
Cirrus-CI also provides containers with KVM enabled and CI jobs with
macOS. Thanks to the so-call "cirrus-run" script, we can even start
the jobs from the gitlab-CI, so we get all the test coverage in the
gitlab-CI again. cirrus-run needs some configuration first, though.
Please refer to the description from libvirt for the details how to
set up your environment for these jobs:

 https://gitlab.com/libvirt/libvirt/-/blob/v7.0.0/ci/README.rst

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml                | 31 +++++++++++++++++
 ci/cirrus-ci-fedora.yml       | 65 +++++++++++++++++++++++++++++++++++
 ci/cirrus-ci-macos-i386.yml   | 36 +++++++++++++++++++
 ci/cirrus-ci-macos-x86-64.yml | 41 ++++++++++++++++++++++
 4 files changed, 173 insertions(+)
 create mode 100644 ci/cirrus-ci-fedora.yml
 create mode 100644 ci/cirrus-ci-macos-i386.yml
 create mode 100644 ci/cirrus-ci-macos-x86-64.yml

```
#### [PATCH 1/2] x86/apic: Export x2apic_mode for use by KVM in "warm" path
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12024229
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 99052C43381
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:05:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67AE7239FC
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 22:05:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727132AbhAOWEr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 17:04:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49696 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726059AbhAOWEq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 17:04:46 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A8545C061796
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 14:04:03 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id i20so8993903qvk.18
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 14:04:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=945mZt11W/e1Cpr0kux35fc/oPlYVUnDMXl7cGh3YTM=;
        b=Yr1kAU4CG074m4dxfzKdbDRb4kKVYmOtLuUvFV4BkhGqFcrk+mQDMyPPg5uboFJ3Am
         wsLXuIay1J8LcDKkxThYDs+tX/wrEnaCXYHI2XtodoBK8qftJCm97N0mNUrrY3hBaL3a
         la48DizDpshlWYMoedKHESMVL/q/JXWPGrhZw+Jg+k+QPzfg96oT0B85TtwjTJGW1rNC
         n5o8DEmkzot0v9Ikh7XVZuH6yJWEFyCW7D8lAbNj7Y7ydcwPUtVeQ5drOj04QtMExVuU
         KUST7RwIFuHGmsLYMpFxRZgRs6Zjt4C8bZUDu38neVfW+UUqr/Hi97D+myZidRsO9JK/
         NP0g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=945mZt11W/e1Cpr0kux35fc/oPlYVUnDMXl7cGh3YTM=;
        b=b9LcKsDep2VEztYbW+q5Km0j15VMD1eeqY1frRpnDtH47uQDEI+IdpzFibjha0MQJm
         5mntMaLcJpuAh3b0/H9VkE5wjUtoyQz80+X9fjKoqeBj7rvZzY9YLKP1n+fxCdVYohYL
         Nh5cLwiTh+Pu28aaT9noUbphkRLhX+XOA17uIjMC4BWpa1XoG0WNZ4amh1ck1ia+217/
         +0C190zd+sSyy4+7hAxT9RTHoV98uxiwKkJ6bZr1H0H3b4cWV9VBzyt1Pd75qEo8qtFd
         1kLjmg6b/X7C+JwilXHDdbkMDFD01EjvRBpnkWkXQuU9UPNp2ZNuqVhTLkRryAciDGHm
         /G+w==
X-Gm-Message-State: AOAM530bPjzSbN35cks6bK7wDk6zN/7G8lqQYm8xgpdwbX1FpIJS+b0A
        HZiMhXh7KF1bHiP88chjgZ6IG/1B+vE=
X-Google-Smtp-Source: 
 ABdhPJyt07jGMmHQFCoFeqGCZ1Bu0ZBh9pKPci86yZRNoZyB2kLRYs8TpCw2UxNarA98HdV3SjMy8aXFUys=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:ad4:4431:: with SMTP id
 e17mr13861250qvt.21.1610748242838;
 Fri, 15 Jan 2021 14:04:02 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 15 Jan 2021 14:03:53 -0800
In-Reply-To: <20210115220354.434807-1-seanjc@google.com>
Message-Id: <20210115220354.434807-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210115220354.434807-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 1/2] x86/apic: Export x2apic_mode for use by KVM in "warm"
 path
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, luferry <luferry@163.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export x2apic_mode so that KVM can query whether x2APIC is active
without having to incur the RDMSR in x2apic_enabled().  When Posted
Interrupts are in use for a guest with an assigned device, KVM ends up
checking for x2APIC at least once every time a vCPU halts.  KVM could
obviously snapshot x2apic_enabled() to avoid the RDMSR, but that's
rather silly given that x2apic_mode holds the exact info needed by KVM.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kernel/apic/apic.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH RFC 1/4] KVM: x86: Drop redundant KVM_MEM_SLOTS_NUM definition
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12022729
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1A325C433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 13:21:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE60C23359
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 13:21:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732913AbhAONVN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 08:21:13 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:55580 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731315AbhAONVN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 Jan 2021 08:21:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610716732;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=72IdiNGgGPIu/gnrc+hSZexB39ZbyEkwh9wEWdrVo7g=;
        b=L3Q3/tFIpNcXe0+LnsP4gAPvKr4B22mes/ERRioA7xEE6sE1FcsMLOCIju73VDx1RnPmOB
        lR5sDk/hc7rKfICIJuDjSnLbvSOeOG0/bRkmXPzJLnfFzg1zXcGmLLJ0ifeTAW9NDzLSmG
        94awpr06fO+y5eK/AI50zgpcmX+Y8e8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-162-L0lTHd_oPn-vYgQajabVIQ-1; Fri, 15 Jan 2021 08:18:50 -0500
X-MC-Unique: L0lTHd_oPn-vYgQajabVIQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 75615190A7A3;
        Fri, 15 Jan 2021 13:18:49 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.14])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D11AA60CCE;
        Fri, 15 Jan 2021 13:18:47 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH RFC 1/4] KVM: x86: Drop redundant KVM_MEM_SLOTS_NUM definition
Date: Fri, 15 Jan 2021 14:18:41 +0100
Message-Id: <20210115131844.468982-2-vkuznets@redhat.com>
In-Reply-To: <20210115131844.468982-1-vkuznets@redhat.com>
References: <20210115131844.468982-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_MEM_SLOTS_NUM is already defined in include/linux/kvm_host.h the
exact same way.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/kvm_host.h | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] KVM: x86/mmu: Remove the defunct update_pte() paging hookFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12021167
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 111EBC433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 00:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D337823B03
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 00:41:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731390AbhAOAlh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 19:41:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55812 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726899AbhAOAlg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 19:41:36 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2DC95C061757
        for <kvm@vger.kernel.org>; Thu, 14 Jan 2021 16:40:56 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id k126so6165917qkf.8
        for <kvm@vger.kernel.org>; Thu, 14 Jan 2021 16:40:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=t8c/Zi1/dJ4uhKjMSCSNdZwekdvteSeGdebcaDLlZ84=;
        b=J08j0qDe02915zC2wJ7Mk1g1vjFzfb/8xM6Fz97phDYXlPIre1A1e3jYGEL3MnRRt1
         cYAXkemNWK3RKolge13RoBcjyl22LWNXyXEi0/fffxt/0v4G7sn8sfoI5BD/s22LcQc9
         DgnEFP9ey8SYkb/GkPHKoLiF0L+WnPLMPWfsMygtYdjuy8zvKsNk2UEa8kFOK8OMEqAC
         MjGyk1/CLfjoZbu3LOTkGCYdNM2OsaOjdTrDeNC7XCU7riXkdWlOEc4yrywwFZEk1gpp
         DFh5I5T86nO1ZRbj5z/YX2mIi/UqsGdmWbbWa/9GSYG2sZdkw4cHLFOF0EtI6YtazJZY
         EUpw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=t8c/Zi1/dJ4uhKjMSCSNdZwekdvteSeGdebcaDLlZ84=;
        b=WweKKeO74dOUeSAbR/wgtSadyWuEw705YMkmwoPEefNAvSyJtyi9LYIVQ1Ga23WpMq
         nArpVXYFy6RtcBSVrIlAtTt6OJPZ1Qg/HMqhYn8Yo5Warz4ipP6ZdxRhB9BRCjWQmRZ4
         8krIsVZvs966rmpy+yuIi2pZIu0M9abKbGpEHdxEd2U5nojnR6fQSu5VqBa5FirHhtpi
         wSepPNatxtvO4P7mnhUBoUIozqv6WD9z0pYH5KshY6+jzu3Qo1e1Dp6xg+Ls/diVQGR8
         0OqlRGdEGjM6nrFM6z9pYuGOj02PRRb+/SCXIWuCJJHZZk+V5yrUZ79BWkI2M/MCvjr/
         lXvQ==
X-Gm-Message-State: AOAM532pgXinjYbphT0bGttPkvLIFkiCr55K+eier61OYPx32zeL5MJa
        xoD6Aguuy2q1UP1Jv6sA8wnjilhZRY0=
X-Google-Smtp-Source: 
 ABdhPJzxCxZXjHhtcvLr1Kf9erN9OuaIBz0HqpYidtZRJoouWRl1ju7FoN0eK6DismJIkfKcznYgWNNK+Gk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:ad4:434e:: with SMTP id
 q14mr9828287qvs.15.1610671255318;
 Thu, 14 Jan 2021 16:40:55 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 14 Jan 2021 16:40:51 -0800
Message-Id: <20210115004051.4099250-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH] KVM: x86/mmu: Remove the defunct update_pte() paging hook
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Yu Zhang <yu.c.zhang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the update_pte() shadow paging logic, which was obsoleted by
commit 4731d4c7a077 ("KVM: MMU: out of sync shadow core"), but never
removed.  As pointed out by Yu, KVM never write protects leaf page
tables for the purposes of shadow paging, and instead marks their
associated shadow page as unsync so that the guest can write PTEs at
will.

The update_pte() path, which predates the unsync logic, optimizes COW
scenarios by refreshing leaf SPTEs when they are written, as opposed to
zapping the SPTE, restarting the guest, and installing the new SPTE on
the subsequent fault.  Since KVM no longer write-protects leaf page
tables, update_pte() is unreachable and can be dropped.

Reported-by: Yu Zhang <yu.c.zhang@intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/include/asm/kvm_host.h |  3 --
 arch/x86/kvm/mmu/mmu.c          | 49 ++-------------------------------
 arch/x86/kvm/x86.c              |  1 -
 3 files changed, 2 insertions(+), 51 deletions(-)

```
#### [PATCH] use pr_warn_ratelimited() for vq_err()
##### From: John Levon <john.levon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Levon <john.levon@nutanix.com>
X-Patchwork-Id: 12023787
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3B789C433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 18:22:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13E7D23A58
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 18:22:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733084AbhAOSWL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 13:22:11 -0500
Received: from 88-98-93-30.dsl.in-addr.zen.co.uk ([88.98.93.30]:34960 "EHLO
        sent" rhost-flags-OK-FAIL-OK-FAIL) by vger.kernel.org with ESMTP
        id S1733294AbhAOSWJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 13:22:09 -0500
X-Greylist: delayed 2553 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 15 Jan 2021 13:22:09 EST
Received: from jlevon by sent with local (Exim 4.93)
        (envelope-from <john.levon@nutanix.com>)
        id 1l0T3g-00B1tx-IL; Fri, 15 Jan 2021 17:38:48 +0000
From: John Levon <john.levon@nutanix.com>
To: levon@movementarian.org, virtualization@lists.linux-foundation.org,
        kvm@vger.kernel.org, jasowang@redhat.com, mst@redhat.com
Cc: John Levon <john.levon@nutanix.com>
Subject: [PATCH] use pr_warn_ratelimited() for vq_err()
Date: Fri, 15 Jan 2021 17:37:41 +0000
Message-Id: <20210115173741.2628737-1-john.levon@nutanix.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vq_err() is used to report various failure states in vhost code, but by
default uses pr_debug(), and as a result doesn't record anything unless
enabled via dynamic debug. We'll change this so we get something recorded
in the log in these failure cases. Guest VMs (and userspace) can trigger
some of these messages, so we want to use the pr_warn_ratelimited()
variant.

Signed-off-by: John Levon <john.levon@nutanix.com>
---
 drivers/vhost/vhost.h | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/3] KVM: X86: append vmx/svm prefix to additional kvm_x86_ops functions
##### From: Jason Baron <jbaron@akamai.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Baron <jbaron@akamai.com>
X-Patchwork-Id: 12021303
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 905B7C433E9
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 03:31:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6927723AF8
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 03:31:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732573AbhAODbd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 22:31:33 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35740 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732533AbhAODbb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 22:31:31 -0500
Received: from mx0b-00190b01.pphosted.com (mx0b-00190b01.pphosted.com
 [IPv6:2620:100:9005:57f::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 51302C0613D6;
        Thu, 14 Jan 2021 19:30:44 -0800 (PST)
Received: from pps.filterd (m0050102.ppops.net [127.0.0.1])
        by m0050102.ppops.net-00190b01. (8.16.0.43/8.16.0.43) with SMTP id
 10F3QHta005349;
        Fri, 15 Jan 2021 03:30:17 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=akamai.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : in-reply-to :
 references; s=jan2016.eng;
 bh=y8x4y10ECVtbx/PyMPHnnjIxYNDK2d8dVeViV55dh3A=;
 b=YB89oQLuWmJirQ0zKeq1Ouvy4bxdbiTqofL02R2MMplFoKDl6rv50cHC8hvQpbBAYJDq
 8Zi4JkDbtzAA07jj8WUssBr5Wems2RM2sp2IH9cUUTxeYRITTm6RfeZ+w4fsK2x09MNI
 Gx1Szp5NQvYUB/2QsRgOeKK/M3HtzADB9Ku5L56cHA412gL5rcuk3XatgZOsInlbcF3C
 nLZK6Z/Z0UODldb+Y3puOeZK8KbdA+NmKQrKdlFK1wIln3nt58UtScbK8n+lh/mTiqFi
 X9oS79h+jzYhoaqTNe8bTNlsvVSbSsSzheQS7eeffOUu+fhnGrAU7MMk/F9UR+64GDIc GA==
Received: from prod-mail-ppoint2 (prod-mail-ppoint2.akamai.com [184.51.33.19]
 (may be forged))
        by m0050102.ppops.net-00190b01. with ESMTP id 35yq24wqen-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 Jan 2021 03:30:17 +0000
Received: from pps.filterd (prod-mail-ppoint2.akamai.com [127.0.0.1])
        by prod-mail-ppoint2.akamai.com (8.16.0.43/8.16.0.43) with SMTP id
 10F3Pr6W014547;
        Thu, 14 Jan 2021 22:30:14 -0500
Received: from prod-mail-relay10.akamai.com ([172.27.118.251])
        by prod-mail-ppoint2.akamai.com with ESMTP id 35y8q2cney-1;
        Thu, 14 Jan 2021 22:30:14 -0500
Received: from bos-lpjec.145bw.corp.akamai.com
 (bos-lpjec.145bw.corp.akamai.com [172.28.3.71])
        by prod-mail-relay10.akamai.com (Postfix) with ESMTP id B1A0E4069E;
        Fri, 15 Jan 2021 03:30:14 +0000 (GMT)
From: Jason Baron <jbaron@akamai.com>
To: pbonzini@redhat.com, seanjc@google.com
Cc: kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Peter Zijlstra <peterz@infradead.org>,
        Andrea Arcangeli <aarcange@redhat.com>
Subject: [PATCH v2 1/3] KVM: X86: append vmx/svm prefix to additional
 kvm_x86_ops functions
Date: Thu, 14 Jan 2021 22:27:54 -0500
Message-Id: 
 <ed594696f8e2c2b2bfc747504cee9bbb2a269300.1610680941.git.jbaron@akamai.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <cover.1610680941.git.jbaron@akamai.com>
References: <cover.1610680941.git.jbaron@akamai.com>
In-Reply-To: <cover.1610680941.git.jbaron@akamai.com>
References: <cover.1610680941.git.jbaron@akamai.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_01:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=831
 malwarescore=0 spamscore=0 phishscore=0 bulkscore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101150015
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-15_01:2021-01-15,2021-01-15 signatures=0
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 priorityscore=1501
 mlxscore=0 clxscore=1015 lowpriorityscore=0 malwarescore=0 bulkscore=0
 mlxlogscore=786 spamscore=0 suspectscore=0 impostorscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101150015
X-Agari-Authentication-Results: mx.akamai.com;
 spf=${SPFResult} (sender IP is 184.51.33.19)
 smtp.mailfrom=jbaron@akamai.com smtp.helo=prod-mail-ppoint2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch introduces macros in preparation for simplifying the
definition for vmx_x86_ops and svm_x86_ops. Making the naming more uniform
expands the coverage of the macros. Add vmx/svm prefix to the following
functions: update_exception_bitmap(), enable_nmi_window(),
enable_irq_window(), update_cr8_intercept and enable_smi_window().

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Signed-off-by: Jason Baron <jbaron@akamai.com>
---
 arch/x86/kvm/svm/svm.c    | 20 ++++++++++----------
 arch/x86/kvm/vmx/nested.c |  2 +-
 arch/x86/kvm/vmx/vmx.c    | 30 +++++++++++++++---------------
 arch/x86/kvm/vmx/vmx.h    |  2 +-
 4 files changed, 27 insertions(+), 27 deletions(-)

```
#### [PATCH v2 1/2] vfio/iommu_type1: Populate full dirty when detach non-pinned group
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12022009
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 072DFC433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:28:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7F6C2343B
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 09:28:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730707AbhAOJ2C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 04:28:02 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:11536 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730633AbhAOJ16 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 04:27:58 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DHG4z6Q6rzMKkp;
        Fri, 15 Jan 2021 17:25:55 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.498.0; Fri, 15 Jan 2021 17:27:06 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH v2 1/2] vfio/iommu_type1: Populate full dirty when detach
 non-pinned group
Date: Fri, 15 Jan 2021 17:26:42 +0800
Message-ID: <20210115092643.728-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210115092643.728-1-zhukeqian1@huawei.com>
References: <20210115092643.728-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a group with non-pinned-page dirty scope is detached with dirty
logging enabled, we should fully populate the dirty bitmaps at the
time it's removed since we don't know the extent of its previous DMA,
nor will the group be present to trigger the full bitmap when the user
retrieves the dirty bitmap.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty pages tracking")
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 18 +++++++++++++++++-
 1 file changed, 17 insertions(+), 1 deletion(-)

```
#### [RESEND PATCH v2 1/2] vfio/iommu_type1: Populate full dirty when detach non-pinned group
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12022155
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7202FC433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 10:15:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E4B62371F
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 10:15:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730801AbhAOKOq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 05:14:46 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:11021 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728199AbhAOKOf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 05:14:35 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DHH743Qz6zj88D;
        Fri, 15 Jan 2021 18:12:48 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Fri, 15 Jan 2021 18:13:41 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [RESEND PATCH v2 1/2] vfio/iommu_type1: Populate full dirty when
 detach non-pinned group
Date: Fri, 15 Jan 2021 18:13:20 +0800
Message-ID: <20210115101321.12084-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210115101321.12084-1-zhukeqian1@huawei.com>
References: <20210115101321.12084-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a group with non-pinned-page dirty scope is detached with dirty
logging enabled, we should fully populate the dirty bitmaps at the
time it's removed since we don't know the extent of its previous DMA,
nor will the group be present to trigger the full bitmap when the user
retrieves the dirty bitmap.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty pages tracking")
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [RFC PATCH v2 01/13] af_vsock: implement 'vsock_wait_data()'.
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12021489
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D6126C433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 05:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9CFEE239FD
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 05:41:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733130AbhAOFl2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 00:41:28 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:46069 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732057AbhAOFl0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 00:41:26 -0500
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id A181D52126E;
        Fri, 15 Jan 2021 08:40:42 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1610689242;
        bh=4bfGyjv63LiF8F91BaWRSmB0D65pfAEqkn1LSpcEoU4=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=PibPcZ7WSs9S7jZeaaOsLystdDUMvldTTF4cWESfJB/JHBa5Xy3xw5EOEvDL+0Qk+
         XEHfbUlAfS5+W7A69/NON+k4WRB1bX2RDurOjruW7MLh1cU8qK6QJ9sEj3Tmw7jYn4
         KbJZevBcYZcJryGWT8GFFTNSxR6SrF3yQbinf6YU=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 2E35B52122C;
        Fri, 15 Jan 2021 08:40:42 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.129) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Fri, 15
 Jan 2021 08:40:41 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Jeff Vander Stoep <jeffv@google.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v2 01/13] af_vsock: implement 'vsock_wait_data()'.
Date: Fri, 15 Jan 2021 08:40:25 +0300
Message-ID: <20210115054028.1455574-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210115053553.1454517-1-arseny.krasnov@kaspersky.com>
References: <20210115053553.1454517-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.68.129]
X-ClientProxiedBy: hqmailmbx1.avp.ru (10.64.67.241) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 01/15/2021 05:18:27
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 161159 [Jan 15 2021]
X-KSE-AntiSpam-Info: LuaCore: 420 420 0b339e70b2b1bb108f53ec9b40aa316bba18ceea
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 arseniy-pc.avp.ru:7.1.1;kaspersky.com:7.1.1;127.0.0.199:7.1.2;d41d8cd98f00b204e9800998ecf8427e.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 01/15/2021 05:21:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 15.01.2021 2:12:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/01/15 05:03:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/01/15 02:12:00 #16041563
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds 'vsock_wait_data()' function which is called from user's read
syscall and waits until new socket data is arrived. It was based on code
from stream dequeue logic and moved to separate function because it will
be called both from SOCK_STREAM and SOCK_SEQPACKET receive loops.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
---
 net/vmw_vsock/af_vsock.c | 47 ++++++++++++++++++++++++++++++++++++++++
 1 file changed, 47 insertions(+)

```
#### [PATCH v3 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL featureFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 12023399
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B9951C433E6
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 17:22:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88EA8239D0
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 17:22:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731151AbhAORWa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 12:22:30 -0500
Received: from mail-bn8nam11on2054.outbound.protection.outlook.com
 ([40.107.236.54]:28768
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729599AbhAORW2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 12:22:28 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=CwmjpScehQiq2MnDuB3Sx3JC+sjT8Ui0SH7Ke17191gb8ECebA1V8tDk1AzgyPbQnBWM+PAYGBZqINz5DNitd96Qv6n/YD/f3mL5YWT8xM7n32Vl0KPg2R2vMD6osjangg/5DkEkiGLyhyRAkXT6DUiNty/ZDCZP9qLxjhdmcgrwWif08zZvwqfo9SRD9hFpMK+UOyBosXeX631ZwyhTGDsCoEe88b1aHPsaTWxu5dn9RxSYZpXAx7MB/jqDFa3qwVB3tz4aW8DGHe7MyjhSn3tKHVvQe7v42h8FndXRL5zZSrYQDJi3wSTtKAiGlHaPTMXDYMThbCvTXZufnbrNHw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CF4J1hbbttjCvzB0KcY0I9jxXx45BP3e7FK7pX8dQ8Q=;
 b=b4lTpWAT9ltXZxX8d5Ytp96x3tYxMWcmmHcDGujcGDX6KfRFsQiQkHwxAejHFgIbqTtL1dWd7GtjVsFMcUr8iNYp4ggTsJmb41yKtFvZnl9FHFoCQDzAcqvxMuVU4qnb6lStr9+Kq+Re3YoeyO4QWIAPIot8CB5ZicMOoEh7mxerb/Ep0kP/R6l2N1ISeiVP2zT4/oXDyHKu6r76WZ87vCzTjMgVm85WWqMdDgbfWz9Kg+gBqR/AxJI1AQpXrdidgsYQYXRMH0/NRxwN7/BojB1uIKI1kFT/+BeQ55T38bPfnOi6l60UmZqNbnULDLVg0gU2g/zTy0u6vB9z/eSLqQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CF4J1hbbttjCvzB0KcY0I9jxXx45BP3e7FK7pX8dQ8Q=;
 b=HyhYPihc5ipyZFIaFUpBumFNu34lTt1aMLJXQDA9VJ/lQ4BjukLKvDU4INRRvTGAtiRXfi8zLKk+zWhRtew79QwFhAYRwsYwcDnrrhDhtTi+UJHV+eRR507SbI1n+9mAjhPPJwWglteJq+aM6km8z0oMaVoefOe65MBLXHJoDFs=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB2736.namprd12.prod.outlook.com (2603:10b6:805:75::30) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.8; Fri, 15 Jan
 2021 17:21:35 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::8c0e:9a64:673b:4fff%5]) with mapi id 15.20.3763.010; Fri, 15 Jan 2021
 17:21:35 +0000
Subject: [PATCH v3 1/2] x86/cpufeatures: Add the Virtual SPEC_CTRL feature
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
Date: Fri, 15 Jan 2021 11:21:33 -0600
Message-ID: <161073129332.13848.9112749469874197137.stgit@bmoger-ubuntu>
In-Reply-To: <161073115461.13848.18035972823733547803.stgit@bmoger-ubuntu>
References: <161073115461.13848.18035972823733547803.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0136.namprd11.prod.outlook.com
 (2603:10b6:806:131::21) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SA0PR11CA0136.namprd11.prod.outlook.com (2603:10b6:806:131::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.11 via Frontend
 Transport; Fri, 15 Jan 2021 17:21:33 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 7af23dba-4bfc-48bf-942c-08d8b97a01f7
X-MS-TrafficTypeDiagnostic: SN6PR12MB2736:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2736FC400EE3868F1952437995A70@SN6PR12MB2736.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1388;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 cAQUXRplne8pWQ8X932D3ndcMZM8RVToZUKKpM7FZsEx4RRh+glED85Ts8pXj3EW3GJ348zICpqNrbOjUC0XZxaguWyW9/UTZ/WQmWqcTCded1VE3KeHcm06ywT6Ensya8YeIRRMTD/i28imLA26YX3HqZlwtCl95hTm574+04rmw3CNYlah03bzu6Eiy9v2tDrXFqcxs+g9SPwLMMDDE9jet4TKKCu6p8Rluebo0LGU32Ii5IZCsszktZFSBWF/YTm2dKkAEeXntZCYQ9FdBCvppTvDbN5+Pksa2tl+nM/HDd+EPmQvNmc3SGCjz4MopuZUNgUc/oUIJO4h1O7bTgA/OcZn5hZB7rFshiYXIlLuraqIWMwV1kJv4GEqLa3TTiC1lwZ9eIaleWD2Lv5nZQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(346002)(39860400002)(366004)(136003)(376002)(396003)(956004)(4326008)(316002)(5660300002)(86362001)(8676002)(44832011)(478600001)(8936002)(16576012)(9686003)(6486002)(7416002)(66476007)(26005)(16526019)(66946007)(186003)(52116002)(33716001)(66556008)(2906002)(103116003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?r5RIQ4N52GDdQlGN1ZpYFCpjDdErbQ?=
	=?utf-8?q?X83aYr8Flg0gNtt4ebNh0C6Tu/Hr/C1pne/2rJl8/3E9zLhIboOtE18425LlRrba4?=
	=?utf-8?q?7fGnMGMWouDSD8Ycph5KoW4JRgUgUBzvV8Ac7PyGAFfsv81kVLvzNLScfvDISY/rD?=
	=?utf-8?q?dCjvBaI3wbe+RA2W3HYwdvat7kfIevMSJyiEXSTB51lrMQSFQi9kpCV2watTJ39Y6?=
	=?utf-8?q?4O0bOTycO9hwCXTB4U21yHI/+8LJivNqXC/917KHds21i6m7SxNFihhTT3Sc26zcF?=
	=?utf-8?q?A9VRdP9g95Wii9f2Mt9UIKFUjR+tPA5mtybrVT6Pv+2xlVYviDaF4ceY1E2Ko2tpI?=
	=?utf-8?q?cud0Z0t+VWgL4LgaE8qj5RZ86h2XpAbn1lU+xB4VqGHg4cqa5vQfsIiWhxrLjYaTc?=
	=?utf-8?q?aUFiUGLKj596mSauQurPK0kw+5FMLTHdk2wNXXeYgRbe0OZC/3bTkazRkH4gEWl/W?=
	=?utf-8?q?CAzr39fYowGzzU5Sv7JLyDmINKVq1+W4YNgBAOqryS8jyH4LsSNqEc+lRV1e7ldwu?=
	=?utf-8?q?pAagHLd8gS/1PonLKJveu3GboF/WG9MV1z8tgFd20HA15VPA5cDaGRCHDY4wId7S/?=
	=?utf-8?q?Hz757P1vAp+RSx5wo4UXLGQGyWgYDbm+sntq1+gXr4KmGlw4MwHUl4o25AipVYqjh?=
	=?utf-8?q?Jb5qegquCVfe2QMv5GBaFf2RPq0D5QUEekzxGCUhDMd21bFYeiZzqObct4dRQa15y?=
	=?utf-8?q?P7nQmc3o69QeL3OV26psnEj4cUPJCPjSadELuXX9xyKjr0MSuat5j6pwOy/IojuT7?=
	=?utf-8?q?Lzttjql49Y/+7Ip5PN6SghAoAS2BHLeuxap1wOGgsF8MSgwP7skmDGTR9nbL1dGs/?=
	=?utf-8?q?zNCDoFbYaPwo7U8hm7qFZGXTCrwIC6JJcTxwn891QRZCmxXbK6GbPZqioTDwylkZn?=
	=?utf-8?q?dhkI+kCIPs1lC+CFzRc82cOTWZ4mlmPYepjK6hGxoZmC7AhHjVntfuLj6v2nzb0?=
	=?utf-8?q?=3D?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7af23dba-4bfc-48bf-942c-08d8b97a01f7
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2021 17:21:35.0302
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 EuKQjiAa0tXpvAENDcNBAN6Z9RsYxmBNpjJ3Zrd4KOZq6pvVvIiWJZc0JEBj6t4W
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2736
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
