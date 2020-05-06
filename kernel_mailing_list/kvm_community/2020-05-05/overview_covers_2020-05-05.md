

#### [PATCH v4 0/8] s390x/vfio-ccw: Channel Path Handling [KVM]
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Tue May  5 12:27:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11528909
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D2FC17E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F5B820735
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 12:27:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728842AbgEEM1y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 08:27:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:51822 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728695AbgEEM1w (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 08:27:52 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 045CRP3X076301;
        Tue, 5 May 2020 08:27:51 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s28g962u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:51 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 045CRe9j077859;
        Tue, 5 May 2020 08:27:51 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30s28g960y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 08:27:50 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 045CQ4Su012085;
        Tue, 5 May 2020 12:27:48 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma05fra.de.ibm.com with ESMTP id 30s0g5jt0h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 05 May 2020 12:27:48 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 045CQZ69197336
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 May 2020 12:26:35 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 72D71A4064;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6081EA4054;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  5 May 2020 12:27:45 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 16DB6E01C6; Tue,  5 May 2020 14:27:45 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v4 0/8] s390x/vfio-ccw: Channel Path Handling [KVM]
Date: Tue,  5 May 2020 14:27:37 +0200
Message-Id: <20200505122745.53208-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-05-05_06:2020-05-04,2020-05-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 suspectscore=0
 impostorscore=0 lowpriorityscore=0 phishscore=0 priorityscore=1501
 mlxscore=0 malwarescore=0 bulkscore=0 adultscore=0 mlxlogscore=999
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005050093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here is a new pass at the channel-path handling code for vfio-ccw.
Changes from previous versions are recorded in git notes for each patch.
Patches 5 through 7 got swizzled a little bit, in order to better
compartmentalize the code they define. Basically, the IRQ definitions
were moved from patch 7 to 5, and then patch 6 was placed ahead of
patch 5.

I have put Conny's r-b's on patches 1, 3, 4, (new) 5, and 8, and believe
I have addressed all comments from v3, with two exceptions:

> I'm wondering if we should make this [vfio_ccw_schib_region_{write,release}]
> callback optional (not in this patch).

I have that implemented on top of this series, and will send later as part
of a larger cleanup series.

> One thing though that keeps coming up: do we need any kind of
> serialization? Can there be any confusion from concurrent reads from
> userspace, or are we sure that we always provide consistent data?

I _think_ this is in good shape, though as suggested another set of
eyeballs would be nice. There is still a problem on the main
interrupt/FSM path, which I'm not attempting to address here.

With this code plus the corresponding QEMU series (posted momentarily)
applied I am able to configure off/on a CHPID (for example, by issuing
"chchp -c 0/1 xx" on the host), and the guest is able to see both the
events and reflect the updated path masks in its structures.

v3: https://lore.kernel.org/kvm/20200417023001.65006-1-farman@linux.ibm.com/
v2: https://lore.kernel.org/kvm/20200206213825.11444-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20191115025620.19593-1-farman@linux.ibm.com/

Eric Farman (3):
  vfio-ccw: Refactor the unregister of the async regions
  vfio-ccw: Refactor IRQ handlers
  vfio-ccw: Add trace for CRW event

Farhan Ali (5):
  vfio-ccw: Introduce new helper functions to free/destroy regions
  vfio-ccw: Register a chp_event callback for vfio-ccw
  vfio-ccw: Introduce a new schib region
  vfio-ccw: Introduce a new CRW region
  vfio-ccw: Wire up the CRW irq and CRW region

 Documentation/s390/vfio-ccw.rst     |  38 ++++++-
 drivers/s390/cio/Makefile           |   2 +-
 drivers/s390/cio/vfio_ccw_chp.c     | 148 +++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_drv.c     | 165 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_ops.c     |  65 ++++++++---
 drivers/s390/cio/vfio_ccw_private.h |  16 +++
 drivers/s390/cio/vfio_ccw_trace.c   |   1 +
 drivers/s390/cio/vfio_ccw_trace.h   |  30 +++++
 include/uapi/linux/vfio.h           |   3 +
 include/uapi/linux/vfio_ccw.h       |  18 +++
 10 files changed, 458 insertions(+), 28 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_chp.c
```
#### [PATCH 0/3] KVM: X86: Two fixes for KVM_SET_GUEST_DEBUG,
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Tue May  5 20:49:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11529879
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4976215E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 20:50:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30A8C20721
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 20:50:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GJUdHb+w"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729289AbgEEUu0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 16:50:26 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:31665 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728660AbgEEUuH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 May 2020 16:50:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588711806;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=aTLHVMbsIaqAX7BaSrLpdm3P4nxyMTwYs/IkveEjuuM=;
        b=GJUdHb+wdANeh2PjO3788dB52RQcEUOexz0eR/BFsxxXZntHDl2TCOePkYmrpBaSZ2mp+B
        TV6GvPRRJz1Niwkg4KrD5k+5AZyV/pVh29/mD/SlQhZS9mBqw1gqzpHR/0SlSrfT7aReQm
        j2Y7aezXLfHi/ef45qDfMba+q7n5mZc=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-482-YKQSZ9DROw-5ay_RB3EFXA-1; Tue, 05 May 2020 16:50:03 -0400
X-MC-Unique: YKQSZ9DROw-5ay_RB3EFXA-1
Received: by mail-qv1-f70.google.com with SMTP id c5so3478991qvi.10
        for <kvm@vger.kernel.org>; Tue, 05 May 2020 13:50:03 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=aTLHVMbsIaqAX7BaSrLpdm3P4nxyMTwYs/IkveEjuuM=;
        b=O1BfpaW8XgmZ317phAwdthnL3H0Q2Vh+huYYTAcEUuhVTLwcpS1YFnGU3zBE/LPPzi
         zttM5BE4dHYL7Wur7xWsaCRPIaSrwMb8262ocbTJxksh6bV9Ns3sVaUNemrWMdYkEuS/
         Qkguf3mhmS4TxqIU1N4Q4SKDgQ0cmF4zlLZyceWGs3YcjjTZdpFB0bRQQhxupPyK8ux/
         ajEG+sg8l0VbXjC8Soe30LGt6raX8QWuooI5kziMLFmW7HHLwMp7u1dHdkPkknI84jeg
         VZleypgpmGdyXaIWap9nMOB0ucnCcuh8uvgjji3RkorVfU23EyLxmwiaSwagmAm04mh+
         EzEA==
X-Gm-Message-State: AGi0PuZPH+LWNeB/kxKRzMDItJHb7qzEAUMtnCDp8KDlY68jjoKNH59A
        BygNJwMSoDr1j3s7g5yozQL6e4Tch4aU/nw0GulqSkKTg/sKdWrO0tKbHADIXCcrtDRR8uCaGJy
        546KxBemyIODj
X-Received: by 2002:ac8:5653:: with SMTP id 19mr4679677qtt.252.1588711802814;
        Tue, 05 May 2020 13:50:02 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJZWCseS8WCKKpT3aDra1sX1ikSoUZ46+/xjslmiir4MILBMJv5VWPlzmW+jNOSrx1v5dxLGw==
X-Received: by 2002:ac8:5653:: with SMTP id 19mr4679660qtt.252.1588711802514;
        Tue, 05 May 2020 13:50:02 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id 193sm19380qkl.42.2020.05.05.13.50.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 05 May 2020 13:50:01 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 0/3] KVM: X86: Two fixes for KVM_SET_GUEST_DEBUG,
 and a selftest
Date: Tue,  5 May 2020 16:49:57 -0400
Message-Id: <20200505205000.188252-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first two patches try to fix two issues I found (I think) with the
selftest.  The 3rd patch is the test itself.  Note, we need below patches to be
applied too for the test to work:

        KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
        KVM: selftests: Fix build for evmcs.h

Please review, thanks.

Peter Xu (3):
  KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
  KVM: X86: Fix single-step with KVM_SET_GUEST_DEBUG
  KVM: selftests: Add KVM_SET_GUEST_DEBUG test

 arch/x86/kvm/vmx/vmx.c                        |   2 +-
 arch/x86/kvm/x86.c                            |   2 +-
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   9 +
 .../testing/selftests/kvm/x86_64/debug_regs.c | 180 ++++++++++++++++++
 6 files changed, 194 insertions(+), 2 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/debug_regs.c
```
#### [PATCH v8 00/18] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Tue May  5 21:13:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11529915
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57F3A912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:14:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3322920735
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:14:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="4SuVa8px"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729011AbgEEVOF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 17:14:05 -0400
Received: from mail-dm6nam12on2082.outbound.protection.outlook.com
 ([40.107.243.82]:6184
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726350AbgEEVOE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 17:14:04 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Y3EehEmi30G9aN/ONUdl64uKYJP1AHjjmfJcTZzvTsRYut3aqHKjcDigYxF0fC4TcbAFO/BswSqRBKsATuswhJ+TrlcVV1VGU8vtB0I+y4mXkM72GjSFkno4CUfomcVTXILAgfOehQ3zwKg8iMed08q+edy8a9JjjcvX9LKI8clq7td6gF42T0BJ0K1j3/AXB5HcDfp9gfjRSzwJgsRlGey124WJgzyhdk8RZEOvCEjc42y15bJMH+e7QlbpLXvAhlBSy51vYKQ2p7+Ds5GOYNgBHaW7b9wOo1LXiBqnxr95bjvCrDwFTODiM3b1iSvRjywddjZPwbBz68TTu8qpNw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=RQ0DRrQtL1xSXgKOx0Yl+9HFkiA4WpumX4oMlpwWUXs=;
 b=lMxHQ8zI4dHo+whtKqEYo8Jvxd02pcyB2ikuosDYOvJtV7o/JLVG7reJBPwgXmT+8KlLsfpqroMcPcthKtJcS+yS0TqVfVFWAZznwTZL/QE5JLYnNQgkkSoMcwX/eoFDjx6T7KSLZuhsEDQyV+xMj+oFSeaozU5zgrFoh6Tk2BOCsdkduFGPojaN97hioLPZv6kcM+4CHa3CJ51pQBGbHrn1Hd1KOtkEs7hA8Z3pKpa6D2GEQhqDp4lJOlklmlSJamDCbdaEPAkWl8X+aFodBlNe5sLFRHM5Yq2XywfIQQ+DNRHznRHDmwLDPc7AbONlB/YlxM7gAJpN56Pg1KbS0g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=RQ0DRrQtL1xSXgKOx0Yl+9HFkiA4WpumX4oMlpwWUXs=;
 b=4SuVa8pxyr2dlqt6MsFF7OABZVjqi5fXsHRKypopGETdyNprsdfPcST+XzDVCUdtT+o/Xqi0PMJDnsR4WG0HQDS1JOhWP9qfwTABNdGGxiYgjfrwdtLO9drb1pOGDzpSvZfIpUNZtFF4nLseknC4bqpO38cimBgUrrZePJXLB4U=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB2518.namprd12.prod.outlook.com (2603:10b6:4:b0::33) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2958.20; Tue, 5 May 2020 21:14:00 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::6962:a808:3fd5:7adb]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::6962:a808:3fd5:7adb%3]) with mapi id 15.20.2958.030; Tue, 5 May 2020
 21:14:00 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, Thomas.Lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, rientjes@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v8 00/18] Add AMD SEV guest live migration support
Date: Tue,  5 May 2020 21:13:49 +0000
Message-Id: <cover.1588711355.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: DM5PR04CA0061.namprd04.prod.outlook.com
 (2603:10b6:3:ef::23) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR04CA0061.namprd04.prod.outlook.com (2603:10b6:3:ef::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.20 via Frontend
 Transport; Tue, 5 May 2020 21:13:59 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 019c3616-da4d-45fc-36c3-08d7f1393ac0
X-MS-TrafficTypeDiagnostic: DM5PR12MB2518:|DM5PR12MB2518:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB251843CC345F8C2D2ACFB77A8EA70@DM5PR12MB2518.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:229;
X-Forefront-PRVS: 0394259C80
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 WD7W6n+t6jJkfmHFZkhUEKCQ63rbtu8zr6cT7ii2M6ax+8+OrqQ0xBidBYkiO9vasWRVpaByDo10gdEggVtxUZUIHq7PV2WKY7hV5hPW7h1GWg2l0V+YIaZa9geeAuvGJ4sjlu1qivmpKXJBqj7s8L0TCvsADR+M3QBAOaFghbNtcfZSfHq6/vTRWawD6ll2UlqijPW5KgyG75jdmFZdT7ccf8X047WJO0KOgiAz9kwdfSCqD2Okc3weF3LIb1dPmsO6qFEScRMrrFzCGaC30DLC1ff+CijdXc84ar4RRcO22GZmQi2hpa+3D74F9w5QNL1Wt36xF1ghnf5fUYJbyeSfhoj0b8T8ZeEx1dyjvQ097EhOi99D2mRCVR3ZS/ECgSv1Sh31qHLOEKV/s/pJh5SWdK6b9SRNm2Uus0qL6jTnS6YruboSe2fbl+WVIz8ZrW90kbtC+JJofzfPUZpijbR5Ewip10VfM8I826+W3D98igdyrs3HZai7zdewLshXnpvJNLdinqUBFjh4zT/TTSms61TOAwhvuE7wevDgcQ6MZ3Ia0RrgntgIL5QgW5AWy5rXupcBg9jn8kns5gpMYEwtFJhhZo7yuAyTm9KN9mXulxhQc5p/WRpNh2PsLBYDCL7Qt8Bm7OZqetvDd+0png==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(366004)(136003)(39860400002)(346002)(376002)(33430700001)(6916009)(26005)(36756003)(956004)(16526019)(478600001)(6486002)(2906002)(5660300002)(6666004)(2616005)(186003)(966005)(66476007)(7416002)(52116002)(8936002)(86362001)(7696005)(8676002)(66556008)(66946007)(4326008)(33440700001)(316002)(136400200001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 3iDiNNsEaihwnUjf//XBhxMXjbZZ9mc/lSFHbCRs9ZTpwmzOs3CgxTWda4izI2uWpXzXQZuRSmOukJLZ+PYR6ni3+bKtSzyk4B/eTXK+VTdx3uPjF7rMe2RFL8HDdKYBUBgB+f14v671AzIVtV70Y++749wg6whqxNun/7Q3TLRQiGr8+6DMPWO1rN8yJkiKFIvVC0DsI6cZgm/0+6O0Sx0YOShVZVoiw0SU/+P2a/eq0EOCCd4YLs04suq7ScubviW59vGehbj6czN3Z4HpUoWzO+VgVc0FVq28C9JOQ5bOX0gBb6opye4BGImmn12QMGLIVHpFBfOV+TFnBacDLpO+PAewNGfy6UA95ZInHbt3RSvoaE5FBS5JQTAiVt3qwHI5Y4OW0qA0w/n1dT8JKa/9gv/dM+9v/8tF9+vNXJFDbRnFeN0M4PpyQUjMhetFaGsIZikkg44TQsQxg4eJEld47qi36trnH8z2nB2sa0YQOrs+AM8pTXrHRJYbrNH7SbLZHxabPfuCTE/jG8hCjqfOcmLBkvYcRhHoST4l1jOP1Y1iuRTrAlqu0QtwCSmBgQFwPi1rRdakTH2S6Pi83fXOpTKf4CJCRP61YmG2G3kttKnWUeTScarb1BUGCjhgU72nFOJNnl+6TQEukrKpOQvkHjWOQcR+H1wrOIaFRz23Xh8RF/wiJppJ/YlGPDDhWSicewq7HlLBZxVKKOdVeZ9yHFb60ZW7CP/S2z1x04gX5P54TQFgo8e9L6vPyHdurmvi7DYvhuqZftF4P513v5gDrLOTxO9+4l9VNoUun5s=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 019c3616-da4d-45fc-36c3-08d7f1393ac0
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 May 2020 21:13:59.9269
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5IsrfyBe2SWd5Gcoz4wB8gsPGH7Mdp2R+07Bvcyi1j1ELktCm9Jm/Yx+FCketLAlsYHzs8MF9ISQbdfRwA4IpQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB2518
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch adds new ioctls KVM_{SET,GET}_PAGE_ENC_BITMAP. The ioctl can be used
by the qemu to get the page encrypted bitmap. Qemu can consult this bitmap
during the migration to know whether the page is encrypted.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR. The host returns error as part of
SET_PAGE_ENC_BITMAP ioctl if guest has not enabled live migration.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-migration-v8

[1] https://developer.amd.com/wp-content/resources/55766.PDF

Changes since v7:
- Removed the hypervisor specific hypercall/paravirt callback for
  SEV live migration and moved back to calling kvm_sev_hypercall3 
  directly.
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>, specifically fixed
  build error when CONFIG_HYPERVISOR_GUEST=y and
  CONFIG_AMD_MEM_ENCRYPT=n.
- Implicitly enabled live migration for incoming VM(s) to handle 
  A->B->C->... VM migrations.
- Fixed Documentation as per comments on v6 patches.
- Fixed error return path in sev_send_update_data() as per comments 
  on v6 patches. 

Changes since v6:
- Rebasing to mainline and refactoring to the new split SVM
  infrastructre.
- Move to static allocation of the unified Page Encryption bitmap
  instead of the dynamic resizing of the bitmap, the static allocation
  is done implicitly by extending kvm_arch_commit_memory_region() callack
  to add svm specific x86_ops which can read the userspace provided memory
  region/memslots and calculate the amount of guest RAM managed by the KVM
  and grow the bitmap.
- Fixed KVM_SET_PAGE_ENC_BITMAP ioctl to set the whole bitmap instead
  of simply clearing specific bits.
- Removed KVM_PAGE_ENC_BITMAP_RESET ioctl, which is now performed using
  KVM_SET_PAGE_ENC_BITMAP.
- Extended guest support for enabling Live Migration feature by adding a
  check for UEFI environment variable indicating OVMF support for Live
  Migration feature and additionally checking for KVM capability for the
  same feature. If not booted under EFI, then we simply check for KVM
  capability.
- Add hypervisor specific hypercall for SEV live migration by adding
  a new paravirt callback as part of x86_hyper_runtime.
  (x86 hypervisor specific runtime callbacks)
- Moving MSR handling for MSR_KVM_SEV_LIVE_MIG_EN into svm/sev code 
  and adding check for SEV live migration enabled by guest in the 
  KVM_GET_PAGE_ENC_BITMAP ioctl.
- Instead of the complete __bss_decrypted section, only specific variables
  such as hv_clock_boot and wall_clock are marked as decrypted in the
  page encryption bitmap

Changes since v5:
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>

Changes since v4:
- Host support has been added to extend KVM capabilities/feature bits to 
  include a new KVM_FEATURE_SEV_LIVE_MIGRATION, which the guest can
  query for host-side support for SEV live migration and a new custom MSR
  MSR_KVM_SEV_LIVE_MIG_EN is added for guest to enable the SEV live
  migration feature.
- Ensure that _bss_decrypted section is marked as decrypted in the
  page encryption bitmap.
- Fixing KVM_GET_PAGE_ENC_BITMAP ioctl to return the correct bitmap
  as per the number of pages being requested by the user. Ensure that
  we only copy bmap->num_pages bytes in the userspace buffer, if
  bmap->num_pages is not byte aligned we read the trailing bits
  from the userspace and copy those bits as is. This fixes guest
  page(s) corruption issues observed after migration completion.
- Add kexec support for SEV Live Migration to reset the host's
  page encryption bitmap related to kernel specific page encryption
  status settings before we load a new kernel by kexec. We cannot
  reset the complete page encryption bitmap here as we need to
  retain the UEFI/OVMF firmware specific settings.

Changes since v3:
- Rebasing to mainline and testing.
- Adding a new KVM_PAGE_ENC_BITMAP_RESET ioctl, which resets the 
  page encryption bitmap on a guest reboot event.
- Adding a more reliable sanity check for GPA range being passed to
  the hypercall to ensure that guest MMIO ranges are also marked
  in the page encryption bitmap.

Changes since v2:
 - reset the page encryption bitmap on vcpu reboot

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Ashish Kalra (7):
  KVM: SVM: Add support for static allocation of unified Page Encryption
    Bitmap.
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  KVM: x86: Add guest support for detecting and enabling SEV Live
    Migration feature.
  KVM: x86: Mark _bss_decrypted section variables as decrypted in page
    encryption bitmap.
  KVM: x86: Add kexec support for SEV Live Migration.
  KVM: SVM: Enable SEV live migration feature implicitly on Incoming
    VM(s).

Brijesh Singh (11):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status is changed
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++
 Documentation/virt/kvm/api.rst                |  71 ++
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  10 +
 arch/x86/include/asm/kvm_host.h               |   7 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |  11 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/uapi/asm/kvm_para.h          |   5 +
 arch/x86/kernel/kvm.c                         |  90 +++
 arch/x86/kernel/kvmclock.c                    |  12 +
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/svm/sev.c                        | 732 +++++++++++++++++-
 arch/x86/kvm/svm/svm.c                        |  21 +
 arch/x86/kvm/svm/svm.h                        |   9 +
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  35 +
 arch/x86/mm/mem_encrypt.c                     |  68 +-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  52 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 25 files changed, 1297 insertions(+), 9 deletions(-)
```
#### [PATCH v2 0/3] vfio-pci: Block user access to disabled device MMIO
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Tue May  5 21:54:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11530001
Return-Path: <SRS0=tDSI=6T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26E6E15E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:54:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0074B20746
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 May 2020 21:54:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z5awgtQ+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728756AbgEEVyo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 May 2020 17:54:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:28860 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728076AbgEEVyo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 May 2020 17:54:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588715682;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ruRIwLyK3gyVc7TdrpR1YTdwCD5wsXYlQVD4A6a2gC0=;
        b=Z5awgtQ+EzvoF8OL89jHpl6wo6hX46B4bHGEhTziC+RjddY6YSf0ZS4VqqBowbiOlykF4o
        Ged2iwtpftOgJQvXZ4hM+HKuhI7V54oL/WU9QQKK6hZ6HzsPbVqIdGDHBpWzsaVLRAiNH3
        0GXA5gKN90ySG8LbHASERl1yos4l4vo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-494-J0qlrQ_iOTu3mBLyNMRLpA-1; Tue, 05 May 2020 17:54:40 -0400
X-MC-Unique: J0qlrQ_iOTu3mBLyNMRLpA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AF113107ACCA;
        Tue,  5 May 2020 21:54:39 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BB7961FDE1;
        Tue,  5 May 2020 21:54:36 +0000 (UTC)
Subject: [PATCH v2 0/3] vfio-pci: Block user access to disabled device MMIO
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca
Date: Tue, 05 May 2020 15:54:36 -0600
Message-ID: <158871401328.15589.17598154478222071285.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:

Locking in 3/ is substantially changed to avoid the retry scenario
within the fault handler, therefore a caller who does not allow retry
will no longer receive a SIGBUS on contention.  IOMMU invalidations
are still not included here, I expect that will be a future follow-on
change as we're not fundamentally changing that issue in this series.
The 'add to vma list only on fault' behavior is also still included
here, per the discussion I think it's still a valid approach and has
some advantages, particularly in a VM scenario where we potentially
defer the mapping until the MMIO BAR is actually DMA mapped into the
VM address space (or the guest driver actually accesses the device
if that DMA mapping is eliminated at some point).  Further discussion
and review appreciated.  Thanks,

Alex

v1:

Add tracking of the device memory enable bit and block/fault accesses
to device MMIO space while disabled.  This provides synchronous fault
handling for CPU accesses to the device and prevents the user from
triggering platform level error handling present on some systems.
Device reset and MSI-X vector table accesses are also included such
that access is blocked across reset and vector table accesses do not
depend on the user configuration of the device.

This is based on the vfio for-linus branch currently in next, making
use of follow_pfn() in vaddr_get_pfn() and therefore requiring patch
1/ to force the user fault in the case that a PFNMAP vma might be
DMA mapped before user access.  Further PFNMAP iommu invalidation
tracking is not yet included here.

As noted in the comments, I'm copying quite a bit of the logic from
rdma code for performing the zap_vma_ptes() calls and I'm also
attempting to resolve lock ordering issues in the fault handler to
lockdep's satisfaction.  I appreciate extra eyes on these sections in
particular.

I expect this to be functionally equivalent for any well behaved
userspace driver, but obviously there is a potential for the user to
get -EIO or SIGBUS on device access.  The device is provided to the
user enabled and device resets will restore the command register, so
by my evaluation a user would need to explicitly disable the memory
enable bit to trigger these faults.  We could potentially remap vmas
to a zero page rather than SIGBUS if we experience regressions, but
without known code requiring that, SIGBUS seems the appropriate
response to this condition.  Thanks,

Alex
---

Alex Williamson (3):
      vfio/type1: Support faulting PFNMAP vmas
      vfio-pci: Fault mmaps to enable vma tracking
      vfio-pci: Invalidate mmaps and block MMIO access on disabled memory


 drivers/vfio/pci/vfio_pci.c         |  321 +++++++++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_config.c  |   36 +++-
 drivers/vfio/pci/vfio_pci_intrs.c   |   18 ++
 drivers/vfio/pci/vfio_pci_private.h |   12 +
 drivers/vfio/pci/vfio_pci_rdwr.c    |   12 +
 drivers/vfio/vfio_iommu_type1.c     |   36 ++++
 6 files changed, 405 insertions(+), 30 deletions(-)
```
