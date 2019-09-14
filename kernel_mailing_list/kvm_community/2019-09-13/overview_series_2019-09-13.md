#### [kvm-unit-tests PATCH] x86: nVMX: Add tests of VMPTRLD and VMPTRST to MMIO addresses
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11143891
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 172A21395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 00:00:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EA76E208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 00:00:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727239AbfIMAAr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 20:00:47 -0400
Received: from mga06.intel.com ([134.134.136.31]:36785 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726516AbfIMAAr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 20:00:47 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Sep 2019 17:00:47 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,492,1559545200";
   d="scan'208";a="179517264"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga008.jf.intel.com with ESMTP; 12 Sep 2019 17:00:46 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org, Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Fuqian Huang <huangfq.daxian@gmail.com>
Subject: [kvm-unit-tests PATCH] x86: nVMX: Add tests of VMPTRLD and VMPTRST to
 MMIO addresses
Date: Thu, 12 Sep 2019 17:00:45 -0700
Message-Id: <20190913000045.19214-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM uses master abort semantics to handle MMIO accesses when emulating
VMX instructions.  Ensure this is the case, i.e. that KVM doesn't inject
a #PF, by emitting VMPTRLD and VMPTRST to the TXT private address space.

Use the TXT private space as the bogus MMIO address so that the tests
can also pass on bare metal.  If my recollection of TXT is correct,
accesses to private space when it is locked trigger master aborts.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Fuqian Huang <huangfq.daxian@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

This obviously assumes the associated KVM change[*] is applied.

[*] https://lkml.kernel.org/r/20190912235603.18954-1-sean.j.christopherson@intel.com

 x86/vmx.c | 15 +++++++++++++++
 x86/vmx.h | 20 ++++++++++++++++++++
 2 files changed, 35 insertions(+)

```
#### [PATCH 01/11] KVM: x86/mmu: Reintroduce fast invalidate/zap for flushing memslot
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11143945
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47C481395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 02:47:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2556320856
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 02:47:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726899AbfIMCqP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 22:46:15 -0400
Received: from mga07.intel.com ([134.134.136.100]:58605 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726647AbfIMCqP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 22:46:15 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Sep 2019 19:46:13 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,492,1559545200";
   d="scan'208";a="176159503"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga007.jf.intel.com with ESMTP; 12 Sep 2019 19:46:13 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        James Harvey <jamespharvey20@gmail.com>,
        Alex Willamson <alex.williamson@redhat.com>
Subject: [PATCH 01/11] KVM: x86/mmu: Reintroduce fast invalidate/zap for
 flushing memslot
Date: Thu, 12 Sep 2019 19:46:02 -0700
Message-Id: <20190913024612.28392-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190913024612.28392-1-sean.j.christopherson@intel.com>
References: <20190913024612.28392-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reintroduce the fast invalidate mechanism and use it when zapping shadow
pages in response to a memslot being deleted/moved.  Using the fast
mechanism fixes a livelock reported by James Harvey that was introduced
by commit d012a06ab1d23 ("Revert "KVM: x86/mmu: Zap only the relevant
pages when removing a memslot"").

The livelock occurs because kvm_mmu_zap_all() as it exists today will
voluntarily reschedule and drop KVM's mmu_lock, which allows other vCPUs
to add shadow pages.  With enough vCPUs, kvm_mmu_zap_all() can get stuck
in an infinite loop as it can never zap all pages before observing lock
contention or the need to reschedule.

The equivalent of kvm_mmu_zap_all() that was in use at the time of
the reverted commit (4e103134b8623, "KVM: x86/mmu: Zap only the relevant
pages when removing a memslot") employed a fast invalidate mechanism and
was not susceptible to the above livelock.  Restore the fast invalidate
code and use it when flushing a memslot.

Reverting the revert (commit d012a06ab1d23) is not a viable option as
the revert is needed to fix a regression that occurs when the guest has
one or more assigned devices.

Alternatively, the livelock could be eliminated by removing the
conditional reschedule from kvm_mmu_zap_all().  However, although
removing the reschedule would be a smaller code change, it's less safe
in the sense that the resulting kvm_mmu_zap_all() hasn't been used in
the wild for flushing memslots since the fast invalidate mechanism was
introduced by commit 6ca18b6950f8d ("KVM: x86: use the fast way to
invalidate all pages"), back in 2013.

For all intents and purposes, this is a revert of commit ea145aacf4ae8
("Revert "KVM: MMU: fast invalidate all pages"") and a partial revert of
commit 7390de1e99a70 ("Revert "KVM: x86: use the fast way to invalidate
all pages""), i.e. restores the behavior of commit 5304b8d37c2a5 ("KVM:
MMU: fast invalidate all pages") and commit 6ca18b6950f8d ("KVM: x86:
use the fast way to invalidate all pages") respectively.

Fixes: d012a06ab1d23 ("Revert "KVM: x86/mmu: Zap only the relevant pages when removing a memslot"")
Reported-by: James Harvey <jamespharvey20@gmail.com>
Cc: Alex Willamson <alex.williamson@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   2 +
 arch/x86/kvm/mmu.c              | 101 +++++++++++++++++++++++++++++++-
 2 files changed, 101 insertions(+), 2 deletions(-)

```
#### [PATCH v3 01/16] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Suthikulpanit,
 Suravee" <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11145141
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C308017E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 19:01:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9752E214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 19:01:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="qI2CN9TN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730176AbfIMTAy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Sep 2019 15:00:54 -0400
Received: from mail-eopbgr820057.outbound.protection.outlook.com
 ([40.107.82.57]:58712
        "EHLO NAM01-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726822AbfIMTAx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Sep 2019 15:00:53 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FRgf+FwqXJutSahBmus5EB5PCZK/cJa0kevWUSliT9oPu1uguaLvV5FoBlW+iEN//ubescb/BDqGsRsY9tFQ1eeQ/OvgacJWmbDpVUnTom+WD8DC46gnQu5iodtHlF3V7xfqjRHB14wOpiR/HyRo8iedIDMoeiYJyfeeB36U90sghAX5G2Bb1WjCf+iNYssZw0/cuMhRA/GYWzZn0xSR1eVCC+dXOgmsPChVLrq6dXRD/jSKqKtV4uSs8qe6VJFM+gfbmp6hYuqkNqCCGjlpwYngcxb9gQUVS8KZVMGVyOwQZ/cpM6Ww6ylXLrc+RX/kxCJd5nNuU9wnwndrsf9vUg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uBKR6fjUDwmwqUmuqzblcx4wmgdgaNGRnVZE7ekQnMw=;
 b=gSWQRon9cIj6i0dX9JcCDp5UEWy2ONZ6ccTZVsEMDvsOfujLDcY0vsSj/fdwAGiB/egcxCUNr4q6UQQ84ZCn0xDI7cAxnlMlGh6XzZW/2qEU9CBUHaJAm2CRVSbTnReD6rpcfRfFLhZvXvJIFnnEJQWEHUiwb5JOxlLqBdyIhu/X/XpEgsywFT9joM7tQf5sMrLndcv3l5B0FD0ywF5XrRZbfgMAsXuDZTt+Pi8t8F791UTPkU3dvtf9v5mLkR/+Eov0Ghe4Gl2+u+1RWuuStD1mqmuUL7z+eGPULutKYqPWaNgRbNjEQ+dVgbbQiZUIf6Ei3RiyfZdnzV5LKFuypw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=uBKR6fjUDwmwqUmuqzblcx4wmgdgaNGRnVZE7ekQnMw=;
 b=qI2CN9TN8n87u1BWzt9LeXbscosKQyU5rkPucFpsyjKs8EXOH3F4kDc/gS5DhapuuO3uNJhtVkxfK4RVZXDcu3n7bazERN5M/OQDnZu9N0YtZAu+0XRIfwyWK1gByroUeeaovopZWT4+n2sJDEXHQzb8LwNse8oB3N1YmrHj28U=
Received: from DM6PR12MB2844.namprd12.prod.outlook.com (20.176.117.96) by
 DM6PR12MB3804.namprd12.prod.outlook.com (10.255.173.29) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2241.20; Fri, 13 Sep 2019 19:00:50 +0000
Received: from DM6PR12MB2844.namprd12.prod.outlook.com
 ([fe80::201f:ac0f:4576:e997]) by DM6PR12MB2844.namprd12.prod.outlook.com
 ([fe80::201f:ac0f:4576:e997%3]) with mapi id 15.20.2241.022; Fri, 13 Sep 2019
 19:00:49 +0000
From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
CC: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "graf@amazon.com" <graf@amazon.com>,
        "jschoenh@amazon.de" <jschoenh@amazon.de>,
        "karahmed@amazon.de" <karahmed@amazon.de>,
        "rimasluk@amazon.com" <rimasluk@amazon.com>,
        "Grimm, Jon" <Jon.Grimm@amd.com>,
        "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>
Subject: [PATCH v3 01/16] kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to
 use struct kvm parameter
Thread-Topic: [PATCH v3 01/16] kvm: x86: Modify kvm_x86_ops.get_enable_apicv()
 to use struct kvm parameter
Thread-Index: AQHVamWOE6Ykw4M51kipY51rilxC+w==
Date: Fri, 13 Sep 2019 19:00:49 +0000
Message-ID: <1568401242-260374-2-git-send-email-suravee.suthikulpanit@amd.com>
References: <1568401242-260374-1-git-send-email-suravee.suthikulpanit@amd.com>
In-Reply-To: 
 <1568401242-260374-1-git-send-email-suravee.suthikulpanit@amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [165.204.78.1]
x-clientproxiedby: SN6PR08CA0021.namprd08.prod.outlook.com
 (2603:10b6:805:66::34) To DM6PR12MB2844.namprd12.prod.outlook.com
 (2603:10b6:5:45::32)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 1.8.3.1
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 2e470d3f-3a5a-4311-84b4-08d7387cb117
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(5600166)(711020)(4605104)(1401327)(4618075)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(2017052603328)(7193020);SRVR:DM6PR12MB3804;
x-ms-traffictypediagnostic: DM6PR12MB3804:
x-ld-processed: 3dd8961f-e488-4e60-8e11-a82d994e183d,ExtAddr
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB3804F36D7179E47C048AAA2BF3B30@DM6PR12MB3804.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:2582;
x-forefront-prvs: 0159AC2B97
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(376002)(346002)(136003)(396003)(39860400002)(366004)(189003)(199004)(6436002)(6512007)(478600001)(6486002)(7416002)(53936002)(2906002)(4326008)(6116002)(3846002)(25786009)(86362001)(99286004)(66946007)(446003)(64756008)(66446008)(36756003)(486006)(71190400001)(71200400001)(52116002)(66556008)(256004)(4720700003)(2616005)(476003)(11346002)(14444005)(102836004)(305945005)(14454004)(7736002)(316002)(50226002)(386003)(6506007)(26005)(2501003)(8936002)(66066001)(8676002)(186003)(81156014)(81166006)(110136005)(5660300002)(76176011)(54906003)(66476007);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3804;H:DM6PR12MB2844.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 yjdseO/Eh4VW/ZtXjgP2U5/islmU8T7BMac77Bi2rybaUNE251SSgS012JOwYWckVlx6GTEYZq+l2I7/cznIRpsXaRm2Lx/GTCbqTu+ZFgMdjU3nErnLV4K2t5BNc0nqFQU2ptLbGYzlAAgbQXw9z99Qb5DYKh3RJw2x72CMnTaRDwolTt1f6LQGuUX09QZdZ3tWw5hCzuoiltf3XS/2H54ArrQ0i4UCM1ALrygnvxERswYktPTOIlexezLJenvgDVwC0XijfYfUMAH3jeiTqRjoTZO7qojblAz8ffiTWgyd/YfsGncD1M1j1uWpzTpFgeceRFMOUijG3LKyMHXB92O9DMk16+SN/Ea41ot8hjQju7jc6DPS4PvpO4PR78xq3ag0aFgWXCVQeBmuiSrTOHDIS5wvPZlUVZADA3hlk64=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2e470d3f-3a5a-4311-84b4-08d7387cb117
X-MS-Exchange-CrossTenant-originalarrivaltime: 13 Sep 2019 19:00:49.7091
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 FX6o7f4Aw4jilNaUYL3XUNqL7gIuVobNfkSWSuuT8d8pXbFuIvM4kY0aDG5A6IJ9xar5OvDGpiv+8h6PKqJfcg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3804
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
#### [PATCH v6 01/10] s390: vfio-ap: Refactor vfio_ap driver probe and remove callbacks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11145327
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24A4D13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 21:27:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07DA321479
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 21:27:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390012AbfIMV1K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Sep 2019 17:27:10 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:1796 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389898AbfIMV1J (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Sep 2019 17:27:09 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8DLGs1o146668;
        Fri, 13 Sep 2019 17:27:07 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uytca4s7h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 17:27:07 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.27/8.16.0.27) with SMTP id x8DLGuPV146786;
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uytca4s73-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8DLK8wk024295;
        Fri, 13 Sep 2019 21:27:05 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma05wdc.us.ibm.com with ESMTP id 2uytdx9xdv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 21:27:05 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id x8DLR3cV35586394
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 13 Sep 2019 21:27:04 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D05332805C;
        Fri, 13 Sep 2019 21:27:03 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5156728059;
        Fri, 13 Sep 2019 21:27:03 +0000 (GMT)
Received: from akrowiak-ThinkPad-P50.ibm.com (unknown [9.85.152.57])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTPS;
        Fri, 13 Sep 2019 21:27:03 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pmorel@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        jjherne@linux.ibm.com, Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v6 01/10] s390: vfio-ap: Refactor vfio_ap driver probe and
 remove callbacks
Date: Fri, 13 Sep 2019 17:26:49 -0400
Message-Id: <1568410018-10833-2-git-send-email-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1568410018-10833-1-git-send-email-akrowiak@linux.ibm.com>
References: <1568410018-10833-1-git-send-email-akrowiak@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-13_10:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=2 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909130213
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to limit the number of private mdev functions called from the
vfio_ap device driver as well as to provide a landing spot for dynamic
configuration code related to binding/unbinding AP queue devices to/from
the vfio_ap driver, the following changes are being introduced:

* Move code from the vfio_ap driver's probe callback into a function
  defined in the mdev private operations file.

* Move code from the vfio_ap driver's remove callback into a function
  defined in the mdev private operations file.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 23 +++--------
 drivers/s390/crypto/vfio_ap_ops.c     | 74 ++++++++++++++++++++++++++++++-----
 drivers/s390/crypto/vfio_ap_private.h |  6 +--
 3 files changed, 72 insertions(+), 31 deletions(-)

```
#### [PATCH v2] KVM: x86: Handle unexpected MMIO accesses using master abort semantics
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11143921
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E0F5E1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 01:56:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BFB50206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 01:56:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726918AbfIMB4Z (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 21:56:25 -0400
Received: from mga03.intel.com ([134.134.136.65]:2948 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726262AbfIMB4Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 21:56:24 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Sep 2019 18:56:24 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,489,1559545200";
   d="scan'208";a="336761100"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga004.jf.intel.com with ESMTP; 12 Sep 2019 18:56:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Fuqian Huang <huangfq.daxian@gmail.com>
Subject: [PATCH v2] KVM: x86: Handle unexpected MMIO accesses using master
 abort semantics
Date: Thu, 12 Sep 2019 18:56:23 -0700
Message-Id: <20190913015623.19869-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use master abort semantics, i.e. reads return all ones and writes are
dropped, to handle unexpected MMIO accesses when reading guest memory
instead of returning X86EMUL_IO_NEEDED, which in turn gets interpreted
as a guest page fault.

Emulation of certain instructions, notably VMX instructions, involves
reading or writing guest memory without going through the emulator.
These emulation flows are not equipped to handle MMIO accesses as no
sane and properly functioning guest kernel will target MMIO with such
instructions, and so simply inject a page fault in response to
X86EMUL_IO_NEEDED.

While not 100% correct, using master abort semantics is at least
sometimes correct, e.g. non-existent MMIO accesses do actually master
abort, whereas injecting a page fault is always wrong, i.e. the issue
lies in the physical address domain, not in the virtual to physical
translation.

Apply the logic to kvm_write_guest_virt_system() in addition to
replacing existing #PF logic in kvm_read_guest_virt(), as VMPTRST uses
the former, i.e. can also leak a host stack address.

Reported-by: Fuqian Huang <huangfq.daxian@gmail.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2: Fix the comment for kvm_read_guest_virt_helper().

 arch/x86/kvm/x86.c | 40 +++++++++++++++++++++++++++++++---------
 1 file changed, 31 insertions(+), 9 deletions(-)

```
