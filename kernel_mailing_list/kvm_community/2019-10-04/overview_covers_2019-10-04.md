

#### [kvm-unit-tests PATCH v2 0/6] arm: Use stable test output lines
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Fri Oct  4 14:18:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11174611
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB14013BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 14:18:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9005121D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 14:18:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388883AbfJDOSj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 10:18:39 -0400
Received: from foss.arm.com ([217.140.110.172]:46212 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388625AbfJDOSj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 10:18:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 85A441597;
        Fri,  4 Oct 2019 07:18:38 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B82E13F68E;
        Fri,  4 Oct 2019 07:18:37 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH v2 0/6] arm: Use stable test output lines
Date: Fri,  4 Oct 2019 15:18:23 +0100
Message-Id: <20191004141829.87135-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

a minor update addressing Drew's comments.
Changelog v1 ... v2:
- rewording IPI test names
- reordering number-of-CPUs reporting
- add Drew's Reviewed-by: tags

Cheers,
Andre.

-------------------------------------------
When using kvm-unit-tests inside automated testing frameworks,
variable test naming becomes a problem. Some frameworks recognise tests
by their test output line and group the outputs from various runs for
statistical and reporting purposes. Having variable output like timer
values in there spoils this approach. Also the test name should be
somewhat self-explanatory, which is not true for every test.
Some examples highlighting the problem (TAP output from run-tests.sh -t):
ok 1 - selftest: setup: smp: nr_cpus = 2
ok 2 - selftest: setup: mem: size = 256 MB
ok 8 - selftest: smp: CPU(  1) mpidr=0080000001
ok 9 - selftest: smp: CPU(  2) mpidr=0080000002
ok 54 - gicv2: mmio: ITARGETSR: byte writes successful (0x1f => 0x01010001)
ok 55 - gicv2: mmio: all 3 CPUs have interrupts
ok 73 - invalid-function
ok 76 - cpu-on
ok 90 - ptimer-busy-loop: timer has expired (-8445)

This series aims to fix most of the problems, by making the actual test
report output line stable. I think this is best practises in the testing
world, at least when using TAP. We still retain the full information, by
moving every variable output into INFO: lines (which are still logged,
but typically filtered for automated processing).
The above lines now look like this:
ok 1 - selftest: setup: smp: number of CPUs matches expectation
ok 2 - selftest: setup: mem: memory size matches expectation
ok 8 - selftest: smp: MPIDR test on all CPUs
ok 49 - gicv2: mmio: ITARGETSR: byte writes successful
ok 50 - gicv2: mmio: all CPUs have interrupts
ok 68 - psci: invalid-function
ok 71 - psci: cpu-on
ok 85 - ptimer-busy-loop: timer has expired

Looks a bit more boring, but it's nicer for automated processing and
logging.

I am open for a discussion about the general approach, thus this is
dealing with ARM tests for now only.

Looking forward to any feedback!

Andre Przywara (6):
  arm: gic: check_acked: add test description
  arm: gic: Split variable output data from test name
  arm: timer: Split variable output data from test name
  arm: selftest: Split variable output data from test name
  arm: selftest: Make MPIDR output stable
  arm: Add missing test name prefix calls

 arm/gic.c      | 64 ++++++++++++++++++++++++++++++--------------------
 arm/pci-test.c |  2 ++
 arm/psci.c     |  2 ++
 arm/selftest.c | 23 ++++++++++++++----
 arm/timer.c    |  3 ++-
 5 files changed, 62 insertions(+), 32 deletions(-)
```
#### [PATCH 00/16] x86/cpu: Clean up handling of VMX features
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Oct  4 21:55:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11175321
Return-Path: <SRS0=SJcU=X5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 590F71920
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 21:56:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 41D04222C8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Oct 2019 21:56:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731380AbfJDV41 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Oct 2019 17:56:27 -0400
Received: from mga09.intel.com ([134.134.136.24]:5964 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727647AbfJDV41 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Oct 2019 17:56:27 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Oct 2019 14:56:26 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,257,1566889200";
   d="scan'208";a="191710644"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga008.fm.intel.com with ESMTP; 04 Oct 2019 14:56:25 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, x86@kernel.org,
 Peter Zijlstra <peterz@infradead.org>,
 Arnaldo Carvalho de Melo <acme@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Tony Luck <tony.luck@intel.com>, Tony W Wang-oc <TonyWWang-oc@zhaoxin.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-edac@vger.kernel.org,
        Borislav Petkov <bp@suse.de>,
        Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH 00/16] x86/cpu: Clean up handling of VMX features
Date: Fri,  4 Oct 2019 14:55:59 -0700
Message-Id: <20191004215615.5479-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up a handful of interrelated warts in the kernel's handling of VMX:

  - Enable VMX in IA32_FEATURE_CONTROL during boot instead of on-demand
    during KVM load to avoid future contention over writing the MSR.

  - Rework VMX feature reporting so that it is accurate and up-to-date,
    now and in the future.

  - Consolidate code across CPUs that support VMX.

The patches are based on tip/x86/cpu, commit
 
  87d6021b8143 ("x86/math-emu: Limit MATH_EMULATION to 486SX compatibles")

Please let me know if you'd prefer not to receive the full patch set on
future versions of the series.  I cc'd everyone on all patches to provide
the full picture, e.g. the motivation behind things like the perf patch.


This series stems from two separate but related issues.  The first issue,
pointed out by Boris in the SGX enabling series[1], is that the kernel
currently doesn't ensure the IA32_FEATURE_CONTROL MSR is configured during
boot.  The second issue is that the kernel's reporting of VMX features is
stale, potentially inaccurate, and difficult to maintain.

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


Sean Christopherson (16):
  x86/intel: Initialize IA32_FEATURE_CONTROL MSR at boot
  x86/mce: WARN once if IA32_FEATURE_CONTROL MSR is left unlocked
  x86/centaur: Use common IA32_FEATURE_CONTROL MSR initialization
  x86/zhaoxin: Use common IA32_FEATURE_CONTROL MSR initialization
  KVM: VMX: Drop initialization of IA32_FEATURE_CONTROL MSR
  x86/cpu: Clear VMX feature flag if VMX is not fully enabled
  KVM: VMX: Use VMX feature flag to query BIOS enabling
  KVM: VMX: Check for full VMX support when verifying CPU compatibility
  x86/vmx: Introduce VMX_FEATURES_*
  x86/cpu: Detect VMX features on Intel, Centaur and Zhaoxin CPUs
  x86/cpu: Print VMX features as separate line item in /proc/cpuinfo
  x86/cpufeatures: Drop synthetic VMX feature flags
  KVM: VMX: Use VMX_FEATURE_* flags to define VMCS control bits
  x86/cpufeatures: Clean up synthetic virtualization flags
  perf/x86: Provide stubs of KVM helpers for non-Intel CPUs
  KVM: VMX: Allow KVM_INTEL when building for Centaur and/or Zhaoxin
    CPUs

 MAINTAINERS                           |   2 +-
 arch/x86/Kconfig.cpu                  |   8 ++
 arch/x86/boot/mkcpustr.c              |   1 +
 arch/x86/include/asm/cpufeatures.h    |  15 +---
 arch/x86/include/asm/perf_event.h     |  22 +++--
 arch/x86/include/asm/processor.h      |   4 +
 arch/x86/include/asm/vmx.h            | 105 +++++++++++-----------
 arch/x86/include/asm/vmxfeatures.h    | 121 ++++++++++++++++++++++++++
 arch/x86/kernel/cpu/Makefile          |   6 +-
 arch/x86/kernel/cpu/centaur.c         |  35 +-------
 arch/x86/kernel/cpu/common.c          |   3 +
 arch/x86/kernel/cpu/cpu.h             |   4 +
 arch/x86/kernel/cpu/feature_control.c | 106 ++++++++++++++++++++++
 arch/x86/kernel/cpu/intel.c           |  49 +----------
 arch/x86/kernel/cpu/mce/intel.c       |   7 +-
 arch/x86/kernel/cpu/mkcapflags.sh     |  15 +++-
 arch/x86/kernel/cpu/proc.c            |  15 ++++
 arch/x86/kernel/cpu/zhaoxin.c         |  35 +-------
 arch/x86/kvm/Kconfig                  |   9 +-
 arch/x86/kvm/vmx/vmx.c                |  41 ++-------
 20 files changed, 368 insertions(+), 235 deletions(-)
 create mode 100644 arch/x86/include/asm/vmxfeatures.h
 create mode 100644 arch/x86/kernel/cpu/feature_control.c
```
