

#### [PATCH v14 00/10] Enable ptp_kvm for arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Fri Sep  4 09:27:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11756383
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 130DC138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 09:29:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF3612087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 09:29:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729869AbgIDJ27 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 05:28:59 -0400
Received: from foss.arm.com ([217.140.110.172]:46702 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725812AbgIDJ27 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 05:28:59 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 33BEB101E;
        Fri,  4 Sep 2020 02:28:58 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-desktop.shanghai.arm.com
 [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 7E4333F66F;
        Fri,  4 Sep 2020 02:28:52 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v14 00/10] Enable ptp_kvm for arm64
Date: Fri,  4 Sep 2020 17:27:34 +0800
Message-Id: <20200904092744.167655-1-jianyong.wu@arm.com>
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
2. ptp_kvm module in guest recive this request then invoke hypercall to route
into host kernel to request host walltime/counter cycle.
3. ptp_kvm hypercall service in host response to the request and send data back.
4. ptp (not ptp_kvm) in guest copy the data to userspace.

This ptp_kvm implementation focuses itself to step 2 and 3 and step 2 works
in guest comparing step 3 works in host kernel.

change log:
from v13 to v14
        (1) rebase code on 5.9-rc3.
        (2) add a document to introduce implementation of PTP_KVM on
arm64.
        (3) fix comments issue in hypercall.c.
        (4) export arm_smccc_1_1_get_conduit using EXPORT_SYMBOL_GPL.
        (5) fix make issue on x86 reported by kernel test robot.

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
Jianyong Wu (9):
  arm64: Probe for the presence of KVM hypervisor services during boot
  smccc: Export smccc conduit get helper.
  ptp: Reorganize ptp_kvm module to make it arch-independent.
  time: Add mechanism to recognize clocksource in time_get_snapshot
  clocksource: Add clocksource id for arm arch counter
  arm64/kvm: Add hypercall service for kvm ptp.
  ptp: arm64: Enable ptp_kvm for arm64
  doc: add ptp_kvm introduction for arm64 support
  arm64: Add kvm capability check extension for ptp_kvm

Will Deacon (1):
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC

 Documentation/virt/kvm/arm/ptp_kvm.rst      | 72 +++++++++++++++++
 arch/arm64/include/asm/hypervisor.h         | 11 +++
 arch/arm64/kernel/setup.c                   | 36 +++++++++
 arch/arm64/kvm/Kconfig                      |  6 ++
 arch/arm64/kvm/arch_timer.c                 |  2 +-
 arch/arm64/kvm/arm.c                        |  4 +
 arch/arm64/kvm/hypercalls.c                 | 78 +++++++++++++++---
 drivers/clocksource/arm_arch_timer.c        | 26 ++++++
 drivers/firmware/smccc/smccc.c              |  1 +
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  5 ++
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm64.c                 | 53 ++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 80 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 89 +++++++++++++++++++++
 include/kvm/arm_arch_timer.h                |  1 +
 include/linux/arm-smccc.h                   | 42 ++++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  2 +
 kernel/time/timekeeping.c                   |  1 +
 23 files changed, 477 insertions(+), 76 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm64.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (63%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [PATCH v8 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Fri Sep  4 17:37:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Paraschiv, Andra-Irina" <andraprs@amazon.com>
X-Patchwork-Id: 11758301
Return-Path: <SRS0=EfB3=CN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F9C392C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 18:02:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 030D723D3C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  4 Sep 2020 18:02:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="VT152JZL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727978AbgIDRhm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 4 Sep 2020 13:37:42 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:24018 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726317AbgIDRhl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Sep 2020 13:37:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1599241060; x=1630777060;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=1RA0SL5UdFMovFbxFhZYdl8BxQFLNRNAqf6r/ZuDHco=;
  b=VT152JZLCu0pfX/LouMRH5TDy+gvIVl7BdYkTKyWhDPbyDmjgbUwvtjm
   qYOHvC47JyGUX9Wai3IwBi5Yffq8iLVmOEx/5ACSGb6n2AhA3Od7F0H3e
   NQcLmulSIUYxvKUQ1prp7mk0llLN9u+oR1l5C/oFsvH57W8+xKnfrN2sB
   A=;
X-IronPort-AV: E=Sophos;i="5.76,390,1592870400";
   d="scan'208";a="52099665"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 04 Sep 2020 17:37:39 +0000
Received: from EX13D16EUB001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan3.iad.amazon.com [10.40.159.166])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id 7A9E9A2544;
        Fri,  4 Sep 2020 17:37:36 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.85) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 4 Sep 2020 17:37:26 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v8 00/18] Add support for Nitro Enclaves
Date: Fri, 4 Sep 2020 20:37:00 +0300
Message-ID: <20200904173718.64857-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.161.85]
X-ClientProxiedBy: EX13D13UWB001.ant.amazon.com (10.43.161.156) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPUs, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the NE driver.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command. The PCI device commands are then
translated into  actions taken on the hypervisor side; that's the Nitro
hypervisor running on the host where the primary VM is running. The Nitro
hypervisor is based on core KVM technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

The memory regions carved out of the primary VM and given to an enclave need to
be aligned 2 MiB / 1 GiB physically contiguous memory regions (or multiple of
this size e.g. 8 MiB). The memory can be allocated e.g. by using hugetlbfs from
user space [2][3]. The memory size for an enclave needs to be at least 64 MiB.
The enclave memory and CPUs need to be from the same NUMA node.

An enclave runs on dedicated cores. CPU 0 and its CPU siblings need to remain
available for the primary VM. A CPU pool has to be set for NE purposes by an
user with admin capability. See the cpu list section from the kernel
documentation [4] for how a CPU pool format looks.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [5]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol [6].

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted. The CID of the
primary VM is 3.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/html/latest/admin-guide/mm/hugetlbpage.html
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
[6] https://www.kernel.org/doc/html/latest/x86/boot.html
---

Patch Series Changelog

The patch series is built on top of v5.9-rc3.

GitHub repo branch for the latest version of the patch series:

* https://github.com/andraprs/linux/tree/ne-driver-upstream-v8 

v7 -> v8

* Rebase on top of v5.9-rc3.
* Add NE customer error codes for invalid flags and enclave CID provided to the
  ioctl calls, and memory regions not backed by pages multiple of 2 MiB.
* Add NE PCI driver shutdown logic.
* Add check for invalid provided enclave CID to the start enclave ioctl.
* Update documentation to include info about the primary / parent VM CID for its
  vsock device. Update reference link for huge pages and include refs for the
  x86 boot protocol.
* Update sample to track the newly added NE custom error codes and match the
  latest logic for the heartbeat enclave boot check.
* v7: https://lore.kernel.org/lkml/20200817131003.56650-1-andraprs@amazon.com/

v6 -> v7

* Rebase on top of v5.9-rc1.
* Use the NE misc device parent field to get the NE PCI device.
* Update the naming and add more comments to make more clear the logic of
  handling full CPU cores and dedicating them to the enclave.
* Remove, for now, the dependency on ARM64 arch in Kconfig. x86 is currently
  supported, with Arm to come afterwards. The NE kernel driver can be currently
  built for aarch64 arch.
* Clarify in the ioctls documentation that the return value is -1 and errno is
  set on failure.
* Update the error code value for NE_ERR_INVALID_MEM_REGION_SIZE as it gets in
  user space as value 25 (ENOTTY) instead of 515. Update the NE custom error
  codes values range to not be the same as the ones defined in
  include/linux/errno.h, although these are not propagated to user space.
* Update the documentation to include references to the NE PCI device id and
  MMIO bar.
* Update check for duplicate user space memory regions to cover additional
  possible scenarios.
* Calculate the number of threads per core and not use smp_num_siblings that is
  x86 specific.
* v6: https://lore.kernel.org/lkml/20200805091017.86203-1-andraprs@amazon.com/

v5 -> v6

* Rebase on top of v5.8.
* Update documentation to kernel-doc format.
* Update sample to include the enclave image loading logic.
* Remove the ioctl to query API version.
* Check for invalid provided flags field via ioctl calls args.
* Check for duplicate provided user space memory regions.
* Check for aligned memory regions.
* Include, in the sample, usage info for NUMA-aware hugetlb config.
* v5: https://lore.kernel.org/lkml/20200715194540.45532-1-andraprs@amazon.com/

v4 -> v5

* Rebase on top of v5.8-rc5.
* Add more details about the ioctl calls usage e.g. error codes.
* Update the ioctl to set an enclave vCPU to not return a fd.
* Add specific NE error codes.
* Split the NE CPU pool in CPU cores cpumasks.
* Remove log on copy_from_user() / copy_to_user() failure.
* Release the reference to the NE PCI device on failure paths.
* Close enclave fd on copy_to_user() failure.
* Set empty string in case of invalid NE CPU pool sysfs value.
* Early exit on NE CPU pool setup if enclave(s) already running.
* Add more sanity checks for provided vCPUs e.g. maximum possible value.
* Split logic for checking if a vCPU is in pool / getting a vCPU from pool.
* Exit without unpinning the pages on NE PCI dev request failure.
* Add check for the memory region user space address alignment.
* Update the logic to set memory region to not have a hardcoded check for 2 MiB.
* Add arch dependency for Arm / x86.
* v4: https://lore.kernel.org/lkml/20200622200329.52996-1-andraprs@amazon.com/

v3 -> v4

* Rebase on top of v5.8-rc2.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.
* Decouple NE ioctl interface from KVM API.
* Remove the "packed" attribute and include padding in the NE data structures.
* Update documentation based on the changes from v4.
* Update sample to match the updates in v4.
* Remove the NE CPU pool init during NE kernel module loading.
* Setup the NE CPU pool at runtime via a sysfs file for the kernel parameter.
* Check if the enclave memory and CPUs are from the same NUMA node.
* Add minimum enclave memory size definition.
* v3: https://lore.kernel.org/lkml/20200525221334.62966-1-andraprs@amazon.com/ 

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for creating an enclave VM
  nitro_enclaves: Add logic for setting an enclave vCPU
  nitro_enclaves: Add logic for getting the enclave image load info
  nitro_enclaves: Add logic for setting an enclave memory region
  nitro_enclaves: Add logic for starting an enclave
  nitro_enclaves: Add logic for terminating an enclave
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 Documentation/nitro_enclaves/ne_overview.rst  |   95 +
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   20 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1736 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |   99 +
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  624 ++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  327 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  359 ++++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  883 +++++++++
 16 files changed, 4204 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/nitro_enclaves/ne_overview.rst
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
