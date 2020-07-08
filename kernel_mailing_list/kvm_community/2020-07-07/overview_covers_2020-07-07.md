

#### [PATCH v2 0/2] iommu_aux_at(de)tach_device() enhancement
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Tue Jul  7 01:39:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11647275
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6444213B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 01:44:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 558F62070C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 01:44:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727826AbgGGBog (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 21:44:36 -0400
Received: from mga03.intel.com ([134.134.136.65]:40649 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726918AbgGGBof (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 21:44:35 -0400
IronPort-SDR: 
 lXTP9Mb1/OvcMrzJk7R7z7kIaaslSUq1eXnrawBCINmHY+O2TGjFsKQRMjpQ7DhzXQUSPp+kyo
 1SZ9ijSsQkeA==
X-IronPort-AV: E=McAfee;i="6000,8403,9674"; a="147536122"
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="147536122"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Jul 2020 18:44:35 -0700
IronPort-SDR: 
 HFLhQnGpMHKamOHZBRQ+F+vBuVPMBcUnf+p3xHf4IHlvImkUA3ScTysnJAuTevgcGcP2WaYAEb
 hzRXtwRh7few==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="266688906"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga007.fm.intel.com with ESMTP; 06 Jul 2020 18:44:32 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Robin Murphy <robin.murphy@arm.com>
Cc: Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v2 0/2] iommu_aux_at(de)tach_device() enhancement
Date: Tue,  7 Jul 2020 09:39:55 +0800
Message-Id: <20200707013957.23672-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to enhance the iommu_aux_at(de)tach_device() api's
so that some generic iommu api's like iommu_get_domain_for_dev() could
also work for vfio/mdev device.

The initial version of this series was post at

https://lkml.org/lkml/2020/6/26/1118

This version is evolved according to Robin's feedback.

Your comments are very appreciated.

Best regards,
baolu

Lu Baolu (2):
  iommu: iommu_aux_at(de)tach_device() extension
  iommu: Add aux_domain_attached flag to iommu_group

 drivers/iommu/iommu.c           | 98 +++++++++++++++++++++++++++++----
 drivers/vfio/vfio_iommu_type1.c |  5 +-
 include/linux/iommu.h           | 12 ++--
 3 files changed, 99 insertions(+), 16 deletions(-)
```
#### [PATCH v2 0/4] Expose new features for intel processor
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
From patchwork Tue Jul  7 02:16:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11647341
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 75F71618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 02:21:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6458320722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 02:21:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727124AbgGGCVp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 22:21:45 -0400
Received: from mga06.intel.com ([134.134.136.31]:19817 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726681AbgGGCVo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 22:21:44 -0400
IronPort-SDR: 
 1bRoAO2++l66kcQS6O+mGl1IDJrNPUaZfXLU9jbC/98g3uzMfcpMCUu4cHEXJtTw0oi7PrTXcG
 2eDewj0XdwmA==
X-IronPort-AV: E=McAfee;i="6000,8403,9674"; a="209050411"
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="209050411"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Jul 2020 19:21:43 -0700
IronPort-SDR: 
 /08WP0qn50HLBtdiMdTo6E6rcAb9CUZQan5fiYL8VajZmofS8j8m/KSlLR89117o4DRzTLyHuC
 rKwpVW7HVggA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="357633718"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by orsmga001.jf.intel.com with ESMTP; 06 Jul 2020 19:21:38 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, ricardo.neri-calderon@linux.intel.com,
        kyung.min.park@intel.com, jpoimboe@redhat.com,
        gregkh@linuxfoundation.org, ak@linux.intel.com,
        dave.hansen@intel.com, tony.luck@intel.com,
        ravi.v.shankar@intel.com, Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH v2 0/4] Expose new features for intel processor
Date: Tue,  7 Jul 2020 10:16:19 +0800
Message-Id: <1594088183-7187-1-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset is to expose two new features for intel
processors which support them, like Sapphire Rapids.
SERIALIZE is a faster serializing instruction which
does not modify registers, arithmetic flags or memory,
will not cause VM exit. TSX suspend load tracking
instruction aims to give a way to choose which memory
accesses do not need to be tracked in the TSX read set.

Changelog:
v2	Add kernel feature enumeration patch to fix build error

Cathy Zhang (2):
  x86: Expose SERIALIZE for supported cpuid
  x86: Expose TSX Suspend Load Address Tracking

Ricardo Neri (1):
  x86/cpufeatures: Add enumeration for SERIALIZE instruction

Kyung Min Park (1):
  x86/cpufeatures: Enumerate TSX suspend load address tracking
    instructions

 arch/x86/include/asm/cpufeatures.h | 2 ++
 arch/x86/kvm/cpuid.c               | 3 ++-
 2 files changed, 4 insertions(+), 1 deletion(-)
---
1.8.3.1
```
#### [PATCH v4 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Tue Jul  7 08:44:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11648049
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A55176C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 08:45:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 916D4206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 08:45:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727916AbgGGIpF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 04:45:05 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64132 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726467AbgGGIpF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Jul 2020 04:45:05 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0678Ve6c104150;
        Tue, 7 Jul 2020 04:45:00 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 324bpmpx67-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 04:44:57 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0678XoAT110196;
        Tue, 7 Jul 2020 04:44:50 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 324bpmpx25-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 04:44:49 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0678iVx4002463;
        Tue, 7 Jul 2020 08:44:42 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma05fra.de.ibm.com with ESMTP id 322hd81mdk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 08:44:42 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0678idwq49741930
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 7 Jul 2020 08:44:39 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6511BA404D;
        Tue,  7 Jul 2020 08:44:39 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 87860A4057;
        Tue,  7 Jul 2020 08:44:38 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.29.12])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  7 Jul 2020 08:44:38 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v4 0/2] s390: virtio: let arch validate VIRTIO features
Date: Tue,  7 Jul 2020 10:44:35 +0200
Message-Id: <1594111477-15401-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-07_05:2020-07-07,2020-07-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 adultscore=0
 suspectscore=1 bulkscore=0 clxscore=1015 cotscore=-2147483648 spamscore=0
 priorityscore=1501 malwarescore=0 mlxscore=0 impostorscore=0 phishscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2007070062
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

I changed the patch subject to reflect the content, becoming more
general.

1) I removed the ack from Christian and Jason even far as
   I understand they gave it for the functionality more than for the
   implementation.
   @Jason, @Christian, please can I get back your acked-by with these changes?

2) previous patch had another name:
   [PATCH v3 0/1] s390: virtio: let arch choose to accept devices without IOMMU feature
   id: Message-Id: <1592390637-17441-2-git-send-email-pmorel@linux.ibm.com>

3) The new version generalize the validation of the features by the
   architecture, making it not IOMMU_PLATFORM specific anymore inside
   virtio.c

   The architecture specific code for s390 is now testing the virtio
   features.

4) Since I reworked the patch I also moved the arch specific code
   from arch/s390/mm/init.c to arch/s390/kernel/to uv.c

5) Finaly, I splitted the patch into generic virtio and arch
   specific code.

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch validate VIRTIO features
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/kernel/uv.c         | 25 +++++++++++++++++++++++++
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 3 files changed, 45 insertions(+)
```
