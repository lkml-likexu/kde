#### [PATCH v2 1/6] KVM: nSVM: refactor the CR3 reload on migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12224171
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0702C43462
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:14:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B3B5613BF
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:14:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233348AbhDZLPQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 07:15:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40415 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233205AbhDZLPE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 07:15:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619435663;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=6XVGhAXBfo9MgQy1ty+oqe6SntrES8m23Sof78r/E/E=;
        b=IZXpeb5TvGbeASyH4WcqkzNxmY0dHKVSgTvd1sp9nX6qBLJER3Z41Hqn8YKJKQL6oNAasD
        /fvupI8n3pTbjMe9yJM3K5hYyrZrwArPdplJyH060xXPmEyoCgCO20dVimK75mM2Bvy5Si
        sK+lgPGrUMT0+vahbxAoItuFQB9BkK4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-141-T7jfQD7PPQiPaeAlmnN-3A-1; Mon, 26 Apr 2021 07:14:21 -0400
X-MC-Unique: T7jfQD7PPQiPaeAlmnN-3A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D124F108BC2F;
        Mon, 26 Apr 2021 11:13:45 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.192.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 316595D9D0;
        Mon, 26 Apr 2021 11:13:40 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        Thomas Gleixner <tglx@linutronix.de>,
        Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/6] KVM: nSVM: refactor the CR3 reload on migration
Date: Mon, 26 Apr 2021 14:13:28 +0300
Message-Id: <20210426111333.967729-2-mlevitsk@redhat.com>
In-Reply-To: <20210426111333.967729-1-mlevitsk@redhat.com>
References: <20210426111333.967729-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Document the actual reason why we need to do it
on migration and move the call to svm_set_nested_state
to be closer to VMX code.

To avoid loading the PDPTRs from possibly not up to date memory map,
in nested_svm_load_cr3 after the move, move this code to
.get_nested_state_pages.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 32 +++++++++++++++++++++++++-------
 1 file changed, 25 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: arm64: Skip CMOs when updating a PTE pointing to non-memory
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12224151
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77E56C433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 10:36:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2BED3611CE
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 10:36:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232933AbhDZKgz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 06:36:55 -0400
Received: from mail.kernel.org ([198.145.29.99]:60254 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232800AbhDZKgy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 06:36:54 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id EA44761185;
        Mon, 26 Apr 2021 10:36:12 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1layb4-009SqT-Lt; Mon, 26 Apr 2021 11:36:10 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Krishna Reddy <vdumpa@nvidia.com>,
        Sumit Gupta <sumitg@nvidia.com>
Subject: [PATCH] KVM: arm64: Skip CMOs when updating a PTE pointing to
 non-memory
Date: Mon, 26 Apr 2021 11:36:05 +0100
Message-Id: <20210426103605.616908-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 suzuki.poulose@arm.com, alexandru.elisei@arm.com, kernel-team@android.com,
 jean-philippe@linaro.org, vdumpa@nvidia.com, sumitg@nvidia.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sumit Gupta and Krishna Reddy both reported that for MMIO regions
mapped into userspace using VFIO, a PTE update can trigger a MMU
notifier reaching kvm_set_spte_hva().

There is an assumption baked in kvm_set_spte_hva() that it only
deals with memory pages, and not MMIO. For this purpose, it
performs a cache cleaning of the potentially newly mapped page.
However, for a MMIO range, this explodes as there is no linear
mapping for this range (and doing cache maintenance on it would
make little sense anyway).

Check for the validity of the page before performing the CMO
addresses the problem.

Reported-by: Krishna Reddy <vdumpa@nvidia.com>
Reported-by: Sumit Gupta <sumitg@nvidia.com>,
Tested-by: Sumit Gupta <sumitg@nvidia.com>,
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/5a8825bc-286e-b316-515f-3bd3c9c70a80@nvidia.com
---
 arch/arm64/kvm/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: selftests: Speed up set_memory_region_test
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12224241
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9937BC433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 13:01:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6916861103
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 13:01:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233567AbhDZNCP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 09:02:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25865 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233549AbhDZNCK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 09:02:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619442089;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+/MOXnX9h7hR/cxq9q03AL7bpej16e5GaIUuHzQUeWc=;
        b=YBWBCoS6voYBYJ8E0/m7MlI+YdmY9XeMnAvphj7mwFUZGwCbML/rh4FdaPIV/5OWQ85VIR
        olAISZzqTObtTS8Wf8eg+X14HKCpdDgx9MrF4itS7C7EvLkJDI2lBQEpudWqHTKE5+Wxmv
        9eYYs40H6G0Y3bXF3HxWq39B5MtJYes=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-339-_QcW6wdhPr6ldfNflr999w-1; Mon, 26 Apr 2021 09:01:25 -0400
X-MC-Unique: _QcW6wdhPr6ldfNflr999w-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 473861922963;
        Mon, 26 Apr 2021 13:01:24 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.54])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B41C5C1CF;
        Mon, 26 Apr 2021 13:01:22 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        kernel test robot <oliver.sang@intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: selftests: Speed up set_memory_region_test
Date: Mon, 26 Apr 2021 15:01:21 +0200
Message-Id: <20210426130121.758229-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit 4fc096a99e01 ("KVM: Raise the maximum number of user memslots")
set_memory_region_test may take too long, reports are that the default
timeout value we have (120s) may not be enough even on a physical host.

Speed things up a bit by throwing away vm_userspace_mem_region_add() usage
from test_add_max_memory_regions(), we don't really need to do the majority
of the stuff it does for the sake of this test.

On my AMD EPYC 7401P, # time ./set_memory_region_test
pre-patch:
 Testing KVM_RUN with zero added memory regions
 Allowed number of memory slots: 32764
 Adding slots 0..32763, each memory region with 2048K size
 Testing MOVE of in-use region, 10 loops
 Testing DELETE of in-use region, 10 loops

 real	0m44.917s
 user	0m7.416s
 sys	0m34.601s

post-patch:
 Testing KVM_RUN with zero added memory regions
 Allowed number of memory slots: 32764
 Adding slots 0..32763, each memory region with 2048K size
 Testing MOVE of in-use region, 10 loops
 Testing DELETE of in-use region, 10 loops

 real	0m20.714s
 user	0m0.109s
 sys	0m18.359s

Reported-by: kernel test robot <oliver.sang@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../selftests/kvm/set_memory_region_test.c    | 61 ++++++++++++++-----
 1 file changed, 45 insertions(+), 16 deletions(-)

```
#### [PATCH v2 1/2] kvm: update kernel headers for KVM_{GET|SET}_SREGS2
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12224201
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45975C433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:59:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0EA6B60FE6
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 11:59:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233242AbhDZL7q (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 07:59:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:56478 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233225AbhDZL7q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 07:59:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619438344;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=2xfjkPnQFPRjK9jBH/26YtD7u3pk0Xa3TCgZG3qQIhc=;
        b=Fe+2+Gl/NMo0Fc5BiRnKp1frHtA61IrztRLRdOuhDAyM1ne98NI4vM5Owj7U2pKbs0/MbR
        99VHULW2S8Z651dIV4DS71FYL1TjUj7i0IrQ4bPdxkMu2QbupQSa5nIce9IrhQuLJgttt7
        TKXEkdsoYRZaPV5yOZ4CwTNs/zltIBQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-234-ozEL8TJpNJ6EPfoL1Ru9mQ-1; Mon, 26 Apr 2021 07:59:02 -0400
X-MC-Unique: ozEL8TJpNJ6EPfoL1Ru9mQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 695596409F;
        Mon, 26 Apr 2021 11:59:01 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.192.73])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8FF9560855;
        Mon, 26 Apr 2021 11:58:58 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <richard.henderson@linaro.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/2] kvm: update kernel headers for KVM_{GET|SET}_SREGS2
Date: Mon, 26 Apr 2021 14:58:49 +0300
Message-Id: <20210426115850.1003501-2-mlevitsk@redhat.com>
In-Reply-To: <20210426115850.1003501-1-mlevitsk@redhat.com>
References: <20210426115850.1003501-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 linux-headers/asm-x86/kvm.h | 13 +++++++++++++
 linux-headers/linux/kvm.h   |  5 +++++
 2 files changed, 18 insertions(+)

```
#### [PATCH v2 01/13] vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12225001
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2D1F6C43461
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 20:00:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F2F01613AB
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 20:00:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241779AbhDZUBH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 16:01:07 -0400
Received: from mail-bn8nam08on2069.outbound.protection.outlook.com
 ([40.107.100.69]:56800
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236419AbhDZUBE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 16:01:04 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=j+ukxqcu7nU3LVgjmkbi9PlwFDALK6x8agUkHlWzXp3BPBb/P5eDHaczlx5AAlmDJ/rHg16o7SBIRxCNIoDI6TS3ZUlWw53luJ5RgrWoCMynClnSjHOFYrbO1Mt4/nQ1sL2mVky9uuticmRS5Ps6xPSUyZVrAea/fmCuth6nwMjw54Ar4nuxfShR63QVw+LqhBym8Dp88jqX9efr+uACnBhfs8dGIXQNita13d61WMycpXaA66m42OMjefIcfLmDRtUaoSjLluLUAxah0xi0GHdMNOuBAhcWCRHvKJ7Ja91sgEhsjQbQm9WcwrNfjm/nuJB1D6tn1mjfJjVmiR4SPQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jtA9wwpcl5JsAiPwSoFC0d2L/Z2niX9OyeZRyPl5MMU=;
 b=UXVf/ig2+rDcP+p4A57xmHmD0MEP5LsS5jgo23eXhTDO0x9tSLXNptvx8J0vEK6MRLESLItnnMOH52oZhQMFmvNQmvpsXD0a/3NNRjnoaGI6KtOufKQySoMNYmTlLoRoe+yEOon9PAXOdK77Uo1ZSyR6bM0OUlMZtBqIKgzzxT2dkIJ0yTgDhKTAnDAVDhMH8+/q0qv4XkYZkM0hAikXFszXdXMqjDmEd7mqAlAusLw+ko+qWUeKdlu7IVn91D2sSEtrAryDHvNvKkUTWa2J1eqmXSOsuqGuXs2uBsS8QStbU1594cJVb9Zgo6T0p7JNcCPZYIP/UjkRYmIerhF80A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jtA9wwpcl5JsAiPwSoFC0d2L/Z2niX9OyeZRyPl5MMU=;
 b=jlQhxHbmtQRvFq52UaPfBa3oLZvvqrlyB1viVjI2goU8Xg9ZuA/p2e9nxVCtr9jMsdRZid7kZghwwZ8c3ZtU3s8lhOaqZ8VGdhPTvsLhcvUMtWfblcgkuyMU0oWeydvY831KkR/Wop3g6s2mj3n18oES6u3D2BqyRqWJ4xml87lqdJAVFAbcrOmaneb4FhnQi9R5n6XEuU3YXA5LVi1Un499PPKcq2E94VVy2tuJxch3S3ed9v4Bw/VOONJo+10fltW0KlFRcBmMevQVE6h8g+l+ic22Cep7O+SapU6sSs2EBXQ+htC7/7uIoFm9fS8n9yGtxHEKrnqnJa4SlsOuOA==
Authentication-Results: linux.ie; dkim=none (message not signed)
 header.d=none;linux.ie; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB3740.namprd12.prod.outlook.com (2603:10b6:5:1c3::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.24; Mon, 26 Apr
 2021 20:00:17 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.4065.026; Mon, 26 Apr 2021
 20:00:17 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org, Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v2 01/13] vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
Date: Mon, 26 Apr 2021 17:00:03 -0300
Message-Id: <1-v2-7667f42c9bad+935-vfio3_jgg@nvidia.com>
In-Reply-To: <0-v2-7667f42c9bad+935-vfio3_jgg@nvidia.com>
References: 
X-Originating-IP: [47.55.113.94]
X-ClientProxiedBy: MN2PR03CA0017.namprd03.prod.outlook.com
 (2603:10b6:208:23a::22) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (47.55.113.94) by
 MN2PR03CA0017.namprd03.prod.outlook.com (2603:10b6:208:23a::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21 via Frontend
 Transport; Mon, 26 Apr 2021 20:00:16 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lb7Ox-00DFZ1-Nc; Mon, 26 Apr 2021 17:00:15 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: b17b8c4c-bd39-4092-1806-08d908ede983
X-MS-TrafficTypeDiagnostic: DM6PR12MB3740:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB374005A85DC3EFECE94B3DD4C2429@DM6PR12MB3740.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 IGsk/G6BFzdQ/d66UubgFTPbSA0Ofp8xyI+upAcv+BiKwlKrCuztEE1H9Cuq7z+8Ad2Wo1hY9KWTPXwnqzSLklCTJdZxEeyTJfg6vxHjFbB6K/1YrS3rMceKN7RX/NV9N3V1XGuU4k2/30UgBMgrppKyxkwhXfb5f58uC2x8bR4K3YYCDiweTryig/aYPRK+I3cE+4+O4y/EOqpGYXa+RoEDnv/b1REJgExaxiiE2EJHNVAbCpLXEbghnNlPRp/W43btTP35vRp8QmvOx9qtMY50efDA8+3JnrIX8/G07qFEgUx3zQmKf39g8+BAEsJl95mg0JMrYgkWpqPN+H4VNoluS23caBSNMiEvcgxLhjCN7HjOVZgZq8+yfcF44pDmPdPMWOzwbUdAEtT1xc/owIiGlDpGrLLJ337O5UmYdZ/V/GpGWNoBfMG4uSzAOWVAKqwKIpQg9ZvTOVDnlBm5JopKuouOaAtrQjHiaZnlELul3REQQmTJyzElKDZBwYOV1uJR4KN75bouCYiSICJjBmM6BpG3LvKUtIzxmYINAkYezV5Z2OUvaLRAnd5V34HDnEOrNwD1IcorMCdvAhapQjxJktfne5sAqYcgOoGz8pN3ee0lcJgKzb1TOMR/4DYPo6an3BCRNZBiDD+BAAOWag6yfDWDgNCYIJs9ymgBz2I=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(346002)(136003)(396003)(376002)(66476007)(66556008)(9746002)(54906003)(426003)(110136005)(107886003)(186003)(26005)(921005)(6666004)(36756003)(316002)(2906002)(2616005)(478600001)(9786002)(8936002)(83380400001)(38100700002)(86362001)(8676002)(5660300002)(7416002)(4326008)(66946007)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 4668C+mMB/GSGBx2Op/LyjMn0yWxu6ae6SEfv+tyX++o6c6pp5IZZVyh1YayThMSstglxJW+eKHKPiN2mOZWZHNAj/xETqCjDHt2FxdOZ8nfoeKTZgUHoi1VSJZKBJ+qpsBjr1yquUNLds6Kt/lYaD5hlYGDITtJj60kv4wcJ5EMcIxVPUVErXothW/PNIEvtzwmIMK872wKTyRrVPcX/C+0dX5f6vpDK2tnrN4W7wJssTx9WgRZqdr44ozqAOQAQWuDWdkgkJcKrnA76O4vkUI+s276rm5CYzTt/kfcNtHnvpezTdQhJA6sJ0UMd2YdpT96Q6/rVt8eYxV3RG8J7Mlzu4XGtYIuu3LHQwPKEiyEUbF5y1UbZzqxVQpKmBZVBFUIY+iH0SDAoZuXf6B+YXTz35i/ulMmmMA00MCtV5ooTvI/MJDFBFfptPB+8cpieLCcWR2bIM19mnuhPuNdmVbiiknYa5dgtcb/dKunBXQs6j+T4b8q9yzAhTXRrz4vGfUHDPJh8Hh1+860a+ILIqx+2fjxHoMhtMVBYc/99qmRIAOZyzJxCe5ZGz6hIuSDbi1kDymzEoNkgC677L6Xlv464GRvBcCGAAeoOidZNBz6mL2CrPt1eJE4BhxPGucmYyPA1NG/b6WD2qoMjSuESVmk9bCMOuv1E/H9yOeeuIgYek1ZMdnN936bdK8wqCsT/rPnChi0vCkljY40wJ+2s3iMZPW82yYux6oKF3Ai+iIhEwaBmUvwGWim+Fy6FLAGZP4DYe6og7spOgxEh03/dpYqImDTSJzHnXRGgKcZZRN4mzp0cUbVaJ868KZM7bDci83H1hgeS9nBJgnt5ePsd2j1ERoTRnNIDCkwi63/pab3Rcg/mVZjhTSeoAGrigpBOfkqvvwSi8t/vpk9uv/3vglf8wysL2kWV/uHlrGLxtbyuXlY1nQS9rAUPvCRvYmSWDu0RPLaFInzdWqvB1fj+1yT7tQNXQHZLGlWSdbUvKau1YQB5/ENtSjg4sXoIFdSFyulfgQXAH3Kt2aXCNDnOp+LTCkMRf8TQuLpADn1XY0Q2/jHJRW0JjnkcFoZWvMa0J8e1VQ+bScDf5Hp0KwDCowPL9ylzPMJ3fnoH4NFG2PfrokKOo3AwNY9RFQBq8E7G253N/aufIHiKHhk/OH/xoR5PYeSUih3wdo81b6jhgk6D+WizkVy0n8I5GiAazJ5qymkiQcaUthRVvbiTWGYpR4m0xD6FESXYofqEuACIeYeNEMk4SuV0ZLi9r/yE9QyHvKumCoTOTgzXso36xnx6kbJWqxfNHsvRcUrGUc65SkJQEIsaQ9VqtO2E0wPZJow
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b17b8c4c-bd39-4092-1806-08d908ede983
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Apr 2021 20:00:17.1567
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 /yVSitDYXtdMgF8tlUDHEN2jM1cKvm0Y606CkejsWT49Zi2ZHdOvYsLqtVih7d/t
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3740
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For some reason the vfio_mdev shim mdev_driver has its own module and
kconfig. As the next patch requires access to it from mdev.ko merge the
two modules together and remove VFIO_MDEV_DEVICE.

A later patch deletes this driver entirely.

Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 Documentation/s390/vfio-ap.rst   |  1 -
 arch/s390/Kconfig                |  2 +-
 drivers/gpu/drm/i915/Kconfig     |  2 +-
 drivers/vfio/mdev/Kconfig        |  7 -------
 drivers/vfio/mdev/Makefile       |  3 +--
 drivers/vfio/mdev/mdev_core.c    | 16 ++++++++++++++--
 drivers/vfio/mdev/mdev_private.h |  2 ++
 drivers/vfio/mdev/vfio_mdev.c    | 24 +-----------------------
 samples/Kconfig                  |  6 +++---
 9 files changed, 23 insertions(+), 40 deletions(-)

```
#### [PATCH] selftests: kvm: Fix the check of return value
##### From: Zhenzhong Duan <zhenzhong.duan@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@intel.com>
X-Patchwork-Id: 12223775
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_12_24,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C8E4C433ED
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 03:31:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D6C3611CD
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 03:31:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231609AbhDZDbr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 25 Apr 2021 23:31:47 -0400
Received: from mga17.intel.com ([192.55.52.151]:8388 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231346AbhDZDbq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 25 Apr 2021 23:31:46 -0400
IronPort-SDR: 
 9z0bDgbut7olTsu01nU4/dd4w0zLLGLxEvV2SF/lhOXxUX39Ynb6kkI4ICQJ3pJh0sWGF2ihmP
 N+Z/+IB6W53Q==
X-IronPort-AV: E=McAfee;i="6200,9189,9965"; a="176392665"
X-IronPort-AV: E=Sophos;i="5.82,251,1613462400";
   d="scan'208";a="176392665"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Apr 2021 20:31:05 -0700
IronPort-SDR: 
 bB9O3aSLWK9aR07i9WUD/2odNc3cEtdDAdTXNinlcUn9ETOOHDjJQJhpItHzXIavkkq7ShGmvg
 0MGfWl0AwxVQ==
X-IronPort-AV: E=Sophos;i="5.82,251,1613462400";
   d="scan'208";a="429183762"
Received: from duan-optiplex-7080.bj.intel.com ([10.238.156.114])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Apr 2021 20:31:03 -0700
From: Zhenzhong Duan <zhenzhong.duan@intel.com>
To: linux-kernel@vger.kernel.org
Cc: linux-kselftest@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, shuah@kernel.org,
        Zhenzhong Duan <zhenzhong.duan@intel.com>
Subject: [PATCH] selftests: kvm: Fix the check of return value
Date: Tue, 27 Apr 2021 03:31:38 +0800
Message-Id: <20210426193138.118276-1-zhenzhong.duan@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In vm_vcpu_rm() and kvm_vm_release(), a stale return value is checked in
TEST_ASSERT macro.

Fix it by assigning variable ret with correct return value.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@intel.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] uio: uio_pci_generic: add memory mappings
##### From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
X-Patchwork-Id: 12224945
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97468C433ED
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 19:09:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D81861158
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 19:09:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236636AbhDZTJq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 15:09:46 -0400
Received: from mail.savoirfairelinux.com ([208.88.110.44]:47722 "EHLO
        mail.savoirfairelinux.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234229AbhDZTJo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 15:09:44 -0400
X-Greylist: delayed 314 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 26 Apr 2021 15:09:44 EDT
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id 96F4E9C1604;
        Mon, 26 Apr 2021 15:03:47 -0400 (EDT)
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10032)
        with ESMTP id TfXJ-JMsE0YT; Mon, 26 Apr 2021 15:03:47 -0400 (EDT)
Received: from localhost (localhost [127.0.0.1])
        by mail.savoirfairelinux.com (Postfix) with ESMTP id 0A1829C1556;
        Mon, 26 Apr 2021 15:03:47 -0400 (EDT)
X-Virus-Scanned: amavisd-new at mail.savoirfairelinux.com
Received: from mail.savoirfairelinux.com ([127.0.0.1])
        by localhost (mail.savoirfairelinux.com [127.0.0.1]) (amavisd-new,
 port 10026)
        with ESMTP id CeQtMkjyRRcf; Mon, 26 Apr 2021 15:03:46 -0400 (EDT)
Received: from barbarian.mtl.sfl (unknown [192.168.51.254])
        by mail.savoirfairelinux.com (Postfix) with ESMTPSA id D506D9C0272;
        Mon, 26 Apr 2021 15:03:46 -0400 (EDT)
From: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
To: gregkh@linuxfoundation.org, mst@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] uio: uio_pci_generic: add memory mappings
Date: Mon, 26 Apr 2021 15:03:46 -0400
Message-Id: <20210426190346.173919-1-firas.ashkar@savoirfairelinux.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

import memory resources from underlying pci device, thus allowing
userspace applications to memory map those resources.

Signed-off-by: Firas Ashkar <firas.ashkar@savoirfairelinux.com>
---
:100644 100644 c7d681fef198 809eca95b5bb M	drivers/uio/uio_pci_generic.c
 drivers/uio/uio_pci_generic.c | 52 +++++++++++++++++++++++++++++------
 1 file changed, 43 insertions(+), 9 deletions(-)

```
#### [for-6.1 v2 1/2] Update linux headers to 5.12-rc8 + FUSE_SYNCFS
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 12224407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2387FC43460
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 15:21:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F0BD161059
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 15:21:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233934AbhDZPWg convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Mon, 26 Apr 2021 11:22:36 -0400
Received: from us-smtp-delivery-44.mimecast.com ([207.211.30.44]:32866 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233829AbhDZPWg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Apr 2021 11:22:36 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-wo_7cLM3NjiCwiIjsK-fyA-1; Mon, 26 Apr 2021 11:21:52 -0400
X-MC-Unique: wo_7cLM3NjiCwiIjsK-fyA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 26C04871377;
        Mon, 26 Apr 2021 15:21:51 +0000 (UTC)
Received: from bahia.redhat.com (ovpn-113-148.ams2.redhat.com [10.36.113.148])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 99564610F0;
        Mon, 26 Apr 2021 15:21:48 +0000 (UTC)
From: Greg Kurz <groug@kaod.org>
To: qemu-devel@nongnu.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>, kvm@vger.kernel.org,
        virtio-fs@redhat.com, Miklos Szeredi <miklos@szeredi.hu>,
        Vivek Goyal <vgoyal@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, Greg Kurz <groug@kaod.org>
Subject: [for-6.1 v2 1/2] Update linux headers to 5.12-rc8 + FUSE_SYNCFS
Date: Mon, 26 Apr 2021 17:21:34 +0200
Message-Id: <20210426152135.842037-2-groug@kaod.org>
In-Reply-To: <20210426152135.842037-1-groug@kaod.org>
References: <20210426152135.842037-1-groug@kaod.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

NOT YET IN UPSTREAM LINUX. DO NOT MERGE.

Signed-off-by: Greg Kurz <groug@kaod.org>
---
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/ethtool.h      | 54 ++++++-----
 include/standard-headers/linux/fuse.h         | 13 ++-
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
 20 files changed, 205 insertions(+), 27 deletions(-)

```
#### [RFC PATCH 1/6] x86/kvm: Reserve KVM_FEATURE_HOST_SUSPEND_TIME and MSR_KVM_HOST_SUSPEND_TIME
##### From: Hikaru Nishida <hikalium@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Hikaru Nishida <hikalium@chromium.org>
X-Patchwork-Id: 12224013
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D466EC433B4
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 09:10:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A7A0A61139
	for <kvm@archiver.kernel.org>; Mon, 26 Apr 2021 09:10:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232524AbhDZJK4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Apr 2021 05:10:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59946 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232718AbhDZJJQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Apr 2021 05:09:16 -0400
Received: from mail-pl1-x62f.google.com (mail-pl1-x62f.google.com
 [IPv6:2607:f8b0:4864:20::62f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DD2A1C061763
        for <kvm@vger.kernel.org>; Mon, 26 Apr 2021 02:08:26 -0700 (PDT)
Received: by mail-pl1-x62f.google.com with SMTP id s15so177053plg.6
        for <kvm@vger.kernel.org>; Mon, 26 Apr 2021 02:08:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=V50YyMbdbg4kQSCC5l/2b7FBtbZFhZcyEXS5Kc3/Kqk=;
        b=Za4K1kqevYO48etJVHFvsJSz5Lpt2B7otONeFbwl8U91tfs2k0ZWOgpaTPJvoqt87r
         GnZRGMhsbds1i7v30bAxXk5gcYXkOtmC8hBem5xAO+Hi8iW5e62iU0AlU5brTo4SNSyn
         JDC40NZFnx4VaEdPeYrHKVQeMEDa1Q9y1dXiI=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=V50YyMbdbg4kQSCC5l/2b7FBtbZFhZcyEXS5Kc3/Kqk=;
        b=jJ5u9cT1w4/L2svZYb8KFvgFIkkbWUX7piJ0xeIUBRkiXvo63gjRVJFb30DKZctpIo
         RrE7o2Fp3/5kCWIXJ+EJiZz2sLuahm08Pfrz+hBPh2AypgkpO2oqc6wJ3WjRLIPxLmPz
         H82zhDO40FyemdKkpdrMUmFXZ1EVz4xbnO0f9i/OHcdsaLcblaHk4DgNTIcXe0NpPxsg
         bc3TI3vU2hIgLD324QjbwwF36xsiROimAq2CoPZ4FWcUKSHc+iv0xOKssl8DJDl/eDKH
         Nm1YFrJCTUqnNJKZRBC6nLz4q4QxdA44lj1NhQXLJ9zNaRZSFFF3pj+dAv2kkbMzrPQz
         kWJw==
X-Gm-Message-State: AOAM532oBPv1JH7IFCMWJyry90tpDgNeenK61mSG3A3V+31XpCkoX5Bo
        avfq7hg4L7JsEt0iClxAG/VxNDomxTtyvQ==
X-Google-Smtp-Source: 
 ABdhPJyQGYzq+3+Y2biONIrwkE7niPYsewV7PhLNOyYleKr/TJht+Nwnjq940Dao4JQSvBYmyTDSFQ==
X-Received: by 2002:a17:902:d2c3:b029:ec:b1ce:c488 with SMTP id
 n3-20020a170902d2c3b02900ecb1cec488mr17905356plc.4.1619428106144;
        Mon, 26 Apr 2021 02:08:26 -0700 (PDT)
Received: from localhost (160.131.236.35.bc.googleusercontent.com.
 [35.236.131.160])
        by smtp.gmail.com with UTF8SMTPSA id
 m2sm10679322pgv.87.2021.04.26.02.08.24
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Mon, 26 Apr 2021 02:08:25 -0700 (PDT)
From: Hikaru Nishida <hikalium@chromium.org>
To: kvm@vger.kernel.org
Cc: suleiman@google.com, Hikaru Nishida <hikalium@chromium.org>,
        Jonathan Corbet <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC PATCH 1/6] x86/kvm: Reserve KVM_FEATURE_HOST_SUSPEND_TIME and
 MSR_KVM_HOST_SUSPEND_TIME
Date: Mon, 26 Apr 2021 18:06:40 +0900
Message-Id: <20210426090644.2218834-2-hikalium@chromium.org>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
In-Reply-To: <20210426090644.2218834-1-hikalium@chromium.org>
References: <20210426090644.2218834-1-hikalium@chromium.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change; just add documentation for
KVM_FEATURE_HOST_SUSPEND_TIME and its corresponding
MSR_KVM_HOST_SUSPEND_TIME to support virtual suspend timing injection in
later patches.

Signed-off-by: Hikaru Nishida <hikalium@chromium.org>
---

 Documentation/virt/kvm/cpuid.rst |  3 +++
 Documentation/virt/kvm/msr.rst   | 29 +++++++++++++++++++++++++++++
 2 files changed, 32 insertions(+)

```
