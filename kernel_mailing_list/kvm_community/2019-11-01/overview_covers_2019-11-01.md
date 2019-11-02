

#### [PATCH v8 0/7] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Nov  1 08:52:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11222779
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09452139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 08:50:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E544421D79
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 08:50:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726948AbfKAItv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 04:49:51 -0400
Received: from mga14.intel.com ([192.55.52.115]:34433 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726689AbfKAItv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 04:49:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Nov 2019 01:49:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,254,1569308400";
   d="scan'208";a="194606591"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga008.jf.intel.com with ESMTP; 01 Nov 2019 01:49:47 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: jmattson@google.com, yu.c.zhang@linux.intel.com,
        yu-cheng.yu@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v8 0/7] Introduce support for guest CET feature
Date: Fri,  1 Nov 2019 16:52:15 +0800
Message-Id: <20191101085222.27997-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM change is required to support guest CET feature.
This patch serial implemented CET related CPUID/XSAVES enumeration, MSRs
and vmentry/vmexit configuration etc.so that guest kernel can setup CET
runtime infrastructure based on them. Some CET MSRs and related feature
flags used reference the definitions in kernel patchset.

CET kernel patches is here:
https://lkml.org/lkml/2019/8/13/1110
https://lkml.org/lkml/2019/8/13/1109

v7 -> v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v6 -> v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v5 -> v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v4 -> v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v3 -> v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v2 -> v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v1 -> v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.


PATCH 1    : Fix CPUID(0xD, n) enumeration to support XSS MSR.
PATCH 2    : Define CET VMCS fields and bits.
PATCH 3    : Pass through CET MSRs to guest.
PATCH 4    : Load guest/host CET states on vmentry/vmexit.
PATCH 5    : Enable update to IA32_XSS for guest.
PATCH 6    : Load Guest FPU states for XSAVES managed MSRs.
PATCH 7    : Add user-space CET MSR access interface.



Sean Christopherson (1):
  KVM: X86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (6):
  KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
  KVM: VMX: Define CET VMCS fields and #CP flag
  KVM: VMX: Pass through CET related MSRs
  KVM: VMX: Load CET states on vmentry/vmexit
  KVM: X86: Enable CET bits update in IA32_XSS
  KVM: X86: Add user-space access interface for CET MSRs

 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/include/asm/vmx.h      |   8 +
 arch/x86/include/uapi/asm/kvm.h |   1 +
 arch/x86/kvm/cpuid.c            | 121 +++++++++-----
 arch/x86/kvm/cpuid.h            |   2 +
 arch/x86/kvm/svm.c              |   7 +
 arch/x86/kvm/vmx/capabilities.h |  10 ++
 arch/x86/kvm/vmx/vmx.c          | 272 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  25 ++-
 arch/x86/kvm/x86.h              |  10 +-
 10 files changed, 415 insertions(+), 46 deletions(-)
```
#### [PATCH 0/4] Emulate and enable UMIP feature on AMD
##### From: "Moger, Babu" <Babu.Moger@amd.com>

```c
From patchwork Fri Nov  1 17:33:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Moger, Babu" <babu.moger@amd.com>
X-Patchwork-Id: 11223459
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D46F1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 17:33:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2317F21855
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 17:33:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="v5dwu2Xl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727940AbfKARdg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 13:33:36 -0400
Received: from mail-eopbgr700086.outbound.protection.outlook.com
 ([40.107.70.86]:2017
        "EHLO NAM04-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726554AbfKARdg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 13:33:36 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=DSkd1gtA7I14yHHWIg1gN3Ei756f4M9rvbNf40/UKVodmjv//JwVN2mG9sD9K/ODbrK/wSPvmPPtC5w1V86v7z/GwI7rTr9w6w7U2U2I7UMHUbXfpJ7d7QX1UnpKkN5DmzxAo0mBlR3HyWczkR95smZ75OMYjtPukahjYjhGuRlLa/1l2Aey2BC8gQYOlKCUD5owKC4T1o0r5xsDW9qxZqVXnt6Pr/G5PN7cdaKdkzC+37V6bOVdA+BmBC9dzE94ZO7wcnykrkPmiti0wucTWGIS1yfKzLlsC2Nf53xylVxj5M14hG1JV0ULr3AOgrHsPPO9HV7Biwyrx3ydb2x/DA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H/dGH5xrTnpEDELMuBijtP5Xkd6krd5g9D3YNTiBfdk=;
 b=FYudDhtiHSOhJb1sZe0LDDN+69fAWrjDkY4lhzOvhSiSSKQcu6EW0e67KBmIRMl4Zpl2j+T3GuLHwy93fcf77800fXNpEj2GSgucsKvPo9qGJoUHSDwYtOM/VBawhiEmEFD5aOJ8ZrOyyNFX3O6f0wmYn0hx5+bIRrScY1neKxRed1OsO1yVFa3uz+v6//Vz7f8b+K+lde2kIa5YNEWvIJhpcCmMwSoJeakqaDqaoUdwnJikZJror9j1MfBAWPcjTVx5pBoOlhbPe7kR55cP+1siAtpKIAZ/dcQynd60SpAb1GeIMk3VOO7q4gwgNx1zkMC30uueV4zkAQFAbYmJUw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H/dGH5xrTnpEDELMuBijtP5Xkd6krd5g9D3YNTiBfdk=;
 b=v5dwu2XlOmtDDDa5b3G8rnoLZjjN7owoGHEqAaeTXgA5Oz3ezQYSBRkcD679HbQjafBgfa8kFoZR8aaUDoXa4fYahXOIf8Q9Xb7GWm/HZNL7e2k3hU7MmNn/fmKlcTusFSTHVV4GKJsUuejdiwmODxvBXUQAnz5OUZG0AqKsUfY=
Received: from BL0PR12MB2468.namprd12.prod.outlook.com (52.132.30.157) by
 BL0PR12MB2548.namprd12.prod.outlook.com (52.132.29.11) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2387.24; Fri, 1 Nov 2019 17:33:30 +0000
Received: from BL0PR12MB2468.namprd12.prod.outlook.com
 ([fe80::748c:1f32:1a4d:acca]) by BL0PR12MB2468.namprd12.prod.outlook.com
 ([fe80::748c:1f32:1a4d:acca%7]) with mapi id 15.20.2387.028; Fri, 1 Nov 2019
 17:33:30 +0000
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
Subject: [PATCH 0/4] Emulate and enable UMIP feature on AMD
Thread-Topic: [PATCH 0/4] Emulate and enable UMIP feature on AMD
Thread-Index: AQHVkNp6yHzbr4SWxUqB/ZBcMwNDtg==
Date: Fri, 1 Nov 2019 17:33:30 +0000
Message-ID: <157262960837.2838.17520432516398899751.stgit@naples-babu.amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN6PR08CA0014.namprd08.prod.outlook.com
 (2603:10b6:805:66::27) To BL0PR12MB2468.namprd12.prod.outlook.com
 (2603:10b6:207:44::29)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.2]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: f572f14a-8a9c-43ec-d5af-08d75ef19caa
x-ms-traffictypediagnostic: BL0PR12MB2548:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <BL0PR12MB2548A0B54B7F58DAD0BA888995620@BL0PR12MB2548.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:6790;
x-forefront-prvs: 020877E0CB
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(366004)(396003)(376002)(39860400002)(136003)(346002)(189003)(199004)(66946007)(71190400001)(2501003)(2906002)(71200400001)(25786009)(14454004)(476003)(478600001)(2201001)(6116002)(3846002)(316002)(5660300002)(54906003)(86362001)(110136005)(4326008)(81156014)(64756008)(26005)(102836004)(66066001)(66446008)(7736002)(99286004)(305945005)(7416002)(8676002)(8936002)(186003)(66476007)(486006)(6486002)(6512007)(6506007)(386003)(66556008)(256004)(14444005)(6436002)(52116002)(103116003)(81166006)(921003)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:BL0PR12MB2548;H:BL0PR12MB2468.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 exGF2hbicJtOq3iGoqpHa0Z3kqNkBTcYWjIa5QrfK22Tb+7MUvIYDDXICOuJJfYuUC35u8hYBBEayUPjk1vuWB79xXzonNfM60uG6lTAqp/YK/M1pvhKBDbsvbpesXD8jhIV/NdYWq4DuG7jUEvBOSTB0plOMEYLgLh//BNjx0F/V3B50cgPGpEwUY0mpUnuouCBfqyEJXVEFJ4FKHULvtM3GB1JxI8lJPAno/pEXJSiofn6rPOH2vIwoAXWehcsTfhpKqrBJf2Gi0fC9ngB0XeJ3373LnGWNQn5er81vN+gpLP8xVQrsRola6zHSEEugQUBCZjW9jXXZAKJJTkRq3ZX6WCyA8rZ0GevqsOOw2qpRl72dMxY/iwmPmNfbRxF/oe0RnGSoTeoV29Ok9zYB5NmLIZGJysRirvHdMH+jKCu6AVxu4IkW/n6zBl2I/oZ
Content-ID: <490770091B2FFE4EBC0CB805FDA3B229@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f572f14a-8a9c-43ec-d5af-08d75ef19caa
X-MS-Exchange-CrossTenant-originalarrivaltime: 01 Nov 2019 17:33:30.6604
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 r07VneNFfItYXPv4qMi24Gx0i8AWgS+kKWEwypBuEV9jmcY8CEOkf2rxbXF66D/6
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL0PR12MB2548
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD 2nd generation EPYC processors support UMIP (User-Mode Instruction
Prevention) feature. Emulate and enable the UMIP feature if bare metal
supports it. Emulation of UMIP instructions (sgdt, sidt, sldt, smsw and
str) requires the hypervisor to read and write the guest memory. Guest
memory is encrypted on SEV guest. Hypervisor cannot successfully read or
write the guest memory. So disable emulation on SEV guest. Enable the
emulation only on non SEV guest.

Tested on EPYC/EPYC-Rome VMs and works as expected. Please review.

Babu Moger (4):
  kvm: x86: Dont set UMIP feature bit unconditionally
  kvm: svm: Enable UMIP feature on AMD
  kvm: svm: Emulate UMIP instructions on non SEV guest
  x86/Kconfig: Rename UMIP config parameter

 arch/x86/Kconfig                         |  8 +++----
 arch/x86/include/asm/disabled-features.h |  2 +-
 arch/x86/include/asm/umip.h              |  4 ++--
 arch/x86/kernel/Makefile                 |  2 +-
 arch/x86/kvm/cpuid.c                     |  2 +-
 arch/x86/kvm/svm.c                       | 30 ++++++++++++++++++++----
 6 files changed, 34 insertions(+), 14 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/2] Save/Restore clobbered register and
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Fri Nov  1 20:33:51 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11223651
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F18861599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 20:34:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CC25421897
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 20:34:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="YKBbLk4H"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727517AbfKAUeE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 16:34:04 -0400
Received: from mail-pl1-f201.google.com ([209.85.214.201]:48873 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726709AbfKAUeE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 16:34:04 -0400
Received: by mail-pl1-f201.google.com with SMTP id t5so5185119plz.15
        for <kvm@vger.kernel.org>; Fri, 01 Nov 2019 13:34:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=u69GTKH2Lgj0OCNQraYxlMapGuKtQ6srnxcY8D4YniI=;
        b=YKBbLk4HJOYCrCFNIhLudf9Q4IhgmYDQg1IVzhYl01ni3OmZVq7q7hDqSBKMRJ9jyF
         lzgxDFSRhG+/QR/gbceal0sqDz/XyTDNiWZbED7cD4W8qBImRpAPp5/W4InV3FN5MVin
         xrJrw3X4tq3iS/RSA6OhLUy5fb7zn5U3Duav16vwVoizc2MRCdQTGFj/yZoVuNjEaCZp
         a0U0lsAYiF+TlebAxeYdEEHzMyuxkmNIGY1+LIRTZcHa/HkQHnmsGNvQtgDuW2vA6LCC
         Lznk2GdeHy0h+b+LxDvwDbH+CDCNTU1xrofZ/eF4AI33fniNGla66nGNJp2HhIWA5Z4x
         2xrg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=u69GTKH2Lgj0OCNQraYxlMapGuKtQ6srnxcY8D4YniI=;
        b=Y5qOEeC5wrKKCM8TAPMPP98i6lRGN9CHWAn202UsrQmrCoJ5kAfl+yVsA+ufXwyVpa
         qevDGWkTSyhNv641sFLIyUGl/HGJTP9nA9Fim/CBoqcbtQNCIrLPQcDnpw54ZoTXvjil
         mUi+1cAYDhU4FL54dIKVntD1BcgzkTa7BeiwDRaJZxdTqHNyttrUQg9OStMXH6aYNW/1
         o99K6i+5yDdrGloDK0elGztsqPy5ftefje/30zUmQM+GBMh4IgsDK2INCPH47V5lX2yV
         WbpDVyRg8hzagPMoog0jiGje1UKaarxRoPjwUMR0w713Lj69FbqQ5JqilqgzJZSj97iT
         PpFA==
X-Gm-Message-State: APjAAAWaHSNJ5PJ+lsuM9iGfwDnsylC+p2wEXbhW0jFG3w38bhs9PSLn
        Ob4WV/FLtOIDw15XaNKtGRMJDbZYrFmWthwMZyPtwRSElfG0TKzyMaiBmcGS7UUNV4F4apyBXut
        M1VYmzASflOieNx5mjIUI+VqvClVhU2tqgG3qS+IWcs07KYC5zUXfQQ==
X-Google-Smtp-Source: 
 APXvYqyjrpMWmekN4aNjha/lRyASusKd5juhZOJGE3II7BwSUBaHgKXIRFuXLe4ETnxmKcT4reXYE7/jgw==
X-Received: by 2002:a63:ec4f:: with SMTP id r15mr15122319pgj.17.1572640442146;
 Fri, 01 Nov 2019 13:34:02 -0700 (PDT)
Date: Fri,  1 Nov 2019 13:33:51 -0700
Message-Id: <20191101203353.150049-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH v3 0/2] Save/Restore clobbered register and
 struct initialization
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, jmattson@google.com
Cc: thuth@redhat.com, alexandru.elisei@arm.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Some tests may clobber the %es register, causing problems later on.
- Many tests require a stack, but it's easy to forget to allocate one.
  Use an initialization function to set it automagically.

Bill Wendling (2):
  x86: realmode: save and restore %es
  x86: realmode: initialize inregs with a stack

 x86/realmode.c | 149 ++++++++++++++++++++++++++++++++++---------------
 1 file changed, 105 insertions(+), 44 deletions(-)
```
#### [PATCH v4 00/17] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
From patchwork Fri Nov  1 22:41:22 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Suthikulpanit,
 Suravee" <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11223901
Return-Path: <SRS0=M4X2=YZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E1A61599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 22:42:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62E58217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 Nov 2019 22:42:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="oQ5hDg90"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727728AbfKAWl1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 Nov 2019 18:41:27 -0400
Received: from mail-eopbgr720065.outbound.protection.outlook.com
 ([40.107.72.65]:49770
        "EHLO NAM05-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727029AbfKAWl1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 Nov 2019 18:41:27 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jOBb4F5gTdTHAeHvgDDJB4YJuF9u2NOsrPsC8X4tNqf3+QGrBAXkUTi9MOwl/1n2TuJmT+ugz8LN8Yoes95XW9bWZBk2tCfSrovcodSKnaiWy4CB2Xu1aGB9FPl0tizzJem5dOMfML+1XBUrovXntJM1G+TyzBgm0PTVmmx6VkDD8JISmguQ+N1Lo7k9iniP1XA0l3df0F0GUr+n/os4I9xpvcsfAlFQU1EP1maDOTBClnam9RHjZPb4W2frFgf7HLyE6wO6F3Y2l1E7CWVy+9U9i+Cbx502UZWHfbftN/pJviodwq+vqMWOB91QfujuDxNYBpFrD5Vho3Pd2yBZcw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pIpksEIacLQcGqwrLOjQ3oi61X6LlqCS4MXDFkZ6/VY=;
 b=Rb2DKFicP4vhZP/3S8dHzwmZtcbWpPF0UExAXsYRR8AGdQAKm24pn45Ro96ZLRjrG+pLVwv7ru/M3oR5TdYu/OeYEM3tEmoGlru8xU0hE5EbmhpGp82DxvIayuVtybSY/IxMK/q5VOIe+3iol97QSSSurrEBmBKOe//wPrnFUtPTIVX/6UkrfJevPYUd7LZmeNhBn1rof/Q4CARSXj5tM/ZMIxrDLuH1y2s3QRajJQ7s3M/+bFPfIpefJzi95TZdOt67y7eDISp+M2RGHkmS3BesB2dLU+X0rqWyzqvyqR78oWU1wPOGtupEZFWmuBRE3WNgjpdUHfXbpCV5tZ+/9g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pIpksEIacLQcGqwrLOjQ3oi61X6LlqCS4MXDFkZ6/VY=;
 b=oQ5hDg90jh0weV1wil8fusnbTs5IQD89lzlqqrVYXTCrOvBVdMXgpZz0gEJMVSRY9w5dKmG7qHIF1SqRLheDc2qATNX7eJC9QVru9oh1KwkHkyPT3dFx94qgkdWt8lfN/ui+7OhKaR0z5qSJ0XA62c2AQjC8z7QruXrVO/8J+Og=
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (10.255.173.210) by
 DM6PR12MB3243.namprd12.prod.outlook.com (20.179.105.155) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2408.24; Fri, 1 Nov 2019 22:41:22 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862%6]) with mapi id 15.20.2408.024; Fri, 1 Nov 2019
 22:41:22 +0000
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
Subject: [PATCH v4 00/17] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
 mode
Thread-Topic: [PATCH v4 00/17] kvm: x86: Support AMD SVM AVIC w/ in-kernel
 irqchip mode
Thread-Index: AQHVkQV87nIRXYvD70eAN6/11mAloQ==
Date: Fri, 1 Nov 2019 22:41:22 +0000
Message-ID: <1572648072-84536-1-git-send-email-suravee.suthikulpanit@amd.com>
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
x-ms-office365-filtering-correlation-id: c877bc34-4629-4515-59ad-08d75f1c9e9b
x-ms-traffictypediagnostic: DM6PR12MB3243:
x-ms-exchange-purlcount: 2
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB32439EBFBD7287903C409504F3620@DM6PR12MB3243.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:1247;
x-forefront-prvs: 020877E0CB
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(346002)(366004)(376002)(39860400002)(136003)(199004)(189003)(66476007)(66446008)(26005)(6506007)(386003)(86362001)(5660300002)(102836004)(4720700003)(305945005)(7736002)(7416002)(256004)(14444005)(8936002)(8676002)(186003)(52116002)(6486002)(478600001)(50226002)(71200400001)(71190400001)(81166006)(6436002)(476003)(6306002)(2906002)(3846002)(6116002)(6512007)(99286004)(4326008)(2616005)(316002)(486006)(81156014)(14454004)(66946007)(36756003)(110136005)(54906003)(66066001)(64756008)(66556008)(25786009)(2501003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3243;H:DM6PR12MB3865.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 bWiGoPPz+pIE1csKJ52L6oFgO8RAj+s5a6E5MrY7XPdXGmUEyPXacHXmIpuTJOTV9m4JD93YfYAr2Kl+nkbI48KuFvnlC0B2mccvRKO9OIXf5BzeIWfuyh54BB490xDf4EOz/ID5P5ojUmMlcVfOJlUM4Uk1l//PTDotVZa47UqzCYvWJcd4fsxieoU3zKY5BvNWZnIn8AeVCPOwyQ8hpbz92lU18hhBWUvUFx+KVCMKj5DHxOc8XaoSEq5eFFmZ6+Zw+3ysF2KJ1MeYb/7P/Tm4oChPx2PO5nDbVHAZMDIWpWxfBG8JfoFEM0ERc9phyKfFaykN3b90LeVvnyIsUxai8E/6DnO9/NOG4LtRu/uQtXv6AuNend0ou0o3EtrZBZphZUR+otlaAlNU+urfLRkvDSLc99XuTzCW+Fdnad+JBJ/r1/8vXinFENcQAHMPHsp6sPNA8nxaatqI5Yb4iMKmy69YMTlWstgvIerUSZU=
Content-ID: <EEEDE0C18170D54C80BC453F68451A6F@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c877bc34-4629-4515-59ad-08d75f1c9e9b
X-MS-Exchange-CrossTenant-originalarrivaltime: 01 Nov 2019 22:41:22.3257
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 D1BfOTxe7SrNjfaA0ZLQ+H1rZYU8FGZK7CipjLLlsrB56lnrIF5qqUHp2GcQcJDw7sy+FyAj7mi31QiDnzkeow==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3243
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'commit 67034bb9dd5e ("KVM: SVM: Add irqchip_split() checks before
enabling AVIC")' was introduced to fix miscellaneous boot-hang issues
when enable AVIC. This is mainly due to AVIC hardware doest not #vmexit
on write to LAPIC EOI register resulting in-kernel PIC and IOAPIC to
wait and do not inject new interrupts (e.g. PIT, RTC).

This limits AVIC to only work with kernel_irqchip=split mode, which is
not currently enabled by default, and also required user-space to
support split irqchip model, which might not be the case.

The goal of this series is to enable AVIC to work in both irqchip modes,
by allowing AVIC to be deactivated temporarily during runtime, and fallback
to legacy interrupt injection mode (w/ vINTR and interrupt windows)
when needed, and then re-enabled subsequently.

Similar approach is also used to handle Hyper-V SynIC in the
'commit 5c919412fe61 ("kvm/x86: Hyper-V synthetic interrupt controller")',
where APICv is permanently disabled at runtime (currently broken for
AVIC, and fixed by this series). 

This series contains serveral parts:
  * Part 1: patch 1,2
    Code clean up, refactor, and introduce helper funtions

  * Part 2: patch 3 
    Introduce APICv deactivate bits to keep track of APICv state 
    for each vm.
 
  * Part 3: patch 4-9
    Add support for activate/deactivate APICv at runtime

  * Part 4: patch 10-13:
    Add support various cases where APICv needs to be deactivated

  * Part 5: patch 14-16:
    Introduce in-kernel IOAPIC workaround for AVIC EOI

  * Part 6: path 17
    Allow enable AVIC w/ kernel_irqchip=on

Pre-requisite Patch:
  * commit b9c6ff94e43a ("iommu/amd: Re-factor guest virtual APIC (de-)activation code")
    (https://git.kernel.org/pub/scm/linux/kernel/git/joro/iommu.git/commit/
     ?h=next&id=b9c6ff94e43a0ee053e0c1d983fba1ac4953b762)

This series has been tested against v5.3 as following:
  * Booting Linux and Windows Server 2019 VMs upto 240 vcpus
    and FreeBSD upto 128 vcpus w/ qemu option "kernel-irqchip=on"
    and "-no-hpet".
  * Pass-through Intel 10GbE NIC and run netperf in the VM.

Changes from V3: (https://lkml.org/lkml/2019/9/13/871)
(Per Paolo comments) 
  * Replace struct kvm_vcpu with struct kvm in various interfaces
  * Replace KVM_REQ_APICV_ACTIVATE/DEACTIVATE with KVM_REQ_APICV_UPDATE request
  * Replace APICv state enum (introduced in V3) w/ deactivate bits to track APICv state
  * Remove kvm_apicv_eoi_accelerate() (introduced in V3)
  * Deactivate APICv when using PIT re-inject mode
  * Consolidate srcu_read_unlock/lock into svm_request_update_avic()

Suravee Suthikulpanit (17):
  kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter
  kvm: lapic: Introduce APICv update helper function
  kvm: x86: Introduce APICv deactivate bits
  kvm: x86: Add support for activate/de-activate APICv at runtime
  kvm: x86: Add APICv activate/deactivate request trace points
  kvm: x86: svm: Add support to activate/deactivate posted interrupts
  svm: Add support for setup/destroy virutal APIC backing page for AVIC
  kvm: x86: Introduce APICv pre-update hook
  svm: Add support for activate/deactivate AVIC at runtime
  kvm: x86: hyperv: Use APICv update request interface
  svm: Deactivate AVIC when launching guest with nested SVM support
  svm: Temporary deactivate AVIC during ExtINT handling
  kvm: i8254: Deactivate APICv when using in-kernel PIT re-injection mode.
  kvm: lapic: Clean up APIC predefined macros
  kvm: ioapic: Refactor kvm_ioapic_update_eoi()
  kvm: ioapic: Lazy update IOAPIC EOI
  svm: Allow AVIC with in-kernel irqchip mode

 arch/x86/include/asm/kvm_host.h |  18 ++++-
 arch/x86/kvm/hyperv.c           |   5 +-
 arch/x86/kvm/i8254.c            |  10 +++
 arch/x86/kvm/ioapic.c           | 149 +++++++++++++++++++++++++---------------
 arch/x86/kvm/lapic.c            |  35 ++++++----
 arch/x86/kvm/lapic.h            |   2 +
 arch/x86/kvm/svm.c              | 136 +++++++++++++++++++++++++++++++-----
 arch/x86/kvm/trace.h            |  19 +++++
 arch/x86/kvm/vmx/vmx.c          |   6 +-
 arch/x86/kvm/x86.c              |  61 +++++++++++++---
 10 files changed, 343 insertions(+), 98 deletions(-)
```
