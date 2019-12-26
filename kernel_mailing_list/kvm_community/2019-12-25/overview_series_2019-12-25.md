#### [PATCH] KVM: nvmx: retry writing guest memory after page fault injected
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11309923
Return-Path: <SRS0=OhkM=2P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 515111395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 02:20:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2C0B720679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 02:20:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726284AbfLYCUH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Dec 2019 21:20:07 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:44692 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726259AbfLYCUH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Dec 2019 21:20:07 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id ED51ABED064994ED5F36;
        Wed, 25 Dec 2019 10:20:01 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Wed, 25 Dec 2019
 10:19:55 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: nvmx: retry writing guest memory after page fault
 injected
Date: Wed, 25 Dec 2019 10:21:41 +0800
Message-ID: <1577240501-763-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

We should retry writing guest memory when kvm_write_guest_virt_system()
failed and page fault is injected in handle_vmread().

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/nested.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [kvmtool RFC PATCH 1/8] update_headers: Sync-up ABI headers with Linux-5.5-rc3
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11309951
Return-Path: <SRS0=OhkM=2P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 171A8138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 03:00:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD68420679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 03:00:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="S0+GOOo2";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="U3pjF0Rl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726832AbfLYDAT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Dec 2019 22:00:19 -0500
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:60709 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726317AbfLYDAT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Dec 2019 22:00:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1577242819; x=1608778819;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=9uAyxwPTbPHGRWGGdDPJKb3hPSPge7ga0ymvBLIQCjE=;
  b=S0+GOOo2vN3Yr6OKSD9k18IsTx1YW6CdnF5jccRNljEUutDqb5G3qHGr
   Z6AA3c42A43ZjAt7w9x2zDdIjuGKLR/7/0CjU1SCE2P/kIcWXJXNX2y6q
   xA6B1D5VS18koMsCpnegdnP8v7BR13SjOUt7UB6YoARUaZFYs7mqxTWdq
   xRCytkS5Cg3DYEYLSXdn06nSu/l3somdzv1xozae7IfPMTWL7QOAWaAdO
   ecoio5lkJegP4f75x571hdhyK/7ijMly7vl3GPNet7eFIFhkFcW9BnZpE
   wHu8S2S1T4lf6F8XShNO5xerh69ml8QMA88S7Y6vtrwQ6GIv9r1RzUXRj
   g==;
IronPort-SDR: 
 LH712Gpc6U3n+Ulc2gPtcmatOPC1xodPRTZg9R7Ipf/RoCi9mqvR3Pn9b9NPjcGMyvxJiEhghj
 Dgu/BpW9r8dQbHCAfQvZi7Sc69Kd4ZzbYRIKngODyoHTezf02ZMmfKmWM8x3TmDnWXd5Z43iJ6
 7TvyKEMS3ZnpzJe3FUYrMJIHuqcBJnCjRZI2SpuF2Z5UUR+sB5anBHLw8KJSNflcp565fgzAvt
 4Kv+XrVXCCeUQRbSWfpoZ8S9pNlM5ZXVkefke3bnFN0ETgIlQUv7bKn+YMXLW/GJLcW7GLB7ne
 xsY=
X-IronPort-AV: E=Sophos;i="5.69,353,1571673600";
   d="scan'208";a="126854665"
Received: from mail-dm6nam11lp2174.outbound.protection.outlook.com (HELO
 NAM11-DM6-obe.outbound.protection.outlook.com) ([104.47.57.174])
  by ob1.hgst.iphmx.com with ESMTP; 25 Dec 2019 11:00:18 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=H+/qn4Ay2hGS43yJ+anl30egcs5YoEHV+BjATt640ym5+AOMWKfRv5TpwOjALf/IDSOwR0WmubL/maLDy8ZiTGk7wdE0biV78AbAqjaQOgbFDLjfKb+GcNSrXy59t+zKE736MeqxBytlz2GMb5MyJL+fcrIs28LW06ZbTtJWYD6XlxcZFeMgQXaq3sQAWWVt67bmbl5J5UKcJ7BL7U52WrqR0efi7opNhCDo9eB3pOJXJtLJZ6BD0JdDn13oMYOL5xGwjf+dprAE7jhsErfsPTE5MMjaMysJkIRZCvppTS60WkUiFKy6lh69MVJl01FBxiycYyr1iFG/lMZBFK/Nlg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z4YkFa03dgbiSlO2HLH5jlHKon49iUZYuIiYSldGZj4=;
 b=Jp4CmZ0iastWzt+F3JGe598xm9iBI/JSaFrp+EHLZ46Gjomu5xpbRRF/IEW2j9uAXSCiC3tPh5ylc3V0syvbrRPE52pMXkDOYa9Ndj45Z1EqnBtDaGOBXSO3mflbVRNzFjVT4p+KSkFHLmJ1/oSIxWYd1FUgmCSdBMBb91PNtr0wUnPSUUdTl0uR7UOBtAMUl/rEp0M/a4Jh5qMLyg/VS3GZuVnB5l0czy5zw1T+1JjZ2jHeis+Pta8R8rn8leBYzJ7BR6p75Mt3Z7isTFjkSF8gl/uZWA0ZjNQTu3zM9Znc5blCKl2k2n7X78cA4Nk9+enizqq3Wmojsmc8X2jymw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z4YkFa03dgbiSlO2HLH5jlHKon49iUZYuIiYSldGZj4=;
 b=U3pjF0Rl9IgKQzVW7RksA2B3P7DP+I4X2yL0WDpjLsa9DewuO2hn/lNHh10CA4ExlcKvS/jCwdjR3vK3jQLpklMzEzm7D8LFAM3L8De0RbnQzFY2Jo6cDRWisGNPmGf39CLeI3N6UmMQ/m4DEuAAvHoUIT5LMe17VE0O7Gg0TQg=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB5597.namprd04.prod.outlook.com (20.179.22.21) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2581.11; Wed, 25 Dec 2019 03:00:16 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89%7]) with mapi id 15.20.2559.017; Wed, 25 Dec 2019
 03:00:16 +0000
Received: from wdc.com (106.51.19.73) by
 MAXPR01CA0084.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:49::26) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2581.11 via Frontend
 Transport; Wed, 25 Dec 2019 03:00:13 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Will Deacon <will.deacon@arm.com>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "kvm-riscv@lists.infradead.org" <kvm-riscv@lists.infradead.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [kvmtool RFC PATCH 1/8] update_headers: Sync-up ABI headers with
 Linux-5.5-rc3
Thread-Topic: [kvmtool RFC PATCH 1/8] update_headers: Sync-up ABI headers with
 Linux-5.5-rc3
Thread-Index: AQHVus9uADFpxo6O5U2AUwBDP3nTWA==
Date: Wed, 25 Dec 2019 03:00:16 +0000
Message-ID: <20191225025945.108466-2-anup.patel@wdc.com>
References: <20191225025945.108466-1-anup.patel@wdc.com>
In-Reply-To: <20191225025945.108466-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MAXPR01CA0084.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:49::26) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [106.51.19.73]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: f7e844bd-5c75-4b88-7276-08d788e69141
x-ms-traffictypediagnostic: MN2PR04MB5597:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB55978D5496B0D77AF67504598D280@MN2PR04MB5597.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:541;
x-forefront-prvs: 02622CEF0A
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(136003)(346002)(376002)(366004)(396003)(199004)(189003)(5660300002)(86362001)(2906002)(4326008)(54906003)(81156014)(81166006)(66946007)(8676002)(1076003)(6916009)(8886007)(71200400001)(44832011)(66556008)(64756008)(1006002)(66446008)(52116002)(66476007)(55236004)(7696005)(16526019)(186003)(316002)(26005)(55016002)(956004)(2616005)(36756003)(478600001)(8936002)(32040200004);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB5597;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 8t55IRsfi4HazG5qDB9JMlIcAUhVvMou2qB/lMGSNAM/IzLlVi4sDqk1ziRqwt/WG2OOv/xSs/foB58Lc+RZ24bFQuc6DykJc+BPYreATXmyxeGMBWdT+6UCWOydxysHkeGDr6FcRY79sdb+4JOut910gfCBwxOcZaENk1axR0KHVqt9aafnaxUFWTbTacHcCpk1slliXxG1cQWx0iMh59JRAsatzElmBgN4oV+DqD9LRS3cNmHMyBExEJInlC7iU+wg2EymOal3NPtaPyIOiYiLAnIGSBBioVsVzH13BKKqgeZYaUaBmAT7Mkt944xUWpRCbexYrdXgCty1rLfwN1q1Oa2ifviKAR2SDYp9y5kvnzG2e8+IeZ+338bAoTESzU5K+fy4+9WlYbt688v+jpO24B4AuwSzYsPD4IIrqM2waAlZGkhtPA/zzKeEsT1pfd1tyElHD+gjjSqNPbHh0796E6MQTvj3p3OwpsQ967bcAuggH/wx1jAsmb+wQtjB
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f7e844bd-5c75-4b88-7276-08d788e69141
X-MS-Exchange-CrossTenant-originalarrivaltime: 25 Dec 2019 03:00:16.1353
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 8PIDA/UNSpmsZN1oBYDa7UVzpOxGqbcMbtGzMXnoqfipAQUnvrDAWZDE5wLRLMB9BV6jDc80/7uUt4yrF+12Nw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB5597
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.5-rc3. This will allow
us to use ONE_REG interface for KVMTOOL RISC-V port.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch32/include/asm/kvm.h |  7 +++++--
 arm/aarch64/include/asm/kvm.h |  9 +++++++--
 include/linux/kvm.h           | 25 +++++++++++++++++++++++++
 powerpc/include/asm/kvm.h     |  3 +++
 4 files changed, 40 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio-ccw: Use the correct style for SPDX License Identifier
##### From: Nishad Kamdar <nishadkamdar@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nishad Kamdar <nishadkamdar@gmail.com>
X-Patchwork-Id: 11310195
Return-Path: <SRS0=OhkM=2P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D46B13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 12:21:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E3B272072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Dec 2019 12:21:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="OMG2oDNk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726397AbfLYMVI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Dec 2019 07:21:08 -0500
Received: from mail-pl1-f193.google.com ([209.85.214.193]:45643 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726106AbfLYMVH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Dec 2019 07:21:07 -0500
Received: by mail-pl1-f193.google.com with SMTP id b22so9420881pls.12;
        Wed, 25 Dec 2019 04:21:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=date:from:to:cc:subject:message-id:mime-version:content-disposition
         :user-agent;
        bh=Wnv0YtxvwjhRCPhA4AJ3WaBp5/g5a1eicQCrc+kMTmY=;
        b=OMG2oDNknz48cEtssDl/vVCwRTDpy4JZD7NsViNt1A+1tVmxUvamS9au6lXuwsfsbb
         xo7sYco5GmLylmIKjvVYxQbeDWo7CINAyrGKej02lF1ONZc7Ij+iiWgI0fvXGFVf7JIa
         Qj2XJgg5U2BXd7VaXEQQaMqF66hMrscytGmNF2e5U1AIxdXFYRRuLw2HOn8tCGywk/Ms
         6GJBKQjpjpc08ZZvU/gqtKv+992lHA4zqnlBS9hEkNo2vVG8z+/XPDB1Z+YjCt7hVThR
         DO76tUarJfoxdKwQ0ewdU7FW+XrT4fVhFo0KeJgFhk0EK9f4IOaWflpfWJQnNEPLKrVb
         wQdw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:user-agent;
        bh=Wnv0YtxvwjhRCPhA4AJ3WaBp5/g5a1eicQCrc+kMTmY=;
        b=swTZun40150ZKGhmHR1Xj73bjh5ha/iw13nyjwS41lG4a/RVMG4cw/gfYOmpH9g7I4
         QsuoIU3U02i0G7vxV5eodK3w9MpuAq7nu+Bsph3Hqgo1+wT9sMvPvjhjcauDt/shDl1Y
         N1AO3V7rxIRqUehnziNt4//9YhuVzdPdp0KV3ndAEx6J0ETB0WZoq4dvTAVFeOD49A5p
         NeDqBObrmqFuaCcMPY3TbnRRl59hR7+kWbOucNXqxF6YLODnhIXvPJapt8C+uPxiuU9F
         woCpPmrHRJ3HpkSB3zmcEF1Px2oFDNVNiGp/h1ntCXmx16u1PZY3q8HOX7li3U0a6LJj
         T1tQ==
X-Gm-Message-State: APjAAAWWfQD+/c987CkrJbhWV6Oc2gTCZSjH4aap82MCTJk5B02nC6/s
        rtsCoDNYiAR6MDOjPC8qRa0=
X-Google-Smtp-Source: 
 APXvYqy58ZqVkaIvHcFkCrMhdICYlw646jVoZnTKQnvdCw8RedHK5kwZitO2+Q0vWLmz8BO97emiag==
X-Received: by 2002:a17:902:74cb:: with SMTP id
 f11mr39713272plt.139.1577276466677;
        Wed, 25 Dec 2019 04:21:06 -0800 (PST)
Received: from nishad ([106.51.232.103])
        by smtp.gmail.com with ESMTPSA id
 b65sm30400263pgc.18.2019.12.25.04.21.02
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Wed, 25 Dec 2019 04:21:06 -0800 (PST)
Date: Wed, 25 Dec 2019 17:50:58 +0530
From: Nishad Kamdar <nishadkamdar@gmail.com>
To: Cornelia Huck <cohuck@redhat.com>, Eric Farman <farman@linux.ibm.com>,
 Halil Pasic <pasic@linux.ibm.com>, Sebastian Ott <sebott@linux.ibm.com>,
 Peter Oberparleiter <oberpar@linux.ibm.com>,
 Heiko Carstens <heiko.carstens@de.ibm.com>,
 Vasily Gorbik <gor@linux.ibm.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
 Joe Perches <joe@perches.com>,
 Uwe =?utf-8?q?Kleine-K=C3=B6nig?=  <u.kleine-koenig@pengutronix.de>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vfio-ccw: Use the correct style for SPDX License Identifier
Message-ID: <20191225122054.GA4598@nishad>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch corrects the SPDX License Identifier style in
header file related to S/390 common i/o drivers.
It assigns explicit block comment to the SPDX License
Identifier.

Changes made by using a script provided by Joe Perches here:
https://lkml.org/lkml/2019/2/7/46.

Suggested-by: Joe Perches <joe@perches.com>
Signed-off-by: Nishad Kamdar <nishadkamdar@gmail.com>
---
 drivers/s390/cio/vfio_ccw_trace.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
