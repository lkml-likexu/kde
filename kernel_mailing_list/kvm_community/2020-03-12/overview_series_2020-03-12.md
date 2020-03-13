#### [PATCH RFCv2 4/4] kvm: Implement atomic memory region resizes via region_resize()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11434821
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EB8A92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 16:14:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE93220724
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 16:14:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LIPsZ84j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727365AbgCLQOE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 12:14:04 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:37847 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726385AbgCLQOE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 12:14:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584029642;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=aUmlo8MrH4gk71Z4QNFrQL6GEhldMh1YHNoBnWn6ApQ=;
        b=LIPsZ84jMGJXs8m5JNvnN8x056rUiTf4pymEBnN5CvQq0A6c4Zem58Avli8P3TI29S8lCi
        rruqMH6vsOrgsr0Apk7aq9IJ3ulTuUP8Dg8kwy2S5Oq7koYuN4+ViSahY4BOL17P0Mcv2C
        rNoY3tt+xNzeYOK5Ye5K3iPwgCEncUk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-33-dmC-x3q7M-Wm-r0xaaxhTA-1; Thu, 12 Mar 2020 12:14:00 -0400
X-MC-Unique: dmC-x3q7M-Wm-r0xaaxhTA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 322E68017CC;
        Thu, 12 Mar 2020 16:13:59 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-117-131.ams2.redhat.com [10.36.117.131])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B507A5C1B5;
        Thu, 12 Mar 2020 16:13:54 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Peter Xu <peterx@redhat.com>, qemu-s390x@nongnu.org,
        David Hildenbrand <david@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        kvm@vger.kernel.org
Subject: [PATCH RFCv2 4/4] kvm: Implement atomic memory region resizes via
 region_resize()
Date: Thu, 12 Mar 2020 17:12:17 +0100
Message-Id: <20200312161217.3590-5-david@redhat.com>
In-Reply-To: <20200312161217.3590-1-david@redhat.com>
References: <20200312161217.3590-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

virtio-mem wants to resize (esp. grow) ram memory regions while the guest
is already aware of them and makes use of them. Resizing a KVM slot can
only currently be done by removing it and re-adding it. While the kvm slot
is temporarily removed, VCPUs that try to access memory on these slots (via
KVM_RUN) will fault. But also, other ioctls might depend on all slots being
in place.

Let's inhibit most KVM ioctls while performing the resize. Once we have an
ioctl that can perform atomic resizes (e.g., KVM_SET_USER_MEMORY_REGION
extensions), we can make inhibiting optional at runtime.

To minimize cache-line bouncing, use separate indicators (in_ioctl) and
locks (ioctl_mutex) per CPU.  Also, make sure to hold the kvm_slots_lock
while performing both actions (removing+re-adding).

We have to wait until all IOCTLs were exited and block new ones from
getting executed. Kick all CPUs, so they will exit the KVM_RUN ioctl.

This approach cannot result in a deadlock as long as the inhibitor does
not hold any locks that might hinder an IOCTL from getting finished and
exited - something fairly unusual. The inhibitor will always hold the BQL.

AFAIKs, one possible candidate would be userfaultfd. If a page cannot be
placed (e.g., during postcopy), because we're waiting for a lock, or if the
userfaultfd thread cannot process a fault, because it is waiting for a
lock, there could be a deadlock. However, the BQL is not applicable here,
because any other guest memory access while holding the BQL would already
result in a deadlock.

Nothing else in the kernel should block forever and wait for userspace
intervention.

Note1: Resizes of memory regions currently seems to happen during bootup
only, so I don't think any existing RT users should be affected.

Note2: pause_all_vcpus()/resume_all_vcpus() or
start_exclusive()/end_exclusive() cannot be used, as they either drop
the BQL or require to be called without the BQL - something inhibitors
cannot handle. We need a low-level locking mechanism that is
deadlock-free even when not releasing the BQL.

Cc: Richard Henderson <rth@twiddle.net>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 accel/kvm/kvm-all.c   | 129 +++++++++++++++++++++++++++++++++++++++---
 hw/core/cpu.c         |   2 +
 include/hw/core/cpu.h |   4 ++
 3 files changed, 128 insertions(+), 7 deletions(-)

```
#### [GIT PULL 1/1] KVM: s390: Also reset registers in sync regs for initial cpu reset
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11434401
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B913E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 14:38:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A317420736
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 14:38:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727716AbgCLOiH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 10:38:07 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37940 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727701AbgCLOiG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Mar 2020 10:38:06 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02CEZwMV071235
        for <kvm@vger.kernel.org>; Thu, 12 Mar 2020 10:38:05 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yqpr11157-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 12 Mar 2020 10:38:03 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 12 Mar 2020 14:27:55 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 12 Mar 2020 14:27:52 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02CERpx260293186
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 12 Mar 2020 14:27:51 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9520D4C04A;
        Thu, 12 Mar 2020 14:27:51 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 831484C040;
        Thu, 12 Mar 2020 14:27:51 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 12 Mar 2020 14:27:51 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 3EFAFE14B0; Thu, 12 Mar 2020 15:27:51 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [GIT PULL 1/1] KVM: s390: Also reset registers in sync regs for
 initial cpu reset
Date: Thu, 12 Mar 2020 15:27:50 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200312142750.3603-1-borntraeger@de.ibm.com>
References: <20200312142750.3603-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20031214-0012-0000-0000-0000038FF7D2
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031214-0013-0000-0000-000021CCCA00
Message-Id: <20200312142750.3603-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-12_06:2020-03-11,2020-03-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 mlxlogscore=999 lowpriorityscore=0 adultscore=0
 phishscore=0 clxscore=1015 malwarescore=0 bulkscore=0 spamscore=0
 impostorscore=0 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003120079
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we do the initial CPU reset we must not only clear the registers
in the internal data structures but also in kvm_run sync_regs. For
modern userspace sync_regs is the only place that it looks at.

Fixes: 7de3f1423ff9 ("KVM: s390: Add new reset vcpu API")
Acked-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 18 +++++++++++++++++-
 1 file changed, 17 insertions(+), 1 deletion(-)

```
#### [PATCH v13 Kernel 1/7] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11435187
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F0B614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:27:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B5A220737
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:27:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="JqY8PPJD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726718AbgCLS1J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 14:27:09 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:13058 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726605AbgCLS1J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 14:27:09 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e6a7ecd0000>; Thu, 12 Mar 2020 11:26:21 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 12 Mar 2020 11:27:06 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 12 Mar 2020 11:27:06 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 12 Mar
 2020 18:27:06 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 12 Mar 2020 18:26:59 +0000
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
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH v13 Kernel 1/7] vfio: KABI for migration interface for device
 state
Date: Thu, 12 Mar 2020 23:23:21 +0530
Message-ID: <1584035607-23166-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1584035607-23166-1-git-send-email-kwankhede@nvidia.com>
References: <1584035607-23166-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1584037581; bh=LP+y9TN4mDqbKdP9InK58TofXnOzbLqG594DRwuyd3I=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=JqY8PPJD74Z3nWiTJeXBznxsr5ej3tKFu2gAxuwqBTJU3rij4R/UPcD1ltO/pLouV
         GC4jNgNJ95Esb+iAKkOXDDnuVpLurdwiRN1dxQHNjE//KQQpmWce6FVrEj+KeEyxNS
         BccmimlytKdOTmUp6efea8mTa70JdYeIews+MoAj2zWM2X0HzOK8mVfniYqV93aKNX
         cHSVaQ04scN1lEzBEBYldKU+Kob9Iz/FqicGlTokNOxvzkQzp251gGdsjNHzx1lUm1
         SxNN9b92NyKaY8C+/HhsQJ9yZ2AsJsb1UEifnJBSTZATfoici8qI/odyIztWRWwJgo
         Zk9KY7e9WNfvA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 227 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 227 insertions(+)

```
#### [kvm-unit-tests PATCH v3 01/12] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11434657
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 207041392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 15:43:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F2EE2206FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 15:43:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jUu7Nr3B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727747AbgCLPn0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 11:43:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:43682 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727240AbgCLPnZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 11:43:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584027804;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5QgGQR5lmCzHdU2tw8u26Dp0LVz138MaKuXfv7AyzLc=;
        b=jUu7Nr3BveV/v6mTnLnIw7eaJ6PsPAD2b8a7INEs0gvFXjVWOOW1gBLd35P2vcfiiejpap
        nHO+BNrEJN6F2GQLhGKJUKSe++M1lgNmwc/gSTgy8QHMDOkMNsR6aHYPCaVc5NanwvVBO4
        INPcr9S0Gld/h7tWeRpkM7RStx+dVak=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-401-dOckM3WQOfWuveQhk9MwrQ-1; Thu, 12 Mar 2020 11:43:20 -0400
X-MC-Unique: dOckM3WQOfWuveQhk9MwrQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E847A100550E;
        Thu, 12 Mar 2020 15:43:17 +0000 (UTC)
Received: from laptop.redhat.com (unknown [10.36.118.12])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C4D215C1B5;
        Thu, 12 Mar 2020 15:43:12 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v3 01/12] arm64: Provide read/write_sysreg_s
Date: Thu, 12 Mar 2020 16:42:50 +0100
Message-Id: <20200312154301.9130-2-eric.auger@redhat.com>
In-Reply-To: <20200312154301.9130-1-eric.auger@redhat.com>
References: <20200312154301.9130-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Sometimes we need to test access to system registers which are
missing assembler mnemonics.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/sysreg.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH] KVM: selftests: s390x: Provide additional num-guest-pages adjustment
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11433871
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CFB692C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:41:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 30B052071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:41:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gj7yo/sO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726883AbgCLKlC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 06:41:02 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:42365 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725978AbgCLKlC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 12 Mar 2020 06:41:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584009661;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=r8/qYhcSrLmwzPMBf5VzmySM+Tb4H39EZs2TEBVhZP0=;
        b=gj7yo/sOKPfrK6jHhUbZxhoars0R8kw0DXD2QvwsG+QO6BHZWBo6zjeU25zbqNcv3JtTFz
        0M04aBD8qBFE79RG0HcFIRV8uH+DKjXVBQ6VEkgf3mvIrebL5VUUs9eSUbe+6BwYVs4GUs
        u9HalvQ1Wll1JoN+zx4tokjS8Ftu+QA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-448-CAjlSswtP_mugpyx_iXXjg-1; Thu, 12 Mar 2020 06:40:59 -0400
X-MC-Unique: CAjlSswtP_mugpyx_iXXjg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 839E8801E77;
        Thu, 12 Mar 2020 10:40:58 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D46245C545;
        Thu, 12 Mar 2020 10:40:56 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, thuth@redhat.com
Subject: [PATCH] KVM: selftests: s390x: Provide additional num-guest-pages
 adjustment
Date: Thu, 12 Mar 2020 11:40:55 +0100
Message-Id: <20200312104055.8558-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s390 requires 1M aligned guest sizes. Embedding the rounding in
vm_adjust_num_guest_pages() allows us to remove it from a few
other places.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Tested-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/testing/selftests/kvm/demand_paging_test.c | 4 ----
 tools/testing/selftests/kvm/dirty_log_test.c     | 5 +----
 tools/testing/selftests/kvm/include/kvm_util.h   | 8 +++++++-
 3 files changed, 8 insertions(+), 9 deletions(-)

```
#### [PATCH] kvm: svm: Introduce GA Log tracepoint for AVIC
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11433869
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1DC5690
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:39:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ECB5620724
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:39:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ArIUjTS2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726669AbgCLKjn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 06:39:43 -0400
Received: from mail-dm6nam11on2042.outbound.protection.outlook.com
 ([40.107.223.42]:65504
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726023AbgCLKjm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 06:39:42 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=cJ//0OxCNsTuWhvFb4ZnQgHAjrIFoINQgzVEBF93klN4rTvAU+m2yM+JwYFZTrNNy6bfyLgFt6Tb+GvXOh9IZaZZF+Yc2tCK6TyJMbkCWhBQaBAwXH0tpPp8mMkVor0AJ5YaQZVT9LLWqkL1yjuCrslzMSszPNz6/BesWhU5CEPELgd+iQmZa8b8pch8aAp3botQD2aIGeKt1DMDHXD2t0Izt7JHBOQ/HWk1yl0cfecnG1xTFDz638xebdYeeCdD1WGHqBTp4ethgEIvfILIs4INDmUrrHkjVMNUrzkJqDz5vaZTv4b5NEBLnvLBsHtwVGR+9IVhSC+1ndJDMuJ5tA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=fWlPjNv/NennGkA26zbaVAstC6MS7BJPLzel49z3I1c=;
 b=So1Bq24SCM9y7gTaltt8NCl7xLJD6BslokEMRk0CFhk1W1DmIdcTGLvgEuQaSvE7p5qQrvRjSiaV4JIvyzJKpyBfv+vrfmX6S1rJY4i0F60Hgy9PW6yZNxxmV58wwS+/sjxZecnM2lsox+5fYMC0auaXo9si4zS68qAcVdhCAGjwLlpdyqa6zZuRAp4B7jRMiaXHwnT/rKMKDzxTaHrUusj/8FAQyRYDptolqVLkqrAM3WPSNnVYJUOFSoa0VOn+LfvD6dwuZmBefukl+kl1HBB1QZhj/2DxLPtXa+lKtsrKq2/gqyPW4dhoFj46xETNyo6lH6X7Pwlz2hiCpTr7SA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=fWlPjNv/NennGkA26zbaVAstC6MS7BJPLzel49z3I1c=;
 b=ArIUjTS2LZaV9MH7grOJemnrIWTIb4zMgTY4Qjckm0ek8xUo31didVQpsuMqi0tGVqFbwwRa0TBfPkOCJxgrCijlmb/CLML046k/m+uEh5FW2Sr6Pt5o4a82BQZGTYwULOCBH/1Vpfh8rMFABZ2PJMGZ0HWoeoccZv2ISuK3QQs=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (2603:10b6:5:1c4::14)
 by DM6PR12MB2812.namprd12.prod.outlook.com (2603:10b6:5:44::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2793.17; Thu, 12 Mar
 2020 10:39:38 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::2d84:ed9d:cba4:dcfd]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::2d84:ed9d:cba4:dcfd%3]) with mapi id 15.20.2793.018; Thu, 12 Mar 2020
 10:39:37 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org, jon.grimm@amd.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH] kvm: svm: Introduce GA Log tracepoint for AVIC
Date: Thu, 12 Mar 2020 05:39:28 -0500
Message-Id: <1584009568-14089-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: DM5PR2001CA0011.namprd20.prod.outlook.com
 (2603:10b6:4:16::21) To DM6PR12MB3865.namprd12.prod.outlook.com
 (2603:10b6:5:1c4::14)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 DM5PR2001CA0011.namprd20.prod.outlook.com (2603:10b6:4:16::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2793.16 via Frontend
 Transport; Thu, 12 Mar 2020 10:39:37 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: dcb947a3-853e-4140-a1a9-08d7c671a9a2
X-MS-TrafficTypeDiagnostic: DM6PR12MB2812:|DM6PR12MB2812:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB28120BDE5B7890772626263EF3FD0@DM6PR12MB2812.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4502;
X-Forefront-PRVS: 0340850FCD
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(396003)(366004)(346002)(39860400002)(376002)(199004)(478600001)(4326008)(6666004)(86362001)(66556008)(66476007)(7696005)(316002)(81166006)(8676002)(81156014)(52116002)(2906002)(66946007)(5660300002)(6486002)(8936002)(16526019)(44832011)(956004)(2616005)(26005)(36756003)(186003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB2812;H:DM6PR12MB3865.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 FTBOzwS2IHHTpztPexVQk/N6ATf/++RSt7ztOUaIl6sPxfJgWytBYaqGm7alOHLD7E5KaIltnmdwE2jfR9yT6sbNF6HlTtnARVvc+cqS8RrxUaZGYfpXzhoZM6TtSAGcLnuk4x+u7W8QNvf7u8+do3DYpqC6SR3d8IR8t7vMlVbxmdcZrYF5QvnnwYDsSQZTCh8dZMvZ5JBX6gTvuZcx/KtwfYhBgMxUZO0PhHin6COHQHtv3/JbKFbnVRcAd1ng5T2qrHx+zuLz7dAPSr2WnGJealFA7QE9IoVWhMSTeYE1qWJIuTi/hKf5HTHlCcOzc8QQphIQQSQmsF5a423xUF35V5Cv05RbIx/KM2pcksAVrv0hay3MIu6Nc0PXAu8QEk61mpudCqME8UdkzynfarWMN4iQ3aay3OI0ZsSGXybETmiGypqsp2UHEK3Y39RP
X-MS-Exchange-AntiSpam-MessageData: 
 R8KUGQeKjOTa73q16Alk48bpW+D3xqx7EtqMUsvyjRv6aPqgVVhJkw6oKKWY16CWKtV1ULzy2OSFszfoVtEJZCQ/onXO2OWgsYKAWBGEXp6fmrMRuVIR51o0FEbed9R5gU/Lo5Kc2Ue2VJlnDbjxXA==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dcb947a3-853e-4140-a1a9-08d7c671a9a2
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Mar 2020 10:39:37.8294
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 8T0Dfc4NvYJL51OpFfP7ab+zzKldgvJyD8rkl2NfAfqe7YqXud21D+COqcbQbx2+wS7nISYb8BKkSgXHqPlBtA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2812
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GA Log tracepoint is useful when debugging AVIC performance
issue as it can be used with perf to count the number of times
IOMMU AVIC injects interrupts through the slow-path instead of
directly inject interrupts to the target vcpu.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c   |  1 +
 arch/x86/kvm/trace.h | 18 ++++++++++++++++++
 arch/x86/kvm/x86.c   |  1 +
 3 files changed, 20 insertions(+)

```
#### [PATCH] KVM: VMX: Condition ENCLS-exiting enabling on CPU support for SGX1
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11435165
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF323913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:04:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D705820736
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:04:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726637AbgCLSET (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 14:04:19 -0400
Received: from mga05.intel.com ([192.55.52.43]:38331 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726328AbgCLSES (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 14:04:18 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 11:04:17 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,545,1574150400";
   d="scan'208";a="277908742"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 12 Mar 2020 11:04:16 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Toni Spets <toni.spets@iki.fi>
Subject: [PATCH] KVM: VMX: Condition ENCLS-exiting enabling on CPU support for
 SGX1
Date: Thu, 12 Mar 2020 11:04:16 -0700
Message-Id: <20200312180416.6679-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enable ENCLS-exiting (and thus set vmcs.ENCLS_EXITING_BITMAP) only if
the CPU supports SGX1.  Per Intel's SDM, all ENCLS leafs #UD if SGX1
is not supported[*], i.e. intercepting ENCLS to inject a #UD is
unnecessary.

Avoiding ENCLS-exiting even when it is reported as supported by the CPU
works around a reported issue where SGX is "hard" disabled after an S3
suspend/resume cycle, i.e. CPUID.0x7.SGX=0 and the VMCS field/control
are enumerated as unsupported.  While the root cause of the S3 issue is
unknown, it's definitely _not_ a KVM (or kernel) bug, i.e. this is a
workaround for what is most likely a hardware or firmware issue.  As a
bonus side effect, KVM saves a VMWRITE when first preparing vmcs01 and
vmcs02.

Query CPUID directly instead of going through cpu_data() or cpu_has() to
ensure KVM is trapping ENCLS when it's supported in hardware, e.g. even
if X86_FEATURE_SGX1 (which doesn't yet exist in upstream) were disabled
by the kernel/user.

Note, SGX must be disabled in BIOS to take advantage of this workaround

[*] The additional ENCLS CPUID check on SGX1 exists so that SGX can be
    globally "soft" disabled post-reset, e.g. if #MC bits in MCi_CTL are
    cleared.  Soft disabled meaning disabling SGX without clearing the
    primary CPUID bit (in leaf 0x7) and without poking into non-SGX
    CPU paths, e.g. for the VMCS controls.

Fixes: 0b665d304028 ("KVM: vmx: Inject #UD for SGX ENCLS instruction in guest")
Reported-by: Toni Spets <toni.spets@iki.fi>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

This seems somewhat premature given that we don't yet know if the observed
behavior is a logic bug, a one off manufacturing defect, firmware specific,
etc...  On the other hand, the change is arguably an optimization
irrespective of using it as a workaround.

 arch/x86/kvm/vmx/vmx.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Micro-optimize vmexit time when not exposing PMU
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11433753
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99CD4913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:06:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A22220724
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 10:06:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Nk/8iiRy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726390AbgCLKGB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 06:06:01 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:33329 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725978AbgCLKGB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 06:06:01 -0400
Received: by mail-pg1-f193.google.com with SMTP id m5so2845715pgg.0;
        Thu, 12 Mar 2020 03:06:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=m7J0hu742fhuCj58D6loBGDul106B3xhX45qJX3dumI=;
        b=Nk/8iiRytuUjG0q9uprwJcaBhevtJfnkqyMusWXWllzk9B3U15QqaAOCVgtSUF5AT0
         nasrar5TZvGnNo60DZgYe9E8TuRT13ugqNuZ2o/dvsAQsfkW7tImySNBo4Q1dLJ/H6vu
         xOkaQO7xO+Rzpj+gMpTdtNrNG06jIUlYorXv5/7GJhG9Bz9sQyjL/FEFvuCfkNFJ/4Ts
         NRcwFQ9PKX+zMhozWIoQWGCazfQksDlzVW5OJZvwQqj45Tkz4WX2tumu3Ve/iiFfb4CQ
         XRP1rfPnohtrFoEe7zwxHN6iwF1TsJ7ksNYJz8Qmqkl9KkjjSDRjNvKD31vXT+mFWctf
         /UAQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=m7J0hu742fhuCj58D6loBGDul106B3xhX45qJX3dumI=;
        b=QhtM8swv/wqEfCLF3zL5fnYIlUi8i0slmlTBlnwPdTbwfDAkYfGPioxTOK48jz6+nO
         396Wo8J7EXA2/kJpp+zNz8/LxqaYZoD5lsRbV78kZH9G/VGriPhdleW5NK6PR+zAz+xp
         i9Qf6hXrj7dAHYJwLpL0QavCOuiSH/lavdtF6GgDW85R2d3LkwhmcZVjxGVkE7mtbdLd
         mq2wRGDHsHL89ULCLr8YstoRm8ytM7UQA3hgqXdzTjEgPyHVIx8h1TvWyonYMZUM64zL
         OEsAW8BiqPGCsN34PbJP6jo+7vvnBupgKpunWknTwP9WWDFNkvtqTUlUe3IrwB6yInGn
         4qNw==
X-Gm-Message-State: ANhLgQ2BvY+078gVk8WiDgfSR4kOmsfKE5scRfwzdhejNTr3a25nvZVb
        zHgEIQ5NuHLz0AUP795s1+e1wVLL
X-Google-Smtp-Source: 
 ADFU+vs2sY6uZfcGRvB4mw5lbE4o/npk0iLwC+R5UumZdHwq3N7seEjGFaYl+X0PfD6VX6QEHtIDmQ==
X-Received: by 2002:aa7:8552:: with SMTP id y18mr7503815pfn.0.1584007560431;
        Thu, 12 Mar 2020 03:06:00 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 dw19sm8234226pjb.16.2020.03.12.03.05.58
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 12 Mar 2020 03:05:59 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: VMX: Micro-optimize vmexit time when not exposing PMU
Date: Thu, 12 Mar 2020 18:05:47 +0800
Message-Id: <1584007547-4802-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

PMU is not exposed to guest by most of cloud providers since the bad performance 
of PMU emulation and security concern. However, it calls perf_guest_switch_get_msrs()
and clear_atomic_switch_msr() unconditionally even if PMU is not exposed to the 
guest before each vmentry. 

~1.28% vmexit time reduced can be observed by kvm-unit-tests/vmexit.flat on my 
SKX server.

Before patch:
vmcall 1559

After patch:
vmcall 1539

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 01/10] KVM: nVMX: Move reflection check into nested_vmx_reflect_vmexit()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11435233
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 18046161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:46:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 01BC020716
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:46:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726706AbgCLSpY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 14:45:24 -0400
Received: from mga02.intel.com ([134.134.136.20]:23434 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726643AbgCLSpY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 14:45:24 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 11:45:23 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,545,1574150400";
   d="scan'208";a="416041226"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga005.jf.intel.com with ESMTP; 12 Mar 2020 11:45:22 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 01/10] KVM: nVMX: Move reflection check into
 nested_vmx_reflect_vmexit()
Date: Thu, 12 Mar 2020 11:45:12 -0700
Message-Id: <20200312184521.24579-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200312184521.24579-1-sean.j.christopherson@intel.com>
References: <20200312184521.24579-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the call to nested_vmx_exit_reflected() from vmx_handle_exit() into
nested_vmx_reflect_vmexit() and change the semantics of the return value
for nested_vmx_reflect_vmexit() to indicate whether or not the exit was
reflected into L1.  nested_vmx_exit_reflected() and
nested_vmx_reflect_vmexit() are intrinsically tied together, calling one
without simultaneously calling the other makes little sense.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.h | 16 +++++++++++-----
 arch/x86/kvm/vmx/vmx.c    |  4 ++--
 2 files changed, 13 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: x86: Print symbolic names of VMX VM-Exit flags in traces
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11435175
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B96A313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:15:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A270D20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:15:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726579AbgCLSPi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 14:15:38 -0400
Received: from mga17.intel.com ([192.55.52.151]:29400 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726520AbgCLSPi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 14:15:38 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Mar 2020 11:15:38 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,545,1574150400";
   d="scan'208";a="442148589"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 12 Mar 2020 11:15:37 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Print symbolic names of VMX VM-Exit flags in traces
Date: Thu, 12 Mar 2020 11:15:35 -0700
Message-Id: <20200312181535.23797-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use __print_flags() to display the names of VMX flags in VM-Exit traces
and strip the flags when printing the basic exit reason, e.g. so that a
failed VM-Entry due to invalid guest state gets recorded as
"INVALID_STATE FAILED_VMENTRY" instead of "0x80000021".

Opportunstically fix misaligned variables in the kvm_exit and
kvm_nested_vmexit_inject tracepoints.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/uapi/asm/vmx.h |  3 +++
 arch/x86/kvm/trace.h            | 32 +++++++++++++++++---------------
 2 files changed, 20 insertions(+), 15 deletions(-)

```
#### [RFC PATCH] vfio: Ignore -ENODEV when getting MSI cookie
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11435177
Return-Path: <SRS0=L3qQ=45=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AAE813B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:20:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E825D206EB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 12 Mar 2020 18:19:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726512AbgCLST6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 12 Mar 2020 14:19:58 -0400
Received: from foss.arm.com ([217.140.110.172]:39520 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726328AbgCLST6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Mar 2020 14:19:58 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 184A130E;
        Thu, 12 Mar 2020 11:19:58 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.25])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BC9F43F67D;
        Thu, 12 Mar 2020 11:19:56 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>
Cc: Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org,
        iommu@lists.linux-foundation.org,
        Eric Auger <eric.auger@redhat.com>
Subject: [RFC PATCH] vfio: Ignore -ENODEV when getting MSI cookie
Date: Thu, 12 Mar 2020 18:19:50 +0000
Message-Id: <20200312181950.60664-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we try to get an MSI cookie for a VFIO device, that can fail if
CONFIG_IOMMU_DMA is not set. In this case iommu_get_msi_cookie() returns
-ENODEV, and that should not be fatal.

Ignore that case and proceed with the initialisation.

This fixes VFIO with a platform device on the Calxeda Midway (no MSIs).

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
Hi,

not sure this is the right fix, or we should rather check if the
platform doesn't support MSIs at all (which doesn't seem to be easy
to do).
Or is this because arm-smmu.c always reserves an IOMMU_RESV_SW_MSI
region?

Also this seems to be long broken, actually since Eric introduced MSI
support in 4.10-rc3, but at least since the initialisation order was
fixed with f6810c15cf9.

Grateful for any insight.

Cheers,
Andre

 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
