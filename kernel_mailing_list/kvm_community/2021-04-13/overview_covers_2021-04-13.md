

#### [PATCH v2 0/3] KVM: Properly account for guest CPU time
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Tue Apr 13 07:16:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12199499
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A3FEC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 07:16:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A62D613B6
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 07:16:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237646AbhDMHQl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 03:16:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48432 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237515AbhDMHQj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 03:16:39 -0400
Received: from mail-pf1-x436.google.com (mail-pf1-x436.google.com
 [IPv6:2607:f8b0:4864:20::436])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D816BC061574;
        Tue, 13 Apr 2021 00:16:20 -0700 (PDT)
Received: by mail-pf1-x436.google.com with SMTP id d124so10816539pfa.13;
        Tue, 13 Apr 2021 00:16:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=4jaLokaB9YgYGQd1dte3mGoZJD+miSFwfBYhbyWtFbs=;
        b=jjh64cmhug+f7SLA7mg20jYLt0Z/v2rJIYUWy5rAgV0dkPAb/0h6Mnc2vuWxoX6akK
         99L2qqnphiDmeOHfQtbTxbc/ghnbtvZ89QPfve1Sy+tt8uCcStSSJ3sREiMNyuKgFr0U
         mYGIecSUAqIcqF/0KbgAP8cW0PrdlebHvpFsWlOPD0cBOeLmF7SLV3rumTir5ZE3Pfba
         y+5fMB+Oqd/tFtYbr6yW9uRdd3g7JcTD7Db5WgClMDFGoeO4PVkd3xu5zEB+oQ82xz7c
         CNYiBQEtMIrguncbmpm6UlX/zei6ulwdXJuOCrFuxX9p0SqYCWyJ5OmlQvFgVYZMYlK4
         VNXw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=4jaLokaB9YgYGQd1dte3mGoZJD+miSFwfBYhbyWtFbs=;
        b=PSHwcXDu5sn5u949FCOxjzJUhBRg7p3AmjOCK6K1kLng56O7njWZqBQgTMncX3AR+C
         nmpcEeQwj7OmXL9VOwNyOn0D9ycWDaunhC/ByfV7f/IMrAhkXdKKj1KpIOfTl3e1lk4H
         O1jaUfe6EOuY7DfWuD2RuFnkXKeYog+9XzvVubDEOEuNTgyHZhd7q6Cj1OHozXmR/nH+
         GYr8KvajumloD3xo9H4sy3wukrqizzE2ysVbBZutMC2PuJzfaCEizZ+5A4TwNOZMchXF
         spNGNC/g3jZ7IeQX+rLsrKcOguTYA1vQ8EO3hKJqAjPNdgbPIP0HYfbacOdWGEqOYauV
         66yA==
X-Gm-Message-State: AOAM532rM7syq0udoA5OmpLjTd3xK/Ex6tDcNA4N4CfCtwdJgB/jfBWz
        PV/ywBdA6rdk0x4KkjyJk7+Kj9yVD48=
X-Google-Smtp-Source: 
 ABdhPJxHMv+p+T4Gek6gYXJ37Y4b4Fh/Wylwlnld+vQvNYSEcBNARDog28+6qhAwEYLaLpqhY5RcUw==
X-Received: by 2002:a65:6483:: with SMTP id e3mr31253666pgv.208.1618298180233;
        Tue, 13 Apr 2021 00:16:20 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 i10sm2031088pjm.1.2021.04.13.00.16.17
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 13 Apr 2021 00:16:19 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>
Subject: [PATCH v2 0/3] KVM: Properly account for guest CPU time
Date: Tue, 13 Apr 2021 15:16:06 +0800
Message-Id: <1618298169-3831-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The bugzilla https://bugzilla.kernel.org/show_bug.cgi?id=209831
reported that the guest time remains 0 when running a while true
loop in the guest.

The commit 87fa7f3e98a131 ("x86/kvm: Move context tracking where it
belongs") moves guest_exit_irqoff() close to vmexit breaks the
tick-based time accouting when the ticks that happen after IRQs are
disabled are incorrectly accounted to the host/system time. This is
because we exit the guest state too early.

This patchset splits both context tracking logic and the time accounting 
logic from guest_enter/exit_irqoff(), keep context tracking around the 
actual vmentry/exit code, have the virt time specific helpers which 
can be placed at the proper spots in kvm. In addition, it will not 
break the world outside of x86.

v1 -> v2:
 * split context_tracking from guest_enter/exit_irqoff
 * provide separate vtime accounting functions for consistent
 * place the virt time specific helpers at the proper splot 

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Michael Tokarev <mjt@tls.msk.ru>

Wanpeng Li (3):
  context_tracking: Split guest_enter/exit_irqoff
  context_tracking: Provide separate vtime accounting functions
  x86/kvm: Fix vtime accounting

 arch/x86/kvm/svm/svm.c           |  6 ++-
 arch/x86/kvm/vmx/vmx.c           |  6 ++-
 arch/x86/kvm/x86.c               |  1 +
 include/linux/context_tracking.h | 84 +++++++++++++++++++++++++++++++---------
 4 files changed, 74 insertions(+), 23 deletions(-)
```
#### [PATCH 0/3] vfio/iommu_type1: Implement dirty log tracking based on
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Tue Apr 13 09:14:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12199743
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0BC32C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:15:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEE59610CE
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 09:15:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245420AbhDMJPe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 05:15:34 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:16552 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236940AbhDMJPc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 05:15:32 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FKKcg1F4GzPqlD;
        Tue, 13 Apr 2021 17:12:19 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 13 Apr 2021 17:15:02 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Tian Kevin <kevin.tian@intel.com>
CC: Robin Murphy <robin.murphy@arm.com>, Will Deacon <will@kernel.org>,
        "Joerg Roedel" <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [PATCH 0/3] vfio/iommu_type1: Implement dirty log tracking based on
 IOMMU HWDBM
Date: Tue, 13 Apr 2021 17:14:42 +0800
Message-ID: <20210413091445.7448-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi everyone,

This patch series implement vfio dma dirty log tracking based on IOMMU HWDBM (hardware
dirty bit management, such as SMMU with HTTU or intel IOMMU with SLADE).

This patch series is split from the series[1] that containes both IOMMU part and
VFIO part. Please refer the new IOMMU part[2] to review or test.

Intention:

As we know, vfio live migration is an important and valuable feature, but there
are still many hurdles to solve, including migration of interrupt, device state,
DMA dirty log tracking, and etc.

For now, the only dirty log tracking interface is pinning. It has some drawbacks:
1. Only smart vendor drivers are aware of this.
2. It's coarse-grained, the pinned-scope is generally bigger than what the device actually access.
3. It can't track dirty continuously and precisely, vfio populates all pinned-scope as dirty.
   So it doesn't work well with iteratively dirty log handling.

About this series:

Implement a new dirty log tracking method for vfio based on iommu hwdbm. A new
ioctl operation named VFIO_DIRTY_LOG_MANUAL_CLEAR is added, which can eliminate
some redundant dirty handling of userspace.   
   
Optimizations Todo:

1. We recognized that each smmu_domain (a vfio_container may has several smmu_domain) has its
   own stage1 mapping, and we must scan all these mapping to sync dirty state. We plan to refactor
   smmu_domain to support more than one smmu in one smmu_domain, then these smmus can share a same
   stage1 mapping.
2. We also recognized that scan TTD is a hotspot of performance. Recently, I have implement a
   SW/HW conbined dirty log tracking at MMU side[3], which can effectively solve this problem.
   This idea can be applied to smmu side too.

Thanks,
Keqian

[1] https://lore.kernel.org/linux-iommu/20210310090614.26668-1-zhukeqian1@huawei.com/
[2] https://lore.kernel.org/linux-iommu/20210413085457.25400-1-zhukeqian1@huawei.com/  
[3] https://lore.kernel.org/linux-arm-kernel/20210126124444.27136-1-zhukeqian1@huawei.com/

Kunkun Jiang (3):
  vfio/iommu_type1: Add HWDBM status maintanance
  vfio/iommu_type1: Optimize dirty bitmap population based on iommu
    HWDBM
  vfio/iommu_type1: Add support for manual dirty log clear

 drivers/vfio/vfio_iommu_type1.c | 310 ++++++++++++++++++++++++++++++--
 include/uapi/linux/vfio.h       |  28 ++-
 2 files changed, 326 insertions(+), 12 deletions(-)
```
#### [PATCH RFC 00/22] KVM: x86: hyper-v: Fine-grained access check to
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Apr 13 12:26:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12200373
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 426F0C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:26:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 054786128E
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:26:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1345506AbhDMM1B (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 08:27:01 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49572 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1345497AbhDMM07 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 08:26:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618316799;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gHXO771pHe9zTon0JL2N9C6BipX6JwrG/i20Z7QO1yU=;
        b=CQeuts+YaiwvwmlueAPwBiq3NOwn3k2pN+u+Siui9VxpY28SHpf0FczYsUPYD+sM96Ch7e
        7MTMW4WB6lzDsgFq/ENku9Jb2J7U1grwo2lheBVQnGdm7uw6IO+YW/xNBFLu/XzpFnhnAI
        5hedAtIPq/3+TEcacO5Ysl1E5QBGN6c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-325-XnBuu0xjN3SGTxk9jSZ6cQ-1; Tue, 13 Apr 2021 08:26:36 -0400
X-MC-Unique: XnBuu0xjN3SGTxk9jSZ6cQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 44E488030D0;
        Tue, 13 Apr 2021 12:26:34 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.75])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C3AB660C04;
        Tue, 13 Apr 2021 12:26:31 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Siddharth Chandrasekaran <sidcha@amazon.de>,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org
Subject: [PATCH RFC 00/22] KVM: x86: hyper-v: Fine-grained access check to
 Hyper-V hypercalls and MSRs
Date: Tue, 13 Apr 2021 14:26:08 +0200
Message-Id: <20210413122630.975617-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, all implemented Hyper-V features (MSRs and hypercalls) are
available unconditionally to all Hyper-V enabled guests. This is not
ideal as KVM userspace may decide to provide only a subset of the
currently implemented features to emulate an older Hyper-V version,
to reduce attack surface,... Implement checks against guest visible
CPUIDs for all currently implemented MSRs and hypercalls.

RFC part:
- KVM has KVM_CAP_ENFORCE_PV_FEATURE_CPUID for KVM PV features. Should
 we use it for Hyper-V as well or should we rather add a Hyper-V specific
 CAP (or neither)?

TODO:
- Write a selftest
- Check with various Windows/Hyper-V versions that CPUID feature bits
 are actually respected.

Vitaly Kuznetsov (22):
  asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED definition
  KVM: x86: hyper-v: Cache guest CPUID leaves determining features
    availability
  KVM: x86: hyper-v: Honor HV_MSR_VP_RUNTIME_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_TIME_REF_COUNT_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_HYPERCALL_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_VP_INDEX_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_RESET_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_REFERENCE_TSC_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_SYNIC_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_SYNTIMER_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_APIC_ACCESS_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_ACCESS_FREQUENCY_MSRS privilege bit
  KVM: x86: hyper-v: Honor HV_ACCESS_REENLIGHTENMENT privilege bit
  KVM: x86: hyper-v: Honor HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE
    privilege bit
  KVM: x86: hyper-v: Honor HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE
    privilege bit
  KVM: x86: hyper-v: Honor HV_STIMER_DIRECT_MODE_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_POST_MESSAGES privilege bit
  KVM: x86: hyper-v: Honor HV_SIGNAL_EVENTS privilege bit
  KVM: x86: hyper-v: Honor HV_DEBUGGING privilege bit
  KVM: x86: hyper-v: Honor HV_X64_REMOTE_TLB_FLUSH_RECOMMENDED bit
  KVM: x86: hyper-v: Honor HV_X64_CLUSTER_IPI_RECOMMENDED bit
  KVM: x86: hyper-v: Check access to HVCALL_NOTIFY_LONG_SPIN_WAIT
    hypercall

 arch/x86/include/asm/kvm_host.h   |   8 +
 arch/x86/kvm/hyperv.c             | 305 +++++++++++++++++++++++++++---
 include/asm-generic/hyperv-tlfs.h |   1 +
 3 files changed, 291 insertions(+), 23 deletions(-)
```
#### [RFC PATCH v8 00/19] virtio/vsock: introduce SOCK_SEQPACKET support
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Tue Apr 13 12:39:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12200433
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ED7CCC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:40:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C380C613B3
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 12:40:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240999AbhDMMke (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 08:40:34 -0400
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:16867 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231235AbhDMMkd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 08:40:33 -0400
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 5BF2B521497;
        Tue, 13 Apr 2021 15:40:10 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1618317610;
        bh=8Badrr+Zs986//53YRkb8YE/zvrorB22rYNWiNJ8/c4=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=LlDpXnt8OQ4LSx6wgtbgZdcwhfL4xMIH/jFPnhwqkarqr98JcCxq+2N40wg2JWsSX
         LJhCiUCYkK67dWKFp6DNzQKnbPP4r30JBiCPdQbqFpslSgb2U3D6wQWLrpnnabt2UU
         rBspFXeQd2pebL1/YTeaajN1D+kEUM81InlBKyJxNa0brXvYdxx+ux1gfCl9T07dWw
         6wXWiqVOHNnIomKTvIwudfPU+tzjEwko9+6z9BtMakjkFEw8d0s85r46Uzli2KFHQf
         6aKOTx+aN+cLiaFYli7Nb+0rbKZzxkjz5g2BaM5xR2lsZUToyAQAUgLuYO6qkbnFeU
         cVrulac1i0OUg==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id A2EA25214CB;
        Tue, 13 Apr 2021 15:40:08 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.64.121) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2176.2; Tue, 13
 Apr 2021 15:40:08 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Jorgen Hansen <jhansen@vmware.com>,
        Colin Ian King <colin.king@canonical.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Norbert Slusarek <nslusarek@gmx.net>,
        Alexander Popov <alex.popov@linux.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <arseny.krasnov@kaspersky.com>,
        <oxffffaa@gmail.com>
Subject: [RFC PATCH v8 00/19] virtio/vsock: introduce SOCK_SEQPACKET support
Date: Tue, 13 Apr 2021 15:39:51 +0300
Message-ID: <20210413123954.3396314-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.64.121]
X-ClientProxiedBy: hqmailmbx3.avp.ru (10.64.67.243) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.20, Database issued on: 04/13/2021 12:26:17
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 163057 [Apr 13 2021]
X-KSE-AntiSpam-Info: Version: 5.9.20.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: LuaCore: 442 442 b985cb57763b61d2a20abb585d5d4cc10c315b09
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1;arseniy-pc.avp.ru:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 04/13/2021 12:28:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 13.04.2021 10:53:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/04/13 07:05:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/04/13 03:14:00 #16587160
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset implements support of SOCK_SEQPACKET for virtio
transport.
	As SOCK_SEQPACKET guarantees to save record boundaries, so to
do it, new bit for field 'flags' was added: SEQ_EOR. This bit is
set to 1 in last RW packet of message.
	Now as  packets of one socket are not reordered neither on vsock
nor on vhost transport layers, such bit allows to restore original
message on receiver's side. If user's buffer is smaller than message
length, when all out of size data is dropped.
	Maximum length of datagram is not limited as in stream socket,
because same credit logic is used. Difference with stream socket is
that user is not woken up until whole record is received or error
occurred. Implementation also supports 'MSG_TRUNC' flags.
	Tests also implemented.

	Thanks to stsp2@yandex.ru for encouragements and initial design
recommendations.

 Arseny Krasnov (19):
  af_vsock: update functions for connectible socket
  af_vsock: separate wait data loop
  af_vsock: separate receive data loop
  af_vsock: implement SEQPACKET receive loop
  af_vsock: implement send logic for SEQPACKET
  af_vsock: rest of SEQPACKET support
  af_vsock: update comments for stream sockets
  virtio/vsock: set packet's type in virtio_transport_send_pkt_info()
  virtio/vsock: simplify credit update function API
  virtio/vsock: defines and constants for SEQPACKET
  virtio/vsock: dequeue callback for SOCK_SEQPACKET
  virtio/vsock: add SEQPACKET receive logic
  virtio/vsock: rest of SOCK_SEQPACKET support
  virtio/vsock: enable SEQPACKET for transport
  vhost/vsock: enable SEQPACKET for transport
  vsock/loopback: enable SEQPACKET for transport
  vsock_test: add SOCK_SEQPACKET tests
  virtio/vsock: update trace event for SEQPACKET
  af_vsock: serialize writes to shared socket

 drivers/vhost/vsock.c                        |  31 +-
 include/linux/virtio_vsock.h                 |  11 +
 include/net/af_vsock.h                       |   8 +
 .../events/vsock_virtio_transport_common.h   |   5 +-
 include/uapi/linux/virtio_vsock.h            |   9 +
 net/vmw_vsock/af_vsock.c                     | 470 +++++++++++------
 net/vmw_vsock/virtio_transport.c             |  17 +
 net/vmw_vsock/virtio_transport_common.c      | 167 ++++--
 net/vmw_vsock/vsock_loopback.c               |  12 +
 tools/testing/vsock/util.c                   |  32 +-
 tools/testing/vsock/util.h                   |   3 +
 tools/testing/vsock/vsock_test.c             |  63 +++
 12 files changed, 625 insertions(+), 203 deletions(-)

 v7 -> v8:
 General changelog:
 - whole idea is simplified: channel now considered reliable,
   so SEQ_BEGIN, SEQ_END, 'msg_len' and 'msg_id' were removed.
   Only thing that is used to mark end of message is bit in
   'flags' field of packet header: VIRTIO_VSOCK_SEQ_EOR. Packet
   with such bit set to 1 means, that this is last packet of
   message.

 - POSIX MSG_EOR support is removed, as there is no exact
   description how it works.

 - all changes to 'include/uapi/linux/virtio_vsock.h' moved
   to dedicated patch, as these changes linked with patch to
   spec.

 - patch 'virtio/vsock: SEQPACKET feature bit support' now merged
   to 'virtio/vsock: setup SEQPACKET ops for transport'.

 - patch 'vhost/vsock: SEQPACKET feature bit support' now merged
   to 'vhost/vsock: setup SEQPACKET ops for transport'.

 Per patch changelog:
  see every patch after '---' line.

 v6 -> v7:
 General changelog:
 - virtio transport callback for message length now removed
   from transport. Length of record is returned by dequeue
   callback.

 - function which tries to get message length now returns 0
   when rx queue is empty. Also length of current message in
   progress is set to 0, when message processed or error
   happens.

 - patches for virtio feature bit moved after patches with
   transport ops.

 Per patch changelog:
  see every patch after '---' line.

 v5 -> v6:
 General changelog:
 - virtio transport specific callbacks which send SEQ_BEGIN or
   SEQ_END now hidden inside virtio transport. Only enqueue,
   dequeue and record length callbacks are provided by transport.

 - virtio feature bit for SEQPACKET socket support introduced:
   VIRTIO_VSOCK_F_SEQPACKET.

 - 'msg_cnt' field in 'struct virtio_vsock_seq_hdr' renamed to
   'msg_id' and used as id.

 Per patch changelog:
 - 'af_vsock: separate wait data loop':
    1) Commit message updated.
    2) 'prepare_to_wait()' moved inside while loop(thanks to
      Jorgen Hansen).
    Marked 'Reviewed-by' with 1), but as 2) I removed R-b.

 - 'af_vsock: separate receive data loop': commit message
    updated.
    Marked 'Reviewed-by' with that fix.

 - 'af_vsock: implement SEQPACKET receive loop': style fixes.

 - 'af_vsock: rest of SEQPACKET support':
    1) 'module_put()' added when transport callback check failed.
    2) Now only 'seqpacket_allow()' callback called to check
       support of SEQPACKET by transport.

 - 'af_vsock: update comments for stream sockets': commit message
    updated.
    Marked 'Reviewed-by' with that fix.

 - 'virtio/vsock: set packet's type in send':
    1) Commit message updated.
    2) Parameter 'type' from 'virtio_transport_send_credit_update()'
       also removed in this patch instead of in next.

 - 'virtio/vsock: dequeue callback for SOCK_SEQPACKET': SEQPACKET
    related state wrapped to special struct.

 - 'virtio/vsock: update trace event for SEQPACKET': format strings
    now not broken by new lines.

 v4 -> v5:
 - patches reorganized:
   1) Setting of packet's type in 'virtio_transport_send_pkt_info()'
      is moved to separate patch.
   2) Simplifying of 'virtio_transport_send_credit_update()' is
      moved to separate patch and before main virtio/vsock patches.
 - style problem fixed
 - in 'af_vsock: separate receive data loop' extra 'release_sock()'
   removed
 - added trace event fields for SEQPACKET
 - in 'af_vsock: separate wait data loop':
   1) 'vsock_wait_data()' removed 'goto out;'
   2) Comment for invalid data amount is changed.
 - in 'af_vsock: rest of SEQPACKET support', 'new_transport' pointer
   check is moved after 'try_module_get()'
 - in 'af_vsock: update comments for stream sockets', 'connect-oriented'
   replaced with 'connection-oriented'
 - in 'loopback/vsock: setup SEQPACKET ops for transport',
   'loopback/vsock' replaced with 'vsock/loopback'

 v3 -> v4:
 - SEQPACKET specific metadata moved from packet header to payload
   and called 'virtio_vsock_seq_hdr'
 - record integrity check:
   1) SEQ_END operation was added, which marks end of record.
   2) Both SEQ_BEGIN and SEQ_END carries counter which is incremented
      on every marker send.
 - af_vsock.c: socket operations for STREAM and SEQPACKET call same
   functions instead of having own "gates" differs only by names:
   'vsock_seqpacket/stream_getsockopt()' now replaced with
   'vsock_connectible_getsockopt()'.
 - af_vsock.c: 'seqpacket_dequeue' callback returns error and flag that
   record ready. There is no need to return number of copied bytes,
   because case when record received successfully is checked at virtio
   transport layer, when SEQ_END is processed. Also user doesn't need
   number of copied bytes, because 'recv()' from SEQPACKET could return
   error, length of users's buffer or length of whole record(both are
   known in af_vsock.c).
 - af_vsock.c: both wait loops in af_vsock.c(for data and space) moved
   to separate functions because now both called from several places.
 - af_vsock.c: 'vsock_assign_transport()' checks that 'new_transport'
   pointer is not NULL and returns 'ESOCKTNOSUPPORT' instead of 'ENODEV'
   if failed to use transport.
 - tools/testing/vsock/vsock_test.c: rename tests

 v2 -> v3:
 - patches reorganized: split for prepare and implementation patches
 - local variables are declared in "Reverse Christmas tree" manner
 - virtio_transport_common.c: valid leXX_to_cpu() for vsock header
   fields access
 - af_vsock.c: 'vsock_connectible_*sockopt()' added as shared code
   between stream and seqpacket sockets.
 - af_vsock.c: loops in '__vsock_*_recvmsg()' refactored.
 - af_vsock.c: 'vsock_wait_data()' refactored.

 v1 -> v2:
 - patches reordered: af_vsock.c related changes now before virtio vsock
 - patches reorganized: more small patches, where +/- are not mixed
 - tests for SOCK_SEQPACKET added
 - all commit messages updated
 - af_vsock.c: 'vsock_pre_recv_check()' inlined to
   'vsock_connectible_recvmsg()'
 - af_vsock.c: 'vsock_assign_transport()' returns ENODEV if transport
   was not found
 - virtio_transport_common.c: transport callback for seqpacket dequeue
 - virtio_transport_common.c: simplified
   'virtio_transport_recv_connected()'
 - virtio_transport_common.c: send reset on socket and packet type
			      mismatch.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
```
#### [PATCH v2 0/8] KVM: Scalable memslots implementation
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

```c
From patchwork Tue Apr 13 14:10:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12200741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9644C43461
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:34:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B1F3D613B1
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 14:34:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245643AbhDMOen (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 10:34:43 -0400
Received: from vps-vb.mhejs.net ([37.28.154.113]:49766 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1346492AbhDMOeU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 10:34:20 -0400
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1lWJkB-0003z9-Tp; Tue, 13 Apr 2021 16:10:19 +0200
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/8] KVM: Scalable memslots implementation
Date: Tue, 13 Apr 2021 16:10:06 +0200
Message-Id: <cover.1618322001.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

The current memslot code uses a (reverse) gfn-ordered memslot array
for keeping track of them.
This only allows quick binary search by gfn, quick lookup by hva is
not possible (the implementation has to do a linear scan of the whole
memslot array).

Because the memslot array that is currently in use cannot be modified
every memslot management operation (create, delete, move, change
flags) has to make a copy of the whole array so it has a scratch copy
to work on.

Strictly speaking, however, it is only necessary to make copy of the
memslot that is being modified, copying all the memslots currently
present is just a limitation of the array-based memslot implementation.

Two memslot sets, however, are still needed so the VM continues to run
on the currently active set while the requested operation is being
performed on the second, currently inactive one.

In order to have two memslot sets, but only one copy of the actual
memslots it is necessary to split out the memslot data from the
memslot sets.

The memslots themselves should be also kept independent of each other
so they can be individually added or deleted.

These two memslot sets should normally point to the same set of memslots.
They can, however, be desynchronized when performing a memslot management
operation by replacing the memslot to be modified by its copy.
After the operation is complete, both memslot sets once again point to
the same, common set of memslot data.

This series implements the aforementioned idea.

The new implementation uses two trees to perform quick lookups:
For tracking of gfn an ordinary rbtree is used since memslots cannot
overlap in the guest address space and so this data structure is
sufficient for ensuring that lookups are done quickly.

For tracking of hva, however, an interval tree is needed since they
can overlap between memslots.

ID to memslot mappings are kept in a hash table instead of using a
statically allocated "id_to_index" array.

The "lru slot" mini-cache, that keeps track of the last found-by-gfn
memslot, is still present in the new code.

There was also a desire to make the new structure operate on "pay as
you go" basis, that is, that the user only pays the price of the
memslot count that is actually used, not of the maximum count allowed.

The operation semantics were carefully matched to the original
implementation, the outside-visible behavior should not change.
Only the timing will be different.

Making lookup and memslot management operations O(log(n)) brings some
performance benefits (tested on a Xeon 8167M machine):
509 slots in use:
Test            Before          After           Improvement
Map             0.0232s         0.0223s          4%
Unmap           0.0724s         0.0315s         56%
Unmap 2M        0.00155s        0.000869s       44%
Move active     0.000101s       0.0000792s      22%
Move inactive   0.000108s       0.0000847s      21%
Slot setup      0.0135s         0.00803s        41%

100 slots in use:
Test            Before          After           Improvement
Map             0.0195s         0.0191s         None
Unmap           0.0374s         0.0312s         17%
Unmap 2M        0.000470s       0.000447s        5%
Move active     0.0000956s      0.0000800s      16%
Move inactive   0.000101s       0.0000840s      17%
Slot setup      0.00260s        0.00174s        33%

50 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0190s         None
Unmap           0.0339s         0.0311s          8%
Unmap 2M        0.000399s       0.000395s       None
Move active     0.0000999s      0.0000854s      15%
Move inactive   0.0000992s      0.0000826s      17%
Slot setup      0.00141s        0.000990s       30%

30 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0190s         None
Unmap           0.0325s         0.0310s          5%
Unmap 2M        0.000373s       0.000373s       None
Move active     0.000100s       0.0000865s      14%
Move inactive   0.000106s       0.0000918s      13%
Slot setup      0.000989s       0.000775s       22%

10 slots in use:
Test            Before          After           Improvement
Map             0.0192s         0.0186s          3%
Unmap           0.0313s         0.0310s         None
Unmap 2M        0.000348s       0.000351s       None
Move active     0.000110s       0.0000948s      14%
Move inactive   0.000111s       0.0000933s      16%
Slot setup      0.000342s       0.000283s       17%

32k slots in use:
Test            Before          After           Improvement
Map (8194)       0.200s         0.0541s         73%
Unmap            3.88s          0.0351s         99%
Unmap 2M         3.88s          0.0348s         99%
Move active      0.00142s       0.0000786s      94%
Move inactive    0.00148s       0.0000880s      94%
Slot setup      16.1s           0.59s           96%

Since the map test can be done with up to 8194 slots, the result above
for this test was obtained running it with that maximum number of
slots.

In both the old and new memslot code case the measurements were done
against the new KVM selftest framework, with TDP MMU disabled
(that is, with the default setting).

On x86-64 the code was well tested, passed KVM unit tests and KVM
selftests with KASAN on.
And, of course, booted various guests successfully (including nested
ones with TDP MMU enabled).
On other KVM platforms the code was compile-tested only.

Changes since v1:
* Drop the already merged HVA handler retpoline-friendliness patch,

* Split the scalable memslots patch into 8 smaller ones,

* Rebase onto the current kvm/queue,

* Make sure that ranges at both memslot's hva_nodes are always
initialized,

* Remove kvm_mmu_calculate_default_mmu_pages() prototype, too,
when removing this function,

* Redo benchmarks, measure 32k memslots on the old implementation, too.

 arch/arm64/kvm/Kconfig              |   1 +
 arch/arm64/kvm/mmu.c                |  20 +-
 arch/mips/kvm/Kconfig               |   1 +
 arch/mips/kvm/mmu.c                 |  12 +-
 arch/powerpc/kvm/Kconfig            |   1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c |  16 +-
 arch/powerpc/kvm/book3s_64_vio.c    |   2 +-
 arch/powerpc/kvm/book3s_64_vio_hv.c |   2 +-
 arch/powerpc/kvm/book3s_hv.c        |   3 +-
 arch/powerpc/kvm/book3s_hv_nested.c |   4 +-
 arch/powerpc/kvm/book3s_hv_uvmem.c  |  14 +-
 arch/powerpc/kvm/book3s_pr.c        |  12 +-
 arch/s390/kvm/Kconfig               |   1 +
 arch/s390/kvm/kvm-s390.c            |  66 +---
 arch/s390/kvm/kvm-s390.h            |  15 +
 arch/s390/kvm/pv.c                  |   4 +-
 arch/x86/include/asm/kvm_host.h     |   2 +-
 arch/x86/kvm/Kconfig                |   1 +
 arch/x86/kvm/mmu/mmu.c              |  78 ++--
 arch/x86/kvm/mmu/tdp_mmu.c          |  15 +-
 arch/x86/kvm/x86.c                  |  18 +-
 include/linux/kvm_host.h            | 139 ++++---
 virt/kvm/kvm_main.c                 | 592 ++++++++++++++++------------
 23 files changed, 603 insertions(+), 416 deletions(-)
```
#### [RFC PATCH v4 0/4] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Tue Apr 13 18:24:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12201281
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 763F3C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:24:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58058613C3
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:24:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347659AbhDMSYl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 14:24:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:53216 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1347644AbhDMSYj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 13 Apr 2021 14:24:39 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13DI3LJD174939;
        Tue, 13 Apr 2021 14:24:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=Mcj9KNyb1VQD9tj3wCqDsBlIU/svScL3oqGgdcN5QYs=;
 b=FV0T1FHiogE4wPvFv6aB9jN/7LfHl280jSWtYGm8rJ4bOo4i1yBkRFNWM3UqcIyqoUZZ
 XDDnUjCtSAR8lNpldUeD77fBXOLzAbv+J0pJyF/FbeFQ2SVmFRpoYU4C3aDlnRG+7lfQ
 BRDb6LUQs6/ClHBBrJdRg9uiLWmHSRIOdRdbywyc/WwZCLzPgKTxcNHWYSDcI+1REYXk
 YeUc4FQUXtghADv0cfawrPNn5jpuDjM6rimGLOPfADQXsWqNxBznKZTe52h8o85j+0nW
 sgmrYszWrEEBF3NrMo/0AGmF1TQlPz3EjSYP5p465Oa+xVEmSQMLibG6LiCeKvhCAre1 vA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37webguqq9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 14:24:18 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13DI3NZB175114;
        Tue, 13 Apr 2021 14:24:18 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37webguqpm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 14:24:17 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13DIOGTg005743;
        Tue, 13 Apr 2021 18:24:16 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma01fra.de.ibm.com with ESMTP id 37u3n89gq3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 13 Apr 2021 18:24:16 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13DIODPN28180832
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 13 Apr 2021 18:24:13 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DCDCE52052;
        Tue, 13 Apr 2021 18:24:12 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id C922452054;
        Tue, 13 Apr 2021 18:24:12 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 7A553E045F; Tue, 13 Apr 2021 20:24:12 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Matthew Rosato <mjrosato@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v4 0/4] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Tue, 13 Apr 2021 20:24:06 +0200
Message-Id: <20210413182410.1396170-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: aXEvu7h_WgfUNsKDSpLfdw-30kt-u1g-
X-Proofpoint-ORIG-GUID: fTwHtlTHMYvLtGaSkZ7V6KtnAsjAzqI2
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-13_12:2021-04-13,2021-04-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 bulkscore=0 phishscore=0 adultscore=0 mlxlogscore=999
 spamscore=0 priorityscore=1501 mlxscore=0 suspectscore=0 impostorscore=0
 clxscore=1011 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104130122
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Conny, Halil,

Let's restart our discussion about the collision between interrupts for
START SUBCHANNEL and HALT/CLEAR SUBCHANNEL. It's been a quarter million
minutes (give or take), so here is the problematic scenario again:

	CPU 1			CPU 2
 1	CLEAR SUBCHANNEL
 2	fsm_irq()
 3				START SUBCHANNEL
 4	vfio_ccw_sch_io_todo()
 5				fsm_irq()
 6				vfio_ccw_sch_io_todo()

From the channel subsystem's point of view the CLEAR SUBCHANNEL (step 1)
is complete once step 2 is called, as the Interrupt Response Block (IRB)
has been presented and the TEST SUBCHANNEL was driven by the cio layer.
Thus, the START SUBCHANNEL (step 3) is submitted [1] and gets a cc=0 to
indicate the I/O was accepted. However, step 2 stacks the bulk of the
actual work onto a workqueue for when the subchannel lock is NOT held,
and is unqueued at step 4. That code misidentifies the data in the IRB
as being associated with the newly active I/O, and may release memory
that is actively in use by the channel subsystem and/or device. Eww.

In this version...

Patch 1 and 2 are defensive checks. Patch 2 was part of v3 [2], but I
would love a better option here to guard between steps 2 and 4.

Patch 3 is a subset of the removal of the CP_PENDING FSM state in v3.
I've obviously gone away from this idea, but I thought this piece is
still valuable.

Patch 4 collapses the code on the interrupt path so that changes to
the FSM state and the channel_program struct are handled at the same
point, rather than separated by a mutex boundary. Because of the
possibility of a START and HALT/CLEAR running concurrently, it does
not make sense to split them here.

With the above patches, maybe it then makes sense to hold the io_mutex
across the entirety of vfio_ccw_sch_io_todo(). But I'm not completely
sure that would be acceptable.

So... Thoughts?

Thanks,
Eric

Previous versions:
v3: https://lore.kernel.org/kvm/20200616195053.99253-1-farman@linux.ibm.com/
v2: https://lore.kernel.org/kvm/20200513142934.28788-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20200124145455.51181-1-farman@linux.ibm.com/

Footnotes:
[1] Halil correctly asserts that today's QEMU should prohibit this, but I
    still have not looked into why. The above is the sequence that is
    occurring in the kernel, and we shouldn't rely on a well-behaved
    userspace to enforce things for us. It is still on my list for further
    investigation, but it's lower in priority.
[2] https://lore.kernel.org/kvm/20200619134005.512fc54f.cohuck@redhat.com/

Eric Farman (4):
  vfio-ccw: Check initialized flag in cp_init()
  vfio-ccw: Check workqueue before doing START
  vfio-ccw: Reset FSM state to IDLE inside FSM
  vfio-ccw: Reset FSM state to IDLE before io_mutex

 drivers/s390/cio/vfio_ccw_cp.c  | 4 ++++
 drivers/s390/cio/vfio_ccw_drv.c | 7 +++----
 drivers/s390/cio/vfio_ccw_fsm.c | 6 ++++++
 drivers/s390/cio/vfio_ccw_ops.c | 2 --
 4 files changed, 13 insertions(+), 6 deletions(-)
```
#### [RFC PATCH 0/7] KVM: Fix tick-based vtime accounting on x86
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Apr 13 18:29:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12201285
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C1785C433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:29:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B53E613BD
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 18:29:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347759AbhDMSaD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 14:30:03 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55330 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1347755AbhDMSaC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 14:30:02 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6B1F3C061574
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 11:29:41 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id e187so46610yba.15
        for <kvm@vger.kernel.org>; Tue, 13 Apr 2021 11:29:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=p83dQZ0k0Eku5abiiX2RjEKklE9nuw+yn1MAe8TcP90=;
        b=WGEETEvbMvrLyFMBiTAiYONPkYqzwOzAjj5TqcXJb7f2DOKCVBc5SnXYbf095GvieY
         2S2mZpybQt3p9wOmu75YEXGr0NVWpSTWueGJNFKG2gS8/qAJpTmtYFj7h1knDMA7VJV6
         1KNA7k6dWVV6wfmA9mWFl42uxC16zfwR5fBajJsI23DWzHHVJXf33hOfKldQI0HZ/K76
         JXj6Q0o2hqKTx5w6OHqhSk75Ln5rXr4cDgemAHVl08JxiA/N7D+p7l/4xhHqibUQyT1+
         4JHPLjNwNG4OsW0wN6nJoeh139xm5lQI23sDfFXscPbqSyhDQBWRJTj8ImaE5qd2jp86
         rJ3w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=p83dQZ0k0Eku5abiiX2RjEKklE9nuw+yn1MAe8TcP90=;
        b=k0u9+tuUFmzNHUB8QWew1/jvWeBTPkb406ZQG+PDAFK75nXn2B/Suw7OmAKJSDoDh2
         BBNubrZFRRFzQRLX87HqO1QYP7XhZuW8KRbXfpufJxm5b9xedc5itgYJJ1vNhg7nnna7
         Ko0KKho68rsL1GrGMT0ZRgJNHCJgOpsiTcTREa3fXee/jV1lx7sA24O9jqm3X95rlL2P
         lj+lNtQwJltCSZKdwHJVzbWnexkMzsqkLZFlcjiWPczYG9VwjdGmRsHl69NJgQ0UsPZs
         sOiNc1nNAMbFrSE1Rn3sLYdJZliLwXrzSGL7KWOdRB5yrBY1oxmBA7yx7p6zL85kGGqy
         1yPQ==
X-Gm-Message-State: AOAM532GheCvbTmdlea+D0JiYA5tu2QiGrAV5eKIvh3mxP8mydqKSQfn
        eP+Hbmkq4gGcd9J8MPPUFGd5KGdLCHo=
X-Google-Smtp-Source: 
 ABdhPJxBMDkmeyEto5eh42lN8cMHROwXTUtvBnzTEYFcNOkJOkf/rgYS0/lHDysrjGIZzbyEsxmuAMbUxXk=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f031:9c1c:56c7:c3bf])
 (user=seanjc job=sendgmr) by 2002:a5b:7c5:: with SMTP id
 t5mr46632593ybq.190.1618338580729;
 Tue, 13 Apr 2021 11:29:40 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 13 Apr 2021 11:29:26 -0700
Message-Id: <20210413182933.1046389-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [RFC PATCH 0/7] KVM: Fix tick-based vtime accounting on x86
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Michael Tokarev <mjt@tls.msk.ru>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is an alternative to Wanpeng's series[*] to fix tick-based accounting
on x86.  The approach for fixing the bug is identical: defer accounting
until after tick IRQs are handled.  The difference is purely in how the
context tracking and vtime code is refactored in order to give KVM the
hooks it needs to fix the x86 bug.

x86 compile tested only, hence the RFC.  If folks like the direction and
there are no unsolvable issues, I'll cross-compile, properly test on x86,
and post an "official" series.

Sean Christopherson (7):
  sched/vtime: Move guest enter/exit vtime accounting to separate
    helpers
  context_tracking: Move guest enter/exit logic to standalone helpers
  context_tracking: Consolidate guest enter/exit wrappers
  context_tracking: KVM: Move guest enter/exit wrappers to KVM's domain
  KVM: Move vtime accounting of guest exit to separate helper
  KVM: x86: Consolidate guest enter/exit logic to common helpers
  KVM: x86: Defer tick-based accounting 'til after IRQ handling

 arch/x86/kvm/svm/svm.c           |  39 +-----------
 arch/x86/kvm/vmx/vmx.c           |  39 +-----------
 arch/x86/kvm/x86.c               |   8 +++
 arch/x86/kvm/x86.h               |  48 +++++++++++++++
 include/linux/context_tracking.h | 100 ++++++++-----------------------
 include/linux/kvm_host.h         |  50 ++++++++++++++++
 include/linux/vtime.h            |  45 ++++++++++++--
 7 files changed, 175 insertions(+), 154 deletions(-)
```
#### [PATCH v3 0/4] Add support for XMM fast hypercalls
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
From patchwork Tue Apr 13 21:50:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12201475
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1F8CAC433B4
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:51:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01F5A61222
	for <kvm@archiver.kernel.org>; Tue, 13 Apr 2021 21:51:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1348479AbhDMVvz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 13 Apr 2021 17:51:55 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:47320 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230491AbhDMVvy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Apr 2021 17:51:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1618350695; x=1649886695;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=/DkrO2gUg58Vl2JO3PCW7Y+6kEN3IaedAlHDNnqPV3Y=;
  b=dS2kZyNa6iLKFD+SrtXiS00y4NFbyAGB11Pe9IF99kgnuxrSPAWk9E/D
   XNJJluxSWpVmuAr6xjan5J66OF4hEsYMdlr/ZIK77Ra2G+NuvSwG6Wrid
   QIvzsp8MwVCFVR/gxM25Q5hMEbeP+t5YR1lHMthMln51KOznGsDFqKTjx
   Q=;
X-IronPort-AV: E=Sophos;i="5.82,220,1613433600";
   d="scan'208";a="118207171"
Received: from pdx4-co-svc-p1-lb2-vlan2.amazon.com (HELO
 email-inbound-relay-2b-81e76b79.us-west-2.amazon.com) ([10.25.36.210])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 13 Apr 2021 21:51:28 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2b-81e76b79.us-west-2.amazon.com (Postfix) with
 ESMTPS id EE0FEA1BE6;
        Tue, 13 Apr 2021 21:51:25 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.39) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 13 Apr 2021 21:51:16 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>,
        Alexander Graf <graf@amazon.com>,
        Evgeny Iakovlev <eyakovl@amazon.de>,
        Liran Alon <liran@amazon.com>,
        Ioannis Aslanidis <iaslan@amazon.de>,
        <linux-hyperv@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v3 0/4] Add support for XMM fast hypercalls
Date: Tue, 13 Apr 2021 23:50:53 +0200
Message-ID: <cover.1618349671.git.sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.39]
X-ClientProxiedBy: EX13D30UWC002.ant.amazon.com (10.43.162.235) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-V supports the use of XMM registers to perform fast hypercalls.
This allows guests to take advantage of the improved performance of the
fast hypercall interface even though a hypercall may require more than
(the current maximum of) two general purpose registers.

The XMM fast hypercall interface uses an additional six XMM registers
(XMM0 to XMM5) to allow the caller to pass an input parameter block of
up to 112 bytes. Hyper-V can also return data back to the guest in the
remaining XMM registers that are not used by the current hypercall.

Although the Hyper-v TLFS mentions that a guest cannot use this feature
unless the hypervisor advertises support for it, some hypercalls which
we plan on upstreaming in future uses them anyway. This patchset adds
necessary infrastructure for handling input/output via XMM registers and
patches kvm_hv_flush_tlb() to use xmm input arguments.

~ Sid.

v3:
- Remove inline for kvm_hv_hypercall_{read,write}_xmm()
- Fix typo: s/ouput/output/
- Remove sse128_t from kvm_emulate.h
- Reword comment to match TLFS wording
- Move num XMM registers macro to hyperv-tlfs.h
- Stop advertising HV_X64_HYPERCALL_XMM_OUTPUT_AVAILABLE

v2:
- Remove inline for kvm_hv_hypercall_{read,write}_xmm()
- Fix typo: s/ouput/output/
- Remove sse128_t from kvm_emulate.h
- Reword comment to match TLFS wording
- Move num XMM registers macro to hyperv-tlfs.h
- Stop advertising HV_X64_HYPERCALL_XMM_OUTPUT_AVAILABLE

Siddharth Chandrasekaran (4):
  KVM: x86: Move FPU register accessors into fpu.h
  KVM: hyper-v: Collect hypercall params into struct
  KVM: x86: kvm_hv_flush_tlb use inputs from XMM registers
  KVM: hyper-v: Advertise support for fast XMM hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |   9 +-
 arch/x86/kvm/emulate.c             | 137 +++---------------
 arch/x86/kvm/fpu.h                 | 140 ++++++++++++++++++
 arch/x86/kvm/hyperv.c              | 222 +++++++++++++++++++----------
 arch/x86/kvm/kvm_emulate.h         |   3 +-
 5 files changed, 309 insertions(+), 202 deletions(-)
 create mode 100644 arch/x86/kvm/fpu.h
```
