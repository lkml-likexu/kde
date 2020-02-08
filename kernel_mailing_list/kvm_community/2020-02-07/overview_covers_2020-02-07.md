

#### [PATCH v3 0/5] Handle monitor trap flag during instruction emulation
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Fri Feb  7 10:36:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11370211
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 708BE112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 10:36:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4B2BB21741
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 10:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="iAy2sqKJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727231AbgBGKga (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 05:36:30 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:54664 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727154AbgBGKg3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 05:36:29 -0500
Received: by mail-pg1-f201.google.com with SMTP id i21so1333822pgm.21
        for <kvm@vger.kernel.org>; Fri, 07 Feb 2020 02:36:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=unQMDuml2JRM4lxYQH2f2pyITlNbCCf7jTarNpqVCtg=;
        b=iAy2sqKJeA5u4JT+aKW2ZATjLCzZ6D5Q7rsC1sHLCP+lQ9kIbvNhDGwPf7SQ2te/zf
         nxUMJGmotyhSNhO9eHPJf92319VtS+y7wL983u8ktJGoNKILbXshZgUfyVqplYpNtUgJ
         nIvwlNbcCpVY/rkSAJlvOVE/gwTCsE6OGyzuJ5msG1N4lmJRpQk4WZzQOBQnNGx+NspO
         I7xC9XTGQXpm8XU+Ftdc09y2CUAbcTbsO6GCDWf4gC8GWe/Aw8f+F/4rF6cMdjsUIW7o
         m33kncoEfF4Zt4SaW29mG2aajfA4Dj/zUgkzyBaMonzapqc92xIa96+bL6Vut2IL02LA
         PX+g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=unQMDuml2JRM4lxYQH2f2pyITlNbCCf7jTarNpqVCtg=;
        b=KPPV4lV2OW6wNoRDM8+j7kt7DRAGiZryxi5XTJwCsv3rWpyjFy/y+d4AVZq+CXGXiA
         g6kW5Rmb7uDryrk8tbivMhFzLD9Z9IfbSQ0Umf5BbSmreupZC1xlpcfU6COysydaZvB3
         S4rCY87Fg0OVVFrut9I2EEmYW6ygBi3sLKaPRS+2DpN7E/SChCab9RwIw+nLmh4cofLr
         mD6CzUMKFx5Tx4aLdMXQe7zZJ7CETL3jpicl9L+IDo7dBsPeeaB7Mk/QyKTINpYkSQ1Z
         qSaSutgXf3mIWsWszMTgFMxuCc/CdO1qvB0CUKwAQIp/gmMKJ5gJVNVcho1CAEq393XC
         bkHw==
X-Gm-Message-State: APjAAAXJZnGfD3OfGQZEZ3uIw/g+SCcIX/Jc1WyslIIY0fuj1AFhByQz
        27Oiav4O1mUuZKpsVJSrvj3M795PwrmflcOHWZC4ZNXhbYpYe+tlvUyNJVBGuqF9JeFHe10h6ly
        Z6SeCOGlo08Ixh6JemuWg6KJFZZ+U/V0JX6x1nPjOdTYfN9zDWINiwGSATA==
X-Google-Smtp-Source: 
 APXvYqxClo4dpjDVyAe6XA2FLDc0x+PYkzKL+JCtlEPz5tMClKKtBg/12Gsl2A1IsE8tk4LKsyPsPQhxIok=
X-Received: by 2002:a63:646:: with SMTP id 67mr8731570pgg.376.1581071788480;
 Fri, 07 Feb 2020 02:36:28 -0800 (PST)
Date: Fri,  7 Feb 2020 02:36:03 -0800
Message-Id: <20200207103608.110305-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v3 0/5] Handle monitor trap flag during instruction emulation
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1: http://lore.kernel.org/r/20200113221053.22053-1-oupton@google.com
v2: http://lore.kernel.org/r/20200128092715.69429-1-oupton@google.com

v1 => v2:
 - Don't split the #DB delivery by vendors. Unconditionally injecting
   #DB payloads into the 'pending debug exceptions' field will cause KVM
   to get stuck in a loop. Per the SDM, when hardware injects an event
   resulting from this field's value, it is checked against the
   exception interception bitmap.
 - Address Sean's comments by injecting the VM-exit into L1 from
   vmx_check_nested_events().
 - Added fix for nested INIT VM-exits + 'pending debug exceptions' field
   as it was noticed in implementing v2.
 - Drop Peter + Jim's Reviewed-by tags, as the patch set has changed
   since v1.

v2 => v3:
 - Merge the check/set_pending_dbg helpers into a single helper,
   vmx_update_pending_dbg(). Add clarifying comment to this helper.
 - Rewrite commit message, descriptive comment for change in 3/5 to
   explicitly describe the reason for mutating payload delivery
   behavior.
 - Undo the changes to kvm_vcpu_do_singlestep(). Instead, add a new hook
   to call for 'full' instruction emulation + 'fast' emulation.

KVM already provides guests the ability to use the 'monitor trap flag'
VM-execution control. Support for this flag is provided by the fact that
KVM unconditionally forwards MTF VM-exits to the guest (if requested),
as KVM doesn't utilize MTF. While this provides support during hardware
instruction execution, it is insufficient for instruction emulation.

Should L0 emulate an instruction on the behalf of L2, L0 should also
synthesize an MTF VM-exit into L1, should control be set.

The first patch corrects a nuanced difference between the definition of
a #DB exception payload field and DR6 register. Mask off bit 12 which is
defined in the 'pending debug exceptions' field when applying to DR6,
since the payload field is said to be compatible with the aforementioned
VMCS field.

The second patch sets the 'pending debug exceptions' VMCS field when
delivering an INIT signal VM-exit to L1, as described in the SDM. This
patch also introduces helpers for setting the 'pending debug exceptions'
VMCS field.

The third patch massages KVM's handling of exception payloads with
regard to API compatibility. Rather than immediately delivering the
payload w/o opt-in, instead defer the payload + inject
before completing a KVM_GET_VCPU_EVENTS. This maintains API
compatibility whilst correcting #DB behavior with regard to higher
priority VM-exit events.

Fourth patch introduces MTF implementation for emulated instructions.
Identify if an MTF is due on an instruction boundary from
kvm_vcpu_do_singlestep(), however only deliver this VM-exit from
vmx_check_nested_events() to respect the relative prioritization to
other VM-exits. Since this augments the nested state, introduce a new
flag for (de)serialization.

Last patch adds tests to kvm-unit-tests to assert the correctness of MTF
under several conditions (concurrent #DB trap, #DB fault, etc). These
tests pass under virtualization with this series as well as on
bare-metal.

Based on commit 2c2787938512 ("KVM: selftests: Stop memslot creation in
KVM internal memslot region").

Oliver Upton (4):
  KVM: x86: Mask off reserved bit from #DB exception payload
  KVM: nVMX: Handle pending #DB when injecting INIT VM-exit
  KVM: x86: Deliver exception payload on KVM_GET_VCPU_EVENTS
  KVM: nVMX: Emulate MTF when performing instruction emulation

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/include/uapi/asm/kvm.h |  1 +
 arch/x86/kvm/svm.c              |  1 +
 arch/x86/kvm/vmx/nested.c       | 54 ++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/nested.h       |  5 +++
 arch/x86/kvm/vmx/vmx.c          | 37 +++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              | 39 ++++++++++++++++--------
 8 files changed, 126 insertions(+), 15 deletions(-)
```
#### [PATCH 00/35] KVM: s390: Add support for protected VMs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Fri Feb  7 11:39:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11370267
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04F3F921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 11:40:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D75A0214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 11:40:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727422AbgBGLkJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 06:40:09 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50638 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727305AbgBGLkJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 06:40:09 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 017BaBFH150237;
        Fri, 7 Feb 2020 06:40:05 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y0m79r8j9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 06:40:04 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 017BbB1a152717;
        Fri, 7 Feb 2020 06:40:03 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y0m79r8hf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 06:40:03 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 017BcmY1015311;
        Fri, 7 Feb 2020 11:40:01 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma04wdc.us.ibm.com with ESMTP id 2xykc9vtpb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Feb 2020 11:40:01 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 017Be08452167154
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 7 Feb 2020 11:40:00 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3AAB5AC05E;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2981DAC059;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri,  7 Feb 2020 11:40:00 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>, linux-mm@kvack.org,
        Andrew Morton <akpm@linux-foundation.org>
Subject: [PATCH 00/35] KVM: s390: Add support for protected VMs
Date: Fri,  7 Feb 2020 06:39:23 -0500
Message-Id: <20200207113958.7320-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-07_01:2020-02-07,2020-02-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 priorityscore=1501 bulkscore=0 lowpriorityscore=0 phishscore=0 mlxscore=0
 clxscore=1015 suspectscore=0 mlxlogscore=999 malwarescore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002070089
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Upfront: This series contains a "pretty small" common code memory
management change that will allow paging, guest backing with files etc
almost just like normal VMs. It should be a no-op for all architectures
not opting in. And it should be usable for others that also try to get
notified on "the pages are in the process of being used for things like
I/O"

I CCed linux-mm (and Andrew as mm maintainer and Andrea as he was
involved in some design discussions) on the first patch (common code
mm). I also added the CC to some other patches that make use of this
infrastructure or are dealing with arch-specific memory management.

The full patch queue is on the linux-s390 and kvm mailing list.  It
would be good to get an ACK for this patch. I can then carry that via
the s390 tree.

Overview
--------
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

All patches are in the protvirtv3 branch of the korg s390 kvm git
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=protvirtv3

Claudio presented the technology at his presentation at KVM Forum
2019.

https://static.sched.com/hosted_files/kvmforum2019/3b/ibm_protected_vms_s390x.pdf


RFCv2 -> v1 (you can diff the protvirtv2 and the protvirtv3 branch)
- tons of review feedback integrated (see mail thread)
- memory management now complete and working
- Documentation patches merged
- interrupt patches merged
- CONFIG_KVM_S390_PROTECTED_VIRTUALIZATION_HOST removed
- SIDA interface integrated into memop
- for merged patches I removed reviews that were not in all patches

Christian Borntraeger (3):
  KVM: s390/mm: Make pages accessible before destroying the guest
  KVM: s390: protvirt: Add SCLP interrupt handling
  KVM: s390: protvirt: do not inject interrupts after start

Claudio Imbrenda (3):
  mm:gup/writeback: add callbacks for inaccessible pages
  s390/mm: provide memory management functions for protected KVM guests
  KVM: s390/mm: handle guest unpin events

Janosch Frank (23):
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
  KVM: s390: protvirt: Add diag 308 subcode 8 - 10 handling
  KVM: s390: protvirt: UV calls diag308 0, 1
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Add UV debug trace
  KVM: s390: protvirt: Mask PSW interrupt bits for interception 104 and
    112
  KVM: s390: protvirt: Add UV cpu reset calls
  DOCUMENTATION: Protected virtual machine introduction and IPL

Michael Mueller (2):
  KVM: s390: protvirt: Add interruption injection controls
  KVM: s390: protvirt: Implement interruption injection

Ulrich Weigand (1):
  KVM: s390/interrupt: do not pin adapter interrupt pages

Vasily Gorbik (3):
  s390/protvirt: introduce host side setup
  s390/protvirt: add ultravisor initialization
  s390/mm: add (non)secure page access exceptions handlers

 .../admin-guide/kernel-parameters.txt         |   5 +
 Documentation/virt/kvm/api.txt                |  67 ++-
 Documentation/virt/kvm/index.rst              |   2 +
 Documentation/virt/kvm/s390-pv-boot.rst       |  79 +++
 Documentation/virt/kvm/s390-pv.rst            | 116 +++++
 MAINTAINERS                                   |   1 +
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  21 +-
 arch/s390/include/asm/gmap.h                  |   3 +
 arch/s390/include/asm/kvm_host.h              | 114 ++++-
 arch/s390/include/asm/mmu.h                   |   2 +
 arch/s390/include/asm/mmu_context.h           |   1 +
 arch/s390/include/asm/page.h                  |   5 +
 arch/s390/include/asm/pgtable.h               |  35 +-
 arch/s390/include/asm/uv.h                    | 267 +++++++++-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   7 +-
 arch/s390/kernel/uv.c                         | 274 ++++++++++
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/diag.c                          |   1 +
 arch/s390/kvm/intercept.c                     | 109 +++-
 arch/s390/kvm/interrupt.c                     | 371 +++++++++++---
 arch/s390/kvm/kvm-s390.c                      | 477 ++++++++++++++++--
 arch/s390/kvm/kvm-s390.h                      |  39 ++
 arch/s390/kvm/priv.c                          |  11 +-
 arch/s390/kvm/pv.c                            | 292 +++++++++++
 arch/s390/mm/fault.c                          |  86 ++++
 arch/s390/mm/gmap.c                           |  65 ++-
 include/linux/gfp.h                           |   6 +
 include/uapi/linux/kvm.h                      |  42 +-
 mm/gup.c                                      |   2 +
 mm/page-writeback.c                           |   1 +
 33 files changed, 2325 insertions(+), 185 deletions(-)
 create mode 100644 Documentation/virt/kvm/s390-pv-boot.rst
 create mode 100644 Documentation/virt/kvm/s390-pv.rst
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
#### [PATCH v5 0/4] selftests: KVM: AMD Nested SVM test infrastructure
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Feb  7 14:27:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11370505
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E021F13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 14:27:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BE898222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 14:27:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="eqBKQHTA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727387AbgBGO1a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 09:27:30 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:51734 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726954AbgBGO12 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 09:27:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581085647;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=jwJM7q/e9p9HXTIwr62/TuUkBLeaNLEHgFKTsr8PSuE=;
        b=eqBKQHTAHddWNI+Ccu3zIvtRvtyT1WfUy+yyWJtXeqA4r8ZeakaS7WqspPaWDnVsp1u9Cy
        Xm7Aj7ON7gLKRf37b51nQSEO1eMzKavYGkiSp0JwgNdIlnFclb0g0HYst1MJsTJPeKQyGX
        KJnG8SvyqHyO4X4c3jChRhba+8HeX6s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-154-1rZIaGQvNe2wvYr-CXgZYQ-1; Fri, 07 Feb 2020 09:27:25 -0500
X-MC-Unique: 1rZIaGQvNe2wvYr-CXgZYQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 35674113787E;
        Fri,  7 Feb 2020 14:27:24 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ABF8C60BEC;
        Fri,  7 Feb 2020 14:27:17 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com, wei.huang2@amd.com,
        krish.sadhukhan@oracle.com
Subject: [PATCH v5 0/4] selftests: KVM: AMD Nested SVM test infrastructure
Date: Fri,  7 Feb 2020 15:27:11 +0100
Message-Id: <20200207142715.6166-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the basic infrastructure needed to test AMD nested SVM.
Also add a first basic vmcall test.

Best regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.5-amd-svm-v5

History:
v4 -> v5:
- Added "selftests: KVM: Remove unused x86_register enum"
- reorder GPRs within gpr64_regs
- removed vmcb_hva and save_area_hva from svm_test_data
- remove the naming for vmcb_gpa in run_guest

v3 -> v4:
- gpr64_regs struct just contains 64b mode GPRs ordered
  as in x86_register
- cleanup in run_guest (vm* instructions) and reduce
  clubber list.
- add some comments

v2 -> v3:
- Took into account Vitaly's comment:
  - added "selftests: KVM: Replace get_gdt/idt_base() by
    get_gdt/idt()"
  - svm.h now is a copy of arch/x86/include/asm/svm.h
  - avoid duplicates

v1 -> v2:
- split into 2 patches
- remove the infrastructure to run low-level sub-tests and only
  keep vmmcall's one.
- move struct regs into processor.h
- force vmcb_gpa into rax in run_guest()

Eric Auger (4):
  selftests: KVM: Replace get_[gdt | idt]_base() by get_[gdt | idt]()
  selftests: KVM: Remove unused x86_register enum
  selftests: KVM: AMD Nested test infrastructure
  selftests: KVM: SVM: Add vmcall test

 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/include/x86_64/processor.h  |  44 +--
 .../selftests/kvm/include/x86_64/svm.h        | 297 ++++++++++++++++++
 .../selftests/kvm/include/x86_64/svm_util.h   |  36 +++
 tools/testing/selftests/kvm/lib/x86_64/svm.c  | 159 ++++++++++
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   6 +-
 .../selftests/kvm/x86_64/svm_vmcall_test.c    |  79 +++++
 7 files changed, 598 insertions(+), 26 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm_util.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/svm.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/svm_vmcall_test.c
```
#### [PATCH v2 0/7] KVM: x86/mmu: nVMX: 5-level paging fixes and enabling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Feb  7 17:37:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11370847
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A606913A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:38:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8276820838
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:38:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727005AbgBGRhu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 12:37:50 -0500
Received: from mga06.intel.com ([134.134.136.31]:53093 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726897AbgBGRhu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 12:37:50 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Feb 2020 09:37:49 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,414,1574150400";
   d="scan'208";a="346067524"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 07 Feb 2020 09:37:48 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/7] KVM: x86/mmu: nVMX: 5-level paging fixes and enabling
Date: Fri,  7 Feb 2020 09:37:40 -0800
Message-Id: <20200207173747.6243-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two fixes for 5-level paging bugs with a 100% fatality rate, a patch to
enable 5-level EPT in L1, and additional clean up on top (mostly renames
of functions/variables that caused me no end of confusion when trying to
figure out what was broken).

Tested fixed kernels at L0, L1 and L2, with most combinations of EPT,
shadow paging, 4-level and 5-level.  EPT kvm-unit-tests runs clean in L0.
Patches for kvm-unit-tests incoming to play nice with 5-level nested EPT.

Ideally patches 1 and 2 would get into 5.6, 5-level paging is quite
broken without them.

v2:
  - Increase the nested EPT array sizes to accomodate 5-level paging in
    the patch that adds support for 5-level nested EPT, not in the bug
    fix for 5-level shadow paging.

Sean Christopherson (7):
  KVM: nVMX: Use correct root level for nested EPT shadow page tables
  KVM: x86/mmu: Fix struct guest_walker arrays for 5-level paging
  KVM: nVMX: Allow L1 to use 5-level page walks for nested EPT
  KVM: nVMX: Rename nested_ept_get_cr3() to nested_ept_get_eptp()
  KVM: nVMX: Rename EPTP validity helper and associated variables
  KVM: x86/mmu: Rename kvm_mmu->get_cr3() to ->get_guest_cr3_or_eptp()
  KVM: nVMX: Drop unnecessary check on ept caps for execute-only

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/include/asm/vmx.h      | 12 +++++++
 arch/x86/kvm/mmu/mmu.c          | 35 ++++++++++----------
 arch/x86/kvm/mmu/paging_tmpl.h  |  6 ++--
 arch/x86/kvm/svm.c              | 10 +++---
 arch/x86/kvm/vmx/nested.c       | 58 ++++++++++++++++++++-------------
 arch/x86/kvm/vmx/nested.h       |  4 +--
 arch/x86/kvm/vmx/vmx.c          |  2 ++
 arch/x86/kvm/x86.c              |  2 +-
 9 files changed, 79 insertions(+), 52 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] nVMX: 5-level nested EPT support
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Feb  7 17:42:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11370853
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9940921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:42:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C29AA21927
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 17:42:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727303AbgBGRms (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 12:42:48 -0500
Received: from mga11.intel.com ([192.55.52.93]:13003 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727154AbgBGRmr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 12:42:47 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 07 Feb 2020 09:42:47 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,414,1574150400";
   d="scan'208";a="312095672"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga001.jf.intel.com with ESMTP; 07 Feb 2020 09:42:46 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/4] nVMX: 5-level nested EPT support
Date: Fri,  7 Feb 2020 09:42:40 -0800
Message-Id: <20200207174244.6590-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for 5-level nested EPT and clean up the test for
MSR_IA32_VMX_EPT_VPID_CAP in the process.

Sean Christopherson (4):
  nVMX: Extend EPTP test to allow 5-level EPT
  nVMX: Refactor the EPT/VPID MSR cap check to make it readable
  nVMX: Mark bit 39 of MSR_IA32_VMX_EPT_VPID_CAP as reserved
  nVMX: Extend EPT cap MSR test to allow 5-level EPT

 x86/vmx.c       | 21 ++++++++++++++++++++-
 x86/vmx.h       |  4 +++-
 x86/vmx_tests.c | 12 ++++++++----
 3 files changed, 31 insertions(+), 6 deletions(-)
```
#### [RFC PATCH v7 00/78] VM introspection
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From patchwork Fri Feb  7 18:15:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11371041
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F8D21398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:18:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E66420726
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 18:18:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726988AbgBGSSt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 13:18:49 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:40530 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726900AbgBGSQl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Feb 2020 13:16:41 -0500
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 73C5130747CA;
        Fri,  7 Feb 2020 20:16:38 +0200 (EET)
Received: from host.bbu.bitdefender.biz (unknown [195.210.4.22])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 56DE03000082;
        Fri,  7 Feb 2020 20:16:38 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>, =?utf-8?q?Adalbert_L?=
	=?utf-8?q?az=C4=83r?= <alazar@bitdefender.com>,
 Jan Kiszka <jan.kiszka@siemens.com>,
 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
 Mathieu Tarral <mathieu.tarral@protonmail.com>,
 Patrick Colp <patrick.colp@oracle.com>,
 =?utf-8?q?Samuel_Laur=C3=A9n?= <samuel.lauren@iki.fi>,
 Stefan Hajnoczi <stefanha@redhat.com>, Tamas K Lengyel <tamas@tklengyel.com>,
 Weijiang Yang <weijiang.yang@intel.com>
Subject: [RFC PATCH v7 00/78] VM introspection
Date: Fri,  7 Feb 2020 20:15:18 +0200
Message-Id: <20200207181636.1065-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM introspection subsystem provides a facility for applications
running on the host or in a separate VM, to control the execution of
other VMs (pause, resume, shutdown), query the state of the vCPUs (GPRs,
MSRs etc.), alter the page access bits in the shadow page tables (only
for the hardware backed ones, eg. Intel's EPT) and receive notifications
when events of interest have taken place (shadow page table level faults,
key MSR writes, hypercalls etc.). Some notifications can be responded
to with an action (like preventing an MSR from being written), others
are mere informative (like breakpoint events which can be used for
execution tracing).  With few exceptions, all events are optional. An
application using this subsystem will explicitly register for them.

The use case that gave way for the creation of this subsystem is to
monitor the guest OS and as such the ABI/API is highly influenced by how
the guest software (kernel, applications) sees the world. For example,
some events provide information specific for the host CPU architecture
(eg. MSR_IA32_SYSENTER_EIP) merely because its leveraged by guest software
to implement a critical feature (fast system calls).

At the moment, the target audience for KVMI are security software authors
that wish to perform forensics on newly discovered threats (exploits)
or to implement another layer of security like preventing a large set
of kernel rootkits simply by "locking" the kernel image in the shadow
page tables (ie. enforce .text r-x, .rodata rw- etc.). It's the latter
case that made KVMI a separate subsystem, even though many of these
features are available in the device manager. The ability to build a
security application that does not interfere (in terms of performance)
with the guest software asks for a specialized interface that is designed
for minimum overhead.

This patch series is based on kvm/master,
commit 2f13437b8917 ("Merge tag 'trace-v5.5-2' of git://git.kernel.org/pub/scm/linux/kernel/git/rostedt/linux-trace").

The previous RFC (v6) can be read here:

	https://lore.kernel.org/kvm/20190809160047.8319-1-alazar@bitdefender.com/

Patches 1-35: make preparatory changes

Patches 36-76: add basic introspection capabilities

Patch 77: support introspection tools that write-protect guest page tables

Patch 78: notify the introspection tool even on emulation failures
          (when the read/write callbacks used by the emulator,
           kvm_page_preread/kvm_page_prewrite, are not invoked)

Changes since v6:
    - this is a subset of the previous version, as Sean and Paolo suggested,
      keeping "only" the basic introspection capabilities
    - add a x86_64 test in tools/testing/selftests/kvm [Paolo]
    - simplify the requests/replies handling [Paolo]
    - add a new ioctl (PREHOOK) to notify the introspection tool to unhook
      [Paolo, Sean]
    - add two new commands KVMI_VCPU_CONTROL_SINGLESTEP
      and KVMI_VCPU_TRANSLATE_GVA [Mathieu]
    - restore the status of MSRs, CR3, descriptors access interception
      and prevent conflicts with userspace [Sean]
    - other fixes for allmost all the issues pointed in the previous
      code review [Sean, Paolo]

Adalbert Lazăr (19):
  sched/swait: add swait_event_killable_exclusive()
  KVM: add new error codes for VM introspection
  KVM: add kvm_vcpu_kick_and_wait()
  KVM: doc: fix the hypercall numbering
  KVM: x86: add .control_cr3_intercept() to struct kvm_x86_ops
  KVM: x86: add .control_desc_intercept()
  KVM: x86: intercept the write access on sidt and other emulated
    instructions
  KVM: introspection: add hook/unhook ioctls
  KVM: introspection: add permission access ioctls
  KVM: introspection: add the read/dispatch message function
  KVM: introspection: add KVMI_GET_VERSION
  KVM: introspection: add KVMI_VM_CHECK_COMMAND and KVMI_VM_CHECK_EVENT
  KVM: introspection: add KVMI_EVENT_UNHOOK
  KVM: introspection: add KVMI_VM_CONTROL_EVENTS
  KVM: introspection: add a jobs list to every introspected vCPU
  KVM: introspection: add KVMI_VCPU_PAUSE
  KVM: introspection: add KVMI_EVENT_PAUSE_VCPU
  KVM: introspection: extend KVMI_GET_VERSION with struct kvmi_features
  KVM: introspection: add KVMI_VCPU_TRANSLATE_GVA

Marian Rotariu (1):
  KVM: introspection: add KVMI_VCPU_GET_CPUID

Mathieu Tarral (1):
  export kill_pid_info()

Mihai Donțu (34):
  KVM: x86: add kvm_arch_vcpu_get_regs() and kvm_arch_vcpu_get_sregs()
  KVM: x86: avoid injecting #PF when emulate the VMCALL instruction
  KVM: x86: add .control_msr_intercept()
  KVM: x86: vmx: use a symbolic constant when checking the exit
    qualifications
  KVM: x86: save the error code during EPT/NPF exits handling
  KVM: x86: add .fault_gla()
  KVM: x86: add .spt_fault()
  KVM: x86: add .gpt_translation_fault()
  KVM: x86: extend kvm_mmu_gva_to_gpa_system() with the 'access'
    parameter
  KVM: x86: page track: provide all page tracking hooks with the guest
    virtual address
  KVM: x86: page track: add track_create_slot() callback
  KVM: x86: page_track: add support for preread, prewrite and preexec
  KVM: x86: wire in the preread/prewrite/preexec page trackers
  KVM: introduce VM introspection
  KVM: introspection: add KVMI_VM_GET_INFO
  KVM: introspection: add KVMI_VM_READ_PHYSICAL/KVMI_VM_WRITE_PHYSICAL
  KVM: introspection: handle vCPU introspection requests
  KVM: introspection: handle vCPU commands
  KVM: introspection: add KVMI_VCPU_GET_INFO
  KVM: introspection: add KVMI_VCPU_CONTROL_EVENTS
  KVM: introspection: add KVMI_VCPU_GET_REGISTERS
  KVM: introspection: add KVMI_VCPU_SET_REGISTERS
  KVM: introspection: add KVMI_EVENT_HYPERCALL
  KVM: introspection: add KVMI_EVENT_BREAKPOINT
  KVM: introspection: add KVMI_VCPU_CONTROL_CR and KVMI_EVENT_CR
  KVM: introspection: add KVMI_VCPU_INJECT_EXCEPTION + KVMI_EVENT_TRAP
  KVM: introspection: add KVMI_EVENT_XSETBV
  KVM: introspection: add KVMI_VCPU_GET_XSAVE
  KVM: introspection: add KVMI_VCPU_GET_MTRR_TYPE
  KVM: introspection: add KVMI_VCPU_CONTROL_MSR and KVMI_EVENT_MSR
  KVM: introspection: add KVMI_VM_SET_PAGE_ACCESS
  KVM: introspection: add KVMI_EVENT_PF
  KVM: introspection: emulate a guest page table walk on SPT violations
    due to A/D bit updates
  KVM: x86: call the page tracking code on emulation failure

Mircea Cîrjaliu (2):
  KVM: x86: disable gpa_available optimization for fetch and page-walk
    NPF/EPT violations
  KVM: introspection: add vCPU related data

Nicușor Cîțu (19):
  KVM: x86: add kvm_arch_vcpu_set_regs()
  KVM: x86: add .bp_intercepted() to struct kvm_x86_ops
  KVM: x86: add .cr3_write_intercepted()
  KVM: x86: add .desc_intercepted()
  KVM: x86: export .msr_write_intercepted()
  KVM: x86: use MSR_TYPE_R, MSR_TYPE_W and MSR_TYPE_RW with AMD code too
  KVM: svm: pass struct kvm_vcpu to set_msr_interception()
  KVM: vmx: pass struct kvm_vcpu to the intercept msr related functions
  KVM: x86: add .control_singlestep()
  KVM: x86: export kvm_arch_vcpu_set_guest_debug()
  KVM: x86: export kvm_inject_pending_exception()
  KVM: x86: export kvm_vcpu_ioctl_x86_get_xsave()
  KVM: introspection: restore the state of #BP interception on unhook
  KVM: introspection: restore the state of CR3 interception on unhook
  KVM: introspection: add KVMI_EVENT_DESCRIPTOR
  KVM: introspection: restore the state of descriptor interception on
    unhook
  KVM: introspection: restore the state of MSR interception on unhook
  KVM: introspection: add KVMI_VCPU_CONTROL_SINGLESTEP
  KVM: introspection: add KVMI_EVENT_SINGLESTEP

Ștefan Șicleru (2):
  KVM: add kvm_get_max_gfn()
  KVM: introspection: add KVMI_VM_GET_MAX_GFN

 Documentation/virt/kvm/api.txt                |  115 +
 Documentation/virt/kvm/hypercalls.txt         |   36 +-
 Documentation/virt/kvm/kvmi.rst               | 1413 +++++++++++++
 arch/x86/include/asm/kvm_emulate.h            |    1 +
 arch/x86/include/asm/kvm_host.h               |   36 +-
 arch/x86/include/asm/kvm_page_track.h         |   71 +-
 arch/x86/include/asm/kvmi_host.h              |   91 +
 arch/x86/include/asm/vmx.h                    |    2 +
 arch/x86/include/uapi/asm/kvmi.h              |  147 ++
 arch/x86/kvm/Kconfig                          |    9 +
 arch/x86/kvm/Makefile                         |    2 +
 arch/x86/kvm/emulate.c                        |    4 +
 arch/x86/kvm/kvmi.c                           | 1168 +++++++++++
 arch/x86/kvm/mmu.h                            |    4 +
 arch/x86/kvm/mmu/mmu.c                        |  160 +-
 arch/x86/kvm/mmu/page_track.c                 |  142 +-
 arch/x86/kvm/svm.c                            |  272 ++-
 arch/x86/kvm/vmx/vmx.c                        |  265 ++-
 arch/x86/kvm/vmx/vmx.h                        |    4 -
 arch/x86/kvm/x86.c                            |  296 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |    2 +-
 include/linux/kvm_host.h                      |   18 +
 include/linux/kvmi_host.h                     |  126 ++
 include/linux/swait.h                         |   11 +
 include/uapi/linux/kvm.h                      |   20 +
 include/uapi/linux/kvm_para.h                 |    5 +
 include/uapi/linux/kvmi.h                     |  217 ++
 kernel/signal.c                               |    1 +
 tools/testing/selftests/kvm/Makefile          |    1 +
 .../testing/selftests/kvm/x86_64/kvmi_test.c  | 1864 +++++++++++++++++
 virt/kvm/introspection/kvmi.c                 | 1408 +++++++++++++
 virt/kvm/introspection/kvmi_int.h             |  178 ++
 virt/kvm/introspection/kvmi_msg.c             | 1149 ++++++++++
 virt/kvm/kvm_main.c                           |   69 +
 34 files changed, 9132 insertions(+), 175 deletions(-)
 create mode 100644 Documentation/virt/kvm/kvmi.rst
 create mode 100644 arch/x86/include/asm/kvmi_host.h
 create mode 100644 arch/x86/include/uapi/asm/kvmi.h
 create mode 100644 arch/x86/kvm/kvmi.c
 create mode 100644 include/linux/kvmi_host.h
 create mode 100644 include/uapi/linux/kvmi.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvmi_test.c
 create mode 100644 virt/kvm/introspection/kvmi.c
 create mode 100644 virt/kvm/introspection/kvmi_int.h
 create mode 100644 virt/kvm/introspection/kvmi_msg.c


base-commit: 2f13437b8917627119d163d62f73e7a78a92303a
CC: Jan Kiszka <jan.kiszka@siemens.com>
CC: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
CC: Mathieu Tarral <mathieu.tarral@protonmail.com>
CC: Patrick Colp <patrick.colp@oracle.com>
CC: Samuel Laurén <samuel.lauren@iki.fi>
CC: Stefan Hajnoczi <stefanha@redhat.com>
CC: Tamas K Lengyel <tamas@tklengyel.com>
CC: Weijiang Yang <weijiang.yang@intel.com>
```
#### [PATCH v12 Kernel 0/7] KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Fri Feb  7 19:42:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11371101
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CEA9138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 20:16:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4184D20715
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 20:16:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="DRKxYNW2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727114AbgBGUQW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 15:16:22 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:17944 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726916AbgBGUQW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 15:16:22 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e3dc5780001>; Fri, 07 Feb 2020 12:15:52 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Fri, 07 Feb 2020 12:16:17 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Fri, 07 Feb 2020 12:16:17 -0800
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 7 Feb
 2020 20:16:17 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 7 Feb 2020 20:16:10 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v12 Kernel 0/7] KABIs to support migration for VFIO devices
Date: Sat, 8 Feb 2020 01:12:27 +0530
Message-ID: <1581104554-10704-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1581106552; bh=ozjH+tKAAJmnPnuzUL56QveBzh7MYBg6k3KzjCa9NPA=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=DRKxYNW2DQ/3gQRCVMhlxLxUiluFQJeD/E8zG+E5HHaWAhlSsLnVdITYPCepR0Wiq
         XF8USsCP/dLFMPsuSnFgXzsLT43BwdROqJhteoPHW27s0ttuBcx4y/Iy1LVK8COZA3
         OotK2nA1LN12DeIxMwoP35UnRRMzqDMAJS1lNCQIDyMp/DSTMYCO0hikZnMgUTPrln
         Hw0Mvnbtp2N1wkNr/B1IL2pOsS5Om+f2/dqi1ozKlDMb89fHx5QEjjlb1N1bpEzARh
         asMbTt+yj+kcSzhb4qIZDjVcoc4P4mpmw5q6mLGYrvzeMcjn/dM8Kei8CiciDFrte3
         0J7cVLlhunIWQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* New IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 7 is proposed change to detect if IOMMU capable device driver is
  smart to report pages to be marked dirty by pinning pages using
  vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti


Kirti Wankhede (7):
  vfio: KABI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Add ioctl definition for dirty pages tracking.
  vfio iommu: Implementation of ioctl to for dirty pages tracking.
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Adds flag to indicate dirty pages tracking capability
    support
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 435 +++++++++++++++++++++++++++++++++++++---
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 267 +++++++++++++++++++++++-
 4 files changed, 692 insertions(+), 27 deletions(-)
```
#### [PATCH RFC 0/4] KVM: MIPS: Provide arch-specific
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Feb  7 22:35:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11371337
Return-Path: <SRS0=xIo7=33=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17E111398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 22:35:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB38622522
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Feb 2020 22:35:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AOc/2Uws"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727347AbgBGWf2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Feb 2020 17:35:28 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:43828 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727068AbgBGWf1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Feb 2020 17:35:27 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581114926;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ugZBz7enuCINLO2hCs0M9spDUSXUeBZ8X9fYPkjTl9M=;
        b=AOc/2UwsgyWFumXlcUmRsQ8YnXeZxd8AmFdKV20GYopInCVNjKV1YsFzGsH1Kx/lNK5pSc
        69wzGCdve9owXwCsTPAjVeWdhLMjpunhhA6XYWQCfP2TnUH5afAWHF1N1uGAuOuctBVKHP
        ZpOCyyrQ9WJlM8pyFN9HjuqbTTwTSMM=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-194-1Pfh9b79OpSJjTvqcPBcPg-1; Fri, 07 Feb 2020 17:35:24 -0500
X-MC-Unique: 1Pfh9b79OpSJjTvqcPBcPg-1
Received: by mail-qt1-f199.google.com with SMTP id e8so538349qtg.9
        for <kvm@vger.kernel.org>; Fri, 07 Feb 2020 14:35:24 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ugZBz7enuCINLO2hCs0M9spDUSXUeBZ8X9fYPkjTl9M=;
        b=QO5jZhtmrZmO/PRE8SoEddwV9vqX1m+sFR6JmulP/9hmboZTPXbxf5TiI/bVepW+7v
         X4yASW9vvd8VzutOnRwEmiPpWeUYWo1Me4Ih9qOD+Z5cJ5SbOD+N2vFDd05PpVNwvP2M
         dK95KwGw0ffwV+5CQbAUddZbBVPL5e5qgscDS/p5nBLyOgH1f6eFusLVs4e2xvx1rnXS
         58bM8/HnWcmhX1Kh3PraYeFZ7w3TTQECR8BKw+BL88P071BLXR/DtIlkLXDEn0KG5c5f
         3YBSNNgctbJoOtRTUm8NVs017J3md2SSmbbpo4q+q3Lcmr4hlouO0YJvqelnEAp8phBT
         trDw==
X-Gm-Message-State: APjAAAXIHQ+CoYi7lwgd7iorFPNT26vaA0MiyJ/1folqaYBzrRu8rSOJ
        RLA55TRLQPlFy/EwLe9sRMVsNgMS+CY7HWNhfGUiAHlUazp8yX5XiUuHj9cb6Zqw+mF2Ak4n8oq
        ucQEzj2jkVqwr
X-Received: by 2002:ac8:1205:: with SMTP id x5mr598702qti.238.1581114923526;
        Fri, 07 Feb 2020 14:35:23 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzFhVS1bhbCdouqP3dIqYiC7xAeG36OuHcbu/fkXUSHwKqa8FFEiGxaaY0/f//YMJs09H18pw==
X-Received: by 2002:ac8:1205:: with SMTP id x5mr598684qti.238.1581114923289;
        Fri, 07 Feb 2020 14:35:23 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c8:32::2])
        by smtp.gmail.com with ESMTPSA id
 u12sm2178736qtj.84.2020.02.07.14.35.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 07 Feb 2020 14:35:22 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-mips@vger.kernel.org, peterx@redhat.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RFC 0/4] KVM: MIPS: Provide arch-specific
 kvm_flush_remote_tlbs()
Date: Fri,  7 Feb 2020 17:35:16 -0500
Message-Id: <20200207223520.735523-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[This series is RFC because I don't have MIPS to compile and test]

kvm_flush_remote_tlbs() can be arch-specific, by either:

- Completely replace kvm_flush_remote_tlbs(), like ARM, who is the
  only user of CONFIG_HAVE_KVM_ARCH_TLB_FLUSH_ALL so far

- Doing something extra before kvm_flush_remote_tlbs(), like MIPS VZ
  support, however still wants to have the common tlb flush to be part
  of the process.  Could refer to kvm_vz_flush_shadow_all().  Then in
  MIPS it's awkward to flush remote TLBs: we'll need to call the mips
  hooks.

It's awkward to have different ways to specialize this procedure,
especially MIPS cannot use the genenal interface which is quite a
pity.  It's good to make it a common interface.

This patch series removes the 2nd MIPS usage above, and let it also
use the common kvm_flush_remote_tlbs() interface.  It should be
suggested that we always keep kvm_flush_remote_tlbs() be a common
entrance for tlb flushing on all archs.

This idea comes from the reading of Sean's patchset on dynamic memslot
allocation, where a new dirty log specific hook is added for flushing
TLBs only for the MIPS code [1].  With this patchset, logically the
new hook in that patch can be dropped so we can directly use
kvm_flush_remote_tlbs().

TODO: We can even extend another common interface for ranged TLB, but
let's see how we think about this series first.

Any comment is welcomed, thanks.

Peter Xu (4):
  KVM: Provide kvm_flush_remote_tlbs_common()
  KVM: MIPS: Drop flush_shadow_memslot() callback
  KVM: MIPS: Replace all the kvm_flush_remote_tlbs() references
  KVM: MIPS: Define arch-specific kvm_flush_remote_tlbs()

 arch/mips/include/asm/kvm_host.h |  7 -------
 arch/mips/kvm/Kconfig            |  1 +
 arch/mips/kvm/mips.c             | 22 ++++++++++------------
 arch/mips/kvm/trap_emul.c        | 15 +--------------
 arch/mips/kvm/vz.c               | 14 ++------------
 include/linux/kvm_host.h         |  1 +
 virt/kvm/kvm_main.c              | 10 ++++++++--
 7 files changed, 23 insertions(+), 47 deletions(-)
```
