#### [kvm-unit-tests PATCH 1/2] x86: vmx: Comprehensive max VMCS field search
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11302997
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E5A113A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 10:11:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5653C24672
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 10:11:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726701AbfLSKL3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 05:11:29 -0500
Received: from mail-pl1-f195.google.com ([209.85.214.195]:33728 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726609AbfLSKL3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 05:11:29 -0500
Received: by mail-pl1-f195.google.com with SMTP id c13so2342588pls.0
        for <kvm@vger.kernel.org>; Thu, 19 Dec 2019 02:11:28 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=bfL9G0/z//jDm9lThiYy6HzVD6N1lKQVtSeDfgyyw7o=;
        b=NPKMxTN9dh+sITZ2jenEIcCMDBB2hMc3cBN6ASaBcEuRVzzG2sDgKEEXJJ0ckQcFwI
         mqGtQ2nSXE4lSgIDCRIKHF7laoRrsivOMj4e6yC0jqWsu31UfgYgXmi1/oTc+gYiyq0O
         vgUh7S4n5+HbEwB0YogXkNVWqEBWcHCwvLtzQbG8MKXWiDsrpDHzhXoa70XOt+w+ZVA6
         1hlc9q9iLCupu7S+t27qPmakBvy8zerLfDk0B50NnFEGxOGOvfIJE2HAtWitgaDpMvyh
         bHKyjN9EpqzFJJiTObMPhcWTacwIt/NP/Jtn5EyBOqs/QsfuMrpUe0ydTXYQjTa3y/7J
         clkA==
X-Gm-Message-State: APjAAAXzuplrXbqbKDzjSNAIX0Zwx8urYXOZSM5ErtmX2EJySZkdBoJk
        nf1/YHLV2W5rA/PrHssrLBE=
X-Google-Smtp-Source: 
 APXvYqwHMFQoXCxXjp+W86S5b39pMbKC47DWXhLLUIHS+OsB/WUF4RS8TIiVkkCZKjI7RcQ7Wmpuiw==
X-Received: by 2002:a17:902:ac97:: with SMTP id
 h23mr8309400plr.237.1576750288088;
        Thu, 19 Dec 2019 02:11:28 -0800 (PST)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 c184sm7565530pfa.39.2019.12.19.02.11.26
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 19 Dec 2019 02:11:26 -0800 (PST)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <namit@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH 1/2] x86: vmx: Comprehensive max VMCS field
 search
Date: Thu, 19 Dec 2019 02:10:05 -0800
Message-Id: <20191219101006.49103-2-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191219101006.49103-1-namit@vmware.com>
References: <20191219101006.49103-1-namit@vmware.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Search all VMCS fields when looking for the max VMCS field index.
Perform the search backwards to save some time. Change the existing test
to compare the maximum expected index (based on MSRs) is equal to the
actual one.  This improves the test that currently performs
greater-equal comparison.

Suggested-by: Jim Mattson <jmattson@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/vmx.c | 38 ++++++++++++++++++++++++++++++++++----
 1 file changed, 34 insertions(+), 4 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-fixes-5.5-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11302481
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B9CC14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 00:19:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 58D5C2465E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 00:19:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="QPXN2QO8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726656AbfLSATW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 19:19:22 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:50811 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726463AbfLSATW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 19:19:22 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 47dXYh2zFLz9sPh; Thu, 19 Dec 2019 11:19:20 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1576714760; bh=zDFPOp5nfTe9y2XdAgtTDk1OYIJnpIlIJMAWmNX76Rs=;
        h=Date:From:To:Cc:Subject:From;
        b=QPXN2QO89XnH+U6Igy7bOrJWBozpChUM+Wfy1iWU17v9LnKwNUDPwiIJ6RdsQ6UDU
         0dVpA3TDAPB379FbLFETgcaMriAGXc6QdxOdLISkVhXDDOQjyB5PsJg1qggTpjLG3n
         2NkzffxNyh3l+6xNAPkomM4cZNw88a9Ui5ofcIfFI9TQ0TiQFgt67D4irpjlRUhuHd
         EUy4Ew0JUrO7StTViV3GYagW726jQvmjqU11dnYGh7ifz9f5Gc4HfXGa/8VTodJ5Nb
         s7PAww+V/uN6m/iRZZua2LMIEkQHrNx7oE78quTyj1zyHbr3WmXTI8u/PdV91sgPmt
         lgRRVXFVoP3CA==
Date: Thu, 19 Dec 2019 11:19:12 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-fixes-5.5-1 tag
Message-ID: <20191219001912.GA12288@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-fixes-5.5-1 to get one commit which
should go in 5.5.  It fixes a regression introduced in my last pull,
which added an ultravisor call even on systems without an ultravisor.

Thanks,
Paul.

The following changes since commit 7d73710d9ca2564f29d291d0b3badc09efdf25e9:

  kvm: vmx: Stop wasting a page for guest_msrs (2019-12-04 12:23:27 +0100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-5.5-1

for you to fetch changes up to d89c69f42bf0fe42d1f52ea9b3dca15b1ade7601:

  KVM: PPC: Book3S HV: Don't do ultravisor calls on systems without ultravisor (2019-12-18 15:46:34 +1100)

----------------------------------------------------------------
PPC KVM fix for 5.5

- Fix a bug where we try to do an ultracall on a system without an
  ultravisor.

----------------------------------------------------------------
Paul Mackerras (1):
      KVM: PPC: Book3S HV: Don't do ultravisor calls on systems without ultravisor

 arch/powerpc/kvm/book3s_hv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
```
#### [PATCH] kvm/svm: PKU not currently supported
##### From: John Allen <john.allen@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Allen <john.allen@amd.com>
X-Patchwork-Id: 11303859
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5106F138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 15:24:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2DEEB222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 15:24:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="zafQFKN7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726858AbfLSPYE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 10:24:04 -0500
Received: from mail-eopbgr700049.outbound.protection.outlook.com
 ([40.107.70.49]:29152
        "EHLO NAM04-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726759AbfLSPYD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 10:24:03 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nNFF7S2oyikJkfRhQ6dadrBbhQWtRQn6b/8Zdly+2u3IsdrZSuR/yh+J/ykqFt8Bia6sUb/kC6P5CgTcXI/ieg5K5MZ4BCb/NUYcZGwPWaixXNhlwpwJl2UJZ7PlPGF55GZpRAIJBdn+x3bDSTEEnFwLnBWImnIQ5jUEIgCuIcR4smt6vVxGMslJSxTPWaFtkP/Y/jxZZoiX593rgu2GYWEInf8BPs0FZkC3Im+OuEA72IT+gHjDVBj7rTvkf3Fm0H4xit931mQjO9rq5TpnOIDJwKLF+AE8JTba1954aPaa6uC46weWIuOfG/8HuCapdPSwrMEiZRLmYnO0UYTDJQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=colmVbztxjP6DO7DVSkO1JYZKkoKN0QbvkdUXky0O94=;
 b=gxrMkdPNenzrjdGumh9/qrIqnSxkuAmf2VXI0XB0mhA/8Ht37QMxBxG6OYVYX2hO71hmfz3A/QPOGFlh7D94QNmrnh7sksUwTMaUNZ17qbMX5/yvbuJIDyp1g5uuF584kwYvvhUEsbE8aMFgo8f6XqJIH2ZP9DQFun4SIXX5qd52WTnQ4Iu5C1kapsj44vqf+xGZJdepZ8uLMZ/xAsg59r3q5zbzn2JNHvkaCqNoXK4S3C433WPa6iqYdhChhHhCfQMTj2CIBcTxUuFT650mhli8vizYWiwTwDWZ1THwvZWzEgPa+huBzVO7vzV5TiWqtl0CR/aSw/c9iODNgiALwA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=colmVbztxjP6DO7DVSkO1JYZKkoKN0QbvkdUXky0O94=;
 b=zafQFKN7hf8jMnaweOv5l2bsHGDv3MWi2RI9y7ge+OO+yjz+lQR0QbxuZl9XVd/VRyqo5m8tKWroFEM0X3NWoAiIDftCrGQ5j5LWmCCb+EYBW+NhE8Ky1s3J5bjsWP12Fc/FpJ3yQvSD4K07/iUosE4Q5pM6kTaaQV9RUuebvMk=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=John.Allen@amd.com;
Received: from DM5PR12MB2423.namprd12.prod.outlook.com (52.132.140.158) by
 DM5PR12MB1708.namprd12.prod.outlook.com (10.175.89.22) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2559.14; Thu, 19 Dec 2019 15:23:59 +0000
Received: from DM5PR12MB2423.namprd12.prod.outlook.com
 ([fe80::84ad:4e59:7686:d79c]) by DM5PR12MB2423.namprd12.prod.outlook.com
 ([fe80::84ad:4e59:7686:d79c%3]) with mapi id 15.20.2538.019; Thu, 19 Dec 2019
 15:23:59 +0000
From: John Allen <john.allen@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        rkrcmar@redhat.com, John Allen <john.allen@amd.com>
Subject: [PATCH] kvm/svm: PKU not currently supported
Date: Thu, 19 Dec 2019 09:23:32 -0600
Message-Id: <20191219152332.28857-1-john.allen@amd.com>
X-Mailer: git-send-email 2.24.0
X-ClientProxiedBy: DM3PR12CA0067.namprd12.prod.outlook.com
 (2603:10b6:0:57::11) To DM5PR12MB2423.namprd12.prod.outlook.com
 (2603:10b6:4:b3::30)
MIME-Version: 1.0
X-Mailer: git-send-email 2.24.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c1383e8f-10a8-4740-38ff-08d7849778ab
X-MS-TrafficTypeDiagnostic: DM5PR12MB1708:|DM5PR12MB1708:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB170844025F1AD2A63A7548C69A520@DM5PR12MB1708.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-Forefront-PRVS: 0256C18696
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(366004)(136003)(39860400002)(346002)(376002)(396003)(189003)(199004)(6486002)(66946007)(66556008)(316002)(4744005)(44832011)(6666004)(6916009)(6506007)(6512007)(2906002)(4326008)(36756003)(66476007)(186003)(5660300002)(8936002)(26005)(478600001)(86362001)(81166006)(81156014)(52116002)(1076003)(2616005)(8676002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM5PR12MB1708;H:DM5PR12MB2423.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 8LKmk6L+W3OPdVTRQ1OB4HdUY865BTrZwSBO9nWQG72ABCKfo+DEC58o/vLuJPpp7CC+ZFioKd3NUGeUduia83yTr7eRpQ5QbBomfayn/gDRbYHNqKcJ+FjEHdrhOZiz4UWywP0Z0P2Dih7453t3O1E57p2uxxI876JypHKZZvUiD0yhPq3V/FYBvPH/9dd8iUicykHGCl4sCMMEePW0npcy32Hj+sbiWBEqTu+m0tDpH/RSNpMRDp/9z1EYmHqNr7Eqb9gjD66R3RFBB7ekYtY0VMq3D5EmY5QcP0qcmSWpetTVWxc2bT3rqlpLuuDZDY0oTK9/omb2smoWLB97gYn6C5oIyNxFrbNWIICYkkRcL/bcCmt4cWO1DL8DigiFJCMHYl2iPbI5Xpg7p/lThQ2yhfx4olDO79TrUSTTaCRMyAyOnxH8xHvG9M1jkq5s
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c1383e8f-10a8-4740-38ff-08d7849778ab
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Dec 2019 15:23:59.7448
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 izVw4Znde0Ge/4/7HsSpTs4drbqRuvZnM/r+cLoKKkOaXtFb8SqiIz5geeGD3oIxvT6ngDRpRPsFSo7FY5lXkg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1708
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current SVM implementation does not have support for handling PKU. Guests
running on a host with future AMD cpus that support the feature will read
garbage from the PKRU register and will hit segmentation faults on boot as
memory is getting marked as protected that should not be. Ensure that cpuid
from SVM does not advertise the feature.

Signed-off-by: John Allen <john.allen@amd.com>
---
 arch/x86/kvm/svm.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v4 1/7] iommu/vt-d: Identify domains using first level page table
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11302597
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 671B2138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 03:17:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4FF2524672
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 03:17:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726858AbfLSDRh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 22:17:37 -0500
Received: from mga05.intel.com ([192.55.52.43]:29385 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726463AbfLSDRf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 22:17:35 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Dec 2019 19:17:35 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,330,1571727600";
   d="scan'208";a="222160402"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by fmsmga001.fm.intel.com with ESMTP; 18 Dec 2019 19:17:33 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v4 1/7] iommu/vt-d: Identify domains using first level page
 table
Date: Thu, 19 Dec 2019 11:16:28 +0800
Message-Id: <20191219031634.15168-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191219031634.15168-1-baolu.lu@linux.intel.com>
References: <20191219031634.15168-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This checks whether a domain should use the first level page
table for map/unmap and marks it in the domain structure.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel-iommu.c | 39 +++++++++++++++++++++++++++++++++++++
 1 file changed, 39 insertions(+)

```
#### [PATCH v12] mm: devmap: refactor 1-based refcounting for ZONE_DEVICE pages
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11302497
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E62E913B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 00:41:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B9D11227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 00:41:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="qjIOKqdC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726762AbfLSAl0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 19:41:26 -0500
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:12803 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726463AbfLSAl0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 19:41:26 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dfac6eb0000>; Wed, 18 Dec 2019 16:40:11 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Wed, 18 Dec 2019 16:40:40 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Wed, 18 Dec 2019 16:40:40 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 19 Dec
 2019 00:40:40 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 19 Dec 2019 00:40:39 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dfac7070000>; Wed, 18 Dec 2019 16:40:39 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: "Kirill A . Shutemov" <kirill@shutemov.name>,
 Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 Christoph Hellwig <hch@lst.de>
Subject: [PATCH v12] mm: devmap: refactor 1-based refcounting for ZONE_DEVICE
 pages
Date: Wed, 18 Dec 2019 16:40:37 -0800
Message-ID: <20191219004037.1198078-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191218160420.gyt4c45e6zsnxqv6@box>
References: <20191218160420.gyt4c45e6zsnxqv6@box>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576716012; bh=meY7XSFZGFTm0ReBYolvDdqRBgCh/HSlArb5Zg3NFvk=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=qjIOKqdCUd7FwtXps/EX5rcy2jzX7ECH7d3gscZlvPWK+USZzY1q0dAG+H1A1e4bW
         xIdpfAI5t4vavi9qpNMvGtiweIkR1awxL4TYXPZwaeONkFcFN1zXQbpW/68snevPNj
         5QIP3HFe/KnwTQJ5t/CB3h4eLlluOox9FBIYdqA3HpeElohSY3KZjP+6dBkbINRhFa
         ZYRgTzuq1d6+3U/JsKziS6j7uhAZMlje1/Nk/EI1s0RtNW9Xt5H7STM2pMGvX9z96O
         6weRpZ4IdcHq5gWYu+R05VYD+Ro8D3XakiiYQK6azXLHolwxZWIhC6GYnIMG6nSLyM
         S6aDYq/kU5kxg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An upcoming patch changes and complicates the refcounting and
especially the "put page" aspects of it. In order to keep
everything clean, refactor the devmap page release routines:

* Rename put_devmap_managed_page() to page_is_devmap_managed(),
  and limit the functionality to "read only": return a bool,
  with no side effects.

* Add a new routine, put_devmap_managed_page(), to handle
  decrementing the refcount for ZONE_DEVICE pages.

* Change callers (just release_pages() and put_page()) to check
  page_is_devmap_managed() before calling the new
  put_devmap_managed_page() routine. This is a performance
  point: put_page() is a hot path, so we need to avoid non-
  inline function calls where possible.

* Rename __put_devmap_managed_page() to free_devmap_managed_page(),
  and limit the functionality to unconditionally freeing a devmap
  page.

This is originally based on a separate patch by Ira Weiny, which
applied to an early version of the put_user_page() experiments.
Since then, Jérôme Glisse suggested the refactoring described above.

Cc: Christoph Hellwig <hch@lst.de>
Suggested-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Signed-off-by: Ira Weiny <ira.weiny@intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 include/linux/mm.h | 18 +++++++++++++-----
 mm/memremap.c      | 16 ++--------------
 mm/swap.c          | 27 ++++++++++++++++++++++++++-
 3 files changed, 41 insertions(+), 20 deletions(-)

```
#### [PATCH v2] kvm/svm: PKU not currently supported
##### From: John Allen <john.allen@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Allen <john.allen@amd.com>
X-Patchwork-Id: 11304357
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4952109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 20:18:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 778242467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 20:18:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="LHNNmDUm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726948AbfLSUSP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 15:18:15 -0500
Received: from mail-bn7nam10on2083.outbound.protection.outlook.com
 ([40.107.92.83]:4216
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726884AbfLSUSP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 15:18:15 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hT5havNwrHD1RDGlNWqFXyEQIkEtksFKpFFqS8n2s70TaQ8lkMalnNL50iw2wtsIvXkuwtQ77wLwi0K98DwnFUmrFD0kdrUXpDYr/CsjuKr5SECXARBwpbNcGb5ZReRnphDGYsypESx4uLzYABxIrJgOF3fFFcgMApYLiSVHHGU+a/dxi2JGj21XgRuczSLaa14wmx4y8U+u1IFyLV64866YShvCrFKwnCWwE6lp5rHnkSO+lgPK9hJETE7KINF6KjEtdCUX6xsbDNsSek3euOLU+wtIntxMZ7vwrpESLS+By6WxQ1riufvqHxzOJ1tXjXS3jKJCdwGzIIVRAm4SPw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Pwm/ZNYhK49hcRhzLjPeDVSBTZseA94Kn46DkUk/NRk=;
 b=nPkDlOSOuD5JxsxbKr8DG6AwhfIhdoeghAxilASRJBrTPsvSZsm5mO834YPd9YUYTYAkCGv5yebxcQBdVZhBJiVkGp8J8qxcfzGRgX9+lamYBRIZ2cxPBz3OL1UUjQB8jEfU2xkjCeXXx6y0TPKiAR4L6F2ivAKNNd3SP1jWMnCERVvUYIZSN5Nw93IikFHhBc2lMuc+A8rZM14POd3OYtIxQcvpMH/Y7G5IzEzKdzBd/6ky0sNFJo7XnSjnNflLWWvCLyPpBCWVsQVcubL78AXJ1MahVtxemoTp3ah1Lx3F+htIiJpsM2MutCwOs5hSAkfRpr7QZTCL7YQFXjj56w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Pwm/ZNYhK49hcRhzLjPeDVSBTZseA94Kn46DkUk/NRk=;
 b=LHNNmDUm9b4sYeOKAhgwFyVpbApqmcISW27hebx1ZJPNkXt5CPxsYdHjU6WwCK5cWjaNMqgcL7Ixud4lK4lTiqZvKNwQ89PHRhbQEJa/2AjLqcxW6pGfBOPhDi/cMmV2dS2iyjA7+AA0rOiqjIWDpSf1LtPGVm36teSZzz+SF90=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=John.Allen@amd.com;
Received: from DM5PR12MB2423.namprd12.prod.outlook.com (52.132.140.158) by
 DM5PR12MB1834.namprd12.prod.outlook.com (10.175.87.9) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2538.19; Thu, 19 Dec 2019 20:18:10 +0000
Received: from DM5PR12MB2423.namprd12.prod.outlook.com
 ([fe80::84ad:4e59:7686:d79c]) by DM5PR12MB2423.namprd12.prod.outlook.com
 ([fe80::84ad:4e59:7686:d79c%3]) with mapi id 15.20.2538.019; Thu, 19 Dec 2019
 20:18:10 +0000
From: John Allen <john.allen@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        rkrcmar@redhat.com, vkuznets@redhat.com,
        John Allen <john.allen@amd.com>
Subject: [PATCH v2] kvm/svm: PKU not currently supported
Date: Thu, 19 Dec 2019 14:17:59 -0600
Message-Id: <20191219201759.21860-1-john.allen@amd.com>
X-Mailer: git-send-email 2.24.0
X-ClientProxiedBy: SN4PR0401CA0018.namprd04.prod.outlook.com
 (2603:10b6:803:21::28) To DM5PR12MB2423.namprd12.prod.outlook.com
 (2603:10b6:4:b3::30)
MIME-Version: 1.0
X-Mailer: git-send-email 2.24.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c8a936f5-ad6c-4e25-0f9f-08d784c0913a
X-MS-TrafficTypeDiagnostic: DM5PR12MB1834:|DM5PR12MB1834:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1834BAE4AC326DC2B04F37A09A520@DM5PR12MB1834.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-Forefront-PRVS: 0256C18696
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(39850400004)(396003)(366004)(376002)(346002)(199004)(189003)(4326008)(1076003)(316002)(6916009)(6666004)(6512007)(6506007)(86362001)(8936002)(26005)(186003)(36756003)(6486002)(478600001)(81166006)(44832011)(5660300002)(2616005)(66946007)(81156014)(8676002)(52116002)(66476007)(66556008)(2906002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM5PR12MB1834;H:DM5PR12MB2423.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 IEdg5eAxfEtFDhfnSDCmtnBwudl0A1MHgbQf3kXLndo2Q2WVWwWDO7xdbCvenkcrnVud0j8DIPi+S78lSuzsDgs+nskvPaW4paDUlbl1zrMTx7DDdYhxa2sb8sO3uppwqZuU+lZH4gUyI9BKGD966L50PRirJFtF+n5U7D6iLSWLwBt6J0hPFpsvK51l1HsYME0LbWsoyysdkgd6hnfC7MBPGBvUheutHKW/SB0Tn+DXE+NVKk3qTXuQL5cl+Z9xnb0A9Kg/akf/2d7XhXsknCXgC3dEgvXhLw+rGXdLbAV0xZorMtMqy56ySar4EDvN4vbIh6tS2uyJCGAH//XAMNosjn0FVWtQ6bGRcCaWPERBBMrQD5DfCm9yEJU6pDr61pY8XSNoKR7am39J5vHevBmUiOFJF8doAsTtv1fN7fSTF6o0z54MQC0GbU1HAJmV
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c8a936f5-ad6c-4e25-0f9f-08d784c0913a
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Dec 2019 20:18:10.3172
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 HfgKrOIaXHhMgVE8LT61ZhBddgpBLAPiG+MZ33EM7xa2OhH6r3DNqJ74KH8+Q44bqYJj3MaNZ5QUHboVjULW6Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1834
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current SVM implementation does not have support for handling PKU. Guests
running on a host with future AMD cpus that support the feature will read
garbage from the PKRU register and will hit segmentation faults on boot as
memory is getting marked as protected that should not be. Ensure that cpuid
from SVM does not advertise the feature.

Signed-off-by: John Allen <john.allen@amd.com>
---
v2:
  -Introduce kvm_x86_ops->pku_supported()
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/cpuid.c            | 4 +++-
 arch/x86/kvm/svm.c              | 6 ++++++
 arch/x86/kvm/vmx/capabilities.h | 5 +++++
 arch/x86/kvm/vmx/vmx.c          | 1 +
 5 files changed, 16 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: remove unnecessary return vals of kvm pit functions
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11302583
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98EF8921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 02:35:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7656A24650
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 02:35:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726813AbfLSCfw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 21:35:52 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:57026 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726700AbfLSCfv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 21:35:51 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id E3B169EA66CD9E325FA9;
        Thu, 19 Dec 2019 10:35:48 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.439.0; Thu, 19 Dec 2019
 10:35:40 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: x86: remove unnecessary return vals of kvm pit
 functions
Date: Thu, 19 Dec 2019 10:35:20 +0800
Message-ID: <1576722920-10558-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The return vals of kvm pit functions are always equal to 0, which means
there is no way to failed with these function. So remove the return vals
as it's unnecessary to check these. Also add BUILD_BUG_ON to guard against
channels size changed unexpectly.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
v2:
	reorganize the patches. The previous one looks unresonable. I'm
sorry about it.
---
 arch/x86/kvm/x86.c | 46 +++++++++++++++++++++++-----------------------
 1 file changed, 23 insertions(+), 23 deletions(-)

```
