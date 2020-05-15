

#### [RFC 00/18] Refactor configuration of guest memory protection
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Thu May 14 06:41:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11548041
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CF6E913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 06:41:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 388D1206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 06:41:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="Qi1X9mS3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726159AbgENGld (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 02:41:33 -0400
Received: from ozlabs.org ([203.11.71.1]:60495 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725931AbgENGlc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 02:41:32 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49N24j0crHz9sSd; Thu, 14 May 2020 16:41:24 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1589438485;
        bh=vvYudY/uRKvNzTDTxC0FfBGKSAwOXcVJGXD3YDR90r8=;
        h=From:To:Cc:Subject:Date:From;
        b=Qi1X9mS3JVsGJg+QbwlDGmsYTuiA4YSccRAY/Py97qcQMVRwNMOPvlEs7c7Pn91lu
         GWudnf/ACmQ0Y39KeD7PtetxzEiQhHc/FV+7ArvAPj3DM3cDsg2Q1DWrkBWnz+TisQ
         E9EReUmtMIIyFJvFy6eQpPzjN9qoLK8mWZnJum7c=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, frankja@linux.ibm.com, pair@us.redhat.com,
        qemu-devel@nongnu.org, brijesh.singh@amd.com
Cc: kvm@vger.kernel.org, qemu-ppc@nongnu.org,
        David Gibson <david@gibson.dropbear.id.au>,
        Richard Henderson <rth@twiddle.net>, cohuck@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, qemu-devel@nongnu.-rg,
        mdroth@linux.vnet.ibm.com
Subject: [RFC 00/18] Refactor configuration of guest memory protection
Date: Thu, 14 May 2020 16:41:02 +1000
Message-Id: <20200514064120.449050-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A number of hardware platforms are implementing mechanisms whereby the
hypervisor does not have unfettered access to guest memory, in order
to mitigate the security impact of a compromised hypervisor.

AMD's SEV implements this with in-cpu memory encryption, and Intel has
its own memory encryption mechanism.  POWER has an upcoming mechanism
to accomplish this in a different way, using a new memory protection
level plus a small trusted ultravisor.  s390 also has a protected
execution environment.

The current code (committed or draft) for these features has each
platform's version configured entirely differently.  That doesn't seem
ideal for users, or particularly for management layers.

AMD SEV introduces a notionally generic machine option
"machine-encryption", but it doesn't actually cover any cases other
than SEV.

This series is a proposal to at least partially unify configuration
for these mechanisms, by renaming and generalizing AMD's
"memory-encryption" property.  It is replaced by a
"guest-memory-protection" property pointing to a platform specific
object which configures and manages the specific details.

For now this series covers just AMD SEV and POWER PEF.  I'm hoping it
can be extended to cover the Intel and s390 mechanisms as well,
though.

Note: I'm using the term "guest memory protection" throughout to refer
to mechanisms like this.  I don't particular like the term, it's both
long and not really precise.  If someone can think of a succinct way
of saying "a means of protecting guest memory from a possibly
compromised hypervisor", I'd be grateful for the suggestion.

David Gibson (18):
  target/i386: sev: Remove unused QSevGuestInfoClass
  target/i386: sev: Move local structure definitions into .c file
  target/i386: sev: Rename QSevGuestInfo
  target/i386: sev: Embed SEVState in SevGuestState
  target/i386: sev: Partial cleanup to sev_state global
  target/i386: sev: Remove redundant cbitpos and reduced_phys_bits
    fields
  target/i386: sev: Remove redundant policy field
  target/i386: sev: Remove redundant handle field
  target/i386: sev: Unify SEVState and SevGuestState
  guest memory protection: Add guest memory protection interface
  guest memory protection: Handle memory encrption via interface
  guest memory protection: Perform KVM init via interface
  guest memory protection: Move side effect out of
    machine_set_memory_encryption()
  guest memory protection: Rework the "memory-encryption" property
  guest memory protection: Decouple kvm_memcrypt_*() helpers from KVM
  use errp for gmpo kvm_init
  spapr: Added PEF based guest memory protection
  guest memory protection: Alter virtio default properties for protected
    guests

 accel/kvm/kvm-all.c                    |  40 +--
 accel/kvm/sev-stub.c                   |   5 -
 accel/stubs/kvm-stub.c                 |  10 -
 backends/Makefile.objs                 |   2 +
 backends/guest-memory-protection.c     |  29 ++
 hw/core/machine.c                      |  61 ++++-
 hw/i386/pc_sysfw.c                     |   6 +-
 include/exec/guest-memory-protection.h |  77 ++++++
 include/hw/boards.h                    |   4 +-
 include/sysemu/kvm.h                   |  17 --
 include/sysemu/sev.h                   |   6 +-
 target/i386/sev.c                      | 358 +++++++++++++------------
 target/i386/sev_i386.h                 |  49 ----
 target/ppc/Makefile.objs               |   2 +-
 target/ppc/pef.c                       |  81 ++++++
 15 files changed, 445 insertions(+), 302 deletions(-)
 create mode 100644 backends/guest-memory-protection.c
 create mode 100644 include/exec/guest-memory-protection.h
 create mode 100644 target/ppc/pef.c
```
#### [PATCH v11 00/11] Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Thu May 14 08:30:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11548237
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F8E960D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 08:31:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E03120675
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 08:31:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726174AbgENIbS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 04:31:18 -0400
Received: from mga18.intel.com ([134.134.136.126]:12077 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725999AbgENIbR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 04:31:17 -0400
IronPort-SDR: 
 02XFEZLVyI27FuKIx1QIQrtczQXVcW89DVUxTR8icEeDRjXDGAOU/oJrfmd19G4hzAS/hX1Sau
 1erzp7CzY4rw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2020 01:31:09 -0700
IronPort-SDR: 
 ui5pev/3O5s9inemVpVoBPby6R+/hUPU/HyUpfcEzVlSXyj9LgkREi4cA8Cg5iAoBltOeesObj
 odan99aHHgYg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,390,1583222400";
   d="scan'208";a="341539902"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga001.jf.intel.com with ESMTP; 14 May 2020 01:31:05 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>, ak@linux.intel.com,
        wei.w.wang@intel.com, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v11 00/11] Guest Last Branch Recording Enabling
Date: Thu, 14 May 2020 16:30:43 +0800
Message-Id: <20200514083054.62538-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Peter,
Would you mind acking the host perf patches if it looks good to you ?

Hi Paolo,
Please help review the KVM proposal changes in this stable version.

Now, we can use upstream QEMU w/ '-cpu host' to test this feature, and
disable it by clearing the LBR format bits in the IA32_PERF_CAPABILITIES.

v10->v11 Changelog:
- add '.config = INTEL_FIXED_VLBR_EVENT' to the guest LBR event config;
- rewrite is_guest_lbr_event() with 'config == INTEL_FIXED_VLBR_EVENT';
- emit pr_warn() on the host when guest LBR is temporarily unavailable;
- drop the KVM_CAP_X86_GUEST_LBR patch;
- rewrite MSR_IA32_PERF_CAPABILITIES patch LBR record format;
- split 'kvm_pmu->lbr_already_available' into a separate patch;
- split 'pmu_ops->availability_check' into a separate patch;
- comments and naming refinement, misc;

You may check more details in each commit.

Previous:
https://lore.kernel.org/kvm/20200423081412.164863-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

The userspace could configure whether it's enabled or not for each
guest via MSR_IA32_PERF_CAPABILITIES msr. As a first step, a guest
could only enable LBR feature if its cpu model is the same as the
host since the LBR feature is still one of model specific features.

If it's enabled on the guest, the guest LBR driver would accesses the
LBR MSR (including IA32_DEBUGCTLMSR and records MSRs) as host does.
The first guest access on the LBR related MSRs is always interceptible.
The KVM trap would create a special LBR event (called guest LBR event)
which enables the callstack mode and none of hardware counter is assigned.
The host perf would enable and schedule this event as usual. 

Guest's first access to a LBR registers gets trapped to KVM, which
creates a guest LBR perf event. It's a regular LBR perf event which gets
the LBR facility assigned from the perf subsystem. Once that succeeds,
the LBR stack msrs are passed through to the guest for efficient accesses.
However, if another host LBR event comes in and takes over the LBR
facility, the LBR msrs will be made interceptible, and guest following
accesses to the LBR msrs will be trapped and meaningless. 

Because saving/restoring tens of LBR MSRs (e.g. 32 LBR stack entries) in
VMX transition brings too excessive overhead to frequent vmx transition
itself, the guest LBR event would help save/restore the LBR stack msrs
during the context switching with the help of native LBR event callstack
mechanism, including LBR_SELECT msr.

If the guest no longer accesses the LBR-related MSRs within a scheduling
time slice and the LBR enable bit is unset, vPMU would release its guest
LBR event as a normal event of a unused vPMC and the pass-through
state of the LBR stack msrs would be canceled.

---

LBR testcase:
echo 1 > /proc/sys/kernel/watchdog
echo 25 > /proc/sys/kernel/perf_cpu_time_max_percent
echo 5000 > /proc/sys/kernel/perf_event_max_sample_rate
echo 0 > /proc/sys/kernel/perf_cpu_time_max_percent
./perf record -b ./br_instr a

- Perf report on the host:
Samples: 72K of event 'cycles', Event count (approx.): 72512
Overhead  Command   Source Shared Object           Source Symbol                           Target Symbol                           Basic Block Cycles
  12.12%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           1
  11.05%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             5
   8.81%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             4
   5.04%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           20
   4.92%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             6
   4.88%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           6
   4.58%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           5

- Perf report on the guest:
Samples: 92K of event 'cycles', Event count (approx.): 92544
Overhead  Command   Source Shared Object  Source Symbol                                   Target Symbol                                   Basic Block Cycles
  12.03%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   1
  11.09%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     5
   8.57%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     4
   5.08%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     6
   5.06%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   20
   4.87%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   6
   4.70%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   5

Conclusion: the profiling results on the guest are similar to that on the host.

Like Xu (9):
  perf/x86/core: Refactor hw->idx checks and cleanup
  perf/x86/lbr: Add interface to get basic information about LBR stack
  perf/x86: Add constraint to create guest LBR event without hw counter
  perf/x86: Keep LBR stack unchanged in host context for guest LBR event
  KVM: x86: Expose MSR_IA32_PERF_CAPABILITIES for LBR record format
  KVM: x86/pmu: Emulate LBR feature via guest LBR event
  KVM: x86/pmu: Release guest LBR event via vPMU lazy release mechanism
  KVM: x86/pmu: Check guest LBR availability in case host reclaims them
  KVM: x86/pmu: Reduce the overhead of LBR passthrough or cancellation

Wei Wang (2):
  perf/x86: Fix variable types for LBR registers
  KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct msr_data' in

 arch/x86/events/core.c            |  26 ++-
 arch/x86/events/intel/core.c      | 105 ++++++----
 arch/x86/events/intel/lbr.c       |  56 +++++-
 arch/x86/events/perf_event.h      |  12 +-
 arch/x86/include/asm/kvm_host.h   |  13 ++
 arch/x86/include/asm/perf_event.h |  34 +++-
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/pmu.c                |  19 +-
 arch/x86/kvm/pmu.h                |  15 +-
 arch/x86/kvm/svm/pmu.c            |   7 +-
 arch/x86/kvm/vmx/capabilities.h   |  15 ++
 arch/x86/kvm/vmx/pmu_intel.c      | 320 +++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |  12 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  18 +-
 15 files changed, 564 insertions(+), 92 deletions(-)
```
#### [PATCH v4 kvmtool 00/12] Add reassignable BARs
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu May 14 15:38:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11549139
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A959D59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 15:38:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9068420756
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 15:38:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727033AbgENPik (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 11:38:40 -0400
Received: from foss.arm.com ([217.140.110.172]:39136 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726056AbgENPik (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 11:38:40 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 71B891FB;
        Thu, 14 May 2020 08:38:39 -0700 (PDT)
Received: from e121566-lin.arm.com (unknown [10.57.31.200])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3B4E93F71E;
        Thu, 14 May 2020 08:38:38 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com, maz@kernel.org
Subject: [PATCH v4 kvmtool 00/12] Add reassignable BARs
Date: Thu, 14 May 2020 16:38:17 +0100
Message-Id: <1589470709-4104-1-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvmtool uses the Linux-only dt property 'linux,pci-probe-only' to prevent
it from trying to reassign the BARs. Let's make the BARs reassignable so we
can get rid of this band-aid.

During device configuration, Linux can assign a region resource to a BAR
that temporarily overlaps with another device. This means that the code
that emulates BAR reassignment must be aware of all the registered PCI
devices. Because of this, and to avoid re-implementing the same code for
each emulated device, the algorithm for activating/deactivating emulation
as BAR addresses change lives completely inside the PCI code. Each device
registers two callback functions which are called when device emulation is
activated (for example, to activate emulation for a newly assigned BAR
address), respectively, when device emulation is deactivated (a previous
BAR address is changed, and emulation for that region must be deactivated).

Two important changes this iteration: the first 18 patches and patch 22
from v3 have been merged and I have dropped the last patch, the patch that
adds support for PCI Express 1.1 (hence the subject change). The CFI
patches have been merged and EDK2 can run right now under kvmtool with
virtio-mmio, and PCI Express breaks that. EDK2 doesn't have support for
legacy PCI, so when running under kvmtool, the PCI bus doesn't exist as far
as EDK2 is concerned. As soon as we add support for PCI Express, EDK2 will
run into the bug that I described in v3 [1]. I'll resent that patch along
with the fixes that make EDK2 work with PCI Express.

Like before, I have tested the patches on an x86_64 and arm64 machine:

1. On AMD Seattle. Tried PCI passthrough using two different guests in each
case; one with 4k pages, and one with 64k pages (the CPU doesn't have
support for 16k pages):
- Intel 82574L Gigabit Ethernet card
- Samsung 970 Pro NVME (controller registers are in the same BAR region as the
  MSIX table and PBA, I wrote a nasty hack to make it work, will try to upstream
  something after this series)
- Realtek 8168 Gigabit Ethernet card
- NVIDIA Quadro P400 (nouveau probe fails because expansion ROM emulation not
  implemented in kvmtool, I will write a fix for that)
- AMD Firepro W2100 (amdgpu driver probe fails just like on the NVIDIA card)
- Seagate Barracuda 1000GB drive and Crucial MX500 SSD attached to a PCIE to
  SATA card.

I wrote a kvm-unit-tests test that stresses the MMIO emulation locking
scheme that I implemented by spawning 4 vcpus (the Seattle machine has 8
physical CPUs) that toggle memory, and another 4 vcpus that read from the
memory region described by a BAR. I ran this under valgrind, and no
deadlocks or use-after-free errors were detected.

I've also installed an official debian iso in a virtual machine by using
the EDK2 binary that Ard posted [2] and virtio-mmio.

2. Ryzen 3900x + Gigabyte x570 Aorus Master (bios F10). Tried PCI passthrough
with a Realtek 8168 and Intel 82574L Gigabit Ethernet cards at the same time,
plus running with --sdl enabled to test VESA device emulation at the same time.
I also managed to get the guest to do bar reassignment for one device by using
the kernel command line parameter pci.resource_alignment=16@pci:10ec:8168.

Changes in v4:
* Patches 1-18 and 22 have been merged.
* Gathered Reviewed-by tags. Thank you!
* Patch #1 (was #19): added comments explaining why refcount starts at 0
  and we use a separate variable for deletion; minor changes to
  ioport__unregister to make it more similar to kvm__deregister_mmio.
* Patch #6 (was #25): assert that size is less than or equal to 4 to
  prevent any stack overruns.
* Patch #7 (was #26): rewrote it, now we prohibit the user from requesting
  more than one of --gtk, --vnc and --sdl.
* Patch #8 (was #27): fixed coding style issues, added a comment explaining
  the the MSIX table and PBA structure can share the same BAR and removed
  the assert from pci__register_bar_regions.
* Patch #10 (was #29): removed unused parameter from the functions that
  activate/deactivate BAR emulation and consolidated them into one
  function; added a comment summarizing the algorithm for BAR reassignment.
* Dropped patch #13 (was #32) for the reasons explained above.

Changes in v3:
* Patches 18, 24 and 26 are new.
* Dropped #9 "arm/pci: Fix PCI IO region" for reasons explained above.
* Reworded commit message for #12 "vfio/pci: Ignore expansion ROM BAR
  writes" to make it clear that kvmtool's implementation of VFIO doesn't
  support expansion BAR emulation.
* Moved variable declaration at the start of the function for #13
  "vfio/pci: Don't access unallocated regions".
* Patch #15 "Don't ignore errors registering a device, ioport or mmio
  emulation" uses ioport__remove consistenly.
* Reworked error cleanup for #16 "hw/vesa: Don't ignore fatal errors".
* Reworded commit message for #17 "hw/vesa: Set the size for BAR 0".
* Reworked #19 "ioport: mmio: Use a mutex and reference counting for
  locking" to also use reference counting to prevent races (and updated the
  commit message in the process).
* Added the function pci__bar_size to #20 "pci: Add helpers for BAR values
  and memory/IO space access".
* Protect mem_banks list with a mutex in #22 "vfio: Destroy memslot when
  unmapping the associated VAs"; also moved the munmap after the slot is
  destroyed, as per the KVM api.
* Dropped the rework of the vesa device in patch #27 "pci: Implement
  callbacks for toggling BAR emulation". Also added a few assert statements
  in some callbacks to make sure that they don't get called with an
  unxpected BAR number (which can only result from a coding error). Also
  return -ENOENT when kvm__deregister_mmio fails, to match ioport behavior
  and for better diagnostics.
* Dropped the PCI configuration write callback from the vesa device in #28
  "pci: Toggle BAR I/O and memory space emulation". Apparently, if we don't
  allow the guest kernel to disable BAR access, it treats the VESA device
  as a VGA boot device, instead of a regular VGA device, and Xorg cannot
  use it.
* Droped struct bar_info from #29 "pci: Implement reassignable BARs". Also
  changed pci_dev_err to pci_dev_warn in pci_{activate,deactivate}_bar,
  because the errors can be benign (they can happen because two vcpus race
  against each other to deactivate memory or I/O access, for example).
* Replaced the PCI device configuration space define with the actual
  number in #32 "arm/arm64: Add PCI Express 1.1 support". On some distros
  the defines weren't present in /usr/include/linux/pci_regs.h.
* Implemented other minor review comments.
* Gathered Reviewed-by tags.

Changes in v2:
* Patches 2, 11-18, 20, 22-27, 29 are new.
* Patches 11, 13, and 14 have been dropped.
* Reworked the way BAR reassignment is implemented.
* The patch "Add PCI Express 1.1 support" has been reworked to apply only
  to arm64. For x86 we would need ACPI support in order to advertise the
  location of the ECAM space.
* Gathered Reviewed-by tags.
* Implemented review comments.

[1] https://www.spinics.net/lists/kvm/msg211272.html
[2] https://www.spinics.net/lists/kvm/msg213842.html


Alexandru Elisei (11):
  ioport: mmio: Use a mutex and reference counting for locking
  pci: Add helpers for BAR values and memory/IO space access
  virtio/pci: Get emulated region address from BARs
  vfio: Reserve ioports when configuring the BAR
  pci: Limit configuration transaction size to 32 bits
  vfio/pci: Don't write configuration value twice
  Don't allow more than one framebuffers
  pci: Implement callbacks for toggling BAR emulation
  pci: Toggle BAR I/O and memory space emulation
  pci: Implement reassignable BARs
  vfio: Trap MMIO access to BAR addresses which aren't page aligned

Julien Thierry (1):
  arm/fdt: Remove 'linux,pci-probe-only' property

 arm/fdt.c                     |   1 -
 builtin-run.c                 |   5 +
 hw/vesa.c                     |  72 +++++---
 include/kvm/ioport.h          |   2 +
 include/kvm/pci.h             |  85 ++++++++-
 include/kvm/rbtree-interval.h |   4 +-
 include/kvm/virtio-pci.h      |   3 -
 ioport.c                      |  85 ++++++---
 mmio.c                        | 107 +++++++++---
 pci.c                         | 320 ++++++++++++++++++++++++++++++----
 powerpc/spapr_pci.c           |   2 +-
 vfio/core.c                   |  18 +-
 vfio/pci.c                    | 132 ++++++++++++--
 virtio/pci.c                  | 158 ++++++++++++-----
 14 files changed, 794 insertions(+), 200 deletions(-)
```
#### [PATCH 0/2] vfio/type1/pci: IOMMU PFNMAP invalidation
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Thu May 14 16:51:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11549323
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70E83618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 16:52:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 54CA9206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 16:52:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hwyr+/vK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726184AbgENQv7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 12:51:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:48495 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725975AbgENQv7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 12:51:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589475116;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=9NDpO6ne1oX6puFusLi9MT5jheUbCdzi50HXZXuFYME=;
        b=hwyr+/vKTbWHwZCtBx79ITs4/RpbAj7IB+BwfwyKGTl14nRKurSIclDhipNSVCpiSCfaDi
        MfQsC8LO4IRPwtk4TW6mwy5ibBrbjpzIpzNWf8GM02X3vPQMQlPFJWFRkXv0CZlXaRTxoo
        kUvsaXdblexf8pLVFDIoKodXvqksVp8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-295-xOZiXWc8OXyREJq3fKHouQ-1; Thu, 14 May 2020 12:51:54 -0400
X-MC-Unique: xOZiXWc8OXyREJq3fKHouQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 388EA1899528;
        Thu, 14 May 2020 16:51:53 +0000 (UTC)
Received: from gimli.home (ovpn-113-111.phx2.redhat.com [10.3.113.111])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 424465C1BE;
        Thu, 14 May 2020 16:51:47 +0000 (UTC)
Subject: [PATCH 0/2] vfio/type1/pci: IOMMU PFNMAP invalidation
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca,
        peterx@redhat.com
Date: Thu, 14 May 2020 10:51:46 -0600
Message-ID: <158947414729.12590.4345248265094886807.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a follow-on series to "vfio-pci: Block user access to disabled
device MMIO"[1], which extends user access blocking of disabled MMIO
ranges to include unmapping the ranges from the IOMMU.  The first patch
adds an invalidation callback path, allowing vfio bus drivers to signal
the IOMMU backend to unmap ranges with vma level granularity.  This
signaling is done both when the MMIO range becomes inaccessible due to
memory disabling, as well as when a vma is closed, making up for the
lack of tracking or pinning for non-page backed vmas.  The second
patch adds registration and testing interfaces such that the IOMMU
backend driver can test whether a given PFNMAP vma is provided by a
vfio bus driver supporting invalidation.  We can then implement more
restricted semantics to only allow PFNMAP DMA mappings when we have
such support, which becomes the new default.

Jason, if you'd like Suggested-by credit for the ideas here I'd be
glad to add it.  Thanks,

Alex

[1]https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home/
---

Alex Williamson (2):
      vfio: Introduce bus driver to IOMMU invalidation interface
      vfio: Introduce strict PFNMAP mappings


 drivers/vfio/pci/vfio_pci.c         |   41 ++++++++++-
 drivers/vfio/pci/vfio_pci_private.h |    1 
 drivers/vfio/vfio.c                 |   76 ++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c     |  130 +++++++++++++++++++++++++++--------
 include/linux/vfio.h                |    9 ++
 5 files changed, 222 insertions(+), 35 deletions(-)
```
#### [PATCH RFC 0/5] KVM: x86: KVM_MEM_ALLONES memory
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu May 14 18:05:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11549457
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BF48139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 18:05:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7096B206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 18:05:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IWhLAZ3k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726553AbgENSFw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 14:05:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:31141 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726075AbgENSFv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 14:05:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589479550;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=LLFv8mqHtnrI3q8vZushlb2smHCADXuknkmWKektqUM=;
        b=IWhLAZ3kQVdoXKwrtg/WuFUCzPYIqEFeG7TGMt6DIDxMfR/JU316ImwC1Emdn3ObRQvXLM
        +XmVkyz0FZIVEW7Txo39TPQ6mAYlQyTrrDVEx6wbC61HV0o4fyofAO7g7w8hN0C+Bp1IOm
        7ruJKi1BmauEou1ZwcYqQHR3fdXdJ2E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-476-1kpvXTpgMCi_hSasxGTFTw-1; Thu, 14 May 2020 14:05:48 -0400
X-MC-Unique: 1kpvXTpgMCi_hSasxGTFTw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7C6731005510;
        Thu, 14 May 2020 18:05:47 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.178])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 412E55D9CA;
        Thu, 14 May 2020 18:05:42 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, x86@kernel.org
Subject: [PATCH RFC 0/5] KVM: x86: KVM_MEM_ALLONES memory
Date: Thu, 14 May 2020 20:05:35 +0200
Message-Id: <20200514180540.52407-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea of the patchset was suggested by Michael S. Tsirkin.

PCIe config space can (depending on the configuration) be quite big but
usually is sparsely populated. Guest may scan it by accessing individual
device's page which, when device is missing, is supposed to have 'pci
holes' semantics: reads return '0xff' and writes get discarded. Currently,
userspace has to allocate real memory for these holes and fill them with
'0xff'. Moreover, different VMs usually require different memory.

The idea behind the feature introduced by this patch is: let's have a
single read-only page filled with '0xff' in KVM and map it to all such
PCI holes in all VMs. This will free userspace of obligation to allocate
real memory and also allow us to speed up access to these holes as we
can aggressively map the whole slot upon first fault.

RFC. I've only tested the feature with the selftest (PATCH5) on Intel/AMD
with and wiuthout EPT/NPT. I haven't tested memslot modifications yet.

Patches are against kvm/next.

Vitaly Kuznetsov (5):
  KVM: rename labels in kvm_init()
  KVM: x86: introduce KVM_MEM_ALLONES memory
  KVM: x86: move kvm_vcpu_gfn_to_memslot() out of try_async_pf()
  KVM: x86: aggressively map PTEs in KVM_MEM_ALLONES slots
  KVM: selftests: add KVM_MEM_ALLONES test

 Documentation/virt/kvm/api.rst                |  22 ++--
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/mmu/mmu.c                        |  34 ++++--
 arch/x86/kvm/mmu/paging_tmpl.h                |  30 ++++-
 arch/x86/kvm/x86.c                            |   9 +-
 include/linux/kvm_host.h                      |  15 ++-
 include/uapi/linux/kvm.h                      |   2 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  81 +++++++------
 .../kvm/x86_64/memory_region_allones.c        | 112 ++++++++++++++++++
 virt/kvm/kvm_main.c                           | 110 +++++++++++++----
 12 files changed, 342 insertions(+), 76 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/memory_region_allones.c
```
#### [kvm-unit-tests PATCH 00/11] Misc fixes and CI improvements
##### From: Thomas Huth <thuth@redhat.com>

```c
From patchwork Thu May 14 19:26:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11549593
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFC1D697
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 19:26:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B690C20643
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 19:26:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TrE0kS6I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727840AbgENT0m (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 15:26:42 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:54063 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727805AbgENT0m (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 May 2020 15:26:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589484400;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Ym4kZHOpu9FP2AlLtBKdZrfkBRnuiojLGkis8wXb9d0=;
        b=TrE0kS6INIWiRwkYKYNsx0GQl3gyeRlUSVbJtWT6fCfOFOWxxCRcgPO5+6gvUxDk7r06IY
        dSfDnGhAl8tD9QRe6T3ChnWsQz6UQeD7biSRERZetNFVnYHIYsn+/D1qP8aBVkJ42DsUcs
        KTqwt2Nq7IotoAovjS65uJjse4Qmqm4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-160-NtkrUXSwPSqMuX1UHr2xjw-1; Thu, 14 May 2020 15:26:32 -0400
X-MC-Unique: NtkrUXSwPSqMuX1UHr2xjw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B67658018A5;
        Thu, 14 May 2020 19:26:31 +0000 (UTC)
Received: from thuth.com (ovpn-112-56.ams2.redhat.com [10.36.112.56])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BD0965C254;
        Thu, 14 May 2020 19:26:28 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>,
        Drew Jones <drjones@redhat.com>,
        Bill Wendling <morbo@google.com>
Subject: [kvm-unit-tests PATCH 00/11] Misc fixes and CI improvements
Date: Thu, 14 May 2020 21:26:15 +0200
Message-Id: <20200514192626.9950-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here's a set of accumulated patches that fix the various problems with
our CI pipelines, and then update the Gitlab-CI to use Fedora 32 instead
of 30. Additionally, the new version of Clang in Fedora 32 is finally
also able to compile the kvm-unit-tests (with some small fixes included
in this series), so we can now also add a CI test with this compiler, too.

Andrew Jones (1):
  Fix out-of-tree builds

Bill Wendling (2):
  x86: use a non-negative number in shift
  x86: use inline asm to retrieve stack pointer

Mohammed Gamal (1):
  x86/access: Fix phys-bits parameter

Paolo Bonzini (1):
  x86: avoid multiply defined symbol

Thomas Huth (6):
  Fixes for the umip test
  Always compile the kvm-unit-tests with -fno-common
  Fix powerpc issue with the linker from Fedora 32
  Update the gitlab-ci to Fedora 32
  vmx_tests: Silence warning from Clang
  Compile the kvm-unit-tests also with Clang

 .gitlab-ci.yml       | 17 +++++++++++++++--
 Makefile             |  2 +-
 configure            |  8 +++-----
 lib/auxinfo.h        |  3 +--
 lib/x86/fault_test.c |  2 +-
 lib/x86/usermode.c   |  2 +-
 powerpc/flat.lds     | 19 ++++++++++++++++---
 x86/Makefile.common  |  1 +
 x86/svm_tests.c      |  2 +-
 x86/umip.c           |  6 ++++--
 x86/unittests.cfg    |  2 +-
 x86/vmx_tests.c      | 10 +++++++---
 12 files changed, 52 insertions(+), 22 deletions(-)
```
#### [PATCH Kernel v20 0/8] Add UAPIs to support migration for VFIO
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Thu May 14 20:37:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11549799
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE6FA697
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 21:11:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BB6952065C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 21:11:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="KchRK1hZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728119AbgENVLE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 17:11:04 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:14246 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727777AbgENVLD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 17:11:03 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebdb35c0001>; Thu, 14 May 2020 14:08:44 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 14 May 2020 14:11:02 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 14 May 2020 14:11:02 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 14 May
 2020 21:11:01 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 14 May 2020 21:10:54 +0000
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
Subject: [PATCH Kernel v20 0/8] Add UAPIs to support migration for VFIO
 devices
Date: Fri, 15 May 2020 02:07:39 +0530
Message-ID: <1589488667-9683-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589490524; bh=DgfFVf9CfgfR9vafvaAWE6FVdgjJMQGPGDhGSFAK7fw=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=KchRK1hZ//d4E/7H7DBQwEnJ5fW/h2m5XepBKVrOEdwXGcAyLbg9JOsyWS99ccwwK
         cLxcnzLTmAv+OuVrjxvY3tTbrNlAWBurJZYoOFMLI70zRaetQLvYXmmJRiez9U2TFg
         LnrAepFpK2rJVBCPdEAKKqx48v9GRU8n5BNlTmFbhC9eQgJ/jOzhqsrOfjAVEW9lJE
         DC1iPl386tE283OFzQZ1bichc3ineWllZlczJ9Gb94AEXCF/mcbZTQm6HCm4zjcVTf
         KL0J42rij8nonpxFHXCtxE8x9qvu3F5YwQXMPiNzcC9yKuBV2TIUU62o2RRJNPyYUb
         ptf+FssnG5TxQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
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

* Patch 8 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v19 -> v20
- Fixed ioctl to get dirty bitmap to get bitmap of multiple vfio_dmas
- Fixed unmap ioctl to get dirty bitmap of multiple vfio_dmas.
- Removed flag definition from migration capability.

v18 -> v19
- Updated migration capability with supported page sizes bitmap for dirty
  page tracking and  maximum bitmap size supported by kernel module.
- Added patch to calculate and cache pgsize_bitmap when iommu->domain_list
  is updated.
- Removed extra buffers added in previous version for bitmap manipulation
  and optimised the code.

v17 -> v18
- Add migration capability to the capability chain for VFIO_IOMMU_GET_INFO
  ioctl
- Updated UMAP_DMA ioctl to return bitmap of multiple vfio_dma

v16 -> v17
- Fixed errors reported by kbuild test robot <lkp@intel.com> on i386

v15 -> v16
- Minor edits and nit picks (Auger Eric)
- On copying bitmap to user, re-populated bitmap only for pinned pages,
  excluding unmapped pages and CPU dirtied pages.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

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



Kirti Wankhede (8):
  vfio: UAPI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Cache pgsize_bitmap in struct vfio_iommu
  vfio iommu: Add ioctl definition for dirty pages tracking
  vfio iommu: Implementation of ioctl for dirty pages tracking
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Add migration capability to report supported features
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 565 ++++++++++++++++++++++++++++++++++++----
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 315 ++++++++++++++++++++++
 4 files changed, 838 insertions(+), 59 deletions(-)
```
