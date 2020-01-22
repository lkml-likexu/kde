

#### [virtio-dev] [PATCH v2 0/5] virtio-mmio enhancement
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
From patchwork Tue Jan 21 13:54:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 11343085
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D0B8C6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 06:19:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B97E621734
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 06:19:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727829AbgAUGTa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 01:19:30 -0500
Received: from mga02.intel.com ([134.134.136.20]:62547 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726052AbgAUGTa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 01:19:30 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Jan 2020 22:19:29 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,344,1574150400";
   d="scan'208";a="278301056"
Received: from hyperv-sh3.bj.intel.com ([10.240.193.95])
  by fmsmga001.fm.intel.com with ESMTP; 20 Jan 2020 22:19:27 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: virtio-dev@lists.oasis-open.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, Jing Liu <jing2.liu@linux.intel.com>
Subject: [virtio-dev] [PATCH v2 0/5] virtio-mmio enhancement
Date: Tue, 21 Jan 2020 21:54:28 +0800
Message-Id: <1579614873-21907-1-git-send-email-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current virtio over MMIO has some limitations that impact the performance.
It only supports single legacy, dedicated interrupt and one virtqueue
notification register for all virtqueues which cause performance penalties.

To address such limitations, we proposed to update virtio-mmio spec with
two new feature bits to support MSI interrupt and enhancing notification mechanism.

For keeping virtio-mmio simple as it was, and considering practical usages, this
provides two kinds of mapping mode for device: MSI non-sharing mode and MSI sharing mode.
MSI non-sharng mode indicates a fixed static vector and event relationship specified
in spec, which can simplify the setup process and reduce vmexit, fitting for
a high interrupt rate request.
MSI sharing mode indicates a dynamic mapping, which is more like PCI does, fitting
for a non-high interrupt rate request.

Change Log:
v1->v2:
* Change version update to feature bit
* Add mask/unmask support
* Add two MSI sharing/non-sharing modes
* Change MSI registers layout and bits

Jing Liu (5):
  virtio-mmio: Add feature bit for MMIO notification
  virtio-mmio: Enhance queue notification support
  virtio-mmio: Add feature bit for MMIO MSI
  virtio-mmio: Introduce MSI details
  virtio-mmio: MSI vector and event mapping

 content.tex | 286 ++++++++++++++++++++++++++++++++++++++++++++++++++++++------
 msi-state.c |   5 ++
 2 files changed, 262 insertions(+), 29 deletions(-)
 create mode 100644 msi-state.c
```
#### [kvm-unit-tests PATCH v4 0/9] s390x: smp: Improve smp code and reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Jan 21 13:42:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11343927
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A5B9D1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:43:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E544217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:43:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729112AbgAUNnS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:43:18 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:48558 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726968AbgAUNnS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jan 2020 08:43:18 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00LDgYPg053571
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 08:43:16 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xp1v599tg-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 08:43:16 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 21 Jan 2020 13:43:14 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 21 Jan 2020 13:43:12 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00LDhBqP54657158
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 21 Jan 2020 13:43:11 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1BC4DA4065;
        Tue, 21 Jan 2020 13:43:11 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 23889A4054;
        Tue, 21 Jan 2020 13:43:10 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.211])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 21 Jan 2020 13:43:09 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v4 0/9] s390x: smp: Improve smp code and reset
 checks
Date: Tue, 21 Jan 2020 08:42:45 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012113-0016-0000-0000-000002DF61D5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012113-0017-0000-0000-0000334209A0
Message-Id: <20200121134254.4570-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-21_04:2020-01-21,2020-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 bulkscore=0
 lowpriorityscore=0 adultscore=0 phishscore=0 mlxlogscore=385 mlxscore=0
 malwarescore=0 suspectscore=0 spamscore=0 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001210114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's extend sigp reset testing and clean up the smp library as well.

GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup

V4:
	* Introduce set_flag() for manipulating testflag
	* Cleanup of stray braces and mb()s

v3:
	* Added patch to introduce cpu loop in cpu setup
	* Added patch that removes cpu loops in favor of the previously introduced one
	* Fixed inline assembly for fpc dirtying
	* Moved cpu stop hunk from first into the second patch
	* Reworked patch #4 commit message and added a comment when waiting for PU

v2:
	* Added cpu stop to test_store_status()
	* Added smp_cpu_destroy() to the end of smp.c main()
	* New patch that prints cpu id on interrupt errors
	* New patch that reworks cpu start in the smp library (needed for lpar)
	* nullp is now an array


Janosch Frank (9):
  s390x: smp: Cleanup smp.c
  s390x: smp: Only use smp_cpu_setup once
  s390x: Add cpu id to interrupt error prints
  s390x: smp: Rework cpu start and active tracking
  s390x: smp: Wait for cpu setup to finish
  s390x: smp: Loop if secondary cpu returns into cpu setup again
  s390x: smp: Remove unneeded cpu loops
  s390x: smp: Test all CRs on initial reset
  s390x: smp: Dirty fpc before initial reset test

 lib/s390x/interrupt.c | 20 +++++-----
 lib/s390x/smp.c       | 53 ++++++++++++++----------
 s390x/cstart64.S      |  4 ++
 s390x/smp.c           | 93 ++++++++++++++++++++++++++++---------------
 4 files changed, 106 insertions(+), 64 deletions(-)
```
#### [PATCH v5 00/19] KVM: Dynamically size memslot arrays
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Jan 21 22:31:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11344689
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B9AF86C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 22:33:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9837424655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 22:33:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726590AbgAUWcD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 17:32:03 -0500
Received: from mga14.intel.com ([192.55.52.115]:1733 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725876AbgAUWcD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 17:32:03 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Jan 2020 14:32:02 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,347,1574150400";
   d="scan'208";a="244845094"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 21 Jan 2020 14:32:02 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, linux-mips@vger.kernel.org,
 kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 linux-kernel@vger.kernel.org, Christoffer Dall <christoffer.dall@arm.com>,
 Peter Xu <peterx@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v5 00/19] KVM: Dynamically size memslot arrays
Date: Tue, 21 Jan 2020 14:31:38 -0800
Message-Id: <20200121223157.15263-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I'd love to get this into 5.6 if possible.  The rebase to kvm/queue only
had a single superficial conflict with 668effb63de8 ("KVM: Fix some wrong
function names in comment"), and s390 (Christian) and arm64 (Marc) both
got smoke tested in v4.

Thanks!

v5:
  - Make the selftest x86-only. [Christian].
  - Collect tags. [Peter]
  - Rebase to kvm/queue, fb0c5f8fb698 ("KVM: x86: inline memslot_...").

v4:
  - Add patch 01 to fix an x86 rmap/lpage bug, and patches 10 and 11 to
    resolve hidden conflicts with the bug fix.
  - Collect tags [Christian, Marc, Philippe].
  - Rebase to kvm/queue, commit e41a90be9659 ("KVM: x86/mmu: WARN if
    root_hpa is invalid when handling a page fault").
v3:
  - Fix build errors on PPC and MIPS due to missed params during
    refactoring [kbuild test robot].
  - Rename the helpers for update_memslots() and add comments describing
    the new algorithm and how it interacts with searching [Paolo].
  - Remove the unnecessary and obnoxious warning regarding memslots being
    a flexible array [Paolo].
  - Fix typos in the changelog of patch 09/15 [Christoffer].
  - Collect tags [Christoffer].

v2:
  - Split "Drop kvm_arch_create_memslot()" into three patches to move
    minor functional changes to standalone patches [Janosch].
  - Rebase to latest kvm/queue (f0574a1cea5b, "KVM: x86: fix ...")
  - Collect an Acked-by and a Reviewed-by

*** v1 cover letter ***

The end goal of this series is to dynamically size the memslot array so
that KVM allocates memory based on the number of memslots in use, as
opposed to unconditionally allocating memory for the maximum number of
memslots.  On x86, each memslot consumes 88 bytes, and so with 2 address
spaces of 512 memslots, each VM consumes ~90k bytes for the memslots.
E.g. given a VM that uses a total of 30 memslots, dynamic sizing reduces
the memory footprint from 90k to ~2.6k bytes.

The changes required to support dynamic sizing are relatively small,
e.g. are essentially contained in patches 17/19 and 18/19.

Patches 2-16 clean up the memslot code, which has gotten quite crusty,
especially __kvm_set_memory_region().  The clean up is likely not strictly
necessary to switch to dynamic sizing, but I didn't have a remotely
reasonable level of confidence in the correctness of the dynamic sizing
without first doing the clean up.

The only functional change in v4 is the addition of an x86-specific bug
fix in x86's handling of KVM_MR_MOVE.  The bug fix is not directly related
to dynamically allocating memslots, but it has subtle and hidden conflicts
with the cleanup patches, and the fix is higher priority than anything
else in the series, i.e. should be merged first.

On non-x86 architectures, v3 and v4 should be functionally equivalent,
the only non-x86 change in v4 is the dropping of a "const" in
kvm_arch_commit_memory_region().

Sean Christopherson (19):
  KVM: x86: Allocate new rmap and large page tracking when moving
    memslot
  KVM: Reinstall old memslots if arch preparation fails
  KVM: Don't free new memslot if allocation of said memslot fails
  KVM: PPC: Move memslot memory allocation into prepare_memory_region()
  KVM: x86: Allocate memslot resources during prepare_memory_region()
  KVM: Drop kvm_arch_create_memslot()
  KVM: Explicitly free allocated-but-unused dirty bitmap
  KVM: Refactor error handling for setting memory region
  KVM: Move setting of memslot into helper routine
  KVM: Drop "const" attribute from old memslot in commit_memory_region()
  KVM: x86: Free arrays for old memslot when moving memslot's base gfn
  KVM: Move memslot deletion to helper function
  KVM: Simplify kvm_free_memslot() and all its descendents
  KVM: Clean up local variable usage in __kvm_set_memory_region()
  KVM: Provide common implementation for generic dirty log functions
  KVM: Ensure validity of memslot with respect to kvm_get_dirty_log()
  KVM: Terminate memslot walks via used_slots
  KVM: Dynamically size memslot array based on number of used slots
  KVM: selftests: Add test for KVM_SET_USER_MEMORY_REGION

 arch/mips/include/asm/kvm_host.h              |   2 +-
 arch/mips/kvm/mips.c                          |  71 +-
 arch/powerpc/include/asm/kvm_ppc.h            |  17 +-
 arch/powerpc/kvm/book3s.c                     |  22 +-
 arch/powerpc/kvm/book3s_hv.c                  |  36 +-
 arch/powerpc/kvm/book3s_pr.c                  |  20 +-
 arch/powerpc/kvm/booke.c                      |  17 +-
 arch/powerpc/kvm/powerpc.c                    |  15 +-
 arch/s390/include/asm/kvm_host.h              |   2 +-
 arch/s390/kvm/kvm-s390.c                      |  23 +-
 arch/x86/include/asm/kvm_page_track.h         |   3 +-
 arch/x86/kvm/mmu/page_track.c                 |  15 +-
 arch/x86/kvm/x86.c                            | 114 +---
 include/linux/kvm_host.h                      |  48 +-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  30 +
 .../kvm/x86_64/set_memory_region_test.c       | 142 ++++
 virt/kvm/arm/arm.c                            |  48 +-
 virt/kvm/arm/mmu.c                            |  20 +-
 virt/kvm/kvm_main.c                           | 621 ++++++++++++------
 22 files changed, 734 insertions(+), 535 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/set_memory_region_test.c
```
