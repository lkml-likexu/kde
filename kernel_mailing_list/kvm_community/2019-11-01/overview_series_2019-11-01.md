#### [PATCH 1/4] kvm: x86: Dont set UMIP feature bit unconditionallyThread-Topic: [PATCH 1/4] kvm: x86: Dont set UMIP feature bit unconditionally
##### From: "Moger, Babu" <Babu.Moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Moger, Babu" <babu.moger@amd.com>
X-Patchwork-Id: 11223463
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C519913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 17:33:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D43E1217F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 17:33:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ggRqusdQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728441AbfKARdo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 13:33:44 -0400
Received: from mail-eopbgr740087.outbound.protection.outlook.com
 ([40.107.74.87]:15264
        "EHLO NAM01-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728304AbfKARdn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 13:33:43 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=MkazRn1AaAkq9spHjNif3yuUNUpYELu0w5PTkI8bjB09+LR0Ana0TxeGmKYOnZ89y8eyhmjzZJa50Os/138nVk0uYo5lhxuU6OmiYrURN7RFCMU6PcQSejpL3dUIOpEIFcCydZf5GWTQtC8nkZnZ0qLDU8BYhIY25GZPlQklBpza7D47id3IJPkdJ9ZVmmIKevR/1zi/uqThwOBiypwcgexvPOuVZUfTSeFbTxkq2+t/WbgqP5yVAZsC4zkGc7f0BxoK933lldiOC2Df2rzIhzS1BFBubipyNMZjFt67ra4MQ+JupTATPkEDy1subEnRgUAoG9owVU5VRIE0Ag6HDw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=sIo0YTKPq3g4HuGAX3ABUR5y6Om49Ib/5xmdievqoM8=;
 b=PMy5hAcTKHwl/RuPrZbq3kLtQJcCNQbhYX/U9uPHNuH61UFKb14V5spgfbdvVlufaGHQXsNQ1cKa5c8PlCYRBhtVF5aCDf7qG05b/azCR6udp/RKlrMsj0h1R6qhMY9CsGA9lYrT2XtKrChNCLprKe9tUgvPYNH/ikKne91CL1Wx3vXjmdvaUwV7jkg2NM6jI34bFlQIKWoV8wXZ9g13bnZfRmiYq8REsghtdW8VNqnuWLpp7KkTMj1jORkzkZdKQ2NvP1mFMqoXIESpJpjbVNSnBV8J9GPl9mArcYCDSX+zZYy7dymRbM+kM3vj93yaLnWsop7kXGxOGKZg6t0Gkg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=sIo0YTKPq3g4HuGAX3ABUR5y6Om49Ib/5xmdievqoM8=;
 b=ggRqusdQgOdl56LqdiK4nEyRn3IfgWPwcV3Ml4VW/4oIhWsXENIRGgWOh6tiBwgkodgjnqgBt2TsCcf08QHZBSz/ntz9Epk8rxZvFb6MgqGwCPeO/28uOktB8IKlfpU3L2t5bYsxDdpHhHMMUqDibd/VmgH6eUyr4YoPGwlw2xw=
Received: from BL0PR12MB2468.namprd12.prod.outlook.com (52.132.30.157) by
 BL0PR12MB2548.namprd12.prod.outlook.com (52.132.29.11) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2387.24; Fri, 1 Nov 2019 17:33:38 +0000
Received: from BL0PR12MB2468.namprd12.prod.outlook.com
 ([fe80::748c:1f32:1a4d:acca]) by BL0PR12MB2468.namprd12.prod.outlook.com
 ([fe80::748c:1f32:1a4d:acca%7]) with mapi id 15.20.2387.028; Fri, 1 Nov 2019
 17:33:38 +0000
From: "Moger, Babu" <Babu.Moger@amd.com>
To: "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>
CC: "x86@kernel.org" <x86@kernel.org>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "Moger, Babu" <Babu.Moger@amd.com>,
        "luto@kernel.org" <luto@kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "nayna@linux.ibm.com" <nayna@linux.ibm.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH 1/4] kvm: x86: Dont set UMIP feature bit unconditionally
Thread-Topic: [PATCH 1/4] kvm: x86: Dont set UMIP feature bit unconditionally
Thread-Index: AQHVkNp+SVH8W6w/AkiSMfw9AT2GlQ==
Date: Fri, 1 Nov 2019 17:33:38 +0000
Message-ID: <157262961597.2838.16953618909905259198.stgit@naples-babu.amd.com>
References: <157262960837.2838.17520432516398899751.stgit@naples-babu.amd.com>
In-Reply-To: 
 <157262960837.2838.17520432516398899751.stgit@naples-babu.amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN6PR08CA0035.namprd08.prod.outlook.com
 (2603:10b6:805:66::48) To BL0PR12MB2468.namprd12.prod.outlook.com
 (2603:10b6:207:44::29)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.2]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: e02a30c8-bbf2-49b2-8087-08d75ef1a12c
x-ms-traffictypediagnostic: BL0PR12MB2548:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <BL0PR12MB254841D70B9058D588F166D295620@BL0PR12MB2548.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:5797;
x-forefront-prvs: 020877E0CB
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(366004)(396003)(376002)(39860400002)(136003)(346002)(189003)(199004)(66946007)(71190400001)(2501003)(2906002)(71200400001)(11346002)(25786009)(14454004)(476003)(478600001)(2201001)(4744005)(6116002)(3846002)(316002)(5660300002)(54906003)(86362001)(110136005)(4326008)(81156014)(64756008)(76176011)(26005)(102836004)(66066001)(446003)(66446008)(7736002)(99286004)(305945005)(7416002)(8676002)(8936002)(186003)(66476007)(486006)(6486002)(6512007)(6506007)(386003)(66556008)(256004)(14444005)(6436002)(52116002)(103116003)(81166006)(921003)(192303002)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:BL0PR12MB2548;H:BL0PR12MB2468.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 KYBpK5FsAooHoXbk7vnsQJ/4gRul8PyOZ/I60i+AiS1CbpKEwf1ipFk0zTJYROdT8FEjzFIKVBWB+fzhmwU17ccvBmu8vFjkMz2mKecKB6RQJtyaT+JpAMgnqdtWyg1abmKJ+JjIjYKnDo5CHZx5E/b2mNBbyF8shFFAZZ78KqyAp4KOuctvS2XzoF0a7PsrUCsnlYxgUVbAxPBQg6Bj+vnwMZMP8PfLm1pzDgpcFj61fqUVZQ+c9ExAWGI3tdLpqU7fcrzpRFpjbUKROmvThtKVq6r6TV2o/wsiIX/ySYHDFZrfu1WLf+I+9oQnx/uxQKUNsWF+iv0TUgYskN331zN7sUSV2n2kLvZR3qKxxov5L2jR00lwAMpxsvnaOPD3e5EzX9STOHySyrN6sy18Sd9aWDQh+KKTUmcRVhlsPBjktbtU2apNvA6tkCtZgeAw
Content-ID: <3CF0EF04BD1C06498BD1643D01E1912C@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e02a30c8-bbf2-49b2-8087-08d75ef1a12c
X-MS-Exchange-CrossTenant-originalarrivaltime: 01 Nov 2019 17:33:38.2191
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 /Ap3bMeIoOEMdKg+Imjtpu+nhLCirujy51GuWEO8Ub2TJroOStReU9YUuok3fkC8
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL0PR12MB2548
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The UMIP (User-Mode Instruction Prevention) feature bit should be
set if the emulation (kvm_x86_ops->umip_emulated) is supported
which is done already.

Remove the unconditional setting of this bit.

Fixes: ae3e61e1c28338d0 ("KVM: x86: add support for UMIP")

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/kvm/cpuid.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v8 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11222777
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B5DF81390
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 08:50:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 93EEC21D79
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 08:50:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727130AbfKAItx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 04:49:53 -0400
Received: from mga14.intel.com ([192.55.52.115]:34433 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726689AbfKAItw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 04:49:52 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Nov 2019 01:49:51 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,254,1569308400";
   d="scan'208";a="194606595"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga008.jf.intel.com with ESMTP; 01 Nov 2019 01:49:49 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: jmattson@google.com, yu.c.zhang@linux.intel.com,
        yu-cheng.yu@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v8 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i)
 enumeration
Date: Fri,  1 Nov 2019 16:52:16 +0800
Message-Id: <20191101085222.27997-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20191101085222.27997-1-weijiang.yang@intel.com>
References: <20191101085222.27997-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The control bits in IA32_XSS MSR are being used for new features,
but current CPUID(0xd,i) enumeration code doesn't support them, so
fix existing code first.

The supervisor states in IA32_XSS haven't been used in public
KVM code, so set KVM_SUPPORTED_XSS to 0 now, anyone who's developing
IA32_XSS related feature may expand the macro to add the CPUID support,
otherwise, CPUID(0xd,i>1) always reports 0 of the subleaf to guest.

Extracted old code into a new filter and keep it same flavor as others.

This patch passed selftest on a few Intel platforms.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   1 +
 arch/x86/kvm/cpuid.c            | 105 ++++++++++++++++++++++----------
 arch/x86/kvm/svm.c              |   7 +++
 arch/x86/kvm/vmx/vmx.c          |   6 ++
 arch/x86/kvm/x86.h              |   7 +++
 5 files changed, 94 insertions(+), 32 deletions(-)

```
#### [kvm-unit-tests PATCH] x86/tscdeadline_delay: test busy-wait loop in host
##### From: Thadeu Lima de Souza Cascardo <cascardo@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thadeu Lima de Souza Cascardo <cascardo@canonical.com>
X-Patchwork-Id: 11223271
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 576BE13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 14:14:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3F8A62085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 14:14:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727036AbfKAOOU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 10:14:20 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:58508 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726912AbfKAOOT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 10:14:19 -0400
Received: from [91.217.168.176] (helo=localhost.localdomain)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <cascardo@canonical.com>)
        id 1iQXgv-00060W-R9
        for kvm@vger.kernel.org; Fri, 01 Nov 2019 14:14:17 +0000
From: Thadeu Lima de Souza Cascardo <cascardo@canonical.com>
To: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86/tscdeadline_delay: test busy-wait loop in
 host
Date: Fri,  1 Nov 2019 11:14:08 -0300
Message-Id: <20191101141408.17838-1-cascardo@canonical.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the tsc deadline is used, the host might use a busy wait loop, which
might sleep for up to the TSC offset/adjust, which is set when the guest
sets the TSC MSR.

Linux commit b606f189c7 ("KVM: LAPIC: cap __delay at lapic_timer_advance_ns")
fixes the issue and this test check for its regression.

On a kernel without that fix, the test fails with:
FAIL: delta: 4296500469

On a kernel with the fix, the max_delta is usually reported as very low
compared to that one:
max delta: 12423150

Signed-off-by: Thadeu Lima de Souza Cascardo <cascardo@canonical.com>
---
 x86/Makefile.x86_64     |   1 +
 x86/tscdeadline_delay.c | 105 ++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg       |   4 ++
 3 files changed, 110 insertions(+)
 create mode 100644 x86/tscdeadline_delay.c

```
#### [PATCH v4 01/17] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Suthikulpanit,
 Suravee" <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11223867
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C5511599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 22:41:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5528B20679
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 22:41:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="I74xxNIE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727927AbfKAWl3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 18:41:29 -0400
Received: from mail-eopbgr720065.outbound.protection.outlook.com
 ([40.107.72.65]:49770
        "EHLO NAM05-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727029AbfKAWl2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 18:41:28 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nbVvEhhjrezlI6sSz3db6FVyFEbBHT5My9nCJxZQzkNwS2fJ/I2AzxjhuR+6sWx/2ztISINlzumhZM7KP0V0oeqOkGD5gZDEutnY+hu2ZEv/E51+7+ZQHV0SlYlJOEVJbrDi92E3VsLcKTe043bGD43xfpqPTZM4ioAxFfEUH80B4junN66MpcrHyMZnOCWYef/lUXWB0HE6gWowOR2R6DYtwgr+KHxPT7wi1PdQiQ6N2aHJJp+fwEBLsFJlAmmMAZ+mpZZGe91jzoZcGm2xDjfqUGX+ifgQqPNywdLQyU87WvvJlUaI7sNpTayfpFyJ5HqKufv4AsaiBCKnU5O5JA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=F6N0JskZtNUJMa6TuW0hyyf3+VOA2N6fT5GUN4+kOBE=;
 b=K+oqbqQlYP+VjgcLN+U1FfxhT2v2hihij3jwvpvofYOrRzpN2jFRKqRNLdgBBDtZljdckHLA+6AAI+J5gIW/UBDWOCK49TlDmugZmioFnE63CHSJm32wSg06lVstkqDGtgqiH5Woh1GtOCeduMypEXQS1n12G0Nqxn27wboXMoImYvl+n/dUlAPLvnjJETfQ65cVnE/X1HFnRO1CqhuUxF6VJWVGFO7F9T0HKsI8k/dChEyvo0a/DfdkJb5QEPZ5gX/J60i1yntLCt8RGuPboy+yEcZo3cUF8ChUBgYyg/eW2Ow2/5BQGOS5LHwIN8i6xnLvKjdO6cpDTUcwkexRQQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=F6N0JskZtNUJMa6TuW0hyyf3+VOA2N6fT5GUN4+kOBE=;
 b=I74xxNIEEOly4inkGdVEGTza0X7bsXc5Ejd1e0Za83434pS8npifkvGb9UVSqFj6mTYxbpe4EdxIDKEH0z+ooCNfg+1jOIcrxpjss2A5wdd7aYD/wQtN7J17AYHbe69QqgDaaJOd2agvvgcwUNlJIPAPbu1sa81pvV+2toLvhR8=
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (10.255.173.210) by
 DM6PR12MB3243.namprd12.prod.outlook.com (20.179.105.155) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2408.24; Fri, 1 Nov 2019 22:41:23 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862%6]) with mapi id 15.20.2408.024; Fri, 1 Nov 2019
 22:41:23 +0000
From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
CC: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "rkagan@virtuozzo.com" <rkagan@virtuozzo.com>,
        "graf@amazon.com" <graf@amazon.com>,
        "jschoenh@amazon.de" <jschoenh@amazon.de>,
        "karahmed@amazon.de" <karahmed@amazon.de>,
        "rimasluk@amazon.com" <rimasluk@amazon.com>,
        "Grimm, Jon" <Jon.Grimm@amd.com>,
        "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>
Subject: [PATCH v4 01/17] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to
 use struct kvm parameter
Thread-Topic: [PATCH v4 01/17] kvm: x86: Modify kvm_x86_ops.get_enable_apicv()
 to use struct kvm parameter
Thread-Index: AQHVkQV8uR2S90+F3EeDF1s2iEmZGA==
Date: Fri, 1 Nov 2019 22:41:23 +0000
Message-ID: <1572648072-84536-2-git-send-email-suravee.suthikulpanit@amd.com>
References: <1572648072-84536-1-git-send-email-suravee.suthikulpanit@amd.com>
In-Reply-To: <1572648072-84536-1-git-send-email-suravee.suthikulpanit@amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [165.204.78.1]
x-clientproxiedby: SN1PR12CA0047.namprd12.prod.outlook.com
 (2603:10b6:802:20::18) To DM6PR12MB3865.namprd12.prod.outlook.com
 (2603:10b6:5:1c8::18)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 1.8.3.1
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: 44c4422f-ae47-49aa-62a9-08d75f1c9f4e
x-ms-traffictypediagnostic: DM6PR12MB3243:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB3243DC4193D8808F55071D17F3620@DM6PR12MB3243.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:2582;
x-forefront-prvs: 020877E0CB
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(346002)(366004)(376002)(39860400002)(136003)(199004)(189003)(66476007)(66446008)(26005)(6506007)(386003)(86362001)(5660300002)(102836004)(4720700003)(305945005)(7736002)(7416002)(76176011)(256004)(14444005)(8936002)(8676002)(186003)(52116002)(6486002)(478600001)(50226002)(71200400001)(71190400001)(81166006)(6436002)(476003)(2906002)(3846002)(6116002)(6512007)(99286004)(4326008)(2616005)(316002)(11346002)(446003)(486006)(81156014)(14454004)(66946007)(36756003)(110136005)(54906003)(66066001)(64756008)(66556008)(25786009)(2501003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3243;H:DM6PR12MB3865.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 zAip+o0CvfvK/NJiEU2qWbCh2QXoJHyC3ukEZdiNGBz+3DWxSrC7Bz6aOAcJFiXEtbJk3U+llt0HNvB97V6srKaoTrzSMSD8TnPJMh8jYznKWUyiDMVQ8YKb7AmGfodqh6gkok8gKWbLtoPrIwbBRDa6M84HAowJ2jKGQbSzTBH++QvAprsISacs6X3DL3V4+Po31s1M+PgBBeRHkIv6TJr9QVDO22iWlrScvfdSxRILw6CxObk424mWT+WD+b2lxpC3xBNVUFAGi/wUGngM/fyhhI8P7zn2bpIqTUAZk2pFEEPfDl+V+TJpU0nHAio15cUEsfEYZyijZCQHNN5JDqIi9ZwfanOSb8ox0KF1UMHgpLGVFL2cMt65EtNzjTuw44FlpWpGPPeVlzbTB62i0l5yhBAz0gM5y3xSC4pSp54cAZ/99Nn9DlLACMDWovTz
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 44c4422f-ae47-49aa-62a9-08d75f1c9f4e
X-MS-Exchange-CrossTenant-originalarrivaltime: 01 Nov 2019 22:41:23.4251
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 6VH6GvSJXHxtOGfYZkZbktVyl5x31W4Dg5ILqXht9AG6BsMWlz/VvBea52oUh/u6dZLTjOlXBVBi9UA98isG4w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3243
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Generally, APICv for all vcpus in the VM are enable/disable in the same
manner. So, get_enable_apicv() should represent APICv status of the VM
instead of each VCPU.

Modify kvm_x86_ops.get_enable_apicv() to take struct kvm as parameter
instead of struct kvm_vcpu.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/svm.c              | 4 ++--
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 arch/x86/kvm/x86.c              | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PULL RESEND] virtio: fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11223635
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EB7A0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 19:34:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D495F21855
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 19:34:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727869AbfKATeE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 15:34:04 -0400
Received: from mx1.redhat.com ([209.132.183.28]:35290 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727600AbfKATeE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 15:34:04 -0400
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id CF82136898
        for <kvm@vger.kernel.org>; Fri,  1 Nov 2019 19:34:03 +0000 (UTC)
Received: by mail-wr1-f70.google.com with SMTP id e3so3637401wrs.17
        for <kvm@vger.kernel.org>; Fri, 01 Nov 2019 12:34:03 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=DDu4dZguSc1AuhYOU131Dph2BpOLdkpSLt78cfUXrP4=;
        b=Na7j4mmtQ+NW1B/52l+US9PQP2UGHW33wDqGCyIayFQ6SQ9vN07WDUSrThHU2H1oE1
         MOLf0Yj6pgkKBRwtbAo/ef7M7o4DVy9RX2PpHsdN/YsNt8tdHznJytvUVilb732FyNKG
         /NHlG4kNraeenmhnN2MtkeiV7K0dK0XKvYddCJECaqax9rA4ZE+vP/G46FOrGJolBjWc
         g0omgJS5u9hWffDHEgaObtIVUqKEOMAz928Y73LLDXBDV6vBhd4cQEWB6lzNGKFkUF9X
         eCw+O2oqso/eCI6ZM3zxr2/0zfGxuKtXek/tLmvhES6nP+L25pCbGlqxgKzcXbHZgD1/
         A4gQ==
X-Gm-Message-State: APjAAAX2sTSL99WEf1nrRuxBl5palRYqtIsWSdqz/JPqMxuGCp1MKpr7
        as/LWWnZGmtvKh47dRMlGbRcIEDNRYiZmvDOYddXe4VQeMMXUfgHGF8Zv1NKs6TqCxYxuqrlfCF
        hsmVG5Nxf62CT
X-Received: by 2002:a1c:3dc4:: with SMTP id
 k187mr11325441wma.167.1572636841902;
        Fri, 01 Nov 2019 12:34:01 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqz0xUERtPHGhyf71lfOGgMY82PECMv5XY2AKvQnIIKeMbgOF3SlGefp223udCXQMXep6c44yw==
X-Received: by 2002:a1c:3dc4:: with SMTP id
 k187mr11325432wma.167.1572636841676;
        Fri, 01 Nov 2019 12:34:01 -0700 (PDT)
Received: from redhat.com (94.222.26.109.rev.sfr.net. [109.26.222.94])
        by smtp.gmail.com with ESMTPSA id
 65sm12393239wrs.9.2019.11.01.12.33.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 01 Nov 2019 12:34:00 -0700 (PDT)
Date: Fri, 1 Nov 2019 15:33:57 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        stable@vger.kernel.org, jasowang@redhat.com, mst@redhat.com,
        sgarzare@redhat.com, yong.liu@intel.com
Subject: [PULL RESEND] virtio: fixes
Message-ID: <20191028042900-1-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Could not figure out whether I sent this pull request or not. Sorry about
the noise if I did.

The following changes since commit 7d194c2100ad2a6dded545887d02754948ca5241:

  Linux 5.4-rc4 (2019-10-20 15:56:22 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to b3683dee840274e9997d958b9d82e5de95950f0b:

  vringh: fix copy direction of vringh_iov_push_kern() (2019-10-28 04:25:04 -0400)

----------------------------------------------------------------
virtio: fixes

Some minor fixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Jason Wang (1):
      vringh: fix copy direction of vringh_iov_push_kern()

Marvin Liu (1):
      virtio_ring: fix stalls for packed rings

Stefano Garzarella (1):
      vsock/virtio: remove unused 'work' field from 'struct virtio_vsock_pkt'

 drivers/vhost/vringh.c       | 8 +++++++-
 drivers/virtio/virtio_ring.c | 7 +++----
 include/linux/virtio_vsock.h | 1 -
 3 files changed, 10 insertions(+), 6 deletions(-)
```
#### [kvm-unit-tests PATCH v3 1/2] x86: realmode: save and restore %esFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11223653
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A923213BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 20:34:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 888A121897
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 20:34:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="p0pPMBKN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727789AbfKAUeG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 16:34:06 -0400
Received: from mail-vk1-f202.google.com ([209.85.221.202]:49153 "EHLO
        mail-vk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726709AbfKAUeG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 16:34:06 -0400
Received: by mail-vk1-f202.google.com with SMTP id v71so4342769vkd.16
        for <kvm@vger.kernel.org>; Fri, 01 Nov 2019 13:34:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=NdMpYXsn4p41hC1RJFMhKomdkFTZyn7osluAUD6/350=;
        b=p0pPMBKN0bVlXmIR2MVnncKCGPL8AngtJCAkTsQiLa8m0HNXprk7oZ43VRQunJMVuq
         xUDRYsRN1fbeS0Q6ir3OZziHWOC8d+nfrucXeZcjKmPKfH+BjKeu64ge2wBeZEmcjn2N
         K2/We3QaeIlw9z5urIzqiSM7VYv1DtQed+Jo+HswKYtS+OP2bAX4MxKViCiVHpdaFwyf
         MaQQF6rSQ+ETDLA+s3XknCSkKyys6d+MA/sIMRUY8gdaPd2UsPnTrE+ccpxQ70p53sVu
         ACKEdqfH6A1eMZO9tOVfApSvz058PlCWvusKJNO68uNwD4HNcKc1R0hHaZo94aBYxDUh
         JG0g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=NdMpYXsn4p41hC1RJFMhKomdkFTZyn7osluAUD6/350=;
        b=nnxSGFNhL4biYPqNSbVTtCieck+V0fmGsyyQDO+eBYJTFQUMZxbOS8R1OEHefpZ6/6
         MnuXaiDwzdGTmZV50lsUS6sCCateeRCQsM5glC0z4pthhUkaUSanWBrbNIDo6LbyEjr2
         ug4p9vRMOg//er7rSUzhgLJWzQ4SD1QTf3Jmx1VVhV7dB+hPqxfP+em0lyuf6ggmuog0
         b2IQXayeQ6yfKoXJga5m9dCMBdaEzTwl6RnScDazRpc550mmInVZhI0qHC4KYC/vSKuv
         mXf1mGHsLJ6LBXgYwlya9/mw+hUZ91QRvrDAy9TOtQzf9W8FRLTD8UM67BkuRYngvL3l
         A/Kw==
X-Gm-Message-State: APjAAAWt6QjzdbNRds7Aghqbl56XFbeTxW1oewXvjerUCBkjfJlfSvmV
        dqWGRrx1kpR8ROjFYeQc8YJemiLdJQ0eP69SJRVw8bmHbY6K0uTrarUsfNg2eaPAjQaKfNuc4W+
        3xD6eNk21jJVdzClZnBYmO0OOwfkItTt7/66dbQg9f3Wc6L27KKKo1g==
X-Google-Smtp-Source: 
 APXvYqzI3br4HrCZ3rQ3okOYczJAAUcQJgRU4sCtjx7djnW+Mycbufyxm/RIeyEmQykmLylzMHIBpgIduQ==
X-Received: by 2002:a1f:d3c1:: with SMTP id k184mr2277469vkg.46.1572640445149;
 Fri, 01 Nov 2019 13:34:05 -0700 (PDT)
Date: Fri,  1 Nov 2019 13:33:52 -0700
In-Reply-To: <20191101203353.150049-1-morbo@google.com>
Message-Id: <20191101203353.150049-2-morbo@google.com>
Mime-Version: 1.0
References: <20191101203353.150049-1-morbo@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH v3 1/2] x86: realmode: save and restore %es
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, jmattson@google.com
Cc: thuth@redhat.com, alexandru.elisei@arm.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some of the code test sequences (e.g. push_es) clobber ES. That causes
trouble for future rep string instructions. So save and restore ES
around the test code sequence in exec_in_big_real_mode.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/realmode.c | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
