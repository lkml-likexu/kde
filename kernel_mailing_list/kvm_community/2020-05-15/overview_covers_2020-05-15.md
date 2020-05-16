

#### [PATCH 0/3 v3] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Fri May 15 05:36:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11550567
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7278697
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 06:16:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEF852075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 06:16:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="qm6xtWB5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726496AbgEOGQs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 02:16:48 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:54806 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726137AbgEOGQs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 May 2020 02:16:48 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04F6GZ6A158181;
        Fri, 15 May 2020 06:16:45 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=uiCA5nOBPKm6rXTYXKWytlWJF6Ig9pQol4RCZ9UiRoo=;
 b=qm6xtWB51V1coW2aj3PuXJrfqv7d7coDUiVcHtxYxumv0AYWAY3IODNJx3EI8Q6ELx8f
 H+lVJ7gyGgh8bKeIqOz6HVFKIuSeyZIAdMcOkyMFP/4vKAJ5y6+wIYWH6Z39cyIRvXgu
 q2hqQv4PS2rs15FkC5/LaZ/cCJ/AIoNOePTm+t2J73jTFVeBNTHX9OaS1PTwnlsfJ3oc
 PyHgSykK+dZuTIgSs7BG0CMWf9usqN0KewQG6l8/JYzoxI5Ahng+NY9FWHQJcK9vxyI9
 pWJakCOvNl+msmqH8FalEzj+AOCExJQcD7UVqV13HaFdIn7ZZ4Y9Bj/Xp8rcI0rWGxHc 4A==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 3100yg7sqk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 15 May 2020 06:16:45 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04F68khG066210;
        Fri, 15 May 2020 06:16:45 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 310vjv6j9b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 May 2020 06:16:44 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 04F6GiLd014395;
        Fri, 15 May 2020 06:16:44 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 14 May 2020 23:16:44 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/3 v3] KVM: nSVM: Check MBZ bits in CR3 and CR4 on vmrun of
 nested guests
Date: Fri, 15 May 2020 01:36:06 -0400
Message-Id: <20200515053609.3347-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9621
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 bulkscore=0 phishscore=0
 spamscore=0 mlxlogscore=880 malwarescore=0 suspectscore=1 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005150052
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9621
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 adultscore=0
 cotscore=-2147483648 mlxscore=0 suspectscore=1 spamscore=0 impostorscore=0
 mlxlogscore=902 malwarescore=0 clxscore=1015 phishscore=0 bulkscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2005150053
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	In patch# 1, the mask for guest CR4 reserved bits is now cached in
	'struct kvm_vcpu_arch', instead of in a global variable.


[PATCH 1/3 v3] KVM: x86: Create mask for guest CR4 reserved bits in
[PATCH 2/3 v3] KVM: nSVM: Check that MBZ bits in CR3 and CR4 are not set on
[PATCH 3/3 v3] KVM: nSVM: Test that MBZ bits in CR3 and CR4 are not set on vmrun

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/svm/nested.c       | 22 ++++++++++++++++++++--
 arch/x86/kvm/svm/svm.h          |  5 ++++-
 arch/x86/kvm/x86.c              | 27 ++++-----------------------
 arch/x86/kvm/x86.h              | 21 +++++++++++++++++++++
 6 files changed, 53 insertions(+), 26 deletions(-)

Krish Sadhukhan (2):
      KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
      nSVM: Check that MBZ bits in CR3 and CR4 are not set on vmrun of nested gu

 x86/svm.h       |   6 ++++
 x86/svm_tests.c | 105 +++++++++++++++++++++++++++++++++++++++++++++++++-------
 2 files changed, 99 insertions(+), 12 deletions(-)

Krish Sadhukhan (1):
      nSVM: Test that MBZ bits in CR3 and CR4 are not set on vmrun of nested g
```
#### [PATCH 0/7] KVM: SVM: baby steps towards nested state migration
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri May 15 17:41:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11552823
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 013E659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 17:41:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB6A52070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 17:41:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="flrdVGB7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726379AbgEORlx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 13:41:53 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:30750 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726198AbgEORlw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 May 2020 13:41:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589564511;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=NstvlP5tNzUfUYikWj6FNTt45pdW5CGZjiroRvCAySM=;
        b=flrdVGB7Z7gftR2Swu6m8u3PcdWHwa491ZmWF6eSi1lxYOPVsboAVf06+nDa36gTwFsqSE
        sbUcFfs6aqxCITKUJV0YLvA8fXcOXTqKvBHHmSzd2tsgYe/3+7uryPTRLPusJr4Mmx9NKT
        MY0K3jjmGQO1cs+6fetvly4TgAKCMis=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-140-S-KRjdPlMCeJNwuSwL0mKg-1; Fri, 15 May 2020 13:41:47 -0400
X-MC-Unique: S-KRjdPlMCeJNwuSwL0mKg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 70E85100CC90;
        Fri, 15 May 2020 17:41:46 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BF64C105911A;
        Fri, 15 May 2020 17:41:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cathy Avery <cavery@redhat.com>,
        Liran Alon <liran.alon@oracle.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 0/7] KVM: SVM: baby steps towards nested state migration
Date: Fri, 15 May 2020 13:41:37 -0400
Message-Id: <20200515174144.1727-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here are some refactorings to prepare for an SVM implementation of
KVM_SET_NESTED_STATE.  It's a prerequisite for that to eliminate
exit_required, moving exceptions to svm_check_nested_events.  However:

- I might work on that soon, because it's needed to handle RSM when
the L1 hypervisor wants to get it from #UD rather than the specific
RSM intercept

- this should be enough to get a quick prototype, that I need in order to
debug a particularly crazy bug and figure out its reproducibility.

So, I am getting these patches out of my todo list for now.

Thanks,

Paolo

Paolo Bonzini (7):
  KVM: SVM: move map argument out of enter_svm_guest_mode
  KVM: SVM: extract load_nested_vmcb_control
  KVM: SVM: extract preparation of VMCB for nested run
  KVM: SVM: save all control fields in svm->nested
  KVM: nSVM: remove HF_VINTR_MASK
  KVM: nSVM: do not reload pause filter fields from VMCB
  KVM: SVM: introduce data structures for nested virt state

 arch/x86/include/asm/kvm_host.h |   1 -
 arch/x86/include/uapi/asm/kvm.h |  26 +++++++-
 arch/x86/kvm/svm/nested.c       | 115 +++++++++++++++++---------------
 arch/x86/kvm/svm/svm.c          |  11 ++-
 arch/x86/kvm/svm/svm.h          |  28 +++++---
 5 files changed, 116 insertions(+), 65 deletions(-)
```
#### [PATCH Kernel v21 0/8] Add UAPIs to support migration for VFIO
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Fri May 15 21:13:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11553075
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFD88138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 21:46:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C05032070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 21:46:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="AEU+rSFk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727772AbgEOVqg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 17:46:36 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:6101 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726228AbgEOVqg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 May 2020 17:46:36 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebf0dae0001>; Fri, 15 May 2020 14:46:22 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Fri, 15 May 2020 14:46:35 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Fri, 15 May 2020 14:46:35 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 15 May
 2020 21:46:34 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 15 May 2020 21:46:28 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v21 0/8] Add UAPIs to support migration for VFIO
 devices
Date: Sat, 16 May 2020 02:43:15 +0530
Message-ID: <1589577203-20640-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589579182; bh=W03FjgpVNoPugeAkD8lX+r7RnLVAW4I4X9JhiloaBqU=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=AEU+rSFkF+HFvT1q5gP7dPjp74G4pTZPqJU9WD0rAEOvhnsoq1i3I2/T+/r33mNOT
         xna5qTBKc8fcrWZe39ocemeU/AA/XiODRjiUifucuzsLbYbfIPyCsF8+C9OUdCxqVB
         6tzY0rR9zy96bfuJGwBp7YhuvG7Ge6TZN9i4K1mmDceRK3tFj4KCOmy4QB8nR5phoL
         WSknSGM02C0WkE3uHNjkmY+Ht3NKk7DFjxRC2/zAILbxhvNs1qKJLojpyHm5jl0fcY
         WMrdlW9+4seMQ9lbrD1diR6gtM1XQVmbPk5T/Jkle0xAgnFNoi6J7B3Mi+tllKZlAp
         N5nsgk9GRgapg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 8 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v20 -> v21
- Added checkin for GET_BITMAP ioctl for vfio_dma boundaries.
- Updated unmap ioctl function - as suggested by Alex.
- Updated comments in DIRTY_TRACKING ioctl definition - as suggested by
  Cornelia.

v19 -> v20
- Fixed ioctl to get dirty bitmap to get bitmap of multiple vfio_dmas
- Fixed unmap ioctl to get dirty bitmap of multiple vfio_dmas.
- Removed flag definition from migration capability.

v18 -> v19
- Updated migration capability with supported page sizes bitmap for dirty
  page tracking and  maximum bitmap size supported by kernel module.
- Added patch to calculate and cache pgsize_bitmap when iommu->domain_list
  is updated.
- Removed extra buffers added in previous version for bitmap manipulation
  and optimised the code.

v17 -> v18
- Add migration capability to the capability chain for VFIO_IOMMU_GET_INFO
  ioctl
- Updated UMAP_DMA ioctl to return bitmap of multiple vfio_dma

v16 -> v17
- Fixed errors reported by kbuild test robot <lkp@intel.com> on i386

v15 -> v16
- Minor edits and nit picks (Auger Eric)
- On copying bitmap to user, re-populated bitmap only for pinned pages,
  excluding unmapped pages and CPU dirtied pages.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti



Kirti Wankhede (8):
  vfio: UAPI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Cache pgsize_bitmap in struct vfio_iommu
  vfio iommu: Add ioctl definition for dirty pages tracking
  vfio iommu: Implementation of ioctl for dirty pages tracking
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Add migration capability to report supported features
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 569 ++++++++++++++++++++++++++++++++++++----
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 315 ++++++++++++++++++++++
 4 files changed, 842 insertions(+), 59 deletions(-)
```
#### [PATCH v7 0/3] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c
From patchwork Fri May 15 22:19:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11553145
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A9E5138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 22:20:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B8C22076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 22:20:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726301AbgEOWUC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 18:20:02 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:52456 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726212AbgEOWUC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 May 2020 18:20:02 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04FM4Wh6146781;
        Fri, 15 May 2020 18:20:01 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 310v8tdq3b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 18:20:01 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04FM5VCj149901;
        Fri, 15 May 2020 18:20:01 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0b-001b2d01.pphosted.com with ESMTP id 310v8tdq35-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 18:20:01 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04FMAJMM007662;
        Fri, 15 May 2020 22:20:00 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma05wdc.us.ibm.com with ESMTP id 3100ucjfvs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 22:20:00 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04FMJudA7602476
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 May 2020 22:19:56 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EA712C605A;
        Fri, 15 May 2020 22:19:56 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2C3C1C6055;
        Fri, 15 May 2020 22:19:56 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.146.125])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 15 May 2020 22:19:55 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v7 0/3] Use DIAG318 to set Control Program Name & Version
 Codes
Date: Fri, 15 May 2020 18:19:32 -0400
Message-Id: <20200515221935.18775-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-15_07:2020-05-15,2020-05-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 adultscore=0
 spamscore=0 priorityscore=1501 clxscore=1015 impostorscore=0 mlxscore=0
 lowpriorityscore=0 suspectscore=0 bulkscore=0 cotscore=-2147483648
 phishscore=0 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005150185
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changelog:

    v7

    • Removed diag handler, as it will now take place within userspace
    • Removed KVM_S390_VM_MISC_ENABLE_DIAG318 (undoes first bullet in v6)
    • Misc clean ups and fixes
        - introduced a new patch to s/diag318/diag_318 and s/byte_134/fac134
          to keep things consistent with the rest of the code

    v6

    • KVM disables diag318 get/set by default [removed in v7]
    • added new IOCTL to tell KVM to enable diag318 [removed in v7]
    • removed VCPU event message in favor of VM_EVENT only

    v5
    
    • s/cpc/diag318_info in order to make the relevant data more clear
    • removed mutex locks for diag318_info get/set

    v4
    
    • removed setup.c changes introduced in bullet 1 of v3
    • kept diag318_info struct cleanup
    • analogous QEMU patches:
        https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg00164.html

    v3
    
    • kernel patch for diag 0x318 instruction call fixup [removed in v4]
    • removed CPU model code
    • cleaned up diag318_info struct
    • cpnc is no longer unshadowed as it was not needed
    • rebased on 5.1.0-rc3

-------------------------------------------------------------------------------

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read Info byte 134 (aka fac134),
bit 0.

DIAG 0x318's is handled by userspace and may be enabled for a guest even if the
host kernel cannot support it.

The diag318_info is composed of a Control Program Name Code (CPNC) and a
Control Program Version Code (CPVC). The CPNC is stored in SIE blocks, and
the CPNC & CPVC pair is stored in the kvm_arch struct. 

These values are used for problem diagnosis and allows IBM to identify control
program information by answering the following question:

    "What environment is this guest running in?" (CPNC)
    "What are more details regarding the OS?" (CPVC)

In the future, we will implement the CPVC to convey more information about the 
OS (such as Linux version and potentially some value denoting a specific 
distro + release). For now, we set this field to 0 until we come up with a solid 
plan.

Collin Walling (3):
  s390/setup: diag 318: refactor struct
  s390: keep diag 318 variables consistent with the rest
  s390/kvm: diagnose 0x318 get/set handling

 Documentation/virt/kvm/devices/vm.rst | 21 +++++++
 arch/s390/include/asm/diag.h          |  8 +--
 arch/s390/include/asm/kvm_host.h      |  5 +-
 arch/s390/include/asm/sclp.h          |  2 +-
 arch/s390/include/uapi/asm/kvm.h      |  4 ++
 arch/s390/kernel/setup.c              |  9 ++-
 arch/s390/kvm/kvm-s390.c              | 82 +++++++++++++++++++++++++++
 arch/s390/kvm/vsie.c                  |  2 +
 drivers/s390/char/sclp.h              |  2 +-
 drivers/s390/char/sclp_early.c        |  2 +-
 10 files changed, 123 insertions(+), 14 deletions(-)
```
