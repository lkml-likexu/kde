

#### [PATCH 0/3] RISC-V KVM preparation
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Apr 24 04:59:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11507093
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5F8613B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:00:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ABF5920776
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 05:00:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="ocdVOzdX";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="vyB01TCv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726347AbgDXFAO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 01:00:14 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:17046 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725554AbgDXFAN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 01:00:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1587704414; x=1619240414;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=3RFL5fk8ktjSeopG8h0D42A38ZN6X8PbrTCsrXCK1WU=;
  b=ocdVOzdXsqEyYbUsFRt9/mve6cf9RWYW/I/9BqEYM+dn9S59+m6Wy+Aj
   1iKYbm3aq21ln7Ff4KJWsxIMS9cRLz+9LeeO9IwId4+bZ3xWlnmXOVS7P
   0bsayC2WH/0FYI6BpAf1EdDqY1yO6oJgzr5tEMzBk894BLFwmfzZGcqyj
   QCrDevTI8UyfwEBMHwtFtraYfmmWexIW/Jwr9P6iwKO2vwGPB7+ESmgit
   sAoCN83Yt31zzwIXYAlXBqyjFEM5uQ+eGKfRvazwq9Hu4si7zNVzCSBKX
   QZaAc4Eka7OmKGwTinEg9ucycloe2/+8qEdk9MsgHp5FsRTwgT8C44Ptf
   g==;
IronPort-SDR: 
 M89i/vv+1ikN4QeDNUnviHuIGjQz1cU6WJVw8dWEg+I5o6OERXs5te56WgXn72DU2ZmO8hgcbL
 em3H3LGw5VBNP4UbB+EIXHgCccydP8N4RV4m3khGp3v70VaPBYzz94tiOOTXG3W3h04mSanL8z
 mOsM/s7Ysj1i13Lzb9rFYkRfjnDFGzxEvt7iZi42y0MTchGSpnGNf0TObJX8gG98Unpk+U0KBK
 9DxELnqjGJnUb104qVr2vuiB59DUqE1wxHBY92XvQ0D6ZdjpDJt5PXFPkpZtDEbjNTpRYFQVCH
 im0=
X-IronPort-AV: E=Sophos;i="5.73,310,1583164800";
   d="scan'208";a="136354210"
Received: from mail-co1nam11lp2174.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.174])
  by ob1.hgst.iphmx.com with ESMTP; 24 Apr 2020 13:00:13 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=XnHIBFyxSRdL72GGgY6+gfta/vV9yq/sZV2aawGsgrfUTQ1G850IHWVEyrPoIiiwb+FQf5VyjOA3ZjVvzPT9HU5tFiHDdul3boYSLxtATyXdQyZkEGTy3wAskoiFOKxnjXZFBstxduKSW74girdwxH/0RXqBV/wxrpXGgA+DvfaVXBmeRFW2OnTHJ42GbwJESlx1WBD0HT9uT0XS2Y5YNzq72LMlh26PhccKBDDXf601gHpuNskjWyYBVzG9nBnZm3/y2A/nnmh5j0NezMysVArTTgU/4OfFtLfG/rlC9l3qhuugHuung0FiajfDnJA/0j406+iqFahnYqu/rr/kAw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MmpUk/iHmXL2NaITJWMDkQWf4xmblBLnoU2PM3OklQ8=;
 b=GHQiu+k4bLeBTnQyM/8yYkywOMf5EWw/j6QU+a0edcezxvSZRYTElolbmWVW2IpG5jaxbkX1vVdgnoLlXIEmUiUgGTj2zXCL/b1w6jBqr2e16F751SzhOoufMtexq9G3Ye99ryvZu/1gZPbFjYz/zUdwpKuwtN3GiNLnyP49JyNGDFw2FVjIqdsAlPtulY/c9lgzyKuBYpDoW1XTWbAnUgJkWIk+iENCHTZoLiTG57EqHufsQJALMUpKD98/y/G8wg0IMpenR0d/vUOinofRhnPUUX02jFX9SpD88+LhjMwfdShNV5gLLPxIkEMmkuuiy4ilUYxc52DTu+sEUC5hqw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MmpUk/iHmXL2NaITJWMDkQWf4xmblBLnoU2PM3OklQ8=;
 b=vyB01TCv2z9PY3qeXhdVaZecrUaUTBoWHU9DV8U0yZlptI0GQ2o4VfYAyttZKF7mV/HtjrPKNGRFYxerHR+dtu6bs5whfvLj4/SaVxKJ1gPQl1T+Hp76Jjkfqc3H8tfPLHlyHh8BqDXOw5U8l0l2+r8qyXdI8RS2R9aIChSxpUs=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (20.178.225.224) by
 DM6PR04MB5467.namprd04.prod.outlook.com (20.178.25.10) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2937.13; Fri, 24 Apr 2020 05:00:11 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::f8b3:c124:482b:52e0%5]) with mapi id 15.20.2921.030; Fri, 24 Apr 2020
 05:00:10 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH 0/3] RISC-V KVM preparation
Date: Fri, 24 Apr 2020 10:29:25 +0530
Message-Id: <20200424045928.79324-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: MA1PR01CA0130.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:35::24) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (49.207.59.136) by
 MA1PR01CA0130.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:35::24) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.13 via Frontend
 Transport; Fri, 24 Apr 2020 05:00:04 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [49.207.59.136]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f8e8f040-1375-42a8-9ea1-08d7e80c5d51
X-MS-TrafficTypeDiagnostic: DM6PR04MB5467:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB54679EE28AEB5B3C0EB182068DD00@DM6PR04MB5467.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-Forefront-PRVS: 03838E948C
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(366004)(39860400002)(136003)(346002)(376002)(54906003)(110136005)(55016002)(52116002)(7696005)(16526019)(8936002)(5660300002)(7416002)(4326008)(2906002)(8886007)(6666004)(81156014)(478600001)(1006002)(186003)(316002)(1076003)(55236004)(36756003)(4744005)(44832011)(8676002)(2616005)(26005)(956004)(66556008)(66476007)(86362001)(66946007);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 wMUHww/1zaXgttl+BrdgHbT9VXw249QEYJOL/3cSxCCPKP0xfTvja7OU9xX/Wagiisk2s9lL37cH6PtUhBZw2Exg6e4QIdeEfYX2x6KCA9E+pautszrfxVm3n2MOrpICdVLxBAZapSTJoqh1ca2DcmiMjzsqCXH+JN0rp4Gkhf6I7wcYqn5qODlbtHXHr7nz4c1WEYq4nr3fP46vp4PdfuKf1n0feondeFfYNxZ8SztHM0PReIbXi3dUTEcx6m2afnuwEsuaIuJCWN3bDazn7WY6j6hCJGJwwA12H71zKjVPyRbIgBdre5c+7EPiv0w4YavvNUEbY2oiCPWmK5V678sq8DLqAAYsu+vKKJah4bf1ErLexc/mH83TeuFAaG/A2qWmqRkUk5+RHkLGwj92jHNlYTy2Lt2Kubp8hzK35vpvcQagU2Com4yiFBHwcjO2
X-MS-Exchange-AntiSpam-MessageData: 
 50sEN5dpNldzM+Rp9BI6K1XXOz5sxQhlIqeHXgZwKtddCm12BKq1HQA9S67VgW3dhUVBPsHH3JL7cYUqoN+rUPCPoDy0wT2+PLFuJOtKRLfv2TWUv/uCYeTrllkkkUw2Hbf5txGmVnOgE227Y9YAZQ==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f8e8f040-1375-42a8-9ea1-08d7e80c5d51
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Apr 2020 05:00:10.3063
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 K9YvWzndkEXMPKxApLWUkTIkdnaQJsdarxr/gc+9I9+VOV4wJwPaa0zPgA/a5bvOKw4HGtLe+4a+7YxukhZm0A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB5467
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is factored-out from the KVM RISC-V v11 series and is
based upon Linux-5.7-rc2.

These patches are mostly preparatory changes in Linux RISC-V kernel which
we require for KVM RISC-V implementation. Also, most of these patches are
already reviewed as part of original KVM RISC-V series.

Anup Patel (3):
  RISC-V: Export riscv_cpuid_to_hartid_mask() API
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Remove N-extension related defines

 arch/riscv/include/asm/csr.h   |  3 --
 arch/riscv/include/asm/hwcap.h | 22 +++++++++
 arch/riscv/kernel/cpufeature.c | 83 ++++++++++++++++++++++++++++++++--
 arch/riscv/kernel/smp.c        |  2 +
 4 files changed, 104 insertions(+), 6 deletions(-)
```
#### [PATCH v4 0/5] kvm: Use rcuwait for vcpu blocking
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id 801EBAD71;
        Fri, 24 Apr 2020 05:52:16 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: peterz@infradead.org, maz@kernel.org, bigeasy@linutronix.de,
        rostedt@goodmis.org, torvalds@linux-foundation.org,
        will@kernel.org, joel@joelfernandes.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        dave@stgolabs.net
Subject: [PATCH v4 0/5] kvm: Use rcuwait for vcpu blocking
Date: Thu, 23 Apr 2020 22:48:32 -0700
Message-Id: <20200424054837.5138-1-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The following is an updated (and hopefully final) revision of the kvm
vcpu to rcuwait conversion[0], following the work on completions using
simple waitqueues.

Patches 1-4 level up the rcuwait api with waitqueues.
Patch 5 converts kvm to use rcuwait.

Changes from v3:
  - picked up maz and peterz's acks for routing via kvm tree.
  - added new patch 4/5 which introduces rcuwait_active. This is to avoid
    directly calling rcu_dereference() to peek at the wait->task.
  - fixed breakage for arm in patch 4/5.
  - removed previous patch 5/5 which updates swait doc as peterz will
    keep it.

Changes from v2:
  - new patch 3 which adds prepare_to_rcuwait and finish_rcuwait helpers.
  - fixed broken sleep and tracepoint semantics in patch 4. (Marc and Paolo)
  
This has only been run tested on x86 but compile tested on mips, powerpc
and arm. It passes all tests from kvm-unit-tests[1].

This series applies on top of current kvm and tip trees.
Please consider for v5.8.

[0] https://lore.kernel.org/lkml/20200320085527.23861-3-dave@stgolabs.net/
[1] git://git.kernel.org/pub/scm/virt/kvm/kvm-unit-tests.git

Thanks!

Davidlohr Bueso (5):
  rcuwait: Fix stale wake call name in comment
  rcuwait: Let rcuwait_wake_up() return whether or not a task was awoken
  rcuwait: Introduce prepare_to and finish_rcuwait
  rcuwait: Introduce rcuwait_active()
  kvm: Replace vcpu->swait with rcuwait

 arch/mips/kvm/mips.c                  |  6 ++----
 arch/powerpc/include/asm/kvm_book3s.h |  2 +-
 arch/powerpc/include/asm/kvm_host.h   |  2 +-
 arch/powerpc/kvm/book3s_hv.c          | 22 ++++++++--------------
 arch/powerpc/kvm/powerpc.c            |  2 +-
 arch/x86/kvm/lapic.c                  |  2 +-
 include/linux/kvm_host.h              | 10 +++++-----
 include/linux/rcuwait.h               | 32 ++++++++++++++++++++++++++------
 kernel/exit.c                         |  9 ++++++---
 virt/kvm/arm/arch_timer.c             |  3 ++-
 virt/kvm/arm/arm.c                    |  9 +++++----
 virt/kvm/async_pf.c                   |  3 +--
 virt/kvm/kvm_main.c                   | 19 +++++++++----------
 13 files changed, 68 insertions(+), 53 deletions(-)
---
2.16.4
```
#### [PATCH v3 0/5] KVM: VMX: Tscdeadline timer emulation fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Fri Apr 24 06:22:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11507171
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4AD8315AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 06:23:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 33B1920767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 06:23:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="WCZQnwIu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726522AbgDXGW5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 02:22:57 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51250 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726078AbgDXGW4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 02:22:56 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A760DC09B045;
        Thu, 23 Apr 2020 23:22:56 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id s18so1490320pgl.12;
        Thu, 23 Apr 2020 23:22:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=b4QeW0VDRqbvEETBZ13QetaInWr2btitEZOC+VxZd+E=;
        b=WCZQnwIuKhUUloQh2c8VR7QuGYr40YhAxbYbxnj9MafTQWfH98agLefwnFk+dwwLBF
         9fqNuPM3rPdotc1tcGf3gXl1rGWH3Cr0/F+hNpopsTyz3JwOFombvtTce/7PW7xHxR0K
         x9xKvc/QOQlFovYUHuamprejDWRPfZHweqsKzRPs/ADFzI2Go4c33+TXAfC6k56NvR+r
         m7uJdzzKttWWeLZDSArEHhGRSf4XEIAP2qh9EwNKW5vZ3z4AoM0W7iO9U3ywmchGXpZ/
         YfwC4hXtwJkAvMS3ax+Z8qgiIvo220y4wtXahG67ff/a2uL7Qpz36YCUVtIKbDdqywWz
         4gkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=b4QeW0VDRqbvEETBZ13QetaInWr2btitEZOC+VxZd+E=;
        b=bgGlorhAzxlJwehLCbNH9pFxM7q6GfdAYX7GpS6rNDs2wTAvheIJDCN4XOp4ehjFSk
         5rb7vMP3g6IHwcpXo5Wff66kgZT2c0d7NpG7hd3PYHoSX4t/FOF1x9ZPdVWx/x1rS0Aj
         0LxyeW+aDzU/JL6sa/ke1+ABE2SL7hhZVS8LXVmtK3pUjqrTIfvqVlYbY1LzTp65H3gu
         Lx22ne9MPa5b0aF/VtD2oudMwEPrREJTuxiW1WqnMFHu+4jYWmS4DLseSdKEJt/0FmWx
         ddZdgZ68yLSTDpBVmX5AjgZVjtrPIj5d680P8N5v6UZ/CZAjbY07BfFxvb5DK8wqlMMa
         jCVQ==
X-Gm-Message-State: AGi0PuaqHTssG9V/tsf/jO57rcLbkEKcF7gySZaSAx8QG1a7RyvJWphw
        XBCZ71E6UYoQPyIG4NsEOOC9VzKo
X-Google-Smtp-Source: 
 APiQypLCAowU4naaUsrYWj3L8M20ZXDYtGd/6A8oMccsd8PP/tZvLc1tOnBHQsjPeJzsALADPaxi5w==
X-Received: by 2002:a62:7c51:: with SMTP id x78mr7651501pfc.227.1587709375986;
        Thu, 23 Apr 2020 23:22:55 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 l30sm3920674pgu.29.2020.04.23.23.22.52
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 23 Apr 2020 23:22:54 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v3 0/5] KVM: VMX: Tscdeadline timer emulation fastpath
Date: Fri, 24 Apr 2020 14:22:39 +0800
Message-Id: <1587709364-19090-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IPI and Timer cause the main vmexits in cloud environment observation, 
after single target IPI fastpath, let's optimize tscdeadline timer 
latency by introducing tscdeadline timer emulation fastpath, it will 
skip various KVM related checks when possible. i.e. after vmexit due 
to tscdeadline timer emulation, handle it and vmentry immediately 
without checking various kvm stuff when possible. 

Testing on SKX Server.

cyclictest in guest(w/o mwait exposed, adaptive advance lapic timer is default -1):

5540.5ns -> 4602ns       17%

kvm-unit-test/vmexit.flat:

w/o avanced timer:
tscdeadline_immed: 2885    -> 2431.25  15.7%
tscdeadline:       5668.75 -> 5188.5    8.4%

w/ adaptive advance timer default -1:
tscdeadline_immed: 2965.25 -> 2520     15.0%
tscdeadline:       4663.75 -> 4537      2.7%

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>

v2 -> v3:
 * skip interrupt notify and use vmx_sync_pir_to_irr before each cont_run
 * add from_timer_fn argument to apic_timer_expired
 * remove all kinds of duplicate codes

v1 -> v2:
 * move more stuff from vmx.c to lapic.c
 * remove redundant checking
 * check more conditions to bail out CONT_RUN
 * not break AMD
 * not handle LVTT sepecial
 * cleanup codes

Wanpeng Li (5):
  KVM: VMX: Introduce generic fastpath handler
  KVM: X86: Introduce need_cancel_enter_guest helper
  KVM: VMX: Optimize posted-interrupt delivery for timer fastpath
  KVM: X86: TSCDEADLINE MSR emulation fastpath
  KVM: VMX: Handle preemption timer fastpath

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/lapic.c            | 18 +++++++++-----
 arch/x86/kvm/vmx/vmx.c          | 52 ++++++++++++++++++++++++++++++++++-------
 arch/x86/kvm/x86.c              | 40 ++++++++++++++++++++++++-------
 arch/x86/kvm/x86.h              |  1 +
 virt/kvm/kvm_main.c             |  1 +
 6 files changed, 91 insertions(+), 22 deletions(-)
```
#### [PATCH 0/2] Config interrupt support in VDPA and IFCVF 
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri Apr 24 10:04:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11507423
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2176913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:08:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D27D9208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:08:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726825AbgDXKHh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 06:07:37 -0400
Received: from mga03.intel.com ([134.134.136.65]:53046 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726808AbgDXKHg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 06:07:36 -0400
IronPort-SDR: 
 sbyXEKFkS2eqBx5N0JhMV63KMwhr3pqeV+PzL9yzs3DLk8oredz/JJd0ExrE9GziMaWg42YWhG
 4x+Gn2TC2kbg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Apr 2020 03:07:33 -0700
IronPort-SDR: 
 iqpJQBt4RyCbuxg/Er9EZDf02Fi1kIQAK37+Wk6ATAN9jt4gJ5Zv2V7tkrxj5+gEPkQFGOm+NG
 wEJrHqwd6mtg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,311,1583222400";
   d="scan'208";a="280755901"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga004.fm.intel.com with ESMTP; 24 Apr 2020 03:07:30 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/2] Config interrupt support in VDPA and IFCVF 
Date: Fri, 24 Apr 2020 18:04:17 +0800
Message-Id: <1587722659-1300-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series includes two patches, one introduced
config interrupt support in VDPA core, the other
one implemented config interrupt in IFCVF.

Zhu Lingshan (2):
  vdpa: Support config interrupt in vhost_vdpa
  vdpa: implement config interrupt in IFCVF

 drivers/vdpa/ifcvf/ifcvf_base.c  |  3 +++
 drivers/vdpa/ifcvf/ifcvf_base.h  |  2 ++
 drivers/vdpa/ifcvf/ifcvf_main.c  | 22 ++++++++++++++++-
 drivers/vhost/vdpa.c             | 53 ++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vhost.h       |  2 ++
 include/uapi/linux/vhost_types.h |  2 ++
 6 files changed, 83 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH v6 00/10] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Fri Apr 24 10:45:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11507511
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3740A13B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:46:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 232A12064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 10:46:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726858AbgDXKqB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 06:46:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10294 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726582AbgDXKqA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 06:46:00 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03OAY86Z026077;
        Fri, 24 Apr 2020 06:45:59 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30kk5tb6ps-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03OAhhb9060735;
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30kk5tb6p1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 06:45:58 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03OAjWGv007923;
        Fri, 24 Apr 2020 10:45:56 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma01fra.de.ibm.com with ESMTP id 30fs658x5e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 24 Apr 2020 10:45:56 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03OAjsSM60883006
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 24 Apr 2020 10:45:54 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 33475A404D;
        Fri, 24 Apr 2020 10:45:54 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA00DA4053;
        Fri, 24 Apr 2020 10:45:53 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.79.138])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 24 Apr 2020 10:45:53 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v6 00/10] s390x: Testing the Channel Subsystem
 I/O
Date: Fri, 24 Apr 2020 12:45:42 +0200
Message-Id: <1587725152-25569-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-24_04:2020-04-23,2020-04-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 lowpriorityscore=0 adultscore=0 mlxscore=0 bulkscore=0 clxscore=1015
 priorityscore=1501 suspectscore=1 impostorscore=0 malwarescore=0
 mlxlogscore=999 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2003020000 definitions=main-2004240082
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Goal of the series is to have a framwork to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test programm to define its own
interrupt handler. We need to do special work under interrupt like acknoledging
the interrupt.
  
Being working on PSW bits to allow I/O interrupt, we define new PSW bits
in arch_def.h and use __ASSEMBLER__ define to be able to include this header
in an assembler source file.

This series presents four major tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled  
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analysing the answer and expecting
        the Control unit type being 0xc0ca
        Checks SSCH(READ) and IO-IRQ

- ping-pong:
        If the reference channel leads to the PONG device (0xc0ca),
        the test exchanges a string containing a 9 digit number with
        the PONG device and expecting this number to be incremented
        by the PONG device.
        Checks SSCH(WRITE)


Note:
- The following patches may be pulled first:
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them

- I think this one if it receives reviewed-by can also be pulled now:
  s390x: define wfi: wait for interrupt

- this patch has a comment from Janosch who asks change so... need opinion:
  but since I need reviews for the next patches I let it here unchanged.
  s390x: interrupt registration

- These 5 patches are really I/O oriented and need reviewed-by:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

Pierre Morel (10):
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them
  s390x: interrupt registration
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: define wfi: wait for interrupt
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

 lib/s390x/asm/arch_def.h |  31 +++-
 lib/s390x/css.h          | 277 +++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 157 ++++++++++++++++++
 lib/s390x/css_lib.c      |  55 +++++++
 lib/s390x/interrupt.c    |  23 ++-
 lib/s390x/interrupt.h    |   8 +
 s390x/Makefile           |   3 +
 s390x/css.c              | 343 +++++++++++++++++++++++++++++++++++++++
 s390x/cstart64.S         |  51 ++++--
 s390x/unittests.cfg      |   4 +
 10 files changed, 936 insertions(+), 16 deletions(-)
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH V2 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
##### From: Huacai Chen <chenhc@lemote.com>

```c
From patchwork Fri Apr 24 11:15:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11507545
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B38C17EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:06:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0264F20736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:06:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="XCBkhHoc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726717AbgDXLGa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 07:06:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38930 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726289AbgDXLGa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 07:06:30 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E6C7C09B045;
        Fri, 24 Apr 2020 04:06:30 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id z1so2952636pfn.3;
        Fri, 24 Apr 2020 04:06:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=HSb8cTfIsUIoexVIsIcYlQ9HLgcMLPVB7mpDFIrYEi0=;
        b=XCBkhHocdvQRqaptKjiSqNbJ+4XqcZnygw1KgE/+K91vgTWkknknfAm+Ts2g3gDhVn
         ooy7oe1qYlt+wvB81zguKXEZcEmzql2JZNDxzP+8dMjhBCp59jXClgsSI6iuD/+bpqqW
         Z0hZ9HJy+Kr+LFz8DensKy4yAS55g7yUMfafEUhrAfmP0TOxmYg+fycIAFE1tSpgVlwS
         gcYoDUk+lrC+MGtGyqJ8V7nJamGJRLA0GZ+Zbq5Iytx+N++IOdYGWDTlCVACRMA/B2J1
         kPQ7vsztETHzEfCT0LxDyf8Gsx3nXE6VFA4URxkLVo2KS7ObcUljWWBTCaSRITn1YyIp
         aCsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=HSb8cTfIsUIoexVIsIcYlQ9HLgcMLPVB7mpDFIrYEi0=;
        b=G7pYFnM3nh3UUmC96geFqlMskf+6YkD7mJ439VVOX76N1BPi7lKUlMbeppFbC6aXCr
         +XzqlVXM9Zr3TDMHiiRPvIat32qrAuH4IadO+q43jFhUb38zPRuaRkYmU8iQa0RLeXRZ
         ShXCfOBvvKNzE51o/jiypfRSU1rZV8RcOqakfeqW20hgWrbmjf7YpymUB51PxJy/AEEW
         xOB0xYZ+dvI2OBajl6rppC8iQKuN/bxptAiAfqktsFrlPHmOoYf8k71jCvozjN89Rj2r
         KMHPMZvoCWNBs9K3B0A09v7L6BBgn7nS+9ZANXsQXijduZQj9ndXXbgc1uK0qwB3p8GI
         mXfg==
X-Gm-Message-State: AGi0PubFl1KDMMdsNWLEP7XDHVATzy6eRtTTtXWqnMXF81QOzjxFaEFV
        4EVe8MN414QbkQbp5cKe4n8=
X-Google-Smtp-Source: 
 APiQypILl0axEiko6pIrOWsPYgTwMFs5DyBA/xk0s8PlGWIWl7vifl6BTtilXxZwQkoIbzRjC3DGcg==
X-Received: by 2002:a63:111a:: with SMTP id g26mr8313438pgl.245.1587726389512;
        Fri, 24 Apr 2020 04:06:29 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 y10sm5470110pfb.53.2020.04.24.04.06.26
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 24 Apr 2020 04:06:28 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V2 00/14] KVM: MIPS: Add Loongson-3 support (Host Side)
Date: Fri, 24 Apr 2020 19:15:19 +0800
Message-Id: <1587726933-31757-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are preparing to add KVM support for Loongson-3. VZ extension is
fully supported in Loongson-3A R4+, and we will not care about old CPUs
(at least now). We already have a full functional Linux kernel (based
on Linux-5.4.x LTS) and QEMU (based on 5.0.0-rc2) and their git
repositories are here:

QEMU: https://github.com/chenhuacai/qemu
Kernel: https://github.com/chenhuacai/linux

Of course these two repositories need to be rework and not suitable for
upstream (especially the commits need to be splitted). We show them here
is just to tell others what we have done, and how KVM/Loongson will look
like.

Our plan is make the KVM host side be upstream first, and after that,
we will make the KVM guest side and QEMU emulator be upstream.

V1 -> V2:
1, Remove "mips: define pud_index() regardless of page table folding"
   because it has been applied.
2, Make Loongson-specific code be guarded by CONFIG_CPU_LOONGSON64.

Xing Li(2):
 KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
 KVM: MIPS: Fix VPN2_MASK definition for variable cpu_vmbits

Huacai Chen(12):
 KVM: MIPS: Increase KVM_MAX_VCPUS and KVM_USER_MEM_SLOTS to 16
 KVM: MIPS: Add EVENTFD support which is needed by VHOST
 KVM: MIPS: Use lddir/ldpte instructions to lookup gpa_mm.pgd
 KVM: MIPS: Introduce and use cpu_guest_has_ldpte
 KVM: MIPS: Use root tlb to control guest's CCA for Loongson-3
 KVM: MIPS: Let indexed cacheops cause guest exit on Loongson-3
 KVM: MIPS: Add more types of virtual interrupts
 KVM: MIPS: Add Loongson-3 Virtual IPI interrupt support
 KVM: MIPS: Add CPUCFG emulation for Loongson-3
 KVM: MIPS: Add CONFIG6 and DIAG registers emulation
 KVM: MIPS: Add more MMIO load/store instructions emulation
 KVM: MIPS: Enable KVM support for Loongson-3

Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/Kconfig                    |   1 +
 arch/mips/include/asm/cpu-features.h |   3 +
 arch/mips/include/asm/kvm_host.h     |  52 +++-
 arch/mips/include/asm/mipsregs.h     |   7 +
 arch/mips/include/uapi/asm/inst.h    |  11 +
 arch/mips/kernel/cpu-probe.c         |   2 +
 arch/mips/kvm/Kconfig                |   1 +
 arch/mips/kvm/Makefile               |   5 +-
 arch/mips/kvm/emulate.c              | 461 ++++++++++++++++++++++++++++++++++-
 arch/mips/kvm/entry.c                |  19 +-
 arch/mips/kvm/interrupt.c            |  93 +------
 arch/mips/kvm/interrupt.h            |  14 +-
 arch/mips/kvm/loongson_ipi.c         | 215 ++++++++++++++++
 arch/mips/kvm/mips.c                 |  49 +++-
 arch/mips/kvm/tlb.c                  |  41 ++++
 arch/mips/kvm/trap_emul.c            |   3 +
 arch/mips/kvm/vz.c                   | 210 +++++++++++-----
 17 files changed, 1021 insertions(+), 166 deletions(-)
 create mode 100644 arch/mips/kvm/loongson_ipi.c
--
2.7.0
```
#### [PATCH v11 0/7] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri Apr 24 11:37:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11507659
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1E3992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:38:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5C4E2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 11:38:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="vEYYXLYJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726849AbgDXLiF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 07:38:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43856 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726667AbgDXLiF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 07:38:05 -0400
Received: from mail-wm1-x344.google.com (mail-wm1-x344.google.com
 [IPv6:2a00:1450:4864:20::344])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D2B9EC09B045;
        Fri, 24 Apr 2020 04:38:03 -0700 (PDT)
Received: by mail-wm1-x344.google.com with SMTP id r26so10349207wmh.0;
        Fri, 24 Apr 2020 04:38:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=YkoHdhSZDcS430ypnKrze+vC3RcbR1ZGrC/igE/91x0=;
        b=vEYYXLYJjg13oRlH8NnKctuuUQ8aL0ZVuh8anZrEa4aRi9aheaYBq1CASYE6htsCmj
         MDQGoIvrJolNA8izQix4L8fNk62GPbwyk1ELDNLMd9/cgy8/euUVTDR7dWWV7y0KnIVq
         I30WNfmO6aQc9dI+nD5xP+TGnVjqGS9kLGpdlyAlQVlKdsip2k/oytmoAfRP70E+h0el
         Ms6OlN+SDBgD4zHgpN3KA+5ClJ0ZY62cE56+hsmysHSWgKgMkkXqiw1WFPIZmvwG54fa
         Ve9SlSskohZvC31uR1tFgyoo2mO3/uUzxZko9pSwB+bu9v50fI1nqS/nvFVWXlcr0AJP
         2WGw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=YkoHdhSZDcS430ypnKrze+vC3RcbR1ZGrC/igE/91x0=;
        b=NLokmAoAYRH8be6CtdOelEUWoLHsOkWITRLtHkhD40hNa0uSz1P4dYi4tXADzEJTtJ
         FAjpgjPdAl+5YCAmfNTG3uXjgKcWRkJox0DAiwl1yOULNVzbilnHjd+uDcB35zm496R/
         gMx5fiOzdDupdDXKkb0garNa4aEMQZrJrPoxM9hooXR15yXT7V0EEKFHhsFZyy6pgonP
         MAr9VX2MTqylwJWqAGFfWzy588z94xxcq2tvnIpnvjc0St8C/FP9K/ED88lavfhJRtIL
         SdBFwXKTl0KIQKYqNTTxNaHBl3ecvx52CgAC50q1lCUaM08b5unLgHrifM+uX9UMVxq3
         B5dQ==
X-Gm-Message-State: AGi0PuajKwaEmZnCbtuKh2C7iNNdsBNZX5nyyW2vTx+KcMfgeDv8eTTl
        HBJtrp48jR5PhNVXoKVh+MyWONfi73s=
X-Google-Smtp-Source: 
 APiQypK0OjvkogfSDfA9/2NWaPJ2MLr/q05Rpz5kWHZHQWjn95TFyi4oCUhDq3SVT2bJI/62hpDIUA==
X-Received: by 2002:a1c:80c3:: with SMTP id
 b186mr10398913wmd.117.1587728282174;
        Fri, 24 Apr 2020 04:38:02 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-154-20.inter.net.il. [84.229.154.20])
        by smtp.gmail.com with ESMTPSA id
 w83sm2451007wmb.37.2020.04.24.04.38.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 24 Apr 2020 04:38:01 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v11 0/7] x86/kvm/hyper-v: add support for synthetic debugger
Date: Fri, 24 Apr 2020 14:37:39 +0300
Message-Id: <20200424113746.3473563-1-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

v11:
Fixed all reviewed by and rebased on latest origin/master

Jon Doron (6):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/kvm/hyper-v: Simplify addition for custom cpuid leafs
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls without hypercall page with syndbg
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

Vitaly Kuznetsov (1):
  KVM: selftests: update hyperv_cpuid with SynDBG tests

 Documentation/virt/kvm/api.rst                |  18 ++
 arch/x86/include/asm/hyperv-tlfs.h            |   6 +
 arch/x86/include/asm/kvm_host.h               |  14 +
 arch/x86/kvm/hyperv.c                         | 242 ++++++++++++++++--
 arch/x86/kvm/hyperv.h                         |  33 +++
 arch/x86/kvm/trace.h                          |  51 ++++
 arch/x86/kvm/x86.c                            |  13 +
 include/uapi/linux/kvm.h                      |  13 +
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 143 +++++++----
 9 files changed, 468 insertions(+), 65 deletions(-)
```
#### [PATCH net v2 0/2] vsock/virtio: fixes about packet delivery to
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Fri Apr 24 15:08:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11508067
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA22D112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:09:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 949F22087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 15:09:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Vf24+Hr9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727946AbgDXPJJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 11:09:09 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:41257 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728047AbgDXPJE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Apr 2020 11:09:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587740943;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=mGgOnRVzcCEgMJaj5VrAhSpVCj/tilxi8AFKq06F19o=;
        b=Vf24+Hr9G4Dusn980oam3TXgYnqPZa6PuDqbwRjFh0PclZ0PtvmQKIZvGsY8QWUUIPbIvL
        yVBIh20T6Aw6XSWFrkE39AE70AR3Fi+uPo/Nl3K9gGXHSTkV5mqbM5l2ahiXIDSoIpvT1E
        WWyd7xJCV/eMefHkFgY1xOyx2z0C+5k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-335-MjVSv9QHNR6m_5AgATCLsw-1; Fri, 24 Apr 2020 11:08:54 -0400
X-MC-Unique: MjVSv9QHNR6m_5AgATCLsw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 16056846348;
        Fri, 24 Apr 2020 15:08:34 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-43.ams2.redhat.com
 [10.36.114.43])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9E8EC5D76A;
        Fri, 24 Apr 2020 15:08:31 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Jason Wang <jasowang@redhat.com>, Jakub Kicinski <kuba@kernel.org>,
        linux-kernel@vger.kernel.org,
        Stefano Garzarella <sgarzare@redhat.com>, kvm@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH net v2 0/2] vsock/virtio: fixes about packet delivery to
 monitoring devices
Date: Fri, 24 Apr 2020 17:08:28 +0200
Message-Id: <20200424150830.183113-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During the review of v1, Stefan pointed out an issue introduced by
that patch, where replies can appear in the packet capture before
the transmitted packet.

While fixing my patch, reverting it and adding a new flag in
'struct virtio_vsock_pkt' (patch 2/2), I found that we already had
that issue in vhost-vsock, so I fixed it (patch 1/2).

v1 -> v2:
- reverted the v1 patch, to avoid that replies can appear in the
  packet capture before the transmitted packet [Stefan]
- added patch to fix packet delivering to monitoring devices in
  vhost-vsock
- added patch to check if the packet is already delivered to
  monitoring devices

v1: https://patchwork.ozlabs.org/project/netdev/patch/20200421092527.41651-1-sgarzare@redhat.com/

Stefano Garzarella (2):
  vhost/vsock: fix packet delivery order to monitoring devices
  vsock/virtio: fix multiple packet delivery to monitoring devices

 drivers/vhost/vsock.c                   | 16 +++++++++++-----
 include/linux/virtio_vsock.h            |  1 +
 net/vmw_vsock/virtio_transport_common.c |  4 ++++
 3 files changed, 16 insertions(+), 5 deletions(-)
```
#### [PATCH v2 00/22] KVM: Event fixes and cleanup
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Apr 24 17:23:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11508679
Return-Path: <SRS0=ezuo=6I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CC4181
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:24:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43BF020736
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Apr 2020 17:24:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="By9raion"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727022AbgDXRYg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Apr 2020 13:24:36 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:42060 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726698AbgDXRYf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Apr 2020 13:24:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587749073;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=GYFwWH6/BVn1OIKUezAa/Z7+8Oz/hFSaieEazSypgrY=;
        b=By9raioncsbAKwA35r4lnwAszPw9nvcj+m1UAHpQR6kxJGjYmhCOlEgcgBZsMZmPyiD1Rw
        20n8b9vTA/aDxFSmUquy5Hmifg8HTZ9ROjJG/A4MZGh+5GJ8xTPnjcxmkITXhfmCMikuZi
        zfQajh8hILTkBYhx2q4Xk2saWWuHNAQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-279-mEkFw_AbPIqqDggtBGfHpw-1; Fri, 24 Apr 2020 13:24:31 -0400
X-MC-Unique: mEkFw_AbPIqqDggtBGfHpw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9D86EA48DA;
        Fri, 24 Apr 2020 17:24:18 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 77D2D25277;
        Fri, 24 Apr 2020 17:24:17 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: wei.huang2@amd.com, cavery@redhat.com, vkuznets@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2 00/22] KVM: Event fixes and cleanup
Date: Fri, 24 Apr 2020 13:23:54 -0400
Message-Id: <20200424172416.243870-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is v2 of Sean's patch series, where the generic and VMX parts
are left more or less untouched and SVM gets the same cure.  It also
incorporates Cathy's patch to move nested NMI to svm_check_nested_events,
which just works thanks to preliminary changes that switch
svm_check_nested_events to look more like VMX.  In particular, the vmexit
is performed immediately instead of being scheduled via exit_required,
so that GIF is cleared and inject_pending_event automagically requests
an interrupt/NMI/SMI window.  This in turn requires the addition of a
nested_run_pending flag similar to VMX's.

As in the Intel patch, check_nested_events is now used for SMIs as well,
so that only exceptions are using the old mechanism.  Likewise,
exit_required is only used for exceptions (and that should go away next).
SMIs can cause a vmexit on AMD, unlike on Intel without dual-monitor
treatment, and are blocked by GIF=0, hence the few SMI-related changes
in common code (patch 9).

Sean's changes to common code are more or less left untouched, except
for the last patch to replace the late check_nested_events() hack.  Even
though it turned out to be unnecessary for NMIs, I think the new fix
makes more sense if applied generally to all events---even NMIs and SMIs,
despite them never being injected asynchronously.  If people prefer to
have a WARN instead we can do that, too.

Because of this, I added a bool argument to interrupt_allowed, nmi_allowed
and smi_allowed instead of adding a fourth hook.

I have some ideas about how to rework the event injection code in the
way that Sean mentioned in his cover letter.  It's not even that scary,
with the right set of testcases and starting from code that (despite its
deficiencies) actually makes some sense and is not a pile of hacks, and
I am very happy in that respect about the general ideas behind these
patches.  Even though some hacks remain it's a noticeable improvement,
and it's very good that Intel and AMD can be brought more or less on
the same page with respect to nested guest event injection.

Please review!

Paolo

Cathy Avery (1):
  KVM: SVM: Implement check_nested_events for NMI

Paolo Bonzini (10):
  KVM: SVM: introduce nested_run_pending
  KVM: SVM: leave halted state on vmexit
  KVM: SVM: immediately inject INTR vmexit
  KVM: x86: replace is_smm checks with kvm_x86_ops.smi_allowed
  KVM: nSVM: Report NMIs as allowed when in L2 and Exit-on-NMI is set
  KVM: nSVM: Move SMI vmexit handling to svm_check_nested_events()
  KVM: SVM: Split out architectural interrupt/NMI/SMI blocking checks
  KVM: nSVM: Report interrupts as allowed when in L2 and
    exit-on-interrupt is set
  KVM: nSVM: Preserve IRQ/NMI/SMI priority irrespective of exiting
    behavior
  KVM: x86: Replace late check_nested_events() hack with more precise
    fix

Sean Christopherson (11):
  KVM: nVMX: Preserve exception priority irrespective of exiting
    behavior
  KVM: nVMX: Open a window for pending nested VMX preemption timer
  KVM: x86: Set KVM_REQ_EVENT if run is canceled with req_immediate_exit
    set
  KVM: x86: Make return for {interrupt_nmi,smi}_allowed() a bool instead
    of int
  KVM: nVMX: Report NMIs as allowed when in L2 and Exit-on-NMI is set
  KVM: VMX: Split out architectural interrupt/NMI blocking checks
  KVM: nVMX: Preserve IRQ/NMI priority irrespective of exiting behavior
  KVM: nVMX: Prioritize SMI over nested IRQ/NMI
  KVM: x86: WARN on injected+pending exception even in nested case
  KVM: VMX: Use vmx_interrupt_blocked() directly from vmx_handle_exit()
  KVM: VMX: Use vmx_get_rflags() to query RFLAGS in
    vmx_interrupt_blocked()

 arch/x86/include/asm/kvm_host.h |   7 ++-
 arch/x86/kvm/svm/nested.c       |  55 ++++++++++++++---
 arch/x86/kvm/svm/svm.c          | 101 ++++++++++++++++++++++++--------
 arch/x86/kvm/svm/svm.h          |  31 ++++++----
 arch/x86/kvm/vmx/nested.c       |  42 ++++++++-----
 arch/x86/kvm/vmx/nested.h       |   5 ++
 arch/x86/kvm/vmx/vmx.c          |  76 ++++++++++++++++--------
 arch/x86/kvm/vmx/vmx.h          |   2 +
 arch/x86/kvm/x86.c              |  53 +++++++++--------
 9 files changed, 256 insertions(+), 116 deletions(-)
```
