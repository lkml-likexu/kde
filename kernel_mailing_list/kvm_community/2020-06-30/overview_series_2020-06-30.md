#### [PATCH] KVM: x86: bit 8 of non-leaf PDPEs is not reserved
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11633771
Return-Path: <SRS0=5uRT=AL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35FA414B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 11:10:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C15720771
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 11:10:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HytoAQ3l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732880AbgF3LKM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 30 Jun 2020 07:10:12 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:41545 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732874AbgF3LKK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Jun 2020 07:10:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593515409;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=msnFaJYZDu81wFuqZFTp1ZOR5QC4oyv6dPxquziRN8w=;
        b=HytoAQ3l5t4/mzUdrDO+1cm6r5p4j9FTs+iOJXMGAtfWT7bvzmhuGh8N5rxbmjSU3jE+mT
        qO1fuvk8/H7yjzVvex5h6Jkk1rLPAzpm02tar+MXSeaVXG/D5AoS7AxJKZxBqMYCxn0RZg
        SQAeR0W0uvLd9C9tVh9/WaOVioOUIDI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-378-VBh_BiGdOGuDy8VESVo1Dw-1; Tue, 30 Jun 2020 07:10:07 -0400
X-MC-Unique: VBh_BiGdOGuDy8VESVo1Dw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9B4C28015F4;
        Tue, 30 Jun 2020 11:10:06 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 171861001901;
        Tue, 30 Jun 2020 11:10:06 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org, Nadav Amit <namit@vmware.com>
Subject: [PATCH] KVM: x86: bit 8 of non-leaf PDPEs is not reserved
Date: Tue, 30 Jun 2020 07:10:05 -0400
Message-Id: <20200630111005.457029-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bit 8 would be the "global" bit, which does not quite make sense for non-leaf
page table entries.  Intel ignores it; AMD ignores it in PDEs and PDPEs, but
reserves it in PML4Es.

Probably, earlier versions of the AMD manual documented it as reserved in PDPEs
as well, and that behavior made it into KVM as well as kvm-unit-tests; fix it.

Cc: stable@vger.kernel.org
Reported-by: Nadav Amit <namit@vmware.com>
Fixes: a0c0feb57992 ("KVM: x86: reserve bit 8 of non-leaf PDPEs and PML4Es in 64-bit mode on AMD", 2014-09-03)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: drop erroneous mmu_check_root() from fast_pgd_switch()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11633611
Return-Path: <SRS0=5uRT=AL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2F5C6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 10:07:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD5C820780
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 10:07:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bhT2YLra"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732238AbgF3KHw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 30 Jun 2020 06:07:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:44045 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732220AbgF3KHu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Jun 2020 06:07:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593511669;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6bMazijEUH/Uu9sCncXdhJdICYXtEKD+O6jGCzyyAiQ=;
        b=bhT2YLra5NIwDrpiAkcClmLb9KhAEpcFbmJ4+jcRp314xMskjj9Ks4NGrBvxxsPwBDy0L+
        0EGwbLzMsnXl/cfJDX0utUPEiV4ZzW9Di/VMze9Akc2nlIPLqox3xKucOVJbxBuZJtBTWv
        w1HBY6Q2W2+C7Q1TfH3R33616p25fNY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-483-hLxQllp4PQGI9P72rIm5Eg-1; Tue, 30 Jun 2020 06:07:47 -0400
X-MC-Unique: hLxQllp4PQGI9P72rIm5Eg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 36AF21883629;
        Tue, 30 Jun 2020 10:07:46 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.43])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6B4EC74193;
        Tue, 30 Jun 2020 10:07:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: drop erroneous mmu_check_root() from
 fast_pgd_switch()
Date: Tue, 30 Jun 2020 12:07:42 +0200
Message-Id: <20200630100742.1167961-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Undesired triple fault gets injected to L1 guest on SVM when L2 is
launched with certain CR3 values. It seems the mmu_check_root()
check in fast_pgd_switch() is wrong: first of all we don't know
if 'new_pgd' is a GPA or a nested GPA and, in case it is a nested
GPA, we can't check it with kvm_is_visible_gfn().

The problematic code path is:
nested_svm_vmrun()
  ...
  nested_prepare_vmcb_save()
    kvm_set_cr3(..., nested_vmcb->save.cr3)
      kvm_mmu_new_pgd()
        ...
        mmu_check_root() -> TRIPLE FAULT

The mmu_check_root() check in fast_pgd_switch() seems to be
superfluous even for non-nested case: when GPA is outside of the
visible range cached_root_available() will fail for non-direct
roots (as we can't have a matching one on the list) and we don't
seem to care for direct ones.

Also, raising #TF immediately when a non-existent GFN is written to CR3
doesn't seem to mach architecture behavior.

Fixes: 7c390d350f8b ("kvm: x86: Add fast CR3 switch code path")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- The patch fixes the immediate issue and doesn't seem to break any
  tests even with shadow PT but I'm not sure I properly understood
  why the check was there in the first place. Please review!
---
 arch/x86/kvm/mmu/mmu.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/5] x86: Remove boot_idt assembly assignment
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11633587
Return-Path: <SRS0=5uRT=AL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E679618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 09:48:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E9B32077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 30 Jun 2020 09:48:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732126AbgF3Js1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 30 Jun 2020 05:48:27 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:21770 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732110AbgF3JsV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Jun 2020 05:48:21 -0400
Received: from sc9-mailhost2.vmware.com (10.113.161.72) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Tue, 30 Jun 2020 02:48:19 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost2.vmware.com (Postfix) with ESMTP id 0A3C1B27D6;
        Tue, 30 Jun 2020 05:48:20 -0400 (EDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 1/5] x86: Remove boot_idt assembly assignment
Date: Tue, 30 Jun 2020 02:45:12 -0700
Message-ID: <20200630094516.22983-2-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200630094516.22983-1-namit@vmware.com>
References: <20200630094516.22983-1-namit@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

boot_idt is now a symbol.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/cstart64.S | 3 ---
 1 file changed, 3 deletions(-)

```
