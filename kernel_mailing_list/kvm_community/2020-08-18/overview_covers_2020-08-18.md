

#### [PATCH v2 0/2] clocksource: arm_arch_timer: Some fixes
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Tue Aug 18 03:28:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11719729
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A7FC614E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 03:28:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9973620866
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 03:28:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726676AbgHRD23 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 23:28:29 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:9824 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726429AbgHRD23 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 23:28:29 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 2FCB945B8D7662B5BD6A;
        Tue, 18 Aug 2020 11:28:25 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Tue, 18 Aug 2020 11:28:16 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 0/2] clocksource: arm_arch_timer: Some fixes
Date: Tue, 18 Aug 2020 11:28:12 +0800
Message-ID: <20200818032814.15968-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

change log:

v2:
 - Do not revert commit 0ea415390cd3, fix it instead.
 - Correct the tags of second patch.

Keqian Zhu (2):
  clocksource: arm_arch_timer: Use stable count reader in erratum sne
  clocksource: arm_arch_timer: Correct fault programming of
    CNTKCTL_EL1.EVNTI

 drivers/clocksource/arm_arch_timer.c | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] s390x: Add Protected VM support
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
From patchwork Tue Aug 18 13:04:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11720769
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C4DC13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 13:05:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BBB5207DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 13:05:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Tmxyrv99"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726570AbgHRNFB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Aug 2020 09:05:01 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:6328 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726145AbgHRNEz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 Aug 2020 09:04:55 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07ID3CeN015352;
        Tue, 18 Aug 2020 09:04:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=HMiQAFf5HGojfQGl+89e7ASM4BszeeXwNiXrohrM/C8=;
 b=Tmxyrv99CmW12Tst7WM66DVMt87AePuTTcjpRjoVEZK+qA3EVUMmKqzvZ4MbCZaGIRvz
 GVOYdfS02mjoBP9odGKynmnMx1/9Wh9ElaB7nRD7dABK0IlMjTHD63Ab7vMibaYVLxyO
 GCRtXUaqchjS1ofDkD7QjUwUCwQqCL642l+lDHMGizUiO0SRCfcdA4QSPuY1R85vawHC
 Xh0x3F2J/fiKshxlzd39WXKHu14XsBfoE59XUJ+TfpGunItgXl3KMGRf9VVcAV3SMtFv
 /oMiiguLsqux1P4yveI5VVkLXJ9UEpK4BnrS49Grz38R0jsrDS55zUS3eewEITT9opcz 6g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304u7167p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 09:04:54 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07ID3Jav016015;
        Tue, 18 Aug 2020 09:04:54 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304u7166n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 09:04:53 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07ID0jYN022901;
        Tue, 18 Aug 2020 13:04:51 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 3304cc0p81-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 13:04:50 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07ID4muF29622644
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 18 Aug 2020 13:04:48 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 37DA14C040;
        Tue, 18 Aug 2020 13:04:48 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BC6D14C046;
        Tue, 18 Aug 2020 13:04:47 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.52.109])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 18 Aug 2020 13:04:47 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/4] s390x: Add Protected VM support
Date: Tue, 18 Aug 2020 15:04:20 +0200
Message-Id: <20200818130424.20522-1-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-18_09:2020-08-18,2020-08-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 impostorscore=0
 phishscore=0 mlxlogscore=999 lowpriorityscore=0 bulkscore=0 spamscore=0
 suspectscore=0 adultscore=0 priorityscore=1501 malwarescore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008180094
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for Protected Virtual Machine (PVM) tests. For starting a
PVM guest we must be able to generate a PVM image by using the
`genprotimg` tool from the s390-tools collection. This requires the
ability to pass a machine-specific host-key document, so the option
`--host-key-document` is added to the configure script.

For everybody's convenience there is a branch:
https://gitlab.com/mhartmay/kvm-unit-tests/-/tree/pv_v1

Changelog:
 RFC v2 -> v1:
  + Rebased
  + patch 1:
    - add r-b from Andrew
  + patch 2:
    - add explicit dependency on config.mak (Andrew)
    - add comment about the order of sourcing (Andrew)
  + patch 3:
    - drop dummy function (Andrew)
    - add arch_cmd hook function (Andrew)
  + patch 4:
    - rephrased the documentation of the configure option (Conny)
    - Skip test case if a PVM image wasn't built or the host-key document wasn't set (Conny)
    - Run PV tests by default
    
 RFC v1 -> RFC v2:
  + Remove `pv_support` option (Janosch, David)
  + Add some preliminary patches:
    - move "testname guard"
    - add support for architecture dependent functions
  + Add support for specifying a parmline file for the PV image
    generation. This is necessary for the `selftest` because the
    kernel cmdline set on the QEMU command line is ignored for PV
    guests

Marc Hartmayer (4):
  common.bash: run `cmd` only if a test case was found
  scripts: add support for architecture dependent functions
  run_tests/mkstandalone: add arch_cmd hook
  s390x: add Protected VM support

 README.md               |  3 ++-
 configure               |  9 +++++++++
 run_tests.sh            |  3 ---
 s390x/Makefile          | 17 +++++++++++++++--
 s390x/selftest.parmfile |  1 +
 s390x/unittests.cfg     |  1 +
 scripts/common.bash     | 21 +++++++++++++++++++--
 scripts/mkstandalone.sh |  4 ----
 scripts/s390x/func.bash | 35 +++++++++++++++++++++++++++++++++++
 9 files changed, 82 insertions(+), 12 deletions(-)
 create mode 100644 s390x/selftest.parmfile
 create mode 100644 scripts/s390x/func.bash
```
#### [PATCH v8 0/2] s390: virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Tue Aug 18 14:58:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11721393
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 954F4109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 15:01:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74B9920786
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 15:01:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="jzE/+AdW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727077AbgHRPA7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Aug 2020 11:00:59 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:48395 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726651AbgHRPA6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 Aug 2020 11:00:58 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07IF0DBA004146;
        Tue, 18 Aug 2020 11:00:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=25izQLYXYfVWZ0i4cAY3epGdXG76W5RcjkJkTe+0JMM=;
 b=jzE/+AdWdKPtTeBKXHpUotgoCIpsllkKpftVNpZeTXfxHG4snNkKdNdEwJ7UIlLf3XQU
 mLGzrXG75kcyPJKpTnas3n2ol7Ul2ItQNK5VY19nUyESyIg28vw8ftVdRLZMLnlTkVcP
 B6RmRWTaba6otVnhSn/uaVPLVOpop000lYDqARF6SKG8cmBahL0IaVkFBZ5lLhOvwGGK
 xpJhQPAOO8uq1OHRh59OWKl+CmDekVkgxoE3Pbe1OtYBP+m4g66TSFIyvnIYpgTBPyAj
 qhEJmAuxkRxXD3cMgNCTdaPYt6dYdZrPzFr2Yy74INQjNSQHk9jBny04Pro/EeowMlip iQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304r3cq03-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 11:00:52 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07IF0lTg007389;
        Tue, 18 Aug 2020 11:00:47 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304r3cnd3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 11:00:43 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07IEtjgu015594;
        Tue, 18 Aug 2020 14:58:36 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma02fra.de.ibm.com with ESMTP id 3304bbrfh3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Aug 2020 14:58:36 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07IEwXm426280302
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 18 Aug 2020 14:58:33 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 49D3342041;
        Tue, 18 Aug 2020 14:58:33 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A56DE4203F;
        Tue, 18 Aug 2020 14:58:32 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.28.154])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 18 Aug 2020 14:58:32 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v8 0/2] s390: virtio: let arch validate VIRTIO features
Date: Tue, 18 Aug 2020 16:58:29 +0200
Message-Id: <1597762711-3550-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-18_10:2020-08-18,2020-08-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 spamscore=0 mlxlogscore=999 bulkscore=0 suspectscore=1 priorityscore=1501
 malwarescore=0 impostorscore=0 adultscore=0 clxscore=1015 phishscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008180102
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

The goal of the series is to give a chance to the architecture
to validate VIRTIO device features.

in this respin:

I use the original idea from Connie for an optional
arch_has_restricted_memory_access.

I renamed the callback accordingly, added the definition of
ARCH_HAS_RESTRICTED_MEMORY_ACCESS inside the VIRTIO Kconfig
and the selection in the PROTECTED_VIRTUALIZATION_GUEST
config entry.


Regards,
Pierre

Pierre Morel (2):
  virtio: let arch validate VIRTIO features
  s390: virtio: PV needs VIRTIO I/O device protection

 arch/s390/Kconfig             |  1 +
 arch/s390/mm/init.c           | 30 ++++++++++++++++++++++++++++++
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       |  4 ++++
 include/linux/virtio_config.h |  9 +++++++++
 5 files changed, 50 insertions(+)
```
#### [PATCH v4 0/4] Restrict PV features to only enabled guests
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Tue Aug 18 15:24:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11721609
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C03513B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 15:24:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DEC0207DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 15:24:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=google.com header.i=@google.com header.b="wTWWWpxE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727896AbgHRPYj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Aug 2020 11:24:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60780 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726630AbgHRPYi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Aug 2020 11:24:38 -0400
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C9189C061389
        for <kvm@vger.kernel.org>; Tue, 18 Aug 2020 08:24:37 -0700 (PDT)
Received: by mail-pl1-x64a.google.com with SMTP id t19so6686685plr.19
        for <kvm@vger.kernel.org>; Tue, 18 Aug 2020 08:24:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=7RzMrCk4RpXzFZelAQn7ckmUoODhv+euE8W8ePc3K9Y=;
        b=wTWWWpxErHV4rTDzZdEPHoch/Y3kjxZKS/TcpKWrRyAj9lg0dWP/lbePzWDVf16vrN
         R4sgeryZ4+M6LxPHLeNMp5yVldYOda/o2yaWFqChb0O/uqmaJIpDUX+0LES+Cl853Al6
         lT5zLiXqgQvG3IHgPVIk5cwSMFLnVk0ER1v7s1Rl6vC0/EcEI3g71WLsC9did1Ln1hME
         P0F037PmwQ6IrQRjK+dAnTKYcJUDWn7liaz054jQqFTt4vjwmZmT6QESseFZ0gYyVI5U
         01oDN6rA/TQX4h15ONlhtksazri3PD/fm0Xu7tWOC2Mc3H6N/AFzNwCtRzx1bQwqk2kw
         7ksg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=7RzMrCk4RpXzFZelAQn7ckmUoODhv+euE8W8ePc3K9Y=;
        b=aS5fY4Mgcw3quKTou3FdUWLtzNswjyjAD//XVGafOPGgL4mwOHjQQc8Ofg2xmoisUG
         +MPGu8sQvXaNxiv3q+6n75xEZdxuayd1mU+XAzPr84/aXcZKwNvYIgp9hmOnK3dOJyY9
         sE1gmwT4kWpNchmIh57Csy47k2uTK0G9qjh0m9B69BwAIpf93sR0i+wNetXkGQiNiNIA
         tpqYtrYMo3BZCFJtyRKWDWc2MFeDBi8lBgWim3xVt3gcEZdCeLWXYBpecRnO4bxlLpV6
         9peWzjuUUYjONqAZqr81bL7eIsro/ioUgJR/fF4WbghebWk7zph2lc8ldAoUAgVjrT+F
         SaNw==
X-Gm-Message-State: AOAM533X+FrkHT/C7plsdFQp8bgr8aIMZ8+tbqQ7KTj8tE9Sl7Kn5IEw
        mU0KEpLTq4MaauametO25caF9rW2Cq4HQv5x86QzJR/QpCSaVRhiqvrFrMJv0sDNQ7sIQySkL/X
        afNGKMrYE0VR5CdJbs3Qrl1ueGjxXNvl1k6g3ZwQEnms5upV5PCuyqtD0sQ==
X-Google-Smtp-Source: 
 ABdhPJyezA8CzUfjzn2SnNZXVouGoDRSNixAGDsfHrLr6ieTvrnir5XeVl6vhmqjG+uIIAQ8uhoXXlvd1+4=
X-Received: from oupton2.c.googlers.com ([fda3:e722:ac3:10:24:72f4:c0a8:518e])
 (user=oupton job=sendgmr) by 2002:a17:90a:f014:: with SMTP id
 bt20mr296476pjb.0.1597764276848; Tue, 18 Aug 2020 08:24:36 -0700 (PDT)
Date: Tue, 18 Aug 2020 15:24:25 +0000
Message-Id: <20200818152429.1923996-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [PATCH v4 0/4] Restrict PV features to only enabled guests
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, KVM has allowed guests to use paravirtual interfaces regardless
of the configured CPUID. While almost any guest will consult the
KVM_CPUID_FEATURES leaf _before_ using PV features, it is still
undesirable to have such interfaces silently present.

This series aims to address the issue by adding explicit checks against
the guest's CPUID when servicing any paravirtual feature. Since this
effectively changes the guest/hypervisor ABI, a KVM_CAP is warranted to
guard the new behavior.

Patches 1-2 refactor some of the PV code in anticipation of the change.
Patch 3 introduces the checks + KVM_CAP. Finally, patch 4 fixes some doc
typos that were noticed when working on this series.

v1 => v2:
 - Strip Change-Id footers (checkpatch is your friend!)

v2 => v3:
 - Mark kvm_write_system_time() as static

v3 => v4:
 - Address Wanpeng's concerns regarding cpuid lookup

Parent commit: e792415c5d3e ("KVM: MIPS/VZ: Fix build error caused by 'kvm_run' cleanup")

Oliver Upton (4):
  kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper
    fn
  kvm: x86: set wall_clock in kvm_write_wall_clock()
  kvm: x86: only provide PV features if enabled in guest's CPUID
  Documentation: kvm: fix some typos in cpuid.rst

 Documentation/virt/kvm/api.rst   |  11 +++
 Documentation/virt/kvm/cpuid.rst |  88 +++++++++++-----------
 arch/x86/include/asm/kvm_host.h  |  15 ++++
 arch/x86/kvm/cpuid.c             |   7 ++
 arch/x86/kvm/cpuid.h             |  10 +++
 arch/x86/kvm/x86.c               | 122 +++++++++++++++++++++++--------
 include/uapi/linux/kvm.h         |   1 +
 7 files changed, 181 insertions(+), 73 deletions(-)
```
#### [PATCH v3 00/12] Allow userspace to manage MSRs
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Aug 18 21:15:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11722175
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6AE58109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 21:16:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 535822067C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 21:16:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="b2eihN35"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726947AbgHRVQR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Aug 2020 17:16:17 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59526 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726176AbgHRVQQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Aug 2020 17:16:16 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0B146C061389
        for <kvm@vger.kernel.org>; Tue, 18 Aug 2020 14:16:16 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id r1so23905613ybg.4
        for <kvm@vger.kernel.org>; Tue, 18 Aug 2020 14:16:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=xHJvUF7NEOJ5tKpmZv+XE90DfAQGLbwQcHvn8trP0MA=;
        b=b2eihN35v+GXolKLzSig5M72cFvSDzwmPBpq7YKmDoE1f+Sw85kRT9KHt0EqjDsL1f
         7iTCwRceXHPPvZAm6usjEzwJExedA73fBlxJd5eWtXbwVYxff/obibIqw16f+iK5qGcE
         eFkev0iscwnHP4okkLRkOFJwJo55APJ2AQYatX7xiZExQJGhn+Ktjap1zQ+WmIf+fzr+
         PvrIqdvCQRBixISS9K4i9Ee9js+Cy/TizISdx89ltA1kROp20cRBmMj2snt9WfvwP/q8
         J/MYtSbCy9BBEKSOa4NWA/WEal2Ll0vsV+Io8MkZVYFkLLqS/cMyvkowDEv4EkLm2gk+
         RAug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=xHJvUF7NEOJ5tKpmZv+XE90DfAQGLbwQcHvn8trP0MA=;
        b=tWeCkhAVMiJ58OxYatu7uxSC8o/aG5+i9luPTnD6dwC6TjjwN2n4TWmF+CtGv/SWYb
         xsL+aMvqgSCYxg0Md9z2a3XwstXz6v5RRPaA3wup6eLQ+rzPBVIijFRdRzU46Ry2UvMh
         xATPFKyGnvkdvCevB4/k7Ca45N1ouFeTSitQUk17fAObT4ZSJXiwTsJNELWJjum3VGXh
         TWVtGbPr+qgz30E4J8j29gSdDxp/Yg8lARpEIXnUeiK5rJmqjrURqpYW0RF8YctDh6KV
         MjuFdI4IEon12Tuyj14CyhCKMnpzw1wXRekDOsmh/40S+XxSBZGoS3CT7olri5venIHT
         S4vw==
X-Gm-Message-State: AOAM530OioehslvoMNKTCb6xz7zEdtu1K9bKEav9jLHvTz2eZL43BBOs
        GXBFMo73R1K3zxHiZADJlt/F6BAfe5+r/Y0p
X-Google-Smtp-Source: 
 ABdhPJwQAAfy6MFTPLF8YYNxLiTXeyLHm/XTBJ2s1i3Z0H6bJPKGWudT5lBXrNi1KDmndAxS9ppz97lR4eYsY2ZN
X-Received: by 2002:a25:cc12:: with SMTP id
 l18mr30292443ybf.224.1597785375229;
 Tue, 18 Aug 2020 14:16:15 -0700 (PDT)
Date: Tue, 18 Aug 2020 14:15:22 -0700
Message-Id: <20200818211533.849501-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [PATCH v3 00/12] Allow userspace to manage MSRs
From: Aaron Lewis <aaronlewis@google.com>
To: jmattson@google.com, graf@amazon.com
Cc: pshier@google.com, oupton@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series makes it possible for userspace to manage MSRs by having KVM
forward select MSRs to it when rdmsr and wrmsr are executed in the guest.
Userspace can set this up by calling the ioctl KVM_SET_EXIT_MSRS with a
list of MSRs it wants to manage.  When KVM encounters any of these MSRs
they are forwarded to userspace for processing.  Userspace can then read
from or write to the MSR, or it can also throw a #GP if needed.

This series includes the kernel changes needed to implement this feature
and a test that exercises this behavior.  Also, included is an
implementation of expection handling in selftests, which allows the test
to excercise throwing a #GP.

v1 -> v2:

  - Added support for generic instruction emulator bouncing to userspace when
    rdmsr or wrmsr are called, and userspace has asked to manage the MSR.
    These changes are committed in patch 3, and are based on changes made by
    Alexander Graf <graf@amazon.com>.
  - Added tests to excercise the code paths for em_{rdmsr,wrmsr} and
    emulator_{get,set}_msr.  These changes are committed in patch 8.

v2 -> v3:

  - Added the series by Alexander Graf <graf@amazon.com> to the beginning of
    This series (patches 1-3).  The two have a lot of overlap, so it made sense
    to combine them to simplify merging them both upstream.  Alex's changes
    account for the first 3 commits in this series.  As a result of incorporating
    those changes, commit 05/12 required some refactoring.
  - Split exception handling in selftests into its own commit (patch 09/12).
  - Split the changes to ucall_get() into it's own commit based on Andrew Jones
    suggestion, and added support for aarch64 and s390x.

Aaron Lewis (12):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Introduce allow list for MSR emulation
  KVM: selftests: Add test for user space MSR handling
  KVM: x86: Add ioctl for accepting a userspace provided MSR list
  KVM: x86: Add support for exiting to userspace on rdmsr or wrmsr
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs
  KVM: x86: Ensure the MSR bitmap never clears userspace tracked MSRs
  selftests: kvm: Fix the segment descriptor layout to match the actual
    layout
  selftests: kvm: Clear uc so UCALL_NONE is being properly reported
  selftests: kvm: Add exception handling to selftests
  selftests: kvm: Add a test to exercise the userspace MSR list
  selftests: kvm: Add emulated rdmsr, wrmsr tests

 Documentation/virt/kvm/api.rst                | 181 +++++++-
 arch/x86/include/asm/kvm_host.h               |  18 +
 arch/x86/include/uapi/asm/kvm.h               |  15 +
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/svm/svm.c                        |  93 ++--
 arch/x86/kvm/trace.h                          |  24 +
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        |  94 ++--
 arch/x86/kvm/vmx/vmx.h                        |   2 +-
 arch/x86/kvm/x86.c                            | 379 +++++++++++++++-
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |  21 +-
 .../selftests/kvm/include/x86_64/processor.h  |  29 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  17 +
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 tools/testing/selftests/kvm/lib/s390x/ucall.c |   3 +
 .../selftests/kvm/lib/x86_64/handlers.S       |  81 ++++
 .../selftests/kvm/lib/x86_64/processor.c      | 168 ++++++-
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |   3 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 221 +++++++++
 .../selftests/kvm/x86_64/userspace_msr_exit.c | 421 ++++++++++++++++++
 24 files changed, 1719 insertions(+), 96 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit.c
```
