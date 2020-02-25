

#### [PATCH 0/2] KVM: VMX: Use basic exit reason for cheking and indexing
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Mon Feb 24 02:07:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11399183
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E6F114BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 02:13:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07EF420836
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 02:13:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727183AbgBXCND (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Feb 2020 21:13:03 -0500
Received: from mga06.intel.com ([134.134.136.31]:24747 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727151AbgBXCND (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Feb 2020 21:13:03 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Feb 2020 18:13:02 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,478,1574150400";
   d="scan'208";a="255437173"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by orsmga002.jf.intel.com with ESMTP; 23 Feb 2020 18:13:00 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 0/2] KVM: VMX: Use basic exit reason for cheking and indexing
Date: Mon, 24 Feb 2020 10:07:49 +0800
Message-Id: <20200224020751.1469-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current KVM directly uses the whole 32-bit EXIT REASON when
1) checking: if (vmx->exit_reason == EXIT_REASON_*)
2) indexing: kvm_vmx_exit_handlers[exit_reason]

However, only the low 16-bit of EXIT REASON serves as basic Exit Reason.
Fix it by using the 16-bit basic exit reason.

BTW, I'm not sure if it's necessary to split nested case into a seperate
patch.

Xiaoyao Li (2):
  kvm: vmx: Use basic exit reason to check if it's the specific VM EXIT
  kvm: nvmx: Use basic(exit_reason) when checking specific EXIT_REASON

 arch/x86/kvm/vmx/nested.c |  6 +++---
 arch/x86/kvm/vmx/nested.h |  2 +-
 arch/x86/kvm/vmx/vmx.c    | 44 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    |  2 ++
 4 files changed, 29 insertions(+), 25 deletions(-)
```
#### [PATCH v3 0/7] use vfio_dma_rw to read/write IOVAs from CPU side
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Mon Feb 24 08:43:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11399525
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 554A217D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 08:55:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3DC672467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 08:55:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727463AbgBXIy6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 03:54:58 -0500
Received: from mga03.intel.com ([134.134.136.65]:55741 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727539AbgBXIxi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 03:53:38 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Feb 2020 00:53:37 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,479,1574150400";
   d="scan'208";a="437630183"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by fmsmga006.fm.intel.com with ESMTP; 24 Feb 2020 00:53:34 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, zhenyuw@linux.intel.com
Cc: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v3 0/7] use vfio_dma_rw to read/write IOVAs from CPU side
Date: Mon, 24 Feb 2020 03:43:50 -0500
Message-Id: <20200224084350.31574-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is better for a device model to use IOVAs to read/write memory to
perform some sort of virtual DMA on behalf of the device.

patch 1 exports VFIO group to external user so that it can hold the group
reference until finishing using of it. It saves ~500 cycles that are spent
on VFIO group looking up, referencing and dereferencing. (this data is
measured with 1 VFIO user).

patch 2 introduces interface vfio_dma_rw().

patch 3 introduces interfaces vfio_pin_pages_from_group() and
vfio_unpin_pages_from_group() to get rid of VFIO group looking-up in
vfio_pin_pages() and vfio_unpin_pages().

patch 4-5 let kvmgt switch from calling kvm_read/write_guest() to calling
vfio_dma_rw to rw IOVAs.

patch 6 let kvmgt switch to use lighter version of vfio_pin/unpin_pages(),
i.e. vfio_pin/unpin_pages_from_group()

patch 7 enables kvmgt to read/write IOVAs of size larger than PAGE_SIZE.


Performance:

Comparison between vfio_dma_rw() and kvm_read/write_guest():

1. avergage CPU cycles of each interface measured with 1 running VM:
 --------------------------------------------------
|  rw       |          avg cycles of               |
|  size     | (vfio_dma_rw - kvm_read/write_guest) |
|---------- ---------------------------------------|
| <= 1 page |            +155 ~ +195               |        
|--------------------------------------------------|
| 5 pages   |                -530                  |
|--------------------------------------------------|
| 20 pages  |           -2005 ~ -2533              |
 --------------------------------------------------

2. average scores

base: base code before applying code in this series. use
kvm_read/write_pages() to rw IOVAs

base + this series: use vfio_dma_rw() to read IOVAs and use
vfio_pin/unpin_pages_from_group(), and kvmgt is able to rw several pages
at a time.

Scores of benchmarks running in 1 VM each:
 -----------------------------------------------------------------
|                    | glmark2 | lightsmark | openarena | heavens |
|-----------------------------------------------------------------|
|       base         |  1248   |  219.70    |  114.9    |   560   |
|-----------------------------------------------------------------|
|base + this series  |  1248   |  225.8     |   115     |   559   |
 -----------------------------------------------------------------

Sum of scores of two benchmark instances running in 2 VMs each:
 -------------------------------------------------------
|                    | glmark2 | lightsmark | openarena |
|-------------------------------------------------------|
|       base         |  812    |  211.46    |  115.3    |
|-------------------------------------------------------|
|base + this series  |  814    |  214.69    |  115.9    |
 -------------------------------------------------------


Changelogs:
v2 --> v3:
- add vfio_group_get_external_user_from_dev() to improve performance (Alex)
- add vfio_pin/unpin_pages_from_group() to avoid repeated looking up of
  VFIO group in vfio_pin/unpin_pages() (Alex)
- add a check for IOMMU_READ permission. (Alex)
- rename vfio_iommu_type1_rw_dma_nopin() to
  vfio_iommu_type1_dma_rw_chunk(). (Alex)
- in kvmgt, change "write ? vfio_dma_rw(...,true) :
  vfio_dma_rw(...,false)" to vfio_dma_rw(dev, gpa, buf, len, write)
  (Alex and Paolo)
- in kvmgt, instead of read/write context pages 1:1, combining the
  reads/writes of continuous IOVAs to take advantage of vfio_dma_rw() for
  faster crossing page boundary accesses.

v1 --> v2:
- rename vfio_iova_rw to vfio_dma_rw, vfio iommu driver ops .iova_rw
to .dma_rw. (Alex).
- change iova and len from unsigned long to dma_addr_t and size_t,
respectively. (Alex)
- fix possible overflow in dma->vaddr + iova - dma->iova + offset (Alex)
- split DMAs from on page boundary to on max available size to eliminate
  redundant searching of vfio_dma and switching mm. (Alex)
- add a check for IOMMU_WRITE permission.

 Yan Zhao (7):
  vfio: allow external user to get vfio group from device
  vfio: introduce vfio_dma_rw to read/write a range of IOVAs
  vfio: avoid inefficient lookup of VFIO group in vfio_pin/unpin_pages
  drm/i915/gvt: hold reference of VFIO group during opening of vgpu
  drm/i915/gvt: subsitute kvm_read/write_guest with vfio_dma_rw
  drm/i915/gvt: avoid unnecessary lookup in each vfio pin & unpin pages
  drm/i915/gvt: rw more pages a time for shadow context

 drivers/gpu/drm/i915/gvt/gvt.h       |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c     |  43 +++----
 drivers/gpu/drm/i915/gvt/scheduler.c | 101 +++++++++++-----
 drivers/vfio/vfio.c                  | 175 +++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c      |  77 ++++++++++++
 include/linux/vfio.h                 |  13 ++
 6 files changed, 358 insertions(+), 52 deletions(-)
```
#### [PATCH 0/1] Documentation fixup
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Feb 24 10:15:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11400139
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FADB924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 10:16:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7881C20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 10:16:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726838AbgBXKQG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 05:16:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14238 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726509AbgBXKQG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 24 Feb 2020 05:16:06 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01OADcV4014040
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 05:16:05 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2yax447gg7-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 05:16:04 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 24 Feb 2020 10:16:03 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 24 Feb 2020 10:16:00 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01OAG00V60162144
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 24 Feb 2020 10:16:00 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E0712A4065;
        Mon, 24 Feb 2020 10:15:59 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CDFC5A4060;
        Mon, 24 Feb 2020 10:15:59 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 24 Feb 2020 10:15:59 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 8AF8AE02D7; Mon, 24 Feb 2020 11:15:59 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>
Subject: [PATCH 0/1] Documentation fixup
Date: Mon, 24 Feb 2020 11:15:58 +0100
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20022410-0028-0000-0000-000003DD70DD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022410-0029-0000-0000-000024A28547
Message-Id: <20200224101559.27405-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-24_02:2020-02-21,2020-02-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 mlxlogscore=617 suspectscore=0 spamscore=0 priorityscore=1501
 impostorscore=0 mlxscore=0 malwarescore=0 phishscore=0 bulkscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002240088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

this is a small fixup for the overlap of the s390 reset changes and
Mauros doc update. No pull request for just one patch. Please apply
to kvm/master.

Christian Borntraeger (1):
  KVM: s390: rstify new ioctls in api.rst

 Documentation/virt/kvm/api.rst | 33 ++++++++++++++++++---------------
 1 file changed, 18 insertions(+), 15 deletions(-)
```
#### [PATCH v4 00/36] KVM: s390: Add support for protected VMs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Feb 24 11:40:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11400255
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE1A6930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 11:41:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CC52720836
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 11:41:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727803AbgBXLls (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 06:41:48 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:29334 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727440AbgBXLlQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 24 Feb 2020 06:41:16 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01OBck2O114993;
        Mon, 24 Feb 2020 06:41:13 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yax37hm39-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 06:41:12 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01OBfCUV120356;
        Mon, 24 Feb 2020 06:41:12 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yax37hm2k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 06:41:12 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01OBZBYd031965;
        Mon, 24 Feb 2020 11:41:11 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma02dal.us.ibm.com with ESMTP id 2yaux6fuqe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 11:41:11 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01OBf9QW34079156
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 24 Feb 2020 11:41:09 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7CF7728059;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5F98028058;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        Andrew Morton <akpm@linux-foundation.org>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>, linux-mm@kvack.org
Subject: [PATCH v4 00/36] KVM: s390: Add support for protected VMs
Date: Mon, 24 Feb 2020 06:40:31 -0500
Message-Id: <20200224114107.4646-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-24_02:2020-02-21,2020-02-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 impostorscore=0
 bulkscore=0 spamscore=0 suspectscore=0 mlxlogscore=999 priorityscore=1501
 lowpriorityscore=0 clxscore=1015 phishscore=0 malwarescore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002240099
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

mm-related patches CCed on linux-mm, the complete list can be found on
the KVM and linux-s390 list. 

Andrew, any chance to take " mm:gup/writeback: add callbacks for
inaccessible pages" for 5.7? I can then carry the s390/kvm part. There
is no build dependency on this patch (just a logical one).  As an
alternative I can take an ack and carry that patch myself. 

This series contains a "pretty small" common code memory management
change that will allow paging, guest backing with files etc almost
just like normal VMs. It should be a no-op for all architectures not
opting in. And it should be usable for others that also try to get
notified on "the pages are in the process of being used for things
like I/O". This time I included error handling and an ACK from Will
Deacon as well as a Reviewed-by: from David Hildenbrand.
This patch will be used by
"[PATCH v4 05/36] s390/mm: provide memory management functions for
protected KVM guests".
We need to call into the "make accessible" architecture function when
the refcount is already increased the writeback bit is set. This will
make sure that we do not call the reverse function (convert to secure)
until the host operation has finished.


Overview
--------
Protected VMs (PVM) are KVM VMs, where KVM can't access the VM's state
like guest memory and guest registers anymore. Instead the PVMs are
mostly managed by a new entity called Ultravisor (UV), which provides
an API, so KVM and the PV can request management actions.

PVMs are encrypted at rest and protected from hypervisor access while
running. They switch from a normal operation into protected mode, so
we can still use the standard boot process to load a encrypted blob
and then move it into protected mode.

Rebooting is only possible by passing through the unprotected/normal
mode and switching to protected again.

All patches are in the protvirtv4 branch of the korg s390 kvm git
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=protvirtv6

Claudio presented the technology at his presentation at KVM Forum
2019.

https://static.sched.com/hosted_files/kvmforum2019/3b/ibm_protected_vms_s390x.pdf


v3 -> v4:
general
-------
- copyright updates
- Reviewedby + acked by tags

KVM: s390/interrupt: do not pin adapter interrupt pages
-------------------------------------------------------
- more comments
- get rid of now obsolete adapter parameter

s390/mm: provide memory management functions for protected KVM guests
---------------------------------------------------------------------
- improved patch description

KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
--------------------------------------------------------------
- rework tweak logic to not use an array
- remove _VM_ part of the subfunction names of PV_COMMAND
- merge alloc/create/destroy/dealloc into init/deinit
- handle cmma deallocation on failures
- rework error handling to pass along the first rc/rrc if VCPU or VM CREATE/DESTROY fails
This was tested successfully with error injection and tracing. We do not deallocate on
destroy failure and we pass along the first rc/rrc when vcpu destroy fails.

 KVM: s390: protvirt: Add KVM api documentation
-----------------------------------------------
- mention new MP_STATE
- remove "old" interfaces that are no longer in the previous patch
- move to the end

KVM: s390: protvirt: Secure memory is not mergeable
---------------------------------------------------
- rebase on new lifecycle patch

KVM: s390: protvirt: UV calls in support of diag308 0,1
-------------------------------------------------------
- remove _VM_ part of the subfunction names of PV_COMMAND

KVM: s390: rstify new ioctls in api.rst
---------------------------------------
- removed from this patch queue



v2 -> v3
- rebase against v5.6-rc2
- move some checks into the callers
- typo fixes
- extend UV query size
- do a tlb flush when entering/exiting protected mode
- more comments
- change interface to PV_ENABLE/DISABLE instead of vcpu/vm
  create/destroy
- lockdep checks for *is_protected calls
- locking improments
- move facility 161 to qemu
- checkpatch fixes
- merged error handling in mm patch
- removed vcpu pv commands
- use mp_state for setting the IPL PSW


v1 -> v2
- rebase on top of kvm/master
- pipe through rc and rrc. This might have created some churn here and
  there
- turn off sclp masking when rebooting into "unsecure"
- memory management simplification
- prefix page handling now via intercept 112
- io interrupt intervention request fix (do not use GISA)
- api.txt conversion to rst
- sample patches on top of mm/gup/writeback
- tons of review feedback
- kvm_uv debug feature fixes and unifications
- ultravisor information for /sys/firmware
- 

RFCv2 -> v1 (you can diff the protvirtv2 and the protvirtv3 branch)
- tons of review feedback integrated (see mail thread)
- memory management now complete and working
- Documentation patches merged
- interrupt patches merged
- CONFIG_KVM_S390_PROTECTED_VIRTUALIZATION_HOST removed
- SIDA interface integrated into memop
- for merged patches I removed reviews that were not in all patches



Christian Borntraeger (4):
  KVM: s390/mm: Make pages accessible before destroying the guest
  KVM: s390: protvirt: Add SCLP interrupt handling
  KVM: s390: protvirt: do not inject interrupts after start
  KVM: s390: protvirt: introduce and enable KVM_CAP_S390_PROTECTED

Claudio Imbrenda (3):
  mm/gup/writeback: add callbacks for inaccessible pages
  s390/mm: provide memory management functions for protected KVM guests
  KVM: s390/mm: handle guest unpin events

Janosch Frank (24):
  KVM: s390: protvirt: Add UV debug trace
  KVM: s390: add new variants of UV CALL
  KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
  KVM: s390: protvirt: Secure memory is not mergeable
  KVM: s390: protvirt: Handle SE notification interceptions
  KVM: s390: protvirt: Instruction emulation
  KVM: s390: protvirt: Handle spec exception loops
  KVM: s390: protvirt: Add new gprs location handling
  KVM: S390: protvirt: Introduce instruction data area bounce buffer
  KVM: s390: protvirt: handle secure guest prefix pages
  KVM: s390: protvirt: Write sthyi data to instruction data area
  KVM: s390: protvirt: STSI handling
  KVM: s390: protvirt: disallow one_reg
  KVM: s390: protvirt: Do only reset registers that are accessible
  KVM: s390: protvirt: Only sync fmt4 registers
  KVM: s390: protvirt: Add program exception injection
  KVM: s390: protvirt: UV calls in support of diag308 0, 1
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Mask PSW interrupt bits for interception 104 and
    112
  KVM: s390: protvirt: Add UV cpu reset calls
  DOCUMENTATION: Protected virtual machine introduction and IPL
  s390: protvirt: Add sysfs firmware interface for Ultravisor
    information
  KVM: s390: protvirt: Add KVM api documentation

Michael Mueller (1):
  KVM: s390: protvirt: Implement interrupt injection

Ulrich Weigand (1):
  KVM: s390/interrupt: do not pin adapter interrupt pages

Vasily Gorbik (3):
  s390/protvirt: introduce host side setup
  s390/protvirt: add ultravisor initialization
  s390/mm: add (non)secure page access exceptions handlers

 .../admin-guide/kernel-parameters.txt         |   5 +
 Documentation/virt/kvm/api.rst                |  61 +-
 Documentation/virt/kvm/devices/s390_flic.rst  |  11 +-
 Documentation/virt/kvm/index.rst              |   2 +
 Documentation/virt/kvm/s390-pv-boot.rst       |  83 +++
 Documentation/virt/kvm/s390-pv.rst            | 116 ++++
 MAINTAINERS                                   |   1 +
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  21 +-
 arch/s390/include/asm/gmap.h                  |   6 +
 arch/s390/include/asm/kvm_host.h              | 113 +++-
 arch/s390/include/asm/mmu.h                   |   2 +
 arch/s390/include/asm/mmu_context.h           |   1 +
 arch/s390/include/asm/page.h                  |   5 +
 arch/s390/include/asm/pgtable.h               |  35 +-
 arch/s390/include/asm/uv.h                    | 252 ++++++++-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   9 +-
 arch/s390/kernel/uv.c                         | 413 ++++++++++++++
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/diag.c                          |   6 +-
 arch/s390/kvm/intercept.c                     | 117 +++-
 arch/s390/kvm/interrupt.c                     | 399 +++++++------
 arch/s390/kvm/kvm-s390.c                      | 532 +++++++++++++++---
 arch/s390/kvm/kvm-s390.h                      |  51 +-
 arch/s390/kvm/priv.c                          |  13 +-
 arch/s390/kvm/pv.c                            | 298 ++++++++++
 arch/s390/mm/fault.c                          |  78 +++
 arch/s390/mm/gmap.c                           |  65 ++-
 include/linux/gfp.h                           |   6 +
 include/uapi/linux/kvm.h                      |  43 +-
 mm/gup.c                                      |  15 +-
 mm/page-writeback.c                           |   5 +
 34 files changed, 2461 insertions(+), 312 deletions(-)
 create mode 100644 Documentation/virt/kvm/s390-pv-boot.rst
 create mode 100644 Documentation/virt/kvm/s390-pv.rst
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
#### [FYI PATCH 0/3] CVE-2020-2732
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon Feb 24 18:56:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11401415
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F9021871
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:56:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 565D721D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:56:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="LTL1hmvY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727964AbgBXS4l (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 13:56:41 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:36873 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726664AbgBXS4l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 13:56:41 -0500
Received: by mail-wr1-f66.google.com with SMTP id l5so7428311wrx.4;
        Mon, 24 Feb 2020 10:56:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=NnFSJ4wxz3IPiMj1BwmfM2ZfdupPqpOk/+KIyr1YuNI=;
        b=LTL1hmvY+p9SeOwCwhvc0/8d1+N5Xvl5LEmWQb6BhL4wTAq7d/jNaj1hKzHjMU5T3a
         3WId6E6jvuLSK+nx59o56vOQiXAYmJYa5hDWweuuoFQhEea+2rnx9MEsZlgy9FQxNqmE
         DKLufNfq7H9drttHAqY9Ilup3GQ3tGB8y6KrUPhp/a7VuZiM9u1PW93bD8OjMBWe4f77
         Vz1VQcEIFBSFqo8jfpOVTXSUNtMQu5suGQE2Nu1CB/vnDuispeYlKbUNjpJWT73KMnrx
         vmR99rxf/JvPHhI7VywcOFisdc85QpSoPukMe3x6V9G4kGX1sDNGXMjPuNxUARZ/D59s
         lSjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=NnFSJ4wxz3IPiMj1BwmfM2ZfdupPqpOk/+KIyr1YuNI=;
        b=AJEu3Kgem3Bo3W8gKERnO8QufKJEYY6aGRLrE/JAaq/2UcSRMUDN78dp1kels8RoGE
         K1kYCQnXA6S1vZ98JMEqfFBP+MJ2UOTH0/GpihujAmgYl1gcQoh96ufhs4JdbNyedYWQ
         pNqTHoooPxvyJdQ3AAC5Z0WjJq0rNHl00mt89iMMGIJtfl1NfBjyewTer1ZekOnIgdo6
         ja2CbW3UUwGnsDJo2l3xX67brwojlRdiyVfJlrv1wlaPF3BmX0Gb3F8+Q8B/3+4HvEd3
         5XZUKr0sv90KZaZpYCCm2rYJ4FMQb2LM/5/ZrNScKT1jh56YPQ3V3gS0oLBCYJ8R0sCi
         mLDA==
X-Gm-Message-State: APjAAAW9rgN/FYMvY2+U6kRIXTN5C0/4OnyHVDgmcJNCix9Y8NGcnVnV
        771nKaNz3OBvvcR0kd40vEUAqYxt
X-Google-Smtp-Source: 
 APXvYqxFl7vEubY2+cyUaHD+DMOaNVtDmIUluQaMZIZnEibNMHQ66vXDhsuImjpo1M7sNxz4iDngdw==
X-Received: by 2002:adf:bbcf:: with SMTP id
 z15mr69057763wrg.266.1582570598470;
        Mon, 24 Feb 2020 10:56:38 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 z8sm19900838wrv.74.2020.02.24.10.56.37
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 24 Feb 2020 10:56:37 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: oupton@google.com
Subject: [FYI PATCH 0/3] CVE-2020-2732
Date: Mon, 24 Feb 2020 19:56:33 +0100
Message-Id: <1582570596-45387-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_check_intercept is not yet fully implemented by KVM on Intel processors,
causing e.g. the I/O or MSR interception bitmaps not to be checked.
In general we can just disallow instruction emulation on behalf of L1,
but this series also implements I/O port checks.

Paolo

Oliver Upton (2):
  KVM: nVMX: Refactor IO bitmap checks into helper function
  KVM: nVMX: Check IO instruction VM-exit conditions

Paolo Bonzini (1):
  KVM: nVMX: Don't emulate instructions in guest mode

 arch/x86/kvm/vmx/nested.c | 39 ++++++++++++++++++++-----------
 arch/x86/kvm/vmx/nested.h |  2 ++
 arch/x86/kvm/vmx/vmx.c    | 59 +++++++++++++++++++++++++++++++++++++++++------
 3 files changed, 79 insertions(+), 21 deletions(-)
```
