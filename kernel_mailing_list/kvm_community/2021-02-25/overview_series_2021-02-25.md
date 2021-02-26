#### [PATCH] Documentation: kvm: fix messy conversion from .txt to .rst
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12104149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34AF4C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 13:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB35164F06
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 13:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232634AbhBYNk1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 08:40:27 -0500
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53889 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231881AbhBYNkW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 08:40:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614260336;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=lAJU+Kapx1ZmAfsicjpeIBV3nVtHSrGbB3aXfXZpnYs=;
        b=cgjIF9YvDlqbVObmssjce2iX27ELXCB1SG34Pbt7cbFbdjVUCuPRbyyygVyBz0Vb86o4mF
        IyscW2WqQGgr/dIajMkRaZDZNTpT0hM16aJK1zioV45KjHUhGRGxSywxfM5PtT67KXmJuG
        Q6FSnoikvE6PRmfbXFy8RW5KKs29iZc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-24-MZzIy0qFOxenNFcSu8XFbw-1; Thu, 25 Feb 2021 08:38:52 -0500
X-MC-Unique: MZzIy0qFOxenNFcSu8XFbw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5A4CCCE646;
        Thu, 25 Feb 2021 13:38:51 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A5ED819C48;
        Thu, 25 Feb 2021 13:38:50 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] Documentation: kvm: fix messy conversion from .txt to .rst
Date: Thu, 25 Feb 2021 08:38:50 -0500
Message-Id: <20210225133850.7946-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Building the documentation gives a warning that the KVM_PPC_RESIZE_HPT_PREPARE
label is defined twice.  The root cause is that the KVM_PPC_RESIZE_HPT_PREPARE
API is present twice, the second being a mix of the prepare and commit APIs.
Fix it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/api.rst | 69 ++++++++--------------------------
 1 file changed, 16 insertions(+), 53 deletions(-)

```
#### [GIT PULL] Second batch of KVM changes for Linux 5.12
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12105013
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C8B54C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 21:05:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8747764DA3
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 21:05:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234109AbhBYVEr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 16:04:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:55501 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234927AbhBYVAw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 16:00:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614286759;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zhZABIuY3Pbl4Q8JCgU55Qt/FN0W7Zsvua1ePi1iSNU=;
        b=D4ycHhejTtv+BoKc5OtRelIiQvsBuYRZTnAfVgg4AWI5Bxh7DKfjaPp+O1sM73TMKxLBvj
        p2P1Vw7A1r1/EJFdz2gNnoLF84Yoi8+hHb7/77LFJOWJ39lZqrotfxTIcY4LLiVW9C5Hf+
        1+bJsUW33xN4wimwM7sxiubvsfq9IZ8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-549-j4eOeKVRNtK6n3D8Ldac1Q-1; Thu, 25 Feb 2021 15:59:15 -0500
X-MC-Unique: j4eOeKVRNtK6n3D8Ldac1Q-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8DC7A50741;
        Thu, 25 Feb 2021 20:59:13 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2CF1861F55;
        Thu, 25 Feb 2021 20:59:13 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.12
Date: Thu, 25 Feb 2021 15:59:12 -0500
Message-Id: <20210225205912.61184-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 8c6e67bec3192f16fa624203c8131e10cc4814ba:

  Merge tag 'kvmarm-5.12' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2021-02-12 11:23:44 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 2df8d3807ce7f75bb975f1aeae8fc6757527c62d:

  KVM: SVM: Fix nested VM-Exit on #GP interception handling (2021-02-25 05:13:05 -0500)

----------------------------------------------------------------
x86:
- take into account HVA before retrying on MMU notifier race
- fixes for nested AMD guests without NPT
- allow INVPCID in guest without PCID
- disable PML in hardware when not in use
- MMU code cleanups

----------------------------------------------------------------
David Stevens (1):
      KVM: x86/mmu: Consider the hva in mmu_notifier retry

Ignacio Alvarado (1):
      selftests: kvm: add hardware_disable test

Like Xu (1):
      KVM: vmx/pmu: Fix dummy check if lbr_desc->event is created

Lukas Bulwahn (1):
      KVM: Documentation: rectify rst markup in KVM_GET_SUPPORTED_HV_CPUID

Makarand Sonare (1):
      KVM: VMX: Dynamically enable/disable PML based on memslot dirty logging

Maxim Levitsky (2):
      KVM: VMX: read idt_vectoring_info a bit earlier
      KVM: nSVM: move nested vmrun tracepoint to enter_svm_guest_mode

Paolo Bonzini (4):
      selftests: kvm: avoid uninitialized variable warning
      KVM: nSVM: fix running nested guests when npt=0
      KVM: nVMX: no need to undo inject_page_fault change on nested vmexit
      KVM: nSVM: prepare guest save area while is_guest_mode is true

Sean Christopherson (17):
      KVM: SVM: Intercept INVPCID when it's disabled to inject #UD
      KVM: x86: Advertise INVPCID by default
      KVM: VMX: Allow INVPCID in guest without PCID
      KVM: x86/mmu: Expand collapsible SPTE zap for TDP MMU to ZONE_DEVICE and HugeTLB pages
      KVM: x86/mmu: Split out max mapping level calculation to helper
      KVM: x86/mmu: Pass the memslot to the rmap callbacks
      KVM: x86/mmu: Consult max mapping level when zapping collapsible SPTEs
      KVM: nVMX: Disable PML in hardware when running L2
      KVM: x86/mmu: Expand on the comment in kvm_vcpu_ad_need_write_protect()
      KVM: x86/mmu: Make dirty log size hook (PML) a value, not a function
      KVM: x86: Move MMU's PML logic to common code
      KVM: x86: Further clarify the logic and comments for toggling log dirty
      KVM: x86/mmu: Don't set dirty bits when disabling dirty logging w/ PML
      KVM: x86: Fold "write-protect large" use case into generic write-protect
      KVM: x86/mmu: Remove a variety of unnecessary exports
      KVM: x86/mmu: Skip mmu_notifier check when handling MMIO page fault
      KVM: SVM: Fix nested VM-Exit on #GP interception handling

 Documentation/virt/kvm/api.rst                     |   2 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |   2 +-
 arch/x86/include/asm/kvm-x86-ops.h                 |   6 +-
 arch/x86/include/asm/kvm_host.h                    |  36 +---
 arch/x86/kvm/cpuid.c                               |   2 +-
 arch/x86/kvm/mmu/mmu.c                             | 224 ++++++++-------------
 arch/x86/kvm/mmu/mmu_internal.h                    |   7 +-
 arch/x86/kvm/mmu/paging_tmpl.h                     |  14 +-
 arch/x86/kvm/mmu/tdp_mmu.c                         |  66 +-----
 arch/x86/kvm/mmu/tdp_mmu.h                         |   3 +-
 arch/x86/kvm/svm/nested.c                          |  48 +++--
 arch/x86/kvm/svm/svm.c                             |  22 +-
 arch/x86/kvm/vmx/nested.c                          |  37 ++--
 arch/x86/kvm/vmx/pmu_intel.c                       |   4 +-
 arch/x86/kvm/vmx/vmx.c                             | 112 ++++-------
 arch/x86/kvm/vmx/vmx.h                             |   2 +
 arch/x86/kvm/x86.c                                 | 143 +++++++------
 include/linux/kvm_host.h                           |  25 ++-
 tools/testing/selftests/kvm/.gitignore             |   1 +
 tools/testing/selftests/kvm/Makefile               |   1 +
 .../testing/selftests/kvm/hardware_disable_test.c  | 165 +++++++++++++++
 tools/testing/selftests/kvm/lib/x86_64/processor.c |   3 +-
 virt/kvm/kvm_main.c                                |  29 ++-
 24 files changed, 533 insertions(+), 423 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/hardware_disable_test.c
```
#### [GIT PULL] virtio: features, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12104865
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-25.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 35984C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 19:36:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D87CF64F18
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 19:36:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234349AbhBYTgu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 14:36:50 -0500
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:43066 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234876AbhBYTfK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 14:35:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614281622;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=J8XckA0wuy/u0dP7Chp3yO58HxOiKtqQRaFNCMmqR6E=;
        b=c/7Oyf6DDTlSYqAFhYywOP3Z6B6pWb2uxPWiN474Iv88kQD0zkNb4O4j9b+MGuKwVKHRfl
        tzjnABCtWIMRgSLJkghOBCKe9CjMiXdpwSpgazHUxlDZot+ns8VL8spNYeWCji2oaBgk3D
        i5MiKHdhjGBZrVKGfFAtNHTZP7opjxw=
Received: from mail-ed1-f69.google.com (mail-ed1-f69.google.com
 [209.85.208.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-36-LnQ-OMBAOC2knCZBa-8gBA-1; Thu, 25 Feb 2021 14:33:40 -0500
X-MC-Unique: LnQ-OMBAOC2knCZBa-8gBA-1
Received: by mail-ed1-f69.google.com with SMTP id q2so3351417edt.16
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 11:33:40 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=J8XckA0wuy/u0dP7Chp3yO58HxOiKtqQRaFNCMmqR6E=;
        b=bLYGv2ukSFNjXUsEne7BX95WbaZsuPkU7ZeblL+eUhvkSmIpaFCRFmtMQhR28F0Oj8
         ScclGhvxOioZoNtx5LGpycLHRK/aNN5gN1GjkDfzgfbGhHxy6DzgXWN3ZxFBUwXbRZB/
         scCkqw468ECuibgn0eYmOqhmcz1lgPB3m9udQyLqmeA7LxQ3JmvAk49vBtCsBi8b2iFM
         QvH5N/1ek4IN1mj7AQLgyrBnHB0rH26y9DvSMucRYXHh83DTvT+xuSD+scTfigURiYQd
         nWWis5fkXqCTdj0yDIPiPvk+bqjOwdGkVvzQe8YCODrOEBjra/kps9PED7dIkFMCkEvZ
         +EOg==
X-Gm-Message-State: AOAM530mBjxtBva2bcuF23uhtBEpNHiIpTe/fikYpVOB4+HTSkoQTvda
        QHw9jRzDhY9IWjCMEq0SDQUA6GHrft2bHl40qAfdxexwfZkt55GoT1qs+s6Pgu18rD7814J3Qy6
        e5a1kga73jYKc
X-Received: by 2002:a17:907:2113:: with SMTP id
 qn19mr4214692ejb.98.1614281619062;
        Thu, 25 Feb 2021 11:33:39 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJz2dN9ZzfgwQ9M65gsI//PlQJrl1Zvqctla4lD8bDjF0K4fbGkjn6jK5ahnGYupXSe2W6FPQw==
X-Received: by 2002:a17:907:2113:: with SMTP id
 qn19mr4214672ejb.98.1614281618920;
        Thu, 25 Feb 2021 11:33:38 -0800 (PST)
Received: from redhat.com (212.116.168.114.static.012.net.il.
 [212.116.168.114])
        by smtp.gmail.com with ESMTPSA id
 ca26sm4215205edb.4.2021.02.25.11.33.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 25 Feb 2021 11:33:38 -0800 (PST)
Date: Thu, 25 Feb 2021 14:33:33 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        abaci-bugfix@linux.alibaba.com, abaci@linux.alibaba.com,
        anders.roxell@linaro.org, arnd@arndb.de,
        aruna.ramakrishna@oracle.com, colin.xu@intel.com, david@redhat.com,
        dongli.zhang@oracle.com, edumazet@google.com, elic@nvidia.com,
        gustavoars@kernel.org, jasowang@redhat.com, joe.jin@oracle.com,
        joseph.qi@linux.alibaba.com, linux@roeck-us.net,
        mathias.crombez@faurecia.com, mst@redhat.com,
        naresh.kamboju@linaro.org, parav@nvidia.com, sgarzare@redhat.com,
        stable@vger.kernel.org, syzkaller@googlegroups.com,
        tiantao6@hisilicon.com, vasyl.vavrychuk@opensynergy.com,
        xianting_tian@126.com
Subject: [GIT PULL] virtio: features, fixes
Message-ID: <20210225143333-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are a couple new drivers and support for the new management
interface for mlx under review now. I figured I'll send them separately
if review is done in time, lots of people are waiting for the vdpa tool
patches to I want to make sure they make this release.

The following changes since commit f40ddce88593482919761f74910f42f4b84c004b:

  Linux 5.11 (2021-02-14 14:32:24 -0800)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 16c10bede8b3d8594279752bf53153491f3f944f:

  virtio-input: add multi-touch support (2021-02-23 07:52:59 -0500)

----------------------------------------------------------------
virtio: features, fixes

new vdpa features to allow creation and deletion of new devices
virtio-blk support per-device queue depth
fixes, cleanups all over the place

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Colin Xu (1):
      virtio_input: Prevent EV_MSC/MSC_TIMESTAMP loop storm for MT.

Dongli Zhang (1):
      vhost scsi: alloc vhost_scsi with kvzalloc() to avoid delay

Gustavo A. R. Silva (1):
      virtio_net: Fix fall-through warnings for Clang

Jason Wang (17):
      virtio-pci: do not access iomem via struct virtio_pci_device directly
      virtio-pci: split out modern device
      virtio-pci-modern: factor out modern device initialization logic
      virtio-pci-modern: introduce vp_modern_remove()
      virtio-pci-modern: introduce helper to set config vector
      virtio-pci-modern: introduce helpers for setting and getting status
      virtio-pci-modern: introduce helpers for setting and getting features
      virtio-pci-modern: introduce vp_modern_generation()
      virtio-pci-modern: introduce vp_modern_set_queue_vector()
      virtio-pci-modern: introduce vp_modern_queue_address()
      virtio-pci-modern: introduce helper to set/get queue_enable
      virtio-pci-modern: introduce helper for setting/geting queue size
      virtio-pci-modern: introduce helper for getting queue nums
      virtio-pci-modern: introduce helper to get notification offset
      virito-pci-modern: rename map_capability() to vp_modern_map_capability()
      virtio-pci: introduce modern device module
      virtio_vdpa: don't warn when fail to disable vq

Jiapeng Zhong (1):
      virtio-mem: Assign boolean values to a bool variable

Joseph Qi (1):
      virtio-blk: support per-device queue depth

Mathias Crombez (1):
      virtio-input: add multi-touch support

Parav Pandit (6):
      vdpa_sim_net: Make mac address array static
      vdpa: Extend routine to accept vdpa device name
      vdpa: Define vdpa mgmt device, ops and a netlink interface
      vdpa: Enable a user to add and delete a vdpa device
      vdpa: Enable user to query vdpa device info
      vdpa_sim_net: Add support for user supported devices

Stefano Garzarella (1):
      vdpa/mlx5: fix param validation in mlx5_vdpa_get_config()

Xianting Tian (1):
      virtio_mmio: fix one typo

 drivers/block/virtio_blk.c             |  11 +-
 drivers/net/virtio_net.c               |   1 +
 drivers/vdpa/Kconfig                   |   1 +
 drivers/vdpa/ifcvf/ifcvf_main.c        |   2 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c      |   4 +-
 drivers/vdpa/vdpa.c                    | 503 ++++++++++++++++++++++++++-
 drivers/vdpa/vdpa_sim/vdpa_sim.c       |   3 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.h       |   2 +
 drivers/vdpa/vdpa_sim/vdpa_sim_net.c   | 100 ++++--
 drivers/vhost/scsi.c                   |   9 +-
 drivers/virtio/Kconfig                 |   9 +
 drivers/virtio/Makefile                |   1 +
 drivers/virtio/virtio_input.c          |  26 +-
 drivers/virtio/virtio_mem.c            |   2 +-
 drivers/virtio/virtio_mmio.c           |   2 +-
 drivers/virtio/virtio_pci_common.h     |  22 +-
 drivers/virtio/virtio_pci_modern.c     | 504 ++++-----------------------
 drivers/virtio/virtio_pci_modern_dev.c | 599 +++++++++++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c           |   3 +-
 include/linux/vdpa.h                   |  44 ++-
 include/linux/virtio_pci_modern.h      | 111 ++++++
 include/uapi/linux/vdpa.h              |  40 +++
 22 files changed, 1492 insertions(+), 507 deletions(-)
 create mode 100644 drivers/virtio/virtio_pci_modern_dev.c
 create mode 100644 include/linux/virtio_pci_modern.h
 create mode 100644 include/uapi/linux/vdpa.h
```
#### [PATCH] KVM: nVMX: Set X86_CR4_CET in cr4_fixed1_bits if CET IBT is enabled
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12103147
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 671B1C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:59:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 26F1264ECB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:59:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234375AbhBYC7O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 21:59:14 -0500
Received: from mga17.intel.com ([192.55.52.151]:39413 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229890AbhBYC7N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 21:59:13 -0500
IronPort-SDR: 
 cnVM5gMeFgQeoFJdlesiQYVnMw3atHDLZKCKAaWEmJxRZ3VdhQn5I88Lt8DZhmP5Ml7/NZAx2x
 ZI/LXstzIWbQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9905"; a="165256826"
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="165256826"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Feb 2021 18:58:33 -0800
IronPort-SDR: 
 nbXT/+alB64Yrz7rFyCIDbZg5FuJULDgOI0w8g2h1I7f91PufB54sX+eLH9zYdJpH8CwdbplmG
 /LYbJM0BXPuA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="391903158"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by fmsmga008.fm.intel.com with ESMTP; 24 Feb 2021 18:58:31 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] KVM: nVMX: Set X86_CR4_CET in cr4_fixed1_bits if CET IBT is
 enabled
Date: Thu, 25 Feb 2021 11:09:50 +0800
Message-Id: <20210225030951.17099-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CET SHSTK and IBT are independently controlled by kernel, set X86_CR4_CET
bit in cr4_fixed1_bits if either of them is enabled so that nested guest
can enjoy the feature.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 01/24] KVM: x86/mmu: Set SPTE_AD_WRPROT_ONLY_MASK if and only if PML is enabled
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12104931
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0FE1AC433E9
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 20:49:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAB9D64E28
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 20:49:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233440AbhBYUsr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 15:48:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50410 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232923AbhBYUsl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 15:48:41 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E7A2EC061786
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 12:48:00 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id v62so7552642ybb.15
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 12:48:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=dqqMnpXbv9GtgsoIAfcqn+NffK0Y9luh9hhBXNIAc1w=;
        b=LJrgs6eZBraYVLoHmXIbR/ceJisGaqISWo801gt9OBRf/fqEOrARTU61943OgAt7yN
         uTJEXaSbNbI/J/kZvNqKJ+YbIIkcl99nWfok3tiBtpDuFv0Bo7Qcy3Su+JkCC+kevDJ4
         kI+FNjrBFAWNaXCKT+o3POGGNrXRZm6mSJy+36NZdwIrhD/ftaXw7gMEqSk1JZ+rXoKe
         nzA57bjON7jkDgenv8nutLeRNRzibmkp767w6dtzFVXD07PXspPK9ttwJBRksipLFbok
         RWddPDWAVkSdKPHkgU4SqywGssuRH3AQxtKIjyT8hPEQ82EkXSCaX7nHpv1UmPEEWz6t
         BRog==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=dqqMnpXbv9GtgsoIAfcqn+NffK0Y9luh9hhBXNIAc1w=;
        b=kja+sqnirUmdW6jZbNSPLVBh3zCvCT58JxwlOtAoMxUwDv6fidkfo1ih8SP/ffB8PA
         gQCCyibCOK2Phc/dSYUpECLHT3FVezFARtDMxFzefh5oI6Q1UHsBuc01nmW9dbgKiJAh
         r9qLODDJnQZJzgp0Q2Yxlokl5TzM10q86h75bvf3CVjd8ES5BhnQMryqB9ANIl4rPj3x
         LbrpMzNG4DXq8VPkCXKJIQdvAJZJLuQ8OKrJcomu/GqL9YPE+Kf1lDIyhbyxgCfSUTBx
         H+poPxN+GYEUaWxKp09DE0vLyT0BIK41ZoCNQKi6rgpBw3oWX1huvRJKe6RC16TmBavB
         bxIQ==
X-Gm-Message-State: AOAM533vNf+pVsZiTCUUnr5MUZ/uH9sjc2rLsABvJhA7jwnM544V6Jlr
        f/h+dCOOW3zrTAK4GEN+8FpwYwwcEmM=
X-Google-Smtp-Source: 
 ABdhPJz2moruALIIKXz6XYFjRun2PuAcc2wsLbw3y5G/mYWepR5qnXm0prqWXw9TX9g8mKVJPKdKrN1xgy0=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:34c4:7c1d:f9ba:4576])
 (user=seanjc job=sendgmr) by 2002:a25:74d4:: with SMTP id
 p203mr6436875ybc.75.1614286080185;
 Thu, 25 Feb 2021 12:48:00 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Feb 2021 12:47:26 -0800
In-Reply-To: <20210225204749.1512652-1-seanjc@google.com>
Message-Id: <20210225204749.1512652-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210225204749.1512652-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 01/24] KVM: x86/mmu: Set SPTE_AD_WRPROT_ONLY_MASK if and only
 if PML is enabled
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check that PML is actually enabled before setting the mask to force a
SPTE to be write-protected.  The bits used for the !AD_ENABLED case are
in the upper half of the SPTE.  With 64-bit paging and EPT, these bits
are ignored, but with 32-bit PAE paging they are reserved.  Setting them
for L2 SPTEs without checking PML breaks NPT on 32-bit KVM.

Fixes: 1f4e5fc83a42 ("KVM: x86: fix nested guest live migration with PML")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu_internal.h | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH 1/4] KVM: x86: determine if an exception has an error code only when injecting it.
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12104419
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62875C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 15:43:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2473A64F19
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 15:43:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232081AbhBYPnV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 10:43:21 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:23416 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232203AbhBYPnQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 10:43:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614267709;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=45FSWo+t/kzijJoT0ABe1FplAFBSy0hQPH4KIv9auEg=;
        b=hR9ma4AN4Er6FXZL/w1ulOaJkbUtyC67Xnu0ldJ81AxXuDslVKWsjpIb0Ftpr1BIZVcg1s
        D0965Bp2Zl03/qWgd7leFsRn0HrOwPeiGJbazpjqtcUppC/zqcZhXeAz9vCXZzzjoIcywL
        2xMGg2Hb39/xo8AVjGgJJMV75eMe9RE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-568-J0wYP-EOPeCLEsmUMCiDqA-1; Thu, 25 Feb 2021 10:41:47 -0500
X-MC-Unique: J0wYP-EOPeCLEsmUMCiDqA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 17E0119611A2;
        Thu, 25 Feb 2021 15:41:45 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 766D350DD2;
        Thu, 25 Feb 2021 15:41:41 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/4] KVM: x86: determine if an exception has an error code
 only when injecting it.
Date: Thu, 25 Feb 2021 17:41:32 +0200
Message-Id: <20210225154135.405125-2-mlevitsk@redhat.com>
In-Reply-To: <20210225154135.405125-1-mlevitsk@redhat.com>
References: <20210225154135.405125-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A page fault can be queued while vCPU is in real paged mode on AMD, and
AMD manual asks the user to always intercept it
(otherwise result is undefined).
The resulting VM exit, does have an error code.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 13 +++++++++----
 1 file changed, 9 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v2 1/7] tools include: sync head files of mmap flag encodings about hugetlb
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "wangyanan (Y)" <wangyanan55@huawei.com>
X-Patchwork-Id: 12103329
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6F4C0C433E9
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 06:01:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24F2664F0A
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 06:01:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235398AbhBYGAw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 01:00:52 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:12203 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234928AbhBYGAh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 01:00:37 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DmMWz5DSlzlPwm;
        Thu, 25 Feb 2021 13:57:51 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.498.0; Thu, 25 Feb 2021 13:59:43 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Ingo Molnar <mingo@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        "Yanan Wang" <wangyanan55@huawei.com>
Subject: [RFC PATCH v2 1/7] tools include: sync head files of mmap flag
 encodings about hugetlb
Date: Thu, 25 Feb 2021 13:59:34 +0800
Message-ID: <20210225055940.18748-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210225055940.18748-1-wangyanan55@huawei.com>
References: <20210225055940.18748-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch syncs contents of tools/include/asm-generic/hugetlb_encode.h
and include/uapi/asm-generic/hugetlb_encode.h. Arch powerpc supports 16KB
hugepages and ARM64 supports 32MB/512MB hugepages. The corresponding mmap
flags have already been added in include/uapi/asm-generic/hugetlb_encode.h,
but not tools/include/asm-generic/hugetlb_encode.h.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 tools/include/asm-generic/hugetlb_encode.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] SVM: add two tests for exitintinto on exception
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12104539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 75B43C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 16:13:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2590664F0D
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 16:13:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233236AbhBYQN2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 11:13:28 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21221 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233597AbhBYQLv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Feb 2021 11:11:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614269422;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=PO3qZUTHG4qkGyWUyaGvKkfQcCTQSsXP6qdxfpaxZig=;
        b=YthUdM/r2vkIi3tGZTBTivfVpRq0c4a3mEb3rPcYIvVr1+BxefbwbiC7RoDzFW6xzhRsVx
        2z96in4o6gDhhTBKxOqcTcjm899XzVMT7d7DLVOPY9JchPeuCdq+FesqfmSVfQ22WxetpM
        lao6F9r0/fh97JCiAUfJSPnMYHoAdU4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-537-YVUNemNvO-Sa4qLNXw8vUg-1; Thu, 25 Feb 2021 11:10:17 -0500
X-MC-Unique: YVUNemNvO-Sa4qLNXw8vUg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F3FB9801997
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 16:10:16 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.207.18])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E33621001281;
        Thu, 25 Feb 2021 16:10:13 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] SVM: add two tests for exitintinto on exception
Date: Thu, 25 Feb 2021 18:10:12 +0200
Message-Id: <20210225161012.408860-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test that exitintinfo is set correctly when
exception happens during exception/interrupt delivery
and that exception is intercepted.

Note that those tests currently fail, due to few bugs in KVM.

Also note that those bugs are in KVM's common x86 code,
thus the issue exists on VMX as well and unit tests
that reproduce those on VMX will be written as well.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 x86/svm_tests.c | 162 +++++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 160 insertions(+), 2 deletions(-)

```
#### [PATCH kvmtool v2 01/22] ioport: Remove ioport__setup_arch()
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 12103015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC718C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 01:01:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C51364EC4
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 01:01:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235673AbhBYBBW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 20:01:22 -0500
Received: from foss.arm.com ([217.140.110.172]:58248 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233299AbhBYBBN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 20:01:13 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id AFAF1101E;
        Wed, 24 Feb 2021 17:00:27 -0800 (PST)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 650B13F73B;
        Wed, 24 Feb 2021 17:00:26 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, Marc Zyngier <maz@kernel.org>,
        Sami Mujawar <sami.mujawar@arm.com>
Subject: [PATCH kvmtool v2 01/22] ioport: Remove ioport__setup_arch()
Date: Thu, 25 Feb 2021 00:58:54 +0000
Message-Id: <20210225005915.26423-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.14.1
In-Reply-To: <20210225005915.26423-1-andre.przywara@arm.com>
References: <20210225005915.26423-1-andre.przywara@arm.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since x86 had a special need for registering tons of special I/O ports,
we had an ioport__setup_arch() callback, to allow each architecture
to do the same. As it turns out no one uses it beside x86, so we remove
that unnecessary abstraction.

The generic function was registered via a device_base_init() call, so
we just do the same for the x86 specific function only, and can remove
the unneeded ioport__setup_arch().

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/ioport.c         | 5 -----
 include/kvm/ioport.h | 1 -
 ioport.c             | 6 ------
 mips/kvm.c           | 5 -----
 powerpc/ioport.c     | 6 ------
 x86/ioport.c         | 3 ++-
 6 files changed, 2 insertions(+), 24 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12103149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5B4EDC433E6
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:59:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BCC064ECB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:59:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236889AbhBYC7c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 21:59:32 -0500
Received: from mga04.intel.com ([192.55.52.120]:44499 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229890AbhBYC7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 21:59:30 -0500
IronPort-SDR: 
 Uab9SATr3pXc36iZWtzOiuFSeD50cl354ulp5/odnlq9jMo+gS5LCBr0BJuzHKRc8aTl4XaVQJ
 ZHLlAGFidOxw==
X-IronPort-AV: E=McAfee;i="6000,8403,9905"; a="182927417"
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="182927417"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Feb 2021 18:58:50 -0800
IronPort-SDR: 
 dTxZLk1S0pQhTYmmPtV8Lhr8Q+EBFJnONmS7wvfvfGkDir1ff38dBsfRXQHhTirYjlY2vchLoa
 xmR1PzV4hlLQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="391903195"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by fmsmga008.fm.intel.com with ESMTP; 24 Feb 2021 18:58:48 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v2] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Thu, 25 Feb 2021 11:09:51 +0800
Message-Id: <20210225030951.17099-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210225030951.17099-1-weijiang.yang@intel.com>
References: <20210225030951.17099-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These fields are rarely updated by L1 QEMU/KVM, sync them when L1 is trying to
read/write them and after they're changed. If CET guest entry-load bit is not
set by L1 guest, migrate them to L2 manaully.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>

change in v2:
 - Per Sean's review feedback, change CET guest states as rarely-updated fields.
   And also migrate L1's CET states to L2 if the entry-load bit is not set.
 - Opportunistically removed one blank line.
---
 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/nested.c | 29 +++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 3 files changed, 32 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: Revise guest_fpu xcomp_bv field
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 12103095
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22DA3C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:05:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C596164EC8
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 02:05:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236733AbhBYCFk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 21:05:40 -0500
Received: from mga03.intel.com ([134.134.136.65]:15399 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235527AbhBYCFj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 21:05:39 -0500
IronPort-SDR: 
 0Oq0OtVrfTxkfF8IE/rlKvy9hqtlCEbA9vtNx7aXFAYdB4fnHqk91ArR303xR+InwDMBg7qGu7
 g+74G0/yDuWA==
X-IronPort-AV: E=McAfee;i="6000,8403,9905"; a="185432101"
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="185432101"
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Feb 2021 18:03:53 -0800
IronPort-SDR: 
 deqi13EprK5XusdLMH1m5cIV/y6T78cCGIGj9ILsMn55gwwJD9BTVIlNDTRIAq1RiApkWy4/kt
 rf2uVs4W6Mzw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,203,1610438400";
   d="scan'208";a="367209747"
Received: from vmmteam.bj.intel.com ([10.240.193.86])
  by orsmga006.jf.intel.com with ESMTP; 24 Feb 2021 18:03:50 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: pbonzini@redhat.com, seanjc@google.com
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: x86: Revise guest_fpu xcomp_bv field
Date: Thu, 25 Feb 2021 05:49:54 -0500
Message-Id: <20210225104955.3553-1-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.18.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

XCOMP_BV[63] field indicates that the save area is in the compacted
format and XCOMP_BV[62:0] indicates the states that have space allocated
in the save area, including both XCR0 and XSS bits enabled by the host
kernel. Use xfeatures_mask_all for calculating xcomp_bv and reuse
XCOMP_BV_COMPACTED_FORMAT defined by kernel.

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---
 arch/x86/kvm/x86.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio/type1: fix unmap all on ILP32
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steve Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 12104897
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 672E4C433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 19:57:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E68864F17
	for <kvm@archiver.kernel.org>; Thu, 25 Feb 2021 19:57:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233961AbhBYT45 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 14:56:57 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:44766 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234592AbhBYTzR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 14:55:17 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11PJoGkB141068;
        Thu, 25 Feb 2021 19:54:26 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=VjXJGwSMw8GdU9G0Fstg4nGMaqu6u6fs9lwl/KkMb+U=;
 b=zjNqg/z3eHDEuyaVQBL4wTrpyAghzVjctJ0+fhqoYN28oq33+GORer8uksDj7DFN6r23
 PsEshD8JyOJtp+XiLBz3CKFis5BIrfu4hQC3TfyFeTFMPz52gJzEd6JQpOdLFWNhTEHv
 SepPlAVleLI6r0hSZqdb/kewy17O4QvmOK8DfDUIfYqn7dgFpCuW2rR8xjylNIWaZr6J
 V6rdotgXyYrLldyOh8LhdRaQp/Yyd3bI7rLmaj8qtNnJ2oeBN8P89j8RxswPWBwAlJxL
 cn8Sr5Rvnc4EgquVMNh65Ct+M11JPL54B+aBVVTB7NhFSVWdPlFVL/NKvD0VSxhyYJ2C 5Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 36tsur7rbs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Feb 2021 19:54:25 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11PJoFFp141810;
        Thu, 25 Feb 2021 19:54:24 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 36uc6ux8e7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Feb 2021 19:54:24 +0000
Received: from abhmp0011.oracle.com (abhmp0011.oracle.com [141.146.116.17])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 11PJsNGZ028249;
        Thu, 25 Feb 2021 19:54:23 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 25 Feb 2021 11:54:22 -0800
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH] vfio/type1: fix unmap all on ILP32
Date: Thu, 25 Feb 2021 11:25:02 -0800
Message-Id: <1614281102-230747-1-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-IMR: 1
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9906
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 mlxscore=0 spamscore=0
 mlxlogscore=999 adultscore=0 bulkscore=0 malwarescore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102250150
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9906
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 spamscore=0
 priorityscore=1501 impostorscore=0 bulkscore=0 mlxscore=0 malwarescore=0
 clxscore=1015 phishscore=0 mlxlogscore=999 lowpriorityscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102250150
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some ILP32 architectures support mapping a 32-bit vaddr within a 64-bit
iova space.  The unmap-all code uses 32-bit SIZE_MAX as an upper bound on
the extent of the mappings within iova space, so mappings above 4G cannot
be found and unmapped.  Use U64_MAX instead, and use u64 for size variables.
This also fixes a static analysis bug found by the kernel test robot running
smatch for ILP32.

Fixes: 0f53afa12bae ("vfio/type1: unmap cleanup")
Fixes: c19650995374 ("vfio/type1: implement unmap all")
Reported-by: kernel test robot <lkp@intel.com>
Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Steve Sistare <steven.sistare@oracle.com>
Reviewed-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c | 12 +++++-------
 1 file changed, 5 insertions(+), 7 deletions(-)

```
