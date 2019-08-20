

#### [PATCH V3 0/3] KVM/Hyper-V: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

This patchset is to add Hyper-V direct tlb support in KVM. Hyper-V
in L0 can delegate L1 hypervisor to handle tlb flush request from
L2 guest when direct tlb flush is enabled in L1.

Patch 2 introduces new cap KVM_CAP_HYPERV_DIRECT_TLBFLUSH to enable
feature from user space. User space should enable this feature only
when Hyper-V hypervisor capability is exposed to guest and KVM profile
is hided. There is a parameter conflict between KVM and Hyper-V hypercall.
We hope L2 guest doesn't use KVM hypercall when the feature is
enabled. Detail please see comment of new API "KVM_CAP_HYPERV_DIRECT_TLBFLUSH"

Change since v2:
       - Move hv assist page(hv_pa_pg) from struct kvm  to struct kvm_hv.

Change since v1:
       - Fix offset issue in the patch 1.
       - Update description of KVM KVM_CAP_HYPERV_DIRECT_TLBFLUSH.


Tianyu Lan (2):
  x86/Hyper-V: Fix definition of struct hv_vp_assist_page
  KVM/Hyper-V: Add new KVM cap KVM_CAP_HYPERV_DIRECT_TLBFLUSH

Vitaly Kuznetsov (1):
  KVM/Hyper-V/VMX: Add direct tlb flush support

 Documentation/virtual/kvm/api.txt  | 13 +++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h | 24 ++++++++++++++++++-----
 arch/x86/include/asm/kvm_host.h    |  4 ++++
 arch/x86/kvm/vmx/evmcs.h           |  2 ++
 arch/x86/kvm/vmx/vmx.c             | 39 ++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                 |  8 ++++++++
 include/uapi/linux/kvm.h           |  1 +
 7 files changed, 86 insertions(+), 5 deletions(-)
```
#### [PATCH v2 0/9] arm64: Stolen time support
##### From: Steven Price <steven.price@arm.com>

```c

This series add support for paravirtualized time for arm64 guests and
KVM hosts following the specification in Arm's document DEN 0057A:

https://developer.arm.com/docs/den0057/a

It implements support for stolen time, allowing the guest to
identify time when it is forcibly not executing.

It doesn't implement support for Live Physical Time (LPT) as there are
some concerns about the overheads and approach in the above
specification, and I expect an updated version of the specification to
be released soon with just the stolen time parts.

NOTE: Patches 7 and 8 will conflict with Mark Rutland's series[1] cleaning
up the SMCCC conduit. I do feel that the addition of an _invoke() call
makes a number of call sites cleaner and it should be possible to
integrate both this and Mark's other cleanups.

[1] https://lore.kernel.org/linux-arm-kernel/20190809132245.43505-1-mark.rutland@arm.com/

Changes from v1:
https://lore.kernel.org/lkml/20190802145017.42543-1-steven.price@arm.com/
 * Host kernel no longer allocates the stolen time structure, instead it
   is allocated by user space. This means the save/restore functionality
   can be removed.
 * Refactored the code so arm has stub implementations and to avoid
   initcall
 * Rebased to pick up Documentation/{virt->virtual} change
 * Bunch of typo fixes

Christoffer Dall (1):
  KVM: arm/arm64: Factor out hypercall handling from PSCI code

Steven Price (8):
  KVM: arm64: Document PV-time interface
  KVM: arm64: Implement PV_FEATURES call
  KVM: arm64: Support stolen time reporting via shared structure
  KVM: Allow kvm_device_ops to be const
  KVM: arm64: Provide a PV_TIME device to user space
  arm/arm64: Provide a wrapper for SMCCC 1.1 calls
  arm/arm64: Make use of the SMCCC 1.1 wrapper
  arm64: Retrieve stolen time as paravirtualized guest

 Documentation/virt/kvm/arm/pvtime.txt | 100 +++++++++++++
 arch/arm/include/asm/kvm_host.h       |  21 +++
 arch/arm/kvm/Makefile                 |   2 +-
 arch/arm/kvm/handle_exit.c            |   2 +-
 arch/arm/mm/proc-v7-bugs.c            |  13 +-
 arch/arm64/include/asm/kvm_host.h     |  19 ++-
 arch/arm64/include/asm/paravirt.h     |   9 +-
 arch/arm64/include/asm/pvclock-abi.h  |  17 +++
 arch/arm64/include/uapi/asm/kvm.h     |   8 ++
 arch/arm64/kernel/cpu_errata.c        |  80 ++++-------
 arch/arm64/kernel/paravirt.c          | 147 +++++++++++++++++++
 arch/arm64/kernel/time.c              |   3 +
 arch/arm64/kvm/Kconfig                |   1 +
 arch/arm64/kvm/Makefile               |   2 +
 arch/arm64/kvm/handle_exit.c          |   4 +-
 include/kvm/arm_hypercalls.h          |  43 ++++++
 include/kvm/arm_psci.h                |   2 +-
 include/linux/arm-smccc.h             |  58 ++++++++
 include/linux/cpuhotplug.h            |   1 +
 include/linux/kvm_host.h              |   4 +-
 include/linux/kvm_types.h             |   2 +
 include/uapi/linux/kvm.h              |   2 +
 virt/kvm/arm/arm.c                    |  20 +++
 virt/kvm/arm/hypercalls.c             |  68 +++++++++
 virt/kvm/arm/psci.c                   |  84 +----------
 virt/kvm/arm/pvtime.c                 | 194 ++++++++++++++++++++++++++
 virt/kvm/kvm_main.c                   |   6 +-
 27 files changed, 758 insertions(+), 154 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
#### [PATCH 0/2] KVM: nVMX: Improve HLT activity support
##### From: Nikita Leshenko <nikita.leshchenko@oracle.com>

```c
From patchwork Mon Aug 19 21:46:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikita Leshenko <nikita.leshchenko@oracle.com>
X-Patchwork-Id: 11102021
Return-Path: <SRS0=6q4q=WP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B955F1813
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 21:47:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 989DB22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 21:47:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="lr9Rc/lj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728353AbfHSVrI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 19 Aug 2019 17:47:08 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:54460 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728014AbfHSVrI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Aug 2019 17:47:08 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7JLd19S133381
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : subject :
 date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=q4B+iWSavjgpiwONyp3kxrqTfAG8hJoijgqc3JeKPBo=;
 b=lr9Rc/lj/Aaj7O6AYjv7X0yp6T1YiBF6gT4a+a/CHGMJYzPHorKEtaDQ5TN//p42ZZLZ
 MWncPxedc/WTXGo3vqJkb2kgta0SgOPZCXtBGLZ47+k0iPfNU3IF7emilDLaw6bgkn2g
 i1NZUYsZb7eZ7l5azM3GfsvuvdM0MiBW6t5sv6xx6gzMfJLO0jDojc+RhUzwcvsX5L8D
 TCH6vjV1JaZfpFa0oT4Ow4ogepddfQEilBYSATpBmo+chxtctxSFdDwbeHEqKkNfgt5S
 IDD9cAJUkeo07/ORTRto62rEhC2xcLjzX2PXX6BlWCZGM8zRZEBkwQDiNukwT/rxGFgi wg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2ue90ta9j5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:06 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7JLcOUM086288
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:06 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 2uejxemsd9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:06 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7JLl5ep009997
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:05 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 19 Aug 2019 14:47:05 -0700
From: Nikita Leshenko <nikita.leshchenko@oracle.com>
To: kvm@vger.kernel.org
Subject: [PATCH 0/2] KVM: nVMX: Improve HLT activity support
Date: Tue, 20 Aug 2019 00:46:48 +0300
Message-Id: <20190819214650.41991-1-nikita.leshchenko@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9354
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=516
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908190217
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9354
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=587 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908190217
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches improve various aspects of nested HLT activity state support. The
first patch prevents usermode from turning off the feature bit in VMX_MISC MSR
and the second patch adds additional activity state related checks on VMCS12 as
required by SDM.

These patches were tested to not cause regressions in kvm-unit-tests.

Nikita
```
