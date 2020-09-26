

#### [PATCH v4 0/2] Add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Sep 25 06:10:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11799007
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5DADD1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 06:07:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 430CD21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 06:07:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727217AbgIYGHv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 02:07:51 -0400
Received: from mga14.intel.com ([192.55.52.115]:55277 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726983AbgIYGHu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 02:07:50 -0400
IronPort-SDR: 
 lvmoOJ7cxx+OSy93Tf+Jmb2exemsfAS8eFLXRXsKpEj10izfbTfEZlr/KvE6iheJTWdYD8eEGq
 km97jihPb0tA==
X-IronPort-AV: E=McAfee;i="6000,8403,9754"; a="160701140"
X-IronPort-AV: E=Sophos;i="5.77,300,1596524400";
   d="scan'208";a="160701140"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Sep 2020 23:07:49 -0700
IronPort-SDR: 
 emxH2a79R33KMfvAjN1EI3RhwfEmtTDslXirqzGK0nSKKSmoMPxHhbT1tNJNZuB1NsJK/mwXTs
 NiaREVJhUXzw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,300,1596524400";
   d="scan'208";a="487325183"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005.jf.intel.com with ESMTP; 24 Sep 2020 23:07:47 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/2] Add bus lock VM exit support
Date: Fri, 25 Sep 2020 14:10:00 +0800
Message-Id: <20200925061002.28336-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series add the support for bus lock VM exit in KVM. It is a
sub-feature of bus lock detection. When it is enabled by the VMM, the
processor generates a "Bus Lock" VM exit following execution of an
instruction if the processor detects that one or more bus locks were
caused the instruction was being executed (due to either direct access
by the instruction or stuffed accesses like through A/D updates).

This first patch applies Sean's refactor for vcpu_vmx.exit_reason
available at https://patchwork.kernel.org/patch/11500659.
It is necessary as bus lock VM exit adds a new modifier bit(bit 26) in
exit_reason field in VMCS.

The second patch is the enabling work for bus lock VM exit. Add the
support to set the capability to enable bus lock vm exit. The current
implementation just exit to user space when handling the bus lock
detected in guest.

The concrete throttling policy in user space is still to be discussed.
We can enforce ratelimit on bus lock in guest, inject some sleep time or
maybe other ideas.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html
---

Changelogs

v3->v4:
- rebase on top of v5.9-rc6
- some code cleanup.
- v3:https://lore.kernel.org/lkml/20200910083751.26686-1-chenyi.qiang@intel.com/

v2->v3:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
- v2:https://lore.kernel.org/lkml/20200817033604.5836-1-chenyi.qiang@intel.com/ 

v1->v2:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.
- v1:https://lore.kernel.org/lkml/20200628085341.5107-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (1):
  KVM: VMX: Enable bus lock VM exit

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/include/asm/kvm_host.h    |   7 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 +++++++-----
 arch/x86/kvm/vmx/vmx.c             | 103 +++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  29 +++++++-
 include/uapi/linux/kvm.h           |   5 ++
 11 files changed, 172 insertions(+), 52 deletions(-)
```
#### [PATCH v8 0/8] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Fri Sep 25 14:34:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11799925
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B2B51580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:35:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F9AE22B2D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 14:35:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="Dfsz7Odp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728978AbgIYOfE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 10:35:04 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:12199 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728960AbgIYOfD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 10:35:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1601044503; x=1632580503;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=glN5TArU2loYWTVC+Uyhcgh2yNYL1XpJNimKI1PsQRc=;
  b=Dfsz7OdpVQv3UyBpRmgqfqBnFiWPO37j8bLRcWypPY40tK3SyDZMAxz0
   Jf7ibU4UC/ckwj0M3H2wpXifgk4jzCLi+k+FWINWm1XoSfkptP7PNP4HH
   I4ElIijnT8yCMdtKWGWFM+o6OkVc7zlJSe6ZeGUJc/sMThaXrGsKcL0Wv
   I=;
X-IronPort-AV: E=Sophos;i="5.77,302,1596499200";
   d="scan'208";a="79292761"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1a-807d4a99.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 25 Sep 2020 14:34:41 +0000
Received: from EX13MTAUWC002.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-807d4a99.us-east-1.amazon.com (Postfix) with
 ESMTPS id 08BBAA1C9C;
        Fri, 25 Sep 2020 14:34:33 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC002.ant.amazon.com (10.43.162.240) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 25 Sep 2020 14:34:33 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.221) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 25 Sep 2020 14:34:30 +0000
From: Alexander Graf <graf@amazon.com>
To: kvm list <kvm@vger.kernel.org>
CC: Aaron Lewis <aaronlewis@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        "Dan Carpenter" <dan.carpenter@oracle.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v8 0/8] Allow user space to restrict and augment MSR emulation
Date: Fri, 25 Sep 2020 16:34:14 +0200
Message-ID: <20200925143422.21718-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.162.221]
X-ClientProxiedBy: EX13D08UWC002.ant.amazon.com (10.43.162.168) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
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

v7 -> v8:

  - new patch: KVM: x86: Return -ENOENT on unimplemented MSRs
  - Add KVM_MSR_EXIT_REASON_UNKNOWN
  - s/KVM_MSR_ALLOW/KVM_MSR_FILTER/g
  - fix language in documentation
  - introduce KVM_MSR_FILTER_MAX_RANGES
  - adapt KVM_MSR_EXIT_REASON_FILTER value
  - selftest: add KVM_MSR_EXIT_REASON_UNKNOWN handling

Aaron Lewis (1):
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs

Alexander Graf (7):
  KVM: x86: Return -ENOENT on unimplemented MSRs
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Add infrastructure for MSR filtering
  KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied
  KVM: x86: Introduce MSR filtering
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 182 ++++++++++-
 arch/x86/include/asm/kvm_host.h               |  18 ++
 arch/x86/include/uapi/asm/kvm.h               |  20 ++
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/svm/svm.c                        | 135 ++++++--
 arch/x86/kvm/svm/svm.h                        |   7 +
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        | 303 ++++++++++++------
 arch/x86/kvm/vmx/vmx.h                        |   9 +-
 arch/x86/kvm/x86.c                            | 271 +++++++++++++++-
 arch/x86/kvm/x86.h                            |   1 +
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  18 ++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 248 ++++++++++++++
 16 files changed, 1100 insertions(+), 136 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
#### [PATCH v1 0/4] s390x: css: pv: css test adaptation for PV
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Fri Sep 25 16:02:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11800355
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D0BB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 16:37:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E509235F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 16:37:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Blo/8nN2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729446AbgIYQhu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 12:37:50 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64876 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728306AbgIYQht (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Sep 2020 12:37:49 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08PGXcT5178823;
        Fri, 25 Sep 2020 12:37:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=U8HaMDBnzvbShJNoUhoZLINiv5DPAPALPd6WKqKhOoM=;
 b=Blo/8nN2SgFjGRj4+X4dTDdGzn0qDoa9WJDmGjYcP2GNCAOAG/6odsAlXXGNJ8I+cQ6A
 Dty3jveXhq1wrn+wSao7bgpJfYrX5tJl0iT04dnk9lHg/xjt6LTVZlav6M6rL56iakpU
 f9wBTAii/x+wtuNfaqy5RN5JeW+kvdi5NLTb7CixUL1QpmVI6UByWRdHzH8cFiLuNAbl
 TZz1TmeK8RXOGaJUcuOsHjpubr7Tb/mXqEqxjJQh+g9oBvOp2tMDrxjnvL5+ngIpBpmO
 KkFLRUsaov767e/+1SAl2ONqYIniOKp3lFb5jyy0kBZtUhMj+Dgeou1xeJpZgBU58cPU 7w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33sm46g5kd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 12:37:49 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08PGXYEP178396;
        Fri, 25 Sep 2020 12:37:48 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33sm46g5jf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 12:37:48 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08PFg6b5023546;
        Fri, 25 Sep 2020 16:02:49 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06fra.de.ibm.com with ESMTP id 33n98guc5n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 25 Sep 2020 16:02:48 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08PG2kk232506168
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 25 Sep 2020 16:02:46 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 05288A4060;
        Fri, 25 Sep 2020 16:02:46 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8F77AA4054;
        Fri, 25 Sep 2020 16:02:45 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.49.151])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 25 Sep 2020 16:02:45 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com
Subject: [PATCH v1 0/4] s390x: css: pv: css test adaptation for PV
Date: Fri, 25 Sep 2020 18:02:40 +0200
Message-Id: <1601049764-11784-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-25_14:2020-09-24,2020-09-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 clxscore=1015 priorityscore=1501 lowpriorityscore=0 adultscore=0
 mlxlogscore=999 impostorscore=0 mlxscore=0 malwarescore=0 phishscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009250111
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

To adapt the CSS I/O tests to protected virtualisation we need
utilities to:

1- allocate the I/O buffers in a private page (patch 3)
   It must be in a dedicated page to avoid exporting code or
   guest private data to the host.

2- share  the I/O buffer with the host (patch 2)

3- be sure to allocate memory under 2Gb (patch 1)

The 3 first patches are the implementation of the tools,
patch 4 is the modification of the css.c test for PV.

regards,
Pierre

Pierre Morel (4):
  memory: allocation in low memory
  s390x: pv: implement routine to share/unshare memory
  s390: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 lib/alloc_dma_page.c  | 57 +++++++++++++++++++++++++++++++++++++++++++
 lib/alloc_dma_page.h  | 24 ++++++++++++++++++
 lib/s390x/asm/uv.h    | 33 +++++++++++++++++++++++++
 lib/s390x/css.h       |  3 +--
 lib/s390x/css_lib.c   | 28 ++++++---------------
 lib/s390x/malloc_io.c | 50 +++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 18 ++++++++++++++
 lib/s390x/sclp.c      |  2 ++
 s390x/Makefile        |  2 ++
 s390x/css.c           | 35 +++++++++++++++++---------
 10 files changed, 219 insertions(+), 33 deletions(-)
 create mode 100644 lib/alloc_dma_page.c
 create mode 100644 lib/alloc_dma_page.h
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
#### [PATCH v4 0/6] Qemu SEV-ES guest support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Fri Sep 25 19:03:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11800613
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3E71112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 19:04:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3BA2221E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 19:04:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="lx10b1kX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729714AbgIYTEV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 15:04:21 -0400
Received: from mail-bn8nam11on2055.outbound.protection.outlook.com
 ([40.107.236.55]:21825
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728069AbgIYTEV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 15:04:21 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hxX2xakAVsIBbq2zuTif663+UBd9mXhVNS0I2JDYkIFhaF5Nip6MRT1f/jOQJcmLXqb8ScvS5WT8o06OTe7VH0/WKfDHe7xPgK8dbXAeLNwGxqELtjnrH6NH5n7aRbTdFQwLPkYkRewoFSN6A7Br/qptup2euz9EFgLjbva2XEkW4/vZ8bStXrwYd5aXCFjrBFe6AaCen/XuOhnJCjaqTNpsGsygIay88j5N0vgnWtV9JAg4LejxQd3JX265EXmSfWVSRMiwz03okEQqU4wu+UpCbJiNz6iwchK3ocGddOetBrGarjT04HNoopoDBJpZ205XN3+n0jQwLua9/MGlYA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cPq7mKywqVJZ1A0hpheU2wUMay/4kqACwBuweMnWVm8=;
 b=b6BNrJRobVah4dj4C6KVDfZGjNYdldkBMirW0kPrq+fHw9y54CDYvXSPOefAzkc3H+6C0t0a1R6BRmePtbVBR0TbzTctt4yrMrwiSJ6UDlUuiBg8ycHrOugria6p7AzLyUqdJqHs/NcCE1vVwey97TDuZbF0i2AiNr/lXwpjEZvabsRrh1kEVGm410UkKij8gSw7+QJmOs/lcIXuWDhuveXlBEp6qX5lhSU8EP2YVu5g/TBju6lC7UikGvjUAEHSmIH3EdcYfZ58WyDNezm/aQDxYQIMTQtZiJpPtR0ChBV9hH927pRKEkNMVPQt674wGGVpvH+YGCYPtY7xCgvKuQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cPq7mKywqVJZ1A0hpheU2wUMay/4kqACwBuweMnWVm8=;
 b=lx10b1kXswl+Kz0TmPyL+DHYmjXZs4Nu7PsD+6logpwhCRivvnRWEcz/yOLsE9F2spbX0U5l96UPbhfYAUodHxK68dmSuXmKb9c1EcE2jVuEBI+V/LHbMeo7di6f3l/cyy3ubWYJRpjV33njFSRGExXR3KVEttedqkFiRL4yS5w=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4297.namprd12.prod.outlook.com (2603:10b6:5:211::20) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.22; Fri, 25 Sep 2020 19:04:17 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3391.024; Fri, 25 Sep 2020
 19:04:17 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v4 0/6] Qemu SEV-ES guest support
Date: Fri, 25 Sep 2020 14:03:34 -0500
Message-Id: <cover.1601060620.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: DM3PR12CA0121.namprd12.prod.outlook.com
 (2603:10b6:0:51::17) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM3PR12CA0121.namprd12.prod.outlook.com (2603:10b6:0:51::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3412.22 via Frontend
 Transport; Fri, 25 Sep 2020 19:04:16 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 7f15d430-0b96-41ec-9823-08d86185cd27
X-MS-TrafficTypeDiagnostic: DM6PR12MB4297:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4297E6EAEA873DBD2D0A6BF5EC360@DM6PR12MB4297.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 +IFiiFfKISANgFubJdQuc+wHLNU7TYsrSmKfrDRJ7OwJCuXxed3QlttaEtb7dnLWMVNYkjiMzN/5uAngIILqA3S8BLFvIPRWZdM7tMXQq5tHHi2Q0O0HXJJy9oSQpqKju6rQ2WemNngoUC1WRHK8lnTuJhx6pQ4FOhW5vqPCmXy2GRPvHnD1y7YUKaKO2BPeZ+JyyIEekCmrnkXl0BH85MIhMHOBPGICuWAQckKxY/i2qOQ5ydMJG1pZ0fv5YI4lPLUC83HC0vBZklLi5RVzv1qPkhDR3d204DW3LFTml4qutzC0Pxy7cGNJ78KbaA8MLTDlSE8RervHgDzGE+4D9CLwpwpyztxcC6Pf/kmLQE9f+VCzCFd9ho4RpVXfLmQbT9TAP9wdc9lX6oYfNhYgTHqen9DOo50oNfgugVuMeIlo+euiI4gTIqoEx3bYa5PP
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(136003)(396003)(376002)(39860400002)(26005)(7416002)(956004)(186003)(6666004)(16526019)(54906003)(2616005)(6486002)(966005)(66556008)(66946007)(36756003)(8936002)(66476007)(86362001)(316002)(478600001)(7696005)(52116002)(2906002)(5660300002)(4326008)(83380400001)(8676002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 oohA0++EeEjP/DszGoBcm+KVazAN3iYU4BcXMfDWttpZWVWLro/qP1pBLlHJw0fGZZ2twoYRqhLVkoNOoDcZYn3kjOB9CZy4WJO5aRy/t96Z3IwUDItJlpXvzZiWxrCN0wgO2yXbg69Gj4iQ1oqhsrqFyOunYYr5dkfnciz7/7O0uJYnreZAwndaDqRstGIanjM2jtBU7RkADOn0U1o3lW8Wo6cijmDZdSli+36FuW2cwpN8l5iP4mLr1Bm1IaXWmh/al+ZmLtTciV1uPL2WmrWh/bOCgAwU9a770Z6wLAc742fSkh+hqNEEgK3ZaZsyM4z4huE5uDhZ+F1uhENp+P/+3xoK7Z18FUD23Yyg1sn9co/Aoq9kfewAOzYZVTIGrDZOFE1O8unHvKcJIovFU3xAqPSXu1BR53gOo2EiCozMZD9CPtP4G9B7RH5i4Qnyv9GRUR8hybl8jhDhCYrXdPr4S+g1BT2M2U/6EKnU25A1FgBqppJ3lS1V9Gqtp7srxjzd9+xEWS9RCsyWEPoiJNlA1zu7SwfGouffi1PN7qgNFw/MGCNodgKBQ2olaKaiCRsYBq0rabCA8we0+uidIGl1XXnoV7KatjLGMbppoFsH2KumUoZ/9tC1/4cHeMaUqijjp/K7uNBymQyd8pVvJw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7f15d430-0b96-41ec-9823-08d86185cd27
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 25 Sep 2020 19:04:17.5872
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 WX9G5PjvDfdbtrDfHSljWf7LC96YXzguo4Wp9kEydbHgYYAX8yI/wnx4vvJ1T+DVbDYeMG99w2LbYNg1JiLLyA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4297
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for launching an SEV-ES guest.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

The main areas of the Qemu code that are updated to support SEV-ES are
around the SEV guest launch process and AP booting in order to support
booting multiple vCPUs.

There are no new command line switches required. Instead, the desire for
SEV-ES is presented using the SEV policy object. Bit 2 of the SEV policy
object indicates that SEV-ES is required.

The SEV launch process is updated in two ways. The first is that a the
KVM_SEV_ES_INIT ioctl is used to initialize the guest instead of the
standard KVM_SEV_INIT ioctl. The second is that before the SEV launch
measurement is calculated, the LAUNCH_UPDATE_VMSA SEV API is invoked for
each vCPU that Qemu has created. Once the LAUNCH_UPDATE_VMSA API has been
invoked, no direct changes to the guest register state can be made.

AP booting poses some interesting challenges. The INIT-SIPI-SIPI sequence
is typically used to boot the APs. However, the hypervisor is not allowed
to update the guest registers. For the APs, the reset vector must be known
in advance. An OVMF method to provide a known reset vector address exists
by providing an SEV information block, identified by UUID, near the end of
the firmware [3]. OVMF will program the jump to the actual reset vector in
this area of memory. Since the memory location is known in advance, an AP
can be created with the known reset vector address as its starting CS:IP.
The GHCB document [2] talks about how SMP booting under SEV-ES is
performed. SEV-ES also requires the use of the in-kernel irqchip support
in order to minimize the changes required to Qemu to support AP booting.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
[3] 30937f2f98c4 ("OvmfPkg: Use the SEV-ES work area for the SEV-ES AP reset vector")
    https://github.com/tianocore/edk2/commit/30937f2f98c42496f2f143fe8374ae7f7e684847
---

These patches are based on commit:
d0ed6a69d3 ("Update version for v5.1.0 release")

(I tried basing on the latest Qemu commit, but I was having build issues
that level)

A version of the tree can be found at:
https://github.com/AMDESE/qemu/tree/sev-es-v12

Changes since v3:
- Use the QemuUUID structure for GUID definitions
- Use SEV-ES policy bit definition from target/i386/sev_i386.h
- Update SMM support to a per-VM check in order to check SMM capability
  at the VM level since SEV-ES guests don't currently support SMM
- Make the CPU resettable check an arch-specific check

Changes since v2:
- Add in-kernel irqchip requirement for SEV-ES guests

Changes since v1:
- Fixed checkpatch.pl errors/warnings

Tom Lendacky (6):
  sev/i386: Add initial support for SEV-ES
  sev/i386: Require in-kernel irqchip support for SEV-ES guests
  sev/i386: Allow AP booting under SEV-ES
  sev/i386: Don't allow a system reset under an SEV-ES guest
  kvm/i386: Use a per-VM check for SMM capability
  sev/i386: Enable an SEV-ES guest based on SEV policy

 accel/kvm/kvm-all.c       |  69 ++++++++++++++++++++++++
 accel/stubs/kvm-stub.c    |   5 ++
 hw/i386/pc_sysfw.c        |  10 +++-
 include/sysemu/cpus.h     |   2 +
 include/sysemu/hw_accel.h |   5 ++
 include/sysemu/kvm.h      |  26 +++++++++
 include/sysemu/sev.h      |   3 ++
 softmmu/cpus.c            |   5 ++
 softmmu/vl.c              |   5 +-
 target/arm/kvm.c          |   5 ++
 target/i386/cpu.c         |   1 +
 target/i386/kvm.c         |  10 +++-
 target/i386/sev-stub.c    |   5 ++
 target/i386/sev.c         | 109 +++++++++++++++++++++++++++++++++++++-
 target/i386/sev_i386.h    |   1 +
 target/mips/kvm.c         |   5 ++
 target/ppc/kvm.c          |   5 ++
 target/s390x/kvm.c        |   5 ++
 18 files changed, 271 insertions(+), 5 deletions(-)
```
#### [PATCH 00/22] Introduce the TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Fri Sep 25 21:22:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11800783
Return-Path: <SRS0=qKOj=DC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB1C6112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 21:23:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 95B29221EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Sep 2020 21:23:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="CNiIGHXx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727324AbgIYVXJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Sep 2020 17:23:09 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726409AbgIYVXJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Sep 2020 17:23:09 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1A937C0613CE
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 14:23:09 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id w2so2637179qvr.19
        for <kvm@vger.kernel.org>; Fri, 25 Sep 2020 14:23:09 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=WhSHXLCkju2/puXa6k5MbwPT2DXvEVJiaCvaA6Ap7fQ=;
        b=CNiIGHXxRoK3qhcUJCN8jKMQo+/coc4H/tTeM8I73ezc7/rLXSt/+D1m8y42+foLxG
         bE12cpwtdq6987ilEd2us3mqAkilRAMKnTLzWSEbvm19WSBGLFb5nJ7z8DXbBP2WnO3Z
         dYPI5btgNrhpBUEI3YlAc/eUHn7HOZkLzJL7CZObbjwq8GVsXR1f9eGu2O/+rqtf8ltU
         LQpgE26nOV50rTCemLAR2QbDLIKu/5liJ/WuBpPLSOANK9MCCpq/JWbwnVNHT/zgYg0r
         gZWyzc5WdJ8LaEzeX7ifqT29Ur8rHhCRJu6GvST/zbQgw/ly5eq/QnY7H/koRS54xAa5
         VgJA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=WhSHXLCkju2/puXa6k5MbwPT2DXvEVJiaCvaA6Ap7fQ=;
        b=EZr2RZZUaUewJQkgmKdmDiGjYvExUJOA/7oInIB5ylbOeDA/zptGOfjHLhhyOWa2hA
         okAvg2urEu/XvBkk6gdpCDaXROFEQeAZMMUaPk3+TPFRuY02HfsK2DWTYBy2mVW1jJZk
         Gft2g1FaUthli/ITmogGWyUxRCbP2eU+XEjZNkwbtWn17MgvNpnlfW0OCs6BjFWNG4aT
         vBuYddgiPy2qPvStV5iQnlXkemR2QQO9+13Ja75LLAwoxeqRFmyP3Wt/IFlOyDqnjDlR
         WoygfbuDI3tUlzJjhq9EFcBKcfx7eErSMDIL/e9lhVakNhXWJMJ3nrcJQGXa9Cc9YthE
         iqmg==
X-Gm-Message-State: AOAM533W/cQdJq432ctqwu5/jRs0bqbPTvX1KDb+6m5wPlo7YXEKA/UN
        Bbc0+DoIeBGXe4th2bvUprbmSMYf2evb
X-Google-Smtp-Source: 
 ABdhPJzqKnFLiB2rs8BKpZdKjFq7yB7IURYL2VHUH6zjuOMgmoioiBcLZbd/+9pDLZAoq1GVwLUjuzrdAIOr
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:ad4:5743:: with SMTP id
 q3mr681860qvx.6.1601068988189; Fri, 25 Sep 2020 14:23:08 -0700 (PDT)
Date: Fri, 25 Sep 2020 14:22:40 -0700
Message-Id: <20200925212302.3979661-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.709.gb0816b6eb0-goog
Subject: [PATCH 00/22] Introduce the TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cannon Matthews <cannonmatthews@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Over the years, the needs for KVM's x86 MMU have grown from running small
guests to live migrating multi-terabyte VMs with hundreds of vCPUs. Where
we previously depended on shadow paging to run all guests, we now have
two dimensional paging (TDP). This patch set introduces a new
implementation of much of the KVM MMU, optimized for running guests with
TDP. We have re-implemented many of the MMU functions to take advantage of
the relative simplicity of TDP and eliminate the need for an rmap.
Building on this simplified implementation, a future patch set will change
the synchronization model for this "TDP MMU" to enable more parallelism
than the monolithic MMU lock. A TDP MMU is currently in use at Google
and has given us the performance necessary to live migrate our 416 vCPU,
12TiB m2-ultramem-416 VMs.

This work was motivated by the need to handle page faults in parallel for
very large VMs. When VMs have hundreds of vCPUs and terabytes of memory,
KVM's MMU lock suffers extreme contention, resulting in soft-lockups and
long latency on guest page faults. This contention can be easily seen
running the KVM selftests demand_paging_test with a couple hundred vCPUs.
Over a 1 second profile of the demand_paging_test, with 416 vCPUs and 4G
per vCPU, 98% of the time was spent waiting for the MMU lock. At Google,
the TDP MMU reduced the test duration by 89% and the execution was
dominated by get_user_pages and the user fault FD ioctl instead of the
MMU lock.

This series is the first of two. In this series we add a basic
implementation of the TDP MMU. In the next series we will improve the
performance of the TDP MMU and allow it to execute MMU operations
in parallel.

The overall purpose of the KVM MMU is to program paging structures
(CR3/EPT/NPT) to encode the mapping of guest addresses to host physical
addresses (HPA), and to provide utilities for other KVM features, for
example dirty logging. The definition of the L1 guest physical address
(GPA) to HPA mapping comes in two parts: KVM's memslots map GPA to HVA,
and the kernel MM/x86 host page tables map HVA -> HPA. Without TDP, the
MMU must program the x86 page tables to encode the full translation of
guest virtual addresses (GVA) to HPA. This requires "shadowing" the
guest's page tables to create a composite x86 paging structure. This
solution is complicated, requires separate paging structures for each
guest CR3, and requires emulating guest page table changes. The TDP case
is much simpler. In this case, KVM lets the guest control CR3 and programs
the EPT/NPT paging structures with the GPA -> HPA mapping. The guest has
no way to change this mapping and only one version of the paging structure
is needed per L1 paging mode. In this case the paging mode is some
combination of the number of levels in the paging structure, the address
space (normal execution or system management mode, on x86), and other
attributes. Most VMs only ever use 1 paging mode and so only ever need one
TDP structure.

This series implements a "TDP MMU" through alternative implementations of
MMU functions for running L1 guests with TDP. The TDP MMU falls back to
the existing shadow paging implementation when TDP is not available, and
interoperates with the existing shadow paging implementation for nesting.
The use of the TDP MMU can be controlled by a module parameter which is
snapshot on VM creation and follows the life of the VM. This snapshot
is used in many functions to decide whether or not to use TDP MMU handlers
for a given operation.

This series can also be viewed in Gerrit here:
https://linux-review.googlesource.com/c/virt/kvm/kvm/+/2538
(Thanks to Dmitry Vyukov <dvyukov@google.com> for setting up the
Gerrit instance)

Ben Gardon (22):
  kvm: mmu: Separate making SPTEs from set_spte
  kvm: mmu: Introduce tdp_iter
  kvm: mmu: Init / Uninit the TDP MMU
  kvm: mmu: Allocate and free TDP MMU roots
  kvm: mmu: Add functions to handle changed TDP SPTEs
  kvm: mmu: Make address space ID a property of memslots
  kvm: mmu: Support zapping SPTEs in the TDP MMU
  kvm: mmu: Separate making non-leaf sptes from link_shadow_page
  kvm: mmu: Remove disallowed_hugepage_adjust shadow_walk_iterator arg
  kvm: mmu: Add TDP MMU PF handler
  kvm: mmu: Factor out allocating a new tdp_mmu_page
  kvm: mmu: Allocate struct kvm_mmu_pages for all pages in TDP MMU
  kvm: mmu: Support invalidate range MMU notifier for TDP MMU
  kvm: mmu: Add access tracking for tdp_mmu
  kvm: mmu: Support changed pte notifier in tdp MMU
  kvm: mmu: Add dirty logging handler for changed sptes
  kvm: mmu: Support dirty logging for the TDP MMU
  kvm: mmu: Support disabling dirty logging for the tdp MMU
  kvm: mmu: Support write protection for nesting in tdp MMU
  kvm: mmu: NX largepage recovery for TDP MMU
  kvm: mmu: Support MMIO in the TDP MMU
  kvm: mmu: Don't clear write flooding count for direct roots

 arch/x86/include/asm/kvm_host.h |   17 +
 arch/x86/kvm/Makefile           |    3 +-
 arch/x86/kvm/mmu/mmu.c          |  437 ++++++----
 arch/x86/kvm/mmu/mmu_internal.h |   98 +++
 arch/x86/kvm/mmu/paging_tmpl.h  |    3 +-
 arch/x86/kvm/mmu/tdp_iter.c     |  198 +++++
 arch/x86/kvm/mmu/tdp_iter.h     |   55 ++
 arch/x86/kvm/mmu/tdp_mmu.c      | 1315 +++++++++++++++++++++++++++++++
 arch/x86/kvm/mmu/tdp_mmu.h      |   52 ++
 include/linux/kvm_host.h        |    2 +
 virt/kvm/kvm_main.c             |    7 +-
 11 files changed, 2022 insertions(+), 165 deletions(-)
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.c
 create mode 100644 arch/x86/kvm/mmu/tdp_iter.h
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.c
 create mode 100644 arch/x86/kvm/mmu/tdp_mmu.h
```
