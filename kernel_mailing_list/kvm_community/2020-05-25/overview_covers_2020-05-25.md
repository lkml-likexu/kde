

#### [RFC PATCH 0/7] kvm: arm64: Support stage2 hardware DBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Mon May 25 11:23:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11568585
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4E711392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 11:25:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C43552087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 11:25:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390143AbgEYLZI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 07:25:08 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:5279 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2389897AbgEYLZI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 07:25:08 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 5A106A0EB3F34B6CB6FB;
        Mon, 25 May 2020 19:25:04 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.173.221.230) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Mon, 25 May 2020 19:24:54 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <zhengxiang9@huawei.com>,
        Keqian Zhu <zhukeqian1@huawei.com>
Subject: [RFC PATCH 0/7] kvm: arm64: Support stage2 hardware DBM
Date: Mon, 25 May 2020 19:23:59 +0800
Message-ID: <20200525112406.28224-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.221.230]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series add support for stage2 hardware DBM, and it is only
used for dirty log for now.

It works well under some migration test cases, including VM with 4K
pages or 2M THP. I checked the SHA256 hash digest of all memory and
they keep same for source VM and destination VM, which means no dirty
pages is missed under hardware DBM.

However, there are some known issues not solved.

1. Some mechanisms that rely on "write permission fault" become invalid,
   such as kvm_set_pfn_dirty and "mmap page sharing".

   kvm_set_pfn_dirty is called in user_mem_abort when guest issues write
   fault. This guarantees physical page will not be dropped directly when
   host kernel recycle memory. After using hardware dirty management, we
   have no chance to call kvm_set_pfn_dirty.

   For "mmap page sharing" mechanism, host kernel will allocate a new
   physical page when guest writes a page that is shared with other page
   table entries. After using hardware dirty management, we have no chance
   to do this too.

   I need to do some survey on how stage1 hardware DBM solve these problems.
   It helps if anyone can figure it out.

2. Page Table Modification Races: Though I have found and solved some data
   races when kernel changes page table entries, I still doubt that there
   are data races I am not aware of. It's great if anyone can figure them out.

3. Performance: Under Kunpeng 920 platform, for every 64GB memory, KVM
   consumes about 40ms to traverse all PTEs to collect dirty log. It will
   cause unbearable downtime for migration if memory size is too big. I will
   try to solve this problem in Patch v1.

Keqian Zhu (7):
  KVM: arm64: Add some basic functions for hw DBM
  KVM: arm64: Set DBM bit of PTEs if hw DBM enabled
  KVM: arm64: Traverse page table entries when sync dirty log
  KVM: arm64: Steply write protect page table by mask bit
  kvm: arm64: Modify stage2 young mechanism to support hw DBM
  kvm: arm64: Save stage2 PTE dirty info if it is coverred
  KVM: arm64: Enable stage2 hardware DBM

 arch/arm64/include/asm/kvm_host.h     |   1 +
 arch/arm64/include/asm/kvm_mmu.h      |  44 +++++-
 arch/arm64/include/asm/pgtable-prot.h |   1 +
 arch/arm64/include/asm/sysreg.h       |   2 +
 arch/arm64/kvm/reset.c                |   9 +-
 virt/kvm/arm/arm.c                    |   6 +-
 virt/kvm/arm/mmu.c                    | 202 ++++++++++++++++++++++++--
 7 files changed, 246 insertions(+), 19 deletions(-)
```
#### [PATCH v2 00/10] KVM: x86: Interrupt-based mechanism for async_pf
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon May 25 14:41:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11568937
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AF6913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:42:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83B5020888
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:42:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G2bxfNn/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391005AbgEYOll (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 10:41:41 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:45716 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390921AbgEYOlg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 25 May 2020 10:41:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590417694;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=K70tf3jYnNdVjDRvfEDwL8NY4vBMlniBrKknRBAKsXU=;
        b=G2bxfNn/cTATA6nyaUrFhR1ArDMmY0l+N6f/1cDwRbDzvp3zQ9RuUlNgS1sHhYrtwP8Chg
        jbvOmfyfb333bkvwhFzL4xB0PI4LyqqTm7yRDbmjwh5GW595YQJn6KX2WtLznUz/VgfP1x
        mAeMgNtfuqCqyRgRoqSFKzGpOdKobj4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-126-nFF1I69QNRqKWgF8nam1Jg-1; Mon, 25 May 2020 10:41:31 -0400
X-MC-Unique: nFF1I69QNRqKWgF8nam1Jg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D1FB31005512;
        Mon, 25 May 2020 14:41:29 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.114])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8501B5D9C5;
        Mon, 25 May 2020 14:41:26 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, Gavin Shan <gshan@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 00/10] KVM: x86: Interrupt-based mechanism for async_pf
 'page present' notifications
Date: Mon, 25 May 2020 16:41:15 +0200
Message-Id: <20200525144125.143875-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Concerns were expressed around (ab)using #PF for KVM's async_pf mechanism,
it seems that re-using #PF exception for a PV mechanism wasn't a great
idea after all. The Grand Plan is to switch to using e.g. #VE for 'page
not present' events and normal APIC interrupts for 'page ready' events.
This series does the later.

Changes since v1:
- struct kvm_vcpu_pv_apf_data's fields renamed to 'flags' and 'token',
  comments added [Vivek Goyal]
- 'type1/2' names for APF events dropped from everywhere [Vivek Goyal]
- kvm_arch_can_inject_async_page_present() renamed to 
  kvm_arch_can_dequeue_async_page_present [Vivek Goyal]
- 'KVM: x86: deprecate KVM_ASYNC_PF_SEND_ALWAYS' patch added.

v1: https://lore.kernel.org/kvm/20200511164752.2158645-1-vkuznets@redhat.com/
QEMU patches for testing: https://github.com/vittyvk/qemu.git (async_pf2_v2 branch)

Vitaly Kuznetsov (10):
  Revert "KVM: async_pf: Fix #DF due to inject "Page not Present" and
    "Page Ready" exceptions simultaneously"
  KVM: x86: extend struct kvm_vcpu_pv_apf_data with token info
  KVM: rename kvm_arch_can_inject_async_page_present() to
    kvm_arch_can_dequeue_async_page_present()
  KVM: introduce kvm_read_guest_offset_cached()
  KVM: x86: interrupt based APF 'page ready' event delivery
  KVM: x86: acknowledgment mechanism for async pf page ready
    notifications
  KVM: x86: announce KVM_FEATURE_ASYNC_PF_INT
  KVM: x86: Switch KVM guest to using interrupts for page ready APF
    delivery
  KVM: x86: drop KVM_PV_REASON_PAGE_READY case from
    kvm_handle_page_fault()
  KVM: x86: deprecate KVM_ASYNC_PF_SEND_ALWAYS

 Documentation/virt/kvm/cpuid.rst     |   6 ++
 Documentation/virt/kvm/msr.rst       | 120 +++++++++++++++------
 arch/s390/include/asm/kvm_host.h     |   4 +-
 arch/s390/kvm/kvm-s390.c             |   2 +-
 arch/x86/entry/entry_32.S            |   5 +
 arch/x86/entry/entry_64.S            |   5 +
 arch/x86/include/asm/hardirq.h       |   3 +
 arch/x86/include/asm/irq_vectors.h   |   6 +-
 arch/x86/include/asm/kvm_host.h      |  12 ++-
 arch/x86/include/asm/kvm_para.h      |  10 +-
 arch/x86/include/uapi/asm/kvm_para.h |  19 +++-
 arch/x86/kernel/irq.c                |   9 ++
 arch/x86/kernel/kvm.c                |  62 +++++++----
 arch/x86/kvm/cpuid.c                 |   3 +-
 arch/x86/kvm/mmu/mmu.c               |  19 ++--
 arch/x86/kvm/svm/nested.c            |   2 +-
 arch/x86/kvm/svm/svm.c               |   3 +-
 arch/x86/kvm/vmx/nested.c            |   2 +-
 arch/x86/kvm/vmx/vmx.c               |   5 +-
 arch/x86/kvm/x86.c                   | 149 ++++++++++++++++++---------
 include/linux/kvm_host.h             |   3 +
 include/uapi/linux/kvm.h             |   1 +
 virt/kvm/async_pf.c                  |  12 ++-
 virt/kvm/kvm_main.c                  |  19 +++-
 24 files changed, 344 insertions(+), 137 deletions(-)
```
#### [PATCH v2 0/5] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Mon May 25 14:44:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11568941
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6147C15E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:45:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53A8E2089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 14:45:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390967AbgEYOpD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 10:45:03 -0400
Received: from mga04.intel.com ([192.55.52.120]:34251 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388687AbgEYOpD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 10:45:03 -0400
IronPort-SDR: 
 MNEUnyJIl08+wYr3Zn4TJLIB0HcBfpZa0KT5ZQ6dQt7VfJqNOq7PZK1Koc8d0pf9mGEYa/SRSf
 mDYgE9EmEhnA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 May 2020 07:45:02 -0700
IronPort-SDR: 
 yV9Ov9Gz0kuWU9Db5dVuhIzcw6jQcENaX56MOivfEnDBMq2FTcuyEcc8IgmIL0CDheHN5rBXhg
 666GxjYJsifQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,433,1583222400";
   d="scan'208";a="266165815"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.249.41.109])
  by orsmga003.jf.intel.com with ESMTP; 25 May 2020 07:44:59 -0700
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
        Bjorn Andersson <bjorn.andersson@linaro.org>
Subject: [PATCH v2 0/5] Add a vhost RPMsg API
Date: Mon, 25 May 2020 16:44:53 +0200
Message-Id: <20200525144458.8413-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- remove "default n" from Kconfig
- drop patch #6 - it depends on a different patch, that is currently 
  an RFC
- update patch #5 with a correct vhost_dev_init() prototype

Linux supports RPMsg over VirtIO for "remote processor" /AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits
A further patch for the ADSP vhost RPMsg driver will be sent
separately for review only since it cannot be merged without audio
patches being upstreamed first.

Thanks
Guennadi

Guennadi Liakhovetski (5):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  vhost: (cosmetic) remove a superfluous variable initialisation
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an rpmsg API

 Documentation/rpmsg.txt          |   2 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +-------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 372 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c            |   2 +-
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++++
 include/linux/virtio_rpmsg.h     |  81 +++++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 10 files changed, 547 insertions(+), 79 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/virtio_rpmsg.h
```
#### [PATCH v3 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Mon May 25 22:13:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11569605
Return-Path: <SRS0=SRxi=7H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2ABDE90
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 22:14:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0DB632071A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 May 2020 22:14:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="uHCsLfmJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388054AbgEYWOI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 May 2020 18:14:08 -0400
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:59587 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729798AbgEYWOH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 May 2020 18:14:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1590444845; x=1621980845;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=Gqa9yJh460SEbEt/xbCMTARTLbZRW5tfuDBAX1ji5js=;
  b=uHCsLfmJw2Y0lmQgkF7FrGJE9dlNSmNpVuX8uvIJUaS0SATkX3YucP66
   yC3QCT0EqZ2MgI1B33OBGpFrHEM7uitUrS30BLmXe+bFSK6bNTmgQSuAk
   8GbxcgpWfwjO81PgXKYSiS3FfzcaCFfMNEsnEocqp1wo6yCvJBrm+lTDY
   I=;
IronPort-SDR: 
 g5ZR5/3J/0v+QciLqZL5v8DICl6PbqTJCIGWsqualwoAJcKoTvwblaoBTcB4vmKg6ky+DNqz7g
 ZVV2qVitGyxw==
X-IronPort-AV: E=Sophos;i="5.73,435,1583193600";
   d="scan'208";a="32053488"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-715bee71.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 25 May 2020 22:13:52 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-715bee71.us-east-1.amazon.com (Postfix) with
 ESMTPS id AC177A2439;
        Mon, 25 May 2020 22:13:50 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 25 May 2020 22:13:50 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 25 May 2020 22:13:40 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "Bjoern Doebel" <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        "Frank van der Linden" <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        "Martin Pohlack" <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v3 00/18] Add support for Nitro Enclaves
Date: Tue, 26 May 2020 01:13:16 +0300
Message-ID: <20200525221334.62966-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D12UWC004.ant.amazon.com (10.43.162.182) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPU, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest  that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

How does all gets to an enclave VM running on the host?

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the current patch series.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command or the KVM_SET_USER_MEMORY_REGION maps to
an add memory PCI command. The PCI device commands are then translated into
actions taken on the hypervisor side; that's the Nitro hypervisor running on the
host where the primary VM is running. The Nitro hypervisor is based on core KVM
technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [2]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol.

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC. We've also considered FIT image format
[3] as an option for the enclave image.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

The following patch series covers the NE driver for enclave lifetime management.
It provides an ioctl interface to the user space and includes the NE PCI device
driver that is the means of communication with the hypervisor running on the
host where the primary VM and the enclave are launched.

The proposed solution is following the KVM model and uses KVM ioctls to be able
to create and set resources for enclaves. Additional NE ioctl commands, besides
the ones provided by KVM, are used to start an enclave and get memory offset for
in-memory enclave image loading.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] http://man7.org/linux/man-pages/man7/vsock.7.html
[3] https://github.com/u-boot/u-boot/tree/master/doc/uImage.FIT
---

Patch Series Changelog

The patch series is built on top of v5.7-rc7.

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for enclave vm creation
  nitro_enclaves: Add logic for enclave vcpu creation
  nitro_enclaves: Add logic for enclave image load metadata
  nitro_enclaves: Add logic for enclave memory region set
  nitro_enclaves: Add logic for enclave start
  nitro_enclaves: Add logic for enclave termination
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 Documentation/nitro_enclaves/ne_overview.txt  |   86 ++
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   16 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1052 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |  109 ++
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  606 ++++++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  254 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |   65 +
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  490 ++++++++
 16 files changed, 2739 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/nitro_enclaves/ne_overview.txt
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
