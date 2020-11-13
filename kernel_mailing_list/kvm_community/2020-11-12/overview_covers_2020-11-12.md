

#### [PATCH 0/2] Fix AMD SEV guest boot issue with PCID feature
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Thu Nov 12 00:28:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11898877
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50DAEC388F9
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 01:53:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B76042076E
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 01:53:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="uvCICGrm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727977AbgKLBby (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 20:31:54 -0500
Received: from mail-dm6nam10on2072.outbound.protection.outlook.com
 ([40.107.93.72]:10913
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728060AbgKLA2S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 19:28:18 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Z5tMhbtBbYIsEEE0m64sOE4Iuc2EyZEj+LqT4/BvyOt5SYoUQyunVp4sA1AE1a/2YZz0ihOYgARm1xv9rd7+2AF6Lz7OWi8qGWRWEzjS54Z0Xm0ObM1cygC4qc/+rEcYiYjhD2IdWTN/5lwWhKaxkWsg2NtnyKAXc+AA3wwDAbGf88g1v09gUfBE2rN8xC7LdZdEex7QgYA3rLd/S1+ktGz7sW/z5SkW1T2EF933YSoa57Z4yJPxT+OM/92QHSVsMhapyIa6s00sdJ9f3LVcQPymFuJl4mZlvh3uhdkSgVEGoN4FpjaeCjtvlgeOuZHq5Xrhc22ytfWiZvcm+zNZFA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CXWP/pqgaf6ycheaTGEUkYexDy0qC61GELpWs1z5IIQ=;
 b=gQ3L0QXSxMiHRAYKihj8jk6HwUBKFqlO3+TPkquUQiX2U8NaMVNYmzDOW3D7jXBfPNyvEVu/jJ2BylQ1H3m1H28zqp8pYCn/3ik+xsco6Do3UfOOjSNWtG2x13pVcXZgEl+O9JRgvn+kTCaqk0PbbugJ+3FDKTPuPl18HgizcBEKYqAXEYDzaoaQPG7lSgLeb9LLeTXtf6/kHEnm95JGkUTWZDmjV1IFkWafZyt5qDZ7urB3Gr9kk2We9YjhkiDsc3ovs5JwlXV2LS8JqHQPk0TuHwnWYtcIxgN5GCf0Qk2RfYGqwFr2EqpA7lphEoa9IAXx9LRBo7yWKQaCzgbp8Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CXWP/pqgaf6ycheaTGEUkYexDy0qC61GELpWs1z5IIQ=;
 b=uvCICGrmkq50OTGVwPp0uesWAUDYCNwmC/Ta3EdO5xF+q2cyHzMfDzUZDH5R2qYxlxkXa5jD5u5V09qo7lhrX/Zx64QHfPkR+m6oeZoRLGkmeF1ycfEFAwuIiAYp33RBK1ktkUER0Xv+zvuHdXqFjtStRO18am3delVbkq8fcIM=
Authentication-Results: google.com; dkim=none (message not signed)
 header.d=none;google.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB2797.namprd12.prod.outlook.com (2603:10b6:805:6e::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Thu, 12 Nov
 2020 00:28:14 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3541.026; Thu, 12 Nov 2020
 00:28:13 +0000
Subject: [PATCH 0/2] Fix AMD SEV guest boot issue with PCID feature
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: junaids@google.com, wanpengli@tencent.com, kvm@vger.kernel.org,
        joro@8bytes.org, x86@kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de, vkuznets@redhat.com,
        jmattson@google.com
Date: Wed, 11 Nov 2020 18:28:11 -0600
Message-ID: <160514082171.31583.9995411273370528911.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR12CA0022.namprd12.prod.outlook.com (2603:10b6:4:1::32)
 To SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 DM5PR12CA0022.namprd12.prod.outlook.com (2603:10b6:4:1::32) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.25 via Frontend
 Transport; Thu, 12 Nov 2020 00:28:12 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 3445ed42-68a7-40b4-b20d-08d886a1d769
X-MS-TrafficTypeDiagnostic: SN6PR12MB2797:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2797618029B362462BBD8AC395E70@SN6PR12MB2797.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6loHngtGbl4CbgfmCfW0IYZFfJmEvTlUiOMqa6E+Rc1C1+7xWYe6P5ePszJdSVid7KG32rP/qExgGCq1hjXkTr+i8gL+KrTXxvyohYzPZveoMx+X1NWshBBnZFSNDtOdqWV5I+T3ctP1weZaKkTWmWjUPEqO+qqkFiKXyW//ZLGvmYVJNwJj7mhv3K5b73/KfqSdCWwtocH8ZjIOPWdpgp5l1YOAh7TpCpMywRQLiibgRNFevzNABIZrUK8H6ZK/KdVQtnO2T+58T2knxhptmKc95fD8sWFFGTMFQDHIzJYRIa4bTAimdUrdksCeMs1Vtc6sRaMUQ6A3Rq/yV9k2GA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(366004)(396003)(136003)(376002)(39860400002)(86362001)(6486002)(5660300002)(52116002)(9686003)(4326008)(186003)(26005)(66946007)(478600001)(66556008)(33716001)(44832011)(66476007)(2906002)(83380400001)(16576012)(8676002)(6916009)(316002)(7416002)(956004)(8936002)(103116003)(16526019);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 tHfJn3VdOR7bCHfdxmmGuhkL0Jw7coLcru/DLocn59UEQlQ6EuCwDuWzlO++IFFBcHds4uYpjNfSHZvaw7UPZ0fd9j8kCUTeDgHoodU3tFCdCFujqnwYmtENpRygpmHNWkdMweyQfo3+V3cQfxUjELfkPJW+0J6/WsBMqenxeccrfcD2Z/R5D8HB19E6Twcvi1MZG+TPHL9uoxSSLdv5SCobAZ5+08Noquvr0+ekpf+Ii1MtHavn04hH1B8wlKyI72DOMD2UGQk9g3iZGfN5Sx24EOst6DPF8rcVZuIihU6YYJJR5I+ApM+buLzZVBCvN0ChIH02FZxszmNAyRKayRVVybAHRZGpWCDdZ6HAIzJ0UP+bi7rqInOC5alt04O0HeFhbusprdjNgMOo8s5N+AFOJSbg0Lg9+gEn/ntGWE2HywX/UVcc2+jc/0noilmfOlbR0i4fFy9djT2jX6mv7eYNDX5v2CDWcT7kJoD9YLBqfOM0CUiZATws+tF3wFIVhckRQZZL7+m/WeOWOnlxg0TbF2l0NrcHTFV5VXF/3osDM7J5jVc0iyCnM3w5K1oHQWpV9hD1u1Wbct4/iSuNlewvyL3M/Q7EMyVEMhVn3wlZwlu+795ea6wofJsYaYMR6WKYBOlNVa7zOyIYQnt36w==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3445ed42-68a7-40b4-b20d-08d886a1d769
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Nov 2020 00:28:13.8817
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 h85AgRN2oJcKEGip5eSawAQkWcSnG/ugx6BkmgUxeW88/yJzeE76E4YiNa1Fl6i4
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2797
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SEV guests fail to boot on systems that support the PCID feature.

The problem is observed with SMM enabled OVMF build. The guest
crashes with the following messages on the console while loading.

----------------------------------------------------------------------
[    0.264224] tsc: Marking TSC unstable due to TSCs unsynchronized
[    0.264946] Calibrating delay loop (skipped) preset value.. 3194.00
                                                 BogoMIPS (lpj=1597000)
[    0.265946] pid_max: default: 65536 minimum: 512
KVM internal error. Suberror: 1
emulation failure
EAX=00000000 EBX=00000000 ECX=00000000 EDX=00000000
ESI=00000000 EDI=7ffac000 EBP=00000000 ESP=7ffa1ff8
EIP=7ffb4280 EFL=00000002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
CS =0000 00000000 00000fff 00009b00 DPL=0 CS16 [-RA]
SS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
DS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
FS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
GS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
LDT=0000 00000000 00000000 00000000
TR =0040 00003000 00004087 00008b00 DPL=0 TSS64-busy
GDT=     fffffe0000001000 0000007f
IDT=     fffffe0000000000 00000fff
CR0=80050033 CR2=ffff88817ffff000 CR3=0008000107e12000 CR4=000606b0
DR0=0000000000000000 DR1=0000000000000000 DR2=0000000000000000
DR3=0000000000000000 DR6=00000000ffff0ff0 DR7=0000000000000400
EFER=0000000000000d01
----------------------------------------------------------------------

The issue is root caused to the way kvm tries to validate the cr3
address in kvm_set_cr3(). The cr3 address in SEV guests have the encryption
bit set. KVM fails because the reserved bit check fails on this address.

This series fixes the problem by introducing a new kvm_x86_ops callback
function to detect the encryption bit and mask it during the check.
---

Babu Moger (2):
      KVM: x86: Introduce mask_cr3_rsvd_bits to mask memory encryption bit
      KVM:SVM: Mask SEV encryption bit from CR3 reserved bits


 arch/x86/include/asm/kvm_host.h |    2 ++
 arch/x86/kvm/svm/svm.c          |   15 +++++++++++++++
 arch/x86/kvm/svm/svm.h          |    3 +++
 arch/x86/kvm/vmx/vmx.c          |    6 ++++++
 arch/x86/kvm/x86.c              |    3 ++-
 5 files changed, 28 insertions(+), 1 deletion(-)

--
```
#### [RFC, v1 0/3] msi support for platform devices
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
From patchwork Thu Nov 12 17:58:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11900903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,SPF_HELO_NONE,SPF_PASS,
	T_TVD_MIME_NO_HEADERS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5228EC55ABD
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 17:59:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC30521D91
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 17:59:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=broadcom.com header.i=@broadcom.com
 header.b="NhhC82fJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726202AbgKLR7G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 12:59:06 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35088 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726056AbgKLR7G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 12:59:06 -0500
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 432FEC0613D4
        for <kvm@vger.kernel.org>; Thu, 12 Nov 2020 09:59:06 -0800 (PST)
Received: by mail-pf1-x441.google.com with SMTP id 10so5256519pfp.5
        for <kvm@vger.kernel.org>; Thu, 12 Nov 2020 09:59:06 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=ajmDYabH23aBLCR+xrziDwXJacB4LEpUdXmD+mNaoo8=;
        b=NhhC82fJbKFZ/yayxgDIrcJ5afJoa9p7QnmlAtl/JapM89GKN3jAezhs2/IyQRbwz3
         Fp7H7JFn6sAqnJr0a6SHo/FCYWv3PvoKbbl7aMdoXVlvfm0kc2Rgot7Cnsj/uoUPg/rX
         DHKOoZjVx9/2kd4roEg1G8mn/5cuH3GWh/LD0=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=ajmDYabH23aBLCR+xrziDwXJacB4LEpUdXmD+mNaoo8=;
        b=YcRZ58urM/1fTm/qlQIQwGbhSfJLIrBnhwFWOCsQzZw+n96BYRjr/sJNI9jeSA3p/s
         v5c7RWbWpZBl61+kBpIw2nF8wb4cRvwaeT2zAwv87GSXmkBtV/6F6f6i7wJzA7ki7bZD
         15RbZyk1dUW2p4RWjvKuqDzzha4uFmr6w99ELoHhGT3RU/R6g6IaMavT0grixe2EzTpE
         EgJg7k9n4yrO39dxt4syvxQsLocItBICOsV16Oa3Z0kYtbGMVxSvfUJu/MdufFqxkMBD
         q2qKfCn9crlhltWU6tB1DMw7kizO5h/egYF1KMFrC9YJ55I9pIaR7gqaR1p8gVPejuYu
         62lw==
X-Gm-Message-State: AOAM532lVLygCrqN/chFNJruwDOFNIwlGVwz3lCxYeSVxffJDNizW4wU
        KVEkZ3HZGj7O3AHtfboxKp6aiw==
X-Google-Smtp-Source: 
 ABdhPJzMcfsWlwV+Yl+Ju6UrSqt7j5dSMFXgh+3u4AQBf/P0A0F+06wx72FnY/z55UZ2PBMWLBWJyA==
X-Received: by 2002:a65:4483:: with SMTP id l3mr575455pgq.96.1605203945461;
        Thu, 12 Nov 2020 09:59:05 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 r6sm7237894pjd.39.2020.11.12.09.59.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 12 Nov 2020 09:59:04 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC, v1 0/3] msi support for platform devices
Date: Thu, 12 Nov 2020 23:28:49 +0530
Message-Id: <20201112175852.21572-1-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201105060257.35269-1-vikas.gupta@broadcom.com>
References: <20201105060257.35269-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC adds support for MSI for platform devices.
a) MSI(s) is/are added in addition to the normal interrupts.
b) The vendor specific MSI configuration can be done using
   callbacks which is implemented as msi module.
c) Adds a msi handling module for the Broadcom platform devices.

Changes from:
-------------
 v0 to v1:
   i)  Removed MSI device flag VFIO_DEVICE_FLAGS_MSI.
   ii) Add MSI(s) at the end of the irq list of platform IRQs.
       MSI(s) with first entry of MSI block has count and flag
       information.
       IRQ list: Allocation for IRQs + MSIs are allocated as below
       Example: if there are 'n' IRQs and 'k' MSIs
       -------------------------------------------------------
       |IRQ-0|IRQ-1|....|IRQ-n|MSI-0|MSI-1|MSI-2|......|MSI-k|
       -------------------------------------------------------
       MSI-0 will have count=k set and flags set accordingly.

Vikas Gupta (3):
  vfio/platform: add support for msi
  vfio/platform: change cleanup order
  vfio/platform: add Broadcom msi module

 drivers/vfio/platform/Kconfig                 |   1 +
 drivers/vfio/platform/Makefile                |   1 +
 drivers/vfio/platform/msi/Kconfig             |   9 +
 drivers/vfio/platform/msi/Makefile            |   2 +
 .../vfio/platform/msi/vfio_platform_bcmplt.c  |  74 ++++++
 drivers/vfio/platform/vfio_platform_common.c  |  86 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 238 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  23 ++
 8 files changed, 419 insertions(+), 15 deletions(-)
 create mode 100644 drivers/vfio/platform/msi/Kconfig
 create mode 100644 drivers/vfio/platform/msi/Makefile
 create mode 100644 drivers/vfio/platform/msi/vfio_platform_bcmplt.c
```
#### [PATCH v2 0/2] Fix AMD SEV guest boot issue with PCID feature
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Thu Nov 12 22:17:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11901893
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23396C56202
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:18:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A9DA32078D
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:18:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="B598HUTk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727446AbgKLWRz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 17:17:55 -0500
Received: from mail-bn8nam11on2060.outbound.protection.outlook.com
 ([40.107.236.60]:55520
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725962AbgKLWRy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 17:17:54 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=UxvBLyDlO0kFvN9PkqjK/KVVBqfprGBRC/sosYzZUCnjhI8OBx3XWFDhrmNb40ZjY0aNMFbl0MQzhMuKbUCkWH51TJfgPTZK+eeUm2oVaQt2laZSfLZy7D6QK7kZ08NHl3oybe9TvEh8kfvpN3uvvV0PA41Xq8J/GtAGOJ7kxFmlWREEQJ8HmQQ8+Dh2qq2wIqpSif71L5zeTdALVY7Rgl7doDJxeQ0z/mTpMRgUZrg2Mw5uG17OCTjPiMoOXZ5xzszHMrfhbZdz++YDoLoyWr74vb53aMNgQ0ljobdlQU+/aEwb9U10B1EsICrwFe53jyhmwJSdXAC+A2JX77yBQA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=q08ehynH9fh2+DeVR+YlEXnDXlLHHA3Nw/aPhtf+Evo=;
 b=MWnU289D3dDhC6TQm31AieRDVFf1/pc+99ToBzYgFrBowLHenMe1wlBtKZkyNGlj6HXOUM+QBqj3I/Im5SOFQXyU/bLA0FWK0FJ3SGblrN5cukGjZnYeFqHn13B2BxtxTfOx7aYyC/4V7ygoWWrRUzoi4t1XaMMVbinEBp/lHZxZyivcidNzYDubTShFXDxow0ss4dXCD7ufaOEmXVdRk2IN6dox4igIBPWNekwyUtjR8PWwP+mLYB82Xbcvz3PzmKfiidtSj/dC/J7axV80TyyCMAK+UrZPORLz6cLEdn28lpRY5QbZ2oBvkyf3CZDmvdSp6SWS7++zLKIyOmGe8g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=q08ehynH9fh2+DeVR+YlEXnDXlLHHA3Nw/aPhtf+Evo=;
 b=B598HUTkmQypG0O0k8nCJdiR+5fbdxt9FP0D+JMrT+UOQ6YQUo96zeRgJFrYFr6eVnj2yK+nUFFvOXU5f6Vqz1pOtBB/ATDPb7PesYzT96UcB7MAex5St7+WdP3YtmqdzjCGwCE14yuyDin+Vk+owPtRqWIwkBK+U4cxVf7cuVY=
Authentication-Results: google.com; dkim=none (message not signed)
 header.d=none;google.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4445.namprd12.prod.outlook.com (2603:10b6:806:95::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Thu, 12 Nov
 2020 22:17:51 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3541.026; Thu, 12 Nov 2020
 22:17:51 +0000
Subject: [PATCH v2 0/2] Fix AMD SEV guest boot issue with PCID feature
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: junaids@google.com, wanpengli@tencent.com, kvm@vger.kernel.org,
        joro@8bytes.org, x86@kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de, vkuznets@redhat.com,
        jmattson@google.com
Date: Thu, 12 Nov 2020 16:17:50 -0600
Message-ID: <160521930597.32054.4906933314022910996.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN1PR12CA0094.namprd12.prod.outlook.com
 (2603:10b6:802:21::29) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN1PR12CA0094.namprd12.prod.outlook.com (2603:10b6:802:21::29) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Thu, 12 Nov 2020 22:17:50 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0a0d79b8-6e0b-4279-ebc1-08d88758cb3a
X-MS-TrafficTypeDiagnostic: SA0PR12MB4445:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4445FEA0FA62793A705411BC95E70@SA0PR12MB4445.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 pNxP1Lp2U+Jw5sMh9a1IRVw7Ejc8O3m07mKNxC0AdfMhCJ6AB2TIkhOAVCK5MWOnjpr9kTWp27iAGG5cgpPjIrpGi3WX5alnGDRqo8iaaCMfEfygYQmklDkFVG/ZmG/mUV6P8/XxVGJniKXT4sFDf7X4sDT964rdcvieTevrEWYDc5eDm66e35UOVTOa/LAhXE6iO5H6A3JscGWkUC+pYCL+RfBUVNzl4NYsBtBuEb8B78UMHa/NK5XSzYAff8BL4Cd5+91ngc8hFFfwpw3nICBQTNUmxAdQkCUyB2QwQZOfV+N3w6shMrlgzMtcAAmygYeDnkueNN+DwMVmjrjNcuc0kd0ZL8lFdQvS5fkAz9yl3CqsAQSMt3CH9ameHSeILCCcstA+QxKrNOqHj99UsQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(366004)(346002)(376002)(396003)(136003)(39860400002)(52116002)(33716001)(16576012)(966005)(9686003)(16526019)(8676002)(86362001)(6486002)(103116003)(478600001)(956004)(6916009)(2906002)(66476007)(8936002)(66556008)(316002)(7416002)(26005)(4326008)(83380400001)(44832011)(5660300002)(66946007)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 4ut1MWxvfqvLBtr8Y8ZZJSkz3gzpifKLXk172cLiQiSpVVhnRl6zAFGsx85Ff7YST9E8tkuSprHaovyH5u9Y/44FgAkDSVxalFaoKb/xY8hYOAOA46Gbv1+IuM/HcxRnRGDVc8GWU72JYxuhZBzTgWuGm2gJn4ibJHTeOr5T5LvJ+z1i26huj274pWNC8vzC5R8XpZXtb3wPd4HVdJckOugSbvvc+d2B5rEinq66+bMzV+cVDpsNf/P/vwlhJwP+S6o9h0Q8s5hC4bX0+EHjuH1A1rhG2ABDN5KNjt7Zk3JsENnTckLvEcFV+/Xyd/JO/VwpxRvGv43KAT5shbCqkCVxf0MtYNGbD2j+yS5prSlrCMuzk9sHxehdZvYkbeiKsH9gInwYiMv2cidSugmyT0DN9e5jlMnDh2v6rlzi3WWio4DQtA0Sf7lYsySVOj/QL7yxIHLtraFygUD/AYPv81ARjfKyPBHNKM5Xed4uPJC8fCPCMBEyPlZVR23iQEDd/jpBql9LYsoRP+/Y7Dp9iZ04+sJoGaMg/b9mIjNwmL/Zdo/4PKx3i5quLj6Qj69o1IjkRE338ypgdwFxM3HPIiecx/Kn7iwP6bkKajl04Ik4AP5Esng0POFzZ2lnFRbr5CTwjiybM9JqBWjVgs49+w==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0a0d79b8-6e0b-4279-ebc1-08d88758cb3a
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Nov 2020 22:17:51.1252
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 R+LPKirxrnNAiHsxC2HlvSvS5miguFW8RKpwrFpwXZN+94IkjjKQqW3la9O60ywg
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4445
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SEV guests fail to boot on systems that support the PCID feature.

The problem is observed with SMM enabled OVMF bios is used. The guest
crashes with the following messages on the console while loading.

----------------------------------------------------------------------
[    0.264224] tsc: Marking TSC unstable due to TSCs unsynchronized
[    0.264946] Calibrating delay loop (skipped) preset value.. 3194.00
                                                 BogoMIPS (lpj=1597000)
[    0.265946] pid_max: default: 65536 minimum: 512
KVM internal error. Suberror: 1
emulation failure
EAX=00000000 EBX=00000000 ECX=00000000 EDX=00000000
ESI=00000000 EDI=7ffac000 EBP=00000000 ESP=7ffa1ff8
EIP=7ffb4280 EFL=00000002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
CS =0000 00000000 00000fff 00009b00 DPL=0 CS16 [-RA]
SS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
DS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
FS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
GS =0020 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
LDT=0000 00000000 00000000 00000000
TR =0040 00003000 00004087 00008b00 DPL=0 TSS64-busy
GDT=     fffffe0000001000 0000007f
IDT=     fffffe0000000000 00000fff
CR0=80050033 CR2=ffff88817ffff000 CR3=0008000107e12000 CR4=000606b0
DR0=0000000000000000 DR1=0000000000000000 DR2=0000000000000000
DR3=0000000000000000 DR6=00000000ffff0ff0 DR7=0000000000000400
EFER=0000000000000d01
----------------------------------------------------------------------

The issue is root caused to the way kvm tries to validate the cr3
address in kvm_set_cr3(). The cr3 address in SEV guests have the encryption
bit set. KVM fails because the reserved bit check fails on this address.

This series fixes the problem by introducing a new field in kvm_vcpu_arch
structure. The new field cr3_lm_rsvd_bits is initialized to 
rsvd_bits(cpuid_maxphyaddr(vcpu), 63) in kvm_vcpu_after_set_cpuid
and clear the any reserved bit specific to vendor in
kvm_x86_ops.vcpu_after_set_cpuid
---
v2: Changed the code suggested by Paolo. Added a new field in kvm_vcpu_arch
    to hold the reserved bits in cr3_lm_rsvd_bits.

v1:
https://lore.kernel.org/lkml/160514082171.31583.9995411273370528911.stgit@bmoger-ubuntu/

Babu Moger (2):
      KVM: x86: Introduce cr3_lm_rsvd_bits in kvm_vcpu_arch
      KVM:SVM: Update cr3_lm_rsvd_bits for AMD SEV guests


 arch/x86/include/asm/kvm_host.h |    1 +
 arch/x86/kvm/cpuid.c            |    2 ++
 arch/x86/kvm/svm/svm.c          |   11 +++++++++++
 arch/x86/kvm/x86.c              |    2 +-
 4 files changed, 15 insertions(+), 1 deletion(-)

--
```
