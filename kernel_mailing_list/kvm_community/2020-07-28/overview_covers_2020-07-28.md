

#### [PATCH 0/6 v3] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Jul 28 00:10:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11687815
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB81C912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:11:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88CAB20786
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:11:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="aJhYidgm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726247AbgG1ALL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 20:11:11 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:49118 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726139AbgG1ALL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jul 2020 20:11:11 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06S098BN046564;
        Tue, 28 Jul 2020 00:11:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=V7WMCBrSZ6HfjHK+KspJqk0BoQ25m/xsnx1QvbrhVlY=;
 b=aJhYidgmty1PWqM0Mc/1fqeqAZJk8i7MMC4CY+DxJbmB7nyFYNeGWidBy3W4p/T9+Q2w
 wngxgyhUNbJVbW+8eiqKKkNpIaaTbe1kVDi45rZqmFko1zpq7GOTaeWE+6fDCrGOOYKi
 wMS9xlyO8ghMHs+bSjVrmLmMICXgIm9lN8sDvqfB7qkzYNrZWrPhYBkTXJsLufQ2q8R1
 ED2LpohLVS86r7ThWM5QLDSq9pI0MfB8yuxkcCAF2dydBQ0TLTo/DTNqaLOfww768xyk
 3xZu6pTBb2MNprdnr2H+7EuuHBEBvs8whr/BEnz1TcP/s6RtFyHU86WQK0ncc+8gzq8/ Zw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 32hu1j4g70-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 28 Jul 2020 00:11:01 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06S08XC6157192;
        Tue, 28 Jul 2020 00:11:00 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 32hu5rvkm8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 28 Jul 2020 00:11:00 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 06S0AxmL030981;
        Tue, 28 Jul 2020 00:10:59 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 27 Jul 2020 17:10:59 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com, qemu-devel@nongnu.org
Subject: [PATCH 0/6 v3] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
 {vmx|svm}_nested_ops via macros
Date: Tue, 28 Jul 2020 00:10:44 +0000
Message-Id: <1595895050-105504-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9695
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 bulkscore=0
 malwarescore=0 suspectscore=1 spamscore=0 mlxlogscore=618 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007270165
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9695
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 bulkscore=0 mlxlogscore=634
 lowpriorityscore=0 malwarescore=0 clxscore=1015 mlxscore=0 impostorscore=0
 phishscore=0 adultscore=0 suspectscore=1 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007270165
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	1. kvm_arch_hardware_unsetup() is changed to
	   kvm_arch_hardware_teardown() on non-x86 arches as well.

	2. The following #defines

		KVM_MEMORY_ENCRYPT_OP
		KVM_MEMORY_ENCRYPT_REG_REGION
	   	KVM_MEMORY_ENCRYPT_UNREG_REGION

	   have been changed to:

		KVM_MEM_ENC_OP
		KVM_MEM_ENC_REGISTER_REGION
		KVM_MEM_ENC_UNREGISTER_REGION

	3. Patch# 6 is new. It changes the KVM_MEMORY_ENCRYPT_* #defines in
	   QEMU to make them conformant to those in the kernel.


[PATCH 1/6 v3] KVM: x86: Change names of some of the kvm_x86_ops
[PATCH 2/6 v3] KVM: SVM: Fill in conforming svm_x86_ops via macro
[PATCH 3/6 v3] KVM: nSVM: Fill in conforming svm_nested_ops via macro
[PATCH 4/6 v3] KVM: VMX: Fill in conforming vmx_x86_ops via macro
[PATCH 5/6 v3] KVM: nVMX: Fill in conforming vmx_nested_ops via macro
[PATCH 6/6 v3] QEMU: x86: Change KVM_MEMORY_ENCRYPT_*  #defines to make them

 arch/arm64/include/asm/kvm_host.h   |   2 +-
 arch/mips/include/asm/kvm_host.h    |   2 +-
 arch/powerpc/include/asm/kvm_host.h |   2 +-
 arch/s390/kvm/kvm-s390.c            |   2 +-
 arch/x86/include/asm/kvm_host.h     |  12 +-
 arch/x86/kvm/svm/avic.c             |   4 +-
 arch/x86/kvm/svm/nested.c           |  18 +--
 arch/x86/kvm/svm/sev.c              |   6 +-
 arch/x86/kvm/svm/svm.c              | 218 +++++++++++++++++----------------
 arch/x86/kvm/svm/svm.h              |   8 +-
 arch/x86/kvm/vmx/nested.c           |  26 ++--
 arch/x86/kvm/vmx/nested.h           |   2 +-
 arch/x86/kvm/vmx/vmx.c              | 238 ++++++++++++++++++------------------
 arch/x86/kvm/vmx/vmx.h              |   2 +-
 arch/x86/kvm/x86.c                  |  28 ++---
 include/linux/kvm_host.h            |   2 +-
 include/uapi/linux/kvm.h            |   6 +-
 tools/include/uapi/linux/kvm.h      |   6 +-
 virt/kvm/kvm_main.c                 |   4 +-
 19 files changed, 298 insertions(+), 290 deletions(-)

Krish Sadhukhan (5):
      KVM: x86: Change names of some of the kvm_x86_ops functions to make them m
      KVM: SVM: Fill in conforming svm_x86_ops via macro
      KVM: nSVM: Fill in conforming svm_nested_ops via macro
      KVM: VMX: Fill in conforming vmx_x86_ops via macro
      KVM: nVMX: Fill in conforming vmx_nested_ops via macro

 target/i386/sev.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

Krish Sadhukhan (1):
      QEMU: x86: Change KVM_MEMORY_ENCRYPT_*  #defines to make them conformant t
```
#### [PATCH V4 0/6] IRQ offloading for vDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Tue Jul 28 04:23:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11688087
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E6CE722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 04:28:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0AFE2206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 04:28:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726299AbgG1E2K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 00:28:10 -0400
Received: from mga18.intel.com ([134.134.136.126]:58408 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725851AbgG1E2K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 00:28:10 -0400
IronPort-SDR: 
 f7SOb9lqMiarA5gkX+CljDMVI0E7qLJfOHLZHcIAzTBDmha014wPxaU8p0Xd23elvbv8J6M9F5
 aef50eO3ti/g==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="138665747"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="138665747"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 21:28:09 -0700
IronPort-SDR: 
 xeUqyBN6CpOAJrUyAF0sVjtt78TIm171Ub7DFnAvWAc1MHPnEBw9A3F9dRG2NWEfjiJkovt9fm
 ue6vjhU0aGuQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="290037157"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga006.jf.intel.com with ESMTP; 27 Jul 2020 21:28:04 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 0/6] IRQ offloading for vDPA
Date: Tue, 28 Jul 2020 12:23:59 +0800
Message-Id: <20200728042405.17579-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to implement IRQ offloading for
vhost_vdpa.

By the feat of irq forwarding facilities like posted
interrupt on X86, irq bypass can  help deliver
interrupts to vCPU directly.

vDPA devices have dedicated hardware backends like VFIO
pass-throughed devices. So it would be possible to setup
irq offloading(irq bypass) for vDPA devices and gain
performance improvements.

In my testing, with this feature, we can save 0.1ms
in a ping between two VFs on average.
changes from V3:
(1)removed vDPA irq allocate/free helpers in vDPA core.
(2)add a new function get_vq_irq() in struct vdpa_config_ops,
upper layer driver can use this function to: A. query the
irq numbner of a vq. B. detect whether a vq is enabled.
(3)implement get_vq_irq() in ifcvf driver.
(4)in vhost_vdpa, set_status() will setup irq offloading when
setting DRIVER_OK, and unsetup when receive !DRIVER_OK.
(5)minor improvements.

changes from V2:
(1)rename struct vhost_call_ctx to vhost_vring_call
(2)add kvm_arch_end_assignment() in del_producer()
code path
(3)rename vDPA helpers to vdpa_devm_request_irq()
and vdpa_devm_free_irq(). Add better comments
for them.
(4)better comments for setup_vq_irq() and
unsetup_vq_irq()
(5)In vDPA VHOST_SET_VRING_CALL, will call vhost_vdpa_update_vq_irq()
without checking producer.irq, move this check into
vhost_vdpa_update_vq_irq(), so that get advantage of the spinlock.
(6)Add a function vhost_vdpa_clean_irq(), this function will unregister
the producer of vqs when vhost_vdpa_release(). This is safe
for control vq.
(7) minor improvements

changes from V1:
(1)dropped vfio changes.
(3)removed KVM_HVAE_IRQ_BYPASS checks
(4)locking fixes
(5)simplified vhost_vdpa_updat


Zhu Lingshan (6):
  vhost: introduce vhost_vring_call
  kvm: detect assigned device via irqbypass manager
  vDPA: add get_vq_irq() in vdpa_config_ops
  vhost_vdpa: implement IRQ offloading in vhost_vdpa
  ifcvf: implement vdpa_config_ops.get_vq_irq()
  irqbypass: do not start cons/prod when failed connect

 arch/x86/kvm/x86.c              | 12 ++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 18 ++++++-
 drivers/vhost/Kconfig           |  1 +
 drivers/vhost/vdpa.c            | 83 +++++++++++++++++++++++++++++++--
 drivers/vhost/vhost.c           | 22 ++++++---
 drivers/vhost/vhost.h           |  9 +++-
 include/linux/vdpa.h            |  6 +++
 virt/lib/irqbypass.c            | 16 ++++---
 8 files changed, 147 insertions(+), 20 deletions(-)
```
#### [PATCH v6 00/15] vfio: expose virtual Shared Virtual Addressing to
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Tue Jul 28 06:27:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11688331
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 425C0138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:22:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2DA0D21744
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:22:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727051AbgG1GU4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 02:20:56 -0400
Received: from mga06.intel.com ([134.134.136.31]:26362 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726797AbgG1GU4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 02:20:56 -0400
IronPort-SDR: 
 YjjR2wcfzydZ7E/DK6ayQQl4eiyUofys18EBusI2y2arzUCebWdVxU9Ada5TrlMkODuMJv6Jus
 AP4kwt8MO3vA==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="212681237"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="212681237"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 23:20:55 -0700
IronPort-SDR: 
 1R39JSLKZPY/jvYAqc2FiYUhyk4zIpzPhvlm+gQ8r/A7hesyzH4vUVqpSzLgdgTY8jaHP1qsWV
 FFgP2ywW5Srg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="320274385"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 27 Jul 2020 23:20:55 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v6 00/15] vfio: expose virtual Shared Virtual Addressing to
 VMs
Date: Mon, 27 Jul 2020 23:27:29 -0700
Message-Id: <1595917664-33276-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This VFIO series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes. For IOMMU and QEMU changes, they are in separate series (listed
in the "Related series").

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.


    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

Patch Overview:
 1. a refactor to vfio_iommu_type1 ioctl (patch 0001)
 2. reports IOMMU nesting info to userspace ( patch 0002, 0003, 0004 and 0015)
 3. vfio support for PASID allocation and free for VMs (patch 0005, 0006, 0007)
 4. vfio support for binding guest page table to host (patch 0008, 0009, 0010)
 5. vfio support for IOMMU cache invalidation from VMs (patch 0011)
 6. vfio support for vSVA usage on IOMMU-backed mdevs (patch 0012)
 7. expose PASID capability to VM (patch 0013)
 8. add doc for VFIO dual stage control (patch 0014)

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This patchset is aiming for the phase 1 and phase 2, and based on Jacob's
below series.
*) [PATCH v6 0/6] IOMMU user API enhancement - wip
   https://lore.kernel.org/linux-iommu/1595525140-23899-1-git-send-email-jacob.jun.pan@linux.intel.com/

*) [PATCH 00/10] IOASID extensions for guest SVA - wip
   https://lore.kernel.org/linux-iommu/1585158931-1825-1-git-send-email-jacob.jun.pan@linux.intel.com/

The latest IOASID code added below new interface for itertate all PASIDs of an
ioasid_set. The implementation is not sent out yet as Jacob needs some cleanup,
it can be found in branch vsva-linux-5.8-rc6-v6 on github (mentioned below):
 int ioasid_set_for_each_ioasid(int sid, void (*fn)(ioasid_t id, void *data), void *data);

Complete set for current vSVA can be found in below branch.
https://github.com/luxis1999/linux-vsva.git: vsva-linux-5.8-rc6-v6

The corresponding QEMU patch series is included in below branch:
https://github.com/luxis1999/qemu.git: vsva_5.8_rc6_qemu_rfcv9


Regards,
Yi Liu

Changelog:
	- Patch v5 -> Patch v6:
	  a) Address comments against v5 from Eric.
	  b) rebase on Jacob's v6 IOMMU uapi enhancement
	  Patch v5: https://lore.kernel.org/kvm/1594552870-55687-1-git-send-email-yi.l.liu@intel.com/

	- Patch v4 -> Patch v5:
	  a) Address comments against v4
	  Patch v4: https://lore.kernel.org/kvm/1593861989-35920-1-git-send-email-yi.l.liu@intel.com/

	- Patch v3 -> Patch v4:
	  a) Address comments against v3
	  b) Add rb from Stefan on patch 14/15
	  Patch v3: https://lore.kernel.org/linux-iommu/1592988927-48009-1-git-send-email-yi.l.liu@intel.com/

	- Patch v2 -> Patch v3:
	  a) Rebase on top of Jacob's v3 iommu uapi patchset
	  b) Address comments from Kevin and Stefan Hajnoczi
	  c) Reuse DOMAIN_ATTR_NESTING to get iommu nesting info
	  d) Drop [PATCH v2 07/15] iommu/uapi: Add iommu_gpasid_unbind_data
	  Patch v2: https://lore.kernel.org/linux-iommu/1591877734-66527-1-git-send-email-yi.l.liu@intel.com/#r

	- Patch v1 -> Patch v2:
	  a) Refactor vfio_iommu_type1_ioctl() per suggestion from Christoph
	     Hellwig.
	  b) Re-sequence the patch series for better bisect support.
	  c) Report IOMMU nesting cap info in detail instead of a format in
	     v1.
	  d) Enforce one group per nesting type container for vfio iommu type1
	     driver.
	  e) Build the vfio_mm related code from vfio.c to be a separate
	     vfio_pasid.ko.
	  f) Add PASID ownership check in IOMMU driver.
	  g) Adopted to latest IOMMU UAPI design. Removed IOMMU UAPI version
	     check. Added iommu_gpasid_unbind_data for unbind requests from
	     userspace.
	  h) Define a single ioctl:VFIO_IOMMU_NESTING_OP for bind/unbind_gtbl
	     and cahce_invld.
	  i) Document dual stage control in vfio.rst.
	  Patch v1: https://lore.kernel.org/linux-iommu/1584880325-10561-1-git-send-email-yi.l.liu@intel.com/

	- RFC v3 -> Patch v1:
	  a) Address comments to the PASID request(alloc/free) path
	  b) Report PASID alloc/free availabitiy to user-space
	  c) Add a vfio_iommu_type1 parameter to support pasid quota tuning
	  d) Adjusted to latest ioasid code implementation. e.g. remove the
	     code for tracking the allocated PASIDs as latest ioasid code
	     will track it, VFIO could use ioasid_free_set() to free all
	     PASIDs.
	  RFC v3: https://lore.kernel.org/linux-iommu/1580299912-86084-1-git-send-email-yi.l.liu@intel.com/

	- RFC v2 -> v3:
	  a) Refine the whole patchset to fit the roughly parts in this series
	  b) Adds complete vfio PASID management framework. e.g. pasid alloc,
	  free, reclaim in VM crash/down and per-VM PASID quota to prevent
	  PASID abuse.
	  c) Adds IOMMU uAPI version check and page table format check to ensure
	  version compatibility and hardware compatibility.
	  d) Adds vSVA vfio support for IOMMU-backed mdevs.
	  RFC v2: https://lore.kernel.org/linux-iommu/1571919983-3231-1-git-send-email-yi.l.liu@intel.com/

	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.
	  RFC v1: https://lore.kernel.org/linux-iommu/1562324772-3084-1-git-send-email-yi.l.liu@intel.com/
---
Eric Auger (1):
  vfio: Document dual stage control

Liu Yi L (13):
  vfio/type1: Refactor vfio_iommu_type1_ioctl()
  iommu: Report domain nesting info
  iommu/smmu: Report empty domain nesting info
  vfio/type1: Report iommu nesting info to userspace
  vfio: Add PASID allocation/free support
  iommu/vt-d: Support setting ioasid set to domain
  vfio/type1: Add VFIO_IOMMU_PASID_REQUEST (alloc/free)
  iommu/vt-d: Check ownership for PASIDs from user-space
  vfio/type1: Support binding guest page tables to PASID
  vfio/type1: Allow invalidating first-level/stage IOMMU cache
  vfio/type1: Add vSVA support for IOMMU-backed mdevs
  vfio/pci: Expose PCIe PASID capability to guest
  iommu/vt-d: Support reporting nesting capability info

Yi Sun (1):
  iommu: Pass domain to sva_unbind_gpasid()

 Documentation/driver-api/vfio.rst  |  75 ++++
 drivers/iommu/arm-smmu-v3.c        |  29 +-
 drivers/iommu/arm-smmu.c           |  29 +-
 drivers/iommu/intel/iommu.c        | 114 +++++-
 drivers/iommu/intel/svm.c          |  10 +-
 drivers/iommu/iommu.c              |   2 +-
 drivers/vfio/Kconfig               |   6 +
 drivers/vfio/Makefile              |   1 +
 drivers/vfio/pci/vfio_pci_config.c |   2 +-
 drivers/vfio/vfio_iommu_type1.c    | 796 ++++++++++++++++++++++++++++---------
 drivers/vfio/vfio_pasid.c          | 284 +++++++++++++
 include/linux/intel-iommu.h        |  23 +-
 include/linux/iommu.h              |   4 +-
 include/linux/vfio.h               |  54 +++
 include/uapi/linux/iommu.h         |  74 ++++
 include/uapi/linux/vfio.h          |  90 +++++
 16 files changed, 1391 insertions(+), 202 deletions(-)
 create mode 100644 drivers/vfio/vfio_pasid.c
```
#### [RFC v9 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Tue Jul 28 06:33:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11688343
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 73184138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:27:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E2FF207E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:27:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727850AbgG1G1m (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 02:27:42 -0400
Received: from mga09.intel.com ([134.134.136.24]:37256 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727044AbgG1G1l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 02:27:41 -0400
IronPort-SDR: 
 VwslsurwU66M3MpinyUFRsFHC/uyuUDgjmM8uBLTCatJhJxWsDIgLYsfCj125wfvid9HSoCt9R
 SCuttd/xd1Yg==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="152412000"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="152412000"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 23:27:30 -0700
IronPort-SDR: 
 lmy+35fvmLsFNUC4IDqmne35X8OPyfvw3RtwpdI+VbJjV3Fu6FrmqKcPf86yN8fgZoijbFSge9
 ZqBexd2QBkOA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="394232772"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga001.fm.intel.com with ESMTP; 27 Jul 2020 23:27:29 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com, jasowang@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org
Subject: [RFC v9 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
Date: Mon, 27 Jul 2020 23:33:53 -0700
Message-Id: <1595918058-33392-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This QEMU series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes.

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.

    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This QEMU patchset is aiming for the phase 1 and phase 2. It is based
on the kernel series below:
[PATCH v6 00/15] vfio: expose virtual Shared Virtual Addressing to VMs
https://lore.kernel.org/kvm/1595917664-33276-1-git-send-email-yi.l.liu@intel.com/#t

Patch Overview:
 1. patch 0001 - 0002: update kernel header files
 2. patch 0003 - 0007: select VFIO_TYPE1_NESTING_IOMMU for vIOMMU built
                       on IOMMU nesting translation.
 3. patch 0008 - 0010: set HostIOMMUContext to vIOMMU.
 4. patch 0011 - 0013: allocate PASID for vIOMMU.
 5. patch 0014 - 0015: PASID cache management for Intel vIOMMU.
 6. patch 0016 - 0020: bind guest page table to host.
 7. patch 0021 - 0024: flush first level/stage cache for vIOMMU.
 8. patch 0025: expose SVA to VM by x-scalable-mode="modern"

The complete QEMU set can be found in below link:
https://github.com/luxis1999/qemu.git vsva_5.8_rc6_qemu_rfcv9

Complete kernel can be found in:
https://github.com/luxis1999/linux-vsva.git vsva-linux-5.8-rc6-v6

Tests: basci vSVA functionality test, VM reboot/shutdown/crash, kernel build in
guest, boot VM with vSVA disabled, full comapilation with all archs, passthru
entire PCI device, passthru Scalable IOV ADI.

Regards,
Yi Liu

Changelog:
	- RFC v8 -> RFC v9:
	  a) Rebase to latest kernel implementation (5.8-rc6 vsva v6)
	  RFC v8: https://lore.kernel.org/kvm/1594553181-55810-1-git-send-email-yi.l.liu@intel.com/

	- RFC v7 -> RFC v8:
	  a) Rebase to latest kernel implementation (5.8-rc3 vsva v5)
	  RFC v7: https://lore.kernel.org/kvm/1593862609-36135-1-git-send-email-yi.l.liu@intel.com/

	- RFC v6 -> RFC v7:
	  a) Rebase to latest kernel implementation (5.8-rc3 vsva)
	  RFC v6: https://lore.kernel.org/kvm/1591880064-30638-1-git-send-email-yi.l.liu@intel.com/

	- RFC v5 -> RFC v6:
	  a) Use RFC instead of formal patch as kernel patch is in progress.
	  b) Address comments from Peter and Eric.
	  c) Add get_iommu_attr() to advertise vIOMMU nesting requirement to
	     VFIO.
	  d) Update per latest kernel UAPI definition.
	  e) Add patch 0017 to check iommu nesting cap info in set_iommu().
	  RFC v5: https://www.spinics.net/lists/kvm/msg211475.html

	- RFC v4 -> RFC v5:
	  a) Refactor the vfio HostIOMMUContext init code (patch 0008 - 0009 of v1 series)
	  b) Refactor the pasid binding handling (patch 0011 - 0016 of v1 series)
	  RFC v4: https://patchwork.ozlabs.org/cover/1259648/

	- RFC v3.1 -> RFC v4:
	  a) Implement HostIOMMUContext in QOM manner.
	  b) Add pci_set/unset_iommu_context() to register HostIOMMUContext to
	     vIOMMU, thus the lifecircle of HostIOMMUContext is awared in vIOMMU
	     side. In such way, vIOMMU could use the methods provided by the
	     HostIOMMUContext safely.
	  c) Add back patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3.1: https://patchwork.kernel.org/cover/11397879/

	- RFC v3 -> v3.1:
	  a) Drop IOMMUContext, and rename DualStageIOMMUObject to HostIOMMUContext.
	     HostIOMMUContext is per-vfio-container, it is exposed to  vIOMMU via PCI
	     layer. VFIO registers a PCIHostIOMMUFunc callback to PCI layer, vIOMMU
	     could get HostIOMMUContext instance via it.
	  b) Check IOMMU uAPI version by VFIO_CHECK_EXTENSION
	  c) Add a check on VFIO_PASID_REQ availability via VFIO_GET_IOMMU_IHNFO
	  d) Reorder the series, put vSVA linux header file update in the beginning
	     put the x-scalable-mode option mofification in the end of the series.
	  e) Dropped patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3: https://patchwork.kernel.org/cover/11356033/

	- RFC v2 -> v3:
	  a) Introduce DualStageIOMMUObject to abstract the host IOMMU programming
	  capability. e.g. request PASID from host, setup IOMMU nesting translation
	  on host IOMMU. The pasid_alloc/bind_guest_page_table/iommu_cache_flush
	  operations are moved to be DualStageIOMMUOps. Thus, DualStageIOMMUObject
	  is an abstract layer which provides QEMU vIOMMU emulators with an explicit
	  method to program host IOMMU.
	  b) Compared with RFC v2, the IOMMUContext has also been updated. It is
	  modified to provide an abstract for vIOMMU emulators. It provides the
	  method for pass-through modules (like VFIO) to communicate with host IOMMU.
	  e.g. tell vIOMMU emulators about the IOMMU nesting capability on host side
	  and report the host IOMMU DMA translation faults to vIOMMU emulators.
	  RFC v2: https://www.spinics.net/lists/kvm/msg198556.html

	- RFC v1 -> v2:
	  Introduce IOMMUContext to abstract the connection between VFIO
	  and vIOMMU emulators, which is a replacement of the PCIPASIDOps
	  in RFC v1. Modify x-scalable-mode to be string option instead of
	  adding a new option as RFC v1 did. Refined the pasid cache management
---
Eric Auger (1):
  scripts/update-linux-headers: Import iommu.h

Liu Yi L (24):
  header file update VFIO/IOMMU vSVA APIs kernel 5.8-rc6
  hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
  hw/pci: introduce pci_device_get_iommu_attr()
  intel_iommu: add get_iommu_attr() callback
  vfio: pass nesting requirement into vfio_get_group()
  vfio: check VFIO_TYPE1_NESTING_IOMMU support
  hw/iommu: introduce HostIOMMUContext
  hw/pci: introduce pci_device_set/unset_iommu_context()
  intel_iommu: add set/unset_iommu_context callback
  vfio/common: provide PASID alloc/free hooks
  vfio: init HostIOMMUContext per-container
  intel_iommu: add virtual command capability support
  intel_iommu: process PASID cache invalidation
  intel_iommu: add PASID cache management infrastructure
  vfio: add bind stage-1 page table support
  intel_iommu: sync IOMMU nesting cap info for assigned devices
  intel_iommu: bind/unbind guest page table to host
  intel_iommu: replay pasid binds after context cache invalidation
  intel_iommu: do not pass down pasid bind for PASID #0
  vfio: add support for flush iommu stage-1 cache
  intel_iommu: process PASID-based iotlb invalidation
  intel_iommu: propagate PASID-based iotlb invalidation to host
  intel_iommu: process PASID-based Device-TLB invalidation
  intel_iommu: modify x-scalable-mode to be string option

 hw/Makefile.objs                      |    1 +
 hw/alpha/typhoon.c                    |    6 +-
 hw/arm/smmu-common.c                  |    6 +-
 hw/hppa/dino.c                        |    6 +-
 hw/i386/amd_iommu.c                   |    6 +-
 hw/i386/intel_iommu.c                 | 1233 ++++++++++++++++++++++++++++++++-
 hw/i386/intel_iommu_internal.h        |  131 ++++
 hw/i386/trace-events                  |    6 +
 hw/iommu/Makefile.objs                |    1 +
 hw/iommu/host_iommu_context.c         |  171 +++++
 hw/pci-host/designware.c              |    6 +-
 hw/pci-host/pnv_phb3.c                |    6 +-
 hw/pci-host/pnv_phb4.c                |    6 +-
 hw/pci-host/ppce500.c                 |    6 +-
 hw/pci-host/prep.c                    |    6 +-
 hw/pci-host/sabre.c                   |    6 +-
 hw/pci/pci.c                          |   73 +-
 hw/ppc/ppc440_pcix.c                  |    6 +-
 hw/ppc/spapr_pci.c                    |    6 +-
 hw/s390x/s390-pci-bus.c               |    8 +-
 hw/vfio/ap.c                          |    2 +-
 hw/vfio/ccw.c                         |    2 +-
 hw/vfio/common.c                      |  299 +++++++-
 hw/vfio/pci.c                         |   26 +-
 hw/vfio/platform.c                    |    2 +-
 hw/virtio/virtio-iommu.c              |    6 +-
 include/hw/i386/intel_iommu.h         |   61 +-
 include/hw/iommu/host_iommu_context.h |  103 +++
 include/hw/pci/pci.h                  |   25 +-
 include/hw/pci/pci_bus.h              |    2 +-
 include/hw/vfio/vfio-common.h         |    7 +-
 linux-headers/linux/iommu.h           |  409 +++++++++++
 linux-headers/linux/vfio.h            |   92 ++-
 scripts/update-linux-headers.sh       |    2 +-
 34 files changed, 2673 insertions(+), 61 deletions(-)
 create mode 100644 hw/iommu/Makefile.objs
 create mode 100644 hw/iommu/host_iommu_context.c
 create mode 100644 include/hw/iommu/host_iommu_context.h
 create mode 100644 linux-headers/linux/iommu.h
```
#### [PATCH 0/3] KVM: x86: KVM_MEM_PCI_HOLE memory
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Jul 28 14:37:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11689267
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2AFFF1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 14:38:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13BFE206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 14:38:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="S/AS6Qzh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730462AbgG1Oh5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 10:37:57 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:53599 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730451AbgG1Oh5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 10:37:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595947075;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=8QXSO/i3jp95ipr7aX72WVFqXrse1Eq2BTavylZNpEE=;
        b=S/AS6QzhbunpS8am5UDnjZqHK2Wg4Ha1Gm1LxYfejkn093SoJpg6mxJI702M5ueNNLVRlk
        +5tevpTQpczZBem2pQ/FHfXJQOPyopnFJAnLoZGG6R0ghCdx+11WW/CtQWyhVnDJkQ5lXG
        yZeGQhWWwkoywPcJwOT9bnC6FIvlM5o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-349-w2s9GueHMyORLL8X2rDX-Q-1; Tue, 28 Jul 2020 10:37:54 -0400
X-MC-Unique: w2s9GueHMyORLL8X2rDX-Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A0DFC1932480;
        Tue, 28 Jul 2020 14:37:52 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.70])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D47DE90E84;
        Tue, 28 Jul 2020 14:37:42 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Xu <peterx@redhat.com>, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Andy Lutomirski <luto@kernel.org>, linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: x86: KVM_MEM_PCI_HOLE memory
Date: Tue, 28 Jul 2020 16:37:38 +0200
Message-Id: <20200728143741.2718593-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a continuation of "[PATCH RFC 0/5] KVM: x86: KVM_MEM_ALLONES
memory" work: 
https://lore.kernel.org/kvm/20200514180540.52407-1-vkuznets@redhat.com/
and pairs with Julia's "x86/PCI: Use MMCONFIG by default for KVM guests":
https://lore.kernel.org/linux-pci/20200722001513.298315-1-jusual@redhat.com/

PCIe config space can (depending on the configuration) be quite big but
usually is sparsely populated. Guest may scan it by accessing individual
device's page which, when device is missing, is supposed to have 'pci
hole' semantics: reads return '0xff' and writes get discarded.

When testing Linux kernel boot with QEMU q35 VM and direct kernel boot
I observed 8193 accesses to PCI hole memory. When such exit is handled
in KVM without exiting to userspace, it takes roughly 0.000001 sec.
Handling the same exit in userspace is six times slower (0.000006 sec) so
the overal; difference is 0.04 sec. This may be significant for 'microvm'
ideas.

Note, the same speed can already be achieved by using KVM_MEM_READONLY
but doing this would require allocating real memory for all missing
devices and e.g. 8192 pages gives us 32mb. This will have to be allocated
for each guest separately and for 'microvm' use-cases this is likely
a no-go.

Introduce special KVM_MEM_PCI_HOLE memory: userspace doesn't need to
back it with real memory, all reads from it are handled inside KVM and
return '0xff'. Writes still go to userspace but these should be extremely
rare.

The original 'KVM_MEM_ALLONES' idea had additional optimizations: KVM
was mapping all 'PCI hole' pages to a single read-only page stuffed with
0xff. This is omitted in this submission as the benefits are unclear:
KVM will have to allocate SPTEs (either on demand or aggressively) and
this also consumes time/memory. We can always take a look at possible
optimizations later.

Vitaly Kuznetsov (3):
  KVM: x86: move kvm_vcpu_gfn_to_memslot() out of try_async_pf()
  KVM: x86: introduce KVM_MEM_PCI_HOLE memory
  KVM: selftests: add KVM_MEM_PCI_HOLE test

 Documentation/virt/kvm/api.rst                |  19 ++-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/mmu/mmu.c                        |  19 +--
 arch/x86/kvm/mmu/paging_tmpl.h                |  10 +-
 arch/x86/kvm/x86.c                            |  10 +-
 include/linux/kvm_host.h                      |   7 +-
 include/uapi/linux/kvm.h                      |   3 +-
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  81 +++++++------
 .../kvm/x86_64/memory_slot_pci_hole.c         | 112 ++++++++++++++++++
 virt/kvm/kvm_main.c                           |  39 ++++--
 12 files changed, 243 insertions(+), 60 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/memory_slot_pci_hole.c
```
