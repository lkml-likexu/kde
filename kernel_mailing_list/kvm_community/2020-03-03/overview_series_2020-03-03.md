#### [PATCH RFC 4/4] kvm: Implement atomic memory region resizes via region_resize()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11418179
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9EB8E14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:20:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 699932086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:20:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LOscpQYi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728488AbgCCOUd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 09:20:33 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:26031 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727311AbgCCOUd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Mar 2020 09:20:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583245231;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=fO4uZMYE82gtwCvsu4xnQfm16x7G0X5NKbdPHitYWJ0=;
        b=LOscpQYigMR776H24Ub6ZxTaIiaOep6L/5ISgJRtvOru10QszwpNMF+C5xlLSxwGPNkonI
        Ac86+y6xlAwqqIW/xgzfMWJrf+b6wOgsw7E553996c4dM5y9xxBSXYMvW5u561zBG+ujK4
        7LZPQT1VLUehtD5Ohol68aUAmRqwIB8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-356-VNP-6lTlN_axUtd7OtkI2Q-1; Tue, 03 Mar 2020 09:20:29 -0500
X-MC-Unique: VNP-6lTlN_axUtd7OtkI2Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8DC60107ACCA;
        Tue,  3 Mar 2020 14:20:28 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-117-113.ams2.redhat.com [10.36.117.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8279C60BE1;
        Tue,  3 Mar 2020 14:20:26 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        kvm@vger.kernel.org
Subject: [PATCH RFC 4/4] kvm: Implement atomic memory region resizes via
 region_resize()
Date: Tue,  3 Mar 2020 15:19:39 +0100
Message-Id: <20200303141939.352319-5-david@redhat.com>
In-Reply-To: <20200303141939.352319-1-david@redhat.com>
References: <20200303141939.352319-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

virtio-mem wants to resize (esp. grow) ram memory regions while the guest
is already aware of them and makes use of them. Resizing a KVM slot can
only currently be done by removing it and re-adding it. While the kvm slot
is temporarily removed, VCPUs that try to read from these slots will fault.
But also, other ioctls might depend on all slots being in place.

Let's inhibit most KVM ioctls while performing the resize. Once we have an
ioctl that can perform atomic resizes (e.g., KVM_SET_USER_MEMORY_REGION
extensions), we can make inhibiting optional at runtime.

Also, make sure to hold the kvm_slots_lock while performing both
actions (removing+re-adding).

Note: Resizes of memory regions currently seems to happen during bootup
only, so I don't think any existing RT users should be affected.

Cc: Richard Henderson <rth@twiddle.net>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 accel/kvm/kvm-all.c   | 121 +++++++++++++++++++++++++++++++++++++++---
 include/hw/core/cpu.h |   3 ++
 2 files changed, 117 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: nVMX: Properly handle userspace interrupt window request
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11417269
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AFC7174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 06:27:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BB7421741
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 06:27:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727487AbgCCG1i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 01:27:38 -0500
Received: from mga03.intel.com ([134.134.136.65]:40059 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725765AbgCCG1h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 01:27:37 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Mar 2020 22:27:36 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,510,1574150400";
   d="scan'208";a="274076019"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 02 Mar 2020 22:27:36 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>
Subject: [PATCH] KVM: nVMX: Properly handle userspace interrupt window request
Date: Mon,  2 Mar 2020 22:27:35 -0800
Message-Id: <20200303062735.31868-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Return true for vmx_interrupt_allowed() if the vCPU is in L2 and L1 has
external interrupt exiting enabled.  IRQs are never blocked in hardware
if the CPU is in the guest (L2 from L1's perspective) when IRQs trigger
VM-Exit.

The new check percolates up to kvm_vcpu_ready_for_interrupt_injection()
and thus vcpu_run(), and so KVM will exit to userspace if userspace has
requested an interrupt window (to inject an IRQ into L1).

Remove the @external_intr param from vmx_check_nested_events(), which is
actually an indicator that userspace wants an interrupt window, e.g.
it's named @req_int_win further up the stack.  Injecting a VM-Exit into
L1 to try and bounce out to L0 userspace is all kinds of broken and is
no longer necessary.

Remove the hack in nested_vmx_vmexit() that attempted to workaround the
breakage in vmx_check_nested_events() by only filling interrupt info if
there's an actual interrupt pending.  The hack actually made things
worse because it caused KVM to _never_ fill interrupt info when the
LAPIC resides in userspace (kvm_cpu_has_interrupt() queries
interrupt.injected, which is always cleared by prepare_vmcs12() before
reaching the hack in nested_vmx_vmexit()).

Fixes: 6550c4df7e50 ("KVM: nVMX: Fix interrupt window request with "Acknowledge interrupt on exit"")
Cc: stable@vger.kernel.org
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Odds are good that this doesn't solve all the problems with running nested
VMX and a userspace LAPIC, but I'm at least able to boot a kernel and run
unit tests, i.e. it's less broken than before.  Not that it matters, I'm
guessing no one actually uses this configuration, e.g. running a SMP
guest with the current KVM+kernel hangs during boot because Qemu
advertises PV IPIs to the guest, which require an in-kernel LAPIC.  I
stumbled on this disaster when disabling the in-kernel LAPIC for a
completely unrelated test.  I'm happy even if it does nothing more than
get rid of the awful logic vmx_check_nested_events().

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 18 ++++--------------
 arch/x86/kvm/vmx/vmx.c          |  9 +++++++--
 arch/x86/kvm/x86.c              | 10 +++++-----
 4 files changed, 17 insertions(+), 22 deletions(-)

```
#### [PATCH] kvm: selftests: Support dirty log initial-all-set test
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhoujian (jay)" <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11417345
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B0701395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 08:07:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5438C21741
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 08:07:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727757AbgCCIHX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 03:07:23 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:44314 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727594AbgCCIHX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 03:07:23 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 50C3727143BE5F251882;
        Tue,  3 Mar 2020 16:07:19 +0800 (CST)
Received: from localhost (10.173.228.206) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Tue, 3 Mar 2020
 16:07:13 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <peterx@redhat.com>, <shuah@kernel.org>,
        <linux-kselftest@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <wangxinxin.wang@huawei.com>, <weidong.huang@huawei.com>,
        <liu.jinsong@huawei.com>, <jianjay.zhou@huawei.com>
Subject: [PATCH] kvm: selftests: Support dirty log initial-all-set test
Date: Tue, 3 Mar 2020 16:07:10 +0800
Message-ID: <20200303080710.1672-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.228.206]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the new capability KVM_DIRTY_LOG_INITIALLY_SET of
KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 has been introduced, tweak the
clear_dirty_log_test to test it.

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
---
 tools/testing/selftests/kvm/clear_dirty_log_test.c |  4 ++++
 tools/testing/selftests/kvm/dirty_log_test.c       | 20 +++++++++++++++++---
 2 files changed, 21 insertions(+), 3 deletions(-)

```
#### [PATCH 1/2] KVM: x86: clear stale x86_emulate_ctxt->intercept value
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11418199
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 663BD174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:33:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C3EB20866
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:33:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iun4E6T8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729551AbgCCOd0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 09:33:26 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:24364 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729261AbgCCOd0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Mar 2020 09:33:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583246004;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=89Ze1It+GtPoLXw9gXBuQh65Mg9trWRIkcttx5v04pM=;
        b=iun4E6T8nnWqn7xTU7sn0q8lu3rPvu1Uj7OpU8MBa40gf82X+5IxE7rzGRYy3c237hXRgP
        9zMBhyOjP5Grqei1uv0jSSQlchjtEZ+q4FGBSkkMuXoW/+X+Vh+a7R0Lo/8UkY0tEq3Dou
        YLJRLJkjcPormJUfmY80Hh4gHpEUfhs=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-376-t6SzJZrWPGWaoz4gc-7-_A-1; Tue, 03 Mar 2020 09:33:23 -0500
X-MC-Unique: t6SzJZrWPGWaoz4gc-7-_A-1
Received: by mail-wr1-f69.google.com with SMTP id w18so1310151wro.2
        for <kvm@vger.kernel.org>; Tue, 03 Mar 2020 06:33:23 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=89Ze1It+GtPoLXw9gXBuQh65Mg9trWRIkcttx5v04pM=;
        b=l73r/krDsybk9Zmslo4K69kN+cdni7Odgr/2CKYKLdaWuNVWihy1vIdkjkHXyNihs5
         VY9hCaUPuUdJTCXh5rPRd/QPKORwIxtCRVjkIT4FVoOr3Qc2hOLUHirzXg/qsZUC639j
         ue6Jc4Y916IPdtoRagMvD/mddFrqD01+Ld5CbhU4GVjHt/I/hjj46FYnrtsdi7edZqYv
         jS9cMP8o6XOrtoIrFhyrv4ahYCLw7l72j2X3Bi/PwXeUfCdYt6YWhVJER1G3Cgrxkocy
         T/vFjCLUifULXTMMdTdVoO2X/cxTgrpHYCQIVLEAXiIUUcuaEwmwzHt6gykAelpYvvr+
         P1Ow==
X-Gm-Message-State: ANhLgQ0pMQEnbVhAPTti+GS6vl+cpxJmmyDxTfwHH7MVwgJmbltUuz57
        BpoZouaVLU1Sfqa/QGShV4SzF2NRDB8Fh4aPRTmeUL30bXjbncACLJEU0rSEXES+/TQja1a6VrW
        6MkXVxb75C5dw
X-Received: by 2002:a05:600c:24b:: with SMTP id
 11mr4505868wmj.1.1583246000303;
        Tue, 03 Mar 2020 06:33:20 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vuINeyCMJT4x0cTD7jAV6m0Gk8tTQJGisiIxOqoW5FQMhdO0tVh7STf4uEv41BsxDxn3roLAw==
X-Received: by 2002:a05:600c:24b:: with SMTP id
 11mr4505852wmj.1.1583246000102;
        Tue, 03 Mar 2020 06:33:20 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 s5sm32248504wru.39.2020.03.03.06.33.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Mar 2020 06:33:19 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Bandan Das <bsd@redhat.com>, Oliver Upton <oupton@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: clear stale x86_emulate_ctxt->intercept value
Date: Tue,  3 Mar 2020 15:33:15 +0100
Message-Id: <20200303143316.834912-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200303143316.834912-1-vkuznets@redhat.com>
References: <20200303143316.834912-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c44b4c6ab80e ("KVM: emulate: clean up initializations in
init_decode_cache") reduced the number of fields cleared by
init_decode_cache() claiming that they are being cleared elsewhere,
'intercept', however, seems to be left uncleared in some cases.

The issue I'm observing manifests itself as following:
after commit 07721feee46b ("KVM: nVMX: Don't emulate instructions in guest
mode") Hyper-V guests on KVM stopped booting with:

 kvm_nested_vmexit:    rip fffff802987d6169 reason EPT_VIOLATION info1 181
    info2 0 int_info 0 int_info_err 0
 kvm_page_fault:       address febd0000 error_code 181
 kvm_emulate_insn:     0:fffff802987d6169: f3 a5
 kvm_emulate_insn:     0:fffff802987d6169: f3 a5 FAIL
 kvm_inj_exception:    #UD (0x0)

Fixes: c44b4c6ab80e ("KVM: emulate: clean up initializations in init_decode_cache")
Fixes: 07721feee46b ("KVM: nVMX: Don't emulate instructions in guest mode")
Cc: stable@vger.kernel.org
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/emulate.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3 1/7] KVM: x86/mmu: Don't drop level/direct from MMU role calculation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11417047
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EF75138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 02:02:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57F2A2465E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 02:02:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727174AbgCCCCn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 21:02:43 -0500
Received: from mga05.intel.com ([192.55.52.43]:54060 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727030AbgCCCCm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Mar 2020 21:02:42 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Mar 2020 18:02:41 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,509,1574150400";
   d="scan'208";a="440384933"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga006.fm.intel.com with ESMTP; 02 Mar 2020 18:02:41 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/7] KVM: x86/mmu: Don't drop level/direct from MMU role
 calculation
Date: Mon,  2 Mar 2020 18:02:34 -0800
Message-Id: <20200303020240.28494-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200303020240.28494-1-sean.j.christopherson@intel.com>
References: <20200303020240.28494-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the calculated role as-is when propagating it to kvm_mmu.mmu_role,
i.e. stop masking off meaningful fields.  The concept of masking off
fields came from kvm_mmu_pte_write(), which (correctly) ignores certain
fields when comparing kvm_mmu_page.role against kvm_mmu.mmu_role, e.g.
the current mmu's access and level have no relation to a shadow page's
access and level.

Masking off the level causes problems for 5-level paging, e.g. CR4.LA57
has its own redundant flag in the extended role, and nested EPT would
need a similar hack to support 5-level paging for L2.

Opportunistically rework the mask for kvm_mmu_pte_write() to define the
fields that should be ignored as opposed to the fields that should be
checked, i.e. make it opt-out instead of opt-in so that new fields are
automatically picked up.  While doing so, stop ignoring "direct".  The
field is effectively ignored anyways because kvm_mmu_pte_write() is only
reached with an indirect mmu and the loop only walks indirect shadow
pages, but double checking "direct" literally costs nothing.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 35 ++++++++++++++++++-----------------
 1 file changed, 18 insertions(+), 17 deletions(-)

```
#### [PATCH v3 18/18] docs: kvm: get read of devices/README
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11418143
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A23EA174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:59:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 785EC20863
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:59:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1583243970;
	bh=s0m7dutvhHUxy0GagWG09NA7+534PrANWICiABloyXk=;
	h=From:Cc:Subject:Date:In-Reply-To:References:To:List-ID:From;
	b=2FhM9TlToGuF53La+tOKS0Ur4mbDDihl0lZVRcnzDSrkOsDizzNSxYTzjuJZ41Re9
	 LF3GFqLBI8Pc7xTd/Ua3T4Gx5N+RA/i5ZPSx868Rxs27EGd9LDtSadViLsRTGTiANC
	 c/ui09h45gzvHKppYkb7qLZB+pR1NzK3/IcPJZx0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729337AbgCCN73 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 08:59:29 -0500
Received: from mail.kernel.org ([198.145.29.99]:45346 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728037AbgCCN73 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 08:59:29 -0500
Received: from mail.kernel.org (ip-109-40-2-133.web.vodafone.de
 [109.40.2.133])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CA2692166E;
        Tue,  3 Mar 2020 13:59:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1583243969;
        bh=s0m7dutvhHUxy0GagWG09NA7+534PrANWICiABloyXk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=VHd1+Rd8iKbiniMJBzd3ZSrKtuo3VTCThxt/tGg4YtrBn8kgYQimTjGz6/kyZKI04
         AovqYF4jNVqQyJIz8L6QNA6lPBPbX2IB6xEhMwhBJeGyWGuGvCf90jQKG1cpWF+bOH
         +1h5fL0iOcwtUR60JNM7RD+zJ4h7iN2bp0GF6LCI=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1j9850-001Ye9-MH; Tue, 03 Mar 2020 14:59:26 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Subject: [PATCH v3 18/18] docs: kvm: get read of devices/README
Date: Tue,  3 Mar 2020 14:59:25 +0100
Message-Id: 
 <6e9c4aaf704cdc7b4e517122fb87cbe05f0ffd23.1583243827.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1583243826.git.mchehab+huawei@kernel.org>
References: <cover.1583243826.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
To: unlisted-recipients:; (no To-header on input)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the information there inside devices/index.rst

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/devices/README    | 1 -
 Documentation/virt/kvm/devices/index.rst | 3 +++
 2 files changed, 3 insertions(+), 1 deletion(-)
 delete mode 100644 Documentation/virt/kvm/devices/README

diff --git a/Documentation/virt/kvm/devices/README b/Documentation/virt/kvm/devices/README
```
#### [PATCH v1 1/3] x86/kvm/hyper-v: Add support for synthetic debugger capability
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11417967
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97400921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:04:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62BDF2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:04:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="KutXbXi4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729280AbgCCNEM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 08:04:12 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:32771 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728602AbgCCNEM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 08:04:12 -0500
Received: by mail-wm1-f68.google.com with SMTP id a25so2320292wmm.0
        for <kvm@vger.kernel.org>; Tue, 03 Mar 2020 05:04:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=HBOsRyY7YIPQAQ60tzetiMJFheF1EFDUBhmMusYANqQ=;
        b=KutXbXi4YvACdnLfwoodun4kNtdd9ZroO34qf1xAGHSi7DIiF+XYeVLQ37qKdbaJ2e
         S/mjCyiZCi0a5XTkZf3Za0jlVjv0QT1ls3/1W3azyPARSqiBWQy14sMqAj1fZ7h/rysL
         NNdtLXsGcP6GOS/B+70GEOKxVIlp8KNk5dn/0e7qCP+4zPCweY2e/s/wyscWcSZu7wMW
         ES+LvM2aTz0pghpsoXFHlL7GRgEUVF9vdFbSmCipygZ7BFw8maz+CfHMaRQfqJ3eQLXr
         nKZRkgCqFXMwp0+KBiblbL+K51L2uJHX55SFQ4MIEm4Q/t1R6Gsq/oitHHByGPGGt7PY
         4dLQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=HBOsRyY7YIPQAQ60tzetiMJFheF1EFDUBhmMusYANqQ=;
        b=auh8/xrDcrwR0tnAMOYItI9IbuNIlbZbUee3qHbhNqiMapyYZi6MKMHB0eLl0z/y9F
         L7+l9AuqBbQWjUFFMxUeouliARvnLEtcKSz7KtfAt909NR5TlXNLtabrk4J92DbkSq15
         8F1XrCNDByLh3v9OwO1m93odWVx8RzXVwoLgJ+YiOjuwoRRThs4H/mtie4nm5WPMrSFQ
         v71g3xxCfGTzl9U8na2rxlxs17Pwjqm7QDO20A1rfLd4m0r3HKdpKHlBtDYUAh/oBAI+
         1INPCOi9atI0mzckkHGdIbgirqfsDI2uN/s5YzabtgXcgiNt1ZWxGIQQoPqZ0ooLIem6
         QSuw==
X-Gm-Message-State: ANhLgQ1fY7ot9yNyPi4JXmQGXDxH75vwp9+OpbpJRGdvpZrwfMXzBhJT
        sAsMMVwEYTkgpeXkIV/YJN6QQfG5
X-Google-Smtp-Source: 
 ADFU+vsIevAqEV94/aZ8ye7VwH4K5mWOPQGg2PZcl/rb7v49NAkShLUAcfGnZ1VR7ORl9zB8uAzNEQ==
X-Received: by 2002:a1c:9dcb:: with SMTP id
 g194mr4474924wme.114.1583240648472;
        Tue, 03 Mar 2020 05:04:08 -0800 (PST)
Received: from linux.local ([199.203.162.213])
        by smtp.gmail.com with ESMTPSA id
 w17sm2171951wrm.92.2020.03.03.05.04.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Mar 2020 05:04:08 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 1/3] x86/kvm/hyper-v: Add support for synthetic debugger
 capability
Date: Tue,  3 Mar 2020 15:03:54 +0200
Message-Id: <20200303130356.50405-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200303130356.50405-1-arilou@gmail.com>
References: <20200303130356.50405-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for Hyper-V synthetic debugger (syndbg) interface.
The syndbg interface is using MSRs to emulate a way to send/recv packets
data.

The debug transport dll (kdvm/kdnet) will identify if Hyper-V is enabled
and if it supports the synthetic debugger interface it will attempt to
use it, instead of trying to initialize a network adapter.

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 arch/x86/include/asm/hyperv-tlfs.h |  16 +++++
 arch/x86/include/asm/kvm_host.h    |  11 +++
 arch/x86/kvm/hyperv.c              | 109 +++++++++++++++++++++++++++++
 arch/x86/kvm/hyperv.h              |   5 ++
 arch/x86/kvm/trace.h               |  22 ++++++
 arch/x86/kvm/x86.c                 |   8 +++
 include/uapi/linux/kvm.h           |   9 +++
 7 files changed, 180 insertions(+)

```
