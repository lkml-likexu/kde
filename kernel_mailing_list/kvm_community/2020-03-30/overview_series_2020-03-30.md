#### [PATCH v5 02/14] KVM: SVM: Add KVM_SEND_UPDATE_DATA command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11464407
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0EBE6912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 01:39:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD25220780
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 01:39:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="BOnJO6Uv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728799AbgC3BjH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Mar 2020 21:39:07 -0400
Received: from mail-eopbgr750053.outbound.protection.outlook.com
 ([40.107.75.53]:39901
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727955AbgC3BjH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 29 Mar 2020 21:39:07 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EpwaBI9hF7WwFBBHEB/iMiPQnkurgp690LzNFN4t5e3tKIooIgGW22hOzDnolkqc+F2wJdvXV2gXG7En1sUKMOp1DGaDYOkuArxR6FOP4Ag0bsksDomeyVHgbhS6fDqGeQDgJniWAuzh+gyA1MIIKH6wHWw46yooJ1U9HO8oqyf7W2yF8x5miyiSKKN1LJfN8kRnsTukTbkuoEu4M89eLjA3KH+nNRRogVDxRIS42+mcSbdfTehG+ZOvKcJmJBvYGXhI0iKn9xxeaN/8vpUAP644Bb8bnqbUdcMmajEfn5kgvm224bCjodopQCe3ag92Uq4bUEQgqV7TrBnml+42Pw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Px3DaSAofM8+jNq45/Y/o5vN7ooFf4B+voinsjKnm1c=;
 b=cHPKREXuO1bq47Fy7DituRB2m/mOqgA6Cr+vJxcmwwRyhFL8gsrm7nGJMhU/oHY/2ZQBNCU7eK99zHsnOes891W+kqQCAiWvMP2mVjAQfZh3AjlChw/CBR7A9RTPKy3ZID0jSa2wJMR2hE6+6QjOcGXZsxzOrOV7Fp4WNkTQCGpBZyDDD2Lvt6l3edhpiEhyJnN/yM5rFasz7zegd6DjUNZHhP9CObtRgtvFnEWWQRgKwPdjoqewz+U1/ggeGSQotLLewZ3HW62/PYchbbYU7+MgRqL9bneG/7w7YaVXQRERPttFLfZa72UBzLjLOEptN8J5QfBQfXPa0J8kp7+duA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Px3DaSAofM8+jNq45/Y/o5vN7ooFf4B+voinsjKnm1c=;
 b=BOnJO6Uvsw6ZI/U3X7OKzWdTVBDTVJc3nEymHjI0lOKwbk02Ou3iQD/EdeAXTy9Ho37se4kaEMGEyhec/4BtB3WNHyktStj1RrbGTvz/ySEnFHefjByWtCRWN+iMoYEOJATBZfDQCO/VAaQ3dgLp0yI08zLUABMIYuBw9dgpTeM=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB1387.namprd12.prod.outlook.com (2603:10b6:3:6c::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2856.20; Mon, 30 Mar 2020 01:34:22 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c%12]) with mapi id 15.20.2856.019; Mon, 30 Mar 2020
 01:34:22 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        rientjes@google.com, srutherford@google.com, luto@kernel.org,
        brijesh.singh@amd.com
Subject: [PATCH v5 02/14] KVM: SVM: Add KVM_SEND_UPDATE_DATA command
Date: Mon, 30 Mar 2020 01:34:13 +0000
Message-Id: 
 <7ea65c7852543a7cd4fb904db751bed859735a84.1585531159.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1585531159.git.ashish.kalra@amd.com>
References: <cover.1585531159.git.ashish.kalra@amd.com>
X-ClientProxiedBy: DM6PR02CA0040.namprd02.prod.outlook.com
 (2603:10b6:5:177::17) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM6PR02CA0040.namprd02.prod.outlook.com (2603:10b6:5:177::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.18 via Frontend
 Transport; Mon, 30 Mar 2020 01:34:21 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f9a7f1e8-f147-4139-11b9-08d7d44a7942
X-MS-TrafficTypeDiagnostic: DM5PR12MB1387:|DM5PR12MB1387:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1387E9DE0525BFB01CE4CBAC8ECB0@DM5PR12MB1387.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-Forefront-PRVS: 0358535363
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10009020)(4636009)(39860400002)(376002)(346002)(366004)(136003)(396003)(186003)(66574012)(66556008)(6666004)(66476007)(86362001)(6916009)(66946007)(316002)(4326008)(7696005)(52116002)(5660300002)(6486002)(16526019)(26005)(36756003)(478600001)(7416002)(81166006)(81156014)(8936002)(2616005)(8676002)(2906002)(956004)(136400200001);DIR:OUT;SFP:1101;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 PTKITN50Ng8u8mxCA56fkAHbGOS8Mpz4YZkVEvrZNVmxhEYARMXpe4Bfa5dN9hOW6g9Gz004KDnIbSJYtvvtaaCctW8WBse/kaQGTSTdHIFDTFHimryIBtgBc6YGkpjBqB0geGiEgLRoUzUHxTsCxngDs2H8Vv9U7yyzG96uNjHi53MWaNfywNI8yDsXDV9vUvU5c1Z367mE0Q5uBjoblD8eyQwAkoC9fL0a5m2JG9qhvt/Pb13wjO8T0s0ACwm9BJqpPJLUWonDcguHfhaPAyQrigJm2sLwMjLdwHXUyfhHhIxfzle5p1H9rjEZfp4ZVu9IQyN3ZXB90rUxiME2XRkSdResarnuhwNUMd+A4JOTbbZrPrT/pL72aUdDtw6DsNNuzUfWNI/etsMLydNOnyw1kyGnPt2b2BPOjalXTO7DQz90Kl5rHose4jvutfd88SbJCp5wqepGATHgBx2K188BBAvwBOSWz2iG5xavxtT5st6QomdvbT4JQg1Mu6bY
X-MS-Exchange-AntiSpam-MessageData: 
 /f49lnhE013ruoHZbd5SrUwDHt0+OLbNVh81n+z5a213PAhTb4CWmU+Rvq8vUc4aYkjvoE4gJg1Lbk2KcZ6rMztYAtpd0X8ZhY9A2+SjlCV/NspIgaAULOGC/NZnUxiJ62nxg2IdoHcLGVDv3VnP9Q==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f9a7f1e8-f147-4139-11b9-08d7d44a7942
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Mar 2020 01:34:22.5145
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 uCwCuPQ7HG1anYzlVa3uo7MDsJFnrGuwSo5rlvfQrxPWGE3mV2U1533nVXlGHv8nKYJ59I7D37ZKk0EAm85fLA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1387
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <Brijesh.Singh@amd.com>

The command is used for encrypting the guest memory region using the encryption
context created with KVM_SEV_SEND_START.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by : Steve Rutherford <srutherford@google.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  24 ++++
 arch/x86/kvm/svm.c                            | 136 +++++++++++++++++-
 include/uapi/linux/kvm.h                      |   9 ++
 3 files changed, 165 insertions(+), 4 deletions(-)

```
#### [PATCH v6 01/14] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11464667
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1BC417EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 06:20:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D08BF2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 06:20:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="nFV/Mz1j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729021AbgC3GUT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 02:20:19 -0400
Received: from mail-bn8nam12on2071.outbound.protection.outlook.com
 ([40.107.237.71]:6183
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728065AbgC3GUS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Mar 2020 02:20:18 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=JEX4WXO/KzVDIAYWfXgqJGXxR7OKI5LGpVg9p1duYe9FxehfzuNWmsdfMJp3hW4nbNL3P2Sv4Nw2Zvgu/u6jymiLSLBDg4DNajiF4es+si0ETI1r9guyv71gs6OcxdlVg718lgT9gLsmq2ypCdNNUY4GI2eA5qKsnJITFAiPK7KQ0DEIn7lAVsjVyzIWiKXjPz3ak3p5zQwy6+t2q2xlrSNR7e8IrVHzv7iIYUwj+ZZMlzrZEUgkiWuYjIDUIlLe4SuJ5CERTfYoOAr27ptfBifQrJOT120SKMwHwg2RykoGtAZ+X9emn/eGdeH99fs8WEP20oiw+qiNSUNWPhtgow==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mXs6oCGGb69ZQb4o3/N3Tk0FaE/hDI9ZPuNqhiXt2NE=;
 b=PwFLGzMdx+4vGJe0JhZMS5SezljjkPQo35pmNVNErTDdzxRnJ0pqu+xqT+LPet5aO0muu8x8k4cD8n3pS3ZylFqEmyesPsPzXaqxdWA4oMX70cjTvqLavZXR0Ye92GZENgYwND9NoEwPOerFZIU4yZv3xr0ANRAp4Sf6ydbFgFOwWSDoDgOEb8B89nNGbhCb/+hGhcQ21srsNj4/Bp6naHNShRFmLmyaaVy3w2Q6Es+fFGcAmDW+uLuqG63NoOEhLALlK8E+dM7wU9GuhMnWGcvxW/IMT9ABGebqCFfVD2lh+EuYQdsfn6Ppp+1cos7Sh1RBeAazJd6umrT0Y0kVYg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mXs6oCGGb69ZQb4o3/N3Tk0FaE/hDI9ZPuNqhiXt2NE=;
 b=nFV/Mz1jt6XbdY8Oe5FspWe+TvuP+sY/3JK63QcvSnTuGvxh06K5aHbyZBsLiTQ6mv7tUFxpC81OhcUpKO1k0Jk2u50kP3iYIixzjlRMVD8+EAiCU8vkmXDYVd9t2NfTHsoDBG2B6y7OMiB3jswvKMrunyHSQ3zfBbsp8U1cuLw=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB1692.namprd12.prod.outlook.com (2603:10b6:4:5::14) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2856.18; Mon, 30 Mar 2020 06:20:14 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c%12]) with mapi id 15.20.2856.019; Mon, 30 Mar 2020
 06:20:14 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        rientjes@google.com, srutherford@google.com, luto@kernel.org,
        brijesh.singh@amd.com
Subject: [PATCH v6 01/14] KVM: SVM: Add KVM_SEV SEND_START command
Date: Mon, 30 Mar 2020 06:19:59 +0000
Message-Id: 
 <3f90333959fd49bed184d45a761cc338424bf614.1585548051.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1585548051.git.ashish.kalra@amd.com>
References: <cover.1585548051.git.ashish.kalra@amd.com>
X-ClientProxiedBy: SN4PR0501CA0034.namprd05.prod.outlook.com
 (2603:10b6:803:40::47) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN4PR0501CA0034.namprd05.prod.outlook.com (2603:10b6:803:40::47) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2878.9 via Frontend
 Transport; Mon, 30 Mar 2020 06:20:13 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 819302f8-e71a-4da0-47ed-08d7d47268c9
X-MS-TrafficTypeDiagnostic: DM5PR12MB1692:|DM5PR12MB1692:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB16920EEA84B6E7D1CF2504F58ECB0@DM5PR12MB1692.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-Forefront-PRVS: 0358535363
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10009020)(4636009)(396003)(376002)(39860400002)(366004)(136003)(346002)(16526019)(186003)(26005)(5660300002)(6666004)(8936002)(6486002)(4326008)(2906002)(36756003)(7416002)(316002)(66946007)(66476007)(86362001)(66556008)(66574012)(8676002)(7696005)(81156014)(6916009)(2616005)(956004)(81166006)(52116002)(478600001)(136400200001);DIR:OUT;SFP:1101;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 6MXw0583YEaPcQQOGPElV6aJ/hORD1Mzy/ENI1Awv7txbvhrXQ8RuZmOuxZ72HExG0S0H2Z3Lhc9NKvpCkqYzyg2kTZhSojGoxyHvO5H2iTpyjvWP+MKRwS+palOb6mTMJQPZAigFayXhF//79Sq+N0OzFpn3hMsti0BHoS5pIcGAt6b729akQh4kov3P9l3H+4QC3OM/LuTlLBmTUT2cEYpBHF8SAKDJtBRkpKSoNxKBipdISxdcTpNzu3p/WS+UQ1juEtNHyKv/barTvsrsEMEDG+BN3MQwFYh/7349rCAEkcmIeB08N2J14cUh9j0nzWnViNkvIrvR8WOSd4neT1T5ZZ2t5xHIV9NmgEu5PB/ELgTaGfsURbJgkv4ifXWztjxUHVP+Vfq5cl8iG7m1eimDkuIUjfiQmbZnBadaQEH17eAwqXN7xqg3fnSmFjFPRsWXA7Hno4geVPMNgxGjBHhsCR0XYP1ahFJwNlmzCoUj8aSUgLL7ZMFhnjvwQK+
X-MS-Exchange-AntiSpam-MessageData: 
 Va6fMAh+M9HEXmrgJpHo4a2AG8p09lxunMkq0W0VoXf81XOgO9DSkgaNX3+QbWGK9xRbMJ3tZ3vyo9wRFGUTlq6EJxcYV+ctsh9r1sZ9HJU9Yu1vBAIVMhmeUdTyC64neMXaNZjt8C6mf/OflxOfAQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 819302f8-e71a-4da0-47ed-08d7d47268c9
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Mar 2020 06:20:14.7145
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 H0030qnK5iXN5P3kJ7v46bpt3KOxTQyf1d/s5pUKbhCQoQYVCzr156dT07DmMwmCg0OzOkizTYERQ8fHD5LZjg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1692
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <Brijesh.Singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  27 ++++
 arch/x86/kvm/svm.c                            | 128 ++++++++++++++++++
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  12 ++
 4 files changed, 171 insertions(+), 4 deletions(-)

```
#### [GIT PULL 1/1] s390/gmap: return proper error code on ksm unsharing
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11465425
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67EB21392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 12:19:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 50A8620714
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 12:19:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730015AbgC3MTp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 08:19:45 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17282 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729981AbgC3MTp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 08:19:45 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02UC3gHl111450
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 08:19:44 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30233787vy-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 08:19:43 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 30 Mar 2020 13:19:29 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 30 Mar 2020 13:19:26 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02UCJaL850659582
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Mar 2020 12:19:36 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E44805205A;
        Mon, 30 Mar 2020 12:19:35 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id CFD8B52051;
        Mon, 30 Mar 2020 12:19:35 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 97D7BE024B; Mon, 30 Mar 2020 14:19:35 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Marc Hartmayer <mhartmay@linux.ibm.com>
Subject: [GIT PULL 1/1] s390/gmap: return proper error code on ksm unsharing
Date: Mon, 30 Mar 2020 14:19:34 +0200
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200330121934.28143-1-borntraeger@de.ibm.com>
References: <20200330121934.28143-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20033012-0016-0000-0000-000002FAF3C7
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033012-0017-0000-0000-0000335EAD14
Message-Id: <20200330121934.28143-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-30_01:2020-03-27,2020-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 suspectscore=0
 impostorscore=0 mlxscore=0 malwarescore=0 clxscore=1015 adultscore=0
 bulkscore=0 mlxlogscore=847 priorityscore=1501 phishscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003300115
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a signal is pending we might return -ENOMEM instead of -EINTR.
We should propagate the proper error during KSM unsharing.
unmerge_ksm_pages returns -ERESTARTSYS on signal_pending. This gets
translated by entry.S to -EINTR. It is important to get this error
code so that userspace can retry.

To make this clearer we also add -EINTR to the documentation of the
PV_ENABLE call, which calls unmerge_ksm_pages.

Fixes: 3ac8e38015d4 ("s390/mm: disable KSM for storage key enabled pages")
Reviewed-by: Janosch Frank <frankja@linux.vnet.ibm.com>
Reported-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Tested-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 Documentation/virt/kvm/api.rst | 6 ++++++
 arch/s390/mm/gmap.c            | 9 +++++----
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH v2 01/22] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11464517
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 906581667
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 04:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6CF7A20780
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 04:19:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726830AbgC3ETQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 00:19:16 -0400
Received: from mga04.intel.com ([192.55.52.120]:46067 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726085AbgC3ETQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Mar 2020 00:19:16 -0400
IronPort-SDR: 
 iEH4jZMCOPJdFHJ4bNtuR8RsMYY0yddyH+wr+ZuyZSOrW2nvVn9kI+s1yCq/CbbRegEDjGqqwt
 aezqftYUMXmw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Mar 2020 21:19:15 -0700
IronPort-SDR: 
 iZiJHfqz2miaNSap2JGHi9aVy40ziL2e/lZmEq/qUR4zcoSWJ1+HD4cjyCDGZk635XwSM9EQl2
 r7dheeCbMp3A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,322,1580803200";
   d="scan'208";a="327632011"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga001.jf.intel.com with ESMTP; 29 Mar 2020 21:19:15 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: eric.auger@redhat.com, pbonzini@redhat.com, mst@redhat.com,
        david@gibson.dropbear.id.au, kevin.tian@intel.com,
        yi.l.liu@intel.com, jun.j.tian@intel.com, yi.y.sun@intel.com,
        kvm@vger.kernel.org, hao.wu@intel.com, jean-philippe@linaro.org,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH v2 01/22] scripts/update-linux-headers: Import iommu.h
Date: Sun, 29 Mar 2020 21:24:40 -0700
Message-Id: <1585542301-84087-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1585542301-84087-1-git-send-email-yi.l.liu@intel.com>
References: <1585542301-84087-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v17 Kernel 1/7] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11466111
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0491692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 17:24:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C331420776
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 17:24:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="RKVOJIxZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728985AbgC3RYU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 13:24:20 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:8294 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728481AbgC3RYT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Mar 2020 13:24:19 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e822b350000>; Mon, 30 Mar 2020 10:24:05 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 30 Mar 2020 10:24:18 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 30 Mar 2020 10:24:18 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 30 Mar
 2020 17:24:18 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 30 Mar 2020 17:24:10 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v17 Kernel 1/7] vfio: UAPI for migration interface for device
 state
Date: Mon, 30 Mar 2020 22:20:38 +0530
Message-ID: <1585587044-2408-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1585587044-2408-1-git-send-email-kwankhede@nvidia.com>
References: <1585587044-2408-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1585589045; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=RKVOJIxZStD/QfvLMeWvFg5J735yuaJ4AV/HmIKtj4lg+PO5FmSWKEb1Ktk3cMHVJ
         A7gt4kSa4Mt08fPfVRVGbuNDDYCMf+xc7GURwC/ECUQfBbaGeVFPcOiHxWfkUZX5Zb
         A0NfBLOyJXBwLxulERBdDgFgwjbtKgMVae5H0oqA5Y/NWYyRgnW3HEz2A0XcaBvckN
         N0oA8KNck7jcyXBldqYarLLT88SdhKx13UD60mhvz43Bt6Rz+lc1dfpHNG2x8ohv8B
         za6REsOtEelBfv8JVMFsHv/xAM/tOEvyPfJcyOGIAHexLK146GuiH3tGeRJtaqI+he
         uq2fG62HxYwXg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: Add stsi 3.2.2 tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11465427
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E74C41392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 12:20:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CF1E620774
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 12:20:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730024AbgC3MUy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 08:20:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4496 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729848AbgC3MUx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 08:20:53 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02UC4Zak024738
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 08:20:53 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 302344fs1f-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 08:20:52 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 30 Mar 2020 13:20:34 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 30 Mar 2020 13:20:32 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02UCKibS60293138
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Mar 2020 12:20:44 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6A53AE04D;
        Mon, 30 Mar 2020 12:20:44 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A1091AE053;
        Mon, 30 Mar 2020 12:20:43 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.43.209])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 30 Mar 2020 12:20:43 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com,
        borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH] s390x: Add stsi 3.2.2 tests
Date: Mon, 30 Mar 2020 08:20:35 -0400
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20033012-0020-0000-0000-000003BE3BDA
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033012-0021-0000-0000-00002216D768
Message-Id: <20200330122035.19607-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-30_01:2020-03-27,2020-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 bulkscore=0
 impostorscore=0 lowpriorityscore=0 suspectscore=1 mlxlogscore=999
 adultscore=0 malwarescore=0 mlxscore=0 priorityscore=1501 spamscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003300111
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Subcode 3.2.2 is handled by KVM/QEMU and should therefore be tested
a bit more thorough.

In this test we set a custom name and uuid through the QEMU command
line. Both parameters will be passed to the guest on a stsi subcode
3.2.2 call and will then be checked.

We also compare the total and configured cpu numbers against the smp
reported numbers.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/stsi.c        | 62 +++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |  1 +
 2 files changed, 63 insertions(+)

```
#### [kvm-unit-tests PATCH v2] s390x: Add stsi 3.2.2 tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11465821
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BB881392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 15:34:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD3BC2072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 15:34:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729192AbgC3PeM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 11:34:12 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:4414 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728441AbgC3PeM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 11:34:12 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02UFWp6c072216
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 11:34:11 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 303jr19f5s-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 30 Mar 2020 11:34:11 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 30 Mar 2020 16:34:03 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 30 Mar 2020 16:34:00 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02UFY5VI48693442
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Mar 2020 15:34:05 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7250611C052;
        Mon, 30 Mar 2020 15:34:05 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2DFE711C04A;
        Mon, 30 Mar 2020 15:34:04 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.43.209])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 30 Mar 2020 15:34:03 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com,
        borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v2] s390x: Add stsi 3.2.2 tests
Date: Mon, 30 Mar 2020 11:33:59 -0400
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20033015-0012-0000-0000-0000039B05B5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033015-0013-0000-0000-000021D80E27
Message-Id: <20200330153359.2386-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-03-30_06:2020-03-30,2020-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 impostorscore=0
 malwarescore=0 suspectscore=1 adultscore=0 bulkscore=0 mlxscore=0
 clxscore=1015 mlxlogscore=999 phishscore=0 lowpriorityscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003300142
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Subcode 3.2.2 is handled by KVM/QEMU and should therefore be tested
a bit more thorough.

In this test we set a custom name and uuid through the QEMU command
line. Both parameters will be passed to the guest on a stsi subcode
3.2.2 call and will then be checked.

We also compare the configured cpu numbers against the smp reported
numbers and if the reserved + configured add up to the total number
reported.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/stsi.c        | 72 +++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |  1 +
 2 files changed, 73 insertions(+)

```
#### [kvm-unit-tests 1/2] s390x/smp: fix detection of "running"
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11464951
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13F42912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 08:49:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EFC5020732
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 08:49:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729767AbgC3ItY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 04:49:24 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:47274 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728759AbgC3ItY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 04:49:24 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02U8Zitg139107;
        Mon, 30 Mar 2020 04:49:22 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 303bgdk8g8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 30 Mar 2020 04:49:22 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 02U8accv141964;
        Mon, 30 Mar 2020 04:49:22 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 303bgdk8fh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 30 Mar 2020 04:49:22 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 02U8nKcu021247;
        Mon, 30 Mar 2020 08:49:20 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma04wdc.us.ibm.com with ESMTP id 301x767d5m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 30 Mar 2020 08:49:20 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02U8nJEr43909464
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Mar 2020 08:49:19 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6712B7805E;
        Mon, 30 Mar 2020 08:49:19 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6C007805F;
        Mon, 30 Mar 2020 08:49:18 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 30 Mar 2020 08:49:18 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Thomas Huth <thuth@redhat.com>
Subject: [kvm-unit-tests 1/2] s390x/smp: fix detection of "running"
Date: Mon, 30 Mar 2020 04:49:10 -0400
Message-Id: <20200330084911.34248-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200330084911.34248-1-borntraeger@de.ibm.com>
References: <20200330084911.34248-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-30_01:2020-03-27,2020-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 priorityscore=1501 lowpriorityscore=0 mlxlogscore=992 clxscore=1015
 impostorscore=0 spamscore=0 suspectscore=0 bulkscore=0 phishscore=0
 mlxscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2003300076
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On s390x hosts with a single CPU, the smp test case hangs (loops).
The check is our restart has finished is wrong.
Sigp sense running status checks if the CPU is currently backed by a
real CPU. This means that on single CPU hosts a sigp sense running
will never claim that a target is running. We need to check for not
being stopped instead.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.vnet.ibm.com>
---
 lib/s390x/smp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11466299
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EFA7E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 20:43:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CE14320786
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 20:43:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EK25I1nU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728979AbgC3Unu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 16:43:50 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:44032 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728471AbgC3Unt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 16:43:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585601028;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=8WcGc/uVHG7ylmz9BTpf5JgzJOmoF9uEr8u6eJ8H6Dk=;
        b=EK25I1nU+ShRY/cYSxSUsYu4Iy2aWNQMHx5h8FWev6tLZFDICBXLyB34LkW+2+86NcjoTK
        bVc1P61/0lIAgGyfXAR1tjhW94/GjI+i3dBF7oiGENquIpo59kpx7Hw5w85Atdi1XS2/W2
        tqm24OJsJUlUpikobEkGPDDeor1liJI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-378-28sXCqmINh-LnPyBKYXAsw-1; Mon, 30 Mar 2020 16:43:43 -0400
X-MC-Unique: 28sXCqmINh-LnPyBKYXAsw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C969E1922960;
        Mon, 30 Mar 2020 20:43:42 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DC74519C58;
        Mon, 30 Mar 2020 20:43:26 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
        david@redhat.com, drjones@redhat.com
Subject: [PATCH 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
Date: Mon, 30 Mar 2020 17:43:09 -0300
Message-Id: <20200330204310.21736-2-wainersm@redhat.com>
In-Reply-To: <20200330204310.21736-1-wainersm@redhat.com>
References: <20200330204310.21736-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduces the vm_get_fd() function in kvm_util which returns
the VM file descriptor.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 5 +++++
 2 files changed, 6 insertions(+)

```
#### [PATCH] selftests: kvm: Update .gitignore with missing binaries
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11466339
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EB1D015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 21:19:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C978E20733
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 21:19:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TKvjsNIw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728939AbgC3VTc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 17:19:32 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:52462 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728481AbgC3VTc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 17:19:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585603171;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=W5E8AnJX6hToQex66ypkBMbfpIseZ8s9JQtsbtKX3pI=;
        b=TKvjsNIwVhKlEs8N6hO3TioSbyBeRtRRYbZsDCsTGe7W4vYCg2ZdfMxQtxTmKYehQXJ4VO
        CIsL184vdTNx125l6otA5KAph86QO5i2nR6mPciwazFER873BTqFFEGJfYmfWUuZw8hedo
        S/p66fIBh7x9uhtMQjFRn5RsDZyOLNI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-408-XrhlEOX0O6uEhWN97qsNUg-1; Mon, 30 Mar 2020 17:19:27 -0400
X-MC-Unique: XrhlEOX0O6uEhWN97qsNUg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B572C18AB2CA;
        Mon, 30 Mar 2020 21:19:26 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9B6D419C6A;
        Mon, 30 Mar 2020 21:19:24 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, frankja@linux.ibm.com
Subject: [PATCH] selftests: kvm: Update .gitignore with missing binaries
Date: Mon, 30 Mar 2020 18:19:22 -0300
Message-Id: <20200330211922.24290-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Updated .gitignore to ignore x86_64/svm_vmcall_test and
s390x/resets test binaries.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v5 01/14] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11464381
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 59143912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 01:35:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16A712076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 01:35:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="E+Z11Fy+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728122AbgC3Be3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Mar 2020 21:34:29 -0400
Received: from mail-eopbgr750053.outbound.protection.outlook.com
 ([40.107.75.53]:39901
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727815AbgC3Be3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 29 Mar 2020 21:34:29 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EDCqW8byiYjliIVcyzQ9phsryBqdPYldwWomD1g/+Wf5V+oBqeX6gYwX5rhZS276JER+drGi6EbS5Yqz30cWpCfoFiLoUAp5ivmd9fx4nu5Kg8rvFVsm26T2xQ13FuPe8AeRbDlVGJahCXrPY472Xzxzsevc/IiUXXMbIykZRXw3JritCnM5rQnPGkwcSvyYf/+X0MMTLhkVESX2YXvN9KPEUZs6voS2hIxV15VcimHmZ53X+ti8xvDWa4UYMp/y4oohfgQpffDPokFq5nTEBRboOZlU+swpMTrRG0raHRbahAyQYKN5FVzq3B434z66IOtd5SpjLprle8GrodsffQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mXs6oCGGb69ZQb4o3/N3Tk0FaE/hDI9ZPuNqhiXt2NE=;
 b=klb8TEB3gyE+eDIE+qnT/gkrpS9GY2c+DalCZjhwjVn/jPvPAo0YiN/P+2icfSZe10OK6nSKbZUGstiHzem83vvru3qAPDXYOgRYUi8yyW7tuXc36OuLRgjC+1LrAh6Gz1RjVdc2u+6ThsmLma0QEA/XGC4dOIv7NGAn9qENkUqcL5DKNLkqJCVCfmoIkgmXLGZpz4L9ev46IPoFjaDARYlGR3zzv3kqK4sEay/5qNVyEnisBg4OXEeuycqVkDQB0BGohtSXt6RQJuhi6eq0kghturQ/x+Fz2AkIvsGKJ3D8V9Js8TIZMq43rmAxjb5XWnRObYWiX6mX68C31T/NfA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=mXs6oCGGb69ZQb4o3/N3Tk0FaE/hDI9ZPuNqhiXt2NE=;
 b=E+Z11Fy+yj+1xhbtbdU41zuj9XdajhmnJdA7Kd9d51BNlnF5y6cQeT9oXH+kXTCxNHZRaJhKG6E+2aaWl2mWz744se2pMTgJ0HS7I/mkdPc1Uynf3R69E7OsgMh4dxXpb2G6OyGQf+DM4npWSGbdgvUPPyE4UPUExlr11YxuJTk=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB1387.namprd12.prod.outlook.com (2603:10b6:3:6c::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2856.20; Mon, 30 Mar 2020 01:33:50 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c%12]) with mapi id 15.20.2856.019; Mon, 30 Mar 2020
 01:33:50 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        rientjes@google.com, srutherford@google.com, luto@kernel.org,
        brijesh.singh@amd.com
Subject: [PATCH v5 01/14] KVM: SVM: Add KVM_SEV SEND_START command
Date: Mon, 30 Mar 2020 01:33:40 +0000
Message-Id: 
 <3f90333959fd49bed184d45a761cc338424bf614.1585531159.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1585531159.git.ashish.kalra@amd.com>
References: <cover.1585531159.git.ashish.kalra@amd.com>
X-ClientProxiedBy: DM5PR2001CA0007.namprd20.prod.outlook.com
 (2603:10b6:4:16::17) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR2001CA0007.namprd20.prod.outlook.com (2603:10b6:4:16::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.19 via Frontend
 Transport; Mon, 30 Mar 2020 01:33:49 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 3ee660f0-ea0c-49d1-e4c8-08d7d44a664a
X-MS-TrafficTypeDiagnostic: DM5PR12MB1387:|DM5PR12MB1387:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB13876B762CD6A5CF1BDC45A08ECB0@DM5PR12MB1387.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-Forefront-PRVS: 0358535363
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10009020)(4636009)(39860400002)(376002)(346002)(366004)(136003)(396003)(186003)(66574012)(66556008)(6666004)(66476007)(86362001)(6916009)(66946007)(316002)(4326008)(7696005)(52116002)(5660300002)(6486002)(16526019)(26005)(36756003)(478600001)(7416002)(81166006)(81156014)(8936002)(2616005)(8676002)(2906002)(956004)(136400200001);DIR:OUT;SFP:1101;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 DjKxISRY7C8UXb4yIncbvyx88BzazXT3aHUJO8fAyZKo58csbYFp4lFMBBc/6HPlzmos/6lt+izRBloEG5K5lJgXK8juuBHnI01DaWqQMLAvyQcTLDlEGAF0Az1flVmMuyhfnr0qUzpgdNckn+Xw1eUHoD+DQuubPgz0DVqIett66hY8Z42A22jpbejN0A60H/AWcMGsXVtXrAoXUvbJ5dEB7LdtbqQ/47UzN+f2a7F7P/04Kyerui0Hh0ksSLZNr1+hYzlEkjlT0M2CyAuvPzrd788Ibd/5PWuIZz+F+z1+VkrK/MJg5hiuRVGodYRUokuvCbXfzZ8iQ/e3K07yQ+/luZTR/ak7vZ4oNKs0sKq7Xg4fLyAtp+V+l4gxuW7Uqb+EJQJ3ecv5g9V+h8St9hSXW9ijPUd5gIQ0+PhEswkKSgAE+rwCkpmGHJfV63h4YyLaQPogcLqLolaALEEONHOzNcBFYXKyjhNPSLQ1JfsA9IuC2JFZgcS4L9HRt0gd
X-MS-Exchange-AntiSpam-MessageData: 
 geylZRr2lWlgSdI0v0q7S7EsmbC9s2VwVxZKG4hOKie2BD++Xyz2cu7VTSo7tDJr28vWJy2vOAJ/cMsESMotVNvIGhVr4b8fId/35I3mfMGsEnbFKVrn7scVpr9R+KU06OM3vuOhhzK3bd3Psc9g6w==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3ee660f0-ea0c-49d1-e4c8-08d7d44a664a
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Mar 2020 01:33:50.7616
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5L+eUD7QKFA5G+7EJTimJQFyodRNc72dR3JIimM9pv6KEGYYXN3nbBDcp4AEMwH5U6Y64c7hw22tb94iJUuYUg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1387
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <Brijesh.Singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  27 ++++
 arch/x86/kvm/svm.c                            | 128 ++++++++++++++++++
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  12 ++
 4 files changed, 171 insertions(+), 4 deletions(-)

```
#### [PATCH v8 01/81] sched/swait: add swait_event_killable_exclusive()
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11465087
Return-Path: <SRS0=cHma=5P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E903913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 10:19:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 179ED20733
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Mar 2020 10:19:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729278AbgC3KTx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 06:19:53 -0400
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:43782 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729206AbgC3KTw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 06:19:52 -0400
Received: from smtp.bitdefender.com (smtp02.buh.bitdefender.net [10.17.80.76])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 5C370306E4AD;
        Mon, 30 Mar 2020 13:12:48 +0300 (EEST)
Received: from localhost.localdomain (unknown [91.199.104.28])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 3CE7C305B7A0;
        Mon, 30 Mar 2020 13:12:48 +0300 (EEST)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
Subject: [PATCH v8 01/81] sched/swait: add swait_event_killable_exclusive()
Date: Mon, 30 Mar 2020 13:11:48 +0300
Message-Id: <20200330101308.21702-2-alazar@bitdefender.com>
In-Reply-To: <20200330101308.21702-1-alazar@bitdefender.com>
References: <20200330101308.21702-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a vCPU is introspected, it waits for introspection commands or event
replies. If the introspection channel is closed, the receiving thread
will wake-up the vCPU threads. With this function the vCPU thread will
wake-up on SIGKILL too.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 include/linux/swait.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
