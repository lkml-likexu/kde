

#### [kvm-unit-tests PATCH 0/5] x86: svm: fixes
##### From: Nadav Amit <namit@vmware.com>

```c
From patchwork Tue Jun 30 09:45:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11633585
Return-Path: <SRS0=5uRT=AL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0819B13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 09:48:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EA4B520775
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 09:48:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732119AbgF3JsV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 30 Jun 2020 05:48:21 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:49348 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732078AbgF3JsU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Jun 2020 05:48:20 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Tue, 30 Jun 2020 02:48:19 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id F0939B211F;
        Tue, 30 Jun 2020 05:48:19 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 0/5] x86: svm: fixes
Date: Tue, 30 Jun 2020 02:45:11 -0700
Message-ID: <20200630094516.22983-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Excluding the first patch, the others are bug-fixes for the svm tests,
that make the tests more robust, and less KVM-dependent.

The fourth patch might indicate there is a bug in KVM, but I did not get
to check it.

Nadav Amit (5):
  x86: Remove boot_idt assembly assignment
  x86: svm: check TSC adjust support
  x86: svm: flush TLB on each test
  x86: svm: wrong reserved bit in npt_rsvd_pfwalk_prepare
  x86: svm: avoid advancing rip incorrectly on exc_inject

 x86/cstart64.S  |  3 ---
 x86/svm.c       |  1 +
 x86/svm_tests.c | 15 ++++++++++-----
 3 files changed, 11 insertions(+), 8 deletions(-)
```
