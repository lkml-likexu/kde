

#### [RFC PATCH v11 0/9] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Tue Apr 21 03:22:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11500343
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BFAF5159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 03:23:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC4D920679
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 03:23:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727928AbgDUDXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 23:23:24 -0400
Received: from foss.arm.com ([217.140.110.172]:57300 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725989AbgDUDXY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 23:23:24 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 601D331B;
        Mon, 20 Apr 2020 20:23:23 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 7ADBD3F6CF;
        Mon, 20 Apr 2020 20:23:16 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v11 0/9] Enable ptp_kvm for arm64
Date: Tue, 21 Apr 2020 11:22:55 +0800
Message-Id: <20200421032304.26300-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. Here, we enable kvm ptp
for arm64.

change log:

from v11 to v10:
        (1) rebase code on 5.7_rc2.
        (2) remove support for arm32, as kvm support for arm32 will be
removed [1]
        (3) add error report in ptp_kvm initialization.

from v10 to v9:
        (1) change code base to v5.5.
	(2) enable ptp_kvm both for arm32 and arm64.
        (3) let user choose which of virtual counter or physical counter
should return when using crosstimestamp mode of ptp_kvm for arm/arm64.
        (4) extend input argument for getcrosstimestamp API.

from v8 to v9:
        (1) move ptp_kvm.h to driver/ptp/
        (2) replace license declaration of ptp_kvm.h the same with other
header files in the same directory.

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v6 to v7:
        (1) include the omitted clocksource_id.h in last version.
        (2) reorder the header file in patch.
        (3) refine some words in commit message to make it more impersonal.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.

from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.

from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1] https://patchwork.kernel.org/cover/11373351/

Jianyong Wu (8):
  psci: export psci conduit get helper.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  psci: Add hypercall service for ptp_kvm.
  ptp: arm64: Enable ptp_kvm for arm/arm64
  ptp: extend input argument for getcrosstimestamp API
  arm64: add mechanism to let user choose which counter to return
  arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

 drivers/clocksource/arm_arch_timer.c        | 33 ++++++++
 drivers/firmware/psci/psci.c                |  1 +
 drivers/net/ethernet/intel/e1000e/ptp.c     |  3 +-
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_chardev.c                   |  8 +-
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm64.c                 | 53 ++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 85 ++++++--------------
 drivers/ptp/ptp_kvm_x86.c                   | 89 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 21 +++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/ptp_clock_kernel.h            |  3 +-
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 include/uapi/linux/ptp_clock.h              |  4 +-
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/hypercalls.c                   | 44 +++++++++-
 21 files changed, 322 insertions(+), 72 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH v3 0/2] KVM: VMX: Unionize vcpu_vmx.exit_reason
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Apr 21 07:53:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11500655
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1955881
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 07:53:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0ABC52084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 07:53:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726801AbgDUHxc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 03:53:32 -0400
Received: from mga06.intel.com ([134.134.136.31]:22871 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726013AbgDUHxa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 03:53:30 -0400
IronPort-SDR: 
 V87Zx9FlJOhzDrcpyCdZ/XRcktCvUykjxKvNZD+D3xfof+M85kVcSULd+yAiveu/5CD1IEdvAD
 jtFu/mqkkhSA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Apr 2020 00:53:29 -0700
IronPort-SDR: 
 Vj82jaY9B1ev7KooQq1BLw9M55NkWk53ByTlltJPDwJZeqauwGQmYffo17X2xEd3cNMxXcu4+0
 8CFCpRWpiQyQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,409,1580803200";
   d="scan'208";a="245611198"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga007.fm.intel.com with ESMTP; 21 Apr 2020 00:53:29 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v3 0/2] KVM: VMX: Unionize vcpu_vmx.exit_reason
Date: Tue, 21 Apr 2020 00:53:26 -0700
Message-Id: <20200421075328.14458-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor fixup patch for a mishandled conflict between the vmcs.INTR_INFO
caching series and the union series, plus the actual unionization patch
rebased onto kvm/queue, commit 604e8bba0dc5 ("KVM: Remove redundant ...").

Sean Christopherson (2):
  KVM: nVMX: Drop a redundant call to vmx_get_intr_info()
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/kvm/vmx/nested.c | 39 ++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    | 65 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 ++++++++++++++-
 3 files changed, 83 insertions(+), 46 deletions(-)
```
#### [PATCH 0/2] KVM: VMX: Tscdeadline timer emulation fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Tue Apr 21 11:20:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11501115
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63FC6112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 11:20:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B8072076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 11:20:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="CfWmPsEx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728473AbgDULUh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 07:20:37 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47584 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726741AbgDULUg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 07:20:36 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DC5F2C061A0F;
        Tue, 21 Apr 2020 04:20:36 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id x26so6615978pgc.10;
        Tue, 21 Apr 2020 04:20:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=5INuHDo8RkxBQI1c6D+UV2G0d783U8nnilEvfGe2hU0=;
        b=CfWmPsExRg8TFieNHdsCul6CDg7KQXi/925bXG18wBDsPfbylGrKs3CqHnCJ9Qcf9/
         Rvff0UYzO3ndeb8H9FyA1PzZywww/9/xujQc3HvsMj+UexNj27db/Thn41aIlXas386Q
         VEvSDzx/pdf+vKkOZzNOX7+UHb/zQa73Z/a2STyvXatMTDBIO8hyAV0F92jqZnpIYaLl
         af9aPGoBqS/39UJZnFXjqHbQKN3+MDO89fry8qdV0PShnrH49zamFChLdvmymTATRJS/
         QqaiZT0G0Oel9hvi5BHGXJBKIjhSd5q5vKmUbVPKWFw+AQkB9Glx2Ra8TgiqJBWs1Ail
         gcAw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=5INuHDo8RkxBQI1c6D+UV2G0d783U8nnilEvfGe2hU0=;
        b=AAAQDinV0laZSidiq/88VlZVEqC5ooV5w9jUJKDFOD/Km5rwfOj/Ogf7Vp9Tuw8BaK
         q4pc61x6YDdHH5wX1rBuy8Pz3wA095RtSq5d0ro4eFhvBcZixDFW1wuq5iFtFE8ada2i
         FRlAHiRt++DNsgfSJsWbs57n7bwMbIA2RDtMISOmF2D0SkXFNON5or6Qxb6g50/jVEle
         gJidKLk3Mh5h88rxs7fd4pxIUsOMkDc9CuSffW8Angj3dcG6QAxXqmd6DGNt1ymYrXwO
         hyju1R4Es8Vd4jyrzEdbYIx5w5ApCJjSDJVQI46hNEAGNV4RYs21+geiYqpiWX8pO21Q
         vhAg==
X-Gm-Message-State: AGi0Pua10nWuh8WiZQWoGSMRv5TrWUGlaqp9WR51pYxim2xJi3FmzTdL
        B1D1maTUVO16IxRISJHeZLQbvjtv
X-Google-Smtp-Source: 
 APiQypI/2oekz+UfVOVdGkdIhyx1xtrd01Pv3bmvUrf59arfqv4RQYs+6JXxh8y6C4lQx7kAZiyJ1g==
X-Received: by 2002:a63:2e44:: with SMTP id u65mr1855828pgu.142.1587468036204;
        Tue, 21 Apr 2020 04:20:36 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 f74sm8643176pje.3.2020.04.21.04.20.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Apr 2020 04:20:35 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH 0/2] KVM: VMX: Tscdeadline timer emulation fastpath
Date: Tue, 21 Apr 2020 19:20:24 +0800
Message-Id: <1587468026-15753-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IPI and Timer cause the main vmexits in cloud environment observation, 
after single target IPI fastpath, let's optimize tscdeadline timer 
latency by introducing tscdeadline timer emulation fastpath , it will 
skip various KVM related checks when possible. i.e. after vmexit due 
to tscdeadline timer emulation, handle it and vmentry immediately 
without checking various kvm stuff when possible. 

Testing on SKX Server.

cyclictest in guest(w/o mwait exposed, adaptive advance lapic timer is default -1):

5632.75ns -> 4559.25ns, 19%

kvm-unit-test/vmexit.flat:

w/o APICv, w/o advance timer:
tscdeadline_immed: 4780.75 -> 3851    19.4%
tscdeadline:       7474    -> 6528.5  12.7%

w/o APICv, w/ adaptive advance timer default -1:
tscdeadline_immed: 4845.75 -> 3930.5  18.9%
tscdeadline:       6048    -> 5871.75    3%

w/ APICv, w/o avanced timer:
tscdeadline_immed: 2919    -> 2467.75 15.5%
tscdeadline:       5661.75 -> 5188.25  8.4%

w/ APICv, w/ adaptive advance timer default -1:
tscdeadline_immed: 3018.5  -> 2561    15.2%
tscdeadline:       4663.75 -> 4626.5     1%

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>

Wanpeng Li (2):
  KVM: X86: TSCDEADLINE MSR emulation fastpath
  KVM: VMX: Handle preemption timer fastpath

 arch/x86/include/asm/kvm_host.h |   3 ++
 arch/x86/kvm/lapic.c            |  20 ++------
 arch/x86/kvm/lapic.h            |  16 +++++++
 arch/x86/kvm/vmx/vmx.c          | 101 ++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/x86.c              |  55 +++++++++++++++++++---
 5 files changed, 167 insertions(+), 28 deletions(-)
```
#### [PATCH v2 0/3] KVM: x86: move nested-related kvm_x86_ops to a
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue Apr 21 16:56:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11502003
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A949F112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:57:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8807C2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:57:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RQiKQXkD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729626AbgDUQ5K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 12:57:10 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:60567 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728951AbgDUQ4k (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Apr 2020 12:56:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587488199;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=Rf0y5DMEXDv12IlLkk2NBKoWJYu1ZKBxtnnwzy0NcJ0=;
        b=RQiKQXkDckNC4+IfRXjOsRZzFSbUXPywSQQ2c5Sdv0qD1WtFzA4KiYikF+6gdRvLXxeTNA
        K8fFzGmDEqgLNPgXkKLEWdYEvV1G95jdTJ0GCsIUOYAAKzYyiKWeU7d8k6QjDKJcU7Iuod
        1okoo7J8xzgh/oliLVIQRDxH4LQjfT0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-170-Fn-gG8nQN_qT5Vt52099EQ-1; Tue, 21 Apr 2020 12:56:37 -0400
X-MC-Unique: Fn-gG8nQN_qT5Vt52099EQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9B204DBA5;
        Tue, 21 Apr 2020 16:56:36 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 693CC48;
        Tue, 21 Apr 2020 16:56:33 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v2 0/3] KVM: x86: move nested-related kvm_x86_ops to a
 separate struct
Date: Tue, 21 Apr 2020 12:56:29 -0400
Message-Id: <20200421165632.20157-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 3 follows the lead of the kvm_pmu_ops and moves callbacks related
to nested virtualization to a separate struct.  Patches 1 and 2 are
preparation (patch 1 mostly makes some lines shorter, while patch 2
avoids semantic changes in KVM_GET_SUPPORTED_HV_CPUID).

While this reintroduces some pointer chasing that was removed in
afaf0b2f9b80 ("KVM: x86: Copy kvm_x86_ops by value to eliminate layer
of indirection", 2020-03-31), the cost is small compared to retpolines
and anyway most of the callbacks are not even remotely on a fastpath.
In fact, only check_nested_events should be called during normal VM
runtime.  When static calls are merged into Linux my plan is to use them
instead of callbacks, and that will finally make things fast again by
removing the retpolines.

Thanks,

Paolo

v1->v2: shorten names by removing "nested".  I did _not_ introduce copying.

Paolo Bonzini (3):
  KVM: x86: check_nested_events is never NULL
  KVM: eVMCS: check if nesting is enabled
  KVM: x86: move nested-related kvm_x86_ops to a separate struct

 arch/x86/include/asm/kvm_host.h | 29 +++++++++++++++-------------
 arch/x86/kvm/hyperv.c           |  4 ++--
 arch/x86/kvm/svm/nested.c       |  6 +++++-
 arch/x86/kvm/svm/svm.c          | 13 +++++--------
 arch/x86/kvm/svm/svm.h          |  3 ++-
 arch/x86/kvm/vmx/evmcs.c        | 24 ++++++++++++-----------
 arch/x86/kvm/vmx/nested.c       | 16 +++++++++-------
 arch/x86/kvm/vmx/nested.h       |  2 ++
 arch/x86/kvm/vmx/vmx.c          |  7 +------
 arch/x86/kvm/x86.c              | 34 ++++++++++++++++-----------------
 10 files changed, 72 insertions(+), 66 deletions(-)
```
#### [PATCH v1 00/15] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Tue Apr 21 18:41:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502069
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D158A92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4CE32072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="Up1q4aSo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729426AbgDUSmV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:21 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:57885 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729380AbgDUSmV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494540; x=1619030540;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=Bn059cn0UaWuunziZy7N2XUwHB6IqIik8uzBmA7RfbM=;
  b=Up1q4aSoFwpqz3UGDJs0Ad+/NJeESEo2HHD32xWI6YHVYulPbIHcF72w
   rpcjHTVPbwkFHcpL0TswkI7B/MYJo9XGZMCwnHDyLsCBWzv3O09AQxkYx
   2PV/yJHc7oFkcqSFtvLbTrRzZMm/u238x9rK4P05rx5UU7rlVz1eXiV0O
   s=;
IronPort-SDR: 
 TnmuHb1KMexz/kTaI5cRCyeYQBuDMZfo1e1qgKu+Qu6ZvfoV7wtrFL11mlK3PV0brJ/BleTI+K
 LTYhxttSSnkQ==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="26614410"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2a-119b4f96.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 21 Apr 2020 18:42:06 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2a-119b4f96.us-west-2.amazon.com (Postfix) with
 ESMTPS id AE10C1A4668;
        Tue, 21 Apr 2020 18:42:05 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:05 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:41:56 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 00/15] Add support for Nitro Enclaves
Date: Tue, 21 Apr 2020 21:41:35 +0300
Message-ID: <20200421184150.68011-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D25UWC004.ant.amazon.com (10.43.162.201) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes highly sensitive data and
runs in a VM, can be separated from other applications running in the same VM.
This application then runs in a separate VM than the primary VM, namely an
enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPU, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [2]. An enclave does not have a disk or a network device
attached.

The following patch series covers the NE driver for enclave lifetime management.
It provides an ioctl interface to the user space and includes a PCI device
driver that is the means of communication with the hypervisor running on the
host where the primary VM and the enclave are launched.

The proposed solution is following the KVM model and uses the KVM API to be able
to create and set resources for enclaves. An additional ioctl command, besides
the ones provided by KVM, is used to start an enclave and setup the addressing
for the communication channel and an enclave unique id.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] http://man7.org/linux/man-pages/man7/vsock.7.html
---

Patch Series Changelog

The patch series is built on top of v5.7-rc2.

v1

* The current patch series.

---

Andra Paraschiv (15):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for enclave vm creation
  nitro_enclaves: Add logic for enclave vcpu creation
  nitro_enclaves: Add logic for enclave memory region set
  nitro_enclaves: Add logic for enclave start
  nitro_enclaves: Add logic for enclave termination
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 MAINTAINERS                                   |   11 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/amazon/Kconfig                   |   28 +
 drivers/virt/amazon/Makefile                  |   19 +
 drivers/virt/amazon/nitro_enclaves/Makefile   |   23 +
 .../virt/amazon/nitro_enclaves/ne_misc_dev.c  | 1039 +++++++++++++++++
 .../virt/amazon/nitro_enclaves/ne_misc_dev.h  |  120 ++
 .../virt/amazon/nitro_enclaves/ne_pci_dev.c   |  675 +++++++++++
 .../virt/amazon/nitro_enclaves/ne_pci_dev.h   |  266 +++++
 include/linux/nitro_enclaves.h                |   23 +
 include/uapi/linux/nitro_enclaves.h           |   52 +
 12 files changed, 2260 insertions(+)
 create mode 100644 drivers/virt/amazon/Kconfig
 create mode 100644 drivers/virt/amazon/Makefile
 create mode 100644 drivers/virt/amazon/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
```
