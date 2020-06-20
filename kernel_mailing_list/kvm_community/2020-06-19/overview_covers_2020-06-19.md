

#### [PATCH v3 0/9] Generalize memory encryption models
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Fri Jun 19 02:05:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11613107
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8130613A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 02:06:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E27E2088E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 02:06:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="nW1oBNml"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729157AbgFSCGK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 18 Jun 2020 22:06:10 -0400
Received: from ozlabs.org ([203.11.71.1]:45405 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725912AbgFSCGK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Jun 2020 22:06:10 -0400
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49p2GS0p6Yz9sRR; Fri, 19 Jun 2020 12:06:08 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1592532368;
        bh=3plDeY4nzUK5TNGdwXZl3rLW3KII0RZMy/LwwJOA+zQ=;
        h=From:To:Cc:Subject:Date:From;
        b=nW1oBNmlP9ShhH8fWDNLyBsl6jA7kUTKJwRFNh2J37Y3xmsaaxqVbvZdpy69Bi7DT
         6VUTVMKEDfU02D7AT08Kz2cCutW9+sgr9M3FMgPWCmgTqowCG0zfbZ7k2e3CNrTLUJ
         I++GvWVXqU1p2B6VuhqiA1zLHNEoBx5NL9wwJCHo=
From: David Gibson <david@gibson.dropbear.id.au>
To: qemu-devel@nongnu.org, brijesh.singh@amd.com, pair@us.ibm.com,
        pbonzini@redhat.com, dgilbert@redhat.com, frankja@linux.ibm.com
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, kvm@vger.kernel.org,
        qemu-ppc@nongnu.org, mst@redhat.com, mdroth@linux.vnet.ibm.com,
        Richard Henderson <rth@twiddle.net>, cohuck@redhat.com,
        pasic@linux.ibm.com, Eduardo Habkost <ehabkost@redhat.com>,
        David Gibson <david@gibson.dropbear.id.au>,
        qemu-s390x@nongnu.org, david@redhat.com
Subject: [PATCH v3 0/9] Generalize memory encryption models
Date: Fri, 19 Jun 2020 12:05:53 +1000
Message-Id: <20200619020602.118306-1-david@gibson.dropbear.id.au>
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
"host-trust-limitation" property pointing to a platform specific
object which configures and manages the specific details.

For now this series covers just AMD SEV and POWER PEF.  I'm hoping it
can be extended to cover the Intel and s390 mechanisms as well,
though.

Please apply.

Changes since RFCv2:
 * Rebased
 * Removed preliminary SEV cleanups (they've been merged)
 * Changed name to "host trust limitation"
 * Added migration blocker to the PEF code (based on SEV's version)
Changes since RFCv1:
 * Rebased
 * Fixed some errors pointed out by Dave Gilbert

David Gibson (9):
  host trust limitation: Introduce new host trust limitation interface
  host trust limitation: Handle memory encryption via interface
  host trust limitation: Move side effect out of
    machine_set_memory_encryption()
  host trust limitation: Rework the "memory-encryption" property
  host trust limitation: Decouple kvm_memcrypt_*() helpers from KVM
  host trust limitation: Add Error ** to HostTrustLimitation::kvm_init
  spapr: Add PEF based host trust limitation
  spapr: PEF: block migration
  host trust limitation: Alter virtio default properties for protected
    guests

 accel/kvm/kvm-all.c                  |  40 ++------
 accel/kvm/sev-stub.c                 |   7 +-
 accel/stubs/kvm-stub.c               |  10 --
 backends/Makefile.objs               |   2 +
 backends/host-trust-limitation.c     |  29 ++++++
 hw/core/machine.c                    |  61 +++++++++--
 hw/i386/pc_sysfw.c                   |   6 +-
 include/exec/host-trust-limitation.h |  72 +++++++++++++
 include/hw/boards.h                  |   2 +-
 include/qemu/typedefs.h              |   1 +
 include/sysemu/kvm.h                 |  17 ----
 include/sysemu/sev.h                 |   4 +-
 target/i386/sev.c                    | 146 ++++++++++++---------------
 target/ppc/Makefile.objs             |   2 +-
 target/ppc/pef.c                     |  89 ++++++++++++++++
 15 files changed, 325 insertions(+), 163 deletions(-)
 create mode 100644 backends/host-trust-limitation.c
 create mode 100644 include/exec/host-trust-limitation.h
 create mode 100644 target/ppc/pef.c
```
#### [RFC PATCH v13 0/9] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Fri Jun 19 09:30:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11613567
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E77814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:30:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB6D02080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 09:30:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731163AbgFSJav (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 05:30:51 -0400
Received: from foss.arm.com ([217.140.110.172]:49090 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729718AbgFSJau (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 05:30:50 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id B5DD12B;
        Fri, 19 Jun 2020 02:30:48 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 883613F71F;
        Fri, 19 Jun 2020 02:30:42 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        Wei.Chen@arm.com, jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v13 0/9] Enable ptp_kvm for arm64
Date: Fri, 19 Jun 2020 17:30:24 +0800
Message-Id: <20200619093033.58344-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we offen use ntp (sync time with remote network clock)
to sync time in VM. But the precision of ntp is subject to network delay
so it's difficult to sync time in a high precision.

kvm virtual ptp clock (ptp_kvm) offers another way to sync time in VM,
as the remote clock locates in the host instead of remote network clock.
It targets to sync time between guest and host in virtualization
environment and in this way, we can keep the time of all the VMs running
in the same host in sync. In general, the delay of communication between
host and guest is quiet small, so ptp_kvm can offer time sync precision
up to in order of nanosecond. Please keep in mind that ptp_kvm just
limits itself to be a channel which transmit the remote clock from
host to guest and leaves the time sync jobs to an application, eg. chrony,
in usersapce in VM.

How ptp_kvm works:
After ptp_kvm initialized, there will be a new device node under
/dev called ptp%d. A guest userspace service, like chrony, can use this
device to get host walltime, sometimes also counter cycle, which depends
on the service it calls. Then this guest userspace service can use those
data to do the time sync for guest.
here is a rough sketch to show how kvm ptp clock works.

|----------------------------|              |--------------------------|
|       guest userspace      |              |          host            |
|ioctl -> /dev/ptp%d         |              |                          |
|       ^   |                |              |                          |
|----------------------------|              |                          |
|       |   | guest kernel   |              |                          |
|       |   V      (get host walltime/counter cycle)                   |
|      ptp_kvm -> hypercall - - - - - - - - - - ->hypercall service    |
|                         <- - - - - - - - - - - -                     |
|----------------------------|              |--------------------------|

1. time sync service in guest userspace call ptp device through /dev/ptp%d.
2. ptp_kvm module in guest recive this request then invoke hypercall to
route into host kernel to request host walltime/counter cycle.
3. ptp_kvm hypercall service in host response to the request and send data
back.
4. ptp (not ptp_kvm) in guest copy the data to userspace.

This ptp_kvm implementation focuses itself to step 2 and 3 and step 2 works
in guest comparing step 3 works in host kernel.

change log:
from v12 to v13:
        (1) rebase code on 5.8-rc1.
        (2) this patch set base on 2 patches of 1/8 and 2/8 from Will Decon.
        (3) remove the change to ptp device code of extend getcrosststamp.
        (4) remove the mechanism of letting user choose the counter type in
ptp_kvm for arm64.
        (5) add virtual counter option in ptp_kvm service to let user choose
the specific counter explicitly.

from v11 to v12:
        (1) rebase code on 5.7-rc6 and rebase 2 patches from Will Decon
including 1/11 and 2/11. as these patches introduce discover mechanism of
vendor smccc service.
        (2) rebase ptp_kvm hypercall service from standard smccc to vendor
smccc and add ptp_kvm to vendor smccc service discover mechanism.
        (3) add detail of why we need ptp_kvm and how ptp_kvm works in cover
letter.

from v10 to v11:
        (1) rebase code on 5.7-rc2.
        (2) remove support for arm32, as kvm support for arm32 will be
removed [1]
        (3) add error report in ptp_kvm initialization.

from v9 to v10:
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

Jianyong Wu (7):
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC
  smccc: export smccc conduit get helper.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  arm64/kvm: Add hypercall service for kvm ptp.
  ptp: arm64: Enable ptp_kvm for arm64
  arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (1):
  arm64: Probe for the presence of KVM hypervisor services during boot

 arch/arm64/include/asm/hypervisor.h         | 11 +++
 arch/arm64/kernel/setup.c                   | 36 +++++++++
 arch/arm64/kvm/arm.c                        |  4 +
 arch/arm64/kvm/hypercalls.c                 | 79 +++++++++++++++---
 drivers/clocksource/arm_arch_timer.c        | 26 ++++++
 drivers/firmware/smccc/smccc.c              |  1 +
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm64.c                 | 53 ++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 80 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 89 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 56 +++++++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/Kconfig                            |  4 +
 20 files changed, 413 insertions(+), 75 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH v13 0/9] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Fri Jun 19 13:01:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11614145
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F06A113A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 13:01:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC5F421582
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 13:01:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731806AbgFSNBl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 09:01:41 -0400
Received: from foss.arm.com ([217.140.110.172]:57352 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728606AbgFSNBl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 09:01:41 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id B0B73101E;
        Fri, 19 Jun 2020 06:01:39 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 81B593F6CF;
        Fri, 19 Jun 2020 06:01:33 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        Wei.Chen@arm.com, jianyong.wu@arm.com, nd@arm.com
Subject: [PATCH v13 0/9] Enable ptp_kvm for arm64
Date: Fri, 19 Jun 2020 21:01:11 +0800
Message-Id: <20200619130120.40556-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we offen use ntp (sync time with remote network clock)
to sync time in VM. But the precision of ntp is subject to network delay
so it's difficult to sync time in a high precision.

kvm virtual ptp clock (ptp_kvm) offers another way to sync time in VM,
as the remote clock locates in the host instead of remote network clock.
It targets to sync time between guest and host in virtualization
environment and in this way, we can keep the time of all the VMs running
in the same host in sync. In general, the delay of communication between
host and guest is quiet small, so ptp_kvm can offer time sync precision
up to in order of nanosecond. Please keep in mind that ptp_kvm just
limits itself to be a channel which transmit the remote clock from
host to guest and leaves the time sync jobs to an application, eg. chrony,
in usersapce in VM.

How ptp_kvm works:
After ptp_kvm initialized, there will be a new device node under
/dev called ptp%d. A guest userspace service, like chrony, can use this
device to get host walltime, sometimes also counter cycle, which depends
on the service it calls. Then this guest userspace service can use those
data to do the time sync for guest.
here is a rough sketch to show how kvm ptp clock works.

|----------------------------|              |--------------------------|
|       guest userspace      |              |          host            |
|ioctl -> /dev/ptp%d         |              |                          |
|       ^   |                |              |                          |
|----------------------------|              |                          |
|       |   | guest kernel   |              |                          |
|       |   V      (get host walltime/counter cycle)                   |
|      ptp_kvm -> hypercall - - - - - - - - - - ->hypercall service    |
|                         <- - - - - - - - - - - -                     |
|----------------------------|              |--------------------------|

1. time sync service in guest userspace call ptp device through /dev/ptp%d.
2. ptp_kvm module in guest recive this request then invoke hypercall to
route into host kernel to request host walltime/counter cycle.
3. ptp_kvm hypercall service in host response to the request and send data
back.
4. ptp (not ptp_kvm) in guest copy the data to userspace.

This ptp_kvm implementation focuses itself to step 2 and 3 and step 2 works
in guest comparing step 3 works in host kernel.

change log:
from v12 to v13:
        (1) rebase code on 5.8-rc1.
        (2) this patch set base on 2 patches of 1/8 and 2/8 from Will Decon.
        (3) remove the change to ptp device code of extend getcrosststamp.
        (4) remove the mechanism of letting user choose the counter type in
ptp_kvm for arm64.
        (5) add virtual counter option in ptp_kvm service to let user choose
the specific counter explicitly.

from v11 to v12:
        (1) rebase code on 5.7-rc6 and rebase 2 patches from Will Decon
including 1/11 and 2/11. as these patches introduce discover mechanism of
vendor smccc service.
        (2) rebase ptp_kvm hypercall service from standard smccc to vendor
smccc and add ptp_kvm to vendor smccc service discover mechanism.
        (3) add detail of why we need ptp_kvm and how ptp_kvm works in cover
letter.

from v10 to v11:
        (1) rebase code on 5.7-rc2.
        (2) remove support for arm32, as kvm support for arm32 will be
removed [1]
        (3) add error report in ptp_kvm initialization.

from v9 to v10:
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

Jianyong Wu (7):
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC
  smccc: export smccc conduit get helper.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  arm64/kvm: Add hypercall service for kvm ptp.
  ptp: arm64: Enable ptp_kvm for arm64
  arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (1):
  arm64: Probe for the presence of KVM hypervisor services during boot

 arch/arm64/include/asm/hypervisor.h         | 11 +++
 arch/arm64/kernel/setup.c                   | 36 +++++++++
 arch/arm64/kvm/arm.c                        |  4 +
 arch/arm64/kvm/hypercalls.c                 | 79 +++++++++++++++---
 drivers/clocksource/arm_arch_timer.c        | 26 ++++++
 drivers/firmware/smccc/smccc.c              |  1 +
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  1 +
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm64.c                 | 53 ++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 80 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 89 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 56 +++++++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/Kconfig                            |  4 +
 20 files changed, 413 insertions(+), 75 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH v2 00/11] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Fri Jun 19 15:39:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614405
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27DD990
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:40:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F23620786
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:40:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GcEVB0X6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393871AbgFSPkE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:40:04 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:51195 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2393769AbgFSPjy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 11:39:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592581193;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ApAwRnIqoKoWTTJBXjZG+FIZOjIxYSpaUm7PAr6FKp4=;
        b=GcEVB0X6oP/RKM53ZFPfY9s9uvfMU0l1X56c9CrjLLlAXKC60hcY0tWxwUy6LXhVJKjl8X
        FhExEQWsYMDd3F1SccKXr3xrWVvV5POHrUl0vgw6n+Ah2FzN+Lg9e3A4VjbsXuexkeTJLA
        trqG0kvmLcpHnKys0bxLjxgzBFw+fMA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-506-T7shlh7sO1iy-CaAz7ymvA-1; Fri, 19 Jun 2020 11:39:50 -0400
X-MC-Unique: T7shlh7sO1iy-CaAz7ymvA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7A53F81EDED;
        Fri, 19 Jun 2020 15:39:34 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C18460BF4;
        Fri, 19 Jun 2020 15:39:27 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, thomas.lendacky@amd.com,
        babu.moger@amd.com, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH v2 00/11] KVM: Support guest MAXPHYADDR < host MAXPHYADDR
Date: Fri, 19 Jun 2020 17:39:14 +0200
Message-Id: <20200619153925.79106-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When EPT/NPT is enabled, KVM does not really look at guest physical
address size. Address bits above maximum physical memory size are reserved.
Because KVM does not look at these guest physical addresses, it currently
effectively supports guest physical address sizes equal to the host.

This can be problem when having a mixed setup of machines with 5-level page
tables and machines with 4-level page tables, as live migration can change
MAXPHYADDR while the guest runs, which can theoretically introduce bugs.

In this patch series we add checks on guest physical addresses in EPT
violation/misconfig and NPF vmexits and if needed inject the proper
page faults in the guest.

A more subtle issue is when the host MAXPHYADDR is larger than that of the
guest. Page faults caused by reserved bits on the guest won't cause an EPT
violation/NPF and hence we also check guest MAXPHYADDR and add PFERR_RSVD_MASK
error code to the page fault if needed.

The last 3 patches (i.e. SVM bits and patch 11) are not intended for
immediate inclusion and probably need more discussion.
We've been noticing some unexpected behavior in handling NPF vmexits
on AMD CPUs (see individual patches for details), and thus we are
proposing a workaround (see last patch) that adds a capability that
userspace can use to decide who to deal with hosts that might have
issues supprting guest MAXPHYADDR < host MAXPHYADDR.


Mohammed Gamal (7):
  KVM: x86: Add helper functions for illegal GPA checking and page fault
    injection
  KVM: x86: mmu: Move translate_gpa() to mmu.c
  KVM: x86: mmu: Add guest physical address check in translate_gpa()
  KVM: VMX: Add guest physical address check in EPT violation and
    misconfig
  KVM: SVM: introduce svm_need_pf_intercept
  KVM: SVM: Add guest physical address check in NPF/PF interception
  KVM: x86: SVM: VMX: Make GUEST_MAXPHYADDR < HOST_MAXPHYADDR support
    configurable

Paolo Bonzini (4):
  KVM: x86: rename update_bp_intercept to update_exception_bitmap
  KVM: x86: update exception bitmap on CPUID changes
  KVM: VMX: introduce vmx_need_pf_intercept
  KVM: VMX: optimize #PF injection when MAXPHYADDR does not match

 arch/x86/include/asm/kvm_host.h | 10 ++------
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/mmu.h              |  6 +++++
 arch/x86/kvm/mmu/mmu.c          | 12 +++++++++
 arch/x86/kvm/svm/svm.c          | 41 +++++++++++++++++++++++++++---
 arch/x86/kvm/svm/svm.h          |  6 +++++
 arch/x86/kvm/vmx/nested.c       | 28 ++++++++++++--------
 arch/x86/kvm/vmx/vmx.c          | 45 +++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h          |  6 +++++
 arch/x86/kvm/x86.c              | 29 ++++++++++++++++++++-
 arch/x86/kvm/x86.h              |  1 +
 include/uapi/linux/kvm.h        |  1 +
 12 files changed, 158 insertions(+), 29 deletions(-)
```
#### [kvm-unit-test PATCH 0/2] access: Enable testing guest MAXPHYADDR <
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Fri Jun 19 15:42:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614433
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8E6213A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:44:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B15BC2158C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:44:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A1ZsFljK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404481AbgFSPo1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:44:27 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:22628 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404502AbgFSPoZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 11:44:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592581464;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qYyCmRniSAhtaolPB4KDJxvQUGNyX/WLZinq5HC+Wt4=;
        b=A1ZsFljKYO9AnTHTvsH8jHXXpL7ZxRpriNsha0GmYdpnT0Fbdg+CL8VC0KxSUG7eOiWC2s
        vpBH2QUamlt0FpAvPlMTfXdfMVm+Gbi/g7ahq8wUVnfBK9uTXp0hNM2Vm1kc6/7cNA8y36
        wZuMg3hdcJ4xC9JPMklPrtz2Y7Okjuk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-7-6_3xmcHcNmSweVVsQVgtJQ-1; Fri, 19 Jun 2020 11:44:22 -0400
X-MC-Unique: 6_3xmcHcNmSweVVsQVgtJQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EBF2D80BC52;
        Fri, 19 Jun 2020 15:43:08 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DB12F60BF4;
        Fri, 19 Jun 2020 15:43:06 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Mohammed Gamal <mgamal@redhat.com>
Subject: [kvm-unit-test PATCH 0/2] access: Enable testing guest MAXPHYADDR <
 host MAXPHYADDR
Date: Fri, 19 Jun 2020 17:42:54 +0200
Message-Id: <20200619154256.79216-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Re-enable phys-bits=36 to test guest MAXPHYADDR < host MAXPHYADDR.
Also increase timeout for access tests since using NPT=0 may need
more time.

Mohammed Gamal (2):
  Revert "access: disable phys-bits=36 for now"
  unittests.cfg: Increase timeout for access test

 x86/unittests.cfg | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
```
#### [PATCH 0/2] kvm: x86/cpu: Support guest MAXPHYADDR < host MAXPHYADDR
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
From patchwork Fri Jun 19 15:53:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11614453
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 782A1912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:54:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 574BF21548
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 15:54:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RvEH1OMe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388574AbgFSPyK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 11:54:10 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:29629 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2392414AbgFSPyD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Jun 2020 11:54:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592582042;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=to2CQWKmk1BHkNF1i45gKO63shrPi4wxU7I0QHSWvYE=;
        b=RvEH1OMeGK6hTtAe+GYSjGNeNmGml40C3KLSqlFMzWiBqVDzRE7ipjhwGpfHBsJvNDJplF
        6bJHxb2nADA34G0efupKLaYglwVyMKZGsTvunum+wNBoESuW8LBaL8bvXW9Fe6gtfR9Y5R
        qYyEqXhG3msUJpk6VYswFOugMTnu45k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-384-CVn1DvXPMHOb91P4X9CdmA-1; Fri, 19 Jun 2020 11:54:00 -0400
X-MC-Unique: CVn1DvXPMHOb91P4X9CdmA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 55711108BD09;
        Fri, 19 Jun 2020 15:53:52 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 96C9E5BAD3;
        Fri, 19 Jun 2020 15:53:47 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: qemu-devel@nongnu.org, pbonzini@redhat.com
Cc: ehabkost@redhat.com, mtosatti@redhat.com, rth@twiddle.net,
        kvm@vger.kernel.org, Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH 0/2] kvm: x86/cpu: Support guest MAXPHYADDR < host MAXPHYADDR
Date: Fri, 19 Jun 2020 17:53:42 +0200
Message-Id: <20200619155344.79579-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds support for KVM_CAP_HAS_SMALLER_MAXPHYADDR to QEMU.
Some processors might not handle GUEST_MAXPHYADDR < HOST_MAXPHYADDR in
the expected manner. Hence, we added KVM_CAP_HAS_SMALLER_MAXPHYADDR to
KVM.
In this implementation KVM is queried for KVM_CAP_HAS_SMALLER_MAXPHYADDR
when setting vCPU physical bits, and if the CPU doesn't support 
KVM_CAP_HAS_SMALLER_MAXPHYADDR the ,phys-bits is ignore and host phyiscal
bits are used. A warning message is printed to the user.

Mohammed Gamal (2):
  kvm: Add support for KVM_CAP_HAS_SMALLER_MAXPHYADDR
  x86/cpu: Handle GUEST_MAXPHYADDR < HOST_MAXPHYADDR for hosts that
    don't support it

 linux-headers/linux/kvm.h |  1 +
 target/i386/cpu.c         | 11 +++++++++++
 target/i386/kvm.c         |  5 +++++
 target/i386/kvm_i386.h    |  1 +
 4 files changed, 18 insertions(+)
```
#### [RFC v9 00/11] vhost: ring format independence
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Fri Jun 19 18:22:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11614891
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2234A14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:23:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07AD121527
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:23:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="eNgDG8eo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388969AbgFSSXT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 14:23:19 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:39201 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388374AbgFSSXS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 14:23:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592590997;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=bc8bgBZaKAykX+oT4Ghe9dJSFsYjpNWBpF2Ak/zUniM=;
        b=eNgDG8eopkX9HAO9j+AuBxLrTJ9ATfQYCWMVs9BWRN4gCvtqhWf0u7cDo2TsfoOPsPKCrK
        KuJsfHw7aWPESto5Qp1FZo/I4T2NZwig3BsGtXCK5Hg2ZlQRJoX6WpfWgTCRv2OVyy99Uj
        7rRukWLxAT3teDbCLTx8/4Gh4qayDrk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-178-78tk4Hn8OS2BD-oyfUyQKg-1; Fri, 19 Jun 2020 14:23:13 -0400
X-MC-Unique: 78tk4Hn8OS2BD-oyfUyQKg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B2264800053;
        Fri, 19 Jun 2020 18:23:12 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-14.ams2.redhat.com
 [10.36.113.14])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1F73B7C1E4;
        Fri, 19 Jun 2020 18:23:05 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: mst@redhat.com
Cc: kvm list <kvm@vger.kernel.org>,
        Stefano Garzarella <sgarzare@redhat.com>,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC v9 00/11] vhost: ring format independence
Date: Fri, 19 Jun 2020 20:22:51 +0200
Message-Id: <20200619182302.850-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

Used ring is similar: we fetch into an independent struct first,
convert that to IOV later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

For used descriptors, this allows keeping track of the buffer length
without need to rescan IOV.

This seems to perform better on UDP stream tests, but a little bit worse on
RR tests and TCP streams, based on a microbenchmark.
More testing would be very much appreciated.

changes from v8:
        - fixes fetch_descs returning "no descriptors available" when
          only few descriptors were available, stalling the communications.
        - minor syntax errors in intermediate commits.
        - skipping checking for sane max_descs if vhost device is not going to
          use worker like vDPA devices.

changes from v7:
        - squashed in fixes. no longer hangs but still known
          to cause data corruption for some people. under debug.

changes from v6:
        - fixes some bugs introduced in v6 and v5

changes from v5:
        - addressed comments by Jason: squashed API changes, fixed up discard

changes from v4:
        - added used descriptor format independence
        - addressed comments by jason
        - fixed a crash detected by the lkp robot.

changes from v3:
        - fixed error handling in case of indirect descriptors
        - add BUG_ON to detect buffer overflow in case of bugs
                in response to comment by Jason Wang
        - minor code tweaks

Changes from v2:
        - fixed indirect descriptor batching
                reported by Jason Wang

Changes from v1:
        - typo fixes

Michael S. Tsirkin (11):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched get_vq_desc version
  vhost/net: pass net specific struct pointer
  vhost: reorder functions
  vhost: format-independent API for used buffers
  vhost/net: convert to new API: heads->bufs
  vhost/net: avoid iov length math
  vhost/test: convert to the buf API
  vhost/scsi: switch to buf APIs
  vhost/vsock: switch to the buf API
  vhost: drop head based APIs

 drivers/vhost/net.c   | 174 ++++++++++----------
 drivers/vhost/scsi.c  |  73 +++++----
 drivers/vhost/test.c  |  22 +--
 drivers/vhost/vhost.c | 372 +++++++++++++++++++++++++++---------------
 drivers/vhost/vhost.h |  44 +++--
 drivers/vhost/vsock.c |  30 ++--
 6 files changed, 435 insertions(+), 280 deletions(-)
```
#### [PATCH 0/4] arm64/x86: KVM: Introduce KVM_CAP_STEAL_TIME
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri Jun 19 18:46:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11614929
Return-Path: <SRS0=UAw1=AA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E1B390
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:46:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C6BF21531
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 19 Jun 2020 18:46:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I5LPmvFI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388041AbgFSSqg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 19 Jun 2020 14:46:36 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:33028 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731358AbgFSSqg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Jun 2020 14:46:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592592395;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=m0FpzCva/zyn/UMs7J4w8ZtycrPgdRAxriFzKZK3P20=;
        b=I5LPmvFIgCYfpFvZPzb3XxhJn5c0qeClkVfb448XfPd4EKs2AChB0fjpTK/aXE5Tfc9o66
        ZsG+f8o9D9yjvHgdQRwOH9uMRKFX0EHxePxUrukQ4TERRPgqrOM5URuoBezydDcGS6WoJz
        lfy1hPu1vlpCLmRXvngIDZmnJh5RqoU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-164-3iUouf49P-q72fQsgHn2hg-1; Fri, 19 Jun 2020 14:46:33 -0400
X-MC-Unique: 3iUouf49P-q72fQsgHn2hg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 87D3BEC1A0;
        Fri, 19 Jun 2020 18:46:32 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.110])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C160F60BF4;
        Fri, 19 Jun 2020 18:46:30 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, steven.price@arm.com
Subject: [PATCH 0/4] arm64/x86: KVM: Introduce KVM_CAP_STEAL_TIME
Date: Fri, 19 Jun 2020 20:46:25 +0200
Message-Id: <20200619184629.58653-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a KVM CAP for steal time to arm64 and x86.
For arm64 the cap resolves a couple issues described in the second
patch's commit message. The cap isn't necessary for x86, but is
added for consistency.

Thanks,
drew

Andrew Jones (4):
  KVM: Documentation minor fixups
  arm64/x86: KVM: Introduce steal time cap
  tools headers kvm: Sync linux/kvm.h with the kernel sources
  KVM: selftests: Use KVM_CAP_STEAL_TIME

 Documentation/virt/kvm/api.rst           | 20 ++++++++++++++++----
 arch/arm64/kvm/arm.c                     |  3 +++
 arch/x86/kvm/x86.c                       |  3 +++
 include/uapi/linux/kvm.h                 |  1 +
 tools/include/uapi/linux/kvm.h           | 15 +++++++++++++++
 tools/testing/selftests/kvm/steal_time.c |  8 ++++++++
 6 files changed, 46 insertions(+), 4 deletions(-)
```
