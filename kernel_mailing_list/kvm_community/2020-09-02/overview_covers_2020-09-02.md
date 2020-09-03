

#### [PATCH v6 0/7] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Wed Sep  2 12:59:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11750531
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70FAB138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 12:59:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50CCC20709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 12:59:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="sLBt0oo8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726726AbgIBM7y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 08:59:54 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:24278 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726124AbgIBM7v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 2 Sep 2020 08:59:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599051590; x=1630587590;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=ICDE6RfR+JH0kcoy+iWotRzmn0cioWZdR6Llakzqiz8=;
  b=sLBt0oo8A1CcTO7SjlIdeuoranP/re6rFKisLOXWU1btF1t8KhPwTkjH
   3jemwKRh4HFA/2Nj3ANeGQsVBdWxd33Cdv6+//2Nmemmiukbkct+q3zog
   e9urpvADwsHqVsdi3o5jyQMgeRctjxIxSqHiz6pFi9/IdHnqir3ad4XG2
   w=;
X-IronPort-AV: E=Sophos;i="5.76,383,1592870400";
   d="scan'208";a="51551893"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2c-c6afef2e.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 02 Sep 2020 12:59:48 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2c-c6afef2e.us-west-2.amazon.com (Postfix) with
 ESMTPS id 141F6A22A4;
        Wed,  2 Sep 2020 12:59:47 +0000 (UTC)
Received: from EX13D20UWC002.ant.amazon.com (10.43.162.163) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 2 Sep 2020 12:59:46 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.145) by
 EX13D20UWC002.ant.amazon.com (10.43.162.163) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 2 Sep 2020 12:59:42 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <kvm@vger.kernel.org>, <linux-doc@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH v6 0/7] Allow user space to restrict and augment MSR emulation
Date: Wed, 2 Sep 2020 14:59:28 +0200
Message-ID: <20200902125935.20646-1-graf@amazon.com>
X-Mailer: git-send-email 2.28.0.394.ge197136389
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D08UWB004.ant.amazon.com (10.43.161.232) To
 EX13D20UWC002.ant.amazon.com (10.43.162.163)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with filtering, user space trapping allows us to emulate
arbitrary MSRs in user space, paving the way for target CPU specific MSR
implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

v3 -> v4:

  - Mention exit reasons in re-enter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
  - lock allow check and clearing
  - free bitmaps on clear

v4 -> v5:

  - use srcu 

v5 -> v6:

  - Switch from allow list to filtering API with explicit fallback option
  - Support and test passthrough MSR filtering
  - Check for filter exit reason
  - Add .gitignore
  - send filter change notification
  - change to atomic set_msr_filter ioctl with fallback flag
  - use EPERM for filter blocks
  - add bit for MSR user space deflection
  - check for overflow of BITS_TO_LONGS (thanks Dan Carpenter!)
  - s/int i;/u32 i;/
  - remove overlap check
  - Introduce exit reason mask to allow for future expansion and filtering
  - s/emul_to_vcpu(ctxt)/vcpu/
  - imported patch: KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs
  - new patch: KVM: x86: Add infrastructure for MSR filtering
  - new patch: KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  - new patch: KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied

Aaron Lewis (1):
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs

Alexander Graf (6):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Add infrastructure for MSR filtering
  KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied
  KVM: x86: Introduce MSR filtering
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 176 +++++++++-
 arch/x86/include/asm/kvm_host.h               |  18 ++
 arch/x86/include/uapi/asm/kvm.h               |  19 ++
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/svm/svm.c                        | 122 +++++--
 arch/x86/kvm/svm/svm.h                        |   7 +
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        | 303 ++++++++++++------
 arch/x86/kvm/vmx/vmx.h                        |   9 +-
 arch/x86/kvm/x86.c                            | 268 +++++++++++++++-
 arch/x86/kvm/x86.h                            |   1 +
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 224 +++++++++++++
 16 files changed, 1056 insertions(+), 132 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
#### [PATCH v4 0/3] vfio/pci: Restore MMIO access for s390 detached VFs
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Wed Sep  2 19:46:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11751697
Return-Path: <SRS0=tgfV=CL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9963A109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 19:47:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C3D620773
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  2 Sep 2020 19:47:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="UGLT4W2a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726794AbgIBTrG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 2 Sep 2020 15:47:06 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10742 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726594AbgIBTq5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 2 Sep 2020 15:46:57 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 082JhIX4136003;
        Wed, 2 Sep 2020 15:46:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=OwSxU4NAP7jStdtuTC+FUhSDcDea3J45JeuxRMcK9oM=;
 b=UGLT4W2aihJmJS5eEAlBU8lJHcgRkZbJ5A5XQwEn+Jg7YHZBlrQuO2Hh6aNcL806eB+b
 2Hc17+uHeSFnOTHZfde9MPcyeeQZ5wEPFXZ63w2//jJM4qWDdA4nFji0LQFgmWpbRIit
 6SziDRAe8KVPqIb4C+Wckx9PLlF+6E5OAkoqC8kloeq7CZzJaqhQONUJX3bVNAi7dhSa
 8hzLEizZBaxZFQkf0uh6J+nnYzBn07cAj4N840K1Eh8bIVD7T1z+riO+qXK9nwA/+X6T
 s8iPzp0/SnQB4lgN8cwP5Qd7bdlJqjYRmOxWuOkgSKu/SVC48sFVHERlOT6iLWnjomri GA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ahswg3fr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 15:46:45 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 082Jhe7L136478;
        Wed, 2 Sep 2020 15:46:44 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ahswg3fd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 15:46:44 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 082JfMA8012026;
        Wed, 2 Sep 2020 19:46:43 GMT
Received: from b01cxnp22034.gho.pok.ibm.com (b01cxnp22034.gho.pok.ibm.com
 [9.57.198.24])
        by ppma01wdc.us.ibm.com with ESMTP id 337en9aejg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 02 Sep 2020 19:46:43 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 082JkhQn42336556
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 2 Sep 2020 19:46:43 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3E34F2805C;
        Wed,  2 Sep 2020 19:46:43 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 95BCC2805A;
        Wed,  2 Sep 2020 19:46:40 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.10.164])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  2 Sep 2020 19:46:40 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, cohuck@redhat.com, kevin.tian@intel.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-pci@vger.kernel.org
Subject: [PATCH v4 0/3] vfio/pci: Restore MMIO access for s390 detached VFs
Date: Wed,  2 Sep 2020 15:46:33 -0400
Message-Id: <1599075996-9826-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-02_14:2020-09-02,2020-09-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 adultscore=0
 phishscore=0 bulkscore=0 suspectscore=0 malwarescore=0 mlxlogscore=845
 mlxscore=0 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009020178
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit abafbc551fdd ("vfio-pci: Invalidate mmaps and block MMIO
access on disabled memory") VFIO now rejects guest MMIO access when the
PCI_COMMAND_MEMORY (MSE) bit is OFF.  This is however not the case for
VFs (fixed in commit ebfa440ce38b ("vfio/pci: Fix SR-IOV VF handling
with MMIO blocking")).  Furthermore, on s390 where we always run with at
least a bare-metal hypervisor (LPAR) PCI_COMMAND_MEMORY, unlike Device/
Vendor IDs and BARs, is not emulated when VFs are passed-through to the
OS independently.

Based upon Bjorn's most recent comment [1], I investigated the notion of
setting is_virtfn=1 for VFs passed-through to Linux and not linked to a
parent PF (referred to as a 'detached VF' in my prior post).  However,
we rapidly run into issues on how to treat an is_virtfn device with no
linked PF. Further complicating the issue is when you consider the guest
kernel has a passed-through VF but has CONFIG_PCI_IOV=n as in many 
locations is_virtfn checking is ifdef'd out altogether and the device is
assumed to be an independent PCI function.

The decision made by VFIO whether to require or emulate a PCI feature 
(in this case PCI_COMMAND_MEMORY) is based upon the knowledge it has 
about the device, including implicit expectations of what/is not
emulated below VFIO. (ex: is it safe to read vendor/id from config
space?) -- Our firmware layer attempts similar behavior by emulating
things such as vendor/id/BAR access - without these an unlinked VF would
not be usable. But what is or is not emulated by the layer below may be
different based upon which entity is providing the emulation (vfio,
LPAR, some other hypervisor)

So, the proposal here aims to fix the immediate issue of s390
pass-through VFs becoming suddenly unusable by vfio by using a dev_flags
bit to identify a VF feature that we know is hardwired to 0 for any
VF (PCI_COMMAND_MEMORY) and de-coupling the need for emulating
PCI_COMMAND_MEMORY from the is_virtfn flag. The exact scope of is_virtfn
and physfn for bare-metal vs guest scenarios and identifying what
features are / are not emulated by the lower-level hypervisors is a much
bigger discussion independent of this limited proposal.

Changes from v3:
- Propose a dev_flags model for the MSE bit
- Set the bit for typical iov linking
- Also set the bit for s390 VFs (linked and unlinked)
- Modify vfio-pci to look at the dev_flags bit instead of is_virtfn

[1]: https://marc.info/?l=linux-pci&m=159856041930022&w=2

Matthew Rosato (3):
  PCI/IOV: Mark VFs as not implementing MSE bit
  s390/pci: Mark all VFs as not implementing MSE bit
  vfio/pci: Decouple MSE bit checks from is_virtfn

 arch/s390/pci/pci_bus.c            |  5 +++--
 drivers/pci/iov.c                  |  1 +
 drivers/vfio/pci/vfio_pci_config.c | 20 +++++++++++++-------
 include/linux/pci.h                |  2 ++
 4 files changed, 19 insertions(+), 9 deletions(-)
```
