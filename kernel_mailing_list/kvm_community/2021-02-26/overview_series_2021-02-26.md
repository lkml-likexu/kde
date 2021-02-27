#### [PATCH v7 1/6] target/i386: Change XSAVE related feature-word names
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12105643
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 917CFC433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 02:10:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 321C264EFA
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 02:10:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229800AbhBZCKK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 21:10:10 -0500
Received: from mga03.intel.com ([134.134.136.65]:38817 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229498AbhBZCKJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 21:10:09 -0500
IronPort-SDR: 
 bAex37otdPAZZOEWOxBkDyVihQqY3UTDGDs8ZfOyy040bsNPqZXtU6LhBSJwkJmoYeQ4Jx9tB+
 dcFcRPVUSAGA==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="185800998"
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="185800998"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Feb 2021 18:09:28 -0800
IronPort-SDR: 
 bjxgzeF6JzUJvY+97ND+UZZ8321fSgbVuxHpTasxMTYoKWPQrp3t/mcZWYUPaCKZYopX/0jmow
 tZDhYwDD6zgQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="404679946"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by orsmga008.jf.intel.com with ESMTP; 25 Feb 2021 18:09:26 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, richard.henderson@linaro.org,
        ehabkost@redhat.com, mtosatti@redhat.com,
        sean.j.christopherson@intel.com, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v7 1/6] target/i386: Change XSAVE related feature-word names
Date: Fri, 26 Feb 2021 10:20:53 +0800
Message-Id: <20210226022058.24562-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210226022058.24562-1-weijiang.yang@intel.com>
References: <20210226022058.24562-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename XSAVE related feature-words for introducing XSAVES related
feature-words.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 target/i386/cpu.c | 24 ++++++++++++------------
 target/i386/cpu.h |  4 ++--
 2 files changed, 14 insertions(+), 14 deletions(-)

```
#### [Patch V2 01/13] x86/irq: Add DEV_MSI allocation type
##### From: Megha Dey <megha.dey@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Megha Dey <megha.dey@intel.com>
X-Patchwork-Id: 12107283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9C368C433E6
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 20:14:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E70664E38
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 20:14:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230124AbhBZUOB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 15:14:01 -0500
Received: from mga17.intel.com ([192.55.52.151]:35678 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230260AbhBZUM3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 15:12:29 -0500
IronPort-SDR: 
 YxRkBkRDTArFCioc32kKUAUcGXZYE0SnSSTw0giS+I+82H/b0aLAj2OumLreeSpcoCulplPFTK
 iVR2y6n75ZuQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9907"; a="165846880"
X-IronPort-AV: E=Sophos;i="5.81,209,1610438400";
   d="scan'208";a="165846880"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 12:11:11 -0800
IronPort-SDR: 
 bv3dIM+IbW13OExEYSXo0hhvv1rA5nhUWMSWlIzU/auQPUWDKDSD5QG824i1vJGPgpNSm87Anc
 802IjYYcsKGQ==
X-IronPort-AV: E=Sophos;i="5.81,209,1610438400";
   d="scan'208";a="405109416"
Received: from megha-z97x-ud7-th.sc.intel.com ([143.183.85.154])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-SHA;
 26 Feb 2021 12:11:10 -0800
From: Megha Dey <megha.dey@intel.com>
To: tglx@linutronix.de
Cc: linux-kernel@vger.kernel.org, dave.jiang@intel.com,
        ashok.raj@intel.com, kevin.tian@intel.com, dwmw@amazon.co.uk,
        x86@kernel.org, tony.luck@intel.com, dan.j.williams@intel.com,
        megha.dey@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        iommu@lists.linux-foundation.org, alex.williamson@redhat.com,
        bhelgaas@google.com, maz@kernel.org, linux-pci@vger.kernel.org,
        baolu.lu@linux.intel.com, ravi.v.shankar@intel.com
Subject: [Patch V2 01/13] x86/irq: Add DEV_MSI allocation type
Date: Fri, 26 Feb 2021 12:11:05 -0800
Message-Id: <1614370277-23235-2-git-send-email-megha.dey@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1614370277-23235-1-git-send-email-megha.dey@intel.com>
References: <1614370277-23235-1-git-send-email-megha.dey@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

For the upcoming device MSI support a new allocation type is
required.

Reviewed-by: Tony Luck <tony.luck@intel.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Megha Dey <megha.dey@intel.com>
---
 arch/x86/include/asm/hw_irq.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: Documentation: Fix index for KVM_CAP_PPC_DAWR1
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12106261
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E5D81C433E6
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 09:49:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E2CA64EB7
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 09:49:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230400AbhBZJtb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 04:49:31 -0500
Received: from mga03.intel.com ([134.134.136.65]:41195 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230292AbhBZJtZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 04:49:25 -0500
IronPort-SDR: 
 Uo81ltxHP9kJPszsP06w/KvOs6C4MZqEkrYdbPPNs0g9j4uo07eN94IKhe+jpRGdQeZZKh60wb
 u46xK2wMurpg==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="185882641"
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="185882641"
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 01:48:44 -0800
IronPort-SDR: 
 wz3J5nREN8FYG6yk1HK8EEoVt29n6/JZczKHTIWeO8OxURIh1jbT9iYeCVcg14crLCDixbjY2U
 87Pimi4qa0EQ==
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="365793283"
Received: from ciparjol-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.230.175])
  by orsmga003-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 01:48:42 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, linux-doc@vger.kernel.org
Cc: pbonzini@redhat.com, corbet@lwn.net,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH] KVM: Documentation: Fix index for KVM_CAP_PPC_DAWR1
Date: Fri, 26 Feb 2021 22:48:32 +1300
Message-Id: <20210226094832.380394-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It should be 7.23 instead of 7.22, which has already been taken by
KVM_CAP_X86_BUS_LOCK_EXIT.

Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: Documentation: rectify rst markup in kvm_run->flags
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12105969
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA23FC433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 07:53:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6023564EE1
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 07:53:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230019AbhBZHx2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 02:53:28 -0500
Received: from mga14.intel.com ([192.55.52.115]:37006 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229800AbhBZHx1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 02:53:27 -0500
IronPort-SDR: 
 mLrEcBkzPIr+vDDeeuGV5SXYyQB01Com7YTau375syMxkCaUvHtzMDGUMMgoJn8qv12CyszAWB
 rUU1l8uMZnrQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="185118894"
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="185118894"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Feb 2021 23:52:46 -0800
IronPort-SDR: 
 EgQBwrnMWF0ZF+1qC1DNq57FF0ROm0nZzUn5xBIEH0yhP9YyNd0DLRFAVQLnbR96GGWsly9/PX
 zW4Csgc/frdA==
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="404797767"
Received: from chenyi-pc.sh.intel.com ([10.239.159.24])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Feb 2021 23:52:33 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Stephen Rothwell <sfr@canb.auug.org.au>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: Documentation: rectify rst markup in kvm_run->flags
Date: Fri, 26 Feb 2021 15:55:41 +0800
Message-Id: <20210226075541.27179-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c32b1b896d2a ("KVM: X86: Add the Document for
KVM_CAP_X86_BUS_LOCK_EXIT") added a new flag in kvm_run->flags
documentation, and caused warning in make htmldocs:

  Documentation/virt/kvm/api.rst:5004: WARNING: Unexpected indentation
  Documentation/virt/kvm/api.rst:5004: WARNING: Inline emphasis start-string without end-string

Fix this rst markup issue.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 Documentation/virt/kvm/api.rst | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: flush deferred static key before checking it
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12106413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E743C433E6
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 10:12:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 236BD64EED
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 10:12:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231147AbhBZKM2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 05:12:28 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37626 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231151AbhBZKKZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Feb 2021 05:10:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614334139;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=G43y8SBbvkYh1R+y/15Z6f9RmEMjkgNDToKDDC5hPAE=;
        b=Q/m6eU1raym/Sgyr0O+42fgD7itP8gT7mXrC2R816T7GGL1s+htEbR4OVtLany0fdlDx42
        GbdZ58Jr4b88tdOGYyAU2hhD97vMNmCgwyBaKFaC40M/mqBww1iAk4u75HucNMn1snF2jf
        steAiv974pN13GWTnocwWnd0kBQ+7rU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-gZGwslxfNUesa8OLxzqTqQ-1; Fri, 26 Feb 2021 05:08:55 -0500
X-MC-Unique: gZGwslxfNUesa8OLxzqTqQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B6F5980196C;
        Fri, 26 Feb 2021 10:08:54 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4FC6F18A77;
        Fri, 26 Feb 2021 10:08:54 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: David Woodhouse <dwmw@amazon.co.uk>
Subject: [PATCH] KVM: flush deferred static key before checking it
Date: Fri, 26 Feb 2021 05:08:53 -0500
Message-Id: <20210226100853.75344-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A missing flush would cause the static branch to trigger incorrectly.

Cc: David Woodhouse <dwmw@amazon.co.uk>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH v6 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12106537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3A60AC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:15:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E6B8064E38
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:15:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230296AbhBZMPf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 07:15:35 -0500
Received: from mga07.intel.com ([134.134.136.100]:15306 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230268AbhBZMPY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 07:15:24 -0500
IronPort-SDR: 
 bGsjPoaK177xCgDyx2MBCe10TBQZMKiq6othpXF3MZIJ8iYpmfKwfMc7T1iC3Z6X+Vlffa1NI8
 tX0ah+DBVpRQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="249915842"
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="249915842"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 04:14:43 -0800
IronPort-SDR: 
 xikXoOcImzQNKVndi3B4Ze+f3WBj9kFUaBZITPIvN0YHNZb+si+EHr7fc77euwGfuZlONA4wjP
 MsoyMda5knpQ==
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="598420320"
Received: from ciparjol-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.230.175])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 04:14:40 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH v6 01/25] x86/cpufeatures: Make SGX_LC feature bit depend
 on SGX bit
Date: Sat, 27 Feb 2021 01:14:27 +1300
Message-Id: 
 <73a1b26037dd48244be6084e39825a9926ff98ed.1614338774.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1614338774.git.kai.huang@intel.com>
References: <cover.1614338774.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM/SVM: Move vmenter.S exception fixups out of line
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 12106641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F29DC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:57:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2C3F64EDB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:57:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229894AbhBZM5H (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 07:57:07 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59930 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229545AbhBZM5G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 07:57:06 -0500
Received: from mail-ed1-x52f.google.com (mail-ed1-x52f.google.com
 [IPv6:2a00:1450:4864:20::52f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E4F2FC061574;
        Fri, 26 Feb 2021 04:56:25 -0800 (PST)
Received: by mail-ed1-x52f.google.com with SMTP id cf12so10011064edb.8;
        Fri, 26 Feb 2021 04:56:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=jaergPFFsfPW93kbmHCbVQ0vZ9RjLcsMl8m5iUEbS3E=;
        b=FFpcIOsV0q6mKbXaHG8rv7+yS3t+c7qga/dKvM4bQKkru+hax+Z2EMhUgVkhgRSgqG
         VMlVcfkYbIVhkv71eSZKDfrJKgGxrh5LEHCgqpcU9xI0VOxCtXm3qJA04qUFOcYcUos5
         heCT+b0WDoMeu2OhW5SzQ5K4bEbRqLJjf54WZ2HWPpHaXzlZDhe7vbu3g9Dp4gSiT14b
         qwrdNhWXqaPU35zYf4vjYk+eiUYrn3D8iLzmoTTaRIFAUXFo/bC4jEHqLj4kuLmN7UQ/
         crH3PjwUFnk2qrL1qOBZOOvDppdehpPkcfIDGLl3yp8XXyHMIZbluIX1khFJvS7PuNSH
         ke3w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=jaergPFFsfPW93kbmHCbVQ0vZ9RjLcsMl8m5iUEbS3E=;
        b=G5jdvD8w9DZXvRukab8VIP8yQZi7eao/QRiYh0MIuK2SiwtNM+HooQlLiDZ2novxU+
         7bhaHbG+TkHiI2Y6f0G/sRzLgDhfQtTJwcs//QlafEwHYuKMWsmlVfmBtvFPOWmMn56F
         AgePLs+Y1NYp4R59nD/bMZ9Ez+cEn2Bv094W1JI3xECPp+LvH5oQZPyObo2zgSwmTQIX
         1RxfR+GOe67lmbd1QDrgf0bCknS6ZomwSXHDiSudr8b9RwG0bcFQVrKOkwU84IasP7KV
         3FmHhJKKOsgnVkgDfCxLI4FX746igxsKI/ugtUEksYTA5Tq/Vsbe2+LD8QF7UFPq3/n1
         1ycQ==
X-Gm-Message-State: AOAM530WTN8TOEc5ytcdta9ZaMsk5F6Cfe/rWOoCPq2nuPHC66RfbOqE
        YbcfYztbcacDjPW1tNv84MFtnI8d2Ga6wA==
X-Google-Smtp-Source: 
 ABdhPJxx+Mt2qgGNb6QwegwSCbm5VrKR19qYN+VGhqPn8DAOgv2ASvaOX+razj8v/hKJUDx61HtkEA==
X-Received: by 2002:a05:6402:1aca:: with SMTP id
 ba10mr3164723edb.6.1614344184418;
        Fri, 26 Feb 2021 04:56:24 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 bn2sm5270463ejb.35.2021.02.26.04.56.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 26 Feb 2021 04:56:23 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM/SVM: Move vmenter.S exception fixups out of line
Date: Fri, 26 Feb 2021 13:56:21 +0100
Message-Id: <20210226125621.111723-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Avoid jump by moving exception fixups out of line.

Cc: Sean Christopherson <seanjc@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/vmenter.S | 35 ++++++++++++++++++++---------------
 1 file changed, 20 insertions(+), 15 deletions(-)

```
#### [PATCH kvm-unit-tests] KVM: svm: add a test to observe the gain from clean bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12106995
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6420EC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 17:03:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B66464EC4
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 17:03:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229791AbhBZRDy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 12:03:54 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28207 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229598AbhBZRDw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Feb 2021 12:03:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614358945;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=g3BvVTqRZcHNF2bumxV68Pob+1+419O+zr+luXDJ/Hw=;
        b=Lti730L46J4eckU8bFO0nzJD0/hJ+tR9WKPp2KOCKmiSYuadjGKP6ksA+0qL/9mDgSmwjj
        ofINtrMNhCdH53CYoHA/RyRyYTQJ2zCMXfimeDijk+dLJcoN/a+gdqXVsJsVEa8NzoTJmz
        EM9wFuOSngSF5rQsa8a5VYZS/Ab1xNM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-502-3BbK47cxMPiVi7l1ogcxdQ-1; Fri, 26 Feb 2021 12:02:23 -0500
X-MC-Unique: 3BbK47cxMPiVi7l1ogcxdQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CDC081005501
        for <kvm@vger.kernel.org>; Fri, 26 Feb 2021 17:02:22 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 99E0560875
        for <kvm@vger.kernel.org>; Fri, 26 Feb 2021 17:02:22 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] KVM: svm: add a test to observe the gain from
 clean bits
Date: Fri, 26 Feb 2021 12:02:22 -0500
Message-Id: <20210226170222.227577-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.h       | 24 +++++++++++++++++++++---
 x86/svm_tests.c |  9 +++++++++
 2 files changed, 30 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: allow compiling out the Xen hypercall interface
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12106415
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6F5C6C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 10:17:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 250F764EC4
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 10:17:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230472AbhBZKRf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 05:17:35 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:22008 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231127AbhBZKPx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Feb 2021 05:15:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614334466;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Z39kMRj5F+w7GwQjo6RQskikMPrjcYP4QGKdBa2Y9ZQ=;
        b=COk74D9pqSVmR6Ib7jcHiEQcYm0cabb8o7eKyCgsuzNgcAT3bZ+Jwv2uqhkBzRQnVDTWNO
        rWLzIRbLfd5DNRxMYsPlJrywmevbM60dZT3XipKGM75gBEFJDDUEOZ+t2xOVIBR1342gl4
        bbF25uFrzhPRZesgSukvTwFB+ucVURA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-599-HEX_cppGMKGDue7hqzoQyg-1; Fri, 26 Feb 2021 05:14:24 -0500
X-MC-Unique: HEX_cppGMKGDue7hqzoQyg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 94BC918B9ECA;
        Fri, 26 Feb 2021 10:14:22 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0DB4C1001281;
        Fri, 26 Feb 2021 10:14:21 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Christoph Hellwig <hch@lst.de>, David Woodhouse <dwmw@amazon.co.uk>
Subject: [PATCH] KVM: x86: allow compiling out the Xen hypercall interface
Date: Fri, 26 Feb 2021 05:14:21 -0500
Message-Id: <20210226101421.81535-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Xen hypercall interface adds to the attack surface of the hypervisor
and will be used quite rarely.  Allow compiling it out.

Suggested-by: Christoph Hellwig <hch@lst.de>
Cc: David Woodhouse <dwmw@amazon.co.uk>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/Kconfig  |  9 ++++++++
 arch/x86/kvm/Makefile |  3 ++-
 arch/x86/kvm/x86.c    |  2 ++
 arch/x86/kvm/xen.h    | 49 ++++++++++++++++++++++++++++++++++++++++++-
 4 files changed, 61 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: hyper-v: Fix Hyper-V context null-ptr-deref
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12105975
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4B625C433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 08:01:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF7E964EDB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 08:01:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230104AbhBZIBC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 03:01:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52784 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229541AbhBZIAu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 03:00:50 -0500
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4C028C06174A;
        Fri, 26 Feb 2021 00:00:10 -0800 (PST)
Received: by mail-pf1-x42a.google.com with SMTP id j24so5744922pfi.2;
        Fri, 26 Feb 2021 00:00:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=SGKC+JVft3JHE0DGY/zfVH90D0jA8OCfIOyzcJ20Wcc=;
        b=XffIAJbzfF4FyjDlJxNDHc5mU8K/77RZLqJY5xBu0uRny+QbYcdpYFDPREhFxOlqix
         lrGIs9z2Y2XGFmY6pm7B9DKLyHjhLkZTRFW/wwFhQIrcuAZT6mW0O7jYWZOIB9acIbhw
         9xxaiFwOG7UgnRoSU5z3nCsTGLdKJlPdgYMeLg7OE1fAh+xw/iLBKELLpcPM2i0JfSQY
         UhZzSfahv/u/+IXT2AVo4DwVQ0V5Xyl3kvqIV7wex8wLiI0TfAZfp8V4X3/6qk3pOpOK
         IpyvdF87hkmFEKDg5oUm4Th4TZ4uNgSYlLdTCSOCFCZgzL/knheRrii92UXoBIcoCwrL
         Mfcw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=SGKC+JVft3JHE0DGY/zfVH90D0jA8OCfIOyzcJ20Wcc=;
        b=aTn5ca/Oh7muRoFzdWffcev9wcBBJwJdtWhxcqAkQbsymNxg0m27aeUavRYJfmPZd7
         wQcmg8VtHxpYUqw1nBXzlEJlmpodwuSdm57R5ObC6E8v4lw6R1etIiwUOUQpb1tImZlB
         WN1PHOPKLcwyQPcXFH5JUFuaziJx4cWAhPHlxuvypiZWJ7iCGdemfVJf6wCf+GoZAUSO
         T4Q3ao53/t8OotikLTzgSx52GjcMoCPn2TLGrnIyiYrS2zoMfj5CDGlOHhziQY3ZmsR4
         EkB7j4dXaS1HAqKRo/jVgKV2mv/q+ujN+bRsveKH2qGO4T2Ld460aAy1Q+oIEwZucatz
         QEBw==
X-Gm-Message-State: AOAM533TyF6yxy49uXEbGErwLc6SpEo0vFFJVZigvZ6sgs4erqMa5hTf
        rteIlZshMCIyTv3XsFygKi/taxBlheXhcw==
X-Google-Smtp-Source: 
 ABdhPJxawGKZ4ZgAsRE/UqeSM6fJzqrwWfMq6XhqheJIZuUgfWr+DWX8mVWgINCwXXDMPA8ZxrbQPw==
X-Received: by 2002:a63:dd49:: with SMTP id g9mr1900154pgj.175.1614326409597;
        Fri, 26 Feb 2021 00:00:09 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 b18sm8785961pfi.173.2021.02.26.00.00.07
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 26 Feb 2021 00:00:09 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: x86: hyper-v: Fix Hyper-V context null-ptr-deref
Date: Fri, 26 Feb 2021 15:59:59 +0800
Message-Id: <1614326399-5762-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Reported by syzkaller:

    KASAN: null-ptr-deref in range [0x0000000000000140-0x0000000000000147]
    CPU: 1 PID: 8370 Comm: syz-executor859 Not tainted 5.11.0-syzkaller #0
    RIP: 0010:synic_get arch/x86/kvm/hyperv.c:165 [inline]
    RIP: 0010:kvm_hv_set_sint_gsi arch/x86/kvm/hyperv.c:475 [inline]
    RIP: 0010:kvm_hv_irq_routing_update+0x230/0x460 arch/x86/kvm/hyperv.c:498
    Call Trace:
     kvm_set_irq_routing+0x69b/0x940 arch/x86/kvm/../../../virt/kvm/irqchip.c:223
     kvm_vm_ioctl+0x12d0/0x2800 arch/x86/kvm/../../../virt/kvm/kvm_main.c:3959
     vfs_ioctl fs/ioctl.c:48 [inline]
     __do_sys_ioctl fs/ioctl.c:753 [inline]
     __se_sys_ioctl fs/ioctl.c:739 [inline]
     __x64_sys_ioctl+0x193/0x200 fs/ioctl.c:739
     do_syscall_64+0x2d/0x70 arch/x86/entry/common.c:46
     entry_SYSCALL_64_after_hwframe+0x44/0xae

Hyper-V context is lazily allocated until Hyper-V specific MSRs are accessed 
or SynIC is enabled. However, the syzkaller testcase sets irq routing table 
directly w/o enabling SynIC. This results in null-ptr-deref when accessing 
SynIC Hyper-V context. This patch fixes it.
     
syzkaller source: https://syzkaller.appspot.com/x/repro.c?x=163342ccd00000

Reported-by: syzbot+6987f3b2dbd9eda95f12@syzkaller.appspotmail.com
Fixes: 8f014550dfb1 ("KVM: x86: hyper-v: Make Hyper-V emulation enablement conditional")
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/hyperv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5] KVM: x86/mmu: Remove spurious TLB flush from TDP MMU's change_pte() hook
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12105335
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0CCEBC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 01:04:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C807464F21
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 01:04:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229769AbhBZBEb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 20:04:31 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48720 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231335AbhBZBEQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 20:04:16 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 67ED2C061786
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 17:03:36 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id a63so8411999yba.2
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 17:03:36 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=BZaWszN/LLBzcU94c/xowczYk0Zi91gjd6GZk09bLp8=;
        b=Tqbg9PdKVSAx0v9v1M+vUle/2MQJ9wjgId2EgtMTB3GOHfGzXZbdf4Ua4weJGSWKcU
         tcZXuhEBfMr9X7+A+v0/93pFy0mx+Ta5ntmHwHIn8e9k6a0s9V/nYJQ6I3QTMZS9Hdp7
         VQpgETaIivseKcse3lEd2M4Rhg3nMs9FGnzqlHw3wZtkFWQRam41xDYf3XTQJ63bdmkO
         uyWXD8yL3cEWfIOy/hD7gW9HCXw9xZjSd7P526xFqENKjPP0JLFOXsgrDNeV1lJokQrI
         0wIVcXzKHdx3cW/hvn4e83cCKQVAzdtPu0Q0eiUBWLRc0xWMfO3jP9aUonNOUqW0bpqF
         cOKA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=BZaWszN/LLBzcU94c/xowczYk0Zi91gjd6GZk09bLp8=;
        b=gE9qL4elOcsgHkqJoQkkGdOWltzT6Bde5Pqk+JTKtpLENv5D1T1ktn2uCq3xjfNGe0
         Okbl3QwG4B15HpVJmLYau9i9cBT02WUbqhBf1b/xEOolE8SL7bWeT/Bv4EoA1ijeMicl
         TQBeptOGHZMCwUX7TVj741uPKpHXuFU3yDESzw/WHzdDpY/sNAO7S68PSVgH4cfdKUeF
         lDBAaGZLnxlKqmhSSsj/p7VskHl/igKHxQjTQbUdm8G+q+9vCUe+nPDaU3bSQn4WThoZ
         v9kIG0f1PzR4GidW/GWqsGoxlP44u7pE3AOgXDAfBwOA22yg6re8uuo1d/QrWU114N7K
         kqLw==
X-Gm-Message-State: AOAM5311VS802ibS32rfVxS2OsTlTkiJ1sxqamnuobrK3KzLoh/ApFHe
        f8Ao/zxA14eazV0+ayFixZVsa2vyafA=
X-Google-Smtp-Source: 
 ABdhPJzLd/OexlxhpNoqN6h4X4CVKwl6YHyGAR57H9qGFlrTHD2sD39ekg0Z+DEZAKW+a9hlzCBbwk2piJM=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:34c4:7c1d:f9ba:4576])
 (user=seanjc job=sendgmr) by 2002:a25:d314:: with SMTP id
 e20mr814723ybf.155.1614301415676;
 Thu, 25 Feb 2021 17:03:35 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Feb 2021 17:03:25 -0800
In-Reply-To: <20210226010329.1766033-1-seanjc@google.com>
Message-Id: <20210226010329.1766033-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210226010329.1766033-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 1/5] KVM: x86/mmu: Remove spurious TLB flush from TDP MMU's
 change_pte() hook
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove an unnecessary remote TLB flush from set_tdp_spte(), the TDP MMu's
hook for handling change_pte() invocations from the MMU notifier.  If
the new host PTE is writable, the flush is completely redundant as there
are no futher changes to the SPTE before the post-loop flush.  If the
host PTE is read-only, then the primary MMU is responsible for ensuring
that the contents of the old and new pages are identical, thus it's safe
to let the guest continue reading both the old and new pages.  KVM must
only ensure the old page cannot be referenced after returning from its
callback; this is handled by the post-loop flush.

Fixes: 1d8dd6b3f12b ("kvm: x86/mmu: Support changed pte notifier in tdp MMU")
Cc: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/1] KVM: x86: remove misplaced comment on active_mmu_pages
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongli Zhang <dongli.zhang@oracle.com>
X-Patchwork-Id: 12105871
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42E93C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 06:21:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C0F1964EDB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 06:21:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229541AbhBZGVg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 01:21:36 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:57292 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229449AbhBZGVc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 01:21:32 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11Q6A7ne174164;
        Fri, 26 Feb 2021 06:19:41 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version;
 s=corp-2020-01-29; bh=RGffaJ9rBMbqmEqn0vIHiLolMApwBwZmco4pO91ey8Q=;
 b=JXI7EqrjbH+L86C+zf4ucCY8WaI2Q17r67B/kCL4dXrq9sXr1y8wHiJrA5ERcklCEaNq
 QPrY73OxZwoNrnjxapKd9qgwxHv+XCOYWbITebETFTFKAZ4JxuV2+QwiTJ/J7+oX0qvA
 dbW4rsjMooMQuFqivUzTorx2zUNcX0pSV8UQAzMMourR4kPMYIfItwIaFotlVCgkF9GO
 CBKxO1Use4YjXlr9TZew1+kwltSkh0C/wJCBTvwh+4K4e7LAxIKrGPrhJIvrYvwh4fdd
 E2pI3N86sbUkrRHeP8PMR0NpkJwjj1JSZD2bhOSTYS9HPJVpkk5Z7ibbYteNaWj0Ymw4 Ng==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 36tsur8vk8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 26 Feb 2021 06:19:40 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11Q6AjVW005633;
        Fri, 26 Feb 2021 06:19:40 GMT
Received: from nam04-co1-obe.outbound.protection.outlook.com
 (mail-co1nam04lp2051.outbound.protection.outlook.com [104.47.45.51])
        by aserp3020.oracle.com with ESMTP id 36ucb31j8c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 26 Feb 2021 06:19:39 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=AuMizV4j7Y2UcEGoE9Nx56E9IuQMff0pSRcp7YZaB4S6ipI2mcFDoLNSvhl2p10ssyTLrOZi40gPp35H3mBnDqFGGHEkrfnmSo+ZD8UgSVyQYuUGPxLuyJdalNdPtDKaaGo/bGjxOeSkJpLx1pT/n+zQHBq64qt1XFzF6NjdgffjbIP3EhqCbBQAra9z/54xfOCHiE5SdrrLAgbo+LS1HDCNFDeV/uy707fQkvwXDUhW2w1pBJFwrL/xPM5BEISGOi87tTJmypakJOG1Fw2pdic6lGir61KUUvsLPfbmYLOqFmSTdJ0NCsdGbMp5W1uYo+1SOhE2znly8SE96agozw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=RGffaJ9rBMbqmEqn0vIHiLolMApwBwZmco4pO91ey8Q=;
 b=RX7in5tc9R15dMTgmmEANJpnTgcep1Pf3vqhkabPEtpI41rueXp8K7lcVNt0rxccV4PkC1Lz6tuvq+7HXGmfnbmsgSugVg730KREJ5QPKN5BBZPkJq/bZyqcXwEU99OKUIMTNgbf7T9CctEB2JTEtmb6oeRoJ5Fhp9sYnj1rkEjaquRb6jezrh5WQ+a84ZGlKUVY+3fKg5TkZVuQPdGQa63DeJKZ+BLEu3X9/zfJA1lD8dnSc6Q215zjsHJ4rEr5nAGvtZFvotGuBfj50Cs5h1jK1VRBKoflierVs7rGetkK7LhUSyehZQ3cFoxcmedyVnfy6r2ZafboDLQh9YuUxQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=RGffaJ9rBMbqmEqn0vIHiLolMApwBwZmco4pO91ey8Q=;
 b=bSE04fqnnQVxp74xmaFaFlL4SK8qirFkEeQqSLxBLXre4bydtfYWQvCMlmso0xq4+TZS8PuU03fI+7a94skLnikV23RbRETaowMoKzOB06wMoMcCX751h0C0pFjhaaSTWykj+f9NCF+stDmMaRi5npmruGUbZwLZa0wk7J8Bl+8=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from BYAPR10MB2663.namprd10.prod.outlook.com (2603:10b6:a02:a9::20)
 by BYAPR10MB3206.namprd10.prod.outlook.com (2603:10b6:a03:155::20) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.33; Fri, 26 Feb
 2021 06:19:37 +0000
Received: from BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14]) by BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::b52e:bdd3:d193:4d14%7]) with mapi id 15.20.3846.041; Fri, 26 Feb 2021
 06:19:37 +0000
From: Dongli Zhang <dongli.zhang@oracle.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/1] KVM: x86: remove misplaced comment on active_mmu_pages
Date: Thu, 25 Feb 2021 22:19:45 -0800
Message-Id: <20210226061945.1222-1-dongli.zhang@oracle.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [138.3.200.16]
X-ClientProxiedBy: SN7PR04CA0112.namprd04.prod.outlook.com
 (2603:10b6:806:122::27) To BYAPR10MB2663.namprd10.prod.outlook.com
 (2603:10b6:a02:a9::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (138.3.200.16) by
 SN7PR04CA0112.namprd04.prod.outlook.com (2603:10b6:806:122::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.19 via Frontend
 Transport; Fri, 26 Feb 2021 06:19:36 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 0796cc0f-c244-4548-3b65-08d8da1e7e35
X-MS-TrafficTypeDiagnostic: BYAPR10MB3206:
X-Microsoft-Antispam-PRVS: 
 <BYAPR10MB32064EF1E84E320A331AC63AF09D9@BYAPR10MB3206.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:935;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 DednicTjP02jIGeZE60i7O+5TTFZjf/3dnIt9o5ELHOAFp7TOwSEvJW9twtRwjg67aXFhDzWTSas3eysKEbXEdt6fXos22Sr/a5Vwk2JLSnWn5igZT3Ygk/dEj6YLvUGJ4UReP4aWgxLscDTf2VMFriY3VRxRCkkr42CWteNmISkaC47De83rfF98W0wD9Px4yKV9OoUljb3SAf2NB/SGLgWWIeZv6OSJ5VLhFbrmbeTGbuFY4N3FgJ2amAbeX2hEijEbx71XH8YEfhhB/c/ZUUcnwlhS+GwDuND6ciwelNVSZW2joadTtznlw4zPw7FLLmmsO7Po1Q7MpNtU2iVoo825Y5YqgcfQhbvzm3Dxx4VpHY/EJz9b676GoiolhIU23Y3MMf4iAoEYjhq2nSvIk9PC0SLn3ZSePyjJdgROGcBDCQVeeq8fTXQWEYyRWjR9rXz6USza6TjqTHB7dNoJZwU/P1TJkbAHundTrktj56k47ku3XiERYbDa3PK1HOI6/qv865xtMPJCaENvzAz29HTvYM221IjMqnqEJw2vh7lBYHg0ioBueE/uQn0Urw94AlTTG76bEMsrMvkGLhy/g==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BYAPR10MB2663.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(396003)(39860400002)(136003)(366004)(376002)(36756003)(6666004)(2906002)(52116002)(86362001)(1076003)(4744005)(8936002)(16526019)(8676002)(6506007)(83380400001)(6512007)(66556008)(66946007)(66476007)(26005)(956004)(316002)(4326008)(7416002)(5660300002)(69590400012)(2616005)(186003)(6486002)(44832011)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Tk84Ok2GR1cBBdsZDFhoHFIU7sgiGCUfK5PMwS3kMXcSPXLvwMSxW/OOJ+GC5lpFuXIzqwD5vR4FgfNezpBp6jAPsNOws7y3e/sAvXoixq9WJxYZrRaqZc8CLpeW7rp7P6HFg3OzbIvr7BTl0h2C7YJDSeg9Eis+tptlJMTaos4oiX4WXaNZxqNSMTEfmHaUVm5Zb3IMPoefN7+rCHZe/XDgbzckaQEynEAzNkteYgCBQt2UVB4O7WokmF2VdRUI8IFV0i1LzX8NB/UnE0dSLFFs7lMKgZenwvmZ1g2jg0cnO295NSDRwfh62pRBWtIbxRwu8yFWA43lXqM0QD9mve8u9GULL5PlVoivi/lHc7QreqmdLJ5JL36n6y4Gwx/+Cj+62kDVgDczYprUaA4OiEXnlLzpzD5HwdUlTYx83Qs0C470CqgUvtX6PEIYWK/n33PQb6To3IsSP4avH3b4QBOdGdw5KZy4ax4KwbsyPxGHxP4OLEmNwkYqJTjXTl8+G45DQJIHeuL/ii9Zx4Qc4MBf6/jgkXWcaxl4YC2mtND6lPlgYSYPeTWHVv2iuv4cDrOMqfIVJTUfxJMhSehj+P7dXc2U9JCvPCeBf6CPn9Ye5R9bFKrePPPa+BjYHSmEHdHlfQmuukO5TozxdGyaUIZNISlcUVV+Cp74HkXd0EizwDSmlKMLOAsdmQRs1u5ocH30dRhsXzQAzEARIrhkbxWb2GK8BFw15PtPxjWnojaMHtNwLXX35aHGAKPLC15YxtkcSaucpC0iiuPjP9KCGsD4n1Sngr0ywsr1Zqcsd7ye6IYWcImYbUT3L8OjFKZgCtaxCpjOc3UmZBCZSxyrkGLBazrVMw7MTAqNpJJvJ1Vz06a76cSdnAW5lH2b3xoe7skIUH3mju9uk3aYThW3R9udH9f1ivNna1uooNh9Q+M37MlTgUYgzcKyvatBhJP7Tc1a+asCMLfAZ9ZKf0Ot7tsr6V2xlsibNwLGACmqgEG7/I0+bEMYjMuPpNiUhTHgLcQ/qWAMR/skNNuZ68u7+d0jRrAllzkkPQY0e6l6lOH7kekXE2/QSMqPrM8Kw8Q6i0r9Uop+lLZFXqeyl5INjDV/AaTo7dN1+0Cj12yiPbhWEJvgkgqvtIgFX7aZ+7rqgRQNxVZz+U6et7TVos1RrQvg+wII76zMkn4yWk8pYMTOctfonpXxIIbDKIch2VJf8PV16d3vpDJG0aLvkHt0bHV1FrZ84LNAUn8r9VQqVJKAsbjbI96Xgpq/5jERk5mUeGE4d4iEg+tpQWF0XXq+rQyI2qIEjpkykADcUrclQYMP1ujzL27BdZnIp8Z9lWjO
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0796cc0f-c244-4548-3b65-08d8da1e7e35
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2663.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Feb 2021 06:19:37.6615
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 dn/IagKiRpR4tXYMhbHVPcClB2JBTIHNUFjva7x6NPy1tIb8weV3nQzebho5LFHlLFujrFQ+65db9yA2q6076Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BYAPR10MB3206
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9906
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0
 malwarescore=0 mlxlogscore=999 adultscore=0 bulkscore=0 mlxscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102260048
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9906
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 spamscore=0
 priorityscore=1501 impostorscore=0 bulkscore=0 mlxscore=0 malwarescore=0
 clxscore=1015 phishscore=0 mlxlogscore=999 lowpriorityscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102260048
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'mmu_page_hash' is used as hash table while 'active_mmu_pages' is a
list. Remove the misplaced comment as it's mostly stating the obvious
anyways.

Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
Changed since v1:
  - change 'incorrect' to 'misplaced'

 arch/x86/include/asm/kvm_host.h | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH v2] KVM: x86: allow compiling out the Xen hypercall interface
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12106501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4B2A0C433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 11:59:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD76A64DE3
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 11:59:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229622AbhBZL7R (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 06:59:17 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38872 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229482AbhBZL7P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Feb 2021 06:59:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614340668;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9ex2gVY8g3pHKx0BP1TDVrlr+j7IDrQGcZOuxsin5kk=;
        b=YbY9jfYkPkalRpnNuS6aQfb3ZBOPvPHIHdHyKXcl3jsLiTJIMpZkZj06xsSpYkpPhcTNyn
        wtjFF8DpAsERq7DDax87VAHg2IE/7KX38liDbzbXB0oZfWM9a8ZEUkQTE6PRMEo7WvrTcu
        UUSXZ/FScwRFgI7aa1vOy8jEzTh06MQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-534-JQwEBj3xNemQtht-DdPDlA-1; Fri, 26 Feb 2021 06:57:46 -0500
X-MC-Unique: JQwEBj3xNemQtht-DdPDlA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 907EAC280;
        Fri, 26 Feb 2021 11:57:45 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1C5F363746;
        Fri, 26 Feb 2021 11:57:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Christoph Hellwig <hch@lst.de>, David Woodhouse <dwmw@amazon.co.uk>
Subject: [PATCH v2] KVM: x86: allow compiling out the Xen hypercall interface
Date: Fri, 26 Feb 2021 06:57:44 -0500
Message-Id: <20210226115744.170536-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Xen hypercall interface adds to the attack surface of the hypervisor
and will be used quite rarely.  Allow compiling it out.

Suggested-by: Christoph Hellwig <hch@lst.de>
Cc: David Woodhouse <dwmw@amazon.co.uk>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
	v1->v2: do not use stubs for the ioctls, cull KVM_CAP_XEN_HVM too

 arch/x86/kvm/Kconfig  |  9 +++++++++
 arch/x86/kvm/Makefile |  3 ++-
 arch/x86/kvm/x86.c    |  8 ++++++++
 arch/x86/kvm/xen.h    | 24 +++++++++++++++++++++++-
 4 files changed, 42 insertions(+), 2 deletions(-)

```
