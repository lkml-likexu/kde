

#### [PATCH v4 0/2] Expose new feature for Intel processor
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
From patchwork Tue Aug 25 00:47:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11734587
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C33C1739
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 00:54:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA71821741
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 00:54:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728227AbgHYAx5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Aug 2020 20:53:57 -0400
Received: from mga07.intel.com ([134.134.136.100]:44396 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726090AbgHYAx5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Aug 2020 20:53:57 -0400
IronPort-SDR: 
 s/5ZfokiSKpQq8n8WseAR4E+QzvMF4ydRlp5prEJ++FlTnHz5tUZuZe892EBUFWw60FS/gjrkh
 RKYQL8bapG4A==
X-IronPort-AV: E=McAfee;i="6000,8403,9723"; a="220284855"
X-IronPort-AV: E=Sophos;i="5.76,350,1592895600";
   d="scan'208";a="220284855"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Aug 2020 17:53:52 -0700
IronPort-SDR: 
 CjSlxqYRBr9+F4QcLIAi6bJu3kzeaxyz8Q5SQtD+YbMYl3ZrSkJ2cmcPRpOZpRHry3x38tzrAx
 i932oJdbbDNQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,350,1592895600";
   d="scan'208";a="281351912"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by fmsmga008.fm.intel.com with ESMTP; 24 Aug 2020 17:53:47 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        gregkh@linuxfoundation.org, tglx@linutronix.de,
        tony.luck@intel.com, dave.hansen@intel.com,
        kyung.min.park@intel.com, ricardo.neri-calderon@linux.intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        jpoimboe@redhat.com, ak@linux.intel.com, ravi.v.shankar@intel.com,
        Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH v4 0/2] Expose new feature for Intel processor
Date: Tue, 25 Aug 2020 08:47:56 +0800
Message-Id: <1598316478-23337-1-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset is to introduce TSX suspend load tracking feature 
and expose it to KVM CPUID for processors which support it. KVM 
reports this information and guests can make use of it finally.

Detailed information on the instruction and CPUID feature
flag can be found in the latest "extensions" manual [1].

Changes since v3:
  * Remove SERIALIZE part from kvm patch and update commit message 

Changes since v2:
  * Combine the two kvm patches into a single one.
  * Provide features' overview introduction in kvm patch commit message.
  * Get the latest kernel patches.
  * Change definition from TSX_LDTRK to TSXLDTRK for TSX new feature.
  * Change kernel patches Author to the owner.
  * Remove SERIALIZE enumeration patch.

Reference:
[1]. https://software.intel.com/content/dam/develop/public/us/en/documents/architecture-instruction-set-extensions-programming-reference.pdf

Cathy Zhang (1):
  x86/kvm: Expose TSX Suspend Load Tracking feature

Kyung Min Park (1):
  x86/cpufeatures: Enumerate TSX suspend load address tracking
    instructions

 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kvm/cpuid.c               | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH v2 0/2] Use same test names in the default and
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
From patchwork Tue Aug 25 10:20:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11735485
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23379722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 10:21:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07AB62074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 10:21:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="aN2LZosW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729857AbgHYKVS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 06:21:18 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:15010 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729680AbgHYKVA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 25 Aug 2020 06:21:00 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07PACij1119387
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=2EmO7GuAkt2CBeoiQu48W4AhvFHCdNqQkoc/pOSQtkw=;
 b=aN2LZosWPFpvcR2gQ7wDO95i5AC/Km8NJyliG1DKg42fge6Xjp/od6DP49u0+Vmy9WNr
 XCLMGftmVlhSKrxvQ/JXzX1ouZYixNpdrmT9lYJ6mZmf+A5AOkBVFd5cx7OamBkUDX4E
 bZiW24B0kciJ2d8n5qly5+VWXdkAOxNg8hAGbwMgNCL80obc+98cFksxXxA4/kLxVlhg
 b9NnMLQgnjTAsMuFYMXMkECAq1OL706dqr2WG3dKeB0rbcTrV2fKYYWtU0W6GF+Nc+/U
 ZMhageIiGKL2hQFjAP4k03mctynuQeOxGmnL0r+AnO4jnphx5+3o0C3px9uFnoGvJGLn Qg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3350pjr6hm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:59 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07PAG6wS127460
        for <kvm@vger.kernel.org>; Tue, 25 Aug 2020 06:20:58 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3350pjr6h2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 25 Aug 2020 06:20:58 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07PAFvws001176;
        Tue, 25 Aug 2020 10:20:56 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 332ujkua9g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 25 Aug 2020 10:20:55 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07PAKrFc30212602
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 25 Aug 2020 10:20:53 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A80A6A404D;
        Tue, 25 Aug 2020 10:20:53 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3F911A4040;
        Tue, 25 Aug 2020 10:20:53 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.56.167])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 25 Aug 2020 10:20:53 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH v2 0/2] Use same test names in the default and
 the TAP13 output format
Date: Tue, 25 Aug 2020 12:20:34 +0200
Message-Id: <20200825102036.17232-1-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-25_02:2020-08-24,2020-08-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 spamscore=0
 adultscore=0 priorityscore=1501 mlxscore=0 malwarescore=0
 lowpriorityscore=0 mlxlogscore=999 suspectscore=0 bulkscore=0 phishscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008250073
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For everybody's convenience there is a branch:
https://gitlab.com/mhartmay/kvm-unit-tests/-/tree/tap_v2

Changelog:
v1 -> v2:
 + added r-b's to patch 1
 + patch 2:
  - I've not added Andrew's r-b since I've worked in the comment from
    Janosch (don't drop the first prefix)

Marc Hartmayer (2):
  runtime.bash: remove outdated comment
  Use same test names in the default and the TAP13 output format

 run_tests.sh         | 15 +++++++++------
 scripts/runtime.bash |  9 +++------
 2 files changed, 12 insertions(+), 12 deletions(-)
```
#### [PATCH 0/4] SEV-ES guest support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Tue Aug 25 19:05:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11736263
Return-Path: <SRS0=SWjj=CD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37E74159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:06:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 141622075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 25 Aug 2020 19:06:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="YMiEhbxq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726225AbgHYTGE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 25 Aug 2020 15:06:04 -0400
Received: from mail-bn7nam10on2082.outbound.protection.outlook.com
 ([40.107.92.82]:26557
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726066AbgHYTGC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 25 Aug 2020 15:06:02 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MjcS1jxPIa9Sjv+RLknuqoEcedZ6peZlKEQoRItHlIsfCmrVjZYo2P6WcLehn9uIpv4IyJAMe3ub7c8ai8Mg/eu8Zm2WG6qvHGDaHPLNVk7f1XrWpY7PQLMWqyM+mIkr5xkJuqxQnh3F/bl/xgMd8s7JHKedciRpId8ZybLSQB6r0Ge1w29otIbDwXuyIHwWwe4mrHTZTZUcy/vkPfhaSidjGmZbuuSozBABLKshNze23s+0fFgVaO7PI4cueT6BFdXVgJGuMkBcvUHSor5K2etHxFVXjFCCK+izH8u77zAnSuYDah+ofzheAQEc+A46nHjZbeQXTIqSWCRG3Ri92Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uGjpO7WPS2TOt2AVoJ9MRAr5ib2VtjdjGHv0KEkusoA=;
 b=TwIgbYlDnEGRLoCmp4HQ+fIkZhI/drhc5YJNOCdKq3EYTP50Y9fZuaXOOcfSZDwZupj7Kc1Nj4lyxGr/d105HEsIZtWzeb26l7oHv4CbVngxcYRfDnzJNCfsl8HIE/nMYCoKTr8uSaSqMsMc+BJj9NzZvSIbs0DFV3Ep6h+JC6sw1Ln885HfJs6kA/o2HJU+REPeHJJAogeOsNFxidxYxHPvzrxHBFjUmpzyafb9seh6u5IUOEqW0QIS46LfS1vxWLA7qjxLEa26dtWJszYVZ/vpHH4KQIoyt7nirj4b5ugxlYKFBUBkupSvnBHHv14CzJ99lseqELi9FSh7NAFcQA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uGjpO7WPS2TOt2AVoJ9MRAr5ib2VtjdjGHv0KEkusoA=;
 b=YMiEhbxqi/fZgyeCNvQTL2pIDtMRspBi8woIDmffDWg2ajz6wz+e6yTONkaLrJdvYCzFg9q9xNWZOSlRTNM39RkuOPDQx8lMuMXusxsHZ4hPxtzZPmoyTw6Wmpr7Wwi5CXHzjWKC3GesG6hIbaTb7rCCRrbCDUZpTJZVVJnNXhA=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR1201MB0219.namprd12.prod.outlook.com (2603:10b6:4:56::19) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3305.25; Tue, 25 Aug 2020 19:05:58 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3305.026; Tue, 25 Aug 2020
 19:05:58 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>
Subject: [PATCH 0/4] SEV-ES guest support
Date: Tue, 25 Aug 2020 14:05:39 -0500
Message-Id: <cover.1598382343.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: DM5PR16CA0014.namprd16.prod.outlook.com
 (2603:10b6:3:c0::24) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 DM5PR16CA0014.namprd16.prod.outlook.com (2603:10b6:3:c0::24) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3305.25 via Frontend
 Transport; Tue, 25 Aug 2020 19:05:57 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 26119b52-ccb2-4ed2-a4cd-08d84929e67a
X-MS-TrafficTypeDiagnostic: DM5PR1201MB0219:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1201MB02199A83C0CE0192448BA694EC570@DM5PR1201MB0219.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 kskI6cGeRdN6L0P3nuHwQcaoRD4NPPH+cydlJTQJRDdsQQtZe9Npc02/Miiv4ONOIAknk6l+m0bByWtZiVPGw67hKL+fqn9HfOzOZfbLe3jgyn6Ygmo9W/Wjnewk3CpvP/tuwiaspYx/Z65keFJHsijTo4i46L51GvY7vwJnF5LYBygItGi1rdEVUJ3wxpG60nIEbf37RijE/nJAzJNxP8/vq5cD0SsasaVB8BVmKM8tsHEniipBORFmTqXSoLSDoaJ+oT2agPK3cKWawPRF6QnbWM/u+4hWAtuFQYZzJESEBnrWAK2Y/3S//aEX9x1cPWTzT7jjZx6vrMHhnCyNo1RgYi95bs712Qwvmxf9CmqnPq4HX9HNdLI4535bfQEndFOhvknlDriRZcJm+Llta2NmnVzo1PWeS2FYSnTVBOMgf9iNy7k6Qmmu/h06a5T2ueVBzpFf/RYuwa7OhodvsA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(136003)(376002)(39860400002)(366004)(346002)(4326008)(186003)(86362001)(8676002)(83380400001)(54906003)(16576012)(966005)(8936002)(6486002)(316002)(478600001)(36756003)(52116002)(26005)(6666004)(66556008)(2616005)(66476007)(66946007)(956004)(2906002)(5660300002)(136400200001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 J7IxsZWr3Qh9e5ChUgW8YnEArYmJrU471ZP2hgQc6vuU8RiAdS6Gz7Yxe+/GIMR/reFzOYwb2I6Y8KcoCkkUyH0CWVs5kmjPYuX9Cy4XaszeQksGg90iOpwPVrF+7BOyUau3+DCBIQTSe1DsZ0P2hC8aHspekHDAzn+cbwNVJ4up+RtR1+kJHQR+KwPKPMSZj8FcwT8ms7qGMG3wB4dQ+1haw3osWvZmRiJvYRk2Y03qy1KqAM6/jIcRXW+W1JwzNFPuKX5w6MqeqU6bUudOdKpvJ+ic8TRi5mGYuNNP5wxMSi7gHA08/44mLPc1JaJhdcfPOkT6jQfBkWboSqzyakkb796B4jslR4QI3CgkySq4tGvQDbZZlCn+H63Z+KMtvqaBwsj5E1oEtBfBJJrS5hjKAo12ayR37Us2TMf3/Y93Nd8BBn8F7E0FbLkVgPGfwGBoISjpgcSDRIDiOkTSMVCXC3Ej2ckNhJSCPtyW1XVolZWSrQ37XgVgZX2FqfRe2CH5hOZlSbSDLYHxz3pjo1JoEWteyG7FmK9KLaRtRxYCP24iph2Rw9joOSeLWckK61yyP6nkpQwhGu9OZJFX97lj/CESmNMslC+by6waw7PMKihby4qAo+4gcfbKyWzfWTndOB9BRih374TV/BvhMQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 26119b52-ccb2-4ed2-a4cd-08d84929e67a
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 25 Aug 2020 19:05:58.5117
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 pi+ZesfZSkg4JcuBXXHw6a8d4ao/qW5u3ox1hJ8tQfPXhFN2aFnsXXNYVu6VfPDEwtg04p87UPTI2wCU7kf1qQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1201MB0219
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for launching an SEV-ES guest.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

The main areas of the Qemu code that are updated to support SEV-ES are
around the SEV guest launch process and AP booting in order to support
booting multiple vCPUs.

There are no new command line switches required. Instead, the desire for
SEV-ES is presented using the SEV policy object. Bit 2 of the SEV policy
object indicates that SEV-ES is required.

The SEV launch process is updated in two ways. The first is that a the
KVM_SEV_ES_INIT ioctl is used to initialize the guest instead of the
standard KVM_SEV_INIT ioctl. The second is that before the SEV launch
measurement is calculated, the LAUNCH_UPDATE_VMSA SEV API is invoked for
each vCPU that Qemu has created. Once the LAUNCH_UPDATE_VMSA API has been
invoked, no direct changes to the guest register state can be made.

AP booting poses some interesting challenges. The INIT-SIPI-SIPI sequence
is typically used to boot the APs. However, the hypervisor is not allowed
to update the guest registers. For the APs, the reset vector must be known
in advance. An OVMF method to provide a known reset vector address exists
by providing an SEV information block, identified by UUID, near the end of
the firmware [3]. OVMF will program the jump to the actual reset vector in
this area of memory. Since the memory location is known in advance, an AP
can be created with the known reset vector address as its starting CS:IP.
The GHCB document [2] talks about how SMP booting under SEV-ES is
performed.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
[3] 30937f2f98c4 ("OvmfPkg: Use the SEV-ES work area for the SEV-ES AP reset vector")
    https://github.com/tianocore/edk2/commit/30937f2f98c42496f2f143fe8374ae7f7e684847
---

These patches are based on commit:
d0ed6a69d3 ("Update version for v5.1.0 release")

(I tried basing on the latest Qemu commit, but I was having build issues
that level)

A version of the tree can be found at:
https://github.com/AMDESE/qemu/tree/sev-es-v9

Tom Lendacky (4):
  sev/i386: Add initial support for SEV-ES
  sev/i386: Allow AP booting under SEV-ES
  sev/i386: Don't allow a system reset under an SEV-ES guest
  sev/i386: Enable an SEV-ES guest based on SEV policy

 accel/kvm/kvm-all.c       | 68 ++++++++++++++++++++++++++++
 accel/stubs/kvm-stub.c    |  5 +++
 hw/i386/pc_sysfw.c        | 10 ++++-
 include/sysemu/cpus.h     |  2 +
 include/sysemu/hw_accel.h |  4 ++
 include/sysemu/kvm.h      | 18 ++++++++
 include/sysemu/sev.h      |  2 +
 softmmu/cpus.c            |  5 +++
 softmmu/vl.c              |  5 ++-
 target/i386/cpu.c         |  1 +
 target/i386/kvm.c         |  2 +
 target/i386/sev-stub.c    |  5 +++
 target/i386/sev.c         | 95 ++++++++++++++++++++++++++++++++++++++-
 target/i386/sev_i386.h    |  1 +
 14 files changed, 219 insertions(+), 4 deletions(-)
```
