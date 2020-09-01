#### [kvm-unit-tests RFC 1/4] arm64: Move get_id_aa64dfr0() in processor.h
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11746905
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4A14109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 19:34:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B19122100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 19:34:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZEVX7Vb8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729259AbgHaTec (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 15:34:32 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:22754 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725872AbgHaTeb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 15:34:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598902470;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=vtLyg6lCGileigLzG/AbjWIpEiRqxpxwtXfCaWYW4BQ=;
        b=ZEVX7Vb8OGsWmdTqUo2StbwPKBbC1YQdExZJ4AqWa1I3n5GysXiZ2NfLxCy7FWEk9A03wh
        6zCj5uC9wPUaDBXd6oriTXjrqHyn7vaCic9xemHIW2CjqK2WWEEzRGS1SP4hYM3KP7pQyt
        IqQQKvcjQ+3eSn9nYOxbbb9sJh9vkW4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-212-IZETdFkBPgyuFjCOujLmHQ-1; Mon, 31 Aug 2020 15:34:27 -0400
X-MC-Unique: IZETdFkBPgyuFjCOujLmHQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7FF6A802B49;
        Mon, 31 Aug 2020 19:34:25 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-112.ams2.redhat.com
 [10.36.112.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DB7637EB7D;
        Mon, 31 Aug 2020 19:34:22 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        qemu-devel@nongnu.org, drjones@redhat.com, andrew.murray@arm.com,
        sudeep.holla@arm.com, maz@kernel.org, will@kernel.org,
        haibo.xu@linaro.org
Subject: [kvm-unit-tests RFC 1/4] arm64: Move get_id_aa64dfr0() in processor.h
Date: Mon, 31 Aug 2020 21:34:11 +0200
Message-Id: <20200831193414.6951-2-eric.auger@redhat.com>
In-Reply-To: <20200831193414.6951-1-eric.auger@redhat.com>
References: <20200831193414.6951-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We plan to use get_id_aa64dfr0() for SPE tests.
So let's move this latter in processor.h header.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 arm/pmu.c                 | 1 -
 lib/arm64/asm/processor.h | 5 +++++
 2 files changed, 5 insertions(+), 1 deletion(-)

```
#### 
##### 

```c
```
#### [PATCH v14 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11746287
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D35813B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:30:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2ADFA2100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:30:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="hr+5a2aS";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="dBezeKVm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726946AbgHaMau (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 08:30:50 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:55064 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726839AbgHaMat (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 08:30:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1598877049; x=1630413049;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=EK/5efwN5ctponF7YeDfvp60Cq6LVz8yReJHQCaEMVs=;
  b=hr+5a2aSQ/UhuS94Ts/sJqqKRhr1Cdz6I8AZTHOprK11Y39g0OnaXlJt
   kAAjBb7jKgBMXCTd5QdU5DjGnInvU1yt+8GkONcMwUSgZMb8Lfg0Zlqy/
   fKD0HJegYrZnGWxuzNUVg5SYg1A0w2cGVpwt83+hZAMHOpp5dlKH/f0tA
   UZL4sOGN/xSE2W9gLAdfzAUigN1ZGbaFeXT9LY/qqlvH4rBHlhfhkBIbi
   Vjl35FqGNIYWp0mJCILw6MX4E0EwYib67zUsL27BHdFpndQbKzoMqY6W6
   KVnUHMl18G8rTe9uuTWt7viry+VFlUrvhhPynK+Qfdt7WeBXXl6Uxe3Mq
   A==;
IronPort-SDR: 
 vJoK5tXk82fIl3IGUZDJF4Jog4PhSpdrVY0roLtULV88kXV0qsIy/8RqlJGkP5woXBj3mtvEHA
 Qm0cWPiATGdMECteutlxupMD9OXGEh8K1xp1tBAqvw+fBdet3BNzJpwil8KdPAsYOU5+Na6eWv
 nbVOq/p4LIOaqc/Mfox4u+QEFB2cwYz2QbvztWmPYrjHe2Ug1vlWNa7RIlvfCc1ysCBsoxWDp3
 0QG7e/eq1hP86Dl5aIDnQxek/94DmM9BYY9cxEm3+6T/tWxR7h7ydPz1HpvZ7NV6gmVpCpZ9G2
 ZE8=
X-IronPort-AV: E=Sophos;i="5.76,375,1592841600";
   d="scan'208";a="146216609"
Received: from mail-co1nam11lp2175.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.175])
  by ob1.hgst.iphmx.com with ESMTP; 31 Aug 2020 20:30:48 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gOZGULF2E4kwWbgNtkSuxovjyDHhqXO9bOonUxNTDxhQgAKm4pLiL2+2NZ1G2Zs5VEPS72TYhZ5YSAnl78Q+AZmdDu0By2YspWxhTY9W+J73AlibrI68fJQ4kL3EFxxyWg6SLs80xk6woHn+dVdT6kz9D7xV0XelLKlzC43l8bFzgbYz5pnvFgrEl0wrU5PtpZjnsjw51hDvSRPTZZ1pI4VBlpY4IT039cvEz1jyyvftRZJTqpAIrqaYonN+/uHU8K7J2QjSd+gZuRcPyEyiM2fvXN2KHqnCBMKs3wfUU7sSUagZJX7wazxumAfwykaN9cHBPdiPKNXI8gVNwYTePQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=YGdHaF3ApP4LiytUu5xCwY7L9Rysh3KUYQjuIUHSHTQC/96r76sJ3WZ7Nset9XuAO+giJA4JKiB1rzsNLGlbb+rA39auriDlXoyw3xHXzGf3bMSQtKd8pSywEar05MEXTDRXpFgCVGEKt2l7EFSQHv8xKN2RWwRLdzq0akXPeFgmhFtYr8te7Z61C0dBh8v11qKp3Udpa5fi7QIiSrfck/6IPGbG6fDmxTkWJAPezflLuTwjU80t745TYspUwPZU0dvLTqTQ9G8e72KfhkAf768wK7m2h/PR3vSj34AZWrbZP/J8NZEXEi9dYfFsg4csCwhhmK5tr0TX3/H3ozsFcA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mHs+gj89i8AEy86hjmH6iBGFS+byJUeIDojUGHCPg8A=;
 b=dBezeKVmpbQe1gDmXG/u4dgBvFHhxHbdRi2B1jLOVTnz2F2lNb1vujXn7YxS/4dtbdafuU0J7mBpfoJpL25Cz7GMdw5YTYkHBUXXW1De2Y8EOgJtkDFKsDt3PGL6tlPmV3ayGmxmJXZbN3+2k7vfUjdFt5GLKwtyyxzDm2KbyCA=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB6124.namprd04.prod.outlook.com (2603:10b6:5:122::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.24; Mon, 31 Aug
 2020 12:30:45 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::607a:44ed:1477:83e%7]) with mapi id 15.20.3326.025; Mon, 31 Aug 2020
 12:30:45 +0000
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
Subject: [PATCH v14 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Mon, 31 Aug 2020 17:59:59 +0530
Message-Id: <20200831123015.336047-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200831123015.336047-1-anup.patel@wdc.com>
References: <20200831123015.336047-1-anup.patel@wdc.com>
X-ClientProxiedBy: BM1PR0101CA0046.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:1a::32) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 BM1PR0101CA0046.INDPRD01.PROD.OUTLOOK.COM (2603:1096:b00:1a::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.19 via Frontend
 Transport; Mon, 31 Aug 2020 12:30:40 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.192]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 111eed40-5136-4444-2561-08d84da9aec2
X-MS-TrafficTypeDiagnostic: DM6PR04MB6124:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB6124126E9DFEA9F91B141F528D510@DM6PR04MB6124.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 yTZiYn+oYgl1FaJawd3WSM2ZsiQsKBp2usOUmsG9uZzLTTjM2rCJQN+6gze1sOROSigsC0IIrcWe43luy+XskZ3Wdd1fFzip3NqsW07rtEDKdXsFw6ef2FiS41uPdedzsLd2et+FLHnYSAm4kip90b0e8R74G4H4+E7zzbwrH3Q5c/Z3CTgsgSxSNTgxubU9CG7i9a+OrG2SKTVVz0qnXazN4eZRnKaCPNAwZhD9eo+bb4ALdB2aci0WQJAYxGjQQ7LYYse9lUE9pLYhDQioH2hnsAIWH0zDhgq0ySYSDxDdzZItj/NgpuOUp+wn38I0iwgSxg8J8sYVk1U9s63nmA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(39860400002)(136003)(366004)(346002)(396003)(8676002)(8936002)(478600001)(52116002)(86362001)(1076003)(54906003)(7416002)(110136005)(6486002)(66556008)(36756003)(5660300002)(66476007)(4326008)(2906002)(66946007)(2616005)(6666004)(26005)(956004)(316002)(83380400001)(16576012)(186003)(44832011);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 JcEwOlB7mfrWzdfIbavMmV3iwXYzkfrGflaTTsvmZ7EYqxsllh04fJeOxGF056e+Infwp7ouQxz9CXZ/GnsR5JXy6qGtvyK1un6Uq88VtyKBuQ94jLgLK/Q9oJMuHYcL41+2vw6oHub4b8GO0Iv9LjgF1w5TklXWnYv8xZmARTD8ELq/QDL9LOEEL0YvJeUDWogUT+viCCLu/OILpgmjoimAhNV/Jnwkw1TCpiEEupLsdWmOI96ukYLEwlpwpZSUUkTh3zaBWvsomKG3UMVxYePRy/dwJl6j3r+57S2l69Ag0yk23igsXiAuEgbc6iErF+VhdS0+WH5rggBmltojHl4TJSPKCfFM8pRNO15D7xxId8VFv535fSKKdIfvtvKdAIvXX1ySs7FCcnc6Ptbm/SVnLsxVJYX33PfzAKOKsK+1WeLSB+vGvEy43yDkyQnr0fPxN5sg2kg7RvBFYfzB6SEawgrFcP+Tf/qJ80CHjjt0lR7MOaC0loHuwIaNuTR0dMMRiOJohefSCx3UsFJgqOfEf1geLn30KzJNdObi3oYXgueUVAepuTX6XctQxahQuiDDeg4VM5S4SIwsPJU5P4KcRc0ZateiB/YbLD6//8mFt4gwfyB5jzFJ7e+i7zb5Vj4gUbTAfFEOW04oN49TVw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 111eed40-5136-4444-2561-08d84da9aec2
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Aug 2020 12:30:45.1474
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 m6WE+azM8qOSZ3tvOQbuSob1gWsdMw8BOtC07ix21x+AI2UKC5P8h1gr/J4lyMZZ2b4wsiFX67Zv10Y/Nq+GtQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB6124
Sender: kvm-owner@vger.kernel.org
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
#### [PATCH tip/core/rcu 17/24] kvm: mmu: page_track: Fix RCU list API usage
##### From: paulmck@kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Paul E. McKenney" <paulmck@kernel.org>
X-Patchwork-Id: 11746799
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A15EB109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 18:03:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BA7D20E65
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 18:03:36 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1598897016;
	bh=G1iH+/QCY280fAQFzIdvytLD1XQc88ODiVu9Ro09iw0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=zjX4EKQte8uys2r17GE7aigXl6vY94a2IJM/nMM/230f6TE8Ci6vVS7GuuwyZAiwL
	 0U+KFgVVonc3wF3/gAxFqWerxBBs6P4cMnTEDRSalf/P7m7iaqgxzrbtu6R4ZlEt0f
	 AiEY2NwtM3Mg6FU5qULEqsx3ks5gaKNm8zbUD2SM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729180AbgHaSC4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 14:02:56 -0400
Received: from mail.kernel.org ([198.145.29.99]:36290 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728815AbgHaSB0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 14:01:26 -0400
Received: from paulmck-ThinkPad-P72.home (unknown [50.45.173.55])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7E4432168B;
        Mon, 31 Aug 2020 18:01:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1598896885;
        bh=G1iH+/QCY280fAQFzIdvytLD1XQc88ODiVu9Ro09iw0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=DU8uCbCylnrnZOH8dD87Y+JCYVHjfpJYEwY5+H/xHHdfEmrR+irf4GbMQZ6sHgjcV
         78yp/HohQdx54beSNjuMFkBvuXtDaKBYL0tczVVeZ/F5YHyea6TlDDfdFornMLz9Bj
         fUdXBLg3+3KEXU+EYH5ease/PcanM7FNGpu5ofJ8=
From: paulmck@kernel.org
To: rcu@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, kernel-team@fb.com, mingo@kernel.org,
        jiangshanlai@gmail.com, dipankar@in.ibm.com,
        akpm@linux-foundation.org, mathieu.desnoyers@efficios.com,
        josh@joshtriplett.org, tglx@linutronix.de, peterz@infradead.org,
        rostedt@goodmis.org, dhowells@redhat.com, edumazet@google.com,
        fweisbec@gmail.com, oleg@redhat.com, joel@joelfernandes.org,
        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>,
        "Paul E . McKenney" <paulmck@kernel.org>, kvm@vger.kernel.org
Subject: [PATCH tip/core/rcu 17/24] kvm: mmu: page_track: Fix RCU list API
 usage
Date: Mon, 31 Aug 2020 11:01:09 -0700
Message-Id: <20200831180116.32690-17-paulmck@kernel.org>
X-Mailer: git-send-email 2.9.5
In-Reply-To: <20200831180050.GA32590@paulmck-ThinkPad-P72>
References: <20200831180050.GA32590@paulmck-ThinkPad-P72>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>

Use hlist_for_each_entry_srcu() instead of hlist_for_each_entry_rcu()
as it also checkes if the right lock is held.
Using hlist_for_each_entry_rcu() with a condition argument will not
report the cases where a SRCU protected list is traversed using
rcu_read_lock(). Hence, use hlist_for_each_entry_srcu().

Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: <kvm@vger.kernel.org>
---
 arch/x86/kvm/mmu/page_track.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/4] sev/i386: Add initial support for SEV-ES
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11746541
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D04B7109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 15:37:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A860620866
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 15:37:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="eBTRGY6a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729196AbgHaPhv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 11:37:51 -0400
Received: from mail-dm6nam08on2043.outbound.protection.outlook.com
 ([40.107.102.43]:56437
        "EHLO NAM04-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729335AbgHaPhj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 11:37:39 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=CA9ituaPySmYdpBCZWQHc719C9VrmO2NG9+6+e6vyFU90F01BXhTuYobsU3RN+6ut7xONhe+jOppQgRYoVtKfsye17t6cX+SJxu4H+3sCD/HrmJNzTPzziHBSxhLVnv///OrPy/O/Edsi92+EqS8HGVb3I+vxUM3BF+0AFm/lyo3KZE+YPje7XHDOujBbsD9fW/KVvfPHtt7W6iWRCJ3K5uFz1KXgSiEyinYkejbqDK0aRdBiMK2vTVWKLmbTIkAF0ANgHWk/ehquC1JAMQL/SFWzTh8aMxZj5IC/ukBbu8NhJ560M/PGuah9Kr6Gu5qfdCLjZF/M7DwUhQPRoB4VA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=hORM3Vy8hyK6xLsYFFSIq/y5Tp6Pg2z/sJ60tyYU1JZyT2yeXLN0JIwCuzigEd90XFO6iCzy/7VCTbvNkYmv3I2yEx66mY7GYHl7KcTWxLvGruA7o89b+SmXOhIQACCdqeJUGDt4zl5J8g5c0NMcTUmJBuYpl0a5bI7ctwF7zxOPH+OVpwJHCH692Ie+5sYpc1qp6RShWQUqGr7CE08rIpEr9KHl+GGSWV1Y1Vc/AL+HCTi/6019BUZCInTm+2kMFx2NHqY37W6J4aVlZAccV2ScuvS9KmtFSyOYRf0c9e9mCvZx5A9ODE4XCPvZjAYFtpeAS4YDOtHNlZhZVqPCPw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MJ+BpJng5csN/LA+I/qcPQkYM/tISIORmRx+LOYMnks=;
 b=eBTRGY6a+GyfUq51LlvjAUZ2fHcsw2xp2QzSuQ9LF+DjVDHDA6KTX5D79vYYHN03TrwuzczBCPhSxTy6dX2I07/wkMbvuWSBMD5hgTnXyJSuGyEMLCZlXFdIi1L7b7uqN47qHv6xhfdvAT3tAL58zzTvUyvQk5k5HLgEHHwNfOg=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4484.namprd12.prod.outlook.com (2603:10b6:5:28f::24) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3326.19; Mon, 31 Aug 2020 15:37:36 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3326.025; Mon, 31 Aug 2020
 15:37:36 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v2 1/4] sev/i386: Add initial support for SEV-ES
Date: Mon, 31 Aug 2020 10:37:10 -0500
Message-Id: 
 <6222b0024f7af99fe7de5eede633d00e42162e2f.1598888232.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1598888232.git.thomas.lendacky@amd.com>
References: <cover.1598888232.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: SN1PR12CA0061.namprd12.prod.outlook.com
 (2603:10b6:802:20::32) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 SN1PR12CA0061.namprd12.prod.outlook.com (2603:10b6:802:20::32) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3326.19 via Frontend
 Transport; Mon, 31 Aug 2020 15:37:35 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9569550a-4ca3-4eab-65e0-08d84dc3c93d
X-MS-TrafficTypeDiagnostic: DM6PR12MB4484:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB448403024AD44777CD0BE3B4EC510@DM6PR12MB4484.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2043;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 sEp+kjbfBef11bfZgkVrkg5IV8ofbX8OSiVzyVbxJsRsel2y/a7COTjh4OjyPDfh8ro02/ASUQiMVfsdmaGngLCbrs3N9jzKB2k5CD6DAH0rrf+g0fVIFgSjcptViR7RCmrHb3PGgjqDJ8/OvrddosHJNa+Bj39dBHPsdfNYgOQNpHnNnLxq9/DRxLwMynjPyeUKjSVe8sLM3hXK7KwgvCXaNpEtlr4MeEtuzd4SxdkDwD9ffcHWbiSooVjtTAdVPGLsWyJQaVR+bRSupXcAOuToqhI5Yptf5cl0qNbuL8lBkpEY3Av4FQqXVc9Mrm7ZNMh4l3ANg3JS4EgKoPpjUX7OMwltedn74PYKTSgWsOwIXxup9ZzxZxvjyQWuv3yx
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(366004)(346002)(376002)(136003)(54906003)(956004)(16576012)(7416002)(2906002)(6666004)(4326008)(2616005)(6486002)(316002)(66556008)(8676002)(66946007)(478600001)(186003)(5660300002)(8936002)(86362001)(83380400001)(66476007)(36756003)(52116002)(26005)(309714004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 BC9uk/Y5kE+Kl2S0IU3FJD8eG/XG8+D3Hl7bC1jXS8CpO66hDLSNRueM1NW1hFMk0Q2YE4CHLfjoMIel0mpPTNuBcYTuZwP7nZ5tw0NJFChW1dREVmhrCbEaTNSp6o/x3JE8LROIvncmO7nO1ebOpXoRz46v0IJy+nnGZqx1r9qnBQ5yGr3QQbSn03z33i4TTc6QkkZ2ZL8QEKg3o0APvje7HW5uMBBKKld8bk6qXA+Z9mIr/t/V4PDsYIEke/vEMBCRgUBt0GO8a0+jMi0uMh9/lhwM5pwkdW8oZBDvs7lSg0lbijDdYAaHDV5v45E80HJxN0bp2u6MxQJSfz1bGgiBPw2A1GbDfcOLGbSBDMZQsEn7cinXrOubP20lkTVfgJRlBORvmwz7prs+Ohwp9ERFv71V7RHe7g1pWRr4MuXFZ7xLbp2qivmkxFatPYz1qXbyB5A2Vrk7i0ppgRyTr06Qjduka2RPk4HX6SvCgLkPJqPzLJHzG6yqgKRg12M5psouQNcCBZBaoPrXTCEHQ+jzu+ORK4ZRXMcfpEsX3I5wSY6aOSTsjyWRf9BwaxL527pKJW19QFGOtgpMChZwf/OwvuTkyXeTTMtwb6yBd85AeVMT6dckM0lifOAPIZi2mRhvKLl0gAA4Xv+tFM5QRA==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9569550a-4ca3-4eab-65e0-08d84dc3c93d
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Aug 2020 15:37:36.6519
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 xHBZq1bZzH2IaITt/kKzRcSjaqYZRPvFht2nuA55LtkDYM9viUkbWMz171Ow4jQanmY4UKW7hbe7tXfhSoORGQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4484
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Provide initial support for SEV-ES. This includes creating a function to
indicate the guest is an SEV-ES guest (which will return false until all
support is in place), performing the proper SEV initialization and
ensuring that the guest CPU state is measured as part of the launch.

Co-developed-by: Jiri Slaby <jslaby@suse.cz>
Signed-off-by: Jiri Slaby <jslaby@suse.cz>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 target/i386/cpu.c      |  1 +
 target/i386/sev-stub.c |  5 +++++
 target/i386/sev.c      | 46 ++++++++++++++++++++++++++++++++++++++++--
 target/i386/sev_i386.h |  1 +
 4 files changed, 51 insertions(+), 2 deletions(-)

```
#### [PATCH v10 1/2] virtio: let arch advertise guest's memory access restrictions
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11745961
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 944DC13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 09:10:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78D202145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 09:10:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="SwTH0qPN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728453AbgHaJKl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 05:10:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28722 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728184AbgHaJKG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 31 Aug 2020 05:10:06 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07V92ZlD084013;
        Mon, 31 Aug 2020 05:09:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=wBf/tROChMDuYAXkup8kbfwmTRrmdskmvoEJM16OTSE=;
 b=SwTH0qPNYMUaqOL1A6WqlJGQ1JwVnQkzNxAYYU0GfakZnMCH6kUM0j7PMXjaH+4pDr/E
 asXp5aqFeKGIMQ5GETvibGxTriiSjaOQB9/feRJB0VqQgo+zBxnycYRdMRy2SiXo0QLT
 yUWavtco6MkItv3NlpDlQ1Y+F2iz7bPg2VMDORsFSzcJfAhK2QXReAK7HWmivfaRiTBB
 esVm9EWP1xln+UKMe/7idJ9QrppGytQZOEwN3qH8FKXIUz0zvxhrOtRv/T7K6JZEvsQm
 pEOnt0+ObuhwfQQsLIDFqbZFO8Xf5PtSgdKe7P6pvCQp5zKilfclnENlajKiwm9i8xsL Qw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 338wgj1akm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 05:09:54 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07V92pkN085113;
        Mon, 31 Aug 2020 05:09:53 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 338wgj1ak3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 05:09:53 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07V8TI6l007338;
        Mon, 31 Aug 2020 09:09:51 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 337e9gt05a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 09:09:51 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07V99nfL28115204
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 31 Aug 2020 09:09:49 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E42F5AE055;
        Mon, 31 Aug 2020 09:09:48 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 36C47AE045;
        Mon, 31 Aug 2020 09:09:48 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.40.55])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 31 Aug 2020 09:09:48 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v10 1/2] virtio: let arch advertise guest's memory access
 restrictions
Date: Mon, 31 Aug 2020 11:09:45 +0200
Message-Id: <1598864986-13875-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1598864986-13875-1-git-send-email-pmorel@linux.ibm.com>
References: <1598864986-13875-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-31_01:2020-08-28,2020-08-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=1
 spamscore=0 clxscore=1015 mlxscore=0 phishscore=0 bulkscore=0
 priorityscore=1501 adultscore=0 lowpriorityscore=0 mlxlogscore=999
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008310051
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may restrict host access to guest memory,
e.g. IBM s390 Secure Execution or AMD SEV.

Provide a new Kconfig entry the architecture can select,
CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS, when it provides
the arch_has_restricted_virtio_memory_access callback to advertise
to VIRTIO common code when the architecture restricts memory access
from the host.

The common code can then fail the probe for any device where
VIRTIO_F_IOMMU_PLATFORM is required, but not set.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h |  9 +++++++++
 3 files changed, 30 insertions(+)

```
#### [PATCH v1 1/3] s390x: pv: implement routine to share/unshare memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11746261
Return-Path: <SRS0=MvWC=CJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 762F21575
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:05:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CD6720866
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 31 Aug 2020 12:05:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="RuJnJmec"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726654AbgHaMFt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 08:05:49 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:19984 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726204AbgHaMFl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 31 Aug 2020 08:05:41 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07VC2a0I026004;
        Mon, 31 Aug 2020 08:05:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=ZRVzO9kDmoyT7pGzE7Gyiex38XywGmdAlXT+v+oP+Ig=;
 b=RuJnJmecLNdGwvgcU0StMERyh2aEagUcYZf3MldxJcnPgR6jeG6K/0uXz85SA/Tr1jfu
 1XcpOXYq4UlIVC6KOqHY1wownEXUkjbbg8EuNxDLPjljfZmR5x3jwA8hA/lyqvZGJEch
 r6RsXepoK0BzWvWLbsHYdvvGyCOf6E9trNb6JfsJ1Lvokv+ffprULCYNJXWmD672wttn
 Xh+6ZVffDXLxTwowCnQecn0zBFm4jJS21jFIlFsvAkXrvH+MGdGv6yVAYKJz3ByGvHxw
 EjjTHyarOBHfMZmhag9xQW/NBMV0bI+gy9at4FSWWteFCV3AbsyjINuWUATTGUKrX/p6 JA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3390txg47n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 08:05:40 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07VC2tfd026878;
        Mon, 31 Aug 2020 08:05:39 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3390txg46u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 08:05:39 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07VBvhRo022059;
        Mon, 31 Aug 2020 12:05:37 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03fra.de.ibm.com with ESMTP id 337en899nj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 31 Aug 2020 12:05:37 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07VC5Zlu31064516
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 31 Aug 2020 12:05:35 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3DAC1A4066;
        Mon, 31 Aug 2020 12:05:35 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EF439A4065;
        Mon, 31 Aug 2020 12:05:34 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.160.216])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 31 Aug 2020 12:05:34 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [PATCH v1 1/3] s390x: pv: implement routine to share/unshare memory
Date: Mon, 31 Aug 2020 14:05:31 +0200
Message-Id: <1598875533-19947-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1598875533-19947-1-git-send-email-pmorel@linux.ibm.com>
References: <1598875533-19947-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-31_04:2020-08-31,2020-08-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=1
 bulkscore=0 phishscore=0 mlxlogscore=999 spamscore=0 clxscore=1015
 impostorscore=0 priorityscore=1501 adultscore=0 lowpriorityscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008310066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When communicating with the host we need to share part of
the memory.

Let's implement the ultravisor calls for this.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Suggested-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/uv.h | 33 +++++++++++++++++++++++++++++++++
 1 file changed, 33 insertions(+)

```
