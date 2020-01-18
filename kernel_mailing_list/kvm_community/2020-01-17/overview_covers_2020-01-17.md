

#### [PATCH 0/4] KVM: x86: TIF_NEED_FPU_LOAD bug fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jan 17 06:26:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11338405
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 087B092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 06:27:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E439E2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 06:27:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729093AbgAQG07 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 01:26:59 -0500
Received: from mga17.intel.com ([192.55.52.151]:14600 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726479AbgAQG0j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jan 2020 01:26:39 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 16 Jan 2020 22:26:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,329,1574150400";
   d="scan'208";a="424342466"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 16 Jan 2020 22:26:29 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Derek Yerger <derek@djy.llc>,
        kernel@najdan.com, Thomas Lambertz <mail@thomaslambertz.de>,
        Rik van Riel <riel@surriel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Borislav Petkov <bp@suse.de>,
        Dave Hansen <dave.hansen@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH 0/4] KVM: x86: TIF_NEED_FPU_LOAD bug fixes
Date: Thu, 16 Jan 2020 22:26:24 -0800
Message-Id: <20200117062628.6233-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Three bug fixes related to deferring FPU loading to return to userspace,
or in this case, deferring to entering a KVM guest.  And a cleanup patch I
couldn't resist throwing on top.

The crux of the matter is that TIF_FPU_NEED_LOAD can be set any time
control is transferred out of KVM, e.g. via IRQ->softirq, not just when
KVM is preempted.  The previous attempt to fix the underlying bug(s)
by handling TIF_FPU_NEED_LOAD during kvm_sched_in() only made the bug(s)
harder to hit, i.e. it resolved the preemption case but only shrunk the
window where a softirq could corrupt state.

Paolo, patch 01 will conflict with commit 95145c25a78c ("KVM: x86: Add a
WARN on TIF_NEED_FPU_LOAD in kvm_load_guest_fpu()") that is sitting in
kvm/queue.  The kvm/queue commit should simply be dropped.

Patch 01 fixes the original underlying bug, which is that KVM doesn't
handle TIF_FPU_NEED_LOAD when swapping between guest and userspace FPU
state.

Patch 02 fixes (unconfirmed) issues similar to the reported bug where KVM
doesn't ensure CPU FPU state is fresh when accessing it during emulation.
This patch is smoke tested only (via kvm-unit-tests' emulator tests).

Patch 03 reverts the preemption bug fix, which simultaneously restores the
handling of TIF_FPU_NEED_LOAD in vcpu_enter_guest() to fix the reported
bugs[1][2] and removes the now-unnecessary preemption workaround.

Alternatively, the handling of TIF_NEED_FPU_LOAD in the kvm_sched_in()
path could be left in place, i.e it doesn't cause immediate damage, but
as stated before, restoring FPU state after KVM is preempted only makes
it harder to find the actual bugs.  Case in point, I originally split
the revert into two separate patches (so that removing the kvm_sched_in()
call wouldn't be tagged for stable), but that only hid the underlying
kvm_put_guest_fpu() bug until I fully reverted the commit.

Patch 04 removes an unused emulator context param from several of the
functions that are fixed in patch 02.  The param was left behind during
a previous KVM FPU state rework.

Tested via Thomas Lambertz's mprime reproducer[3], which detected issues
with buggy KVMs on my system in under a minute.  Ran clean for ~30 minutes
on each of the first two patches and several hours with all three patches
applied.

[1] https://lore.kernel.org/kvm/1e525b08-6204-3238-5d56-513f82f1d7fb@djy.llc
[2] https://lore.kernel.org/kvm/bug-206215-28872@https.bugzilla.kernel.org%2F
[3] https://lore.kernel.org/lkml/217248af-e980-9cb0-ff0d-9773413b9d38@thomaslambertz.de

Sean Christopherson (4):
  KVM: x86: Handle TIF_NEED_FPU_LOAD in kvm_{load,put}_guest_fpu()
  KVM: x86: Ensure guest's FPU state is loaded when accessing for
    emulation
  KVM: x86: Revert "KVM: X86: Fix fpu state crash in kvm guest"
  KVM: x86: Remove unused ctxt param from emulator's FPU accessors

 arch/x86/kvm/emulate.c | 67 ++++++++++++++++++++++++++++++++----------
 arch/x86/kvm/x86.c     | 36 +++++++++++++++++------
 2 files changed, 79 insertions(+), 24 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/9] s390x: smp: Improve smp code and reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Jan 17 10:46:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11338725
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FB8C13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 10:46:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 784632083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 10:46:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727012AbgAQKqy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 05:46:54 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40572 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726915AbgAQKqy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jan 2020 05:46:54 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00HAbwqq021956
        for <kvm@vger.kernel.org>; Fri, 17 Jan 2020 05:46:53 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xk0qtraud-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 17 Jan 2020 05:46:53 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 17 Jan 2020 10:46:51 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 17 Jan 2020 10:46:47 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00HAkkxE49217748
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jan 2020 10:46:46 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9B498AE051;
        Fri, 17 Jan 2020 10:46:46 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 13404AE053;
        Fri, 17 Jan 2020 10:46:45 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.184.110])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jan 2020 10:46:44 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/9] s390x: smp: Improve smp code and reset
 checks
Date: Fri, 17 Jan 2020 05:46:31 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011710-0028-0000-0000-000003D1F5CD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011710-0029-0000-0000-0000249620D3
Message-Id: <20200117104640.1983-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-17_02:2020-01-16,2020-01-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 phishscore=0
 malwarescore=0 clxscore=1015 mlxscore=0 suspectscore=0 adultscore=0
 bulkscore=0 lowpriorityscore=0 priorityscore=1501 spamscore=0
 mlxlogscore=365 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001170083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's extend sigp reset testing and clean up the smp library as well.

GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup

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

 lib/s390x/interrupt.c | 20 +++++------
 lib/s390x/smp.c       | 52 ++++++++++++++++-----------
 s390x/cstart64.S      |  4 +++
 s390x/smp.c           | 82 +++++++++++++++++++++++++++----------------
 4 files changed, 97 insertions(+), 61 deletions(-)
```
#### [PATCH v2 0/4] KVM: x86: TIF_NEED_FPU_LOAD bug fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jan 17 19:30:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11339707
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BA1E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 19:35:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 537492082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 19:35:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729360AbgAQTeh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 14:34:37 -0500
Received: from mga18.intel.com ([134.134.136.126]:18185 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726761AbgAQTeh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jan 2020 14:34:37 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Jan 2020 11:30:54 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,331,1574150400";
   d="scan'208";a="274474188"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Jan 2020 11:30:53 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Derek Yerger <derek@djy.llc>,
        kernel@najdan.com, Thomas Lambertz <mail@thomaslambertz.de>,
        Rik van Riel <riel@surriel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Borislav Petkov <bp@suse.de>,
        Dave Hansen <dave.hansen@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH v2 0/4] KVM: x86: TIF_NEED_FPU_LOAD bug fixes
Date: Fri, 17 Jan 2020 11:30:48 -0800
Message-Id: <20200117193052.1339-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Apologies for the quick v2, I'm hoping the fixes can squeak into 5.5 and
I'm about to go offline for a long weekend.

v2: Add a helper to handle TIF_NEED_FPU_LOAD when saving from the current
    FPU to the guest/userspace FPU (patch 01). [Dave]

*** v1 cover letter ***

Three bug fixes related to deferring FPU loading to return to userspace,
or in this case, deferring to entering a KVM guest.  And a cleanup patch I
couldn't resist throwing on top.

The crux of the matter is that TIF_FPU_NEED_LOAD can be set any time
control is transferred out of KVM, e.g. via IRQ->softirq, not just when
KVM is preempted.  The previous attempt to fix the underlying bug(s)
by handling TIF_FPU_NEED_LOAD during kvm_sched_in() only made the bug(s)
harder to hit, i.e. it resolved the preemption case but only shrunk the
window where a softirq could corrupt state.

Paolo, patch 01 will conflict with commit 95145c25a78c ("KVM: x86: Add a
WARN on TIF_NEED_FPU_LOAD in kvm_load_guest_fpu()") that is sitting in
kvm/queue.  The kvm/queue commit should simply be dropped.

Patch 01 fixes the original underlying bug, which is that KVM doesn't
handle TIF_FPU_NEED_LOAD when swapping between guest and userspace FPU
state.

Patch 02 fixes (unconfirmed) issues similar to the reported bug where KVM
doesn't ensure CPU FPU state is fresh when accessing it during emulation.
This patch is smoke tested only (via kvm-unit-tests' emulator tests).

Patch 03 reverts the preemption bug fix, which simultaneously restores the
handling of TIF_FPU_NEED_LOAD in vcpu_enter_guest() to fix the reported
bugs[1][2] and removes the now-unnecessary preemption workaround.

Alternatively, the handling of TIF_NEED_FPU_LOAD in the kvm_sched_in()
path could be left in place, i.e it doesn't cause immediate damage, but
as stated before, restoring FPU state after KVM is preempted only makes
it harder to find the actual bugs.  Case in point, I originally split
the revert into two separate patches (so that removing the kvm_sched_in()
call wouldn't be tagged for stable), but that only hid the underlying
kvm_put_guest_fpu() bug until I fully reverted the commit.

Patch 04 removes an unused emulator context param from several of the
functions that are fixed in patch 02.  The param was left behind during
a previous KVM FPU state rework.

Tested via Thomas Lambertz's mprime reproducer[3], which detected issues
with buggy KVMs on my system in under a minute.  Ran clean for ~30 minutes
on each of the first two patches and several hours with all three patches
applied.

[1] https://lore.kernel.org/kvm/1e525b08-6204-3238-5d56-513f82f1d7fb@djy.llc
[2] https://lore.kernel.org/kvm/bug-206215-28872@https.bugzilla.kernel.org%2F
[3] https://lore.kernel.org/lkml/217248af-e980-9cb0-ff0d-9773413b9d38@thomaslambertz.de

Sean Christopherson (4):
  KVM: x86: Handle TIF_NEED_FPU_LOAD in kvm_{load,put}_guest_fpu()
  KVM: x86: Ensure guest's FPU state is loaded when accessing for
    emulation
  KVM: x86: Revert "KVM: X86: Fix fpu state crash in kvm guest"
  KVM: x86: Remove unused ctxt param from emulator's FPU accessors

 arch/x86/kvm/emulate.c | 67 ++++++++++++++++++++++++++++++++----------
 arch/x86/kvm/x86.c     | 28 +++++++++++++-----
 2 files changed, 72 insertions(+), 23 deletions(-)
```
