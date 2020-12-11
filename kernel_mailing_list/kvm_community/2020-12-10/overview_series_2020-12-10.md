#### [GIT PULL 1/4] KVM: s390: Add memcg accounting to KVM allocations
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11964929
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6210FC0018C
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 14:27:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BEA423DE5
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 14:27:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390042AbgLJO05 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 09:26:57 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:20474 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730742AbgLJO04 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Dec 2020 09:26:56 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BAE28wt151406;
        Thu, 10 Dec 2020 09:26:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=R6J7B3mgx+W41RaQLW/eiYgywm//wVZlLAVZLDfjaH4=;
 b=RXMdnAJY6xsr82NfqrJ+fH74XxzSNnn96Kw+eRel5mX9jnV2QMNgAXu29MDzuaZEy69U
 pcTioqb/IyFrJWmmGFTY3EGloF5Hfwz48/sgwnccQdTq2xpEE0rTyh0kGDsguZwUkwQR
 g+m5bVzn/A+jead0SMPvOn6waE8eXSN8ZPQPBY0E7CQzbQIbIQRorToCuZFC6xL7wAlB
 f2rhrDcc6tjswRDj3s2bawq6juLkRLCSYCUHKKg4tpfmzIamXBcrvnh7ZuEM16gCNZcr
 OPXGUmrJ1eln2FKIX66/HvsK9SNV0k0REpPGQg1X5tVZGdjWqX1+yqLHY11ffYd/WXuq JA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35bjvbwe1s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Dec 2020 09:26:07 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BAE2i29157949;
        Thu, 10 Dec 2020 09:26:06 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35bjvbwe0v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Dec 2020 09:26:06 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BAEIOPP025187;
        Thu, 10 Dec 2020 14:26:04 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 3581u8rnu5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 10 Dec 2020 14:26:04 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BAEQ1f122675750
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Dec 2020 14:26:01 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4BEE4AE064;
        Thu, 10 Dec 2020 14:26:01 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2D8B6AE063;
        Thu, 10 Dec 2020 14:26:01 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 10 Dec 2020 14:26:01 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id DCCEBE0450; Thu, 10 Dec 2020 15:26:00 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Collin Walling <walling@linux.ibm.com>
Subject: [GIT PULL 1/4] KVM: s390: Add memcg accounting to KVM allocations
Date: Thu, 10 Dec 2020 15:25:56 +0100
Message-Id: <20201210142600.6771-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201210142600.6771-1-borntraeger@de.ibm.com>
References: <20201210142600.6771-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-10_05:2020-12-09,2020-12-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=2 malwarescore=0 clxscore=1015 adultscore=0 phishscore=0
 mlxlogscore=999 bulkscore=0 priorityscore=1501 mlxscore=0 impostorscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012100084
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Almost all kvm allocations in the s390x KVM code can be attributed to
the process that triggers the allocation (in other words, no global
allocation for other guests). This will help the memcg controller to
make the right decisions.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/guestdbg.c  |  8 ++++----
 arch/s390/kvm/intercept.c |  2 +-
 arch/s390/kvm/interrupt.c | 10 +++++-----
 arch/s390/kvm/kvm-s390.c  | 20 ++++++++++----------
 arch/s390/kvm/priv.c      |  4 ++--
 arch/s390/kvm/pv.c        |  6 +++---
 arch/s390/kvm/vsie.c      |  4 ++--
 7 files changed, 27 insertions(+), 27 deletions(-)

```
#### [PATCH v3 01/66] arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11965579
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 01470C2BB40
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 16:43:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BACEF2388B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 16:43:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392182AbgLJQBX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 11:01:23 -0500
Received: from mail.kernel.org ([198.145.29.99]:59866 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2392173AbgLJQBM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 11:01:12 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2E29C23D56;
        Thu, 10 Dec 2020 16:00:31 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1knOMm-0008Di-Ny; Thu, 10 Dec 2020 16:00:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, Jintack Lim <jintack.lim@linaro.org>
Subject: [PATCH v3 01/66] arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
Date: Thu, 10 Dec 2020 15:58:57 +0000
Message-Id: <20201210160002.1407373-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201210160002.1407373-1-maz@kernel.org>
References: <20201210160002.1407373-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, jintack@cs.columbia.edu, alexandru.elisei@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, jintack.lim@linaro.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jintack Lim <jintack.lim@linaro.org>

Add a new ARM64_HAS_NESTED_VIRT feature to indicate that the
CPU has the ARMv8.3 nested virtualization capability.

This will be used to support nested virtualization in KVM.

Signed-off-by: Jintack Lim <jintack.lim@linaro.org>
Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 .../admin-guide/kernel-parameters.txt         |  4 +++
 arch/arm64/include/asm/cpucaps.h              |  1 +
 arch/arm64/kernel/cpufeature.c                | 25 +++++++++++++++++++
 3 files changed, 30 insertions(+)

```
#### [PATCH] KVM: SVM: use vmsave/vmload for saving/restoring additional host state
##### From: Michael Roth <michael.roth@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 11965825
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 63977C433FE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:55:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C7FF23E23
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:55:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392925AbgLJRxK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 12:53:10 -0500
Received: from mail-bn7nam10hn2221.outbound.protection.outlook.com
 ([52.100.155.221]:19105
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392889AbgLJRxE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 12:53:04 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=g+ViLrTQvH2Xp7wVp+o40GQA231XlVNgEZ3YALl5BVfS+OoWXTdIvKfarlcxE3f/5nqJPdetf004dSmo8duCgjyIv/u2+Cx1mcVRI5Op6Q7nr0F/nny1rOmjc5fCZV815rOXmxvNtb4wLIE4en3yWSFgZIwtP9raOZ95dzvFihCWgOK6EJEYYdWbAXzrv4whtu1iaYNYP9mHPR/gwHN9PDyXWQFmmT1NeavIW4pZLVqD1+MP3qKN0t4HZWtOlYyN/LCJGSsMSmIoPyNsnAoYAdIV2fC/xTZ5T3JbReHvqN2614cXx+tbfWF+l+U81lm69bl/3GXvVvTPD56h+PElUA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=urobVT8UCA8HtaJSlMSkRSSBi/svQKWHAIb3/zlBE5M=;
 b=RsSTXn1l0j8jkd9c5IEmNygvGiIHv4rFmXOm9lNCUUO6q+Btm0ta8nsxCZVK3CzlrmdlmupRXUeKSzw3UmQp5tC6XQBrW3fZ2FDeeSVVzbTA7sCIWME43GNwh6faHgKWRCN+QJYi2yz6xK/JwBKLehsCE0Z2GgYfSs56CPE/7yAxf+R0rqBNQe/rbwWYgSiQz3X3n15TG8P5JavhVI9wIu9DoVbyp6OYgbSjCgq7+nHezlCI/zH9Nn26dAtst2tnZ4pUiuYHZJjjFqdYU7gDEpB7Je4rPHMaLDO2/EuoQmbe01PfilBqbVzCku0X+YSjKs1fiP8noyn1rF8B8sWjFQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=urobVT8UCA8HtaJSlMSkRSSBi/svQKWHAIb3/zlBE5M=;
 b=P9Tj/LQ9Ozy1IMES6ANbAImFLgZB+aiZnIXiYc5Je9gOja4nf9X+xbJp8Srl08hFNO44oui5MWXxqQOJlO+4nqPczI1zsyqKf6NbxxKD7Exw9lI2KlCZytW1LO4Z1slKyaeOMys0LdoguzlYBD9eRdfn+LguwScvt/zFwMQxt78=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB4806.namprd12.prod.outlook.com (2603:10b6:610:f::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.14; Thu, 10 Dec
 2020 17:52:14 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e%7]) with mapi id 15.20.3632.021; Thu, 10 Dec 2020
 17:52:14 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH] KVM: SVM: use vmsave/vmload for saving/restoring additional
 host state
Date: Thu, 10 Dec 2020 11:48:14 -0600
Message-Id: <20201210174814.1122585-1-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [165.204.53.104]
X-ClientProxiedBy: BYAPR21CA0015.namprd21.prod.outlook.com
 (2603:10b6:a03:114::25) To CH2PR12MB4133.namprd12.prod.outlook.com
 (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.53.104) by
 BYAPR21CA0015.namprd21.prod.outlook.com (2603:10b6:a03:114::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3676.5 via Frontend
 Transport; Thu, 10 Dec 2020 17:52:13 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 93edb81a-770f-4096-fb98-08d89d3453d5
X-MS-TrafficTypeDiagnostic: CH2PR12MB4806:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB4806BC5B863DFAFAA0A78C8695CB0@CH2PR12MB4806.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 oqUyPgBfc1A5TrA6Ylnrkw+GC3HKEAA5b8tIwnKA6hvlgCbrPF0ZH9ScPtLjSpN+RCx5bRxyi49hukhCCQsx8qxMgCOiSr9fW2i0M2hCI8Oq3fdisMpMxOpCZlU01t4Y1zmfbIkN6iil+LdLnS6YIn8d7raPXj6l5LJ6zlIYO2aLVv5AdLLVwmiaOQPp8s0yAMM/ckyD6YrsJdAfWCiuHY4mrNwoS+pUj0MAp7kAmcIVjOfdlv890JAibzoUc1E2EmqgCuAmE3mUtDpYGX0mZ7EaJh80UkigC53tOONrlOUssPM33dvPfOHaFKiseKhcOdUKDO8sJOUE9QcnSYAHx3qzlP9fV+WPneO4XL4yfHOyzSZ1mVLexr66GQ1EF57JrLLS4JngIs2O8GcmLFXmuK+7xgrsRSXrwhDr965ErbMfJXUUVKjVaqraXUpYTGDiNgd0PaVoH5rZgDDDHJDyTlygpXlY0ecyASNco6XGefbU2Iz4lfL6ocZbKXJk8iUdW1xPRRp4t6/lJv+SJP229PImBvavkHcy0+fntTYeoUwysMG+HA8CtO3owoA39Cq9RiOnpyltaeXf3T5Dg9CgLfu7RmaQL7XjCXnILZFvXZ2FyOLgO1pnK0cx6MDk3vVOtBXTI77L0ZtX4rI53PShySP169YNOYDugd2mWv+HeLtFcU6VyUO+4akrgHy57KwkgSa187gxVaL9lxxPB/oImQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(376002)(366004)(346002)(136003)(66476007)(34490700003)(6916009)(36756003)(4326008)(2616005)(508600001)(956004)(5660300002)(8676002)(1076003)(44832011)(83380400001)(8936002)(54906003)(52116002)(86362001)(7416002)(2906002)(186003)(66556008)(6486002)(6496006)(66946007)(16526019)(26005)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 l3h3vxr+tLO/aES48EyM1lX/OOkj7kx+DSpG/U1LUDkEK/kUrmAAGuB8T2Yw0sH6MmQ1TitXDZn3KFHpTI2v0Ne6IzgrIH50rsCq4h2KDIGX9CgJS212dZhloffvY38/Tlfw/PYgBXdIFYX1lkmT/RvnIIbot8S5YjNiJvNdPb9qGpvFK/+jP+oJydR3R/UIwQvh2EsZQQC2+GUjSWCukIB43j/Iv4THT5C7LKIEhtN4s8HOjKIrPQxoJPQ529QV40ieYeqdH40gZc2kYBNNLnr+MenK/77Eba0m3mtUJ1Moe5KqCEkHIcrOo+pzdFUzHbECkQ2U5+5pXrp2sYheFdr4JAlffI78zYUnPk5fNW7imdtKwUi9SblXqvXDW9pe7SEO1WF908wR84vRbgI27VGZZtyRguRaQ+ExGhCzBS9gK9R8dRRO8vRATOZL+Mi5vnSCC1BaPI/hp0XQ1S+04f/9CjWbulmC0m9ydY8XbcR3oS2uuUCqReltticAxqx/YNU0abuWlibdII/Oa69fGqN8qAiZItkCvQ/zC6EnkB271oMmPjyW7URm9shSvQiyxHP8OR91PefZKxc6G6xuYUkALKhLNW8Wcb+gkGrtdLgOcpT8LK2Z+l5LbOX8GTKJaY+6GSv8ksOmOJjBeGXrXCyUjZRjOTVj991skICCHXJvbdn6V5x8eH1YRVQAuXWPG/M0dd7VXNdZdb16bW1T31Hsbmw71PwHGuVNs5YTPq+/7DbO5JN/yjlnD8DRBPSckLAOgjL6yVyg3VoyotSqLjvLw69vh2eIXlkq/eNMx6+7SxSTsPnp3d8WmiYrKf6G4/ciL4I2d8VO+zCh9Bt0cest/QJ1GofwuaLxuC1gz4mIHLpqm/5YwrBe+9SdzHwDxxSeaAMG9BM10axnrv4kSkRO46XOsBGsiD0R26D0GNQVOcxZTfnHDWVJ4V+Rs1sjp8NRy5EJ2sRjpqy2i5tHlA3VjNaqxHdpox1Zjqy0AJEdwtM37TrGNABHwLukL9dh
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Dec 2020 17:52:14.1565
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 93edb81a-770f-4096-fb98-08d89d3453d5
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 IqRAp6P1kezhxcZUqgzbuDU3AoLvq1zzEtTN348fAwHNSYtDY1E/kiCWSXcZjfAkqohI/SfmlR5h42fjPMcMiQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB4806
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using a guest workload which simply issues 'hlt' in a tight loop to
generate VMEXITs, it was observed (on a recent EPYC processor) that a
significant amount of the VMEXIT overhead measured on the host was the
result of MSR reads/writes in svm_vcpu_load/svm_vcpu_put according to
perf:

  67.49%--kvm_arch_vcpu_ioctl_run
          |
          |--23.13%--vcpu_put
          |          kvm_arch_vcpu_put
          |          |
          |          |--21.31%--native_write_msr
          |          |
          |           --1.27%--svm_set_cr4
          |
          |--16.11%--vcpu_load
          |          |
          |           --15.58%--kvm_arch_vcpu_load
          |                     |
          |                     |--13.97%--svm_set_cr4
          |                     |          |
          |                     |          |--12.64%--native_read_msr

Most of these MSRs relate to 'syscall'/'sysenter' and segment bases, and
can be saved/restored using 'vmsave'/'vmload' instructions rather than
explicit MSR reads/writes. In doing so there is a significant reduction
in the svm_vcpu_load/svm_vcpu_put overhead measured for the above
workload:

  50.92%--kvm_arch_vcpu_ioctl_run
          |
          |--19.28%--disable_nmi_singlestep
          |
          |--13.68%--vcpu_load
          |          kvm_arch_vcpu_load
          |          |
          |          |--9.19%--svm_set_cr4
          |          |          |
          |          |           --6.44%--native_read_msr
          |          |
          |           --3.55%--native_write_msr
          |
          |--6.05%--kvm_inject_nmi
          |--2.80%--kvm_sev_es_mmio_read
          |--2.19%--vcpu_put
          |          |
          |           --1.25%--kvm_arch_vcpu_put
          |                     native_write_msr

Quantifying this further, if we look at the raw cycle counts for a
normal iteration of the above workload (according to 'rdtscp'),
kvm_arch_vcpu_ioctl_run() takes ~4600 cycles from start to finish with
the current behavior. Using 'vmsave'/'vmload', this is reduced to
~2800 cycles, a savings of 39%.

While this approach doesn't seem to manifest in any noticeable
improvement for more realistic workloads like UnixBench, netperf, and
kernel builds, likely due to their exit paths generally involving IO
with comparatively high latencies, it does improve overall overhead
of KVM_RUN significantly, which may still be noticeable for certain
situations. It also simplifies some aspects of the code.

With this change, explicit save/restore is no longer needed for the
following host MSRs, since they are documented[1] as being part of the
VMCB State Save Area:

  MSR_STAR, MSR_LSTAR, MSR_CSTAR,
  MSR_SYSCALL_MASK, MSR_KERNEL_GS_BASE,
  MSR_IA32_SYSENTER_CS,
  MSR_IA32_SYSENTER_ESP,
  MSR_IA32_SYSENTER_EIP,
  MSR_FS_BASE, MSR_GS_BASE

and only the following MSR needs individual handling in
svm_vcpu_put/svm_vcpu_load:

  MSR_TSC_AUX

We could drop the host_save_user_msrs array/loop and instead handle
MSR read/write of MSR_TSC_AUX directly, but we leave that for now as
a potential follow-up.

Since 'vmsave'/'vmload' also handles the LDTR and FS/GS segment
registers (and associated hidden state)[2], some of the code
previously used to handle this is no longer needed, so we drop it
as well.

The first public release of the SVM spec[3] also documents the same
handling for the host state in question, so we make these changes
unconditionally.

Also worth noting is that we 'vmsave' to the same page that is
subsequently used by 'vmrun' to record some host additional state. This
is okay, since, in accordance with the spec[2], the additional state
written to the page by 'vmrun' does not overwrite any fields written by
'vmsave'. This has also been confirmed through testing (for the above
CPU, at least).

[1] AMD64 Architecture Programmer's Manual, Rev 3.33, Volume 2, Appendix B, Table B-2
[2] AMD64 Architecture Programmer's Manual, Rev 3.31, Volume 3, Chapter 4, VMSAVE/VMLOAD
[3] Secure Virtual Machine Architecture Reference Manual, Rev 3.01

Suggested-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Michael Roth <michael.roth@amd.com>
---
 arch/x86/kvm/svm/svm.c | 48 ++++++++++++++++++++++++++----------------
 arch/x86/kvm/svm/svm.h |  6 ------
 2 files changed, 30 insertions(+), 24 deletions(-)

```
#### [PATCH] kvm:vmx:code changes in handle_io() to save some CPU cycles.
##### From: Stephen Zhang <starzhangzsd@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Zhang <starzhangzsd@gmail.com>
X-Patchwork-Id: 11963661
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 189C6C433FE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 08:16:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D12EC23D56
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 08:16:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387657AbgLJIQ1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 03:16:27 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59556 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387639AbgLJIQL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 03:16:11 -0500
Received: from mail-pl1-x642.google.com (mail-pl1-x642.google.com
 [IPv6:2607:f8b0:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 37F03C061794;
        Thu, 10 Dec 2020 00:15:31 -0800 (PST)
Received: by mail-pl1-x642.google.com with SMTP id u4so2372289plr.12;
        Thu, 10 Dec 2020 00:15:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=1rCIZ2aFQJb9JggKwJdiRgk6PJ0mPfhOdiJnDt3jhOo=;
        b=lFPUvVgKLCb8cKfBI6Axvd/IQCepYEs4CksDpqIJjvTNRMkbc7z8zsgW0LM+RLJorT
         NKQR/c6VdD5A71ojCvDSNOj0wTszbLhRSsRY8Qha7utYuuo91F/OaFrFRQumz+LQHuBH
         CWuiFtNbDBp8Dd32oWDu+EMpuG88Q1sqLIXeq7OCF21l5sE008HV1sSZ2vLKstkT19v9
         SpiUUJomSwL+q8HgC3ifq22IKALy3WoBnhDw5LX5r4qLBBAadwG944I3gdcQs3mVH9v4
         0YO+/jxtEB5PBMBZcXUDt0XAKNzj24FOsJLOy/ZA/SzRspXV9tm3rt2ojlyLcBAbc4wT
         McTA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=1rCIZ2aFQJb9JggKwJdiRgk6PJ0mPfhOdiJnDt3jhOo=;
        b=qyd+5LMW73EOgQ2DYO8BtJehzfqLU+MocqLHbkV5TQw9fZetwutQMIYpTEkIx4TEol
         x/b5W0xU3ZNerKBGDIjI1pl89DgsdWd68C1nU/reaidJ4rXtXPfjmeZhiXt9v3ZXsPtz
         QXHYbXH+/xNviQEaqUomf2vFU4w4OyvaSjGv50QtXeqJC371s3mJHWK11aUbP8ngqW0U
         jn1N/c4V469CEMcSJy0YrzilZH0apm9YBYVHECbE77uyW87tRp2fj+04eKsphn/KhA6f
         IEyKSkGhhYRcu3gzj5UEz8IvcNfTpG3+gZLnL7R3v7ARRiZ2PO9Wh94CEtsbbAW+51A/
         cvnQ==
X-Gm-Message-State: AOAM532OfjA55rsjq9wTL0PgpQsMLoB4OQ4+Ti40Ip8Aw3k3T5z6qaQN
        vBf9lsZr4zlQAa0Dw4EAtIY=
X-Google-Smtp-Source: 
 ABdhPJwm8acp3VmSgLF4pkd4f+rev8FIhe932yQHoQ7mQ7d4+mL2H0/sL0SbBBfGsl4vQ+vszUpsAw==
X-Received: by 2002:a17:902:ea89:b029:da:539e:9bb with SMTP id
 x9-20020a170902ea89b02900da539e09bbmr5826549plb.52.1607588130780;
        Thu, 10 Dec 2020 00:15:30 -0800 (PST)
Received: from localhost.localdomain
 (ec2-18-162-59-208.ap-east-1.compute.amazonaws.com. [18.162.59.208])
        by smtp.gmail.com with ESMTPSA id
 q70sm5129650pja.39.2020.12.10.00.15.27
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 10 Dec 2020 00:15:30 -0800 (PST)
From: Stephen Zhang <starzhangzsd@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Stephen Zhang <starzhangzsd@gmail.com>
Subject: [PATCH] kvm:vmx:code changes in handle_io() to save some CPU cycles.
Date: Thu, 10 Dec 2020 16:15:15 +0800
Message-Id: <1607588115-29971-1-git-send-email-starzhangzsd@gmail.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

code changes in handle_io() to save some CPU cycles.

Signed-off-by: Stephen Zhang <starzhangzsd@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [RFC PATCH 1/1] platform-msi: Add platform check for subdevice irq domain
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11962985
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3335C433FE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 00:56:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8404623770
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 00:56:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731450AbgLJA4O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 19:56:14 -0500
Received: from mga02.intel.com ([134.134.136.20]:11147 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728438AbgLJA4N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 19:56:13 -0500
IronPort-SDR: 
 EB40AqRYvyiZYfSRQF1S+qBk/WRbZjEOxF6U0Wp1oWK+yuzmDK8JKrcwM1okGI2bXO4JmOHlU8
 htBhc+IrDgXQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9830"; a="161226432"
X-IronPort-AV: E=Sophos;i="5.78,407,1599548400";
   d="scan'208";a="161226432"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Dec 2020 16:54:27 -0800
IronPort-SDR: 
 MDXlwNbAQ1JCT+K95B+KYpwNKNCAuS13LyV+ICIhcoUiXuEs3nXzfFaqItmkWJeqkTR+ThvX0k
 6/91qjkH07zg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,407,1599548400";
   d="scan'208";a="438062595"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga001.fm.intel.com with ESMTP; 09 Dec 2020 16:54:20 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: tglx@linutronix.de, ashok.raj@intel.com, kevin.tian@intel.com,
        dave.jiang@intel.com, megha.dey@intel.com
Cc: alex.williamson@redhat.com, bhelgaas@google.com,
        dan.j.williams@intel.com, dmaengine@vger.kernel.org,
        eric.auger@redhat.com, jacob.jun.pan@intel.com, jgg@mellanox.com,
        jing.lin@intel.com, kvm@vger.kernel.org, kwankhede@nvidia.com,
        linux-kernel@vger.kernel.org, linux-pci@vger.kernel.org,
        maz@kernel.org, mona.hossain@intel.com, netanelg@mellanox.com,
        parav@mellanox.com, pbonzini@redhat.com, rafael@kernel.org,
        samuel.ortiz@intel.com, sanjay.k.kumar@intel.com,
        shahafs@mellanox.com, tony.luck@intel.com, vkoul@kernel.org,
        yan.y.zhao@linux.intel.com, yi.l.liu@intel.com,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [RFC PATCH 1/1] platform-msi: Add platform check for subdevice irq
 domain
Date: Thu, 10 Dec 2020 08:46:24 +0800
Message-Id: <20201210004624.345282-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The pci_subdevice_msi_create_irq_domain() should fail if the underlying
platform is not able to support IMS (Interrupt Message Storage). Otherwise,
the isolation of interrupt is not guaranteed.

For x86, IMS is only supported on bare metal for now. We could enable it
in the virtualization environments in the future if interrupt HYPERCALL
domain is supported or the hardware has the capability of interrupt
isolation for subdevices.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Link: https://lore.kernel.org/linux-pci/87pn4nk7nn.fsf@nanos.tec.linutronix.de/
Link: https://lore.kernel.org/linux-pci/877dqrnzr3.fsf@nanos.tec.linutronix.de/
Link: https://lore.kernel.org/linux-pci/877dqqmc2h.fsf@nanos.tec.linutronix.de/
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 arch/x86/pci/common.c       | 43 +++++++++++++++++++++++++++++++++++++
 drivers/base/platform-msi.c |  8 +++++++
 include/linux/msi.h         |  1 +
 3 files changed, 52 insertions(+)

Note:
Learnt from the discussions in this thread:

https://lore.kernel.org/linux-pci/160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com/

The device IMS (Interrupt Message Storage) should not be enabled in any
virtualization environments unless there is a HYPERCALL domain which
makes the changes in the message store managed by the hypervisor.

As the initial step, we allow the IMS to be enabled only if we are
running on the bare metal. It's easy to enable IMS in the virtualization
environments if above preconditions are met in the future.

We ever thought about moving probably_on_bare_metal() to a more generic
file so that it could be well maintained and used. But we need some
suggestions about where to put it. Your comments are very appreciated.

This patch is only for comments purpose. Please don't merge it. We will
include it in the Intel IMS implementation later once we reach a
consensus.

Best regards,
baolu

```
#### [PATCH] selftests: kvm: remove reassignment of non-absolute variablesFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11963291
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A67CEC4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 04:37:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74C0623BC7
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 04:37:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732455AbgLJEhH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 23:37:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54272 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732448AbgLJEhG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 23:37:06 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 06977C0613D6
        for <kvm@vger.kernel.org>; Wed,  9 Dec 2020 20:36:26 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id x20so2717663pfm.6
        for <kvm@vger.kernel.org>; Wed, 09 Dec 2020 20:36:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=jH+BFqTYM/TwX75APIA2AjyEOFPXOw7P8lcdqybb7hc=;
        b=Y/G9LwbZcGEr1UAJ0F3cFNU4kOSSyxfv3KDY4m2JT5W3oWMmwHCbAOgr+NrYLhCWUu
         RWQmywIWSAd4qT1aEXmUzTSSmNEH1gIHGjQcGtjvfQk0SS7QAAo/+DXns+IaI1vfthwY
         rKcrBaFWXWhAXboUQ2j3tOIbM+Ia5SOyFGMjJgWxaLo+7Sw7R6D/QEWZBCgXIxVYc5/d
         ubA76euzm/oTEPoOId5UNIPrLjK7SJD9HkrPflWzhAHDNEjxfkHjVYcXhu8wnKYFVtJo
         1Z/eYzV0zV0r2Qzk1JpfPobE2Cw8NK7SqeeHdRSlhf0nDa667CTkqk67pPWkslEgNeCC
         m92w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=jH+BFqTYM/TwX75APIA2AjyEOFPXOw7P8lcdqybb7hc=;
        b=IqksqajfuzGsdK11mm9Hrs4pL0vLa4GmfoI7m+FKOh1wTonaeeTPtKORQ/IIrYnUvw
         0CPQ11L9Xmf0GVQSphSCelx183LxyzO5HaHOf7ZYlmxub1DSEm6CQZj/863DslbNkI3u
         ZCthmLAggEwDocWIbNQ+2CEBuTceSUxdVQ5Jl4boGFv6w/rbL3EaBUI/AHhBWnrIjnX7
         5bWn2ohTTzcTFkca6maLbjt3kL2PTGQJs4QMJdiqZjr473xc9lppItwTF97gQnV8KT6i
         ViRN1VMopLki9QKBnarsXF3zDt2mEZXoFASNm5Bv1cuv4w0UKFZ3Pfz8pDpjcXX2jbRM
         O0Bw==
X-Gm-Message-State: AOAM533L11adlZ4ghdHz1Vtc6uQ6yOY/B7XB3Yu7XAK3HsDmKq2W1K+d
        usj3lvmFYuUoKcmY08Eh1G+Jz1Mi
X-Google-Smtp-Source: 
 ABdhPJxqFIjjdoRvM3pSV/+xbG2xUOSqpD6KJIhfiBxyCLRoTswMnTSxRBNTb98N4Houy5SUkGn9oRPCIA==
Sender: "morbo via sendgmr" <morbo@fawn.svl.corp.google.com>
X-Received: from fawn.svl.corp.google.com
 ([2620:15c:2cd:202:7220:84ff:fe0f:9f6a])
 (user=morbo job=sendgmr) by 2002:a17:902:6b02:b029:da:c6c0:d650 with SMTP id
 o2-20020a1709026b02b02900dac6c0d650mr4893633plk.74.1607574985383; Wed, 09 Dec
 2020 20:36:25 -0800 (PST)
Date: Wed,  9 Dec 2020 20:36:11 -0800
Message-Id: <20201210043611.3156624-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [PATCH] selftests: kvm: remove reassignment of non-absolute variables
From: Bill Wendling <morbo@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        linux-kselftest@vger.kernel.org, kvm@vger.kernel.org
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Shuah Khan <shuah@kernel.org>,
        Bill Wendling <morbo@google.com>, Jian Cai <caij2003@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang's integrated assembler does not allow symbols with non-absolute
values to be reassigned. Modify the interrupt entry loop macro to be
compatible with IAS by using a label and an offset.

Cc: Jian Cai <caij2003@gmail.com>
Signed-off-by: Bill Wendling <morbo@google.com>
References: https://lore.kernel.org/lkml/20200714233024.1789985-1-caij2003@gmail.com/
---
 tools/testing/selftests/kvm/lib/x86_64/handlers.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v5 01/34] x86/cpu: Add VM page flush MSR availablility as a CPUID feature
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11965693
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C55FEC4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:09:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99E7C23D39
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:09:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392496AbgLJRJZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 12:09:25 -0500
Received: from mail-dm6nam12on2055.outbound.protection.outlook.com
 ([40.107.243.55]:46528
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1730503AbgLJRJK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 12:09:10 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lLAJzhBDKxzJdFcSf89HT1YTauyoEQ/4TziLaGANXL8Y/KWjh+/VR+qiKKvWWJTj7yOGKyaJrREb4KmXscXrc+QG2m4mfsYTPXzPZDllSr1pAu54ghjPFY79XlL4QEcn0ETyFqmEJxY+MwjlAjr3+enW8odIVTq4ceBIL3JRn/fpMdI9qrSUMJ58ilYJEpP4qbZeB1n0ZiDJpxETofVjKRpY+IpRHiGsZdMyL+k02tlzMl8mvL98erg+t/+gNm4ZXWmiuljgvRWdHMKzf+o2A1KuOMPq4V72O98KTguO8CJjSa/iiba+kSULCCtKd4d3eQiCRHRPniMFQOlQyhYzSA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=jWouVlkxPGesp+cgKzaZXoFSsmGuvve45KZw+wtsGiWj8AJbv5KKg+pPqFq0YYYZDaRb4uXhy/LqBWtjOuwA/lUFtTNTDNEoXhPpVcEZ7GxotVY2uqddsJdfkLKuZ8lzSL7fOcOM4xqJHlSJReVs5KlPVjzSy3nOfQfUMBEKJ6enKIXi72bxNsJzcf+4i0EmlJgZtp/AWRjeFenkvl+VHnjQJULL/9mMuImy6/q3GCIaDNu7WXhT9XxWyY9qQYoZTXDfyh9eUCHW1MT5JAqbgb6pxmGhfCkKbGyX/QfcoNMNlzG7abz8B4Nh1BvnTfp8bPE/xP9fQTQNxnE2Lc7VQQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=NdS51naCgAUj3Gvu6z0BMHLHBDsNM366Fb5sA6CCt9jgssQSk6y8VVV2acrpf9Avcmr5eUlEhPP+eZGeOceZ8sEODN06awJubZ1Rm0hjpnKelKjCWNJcTSQfSwhoHDYQHPvvtJChKBjvNf8CRFULL+0FzZkscIFjC0BQTx+C3/E=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR12MB1493.namprd12.prod.outlook.com (2603:10b6:910:11::7) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12; Thu, 10 Dec
 2020 17:07:43 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d%8]) with mapi id 15.20.3632.021; Thu, 10 Dec 2020
 17:07:43 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v5 01/34] x86/cpu: Add VM page flush MSR availablility as a
 CPUID feature
Date: Thu, 10 Dec 2020 11:06:45 -0600
Message-Id: 
 <f1966379e31f9b208db5257509c4a089a87d33d0.1607620037.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1607620037.git.thomas.lendacky@amd.com>
References: <cover.1607620037.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH2PR03CA0013.namprd03.prod.outlook.com
 (2603:10b6:610:59::23) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 CH2PR03CA0013.namprd03.prod.outlook.com (2603:10b6:610:59::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Thu, 10 Dec 2020 17:07:42 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f213ff22-85c6-4d90-4d6d-08d89d2e1bc9
X-MS-TrafficTypeDiagnostic: CY4PR12MB1493:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB1493EFB922691DE290F4AE1CECCB0@CY4PR12MB1493.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 gMfvoe2AdnTKdr6tfMlnus88PrYJm1e0iKvqCte7+5TJStINuX6B61I75KMoSEg2tHZYbdoh5aDDQ2ruuJOzA9Uii2RkMCYRn9luKo8RMMshri0IqLd2zpHrcGDFUMwcPNbOu0rvAuiXbk4qm/rWo4vt21lGfUSatF+xMIA0ptIo8caPW3+OqALiUNxrKx1En0ShP0bV7IV0uYFcW9kFJ7sdtffHJ8uIKv1WYPD3P2dIHg2qc7FJXz8QN50EbhB5AFHaXO9+P3tC6XzhDzLA4HlIcI4QPvz9j2bnDl8yqjvKV++0jvd20wApQoo4KBocq4CbSfh8l0rfz9UPTRA/hKx6pIK9TeC3kt8/pzzkiQyO5zldaq7ttWrXGy3xN/PU
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(136003)(376002)(346002)(5660300002)(66476007)(186003)(52116002)(8676002)(36756003)(8936002)(4326008)(86362001)(2906002)(66946007)(66556008)(26005)(508600001)(34490700003)(7416002)(2616005)(16526019)(54906003)(7696005)(956004)(6486002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 F6l0gRMtm6TicIMHKEA/LCdtLmfsboFj4kcUOaG9EkogsdIAanrmJOo9CXK+HYW8vmVTLz9JbxBQLxvjgqfzqeC3jkOsUht1q1YQUMAqWhkGIkT48WDpWiPYg5XnqkicJzzZh/7czCv5CSuhY/BnlvgtEpjSlEnTCMKzcYPdKC4nEjJhfX/uZ8/DTPNQXdPcePlTXGy6x0oZ7oA6dQxGmwj2GzXZVb268y1LeCEY8i35RYOHNhVHE0rRXkOWDjv8E0DJvSjmagKs6A1++vrOSc+GH7bv2YgY9ESr4UFFNblSNtQO9qgsp1ZSwOc4Oc0FNDbahuOAjqoUfl71qzYD0Hmz/ch98JtpmL7hAQImvsNFIs7vPeVkqHrBeVBbDuf3rlOQ4pkKuMp9LDG6mepsm6Pv6FXV5aHj2Iq4OGWCNvWqjmrYBCffk3MlcqWbRWYrH3UIM2zvleY3AYz/VgYffv6OEIDBHCJrIiaZjETKYnLIuW5nRT1HKnvAllitXtDizD5HCrIQ0pqYMHGcGzgQkYUUWjb3wdk3QNZHIgpCID3eutELv4bjC/dXMsuVq/3rjVyREv1A6Ee0HXALye1u8FfCl4LGkAJkg4LIupsVbMc9q1/LGNlIkj/KvikXWLZUD1AF8zBE0isEd6DTuRBEOOsy9D4sun+PBI4tOWJJZ9vRl7HSTMONxL0XaArOgHFahrrV+3Ggalx81WapZybBErwb7dJjutnwgx/XSHw8Sks6VQWNhAdcVYu2hhQyC0v77Hvuka+Enl/UPV71v8Knr34qVGKu+zfxskPrT3WR4qLaOy4gdtRk8SdR/Tbertsf0bRuQP9g3SXqnjmkZIgD92jo94Z41Ok24yVZYltMklvkHb6Zl0p9Vk4lzFH9ymuB8yLQv7N5ZaDithe9pTuIuCfSr+MyT6MWwSOqhbsZ9fqkutHfmPxbQ1PO09ay0oEgTSJIWILxljReN1Mttsa/Ez+8vSE4lJaGQrknOznQgj/wYvD3LAOVyrO0KfyDtHCE
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Dec 2020 17:07:43.2509
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f213ff22-85c6-4d90-4d6d-08d89d2e1bc9
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 d8I5PNeM1OeCRnSKJ1wO2yXAnqPBNTc17PK+JtouS+g8+3rwNXppOM7Yba3JIyj2t3ENEj2TM0i6KRkzNEUFvg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1493
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

On systems that do not have hardware enforced cache coherency between
encrypted and unencrypted mappings of the same physical page, the
hypervisor can use the VM page flush MSR (0xc001011e) to flush the cache
contents of an SEV guest page. When a small number of pages are being
flushed, this can be used in place of issuing a WBINVD across all CPUs.

CPUID 0x8000001f_eax[2] is used to determine if the VM page flush MSR is
available. Add a CPUID feature to indicate it is supported and define the
MSR.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/include/asm/msr-index.h   | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 3 files changed, 3 insertions(+)

```
#### [PATCH v5 01/34] x86/cpu: Add VM page flush MSR availablility as a CPUID feature
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11965859
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 541C8C4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:06:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 15F3B23DE3
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:06:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404081AbgLJSFc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 13:05:32 -0500
Received: from mail-bn8nam11on2087.outbound.protection.outlook.com
 ([40.107.236.87]:25696
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392578AbgLJRL4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 12:11:56 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=UDjxLR1VOiZEkpRvd1LHcGGmxP0nTXOD1EVs1URsU340VSm+HiCLLxJebMn2Mk87n/HI8CBkGOU+pe+ydAvrFfMaWtvkRPYIR4bLERo5uMUaY8qWnVq/yi/qOjiAr8IA1zVPMJoJ+DkP+dmq/tx88SHCJMRUsQvcurpZIBHDK5DtqP4FQEqxJu44Myt4aLp9ScANqzMwG3gHw0FTOoRfVuQK1rN1rGPiuH6CKa8sp88rG18lvRfReB8bnZxhEepRUR+eN3F3di0jBLl/dIdu0GR+Yha9XMZ0IpIau8CxpjBV8ucy84fZeJMDBY5omLFYYgEQeGDAT6ehpK9XtP4Img==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=Dybb8heY7SWuCik5fBpouj4CIBIxjihECg5Lgq4xktDwTOdRW+3kw5u40YCZUMB2Vy/hoJwY62Jx0J/+wP0oiUXWvj1+2gld+Zttu+8fxpG1kqQqQzAnJTQBdTqpHgSXtZjCa6hkj+K/yY9crkAthmMQxdBEMf19yqbc9c1wnlz7ZitdfPHO2zkyu5z0ZDWa0YRgNOigpeE+t8o6Ae5bitE/jgDreiszDUVkYhS49llSJCOpC41dcH2v7GawYpzvUHjGb5j6NCWS/qhEh3I0QLfKZj9029jZm7bLG3Ymplx0rU85vAviS1BnvQ2U8/Ujygo0hwggkbHepzYx/49e9A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=RaPL/SkflB8LRrlDUl58Y7ylkGyIR/lXEK5m17/ZVaruES2QrHiLzqsALxxfPopOgG/fLe7bRZ9ZRuQeq8Lofn3htDKwQScpIXLQBSEYZ19pikf2uLgruVqxQmSV2RiSLuEl3s1Y9s5ZnGSM9iEzZ2h6m58J7DBkr2ymU+zrDbA=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR1201MB0168.namprd12.prod.outlook.com (2603:10b6:910:1d::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.22; Thu, 10 Dec
 2020 17:10:26 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d%8]) with mapi id 15.20.3632.021; Thu, 10 Dec 2020
 17:10:26 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v5 01/34] x86/cpu: Add VM page flush MSR availablility as a
 CPUID feature
Date: Thu, 10 Dec 2020 11:09:36 -0600
Message-Id: 
 <f1966379e31f9b208db5257509c4a089a87d33d0.1607620209.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1607620209.git.thomas.lendacky@amd.com>
References: <cover.1607620209.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH2PR10CA0030.namprd10.prod.outlook.com
 (2603:10b6:610:4c::40) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 CH2PR10CA0030.namprd10.prod.outlook.com (2603:10b6:610:4c::40) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Thu, 10 Dec 2020 17:10:25 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f4a4e8cf-7de9-4e2a-d163-08d89d2e7cf2
X-MS-TrafficTypeDiagnostic: CY4PR1201MB0168:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR1201MB0168D137EF7DCC3A0EDD0433ECCB0@CY4PR1201MB0168.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CaDYmh9pJ0oZgX31lFTZu8qWQdjbaCNAh2lkDRwGoAca2tWQExcM63apcxoSFqJreu2rM+b06YYJsk1wxKOf1VgQ4UJtgWezKuBCUn0pPH9kg4G66CNfrEhRyRiDP+hMyDBdVRzINm+o41VjGt8fuLtAbRp322bhTR4dMLps+AA1MICM+pKCCzcVvuKmt++CdX9WhHl4gyElizH3I5aSyIpYA46bmi+b/SgsNiZjpq/oQK795TUmmIkNnJPt977N43fDn/wrIpKBTCXTTY4gp18qyhUh356FxjUr6sc6ohIv1PYv1xaOXAHFzdIG/2jH782PEW/P3wI4YY1W0IL1YyUbxDrfSQZ0xtyD/QFQrurHz5FyKuCumoy+EQcMvBNQ
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(136003)(346002)(376002)(36756003)(8676002)(6486002)(4326008)(66476007)(86362001)(7416002)(66946007)(7696005)(54906003)(6666004)(26005)(16526019)(34490700003)(66556008)(8936002)(186003)(2906002)(2616005)(52116002)(956004)(508600001)(5660300002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 GrAyUDUVg9k3mbUZeUV2moygcE761cqfgC4vppU9BoFbMAatF2142WL1mYKRvL45hsQoFC711neDQhSJ5VR9sxyVG3mpIRyKoP3JI+a0PTiWDOB7e+L6rLuT+CQU14Q/U4IE+jEe41CEG+lO1Ppva1j1PKdlO+A7GOA/HcDwrdEcmWMbabxTZuzeju2PJ71EAQpQk0nZEHRsWqc5QsJWovovwstI2+gB/nRSBySmG6MLafSieXw2JOI4zzAM1RKoLr06kOBJXFTQZeKd1xy8FfBSTrxUbgVuDIPo/4wpIOZG0+ZNN23JOLXUhYCb1a8T0yLZHNUKtgAx54n93GigC/0sVQO01aLh73+dzX8n97x53bS8LGLJDvnkK/sU6UXANJlgAwkDL2s7SmxT1B5kmPGC7nYml/LEtidgL7blSMzgeUqZY5FQ5EwNesP7Z+ubN9k4HfzOdJ2cnHqVVXj5Ll/2kbrJxNXTCcKy1dkD2l18m5mR0GG3HGAy+4Rdcnf8u2wqD07iZl9zwJXsqs3/hDg6ka69bA0RW22KXPMcZ6jjXzrIaIAT85vdtW7mBHP4XMzNOtEoQEfrTYGF5K/dmeml1kfk8GaHv/CmtZeLq7xAU/EWpwFb23L4mL3cdfok2EOP+FTE01nYgrkQiWjHq7zYP6eS/849G4EKoDocs9Qo+jUslUIHh6podqENPUNV9BScL8+29ydatXuIXQeAcnDOdE7nbFInzTquZNXbJSfiwSazghjBOdKCCDv6M36j1tPWbQxogN3o2dCoS99CaYqlTCXczdCZ0fY4swuKZneSwWIr8SpzD7ewKoBWIOcNIADIqkQgomhod9E0Ev5ngsqd78UbDwiMTqd6g+TxzsHPSrMMA1A3KXDHlI+hIwXDkIdhYjZ0ds2vjvdEqGva4t3u3G9rSd/IzBsSNdVDkNFy//6/+rtyEoS6KcZi71hoeAaPDba5edLffTUfg9pshakOLZfU6ia+qoV+TkPR6nCTWRPJ3u4a8yzROK1FMMHF
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Dec 2020 17:10:26.2710
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f4a4e8cf-7de9-4e2a-d163-08d89d2e7cf2
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 mDMUBBZZ78kOxEeZuFTWRGknlJaLjRFIBDPEq8WGUCZwt0qMLCpTqxW7l75lljS9oD2se4MjcDi/xYkkKlUXVw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR1201MB0168
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

On systems that do not have hardware enforced cache coherency between
encrypted and unencrypted mappings of the same physical page, the
hypervisor can use the VM page flush MSR (0xc001011e) to flush the cache
contents of an SEV guest page. When a small number of pages are being
flushed, this can be used in place of issuing a WBINVD across all CPUs.

CPUID 0x8000001f_eax[2] is used to determine if the VM page flush MSR is
available. Add a CPUID feature to indicate it is supported and define the
MSR.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/include/asm/msr-index.h   | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 3 files changed, 3 insertions(+)

```
#### [PATCH kvmtool 01/21] ioport: Remove ioport__setup_arch()
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11966013
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DE05C4167B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 19:29:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F1D0522EBE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 19:29:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390310AbgLJT3Q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 14:29:16 -0500
Received: from foss.arm.com ([217.140.110.172]:44772 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390263AbgLJOaJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 09:30:09 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 43F3531B;
        Thu, 10 Dec 2020 06:29:23 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.195.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 288143F718;
        Thu, 10 Dec 2020 06:29:22 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Marc Zyngier <maz@kernel.org>
Subject: [PATCH kvmtool 01/21] ioport: Remove ioport__setup_arch()
Date: Thu, 10 Dec 2020 14:28:48 +0000
Message-Id: <20201210142908.169597-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201210142908.169597-1-andre.przywara@arm.com>
References: <20201210142908.169597-1-andre.przywara@arm.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since x86 had a special need for registering tons of special I/O ports,
we had an ioport__setup_arch() callback, to allow each architecture
to do the same. As it turns out no one uses it beside x86, so we remove
that unnecessary abstraction.

The generic function was registered via a device_base_init() call, so
we just do the same for the x86 specific function only, and can remove
the unneeded ioport__setup_arch().

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/ioport.c         |  5 -----
 include/kvm/ioport.h |  1 -
 ioport.c             | 28 ----------------------------
 mips/kvm.c           |  5 -----
 powerpc/ioport.c     |  6 ------
 x86/ioport.c         | 25 ++++++++++++++++++++++++-
 6 files changed, 24 insertions(+), 46 deletions(-)

```
#### [PATCH v2] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11965897
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE5F7C433FE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:27:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB18523E1E
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:27:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392350AbgLJS1D (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 13:27:03 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:41584 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389529AbgLJS05 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 13:26:57 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1knQdO-0004dA-3B; Thu, 10 Dec 2020 19:25:46 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, linux-doc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
Date: Thu, 10 Dec 2020 19:25:40 +0100
Message-Id: 
 <85d2d9f31ff693cf39e787af3ec5fe599cb66c5e.1607624644.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

Commit cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
cleaned up the computation of MMIO generation SPTE masks, however it
introduced a bug how the upper part was encoded:
SPTE bits 52-61 were supposed to contain bits 10-19 of the current
generation number, however a missing shift encoded bits 1-10 there instead
(mostly duplicating the lower part of the encoded generation number that
then consisted of bits 1-9).

In the meantime, the upper part was shrunk by one bit and moved by
subsequent commits to become an upper half of the encoded generation number
(bits 9-17 of bits 0-17 encoded in a SPTE).

In addition to the above, commit 56871d444bc4 ("KVM: x86: fix overlap between SPTE_MMIO_MASK and generation")
has changed the SPTE bit range assigned to encode the generation number and
the total number of bits encoded but did not update them in the comment
attached to their defines, nor in the KVM MMU doc.
Let's do it here, too, since it is too trivial thing to warrant a separate
commit.

Fixes: cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
    Changes from v1:
    * Introduce MMIO_SPTE_GEN_{LOW,HIGH}_BITS and use it to compute
      MMIO_SPTE_GEN_HIGH_SHIFT.
    
    * Add build-time MMIO_SPTE_GEN_MASK consistency checking with the
      above bits defines via a BUILD_BUG_ON().
    
    The easiest way to reproduce the issue is to apply the patch
    below to the existing code and observe how memslots generations
```
#### [PATCH 1/7] vfio: iommu_type1: Clear added dirty bit when unwind pin
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11963583
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B487FC4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 07:39:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7402122B3F
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 07:39:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732661AbgLJHio (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 02:38:44 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:9861 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731363AbgLJHgT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 02:36:19 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4Cs5Kg6N1tz7CCB;
        Thu, 10 Dec 2020 15:35:03 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.37) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.487.0; Thu, 10 Dec 2020 15:35:25 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>
CC: Joerg Roedel <joro@8bytes.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 1/7] vfio: iommu_type1: Clear added dirty bit when unwind pin
Date: Thu, 10 Dec 2020 15:34:19 +0800
Message-ID: <20201210073425.25960-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20201210073425.25960-1-zhukeqian1@huawei.com>
References: <20201210073425.25960-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.37]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently we do not clear added dirty bit of bitmap when unwind
pin, so if pin failed at halfway, we set unnecessary dirty bit
in bitmap. Clearing added dirty bit when unwind pin, userspace
will see less dirty page, which can save much time to handle them.

Note that we should distinguish the bits added by pin and the bits
already set before pin, so introduce bitmap_added to record this.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 33 ++++++++++++++++++++++-----------
 1 file changed, 22 insertions(+), 11 deletions(-)

```
