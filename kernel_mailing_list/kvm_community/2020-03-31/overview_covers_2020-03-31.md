

#### [RFC PATCH v3 0/8] KVMTOOL RISC-V support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Tue Mar 31 10:53:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11467429
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 872C917EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 10:54:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 554372145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 10:54:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="L3GnqzdA";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="IisP3za7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731025AbgCaKyG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 06:54:06 -0400
Received: from esa3.hgst.iphmx.com ([216.71.153.141]:1490 "EHLO
        esa3.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731003AbgCaKyG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 06:54:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1585652046; x=1617188046;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=8NjGO2zEjzVhqWRimhrXKVoUlyiLoSMwgTQbyhOfgNM=;
  b=L3GnqzdAHZC6VhB30Z+oZFcHX+Jtmbnm3jJThggyEW3LjIB3jyEPRlb1
   XpulybVPXb94BZetrZ53X6iXbG7SrBzZLWiVRs/zQF4rSko2Qe1ed2foV
   D/FASAZ6DnjfRju1AakqtBGnpJm7i0p4oDz2o4+L96JipgGohDV3zfqU5
   UWmGqOeFqmTjaIz0POFvUHddjwVwB0ns75QSsWL1K1Qx1nVQo2lJLP2ii
   FbFBXbviX7jg2+TM8td/LRFSkGqbj6cp42fH9L67uIHIopbKNYON3mA8A
   KuDENNVvzJPMbHcnRcZUlSYPi/wRGQ3/ohd9H60KB4MHv77sxr6iORDDp
   w==;
IronPort-SDR: 
 bDGeStc4yCh08TRops/bC9mwjLCkVOZfxgeb/5E+tQF7BOLCWGuSUTV+a40oScZtGprsgBNyUO
 ONhX7hmi5vwKpfjeoTkVyaL4AjRXOBqCZ0gueh8asHbzg9mbRbcFlC3kouWq+QVLxTm+nOuE4/
 a7Q15MrBj7PDaTzD2/5hNmx5xt+wF4OPuGC+JPNgW0yQ/zIfC1nTQp/gM3CvpCK1LpnvWCGcTA
 hdOoBEGPkCSCD444IPnigll7BHSypUOrRbFwnrOavHisUgdS7wGCBVQD6rbJjqI8Y9Q+rIWe3C
 xx0=
X-IronPort-AV: E=Sophos;i="5.72,327,1580745600";
   d="scan'208";a="138377087"
Received: from mail-mw2nam10lp2101.outbound.protection.outlook.com (HELO
 NAM10-MW2-obe.outbound.protection.outlook.com) ([104.47.55.101])
  by ob1.hgst.iphmx.com with ESMTP; 31 Mar 2020 18:54:05 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=KpGT3Jbw35JHGIWh6UeDZXHpF44ynDQjxPcmO38iaJ+Hy4elB9nlwb5QjI1dJ2mOIE290gMLU5yGim5ECZuGiyvyG1A1ZBOmLZuht+FEZuPQNja6Omt8qjWZJEHju/fR5t8u5i9QQsMMSuvkEnY4iNFRGKH1x3ozO2YrvfYldNHSV2bPIwR2Im6CEQSCZiQrEMWINjKWoUj1c1DZy6EldT7MgLs3srPtXN3oWGq2zCW2QcR3Ilj/uxE6otsHaW4w1fARe4hA4X2PzPkasTyLaO1Vj+AGCNoRHzVfSNUxTti2cjjr7Xu1NEspXc+Irz+4atRCbUeP6Io6LXDvsYKnQA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=1Bel8HatHqQkfbApVlPLcXsm11/bPRJ0SSuXIba9Sow=;
 b=FAzBNIpXCjbBXBefYLVJ5MXtuP9ZYZnuLA5NiAighHRGnr63XLbw4/4u7IsAz0JFa1hC9/OKY3f9J+YeUa/6jIY4Ksggcs7vHqkCNNnE6hwCB3bjtvLGVik7a7PmVWVjAk6ZiBQil9JYT7tS1wGvwCF6yOxXBczfXdyD8f4t1qCCp8iosKlILoSQSrhS+/SL9q0Zzcl0qs6a35CEJ47hQusfJrqAm1YtWKgVdXuU/+HrqcOK+Jka+ZmmmkSQBWw4LN0737/H0/GbIW8OOnoiCPYXgcdcehVPElsanHrlwm5u26XC6yHy01r1P8x6+Yv7PUpYRxo4jjBflP1dLOal2Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=1Bel8HatHqQkfbApVlPLcXsm11/bPRJ0SSuXIba9Sow=;
 b=IisP3za74+jbOXpYxZ/Gm7oyN377mr0Epuc1t6LyA6jUcX7J+yMgrCC7jh5qoTmGrpRaMcPxkt9+uMIb41GHnFPj1yAxikLM65ie5LmQps6RWEAtWdUZ/cjq86r99ZeqPv/JPiFSzwgUCG70e4xApWhm0Da+q9Zeh1TYssQbjrg=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
 by MN2PR04MB7088.namprd04.prod.outlook.com (2603:10b6:208:1e1::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.20; Tue, 31 Mar
 2020 10:54:03 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8%6]) with mapi id 15.20.2856.019; Tue, 31 Mar 2020
 10:54:03 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will.deacon@arm.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v3 0/8] KVMTOOL RISC-V support
Date: Tue, 31 Mar 2020 16:23:25 +0530
Message-Id: <20200331105333.52296-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: BM1PR0101CA0049.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:19::11) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (49.207.59.117) by
 BM1PR0101CA0049.INDPRD01.PROD.OUTLOOK.COM (2603:1096:b00:19::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.20 via Frontend
 Transport; Tue, 31 Mar 2020 10:54:00 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [49.207.59.117]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 72e1e799-92fd-45b3-2c10-08d7d561d369
X-MS-TrafficTypeDiagnostic: MN2PR04MB7088:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR04MB7088D5F10EDACBA3F3FD0E138DC80@MN2PR04MB7088.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-Forefront-PRVS: 0359162B6D
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MN2PR04MB6061.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10019020)(4636009)(346002)(39860400002)(366004)(396003)(136003)(376002)(8886007)(1006002)(6666004)(2906002)(966005)(478600001)(316002)(7696005)(52116002)(36756003)(6916009)(54906003)(16526019)(81156014)(8676002)(186003)(2616005)(81166006)(1076003)(8936002)(55016002)(44832011)(5660300002)(956004)(66946007)(66556008)(86362001)(26005)(4326008)(66476007)(55236004)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 8+JRVmboCHisD87i5R4fzAXLB7iodeMlW2nVxW8UIe6fgKJqYMO/y4yjAqEhsep2lVcCoVdWfTZ9Ox1+TpqrrhuxGt8Izw22+hQgfqZ8USasekNH4h2yT7j+d560gNlWiEdleD7Mor6DJS/YYKw3JGviU9JtG4yexF/igmMMXeabM7Nf/HaAfEPuP+0SZWvZUSPNpGr9OGhWawXo6YXhAzms1y+LJY0x9KQTgZA6cZonJaewHwee1MA00F0vgEw+PaDLhCwD99EHzoQBs11fFfAxQ1ypJQcH9HYAq1e1lT+60B9FYEmLHzRhDRsAILSh3ke1LjILq0jK8zDqsDeJey3KcJkBrJLIpId8Lntvosz7PbzE0z85pIMz/Vl5tRnSH0P5J4dXRYlmG97EptfzfwHhT1MLrXMIP4Gmc723gdliZI9bms5MTCpYW/uwYvk3eR1W4vRm/KYNB+PII/UlpRdeOUzB7mgh1Zi74GF0wkz+s+ZXWTPmRJQTkf4QQeEadl427KMWvotEhQzGq30va+8v0lwhAqTfu0dlyyGasnixob7jUMErXwreH1BYIqNWNFiEviWyDknjoyu0seP2bQ==
X-MS-Exchange-AntiSpam-MessageData: 
 e6pnTMJfq7fh7qq8tGImKR9/gxjr9ZHlThFOXdCH2IciLKAj3nzvJV5CKsyKegwaWysid0hGzqar2TmQrRCmOS/92AfusiaC3JQMUhdnUgsF0LGQVvgtUFYGadpxu9HXu856jMa06f0uoCkyyG7IUw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 72e1e799-92fd-45b3-2c10-08d7d561d369
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Mar 2020 10:54:03.5181
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 krA2y2Ui+SMVCxvbmnhl8l/qaH8Cb/zPQEVfMF02c4xGjk1MxnsTQ3nRCIz3NG58PJsS5c8DBzxcQ8hwirKMng==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB7088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds RISC-V support for KVMTOOL and it is based on
the v10 of KVM RISC-V series. The KVM RISC-V patches are not yet
merged in Linux kernel but it will be good to get early review
for KVMTOOL RISC-V support.

The KVMTOOL RISC-V patches can be found in riscv_master branch at:
https//github.com/kvm-riscv/kvmtool.git

The KVM RISC-V patches can be found in riscv_kvm_master branch at:
https//github.com/kvm-riscv/linux.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is
available in mainline/anup/riscv-hyp-ext-v0.5.3 branch at:
https://github.com/kvm-riscv/qemu.git

Changes since v2:
 - Support compiling KVMTOOL for both RV32 and RV64 systems using
   a multilib toolchain
 - Fix kvm_cpu__arch_init() for RV32 system

Changes since v1:
 - Use linux/sizes.h in kvm/kvm-arch.h
 - Added comment in kvm/kvm-arch.h about why PCI config space is 256M
 - Remove forward declaration of "struct kvm" from kvm/kvm-cpu-arch.h
 - Fixed placement of DTB and INITRD in guest RAM
 - Use __riscv_xlen instead of sizeof(unsigned long) in __kvm_reg_id()

Anup Patel (8):
  update_headers: Sync-up ABI headers with Linux-5.6-rc5
  riscv: Initial skeletal support
  riscv: Implement Guest/VM arch functions
  riscv: Implement Guest/VM VCPU arch functions
  riscv: Add PLIC device emulation
  riscv: Generate FDT at runtime for Guest/VM
  riscv: Handle SBI calls forwarded to user space
  riscv: Generate PCI host DT node

 INSTALL                             |   7 +-
 Makefile                            |  24 +-
 arm/aarch32/include/asm/kvm.h       |   7 +-
 arm/aarch64/include/asm/kvm.h       |  21 +-
 include/linux/kvm.h                 |  30 ++
 powerpc/include/asm/kvm.h           |   3 +
 riscv/fdt.c                         | 195 ++++++++++
 riscv/include/asm/kvm.h             | 127 +++++++
 riscv/include/kvm/barrier.h         |  14 +
 riscv/include/kvm/fdt-arch.h        |   8 +
 riscv/include/kvm/kvm-arch.h        |  85 +++++
 riscv/include/kvm/kvm-config-arch.h |  15 +
 riscv/include/kvm/kvm-cpu-arch.h    |  51 +++
 riscv/include/kvm/sbi.h             |  48 +++
 riscv/ioport.c                      |  11 +
 riscv/irq.c                         |  13 +
 riscv/kvm-cpu.c                     | 408 ++++++++++++++++++++
 riscv/kvm.c                         | 174 +++++++++
 riscv/pci.c                         | 109 ++++++
 riscv/plic.c                        | 558 ++++++++++++++++++++++++++++
 util/update_headers.sh              |   2 +-
 x86/include/asm/kvm.h               |   1 +
 22 files changed, 1900 insertions(+), 11 deletions(-)
 create mode 100644 riscv/fdt.c
 create mode 100644 riscv/include/asm/kvm.h
 create mode 100644 riscv/include/kvm/barrier.h
 create mode 100644 riscv/include/kvm/fdt-arch.h
 create mode 100644 riscv/include/kvm/kvm-arch.h
 create mode 100644 riscv/include/kvm/kvm-config-arch.h
 create mode 100644 riscv/include/kvm/kvm-cpu-arch.h
 create mode 100644 riscv/include/kvm/sbi.h
 create mode 100644 riscv/ioport.c
 create mode 100644 riscv/irq.c
 create mode 100644 riscv/kvm-cpu.c
 create mode 100644 riscv/kvm.c
 create mode 100644 riscv/pci.c
 create mode 100644 riscv/plic.c
```
#### [PATCH v2 0/8] vhost: Reset batched descriptors on SET_VRING_BASE
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Tue Mar 31 17:59:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11468169
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F0E11805
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 18:00:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1AEEC212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 18:00:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ENrGLgUE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727541AbgCaSAW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 14:00:22 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:46089 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726028AbgCaSAW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 14:00:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585677621;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=cFoxPzLg3hdCD0+oBUzFhDTOM1NMJFZ5aeMIjUALD/M=;
        b=ENrGLgUE2RBoZ9qKIkk+mp48G1HFpIZzCm/AACqPq++CGCMUpWAL9JIcyl8Sp8iF7Z3Vqz
        OCYvUbe5d3lfMaXCkFrnMiog0HKMAvG8US2MuF8Y7FIZumXqpColqRaHk/P9oJpJ3JwEAG
        arW33qSN5E1lLr1zyihejVRH/n9wQXA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-166-UG21D0t2MnuDehxvHf0PFg-1; Tue, 31 Mar 2020 14:00:17 -0400
X-MC-Unique: UG21D0t2MnuDehxvHf0PFg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C1FEE1084424;
        Tue, 31 Mar 2020 18:00:15 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-92.ams2.redhat.com
 [10.36.112.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 25924608E7;
        Tue, 31 Mar 2020 18:00:10 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
	=?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 kvm list <kvm@vger.kernel.org>, Halil Pasic <pasic@linux.ibm.com>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 Cornelia Huck <cohuck@redhat.com>, Stephen Rothwell <sfr@canb.auug.org.au>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH v2 0/8] vhost: Reset batched descriptors on SET_VRING_BASE
 call
Date: Tue, 31 Mar 2020 19:59:58 +0200
Message-Id: <20200331180006.25829-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Vhost did not reset properly the batched descriptors on SET_VRING_BASE
event. Because of that, is possible to return an invalid descriptor to
the guest.

This series ammend this, resetting them every time backend changes, and
creates a test to assert correct behavior. To do that, they need to
expose a new function in virtio_ring, virtqueue_reset_free_head, only
on test code.

Another useful thing would be to check if mutex is properly get in
vq private_data accessors. Not sure if mutex debug code allow that,
similar to C++ unique lock::owns_lock. Not acquiring in the function
because caller code holds the mutex in order to perform more actions.

v2:
* Squashed commits.
* Create vq private_data accesors (mst).

This is meant to be applied on top of
c4f1c41a6094582903c75c0dcfacb453c959d457 in
git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git.

Eugenio Pérez (5):
  vhost: Create accessors for virtqueues private_data
  tools/virtio: Add --batch option
  tools/virtio: Add --batch=random option
  tools/virtio: Add --reset=random
  tools/virtio: Make --reset reset ring idx

Michael S. Tsirkin (3):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched version by default
  vhost: batching fetches

 drivers/vhost/net.c          |  28 ++--
 drivers/vhost/test.c         |  59 +++++++-
 drivers/vhost/test.h         |   1 +
 drivers/vhost/vhost.c        | 271 +++++++++++++++++++++++------------
 drivers/vhost/vhost.h        |  45 +++++-
 drivers/vhost/vsock.c        |  14 +-
 drivers/virtio/virtio_ring.c |  29 ++++
 tools/virtio/linux/virtio.h  |   2 +
 tools/virtio/virtio_test.c   | 123 ++++++++++++++--
 9 files changed, 445 insertions(+), 127 deletions(-)
```
#### [PATCH v8 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Tue Mar 31 18:59:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11468263
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9B601667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:00:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AFCF721473
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:00:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M2vJoqTE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728486AbgCaTAY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:00:24 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:58458 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728225AbgCaTAV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 15:00:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585681220;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EqCCvsaS7AGlrQSx9pMux9InxynW3QeXih5EQnJcqPc=;
        b=M2vJoqTE5osfPsG+td2m63sTjGUenW/Af9smxe+X4U03N9FSBndptz0Y/JYoctlIDyZ99d
        GTjUi5E0X7NCRo7KxR8E8e8vfOtkvZNm7WjRVeCA/vSn4BwLHDGN9VxmqdrPN6lKLgsGDI
        wt0kAqFLoU2q/eCZeO+i06J9/o+e2vs=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-107-dTVFe5XtOSCb7RR-PD2-bg-1; Tue, 31 Mar 2020 15:00:06 -0400
X-MC-Unique: dTVFe5XtOSCb7RR-PD2-bg-1
Received: by mail-wr1-f72.google.com with SMTP id v14so13377445wrq.13
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 12:00:05 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=EqCCvsaS7AGlrQSx9pMux9InxynW3QeXih5EQnJcqPc=;
        b=f5TnDgPR7eltJWAJLi70lh3ibtBo90z9RxhN5iyzPPFKqC354flXX68XTr3Fz5JdBW
         bIkcJ4T2j2eQ1Xb29p6GWgxDbqUaz1LOLnMq8kukKMtmXhX3fVOqUC2a9FPx2/laZGv/
         I8YsEAgv5sIjjZ4LfQRo7wVzsMwIpJtMMwwiMNdv7+l/WUG6Yrtg0SCrkt7U7H4H97ur
         Rv6VAR9lsOyr28OoQ+cp5JrgsDhgxABbciXCxoScJ6YzGuodnb7HqN6ppGKTifvKE6DK
         LwPxfdCw4EK7+0txOtcXRK7Rgp1d4FtyaypCxq3PDVFD/U91fKEH2G3nX85XMM9Xk+/N
         yhhw==
X-Gm-Message-State: AGi0Puas5Kd0XUCb7XEhKaJIF3CIle8X5i9GFOVNT7bAS2L/7Kl/LXDC
        PssOXsAiDKGeyN/xo3HbYmwGr5b5p2PbBU8gJXy4E4IKF7qom46+4kptiD5q7aKyZJbx43cQMgo
        YDHc+/HSdgtzK
X-Received: by 2002:a1c:7e43:: with SMTP id z64mr279512wmc.45.1585681204949;
        Tue, 31 Mar 2020 12:00:04 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJRvFzKoEHXWn0ZsVj5logJ4oHj//9RzEBZbKfWFuX6NiqNOMSvgM6lJtuPuZOvt0ULVS2edA==
X-Received: by 2002:a1c:7e43:: with SMTP id z64mr279482wmc.45.1585681204586;
        Tue, 31 Mar 2020 12:00:04 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 j5sm26180404wrr.47.2020.03.31.12.00.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 31 Mar 2020 12:00:03 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Kevin Tian <kevin.tian@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com
Subject: [PATCH v8 00/14] KVM: Dirty ring interface
Date: Tue, 31 Mar 2020 14:59:46 -0400
Message-Id: <20200331190000.659614-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v8:
- rebase to kvm/next
- fix test bisection issues [Drew]
- reword comment for __x86_set_memory_region [Sean]
- document fixup on "mutual exclusive", etc. [Sean]

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (14):
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm.c                            |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  89 +--
 arch/x86/kvm/x86.c                            |  48 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  78 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                | 100 +++-
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  68 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 195 +++++++
 virt/kvm/kvm_main.c                           | 162 +++++-
 22 files changed, 1459 insertions(+), 138 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v3 0/8] vhost: Reset batched descriptors on SET_VRING_BASE
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Tue Mar 31 19:27:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11468297
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D9EC15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:28:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 27E50212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:28:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fkKgv8kk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729060AbgCaT2U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:28:20 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:22650 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727795AbgCaT2U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 15:28:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585682898;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=bZBZ2PvIvDxfPAe1u1A6kkjjW8ODyemq7LucCatSJOc=;
        b=fkKgv8kkWljFwdfF4mCP69z7oHk+IQztyjfT7G4xNfc+nm4ra+KCZwQaXLVKiAmsA2DbfL
        qIdXve7aCP0/08OYs3/G4rvYJpbH5E+UggdSpLZ0QM1neczgsAZEXK0GCsYJUFd4dF0Uhz
        q8qIE8w2jWFVidPtOKO+AxalLJu5MFE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-25-PaRuMewrOIaDewXx01564w-1; Tue, 31 Mar 2020 15:28:14 -0400
X-MC-Unique: PaRuMewrOIaDewXx01564w-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F07C418A6EC1;
        Tue, 31 Mar 2020 19:28:12 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-92.ams2.redhat.com
 [10.36.112.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6BE2898A57;
        Tue, 31 Mar 2020 19:28:07 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Stephen Rothwell <sfr@canb.auug.org.au>, kvm list <kvm@vger.kernel.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Halil Pasic <pasic@linux.ibm.com>, Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH v3 0/8] vhost: Reset batched descriptors on SET_VRING_BASE
 call
Date: Tue, 31 Mar 2020 21:27:56 +0200
Message-Id: <20200331192804.6019-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Vhost did not reset properly the batched descriptors on SET_VRING_BASE
event. Because of that, is possible to return an invalid descriptor to
the guest.

This series ammend this, resetting them every time backend changes, and
creates a test to assert correct behavior. To do that, they need to
expose a new function in virtio_ring, virtqueue_reset_free_head, only
on test code.

Another useful thing would be to check if mutex is properly get in
vq private_data accessors. Not sure if mutex debug code allow that,
similar to C++ unique lock::owns_lock. Not acquiring in the function
because caller code holds the mutex in order to perform more actions.

v3:
* Rename accesors functions.
* Make scsi and test use the accesors too.

v2:
* Squashed commits.
* Create vq private_data accesors (mst).

This is meant to be applied on top of
c4f1c41a6094582903c75c0dcfacb453c959d457 in
git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git.

Eugenio Pérez (5):
  vhost: Create accessors for virtqueues private_data
  tools/virtio: Add --batch option
  tools/virtio: Add --batch=random option
  tools/virtio: Add --reset=random
  tools/virtio: Make --reset reset ring idx

Michael S. Tsirkin (3):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched version by default
  vhost: batching fetches

 drivers/vhost/net.c          |  28 ++--
 drivers/vhost/scsi.c         |  14 +-
 drivers/vhost/test.c         |  69 ++++++++-
 drivers/vhost/test.h         |   1 +
 drivers/vhost/vhost.c        | 271 +++++++++++++++++++++++------------
 drivers/vhost/vhost.h        |  44 +++++-
 drivers/vhost/vsock.c        |  14 +-
 drivers/virtio/virtio_ring.c |  29 ++++
 tools/virtio/linux/virtio.h  |   2 +
 tools/virtio/virtio_test.c   | 123 ++++++++++++++--
 10 files changed, 456 insertions(+), 139 deletions(-)
```
#### [PATCH 0/3] tools/kvm_stat: add logfile support
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From patchwork Tue Mar 31 20:00:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11468327
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BFC6315AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:00:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A65EC20658
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:00:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729153AbgCaUAu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 16:00:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:24464 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727837AbgCaUAu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 16:00:50 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02VJX2g5046117
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 16:00:49 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 303v2t526b-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 16:00:49 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <raspl@linux.ibm.com>;
        Tue, 31 Mar 2020 21:00:34 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 31 Mar 2020 21:00:32 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02VK0ins51511398
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 31 Mar 2020 20:00:44 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 93906A405B;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 68DFBA4060;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3] tools/kvm_stat: add logfile support
Date: Tue, 31 Mar 2020 22:00:39 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20033120-4275-0000-0000-000003B71EE6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033120-4276-0000-0000-000038CC6FA4
Message-Id: <20200331200042.2026-1-raspl@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-03-31_07:2020-03-31,2020-03-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 malwarescore=0 mlxscore=0 lowpriorityscore=0 phishscore=0 mlxlogscore=861
 adultscore=0 suspectscore=1 spamscore=0 clxscore=1015 priorityscore=1501
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003310164
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Next attempt to come up with support for logfiles that can be combined
with a solution for rotating logs.
Adding another patch to skip records with all zeros to preserve space.

Stefan Raspl (3):
  tools/kvm_stat: add command line switch '-z' to skip zero records
  tools/kvm_stat: Add command line switch '-L' to log to file
  tools/kvm_stat: add sample systemd unit file

 tools/kvm/kvm_stat/kvm_stat         | 110 ++++++++++++++++++++++++----
 tools/kvm/kvm_stat/kvm_stat.service |  16 ++++
 tools/kvm/kvm_stat/kvm_stat.txt     |   9 +++
 3 files changed, 121 insertions(+), 14 deletions(-)
 create mode 100644 tools/kvm/kvm_stat/kvm_stat.service
```
#### [RFC PATCH 0/4] kvm,x86,async_pf: Add capability to return page fault
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
From patchwork Tue Mar 31 19:40:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11468335
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC013913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:10:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9271206EB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:10:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MoDl2nTO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729647AbgCaUKE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 16:10:04 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:22063 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727720AbgCaUKE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 16:10:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585685403;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9tiFegyAVmmAr1Blf/zEd5Ozn4gaTM1GAemIQes9+TA=;
        b=MoDl2nTOr+jbsLEszC8VV16bROOGjp4feAM5qKrXjEvwA4oaDV+mZ9OM8uXxRssu3GwiHh
        fHPKlPDZODFgS0i3rfjL5aUBNnlcVXssHnB41EbbWuKwlq7vTx4fq+Hgbw14Nxu7Y/t2UC
        oZtKdYxunbCQkewBYsVFIBNa9rSf55I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-422-1tFIgNMfN5aGcZnHSE4dlg-1; Tue, 31 Mar 2020 15:40:27 -0400
X-MC-Unique: 1tFIgNMfN5aGcZnHSE4dlg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C2260DB6F;
        Tue, 31 Mar 2020 19:40:26 +0000 (UTC)
Received: from horse.redhat.com (ovpn-118-184.phx2.redhat.com [10.3.118.184])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3339160BE0;
        Tue, 31 Mar 2020 19:40:21 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 595FB220291; Tue, 31 Mar 2020 15:40:20 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, vgoyal@redhat.com, aarcange@redhat.com,
        dhildenb@redhat.com
Subject: [RFC PATCH 0/4] kvm,x86,async_pf: Add capability to return page fault
 error
Date: Tue, 31 Mar 2020 15:40:07 -0400
Message-Id: <20200331194011.24834-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current page fault logic in kvm seems to assume that host will always
be able to successfully resolve page fault soon or later. There does not
seem to be any mechanism for hypervisor to return an error say -EFAULT
to guest.

We are writing DAX support for virtiofs filesystem. This will allow
directly mapping host page cache page into guest user space process.

This mechanism now needs additional support from kvm where a page
fault error needs to be propagated back into guest. For example, say
guest process mmaped a file (and this did an mmap of portion of file
on host into qemu address space). Now file gets truncated and guest
process tries to access mapped region. It will generate page fault
in host and it will try to map the file page. But page is not there
any more so it will get back -EFAULT. But there is no mechanism to
send this information back to guest and currently host sends PAGE_READY
to guest, guest retries and fault happens again and host tries to
resolve page fault again and this becomes an infinite loop.

This is an RFC patch series which tries to extend async page fault
mechanism to also be able to communicate back that an error occurred
while resolving the page fault. Then guest can send SIGBUS to guest
process accessing the truncated portion of file. Or if access happened
in guest kernel, then it can try to fixup the exception and jump
to error handling portion if there is one.  

This patch series tries to solve it only for x86 architecture on intel
vmx only. Also it does not solve the problem for nested virtualization.

Is extending async page fault mechanism to report error back to
guest is right thing to do? Or there needs to be another way.

Any feedback or comments are welcome. 

Thanks
Vivek

Vivek Goyal (4):
  kvm: Add capability to be able to report async pf error to guest
  kvm: async_pf: Send faulting gva address in case of error
  kvm: Always get async page notifications
  kvm,x86,async_pf: Search exception tables in case of error

 Documentation/virt/kvm/cpuid.rst     |  4 ++
 Documentation/virt/kvm/msr.rst       | 11 +++--
 arch/x86/include/asm/kvm_host.h      | 17 ++++++-
 arch/x86/include/asm/kvm_para.h      | 13 +++---
 arch/x86/include/asm/vmx.h           |  2 +
 arch/x86/include/uapi/asm/kvm_para.h | 12 ++++-
 arch/x86/kernel/kvm.c                | 69 ++++++++++++++++++++++------
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/mmu/mmu.c               | 12 +++--
 arch/x86/kvm/vmx/nested.c            |  2 +-
 arch/x86/kvm/vmx/vmx.c               | 11 ++++-
 arch/x86/kvm/x86.c                   | 37 +++++++++++----
 include/linux/kvm_host.h             |  1 +
 virt/kvm/async_pf.c                  |  6 ++-
 14 files changed, 156 insertions(+), 44 deletions(-)
```
