

#### [PATCH 0/6] VFIO mdev aggregated resources handling
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
From patchwork Thu Oct 24 05:08:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11208279
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C74B139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:08:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 34F1B20679
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 05:08:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437451AbfJXFIe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 01:08:34 -0400
Received: from mga11.intel.com ([192.55.52.93]:7748 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725298AbfJXFIe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 01:08:34 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Oct 2019 22:08:33 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,223,1569308400";
   d="scan'208";a="197627623"
Received: from debian-nuc.sh.intel.com ([10.239.160.133])
  by fmsmga007.fm.intel.com with ESMTP; 23 Oct 2019 22:08:32 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: kvm@vger.kernel.org
Cc: alex.williamson@redhat.com, kwankhede@nvidia.com,
        kevin.tian@intel.com, cohuck@redhat.com
Subject: [PATCH 0/6] VFIO mdev aggregated resources handling
Date: Thu, 24 Oct 2019 13:08:23 +0800
Message-Id: <20191024050829.4517-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.24.0.rc0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is a refresh for previous send of this series. I got impression that
some SIOV drivers would still deploy their own create and config method so
stopped effort on this. But seems this would still be useful for some other
SIOV driver which may simply want capability to aggregate resources. So here's
refreshed series.

Current mdev device create interface depends on fixed mdev type, which get uuid
from user to create instance of mdev device. If user wants to use customized
number of resource for mdev device, then only can create new mdev type for that
which may not be flexible. This requirement comes not only from to be able to
allocate flexible resources for KVMGT, but also from Intel scalable IO
virtualization which would use vfio/mdev to be able to allocate arbitrary
resources on mdev instance. More info on [1] [2] [3].

To allow to create user defined resources for mdev, it trys to extend mdev
create interface by adding new "aggregate=xxx" parameter following UUID, for
target mdev type if aggregation is supported, it can create new mdev device
which contains resources combined by number of instances, e.g

    echo "<uuid>,aggregate=10" > create

VM manager e.g libvirt can check mdev type with "aggregation" attribute which
can support this setting. If no "aggregation" attribute found for mdev type,
previous behavior is still kept for one instance allocation. And new sysfs
attribute "aggregated_instances" is created for each mdev device to show allocated number.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

Zhenyu Wang (6):
  vfio/mdev: Add new "aggregate" parameter for mdev create
  vfio/mdev: Add "aggregation" attribute for supported mdev type
  vfio/mdev: Add "aggregated_instances" attribute for supported mdev
    device
  Documentation/driver-api/vfio-mediated-device.rst: Update for
    vfio/mdev aggregation support
  Documentation/ABI/testing/sysfs-bus-vfio-mdev: Update for vfio/mdev
    aggregation support
  drm/i915/gvt: Add new type with aggregation support

 Documentation/ABI/testing/sysfs-bus-vfio-mdev | 24 ++++++
 .../driver-api/vfio-mediated-device.rst       | 23 ++++++
 drivers/gpu/drm/i915/gvt/gvt.c                |  4 +-
 drivers/gpu/drm/i915/gvt/gvt.h                | 11 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 53 ++++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c               | 56 ++++++++++++-
 drivers/vfio/mdev/mdev_core.c                 | 36 ++++++++-
 drivers/vfio/mdev/mdev_private.h              |  6 +-
 drivers/vfio/mdev/mdev_sysfs.c                | 79 ++++++++++++++++++-
 include/linux/mdev.h                          | 19 +++++
 10 files changed, 294 insertions(+), 17 deletions(-)
```
#### [RFC PATCH v6 0/7] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Thu Oct 24 11:02:02 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11208955
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24B9214E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:02:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0CA7721929
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:02:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392847AbfJXLCj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 07:02:39 -0400
Received: from foss.arm.com ([217.140.110.172]:47392 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732328AbfJXLCj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 07:02:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5AE73497;
        Thu, 24 Oct 2019 04:02:23 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 757673F71A;
        Thu, 24 Oct 2019 04:02:18 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v6 0/7] Enable ptp_kvm for arm64
Date: Thu, 24 Oct 2019 19:02:02 +0800
Message-Id: <20191024110209.21328-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. This patch enable kvm ptp
for arm64.
This patch set base on [1][2][3]

change log:
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

[1]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=125ea89e4a21e2fc5235410f966a996a1a7148bf
[2]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=464f5a1741e5959c3e4d2be1966ae0093b4dce06
[3]https://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git/
commit/?h=kvm/hvc&id=6597490e005d0eeca8ed8c1c1d7b4318ee014681
[4]https://git.kernel.org/pub/scm/linux/kernel/git/arm64/linux.git/
commit/?h=for-next/smccc-conduit-cleanup&id=6b7fe77c334ae59fed9500140e08f4f896b36871

Jianyong Wu (6):
  psci: let arm_smccc_1_1_invoke available by modules
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  time: Add mechanism to recognize clocksource in time_get_snapshot
  psci: Add hvc call service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm64
  kvm: arm64: Add capability check extension for ptp_kvm

Mark Rutland (1):
  arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()

 drivers/clocksource/arm_arch_timer.c        | 24 ++++++
 drivers/firmware/psci/psci.c                | 16 ++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm_arm64.c                 | 53 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 77 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/asm-generic/ptp_kvm.h               | 12 +++
 include/clocksource/arm_arch_timer.h        |  4 +
 include/linux/arm-smccc.h                   | 30 ++++++-
 include/linux/clocksource.h                 |  6 ++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/psci.c                         | 22 ++++++
 17 files changed, 286 insertions(+), 66 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/asm-generic/ptp_kvm.h
```
#### [RFC 00/37] KVM: s390: Add support for protected VMs
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Oct 24 11:40:22 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11209085
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 18CA11515
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EBD0520679
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 11:41:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439089AbfJXLlw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 07:41:52 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:18914 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2436528AbfJXLlw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Oct 2019 07:41:52 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9OBbD4S174610
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:50 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vt294fejq-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 07:41:50 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 24 Oct 2019 12:41:48 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 24 Oct 2019 12:41:45 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9OBfifA46858288
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 24 Oct 2019 11:41:44 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DB5B75204F;
        Thu, 24 Oct 2019 11:41:43 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 5AAFE52054;
        Thu, 24 Oct 2019 11:41:42 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com,
        gor@linux.ibm.com, frankja@linux.ibm.com
Subject: [RFC 00/37] KVM: s390: Add support for protected VMs
Date: Thu, 24 Oct 2019 07:40:22 -0400
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19102411-0012-0000-0000-0000035CCA83
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102411-0013-0000-0000-00002197FCDF
Message-Id: <20191024114059.102802-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-24_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=418 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910240115
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

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

All patches are in the protvirt branch of the korg s390 kvm git.

Claudio will present the technology at his presentation at KVM Forum
2019.

Christian Borntraeger (1):
  KVM: s390: protvirt: Add SCLP handling

Claudio Imbrenda (2):
  KVM: s390: add missing include in gmap.h
  KVM: s390: protvirt: Implement on-demand pinning

Janosch Frank (27):
  DOCUMENTATION: protvirt: Protected virtual machine introduction
  KVM: s390: protvirt: Add initial lifecycle handling
  s390: KVM: Export PV handle to gmap
  s390: UV: Add import and export to UV library
  KVM: s390: protvirt: Secure memory is not mergeable
  DOCUMENTATION: protvirt: Interrupt injection
  KVM: s390: protvirt: Handle SE notification interceptions
  DOCUMENTATION: protvirt: Instruction emulation
  KVM: s390: protvirt: Handle spec exception loops
  KVM: s390: protvirt: Add new gprs location handling
  KVM: S390: protvirt: Introduce instruction data area bounce buffer
  KVM: S390: protvirt: Instruction emulation
  KVM: s390: protvirt: Make sure prefix is always protected
  KVM: s390: protvirt: Write sthyi data to instruction data area
  KVM: s390: protvirt: STSI handling
  KVM: s390: protvirt: Only sync fmt4 registers
  KVM: s390: protvirt: SIGP handling
  KVM: s390: protvirt: Add program exception injection
  KVM: s390: protvirt: Sync pv state
  DOCUMENTATION: protvirt: Diag 308 IPL
  KVM: s390: protvirt: Add diag 308 subcode 8 - 10 handling
  KVM: s390: protvirt: UV calls diag308 0, 1
  KVM: s390: Introduce VCPU reset IOCTL
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: Fix cpu reset local IRQ clearing
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Add UV debug trace

Michael Mueller (4):
  KVM: s390: protvirt: Add interruption injection controls
  KVM: s390: protvirt: Implement interruption injection
  KVM: s390: protvirt: Add machine-check interruption injection controls
  KVM: s390: protvirt: Implement machine-check interruption injection

Vasily Gorbik (3):
  s390/protvirt: introduce host side setup
  s390/protvirt: add ultravisor initialization
  s390: add (non)secure page access exceptions handlers

 .../admin-guide/kernel-parameters.txt         |   5 +
 Documentation/virtual/kvm/s390-pv-boot.txt    |  62 +++
 Documentation/virtual/kvm/s390-pv.txt         |  97 ++++
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  20 +-
 arch/s390/include/asm/gmap.h                  |   4 +
 arch/s390/include/asm/kvm_host.h              | 103 +++-
 arch/s390/include/asm/uv.h                    | 255 +++++++++-
 arch/s390/include/uapi/asm/kvm.h              |   5 +-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   7 +-
 arch/s390/kernel/uv.c                         | 121 +++++
 arch/s390/kvm/Kconfig                         |   9 +
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/diag.c                          |   7 +
 arch/s390/kvm/intercept.c                     |  91 +++-
 arch/s390/kvm/interrupt.c                     | 208 ++++++--
 arch/s390/kvm/kvm-s390.c                      | 476 +++++++++++++++---
 arch/s390/kvm/kvm-s390.h                      |  58 +++
 arch/s390/kvm/priv.c                          |   9 +-
 arch/s390/kvm/pv.c                            | 317 ++++++++++++
 arch/s390/mm/fault.c                          |  64 +++
 arch/s390/mm/gmap.c                           |  28 +-
 include/uapi/linux/kvm.h                      |  42 ++
 25 files changed, 1848 insertions(+), 149 deletions(-)
 create mode 100644 Documentation/virtual/kvm/s390-pv-boot.txt
 create mode 100644 Documentation/virtual/kvm/s390-pv.txt
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
#### [RFC v2 0/3] vfio: support Shared Virtual Addressing
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Thu Oct 24 12:26:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11209425
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E727139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 12:52:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0785920856
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 12:52:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502181AbfJXMwv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 08:52:51 -0400
Received: from mga02.intel.com ([134.134.136.20]:11532 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731315AbfJXMwv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 08:52:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Oct 2019 05:52:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,224,1569308400";
   d="scan'208";a="201464798"
Received: from iov.bj.intel.com ([10.238.145.67])
  by orsmga003.jf.intel.com with ESMTP; 24 Oct 2019 05:52:47 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [RFC v2 0/3] vfio: support Shared Virtual Addressing
Date: Thu, 24 Oct 2019 08:26:20 -0400
Message-Id: <1571919983-3231-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared virtual address (SVA), a.k.a, Shared virtual memory (SVM) on Intel
platforms allow address space sharing between device DMA and applications.
SVA can reduce programming complexity and enhance security.
This series is intended to expose SVA capability to VMs. i.e. shared guest
application address space with passthru devices. The whole SVA virtualization
requires QEMU/VFIO/IOMMU changes. This series includes the VFIO changes, for
QEMU and IOMMU changes, they are in separate series (listed in the "Related
series").

The high-level architecture for SVA virtualization is as below:

    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

There are roughly three parts in this patchset which are
corresponding to the basic vSVA support for PCI device
assignment
 1. vfio support for PASID allocation and free from VMs
 2. vfio support for guest PASID binding from VMs
 3. vfio support for IOMMU cache invalidation from VMs

The complete vSVA upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. Page Request Services (PRS) support
    3. Mediated device assignment

This RFC patchset is aiming for the phase 1, and works together with the
VT-d driver[1] changes and QEMU changes[2]. Complete set for vSVA can be
found in:
https://github.com/jacobpan/linux.git:siov_sva.

And this patchset doesn't include the patch to expose PASID capability to
guest. This is expected to be in another series.

Related series:
[1] [PATCH v6 00/10] Nested Shared Virtual Address (SVA) VT-d support:
https://lkml.org/lkml/2019/10/22/953
<This series is based on this kernel series from Jacob Pan>

[2] [RFC v2 00/20] intel_iommu: expose Shared Virtual Addressing to VM
from Yi Liu

Changelog:
	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.
	  RFC v1: https://patchwork.kernel.org/cover/11033699/

Liu Yi L (3):
  vfio: VFIO_IOMMU_CACHE_INVALIDATE
  vfio/type1: VFIO_IOMMU_PASID_REQUEST(alloc/free)
  vfio/type1: bind guest pasid (guest page tables) to host

 drivers/vfio/vfio_iommu_type1.c | 305 ++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       |  82 +++++++++++
 2 files changed, 387 insertions(+)
```
#### [RFC v2 00/22] intel_iommu: expose Shared Virtual Addressing to VM
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Thu Oct 24 12:34:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11209461
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3DE0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:01:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C21462166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 13:01:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502250AbfJXNBK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 09:01:10 -0400
Received: from mga04.intel.com ([192.55.52.120]:5155 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726484AbfJXNBK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 09:01:10 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Oct 2019 06:01:09 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,224,1569308400";
   d="scan'208";a="210156134"
Received: from iov.bj.intel.com ([10.238.145.67])
  by fmsmga001.fm.intel.com with ESMTP; 24 Oct 2019 06:01:06 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, mst@redhat.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, peterx@redhat.com
Cc: eric.auger@redhat.com, david@gibson.dropbear.id.au,
        tianyu.lan@intel.com, kevin.tian@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jacob.jun.pan@linux.intel.com, kvm@vger.kernel.org
Subject: [RFC v2 00/22] intel_iommu: expose Shared Virtual Addressing to VM
Date: Thu, 24 Oct 2019 08:34:21 -0400
Message-Id: <1571920483-3382-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared virtual address (SVA), a.k.a, Shared virtual memory (SVM) on Intel
platforms allow address space sharing between device DMA and applications.
SVA can reduce programming complexity and enhance security.
This series is intended to expose SVA capability to VMs. i.e. shared guest
application address space with passthru devices. The whole SVA virtualization
requires QEMU/VFIO/IOMMU changes. This series includes the QEMU changes, for
VFIO and IOMMU changes, they are in separate series (listed in the "Related
series").

The high-level architecture for SVA virtualization is as below:

    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

The complete vSVA upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. Page Request Services (PRS) support
    3. Mediated device assignment

This RFC patchset is aiming for the phase 1. Works together with the VT-d
driver[1] changes and VFIO changes[2].

Related series:
[1] [PATCH v6 00/10] Nested Shared Virtual Address (SVA) VT-d support:
https://lkml.org/lkml/2019/10/22/953
<This series is based on this kernel series from Jacob Pan>

[2] [RFC v2 0/3] vfio: support Shared Virtual Addressing from Yi Liu

There are roughly four parts:
 1. Introduce IOMMUContext as abstract layer between vIOMMU emulator and
    VFIO to avoid direct calling between the two
 2. Passdown PASID allocation and free to host
 3. Passdown guest PASID binding to host
 4. Passdown guest IOMMU cache invalidation to host

The full set can be found in below link:
https://github.com/luxis1999/qemu.git: sva_vtd_v6_qemu_rfc_v2

Changelog:
	- RFC v1 -> v2:
	  Introduce IOMMUContext to abstract the connection between VFIO
	  and vIOMMU emulator, which is a replacement of the PCIPASIDOps
	  in RFC v1. Modify x-scalable-mode to be string option instead of
	  adding a new option as RFC v1 did. Refined the pasid cache management
	  and addressed the TODOs mentioned in RFC v1. 
	  RFC v1: https://patchwork.kernel.org/cover/11033657/

Eric Auger (1):
  update-linux-headers: Import iommu.h

Liu Yi L (20):
  header update VFIO/IOMMU vSVA APIs against 5.4.0-rc3+
  intel_iommu: modify x-scalable-mode to be string option
  vfio/common: add iommu_ctx_notifier in container
  hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
  hw/pci: introduce pci_device_iommu_context()
  intel_iommu: provide get_iommu_context() callback
  vfio/pci: add iommu_context notifier for pasid alloc/free
  intel_iommu: add virtual command capability support
  intel_iommu: process pasid cache invalidation
  intel_iommu: add present bit check for pasid table entries
  intel_iommu: add PASID cache management infrastructure
  vfio/pci: add iommu_context notifier for pasid bind/unbind
  intel_iommu: bind/unbind guest page table to host
  intel_iommu: replay guest pasid bindings to host
  intel_iommu: replay pasid binds after context cache invalidation
  intel_iommu: do not passdown pasid bind for PASID #0
  vfio/pci: add iommu_context notifier for PASID-based iotlb flush
  intel_iommu: process PASID-based iotlb invalidation
  intel_iommu: propagate PASID-based iotlb invalidation to host
  intel_iommu: process PASID-based Device-TLB invalidation

Peter Xu (1):
  hw/iommu: introduce IOMMUContext

 hw/Makefile.objs                |    1 +
 hw/alpha/typhoon.c              |    6 +-
 hw/arm/smmu-common.c            |    6 +-
 hw/hppa/dino.c                  |    6 +-
 hw/i386/amd_iommu.c             |    6 +-
 hw/i386/intel_iommu.c           | 1249 +++++++++++++++++++++++++++++++++++++--
 hw/i386/intel_iommu_internal.h  |  109 ++++
 hw/i386/trace-events            |    6 +
 hw/iommu/Makefile.objs          |    1 +
 hw/iommu/iommu.c                |   66 +++
 hw/pci-host/designware.c        |    6 +-
 hw/pci-host/ppce500.c           |    6 +-
 hw/pci-host/prep.c              |    6 +-
 hw/pci-host/sabre.c             |    6 +-
 hw/pci/pci.c                    |   27 +-
 hw/ppc/ppc440_pcix.c            |    6 +-
 hw/ppc/spapr_pci.c              |    6 +-
 hw/s390x/s390-pci-bus.c         |    8 +-
 hw/vfio/common.c                |   10 +
 hw/vfio/pci.c                   |  149 +++++
 include/hw/i386/intel_iommu.h   |   58 +-
 include/hw/iommu/iommu.h        |  113 ++++
 include/hw/pci/pci.h            |   13 +-
 include/hw/pci/pci_bus.h        |    2 +-
 include/hw/vfio/vfio-common.h   |    9 +
 linux-headers/linux/iommu.h     |  324 ++++++++++
 linux-headers/linux/vfio.h      |   83 +++
 scripts/update-linux-headers.sh |    2 +-
 28 files changed, 2232 insertions(+), 58 deletions(-)
 create mode 100644 hw/iommu/Makefile.objs
 create mode 100644 hw/iommu/iommu.c
 create mode 100644 include/hw/iommu/iommu.h
 create mode 100644 linux-headers/linux/iommu.h
```
#### [PATCH v3 0/3] kvm: call kvm_arch_destroy_vm if vm creation fails
##### From: Jim Mattson <jmattson@google.com>

```c
From patchwork Thu Oct 24 23:03:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11211051
Return-Path: <SRS0=LVJf=YR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 262061864
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 23:03:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED0EB2166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Oct 2019 23:03:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="iJ4AdUvw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732359AbfJXXDm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 19:03:42 -0400
Received: from mail-yb1-f202.google.com ([209.85.219.202]:32879 "EHLO
        mail-yb1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726175AbfJXXDm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 19:03:42 -0400
Received: by mail-yb1-f202.google.com with SMTP id p66so493877yba.0
        for <kvm@vger.kernel.org>; Thu, 24 Oct 2019 16:03:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=H5UH2UlO9XnU36X6S3z2ls74WXsy5ReVfipmx8i1xro=;
        b=iJ4AdUvwZcNjsp9MNh2e7CXdFwOQ3xnzFfUbrgHTzM1AFJNXvPVamVtjbsgKZkMToV
         m2y5uIiCxxL+ZjGgH47GddWoGsx8XFqjNSLTLXX5fZ54c8+3aH9SfF6Vac8EwZ9LlWca
         ps1F1EVyZmLto8ZvObns7FeRPqssZ/LHwkAXa3tnKzNCsIS81ntY3VYOhkTvnddz44OJ
         cU1Mwn0N4MTm5J9U3x766uCEeOLfNE8BQ/FoeouIB2ueM3mcbDhNaoJ+dvXC7NvjS4qY
         iBF8XoP4XH1Xo/7CKD7XY1oXHOPlwmvqU/mqoLJYeB3Gq5+NT9NEtT/SIAsIbp6zuFNT
         +Vxw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=H5UH2UlO9XnU36X6S3z2ls74WXsy5ReVfipmx8i1xro=;
        b=BiNPFIEZ0vU12jK+/RDXH2drNh0UztkclVb2WiBSwwoHP7I3q2vbLckjwIN4h3EHqk
         /FuaQZA2fs7TA4yUbOiB5CUDu7Lz2UB9lZ3AsLsLNCMPL54wb2pca8gbxwyuDGXwXy2+
         xEZHTtEEh0vYc0VH+0glfePkwVrDLGVcuXCA28wOtTDROIa0ea7Nw0LiTjmzJg0OOazB
         BkOFDbGpnjerMDBTbIhOcRZHPBlM+ExWMrZo5TZQ1h4KsoiPJLGopC55ONLkxUZmBq0X
         1AdI+ULiczP45XmVsLS2NtuKbUGvDbODnCLInDVenPabPbjyODgWKPEPRurKqUKv0S8R
         WIAw==
X-Gm-Message-State: APjAAAV1lWanAxeMZM7eEReQfNKlfnkj2oVCYaAo+u6RZaZad+g5zZAL
        qL958MRd9WiahuG4OshrNstqFBP8EXAhfFNRsaw6YjA+PNMgxy0QP86hdMGR8KCjjl52tTquiam
        JJHF9eHjekzOWTdNK9faL/+s7VCw0RygRJVEbYsr1LANAoTSwg8UQnAa2+QviNgI=
X-Google-Smtp-Source: 
 APXvYqzkCyaGyRBtWf4UllraGDO7vSa/gmvBuHJarvPTSxVfu9/GCCzxD6q1D1UBeBeCzEEsUiMpvY8OzJPmew==
X-Received: by 2002:a81:af49:: with SMTP id x9mr7450557ywj.421.1571958221359;
 Thu, 24 Oct 2019 16:03:41 -0700 (PDT)
Date: Thu, 24 Oct 2019 16:03:24 -0700
Message-Id: <20191024230327.140935-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v3 0/3] kvm: call kvm_arch_destroy_vm if vm creation fails
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        John Sperbeck <jsperbeck@google.com>,
        Junaid Shahid <junaids@google.com>
Cc: Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Beginning with commit 44a95dae1d229a ("KVM: x86: Detect and Initialize
AVIC support"), AMD's version of kvm_arch_init_vm() will allocate
memory if the module parameter, avic, is enabled. (Note that this
module parameter is disabled by default.) However, there are many
possible failure exits from kvm_create_vm() *after* the call to
kvm_arch_init_vm(), and the memory allocated by kvm_arch_init_vm() was
leaked on these failure paths.

The obvious solution is to call kvm_arch_destroy_vm() on these failure
paths, since it will free the memory allocated by
kvm_arch_init_vm(). However, kvm_arch_destroy_vm() may reference
memslots and buses that were allocated later in kvm_create_vm(). So,
before we can call kvm_arch_destroy_vm() on the failure paths out of
kvm_create_vm(), we need to hoist the memslot and bus allocation up
before the call to kvm_arch_init_vm().

The call to clear the reference count on (some) failure paths out of
kvm_create_vm() just added to the potential confusion. By sinking the
call to set the reference count below any possible failure exits, we
can eliminate the call to clear the reference count on the failure
paths.

v1 -> v2: Call kvm_arch_destroy_vm before refcount_set
v2 -> v3: Added two preparatory changes

Jim Mattson (2):
  kvm: Don't clear reference count on kvm_create_vm() error path
  kvm: Allocate memslots and buses before calling kvm_arch_init_vm

John Sperbeck (1):
  kvm: call kvm_arch_destroy_vm if vm creation fails

 virt/kvm/kvm_main.c | 52 ++++++++++++++++++++++++++-------------------
 1 file changed, 30 insertions(+), 22 deletions(-)
```
