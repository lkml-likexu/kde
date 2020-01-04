

#### [PATCH 0/2] use vfio_iova_rw() to read/write IOVAs from CPU side
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Fri Jan  3 01:00:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11316219
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B9441395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 01:09:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 839272085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 01:09:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726148AbgACBJa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jan 2020 20:09:30 -0500
Received: from mga03.intel.com ([134.134.136.65]:29111 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725872AbgACBJa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jan 2020 20:09:30 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Jan 2020 17:09:29 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,388,1571727600";
   d="scan'208";a="252429485"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.9])
  by fmsmga002.fm.intel.com with ESMTP; 02 Jan 2020 17:09:28 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, zhenyuw@linux.intel.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        intel-gvt@eclists.intel.com, pbonzini@redhat.com,
        kevin.tian@intel.com, Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH 0/2] use vfio_iova_rw() to read/write IOVAs from CPU side
Date: Thu,  2 Jan 2020 20:00:55 -0500
Message-Id: <20200103010055.4140-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When device models read/write memory pointed by a range of IOVAs, it is
better to use vfio interfaces. And because this read/write is from CPUs,
there's no need to call vfio_pin_pages() to pin those memory.

patch 1 introduces interface vfio_iova_rw() in vfio to read/write
userspace IOVAs without pinning userspace pages.

patch 2 let gvt switch from kvm side rw interface to vfio_iova_rw().


Yan Zhao (2):
  vfio: introduce vfio_iova_rw to read/write a range of IOVAs
  drm/i915/gvt: subsitute kvm_read/write_guest with vfio_iova_rw

 drivers/gpu/drm/i915/gvt/kvmgt.c | 26 +++-------
 drivers/vfio/vfio.c              | 45 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c  | 81 ++++++++++++++++++++++++++++++++
 include/linux/vfio.h             |  5 ++
 4 files changed, 138 insertions(+), 19 deletions(-)
```
#### [PATCH v16 0/9] mm / virtio: Provide support for free page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Fri Jan  3 21:16:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11317403
Return-Path: <SRS0=EQ1L=2Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D45F1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:16:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CCC2822314
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jan 2020 21:16:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="qAynO6RR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728574AbgACVQQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jan 2020 16:16:16 -0500
Received: from mail-pj1-f66.google.com ([209.85.216.66]:37963 "EHLO
        mail-pj1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728462AbgACVQQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jan 2020 16:16:16 -0500
Received: by mail-pj1-f66.google.com with SMTP id l35so5170488pje.3;
        Fri, 03 Jan 2020 13:16:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=vcaGvboVizxYuIExjSTuyqUpOj8K40jvPE3aaD65vAI=;
        b=qAynO6RRAK9uXppPlGUBZmyii9CWItToi8vMzhAbX/jvYIh3fwJ/Q9F8fxHBeZ3DlP
         +lEyQ3AjXHrfiDC471GHrS6/mas1xrQaGOVbG2bMOb5PFror/mvU3b0fJxwnWOP0pZnz
         ujHdQQuFAZ7LrOClka9JSeZPGWr2pxQzOsUqMYsbWGacjunkQ/Uc+EqVRnkA/V0ab2Mx
         ND/A9cUQL50r1XiN9FyARDSw8A1iEG/iTeN1MkXQP6Jrrb20G0yykhFTikR+mdKJgoWH
         nOnN8vGqqyDRKOjD2h4wfi4Q/nNns2PCKn0u3tmXyI2q2A0PqCGZA8LjsokoOLgzQIm5
         tMKg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=vcaGvboVizxYuIExjSTuyqUpOj8K40jvPE3aaD65vAI=;
        b=DkBAKvFH/6KCahx/Qg+hDvnhFX38PeRXKzXDpjGNSP+XfnNGEj5lvT0A3a+dcrlFOP
         tGvnnPG7Vwu4CsjKgTlx/IDqh20TPBMHwXWZflPkc1RgVcUb8CLAI1VTEeO5H0InwHL7
         J65JgU+YX0nTtD23HS5qSw3hEs6+YjCiPbIQAaTt0I1RnJwPStDQTouB6CynWRswoNwc
         kpWTBIG0/7LZJXOTTHUGxUDOWbYFD2j4rI3Fm+xUEd29IN3PnO5FXBSIhLnE6m/B0U9w
         bc2middbEhpMIcrn9wMecdMUiAtoXjsZpSnfJLM7R9JEICVadQbkKtgi9o+1leAsZvOq
         IQrQ==
X-Gm-Message-State: APjAAAXtBJLd4MDM9ykFDIeAbccoKC8FMx/R5XhteyB3Jn9w+wSQIdZY
        U5imel7kOLnhOxBx/vYuc8U=
X-Google-Smtp-Source: 
 APXvYqwg7IKFnVFK9R0BDEoHaZLlPE6cbznsAksfzM8NG/9KTd09ZvEOIK0ZOwZ9SEaFbhbRAPDi2Q==
X-Received: by 2002:a17:902:fe05:: with SMTP id
 g5mr94736350plj.3.1578086175416;
        Fri, 03 Jan 2020 13:16:15 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 u10sm64158707pgg.41.2020.01.03.13.16.14
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 03 Jan 2020 13:16:14 -0800 (PST)
Subject: [PATCH v16 0/9] mm / virtio: Provide support for free page reporting
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
Date: Fri, 03 Jan 2020 13:16:13 -0800
Message-ID: <20200103210509.29237.18426.stgit@localhost.localdomain>
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
while pages of sufficiently high order are being freed. In each pass at
least one sixteenth of each free list will be reported. By doing this we
avoid racing against other threads that may be causing a high amount of
memory churn.

The lowest page order currently scanned when reporting pages is
pageblock_order so that this feature will not interfere with the use of
Transparent Huge Pages in the case of virtualization.

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
node of a E5-2630 v3. The host has had some features such as CPU turbo
disabled in the BIOS.

Test                   page_fault1 (THP)    page_fault2
Name            tasks  Process Iter  STDEV  Process Iter  STDEV
Baseline            1    1012402.50  0.14%     361855.25  0.81%
                   16    8827457.25  0.09%    3282347.00  0.34%

Patches Applied     1    1007897.00  0.23%     361887.00  0.26%
                   16    8784741.75  0.39%    3240669.25  0.48%

Patches Enabled     1    1010227.50  0.39%     359749.25  0.56%
                   16    8756219.00  0.24%    3226608.75  0.97%

Patches Enabled     1    1050982.00  4.26%     357966.25  0.14%
 page shuffle      16    8672601.25  0.49%    3223177.75  0.40%

Patches Enabled     1    1003238.00  0.22%     360211.00  0.22%
 shuffle w/ RFC    16    8767010.50  0.32%    3199874.00  0.71%

The results above are for a baseline with a linux-next-20191219 kernel,
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
The overhead is reduced when using MADV_FREE as we can avoid the extra
zeroing of the pages when they are reintroduced to the host, as can be seen
when the RFC is applied with shuffling enabled.

The overall guest size is kept fairly small to only a few GB while the test
is running. If the host memory were oversubscribed this patch set should
result in a performance improvement as swapping memory in the host can be
avoided.

A brief history on the background of free page reporting can be found at:
https://lore.kernel.org/lkml/29f43d5796feed0dec8e8bb98b187d9dac03b900.camel@linux.intel.com/

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

Changes from v15:
https://lore.kernel.org/lkml/20191205161928.19548.41654.stgit@localhost.localdomain/
Rebased on linux-next-20191219
Split out patches for budget and moving head to last page processed
  Updated budget code to reduce how much memory is reported per pass
  Added logic to also rotate the list if we exit due a page isolation failure
Added migratetype as argument in __putback_isolated_page
---

Alexander Duyck (9):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Add function __putback_isolated_page
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing free page reports to host
      mm: Rotate free list so reported pages are moved to the tail of the list
      mm: Add budget limit to how many pages can be reported per list per pass
      mm: Add free page reporting documentation


 Documentation/vm/free_page_reporting.rst |   41 +++
 drivers/virtio/Kconfig                   |    1 
 drivers/virtio/virtio_balloon.c          |   87 +++++++
 include/linux/mmzone.h                   |   44 ----
 include/linux/page-flags.h               |   11 +
 include/linux/page_reporting.h           |   26 ++
 include/uapi/linux/virtio_balloon.h      |    1 
 mm/Kconfig                               |   11 +
 mm/Makefile                              |    1 
 mm/internal.h                            |    2 
 mm/page_alloc.c                          |  164 ++++++++++----
 mm/page_isolation.c                      |    6 
 mm/page_reporting.c                      |  364 ++++++++++++++++++++++++++++++
 mm/page_reporting.h                      |   54 ++++
 mm/shuffle.c                             |   12 -
 mm/shuffle.h                             |    6 
 16 files changed, 725 insertions(+), 106 deletions(-)
 create mode 100644 Documentation/vm/free_page_reporting.rst
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
