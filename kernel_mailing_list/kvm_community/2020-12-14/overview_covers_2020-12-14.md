

#### [PATCH v3 00/17] KVM: Add minimal support for Xen HVM guests
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Mon Dec 14 08:38:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11971523
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB8B7C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 08:40:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92F7C206C1
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 08:40:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439340AbgLNIkM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 03:40:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47442 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2439091AbgLNIjx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 03:39:53 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B26E3C0613D3
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 00:39:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=wx/ghlTnyKIamax6lLM5rHnGR9Aiyh/EKRTrwJDR6A4=;
 b=rKR4diG6ipHmAjh1ZIYTvw6xDj
        kVubC2piqgoSu81jJYrkPp3HhWtbioM9Inw/wXR2owTYK2nJYXxY9e3dBw0er0FmasFJefLIJo9Ww
        6Z2DE7hqGbzDOvETU9QkeTf1sXeZKoA4iVtpUmfLmkTdsmV/MIvntrwo6MoUeyFa7qFISHXdYZ9gY
        6RpOX0TlBNv8VoqjMgtBG2Kaa1OmTemEBGYgoYlu3aSXNt8aZLmM3CGm4OiDxc6of6pNdZeqwqrtL
        jaRFYPHY3Ury0p6MYfQAIELlO70aLED9hEi7zdWcthnBxOWj6mm6KXiUlvcCx2QJY7gEVdi7D8DbP
        Fyyj2xmg==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kojNs-00028a-07; Mon, 14 Dec 2020 08:39:08 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kojNr-008SxU-IJ; Mon, 14 Dec 2020 08:39:07 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com
Subject: [PATCH v3 00/17] KVM: Add minimal support for Xen HVM guests
Date: Mon, 14 Dec 2020 08:38:48 +0000
Message-Id: <20201214083905.2017260-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reviving the first section (so far) of a patch set that Joao posted as 
RFC last year:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

This is just enough to support Xen HVM guests. It allows hypercalls to
be trapped to userspace for handling, uses the existing KVM functions for
writing system clock and pvclock information to Xen shared pages, and
adds Xen runstate info and event channel upcall vector delivery.

I've updated and reworked the original a bit, including (in my v1):
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

v2: 
 • Remember the RCU read-critical sections on using the shared info pages
 • Fix 32-bit build of compat structures (which we use there too)
 • Use RUNSTATE_blocked as initial state not RUNSTATE_runnable
 • Include documentation, add cosmetic KVM_XEN_HVM_CONFIG_HYPERCALL_MSR

v3:
 • Stop mapping the shared pages; use kvm_guest_write_cached() instead.
 • Use kvm_setup_pvclock_page() for Xen pvclock writes too.
 • Fix CPU numbering confusion and update documentation accordingly.
 • Support HVMIRQ_callback_vector delivery based on evtchn_upcall_pending.

With the addition in v3 of the callback vector support, we can now 
successfully boot Linux guests. Other callback types can be handled 
entirely from userspace, but the vector injection needs kernel support 
because it doesn't quite work to inject it as ExtINT.

We will work on a little bit more event channel offload in future patches,
as discussed, but those are purely optimisations. There's a bunch of work
for us to do in userspace before those get to the top of our list, and
this patch set should be functionally complete as it is.

We're working on pushing out rust-vmm support to make use of this, and
Joao's qemu patches from last year should still also work with minor
tweaks where I've "improved" the KVM←→userspace ABI.

 Documentation/virt/kvm/api.rst                       | 123 ++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h                      |  24 ++++
 arch/x86/include/asm/xen/interface.h                 |   3 +
 arch/x86/kvm/Makefile                                |   2 +-
 arch/x86/kvm/hyperv.c                                |  40 +++++--
 arch/x86/kvm/irq.c                                   |   7 ++
 arch/x86/kvm/trace.h                                 |  36 ++++++
 arch/x86/kvm/x86.c                                   | 142 ++++++++++++++---------
 arch/x86/kvm/x86.h                                   |   1 +
 arch/x86/kvm/xen.c                                   | 495 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/xen.h                                   |  68 +++++++++++
 include/linux/kvm_host.h                             |  34 +++---
 include/uapi/linux/kvm.h                             |  50 ++++++++
 include/xen/interface/xen.h                          |   4 +-
 tools/testing/selftests/kvm/Makefile                 |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c           |   1 +
 tools/testing/selftests/kvm/x86_64/xen_shinfo_test.c | 194 +++++++++++++++++++++++++++++++
 tools/testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 ++++++++++++++++++++++++
 virt/kvm/kvm_main.c                                  |   8 +-
 19 files changed, 1297 insertions(+), 87 deletions(-)

David Woodhouse (8):
      KVM: Fix arguments to kvm_{un,}map_gfn()
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates
      KVM: x86/xen: Add event channel interrupt vector upcall

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: register vcpu time info region
      KVM: x86/xen: register runstate info
```
#### [RFC, v3 0/2] msi support for platform devices
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
From patchwork Mon Dec 14 17:45:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11972609
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4732AC2BB40
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F30821D7F
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408691AbgLNRqV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 12:46:21 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47230 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730877AbgLNRqJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 12:46:09 -0500
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AE89BC0613D3
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 09:45:29 -0800 (PST)
Received: by mail-pj1-x1042.google.com with SMTP id hk16so7009059pjb.4
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 09:45:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=mime-version:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=qsZglg7YDD1R/xq2UYS6OScnwm+S6oaLv8VfaqEBCrY=;
        b=HvLQR4hVHShkUXunMDNeoR12kKL1Wfebd+Zb+b2tOoxI93uJ+1s4kRBVBu4pJrk+IO
         gFPNFC0LxgVpSS9UfZwdcnPMVCpcOQXIdRDzLBDKRU/BctMgC6oYyIzpCps749Zj9ngH
         zaO/tY8HCyMH4Io2jSFyHGETTUDGotc+bhaT8=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=mime-version:x-gm-message-state:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=qsZglg7YDD1R/xq2UYS6OScnwm+S6oaLv8VfaqEBCrY=;
        b=jaK+1xsqZ4ZwzVdjXxSHl8V3eXZ+rsfHP8q4S6S6mOSdLEkodsQAvbFZdoikxfQeJW
         nYxK7Migd470MfotBaatboqj1dbcxV5EWNqbuzE+F/P/OeEKXTkZ61Go64jlQzeCH2TD
         gisMHiVZtnFXhzJW9e2QR4u0CRK3e0hhwt3sH79mqv1PardTdPAXCOEeU8Dlj7VUuEm8
         46qgJAoCzblEopqBK7Ece8v0mjsjXJOFp8ks5ADWQo+1hAvfHQtxaRhI684YNUIuZrzP
         1eIuDHlXYAxtXJ33jgZXJzTsBSOPVAi2QRlxBQVfv94dDzgEIuS/9E7WxOlVVXlv+raE
         OQ7g==
MIME-Version: 1.0
X-Gm-Message-State: AOAM5310CYcGztAYESbXuAweypJ5nJlJCp1c5qPSzQVbifYcEr1FiNpK
        R1AYvCKIRdTF+9/LeGFX+IQtFJcRvzfE2PDBMkGNKYcqGRt7jNGBd3NWTuyOkNeZjalCmyP/F9B
        wCTc=
X-Google-Smtp-Source: 
 ABdhPJx5QiCPwN50K+LREilTYGjyEtiHQSZRpErcamh+B+9kk8PEkIf0bPJaXsyoGTCZKvTW1rP0tA==
X-Received: by 2002:a17:90a:a781:: with SMTP id
 f1mr15360359pjq.111.1607967928796;
        Mon, 14 Dec 2020 09:45:28 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 m8sm6658131pgg.78.2020.12.14.09.45.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 14 Dec 2020 09:45:27 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC, v3 0/2] msi support for platform devices
Date: Mon, 14 Dec 2020 23:15:12 +0530
Message-Id: <20201214174514.22006-1-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201124161646.41191-1-vikas.gupta@broadcom.com>
References: <20201124161646.41191-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC adds support for MSI for platform devices.
MSI block is added as an ext irq along with the existing
wired interrupt implementation. The patchset exports two
caps for MSI and related data to configure MSI source device.

Changes from:
-------------
 v2 to v3:
	1) Restored the vendor specific module to get max number
	   of MSIs supported and .count value initialized.
	2) Comments from Eric addressed.

 v1 to v2:
	1) IRQ allocation has been implemented as below:
	       ----------------------------
	       |IRQ-0|IRQ-1|....|IRQ-n|MSI|
       	       ----------------------------
		MSI block has msi contexts and its implemneted
		as ext irq.

	2) Removed vendor specific module for msi handling so
	   previously patch2 and patch3 are not required.

	3) MSI related data is exported to userspace using 'caps'.
	 Please note VFIO_IRQ_INFO_CAP_TYPE in include/uapi/linux/vfio.h implementation
	is taken from the Eric`s patch
        https://patchwork.kernel.org/project/kvm/patch/20201116110030.32335-8-eric.auger@redhat.com/


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


Vikas Gupta (2):
  vfio/platform: add support for msi
  vfio/platform: msi: add Broadcom platform devices

 drivers/vfio/platform/Kconfig                 |   1 +
 drivers/vfio/platform/Makefile                |   1 +
 drivers/vfio/platform/msi/Kconfig             |   9 +
 drivers/vfio/platform/msi/Makefile            |   2 +
 .../vfio/platform/msi/vfio_platform_bcmplt.c  |  49 ++++
 drivers/vfio/platform/vfio_platform_common.c  | 179 +++++++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 260 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  32 +++
 include/uapi/linux/vfio.h                     |  44 +++
 9 files changed, 558 insertions(+), 19 deletions(-)
 create mode 100644 drivers/vfio/platform/msi/Kconfig
 create mode 100644 drivers/vfio/platform/msi/Makefile
 create mode 100644 drivers/vfio/platform/msi/vfio_platform_bcmplt.c
```
#### [PATCH 0/3] KVM: x86: MSR completion refactoring for SEV-ES
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon Dec 14 18:32:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11972703
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43785C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:35:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EAB322250F
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:35:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2440922AbgLNSee (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 13:34:34 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33006 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2440906AbgLNSe0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Dec 2020 13:34:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607970777;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xkuYtdLf6aD5g/AJsimLnGfHqBLSAGTfbX/Ao9PPeSQ=;
        b=RnVucHFdLC0A99DyxRTSP16UrOSV/zU9pvEhF1l5LHw8z3gd4O5+wUg/MsyqdmCVHS2h8R
        bbSBIm4f8YtfCyoPcmYBoi0yS7C+2E/XqQhVDiJl/JzTxNYMFMBmJHALRAeZBcnEUosp/v
        jyPrhmQrm3/TstZvZwcI9eqEUn6FTT0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-323-xMThsjC3OO66Xqsd14h6wA-1; Mon, 14 Dec 2020 13:32:53 -0500
X-MC-Unique: xMThsjC3OO66Xqsd14h6wA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 005D6180A0AA;
        Mon, 14 Dec 2020 18:32:52 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 67D73100AE36;
        Mon, 14 Dec 2020 18:32:51 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Alexander Graf <graf@amazon.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH 0/3] KVM: x86: MSR completion refactoring for SEV-ES
Date: Mon, 14 Dec 2020 13:32:47 -0500
Message-Id: <20201214183250.1034541-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches remove kvm_inject_gp from the RDMSR/WRMSR emulation
path, with the purpose of letting SEV-ES inject the #GP through
the GHCB instead.

The main idea is to introduce a complete_emulated_msr callback
that is call-compatible with kvm_complete_insn_gp, so that svm.c
can just call kvm_complete_insn_gp in the common case.

I have more patches to use kvm_complete_insn_gp instead of
kvm_inject_gp in other paths, but they are not necessary for
SEV-ES so they can be delayed to 5.12.

Paolo

Paolo Bonzini (3):
  KVM: x86: remove bogus #GP injection
  KVM: x86: use kvm_complete_insn_gp in emulating RDMSR/WRMSR
  KVM: x86: introduce complete_emulated_msr callback

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mtrr.c             |  6 +----
 arch/x86/kvm/svm/svm.c          |  1 +
 arch/x86/kvm/vmx/vmx.c          |  1 +
 arch/x86/kvm/x86.c              | 42 +++++++++++++--------------------
 5 files changed, 20 insertions(+), 31 deletions(-)
```
#### [PATCH v2 00/16] target/mips: Boring code reordering + add
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Mon Dec 14 18:37:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11972731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DE134C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:38:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A390E22525
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:38:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408902AbgLNSis (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 13:38:48 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55364 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2408880AbgLNSiX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 13:38:23 -0500
Received: from mail-wr1-x42a.google.com (mail-wr1-x42a.google.com
 [IPv6:2a00:1450:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70A91C0613D6
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 10:37:43 -0800 (PST)
Received: by mail-wr1-x42a.google.com with SMTP id r7so17447868wrc.5
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 10:37:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=AG2rQ9Qtoq4dN1hxG3H/JYpJcOn2clPmULTzCCQTdSg=;
        b=dofAUxB8rl9deqttLdM9wJfdeOk+uMF9M+K33hBsYpo6ml/65Tvhhrx/vtw3QNHAMr
         wSHc6Q39uT6NgKHt6Z6400LcxQETiWX1FW2d0qESbGYMMR86dXK8xVcKc3da0RPmibJR
         Cft0X489fWZYC/kOlyTFkay+KSGwphpCPV7N9LIl/yWbPhdZZOxCdnJVliQ8BWgfQbbj
         mlOIg/YOIAnZFdrcEWMRDwaz1PBl4/KAq1BJzZK8k19847lFj0+KnTvIDxMZDxoYkNEA
         aTChfn07kynPe6FJ1On4KKkkAnMGA4Ceo3KLPvL4Z/kGzMMDbHCTfnLesTe5xdA8XHFA
         0d8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=AG2rQ9Qtoq4dN1hxG3H/JYpJcOn2clPmULTzCCQTdSg=;
        b=CBoAsxBjrQTbftxxulbuu4YTekQ06Tym3PgA0JtkSEei4B97mfbYxervnDzTkHOQ3g
         t+YcqOeemuRfUFg6q8fJO+ghVF/1qlWWhPReCvx3kADIfm5xOtCpjny2D2BEm33BEsQb
         1nqKTUEAO3eIsmFFNgr2llQNBE/7uZKHkcY51ll68AXYbGcQyxypP8M8sTjvDpTc4xL5
         0QUKzhvEt7uHQAy/1qxZbT2H4Y5dEV+Q2i5P4iRBd3C2hlx8q0dpbhZljVfUjJlTIWAx
         DRu1It6RujauClq+wL7KX6v0vczKbsNOeyqEUmL/uOurguCQPN6LcA0Oa8FUs8SlPTe1
         Tzlw==
X-Gm-Message-State: AOAM530MJ1SWSqAwZNRAUeLvTlYSyFarcFOl5PTMcNHU5Jby+EFzVrhK
        /FZme8ASJ6f1nO8JqcoMlmM7huL+GrI=
X-Google-Smtp-Source: 
 ABdhPJyGIAR0xFDE405UQS33tC5brIhj4plOxCsmIutdMpwyktpCHuGbf+AeTk8Lgn6viqQ6dVnD1g==
X-Received: by 2002:adf:fe05:: with SMTP id n5mr22567213wrr.9.1607971062134;
        Mon, 14 Dec 2020 10:37:42 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 v11sm3413358wrt.25.2020.12.14.10.37.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 14 Dec 2020 10:37:41 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Aurelien Jarno <aurelien@aurel32.net>,
 Huacai Chen <chenhuacai@kernel.org>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Laurent Vivier <laurent@vivier.eu>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v2 00/16] target/mips: Boring code reordering + add
 "translate.h"
Date: Mon, 14 Dec 2020 19:37:23 +0100
Message-Id: <20201214183739.500368-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series contains the patches previously sent in "Boring code
reordering" [1] and "Add translate.h and fpu_translate.h headers"
[2]. I removed the patches merged and addressed Richard review
comments.

Missing review: 1 3-5 9-11 14 15

Available as:
  https://gitlab.com/philmd/qemu/-/commits/refactor_translate_h

Regards,

Phil.

Based-on: https://gitlab.com/philmd/qemu.git tags/mips-next
Supersedes: <20201206233949.3783184-1-f4bug@amsat.org>
Supersedes: <20201207235539.4070364-1-f4bug@amsat.org>

[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg764551.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg764828.html

Philippe Mathieu-Daudé (16):
  target/mips: Inline cpu_state_reset() in mips_cpu_reset()
  target/mips: Extract FPU helpers to 'fpu_helper.h'
  target/mips: Add !CONFIG_USER_ONLY comment after #endif
  target/mips: Remove consecutive CONFIG_USER_ONLY ifdefs
  target/mips: Extract common helpers from helper.c to common_helper.c
  target/mips: Rename helper.c as tlb_helper.c
  target/mips: Fix code style for checkpatch.pl
  target/mips: Move mmu_init() functions to tlb_helper.c
  target/mips: Rename translate_init.c as cpu-defs.c
  target/mips: Replace gen_exception_err(err=0) by gen_exception_end()
  target/mips: Replace gen_exception_end(EXCP_RI) by
    gen_rsvd_instruction
  target/mips/translate: Extract DisasContext structure
  target/mips/translate: Add declarations for generic code
  target/mips: Declare generic FPU functions in 'translate.h'
  target/mips: Extract FPU specific definitions to translate.h
  target/mips: Only build TCG code when CONFIG_TCG is set

 target/mips/fpu_helper.h                      |  59 ++
 target/mips/internal.h                        |  52 +-
 target/mips/translate.h                       | 166 ++++
 linux-user/mips/cpu_loop.c                    |   1 +
 target/mips/cpu.c                             | 243 ++++-
 target/mips/fpu_helper.c                      |   1 +
 target/mips/gdbstub.c                         |   1 +
 target/mips/kvm.c                             |   1 +
 target/mips/machine.c                         |   1 +
 target/mips/msa_helper.c                      |   1 +
 target/mips/op_helper.c                       |   2 +-
 target/mips/{helper.c => tlb_helper.c}        | 260 ++---
 target/mips/translate.c                       | 897 ++++++++----------
 .../{translate_init.c.inc => cpu-defs.c.inc}  |  50 +-
 target/mips/meson.build                       |  10 +-
 15 files changed, 903 insertions(+), 842 deletions(-)
 create mode 100644 target/mips/fpu_helper.h
 create mode 100644 target/mips/translate.h
 rename target/mips/{helper.c => tlb_helper.c} (87%)
 rename target/mips/{translate_init.c.inc => cpu-defs.c.inc} (96%)
```
