

#### [RFC PATCH v2 0/9] Introduce vendor ops in vfio-pci
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Fri Jan 31 02:08:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11359005
Return-Path: <SRS0=N1aq=3U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7F4792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 02:18:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A542C206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 02:18:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727820AbgAaCSG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 21:18:06 -0500
Received: from mga02.intel.com ([134.134.136.20]:45714 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727741AbgAaCSG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 21:18:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Jan 2020 18:18:05 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,384,1574150400";
   d="scan'208";a="222995947"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga008.jf.intel.com with ESMTP; 30 Jan 2020 18:18:03 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        cohuck@redhat.com, zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH v2 0/9] Introduce vendor ops in vfio-pci
Date: Thu, 30 Jan 2020 21:08:03 -0500
Message-Id: <20200131020803.27519-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using module vfio-pci to pass through devices, though for the most
of time, it is desired to use default implementations in vfio-pci, vendors
sometimes may want to do certain kind of customization.
For example, vendors may want to add a vendor device region or may want to
intercept writes to a BAR region.
So, in this patch set, we introduce a way to allow vendors to focus on
handling of regions of their interest and call default vfio-pci ops to
handle the reset ones.

It goes like this:
(1) macros are provided to let vendor drivers register/unregister
vfio_pci_vendor_driver_ops to vfio_pci in their module_init() and
module_exit().
vfio_pci_vendor_driver_ops contains callbacks probe() and remove() and a
pointer to vfio_device_ops.

(2) vendor drivers define their module aliases as
"vfio-pci:$vendor_id-$device_id".
E.g. A vendor module for VF devices of Intel(R) Ethernet Controller XL710
family can define its module alias as MODULE_ALIAS("vfio-pci:8086-154c").

(3) when module vfio_pci is bound to a device, it would call modprobe in
user space for modules of alias "vfio-pci:$vendor_id-$device_id", which
would trigger unloaded vendor drivers to register their
vfio_pci_vendor_driver_ops to vfio_pci.
Then it searches registered ops list and calls probe() to test whether this
vendor driver supports this physical device.
A success probe() would make vfio_pci to use vfio_device_ops provided
vendor driver as the ops of the vfio device. So vfio_pci_ops are not to be
called for this device any more. Instead, they are exported to be called
from vendor drivers as a default implementation.


                                        _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
                                  
 __________   (un)register vendor ops  |  ___________    ___________   |
|          |<----------------------------|    VF    |   |           |   
| vfio-pci |                           | |  vendor  |   | PF driver |  |
|__________|---------------------------->|  driver  |   |___________|   
     |           probe/remove()        |  -----------          |       |
     |                                                         |         
     |                                 |_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _|
    \|/                                                       \|/
-----------                                              ------------
|    VF   |                                              |    PF    |
-----------                                              ------------
                   a typical usage in SRIOV



Ref counts:
(1) vendor drivers must be a module and compiled to depend on module
vfio_pci.
(2) In vfio_pci, a successful register would add refs of itself, and a
successful unregister would derefs of itself.
(3) In vfio_pci, a successful probe() of a vendor driver would add ref of
the vendor module. It derefs of the vendor module after calling remove().
(4) macro provided to make sure vendor module always unregister itself in
its module_exit

Those are to prevent below conditions:
a. vfio_pci is unloaded after a successful register from vendor driver.
   Though vfio_pci would later call modprobe to ask the vendor module to
   register again, it cannot help if vendor driver remain as loaded
   across unloading-loading of vfio_pci.
b. vendor driver unregisters itself after successfully probed by vfio_pci.
c. circular dependency between vfio_pci and the vendor driver.
   if vfio_pci adds refs to both vfio_pci and vendor driver on a successful
   register and if vendor driver only do the unregister in its module_exit,
   then it would have no chance to do the unregister.


Patch Overview
patches 1-2 makes vfio_pci inheritable by vendor modules
            by making part of struct vfio_pci_device public and functions
            in struct vfio_pci_ops exported
patches 3-4 provide register/unregister interfaces for vendor drivers
patches 5-6 some more enhancements
patch 7 provides an sample to pass through IGD devices
patches 8-9 implement VF live migration on Intel's 710 SRIOV devices.
            Some dirty page tracking functions are intentionally
            commented out and would send out later in future.

Changelog:
RFC v1- RFC v2:
- renamed mediate ops to vendor ops
- use of request_module and module alias to manage vendor driver load
  (Alex)
- changed from vfio_pci_ops calling vendor ops
  to vendor ops calling default vfio_pci_ops  (Alex)
- dropped patches for dynamic traps of BARs. will submit them later.

Links:
Previous version (RFC v1):
kernel part: https://www.spinics.net/lists/kernel/msg3337337.html.
qemu part: https://www.spinics.net/lists/kernel/msg3337337.html.

VFIO live migration v8:
https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05542.html.


Yan Zhao (9):
  vfio/pci: split vfio_pci_device into public and private parts
  vfio/pci: export functions in vfio_pci_ops
  vfio/pci: register/unregister vfio_pci_vendor_driver_ops
  vfio/pci: macros to generate module_init and module_exit for vendor
    modules
  vfio/pci: let vfio_pci know how many vendor regions are registered
  vfio/pci: export vfio_pci_setup_barmap
  samples/vfio-pci: add a sample vendor module of vfio-pci for IGD
    devices
  vfio: header for vfio live migration region.
  i40e/vf_migration: vfio-pci vendor driver for VF live migration

 drivers/net/ethernet/intel/Kconfig            |  10 +
 drivers/net/ethernet/intel/i40e/Makefile      |   2 +
 drivers/net/ethernet/intel/i40e/i40e.h        |   2 +
 .../ethernet/intel/i40e/i40e_vf_migration.c   | 590 ++++++++++++++++++
 .../ethernet/intel/i40e/i40e_vf_migration.h   |  92 +++
 drivers/vfio/pci/vfio_pci.c                   | 337 ++++++----
 drivers/vfio/pci/vfio_pci_config.c            | 157 ++---
 drivers/vfio/pci/vfio_pci_igd.c               |  16 +-
 drivers/vfio/pci/vfio_pci_intrs.c             | 171 ++---
 drivers/vfio/pci/vfio_pci_nvlink2.c           |  16 +-
 drivers/vfio/pci/vfio_pci_private.h           |  11 +-
 drivers/vfio/pci/vfio_pci_rdwr.c              |  60 +-
 include/linux/vfio.h                          |  61 ++
 include/uapi/linux/vfio.h                     | 149 +++++
 samples/Kconfig                               |   6 +
 samples/Makefile                              |   1 +
 samples/vfio-pci/Makefile                     |   2 +
 samples/vfio-pci/igd_pt.c                     | 153 +++++
 18 files changed, 1518 insertions(+), 318 deletions(-)
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.c
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.h
 create mode 100644 samples/vfio-pci/Makefile
 create mode 100644 samples/vfio-pci/igd_pt.c
```
#### [PATCH v10 0/6] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Jan 31 10:01:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11359527
Return-Path: <SRS0=N1aq=3U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7086813A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 10:02:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5802220CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 10:02:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728352AbgAaKCU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jan 2020 05:02:20 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:10038 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728160AbgAaKCT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 31 Jan 2020 05:02:19 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00V9vehj046984
        for <kvm@vger.kernel.org>; Fri, 31 Jan 2020 05:02:18 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xvfy8vnfp-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 31 Jan 2020 05:02:17 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 31 Jan 2020 10:02:15 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 31 Jan 2020 10:02:12 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00VA1JrI46465344
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 31 Jan 2020 10:01:19 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7262F11C04A;
        Fri, 31 Jan 2020 10:02:11 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C63E011C052;
        Fri, 31 Jan 2020 10:02:09 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.11.63])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 31 Jan 2020 10:02:09 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v10 0/6] KVM: s390: Add new reset vcpu API
Date: Fri, 31 Jan 2020 05:01:59 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20013110-0016-0000-0000-000002E2799C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20013110-0017-0000-0000-00003345486D
Message-Id: <20200131100205.74720-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-31_02:2020-01-30,2020-01-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 mlxscore=0 mlxlogscore=689 priorityscore=1501 phishscore=0 spamscore=0
 lowpriorityscore=0 suspectscore=1 clxscore=1015 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001310088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's implement the remaining resets, namely the normal and clear
reset to improve architectural compliance.

While we're at it, let's also start testing the new API.
Those tests are not yet complete, but will be extended in the future.

v10:
	* Cleared up the test patch and added strerror information
	* Removed capability checks from irq test
	* Fixed clobber patch

Christian Borntraeger (1):
  KVM: s390: do not clobber registers during guest reset/store status

Janosch Frank (4):
  KVM: s390: Cleanup initial cpu reset
  KVM: s390: Add new reset vcpu API
  selftests: KVM: Add fpu and one reg set/get library functions
  selftests: KVM: s390x: Add reset tests

Pierre Morel (1):
  selftests: KVM: testing the local IRQs resets

 Documentation/virt/kvm/api.txt                |  43 ++++
 arch/s390/include/asm/kvm_host.h              |   5 +
 arch/s390/kvm/kvm-s390.c                      |  92 +++++---
 include/uapi/linux/kvm.h                      |   5 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  36 ++++
 tools/testing/selftests/kvm/s390x/resets.c    | 197 ++++++++++++++++++
 8 files changed, 351 insertions(+), 34 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/s390x/resets.c
```
#### [kvm-unit-tests PATCH v4 00/10] arm/arm64: Various fixes
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Fri Jan 31 16:37:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11360249
Return-Path: <SRS0=N1aq=3U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 974EA924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 16:38:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7F08D206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jan 2020 16:38:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726347AbgAaQiI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jan 2020 11:38:08 -0500
Received: from foss.arm.com ([217.140.110.172]:37306 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726139AbgAaQiI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jan 2020 11:38:08 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C036FFEC;
        Fri, 31 Jan 2020 08:38:07 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 BCDE33F68E;
        Fri, 31 Jan 2020 08:38:06 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, maz@kernel.org,
        andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH v4 00/10] arm/arm64: Various fixes
Date: Fri, 31 Jan 2020 16:37:18 +0000
Message-Id: <20200131163728.5228-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These are the patches that were left unmerged from the previous version of
the series, plus a few new patches. Patch #1 "Makefile: Use
no-stack-protector compiler options" is straightforward and came about
because of a compile error I experienced on RockPro64.

Patches #3 and #5 are the result of Andre's comments on the previous
version. When adding ISBs after register writes I noticed in the ARM ARM
that a read of the timer counter value can be reordered, and patch #4
tries to avoid that.

Patch #7 is also the result of a review comment. For the GIC tests, we wait
up to 5 seconds for the interrupt to be asserted. However, the GIC tests
can use more than one CPU, which is not the case with the timer test. And
waiting for the GIC to assert the interrupt can happen up to 6 times (8
times after patch #9), so I figured that a timeout of 10 seconds for the
test is acceptable.

Patch #8 tries to improve the way we test how the timer generates the
interrupt. If the GIC asserts the timer interrupt, but the device itself is
not generating it, that's a pretty big problem.

Ran the same tests as before:

- with kvmtool, on an arm64 host kernel: 64 and 32 bit tests, with GICv3
  (on an Ampere eMAG) and GICv2 (on a AMD Seattle box).

- with qemu, on an arm64 host kernel:
    a. with accel=kvm, 64 and 32 bit tests, with GICv3 (Ampere eMAG) and
       GICv2 (Seattle).
    b. with accel=tcg, 64 and 32 bit tests, on the Ampere eMAG machine.

Changes:
* Patches #1, #3, #4, #5, #7, #8 are new.
* For patch #2, as per Drew's suggestion, I changed the entry point to halt
  because the test is supposed to test if CPU_ON is successful.
* Removed the ISB from patch #6 because that was fixed by #3.
* Moved the architecture dependent function init_dcache_line_size to
  cpu_init in lib/arm/setup.c as per Drew's suggestion.

Alexandru Elisei (10):
  Makefile: Use no-stack-protector compiler options
  arm/arm64: psci: Don't run C code without stack or vectors
  arm64: timer: Add ISB after register writes
  arm64: timer: Add ISB before reading the counter value
  arm64: timer: Make irq_received volatile
  arm64: timer: EOIR the interrupt after masking the timer
  arm64: timer: Wait for the GIC to sample timer interrupt state
  arm64: timer: Check the timer interrupt state
  arm64: timer: Test behavior when timer disabled or masked
  arm/arm64: Perform dcache clean + invalidate after turning MMU off

 Makefile                  |  4 +-
 lib/arm/asm/processor.h   | 13 +++++++
 lib/arm64/asm/processor.h | 12 ++++++
 lib/arm/setup.c           |  8 ++++
 arm/cstart.S              | 22 +++++++++++
 arm/cstart64.S            | 23 ++++++++++++
 arm/psci.c                | 15 ++++++--
 arm/timer.c               | 79 ++++++++++++++++++++++++++++++++-------
 arm/unittests.cfg         |  2 +-
 9 files changed, 158 insertions(+), 20 deletions(-)
```
