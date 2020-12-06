#### [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 11952651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2F540C4361A
	for <kvm@archiver.kernel.org>; Sat,  5 Dec 2020 00:49:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E718F22D70
	for <kvm@archiver.kernel.org>; Sat,  5 Dec 2020 00:49:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731194AbgLEAtD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 19:49:03 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:42454 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726567AbgLEAtC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 19:49:02 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1klLkE-0003Bx-1N; Sat, 05 Dec 2020 01:48:14 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, linux-doc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: mmu: Fix SPTE encoding of MMIO generation upper half
Date: Sat,  5 Dec 2020 01:48:08 +0100
Message-Id: 
 <156700708db2a5296c5ed7a8b9ac71f1e9765c85.1607129096.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

Commit cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
cleaned up the computation of MMIO generation SPTE masks, however it
introduced a bug how the upper part was encoded:
SPTE bits 52-61 were supposed to contain bits 10-19 of the current
generation number, however a missing shift encoded bits 1-10 there instead
(mostly duplicating the lower part of the encoded generation number that
then consisted of bits 1-9).

In the meantime, the upper part was shrunk by one bit and moved by
subsequent commits to become an upper half of the encoded generation number
(bits 9-17 of bits 0-17 encoded in a SPTE).

In addition to the above, commit 56871d444bc4 ("KVM: x86: fix overlap between SPTE_MMIO_MASK and generation")
has changed the SPTE bit range assigned to encode the generation number and
the total number of bits encoded but did not update them in the comment
attached to their defines, nor in the KVM MMU doc.
Let's do it here, too, since it is too trivial thing to warrant a separate
commit.

Fixes: cae7ed3c2cb0 ("KVM: x86: Refactor the MMIO SPTE generation handling")
Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
    The easiest way to reproduce the issue is to apply the patch
    below to the existing code and observe how memslots generations
```
