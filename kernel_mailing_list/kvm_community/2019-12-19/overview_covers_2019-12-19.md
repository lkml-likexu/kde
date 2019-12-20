

#### [PATCH v4 0/7] Use 1st-level for IOVA translation
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Thu Dec 19 03:16:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11302595
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0397913B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 03:17:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DDE8421D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 03:17:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726797AbfLSDRe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 22:17:34 -0500
Received: from mga05.intel.com ([192.55.52.43]:29385 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726463AbfLSDRe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 22:17:34 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Dec 2019 19:17:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,330,1571727600";
   d="scan'208";a="222160398"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by fmsmga001.fm.intel.com with ESMTP; 18 Dec 2019 19:17:30 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        Peter Xu <peterx@redhat.com>, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v4 0/7] Use 1st-level for IOVA translation
Date: Thu, 19 Dec 2019 11:16:27 +0800
Message-Id: <20191219031634.15168-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel VT-d in scalable mode supports two types of page tables
for DMA translation: the first level page table and the second
level page table. The first level page table uses the same
format as the CPU page table, while the second level page table
keeps compatible with previous formats. The software is able
to choose any one of them for DMA remapping according to the use
case.

This patchset aims to move IOVA (I/O Virtual Address) translation
to 1st-level page table in scalable mode. This will simplify vIOMMU
(IOMMU simulated by VM hypervisor) design by using the two-stage
translation, a.k.a. nested mode translation.

As Intel VT-d architecture offers caching mode, guest IOVA (GIOVA)
support is currently implemented in a shadow page manner. The device
simulation software, like QEMU, has to figure out GIOVA->GPA mappings
and write them to a shadowed page table, which will be used by the
physical IOMMU. Each time when mappings are created or destroyed in
vIOMMU, the simulation software has to intervene. Hence, the changes
on GIOVA->GPA could be shadowed to host.


     .-----------.
     |  vIOMMU   |
     |-----------|                 .--------------------.
     |           |IOTLB flush trap |        QEMU        |
     .-----------. (map/unmap)     |--------------------|
     |GIOVA->GPA |---------------->|    .------------.  |
     '-----------'                 |    | GIOVA->HPA |  |
     |           |                 |    '------------'  |
     '-----------'                 |                    |
                                   |                    |
                                   '--------------------'
                                                |
            <------------------------------------
            |
            v VFIO/IOMMU API
      .-----------.
      |  pIOMMU   |
      |-----------|
      |           |
      .-----------.
      |GIOVA->HPA |
      '-----------'
      |           |
      '-----------'

In VT-d 3.0, scalable mode is introduced, which offers two-level
translation page tables and nested translation mode. Regards to
GIOVA support, it can be simplified by 1) moving the GIOVA support
over 1st-level page table to store GIOVA->GPA mapping in vIOMMU,
2) binding vIOMMU 1st level page table to the pIOMMU, 3) using pIOMMU
second level for GPA->HPA translation, and 4) enable nested (a.k.a.
dual-stage) translation in host. Compared with current shadow GIOVA
support, the new approach makes the vIOMMU design simpler and more
efficient as we only need to flush the pIOMMU IOTLB and possible
device-IOTLB when an IOVA mapping in vIOMMU is torn down.

     .-----------.
     |  vIOMMU   |
     |-----------|                 .-----------.
     |           |IOTLB flush trap |   QEMU    |
     .-----------.    (unmap)      |-----------|
     |GIOVA->GPA |---------------->|           |
     '-----------'                 '-----------'
     |           |                       |
     '-----------'                       |
           <------------------------------
           |      VFIO/IOMMU          
           |  cache invalidation and  
           | guest gpd bind interfaces
           v
     .-----------.
     |  pIOMMU   |
     |-----------|
     .-----------.
     |GIOVA->GPA |<---First level
     '-----------'
     | GPA->HPA  |<---Scond level
     '-----------'
     '-----------'

This patch applies the first level page table for IOVA translation
unless the DOMAIN_ATTR_NESTING domain attribution has been set.
Setting of this attribution means the second level will be used to
map gPA (guest physical address) to hPA (host physical address), and
the mappings between gVA (guest virtual address) and gPA will be
maintained by the guest with the page table address binding to host's
first level.

Based-on-idea-by: Ashok Raj <ashok.raj@intel.com>
Based-on-idea-by: Kevin Tian <kevin.tian@intel.com>
Based-on-idea-by: Liu Yi L <yi.l.liu@intel.com>
Based-on-idea-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Based-on-idea-by: Sanjay Kumar <sanjay.k.kumar@intel.com>
Based-on-idea-by: Lu Baolu <baolu.lu@linux.intel.com>

Change log:

v3->v4:
 - The previous version was posted here
   https://lkml.org/lkml/2019/12/10/2126
 - Set Execute Disable (bit 63) in first level table entries.
 - Enhance pasid-based iotlb invalidation for both default domain
   and auxiliary domain.
 - Add debugfs file to expose page table internals.

v2->v3:
 - The previous version was posted here
   https://lkml.org/lkml/2019/11/27/1831
 - Accept Jacob's suggestion on merging two page tables.

 v1->v2
 - The first series was posted here
   https://lkml.org/lkml/2019/9/23/297
 - Use per domain page table ops to handle different page tables.
 - Use first level for DMA remapping by default on both bare metal
   and vm guest.
 - Code refine according to code review comments for v1.

Lu Baolu (7):
  iommu/vt-d: Identify domains using first level page table
  iommu/vt-d: Add set domain DOMAIN_ATTR_NESTING attr
  iommu/vt-d: Add PASID_FLAG_FL5LP for first-level pasid setup
  iommu/vt-d: Setup pasid entries for iova over first level
  iommu/vt-d: Flush PASID-based iotlb for iova over first level
  iommu/vt-d: Use iova over first level
  iommu/vt-d: debugfs: Add support to show page table internals

 drivers/iommu/dmar.c                |  41 ++++++
 drivers/iommu/intel-iommu-debugfs.c |  75 +++++++++++
 drivers/iommu/intel-iommu.c         | 201 +++++++++++++++++++++++++---
 drivers/iommu/intel-pasid.c         |   7 +-
 drivers/iommu/intel-pasid.h         |   6 +
 drivers/iommu/intel-svm.c           |   8 +-
 include/linux/intel-iommu.h         |  20 ++-
 7 files changed, 326 insertions(+), 32 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2] Better max VMCS field index test
##### From: Nadav Amit <namit@vmware.com>

```c
From patchwork Thu Dec 19 10:10:04 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11302995
Return-Path: <SRS0=/vIX=2J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADB3413A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 10:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9549824679
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Dec 2019 10:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726698AbfLSKL1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 05:11:27 -0500
Received: from mail-pl1-f180.google.com ([209.85.214.180]:39462 "EHLO
        mail-pl1-f180.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726609AbfLSKL1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 05:11:27 -0500
Received: by mail-pl1-f180.google.com with SMTP id z3so2329763plk.6
        for <kvm@vger.kernel.org>; Thu, 19 Dec 2019 02:11:27 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=eE0ZKkUmOMgOE3HsieJIzrZOQCpkieai9Dy4KqlnxE4=;
        b=VAdUDrev8s3gokd7evm+Rrw/Ljt5WbOs/9k+wBcrCSympctjdj22svJktfNaUjdsxY
         Qyglt6XLwtW1uxzrJHJUGqNIuCqTuYiK+jH94TQcTd+zERtEEwvEULbCQtkKVx71odAb
         7XHdg/sNle+q5pT2nJjdwCaYRL4TyklS5PPSnbaLuDmJOtx46kGQ/aPH6AlEplTVtjrs
         3WTq61QFNwCKn7NvDdn7urwZwASivMFp3As0kYnkRP1rFO+Dey0JIskr+69YXV0Xb8ui
         pF7KZmKcHxTqIexAj2d21ZUoKhYKwJUWydAtM7F6DS94tmF5tWUDKv4YoPICHoSPyyjs
         kXOQ==
X-Gm-Message-State: APjAAAU16MlvWTXl1hc+aKXnA+n/f9jDMbctev5r+T2M+CSvIbGg3jog
        cjq4VexGL+aHfwOGWJvGosU=
X-Google-Smtp-Source: 
 APXvYqxFWZTvy5fi1PA3rBsDH1mPGkKXVDBv66QU4++jHTpv6CIRiXqkXKHCM4oPLjpPdUdAJNWrwA==
X-Received: by 2002:a17:90b:d89:: with SMTP id
 bg9mr8785209pjb.75.1576750286439;
        Thu, 19 Dec 2019 02:11:26 -0800 (PST)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 c184sm7565530pfa.39.2019.12.19.02.11.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 19 Dec 2019 02:11:25 -0800 (PST)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <namit@vmware.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH 0/2] Better max VMCS field index test
Date: Thu, 19 Dec 2019 02:10:04 -0800
Message-Id: <20191219101006.49103-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch improves max VMCS field index search so an exact
comparison would be possible. The second one does some cleanup.

Cc: Jim Mattson <jmattson@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>

Nadav Amit (2):
  x86: vmx: Comprehensive max VMCS field search
  x86: vmx: Remove max_index tracking in check_vmcs_field()

 x86/vmx.c | 50 ++++++++++++++++++++++++++++++++++----------------
 1 file changed, 34 insertions(+), 16 deletions(-)
```
