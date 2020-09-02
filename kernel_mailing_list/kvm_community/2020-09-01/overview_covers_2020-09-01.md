

#### [PATCH v4 0/5] iommu aux-domain APIs extensions
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Tue Sep  1 03:34:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11747321
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74A1614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 03:40:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 66139207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 03:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726510AbgIADkK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 31 Aug 2020 23:40:10 -0400
Received: from mga12.intel.com ([192.55.52.136]:62487 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725987AbgIADkK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 31 Aug 2020 23:40:10 -0400
IronPort-SDR: 
 GAFvU7O0EQRfcymRArsXWKjZP3g/ubMy11GaareUnUBGHphZ15cb+uVGOiEvxOues+4njavCjD
 yqJtbF0abb5w==
X-IronPort-AV: E=McAfee;i="6000,8403,9730"; a="136620916"
X-IronPort-AV: E=Sophos;i="5.76,377,1592895600";
   d="scan'208";a="136620916"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 31 Aug 2020 20:40:09 -0700
IronPort-SDR: 
 xGboYKzvsJlkHn6PaFg2gJdD6Ho9X+J4xWldMcYK4l8ocnu41LSY2oGnWtKaxhn0DKvjOlZD+S
 0KuPivwRFKtQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,377,1592895600";
   d="scan'208";a="325180845"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga004.fm.intel.com with ESMTP; 31 Aug 2020 20:40:06 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v4 0/5] iommu aux-domain APIs extensions
Date: Tue,  1 Sep 2020 11:34:17 +0800
Message-Id: <20200901033422.22249-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to extend the IOMMU aux-domain API set so that it
could be more friendly to vfio/mdev usage. The interactions between
vfio/mdev and iommu during mdev creation and passthr are:

1. Create a group for mdev with iommu_group_alloc();
2. Add the device to the group with

       group = iommu_group_alloc();
       if (IS_ERR(group))
               return PTR_ERR(group);

       ret = iommu_group_add_device(group, &mdev->dev);
       if (!ret)
               dev_info(&mdev->dev, "MDEV: group_id = %d\n",
                        iommu_group_id(group));

3. Allocate an aux-domain with iommu_domain_alloc();
4. Attach the aux-domain to the iommu_group.

       iommu_group_for_each_dev {
               if (iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
                       return iommu_aux_attach_device(domain, iommu_device);
               else
                       return iommu_attach_device(domain, iommu_device);
        }

   where, iommu_device is the aux-domain-capable device. The mdev's in
   the group are all derived from it.

In the whole process, an iommu group was allocated for the mdev and an
iommu domain was attached to the group, but the group->domain leaves
NULL. As the result, iommu_get_domain_for_dev() (or other similar
interfaces) doesn't work anymore.

The iommu_get_domain_for_dev() is a necessary interface for device
drivers that want to support vfio/mdev based aux-domain. For example,

        unsigned long pasid;
        struct iommu_domain *domain;
        struct device *dev = mdev_dev(mdev);
        struct device *iommu_device = vfio_mdev_get_iommu_device(dev);

        domain = iommu_aux_get_domain_for_dev(dev);
        if (!domain)
                return -ENODEV;

        pasid = iommu_aux_get_pasid(domain, iommu_device);
        if (pasid <= 0)
                return -EINVAL;

         /* Program the device context */
         ....

We tried to address this by extending iommu_aux_at(de)tach_device() so that
the users could pass in an optional device pointer (for example vfio/mdev).
(v2 of this series)

https://lore.kernel.org/linux-iommu/20200707013957.23672-1-baolu.lu@linux.intel.com/

But that will cause a lock issue as group->mutex has been applied in
iommu_group_for_each_dev(), but has to be reapplied again in the
iommu_aux_attach_device().

We also tried to implement an equivalent iommu_attch_group() for groups
which includes subdevices derived from a single physical device. (v3 of
this series)

https://lore.kernel.org/linux-iommu/20200714055703.5510-1-baolu.lu@linux.intel.com/

But that's too harsh (requires that all subdevices in an iommu_group
must be derived from a same physical device) and breaks some generic
concept of iommmu_group.

This version continues to address this by introducing some new APIs into
the aux-domain API set according to comments during v3 reviewing period.

/**
 * iommu_attach_subdev_group - attach domain to an iommu_group which
 *                             contains subdevices.
 *
 * @domain: domain
 * @group:  iommu_group which contains subdevices
 * @fn:     callback for each subdevice in the @iommu_group to retrieve the
 *          physical device where the subdevice was created from.
 *
 * Returns 0 on success, or an error value.
 */
int iommu_attach_subdev_group(struct iommu_domain *domain,
                              struct iommu_group *group,
                              iommu_device_lookup_t fn)

/**
 * iommu_detach_subdev_group - detach domain from an iommu_group which
 *                             contains subdevices
 *
 * @domain: domain
 * @group:  iommu_group which contains subdevices
 * @fn:     callback for each subdevice in the @iommu_group to retrieve the
 *          physical device where the subdevice was created from.
 *
 * The domain must have been attached to @group via iommu_attach_subdev_group().
 */
void iommu_detach_subdev_group(struct iommu_domain *domain,
                               struct iommu_group *group,
                               iommu_device_lookup_t fn)

struct iommu_domain *iommu_aux_get_domain_for_dev(struct device *subdev)

This version is evolved according to feedbacks from Robin, Alex and Kevin.
I'm very appreciated to their contributions.

Best regards,
baolu
---
Change log:
 - v1->v2:
   - https://lore.kernel.org/linux-iommu/20200627031532.28046-1-baolu.lu@linux.intel.com/
   - Suggested by Robin.

 - v2->v3:
   - https://lore.kernel.org/linux-iommu/20200707013957.23672-1-baolu.lu@linux.intel.com/
   - Suggested by Alex, Kevin.

 - v3->v4:
   - https://lore.kernel.org/linux-iommu/20200714055703.5510-1-baolu.lu@linux.intel.com/
   - Evolve the aux_attach_group APIs to take an iommu_device lookup
     callback.
   - Add interface to check whether a domain is aux-domain for a device.
   - Return domain only if the domain is aux-domain in
     iommu_aux_get_domain_for_dev().

Lu Baolu (5):
  iommu: Add optional subdev in aux_at(de)tach ops
  iommu: Add iommu_at(de)tach_subdev_group()
  iommu: Add iommu_aux_get_domain_for_dev()
  vfio/type1: Use iommu_aux_at(de)tach_group() APIs
  iommu/vt-d: Add is_aux_domain support

 drivers/iommu/intel/iommu.c     | 135 +++++++++++++++++++--------
 drivers/iommu/iommu.c           | 158 +++++++++++++++++++++++++++++++-
 drivers/vfio/vfio_iommu_type1.c |  43 ++-------
 include/linux/intel-iommu.h     |  17 ++--
 include/linux/iommu.h           |  46 +++++++++-
 5 files changed, 315 insertions(+), 84 deletions(-)
```
#### [kvm-unit-tests PATCH v2 00/10] Add support for generic ELF
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id Bj02x__pdgCY; Tue,  1 Sep 2020 11:51:03 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id F0ECB5141E;
        Tue,  1 Sep 2020 11:51:03 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Tue, 1 Sep
 2020 11:51:03 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Thomas Huth <thuth@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH v2 00/10] Add support for generic ELF
 cross-compiler
Date: Tue, 1 Sep 2020 11:50:46 +0300
Message-ID: <20200901085056.33391-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The series introduces a way to build the tests with generic i686-pc-elf
and x86_64-pc-elf GCC target. It also fixes build on macOS and
introduces a way to specify enhanced getopt. Build instructions for macOS
have been updated to reflect the changes.

Changes since v1:
 - Detect if -Wa,--divide is really needed to avoid compilation failure
   on clang-10 (Thomas)
 - Add Travis CI jobs for x86/osx/TCG and bionic/clang-10 (Thomas)
   (https://travis-ci.com/github/roolebo/kvm-unit-tests/builds/182213034)
 - Added one portable format macro for new code (Thomas)

Roman Bolshakov (10):
  x86: Makefile: Allow division on x86_64-elf binutils
  x86: Replace instruction prefixes with spaces
  x86: Makefile: Fix linkage of realmode on x86_64-elf binutils
  lib: Bundle debugreg.h from the kernel
  lib: x86: Use portable format macros for uint32_t
  configure: Add an option to specify getopt
  README: Update build instructions for macOS
  travis.yml: Add CI for macOS
  travis.yml: Change matrix keyword to jobs
  travis.yml: Add x86 build with clang 10

 .travis.yml            | 55 ++++++++++++++++++++++++++--
 README.macOS.md        | 71 +++++++++++++++++++++++++-----------
 configure              | 25 +++++++++++++
 lib/pci.c              |  2 +-
 lib/x86/asm/debugreg.h | 81 ++++++++++++++++++++++++++++++++++++++++++
 run_tests.sh           |  2 +-
 x86/Makefile.common    |  6 +++-
 x86/asyncpf.c          |  2 +-
 x86/cstart.S           |  4 +--
 x86/cstart64.S         |  4 +--
 x86/emulator.c         | 38 ++++++++++----------
 x86/msr.c              |  3 +-
 x86/s3.c               |  2 +-
 13 files changed, 244 insertions(+), 51 deletions(-)
 create mode 100644 lib/x86/asm/debugreg.h
```
#### [RFC V2 0/9] x86/mmu:Introduce parallel memory virtualization to
##### From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
From: Yulei Zhang <yulei.kernel@gmail.com>

```c
From patchwork Tue Sep  1 11:52:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: yulei zhang <yulei.kernel@gmail.com>
X-Patchwork-Id: 11747991
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 203E2166C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 11:53:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08C8020FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 11:53:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LcSn7KwX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727946AbgIALxK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 07:53:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48848 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727035AbgIALw7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 07:52:59 -0400
Received: from mail-pl1-x643.google.com (mail-pl1-x643.google.com
 [IPv6:2607:f8b0:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 567A1C061244;
        Tue,  1 Sep 2020 04:52:59 -0700 (PDT)
Received: by mail-pl1-x643.google.com with SMTP id y6so422147plt.3;
        Tue, 01 Sep 2020 04:52:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=3rTng8S6klnaXBOW81+9mrDYY1I9NVTRnB9JeoS2jtw=;
        b=LcSn7KwXfafkZ0IC+YHw5KEiNnvCSWevlxP8z2DjXGAba25LnTum8hh367JdOezYo2
         su945SOoKCr6SLGAWrrDZNyxzj733IghhO9OBGKnVDWilTSKf9UeA/49n1Oo32wndh0e
         GJ7d21ncUOh+4vpNZA6vcFw3SLdwlH+juMamv4iR09qEbB8BdDnvj1Zs/H9CiVrKweF6
         Tn9Cyl+HNyOSoA9z4FOJ58sH/1vi4WvxjfCc3i7V99HdXaGiNLfJGKoDASktdRqQV5OG
         AAN1aRnOW51QSqDuUjLeCOZyRc6AgmmLeOookncCLvHomGNlAPvMWpPkRW3Cawv+7FN3
         r8+Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=3rTng8S6klnaXBOW81+9mrDYY1I9NVTRnB9JeoS2jtw=;
        b=s21VMyY7isUOwWoK8PoumextrMy2Po5gnOptFcmGr9dc0HbtCeZaxBESznZHVivRX6
         AgsxArgCTO0YUM27R6D4d3VEpixq4ts7ZnsNs0XTljA30z9RfRnUvxpaNmR/bwN6t1KP
         f8XNIUQCny8swXH2rTsRfpq7ltpDBGOVTfm8VU41+lQWouoqRI0JZgDEv27SeAryN/75
         hGBIPYaYRXHfZbulh68ohXaxT6qMFdf0zO2KUoNrKhCm2rKyYcSbnnkoaZIQiPLDqGs0
         KSRYWiQ2/2Pa8oJElpIQPQrvEFYBfC5KN0PfJinTV+hE+o3U5Y781wUQqQDxWZbCTDfb
         lNcQ==
X-Gm-Message-State: AOAM532lrs6eo0biUJ/RuNmvS+LyPdsHnZdZllVc4ox8w3drYy+HX3Ef
        SArqtLcRGT49Tq/BFD3zxck=
X-Google-Smtp-Source: 
 ABdhPJzajFQFmglNSy1ftQejcM7kY3dMr6o6k6FV5TerWypS4jTtWmLGRJbydsOgb7NrR6ESgRP7UQ==
X-Received: by 2002:a17:90a:ba04:: with SMTP id
 s4mr1280236pjr.3.1598961178901;
        Tue, 01 Sep 2020 04:52:58 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.65])
        by smtp.gmail.com with ESMTPSA id
 h15sm1482498pjf.54.2020.09.01.04.52.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 01 Sep 2020 04:52:58 -0700 (PDT)
From: yulei.kernel@gmail.com
X-Google-Original-From: yuleixzhang@tencent.com
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, jmattson@google.com,
        junaids@google.com, bgardon@google.com, vkuznets@redhat.com,
        xiaoguangrong.eric@gmail.com, kernellwp@gmail.com,
        lihaiwei.kernel@gmail.com, Yulei Zhang <yulei.kernel@gmail.com>
Subject: [RFC V2 0/9] x86/mmu:Introduce parallel memory virtualization to
 boost performance
Date: Tue,  1 Sep 2020 19:52:42 +0800
Message-Id: <cover.1598868203.git.yulei.kernel@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yulei Zhang <yulei.kernel@gmail.com>

Currently in KVM memory virtulization we relay on mmu_lock to
synchronize the memory mapping update, which make vCPUs work
in serialize mode and slow down the execution, especially after
migration to do substantial memory mapping will cause visible
performance drop, and it can get worse if guest has more vCPU
numbers and memories.
  
The idea we present in this patch set is to mitigate the issue
with pre-constructed memory mapping table. We will fast pin the
guest memory to build up a global memory mapping table according
to the guest memslots changes and apply it to cr3, so that after
guest starts up all the vCPUs would be able to update the memory
simultaneously without page fault exception, thus the performance
improvement is expected. 

We use memory dirty pattern workload to test the initial patch
set and get positive result even with huge page enabled. For example,
we create guest with 32 vCPUs and 64G memories, and let the vcpus
dirty the entire memory region concurrently, as the initial patch
eliminate the overhead of mmu_lock, in 2M/1G huge page mode we would
get the job done in about 50% faster.

We only validate this feature on Intel x86 platform. And as Ben
pointed out in RFC V1, so far we disable the SMM for resource
consideration, drop the mmu notification as in this case the
memory is pinned.

V1->V2:
* Rebase the code to kernel version 5.9.0-rc1.

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
 arch/x86/kvm/mmu/mmu.c          | 533 ++++++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c          |   2 +-
 arch/x86/kvm/vmx/vmx.c          |   7 +-
 arch/x86/kvm/x86.c              |  55 ++--
 include/linux/kvm_host.h        |   7 +-
 virt/kvm/kvm_main.c             |  43 ++-
 10 files changed, 639 insertions(+), 60 deletions(-)
```
#### [PATCH v6 0/4] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Tue Sep  1 15:11:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11749293
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A868109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 17:23:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F27320BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 17:23:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732604AbgIARXb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 13:23:31 -0400
Received: from mga07.intel.com ([134.134.136.100]:55890 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726948AbgIAPL7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 11:11:59 -0400
IronPort-SDR: 
 GamCM1ZaRCny8m5MdVcT6lm6QNcx2RoxpADugP4p7Z1F1S4ulhNb5PFJRbo4vbuM8jPc/c/io0
 JPMwmUi4J3DQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9730"; a="221408195"
X-IronPort-AV: E=Sophos;i="5.76,379,1592895600";
   d="scan'208";a="221408195"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Sep 2020 08:11:56 -0700
IronPort-SDR: 
 xhgBk0HRaUHSTp8EmUugDb/xel8Pubh4lnHwAM4BS/F3dn+IA7OphmeXEF58tl5Kj4GovF+QqS
 5i1vgIRy90Xw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,379,1592895600";
   d="scan'208";a="501776229"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.56.69])
  by fmsmga006.fm.intel.com with ESMTP; 01 Sep 2020 08:11:54 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v6 0/4] Add a vhost RPMsg API
Date: Tue,  1 Sep 2020 17:11:49 +0200
Message-Id: <20200901151153.28111-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Next update:

v6:
- rename include/linux/virtio_rpmsg.h -> include/linux/rpmsg/virtio.h

v5:
- don't hard-code message layout

v4:
- add endianness conversions to comply with the VirtIO standard

v3:
- address several checkpatch warnings
- address comments from Mathieu Poirier

v2:
- update patch #5 with a correct vhost_dev_init() prototype
- drop patch #6 - it depends on a different patch, that is currently
  an RFC
- address comments from Pierre-Louis Bossart:
  * remove "default n" from Kconfig

Linux supports RPMsg over VirtIO for "remote processor" / AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits

Thanks
Guennadi

Guennadi Liakhovetski (4):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an RPMsg API

 Documentation/rpmsg.txt          |   6 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 373 +++++++++++++++++++++++++++++++
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++
 include/linux/rpmsg/virtio.h     |  83 +++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 9 files changed, 551 insertions(+), 80 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/rpmsg/virtio.h
```
#### [PATCH v6 0/7] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Tue Sep  1 20:15:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11749425
Return-Path: <SRS0=IPmA=CK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F332618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 20:15:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FE0C2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  1 Sep 2020 20:15:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="EMAd95ar"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729348AbgIAUPg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 1 Sep 2020 16:15:36 -0400
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:23808 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726323AbgIAUPf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 1 Sep 2020 16:15:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1598991335; x=1630527335;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=3EnOz/3Rmff/sgE96/Smy7EzDfB4zcQK8Cuf3LKrUSg=;
  b=EMAd95arIFU/VydIlwl0eQurIUojnyuFqua0ooGUbhsX1dWt8ha8W4Vf
   s2zU4ijBu4ciTkReChgWWx0UpjwwfRr3JQAZ2ugwuo/F4jRhCGSMT0/IC
   RYV688ky/Bx6LwQ3tI9eDGfBl9gq/z2rFQIjM6vPD7sHTKR6KZAOL/09i
   w=;
X-IronPort-AV: E=Sophos;i="5.76,380,1592870400";
   d="scan'208";a="51310818"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2a-22cc717f.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 01 Sep 2020 20:15:32 +0000
Received: from EX13MTAUWC002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-22cc717f.us-west-2.amazon.com (Postfix) with
 ESMTPS id 6E9C7A2028;
        Tue,  1 Sep 2020 20:15:30 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC002.ant.amazon.com (10.43.162.240) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 1 Sep 2020 20:15:28 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.160.229) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 1 Sep 2020 20:15:25 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>,
        Dan Carpenter <dan.carpenter@oracle.com>,
        <kvm@vger.kernel.org>, <linux-doc@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH v6 0/7] Allow user space to restrict and augment MSR emulation
Date: Tue, 1 Sep 2020 22:15:10 +0200
Message-ID: <20200901201517.29086-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.160.229]
X-ClientProxiedBy: EX13D18UWC001.ant.amazon.com (10.43.162.105) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with filtering, user space trapping allows us to emulate
arbitrary MSRs in user space, paving the way for target CPU specific MSR
implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

v3 -> v4:

  - Mention exit reasons in re-enter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
  - lock allow check and clearing
  - free bitmaps on clear

v4 -> v5:

  - use srcu 

v5 -> v6:

  - Switch from allow list to filtering API with explicit fallback option
  - Support and test passthrough MSR filtering
  - Check for filter exit reason
  - Add .gitignore
  - send filter change notification
  - change to atomic set_msr_filter ioctl with fallback flag
  - use EPERM for filter blocks
  - add bit for MSR user space deflection
  - check for overflow of BITS_TO_LONGS (thanks Dan Carpenter!)
  - s/int i;/u32 i;/
  - remove overlap check
  - Introduce exit reason mask to allow for future expansion and filtering
  - s/emul_to_vcpu(ctxt)/vcpu/
  - imported patch: KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs
  - new patch: KVM: x86: Add infrastructure for MSR filtering
  - new patch: KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  - new patch: KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied

Aaron Lewis (1):
  KVM: x86: Prepare MSR bitmaps for userspace tracked MSRs

Alexander Graf (6):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Add infrastructure for MSR filtering
  KVM: x86: SVM: Prevent MSR passthrough when MSR access is denied
  KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied
  KVM: x86: Introduce MSR filtering
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 176 +++++++++-
 arch/x86/include/asm/kvm_host.h               |  18 ++
 arch/x86/include/uapi/asm/kvm.h               |  19 ++
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/svm/svm.c                        | 122 +++++--
 arch/x86/kvm/svm/svm.h                        |   7 +
 arch/x86/kvm/vmx/nested.c                     |   2 +-
 arch/x86/kvm/vmx/vmx.c                        | 303 ++++++++++++------
 arch/x86/kvm/vmx/vmx.h                        |   9 +-
 arch/x86/kvm/x86.c                            | 267 ++++++++++++++-
 arch/x86/kvm/x86.h                            |   1 +
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  17 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 224 +++++++++++++
 16 files changed, 1055 insertions(+), 132 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
