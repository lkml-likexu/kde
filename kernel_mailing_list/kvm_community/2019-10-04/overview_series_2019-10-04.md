#### [kvm-unit-tests PATCH v2 1/6] arm: gic: check_acked: add test description
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11174613
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00BB116B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 14:18:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DCB6C2133F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 14:18:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388968AbfJDOSk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 10:18:40 -0400
Received: from foss.arm.com ([217.140.110.172]:46222 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388625AbfJDOSj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 10:18:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 84CD715AB;
        Fri,  4 Oct 2019 07:18:39 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B88AB3F68E;
        Fri,  4 Oct 2019 07:18:38 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH v2 1/6] arm: gic: check_acked: add test
 description
Date: Fri,  4 Oct 2019 15:18:24 +0100
Message-Id: <20191004141829.87135-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191004141829.87135-1-andre.przywara@arm.com>
References: <20191004141829.87135-1-andre.przywara@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment the check_acked() IRQ helper function just prints a
generic "Completed" or "Timed out" message, without given a more
detailed test description.

To be able to tell the different IRQ tests apart, and also to allow
re-using it more easily, add a "description" parameter string,
which is prefixing the output line. This gives more information on what
exactly was tested.

This also splits the variable output part of the line (duration of IRQ
delivery) into a separate INFO: line, to not confuse testing frameworks.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 arm/gic.c | 17 ++++++++++-------
 1 file changed, 10 insertions(+), 7 deletions(-)

```
#### [GIT PULL] KVM fixes for Linux 5.4-rc2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11174315
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C84316B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 12:04:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1B59D20862
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 12:04:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="gCuTIPxB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730117AbfJDMEA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 08:04:00 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:37449 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725775AbfJDMEA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 08:04:00 -0400
Received: by mail-wm1-f67.google.com with SMTP id f22so5578586wmc.2;
        Fri, 04 Oct 2019 05:03:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=KVrTSfhJQkcjGUoc6/wChtJatdSgDTO1rfWfls9h3Lo=;
        b=gCuTIPxBpH1goz7Jtyo4AdIW3vOQiGnlAioh/38P0AiDodj95Ep7QBms8Ew3szTn6H
         z3ZyAMgJGNRgKN/pBecNOh/f/7/QpdK1uwz8VnFWQtbhsspZLn2dyxz6ELYD1MXTgmhn
         6KwcNNuPg/qV1HdMzNChLLuxaN0MgX4w8DpqCmAz9OBcdkKx029FT70ShiSul5a2CUmR
         YIJZ4Eq2+U6qgyu6r4JXErswh6ZiLmOcU8cW+LlpVSGTXPvyrrUlbFv59X9e9w6rbnZb
         BaKafSsJzR2R1RRATANDjKaIn0umprbD44+wpvQzyv86ERHeQwbfMRIdLPmD/E/WtAIJ
         Zu2g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=KVrTSfhJQkcjGUoc6/wChtJatdSgDTO1rfWfls9h3Lo=;
        b=sMKZjd70Jl9W1nSjXj6m6r1BTGUoVXWhMjKFsXhS0Aax7D0wDideJiPsxmml37oFoj
         l9yAhFNO92EINE98hG0vhdUWGYlzejpuBRQ/eKpF+HjZ4LhXJQ/zIle121H3c9Uz+KPc
         KWQUH9EBjA1eANjUSPyOlruWSmQU9/SsGPNmB2cA45CSSYaYxibCVEpZLNNyQIMr+sVm
         5+4aBWZHi28Bkv2Cxs2TmC5bZ9yIPUN8436BIHs7hr1B6BH3E6RmMfo8B1YT6Lfq/RlY
         Te14ivUihFCNyje8kUsllPSlNTakakM+G55uLZtgU44rSekEbo+JgqNZ6kyisKu/9gqD
         QfzQ==
X-Gm-Message-State: APjAAAXFw2I1MU/XqFJinvyJJoov+HrfZ9FlYapLrtzhQoR1Caicqnp2
        OdaV9vh3xdQF8RkjJunmqmQ=
X-Google-Smtp-Source: 
 APXvYqy8k3bgKZ6SInwf+MtKGz30qnvpeRSYEDcISJ/9qHK4gqkYxjgovCiY5DiyZ7FrOUPil/on6Q==
X-Received: by 2002:a1c:66c2:: with SMTP id a185mr10587954wmc.2.1570190636233;
        Fri, 04 Oct 2019 05:03:56 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 t83sm9325709wmt.18.2019.10.04.05.03.55
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 04 Oct 2019 05:03:55 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.4-rc2
Date: Fri,  4 Oct 2019 14:03:52 +0200
Message-Id: <1570190632-22964-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit fd3edd4a9066f28de99a16685a586d68a9f551f8:

  KVM: nVMX: cleanup and fix host 64-bit mode checks (2019-09-25 19:22:33 +0200)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to cf05a67b68b8d9d6469bedb63ee461f8c7de62e6:

  KVM: x86: omit "impossible" pmu MSRs from MSR list (2019-10-04 14:01:28 +0200)

----------------------------------------------------------------
ARM and x86 bugfixes of all kinds.  The most visible one is that migrating
a nested hypervisor has always been busted on Broadwell and newer processors,
and that has finally been fixed.

----------------------------------------------------------------
Jim Mattson (5):
      kvm: x86: Fix a spurious -E2BIG in __do_cpuid_func
      kvm: x86: Improve emulation of CPUID leaves 0BH and 1FH
      kvm: x86: Use AMD CPUID semantics for AMD vCPUs
      kvm: x86: Enumerate support for CLZERO instruction
      kvm: vmx: Limit guest PMCs to those supported on the host

Marc Zyngier (3):
      arm64: KVM: Drop hyp_alternate_select for checking for ARM64_WORKAROUND_834220
      arm64: KVM: Replace hyp_alternate_select with has_vhe()
      arm64: KVM: Kill hyp_alternate_select()

Paolo Bonzini (7):
      KVM: x86: assign two bits to track SPTE kinds
      KVM: x86: fix nested guest live migration with PML
      selftests: kvm: add test for dirty logging inside nested guests
      kvm: x86, powerpc: do not allow clearing largepages debugfs entry
      KVM: x86: omit absent pmu MSRs from MSR list
      Merge tag 'kvmarm-fixes-5.4-1' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: x86: omit "impossible" pmu MSRs from MSR list

Sean Christopherson (1):
      KVM: nVMX: Fix consistency check on injected exception error code

Sebastian Andrzej Siewior (1):
      KVM: x86: Expose XSAVEERPTR to the guest

Shuah Khan (1):
      selftests: kvm: Fix libkvm build error

Vitaly Kuznetsov (1):
      KVM: selftests: x86: clarify what is reported on KVM_GET_MSRS failure

Waiman Long (1):
      KVM: VMX: Set VMENTER_L1D_FLUSH_NOT_REQUIRED if !X86_BUG_L1TF

Wanpeng Li (2):
      KVM: LAPIC: Loosen filter for adaptive tuning of lapic_timer_advance_ns
      KVM: X86: Fix userspace set invalid CR4

Zenghui Yu (1):
      KVM: arm/arm64: vgic: Use the appropriate TRACE_INCLUDE_PATH

 arch/arm64/include/asm/kvm_hyp.h                   |  24 ---
 arch/arm64/kvm/hyp/switch.c                        |  17 +-
 arch/arm64/kvm/hyp/tlb.c                           |  36 ++--
 arch/powerpc/kvm/book3s.c                          |   8 +-
 arch/x86/include/asm/kvm_host.h                    |   7 -
 arch/x86/kvm/cpuid.c                               | 102 ++++++-----
 arch/x86/kvm/lapic.c                               |  13 +-
 arch/x86/kvm/mmu.c                                 |  65 +++++--
 arch/x86/kvm/vmx/nested.c                          |   2 +-
 arch/x86/kvm/vmx/pmu_intel.c                       |   7 +-
 arch/x86/kvm/vmx/vmx.c                             |  15 +-
 arch/x86/kvm/x86.c                                 |  72 ++++----
 include/linux/kvm_host.h                           |   2 +
 tools/testing/selftests/kvm/Makefile               |   3 +-
 .../selftests/kvm/include/x86_64/processor.h       |   3 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |  14 ++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   2 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   3 +
 tools/testing/selftests/kvm/lib/x86_64/processor.c |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 201 ++++++++++++++++++++-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c      | 156 ++++++++++++++++
 virt/kvm/arm/vgic/trace.h                          |   2 +-
 virt/kvm/kvm_main.c                                |  10 +-
 23 files changed, 584 insertions(+), 182 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_dirty_log_test.c
```
#### [PATCH] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11175149
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C85CE13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 17:52:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9260421D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 17:52:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="fvBbctmY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388496AbfJDRwO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 13:52:14 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:40481 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388197AbfJDRwO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 13:52:14 -0400
Received: by mail-pg1-f202.google.com with SMTP id w5so4823101pgp.7
        for <kvm@vger.kernel.org>; Fri, 04 Oct 2019 10:52:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=WntMB4QMmx7jpfA4AcSP9Rfh9DukEF1gUBf1ITUKNjU=;
        b=fvBbctmYoNMlKdzP+/yqeQCccZWQxUofCw8bGUWU6Fc1Dz8dBYov18n7g7DdkJnTmS
         pq8RmPWO4EbjaBTMSUfimgqDoWJDY1EReNEF1Ac1a4sO+vD/lFH2ht0JqRtq3LV5Z/Sg
         I+108O36xZrtobANf1pOkFB11bQOvYBnhlJ2+VwAYcSGWuGYi8ufb0/Nq2AYOPDsim7v
         kXRc1ATsSC/l8IL/6XhxsDRzKfzFTwF/uzc3oMZQIMelgzRZeH1zGy7U9Agl+B6ID6bS
         tr16M/e13WSfRyNmvU0ifTZMoeTCY5xLxsG4BPeDgFa+IJXhqkXfPIlBJt2h/PVHBezn
         eEsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=WntMB4QMmx7jpfA4AcSP9Rfh9DukEF1gUBf1ITUKNjU=;
        b=sZ62v9GspygUbRKCAFLu9cKPhZBmBk8ojqYlqIlhSCkxrhBg5/o0fWAfb96+10V2G0
         bf467DhtXPzmrvXGA6hnkwdZlWW9EZRkyumuqOYTrNtqamAX7ywiMZq1vfvoNRWtJ0BK
         Pdb8pYcQNcAuciOrriPy+xk8sVmBaxXOhIIJcwq/XteVKh3tRXfEQjjrNSVDw4GUKDQq
         HakxjVOUZBlEP4363He/jlR4XksYI5JHLK8DRuDvADDL6ZVt1NZKG8F27VYEqEV7/IHB
         YPZpUGJI7rQpw+SXO2CY9jPMm9/XmLdD/ydt3pmM11t32ncvUAKqD2rEfL7l9mxZtNxv
         0bvw==
X-Gm-Message-State: APjAAAWijOIXY+nwLXQ6Rkqd3bSwuxPHilbNEbveMxgOYWasgvKJ1Pqz
        dudoB/2MNgglHZ03qISswGwcLqwuNgLiPsL8FudySDZToQ77wkED1k364d8J5cGlx6SJeWl/S3V
        0caYWF0VOAxxNI3rDz+wS/pYh0eeCONGPb5hRmHqCJg1ylxVk2ImWKz00gLILrKk=
X-Google-Smtp-Source: 
 APXvYqw0JiN+azKkD0VKtjYoIW4436ghFaTlNfWz/teqGIqz5MfrW/WeI5cW+7x7vB+J6wM/S24GjFFBggDTEg==
X-Received: by 2002:a63:1c48:: with SMTP id c8mr16449251pgm.342.1570211532973;
 Fri, 04 Oct 2019 10:52:12 -0700 (PDT)
Date: Fri,  4 Oct 2019 10:52:03 -0700
Message-Id: <20191004175203.145954-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.581.g78d2f28ef7-goog
Subject: [PATCH] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Marc Orr <marcorr@google.com>, Peter Shier <pshier@google.com>,
        Liran Alon <liran.alon@oracle.com>
Content-Type: text/plain; charset="UTF-8"
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
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Dan Cross <dcross@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
v1: Same code as the RFC.

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 46 ++++++++++++++++++---------------
 arch/x86/kvm/x86.c              |  9 +++++--
 3 files changed, 33 insertions(+), 24 deletions(-)

```
#### [PATCH] kvm: selftests: fix spelling mistake: missmatch -> mismatch
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin Ian King <colin.king@canonical.com>
X-Patchwork-Id: 11173745
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F95915AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 08:13:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 280C22084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 08:13:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387588AbfJDINq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 04:13:46 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:39782 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725730AbfJDINq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 04:13:46 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1iGIic-0001Rs-IS; Fri, 04 Oct 2019 08:13:42 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Shuah Khan <shuah@kernel.org>, kvm@vger.kernel.org,
 linux-kselftest@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] kvm: selftests: fix spelling mistake: missmatch -> mismatch
Date: Fri,  4 Oct 2019 09:13:42 +0100
Message-Id: <20191004081342.22108-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

There is a spelling mistake in in an error message, fix it.

Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 tools/testing/selftests/kvm/lib/sparsebit.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: x86: Expose RDPID in KVM_GET_SUPPORTED_CPUIDFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11175269
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E47013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 20:23:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6B76E21D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 20:23:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dvVFZMsf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731270AbfJDUW7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 16:22:59 -0400
Received: from mail-vk1-f202.google.com ([209.85.221.202]:45365 "EHLO
        mail-vk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729079AbfJDUW7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 16:22:59 -0400
Received: by mail-vk1-f202.google.com with SMTP id q84so3101800vkb.12
        for <kvm@vger.kernel.org>; Fri, 04 Oct 2019 13:22:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=qJDTT4TzSeM6Ovj+jHpxrL9mwVSVi8k8BDpDAv20MTU=;
        b=dvVFZMsfHuYIqaLHJklvqK9f+qzvk35qAJsMoBxiPLkbyumc8k+ZhLW2Sw4F0Mgz69
         8NLIjjpYDavr4DfYDNuac9vhiDqekaoPQsCe2C21nhMkSOAzR0HqZq2IDje/5YjK3vFH
         r2aaE5rvb/HO/pwXPF8+Dz79iNB68n8A/iKSKlxERlzOj4XNO9yc9erSW/7wK/O0LVki
         Dps5ZbVIGf86051T65wcyEfrtGwRvCtBGFUJCpjgdHA55TDqqEbBfXXN83+VhK0+t9rK
         mzhH8R037X0MPaMii0V9av6O586XZ1wUTim74ZIz/b6LBg7zmp3Td3xtJS5rEVk5dDsT
         mAGg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=qJDTT4TzSeM6Ovj+jHpxrL9mwVSVi8k8BDpDAv20MTU=;
        b=p+PTALnPEFnYe/1g8Dip9Ak9FkL1BOqCFEkc0jaq1QxbBW7VFNZGTf0Jy16A+eWiJT
         b7wyDZ/Z3fs07ppBbW6ljwoAmwO9oy1NA3mwR+MfAEswMs0sY5F2fn+8vpgy+jL7Aa+b
         yFpTcuj1sBvwthh25z4EZfMA7nxmEmNDmWln53r9pNduggIOdP4Ov4HjKYjUBEwJW9TW
         OIlh08XV0YvT3g10LDqgZ3CjdXRCx81yPWAGe/WktNwMfIf3hE24PYu5VmfBXTUFoCpY
         /GzGAIDaNjlZhqYCvdWG0yerqFxpt2PBX2g1B8IWKhBiT8JhkhjVj9v4oTW+T32ypGoh
         2epw==
X-Gm-Message-State: APjAAAU0g6+cyvuM62dS8vmvbpnRHpr5jYoVWdcqnSxNEaKN38KUsVqe
        YH7axfaGAeAPE/02yLAaoGiawx11rPfAEiL6NUtgq/z868wbgaUw/eVB8S2UYLGzdOYJ5Dz7HZ+
        qtRmhwuGjqVwGIX3G139Il562ocW2vWZtWQ3hE4+R9+6LfLPjMNoro11GRUEF3xI=
X-Google-Smtp-Source: 
 APXvYqxDBs1MunWLoVdvn9DuiZTa26vmQ3PveqfRoanmVeBobh3RHhZyXd3GOr+gBpo2YKZNqbh41I7a+A8iYQ==
X-Received: by 2002:ac5:c186:: with SMTP id z6mr2003757vkb.45.1570220577770;
 Fri, 04 Oct 2019 13:22:57 -0700 (PDT)
Date: Fri,  4 Oct 2019 13:22:47 -0700
Message-Id: <20191004202247.179660-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.581.g78d2f28ef7-goog
Subject: [PATCH] kvm: x86: Expose RDPID in KVM_GET_SUPPORTED_CPUID
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Jim Mattson <jmattson@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the RDPID instruction is supported on the host, enumerate it in
KVM_GET_SUPPORTED_CPUID.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] powerpc: Fix up RTAS invocation for new qemu versions
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11174111
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC30513BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 10:38:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B974F21D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 10:38:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="pb1FvXcO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729291AbfJDKix (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 06:38:53 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:45301 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725788AbfJDKix (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 06:38:53 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 46l5vZ2Hgkz9sNw; Fri,  4 Oct 2019 20:38:50 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1570185530;
        bh=6ZYAP3kzygIvshHZBkrCIgOhh+ZjXOmnm0g1aJ4p4m8=;
        h=From:To:Cc:Subject:Date:From;
        b=pb1FvXcOt4ClvFpDA07cag6IunhntVyApGw7VA/Srgc7/IJk+7VDMPZ/aZFvMP0cQ
         qY7Dye93O1U0YS/u3RfoXe1htmaUixXK3320U0+MKYxxw9DnOz3EnRdrc4J0zTHoL4
         CddYkk1Gg2ZuGuLLGDHI/kjgZNIdtGcQFv6nk9HQ=
From: David Gibson <david@gibson.dropbear.id.au>
To: lvivier@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, kvm-ppc@vger.kernel.org, pbonzini@redhat.com,
        rkrcmar@redhat.com, David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] powerpc: Fix up RTAS invocation for new qemu versions
Date: Fri,  4 Oct 2019 20:38:44 +1000
Message-Id: <20191004103844.32590-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to call RTAS functions on powerpc kvm-unit-tests relies on the
RTAS blob supplied by qemu.  But new versions of qemu don't supply an RTAS
blob: since the normal way for guests to get RTAS is to call the guest
firmware's instantiate-rtas function, we now rely on that guest firmware
to provide the RTAS code itself.

But qemu-kvm-tests bypasses the usual guest firmware to just run itself,
so we can't get the rtas blob from SLOF.

But.. in fact the RTAS blob under qemu is a bit of a sham anyway - it's
a tiny wrapper that forwards the RTAS call to a hypercall.  So, we can
just invoke that hypercall directly.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 lib/powerpc/asm/hcall.h |  3 +++
 lib/powerpc/rtas.c      |  6 +++---
 powerpc/cstart64.S      | 20 ++++++++++++++++----
 3 files changed, 22 insertions(+), 7 deletions(-)

So.. "new versions of qemu" in this case means ones that incorporate
the pull request I just sent today.

```
#### [PATCH 01/16] x86/intel: Initialize IA32_FEATURE_CONTROL MSR at boot
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11175379
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2070213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 21:57:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 09D14222C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 21:57:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731452AbfJDV42 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 17:56:28 -0400
Received: from mga09.intel.com ([134.134.136.24]:5964 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731179AbfJDV41 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 17:56:27 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Oct 2019 14:56:26 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,257,1566889200";
   d="scan'208";a="191710648"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga008.fm.intel.com with ESMTP; 04 Oct 2019 14:56:25 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, x86@kernel.org,
 Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-edac@vger.kernel.org,
        Borislav Petkov <bp@suse.de>,
        Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH 01/16] x86/intel: Initialize IA32_FEATURE_CONTROL MSR at boot
Date: Fri,  4 Oct 2019 14:56:00 -0700
Message-Id: <20191004215615.5479-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20191004215615.5479-1-sean.j.christopherson@intel.com>
References: <20191004215615.5479-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Opportunistically initialize IA32_FEATURE_CONTROL MSR to enable VMX when
the MSR is left unlocked by BIOS.  Configuring IA32_FEATURE_CONTROL at
boot time paves the way for similar enabling of other features, e.g.
Software Guard Extensions (SGX).

Temporarily leave equivalent KVM code in place in order to avoid
introducing a regression on Centaur and Zhaoxin CPUs, e.g. removing
KVM's code would leave the MSR unlocked on those CPUs and would break
existing functionality if people are loading kvm_intel on Centaur and/or
Zhaoxin.  Defer enablement of the boot-time configuration on Centaur and
Zhaoxin to future patches to aid bisection.

Note, Local Machine Check Exceptions (LMCE) are also supported by the
kernel and enabled via IA32_FEATURE_CONTROL, but the kernel currently
uses LMCE if and and only if the feature is explicitly enable by BIOS.
Keep the current behavior to avoid introducing bugs, future patches can
opt in to opportunistic enabling if it's deemed desirable to do so.

Always lock IA32_FEATURE_CONTROL if it exists, even if the CPU doesn't
support VMX, so that other existing and future kernel code that queries
IA32_FEATURE_CONTROL can assume it's locked.

Start from a clean slate when constructing the value to write to
IA32_FEATURE_CONTROL, i.e. ignore whatever value BIOS left in the MSR so
as not to enable random features or fault on the WRMSR.

Suggested-by: Borislav Petkov <bp@suse.de>
Cc: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/Kconfig.cpu                  |  4 ++++
 arch/x86/kernel/cpu/Makefile          |  1 +
 arch/x86/kernel/cpu/cpu.h             |  4 ++++
 arch/x86/kernel/cpu/feature_control.c | 30 +++++++++++++++++++++++++++
 arch/x86/kernel/cpu/intel.c           |  2 ++
 5 files changed, 41 insertions(+)
 create mode 100644 arch/x86/kernel/cpu/feature_control.c

```
