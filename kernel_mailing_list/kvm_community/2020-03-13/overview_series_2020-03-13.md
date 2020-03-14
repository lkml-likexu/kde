#### [PATCH v9 01/10] perf/x86: Fix msr variable type for the LBR msrs
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11435837
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23E38913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 02:19:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 03138206E7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 02:19:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726483AbgCMCSv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 22:18:51 -0400
Received: from mga14.intel.com ([192.55.52.115]:25868 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726461AbgCMCSv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 22:18:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 19:18:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,546,1574150400";
   d="scan'208";a="261743756"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 12 Mar 2020 19:18:46 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>, kvm@vger.kernel.org,
        Andi Kleen <ak@linux.intel.com>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Liran Alon <liran.alon@oracle.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Liang Kan <kan.liang@linux.intel.com>,
        Wei Wang <wei.w.wang@intel.com>,
        Like Xu <like.xu@linux.intel.com>,
        linux-kernel@vger.kernel.org, Ingo Molnar <mingo@kernel.org>
Subject: [PATCH v9 01/10] perf/x86: Fix msr variable type for the LBR msrs
Date: Fri, 13 Mar 2020 10:16:07 +0800
Message-Id: <20200313021616.112322-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200313021616.112322-1-like.xu@linux.intel.com>
References: <20200313021616.112322-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

The MSR variable type can be 'unsigned int', which uses less memory than
the longer 'unsigned long'. Fix struct x86_pmu for that. the lbr_nr won't
be a negative number, so make it 'unsigned int' as well.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@kernel.org>
Cc: Arnaldo Carvalho de Melo <acme@kernel.org>
Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v11 01/20] RISC-V: Export riscv_cpuid_to_hartid_mask() API
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11436095
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E06214B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 07:53:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 629822074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 07:53:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="oGaxxAFX";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="m+/EIU+8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726479AbgCMHxe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 03:53:34 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:8916 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726300AbgCMHxc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Mar 2020 03:53:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1584086012; x=1615622012;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=VzbtfCv0+v3UpQ1c6VZC9sCK2uORkqaX0W2/L7bKdDM=;
  b=oGaxxAFXbUR4SsoOlsDcqSISjB5BHxDVetQcmecL0w2248j+0Biduh2R
   Td5cIRDyw7ewx3Yj33au2DWIk8SYQPqni1gvvkItu1PVX7SHftOgqYCni
   OnSC6voM5ePg78dW0WoqHsejjdglSbTC+6ej72B8UlnNyr6fFPHjR5Kkf
   ZgIGWvYtZtCuRr5IUDZj8yq9GSAaaLgseCq7UvNIKSZIPClbuH1POMlhn
   TFrZmmwu/er0kZCP+b5p6U2r8T196w9YIug0UygLKOw3wZbG4VB4Gi2/n
   pTJAedTScOteXMIU/vnJQwp+uGkZH9/7SGuzBTqidoQc6fMKa6bnHuWnG
   Q==;
IronPort-SDR: 
 doPZgvi6EXQKQ8kQz/Lm43Y9pYqWcnHtkC2wcOoGL2yMYUVlD+Zsqn6C1yzmvOm0s+1XVZ+Rh9
 oNrDqIUtKcN1AxjhVVlTp6WCaFfkX48MHi5BiWkQZdXXvYWcp62rs+nxHBHIEtgRRGzz61A2Qf
 qJvR9ZSFbL17lOWc9UM6odcGHP5tlRH5iiR9ksRBKRqkC5PaC2W+tc9dAaL5A60mIKdNtYvOF+
 se+L5S/Xs2JGM6F/x2kD9fPDGQ3+eT5ilj+MU3pyzcyEe3Q/olOEzDXJRUhM1ZA8AFJ3WTxxUp
 ZSM=
X-IronPort-AV: E=Sophos;i="5.70,547,1574092800";
   d="scan'208";a="132827555"
Received: from mail-bn8nam11lp2171.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.171])
  by ob1.hgst.iphmx.com with ESMTP; 13 Mar 2020 15:53:26 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YycXnYiRIMecX34zj3GBYu1qW3+hzEPBCU4D8y+LQM78hfUHn2ZniOPVfYYIT85XzX2i3zSbDP9DVIeWKrc+xw0Gta+gGKa4rgHxTPdPnm2HaQueRjtMGdX4hPyoe8kCDl7UGdCVnysA0fEXF2PHCmv0FH88JI5ZhMFwGGaLsS/wPDFVrcvniowJ9r808vlIqHLjwmNMfR3lB2EuyUWWIuBOp9FiGHdOFDJ9+FCmtgAYRJIqAdjs7ZZNTXKjAs99orRwaQk1ANJPGeW5Wqel3a111+SJbWuHPKS5nHVH795kujbfjg5nRepRgvx9LakX2j/x+EUWjPgf4c1CaiIkWQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=o2MO+pNVTGhfQHncGwC2iRlM8Z70M503X3V3OHDCjZ8=;
 b=DjPJSYWk7gLurfkSAhUbHkjUUWcfk421YszSvzHuOyTSHxha8D1EvC+HonRXWPDnqOGDVg4UljO6HTH1zioRRCBpuk1Gfb3SPeDOEz/y7FK/dDcdmdFR5MFalOkxIkPCIbD6jfFoslITnphFWm+MQxbfavjwQRT7LXLjrqwIO/jqn+OzRAgT+ZxMQeN7Edh5/FU747JjheRguOF3F5fxs/7sx54MBOEB+mrEVBTgPQkdPBYYuvlo7zYPKe/ct7HjoFowPaaQ+EIApFjwLzVbKTalg/07ZTBSyIYp0E5uOzbtr8gWNP0W25SMTz9u0cFNhXLwhgYHHlQ5AzbuAsS9FQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=o2MO+pNVTGhfQHncGwC2iRlM8Z70M503X3V3OHDCjZ8=;
 b=m+/EIU+8/jri64ySiHRG+OowE4QFBvqC4CE1jPa8wXKC4/vMIWtUPkDA8hEP0Ta/rkXfB//ESdJj4w8NnRQHozdr9zLAOFHKfO7MNEMmN/Qk8KJnwKBDkxXNQe4Dgi//B9t2ebqFkYIExFfd1BAnWjr7d5rA6cmlS1Zozbeawig=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
 by MN2PR04MB6637.namprd04.prod.outlook.com (2603:10b6:208:1ef::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2793.16; Fri, 13 Mar
 2020 07:53:25 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8%6]) with mapi id 15.20.2814.018; Fri, 13 Mar 2020
 07:53:25 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Christoph Hellwig <hch@lst.de>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v11 01/20] RISC-V: Export riscv_cpuid_to_hartid_mask() API
Date: Fri, 13 Mar 2020 13:21:12 +0530
Message-Id: <20200313075131.69837-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200313075131.69837-1-anup.patel@wdc.com>
References: <20200313075131.69837-1-anup.patel@wdc.com>
X-ClientProxiedBy: MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:20::19) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (1.39.129.91) by
 MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:20::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2814.14 via Frontend
 Transport; Fri, 13 Mar 2020 07:52:55 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [1.39.129.91]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c95151df-1e13-4ab4-5867-08d7c7239ba8
X-MS-TrafficTypeDiagnostic: MN2PR04MB6637:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR04MB663794CA88D170E0CEC898928DFA0@MN2PR04MB6637.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:3968;
X-Forefront-PRVS: 034119E4F6
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(346002)(376002)(136003)(396003)(366004)(199004)(6666004)(1006002)(4326008)(8886007)(8676002)(81156014)(478600001)(7696005)(5660300002)(8936002)(36756003)(81166006)(52116002)(1076003)(44832011)(66476007)(26005)(4744005)(316002)(66946007)(956004)(55016002)(186003)(2616005)(16526019)(54906003)(2906002)(7416002)(66556008)(86362001)(110136005)(36456003)(42976004);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6637;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ICP5Ol+j6pAsVUiM9XBkTg+DMe/GC1q6Agmqm+oG9M4CnOXQ6JxZ/TyK7UvQqV2Slp+eLVnZdAeAzjcYjZkjcAF9JtYwNLxiYcvWN318X6Gm/hznPeDIFe6fqQdRLIKApWlxx1w+/fZeOEsP8Vas5laQF5qVsz+In5jfaYfEvMmjzyFo1yI4Xo9jl10sYkGVmFKsksP5JWEKucRxXaal2PVMpVjO4OlyztLgbBL+mUwlSd26S5/7Nhis9f+FNnWgBeW74+Yr9ghk/9sqvuI3FiOByKkZxWp9uwTL7FF+todIigLcFVPsrEPWE+Y0JURvdI+tFAdiFm3QiuGvk4N0BpLuc1t4EOQn5LqiqRaOTPXr1rAN0g9IZNm5yHukeVwn7TImSJWlj+zYt0Ku4aVmcNo7Gz999bU5qALPumDoBZfRlk733lAcYrnHzaqHA7JRB8YOICD7UtHWlUHtSNOUbn9LEHwFYBohr8LHtFlzBa6RcPoTNsX1cy/xteKV+FKFfCTCpoUsEIsaI+hczkB1JQ==
X-MS-Exchange-AntiSpam-MessageData: 
 hybDEmOmMVxEZi1bAp2P9aA//0zXYwkNMGlJo6ureCPbkT9XOzjO1mc598DSIGUFk5y6BjFfIYj8BJm2WSwRHt2eVs9mGu7McE3a4qePI+Dz/NRq9m4K/IOmKM2DjlCyp4Rx9h9ptpa7QMm1GtV6Iw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c95151df-1e13-4ab4-5867-08d7c7239ba8
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Mar 2020 07:53:24.9786
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 1+BnRAKISxzCyN8PHN/s/coQ+610BWKbH9EUOtseMCF2lu8zUUM8K1M6ctmuDY4dyYcqv76/V42r/iD7rciZQw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6637
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The riscv_cpuid_to_hartid_mask() API should be exported to allow
building KVM RISC-V as loadable module.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Reviewed-by: Palmer Dabbelt <palmerdabbelt@google.com>
---
 arch/riscv/kernel/smp.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: s390: pending interrupts are unlikely
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Mueller <mimu@linux.ibm.com>
X-Patchwork-Id: 11436857
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4598792C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 12:40:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2E63520724
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 12:40:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726674AbgCMMks (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 08:40:48 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:28344 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726534AbgCMMks (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Mar 2020 08:40:48 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02DCY1lh116216
        for <kvm@vger.kernel.org>; Fri, 13 Mar 2020 08:40:47 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yr0stnkwy-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 13 Mar 2020 08:40:46 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <mimu@linux.ibm.com>;
        Fri, 13 Mar 2020 12:40:44 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 13 Mar 2020 12:40:42 -0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02DCee6n20054074
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 13 Mar 2020 12:40:40 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C21F542042;
        Fri, 13 Mar 2020 12:40:40 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 739B142041;
        Fri, 13 Mar 2020 12:40:40 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 13 Mar 2020 12:40:40 +0000 (GMT)
From: Michael Mueller <mimu@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        Michael Mueller <mimu@linux.ibm.com>
Subject: [PATCH] KVM: s390: pending interrupts are unlikely
Date: Fri, 13 Mar 2020 13:40:30 +0100
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20031312-0020-0000-0000-000003B3C72E
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031312-0021-0000-0000-0000220C1F6D
Message-Id: <20200313124030.99834-1-mimu@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-13_04:2020-03-12,2020-03-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 adultscore=0
 malwarescore=0 priorityscore=1501 impostorscore=0 bulkscore=0
 mlxlogscore=616 clxscore=1015 mlxscore=0 lowpriorityscore=0 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003130067
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A statistical analysis shows that in most cases when deliverable_irqs()
is called, no interrupts are pending. (see: early exit ratio)

The data was sampled during an iperf3 run over virtio_net
between one guest and the host.

deliverable_irqs()
        called = 3145123
           by kvm_s390_vcpu_has_irq() = 3005581 (95.56%)
              by kvm_arch_vcpu_runnable() = 3005578 (95.56%)
                 by kvm_s390_handle_wait() = 1219331 (38.76%)
                 by kvm_vcpu_check_block() = 2943565 (93.59%)
                    by kvm_cpu_block(1) = 2826431 (89.86%)
                    by kvm_cpu_block(2) = 117136 (3.72%)
                 by kvm_arch_dy_runnable() = 0 (0%)
              by kvm_arch_setup_async_pf() = 0 (0%)
              by handle_stop() = 0 (0%)
           by kvm_s390_deliver_pending_interrupt() = 139542 (4.43%)
              irqs_delivered = (0:15917 1:61810 2:1 3:0 4:0 x:0)
              irqs_pending = (0:15917 1:61722 2:86 3:1 4:0 x:0)
    early exit = 3021787 (96.07%)
  pending irqs = 123237 (3.91%)

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/interrupt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: selftests: virt_map should take npages, not size
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11437321
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CC851392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 15:56:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 334A920746
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 15:56:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Evdbg7sB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727036AbgCMP46 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 11:56:58 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:59546 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727024AbgCMP46 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Mar 2020 11:56:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584115016;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=0TlnYuG1vxW9vxNmtolQqNH8uI5iJFkajryLnEBQjsU=;
        b=Evdbg7sBlPux3vw6gJkoKDcjmdB4gNiQG8o0dVt2qYt9Lix9gr94Ehw4WvN4V/1l4xR5iP
        ESdf19K7MWNx78CmsVARruf1Z7J5A3HIAzELLwR206HFwrhmqqSatnum8LlVUFliwAPHHQ
        jpBJ5EdGoDcmdG3WkuuLwQs+gDoWmgk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-280-tbd92L-sOumh-eZ3ofcpBQ-1; Fri, 13 Mar 2020 11:56:54 -0400
X-MC-Unique: tbd92L-sOumh-eZ3ofcpBQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 08C531005513
        for <kvm@vger.kernel.org>; Fri, 13 Mar 2020 15:56:54 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2E05C93535;
        Fri, 13 Mar 2020 15:56:50 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/2] KVM: selftests: virt_map should take npages, not size
Date: Fri, 13 Mar 2020 16:56:43 +0100
Message-Id: <20200313155644.29779-2-drjones@redhat.com>
In-Reply-To: <20200313155644.29779-1-drjones@redhat.com>
References: <20200313155644.29779-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Also correct the comment and prototype for vm_create_default(),
as it takes a number of pages, not a size.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/demand_paging_test.c      |  3 +--
 tools/testing/selftests/kvm/dirty_log_test.c          |  3 +--
 tools/testing/selftests/kvm/include/kvm_util.h        |  6 +++---
 tools/testing/selftests/kvm/lib/kvm_util.c            | 10 +++++-----
 .../selftests/kvm/x86_64/set_memory_region_test.c     |  2 +-
 .../testing/selftests/kvm/x86_64/vmx_dirty_log_test.c | 11 +++++------
 6 files changed, 16 insertions(+), 19 deletions(-)

```
#### [PATCH v4 1/7] vfio: allow external user to get vfio group from device
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11435891
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7154E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:17:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5B6A820716
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:17:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726426AbgCMDRb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 23:17:31 -0400
Received: from mga09.intel.com ([134.134.136.24]:6435 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726246AbgCMDRb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 23:17:31 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 20:17:30 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,546,1574150400";
   d="scan'208";a="278064811"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by fmsmga002.fm.intel.com with ESMTP; 12 Mar 2020 20:17:27 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: alex.williamson@redhat.com, zhenyuw@linux.intel.com,
        pbonzini@redhat.com, kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v4 1/7] vfio: allow external user to get vfio group from
 device
Date: Thu, 12 Mar 2020 23:07:55 -0400
Message-Id: <20200313030755.7767-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200313030548.7705-1-yan.y.zhao@intel.com>
References: <20200313030548.7705-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

external user calls vfio_group_get_external_user_from_dev() with a device
pointer to get the VFIO group associated with this device.
The VFIO group is checked to be vialbe and have IOMMU set. Then
container user counter is increased and VFIO group reference is hold
to prevent the VFIO group from disposal before external user exits.

when the external user finishes using of the VFIO group, it calls
vfio_group_put_external_user() to dereference the VFIO group and the
container user counter.

Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio.c  | 38 ++++++++++++++++++++++++++++++++++++++
 include/linux/vfio.h |  2 ++
 2 files changed, 40 insertions(+)

```
#### [PATCH v2] KVM: VMX: Micro-optimize vmexit time when not exposing PMU
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11435963
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 73CB91392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:55:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 51DCE2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:55:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="QgwHFrUh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726377AbgCMDzg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 23:55:36 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:41281 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726254AbgCMDzg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 23:55:36 -0400
Received: by mail-pf1-f194.google.com with SMTP id z65so4375727pfz.8;
        Thu, 12 Mar 2020 20:55:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=bFy5BGqYIsvQcigpiL/tId818nkLJ5jSEKOHxLuc+ho=;
        b=QgwHFrUhzfSofz5itbllISH4EH2+ljgNI0x0fmR9HiOZV4NjCYt/vTQbrXlzxCPC5F
         MHh3ReUBkwcO0DLIi/hkvWskaBT5bvfN0E/WlU9vEe5t8/J4R6lEincGPn3vjreyOx72
         WYcWN0GicThi/G8roCHyJxoEnEYyO1OtMIrvN/e7rFDI82u8EzZ5xjV63MdCmmAQZkxM
         C6icuyKtJYwwKZtuNgJJH8vElDDaJdW0iZNKQHNHZ9Uk+ThyQPPnO4fv7dvKblejMiti
         yVge5r/xFHBn+/j5BCaJKdi8LBuytjogaEPlMyqb8Q7Y/KWcK81k523QSQH7wgdQm+cF
         MBlA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=bFy5BGqYIsvQcigpiL/tId818nkLJ5jSEKOHxLuc+ho=;
        b=lyk4ysriDYHO5uvbczT9vj9mtV20afKO34FMMHBkQneH51zmxkJqoUWC88S3Bb7Clj
         HgihdPI7lcDbnFxSJUxv8A1cpMpQfwU039i9kCOwSfOehMtoEQzY5fDDYZv15uXrWLdS
         qzfh+iV5o4iKzLNQbK1T+hvV0PR4ifsjtj4c03cs8FERNntiNCBbePXL6wwfUAnmok81
         dAoVg4nvrGfnKvp5ScFvTsNUoEaMXgOGkAk/H2zFru9+2z875ea8nQcouL/BVmBJO2Xh
         zwWTPkv8/OWkcnT3hP8A8t+BZy9bLTvnm2nKW50rZ75ueM19+Nh4pnSLqSkZlLZ8ROjj
         D31w==
X-Gm-Message-State: ANhLgQ1R33xTGn+S6wAstaNX6f0BMJehSN2XVPgWOkzc+IqdLs47Toak
        uhRBO8icDpYD03wo3qnSMlc7ndZY
X-Google-Smtp-Source: 
 ADFU+vvEtxyIaqDqKWJgBRMV5ZSjK/QVfAp+w8TpRpMiFUcvCI6x5N0FZQO4poCsbcMd98aWIX1BrQ==
X-Received: by 2002:aa7:850b:: with SMTP id v11mr8012798pfn.64.1584071734727;
        Thu, 12 Mar 2020 20:55:34 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 y9sm19625326pgo.80.2020.03.12.20.55.32
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 12 Mar 2020 20:55:34 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: VMX: Micro-optimize vmexit time when not exposing PMU
Date: Fri, 13 Mar 2020 11:55:18 +0800
Message-Id: <1584071718-17163-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

PMU is not exposed to guest by most of products from cloud providers since the 
bad performance of PMU emulation and security concern. However, it calls 
perf_guest_switch_get_msrs() and clear_atomic_switch_msr() unconditionally 
even if PMU is not exposed to the guest before each vmentry. 

~2% vmexit time reduced can be observed by kvm-unit-tests/vmexit.flat on my 
SKX server.

Before patch:
vmcall 1559

After patch:
vmcall 1529

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * move the check before atomic_switch_perf_msrs

 arch/x86/kvm/vmx/vmx.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [Patch v2] KVM: x86: Initializing all kvm_lapic_irq fields in ioapic_write_indirect
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11436913
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1A5692C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:16:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 80F0B2074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:16:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OdP/QA25"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726659AbgCMNQd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 09:16:33 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:41566 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726495AbgCMNQd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Mar 2020 09:16:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584105392;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=7LrEVfZqSzW5l9b4ZSlHX3dnPgc63h+ofdKggf3vssA=;
        b=OdP/QA25McLc9wy1q4vKWQpLn4vKENsFxeNKWYTqkS01/Wx7/lfVlVSxI8Z/JK28OsuYDC
        Ep0/7L72u2ZOQLDI8MSlx86KNLRIOAOi5aFeaPSqglOd3JHa3h2nvdZfOZc/8EPngS5bla
        VlYzOLmAGliLlJ2yAYJfaPn+q478Pes=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-464-T1yMoNLHMxSWIvn3GkXIxw-1; Fri, 13 Mar 2020 09:16:30 -0400
X-MC-Unique: T1yMoNLHMxSWIvn3GkXIxw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 37BFD8017CC;
        Fri, 13 Mar 2020 13:16:29 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C96B492D47;
        Fri, 13 Mar 2020 13:16:24 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        mtosatti@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, pbonzini@redhat.com,
        peterx@redhat.com
Subject: [Patch v2] KVM: x86: Initializing all kvm_lapic_irq fields in
 ioapic_write_indirect
Date: Fri, 13 Mar 2020 09:16:24 -0400
Message-Id: <1584105384-4864-1-git-send-email-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously all fields of structure kvm_lapic_irq were not initialized
before it was passed to kvm_bitmap_or_dest_vcpus(). Which will cause
an issue when any of those fields are used for processing a request.
For example not initializing the msi_redir_hint field before passing
to the kvm_bitmap_or_dest_vcpus(), may lead to a misbehavior of
kvm_apic_map_get_dest_lapic(). This will specifically happen when the
kvm_lowest_prio_delivery() returns TRUE due to a non-zero garbage
value of msi_redir_hint, which should not happen as the request belongs
to APIC fixed delivery mode and we do not want to deliver the
interrupt only to the lowest priority candidate.

This patch initializes all the fields of kvm_lapic_irq based on the
values of ioapic redirect_entry object before passing it on to
kvm_bitmap_or_dest_vcpus().

Fixes: 7ee30bc132c6("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/ioapic.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v2 Resend 1/3] KVM: MIPS: Change KVM_ENTRYHI_ASID to cpu_asid_mask(&current_cpu_data)
##### From: Xing Li <lixing@loongson.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xing Li <lixing@loongson.cn>
X-Patchwork-Id: 11435879
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 733AF14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:14:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5C6492072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 03:14:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726530AbgCMDO3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 23:14:29 -0400
Received: from mail.loongson.cn ([114.242.206.163]:55506 "EHLO loongson.cn"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726420AbgCMDO3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 23:14:29 -0400
Received: from localhost.localdomain.localdomain (unknown [125.69.47.232])
        by mail.loongson.cn (Coremail) with SMTP id
 AQAAf9Dxn9uK+mpe1gcaAA--.45S2;
        Fri, 13 Mar 2020 11:14:19 +0800 (CST)
From: Xing Li <lixing@loongson.cn>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, maobibo@loongson.cn,
        chenhc@lemote.com, jiaxun.yang@flygoat.com
Subject: [PATCH v2 Resend 1/3] KVM: MIPS: Change KVM_ENTRYHI_ASID to
 cpu_asid_mask(&current_cpu_data)
Date: Fri, 13 Mar 2020 11:14:15 +0800
Message-Id: <1584069257-30896-1-git-send-email-lixing@loongson.cn>
X-Mailer: git-send-email 2.1.0
X-CM-TRANSID: AQAAf9Dxn9uK+mpe1gcaAA--.45S2
X-Coremail-Antispam: 1UD129KBjvdXoWrtFWktw1rWw47uFW3tFWDJwb_yoWkWrc_Z3
        W7Zws7ur4fCrZFy39Iywn3WFWFgw1UWF929r9IgFyq9asFyry5Wa9xJr9rAwsxur4qyF4r
        W34DJ34rZrnrCjkaLaAFLSUrUUUUjb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUIcSsGvfJTRUUUb48FF20E14v26r4j6ryUM7CY07I20VC2zVCF04k26cxKx2IYs7xG
        6rWj6s0DM7CIcVAFz4kK6r1j6r18M28lY4IEw2IIxxk0rwA2F7IY1VAKz4vEj48ve4kI8w
        A2z4x0Y4vE2Ix0cI8IcVAFwI0_Gr0_Xr1l84ACjcxK6xIIjxv20xvEc7CjxVAFwI0_Cr0_
        Gr1UM28EF7xvwVC2z280aVAFwI0_Gr1j6F4UJwA2z4x0Y4vEx4A2jsIEc7CjxVAFwI0_Cr
        1j6rxdM2AIxVAIcxkEcVAq07x20xvEncxIr21l5I8CrVACY4xI64kE6c02F40Ex7xfMcIj
        6xIIjxv20xvE14v26r106r15McIj6I8E87Iv67AKxVWUJVW8JwAm72CE4IkC6x0Yz7v_Jr
        0_Gr1lF7xvr2IYc2Ij64vIr41lF7I21c0EjII2zVCS5cI20VAGYxC7MxkIecxEwVAFwVW8
        GwCF04k20xvY0x0EwIxGrwCFx2IqxVCFs4IE7xkEbVWUJVW8JwC20s026c02F40E14v26r
        1j6r18MI8I3I0E7480Y4vE14v26r106r1rMI8E67AF67kF1VAFwI0_JF0_Jw1lIxkGc2Ij
        64vIr41lIxAIcVC0I7IYx2IY67AKxVWUJVWUCwCI42IY6xIIjxv20xvEc7CjxVAFwI0_Jr
        0_Gr1lIxAIcVCF04k26cxKx2IYs7xG6rWUJVWrZr1UMIIF0xvEx4A2jsIE14v26r1j6r4U
        MIIF0xvEx4A2jsIEc7CjxVAFwI0_Jr0_GrUvcSsGvfC2KfnxnUUI43ZEXa7VUb2g4DUUUU
        U==
X-CM-SenderInfo: pol0x03j6o00pqjv00gofq/
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The code in decode_config4 of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask

So KVM_ENTRYHI_ASID should change to cpu_asid_mask(&current_cpu_data)
for support 10bits ASID_MASK

Signed-off-by: Xing Li <lixing@loongson.cn>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [Patch v3] KVM: x86: Initializing all kvm_lapic_irq fields in ioapic_write_indirect
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11437523
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 429C7139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 17:38:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22A10206B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 17:38:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZqDmbPKs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726802AbgCMRiJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 13:38:09 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:41952 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726446AbgCMRiJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Mar 2020 13:38:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584121088;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=vyTSjj6dhi7L5i7AP4TVMNcNaJWuuKHcypzi7S8GnSk=;
        b=ZqDmbPKsz1ulOufRM7Gy/Eb6i76qOsf606nY5dxRDlBDwRiIfxEHpcBiQNg/MhJWRkLhb/
        jr6KD9KqfEjdcFw7rSQ1gKDtvpgKEmYBfjO2+pppUw9fyh8upwMfxPInEcUjkiN6MA+ipw
        8NZD42hOS/hYu77TArko+kalI3wqZUE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-98-baDEUYg9NMq4UH-Z6JMhIw-1; Fri, 13 Mar 2020 13:38:06 -0400
X-MC-Unique: baDEUYg9NMq4UH-Z6JMhIw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B4F7C13FE;
        Fri, 13 Mar 2020 17:38:04 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7141A60BF7;
        Fri, 13 Mar 2020 17:37:58 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        mtosatti@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, pbonzini@redhat.com,
        peterx@redhat.com
Subject: [Patch v3] KVM: x86: Initializing all kvm_lapic_irq fields in
 ioapic_write_indirect
Date: Fri, 13 Mar 2020 13:37:57 -0400
Message-Id: <1584121077-9753-1-git-send-email-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously all fields of structure kvm_lapic_irq were not initialized
before it was passed to kvm_bitmap_or_dest_vcpus(). Which will cause
an issue when any of those fields are used for processing a request.
For example not initializing the msi_redir_hint field before passing
to the kvm_bitmap_or_dest_vcpus(), may lead to a misbehavior of
kvm_apic_map_get_dest_lapic(). This will specifically happen when the
kvm_lowest_prio_delivery() returns TRUE due to a non-zero garbage
value of msi_redir_hint, which should not happen as the request belongs
to APIC fixed delivery mode and we do not want to deliver the
interrupt only to the lowest priority candidate.

This patch initializes all the fields of kvm_lapic_irq based on the
values of ioapic redirect_entry object before passing it on to
kvm_bitmap_or_dest_vcpus().

Fixes: 7ee30bc132c6 ("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/kvm/ioapic.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v5 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11436919
Return-Path: <SRS0=i7x9=46=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7DBEB14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:20:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DBA52073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Mar 2020 13:20:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="W0tsUm9Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726621AbgCMNU5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Mar 2020 09:20:57 -0400
Received: from mail-wr1-f53.google.com ([209.85.221.53]:40872 "EHLO
        mail-wr1-f53.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726550AbgCMNU5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Mar 2020 09:20:57 -0400
Received: by mail-wr1-f53.google.com with SMTP id f3so5073976wrw.7;
        Fri, 13 Mar 2020 06:20:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=0wyf1C6fvDgXY4wvk08Bh1opszF62aUSzjowFRYBQm0=;
        b=W0tsUm9ZEiiSWqRJF2QtSRp2ic9I5oBrN42Ay2dUzJXNH2i5zvlhF8sMpUcyhUJSMG
         09ZzXKETY3MQGVmzHPYzGvgUADFZqVaDq6L5qxSkRifNjdLKog4BdF7R6tTy6/kyJDXM
         PAeMCx8Kh+vIH6Bjz/NFrNiRWAyHOKKSkSoa+KxaGKhVRuz9lmWwPASsEZVMw4oCNrf4
         ariSnLtWVH7KJne+rZ2WVRQpWY0p+cP6Y0HgYS4jZ/c/NJ5rcMcPk5H0dnThDeWivT3G
         tJzXWDVd/Uvf6xo9/TE4+PXNMXDk5OS4r3b6z9KQATEsZPvOkYvl5t4jl3yE9MWq50lb
         hGZg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=0wyf1C6fvDgXY4wvk08Bh1opszF62aUSzjowFRYBQm0=;
        b=rvAOIBfUczfiWKLI62XAHQMroMbuJQUjx1BNW3Y4OccC/sgOB5MprfiT2n6FNmgwUj
         eSx39iT4KCGTqTj2JHNuXG+Z9u6f7Q9ZrPeSkTJ7n/6qi/LEAA9hy2uuaHo1+jnUe7CT
         Cmu5VEKZs7P2zHvg5M6UgI+m7pYF73cPVWGgkuVgaVpHfbqCPhYjEWhFh+t7g6BjsqQ4
         LVZ4GY1VPkrrxtnjAHwJigdexy0GYICVNiBYNKprGEB3squTh0FRdu+xHWfDhexxCD9i
         JkQVROG8dCXSkHsUVLg2kF2sV/p6xRwh1LFN4w7dy4ruwYOnrbzAWSVfQ2HRVJPCRY47
         EAbA==
X-Gm-Message-State: ANhLgQ1+VDvi/3JjRIy5OuDhTZcnEjnW69yiXyx6M8N/FmzucOcK364O
        jfeNDGjGEBCWDUJnUqjqex3YuDJcdgc=
X-Google-Smtp-Source: 
 ADFU+vtL/FpqWd63CU/2WKZIMH+tVjqqYr4tY4VTvKnceraUtMaGgJ7SseHjenin4Qdvxh57YnNuQQ==
X-Received: by 2002:adf:a285:: with SMTP id s5mr18678820wra.118.1584105656034;
        Fri, 13 Mar 2020 06:20:56 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 v8sm77112121wrw.2.2020.03.13.06.20.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 13 Mar 2020 06:20:55 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v5 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Fri, 13 Mar 2020 15:20:30 +0200
Message-Id: <20200313132034.132315-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200313132034.132315-1-arilou@gmail.com>
References: <20200313132034.132315-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 ++
 include/uapi/linux/kvm.h       | 2 ++
 2 files changed, 4 insertions(+)

```
