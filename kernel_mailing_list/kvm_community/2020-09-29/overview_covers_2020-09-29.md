

#### [PATCH v5 00/10] vfio/fsl-mc: VFIO support for FSL-MC device
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

The patches are dependent on some changes in the mc-bus (bus/fsl-mc)
driver. The changes were needed in order to re-use code and to export
some more functions that are needed by the VFIO driver.
Currenlty the mc-bus patches are under review:
https://www.spinics.net/lists/kernel/msg3680670.html

v4 --> v5
- do not allow mmap for DPRCs
- style fixes

v3 --> v4
- use bus provided functions to tear down the DPRC
- added reset support

v2 --> v3
- There is no need to align region size to page size
- read/write implemented for all DPAA2 objects
- review fixes

v1 --> v2
- Fixed the container reset, a new flag added to the firmware command
- Implement a bus notifier for setting driver_override

Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (9):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices
  vfio/fsl-mc: Add support for device reset

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 677 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 193 ++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  55 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 947 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
#### [RFC PATCH 0/4] Add support for ARMv8.6 TWED feature
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
From patchwork Tue Sep 29 09:17:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11805417
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F4DE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 09:17:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 116B6208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 09:17:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727958AbgI2JRz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 05:17:55 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:14707 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727691AbgI2JRy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Sep 2020 05:17:54 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 545B0E38F9F3F29BB102;
        Tue, 29 Sep 2020 17:17:52 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.69) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.487.0; Tue, 29 Sep 2020 17:17:45 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>
CC: <will@kernel.org>, <catalin.marinas@arm.com>, <maz@kernel.org>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <wanghaibin.wang@huawei.com>,
        <yezengruan@huawei.com>, <shameerali.kolothum.thodi@huawei.com>,
        <fanhenglong@huawei.com>, <wangjingyi11@huawei.com>,
        <prime.zeng@hisilicon.com>
Subject: [RFC PATCH 0/4] Add support for ARMv8.6 TWED feature
Date: Tue, 29 Sep 2020 17:17:23 +0800
Message-ID: <20200929091727.8692-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.69]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TWE Delay is an optional feature in ARMv8.6 Extentions. There is a
performance benefit in waiting for a period of time for an event to
arrive before taking the trap as it is common that event will arrive
“quite soon” after executing the WFE instruction.

This series adds support for TWED feature and implements TWE delay
value dynamic adjustment.

Thanks for Shameer's advice on this series. The function of this patch
has been tested on TWED supported hardware and the performance of it is
still on test, any advice will be welcomed.

Jingyi Wang (2):
  KVM: arm64: Make use of TWED feature
  KVM: arm64: Use dynamic TWE Delay value

Zengruan Ye (2):
  arm64: cpufeature: TWED support detection
  KVM: arm64: Add trace for TWED update

 arch/arm64/Kconfig                   | 10 +++++
 arch/arm64/include/asm/cpucaps.h     |  3 +-
 arch/arm64/include/asm/kvm_arm.h     |  5 +++
 arch/arm64/include/asm/kvm_emulate.h | 38 ++++++++++++++++++
 arch/arm64/include/asm/kvm_host.h    | 19 ++++++++-
 arch/arm64/include/asm/virt.h        |  8 ++++
 arch/arm64/kernel/cpufeature.c       | 12 ++++++
 arch/arm64/kvm/arm.c                 | 58 ++++++++++++++++++++++++++++
 arch/arm64/kvm/handle_exit.c         |  2 +
 arch/arm64/kvm/trace_arm.h           | 21 ++++++++++
 10 files changed, 174 insertions(+), 2 deletions(-)
```
#### [PATCH v3 0/2] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Sep 29 15:09:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11806203
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 639C56CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 15:10:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D50320789
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 15:10:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QGXpIkPw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731420AbgI2PKV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 11:10:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49249 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729963AbgI2PKJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Sep 2020 11:10:09 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601392208;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xAend5D4n0puvrh6V/dnpWIor7tFXJ4ZRbs/LW8W9/Y=;
        b=QGXpIkPwGivJ7R2BXNuUiV5UYVDGIBoYYyMWCKwS5Gg5fw5lR4/L+1ZGYD4qp1FbsLl4ui
        0McIJGoVH3BxaOjAI7KHo5D6o0f31mWj9m5TEfOE9aWFT30SFt4n1zu8ED+FxVAws6KwfM
        qK8XgOMr1xcwYEZn0XI4cDqDhaEMVuc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-61-QZ-9gau8Nt-qac9udG7_hQ-1; Tue, 29 Sep 2020 11:10:04 -0400
X-MC-Unique: QZ-9gau8Nt-qac9udG7_hQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B145956B2C;
        Tue, 29 Sep 2020 15:09:47 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.26])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 358C97366C;
        Tue, 29 Sep 2020 15:09:45 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/2] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
 more useful
Date: Tue, 29 Sep 2020 17:09:42 +0200
Message-Id: <20200929150944.1235688-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v2:
- Keep vCPU version of the ioctl intact but make it 'deprecated' in
  api.rst [Paolo Bonzini]
- First two patches of v2 series already made it to kvm/queue

QEMU series using the feature:
https://lists.gnu.org/archive/html/qemu-devel/2020-09/msg02017.html

Original description:

KVM_GET_SUPPORTED_HV_CPUID was initially implemented as a vCPU ioctl but
this is not very useful when VMM is just trying to query which Hyper-V
features are supported by the host prior to creating VM/vCPUs. The data
in KVM_GET_SUPPORTED_HV_CPUID is mostly static with a few exceptions but
it seems we can change this. Add support for KVM_GET_SUPPORTED_HV_CPUID as
a system ioctl as well.

QEMU specific description:
In some cases QEMU needs to collect the information about which Hyper-V
features are supported by KVM and pass it up the stack. For non-hyper-v
features this is done with system-wide KVM_GET_SUPPORTED_CPUID/
KVM_GET_MSRS ioctls but Hyper-V specific features don't get in the output
(as Hyper-V CPUIDs intersect with KVM's). In QEMU, CPU feature expansion
happens before any KVM vcpus are created so KVM_GET_SUPPORTED_HV_CPUID
can't be used in its current shape.

Vitaly Kuznetsov (2):
  KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
  KVM: selftests: test KVM_GET_SUPPORTED_HV_CPUID as a system ioctl

 Documentation/virt/kvm/api.rst                | 16 ++--
 arch/x86/kvm/hyperv.c                         |  6 +-
 arch/x86/kvm/hyperv.h                         |  4 +-
 arch/x86/kvm/vmx/evmcs.c                      |  3 +-
 arch/x86/kvm/x86.c                            | 45 ++++++----
 include/uapi/linux/kvm.h                      |  3 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 26 ++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 87 +++++++++++--------
 9 files changed, 123 insertions(+), 69 deletions(-)
```
#### [PATCH v2 0/2] vhost: Skip access checks on GIOVAs
##### From: Greg Kurz <groug@kaod.org>

```c
From patchwork Tue Sep 29 16:30:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11806339
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D13E139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 16:30:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 743AC2076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 16:30:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729556AbgI2Qag convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 12:30:36 -0400
Received: from us-smtp-delivery-44.mimecast.com ([207.211.30.44]:38840 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728615AbgI2Qad (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Sep 2020 12:30:33 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-553-Zle2tyG7M42IAyhjs9qLRQ-1; Tue, 29 Sep 2020 12:30:27 -0400
X-MC-Unique: Zle2tyG7M42IAyhjs9qLRQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 33FBC8015C5;
        Tue, 29 Sep 2020 16:30:26 +0000 (UTC)
Received: from bahia.lan (ovpn-113-41.ams2.redhat.com [10.36.113.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EAF9E1972A;
        Tue, 29 Sep 2020 16:30:20 +0000 (UTC)
Subject: [PATCH v2 0/2] vhost: Skip access checks on GIOVAs
From: Greg Kurz <groug@kaod.org>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, qemu-devel@nongnu.org,
        Laurent Vivier <laurent@vivier.eu>,
        David Gibson <david@gibson.dropbear.id.au>
Date: Tue, 29 Sep 2020 18:30:20 +0200
Message-ID: <160139701999.162128.2399875915342200263.stgit@bahia.lan>
User-Agent: StGit/0.21
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series addresses some misuse around vring addresses provided by
userspace when using an IOTLB device. The misuse cause failures of
the VHOST_SET_VRING_ADDR ioctl on POWER, which in turn causes QEMU
to crash at migration time.

While digging some more I realized that log_access_ok() can also be 
passed a GIOVA (vq->log_addr) even though log_used() will never log
anything at that address. I could observe addresses beyond the end
of the log bitmap being passed to access_ok(), but it didn't have any
impact because the addresses were still acceptable from an access_ok()
standpoint. Adding a second patch to fix that anyway.

Note that I've also posted a patch for QEMU so that it skips the used
structure GIOVA when allocating the log bitmap. Otherwise QEMU fails to
allocate it because POWER puts GIOVAs very high in the address space (ie.
over 0x800000000000000ULL).

https://patchwork.ozlabs.org/project/qemu-devel/patch/160105498386.68108.2145229309875282336.stgit@bahia.lan/

v2:
 - patch 1: move the (vq->ioltb) check from vhost_vq_access_ok() to
            vq_access_ok() as suggested by MST
 - patch 2: new patch
---

Greg Kurz (2):
      vhost: Don't call access_ok() when using IOTLB
      vhost: Don't call log_access_ok() when using IOTLB


 drivers/vhost/vhost.c |   32 ++++++++++++++++++++++++--------
 1 file changed, 24 insertions(+), 8 deletions(-)

--
Greg
```
#### [PATCH v4 00/12] Support disabling TCG on ARM (part 2)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Tue Sep 29 22:43:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11807293
Return-Path: <SRS0=xlFf=DG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3271E13B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 22:44:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A8712075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Sep 2020 22:44:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DfJkfJrY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728701AbgI2WoG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Sep 2020 18:44:06 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:39596 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728206AbgI2WoF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Sep 2020 18:44:05 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601419443;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Sm3Gm34Jjn5EWoNbFg1uRbBUxTP1yXhpa0ydpRV9pWQ=;
        b=DfJkfJrYWYEmrzSS/DwzH9maizUGiuRsF//vS5MkWBOnc3dR+q414QXHQv8M+4Jqxz9ni0
        67aDwI1+ndqOevka49kb4ff9fuZ/liToqMM434jytP4rsVsfM//4EAzU9ewtX6/uxIsERi
        ZRrKgb9xYVvgnoM+VwH7MNtYdPsa3AY=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-541-Pm43bzf8NGKboPvbAZf0cA-1; Tue, 29 Sep 2020 18:43:59 -0400
X-MC-Unique: Pm43bzf8NGKboPvbAZf0cA-1
Received: by mail-wm1-f72.google.com with SMTP id m25so2428690wmi.0
        for <kvm@vger.kernel.org>; Tue, 29 Sep 2020 15:43:58 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Sm3Gm34Jjn5EWoNbFg1uRbBUxTP1yXhpa0ydpRV9pWQ=;
        b=M1YUl+rvq2zy9qC5q5eiH8usQmltnV2CoOSuc663I04FPTWJOXf+gVSASkP7BGAd7B
         tO0tjRONqnKjOATpjDet+nCnr80xDBvHSomrxfVyIe0sb4cN89zNwUzIOPd9JQRXLXHs
         Dv9t29yfos5ipRiVtgkQLmmn4iT+O/QB22Z1U/K7jE0WJSJlpyTX04PMHmVswJ7bVGCF
         r8PRrPJThlHlvf1DoU7PDG+BsINCdEfZRYNhUnjTf5fdqOLjdnYrBpuvCynrm+pXbnl9
         cBx+9/eCn71sQFPYvqMK7yvWC1qz1/jGi/8gS0+1Aa2wzMmsl8o+2Vs29LA3NqEj8QJ0
         zOWA==
X-Gm-Message-State: AOAM5317kkALBroFzgIdWV9HxbPk2vbI/uM+MFfs0b31fqD/0yX9HomY
        07Nte3mtSmNvZBJvERjTS/dOuDX8hhk+x8TI/2UMAHXoIHJEO7G5jl2YquDml6I4rc3ftAwm1QU
        5tTfX0J9N1LFH
X-Received: by 2002:a05:600c:2053:: with SMTP id
 p19mr6799089wmg.50.1601419437869;
        Tue, 29 Sep 2020 15:43:57 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzytBklMSd+mcQkWT4fWwubovRHL78gH/20a8RlxC2MfpeBb4ay504uDGUwZsnPRbVg7dNQwQ==
X-Received: by 2002:a05:600c:2053:: with SMTP id
 p19mr6799082wmg.50.1601419437666;
        Tue, 29 Sep 2020 15:43:57 -0700 (PDT)
Received: from x1w.redhat.com (74.red-83-53-161.dynamicip.rima-tde.net.
 [83.53.161.74])
        by smtp.gmail.com with ESMTPSA id
 t17sm8129443wrx.82.2020.09.29.15.43.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 29 Sep 2020 15:43:56 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Thomas Huth <thuth@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>, Fam Zheng <fam@euphon.net>,
 Peter Maydell <peter.maydell@linaro.org>, kvm@vger.kernel.org, =?utf-8?q?Al?=
	=?utf-8?q?ex_Benn=C3=A9e?= <alex.bennee@linaro.org>, qemu-arm@nongnu.org,
 Richard Henderson <rth@twiddle.net>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v4 00/12] Support disabling TCG on ARM (part 2)
Date: Wed, 30 Sep 2020 00:43:43 +0200
Message-Id: <20200929224355.1224017-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cover from Samuel Ortiz from (part 1) [1]:

  This patchset allows for building and running ARM targets with TCG
  disabled. [...]

  The rationale behind this work comes from the NEMU project where we're
  trying to only support x86 and ARM 64-bit architectures, without
  including the TCG code base. We can only do so if we can build and run
  ARM binaries with TCG disabled.

v4 almost 2 years later... [2]:
- Rebased on Meson
- Addressed Richard review comments
- Addressed Claudio review comments

v3 almost 18 months later [3]:
- Rebased
- Addressed Thomas review comments
- Added Travis-CI job to keep building --disable-tcg on ARM

v2 [4]:
- Addressed review comments from Richard and Thomas from v1 [1]

Regards,

Phil.

[1]: https://lists.gnu.org/archive/html/qemu-devel/2018-11/msg02451.html
[2]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg689168.html
[3]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg641796.html
[4]: https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05003.html

Green CI:
- https://cirrus-ci.com/build/4572961761918976
- https://gitlab.com/philmd/qemu/-/pipelines/196047779
- https://travis-ci.org/github/philmd/qemu/builds/731370972

Based-on: <20200929125609.1088330-1-philmd@redhat.com>
"hw/arm: Restrict APEI tables generation to the 'virt' machine"
https://www.mail-archive.com/qemu-devel@nongnu.org/msg745792.html

Philippe Mathieu-Daudé (10):
  accel/tcg: Add stub for cpu_loop_exit()
  meson: Allow optional target/${ARCH}/Kconfig
  target/arm: Select SEMIHOSTING if TCG is available
  target/arm: Restrict ARMv4 cpus to TCG accel
  target/arm: Restrict ARMv5 cpus to TCG accel
  target/arm: Restrict ARMv6 cpus to TCG accel
  target/arm: Restrict ARMv7 R-profile cpus to TCG accel
  target/arm: Restrict ARMv7 M-profile cpus to TCG accel
  target/arm: Reorder meson.build rules
  .travis.yml: Add a KVM-only Aarch64 job

Samuel Ortiz (1):
  target/arm: Do not build TCG objects when TCG is off

Thomas Huth (1):
  target/arm: Make m_helper.c optional via CONFIG_ARM_V7M

 default-configs/arm-softmmu.mak |  3 --
 meson.build                     |  8 +++-
 target/arm/cpu.h                | 12 ------
 accel/stubs/tcg-stub.c          |  5 +++
 target/arm/cpu_tcg.c            |  4 +-
 target/arm/helper.c             |  7 ----
 target/arm/m_helper-stub.c      | 73 +++++++++++++++++++++++++++++++++
 .travis.yml                     | 35 ++++++++++++++++
 hw/arm/Kconfig                  | 32 +++++++++++++++
 target/arm/Kconfig              |  4 ++
 target/arm/meson.build          | 40 +++++++++++-------
 11 files changed, 184 insertions(+), 39 deletions(-)
 create mode 100644 target/arm/m_helper-stub.c
 create mode 100644 target/arm/Kconfig
```
