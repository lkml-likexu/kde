

#### [PATCH v16 0/9] Enable ptp_kvm for arm/arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Wed Dec  9 06:09:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11960549
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 27DFAC2BB40
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 06:13:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F1C5D23B7C
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 06:13:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727860AbgLIGKr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 01:10:47 -0500
Received: from foss.arm.com ([217.140.110.172]:57756 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725878AbgLIGKp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 01:10:45 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DE0941042;
        Tue,  8 Dec 2020 22:09:53 -0800 (PST)
Received: from entos-thunderx2-desktop.shanghai.arm.com
 (entos-thunderx2-desktop.shanghai.arm.com [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 B07303F66B;
        Tue,  8 Dec 2020 22:09:47 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v16 0/9] Enable ptp_kvm for arm/arm64
Date: Wed,  9 Dec 2020 14:09:23 +0800
Message-Id: <20201209060932.212364-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we offen use ntp (sync time with remote network clock)
to sync time in VM. But the precision of ntp is subject to network delay
so it's difficult to sync time in a high precision.

kvm virtual ptp clock (ptp_kvm) offers another way to sync time in VM,
as the remote clock locates in the host instead of remote network clock.
It targets to sync time between guest and host in virtualization
environment and in this way, we can keep the time of all the VMs running
in the same host in sync. In general, the delay of communication between
host and guest is quiet small, so ptp_kvm can offer time sync precision
up to in order of nanosecond. Please keep in mind that ptp_kvm just
limits itself to be a channel which transmit the remote clock from
host to guest and leaves the time sync jobs to an application, eg. chrony,
in usersapce in VM.

How ptp_kvm works:
After ptp_kvm initialized, there will be a new device node under
/dev called ptp%d. A guest userspace service, like chrony, can use this
device to get host walltime, sometimes also counter cycle, which depends
on the service it calls. Then this guest userspace service can use those
data to do the time sync for guest.
here is a rough sketch to show how kvm ptp clock works.

|----------------------------|              |--------------------------|
|       guest userspace      |              |          host            |
|ioctl -> /dev/ptp%d         |              |                          |
|       ^   |                |              |                          |
|----------------------------|              |                          |
|       |   | guest kernel   |              |                          |
|       |   V      (get host walltime/counter cycle)                   |
|      ptp_kvm -> hypercall - - - - - - - - - - ->hypercall service    |
|                         <- - - - - - - - - - - -                     |
|----------------------------|              |--------------------------|

1. time sync service in guest userspace call ptp device through /dev/ptp%d.
2. ptp_kvm module in guest receives this request then invoke hypercall to route
into host kernel to request host walltime/counter cycle.
3. ptp_kvm hypercall service in host response to the request and send data back.
4. ptp (not ptp_kvm) in guest copy the data to userspace.

This ptp_kvm implementation focuses itself to step 2 and 3 and step 2 works
in guest comparing step 3 works in host kernel.

change log:

from v15 to v16:
        (1) remove ARM_PTP_NONE_COUNTER suggested by Marc.
        (2) add more detail for ptp_kvm doc.
        (3) fix ci issues reported by test robot.

from v14 to v15:
        (1) enable ptp_kvm on arm32 guest, also ptp_kvm has been tested
on both arm64 and arm32 guest running on arm64 kvm host.
        (2) move arch-agnostic part of ptp_kvm.rst into timekeeping.rst.
        (3) rename KVM_CAP_ARM_PTP_KVM to KVM_CAP_PTP_KVM as it should be
arch agnostic.
        (4) add description for KVM_CAP_PTP_KVM in Documentation/virt/kvm/api.rst.
        (5) adjust dependency in Kconfig for ptp_kvm.
        (6) refine multi-arch process in driver/ptp/Makefile.
        (7) fix make pdfdocs htmldocs issue for ptp_kvm doc.
        (8) address other issues from comments in v14.
        (9) fold hypercall service of ptp_kvm as a function.
        (10) rebase to 5.10-rc3.

from v13 to v14
        (1) rebase code on 5.9-rc3.
        (2) add a document to introduce implementation of PTP_KVM on
arm64.
        (3) fix comments issue in hypercall.c.
        (4) export arm_smccc_1_1_get_conduit using EXPORT_SYMBOL_GPL.
        (5) fix make issue on x86 reported by kernel test robot.

from v12 to v13:
        (1) rebase code on 5.8-rc1.
        (2) this patch set base on 2 patches of 1/8 and 2/8 from Will Decon.
        (3) remove the change to ptp device code of extend getcrosststamp.
        (4) remove the mechanism of letting user choose the counter type in
ptp_kvm for arm64.
        (5) add virtual counter option in ptp_kvm service to let user choose
the specific counter explicitly.

from v11 to v12:
        (1) rebase code on 5.7-rc6 and rebase 2 patches from Will Decon
including 1/11 and 2/11. as these patches introduce discover mechanism of
vendor smccc service.
        (2) rebase ptp_kvm hypercall service from standard smccc to vendor
smccc and add ptp_kvm to vendor smccc service discover mechanism.
        (3) add detail of why we need ptp_kvm and how ptp_kvm works in cover
letter.

from v10 to v11:
        (1) rebase code on 5.7-rc2.
        (2) remove support for arm32, as kvm support for arm32 will be
removed [1]
        (3) add error report in ptp_kvm initialization.

from v9 to v10:
        (1) change code base to v5.5.
        (2) enable ptp_kvm both for arm32 and arm64.
        (3) let user choose which of virtual counter or physical counter
should return when using crosstimestamp mode of ptp_kvm for arm/arm64.
        (4) extend input argument for getcrosstimestamp API.

from v8 to v9:
        (1) move ptp_kvm.h to driver/ptp/
        (2) replace license declaration of ptp_kvm.h the same with other
header files in the same directory.

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.

from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.

from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1] https://patchwork.kernel.org/cover/11373351/


Jianyong Wu (6):
  ptp: Reorganize ptp_kvm module to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  arm64/kvm: Add hypercall service for kvm ptp.
  ptp: arm/arm64: Enable ptp_kvm for arm/arm64
  doc: add ptp_kvm introduction for arm64 support
  arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (2):
  arm64: Probe for the presence of KVM hypervisor
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC

 Documentation/virt/kvm/api.rst              |  9 ++
 Documentation/virt/kvm/arm/index.rst        |  1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst      | 31 +++++++
 Documentation/virt/kvm/timekeeping.rst      | 35 ++++++++
 arch/arm/kernel/setup.c                     |  5 ++
 arch/arm64/kernel/setup.c                   |  1 +
 arch/arm64/kvm/arm.c                        |  1 +
 arch/arm64/kvm/hypercalls.c                 | 86 ++++++++++++++++--
 drivers/clocksource/arm_arch_timer.c        | 31 +++++++
 drivers/firmware/smccc/smccc.c              | 37 ++++++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  2 +
 drivers/ptp/ptp_kvm_arm.c                   | 45 ++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 84 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 96 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 59 +++++++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/ptp_kvm.h                     | 16 ++++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  2 +
 kernel/time/timekeeping.c                   |  1 +
 23 files changed, 498 insertions(+), 77 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
 create mode 100644 include/linux/ptp_kvm.h
```
#### [RFC 0/4] vfio-pci/zdev: Fixing s390 vfio-pci ISM support
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Wed Dec  9 20:27:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11962491
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 790B1C433FE
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:30:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4943E23B99
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:30:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388560AbgLIUaP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:30:15 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:40172 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388549AbgLIU34 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 9 Dec 2020 15:29:56 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B9KCvbH144267;
        Wed, 9 Dec 2020 15:29:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=yupa4joXOPYeGTBuhmT7BcsmAz7RWT5H1phB7fpnD0s=;
 b=Gxq8aEhBg8OgCUUKAeKa4gDEXS+RqHid+Ai+3KHpcLHJOWrnT/QAKygp55kyRfpteCd6
 JqSZc7b1jSW7RFRX1TqAoOPbgwZe4GhC3WOSxqqVhNsM3q4IY+3FhyRB0n3sEzcz14D2
 UY9qLOo8qn4cDTZGm14I5zAMZ7VL7U2QthsfYksYtbxw+8WsrGaSbVpGrXDgTBlHnp2o
 7xQJwal45QZo2IHQscKu7lkDhj29c1wu8sibvKzdt7lq1Ic3T+jU7cukRzyvYuyen6ch
 NgaHUj9Dvp4BMppJSq5sP7aHhepRad0XrunD07YSXOKqkMPEzliL2nud3uYe81EWShmI kA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35avfffg8q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 15:29:14 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B9KQsBT001975;
        Wed, 9 Dec 2020 15:29:14 -0500
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35avfffg8a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 15:29:14 -0500
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B9KM7iq015859;
        Wed, 9 Dec 2020 20:29:13 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma01wdc.us.ibm.com with ESMTP id 3581u9gdxs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 09 Dec 2020 20:29:13 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0B9KRunZ22610650
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 9 Dec 2020 20:27:56 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B1077B2064;
        Wed,  9 Dec 2020 20:27:56 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0D626B205F;
        Wed,  9 Dec 2020 20:27:54 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.37.122])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  9 Dec 2020 20:27:53 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC 0/4] vfio-pci/zdev: Fixing s390 vfio-pci ISM support
Date: Wed,  9 Dec 2020 15:27:46 -0500
Message-Id: <1607545670-1557-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-09_16:2020-12-09,2020-12-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 spamscore=0
 priorityscore=1501 phishscore=0 bulkscore=0 suspectscore=0 impostorscore=0
 adultscore=0 mlxscore=0 lowpriorityscore=0 mlxlogscore=860 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2012090137
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Today, ISM devices are completely disallowed for vfio-pci passthrough as
QEMU will reject the device due to an (inappropriate) MSI-X check.
However, in an effort to enable ISM device passthrough, I realized that the
manner in which ISM performs block write operations is highly incompatible
with the way that QEMU s390 PCI instruction interception and
vfio_pci_bar_rw break up I/O operations into 8B and 4B operations -- ISM
devices have particular requirements in regards to the alignment, size and
order of writes performed.  Furthermore, they require that legacy/non-MIO
s390 PCI instructions are used, which is also not guaranteed when the I/O
is passed through the typical userspace channels.

As a result, this patchset proposes a new VFIO region to allow a guest to
pass certain PCI instruction intercepts directly to the s390 host kernel
PCI layer for exeuction, pinning the guest buffer in memory briefly in
order to execute the requested PCI instruction.

Matthew Rosato (4):
  s390/pci: track alignment/length strictness for zpci_dev
  vfio-pci/zdev: Pass the relaxed alignment flag
  s390/pci: Get hardware-reported max store block length
  vfio-pci/zdev: Introduce the zPCI I/O vfio region

 arch/s390/include/asm/pci.h         |   4 +-
 arch/s390/include/asm/pci_clp.h     |   7 +-
 arch/s390/pci/pci_clp.c             |   2 +
 drivers/vfio/pci/vfio_pci.c         |   8 ++
 drivers/vfio/pci/vfio_pci_private.h |   6 ++
 drivers/vfio/pci/vfio_pci_zdev.c    | 160 ++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |   4 +
 include/uapi/linux/vfio_zdev.h      |  33 ++++++++
 8 files changed, 221 insertions(+), 3 deletions(-)
```
#### [Patch v3 0/2] cgroup: KVM: New Encryption IDs cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Wed Dec  9 20:54:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11962553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F90FC433FE
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:55:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D3F523BAC
	for <kvm@archiver.kernel.org>; Wed,  9 Dec 2020 20:55:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732302AbgLIUzG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 9 Dec 2020 15:55:06 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39646 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729345AbgLIUzF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Dec 2020 15:55:05 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8959BC061793
        for <kvm@vger.kernel.org>; Wed,  9 Dec 2020 12:54:25 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id v9so2231318qtw.12
        for <kvm@vger.kernel.org>; Wed, 09 Dec 2020 12:54:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=eyAf9tPh5kwa3NPR7RusvbbsQzwJzLjle+w/qgwIjD0=;
        b=Xh+cDnP4DoT5owh0/0HIm4Z8CAhhPYD263reDQNel9C7pyR9gOBxcvWO1X4IndEzBo
         7qit/pbm/xw+nUhXMQHMHo4ZOSnJURBK6g4JlEQGbr9TaCusAVM7X9Vfa0z/dW5DpIBI
         rqMBWuvl00va7X5MtLz55B492M6+6mfoJ9Uk2Fi+pHbJskFwKGDDup9dcxmjXNO/LKVA
         Rh03vIm2GpQtTy9xl6oJJ2JuYoFUe1sdme9kePmiHMD8hAAxZqjYYZUw2qS4/eUfb3Wv
         pulYP0O+TmrLVyxcMzc6hGb24eBry7Icr/iCipBtYKBepUWMk7/TWkK7kFIar6lVMn3x
         zrEA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=eyAf9tPh5kwa3NPR7RusvbbsQzwJzLjle+w/qgwIjD0=;
        b=nxdBhON/egjZCfiQiShnXKOT047lXkG/n2EVnmHRXfM70MyCmQ8dWhY6CVZNyzayAZ
         xLGgeOPI0htmdaCFoYVIzyQ3IrgBnvuWBCpHv/xhtT65vpFOwUOOFAgSGaNKD+laDFPj
         rQOz2vIGHXyluoHSTIo9fOvzjAxep8KOeJ4tCBaMox/jSnqTyKNFgksu3VoJLqA+LObF
         7VkE0Xs8ZejkZ7fDXZFgDAF8+5zcMyE6XYlnnPMq3vESr8YhoeeEWJXH8OfP+rTifGBB
         4dC7uHUtRer/Rx9jg1r+hsPLqiBLns3FAj+n12sb0B9yPPs6jLAmfiqPa/O1MJ1MlH/g
         t4Zw==
X-Gm-Message-State: AOAM532B9KoR+E5PNSY5ttNZGxvJHPGKYKuxIxb0zkbBCxPrWRtfW78z
        iDajWjfFfJWv8IfqOAZfsi1ZRUHgipb8
X-Google-Smtp-Source: 
 ABdhPJyHiL9v7qyrY0Ac/3Fc8Zm/BX/g/QvBraZOuqkew4GB+ozMmGKuR5pYDHMyzGr7COsym2qO6fKRCDvy
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a0c:f74a:: with SMTP id
 e10mr731582qvo.47.1607547264628; Wed, 09 Dec 2020 12:54:24 -0800 (PST)
Date: Wed,  9 Dec 2020 12:54:11 -0800
Message-Id: <20201209205413.3391139-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [Patch v3 0/2] cgroup: KVM: New Encryption IDs cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch adds a new cgroup controller, Encryption IDs, to track and
limit the usage of encryption IDs on a host.

AMD provides Secure Encrypted Virtualization (SEV) and SEV with
Encrypted State (SEV-ES) to encrypt the guest OS's memory using limited
number of Address Space Identifiers (ASIDs).

This limited number of ASIDs creates issues like SEV ASID starvation and
unoptimized scheduling in the cloud infrastucture.

In the RFC patch v1, I provided only SEV cgroup controller but based
on the feedback and discussion it became clear that this cgroup
controller can be extended to be used by Intel's Trusted Domain
Extension (TDX) and s390's protected virtualization Secure Execution IDs
(SEID)

This patch series provides a generic Encryption IDs controller with
tracking support of the SEV ASIDs.

Changes in v3:
- Fixes a build error when CONFIG_CGROUP is disabled.

Changes in v2:
- Changed cgroup name from sev to encryption_ids.
- Replaced SEV specific names in APIs and documentations with generic
  encryption IDs.
- Providing 3 cgroup files per encryption ID type. For example in SEV,
  - encryption_ids.sev.stat (only in the root cgroup directory).
  - encryption_ids.sev.max
  - encryption_ids.sev.current

Thanks
Vipin Sharma

[1] https://lore.kernel.org/lkml/20200922004024.3699923-1-vipinsh@google.com/#r
[2] https://lore.kernel.org/lkml/20201208213531.2626955-1-vipinsh@google.com/

 .../admin-guide/cgroup-v1/encryption_ids.rst  | 108 +++++
 Documentation/admin-guide/cgroup-v2.rst       |  78 +++-
 arch/x86/kvm/svm/sev.c                        |  28 +-
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/encryption_ids_cgroup.h         |  71 +++
 include/linux/kvm_host.h                      |   4 +
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/encryption_ids.c                | 430 ++++++++++++++++++
 9 files changed, 729 insertions(+), 9 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/encryption_ids.rst
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c
```
