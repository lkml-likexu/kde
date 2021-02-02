#### [PATCH 1/2] KVM: selftests: Keep track of memslots more efficiently
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12058343
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5ABACC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:12:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F00B564E24
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:12:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232440AbhBAIMW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 03:12:22 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:42918 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232406AbhBAIMR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 03:12:17 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1l6UIa-0004r0-Au; Mon, 01 Feb 2021 09:11:04 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Shuah Khan <shuah@kernel.org>,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: selftests: Keep track of memslots more efficiently
Date: Mon,  1 Feb 2021 09:10:56 +0100
Message-Id: 
 <5e5d83b305077e3e65b130dbb31c131bfb831170.1612139762.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

The KVM selftest framework was using a simple list for keeping track of
the memslots currently in use.
This resulted in lookups and adding a single memslot being O(n), the
later due to linear scanning of the existing memslot set to check for
the presence of any conflicting entries.

Before this change, benchmarking high count of memslots was more or less
impossible as pretty much all the benchmark time was spent in the
selftest framework code.

We can simply use a rbtree for keeping track of both of gfn and hva.
We don't need an interval tree for hva here as we can't have overlapping
memslots because we allocate a completely new memory chunk for each new
memslot.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    | 141 ++++++++++++++----
 .../selftests/kvm/lib/kvm_util_internal.h     |  15 +-
 tools/testing/selftests/kvm/lib/rbtree.c      |   1 +
 4 files changed, 124 insertions(+), 35 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/rbtree.c

```
#### [PATCH 1/2] KVM: x86/mmu: Make HVA handler retpoline-friendly
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12058347
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4388AC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:15:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8B1164E34
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:14:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232330AbhBAIO6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 03:14:58 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:43152 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232045AbhBAIO4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 03:14:56 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1l6UL3-0004rW-Ua; Mon, 01 Feb 2021 09:13:37 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86/mmu: Make HVA handler retpoline-friendly
Date: Mon,  1 Feb 2021 09:13:31 +0100
Message-Id: 
 <ceb96527b6f7bb662eec813f05b897a551ebd0b2.1612140117.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

When retpolines are enabled they have high overhead in the inner loop
inside kvm_handle_hva_range() that iterates over the provided memory area.

Implement a static dispatch there, just like commit 7a02674d154d
("KVM: x86/mmu: Avoid retpoline on ->page_fault() with TDP") did for the
MMU page fault handler.

This significantly improves performance on the unmap test on the existing
kernel memslot code (tested on a Xeon 8167M machine):
30 slots in use:
Test		Before	  After	    Improvement
Unmap		0.0368s	  0.0353s    4%
Unmap 2M	0.000952s 0.000431s 55%

509 slots in use:
Unmap		0.0872s	  0.0777s   11%
Unmap 2M	0.00236s  0.00168s  29%

Looks like performing this indirect call via a retpoline might have
interfered with unrolling of the whole loop in the CPU.

Provide such static dispatch only for kvm_unmap_rmapp() and
kvm_age_rmapp() and their TDP MMU equivalents since other handlers are
called in ranges of single byte only, so they already have high overhead
to begin with if walking over a large memory area.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
 arch/x86/kvm/mmu/mmu.c     |  59 +++++++++++++------
 arch/x86/kvm/mmu/tdp_mmu.c | 116 ++++++++++++++++++++++---------------
 2 files changed, 112 insertions(+), 63 deletions(-)

```
#### [PATCH 1/9] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12059455
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6EE0AC433E9
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 16:29:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37B8C64DCC
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 16:29:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229793AbhBAQ3U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 11:29:20 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:9089 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229483AbhBAQ3T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 11:29:19 -0500
Received: from hqmail.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, AES256-SHA)
        id <B60182c370000>; Mon, 01 Feb 2021 08:28:39 -0800
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 1 Feb
 2021 16:28:38 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server id 15.0.1473.3 via Frontend
 Transport; Mon, 1 Feb 2021 16:28:34 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <jgg@nvidia.com>, <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <alex.williamson@redhat.com>
CC: <liranl@nvidia.com>, <oren@nvidia.com>, <tzahio@nvidia.com>,
        <leonro@nvidia.com>, <yarong@nvidia.com>, <aviadye@nvidia.com>,
        <shahafs@nvidia.com>, <artemp@nvidia.com>, <kwankhede@nvidia.com>,
        <ACurrid@nvidia.com>, <gmataev@nvidia.com>, <cjia@nvidia.com>,
        <mjrosato@linux.ibm.com>, <yishaih@nvidia.com>, <aik@ozlabs.ru>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/9] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
Date: Mon, 1 Feb 2021 16:28:20 +0000
Message-ID: <20210201162828.5938-2-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210201162828.5938-1-mgurtovoy@nvidia.com>
References: <20210201162828.5938-1-mgurtovoy@nvidia.com>
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1612196919; bh=cD5IrQ+dWwGI6zYP21oJURgsVtNrdqC+pW+2KPZxPk0=;
        h=From:To:CC:Subject:Date:Message-ID:X-Mailer:In-Reply-To:
         References:MIME-Version:Content-Transfer-Encoding:Content-Type;
        b=M44nR0TmIGfBbdIaZwHOQ99ZI2fGzJRTBHYvemPa6ms/mWEpvB+NXzJuc+tL/ZbfY
         nwNMJyks+P27xHDfDRWfGejJ30dwEeBUlTt6O5Ngrui5QbZn1kN4FW16n24apMLQ8a
         z9xI7fe5mQ9DpGHMG9lyuDpCE4NUES1KhbGiGGuLdP/KWOSQpj/FbsgDfIW1RBK50k
         P34W4iSSyy4ds9PIugnHYOxWG1DAzThAHGlVHNGXtanJ3ijaHHqi+XfSMnmk/3JHJx
         dPDSd3yFk1A4u4gyZL4DP3c6daXMjyF+iCdWVMP2UnadN+WJyt2M5CMwx+0a7vy204
         HTwHv6F3aOa8Q==
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preparation patch for separating the vfio_pci driver to a
subsystem driver and a generic pci driver. This patch doesn't change any
logic.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---
 drivers/vfio/pci/Makefile                        | 2 +-
 drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} | 0
 2 files changed, 1 insertion(+), 1 deletion(-)
 rename drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} (100%)

```
#### [PATCH] KVM: Replace DEFINE_SIMPLE_ATTRIBUTE with DEFINE_DEBUGFS_ATTRIBUTE
##### From: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
X-Patchwork-Id: 12058379
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 284D7C43381
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:39:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB26E64E3D
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:39:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232590AbhBAIjU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 03:39:20 -0500
Received: from out30-56.freemail.mail.aliyun.com ([115.124.30.56]:46615 "EHLO
        out30-56.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232577AbhBAIjK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Feb 2021 03:39:10 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R191e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=alimailimapcm10staff010182156082;MF=jiapeng.chong@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0UNWymoB_1612168686;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:jiapeng.chong@linux.alibaba.com
 fp:SMTPD_---0UNWymoB_1612168686)
          by smtp.aliyun-inc.com(127.0.0.1);
          Mon, 01 Feb 2021 16:38:23 +0800
From: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
Subject: [PATCH] KVM: Replace DEFINE_SIMPLE_ATTRIBUTE with
 DEFINE_DEBUGFS_ATTRIBUTE
Date: Mon,  1 Feb 2021 16:38:05 +0800
Message-Id: 
 <1612168685-33799-1-git-send-email-jiapeng.chong@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warning:

./arch/x86/kvm/debugfs.c:44:0-23: WARNING: vcpu_tsc_scaling_frac_fops
should be defined with DEFINE_DEBUGFS_ATTRIBUTE.

./arch/x86/kvm/debugfs.c:36:0-23: WARNING: vcpu_tsc_scaling_fops should
be defined with DEFINE_DEBUGFS_ATTRIBUTE.

./arch/x86/kvm/debugfs.c:27:0-23: WARNING: vcpu_tsc_offset_fops should
be defined with DEFINE_DEBUGFS_ATTRIBUTE.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
---
 arch/x86/kvm/debugfs.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [kvm-unit-test] [PATCH] x86: Add tests for Guest Last Branch Recording (LBR)
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12058055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56723C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:06:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E66764E25
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:06:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229557AbhBAFGG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 00:06:06 -0500
Received: from mga14.intel.com ([192.55.52.115]:45366 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229548AbhBAFGE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 00:06:04 -0500
IronPort-SDR: 
 YESUiSOQ2+KngoD0UXO+dkQf2+t+fHXK/gqEmgCsgzxM/1CFWIw5AAGZGLeZ1UJGVbiTMp+4+v
 BCXB1dsGmRfQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9881"; a="179856554"
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="179856554"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jan 2021 21:04:17 -0800
IronPort-SDR: 
 C+/CQ+tbwRBl9rIFfWDsdp3NXXd+bypbJ61F8Qi7NJbqssY33aL3Ty3Ba48VhIkG5KSncwQ9hf
 HdTsuovEiKXw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="368961982"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga008.fm.intel.com with ESMTP; 31 Jan 2021 21:04:16 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-test] [PATCH] x86: Add tests for Guest Last Branch
 Recording (LBR)
Date: Mon,  1 Feb 2021 12:57:51 +0800
Message-Id: <20210201045751.243231-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test the KVM's support for the
Last Branch Recording (LBR) which is a performance monitor
unit (PMU) feature on Intel processors.

If the LBR bit is set to 1 in the DEBUGCTLMSR, the processor
will record a running trace of the most recent branches guest
taken in the LBR entries for guest to read.

This is a basic check that looks for the MSR LBR (via #GP check),
does some branches, and checks that the FROM_IP/TO_IP are good.
To run this test, use the QEMU option "-cpu host,migratable=no".

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 x86/Makefile.common |   3 +-
 x86/pmu_lbr.c       | 121 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   6 +++
 3 files changed, 129 insertions(+), 1 deletion(-)
 create mode 100644 x86/pmu_lbr.c

```
#### [PATCH v14 01/11] KVM: x86/vmx: Make vmx_set_intercept_for_msr() non-static
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12058065
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B56CFC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:19:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BEB064E2B
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 05:19:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229736AbhBAFTB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 00:19:01 -0500
Received: from mga17.intel.com ([192.55.52.151]:9254 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229557AbhBAFS4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 00:18:56 -0500
IronPort-SDR: 
 QUkfAx+HIcWOgSAvuPuauGtXmMgTpS5v308jxX8LPQKmVgPXHlO/50NjUL8aQQkr54dNtr0OZh
 vuy1ielIzL0w==
X-IronPort-AV: E=McAfee;i="6000,8403,9881"; a="160401827"
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="160401827"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jan 2021 21:17:11 -0800
IronPort-SDR: 
 0hlxxwExa63tdWHjRkLRb8aR41/Iswwcm3TstTtVQpxu90IQlSP3P9yQ91Q1OjLswhrvNE1yGs
 CLmfyjxIInvw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="390694260"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 31 Jan 2021 21:17:08 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, kan.liang@intel.com,
        alex.shi@linux.alibaba.com, kvm@vger.kernel.org, x86@kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v14 01/11] KVM: x86/vmx: Make vmx_set_intercept_for_msr()
 non-static
Date: Mon,  1 Feb 2021 13:10:29 +0800
Message-Id: <20210201051039.255478-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210201051039.255478-1-like.xu@linux.intel.com>
References: <20210201051039.255478-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To make code responsibilities clear, we may resue and invoke the
vmx_set_intercept_for_msr() in other vmx-specific files (e.g. pmu_intel.c),
so expose it to passthrough LBR msrs later.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 arch/x86/kvm/vmx/vmx.h | 2 ++
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Supplement __cr4_reserved_bits() with X86_FEATURE_PCID check
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12059141
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8340EC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 14:30:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E20464DD9
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 14:30:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229816AbhBAOaV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 09:30:21 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28863 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229566AbhBAOaR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Feb 2021 09:30:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612189730;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+vZ66VqPrxvnrqTCUTK/999/9ewUHwH+ZXDKtfFOdSk=;
        b=aKLGXUxGWcu2dw9R6MIMFlsCWqpG5wwiioWfO+DSCENdmsbFiADGsB4lNyNDg45tG7wavL
        gmeE49VvLzW2qIZSj8o45P7kmvBWvk0/1njOGtOyVQ9kfTxSlK1zk4xMrVOepCp5JvW0bF
        l5zpl0FaTsoip/c1xqxQYYPIzINNr70=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-486-ZLKHlcPBMhKSpKoJddYSzQ-1; Mon, 01 Feb 2021 09:28:49 -0500
X-MC-Unique: ZLKHlcPBMhKSpKoJddYSzQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C57B1801AC4;
        Mon,  1 Feb 2021 14:28:47 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.123])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A38D8100239A;
        Mon,  1 Feb 2021 14:28:44 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH] KVM: x86: Supplement __cr4_reserved_bits() with
 X86_FEATURE_PCID check
Date: Mon,  1 Feb 2021 15:28:43 +0100
Message-Id: <20210201142843.108190-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 7a873e455567 ("KVM: selftests: Verify supported CR4 bits can be set
before KVM_SET_CPUID2") reveals that KVM allows to set X86_CR4_PCIDE even
when PCID support is missing:

==== Test Assertion Failure ====
  x86_64/set_sregs_test.c:41: rc
  pid=6956 tid=6956 - Invalid argument
     1	0x000000000040177d: test_cr4_feature_bit at set_sregs_test.c:41
     2	0x00000000004014fc: main at set_sregs_test.c:119
     3	0x00007f2d9346d041: ?? ??:0
     4	0x000000000040164d: _start at ??:?
  KVM allowed unsupported CR4 bit (0x20000)

Add X86_FEATURE_PCID feature check to __cr4_reserved_bits() to make
kvm_is_valid_cr4() fail.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v14 07/11] KVM: vmx/pmu: Reduce the overhead of LBR pass-through or cancellation
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12058143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A09CEC433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 06:35:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A27D64E30
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 06:35:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231877AbhBAGbZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 01:31:25 -0500
Received: from mga14.intel.com ([192.55.52.115]:26662 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232122AbhBAGK0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 01:10:26 -0500
IronPort-SDR: 
 nBA9B+YJaami8y8u2Te6h1RVOrQscx7koabazhk9w8wj2h02UJ/YHHjU5CBWFcpcXZVnX9psXn
 YpZ6cui3MxWw==
X-IronPort-AV: E=McAfee;i="6000,8403,9881"; a="179860892"
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="179860892"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Jan 2021 22:08:20 -0800
IronPort-SDR: 
 SmZu/epYWqJg2KowbBnFA0dfDjJKq4ol5vn0Wq401xaOZDcJ5fgpcAmnvlzoAxEVgk7OnT5tKa
 KdiYaVXUYk+w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,391,1602572400";
   d="scan'208";a="368980347"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga008.fm.intel.com with ESMTP; 31 Jan 2021 22:08:18 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, kan.liang@intel.com,
        alex.shi@linux.alibaba.com, kvm@vger.kernel.org, x86@kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v14 07/11] KVM: vmx/pmu: Reduce the overhead of LBR
 pass-through or cancellation
Date: Mon,  1 Feb 2021 14:01:48 +0800
Message-Id: <20210201060152.370069-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210201051039.255478-1-like.xu@linux.intel.com>
References: <20210201051039.255478-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the LBR records msrs has already been pass-through, there is no
need to call vmx_update_intercept_for_lbr_msrs() again and again, and
vice versa.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 13 +++++++++++++
 arch/x86/kvm/vmx/vmx.h       |  3 +++
 2 files changed, 16 insertions(+)

```
#### [stable-5.4][PATCH] KVM: Forbid the use of tagged userspace addresses for memslots
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12059063
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1D32C433E6
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 13:32:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A660864D99
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 13:32:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232290AbhBANc0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 08:32:26 -0500
Received: from mail.kernel.org ([198.145.29.99]:44938 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231477AbhBANcY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 08:32:24 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id AD41964E8F;
        Mon,  1 Feb 2021 13:31:43 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l6ZIr-00BHLa-I2; Mon, 01 Feb 2021 13:31:41 +0000
From: Marc Zyngier <maz@kernel.org>
To: stable@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, gregkh@linuxfoundation.org,
        kvm@vger.kernel.org, Rick Edgecombe <rick.p.edgecombe@intel.com>,
        Catalin Marinas <catalin.marinas@arm.com>
Subject: [stable-5.4][PATCH] KVM: Forbid the use of tagged userspace addresses
 for memslots
Date: Mon,  1 Feb 2021 13:31:37 +0000
Message-Id: <20210201133137.3541896-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: stable@vger.kernel.org, pbonzini@redhat.com,
 gregkh@linuxfoundation.org, kvm@vger.kernel.org, rick.p.edgecombe@intel.com,
 catalin.marinas@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 139bc8a6146d92822c866cf2fd410159c56b3648 upstream.

The use of a tagged address could be pretty confusing for the
whole memslot infrastructure as well as the MMU notifiers.

Forbid it altogether, as it never quite worked the first place.

Cc: stable@vger.kernel.org
Reported-by: Rick Edgecombe <rick.p.edgecombe@intel.com>
Reviewed-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/api.txt | 3 +++
 virt/kvm/kvm_main.c            | 1 +
 2 files changed, 4 insertions(+)

```
#### [PATCH v5 1/2] drivers/misc: sysgenid: add system generation id driver
##### From: Adrian Catangiu <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12059513
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8AAC2C4332B
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 17:27:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5824564EBA
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 17:27:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231699AbhBAR0w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 12:26:52 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:19576 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231350AbhBAR0i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 12:26:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1612200395; x=1643736395;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=6XZVkuKV3mgPC5hyMw49kI7JAdzbX6z3meX2yRYqchI=;
  b=I/EX7xN9Z7HNdaUnL622qxfGGRolheRqU8kw5+3GH4KAv3+EpGIGOcIL
   pu/pAIDocPpty1bLO45JPTyRaolhvVdcTj7qcXudBiWK5oYlMGn3w6AVX
   tVXvuJjI1A2GEVTBiRRqWkufqVBvn2bmVXzzeTwiCcljJnjWY2LGcvrKU
   Y=;
X-IronPort-AV: E=Sophos;i="5.79,393,1602547200";
   d="scan'208";a="79082184"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 01 Feb 2021 17:25:43 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com (Postfix) with
 ESMTPS id A9841A2701;
        Mon,  1 Feb 2021 17:25:39 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.253) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 1 Feb 2021 17:25:24 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, Adrian Catangiu <acatan@amazon.com>
Subject: [PATCH v5 1/2] drivers/misc: sysgenid: add system generation id
 driver
Date: Mon, 1 Feb 2021 19:24:53 +0200
Message-ID: <1612200294-17561-2-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1612200294-17561-1-git-send-email-acatan@amazon.com>
References: <1612200294-17561-1-git-send-email-acatan@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.253]
X-ClientProxiedBy: EX13D24UWB002.ant.amazon.com (10.43.161.159) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background and problem

The System Generation ID feature is required in virtualized or
containerized environments by applications that work with local copies
or caches of world-unique data such as random values, uuids,
monotonically increasing counters, etc.
Such applications can be negatively affected by VM or container
snapshotting when the VM or container is either cloned or returned to
an earlier point in time.

Furthermore, simply finding out about a system generation change is
only the starting point of a process to renew internal states of
possibly multiple applications across the system. This process could
benefit from a driver that provides an interface through which
orchestration can be easily done.

- Solution

The System Generation ID is a simple concept meant to alleviate the
issue by providing a monotonically increasing u32 counter that changes
each time the VM or container is restored from a snapshot.

The `sysgenid` driver exposes a monotonic incremental System Generation
u32 counter via a char-dev FS interface that provides sync and async
SysGen counter updates notifications. It also provides SysGen counter
retrieval and confirmation mechanisms.

The counter starts from zero when the driver is initialized and
monotonically increments every time the system generation changes.

The `sysgenid` driver exports the `void sysgenid_bump_generation()`
symbol which can be used by backend drivers to drive system generation
changes based on hardware events.
System generation changes can also be driven by userspace software
through a dedicated driver ioctl.

Userspace applications or libraries can then (a)synchronously consume
the system generation counter through the provided FS interface to make
any necessary internal adjustments following a system generation
update.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
 Documentation/misc-devices/sysgenid.rst            | 236 ++++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 MAINTAINERS                                        |   8 +
 drivers/misc/Kconfig                               |  16 ++
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 307 +++++++++++++++++++++
 include/uapi/linux/sysgenid.h                      |  17 ++
 7 files changed, 586 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h

diff --git a/Documentation/misc-devices/sysgenid.rst b/Documentation/misc-devices/sysgenid.rst
new file mode 100644
index 0000000..4337ca0
--- /dev/null
+++ b/Documentation/misc-devices/sysgenid.rst
@@ -0,0 +1,236 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+========
+SYSGENID
+========
+
+The System Generation ID feature is required in virtualized or
+containerized environments by applications that work with local copies
+or caches of world-unique data such as random values, UUIDs,
+monotonically increasing counters, etc.
+Such applications can be negatively affected by VM or container
+snapshotting when the VM or container is either cloned or returned to
+an earlier point in time.
+
+The System Generation ID is a simple concept meant to alleviate the
+issue by providing a monotonically increasing counter that changes
+each time the VM or container is restored from a snapshot.
+The driver for it lives at ``drivers/misc/sysgenid.c``.
+
+The ``sysgenid`` driver exposes a monotonic incremental System
+Generation u32 counter via a char-dev FS interface accessible through
+``/dev/sysgenid`` that provides sync and async SysGen counter update
+notifications. It also provides SysGen counter retrieval and
+confirmation mechanisms.
+
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the system generation changes.
+
+The ``sysgenid`` driver exports the ``void sysgenid_bump_generation()``
+symbol which can be used by backend drivers to drive system generation
+changes based on hardware events.
+System generation changes can also be driven by userspace software
+through a dedicated driver ioctl.
+
+Userspace applications or libraries can (a)synchronously consume the
+system generation counter through the provided FS interface, to make
+any necessary internal adjustments following a system generation update.
+
+Driver FS interface:
+
+``open()``:
+  When the device is opened, a copy of the current Sys-Gen-Id (counter)
+  is associated with the open file descriptor. The driver now tracks
+  this file as an independent *watcher*. The driver tracks how many
+  watchers are aware of the latest Sys-Gen-Id counter and how many of
+  them are *outdated*; outdated being those that have lived through
+  a Sys-Gen-Id change but not yet confirmed the new generation counter.
+
+``read()``:
+  Read is meant to provide the *new* system generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date, at which point the new
+  counter is provided/returned.
+  Nonblocking ``read()`` uses ``EAGAIN`` to signal that there is no
+  *new* counter value available. The generation counter is considered
+  *new* for each open file descriptor that hasn't confirmed the new
+  value following a generation change. Therefore, once a generation
+  change takes place, all ``read()`` calls will immediately return the
+  new generation counter and will continue to do so until the
+  new value is confirmed back to the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  32 bits in size.
+
+``write()``:
+  Write is used to confirm the up-to-date Sys Gen counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` confirms the up-to-date counter back to
+  the driver.
+  Partial writes are not allowed - write buffer should be exactly
+  32 bits in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for waiting on open file descriptors
+  that haven't acknowledged a generation counter update, as well as a
+  mechanism for userspace to *force* a generation update:
+
+  - SYSGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    watchers, or if a ``timeout`` argument is provided, until the
+    timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - SYSGENID_FORCE_GEN_UPDATE: forces a generation counter increment.
+    It takes a ``minimum-generation`` argument which represents the
+    minimum value the generation counter will be incremented to. For
+    example if current generation is ``5`` and ``SYSGENID_FORCE_GEN_UPDATE(8)``
+    is called, the generation counter will increment to ``8``.
+    This IOCTL can only be used by processes with CAP_CHECKPOINT_RESTORE
+    or CAP_SYS_ADMIN capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date u32 copy of the system generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections - see examples.
+
+``close()``:
+  Removes the file descriptor as a system generation counter *watcher*.
+
+Example application workflows
+-----------------------------
+
+1) Watchdog thread simplified example::
+
+	void watchdog_thread_handler(int *thread_active)
+	{
+		unsigned int genid;
+		int fd = open("/dev/sysgenid", O_RDWR | O_CLOEXEC, S_IRUSR | S_IWUSR);
+
+		do {
+			// read new gen ID - blocks until VM generation changes
+			read(fd, &genid, sizeof(genid));
+
+			// because of VM generation change, we need to rebuild world
+			reseed_app_env();
+
+			// confirm we're done handling gen ID update
+			write(fd, &genid, sizeof(genid));
+		} while (atomic_read(thread_active));
+
+		close(fd);
+	}
+
+2) ASYNC simplified example::
+
+	void handle_io_on_sysgenfd(int sysgenfd)
+	{
+		unsigned int genid;
+
+		// read new gen ID - we need it to confirm we've handled update
+		read(fd, &genid, sizeof(genid));
+
+		// because of VM generation change, we need to rebuild world
+		reseed_app_env();
+
+		// confirm we're done handling the gen ID update
+		write(fd, &genid, sizeof(genid));
+	}
+
+	int main() {
+		int epfd, sysgenfd;
+		struct epoll_event ev;
+
+		epfd = epoll_create(EPOLL_QUEUE_LEN);
+
+		sysgenfd = open("/dev/sysgenid",
+		               O_RDWR | O_CLOEXEC | O_NONBLOCK,
+		               S_IRUSR | S_IWUSR);
+
+		// register sysgenid for polling
+		ev.events = EPOLLIN;
+		ev.data.fd = sysgenfd;
+		epoll_ctl(epfd, EPOLL_CTL_ADD, sysgenfd, &ev);
+
+		// register other parts of your app for polling
+		// ...
+
+		while (1) {
+			// wait for something to do...
+			int nfds = epoll_wait(epfd, events,
+				MAX_EPOLL_EVENTS_PER_RUN,
+				EPOLL_RUN_TIMEOUT);
+			if (nfds < 0) die("Error in epoll_wait!");
+
+			// for each ready fd
+			for(int i = 0; i < nfds; i++) {
+				int fd = events[i].data.fd;
+
+				if (fd == sysgenfd)
+					handle_io_on_sysgenfd(sysgenfd);
+				else
+					handle_some_other_part_of_the_app(fd);
+			}
+		}
+
+		return 0;
+	}
+
+3) Mapped memory polling simplified example::
+
+	/*
+	 * app/library function that provides cached secrets
+	 */
+	char * safe_cached_secret(app_data_t *app)
+	{
+		char *secret;
+		volatile unsigned int *const genid_ptr = get_sysgenid_mapping(app);
+	again:
+		secret = __cached_secret(app);
+
+		if (unlikely(*genid_ptr != app->cached_genid)) {
+			app->cached_genid = *genid_ptr;
+			barrier();
+
+			// rebuild world then confirm the genid update (thru write)
+			rebuild_caches(app);
+
+			ack_sysgenid_update(app);
+
+			goto again;
+		}
+
+		return secret;
+	}
+
+4) Orchestrator simplified example::
+
+	/*
+	 * orchestrator - manages multiple applications and libraries used by
+	 * a service and tries to make sure all sensitive components gracefully
+	 * handle VM generation changes.
+	 * Following function is called on detection of a VM generation change.
+	 */
+	int handle_sysgen_update(int sysgen_fd, unsigned int new_gen_id)
+	{
+		// pause until all components have handled event
+		pause_service();
+
+		// confirm *this* watcher as up-to-date
+		write(sysgen_fd, &new_gen_id, sizeof(unsigned int));
+
+		// wait for all *others* for at most 5 seconds.
+		ioctl(sysgen_fd, VMGENID_WAIT_WATCHERS, 5000);
+
+		// all applications on the system have rebuilt worlds
+		resume_service();
+	}
```
#### [PATCH] uio: uio_pci_generic: don't fail probe if pdev->irq equals to IRQ_NOTCONNECTED
##### From: "jie6.li" <jie6.li@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "jie6.li" <jie6.li@samsung.com>
X-Patchwork-Id: 12058029
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9B40DC433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 04:32:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 56C2A64E2B
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 04:32:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231475AbhBAEbN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 31 Jan 2021 23:31:13 -0500
Received: from mailout1.samsung.com ([203.254.224.24]:41565 "EHLO
        mailout1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231472AbhBAE3U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 31 Jan 2021 23:29:20 -0500
Received: from epcas5p4.samsung.com (unknown [182.195.41.42])
        by mailout1.samsung.com (KnoxPortal) with ESMTP id
 20210201042802epoutp01248d2501780ad223b2e0e841c005d918~fhTuPqItM1196311963epoutp01S
        for <kvm@vger.kernel.org>; Mon,  1 Feb 2021 04:28:02 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.samsung.com
 20210201042802epoutp01248d2501780ad223b2e0e841c005d918~fhTuPqItM1196311963epoutp01S
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1612153682;
        bh=wYGV5gWfecQFhg6xzaMF6JtUcCvRNBh8Pi1Z/2G9s0w=;
        h=From:To:Cc:Subject:Date:References:From;
        b=Gn+9ZK6RdbrxVtxQs5SmadJA1whOY+M28nQSm2bFGSF1/YF7o5B7Tt2ytFXYMPcp2
         7ulDKqjikAc+yMZC1A3p3+6T4ULvlIaP4YWaoLK7rbrnFxc778TfTTOKcBSct+u6j7
         rXPYv9yT1JPpoNTmyh0BTyH6/tB58MDaYv7hrk8c=
Received: from epsnrtp4.localdomain (unknown [182.195.42.165]) by
        epcas5p3.samsung.com (KnoxPortal) with ESMTP id
        20210201042801epcas5p3379a03a22ef539b8bbcbfa309ad6f767~fhTtnbOGb1572215722epcas5p38;
        Mon,  1 Feb 2021 04:28:01 +0000 (GMT)
Received: from epsmges5p1new.samsung.com (unknown [182.195.40.194]) by
        epsnrtp4.localdomain (Postfix) with ESMTP id 4DTZgM3kzdz4x9Q9;
 Mon,  1 Feb
        2021 04:27:59 +0000 (GMT)
Received: from epcas5p4.samsung.com ( [182.195.41.42]) by
        epsmges5p1new.samsung.com (Symantec Messaging Gateway) with SMTP id
        63.03.15682.F4387106; Mon,  1 Feb 2021 13:27:59 +0900 (KST)
Received: from epsmtrp2.samsung.com (unknown [182.195.40.14]) by
        epcas5p1.samsung.com (KnoxPortal) with ESMTPA id
        20210201042758epcas5p1a6cb788bf5eb1bf85efa66662db2edf6~fhTq-u34C3002330023epcas5p1r;
        Mon,  1 Feb 2021 04:27:58 +0000 (GMT)
Received: from epsmgms1p2.samsung.com (unknown [182.195.42.42]) by
        epsmtrp2.samsung.com (KnoxPortal) with ESMTP id
        20210201042758epsmtrp2eb63960f9e83c78101e1281f64552e43~fhTq_0gW-0999509995epsmtrp2j;
        Mon,  1 Feb 2021 04:27:58 +0000 (GMT)
X-AuditID: b6c32a49-8bfff70000013d42-68-6017834f8036
Received: from epsmtip1.samsung.com ( [182.195.34.30]) by
        epsmgms1p2.samsung.com (Symantec Messaging Gateway) with SMTP id
        21.D0.08745.E4387106; Mon,  1 Feb 2021 13:27:58 +0900 (KST)
Received: from localhost.localdomain (unknown [109.105.112.123]) by
        epsmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20210201042657epsmtip1482c387050911ba311e23757f522a620~fhSxTDb1x0727807278epsmtip1b;
        Mon,  1 Feb 2021 04:26:50 +0000 (GMT)
From: "jie6.li" <jie6.li@samsung.com>
To: gregkh@linuxfoundation.org
Cc: mst@redhat.com, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        ks0204.kim@samsung.com, xing84.he@samsung.com,
        gaofei.lv@samsung.com, jie6.li@samsung.com, security.xa@samsung.com
Subject: [PATCH] uio: uio_pci_generic: don't fail probe if pdev->irq equals
 to IRQ_NOTCONNECTED
Date: Mon,  1 Feb 2021 04:25:59 +0000
Message-Id: <1612153559-17028-1-git-send-email-jie6.li@samsung.com>
X-Mailer: git-send-email 2.6.4.windows.1
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFjrFKsWRmVeSWpSXmKPExsWy7bCmlq5/s3iCweVeSYtdizeyWDQvXs9m
        MXtaK7vF0T0cFnOmFlpc3jWHzeL/r1esFmcnfGC12Nvn48DpsX/uGnaP9/uusnn0bVnF6PF5
        k1wAS1SOTUZqYkpqkUJqXnJ+SmZeuq2Sd3C8c7ypmYGhrqGlhbmSQl5ibqqtkotPgK5bZg7Q
        IUoKZYk5pUChgMTiYiV9O5ui/NKSVIWM/OISW6XUgpScAkOjAr3ixNzi0rx0veT8XCtDAwMj
        U6DKhJyMf18msxZ85qzoWFXWwLiCo4uRk0NCwETi35ZnzF2MXBxCArsZJW623WGBcD4xSqza
        /hUq85lRYu2UqUwwLQt7XzNBJHYxSty/vJMVwvnKKNH5/zc7SBWbgKrEj5Wn2UBsEQE5iSe3
        /zCD2MwCexklvs5wBbGFBRIllnZ9ZgGxWYDqv5zrAtvAK+AscWDDARaIbRoS6zv2g90kIbCJ
        XWJ7/2E2iISLxMNpS9khbGGJV8e3QNlSEp/f7YWqqZc48/sIO0RzB6PEzoufWCES1hIXV98A
        uogD6CJNifW79CGO45Po/f2ECSQsIcAr0dEmBFGtKDH73C6oe8QlXr57xAhhe0jc/XoKbK2Q
        QKzEog/3mCYwysxCGLqAkXEVo2RqQXFuemqxaYFhXmo5cuRsYgQnKi3PHYx3H3zQO8TIxMF4
        iFGCg1lJhPfUJLEEId6UxMqq1KL8+KLSnNTiQ4ymwHCayCwlmpwPTJV5JfGGpkZmZgaWBqbG
        FmaGSuK8OwwexAsJpCeWpGanphakFsH0MXFwSjUwLV6zV3ZX5+rn+1UOpapWsfis2qF78sMl
        9R7Gb0q/5rU5brT2Lp339cEDltJ1K6ec2rFSV0pF/M/rhmAd20MO86bzdj7bfVfiZw2HY9bN
        OA3LT0mb4gQ0Th5jjKv3SZDOqr8VnvFR1GfNnQO1nFNP3fk6dX3av+p6ERkFyV2adT7qn3ru
        MjGrr9Qt49/FtbNo75q8S+mXpDb59k6Y8OLWvEoX/quLo1Zv95nSe5dzLvc13WlXJvXsnfR2
        blSozOKvRemLPj26kfXDIszU7cXPqOmttqd8NpjbVc9jXNcyT0va4vHs+rd3Vu2d3rvx0bX/
        j69+Y5ln2l0hyhwryBc3a8U/+yt1X9b5dzXq9T4/FKfEUpyRaKjFXFScCADqHGXN3QMAAA==
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFmpgluLIzCtJLcpLzFFi42LZdlhJTtevWTzB4Ng5E4tdizeyWDQvXs9m
        MXtaK7vF0T0cFnOmFlpc3jWHzeL/r1esFmcnfGC12Nvn48DpsX/uGnaP9/uusnn0bVnF6PF5
        k1wASxSXTUpqTmZZapG+XQJXxr8vk1kLPnNWdKwqa2BcwdHFyMkhIWAisbD3NROILSSwg1Fi
        2s4iiLi4xKFVP1ghbGGJlf+es3cxcgHVfGaU2P5iB1gDm4CqxI+Vp9lAbBEBOYknt/8wgxQx
        CxxnlHh7YDJYQlggXmJj6yswmwWo4cu5LrBmXgFniQMbDrBAbNCQWN+xn2UCI88CRoZVjJKp
        BcW56bnFhgVGeanlesWJucWleel6yfm5mxjBgaSltYNxz6oPeocYmTgYDzFKcDArifCemiSW
        IMSbklhZlVqUH19UmpNafIhRmoNFSZz3QtfJeCGB9MSS1OzU1ILUIpgsEwenVAPTuthbvLKr
        Ln48/XiKW6Cp0721L3+6Tpw1Je5s5HeueX4l16Tvef9UPMSdeGHlx5Cpsw9YG6qc/su1O0fg
        1b1Zk01NclUPLn1bqSnNcG7yyivlVrovxa4fKjb8x/GqxqKgN5vzZbOnqNXNjfG1dzcnxC43
        uLf27+Y3LVGnrnksfZrwskcu4vyRG72lKwOnPvexfrzB+yHf3LrLIiJh+xLNm9vXnlj1WtZl
        l+iVxnezbO4Zt+45ZOB2ZtbeAr5YG9/kTRVOd+ZGf7Co2ihgFsvSzcIcabz5avbkLJ6wGblJ
        vvba38Lerfn7amnyh4vRChMmxhvMen/E51n3ojyD1ed3bf077aKd2rlpBcvXdZr9ilZiKc5I
        NNRiLipOBADHKPW8kwIAAA==
X-CMS-MailID: 20210201042758epcas5p1a6cb788bf5eb1bf85efa66662db2edf6
X-Msg-Generator: CA
CMS-TYPE: 105P
DLP-Filter: Pass
X-CFilter-Loop: Reflected
X-CMS-RootMailID: 20210201042758epcas5p1a6cb788bf5eb1bf85efa66662db2edf6
References: 
 <CGME20210201042758epcas5p1a6cb788bf5eb1bf85efa66662db2edf6@epcas5p1.samsung.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jie Li <jie6.li@samsung.com>

Some devices use 255 as default value of Interrupt Line register, and this
maybe causes pdev->irq is set as IRQ_NOTCONNECTED in some scenarios. For
example, NVMe controller connects to Intel Volume Management Device (VMD).
In this situation, IRQ_NOTCONNECTED means INTx line is not connected, not
fault. If bind uio_pci_generic to these devices, uio frame will return
-ENOTCONN through request_irq.

This patch allows binding uio_pci_generic to device with dev->irq of
IRQ_NOTCONNECTED.

Signed-off-by: Jie Li <jie6.li@samsung.com>
Acked-by: Kyungsan Kim <ks0204.kim@samsung.com>
---
 drivers/uio/uio_pci_generic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12058377
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF315C433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:37:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D02F64E49
	for <kvm@archiver.kernel.org>; Mon,  1 Feb 2021 08:37:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232392AbhBAIhh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 03:37:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37186 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229736AbhBAIhg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 03:37:36 -0500
Received: from mail-pg1-x52c.google.com (mail-pg1-x52c.google.com
 [IPv6:2607:f8b0:4864:20::52c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2707AC061573;
        Mon,  1 Feb 2021 00:36:56 -0800 (PST)
Received: by mail-pg1-x52c.google.com with SMTP id j2so9937944pgl.0;
        Mon, 01 Feb 2021 00:36:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=eVINvg/Fw9V8hooodk2Ygvx8KN7ol+WUF2ilOSjWNrQ=;
        b=Nj1jwMQ3BLyOEU9G7jUae9Ir45WM27dbdJkb5RAkU+3teGa59eOJkXNV6ESVQJ+X34
         3qkKryIAX8hQRWgKeattWPAmBEZCqUtvTwv0yLyX/NO1ubjnqNy0/M4ewa+QCrWUKWDl
         5z8UEjYEv3PuWLfyKldEPTIYbquhRCLFOksH9ugAJZAQxWJgOAjg53hoqXg8XMPx6lBU
         9nZhy6Yy75LHuXII1dIYDRzPfGQpMGXagoOZ04pVXVNWEiDby3c3dD6vfwRaEMH9FEAI
         XLtZRxO4PlQ+WUYzHqlGeuuHPUOVk3ncXq3GX/8zLRNwMY4iZh0MzDYpNgUHKvrs7I8D
         A+Yw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=eVINvg/Fw9V8hooodk2Ygvx8KN7ol+WUF2ilOSjWNrQ=;
        b=UiG0Tslyv6NmqV6PogbhPX0vn8BVWPF5g4PZp3jeGkQ/COilCfeCtVhhORxg/hzyUd
         +xw6JpqDMhJRJRpJiDo57VUsIywH2SzjnjBWs5Wf9UZ+Ok7Wy37uuMzrqfgw8BL4qm9y
         7cANAlGYC8t8vNeob5weJgGhJj19+kZfftpQsG8V3Hek0IBNpFU1eDuY51MRlUTpe60o
         QeDJ71ntdni2BYQSFALHNE4j+XbigXW4RiwwfbiuavekSt/4SHGZO9O2eXUxmCRejfWN
         AvowDiq3aqy5hu4N+Ilz/7GXB7EpXp0mO7Yi1xff+qsLIHLoWcb1lYBa2dGF2gf0fAgF
         uUWQ==
X-Gm-Message-State: AOAM531lNspjhlurC8rRgvlps4HJ4dt5mplNx25UEsktmaFwCQHSY4BG
        NuE0nlIi1N2rS0fJa6hYhjd7SNTwAsPpng==
X-Google-Smtp-Source: 
 ABdhPJzJjlaC3zpkzKamcZUZW5v4s6e6oNTOtMTymP4gZzLu8JTAVNzp83KtRgZ3oKOKid3mcFZQrw==
X-Received: by 2002:a63:5526:: with SMTP id
 j38mr16180273pgb.177.1612168615250;
        Mon, 01 Feb 2021 00:36:55 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 t25sm17234032pgv.30.2021.02.01.00.36.52
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 01 Feb 2021 00:36:54 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v3] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
Date: Mon,  1 Feb 2021 16:36:27 +0800
Message-Id: <1612168596-3782-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The per-cpu vsyscall pvclock data pointer assigns either an element of the 
static array hv_clock_boot (#vCPU <= 64) or dynamically allocated memory 
hvclock_mem (vCPU > 64), the dynamically memory will not be allocated if 
kvmclock vsyscall is disabled, this can result in cpu hotpluged fails in 
kvmclock_setup_percpu() which returns -ENOMEM. It's broken for no-vsyscall
and sometimes you end up with vsyscall disabled if the host does something 
strange. This patch fixes it by allocating this dynamically memory 
unconditionally even if vsyscall is disabled.

Fixes: 6a1cac56f4 ("x86/kvm: Use __bss_decrypted attribute in shared variables")
Reported-by: Zelin Deng <zelin.deng@linux.alibaba.com>
Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: stable@vger.kernel.org#v4.19-rc5+
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reported-by: kernel test robot <lkp@intel.com>
Reported-by: kernel test robot <lkp@intel.com>
---
v2 -> v3:
 * allocate dynamically memory unconditionally
v1 -> v2:
 * add code comments

 arch/x86/kernel/kvmclock.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
