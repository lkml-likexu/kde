

#### [RFC PATCH 00/24] Control VQ support in vDPA
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Sep 24 03:21:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11795923
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B80081668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 03:21:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9506F23600
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 03:21:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Ji0Pi0uv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726553AbgIXDVs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 23:21:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40899 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726513AbgIXDVs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 23:21:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600917706;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ulvoXaawU1LlJCvKBwZXwnTD0YBj1z2Rn2hoHe4yuKA=;
        b=Ji0Pi0uvPp+TIOMcy7TqKvbmb1ZtbqIvG1BlqmBthkHyr4kg2kQzcTd4PSeGnt3tT+UNXf
        aptIQ8vX9W9/s1kBWO9v6EjMWoyY9AG8W9LBYM891Bw987g5iOXMMNWTKQmlP+lFqaZYBF
        uMFGMpx5d5OVokR7b79LNqnVEjmP8zs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-311-nXpWs3-YNjaBVu0TOZk99g-1; Wed, 23 Sep 2020 23:21:45 -0400
X-MC-Unique: nXpWs3-YNjaBVu0TOZk99g-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F5251005E72;
        Thu, 24 Sep 2020 03:21:43 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-193.pek2.redhat.com [10.72.13.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2852B3782;
        Thu, 24 Sep 2020 03:21:27 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: lulu@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, rob.miller@broadcom.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, hanand@xilinx.com,
        mhabets@solarflare.com, eli@mellanox.com, amorenoz@redhat.com,
        maxime.coquelin@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com
Subject: [RFC PATCH 00/24] Control VQ support in vDPA
Date: Thu, 24 Sep 2020 11:21:01 +0800
Message-Id: <20200924032125.18619-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All:

This series tries to add the support for control virtqueue in vDPA.

Control virtqueue is used by networking device for accepting various
commands from the driver. It's a must to support multiqueue and other
configurations.

When used by vhost-vDPA bus driver for VM, the control virtqueue
should be shadowed via userspace VMM (Qemu) instead of being assigned
directly to Guest. This is because Qemu needs to know the device state
in order to start and stop device correctly (e.g for Live Migration).

This requies to isolate the memory mapping for control virtqueue
presented by vhost-vDPA to prevent guest from accesing it directly.

To achieve this, vDPA introduce two new abstractions:

- address space: identified through address space id (ASID) and a set
                 of memory mapping in maintained
- virtqueue group: the minimal set of virtqueues that must share an
                 address space

Device needs to advertise the following attributes to vDPA:

- the number of address spaces supported in the device
- the number of virtqueue groups supported in the device
- the mappings from a specific virtqueue to its virtqueue groups

The mappings from virtqueue to virtqueue groups is fixed and defined
by vDPA device driver. E.g:

- For the device that has hardware ASID support, it can simply
  advertise a per virtqueue virtqueue group.
- For the device that does not have hardware ASID support, it can
  simply advertise a single virtqueue group that contains all
  virtqueues. Or if it wants a software emulated control virtqueue, it
  can advertise two virtqueue groups, one is for cvq, another is for
  the rest virtqueues.

vDPA also allow to change the association between virtqueue group and
address space. So in the case of control virtqueue, userspace
VMM(Qemu) may use a dedicated address space for the control virtqueue
group to isolate the memory mapping.

The vhost/vhost-vDPA is also extend for the userspace to:

- query the number of virtqueue groups and address spaces supported by
  the device
- query the virtqueue group for a specific virtqueue
- assocaite a virtqueue group with an address space
- send ASID based IOTLB commands

This will help userspace VMM(Qemu) to detect whether the control vq
could be supported and isolate memory mappings of control virtqueue
from the others.

To demonstrate the usage, vDPA simulator is extended to support
setting MAC address via a emulated control virtqueue. Please refer
patch 24 for more implementation details.

Please review.

Note that patch 1 and a equivalent of patch 2 have been posted in the
list. Those two are requirement for this series to work, so I add them
here.

Thank

Jason Wang (24):
  vhost-vdpa: fix backend feature ioctls
  vhost-vdpa: fix vqs leak in vhost_vdpa_open()
  vhost: move the backend feature bits to vhost_types.h
  virtio-vdpa: don't set callback if virtio doesn't need it
  vhost-vdpa: passing iotlb to IOMMU mapping helpers
  vhost-vdpa: switch to use vhost-vdpa specific IOTLB
  vdpa: add the missing comment for nvqs in struct vdpa_device
  vdpa: introduce virtqueue groups
  vdpa: multiple address spaces support
  vdpa: introduce config operations for associating ASID to a virtqueue
    group
  vhost_iotlb: split out IOTLB initialization
  vhost: support ASID in IOTLB API
  vhost-vdpa: introduce ASID based IOTLB
  vhost-vdpa: introduce uAPI to get the number of virtqueue groups
  vhost-vdpa: introduce uAPI to get the number of address spaces
  vhost-vdpa: uAPI to get virtqueue group id
  vhost-vdpa: introduce uAPI to set group ASID
  vhost-vdpa: support ASID based IOTLB API
  vdpa_sim: use separated iov for reading and writing
  vdpa_sim: advertise VIRTIO_NET_F_MTU
  vdpa_sim: advertise VIRTIO_NET_F_MAC
  vdpa_sim: factor out buffer completion logic
  vdpa_sim: filter destination mac address
  vdpasim: control virtqueue support

 drivers/vdpa/ifcvf/ifcvf_main.c   |   9 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c |  11 +-
 drivers/vdpa/vdpa.c               |   8 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c  | 293 ++++++++++++++++++++++++------
 drivers/vhost/iotlb.c             |  23 ++-
 drivers/vhost/vdpa.c              | 259 ++++++++++++++++++++------
 drivers/vhost/vhost.c             |  23 ++-
 drivers/vhost/vhost.h             |   4 +-
 drivers/virtio/virtio_vdpa.c      |   2 +-
 include/linux/vdpa.h              |  42 ++++-
 include/linux/vhost_iotlb.h       |   2 +
 include/uapi/linux/vhost.h        |  19 +-
 include/uapi/linux/vhost_types.h  |  10 +-
 13 files changed, 556 insertions(+), 149 deletions(-)
```
#### [PATCH v2 0/7] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Sep 24 14:57:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11797651
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F5406CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 14:59:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 505F32311B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 14:59:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Sxh4UaUS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728329AbgIXO6T (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 10:58:19 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43741 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728307AbgIXO6P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 10:58:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600959494;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=kiRvf77/BW2pJi/JFFEx+okLfqnrBcg7+cHOh16//18=;
        b=Sxh4UaUSk12Y8bxKPMEHx4PqVflIvz3eu/HbOIglp3l35gzYeWs4ra88HPl4OTsda8H1aZ
        3wfhKLqvYejIF18J8IwZb+G2Kjo8h6MgTpxHnKrhy3xvO7fta2dl+lROicuxJCXlEXxH8S
        ePllBi+4qGwrW1Tw00WO5K/w37b7Kws=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-171--Sk-b6pwOVm3bA48u1k4Lg-1; Thu, 24 Sep 2020 10:58:03 -0400
X-MC-Unique: -Sk-b6pwOVm3bA48u1k4Lg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8F17D1008562;
        Thu, 24 Sep 2020 14:58:01 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B0BA55786;
        Thu, 24 Sep 2020 14:57:59 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/7] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
 more useful
Date: Thu, 24 Sep 2020 16:57:50 +0200
Message-Id: <20200924145757.1035782-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1:
- Rebased to kvm/queue [KVM_CAP_SYS_HYPERV_CPUID -> 188]

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

Vitaly Kuznetsov (7):
  KVM: x86: hyper-v: Mention SynDBG CPUID leaves in api.rst
  KVM: x86: hyper-v: disallow configuring SynIC timers with no SynIC
  KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID output independent
    of eVMCS enablement
  KVM: x86: hyper-v: always advertise HV_STIMER_DIRECT_MODE_AVAILABLE
  KVM: x86: hyper-v: drop now unneeded vcpu parameter from
    kvm_vcpu_ioctl_get_hv_cpuid()
  KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
  KVM: selftests: test KVM_GET_SUPPORTED_HV_CPUID as a system ioctl

 Documentation/virt/kvm/api.rst                | 12 +--
 arch/x86/include/asm/kvm_host.h               |  2 +-
 arch/x86/kvm/hyperv.c                         | 30 ++++----
 arch/x86/kvm/hyperv.h                         |  3 +-
 arch/x86/kvm/vmx/evmcs.c                      |  8 +-
 arch/x86/kvm/vmx/evmcs.h                      |  2 +-
 arch/x86/kvm/x86.c                            | 44 ++++++-----
 include/uapi/linux/kvm.h                      |  3 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 26 +++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 77 +++++++++----------
 11 files changed, 120 insertions(+), 89 deletions(-)
```
#### [kvm-unit-tests PATCH 0/9] Update travis CI
##### From: Thomas Huth <thuth@redhat.com>

```c
From patchwork Thu Sep 24 16:16:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11797869
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5BBA9112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 326E42311B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:16:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NLC9UKDP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726596AbgIXQQ3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 12:16:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56014 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726458AbgIXQQ2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 12:16:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600964187;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=5f9IDQpqKUYEZt/PJc6SN3XdD+SlWrtomGR4ny1qU3M=;
        b=NLC9UKDPGmym/FnqJyo6MNQCtZJoMWgdIT7iKxk6x268JvrHmC9ZDeKBfd9SaA+6QEa5Qf
        6GbuT43K6gzwLUcYQugnYrbkNqqJDdKvkVyZT+c4tjYtfiSumhYSI8bbb+7Y3mxz77Iozy
        CvEYepngJ6XkpGsZ27GzR3OeQKcY9RM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-297-DfzocSktP2mCtUwC0lvtBQ-1; Thu, 24 Sep 2020 12:16:25 -0400
X-MC-Unique: DfzocSktP2mCtUwC0lvtBQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 69F6584E247;
        Thu, 24 Sep 2020 16:16:24 +0000 (UTC)
Received: from thuth.com (ovpn-113-113.ams2.redhat.com [10.36.113.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9899573662;
        Thu, 24 Sep 2020 16:16:19 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Drew Jones <drjones@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests PATCH 0/9] Update travis CI
Date: Thu, 24 Sep 2020 18:16:03 +0200
Message-Id: <20200924161612.144549-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Travis now features Ubuntu Focal containers, so we can update our
kvm-unit-tests CI to use it for getting a newer version of QEMU and
the compilers. Thanks to this QEMU update, we can now run more tests
with TCG here.

Additionally, this series switches the second aarch64 build job to
use the native builder - this way we can use the Clang compiler
there to get some additional test coverage. This indeed already helped
to discover some bogus register constraints in the aarch64 code.
(ppc64 and s390x are not using the native builders yet since there are
still some issues with Clang there that I haven't quite figured out ...
that's maybe something for later)

Thomas Huth (9):
  travis.yml: Update from Bionic to Focal
  travis.yml: Rework the x86 64-bit tests
  travis.yml: Refresh the x86 32-bit test list
  travis.yml: Add the selftest-setup ppc64 test
  kbuild: fix asm-offset generation to work with clang
  arm/pmu: Fix inline assembly for Clang
  lib/arm64/spinlock: Fix inline assembly for Clang
  travis.yml: Rework the aarch64 jobs
  travis.yml: Update the list of s390x tests

 .travis.yml             | 71 ++++++++++++++++++++++++-----------------
 arm/pmu.c               | 10 +++---
 lib/arm64/spinlock.c    |  2 +-
 lib/kbuild.h            |  6 ++--
 scripts/asm-offsets.mak |  5 +--
 5 files changed, 54 insertions(+), 40 deletions(-)
```
#### [PATCH v2 0/2] INVD intercept change to skip instruction
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Thu Sep 24 18:41:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11798077
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9903F6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:42:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7722B23600
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:42:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="s8DvnKhy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728750AbgIXSmW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 14:42:22 -0400
Received: from mail-co1nam11on2053.outbound.protection.outlook.com
 ([40.107.220.53]:53036
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727753AbgIXSmW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 14:42:22 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ExYTL9eTaWpX4TWksvwSbIMBRJPl3UUvc2Qn+pb0jKPIm0wcUluw/ww21xbskmTcZJZPkxtV8tVP+/O/u3hUy0QcWBvd2y1PdGD0eXyuRDRcWor/w0HqU1qcWzWYkD7/QjIiiFthCE8gDL+UXst4fQXV7dUWD+EUUyIMBxg6GESnmrYAS79jPqli5yfZZZwAarb4ctQ9eqJAhYscBv7mU4bgscyNMV2b8Dy+5fVVDxS2L8EZGoVeBz9GmwW9izBwiRmBSs/xSc3b46H5LyuLx9OyQ+Lidi7Jd7tZhnpad7wJlRBaG6gSMTnB457ZYut3zpAHn4HgS2hhGwgW6IIC+g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Lcm8HfIXgqeSNXSEypqoTkY498c1ADpLBsIAWg5qeds=;
 b=mb4UfTu8Weo3RY29VlMMTb/rCvaWiy0SYxDkg89XquNZSqfVNjRFiOZlBoZxsA53HlXHJ2xvESW1MxJD2FM9NE5/p5+yTo+gRhBssDh9z4Tz9uprfPjSOQfdbkGvFNHvfq778WCA/xiA4j/vGZhlEUcm6A8azr7ncN1tMill+SGdbr5TaPHrb00+xrXE40LPTrptB/UZv5nvOl2mwOb9tbyvO05K4XugA2qfLxBvgKaNyQZpo/lVK5c1LVRKRjjs3ii0H9lFnRJe5iAdluTzHiY655hG5c747O2+/WFpUJ8AKT5A4nEK4/Msfze8x8B5Mcud8fKricnWc/di0XCbwg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Lcm8HfIXgqeSNXSEypqoTkY498c1ADpLBsIAWg5qeds=;
 b=s8DvnKhyO+RNI+Llurl0ofpertoN9jIYPHhgZN/cyFeJsjEJ7+1I8+t5ZERE9y/ztO5RZqqbPKOqjNhoLZu4TaPWZyKJk4oa/hnTH7AKvHFARu/FqxW2+crLL/VW9YAxpZz03ABkxltoRjAZjpaiE7yfY2LrLB57ifo+7mVyMzo=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB3082.namprd12.prod.outlook.com (2603:10b6:5:11b::12) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.23; Thu, 24 Sep 2020 18:42:20 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3391.024; Thu, 24 Sep 2020
 18:42:20 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH v2 0/2] INVD intercept change to skip instruction
Date: Thu, 24 Sep 2020 13:41:56 -0500
Message-Id: <cover.1600972918.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-ClientProxiedBy: DM5PR21CA0057.namprd21.prod.outlook.com
 (2603:10b6:3:129::19) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR21CA0057.namprd21.prod.outlook.com (2603:10b6:3:129::19) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3433.2 via Frontend
 Transport; Thu, 24 Sep 2020 18:42:19 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c5c51f53-83e9-449b-45d9-08d860b99174
X-MS-TrafficTypeDiagnostic: DM6PR12MB3082:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB308283D9FE4F99E2820198EEEC390@DM6PR12MB3082.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 44C3SicwqDquHX6VSeFAP6NeY9I3ohr587dbTahz+TTzVlk2U/hz3Cy9RZl2njYKxgXBycCqUP0plxV5Gj8FrXNXpnSevbQMB8q1wu6XgXC7v2JrNWrjuG+h7K9+YT20CaygY0G8SOGXzXLQKppAbu906PKgKnoY2Yj6T0dBDsU2Mygs+8/eN4H5iNe9DiFgDIgALCchpMXa+XwaAxlxqKA5plOvCYjIQPO9bomAp19o++AubRGNK4/fc7elYSqMauCK0/yWWZkfD0QkgKGGvYsgvWTmt6fKhw3cJhRSmbDlfc8wOpGgSwW4gF1PT//9pWvMjX4vzd2Jl2ZcoKWWsA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(376002)(346002)(136003)(39860400002)(7416002)(83380400001)(316002)(36756003)(2906002)(956004)(8676002)(8936002)(66556008)(26005)(66476007)(186003)(16526019)(54906003)(478600001)(52116002)(7696005)(2616005)(4744005)(6666004)(5660300002)(66946007)(4326008)(6486002)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 5pzVv+CYb5xXVmKiEe+ZNw1Na7FJd2vecnkF3cLcjlU+i1+5K3YWIkWn+cTdsn0UDJgWno5jNGmZLwSZYHoic/jBS+upfcYH/EVmZRTII+50r3vMRauRbVlJ04N+5tWCXooq9pdsA25+JnwvOoSsHQuN24njjk5XkIYxSVBONbx+gOZSaRyGbodCxXsraDMBT4LEo2waXviu0/Jw2PqAwcDe8fYldwyxdqxTKsm4u8Ayt04xG+9n7nsOytmiXj89bhupYjyyw6nkdCejg6t6oOTaoct9KrUEBp6GBS8+K5Ws9NDUzluo8Atsv+rXjXTGx7nF4VnVr2d2c0WeXWCpnAAuEsgmrKt3TG/+AIM0jnJ9FyM2MvvxRBfiat7FkU1YpvvWQhkiUe18WwYdCSbHEk8/iFwDhFvim0PuQA0d6ue9CBF14fVPMBwhY/coRE/eBrU/ONMJrsC4DogZD4ESVXNwmr0fGouR2BuBfldJ7sHGmpUcBWDpibPlUxWggkTYRRM4H8iGbz3tCU/syDgLYz5yLlfwLuAZMqdvFFqZqLTcFZtYCAagCixlxc6XMzezWesGAoa3bCPFpvBNOHIapB7XG6KWNE9pWnnbcnd7wABHtt9II6/L9eQfUHYsgBmWWBRHmuDjCGT8rD2FammBSw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c5c51f53-83e9-449b-45d9-08d860b99174
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Sep 2020 18:42:19.9787
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 wnmykPQSTd1S/aWTmCPV5pS3IGxcC38eOYaWEUhTy/gUUBRiWD606XmGvrCuo7MOL64ZG682fdfm+Rp7jh4igg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3082
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This series updates the INVD intercept support for both SVM and VMX to
skip the instruction rather than emulating it, since emulation of this
instruction is just a NOP.

For SVM, it requires creating a dedicated INVD intercept routine that
invokes kvm_skip_emulated_instruction(). The current support uses the
common emulate_on_interception() routine, which does not work for SEV
guests, and so a Fixes: tag is added.

For VMX, which already has a dedicated INVD intercept routine, it changes
kvm_emulate_instruction() into a call to kvm_skip_emulated_instruction().

Tom Lendacky (2):
  KVM: SVM: Add a dedicated INVD intercept routine
  KVM: VMX: Do not perform emulation for INVD intercept

 arch/x86/kvm/svm/svm.c | 8 +++++++-
 arch/x86/kvm/vmx/vmx.c | 3 ++-
 2 files changed, 9 insertions(+), 2 deletions(-)
```
#### [PATCH v3 0/5]  KVM: VMX: Clean up RTIT MAXPHYADDR usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Sep 24 19:42:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11798187
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDA991580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 19:43:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD562239CF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 19:43:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726513AbgIXTnQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 15:43:16 -0400
Received: from mga18.intel.com ([134.134.136.126]:31793 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725272AbgIXTmz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 15:42:55 -0400
IronPort-SDR: 
 41lHK3Z6RdKtA7GfkcZXKlHZsYJfBaZrLXjkBA2EkcYASvH7+5IQB3PDYcpV2fqBagH9v3IYXT
 2ZAODmOp/CSA==
X-IronPort-AV: E=McAfee;i="6000,8403,9754"; a="149076385"
X-IronPort-AV: E=Sophos;i="5.77,299,1596524400";
   d="scan'208";a="149076385"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Sep 2020 12:42:52 -0700
IronPort-SDR: 
 A/+uMWafT6EWXWKKO5iDn/P9CPytRGZ7xZ1tjaw9eMO7vtWPt+EPEhFrvFbnu3o/MFdSUzhmV3
 HVjswC92wVGw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,299,1596524400";
   d="scan'208";a="347953041"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by FMSMGA003.fm.intel.com with ESMTP; 24 Sep 2020 12:42:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/5]  KVM: VMX: Clean up RTIT MAXPHYADDR usage
Date: Thu, 24 Sep 2020 12:42:45 -0700
Message-Id: <20200924194250.19137-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Stop using cpuid_query_maxphyaddr() for a random RTIT MSR check, unexport
said function to discourage future use, and do additional related cleanup.

Paolo, feel free to reorder/squash these as you see fit.  Five patches
feels more than a bit gratuitous, but every time I tried to squash things
I ended up with changelogs that ran on and on...

v2:
  - Rebased to kvm/queue, commit e1ba1a15af73 ("KVM: SVM: Enable INVPCID
    feature on AMD").

Sean Christopherson (5):
  KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
  KVM: x86: Unexport cpuid_query_maxphyaddr()
  KVM: VMX: Replace MSR_IA32_RTIT_OUTPUT_BASE_MASK with helper function
  KVM: x86: Move illegal GPA helper out of the MMU code
  KVM: VMX: Use "illegal GPA" helper for PT/RTIT output base check

 arch/x86/kvm/cpuid.c   |  1 -
 arch/x86/kvm/cpuid.h   |  5 +++++
 arch/x86/kvm/mmu.h     |  5 -----
 arch/x86/kvm/mmu/mmu.c |  2 +-
 arch/x86/kvm/vmx/vmx.c | 13 ++++++++-----
 5 files changed, 14 insertions(+), 12 deletions(-)
```
