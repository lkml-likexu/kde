

#### [PATCH 0/7] powerpc/watchpoint: 2nd DAWR kvm enablement + selftests
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Thu Jul 23 10:20:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11680569
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1EF06C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:23:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2A90206C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:23:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728159AbgGWKWd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 06:22:33 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:27660 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726786AbgGWKWd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jul 2020 06:22:33 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06NA4QJx176342;
        Thu, 23 Jul 2020 06:22:09 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vstqg1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:22:09 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06NA6li0187675;
        Thu, 23 Jul 2020 06:22:08 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vstqfc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:22:08 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAGqFh022080;
        Thu, 23 Jul 2020 10:22:06 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma05fra.de.ibm.com with ESMTP id 32brq83924-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 10:22:06 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06NAM2Au29622582
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jul 2020 10:22:02 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0965EA405B;
        Thu, 23 Jul 2020 10:22:02 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DBE42A405F;
        Thu, 23 Jul 2020 10:21:58 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.160])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jul 2020 10:21:58 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        pbonzini@redhat.com, christophe.leroy@c-s.fr, jniethe5@gmail.com,
        pedromfc@br.ibm.com, rogealve@br.ibm.com, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 0/7] powerpc/watchpoint: 2nd DAWR kvm enablement + selftests
Date: Thu, 23 Jul 2020 15:50:51 +0530
Message-Id: <20200723102058.312282-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-23_03:2020-07-22,2020-07-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 malwarescore=0 mlxlogscore=999 phishscore=0 spamscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 suspectscore=0 clxscore=1011
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007230072
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch #1, #2 and #3 enables p10 2nd DAWR feature for Book3S kvm guest. DAWR
is a hypervisor resource and thus H_SET_MODE hcall is used to set/unset it.
A new case H_SET_MODE_RESOURCE_SET_DAWR1 is introduced in H_SET_MODE hcall
for setting/unsetting 2nd DAWR. Also, new capability KVM_CAP_PPC_DAWR1 has
been added to query 2nd DAWR support via kvm ioctl.

This feature also needs to be enabled in Qemu to really use it. I'll reply
link to qemu patches once I post them in qemu-devel mailing list.

Patch #4, #5, #6 and #7 adds selftests to test 2nd DAWR.

Dependency:
  1: p10 kvm base enablement
     https://lore.kernel.org/linuxppc-dev/20200602055325.6102-1-alistair@popple.id.au

  2: 2nd DAWR powervm/baremetal enablement
     https://lore.kernel.org/linuxppc-dev/20200723090813.303838-1-ravi.bangoria@linux.ibm.com

  3: ptrace PPC_DEBUG_FEATURE_DATA_BP_DAWR_ARCH_31 flag
     https://lore.kernel.org/linuxppc-dev/20200723093330.306341-1-ravi.bangoria@linux.ibm.com

Patches in this series applies fine on top of powerpc/next (9a77c4a0a125)
plus above dependency patches.

Ravi Bangoria (7):
  powerpc/watchpoint/kvm: Rename current DAWR macros and variables
  powerpc/watchpoint/kvm: Add infrastructure to support 2nd DAWR
  powerpc/watchpoint/kvm: Introduce new capability for 2nd DAWR
  powerpc/selftests/ptrace-hwbreak: Add testcases for 2nd DAWR
  powerpc/selftests/perf-hwbreak: Coalesce event creation code
  powerpc/selftests/perf-hwbreak: Add testcases for 2nd DAWR
  powerpc/selftests: Add selftest to test concurrent perf/ptrace events

 Documentation/virt/kvm/api.rst                |   6 +-
 arch/powerpc/include/asm/hvcall.h             |   2 +
 arch/powerpc/include/asm/kvm_host.h           |   6 +-
 arch/powerpc/include/uapi/asm/kvm.h           |   8 +-
 arch/powerpc/kernel/asm-offsets.c             |   6 +-
 arch/powerpc/kvm/book3s_hv.c                  |  73 +-
 arch/powerpc/kvm/book3s_hv_nested.c           |  15 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S       |  43 +-
 arch/powerpc/kvm/powerpc.c                    |   3 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/arch/powerpc/include/uapi/asm/kvm.h     |   8 +-
 .../selftests/powerpc/ptrace/.gitignore       |   1 +
 .../testing/selftests/powerpc/ptrace/Makefile |   2 +-
 .../selftests/powerpc/ptrace/perf-hwbreak.c   | 646 +++++++++++++++--
 .../selftests/powerpc/ptrace/ptrace-hwbreak.c |  79 +++
 .../powerpc/ptrace/ptrace-perf-hwbreak.c      | 659 ++++++++++++++++++
 16 files changed, 1476 insertions(+), 82 deletions(-)
 create mode 100644 tools/testing/selftests/powerpc/ptrace/ptrace-perf-hwbreak.c
```
#### [PATCH 0/2] ppc: Enable 2nd DAWR support on p10
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Thu Jul 23 10:42:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11680587
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 18E7113B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:43:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A83A20888
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:43:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728427AbgGWKnC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 06:43:02 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:54184 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726675AbgGWKnB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jul 2020 06:43:01 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAW0wt065837;
        Thu, 23 Jul 2020 06:42:33 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vsu8kc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:42:33 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06NAYqYw075228;
        Thu, 23 Jul 2020 06:42:32 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vsu8jv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:42:32 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAf8jU021419;
        Thu, 23 Jul 2020 10:42:30 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04fra.de.ibm.com with ESMTP id 32dbmn1wrc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 10:42:30 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06NAgQUu47120514
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jul 2020 10:42:26 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 43EA411C04A;
        Thu, 23 Jul 2020 10:42:26 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A8CC611C058;
        Thu, 23 Jul 2020 10:42:22 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.160])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jul 2020 10:42:22 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        pbonzini@redhat.com, christophe.leroy@c-s.fr, jniethe5@gmail.com,
        pedromfc@br.ibm.com, rogealve@br.ibm.com, cohuck@redhat.com,
        mst@redhat.com, clg@kaod.org, qemu-ppc@nongnu.org,
        qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH 0/2] ppc: Enable 2nd DAWR support on p10
Date: Thu, 23 Jul 2020 16:12:18 +0530
Message-Id: <20200723104220.314671-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-23_03:2020-07-22,2020-07-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 malwarescore=0 mlxlogscore=714 phishscore=0 spamscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 suspectscore=0 clxscore=1011
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007230076
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables 2nd DAWR support on p10 qemu/kvm guest. This
series depends on kernel patches:
https://lore.kernel.org/linuxppc-dev/20200723102058.312282-1-ravi.bangoria@linux.ibm.com

Patches apply fine on qemu/master branch (c8004fe6bbfc)

Ravi Bangoria (2):
  ppc: Rename current DAWR macros
  ppc: Enable 2nd DAWR support on p10

 hw/ppc/spapr.c                  | 33 +++++++++++++++++++++++++++++++++
 include/hw/ppc/spapr.h          |  3 ++-
 linux-headers/asm-powerpc/kvm.h |  8 ++++++--
 linux-headers/linux/kvm.h       |  1 +
 target/ppc/cpu.h                |  6 ++++--
 target/ppc/kvm.c                |  7 +++++++
 target/ppc/kvm_ppc.h            |  6 ++++++
 target/ppc/translate_init.inc.c | 25 ++++++++++++++++++++-----
 8 files changed, 79 insertions(+), 10 deletions(-)
```
#### [PATCH v3 0/5] vfio/pci: add denylist and disable qat
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
From patchwork Thu Jul 23 21:47:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11681661
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D73C722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 21:47:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F29922B49
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 21:47:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726567AbgGWVrZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 17:47:25 -0400
Received: from mga04.intel.com ([192.55.52.120]:44370 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726173AbgGWVrZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jul 2020 17:47:25 -0400
IronPort-SDR: 
 IHiOQUigsowuovwF9++LoAbHkFLEviz8Ueu8V+fucqfxakLRBFcc4mh+cItJlfNLDfdPwfAvJe
 sTWaVTzFJH6Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="148119970"
X-IronPort-AV: E=Sophos;i="5.75,388,1589266800";
   d="scan'208";a="148119970"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jul 2020 14:47:25 -0700
IronPort-SDR: 
 DR3gv6LNQVyX5Ww+GFh6oO5u5AZ/6kZgXFBP/+g4YSvs7wxsWPKWKERIyDixI8ngadk6lYYImp
 JN37i6bEyAvw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,388,1589266800";
   d="scan'208";a="311183940"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by fmsmga004.fm.intel.com with ESMTP; 23 Jul 2020 14:47:22 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v3 0/5] vfio/pci: add denylist and disable qat
Date: Thu, 23 Jul 2020 22:47:00 +0100
Message-Id: <20200723214705.5399-1-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset defines a denylist of devices in the vfio-pci module and adds
the current generation of Intel(R) QuickAssist devices to it as they are
not designed to run in an untrusted environment.

By default, if a device is in the denylist, the probe of vfio-pci fails.
If a user wants to use a device in the denylist, he needs to disable the
full denylist providing the option disable_denylist=1 at the load of
vfio-pci or specifying that parameter in a config file in /etc/modprobe.d.

This series also moves the device ids definitions present in the qat driver
to linux/pci_ids.h since they will be shared between the vfio-pci and the qat
drivers and replaces the custom ADF_SYSTEM_DEVICE macro with PCI_VDEVICE.

The series is applicable to Herbert's tree. Patches 1 to 3 apply also to
Alex's tree (next). Patches 4 and 5 are optional and can be applied at a later
stage.

Changes from v2:
 - Renamed blocklist in denylist
 - Patch #2: reworded module parameter description to clarify why a device is
   in the denylist
 - Patch #2: reworded warning that occurs when denylist is enabled and device
   is present in that list

Changes from v1:
 - Reworked commit messages:
   Patches #1, #2 and #3: capitalized first character after column to comply to
   subject line convention
   Patch #3: Capitalized QAT acronym and added link and doc number for document
   "Intel® QuickAssist Technology (Intel® QAT) Software for Linux"

Giovanni Cabiddu (5):
  PCI: Add Intel QuickAssist device IDs
  vfio/pci: Add device denylist
  vfio/pci: Add QAT devices to denylist
  crypto: qat - replace device ids defines
  crypto: qat - use PCI_VDEVICE

 drivers/crypto/qat/qat_c3xxx/adf_drv.c        | 11 ++---
 drivers/crypto/qat/qat_c3xxxvf/adf_drv.c      | 11 ++---
 drivers/crypto/qat/qat_c62x/adf_drv.c         | 11 ++---
 drivers/crypto/qat/qat_c62xvf/adf_drv.c       | 11 ++---
 .../crypto/qat/qat_common/adf_accel_devices.h |  6 ---
 drivers/crypto/qat/qat_common/qat_hal.c       |  7 +--
 drivers/crypto/qat/qat_common/qat_uclo.c      |  9 ++--
 drivers/crypto/qat/qat_dh895xcc/adf_drv.c     | 11 ++---
 drivers/crypto/qat/qat_dh895xccvf/adf_drv.c   | 11 ++---
 drivers/vfio/pci/vfio_pci.c                   | 48 +++++++++++++++++++
 include/linux/pci_ids.h                       |  6 +++
 11 files changed, 87 insertions(+), 55 deletions(-)
```
