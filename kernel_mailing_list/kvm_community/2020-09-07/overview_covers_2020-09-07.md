

#### [PATCH v11 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Sep  7 09:39:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11760335
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C62259D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 09:40:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4891121473
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 09:40:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="WPvQMiZH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728472AbgIGJja (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 05:39:30 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:59102 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728300AbgIGJj3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 05:39:29 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0879Vp67008621;
        Mon, 7 Sep 2020 05:39:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=/zsoqtLlLbEPeX56/5WqT6AsOKEzVbCt1a7Ompwymls=;
 b=WPvQMiZHoj+krc7szVHr3KR8Dth4u7rrk9gmXULVKwKiISKoxDWdeR00fSQ6/wFaWLw3
 y8uX0uio5xDMuMmySUIHW2qtUqGZblyjAZ8AgeNEToC/9q/FMb6wgbalFfMELy3FxInl
 D0yXYsss5nKqlNqiLnuvm4f/MW+M16GYVnVQY3oRuel2bDMRfxYUUBX5ia+ydCwzFEWT
 q29+3TgLu7XBZXMxr676edSqVK/6TKLlIylfCmaFBdLimeUDZKG7K+ixv5QPuO8Pg34p
 2tHtbQD7hG7hTek66KdO00IxUgiNFhb0y4gCbKFPmYanVAVgip0d7UfYszfIeHMUDW/O 5g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dff85k9c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 05:39:16 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0879WrP2011545;
        Mon, 7 Sep 2020 05:39:16 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dff85k88-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 05:39:15 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0879bbYJ001949;
        Mon, 7 Sep 2020 09:39:13 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03ams.nl.ibm.com with ESMTP id 33c2a827c7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 09:39:13 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0879dAIb32244048
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 09:39:10 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 389B3A4065;
        Mon,  7 Sep 2020 09:39:10 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 62105A4060;
        Mon,  7 Sep 2020 09:39:09 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.86.222])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 09:39:09 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v11 0/2] s390: virtio: let arch validate VIRTIO features
Date: Mon,  7 Sep 2020 11:39:05 +0200
Message-Id: <1599471547-28631-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_04:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 clxscore=1015 mlxscore=0 malwarescore=0 adultscore=0 spamscore=0
 suspectscore=1 impostorscore=0 bulkscore=0 mlxlogscore=999
 priorityscore=1501 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009070090
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

The tests are back to virtio_finalize_features.

No more argument for the architecture callback which only reports
if the architecture needs guest memory access restrictions for
VIRTIO.

I renamed the callback to arch_has_restricted_virtio_memory_access,
the config option to ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS,
and VIRTIO_F_IOMMU_PLATFORM to VIRTIO_F_ACCESS_PLATFORM.

Regards,
Pierre

Pierre Morel (2):
  virtio: let arch advertise guest's memory access restrictions
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/Kconfig             |  1 +
 arch/s390/mm/init.c           | 10 ++++++++++
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h | 10 ++++++++++
 5 files changed, 42 insertions(+)
```
#### [PATCH v4.19.y 0/3] vfio: Fix for CVE-2020-12888
##### From: Ajay Kaher <akaher@vmware.com>

```c
From patchwork Mon Sep  7 10:17:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11760443
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6455713B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:22:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 531BD204FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:22:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728951AbgIGKVp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 06:21:45 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:8125 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728421AbgIGKVn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 06:21:43 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 03:21:33 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 22D5540271;
        Mon,  7 Sep 2020 03:21:34 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.19.y 0/3] vfio: Fix for CVE-2020-12888
Date: Mon, 7 Sep 2020 15:47:23 +0530
Message-ID: <1599473843-34234-4-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599473843-34234-1-git-send-email-akaher@vmware.com>
References: <1599473843-34234-1-git-send-email-akaher@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2020-12888 Kernel: vfio: access to disabled MMIO space of some
devices may lead to DoS scenario
    
The VFIO modules allow users (guest VMs) to enable or disable access to the
devices' MMIO memory address spaces. If a user attempts to access (read/write)
the devices' MMIO address space when it is disabled, some h/w devices issue an
interrupt to the CPU to indicate a fatal error condition, crashing the system.
This flaw allows a guest user or process to crash the host system resulting in
a denial of service.
    
Patch 1/ is to force the user fault if PFNMAP vma might be DMA mapped
before user access.
    
Patch 2/ setup a vm_ops handler to support dynamic faulting instead of calling
remap_pfn_range(). Also provides a list of vmas actively mapping the area which
can later use to invalidate those mappings.
    
Patch 3/ block the user from accessing memory spaces which is disabled by using
new vma list support to zap, or invalidate, those memory mappings in order to
force them to be faulted back in on access.
    
Upstreamed patches link:
https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home
        
[PATCH v4.19.y 1/3]:
Backporting of upsream commit 41311242221e:
vfio/type1: Support faulting PFNMAP vmas
        
[PATCH v4.19.y 2/3]:
Backporting of upsream commit 11c4cd07ba11:
vfio-pci: Fault mmaps to enable vma tracking
        
[PATCH v4.19.y 3/3]:
Backporting of upsream commit abafbc551fdd:
vfio-pci: Invalidate mmaps and block MMIO access on disabled memory
```
#### [PATCH 0/2] fix dead lock issues in vhost_vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Mon Sep  7 10:52:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11760587
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90E4459D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:56:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 821A42166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:56:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728935AbgIGK4X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 06:56:23 -0400
Received: from mga12.intel.com ([192.55.52.136]:22272 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728649AbgIGK4V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 06:56:21 -0400
IronPort-SDR: 
 TJTpybBuRxpVPkA8HQ6iVLofC9V3d8cooB+CqyPFFVXWzioUfFML+DwgZLfKHjG9UK+cEbNQg5
 pheE7jXA54GA==
X-IronPort-AV: E=McAfee;i="6000,8403,9736"; a="137503288"
X-IronPort-AV: E=Sophos;i="5.76,401,1592895600";
   d="scan'208";a="137503288"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Sep 2020 03:56:21 -0700
IronPort-SDR: 
 haIiBvqZXXwkE6pW6vKULio2NxvjM4+4EQxz752QobHhd0YNtT2XLPS9cIUT2vUL7wGSpe5dH0
 2L588EOQRovA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,401,1592895600";
   d="scan'208";a="303698262"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga006.jf.intel.com with ESMTP; 07 Sep 2020 03:56:19 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/2] fix dead lock issues in vhost_vdpa
Date: Mon,  7 Sep 2020 18:52:18 +0800
Message-Id: <20200907105220.27776-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series fixed a dead lock issue in vhost_vdpa.
In current vhost_vdpa ioctl code path, it will lock
vhost_dev mutex once, then try to re-lock it in
vhost_set_backend_features, which is buggy.

These commits will remove mutex locks operations
in vhost_set_backend_features, then as a compensation,
a new function vhost_net_set_backend_features() in vhost_net
is introduced to do proper mutex locking and call
vhost_set_backend_features()

Please help review. Thanks!

Zhu Lingshan (2):
  vhost: remove mutex ops in vhost_set_backend_features
  vhost_net: introduce vhost_net_set_backend_features()

 drivers/vhost/net.c   | 9 ++++++++-
 drivers/vhost/vhost.c | 2 --
 2 files changed, 8 insertions(+), 3 deletions(-)
```
#### [PATCH v7 00/72] x86: SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Mon Sep  7 13:15:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11761795
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1479E746
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:44:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 009B621532
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:44:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731444AbgIGRoP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 13:44:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60160 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729439AbgIGNRq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 09:17:46 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B59ABC061574;
        Mon,  7 Sep 2020 06:16:44 -0700 (PDT)
Received: from cap.home.8bytes.org (p549add56.dip0.t-ipconnect.de
 [84.154.221.86])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 12A591CA;
        Mon,  7 Sep 2020 15:16:39 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7 00/72] x86: SEV-ES Guest Support
Date: Mon,  7 Sep 2020 15:15:01 +0200
Message-Id: <20200907131613.12703-1-joro@8bytes.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here is a new version of the SEV-ES Guest Support patches for x86. The
previous versions can be found as a linked list starting here:

	https://lore.kernel.org/lkml/20200824085511.7553-1-joro@8bytes.org/

I updated the patch-set based on ther review comments I got and the
discussions around it.

Another important change is that the early IDT setup code is now
completly moved to arch/x86/kernel/head64.c. This makes the whole
early exception handling setup code more robust for kernels that have
KASAN and/or Tracing enabled.

A side effect of this change is that secondary CPU now don't use the
idt_table at early boot, which means that on the secondary CPUs the
early handler does not use IST or paranoid_entry() anymore. This
allowed to remove a couple of patches from this series which were only
needed to setup relevant processor starte early enough for IST
exceptions. In particular this means that the early FSGSBASE and TSS
setup is gone now. Also the patch which moved the idt_table to the
data segement is now removed.

A related change was necessary in the boot path of secondary CPUs,
because those loaded the runtime IDT before setting up the TSS and the
getcpu GDT entry. This is now in proper order so that IST exceptions
will work when the runtime IDT is loaded for the first time. This
setup is added in patch 67.

The cpu_init() function is untouched so that it still act as the
intended cpu-state barrier, regardless of what happens before.

The code survived the usual load test of running one x86-selftest loop
on each core of the guest in parallel with perf (for NMI load). This
runs for several (4+) hours now without any issues.

Please review.

Thanks,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Doug Covelli (1):
  x86/vmware: Add VMware specific handling for VMMCALL under SEV-ES

Joerg Roedel (50):
  KVM: SVM: nested: Don't allocate VMCB structures on stack
  KVM: SVM: Add GHCB Accessor functions
  x86/traps: Move pf error codes to <asm/trap_pf.h>
  x86/insn: Make inat-tables.c suitable for pre-decompression code
  x86/umip: Factor out instruction fetch
  x86/umip: Factor out instruction decoding
  x86/insn: Add insn_get_modrm_reg_off()
  x86/insn: Add insn_has_rep_prefix() helper
  x86/boot/compressed/64: Disable red-zone usage
  x86/boot/compressed/64: Add IDT Infrastructure
  x86/boot/compressed/64: Rename kaslr_64.c to ident_map_64.c
  x86/boot/compressed/64: Add page-fault handler
  x86/boot/compressed/64: Always switch to own page-table
  x86/boot/compressed/64: Don't pre-map memory in KASLR code
  x86/boot/compressed/64: Change add_identity_map() to take start and
    end
  x86/boot/compressed/64: Add stage1 #VC handler
  x86/boot/compressed/64: Call set_sev_encryption_mask() earlier
  x86/boot/compressed/64: Check return value of
    kernel_ident_mapping_init()
  x86/boot/compressed/64: Add set_page_en/decrypted() helpers
  x86/boot/compressed/64: Setup GHCB Based VC Exception handler
  x86/boot/compressed/64: Unmap GHCB page before booting the kernel
  x86/fpu: Move xgetbv()/xsetbv() into separate header
  x86/idt: Split idt_data setup out of set_intr_gate()
  x86/head/64: Install startup GDT
  x86/head/64: Load GDT after switch to virtual addresses
  x86/head/64: Load segment registers earlier
  x86/head/64: Switch to initial stack earlier
  x86/head/64: Install a CPU bringup IDT
  x86/idt: Move two function from k/idt.c to i/a/desc.h
  x86/head/64: Move early exception dispatch to C code
  x86/sev-es: Add SEV-ES Feature Detection
  x86/sev-es: Print SEV-ES info into kernel log
  x86/sev-es: Compile early handler code into kernel image
  x86/sev-es: Setup early #VC handler
  x86/sev-es: Setup GHCB based boot #VC handler
  x86/sev-es: Allocate and Map IST stack for #VC handler
  x86/sev-es: Adjust #VC IST Stack on entering NMI handler
  x86/dumpstack/64: Add noinstr version of get_stack_info()
  x86/entry/64: Add entry code for #VC handler
  x86/sev-es: Wire up existing #VC exit-code handlers
  x86/sev-es: Handle instruction fetches from user-space
  x86/sev-es: Handle MMIO String Instructions
  x86/sev-es: Handle #AC Events
  x86/sev-es: Handle #DB Events
  x86/paravirt: Allow hypervisor specific VMMCALL handling under SEV-ES
  x86/realmode: Add SEV-ES specific trampoline entry point
  x86/smpboot: Load TSS and getcpu GDT entry before loading IDT
  x86/head/64: Don't call verify_cpu() on starting APs
  x86/sev-es: Support CPU offline/online
  x86/sev-es: Handle NMI State

Martin Radev (1):
  x86/sev-es: Check required CPU features for SEV-ES

Tom Lendacky (19):
  KVM: SVM: Add GHCB definitions
  x86/cpufeatures: Add SEV-ES CPU feature
  x86/sev-es: Add support for handling IOIO exceptions
  x86/sev-es: Add CPUID handling to #VC handler
  x86/sev-es: Setup per-cpu GHCBs for the runtime handler
  x86/sev-es: Add Runtime #VC Exception Handler
  x86/sev-es: Handle MMIO events
  x86/sev-es: Handle MSR events
  x86/sev-es: Handle DR7 read/write events
  x86/sev-es: Handle WBINVD Events
  x86/sev-es: Handle RDTSC(P) Events
  x86/sev-es: Handle RDPMC Events
  x86/sev-es: Handle INVD Events
  x86/sev-es: Handle MONITOR/MONITORX Events
  x86/sev-es: Handle MWAIT/MWAITX Events
  x86/sev-es: Handle VMMCALL Events
  x86/kvm: Add KVM specific VMMCALL handling under SEV-ES
  x86/realmode: Setup AP jump table
  x86/efi: Add GHCB mappings when SEV-ES is active

 arch/x86/Kconfig                           |    1 +
 arch/x86/boot/compressed/Makefile          |   11 +-
 arch/x86/boot/compressed/cpuflags.c        |    4 -
 arch/x86/boot/compressed/head_64.S         |   33 +-
 arch/x86/boot/compressed/ident_map_64.c    |  349 +++++
 arch/x86/boot/compressed/idt_64.c          |   54 +
 arch/x86/boot/compressed/idt_handlers_64.S |   77 ++
 arch/x86/boot/compressed/kaslr.c           |   36 +-
 arch/x86/boot/compressed/kaslr_64.c        |  153 ---
 arch/x86/boot/compressed/misc.c            |    7 +
 arch/x86/boot/compressed/misc.h            |   50 +-
 arch/x86/boot/compressed/sev-es.c          |  214 +++
 arch/x86/entry/entry_64.S                  |   80 ++
 arch/x86/include/asm/cpu_entry_area.h      |   33 +-
 arch/x86/include/asm/cpufeatures.h         |    1 +
 arch/x86/include/asm/desc.h                |   27 +
 arch/x86/include/asm/desc_defs.h           |   10 +
 arch/x86/include/asm/fpu/internal.h        |   30 +-
 arch/x86/include/asm/fpu/xcr.h             |   34 +
 arch/x86/include/asm/idtentry.h            |   50 +
 arch/x86/include/asm/insn-eval.h           |    6 +
 arch/x86/include/asm/mem_encrypt.h         |    5 +
 arch/x86/include/asm/msr-index.h           |    3 +
 arch/x86/include/asm/page_64_types.h       |    1 +
 arch/x86/include/asm/pgtable.h             |    2 +-
 arch/x86/include/asm/processor.h           |    1 +
 arch/x86/include/asm/proto.h               |    1 +
 arch/x86/include/asm/realmode.h            |    7 +
 arch/x86/include/asm/segment.h             |    2 +-
 arch/x86/include/asm/setup.h               |    6 +-
 arch/x86/include/asm/sev-es.h              |  114 ++
 arch/x86/include/asm/stacktrace.h          |    2 +
 arch/x86/include/asm/svm.h                 |  106 +-
 arch/x86/include/asm/trap_pf.h             |   24 +
 arch/x86/include/asm/trapnr.h              |    1 +
 arch/x86/include/asm/traps.h               |   20 +-
 arch/x86/include/asm/x86_init.h            |   16 +-
 arch/x86/include/uapi/asm/svm.h            |   11 +
 arch/x86/kernel/Makefile                   |    3 +
 arch/x86/kernel/cpu/amd.c                  |    3 +-
 arch/x86/kernel/cpu/common.c               |   25 +
 arch/x86/kernel/cpu/scattered.c            |    1 +
 arch/x86/kernel/cpu/vmware.c               |   50 +-
 arch/x86/kernel/dumpstack.c                |    7 +-
 arch/x86/kernel/dumpstack_64.c             |   46 +-
 arch/x86/kernel/head64.c                   |  122 +-
 arch/x86/kernel/head_64.S                  |  160 ++-
 arch/x86/kernel/idt.c                      |   41 +-
 arch/x86/kernel/kvm.c                      |   35 +-
 arch/x86/kernel/nmi.c                      |   15 +
 arch/x86/kernel/sev-es-shared.c            |  507 +++++++
 arch/x86/kernel/sev-es.c                   | 1404 ++++++++++++++++++++
 arch/x86/kernel/smpboot.c                  |    2 +-
 arch/x86/kernel/traps.c                    |   48 +
 arch/x86/kernel/umip.c                     |   49 +-
 arch/x86/kvm/svm/nested.c                  |   47 +-
 arch/x86/kvm/svm/svm.c                     |    2 +
 arch/x86/lib/insn-eval.c                   |  130 ++
 arch/x86/mm/cpu_entry_area.c               |    3 +-
 arch/x86/mm/extable.c                      |    1 +
 arch/x86/mm/mem_encrypt.c                  |   38 +-
 arch/x86/mm/mem_encrypt_identity.c         |    3 +
 arch/x86/platform/efi/efi_64.c             |   10 +
 arch/x86/realmode/init.c                   |   24 +-
 arch/x86/realmode/rm/header.S              |    3 +
 arch/x86/realmode/rm/trampoline_64.S       |   20 +
 arch/x86/tools/gen-insn-attr-x86.awk       |   50 +-
 tools/arch/x86/tools/gen-insn-attr-x86.awk |   50 +-
 68 files changed, 4030 insertions(+), 451 deletions(-)
 create mode 100644 arch/x86/boot/compressed/ident_map_64.c
 create mode 100644 arch/x86/boot/compressed/idt_64.c
 create mode 100644 arch/x86/boot/compressed/idt_handlers_64.S
 delete mode 100644 arch/x86/boot/compressed/kaslr_64.c
 create mode 100644 arch/x86/boot/compressed/sev-es.c
 create mode 100644 arch/x86/include/asm/fpu/xcr.h
 create mode 100644 arch/x86/include/asm/sev-es.h
 create mode 100644 arch/x86/include/asm/trap_pf.h
 create mode 100644 arch/x86/kernel/sev-es-shared.c
 create mode 100644 arch/x86/kernel/sev-es.c
```
#### [PATCH v2 0/2] s390x: pv: Fixes and improvements
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon Sep  7 12:46:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11761823
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E597B59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:48:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C9492208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:48:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="l5z76WXE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729282AbgIGMrk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 08:47:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:31622 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729233AbgIGMr3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 08:47:29 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 087CXLZP075524;
        Mon, 7 Sep 2020 08:47:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=2RyC8LYAhiLnnCHqOK/2SaSmB1wB57P8mu9LBs+Qtgg=;
 b=l5z76WXE7cr7A7p3ZL/4riG9e7G1BC9BKaCdQWp4/ZCf5te6NslMqXuU+2DdiIV5UfLx
 5YoPCewxvumNa3Sh3B74i+6EfEDl3ZqONqmwWSG5aY8qHt2ctMhnTDsG+2PQ/aastCij
 hgIQkS1NbXlntYUbwF94H7n8mpU3FO4x0wKnYtTfUPWWkYPgCCCiWbzo0ylLc4epdHl6
 WEQ1V4HCLxNJPcLMjBHWlFBmFaOO69vm6bKWGYr4uT1ehoFgNc8+3DGtq9mEFYEYzmqX
 tn0Dz0VbQ8bLgKGC88R05HPtFdxa6J1/n3jBwzEkLak6xEBwHYvsMTMBzNAjNNhVCmK9 HQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dkc4axvv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 08:47:08 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 087CXMDe075593;
        Mon, 7 Sep 2020 08:47:08 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dkc4axve-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 08:47:08 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 087CfamK025350;
        Mon, 7 Sep 2020 12:47:06 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 33c2a82d5t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 12:47:06 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 087Cl3W661276656
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 12:47:03 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BCA314C058;
        Mon,  7 Sep 2020 12:47:03 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EB62A4C046;
        Mon,  7 Sep 2020 12:47:02 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 12:47:02 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-s390@vger.kernel.org
Cc: borntraeger@de.ibm.com, gor@linux.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, david@redhat.com, hca@linux.ibm.com
Subject: [PATCH v2 0/2] s390x: pv: Fixes and improvements
Date: Mon,  7 Sep 2020 08:46:58 -0400
Message-Id: <20200907124700.10374-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_07:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxscore=0
 adultscore=0 suspectscore=1 malwarescore=0 priorityscore=1501
 impostorscore=0 lowpriorityscore=0 mlxlogscore=742 bulkscore=0 spamscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009070123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using the destroy call instead of the export on a VM shutdown, we can
clear out a protected guest much faster.

The 3f exception can in fact be triggered by userspace and therefore
should not panic the whole system, but send a SIGSEGV to the culprit
process.

v2:
	* Removed whitespace damage
	* Directly access task struct for pid and comm
	* Removed NOKPROBE_SYMBOL

Janosch Frank (2):
  s390x: uv: Add destroy page call
  s390x: Add 3f program exception handler

 arch/s390/include/asm/uv.h   |  7 +++++++
 arch/s390/kernel/pgm_check.S |  2 +-
 arch/s390/kernel/uv.c        | 20 ++++++++++++++++++++
 arch/s390/mm/fault.c         | 20 ++++++++++++++++++++
 arch/s390/mm/gmap.c          |  2 +-
 5 files changed, 49 insertions(+), 2 deletions(-)
```
#### [PATCH v4.14.y 0/3] vfio: Fix for CVE-2020-12888
##### From: Ajay Kaher <akaher@vmware.com>

```c
From patchwork Mon Sep  7 20:17:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11762199
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57617138E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:22:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 402E421582
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:22:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729742AbgIGUVg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 16:21:36 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:17994 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729658AbgIGUVZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 16:21:25 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 13:21:21 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id EF9574072D;
        Mon,  7 Sep 2020 13:21:21 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.14.y 0/3] vfio: Fix for CVE-2020-12888
Date: Tue, 8 Sep 2020 01:47:08 +0530
Message-ID: <1599509828-23596-4-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599509828-23596-1-git-send-email-akaher@vmware.com>
References: <1599509828-23596-1-git-send-email-akaher@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2020-12888 Kernel: vfio: access to disabled MMIO space of some
devices may lead to DoS scenario
    
The VFIO modules allow users (guest VMs) to enable or disable access to the
devices' MMIO memory address spaces. If a user attempts to access (read/write)
the devices' MMIO address space when it is disabled, some h/w devices issue an
interrupt to the CPU to indicate a fatal error condition, crashing the system.
This flaw allows a guest user or process to crash the host system resulting in
a denial of service.
    
Patch 1/ is to force the user fault if PFNMAP vma might be DMA mapped
before user access.
    
Patch 2/ setup a vm_ops handler to support dynamic faulting instead of calling
remap_pfn_range(). Also provides a list of vmas actively mapping the area which
can later use to invalidate those mappings.
    
Patch 3/ block the user from accessing memory spaces which is disabled by using
new vma list support to zap, or invalidate, those memory mappings in order to
force them to be faulted back in on access.
    
Upstreamed patches link:
https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home
        
[PATCH v4.14.y 1/3]:
Backporting of upsream commit 41311242221e:
vfio/type1: Support faulting PFNMAP vmas
        
[PATCH v4.14.y 2/3]:
Backporting of upsream commit 11c4cd07ba11:
vfio-pci: Fault mmaps to enable vma tracking
        
[PATCH v4.14.y 3/3]:
Backporting of upsream commit abafbc551fdd:
vfio-pci: Invalidate mmaps and block MMIO access on disabled memory
```
#### [PATCH v4.9.y 0/3] vfio: Fix for CVE-2020-12888
##### From: Ajay Kaher <akaher@vmware.com>

```c
From patchwork Mon Sep  7 20:35:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11762219
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4945112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:40:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89F7521582
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:40:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727838AbgIGUjy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 16:39:54 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:52489 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726810AbgIGUjp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 16:39:45 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 13:39:42 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id BC1FA40735;
        Mon,  7 Sep 2020 13:39:42 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.9.y 0/3] vfio: Fix for CVE-2020-12888
Date: Tue, 8 Sep 2020 02:05:17 +0530
Message-ID: <1599510917-23734-4-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599510917-23734-1-git-send-email-akaher@vmware.com>
References: <1599510917-23734-1-git-send-email-akaher@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2020-12888 Kernel: vfio: access to disabled MMIO space of some
devices may lead to DoS scenario
    
The VFIO modules allow users (guest VMs) to enable or disable access to the
devices' MMIO memory address spaces. If a user attempts to access (read/write)
the devices' MMIO address space when it is disabled, some h/w devices issue an
interrupt to the CPU to indicate a fatal error condition, crashing the system.
This flaw allows a guest user or process to crash the host system resulting in
a denial of service.
    
Patch 1/ is to force the user fault if PFNMAP vma might be DMA mapped
before user access.
    
Patch 2/ setup a vm_ops handler to support dynamic faulting instead of calling
remap_pfn_range(). Also provides a list of vmas actively mapping the area which
can later use to invalidate those mappings.
    
Patch 3/ block the user from accessing memory spaces which is disabled by using
new vma list support to zap, or invalidate, those memory mappings in order to
force them to be faulted back in on access.
    
Upstreamed patches link:
https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home
        
[PATCH v4.9.y 1/3]:
Backporting of upsream commit 41311242221e:
vfio/type1: Support faulting PFNMAP vmas
        
[PATCH v4.9.y 2/3]:
Backporting of upsream commit 11c4cd07ba11:
vfio-pci: Fault mmaps to enable vma tracking
        
[PATCH v4.9.y 3/3]:
Backporting of upsream commit abafbc551fdd:
vfio-pci: Invalidate mmaps and block MMIO access on disabled memory
```
