#### [PATCH] kvm: mmu: fix is_tdp_mmu_check when the TDP MMU is not in use
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11906441
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DC49AC55ABD
	for <kvm@archiver.kernel.org>; Sun, 15 Nov 2020 15:28:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3E93223C7
	for <kvm@archiver.kernel.org>; Sun, 15 Nov 2020 15:28:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LAqSXJo7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727059AbgKOP16 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 15 Nov 2020 10:27:58 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38314 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727042AbgKOP16 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 15 Nov 2020 10:27:58 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605454077;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tEILAmOv/3vnRK3BL1tBNlRIN1HW0Lh9cIAmXOTwRHs=;
        b=LAqSXJo7MhCNZGYUZyif28vjHj9Hd6cppfAWB2qR41sM07h5mukQenaAW0Fosf+3OJdWD/
        7xnKfirys4/TslPi4gdy9tpsHieXiWirDo9ebd0VJE5IbW8e0jVcD/j9BEJT09kiESd58V
        mftxMQZw5VVqXHMHKV1m2Bu7Imz5r5s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-366-dVX9a26FOB2wCnB7W9j7mQ-1; Sun, 15 Nov 2020 10:27:54 -0500
X-MC-Unique: dVX9a26FOB2wCnB7W9j7mQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 82240427C7;
        Sun, 15 Nov 2020 15:27:53 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A39321E78;
        Sun, 15 Nov 2020 15:27:53 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Ben Gardon <bgardon@google.com>
Subject: [PATCH] kvm: mmu: fix is_tdp_mmu_check when the TDP MMU is not in use
Date: Sun, 15 Nov 2020 10:27:52 -0500
Message-Id: <20201115152752.1625224-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In some cases where shadow paging is in use, the root page will
be either mmu->pae_root or vcpu->arch.mmu->lm_root.  Then it will
not have an associated struct kvm_mmu_page, because it is allocated
with alloc_page instead of kvm_mmu_alloc_page.

Just return false quickly from is_tdp_mmu_root if the TDP MMU is
not in use, which also includes the case where shadow paging is
enabled.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
