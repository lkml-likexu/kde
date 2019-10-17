

#### [RFC 0/2] Intel IFC VF driver for vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Oct 16 01:30:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11192195
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 921D076
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7BA47214AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389017AbfJPBbI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 21:31:08 -0400
Received: from mga17.intel.com ([192.55.52.151]:60917 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726786AbfJPBbI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 21:31:08 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Oct 2019 18:31:07 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,302,1566889200";
   d="scan'208";a="279378776"
Received: from lingshan-mobl5.ccr.corp.intel.com (HELO localhost.localdomain)
 ([10.249.68.79])
  by orsmga001.jf.intel.com with ESMTP; 15 Oct 2019 18:30:53 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC 0/2] Intel IFC VF driver for vdpa
Date: Wed, 16 Oct 2019 09:30:48 +0800
Message-Id: <20191016013050.3918-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.16.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:
 
This series intends to introduce Intel IFC VF NIC driver for Vhost
Data Plane Acceleration.
 
Here comes two main parts, one is ifcvf_base layer, which handles
hardware operations. The other is ifcvf_main layer handles VF
initialization, configuration and removal, which depends on
and complys to vhost_mdev https://lkml.org/lkml/2019/9/26/15 
 
This is a first RFC try, please help review.
 
Thanks!
BR
Zhu Lingshan


Zhu Lingshan (2):
  vhost: IFC VF hardware operation layer
  vhost: IFC VF vdpa layer

 drivers/vhost/ifcvf/ifcvf_base.c | 390 ++++++++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 137 ++++++++++
 drivers/vhost/ifcvf/ifcvf_main.c | 541 +++++++++++++++++++++++++++++++++++++++
 3 files changed, 1068 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c
```
#### [PATCH v2 0/4] vfio-ccw: A couple trace changes
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Wed Oct 16 01:58:18 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11192209
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0477139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:58:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A895B2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:58:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388939AbfJPB6d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 21:58:33 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55668 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388720AbfJPB6c (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Oct 2019 21:58:32 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9G1q3Ru073821
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 21:58:31 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vnq8sm3w3-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 21:58:31 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Wed, 16 Oct 2019 02:58:29 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 16 Oct 2019 02:58:26 +0100
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9G1wO3w29753438
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Oct 2019 01:58:24 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 85F9F4203F;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 714C942047;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id CD915E016E; Wed, 16 Oct 2019 03:58:23 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Steffen Maier <maier@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v2 0/4] vfio-ccw: A couple trace changes
Date: Wed, 16 Oct 2019 03:58:18 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 19101601-0028-0000-0000-000003AA6617
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101601-0029-0000-0000-0000246C7D7C
Message-Id: <20191016015822.72425-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-15_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=600 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910160015
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here a couple updates to the vfio-ccw traces in the kernel,
based on things I've been using locally.  Perhaps they'll
be useful for future debugging.

Steffen's comments earlier today (thank you!) were simple enough
that here's a quick turnaround on a v2:

v1/RFC -> v2:
 - Convert state/event=%x to %d
 - Use individual fields for cssid/ssid/sch_no, to enable
   filtering by device
 - Add 0x prefix to remaining %x substitution in existing trace

Eric Farman (4):
  vfio-ccw: Refactor how the traces are built
  vfio-ccw: Trace the FSM jumptable
  vfio-ccw: Add a trace for asynchronous requests
  vfio-ccw: Rework the io_fctl trace

 drivers/s390/cio/Makefile           |  4 +-
 drivers/s390/cio/vfio_ccw_cp.h      |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c     | 11 +++--
 drivers/s390/cio/vfio_ccw_private.h |  1 +
 drivers/s390/cio/vfio_ccw_trace.c   | 14 ++++++
 drivers/s390/cio/vfio_ccw_trace.h   | 76 ++++++++++++++++++++++++++---
 6 files changed, 93 insertions(+), 14 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c
```
#### [PATCH V3 0/2] target/i386/kvm: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
From patchwork Wed Oct 16 13:07:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11193339
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C5C98112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 13:07:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A5B6F21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 13:07:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Oe2or1AE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405311AbfJPNHe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 09:07:34 -0400
Received: from mail-pf1-f193.google.com ([209.85.210.193]:41163 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2405306AbfJPNHe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 09:07:34 -0400
Received: by mail-pf1-f193.google.com with SMTP id q7so14692453pfh.8
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 06:07:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=wQCJmNzmQsC9KNIjHMU1j2cgYJLfCM+agj01R4DYfjE=;
        b=Oe2or1AEnGi2tuxYEI+dDM6EqbS93wmPnH5+gXDxmvkVXF7KJnYVqfREtqDuHPwtlL
         KrhCNoGau/eOsWVoyWIgQSEtiJgmoJlgYtoltCXwYia7/dCmM7rbKoCes9HsTPyJrpE4
         UOp/N0DqDyEmHKreDXM6Z+B27pUGnsIt744FeHQwu9mDIVqnQoX6t0y0nKRdmLE6ZSj4
         wTSd9iRtTAYZOf0EEwxu/1ZzJozZUzpOFdPy4FPogV1acswssVFeQQq3Piiy0lx0J1zP
         2HnANWPP62uVD0rRtGdzecsjICguXgfIPYag+D0RLBOHv19e1AEuTKSVYd1zwkNja7D4
         q+tQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=wQCJmNzmQsC9KNIjHMU1j2cgYJLfCM+agj01R4DYfjE=;
        b=VctCe98zBAyHY1OWfmap7m5BkYelXZBr0YChMycuY0lJMA2Bg1dCgTOjuDjPV4kDx0
         giJjeWBjDSBlcjcKlNcFcz5nD14R2CX1zkqdGhS0PNgyrdycty5RY2NuzdKInJxebmFi
         Kdn1EhZY60AIz4B2YnnExzq0On1AyTRdbDM+7rkYokY8e9muE+DkeVQFCr+rbOt+l7QJ
         uHHBl8+QQzIsAmH9iMZzh4jL1FE5e64eXrDEDOw3QnT1XRCX+HBX/u0MDGmdaO/7Wval
         hOh3ru/6SD7ai9ThpFuoHOC4XN3dwqj/hjbccTlYAJAJdKNo+M/IsgfIupuqHxxZz1jA
         Yc7A==
X-Gm-Message-State: APjAAAWrGEl+sFdPVbWiayO9KJqwji+WBjCJJcaHhbwahCCYtUxr0v/z
        1rX9w0wixMeguEGYIUnArRmtmbhEQ2U=
X-Google-Smtp-Source: 
 APXvYqz86v6HgU7P7jaCkPhMGAi8X8SUCsEErtJmXv76sPMHpWi5QQGtmQNnOcoKXrKc30+cx6p6Aw==
X-Received: by 2002:aa7:96ba:: with SMTP id g26mr44752072pfk.45.1571231253825;
        Wed, 16 Oct 2019 06:07:33 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 s97sm2792296pjc.4.2019.10.16.06.07.30
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Wed, 16 Oct 2019 06:07:33 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: mst@redhat.com, cohuck@redhat.com, pbonzini@redhat.com,
        rth@twiddle.net, ehabkost@redhat.com, mtosatti@redhat.com,
        rkagan@virtuozzo.com, vkuznets@redhat.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, kvm@vger.kernel.org,
        qemu-devel@nongnu.org
Subject: [PATCH V3 0/2] target/i386/kvm: Add Hyper-V direct tlb flush support
Date: Wed, 16 Oct 2019 21:07:23 +0800
Message-Id: <20191016130725.5045-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

This patchset is to enable Hyper-V direct tlbflush
feature. The feature is to let L0 hypervisor to handle
tlb flush hypercall for L1 hypervisor.

Tianyu Lan (2):
  linux headers: update against Linux 5.4-rc2
  target/i386/kvm: Add Hyper-V direct tlb flush support

 docs/hyperv.txt                              | 10 ++++
 include/standard-headers/asm-x86/bootparam.h |  2 +
 include/standard-headers/asm-x86/kvm_para.h  |  1 +
 include/standard-headers/linux/ethtool.h     | 24 ++++++++++
 include/standard-headers/linux/pci_regs.h    | 19 +++++++-
 include/standard-headers/linux/virtio_ids.h  |  2 +
 include/standard-headers/linux/virtio_pmem.h |  6 +--
 linux-headers/asm-arm/kvm.h                  | 16 ++++++-
 linux-headers/asm-arm/unistd-common.h        |  2 +
 linux-headers/asm-arm64/kvm.h                | 21 +++++++-
 linux-headers/asm-generic/mman-common.h      | 18 ++++---
 linux-headers/asm-generic/mman.h             | 10 ++--
 linux-headers/asm-generic/unistd.h           | 10 +++-
 linux-headers/asm-mips/mman.h                |  3 ++
 linux-headers/asm-mips/unistd_n32.h          |  2 +
 linux-headers/asm-mips/unistd_n64.h          |  2 +
 linux-headers/asm-mips/unistd_o32.h          |  2 +
 linux-headers/asm-powerpc/mman.h             |  6 +--
 linux-headers/asm-powerpc/unistd_32.h        |  2 +
 linux-headers/asm-powerpc/unistd_64.h        |  2 +
 linux-headers/asm-s390/kvm.h                 |  6 +++
 linux-headers/asm-s390/unistd_32.h           |  2 +
 linux-headers/asm-s390/unistd_64.h           |  2 +
 linux-headers/asm-x86/kvm.h                  | 28 ++++++++---
 linux-headers/asm-x86/unistd.h               |  2 +-
 linux-headers/asm-x86/unistd_32.h            |  2 +
 linux-headers/asm-x86/unistd_64.h            |  2 +
 linux-headers/asm-x86/unistd_x32.h           |  2 +
 linux-headers/linux/kvm.h                    | 12 ++++-
 linux-headers/linux/psp-sev.h                |  5 +-
 linux-headers/linux/vfio.h                   | 71 ++++++++++++++++++++--------
 target/i386/cpu.c                            |  2 +
 target/i386/cpu.h                            |  1 +
 target/i386/kvm.c                            | 24 ++++++++++
 34 files changed, 262 insertions(+), 59 deletions(-)
```
#### [PATCH v3 0/4] vfio-ccw: A couple trace changes
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Wed Oct 16 14:20:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11193429
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D8B0C17E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 14:20:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C436E218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 14:20:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393985AbfJPOUu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 10:20:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49328 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2393973AbfJPOUu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Oct 2019 10:20:50 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9GE3T1O093491
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 10:20:48 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vp369n230-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 10:20:48 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Wed, 16 Oct 2019 15:20:47 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 16 Oct 2019 15:20:44 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9GEKgxg21168412
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Oct 2019 14:20:43 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CDDDBA405B;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C3D50A405C;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 59B47E01FD; Wed, 16 Oct 2019 16:20:42 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Steffen Maier <maier@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 0/4] vfio-ccw: A couple trace changes
Date: Wed, 16 Oct 2019 16:20:36 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 19101614-4275-0000-0000-000003729FCC
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101614-4276-0000-0000-00003885B5A2
Message-Id: <20191016142040.14132-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-16_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=609 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910160124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here a couple updates to the vfio-ccw traces in the kernel,
based on things I've been using locally.  Perhaps they'll
be useful for future debugging.

v2 -> v3:
 - Added Conny's r-b to patches 1, 2, 4
 - s/command=%d/command=0x%x/ in patch 3 [Cornelia Huck]

v1/RFC -> v2:
 - Convert state/event=%x to %d [Steffen Maier]
 - Use individual fields for cssid/ssid/sch_no, to enable
   filtering by device [Steffen Maier]
 - Add 0x prefix to remaining %x substitution in existing trace

Eric Farman (4):
  vfio-ccw: Refactor how the traces are built
  vfio-ccw: Trace the FSM jumptable
  vfio-ccw: Add a trace for asynchronous requests
  vfio-ccw: Rework the io_fctl trace

 drivers/s390/cio/Makefile           |  4 +-
 drivers/s390/cio/vfio_ccw_cp.h      |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c     | 11 +++--
 drivers/s390/cio/vfio_ccw_private.h |  1 +
 drivers/s390/cio/vfio_ccw_trace.c   | 14 ++++++
 drivers/s390/cio/vfio_ccw_trace.h   | 76 ++++++++++++++++++++++++++---
 6 files changed, 93 insertions(+), 14 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c
```
#### [PATCH v9 00/22] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
From patchwork Wed Oct 16 16:08:02 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11193647
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49F59912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 16:08:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 15EE321D7A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 16:08:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="pV8AJmxd";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="FjpPncGw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387435AbfJPQII (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 12:08:08 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:14144 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728234AbfJPQIH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 12:08:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1571242086; x=1602778086;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=dfLLuN+la3iKy6ZX8Z5xrKNppveTKZfMpAZXhDH99yg=;
  b=pV8AJmxdtMjDlDgqcv+rDixEpXjJu3XsECCsPzVVLSmZ/cS0LFVkTXUM
   vgor1CCEcXMJkU18I1pTK2v2/2H38DzJohOv4rrCfNymeo/nyCWQvWQOC
   7H7FPKZKEPrwDSnclHmRx5lBlswZve+4MknzxmXY7WPbc4cIeXRIiGp/8
   YuEbkGtndMvTMXVGgIsU0lEIsZT5b0EJNyzlpc4/IxqeeWEyR2pTGxlOu
   QHM/7MGCEBbRcjzqo9jlE4p2jhqgG2NfddpJ/c0r35VOVSnQvHy0WDEaG
   KmYtw3cOzq/zMs/WwIOU4iaSUHoZg4MivJ09MaJeQxEeiQ9LsYnQtzCz3
   Q==;
IronPort-SDR: 
 PyR8FXrA+Oo/TUxPkU/9BwGytWTeQhrkCIDMl1ai5zGXxvzBI6qQ42ZYyUBayq7SGwx79WMQ6u
 zkLb2T+Jhl9+CmykdoVBe8BWu+eW2whTKnNL2N1Lxv1nLWOI16OFxw+5/6/c5yKLRVPkkMt58k
 D49V6fi4BmzvTxYwVKcdafMDfB5IQCRvcduv7U403+M9nh5tJezd9DZMoM643GkyLtrjrXm2AH
 tZWMq2j72so9e08LuZxWs4CVBE+HjYWcOvIuSBfmGg4JKYmY0rwq8sZWP0S8U2EtpZxBq8b2N7
 biM=
X-IronPort-AV: E=Sophos;i="5.67,304,1566835200";
   d="scan'208";a="121448168"
Received: from mail-dm3nam03lp2052.outbound.protection.outlook.com (HELO
 NAM03-DM3-obe.outbound.protection.outlook.com) ([104.47.41.52])
  by ob1.hgst.iphmx.com with ESMTP; 17 Oct 2019 00:08:04 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=f9YB1nY9fFoo/i2Ev2Ti0T1YDvbnTFY3AntianmfnjVAdBQZ15FE/MEBIudsrIFpBym9JlhJox1ngA9Dra7DYAbeIoQPpVvUjQu2wok4WwdwwKpb4SWQ48DGV32O6YGcuzv/3eixJ4ZvSnB1mGE9ypF5kwM2VkDNObA/T6sp9ViTOQlCnUjOK8TtBu6YUMYBxReWo4cuj85PvHFiaml/YosyekoO2umw+7yQreesCEjdGazp/hAQLVGUBzwA8nK2R0fzTm921FUMQjPxRt5Ux0/QnKoz/ByQtmDb+iXWjFIsoVWmyH4+DBrSVDF/W/QPL0iDpoyr/eoIATyH+AyikA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=J91KfnOUqoFoWj199Ik90adrRRo0HPquPXLjl2e7yRY=;
 b=BuqFPWADAVIS223UIFGRNAJjZ75FuQ15wyao9EU7rbKBtDBS3Pa1lYxcqmBa7I4gG64ssLRq8OR2WBUr9NO6TkGkZk0yBQLRtcpS1T5pI7p6v6AHJqqrs8GmLqFztZqlmN8LiZ21QtNEVwGDkowZCLL9SAf+Yc+KGlq78k5EAUNGKJLe9XbEX58fV7uqqiV5g66leUM9BdcoCZ/IAiM+zAVwrBw6eXUNCxkxN/lUaKA1P2wRUVR5+Ktdbek1Cr8/6/KlA79iwgfXnAJAiVOymb7L3YnYsqiVM36Ft711wGqKh1cZzm2alN3W8vSnC6fUqQiqQpOS/STRAMKVrigRDA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=J91KfnOUqoFoWj199Ik90adrRRo0HPquPXLjl2e7yRY=;
 b=FjpPncGwPMwNJG/1G4DOprGiW/Iinf+b9F4Kv+iyMf1nfp+MMn3X9qgAZdq4eq2CR97drqRWcd7jlmD0QNYiKMmLtvDmY5/NBOrbrY3gNCayNFk3UEU3MH/9Oxipshj2GDdSpVQmjofK9cp6WWfxlScSRpj0IdSljTjWHn25RdM=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB6397.namprd04.prod.outlook.com (52.132.170.135) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2347.17; Wed, 16 Oct 2019 16:08:02 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a%7]) with mapi id 15.20.2347.023; Wed, 16 Oct 2019
 16:08:02 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v9 00/22] KVM RISC-V Support
Thread-Topic: [PATCH v9 00/22] KVM RISC-V Support
Thread-Index: AQHVhDvjgWUSb1QOnEOpmdfhfnPxUQ==
Date: Wed, 16 Oct 2019 16:08:02 +0000
Message-ID: <20191016160649.24622-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MAXPR01CA0098.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:5d::16) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [106.51.27.162]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 261cb235-cf59-4666-6d9f-08d75253057c
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: MN2PR04MB6397:
x-ms-exchange-purlcount: 3
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB639769652E62FDC250C1244F8D920@MN2PR04MB6397.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:277;
x-forefront-prvs: 0192E812EC
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(366004)(346002)(396003)(376002)(39860400002)(136003)(199004)(189003)(71190400001)(71200400001)(66556008)(66476007)(66446008)(64756008)(66946007)(6116002)(3846002)(14444005)(66066001)(52116002)(256004)(99286004)(25786009)(7416002)(14454004)(4326008)(478600001)(966005)(7736002)(8676002)(305945005)(110136005)(476003)(54906003)(86362001)(2616005)(316002)(102836004)(81166006)(486006)(55236004)(44832011)(6306002)(5660300002)(50226002)(26005)(9456002)(186003)(8936002)(36756003)(1076003)(6436002)(6512007)(2906002)(6486002)(386003)(81156014)(6506007);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6397;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 hpblZSej8o99pKKGUio2DnS/CuEHzt/vAZgGcbH7s/aFraIjTeeWKuU0RolJAeI1IGG47ZF7rSmTivIAc44cnCC7NJLJ6sdxi4cSSRpR9I3xGjLmSkr/fS4HelYJhU7NevcgjxwCGNCUM3e4rS/cW10/zYnXgKJs9kufHD65hGS1eA5RJbNUk8qvMH7Up9048Y+PLkJ0Ah8GAq7Hd5QAQfLnpmrG9Pb6x8Ut86TTAOF6TJEvDwz5rzzatw4/i5xaH4ogm1lkMg1rLYKbzFjHwtMu4eouw7vXzqA9uCI5r3UdELD8KZTSsiPYdugZi38eNwl9kAapqpjyuUyAbzA95AB7FuGwF7l+O5Q/cVlV8a/tYwk41fn4EUfTxSH8DNe9qLjaIWfqGojtQR7d9WLKdxff0C/CPo0qQW/4vvL0Ne+vxEC3HLw2Dhpm1ShR2UlMos/atmw/GQO4dy6XourizQ==
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 261cb235-cf59-4666-6d9f-08d75253057c
X-MS-Exchange-CrossTenant-originalarrivaltime: 16 Oct 2019 16:08:02.6107
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 WHOI3wvyQYz8gSHma6FaSJdWpE8MtiZartrjwyX3rRIAVlLcAn67exp/k2SX4DbOt1R+h76So10b/Iu7DB88nw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6397
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.
9. Forward unhandled SBI calls to KVM userspace.
10. Hugepage support for Guest/VM

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart hotplug emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v9 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch at:
https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/alistair/riscv-hyp-ext-v0.4.1 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
- Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
- Removed PATCH1, PATCH3, and PATCH20 because these already merged
- Use kernel doc style comments for ISA bitmap functions
- Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
  be added in-future
- Mark KVM RISC-V kconfig option as EXPERIMENTAL
- Typo fix in commit description of PATCH6 of v7 series
- Use separate structs for CORE and CSR registers of ONE_REG interface
- Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
- Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
- No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
- Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
- Added defines for checking/decoding instruction length
- Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
- Rebased patches on Linux-5.3-rc7
- Added "return_handled" in struct kvm_mmio_decode to ensure that
  kvm_riscv_vcpu_mmio_return() updates SEPC only once
- Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
- Updated git repo URL in MAINTAINERS entry

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (18):
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Forward unhandled SBI calls to userspace
  RISC-V: KVM: Simplify stage2 page table programming
  RISC-V: KVM: Remove per-CPU vsip_shadow variable
  RISC-V: KVM: Fix race-condition in kvm_riscv_vcpu_sync_interrupts()
  RISC-V: KVM: Document RISC-V specific parts of KVM API.
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.txt          | 158 +++-
 MAINTAINERS                             |  10 +
 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/include/asm/csr.h            |  58 ++
 arch/riscv/include/asm/hwcap.h          |  22 +
 arch/riscv/include/asm/kvm_host.h       | 260 +++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  30 +
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 111 +++
 arch/riscv/kernel/asm-offsets.c         | 148 ++++
 arch/riscv/kernel/cpufeature.c          |  83 +-
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  86 ++
 arch/riscv/kvm/mmu.c                    | 773 ++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  43 +
 arch/riscv/kvm/vcpu.c                   | 995 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 610 +++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 151 ++++
 arch/riscv/kvm/vcpu_switch.S            | 382 +++++++++
 arch/riscv/kvm/vcpu_timer.c             | 110 +++
 arch/riscv/kvm/vm.c                     |  86 ++
 arch/riscv/kvm/vmid.c                   | 123 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   8 +
 27 files changed, 4314 insertions(+), 10 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
---
2.17.1
```
