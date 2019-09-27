

#### [RFC PATCH v4 0/6] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Thu Sep 26 11:42:07 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11162615
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E65C1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 11:42:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 06FFF222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 11:42:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726300AbfIZLmY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 07:42:24 -0400
Received: from foss.arm.com ([217.140.110.172]:47040 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725784AbfIZLmY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 07:42:24 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 97FA5142F;
        Thu, 26 Sep 2019 04:42:23 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 0C9173F67D;
        Thu, 26 Sep 2019 04:42:18 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com,
        Will.Deacon@arm.com, suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v4 0/6] Enable ptp_kvm for arm64
Date: Thu, 26 Sep 2019 19:42:07 +0800
Message-Id: <20190926114212.5322-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. This patch enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:
from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.
from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.
from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=125ea89e4a21e2fc5235410f966a996a1a7148bf
[2]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06
[3]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681

Jianyong Wu (5):
  psci: Export psci_ops.conduit symbol as modules will use it.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

 drivers/clocksource/arm_arch_timer.c | 28 +++++++++
 drivers/firmware/psci/psci.c         |  6 ++
 drivers/ptp/Kconfig                  |  2 +-
 drivers/ptp/Makefile                 |  1 +
 drivers/ptp/{ptp_kvm.c => kvm_ptp.c} | 79 +++++++------------------
 drivers/ptp/ptp_kvm_arm64.c          | 73 +++++++++++++++++++++++
 drivers/ptp/ptp_kvm_x86.c            | 87 ++++++++++++++++++++++++++++
 include/asm-generic/ptp_kvm.h        | 12 ++++
 include/linux/arm-smccc.h            | 14 ++++-
 include/linux/psci.h                 |  1 +
 include/uapi/linux/kvm.h             |  1 +
 virt/kvm/arm/arm.c                   |  1 +
 virt/kvm/arm/psci.c                  | 18 ++++++
 13 files changed, 262 insertions(+), 61 deletions(-)
 rename drivers/ptp/{ptp_kvm.c => kvm_ptp.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
```
#### [RFC PATCH 0/1] KVM: VMX: Always sync CR3 to VMCS in
##### From: Reto Buerki <reet@codelabs.ch>

```c
From patchwork Thu Sep 26 14:05:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Reto Buerki <reet@codelabs.ch>
X-Patchwork-Id: 11162821
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 80DC117EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 14:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 699AD222C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 14:15:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727165AbfIZOP0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 10:15:26 -0400
Received: from mail.codelabs.ch ([109.202.192.35]:57708 "EHLO
 mail.codelabs.ch"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726975AbfIZOP0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 10:15:26 -0400
X-Greylist: delayed 571 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 26 Sep 2019 10:15:24 EDT
Received: from localhost (localhost [127.0.0.1])
        by mail.codelabs.ch (Postfix) with ESMTP id 3E7C9A0166;
        Thu, 26 Sep 2019 16:05:53 +0200 (CEST)
Received: from mail.codelabs.ch ([127.0.0.1])
        by localhost (fenrir.codelabs.ch [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id B34XwJeBYrfE; Thu, 26 Sep 2019 16:05:50 +0200 (CEST)
Received: from skyhawk.codelabs.ch (unknown [192.168.10.191])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.codelabs.ch (Postfix) with ESMTPSA id 2771DA0125;
        Thu, 26 Sep 2019 16:05:50 +0200 (CEST)
From: Reto Buerki <reet@codelabs.ch>
To: kvm@vger.kernel.org
Subject: [RFC PATCH 0/1] KVM: VMX: Always sync CR3 to VMCS in
 nested_vmx_load_cr3
Date: Thu, 26 Sep 2019 16:05:40 +0200
Message-Id: <20190926140541.15453-1-reet@codelabs.ch>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Muen [1] is an Open Source separation kernel (SK) for x86/64. It is
written in SPARK/Ada and uses VMX non-root mode to isolate both its
'native' (IA32-e paging) and VM guests (EPT).

Native guests are written in SPARK/Ada as well. They run directly on the
vCPU with no surrounding OS, page tables are compile-time static, guest
CR3 is initially setup in the associated VMCS by the SK and never
changes.

We are trying to use nested KVM/QEMU for faster deployment and testing
of Muen-based systems but encountered a problem with how KVM handles L2
guest CR3 in our setup. As soon as guests start to idle executing HLT,
things go sideways (#GP, unexpected page faults in native subjects,
triple faults in VMs).

We assume the failure is related to the "HLT Exiting" control in
Processor-Based VM-Execution Controls, as Muen has this flag disabled
due to the static, round-robin nature of its scheduler. This might be
uncommon.

We instrumented the SK to check if a known CR3 value changes during
runtime, which produced the following output. CR3 of guests 8 and 9 are
initially zero because these are VM guests with EPT.

Booting Muen kernel v0.9.1-262-g71ffcad4b-UNCLEAN (GNAT Community 2019 (20190517-83))
[..snip..]
PML4 address of subject 16#0000#: 16#00000000018c9000#
PML4 address of subject 16#0001#: 16#000000000189f000#
PML4 address of subject 16#0002#: 16#0000000001834000#
PML4 address of subject 16#0003#: 16#000000000183d000#
PML4 address of subject 16#0005#: 16#0000000001630000#
PML4 address of subject 16#0004#: 16#0000000001846000#
PML4 address of subject 16#0007#: 16#000000000186f000#
PML4 address of subject 16#0006#: 16#0000000001818000#
PML4 address of subject 16#0008#: 16#0000000000000000#
PML4 address of subject 16#0009#: 16#0000000000000000#
[..snip..]
ERROR CR3 of subject 1 changed: 16#0000000010ff9000# exit 16#0034#
ERROR Halting CPU

The CR3 value of guest 1 changed from 16#000000000189f000# to
16#0000000010ff9000#, which is the CR3 value of a VM guest.

A second run shows:
ERROR CR3 of subject 1 changed: 16#000000000183d000# exit 16#0034#,
which is the CR3 value of guest 3.

The problem does not only show for native guests, but also CR3 values of
VM guests with EPT get mixed up.

Tested KVM version is fd3edd4a9066.

A Muen system image to reproduce the problem is provided:

$ wget https://www.codelabs.ch/~reet/files/muen.iso.tar.xz
$ tar xfvJ muen.iso.tar.xz
$ qemu-system-x86_64 -cdrom muen.iso \
  -serial file:serial.out \
  -cpu host,+invtsc \
  --enable-kvm \
  -m 5120 \
  -smp cores=2,threads=2,sockets=1

This patch fixes the issue for Muen. I'm aware that this might not be
the proper fix, please advise how to update it if the problem is
reproducible.

[1] - https://muen.sk

Reto Buerki (1):
  KVM: VMX: Always sync CR3 to VMCS in nested_vmx_load_cr3

 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)
```
#### [PATCH 0/3] KVM: MMU: fix nested guest live migration with PML
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Sep 26 17:18:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11163049
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65ACE14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 17:18:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 43C59222C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 17:18:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="KqkKqLFn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727677AbfIZRSc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 13:18:32 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:36925 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726029AbfIZRSb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 13:18:31 -0400
Received: by mail-wr1-f68.google.com with SMTP id i1so3676001wro.4;
        Thu, 26 Sep 2019 10:18:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=G8ATWpvsPeQhyAU95P46GVmGRpo0pkchWBreGDYzCWE=;
        b=KqkKqLFnIu9dqQ5CM5kJFw3B/WnvfuWZO2qxHridDqPjzx5ATenOPpny39CvD294pE
         THmQ8q0FvnlmLc6fyCoZFF06RK+z9TUIvlDUlEVNzo+9wcFWmiB/m1axYi4otWr/WvW5
         lGhXov7yRw+RTBnT/lnOCmJVEEFrssn7TzLWiV/efE/G42MsHMStGbvQYkFb2hHSqkPM
         tm/MysLFkpLP1YfcNCyzSJFRZM77b01U0KFk63v0Z++nGCr0yfT4Wk05WQKaHuTWiCyu
         Jg3mqVVKb0pX0RlWsVaYTdmjcnFy7ee/wqA0A45X7ODJtHir/gCkdVvVA0q0Hag018OC
         /SPw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=G8ATWpvsPeQhyAU95P46GVmGRpo0pkchWBreGDYzCWE=;
        b=F6npoADVEQlMgzAir25gh+XTQ2Kta5HTtYmD2UcA7lIfoy38HzH1pkkqbKOUcLJHMg
         NyTBONeIZ0s0VnCuMNPacuf9c6FMMe6yGe3ltHFESvs/wzW3jz88CJL813n6ZimPOqQe
         hCAawew3anDbqa9tXUiuGvXViLwRvZoTazPCNyrfBd79sk03TVaCv3xPRc6AOo8dmA6S
         hDIdW5FiXw6nyGA2niWwNLVYkunWWOhcDb8yUJkxK+BRfY575RtQcTKlYuIBc13PMWxj
         0qNu1qrmOK+ZDZAeHJw5cojBnIdnWGxn7PUI+6ja18iVUShNk8rcBuWIu6uyL2RTx+TZ
         IVkA==
X-Gm-Message-State: APjAAAXPItwEvKB0hOv9TkZlt0AA0Zk4gfR+I3lWiwBgFTU+AQ5vAAl2
        sC5FtJOFOT3grDZCCZPtIUVFr0Z1
X-Google-Smtp-Source: 
 APXvYqzmD5sjDJT/FzC/PxkKE9HLYAtS9TV5ircrgPv0vUA1Kjo6epfRGl/PyrlV7UFo+q17PiktvQ==
X-Received: by 2002:a5d:6ace:: with SMTP id u14mr4147987wrw.385.1569518309013;
        Thu, 26 Sep 2019 10:18:29 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 v4sm4792782wrg.56.2019.09.26.10.18.28
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 26 Sep 2019 10:18:28 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH 0/3] KVM: MMU: fix nested guest live migration with PML
Date: Thu, 26 Sep 2019 19:18:23 +0200
Message-Id: <1569518306-46567-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shadow paging is fundamentally incompatible with the page-modification
log, because the GPAs in the log come from the wrong memory map.
In particular, for the EPT page-modification log, the GPAs in the log come
from L2 rather than L1.  (If there was a non-EPT page-modification log,
we couldn't use it for shadow paging because it would log GVAs rather
than GPAs).

Therefore, we need to rely on write protection to record dirty pages.
This has the side effect of bypassing PML, since writes now result in an
EPT violation vmexit.

This turns out to be a surprisingly small patch---the testcase is what's
guilty of the scary diffstat.  But that is because the KVM MMU code is
absurdly clever, so a very close review is appreciated.

Paolo

Paolo Bonzini (3):
  KVM: x86: assign two bits to track SPTE kinds
  KVM: x86: fix nested guest live migration with PML
  selftests: kvm: add test for dirty logging inside nested guests

 arch/x86/include/asm/kvm_host.h                    |   7 -
 arch/x86/kvm/mmu.c                                 |  58 ++++--
 tools/testing/selftests/kvm/Makefile               |   1 +
 .../selftests/kvm/include/x86_64/processor.h       |   3 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |  14 ++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   2 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   3 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 201 ++++++++++++++++++++-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c      | 156 ++++++++++++++++
 9 files changed, 424 insertions(+), 21 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_dirty_log_test.c
```
#### [PATCH 0/2] KVM: nVMX: Bug fix for consuming stale vmcs02.GUEST_CR3
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Sep 26 21:43:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11163383
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6A8376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 21:43:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B53232245C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 21:43:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726133AbfIZVnE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 17:43:04 -0400
Received: from mga07.intel.com ([134.134.136.100]:8270 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725943AbfIZVnE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 17:43:04 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Sep 2019 14:43:03 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,553,1559545200";
   d="scan'208";a="192958527"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga003.jf.intel.com with ESMTP; 26 Sep 2019 14:43:03 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reto Buerki <reet@codelabs.ch>
Subject: [PATCH 0/2] KVM: nVMX: Bug fix for consuming stale vmcs02.GUEST_CR3
Date: Thu, 26 Sep 2019 14:43:00 -0700
Message-Id: <20190926214302.21990-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reto Buerki reported a failure in a nested VMM when running with HLT
interception disabled in L1.  When putting L2 into HLT, KVM never actually
enters L2 and instead cancels the nested run and pretends that VM-Enter to
L2 completed and then exited on HLT (which KVM intercepted).  Because KVM
never actually runs L2, KVM skips the pending MMU update for L2 and so
leaves a stale value in vmcs02.GUEST_CR3.  If the next wake event for L2
triggers a nested VM-Exit, KVM will refresh vmcs12->guest_cr3 from
vmcs02.GUEST_CR3 and consume the stale value.

Fix the issue by unconditionally writing vmcs02.GUEST_CR3 during nested
VM-Enter instead of deferring the update to vmx_set_cr3(), and skip the
update of GUEST_CR3 in vmx_set_cr3() when running L2.  I.e. make the
nested code fully responsible for vmcs02.GUEST_CR3.

I really wanted to go with a different fix of handling this as a one-off
case in the HLT flow (in nested_vmx_run()), and then following that up
with a cleanup of VMX's CR3 handling, e.g. to do proper dirty tracking
instead of having the nested code do manual VMREADs and VMWRITEs.  I even
went so far as to hide vcpu->arch.cr3 (put CR3 in vcpu->arch.regs), but
things went south when I started working through the dirty tracking logic.

Because EPT can be enabled *without* unrestricted guest, enabling EPT
doesn't always mean GUEST_CR3 really is the guest CR3 (unlike SVM's NPT).
And because the unrestricted guest handling of GUEST_CR3 is dependent on
whether the guest has paging enabled, VMX can't even do a clean handoff
based on unrestricted guest.  In a nutshell, dynamically handling the
transitions of GUEST_CR3 ownership in VMX is a nightmare, so fixing this
purely within the context of nested VMX turned out to be the cleanest fix.

Sean Christopherson (2):
  KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested VM-Enter
  KVM: VMX: Skip GUEST_CR3 VMREAD+VMWRITE if the VMCS is up-to-date

 arch/x86/kvm/vmx/nested.c |  8 ++++++++
 arch/x86/kvm/vmx/vmx.c    | 15 ++++++++++-----
 2 files changed, 18 insertions(+), 5 deletions(-)
```
