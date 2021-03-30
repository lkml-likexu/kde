

#### [PATCH v2 0/3] ppc: Enable 2nd DAWR support on Power10
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Mon Mar 29 04:19:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12169483
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EFDADC433C1
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 04:21:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B59CF6195A
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 04:21:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229911AbhC2EUy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 00:20:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3552 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229441AbhC2EUZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 29 Mar 2021 00:20:25 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12T44MqS186987;
        Mon, 29 Mar 2021 00:20:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=IR07W5LIxpzREqRvvNBiQMSIF2pzsSh0D44KCLXQzvE=;
 b=KgB0LIDxMH2NfnuB0mEEJmpdC0HLU+DI0WXdvjDoWRLaOuaXB/euOk4QFLms2npqhazI
 AJfRaZyBfH1rI6+VxdxXLBkARdOCaaEQxBG9WgrYn3eMy0QRjPqkMlNAMI4kJJl67ccx
 tclGDmtPMmLODl4Dq8TungUV5KNecxpau31Vxh3TLNv3jXx3JTAsoPGltxj1T0ErMzhU
 VirzdJDaAKf8dEAu5YwqNuplQhJ+wtJw1aQHQL5WqVIXp4YRda0dAiDe+coPAsH4Sny/
 cLdRO5YcVrprvmtavSZt0pxF1ZntU1aTghDu84hwOYSHsupS6alFfGz5Ia3DK/R0iICP yA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhm4b4xk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 00:20:01 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12T48dcp000687;
        Mon, 29 Mar 2021 00:20:01 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhm4b4x2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 00:20:01 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12T4HcLS013743;
        Mon, 29 Mar 2021 04:19:58 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma02fra.de.ibm.com with ESMTP id 37hvb88rqh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 29 Mar 2021 04:19:58 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12T4JuVe23855434
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 29 Mar 2021 04:19:56 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 357FB4C046;
        Mon, 29 Mar 2021 04:19:56 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EF9974C050;
        Mon, 29 Mar 2021 04:19:52 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.34.103])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 29 Mar 2021 04:19:52 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Subject: [PATCH v2 0/3] ppc: Enable 2nd DAWR support on Power10
Date: Mon, 29 Mar 2021 09:49:03 +0530
Message-Id: <20210329041906.213991-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: EyPXyix-vOAiCXaFRJQj6eMW92jyQKB3
X-Proofpoint-ORIG-GUID: mWY1CsqNmpM7uAnNDJHE2hqxBV5MI2bb
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-29_02:2021-03-26,2021-03-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 clxscore=1011
 spamscore=0 lowpriorityscore=0 phishscore=0 impostorscore=0 suspectscore=0
 priorityscore=1501 mlxlogscore=964 malwarescore=0 bulkscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103250000
 definitions=main-2103290029
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables 2nd DAWR support on p10 qemu guest. 2nd
DAWR is new watchpoint added in Power10 processor. Kernel/kvm
patches are already in[1].

Patches apply fine on qemu/master branch (9e2e9fe3df9f).

v1: https://lore.kernel.org/r/20200723104220.314671-1-ravi.bangoria@linux.ibm.com
[Apologies for long gap]
v1->v2:
  - Introduce machine capability cap-dawr1 to enable/disable
    the feature. By default, 2nd DAWR is OFF for guests even
    when host kvm supports it. User has to manually enable it
    with -machine cap-dawr1=on if he wishes to use it.
  - Split the header file changes into separate patch. (Sync
    headers from v5.12-rc3)

[1] https://git.kernel.org/torvalds/c/bd1de1a0e6eff

Ravi Bangoria (3):
  Linux headers: update from 5.12-rc3
  ppc: Rename current DAWR macros and variables
  ppc: Enable 2nd DAWR support on p10

 hw/ppc/spapr.c                                 | 34 ++++++++++
 hw/ppc/spapr_caps.c                            | 32 +++++++++
 include/hw/ppc/spapr.h                         |  8 ++-
 include/standard-headers/drm/drm_fourcc.h      | 23 ++++++-
 include/standard-headers/linux/input.h         |  2 +-
 include/standard-headers/rdma/vmw_pvrdma-abi.h |  7 ++
 linux-headers/asm-generic/unistd.h             |  4 +-
 linux-headers/asm-mips/unistd_n32.h            |  1 +
 linux-headers/asm-mips/unistd_n64.h            |  1 +
 linux-headers/asm-mips/unistd_o32.h            |  1 +
 linux-headers/asm-powerpc/kvm.h                |  2 +
 linux-headers/asm-powerpc/unistd_32.h          |  1 +
 linux-headers/asm-powerpc/unistd_64.h          |  1 +
 linux-headers/asm-s390/unistd_32.h             |  1 +
 linux-headers/asm-s390/unistd_64.h             |  1 +
 linux-headers/asm-x86/kvm.h                    |  1 +
 linux-headers/asm-x86/unistd_32.h              |  1 +
 linux-headers/asm-x86/unistd_64.h              |  1 +
 linux-headers/asm-x86/unistd_x32.h             |  1 +
 linux-headers/linux/kvm.h                      | 89 ++++++++++++++++++++++++++
 linux-headers/linux/vfio.h                     | 27 ++++++++
 target/ppc/cpu.h                               |  6 +-
 target/ppc/kvm.c                               | 12 ++++
 target/ppc/kvm_ppc.h                           |  7 ++
 target/ppc/translate_init.c.inc                | 21 +++++-
 25 files changed, 274 insertions(+), 11 deletions(-)
```
#### [PATCH v4 00/16] KVM: x86/pmu: Add basic support to enable Guest PEBS
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon Mar 29 05:41:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12169537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EDCE0C433C1
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 05:50:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C50DF61964
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 05:50:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229557AbhC2Ftk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 01:49:40 -0400
Received: from mga07.intel.com ([134.134.136.100]:15632 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229515AbhC2FtZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 29 Mar 2021 01:49:25 -0400
IronPort-SDR: 
 cLO0AHKdrH1kXzRcwbUeJjOuZYhT0CrookATUbqjWo0VZeNfuXUhy5dO3bMn5SzpU3vo+KIv08
 kQKQHZsPtzLA==
X-IronPort-AV: E=McAfee;i="6000,8403,9937"; a="255478706"
X-IronPort-AV: E=Sophos;i="5.81,285,1610438400";
   d="scan'208";a="255478706"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Mar 2021 22:49:23 -0700
IronPort-SDR: 
 t/wHvNuUyofxcUzRtyW16YZzvE2GIz4pUu4kq7TFfIAGk2lkMT5gCBZMNLI1DMCP5mmc3an8CS
 IHjUPuthU6JA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,285,1610438400";
   d="scan'208";a="417506661"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 28 Mar 2021 22:49:20 -0700
From: Like Xu <like.xu@linux.intel.com>
To: peterz@infradead.org, Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: eranian@google.com, andi@firstfloor.org, kan.liang@linux.intel.com,
        wei.w.wang@intel.com, Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v4 00/16] KVM: x86/pmu: Add basic support to enable Guest PEBS
 via DS
Date: Mon, 29 Mar 2021 13:41:21 +0800
Message-Id: <20210329054137.120994-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest Precise Event Based Sampling (PEBS) feature can provide
an architectural state of the instruction executed after the guest
instruction that exactly caused the event. It needs new hardware
facility only available on Intel Ice Lake Server platforms. This
patch set enables the basic PEBS via DS feature for KVM guests on ICX.

We can use PEBS feature on the Linux guest like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

To emulate guest PEBS facility for the above perf usages,
we need to implement 2 code paths:

1) Fast path

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
This path is used in most common use cases.

2) Slow path

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure.

The previous version [0] enables both fast path and slow path, which
seems a bit more complex as the first step. In this patchset, we want
to start with the fast path to get the basic guest PEBS enabled while
keeping the slow path disabled. More focused discussion on the slow
path [1] is planned to be put to another patchset in the next step.

Compared to later versions in subsequent steps, the functionality
to support host-guest PEBS both enabled and the functionality to
emulate guest PEBS when the counter is cross-mapped are missing
in this patch set (neither of these are typical scenarios).

With the basic support, the guest can retrieve the correct PEBS
information from its own PEBS records on the Ice Lake servers.
And we expect it should work when migrating to another Ice Lake
and no regression about host perf is expected.

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
   Conclusion: the profiling results on the guest are similar tothat on the host.

Please check more details in each commit and feel free to comment.

Previous:
[0] https://lore.kernel.org/kvm/20210104131542.495413-1-like.xu@linux.intel.com/
[1] https://lore.kernel.org/kvm/20210115191113.nktlnmivc3edstiv@two.firstfloor.org/

v3->v4 Changelog:
- Update this cover letter and propose a new upstream plan;
[PERF]
- Drop check host DS and move handler to handle_pmi_common();
- Pass "struct kvm_pmu *" to intel_guest_get_msrs();
- Propose new assignment logic for perf_guest_switch_msr();
- Introduce x86_pmu.pebs_vmx for future capability maintenance;
[KVM]
- Add kvm_pmu_cap to optimize perf_get_x86_pmu_capability;
- Raising PEBS PMI only when OVF_BIT 62 is not set;
- Make vmx_icl_pebs_cpu specific for PEBS-PDIR emulation;
- Fix a bug for fixed_ctr_ctrl_mask;
- Add two minor refactoring patches for reuse;

Like Xu (16):
  perf/x86/intel: Add x86_pmu.pebs_vmx for Ice Lake Servers
  perf/x86/intel: Handle guest PEBS overflow PMI for KVM guest
  perf/x86/core: Pass "struct kvm_pmu *" to determine the guest values
  KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
  KVM: x86/pmu: Introduce the ctrl_mask value for fixed counter
  KVM: x86/pmu: Reprogram guest PEBS event to emulate guest PEBS counter
  KVM: x86/pmu: Add IA32_PEBS_ENABLE MSR emulation for extended PEBS
  KVM: x86/pmu: Add IA32_DS_AREA MSR emulation to manage guest DS buffer
  KVM: x86/pmu: Add PEBS_DATA_CFG MSR emulation to support adaptive PEBS
  KVM: x86: Set PEBS_UNAVAIL in IA32_MISC_ENABLE when PEBS is enabled
  KVM: x86/pmu: Adjust precise_ip to emulate Ice Lake guest PDIR counter
  KVM: x86/pmu: Move pmc_speculative_in_use() to arch/x86/kvm/pmu.h
  KVM: x86/pmu: Disable guest PEBS before vm-entry in two cases
  KVM: x86/pmu: Add kvm_pmu_cap to optimize perf_get_x86_pmu_capability
  KVM: x86/cpuid: Refactor host/guest CPU model consistency check
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64

 arch/x86/events/core.c            |   5 +-
 arch/x86/events/intel/core.c      |  93 +++++++++++++++++++++++---
 arch/x86/events/perf_event.h      |   5 +-
 arch/x86/include/asm/kvm_host.h   |  16 +++++
 arch/x86/include/asm/msr-index.h  |   6 ++
 arch/x86/include/asm/perf_event.h |   5 +-
 arch/x86/kvm/cpuid.c              |  24 ++-----
 arch/x86/kvm/cpuid.h              |   5 ++
 arch/x86/kvm/pmu.c                |  49 ++++++++++----
 arch/x86/kvm/pmu.h                |  37 +++++++++++
 arch/x86/kvm/vmx/capabilities.h   |  26 ++++++--
 arch/x86/kvm/vmx/pmu_intel.c      | 105 ++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c            |  25 ++++++-
 arch/x86/kvm/vmx/vmx.h            |   2 +-
 arch/x86/kvm/x86.c                |  14 ++--
 15 files changed, 339 insertions(+), 78 deletions(-)
```
#### [PATCH v2 0/2] KVM: x86: hyper-v: Fix TSC page update after
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Mar 29 11:47:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12169969
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C654DC433E0
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 11:49:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F6736195C
	for <kvm@archiver.kernel.org>; Mon, 29 Mar 2021 11:49:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230434AbhC2Lsb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 29 Mar 2021 07:48:31 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59570 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231304AbhC2LsK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 29 Mar 2021 07:48:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617018490;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=XBBhbaK4RjgYEf7pYCtNqcj852KHocFegJV6ZZyHbik=;
        b=SUIb51kMGcZ7cwd/bpdwSb6/t0CPfyh1j/qBl3EGcDMv3GvfIVYMDZE1Uv88GeErPaw52E
        CRMc/CYRs2NsPmfoak9MwFTtmncV1CSqjnNBbkaXL/O7zrhPFcJqZlmAI7C/XKu6eatS1k
        0W2NB8uF85H2FjI/p/KTgX9xuQJNOM0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-487-kZar8vd3PgO6U-y2Jj34Fw-1; Mon, 29 Mar 2021 07:48:08 -0400
X-MC-Unique: kZar8vd3PgO6U-y2Jj34Fw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CB0CC180FCA5;
        Mon, 29 Mar 2021 11:48:06 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 765FB1001B2C;
        Mon, 29 Mar 2021 11:48:01 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2 0/2] KVM: x86: hyper-v: Fix TSC page update after
 KVM_SET_CLOCK(0) call
Date: Mon, 29 Mar 2021 13:47:58 +0200
Message-Id: <20210329114800.164066-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1:
- Fix the issue by casting 'hv_clock->system_time' to s64 in 
 compute_tsc_page_parameters() instead of clamping its value to zero in
 kvm_guest_time_update() [Paolo]

Original description:

I discovered that after KVM_SET_CLOCK(0) TSC page value in the guest can
go through the roof and apparently we have a signedness issue when the
update is performed. Fix the issue and add a selftest.

Vitaly Kuznetsov (2):
  KVM: x86: hyper-v: Properly divide maybe-negative
    'hv_clock->system_time' in compute_tsc_page_parameters()
  selftests: kvm: Check that TSC page value is small after
    KVM_SET_CLOCK(0)

 arch/x86/kvm/hyperv.c                             |  9 ++++++---
 tools/testing/selftests/kvm/x86_64/hyperv_clock.c | 13 +++++++++++--
 2 files changed, 17 insertions(+), 5 deletions(-)
```
