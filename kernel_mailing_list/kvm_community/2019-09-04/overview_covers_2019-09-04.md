

#### [PATCH v2 0/2] KVM: s390: Check for invalid bits in kvm_valid_regs
##### From: Thomas Huth <thuth@redhat.com>

```c
From patchwork Wed Sep  4 08:51:58 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11129683
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3833C1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 08:52:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2329B22CF7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 08:52:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728448AbfIDIwJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 04:52:09 -0400
Received: from mx1.redhat.com ([209.132.183.28]:46010 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725938AbfIDIwI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 04:52:08 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id C67233082E20;
        Wed,  4 Sep 2019 08:52:08 +0000 (UTC)
Received: from thuth.com (ovpn-116-69.ams2.redhat.com [10.36.116.69])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A421600CD;
        Wed,  4 Sep 2019 08:52:04 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/2] KVM: s390: Check for invalid bits in kvm_valid_regs
 and kvm_dirty_regs
Date: Wed,  4 Sep 2019 10:51:58 +0200
Message-Id: <20190904085200.29021-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.46]);
 Wed, 04 Sep 2019 08:52:08 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Avoid invalid bits in kvm_valid_regs and kvm_dirty_regs on s390x.

v2:
 - Split the single patch from v1 into two separate patches
   (I've kept the Reviewed-bys from v1, but if you don't agree with the
    patch description of the 2nd patch, please complain)

Thomas Huth (2):
  KVM: s390: Disallow invalid bits in kvm_valid_regs and kvm_dirty_regs
  KVM: selftests: Test invalid bits in kvm_valid_regs and kvm_dirty_regs
    on s390x

 arch/s390/include/uapi/asm/kvm.h              |  6 ++++
 arch/s390/kvm/kvm-s390.c                      |  4 +++
 .../selftests/kvm/s390x/sync_regs_test.c      | 30 +++++++++++++++++++
 3 files changed, 40 insertions(+)
```
#### [PATCH v2 0/2] KVM: Only use posted interrupts for Fixed/LowPrio MSIs
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Wed Sep  4 13:35:09 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11130313
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D084D1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 13:35:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AFE822339D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 13:35:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="XLoNF5Qq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729910AbfIDNfa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 09:35:30 -0400
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:59068 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726943AbfIDNf3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 09:35:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1567604129; x=1599140129;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=2h7LEOemSqSqyfSBSe/LZjqqJl3VgwAeehys9LlM7oE=;
  b=XLoNF5QqxEgRypynV+ebSm212vVvmCQtgtNi1sf1nTDVO8CtalqbUS/5
   FkESBMNfWIwdHikqviRhLifswCSySA/BoxBWneE0IqAHdxlg4y7LAEbqG
   OzRhgj7TJHWbhtGZjnBWouogL/DYRbLdGAqv43pjsOMnZ8WudRLYA21eF
   s=;
X-IronPort-AV: E=Sophos;i="5.64,467,1559520000";
   d="scan'208";a="748980393"
Received: from iad6-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-715bee71.us-east-1.amazon.com) ([10.124.125.2])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 04 Sep 2019 13:35:27 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-715bee71.us-east-1.amazon.com (Postfix) with
 ESMTPS id A6DB3A2BBA;
        Wed,  4 Sep 2019 13:35:22 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Wed, 4 Sep 2019 13:35:22 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.160.160) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Wed, 4 Sep 2019 13:35:18 +0000
From: Alexander Graf <graf@amazon.com>
To: <kvm@vger.kernel.org>
CC: <linux-kernel@vger.kernel.org>, <x86@kernel.org>,
 "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
 Ingo Molnar <mingo@redhat.com>, Thomas Gleixner <tglx@linutronix.de>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Wanpeng Li <wanpengli@tencent.com>, Vitaly Kuznetsov <vkuznets@redhat.com>,
 "Sean Christopherson" <sean.j.christopherson@intel.com>, =?utf-8?b?UmFkaW0g?=
	=?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v2 0/2] KVM: Only use posted interrupts for Fixed/LowPrio MSIs
Date: Wed, 4 Sep 2019 15:35:09 +0200
Message-ID: <20190904133511.17540-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.43.160.160]
X-ClientProxiedBy: EX13D31UWA002.ant.amazon.com (10.43.160.82) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MSI-X descriptor has a "delivery mode" field which can be set to
various different targets, such as "Fixed" (default), SMI, NMI or INIT.

Usually when we pass devices into guests, we only ever see this MSI-X
descriptor configured as Fixed, so nobody realized that the other modes
were broken when using posted interrupts.

With posted interrupts, we end up configuring these special modes just
the same as a Fixed interrupt. That means instead of generating an SMI,
we inject a normal GSI into the guest.

Of course, that if completely broken. These two patches attempt to fix
the situation for x86 systems. If anyone has a great idea how to generalize
the filtering though, I'm all ears.


Alex
---

v1 -> v2:

  - Make error message more unique
  - Update commit message to point to __apic_accept_irq()

Alexander Graf (2):
  KVM: VMX: Disable posted interrupts for odd IRQs
  KVM: SVM: Disable posted interrupts for odd IRQs

 arch/x86/kvm/svm.c     | 16 ++++++++++++++++
 arch/x86/kvm/vmx/vmx.c | 22 ++++++++++++++++++++++
 2 files changed, 38 insertions(+)
```
#### [PATCH v7 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Wed Sep  4 15:10:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11130907
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26C5D1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 15:10:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E887122CF7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 15:10:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ZzQNV8kA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731259AbfIDPK1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 11:10:27 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:34470 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730173AbfIDPK0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 11:10:26 -0400
Received: by mail-pg1-f196.google.com with SMTP id n9so11421792pgc.1;
        Wed, 04 Sep 2019 08:10:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=J2tFQpQAldqgZlKB5LupCO5ngfjUyWGYvS66dt/H1ec=;
        b=ZzQNV8kASJ4xpTd7HZFPhRYirN94yMl7+GhAo/XuIOfYraA91weugvO/OlQfU3YaAo
         h6RQpfsLGHbKwicknjT9CMEywHlwYBwGEvzMRMXb+H6422PAlbNaTX0h+cDapWvVlt7g
         fi4NuuJVVp34+TcQRaI09XNZyTSCIeO1j0KMUS9vvhu7ZNMKzH6V7yW72qP0gR/1C6rO
         vYwDUSkDA/3vp6h+Og/CeGA6gv0H4I8eF/HqkDu9E5nTnReOtw4nv2HIc/3iQSEo2z4M
         RqMcoWltTdciRv6fKcuPyQh73ImKGQE2xXwI4wwobPKC+qYJRPAweDjuY5J3xaPYpRJR
         gunw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=J2tFQpQAldqgZlKB5LupCO5ngfjUyWGYvS66dt/H1ec=;
        b=dIPvtWLzlJNrtMj1OIxD8qYiDTNyilzcmJrdlN49AXuE6AfUj5LjKwksxtLvsOVTlX
         frLbq8epBEKQQJJHPkanwVvbJUuALdmJ48Tnq9V0jHG/+XhwwxCutBPndJ1KGMLpJ6qh
         1FHRsFBRZvpMV0TS1o33IOFRKHi/imG33F5rZTbGpp1J665ewTc736uxfr7ObRZVsX2X
         ADbsrMVJ9X6q+gs8WkOUp1ezmWpG/V8q7dRAbzJj4gJ82i/vJaRpaZV1y0XI1ruGJ3en
         1c5jFP48Jn95i5mTvmVHy5IFhGgVfyPEIXys1xtQHjYNehXQbI7tLPovYPpfXI1kl0D4
         L5HA==
X-Gm-Message-State: APjAAAXuuUl9JGCj2dz7sAls//gFSv+15a9iZwxw2bQNGWGPQ/LBb0Gv
        gs/Y93NuYWrgyL6E40z4MZA=
X-Google-Smtp-Source: 
 APXvYqx+WKEu5kZbeBnFWxNU4xgdmRXuCvXOlsEfBHqA7lBWZDwZpdD7lx1MX7lPKg9wgI86ymZ4ow==
X-Received: by 2002:a17:90a:a896:: with SMTP id
 h22mr5514847pjq.1.1567609825568;
        Wed, 04 Sep 2019 08:10:25 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 y25sm22561609pfm.95.2019.09.04.08.10.24
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Sep 2019 08:10:25 -0700 (PDT)
Subject: [PATCH v7 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        virtio-dev@lists.oasis-open.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, lcapitulino@redhat.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com
Date: Wed, 04 Sep 2019 08:10:24 -0700
Message-ID: <20190904150920.13848.32271.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page reporting device and it will perform
the required action to make the pages "reported", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a reported buddy page instead of a
standard buddy page. The cycle then repeats with additional non-reported
pages being pulled until the free areas all consist of reported pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scattergather list.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 40g on a 40g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. I have modified it to use Transparent Huge Pages. With this I
see almost no difference, -0.08%, with the patches applied and the feature
disabled. I see a regression of -0.86% with the feature enabled, but the
madvise disabled in the hypervisor due to a device being assigned. With
the feature fully enabled I see a regression of -3.27% versus the baseline
without these patches applied. In my testing I found that most of the
overhead was due to the page zeroing that comes as a result of the pages
having to be faulted back into the guest.

One side effect of these patches is that the guest becomes much more
resilient in terms of NUMA locality. With the pages being freed and then
reallocated when used it allows for the pages to be much closer to the
active thread, and as a result there can be situations where this patch
set will out-perform the stock kernel when the guest memory is not local
to the guest vCPUs. To avoid that in my testing I set the affinity of all
the vCPUs and QEMU instance to the same node.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermediate array
Moved stats out of free_area, now in separate area and pointed to from zone
Merged patch 5 into patch 4 to improve review-ability
Updated various code comments throughout

Changes from v2:
https://lore.kernel.org/lkml/20190724165158.6685.87228.stgit@localhost.localdomain/
Dropped "page hinting" in favor of "page reporting"
Renamed files from "hinting" to "reporting"
Replaced "Hinted" page type with "Reported" page flag
Added support for page poisoning while hinting is active
Add QEMU patch that implements PAGE_POISON feature

Changes from v3:
https://lore.kernel.org/lkml/20190801222158.22190.96964.stgit@localhost.localdomain/
Added mutex lock around page reporting startup and shutdown
Fixed reference to "page aeration" in patch 2
Split page reporting function bit out into separate QEMU patch
Limited capacity of scatterlist to vq size - 1 instead of vq size
Added exception handling for case of virtio descriptor allocation failure

Changes from v4:
https://lore.kernel.org/lkml/20190807224037.6891.53512.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_cycle()
Dropped if/continue for ternary operator in page_reporting_process()
Added checks for isolate and cma types to for_each_reporting_migratetype_order
Added virtio-dev, Michal Hocko, and Oscar Salvador to to:/cc:
Rebased on latest linux-next and QEMU git trees

Changes from v5:
https://lore.kernel.org/lkml/20190812213158.22097.30576.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_startup()
Updated shuffle code to use "shuffle_pick_tail" and updated patch description
Dropped storage of order and migratettype while page is being reported
Used get_pfnblock_migratetype to determine migratetype of page
Renamed put_reported_page to free_reported_page, added order as argument
Dropped check for CMA type as I believe we should be reporting those
Added code to allow moving of reported pages into and out of isolation
Defined page reporting order as minimum of Huge Page size vs MAX_ORDER - 1
Cleaned up use of static branch usage for page_reporting_notify_enabled

Changes from v6:
https://lore.kernel.org/lkml/20190821145806.20926.22448.stgit@localhost.localdomain/
Rebased on linux-next for 20190903
Added jump label to __page_reporting_request so we release RCU read lock
Removed "- 1" from capacity limit based on virtio ring
Added code to verify capacity is non-zero or return error on startup
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   84 ++++++++-
 include/linux/mmzone.h              |  124 ++++++++-----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |  177 ++++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  216 ++++++++++++++++------
 mm/page_reporting.c                 |  340 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   40 ++--
 mm/shuffle.h                        |   12 +
 14 files changed, 900 insertions(+), 131 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
#### [PATCH v7 00/21] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
From patchwork Wed Sep  4 16:13:17 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11130969
Return-Path: <SRS0=1IPj=W7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9839617EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 16:13:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6617921670
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Sep 2019 16:13:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="VOpQe785";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="JsFyqgNc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733110AbfIDQNV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 12:13:21 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:2389 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733149AbfIDQNV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 12:13:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1567613601; x=1599149601;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=CEJXn/Ju4H/MErkNTLsM4XX050EUmKAwz4FXqK1Ryro=;
  b=VOpQe785+BElvazfkfie3dVOJsWzIfbM+VXbgd8+Hz3g5r7XVqbLrhMn
   440ISIQnyVcdAPpADaLiyEEiqln946lK+VAR8b8hy5eH328+tRsyrQKBf
   rEhL0wdVq/8D5R0WsUCPbEC+yLuOwpw5qCa6Mt70syUWRf9FhR5nGTyi+
   Bh0Yl5CHovk389aFqc5puU4cfEKq/4UWTo79jafIK18pjE3OftrsoiXpo
   HtpF8qrL1Zhg8fbvI103eI8i4UGx90dsw5mnlIPynzeCpNQIUjnZKsCqx
   tNF8u7S1dvTzkCeAa1Iw18PhAAKG4nqHXnrHGaJtCa9SfgO5gjYWtENt/
   A==;
IronPort-SDR: 
 xhz7x+FFkkor3jGE/rN2hWNDoYtXloLRy9j7kDbspCCePbivblP6wH5W1r5DCMzyBPoJprFNUd
 5yjflF122JPKbZDVLX1abxadB0RfWAzkIiu0Z2IjHBBfxly7IewS4vJ0F8AJ4DEkTJflCxaVu0
 njPnTMDacCH2wyipv/sCDo5kwZsQgwG7c1tQEFwI2NAngXFy1wzQTv4qbyhuGkNtQhs7sVwfop
 rWJMEpmjpoM7rxpKJL3llI3+XfhbGZ3ZK6T2NNYwlMTTmvD/gBUxCaDx724yGagtl038Rx+iMf
 qVU=
X-IronPort-AV: E=Sophos;i="5.64,467,1559491200";
   d="scan'208";a="118323682"
Received: from mail-dm3nam05lp2052.outbound.protection.outlook.com (HELO
 NAM05-DM3-obe.outbound.protection.outlook.com) ([104.47.49.52])
  by ob1.hgst.iphmx.com with ESMTP; 05 Sep 2019 00:13:19 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=e5gOlx1+oyhwOc8+IPGaUZR3Fe6y9B3UUfh11oRqy8EXZwmBZf9JV5qVnvYo0SHMv0/dH4KNn5TKvrJfnPN4Ea0fi4reah0Tx/RdbJEYQEoJuY6SkaFIeHRTZNChPeZtPIzEEQadT3L96Us9qO3Gcv8pCW3OSqD+ig/0CvYzK242B0rtvjmO+2LUY0wkbdml8osZWZnsr0pyMl5KKaDLDSIeQ/Qmr4MU1i+A6fU93DhRjiG4V8l5QOdDhwkXLkwpwrYL/FldAFrFocFQ+CPrjF7Y2sF66sFzOmH2+XsJELiHRgzTvh3lKG/3X6ZX+pe2FNJGFiH3Q4zWXSHRB8u0Tg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=u+6R2dTZKRagaVpYFf5y7/cnzKNja7pUVOaQfpTag04=;
 b=Q8J4bZnig/V09CpsD1qaTgNAUw7S0ESihY7FOo4hA/PrRfAdWbQS80OLcSEgxWZ2sxfqA0a/9l2CSRMuc8yw9+Rblnv+Kk+Wl2TkB7qPkPusfy7sSh9q+mkS6GVO94BGQAAcg+/07V+4XMvN6cSaMOyFMJv0gIGb6V5Qe6ChGnqlCdi/5wtGrWd7Jlknxb/nYDAX/KxfNZPuv+5NTKnMyQEInIz80B25h+LOh/XpNuynirn5Yum4YFMpS0hvwbPP6PRxGZ6VHhOPZrWiCy+5wNnyBj0+kFhP+ngCCKH+VOjU6sx98WVakDYkLgeKydUi3X7BKd4AwjsEn+oZrLqWFA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=u+6R2dTZKRagaVpYFf5y7/cnzKNja7pUVOaQfpTag04=;
 b=JsFyqgNclkXMJo4ALUmcWaT3m76L2AquenFqkq0pYDXFlF7fU6o9LtXuOn+9CMgyDwjbhKBNkMB+HSwQyOTkRfRFiAHpEBQirouJ3tIwjVtStEnAfKwnyDFv3UkJ1Wuq6UjsqbzAU4BctAb3gvhAaT7NIplEV0VsoKSQ0MjJbNk=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB5504.namprd04.prod.outlook.com (20.178.247.210) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2178.16; Wed, 4 Sep 2019 16:13:17 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0%7]) with mapi id 15.20.2220.022; Wed, 4 Sep 2019
 16:13:17 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v7 00/21] KVM RISC-V Support
Thread-Topic: [PATCH v7 00/21] KVM RISC-V Support
Thread-Index: AQHVYzup7UjOJOzJOkmagvBOHGzFdQ==
Date: Wed, 4 Sep 2019 16:13:17 +0000
Message-ID: <20190904161245.111924-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MA1PR01CA0084.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::24)
 To MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [49.207.53.222]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: afccc673-423b-4e90-da9f-08d73152cbf6
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(7168020)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(4618075)(2017052603328)(7193020);SRVR:MN2PR04MB5504;
x-ms-traffictypediagnostic: MN2PR04MB5504:
x-ms-exchange-purlcount: 4
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB5504B94DECC64106E1BB14438DB80@MN2PR04MB5504.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:2043;
x-forefront-prvs: 0150F3F97D
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(376002)(136003)(396003)(346002)(366004)(39860400002)(199004)(189003)(66556008)(66446008)(7416002)(7736002)(8676002)(478600001)(966005)(25786009)(386003)(66946007)(99286004)(256004)(14444005)(50226002)(14454004)(66476007)(64756008)(6506007)(6512007)(102836004)(6306002)(6436002)(8936002)(54906003)(6116002)(3846002)(486006)(26005)(55236004)(86362001)(1076003)(53936002)(476003)(316002)(71200400001)(71190400001)(81156014)(52116002)(305945005)(5660300002)(6486002)(36756003)(186003)(2616005)(66066001)(44832011)(4326008)(2906002)(81166006)(110136005);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB5504;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 gRLcvomCvDWjS0ThogvN94yiUxqKM5248/e54GGXAQ/naqg13joSITAcfFz6RwGikzDe2NTvLScrprdz97VoFaozQWpTSCUjCvhGrFAZJUZe+ZUO4u8eHI6Bf2JRJ7LA8giuSFQfjKx1V0xnuLdAU+JxjaOaEROyda0tloe0o4GX1a2a6va3017IXVgSWaxF4W+w+wWjREqasUIAzainNwvKl0bBIj1vGCgA3LOocZH9lPJFdmi5srVgXwLHCI6QRHDfzCG4JGDbh+DErzP7Y3aak3yG7ma0+N5RXCiA2lg/B58UuSP5Yty0vndpuD+pGJ3mp/94xpgFy/dloncgspIf0NZIi9taQXzmM/FTXm8wBNFlVigGytZ/1ynLfDwZUyFqNLkZnnhjnpmCDJGqOLr03V/gRsfRTKrHCn85JKU=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 afccc673-423b-4e90-da9f-08d73152cbf6
X-MS-Exchange-CrossTenant-originalarrivaltime: 04 Sep 2019 16:13:17.6475
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 4Uq1Or3zPQWhWmIpuxiW2cOUyVLZEPpRswPo+VcGLGysnXRdPUYXFCtbJbeEvk8Uwq5oeTDrY7u+e6SOSKTBNQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB5504
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.

Here's a brief TODO list which we will work upon after this series:
1. Implement recursive stage2 page table programing
2. SBI v0.2 emulation in-kernel
3. SBI v0.2 hart hotplug emulation in-kernel
4. In-kernel PLIC emulation
5. ..... and more .....

This series can be found in riscv_kvm_v7 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch at:
https//github.com/avpatel/kvmtool.git

We need OpenSBI with RISC-V hypervisor extension support which can be
found in hyp_ext_changes_v1 branch at:
https://github.com/riscv/opensbi.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in riscv-hyp-work.next branch at:
https://github.com/alistair23/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v6:
- Rebased patches on Linux-5.3-rc7
- Added "return_handled" in struct kvm_mmio_decode to ensure that
  kvm_riscv_vcpu_mmio_return() updates SEPC only once
- Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
- Updated git repo URL in MAINTAINERS entry

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (16):
  KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API.
  RISC-V: Enable VIRTIO drivers in RV64 and RV32 defconfig
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (5):
  RISC-V: Export few kernel symbols
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.txt          | 141 +++-
 MAINTAINERS                             |  10 +
 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/configs/defconfig            |  11 +
 arch/riscv/configs/rv32_defconfig       |  11 +
 arch/riscv/include/asm/csr.h            |  58 ++
 arch/riscv/include/asm/hwcap.h          |  26 +
 arch/riscv/include/asm/kvm_host.h       | 255 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  30 +
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 104 +++
 arch/riscv/kernel/asm-offsets.c         | 148 ++++
 arch/riscv/kernel/cpufeature.c          |  79 +-
 arch/riscv/kernel/smp.c                 |   2 +-
 arch/riscv/kernel/time.c                |   1 +
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  92 +++
 arch/riscv/kvm/mmu.c                    | 911 +++++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  43 +
 arch/riscv/kvm/vcpu.c                   | 998 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 616 +++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 104 +++
 arch/riscv/kvm/vcpu_switch.S            | 376 +++++++++
 arch/riscv/kvm/vcpu_timer.c             | 113 +++
 arch/riscv/kvm/vm.c                     |  86 ++
 arch/riscv/kvm/vmid.c                   | 123 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   1 +
 31 files changed, 4405 insertions(+), 11 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
---
2.17.1
```
