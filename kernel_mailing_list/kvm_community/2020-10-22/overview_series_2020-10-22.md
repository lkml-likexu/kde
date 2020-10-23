#### [GIT PULL] VFIO updates for v5.10-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11851741
Return-Path: <SRS0=LSAW=D5=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AD3FEC4363A
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 17:52:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 363EB20936
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 17:52:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HsazYTo1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S368333AbgJVRwE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Oct 2020 13:52:04 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29140 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S368308AbgJVRwE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 22 Oct 2020 13:52:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603389122;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Snym3up3V+Jaq0VoNL6Bf+mG/o9VEWmu15l14qW0Ezk=;
        b=HsazYTo14z6lwcl7LUJ3FQ7pG7jDOug5XxgjlKpej0aMZWNVfrvKuZk6qdWOpUMA2MvS7x
        eKV1hBv4VDzvIYbmp7XAiCN/aJadQY3pqa+256+thxwrRJzoEYzN1SqR/XFBch1Ky/GGvp
        D2MMiWGHPygPQ2EPnMXuTMnenDNnTRE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-477-hOLuj33oMqSIV1a9CNuMAw-1; Thu, 22 Oct 2020 13:52:00 -0400
X-MC-Unique: hOLuj33oMqSIV1a9CNuMAw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B36AA107ACF8;
        Thu, 22 Oct 2020 17:51:58 +0000 (UTC)
Received: from w520.home (ovpn-112-213.phx2.redhat.com [10.3.112.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 510515D9CC;
        Thu, 22 Oct 2020 17:51:58 +0000 (UTC)
Date: Thu, 22 Oct 2020 11:51:57 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        Diana Craciun <diana.craciun@oss.nxp.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>
Subject: [GIT PULL] VFIO updates for v5.10-rc1
Message-ID: <20201022115157.597fa544@w520.home>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit ba4f184e126b751d1bffad5897f263108befc780:

  Linux 5.9-rc6 (2020-09-20 16:33:55 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.10-rc1

for you to fetch changes up to 2e6cfd496f5b57034cf2aec738799571b5a52124:

  vfio iommu type1: Fix memory leak in vfio_iommu_type1_pin_pages (2020-10-20 10:12:17 -0600)


Please note, this tag has a minor merge conflict with the s390
tree as Vasily noted in his pull request[1] and originally found
by Stephen[2] in linux-next.  The resolution is:

+++ b/arch/s390/pci/pci_bus.c
@@@ -135,9 -197,10 +135,10 @@@ void pcibios_bus_add_device(struct pci_
  	 * With pdev->no_vf_scan the common PCI probing code does not
  	 * perform PF/VF linking.
  	 */
- 	if (zdev->vfn)
+ 	if (zdev->vfn) {
 -		zpci_bus_setup_virtfn(zdev->zbus, pdev, zdev->vfn);
 +		zpci_iov_setup_virtfn(zdev->zbus, pdev, zdev->vfn);
- 
+ 		pdev->no_command_memory = 1;
+ 	}
  }
  
  static int zpci_bus_add_device(struct zpci_bus *zbus, struct zpci_dev *zdev)

[1]https://lore.kernel.org/lkml/your-ad-here.call-01602846038-ext-6012@work.hours/
[2]https://lore.kernel.org/lkml/20200924142651.28382ed7@canb.auug.org.au/

----------------------------------------------------------------
VFIO updates for v5.10-rc1

 - New fsl-mc vfio bus driver supporting userspace drivers of objects
   within NXP's DPAA2 architecture (Diana Craciun)

 - Support for exposing zPCI information on s390 (Matthew Rosato)

 - Fixes for "detached" VFs on s390 (Matthew Rosato)

 - Fixes for pin-pages and dma-rw accesses (Yan Zhao)

 - Cleanups and optimize vconfig regen (Zenghui Yu)

 - Fix duplicate irq-bypass token registration (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (3):
      Merge branches 'v5.10/vfio/bardirty', 'v5.10/vfio/dma_avail', 'v5.10/vfio/misc', 'v5.10/vfio/no-cmd-mem' and 'v5.10/vfio/yan_zhao_fixes' into v5.10/vfio/next
      Merge branches 'v5.10/vfio/fsl-mc-v6' and 'v5.10/vfio/zpci-info-v3' into v5.10/vfio/next
      vfio/pci: Clear token on bypass registration failure

Bharat Bhushan (1):
      vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (12):
      vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
      vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
      vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
      vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
      vfio/fsl-mc: Added lock support in preparation for interrupt handling
      vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
      vfio/fsl-mc: trigger an interrupt via eventfd
      vfio/fsl-mc: Add read/write support for fsl-mc devices
      vfio/fsl-mc: Add support for device reset
      vfio/fsl-mc: Fixed vfio-fsl-mc driver compilation on 32 bit
      vfio/fsl-mc: Fix the dead code in vfio_fsl_mc_set_irq_trigger
      vfio/fsl-mc: fix the return of the uninitialized variable ret

Matthew Rosato (9):
      PCI/IOV: Mark VFs as not implementing PCI_COMMAND_MEMORY
      vfio iommu: Add dma available capability
      s390/pci: Mark all VFs as not implementing PCI_COMMAND_MEMORY
      vfio/pci: Decouple PCI_COMMAND_MEMORY bit checks from is_virtfn
      s390/pci: stash version in the zpci_dev
      s390/pci: track whether util_str is valid in the zpci_dev
      vfio: Introduce capability definitions for VFIO_DEVICE_GET_INFO
      vfio-pci/zdev: Add zPCI capabilities to VFIO_DEVICE_GET_INFO
      MAINTAINERS: Add entry for s390 vfio-pci

Xiaoyang Xu (1):
      vfio iommu type1: Fix memory leak in vfio_iommu_type1_pin_pages

Yan Zhao (3):
      vfio: add a singleton check for vfio_group_pin_pages
      vfio: fix a missed vfio group put in vfio_pin_pages
      vfio/type1: fix dirty bitmap calculation in vfio_dma_rw

Zenghui Yu (3):
      vfio: Fix typo of the device_state
      vfio/pci: Remove redundant declaration of vfio_pci_driver
      vfio/pci: Don't regenerate vconfig for all BARs if !bardirty

 MAINTAINERS                               |  14 +
 arch/s390/include/asm/pci.h               |   4 +-
 arch/s390/pci/pci_bus.c                   |   5 +-
 arch/s390/pci/pci_clp.c                   |   2 +
 drivers/pci/iov.c                         |   1 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 683 ++++++++++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 194 +++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  55 +++
 drivers/vfio/pci/Kconfig                  |  12 +
 drivers/vfio/pci/Makefile                 |   1 +
 drivers/vfio/pci/vfio_pci.c               |  38 +-
 drivers/vfio/pci/vfio_pci_config.c        |  27 +-
 drivers/vfio/pci/vfio_pci_intrs.c         |   4 +-
 drivers/vfio/pci/vfio_pci_private.h       |  12 +
 drivers/vfio/pci/vfio_pci_zdev.c          | 143 +++++++
 drivers/vfio/vfio.c                       |   9 +-
 drivers/vfio/vfio_iommu_type1.c           |  23 +-
 include/linux/pci.h                       |   1 +
 include/uapi/linux/vfio.h                 |  29 +-
 include/uapi/linux/vfio_zdev.h            |  78 ++++
 24 files changed, 1330 insertions(+), 20 deletions(-)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
 create mode 100644 drivers/vfio/pci/vfio_pci_zdev.c
 create mode 100644 include/uapi/linux/vfio_zdev.h

```
#### [PATCH] KVM: X86: Expose KVM_HINTS_REALTIME in KVM_GET_SUPPORTED_CPUID
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11850093
Return-Path: <SRS0=LSAW=D5=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 33C5DC55178
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 01:34:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C01A920725
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 01:34:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="DaIryzOA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2894744AbgJVBes (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 21:34:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55022 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2894703AbgJVBes (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 21:34:48 -0400
Received: from mail-pg1-x541.google.com (mail-pg1-x541.google.com
 [IPv6:2607:f8b0:4864:20::541])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9ADBAC0613CE;
        Wed, 21 Oct 2020 18:34:46 -0700 (PDT)
Received: by mail-pg1-x541.google.com with SMTP id s22so2590333pga.9;
        Wed, 21 Oct 2020 18:34:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=zNKVQRtl8vfQItkTAR2QKWDzX8AbVsj4JXt+RK8do8I=;
        b=DaIryzOAJGOyqZoPSszwqFZw9oUE0zc7MM3We7s/DAGw3+ioDMCj6M+fREQyVZjz+n
         +z/LEH2o48uBxXmKstLKdm5vsN2howD3wceHBxYwlGasykhTmgpi23T4upBG28pbUyE+
         GCJJ6FfztGioPLkhyq2IGpZqPOdY4eUe6rnU1fWoouUjnEqgkPsmCh64qTeOKqQuvqOF
         wYXVJ8q7+IYvM9IJ9+x2C8wzn/pBX+HfE2Z0dXuZCC5dDwT2IDTkpY0hxcoah+roQgrk
         NXJoK+y9Ty0Trguq6yJBTiwvewzKt+GL2LEY+dl/4+0fS6kjrzj09iCgzFP0rvga3eAr
         kvVA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=zNKVQRtl8vfQItkTAR2QKWDzX8AbVsj4JXt+RK8do8I=;
        b=fOU6dclQDrx25lBvZV1vFckW1U+m8vmpcMCTxYpMRECBF8l2JR8qBR7kZ3XHn1Ih56
         Ftl9DJdh8F2Hq2OX5kfa3jEBFK8rKbPpHdU4VfuTfFbQk2ZoVnnJIZ5AawEzPE+zashw
         6oKFihmPahqMvaMbjRhu1GV/ldLpkIRC5gi0aMvZpmQg+c/VHkewRAl1yLA0Htq5b398
         pI8MLF4PUoBuWpY8BD+e7vqyUBmmbmdskHOwJZTuFNkEO/4l+UIglusBPHEpbYyKzxuO
         jM9ZEyQ2TjmE87pQBLvT1hXUzVuKU4ZJT34usy4Cq2xtd0oo+cp6nFkL3UNIiCO7/vr7
         Txkw==
X-Gm-Message-State: AOAM533P4Qu6PdoDD87f1INwwmHt9AjKNNajV9iea8y275UDmP4TdZLK
        RP0Nkufc0QwYN9shkra8Gt9WlXZ0Bp0=
X-Google-Smtp-Source: 
 ABdhPJxBMPAYu5DIsToLDmpp11MFkGT4FM098nbniWPHUQa5FCz7+iPgcrVfY+L+rwbJ7eJbQ0nHNQ==
X-Received: by 2002:a63:4702:: with SMTP id u2mr302963pga.111.1603330485678;
        Wed, 21 Oct 2020 18:34:45 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 kc21sm55289pjb.36.2020.10.21.18.34.42
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Oct 2020 18:34:44 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Expose KVM_HINTS_REALTIME in
 KVM_GET_SUPPORTED_CPUID
Date: Thu, 22 Oct 2020 09:34:35 +0800
Message-Id: <1603330475-7063-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Per KVM_GET_SUPPORTED_CPUID ioctl documentation:

This ioctl returns x86 cpuid features which are supported by both the 
hardware and kvm in its default configuration.

A well-behaved userspace should not set the bit if it is not supported.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v11 01/14] s390/vfio-ap: No need to disable IRQ after queue reset
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11851641
Return-Path: <SRS0=LSAW=D5=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61770C388F7
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 17:12:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB1BB24630
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 17:12:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="o/kz1s2I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2898702AbgJVRM2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Oct 2020 13:12:28 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56276 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2506063AbgJVRM1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 22 Oct 2020 13:12:27 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09MH2Mah030283;
        Thu, 22 Oct 2020 13:12:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=9iz41qkKcI5UFyaLbfBJOVav71tdPjHy80191QGlZaE=;
 b=o/kz1s2Ig5M8/fQTmipfV5LItIYzun7+q8tt8Zn/1zw00ahvzXHgHHdvi5GsoW9PWINV
 /yMDlSoRMo9Ce62YH7WDKUbU56X59G2nub1bbCL8YlqGnXaZ+FRbmVWqWLd7VRn50JGT
 4iC+6wtV10cUAqgpgtGi4MpMhybz+SfiXr4aOTf4K/Ck6J1eZIIib1mR5mtW+8aZnX8/
 i/KYiwlB9cx19V0iibaA+SUzLLjz7ZZQVzMnTxp2l6jVxDf+xTSAKugVtQBNbqR5c5y0
 8na6p8dIK1CtZI/kduw1mtebIuSQV14Q8wxQTpRoO8W27WXD1Z38i/mCjVSNx7rsgXyX iw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34b6n8r6k1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 22 Oct 2020 13:12:25 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09MH2Sch030989;
        Thu, 22 Oct 2020 13:12:25 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34b6n8r6jn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 22 Oct 2020 13:12:25 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09MHCLav015337;
        Thu, 22 Oct 2020 17:12:24 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma01dal.us.ibm.com with ESMTP id 347r89vb9q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 22 Oct 2020 17:12:24 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 09MHCKCn7864646
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 22 Oct 2020 17:12:21 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D7A2178064;
        Thu, 22 Oct 2020 17:12:20 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A9E37805C;
        Thu, 22 Oct 2020 17:12:19 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.170.177])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 22 Oct 2020 17:12:19 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v11 01/14] s390/vfio-ap: No need to disable IRQ after queue
 reset
Date: Thu, 22 Oct 2020 13:11:56 -0400
Message-Id: <20201022171209.19494-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20201022171209.19494-1-akrowiak@linux.ibm.com>
References: <20201022171209.19494-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.737
 definitions=2020-10-22_12:2020-10-20,2020-10-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 lowpriorityscore=0 priorityscore=1501 clxscore=1015 impostorscore=0
 spamscore=0 mlxlogscore=973 malwarescore=0 phishscore=0 mlxscore=0
 suspectscore=2 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010220108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The queues assigned to a matrix mediated device are currently reset when:

* The VFIO_DEVICE_RESET ioctl is invoked
* The mdev fd is closed by userspace (QEMU)
* The mdev is removed from sysfs.

Immediately after the reset of a queue, a call is made to disable
interrupts for the queue. This is entirely unnecessary because the reset of
a queue disables interrupts, so this will be removed.

Since interrupt processing may have been enabled by the guest, it may also
be necessary to clean up the resources used for interrupt processing. Part
of the cleanup operation requires a reference to KVM, so a check is also
being added to ensure the reference to KVM exists. The reason is because
the release callback - invoked when userspace closes the mdev fd - removes
the reference to KVM. When the remove callback - called when the mdev is
removed from sysfs - is subsequently invoked, there will be no reference to
KVM when the cleanup is performed.

This patch will also do a bit of refactoring due to the fact that the
remove callback, implemented in vfio_ap_drv.c, disables the queue after
resetting it. Instead of the remove callback making a call into the
vfio_ap_ops.c to clean up the resources used for interrupt processing,
let's move the probe and remove callbacks into the vfio_ap_ops.c
file keep all code related to managing queues in a single file.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 45 +------------------
 drivers/s390/crypto/vfio_ap_ops.c     | 63 +++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |  7 +--
 3 files changed, 52 insertions(+), 63 deletions(-)

```
#### [PATCH] vfio/type1: Use the new helper to find vfio_group
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11850975
Return-Path: <SRS0=LSAW=D5=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26C97C55179
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 12:27:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C327D221FB
	for <kvm@archiver.kernel.org>; Thu, 22 Oct 2020 12:27:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2898158AbgJVM1B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Oct 2020 08:27:01 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:15243 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2898151AbgJVM1A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Oct 2020 08:27:00 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id B8C0452696F9DE132DF9;
        Thu, 22 Oct 2020 20:25:33 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.179) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Thu, 22 Oct 2020 20:25:26 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <alex.williamson@redhat.com>, <cohuck@redhat.com>
CC: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <wanghaibin.wang@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] vfio/type1: Use the new helper to find vfio_group
Date: Thu, 22 Oct 2020 20:24:17 +0800
Message-ID: <20201022122417.245-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.179]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When attaching a new group to the container, let's use the new helper
vfio_iommu_find_iommu_group() to check if it's already attached. There
is no functional change.

Also take this chance to add a missing blank line.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 17 +++++------------
 1 file changed, 5 insertions(+), 12 deletions(-)

```
