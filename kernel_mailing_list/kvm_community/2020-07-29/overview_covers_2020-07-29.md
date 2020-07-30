

#### [PATCH 0/4] KVM: SVM: SEV-ES groundwork
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Wed Jul 29 13:22:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11691015
Return-Path: <SRS0=6Tui=BI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C5486C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 13:23:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D39720829
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jul 2020 13:23:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727109AbgG2NWt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jul 2020 09:22:49 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49346 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727032AbgG2NWr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jul 2020 09:22:47 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 33655C061794;
        Wed, 29 Jul 2020 06:22:47 -0700 (PDT)
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 0062B3EC; Wed, 29 Jul 2020 15:22:44 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] KVM: SVM: SEV-ES groundwork
Date: Wed, 29 Jul 2020 15:22:30 +0200
Message-Id: <20200729132234.2346-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

here are some groundwork patches for the upcoming SEV-ES support in the
Linux kernel. They are part of both the client patch-set and of the KVM
hypervisor patches (under development).

Patch 1 necesary to fix a compile warning about a stack-frame getting
too large. The other 3 patches are currently posted as part of the
SEV-ES client patch-set.

It would be great if you could consider them for v5.9, so that the
client and the hypervisor patch-sets can be developed more independently
of each other.

Please let me know what you think.

Regards,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Joerg Roedel (2):
  KVM: SVM: nested: Don't allocate VMCB structures on stack
  KVM: SVM: Add GHCB Accessor functions

Tom Lendacky (1):
  KVM: SVM: Add GHCB definitions

 arch/x86/include/asm/svm.h | 118 ++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/svm/nested.c  |  44 +++++++++-----
 arch/x86/kvm/svm/svm.c     |   2 +
 3 files changed, 143 insertions(+), 21 deletions(-)
```
