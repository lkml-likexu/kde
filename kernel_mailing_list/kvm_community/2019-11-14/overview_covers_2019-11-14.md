

#### [PATCH v5 0/8] KVM: nVMX: Add full nested support for "load
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Thu Nov 14 00:17:14 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11242893
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2622D1393
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 00:17:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AFC66206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 00:17:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Txi9mR2p"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726473AbfKNARe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 19:17:34 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:56414 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726195AbfKNARe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Nov 2019 19:17:34 -0500
Received: by mail-pg1-f201.google.com with SMTP id 11so3112637pgm.23
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 16:17:32 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=GTIC95OO8wyHkXq89RvQsalRu9vquP6LSLQDB4RTONs=;
        b=Txi9mR2pTU0pZCkosjcm1DVX9yWJYOo+4X64OW5Gm+J6WOPI1Or+0giA7VVJQ3ERUK
         7wM2OoHOR+d4B1/r+DLzWAXy9/veatXdlJXVJ0El8qSGCNxGQZTmwKl6948XUrnZGla8
         MQpOMbT0M7a8GI48LmfCA2qm4HZjhE2eYkRwWXye9Qoor413Vw6O7wZKXB7YYlTWbKtz
         IkRmy+R9mJAAPjlEEzDO9MiFD6YHmDcQ/f3RWZnCGtlc5G5jv/bv6b0hmlzo9X2j/lW1
         +gJIQYRgui7iiszSbCJtZ1GgWjnr0mBhEgwyNUMG8UHnBcg8KEjwOzYHyiN0WPhOYAc3
         lt4g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=GTIC95OO8wyHkXq89RvQsalRu9vquP6LSLQDB4RTONs=;
        b=lPzUzex6ZXN5mo1KqnALHnfdNQYE+4pV23DXJMhnafIBle/ephiOv7HVtytJUSns4O
         Z492s/FvyKreyDmzB6kgQbUMkG75/v4MsUg7DzYmRKCUWdx2G6RnqSj+y8pG4OTzRxDl
         j+PAS/iyIj3YhsTXehz0USP14LyS+6gqR8LwmZALD1OntH69W1aUREPxsxxi3rDIY2Bk
         MxbL6NY4goZ/D6mi48IEBzkz5q81pDgfhys6n56Wf3L/vcif/mt3lkJtARDopkj+j9j+
         hFJl0T8YPjtXdWCE5+ORRVEjDz5DYWGkpPC7EOlqn4hXbyr7hPb7NC2e+M6vNWO3/NhY
         jyxQ==
X-Gm-Message-State: APjAAAVQRLi1SgiHGceDpBpLWhFEhuIv/ttlkRsLUD1n8GkfkUEckb2K
        jNbk8uUuxsE4CHu8HbNqsYuo6VJZxEFB64XjCyTzkffV7eEDVDGcuHIsg+V3D1lZBlWkYUEOOer
        onPlQ66foAQ1M4V3hx5WD5sIwsox6H6otqa2CnxTsmB4ozy7bYZy1RLcXLA==
X-Google-Smtp-Source: 
 APXvYqyYaQFXSRef/kiz4OUzE0JH+kQxyotZdTTl1c8PG92NUXU/fM8iRZ1aADSA3xufuFYRWe5GxV4eMLk=
X-Received: by 2002:a63:b20f:: with SMTP id x15mr6707598pge.65.1573690651517;
 Wed, 13 Nov 2019 16:17:31 -0800 (PST)
Date: Wed, 13 Nov 2019 16:17:14 -0800
Message-Id: <20191114001722.173836-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [PATCH v5 0/8] KVM: nVMX: Add full nested support for "load
 IA32_PERF_GLOBAL_CTRL" VM-{Entry,Exit} control
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, "
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= " <rkrcmar@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[v1] https://lore.kernel.org/r/20190828234134.132704-1-oupton@google.com
[v2] https://lore.kernel.org/r/20190903213044.168494-1-oupton@google.com
[v3] https://lore.kernel.org/r/20190903215801.183193-1-oupton@google.com
[v4] https://lore.kernel.org/r/20190906210313.128316-1-oupton@google.com

v1 => v2:
 - Add Krish's Co-developed-by and Signed-off-by tags.
 - Fix minor nit to kvm-unit-tests to use 'host' local variable
   throughout test_load_pgc()
 - Teach guest_state_test_main() to check guest state from within nested
   VM
 - Update proposed tests to use guest/host state checks, wherein the
   value is checked from MSR_CORE_PERF_GLOBAL_CTRL.
 - Changelog line wrapping

v2 => v3:
 - Remove the value unchanged condition from
   kvm_is_valid_perf_global_ctrl
 - Add line to changelog for patch 3/8

v3 => v4:
 - Allow tests to set the guest func multiple times
 - Style fixes throughout kvm-unit-tests patches, per Krish's review

v4 => v5:
 - Rebased kernel and kvm-unit-tests patches
 - Reordered and reworked patches to now WARN on a failed
   kvm_set_msr()
 - Dropped patch to alow resetting guest in kvm-unit-tests, as the
   functionality is no longer needed.

This patchset exposes the "load IA32_PERF_GLOBAL_CTRL" to guests for nested
VM-entry and VM-exit. There already was some existing code that supported
the VM-exit ctrl, though it had an issue and was not exposed to the guest
anyway. These patches are based on the original set that Krish Sadhukhan
sent out earlier this year.

Oliver Upton (6):
  KVM: nVMX: Expose load IA32_PERF_GLOBAL_CTRL VM-{Entry,Exit} control
  KVM: nVMX: Load GUEST_IA32_PERF_GLOBAL_CTRL MSR on VM-Entry
  KVM: nVMX: Use kvm_set_msr to load IA32_PERF_GLOBAL_CTRL on VM-Exit
  KVM: nVMX: Check HOST_IA32_PERF_GLOBAL_CTRL on VM-Entry
  KVM: nVMX: Check GUEST_IA32_PERF_GLOBAL_CTRL on VM-Entry
  KVM: VMX: Add helper to check reserved bits in IA32_PERF_GLOBAL_CTRL

 arch/x86/kvm/pmu.h           |  6 ++++++
 arch/x86/kvm/vmx/nested.c    | 51 +++++++++++++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/nested.h    |  1 +
 arch/x86/kvm/vmx/pmu_intel.c |  5 ++++-
```
#### [PATCH net-next v2 00/15] vsock: add multi-transports support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Nov 14 09:57:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11243295
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41E2E913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 09:58:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1956C206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 09:58:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZVFrWIse"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726812AbfKNJ6H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 04:58:07 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51136 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726632AbfKNJ6G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 04:58:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573725484;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=i+ghB/wyVNL5oaMuN4UVb/xQcoBfZlXxJT0AidebzUE=;
        b=ZVFrWIseHa6oG8+5r15kV1alVIkd8roTf6ggh41eqjWnqLhA2+qPWlQZVWCvQoDC/zMZ3G
        b6T7QnDzlKGGdpM0Mlsu7ZD/kAteJ8AAsF7uT/Yd3Lhlp+/+5Q+3X28S4KMgz2GRX2EERI
        Hxu4jGZU8E5Gpicz0xXDrGMFeqLuks0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-400-hkAcOLRiNvW9sTlvdhU7Sw-1; Thu, 14 Nov 2019 04:58:01 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3AB44800EBE;
        Thu, 14 Nov 2019 09:57:59 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-81.ams2.redhat.com
 [10.36.117.81])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1E6E0A7F1;
        Thu, 14 Nov 2019 09:57:50 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: Stephen Hemminger <sthemmin@microsoft.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Jorgen Hansen <jhansen@vmware.com>,
        Jason Wang <jasowang@redhat.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        linux-kernel@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Sasha Levin <sashal@kernel.org>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Dexuan Cui <decui@microsoft.com>, linux-hyperv@vger.kernel.org
Subject: [PATCH net-next v2 00/15] vsock: add multi-transports support
Date: Thu, 14 Nov 2019 10:57:35 +0100
Message-Id: <20191114095750.59106-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: hkAcOLRiNvW9sTlvdhU7Sw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Most of the patches are reviewed by Dexuan, Stefan, and Jorgen.
The following patches need reviews:
- [11/15] vsock: add multi-transports support
- [12/15] vsock/vmci: register vmci_transport only when VMCI guest/host
          are active
- [15/15] vhost/vsock: refuse CID assigned to the guest->host transport

RFC: https://patchwork.ozlabs.org/cover/1168442/
v1: https://patchwork.ozlabs.org/cover/1181986/

v1 -> v2:
- Patch 11:
    + vmci_transport: sent reset when vsock_assign_transport() fails
      [Jorgen]
    + fixed loopback in the guests, checking if the remote_addr is the
      same of transport_g2h->get_local_cid()
    + virtio_transport_common: updated space available while creating
      the new child socket during a connection request
- Patch 12:
    + removed 'features' variable in vmci_transport_init() [Stefan]
    + added a flag to register only once the host [Jorgen]
- Added patch 15 to refuse CID assigned to the guest->host transport in
  the vhost_transport

This series adds the multi-transports support to vsock, following
this proposal: https://www.spinics.net/lists/netdev/msg575792.html

With the multi-transports support, we can use VSOCK with nested VMs
(using also different hypervisors) loading both guest->host and
host->guest transports at the same time.
Before this series, vmci_transport supported this behavior but only
using VMware hypervisor on L0, L1, etc.

The first 9 patches are cleanups and preparations, maybe some of
these can go regardless of this series.

Patch 10 changes the hvs_remote_addr_init(). setting the
VMADDR_CID_HOST as remote CID instead of VMADDR_CID_ANY to make
the choice of transport to be used work properly.

Patch 11 adds multi-transports support.

Patch 12 changes a little bit the vmci_transport and the vmci driver
to register the vmci_transport only when there are active host/guest.

Patch 13 prevents the transport modules unloading while sockets are
assigned to them.

Patch 14 fixes an issue in the bind() logic discoverable only with
the new multi-transport support.

Patch 15 refuses CID assigned to the guest->host transport in the
vhost_transport.

I've tested this series with nested KVM (vsock-transport [L0,L1],
virtio-transport[L1,L2]) and with VMware (L0) + KVM (L1)
(vmci-transport [L0,L1], vhost-transport [L1], virtio-transport[L2]).

Dexuan successfully tested the RFC series on HyperV with a Linux guest.

Stefano Garzarella (15):
  vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
  vsock: remove vm_sockets_get_local_cid()
  vsock: remove include/linux/vm_sockets.h file
  vsock: add 'transport' member in the struct vsock_sock
  vsock/virtio: add transport parameter to the
    virtio_transport_reset_no_sock()
  vsock: add 'struct vsock_sock *' param to vsock_core_get_transport()
  vsock: handle buffer_size sockopts in the core
  vsock: add vsock_create_connected() called by transports
  vsock: move vsock_insert_unbound() in the vsock_create()
  hv_sock: set VMADDR_CID_HOST in the hvs_remote_addr_init()
  vsock: add multi-transports support
  vsock/vmci: register vmci_transport only when VMCI guest/host are
    active
  vsock: prevent transport modules unloading
  vsock: fix bind() behaviour taking care of CID
  vhost/vsock: refuse CID assigned to the guest->host transport

 drivers/misc/vmw_vmci/vmci_driver.c     |  67 +++++
 drivers/misc/vmw_vmci/vmci_driver.h     |   2 +
 drivers/misc/vmw_vmci/vmci_guest.c      |   2 +
 drivers/misc/vmw_vmci/vmci_host.c       |   7 +
 drivers/vhost/vsock.c                   | 102 ++++---
 include/linux/virtio_vsock.h            |  18 +-
 include/linux/vm_sockets.h              |  15 -
 include/linux/vmw_vmci_api.h            |   2 +
 include/net/af_vsock.h                  |  45 +--
 include/net/vsock_addr.h                |   2 +-
 net/vmw_vsock/af_vsock.c                | 382 ++++++++++++++++++------
 net/vmw_vsock/hyperv_transport.c        |  70 ++---
 net/vmw_vsock/virtio_transport.c        | 177 ++++++-----
 net/vmw_vsock/virtio_transport_common.c | 166 +++++-----
 net/vmw_vsock/vmci_transport.c          | 140 ++++-----
 net/vmw_vsock/vmci_transport.h          |   3 -
 net/vmw_vsock/vmci_transport_notify.h   |   1 -
 17 files changed, 679 insertions(+), 522 deletions(-)
 delete mode 100644 include/linux/vm_sockets.h
```
#### [RFC PATCH v7 0/7] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Thu Nov 14 12:13:51 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11243629
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17C1F1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 12:14:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0021F2071B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 12:14:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726953AbfKNMOQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 07:14:16 -0500
Received: from foss.arm.com ([217.140.110.172]:41816 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbfKNMOQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 07:14:16 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 726A231B;
        Thu, 14 Nov 2019 04:14:15 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 8FA853F6C4;
        Thu, 14 Nov 2019 04:14:08 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v7 0/7] Enable ptp_kvm for arm64
Date: Thu, 14 Nov 2019 20:13:51 +0800
Message-Id: <20191114121358.6684-1-jianyong.wu@arm.com>
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
from v6 to v7:
        (1) include the omited clocksource_id.h in last version.
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
  time: Add mechanism to recognize clocksource in time_get_snapshot
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

Mark Rutland (1):
  arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()

 drivers/clocksource/arm_arch_timer.c        | 24 ++++++
 drivers/firmware/psci/psci.c                | 16 ++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm_arm64.c                 | 53 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 77 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/asm-generic/ptp_kvm.h               | 12 +++
 include/linux/arm-smccc.h                   | 30 ++++++-
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 13 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/psci.c                         | 22 ++++++
 17 files changed, 295 insertions(+), 66 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH v5 00/18] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
From patchwork Thu Nov 14 20:15:02 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11244469
Return-Path: <SRS0=Qdv9=ZG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7ABAB17F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 20:17:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 534EF20725
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 Nov 2019 20:17:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="29QKVIUh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726969AbfKNUPf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 Nov 2019 15:15:35 -0500
Received: from mail-eopbgr730059.outbound.protection.outlook.com
 ([40.107.73.59]:60877
        "EHLO NAM05-DM3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726474AbfKNUPe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Nov 2019 15:15:34 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BBxXP0/MTTM6DQZHBQEha6OVL2wI+S2cQwutPk2M6mGkS7RGi7Y6KwWx0aBPmNk7CUNG7Ee59w4iL+qMxsUsqtL5phM5QPYcoe0EIYv4OOhB5lB56S9pCnUuWFT75/Nh95JrXdU2be0WbkSZ222QC0Sd27ateCLZJrsLiEkH1wHftGKolaO/PAkBZWiIT5YZvX5ZoVxvRnZWAkriprAXDnv9hmhonQWH5K7Mi3B5DXpSsE091jCno7sbo3SV45IozXs6amCC17KqfeZYojbzRNrynYpB1rc77O5DsYExL11HtZQMfgd6HeLEejg7KUveOcxt8gcQgV6SVy3tfDANgw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jDqC351o0js/cAD46FTL4V92yHTqkl9fm/26NeKosas=;
 b=mooOf2YvtCVHRQa1WQ0TMg8fNG6Sjh+yXe8ys+GyuSkxdnTHLoS2oT2bjwpDGEt+31ircb7XAtrrv8YJ97pgAguhZWBjkHnR0cp3qE4pUQnbVoG8AK/6Y5YalvDl2Xnpm+QONlPjg9QEiLUGLREKRxmmxYznbL4p+k1cv4zHGtIym4Mo/jT2yH/UrFdaJQLBXyAvXGq3eyrGFERnodjLobr/8e69SWwE+IDfmTQt5zF9SFky8SrVdKvh/itPEQrvPFUmnXXhtU/9JGSrnGWbJosF6UGynbPbgQ57kXoxYY3mxbPQBoqCEhEOenDfL+nQGD8dIHvn5mYfPa0+qElTTA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jDqC351o0js/cAD46FTL4V92yHTqkl9fm/26NeKosas=;
 b=29QKVIUhlbfrEoqwsVDFocWanhjxGyy+WYzgdfchNdgSZmtPL4qELWnbrC0EhZ0+uOntANMvxgrPzVHGK8+I6z2Q5QuB/oB33EGOCYME0CyxWXz0lbj9WE/CgoCWTCh3mfPlOBAw9NzbECtetSDJhfnpE1z+kSNjocaOFb8X9Wc=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (10.255.173.210) by
 DM6PR12MB3739.namprd12.prod.outlook.com (10.255.172.140) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2451.23; Thu, 14 Nov 2019 20:15:31 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::4898:93e0:3c0c:d862%6]) with mapi id 15.20.2451.027; Thu, 14 Nov 2019
 20:15:30 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, joro@8bytes.org,
        vkuznets@redhat.com, rkagan@virtuozzo.com, graf@amazon.com,
        jschoenh@amazon.de, karahmed@amazon.de, rimasluk@amazon.com,
        jon.grimm@amd.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH v5 00/18] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
 mode
Date: Thu, 14 Nov 2019 14:15:02 -0600
Message-Id: <1573762520-80328-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: SN1PR12CA0099.namprd12.prod.outlook.com
 (2603:10b6:802:21::34) To DM6PR12MB3865.namprd12.prod.outlook.com
 (2603:10b6:5:1c8::18)
MIME-Version: 1.0
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c83b3ded-d871-48ad-af91-08d7693f65b5
X-MS-TrafficTypeDiagnostic: DM6PR12MB3739:
X-MS-Exchange-PUrlCount: 2
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3739F0394876D32638C4CE3BF3710@DM6PR12MB3739.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1247;
X-Forefront-PRVS: 02213C82F8
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(366004)(376002)(39860400002)(346002)(136003)(189003)(199004)(6506007)(25786009)(86362001)(6512007)(6306002)(6436002)(8676002)(47776003)(7416002)(66066001)(6486002)(50226002)(4326008)(3846002)(8936002)(4720700003)(81156014)(2906002)(2870700001)(7736002)(66556008)(305945005)(66476007)(2616005)(6116002)(66946007)(186003)(316002)(14454004)(486006)(478600001)(99286004)(81166006)(26005)(14444005)(476003)(5660300002)(44832011)(386003)(52116002)(23676004)(50466002)(6666004)(36756003)(21314003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3739;H:DM6PR12MB3865.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 bZbTTViH4D/iZRc5tmyfcP+gKVilS0c1lAY54cwwXrUga8YqHyE4Mw3ZU250TYuu4TglVYh/K6J8sQLpFxXofEIidlp2B73vg+WaGU/evKJMhSFSU3zr4WZL+qP3/QtzHi8Xp+JB4YCh65TDgDubjBXUUJTlnGVI3OeV52oOxoE5pf8hlU6GIe1JRIgy9vGF7k1H2Q3iG0pM3ihthWeZFknxQs7AV1+VdM4iJb2yxM7K5os5ffICeYqOZ90Sa2QjcJbc41YKbm0HYwz+OAtUi6Th1H9MfKv0Jod54kwqGCOr61ATj9BUu5mQk8INHks7s1EhdBS0nkz6Veyr+4xjTCmZmMD+EOyfoqXiM/dpfd1tX4/lAzSvALWuGy5oNju3sW68Qd94Z2utofiPYDQbKwEI9GsbY0ZdZXVpRY3ehw2a4dr4s0Z5GZD4vrGQf8eJkE18DjMctVg1+7hO/AvkdKNJxz7bHL4Dn16o1kGizZo=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c83b3ded-d871-48ad-af91-08d7693f65b5
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 14 Nov 2019 20:15:30.7855
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 CiwEeXsQewKXn503MiyBqIimbGmCW5CPcGfAsSrmSIrLyyiMdjRZt1JdujADO9QdtKkt94WqoiJ6KS2h+nZa3w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3739
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'commit 67034bb9dd5e ("KVM: SVM: Add irqchip_split() checks before
enabling AVIC")' was introduced to fix miscellaneous boot-hang issues
when enable AVIC. This is mainly due to AVIC hardware doest not #vmexit
on write to LAPIC EOI register resulting in-kernel PIC and IOAPIC to
wait and do not inject new interrupts (e.g. PIT, RTC).

This limits AVIC to only work with kernel_irqchip=split mode, which is
not currently enabled by default, and also required user-space to
support split irqchip model, which might not be the case.

The goal of this series is to enable AVIC to work in both irqchip modes,
by allowing AVIC to be deactivated temporarily during runtime, and fallback
to legacy interrupt injection mode (w/ vINTR and interrupt windows)
when needed, and then re-enabled subsequently (a.k.a Dynamic APICv).

Similar approach is also used to handle Hyper-V SynIC in the
'commit 5c919412fe61 ("kvm/x86: Hyper-V synthetic interrupt controller")',
where APICv is permanently disabled at runtime (currently broken for
AVIC, and fixed by this series). 

This series contains several parts:
  * Part 1: patch 1,2
    Code clean up, refactor, and introduce helper functions

  * Part 2: patch 3 
    Introduce APICv deactivate bits to keep track of APICv state 
    for each vm.
 
  * Part 3: patch 4-10
    Add support for activate/deactivate APICv at runtime

  * Part 4: patch 11-14:
    Add support for various cases where APICv needs to
    be deactivated

  * Part 5: patch 15-17:
    Introduce in-kernel IOAPIC workaround for AVIC EOI

  * Part 6: path 18
    Allow enable AVIC w/ kernel_irqchip=on

Pre-requisite Patch:
  * commit b9c6ff94e43a ("iommu/amd: Re-factor guest virtual APIC (de-)activation code")
    (https://git.kernel.org/pub/scm/linux/kernel/git/joro/iommu.git/commit/
     ?h=next&id=b9c6ff94e43a0ee053e0c1d983fba1ac4953b762)

This series has been tested against v5.3 as following:
  * Booting Linux, FreeBSD, and Windows Server 2019 VMs upto 240 vcpus
    w/ qemu option "kernel-irqchip=on" and "-no-hpet".
  * Pass-through Intel 10GbE NIC and run netperf in the VM.

Changes from V4: (https://lkml.org/lkml/2019/11/1/764)
  * Rename APICV_DEACT_BIT_xxx to APICV_INHIBIT_REASON_xxxx
  * Introduce kvm_x86_ops.check_apicv_inhibit_reasons hook
    to allow vendors to specify which APICv inhibit reason bits
    to support (patch 08/18).
  * Update comment on kvm_request_apicv_update() no-lock requirement.
    (patch 04/18)

Suravee Suthikulpanit (18):
  kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm
    parameter
  kvm: lapic: Introduce APICv update helper function
  kvm: x86: Introduce APICv inhibit reason bits
  kvm: x86: Add support for dynamic APICv
  kvm: x86: Add APICv (de)activate request trace points
  kvm: x86: svm: Add support to (de)activate posted interrupts
  svm: Add support for setup/destroy virutal APIC backing page for AVIC
  kvm: x86: Introduce APICv x86 ops for checking APIC inhibit reasons
  kvm: x86: Introduce x86 ops hook for pre-update APICv
  svm: Add support for dynamic APICv
  kvm: x86: hyperv: Use APICv update request interface
  svm: Deactivate AVIC when launching guest with nested SVM support
  svm: Temporary deactivate AVIC during ExtINT handling
  kvm: i8254: Deactivate APICv when using in-kernel PIT re-injection
    mode.
  kvm: lapic: Clean up APIC predefined macros
  kvm: ioapic: Refactor kvm_ioapic_update_eoi()
  kvm: ioapic: Lazy update IOAPIC EOI
  svm: Allow AVIC with in-kernel irqchip mode

 arch/x86/include/asm/kvm_host.h |  19 ++++-
 arch/x86/kvm/hyperv.c           |   5 +-
 arch/x86/kvm/i8254.c            |  12 +++
 arch/x86/kvm/ioapic.c           | 149 +++++++++++++++++++++++-------------
 arch/x86/kvm/lapic.c            |  35 +++++----
 arch/x86/kvm/lapic.h            |   2 +
 arch/x86/kvm/svm.c              | 164 +++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/trace.h            |  19 +++++
 arch/x86/kvm/vmx/vmx.c          |  12 ++-
 arch/x86/kvm/x86.c              |  71 ++++++++++++++---
 10 files changed, 385 insertions(+), 103 deletions(-)
```
