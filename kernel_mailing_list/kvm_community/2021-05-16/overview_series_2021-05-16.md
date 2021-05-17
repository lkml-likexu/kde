#### [PATCH v3 1/8] KVM: x86: Cache total page count to avoid traversing the memslot array
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12260647
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 05D89C43460
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 21:45:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6D6861159
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 21:45:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234204AbhEPVqY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 16 May 2021 17:46:24 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:54360 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234126AbhEPVqX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 May 2021 17:46:23 -0400
Received: from MUA
        by vps-vb.mhejs.net with esmtps  (TLS1.2) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1liOZ3-0007yk-LH; Sun, 16 May 2021 23:44:45 +0200
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
Subject: [PATCH v3 1/8] KVM: x86: Cache total page count to avoid traversing
 the memslot array
Date: Sun, 16 May 2021 23:44:27 +0200
Message-Id: 
 <eb1c881ce814705c83813f02a1a13ced96f1b1d1.1621191551.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <cover.1621191549.git.maciej.szmigiero@oracle.com>
References: <cover.1621191549.git.maciej.szmigiero@oracle.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

There is no point in recalculating from scratch the total number of pages
in all memslots each time a memslot is created or deleted.

Just cache the value and update it accordingly on each such operation so
the code doesn't need to traverse the whole memslot array each time.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/mmu/mmu.c          | 24 ------------------------
 arch/x86/kvm/x86.c              | 18 +++++++++++++++---
 3 files changed, 16 insertions(+), 28 deletions(-)

```
#### [PATCH v3 15/16] docs: virt: kvm: api.rst: replace some characters
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12260213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 05BA3C43461
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 10:18:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE1736117A
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 10:18:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232298AbhEPKUD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 16 May 2021 06:20:03 -0400
Received: from mail.kernel.org ([198.145.29.99]:37558 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231480AbhEPKTx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 May 2021 06:19:53 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 8941961242;
        Sun, 16 May 2021 10:18:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1621160317;
        bh=vfreIcvlPF/8OZus3kXkczSP81akAE9RkS16w+hHttA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=HwEBNtghW9V/jdln44alW/pcRzsAKaWn4I/FBghqmMFEbIuQ7jbjvX7EwOm4sZAtv
         U7plEhjM+Kpzj5sEyxEjZLAu/XL1lWRuZYeDJ+AwA5SoIj7fMOPbh8Md4LGXl2674a
         BXHfTHf5UM2qWrOJvM4hURQCGiu12+xLYon2xqrxGP91Pb6JDQh1sVTYfWFawDCssJ
         KhzbNsv8V320MvZpvPcYpNjv09gnSI2z+ei5vfB1EKGaxt1QDIp4SSpHka1MzzF+Ne
         XpP8fKHN7lFZeLw6ObJDJ6AAmhRcWRS0A6ipXLQXt0QwaJxZiRGlFa66Fo8IfVIXF5
         FymixdsGColjw==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1liDr1-003o96-Of; Sun, 16 May 2021 12:18:35 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 15/16] docs: virt: kvm: api.rst: replace some characters
Date: Sun, 16 May 2021 12:18:32 +0200
Message-Id: 
 <19f884773a95649e7b11609d8d3075f30db00aef.1621159997.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <cover.1621159997.git.mchehab+huawei@kernel.org>
References: <cover.1621159997.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The conversion tools used during DocBook/LaTeX/html/Markdown->ReST
conversion and some cut-and-pasted text contain some characters that
aren't easily reachable on standard keyboards and/or could cause
troubles when parsed by the documentation build system.

Replace the occurences of the following characters:

	- U+00a0 (' '): NO-BREAK SPACE
	  as it can cause lines being truncated on PDF output

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/api.rst | 28 ++++++++++++++--------------
 1 file changed, 14 insertions(+), 14 deletions(-)

```
#### [PATCH RESEND v2 1/2] KVM: selftests: Keep track of memslots more efficiently
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12260515
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A98C8C433B4
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 18:39:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 798CB61185
	for <kvm@archiver.kernel.org>; Sun, 16 May 2021 18:39:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231400AbhEPSkO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 16 May 2021 14:40:14 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:43132 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229490AbhEPSkO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 May 2021 14:40:14 -0400
Received: from MUA
        by vps-vb.mhejs.net with esmtps  (TLS1.2) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1liLf3-0007Sk-Gk; Sun, 16 May 2021 20:38:45 +0200
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Shuah Khan <shuah@kernel.org>,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH RESEND v2 1/2] KVM: selftests: Keep track of memslots more
 efficiently
Date: Sun, 16 May 2021 20:38:38 +0200
Message-Id: 
 <7f739f0bd675ed34ce6fceec16c13deaa789f2fd.1621190044.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
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
Reviewed-by: Andrew Jones <drjones@redhat.com>
---

This is just a resend of this patch without any changes.

 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    | 141 ++++++++++++++----
 .../selftests/kvm/lib/kvm_util_internal.h     |  15 +-
 tools/testing/selftests/kvm/lib/rbtree.c      |   1 +
 4 files changed, 124 insertions(+), 35 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/rbtree.c

```
