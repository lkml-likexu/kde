

#### [PATCH v2 0/2] selftests: KVM: AMD Nested SVM test infrastructure
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Feb  3 09:08:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11362229
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABA24138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 09:09:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 896502070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 09:09:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AU6oMYsI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727451AbgBCJJY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 04:09:24 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:45398 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726853AbgBCJJX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 04:09:23 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580720962;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=r9fxWWlEahNQ22mhQNSmY7IQqFx4Ff6A7HJS7S6T+SQ=;
        b=AU6oMYsIs0o6tkMN36SnSguHx5DQdEhQzcqFbMVuSQkBUnf2Edgfn3qGuPi05xpto8y0bQ
        9JBmiDQV8XzHHs29qFXqO6KmcF2cUAymmlDHEMgXL8pkvwlAezg0/1WlayBJfS70/u5u35
        rjqSuaaahnAnmimvTQ4oPPsFiCAWX64=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-140-kETJaCAZP4eWE84Y6UxxdA-1; Mon, 03 Feb 2020 04:09:21 -0500
X-MC-Unique: kETJaCAZP4eWE84Y6UxxdA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3D1B21882CD2;
        Mon,  3 Feb 2020 09:09:20 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AED40165F7;
        Mon,  3 Feb 2020 09:09:13 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com
Subject: [PATCH v2 0/2] selftests: KVM: AMD Nested SVM test infrastructure
Date: Mon,  3 Feb 2020 10:08:49 +0100
Message-Id: <20200203090851.19938-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the basic infrastructure needed to test AMD nested SVM.
Also add a first basic vmcall test.

Best regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.5-amd-svm-v2

History:
v1 -> v2:
- split into 2 patches
- remove the infrastructure to run low-level sub-tests and only
  keep vmmcall's one.
- move struct regs into processor.h
- force vmcb_gpa into rax in run_guest()

Eric Auger (2):
  selftests: KVM: AMD Nested test infrastructure
  selftests: KVM: SVM: Add vmcall test

 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/include/x86_64/processor.h  |  20 +
 .../selftests/kvm/include/x86_64/svm.h        | 355 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/x86_64/svm.c  | 211 +++++++++++
 .../selftests/kvm/x86_64/svm_vmcall_test.c    |  86 +++++
 5 files changed, 674 insertions(+), 1 deletion(-)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/svm.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/svm_vmcall_test.c
```
#### [RFCv2 00/37] KVM: s390: Add support for protected VMs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Feb  3 13:19:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11362607
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE3A11395
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 13:20:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 89CB72080D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 13:20:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727756AbgBCNUD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 08:20:03 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24848 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726913AbgBCNUC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 3 Feb 2020 08:20:02 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 013DFUNa059470
        for <kvm@vger.kernel.org>; Mon, 3 Feb 2020 08:20:01 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxbx5ykag-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 03 Feb 2020 08:20:01 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 013DFm2S060616
        for <kvm@vger.kernel.org>; Mon, 3 Feb 2020 08:20:01 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xxbx5yka0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 Feb 2020 08:20:01 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 013DFSGN028727;
        Mon, 3 Feb 2020 13:20:00 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma02dal.us.ibm.com with ESMTP id 2xw0y6da44-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 03 Feb 2020 13:20:00 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 013DJwkv46072098
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 3 Feb 2020 13:19:58 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4AE612806E;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3C0C92805C;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon,  3 Feb 2020 13:19:58 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>
Subject: [RFCv2 00/37] KVM: s390: Add support for protected VMs
Date: Mon,  3 Feb 2020 08:19:20 -0500
Message-Id: <20200203131957.383915-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-03_04:2020-02-02,2020-02-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 priorityscore=1501
 adultscore=0 bulkscore=0 phishscore=0 clxscore=1015 impostorscore=0
 lowpriorityscore=0 spamscore=0 malwarescore=0 suspectscore=0
 mlxlogscore=661 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2002030099
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

All patches are in the protvirtv2 branch of the korg s390 kvm git
(on top of Janoschs reset rework).

Claudio presented the technology at his presentation at KVM Forum
2019.

This contains a "pretty small" common code memory management change that
will allow paging, guest backing with files etc almost just like normal
VMs. Please note that the memory management part will still see some
changes to deal with a corner case for the adapter interrupt indicator
pages. So please focus on the non-mm parts (which hopefully has
everthing addressed in the next version). Claudio will work with Andrea
regarding this.

Christian Borntraeger (3):
  KVM: s390/mm: Make pages accessible before destroying the guest
  KVM: s390: protvirt: Add SCLP interrupt handling
  KVM: s390: protvirt: do not inject interrupts after start

Claudio Imbrenda (3):
  mm:gup/writeback: add callbacks for inaccessible pages
  s390/mm: provide memory management functions for protected KVM guests
  KVM: s390/mm: handle guest unpin events

Janosch Frank (24):
  DOCUMENTATION: protvirt: Protected virtual machine introduction
  KVM: s390: add new variants of UV CALL
  KVM: s390: protvirt: Add initial lifecycle handling
  KVM: s390: protvirt: Add KVM api documentation
  KVM: s390: protvirt: Secure memory is not mergeable
  KVM: s390: protvirt: Handle SE notification interceptions
  KVM: s390: protvirt: Instruction emulation
  KVM: s390: protvirt: Handle spec exception loops
  KVM: s390: protvirt: Add new gprs location handling
  KVM: S390: protvirt: Introduce instruction data area bounce buffer
  KVM: s390: protvirt: handle secure guest prefix pages
  KVM: s390: protvirt: Write sthyi data to instruction data area
  KVM: s390: protvirt: STSI handling
  KVM: s390: protvirt: disallow one_reg
  KVM: s390: protvirt: Only sync fmt4 registers
  KVM: s390: protvirt: Add program exception injection
  DOCUMENTATION: protvirt: Diag 308 IPL
  KVM: s390: protvirt: Add diag 308 subcode 8 - 10 handling
  KVM: s390: protvirt: UV calls diag308 0, 1
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Add UV debug trace
  KVM: s390: protvirt: Mask PSW interrupt bits for interception 104 and
    112
  KVM: s390: protvirt: Add UV cpu reset calls

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
 Documentation/virt/kvm/api.txt                |  62 +++
 Documentation/virt/kvm/s390-pv-boot.rst       |  64 +++
 Documentation/virt/kvm/s390-pv.rst            | 103 ++++
 MAINTAINERS                                   |   1 +
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  20 +-
 arch/s390/include/asm/gmap.h                  |   3 +
 arch/s390/include/asm/kvm_host.h              | 112 +++-
 arch/s390/include/asm/mmu.h                   |   2 +
 arch/s390/include/asm/mmu_context.h           |   1 +
 arch/s390/include/asm/page.h                  |   5 +
 arch/s390/include/asm/pgtable.h               |  35 +-
 arch/s390/include/asm/uv.h                    | 265 +++++++++-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   7 +-
 arch/s390/kernel/uv.c                         | 271 ++++++++++
 arch/s390/kvm/Kconfig                         |  19 +
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/diag.c                          |   7 +
 arch/s390/kvm/intercept.c                     | 107 +++-
 arch/s390/kvm/interrupt.c                     | 211 ++++++--
 arch/s390/kvm/kvm-s390.c                      | 486 ++++++++++++++++--
 arch/s390/kvm/kvm-s390.h                      |  56 ++
 arch/s390/kvm/priv.c                          |   9 +-
 arch/s390/kvm/pv.c                            | 293 +++++++++++
 arch/s390/mm/fault.c                          |  87 ++++
 arch/s390/mm/gmap.c                           |  63 ++-
 include/linux/gfp.h                           |   6 +
 include/uapi/linux/kvm.h                      |  47 +-
 mm/gup.c                                      |   2 +
 mm/page-writeback.c                           |   1 +
 33 files changed, 2217 insertions(+), 142 deletions(-)
 create mode 100644 Documentation/virt/kvm/s390-pv-boot.rst
 create mode 100644 Documentation/virt/kvm/s390-pv.rst
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
#### [PATCH v2 0/6] kvm/split_lock: Add feature split lock detection
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Mon Feb  3 15:16:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11362989
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 472E01395
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 15:21:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25F2221775
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 15:21:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727619AbgBCPVR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 10:21:17 -0500
Received: from mga02.intel.com ([134.134.136.20]:32939 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726272AbgBCPVR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 10:21:17 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Feb 2020 07:21:16 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,398,1574150400";
   d="scan'208";a="429473339"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by fmsmga005.fm.intel.com with ESMTP; 03 Feb 2020 07:21:15 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@amacapital.net>
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        David Laight <David.Laight@aculab.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 0/6] kvm/split_lock: Add feature split lock detection
 support in kvm
Date: Mon,  3 Feb 2020 23:16:02 +0800
Message-Id: <20200203151608.28053-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This version adds the virtualization of split lock detection for guest
in patch 5 and patch 6.

No matter whether we advertise split lock detection to guest, we have to make
a choice between not burn the old guest and prevent DoS attack from guest since
we cannot identify whether a guest is malicious.

Since sld_warn mode also allows userspace applications to do split lock
we can extend the similar policy to guest that if host is sld_warn, we allow
guest to generate split lock by clearing MSR_TEST_CTRL.SPLIT_LOCK_DETECT bit
when vcpu is running.

If host is sld_fatal mode and guest doesn't set its SPLIT_LOCK_DETECT bit we
forward split lock #AC to user space, similar as sending SIGBUS.

Xiaoyao Li (6):
  x86/split_lock: Add and export get_split_lock_detect_state()
  x86/split_lock: Add and export split_lock_detect_set()
  kvm: x86: Emulate split-lock access as a write
  kvm: vmx: Extend VMX's #AC handding for split lock in guest
  kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
  x86: vmx: virtualize split lock detection

 arch/x86/include/asm/cpu.h      | 13 +++++
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kernel/cpu/intel.c     | 18 ++++--
 arch/x86/kvm/cpuid.c            |  5 +-
 arch/x86/kvm/vmx/vmx.c          | 98 ++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.h          |  4 ++
 arch/x86/kvm/x86.c              | 44 ++++++++++++++-
 7 files changed, 171 insertions(+), 12 deletions(-)
```
#### [PATCH 0/2] KVM: MIPS: Bug fix and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Feb  3 18:41:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11363301
Return-Path: <SRS0=qnBn=3X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31FA292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 18:42:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19B9D2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Feb 2020 18:42:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729502AbgBCSmC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Feb 2020 13:42:02 -0500
Received: from mga02.intel.com ([134.134.136.20]:49288 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726930AbgBCSmC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Feb 2020 13:42:02 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Feb 2020 10:42:01 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,398,1574150400";
   d="scan'208";a="310804550"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 03 Feb 2020 10:42:01 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 0/2] KVM: MIPS: Bug fix and cleanup
Date: Mon,  3 Feb 2020 10:41:58 -0800
Message-Id: <20200203184200.23585-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix for a compilation error introduced by the vCPU create refactoring, and
a patch on top to cleanup some ugliness in the relocated code.

Untested, really need to setup a cross-compiling environment...

Sean Christopherson (2):
  KVM: MIPS: Fix a build error due to referencing not-yet-defined
    function
  KVM: MIPS: Fold comparecount_func() into comparecount_wakeup()

 arch/mips/kvm/mips.c | 37 ++++++++++++++++---------------------
 1 file changed, 16 insertions(+), 21 deletions(-)
```
