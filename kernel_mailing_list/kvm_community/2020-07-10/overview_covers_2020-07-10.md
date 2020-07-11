

#### [RFC PATCH 0/3] MIPS KVM related clean-ups
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
From patchwork Fri Jul 10 06:30:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11655787
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68BBD13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 06:32:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43A1A2077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 06:32:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="b/lZnQyF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727019AbgGJGc2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 02:32:28 -0400
Received: from vultr.net.flygoat.com ([149.28.68.211]:40620 "EHLO
        vultr.net.flygoat.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726004AbgGJGc2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 02:32:28 -0400
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id 589A51FF13;
        Fri, 10 Jul 2020 06:32:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1594362747; bh=mKcRZRz0SOJEYqGXRTX5Rcjg9hStrtnxlG5utBmVrdg=;
        h=From:To:Cc:Subject:Date:From;
        b=b/lZnQyFE1L7HDw+cKy7OX6z/eFeKFaGpm1RK7vM2GpP3vcshS4KDW/4JGRvh8upL
         xCNI8u4vSLmFHipoNd+5WOXa5IGzpuJ6vIrIkR43LvQWLc3fKBXSyh4f79ZNffYLlE
         IJun9AO8nktgZdm/ThbuOYyU9rEepnd6ThkzkPTzzWXTnvQlUs/9EGhMb1mvnKzDSN
         Fx7wK5lgokP2S2qCglv3OmBHrwWCVM2Sh10d1eVWZHF+cKLDrGxdwj2Qi609pfRHIg
         KwgfYTyIKuh7ujoGTcvpPaiqJw66TFIRcNy0O/i+dTQnuvtXrJQLTkM7TBQu0Q5MfH
         BfvOQBCQkP1Rw==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: linux-mips@vger.kernel.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Masahiro Yamada <masahiroy@kernel.org>,
        Michal Simek <michal.simek@xilinx.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Alexander Lobakin <alobakin@pm.me>,
        Bjorn Helgaas <bhelgaas@google.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Huacai Chen <chenhc@lemote.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Paul Burton <paulburton@kernel.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [RFC PATCH 0/3] MIPS KVM related clean-ups
Date: Fri, 10 Jul 2020 14:30:15 +0800
Message-Id: <20200710063047.154611-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Retire some features that never worked in the real world.

Also I wonder if there are any actual user of TE KVM.
Will Huacai or Alexsander take care relevant code?

Thanks.

Jiaxun Yang (3):
  MIPS: Retire kvm paravirt
  MIPS: KVM: Limit Trap-and-Emulate to MIPS32R2 only
  MIPS: KVM: Remove outdated README

 arch/mips/Kbuild.platforms                |   1 -
 arch/mips/Kconfig                         |  20 +-
 arch/mips/configs/mips_paravirt_defconfig |  98 ------
 arch/mips/include/asm/Kbuild              |   1 +
 arch/mips/include/asm/kvm_para.h          | 115 -------
 arch/mips/include/uapi/asm/Kbuild         |   2 +
 arch/mips/include/uapi/asm/kvm_para.h     |   5 -
 arch/mips/kvm/00README.txt                |  31 --
 arch/mips/kvm/Kconfig                     |   3 +-
 arch/mips/paravirt/Kconfig                |   7 -
 arch/mips/paravirt/Makefile               |  14 -
 arch/mips/paravirt/Platform               |   7 -
 arch/mips/paravirt/paravirt-irq.c         | 368 ----------------------
 arch/mips/paravirt/paravirt-smp.c         | 145 ---------
 arch/mips/paravirt/serial.c               |  39 ---
 arch/mips/paravirt/setup.c                |  67 ----
 arch/mips/pci/Makefile                    |   1 -
 arch/mips/pci/pci-virtio-guest.c          | 131 --------
 18 files changed, 6 insertions(+), 1049 deletions(-)
 delete mode 100644 arch/mips/configs/mips_paravirt_defconfig
 delete mode 100644 arch/mips/include/asm/kvm_para.h
 delete mode 100644 arch/mips/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/mips/kvm/00README.txt
 delete mode 100644 arch/mips/paravirt/Kconfig
 delete mode 100644 arch/mips/paravirt/Makefile
 delete mode 100644 arch/mips/paravirt/Platform
 delete mode 100644 arch/mips/paravirt/paravirt-irq.c
 delete mode 100644 arch/mips/paravirt/paravirt-smp.c
 delete mode 100644 arch/mips/paravirt/serial.c
 delete mode 100644 arch/mips/paravirt/setup.c
 delete mode 100644 arch/mips/pci/pci-virtio-guest.c
```
#### [PATCH v13 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Jul 10 08:25:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11655985
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE70C14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 08:26:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88862207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 08:26:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="IsAZF4Bp";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="NLctSvSg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726644AbgGJI0Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 04:26:24 -0400
Received: from esa1.hgst.iphmx.com ([68.232.141.245]:47933 "EHLO
        esa1.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726369AbgGJI0Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 04:26:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1594369583; x=1625905583;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=y5uVOyAduU/SLIcPpQ0FyrkEmKU6J3cnhwwPQUOKPJE=;
  b=IsAZF4Bp8hdfHc3ASjtr1YJf2qhe+iO7F+MIxdMHSNLVinrxd9QwoHHM
   xZG+aXEN+RFfwcuMRjHorlYacAHT6txrx86qSOF+Pmt79g0TXHDVRpQup
   bBAyj1KA1gfzeB6MdsD+ymHxfRSO9KuhCUDdXXI9Tsv1N0Pxyga7NbErk
   G7wyCh1MWKdTMsNrKcxdl8+bOeApg9wE6Z56IpUlrmn46L76JsszoEfQd
   gMnN0/P7amCS++oftbGfMW3dsojiahz4Be1jT2M21O0H3pDOcQph29V3w
   LgzZdtFUromXJL0v1fe8irGyCOfFHdoS8f15b4NO/m1YXtxCeLkaJlq5Z
   w==;
IronPort-SDR: 
 5R8ASqSwISQ6X6hUZZsXXWfu/jDE9P/Ev9tLq/jsu5SZMDOUp+Bvy9KimWB10K1Ex9zGvofr4F
 Ivx+SvoIRsc+YZu74WRUOonOhSLxf4iZKv0xtGsdK7wjdeHOUZXLibbX5gMTOvLuf6rsKeyVt1
 Pu6Xhr8IbFYSGOW4k1SE9MnFSRo3E2h5so8YtDiT7nFx+XpWtvc4tXHrXLoF0bQLInuG/czbEG
 zzDV6OtE1pT8eDNt6UXi9R97k0KwVHtFg3IWcwgZnMUt2Io2tD3Ch5VMjkpS/8bQKhDNieuk1Q
 4Jw=
X-IronPort-AV: E=Sophos;i="5.75,335,1589212800";
   d="scan'208";a="251355407"
Received: from mail-bn8nam11lp2173.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.173])
  by ob1.hgst.iphmx.com with ESMTP; 10 Jul 2020 16:26:22 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=AtcUVEmWyEpRXhT1qKpxXkQQPozVAWbulQ144VBevr/cQHp5tTQ3Meh9VdWL3zyOrQiZxduVOPpssT5M4Dh2sJR8tIGnQZEAiY60d2X+kKcGui0eDUuvGxAh+alWD7E1I/iFdb8wrGujizX4pu68bX7Of7d353fb8n0mRfoYH3Hj2iCHMWOeB0o30iVninROOi8EfXlC80lga34WRZ9dIZSi44pO88JYZc30bIbxY7PX18vQ9amhXmeS7Xk53Hx39w86cXULzosRrgtsLeTGaTjQ0K39rbCQ5g/FmKkKp5BD4MLRSYR7v/zEMMDHsKkRRfQy4gBhf+3iiyn+pJ24+g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zmZ2gkcQy2eyVg3HEuqk9qcfxmqNlmXtrkNHHa0k/B0=;
 b=ZY3S9fjgYM6r6Dz4kHEn8SOh8bpy1+wHvfg/tguh/YUrQJKW7oAW7eIiz1OMjI0xlaPvZlQK8ixftYBXka8015SmWBZUirvzEL09+ROnQkSZeAI1JkTbmmN9q3x/t8IYziG2RNIq3g9uKBr8632MSN3TJjSP6i0XFv4QzpAtV09vGBhvVBjeEYerOcKy+eiETLe/evv0d0M1/1BQ7i41nIJH+2vS3mMAoMVZdeiYmJD88b053zQBOnpH56hXI/Nz9GoBfd6T0Ajg6Hev9d3YQhgD7c9jpb4dxnoXItkt1tUK/WOU6fsmupm6hw0wo//Z94r8U1y0YfhwIdRdtfjADQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zmZ2gkcQy2eyVg3HEuqk9qcfxmqNlmXtrkNHHa0k/B0=;
 b=NLctSvSgsif8N81c9k8XxJ9Ue5telvuIOM1XF9cK+eXe8F3CgT+I0QGv1DTeHalgZitI7x/vd3IKMf1NxmOp8C2hJxTgxEki9o/SveCyelAisQjXaqJgHV16sqhID/UBQMPOLsjltBXGjbs6jOVqITFS8HS60jfAptQtzVbIvm0=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB0461.namprd04.prod.outlook.com (2603:10b6:3:ab::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3153.22; Fri, 10 Jul
 2020 08:26:21 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5%7]) with mapi id 15.20.3174.023; Fri, 10 Jul 2020
 08:26:20 +0000
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
Subject: [PATCH v13 00/17] KVM RISC-V Support
Date: Fri, 10 Jul 2020 13:55:31 +0530
Message-Id: <20200710082548.123180-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: PN1PR0101CA0035.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:c00:c::21) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (103.15.57.207) by
 PN1PR0101CA0035.INDPRD01.PROD.OUTLOOK.COM (2603:1096:c00:c::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3174.20 via Frontend
 Transport; Fri, 10 Jul 2020 08:26:15 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.207]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 08617608-40c4-4d92-c547-08d824aaec52
X-MS-TrafficTypeDiagnostic: DM5PR04MB0461:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB04611B2D8471540D2315E1B58D650@DM5PR04MB0461.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:133;
X-Forefront-PRVS: 046060344D
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 nQ7OniAhl4V0QtRu3MgYG76UDjiciQhqMyE71MkSsooT76nnj4uDmzHGooUZ+jDrn+PhvQECAzHhFl5oO5Vgd8cZHmiVEa1dbDaQfAE6qpInYX5m5rvlZ9nCHwS00FEnQ8IUSKYa4sKbfPXRqo76VMhT2Q5tpZVgcERwgPDwX/BZ2HMNiiGJBpK6A5eXtX4xcSexPJexKN73Q2WJHfZpiiktc1NHxVOB4whaQN7co168aGswJecJAqhJ9TofAqnD0VLdoxk2hQi0UeaFv2JfXmgxcS0zwcLu7Sfi3/4+xT9GWw2IylRlthgBjuT2VOM+yBWtke57j60DEjmgnBJU5Fpq+s+AnU2qLH2tOCO4v5LGRD+WljvxFihQmPV+WzT+Q6d0Wg0CKMdvIsrbp6O87cQvOY80HrFbh7lUUgmcVM5cxaeo5iwAVlY3gLKiht5wDf4z8TxubgZ1dFyUn6/vFcS0v6HABm1DMWNCOrwIE5g=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(136003)(376002)(396003)(346002)(2906002)(316002)(83380400001)(110136005)(54906003)(7416002)(478600001)(6666004)(86362001)(43170500006)(8936002)(966005)(5660300002)(7696005)(4326008)(2616005)(26005)(956004)(52116002)(8886007)(8676002)(186003)(66946007)(66476007)(55016002)(36756003)(66556008)(44832011)(16526019)(1076003)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 w9IlSbF3/QdxNJ/H6WCkAXiw0VVTT5kEAFefdZjSrq1kr6Sbzd6svXjtb230nrVseS24vIcWRsSjwuN9/QiqcHP7uInm8JZv1F/dPDjXfY5DZLIOtm1gknYrpiiam0tMFv4aD37s/V6K+Pdl7kNT0Cq2IiZAW1F8XlcXtBINjwmvPtexbyI74v4RyXb68qpUCCYGHz1v1iuedMriO3KIpAzt7yDWF/m7UBbTBAqVqW4hEnuEX4sECkKahjFKxQZJTa6DMcnmHON+oELNNAO7icpwA9w6kw9eCS3z4/X4gydGzZQ+l4iLEmdr+64Po8Vf2pkvV53W8NFfr3JRO5oSOeeoMaSJXWmsZ6iVm8KSNF3TGjf0jK7qQjXhbmQm45Ck1aZIvFRapX3WcI/b6GHzJasMw/ZahqQINOI/x1ivC6WHZXavXHeFIindw/AhlZwC4T6NRpQ/q9cdTf7RywH3Ra9m4pP4e3fInoeh2Ml0+Do=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 08617608-40c4-4d92-c547-08d824aaec52
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Jul 2020 08:26:20.5090
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6uSNt8zJC3NbUewLW19fnSTWQIv5z02mYyuScmMrw2iRDjl0ExnU5GzcPrjGQ/qcjryRDM8TaXfDi4BK390peQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB0461
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.
9. Forward unhandled SBI calls to KVM userspace.
10. Hugepage support for Guest/VM

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v13 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v4 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/anup/riscv-hyp-ext-v0.6.1 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          |  193 ++++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    2 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   87 ++
 arch/riscv/include/asm/kvm_host.h       |  273 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  127 +++
 arch/riscv/kernel/asm-offsets.c         |  154 ++++
 arch/riscv/kvm/Kconfig                  |   34 +
 arch/riscv/kvm/Makefile                 |   14 +
 arch/riscv/kvm/main.c                   |   99 +++
 arch/riscv/kvm/mmu.c                    |  775 +++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   74 ++
 arch/riscv/kvm/vcpu.c                   | 1012 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  670 +++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  173 ++++
 arch/riscv/kvm/vcpu_switch.S            |  391 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   86 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 25 files changed, 4590 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [RFC PATCH v4 0/8] KVMTOOL RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Fri Jul 10 09:00:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11656059
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D5BB13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 09:01:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E154E206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 09:01:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="mOkXZ+Nf";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="oGBzH4hC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726962AbgGJJBD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 05:01:03 -0400
Received: from esa1.hgst.iphmx.com ([68.232.141.245]:30265 "EHLO
        esa1.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726496AbgGJJBD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 05:01:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1594371663; x=1625907663;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=RSbpFKTbhMk1mgcdtZ7aUuAgwwNIh281CEDooyKHlHk=;
  b=mOkXZ+Nff1fyZY8Y94mXupAajzAQuntsEjB6jdfrgsCYDwfREIfVB7qR
   q1GKldS1dRLJb4UawNWTfciBmu47rOa+3qbQ9cwERq0YHU2mhKXzrzmJ5
   sJDHX5zIZXfurCAstwyLD4PxtVKXH6mzC+LbT6cqFCGr8PpIyDC25DkCh
   dp4dCJZJiod9NA5wEWmtiTSsrqPf+l0I7U/TjrbaYMJvQRMgKMyl1RqyP
   h/rl4X9TxJ0kfTNNt2ONPwZd53uNIWHKTbFT522xuzsVOmpoyAegHNs4/
   bXtKSzCaFGtMw1adBVgn04ligO7lYRzqZfZWcyO5YXTXNreoYjTwOEYFZ
   Q==;
IronPort-SDR: 
 AD1b/wugxXYq00kuxSwE9QzjeLtmBaFrcxIRj5CNNA3d1i4gQpXfHia2hvM5qSrKkP+3K+Nzja
 h8mXXVv3NKtTTwkys9D4q+v5LIvip3USf5NpaZoBwdie/gMDbwra7qKb716ybmG8/5RpTj1qx8
 U0rmhKmd6F6WwK8oAMhPhyyerM5uuj5R5pJlhI/dz80I/CxX2PNBjCl6KjATICSx/ZZKU8MdKV
 f05OJtdVShBOOYDEto/mPcwLwNl5KZGyYFORAZAvi81p/l5fHKG0z1oSf2+cqbPDmOn81qx48B
 T7E=
X-IronPort-AV: E=Sophos;i="5.75,335,1589212800";
   d="scan'208";a="251358817"
Received: from mail-bn8nam12lp2174.outbound.protection.outlook.com (HELO
 NAM12-BN8-obe.outbound.protection.outlook.com) ([104.47.55.174])
  by ob1.hgst.iphmx.com with ESMTP; 10 Jul 2020 17:01:02 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=T0qIOOBvGOWCwwmPEzcBSznZ4CvP/MpdzbwfEWUo7wDm18AKclOJttxd3AcU1Qw9d+XM5WmN+iWgnq7SEHAOS38h1xXLk0yVfNAc3vvUfFco/ziKivYdKvoZ62Q+kySgjtFiG4oAAzHnWezl0s+m/6u4NtElxent+2pxQqClgvlnKG8TdQhdLlO28hxi/tS0+Ofv3yE2NGtAy71M/fZMojlzStksSVQpC/BqNfgj1nDk/Hzf1V2lsjmnjVvC3Kaz9NqyDVwe3JuQsnoujjlzsC98ltv+rutryQMQX1vd6c2FTjG5PPL8I6mkjhHOJUbBRvUL99bRX5twoxsxHYrCXw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MIrRnDBpWIEWDJSQzVVYi9a6Hjp93fx+7cTzMfzIE6I=;
 b=LBJrEs3+WoL3FcZOldskL11URCD2fT/H8JEoh2PpDjKqt+N8VmVesux5GWbBCL0KXARmmFDi56VggL6JmRetm8eQN19R8hlwnsfC5agXdJsBhyn/UoirP4/6PRewWDj6sbfx2oQXMxIUBwxxEoEYFdDYavmoD/maFKGmRku6DqlOBI7t85idvPHjS/vuH/5REtjyt8BgscDYnq15r2nobtlAO/1Y8WMPaF9mn+AFDhZHqoIg6zR+joq+HiJbhQ/KpMDlku5glzt+uOR6M2nM6CAOvkxgGMWSWeK16GJEcznxRsf+iEjOOCLHdx+FtSgW/DleiSmqYyWDUb+Ezaw88g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MIrRnDBpWIEWDJSQzVVYi9a6Hjp93fx+7cTzMfzIE6I=;
 b=oGBzH4hCSpPlttyvUOi0UL+uxiXmdEXXYuspeMEEQv4STM4I2yybonTSlizhHjBQtFBs+x6rZZi5J4dIIcTHXlZwA8XrbI0qviSnpR0e9H2dhZVzpXzAKkzfB0hLj9/R7WdaqswZ47CRYO2KPCe3bD0dWqLX20SKs1WkqdzVwQo=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB0346.namprd04.prod.outlook.com (2603:10b6:3:6f::7) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3174.21; Fri, 10 Jul 2020 09:01:00 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5%7]) with mapi id 15.20.3174.023; Fri, 10 Jul 2020
 09:01:00 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v4 0/8] KVMTOOL RISC-V Support
Date: Fri, 10 Jul 2020 14:30:27 +0530
Message-Id: <20200710090035.123941-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-ClientProxiedBy: PN1PR0101CA0029.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:c00:c::15) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (103.15.57.207) by
 PN1PR0101CA0029.INDPRD01.PROD.OUTLOOK.COM (2603:1096:c00:c::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3174.21 via Frontend
 Transport; Fri, 10 Jul 2020 09:00:56 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.207]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: dde5dfb7-479b-4ff0-f147-08d824afc3b8
X-MS-TrafficTypeDiagnostic: DM5PR04MB0346:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB03468F46C8F0D40943DB39D98D650@DM5PR04MB0346.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:1923;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 VDR7/UOuL/BhHllRsOFZMmzuvIshge7sVQ6OFJ/MCziRgliYHzXegwBDtQk51GvZmaWxsF5jiFfjSxc4ZU4LLMh/yeDDaSJI+ifHF8h+c8Bw36AMDWYI46TVs6eEMaMp8kccBOMjOI9MTHupzQ6vlNAuyXtzjOLqxjytWUgodB+nCRGZf8SAFKVfG6gE9zcKMD3eofe8Z2E47yhAnDyKFr+3APPYVZo+Z/RygwMWFUP+d/Wg7qojTaBN36j3v/pgK1l1TdciItFf2He63ScqO0i2yHdLNQVFTtXS1cQkeo9OsdSebvMAI4mRvyVigLQfKPjzeeX0RMyPxqUtbnjpAKSECkEy60rGdfj0AUe2H0ZE0GRLI6X7CkCzrUgybFqUFDVTVTDwY5g1Re8D1fWm2kY9YqWfDkS2xBBbTyJtMM8hD2zA1PR2p9Nbc5G/NyciTgXKR8PldnTN/vCuOSxuQA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(346002)(136003)(366004)(376002)(39860400002)(66476007)(186003)(66556008)(16526019)(6666004)(52116002)(8886007)(1076003)(6916009)(86362001)(7696005)(36756003)(26005)(66946007)(4326008)(5660300002)(8936002)(956004)(2906002)(2616005)(83380400001)(55016002)(478600001)(316002)(966005)(44832011)(8676002)(54906003)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 efFxrTiFN7sFHaPItsuG48sDwq3iKTGN0Yj+7tg34UnRzjqSU3UvlLBz0+OGALqa9T+YcCC+vxrEQyf9WPWKIza27ocAf4X/45hPaqIIvWKp+PYM9u5DDH3DJnCGmbIUB28gqZYeL9AQmJQ4UK/cStUsAcbQG0sI/rLhIOOZL1XOrUbTD4ennZ8bqqNde0iQaqlyop1X5iTAOkya0uR8EE6X/5xgsy4cCJskown4R984pbH5v0pCa74PhZWKnhV99WnoU2q2u38F1+wTlAKytwQSOn3AU0wpkHd9cCOl4eZCRVDFSr96h2fMaWbSXk3SQn8tdvqRUkcA5gV4Fp/cH/gZU3Y1n5zhFo2sneMOlcyPVj2FehUY7oE6MzTaQ+qdEIdN7mQrdQUCNVjdfTBCjB0/2STtOSlbkY7bWVST/tQTl8V+O7mfi3AOWUxxSw45gK9RLhzQzaWXrXZrW6CIC9nNg2BgKlyvvy2nbc6ycPY=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dde5dfb7-479b-4ff0-f147-08d824afc3b8
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Jul 2020 09:00:59.7707
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3mETqDGuLhm6YkXvBDFf4FhILbINxnkqDIAiCERHIF377IlOFMjEelWibViDry0SilEyX9ZLvfggzC2phrwPNA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB0346
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
available in mainline/anup/riscv-hyp-ext-v0.6.1 branch at:
https://github.com/kvm-riscv/qemu.git

Changes since v3:
 - Rebased on recent commit 351d931f496aeb2e97b8daa44c943d8b59351d07
 - Improved kvm_cpu__show_registers() implementation

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
  update_headers: Sync-up ABI headers with Linux-5.8-rc4
  riscv: Initial skeletal support
  riscv: Implement Guest/VM arch functions
  riscv: Implement Guest/VM VCPU arch functions
  riscv: Add PLIC device emulation
  riscv: Generate FDT at runtime for Guest/VM
  riscv: Handle SBI calls forwarded to user space
  riscv: Generate PCI host DT node

 INSTALL                             |   7 +-
 Makefile                            |  24 +-
 arm/aarch64/include/asm/kvm.h       |  21 +-
 include/linux/kvm.h                 |  95 ++++-
 powerpc/include/asm/kvm.h           |   3 +
 riscv/fdt.c                         | 195 ++++++++++
 riscv/include/asm/kvm.h             | 127 +++++++
 riscv/include/kvm/barrier.h         |  14 +
 riscv/include/kvm/fdt-arch.h        |   8 +
 riscv/include/kvm/kvm-arch.h        |  85 +++++
 riscv/include/kvm/kvm-config-arch.h |  15 +
 riscv/include/kvm/kvm-cpu-arch.h    |  51 +++
 riscv/include/kvm/sbi.h             |  48 +++
 riscv/ioport.c                      |  12 +
 riscv/irq.c                         |  13 +
 riscv/kvm-cpu.c                     | 490 ++++++++++++++++++++++++
 riscv/kvm.c                         | 174 +++++++++
 riscv/pci.c                         | 109 ++++++
 riscv/plic.c                        | 563 ++++++++++++++++++++++++++++
 util/update_headers.sh              |   2 +-
 x86/include/asm/kvm.h               |  21 +-
 21 files changed, 2063 insertions(+), 14 deletions(-)
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
#### [PATCH v4 0/9] KVM: nSVM: fixes for CR3/MMU switch upon nested guest
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Jul 10 14:11:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11656773
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BCD6913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 14:13:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 612232083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 14:13:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i+rSYatf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728042AbgGJOMJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 10:12:09 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:22836 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727861AbgGJOMI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 10:12:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594390327;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tC/RDuBXGV/0eBPfyMsRxhpj4+FXW/fTZ0b83kArGak=;
        b=i+rSYatf8DuJcr6S6MR9boPxcOpW8fI4vMGGLt6kCpibNhGHiQddatCesT6IbXb9Ifa6OU
        qJTWnJfTQqFtsPHCTQ0YMyuRZiQFDmthojnlnwRRHf4PFof6bAMMmmtcIM3BxU12k9kJmC
        S1dlwtPfYggU6N6QPD7pVKFIQOEubnc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-20-8WEcPZc2OI29-Fy4J8_xCg-1; Fri, 10 Jul 2020 10:12:03 -0400
X-MC-Unique: 8WEcPZc2OI29-Fy4J8_xCg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8B2B8186A8E3;
        Fri, 10 Jul 2020 14:12:01 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EF53774F5E;
        Fri, 10 Jul 2020 14:11:58 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/9] KVM: nSVM: fixes for CR3/MMU switch upon nested guest
 entry/exit
Date: Fri, 10 Jul 2020 16:11:48 +0200
Message-Id: <20200710141157.1640173-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v3:
- Swapped my "KVM: nSVM: stop dereferencing vcpu->arch.mmu to get the
 context in kvm_init_shadow{,_npt}_mmu()" with Paolo's "KVM: MMU: stop
 dereferencing vcpu->arch.mmu to get the context for MMU init".
- keeping nested_svm_init_mmu_context() in nested_prepare_vmcb_control()
 as this is also used from svm_set_nested_state() [Paolo],
 nested_svm_load_cr3() becomes a separate step in enter_svm_guest_mode().
- nested_prepare_vmcb_save() remains 'void' [Paolo]

Original description:

This is a successor of "[PATCH v2 0/3] KVM: nSVM: fix #TF from CR3 switch
when entering guest" and "[PATCH] KVM: x86: drop erroneous mmu_check_root()
from fast_pgd_switch()".

The snowball is growing fast! It all started with an intention to fix
the particular 'tripple fault' issue (now fixed by PATCH7) but now we
also get rid of unconditional kvm_mmu_reset_context() upon nested guest
entry/exit and make the code resemble nVMX. There is still a huge room
for further improvement (proper error propagation, removing unconditional
MMU sync/TLB flush,...) but at least we're making some progress.

Tested with kvm selftests/kvm-unit-tests and by running nested Hyper-V
on KVM. The series doesn't seem to introduce any new issues.

Paolo Bonzini (1):
  KVM: MMU: stop dereferencing vcpu->arch.mmu to get the context for MMU
    init

Vitaly Kuznetsov (8):
  KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
  KVM: nSVM: reset nested_run_pending upon nested_svm_vmrun_msrpm()
    failure
  KVM: nSVM: prepare to handle errors from enter_svm_guest_mode()
  KVM: nSVM: introduce nested_svm_load_cr3()/nested_npt_enabled()
  KVM: nSVM: move kvm_set_cr3() after nested_svm_uninit_mmu_context()
  KVM: nSVM: implement nested_svm_load_cr3() and use it for host->guest
    switch
  KVM: nSVM: use nested_svm_load_cr3() on guest->host switch
  KVM: x86: drop superfluous mmu_check_root() from fast_pgd_switch()

 arch/x86/kvm/mmu.h        |  3 +-
 arch/x86/kvm/mmu/mmu.c    | 45 ++++++++++++------
 arch/x86/kvm/svm/nested.c | 97 ++++++++++++++++++++++++++++-----------
 arch/x86/kvm/svm/svm.c    |  6 ++-
 arch/x86/kvm/svm/svm.h    |  4 +-
 5 files changed, 110 insertions(+), 45 deletions(-)
```
#### [PATCH v3 0/9] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Fri Jul 10 15:48:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11656885
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0516C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE92720748
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:48:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F6tn6DCu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727978AbgGJPsX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 11:48:23 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:30709 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726965AbgGJPsX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 11:48:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594396102;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qnq1BGapFhMZc1AmRLOzTnZddFrUvqx4x+MyFf6t4sA=;
        b=F6tn6DCuvzmcyA4Pd8CrjWORmtyIQh4Bqmg/Z63WqnTA3sV6IRTtn0nh5xagpqycDzoZDY
        6TPvhHGLNmAM0gku4UV7Hzgo+fS7YLY3elTJUdsnX64yhsgL4LDeAowV+Kg3XSQge8H4Ad
        iSmh5XvYglD+5ygyhWypKuf7HuUh2tI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-447-kURzJpZRPQyy5obrA0h2yA-1; Fri, 10 Jul 2020 11:48:20 -0400
X-MC-Unique: kURzJpZRPQyy5obrA0h2yA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 516A68015F3;
        Fri, 10 Jul 2020 15:48:19 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-235.ams2.redhat.com
 [10.36.114.235])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BFA8C7EFA3;
        Fri, 10 Jul 2020 15:48:13 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org,
        Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH v3 0/9] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
Date: Fri, 10 Jul 2020 17:48:02 +0200
Message-Id: <20200710154811.418214-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When EPT is enabled, KVM does not really look at guest physical
address size. Address bits above maximum physical memory size are reserved.
Because KVM does not look at these guest physical addresses, it currently
effectively supports guest physical address sizes equal to the host.

This can be problem when having a mixed setup of machines with 5-level page
tables and machines with 4-level page tables, as live migration can change
MAXPHYADDR while the guest runs, which can theoretically introduce bugs.

In this patch series we add checks on guest physical addresses in EPT
violation/misconfig and NPF vmexits and if needed inject the proper
page faults in the guest.

A more subtle issue is when the host MAXPHYADDR is larger than that of the
guest. Page faults caused by reserved bits on the guest won't cause an EPT
violation/NPF and hence we also check guest MAXPHYADDR and add PFERR_RSVD_MASK
error code to the page fault if needed.

----

Changes from v2:
- Drop support for this feature on AMD processors after discussion with AMD


Mohammed Gamal (5):
  KVM: x86: Add helper functions for illegal GPA checking and page fault
    injection
  KVM: x86: mmu: Move translate_gpa() to mmu.c
  KVM: x86: mmu: Add guest physical address check in translate_gpa()
  KVM: VMX: Add guest physical address check in EPT violation and
    misconfig
  KVM: x86: SVM: VMX: Make GUEST_MAXPHYADDR < HOST_MAXPHYADDR support
    configurable

Paolo Bonzini (4):
  KVM: x86: rename update_bp_intercept to update_exception_bitmap
  KVM: x86: update exception bitmap on CPUID changes
  KVM: VMX: introduce vmx_need_pf_intercept
  KVM: VMX: optimize #PF injection when MAXPHYADDR does not match

 arch/x86/include/asm/kvm_host.h | 10 ++------
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/mmu.h              |  6 +++++
 arch/x86/kvm/mmu/mmu.c          | 12 +++++++++
 arch/x86/kvm/svm/svm.c          | 22 +++++++++++++---
 arch/x86/kvm/vmx/nested.c       | 28 ++++++++++++--------
 arch/x86/kvm/vmx/vmx.c          | 45 +++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h          |  6 +++++
 arch/x86/kvm/x86.c              | 29 ++++++++++++++++++++-
 arch/x86/kvm/x86.h              |  1 +
 include/uapi/linux/kvm.h        |  1 +
 11 files changed, 133 insertions(+), 29 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] x86: svm: bare-metal fixes
##### From: Nadav Amit <namit@vmware.com>

```c
From patchwork Fri Jul 10 18:33:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11657239
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B4E9914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 18:35:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A42712076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 18:35:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728135AbgGJSfn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 14:35:43 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:7518 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727091AbgGJSfn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 14:35:43 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 10 Jul 2020 11:35:38 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id C431440CB1;
        Fri, 10 Jul 2020 11:35:42 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 0/4] x86: svm: bare-metal fixes
Date: Fri, 10 Jul 2020 11:33:16 -0700
Message-ID: <20200710183320.27266-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches are intended to allow the svm tests to run on bare-metal.
The second patch indicates there is a bug in KVM.

Unfortunately, two tests still fail on bare-metal for reasons that I
could not figure out, with my somewhat limited SVM knowledge.

The first failure is "direct NMI while running guest". For some reason
the NMI is not delivered. Note that "direct NMI + hlt" and others pass.

The second is npt_rw_pfwalk_check. Even after the relevant fixes,
exit_info_2 has a mismatch, when the expected value (of the faulting
guest physical address) is 0x641000 and the actual is 0x641208. It might
be related to the fact that the physical server has more memory, but I
could not reproduce it on a VM with more physical memory.

Nadav Amit (4):
  x86: svm: clear CR4.DE on DR intercept test
  x86: svm: present bit is set on nested page-faults
  x86: remove blind writes from setup_mmu()
  x86: Allow to limit maximum RAM address

 lib/x86/fwcfg.c | 4 ++++
 lib/x86/fwcfg.h | 1 +
 lib/x86/setup.c | 7 +++++++
 lib/x86/vm.c    | 3 ---
 x86/svm_tests.c | 5 +++--
 5 files changed, 15 insertions(+), 5 deletions(-)
```
