

#### [PATCH 0/4] KVM: SVM: Code move follow-up
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Thu Jun 25 08:03:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11624747
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF1756C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 08:04:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DD86520789
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 08:04:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390496AbgFYIDc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 04:03:32 -0400
Received: from 8bytes.org ([81.169.241.247]:48804 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726930AbgFYIDc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 04:03:32 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 8E7BF36D; Thu, 25 Jun 2020 10:03:30 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 0/4] KVM: SVM: Code move follow-up
Date: Thu, 25 Jun 2020 10:03:21 +0200
Message-Id: <20200625080325.28439-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here is small series to follow-up on the review comments for moving
the kvm-amd module code to its own sub-directory. The comments were
only about renaming structs and symbols, so there are no functional
changes in these patches.

The comments addressed here are all from [1].

Regards,

	Joerg

[1] https://lore.kernel.org/lkml/87d0917ezq.fsf@vitty.brq.redhat.com/

Joerg Roedel (4):
  KVM: SVM: Rename struct nested_state to svm_nested_state
  KVM: SVM: Add vmcb_ prefix to mark_*() functions
  KVM: SVM: Add svm_ prefix to set/clr/is_intercept()
  KVM: SVM: Rename svm_nested_virtualize_tpr() to
    nested_svm_virtualize_tpr()

 arch/x86/kvm/svm/avic.c   |   2 +-
 arch/x86/kvm/svm/nested.c |   8 +--
 arch/x86/kvm/svm/sev.c    |   2 +-
 arch/x86/kvm/svm/svm.c    | 138 +++++++++++++++++++-------------------
 arch/x86/kvm/svm/svm.h    |  20 +++---
 5 files changed, 85 insertions(+), 85 deletions(-)
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
```
#### [PATCH RFC 0/4] Changes to Support *Virtual* CPU Hotplug for ARM64
##### From: Salil Mehta <salil.mehta@huawei.com>

```c
From patchwork Thu Jun 25 13:37:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Salil Mehta <salil.mehta@huawei.com>
X-Patchwork-Id: 11625377
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 303D314B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:43:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 167AA20707
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:43:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405075AbgFYNnx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 09:43:53 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:60012 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2404890AbgFYNnx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 09:43:53 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 429DA41853EE28F8554D;
        Thu, 25 Jun 2020 21:43:50 +0800 (CST)
Received: from A190218597.china.huawei.com (10.47.76.118) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.487.0; Thu, 25 Jun 2020 21:43:41 +0800
From: Salil Mehta <salil.mehta@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>
CC: <maz@kernel.org>, <will@kernel.org>, <catalin.marinas@arm.com>,
        <christoffer.dall@arm.com>, <andre.przywara@arm.com>,
        <james.morse@arm.com>, <mark.rutland@arm.com>,
        <lorenzo.pieralisi@arm.com>, <sudeep.holla@arm.com>,
        <qemu-arm@nongnu.org>, <peter.maydell@linaro.org>,
        <richard.henderson@linaro.org>, <imammedo@redhat.com>,
        <mst@redhat.com>, <drjones@redhat.com>, <pbonzini@redhat.com>,
        <eric.auger@redhat.com>, <gshan@redhat.com>, <david@redhat.com>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linuxarm@huawei.com>, <mehta.salil.lnk@gmail.com>,
        Salil Mehta <salil.mehta@huawei.com>
Subject: [PATCH RFC 0/4] Changes to Support *Virtual* CPU Hotplug for ARM64
Date: Thu, 25 Jun 2020 14:37:53 +0100
Message-ID: <20200625133757.22332-1-salil.mehta@huawei.com>
X-Mailer: git-send-email 2.8.3
MIME-Version: 1.0
X-Originating-IP: [10.47.76.118]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes to support virtual cpu hotplug in QEMU[1] have been introduced to the
community as RFC. These are under review.

To support virtual cpu hotplug guest kernel must:
1. Identify disabled/present vcpus and set/unset the present mask of the vcpu
   during initialization and hotplug event. It must also set the possible mask
   (which includes disabled vcpus) during init of guest kernel.
2. Provide architecture specific ACPI hooks, for example to map/unmap the
   logical cpuid to hwids/MPIDR. Linux kernel already has generic ACPI cpu
   hotplug framework support.

Changes introduced in this patch-set also ensures that initialization of the
cpus when virtual cpu hotplug is not supported remains un-affected.

Repository:
(*) Kernel changes are at,
     https://github.com/salil-mehta/linux.git virt-cpuhp-arm64/rfc-v1
(*) QEMU changes for vcpu hotplug could be cloned from below site,
     https://github.com/salil-mehta/qemu.git virt-cpuhp-armv8/rfc-v1


THINGS TO DO:
1. Handling of per-cpu variables especially the first-chunk allocations
   (which are NUMA aware) when the vcpu is hotplugged needs further attention
   and review.
2. NUMA related stuff has not been fully tested both in QEMU and kernel.
3. Comprehensive Testing including when cpu hotplug is not supported.
4. Docs

DISCLAIMER:
This is not a complete work but an effort to present the arm vcpu hotplug
implementation to the community. This RFC is being used as a way to verify
the idea mentioned above and to support changes presented for QEMU[1] to
support vcpu hotplug. As of now this is *not* a production level code and might
have bugs. Only a basic testing has been done on HiSilicon Kunpeng920 ARM64
based SoC for Servers to verify the proof-of-concept that has been found working!

Best regards
Salil.

REFERENCES:
[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg712010.html
[2] https://lkml.org/lkml/2019/6/28/1157
[3] https://lists.cs.columbia.edu/pipermail/kvmarm/2018-July/032316.html

Organization of Patches:
[Patch 1-3]
(*) Changes required during guest boot time to support vcpu hotplug 
(*) Max cpu overflow checks
(*) Changes required to pre-setup cpu-operations even for disabled cpus
[Patch 4]
(*) Arch changes required by guest kernel ACPI CPU Hotplug framework.


Salil Mehta (4):
  arm64: kernel: Handle disabled[(+)present] cpus in MADT/GICC during
    init
  arm64: kernel: Bound the total(present+disabled) cpus with nr_cpu_ids
  arm64: kernel: Init cpu operations for all possible vcpus
  arm64: kernel: Arch specific ACPI hooks(like logical cpuid<->hwid
    etc.)

 arch/arm64/kernel/smp.c | 153 ++++++++++++++++++++++++++++++++--------
 1 file changed, 123 insertions(+), 30 deletions(-)
```
#### [RFC 0/3] virtio: NUMA-aware memory allocation
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
From patchwork Thu Jun 25 13:57:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11625403
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB4796C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:58:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2F0B206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:58:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YPKwJLXG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405145AbgFYN6E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 09:58:04 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:23056 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2404890AbgFYN6D (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 09:58:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593093482;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=a3sOV0ZHvCtW1jwkrpJy23JJcAH66RTksrishZc28jc=;
        b=YPKwJLXGrBpLwxeIymWJ+tB3RiMv/gznx0/2Sac2F5Y0Lnx3tJXOv8VXCfq19gLk2vFDbf
        NpjJtkZxgkRNI3MhnYxgRim1vwOWnV14lmd85WHqwD0Y506GEJhKVfgj+7MyNvfepec5k+
        k0I8vNa1nPQqRTO4nsx4eFLZpDXIzFE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-274-rMkuzU0sPliCfnKdECi-2w-1; Thu, 25 Jun 2020 09:57:58 -0400
X-MC-Unique: rMkuzU0sPliCfnKdECi-2w-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6E5751940920;
        Thu, 25 Jun 2020 13:57:57 +0000 (UTC)
Received: from localhost (ovpn-115-49.ams2.redhat.com [10.36.115.49])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CCF521DC;
        Thu, 25 Jun 2020 13:57:53 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC 0/3] virtio: NUMA-aware memory allocation
Date: Thu, 25 Jun 2020 14:57:49 +0100
Message-Id: <20200625135752.227293-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches are not ready to be merged because I was unable to measure a
performance improvement. I'm publishing them so they are archived in case
someone picks up this work again in the future.

The goal of these patches is to allocate virtqueues and driver state from the
device's NUMA node for optimal memory access latency. Only guests with a vNUMA
topology and virtio devices spread across vNUMA nodes benefit from this.  In
other cases the memory placement is fine and we don't need to take NUMA into
account inside the guest.

These patches could be extended to virtio_net.ko and other devices in the
future. I only tested virtio_blk.ko.

The benchmark configuration was designed to trigger worst-case NUMA placement:
 * Physical NVMe storage controller on host NUMA node 0
 * IOThread pinned to host NUMA node 0
 * virtio-blk-pci device in vNUMA node 1
 * vCPU 0 on host NUMA node 1 and vCPU 1 on host NUMA node 0
 * vCPU 0 in vNUMA node 0 and vCPU 1 in vNUMA node 1

The intent is to have .probe() code run on vCPU 0 in vNUMA node 0 (host NUMA
node 1) so that memory is in the wrong NUMA node for the virtio-blk-pci devic=
e.
Applying these patches fixes memory placement so that virtqueues and driver
state is allocated in vNUMA node 1 where the virtio-blk-pci device is located.

The fio 4KB randread benchmark results do not show a significant improvement:

Name                  IOPS   Error
virtio-blk        42373.79 =C2=B1 0.54%
virtio-blk-numa   42517.07 =C2=B1 0.79%

Stefan Hajnoczi (3):
  virtio-pci: use NUMA-aware memory allocation in probe
  virtio_ring: use NUMA-aware memory allocation in probe
  virtio-blk: use NUMA-aware memory allocation in probe

 include/linux/gfp.h                |  2 +-
 drivers/block/virtio_blk.c         |  7 +++++--
 drivers/virtio/virtio_pci_common.c | 16 ++++++++++++----
 drivers/virtio/virtio_ring.c       | 26 +++++++++++++++++---------
 mm/page_alloc.c                    |  2 +-
 5 files changed, 36 insertions(+), 17 deletions(-)

--=20
2.26.2
```
#### [PATCH v2 0/2] s390: Add API Docs for DIAGNOSE 0x318 and fix rst
##### From: Collin Walling <walling@linux.ibm.com>

```c
From patchwork Thu Jun 25 15:07:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11625529
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 621636C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 15:07:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5357C20767
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 15:07:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405751AbgFYPHm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 11:07:42 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:26216 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2405552AbgFYPHl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 11:07:41 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05PF2LQ7116909;
        Thu, 25 Jun 2020 11:07:40 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31uwyg381f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 11:07:39 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05PF2Lon116917;
        Thu, 25 Jun 2020 11:07:39 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31uwyg3814-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 11:07:39 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05PF6DJR020140;
        Thu, 25 Jun 2020 15:07:38 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma04wdc.us.ibm.com with ESMTP id 31uurycwka-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 15:07:38 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 05PF7aX848759276
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Jun 2020 15:07:36 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3E5D2AC05F;
        Thu, 25 Jun 2020 15:07:36 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0624DAC05B;
        Thu, 25 Jun 2020 15:07:36 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.202.75])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 25 Jun 2020 15:07:35 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v2 0/2] s390: Add API Docs for DIAGNOSE 0x318 and fix rst
Date: Thu, 25 Jun 2020 11:07:22 -0400
Message-Id: <20200625150724.10021-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-25_10:2020-06-25,2020-06-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 suspectscore=0
 impostorscore=0 mlxlogscore=876 mlxscore=0 priorityscore=1501 phishscore=0
 malwarescore=0 cotscore=-2147483648 lowpriorityscore=0 bulkscore=0
 clxscore=1015 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006250095
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changelog:

    v2

    • Reworded patch 1 doc text

    • Added "Introduced in commit..." for rst fix patch

    • Added r-b's (thanks!)

Adds documentation for the s390-specfic DIAGNOSE 0x318 instruction, as
well as fixes some missing rst symbols for the neighboring entries.

Suggested-by: Cornelia Huck <cohuck@redhat.com>

Collin Walling (2):
  docs: kvm: add documentation for KVM_CAP_S390_DIAG318
  docs: kvm: fix rst formatting

 Documentation/virt/kvm/api.rst | 27 ++++++++++++++++++++++++---
 1 file changed, 24 insertions(+), 3 deletions(-)
```
