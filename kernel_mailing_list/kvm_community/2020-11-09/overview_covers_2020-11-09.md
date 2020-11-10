

#### [PATCH RFC v2 00/17] KVM: x86/pmu: Add support to enable Guest PEBS
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon Nov  9 02:12:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11890309
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9BA87C56201
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 59815206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729080AbgKICQu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 8 Nov 2020 21:16:50 -0500
Received: from mga01.intel.com ([192.55.52.88]:64875 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728006AbgKICQu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Nov 2020 21:16:50 -0500
IronPort-SDR: 
 cydSXvtAB7ITKVZ3/N01yR4Ub1rjyqMlmi0LCWhzT6oCJyXKhjqX22EfXxg6FXwkEgL9e/JJx4
 5JnvKXFsSmpw==
X-IronPort-AV: E=McAfee;i="6000,8403,9799"; a="187684535"
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="187684535"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Nov 2020 18:16:49 -0800
IronPort-SDR: 
 0isBKzzx4pbgmXS6CNxAlimbfIJmLVm3/pD/NOnTEAG5/wgQbLuX7BUMI+2mQtqsjNNKGYXWII
 CBxqjP5wc+Lw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="540646088"
Received: from e5-2699-v4-likexu.sh.intel.com ([10.239.48.39])
  by orsmga005.jf.intel.com with ESMTP; 08 Nov 2020 18:16:45 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Kan Liang <kan.liang@linux.intel.com>, luwei.kang@intel.com,
        Thomas Gleixner <tglx@linutronix.de>, wei.w.wang@intel.com,
        Tony Luck <tony.luck@intel.com>,
        Stephane Eranian <eranian@google.com>,
        Mark Gross <mgross@linux.intel.com>,
        Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH RFC v2 00/17] KVM: x86/pmu: Add support to enable Guest PEBS
 via DS
Date: Mon,  9 Nov 2020 10:12:37 +0800
Message-Id: <20201109021254.79755-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Precise Event Based Sampling(PEBS) supported on Intel Ice Lake server
platforms can provide an architectural state of the instruction executed
after the instruction that caused the event. This patch set enables the
the PEBS via DS feature for KVM (also non) Linux guest on the Ice Lake.
The Linux guest can use PEBS feature like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

If the counter_freezing is not enabled on the host, the guest PEBS will
be disabled on purpose when host is using PEBS facility. By default,
KVM disables the co-existence of guest PEBS and host PEBS.

The whole patch set could be divided into three parts and the first two
parts enables the basic PEBS via DS feature which could be considered
to be merged and no regression about host perf is expected.

- part 1: patch 0001-0003: preparation and minor fixes for vPMU overall;
- part 2: patch 0004-0012: enable guest PEBS when the guest PEBS counters
are not cross-mapped, which is the most usual case in practice;
- part 3: patch 0012-0017: enable guest PEBS when cross-mapping happens;

Compared to the first version, an important change here is the removal
of the forced 1-1 mapping of the virtual to physical PMC and we handle
the cross-mapping issue carefully in the part 3 which may address
artificial competition concern from PeterZ.

In general, there are 2 code paths to emulate guest PEBS facility.

1) Fast path (part 2)

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
It works as the 1-1 mapping that we did in the first version.

2) Slow path (part 3)

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure. Large PEBS
needs to be disabled by KVM rewriting the pebs_interrupt_threshold
filed in DS to only one record in the slow path. 

This is because a guest may implicitly drain PEBS buffer, e.g.,
context switch. KVM doesn't get a chance to update the PEBS buffer.
The physical PMC index will confuse the guest. The difficulty comes
when multiple events get rescheduled inside the guest.

Hence disabling large PEBS in this case might be an easy and safe way
to keep it corrects as an initial step here. 

We don't expect this to break any guest code, which can generally tolerate
earlier PMIs. In the fast path with 1:1 mapping this is not needed.

The rewriting work is performed before delivering a vPMI to the guest to
notify the guest to read the record (before entering the guest, where
interrupt has been disabled so no counter reschedule would happen
at that point on the host).

In summary, this patch set enables the guest PEBS to retrieve the correct
information from its own PEBS records on the Ice Lake server platforms
when host is not using PEBS facility at the same time. And we expect it
should work when migrating to another Ice Lake.

Here are the results of pebs test from guest/host for same workload:

perf report on guest:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1473377250
# Overhead  Command   Shared Object      Symbol
  57.74%  br_instr  br_instr           [.] lfsr_cond
  41.40%  br_instr  br_instr           [.] cmp_end
   0.21%  br_instr  [kernel.kallsyms]  [k] __lock_acquire

perf report on host:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1462721386
# Overhead  Command   Shared Object     Symbol
  57.90%  br_instr  br_instr          [.] lfsr_cond
  41.95%  br_instr  br_instr          [.] cmp_end
   0.05%  br_instr  [kernel.vmlinux]  [k] lock_acquire
   
Conclusion: the profiling results on the guest are similar to that on the host.

Please check more details in each commit and feel free to comment.

v1->v2 Changelog:
- drop the 1:1 counter mapping proposal for PeterZ;
- *add the guest PEBS records rewrite proposal* (new patch 0013 - 0017);
- drop the co-existence of guest PEBS and host PEBS w/o counter_freezing;
- drop the auto-reload configuration for guest PEBS event;
- use attr.precise_ip = 3 for guest PEBS PDIR counter;
- move msr-switch code to perf_guest_get_msrs();
- new user interface to dis/enable guest PEBS via IA32_PERF_CAPABILITIES;
- general vPMU related fixup patches (patch 0001 - 0003);
- rebased to the latest kvm-queue;

Previous:
https://lore.kernel.org/kvm/1583431025-19802-1-git-send-email-luwei.kang@intel.com

Like Xu (17):
  KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
  KVM: vmx/pmu: Use IA32_PERF_CAPABILITIES to adjust features visibility
  KVM: x86/pmu: Introduce the ctrl_mask value for fixed counter
  perf: x86/ds: Handle guest PEBS overflow PMI and inject it to guest
  KVM: x86/pmu: Reprogram guest PEBS event to emulate guest PEBS counter
  KVM: x86/pmu: Add IA32_PEBS_ENABLE MSR emulation for extended PEBS
  KVM: x86/pmu: Add IA32_DS_AREA MSR emulation to manage guest DS buffer
  KVM: x86/pmu: Add PEBS_DATA_CFG MSR emulation to support adaptive PEBS
  KVM: x86: Set PEBS_UNAVAIL in IA32_MISC_ENABLE when PEBS is enabled
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64
  KVM: x86/pmu: Adjust precise_ip to emulate Ice Lake guest PDIR counter
  KVM: x86/pmu: Disable guest PEBS when counters are cross-mapped
  KVM: x86/pmu: Add hook to emulate pebs for cross-mapped counters
  KVM: vmx/pmu: Limit pebs_interrupt_threshold in the guest DS area
  KVM: vmx/pmu: Rewrite applicable_counters field in the guest PEBS record
  KVM: x86/pmu: Save guest pebs reset value when a pebs counter is configured
  KVM: x86/pmu: Adjust guest DS pebs reset counter values for mapped counter

 arch/x86/events/intel/core.c     |  46 +++++
 arch/x86/events/intel/ds.c       |  64 +++++++
 arch/x86/include/asm/kvm_host.h  |  15 ++
 arch/x86/include/asm/msr-index.h |   6 +
 arch/x86/kvm/pmu.c               |  91 +++++++--
 arch/x86/kvm/pmu.h               |  20 ++
 arch/x86/kvm/vmx/capabilities.h  |  17 +-
 arch/x86/kvm/vmx/pmu_intel.c     | 313 ++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c           |  29 +++
 arch/x86/kvm/x86.c               |  12 +-
 10 files changed, 594 insertions(+), 19 deletions(-)
```
#### [PATCH 0/3] accel: Remove system-mode stubs from user-mode builds
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Mon Nov  9 09:45:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11890809
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 47196C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 09:45:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D646B206ED
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 09:45:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="oXshjwy5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728335AbgKIJpv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 04:45:51 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46712 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726482AbgKIJpv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 04:45:51 -0500
Received: from mail-wr1-x435.google.com (mail-wr1-x435.google.com
 [IPv6:2a00:1450:4864:20::435])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 45B0FC0613CF
        for <kvm@vger.kernel.org>; Mon,  9 Nov 2020 01:45:51 -0800 (PST)
Received: by mail-wr1-x435.google.com with SMTP id c17so7927427wrc.11
        for <kvm@vger.kernel.org>; Mon, 09 Nov 2020 01:45:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/q4o4BiIHWmBVIAtODv3UPM1kTXJig1tzzvjpmqNPpQ=;
        b=oXshjwy58XW4nOnK2QAPSmctnhXSDSl84kEoQ/WCKipy06AHZ7PgRMlNZ9hsm0s1di
         VgEos8EY3M3ciaUyFZvpsPreZAZiHxeSxc6x6l3hGQ02CKFw4tDnfvt/QDIJtvC16Q1x
         2btmMTcMltfDe60QRCx0l86+61soNuNi2eFeuw+eJmAq/7Zz8fWDeXf2vn70KfTg/QJ8
         diVMFr0Q2mB1S7ZZXhOMZ2o3+ik1AyJqb8Eju4WuOxxkxWPOTrq2yXrIVMWhrCDyfX7e
         qpcoYWKnji1/wQncrGWsAcMDj9FqnaeV+ZPLH4RE2gFRTFlAsgrP16o9JdTg6o4Hez8H
         MYbA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=/q4o4BiIHWmBVIAtODv3UPM1kTXJig1tzzvjpmqNPpQ=;
        b=aFJiUNkeAgI+ca/LN7H6btnqH9q4PcZCbwiy2eZjMT4LVZ4VyU0untv2sF9Fig/Eq/
         w5Oh6H/B+vXSmGecjMxxbsHYu8oy7OObFlSIquZbIssk8EVh6l2vk//Db/vShIBQS3n/
         964Oz3w1UuyIBSxuClt+xR6LnP6UC7ee+zgtor7PDzKipxzqbuvaDxQ+dPPsW2qrTQcS
         F8w+q3Uu1oUKE7cu85MJx5urdsEmFXWfHPNNRjKoyyPSelMHl8koa3K7YJUKxpcoMnfR
         yyWoassQmORWUXb+SB7oOeSuZvDz2Nm+2MShsMtHKUwQzZk3YqMhathQBIOsZ5Q3a6HW
         o9lw==
X-Gm-Message-State: AOAM53337uXaLOdLRPYZ48gDYZ3ttskdykPJ28tCzEsHf+S5yYWEh8p9
        X3UJObiLW+kEEaimt3enpcVWVjT+TB4=
X-Google-Smtp-Source: 
 ABdhPJypYLA8yDC42PAwQMJL5W7KWz1kEYPcRWXSp9aw20JGITNOoQXvJA/WTqE4S6Ta7XEGPjE77w==
X-Received: by 2002:a5d:4e0e:: with SMTP id
 p14mr16615971wrt.160.1604915149678;
        Mon, 09 Nov 2020 01:45:49 -0800 (PST)
Received: from localhost.localdomain (234.red-83-42-66.dynamicip.rima-tde.net.
 [83.42.66.234])
        by smtp.gmail.com with ESMTPSA id
 u81sm13094834wmb.27.2020.11.09.01.45.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Nov 2020 01:45:49 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Laurent Vivier <laurent@vivier.eu>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH 0/3] accel: Remove system-mode stubs from user-mode builds
Date: Mon,  9 Nov 2020 10:45:44 +0100
Message-Id: <20201109094547.2456385-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is pointless to build/link these stubs into user-mode binaries.

Philippe Mathieu-Daudé (3):
  accel: Only include TCG stubs in user-mode only builds
  accel/stubs: Restrict system-mode emulation stubs
  accel/stubs: Simplify kvm-stub.c

 accel/stubs/kvm-stub.c  |  5 -----
 accel/meson.build       | 10 ++++++----
 accel/stubs/meson.build | 12 ++++++++----
 3 files changed, 14 insertions(+), 13 deletions(-)
```
#### [PATCH v3 0/9] slab: provide and use krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>
From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

```c
From patchwork Mon Nov  9 11:06:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11891095
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 20B31C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:08:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA8A4206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:08:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="h63NN6JI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729472AbgKILHB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:07:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59476 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729243AbgKILHB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:07:01 -0500
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D1C24C0613D3
        for <kvm@vger.kernel.org>; Mon,  9 Nov 2020 03:07:00 -0800 (PST)
Received: by mail-wr1-x444.google.com with SMTP id s8so1124264wrw.10
        for <kvm@vger.kernel.org>; Mon, 09 Nov 2020 03:07:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/BZufo5GeZBBjJpVBhVfUUqf7bDRhIufHOC+GeAXTjw=;
        b=h63NN6JIr7BPg/L5K4tALUY+/tMHu7b/AohNm+Sq0AHtLr7C775RNCqPF5N91xMyBI
         MOiY+0CB7+nr/djuF77eQh2JjzNwZIgYaGZcGaavyRIGIDOMtNAYYoguPo3Q8xFlwx6L
         QddH+S2xNU+tvs03WMAyY063pe678sUddwGJwNwh+sGNbGg5ToLYxAiebC7qHygj5JKC
         wX/om83DYWGS2MTV/IcOR6891AOSOJx6pnI6tFAZh8FUdpFrpM+edanMCufFGJCkBefi
         wPu7sueEx5oa9fOWdtBQSKZ4a7oTEsuZvbf1jYwrHa9aigN1cKpCLLxVES7TkXXM96mf
         VUKg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/BZufo5GeZBBjJpVBhVfUUqf7bDRhIufHOC+GeAXTjw=;
        b=P7DL/V8GuVoyzm/Yve5wz1G94H7pJvax97lNemTSdzEb0BRpHQcOlmDZe8Ggw97uSX
         1qqTmDM2o1QV7u3SGgSA2CMXbKxwI1K5bsrBcSzUUsjvoMwRiEkscFDMrQCbWPijSmZs
         +xKhESbCe3sj6IJA5ADShcaza750RCnzHzyE3nPsxV2q2wfl/lp/Y9/QGiEe8Hrazj7o
         0/R89ns0WtWZG1UP917U0KbGrUEDeZmneogKxMVpT8ltmaHnrHk9I8s9qL4zGEdClxNu
         +lMGlqOAsjTy32Nu+/11E3PuHYkJXboKoOIDopHX61ectbOs5h+qz+ngpLf9lPyO7kKb
         m+Vw==
X-Gm-Message-State: AOAM531TKBOgDAAuYNCVmJA/Cs5CWU6c5iGhzMQDbI14FrWpbqDrcbAf
        17ubBOjNxCmzf9s6VkRdcmfWyw==
X-Google-Smtp-Source: 
 ABdhPJyoLN1aG0XKVyv+yWfCk24OCLDvJjyIFGdAfhV/HDRuWRPPB2x0i9RWfrD3NWEqtPTk5g+kWQ==
X-Received: by 2002:adf:9066:: with SMTP id
 h93mr18252220wrh.166.1604920019608;
        Mon, 09 Nov 2020 03:06:59 -0800 (PST)
Received: from localhost.localdomain (lfbn-nic-1-190-206.w2-15.abo.wanadoo.fr.
 [2.15.39.206])
        by smtp.gmail.com with ESMTPSA id
 d3sm12815582wre.91.2020.11.09.03.06.57
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 09 Nov 2020 03:06:58 -0800 (PST)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>
Subject: [PATCH v3 0/9] slab: provide and use krealloc_array()
Date: Mon,  9 Nov 2020 12:06:45 +0100
Message-Id: <20201109110654.12547-1-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

Andy brought to my attention the fact that users allocating an array of
equally sized elements should check if the size multiplication doesn't
overflow. This is why we have helpers like kmalloc_array().

However we don't have krealloc_array() equivalent and there are many
users who do their own multiplication when calling krealloc() for arrays.

This series provides krealloc_array() and uses it in a couple places.

A separate series will follow adding devm_krealloc_array() which is
needed in the xilinx adc driver.

v1 -> v2:
- added a kernel doc for krealloc_array()
- mentioned krealloc et al in the docs
- collected review tags

v2 -> v3:
- add a patch improving krealloc()'s kerneldoc
- fix a typo
- improve .rst doc
- tweak line breaks

Bartosz Golaszewski (9):
  mm: slab: clarify krealloc()'s behavior with __GFP_ZERO
  mm: slab: provide krealloc_array()
  ALSA: pcm: use krealloc_array()
  vhost: vringh: use krealloc_array()
  pinctrl: use krealloc_array()
  edac: ghes: use krealloc_array()
  drm: atomic: use krealloc_array()
  hwtracing: intel: use krealloc_array()
  dma-buf: use krealloc_array()

 Documentation/core-api/memory-allocation.rst |  4 ++++
 drivers/dma-buf/sync_file.c                  |  3 +--
 drivers/edac/ghes_edac.c                     |  4 ++--
 drivers/gpu/drm/drm_atomic.c                 |  3 ++-
 drivers/hwtracing/intel_th/msu.c             |  2 +-
 drivers/pinctrl/pinctrl-utils.c              |  2 +-
 drivers/vhost/vringh.c                       |  3 ++-
 include/linux/slab.h                         | 18 ++++++++++++++++++
 mm/slab_common.c                             |  6 +++---
 sound/core/pcm_lib.c                         |  4 ++--
 10 files changed, 36 insertions(+), 13 deletions(-)
```
#### [PATCH v15 00/17] KVM RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Mon Nov  9 11:32:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891259
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 21B2BC388F7
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:36:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E945206A4
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:36:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="W2ywac5R";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="NOc7+pQi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729743AbgKILdi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:33:38 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:1326 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729802AbgKILdg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:33:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921613; x=1636457613;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=3Ak/ftzQ672FjrPdWl/9EEILfkX/y6YcGgM73Baq3Bc=;
  b=W2ywac5RcjN27mEGy0BYgRMhazmR76uGLlZAByYbyQEmLd36/Mr9ZkX7
   /zNpEUc6KbQS2573iAZHcSIzVtAbXUuO4qvXb3+JlXd3g+xcR9hM1F2Zy
   gL4W3RiUzQPreFQUCzHWBnrVEnOXOVGK+HITVgVgBJJlfNqmMDxEkY0zL
   6R0tgTnTd/qsEVBOlkFm7fwqmmKZYAT6aAKaxtUe5bCwm8ig0wYVbVvye
   A+F4/r0g9/jxGcM9vZKGIBeafWScS55nHHen+se+6ftnxMaGs9NRMLNIK
   4burIS1MQSGMRYSP49aAMaFik/xUCN5E+a0HU83/q8n0HQ1wbdNc0zFwc
   Q==;
IronPort-SDR: 
 2v96CyTRYfDyQ8bmRONbnZSHq83aB5nPkh1alNAO8ev9V/YZE1bFNb5BxWTfiobiKaJbkvDfho
 n6hp99IhTbiy9rAIR0QWtvV+2Y+NvpkhD4N4ina2qoVflUxePTiIR95s5h0qipt0o2K/qUEC6K
 ZlkKUwF5QUkN5M/roAJ0JPnt1ckaWlrCjTiIKWXoiV7vKxW2xaIyoC+F3SHym4KgXM/KOyScr+
 ryxHKcJJiekQJc2kiWU/Qkxy2JhgasR2e2VQXAfIYBzM3lRoZpVEzYvaKdKorjVaxSxP7caBO0
 nQA=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="152080997"
Received: from mail-co1nam11lp2177.outbound.protection.outlook.com (HELO
 NAM11-CO1-obe.outbound.protection.outlook.com) ([104.47.56.177])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:33:32 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ShtccP0GOWCvKcjdKXdewlcq0lP6hRL59hZNNNfEKPXKgXLk/h6ovJyv6kaJkElSukfUFW6SrrMGPoHVADkT1EH3eYL2aJQm+cMSAmtp9/SI+jdLs7UjC/o1MXBbftPNiH+bKzqHiPgEJz+kqZEIfRJdibgm+b3X7Dl2LW8Qbboj3S9UnKO4FJf690YR0MkcHKyQAEF8FuakMN7av//BWD8A5d//bR5WGcMFTjxKwIbePWXCtNB4/7yac+bVOdSkt6XgtZRShiMEv1YPVrOu8nzp7T/emdCi0iVvQdscmxeBdpmCbFGqp+w2Pg+WF4fYpP2PxOuB2IGjb8wHdfQ9sQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pyNOF1VmUl8HBD98rW65in+JUnc9nyt4UEXnkFo6uG4=;
 b=JZ9TXLIdu8xzkq6wJMX8MkqgcscDIsnNJMdace+kIYFNYd5Cd/tANmtctuWZYngoHNlJ78tCuDZuEvXvgIeGzCAtS2D0m/NjkPU9q+WRb1bbPkeC5jKzUFG4p+GQ5nm/RVtNuTbu4DgW3t+q5YvA1qc4+vp0SUzKCJRSvqgXUi1wFY8SJ07sC+fOtkr23HZA80qpdg+Bd96gz6K5obqtZkQUMJVBwUo7eM4ALpzfiuyco6CrtqC+dBQvmJxeWnWpAXyP35DiZdGls9tlu2nH+GEHuWguFJA1+k1gMAkl3jLYUR0DFb+59rdpCcB4i6Hq7vPYTn/6Pi9Vfck6wdRhFg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pyNOF1VmUl8HBD98rW65in+JUnc9nyt4UEXnkFo6uG4=;
 b=NOc7+pQiUFg6q9My+Qu1Q0U1YruBpmZI3K9cWzVl2NG84DnU5QiwYyLWPSvtKlliQEWdK8VaDAdRuf6FEwJqh+82cwrMr4OuhleGwvu2cPUvp2axZH65/z5N99MRKKwLuRyCH3k3mmQCDsV2zwEFuKGW7v8OprZdrAxa2XfherU=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR0401MB3510.namprd04.prod.outlook.com (2603:10b6:4:7e::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:33:31 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:33:31 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v15 00/17] KVM RISC-V Support
Date: Mon,  9 Nov 2020 17:02:23 +0530
Message-Id: <20201109113240.3733496-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:5d::17) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MAXPR01CA0099.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:5d::17) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:33:26 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 40a1c959-55a8-4e03-59cf-08d884a348a3
X-MS-TrafficTypeDiagnostic: DM5PR0401MB3510:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR0401MB351055B2A38EF85E8336B7508DEA0@DM5PR0401MB3510.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:79;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 eQJTWv5508sAYzp59Nhevxwq87Zj/3aRwzq+9X360jjFL/F/0XKmyQ0Ge2ucTYEMcUectUoB5Xvag0BIo+oyiJr3KyNtuoZIMTQ5jsGWnUCZIeQOBiMw8uokG1KYmfs09w00loLk76BmfLx6yz/Q7Sxg6VNYjSr3X/wfb2RP2hsdxNuDnATUPgADXz/9pzEn/buFdBbqCroCH8oxjhGfUK/5/wu5tM2cyJptQ/5oEMThm7lRHOuAzhkf02GxeegsAd8kFztuUsDXH54GDPW5b8IPlQ60bnSr3abGV3NTcHtWFfRLzkBeYgY5zqNn+OZrHkOsoXCAXt4+j3WeA3foYF8DglADtsQZXtXQS94J9kUA4h4SUIpfAXHQVB/NfRwb9rs4yqUN9whmducBCsxrYOvTo1R1RRZm0bQoZ0Cc850DWc1KrPXyZCdLbS7oGIOO/CVmJDaba4JH+Y2QCwkMpg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(136003)(376002)(39860400002)(396003)(366004)(478600001)(110136005)(316002)(83380400001)(54906003)(86362001)(26005)(186003)(16526019)(36756003)(5660300002)(2616005)(956004)(2906002)(8886007)(44832011)(66946007)(66556008)(66476007)(6666004)(7416002)(966005)(8936002)(30864003)(1076003)(4326008)(52116002)(7696005)(55016002)(8676002)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 8LKKEWDbs5fI+ml/HfbUWeeCxWbbl7dh/XCprrICa8Yzg2GtnxqfGj4iXDXs8Gv/ma+1mmpO8dAx3GQINGfWpV/kjOWUMj//oMaVmJXXf+/wL0qct43qsM47SB+G8s6zojV6fKh94MASuB/ZZCveYdqAi9G1x+mlyYLpsuYtNHdsv9+pKE/vKpTudQpyaPvYh8AzCWVl4N2duWQmJ/c0GGnmmInlH3F3TmXgq44wqG03V9T5AylWIzZOuQ1upcP/RBdWFe54j9mDMSoBCPkZJLch0DskEpdKjBkuKUNk1qTapYtsJyma6ut0bXN3jIbOjY4Jpn96M816kZI9Z/J2/ZSO8alDgfOt+XzClYO0PRmkVQIpgfgvgc4BxuBXzk7xHwR7tT513eo7oz2eoQJx5if2arpbLrxKZ/RC2lL6HKTIjX2MEhvUxXPJ3odneNcXICmoH28I4dEpZ1P3mM2uf7nPK9hb7psU0p2j7axiHAAZIn1t9sSm61ti8tX4HRAX9/16/ZQMNB6ueysihHozcDSDCTREKNcU6O+qUPaoRq9U5l568If8zj90eVyee9IC9UOAyLng48fW7UMquQSk1s20aQA7zhV2IoZ1cjC5OnUOW52lOO16XXH6D1NmJBgSBRSkZvqeSbJcDGd8g/NvVg==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 40a1c959-55a8-4e03-59cf-08d884a348a3
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:33:31.1392
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 LMB8v7KZDCyqabPpCi5R1aF8ltgmSx28dOq1b/X5o1DrmUuKrj8ZKQrCaD1MQ0sUnHPWvotwsGtenpxIG0p0Wg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR0401MB3510
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
Linux on RV64/RV32 Guest with multiple VCPUs.

Key aspects of KVM RISC-V added by this series are:
1. No RISC-V specific KVM IOCTL
2. Minimal possible KVM world-switch which touches only GPRs and few CSRs
3. Both RV64 and RV32 host supported
4. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure
5. KVM ONE_REG interface for VCPU register access from user-space
6. PLIC emulation is done in user-space
7. Timer and IPI emuation is done in-kernel
8. Both Sv39x4 and Sv48x4 supported for RV64 host
9. MMU notifiers supported
10. Generic dirtylog supported
11. FP lazy save/restore supported
12. SBI v0.1 emulation for KVM Guest available
13. Forward unhandled SBI calls to KVM userspace
14. Hugepage support for Guest/VM
15. IOEVENTFD support for Vhost

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v15 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v5 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in master branch at: https://git.qemu.org/git/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-Spike

Changes since v14:
 - Rebased on Linux-5.10-rc3
 - Fixed Stage2 (G-stage) PDG allocation to ensure it is 16KB aligned

Changes since v13:
 - Rebased on Linux-5.9-rc3
 - Fixed kvm_riscv_vcpu_set_reg_csr() for SIP updation in PATCH5
 - Fixed instruction length computation in PATCH7
 - Added ioeventfd support in PATCH7
 - Ensure HSTATUS.SPVP is set to correct value before using HLV/HSV
   intructions in PATCH7
 - Fixed stage2_map_page() to set PTE 'A' and 'D' bits correctly
   in PATCH10
 - Added stage2 dirty page logging in PATCH10
 - Allow KVM user-space to SET/GET SCOUNTER CSR in PATCH5
 - Save/restore SCOUNTEREN in PATCH6
 - Reduced quite a few instructions for __kvm_riscv_switch_to() by
   using CSR swap instruction in PATCH6
 - Detect and use Sv48x4 when available in PATCH10

Changes since v12:
 - Rebased patches on Linux-5.8-rc4
 - By default enable all counters in HCOUNTEREN
 - RISC-V H-Extension v0.6.1 spec support

Changes since v11:
 - Rebased patches on Linux-5.7-rc3
 - Fixed typo in typecast of stage2_map_size define
 - Introduced struct kvm_cpu_trap to represent trap details and
   use it as function parameter wherever applicable
 - Pass memslot to kvm_riscv_stage2_map() for supporing dirty page
   logging in future
 - RISC-V H-Extension v0.6 spec support
 - Send-out first three patches as separate series so that it can
   be taken by Palmer for Linux RISC-V

Changes since v10:
 - Rebased patches on Linux-5.6-rc5
 - Reduce RISCV_ISA_EXT_MAX from 256 to 64
 - Separate PATCH for removing N-extension related defines
 - Added comments as requested by Palmer
 - Fixed HIDELEG CSR programming

Changes since v9:
 - Rebased patches on Linux-5.5-rc3
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

Changes since v7:
 - Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
 - Removed PATCH1, PATCH3, and PATCH20 because these already merged
 - Use kernel doc style comments for ISA bitmap functions
 - Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
   be added in-future
 - Mark KVM RISC-V kconfig option as EXPERIMENTAL
 - Typo fix in commit description of PATCH6 of v7 series
 - Use separate structs for CORE and CSR registers of ONE_REG interface
 - Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
 - Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
 - No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
 - Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
 - Added defines for checking/decoding instruction length
 - Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
 - Rebased patches on Linux-5.3-rc7
 - Added "return_handled" in struct kvm_mmio_decode to ensure that
   kvm_riscv_vcpu_mmio_return() updates SEPC only once
 - Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
 - Updated git repo URL in MAINTAINERS entry

Changes since v5:
 - Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
   KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
 - Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
 - Use switch case instead of illegal instruction opcode table for simplicity
 - Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
 - Handle all unsupported SBI calls in default case of
   kvm_riscv_vcpu_sbi_ecall() function
 - Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
 - Improved unprivilege reads to handle traps due to Guest stage1 page table
 - Added separate patch to document RISC-V specific things in
   Documentation/virt/kvm/api.txt

Changes since v4:
 - Rebased patches on Linux-5.3-rc5
 - Added Paolo's Acked-by and Reviewed-by
 - Updated mailing list in MAINTAINERS entry

Changes since v3:
 - Moved patch for ISA bitmap from KVM prep series to this series
 - Make vsip_shadow as run-time percpu variable instead of compile-time
 - Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
 - Removed references of KVM_REQ_IRQ_PENDING from all patches
 - Use kvm->srcu within in-kernel KVM run loop
 - Added percpu vsip_shadow to track last value programmed in VSIP CSR
 - Added comments about irqs_pending and irqs_pending_mask
 - Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
   in system_opcode_insn()
 - Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
 - Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
 - Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
 - Fixed compile errors in building KVM RISC-V as module
 - Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
 - Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
 - Made vmid_version as unsigned long instead of atomic
 - Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
 - Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
 - Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
 - Updated ONE_REG interface for CSR access to user-space
 - Removed irqs_pending_lock and use atomic bitops instead
 - Added separate patch for FP ONE_REG interface
 - Added separate patch for updating MAINTAINERS file

Anup Patel (13):
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.rst          |  193 ++++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    1 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   89 ++
 arch/riscv/include/asm/kvm_host.h       |  279 +++++++
 arch/riscv/include/asm/kvm_types.h      |    7 +
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  128 +++
 arch/riscv/kernel/asm-offsets.c         |  156 ++++
 arch/riscv/kvm/Kconfig                  |   36 +
 arch/riscv/kvm/Makefile                 |   15 +
 arch/riscv/kvm/main.c                   |  118 +++
 arch/riscv/kvm/mmu.c                    |  860 +++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   74 ++
 arch/riscv/kvm/vcpu.c                   | 1012 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  701 ++++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  173 ++++
 arch/riscv/kvm/vcpu_switch.S            |  400 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   81 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 26 files changed, 4749 insertions(+), 9 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_types.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
```
#### [RFC PATCH v5 0/8] KVMTOOL RISC-V Support
##### From: Anup Patel <anup.patel@wdc.com>

```c
From patchwork Mon Nov  9 11:36:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11891285
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 631AAC388F7
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:37:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0346420731
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 11:37:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="hevjU/u+";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="xkEUu3ov"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729671AbgKILhk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 06:37:40 -0500
Received: from esa6.hgst.iphmx.com ([216.71.154.45]:28154 "EHLO
        esa6.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727826AbgKILhj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 06:37:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1604921858; x=1636457858;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=6zoCEcDzBlY+MvJa96aL5yOujWiEDYlPehO+wFsNorc=;
  b=hevjU/u+6zCNc97OV7pKCCKlz/SnAMTbHOHOuILoDp0KFRFf0aJ2DopZ
   JazU+lrTVJPCDNa6urwweXskYQmsFVTABIHCZcWFclHbg8K4lv+PScTvc
   nyS+a9NLzn3bWBJ9DvtkSvBX+zJ4YdlgNg1a2D+o/LJ8uaWM3StZ8UuZ8
   G9Mq2Bbc1by4o+IbL4X4NK6K3EydlIEC+oSnBS37W+ZiV9ZbWHSJHDHN8
   63bNfSfssSP9M0zLeRjgsU21EUKVOwEwC/NbAsCoOipYxzTKytXuRfpsi
   kxfGc5twmkviDZknRWsmH0dEBon5L8276CGNfmiHwedN6OqU9+/Vz/UDz
   w==;
IronPort-SDR: 
 vkx2gM2mchtyTRkscw+OpuoZLLDxDBNswlGwmItV+CdhDtuRRH53KJl8286SgUYJrtMpTO3Ao5
 vzd4/M4hFu19Kp6e8PpuvM3WjFaG+pwZFszcAVkKK3o2asueqxCT7tC+eOiP0tnkehNrassbYL
 D4/AfNkhxy0+O58Dr1P7fZj5HAdREdeHu9If5tcPbbb+EPqSM8cWbkAGIHk2ebt85NQDR6d30a
 sQby+AcIVBZUBXUucKp6hgdLa9mylyAHFFtMLlfet0phBtuZTccBdnIGeg/cvN4d76PbwxqdeD
 tr0=
X-IronPort-AV: E=Sophos;i="5.77,463,1596470400";
   d="scan'208";a="153383025"
Received: from mail-bn8nam08lp2044.outbound.protection.outlook.com (HELO
 NAM04-BN8-obe.outbound.protection.outlook.com) ([104.47.74.44])
  by ob1.hgst.iphmx.com with ESMTP; 09 Nov 2020 19:37:37 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=foPfai0gYDUw7BaKcKlxcT4ETcg2Qj6f52rCIZUhKkN+FbONcVLCAU9VnPtr8qzaAFgEWqGoHyfloxYHeGNdoVhqnqdYGBiPja/+HbOFF8Ev62E0GQP5iknKNNNrN6pnzxxRFu9v4ferbwieGjDNsQTtuuNVpQtXb1364XAAo7fPaeoId7WZ0qQ2rAHUUS72JD6Ik05MaNeg4C+J0/Lf/ajuLMPKtTWKs8fveGzIPXHdKK8l3VNSx56klQnfEOtmK77CO5dnR28sf5Cz9DifRho8rKMznbiTfuHPPb7MrjIDpy6tJvb0Z88DERRb0Mc+HNFGcjiH8EKB+qZVExDlMg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JVcfIdSKGzkhE/vCyHpFBUrtvaEP1YMRFNO3518V/30=;
 b=J8nrt4+lTpkRy0m63IgIFimD9vcoPRPA/p3i+9WIH0nK19o1RZouRHFq8j5db4yeCAZvjjajC7Ht/qK+9RoTtrURCMPxDO7HI1cuMEFR2tJcvyEKw7aFN4qI/Y1emHNPm0aJlmeDkuakuNgLeP6EzUjNfvT+flJgIbNnJ3jXIEvceXela5+lMiaerh++KedO4gIl0QyeBSna7JrrabfFQ42r+2ViMtHlTyBMxR5AEpKIHtMxUQqr58SljQw8EphXfWCVtuHtTZ7UqmOQs/a9dpmfZY9Jc3q6RQaBko1VgDUjdUsOxqseGNXM+kWRywZSN5YjghbC+uq7guT2YdPQBA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JVcfIdSKGzkhE/vCyHpFBUrtvaEP1YMRFNO3518V/30=;
 b=xkEUu3ovdXZ/qHaZRQGvm3zkdJwkrI/weOHnmXj+ecshX9HqStIQwiuhioI+DhJFeRUIfSyQnjS6QXYtcGLiGB+N0d/uas/FKgiAH5OTqBT3XAdWMj2n785PlL7pO9ZLo4uKIWmHmYb0D9H4LJEuyOyAGy32/lVJT9ALSd5lYEo=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3866.namprd04.prod.outlook.com (2603:10b6:5:ad::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Mon, 9 Nov
 2020 11:37:35 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::d035:e2c6:c11:51dd%6]) with mapi id 15.20.3541.025; Mon, 9 Nov 2020
 11:37:35 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v5 0/8] KVMTOOL RISC-V Support
Date: Mon,  9 Nov 2020 17:06:47 +0530
Message-Id: <20201109113655.3733700-1-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [122.171.188.68]
X-ClientProxiedBy: MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34)
 To DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.171.188.68) by
 MA1PR01CA0094.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 11:37:32 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: cf9113e0-4911-484f-be47-08d884a3da81
X-MS-TrafficTypeDiagnostic: DM6PR04MB3866:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB386664B8737F2936FC7538A28DEA0@DM6PR04MB3866.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:1923;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 V79NtzZ/Yt4yEEW/BKzg9WgZIbwirmtQZaXDdnIIyH9uHFL3vYPScLKqvgFgLXOQZjjAfrjuhkJv+cahen4su+WvsqdzXVxfIpaeyPyoUty7OTfYzLge0jEEK9mVITMnf9FaCC5QhdM6e08lQIRseHBNV/Sok+rP/4AcSbdY9SG/WBJWm235BAYjNHVZcuY4L96uqzHm3H91UnjEUOpiNSSOfjYfGblMUBABqZvp/wzIsuBkJLcWvs1cB8OtIkluoKB6JuXrXLLfsEkM8+yhJn1O/aJn2EhVzx/5d2mWDS+yM91uJYuPAY0YUEdrvDno6fuhYWHTuv/I997TXJ1eEU9hB+li6vWKpCDicmItysiFPZZY44VIfVO9ra9Bp0X2GnO2uDa7Q6qQsL5CVVLskWwTcIzsQvjKjZrKrOguLdiVhvXHT52QbV6/9+FbGYmoaeRKhvFY3sb53aStsSm3nQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(136003)(39860400002)(376002)(55016002)(83380400001)(6916009)(1076003)(44832011)(16526019)(186003)(316002)(26005)(8676002)(54906003)(5660300002)(52116002)(7696005)(956004)(966005)(2616005)(478600001)(66476007)(66556008)(4326008)(66946007)(6666004)(2906002)(36756003)(86362001)(8886007)(8936002)(42580500001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 9p2NB2/NsOdmR71b3pUxzCfDJZ1yVGCCW33eBbEZDj54l5+5qiRoxExrFg5bIuPl10xkCIgm7u+Ir6p5fPo/n9AV3m6rJuDnyV7xQsRw9ls5lPFUO/hpQYsDoUYQTQlV85GapGhBYouA0zJlS3HMfcJiO/k6HCZ5OZjXcaAnQPgF6L/jPjDBAlFLNNZ/2Jwxaa5MY977qT+8X4QiEJKZkGrsOrs5cyTSyrnGcU9AIpwlFZ4hlzcVOdpuQ53bYE0PaRl2k3oLDafzArwlIvrDdiZwkqaxob1uVU5Nv1C1BXsIeUjdb/YmIKBrbmcuxTMeM9BDpNLX1h2nhD1OHYhdiYbiDJGRv+OrNzERfBJnBa+nPBDTeyK8Ih4Iy22nJEB69LX+o23+6s1j64jWQXSEEHeAmp4L8QCGCPreex3vlhIXjGHFKg4XVE0+VpcHYtkGRi72WTmZKRCmfVl+4e8OFSAPvSYxj4xtwBuhysKowP/VCyuSZZxdHYldPpjeis+b5lxIicB3A6kJsBuurGFidlNQ+a2XTJUHVyjRhHQ4KWi2vt6JHECqjvcvntnmo39sKEx0V/u0PNjUdu1Ab+wWHOB9bzp/lXRIAguAFmJkrYJuqIaVf99ktmm9fsfgkV+zw7KQ2RzgySSqQKIRi0Ra8A==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 cf9113e0-4911-484f-be47-08d884a3da81
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 11:37:35.4805
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 rrm/pNPhiE4qSZuKVguaSI/Z74wKbB5yVzWCJJNdNpPU86qQXbFz1EqEpEpMlLXX3V0HfkIR7/azvsDbnpd1XA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3866
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds RISC-V support for KVMTOOL and it is based on
the v10 of KVM RISC-V series. The KVM RISC-V patches are not yet
merged in Linux kernel but it will be good to get early review
for KVMTOOL RISC-V support.

The KVMTOOL RISC-V patches can be found in riscv_master branch at:
https//github.com/kvm-riscv/kvmtool.git

The KVM RISC-V patches can be found in riscv_kvm_master branch at:
https//github.com/kvm-riscv/linux.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is
available in master branch at: https://git.qemu.org/git/qemu.git

Changes since v4:
 - Rebased on recent commit 90b2d3adadf218dfc6bdfdfcefe269843360223c
 - Sync-up headers with latest KVM RISC-V v15 series which is based
   on Linux-5.10-rc3

Changes since v3:
 - Rebased on recent commit 351d931f496aeb2e97b8daa44c943d8b59351d07
 - Improved kvm_cpu__show_registers() implementation

Changes since v2:
 - Support compiling KVMTOOL for both RV32 and RV64 systems using
   a multilib toolchain
 - Fix kvm_cpu__arch_init() for RV32 system

Changes since v1:
 - Use linux/sizes.h in kvm/kvm-arch.h
 - Added comment in kvm/kvm-arch.h about why PCI config space is 256M
 - Remove forward declaration of "struct kvm" from kvm/kvm-cpu-arch.h
 - Fixed placement of DTB and INITRD in guest RAM
 - Use __riscv_xlen instead of sizeof(unsigned long) in __kvm_reg_id()

Anup Patel (8):
  update_headers: Sync-up ABI headers with Linux-5.10-rc3
  riscv: Initial skeletal support
  riscv: Implement Guest/VM arch functions
  riscv: Implement Guest/VM VCPU arch functions
  riscv: Add PLIC device emulation
  riscv: Generate FDT at runtime for Guest/VM
  riscv: Handle SBI calls forwarded to user space
  riscv: Generate PCI host DT node

 INSTALL                             |   7 +-
 Makefile                            |  24 +-
 arm/aarch64/include/asm/kvm.h       |  46 ++-
 include/linux/kvm.h                 | 124 +++++-
 powerpc/include/asm/kvm.h           |   8 +
 riscv/fdt.c                         | 195 ++++++++++
 riscv/include/asm/kvm.h             | 127 +++++++
 riscv/include/kvm/barrier.h         |  14 +
 riscv/include/kvm/fdt-arch.h        |   8 +
 riscv/include/kvm/kvm-arch.h        |  85 +++++
 riscv/include/kvm/kvm-config-arch.h |  15 +
 riscv/include/kvm/kvm-cpu-arch.h    |  51 +++
 riscv/include/kvm/sbi.h             |  48 +++
 riscv/ioport.c                      |  12 +
 riscv/irq.c                         |  13 +
 riscv/kvm-cpu.c                     | 490 ++++++++++++++++++++++++
 riscv/kvm.c                         | 174 +++++++++
 riscv/pci.c                         | 109 ++++++
 riscv/plic.c                        | 563 ++++++++++++++++++++++++++++
 util/update_headers.sh              |   2 +-
 x86/include/asm/kvm.h               |  42 ++-
 21 files changed, 2141 insertions(+), 16 deletions(-)
 create mode 100644 riscv/fdt.c
 create mode 100644 riscv/include/asm/kvm.h
 create mode 100644 riscv/include/kvm/barrier.h
 create mode 100644 riscv/include/kvm/fdt-arch.h
 create mode 100644 riscv/include/kvm/kvm-arch.h
 create mode 100644 riscv/include/kvm/kvm-config-arch.h
 create mode 100644 riscv/include/kvm/kvm-cpu-arch.h
 create mode 100644 riscv/include/kvm/sbi.h
 create mode 100644 riscv/ioport.c
 create mode 100644 riscv/irq.c
 create mode 100644 riscv/kvm-cpu.c
 create mode 100644 riscv/kvm.c
 create mode 100644 riscv/pci.c
 create mode 100644 riscv/plic.c
```
#### [PATCH v2 0/5] KVM: arm64: Host EL2 entry improvements
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Nov  9 17:59:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11892149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 058DEC5517A
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4FAB21D93
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 17:59:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="1WyyWxd6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730027AbgKIR7a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 12:59:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:47176 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726410AbgKIR7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 12:59:30 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 47E8920665;
        Mon,  9 Nov 2020 17:59:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604944769;
        bh=VB4W1R6Xidy63HPldBkvYgNymeTHvz90LHtlTza6wcQ=;
        h=From:To:Cc:Subject:Date:From;
        b=1WyyWxd6omZIqHS646zTRLqZpPKC0zBMKlpQ++0dgOSQlhLk+b4uq2Q45g3bt7jFP
         oWSo3EUsYmCs6w/muSDYPFB5Kmg2A1XuCLYVpmszzmdd08s+bMofK656RIoxq+7/VC
         mvacaEITP9Jz8ni9pNyFrBepc5qQ6ujtFysiCDvM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcBRv-009BQs-17; Mon, 09 Nov 2020 17:59:27 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, ndesaulniers@google.com,
        dbrazdil@google.com, kernel-team@android.com
Subject: [PATCH v2 0/5] KVM: arm64: Host EL2 entry improvements
Date: Mon,  9 Nov 2020 17:59:18 +0000
Message-Id: <20201109175923.445945-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, ascull@google.com, will@kernel.org,
 qperret@google.com, ndesaulniers@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This small series reworks various bits of the host EL2 entry after
Andrew's extensive rework to move from direct function calls to a
SMCCC implementation.

The first 2 patches allow the use of direct function pointers at EL2,
something that we can't do at the moment (other than PC-relative
addressing). This requires a helper to translate pointers at runtime,
but the result is neat enough. This allows the rewrite of the host HVC
handling in a more maintainable way.

Note that this version now includes the result of a discussion with
Nick, providing some funky pointer mangling in order to make the use
of these pointers vaguely safer (no, they are not safe at all).

Another patch removes the direct use of kimage_voffset, which we won't
be able to trust for much longer.

The last two patches are just cleanups and optimisations.

* From v1 [1]:
  - Merged the 3 first patches as fixes
  - Added pointer mangling for function calls
  - Moved EL2 entry ldp a couple of instructions later (as suggested
    by Alex)
  - Rebased on top of -rc3

[1] https://lore.kernel.org/r/20201026095116.72051-1-maz@kernel.org

Marc Zyngier (5):
  KVM: arm64: Add kimg_hyp_va() helper
  KVM: arm64: Turn host HVC handling into a dispatch table
  KVM: arm64: Patch kimage_voffset instead of loading the EL1 value
  KVM: arm64: Simplify __kvm_enable_ssbs()
  KVM: arm64: Avoid repetitive stack access on host EL1 to EL2 exception

 arch/arm64/include/asm/kvm_asm.h    |   2 -
 arch/arm64/include/asm/kvm_mmu.h    |  40 +++++
 arch/arm64/include/asm/sysreg.h     |   1 +
 arch/arm64/kernel/image-vars.h      |   5 +-
 arch/arm64/kvm/hyp/nvhe/host.S      |  11 +-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c  | 232 +++++++++++++++++-----------
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c |  11 --
 arch/arm64/kvm/va_layout.c          |  56 +++++++
 8 files changed, 241 insertions(+), 117 deletions(-)
```
#### [PATCH v3 00/34] SEV-ES hypervisor support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Mon Nov  9 22:25:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11892667
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5E1D1C55ABD
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 22:26:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E320F2074F
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 22:26:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="17x+OhdF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730554AbgKIW0U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 17:26:20 -0500
Received: from mail-bn8nam12on2080.outbound.protection.outlook.com
 ([40.107.237.80]:57211
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729247AbgKIW0T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 17:26:19 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=cGbbVc3CPGMVnbMqx9ft43V3ZLG5HIeRiYOQdnInrZTww83Ph5Vpzm1lXe/MN7Q+9ecaTMDjyLOdN66nxUKakjAj8fPwS9BVM5DsVylOmF/oHbnGTks+l9QUvbFszyXaEiqyhKXoMIb79/YDe9u+XlrpkTVydoZN6a64fpFSYFRNEX3X90FAX9fat9ce1YldnCFK0xRTCCIK0ZBjS81iNsAJcyC/U8zC0eQG59d+jDlJTXDJVf6UZxpgoZ0q2VJTDa1piRX6AumnhU8bSPg1GCmnWGyatCJohKuwA1cEguhhxhSgtPVSCxzt3uEwvMWgXPaHCh0flT8N7CMOWrL4Mw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZecpU8TB8bdxSMlv1o2rDcWT0a3Zsnxf/3ubLg10/4w=;
 b=nEeAsxqmnItn6P27SkY6ClqxZ42oKtjGks0U2dnKVXsytcBgD6CEr6fY5XYZo1Z9rsVbsUMAybq4KImlEILwRR02vtmNMXDxCOFCLNp2XemYnSDSt/Xqn3jh7SkdGhL44P97lPTcjrzcjEqBIn87Da0H4Y7fiXSLYqzpHs/24WzYWMbtQ8AFyj3xpBktYYC36rgJv2QNnuLwHxv+HqVcHNIXdmAuwXEdzvoJo+OU7MtRew1c1gWw9mLoaD2etEJUxL0n+H9lNH7bqrgmsYA/HhCaeQhEwifL4riUuXM4tnnP5Ogt9beYS4YCseXa0ummaXYjmPe8SenwmLBzaxwjaA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZecpU8TB8bdxSMlv1o2rDcWT0a3Zsnxf/3ubLg10/4w=;
 b=17x+OhdFhP8XuHyazKlJ+fRdfg3KV44S6lotyTk1G14SWTyRyiU4eV11I08VpERlPNjLux6Npnf/N2rr7/8QRHWInbgZeUF6GdiI47BdkntWpWEeHRTuLwv3xlGCw4Bp+oRzvQP0DYdQ2n/x8X0/Gq9CWw6qM74Ky7UA4VM2lYU=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4058.namprd12.prod.outlook.com (2603:10b6:5:21d::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3541.21; Mon, 9 Nov 2020 22:26:15 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::e442:c052:8a2c:5fba]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::e442:c052:8a2c:5fba%6]) with mapi id 15.20.3499.032; Mon, 9 Nov 2020
 22:26:15 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v3 00/34] SEV-ES hypervisor support
Date: Mon,  9 Nov 2020 16:25:26 -0600
Message-Id: <cover.1604960760.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR19CA0008.namprd19.prod.outlook.com
 (2603:10b6:3:151::18) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR19CA0008.namprd19.prod.outlook.com (2603:10b6:3:151::18) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Mon, 9 Nov 2020 22:26:14 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 23f7b5ca-7478-4ce3-c6a0-08d884fe7892
X-MS-TrafficTypeDiagnostic: DM6PR12MB4058:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB40587C7F008979334D15C57BECEA0@DM6PR12MB4058.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CrgWnswjvbztBg0+tCi7F9WF/YBmxkAb1xfkCzDURf53tlMwaE42HQznSS8YJK+cNGC5KT10pB3BG8PVlJZnHuoFP6ARHgu/vUrMbjlb3LyGJ2N8WLweUaRjlumGGBAzhLlFpA4LuMoa6pH1VlQgQ8p1WYvJTFab7jdcASPQ/EwTdF0P5arSFww/m+EPQzLGkcMhAbJ8N6Jm4ySFq+1hZYXU1oz3e5DQ7uhgucEsMi8RxbDWSFXzuCej7Avzz4xXNni39bS6eC7Z2Pe2VxqvQpBLethKaXnnhptlp8kXSxtIS6/ZXv+fzT47m2fgT2rxfwt11CSQIM2xLqaEFzEVc9ZDWELLbrO5aYD/wJbygFm8yD3f656c/mF2PBj9dDW4pOS9fPqHCIbEal6lb6M6kA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(396003)(136003)(39860400002)(366004)(2616005)(956004)(8676002)(16526019)(54906003)(316002)(86362001)(4326008)(26005)(8936002)(7416002)(36756003)(5660300002)(52116002)(6666004)(7696005)(66556008)(66476007)(66946007)(6486002)(478600001)(966005)(83380400001)(2906002)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 sPS0irrVx+cOzrENJGDPpLZIO0SN6f5ZWPXqvQ7GdbTOKI5NvTz279QLk8fdX0ggvzw/sfHcyuBh9JaiEpDiBGEBESimQ/g6l7opYQptasZ0w9utercQa6VhWPFqlefPoT/d7gZ4BQPm2wTLU6v/MnLMtscrjCBxO5YznaS49cTkTi8F9Yg5jqBrDCR4klxgr9wWoYal8dSFudK84HFH6CBurTu2EmpHRmVEYQk1XN34yumI85KHMrjYz/T/q9qUVqGN+eiCx+xPRJ6DyNV61pQWmQg10KGhUrXTlqpJkbVvVDCZL6QN1+Wmmgwc10QWVgHo6L+FN1XYcTICmBhhcxK60iL1zyKWZBRjMdZWZSIvrUzECOb/ul4KUNE4Z+ntQvRbf5gymynl5QCCUNvSRfSMu4Ww1OHZNDsBu1PLgeqZAxbz2dGCoJpq/XBcczu/PBwDfD9+bRBkMoSyPW8J3PESeHgrGaBYj2k0vr7wZ1dyrYOova+69INiAfhZ5QrsDyNzWuJPYIf/b+65shoylhwFdEUj4IqWSlSclatofAk+7uWVv7eLC4VrcaW5W1+Fva7lfo7HkYgGdqbJwdCUIPB0/VbO7RH/ggC07vA3uVjxqmLA9LsH7tI3k8EJCfhJLM+HujLo0MhsESP7h8kP9Q==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 23f7b5ca-7478-4ce3-c6a0-08d884fe7892
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Nov 2020 22:26:15.3949
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 I7PYm1jawzcUi6HzXMlYwEe7tII3JyjGxmo944h2TtCIiIuGZicXST3ak5j49CqMRPysk7LcdP5AAcBnzDn5ZQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4058
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for running SEV-ES guests under KVM.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

Under SEV-ES, a vCPU save area (VMSA) must be encrypted. SVM is updated to
build the initial VMSA and then encrypt it before running the guest. Once
encrypted, it must not be modified by the hypervisor. Modification of the
VMSA will result in the VMRUN instruction failing with a SHUTDOWN exit
code. KVM must support the VMGEXIT exit code in order to perform the
necessary functions required of the guest. The GHCB is used to exchange
the information needed by both the hypervisor and the guest.

Register data from the GHCB is copied into the KVM register variables and
accessed as usual during handling of the exit. Upon return to the guest,
updated registers are copied back to the GHCB for the guest to act upon.

There are changes to some of the intercepts that are needed under SEV-ES.
For example, CR0 writes cannot be intercepted, so the code needs to ensure
that the intercept is not enabled during execution or that the hypervisor
does not try to read the register as part of exit processing. Another
example is shutdown processing, where the vCPU cannot be directly reset.

Support is added to handle VMGEXIT events and implement the GHCB protocol.
This includes supporting standard exit events, like a CPUID instruction
intercept, to new support, for things like AP processor booting. Much of
the existing SVM intercept support can be re-used by setting the exit
code information from the VMGEXIT and calling the appropriate intercept
handlers.

Finally, to launch and run an SEV-ES guest requires changes to the vCPU
initialization, loading and execution.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
---

These patches are based on the KVM next branch:
https://git.kernel.org/pub/scm/virt/kvm/kvm.git next

6d6a18fdde8b ("KVM: selftests: allow two iterations of dirty_log_perf_test")

A version of the tree can also be found at:
https://github.com/AMDESE/linux/tree/sev-es-v3

Changes from v2:
- Update the freeing of the VMSA page to account for the encrypted memory
  cache coherency feature as well as the VM page flush feature.
- Update the GHCB dump function with a bit more detail.
- Don't check for RAX being present as part of a string IO operation.
- Include RSI when syncing from GHCB to support KVM hypercall arguments.
- Add GHCB usage field validation check.

Changes from v1:
- Removed the VMSA indirection support:
  - On LAUNCH_UPDATE_VMSA, sync traditional VMSA over to the new SEV-ES
    VMSA area to be encrypted.
  - On VMGEXIT VMEXIT, directly copy valid registers into vCPU arch
    register array from GHCB. On VMRUN (following a VMGEXIT), directly
    copy dirty vCPU arch registers to GHCB.
  - Removed reg_read_override()/reg_write_override() KVM ops.
- Added VMGEXIT exit-reason validation.
- Changed kvm_vcpu_arch variable vmsa_encrypted to guest_state_protected
- Updated the tracking support for EFER/CR0/CR4/CR8 to minimize changes
  to the x86.c code
- Updated __set_sregs to not set any register values (previously supported
  setting the tracked values of EFER/CR0/CR4/CR8)
- Added support for reporting SMM capability at the VM-level. This allows
  an SEV-ES guest to indicate SMM is not supported
- Updated FPU support to check for a guest FPU save area before using it.
  Updated SVM to free guest FPU for an SEV-ES guest during KVM create_vcpu
  op.
- Removed changes to the kvm_skip_emulated_instruction()
- Added VMSA validity checks before invoking LAUNCH_UPDATE_VMSA
- Minor code restructuring in areas for better readability

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>

Tom Lendacky (34):
  x86/cpu: Add VM page flush MSR availablility as a CPUID feature
  KVM: SVM: Remove the call to sev_platform_status() during setup
  KVM: SVM: Add support for SEV-ES capability in KVM
  KVM: SVM: Add GHCB accessor functions for retrieving fields
  KVM: SVM: Add support for the SEV-ES VMSA
  KVM: x86: Mark GPRs dirty when written
  KVM: SVM: Add required changes to support intercepts under SEV-ES
  KVM: SVM: Prevent debugging under SEV-ES
  KVM: SVM: Do not allow instruction emulation under SEV-ES
  KVM: SVM: Cannot re-initialize the VMCB after shutdown with SEV-ES
  KVM: SVM: Prepare for SEV-ES exit handling in the sev.c file
  KVM: SVM: Add initial support for a VMGEXIT VMEXIT
  KVM: SVM: Create trace events for VMGEXIT processing
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
  KVM: SVM: Create trace events for VMGEXIT MSR protocol processing
  KVM: SVM: Support MMIO for an SEV-ES guest
  KVM: SVM: Support string IO operations for an SEV-ES guest
  KVM: SVM: Add support for EFER write traps for an SEV-ES guest
  KVM: SVM: Add support for CR0 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR4 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR8 write traps for an SEV-ES guest
  KVM: x86: Update __get_sregs() / __set_sregs() to support SEV-ES
  KVM: SVM: Do not report support for SMM for an SEV-ES guest
  KVM: SVM: Guest FPU state save/restore not needed for SEV-ES guest
  KVM: SVM: Add support for booting APs for an SEV-ES guest
  KVM: SVM: Add NMI support for an SEV-ES guest
  KVM: SVM: Set the encryption mask for the SVM host save area
  KVM: SVM: Update ASID allocation to support SEV-ES guests
  KVM: SVM: Provide support for SEV-ES vCPU creation/loading
  KVM: SVM: Provide support for SEV-ES vCPU loading
  KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
  KVM: SVM: Provide support to launch and run an SEV-ES guest

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/include/asm/kvm_host.h    |  12 +-
 arch/x86/include/asm/msr-index.h   |   1 +
 arch/x86/include/asm/svm.h         |  40 +-
 arch/x86/include/uapi/asm/svm.h    |  28 +
 arch/x86/kernel/cpu/scattered.c    |   1 +
 arch/x86/kernel/cpu/vmware.c       |  12 +-
 arch/x86/kvm/Kconfig               |   3 +-
 arch/x86/kvm/cpuid.c               |   1 +
 arch/x86/kvm/kvm_cache_regs.h      |  51 +-
 arch/x86/kvm/svm/sev.c             | 929 +++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c             | 442 +++++++++++---
 arch/x86/kvm/svm/svm.h             | 166 +++++-
 arch/x86/kvm/svm/vmenter.S         |  50 ++
 arch/x86/kvm/trace.h               |  97 +++
 arch/x86/kvm/vmx/vmx.c             |   6 +-
 arch/x86/kvm/x86.c                 | 365 ++++++++++--
 arch/x86/kvm/x86.h                 |   9 +
 18 files changed, 1964 insertions(+), 250 deletions(-)
```
