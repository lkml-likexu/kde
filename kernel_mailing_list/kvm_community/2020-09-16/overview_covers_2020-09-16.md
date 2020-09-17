

#### [PATCH v7 0/7] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Wed Sep 16 20:29:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11780829
Return-Path: <SRS0=aKWm=CZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 50B37618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 20:33:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28B7C21974
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Sep 2020 20:33:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="nzqd9VJj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727133AbgIPUck (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 16:32:40 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:48544 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726943AbgIPUaI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 16:30:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1600288207; x=1631824207;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=4OMtNb83YORhDNCIQPC8PZHNb6sILR2vnYsotDnFmcY=;
  b=nzqd9VJjBWWXW9MTRoYBhCRF2bp56x5gccM8yk4c1C873HJ8trVqe4Le
   8IjnBK8bveUtxcwThN+SofhyABEoJ76aiXBaHe9molyy5tiMKCngKTytU
   yO8nPXE8FpGm4Bp3z+xs/+1lgPB9pPw5BpowLK/If43t+8LzWqPrUCRp4
   o=;
X-IronPort-AV: E=Sophos;i="5.76,434,1592870400";
   d="scan'208";a="54452033"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 16 Sep 2020 20:30:04 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com (Postfix) with
 ESMTPS id C7A69A1BD3;
        Wed, 16 Sep 2020 20:30:02 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 16 Sep 2020 20:30:02 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.35) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 16 Sep 2020 20:29:58 +0000
From: Alexander Graf <graf@amazon.com>
To: kvm list <kvm@vger.kernel.org>
CC: Sean Christopherson <sean.j.christopherson@intel.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v7 0/7] Allow user space to restrict and augment MSR emulation
Date: Wed, 16 Sep 2020 22:29:44 +0200
Message-ID: <20200916202951.23760-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.162.35]
X-ClientProxiedBy: EX13D42UWA002.ant.amazon.com (10.43.160.16) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with filtering, user space trapping allows us to emulate
arbitrary MSRs in user space, paving the way for target CPU specific MSR
implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

v3 -> v4:

  - Mention exit reasons in re-enter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
  - lock allow check and clearing
  - free bitmaps on clear

v4 -> v5:

  - use srcu 

v5 -> v6:

  - Switch from allow list to filtering API with explicit fallback option
  - Support and test passthrough MSR filtering
  - Check for filter exit reason
  - Add .gitignore
  - send filter change notification
  - change to atomic set_msr_filter ioctl with fallback flag
  - use EPERM for filter blocks
  - add bit for MSR user space deflection
  - check for overflow of BITS_TO_LONGS (thanks Dan Carpenter!)
  - s/int i;/u32 i;/
  - remove overlap check
  - Introduce exit reason mask to allow for future expansion and filtering
  - s/emul_to_vcpu(ctxt)/vcpu/
  - imported patch: KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs
  - new patch: KVM: x86: Add infrastructure for MSR filtering
  - new patch: KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  - new patch: KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied

v6 -> v7:

  - s/MAX_POSSIBLE_PASSGHROUGH_MSRS/MAX_POSSIBLE_PASSTHROUGH_MSRS/g
  - Fire #GP without skipping the MSR instruction
  - uapi: Fix padding
  - selftest: trap on KVM_MSR_EXIT_REASON_FILTER as well
  - selftest: fix asserts
  - selftest: add test for invalid msr handling

Aaron Lewis (1):
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs

Alexander Graf (6):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Add infrastructure for MSR filtering
  KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied
  KVM: x86: Introduce MSR filtering
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 176 +++++++++-
 arch/x86/include/asm/kvm_host.h               |  18 ++
 arch/x86/include/uapi/asm/kvm.h               |  19 ++
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/svm/svm.c                        | 135 ++++++--
 arch/x86/kvm/svm/svm.h                        |   7 +
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        | 303 ++++++++++++------
 arch/x86/kvm/vmx/vmx.h                        |   9 +-
 arch/x86/kvm/x86.c                            | 267 ++++++++++++++-
 arch/x86/kvm/x86.h                            |   1 +
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 247 ++++++++++++++
 16 files changed, 1088 insertions(+), 135 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
