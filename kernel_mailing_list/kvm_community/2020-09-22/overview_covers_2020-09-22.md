

#### [RFC Patch 0/2] KVM: SVM: Cgroup support for SVM SEV ASIDs
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Tue Sep 22 00:40:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11791313
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9461112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 00:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0F0723A1B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 00:40:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="kdyVgyus"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729173AbgIVAko (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 20:40:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51112 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728597AbgIVAko (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 20:40:44 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 92DE7C061755
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 17:40:44 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id k3so14645263ybk.16
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 17:40:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=V3Xr2zBCrWRdkK+k7x0nVhZayUYo5UZWzWiSfnS90fI=;
        b=kdyVgyusZNzoXrTJhguQAb+Mx6TJNWHRXlrjar7ZHpeVOaXSPFcnqpBVcrKSj7jdY/
         Z9S2h73yYxQ9ye0LpN+CnHJtEkvDKrW9dX9pf4gz/5JYMJcccJoedfYoOR8AT6arrG/0
         ux966VV/bda9j4D3905gY+7QxO5ycI5EIzvDsYywy96gVK8JhFGFJMy2GicwDum9X/7W
         5AEWANjjafFjdR3tEOf/Btn3rFXzJXaLz1TU4p2opSJylwS9O8Y07YUPXzdI/9WSkVZ9
         xceQndQbqE8aM4VfKijgA1/KGV6BKYHLXzO7PTdnAOW4uHnL0OrmfA8n9UcoRW9J8H5E
         Wt1A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=V3Xr2zBCrWRdkK+k7x0nVhZayUYo5UZWzWiSfnS90fI=;
        b=RzP88snqgNAHjU925Y2qIEEXJRmVQ5RmTNwSN4mNc3MdS4x3N8EeYlKw0USwSiGWiq
         VKY7N2mo2XyFrrsPX+UGu9v36mIWQDl5ZyXaGn8f5Cxp+Tz1Wx10vz+UV/RZLrV51OWL
         FQfqqMhqizPwELpHB19CI1Srznj10nvmE6Zc2IVrsd8M48R19CxY6BaylKLn/RXY8WEJ
         n5eabhuqXTpVagTLMB3ITUV0QWnDioCfLRRMXemoD2IdWm2aTILgzjmgEFGWnHZn46Ea
         lpRgEiU5n+8DWOSrOWoh/e6od8hiSd18YSDwbpTn9raojtJHJlgnNpCtO//L9QY/7Agx
         l+nw==
X-Gm-Message-State: AOAM533JeAu1Yc8yv4AlGpOXwy200UASoHrEs/xFE6yAihwHIJutMru4
        dac1sGgUqfg1tL/XQc4gYVkecsenr7d0
X-Google-Smtp-Source: 
 ABdhPJxDC6JLVG11hhZe1uOVPGKcetCubbINqx66dzuSedg2x2A03OBC/7sbWEURwwLPReMPnq569d3iROp7
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a25:900b:: with SMTP id
 s11mr3389263ybl.426.1600735243795; Mon, 21 Sep 2020 17:40:43 -0700 (PDT)
Date: Mon, 21 Sep 2020 17:40:22 -0700
Message-Id: <20200922004024.3699923-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.681.g6f77f65b4e-goog
Subject: [RFC Patch 0/2] KVM: SVM: Cgroup support for SVM SEV ASIDs
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, tj@kernel.org, lizefan@huawei.com
Cc: joro@8bytes.org, corbet@lwn.net, brijesh.singh@amd.com,
        jon.grimm@amd.com, eric.vantassell@amd.com, gingell@google.com,
        rientjes@google.com, kvm@vger.kernel.org, x86@kernel.org,
        cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch series adds a new SEV controller for tracking and limiting
the usage of SEV ASIDs on the AMD SVM platform.

SEV ASIDs are used in creating encrypted VM and lightweight sandboxes
but this resource is in very limited quantity on a host.

This limited quantity creates issues like SEV ASID starvation and
unoptimized scheduling in the cloud infrastructure.

SEV controller provides SEV ASID tracking and resource control
mechanisms.

Patch 1 - Overview, motivation, and implementation details of the SEV
          controller.
Patch 2 - Kernel documentation of the SEV controller for both
	  cgroup v1 and v2.

Thanks

Vipin Sharma (2):
  KVM: SVM: Create SEV cgroup controller.
  KVM: SVM: SEV cgroup controller documentation

 Documentation/admin-guide/cgroup-v1/sev.rst |  94 +++++
 Documentation/admin-guide/cgroup-v2.rst     |  56 ++-
 arch/x86/kvm/Makefile                       |   1 +
 arch/x86/kvm/svm/sev.c                      |  16 +-
 arch/x86/kvm/svm/sev_cgroup.c               | 414 ++++++++++++++++++++
 arch/x86/kvm/svm/sev_cgroup.h               |  40 ++
 include/linux/cgroup_subsys.h               |   3 +
 init/Kconfig                                |  14 +
 8 files changed, 634 insertions(+), 4 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/sev.rst
 create mode 100644 arch/x86/kvm/svm/sev_cgroup.c
 create mode 100644 arch/x86/kvm/svm/sev_cgroup.h
```
#### [PATCH v5 0/5] iommu aux-domain APIs extensions
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Tue Sep 22 06:10:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11791567
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3850B618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 06:17:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 27F2D21BE5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 06:17:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729196AbgIVGQy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 02:16:54 -0400
Received: from mga12.intel.com ([192.55.52.136]:45065 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729065AbgIVGQx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Sep 2020 02:16:53 -0400
IronPort-SDR: 
 ZsUj4qbAu/7JP6igfvIoYOLbe2cJ+YDR1P72npZn5vnMl2eLdpIh1IQPyoHc4kPF0V/H0LsLe7
 3hc3Ll7DFohQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9751"; a="140023298"
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="140023298"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Sep 2020 23:16:53 -0700
IronPort-SDR: 
 MRN1pkDHtVIp8X7IJS5GWx5rYmWiDE08UuKtxsPLLtqWw5ql7hbfKzxbhbczzbNIAFnIiY8+kw
 y7Nbta3zIyZQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="334877182"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga004.fm.intel.com with ESMTP; 21 Sep 2020 23:16:50 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v5 0/5] iommu aux-domain APIs extensions
Date: Tue, 22 Sep 2020 14:10:37 +0800
Message-Id: <20200922061042.31633-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jorge and Alex,

A description of this patch series could be found here.

https://lore.kernel.org/linux-iommu/20200901033422.22249-1-baolu.lu@linux.intel.com/

This version adds some changes according to Alex's review comments.

- Add comments and naming rule for subdevices.
https://lore.kernel.org/linux-iommu/20200910160549.2b176ac5@w520.home/

- Continue detaching even no subdevice parent found.
https://lore.kernel.org/linux-iommu/20200910160547.0a8b9891@w520.home/

- Make subdev_link_device() and subdev_unlink_device() symmetrical.

Please help to review and merge.

Best regards,
baolu

Lu Baolu (5):
  iommu: Add optional subdev in aux_at(de)tach ops
  iommu: Add iommu_at(de)tach_subdev_group()
  iommu: Add iommu_aux_get_domain_for_dev()
  vfio/type1: Use iommu_aux_at(de)tach_group() APIs
  iommu/vt-d: Add is_aux_domain support

 drivers/iommu/intel/iommu.c     | 139 +++++++++++++++++-------
 drivers/iommu/iommu.c           | 184 ++++++++++++++++++++++++++++++--
 drivers/vfio/vfio_iommu_type1.c |  43 ++------
 include/linux/intel-iommu.h     |  17 +--
 include/linux/iommu.h           |  46 +++++++-
 5 files changed, 336 insertions(+), 93 deletions(-)
```
#### [PATCH 0/3] i386/kvm: Assume IRQ routing is always available
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
From patchwork Tue Sep 22 20:19:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11793033
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E59992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:19:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57EF9206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:19:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PTFU2SDd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726686AbgIVUTe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 16:19:34 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:35486 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726448AbgIVUTe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 16:19:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600805973;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9x1hlobF7KdJZj9Gxk1LjuIS+slLQ+pwDxPhU6e65XM=;
        b=PTFU2SDdUQQ67SQzGisHHYk75sge+GvSZ8REiUK19OFvlBPdGYBv0RcIMwOae0XaPTEJKl
        IuAL4sCZL1GBDRh7OPTx1UIbSWlr4o5dmN9xk5pj/E854UpBLIv/mBeq0UOy13dpVFY8mI
        PLMELVcD6B2THaCavPqucw+ZicFh5b0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-32-Bz2zwGMvOnmXRDFrPmH-aw-1; Tue, 22 Sep 2020 16:19:31 -0400
X-MC-Unique: Bz2zwGMvOnmXRDFrPmH-aw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EF4C118B9ECB;
        Tue, 22 Sep 2020 20:19:29 +0000 (UTC)
Received: from localhost (unknown [10.10.67.5])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 946A519D6C;
        Tue, 22 Sep 2020 20:19:23 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sergio Lopez <slp@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <rth@twiddle.net>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 0/3] i386/kvm: Assume IRQ routing is always available
Date: Tue, 22 Sep 2020 16:19:19 -0400
Message-Id: <20200922201922.2153598-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_CAP_IRQ_ROUTING is available since 2019 (Linux v2.6.30), so
we can safely assume it's always present and remove some runtime
checks.

Eduardo Habkost (3):
  i386/kvm: Require KVM_CAP_IRQ_ROUTING
  i386/kvm: Remove IRQ routing support checks
  i386/kvm: Delete kvm_allows_irq0_override()

 target/i386/kvm_i386.h |  1 -
 hw/i386/fw_cfg.c       |  2 +-
 hw/i386/kvm/apic.c     |  5 ++---
 hw/i386/kvm/ioapic.c   | 33 ++++++++++++++++-----------------
 hw/i386/microvm.c      |  2 +-
 hw/i386/pc.c           |  2 +-
 target/i386/kvm-stub.c |  5 -----
 target/i386/kvm.c      | 17 +++++------------
 8 files changed, 26 insertions(+), 41 deletions(-)
```
#### [PATCH v6 0/4] KVM: nSVM: ondemand nested state allocation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Tue Sep 22 21:10:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11793173
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41981112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 21:10:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 206AA206FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 21:10:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ekIwuyE4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726716AbgIVVKf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 17:10:35 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:27967 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726625AbgIVVKf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 17:10:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600809034;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=bNjVgWpgtIkPhRa8XVCPnausw2GfEoBb82DdGdZXVvc=;
        b=ekIwuyE46DrYdAaRR3VUm9LJ6r86ZyXtW9vna51dozcxfWozLSzNT6srwE2a0xuuuUv4XQ
        AEg5PntS9WxpfXwePKBvt4KyJRAGcL9RvrB036MI35X+RjLHN8wY7TVNG517Fc9UqGOOIU
        ahdkDAwhtTWQKy7OVlzx6mYY3DHOA3k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-91-EmSHZr1ePa6cO30n87NEuA-1; Tue, 22 Sep 2020 17:10:32 -0400
X-MC-Unique: EmSHZr1ePa6cO30n87NEuA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E4AE01007B36;
        Tue, 22 Sep 2020 21:10:30 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.154])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EF02155768;
        Tue, 22 Sep 2020 21:10:26 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v6 0/4] KVM: nSVM: ondemand nested state allocation
Date: Wed, 23 Sep 2020 00:10:21 +0300
Message-Id: <20200922211025.175547-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the next version of this patch series.

In V5 I adopted Sean Christopherson's suggestion to make .set_efer return
a negative error (-ENOMEM in this case) which in most cases in kvm
propagates to the userspace.

I noticed though that wrmsr emulation code doesn't do this and instead
it injects #GP to the guest on _any_ error.

So I fixed the wrmsr code to behave in a similar way to the rest
of the kvm code.
(#GP only on a positive error value, and forward the negative error to
the userspace)

I had to adjust one wrmsr handler (xen_hvm_config) to stop it from returning
negative values	so that new WRMSR emulation behavior doesn't break it.
This patch was only compile tested.

The memory allocation failure was tested by always returning -ENOMEM
from svm_allocate_nested.

The nested allocation itself was tested by countless attempts to run
nested guests, do nested migration on both my AMD and Intel machines.
I wasn't able to break it.

Changes from V5: addressed Sean Christopherson's review feedback.

Best regards,
	Maxim Levitsky

Maxim Levitsky (4):
  KVM: x86: xen_hvm_config: cleanup return values
  KVM: x86: report negative values from wrmsr emulation to userspace
  KVM: x86: allow kvm_x86_ops.set_efer to return an error value
  KVM: nSVM: implement on demand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/emulate.c          |  7 ++--
 arch/x86/kvm/svm/nested.c       | 42 ++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          | 58 +++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.h          |  8 ++++-
 arch/x86/kvm/vmx/vmx.c          |  6 ++--
 arch/x86/kvm/x86.c              | 37 ++++++++++++---------
 7 files changed, 113 insertions(+), 47 deletions(-)
```
