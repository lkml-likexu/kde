

#### [PATCH 0/5] KVM: x86: Handle reserved CR4 bit interception in VMX
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Sep 30 04:16:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11807815
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A5E3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:17:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5320A20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 04:17:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725798AbgI3ERD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 00:17:03 -0400
Received: from mga18.intel.com ([134.134.136.126]:60793 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725306AbgI3ERD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Sep 2020 00:17:03 -0400
IronPort-SDR: 
 yP2s851zwsADPoqTbfxmReqQ3cF3nFVRqxVDbSJ/VzGwIRDIDzsUI9IQ/7SX+rowT2AGgm1ove
 EZ7BPTq45oKg==
X-IronPort-AV: E=McAfee;i="6000,8403,9759"; a="150137442"
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="150137442"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Sep 2020 21:17:02 -0700
IronPort-SDR: 
 lP4CQa/l4bbc0mzz+ZwM7GnfsFmbuqynTTtO0n5TUvHt0elDV/NUxmWFCNaJzCrM49UE0mXyfN
 13vH5TGP9uPQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,321,1596524400";
   d="scan'208";a="415607859"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga001.fm.intel.com with ESMTP; 29 Sep 2020 21:17:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Lai Jiangshan <jiangshanlai@gmail.com>,
        Lai Jiangshan <laijs@linux.alibaba.com>
Subject: [PATCH 0/5] KVM: x86: Handle reserved CR4 bit interception in VMX
Date: Tue, 29 Sep 2020 21:16:54 -0700
Message-Id: <20200930041659.28181-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series stems from Lai's RFC patches to intercept LA57 and let the
guest own FSGSBASE[*].  Discussion and inspection revealed that KVM does
not handle the case where LA57 is supported in hardware but not exposed to
the guest.  This is actually true for all CR4 bits, but LA57 is currently
the only bit that can be reserved and also owned by the guest.  I have
a unit test for this that I'll post separately.

Intercepting LA57 was by far the easiest fix for the immedidate bug, and
is likely the right change in the long term as there's no justification
for letting the guest own LA57.

The middle three patches adjust VMX's CR4 guest/host mask to intercept
reserved bits.  This required reworking CPUID updates to also refresh said
mask at the correct time.

The last past is Lai's, which let's the guest own FSGSBASE.  This depends
on the reserved bit handling being in place.

Ran everything through unit tests, and ran the kernel's FSGSBASE selftests
in a VM.

[*] https://lkml.kernel.org/r/20200928083047.3349-1-jiangshanlai@gmail.com

Lai Jiangshan (2):
  KVM: x86: Intercept LA57 to inject #GP fault when it's reserved
  KVM: x86: Let the guest own CR4.FSGSBASE

Sean Christopherson (3):
  KVM: x86: Invoke vendor's vcpu_after_set_cpuid() after all common
    updates
  KVM: x86: Move call to update_exception_bitmap() into VMX code
  KVM: VMX: Intercept guest reserved CR4 bits to inject #GP fault

 arch/x86/kvm/cpuid.c          |  6 +++---
 arch/x86/kvm/kvm_cache_regs.h |  2 +-
 arch/x86/kvm/vmx/vmx.c        | 18 +++++++++++++-----
 3 files changed, 17 insertions(+), 9 deletions(-)
```
#### [PATCH 0/3 v4] nVMX: Test Selector and Base Address fields of Guest
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Sep 30 21:45:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11810289
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A5555112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:45:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7FA4A20888
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:45:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="XWjC31Ss"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730663AbgI3Vpi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 17:45:38 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:53412 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725814AbgI3Vph (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Sep 2020 17:45:37 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08ULiCPu097607;
        Wed, 30 Sep 2020 21:45:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=46KbTF0OAF22T/oKcyzqNkda115P5bsT1F97NsMzEXg=;
 b=XWjC31SsCOfW3QjIjFlYFxcBzRvJV8/kFHww3XBfRSamz68CNe2i45lot/E7mAvzkMQI
 Q4ur511xSxTnHwaSy0wjPbBrzdaUPA1v0I2x0KFp+MNf/HG9NiXklAe+rH3Xw+FTbmrV
 FfZCx1QtUDJk3/BZ2dbGEntq6PbXZ73ih2hO1gUeruHaZdneNngO23MAydDyvAG60mrA
 Dk+hmSlYrVtnsCoO7LXElK2oeVxWU3Du44LlhBF6NhuRQ1rICR4wZ1vI+se1VgvjSCJM
 3YEPFxAmOkJ3jcwjEJratjPgiGzOIAT02OBX4kJiZIhat0WtdCW7kWLW5/u30CMPYoun IA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 33su5b31xk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 30 Sep 2020 21:45:33 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08ULiulA007327;
        Wed, 30 Sep 2020 21:45:32 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 33uv2g1bca-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 30 Sep 2020 21:45:32 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08ULjWhF005128;
        Wed, 30 Sep 2020 21:45:32 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.230.226)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 30 Sep 2020 14:45:31 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/3 v4] nVMX: Test Selector and Base Address fields of Guest
 Segment registers
Date: Wed, 30 Sep 2020 21:45:13 +0000
Message-Id: <20200930214516.20926-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9760
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 spamscore=0 adultscore=0
 suspectscore=1 malwarescore=0 bulkscore=0 mlxlogscore=877 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009300175
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9760
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=899
 suspectscore=1
 lowpriorityscore=0 spamscore=0 clxscore=1015 mlxscore=0 impostorscore=0
 malwarescore=0 phishscore=0 adultscore=0 bulkscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009300175
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch-series tests the Selector and Base Address fields of the Guest
Segement register according to section "Checks on Guest Segment Registers"
in SDM vol 3C. "Unrestricted guest" VM-execution control is a condition in
testing some parts of the Guest Segement registers.

v3 -> v4:
	In patch# 3's commit message, I have changed the following
		"Signed-off-by: Jim Mattson <jmattson@google.com>"
	to
		"Co-developed-by: Jim Mattson <jmattson@google.com>"


[PATCH 1/3 v4] KVM: nVMX: KVM needs to unset "unrestricted guest"
[PATCH 2/3 v4] nVMX: Test Selector and Base Address fields of Guest Segment
[PATCH 3/3 v4] nVMX: Test vmentry of unrestricted (unpaged protected) nested

 arch/x86/kvm/vmx/nested.c |  3 +++
 arch/x86/kvm/vmx/vmx.c    | 17 +++++++++--------
 arch/x86/kvm/vmx/vmx.h    |  7 +++++++
 3 files changed, 19 insertions(+), 8 deletions(-)

Krish Sadhukhan (1):
      KVM: nVMX: KVM needs to unset "unrestricted guest" VM-execution control in vmcs02 if vmcs12 doesn't set it

 lib/x86/processor.h |   1 +
 x86/vmx_tests.c     | 200 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 201 insertions(+)

Krish Sadhukhan (1):
      nVMX: Test Selector and Base Address fields of Guest Segment Registers on vmentry of nested guests

 x86/vmx.c       |  2 +-
 x86/vmx.h       |  1 +
 x86/vmx_tests.c | 48 ++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 50 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nVMX: Test vmentry of unrestricted (unpaged protected) nested guest
```
#### [PATCH v12 00/13] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Wed Sep 30 21:49:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11810297
Return-Path: <SRS0=sA+7=DH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B1FE112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:50:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3505420BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Sep 2020 21:50:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hX90Ip4B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731034AbgI3Vt6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 17:49:58 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51667 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730984AbgI3Vt5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 30 Sep 2020 17:49:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601502595;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ulKW+S9BEW8uFmibk0rcRoVyWzzEUBD0nc62HGhPA+o=;
        b=hX90Ip4BMNkZDjya38mp41wJu+zznj58EKjzj51Z9+AE62eIhLNUNJx5rxaQI+bXAq/vfK
        nv9ySpxJWO7TXotEK9ZpW047YEXVZo/B2ULSad+bqlFkzNjc8ZxAcC04zEZLR3OH40LOzr
        29FdB1omMsTf361NyL/IJblqCXl+XG4=
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-68-YVDWb-lfNCuANkrfYdjVww-1; Wed, 30 Sep 2020 17:49:51 -0400
X-MC-Unique: YVDWb-lfNCuANkrfYdjVww-1
Received: by mail-qt1-f200.google.com with SMTP id u6so2197254qte.8
        for <kvm@vger.kernel.org>; Wed, 30 Sep 2020 14:49:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ulKW+S9BEW8uFmibk0rcRoVyWzzEUBD0nc62HGhPA+o=;
        b=kqhoODFmvbFWojlyq1W5OLvhul/xj8t8ERtF5I9M2I461F/Hsmj/FN2H/XOpmnUXC4
         Vk1/ey3zTgdjXYYDc226zwez38uL/PV8ECEw7KJASiFDVcFasVKKMNTAVMqeLNORGKvi
         T2NSs0m7bTXwteGkaM7Fp+eo8f6TbP3JpgCFFO261dZnCtxYgIbi7TnKeOMc4xmPzdLO
         iUaA+IJMlrUv8l3U1tD96u0MY+j9cHmFMoT2LZdJ204nA17i75Itb4e0xZDz+p4+0Wbn
         p30wOtvYbBgFdNv7MgSWskwjQbS7AuUQpazo7Gtrp3CTnosqIQ+NwLPaIiia9L5Cjsxp
         FI5A==
X-Gm-Message-State: AOAM531Hlb1UVkmcF5wiwiH6BsQt1VsiVWr0iUvNrYFhyHTISoE9Woy3
        9z8zySCMxPZVjnFYjYxabikXEwpXJgMQOdD1jAQT/vXDN4Yo6hsv5lOrwKpFPcfhAYcK+hKPn70
        lrOTLESDR1cZB
X-Received: by 2002:a0c:cd0d:: with SMTP id b13mr4741508qvm.53.1601502591013;
        Wed, 30 Sep 2020 14:49:51 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxBXo+o8x2Q2f6w+6rbE35Wt/RIFojSAPK0I96xJJlLe70+VSfSEAdqdBN+HnIYHiBysGWlpA==
X-Received: by 2002:a0c:cd0d:: with SMTP id b13mr4741477qvm.53.1601502590619;
        Wed, 30 Sep 2020 14:49:50 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp130-09-184-147-14-204.dsl.bell.ca. [184.147.14.204])
        by smtp.gmail.com with ESMTPSA id
 j88sm3786165qte.96.2020.09.30.14.49.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 30 Sep 2020 14:49:49 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com,
        Andrew Jones <drjones@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v12 00/13] KVM: Dirty ring interface
Date: Wed, 30 Sep 2020 17:49:35 -0400
Message-Id: <20200930214948.47225-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v12:
- add r-bs for Sean
- rebase

v11:
- rebased to kvm/queue (seems the newest)
- removed kvm_dirty_ring_waitqueue() tracepoint since not used
- set memslot->as_id in kvm_delete_memslot() [Sean]
- let __copy_to_user() always return -EFAULT [Sean]
- rename 'r' in alloc_apic_access_page into 'hva' [Sean]

v10:
- remove unused identity_map_pfn in init_rmode_identity_map [syzbot]
- add "static" to kvm_dirty_ring_full [syzbot]
- kvm_page_in_dirty_ring() use "#if" macros for KVM_DIRTY_LOG_PAGE_OFFSET to
  quiesce syzbot [syzbot]
- s/false/null/ in gfn_to_memslot_dirty_bitmap() [syzbot]

v9:
- patch 3: __x86_set_memory_region: squash another trivial change to return
  (0xdeadull << 48) always for slot removal [Sean]
- pick r-bs for Drew

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com
V8: https://lore.kernel.org/kvm/20200331190000.659614-1-peterx@redhat.com
V9: https://lore.kernel.org/kvm/20200523225659.1027044-1-peterx@redhat.com
V10: https://lore.kernel.org/kvm/20200601115957.1581250-1-peterx@redhat.com/

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (13):
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/svm/avic.c                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  96 ++--
 arch/x86/kvm/x86.c                            |  46 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  63 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  53 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 168 +++++-
 21 files changed, 1408 insertions(+), 135 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
