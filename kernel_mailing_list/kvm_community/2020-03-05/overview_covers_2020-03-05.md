

#### [PATCH v2 0/7] KVM: x86: CPUID emulation and tracing fixes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Mar  5 01:34:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11421043
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 194F6174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 01:35:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04A4820870
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 01:35:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725882AbgCEBej (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 20:34:39 -0500
Received: from mga03.intel.com ([134.134.136.65]:31855 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725776AbgCEBej (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 20:34:39 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Mar 2020 17:34:39 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,516,1574150400";
   d="scan'208";a="234301737"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 04 Mar 2020 17:34:38 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Pu Wen <puwen@hygon.cn>
Subject: [PATCH v2 0/7] KVM: x86: CPUID emulation and tracing fixes
Date: Wed,  4 Mar 2020 17:34:30 -0800
Message-Id: <20200305013437.8578-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Round two of trying to wrangle kvm_cpuid() into submission.  Two more bug
fixes, both related to querying for an "AMD" vendor, in addition to the
fixes in v1 (tracing and Hypervisor/Centaur range checks).

In theory, everything up to the refactoring is non-controversial, i.e. we
can bikeshed the refactoring without delaying the bug fixes.

v2:
  - Use Jan's patch to fix the trace bug. [Everyone]
  - Rework Hypervisor/Centaur handling so that only the Hypervisor
    sub-ranges get the restrictive 0xffffff00 mask, and so that Centaur's
    range only gets recognized when the guest vendor is Centaur. [Jim]
  - Add the aforementioned bug fixes.
  - Add a patch to do build time assertions on the vendor string, which
    are hand coded u32s in the emulator (for direct comparison against
    CPUID register output).
  - Drop the patch to add CPUID.maxphyaddr emulator helper. [Paolo]
  - Redo refactoring patches to land them after all the bug fixes
    and to do the refactoring without any semantic changes in the
    emulator.

Jan Kiszka (1):
  KVM: x86: Trace the original requested CPUID function in kvm_cpuid()

Sean Christopherson (6):
  KVM: x86: Add helpers to perform CPUID-based guest vendor check
  KVM x86: Extend AMD specific guest behavior to Hygon virtual CPUs
  KVM: x86: Fix CPUID range checks for Hypervisor and Centaur classes
  KVM: x86: Add build-time assertions on validity of vendor strings
  KVM: x86: Refactor out-of-range logic to contain the madness
  KVM: x86: Refactor kvm_cpuid() param that controls out-of-range logic

 arch/x86/include/asm/kvm_emulate.h |  37 +++++++++-
 arch/x86/kvm/cpuid.c               | 111 +++++++++++++++++++++--------
 arch/x86/kvm/cpuid.h               |   8 ++-
 arch/x86/kvm/emulate.c             |  64 ++++++++---------
 arch/x86/kvm/mmu/mmu.c             |   3 +-
 arch/x86/kvm/svm.c                 |   2 +-
 arch/x86/kvm/x86.c                 |   7 +-
 7 files changed, 162 insertions(+), 70 deletions(-)
Reported-by: kbuild test robot <lkp@intel.com>
```
#### [PATCH kvm-unit-tests 0/2] svm: more interrupt injection tests
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Mar  5 09:36:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11421439
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DCBB14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:36:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22DE92146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:36:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="EubDSzL7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725974AbgCEJgv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 04:36:51 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:46596 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725937AbgCEJgv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 04:36:51 -0500
Received: by mail-wr1-f68.google.com with SMTP id n15so763240wrw.13
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 01:36:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=Ye/O37MCIbzXLxyjF3VkWBXDADKZKKWQnOm/v94m10I=;
        b=EubDSzL7mn/zJ0WD35PgLt3hWlGyysVIFovIGNtRa0NkQiEMpGCCTRxAqSd2g6XtXy
         SEjVTFUbo+l5y4NAhf2406E7SFt0+QH5efMpDQZIstAKo2+lAVXSWw+8l8hSly9LwT7C
         ArLCWZpE8fUUlNAofOG0n6RZOJ6oZ/CcRx0vFS/z3uJR2esUNVGW0TCVBiihFTgUX5Q6
         bh0z/zym6Icrkvl7s6rmrUK0LqcVnslZb1HqMYMLV+uDDOR1bxVfgOPcJJuQnNmIRSMs
         bCE+cmRkc3/2B8AMULzDbKu9Moij8Lqsn8kf2noPgBOHJqCkLWrFxXeHq1QoH9nucOtV
         IKnQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=Ye/O37MCIbzXLxyjF3VkWBXDADKZKKWQnOm/v94m10I=;
        b=pay1k0tjhacTX/2cD5Dl+hi31TTKkyGkThQHxrhEa8r20d3CGqqEZFTXSsjLhzKlCp
         d7axmb2zTTSwV+Qgc4P2GqwLgnIpKEXc0uc5QyoJzAWo78yvJBnmo7obQm+E3B11yYGs
         Q8NJcokadOhD7J8PXY3J42f+8/7kODmEPDnfX4luTlzGesWO7R2HbOnOdygGlCBm8zPY
         Zka9oFX4eAuzbspOhO3HTY2XfjrtpcL2bhq+IIoUE9+4HHboIQzgPGxQGp0hZadqo9Nn
         +iYMDTnAyUCWTXc8u3qFfPfjz49i+kzWfh/fySqSj+hQukBXvDp5GETx3BNJR6VSrJUA
         I+QA==
X-Gm-Message-State: ANhLgQ1IMDJZ66ASJsn1cCbhArYKKg3mXerTOWuVHjCI8tUlSasTXnT2
        kOyNonNTKhXeHTJMNFvM28pJ04SM
X-Google-Smtp-Source: 
 ADFU+vvdQcT0HDnZ4IPn91n6VXteyRqke954CMMxgUoJbDnANUmD4AOsiqSm98Ew6ZNgpLKULkZu+Q==
X-Received: by 2002:adf:a2d9:: with SMTP id t25mr9012925wra.84.1583401008693;
        Thu, 05 Mar 2020 01:36:48 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w1sm8188563wmc.11.2020.03.05.01.36.47
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Mar 2020 01:36:48 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] svm: more interrupt injection tests
Date: Thu,  5 Mar 2020 10:36:44 +0100
Message-Id: <1583401006-57136-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is just a cleanup.  Patch 2 adds more coverage of interrupt
injection, including running HLT in L2 when L1 does not intercept it.

Paolo

Cathy Avery (1):
  svm: Add test cases around interrupt injection and halting

Paolo Bonzini (1):
  svm: rename and comment the pending_event_vmask test

 x86/svm.c | 166 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++----
 1 file changed, 157 insertions(+), 9 deletions(-)
```
#### [PATCH v1 00/11] PEBS virtualization enabling via DS
##### From: Luwei Kang <luwei.kang@intel.com>

```c
From patchwork Thu Mar  5 17:56:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11421451
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0922C139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:58:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E7F8421741
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:58:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726979AbgCEJ6s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 04:58:48 -0500
Received: from mga07.intel.com ([134.134.136.100]:1764 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725912AbgCEJ6s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 04:58:48 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Mar 2020 01:58:47 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,517,1574150400";
   d="scan'208";a="234366353"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga008.jf.intel.com with ESMTP; 05 Mar 2020 01:58:41 -0800
From: Luwei Kang <luwei.kang@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, mingo@redhat.com, acme@kernel.org,
        mark.rutland@arm.com, alexander.shishkin@linux.intel.com,
        jolsa@redhat.com, namhyung@kernel.org, tglx@linutronix.de,
        bp@alien8.de, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        pawan.kumar.gupta@linux.intel.com, ak@linux.intel.com,
        thomas.lendacky@amd.com, fenghua.yu@intel.com,
        kan.liang@linux.intel.com, like.xu@linux.intel.com,
        Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v1 00/11] PEBS virtualization enabling via DS
Date: Fri,  6 Mar 2020 01:56:54 +0800
Message-Id: <1583431025-19802-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Processor Event-Based Sampling(PEBS) supported on mainstream Intel
platforms can provide an architectural state of the instruction executed
after the instruction that caused the event. This patchset is going to
enable PEBS feature via DS on KVM for the Icelake server.
Although PEBS via DS supports EPT violations feature is supported starting
Skylake Server, but we have to pin DS area to avoid losing PEBS records due
to some issues.

BTW:
The PEBS virtualization via Intel PT patchset V1 has been posted out and the
later version will base on this patchset.
https://lkml.kernel.org/r/1572217877-26484-1-git-send-email-luwei.kang@intel.com/

Testing:
The guest can use PEBS feature like native. e.g.

# perf record -e instructions:ppp ./br_instr a

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


Kan Liang (4):
  perf/x86/core: Support KVM to assign a dedicated counter for guest
    PEBS
  perf/x86/ds: Handle guest PEBS events overflow and inject fake PMI
  perf/x86: Expose a function to disable auto-reload
  KVM: x86/pmu: Decouple event enablement from event creation

Like Xu (1):
  KVM: x86/pmu: Add support to reprogram PEBS event for guest counters

Luwei Kang (6):
  KVM: x86/pmu: Implement is_pebs_via_ds_supported pmu ops
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64
  KVM: x86/pmu: PEBS MSRs emulation
  KVM: x86/pmu: Expose PEBS feature to guest
  KVM: x86/pmu: Introduce the mask value for fixed counter
  KVM: x86/pmu: Adaptive PEBS virtualization enabling

 arch/x86/events/intel/core.c      |  74 +++++++++++++++++++++-
 arch/x86/events/intel/ds.c        |  59 ++++++++++++++++++
 arch/x86/events/perf_event.h      |   1 +
 arch/x86/include/asm/kvm_host.h   |  12 ++++
 arch/x86/include/asm/msr-index.h  |   4 ++
 arch/x86/include/asm/perf_event.h |   2 +
 arch/x86/kvm/cpuid.c              |   9 ++-
 arch/x86/kvm/pmu.c                |  71 ++++++++++++++++++++-
 arch/x86/kvm/pmu.h                |   2 +
 arch/x86/kvm/svm.c                |  12 ++++
 arch/x86/kvm/vmx/capabilities.h   |  17 +++++
 arch/x86/kvm/vmx/pmu_intel.c      | 128 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |   6 +-
 arch/x86/kvm/vmx/vmx.h            |   4 ++
 arch/x86/kvm/x86.c                |  19 +++++-
 include/linux/perf_event.h        |   2 +
 kernel/events/core.c              |   1 +
 17 files changed, 414 insertions(+), 9 deletions(-)
```
#### [PATCH 0/2] KVM: x86: VMX: cleanup VMXON region allocation
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Mar  5 10:01:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11421485
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2726392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:01:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 080AB2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:01:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PBWXocnq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727289AbgCEKBe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 05:01:34 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:52046 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727130AbgCEKBb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 05:01:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583402490;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qpugOFYl5V3c99FSliIabsi6Xzso9YXY154ETSWVrWk=;
        b=PBWXocnqIjC4gdmyz9dumOqje10wq5Z9bRaQw+HSXxrY2zRRR7vzHYyp2jO5kqPXnEKXDJ
        h2BIMwwtD8jPM8fnOkX+S1Z86RwGl+wKqlASYijeJHkUFEtCaWcVuYlB4d5alb9y63cl4R
        pJ/yOs4RJykSPzBookM0lzjMxdGxAas=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-374-7vStS2C1NgydXGE7oDazEg-1; Thu, 05 Mar 2020 05:01:26 -0500
X-MC-Unique: 7vStS2C1NgydXGE7oDazEg-1
Received: by mail-wr1-f72.google.com with SMTP id n12so2079326wrp.19
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 02:01:26 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qpugOFYl5V3c99FSliIabsi6Xzso9YXY154ETSWVrWk=;
        b=hqO2SyHWstjx4yfNj2Wol29G3IGo5k7DFRl7xddxpSK9WiyoPVUc0or+cgYCBA28UJ
         LIh88mAgrzzvf//kZAq3dvHJrG0CyWuPdWnrJJPfn2YFqBmvDm9T/AGwVl8ZbZ3oqBWu
         D1z1ADE79Xx3Bv5V8XBtbJAsa0qkc0C/moUvraQGYZP3CoQSTs/pEnuz9fmZOnczlxZf
         EZEL4RaHMBcvKaKhAAq10xrrcUOSdZHAFzfq33JdXaXl/F/IngtP4koFQh6aIWfbRXH/
         e5hRI+kYAU1Hc19t9qY5oWf3G98yt2y1l+T3QhJLyR2O/HyhcWj7oGwbL1+0WqPN1fhA
         HbIA==
X-Gm-Message-State: ANhLgQ2eu3SGYSXDMLvO4U9qjdUAzCpOioncOH0EtbYsoZZV2MX7Annc
        N1JpHP5MPI4iyrrg3bLLv5xKSTv0VNDaBsBOb5pKNlLF/2BMe8BFSGXhYQgE8NEBoITWQQ8AWZs
        XlZ1ofGpG+ahI
X-Received: by 2002:a1c:df07:: with SMTP id w7mr3298018wmg.7.1583402485696;
        Thu, 05 Mar 2020 02:01:25 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vuz6dICjFPBTcnmSBIcEQjdYGYqDapQCmvmzoB8Kk/sgxpi35ZXSbrUoVQzUwpjoTnnS8XQNw==
X-Received: by 2002:a1c:df07:: with SMTP id w7mr3297996wmg.7.1583402485531;
        Thu, 05 Mar 2020 02:01:25 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 f207sm10440025wme.9.2020.03.05.02.01.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 02:01:24 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: x86: VMX: cleanup VMXON region allocation
Date: Thu,  5 Mar 2020 11:01:21 +0100
Message-Id: <20200305100123.1013667-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor cleanup with no functional change (intended):
- Rename 'kvm_area' to 'vmxon_region'
- Simplify setting revision_id for VMXON region when eVMCS is in use

Vitaly Kuznetsov (2):
  KVM: x86: VMX: rename 'kvm_area' to 'vmxon_region'
  KVM: x86: VMX: untangle VMXON revision_id setting when using eVMCS

 arch/x86/kvm/vmx/vmx.c | 41 ++++++++++++++++++-----------------------
 arch/x86/kvm/vmx/vmx.h | 12 +++++++++---
 2 files changed, 27 insertions(+), 26 deletions(-)
```
#### [PATCH 0/4] KVM: nSVM: first step towards fixing event injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Mar  5 10:13:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11421501
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BADE192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:14:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 916FD2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:14:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="USeffCvG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgCEKNx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 05:13:53 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:50395 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725816AbgCEKNx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 05:13:53 -0500
Received: by mail-wm1-f68.google.com with SMTP id a5so5559396wmb.0;
        Thu, 05 Mar 2020 02:13:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=cxk+MXcOeQV1WCXNQhxSl7i6QKVRGSx/9Z04A+Iz51g=;
        b=USeffCvGW2kT/2nvw5Nshh15XS/mOrJtx1GAM/JerLUzySuvvCWxin5vWI23TGKR/m
         tQFAFp1FGa71JP8HW4kq08UYGOqN4Dx2VlFi/QkN3/wMqIbGeFHvdJvmkpF3pm/6QP8n
         Z/7NoxN40809fdsX7ZklFuQSj6xO8cMDpdngGTFdC34m6w2IRaxzzBYkY/tI9Uu0Wlhk
         Pp4t+kSSO4TncVqzAVTZorMiglcTIIdDk5fkJZzu5CdK72Rw1NAjMcHJoGEoZOgaLNUl
         ByHiM8ysMfiPyPBPBa5RHYJ2b4kInsKpr9dnQnLDzsTSDyL/qkOiutYD4QxaltWVZnS2
         TFuw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=cxk+MXcOeQV1WCXNQhxSl7i6QKVRGSx/9Z04A+Iz51g=;
        b=e6ib+0NOjXix6dycrhxjXeIdWD9GlUtBDHEDkwvrxBUEo6uT0NoqvKlMtUwDv6WBE4
         ZWfn0IzJVNV8fcw9RA3hXUf30bTFFJPR5/jAxoFyktCxuEqo28nOz5FeB+7DVbvSqubA
         f9LHjQXtL/NaydH4CbJrQUPJnYl0XbaEEvzD8ZU9IUmNGqWjtsJvIzhesW4aEX64HUep
         NrEBpgUANHcogtLb2xyHwlJmgmccOmvUp0o5O1WlBnch7G6qEKXHc//XHjDEzuXguBsn
         UQgcO15ANfbyfr/wgnaaI19QjA3RiHQmHCQF2CEX8IYHsS3Ma7hJhO0kMfHXMXVdh4Iw
         bVOQ==
X-Gm-Message-State: ANhLgQ3b/p3kKPO9wyUIRjnPGueS6lQYrbLaerLQ3Smb51li+++y5FKc
        Rm4TnL53Q/pROmw0OQ6C3jypRflc
X-Google-Smtp-Source: 
 ADFU+vtTOHJCj1WO3JX2pSwmBJ2rHiIGvOkj6V7BV0UQ+q4w1huemNS4QWTaP3HgDBcAIVBi2B7fTw==
X-Received: by 2002:a1c:7719:: with SMTP id t25mr8314292wmi.7.1583403230448;
        Thu, 05 Mar 2020 02:13:50 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p15sm8331066wma.40.2020.03.05.02.13.49
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Mar 2020 02:13:49 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: cavery@redhat.com, vkuznets@redhat.com, jan.kiszka@siemens.com,
        wei.huang2@amd.com
Subject: [PATCH 0/4] KVM: nSVM: first step towards fixing event injection
Date: Thu,  5 Mar 2020 11:13:43 +0100
Message-Id: <1583403227-11432-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Event injection in nSVM does not use check_nested_events, which means it
is basically broken.  As a first step, this fixes interrupt injection
which is probably the most complicated case due to the interactions
with V_INTR_MASKING and the host EFLAGS.IF.

This series fixes Cathy's test case that I have sent earlier.

Paolo

Paolo Bonzini (4):
  KVM: nSVM: do not change host intercepts while nested VM is running
  KVM: nSVM: ignore L1 interrupt window while running L2 with
    V_INTR_MASKING=1
  KVM: nSVM: implement check_nested_events for interrupts
  KVM: nSVM: avoid loss of pending IRQ/NMI before entering L2

 arch/x86/kvm/svm.c | 172 ++++++++++++++++++++++++++++++++---------------------
 1 file changed, 103 insertions(+), 69 deletions(-)
```
#### [PATCH v2 0/4] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Thu Mar  5 14:01:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11421889
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8ACFB14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 14:01:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6B88B2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 14:01:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="nK3vdZUi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726579AbgCEOBl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 09:01:41 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:42144 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726173AbgCEOBk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 09:01:40 -0500
Received: by mail-wr1-f68.google.com with SMTP id v11so5198349wrm.9;
        Thu, 05 Mar 2020 06:01:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KdIXn7KFlU+BLAhj4v00VAp1VIZz+zjZjmRj9J5ZrXM=;
        b=nK3vdZUiOeawGy2FGMrVCmtgYTG6YJhGQzXFfPQF+OFXMgJ8t2LLX7PhiRxzrAeVOZ
         yXtUijNaWJd1DKuctoPKJjwn38KRSLrPrNi/ElR76K3SXjwo5PemjnEDn69WvoGO+T2O
         rabQ2E/QAJ9BWYeK7ReieBXAouMPR/dAOnd6XvVyceE3uYB2ShRYCJtdTBrTQwljhxv3
         943AHTqXdu/ceL9X451jfuXfTaV3rs9v77L9fPzsxrIeUhYh3W0793d8kEEPwhIgLmX7
         xeJ89McsYam+LStpRFc3UguXmdWQhFoEDo2b1HYBPI6x68BTtEnW7v2N3Gk5vow3/c54
         QBRw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KdIXn7KFlU+BLAhj4v00VAp1VIZz+zjZjmRj9J5ZrXM=;
        b=rLoC9M2Hc5vBCvQ0aSGlQEK45tW7leUWEifJCu2PM0xKiPtCiszFV35HI+Mem0jHaD
         yEihkrR8z4Q5SomSLtjww04m2QJ4xUpcpgN8T6rLyR5fQCfyja2iyUw8tuJ7iARGLAmy
         JNT93/niFinjID5MQOaKOmGvUGegZrcJNbQ/QzoU46wby61v3r1/Hb5X3A4CUzcuhRaH
         NnqfHHSuxohPgagRTT/qH0YKgReIMXRWCtAIINJeNWgMZbT94QiL7JHiQWyXsARzOOrY
         btYGlhWQe5E8L3H2SxhzzwxIw4PxcazqWMYH3NZmKBCxWTgEOps+Fi+py0Aj5gumbtQh
         HRcA==
X-Gm-Message-State: ANhLgQ2ZxnlOcDCI7rURmgcLiP2zNEoJmeW6t9GDXKW3h9I1+Uzi/Up0
        Gh4ixL7EQTEo99qEkXVi3A1ztAK3
X-Google-Smtp-Source: 
 ADFU+vv2/QxGHV9O6XBuCWBrYgNKKMmH0ZypNp2Rpgx4JtApn6S7E21yuLskeOJ9lyqbIE+tj7rG3Q==
X-Received: by 2002:a5d:6385:: with SMTP id p5mr10261244wru.167.1583416898425;
        Thu, 05 Mar 2020 06:01:38 -0800 (PST)
Received: from linux.local ([31.154.166.148])
        by smtp.gmail.com with ESMTPSA id
 c72sm3379824wme.35.2020.03.05.06.01.37
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 06:01:37 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v2 0/4] x86/kvm/hyper-v: add support for synthetic debugger
Date: Thu,  5 Mar 2020 16:01:38 +0200
Message-Id: <20200305140142.413220-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

In the first patch the first mode is being implemented in the sense that
it simply exits to user-space when a control MSR is being written and
when the pending MSR is being set, then it's up-to userspace to
implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

Jon Doron (4):
  x86/kvm/hyper-v: Align the hcall param for kvm_hyperv_exit
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |  21 +++++
 arch/x86/include/asm/kvm_host.h    |  13 +++
 arch/x86/kvm/hyperv.c              | 136 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |   5 ++
 arch/x86/kvm/trace.h               |  25 ++++++
 arch/x86/kvm/x86.c                 |   9 ++
 include/uapi/linux/kvm.h           |  11 +++
 7 files changed, 218 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/2] KVM: Drop gfn_to_pfn_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Thu Mar  5 15:57:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11422083
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57ACD17EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 15:57:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 37612208CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 15:57:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dQtCxkPu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726191AbgCEP5Q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 10:57:16 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:52730 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726184AbgCEP5O (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Mar 2020 10:57:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583423833;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=IxoeEnt35O7QTmRZWyr2gwugnfgn2HRJVIdogRILp7k=;
        b=dQtCxkPub7SE1lGVzRmyEOJVXWbvZq/fj+FaEgtuHOc1UIPfOUcI3TJKJ5b7A6bvQTUAC+
        WYxzAMSSR46DhjqGNtRHQLuEFud0jr/pSwTioQHRSAtVk4vufNBD1yhVsk4fFsUk4+7vz5
        4JWEdOTlBIqJEsEcz8dFYdCz9ZNmlXY=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-167-FnlzzZx7M2CEOesy1lHj7g-1; Thu, 05 Mar 2020 10:57:12 -0500
X-MC-Unique: FnlzzZx7M2CEOesy1lHj7g-1
Received: by mail-qv1-f71.google.com with SMTP id g11so3294437qvl.3
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 07:57:12 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IxoeEnt35O7QTmRZWyr2gwugnfgn2HRJVIdogRILp7k=;
        b=Lu/Jj7l5MWzse23Zep9LEni5M2PueLdIHVva1BlNYpU7GvADPEFqPoDrWWZTqRADYt
         JdPIEIaaR3nmTVzIysWQpf0gndI53L0ILq+q7G4+9M4uFxD277/2Awh7ItXGdEZT85l3
         oqLV9gDXK59FtB5agO7miCveOWltnwkwcAf1uUHkzY15sNVGcC1ecdivDNC6sX34l8uw
         RZerbdltSq6Xlt8zSj22ZJ6Cnoo9vPSXVhlml6Ms39Sxn4oDuIUv/q2DmOybwfMSYJR7
         cFJL5xzh7PBdf7/DTcjCIT8Tu5XJxGiGHQOXw92AJg4eokwI7UB8CJQsJMiSoIdsyZCn
         qn/A==
X-Gm-Message-State: ANhLgQ1MNiTJzYMcvuBFY7STnaReFYJ0bthVlKpworVk1aUmdERtrV/u
        IYjS7HsfPjy3AyQAAYGLi2C1kwqfKos8mB8Wuec+EUks90HRBH2L/BKttZlgvG6+xFzrvOHi0of
        Gn2igK7cQITo5
X-Received: by 2002:a37:6258:: with SMTP id w85mr9019903qkb.206.1583423831397;
        Thu, 05 Mar 2020 07:57:11 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vsWJ9ChA7AqjC8mi6Y+3B8RoMTG+j/4BpcKmFtJ6GioCGLGAqBL5bV82PTSSCUwsx+KztqSCw==
X-Received: by 2002:a37:6258:: with SMTP id w85mr9019888qkb.206.1583423831166;
        Thu, 05 Mar 2020 07:57:11 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 a18sm14815053qkg.48.2020.03.05.07.57.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 07:57:10 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: linmiaohe@huawei.com, Paolo Bonzini <pbonzini@redhat.com>,
        peterx@redhat.com
Subject: [PATCH v2 0/2] KVM: Drop gfn_to_pfn_atomic()
Date: Thu,  5 Mar 2020 10:57:07 -0500
Message-Id: <20200305155709.118503-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- add a document update for indirect sp fast path which referenced
  gfn_to_pfn_atomic(). [linmiaohe]

Please review, thanks.

Peter Xu (2):
  KVM: Documentation: Update fast page fault for indirect sp
  KVM: Drop gfn_to_pfn_atomic()

 Documentation/virt/kvm/locking.rst | 9 ++++-----
 include/linux/kvm_host.h           | 1 -
 virt/kvm/kvm_main.c                | 6 ------
 3 files changed, 4 insertions(+), 12 deletions(-)
```
#### [RFC PATCH 0/1] kvm: selftests: Add TEST_FAIL macro
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Thu Mar  5 17:25:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11422419
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C52A1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 17:25:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BABA2073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 17:25:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Vfd9qM7P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727206AbgCERZw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 12:25:52 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:23754 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725938AbgCERZv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 12:25:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583429151;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=LNaeYUuZ/I8N5sWDPpA8Jaa5r8899vfI3fz+QN5P+JQ=;
        b=Vfd9qM7PAiQtytjcKpI/TgPKhPaYUvVvKpj2Dca27L820+7A5sFeN7wkO7VI6RZQuAcZ0Y
        hNH3bKcaM3STmdnnaIsKJw7+Tfij93aXMynWKjg9qT1Khy+TlDMlL6khKcLCxrxfd0dTKe
        z5YoCMOPZhOCC9pJ4Qh9zQ5u1FlSTe8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-311-gvySo0gPN4e7waaKGzfUMA-1; Thu, 05 Mar 2020 12:25:47 -0500
X-MC-Unique: gvySo0gPN4e7waaKGzfUMA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D1B9C1005509;
        Thu,  5 Mar 2020 17:25:45 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-124.gru2.redhat.com
 [10.97.116.124])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 704005C219;
        Thu,  5 Mar 2020 17:25:41 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: shuah@kernel.org, tglx@linutronix.de, thuth@redhat.com,
        sean.j.christopherson@intel.com, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC PATCH 0/1] kvm: selftests: Add TEST_FAIL macro
Date: Thu,  5 Mar 2020 14:25:31 -0300
Message-Id: <20200305172532.9360-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following patch's commit message is self-explanatory about this proposal.

I adjusted to use TEST_FAIL only a few source files, in reality it will
need to change all the ones listed below. I will proceed with the
adjustments if this new macro idea is accepted.

$ find . -type f -name "*.c" -exec grep -l "TEST_ASSERT(false" {} \;
./lib/kvm_util.c
./lib/io.c
./lib/x86_64/processor.c
./lib/aarch64/ucall.c
./lib/aarch64/processor.c
./x86_64/vmx_dirty_log_test.c
./x86_64/state_test.c
./x86_64/vmx_tsc_adjust_test.c
./x86_64/svm_vmcall_test.c
./x86_64/evmcs_test.c
./x86_64/vmx_close_while_nested_test.c

Wainer dos Santos Moschetta (1):
  kvm: selftests: Add TEST_FAIL macro

 tools/testing/selftests/kvm/dirty_log_test.c             | 7 +++----
 tools/testing/selftests/kvm/include/test_util.h          | 3 +++
 tools/testing/selftests/kvm/x86_64/cr4_cpuid_sync_test.c | 4 ++--
 3 files changed, 8 insertions(+), 6 deletions(-)
```
#### [PATCH v2 0/2] KVM: VMX: cleanup VMXON region allocation
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Mar  5 18:37:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11422459
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 471D414B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 18:37:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 27C35208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 18:37:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QsKwVdNi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726191AbgCEShf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 13:37:35 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:20411 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725977AbgCEShe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 13:37:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583433453;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=yAqQBw7q9t4PgjjslG8SKuDvnBf92v/kO5v+bREuIJ8=;
        b=QsKwVdNig4WhDoGRSAZ9fExtP2Rf+hAS3lG6zWo43eDdMPdkCIZ6IiLjgP3wD0e4RM5b8U
        NtrVWUbm+0IE5xr8OplUGLoHJ3kyblxRTCEVBVKGOE5cAmtVWqoylr3i6dKZdbd2FaDHky
        TUZTM5B2GVa4dmIrvMT9gXC/6gg5FG4=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-407-kIX4yRHjMVKe7R3mFs7Egw-1; Thu, 05 Mar 2020 13:37:30 -0500
X-MC-Unique: kIX4yRHjMVKe7R3mFs7Egw-1
Received: by mail-wr1-f72.google.com with SMTP id p5so2610787wrj.17
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 10:37:30 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=yAqQBw7q9t4PgjjslG8SKuDvnBf92v/kO5v+bREuIJ8=;
        b=oZfuU1k37OFTE7gKrZDhTSZly9waHFqHD6qKKEafDv6L6B9k3DERdnWhskZCG1htnK
         tetRtxSyCYctNwNSj9UEnoEDyIUOdmwdJb8BBZe/KyUPNhNkziOCYW/OLv822JuQPRkz
         SGs+07G0/VgsC06SwnIYG7M9SW3UI8iTvPXhWqG55MWXwGvbik6ANtllQ8CN3RA3L5Jk
         32v/5h1bPpoivcGT2Chgi4E8jOr8Si4BtS015nTWkZTdy26hgHLPbO4Zu1mVTCLFSmPg
         NzqIuvlkQyYAGLTBf3ALLsj+g+tYuxF3JMWns5QamF+XVHjSv/yz0GtRSk9VLY2xDDtu
         2IkA==
X-Gm-Message-State: ANhLgQ31mCKM1SOxH3R/6ZvhSSCK99OJtG6nbaVMsrdSmqC9cDkFsC6B
        NQFDxE4pac2/s1byug91qG7wZOc4cFtez3zd57Ghrx/Ee6aouKbBCx43joeQmPRxTMuy8tj0Kk+
        pBly6O2HrI0BQ
X-Received: by 2002:adf:94a3:: with SMTP id 32mr296960wrr.276.1583433449214;
        Thu, 05 Mar 2020 10:37:29 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vvhHuGisFdgFqK+06OOLUW1ehdv33D3YUuQu/8RquwUxfPL95K46vixq9wQPfQFCkl0BQDXoQ==
X-Received: by 2002:adf:94a3:: with SMTP id 32mr296951wrr.276.1583433449033;
        Thu, 05 Mar 2020 10:37:29 -0800 (PST)
Received: from vitty.brq.redhat.com (g-server-2.ign.cz. [91.219.240.2])
        by smtp.gmail.com with ESMTPSA id
 u17sm9369121wmj.47.2020.03.05.10.37.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 10:37:28 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/2] KVM: VMX: cleanup VMXON region allocation
Date: Thu,  5 Mar 2020 19:37:23 +0100
Message-Id: <20200305183725.28872-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor cleanup with no functional change (intended):
- Rename 'kvm_area' to 'vmxon_region'
- Simplify setting revision_id for VMXON region when eVMCS is in use

Changes since v1:
- Patches prefix ('KVM: VMX:' now) [Sean Christopherson]
- Add Sean's R-b to PATCH1
- Do not rename alloc_vmcs_cpu() to alloc_vmx_area_cpu() and add a comment
  explaining why we call VMXON region 'VMCS' [Sean Christopherson]

Vitaly Kuznetsov (2):
  KVM: VMX: rename 'kvm_area' to 'vmxon_region'
  KVM: VMX: untangle VMXON revision_id setting when using eVMCS

 arch/x86/kvm/vmx/vmx.c | 42 +++++++++++++++++++-----------------------
 arch/x86/kvm/vmx/vmx.h | 12 +++++++++---
 2 files changed, 28 insertions(+), 26 deletions(-)
```
