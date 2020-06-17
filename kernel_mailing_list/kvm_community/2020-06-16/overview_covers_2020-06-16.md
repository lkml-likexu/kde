

#### [PATCH 00/12] KVM: arm64: Support stage2 hardware DBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Tue Jun 16 09:35:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: zhukeqian <zhukeqian1@huawei.com>
X-Patchwork-Id: 11606961
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4ED8D14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 09:36:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41A91208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 09:36:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728271AbgFPJgR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 05:36:17 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:6334 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728240AbgFPJgQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 05:36:16 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 968F783B892EBF894D59;
        Tue, 16 Jun 2020 17:36:13 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.173.221.230) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Tue, 16 Jun 2020 17:36:03 +0800
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
        <liangpeng10@huawei.com>, <zhengxiang9@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 00/12] KVM: arm64: Support stage2 hardware DBM
Date: Tue, 16 Jun 2020 17:35:41 +0800
Message-ID: <20200616093553.27512-1-zhukeqian1@huawei.com>
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

Some key points:

1. Only support hardware updates of dirty status for PTEs. PMDs and PUDs
   are not involved for now.

2. About *performance*: In RFC patch, I have mentioned that for every 64GB
   memory, KVM consumes about 40ms to scan all PTEs to collect dirty log.
   
   Initially, I plan to solve this problem using parallel CPUs. However
   I faced two problems.

   The first is bottleneck of memory bandwith. Single thread will occupy
   bandwidth about 500GB/s, we can support about 4 parallel threads at
   most, so the ideal speedup ratio is low.

   The second is huge impact on other CPUs. To scan PTs quickly, I use
   smp_call_function_many, which is based on IPI, to dispatch workload
   on other CPUs. Though it can complete work in time, the interrupt is
   disabled during scaning PTs, which has huge impact on other CPUs.

   Now, I make hardware dirty log can be dynamic enabled and disabled.
   Userspace can enable it before VM migration and disable it when
   remaining dirty pages is little. Thus VM downtime is not affected. 


3. About correctness: Only add DBM bit when PTE is already writable, so
   we still have readonly PTE and some mechanisms which rely on readonly
   PTs are not broken.

4. About PTs modification races: There are two kinds of PTs modification.
   
   The first is adding or clearing specific bit, such as AF or RW. All
   these operations have been converted to be atomic, avoid covering
   dirty status set by hardware.
   
   The second is replacement, such as PTEs unmapping or changement. All
   these operations will invoke kvm_set_pte finally. kvm_set_pte have
   been converted to be atomic and we save the dirty status to underlying
   bitmap if dirty status is coverred.


Keqian Zhu (12):
  KVM: arm64: Add some basic functions to support hw DBM
  KVM: arm64: Modify stage2 young mechanism to support hw DBM
  KVM: arm64: Report hardware dirty status of stage2 PTE if coverred
  KVM: arm64: Support clear DBM bit for PTEs
  KVM: arm64: Add KVM_CAP_ARM_HW_DIRTY_LOG capability
  KVM: arm64: Set DBM bit of PTEs during write protecting
  KVM: arm64: Scan PTEs to sync dirty log
  KVM: Omit dirty log sync in log clear if initially all set
  KVM: arm64: Steply write protect page table by mask bit
  KVM: arm64: Save stage2 PTE dirty status if it is coverred
  KVM: arm64: Support disable hw dirty log after enable
  KVM: arm64: Enable stage2 hardware DBM

 arch/arm64/include/asm/kvm_host.h |  11 +
 arch/arm64/include/asm/kvm_mmu.h  |  56 +++-
 arch/arm64/include/asm/sysreg.h   |   2 +
 arch/arm64/kvm/arm.c              |  22 +-
 arch/arm64/kvm/mmu.c              | 411 ++++++++++++++++++++++++++++--
 arch/arm64/kvm/reset.c            |  14 +-
 include/uapi/linux/kvm.h          |   1 +
 tools/include/uapi/linux/kvm.h    |   1 +
 virt/kvm/kvm_main.c               |   7 +-
 9 files changed, 499 insertions(+), 26 deletions(-)
```
#### [RFC PATCH v3 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Tue Jun 16 19:50:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11608553
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5262F14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 414692082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730940AbgFPTvC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 15:51:02 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41400 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728518AbgFPTvB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 15:51:01 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJWNEJ002581;
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31n45dvujq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05GJWbHm003478;
        Tue, 16 Jun 2020 15:51:00 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31n45dvuj7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:00 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJnhjG013450;
        Tue, 16 Jun 2020 19:50:58 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 31mpe7wv99-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 19:50:58 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05GJot3S58916932
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Jun 2020 19:50:55 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6C844A405C;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 53030A405B;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id E791DE01F3; Tue, 16 Jun 2020 21:50:54 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v3 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Tue, 16 Jun 2020 21:50:50 +0200
Message-Id: <20200616195053.99253-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-16_12:2020-06-16,2020-06-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=0 phishscore=0 adultscore=0 mlxlogscore=999
 priorityscore=1501 bulkscore=0 malwarescore=0 spamscore=0 impostorscore=0
 clxscore=1011 cotscore=-2147483648 mlxscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006160134
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's continue our discussion of the handling of vfio-ccw interrupts.

The initial fix [1] relied upon the interrupt path's examination of the
FSM state, and freeing all resources if it were CP_PENDING. But the
interface used by HALT/CLEAR SUBCHANNEL doesn't affect the FSM state.
Consider this sequence:

    CPU 1                           CPU 2
    CLEAR (state=IDLE/no change)
                                    START [2]
    INTERRUPT (set state=IDLE)
                                    INTERRUPT (set state=IDLE)

This translates to a couple of possible scenarios:

 A) The START gets a cc2 because of the outstanding CLEAR, -EBUSY is
    returned, resources are freed, and state remains IDLE
 B) The START gets a cc0 because the CLEAR has already presented an
    interrupt, and state is set to CP_PENDING

If the START gets a cc0 before the CLEAR INTERRUPT (stacked onto a
workqueue by the IRQ context) gets a chance to run, then the INTERRUPT
will release the channel program memory prematurely. If the two
operations run concurrently, then the FSM state set to CP_PROCESSING
will prevent the cp_free() from being invoked. But the io_mutex
boundary on that path will pause itself until the START completes,
and then allow the FSM to be reset to IDLE without considering the
outstanding START. Neither scenario would be considered good.

Having said all of that, in v2 Conny suggested [3] the following:

> - Detach the cp from the subchannel (or better, remove the 1:1
>   relationship). By that I mean building the cp as a separately
>   allocated structure (maybe embedding a kref, but that might not be
>   needed), and appending it to a list after SSCH with cc=0. Discard it
>   if cc!=0.
> - Remove the CP_PENDING state. The state is either IDLE after any
>   successful SSCH/HSCH/CSCH, or a new state in that case. But no
>   special state for SSCH.
> - A successful CSCH removes the first queued request, if any.
> - A final interrupt removes the first queued request, if any.

What I have implemented here is basically this, with a few changes:

 - I don't queue cp's. Since there should only be one START in process
   at a time, and HALT/CLEAR doesn't build a cp, I didn't see a pressing
   need to introduce that complexity.
 - Furthermore, while I initially made a separately allocated cp, adding
   an alloc for a cp on each I/O AND moving the guest_cp alloc from the
   probe path to the I/O path seems excessive. So I implemented a
   "started" flag to the cp, set after a cc0 from the START, and examine
   that on the interrupt path to determine whether cp_free() is needed.
 - I opted against a "SOMETHING_PENDING" state if START/HALT/CLEAR
   got a cc0, and just put the FSM back to IDLE. It becomes too unwieldy
   to discern which operation an interrupt is completing, and whether
   more interrupts are expected, to be worth the additional state.
 - A successful CSCH doesn't do anything special, and cp_free()
   is only performed on the interrupt path. Part of me wrestled with
   how a HALT fits into that, but mostly it was that a cc0 on any
   of the instructions indicated the "channel subsystem is signaled
   to asynchronously perform the [START/HALT/CLEAR] function."
   This means that an in-flight START could still receive data from the
   device/subchannel, so not a good idea to release memory at that point.

Separate from all that, I added a small check of the io_work queue to
the FSM START path. Part of the problems I've seen was that an interrupt
is presented by a CPU, but not yet processed by vfio-ccw. Some of the
problems seen thus far is because of this gap, and the above changes
don't address that either. Whether this is appropriate or ridiculous
would be a welcome discussion.

Previous versions:
v2: https://lore.kernel.org/kvm/20200513142934.28788-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20200124145455.51181-1-farman@linux.ibm.com/

Footnotes:
[1] https://lore.kernel.org/kvm/62e87bf67b38dc8d5760586e7c96d400db854ebe.1562854091.git.alifm@linux.ibm.com/
[2] Halil has pointed out that QEMU should prohibit this, based on the
    rules set forth by the POPs. This is true, but we should not rely on
    it behaving properly without addressing this scenario that is visible
    today. Once I get this behaving correctly, I'll spend some time
    seeing if QEMU is misbehaving somehow.
[3] https://lore.kernel.org/kvm/20200518180903.7cb21dd8.cohuck@redhat.com/
[4] https://lore.kernel.org/kvm/a52368d3-8cec-7b99-1587-25e055228b62@linux.ibm.com/

Eric Farman (3):
  vfio-ccw: Indicate if a channel_program is started
  vfio-ccw: Remove the CP_PENDING FSM state
  vfio-ccw: Check workqueue before doing START

 drivers/s390/cio/vfio_ccw_cp.c      |  2 ++
 drivers/s390/cio/vfio_ccw_cp.h      |  1 +
 drivers/s390/cio/vfio_ccw_drv.c     |  5 +----
 drivers/s390/cio/vfio_ccw_fsm.c     | 32 +++++++++++++++++------------
 drivers/s390/cio/vfio_ccw_ops.c     |  3 +--
 drivers/s390/cio/vfio_ccw_private.h |  1 -
 6 files changed, 24 insertions(+), 20 deletions(-)
```
#### [RFC PATCH 0/3] kvm,x86: Improve kvm page fault error handling
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
From patchwork Tue Jun 16 21:48:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11608715
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E7C3913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:49:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C94D20C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:49:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Rg9C1Stk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726454AbgFPVtd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 17:49:33 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:35136 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726311AbgFPVtQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 17:49:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592344154;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uv780jpNQSYzquFkmBB1m3mWJ1oYSVcoXMxNLu+Q8MQ=;
        b=Rg9C1Stka9T5KHBzH1e0vJi5ep0klrGSWjHxzpapBn87iQ9N8k8n2bMPbhU+LgNxfUSBlS
        ++ZiA61XnjsCNWNwh/KLiqYSusbLc/mDg75JC1H/L6+S2cNi15/p9OrTVcxCJZapxnAraF
        0XakA0vcFblYcZRNGnqOaAXrjPuzqik=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-E7zfeKlANEm4BKAq4l_3xQ-1; Tue, 16 Jun 2020 17:49:11 -0400
X-MC-Unique: E7zfeKlANEm4BKAq4l_3xQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D7A0C872FF2;
        Tue, 16 Jun 2020 21:49:09 +0000 (UTC)
Received: from horse.redhat.com (ovpn-114-132.rdu2.redhat.com [10.10.114.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7E62360BE2;
        Tue, 16 Jun 2020 21:49:03 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id C17E522363A; Tue, 16 Jun 2020 17:49:02 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, vgoyal@redhat.com, vkuznets@redhat.com,
        pbonzini@redhat.com, wanpengli@tencent.com,
        sean.j.christopherson@intel.com
Subject: [RFC PATCH 0/3] kvm,x86: Improve kvm page fault error handling
Date: Tue, 16 Jun 2020 17:48:44 -0400
Message-Id: <20200616214847.24482-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is an RFC patch series to improve error handling. Compiled and
tested only on x86. Have not tested or thought about nested
configuration yet.

This is built on top of Vitaly's patches sending "page ready" events
using interrupts. But it has not been rebased on top of recent
interrupt rework yet. Patches are also available here.

https://github.com/rhvgoyal/linux/commits/asyncpf-error-v1

Problem
=======
Currently kvm page fault error handling seems very unpredictable. If
a page fault fails and kvm decided not to do async page fault, then
upon error, we exit to user space and qemu prints
"error: kvm run failed Bad address" and associated cpu state and VM
freezes.

But if kvm decided to async page fault, then async_pf_execute() simply
ignores the error code (-EFAULT) returned by get_user_pages_remote()
and injects "page ready" event into guest. Guest retries the faulting
instruction and takes exit again and kvm again retries async page
fault and this cycle continues and forms an infinite loop.

I can reproduce this -EFAULT situation easily. Created a file
(nvdimm.img) and exported it to guest as nvdimm device. Inside the guest
created ext4 filesystem on device and mounted with dax enabled. Now mmap a
file (/mnt/pmem0/foo.txt) and load from it one page at a time. Also
truncate nvdimm.img on host. So when guest tries to load from nvdimm,
its not mapped in page tables anymore (due to truncation) and we take
exit and try to fault in the page. Now we either exit to user space
with bad address or and get into infinite loop depending on state of
filesystem in guest whether at the time of exit we were in kernel mode
or user space mode.

I am implementing DAX support in virtiofs (which is very close to what
nvdimm will do) and I have scenarios where a DAX mapped file in guest
can get truncated on host and page fault errors can happen. I need to
do better error handling instead of guest and host spinning infinitely.
It otherwise sort of creates an attack vector where a kata container
has to mount virtiofs using DAX, mmap a file, and then truncate that
file on host and then access it inside guest and we can hog kvm on
host in this infinite loop of trying to fault in page.

Proposed Solution
=================
So first idea is that how about we make the error behavior uniform. That
is when an error is encountered, we exit to qemu which prints the
error message and VM freezes. That will end the discrepancy in the
behavior of sync/async page fault. First patch of the series does
that.

Second idea is that if we are doing async page fault and if guest is
in a state so that we can inject "page not present" and "page ready"
events, then instead of exiting to user space, send error back to
guest as part of "page ready" event. This will allow guest to do
finer grained error handling. For example, send SIGBUS to offending
process. And whole of the VM does not have to go down. Second patch
implemented it.

Third idea is that find a way to inject error even when async page
fault can't be injected. Now if we disabled any kind of async page
fault delivery if guest is in kernel mode because this was racy.
Once we figure out a race free way  to be able to inject page
fault in guest (using #VE?), then use that to report errors back
to guest even when it is in kernel mode. And that will allow
guest to call fixup_exception() and possibly recover from situation
otherwise panic(). This can only be implemented once we have a
way race free way to inject an async page event into guest. So this
is a future TBD item. For now, if we took exit and guest is in kernel
mode and error happened, we will vcpu_run() will fail and exit
to user space.  

I have only compiled and tested this series on x86. Before I refine
it further, wanted to post it for some feedback and see if this
the right direction or not.

Any feedback or comments are welcome.

Thanks
Vivek 

Vivek Goyal (3):
  kvm,x86: Force sync fault if previous attempts failed
  kvm: Add capability to be able to report async pf error to guest
  kvm, async_pf: Use FOLL_WRITE only for write faults

 Documentation/virt/kvm/cpuid.rst     |  4 +++
 Documentation/virt/kvm/msr.rst       | 10 +++---
 arch/x86/include/asm/kvm_host.h      |  4 +++
 arch/x86/include/asm/kvm_para.h      |  8 ++---
 arch/x86/include/uapi/asm/kvm_para.h | 10 ++++--
 arch/x86/kernel/kvm.c                | 34 +++++++++++++++----
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/mmu.h                   |  2 +-
 arch/x86/kvm/mmu/mmu.c               | 11 ++++---
 arch/x86/kvm/x86.c                   | 49 +++++++++++++++++++++++-----
 include/linux/kvm_host.h             |  5 ++-
 virt/kvm/async_pf.c                  | 15 +++++++--
 12 files changed, 119 insertions(+), 36 deletions(-)
```
#### [PATCH v2 0/3] INVPCID support for the AMD guests
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Tue Jun 16 22:03:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11608721
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB370138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D52020C09
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:03:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="g3G5ILDc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726349AbgFPWDh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 18:03:37 -0400
Received: from mail-mw2nam12on2054.outbound.protection.outlook.com
 ([40.107.244.54]:8672
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725901AbgFPWDg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 18:03:36 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=XxPRaytk1dl+tywJR/gPwab/F+lBcPU2gRw4LOed7c0E73CI3s16cX2Bgo740Qrkj56dKtUkRCYakuG+tzW0+BokAdFzDS9eiRIFuPD7UXw7Ev2J4OKT9E29tFX/ApvObwJSu3lmdZcCuFFspbmfhiUoLW4KR8DiwkxmXTE57K32uSrYUip9hcmo6gKmZIyo+euogPZtj9VjxRpbsqA5rDidTZ+Ivc9YoFtTs0ke016AZfqkNlCuS/fLXpkiafL8am19ozGat2QrSSHFdYlXEOT1SqoOcmAJ0F8fdHW+utyhmdw+ZLzsrq6FfuURga/6SCAvkw4bI074OoPSbWEnag==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UJtnPHwqrwsPthAoJRJfVCpS5cTAILQJ6MpaOqbjKME=;
 b=n/Tqygc+qw22Klb+xCnferPzqI2r+4/iC7Q+YKSTdng8Q0Sbvxq16jdWiERp5HbpZXVF4DdUFzFzNJ6F6eYZvNhqf/uCnYPXCS7z9H1drqm3yeCHsLhh4sQX5xfjt6eTLAqxnFZh518uoj72+EdJseFGyQNk/KkfUXzgTG/YlmBNpENUmd9Clp4SClhymSZ83pf5/0tWxumqlX5t348GQ703YnWSXIpDGA4JGyRBPD+jZoPtRBhvIyNGbiGka5P1uI9iWXY9U2aTo0Ry6gXGHZ++HD/TXG8723ZBJxEPK8L6RKCFlp6NfjpXfPJk1fRKWc5ZT0ezzUvJv6sw5ZPzew==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=UJtnPHwqrwsPthAoJRJfVCpS5cTAILQJ6MpaOqbjKME=;
 b=g3G5ILDcGm4XTY4k416yz5coVUmTHVjtxNn5K+svc9Jr2iJPbrgKqy95coNAkzcf9a0/pE7RSo3BsRHGxebV/gKnzid2fger/SjQZfikr+sGc2nZTWwHvNdhIOsolUHU5cvQ+MtlJUgsIz3tCnhsgS4CgXpv6x2fETNSUIVqOeE=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB2622.namprd12.prod.outlook.com (2603:10b6:805:72::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.18; Tue, 16 Jun
 2020 22:03:32 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2%3]) with mapi id 15.20.3088.029; Tue, 16 Jun 2020
 22:03:31 +0000
Subject: [PATCH v2 0/3] INVPCID support for the AMD guests
From: Babu Moger <babu.moger@amd.com>
To: wanpengli@tencent.com, joro@8bytes.org, x86@kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, vkuznets@redhat.com,
        tglx@linutronix.de, jmattson@google.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Tue, 16 Jun 2020 17:03:29 -0500
Message-ID: <159234483706.6230.13753828995249423191.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: DM5PR04CA0072.namprd04.prod.outlook.com
 (2603:10b6:3:ef::34) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 DM5PR04CA0072.namprd04.prod.outlook.com (2603:10b6:3:ef::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3109.21 via Frontend
 Transport; Tue, 16 Jun 2020 22:03:30 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f1f4adb1-2d81-4be5-9984-08d812411b5e
X-MS-TrafficTypeDiagnostic: SN6PR12MB2622:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2622FF7E36867C7F74637479959D0@SN6PR12MB2622.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-Forefront-PRVS: 04362AC73B
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 uoUzP+oP559/HakRXlW2/GW91fQzxGl57qS3EdxXsysTfe3r69tYOXkprnvOdbGWto8FIzD5vVjXH2AptYYs0zYL0dTFWZpVeLkrjEHUGV+VPTVbv5OEFSBkC8NHLMF4iNstP0Z7GwyqM/fesl6ZjLxPr8AN4KMvmUs0TEJwcyJGdMIJFSvyrA96cdEc7mtai9XJ8Hrvzb/DwDkddzBUE7yetuKDf7UuHslWny9kgRdnGBSoSYP8nubN6X/ROVHhk9pC79f8wSgBIKv9/VtQnrO2QDwIZuE83kKuKhtMcWBJ98gPuvcM3+ORT+v32PJqJxvYuLBQBSvcmtvEygMMH5MI1K48QOJ9n9y6oyeai/O7nyb2bDMlVj3glQ5CaClaXBaTEgFRLapkCaE3nwDnZJdMOa9rQMDsc0FELG9hlzYUuCwP9Q3dZekXy+9VzaRH
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(7916004)(366004)(39860400002)(136003)(396003)(376002)(346002)(7416002)(8676002)(83380400001)(478600001)(5660300002)(16576012)(966005)(8936002)(186003)(4326008)(103116003)(16526019)(2906002)(316002)(26005)(66476007)(66946007)(66556008)(956004)(33716001)(6486002)(9686003)(44832011)(52116002)(86362001)(921003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 1+wtB8g7g/LKTQ3pFouINuKeHxL/vqnm7fgRXMfoU3eXup4IVzEswuhV+skJ4F/rYYNmIXG9OLQXRgjANTfjgBZ6r26anJtchMMjX9F5ISCYHbu2f2bzFnK6IKx53bBeDi82uasr2FMpxUQn0TiZlTW/AfPb3ViQsTiz9+wS2MsoOo7E213/trclvpVHwwynDLIZxqn1DM9PvPFddxQvM3VGUDO0vqwf2ErRYb7Oy7T4wcQNhHEsSKlP7gJz1Z+enOqpHFddC6C5iWhYa3ELuCKlJYD/1Q/t+aS0RUKcQsrDGJ5OxydIMvkHKg6/YZV52rB1jx9zY2SsCu9H3GTQj3AjCOpP3G35QmNplLEFkXPSVccQDWu8SPlmdBCO/wkDX5lFjrTSOhcALGZihAt9C7hACTrV0ZVOrQSx88wh4IwLMlm0fvqczQEZuEK32wjcwArIVJQbsBaDm49D2TZz/KGLSUBzY3fw9BDeiPOB+cc=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f1f4adb1-2d81-4be5-9984-08d812411b5e
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Jun 2020 22:03:31.6922
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Bv8F+ISttHuDZHkqvj2CEsAKABIORlF6VBmzyk+A6OjWDlsLpJvZfQ8APTg6J1D1
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2622
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following series adds the support for PCID/INVPCID on AMD guests.

For the guests with nested page table (NPT) support, the INVPCID
feature works as running it natively. KVM does not need to do any
special handling in this case.

INVPCID interceptions are added only when the guest is running with
shadow page table enabled. In this case the hypervisor needs to
handle the tlbflush based on the type of invpcid instruction type.

AMD documentation for INVPCID feature is available at "AMD64
Architecture Programmer’s Manual Volume 2: System Programming,
Pub. 24593 Rev. 3.34(or later)"

The documentation can be obtained at the links below:
Link: https://www.amd.com/system/files/TechDocs/24593.pdf
Link: https://bugzilla.kernel.org/show_bug.cgi?id=206537
---
v2:
  - Taken care of few comments from Jim Mattson.
  - KVM interceptions added only when tdp is off. No interceptions
    when tdp is on.
  - Reverted the fault priority to original order.sed the 
  
v1:
  https://lore.kernel.org/lkml/159191202523.31436.11959784252237488867.stgit@bmoger-ubuntu/

Babu Moger (3):
      KVM: X86: Move handling of INVPCID types to x86
      KVM:SVM: Add extended intercept support
      KVM:SVM: Enable INVPCID feature on AMD


 arch/x86/include/asm/svm.h      |    7 +++
 arch/x86/include/uapi/asm/svm.h |    2 +
 arch/x86/kvm/svm/nested.c       |    6 ++-
 arch/x86/kvm/svm/svm.c          |   55 +++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.h          |   18 +++++++++
 arch/x86/kvm/trace.h            |   12 ++++--
 arch/x86/kvm/vmx/vmx.c          |   68 ----------------------------------
 arch/x86/kvm/x86.c              |   79 +++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              |    3 +
 9 files changed, 176 insertions(+), 74 deletions(-)

--
Signature
```
