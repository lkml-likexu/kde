

#### [PATCH v4 00/19] x86/cpu: Clean up handling of VMX features
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Nov 28 01:39:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11265225
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A948921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 01:42:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62C47215F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 01:42:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727600AbfK1BkV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 20:40:21 -0500
Received: from mga02.intel.com ([134.134.136.20]:10954 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727109AbfK1BkV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 20:40:21 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 17:40:18 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,251,1571727600";
   d="scan'208";a="221166461"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga002.jf.intel.com with ESMTP; 27 Nov 2019 17:40:18 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Mark Rutland <mark.rutland@arm.com>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Jiri Olsa <jolsa@redhat.com>, Namhyung Kim <namhyung@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>,
 Len Brown <lenb@kernel.org>, Shuah Khan <shuah@kernel.org>,
 linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
 linux-edac@vger.kernel.org, linux-pm@vger.kernel.org,
 linux-kselftest@vger.kernel.org, Borislav Petkov <bp@suse.de>,
 Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH v4 00/19] x86/cpu: Clean up handling of VMX features
Date: Wed, 27 Nov 2019 17:39:57 -0800
Message-Id: <20191128014016.4389-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up a handful of interrelated warts in the kernel's handling of VMX:

  - Enable VMX in IA32_FEATURE_CONTROL during boot instead of on-demand
    during KVM load to avoid future contention over IA32_FEATURE_CONTROL.

  - Rework VMX feature reporting so that it is accurate and up-to-date,
    now and in the future.

  - Consolidate code across CPUs that support VMX.

This series stems from two separate but related issues.  The first issue,
pointed out by Boris in the SGX enabling series[1], is that the kernel
currently doesn't ensure the IA32_FEATURE_CONTROL MSR is configured during
boot.  The second issue is that the kernel's reporting of VMX features is
stale, potentially inaccurate, and difficult to maintain.

v4:
  - Rebase to tip/master, 8a1b070333f4 ("Merge branch 'WIP.x86/mm'")
  - Rename everything feature control related to IA32_FEAT_CTL. [Boris]
  - Minor coding style tweaks [Boris and Jarkko].
  - Print VMX feature flags in "vmx flags" to avoid polluting "flags",
    but keep printing the current synthetic VMX in "flags" so as not to
    break the ABI. [Boris]
  - Don't bother printing an error message in the extremely unlikely
    event VMX is supported but IA32_FEAT_CTL doesn't exist. [Boris]
  - Beef up a few changelogs and comments. [Boris]
  - Add a comment in the LMCE code for the new WARN. [Jarkko]
  - Check CONFIG_KVM_INTEL instead of CONFIG_KVM when deciding whether
    or not to enable VMX.
  - Add a patch to introduce X86_FEATURE_MSR_IA32_FEAT_CTL.
  - Dropped Jim's Reviewed-by from a few KVM patches due to the above
    addition.

v3:
  - Rebase to tip/master, ceceaf1f12ba ("Merge branch 'WIP.x86/cleanups'").
  - Rename the feature control MSR bit defines [Boris].
  - Rewrite the error message displayed when reading feature control MSR
    faults on a VMX capable CPU to explicitly state that it's likely a
    hardware or hypervisor issue [Boris].
  - Collect a Reviewed-by for the LMCE change [Boris].
  - Enable VMX in feature control (if it's unlocked) if and only if
    KVM is enabled [Paolo].
  - Remove a big pile of redudant MSR defines from the KVM selftests that
    was discovered when renaming the feature control defines.
  - Fix a changelog typoe [Boris].

v2:
  - Rebase to latest tip/x86/cpu (1edae1ae6258, "x86/Kconfig: Enforce...)
  - Collect Jim's reviews.
  - Fix a typo in setting of EPT capabilities [TonyWWang-oc].
  - Remove defines for reserved VMX feature flags [Paolo].
  - Print the VMX features under "flags" and maintain all existing names
    to be backward compatible with the ABI [Paolo].
  - Create aggregate APIC features to report FLEXPRIORITY and APICV, so
    that the full feature *and* their associated individual features are
    printed, e.g. to aid in recognizing why an APIC feature isn't being
    used.
  - Fix a few copy paste errors in changelogs.


v1 cover letter:

== IA32_FEATURE_CONTROL ==
Lack of IA32_FEATURE_CONTROL configuration during boot isn't a functional
issue in the current kernel as the majority of platforms set and lock
IA32_FEATURE_CONTROL in firmware.  And when the MSR is left unlocked, KVM
is the only subsystem that writes IA32_FEATURE_CONTROL.  That will change
if/when SGX support is enabled, as SGX will also want to fully enable
itself when IA32_FEATURE_CONTROL is unlocked.

== VMX Feature Reporting ==
VMX features are not enumerated via CPUID, but instead are enumerated
through VMX MSRs.  As a result, new VMX features are not automatically
reported via /proc/cpuinfo.

An attempt was made long ago to report interesting and/or meaningful VMX
features by synthesizing select features into a Linux-defined cpufeatures
word.  Synthetic feature flags worked for the initial purpose, but the
existence of the synthetic flags was forgotten almost immediately, e.g.
only one new flag (EPT A/D) has been added in the the decade since the
synthetic VMX features were introduced, while VMX and KVM have gained
support for many new features.

Placing the synthetic flags in x86_capability also allows them to be
queried via cpu_has() and company, which is misleading as the flags exist
purely for reporting via /proc/cpuinfo.  KVM, the only in-kernel user of
VMX, ignores the flags.

Last but not least, VMX features are reported in /proc/cpuinfo even
when VMX is unusable due to lack of enabling in IA32_FEATURE_CONTROL.

== Caveats ==
All of the testing of non-standard flows was done in a VM, as I don't
have a system that leaves IA32_FEATURE_CONTROL unlocked, or locks it with
VMX disabled.

The Centaur and Zhaoxin changes are somewhat speculative, as I haven't
confirmed they actually support IA32_FEATURE_CONTROL, or that they want to
gain "official" KVM support.  I assume they unofficially support KVM given
that both CPUs went through the effort of enumerating VMX features.  That
in turn would require them to support IA32_FEATURE_CONTROL since KVM will
fault and refuse to load if the MSR doesn't exist.

[1] https://lkml.kernel.org/r/20190925085156.GA3891@zn.tnic

Sean Christopherson (19):
  x86/msr-index: Clean up bit defines for IA32_FEATURE_CONTROL MSR
  selftests: kvm: Replace manual MSR defs with common msr-index.h
  tools arch x86: Sync msr-index.h from kernel sources
  x86/intel: Initialize IA32_FEAT_CTL MSR at boot
  x86/mce: WARN once if IA32_FEAT_CTL MSR is left unlocked
  x86/centaur: Use common IA32_FEAT_CTL MSR initialization
  x86/zhaoxin: Use common IA32_FEAT_CTL MSR initialization
  x86/cpu: Clear VMX feature flag if VMX is not fully enabled
  x86/vmx: Introduce VMX_FEATURES_*
  x86/cpu: Detect VMX features on Intel, Centaur and Zhaoxin CPUs
  x86/cpu: Print VMX flags in /proc/cpuinfo using VMX_FEATURES_*
  x86/cpu: Set synthetic VMX cpufeatures during init_ia32_feat_ctl()
  x86/cpufeatures: Add flag to track whether MSR IA32_FEAT_CTL is
    configured
  KVM: VMX: Drop initialization of IA32_FEAT_CTL MSR
  KVM: VMX: Use VMX feature flag to query BIOS enabling
  KVM: VMX: Check for full VMX support when verifying CPU compatibility
  KVM: VMX: Use VMX_FEATURE_* flags to define VMCS control bits
  perf/x86: Provide stubs of KVM helpers for non-Intel CPUs
  KVM: VMX: Allow KVM_INTEL when building for Centaur and/or Zhaoxin
    CPUs

 MAINTAINERS                                   |   2 +-
 arch/x86/Kconfig.cpu                          |   8 +
 arch/x86/boot/mkcpustr.c                      |   1 +
 arch/x86/include/asm/cpufeatures.h            |   1 +
 arch/x86/include/asm/msr-index.h              |  14 +-
 arch/x86/include/asm/perf_event.h             |  22 +-
 arch/x86/include/asm/processor.h              |   4 +
 arch/x86/include/asm/vmx.h                    | 105 +--
 arch/x86/include/asm/vmxfeatures.h            |  86 +++
 arch/x86/kernel/cpu/Makefile                  |   6 +-
 arch/x86/kernel/cpu/centaur.c                 |  35 +-
 arch/x86/kernel/cpu/common.c                  |   3 +
 arch/x86/kernel/cpu/cpu.h                     |   4 +
 arch/x86/kernel/cpu/feat_ctl.c                | 140 ++++
 arch/x86/kernel/cpu/intel.c                   |  49 +-
 arch/x86/kernel/cpu/mce/intel.c               |  15 +-
 arch/x86/kernel/cpu/mkcapflags.sh             |  15 +-
 arch/x86/kernel/cpu/proc.c                    |  15 +
 arch/x86/kernel/cpu/zhaoxin.c                 |  35 +-
 arch/x86/kvm/Kconfig                          |  10 +-
 arch/x86/kvm/vmx/nested.c                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        |  67 +-
 arch/x86/kvm/vmx/vmx.h                        |   2 +-
 arch/x86/kvm/x86.c                            |   2 +-
 tools/arch/x86/include/asm/msr-index.h        |  30 +-
 tools/power/x86/turbostat/turbostat.c         |   4 +-
 tools/testing/selftests/kvm/Makefile          |   4 +-
 .../selftests/kvm/include/x86_64/processor.h  | 726 +-----------------
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   8 +-
 29 files changed, 431 insertions(+), 986 deletions(-)
 create mode 100644 arch/x86/include/asm/vmxfeatures.h
 create mode 100644 arch/x86/kernel/cpu/feat_ctl.c
```
#### [PATCH v2 0/8] Use 1st-level for DMA remapping
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Thu Nov 28 02:25:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11265295
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E1FF13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 02:30:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DDAB2168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 02:30:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727644AbfK1C36 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 Nov 2019 21:29:58 -0500
Received: from mga18.intel.com ([134.134.136.126]:17935 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726695AbfK1C35 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 Nov 2019 21:29:57 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Nov 2019 18:29:57 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,251,1571727600";
   d="scan'208";a="221176106"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by orsmga002.jf.intel.com with ESMTP; 27 Nov 2019 18:29:54 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v2 0/8] Use 1st-level for DMA remapping
Date: Thu, 28 Nov 2019 10:25:42 +0800
Message-Id: <20191128022550.9832-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel VT-d in scalable mode supports two types of page talbes
for DMA translation: the first level page table and the second
level page table. The first level page table uses the same
format as the CPU page table, while the second level page table
keeps compatible with previous formats. The software is able
to choose any one of them for DMA remapping according to the use
case.

This patchset aims to move IOVA (I/O Virtual Address) translation
to 1st-level page table in scalable mode. This will simplify vIOMMU
(IOMMU simulated by VM hypervisor) design by using the two-stage
translation, a.k.a. nested mode translation.

As Intel VT-d architecture offers caching mode, guest IOVA (GIOVA)
support is now implemented in a shadow page manner. The device
simulation software, like QEMU, has to figure out GIOVA->GPA mappings
and write them to a shadowed page table, which will be used by the
physical IOMMU. Each time when mappings are created or destroyed in
vIOMMU, the simulation software has to intervene. Hence, the changes
on GIOVA->GPA could be shadowed to host.


     .-----------.
     |  vIOMMU   |
     |-----------|                 .--------------------.
     |           |IOTLB flush trap |        QEMU        |
     .-----------. (map/unmap)     |--------------------|
     |GIOVA->GPA |---------------->|    .------------.  |
     '-----------'                 |    | GIOVA->HPA |  |
     |           |                 |    '------------'  |
     '-----------'                 |                    |
                                   |                    |
                                   '--------------------'
                                                |
            <------------------------------------
            |
            v VFIO/IOMMU API
      .-----------.
      |  pIOMMU   |
      |-----------|
      |           |
      .-----------.
      |GIOVA->HPA |
      '-----------'
      |           |
      '-----------'

In VT-d 3.0, scalable mode is introduced, which offers two-level
translation page tables and nested translation mode. Regards to
GIOVA support, it can be simplified by 1) moving the GIOVA support
over 1st-level page table to store GIOVA->GPA mapping in vIOMMU,
2) binding vIOMMU 1st level page table to the pIOMMU, 3) using pIOMMU
second level for GPA->HPA translation, and 4) enable nested (a.k.a.
dual-stage) translation in host. Compared with current shadow GIOVA
support, the new approach makes the vIOMMU design simpler and more
efficient as we only need to flush the pIOMMU IOTLB and possible
device-IOTLB when an IOVA mapping in vIOMMU is torn down.

     .-----------.
     |  vIOMMU   |
     |-----------|                 .-----------.
     |           |IOTLB flush trap |   QEMU    |
     .-----------.    (unmap)      |-----------|
     |GIOVA->GPA |---------------->|           |
     '-----------'                 '-----------'
     |           |                       |
     '-----------'                       |
           <------------------------------
           |      VFIO/IOMMU          
           |  cache invalidation and  
           | guest gpd bind interfaces
           v
     .-----------.
     |  pIOMMU   |
     |-----------|
     .-----------.
     |GIOVA->GPA |<---First level
     '-----------'
     | GPA->HPA  |<---Scond level
     '-----------'
     '-----------'

This patch set includes two parts. The former part implements the
per-domain page table abstraction, which makes the page table
difference transparent to various map/unmap APIs. The later part
applies the first level page table for IOVA translation unless the
DOMAIN_ATTR_NESTING domain attribution has been set, which indicates
nested mode in use.

Based-on-idea-by: Ashok Raj <ashok.raj@intel.com>
Based-on-idea-by: Kevin Tian <kevin.tian@intel.com>
Based-on-idea-by: Liu Yi L <yi.l.liu@intel.com>
Based-on-idea-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Based-on-idea-by: Sanjay Kumar <sanjay.k.kumar@intel.com>
Based-on-idea-by: Lu Baolu <baolu.lu@linux.intel.com>

Change log:

 v1->v2
 - The first series was posted here
   https://lkml.org/lkml/2019/9/23/297
 - Use per domain page table ops to handle different page tables.
 - Use first level for DMA remapping by default on both bare metal
   and vm guest.
 - Code refine according to code review comments for v1.

Lu Baolu (8):
  iommu/vt-d: Add per domain page table ops
  iommu/vt-d: Move domain_flush_cache helper into header
  iommu/vt-d: Implement second level page table ops
  iommu/vt-d: Apply per domain second level page table ops
  iommu/vt-d: Add first level page table interfaces
  iommu/vt-d: Implement first level page table ops
  iommu/vt-d: Identify domains using first level page table
  iommu/vt-d: Add set domain DOMAIN_ATTR_NESTING attr

 drivers/iommu/Makefile             |   2 +-
 drivers/iommu/intel-iommu.c        | 412 +++++++++++++++++++++++------
 drivers/iommu/intel-pgtable.c      | 376 ++++++++++++++++++++++++++
 include/linux/intel-iommu.h        |  64 ++++-
 include/trace/events/intel_iommu.h |  60 +++++
 5 files changed, 837 insertions(+), 77 deletions(-)
 create mode 100644 drivers/iommu/intel-pgtable.c
```
#### [kvm-unit-tests PATCH v2 0/9] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Nov 28 12:45:58 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11265915
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6FF8109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 12:46:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF700215A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 12:46:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726496AbfK1MqQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 07:46:16 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:33154 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726227AbfK1MqQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 07:46:16 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xASCgxqV038937
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 07:46:15 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2whcxrujxh-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 28 Nov 2019 07:46:14 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Thu, 28 Nov 2019 12:46:12 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 28 Nov 2019 12:46:10 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xASCk9hv62259226
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 28 Nov 2019 12:46:09 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9023DAE045;
        Thu, 28 Nov 2019 12:46:09 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2DB8AAE056;
        Thu, 28 Nov 2019 12:46:09 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.185.119])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 28 Nov 2019 12:46:09 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/9] s390x: Testing the Channel Subsystem
 I/O
Date: Thu, 28 Nov 2019 13:45:58 +0100
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
x-cbid: 19112812-0028-0000-0000-000003C11C66
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19112812-0029-0000-0000-000024842715
Message-Id: <1574945167-29677-1-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-28_03:2019-11-28,2019-11-28 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxscore=0
 suspectscore=1 spamscore=0 phishscore=0 mlxlogscore=711 bulkscore=0
 priorityscore=1501 impostorscore=0 malwarescore=0 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911280112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Goal of the series is to have a framwork to test Channel-Subsystem I/O with
QEMU/KVM.

To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.

Making the interrupt handler weak allows the test programm to define its own
interrupt handler. We need to do special work under interrupt like acknoledging
the interrupt.

Being working on PSW bits to allow I/O interrupt, we define all PSW bits in a
dedicated file.

The simple test tests the I/O reading by the SUB Channel. It needs QEMU to
be patched to have the pong device defined.
The pong device answers, for now, with a Hello World to the read request.


Pierre Morel (9):
  s390x: saving regs for interrupts
  s390x: Define the PSW bits
  s390x: irq: make IRQ handler weak
  s390x: export the clock get_clock_ms() utility
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

 lib/s390x/asm/arch_bits.h |  20 +++
 lib/s390x/asm/arch_def.h  |   6 +-
 lib/s390x/asm/clock.h     |  25 ++++
 lib/s390x/css.h           | 282 ++++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c      | 147 +++++++++++++++++++
 lib/s390x/interrupt.c     |   2 +-
 s390x/Makefile            |   4 +-
 s390x/css.c               | 294 ++++++++++++++++++++++++++++++++++++++
 s390x/cstart64.S          |  38 +++--
 s390x/intercept.c         |  11 +-
 s390x/unittests.cfg       |   4 +
 11 files changed, 809 insertions(+), 24 deletions(-)
 create mode 100644 lib/s390x/asm/arch_bits.h
 create mode 100644 lib/s390x/asm/clock.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 s390x/css.c
```
#### [RFC PATCH 0/3] vsock: support network namespace
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Nov 28 17:15:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11266433
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EABE015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 17:15:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA6F521739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 17:15:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="e1INEXf8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726876AbfK1RPd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 12:15:33 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:51746 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726586AbfK1RPd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Nov 2019 12:15:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574961331;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9JTXqexhPJCr/NYp8eLm2gzq1RhmqcIBI6fHhWivQDE=;
        b=e1INEXf8jA8qZ7bf1Z4/sjdlq7+jJTwRHITA3Q9gNy6ZsgGQsSbDvEQNo04ftpqL5MVCSB
        ks+lS8RLjcOJceRMJrDakiT+W2Wj3S+wAILVjmcIa0GecMzm1XOIU/WL8M2yPI41w1GMvo
        VLh3HvyHaAWj9+s8faVVoCixq5XmogM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-394-2CitP0_oPIi5IxNIq7mh5g-1; Thu, 28 Nov 2019 12:15:29 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 50567107ACCC;
        Thu, 28 Nov 2019 17:15:28 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-168.ams2.redhat.com
 [10.36.117.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A8A4600CA;
        Thu, 28 Nov 2019 17:15:19 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Dexuan Cui <decui@microsoft.com>,
        Jason Wang <jasowang@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jorgen Hansen <jhansen@vmware.com>
Subject: [RFC PATCH 0/3] vsock: support network namespace
Date: Thu, 28 Nov 2019 18:15:16 +0100
Message-Id: <20191128171519.203979-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: 2CitP0_oPIi5IxNIq7mh5g-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
now that we have multi-transport upstream, I started to take a look to
support network namespace (netns) in vsock.

As we partially discussed in the multi-transport proposal [1], it could
be nice to support network namespace in vsock to reach the following
goals:
- isolate host applications from guest applications using the same ports
  with CID_ANY
- assign the same CID of VMs running in different network namespaces
- partition VMs between VMMs or at finer granularity

This preliminary implementation provides the following behavior:
- packets received from the host (received by G2H transports) are
  assigned to the default netns (init_net)
- packets received from the guest (received by H2G - vhost-vsock) are
  assigned to the netns of the process that opens /dev/vhost-vsock
  (usually the VMM, qemu in my tests, opens the /dev/vhost-vsock)
    - for vmci I need some suggestions, because I don't know how to do
      and test the same in the vmci driver, for now vmci uses the
      init_net
- loopback packets are exchanged only in the same netns

Questions:
1. Should we make configurable the netns (now it is init_net) where
   packets from the host should be delivered?
2. Should we provide an ioctl in vhost-vsock to configure the netns
   to use? (instead of using the netns of the process that opens
   /dev/vhost-vsock)
3. Should we provide a way to disable the netns support in vsock?
4. Jorgen: Do you think can be useful support it in vmci host
   driver?

I tested the series in this way:
l0_host$ qemu-system-x86_64 -m 4G -M accel=kvm -smp 4 \
            -drive file=/tmp/vsockvm0.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=3

l1_vm$ ip netns add ns1
l1_vm$ ip netns add ns2
 # same CID on different netns
l1_vm$ ip netns exec ns1 qemu-system-x86_64 -m 1G -M accel=kvm -smp 2 \
            -drive file=/tmp/vsockvm1.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=4
l1_vm$ ip netns exec ns2 qemu-system-x86_64 -m 1G -M accel=kvm -smp 2 \
            -drive file=/tmp/vsockvm2.img,if=virtio --nographic \
            -device vhost-vsock-pci,guest-cid=4

 # all iperf3 listen on CID_ANY and port 5201, but in different netns
l1_vm$ ./iperf3 --vsock -s # connection from l0 or guests started
                           # on default netns (init_net)
l1_vm$ ip netns exec ns1 ./iperf3 --vsock -s
l1_vm$ ip netns exec ns1 ./iperf3 --vsock -s

l0_host$ ./iperf3 --vsock -c 3
l2_vm1$ ./iperf3 --vsock -c 2
l2_vm2$ ./iperf3 --vsock -c 2

This series is on top of the vsock-loopback series (not yet merged),
and it is available in the Git repository at:

  git://github.com/stefano-garzarella/linux.git vsock-netns

Any comments are really appreciated!

Thanks,
Stefano

[1] https://www.spinics.net/lists/netdev/msg575792.html

Stefano Garzarella (3):
  vsock: add network namespace support
  vsock/virtio_transport_common: handle netns of received packets
  vhost/vsock: use netns of process that opens the vhost-vsock device

 drivers/vhost/vsock.c                   | 29 ++++++++++++++++-------
 include/linux/virtio_vsock.h            |  2 ++
 include/net/af_vsock.h                  |  6 +++--
 net/vmw_vsock/af_vsock.c                | 31 ++++++++++++++++++-------
 net/vmw_vsock/hyperv_transport.c        |  5 ++--
 net/vmw_vsock/virtio_transport.c        |  2 ++
 net/vmw_vsock/virtio_transport_common.c | 12 ++++++++--
 net/vmw_vsock/vmci_transport.c          |  5 ++--
 8 files changed, 67 insertions(+), 25 deletions(-)
```
#### [kvm-unit-tests PATCH v2 00/18] arm/arm64: Various fixes
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Nov 28 18:04:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11266473
Return-Path: <SRS0=sCwx=ZU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B0FB109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 18:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 79CEF21775
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Nov 2019 18:04:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726582AbfK1SEb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Nov 2019 13:04:31 -0500
Received: from foss.arm.com ([217.140.110.172]:39294 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726401AbfK1SEb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Nov 2019 13:04:31 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 84FD11FB;
        Thu, 28 Nov 2019 10:04:30 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 682863F6C4;
        Thu, 28 Nov 2019 10:04:29 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, drjones@redhat.com,
        maz@kernel.org, andre.przywara@arm.com, vladimir.murzin@arm.com,
        mark.rutland@arm.com
Subject: [kvm-unit-tests PATCH v2 00/18] arm/arm64: Various fixes
Date: Thu, 28 Nov 2019 18:04:00 +0000
Message-Id: <20191128180418.6938-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a combination of the fixes from my EL2 series [1] and other new
fixes.

Changes in v2:
* Fixed the prefetch abort test on QEMU by changing the address used to
  cause the abort.

Summary of the patches:
* Patch 1 adds coherent translation table walks for ARMv7 and removes
  unneeded dcache maintenance.
* Patches 2-4 make translation table updates more robust.
* Patches 5-6 fix a pretty serious bug in our PSCI test, which was causing
  an infinite loop of prefetch aborts.
* Patches 7-10 add a proper test for prefetch aborts. The test now uses
  mmu_clear_user.
* Patches 11-13 are fixes for the timer test.
* Patches 14-15 fix turning the MMU off.
* Patches 16-18 are small fixes to make the code more robust, and perhaps
  more important, remove unnecessary operations that might hide real bugs
  in KVM.

Patches 1-4, 9, 18 are new. The rest are taken from the EL2 series, and
I've kept the Reviewed-by tag where appropriate. There are no major
changes, only those caused by rebasing on top of the current kvm-unit-tests
version.

Please review.

[1] https://www.spinics.net/lists/kvm/msg196797.html

Alexandru Elisei (18):
  lib: arm/arm64: Remove unnecessary dcache maintenance operations
  lib: arm64: Remove barriers before TLB operations
  lib: Add WRITE_ONCE and READ_ONCE implementations in compiler.h
  lib: arm/arm64: Use WRITE_ONCE to update the translation tables
  lib: arm/arm64: Remove unused CPU_OFF parameter
  arm/arm64: psci: Don't run C code without stack or vectors
  lib: arm/arm64: Add missing include for alloc_page.h in pgtable.h
  lib: arm: Implement flush_tlb_all
  lib: arm/arm64: Teach mmu_clear_user about block mappings
  arm/arm64: selftest: Add prefetch abort test
  arm64: timer: Write to ICENABLER to disable timer IRQ
  arm64: timer: EOIR the interrupt after masking the timer
  arm64: timer: Test behavior when timer disabled or masked
  lib: arm/arm64: Refuse to disable the MMU with non-identity stack
    pointer
  arm/arm64: Perform dcache clean + invalidate after turning MMU off
  arm: cstart64.S: Downgrade TLBI to non-shareable in asm_mmu_enable
  arm/arm64: Invalidate TLB before enabling MMU
  arm: cstart64.S: Remove icache invalidation from asm_mmu_enable

 lib/linux/compiler.h          |  81 ++++++++++++++++++++++++
 lib/arm/asm/gic-v3.h          |   1 +
 lib/arm/asm/gic.h             |   1 +
 lib/arm/asm/mmu-api.h         |   2 +-
 lib/arm/asm/mmu.h             |  11 ++--
 lib/arm/asm/pgtable-hwdef.h   |  11 ++++
 lib/arm/asm/pgtable.h         |  20 ++++--
 lib/arm/asm/processor.h       |   6 ++
 lib/arm64/asm/esr.h           |   3 +
 lib/arm64/asm/mmu.h           |   2 -
 lib/arm64/asm/pgtable-hwdef.h |   3 +
 lib/arm64/asm/pgtable.h       |  15 ++++-
 lib/arm64/asm/processor.h     |   6 ++
 lib/arm/mmu.c                 |  64 +++++++++++--------
 lib/arm/processor.c           |  10 +++
 lib/arm/psci.c                |   4 +-
 lib/arm/setup.c               |   2 +
 lib/arm64/processor.c         |  11 ++++
 arm/cstart.S                  |  40 +++++++++++-
 arm/cstart64.S                |  35 ++++++++++-
 arm/cache.c                   |   3 +-
 arm/psci.c                    |   5 +-
 arm/selftest.c                | 112 +++++++++++++++++++++++++++++++++-
 arm/timer.c                   |  38 ++++++++----
 24 files changed, 421 insertions(+), 65 deletions(-)
 create mode 100644 lib/linux/compiler.h
```
