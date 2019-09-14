

#### [PATCH 00/11] KVM: x86/mmu: Restore fast invalidate/zap flow
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Sep 13 02:46:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11143947
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1EA71395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 02:47:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C8CED2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 02:47:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728312AbfIMCrG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Sep 2019 22:47:06 -0400
Received: from mga07.intel.com ([134.134.136.100]:58608 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726032AbfIMCqP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Sep 2019 22:46:15 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Sep 2019 19:46:13 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,492,1559545200";
   d="scan'208";a="176159501"
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
Subject: [PATCH 00/11] KVM: x86/mmu: Restore fast invalidate/zap flow
Date: Thu, 12 Sep 2019 19:46:01 -0700
Message-Id: <20190913024612.28392-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Restore the fast invalidate flow for zapping shadow pages and use it
whenever vCPUs can be active in the VM.  This fixes (in theory, not yet
confirmed) a regression reported by James Harvey where KVM can livelock
in kvm_mmu_zap_all() when it's invoked in response to a memslot update.

The fast invalidate flow was removed as it was deemed to be unnecessary
after its primary user, memslot flushing, was reworked to zap only the
memslot in question instead of all shadow pages.  Unfortunately, zapping
only the memslot being (re)moved during a memslot update introduced a
regression for VMs with assigned devices.  Because we could not discern
why zapping only the relevant memslot broke device assignment, or if the
regression extended beyond device assignment, we reverted to zapping all
shadow pages when a memslot is (re)moved.

The revert to "zap all" failed to account for subsequent changes that
have been made to kvm_mmu_zap_all() between then and now.  Specifically,
kvm_mmu_zap_all() now conditionally drops reschedules and drops mmu_lock
if a reschedule is needed or if the lock is contended.  Dropping the lock
allows other vCPUs to add shadow pages, and, with enough vCPUs, can cause
kvm_mmu_zap_all() to get stuck in an infinite loop as it can never zap all
pages before observing lock contention or the need to reschedule.

The reasoning behind having kvm_mmu_zap_all() conditionally reschedule was
that it would only be used when the VM is inaccesible, e.g. when its
mm_struct is dying or when the VM itself is being destroyed.  In that case,
playing nice with the rest of the kernel instead of hogging cycles to free
unused shadow pages made sense.

Since it's unlikely we'll root cause the device assignment regression any
time soon, and that simply removing the conditional rescheduling isn't
guaranteed to return us to a known good state, restore the fast invalidate
flow for zapping on memslot updates, including mmio generation wraparound.
Opportunisticaly tack on a bug fix and a couple enhancements.

Alex and James, it probably goes without saying... please test, especially
patch 01/11 as a standalone patch as that'll likely need to be applied to
stable branches, assuming it works.  Thanks!

Sean Christopherson (11):
  KVM: x86/mmu: Reintroduce fast invalidate/zap for flushing memslot
  KVM: x86/mmu: Treat invalid shadow pages as obsolete
  KVM: x86/mmu: Use fast invalidate mechanism to zap MMIO sptes
  KVM: x86/mmu: Revert "Revert "KVM: MMU: show mmu_valid_gen in shadow
    page related tracepoints""
  KVM: x86/mmu: Revert "Revert "KVM: MMU: add tracepoint for
    kvm_mmu_invalidate_all_pages""
  KVM: x86/mmu: Revert "Revert "KVM: MMU: zap pages in batch""
  KVM: x86/mmu: Revert "Revert "KVM: MMU: collapse TLB flushes when zap
    all pages""
  KVM: x86/mmu: Revert "Revert "KVM: MMU: reclaim the zapped-obsolete
    page first""
  KVM: x86/mmu: Revert "KVM: x86/mmu: Remove is_obsolete() call"
  KVM: x86/mmu: Explicitly track only a single invalid mmu generation
  KVM: x86/mmu: Skip invalid pages during zapping iff root_count is zero

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/mmu.c              | 154 ++++++++++++++++++++++++++++----
 arch/x86/kvm/mmutrace.h         |  42 +++++++--
 arch/x86/kvm/x86.c              |   1 +
 4 files changed, 173 insertions(+), 28 deletions(-)
```
#### [PATCH v3 00/16] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
From patchwork Fri Sep 13 19:00:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Suthikulpanit,
 Suravee" <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11145131
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3AEF17E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 19:01:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A688520CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 19:01:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="dImAT+oy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388321AbfIMTAz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Sep 2019 15:00:55 -0400
Received: from mail-eopbgr820057.outbound.protection.outlook.com
 ([40.107.82.57]:58712
        "EHLO NAM01-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1730118AbfIMTAy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Sep 2019 15:00:54 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=j+bqGlrTS7eVs6ewi/IOHz/O1sBoeY9ehwqwXySMSqGR3NH+tahhC9ClyEdFQAF1tEQuLdbB8PAhDW8eJht4FfH46LF9p8UKija1NBtFcmbiVzNWEjwDNJ8usGklUcdi2jiamjpDD67fNAlO208tOWGLVCdNaQ4a1toFQvSaLUXAc9T0CKAwYehZwkH9hJVqiRq8iLQ/WAFbTon7+n1biVYM99frkgqMCvSyNuJtprIqdJVs/B87lco2lamrQ8Xbt47BRyJr7ukFM5QFV+kp/2x9SiATcbLG4d9V/9fTllYYllgAslDcgcWXPbGHGztWmMGnawGK87nbfEtSzk+CAQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LJjg+xGFnIZYniI7cQgYICURDGNtboMJYL34yLv3hK8=;
 b=dijOuncCILBuIJdBMCaBf0HIVaUU4pdKtpuLP4SRibu48NQYeUSsil9cNJKjEd5RcmA1XTIT8F0cXJoa2hv0x++k3SX2K9ZBdIZd8EYZoAFGoI39YjiLFeC9+ffAOQk15s62XQq0JPU6InfuofNG+zFXcagjgdx8FvorvcHQ+WgnKRgU+zZP/JZARPHV6RTF3D1k+m+MqM8v9lEWZ3tTgdpvF6Nrz/yFlA+N4DjI8hgTr3pwrLlB9lYJkcrMMb8DQfWgoSpy3m+1TQ5XHrAeKA4MCxABUcDoTarZueuEk+PB+GM+vHok7m00MpPWGKA+8ac3OFHWCx+2nJxwPa7x8w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=LJjg+xGFnIZYniI7cQgYICURDGNtboMJYL34yLv3hK8=;
 b=dImAT+oySwlrcmfQSr9ZOK4Bmg5SKukutShRUtdXHsWPNkCEWajDY3Jc7KYwnQ1rVpB2GqnMflyfv4wcEkMfRlkvENxT3MoCX0EJpuERrQtlr35HYvTloTC/WxSKq6VRi4GvtWdNco3opn/QMFyW0H7J+uasM+gjV7RkRvL/umI=
Received: from DM6PR12MB2844.namprd12.prod.outlook.com (20.176.117.96) by
 DM6PR12MB3804.namprd12.prod.outlook.com (10.255.173.29) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2241.20; Fri, 13 Sep 2019 19:00:48 +0000
Received: from DM6PR12MB2844.namprd12.prod.outlook.com
 ([fe80::201f:ac0f:4576:e997]) by DM6PR12MB2844.namprd12.prod.outlook.com
 ([fe80::201f:ac0f:4576:e997%3]) with mapi id 15.20.2241.022; Fri, 13 Sep 2019
 19:00:48 +0000
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
Subject: [PATCH v3 00/16] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
 mode
Thread-Topic: [PATCH v3 00/16] kvm: x86: Support AMD SVM AVIC w/ in-kernel
 irqchip mode
Thread-Index: AQHVamWNwMSOXdHv0kO89gBM6mvXdw==
Date: Fri, 13 Sep 2019 19:00:48 +0000
Message-ID: <1568401242-260374-1-git-send-email-suravee.suthikulpanit@amd.com>
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
x-ms-office365-filtering-correlation-id: d8199909-0bdf-4683-f638-08d7387cb050
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(5600166)(711020)(4605104)(1401327)(4618075)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(2017052603328)(7193020);SRVR:DM6PR12MB3804;
x-ms-traffictypediagnostic: DM6PR12MB3804:
x-ms-exchange-purlcount: 3
x-ld-processed: 3dd8961f-e488-4e60-8e11-a82d994e183d,ExtAddr
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB38048A0D64F0DD15139E4836F3B30@DM6PR12MB3804.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:1247;
x-forefront-prvs: 0159AC2B97
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(376002)(346002)(136003)(396003)(39860400002)(366004)(189003)(199004)(6436002)(6512007)(478600001)(6486002)(7416002)(53936002)(2906002)(4326008)(6116002)(3846002)(25786009)(86362001)(6306002)(99286004)(66946007)(64756008)(66446008)(36756003)(486006)(71190400001)(71200400001)(52116002)(66556008)(256004)(4720700003)(2616005)(476003)(14444005)(102836004)(305945005)(14454004)(7736002)(316002)(50226002)(386003)(6506007)(26005)(2501003)(8936002)(66066001)(8676002)(186003)(81156014)(81166006)(110136005)(5660300002)(54906003)(66476007);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3804;H:DM6PR12MB2844.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 wMhkL0YQIemWGVFst6FvkDOkaPcl4ou3B4/iR3qdXRukgheEZBxUp3x4IPgg9OtjgbXNRZK73NxQvN+kRp2BUCWqA/3QRijV70yGgviK1WnoLW1e5aB4RdqDh98cixzniXy/fX0FIW09kH+wsiU4hw4wVO4caZ727qNyymFBbxnT6/G/+YztiNRITIfxiAUxaJ9hPzo8Uy6QPAqAFFaJ+8cvIjnLbI4KpqL4OW+mYcGcMqNgfAXXDrSDV4uwnJIak5U7X7qNHC7OdgbabxaITqQKFHoub4pzSZGoK1RK9mmGPpsns3s8XITBojNY1FVJWsexjt0ezUuJ8PL3NdQrXQVFi04CGXuva2SchEoI85gTJnVp7jT+6CK0OtxA+p6pk31WH2D2i5y1vYQU/3vDbsGLr4tJJ2si3m56p4BF+XQ=
Content-Type: text/plain; charset="utf-8"
Content-ID: <42AC8A303734644DB7BD6EE5EC84398D@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d8199909-0bdf-4683-f638-08d7387cb050
X-MS-Exchange-CrossTenant-originalarrivaltime: 13 Sep 2019 19:00:48.5218
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 gRKjhRsym7LB/fJsqSv01WSIRenwql7VPTm4pPbxE5FYWyo1MlplZX+bfaw++jJaq2XHXN8+O0Ym8DQfUshNPA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3804
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

This series contains three parts:
  * Part 1: patch 1-2
    Introduce APICv state enum and logic for keeping track of the state
    for each vm.
 
  * Part 2: patch 3-11
    Add support for activate/deactivate APICv at runtime

  * Part 3: patch 12-16:
    Provide workaround for AVIC EOI and allow enable AVIC w/
    kernel_irqchip=on

Pre-requisite Patch:
  * commit b9c6ff94e43a ("iommu/amd: Re-factor guest virtual APIC
    (de-)activation code")
    (https://git.kernel.org/pub/scm/linux/kernel/git/joro/iommu.git/commit/
     ?h=next&id=b9c6ff94e43a0ee053e0c1d983fba1ac4953b762)

This series has been tested against v5.3-rc5 as following:
  * Booting Linux and Windows Server 2019 VMs upto 240 vcpus
    and FreeBSD upto 128 vcpus w/ qemu option "kernel-irqchip=on"
    and "-no-hpet".
  * Pass-through Intel 10GbE NIC and run netperf in the VM.

Changes from V2: (https://lkml.org/lkml/2019/8/15/672)
  * Rebase to v5.3-rc5
  * Misc changes recommended by Alex and Vitaly.
  * Rename APICV_DEACTIVATED to APICV_SUSPENDED
  * Disable AVIC when guest booting w/ SVM support since AVIC
    does not currently support guest w/ nested virt.
  * Add tracepoint for APICV activate/deactivate request. (per Alex)
  * Consolidate changes for handling EOI for kvm PIT emulation and
    IOAPIC RTC handling in V2 into ioapic_lazy_update_eoi() in
    patch 17/18 of v3 serie.
  * Remove patches for providing per-vm apicv_state debug information.

Changes from V1: (https://lkml.org/lkml/2019/3/22/1042)
  * Introduce APICv state enumeration
  * Introduce KVM debugfs for APICv state
  * Add synchronization logic for APICv state to prevent potential
    race condition (per Jan's suggestion)
  * Add support for activate/deactivate posted interrupt
    (per Jan's suggestion)
  * Remove callback functions for handling APIC ID, DFR and LDR update
    (per Paolo's suggestion)
  * Add workaround for handling EOI for in-kernel PIT and IOAPIC.

Suravee Suthikulpanit (16):
  kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm
    parameter
  kvm: x86: Introduce KVM APICv state
  kvm: lapic: Introduce APICv update helper function
  kvm: x86: Add support for activate/de-activate APICv at runtime
  kvm: x86: Add APICv activate/deactivate request trace points
  kvm: x86: svm: Add support to activate/deactivate posted interrupts
  svm: Add support for setup/destroy virutal APIC backing page for AVIC
  svm: Add support for activate/deactivate AVIC at runtime
  kvm: x86: hyperv: Use APICv deactivate request interface
  svm: Disable AVIC when launching guest with SVM support
  svm: Temporary deactivate AVIC during ExtINT handling
  kvm: x86: Introduce struct kvm_x86_ops.apicv_eoi_accelerate
  kvm: lapic: Clean up APIC predefined macros
  kvm: ioapic: Refactor kvm_ioapic_update_eoi()
  kvm: x86: ioapic: Lazy update IOAPIC EOI
  svm: Allow AVIC with in-kernel irqchip mode

 arch/x86/include/asm/kvm_host.h |  28 +++++-
 arch/x86/kvm/hyperv.c           |  12 ++-
 arch/x86/kvm/ioapic.c           | 149 +++++++++++++++++++-----------
 arch/x86/kvm/lapic.c            |  35 ++++---
 arch/x86/kvm/lapic.h            |   2 +
 arch/x86/kvm/svm.c              | 198 +++++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/trace.h            |  30 ++++++
 arch/x86/kvm/vmx/vmx.c          |   2 +-
 arch/x86/kvm/x86.c              | 136 ++++++++++++++++++++++++++-
 9 files changed, 506 insertions(+), 86 deletions(-)
```
#### [PATCH v6 00/10] s390: vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Fri Sep 13 21:26:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11145333
Return-Path: <SRS0=Ziz+=XI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 30BDB13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 21:28:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0933020650
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 13 Sep 2019 21:28:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389855AbfIMV1I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 13 Sep 2019 17:27:08 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:42064 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387554AbfIMV1I (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 13 Sep 2019 17:27:08 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8DLGuVw056454;
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v0ghxvwe7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.27/8.16.0.27) with SMTP id x8DLR6FZ076030;
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v0ghxvwdp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 17:27:06 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8DLK9a9017561;
        Fri, 13 Sep 2019 21:27:05 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma02wdc.us.ibm.com with ESMTP id 2uytdx9wf9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 13 Sep 2019 21:27:05 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id x8DLR3Zp53412204
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 13 Sep 2019 21:27:03 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A91C2805C;
        Fri, 13 Sep 2019 21:27:03 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ADE6028058;
        Fri, 13 Sep 2019 21:27:02 +0000 (GMT)
Received: from akrowiak-ThinkPad-P50.ibm.com (unknown [9.85.152.57])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTPS;
        Fri, 13 Sep 2019 21:27:02 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pmorel@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        jjherne@linux.ibm.com, Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v6 00/10] s390: vfio-ap: dynamic configuration support
Date: Fri, 13 Sep 2019 17:26:48 -0400
Message-Id: <1568410018-10833-1-git-send-email-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.7.4
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-13_10:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1011 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909130213
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in three deficiencies
this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP configuration
   becomes available to the guest when it is subsequently restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to either
   mask can result in AP queue devices being unbound from the vfio_ap
   device driver and bound to a zcrypt device driver even if a guest is
   using the queues, thus giving the host access to the guest's private
   crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. 

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement more
of the AP architecture:

1. A root user will be prevented from making changes to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the ownership of an APQN
   changes from the vfio_ap device driver to a zcrypt driver when the APQN
   is assigned to a matrix mdev.

2. The sysfs bind/unbind interfaces will be disabled for the vfio_ap
   device driver.

3. Allow AP resources to be assigned to or removed from a matrix mdev
   while a guest is using it and hot plug the resource into or hot unplug
   the resource from the running guest.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if it
   results in assignment of an APQN that does not reference an AP queue
   device bound to the vfio_ap device driver, as long as the APQN is owned
   by the vfio_ap driver. Allowing over-provisioning of AP resources
   better models the architecture which does not preclude assigning AP
   resources that are not yet available in the system. If/when the queue
   becomes available to the host, it will immediately also become available
   to the guest.

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for disabling bind/unbind interfaces for vfio_ap driver:
-----------------------------------------------------------------
By disabling the bind/unbind interfaces for the vfio_ap device driver, 
the user is forced to use the AP bus's apmask/aqmask interfaces to control
the probing and removing of AP queues. There are two primary reasons for
disabling the bind/unbind interfaces for the vfio_ap device driver:

* The device architecture does not provide a means to prevent unbinding
  a device from a device driver, so an AP queue device can be unbound
  from the vfio_ap driver even when the queue is in use by a guest. By
  disabling the unbind interface, the user is forced to use the AP bus's
  apmask/aqmask interfaces which will prevent this.

* Binding of AP queues is controlled by the AP bus /sys/bus/ap/apmask and
  /sys/bus/ap/aqmask interfaces. If the masks indicate that an APQN is
  owned by zcrypt, trying to bind it to the vfio_ap device driver will
  fail; therefore, the bind interface is somewhat redundant and certainly
  unnecessary.        
  
3. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes 
reconfiguring a guest's AP matrix much less disruptive.

4. Rationale for allowing over-provisioning of AP resources:
----------------------------------------------------------- 
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will automatically acquire access to it. If an APQN
is dynamically unassigned from the underlying host system, it will 
automatically become unavailable to the guest.

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5 
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed. 

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2.  

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (10):
  s390: vfio-ap: Refactor vfio_ap driver probe and remove callbacks
  s390: vfio-ap: allow assignment of unavailable AP resources to mdev
    device
  s390: vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390: vfio-ap: filter CRYCB bits for unavailable queue devices
  s390: vfio-ap: sysfs attribute to display the guest CRYCB
  s390: vfio-ap: update guest CRYCB in vfio_ap probe and remove
    callbacks
  s390: zcrypt: driver callback to indicate resource in use
  s390: vfio-ap: implement in-use callback for vfio_ap driver
  s390: vfio-ap: added versioning to vfio_ap module
  s390: vfio-ap: update documentation

 Documentation/s390/vfio-ap.rst        | 899 +++++++++++++++++++++++++---------
 drivers/s390/crypto/ap_bus.c          | 144 +++++-
 drivers/s390/crypto/ap_bus.h          |   4 +
 drivers/s390/crypto/vfio_ap_drv.c     |  27 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 610 ++++++++++++++---------
 drivers/s390/crypto/vfio_ap_private.h |  12 +-
 6 files changed, 1200 insertions(+), 496 deletions(-)
```
