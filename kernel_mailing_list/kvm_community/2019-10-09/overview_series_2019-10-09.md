#### [PATCH v2] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11180177
Return-Path: <SRS0=YPTB=YC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B7F317D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Oct 2019 00:04:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 67A8221871
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Oct 2019 00:04:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Ov5hRXOp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729922AbfJIAD7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 20:03:59 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:45011 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727051AbfJIAD7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 20:03:59 -0400
Received: by mail-pf1-f201.google.com with SMTP id b204so448991pfb.11
        for <kvm@vger.kernel.org>; Tue, 08 Oct 2019 17:03:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=DBDb8BfaknlNbargZmd/ZeQvvg2C+ScBJir7YYzrA3A=;
        b=Ov5hRXOp8JezlYy2XfVC13k85lvlRmOvrkPRZx5+aN9h4UMwPwcilkS9MrOzKLTpjR
         DHwTKrDZLVTtsoDo+pMukDIJwZcJ8Rh7dCFDNdYMt0CvRnaToVvomK1JhDKi62ti6OmP
         D8hMskJoawY4Bt1oMOuelkjHDqhNB/0BgU6hZYjnsmiF+dazIm10ZHQ9gBGJ4C9WW8dl
         n8Bp4swvrJOX8IntZTVYrj62ObLnqdq6EgQSlNB9vasTWAztyukxFeZYCirCFOUGgcdr
         fn50scQVi5IcA2WE/Eeg1ZpnVW2DsBErXRO81LyTLlMf/1lTtR9BA7JIfkTTLUJ5oXt8
         Z16A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=DBDb8BfaknlNbargZmd/ZeQvvg2C+ScBJir7YYzrA3A=;
        b=CA9opw/XfDmod0E1xN+mPgbpt81C+dNF+4eX7Z6/cyCEthWM9b39srB9G4Mm25y0qh
         ibFaiWwe1Cbi9s84FoFFLM2HrSi4DltE0+3H9lQJTKUZGEkOFE/6ncBwFttf9HVz+Bn7
         9PHNhSDyZjLlq2y9D3DP3FaP0Q6jqga4arHBl2Iq2Te8/BGdEaGyhwsQ8AJsP9OuQ2hv
         QN5h1WZq51rxWJR1F/JzK39O+g8Kj8DR3ZXSK7Bv/oHcUVpwRYFh04b1HqWJQCTAZTa7
         B4dHxOTnilT6z+aLEn5OHlbnsKRqRiwW4emIz07xGbyhbqyjHr1/VfPM0uH59Yx4LbQ+
         CL3Q==
X-Gm-Message-State: APjAAAVuyvA/fn9cNcY7WxXy548BodYbpYd1/erE8/USmxpwrJ6l/s9E
        mvyJKUA+d9eTtyj3S6UEa533PkPJVrYiftyZmjimxq2rhCvGVqbt+9Ywmu9GGi3pfxZ511pk/nv
        RjNCa2FvxUob7I/MPozeY4AD7L5mku+gKTcntRAvpVcrPOtOYdCMVwdd4it997uM=
X-Google-Smtp-Source: 
 APXvYqxFeZ1joLfl36DQgk6mr/O1kki+ykH+SEZeS7vZ8iyBWu+mq5a5Wze897RxbtB5xbrfK4c99vgvCLXdmQ==
X-Received: by 2002:a63:e013:: with SMTP id e19mr1246596pgh.274.1570579435580;
 Tue, 08 Oct 2019 17:03:55 -0700 (PDT)
Date: Tue,  8 Oct 2019 17:03:43 -0700
Message-Id: <20191009000343.13495-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.581.g78d2f28ef7-goog
Subject: [PATCH v2] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the "virtualize APIC accesses" VM-execution control is set in the
VMCS, the APIC virtualization hardware is triggered when a page walk
in VMX non-root mode terminates at a PTE wherein the address of the 4k
page frame matches the APIC-access address specified in the VMCS. On
hardware, the APIC-access address may be any valid 4k-aligned physical
address.

KVM's nVMX implementation enforces the additional constraint that the
APIC-access address specified in the vmcs12 must be backed by
cacheable memory in L1. If not, L0 will simply clear the "virtualize
APIC accesses" VM-execution control in the vmcs02.

The problem with this approach is that the L1 guest has arranged the
vmcs12 EPT tables--or shadow page tables, if the "enable EPT"
VM-execution control is clear in the vmcs12--so that the L2 guest
physical address(es)--or L2 guest linear address(es)--that reference
the L2 APIC map to the APIC-access address specified in the
vmcs12. Without the "virtualize APIC accesses" VM-execution control in
the vmcs02, the APIC accesses in the L2 guest will directly access the
APIC-access page in L1.

When there is no mapping whatsoever for the APIC-access address in L1,
the L2 VM just loses the intended APIC virtualization. However, when
the APIC-access address is mapped to an MMIO region in L1, the L2
guest gets direct access to the L1 MMIO device. For example, if the
APIC-access address specified in the vmcs12 is 0xfee00000, then L2
gets direct access to L1's APIC.

Since this vmcs12 configuration is something that KVM cannot
faithfully emulate, the appropriate response is to exit to userspace
with KVM_INTERNAL_ERROR_EMULATION.

Fixes: fe3ef05c7572 ("KVM: nVMX: Prepare vmcs02 from vmcs01 and vmcs12")
Reported-by: Dan Cross <dcross@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 v1 -> v2: Added enum enter_vmx_status
 
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 65 +++++++++++++++++++--------------
 arch/x86/kvm/vmx/nested.h       | 13 ++++++-
 arch/x86/kvm/x86.c              |  8 +++-
 4 files changed, 56 insertions(+), 32 deletions(-)

```
