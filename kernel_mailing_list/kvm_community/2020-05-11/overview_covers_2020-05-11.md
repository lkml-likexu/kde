

#### [PATCH 0/8] KVM: x86: Interrupt-based mechanism for async_pf 'page
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon May 11 16:47:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11541317
Return-Path: <SRS0=C6NV=6Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46FBB14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 16:48:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25F1C20722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 11 May 2020 16:48:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JY3+JDkj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730635AbgEKQsC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 11 May 2020 12:48:02 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:38860 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730561AbgEKQsB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 May 2020 12:48:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589215680;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=iI35m1Q2pEPIu1XMN3gYwH8xjnbhhmQn5yUKJEAaaGY=;
        b=JY3+JDkjEKFVO559Ashqc5JtPf/22qBd4ISadbMG0zIpwwkej9iQr8CsGY/oDKivPlERUn
        wewgUJqG2C03MggNmMN0KT1lO6YNF7FV2cR+ADhW5lYmNQ8/AF6MY1qXJqBovHaNC7Kn74
        RvpxoGst0WNNVXlM3dFCqEYV5TP9ghk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-55-Dnascdt-PiKmtD8rXmkjvQ-1; Mon, 11 May 2020 12:47:58 -0400
X-MC-Unique: Dnascdt-PiKmtD8rXmkjvQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F338E100CCC1;
        Mon, 11 May 2020 16:47:56 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DDF59196AE;
        Mon, 11 May 2020 16:47:53 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, Gavin Shan <gshan@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/8] KVM: x86: Interrupt-based mechanism for async_pf 'page
 present' notifications
Date: Mon, 11 May 2020 18:47:44 +0200
Message-Id: <20200511164752.2158645-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Concerns were expressed around (ab)using #PF for KVM's async_pf mechanism,
it seems that re-using #PF exception for a PV mechanism wasn't a great
idea after all. The Grand Plan is to switch to using e.g. #VE for 'page
not present' events and normal APIC interrupts for 'page ready' events.
This series does the later.

Changes since RFC:
- Using #PF for 'page ready' is deprecated and removed [Paolo Bonzini]
- 'reason' field in 'struct kvm_vcpu_pv_apf_data' is not used for 'page ready'
  notifications and 'pageready_token' is not used for 'page not present' events
  [Paolo Bonzini]
- Renamed MSR_KVM_ASYNC_PF2 -> MSR_KVM_ASYNC_PF_INT [Peter Xu]
- Drop 'enabled' field from MSR_KVM_ASYNC_PF_INT [Peter Xu]
- Other minor changes supporting the above.

Vitaly Kuznetsov (8):
  Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and
    "Page Ready" exceptions simultaneously"
  KVM: x86: extend struct kvm_vcpu_pv_apf_data with token info
  KVM: introduce kvm_read_guest_offset_cached()
  KVM: x86: interrupt based APF page-ready event delivery
  KVM: x86: acknowledgment mechanism for async pf page ready
    notifications
  KVM: x86: announce KVM_FEATURE_ASYNC_PF_INT
  KVM: x86: Switch KVM guest to using interrupts for page ready APF
    delivery
  KVM: x86: drop KVM_PV_REASON_PAGE_READY case from
    kvm_handle_page_fault()

 Documentation/virt/kvm/cpuid.rst     |   6 ++
 Documentation/virt/kvm/msr.rst       | 106 ++++++++++++++------
 arch/s390/include/asm/kvm_host.h     |   2 +
 arch/x86/entry/entry_32.S            |   5 +
 arch/x86/entry/entry_64.S            |   5 +
 arch/x86/include/asm/hardirq.h       |   3 +
 arch/x86/include/asm/irq_vectors.h   |   6 +-
 arch/x86/include/asm/kvm_host.h      |   7 +-
 arch/x86/include/asm/kvm_para.h      |   6 ++
 arch/x86/include/uapi/asm/kvm_para.h |  11 ++-
 arch/x86/kernel/irq.c                |   9 ++
 arch/x86/kernel/kvm.c                |  42 ++++++--
 arch/x86/kvm/cpuid.c                 |   3 +-
 arch/x86/kvm/mmu/mmu.c               |  10 +-
 arch/x86/kvm/x86.c                   | 142 ++++++++++++++++++---------
 include/linux/kvm_host.h             |   3 +
 include/uapi/linux/kvm.h             |   1 +
 virt/kvm/async_pf.c                  |  10 ++
 virt/kvm/kvm_main.c                  |  19 +++-
 19 files changed, 295 insertions(+), 101 deletions(-)
```
