

#### [PATCH v18 00/18] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>
From: Anup Patel <anup@brainfault.org>

```c
From patchwork Wed May 19 03:35:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12266103
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF710C433ED
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEBB161184
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 03:36:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236825AbhESDhi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 23:37:38 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:58230 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235058AbhESDhi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 23:37:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1621395378; x=1652931378;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=T928rnrPgluU0UhJVYwE+uScXpesaiL3M/ku4yQib5o=;
  b=Q0untvEF73n7ZhRcZNStTaVcrpMUPuAwNRuioxU6sKE/HFXRoiuwcTSd
   134M5TwM7vKNmC7L6SOBHl42qIOQXut4en4KQERu9loh+gPjyi8EQvY+y
   AgcaZv6Ast5x4PzcZXFR2aLF6TuPc8UNEwFHCi08rXGPlNWUbCKsE+Wvl
   ZqVbTKTzVmf7MvXMtT8eNhTkm+ugFGvqcbGl+6O5f0t6m1YQaYZFQlTDD
   chIIebjv+iC2TXDF85rwFXlz/R6iPp3+LiMCBhjdkUs6o9MUFvzwWGGZU
   o6Wpd+QsMoABfOwFwx/oknOKAgpTOxasfxlRJMa6cU5dPicHNa2goR1zt
   g==;
IronPort-SDR: 
 Mmv8cqc1Sa1u0CoESzgHz7Pcz6sDJcwX1wdQpG3uvk1LhkgJA8THTgEscF0kTqw+NEILugeOPl
 3SI6AHnnULwETpJTaFVYa2fNEscJXMzpp9G5qEjwXwA8xmgQX5uZ4CkLBjOTW+NULM5js2/Ma1
 ioXFxX0uGiF80XL4k2fynJA19YTFDn45wATxpiiEikMc1Kkt3T5c+OGv39Ebp0PHfAMI7TMRkn
 VYsHsxtYPNZ3pIs/ytiT5UxNtD97/+OeLwPR4Ria84EsvTg53FZd+mVV+wbAMUoYzG4hLKrSrr
 ipw=
X-IronPort-AV: E=Sophos;i="5.82,311,1613404800";
   d="scan'208";a="168652736"
Received: from mail-co1nam11lp2169.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.169])
  by ob1.hgst.iphmx.com with ESMTP; 19 May 2021 11:36:18 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=GBKQgGs4bZXWRtwqvUizVIcHOfja1rmnWPlWuk2bHGHlWfRJ8aprALZuR5vp+zaPRCpafDDlvZByScrLibzWo/t8oWh+4BoPBJUaLq+pPlkR1SgQWmVd01Gyht57qf3qsLZLoBEx9NutT3pOVchk/Mok1SBKxu6pMjQITF3YmU5cIe4VB6rS1frtosgqLFN8l2r9zd2kqSL0O/e1xpbcsoAkvrbHPyJmgshleHn/CxMgzEjk3PA9tG8x39/TwgvM6eaTGCdOsCKT5z9jIHY4q3sM6ao0DcANV3ofdiXiMAA5Gjf0DsqYlC8u3gNlruoSFd99eQNDTvDiGKxfvmYOqw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=osCqAPJkD6g0ggfoqkXxp+33qJgrlILQhlCFsEQHuOw=;
 b=a6CQs/Z6FBpyck0oVVVf6BWdr/BVKFOW2eVog1LJvN4KWxqIwRIe/kG/WVwhAVkVa05eKENr+ilBR4IRhCd6w1qLiUpVjEjqT0lS7d3Em3Sh5D8OlGbPL6ygBrEjEIrtL/mhoEyDjvGCiryiGxKdGG4A+ojcPTqe+Q7PHwNp9d6EFFkdrE7VEgEQo8x9TthJcAgkeLy8GsPs4pZsRZqUQewyho31dMNv8kfiZGkvJSowqbHfTVIMLshoQIiBUMsBfgHH30cKKoaFmtanqeVJqI7gO+pFYr27yOpylK6SPO9v7y/1MVKmtZa2FBWGBWGIEzv6i1r1u3sEgjSzqVCjnQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=osCqAPJkD6g0ggfoqkXxp+33qJgrlILQhlCFsEQHuOw=;
 b=q75CcJUXKLGyg/NGiV8f/jrwUMD1YcTVq1StXl/m5yJvdO7vujN1s7XHcd+ij3vz45Tea46uaVHEtZdzCG95wjv90smFQaD7BT1+AN1JOg0S73usFXrTxjl2P5vgUoFFhPVWqZqNPRy+ztq2a4MFZxuK2+uM5RfjDKuumQ9vxg8=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from CO6PR04MB7812.namprd04.prod.outlook.com (2603:10b6:303:138::6)
 by CO6PR04MB7761.namprd04.prod.outlook.com (2603:10b6:5:35f::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Wed, 19 May
 2021 03:36:17 +0000
Received: from CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50]) by CO6PR04MB7812.namprd04.prod.outlook.com
 ([fe80::88a0:bf18:b01d:1a50%4]) with mapi id 15.20.4129.033; Wed, 19 May 2021
 03:36:17 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-staging@lists.linux.dev
Subject: [PATCH v18 00/18] KVM RISC-V Support
Date: Wed, 19 May 2021 09:05:35 +0530
Message-Id: <20210519033553.1110536-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.179.32.148]
X-ClientProxiedBy: MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:20::19) To CO6PR04MB7812.namprd04.prod.outlook.com
 (2603:10b6:303:138::6)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.32.148) by
 MA1PR0101CA0057.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:20::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.25 via Frontend
 Transport; Wed, 19 May 2021 03:36:12 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 19c427e5-1a3c-4f75-851d-08d91a774295
X-MS-TrafficTypeDiagnostic: CO6PR04MB7761:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CO6PR04MB776105746584F190CBE24E878D2B9@CO6PR04MB7761.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 iqqhZJuMomzu2AE3I2OeAwVQ1uqPblNe1SbZ89PiJZhbD/dKCmv4qKTWQOejPwzEakd4L3cVnGEuUpWTsioaF4OSaSFZmdfQ+cjIA5yb+dA30c2RsT088tONtidTCycf1pQyAe6XmBypMGmAKyOsJeVUtkzgJtCkd4oDJcG6mbZe76IJuLZkpShEgVCx2AOi7K8R2qhevNteEA5MAJtk/HERZPtp99peV8T/XpBSvnkqwgYEdlnBuLcTg7/on48BAgGt5VbRIu2jGLDdhTc4rmk8FVmQwsZBKe+AcXF1w9qZINs41LHIGtkGY4UjHVrqoUjjM7d3opfyWPPq6Pu+xgKpeIpQuM6X7So+KzPYv305JXY6Oct50aCmDUwvkI/dlXUmLauAMh+EqyfWwSMv9j1Qx2LsEWw4VoCZizuoxq4H3ikNNBSXE+JXnmCIxqAz20yLQZ0c9FDN7nKbL+lnB4jdqSQfxGFjydJWZnUwgWV3NaBwbuRKWV6Ss4b0j0QLod4QClX73LMsLx03wrAx/wiRGvoaO25+0uT+ypRtPUaz07qPNjD0Z9qRbgi69mb10kIvmQvBLWNPHLeh2J1bPIyZjxq7XF8+tS+snqw8bd1FsS9pd4Klrz8Qg1MW/VjIi7t/OxhuCGJpHjuHrCPmpdMPKtadWYU8y3og6kco4TDNmJSKJMbfB9cdhlydmsDQB4lwZmnf7mDEFX5HEOU4GIqLKGDYir3eEaJcIPJ4+15GSMSeLbMllNwJp86FB/LiUqnnk3gq26auAMenn3DmQXuVYTobZpFYJoljW8QuLJGKiTW3x2HmuSEX9dq/OVWFJTAA8WNhp16wSbLE8wj8YQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CO6PR04MB7812.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(136003)(376002)(39860400002)(346002)(316002)(38350700002)(55016002)(38100700002)(66476007)(66946007)(1076003)(2616005)(186003)(5660300002)(4326008)(26005)(8936002)(478600001)(86362001)(2906002)(52116002)(7696005)(16526019)(110136005)(83380400001)(8676002)(6666004)(966005)(66556008)(36756003)(30864003)(7416002)(956004)(54906003)(44832011)(8886007)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 DpUQKgaoij+kk5lQnaEXtmQ32O6VMRSPoC6S3R2qzKiUTurq11Zigm7nQRjULl4MEZLHBfuEv/3cvA5vrd+mvlDyB/zG+/vRxak+iIYMuhEfZDusplX24LkIC/hON3hkH/6CSLdXeO9K5b872F2OaYU1FJRo9KtPwDvmUVzTfb+EJkq7/H4/gF8dIb6yzLBWjVcNN0fjsvHDyO3hC4sc01uoTddGmKwiF8WPNIWRcDMmmTdiJ3+KrpHZrlyTgyc1PJHHUy5jXTaZe9pEJXbY5kPW5mb/0Jx0uVSbmJaPnIrwd/kWX5OTX/VPSUvrMfAFtKU79MMlmia2BcgH7lpRMDMTj74gR9i5OAfppbUfnA+oH6i+3RRav84WEAjTmjRrMUo9MpUjOE0gEbpvd8xMacCw45T3AYVeci25jJbzOJ7MccxYKOP+RhFUHEathwO7vI1aI5+DMxQ9asPf7dcfSSiOO3SXfLGiEO3EW1+0O4yWjKPJT9U+tTlnqS2lFQT5tYSIQ9IiyEgvLnZWSOPh8qgTNpdsDU5KnTK2OajSl0vpTQiQjTYQ+0kgTcHE118v4wnZNz2rxj8ZU00Tc2idwjUNFcmTSIVPI7JfTiGVmNWsNP4dIkp6JeNdVtEdxu7R2mvgBPFun9HjBzqpaIn8f4wwpBxGMRDm1475Fh2Zt80fwYi7ay6k0noV+2w9C9BLaXV1jEczD+Da65tx7WJ2duvcsg+5nzS5eVPs+dlLtc0eWXMctH72h/vu4Qstp97nzNnTlF8vbihQIezWdN1ijZKxchKIypBEl/BRFhLNocLJMS65nATIltleF+lCT4YYZZYs25Q+/Mk8zIqEfFz3IbotHUhtik3Bs2+hoXfnQfd3wSFpk3Q7uAkfVNAZSqRzyZuOlokypwrF1ycxVRIW1NTlgwmXhAMFQ1MavoKNxA+LTpdoSeoCnQJV4ce+1FiBukO+dOBSIbA3SBl93lLwStVI3EKGK9e1qfR74zD2CL+TzGffzFGBAecoqPxCh4X3ELJMYmPmolFUSFZZJsRtiT3M+9OzC85svO6jMXkfunI2+qs1F3W+gqxpFyAuUN908oC4A3ai7oFizVz0z1AJtq52bibDP8wKgass+wmb8THBhYtMIai4io7ABXfGwIdtXFRhH8/Pfd/MmUWwWs7XAd+xy69ofXlJaNK+n4WR4aMyA2l0izUkiKYf3w1WyEq+9d2b8nT7KedSE1qySA/VK58C+SKF2aiLUn5Xn9P7Gvc6Pugl1z4r0p22YwqDHVQcaG4q/srA4X/tmFWlxzPutJ9kqC0/dAJlqdtpp0iGDSjcEjrmeus8iCcEQPKUhebI
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 19c427e5-1a3c-4f75-851d-08d91a774295
X-MS-Exchange-CrossTenant-AuthSource: CO6PR04MB7812.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 May 2021 03:36:17.4084
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 sG6fRhosZzNrfa0x8RaNCilb/XBCTuDv1DxoRxlg/NtN5HV6rxegn6DLSX7Ka6e1OeTxbL/2ZiRbMF5hDNdVMg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CO6PR04MB7761
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Anup Patel <anup@brainfault.org>

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v18 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v7 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in master branch at: https://git.qemu.org/git/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v17:
 - Rebased on Linux-5.13-rc2
 - Moved to new KVM MMU notifier APIs
 - Removed redundant kvm_arch_vcpu_uninit()
 - Moved KVM RISC-V sources to drivers/staging for compliance with
   Linux RISC-V patch acceptance policy

Changes since v16:
 - Rebased on Linux-5.12-rc5
 - Remove redundant kvm_arch_create_memslot(), kvm_arch_vcpu_setup(),
   kvm_arch_vcpu_init(), kvm_arch_has_vcpu_debugfs(), and
   kvm_arch_create_vcpu_debugfs() from PATCH5
 - Make stage2_wp_memory_region() and stage2_ioremap() as static
   in PATCH13

Changes since v15:
 - Rebased on Linux-5.11-rc3
 - Fixed kvm_stage2_map() to use gfn_to_pfn_prot() for determing
   writeability of a host pfn.
 - Use "__u64" in-place of "u64" and "__u32" in-place of "u32" for
   uapi/asm/kvm.h

Changes since v14:
 - Rebased on Linux-5.10-rc3
 - Fixed Stage2 (G-stage) PDG allocation to ensure it is 16KB aligned

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

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

Anup Patel (14):
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
  RISC-V: KVM: Move sources to drivers/staging directory
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst                | 193 +++-
 MAINTAINERS                                   |  11 +
 arch/riscv/Kconfig                            |   1 +
 arch/riscv/Makefile                           |   1 +
 arch/riscv/include/uapi/asm/kvm.h             | 128 +++
 drivers/clocksource/timer-riscv.c             |   9 +
 drivers/staging/riscv/kvm/Kconfig             |  36 +
 drivers/staging/riscv/kvm/Makefile            |  23 +
 drivers/staging/riscv/kvm/asm/kvm_csr.h       | 105 ++
 drivers/staging/riscv/kvm/asm/kvm_host.h      | 271 +++++
 drivers/staging/riscv/kvm/asm/kvm_types.h     |   7 +
 .../staging/riscv/kvm/asm/kvm_vcpu_timer.h    |  44 +
 drivers/staging/riscv/kvm/main.c              | 118 +++
 drivers/staging/riscv/kvm/mmu.c               | 802 ++++++++++++++
 drivers/staging/riscv/kvm/riscv_offsets.c     | 170 +++
 drivers/staging/riscv/kvm/tlb.S               |  74 ++
 drivers/staging/riscv/kvm/vcpu.c              | 997 ++++++++++++++++++
 drivers/staging/riscv/kvm/vcpu_exit.c         | 701 ++++++++++++
 drivers/staging/riscv/kvm/vcpu_sbi.c          | 173 +++
 drivers/staging/riscv/kvm/vcpu_switch.S       | 401 +++++++
 drivers/staging/riscv/kvm/vcpu_timer.c        | 225 ++++
 drivers/staging/riscv/kvm/vm.c                |  81 ++
 drivers/staging/riscv/kvm/vmid.c              | 120 +++
 include/clocksource/timer-riscv.h             |  16 +
 include/uapi/linux/kvm.h                      |   8 +
 25 files changed, 4706 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 drivers/staging/riscv/kvm/Kconfig
 create mode 100644 drivers/staging/riscv/kvm/Makefile
 create mode 100644 drivers/staging/riscv/kvm/asm/kvm_csr.h
 create mode 100644 drivers/staging/riscv/kvm/asm/kvm_host.h
 create mode 100644 drivers/staging/riscv/kvm/asm/kvm_types.h
 create mode 100644 drivers/staging/riscv/kvm/asm/kvm_vcpu_timer.h
 create mode 100644 drivers/staging/riscv/kvm/main.c
 create mode 100644 drivers/staging/riscv/kvm/mmu.c
 create mode 100644 drivers/staging/riscv/kvm/riscv_offsets.c
 create mode 100644 drivers/staging/riscv/kvm/tlb.S
 create mode 100644 drivers/staging/riscv/kvm/vcpu.c
 create mode 100644 drivers/staging/riscv/kvm/vcpu_exit.c
 create mode 100644 drivers/staging/riscv/kvm/vcpu_sbi.c
 create mode 100644 drivers/staging/riscv/kvm/vcpu_switch.S
 create mode 100644 drivers/staging/riscv/kvm/vcpu_timer.c
 create mode 100644 drivers/staging/riscv/kvm/vm.c
 create mode 100644 drivers/staging/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [kvm-unit-tests PATCH v3 0/6] s390x: uv: Extend guest test and add
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed May 19 07:40:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12266605
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9E66C433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:07:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD93561007
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:07:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236758AbhESIIw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 04:08:52 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17942 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235683AbhESIIv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 May 2021 04:08:51 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14J83pJ1081357;
        Wed, 19 May 2021 04:07:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=fYdLleFOEMY/oyxAzuS1SA9ft/aeIlge04AQUxk2Ueg=;
 b=a3mwC7gETkoMXWV4+Iy5GSmhLFZTxN8uQjYDqgNUOTpHZESKlUmsEk5YZXmrBDFjKWW3
 jkiRef+VjhgU1kU85PDZ5GuN2Xax3UIAvR5Zetlo1y/9QuTpEVrjVJsPsl2nijflZ5rJ
 oMniTza72t4ei9O00A85GC5kG6NAsWokU5rhFoD3Lictuv/iPKd6F4jih7fbTlcYSX9S
 OO966+3ICZFO6Ux0Rz3NXERT2taIRGR1FIc5cdOPU0BZil4FltCOyb7ibCj2wLfdqPGm
 cCSEyRFBbLymUXnW+lPm2mbDIXG9N1n+7gqI9brqqubI5WQ5+wmGTPHmnm4jOfy9ybId vQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj1rn80-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:07:32 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14J841Ot081806;
        Wed, 19 May 2021 04:07:31 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj1rn6m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:07:31 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14J7cQlQ025872;
        Wed, 19 May 2021 07:40:38 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03fra.de.ibm.com with ESMTP id 38j5x892gg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 07:40:38 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14J7eZMB63111662
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 May 2021 07:40:35 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7D1DAA405C;
        Wed, 19 May 2021 07:40:35 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B8389A405F;
        Wed, 19 May 2021 07:40:34 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 19 May 2021 07:40:34 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/6] s390x: uv: Extend guest test and add
 host test
Date: Wed, 19 May 2021 07:40:16 +0000
Message-Id: <20210519074022.7368-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: kg7dUF4trKY-fowOmQi3B4ks5krRJYFP
X-Proofpoint-ORIG-GUID: pzOVygziU9AEQe_04cjt5lXnzZlKsyST
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-19_02:2021-05-18,2021-05-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 lowpriorityscore=0 spamscore=0 clxscore=1015 phishscore=0 impostorscore=0
 bulkscore=0 malwarescore=0 priorityscore=1501 adultscore=0 mlxscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105190059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My stack of patches is starting to lean, so lets try to put some of
them upstream...

The first part is just additions to the UV guest test and a library
that makes checking the installed UV calls easier. Additionally we now
check for the proper UV share/unshare availability when allocating IO
memory instead of only relying on stfle 158.

The second part adds a UV host test with a large number UV of return
code checks.

v3:
	* Minor changes due to review
	* I'll pick this on Friday if there are no more remarks

v2:
	* Added rev-bys
	* Added stfle 158 check to uv_os_is_host/guest
	* Added asserts to uv_query_test_feature()
	  * Prevent specifying bit nr outside of range
	  * Prevent checking for features without having queried them
	* Added !feature bit check to uv guest/host invalid command test
	* Renamed uv_query_test_feature() to uv_query_test_call()

Janosch Frank (6):
  s390x: uv-guest: Add invalid share location test
  s390x: Add more Ultravisor command structure definitions
  s390x: uv: Add UV lib
  s390x: Test for share/unshare call support before using them
  s390x: uv-guest: Test invalid commands
  s390x: Add UV host test

 lib/s390x/asm/uv.h    | 152 ++++++++++++-
 lib/s390x/io.c        |   2 +
 lib/s390x/malloc_io.c |   5 +-
 lib/s390x/uv.c        |  45 ++++
 lib/s390x/uv.h        |  10 +
 s390x/Makefile        |   2 +
 s390x/uv-guest.c      |  60 +++++-
 s390x/uv-host.c       | 480 ++++++++++++++++++++++++++++++++++++++++++
 8 files changed, 743 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/uv.c
 create mode 100644 lib/s390x/uv.h
 create mode 100644 s390x/uv-host.c
Acked-by: Thomas Huth <thuth@redhat.com>
```
#### [kvm-unit-tests PATCH v2 0/3] s390x: cpumodel: Add sclp checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed May 19 08:26:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12266627
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B9B18C433ED
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:27:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2AC460240
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:27:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245169AbhESI3G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 04:29:06 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:25834 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S245141AbhESI3F (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 May 2021 04:29:05 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14J83mvE073641;
        Wed, 19 May 2021 04:27:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=A4DdO4Wl7QT1jblXnN6RsoPIDMfpmtxhWFkIPRD6V00=;
 b=myS0+IhHUAURyHggfpxlT9MzsivI7skMHOeruewnWAY1r14nPc5+4C2w+XX9z9HstaPV
 1alVyxYemwE4Qygek/awGA76SnaAelLONsNB9WU/MxHJuHUty/vsz5XDfK+UVjqhygJl
 33p2sMiFKfU8DxVS7hmV/gwS0kpA8ZASZ6xiT2+pjXuKuj0Duwlzd1YXVi91RRFhxlvD
 nQWaEOYB6JxGHfwFgegCddf710xw+3dEc9PvWmKNKgpcbLx8EN6QzzM22/mVtD2MpUV4
 EspLlbKyTGfKRINE9IdMrZslsONb98VLGYTDsECW6DgTTl9nze0Iso4vuelqp1Kexxoe rw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj1162h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:27:45 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14J83qm2074071;
        Wed, 19 May 2021 04:27:45 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38mxj11620-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 04:27:44 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14J8MMeJ003217;
        Wed, 19 May 2021 08:27:43 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma01fra.de.ibm.com with ESMTP id 38m1gv0ewx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 May 2021 08:27:43 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14J8Re9Y36045140
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 May 2021 08:27:40 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 17EA342045;
        Wed, 19 May 2021 08:27:40 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 49AEC42041;
        Wed, 19 May 2021 08:27:39 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 19 May 2021 08:27:39 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/3] s390x: cpumodel: Add sclp checks
Date: Wed, 19 May 2021 08:26:45 +0000
Message-Id: <20210519082648.46803-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: 0r9jNsgzMTqZMhei2Kg8tvH9WkOKtBNs
X-Proofpoint-ORIG-GUID: PzdhCvRqzL2d-Iz_SMpnUzh2VmLgUEh5
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-19_02:2021-05-18,2021-05-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 mlxlogscore=999 impostorscore=0 adultscore=0 bulkscore=0
 clxscore=1015 suspectscore=0 mlxscore=0 spamscore=0 lowpriorityscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105190059
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SCLP facilities have been a bit overlooked in cpumodel tests and have
recently caused some headaches. So let's extend the tests and the
library with a bit of sclp feature checking.

Based on the uv_host branch / patches.

v2:
	* Check bit instead of mask
	* Squashed fmt 2 and 4 patches into one

Janosch Frank (3):
  s390x: sclp: Only fetch read info byte 134 if cpu entries are above it
  lib: s390x: sclp: Extend feature probing
  s390x: cpumodel: FMT2 and FMT4 SCLP test

 lib/s390x/sclp.c | 23 +++++++++++++++-
 lib/s390x/sclp.h | 38 ++++++++++++++++++++++++--
 s390x/cpumodel.c | 71 +++++++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 127 insertions(+), 5 deletions(-)
```
#### [PATCH 00/10] Documentation build warning fixes
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Wed May 19 08:51:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12266665
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6FFDC43603
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:51:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB3EC6135C
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 08:51:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343921AbhESIxM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 04:53:12 -0400
Received: from mail.kernel.org ([198.145.29.99]:60252 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S245541AbhESIxL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 May 2021 04:53:11 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 5A3B560C3F;
        Wed, 19 May 2021 08:51:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1621414311;
        bh=Xxq1uGAbMGFgeGY3ywEv0OBhOMcnDBc4Aw7rV293abg=;
        h=From:To:Cc:Subject:Date:From;
        b=HDXmH4kOj1Ffc8/2cPIVagMkwv75xN8kuE4Rn2GW4zUfWOy+/uoxuQky8Dxr9RDVR
         fVbJMLGgIq+XN+7alWCEcvtKmIWWeiFvOiQyJ9+cMJ+eSmjCj1liIls/T2ERP28sI/
         Mx2fxh/6TMjsCdbJkuDfE+YtP5rjlL4GYJEyhOZQoAdSbeHyiSWV4ePGv7ROh0zXu8
         AjzAbT5IYTV7AdlhASpd63KP0Dt2giApS3oj5J8fG1nIer7c4N9j0aGbYuzwaHItI1
         /kiR1YGrJsdKvu92/Jkc0v9EXHz/fFBf6YBUXpnf+fLICsbgPu9SeBtSBORPjhj95H
         lVUyUg6TpgwrA==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1ljHvh-007gXv-8w; Wed, 19 May 2021 10:51:49 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>,
        Jonathan Corbet <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Daniel Thompson <daniel.thompson@linaro.org>,
        Jingoo Han <jingoohan1@gmail.com>,
        Jonathan Cameron <jic23@kernel.org>,
        Lars-Peter Clausen <lars@metafoo.de>,
        Lee Jones <lee.jones@linaro.org>,
        Linus Walleij <linus.walleij@linaro.org>,
        alsa-devel@alsa-project.org, dri-devel@lists.freedesktop.org,
        kvm@vger.kernel.org, linux-gpio@vger.kernel.org,
        linux-iio@vger.kernel.org, patches@opensource.cirrus.com
Subject: [PATCH 00/10] Documentation build warning fixes
Date: Wed, 19 May 2021 10:51:37 +0200
Message-Id: <cover.1621413933.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jon,

This small series contain a series of fixes for the documentation. it is
against your docs-next branch.

Three of the patches fix duplicated symbols at the ABI documents.
There are still some ABI warnings from IIO, but all but one were
already fixed at linux-next. So, hopefully, after having everything
merged, the ABI warnings will be solved.

Mauro Carvalho Chehab (10):
  docs: update sysfs-platform_profile.rst reference
  docs: vcpu-requests.rst: fix reference for atomic ops
  docs: translations/zh_CN: fix a typo at 8.Conclusion.rst
  docs: sched-bwc.rst: fix a typo on a doc name
  docs: update pin-control.rst references
  docs: virt: api.rst: fix a pointer to SGX documentation
  docs: ABI: iommu: remove duplicated definition for
    sysfs-kernel-iommu_groups
  docs: ABI: sysfs-class-backlight: unify ambient light zone nodes
  docs: ABI: sysfs-class-led-trigger-pattern: remove repeat duplication
  iio: documentation: fix a typo

 Documentation/ABI/testing/sysfs-bus-iio       |   4 +-
 .../ABI/testing/sysfs-class-backlight         | 100 ++++++++++++++++++
 .../ABI/testing/sysfs-class-backlight-adp5520 |  31 ------
 .../ABI/testing/sysfs-class-backlight-adp8860 |  37 -------
 .../sysfs-class-backlight-driver-adp8870      |  32 ------
 .../testing/sysfs-class-led-driver-el15203000 |   9 --
 .../testing/sysfs-class-led-trigger-pattern   |   3 +
 .../ABI/testing/sysfs-kernel-iommu_groups     |  12 +--
 Documentation/scheduler/sched-bwc.rst         |   2 +-
 .../zh_CN/process/8.Conclusion.rst            |   2 +-
 Documentation/virt/kvm/api.rst                |   2 +-
 Documentation/virt/kvm/vcpu-requests.rst      |   2 +-
 include/linux/device.h                        |   2 +-
 include/linux/mfd/madera/pdata.h              |   2 +-
 include/linux/pinctrl/pinconf-generic.h       |   2 +-
 include/linux/platform_profile.h              |   2 +-
 16 files changed, 117 insertions(+), 127 deletions(-)
 delete mode 100644 Documentation/ABI/testing/sysfs-class-backlight-adp5520
 delete mode 100644 Documentation/ABI/testing/sysfs-class-backlight-adp8860
 delete mode 100644 Documentation/ABI/testing/sysfs-class-backlight-driver-adp8870
 delete mode 100644 Documentation/ABI/testing/sysfs-class-led-driver-el15203000
```
#### [PATCH v2 0/8] x86/sev-es: Fixes for SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Wed May 19 13:52:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12267383
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DDE6C43461
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 13:53:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DCC86100C
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 13:53:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1353794AbhESNye (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 09:54:34 -0400
Received: from 8bytes.org ([81.169.241.247]:39974 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S239473AbhESNyc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 May 2021 09:54:32 -0400
Received: from cap.home.8bytes.org (p549ad305.dip0.t-ipconnect.de
 [84.154.211.5])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id EF587104;
        Wed, 19 May 2021 15:53:07 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org, Hyunwook Baek <baekhw@google.com>
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-coco@lists.linux.dev, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org
Subject: [PATCH v2 0/8] x86/sev-es: Fixes for SEV-ES Guest Support
Date: Wed, 19 May 2021 15:52:43 +0200
Message-Id: <20210519135251.30093-1-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here is the second version of my pending SEV-ES fixes. The most
important patches are patch 1 to 5, as they fix warnings and splats
that trigger with various debugging options are enabled.

Patches 6 to 8 fix a correctness issue in the instruction emulation
part of the #VC exception handler.

Please review.

Thanks,

	Joerg

Link to v1: https://lore.kernel.org/lkml/20210512075445.18935-1-joro@8bytes.org/

Changes since v1:

	- Documented why __get_user()/__put_user() are safe to use in
	  the #VC handlers memory access path.

	- Merged the revert into patch 3

	- Refactored code in the instruction decoder and added #GP
	  reporting when getting the instructions linear address fails.

Joerg Roedel (8):
  x86/sev-es: Don't return NULL from sev_es_get_ghcb()
  x86/sev-es: Forward page-faults which happen during emulation
  x86/sev-es: Use __put_user()/__get_user() for data accesses
  x86/sev-es: Fix error message in runtime #VC handler
  x86/sev-es: Leave NMI-mode before sending signals
  x86/insn-eval: Make 0 a valid RIP for insn_get_effective_ip()
  x86/insn: Extend error reporting from
    insn_fetch_from_user[_inatomic]()
  x86/sev-es: Propagate #GP if getting linear instruction address failed

 arch/x86/include/asm/insn-eval.h |   6 +-
 arch/x86/kernel/sev.c            | 127 +++++++++++++++++++++----------
 arch/x86/kernel/umip.c           |  10 +--
 arch/x86/lib/insn-eval.c         |  52 ++++++++-----
 4 files changed, 129 insertions(+), 66 deletions(-)


base-commit: a50c5bebc99c525e7fbc059988c6a5ab8680cb76
```
#### [PATCH v2 0/5] KVM: arm64: selftests: Fix get-reg-list
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Wed May 19 14:07:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12267415
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4BD3C433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 14:07:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A840961244
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 14:07:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1353874AbhESOIx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 10:08:53 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:49168 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1353848AbhESOIw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 May 2021 10:08:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621433252;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=w6Ik3ix00seen7f0ACeVszG5V6/4OpjDNwj8RlI2yS0=;
        b=DYzzXSY/0ivsrY71xJGQc3i51sSTOk3RWV/piOgUJACnTlXQlieBTbpMJCyuuU2ob+hEwh
        AbsLoHNQzbLQZl51BZ1f4FCGN+GVrr32bNWDVY5nHPJAB4auySmlQQf45L/AEhxwiMAYfA
        fE9mD4bIC9N4ZBZfmhjRrJQCy4zFIc8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-418-CPE_d8ZRPu6BV6ilekZGDg-1; Wed, 19 May 2021 10:07:30 -0400
X-MC-Unique: CPE_d8ZRPu6BV6ilekZGDg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 479B0180FD68;
        Wed, 19 May 2021 14:07:29 +0000 (UTC)
Received: from gator.redhat.com (unknown [10.40.192.248])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 350C710013C1;
        Wed, 19 May 2021 14:07:27 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, ricarkol@google.com, eric.auger@redhat.com,
        alexandru.elisei@arm.com, pbonzini@redhat.com
Subject: [PATCH v2 0/5] KVM: arm64: selftests: Fix get-reg-list
Date: Wed, 19 May 2021 16:07:21 +0200
Message-Id: <20210519140726.892632-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
 - Removed some cruft left over from a previous more complex design of the
   config command line parser
 - Dropped the list printing factor out patch as it's not necessary
 - Added a 'PASS' output for passing tests to allow testers to feel good
 - Changed the "up to date with kernel" comment to reference 5.13.0-rc2


Since KVM commit 11663111cd49 ("KVM: arm64: Hide PMU registers from
userspace when not available") the get-reg-list* tests have been
failing with

  ...
  ... There are 74 missing registers.
  The following lines are missing registers:
  ...

where the 74 missing registers are all PMU registers. This isn't a
bug in KVM that the selftest found, even though it's true that a
KVM userspace that wasn't setting the KVM_ARM_VCPU_PMU_V3 VCPU
flag, but still expecting the PMU registers to be in the reg-list,
would suddenly no longer have their expectations met. In that case,
the expectations were wrong, though, so that KVM userspace needs to
be fixed, and so does this selftest.

We could fix the test with a one-liner since we just need a

  init->features[0] |= 1 << KVM_ARM_VCPU_PMU_V3;

in prepare_vcpu_init(), but that's too easy, so here's a 5 patch patch
series instead :-)  The reason for all the patches and the heavy diffstat
is to prepare for other vcpu configuration testing, e.g. ptrauth and mte.
With the refactoring done in this series, we should now be able to easily
add register sublists and vcpu configs to the get-reg-list test, as the
last patch demonstrates with the pmu fix.

Thanks,
drew


Andrew Jones (5):
  KVM: arm64: selftests: get-reg-list: Introduce vcpu configs
  KVM: arm64: selftests: get-reg-list: Prepare to run multiple configs
    at once
  KVM: arm64: selftests: get-reg-list: Provide config selection option
  KVM: arm64: selftests: get-reg-list: Remove get-reg-list-sve
  KVM: arm64: selftests: get-reg-list: Split base and pmu registers

 tools/testing/selftests/kvm/.gitignore        |   1 -
 tools/testing/selftests/kvm/Makefile          |   1 -
 .../selftests/kvm/aarch64/get-reg-list-sve.c  |   3 -
 .../selftests/kvm/aarch64/get-reg-list.c      | 388 ++++++++++++------
 4 files changed, 271 insertions(+), 122 deletions(-)
 delete mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list-sve.c
```
#### [PATCH v2 00/10] KVM: selftests: exercise userfaultfd minor faults
##### From: Axel Rasmussen <axelrasmussen@google.com>

```c
From patchwork Wed May 19 20:03:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Axel Rasmussen <axelrasmussen@google.com>
X-Patchwork-Id: 12268419
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 543EDC433B4
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 20:03:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31486611BD
	for <kvm@archiver.kernel.org>; Wed, 19 May 2021 20:03:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232572AbhESUFK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 19 May 2021 16:05:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33108 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232471AbhESUFJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 May 2021 16:05:09 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6628AC061760
        for <kvm@vger.kernel.org>; Wed, 19 May 2021 13:03:48 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 p138-20020a2542900000b029051304a381d9so7099643yba.20
        for <kvm@vger.kernel.org>; Wed, 19 May 2021 13:03:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=TRzyq4oNy0xbwezI+8cBZnf/nTLSb+t8cRqYWcWY/Eg=;
        b=CxvtArSRKX6OIHDHNbloVqlUItuDs1pUVWO461kxImFFcH32VxsUk8wQRTWZwQ6azV
         xH9kIDgHSGkmKm3QMzYT8uD5SUun0xyFySIS+XdVS0A3rqkbCqR3aWZIGyOmeKCdjjEj
         ZC2H/hOoPa5G7ZMVYY0Ra3jjN+vFL3opMB+3VKbRuP9Um+YHZNcNdhuIUS/xWwqbJH+i
         jXPI/8k+0f6H7op/p+Aa0EWorl/GZObZys8KJJnM7xcqT6q9C+QoQGA3cOfd6VG2rF60
         ETVQ91+uqYc3SF2jfC1c2q0N8ia/NuFB3pTg7Cf2b5wJCmdp2TJch+OuowdqLY9nCkD2
         dOmA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=TRzyq4oNy0xbwezI+8cBZnf/nTLSb+t8cRqYWcWY/Eg=;
        b=hojmyThQqJ0PamAHoNI65yyWgdcjW89H/cA/y/m2MctZt5T8Tq9vmQV4EwV9ZDXKSr
         2Nhzp545nWyaoDrQL9QDRwoPbCrkOFY3X68TZwgBZ6siS24NZ44zJ8M+Kd/d4RdUFvD5
         OrnL/rpCcaYJuE4zVRvowySu840dhtgUNN/vappkzvRTBaZZfKIkzsPFcsRal+jtgXnl
         cTbR8AnOfLcuwnIch6XMM3Gn3698Ctg5Zrked4x1eyOfVPAZ5kBKBfusOWuLtXX53NLN
         sg9Wts8yP1A/W3rfoe1gBomtHjKDL15DcOVtqq4TThHx3CmeIx1cdvqMYROnAsH2BdrU
         2Gpg==
X-Gm-Message-State: AOAM533eVAOe/8xDGAVsPMBjHTdFPpLsiBmmCgr4AUmeJIXD4gt9JBm3
        NP3LJZ7UaaUCYN5Yi/xu2sGj35ems/MXf504Z/Vb
X-Google-Smtp-Source: 
 ABdhPJyFo1HijtaGGGcxKGVnq1SWKSvHoMWpsxuc+TwmN6hh5Zag+cdBMzwAriowHUIKTHlRVkauQ7YZIi2LKSLHBpWj
X-Received: from ajr0.svl.corp.google.com
 ([2620:15c:2cd:203:7eb5:10bb:834a:d5ec])
 (user=axelrasmussen job=sendgmr) by 2002:a25:8205:: with SMTP id
 q5mr1802119ybk.170.1621454627516; Wed, 19 May 2021 13:03:47 -0700 (PDT)
Date: Wed, 19 May 2021 13:03:29 -0700
Message-Id: <20210519200339.829146-1-axelrasmussen@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH v2 00/10] KVM: selftests: exercise userfaultfd minor faults
From: Axel Rasmussen <axelrasmussen@google.com>
To: Aaron Lewis <aaronlewis@google.com>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Ben Gardon <bgardon@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Jacob Xu <jacobhxu@google.com>,
        Makarand Sonare <makarandsonare@google.com>,
        Oliver Upton <oupton@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>, Shuah Khan <shuah@kernel.org>,
        Yanan Wang <wangyanan55@huawei.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org,
        Axel Rasmussen <axelrasmussen@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Base
====

These patches are based upon Andrew Morton's v5.13-rc1-mmots-2021-05-13-17-23
tag. This is because this series depends on:

- UFFD minor fault support for hugetlbfs (in v5.13-rc1) [1]
- UFFD minor fault support for shmem (in Andrew's tree) [2]

[1] https://lore.kernel.org/linux-fsdevel/20210301222728.176417-1-axelrasmussen@google.com/
[2] https://lore.kernel.org/patchwork/cover/1420967/

Changelog
=========

v1->v2:
- Picked up Reviewed-by's.
- Change backing_src_is_shared() to check the flags, instead of the type. This
  makes it robust to adding new backing source types in the future.
- Add another commit which refactors setup_demand_paging() error handling.
- Print UFFD ioctl type once in setup_demand_paging, instead of on every page-in
  operation.
- Expand comment on why we use MFD_HUGETLB instead of MAP_HUGETLB.
- Reworded comment on addr_gpa2alias.
- Moved demand_paging_test.c timing calls outside of the if (), deduplicating
  them.
- Split trivial comment / logging fixups into a separate commit.
- Add another commit which prints a clarifying message on test skip.
- Split the commit allowing backing src_type to be modified in two.
- Split the commit adding the shmem backing type in two.
- Rebased onto v5.13-rc1-mmots-2021-05-13-17-23.

Overview
========

Minor fault handling is a new userfaultfd feature whose goal is generally to
improve performance. In particular, it is intended for use with demand paging.
There are more details in the cover letters for this new feature (linked above),
but at a high level the idea is that we think of these three phases of live
migration of a VM:

1. Precopy, where we copy "some" pages from the source to the target, while the
   VM is still running on the source machine.
2. Blackout, where execution stops on the source, and begins on the target.
3. Postcopy, where the VM is running on the target, some pages are already up
   to date, and others are not (because they weren't copied, or were modified
   after being copied).

During postcopy, the first time the guest touches memory, we intercept a minor
fault. Userspace checks whether or not the page is already up to date. If
needed, we copy the final version of the page from the soure machine. This
could be done with RDMA for example, to do it truly in place / with no copying.
At this point, all that's left is to setup PTEs for the guest: so we issue
UFFDIO_CONTINUE. No copying or page allocation needed.

Because of this use case, it's useful to exercise this as part of the demand
paging test. It lets us ensure the use case works correctly end-to-end, and also
gives us an in-tree way to profile the end-to-end flow for future performance
improvements.

Axel Rasmussen (10):
  KVM: selftests: trivial comment/logging fixes
  KVM: selftests: simplify setup_demand_paging error handling
  KVM: selftests: print a message when skipping KVM tests
  KVM: selftests: compute correct demand paging size
  KVM: selftests: allow different backing source types
  KVM: selftests: refactor vm_mem_backing_src_type flags
  KVM: selftests: add shmem backing source type
  KVM: selftests: create alias mappings when using shared memory
  KVM: selftests: allow using UFFD minor faults for demand paging
  KVM: selftests: add shared hugetlbfs backing source type

 .../selftests/kvm/demand_paging_test.c        | 175 +++++++++++-------
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 .../testing/selftests/kvm/include/test_util.h |  12 ++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  84 ++++++++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 tools/testing/selftests/kvm/lib/test_util.c   |  51 +++--
 6 files changed, 238 insertions(+), 87 deletions(-)
---
2.31.1.751.gd2f1c929bd-goog
```
