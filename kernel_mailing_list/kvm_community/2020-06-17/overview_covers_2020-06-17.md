

#### [PATCH v3 0/1] s390: virtio: let arch choose to accept devices
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Wed Jun 17 10:43:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11609647
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABC4614DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 10:44:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DDBC20FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 10:44:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726858AbgFQKoN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 06:44:13 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:11084 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726270AbgFQKoM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Jun 2020 06:44:12 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05HAY1sx006314;
        Wed, 17 Jun 2020 06:44:05 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q6j3hjdr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 06:44:05 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05HAYdrw008682;
        Wed, 17 Jun 2020 06:44:04 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q6j3hjcq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 06:44:04 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05HAZkY4002574;
        Wed, 17 Jun 2020 10:44:02 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 31q6ch8v48-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 10:44:02 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05HAhxAv47448264
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 17 Jun 2020 10:43:59 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 57E9D52051;
        Wed, 17 Jun 2020 10:43:59 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.186.32])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 78A9E5204E;
        Wed, 17 Jun 2020 10:43:58 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v3 0/1] s390: virtio: let arch choose to accept devices
 without IOMMU feature
Date: Wed, 17 Jun 2020 12:43:56 +0200
Message-Id: <1592390637-17441-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-17_03:2020-06-17,2020-06-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 phishscore=0 clxscore=1015 cotscore=-2147483648
 suspectscore=1 spamscore=0 mlxscore=0 priorityscore=1501 bulkscore=0
 mlxlogscore=577 adultscore=0 impostorscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006170083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture protecting the guest memory against unauthorized host
access may want to enforce VIRTIO I/O device protection through the
use of VIRTIO_F_IOMMU_PLATFORM.

Let's give a chance to the architecture to accept or not devices
without VIRTIO_F_IOMMU_PLATFORM.

Pierre Morel (1):
  s390: virtio: let arch accept devices without IOMMU feature

 arch/s390/mm/init.c     |  6 ++++++
 drivers/virtio/virtio.c | 22 ++++++++++++++++++++++
 include/linux/virtio.h  |  2 ++
 3 files changed, 30 insertions(+)
```
#### [PATCH 0/4] Paravirtualized Control Register pinning
##### From: John Andersen <john.s.andersen@intel.com>

```c
From patchwork Wed Jun 17 19:07:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11610465
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0080392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 19:08:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC50F2075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 19:08:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727006AbgFQTII (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 15:08:08 -0400
Received: from mga04.intel.com ([192.55.52.120]:48955 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726496AbgFQTIH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 15:08:07 -0400
IronPort-SDR: 
 GXAD86Y+v0sAZ7jjCoGmhuL8BUfr1j6pluGgzU4R9vqHj7R/YWI1hhy/F7olgkkf0YqS2oMViU
 Z5Wc2qnZ0GdA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jun 2020 12:05:05 -0700
IronPort-SDR: 
 f4PG7rOzUp9wJxnaGIS99b7kAedDAFG1mwUMnkZiMuYr+yJgZN+GU8YukTeTJ/vMUngKvmiene
 3v5dNH4Wg0Qg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,523,1583222400";
   d="scan'208";a="273609545"
Received: from gza.jf.intel.com ([10.54.75.28])
  by orsmga003.jf.intel.com with ESMTP; 17 Jun 2020 12:05:04 -0700
From: John Andersen <john.s.andersen@intel.com>
To: corbet@lwn.net, pbonzini@redhat.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        shuah@kernel.org, sean.j.christopherson@intel.com,
        liran.alon@oracle.com, drjones@redhat.com,
        rick.p.edgecombe@intel.com, kristen@linux.intel.com
Cc: vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, mchehab+huawei@kernel.org,
        gregkh@linuxfoundation.org, paulmck@kernel.org,
        pawan.kumar.gupta@linux.intel.com, jgross@suse.com,
        mike.kravetz@oracle.com, oneukum@suse.com, luto@kernel.org,
        peterz@infradead.org, fenghua.yu@intel.com,
        reinette.chatre@intel.com, vineela.tummalapalli@intel.com,
        dave.hansen@linux.intel.com, john.s.andersen@intel.com,
        arjan@linux.intel.com, caoj.fnst@cn.fujitsu.com, bhe@redhat.com,
        nivedita@alum.mit.edu, keescook@chromium.org,
        dan.j.williams@intel.com, eric.auger@redhat.com,
        aaronlewis@google.com, peterx@redhat.com,
        makarandsonare@google.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org,
        kernel-hardening@lists.openwall.com
Subject: [PATCH 0/4] Paravirtualized Control Register pinning
Date: Wed, 17 Jun 2020 12:07:53 -0700
Message-Id: <20200617190757.27081-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The paravirtualized CR pinning patchset is a strengthened version of
existing control registers pinning for paravritualized guests. It
protects KVM guests from ROP based attacks which attempt to disable key
security features. Virtualized Linux guests such as Kata Containers, AWS
Lambda, and Chromos Termina will get this protection enabled by default
when they update their kernel / configs. Using virtualization allows us
to provide a stronger version of a proven exploit mitigation technique.

We’ve patched KVM to create 6 new KVM specific MSRs used to query which
bits may be pinned, and to set which bits are pinned high or low in
control registers 0 and 4. Linux guest support was added so that
non-kexec guests will be able to take advantage of this strengthened
protection by default. A plan for enabling guests with kexec is proposed
in this cover letter. As part of that plan, we add a command line flag
that allows users to opt-in to the protection on boot if they have kexec
built into their kernel, effectively opting out of kexec support.
Hibernation and suspend to ram were enabled by updating the location
where bits in control register 4 were saved to and restored from. The
work also includes minor patches for QEMU to ensure reboot works by
clearing the added MSRs and exposing the new CPUID feature bit. There is
one SMM related selftest added in this patchset and another patch for
kvm-unit-tests that will be sent separately.

Thank you to Sean and Drew who reviewed v2, to Boris, Paolo, Andy, and
Liran who reviewed v1, and to Sean, Dave, Kristen, and Rick who've
provided feedback throughout. I appreciate your time spent reviewing and
feedback.

Here are the previous RFC versions of this patchset for reference

RFC v2: https://lkml.org/lkml/2020/2/18/1162
RFC v1: https://lkml.org/lkml/2019/12/24/380



=== High level overview of the changes ===

- A CPUID feature bit as well as MSRs were added to KVM. Guests can use
  the CPUID feature bit to determine if MSRs are available. Reading the
  first 2 MSRs returns the bits which may be pinned for CR0/4
  respectively. The next 4 MSRs are writeable and allow the guest and
  host userspace to set which bits are pinned low or pinned high for
  CR0/4.

- Hibernation and suspend-to-RAM are supported. This was done by
  updating mmu_cr4_features on feature identification of the boot CPU.
  As such, mmu_cr4_features is no longer read only after init.

- CPU hotplug is supported. Pinning is per vCPU. When running as a guest
  pinning is requested after CPU identification for non-boot CPUs. The
  boot CPU requests pinning a directly after existing pinning is setup.

- Nested virtualization is supported. SVM / VMX restore pinned bits on
  VM-Exit if they had been unset in the host VMCB / VMCS.

- As suggested by Sean, unpinning of pinned bits on return from SMM due
  to modification of SMRAM will cause an unhandleable emulation fault
  resulting in termination of the guest.

- kexec support is still pending, since the plan is a bit long it's been
  moved to the end of the cover letter. It talks about the decision to
  make a command line parameter, why we opt in to pinning (and
  effectively out of kexec). Being that those changes wouldn't be
  localized to KVM (and this patchset is on top of kvm/next).

- As Paolo requested, a patch will be sent immediately following this
  patchset for kvm-unit-tests with the unit tests for general
  functionality. selftests are included for SMM specific functionality.



=== Chanages since RFCv2 ===

- Related to Drew's comments

  - Used linux/stringify.h in selftests

  - Added comments on why we don't use GUEST_* due to SMM trickiness.
    We opt not to use GUEST_SYNC() because we also have to make a sync call
    from SMM. As such, the address of the ucall struct we'd need to pass isn't
    something we can put into the machine code in a maintainable way. At least
    so far as I could tell.

- Related to Sean's comments

  - Allowed pinning bits high or low rather than just high

  - Cleaner code path for guest and host when writing to MSRs

    - Didn't use read modify write behavior due to that requiring changes to
      selftest save restore code which made me suspect that there might be
      issues with other VMMs. The issue was because we read CR0/4 in the RWM
      operation on the MSR, we must do KVM_SET_REGS before KVM_SET_MSRS, we also
      had to call KVM_SET_SREGS and add checks for if we're in SMM or not. This
      made it a bit more messy overall so I went with the first approach Sean
      suggested where we just have pin high/low semantics.

  - If the guest writes values to the allowed MSRs that are not the correct
    value the wrmsr fails.

  - If SMRAM modification would result in unpinning bits we bail with
    X86EMUL_UNHANDLEABLE

  - Added silent restoration of pinned bits for SVM and VMX when they may have
    been modified in VMCB / VMCS. This didn't seem like a place were we'd want
    to inject a fault, please let me know if we should.



=== Description of changes and rational ===

Paravirtualized Control Register pinning is a strengthened version of
existing protections on the Write Protect, Supervisor Mode Execution /
Access Protection, and User-Mode Instruction Prevention bits. The
existing protections prevent native_write_cr*() functions from writing
values which disable those bits. This patchset prevents any guest
writes to control registers from disabling pinned bits, not just writes
from native_write_cr*(). This stops attackers within the guest from
using ROP to disable protection bits.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

The protection is implemented by adding MSRs to KVM which contain the
bits that are allowed to be pinned, and the bits which are pinned. The
guest or userspace can enable bit pinning by reading MSRs to check
which bits are allowed to be pinned, and then writing MSRs to set which
bits they want pinned.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

We add a CR pin feature bit to the KVM cpuid, read only MSRs which
guests use to identify which bits they may request be pinned, and CR
pinned low/high MSRs which contain the pinned bits. Guests can request
that KVM pin bits within control register 0 or 4 via the CR pinned MSRs.
Writes to the MSRs fail if they include bits that aren't allowed to be
pinned. Host userspace may clear or modify pinned bits at any time. Once
pinned bits are set, the guest may pin more allowed bits, but may never
clear pinned bits.

In the event that the guest vCPU attempts to disable any of the pinned
bits, the vCPU that issued the write is sent a general protection
fault, and the register is left unchanged.

When running with KVM guest support and paravirtualized CR pinning
enabled, paravirtualized and existing pinning are setup at the same
point on the boot CPU. Non-boot CPUs setup pinning upon identification.

Pinning is not active when running in SMM. Entering SMM disables pinned
bits. Writes to control registers within SMM would therefore trigger
general protection faults if pinning was enforced. Upon exit from SMM,
SMRAM is modified to ensure the values of CR0/4 that will be restored
contain the correct values for pinned bits. CR0/4 values are then
restored from SMRAM as usual.

When running with nested virtualization, should pinned bits be cleared
from host VMCS / VMCB, on VM-Exit, they will be silently restored.

Should userspace expose the CR pining CPUID feature bit, it must zero
CR pinned MSRs on reboot. If it does not, it runs the risk of having
the guest enable pinning and subsequently cause general protection
faults on next boot due to early boot code setting control registers to
values which do not contain the pinned bits.

Hibernation to disk and suspend-to-RAM are supported. identify_cpu was
updated to ensure SMEP/SMAP/UMIP are present in mmu_cr4_features. This
is necessary to ensure protections stay active during hibernation image
restoration.

Guests using the kexec system call currently do not support
paravirtualized control register pinning. This is due to early boot
code writing known good values to control registers, these values do
not contain the protected bits. This is due to CPU feature
identification being done at a later time, when the kernel properly
checks if it can enable protections. As such, the pv_cr_pin command
line option has been added which instructs the kernel to disable kexec
in favor of enabling paravirtualized control register pinning.
crashkernel is also disabled when the pv_cr_pin parameter is specified
due to its reliance on kexec.

When we make kexec compatible, we will still need a way for a kernel
with support to know if the kernel it is attempting to load has
support. If a kernel with this enabled attempts to kexec a kernel where
this is not supported, it would trigger a fault almost immediately.

Liran suggested adding a section to the built image acting as a flag to
signify support for being kexec'd by a kernel with pinning enabled.
Should that approach be implemented, it is likely that the command line
flag (pv_cr_pin) would still be desired for some deprecation period. We
wouldn't want the default behavior to change from being able to kexec
older kernels to not being able to, as this might break some users
workflows. Since we require that the user opt-in to break kexec we've
held off on attempting to fix kexec in this patchset. This way no one
sees any behavior they are not explicitly opting in to.

Security conscious kernel configurations disable kexec already, per
KSPP guidelines. Projects such as Kata Containers, AWS Lambda, ChromeOS
Termina, and others using KVM to virtualize Linux will benefit from
this protection without the need to specify pv_cr_pin on the command
line.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction. Guests running with paravirtualized CR pinning are now
protected against the use of ROP to disable CR bits. The same bits that
are being pinned natively may be pinned via the CR pinned MSRs. These
bits are WP in CR0, and SMEP, SMAP, and UMIP in CR4.

Future patches could implement similar MSRs to protect bits in MSRs.
The NXE bit of the EFER MSR is a prime candidate.



=== Plan for kexec support ===

Andy's suggestion of a boot option has been incorporated as the
pv_cr_pin command line option. Boris mentioned that short-term
solutions become immutable. However, for the reasons outlined below
we need a way for the user to opt-in to pinning over kexec if both
are compiled in, and the command line parameter seems to be a good
way to do that. Liran's proposed solution of a flag within the ELF
would allow us to identify which kernels have support is assumed to
be implemented in the following scenarios.

We then have the following cases (without the addition of pv_cr_pin):


- Kernel running without pinning enabled kexecs kernel with pinning.

  - Loaded kernel has kexec

    - Do not enable pinning

  - Loaded kernel lacks kexec

    - Enable pinning

- Kernel running with pinning enabled kexecs kernel with pinning (as
  identified by ELF addition).

  - Okay

- Kernel running with pinning enabled kexecs kernel without pinning
  (as identified by lack of ELF addition).

  - User is presented with an error saying that they may not kexec
    a kernel without pinning support.


With the addition of pv_cr_pin we have the following situations:


- Kernel running without pinning enabled kexecs kernel with pinning.

  - Loaded kernel has kexec

    - pv_cr_pin command line parameter present for new kernel

      - Enable pinning

    - pv_cr_pin command line parameter not present for new kernel

      - Do not enable pinning

  - Loaded kernel lacks kexec

    - Enable pinning

- Kernel running with pinning enabled kexecs kernel with pinning (as
  identified by ELF addition).

  - Okay

- Kernel running with kexec and pinning enabled (opt-in via pv_cr_pin)
  kexecs kernel without pinning (as identified by lack of ELF addition).

  - User is presented with an error saying that they have opted
    into pinning support and may not kexec a kernel without pinning
    support.


Without the command line parameter I'm not sure how we could preserve
users workflows which might rely on kexecing older kernels (ones
which wouldn't have support). I see the benefit here being that users
have to opt-in to the possibility of breaking their workflow, via
their addition of the pv_cr_pin command line flag. Which could of
course also be called nokexec. A deprecation period could then be
chosen where eventually pinning takes preference over kexec and users
are presented with the error if they try to kexec an older kernel.
Input on this would be much appreciated, as well as if this is the
best way to handle things or if there's another way that would be
preferred. This is just what we were able to come up with to ensure
users didn't get anything broken they didn't agree to have broken.


Thanks,
John

John Andersen (4):
  X86: Update mmu_cr4_features during feature identification
  KVM: x86: Introduce paravirt feature CR0/CR4 pinning
  selftests: kvm: add test for CR pinning with SMM
  X86: Use KVM CR pin MSRs

 .../admin-guide/kernel-parameters.txt         |  11 +
 Documentation/virt/kvm/msr.rst                |  53 +++++
 arch/x86/Kconfig                              |  10 +
 arch/x86/include/asm/kvm_host.h               |   7 +
 arch/x86/include/asm/kvm_para.h               |  28 +++
 arch/x86/include/uapi/asm/kvm_para.h          |   7 +
 arch/x86/kernel/cpu/common.c                  |  11 +-
 arch/x86/kernel/kvm.c                         |  39 ++++
 arch/x86/kernel/setup.c                       |  12 +-
 arch/x86/kvm/cpuid.c                          |   3 +-
 arch/x86/kvm/emulate.c                        |   3 +-
 arch/x86/kvm/kvm_emulate.h                    |   2 +-
 arch/x86/kvm/svm/nested.c                     |  11 +-
 arch/x86/kvm/vmx/nested.c                     |  10 +-
 arch/x86/kvm/x86.c                            | 106 ++++++++-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |  13 ++
 .../selftests/kvm/x86_64/smm_cr_pin_test.c    | 207 ++++++++++++++++++
 19 files changed, 521 insertions(+), 14 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_cr_pin_test.c


base-commit: 49b3deaad3452217d62dbd78da8df24eb0c7e169
```
