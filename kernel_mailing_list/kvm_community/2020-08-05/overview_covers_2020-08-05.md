

#### [PATCH v6 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Wed Aug  5 09:09:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11701569
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3D4B722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 09:10:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C6F1022CA0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 09:10:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="R6JQa5KG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728129AbgHEJKl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 05:10:41 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:16612 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726175AbgHEJKi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 05:10:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596618637; x=1628154637;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=lBc50Mn2o8g6SNwBri9hCvz9EnTPYK9p0iygtLBKoMM=;
  b=R6JQa5KG1YM/B0brkAe0hxyVb6CUUt237DLQiuzp3yj7mjh8hl9fWg2t
   zsT0XlsY4LHH4GuOflFfU5q8G/OsTWTnVBFwYZD6sRexm/pL5QtE8bQ/W
   OOglM6BBc5B2D8cniIQwChNqDPcgjga0DutkPHxmr542VL9NnBWxlqjVs
   A=;
IronPort-SDR: 
 6DVQ/F6UbiWxvD+eK6DQAxtpMSYD8XkQZH2pPPOoagovwq+2+8Bwp/KJiEcSYb1qJbLDYR6xdg
 nDcSe3IWQ9zA==
X-IronPort-AV: E=Sophos;i="5.75,436,1589241600";
   d="scan'208";a="57530506"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 05 Aug 2020 09:10:35 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com (Postfix) with
 ESMTPS id F21EBA20D6;
        Wed,  5 Aug 2020 09:10:34 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 5 Aug 2020 09:10:34 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.26) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 5 Aug 2020 09:10:24 +0000
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
Subject: [PATCH v6 00/18] Add support for Nitro Enclaves
Date: Wed, 5 Aug 2020 12:09:59 +0300
Message-ID: <20200805091017.86203-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.160.26]
X-ClientProxiedBy: EX13D03UWA003.ant.amazon.com (10.43.160.39) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
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
boot protocol.

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
used to check in the primary VM that the enclave has booted.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/Documentation/vm/hugetlbpage.txt
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
---

Patch Series Changelog

The patch series is built on top of v5.8.

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

 Documentation/nitro_enclaves/ne_overview.rst  |   87 +
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   16 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1517 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |   92 +
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  600 +++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  321 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  327 ++++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  853 +++++++++
 16 files changed, 3874 insertions(+), 1 deletion(-)
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
#### [RFC 0/9] KVM:x86/mmu:Introduce parallel memory virtualization to
##### From: Yulei Zhang <yulei.kernel@gmail.com>
From: Yulei Zhang <yuleixzhang@tencent.com>

```c
From patchwork Wed Aug  5 14:12:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yulei Zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11701947
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9421514E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 16:52:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7CA3122D2B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 16:52:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mGGnDTpN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728225AbgHEQwb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 12:52:31 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46396 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728139AbgHEQtq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 12:49:46 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 76992C0A8938;
        Wed,  5 Aug 2020 07:11:20 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id t6so24510493pgq.1;
        Wed, 05 Aug 2020 07:11:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=gnq2bYcLCYbS7fB6hPJYIGySV/efaN7joodM7bHp3HM=;
        b=mGGnDTpNY8ZF+dLJA+3RJn/hk+73NVX1GPiWuFeKj+prG1T5Q8RHEnAe34YY7ukHRh
         C9nNFsKDK339IwgGBO4ithBKkz6AQSgtkyiJzTUXPPI+SF9/zjSlJ3GmJQbHhepK72cs
         i0nwwk1P6k9gGvDitoQ5lD+4hQDzmYv49X2pGW/d3uNqLhLzH0wO4oPzqwI1Fs1Vpi01
         OWCldIcCxihrBnDzIWcJaNL9kjCR6ErUPUQ6nDigCLnEbr0ObGtSWZ76VyZxhFTo4Obl
         vqQr+3waWg9fZ/qrUl/4lfkLv1DAwOJAZCzyMehir3PlK6cc9umER0w/WUJNmlSUS9qZ
         7CYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=gnq2bYcLCYbS7fB6hPJYIGySV/efaN7joodM7bHp3HM=;
        b=ll40ktqYFkDll/eFP8oNlInzcdHl8eaC5GWXDhOk97yeEinYji2P7l33r3BiDv7kWG
         9lIDsDXcJGPgTpNd+C2rm6cXgQrSSG5mou+c2dR8ckFzS8CvZxgasiapIA8fspNJMo7/
         b/pMHlvLJCND0FHsJvaeb3MIj+pWZphqZWSFTnOhPgjX6FqWXh5oF2odcA+Hgotur6w1
         HbyZMHTTQ92CQwSSApG+yfVMK0ZRYWuscLeqfX7FzpqIwH0Y29Ri7fiRi+7/23F8LvTA
         kHAKg2mzrB3rBNveqNBkt/ItRFHlbYNGzcS88Uf1tjw1yzhaGOcYlQ3gPrWVcXbXLD/6
         2icA==
X-Gm-Message-State: AOAM531cJHyPvxK3dL2+Oidd+9anwJeLPQJTOKwWBE2h0sg/NzQXMKyF
        7eNdYiGwbL5qwQJ1u6OVP0s=
X-Google-Smtp-Source: 
 ABdhPJy77TbI6/Hga9l/DBSuyThrNPQZmn3Gth7qz6s8qSxdXr8BWBae5Rt5ikEaEgOlo8d1yiB2zg==
X-Received: by 2002:a63:4c22:: with SMTP id z34mr3191367pga.370.1596636680035;
        Wed, 05 Aug 2020 07:11:20 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.56])
        by smtp.gmail.com with ESMTPSA id
 z29sm3898453pfj.182.2020.08.05.07.11.17
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 05 Aug 2020 07:11:19 -0700 (PDT)
From: Yulei Zhang <yulei.kernel@gmail.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC 0/9] KVM:x86/mmu:Introduce parallel memory virtualization to
 boost performance
Date: Wed,  5 Aug 2020 22:12:02 +0800
Message-Id: <20200805141202.8641-1-yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

Currently in KVM memory virtulization we relay on mmu_lock to synchronize
the memory mapping update, which make vCPUs work in serialize mode and
slow down the execution, especially after migration to do substantial
memory mapping setup, and performance get worse if increase vCPU numbers
and guest memories.
  
The idea we present in this patch set is to mitigate the issue with
pre-constructed memory mapping table. We will fast pin the guest memory
to build up a global memory mapping table according to the guest memslots
changes and apply it to cr3, so that after guest starts up all the vCPUs
would be able to update the memory concurrently, thus the performance 
improvement is expected.

And after test the initial patch with memory dirty pattern workload, we
have seen positive results even with huge page enabled. For example,
guest with 32 vCPUs and 64G memories, in 2M/1G huge page mode we would get
more than 50% improvement. 


Yulei Zhang (9):
  Introduce new fields in kvm_arch/vcpu_arch struct for direct build EPT
    support
  Introduce page table population function for direct build EPT feature
  Introduce page table remove function for direct build EPT feature
  Add release function for direct build ept when guest VM exit
  Modify the page fault path to meet the direct build EPT requirement
  Apply the direct build EPT according to the memory slots change
  Add migration support when using direct build EPT
  Introduce kvm module parameter global_tdp to turn on the direct build
    EPT mode
  Handle certain mmu exposed functions properly while turn on direct
    build EPT mode

 arch/mips/kvm/mips.c            |  13 +
 arch/powerpc/kvm/powerpc.c      |  13 +
 arch/s390/kvm/kvm-s390.c        |  13 +
 arch/x86/include/asm/kvm_host.h |  13 +-
 arch/x86/kvm/mmu/mmu.c          | 537 ++++++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c          |   2 +-
 arch/x86/kvm/vmx/vmx.c          |  17 +-
 arch/x86/kvm/x86.c              |  55 ++--
 include/linux/kvm_host.h        |   7 +-
 virt/kvm/kvm_main.c             |  43 ++-
 10 files changed, 648 insertions(+), 65 deletions(-)
```
#### [PATCH 0/4] Restrict PV features to only enabled guests
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Wed Aug  5 21:16:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11702543
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 504701575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:16:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3861D2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:16:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Rl6YpFib"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726399AbgHEVQT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 17:16:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60624 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725920AbgHEVQQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 17:16:16 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6687EC061575
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 14:16:16 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id u206so20906080ybb.8
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 14:16:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=6YME6h3frh55VOhFAbXLI9InvDtCOC1i09SrGpWX2Gg=;
        b=Rl6YpFib0Dg8qz/g/d0nLv+Iu6+R6IdjY8jIpYyJEjWQRS79tXRrsqjjr1K7SVNDab
         5INS0mkjWMq9FJ+2rsX+bunqP5fFQhX+8bpgitkmtVuxhzDWy70iOouaW9O84OkjUFv6
         tF8PhFvxvP74FPoXqtMLNpgpQlXipV0m7XumoX9sC68JI4vTaLQY1JnVF2mxsVtoT1Xg
         sQABl8u4cy4r58Y2+hcQxCnQNtrMf0K1dFXET9uVikRp2CMruUZ9MEVP0KvY0979LED5
         GdlYb58GWCxTFVjoI5EAxFXd4K2TS6Bm1gsCFPkDRFVAYyKFuDy5DsBFNPcLt6/I8gWu
         SXsw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=6YME6h3frh55VOhFAbXLI9InvDtCOC1i09SrGpWX2Gg=;
        b=nuNzqcCpLh8QsFKvtLYtlHIZqgyqabQvJAmLjPN99pKWHyfvj0UUkRZk+S6Y3vlQjX
         YFARfXrwdQ6X0iAr1+rj6r7kd0I0nb5ioDl7wCrxKDN5OPjP3Z33FwTadcm5dISZ15mu
         uvZpA+NlaxWkk7YSqE+pHezN7MGl9nVCUtTxjGiK5iDhjaDerPkaQhtqeb/euBh6wk2n
         5+9LWgcBeWYEDt+0PbT1Kv6EUT1gMQc9jt306VcTEKm31UK1Mvc8hhK6ieZpcSQNDrub
         s4K0AL5NzSStuJymCLqgTWWQlkqW4UPeniygsRfYp8d2dDx3y7bECE0d4zZaTZiiojVS
         xeOQ==
X-Gm-Message-State: AOAM5317Y3aABv1sAV13r6lqzi5qwNPJmfJVUg7kxKZwo8EezWn3Gf8O
        Si7Nwzge69xXLLwD51duxWWyGLfCn17n3DAvcLuFrgfnM75i6FH0CTeMYItwAsl9OsGFFuI1h9j
        eWK4iwySax3LSSA8WsJSoxkpO5V/696Qgu9u/AKe3Pyw9C6kwuTn4NCUKww==
X-Google-Smtp-Source: 
 ABdhPJx1uczf46tedRc6MnjromBY3Kc2pRLCXPNzk6KKP/R0AddR72fEYUfkebpsd2HCOcZ22BHUAHDf2R4=
X-Received: by 2002:a25:a0c6:: with SMTP id i6mr7683961ybm.58.1596662174395;
 Wed, 05 Aug 2020 14:16:14 -0700 (PDT)
Date: Wed,  5 Aug 2020 21:16:03 +0000
Message-Id: <20200805211607.2048862-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH 0/4] Restrict PV features to only enabled guests
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, KVM has allowed guests to use paravirtual interfaces regardless
of the configured CPUID. While almost any guest will consult the
KVM_CPUID_FEATURES leaf _before_ using PV features, it is still
undesirable to have such interfaces silently present.

This series aims to address the issue by adding explicit checks against
the guest's CPUID when servicing any paravirtual feature. Since this
effectively changes the guest/hypervisor ABI, a KVM_CAP is warranted to
guard the new behavior.

Patches 1-2 refactor some of the PV code in anticipation of the change.
Patch 3 introduces the checks + KVM_CAP. Finally, patch 4 fixes some doc
typos that were noticed when working on this series.

Parent commit: f3633c268354 ("Merge tag 'kvm-s390-next-5.9-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-next-5.6")

Oliver Upton (4):
  kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper
    fn
  kvm: x86: set wall_clock in kvm_write_wall_clock()
  kvm: x86: only provide PV features if enabled in guest's CPUID
  Documentation: kvm: fix some typos in cpuid.rst

 Documentation/virt/kvm/api.rst   |  11 +++
 Documentation/virt/kvm/cpuid.rst |  88 +++++++++++-----------
 arch/x86/include/asm/kvm_host.h  |   6 ++
 arch/x86/kvm/cpuid.h             |  16 ++++
 arch/x86/kvm/x86.c               | 122 +++++++++++++++++++++++--------
 include/uapi/linux/kvm.h         |   1 +
 6 files changed, 171 insertions(+), 73 deletions(-)
```
#### [PATCH v2 0/4] Restrict PV features to only enabled guests
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Wed Aug  5 21:21:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11702551
Return-Path: <SRS0=UpKl=BP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C0F31392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:21:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 132FC22CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  5 Aug 2020 21:21:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="hrlTCk0J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726155AbgHEVVg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 17:21:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33234 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725730AbgHEVVf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 17:21:35 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 779BAC061575
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 14:21:35 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id d1so11596005pgn.11
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 14:21:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=A2zBYE4JiXe7P1RdEtYrh0UlIzax492Zsz/u2fr1/JI=;
        b=hrlTCk0JLM37eqUbn0GuG+7BNaEmJ45LEewsJ+6ngaPgcRmz7yxuhpqe5cN0X6NwCO
         vf+4J9HNw4c1m+NngZc4U6DESy7MEL26WmMwM/zaeK2TibV9Y7n67kPcTsKPZF6SwHfh
         Ntz1AYkxDWrdQNSkrm5a3GkVGwNEoqrMFpPvHbNyinKxcs+GVjFIODQbwtNjbKsVuwYX
         hzUzx5iY9V1ScOrBkhYvQMw+34Kplf3y68OSvocchxobBGNaZYIY9z1H28/nCjauHDbT
         R/jC1za9d+rMwAtQYDxHm1UP3L/8KexM2nFt227nkFmjkajhbrxF6VWUn5ZFaJVGELHz
         kbzA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=A2zBYE4JiXe7P1RdEtYrh0UlIzax492Zsz/u2fr1/JI=;
        b=JzJysX9/5sl9ghdbxqb3RYixBjnSnzRb5nFVJN11ebBF33TS4ZofRVAF0emJYYKrJs
         4F782/egjlRmmG10OQi+Si9nxhWEYHqLC5cozu70/upQUnyOgANduA6nIxr0ddcyX1m8
         SmOPCQfnN09DjWZ3haUqsJfsUeYsKkftJT4bV2mbiUvTwpxiegjiJSwKPROU0amtvFQa
         7hWDIB93bnBzV5bzwaxAcLt3oJu7qn/o4GI6ANuZZqPKIjOtEjepC4kBhkbxlQshbDLl
         XE7N46lw7Q3xnKblyUnKq+kcyZK3YOv8VREFNKhPvW+Uj0HXFy6PXevK4RRq2WCkkzZq
         argw==
X-Gm-Message-State: AOAM530poj/YfQYSZ8lFcwlT8SzkSf+E8cytJ4N8tqdYwRtKJb/XNUXj
        kjyASbRGdFi4PkbiSy4ysnqS8pus+hyKceueFK2ApJoidYVtVZXxAhEiVGQLaFdCuXaaeRXqAa5
        P4O7Px4AdJWkee5sowZBlPAnQWciODs1mMHoJC63WqnOlbIVkx868eMt4jQ==
X-Google-Smtp-Source: 
 ABdhPJz1YPcyRQUytsMWE18wuedIDmO9gzPSlezLeApOG/5uD6NLkw/fWQdNaUSbcQtOJJlc0mpRobFkfcs=
X-Received: by 2002:a62:7c4f:: with SMTP id x76mr5471614pfc.124.1596662493665;
 Wed, 05 Aug 2020 14:21:33 -0700 (PDT)
Date: Wed,  5 Aug 2020 21:21:27 +0000
Message-Id: <20200805212131.2059634-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v2 0/4] Restrict PV features to only enabled guests
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, KVM has allowed guests to use paravirtual interfaces regardless
of the configured CPUID. While almost any guest will consult the
KVM_CPUID_FEATURES leaf _before_ using PV features, it is still
undesirable to have such interfaces silently present.

This series aims to address the issue by adding explicit checks against
the guest's CPUID when servicing any paravirtual feature. Since this
effectively changes the guest/hypervisor ABI, a KVM_CAP is warranted to
guard the new behavior.

Patches 1-2 refactor some of the PV code in anticipation of the change.
Patch 3 introduces the checks + KVM_CAP. Finally, patch 4 fixes some doc
typos that were noticed when working on this series.

v1 => v2:
 - Strip Change-Id footers (checkpatch is your friend!)

Parent commit: f3633c268354 ("Merge tag 'kvm-s390-next-5.9-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-next-5.6")

Oliver Upton (4):
  kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper
    fn
  kvm: x86: set wall_clock in kvm_write_wall_clock()
  kvm: x86: only provide PV features if enabled in guest's CPUID
  Documentation: kvm: fix some typos in cpuid.rst

 Documentation/virt/kvm/api.rst   |  11 +++
 Documentation/virt/kvm/cpuid.rst |  88 +++++++++++-----------
 arch/x86/include/asm/kvm_host.h  |   6 ++
 arch/x86/kvm/cpuid.h             |  16 ++++
 arch/x86/kvm/x86.c               | 122 +++++++++++++++++++++++--------
 include/uapi/linux/kvm.h         |   1 +
 6 files changed, 171 insertions(+), 73 deletions(-)
```
