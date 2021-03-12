#### [PATCH v3 03/25] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12130069
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4230C433E9
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 02:02:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C0A464FCD
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 02:02:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229712AbhCKCC0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 21:02:26 -0500
Received: from mga03.intel.com ([134.134.136.65]:17593 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229732AbhCKCCA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 21:02:00 -0500
IronPort-SDR: 
 Xd8thHuJZXPsFEv51ow/4pyOzC0ymbh88NrYUQ2GijjtlUR8WAJrUPb4UIjrRIKnebgw7vE/Aa
 sJVuzCnOtbng==
X-IronPort-AV: E=McAfee;i="6000,8403,9919"; a="188637167"
X-IronPort-AV: E=Sophos;i="5.81,238,1610438400";
   d="scan'208";a="188637167"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 18:01:59 -0800
IronPort-SDR: 
 rC1XXEczXjVfHmcxzcFBWufL7rmCqZTEUB9lcvcJI/1dtIGjxfQrCEntZpPlWl3bskp1kH+Uh9
 BSQ5IwFmFOfQ==
X-IronPort-AV: E=Sophos;i="5.81,238,1610438400";
   d="scan'208";a="603341119"
Received: from xuhuiliu-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.31.67])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 18:01:54 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v3 03/25] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
Date: Thu, 11 Mar 2021 15:01:42 +1300
Message-Id: <20210311020142.125722-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: 
 <e1ca4131bc9f98cf50a1200efcf46080d6512fe7.1615250634.git.kai.huang@intel.com>
References: 
 <e1ca4131bc9f98cf50a1200efcf46080d6512fe7.1615250634.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jarkko Sakkinen <jarkko@kernel.org>

EREMOVE takes a page and removes any association between that page and
an enclave.  It must be run on a page before it can be added into
another enclave.  Currently, EREMOVE is run as part of pages being freed
into the SGX page allocator.  It is not expected to fail.

KVM does not track how guest pages are used, which means that SGX
virtualization use of EREMOVE might fail.

Break out the EREMOVE call from the SGX page allocator.  This will allow
the SGX virtualization code to use the allocator directly.  (SGX/KVM
will also introduce a more permissive EREMOVE helper).

Implement original sgx_free_epc_page() as sgx_encl_free_epc_page() to be
more specific that it is used to free EPC page assigned to one enclave.
Print an error message when EREMOVE fails to explicitly call out EPC
page is leaked, and requires machine reboot to get leaked pages back.

Signed-off-by: Jarkko Sakkinen <jarkko@kernel.org>
Co-developed-by: Kai Huang <kai.huang@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
v2->v3:

 - Fixed bug during copy/paste which results in SECS page and va pages are not
   correctly freed in sgx_encl_release() (sorry for the mistake).
 - Added Jarkko's Acked-by.

v1->v2:

 - Changed to hide both SGX1 and SGX2 from /proc/cpuinfo, since no concrete
   use case, per Boris.
 - Refined commit msg to explain why to hide SGX1 and SGX2 in /proc/cpuinfo.

---
 arch/x86/kernel/cpu/sgx/encl.c | 27 ++++++++++++++++++++++++---
 arch/x86/kernel/cpu/sgx/main.c | 12 ++++--------
 2 files changed, 28 insertions(+), 11 deletions(-)

```
#### [PATCH v3 1/2] KVM: arm64: Reject VM creation when the default IPA size is unsupported
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12130769
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D2671C4332E
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 10:01:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D7A064E57
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 10:01:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232134AbhCKKA7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 05:00:59 -0500
Received: from mail.kernel.org ([198.145.29.99]:56292 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232108AbhCKKA1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Mar 2021 05:00:27 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E76E164E28;
        Thu, 11 Mar 2021 10:00:26 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lKI7F-000xb0-2f; Thu, 11 Mar 2021 10:00:25 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH v3 1/2] KVM: arm64: Reject VM creation when the default IPA
 size is unsupported
Date: Thu, 11 Mar 2021 10:00:15 +0000
Message-Id: <20210311100016.3830038-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210311100016.3830038-1-maz@kernel.org>
References: <20210311100016.3830038-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 drjones@redhat.com, eric.auger@redhat.com, alexandru.elisei@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm64 has forever used a 40bit default IPA space, partially
due to its 32bit heritage (where the only choice is 40bit).

However, there are implementations in the wild that have a *cough*
much smaller *cough* IPA space, which leads to a misprogramming of
VTCR_EL2, and a guest that is stuck on its first memory access
if userspace dares to ask for the default IPA setting (which most
VMMs do).

Instead, blundly reject the creation of such VM, as we can't
satisfy the requirements from userspace (with a one-off warning).
Also clarify the boot warning, and document that the VM creation
will fail when an unsupported IPA size is probided.

Although this is an ABI change, it doesn't really change much
for userspace:

- the guest couldn't run before this change, but no error was
  returned. At least userspace knows what is happening.

- a memory slot that was accepted because it did fit the default
  IPA space now doesn't even get a chance to be registered.

The other thing that is left doing is to convince userspace to
actually use the IPA space setting instead of relying on the
antiquated default.

Fixes: 233a7cb23531 ("kvm: arm64: Allow tuning the physical address size for VM")
Signed-off-by: Marc Zyngier <maz@kernel.org>
Cc: stable@vger.kernel.org
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 Documentation/virt/kvm/api.rst |  3 +++
 arch/arm64/kvm/reset.c         | 12 ++++++++----
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] vhost-vdpa: fix use-after-free of v->config_ctx
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12131413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9FF64C433E0
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:53:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4AB1064F9F
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:53:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233820AbhCKNxX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 08:53:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:40473 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233808AbhCKNxL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Mar 2021 08:53:11 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615470791;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=fU0jQeEMLvNYK1r/S5O2kpHjVv1Rt/n95eYPSXJ6zNc=;
        b=QQcVslOkWasXLnpaBJg2JSBXOs3L3Qw92j3na8nV7NrB7+nBj46zVrgklUIsg24nVbwMUY
        CZA9CcEGnGHTzickW5ylbGoWFu0tirS2M4eRiQRsnLNbLI1Z+cKEYRyVlo4yaDMRc6+BBW
        OsFVMaYkVbZ775gP19uQNRLqBcighM8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-306-VpN4r4CWMkiQ9mULivpb2w-1; Thu, 11 Mar 2021 08:53:07 -0500
X-MC-Unique: VpN4r4CWMkiQ9mULivpb2w-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D1A3B83DBE2;
        Thu, 11 Mar 2021 13:53:05 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-146.ams2.redhat.com
 [10.36.113.146])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 213AF196E3;
        Thu, 11 Mar 2021 13:53:03 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Jason Wang <jasowang@redhat.com>, netdev@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 1/2] vhost-vdpa: fix use-after-free of v->config_ctx
Date: Thu, 11 Mar 2021 14:52:56 +0100
Message-Id: <20210311135257.109460-2-sgarzare@redhat.com>
In-Reply-To: <20210311135257.109460-1-sgarzare@redhat.com>
References: <20210311135257.109460-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the 'v->config_ctx' eventfd_ctx reference is released we didn't
set it to NULL. So if the same character device (e.g. /dev/vhost-vdpa-0)
is re-opened, the 'v->config_ctx' is invalid and calling again
vhost_vdpa_config_put() causes use-after-free issues like the
following refcount_t underflow:

    refcount_t: underflow; use-after-free.
    WARNING: CPU: 2 PID: 872 at lib/refcount.c:28 refcount_warn_saturate+0xae/0xf0
    RIP: 0010:refcount_warn_saturate+0xae/0xf0
    Call Trace:
     eventfd_ctx_put+0x5b/0x70
     vhost_vdpa_release+0xcd/0x150 [vhost_vdpa]
     __fput+0x8e/0x240
     ____fput+0xe/0x10
     task_work_run+0x66/0xa0
     exit_to_user_mode_prepare+0x118/0x120
     syscall_exit_to_user_mode+0x21/0x50
     ? __x64_sys_close+0x12/0x40
     do_syscall_64+0x45/0x50
     entry_SYSCALL_64_after_hwframe+0x44/0xae

Fixes: 776f395004d8 ("vhost_vdpa: Support config interrupt in vdpa")
Cc: lingshan.zhu@intel.com
Cc: stable@vger.kernel.org
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vdpa.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] x86/kvmclock: Stop kvmclocks for hibernate restore
##### From: Lenny Szubowicz <lszubowi@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lenny Szubowicz <lszubowi@redhat.com>
X-Patchwork-Id: 12131215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3EB3BC433DB
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:29:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F05EF64FEE
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 13:29:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233628AbhCKN3W (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 08:29:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53311 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233610AbhCKN2y (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Mar 2021 08:28:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615469333;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZKrgnsUmWJ3UzHyrpBLpzaQDnaWIoZ/zFnog8cM5uQs=;
        b=YUVSvCxPdlGE7VmaJGiJtHidklgeNqwzFEezTe2B1UmOTF0RYA17+WFKBSWFO8c3OpSea9
        6sVOFt/Aj5JudRUr8apVRbjG2TU+Z7VjtSBLG3pMnQryPRZUcV5ImUGH6kPMVHoDEqZAxb
        7lVVew/zEP+x5MYBC0glE4y0uHadEMU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-40-GNCw1OkIOT6OqIp_gq2aJg-1; Thu, 11 Mar 2021 08:28:52 -0500
X-MC-Unique: GNCw1OkIOT6OqIp_gq2aJg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 832421934100;
        Thu, 11 Mar 2021 13:28:50 +0000 (UTC)
Received: from lszubowi.redhat.com (ovpn-0-2.rdu2.redhat.com [10.22.0.2])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 417FA1001B2C;
        Thu, 11 Mar 2021 13:28:48 +0000 (UTC)
From: Lenny Szubowicz <lszubowi@redhat.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] x86/kvmclock: Stop kvmclocks for hibernate restore
Date: Thu, 11 Mar 2021 08:28:47 -0500
Message-Id: <20210311132847.224406-1-lszubowi@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Turn off host updates to the registered kvmclock memory
locations when transitioning to a hibernated kernel in
resume_target_kernel().

This is accomplished for secondary vcpus by disabling host
clock updates for that vcpu when it is put offline. For the
primary vcpu, it's accomplished by using the existing call back
from save_processor_state() to kvm_save_sched_clock_state().

The registered kvmclock memory locations may differ between
the currently running kernel and the hibernated kernel, which
is being restored and resumed. Kernel memory corruption is thus
possible if the host clock updates are allowed to run while the
hibernated kernel is relocated to its original physical memory
locations.

This is similar to the problem solved for kexec by
commit 1e977aa12dd4 ("x86: KVM guest: disable clock before rebooting.")

Commit 95a3d4454bb1 ("x86/kvmclock: Switch kvmclock data to a
PER_CPU variable") innocently increased the exposure for this
problem by dynamically allocating the physical pages that are
used for host clock updates when the vcpu count exceeds 64.
This increases the likelihood that the registered kvmclock
locations will differ for vcpus above 64.

Reported-by: Xiaoyi Chen <cxiaoyi@amazon.com>
Tested-by: Mohamed Aboubakr <mabouba@amazon.com>
Signed-off-by: Lenny Szubowicz <lszubowi@redhat.com>
---
 arch/x86/kernel/kvmclock.c | 34 ++++++++++++++++++++++++++++++++--
 1 file changed, 32 insertions(+), 2 deletions(-)

```
#### [PATCH v7 04/14] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Juergen Gross <jgross@suse.com>
X-Patchwork-Id: 12131541
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 941E0C433E6
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 14:24:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B02464FC9
	for <kvm@archiver.kernel.org>; Thu, 11 Mar 2021 14:24:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233573AbhCKOX4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Mar 2021 09:23:56 -0500
Received: from mx2.suse.de ([195.135.220.15]:47660 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233530AbhCKOX0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Mar 2021 09:23:26 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615472604;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=55byjntLWrac+G1/EmyNpbetggnp+E6260ue3t2P3P4=;
        b=pYx9kXR2pk2ZxyiESzP4xgpDuzzlLheI8he4AgVsdLKuUnT8pC0NrFk+J8dKtLPkpVilEJ
        sdTX57T1rw0QbslhJPMJOVWRKm6V1fU4gViCLQE6yIslQtR1nUon0DSNeeIJZLvS2l72aZ
        eIxUlXXU1vXNwzJ0ggSGszKirXHgt6g=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id D7AE7AD73;
        Thu, 11 Mar 2021 14:23:23 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Subject: [PATCH v7 04/14] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Thu, 11 Mar 2021 15:23:09 +0100
Message-Id: <20210311142319.4723-5-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210311142319.4723-1-jgross@suse.com>
References: <20210311142319.4723-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Signed-off-by: Juergen Gross <jgross@suse.com>
Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
V4:
- drop paravirt_time.h again
- don't move Hyper-V code (Michael Kelley)
V5:
- drop no longer needed Hyper-V modification (Michael Kelley)
- switch Arm and Arm64 to static_call(), too (kernel test robot)
V6:
- factor out common parts in Xen pv/pvh initialization (Boris Petkov)
V7:
- use new function static_call_query()
---
 arch/arm/include/asm/paravirt.h       | 14 +++++---------
 arch/arm/kernel/paravirt.c            |  9 +++++++--
 arch/arm64/include/asm/paravirt.h     | 14 +++++---------
 arch/arm64/kernel/paravirt.c          | 13 +++++++++----
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       |  2 +-
 arch/x86/include/asm/paravirt.h       | 15 ++++++++++++---
 arch/x86/include/asm/paravirt_types.h |  6 ------
 arch/x86/kernel/cpu/vmware.c          |  5 +++--
 arch/x86/kernel/kvm.c                 |  2 +-
 arch/x86/kernel/kvmclock.c            |  2 +-
 arch/x86/kernel/paravirt.c            | 13 +++++++++----
 arch/x86/kernel/tsc.c                 |  3 ++-
 arch/x86/xen/time.c                   | 26 +++++++++++++-------------
 drivers/xen/time.c                    |  3 ++-
 15 files changed, 71 insertions(+), 57 deletions(-)

```
