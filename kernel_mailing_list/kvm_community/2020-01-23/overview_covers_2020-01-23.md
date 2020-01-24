

#### [PATCH v2 kvmtool 00/30] Add reassignable BARs and PCIE 1.1 support
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Jan 23 13:47:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11347907
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 128D792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 13:48:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E55462468D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 13:48:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728609AbgAWNsW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 08:48:22 -0500
Received: from foss.arm.com ([217.140.110.172]:39636 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726780AbgAWNsV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 08:48:21 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5BD26FEC;
        Thu, 23 Jan 2020 05:48:19 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 56FE33F68E;
        Thu, 23 Jan 2020 05:48:18 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com, maz@kernel.org
Subject: [PATCH v2 kvmtool 00/30] Add reassignable BARs and PCIE 1.1 support
Date: Thu, 23 Jan 2020 13:47:35 +0000
Message-Id: <20200123134805.1993-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvmtool uses the Linux-only dt property 'linux,pci-probe-only' to prevent
it from trying to reassign the BARs. Let's make the BARs reassignable so
we can get rid of this band-aid.

Let's also extend the legacy PCI emulation, which came out in 1992, so we
can properly emulate the PCI Express version 1.1 protocol, which is
relatively new, being published in 2005.

For this iteration, I have completely reworked the way BARs are
reassigned. As I was adding support for reassignable BARs to more devices,
it became clear to me that I was duplicating the same code over and over
again.  Furthermore, during device configuration, Linux can assign a region
resource to a BAR that temporarily overlaps with another device. With my
original approach, that meant that every device must be aware of the BAR
values for all the other devices.

With this new approach, the algorithm for activating/deactivating emulation
as BAR addresses change lives completely inside the PCI code. Each device
registers two callback functions which are called when device emulation is
activated (for example, to activate emulation for a newly assigned BAR
address), respectively, when device emulation is deactivated (a previous
BAR address is changed, and emulation for that region must be deactivated).

I also tried to do better at testing the patches. I have tested VFIO with
virtio-pci on an arm64 and a x86 machine:

1. AMD Seattle: Intel 82574L Gigabit Ethernet card, Samsung 970 Pro NVME
(controller registers are in the same BAR region as the MSIX table and PBA,
I wrote a nasty hack to make it work, will try to upstream something after
this series), Realtek 8168 Gigabit Ethernet card, NVIDIA Quadro P400 (only
device detection), AMD Firepro W2100 (amdgpu driver fails probing
because of missing expansion ROM emulation in kvmtool, I will send patches
for this too), Myricom 10 Gigabit Ethernet card, Seagate Barracuda 1000GB
drive.

2. Ryzen 3900x + Gigabyte x570 Aorus Master (bios F10): Realtek 8168
Gigabit Ethernet card, AMD Firepro W2100 (same issue as on Seattle).

Using the CFI flash emulation for kvmtool [1] and a hacked version of EDK2
as the firmware for the virtual machine, I was able download an official
debian arm64 installation iso, install debian and then run it. EDK2 patches
for kvmtool will be posted soon.

You will notice from the changelog that there are a lot of new patches
(17!), but most of them are fixes for stuff that I found while testing.

Patches 1-18 are fixes and cleanups, and can be merged independently. They
are pretty straightforward, so if the size of the series looks off-putting,
please review these first. I am aware that the series has grown quite a
lot, I am willing to split the fixes from the rest of the patches, or
whatever else can make reviewing easier.

Changes in v2:
* Patches 2, 11-18, 20, 22-27, 29 are new.
* Patches 11, 13, and 14 have been dropped.
* Reworked the way BAR reassignment is implemented.
* The patch "Add PCI Express 1.1 support" has been reworked to apply only
  to arm64. For x86 we would need ACPI support in order to advertise the
  location of the ECAM space.
* Gathered Reviewed-by tags.
* Implemented review comments.

[1] https://www.spinics.net/lists/arm-kernel/msg778623.html

Alexandru Elisei (24):
  Makefile: Use correct objcopy binary when cross-compiling for x86_64
  hw/i8042: Compile only for x86
  Remove pci-shmem device
  Check that a PCI device's memory size is power of two
  arm/pci: Advertise only PCI bus 0 in the DT
  vfio/pci: Allocate correct size for MSIX table and PBA BARs
  vfio/pci: Don't assume that only even numbered BARs are 64bit
  vfio/pci: Ignore expansion ROM BAR writes
  vfio/pci: Don't access potentially unallocated regions
  virtio: Don't ignore initialization failures
  Don't ignore errors registering a device, ioport or mmio emulation
  hw/vesa: Don't ignore fatal errors
  hw/vesa: Set the size for BAR 0
  Use independent read/write locks for ioport and mmio
  pci: Add helpers for BAR values and memory/IO space access
  virtio/pci: Get emulated region address from BARs
  vfio: Destroy memslot when unmapping the associated VAs
  vfio: Reserve ioports when configuring the BAR
  vfio/pci: Don't write configuration value twice
  pci: Implement callbacks for toggling BAR emulation
  pci: Toggle BAR I/O and memory space emulation
  pci: Implement reassignable BARs
  vfio: Trap MMIO access to BAR addresses which aren't page aligned
  arm/arm64: Add PCI Express 1.1 support

Julien Thierry (5):
  ioport: pci: Move port allocations to PCI devices
  pci: Fix ioport allocation size
  arm/pci: Fix PCI IO region
  virtio/pci: Make memory and IO BARs independent
  arm/fdt: Remove 'linux,pci-probe-only' property

Sami Mujawar (1):
  pci: Fix BAR resource sizing arbitration

 Makefile                          |   6 +-
 arm/fdt.c                         |   1 -
 arm/include/arm-common/kvm-arch.h |   4 +-
 arm/include/arm-common/pci.h      |   1 +
 arm/ioport.c                      |   3 +-
 arm/kvm.c                         |   3 +
 arm/pci.c                         |  25 +-
 builtin-run.c                     |   6 +-
 hw/i8042.c                        |  14 +-
 hw/pci-shmem.c                    | 400 ------------------------------
 hw/vesa.c                         | 132 +++++++---
 include/kvm/devices.h             |   3 +-
 include/kvm/ioport.h              |  10 +-
 include/kvm/kvm-config.h          |   2 +-
 include/kvm/kvm.h                 |   9 +-
 include/kvm/pci-shmem.h           |  32 ---
 include/kvm/pci.h                 | 168 ++++++++++++-
 include/kvm/util.h                |   2 +
 include/kvm/vesa.h                |   6 +-
 include/kvm/virtio-pci.h          |   3 -
 include/kvm/virtio.h              |   7 +-
 include/linux/compiler.h          |   2 +-
 ioport.c                          |  57 ++---
 kvm.c                             |  65 ++++-
 mips/kvm.c                        |   3 +-
 mmio.c                            |  26 +-
 pci.c                             | 320 ++++++++++++++++++++++--
 powerpc/include/kvm/kvm-arch.h    |   2 +-
 powerpc/ioport.c                  |   3 +-
 powerpc/spapr_pci.c               |   2 +-
 vfio/core.c                       |  22 +-
 vfio/pci.c                        | 231 +++++++++++++----
 virtio/9p.c                       |   9 +-
 virtio/balloon.c                  |  10 +-
 virtio/blk.c                      |  14 +-
 virtio/console.c                  |  11 +-
 virtio/core.c                     |   9 +-
 virtio/mmio.c                     |  13 +-
 virtio/net.c                      |  32 +--
 virtio/pci.c                      | 220 +++++++++++-----
 virtio/scsi.c                     |  14 +-
 x86/include/kvm/kvm-arch.h        |   2 +-
 x86/ioport.c                      |  66 +++--
 43 files changed, 1217 insertions(+), 753 deletions(-)
 delete mode 100644 hw/pci-shmem.c
 delete mode 100644 include/kvm/pci-shmem.h
```
#### [PATCH v4 00/10] Create a userfaultfd demand paging test
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Thu Jan 23 18:04:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11348881
Return-Path: <SRS0=w9Mo=3M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FA3E1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 18:04:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A56622464
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jan 2020 18:04:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="gayc+oHA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729031AbgAWSEm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jan 2020 13:04:42 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:55609 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728767AbgAWSEl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jan 2020 13:04:41 -0500
Received: by mail-pg1-f201.google.com with SMTP id v30so2196213pga.22
        for <kvm@vger.kernel.org>; Thu, 23 Jan 2020 10:04:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=kn8HZu/EyvR9ymq67hLBoXpwH5gJWxf8SifOgi6S8zE=;
        b=gayc+oHAI9zN5b0/03xCzShBxN/WC8D2wZUQzrvrA4a8Ok5/cCHnf7ocuW/udyqRq4
         qNvLtjz/r0qjh1yMl+DIt1S4o06FzUbNUdkF38Z+c8RTEvh1cChTO05OT/w5Lz9tGbrO
         wclRK3FhRL9yqoFyuLusmCJ5xdoWnB5shFaIEtDQ4LRKbKzCZndBeju/xwFnze+oxnI5
         RZC4MZ6u+xrlAxJXHTDlPLLAyt12nO7334cKIbKC5AihX2UgL+VvIipsoK88othnIzKa
         ZYl515ugP/UefCp2y1q2ADAgQ7RVyxOJETooXL13wpPg57v1hwY/SXmLoKN4fSflTDVI
         Wjag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=kn8HZu/EyvR9ymq67hLBoXpwH5gJWxf8SifOgi6S8zE=;
        b=tVe3TZ9+XkfDQ/pALY0QVSYcN/XuYbEDvOHrm52yF325ZeeM8RV/8uMgY8JSe5Mi/+
         p8IyYeJPdNQMtDjtmWG/FbrSBF8VlDVAI8meesHGh5i0qouxosSP2EJ5+Ma+oKz9nGMr
         S+HqztsOHtSCWJGTV+IHZZY/r/wgYYvvgIcetNW1b6qtkOGL4ILwy/ELXf3YAMgAL7JW
         MjDsUCY2bmVyjp2h8e/nXRkdhG+7IUdthHLRS7DWaBuXHR/7MOFYiqGFTQSBmSd4MLZo
         sGnbPn3iwZ98+xLHUotYK5qLkwoEpWi3vzsLJmQ83Q4+z9+O0qvkQSwNK6fGQpfPqM2R
         ebsQ==
X-Gm-Message-State: APjAAAWqo69JebGbykSHPHjAif2FoKq/mlJHJDzzr2AvbstI9NX9qrIx
        T0zqFYMmM4I32r1OlecR+THE+YLxjuxk
X-Google-Smtp-Source: 
 APXvYqxqrRXE16kM6yIDMn+KPoeZ2CKFEsGQZqIPRn2ZutzCuwTTppZzgh96c6OwNyyUAmd6AOoMidiREkQL
X-Received: by 2002:a63:3cb:: with SMTP id 194mr5353607pgd.123.1579802681044;
 Thu, 23 Jan 2020 10:04:41 -0800 (PST)
Date: Thu, 23 Jan 2020 10:04:26 -0800
Message-Id: <20200123180436.99487-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.341.g760bfbb309-goog
Subject: [PATCH v4 00/10] Create a userfaultfd demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When handling page faults for many vCPUs during demand paging, KVM's MMU
lock becomes highly contended. This series creates a test with a naive
userfaultfd based demand paging implementation to demonstrate that
contention. This test serves both as a functional test of userfaultfd
and a microbenchmark of demand paging performance with a variable number
of vCPUs and memory per vCPU.

The test creates N userfaultfd threads, N vCPUs, and a region of memory
with M pages per vCPU. The N userfaultfd polling threads are each set up
to serve faults on a region of memory corresponding to one of the vCPUs.
Each of the vCPUs is then started, and touches each page of its disjoint
memory region, sequentially. In response to faults, the userfaultfd
threads copy a static buffer into the guest's memory. This creates a
worst case for MMU lock contention as we have removed most of the
contention between the userfaultfd threads and there is no time required
to fetch the contents of guest memory.

This test was run successfully on Intel Haswell, Broadwell, and
Cascadelake hosts with a variety of vCPU counts and memory sizes.

This test was adapted from the dirty_log_test.

The series can also be viewed in Gerrit here:
https://linux-review.googlesource.com/c/virt/kvm/kvm/+/1464
(Thanks to Dmitry Vyukov <dvyukov@google.com> for setting up the Gerrit
instance)

v4 (Responding to feedback from Andrew Jones, Peter Xu, and Peter Shier):
- Tested this revision by running
  demand_paging_test
  at each commit in the series on an Intel Haswell machine. Ran
  demand_paging_test -u -v 8 -b 8M -d 10
  on the same machine at the last commit in the series.
- Readded partial aarch64 support, though aarch64 and s390 remain
  untested
- Implemented pipefd polling to reduce UFFD thread exit latency
- Added variable unit input for memory size so users can pass command
  line arguments of the form -b 24M instead of the raw number or bytes
- Moved a missing break from a patch later in the series to an earlier
  one
- Moved to syncing per-vCPU global variables to guest and looking up
  per-vcpu arguments based on a single CPU ID passed to each guest
  vCPU. This allows for future patches to pass more than the supported
  number of arguments for each arch to the vCPUs.
- Implemented vcpu_args_set for s390 and aarch64 [UNTESTED]
- Changed vm_create to always allocate memslot 0 at 4G instead of only
  when the number of pages required is large.
- Changed vcpu_wss to vcpu_memory_size for clarity.

Ben Gardon (10):
  KVM: selftests: Create a demand paging test
  KVM: selftests: Add demand paging content to the demand paging test
  KVM: selftests: Add configurable demand paging delay
  KVM: selftests: Add memory size parameter to the demand paging test
  KVM: selftests: Pass args to vCPU in global vCPU args struct
  KVM: selftests: Add support for vcpu_args_set to aarch64 and s390x
  KVM: selftests: Support multiple vCPUs in demand paging test
  KVM: selftests: Time guest demand paging
  KVM: selftests: Stop memslot creation in KVM internal memslot region
  KVM: selftests: Move memslot 0 above KVM internal memslots

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   5 +-
 .../selftests/kvm/demand_paging_test.c        | 680 ++++++++++++++++++
 .../testing/selftests/kvm/include/test_util.h |   2 +
 .../selftests/kvm/lib/aarch64/processor.c     |  33 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  27 +-
 .../selftests/kvm/lib/s390x/processor.c       |  35 +
 tools/testing/selftests/kvm/lib/test_util.c   |  61 ++
 8 files changed, 839 insertions(+), 5 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c
 create mode 100644 tools/testing/selftests/kvm/lib/test_util.c
```
