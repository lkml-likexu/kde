

#### [PATCH 0/5] KVM: nSVM: few fixes for the nested migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon May  3 12:54:41 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12236019
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95821C433B4
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:54:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E235611EE
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 12:54:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233875AbhECMzu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 08:55:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:52276 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230246AbhECMzt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 May 2021 08:55:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620046495;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=1Rw8PEoNDUSMjSr1Op+FeFRDfcIRdOVFZ6tTPEgh5kA=;
        b=c/luLvoSRJ9tfceNU2Ic0lt8rUvCqVXB1+0zuAF8qD/s73xjY+scaBUvG+CEh7goqYclDb
        IRgQSEsHjaNPI4Ri3kbXUq03t5NsBOs+hSryO/UxuYhOllq7kOK0eueJq151gYa8tQo3Af
        aVvFVuq+3aCwfdirYqElslUyGttZyXo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-465-nzEQ7-B_NrCWNWi_DZLH4A-1; Mon, 03 May 2021 08:54:54 -0400
X-MC-Unique: nzEQ7-B_NrCWNWi_DZLH4A-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5802E1922962;
        Mon,  3 May 2021 12:54:52 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.193.27])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A79E610DF;
        Mon,  3 May 2021 12:54:47 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <joro@8bytes.org>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Sean Christopherson <seanjc@google.com>,
        Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/5] KVM: nSVM: few fixes for the nested migration
Date: Mon,  3 May 2021 15:54:41 +0300
Message-Id: <20210503125446.1353307-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Those are few fixes for issues I uncovered by doing variants of a
synthetic migration test I just created:

I modified the qemu, such that on each vm pause/resume cycle,
just prior to resuming a vCPU, qemu reads its KVM state,
then (optionaly) resets this state by uploading a
dummy reset state to KVM, and then it uploads back to KVM,
the state that this vCPU had before.

I'll try to make this test upstreamable soon, pending few details
I need to figure out.

Last patch in this series is for false positive warning
that I have seen lately when setting the nested state,
in nested_svm_vmexit, where it expects the vmcb01 to have
VMRUN vmexit, which is not true after nested migration,
as it is not fully initialized.
If you prefer the warning can be removed instead.

Best regards,
	Maxim Levitsky

Maxim Levitsky (5):
  KVM: nSVM: fix a typo in svm_leave_nested
  KVM: nSVM: fix few bugs in the vmcb02 caching logic
  KVM: nSVM: leave the guest mode prior to loading a nested state
  KVM: nSVM: force L1's GIF to 1 when setting the nested state
  KVM: nSVM: set a dummy exit reason in L1 vmcb when loading the nested
    state

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm/nested.c       | 29 ++++++++++++++++++++++++++---
 arch/x86/kvm/svm/svm.c          |  4 ++--
 3 files changed, 29 insertions(+), 5 deletions(-)
```
#### [PATCH 0/4] KVM: nVMX: Fix migration of nested guests when eVMCS is
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon May  3 15:08:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12236195
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6138C433ED
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 15:09:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6BE7F61166
	for <kvm@archiver.kernel.org>; Mon,  3 May 2021 15:09:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229964AbhECPJz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 3 May 2021 11:09:55 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43646 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229852AbhECPJy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 May 2021 11:09:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620054541;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3NSTvLyUxmHOiVo7fotK2BXG7bF8hMwAK4lLfzcPP+k=;
        b=d7H2rc5Gs0V1wR/LrH8zHK1J9FDP0j1cJ/JZ5Qm//NwO48SjOU29xIzYALQcbEDfos3M1B
        oos+v20LwMT0i173t3TrQEEpHV6DQ6ppU8OJTUBFFtLeFhtntO2A7LUVihrILVVx8WVl3Y
        cp5CNASh1R77SRgpT2ewtS+QvRfrLMU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-575-ynpy81ogPmqaVuiVqqWbYQ-1; Mon, 03 May 2021 11:08:59 -0400
X-MC-Unique: ynpy81ogPmqaVuiVqqWbYQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06994107ACC7;
        Mon,  3 May 2021 15:08:58 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CFDFA19C45;
        Mon,  3 May 2021 15:08:55 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] KVM: nVMX: Fix migration of nested guests when eVMCS is
 in use
Date: Mon,  3 May 2021 17:08:50 +0200
Message-Id: <20210503150854.1144255-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Win10 guests with WSL2 enabled sometimes crash on migration when
enlightened VMCS was used. The condition seems to be induced by the
situation when L2->L1 exit is caused immediately after migration and
before L2 gets a chance to run (e.g. when there's an interrupt pending).
The issue was introduced by commit f2c7ef3ba955 ("KVM: nSVM: cancel 
KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit") and the first patch
of the series addresses the immediate issue. The eVMCS mapping restoration
path, however, seems to be fragile and the rest of the series tries to
make it more future proof by including eVMCS GPA in the migration data.

Vitaly Kuznetsov (4):
  KVM: nVMX: Always make an attempt to map eVMCS after migration
  KVM: nVMX: Properly pad 'struct kvm_vmx_nested_state_hdr'
  KVM: nVMX: Introduce __nested_vmx_handle_enlightened_vmptrld()
  KVM: nVMX: Map enlightened VMCS upon restore when possible

 arch/x86/include/uapi/asm/kvm.h |  4 ++
 arch/x86/kvm/vmx/nested.c       | 82 +++++++++++++++++++++++----------
 2 files changed, 61 insertions(+), 25 deletions(-)
```
