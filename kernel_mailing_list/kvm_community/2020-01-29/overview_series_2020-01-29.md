#### [RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11356037
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A770692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:11:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7CB6720720
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:11:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726347AbgA2MLo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:11:44 -0500
Received: from mga04.intel.com ([192.55.52.120]:15927 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726177AbgA2MLo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:11:44 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:11:43 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="314070761"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga001.fm.intel.com with ESMTP; 29 Jan 2020 04:11:43 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, david@gibson.dropbear.id.au,
        pbonzini@redhat.com, alex.williamson@redhat.com, peterx@redhat.com
Cc: mst@redhat.com, eric.auger@redhat.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, jun.j.tian@intel.com, yi.y.sun@intel.com,
        kvm@vger.kernel.org, hao.wu@intel.com,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>
Subject: [RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
Date: Wed, 29 Jan 2020 04:16:32 -0800
Message-Id: <1580300216-86172-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1580300216-86172-1-git-send-email-yi.l.liu@intel.com>
References: <1580300216-86172-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@intel.com>

This patch modifies pci_setup_iommu() to set PCIIOMMUOps
instead of setting PCIIOMMUFunc. PCIIOMMUFunc is used to
get an address space for a PCI device in vendor specific
way. The PCIIOMMUOps still offers this functionality. But
using PCIIOMMUOps leaves space to add more iommu related
vendor specific operations.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: David Gibson <david@gibson.dropbear.id.au>
Cc: Michael S. Tsirkin <mst@redhat.com>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 hw/alpha/typhoon.c       |  6 +++++-
 hw/arm/smmu-common.c     |  6 +++++-
 hw/hppa/dino.c           |  6 +++++-
 hw/i386/amd_iommu.c      |  6 +++++-
 hw/i386/intel_iommu.c    |  6 +++++-
 hw/pci-host/designware.c |  6 +++++-
 hw/pci-host/ppce500.c    |  6 +++++-
 hw/pci-host/prep.c       |  6 +++++-
 hw/pci-host/sabre.c      |  6 +++++-
 hw/pci/pci.c             | 12 +++++++-----
 hw/ppc/ppc440_pcix.c     |  6 +++++-
 hw/ppc/spapr_pci.c       |  6 +++++-
 hw/s390x/s390-pci-bus.c  |  8 ++++++--
 include/hw/pci/pci.h     |  8 ++++++--
 include/hw/pci/pci_bus.h |  2 +-
 15 files changed, 75 insertions(+), 21 deletions(-)

```
#### [PATCH v8 1/4] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11356759
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2BCA112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 20:03:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 819392067C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 20:03:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727337AbgA2UDa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 15:03:30 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15386 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726259AbgA2UDa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Jan 2020 15:03:30 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00TJtMRF042646
        for <kvm@vger.kernel.org>; Wed, 29 Jan 2020 15:03:29 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xttnu23x4-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 29 Jan 2020 15:03:28 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 29 Jan 2020 20:03:27 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 29 Jan 2020 20:03:23 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00TK3N3v61472808
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 29 Jan 2020 20:03:23 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E4A6911C04A;
        Wed, 29 Jan 2020 20:03:22 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 384A211C054;
        Wed, 29 Jan 2020 20:03:21 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.2.173])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 29 Jan 2020 20:03:20 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v8 1/4] KVM: s390: Add new reset vcpu API
Date: Wed, 29 Jan 2020 15:03:09 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200129200312.3200-1-frankja@linux.ibm.com>
References: <20200129200312.3200-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012920-0012-0000-0000-00000381D9A3
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012920-0013-0000-0000-000021BE3206
Message-Id: <20200129200312.3200-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-29_06:2020-01-28,2020-01-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 malwarescore=0
 spamscore=0 impostorscore=0 phishscore=0 bulkscore=0 suspectscore=1
 adultscore=0 priorityscore=1501 mlxlogscore=999 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001290154
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virt/kvm/api.txt |  43 ++++++++++++++
 arch/s390/kvm/kvm-s390.c       | 103 +++++++++++++++++++++++----------
 include/uapi/linux/kvm.h       |   5 ++
 3 files changed, 122 insertions(+), 29 deletions(-)

```
#### [RFC] eventfd: add EFD_AUTORESET flag
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11356623
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5C0B13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 17:20:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B9F552071E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 17:20:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gdkONAdz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727141AbgA2RUq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 12:20:46 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:30756 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726906AbgA2RUq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Jan 2020 12:20:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580318442;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CDEy69IL/eMYtpmDS3XjUwKwXrl7W0ck1hqzenez+2c=;
        b=gdkONAdzy+pd4yBkwcpuqpZLD1tKOLuPAfVsUnlWO7rcuC1kTdGJKLdue/bsmp/OY7xuYs
        5cFgLjxxDhHJ1+JIjQMxTbQuH9riVpH97zM1ktcYGcOhHaTyfjwadxP5SNI/i5/7XhPWd8
        CXIujZGQTeQw/kl/4HEv7DpiMnb0mNY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-IuDla0bKOH2KmPPH79RJLw-1; Wed, 29 Jan 2020 12:20:20 -0500
X-MC-Unique: IuDla0bKOH2KmPPH79RJLw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 46763477;
        Wed, 29 Jan 2020 17:20:19 +0000 (UTC)
Received: from localhost (ovpn-117-180.ams2.redhat.com [10.36.117.180])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D7B5F5DE53;
        Wed, 29 Jan 2020 17:20:11 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: linux-fsdevel@vger.kernel.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Avi Kivity <avi@scylladb.com>,
        Davide Libenzi <davidel@xmailserver.org>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [RFC] eventfd: add EFD_AUTORESET flag
Date: Wed, 29 Jan 2020 17:20:10 +0000
Message-Id: <20200129172010.162215-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some applications simply use eventfd for inter-thread notifications
without requiring counter or semaphore semantics.  They wait for the
eventfd to become readable using poll(2)/select(2) and then call read(2)
to reset the counter.

This patch adds the EFD_AUTORESET flag to reset the counter when
f_ops->poll() finds the eventfd is readable, eliminating the need to
call read(2) to reset the counter.

This results in a small but measurable 1% performance improvement with
QEMU virtio-blk emulation.  Each read(2) takes 1 microsecond execution
time in the event loop according to perf.

Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
Does this look like a reasonable thing to do?  I'm not very familiar
with f_ops->poll() or the eventfd internals, so maybe I'm overlooking a
design flaw.

I've tested this with QEMU and it works fine:
https://github.com/stefanha/qemu/commits/eventfd-autoreset
---
 fs/eventfd.c            | 99 +++++++++++++++++++++++++----------------
 include/linux/eventfd.h |  3 +-
 2 files changed, 62 insertions(+), 40 deletions(-)

```
#### [RFC v3 1/8] vfio: Add VFIO_IOMMU_PASID_REQUEST(alloc/free)
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11356027
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54F89112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:07:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 287E222522
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:07:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726834AbgA2MHI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:07:08 -0500
Received: from mga03.intel.com ([134.134.136.65]:59027 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726632AbgA2MGk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:06:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:06:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="222433135"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 29 Jan 2020 04:06:38 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC v3 1/8] vfio: Add VFIO_IOMMU_PASID_REQUEST(alloc/free)
Date: Wed, 29 Jan 2020 04:11:45 -0800
Message-Id: <1580299912-86084-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1580299912-86084-1-git-send-email-yi.l.liu@intel.com>
References: <1580299912-86084-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@intel.com>

For a long time, devices have only one DMA address space from platform
IOMMU's point of view. This is true for both bare metal and directed-
access in virtualization environment. Reason is the source ID of DMA in
PCIe are BDF (bus/dev/fnc ID), which results in only device granularity
DMA isolation. However, this is changing with the latest advancement of
I/O technology. More and more platform vendors are utilizing the PCIe
PASID TLP prefix in DMA requests, thus to give devices with multiple DMA
address spaces as identified by their individual PASIDs. For example,
Shared Virtual Addressing (SVA, a.k.a Shared Virtual Memory) is able to
let device access multiple process virtual address space by binding the
virtual address space with a PASID. Wherein the PASID is allocated in
software and programmed to device per device specific manner. Devices
which support PASID capability are called PASID-capable devices. If such
devices are passed through to VMs, guest software are also able to bind
guest process virtual address space on such devices. Therefore, the guest
software could reuse the bare metal software programming model, which
means guest software will also allocate PASID and program it to device
directly. This is a dangerous situation since it has potential PASID
conflicts and unauthorized address space access. It would be safer to
let host intercept in the guest software's PASID allocation. Thus PASID
are managed system-wide.

This patch adds VFIO_IOMMU_PASID_REQUEST ioctl which aims to passdown
PASID allocation/free request from the virtual IOMMU. Additionally, such
requests are intended to be invoked by QEMU or other applications which
are running in userspace, it is necessary to have a mechanism to prevent
single application from abusing available PASIDs in system. With such
consideration, this patch tracks the VFIO PASID allocation per-VM. There
was a discussion to make quota to be per assigned devices. e.g. if a VM
has many assigned devices, then it should have more quota. However, it
is not sure how many PASIDs an assigned devices will use. e.g. it is
possible that a VM with multiples assigned devices but requests less
PASIDs. Therefore per-VM quota would be better.

This patch uses struct mm pointer as a per-VM token. We also considered
using task structure pointer and vfio_iommu structure pointer. However,
task structure is per-thread, which means it cannot achieve per-VM PASID
alloc tracking purpose. While for vfio_iommu structure, it is visible
only within vfio. Therefore, structure mm pointer is selected. This patch
adds a structure vfio_mm. A vfio_mm is created when the first vfio
container is opened by a VM. On the reverse order, vfio_mm is free when
the last vfio container is released. Each VM is assigned with a PASID
quota, so that it is not able to request PASID beyond its quota. This
patch adds a default quota of 1000. This quota could be tuned by
administrator. Making PASID quota tunable will be added in another patch
in this series.

Previous discussions:
https://patchwork.kernel.org/patch/11209429/

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
Signed-off-by: Yi Sun <yi.y.sun@linux.intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
---
 drivers/vfio/vfio.c             | 125 ++++++++++++++++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c |  92 +++++++++++++++++++++++++++++
 include/linux/vfio.h            |  15 +++++
 include/uapi/linux/vfio.h       |  41 +++++++++++++
 4 files changed, 273 insertions(+)

```
#### [RFC v1 1/2] vfio/pci: Expose PCIe PASID capability to guest
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11356109
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFE981800
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:13:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C78B5207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:13:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726598AbgA2MNc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:13:32 -0500
Received: from mga18.intel.com ([134.134.136.126]:21973 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726322AbgA2MNc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:13:32 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:13:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="222434773"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 29 Jan 2020 04:13:32 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC v1 1/2] vfio/pci: Expose PCIe PASID capability to guest
Date: Wed, 29 Jan 2020 04:18:44 -0800
Message-Id: <1580300325-86259-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1580300325-86259-1-git-send-email-yi.l.liu@intel.com>
References: <1580300325-86259-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@intel.com>

This patch exposes PCIe PASID capability to guest. Existing vfio_pci
driver hides it from guest by setting the capability length as 0 in
pci_ext_cap_length[].

This capability is required for vSVA enabling on pass-through PCIe
devices.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/pci/vfio_pci_config.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
