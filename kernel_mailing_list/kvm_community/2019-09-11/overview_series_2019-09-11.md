#### [PATCH 12/16] x86/kvm: Add Hygon Dhyana support to KVM
##### From: Jinke Fan <fanjinke@hygon.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jinke Fan <fanjinke@hygon.cn>
X-Patchwork-Id: 11140551
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC8FA1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 07:51:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B493E20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 07:51:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726842AbfIKHvX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 03:51:23 -0400
Received: from [110.188.70.11] ([110.188.70.11]:20877 "EHLO spam1.hygon.cn"
        rhost-flags-FAIL-FAIL-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725616AbfIKHvX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 03:51:23 -0400
Received: from MK-DB.hygon.cn ([172.23.18.60])
        by spam1.hygon.cn with ESMTP id x8B7mu9d087318;
        Wed, 11 Sep 2019 15:48:56 +0800 (GMT-8)
        (envelope-from fanjinke@hygon.cn)
Received: from cncheex01.Hygon.cn ([172.23.18.10])
        by MK-DB.hygon.cn with ESMTP id x8B7mid8071103;
        Wed, 11 Sep 2019 15:48:44 +0800 (GMT-8)
        (envelope-from fanjinke@hygon.cn)
Received: from bogon.hygon.cn (172.23.18.44) by cncheex01.Hygon.cn
 (172.23.18.10) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256) id 15.1.1466.3; Wed, 11 Sep
 2019 15:48:46 +0800
From: Jinke Fan <fanjinke@hygon.cn>
To: <fanjinke@hygon.cn>
CC: Pu Wen <puwen@hygon.cn>, Borislav Petkov <bp@suse.de>,
        <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <tglx@linutronix.de>,
        <mingo@redhat.com>, <hpa@zytor.com>, <x86@kernel.org>,
        <thomas.lendacky@amd.com>, <kvm@vger.kernel.org>
Subject: [PATCH 12/16] x86/kvm: Add Hygon Dhyana support to KVM
Date: Wed, 11 Sep 2019 15:48:39 +0800
Message-ID: <20190911074839.69650-1-fanjinke@hygon.cn>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [172.23.18.44]
X-ClientProxiedBy: cncheex02.Hygon.cn (172.23.18.12) To cncheex01.Hygon.cn
 (172.23.18.10)
X-MAIL: spam1.hygon.cn x8B7mu9d087318
X-DNSRBL: 
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pu Wen <puwen@hygon.cn>

The Hygon Dhyana CPU has the SVM feature as AMD family 17h does.
So enable the KVM infrastructure support to it.

Signed-off-by: Pu Wen <puwen@hygon.cn>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Borislav Petkov <bp@suse.de>
Cc: pbonzini@redhat.com
Cc: rkrcmar@redhat.com
Cc: tglx@linutronix.de
Cc: mingo@redhat.com
Cc: hpa@zytor.com
Cc: x86@kernel.org
Cc: thomas.lendacky@amd.com
Cc: kvm@vger.kernel.org
Link: https://lkml.kernel.org/r/654dd12876149fba9561698eaf9fc15d030301f8.1537533369.git.puwen@hygon.cn
---
 arch/x86/include/asm/kvm_emulate.h |  4 ++++
 arch/x86/include/asm/virtext.h     |  5 +++--
 arch/x86/kvm/emulate.c             | 11 ++++++++++-
 3 files changed, 17 insertions(+), 3 deletions(-)

```
#### [PATCH 01/13] KVM: Reinstall old memslots if arch preparation fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11141789
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FC20112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 18:51:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4824D2075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 18:51:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730228AbfIKSum (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 14:50:42 -0400
Received: from mga06.intel.com ([134.134.136.31]:39421 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729758AbfIKSul (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 14:50:41 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Sep 2019 11:50:40 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,492,1559545200";
   d="scan'208";a="196980864"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga002.jf.intel.com with ESMTP; 11 Sep 2019 11:50:40 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: James Hogan <jhogan@kernel.org>, Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Marc Zyngier <marc.zyngier@arm.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Suzuki K Pouloze <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH 01/13] KVM: Reinstall old memslots if arch preparation fails
Date: Wed, 11 Sep 2019 11:50:26 -0700
Message-Id: <20190911185038.24341-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190911185038.24341-1-sean.j.christopherson@intel.com>
References: <20190911185038.24341-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reinstall the old memslots if preparing the new memory region fails
after invalidating a to-be-{re}moved memslot.

Remove the superfluous 'old_memslots' variable so that it's somewhat
clear that the error handling path needs to free the unused memslots,
not simply the 'old' memslots.

Fixes: bc6678a33d9b9 ("KVM: introduce kvm->srcu and convert kvm_set_memory_region to SRCU update")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 virt/kvm/kvm_main.c | 23 ++++++++++++-----------
 1 file changed, 12 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: setjmp: check expected value of "i" to give better feedback
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11140205
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E29D112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 02:32:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 084DB2171F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 02:32:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="G4ee354G"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726680AbfIKCcV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 22:32:21 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:44805 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726548AbfIKCcV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 22:32:21 -0400
Received: by mail-pf1-f201.google.com with SMTP id b204so14558209pfb.11
        for <kvm@vger.kernel.org>; Tue, 10 Sep 2019 19:32:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=VYuTDX4Ncc3pgau4EG/2ob1LMzFBgqPRY3cI9SdDu4s=;
        b=G4ee354GvO9uEp4Yi3nXy4FRn5J6wGdN/ZjQIQ5hYkvGgYZVjdCGYAerkfeNvrjueV
         rOQskLynifLjQf+uEnDi+WEJaU1ECqIMlrFDYZCP0HMxfvkHmVS84dOguDvkRCSKFB2V
         gkT5UkjND3QCo7J5HDN6BG9VLyAHVBrAJUbU3GPdXzifFFpcn7I/DNT9/h318g4W7Pb6
         0sfEM/JoJKIaSvDxxh0prXVA1iYUFb87K+q/OY4aENO6w57Dua8hczokasV3MsjkSdvt
         BPGBvrhR+yKlcyFSNOqw04yetppIq7xP3bHEf5DUt7Rw4Kvr9zd/DW8cDuZi+PqV/dW2
         Ks+A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=VYuTDX4Ncc3pgau4EG/2ob1LMzFBgqPRY3cI9SdDu4s=;
        b=MHu+m19Yt1XcP7VLAg67lgQsprtMIja6i76tYtAjDnOaQS6wBaX1/y5m4DjVwoSt+U
         2XW0gmKdozx0qpRgv4hq+DTPLeu1wFiaXMxP3N8sTyotl0kZ9Q2UELh1e9nv9pUVMbnv
         wIaH2MQxxR4hPN04x0QHxsI+ne7f2nCeAp0KLJTAjhWwaE2vjx3QZEeZgCI9g7mV0XsZ
         foikV3PSYGGU8z8SxItkDtuSs7ybVHkW70enp0V5gStQ6ZSZFmpQW5X3mggc3GzRsOWM
         hr4XuqMD7GIJcKRU14UzzzOPVQ6CDaJE01bVRugns/nd3J7Qtzk+qiI/T1o/85v72UyT
         +PxQ==
X-Gm-Message-State: APjAAAXZd4FAyEGjysgIDG6FD2h3wpArqi7t7g4ch/G6QM4MG8IUTgsE
        G4vxWxI85XTr6l8kMtxMAlWXnKYpW6xEprHTlV2dca5BasxQXwsIaSWi4WolF97h+GyEymeOXM8
        X2u6dxjXVF8DvGP5qtuLHxM9192xDN6/M8fgdsz4e6X7mPSjT44xDpg==
X-Google-Smtp-Source: 
 APXvYqyIh3X/BP1Giz6hj0H9bf8gg6qdwQ3zEZieZDh40WB7d6H+0ZHCmDxLvJ84l06lnZ6voLXdVUNrBg==
X-Received: by 2002:a63:3006:: with SMTP id w6mr31055891pgw.440.1568169139836;
 Tue, 10 Sep 2019 19:32:19 -0700 (PDT)
Date: Tue, 10 Sep 2019 19:31:42 -0700
Message-Id: <20190911023142.85970-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.162.g0b9fbb3734-goog
Subject: [kvm-unit-tests PATCH] x86: setjmp: check expected value of "i" to
 give better feedback
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use a list of expected values instead of printing out numbers, which
aren't very meaningful. This prints only if the expected and actual
values differ.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/setjmp.c | 19 +++++++++++++++----
 1 file changed, 15 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Manually flush collapsible SPTEs only when toggling flags
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11141831
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 292F014ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 19:19:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 107AF20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 19:19:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728623AbfIKTTy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 15:19:54 -0400
Received: from mga18.intel.com ([134.134.136.126]:16558 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728287AbfIKTTy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 15:19:54 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Sep 2019 12:19:53 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,492,1559545200";
   d="scan'208";a="187274874"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga003.jf.intel.com with ESMTP; 11 Sep 2019 12:19:53 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Manually flush collapsible SPTEs only when toggling
 flags
Date: Wed, 11 Sep 2019 12:19:52 -0700
Message-Id: <20190911191952.31126-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Zapping collapsible sptes, a.k.a. 4k sptes that can be promoted into a
large page, is only necessary when changing only the dirty logging flag
of a memory region.  If the memslot is also being moved, then all sptes
for the memslot are zapped when it is invalidated.  When a memslot is
being created, it is impossible for there to be existing dirty mappings,
e.g. KVM can have MMIO sptes, but not present, and thus dirty, sptes.

Note, the comment and logic are shamelessly borrowed from MIPS's version
of kvm_arch_commit_memory_region().

Fixes: 3ea3b7fa9af06 ("kvm: mmu: lazy collapse small sptes into large sptes")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: s390: kvm_s390_vm_start_migration: check dirty_bitmap before using it as target for memset()
##### From: Igor Mammedov <imammedo@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Igor Mammedov <imammedo@redhat.com>
X-Patchwork-Id: 11140557
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 422571395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 07:52:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2AA44222BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 07:52:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727236AbfIKHw2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 03:52:28 -0400
Received: from mx1.redhat.com ([209.132.183.28]:40046 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727208AbfIKHw2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 03:52:28 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id B4E55316E536;
        Wed, 11 Sep 2019 07:52:27 +0000 (UTC)
Received: from dell-r430-03.lab.eng.brq.redhat.com
 (dell-r430-03.lab.eng.brq.redhat.com [10.37.153.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2AD0B6012A;
        Wed, 11 Sep 2019 07:52:23 +0000 (UTC)
From: Igor Mammedov <imammedo@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, david@redhat.com, cohuck@redhat.com,
        frankja@linux.ibm.com, heiko.carstens@de.ibm.com,
        gor@linux.ibm.com, imbrenda@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH v2] KVM: s390: kvm_s390_vm_start_migration: check dirty_bitmap
 before using it as target for memset()
Date: Wed, 11 Sep 2019 03:52:18 -0400
Message-Id: <20190911075218.29153-1-imammedo@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.41]);
 Wed, 11 Sep 2019 07:52:27 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If userspace doesn't set KVM_MEM_LOG_DIRTY_PAGES on memslot before calling
kvm_s390_vm_start_migration(), kernel will oops with:

  Unable to handle kernel pointer dereference in virtual kernel address space
  Failing address: 0000000000000000 TEID: 0000000000000483
  Fault in home space mode while using kernel ASCE.
  AS:0000000002a2000b R2:00000001bff8c00b R3:00000001bff88007 S:00000001bff91000 P:000000000000003d
  Oops: 0004 ilc:2 [#1] SMP
  ...
  Call Trace:
  ([<001fffff804ec552>] kvm_s390_vm_set_attr+0x347a/0x3828 [kvm])
   [<001fffff804ecfc0>] kvm_arch_vm_ioctl+0x6c0/0x1998 [kvm]
   [<001fffff804b67e4>] kvm_vm_ioctl+0x51c/0x11a8 [kvm]
   [<00000000008ba572>] do_vfs_ioctl+0x1d2/0xe58
   [<00000000008bb284>] ksys_ioctl+0x8c/0xb8
   [<00000000008bb2e2>] sys_ioctl+0x32/0x40
   [<000000000175552c>] system_call+0x2b8/0x2d8
  INFO: lockdep is turned off.
  Last Breaking-Event-Address:
   [<0000000000dbaf60>] __memset+0xc/0xa0

due to ms->dirty_bitmap being NULL, which might crash the host.

Make sure that ms->dirty_bitmap is set before using it or
return -ENIVAL otherwise.

Fixes: afdad61615cc ("KVM: s390: Fix storage attributes migration with memory slots")
Signed-off-by: Igor Mammedov <imammedo@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
Cc: stable@vger.kernel.org # v4.19+

v2:
   - remove not true anym 'warning' clause in commit message
v2:
   - drop WARN()

 arch/s390/kvm/kvm-s390.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v2] vhost: block speculation of translated descriptors
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11141037
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4417D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 12:10:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B28120CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 12:10:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727899AbfIKMKG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 08:10:06 -0400
Received: from mx1.redhat.com ([209.132.183.28]:32912 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727696AbfIKMKG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 08:10:06 -0400
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 5B3C177324
        for <kvm@vger.kernel.org>; Wed, 11 Sep 2019 12:10:06 +0000 (UTC)
Received: by mail-qt1-f198.google.com with SMTP id l22so23513864qtq.5
        for <kvm@vger.kernel.org>; Wed, 11 Sep 2019 05:10:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=nO3SYHGDRWEzxT3/abFXM0Gu89GIuWvlxuxu/SDZ8iw=;
        b=ayASTC75Su7u6tLw1LiqfIgkJ+sf7VtlKFpGPj2cL/7twnOxs2CKkpKx1qWbdeDlkX
         PF/GBPoBVpPgcJsOpbyUtbAUsbBFRc53k/0nycSrVJpHkpYPDCVzqFgUvoLhNR/BQnob
         Gp4KtUoDedJUpesKRbirp3P1IM6Y0wlVUTw/HwPrEgqJw2F3SRhDOlK++s4HwpdXzhD8
         nN9FRBeMqO8ZLUUUbCvyK1ZW3fCbRs/V3GbR4SucPlDvLA9xNV9/W46vIL4wYsnmshC3
         p212Kip1Zixr6Qdfm9r4srm0hYMOUybn6EKYHzGwPDcwZ97lcEfi4IoJ0qlafMqF65mi
         vSGw==
X-Gm-Message-State: APjAAAWHyoOiJLYaacOEkpWXm5nWt4jFT7xoEZ578fG53FyPcziv+SH+
        98HBV0vLUJEFjeYGIprf8vMKK4V1NBPmWYE4dmNxynFCESZ9DeoZqP6QZyAfNus3RKGR759RhqP
        ghzG2wcjqCr/J
X-Received: by 2002:ad4:5494:: with SMTP id q20mr21893381qvy.8.1568203805669;
        Wed, 11 Sep 2019 05:10:05 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqxpfN8qjonuIyL61v7mAfTW2LcQ+Fqop0jhY4LwumZnvN9ZVZG/z8lBS94ag/ZEibKr7bFsQA==
X-Received: by 2002:ad4:5494:: with SMTP id q20mr21893369qvy.8.1568203805473;
        Wed, 11 Sep 2019 05:10:05 -0700 (PDT)
Received: from redhat.com ([80.74.107.118])
        by smtp.gmail.com with ESMTPSA id
 h29sm12975276qtb.46.2019.09.11.05.10.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 11 Sep 2019 05:10:04 -0700 (PDT)
Date: Wed, 11 Sep 2019 08:10:00 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v2] vhost: block speculation of translated descriptors
Message-ID: <20190911120908.28410-1-mst@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

iovec addresses coming from vhost are assumed to be
pre-validated, but in fact can be speculated to a value
out of range.

Userspace address are later validated with array_index_nospec so we can
be sure kernel info does not leak through these addresses, but vhost
must also not leak userspace info outside the allowed memory table to
guests.

Following the defence in depth principle, make sure
the address is not validated out of node range.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Tested-by: Jason Wang <jasowang@redhat.com>
---

changes from v1: fix build on 32 bit

 drivers/vhost/vhost.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost: make sure log_num < in_num
##### From: ">" <duanery.duan@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: ">" <duanery.duan@gmail.com>
X-Patchwork-Id: 11140779
Return-Path: <SRS0=z48u=XG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4440912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 09:45:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81BED2067B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Sep 2019 09:45:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="eNFrYSBT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727307AbfIKJpO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Sep 2019 05:45:14 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:33806 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726657AbfIKJpN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Sep 2019 05:45:13 -0400
Received: by mail-pg1-f196.google.com with SMTP id n9so11272228pgc.1;
        Wed, 11 Sep 2019 02:45:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=xohSRI3/IN3LcNp/shyymPBhjiQ0ndNIrEZv77qi1n8=;
        b=eNFrYSBTzqFYv6+obW49UrPBUKl9KYM0Rdo2ufzGT7FnHxVylhb0D+BvmoELZdjrif
         jh08AbIoPqz+O0YbqIVuK4JjIlS0h72or+DMIicDzRslV8q3aaM91zdtFlz4MSoLA+4p
         LK9+lPOwgKA/FkZhEhjXMTcsBMQEJSQJK+eO2Zxq64FYec+KgdDkUh005o4f4vRM2BAZ
         wU7xsSkMLH0HEp1Lng201XZ9Ty1KN3sWXpmAPUyb/sp7nU6UMiLqd1irw9Kp5MUTmL1R
         Nou+WTCCysSsKDQhbOvQgeLb581nZaYAm+eHMK2zvPl61DFZQ8ygJB32ISzxreCNuQWJ
         BNpg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=xohSRI3/IN3LcNp/shyymPBhjiQ0ndNIrEZv77qi1n8=;
        b=D9IGC0FRB4D7PydYQg3YMUNzIQ1CHaEoBDrngch67Jg2jDbo0SF0TDozFib5F5nzpH
         evBcZixpI0Yv3XsjhzI++ehv3JTyNuojV3jSqBdL1Yl6Qp+K5QsE4QM4Bo3nnUH9+/w6
         iEpHrvAX5K4tfaBmFY/YqQBtd2EPoPQl3f8Mn17UKeM/xV/L8TJGdadbzUW9GHQijawv
         Db43ATuvhFyCeKsl7Ltkr6qeSjYv53031UqICnwdxoz/Sz5GhiNp9OK7eI50x5rmBg4w
         GgeLsMVGeDMXCv4VevHL7gyiJzxWuclzBTL1j7GZ7daac7ffNuhbeWtieyk2Td2jQfL1
         SpFw==
X-Gm-Message-State: APjAAAXryAXQHS4c0D37HTxZ7cpheRi9tNkoaOm8Yf9YG1XLpBU2Noqt
        iJxAWKQur2BTml1U6Q81sqs=
X-Google-Smtp-Source: 
 APXvYqzGG3hxVk92CVHl/gupHPvrti067E/3fRB1vNM3dLv8dfmiJoRkfg1nqwCDmIS3eHu8cM88EQ==
X-Received: by 2002:aa7:9303:: with SMTP id 3mr42022142pfj.29.1568195112978;
        Wed, 11 Sep 2019 02:45:12 -0700 (PDT)
Received: from VM_67_169_centos.localdomain ([129.226.133.242])
        by smtp.gmail.com with ESMTPSA id
 m13sm20987739pgn.57.2019.09.11.02.45.11
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 11 Sep 2019 02:45:12 -0700 (PDT)
From: ">" <duanery.duan@gmail.com>
X-Google-Original-From: yongduan@tencent.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        lidongchen@tencent.com, yongduan <yongduan@tencent.com>,
        ruippan <ruippan@tencent.com>
Subject: [PATCH] vhost: make sure log_num < in_num
Date: Wed, 11 Sep 2019 17:44:24 +0800
Message-Id: <1568195064-18037-1-git-send-email-yongduan@tencent.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: yongduan <yongduan@tencent.com>

The code assumes log_num < in_num everywhere, and that is true as long as
in_num is incremented by descriptor iov count, and log_num by 1. However
this breaks if there's a zero sized descriptor.

As a result, if a malicious guest creates a vring desc with desc.len = 0,
it may cause the host kernel to crash by overflowing the log array. This
bug can be triggered during the VM migration.

There's no need to log when desc.len = 0, so just don't increment log_num
in this case.

Fixes: 3a4d5c94e959 ("vhost_net: a kernel-level virtio server")
Reviewed-by: Lidong Chen <lidongchen@tencent.com>
Signed-off-by: ruippan <ruippan@tencent.com>
Signed-off-by: yongduan <yongduan@tencent.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Reviewed-by: Tyler Hicks <tyhicks@canonical.com>
---
 drivers/vhost/vhost.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
