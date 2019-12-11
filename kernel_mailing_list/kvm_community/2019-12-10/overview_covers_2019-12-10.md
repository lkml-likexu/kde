

#### [RFC PATCH v9 0/8] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Tue Dec 10 03:40:18 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11281259
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27B80138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 03:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 064A320692
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 03:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726771AbfLJDkk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Dec 2019 22:40:40 -0500
Received: from foss.arm.com ([217.140.110.172]:55806 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726623AbfLJDkk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Dec 2019 22:40:40 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 592601FB;
        Mon,  9 Dec 2019 19:40:39 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 27C973F52E;
        Mon,  9 Dec 2019 19:40:33 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v9 0/8] Enable ptp_kvm for arm64
Date: Tue, 10 Dec 2019 11:40:18 +0800
Message-Id: <20191210034026.45229-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. Here, we enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:

from v8 to v9:
	(1) move ptp_kvm.h to driver/ptp/
	(2) replace license declaration of ptp_kvm.h the same with other
header files in the same directory.

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v6 to v7:
        (1) include the omitted clocksource_id.h in last version.
        (2) reorder the header file in patch.
        (3) refine some words in commit message to make it more impersonal.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
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
[4]https://git.kernel.org/pub/scm/linux/kernel/git/arm64/linux.git/
commit/?h=for-next/smccc-conduit-cleanup&id=6b7fe77c334ae59fed9500140e08f4f896b36871

Jianyong Wu (6):
  psci: let arm_smccc_1_1_invoke available by modules
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

Mark Rutland (1):
  arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

 drivers/clocksource/arm_arch_timer.c        | 24 ++++++
 drivers/firmware/psci/psci.c                | 16 ++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm64.c                 | 53 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 77 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 30 ++++++-
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 13 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/psci.c                         | 22 ++++++
 17 files changed, 294 insertions(+), 66 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH net-next v2 0/6] vsock: add local transport support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Tue Dec 10 10:43:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11281845
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC266138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 10:44:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 99A0B207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 10:44:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Dhc96tRA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727222AbfLJKoA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 05:44:00 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:57985 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727411AbfLJKnU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Dec 2019 05:43:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575974599;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=mP35JmqQ9E99xN9+azImIkT0EtvsAAz/WVB37DGVDWA=;
        b=Dhc96tRAENHWGyzHJMOlFIobmwvMom3CQgEXMIAUfzSTAouBPLHnMKBiE0kixD/yglcZmL
        yvyxmh5iqy2K+LOmo6YvIQKVRsVKW7jgz5vwPUtL3N6764G4gzBMTM0wlzsWo17RHjR5Dm
        PWPH+xJfIGguww88hVog/s7VUbVPBFM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-144-bddPvOfPNauR0dU7DHbVGQ-1; Tue, 10 Dec 2019 05:43:16 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 11167802B7D;
        Tue, 10 Dec 2019 10:43:13 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-168.ams2.redhat.com
 [10.36.117.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1F18F60568;
        Tue, 10 Dec 2019 10:43:07 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org, davem@davemloft.net
Cc: Dexuan Cui <decui@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Stefano Garzarella <sgarzare@redhat.com>
Subject: [PATCH net-next v2 0/6] vsock: add local transport support
Date: Tue, 10 Dec 2019 11:43:01 +0100
Message-Id: <20191210104307.89346-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: bddPvOfPNauR0dU7DHbVGQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
 - style fixes [Dave]
 - removed RCU sync and changed 'the_vsock_loopback' in a global
   static variable [Stefan]
 - use G2H transport when local transport is not loaded and remote cid
   is VMADDR_CID_LOCAL [Stefan]
 - rebased on net-next

v1: https://patchwork.kernel.org/cover/11251735/

This series introduces a new transport (vsock_loopback) to handle
local communication.
This could be useful to test vsock core itself and to allow developers
to test their applications without launching a VM.

Before this series, vmci and virtio transports allowed this behavior,
but only in the guest.
We are moving the loopback handling in a new transport, because it
might be useful to provide this feature also in the host or when
no H2G/G2H transports (hyperv, virtio, vmci) are loaded.

The user can use the loopback with the new VMADDR_CID_LOCAL (that
replaces VMADDR_CID_RESERVED) in any condition.
Otherwise, if the G2H transport is loaded, it can also use the guest
local CID as previously supported by vmci and virtio transports.
If G2H transport is not loaded, the user can also use VMADDR_CID_HOST
for local communication.

Patch 1 is a cleanup to build virtio_transport_common without virtio
Patch 2 adds the new VMADDR_CID_LOCAL, replacing VMADDR_CID_RESERVED
Patch 3 adds a new feature flag to register a loopback transport
Patch 4 adds the new vsock_loopback transport based on the loopback
        implementation of virtio_transport
Patch 5 implements the logic to use the local transport for loopback
        communication
Patch 6 removes the loopback from virtio_transport

Stefano Garzarella (6):
  vsock/virtio_transport_common: remove unused virtio header includes
  vsock: add VMADDR_CID_LOCAL definition
  vsock: add local transport support in the vsock core
  vsock: add vsock_loopback transport
  vsock: use local transport when it is loaded
  vsock/virtio: remove loopback handling

 MAINTAINERS                             |   1 +
 include/net/af_vsock.h                  |   2 +
 include/uapi/linux/vm_sockets.h         |   8 +-
 net/vmw_vsock/Kconfig                   |  12 ++
 net/vmw_vsock/Makefile                  |   1 +
 net/vmw_vsock/af_vsock.c                |  45 +++++-
 net/vmw_vsock/virtio_transport.c        |  61 +-------
 net/vmw_vsock/virtio_transport_common.c |   3 -
 net/vmw_vsock/vmci_transport.c          |   2 +-
 net/vmw_vsock/vsock_loopback.c          | 180 ++++++++++++++++++++++++
 10 files changed, 243 insertions(+), 72 deletions(-)
 create mode 100644 net/vmw_vsock/vsock_loopback.c
```
#### [PATCH 0/4] KVM: x86: Add checks on host-reserved cr4 bits
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Dec 10 22:44:12 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11283373
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FA31112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 22:44:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3DFF820828
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 22:44:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728828AbfLJWoV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 17:44:21 -0500
Received: from mga09.intel.com ([134.134.136.24]:9123 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727170AbfLJWoT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 17:44:19 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Dec 2019 14:44:18 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,301,1571727600";
   d="scan'208";a="413279324"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 10 Dec 2019 14:44:18 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Jun Nakajima <jun.nakajima@intel.com>
Subject: [PATCH 0/4] KVM: x86: Add checks on host-reserved cr4 bits
Date: Tue, 10 Dec 2019 14:44:12 -0800
Message-Id: <20191210224416.10757-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM currently doesn't incorporate the platform's capabilities in its cr4
reserved bit checks and instead checks only whether KVM is aware of the
feature in general and whether or not userspace has advertised the feature
to the guest.

Lack of checking allows userspace/guest to set unsupported bits in cr4.
For the most part, setting unsupported bits will simply cause VM-Enter to
fail.  The one existing exception is OSXSAVE, which is conditioned on host
support as checking only guest_cpuid_has() would result in KVM attempting
XSAVE, leading to faults and WARNs.

57-bit virtual addressing has introduced another case where setting an
unsupported bit (cr4.LA57) can induce a fault in the host.  In the LA57
case, userspace can set the guest's cr4.LA57 by advertising LA57 support
via CPUID and abuse the bogus cr4.LA57 to effectively bypass KVM's
non-canonical address check, ultimately causing a #GP when VMX writes
the guest's bogus address to MSR_KERNEL_GS_BASE during VM-Enter.

Given that the best case scenario is a failed VM-Enter, there's no sane
reason to allow setting unsupported bits in cr4.  Fix the LA57 bug by not
allowing userspace or the guest to set cr4 bits that are not supported
by the platform.

Sean Christopherson (4):
  KVM: x86: Don't let userspace set host-reserved cr4 bits
  KVM: x86: Ensure all logical CPUs have consistent reserved cr4 bits
  KVM: x86: Drop special XSAVE handling from guest_cpuid_has()
  KVM: x86: Add macro to ensure reserved cr4 bits checks stay in sync

 arch/x86/kvm/cpuid.h   |  4 ---
 arch/x86/kvm/svm.c     |  1 +
 arch/x86/kvm/vmx/vmx.c |  1 +
 arch/x86/kvm/x86.c     | 65 +++++++++++++++++++++++++++++-------------
 4 files changed, 47 insertions(+), 24 deletions(-)
```
