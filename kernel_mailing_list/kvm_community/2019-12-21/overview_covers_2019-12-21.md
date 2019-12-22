

#### [PATCH RESEND v2 00/17] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Sat Dec 21 01:49:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306589
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6A05138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 01:50:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AA0E720866
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 01:50:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MsId0a/6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726799AbfLUBtu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 20:49:50 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:39150 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726634AbfLUBtt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Dec 2019 20:49:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576892986;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=MsId0a/6j24DN63B/5fJ2wpFEAVesDYxlh50HwUTZ6Ca5SevTDHhBCpEjDpX6RNfNh4jEf
        n5cbQ/wkHqHksFZBvkihQcW2t6waKjDny+/BnVyS8XuwJjnbOo0hGBSPoNWxOLTaSkC3xU
        7S1sa81UxT3rE2KsvUfh2935Jp8pfpk=
Received: from mail-qt1-f199.google.com (mail-qt1-f199.google.com
 [209.85.160.199]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-127-E78Z2xGcMoajxeW9d4Pt7g-1; Fri, 20 Dec 2019 20:49:43 -0500
X-MC-Unique: E78Z2xGcMoajxeW9d4Pt7g-1
Received: by mail-qt1-f199.google.com with SMTP id m30so7206939qtb.2
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 17:49:43 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=c18e8rKSv8325pvrQMU+fALYc7WN/wrlvlWhuo6mWrkTfZ3voksgLxTUb7azUWNsWl
         4EAusXHn8X4d/xehpTzZZMNUDdX0dvN/Xvb2Q3K2lk2+0c2EkQHY/KMFoZOvxFvbeY4k
         84DPFZX4JEuZBc7Zm86/ftXJFTenbaJQh25AKtpKXiq1NwvqUBn1SMaf4GsHRS+/0fBJ
         GIRtogrktcTFQJcX6AKL8OxXtbuVhItR6YaVs5KR4iXzvY7g5mH5EEyqFMcYk7ZUFqv4
         sGnVSw/vKE2CatJltaAlD+J3CGj3nJpcoDRv90iYJzKmnx4/hYMLO+JSOcvGHJYRpupy
         zD4w==
X-Gm-Message-State: APjAAAXFK5zzUm/iXcQXnpruG589RY4gIdafXxIVGl2KwsuAFlXb1aqd
        SH7OnSuwgE6Y4IpAlW0Vq5OG9M8cMB3KbopKtEiTi2W4Xk7lM3V/wIA62aSSy7KgNnKDsMz5yMJ
        H4DYtvC/+4ZPH
X-Received: by 2002:a37:674a:: with SMTP id
 b71mr16718552qkc.471.1576892982601;
        Fri, 20 Dec 2019 17:49:42 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzfv9xjdg8Jai4eu6KsWDYVzIgo0LO/qzp6gAZdszcZHmYwWLIVMeCSfyKeBtV2i0p9e1hhTg==
X-Received: by 2002:a37:674a:: with SMTP id
 b71mr16718528qkc.471.1576892982219;
        Fri, 20 Dec 2019 17:49:42 -0800 (PST)
Received: from xz-x1.hitronhub.home
 (CPEf81d0fb19163-CMf81d0fb19160.cpe.net.fido.ca. [72.137.123.47])
        by smtp.gmail.com with ESMTPSA id
 e21sm3396932qkm.55.2019.12.20.17.49.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 17:49:41 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH RESEND v2 00/17] KVM: Dirty ring interface
Date: Fri, 20 Dec 2019 20:49:21 -0500
Message-Id: <20191221014938.58831-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring
(based on 5.4.0)

This is v2 of the dirty ring series, and also the first non-RFC
version of it.  I didn't put a changelog from v1-rfc because I feel
like it would be easier to go into the patchset comparing to read that
lengthy and probably helpless changelog.  However I do like to do a
summary here on what has majorly changed, and also some conclusions on
the previous v1 discussions.

======================

* Per-vm ring is dropped

For x86 (which is still the major focus for now), we found that kvmgt
is probably the only one that still writes to the guest without a vcpu
context.  It would be a complete pity if we keep the per-vm ring only
for kvmgt (who shouldn't write directly to guest via kvm api after
all...), so remove it.  Work should be ongoing in parallel to refactor
kvmgt to not use kvm apis like kvm_write_guest().

However I don't want to break kvmgt before it's fixed.  So this series
uses an interim way to solve this by fallback no-vcpu-context writes
to vcpu0 if there is.  So we will keep the interface clean (per-vcpu
only), while we don't break the code base.  After kvmgt is fixed, we
can probably even drop this special fallback and kvm->dirty_ring_lock.

* Waitqueue is still kept (for now)

We did plan to drop the waitqueue, however again if with kvmgt we
still have chance to ful-fill a ring (and I feel like it'll definitely
happen if we migrate a kvmgt guest).  This series will only trigger
the waitqueue mechanism if it's the special case (no-vcpu-context) and
actually it naturally avoids another mmu lock deadlock issue I've
encountered, which is good.

For vcpu context writes, now the series is even more strict that we'll
directly fail the KVM_RUN if the dirty ring is soft full, until the
userspace collects the dirty rings first.  That'll guarantee the ring
will never be full.  With that, I dropped KVM_REQ_DIRTY_RING_FULL
together because then it's not needed.

Potentially this could still also be used by ARM when there're code
paths that dump the ARM device information to the guests
(e.g. KVM_DEV_ARM_ITS_SAVE_TABLES).  We'll see.  No matter what, even
if the code is there, x86 (as long as without kvmgt) should never
trigger waitqueue.

Although the waitqueue is kept, I dropped the complete waitqueue test,
simply because now I can never trigger it without kvmgt...

* Why not virtio?

There's already some discussion during v1 patchset on whether it's
good to use virtio for the data path of delivering dirty pages [1].
I'd confess the only thing that we might consider to use is the vring
layout (because virtqueue is tightly bound to devices, while we don't
have a device contet here), however it's a pity that even we only use
the most low-level vring api it'll be at least iov based which is
already an overkill for dirty ring (which is literally an array of
addresses).  So I just kept things easy.

======================

About the patchset:

Patch 1-5:    Mostly cleanups
Patch 6,7:    Prepare for the dirty ring interface
Patch 8-10:   Dirty ring implementation (majorly patch 8)
Patch 11-17:  Test cases update

Please have a look, thanks.

[1] V1 is here: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (16):
  KVM: Remove kvm_read_guest_atomic()
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Cache as_id in kvm_memory_slot
  KVM: Add build-time error check on kvm_run size
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.txt                |  96 ++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   3 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu.c                            |   6 +
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            |   9 +
 include/linux/kvm_dirty_ring.h                |  57 +++
 include/linux/kvm_host.h                      |  44 +-
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  31 ++
 tools/include/uapi/linux/kvm.h                |  36 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 420 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  64 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   3 +
 virt/kvm/arm/arch_timer.c                     |   2 +-
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 201 +++++++++
 virt/kvm/kvm_main.c                           | 269 +++++++++--
 27 files changed, 1274 insertions(+), 145 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v5 00/19] x86/cpu: Clean up handling of VMX features
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Sat Dec 21 04:44:54 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11306783
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C632514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 04:47:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B6A221927
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 04:47:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726750AbfLUEpx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 23:45:53 -0500
Received: from mga03.intel.com ([134.134.136.65]:31824 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726613AbfLUEpw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 23:45:52 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Dec 2019 20:45:50 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,338,1571727600";
   d="scan'208";a="222620045"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 20 Dec 2019 20:45:50 -0800
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
 Jacob Pan <jacob.jun.pan@linux.intel.com>, Len Brown <lenb@kernel.org>,
 Shuah Khan <shuah@kernel.org>, linux-kernel@vger.kernel.org,
 kvm@vger.kernel.org, linux-edac@vger.kernel.org, linux-pm@vger.kernel.org,
 linux-kselftest@vger.kernel.org, Borislav Petkov <bp@suse.de>,
 Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Subject: [PATCH v5 00/19] x86/cpu: Clean up handling of VMX features
Date: Fri, 20 Dec 2019 20:44:54 -0800
Message-Id: <20191221044513.21680-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
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
pointed out by Boris in the SGX enabling series[*], is that the kernel
currently doesn't ensure the IA32_FEATURE_CONTROL MSR is configured during
boot.  The second issue is that the kernel's reporting of VMX features is
stale, potentially inaccurate, and difficult to maintain.

v5:
  - Rebase to tip/master, ec7b10f2d023 ("Merge branch 'x86/cleanups'")
  - Fix a missing IA32_FEAT_CTL change in the idle driver (which amusingly
    reads the MSR to deal with SGX). [kbuild test robot]
  - Tweak the displayed names for VMX flags. [Boris, Paolo, Liran]
  - Add a comment above the raw rdmsr() calls in the VMX feature flag
    parsing. [Boris]
  - Fix a few changelog typos. [Boris]
  - Use VMX_F() instead of F() for the VMX flag extraction macro. [Boris]
  - Drop 'PROC' from the PRIMARY_CTLS and SECONDARY_CTLS enums to keep
    line lengths sane.
  - Keep the pr_fmt at the top of feat_ctl.c when the flag populating code
    is introduced (previously got buried in the middle of the file).

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
  - Fix a changelog typo [Boris].

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

[*] https://lkml.kernel.org/r/20190925085156.GA3891@zn.tnic

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
 arch/x86/kernel/cpu/feat_ctl.c                | 144 ++++
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
 drivers/idle/intel_idle.c                     |   2 +-
 tools/arch/x86/include/asm/msr-index.h        |  14 +-
 tools/power/x86/turbostat/turbostat.c         |   4 +-
 tools/testing/selftests/kvm/Makefile          |   4 +-
 .../selftests/kvm/include/x86_64/processor.h  | 726 +-----------------
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   8 +-
 30 files changed, 420 insertions(+), 987 deletions(-)
 create mode 100644 arch/x86/include/asm/vmxfeatures.h
 create mode 100644 arch/x86/kernel/cpu/feat_ctl.c
```
#### [PATCH 0/8] Convert the intel iommu driver to the dma-iommu api
##### From: Tom Murphy <murphyt7@tcd.ie>

```c
From patchwork Sat Dec 21 15:03:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tom Murphy <murphyt7@tcd.ie>
X-Patchwork-Id: 11306995
Return-Path: <SRS0=aF81=2L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6438E138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:04:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 37F262070C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Dec 2019 15:04:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tcd-ie.20150623.gappssmtp.com
 header.i=@tcd-ie.20150623.gappssmtp.com header.b="neV87FDz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726802AbfLUPEQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Dec 2019 10:04:16 -0500
Received: from mail-ed1-f68.google.com ([209.85.208.68]:39374 "EHLO
        mail-ed1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727090AbfLUPEP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Dec 2019 10:04:15 -0500
Received: by mail-ed1-f68.google.com with SMTP id t17so11390861eds.6
        for <kvm@vger.kernel.org>; Sat, 21 Dec 2019 07:04:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=tcd-ie.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Wrv1jKXMHqqWHNzOL/6EYVPe/DHxphPiIOsjGB9s2BI=;
        b=neV87FDzcGxEtXMGvHrtTmbUOLtYtU+7I9MOQqfdQ+hsUXA8p8rI9n+KxmtaOLCADC
         oqzQwM+E41sGIEhE26+tkV5wTeVqusoqBdHCsFTHLhlkaDp++P9e9+/8rjVQr/Wsf9hN
         kPbAbKsiSsT63+7OMPlwjagzVfM0swjA056jVZJc1EqBSggoujvgAZK6bAD1VYJYtXeD
         ft7DHsq/EkMf9BhDvmD36g1hqGBWyqNIVG1DfNnWrfT4s1zi4GMzfbjEz0QIobV6kmY1
         laD6eUJQwGoQ0UWRg2PHTAA5VDA0M3C2Amsc74c9QymUHI36GRshkavBOusZCLhvlyeT
         csig==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Wrv1jKXMHqqWHNzOL/6EYVPe/DHxphPiIOsjGB9s2BI=;
        b=ryzglJDLABVyhOEbVr2Ywgqcoj4U1WfvXsXHqljndMCsOlVCih++HWHXwe8p3rvayC
         r+9Fg8r+obXw+2rbezbwRTo92mXa1h0FLKufPa+wZTx0+9iX7MeVvnF5pzf3O5zGs1fo
         0hQ6u2pJ0/jJtvWdFsQuIgyA6WPXgUR372Y88lcnRnIbc4fi5fGfF6U9Cqf4pK+kvRWk
         kYUZgrKssSLh7zJ+AOsYhFQexeEcqtDwiEHtK+oAaGIEv2zyt0mtfUQJAsbfC6yFat1R
         acjmGB+rN/KAW33YEBoRDD7VNrdC/9r6ttt+hbVAy3FU9UnerZPQ0VfFF2EFyeKLOtSk
         HaBw==
X-Gm-Message-State: APjAAAUOimnDWn/YDFowIbjPXU2L01DncW9gcuIBVvOGQxkSftkoBKG4
        y3wPn0lo+cnR4gZB6+anusX4kw==
X-Google-Smtp-Source: 
 APXvYqzVFV+nAZt2efpFSBwn8fHDfarT+lNLK2u/m6P0Ib5tJlSKcUyhpXmrMgKd3Rdn4f4Yf8qeow==
X-Received: by 2002:a17:906:2e53:: with SMTP id
 r19mr22235209eji.306.1576940652743;
        Sat, 21 Dec 2019 07:04:12 -0800 (PST)
Received: from localhost.localdomain ([80.233.37.20])
        by smtp.googlemail.com with ESMTPSA id
 u13sm1517639ejz.69.2019.12.21.07.04.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 21 Dec 2019 07:04:12 -0800 (PST)
From: Tom Murphy <murphyt7@tcd.ie>
To: iommu@lists.linux-foundation.org
Cc: Tom Murphy <murphyt7@tcd.ie>,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Marek Szyprowski <m.szyprowski@samsung.com>,
        Kukjin Kim <kgene@kernel.org>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Andy Gross <agross@kernel.org>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Matthias Brugger <matthias.bgg@gmail.com>,
        Rob Clark <robdclark@gmail.com>,
        Heiko Stuebner <heiko@sntech.de>,
        Gerald Schaefer <gerald.schaefer@de.ibm.com>,
        Thierry Reding <thierry.reding@gmail.com>,
        Jonathan Hunter <jonathanh@nvidia.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Julien Grall <julien.grall@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        Eric Auger <eric.auger@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        intel-gfx@lists.freedesktop.org, dri-devel@lists.freedesktop.org,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        linux-mediatek@lists.infradead.org,
        linux-rockchip@lists.infradead.org, linux-s390@vger.kernel.org,
        linux-tegra@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH 0/8] Convert the intel iommu driver to the dma-iommu api
Date: Sat, 21 Dec 2019 15:03:52 +0000
Message-Id: <20191221150402.13868-1-murphyt7@tcd.ie>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset converts the intel iommu driver to the dma-iommu api.

While converting the driver I exposed a bug in the intel i915 driver which causes a huge amount of artifacts on the screen of my laptop. You can see a picture of it here:
https://github.com/pippy360/kernelPatches/blob/master/IMG_20191219_225922.jpg

This issue is most likely in the i915 driver and is most likely caused by the driver not respecting the return value of the dma_map_ops::map_sg function. You can see the driver ignoring the return value here:
https://github.com/torvalds/linux/blob/7e0165b2f1a912a06e381e91f0f4e495f4ac3736/drivers/gpu/drm/i915/gem/i915_gem_dmabuf.c#L51

Previously this didn’t cause issues because the intel map_sg always returned the same number of elements as the input scatter gather list but with the change to this dma-iommu api this is no longer the case. I wasn’t able to track the bug down to a specific line of code unfortunately.  

Could someone from the intel team look at this?


I have been testing on a lenovo x1 carbon 5th generation. Let me know if there’s any more information you need.

To allow my patch set to be tested I have added a patch (patch 8/8) in this series to disable combining sg segments in the dma-iommu api which fixes the bug but it doesn't fix the actual problem.

As part of this patch series I copied the intel bounce buffer code to the dma-iommu path. The addition of the bounce buffer code took me by surprise. I did most of my development on this patch series before the bounce buffer code was added and my reimplementation in the dma-iommu path is very rushed and not properly tested but I’m running out of time to work on this patch set.

On top of that I also didn’t port over the intel tracing code from this commit:
https://github.com/torvalds/linux/commit/3b53034c268d550d9e8522e613a14ab53b8840d8#diff-6b3e7c4993f05e76331e463ab1fc87e1
So all the work in that commit is now wasted. The code will need to be removed and reimplemented in the dma-iommu path. I would like to take the time to do this but I really don’t have the time at the moment and I want to get these changes out before the iommu code changes any more.


Tom Murphy (8):
  iommu/vt-d: clean up 32bit si_domain assignment
  iommu/vt-d: Use default dma_direct_* mapping functions for direct
    mapped devices
  iommu/vt-d: Remove IOVA handling code from non-dma_ops path
  iommu: Handle freelists when using deferred flushing in iommu drivers
  iommu: Add iommu_dma_free_cpu_cached_iovas function
  iommu: allow the dma-iommu api to use bounce buffers
  iommu/vt-d: Convert intel iommu driver to the iommu ops
  DO NOT MERGE: iommu: disable list appending in dma-iommu

 drivers/iommu/Kconfig           |   1 +
 drivers/iommu/amd_iommu.c       |  14 +-
 drivers/iommu/arm-smmu-v3.c     |   3 +-
 drivers/iommu/arm-smmu.c        |   3 +-
 drivers/iommu/dma-iommu.c       | 183 +++++--
 drivers/iommu/exynos-iommu.c    |   3 +-
 drivers/iommu/intel-iommu.c     | 936 ++++----------------------------
 drivers/iommu/iommu.c           |  39 +-
 drivers/iommu/ipmmu-vmsa.c      |   3 +-
 drivers/iommu/msm_iommu.c       |   3 +-
 drivers/iommu/mtk_iommu.c       |   3 +-
 drivers/iommu/mtk_iommu_v1.c    |   3 +-
 drivers/iommu/omap-iommu.c      |   3 +-
 drivers/iommu/qcom_iommu.c      |   3 +-
 drivers/iommu/rockchip-iommu.c  |   3 +-
 drivers/iommu/s390-iommu.c      |   3 +-
 drivers/iommu/tegra-gart.c      |   3 +-
 drivers/iommu/tegra-smmu.c      |   3 +-
 drivers/iommu/virtio-iommu.c    |   3 +-
 drivers/vfio/vfio_iommu_type1.c |   2 +-
 include/linux/dma-iommu.h       |   3 +
 include/linux/intel-iommu.h     |   1 -
 include/linux/iommu.h           |  32 +-
 23 files changed, 345 insertions(+), 908 deletions(-)
```
