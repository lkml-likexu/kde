

#### [PATCH v3 0/4] KVM: arm64: Add VLPI migration support on GICv4.1
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Wed Jan 27 12:13:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12049919
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1F50C433E0
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 12:21:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5BFF220791
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 12:21:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237670AbhA0MVT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 07:21:19 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11902 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237709AbhA0MOr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Jan 2021 07:14:47 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DQjD34KLGz7bFy;
        Wed, 27 Jan 2021 20:12:51 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.186.182) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Wed, 27 Jan 2021 20:13:57 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v3 0/4] KVM: arm64: Add VLPI migration support on GICv4.1
Date: Wed, 27 Jan 2021 20:13:33 +0800
Message-ID: <20210127121337.1092-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.182]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Marc, sorry for the late commit.

In GICv4.1, migration has been supported except for (directly-injected)
VLPI. And GICv4.1 Spec explicitly gives a way to get the VLPI's pending
state (which was crucially missing in GICv4.0). So we make VLPI migration
capable on GICv4.1 in this patch set.

In order to support VLPI migration, we need to save and restore all
required configuration information and pending states of VLPIs. But
in fact, the configuration information of VLPIs has already been saved
(or will be reallocated on the dst host...) in vgic(kvm) migration.
So we only have to migrate the pending states of VLPIs specially.

Below is the related workflow in migration.

On the save path:
	In migration completion:
		pause all vCPUs
				|
		call each VM state change handler:
			pause other devices (just keep from sending interrupts, and
			such as VFIO migration protocol has already realized it [1])
					|
			flush ITS tables into guest RAM
					|
			flush RDIST pending tables (also flush VLPI state here)
				|
		...
On the resume path:
	load each device's state:
		restore ITS tables (include pending tables) from guest RAM
				|
		for other (PCI) devices (paused), if configured to have VLPIs,
		establish the forwarding paths of their VLPIs (and transfer
		the pending states from kvm's vgic to VPT here)

We have tested this series in VFIO migration, and found some related
issues in QEMU [2].

Links:
[1] vfio: UAPI for migration interface for device state:
    https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=a8a24f3f6e38103b77cf399c38eb54e1219d00d6
[2] vfio: Some fixes and optimizations for VFIO migration:
    https://patchwork.ozlabs.org/cover/1413263/

History:

v2 -> v3
 - Add the vgic initialized check to ensure that the allocation and enabling
   of the doorbells have already been done before unmapping the vPEs.
 - Check all get_vlpi_state related conditions in save_pending_tables in one place.
 - Nit fixes.

v1 -> v2:
 - Get the VLPI state from the KVM side.
 - Nit fixes.

Thanks,
Shenming


Shenming Lu (3):
  KVM: arm64: GICv4.1: Add function to get VLPI state
  KVM: arm64: GICv4.1: Try to save hw pending state in
    save_pending_tables
  KVM: arm64: GICv4.1: Give a chance to save VLPI's pending state

Zenghui Yu (1):
  KVM: arm64: GICv4.1: Restore VLPI's pending state to physical side

 .../virt/kvm/devices/arm-vgic-its.rst         |  2 +-
 arch/arm64/kvm/vgic/vgic-its.c                |  6 +-
 arch/arm64/kvm/vgic/vgic-v3.c                 | 61 +++++++++++++++++--
 arch/arm64/kvm/vgic/vgic-v4.c                 | 33 ++++++++++
 arch/arm64/kvm/vgic/vgic.h                    |  1 +
 5 files changed, 93 insertions(+), 10 deletions(-)
```
#### [PATCH 0/5] KVM: Make the maximum number of user memslots
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Jan 27 17:57:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12050747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A294BC433DB
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 17:59:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58B3064DA0
	for <kvm@archiver.kernel.org>; Wed, 27 Jan 2021 17:59:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344077AbhA0R7V (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 27 Jan 2021 12:59:21 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:22922 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1344094AbhA0R7I (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 27 Jan 2021 12:59:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611770261;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=PiBd6yjo3qbKRU8POFjExLSn96nLsQdRPV9/WzOWKC8=;
        b=i5a2H8mYip9YcsWadjcPQi4JkOOeY+alDVmCxaPMGFm/bdYAojacrUcBwqs6zh8q3fzQow
        70FQkw0hg6MOmGtVt2mNCrTwDxREJ+CtUBsd6boPWDrCiA3vN4Ld/s/EJJdCSBnMOHMHY/
        D83fyY2v8NtS/ZzXik2GHJRHUl/5HvY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-395-WXuDuhHtPem9jt0yQOnMOw-1; Wed, 27 Jan 2021 12:57:38 -0500
X-MC-Unique: WXuDuhHtPem9jt0yQOnMOw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3C47959;
        Wed, 27 Jan 2021 17:57:37 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.57])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7CC3660854;
        Wed, 27 Jan 2021 17:57:32 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        "Maciej S . Szmigiero" <maciej.szmigiero@oracle.com>
Subject: [PATCH 0/5] KVM: Make the maximum number of user memslots
 configurable and raise the default
Date: Wed, 27 Jan 2021 18:57:26 +0100
Message-Id: <20210127175731.2020089-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a successor of previously sent "[PATCH RFC 0/4] KVM: x86:
Drastically raise KVM_USER_MEM_SLOTS limit".

Changes since RFC:
- Re-wrote everything [Sean]. The maximum number of slots is now
a per-VM thing controlled by an ioctl.

Original description:

Current KVM_USER_MEM_SLOTS limit on x86 (509) can be a limiting factor
for some configurations. In particular, when QEMU tries to start a Windows
guest with Hyper-V SynIC enabled and e.g. 256 vCPUs the limit is hit as
SynIC requires two pages per vCPU and the guest is free to pick any GFN for
each of them, this fragments memslots as QEMU wants to have a separate
memslot for each of these pages (which are supposed to act as 'overlay'
pages).

Memory slots are allocated dynamically in KVM when added so the only real
limitation is 'id_to_index' array which is 'short'. We don't seem to have
any other KVM_MEM_SLOTS_NUM/KVM_USER_MEM_SLOTS-sized statically defined
structures.

We could've just raised the limit to e.g. '1021' (we have 3 private
memslots on x86) and this should be enough for now as KVM_MAX_VCPUS is
'288' but AFAIK there are plans to raise this limit as well. Raise the
default value to 32768 - KVM_PRIVATE_MEM_SLOTS and introduce a new ioctl
to set the limit per-VM.

Vitaly Kuznetsov (5):
  KVM: Make the maximum number of user memslots a per-VM thing
  KVM: Raise the maximum number of user memslots
  KVM: Make the maximum number of user memslots configurable
  selftests: kvm: Test the newly introduced KVM_CAP_MEMSLOTS_LIMIT
  selftests: kvm: Raise the default timeout to 120 seconds

 Documentation/virt/kvm/api.rst                | 16 +++++++
 arch/arm64/include/asm/kvm_host.h             |  1 -
 arch/mips/include/asm/kvm_host.h              |  1 -
 arch/powerpc/include/asm/kvm_host.h           |  1 -
 arch/powerpc/kvm/book3s_hv.c                  |  2 +-
 arch/s390/include/asm/kvm_host.h              |  1 -
 arch/s390/kvm/kvm-s390.c                      |  2 +-
 arch/x86/include/asm/kvm_host.h               |  2 -
 include/linux/kvm_host.h                      |  6 +--
 include/uapi/linux/kvm.h                      |  1 +
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 30 ++++++++++++-
 .../selftests/kvm/set_memory_region_test.c    | 43 ++++++++++++++++---
 tools/testing/selftests/kvm/settings          |  1 +
 virt/kvm/dirty_ring.c                         |  2 +-
 virt/kvm/kvm_main.c                           | 42 +++++++++++++++---
 16 files changed, 128 insertions(+), 24 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/settings
```
