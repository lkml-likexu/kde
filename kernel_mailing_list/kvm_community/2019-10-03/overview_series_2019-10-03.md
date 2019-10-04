#### [kvm-unit-tests PATCH v2 1/3] lib: arm64: Add missing ISB in flush_tlb_page
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11172543
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 50FE376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 11:32:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3048D2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 11:32:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730127AbfJCLcg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 07:32:36 -0400
Received: from foss.arm.com ([217.140.110.172]:42370 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729942AbfJCLcg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 07:32:36 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id B65281597;
        Thu,  3 Oct 2019 04:32:35 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 A88243F706;
        Thu,  3 Oct 2019 04:32:34 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, maz@kernel.org,
        mark.rutland@arm.com, andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH v2 1/3] lib: arm64: Add missing ISB in
 flush_tlb_page
Date: Thu,  3 Oct 2019 12:32:15 +0100
Message-Id: <20191003113217.25464-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191003113217.25464-1-alexandru.elisei@arm.com>
References: <20191003113217.25464-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linux commit d0b7a302d58a made it abundantly clear that certain CPU
implementations require an ISB after a DSB. Add the missing ISB to
flush_tlb_page. No changes are required for flush_tlb_all, as the function
already had the ISB.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/mmu.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: arm64: pmu: Fix cycle counter truncation on counter stop
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11173055
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3824414DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 18:02:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0CFA22133F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 18:02:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570125725;
	bh=ohBL1VWJOVKtjFjS/GcN9yNCD2m7Te28r/lnMrS2YRk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=z++7/5zvEYdttrnghz+Cqpd4UybQt01gVldvE72r5jj8yfbCkMcJEwN9DR1blyVQs
	 H5S5l1Hbzhbz/ZvIP1qemGASlFpHJ0LIwkv+EhkYr/MzPzDjsB5sXFist5r3+MVSTT
	 KiSkUSWs0IfLqZH3llr+4xbf8WZTlmPNrxW0dPPM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730298AbfJCSCE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 14:02:04 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:37310 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727793AbfJCSCD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Oct 2019 14:02:03 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iG4ps-0003xB-EA; Thu, 03 Oct 2019 19:24:16 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Andrew Murray <andrew.murray@arm.com>,
        Julien Thierry Julien Thierry <julien.thierry.kdev@gmail.com>
Subject: [PATCH] KVM: arm64: pmu: Fix cycle counter truncation on counter stop
Date: Thu,  3 Oct 2019 18:24:00 +0100
Message-Id: <20191003172400.21157-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, suzuki.poulose@arm.com,
 james.morse@arm.com, andrew.murray@arm.com, julien.thierry.kdev@gmail.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a counter is disabled, its value is sampled before the event
is being disabled, and the value written back in the shadow register.

In that process, the value gets truncated to 32bit, which is adequate
for any counter but the cycle counter, which can be configured to
hold a 64bit value. This obviously results in a corrupted counter,
and things like "perf record -e cycles" not working at all when
run in a guest...

Make the truncation conditional on the counter not being 64bit.

Fixes: 80f393a23be6 ("KVM: arm/arm64: Support chained PMU counters")
Cc: Andrew Murray <andrew.murray@arm.com>
Reported-by: Julien Thierry Julien Thierry <julien.thierry.kdev@gmail.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/pmu.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v8 01/19] RISC-V: Add bitmap reprensenting ISA features common across CPUs
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11172081
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B1C914DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 05:06:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E058C21D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 05:06:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="FXyVLmWn";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="OO2JwJgX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727503AbfJCFGp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 01:06:45 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:3936 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727024AbfJCFGo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 01:06:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1570079205; x=1601615205;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=+A2ZJ1+Du23SnbGIDSEykGTOoe9pFTwS8AcSw1fUgkI=;
  b=FXyVLmWny9WWsOwjHMBzWu8kdP2Z02R7NbmDIwl8+idi3SSvz5AQbIY7
   iUSCMhyXgkEokn3zYiUQDy6NREceY+2bLbhN43ebXDYHo8CKTZcYDuIHj
   FkNxHtk0Vtockwwiof5vuQ0LKOwGe0fbJszwpgeUj5LynWR+pb9iUpgFG
   bGhjgEBugPFUfKKW2YFyZWAs7jkr+MZvD6q3qhVL2itgcAYCBbozdnJ2R
   HD+LX2xxaXKclYO5pS3dQT7ULqB+kBkj/CAt7XoWmQ1bbvIG8vmngUpJV
   X2JbNnTGaqW9yuRaC1OtontZGu+N4L0NCdOBprMFe6vwPhqSBAkC0pOSh
   Q==;
IronPort-SDR: 
 NdMo9tYXvIUOwn5GdJKOHwb/IkEbwxFCaG9hIQZqkWF3xGCuk0+LYS6zIYj20t+h82YzINjMo9
 +OVb4hEhB5LVdnDwdUsxClqw8teYPuWz/f/99YAictx42OqH8t2L8RYhx4vyslgIgny9PC05CH
 VvELTlk97o9WZdR+KsRiDyaUm0UXSzq8OHaN3gorXiRv6K+S4xq9j0Xia/O3SmozgaIpzKdxuj
 EGNNHq6i1kSGYZvPbVrTAEhKAveGgd56S62aahF4rF4UT9x81sVbdPuNzIvYQR7onsk+lgD5YJ
 gCU=
X-IronPort-AV: E=Sophos;i="5.67,251,1566835200";
   d="scan'208";a="120461283"
Received: from mail-co1nam03lp2059.outbound.protection.outlook.com (HELO
 NAM03-CO1-obe.outbound.protection.outlook.com) ([104.47.40.59])
  by ob1.hgst.iphmx.com with ESMTP; 03 Oct 2019 13:06:38 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=fXw9EQS4+CA2cM93mraUGxxOVcpxS/UV4ROvy4vhKGm406Lg2JT0A1zXI8JpFDHhhs6mvlwp8A9E/1NCwrPomSv2r7QJqwNr3mw4ncpGOvZBwHSwAHozhvWX4CCqRW0a/1ZcNGEZwCOmQV96DF4LrtG/RDyL4QSubu9DhwOGWHFUiowI418CsdnM4awDC3mt2KJuMGVeSN6eflc+JCYHKJ71Vq3intq7e5VtD91/lpMEhlaOCFw398v4rQu5Eucsos6eoOUk+Ra/n5i63HB6Umj5paoikLd6uFehxIUkFCLN2dHT/nwxVcAVO63MF574m2/smojUet/hcow0b0hNfg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+ng04hoOzq57TGmSmTLrnTpV7rjJVazlrDmWeCuRHiw=;
 b=QklvUWOmKZen3q1vc7gG0b7xdLw69dpzbFE4fkiTw6Sb+DVk0MCHtHy7mv99SJBJ3neGpLvUz01HlvQsaVKtdpwQvN91w8UXZwQSa060amj8mQpAtJ1VLFujgd60psIZoYy/Q/HNG/8RRB1buBH6kKPRwQLuXY1JDfjTkUVwxw+2Sob7j7lj4P896jSUqry1qiJzCc6SW2wmyzcnKM1Sy4EWiCA1uVugLb9Aa0wno8xdd92WJfJJLY1+LU2oC7p1Y7Vzzi9MAQaFW1ZBeyQkPmDEZjNFGSPWnwnBR9tuVBjTXeTXkLfGuEtDGbygL0qgzLhRZOcTcyymP6Huoex8hg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=+ng04hoOzq57TGmSmTLrnTpV7rjJVazlrDmWeCuRHiw=;
 b=OO2JwJgXUfvKTdxiyb7HxIS7QNjqKDx/Wj2MrQXtJBKzQf/8+0CD1sDN9yMsJFXn/qiumGOr+DQ/QEMbhI7HT8mysilxin5o6jUQ2ZYCoWOHkGKpIUfMBGmjk5fHvvsnV4lSeViHAT31UWYs3m6FLNkNVEUF/IHepbUtv5bZom0=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB6991.namprd04.prod.outlook.com (10.186.144.209) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.18; Thu, 3 Oct 2019 05:06:37 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a%7]) with mapi id 15.20.2305.023; Thu, 3 Oct 2019
 05:06:37 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v8 01/19] RISC-V: Add bitmap reprensenting ISA features common
 across CPUs
Thread-Topic: [PATCH v8 01/19] RISC-V: Add bitmap reprensenting ISA features
 common across CPUs
Thread-Index: AQHVeahV15EOT3PPQ0aY9a6zOfeW3g==
Date: Thu, 3 Oct 2019 05:06:37 +0000
Message-ID: <20191003050558.9031-2-anup.patel@wdc.com>
References: <20191003050558.9031-1-anup.patel@wdc.com>
In-Reply-To: <20191003050558.9031-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: BMXPR01CA0030.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:c::16) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [111.235.74.37]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: c53c98c7-807a-4444-1645-08d747bf77ca
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: MN2PR04MB6991:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB6991C30CDF392F653DDBC81F8D9F0@MN2PR04MB6991.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:317;
x-forefront-prvs: 01792087B6
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(366004)(346002)(39860400002)(136003)(376002)(396003)(189003)(199004)(7416002)(52116002)(25786009)(102836004)(76176011)(54906003)(6506007)(1076003)(386003)(7736002)(44832011)(6436002)(486006)(66066001)(71190400001)(71200400001)(11346002)(446003)(6116002)(3846002)(476003)(2616005)(26005)(305945005)(6512007)(36756003)(186003)(14454004)(110136005)(5660300002)(6486002)(66446008)(66476007)(8936002)(66556008)(256004)(64756008)(66946007)(86362001)(8676002)(81156014)(81166006)(99286004)(316002)(4326008)(2906002)(478600001)(50226002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6991;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 47rSjwKH9seA2/WYOnTe9bSYjQc85Q/ZbCi35nyYr1XKnrd385UtwTTD7L3PcRJTtAdlFRZ80Jr8dZMznBwD2F67quyYfqIXvXLaqjL1yaFXQ8fBB6iNRrN7iRVzMnEoAvcJHwZUoOcfShOEI8dN9KMJVF6GSTEAWW5jigOqDSRpKrvjKix2wvZcwtuT3tyiKsrdRtpc1wWaF/qKiA2c3Nh3rK4Rz9EHYmWe836MRHJylRTEefWDWq/Dj8is7zza6ms2/L5lycWTk8+R0j8ETG4GQ3gVEsc93xbaldolQmAvmEIqm9UX7hN5G7oqJaD8FOZ40dv2z4fnmmRL0RF2joIC3W1YVIfLnuRiPQdqLvdYF0DTX6zkmxSFJWF6wShLFZ36h4JayxBeCKg6XUs7tQ/iAWvnLKVN3mLuHxMVWHM=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c53c98c7-807a-4444-1645-08d747bf77ca
X-MS-Exchange-CrossTenant-originalarrivaltime: 03 Oct 2019 05:06:37.4060
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 npHe2RquDDEhjV4eYQXEvIbzFmemdbA2lw6GCf9TvegjqQfCPSYe5gP9askCkZoKterommmSdWHlIm41Sim6zw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6991
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds riscv_isa bitmap which represents Host ISA features
common across all Host CPUs. The riscv_isa is not same as elf_hwcap
because elf_hwcap will only have ISA features relevant for user-space
apps whereas riscv_isa will have ISA features relevant to both kernel
and user-space apps.

One of the use-case for riscv_isa bitmap is in KVM hypervisor where
we will use it to do following operations:

1. Check whether hypervisor extension is available
2. Find ISA features that need to be virtualized (e.g. floating
   point support, vector extension, etc.)

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Signed-off-by: Atish Patra <atish.patra@wdc.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/hwcap.h | 22 +++++++++
 arch/riscv/kernel/cpufeature.c | 83 ++++++++++++++++++++++++++++++++--
 2 files changed, 102 insertions(+), 3 deletions(-)

```
#### [PATCH kvm-unit-tests] svm: Fixed error code comparison in test npt_rsvd_pfwalk
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11172673
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7681D17EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 12:38:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5F60420862
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 12:38:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729704AbfJCMir (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 08:38:47 -0400
Received: from mx1.redhat.com ([209.132.183.28]:56014 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729048AbfJCMir (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 08:38:47 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 270E830622EA
        for <kvm@vger.kernel.org>; Thu,  3 Oct 2019 12:38:47 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-121-204.rdu2.redhat.com
 [10.10.121.204])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A25265D6A9;
        Thu,  3 Oct 2019 12:38:46 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] svm: Fixed error code comparison in test
 npt_rsvd_pfwalk
Date: Thu,  3 Oct 2019 08:38:45 -0400
Message-Id: <20191003123845.2895-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Thu, 03 Oct 2019 12:38:47 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the AMD64 spec Bit 3 (RSV) in exitinfo1 should be set
to 1 if reserved bits were set in the corresponding nested page
table entry. Exitinfo1 should be checking against error code
0x20000000eULL not 0x200000006ULL.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] vmexit: measure IPI and EOI cost
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11172781
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 818CD15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 15:24:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5FF70215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 15:24:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="g/32q7fJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730275AbfJCPYk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 11:24:40 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:46518 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727302AbfJCPYk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 11:24:40 -0400
Received: by mail-wr1-f66.google.com with SMTP id o18so3204295wrv.13
        for <kvm@vger.kernel.org>; Thu, 03 Oct 2019 08:24:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=ZRM8UhcRohD7Bt53XpU0TqsliASuoqYedkYx4gqC86I=;
        b=g/32q7fJLjKwlwfjz4nMIB0KVXyrrysPfeZ5AGpTovt0yRYceiR5zcjmIX7EkucxLG
         I1RRojWp8jfKwqdKp7yobSaXlSuMRvHOg30M1D+3EX8JsyorPRyHkjinnK+SD+PyZE/c
         XmQL2TDcSJgunD6XirGGYf3CkNl8VUOq+VylzCKz4wFbHFgvkVrIPpkoFRIn88UEUaOq
         C41YQJ1SGXIY6xUillzqoBD789LhgqsnEpwMLc7i9NpiZvBZK+/gecY/ngnKgnYP3kh5
         34QR7pwFTZvJF9kUhQpJzdJLHnGF/vrb1T3wsH4kqoVTDnY76GaOzsSXNX3nsjEGQxDl
         Tnxw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=ZRM8UhcRohD7Bt53XpU0TqsliASuoqYedkYx4gqC86I=;
        b=HMjDS0/P35ioTrvZnQdEvCd+ReGOyFa1oLrALJstWN/oR0j4vbsdhNdUZFKJzA0R5w
         Mu0dJjKZzvTwXwiYQhQHQqfErcJCNVZ9voyDXfYHuJLpvGtriB+GfGiskz0FENHJ5tKu
         Mp5N+1FQniaUwhpQzsMWfgRYJnbFTWR+bitw8LyCOZa2i9vfyIo7Td+MWpnGUnJF9RVq
         G6WAK8VXpORBsMbB1Ca5pt+h/sgi2gtc0NookATAngDO0Ia0NwTajpapKcvGEaF6699f
         lte3nd6IUB16Wu7kzcocW5D+S27IDmjVf3ZTsaetki3WisfyGHJn2x8giu9fxF6dxHn+
         8U6g==
X-Gm-Message-State: APjAAAWFBHci4pUKvdsXHxyIzpH1EE6B3mDgVHKSTLEgZE0y7Yp33Ufi
        3HrFVrFPCiViJdCgnEAIlWEarWVX
X-Google-Smtp-Source: 
 APXvYqzONuhyqR/NtrlUFzAdknQaYxBfLzty3tUjBuNFUYrBT4vRRtectyb2qjTb6oAccmEIFjHwTw==
X-Received: by 2002:adf:d1a8:: with SMTP id w8mr3145322wrc.271.1570116276027;
        Thu, 03 Oct 2019 08:24:36 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 n1sm5407670wrg.67.2019.10.03.08.24.34
        for <kvm@vger.kernel.org>
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 03 Oct 2019 08:24:35 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] vmexit: measure IPI and EOI cost
Date: Thu,  3 Oct 2019 17:24:31 +0200
Message-Id: <1570116271-8038-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
 x86/vmexit.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: VMX: Mask advanced VM-exit info
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11173335
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13ADE112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 20:47:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E5D702086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 20:47:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731413AbfJCUrS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 16:47:18 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:37126 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729193AbfJCUrR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 16:47:17 -0400
Received: by mail-pf1-f194.google.com with SMTP id y5so2498963pfo.4
        for <kvm@vger.kernel.org>; Thu, 03 Oct 2019 13:47:17 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=vDz4CNFWOTztzA1GiLBvWR2d/6AIBHLVshICPQcqmiQ=;
        b=tpS9Xyq8UxQIeioJvhHyAjd/1b0w7dxkiB4JlCUpsBHPlN9IeqV0YiIS9Am3+2ep2U
         oYpZ1Ax2M6ikdG4VRihJjXsQUF4ZsEUEIgpjZtrx/si4plvXxnPBvzWLU4Jfv4Agt6LR
         9eqtwIy6VgWUkLzhdBw74/+Jn6JqNV4Y+Ew2E+GIM4HRQnBknVXVUw5VI7NSYmz47dmK
         oBSbksdE8Q9nWAiML6dVV4QY0jbIIeTb4pHK8sWYb459SWj/2+wje1PVAJLumkw47IUR
         cfOIgUqVz0Qn+LvqKjf2rst7CpfWvUqQQnZY5BKd96CINsFeFxLaw7MLxGzXKDlqxLRC
         bfpw==
X-Gm-Message-State: APjAAAVoWzMahV+y8X2Rsf3sl9438FEsUKpMBj1ini36LcEQ3sGprJ9+
        fx8+UQ9MP/TEwo9vO8pjwCj5aw9rR6U=
X-Google-Smtp-Source: 
 APXvYqzEB7vDO7DrJWNuOzXa8QOUt1SdweDU5XBbGkmckSz/KjW6E24bo4JlLWa9Q413fYFPY7jWEg==
X-Received: by 2002:a17:90a:e50e:: with SMTP id
 t14mr13023170pjy.62.1570135636656;
        Thu, 03 Oct 2019 13:47:16 -0700 (PDT)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 q29sm6100093pgc.88.2019.10.03.13.47.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 03 Oct 2019 13:47:15 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, sean.j.christopherson@intel.com,
        Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: VMX: Mask advanced VM-exit info
Date: Thu,  3 Oct 2019 06:26:18 -0700
Message-Id: <20191003132618.8485-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bits [9:11] are undefined in the VM-exit qualification when "advanced
VM-exit information for EPT violations" is not supported.

Mask these bits for now to avoid false failures. If KVM supports this
feature, the tests would need to be adapted, and the masking would need
to be removed.

Unfortunately, I do not have hardware that supports this feature
available for my use to make a better fix.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/vmx.h       | 2 ++
 x86/vmx_tests.c | 7 +++++++
 2 files changed, 9 insertions(+)

```
#### [PATCH tip/core/rcu 2/9] x86/kvm/pmu: Replace rcu_swap_protected() with rcu_replace()
##### From: paulmck@kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Paul E. McKenney" <paulmck@kernel.org>
X-Patchwork-Id: 11172001
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00FA9139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 01:43:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CAC6A222CE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 01:43:50 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570067030;
	bh=vJactgM3M2ccX7Qs5sz0+VAKv+twysNQWUyUR3pB7oQ=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=S2Zis0nwXB6rcYGogJazRDrG0xDMEYbXtTxim4xM88z9Uy7Idt7aoS2bLIqKGcHYP
	 NPNsFmRhnbXebG0D09FjMbkZeNFLb0sC8qRY6lLmfwmfgAZaiGh+5SrjOqO/E7ONW/
	 Nlzfbitvjn3ObB3OEq77NULWa4Nie17lGODl+RgA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728294AbfJCBnq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Oct 2019 21:43:46 -0400
Received: from mail.kernel.org ([198.145.29.99]:46354 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726364AbfJCBnM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Oct 2019 21:43:12 -0400
Received: from paulmck-ThinkPad-P72.home (50-39-105-78.bvtn.or.frontiernet.net
 [50.39.105.78])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 16B52222C6;
        Thu,  3 Oct 2019 01:43:12 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1570066992;
        bh=vJactgM3M2ccX7Qs5sz0+VAKv+twysNQWUyUR3pB7oQ=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=HUiGVvKyZr1aow3e8Bar+GnMPXkDxlGJVKuQwD++B2faft524sFpkWCjhyGlatxNc
         m+ApIIqFWfp3SXG55n9nOJjt383I5KBFYF8VbHSUl0dB6uIXiMT+K5YeIVUny//ZSE
         Q2ux/Zo6uD2Q3EXPFgYdMJlcRPc69VPK5Sr6qWoU=
From: paulmck@kernel.org
To: rcu@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, mingo@kernel.org, jiangshanlai@gmail.com,
 dipankar@in.ibm.com, akpm@linux-foundation.org,
 mathieu.desnoyers@efficios.com, josh@joshtriplett.org, tglx@linutronix.de,
 peterz@infradead.org, rostedt@goodmis.org, dhowells@redhat.com,
 edumazet@google.com, fweisbec@gmail.com, oleg@redhat.com,
 joel@joelfernandes.org, "Paul E. McKenney" <paulmck@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
 "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org, kvm@vger.kernel.org
Subject: [PATCH tip/core/rcu 2/9] x86/kvm/pmu: Replace rcu_swap_protected()
 with rcu_replace()
Date: Wed,  2 Oct 2019 18:43:03 -0700
Message-Id: <20191003014310.13262-2-paulmck@kernel.org>
X-Mailer: git-send-email 2.9.5
In-Reply-To: <20191003014153.GA13156@paulmck-ThinkPad-P72>
References: <20191003014153.GA13156@paulmck-ThinkPad-P72>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Paul E. McKenney" <paulmck@kernel.org>

This commit replaces the use of rcu_swap_protected() with the more
intuitively appealing rcu_replace() as a step towards removing
rcu_swap_protected().

Link: https://lore.kernel.org/lkml/CAHk-=wiAsJLw1egFEE=Z7-GGtM6wcvtyytXZA1+BHqta4gg6Hw@mail.gmail.com/
Reported-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: <x86@kernel.org>
Cc: <kvm@vger.kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/pmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/5] KVM: SVM: Serialize access to the SEV ASID bitmapThread-Topic: [PATCH 1/5] KVM: SVM: Serialize access to the SEV ASID bitmap
##### From: "Lendacky, Thomas" <Thomas.Lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Lendacky, Thomas" <thomas.lendacky@amd.com>
X-Patchwork-Id: 11173395
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C6B213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:18:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4E4022133F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:18:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="GDhfKIGE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732237AbfJCVRr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 17:17:47 -0400
Received: from mail-eopbgr810082.outbound.protection.outlook.com
 ([40.107.81.82]:48791
        "EHLO NAM01-BY2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729029AbfJCVRq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 17:17:46 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=QcJsJ/wb9R+GB6e9CMSuKstvwwRx8QgRkq8h6YQ9VRuaHstifc9MJXczoxZoaeqIH607gQNA1wsqfVN9ktgrYXYZSURJk/Jh0qkH8SJJb1KTLFm6aA7YzeSx9mUzkU3z7E6+LbaRBe/nFXnDxpPOIe+nFm3P47k0OOSYFjWpYIR/SN9UXF5fYr88CfnWmwWarDLikA9+ASNlVNkxK4U5YzV/Augkb75qQ6J0xCdGudCMhykTPF8TQUyfiFenkJEliuMdUO/Ce48zoeV2blmkV9je30Tn+IrxH7QCXWHBlQLG3lGyg5C8S1DXhfhj8rByQECbF1cxNq3Eu0wpukvrzQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=TwqGdFpg1itFbkpP8DLz8O+PS7rEilDeb+3JTReRaBc=;
 b=LTeOYAUgGwugv9wxHrm7lxrDGp6zGhXd4cxUoWSmFmOWQycoiFLH433MNyFZa76PQzreYbNZ1t+McMSppOI3VcWpb+vc/oxANAqE/59DRxHdr7NOEnjeEJPbDzBLQuGZFquHkQClsd8bTZbdJWns+Sg/Y/DNsLzVPKPwj/PyVJYqKagTns4PzVVL1kEiaFjrbmN442jYvRt33nqc02lu9mwviQcE87ecct2YkOJwndcxy3Xr86yD4o73Du5j/IAEpcKLAof6yO4y/TigHr9bBVOaKg18ftdsckWFEu1TXsOovQpV1tbXeegKYLlB6ulIqZa0n2s3yWysUYcnSYZLag==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=TwqGdFpg1itFbkpP8DLz8O+PS7rEilDeb+3JTReRaBc=;
 b=GDhfKIGEZ5nwQ/L1mCvTiK4FF9kxu8Ls0s8o+UN61vyVR0iuP5GOC7QajUq9jnfFUX6c+rrl/NCr8IeAPzj1J0MXfv1lO98XoKGiLq3ydq/sPD2JhBPYv605YKiz6ENcwOjx/OnTtvDFjHqyhL6iK7XDScCVIif2NNlw7lXutxo=
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.104.150) by
 DM6PR12MB3115.namprd12.prod.outlook.com (20.178.31.21) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.20; Thu, 3 Oct 2019 21:17:43 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::85b7:7456:1a67:78aa]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::85b7:7456:1a67:78aa%7]) with mapi id 15.20.2305.023; Thu, 3 Oct 2019
 21:17:43 +0000
From: "Lendacky, Thomas" <Thomas.Lendacky@amd.com>
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
 =?iso-8859-2?q?Radim_Kr=E8m=E1=F8?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>, "Singh,
 Brijesh" <brijesh.singh@amd.com>, David Rientjes <rientjes@google.com>
Subject: [PATCH 1/5] KVM: SVM: Serialize access to the SEV ASID bitmap
Thread-Topic: [PATCH 1/5] KVM: SVM: Serialize access to the SEV ASID bitmap
Thread-Index: AQHVei/+q25933Ls5kKPMJeGuLAJPQ==
Date: Thu, 3 Oct 2019 21:17:43 +0000
Message-ID: 
 <0fc0372d446cb559c2a5b9389c5844df7582dc50.1570137447.git.thomas.lendacky@amd.com>
References: <cover.1570137447.git.thomas.lendacky@amd.com>
In-Reply-To: <cover.1570137447.git.thomas.lendacky@amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-mailer: git-send-email 2.17.1
x-clientproxiedby: SN6PR05CA0006.namprd05.prod.outlook.com
 (2603:10b6:805:de::19) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:182::22)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.1]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 148dcb1d-1a89-4110-811c-08d74847211f
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: DM6PR12MB3115:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB31151375AC61C9F750E15132EC9F0@DM6PR12MB3115.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:4714;
x-forefront-prvs: 01792087B6
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(366004)(396003)(376002)(346002)(136003)(189003)(199004)(26005)(256004)(14444005)(186003)(2906002)(102836004)(6512007)(99286004)(66946007)(476003)(14454004)(6436002)(446003)(8676002)(81166006)(8936002)(81156014)(478600001)(2501003)(11346002)(50226002)(71190400001)(71200400001)(36756003)(6116002)(76176011)(52116002)(86362001)(3846002)(486006)(386003)(6506007)(7736002)(316002)(25786009)(305945005)(5660300002)(7416002)(118296001)(66556008)(66446008)(64756008)(66476007)(4326008)(54906003)(110136005)(6486002)(66066001)(2616005);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3115;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 oguROAvFNbPXfce7S6Osur4tJx1YfVI6eF+iCvdWuEcP5FaNytdvwAvmC7tVDrdiLV/x2egzDA+muAaLZco6ddDvJjIPf4qJPf3qNssiDx0yXNZ72cP9lwNdZeXW1FUF30E5IBQTA91mQNKJDtFY2zdoZ5wLm4WxOYobcqhuUF9m8XJHMSF4NALh/g58RYo2jQBIF8PR9pnp2TFHp+G+TYQqPzjoLtVfNEb9O+fpkfZ2Itt61zIrUh+gLvYyCAE3ED5V0QFIPzGB9XfISmphMtmu+izdlb+j/4ge3l0jBk0LuA5vn8Fr8XYqNA8D9MduU1NQaKtmpJvVTxQRT/RN3okFjQ4F3vvEDr55JGi4XlBbqY7BvTiOfKFLeHuqpfqBdlm4mNsn00EjHNHevWBda9LUJ4B2GgrCF2tu0RiIXqU=
Content-Type: text/plain; charset="iso-8859-2"
Content-ID: <705D6201B50DD84EB66BE1753323E0E9@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 148dcb1d-1a89-4110-811c-08d74847211f
X-MS-Exchange-CrossTenant-originalarrivaltime: 03 Oct 2019 21:17:43.5832
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 D3fK5TccoWOWTxRQUVRLyme9MNEd1+DylsJzizsWPXFVUIFy86aQNXz418uTFJzGrgoRNct+BNf2/YUr1Ngjmw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3115
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

The SEV ASID bitmap currently is not protected against parallel SEV guest
startups. This can result in an SEV guest failing to start because another
SEV guest could have been assigned the same ASID value. Use a mutex to
serialize access to the SEV ASID bitmap.

Fixes: 1654efcbc431 ("KVM: SVM: Add KVM_SEV_INIT command")
Tested-by: David Rientjes <rientjes@google.com>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm.c | 29 +++++++++++++++++------------
 1 file changed, 17 insertions(+), 12 deletions(-)

```
#### [PATCH v2] KVM: x86: omit absent pmu MSRs from MSR list
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11172429
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C81C013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 10:10:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A5AA82086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 10:10:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="seTVmCw1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728660AbfJCKKY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 06:10:24 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:44894 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725827AbfJCKKY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 06:10:24 -0400
Received: by mail-wr1-f66.google.com with SMTP id z9so2251896wrl.11;
        Thu, 03 Oct 2019 03:10:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=ottjOaTEs3Ikgb7CnHP3dioI7rwiHnXtk/G5yLxaaPo=;
        b=seTVmCw1DuIF0JANo3cCvEMKzbuNRA6FupcEyAP8s+iQ44VKrfzN+QttsFwMgdYEvi
         JWawy6V9Uuy/2t3xVz/mKTS9lHiIYFvcZ26TmH9229Ab8WkIbg5K3PWhw8S21jDXG1M+
         Zegi3vYe3exoL/+Ld8mflSsckdCRJ1iFHTFKU8Va6rumr7Edid7Chc2OXs5uOBcc6wf/
         Rkh0lBsO98fXe3pF/DJWcNM5uIfZm9zwIUf+vD8lydzCGHPi6RSbVirIrGcAtHIN8QSx
         ch7CBYluAImlhLCWwquTokGx2Seh3oooWzeRxte5NFx/3Vrmo7Pu2uYmpwR8b8NW/37c
         b3FA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=ottjOaTEs3Ikgb7CnHP3dioI7rwiHnXtk/G5yLxaaPo=;
        b=hdy2PG+f5xh+GxQDsyzNjzGGTYuPXJaVBrVhAaU1OhxNLZtL+mYclA5mHfTcJOtY3u
         NSJXYPKVO1Lzn63mpdEzx5PPGbzH1e+fvNdwx+cc2n8gPdctXYMaSqez//OJMfdZO9r+
         BGwfrMRjqDO+IGdpvJDLBZTj8bNdZO/TQEn/nBhzGpTB5kmweaSehHJ+9iAOSRG5F4ry
         Hdr1/rEZ/7dWdSh17DrIImFmK2nFhzPUFP1ELvGPt1GWUgMlxz84e4x4tja5o4ZPhuy9
         KQgJBkHl6v9CTiqMpSevqgDOmXBT9G65Wgj0/VyJZehasBhl9BJy6vUvdZAXZzrXn/aI
         81Aw==
X-Gm-Message-State: APjAAAWERNdEASr0nLxM3N3BOdTIfhTyezhxRS4rfRXenJsVhm+8aM12
        fRITVM1Z3fYgFDNRIq+ZVnJOQcm/
X-Google-Smtp-Source: 
 APXvYqzwwBM7nhU8aTEIMRdR49D+1r0ygejlqnwQRZf0IJ0xhbv8FN6y/iMkGbXaYlnQCQuHGc6nBw==
X-Received: by 2002:a5d:4b46:: with SMTP id w6mr6827233wrs.223.1570097421982;
        Thu, 03 Oct 2019 03:10:21 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 r20sm4003148wrg.61.2019.10.03.03.10.20
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 03 Oct 2019 03:10:21 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Jim Mattson <jmattson@google.com>
Subject: [PATCH v2] KVM: x86: omit absent pmu MSRs from MSR list
Date: Thu,  3 Oct 2019 12:10:18 +0200
Message-Id: <1570097418-42233-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INTEL_PMC_MAX_GENERIC is currently 32, which exceeds the 18 contiguous
MSR indices reserved by Intel for event selectors.  Since some machines
actually have MSRs past the reserved range, these may survive the
filtering of msrs_to_save array and would be rejected by KVM_GET/SET_MSR.
To avoid this, cut the list to whatever CPUID reports for the host's
architectural PMU.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Fixes: e2ada66ec418 ("kvm: x86: Add Intel PMU MSRs to msrs_to_save[]", 2019-08-21)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 14 ++++++++++++--
 1 file changed, 12 insertions(+), 2 deletions(-)

```
#### [RFC PATCH 01/13] kvm: Enable MTRR to work with GFNs with perm bits
##### From: Rick Edgecombe <rick.p.edgecombe@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rick Edgecombe <rick.p.edgecombe@intel.com>
X-Patchwork-Id: 11173453
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B7D815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:40:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E838E215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:40:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388735AbfJCVkA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 17:40:00 -0400
Received: from mga09.intel.com ([134.134.136.24]:52653 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387926AbfJCVi7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 17:38:59 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Oct 2019 14:38:57 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,253,1566889200";
   d="scan'208";a="186051615"
Received: from linksys13920.jf.intel.com (HELO rpedgeco-DESK5.jf.intel.com)
 ([10.54.75.11])
  by orsmga008.jf.intel.com with ESMTP; 03 Oct 2019 14:38:57 -0700
From: Rick Edgecombe <rick.p.edgecombe@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org,
        linux-mm@kvack.org, luto@kernel.org, peterz@infradead.org,
        dave.hansen@intel.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, keescook@chromium.org
Cc: kristen@linux.intel.com, deneen.t.dock@intel.com,
        Rick Edgecombe <rick.p.edgecombe@intel.com>
Subject: [RFC PATCH 01/13] kvm: Enable MTRR to work with GFNs with perm bits
Date: Thu,  3 Oct 2019 14:23:48 -0700
Message-Id: <20191003212400.31130-2-rick.p.edgecombe@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191003212400.31130-1-rick.p.edgecombe@intel.com>
References: <20191003212400.31130-1-rick.p.edgecombe@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mask gfn by maxphyaddr in kvm_mtrr_get_guest_memory_type so that the
guests view of gfn is used when high bits of the physical memory are
used as extra permissions bits. This supports the KVM XO feature.

TODO: Since MTRR is emulated using EPT permissions, the XO version of
the gpa range will not inherrit the MTRR type with this implementation.
There shouldn't be any legacy use of KVM XO, but hypothetically it could
interfere with the uncacheable MTRR type.

Signed-off-by: Rick Edgecombe <rick.p.edgecombe@intel.com>
---
 arch/x86/kvm/mtrr.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
