

#### [PATCH v3 00/15] virtio-mem: paravirtualized memory
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Thu May  7 10:31:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11533025
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8729A139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 10:32:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69B702186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 10:32:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HWfo/ttF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726267AbgEGKcA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 06:32:00 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58618 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725903AbgEGKcA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 06:32:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588847519;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VLTLF8okWG2U8qocbOPYjuf/W5P0dXVCWo4Nb3iuQAg=;
        b=HWfo/ttFkGYtqRBHinrbWAUXGMYA7twEqvIgY6sK2QxBEj+RZ4RpmJc9xjz2R0/JxN4LWy
        pDajlhza+8EZBvA75EXp8SdxqZnMtnzbq3JjAab8KLVy2vdzWPbBGCgVfIiJ//1mafUEVg
        F19+MdELaQO9s0QhrFUa4wEH4Jdecqs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-228-7KSFfIZuMTWeQ6b4FFHZvw-1; Thu, 07 May 2020 06:31:55 -0400
X-MC-Unique: 7KSFfIZuMTWeQ6b4FFHZvw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0208780183C;
        Thu,  7 May 2020 10:31:51 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-245.ams2.redhat.com [10.36.113.245])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8D8415D9C5;
        Thu,  7 May 2020 10:31:28 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        Samuel Ortiz <samuel.ortiz@intel.com>,
        Robert Bradford <robert.bradford@intel.com>,
        Luiz Capitulino <lcapitulino@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        teawater <teawaterz@linux.alibaba.com>,
        Igor Mammedov <imammedo@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Alexander Potapenko <glider@google.com>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Anthony Yznaga <anthony.yznaga@oracle.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Dave Young <dyoung@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Johannes Weiner <hannes@cmpxchg.org>,
        Juergen Gross <jgross@suse.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Len Brown <lenb@kernel.org>,
        Mel Gorman <mgorman@techsingularity.net>,
        Michal Hocko <mhocko@suse.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Oscar Salvador <osalvador@suse.com>,
        Oscar Salvador <osalvador@suse.de>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Pavel Tatashin <pavel.tatashin@microsoft.com>,
        Pingfan Liu <kernelfans@gmail.com>, Qian Cai <cai@lca.pw>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        Wei Yang <richard.weiyang@gmail.com>
Subject: [PATCH v3 00/15] virtio-mem: paravirtualized memory
Date: Thu,  7 May 2020 12:31:04 +0200
Message-Id: <20200507103119.11219-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is based on latest linux-next. The patches are located at:
    https://github.com/davidhildenbrand/linux.git virtio-mem-v3

Patch #1 - #10 where contained in v2 and only contain minor modifications
(mostly smaller fixes). The remaining patches are new and contain smaller
optimizations.

Details about virtio-mem can be found in the cover letter of v2 [1]. A
basic QEMU implementation was posted yesterday [2].

[1] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com
[2] https://lkml.kernel.org/r/20200506094948.76388-1-david@redhat.com

v2 -> v3:
- "virtio-mem: Paravirtualized memory hotplug"
-- Include "linux/slab.h" to fix build issues
-- Remember the "region_size", helpful for patch #11
-- Minor simplifaction in virtio_mem_overlaps_range()
-- Use notifier_from_errno() instead of notifier_to_errno() in notifier
-- More reliable check for added memory when unloading the driver
- "virtio-mem: Allow to specify an ACPI PXM as nid"
-- Also print the nid
- Added patch #11-#15

Cc: Sebastien Boeuf <sebastien.boeuf@intel.com>
Cc: Samuel Ortiz <samuel.ortiz@intel.com>
Cc: Robert Bradford <robert.bradford@intel.com>
Cc: Luiz Capitulino <lcapitulino@redhat.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: teawater <teawaterz@linux.alibaba.com>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Dr. David Alan Gilbert <dgilbert@redhat.com>

David Hildenbrand (15):
  virtio-mem: Paravirtualized memory hotplug
  virtio-mem: Allow to specify an ACPI PXM as nid
  virtio-mem: Paravirtualized memory hotunplug part 1
  virtio-mem: Paravirtualized memory hotunplug part 2
  mm: Allow to offline unmovable PageOffline() pages via
    MEM_GOING_OFFLINE
  virtio-mem: Allow to offline partially unplugged memory blocks
  mm/memory_hotplug: Introduce offline_and_remove_memory()
  virtio-mem: Offline and remove completely unplugged memory blocks
  virtio-mem: Better retry handling
  MAINTAINERS: Add myself as virtio-mem maintainer
  virtio-mem: Add parent resource for all added "System RAM"
  virtio-mem: Drop manual check for already present memory
  virtio-mem: Unplug subblocks right-to-left
  virtio-mem: Use -ETXTBSY as error code if the device is busy
  virtio-mem: Try to unplug the complete online memory block first

 MAINTAINERS                     |    7 +
 drivers/acpi/numa/srat.c        |    1 +
 drivers/virtio/Kconfig          |   17 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1962 +++++++++++++++++++++++++++++++
 include/linux/memory_hotplug.h  |    1 +
 include/linux/page-flags.h      |   10 +
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  208 ++++
 mm/memory_hotplug.c             |   81 +-
 mm/page_alloc.c                 |   26 +
 mm/page_isolation.c             |    9 +
 12 files changed, 2314 insertions(+), 10 deletions(-)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h
```
#### [PATCH v2 0/9] KVM_SET_GUEST_DEBUG tests and fixes,
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu May  7 11:50:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11533237
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2FC81139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:51:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E77C20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:51:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EuXEDKyX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726542AbgEGLuT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 07:50:19 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:58967 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725985AbgEGLuT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 May 2020 07:50:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588852217;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=HpySo1fPq0F4Fe5nieQHEfTObO9AX94O/qzGxsIgTec=;
        b=EuXEDKyXkcsbch+mo96bh7IWx/osBnm7S2Llw+ksM6vDZ0Cx9x4Rs06AyJq5GSDQLMl5sP
        sK8xh+z6r76aSB8vF/1ih716ZBv8S/wryr6ZBfQXMr5FrbSG90wTzl4cH5SNV7xHrVnpor
        bOtZGIZ+3TCil6ug1vqghHaH3JPeCRc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-119-vreDZiYOMKqkFon784JXFg-1; Thu, 07 May 2020 07:50:16 -0400
X-MC-Unique: vreDZiYOMKqkFon784JXFg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0A080801504;
        Thu,  7 May 2020 11:50:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E24341C933;
        Thu,  7 May 2020 11:50:11 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH v2 0/9] KVM_SET_GUEST_DEBUG tests and fixes,
 DR accessors cleanups
Date: Thu,  7 May 2020 07:50:02 -0400
Message-Id: <20200507115011.494562-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This new version of the patches improves the AMD bugfix where
KVM_EXIT_DEBUG clobbers the guest DR6 and includes stale causes.
The improved fix makes it possible to drop kvm_set_dr6 and
kvm_update_dr6 altogether.

v1->v2: - merge v1 patch 6 with get_dr6 part of v1 patch 7, cover nested SVM
	- new patch "KVM: nSVM: trap #DB and #BP to userspace if guest debugging is on"
	- rewritten patch 8 to get rid of set_dr6 completely

Paolo Bonzini (5):
  KVM: x86: fix DR6 delivery for various cases of #DB injection
  KVM: nSVM: trap #DB and #BP to userspace if guest debugging is on
  KVM: SVM: keep DR6 synchronized with vcpu->arch.dr6
  KVM: x86, SVM: isolate vcpu->arch.dr6 from vmcb->save.dr6
  KVM: VMX: pass correct DR6 for GD userspace exit

Peter Xu (4):
  KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
  KVM: X86: Set RTM for DB_VECTOR too for KVM_EXIT_DEBUG
  KVM: X86: Fix single-step with KVM_SET_GUEST_DEBUG
  KVM: selftests: Add KVM_SET_GUEST_DEBUG test

 arch/powerpc/kvm/powerpc.c                    |   1 +
 arch/s390/kvm/kvm-s390.c                      |   1 +
 arch/x86/include/asm/kvm_host.h               |   3 +-
 arch/x86/kvm/svm/nested.c                     |  39 +++-
 arch/x86/kvm/svm/svm.c                        |  36 ++--
 arch/x86/kvm/vmx/vmx.c                        |  23 +-
 arch/x86/kvm/x86.c                            |  27 +--
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   9 +
 .../testing/selftests/kvm/x86_64/debug_regs.c | 202 ++++++++++++++++++
 11 files changed, 281 insertions(+), 63 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/debug_regs.c
```
#### [PATCH resend 0/2] KVM: arm64: Unify stage2 mapping for THP backed
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
From patchwork Thu May  7 12:35:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11533507
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5A261913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 12:36:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BCB920663
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 12:36:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726767AbgEGMgi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 08:36:38 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:37856 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726235AbgEGMgi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 08:36:38 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id C0507E11C10FEA00DF20;
        Thu,  7 May 2020 20:36:31 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Thu, 7 May 2020 20:36:22 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>, <suzuki.poulose@arm.com>
CC: <maz@kernel.org>, <christoffer.dall@arm.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <kvm@vger.kernel.org>, <linux-arm-kernel@lists.infradead.org>,
        <linux-kernel@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        <zhengxiang9@huawei.com>, <amurray@thegoodpenguin.co.uk>,
        <eric.auger@redhat.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH resend 0/2] KVM: arm64: Unify stage2 mapping for THP backed
 memory
Date: Thu, 7 May 2020 20:35:44 +0800
Message-ID: <20200507123546.1875-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series was originally posted by Suzuki K Poulose a year ago [*],
with the aim of cleaning up the handling of the stage2 huge mapping for
THP. I think this still helps to make the current code cleaner, so
rebase it on top of kvmarm/master and repost it for acceptance.

Thanks!

[*] https://lore.kernel.org/kvm/1554909832-7169-1-git-send-email-suzuki.poulose@arm.com/

Suzuki K Poulose (2):
  KVM: arm64: Clean up the checking for huge mapping
  KVM: arm64: Unify handling THP backed host memory

 virt/kvm/arm/mmu.c | 121 ++++++++++++++++++++++++---------------------
 1 file changed, 65 insertions(+), 56 deletions(-)
```
#### [PATCH v26 00/10] Add ARMv8 RAS virtualization support in QEMU
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
From patchwork Thu May  7 13:41:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: gengdongjiu <gengdongjiu@huawei.com>
X-Patchwork-Id: 11533799
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F6CF913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 13:40:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EAC322075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 13:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727789AbgEGNkn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 09:40:43 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:3895 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725879AbgEGNkZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 09:40:25 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id C2B1F785302588A9561B;
        Thu,  7 May 2020 21:40:17 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.487.0; Thu, 7 May 2020
 21:40:08 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <pbonzini@redhat.com>,
        <fam@euphon.net>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>, <qemu-devel@nongnu.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v26 00/10] Add ARMv8 RAS virtualization support in QEMU
Date: Thu, 7 May 2020 21:41:55 +0800
Message-ID: <20200507134205.7559-1-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the ARMv8 platform, the CPU error types includes synchronous external abort(SEA)
and SError Interrupt (SEI). If exception happens in guest, host does not know the detailed
information of guest, so it is expected that guest can do the recovery. For example, if an
exception happens in a guest user-space application, host does not know which application
encounters errors, only guest knows it.

For the ARMv8 SEA/SEI, KVM or host kernel delivers SIGBUS to notify userspace.
After user space gets the notification, it will record the CPER into guest GHES
buffer and inject an exception or IRQ to guest.

In the current implementation, if the type of SIGBUS is BUS_MCEERR_AR, we will
treat it as a synchronous exception, and notify guest with ARMv8 SEA
notification type after recording CPER into guest.

A) This series of patches are based on Qemu 4.2, which include two parts:
1. Generate APEI/GHES table.
2. Handle the SIGBUS signal, record the CPER in runtime and fill it into guest
   memory, then notify guest according to the type of SIGBUS.

B) The solution was suggested by James(james.morse@arm.com); The APEI part solution was suggested by Laszlo(lersek@redhat.com). Show some discussions in [1].

C) This series of patches have already been tested on ARM64 platform with RAS
feature enabled:
1. Show the APEI part verification result in [2].
2. Show the SIGBUS of BUS_MCEERR_AR handling verification result in [3].

D) Add 'ras' option in command Line to enable guest RAS error recovery feature, For example:
KVM model: ./qemu-system-aarch64 --enable-kvm -cpu host --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on
-smp 4 -nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
TCG model: ./qemu-system-aarch64 -cpu cortex-a57 --bios QEMU_EFI.fd_new  -machine virt,gic-version=3,ras,kernel-irqchip=on  -smp 4
-nographic -kernel Image  -append "rdinit=/init console=ttyAMA0 mem=512M root=/dev/ram0" -initrd guestfs_new.cpio.gz
---
Change since v23:
1. fix a warning for uuid

Change since v22:
1. Using 1 * KiB instead of 0x400 to define max size of one error block
2. Make the alignment to 8 bytes in bios_linker_loader_alloc()
3. Change "Copyright (c) 2019" to "Copyright (c) 2020" in file header
4. Fix some code style warnings/errors and add some comments in code
5. Address Jonathan's comments to easily support CCIX error injection
6. Add vmstate_ghes_state .subsections in vmstate_acpi_ged

Change since v21:
1. Make the user-facing 'ras' option description more clearly to address Peter's comments.
2. Update the doc description in "docs/specs/acpi_hest_ghes.rst"
3. Split HEST/GHES patches to more patches to make the review easily
4. Using source_id to index the location to save the CPER.
5. Optimize and simplify the logic to build HEST/GHES table to address Igor/Michael/Beata comments.
6. make ghes_addr_le a part of GED device.

Change since v20:
1. Move some implementation details from acpi_ghes.h to acpi_ghes.c
2. Add the reviewers for the ACPI/APEI/GHES part

Change since v19:
1. Fix clang compile error
2. Fix sphinx build error

Change since v18:
1. Fix some code-style and typo/grammar problems.
2. Remove no_ras in the VirtMachineClass struct.
3. Convert documentation to rst format.
4. Simplize the code and add comments for some magic value.
5. Move kvm_inject_arm_sea() function into the patch where it's used.
6. Register the reset handler(kvm_unpoison_all()) in the kvm_init() function.

Change since v17:
1. Improve some commit messages and comments.
2. Fix some code-style problems.
3. Add a *ras* machine option.
4. Move HEST/GHES related structures and macros into "hw/acpi/acpi_ghes.*".
5. Move HWPoison page functions into "include/sysemu/kvm_int.h".
6. Fix some bugs.
7. Improve the design document.

Change since v16:
1. check whether ACPI table is enabled when handling the memory error in the SIGBUS handler.

Change since v15:
1. Add a doc-comment in the proper format for 'include/exec/ram_addr.h'
2. Remove write_part_cpustate_to_list() because there is another bug fix patch
   has been merged "arm: Allow system registers for KVM guests to be changed by QEMU code"
3. Add some comments for kvm_inject_arm_sea() in 'target/arm/kvm64.c'
4. Compare the arm_current_el() return value to 0,1,2,3, not to PSTATE_MODE_* constants.
5. Change the RAS support wasn't introduced before 4.1 QEMU version.
6. Move the no_ras flag  patch to begin in this series

Change since v14:
1. Remove the BUS_MCEERR_AO handling logic because this asynchronous signal was masked by main thread
2. Address some Igor Mammedov's comments(ACPI part)
   1) change the comments for the enum AcpiHestNotifyType definition and remove ditto in patch 1
   2) change some patch commit messages and separate "APEI GHES table generation" patch to more patches.
3. Address some peter's comments(arm64 Synchronous External Abort injection)
   1) change some code notes
   2) using arm_current_el() for current EL
   2) use the helper functions for those (syn_data_abort_*).

Change since v13:
1. Move the patches that set guest ESR and inject virtual SError out of this series
2. Clean and optimize the APEI part patches
3. Update the commit messages and add some comments for the code

Change since v12:
1. Address Paolo's comments to move HWPoisonPage definition to accel/kvm/kvm-all.c
2. Only call kvm_cpu_synchronize_state() when get the BUS_MCEERR_AR signal
3. Only add and enable GPIO-Signal and ARMv8 SEA two hardware error sources
4. Address Michael's comments to not sync SPDX from Linux kernel header file

Change since v11:
Address James's comments(james.morse@arm.com)
1. Check whether KVM has the capability to to set ESR instead of detecting host CPU RAS capability
2. For SIGBUS_MCEERR_AR SIGBUS, use Synchronous-External-Abort(SEA) notification type
   for SIGBUS_MCEERR_AO SIGBUS, use GPIO-Signal notification


Address Shannon's comments(for ACPI part):
1. Unify hest_ghes.c and hest_ghes.h license declaration
2. Remove unnecessary including "qmp-commands.h" in hest_ghes.c
3. Unconditionally add guest APEI table based on James's comments(james.morse@arm.com)
4. Add a option to virt machine for migration compatibility. On new virt machine it's on
   by default while off for old ones, we enabled it since 2.12
5. Refer to the ACPI spec version which introduces Hardware Error Notification first time
6. Add ACPI_HEST_NOTIFY_RESERVED notification type

Address Igor's comments(for ACPI part):
1. Add doc patch first which will describe how it's supposed to work between QEMU/firmware/guest
   OS with expected flows.
2. Move APEI diagrams into doc/spec patch
3. Remove redundant g_malloc in ghes_record_cper()
4. Use build_append_int_noprefix() API to compose whole error status block and whole APEI table,
   and try to get rid of most structures in patch 1, as they will be left unused after that
5. Reuse something like https://github.com/imammedo/qemu/commit/3d2fd6d13a3ea298d2ee814835495ce6241d085c to build GAS
6. Remove much offsetof() in the function
7. Build independent tables first and only then build dependent tables passing to it pointers
   to previously build table if necessary.
8. Redefine macro GHES_ACPI_HEST_NOTIFY_RESERVED to ACPI_HEST_ERROR_SOURCE_COUNT to avoid confusion


Address Peter Maydell's comments
1. linux-headers is done as a patch of their own created using scripts/update-linux-headers.sh run against a mainline kernel tree
2. Tested whether this patchset builds OK on aarch32
3. Abstract Hwpoison page adding code  out properly into a cpu-independent source file from target/i386/kvm.c, such as kvm-all.c
4. Add doc-comment formatted documentation comment for new globally-visible function prototype in a header

---
[1]:
https://lkml.org/lkml/2017/2/27/246
https://patchwork.kernel.org/patch/9633105/
https://patchwork.kernel.org/patch/9925227/

[2]:
Note: the UEFI(QEMU_EFI.fd) is needed if guest want to use ACPI table.

After guest boot up, dump the APEI table, then can see the initialized table
(1) # iasl -p ./HEST -d /sys/firmware/acpi/tables/HEST
(2) # cat HEST.dsl
    /*
     * Intel ACPI Component Architecture
     * AML/ASL+ Disassembler version 20170728 (64-bit version)
     * Copyright (c) 2000 - 2017 Intel Corporation
     *
     * Disassembly of /sys/firmware/acpi/tables/HEST, Mon Sep  5 07:59:17 2016
     *
     * ACPI Data Table [HEST]
     *
     * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
     */

    ..................................................................................
    [308h 0776   2]                Subtable Type : 000A [Generic Hardware Error Source V2]
    [30Ah 0778   2]                    Source Id : 0001
    [30Ch 0780   2]            Related Source Id : FFFF
    [30Eh 0782   1]                     Reserved : 00
    [30Fh 0783   1]                      Enabled : 01
    [310h 0784   4]       Records To Preallocate : 00000001
    [314h 0788   4]      Max Sections Per Record : 00000001
    [318h 0792   4]          Max Raw Data Length : 00001000

    [31Ch 0796  12]         Error Status Address : [Generic Address Structure]
    [31Ch 0796   1]                     Space ID : 00 [SystemMemory]
    [31Dh 0797   1]                    Bit Width : 40
    [31Eh 0798   1]                   Bit Offset : 00
    [31Fh 0799   1]         Encoded Access Width : 04 [QWord Access:64]
    [320h 0800   8]                      Address : 00000000785D0040

    [328h 0808  28]                       Notify : [Hardware Error Notification Structure]
    [328h 0808   1]                  Notify Type : 08 [SEA]
    [329h 0809   1]                Notify Length : 1C
    [32Ah 0810   2]   Configuration Write Enable : 0000
    [32Ch 0812   4]                 PollInterval : 00000000
    [330h 0816   4]                       Vector : 00000000
    [334h 0820   4]      Polling Threshold Value : 00000000
    [338h 0824   4]     Polling Threshold Window : 00000000
    [33Ch 0828   4]        Error Threshold Value : 00000000
    [340h 0832   4]       Error Threshold Window : 00000000

    [344h 0836   4]    Error Status Block Length : 00001000
    [348h 0840  12]            Read Ack Register : [Generic Address Structure]
    [348h 0840   1]                     Space ID : 00 [SystemMemory]
    [349h 0841   1]                    Bit Width : 40
    [34Ah 0842   1]                   Bit Offset : 00
    [34Bh 0843   1]         Encoded Access Width : 04 [QWord Access:64]
    [34Ch 0844   8]                      Address : 00000000785D0098

    [354h 0852   8]            Read Ack Preserve : 00000000FFFFFFFE
    [35Ch 0860   8]               Read Ack Write : 0000000000000001

    .....................................................................................

(3) After a synchronous external abort(SEA) happen, Qemu receive a SIGBUS and 
    filled the CPER into guest GHES memory.  For example, according to above table,
    the address that contains the physical address of a block of memory that holds
    the error status data is 0x00000000785D0040
(4) the address of error source which is SEA notification type is 0x785d80b0
    (qemu) xp /1 0x00000000785D0040
    00000000785d0040: 0x785d80b0

(5) check the content of generic error status block and generic error data entry
    (qemu) xp /100x 0x785d80b0
    00000000785d80b0: 0x00000001 0x00000000 0x00000000 0x00000098
    00000000785d80c0: 0x00000000 0xa5bc1114 0x4ede6f64 0x833e63b8
    00000000785d80d0: 0xb1837ced 0x00000000 0x00000300 0x00000050
    00000000785d80e0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d80f0: 0x00000000 0x00000000 0x00000000 0x00000000
    00000000785d8100: 0x00000000 0x00000000 0x00000000 0x00004002
(6) check the OSPM's ACK value(for example SEA)
    /* Before OSPM acknowledges the error, check the ACK value */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000000

    /* After OSPM acknowledges the error, check the ACK value, it change to 1 from 0 */
    (qemu) xp /1 0x00000000785D0098
    00000000785d00f0: 0x00000001

[3]: KVM deliver "BUS_MCEERR_AR" to Qemu, Qemu record the guest CPER and inject
    synchronous external abort to notify guest, then guest do the recovery.

[ 1552.516170] Synchronous External Abort: synchronous external abort (0x92000410) at 0x000000003751c6b4
[ 1553.074073] {1}[Hardware Error]: Hardware error from APEI Generic Hardware Error Source: 8
[ 1553.081654] {1}[Hardware Error]: event severity: recoverable
[ 1554.034191] {1}[Hardware Error]:  Error 0, type: recoverable
[ 1554.037934] {1}[Hardware Error]:   section_type: memory error
[ 1554.513261] {1}[Hardware Error]:   physical_address: 0x0000000040fa6000
[ 1554.513944] {1}[Hardware Error]:   error_type: 0, unknown
[ 1555.041451] Memory failure: 0x40fa6: Killing mca-recover:1296 due to hardware memory corruption
[ 1555.373116] Memory failure: 0x40fa6: recovery action for dirty LRU page: Recovered

Dongjiu Geng (10):
  acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
  hw/arm/virt: Introduce a RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Build related register address fields via hardware error fw_cfg
    blob
  ACPI: Build Hardware Error Source Table
  ACPI: Record the Generic Error Status Block address
  KVM: Move hwpoison page related functions into kvm-all.c
  ACPI: Record Generic Error Status Block(GESB) table
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM
  MAINTAINERS: Add ACPI/HEST/GHES entries

 MAINTAINERS                            |   9 +
 accel/kvm/kvm-all.c                    |  36 +++
 default-configs/arm-softmmu.mak        |   1 +
 docs/specs/acpi_hest_ghes.rst          | 110 ++++++++
 docs/specs/index.rst                   |   1 +
 hw/acpi/Kconfig                        |   4 +
 hw/acpi/Makefile.objs                  |   1 +
 hw/acpi/aml-build.c                    |   2 +
 hw/acpi/generic_event_device.c         |  19 ++
 hw/acpi/ghes.c                         | 448 +++++++++++++++++++++++++++++++++
 hw/acpi/nvdimm.c                       |  10 +-
 hw/arm/virt-acpi-build.c               |  15 ++
 hw/arm/virt.c                          |  23 ++
 include/hw/acpi/aml-build.h            |   1 +
 include/hw/acpi/generic_event_device.h |   2 +
 include/hw/acpi/ghes.h                 |  74 ++++++
 include/hw/arm/virt.h                  |   1 +
 include/qemu/uuid.h                    |   9 +
 include/sysemu/kvm.h                   |   3 +-
 include/sysemu/kvm_int.h               |  12 +
 target/arm/cpu.h                       |   4 +
 target/arm/helper.c                    |   2 +-
 target/arm/internals.h                 |   5 +-
 target/arm/kvm64.c                     |  77 ++++++
 target/arm/tlb_helper.c                |   2 +-
 target/i386/cpu.h                      |   2 +
 target/i386/kvm.c                      |  36 ---
 27 files changed, 860 insertions(+), 49 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/ghes.c
 create mode 100644 include/hw/acpi/ghes.h

Dongjiu Geng (10):
  acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
  hw/arm/virt: Introduce a RAS machine option
  docs: APEI GHES generation and CPER record description
  ACPI: Build related register address fields via hardware error fw_cfg
    blob
  ACPI: Build Hardware Error Source Table
  ACPI: Record the Generic Error Status Block address
  KVM: Move hwpoison page related functions into kvm-all.c
  ACPI: Record Generic Error Status Block(GESB) table
  target-arm: kvm64: handle SIGBUS signal from kernel or KVM
  MAINTAINERS: Add ACPI/HEST/GHES entries

 MAINTAINERS                            |   9 +
 accel/kvm/kvm-all.c                    |  36 +++
 default-configs/arm-softmmu.mak        |   1 +
 docs/specs/acpi_hest_ghes.rst          | 110 ++++++++
 docs/specs/index.rst                   |   1 +
 hw/acpi/Kconfig                        |   4 +
 hw/acpi/Makefile.objs                  |   1 +
 hw/acpi/aml-build.c                    |   2 +
 hw/acpi/generic_event_device.c         |  19 ++
 hw/acpi/ghes.c                         | 448 +++++++++++++++++++++++++++++++++
 hw/acpi/nvdimm.c                       |  10 +-
 hw/arm/virt-acpi-build.c               |  15 ++
 hw/arm/virt.c                          |  23 ++
 include/hw/acpi/aml-build.h            |   1 +
 include/hw/acpi/generic_event_device.h |   2 +
 include/hw/acpi/ghes.h                 |  74 ++++++
 include/hw/arm/virt.h                  |   1 +
 include/qemu/uuid.h                    |  26 ++
 include/sysemu/kvm.h                   |   3 +-
 include/sysemu/kvm_int.h               |  12 +
 slirp                                  |   2 +-
 target/arm/cpu.h                       |   4 +
 target/arm/helper.c                    |   2 +-
 target/arm/internals.h                 |   5 +-
 target/arm/kvm64.c                     |  77 ++++++
 target/arm/tlb_helper.c                |   2 +-
 target/i386/cpu.h                      |   2 +
 target/i386/kvm.c                      |  36 ---
 28 files changed, 878 insertions(+), 50 deletions(-)
 create mode 100644 docs/specs/acpi_hest_ghes.rst
 create mode 100644 hw/acpi/ghes.c
 create mode 100644 include/hw/acpi/ghes.h
```
#### [PATCH v4 00/15] virtio-mem: paravirtualized memory
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Thu May  7 14:01:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11533867
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2771681
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 14:02:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CA6120838
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 14:02:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cA2dOUFy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726660AbgEGOCO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 10:02:14 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:28597 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726408AbgEGOCN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 May 2020 10:02:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588860131;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=YnnUFsND7O7jqtL6msM8nwBMUisTSmUw25RGNt2JJrs=;
        b=cA2dOUFyzz3xZhTTLdSIVp2NdSKgyvVyjJ7QTDkMFgWT9gTFSDzCrdeUyfPikRSQMu3xGf
        Mq74s3CzLtsnht/MY5YB3umFiMFUBEIhpmuc16oAZyq+CtENaxIBF23J2auFnsQThh6Tyl
        aRd0kk9AqCyan2cnxq6EYo9YLniVyaY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-103-rdP8lYCVMWC9u4yrElCVAQ-1; Thu, 07 May 2020 10:02:03 -0400
X-MC-Unique: rdP8lYCVMWC9u4yrElCVAQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C4169835B45;
        Thu,  7 May 2020 14:01:58 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-245.ams2.redhat.com [10.36.113.245])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AF26260FB9;
        Thu,  7 May 2020 14:01:40 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Alexander Duyck <alexander.h.duyck@linux.intel.com>,
        Alexander Potapenko <glider@google.com>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Anthony Yznaga <anthony.yznaga@oracle.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Dave Young <dyoung@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Johannes Weiner <hannes@cmpxchg.org>,
        Juergen Gross <jgross@suse.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Len Brown <lenb@kernel.org>,
        Mel Gorman <mgorman@techsingularity.net>,
        Michal Hocko <mhocko@suse.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Oscar Salvador <osalvador@suse.com>,
        Oscar Salvador <osalvador@suse.de>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Pavel Tatashin <pavel.tatashin@microsoft.com>,
        Pingfan Liu <kernelfans@gmail.com>, Qian Cai <cai@lca.pw>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        Wei Yang <richard.weiyang@gmail.com>
Subject: [PATCH v4 00/15] virtio-mem: paravirtualized memory
Date: Thu,  7 May 2020 16:01:24 +0200
Message-Id: <20200507140139.17083-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is based on v5.7-rc4. The patches are located at:
    https://github.com/davidhildenbrand/linux.git virtio-mem-v4

This is basically a resend of v3 [1], now based on v5.7-rc4 and restested.
One patch was reshuffled and two ACKs I missed to add were added. The
rebase did not require any modifications to patches.

Details about virtio-mem can be found in the cover letter of v2 [2]. A
basic QEMU implementation was posted yesterday [3].

[1] https://lkml.kernel.org/r/20200507103119.11219-1-david@redhat.com
[2] https://lkml.kernel.org/r/20200311171422.10484-1-david@redhat.com
[3] https://lkml.kernel.org/r/20200506094948.76388-1-david@redhat.com

v3 -> v4:
- Move "MAINTAINERS: Add myself as virtio-mem maintainer" to #2
- Add two ACKs from Andrew (in reply to v2)
-- "mm: Allow to offline unmovable PageOffline() pages via ..."
-- "mm/memory_hotplug: Introduce offline_and_remove_memory()"

v2 -> v3:
- "virtio-mem: Paravirtualized memory hotplug"
-- Include "linux/slab.h" to fix build issues
-- Remember the "region_size", helpful for patch #11
-- Minor simplifaction in virtio_mem_overlaps_range()
-- Use notifier_from_errno() instead of notifier_to_errno() in notifier
-- More reliable check for added memory when unloading the driver
- "virtio-mem: Allow to specify an ACPI PXM as nid"
-- Also print the nid
- Added patch #11-#15

David Hildenbrand (15):
  virtio-mem: Paravirtualized memory hotplug
  MAINTAINERS: Add myself as virtio-mem maintainer
  virtio-mem: Allow to specify an ACPI PXM as nid
  virtio-mem: Paravirtualized memory hotunplug part 1
  virtio-mem: Paravirtualized memory hotunplug part 2
  mm: Allow to offline unmovable PageOffline() pages via
    MEM_GOING_OFFLINE
  virtio-mem: Allow to offline partially unplugged memory blocks
  mm/memory_hotplug: Introduce offline_and_remove_memory()
  virtio-mem: Offline and remove completely unplugged memory blocks
  virtio-mem: Better retry handling
  virtio-mem: Add parent resource for all added "System RAM"
  virtio-mem: Drop manual check for already present memory
  virtio-mem: Unplug subblocks right-to-left
  virtio-mem: Use -ETXTBSY as error code if the device is busy
  virtio-mem: Try to unplug the complete online memory block first

 MAINTAINERS                     |    7 +
 drivers/acpi/numa/srat.c        |    1 +
 drivers/virtio/Kconfig          |   17 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1962 +++++++++++++++++++++++++++++++
 include/linux/memory_hotplug.h  |    1 +
 include/linux/page-flags.h      |   10 +
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  208 ++++
 mm/memory_hotplug.c             |   81 +-
 mm/page_alloc.c                 |   26 +
 mm/page_isolation.c             |    9 +
 12 files changed, 2314 insertions(+), 10 deletions(-)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h
```
