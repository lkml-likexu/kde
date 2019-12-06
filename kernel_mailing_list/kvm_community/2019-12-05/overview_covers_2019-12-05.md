

#### [RFC PATCH 0/9] Introduce mediate ops in vfio-pci
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Thu Dec  5 03:24:19 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11274097
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B2B06C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:32:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EAC5221835
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:32:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728847AbfLEDcu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 22:32:50 -0500
Received: from mga04.intel.com ([192.55.52.120]:20226 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728098AbfLEDct (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 22:32:49 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Dec 2019 19:32:47 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,279,1571727600";
   d="scan'208";a="205628942"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.9])
  by orsmga008.jf.intel.com with ESMTP; 04 Dec 2019 19:32:45 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        libvir-list@redhat.com, qemu-devel@nongnu.org, cohuck@redhat.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH 0/9] Introduce mediate ops in vfio-pci
Date: Wed,  4 Dec 2019 22:24:19 -0500
Message-Id: <20191205032419.29606-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For SRIOV devices, VFs are passthroughed into guest directly without host
driver mediation. However, when VMs migrating with passthroughed VFs,
dynamic host mediation is required to  (1) get device states, (2) get
dirty pages. Since device states as well as other critical information
required for dirty page tracking for VFs are usually retrieved from PFs,
it is handy to provide an extension in PF driver to centralizingly control
VFs' migration.

Therefore, in order to realize (1) passthrough VFs at normal time, (2)
dynamically trap VFs' bars for dirty page tracking and (3) centralizing
VF critical states retrieving and VF controls into one driver, we propose
to introduce mediate ops on top of current vfio-pci device driver.


                                   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
                                  
 __________   register mediate ops|  ___________     ___________    |
|          |<-----------------------|     VF    |   |           |   
| vfio-pci |                      | |  mediate  |   | PF driver |   |
|__________|----------------------->|   driver  |   |___________|   
     |            open(pdev)      |  -----------          |         |
     |                                                    |         
     |                            |_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _ _|
    \|/                                                  \|/
-----------                                         ------------
|    VF   |                                         |    PF    |
-----------                                         ------------


VF mediate driver could be a standalone driver that does not bind to
any devices (as in demo code in patches 5-6) or it could be a built-in
extension of PF driver (as in patches 7-9) .

Rather than directly bind to VF, VF mediate driver register a mediate
ops into vfio-pci in driver init. vfio-pci maintains a list of such
mediate ops.
(Note that: VF mediate driver can register mediate ops into vfio-pci
before vfio-pci binding to any devices. And VF mediate driver can
support mediating multiple devices.)

When opening a device (e.g. a VF), vfio-pci goes through the mediate ops
list and calls each vfio_pci_mediate_ops->open() with pdev of the opening
device as a parameter.
VF mediate driver should return success or failure depending on it
supports the pdev or not.
E.g. VF mediate driver would compare its supported VF devfn with the
devfn of the passed-in pdev.
Once vfio-pci finds a successful vfio_pci_mediate_ops->open(), it will
stop querying other mediate ops and bind the opening device with this
mediate ops using the returned mediate handle.

Further vfio-pci ops (VFIO_DEVICE_GET_REGION_INFO ioctl, rw, mmap) on the
VF will be intercepted into VF mediate driver as
vfio_pci_mediate_ops->get_region_info(),
vfio_pci_mediate_ops->rw,
vfio_pci_mediate_ops->mmap, and get customized.
For vfio_pci_mediate_ops->rw and vfio_pci_mediate_ops->mmap, they will
further return 'pt' to indicate whether vfio-pci should further
passthrough data to hw.

when vfio-pci closes the VF, it calls its vfio_pci_mediate_ops->release()
with a mediate handle as parameter.

The mediate handle returned from vfio_pci_mediate_ops->open() lets VF
mediate driver be able to differentiate two opening VFs of the same device
id and vendor id.

When VF mediate driver exits, it unregisters its mediate ops from
vfio-pci.


In this patchset, we enable vfio-pci to provide 3 things:
(1) calling mediate ops to allow vendor driver customizing default
region info/rw/mmap of a region.
(2) provide a migration region to support migration
(3) provide a dynamic trap bar info region to allow vendor driver
control trap/untrap of device pci bars

This vfio-pci + mediate ops way differs from mdev way in that
(1) medv way needs to create a 1:1 mdev device on top of one VF, device
specific mdev parent driver is bound to VF directly.
(2) vfio-pci + mediate ops way does not create mdev devices and VF
mediate driver does not bind to VFs. Instead, vfio-pci binds to VFs.

The reason why we don't choose the way of writing mdev parent driver is
that
(1) VFs are almost all the time directly passthroughed. Directly binding
to vfio-pci can make most of the code shared/reused. If we write a
vendor specific mdev parent driver, most of the code (like passthrough
style of rw/mmap) still needs to be copied from vfio-pci driver, which is
actually a duplicated and tedious work.
(2) For features like dynamically trap/untrap pci bars, if they are in
vfio-pci, they can be available to most people without repeated code
copying and re-testing.
(3) with a 1:1 mdev driver which passthrough VFs most of the time, people
have to decide whether to bind VFs to vfio-pci or mdev parent driver before
it runs into a real migration need. However, if vfio-pci is bound
initially, they have no chance to do live migration when there's a need
later. 

In this patchset,
- patches 1-4 enable vfio-pci to call mediate ops registered by vendor
  driver to mediate/customize region info/rw/mmap.

- patches 5-6 provide a standalone sample driver to register a mediate ops
  for Intel Graphics Devices. It does not bind to IGDs directly but decides
  what devices it supports via its pciidlist. It also demonstrates how to
  dynamic trap a device's PCI bars. (by adding more pciids in its
  pciidlist, this sample driver actually is not necessarily limited to
  support IGDs)

- patch 7-9 provide a sample on i40e driver that supports Intel(R)
  Ethernet Controller XL710 Family of devices. It supports VF precopy live
  migration on Intel's 710 SRIOV. (but we commented out the real
  implementation of dirty page tracking and device state retrieving part
  to focus on demonstrating framework part. Will send out them in future
  versions)
 
  patch 7 registers/unregisters VF mediate ops when PF driver
  probes/removes. It specifies its supporting VFs via
  vfio_pci_mediate_ops->open(pdev)

  patch 8 reports device cap of VFIO_PCI_DEVICE_CAP_MIGRATION and
  provides a sample implementation of migration region.
  The QEMU part of vfio migration is based on v8
  https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05542.html.
  We do not based on recent v9 because we think there are still opens in
  dirty page track part in that series.

  patch 9 reports device cap of VFIO_PCI_DEVICE_CAP_DYNAMIC_TRAP_BAR and
  provides an example on how to trap part of bar0 when migration starts
  and passthrough this part of bar0 again when migration fails.

Yan Zhao (9):
  vfio/pci: introduce mediate ops to intercept vfio-pci ops
  vfio/pci: test existence before calling region->ops
  vfio/pci: register a default migration region
  vfio-pci: register default dynamic-trap-bar-info region
  samples/vfio-pci/igd_dt: sample driver to mediate a passthrough IGD
  sample/vfio-pci/igd_dt: dynamically trap/untrap subregion of IGD bar0
  i40e/vf_migration: register mediate_ops to vfio-pci
  i40e/vf_migration: mediate migration region
  i40e/vf_migration: support dynamic trap of bar0

 drivers/net/ethernet/intel/Kconfig            |   2 +-
 drivers/net/ethernet/intel/i40e/Makefile      |   3 +-
 drivers/net/ethernet/intel/i40e/i40e.h        |   2 +
 drivers/net/ethernet/intel/i40e/i40e_main.c   |   3 +
 .../ethernet/intel/i40e/i40e_vf_migration.c   | 626 ++++++++++++++++++
 .../ethernet/intel/i40e/i40e_vf_migration.h   |  78 +++
 drivers/vfio/pci/vfio_pci.c                   | 189 +++++-
 drivers/vfio/pci/vfio_pci_private.h           |   2 +
 include/linux/vfio.h                          |  18 +
 include/uapi/linux/vfio.h                     | 160 +++++
 samples/Kconfig                               |   6 +
 samples/Makefile                              |   1 +
 samples/vfio-pci/Makefile                     |   2 +
 samples/vfio-pci/igd_dt.c                     | 367 ++++++++++
 14 files changed, 1455 insertions(+), 4 deletions(-)
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.c
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.h
 create mode 100644 samples/vfio-pci/Makefile
 create mode 100644 samples/vfio-pci/igd_dt.c
```
#### [PATCH v15 0/7] mm / virtio: Provide support for free page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Thu Dec  5 16:22:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275147
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A36C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:22:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5498D24249
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:22:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ntv2TvpP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729712AbfLEQWJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:22:09 -0500
Received: from mail-qv1-f66.google.com ([209.85.219.66]:36845 "EHLO
        mail-qv1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726589AbfLEQWJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:22:09 -0500
Received: by mail-qv1-f66.google.com with SMTP id b18so1501350qvy.3;
        Thu, 05 Dec 2019 08:22:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=Qpy6K11ax0kK4ciQM3JG1UmIIJR6lqYusM7Lr8kdIP8=;
        b=ntv2TvpPrlFC29Z8dt/yFPk4ZU994TTQ3MZxhlyx8CDhllpFCkt1k0VdcVvV+LkFMp
         uUDkD8rqa0Y4bdl+vaVC/fhOAZnX4K59HT0mkWWTQpL3bdIXlMc61SQvb54rSPyS2cKO
         cPxqyLngQTmFZ8SiaUMtZAz8cXN4ASiptX4Iy4eDhQf1OmA71uIeM9Hx53CJ7NAekVun
         HrldzA1OcjEJM6gE7yPe95LhBut6gzyqVDpOJ2UHhzlCKTejOXmo37zcwwzaA1nT4Lgd
         r5TtlMdPut6l1Dwoa6rgTq6t2IdVs4EKTPu/Ca+KbazPcNt1cvAfyJclBoT1i4m92aVz
         1/OQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=Qpy6K11ax0kK4ciQM3JG1UmIIJR6lqYusM7Lr8kdIP8=;
        b=KcIM2gNc1p77l3nvxJekNIyCKTomQXyc+l8LUN2wJMILwD+TxZpLFH8BXd4562yMGD
         PnBMcw1kEZrgq5xcUyKZD4L/9fp3nwGTvgiOqWDLx+0L5nSHoVpyBZuDkUZBLgD9Yjle
         Yo06+VSLJx3sQdAeL+/Ei6QL9J1Xk39WrwbTbOGOj1rmB2G0LrT/v2Ht9pew2DNo9ioB
         8Bxp+iax+kajf1vhCwjqqJ1wmgg8DYi+k1m4p46glzwU0Dbe1zM1680bmQkDAdwRJyn3
         v/WgFsudBJ7Ah0/Brh+N84w9uTEhDxgUzjmHXiq0e+RtB+V5vVvUgYGZIbttETPoVrJ1
         syWA==
X-Gm-Message-State: APjAAAULIAFBTjOLfqTTdhWxVUpV0GqeFx0OmfhRXF7SAD3lepsjj4Ac
        OP8nYaOaQeGg3e711MDc2+o=
X-Google-Smtp-Source: 
 APXvYqywFjguj3KYPD3Q9UUX11DryNlxCYob26zjWKeo8xEpYWA1gNBELiUDvYTJzAtTA+o2WPVuRg==
X-Received: by 2002:a05:6214:844:: with SMTP id
 dg4mr8101649qvb.94.1575562927636;
        Thu, 05 Dec 2019 08:22:07 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 17sm5511558qtz.85.2019.12.05.08.22.04
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:22:06 -0800 (PST)
Subject: [PATCH v15 0/7] mm / virtio: Provide support for free page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:22:04 -0800
Message-ID: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting free guest pages
to a hypervisor so that the memory associated with those pages can be
dropped and reused by other processes and/or guests on the host. Using
this it is possible to avoid unnecessary I/O to disk and greatly improve
performance in the case of memory overcommit on the host.

When enabled we will be performing a scan of free memory every 2 seconds
while pages of sufficiently high order are being freed. Currently the order
used is pageblock_order so that this feature will not interfere with the
use of Transparent Huge Pages in the case of virtualization.

Currently this is only in use by virtio-balloon however there is the hope
that at some point in the future other hypervisors might be able to make
use of it. In the virtio-balloon/QEMU implementation the hypervisor is
currently using MADV_DONTNEED to indicate to the host kernel that the page
is currently free. It will be zeroed and faulted back into the guest the
next time the page is accessed.

To track if a page is reported or not the Uptodate flag was repurposed and
used as a Reported flag for Buddy pages. We walk though the free list
isolating pages and adding them to the scatterlist until we either
encounter the end of the list, processed as many pages as were listed in
nr_free prior to us starting, or have filled the scatterlist with pages to
be reported. If we fill the scatterlist before we reach the end of the
list we rotate the list so that the first unreported page we encounter is
moved to the head of the list as that is where we will resume after we
have freed the reported pages back into the tail of the list.

Below are the results from various benchmarks. I primarily focused on two
tests. The first is the will-it-scale/page_fault2 test, and the other is
a modified version of will-it-scale/page_fault1 that was enabled to use
THP. I did this as it allows for better visibility into different parts
of the memory subsystem. The guest is running with 32G for RAM on one
node of a E5-2630 v3. The host has had some power saving features disabled
by setting the /dev/cpu_dma_latency value to 10ms.

Test                   page_fault1 (THP)    page_fault2
Name            tasks  Process Iter  STDEV  Process Iter  STDEV
Baseline            1    1208307.25  0.10%     408596.00  0.19%
                   16    8865204.75  0.16%    3344169.00  0.60%

Patches applied     1    1206809.00  0.26%     412558.25  0.32%
                   16    8814350.50  0.78%    3420102.00  1.16%

Patches enabled     1    1201386.25  0.21%     407903.75  0.32%
                   16    8880178.00  0.08%    3396700.50  0.54%

Patches enabled     1    1173529.00  1.04%     409006.50  0.45%
 page shuffle      16    8384540.25  0.74%    3288289.25  0.41%

Patches enabled     1    1193411.00  0.33%     406333.50  0.09%
 shuffle w/ RFC    16    8812639.75  0.73%    3321706.25  0.53%

The results above are for a baseline with a linux-next-20191203 kernel,
that kernel with this patch set applied but page reporting disabled in
virtio-balloon, the patches applied and page reporting fully enabled, the
patches enabled with page shuffling enabled, and the patches applied with
page shuffling enabled and an RFC patch that makes used of MADV_FREE in
QEMU. These results include the deviation seen between the average value
reported here versus the high and/or low value. I observed that during the
test memory usage for the first three tests never dropped whereas with the
patches fully enabled the VM would drop to using only a few GB of the
host's memory when switching from memhog to page fault tests.

Any of the overhead visible with this patch set enabled seems due to page
faults caused by accessing the reported pages and the host zeroing the page
before giving it back to the guest. This overhead is much more visible when
using THP than with standard 4K pages. In addition page shuffling seemed to
increase the amount of faults generated due to an increase in memory churn.
As seen in the data above, using MADV_FREE in QEMU mostly eliminates this
overhead.

The overall guest size is kept fairly small to only a few GB while the test
is running. If the host memory were oversubscribed this patch set should
result in a performance improvement as swapping memory in the host can be
avoided.

A brief history on the background of free page reporting can be found at:
https://lore.kernel.org/lkml/29f43d5796feed0dec8e8bb98b187d9dac03b900.camel@linux.intel.com/

Changes from v13:
https://lore.kernel.org/lkml/20191105215940.15144.65968.stgit@localhost.localdomain/
Rewrote core reporting functionality
  Merged patches 3 & 4
  Dropped boundary list and related code
  Folded get_reported_page into page_reporting_fill
  Folded page_reporting_fill into page_reporting_cycle
Pulled reporting functionality out of free_reported_page
  Renamed it to __free_isolated_page
  Moved page reporting specific bits to page_reporting_drain
Renamed phdev to prdev since we aren't "hinting" we are "reporting"
Added documentation to describe the usage of unused page reporting
Updated cover page and patch descriptions to avoid mention of boundary

Changes from v14:
https://lore.kernel.org/lkml/20191119214454.24996.66289.stgit@localhost.localdomain/
Renamed "unused page reporting" to "free page reporting"
  Updated code, kconfig, and patch descriptions
Split out patch for __free_isolated_page
  Renamed function to __putback_isolated_page
Rewrote core reporting functionality
  Added logic to reschedule worker in 2 seconds instead of run to completion
  Removed reported_pages statistics
  Removed REPORTING_REQUESTED bit used in zone flags
  Replaced page_reporting_dev_info refcount with state variable
  Removed scatterlist from page_reporting_dev_info
  Removed capacity from page reporting device
  Added dynamic scatterlist allocation/free at start/end of reporting process
  Updated __free_one_page so that reported pages are not always added to tail
  Added logic to handle error from report function
Updated virtio-balloon patch that adds support for page reporting
  Updated patch description to try and highlight differences in approaches
  Updated logic to reflect that we cannot limit the scatterlist from device
  Added logic to return error from report function
Moved documentation patch to end of patch set
---

Alexander Duyck (7):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Add function __putback_isolated_page
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing free page reports to host
      mm: Add free page reporting documentation


 Documentation/vm/free_page_reporting.rst |   41 ++++
 drivers/virtio/Kconfig                   |    1 
 drivers/virtio/virtio_balloon.c          |   87 +++++++-
 include/linux/mmzone.h                   |   44 ----
 include/linux/page-flags.h               |   11 +
 include/linux/page_reporting.h           |   25 ++
 include/uapi/linux/virtio_balloon.h      |    1 
 mm/Kconfig                               |   11 +
 mm/Makefile                              |    1 
 mm/internal.h                            |    1 
 mm/page_alloc.c                          |  169 +++++++++++----
 mm/page_isolation.c                      |    6 -
 mm/page_reporting.c                      |  336 ++++++++++++++++++++++++++++++
 mm/page_reporting.h                      |   54 +++++
 mm/shuffle.c                             |   12 +
 mm/shuffle.h                             |    6 +
 16 files changed, 700 insertions(+), 106 deletions(-)
 create mode 100644 Documentation/vm/free_page_reporting.rst
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
