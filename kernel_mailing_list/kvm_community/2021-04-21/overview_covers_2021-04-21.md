

#### [RFC PATCH 0/7] Untrusted device support for virtio
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Apr 21 03:21:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12215327
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4B10FC433ED
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:21:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1B4EB613F2
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:21:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234641AbhDUDWQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 23:22:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:38575 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233927AbhDUDWL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 23:22:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618975296;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=GEfjyJT9pCdQ1S+UliWsNNDLnxg2PWz47J1URl6HOzU=;
        b=eEypCuRSDzs0HwL76gE4p7yCtBCnHwUr2m1t7Wvn7UaH2LXMW9Jr3CNY4a5D92Q+2qQLJv
        09ibMyGY/uabo2HmXmKIwVMH0caipuBLuTnhRcHOT7zDhQtHZaVM+ZlCzjcbIR8luqGY6K
        od6OZZ93fmVu7d9IHk2Keba3vrSRoSw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-174-b2XJ9duBPvGdM2cnsCx9ww-1; Tue, 20 Apr 2021 23:21:33 -0400
X-MC-Unique: b2XJ9duBPvGdM2cnsCx9ww-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 84BEA8189C6;
        Wed, 21 Apr 2021 03:21:31 +0000 (UTC)
Received: from localhost.localdomain (ovpn-13-189.pek2.redhat.com
 [10.72.13.189])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9F6836064B;
        Wed, 21 Apr 2021 03:21:19 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, xieyongji@bytedance.com,
        stefanha@redhat.com, file@sect.tu-berlin.de, ashish.kalra@amd.com,
        martin.radev@aisec.fraunhofer.de, konrad.wilk@oracle.com,
        kvm@vger.kernel.org
Subject: [RFC PATCH 0/7] Untrusted device support for virtio
Date: Wed, 21 Apr 2021 11:21:10 +0800
Message-Id: <20210421032117.5177-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All:

Sometimes, the driver doesn't trust the device. This is usually
happens for the encrtpyed VM or VDUSE[1]. In both cases, technology
like swiotlb is used to prevent the poking/mangling of memory from the
device. But this is not sufficient since current virtio driver may
trust what is stored in the descriptor table (coherent mapping) for
performing the DMA operations like unmap and bounce so the device may
choose to utilize the behaviour of swiotlb to perform attacks[2].

For double insurance, to protect from a malicous device, when DMA API
is used for the device, this series store and use the descriptor
metadata in an auxiliay structure which can not be accessed via
swiotlb instead of the ones in the descriptor table. Actually, we've
almost achieved that through packed virtqueue and we just need to fix
a corner case of handling mapping errors. For split virtqueue we just
follow what's done in the packed.

Note that we don't duplicate descriptor medata for indirect
descriptors since it uses stream mapping which is read only so it's
safe if the metadata of non-indirect descriptors are correct.

The behaivor for non DMA API is kept for minimizing the performance
impact.

Slightly tested with packed on/off, iommu on/of, swiotlb force/off in
the guest.

Please review.

[1] https://lore.kernel.org/netdev/fab615ce-5e13-a3b3-3715-a4203b4ab010@redhat.com/T/
[2] https://yhbt.net/lore/all/c3629a27-3590-1d9f-211b-c0b7be152b32@redhat.com/T/#mc6b6e2343cbeffca68ca7a97e0f473aaa871c95b

Jason Wang (7):
  virtio-ring: maintain next in extra state for packed virtqueue
  virtio_ring: rename vring_desc_extra_packed
  virtio-ring: factor out desc_extra allocation
  virtio_ring: secure handling of mapping errors
  virtio_ring: introduce virtqueue_desc_add_split()
  virtio: use err label in __vring_new_virtqueue()
  virtio-ring: store DMA metadata in desc_extra for split virtqueue

 drivers/virtio/virtio_ring.c | 189 ++++++++++++++++++++++++++---------
 1 file changed, 141 insertions(+), 48 deletions(-)
```
#### [PATCH v6 0/3] CET fix patches for nested guest
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed Apr 21 09:05:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12215693
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3FADC433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 08:53:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7FDE061446
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 08:53:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237735AbhDUIyX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 04:54:23 -0400
Received: from mga17.intel.com ([192.55.52.151]:11339 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234557AbhDUIyW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 04:54:22 -0400
IronPort-SDR: 
 KLuE2zBevnOd0vrZ+lgrpkmWY8L9Nhdeb10vKQJ5ANwkJMOcPjOojexFbfV5xX1bt5RUBVSc0k
 ywEWfLYiGHYA==
X-IronPort-AV: E=McAfee;i="6200,9189,9960"; a="175771760"
X-IronPort-AV: E=Sophos;i="5.82,238,1613462400";
   d="scan'208";a="175771760"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Apr 2021 01:53:50 -0700
IronPort-SDR: 
 76cRHvhblxfD+AD9NGgZ4CHGe+v4RejOAL8RT1pyJhZAgRExpygrpN1xsyowCRFfXzd1Avh46W
 vxZPZeAgseUA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,238,1613462400";
   d="scan'208";a="455253027"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga002.fm.intel.com with ESMTP; 21 Apr 2021 01:53:48 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v6 0/3] CET fix patches for nested guest
Date: Wed, 21 Apr 2021 17:05:49 +0800
Message-Id: <20210421090552.10403-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is to fix a few issues found during patch review and
testing on Linux, also including a patch to explictly disable CET support
in nested guest over Hyper-V(s).

change in v6:
- Add check for nested vm_entry_controls without VM_ENTRY_LOAD_CET_STATE set
  to snapshot L1's CET states for L2.


Yang Weijiang (3):
  KVM: nVMX: Sync L2 guest CET states between L1/L2
  KVM: nVMX: Set X86_CR4_CET in cr4_fixed1_bits if CET IBT is enabled
  KVM: nVMX: Add CET entry/exit load bits to evmcs unsupported list

 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/evmcs.c  |  4 ++--
 arch/x86/kvm/vmx/evmcs.h  |  6 ++++--
 arch/x86/kvm/vmx/nested.c | 31 +++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c    |  1 +
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 6 files changed, 41 insertions(+), 5 deletions(-)
```
#### [PATCH v3 0/7] Hyper-V nested virt enlightenments for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
From patchwork Wed Apr 21 14:06:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12216201
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E72D2C43617
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 14:07:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B9BD361457
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 14:07:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243371AbhDUOHp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 10:07:45 -0400
Received: from linux.microsoft.com ([13.77.154.182]:36978 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243323AbhDUOHi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 10:07:38 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id A031020B8001;
        Wed, 21 Apr 2021 07:07:04 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com A031020B8001
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1619014024;
        bh=Cg5t1YQVX4cxqUdMwABIBhBs50zuYp0RIByfae1cQIs=;
        h=From:To:Cc:Subject:Date:From;
        b=sNmmAB3BcY0o93b9qcSFnOEbwY3ph/E3Kh64eWsqihR8XQP0ycLXgMHqIdofeuiXp
         fxwdd95sbKFEvYMd1dc9Pxf9XxNwOvnVYAHuhnMugcCoj8TmKxZWq9qHje2uznlzrU
         Wwm7Kws0hrjCsyJvQmgpafYqzb/fD2ZDzXKFIH5o=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v3 0/7] Hyper-V nested virt enlightenments for SVM
Date: Wed, 21 Apr 2021 14:06:47 +0000
Message-Id: <cover.1619013347.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series enables the nested virtualization enlightenments for
SVM. This is very similar to the enlightenments for VMX except for the
fact that there is no enlightened VMCS. For SVM, VMCB is already an
architectural in-memory data structure.

The supported enlightenments are:

Enlightened TLB Flush: If this is enabled, ASID invalidations invalidate
only gva -> hpa entries. To flush entries derived from NPT, hyper-v
provided hypercalls (HvFlushGuestPhysicalAddressSpace or
HvFlushGuestPhysicalAddressList) should be used.

Enlightened MSR bitmap(TLFS 16.5.3): "When enabled, L0 hypervisor does
not monitor the MSR bitmaps for changes. Instead, the L1 hypervisor must
invalidate the corresponding clean field after making changes to one of
the MSR bitmaps."

Direct Virtual Flush(TLFS 16.8): The hypervisor exposes hypercalls
(HvFlushVirtualAddressSpace, HvFlushVirtualAddressSpaceEx,
HvFlushVirtualAddressList, and HvFlushVirtualAddressListEx) that allow
operating systems to more efficiently manage the virtual TLB. The L1
hypervisor can choose to allow its guest to use those hypercalls and
delegate the responsibility to handle them to the L0 hypervisor. This
requires the use of a partition assist page."

L2 Windows boot time was measured with and without the patch. Time was
measured from power on to the login screen and was averaged over a
consecutive 5 trials:
  Without the patch: 42 seconds
  With the patch: 29 seconds
---

Changes from v2:
- Refactored the Remote TLB Flush logic into separate hyperv specific
  source files (kvm_onhyperv.[ch]).
- Reverted the VMCB Clean bits macro changes as it is no longer needed.

Changes from v1:
- Move the remote TLB flush related fields from kvm_vcpu_hv and kvm_hv
  to kvm_vcpu_arch and kvm_arch.
- Modify the VMCB clean mask runtime based on whether L1 hypervisor
  is running on Hyper-V or not.
- Detect Hyper-V nested enlightenments based on
  HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS.
- Address other minor review comments.
---

Vineeth Pillai (7):
  hyperv: Detect Nested virtualization support for SVM
  hyperv: SVM enlightened TLB flush support flag
  KVM: x86: hyper-v: Move the remote TLB flush logic out of vmx
  KVM: SVM: hyper-v: Nested enlightenments in VMCB
  KVM: SVM: hyper-v: Remote TLB flush for SVM
  KVM: SVM: hyper-v: Enlightened MSR-Bitmap support
  KVM: SVM: hyper-v: Direct Virtual Flush support

 arch/x86/include/asm/hyperv-tlfs.h |   9 +++
 arch/x86/include/asm/kvm_host.h    |  14 ++++
 arch/x86/include/asm/svm.h         |  24 +++++-
 arch/x86/kernel/cpu/mshyperv.c     |  10 ++-
 arch/x86/kvm/Makefile              |   5 ++
 arch/x86/kvm/kvm_onhyperv.c        |  94 ++++++++++++++++++++++
 arch/x86/kvm/kvm_onhyperv.h        |  31 ++++++++
 arch/x86/kvm/svm/svm.c             | 121 +++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.h             |  12 ++-
 arch/x86/kvm/vmx/vmx.c             |  97 ++---------------------
 arch/x86/kvm/vmx/vmx.h             |  10 ---
 arch/x86/kvm/x86.c                 |   8 ++
 12 files changed, 330 insertions(+), 105 deletions(-)
 create mode 100644 arch/x86/kvm/kvm_onhyperv.c
 create mode 100644 arch/x86/kvm/kvm_onhyperv.h
```
#### [RFC PATCH 0/2] Mitigating Excessive Pause-Loop Exiting in
##### From: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>

```c
From patchwork Wed Apr 21 15:08:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
X-Patchwork-Id: 12216353
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49922C433ED
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 15:10:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0DF6461457
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 15:10:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243852AbhDUPKp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 11:10:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38236 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243950AbhDUPJO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 11:09:14 -0400
Received: from mail-pf1-x42a.google.com (mail-pf1-x42a.google.com
 [IPv6:2607:f8b0:4864:20::42a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 891AEC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 08:08:39 -0700 (PDT)
Received: by mail-pf1-x42a.google.com with SMTP id c17so29123715pfn.6
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 08:08:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=sslab.ics.keio.ac.jp; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=6tJWCygQYXpyjmta5WwDxPI/i/SiGWVTOjHzOmEYKlE=;
        b=C1PVVj6GicJZ2pct0tdsal9RHi3mTrSgwF8Perq6B7IXO9c6YWeePyMrncWjx9dX5c
         4wbHBbiVh9evi6zxlz+viHBjFYkU/JgnXxXMGXTCKx2V8pb3vawpkwRCVALFs8jiBRDJ
         rSffYnzLVqokcFKXrrza+WO2+Q15zJ+Ylckh4=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=6tJWCygQYXpyjmta5WwDxPI/i/SiGWVTOjHzOmEYKlE=;
        b=D8/GIzyUtsQjqWfhh4jphe7/G+x8BMqNsboCdZ8MJxY2S0xgQT8umhYK6qjo/geNYh
         k5l2itbY8R2IU78PVigXzWaWlbLwVyhEuCuE/va/EKjnTrpfHqtRbKTJC5As8XhbQE0k
         0b/CJwRWVWf0ymaUOyuBf22EnrZNqMMBZLcd2vg68C2xsYBGIbUbNBGLRwTOd2B4hPwi
         d51wqBbvvP4G/HJHI9P5M2VsIm2v9Uxi+y3FS64MJju3DLz46s4bUCWPCDzIgiL8CP0G
         xI4y/nSxr6klHpds+KcoqoFLWcW55ZmI+6rf5+82tcZQxEu0rGNVs4WDBsM6AUS5gXph
         m3GA==
X-Gm-Message-State: AOAM531l/XNRs8Q8RYtQkYxGGTz+WcbOZvA5izX2lPH3LQrkmhJbgOLY
        CO7gtiDhblzxlI2rAOJdJxz/gQ==
X-Google-Smtp-Source: 
 ABdhPJz1WE6GD3g5TmO4Eb0xaKhSpVZkOqP/gqcFkJCrrmxOYw5FpUQvy3ylfWfox/xr2V5sf2Zomg==
X-Received: by 2002:a17:90a:a895:: with SMTP id
 h21mr11920590pjq.13.1619017718934;
        Wed, 21 Apr 2021 08:08:38 -0700 (PDT)
Received: from haraichi.dnlocal (113x36x239x145.ap113.ftth.ucom.ne.jp.
 [113.36.239.145])
        by smtp.googlemail.com with ESMTPSA id
 f3sm5432553pjo.3.2021.04.21.08.08.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 21 Apr 2021 08:08:38 -0700 (PDT)
From: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        David Hildenbrand <david@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pl@sslab.ics.keio.ac.jp,
        kono@sslab.ics.keio.ac.jp,
        Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
Subject: [RFC PATCH 0/2] Mitigating Excessive Pause-Loop Exiting in
 VM-Agnostic KVM
Date: Thu, 22 Apr 2021 00:08:29 +0900
Message-Id: <20210421150831.60133-1-kentaishiguro@sslab.ics.keio.ac.jp>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Dear KVM developers and maintainers,

In our research work presented last week at the VEE 2021 conference [1], we
found out that a lot of continuous Pause-Loop-Exiting (PLE) events occur
due to three problems we have identified: 1) Linux CFS ignores hints from
KVM; 2) IPI receiver vCPUs in user-mode are not boosted; 3) IPI-receiver
that has halted is always a candidate for boost.  We have intoduced two
mitigations against the problems.

To solve problem (1), patch 1 increases the vruntime of yielded vCPU to
pass the check `if (cfs_rq->next && wakeup_preempt_entity(cfs_rq->next,
left) < 1)` in `struct sched_entity * pick_next_entity()` if the cfs_rq's
skip and next are both vCPUs in the same VM. To keep fairness it does not
prioritize the guest VM which causes PLE, however it improves the
performance by eliminating unnecessary PLE. Also we have confirmed
`yield_to_task_fair` is called only from KVM.

To solve problems (2) and (3), patch 2 monitors IPI communication between
vCPUs and leverages the relationship between vCPUs to select boost
candidates.  The "[PATCH] KVM: Boost vCPU candidiate in user mode which is
delivering interrupt" patch
(https://lore.kernel.org/kvm/CANRm+Cy-78UnrkX8nh5WdHut2WW5NU=UL84FRJnUNjsAPK+Uww@mail.gmail.com/T/)
seems to be effective for (2) while it only uses the IPI receiver
information.

Our approach reduces the total number of PLE events by up to 87.6 % in four
8-vCPU VMs in over-subscribed scenario with the Linux kernel 5.6.0. Please
find the patch below.

We would greatly appreciate your valuable feedback on our approach and
patch.

Thank you very much for your consideration
Kenta Ishiguro

[1] Kenta Ishiguro, Naoki Yasuno, Pierre-Louis Aublin, and Kenji Kono.
    "Mitigating excessive vCPU spinning in VM-agnostic KVM".
    In Proceedings of the 17th ACM SIGPLAN/SIGOPS International Conference
    on Virtual Execution Environments (VEE 2021).
    Association for Computing Machinery, New York,
    NY, USA, 139--152.  https://dl.acm.org/doi/abs/10.1145/3453933.3454020

Kenta Ishiguro (2):
  Prevent CFS from ignoring boost requests from KVM
  Boost vCPUs based on IPI-sender and receiver information

 arch/x86/kvm/lapic.c     | 14 ++++++++++++++
 arch/x86/kvm/vmx/vmx.c   |  2 ++
 include/linux/kvm_host.h |  5 +++++
 kernel/sched/fair.c      | 31 +++++++++++++++++++++++++++++++
 virt/kvm/kvm_main.c      | 26 ++++++++++++++++++++++++--
 5 files changed, 76 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/2] KVM: x86: guest interface for SEV live migration
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed Apr 21 17:37:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12216669
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56C33C433ED
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 17:37:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 228256140D
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 17:37:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244768AbhDURh5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 13:37:57 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:38217 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234882AbhDURhz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Apr 2021 13:37:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619026642;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mZ151TioPJVlWCYFd+WMRoWzUWYENr1Mw5ggyRpzHCc=;
        b=LwRJXXownLQMT0O+jrgTGZNc067WoEvvV9qU3Xm0/WfsmUSLbIgy0ldZF0BxjA0Fz6iLYE
        38dg/gi28qSLNWrG/n58RG5l+KU4cP0/v8/occIyURbY33RrfaN34aCrSv3UTvsZ5PlkBn
        qdqWI6rAGrx5XxZgqqFASeV4AQXgfzE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-372-Ty8iWhTANKK8fF6jVl_Z_A-1; Wed, 21 Apr 2021 13:37:20 -0400
X-MC-Unique: Ty8iWhTANKK8fF6jVl_Z_A-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 127F818B9ECA;
        Wed, 21 Apr 2021 17:37:18 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 61E7A1001B2C;
        Wed, 21 Apr 2021 17:37:17 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, srutherford@google.com, joro@8bytes.org,
        brijesh.singh@amd.com, thomas.lendacky@amd.com,
        venu.busireddy@oracle.com
Subject: [PATCH v2 0/2] KVM: x86: guest interface for SEV live migration
Date: Wed, 21 Apr 2021 13:37:14 -0400
Message-Id: <20210421173716.1577745-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a reviewed version of the guest interface (hypercall+MSR)
for SEV live migration.  The differences lie mostly in the API
for userspace.  In particular:

- the CPUID feature is not exposed in KVM_GET_SUPPORTED_CPUID

- the hypercall must be enabled manually with KVM_ENABLE_CAP

- the MSR has sensible behavior if not filtered (reads as zero,
  writes must leave undefined bits as zero or they #GP)

v1->v2: reviewed KVM_CAP_EXIT_HYPERCALL semantics,
	split CPUID bits so that the migration control MSR
	can be used for TDX

Ashish Kalra (1):
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall

Paolo Bonzini (1):
  KVM: x86: add MSR_KVM_MIGRATION_CONTROL

 Documentation/virt/kvm/api.rst        | 19 ++++++++++
 Documentation/virt/kvm/cpuid.rst      |  9 +++++
 Documentation/virt/kvm/hypercalls.rst | 15 ++++++++
 Documentation/virt/kvm/msr.rst        | 10 ++++++
 arch/x86/include/asm/kvm_host.h       |  2 ++
 arch/x86/include/uapi/asm/kvm_para.h  |  5 +++
 arch/x86/kvm/cpuid.c                  |  3 +-
 arch/x86/kvm/x86.c                    | 50 +++++++++++++++++++++++++++
 include/uapi/linux/kvm.h              |  1 +
 include/uapi/linux/kvm_para.h         |  1 +
 10 files changed, 114 insertions(+), 1 deletion(-)
```
