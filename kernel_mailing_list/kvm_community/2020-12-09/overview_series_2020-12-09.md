#### [Patch v3 1/2] cgroup: svm: Add Encryption ID controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11962555
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4DC78C4361B
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:56:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B5EF23B99
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:56:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733305AbgLIUz3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:55:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39684 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733214AbgLIUzT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 15:55:19 -0500
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB9B4C0617A7
        for <kvm@vger.kernel.org>; Wed,  9 Dec 2020 12:54:28 -0800 (PST)
Received: by mail-pl1-x649.google.com with SMTP id x12so1516858plr.21
        for <kvm@vger.kernel.org>; Wed, 09 Dec 2020 12:54:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=4wPvcXyrHKFSqikUYQ+f3mRJdXUxg4ovbfoSv1htTY8=;
        b=oP2KIHv0nY4YExgDPf5qblS4r/e9dzuqfV5OyerXg5CQdlobnqXCRRYjW71kHWNVB+
         WtZ3LZTKgMy92tJRZwWA6ay7AICpmLknbKbzBQX1+s3WqWpd5GmzVJSHe7ofktbRLXZL
         Bt8Z9YnM993yaB4VybhxwDpF9nIyO3Sz7e0anQrXI43P26Yb6pH8EpQcNWSxgWtJbda9
         oj2TP1cE04Y1c1FGztW5CWFU3bMd1gC8nFTOpoTeag4LZnCxQNDu3n8Osaygybab03j0
         SIOW/JbgyW3OZA6IKKjvm77gqyycOXUeHBukg6jBRBbEH3tuSmOe3Wx/h2JqFI2n0Ni2
         XluQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=4wPvcXyrHKFSqikUYQ+f3mRJdXUxg4ovbfoSv1htTY8=;
        b=rI1+YRYFp8nbxHQ3/kscRk5bv11sqwBfvCTAEl8MAuHLl5yHKf67e4WbIUegQwEhwj
         eEXeyElfJUIYeEeGLzjWbLwCzIA59Swq5O2M3NHNqPouPbAAK0ELUO8ZjVQq8MC7iuQ4
         v9Ebn5JXzjwx3d9kgg03r0fMygymLuhQf38SUgPDYWLpvN0sid2b6ItcWWSM0d7+byHu
         cLFXkwYN4Sjbxa+M3/Xv+q/0p9mERV4BlReNLrF28AAZw/v9+C8t5mE6l/H7zw0ReLnE
         y4hBEFE7EX8XH5cZWUXUATS04m1lIqOoCxEQYblrXrYu/jDjaxSFty/AIkbWsfUpROtB
         PpHQ==
X-Gm-Message-State: AOAM533osXKJqUdfZkb/S/6s2QSe5kgIGF76J52aKZuHlvU+GA5sGFoP
        29aZTvIsSdbHnf5Agg92U5xDtEC8Ug37
X-Google-Smtp-Source: 
 ABdhPJwtoyUBRkssYi/MYaMOhZFvZuw68rIPJjzZmJLOOxgJkjHrYQVZN2cxqKxps7cdehirWem980W1qOoq
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:aa7:96d8:0:b029:19e:bc79:cf7 with SMTP id
 h24-20020aa796d80000b029019ebc790cf7mr396004pfq.22.1607547268068; Wed, 09 Dec
 2020 12:54:28 -0800 (PST)
Date: Wed,  9 Dec 2020 12:54:12 -0800
In-Reply-To: <20201209205413.3391139-1-vipinsh@google.com>
Message-Id: <20201209205413.3391139-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20201209205413.3391139-1-vipinsh@google.com>
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [Patch v3 1/2] cgroup: svm: Add Encryption ID controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>,
        kernel test robot <lkp@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardware memory encryption is available on multiple generic CPUs. For
example AMD has Secure Encrypted Virtualization (SEV) and SEV -
Encrypted State (SEV-ES).

These memory encryptions are useful in creating encrypted virtual
machines (VMs) and user space programs.

There are limited number of encryption IDs that can be used
simultaneously on a machine for encryption. This generates a need for
the system admin to track, limit, allocate resources, and optimally
schedule VMs and user workloads in the cloud infrastructure. Some
malicious programs can exhaust all of these resources on a host causing
starvation of other workloads.

Encryption ID controller allows control of these resources using
Cgroups.

Controller is enabled by CGROUP_ENCRYPTION_IDS config option.
Encryption controller provide 3 interface files for each encryption ID
type. For example, in SEV:

1. encryption_ids.sev.stat
	Shown only at the root cgroup. Displays total SEV IDs available
	on the platform and current usage count.
2. encrpytion_ids.sev.max
	Sets the maximum usage of SEV IDs in the cgroup.
3. encryption_ids.sev.current
	Current usage of SEV IDs in the cgroup and its children.

Other ID types can be easily added in the controller in the same way.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
Reviewed-by: Dionna Glaze <dionnaglaze@google.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 arch/x86/kvm/svm/sev.c                |  28 +-
 include/linux/cgroup_subsys.h         |   4 +
 include/linux/encryption_ids_cgroup.h |  71 +++++
 include/linux/kvm_host.h              |   4 +
 init/Kconfig                          |  14 +
 kernel/cgroup/Makefile                |   1 +
 kernel/cgroup/encryption_ids.c        | 430 ++++++++++++++++++++++++++
 7 files changed, 545 insertions(+), 7 deletions(-)
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c

```
#### [PATCH v16 1/9] arm64: Probe for the presence of KVM hypervisor
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11960551
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D38FC433FE
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 06:13:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D14623440
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 06:13:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727839AbgLIGKq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 01:10:46 -0500
Received: from foss.arm.com ([217.140.110.172]:57780 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725892AbgLIGKq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 01:10:46 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 92EBC139F;
        Tue,  8 Dec 2020 22:10:00 -0800 (PST)
Received: from entos-thunderx2-desktop.shanghai.arm.com
 (entos-thunderx2-desktop.shanghai.arm.com [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 685C73F66B;
        Tue,  8 Dec 2020 22:09:54 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v16 1/9] arm64: Probe for the presence of KVM hypervisor
Date: Wed,  9 Dec 2020 14:09:24 +0800
Message-Id: <20201209060932.212364-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201209060932.212364-1-jianyong.wu@arm.com>
References: <20201209060932.212364-1-jianyong.wu@arm.com>
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

Change from Jianyong Wu:
mv kvm_arm_hyp_service_available to common place to let both arm/arm64 touch it.
add kvm_init_hyp_services also under arm arch to let arm kvm guest use this service.

Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 arch/arm/kernel/setup.c        |  5 ++++
 arch/arm64/kernel/setup.c      |  1 +
 drivers/firmware/smccc/smccc.c | 37 +++++++++++++++++++++++++++++
 include/linux/arm-smccc.h      | 43 ++++++++++++++++++++++++++++++++++
 4 files changed, 86 insertions(+)

```
#### [PATCH v1] vfio: platform: enable compile test
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
X-Patchwork-Id: 11962495
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 813B4C4361B
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:31:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5689A23B99
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:31:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728716AbgLIUbL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:31:11 -0500
Received: from mga14.intel.com ([192.55.52.115]:64821 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729187AbgLIUbA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 15:31:00 -0500
IronPort-SDR: 
 FainkkfyZHrCTKH65VHQjJOLtS7U6cYfS5o8NkPbcE/0g2pG0ae+A/uKNSN3IFG425QE2USmyT
 4FdzGSz2d3Fw==
X-IronPort-AV: E=McAfee;i="6000,8403,9830"; a="173383197"
X-IronPort-AV: E=Sophos;i="5.78,405,1599548400";
   d="scan'208";a="173383197"
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Dec 2020 12:29:11 -0800
IronPort-SDR: 
 OWkzm9C0bxeDUxcMr0BM9sPClVzq9KjA/tYUzOTRk6jgqAV6Qj2bc0Slp8OaPaWAHq0BABFsDY
 AJv/bGpAnx7w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,405,1599548400";
   d="scan'208";a="552771422"
Received: from black.fi.intel.com ([10.237.72.28])
  by orsmga005.jf.intel.com with ESMTP; 09 Dec 2020 12:29:10 -0800
Received: by black.fi.intel.com (Postfix, from userid 1003)
        id 831801C8; Wed,  9 Dec 2020 22:29:09 +0200 (EET)
From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
To: Eric Auger <eric.auger@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        kvm@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Cc: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
Subject: [PATCH v1] vfio: platform: enable compile test
Date: Wed,  9 Dec 2020 22:29:08 +0200
Message-Id: <20201209202908.61658-1-andriy.shevchenko@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enable compile test of the VFIO platform code.

Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
---
 drivers/vfio/platform/Kconfig | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/5] driver core: platform: Introduce platform_get_mem_or_io()
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
X-Patchwork-Id: 11962519
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A368FC433FE
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:39:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70CD923C85
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:39:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730595AbgLIUii (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:38:38 -0500
Received: from mga04.intel.com ([192.55.52.120]:10548 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729213AbgLIUii (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 15:38:38 -0500
IronPort-SDR: 
 7giOMYbGVopHkmni2utGr3G5+ExGrdo8XsGwLQZelc2ZBvQg5emAEvIlAuNESXZxRGFIMnfh8/
 wVf6qW/6GLuw==
X-IronPort-AV: E=McAfee;i="6000,8403,9830"; a="171570350"
X-IronPort-AV: E=Sophos;i="5.78,405,1599548400";
   d="scan'208";a="171570350"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Dec 2020 12:36:46 -0800
IronPort-SDR: 
 FeNYAK3Gyy9HFFGiBtyTiMiIK1351ysdS6Fwu4Q7OrbwlpLs2gX2ZKgIkft8+dRAEFoSAR07FS
 SNLGDb5nusIA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,405,1599548400";
   d="scan'208";a="542523753"
Received: from black.fi.intel.com ([10.237.72.28])
  by fmsmga005.fm.intel.com with ESMTP; 09 Dec 2020 12:36:44 -0800
Received: by black.fi.intel.com (Postfix, from userid 1003)
        id 7C8641C8; Wed,  9 Dec 2020 22:36:43 +0200 (EET)
From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
To: Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        linux-kernel@vger.kernel.org
Cc: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        kvm@vger.kernel.org, linux-usb@vger.kernel.org,
        Peng Hao <peng.hao2@zte.com.cn>, Arnd Bergmann <arnd@arndb.de>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH v2 1/5] driver core: platform: Introduce
 platform_get_mem_or_io()
Date: Wed,  9 Dec 2020 22:36:38 +0200
Message-Id: <20201209203642.27648-1-andriy.shevchenko@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are at least few existing users of the proposed API which
retrieves either MEM or IO resource from platform device.

Make it common to utilize in the existing and new users.

Cc: Eric Auger <eric.auger@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: kvm@vger.kernel.org
Cc: linux-usb@vger.kernel.org
Cc: Peng Hao <peng.hao2@zte.com.cn>
Cc: Arnd Bergmann <arnd@arndb.de>
Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
v2: moved to C-file and renamed for the sake of consistency with the rest
    platform code

 drivers/base/platform.c         | 15 +++++++++++++++
 include/linux/platform_device.h |  3 +++
 2 files changed, 18 insertions(+)

```
#### [PATCH v4 1/1] vfio/type1: Add vfio_group_iommu_domain()
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11960149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EF41DC433FE
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 01:54:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7054238EB
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 01:54:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726250AbgLIByI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 20:54:08 -0500
Received: from mga11.intel.com ([192.55.52.93]:50399 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725283AbgLIByI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Dec 2020 20:54:08 -0500
IronPort-SDR: 
 g3Vq3VUV6ba3QM4jti/tITZY1Y4vDeG0ud/sfx2x4T1K+NlDSI5Z7POvxIDTKqbnqPcewuRG67
 7LWesUq7QTyQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9829"; a="170493420"
X-IronPort-AV: E=Sophos;i="5.78,404,1599548400";
   d="scan'208";a="170493420"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Dec 2020 17:52:22 -0800
IronPort-SDR: 
 p9GFQc1L7/h6pbmnpMG4Am+qXvFd6Zl3fTnwJGN3OBiNcEQkmNyUac0raGFIqVqQPy119057Rt
 c2Hw6pi3fkgg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,404,1599548400";
   d="scan'208";a="367998068"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga004.fm.intel.com with ESMTP; 08 Dec 2020 17:52:18 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v4 1/1] vfio/type1: Add vfio_group_iommu_domain()
Date: Wed,  9 Dec 2020 09:44:44 +0800
Message-Id: <20201209014444.332772-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the API for getting the domain from a vfio group. This could be used
by the physical device drivers which rely on the vfio/mdev framework for
mediated device user level access. The typical use case like below:

	unsigned int pasid;
	struct vfio_group *vfio_group;
	struct iommu_domain *iommu_domain;
	struct device *dev = mdev_dev(mdev);
	struct device *iommu_device = mdev_get_iommu_device(dev);

	if (!iommu_device ||
	    !iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
		return -EINVAL;

	vfio_group = vfio_group_get_external_user_from_dev(dev);
	if (IS_ERR_OR_NULL(vfio_group))
		return -EFAULT;

	iommu_domain = vfio_group_iommu_domain(vfio_group);
	if (IS_ERR_OR_NULL(iommu_domain)) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	pasid = iommu_aux_get_pasid(iommu_domain, iommu_device);
	if (pasid < 0) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	/* Program device context with pasid value. */
	...

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/vfio.c             | 18 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 24 ++++++++++++++++++++++++
 include/linux/vfio.h            |  4 ++++
 3 files changed, 46 insertions(+)

Change log:
 - v3: https://lore.kernel.org/linux-iommu/20201201012328.2465735-1-baolu.lu@linux.intel.com/
 - Changed according to comments @ https://lore.kernel.org/linux-iommu/20201202144834.1dd0983e@w520.home/
   - Rename group_domain to group_iommu_domain;
   - Remove an unnecessary else branch.

```
#### [RFC 1/4] s390/pci: track alignment/length strictness for zpci_dev
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11962493
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95DDDC4167B
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:30:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 645FA22B39
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:30:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388570AbgLIUaT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:30:19 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:6860 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387663AbgLIU36 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 9 Dec 2020 15:29:58 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B9KCmPm171107;
        Wed, 9 Dec 2020 15:29:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Ll19ePRbwoEsUoHXPbtitX6SHMdAUB9AHe5X2OcjHU8=;
 b=J1419j+jfIh9qofTLjUfl/UKmjhRo27Sq/elTRn0Z0SjmZ7pb6ATHmubxTIr5+OYrvQt
 prn8a+u0CmhFvXfhI7++SYJVPlE0NEs6n+pvNzcPqysGQ6kXym2lJ6AY1n5wHO0OcO3d
 vFXSmvwmU6vFtC0oc+M7PP1tm73ASW9zta5YR6QBnp25kwhFn9onp0QPyF4sLAmyI23o
 yKjjQjpODm2QXfnqx73YDeJtt7qJJhimEcJZvx9gYETH2Rv+QQ0F70fXsf6WBtoH42Rq
 kvZ2rGP54/4HT9G6m6dfivQBSxoN3yr6jfTaCaO12C2a6iXwGOF7KSxw4y36rgKYGlcH lA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35avp1pys3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 15:29:17 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B9KLIMd007118;
        Wed, 9 Dec 2020 15:29:17 -0500
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35avp1pyrq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 15:29:17 -0500
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B9KMAL7015879;
        Wed, 9 Dec 2020 20:29:16 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma01wdc.us.ibm.com with ESMTP id 3581u9gdy1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 20:29:16 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0B9KRxWU29884698
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 9 Dec 2020 20:27:59 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1CE64B2068;
        Wed,  9 Dec 2020 20:27:59 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EE889B2066;
        Wed,  9 Dec 2020 20:27:56 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.37.122])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  9 Dec 2020 20:27:56 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC 1/4] s390/pci: track alignment/length strictness for zpci_dev
Date: Wed,  9 Dec 2020 15:27:47 -0500
Message-Id: <1607545670-1557-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1607545670-1557-1-git-send-email-mjrosato@linux.ibm.com>
References: <1607545670-1557-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-09_16:2020-12-09,2020-12-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 impostorscore=0 malwarescore=0 clxscore=1015 suspectscore=0
 mlxscore=0 spamscore=0 priorityscore=1501 bulkscore=0 phishscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012090140
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some zpci device types (e.g., ISM) follow different rules for length
and alignment of pci instructions.  Recognize this and keep track of
it in the zpci_dev.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Reviewed-by: Niklas Schnelle <schnelle@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/pci.h     | 3 ++-
 arch/s390/include/asm/pci_clp.h | 4 +++-
 arch/s390/pci/pci_clp.c         | 1 +
 3 files changed, 6 insertions(+), 2 deletions(-)

```
