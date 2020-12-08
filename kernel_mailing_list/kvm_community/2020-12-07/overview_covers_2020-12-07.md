

#### [PATCH v2 0/5] gitlab-ci: Add accelerator-specific Linux jobs
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Mon Dec  7 11:23:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11955313
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	TVD_PH_BODY_ACCOUNTS_PRE,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5782CC4361B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:25:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 158A52310B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:25:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726628AbgLGLZ2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 06:25:28 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43656 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726110AbgLGLZ1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 06:25:27 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607340241;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=auivzVy5y6QOjO5B6onFwW2/1Tqt9pcw8PvGSGN2N6I=;
        b=Pkij+/YyV/8cz1PaXpNPsg7BK2zTqi/P0zpOmTQFulHhUnSpS3uovLH7AsGvVp1FPI2Fgb
        1XQwCZkktxOdeka/bDYg9/htbtFxTWyAnkW7lU5BiaAby6Z/+FqCJB1knP5G7yvqe7Y7mv
        TLriBJUKd0xzFy+LLwmEzxDjkqFOv40=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-28-X1OdqdOYMP2pwMF5LlJNzQ-1; Mon, 07 Dec 2020 06:23:58 -0500
X-MC-Unique: X1OdqdOYMP2pwMF5LlJNzQ-1
Received: by mail-wm1-f71.google.com with SMTP id k126so2276890wmb.0
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 03:23:58 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=auivzVy5y6QOjO5B6onFwW2/1Tqt9pcw8PvGSGN2N6I=;
        b=OvF2y75UvqSJf1DlpQPafK5rNLE1jngDdPtKTtjSW4jL7JG01/qo/joKOAoRrMA1z8
         aoGC5wFtGEPXq2dMlicNAv3MmsTd5wfj3zCjPdKXx97G95nceAbeFTniydvGZgfdeCq3
         S97Ru9JtQIy6H/gKdLuo2d9ZLIcG9pX256fL9tTCtE2QloTVY+fstFwsDkoWV5v5oYzo
         tWY7icAehLcRHLwnRsOQb/yPcH9GgZp1aY6VeFsmOpRA3h0G5MBtxKq/yxIOw9L49+Jv
         MY8WMckf7ifuXzyb24OIh+UYJudlA4lltlW0ra1blaUghQdL/8qRZJLcDUFU+zbCGumh
         u+4A==
X-Gm-Message-State: AOAM5303NIOTQjg8QuJIvFNtxHHIp23dEs1N3MEKk/dOTPZtXA1aJ7mt
        1NQegliWJZfQavNYsJBU8ffHgf28hUn/NQQ5UKDkAtjOxSeldbbJ+GMB4b9+Dtu/cgxiwYqT34b
        KzyWB0AuwLr6q
X-Received: by 2002:a1c:750f:: with SMTP id
 o15mr17874285wmc.144.1607340237196;
        Mon, 07 Dec 2020 03:23:57 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJxtEVzeEC7jhHuC2uJxrowF2KeO/P6RnnWe7mlJ0qlo0yRhGBZE6N17mpPfK6BoXPRNgR263w==
X-Received: by 2002:a1c:750f:: with SMTP id
 o15mr17874250wmc.144.1607340236966;
        Mon, 07 Dec 2020 03:23:56 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 34sm14514869wrh.78.2020.12.07.03.23.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 03:23:56 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Halil Pasic <pasic@linux.ibm.com>, Thomas Huth <thuth@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Claudio Fontana <cfontana@suse.de>,
 Willian Rampazzo <wrampazz@redhat.com>, qemu-s390x@nongnu.org,
 Anthony Perard <anthony.perard@citrix.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 xen-devel@lists.xenproject.org, Paul Durrant <paul@xen.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>
Subject: [PATCH v2 0/5] gitlab-ci: Add accelerator-specific Linux jobs
Date: Mon,  7 Dec 2020 12:23:48 +0100
Message-Id: <20201207112353.3814480-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since v1:
- Documented cross_accel_build_job template (Claudio)
- Only add new job for s390x (Thomas)
- Do not add entry to MAINTAINERS (Daniel)
- Document 'build-tcg-disabled' job is X86 + KVM
- Drop the patches with negative review feedbacks

Hi,

I was custom to use Travis-CI for testing KVM builds on s390x/ppc
with the Travis-CI jobs.

During October Travis-CI became unusable for me (extremely slow,
see [1]). Then my free Travis account got updated to the new
"10K credit minutes allotment" [2] which I burned without reading
the notification email in time (I'd burn them eventually anyway).

Today Travis-CI is pointless to me. While I could pay to run my
QEMU jobs, I don't think it is fair for an Open Source project to
ask its forks to pay for a service.

As we want forks to run some CI before contributing patches, and
we have cross-build Docker images available for Linux hosts, I
added some cross KVM/Xen build jobs to Gitlab-CI.

Cross-building doesn't have the same coverage as native building,
as we can not run the tests. But this is still useful to get link
failures.

Resulting pipeline:
https://gitlab.com/philmd/qemu/-/pipelines/225948077

Regards,

Phil.

[1] https://travis-ci.community/t/build-delays-for-open-source-project/10272
[2] https://blog.travis-ci.com/2020-11-02-travis-ci-new-billing

Philippe Mathieu-Daudé (5):
  gitlab-ci: Document 'build-tcg-disabled' is a KVM X86 job
  gitlab-ci: Replace YAML anchors by extends (cross_system_build_job)
  gitlab-ci: Introduce 'cross_accel_build_job' template
  gitlab-ci: Add KVM s390x cross-build jobs
  gitlab-ci: Add Xen cross-build jobs

 .gitlab-ci.d/crossbuilds.yml | 80 ++++++++++++++++++++++++++----------
 .gitlab-ci.yml               |  5 +++
 2 files changed, 64 insertions(+), 21 deletions(-)
```
#### [RFC V2 00/37] Enhance memory utilization with DMEMFS
##### From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
From: Yulei Zhang <yuleixzhang@tencent.com>

```c
From patchwork Mon Dec  7 11:30:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: yulei zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11955355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5AB19C4167B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:32:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2327923340
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 11:32:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726650AbgLGLcR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 06:32:17 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40460 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726343AbgLGLcR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 06:32:17 -0500
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3457CC0613D1;
        Mon,  7 Dec 2020 03:31:37 -0800 (PST)
Received: by mail-pf1-x441.google.com with SMTP id t7so9599419pfh.7;
        Mon, 07 Dec 2020 03:31:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ILnSBWwyABm/ViEoQp4lFyaqVJLrOFveysOKfZkRhag=;
        b=rOqpLC970kODnReOtTNxrnnMNPzauP6Lc115KldbryjjQRCZwd2tgMSQz36C/kXt9Z
         56dN0/oxHJyldy4W9HdAVs4m9hHTgiYq6XORi2+17t9QxzLq9CSyGMoY6sU9WsUCUJmq
         hFSae+7CYWJuWnmH/utLWNjoeEGfdF6L92cc0b3mNBllb5TrS0zuwZQIrwEPB3RlN99I
         AL9gnTSq4awwyxv0ReEbuh0yGvL6GN3JwGQN39IHk9PEYfw2jBETrr4s+uq3N4+1Qm17
         takM/sOTbb34RuK6uOEAKMGSZYeKzXJt0NLJiHOg0sAG9T948DCs8tOXnElF9Bk+1YeY
         e2WQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ILnSBWwyABm/ViEoQp4lFyaqVJLrOFveysOKfZkRhag=;
        b=LbQvAnkdfmEtyjwSlUnaagEcJqxyK9SE81MFzarHXAC1bS1KWovtx5uZH7vUR9GMWd
         tlWubRY1Xz7q4RHjbGAOFn8ejLqR1nh2bKf6JYDM1f3rRM2vGRGD1O6siPLpKDBZNzb2
         XY36QModpMXV+qKCon8nSV/UwPCHPT3LPDA/714rP/XBo5lGXb7NZSZoGLtZKOqR5mOI
         HeiBMIpFp+tLUpOAd/NpUCE/uuQcWL7aB5669BiPKCZ5RBvtzTGcv8tFl15AojGxrjlZ
         Yjowa+IQBWVb6eJ00Um0JbrlDT/Rod6TwfSATD0gYfN97T9Xhr2qNu3+F/C598Z3btiL
         8pnw==
X-Gm-Message-State: AOAM530H0I8Wov6OWI8XUq7/k5ntpITAThEalqB/lKnHhcQ5ssIXWCY2
        nwJfNvcxVK03d4zYwO5Uc/4=
X-Google-Smtp-Source: 
 ABdhPJymSUXlaRjzXEzU2ngDriybhzR1Pzab6/cvJ6uKqjlNaxk3d/92EIH+NhH+um1mO4rml2NgOw==
X-Received: by 2002:a17:902:6103:b029:da:c46c:b3d6 with SMTP id
 t3-20020a1709026103b02900dac46cb3d6mr15400411plj.46.1607340696714;
        Mon, 07 Dec 2020 03:31:36 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 d4sm14219822pfo.127.2020.12.07.03.31.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 07 Dec 2020 03:31:36 -0800 (PST)
From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
To: linux-mm@kvack.org, akpm@linux-foundation.org,
        linux-fsdevel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, naoya.horiguchi@nec.com,
        viro@zeniv.linux.org.uk, pbonzini@redhat.com
Cc: joao.m.martins@oracle.com, rdunlap@infradead.org,
        sean.j.christopherson@intel.com, xiaoguangrong.eric@gmail.com,
        kernellwp@gmail.com, lihaiwei.kernel@gmail.com,
        Yulei Zhang <yuleixzhang@tencent.com>
Subject: [RFC V2 00/37] Enhance memory utilization with DMEMFS
Date: Mon,  7 Dec 2020 19:30:53 +0800
Message-Id: <cover.1607332046.git.yuleixzhang@tencent.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yuleixzhang@tencent.com>

In current system each physical memory page is assocaited with
a page structure which is used to track the usage of this page.
But due to the memory usage rapidly growing in cloud environment,
we find the resource consuming for page structure storage becomes
more and more remarkable. So is it possible that we could reclaim
such memory and make it reusable?

This patchset introduces an idea about how to save the extra
memory through a new virtual filesystem -- dmemfs.

Dmemfs (Direct Memory filesystem) is device memory or reserved
memory based filesystem. This kind of memory is special as it
is not managed by kernel and most important it is without 'struct page'.
Therefore we can leverage the extra memory from the host system
to support more tenants in our cloud service.

As the belowing figure shows, we uses a kernel boot parameter 'dmem='
to reserve the system memory when the host system boots up, the
remaining system memory is still managed by system memory management
which is associated with "struct page", the reserved memory
will be managed by dmem and assigned to guest system, the details
can be checked in /Documentation/admin-guide/kernel-parameters.txt.

   +------------------+--------------------------------------+
   |  system memory   |     memory for guest system          | 
   +------------------+--------------------------------------+
    |                                   |
    v                                   |
struct page                             |
    |                                   |
    v                                   v
    system mem management             dmem  

And during the usage, the dmemfs will handle the memory request to
allocate and free the reserved memory on each NUMA node, the user 
space application could leverage the mmap interface to access the 
memory, and kernel module such as kvm and vfio would be able to pin
the memory thongh follow_pfn() and get_user_page() in different given
page size granularities.

          +-----------+  +-----------+
          |   QEMU    |  |  dpdk etc.|      user
          +-----+-----+  +-----------+
  +-----------|------\------------------------------+
  |           |       v                    kernel   |
  |           |     +-------+  +-------+            |
  |           |     |  KVM  |  | vfio  |            |
  |           |     +-------+  +-------+            |
  |           |         |          |                |
  |      +----v---------v----------v------+         |
  |      |                                |         |
  |      |             Dmemfs             |         |
  |      |                                |         |
  |      +--------------------------------+         |
  +-----------/-----------------------\-------------+
             /                         \
     +------v-----+                +----v-------+
     |   node 0   |                |   node 1   |
     +------------+                +------------+

Theoretically for each 4k physical page it can save 64 bytes if
we drop the 'struct page', so for guest memory with 320G it can
save about 5G physical memory totally.

Detailed usage of dmemfs is included in
/Documentation/filesystem/dmemfs.rst.

V1->V2:
* Rebase the code the kernel version 5.10.0-rc3.
* Introudce dregion->memmap for dmem to add _refcount for each
  dmem page.
* Enable record_steal_time for dmem before entering guest system.
* Adjust page walking for dmem.

Yulei Zhang (37):
  fs: introduce dmemfs module
  mm: support direct memory reservation
  dmem: implement dmem memory management
  dmem: let pat recognize dmem
  dmemfs: support mmap for dmemfs
  dmemfs: support truncating inode down
  dmem: trace core functions
  dmem: show some statistic in debugfs
  dmemfs: support remote access
  dmemfs: introduce max_alloc_try_dpages parameter
  mm: export mempolicy interfaces to serve dmem allocator
  dmem: introduce mempolicy support
  mm, dmem: introduce PFN_DMEM and pfn_t_dmem
  mm, dmem: differentiate dmem-pmd and thp-pmd
  mm: add pmd_special() check for pmd_trans_huge_lock()
  dmemfs: introduce ->split() to dmemfs_vm_ops
  mm, dmemfs: support unmap_page_range() for dmemfs pmd
  mm: follow_pmd_mask() for dmem huge pmd
  mm: gup_huge_pmd() for dmem huge pmd
  mm: support dmem huge pmd for vmf_insert_pfn_pmd()
  mm: support dmem huge pmd for follow_pfn()
  kvm, x86: Distinguish dmemfs page from mmio page
  kvm, x86: introduce VM_DMEM for syscall support usage
  dmemfs: support hugepage for dmemfs
  mm, x86, dmem: fix estimation of reserved page for vaddr_get_pfn()
  mm, dmem: introduce pud_special() for dmem huge pud support
  mm: add pud_special() check to support dmem huge pud
  mm, dmemfs: support huge_fault() for dmemfs
  mm: add follow_pte_pud() to support huge pud look up
  dmem: introduce dmem_bitmap_alloc() and dmem_bitmap_free()
  dmem: introduce mce handler
  mm, dmemfs: register and handle the dmem mce
  kvm, x86: enable record_steal_time for dmem
  dmem: add dmem unit tests
  mm, dmem: introduce dregion->memmap for dmem
  vfio: support dmempage refcount for vfio
  Add documentation for dmemfs

 Documentation/admin-guide/kernel-parameters.txt |   38 +
 Documentation/filesystems/dmemfs.rst            |   58 ++
 Documentation/filesystems/index.rst             |    1 +
 arch/x86/Kconfig                                |    1 +
 arch/x86/include/asm/pgtable.h                  |   32 +-
 arch/x86/include/asm/pgtable_types.h            |   13 +-
 arch/x86/kernel/setup.c                         |    3 +
 arch/x86/kvm/mmu/mmu.c                          |    1 +
 arch/x86/mm/pat/memtype.c                       |   21 +
 drivers/vfio/vfio_iommu_type1.c                 |   13 +-
 fs/Kconfig                                      |    1 +
 fs/Makefile                                     |    1 +
 fs/dmemfs/Kconfig                               |   16 +
 fs/dmemfs/Makefile                              |    8 +
 fs/dmemfs/inode.c                               | 1060 ++++++++++++++++++++
 fs/dmemfs/trace.h                               |   54 +
 fs/inode.c                                      |    6 +
 include/linux/dmem.h                            |   54 +
 include/linux/fs.h                              |    1 +
 include/linux/huge_mm.h                         |    5 +-
 include/linux/mempolicy.h                       |    3 +
 include/linux/mm.h                              |    9 +
 include/linux/pfn_t.h                           |   17 +-
 include/linux/pgtable.h                         |   22 +
 include/trace/events/dmem.h                     |   85 ++
 include/uapi/linux/magic.h                      |    1 +
 mm/Kconfig                                      |   19 +
 mm/Makefile                                     |    1 +
 mm/dmem.c                                       | 1196 +++++++++++++++++++++++
 mm/dmem_reserve.c                               |  303 ++++++
 mm/gup.c                                        |  101 +-
 mm/huge_memory.c                                |   19 +-
 mm/memory-failure.c                             |   70 +-
 mm/memory.c                                     |   74 +-
 mm/mempolicy.c                                  |    4 +-
 mm/mincore.c                                    |    8 +-
 mm/mprotect.c                                   |    7 +-
 mm/mremap.c                                     |    3 +
 mm/pagewalk.c                                   |    4 +-
 tools/testing/dmem/Kbuild                       |    1 +
 tools/testing/dmem/Makefile                     |   10 +
 tools/testing/dmem/dmem-test.c                  |  184 ++++
 virt/kvm/kvm_main.c                             |   13 +-
 43 files changed, 3483 insertions(+), 58 deletions(-)
 create mode 100644 Documentation/filesystems/dmemfs.rst
 create mode 100644 fs/dmemfs/Kconfig
 create mode 100644 fs/dmemfs/Makefile
 create mode 100644 fs/dmemfs/inode.c
 create mode 100644 fs/dmemfs/trace.h
 create mode 100644 include/linux/dmem.h
 create mode 100644 include/trace/events/dmem.h
 create mode 100644 mm/dmem.c
 create mode 100644 mm/dmem_reserve.c
 create mode 100644 tools/testing/dmem/Kbuild
 create mode 100644 tools/testing/dmem/Makefile
 create mode 100644 tools/testing/dmem/dmem-test.c
```
#### [PATCH v3 0/5] gitlab-ci: Add accelerator-specific Linux jobs
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Mon Dec  7 13:14:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11955797
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	TVD_PH_BODY_ACCOUNTS_PRE,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C998C433FE
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 13:16:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 446EB23339
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 13:16:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725850AbgLGNQk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 08:16:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29634 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725550AbgLGNQk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 08:16:40 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607346913;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=D+Xzt47T3O6uanVPO2OPfmJ/SH9QMRtVuJ5cnLL0G9o=;
        b=XJcNucjFg6/wMUKU4ReBm+QmxzGaJ87q471BSw4qT+Ucm9kQCssrV+M8DVZFQGlQLCWI/a
        1BKP/D5z4rvzhBJGwvBdpyhYYD7OXPDRbViSqXmZHiTsLBAlqVvuLvxXgubqPleA3uD2zM
        Sl/I2skzvH+gf/z1XEebN7PZOuPo1jI=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-455-pvtvFBvYOyOImE_AFkFRww-1; Mon, 07 Dec 2020 08:15:09 -0500
X-MC-Unique: pvtvFBvYOyOImE_AFkFRww-1
Received: by mail-wm1-f70.google.com with SMTP id k128so5297569wme.7
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 05:15:08 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=D+Xzt47T3O6uanVPO2OPfmJ/SH9QMRtVuJ5cnLL0G9o=;
        b=VoRXN9ICh8P2SGKQPH9yQP58e8lRmFuEPt9dQlM9y6Q64HBti3PvOyFvzrej27iDOS
         F4f3hcvALixTn6L4uuR1Op+/u8Ir2lI0zYyuWDJE7Ts9dC3lui+GLQi0k1hXu5xwQniN
         EbyuOenHUyusA2xM7ta6HwaY2QXJuh0xnGyl6zs7M7yrRaMExzS8rlHfZad/NliTE47e
         DlX9PNmOe5UDEcRoBdgR+mfJaI+kBgAEfmuW6wyY6aw9rqkhPIfsOhJe67n/e92c9fyt
         VxHxeskWegdgWajpCkHN+H3EISff+j3Fl2OYKRfMFYcasz/DAXAnm4BGSuMH+pLyK8at
         7MoQ==
X-Gm-Message-State: AOAM531BEX+tn7a68FSeRLkBNmJcpcEIGkFgxPEGKP3WzDN9NcMZVLuf
        YOtLlW7zjpmnyRy6EZlHppnLLeSthWozwra+giuTAaPd4trcR4RrN5Z8Pv3SqAvTczvJh+ygQtl
        EknudA+XDr7ec
X-Received: by 2002:a5d:4d88:: with SMTP id b8mr19446877wru.134.1607346907512;
        Mon, 07 Dec 2020 05:15:07 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJzpnUya1Cq26y+zerYd2xTIJ5RvuSXM0q1BxVsK+34xdINKnlF/ke5kWAF9RdCASl4P3rK0fg==
X-Received: by 2002:a5d:4d88:: with SMTP id b8mr19446856wru.134.1607346907342;
        Mon, 07 Dec 2020 05:15:07 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 94sm6169289wrq.22.2020.12.07.05.15.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 05:15:06 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Thomas Huth <thuth@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, kvm@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Anthony Perard <anthony.perard@citrix.com>, =?utf-8?q?Philippe_Mathieu-Daud?=
	=?utf-8?q?=C3=A9?= <philmd@redhat.com>, qemu-s390x@nongnu.org,
 Halil Pasic <pasic@linux.ibm.com>, Willian Rampazzo <wrampazz@redhat.com>,
 Paul Durrant <paul@xen.org>, Cornelia Huck <cohuck@redhat.com>,
 xen-devel@lists.xenproject.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Claudio Fontana <cfontana@suse.de>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>
Subject: [PATCH v3 0/5] gitlab-ci: Add accelerator-specific Linux jobs
Date: Mon,  7 Dec 2020 14:14:58 +0100
Message-Id: <20201207131503.3858889-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since v2:
- Fixed ARM Xen job
- Renamed jobs with -$accel trailer (Thomas)

Since v1:
- Documented cross_accel_build_job template (Claudio)
- Only add new job for s390x (Thomas)
- Do not add entry to MAINTAINERS (Daniel)
- Document 'build-tcg-disabled' job is X86 + KVM
- Drop the patches with negative review feedbacks

Hi,

I was custom to use Travis-CI for testing KVM builds on s390x/ppc
with the Travis-CI jobs.

During October Travis-CI became unusable for me (extremely slow,
see [1]). Then my free Travis account got updated to the new
"10K credit minutes allotment" [2] which I burned without reading
the notification email in time (I'd burn them eventually anyway).

Today Travis-CI is pointless to me. While I could pay to run my
QEMU jobs, I don't think it is fair for an Open Source project to
ask its forks to pay for a service.

As we want forks to run some CI before contributing patches, and
we have cross-build Docker images available for Linux hosts, I
added some cross KVM/Xen build jobs to Gitlab-CI.

Cross-building doesn't have the same coverage as native building,
as we can not run the tests. But this is still useful to get link
failures.

Resulting pipeline:
https://gitlab.com/philmd/qemu/-/pipelines/226240415

Regards,

Phil.

[1] https://travis-ci.community/t/build-delays-for-open-source-project/10272
[2] https://blog.travis-ci.com/2020-11-02-travis-ci-new-billing

Philippe Mathieu-Daudé (5):
  gitlab-ci: Document 'build-tcg-disabled' is a KVM X86 job
  gitlab-ci: Replace YAML anchors by extends (cross_system_build_job)
  gitlab-ci: Introduce 'cross_accel_build_job' template
  gitlab-ci: Add KVM s390x cross-build jobs
  gitlab-ci: Add Xen cross-build jobs

 .gitlab-ci.d/crossbuilds.yml | 78 ++++++++++++++++++++++++++----------
 .gitlab-ci.yml               |  5 +++
 2 files changed, 62 insertions(+), 21 deletions(-)
```
#### [PATCH 0/2 v4] KVM: nSVM: Check reserved values for 'Type' and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Dec  7 19:41:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11956635
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DAF40C4167B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 19:44:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A41BF238E1
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 19:44:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726744AbgLGTo2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 14:44:28 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:56404 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725822AbgLGTo1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 14:44:27 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7JdqUu004059;
        Mon, 7 Dec 2020 19:43:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=dQzv5Yngcb2G7uGdsv+4ZRDkPEbGpTwdACNd/Um74SU=;
 b=cNFYRZeBTmflvcKvsafSBX6Ena+CB6i4TUnxfpidnZncpWHHoU5lbkJER7+YEzDyq72Y
 bICKeIEttcVoPvb4IUJL8j7kXWf7l4VQbJ+8mjhRmtjOLTeLqLaGOsQti6Q34Q67Xf1y
 FQrmWvx/t8IFjM2nMM2qsuNtALEplZErNor8F4qO60ej/mutGM2Q87BBRySV6cOnk7Us
 ofi2G8zmbOkWq1U5oQ77wExcLsoWSVWOPZ4VCWGe4tyASp1Z8gmf2HmkMHDIWZcMtA7j
 NtX7/RNfD89rzZYxeiCDUnHLZc6WjSohPHjhjMD8H2LKBeVrUM08ZWYitXnJmSfEco7B cg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 3581mqq6g7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 07 Dec 2020 19:43:42 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0B7JeiB3044479;
        Mon, 7 Dec 2020 19:41:42 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 358ksmn0x5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 07 Dec 2020 19:41:42 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0B7JfeNO013137;
        Mon, 7 Dec 2020 19:41:41 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 07 Dec 2020 11:41:40 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/2 v4] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon,  7 Dec 2020 19:41:27 +0000
Message-Id: <20201207194129.7543-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9828
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=940
 suspectscore=1
 bulkscore=0 malwarescore=0 phishscore=0 mlxscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012070126
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9828
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 mlxlogscore=954
 clxscore=1015 malwarescore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 phishscore=0 spamscore=0 impostorscore=0 mlxscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012070126
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
	1. Changed storage type of local variables, 'type' and 'vector' in
	   patch# 1, from u32 to u8.
	2. Fixed build breakage due to missing parentheses around logical
	   operators. The second check has also been split into two 'if-else'
	   conditionals.

[PATCH 1/2 v4] KVM: nSVM: Check reserved values for 'Type' and invalid
[PATCH 2/2 v4] nSVM: Test reserved values for 'Type' and invalid vectors in

 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

Krish Sadhukhan (1):
      KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ

 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

Krish Sadhukhan (1):
      nSVM: Test reserved values for 'Type' and invalid vectors in EVENTINJ
```
#### [PATCH v11 00/81] VM introspection
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From patchwork Mon Dec  7 20:45:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11956657
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7BC94C1B0D9
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 20:47:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 60B152389F
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 20:47:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726939AbgLGUq5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 15:46:57 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:41852 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726734AbgLGUq5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Dec 2020 15:46:57 -0500
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 D92AF30462D3;
        Mon,  7 Dec 2020 22:46:11 +0200 (EET)
Received: from localhost.localdomain (unknown [91.199.104.27])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 6C0163072784;
        Mon,  7 Dec 2020 22:46:11 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>,
 Edwin Zhai <edwin.zhai@intel.com>, Jan Kiszka <jan.kiszka@siemens.com>,
 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
 Mathieu Tarral <mathieu.tarral@protonmail.com>,
 Patrick Colp <patrick.colp@oracle.com>,
 =?utf-8?q?Samuel_Laur=C3=A9n?= <samuel.lauren@iki.fi>,
 Stefan Hajnoczi <stefanha@redhat.com>, Tamas K Lengyel <tamas@tklengyel.com>,
 Weijiang Yang <weijiang.yang@intel.com>, Yu C Zhang <yu.c.zhang@intel.com>,
 Sean Christopherson <seanjc@google.com>, Joerg Roedel <joro@8bytes.org>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>
Subject: [PATCH v11 00/81] VM introspection
Date: Mon,  7 Dec 2020 22:45:01 +0200
Message-Id: <20201207204622.15258-1-alazar@bitdefender.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are no major changes from the previous version (v10), except on
patch 49, to avoid a possible case of stack corruption.

Changes since v10 (https://lore.kernel.org/kvm/20201125093600.2766-1-alazar@bitdefender.com/):
  - fix the event reply validation
  - fix the compile-time warnings reported by "kernel test robot <lkp@intel.com>"
  - send the error code (KVM_ENOMEM) when the memory allocation fails
    while handling the KVMI_VCPU_GET_XSAVE command

Adalbert Lazăr (24):
  KVM: UAPI: add error codes used by the VM introspection code
  KVM: add kvm_vcpu_kick_and_wait()
  KVM: doc: fix the hypercalls numbering
  KVM: x86: add kvm_x86_ops.control_cr3_intercept()
  KVM: x86: add kvm_x86_ops.desc_ctrl_supported()
  KVM: x86: add kvm_x86_ops.control_desc_intercept()
  KVM: x86: export kvm_vcpu_ioctl_x86_set_xsave()
  KVM: introspection: add hook/unhook ioctls
  KVM: introspection: add permission access ioctls
  KVM: introspection: add the read/dispatch message function
  KVM: introspection: add KVMI_GET_VERSION
  KVM: introspection: add KVMI_VM_CHECK_COMMAND and KVMI_VM_CHECK_EVENT
  KVM: introspection: add KVM_INTROSPECTION_PREUNHOOK
  KVM: introspection: add KVMI_VM_EVENT_UNHOOK
  KVM: introspection: add KVMI_VM_CONTROL_EVENTS
  KVM: introspection: add a jobs list to every introspected vCPU
  KVM: introspection: add KVMI_VM_PAUSE_VCPU
  KVM: introspection: add support for vCPU events
  KVM: introspection: add KVMI_VCPU_EVENT_PAUSE
  KVM: introspection: add KVMI_VM_CONTROL_CLEANUP
  KVM: introspection: add KVMI_VCPU_GET_XCR
  KVM: introspection: add KVMI_VCPU_SET_XSAVE
  KVM: introspection: extend KVMI_GET_VERSION with struct kvmi_features
  KVM: introspection: add KVMI_VCPU_TRANSLATE_GVA

Marian Rotariu (1):
  KVM: introspection: add KVMI_VCPU_GET_CPUID

Mihai Donțu (33):
  KVM: x86: add kvm_arch_vcpu_get_regs() and kvm_arch_vcpu_get_sregs()
  KVM: x86: avoid injecting #PF when emulate the VMCALL instruction
  KVM: x86: add kvm_x86_ops.control_msr_intercept()
  KVM: x86: vmx: use a symbolic constant when checking the exit
    qualifications
  KVM: x86: save the error code during EPT/NPF exits handling
  KVM: x86: add kvm_x86_ops.fault_gla()
  KVM: x86: extend kvm_mmu_gva_to_gpa_system() with the 'access'
    parameter
  KVM: x86: page track: provide all callbacks with the guest virtual
    address
  KVM: x86: page track: add track_create_slot() callback
  KVM: x86: page_track: add support for preread, prewrite and preexec
  KVM: x86: wire in the preread/prewrite/preexec page trackers
  KVM: introduce VM introspection
  KVM: introspection: add KVMI_VM_GET_INFO
  KVM: introspection: add KVMI_VM_READ_PHYSICAL/KVMI_VM_WRITE_PHYSICAL
  KVM: introspection: handle vCPU introspection requests
  KVM: introspection: handle vCPU commands
  KVM: introspection: add KVMI_VCPU_GET_INFO
  KVM: introspection: add the crash action handling on the event reply
  KVM: introspection: add KVMI_VCPU_CONTROL_EVENTS
  KVM: introspection: add KVMI_VCPU_GET_REGISTERS
  KVM: introspection: add KVMI_VCPU_SET_REGISTERS
  KVM: introspection: add KVMI_VCPU_EVENT_HYPERCALL
  KVM: introspection: add KVMI_VCPU_EVENT_BREAKPOINT
  KVM: introspection: add KVMI_VCPU_CONTROL_CR and KVMI_VCPU_EVENT_CR
  KVM: introspection: add KVMI_VCPU_INJECT_EXCEPTION +
    KVMI_VCPU_EVENT_TRAP
  KVM: introspection: add KVMI_VCPU_EVENT_XSETBV
  KVM: introspection: add KVMI_VCPU_GET_XSAVE
  KVM: introspection: add KVMI_VCPU_GET_MTRR_TYPE
  KVM: introspection: add KVMI_VCPU_CONTROL_MSR and KVMI_VCPU_EVENT_MSR
  KVM: introspection: add KVMI_VM_SET_PAGE_ACCESS
  KVM: introspection: add KVMI_VCPU_EVENT_PF
  KVM: introspection: emulate a guest page table walk on SPT violations
    due to A/D bit updates
  KVM: x86: call the page tracking code on emulation failure

Mircea Cîrjaliu (2):
  KVM: x86: disable gpa_available optimization for fetch and page-walk
    SPT violations
  KVM: introspection: add vCPU related data

Nicușor Cîțu (19):
  KVM: x86: add kvm_arch_vcpu_set_regs()
  KVM: x86: add kvm_x86_ops.bp_intercepted()
  KVM: x86: add kvm_x86_ops.cr3_write_intercepted()
  KVM: svm: add support for descriptor-table VM-exits
  KVM: x86: add kvm_x86_ops.desc_intercepted()
  KVM: x86: add kvm_x86_ops.msr_write_intercepted()
  KVM: x86: svm: use the vmx convention to control the MSR interception
  KVM: x86: add kvm_x86_ops.control_singlestep()
  KVM: x86: export kvm_arch_vcpu_set_guest_debug()
  KVM: x86: export kvm_inject_pending_exception()
  KVM: x86: export kvm_vcpu_ioctl_x86_get_xsave()
  KVM: introspection: add cleanup support for vCPUs
  KVM: introspection: restore the state of #BP interception on unhook
  KVM: introspection: restore the state of CR3 interception on unhook
  KVM: introspection: add KVMI_VCPU_EVENT_DESCRIPTOR
  KVM: introspection: restore the state of descriptor-table register
    interception on unhook
  KVM: introspection: restore the state of MSR interception on unhook
  KVM: introspection: add KVMI_VCPU_CONTROL_SINGLESTEP
  KVM: introspection: add KVMI_VCPU_EVENT_SINGLESTEP

Ștefan Șicleru (2):
  KVM: add kvm_get_max_gfn()
  KVM: introspection: add KVMI_VM_GET_MAX_GFN

 Documentation/virt/kvm/api.rst                |  159 ++
 Documentation/virt/kvm/hypercalls.rst         |   39 +-
 Documentation/virt/kvm/kvmi.rst               | 1573 +++++++++++++
 arch/x86/include/asm/kvm_host.h               |   46 +-
 arch/x86/include/asm/kvm_page_track.h         |   71 +-
 arch/x86/include/asm/kvmi_host.h              |  110 +
 arch/x86/include/asm/vmx.h                    |    2 +
 arch/x86/include/uapi/asm/kvmi.h              |  167 ++
 arch/x86/kvm/Kconfig                          |    9 +
 arch/x86/kvm/Makefile                         |    2 +
 arch/x86/kvm/emulate.c                        |    4 +
 arch/x86/kvm/kvm_emulate.h                    |    1 +
 arch/x86/kvm/kvmi.c                           | 1131 ++++++++++
 arch/x86/kvm/kvmi.h                           |   24 +
 arch/x86/kvm/kvmi_msg.c                       |  456 ++++
 arch/x86/kvm/mmu/mmu.c                        |  140 +-
 arch/x86/kvm/mmu/mmu_internal.h               |    4 +
 arch/x86/kvm/mmu/page_track.c                 |  146 +-
 arch/x86/kvm/mmu/spte.c                       |   17 +
 arch/x86/kvm/svm/svm.c                        |  288 ++-
 arch/x86/kvm/svm/svm.h                        |    7 +
 arch/x86/kvm/vmx/capabilities.h               |    7 +-
 arch/x86/kvm/vmx/vmx.c                        |  168 +-
 arch/x86/kvm/vmx/vmx.h                        |    4 -
 arch/x86/kvm/x86.c                            |  302 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |    2 +-
 include/linux/kvm_host.h                      |   16 +
 include/linux/kvmi_host.h                     |  110 +
 include/uapi/linux/kvm.h                      |   20 +
 include/uapi/linux/kvm_para.h                 |    5 +
 include/uapi/linux/kvmi.h                     |  245 ++
 tools/testing/selftests/kvm/Makefile          |    1 +
 .../testing/selftests/kvm/x86_64/kvmi_test.c  | 2005 +++++++++++++++++
 virt/kvm/introspection/kvmi.c                 | 1264 +++++++++++
 virt/kvm/introspection/kvmi_int.h             |  129 ++
 virt/kvm/introspection/kvmi_msg.c             |  915 ++++++++
 virt/kvm/kvm_main.c                           |   98 +
 37 files changed, 9525 insertions(+), 162 deletions(-)
 create mode 100644 Documentation/virt/kvm/kvmi.rst
 create mode 100644 arch/x86/include/asm/kvmi_host.h
 create mode 100644 arch/x86/include/uapi/asm/kvmi.h
 create mode 100644 arch/x86/kvm/kvmi.c
 create mode 100644 arch/x86/kvm/kvmi.h
 create mode 100644 arch/x86/kvm/kvmi_msg.c
 create mode 100644 include/linux/kvmi_host.h
 create mode 100644 include/uapi/linux/kvmi.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvmi_test.c
 create mode 100644 virt/kvm/introspection/kvmi.c
 create mode 100644 virt/kvm/introspection/kvmi_int.h
 create mode 100644 virt/kvm/introspection/kvmi_msg.c


base-commit: dc924b062488a0376aae41d3e0a27dc99f852a5e
CC: Edwin Zhai <edwin.zhai@intel.com>
CC: Jan Kiszka <jan.kiszka@siemens.com>
CC: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
CC: Mathieu Tarral <mathieu.tarral@protonmail.com>
CC: Patrick Colp <patrick.colp@oracle.com>
CC: Samuel Laurén <samuel.lauren@iki.fi>
CC: Stefan Hajnoczi <stefanha@redhat.com>
CC: Tamas K Lengyel <tamas@tklengyel.com>
CC: Weijiang Yang <weijiang.yang@intel.com>
CC: Yu C Zhang <yu.c.zhang@intel.com>
CC: Sean Christopherson <seanjc@google.com>
CC: Joerg Roedel <joro@8bytes.org>
CC: Vitaly Kuznetsov <vkuznets@redhat.com>
CC: Wanpeng Li <wanpengli@tencent.com>
CC: Jim Mattson <jmattson@google.com>
```
#### [PATCH 0/2] x86: Add the feature Virtual SPEC_CTRL
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Mon Dec  7 22:37:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11957003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4C69C4361B
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 22:38:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 95436239CF
	for <kvm@archiver.kernel.org>; Mon,  7 Dec 2020 22:38:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727995AbgLGWik (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 17:38:40 -0500
Received: from mail-eopbgr760058.outbound.protection.outlook.com
 ([40.107.76.58]:62457
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727785AbgLGWik (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 17:38:40 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=N52ZQHCJ55NCsLxUSD8ESC9XVCqFZ5z69hlVqvnWOy2EkvaY1vjJyt4JHU8fexQz4IndfwmbOloIeeIwfZq45oifjN9zFupDyAVzHACWkwP/PCg7E4bpvHZH+PLHWPllgT0MpFAP9uAr8L1ra4/Cqsb0RDV8fYNUW8/zJW8IjNitCG4f3L5N0blxmou/Za+5SxLlACegFVUdyzWle+HlVDpmDN4HsuiZ49DFvPRp9O9pJkmH5p+z68gLMz763wrDPMc/TJwtW0GnH2Wzq8x4wBLDwfUHUOgoBOtAlb/oUsNrDWuHfYLsXJvIRL7J/N2MW7hdSe5dCqjsO+Fi057e3Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=GEQ0wqp9bp9VQT35GabU9pffixk7osnVtkmYsDMiSjg=;
 b=HJ8SD7tz381Vo1LgkMTkP2uiFTtBil64IGaNcJeFQ6catISCo8GgUYvYnVXZvkVvIIiUopQZEoUl84qVBEaMH3ePHFnDT2AmQSeV12yN/jWKfjyJgGfafjeHSAQI/TbclF/MudWTORaV/oWMOifsAt/a7BrDYmIKUc2gTej6s02IsPb919tkJEVU7Jqu/6t6egwb6/zxZiI9uMMKtx/xj4EGN5ZH3aZe+FP8OUEWrlsDVOM120r95Y81FVJXIEI3wo+0cWPPhOdBTMNCsT0HgT7IIwr3bFQp/e+bJwbG7cFx2tI4GyKWmcD3l0PXJ8MqNMd7mDUY3+JCPilhQOrkQg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=GEQ0wqp9bp9VQT35GabU9pffixk7osnVtkmYsDMiSjg=;
 b=qLk+3Rn8A1AU765csXPukI//kMRtdwuL0zvSwFvKtT7cJbRWe7EusYNbo6YzF5kNbypUk0t84abh/TcNZ6afXywwGplOyzhw2y80JDd4WzXqFH2DM64RzkONYJfbh8KiOxJHRA64f4o7ZN2N5s7zgtlZ24fFOsbdouISCzB5QqE=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB2624.namprd12.prod.outlook.com (2603:10b6:805:70::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.31; Mon, 7 Dec
 2020 22:37:46 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3632.023; Mon, 7 Dec 2020
 22:37:45 +0000
Subject: [PATCH 0/2] x86: Add the feature Virtual SPEC_CTRL
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de
Cc: fenghua.yu@intel.com, tony.luck@intel.com, wanpengli@tencent.com,
        kvm@vger.kernel.org, thomas.lendacky@amd.com, peterz@infradead.org,
        seanjc@google.com, joro@8bytes.org, x86@kernel.org,
        kyung.min.park@intel.com, linux-kernel@vger.kernel.org,
        krish.sadhukhan@oracle.com, hpa@zytor.com, mgross@linux.intel.com,
        vkuznets@redhat.com, kim.phillips@amd.com, wei.huang2@amd.com,
        jmattson@google.com
Date: Mon, 07 Dec 2020 16:37:42 -0600
Message-ID: <160738054169.28590.5171339079028237631.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH2PR14CA0017.namprd14.prod.outlook.com
 (2603:10b6:610:60::27) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 CH2PR14CA0017.namprd14.prod.outlook.com (2603:10b6:610:60::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17 via Frontend
 Transport; Mon, 7 Dec 2020 22:37:43 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c59130bc-2708-47ff-c9c7-08d89b00b7d1
X-MS-TrafficTypeDiagnostic: SN6PR12MB2624:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB262488E28B70D62F8307E0C095CE0@SN6PR12MB2624.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 c18iB9MIl2TbT3iyCC6YDC28IfS4RA4uiVgR4zN+vvh/MyLW4bdF6Vrgl4tynzwJqYI9exnC4NG2P7/8lNC8RvLucUdnyXqGYK/qiOlbJCwk2rpuOBpdwhyUt4rZTAe8NZddye6BoMf9nMWKxndoSUwyNLyrcmoqMlkYzHWD/ID1IzE3t0A6sdbgwFKCvaIojK0Mh6zPKqe1b4btvCEU4PNtF99YsRJkI1qmCx1A/0rKn8T+QiFbmym7WHqaZtTI8P6vpMGpp8WU1jMydCQe55WaGvFER2YKi/tmw0vPze3VoaIQi9/RtBwH+w4UECXp
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(396003)(366004)(346002)(136003)(376002)(39860400002)(7416002)(8676002)(66946007)(5660300002)(66556008)(86362001)(478600001)(66476007)(83380400001)(16526019)(33716001)(8936002)(26005)(52116002)(103116003)(6486002)(44832011)(9686003)(316002)(2906002)(956004)(4326008)(4744005)(186003)(16576012);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?yfnabd3y44vIC7Gp2M8NPR9T4ADlo+?=
	=?utf-8?q?yparlzX6mBac/oBW4P/J8Z4IS2Zwd2E0uGbdB/pqNGmpY1CeOH6L93JJvsIgh2ib2?=
	=?utf-8?q?4egfAwxda/G625emZtBohZ8hejpscNWvMrAxbKmT+O4UNbjkqt5DXUj/vEwYwPs++?=
	=?utf-8?q?SOSy8Z+cxIHdxmg2CuvNDPJM+Fy3RLm9t9YWqYBOLzg8CoMr14ZjuzH7g+IxeN8D+?=
	=?utf-8?q?xOJL0UWU6VhcIZe4ZgIndI4Or7u8yuBnFmTJmoEh0NltE48iyAlck4t7KQELYvf9I?=
	=?utf-8?q?6OX3Z8nLiU4P+WQNwziShJWchR5ihQYO2MFSjG97Th6rocSwp63hKRWiTIl1ck7EK?=
	=?utf-8?q?4BlDu3KeCrdWll5KEaGYLY5v6Ue7b5Y5lOU/BaKDzD2j0dhoXzWTE2EYyTW3/D3J+?=
	=?utf-8?q?wsw1abYIIbIs9nuoOQUz2PJjsfYvz2JjLnkBd67OEVZC7XWAaA9/XXQ+wksp+DWCV?=
	=?utf-8?q?8xinv8KWF18c5MAbgLN+8j/L53aMaI5P5i0FL53RsVLV6N57asgT8eJrcs1SK6N17?=
	=?utf-8?q?QBWbiFjNTCAllpJvl2D4hA6YxTMYC36KhhgGGC0TWGQ6r/x4SyXFkfbo6joZLSESg?=
	=?utf-8?q?J53hQXnK/2Os1K9nflt02eVc3t7HwUURp4iM1PIzKXfIAaWZWFtkDL6igwqJXwPls?=
	=?utf-8?q?eJgnfYecvjnZjfyBAlBR9jignKKWjce0LAZBMF9PCLBkbPsWtZwy2vVRrk7zVEyY3?=
	=?utf-8?q?fgUx8xwf+9UN08oWhr29/5n9z3sDwDswrU3LNRhYoeSHPH0nBxkvf1sbLNvXH5dFN?=
	=?utf-8?q?9n8/npm7MHdFhgvzhpNlLP34sCu4lQf1LcO9l9apChZqmbV4VBD/wrBgaqvVpKC+N?=
	=?utf-8?q?J3rloWzv85Dpx25P0HpcYlp7p7HXzKKXl4nOz90QOBrXWjmdTpEPt6LqZjFgxW1D1?=
	=?utf-8?q?J1g02Zof2djhii+S5GbEIbHivNv1WKjZxNqXZAgmVINhqXpKLCD+B99xwCaD3nXgI?=
	=?utf-8?q?n6yld36zWYku9k7rla7?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Dec 2020 22:37:45.7680
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c59130bc-2708-47ff-c9c7-08d89b00b7d1
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 /GsrYGQ0v/a9LFFjy6s0LZiaF9etV2IqhhDohHxJpHUhR+SH2tx1miMfcnB66Ikt
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2624
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Newer AMD processors have a feature to virtualize the use of
the SPEC_CTRL MSR. The series adds the feature support and
enables the feature on SVM.
---

Babu Moger (2):
      x86/cpufeatures: Add the Virtual SPEC_CTRL feature
      KVM: SVM: Add support for Virtual SPEC_CTRL


 arch/x86/include/asm/cpufeatures.h |    1 +
 arch/x86/kvm/svm/svm.c             |   17 ++++++++++++++---
 2 files changed, 15 insertions(+), 3 deletions(-)

--
```
