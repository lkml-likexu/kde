

#### [PATCH kvm-unit-tests v2 0/3] svm: INIT test and test_run on selected
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Fri Jul 17 11:34:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11669997
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D9DE13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 11:34:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 651C321702
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 11:34:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dT6p3ftt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726627AbgGQLe2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 07:34:28 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:26224 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726113AbgGQLe2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jul 2020 07:34:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594985667;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ap+OTTNHSy5NfknFXFXO4vdY1KCy5ST6u153yyPpCug=;
        b=dT6p3ftt8LJJgkZnPcrHLGBpYr7gSC21EzqT05PuIbJcHsUCCVRNlW2xZ+r/IvjEDtshHc
        OZf6Z7LETRpLjPerOgzOwvD+KTL56VGIMv6yF+XCC5tlNaU9BiMntH2f4NiF1NQnHgOeYv
        KuTsWyircDeFeZeRUf7DjQAGtcv8zXc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-64-vXZJzFuYPJuX1-pA46pgYQ-1; Fri, 17 Jul 2020 07:34:24 -0400
X-MC-Unique: vXZJzFuYPJuX1-pA46pgYQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0CF41100A8E7;
        Fri, 17 Jul 2020 11:34:23 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8C09B19C58;
        Fri, 17 Jul 2020 11:34:22 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2 0/3] svm: INIT test and test_run on selected
 vcpu
Date: Fri, 17 Jul 2020 07:34:19 -0400
Message-Id: <20200717113422.19575-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INIT intercept test and the ability to execute test_run
on a selected vcpu

Changes from v1:

1) Incorporated feedback:
	- DR6/DR7/CR2/DEBUGCTL should not be need.
	- HSAVE should be set to a different page for each vCPU
	- The on_cpu to set EFER should be in setup_svm
	- The on_cpu to set cr0/cr3/cr4 should be in setup_vm.

2) Execute tests on selected vcpu using on_cpu_async so the tests
may use the on_cpu functions without causing an ipi_lock deadlock.

3) Added additional test svm_init_startup_test which inits the vcpu and
restarts with sipi.

Cathy Avery (3):
  svm: Add ability to execute test via test_run on a vcpu other than
    vcpu 0
  svm: INIT and STARTUP ipi test
  svm: INIT intercept test

 lib/x86/vm.c    | 18 +++++++++
 lib/x86/vm.h    |  7 ++++
 x86/cstart64.S  |  1 +
 x86/svm.c       | 24 +++++++++++-
 x86/svm.h       |  2 +
 x86/svm_tests.c | 97 +++++++++++++++++++++++++++++++++++++++++++++++++
 6 files changed, 148 insertions(+), 1 deletion(-)
```
#### [PATCH v1 0/1] Synic default SCONTROL MSR needs to be enabled
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri Jul 17 12:52:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11670081
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E209B159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 12:52:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C895A2070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 12:52:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Q5XzwZ0H"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726238AbgGQMww (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 08:52:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57272 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726205AbgGQMwv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jul 2020 08:52:51 -0400
Received: from mail-wm1-x32a.google.com (mail-wm1-x32a.google.com
 [IPv6:2a00:1450:4864:20::32a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B43D2C061755
        for <kvm@vger.kernel.org>; Fri, 17 Jul 2020 05:52:51 -0700 (PDT)
Received: by mail-wm1-x32a.google.com with SMTP id c80so14655441wme.0
        for <kvm@vger.kernel.org>; Fri, 17 Jul 2020 05:52:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=j9uK5iW2gxdUCw+ZyRXugfIrp0K9oX6FsRLPbqZGRqQ=;
        b=Q5XzwZ0HCl7Xb8okB3FDL/Oii6D8txYaepRLF1YCYG1vlIL7h5tSOvtuGWrsaACmZC
         qt+e0fPwtx3GeLx4jHNtziCQJy0T2Vj1P3LnLgm47w+gv0itiPoZaM6mjbmS5X2lF5i4
         6jjzXL/DT3T3zPQtcX497PxAhxv9hyA2UE9OHEupFlggHcRmWGq5Sljez1qcpltit6c1
         PTDrzYpCeGwl8i9E4WfQFZxGaLjOTMk6PHfvtrXNbq2Zor9XK4G5Stu/yGsSasxL6Dwz
         4Q/KA3KLoxIJ4mhodDJxCvHmzQ5AxdelkODQ/rRmLkXkhBI+xFHkCgeuwJiKMH2ssH2V
         mp8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=j9uK5iW2gxdUCw+ZyRXugfIrp0K9oX6FsRLPbqZGRqQ=;
        b=sl2Df/lPx50qbie0UPNMLX0RvLOw/YG0fdP97olK7NhQgH52je5+CW6dOPVAQ7V+X7
         yKHZ4teY/EiMKOTXmdHVJdoDo9q16PbLNox+UKICbB5nA3bfFCBJC83s4tebn22U7uSp
         cbH5mLOhJdc4mN6YOFZ/6rzv69e1s2FlGwbX4oxU3pxr7sPEzqH4vbpUyNDOXadUC/gM
         UBwTqnC8/Biyx1EeBCTOtLnrrTbysLqmNydBbDlTph+r5rhJKStZebXZoRu7FeAHXWIY
         Qp1dhM1RXaHwDz0RRgW8b5GWSaxJfFxD1JAVXGjs7W51Fjlfp7JQOuUVIcpeJyo9qCup
         BNQA==
X-Gm-Message-State: AOAM5336qiECC32L4mww24MH589bHKmdXQTiX8OlsFg38mhyGipD8RLM
        a4lkJ0S0zCBDCQQy1EL/vsflOdZw
X-Google-Smtp-Source: 
 ABdhPJw2htQYvpk7kOZtx39k6Ngrgu7QOJYaVdN49bEZ2rM7FBrvRaeOhqfUODdX9SRiOtcykjYLAQ==
X-Received: by 2002:a05:600c:2144:: with SMTP id
 v4mr9788581wml.128.1594990370262;
        Fri, 17 Jul 2020 05:52:50 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-64.inter.net.il. [84.229.155.64])
        by smtp.gmail.com with ESMTPSA id
 z132sm15160699wmb.21.2020.07.17.05.52.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 17 Jul 2020 05:52:49 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org
Cc: vkuznets@redhat.com, pbonzini@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 0/1] Synic default SCONTROL MSR needs to be enabled
Date: Fri, 17 Jul 2020 15:52:37 +0300
Message-Id: <20200717125238.1103096-1-arilou@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Based on an analysis of the HyperV firmwares (Gen1 and Gen2) it seems
like the SCONTROL is not being set to the ENABLED state as like we have
thought.

Also from a test done by Vitaly Kuznetsov, running a nested HyperV it
was concluded that the first access to the SCONTROL MSR with a read
resulted with the value of 0x1, aka HV_SYNIC_CONTROL_ENABLE.

It's important to note that this diverges from the value states in the
HyperV TLFS of 0.

Jon Doron (1):
  x86/kvm/hyper-v: Synic default SCONTROL MSR needs to be enabled

 arch/x86/kvm/hyperv.c | 1 +
 1 file changed, 1 insertion(+)
```
#### [v3 00/15] powerpc/perf: Add support for power10 PMU Hardware
##### From: Athira Rajeev <atrajeev@linux.vnet.ibm.com>

```c
From patchwork Fri Jul 17 14:38:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Athira Rajeev <atrajeev@linux.vnet.ibm.com>
X-Patchwork-Id: 11670461
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CA0714E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:38:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5261F22B51
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 14:38:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727938AbgGQOit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 10:38:49 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14134 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726859AbgGQOis (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jul 2020 10:38:48 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEWp0O140989;
        Fri, 17 Jul 2020 10:38:38 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32b9ag0kfs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:38:38 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEU73d024878;
        Fri, 17 Jul 2020 14:38:35 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 327527kf7e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 14:38:35 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06HEcV8w12714466
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jul 2020 14:38:31 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3376B4C050;
        Fri, 17 Jul 2020 14:38:31 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7978D4C046;
        Fri, 17 Jul 2020 14:38:28 +0000 (GMT)
Received: from localhost.localdomain.localdomain (unknown [9.77.207.73])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jul 2020 14:38:28 +0000 (GMT)
From: Athira Rajeev <atrajeev@linux.vnet.ibm.com>
To: mpe@ellerman.id.au
Cc: linuxppc-dev@lists.ozlabs.org, maddy@linux.vnet.ibm.com,
        mikey@neuling.org, kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        ego@linux.vnet.ibm.com, svaidyan@in.ibm.com, acme@kernel.org,
        jolsa@kernel.org
Subject: [v3 00/15] powerpc/perf: Add support for power10 PMU Hardware
Date: Fri, 17 Jul 2020 10:38:12 -0400
Message-Id: <1594996707-3727-1-git-send-email-atrajeev@linux.vnet.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-17_06:2020-07-17,2020-07-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 priorityscore=1501 spamscore=0 mlxscore=0 phishscore=0 suspectscore=1
 lowpriorityscore=0 impostorscore=0 clxscore=1011 malwarescore=0
 mlxlogscore=807 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2007170108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The patch series adds support for power10 PMU hardware.

Patches 1..3 are the clean up patches which refactors the way how
PMU SPR's are stored in core-book3s and in KVM book3s, as well as update
data type for PMU cache_events.

Patches 12 and 13 adds base support for perf extended register
capability in powerpc. Support for extended regs in power10 is
covered in patches 14,15

Other patches includes main changes to support for power10 PMU.

Anju T Sudhakar (2):
  powerpc/perf: Add support for outputting extended regs in perf
    intr_regs
  tools/perf: Add perf tools support for extended register capability in
    powerpc

Athira Rajeev (10):
  powerpc/perf: Update cpu_hw_event to use `struct` for storing MMCR
    registers
  KVM: PPC: Book3S HV: Cleanup updates for kvm vcpu MMCR
  powerpc/perf: Update Power PMU cache_events to u64 type
  KVM: PPC: Book3S HV: Save/restore new PMU registers
  powerpc/perf: power10 Performance Monitoring support
  powerpc/perf: Ignore the BHRB kernel address filtering for P10
  powerpc/perf: Add Power10 BHRB filter support for
    PERF_SAMPLE_BRANCH_IND_CALL/COND
  powerpc/perf: BHRB control to disable BHRB logic when not used
  powerpc/perf: Add extended regs support for power10 platform
  tools/perf: Add perf tools support for extended regs in power10

Madhavan Srinivasan (3):
  powerpc/perf: Add support for ISA3.1 PMU SPRs
  powerpc/xmon: Add PowerISA v3.1 PMU SPRs
  powerpc/perf: Add power10_feat to dt_cpu_ftrs
---
Changes from v2 -> v3
- Addressed review comments from Michael Neuling,
  Michael Ellerman, Gautham Shenoy and Paul Mackerras

Changes from v1 -> v2
- Added support for extended regs in powerpc
  for power9/power10 platform ( patches 12 to 15)
- Addressed change/removal of some event codes
  in the PMU driver
---

 Documentation/virt/kvm/api.rst                  |   3 +
 arch/powerpc/include/asm/kvm_book3s_asm.h       |   2 +-
 arch/powerpc/include/asm/kvm_host.h             |   6 +-
 arch/powerpc/include/asm/perf_event_server.h    |  22 +-
 arch/powerpc/include/asm/processor.h            |   4 +
 arch/powerpc/include/asm/reg.h                  |   9 +
 arch/powerpc/include/uapi/asm/kvm.h             |   9 +-
 arch/powerpc/include/uapi/asm/perf_regs.h       |  20 +-
 arch/powerpc/kernel/asm-offsets.c               |   5 +
 arch/powerpc/kernel/cpu_setup_power.S           |   8 +
 arch/powerpc/kernel/dt_cpu_ftrs.c               |  26 ++
 arch/powerpc/kernel/sysfs.c                     |   8 +
 arch/powerpc/kvm/book3s_hv.c                    |  38 ++-
 arch/powerpc/kvm/book3s_hv_interrupts.S         |   8 +
 arch/powerpc/kvm/book3s_hv_rmhandlers.S         |  36 +-
 arch/powerpc/perf/Makefile                      |   2 +-
 arch/powerpc/perf/core-book3s.c                 | 108 ++++--
 arch/powerpc/perf/generic-compat-pmu.c          |   2 +-
 arch/powerpc/perf/internal.h                    |   1 +
 arch/powerpc/perf/isa207-common.c               |  91 +++--
 arch/powerpc/perf/isa207-common.h               |  37 ++-
 arch/powerpc/perf/mpc7450-pmu.c                 |  23 +-
 arch/powerpc/perf/perf_regs.c                   |  44 ++-
 arch/powerpc/perf/power10-events-list.h         |  70 ++++
 arch/powerpc/perf/power10-pmu.c                 | 425 ++++++++++++++++++++++++
 arch/powerpc/perf/power5+-pmu.c                 |  19 +-
 arch/powerpc/perf/power5-pmu.c                  |  19 +-
 arch/powerpc/perf/power6-pmu.c                  |  18 +-
 arch/powerpc/perf/power7-pmu.c                  |  19 +-
 arch/powerpc/perf/power8-pmu.c                  |   2 +-
 arch/powerpc/perf/power9-pmu.c                  |   8 +-
 arch/powerpc/perf/ppc970-pmu.c                  |  26 +-
 arch/powerpc/platforms/powernv/idle.c           |  22 +-
 arch/powerpc/xmon/xmon.c                        |  13 +
 tools/arch/powerpc/include/uapi/asm/kvm.h       |   9 +-
 tools/arch/powerpc/include/uapi/asm/perf_regs.h |  20 +-
 tools/perf/arch/powerpc/include/perf_regs.h     |   8 +-
 tools/perf/arch/powerpc/util/header.c           |   9 +-
 tools/perf/arch/powerpc/util/perf_regs.c        |  55 +++
 tools/perf/arch/powerpc/util/utils_header.h     |  15 +
 40 files changed, 1117 insertions(+), 152 deletions(-)
 create mode 100644 arch/powerpc/perf/power10-events-list.h
 create mode 100644 arch/powerpc/perf/power10-pmu.c
 create mode 100644 tools/perf/arch/powerpc/util/utils_header.h
```
#### [kvm-unit-tests PATCH 0/3] PV tests part 1
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Jul 17 14:58:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11670573
Return-Path: <SRS0=oLpl=A4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4339C14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 15:00:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 34C652076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jul 2020 15:00:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726761AbgGQO62 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jul 2020 10:58:28 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30058 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726232AbgGQO61 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jul 2020 10:58:27 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEWtoI017229;
        Fri, 17 Jul 2020 10:58:27 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32b8k32b80-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:58:26 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06HEX2bl017930;
        Fri, 17 Jul 2020 10:58:26 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32b8k32b7c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 10:58:26 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06HEpNUX027866;
        Fri, 17 Jul 2020 14:58:24 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 3274pgxkxc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Jul 2020 14:58:24 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06HEwLdR29163776
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jul 2020 14:58:21 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 62AD842041;
        Fri, 17 Jul 2020 14:58:21 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 94E5742049;
        Fri, 17 Jul 2020 14:58:20 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jul 2020 14:58:20 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 0/3] PV tests part 1
Date: Fri, 17 Jul 2020 10:58:10 -0400
Message-Id: <20200717145813.62573-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-17_06:2020-07-17,2020-07-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=837
 impostorscore=0 bulkscore=0 clxscore=1015 priorityscore=1501 phishscore=0
 malwarescore=0 lowpriorityscore=0 suspectscore=0 adultscore=0 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007170108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's start bringing in some more PV related code.

Somehow I missed that we can also have a key in a exception new
PSW. The interesting bit when skrf is active is that if such a PSW is
loaded on an exception it will result in a specification exception and
not a special operation exception like on all other key related
actions.

The third patch adds a basic guest UV call API test. It has mostly
been used for firmware testing but I also think it's good to have a
building block like this for more PV tests.


GIT: https://github.com/frankjaa/kvm-unit-tests/tree/queue


Janosch Frank (3):
  s390x: Add custom pgm cleanup function
  s390x: skrf: Add exception new skey test and add test to unittests.cfg
  s390x: Ultavisor guest API test

 lib/s390x/asm/interrupt.h |   1 +
 lib/s390x/asm/uv.h        |  68 +++++++++++++++++
 lib/s390x/interrupt.c     |   9 +++
 s390x/Makefile            |   1 +
 s390x/skrf.c              |  81 ++++++++++++++++++++
 s390x/unittests.cfg       |   7 ++
 s390x/uv-guest.c          | 156 ++++++++++++++++++++++++++++++++++++++
 7 files changed, 323 insertions(+)
 create mode 100644 lib/s390x/asm/uv.h
 create mode 100644 s390x/uv-guest.c
```
