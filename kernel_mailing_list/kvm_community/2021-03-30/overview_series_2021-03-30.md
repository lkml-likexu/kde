#### [PATCH v4 1/3] cgroup: Add misc cgroup controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12171621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 43952C433E2
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 04:43:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C156619A6
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 04:43:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229755AbhC3Emn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 00:42:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59582 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229567AbhC3EmQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 00:42:16 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BF105C061764
        for <kvm@vger.kernel.org>; Mon, 29 Mar 2021 21:42:15 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id i6so6691398ybk.2
        for <kvm@vger.kernel.org>; Mon, 29 Mar 2021 21:42:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=1np1BegAKf1p/qLgI0qb1yNV9cLibVUUhaOTRhnPJnw=;
        b=A5tlFUHBnzErekKRYMRnvdWYNIL1OvUkqbUEv0eeZcQEi7ttmhWvkUENOfs0yEf9mG
         yUeo9jApT8YXWX5UXxrJCJvJjWtFsrQK0uf/nUxj62+JzUkY82HgXMDI8RV3JGCUelDc
         WaCxw0xPce+SOcVem70HWFFanL8/DxQv+v6I357b/1JJkri1VDIKq93suioLezn6oyZl
         SSV7sPxCXbvQOS7QPHoHY30B9nhjP34PpRmCABKq3aG4cBVxvjCDnu8YHlnijT6LRQVU
         r/fDAjq7drtCoSWmu83m3x+h4PIZaRNDx9PXIB/kLxq8I9fXZpmIwMmd5S8FQOu8waJ3
         INqw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=1np1BegAKf1p/qLgI0qb1yNV9cLibVUUhaOTRhnPJnw=;
        b=Z91iRYXk6zoPnUk0LtFvIrDuWbH6ttySuxS1xqFy4i+WglrE32yY8KtUhf7TEVdUuc
         irUhYApac0fadNXyFVmDDfUn//1XYCd7ZlTAOXMG4VZZxX51pyVftn/bC6uv3Rd4awaG
         O8+NEeioURFZYG0c6oIKKd7aQTlS619qFO6KdsU+kyksx7fb82pzEVIAaTeBa0KlLjMn
         fJcq4s+zzjZWNe65A95eCu0WDMd4U5uvcIWhtx5drLDXsIvMutpMXcWc9S1JLDUs0X3L
         3h2+H6Rvlt7sT1IajtmR2xbQ1ej4TJCM6mf0unDga9LcoA0kj/12lrRCLNhpL/aQmiA+
         ZPQg==
X-Gm-Message-State: AOAM5301wXvGROxP3ehgI3vvEQIqD3PIfOM6Pd15o/Q5aUrQAnliueul
        u08xPp3ctszXzfstiJGwsfOy9pjDSZx1
X-Google-Smtp-Source: 
 ABdhPJy9lPu2p4WTjuNjsi58pm7E3mssgnViCFwx4cpXi2yXv9mwI+70MJBnQ3c902v6kfAT9j/I43oB1Hv6
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:8048:6a12:bd4f:a453])
 (user=vipinsh job=sendgmr) by 2002:a25:664b:: with SMTP id
 z11mr40587444ybm.437.1617079334996; Mon, 29 Mar 2021 21:42:14 -0700 (PDT)
Date: Mon, 29 Mar 2021 21:42:04 -0700
In-Reply-To: <20210330044206.2864329-1-vipinsh@google.com>
Message-Id: <20210330044206.2864329-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20210330044206.2864329-1-vipinsh@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH v4 1/3] cgroup: Add misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, mkoutny@suse.com, jacob.jun.pan@intel.com,
        rdunlap@infradead.org, thomas.lendacky@amd.com,
        brijesh.singh@amd.com, jon.grimm@amd.com, eric.vantassell@amd.com,
        pbonzini@redhat.com, hannes@cmpxchg.org, frankja@linux.ibm.com,
        borntraeger@de.ibm.com
Cc: corbet@lwn.net, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        gingell@google.com, rientjes@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Miscellaneous cgroup provides the resource limiting and tracking
mechanism for the scalar resources which cannot be abstracted like the
other cgroup resources. Controller is enabled by the CONFIG_CGROUP_MISC
config option.

A resource can be added to the controller via enum misc_res_type{} in
the include/linux/misc_cgroup.h file and the corresponding name via
misc_res_name[] in the kernel/cgroup/misc.c file. Provider of the
resource must set its capacity prior to using the resource by calling
misc_cg_set_capacity().

Once a capacity is set then the resource usage can be updated using
charge and uncharge APIs. All of the APIs to interact with misc
controller are in include/linux/misc_cgroup.h.

Miscellaneous controller provides 3 interface files. If two misc
resources (res_a and res_b) are registered then:

misc.capacity
A read-only flat-keyed file shown only in the root cgroup.  It shows
miscellaneous scalar resources available on the platform along with
their quantities::

    $ cat misc.capacity
    res_a 50
    res_b 10

misc.current
A read-only flat-keyed file shown in the non-root cgroups.  It shows
the current usage of the resources in the cgroup and its children::

    $ cat misc.current
    res_a 3
    res_b 0

misc.max
A read-write flat-keyed file shown in the non root cgroups. Allowed
maximum usage of the resources in the cgroup and its children.::

    $ cat misc.max
    res_a max
    res_b 4

Limit can be set by::

    # echo res_a 1 > misc.max

Limit can be set to max by::

    # echo res_a max > misc.max

Limits can be set more than the capacity value in the misc.capacity
file.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
---
 include/linux/cgroup_subsys.h |   4 +
 include/linux/misc_cgroup.h   | 126 +++++++++++
 init/Kconfig                  |  14 ++
 kernel/cgroup/Makefile        |   1 +
 kernel/cgroup/misc.c          | 401 ++++++++++++++++++++++++++++++++++
 5 files changed, 546 insertions(+)
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c

```
#### [GIT PULL] VFIO fixes for v5.12-rc6
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12173149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12534C433E0
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 16:46:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E278E619CD
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 16:46:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232415AbhC3QqU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 12:46:20 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42547 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232529AbhC3Qpi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 12:45:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617122738;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=zzc2KTIEFsB3osEymwowtqBBc0fZZdXcHQvsko2yUzo=;
        b=T/JBsC2ImjM4bYtOMs7VZnTt0UmqPSmm6JMCWjj9ZdXKzbN/k/pn8/2fwxG5fk/ovJSdx6
        MvEUw4Br6hqJfm9NlrJLGtjfapcoiSe84KcopZrauixshlDOPVe0R0Nfr4b07ziqPqTTP4
        0FcANRFYEAt5t0NlvrHMliRRgm30YgM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-347-ljLN9JOIOR-Zyrx8eNaKZg-1; Tue, 30 Mar 2021 12:45:36 -0400
X-MC-Unique: ljLN9JOIOR-Zyrx8eNaKZg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 944E71005D64;
        Tue, 30 Mar 2021 16:45:34 +0000 (UTC)
Received: from omen (ovpn-112-120.phx2.redhat.com [10.3.112.120])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 36EB75C1D1;
        Tue, 30 Mar 2021 16:45:34 +0000 (UTC)
Date: Tue, 30 Mar 2021 10:45:33 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>, jgg@nvidia.com,
        daniel.m.jordan@oracle.com
Subject: [GIT PULL] VFIO fixes for v5.12-rc6
Message-ID: <20210330104533.4ab8d840@omen>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 0d02ec6b3136c73c09e7859f0d0e4e2c4c07b49b:

  Linux 5.12-rc4 (2021-03-21 14:56:43 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.12-rc6

for you to fetch changes up to e0146a108ce4d2c22b9510fd12268e3ee72a0161:

  vfio/nvlink: Add missing SPAPR_TCE_IOMMU depends (2021-03-29 14:48:00 -0600)

----------------------------------------------------------------
VFIO fixes for v5.12-rc6

 - Fix pfnmap batch carryover (Daniel Jordan)

 - Fix nvlink Kconfig dependency (Jason Gunthorpe)

----------------------------------------------------------------
Daniel Jordan (1):
      vfio/type1: Empty batch for pfnmap pages

Jason Gunthorpe (1):
      vfio/nvlink: Add missing SPAPR_TCE_IOMMU depends

 drivers/vfio/pci/Kconfig        | 2 +-
 drivers/vfio/vfio_iommu_type1.c | 6 ++++++
 2 files changed, 7 insertions(+), 1 deletion(-)
```
#### [PATCH v19 1/7] arm/arm64: Probe for the presence of KVM hypervisor
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12172811
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C2418C433DB
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 14:55:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C080619CE
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 14:55:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231636AbhC3Oy5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 10:54:57 -0400
Received: from mail.kernel.org ([198.145.29.99]:55434 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231829AbhC3Oyq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 10:54:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2D765619C8;
        Tue, 30 Mar 2021 14:54:46 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lRFlU-004hoo-Hc; Tue, 30 Mar 2021 15:54:44 +0100
From: Marc Zyngier <maz@kernel.org>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com, seanjc@google.com,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com, lorenzo.pieralisi@arm.com,
        sudeep.holla@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        kernel-team@android.com
Subject: [PATCH v19 1/7] arm/arm64: Probe for the presence of KVM hypervisor
Date: Tue, 30 Mar 2021 15:54:24 +0100
Message-Id: <20210330145430.996981-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210330145430.996981-1-maz@kernel.org>
References: <20210330145430.996981-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: netdev@vger.kernel.org, yangbo.lu@nxp.com,
 john.stultz@linaro.org, tglx@linutronix.de, pbonzini@redhat.com,
 seanjc@google.com, richardcochran@gmail.com, Mark.Rutland@arm.com,
 will@kernel.org, suzuki.poulose@arm.com, Andre.Przywara@arm.com,
 steven.price@arm.com, lorenzo.pieralisi@arm.com, sudeep.holla@arm.com,
 linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, Steve.Capper@arm.com,
 justin.he@arm.com, jianyong.wu@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

Although the SMCCC specification provides some limited functionality for
describing the presence of hypervisor and firmware services, this is
generally applicable only to functions designated as "Arm Architecture
Service Functions" and no portable discovery mechanism is provided for
standard hypervisor services, despite having a designated range of
function identifiers reserved by the specification.

In an attempt to avoid the need for additional firmware changes every
time a new function is added, introduce a UID to identify the service
provider as being compatible with KVM. Once this has been established,
additional services can be discovered via a feature bitmap.

Reviewed-by: Steven Price <steven.price@arm.com>
Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
[maz: move code to its own file, plug it into PSCI]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201209060932.212364-2-jianyong.wu@arm.com
---
 arch/arm/include/asm/hypervisor.h   |  3 ++
 arch/arm64/include/asm/hypervisor.h |  3 ++
 drivers/firmware/psci/psci.c        |  2 ++
 drivers/firmware/smccc/Makefile     |  2 +-
 drivers/firmware/smccc/kvm_guest.c  | 50 +++++++++++++++++++++++++++++
 drivers/firmware/smccc/smccc.c      |  1 +
 include/linux/arm-smccc.h           | 25 +++++++++++++++
 7 files changed, 85 insertions(+), 1 deletion(-)
 create mode 100644 drivers/firmware/smccc/kvm_guest.c

```
#### [PATCH 1/4] kvm: cpuid: adjust the returned nent field of kvm_cpuid2 for KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12173575
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 37594C433C1
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 18:59:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC9D66196A
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 18:59:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232965AbhC3S7J (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 14:59:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32919 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232968AbhC3S67 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 14:58:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617130738;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=aPc+rabAZpzxBvkEBQsdws4dCgLq8Pb5mtjSkAQD3So=;
        b=ciGiYcZwJuzQN0RQJQzvG0GXSNDLa0GLDZ4sUC0LXJ8GPhXYC43CU2vjvEWHy6fxEqVobl
        MAR6g6eYg50MxxL19SzJeAdNUgmT0HQdouboPZgq+goUTRHUmykAalElgTbpdTJxCvZArs
        q8z5fIjDyg80wYgeajOGqkQv/iYjen8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-285-gAWCBbpRMLS2c762orwA8w-1; Tue, 30 Mar 2021 14:58:57 -0400
X-MC-Unique: gAWCBbpRMLS2c762orwA8w-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5CD2B8030A1;
        Tue, 30 Mar 2021 18:58:55 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-41.ams2.redhat.com
 [10.36.112.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3CEF819C44;
        Tue, 30 Mar 2021 18:58:50 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 1/4] kvm: cpuid: adjust the returned nent field of kvm_cpuid2
 for KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
Date: Tue, 30 Mar 2021 20:58:38 +0200
Message-Id: <20210330185841.44792-2-eesposit@redhat.com>
In-Reply-To: <20210330185841.44792-1-eesposit@redhat.com>
References: <20210330185841.44792-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Calling the kvm KVM_GET_[SUPPORTED/EMULATED]_CPUID ioctl requires
a nent field inside the kvm_cpuid2 struct to be big enough to contain
all entries that will be set by kvm.
Therefore if the nent field is too high, kvm will adjust it to the
right value. If too low, -E2BIG is returned.

However, when filling the entries do_cpuid_func() requires an
additional entry, so if the right nent is known in advance,
giving the exact number of entries won't work because it has to be increased
by one.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 arch/x86/kvm/cpuid.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] kvm: fix minor typos in x86/kvm.h and selftests/processor.c
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12173599
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3E752C433C1
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 19:31:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F21CD6148E
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 19:31:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233121AbhC3TbT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 15:31:19 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:37844 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233161AbhC3Tao (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 15:30:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617132643;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=eTWTr8cAwYev5yD8LuZQ3faxQx+nRJ4mRBG0w/bSeiQ=;
        b=JTfJeicYClaN2cgzqjMKbs0a+/dOjyVckVZVTj8mQiH+GtZ4TLWrVPr3SMHHhrffIildj+
        5zKkCf4kSIkXGjFyudphX/osJgZQTOcJGcKUQzbaMSNISczlWjMdmQKsWm2CK1XxinfGz8
        VwpiazQ+BTzoIfp2rHPq5ALD61qUr7g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-428-VdVI23fzMqqwbqr38R4dmQ-1; Tue, 30 Mar 2021 15:30:39 -0400
X-MC-Unique: VdVI23fzMqqwbqr38R4dmQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68F069CDA4;
        Tue, 30 Mar 2021 19:30:38 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-41.ams2.redhat.com
 [10.36.112.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 99F9719C44;
        Tue, 30 Mar 2021 19:30:36 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH] kvm: fix minor typos in x86/kvm.h and selftests/processor.c
Date: Tue, 30 Mar 2021 21:30:29 +0200
Message-Id: <20210330193029.47746-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 tools/arch/x86/include/uapi/asm/kvm.h              | 2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v6 01/10] tools/headers: sync headers of asm-generic/hugetlb_encode.h
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12171977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A5644C433E2
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 08:10:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5301D61999
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 08:10:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231521AbhC3IJr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 04:09:47 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:15104 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231338AbhC3IJN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 04:09:13 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4F8hqs4Htrz19Jq2;
        Tue, 30 Mar 2021 16:07:05 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 30 Mar 2021 16:08:59 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kselftest@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Ben Gardon <bgardon@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Peter Xu <peterx@redhat.com>, "Ingo Molnar" <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v6 01/10] tools/headers: sync headers of
 asm-generic/hugetlb_encode.h
Date: Tue, 30 Mar 2021 16:08:47 +0800
Message-ID: <20210330080856.14940-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210330080856.14940-1-wangyanan55@huawei.com>
References: <20210330080856.14940-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch syncs contents of tools/include/asm-generic/hugetlb_encode.h
and include/uapi/asm-generic/hugetlb_encode.h. Arch powerpc supports 16KB
hugepages and ARM64 supports 32MB/512MB hugepages. The corresponding mmap
flags have already been added in include/uapi/asm-generic/hugetlb_encode.h,
but not tools/include/asm-generic/hugetlb_encode.h.

Cc: Ingo Molnar <mingo@kernel.org>
Cc: Adrian Hunter <adrian.hunter@intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@redhat.com>
Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 tools/include/asm-generic/hugetlb_encode.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/2] KVM: x86: reduce pvclock_gtod_sync_lock critical sections
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12173161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7CD4FC433E0
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 17:00:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DE3A619CD
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 17:00:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232319AbhC3RAU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 13:00:20 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:48277 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231910AbhC3RAE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 13:00:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617123603;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Ia9RiC+ShFIXJPCH922QqvDmZ58hKqtXlB2NuN0+x8M=;
        b=jMaEr3z2tzu7Yex7Dc8WkvKTJyev9ro4baa72U43JMzjmnW3tT+g6R4VG/se2F7cPJ8/iL
        q274IoPLN6c2hAWwdPof/A2PAxBH/8bd6GbNU8+n/iZfp2lZPu0dKl89tnC9quOfQU1N+W
        Aik1s+w1Rch3iwX+tgQceqLX3vH+m7o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-451-ZI0GqeLDP0GB28ZlAJTShA-1; Tue, 30 Mar 2021 13:00:01 -0400
X-MC-Unique: ZI0GqeLDP0GB28ZlAJTShA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 28023190A7A2;
        Tue, 30 Mar 2021 17:00:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A9BB163B8C;
        Tue, 30 Mar 2021 16:59:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mtosatti@redhat.com, vkuznets@redhat.com, dwmw@amazon.co.uk
Subject: [PATCH 1/2] KVM: x86: reduce pvclock_gtod_sync_lock critical sections
Date: Tue, 30 Mar 2021 12:59:57 -0400
Message-Id: <20210330165958.3094759-2-pbonzini@redhat.com>
In-Reply-To: <20210330165958.3094759-1-pbonzini@redhat.com>
References: <20210330165958.3094759-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no need to include changes to vcpu->requests into
the pvclock_gtod_sync_lock critical section.  The changes to
the shared data structures (in pvclock_update_vm_gtod_copy)
already occur under the lock.

Cc: David Woodhouse <dwmw@amazon.co.uk>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 10 ++++------
 1 file changed, 4 insertions(+), 6 deletions(-)

```
#### [PATCH v3 1/3] Linux headers: update from 5.12-rc3
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12172177
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8936FC433DB
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 09:55:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CE2D61996
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 09:55:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231269AbhC3Jyh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 05:54:37 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:27544 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231574AbhC3Jyf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 05:54:35 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12U9YQaT065994;
        Tue, 30 Mar 2021 05:54:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XH41vIKQPXVPDTcuOx2GPyt+VwfndhJWpB7omC2dJ1U=;
 b=UGKxucPHGezdLa/vceCeSgJZPIgaC/hvhlPaBrfMWlaht86jzDBPK+nJi8dWMI99gMMo
 bQL/48fo/9RJ/Kt8kArpWJY4f8Yr6fEcnyDYYzAhWupDIMSv2A1x66Yt20+75n9yMLOL
 NlIokm/F2TMb5UGaSo3acBMsv1zyzPGBlIODmpVD5B4lhs8FthlHsw4tda+acxlzLAXp
 4W9BVFUWWV1ZB+JFswZjDNcboIPcIB/smvMvv6H7rkQRzHsVrEmpPa5djEWTWiHXGloj
 AXTPL5a6neyDd/bTU0UcvWFo4YIqurlQwMos5l8Pg0td+No34rkbU7aBSRXKLsTskWo1 qw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhm5m081-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 05:54:13 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12U9bBSP075212;
        Tue, 30 Mar 2021 05:54:12 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhm5m067-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 05:54:12 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12U9qc2x029753;
        Tue, 30 Mar 2021 09:54:10 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 37hvb8jjv1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 09:54:10 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12U9s7ef44106098
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 30 Mar 2021 09:54:07 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A871652052;
        Tue, 30 Mar 2021 09:54:07 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.47.23])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 7FD7D52050;
        Tue, 30 Mar 2021 09:54:04 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Subject: [PATCH v3 1/3] Linux headers: update from 5.12-rc3
Date: Tue, 30 Mar 2021 15:23:48 +0530
Message-Id: <20210330095350.36309-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210330095350.36309-1-ravi.bangoria@linux.ibm.com>
References: <20210330095350.36309-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: ejY37gtjE28i7w1fDsWRjjdmVf0fP8i2
X-Proofpoint-ORIG-GUID: oD0AdYhTtF_1lraPI13sQI8nP1ozZwrD
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-30_03:2021-03-26,2021-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 clxscore=1015
 spamscore=0 lowpriorityscore=0 phishscore=0 impostorscore=0 suspectscore=0
 priorityscore=1501 mlxlogscore=999 malwarescore=0 bulkscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103250000
 definitions=main-2103300066
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update against Linux 5.12-rc3

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 18 files changed, 161 insertions(+), 4 deletions(-)

```
