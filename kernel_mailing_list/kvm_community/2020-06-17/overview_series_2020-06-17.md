#### [PATCH v5 5/7] arm64: kvm: pmu: Make overflow handler NMI safe
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11609739
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00E3660D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 11:38:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4AA620DD4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 11:38:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726958AbgFQLig (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 07:38:36 -0400
Received: from foss.arm.com ([217.140.110.172]:56306 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726980AbgFQLid (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 07:38:33 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 8816F1045;
        Wed, 17 Jun 2020 04:38:32 -0700 (PDT)
Received: from monolith.arm.com (unknown [10.37.8.7])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 14DF43F71F;
        Wed, 17 Jun 2020 04:38:29 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org
Cc: maz@kernel.org, will@kernel.org, catalin.marinas@arm.com,
        mark.rutland@arm.com, Julien Thierry <julien.thierry@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Marc Zyngier <marc.zyngier@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Pouloze <suzuki.poulose@arm.com>,
        Will Deacon <will.deacon@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [PATCH v5 5/7] arm64: kvm: pmu: Make overflow handler NMI safe
Date: Wed, 17 Jun 2020 12:38:49 +0100
Message-Id: <20200617113851.607706-6-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200617113851.607706-1-alexandru.elisei@arm.com>
References: <20200617113851.607706-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Julien Thierry <julien.thierry@arm.com>

kvm_vcpu_kick() is not NMI safe. When the overflow handler is called from
NMI context, defer waking the vcpu to an irq_work queue.

Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: James Morse <james.morse@arm.com>
Cc: Suzuki K Pouloze <suzuki.poulose@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: kvmarm@lists.cs.columbia.edu
Cc: kvm@vger.kernel.org
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arch/arm64/kvm/pmu-emul.c | 25 ++++++++++++++++++++++++-
 include/kvm/arm_pmu.h     |  1 +
 2 files changed, 25 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: s390: reduce number of IO pins to 1
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11609451
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3B3A90
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 08:36:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 958532100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 08:36:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726729AbgFQIg2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 04:36:28 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:22684 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726280AbgFQIg1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Jun 2020 04:36:27 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05H8VjBM092449;
        Wed, 17 Jun 2020 04:36:26 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31q6hdebe8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 04:36:26 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05H8VlWD092647;
        Wed, 17 Jun 2020 04:36:25 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31q6hdebdm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 04:36:25 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05H8VJ9N022432;
        Wed, 17 Jun 2020 08:36:24 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma05fra.de.ibm.com with ESMTP id 31q6c8r97v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 08:36:24 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05H8aMXV64684036
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 17 Jun 2020 08:36:22 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E24CA4C04A;
        Wed, 17 Jun 2020 08:36:21 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CD9BC4C040;
        Wed, 17 Jun 2020 08:36:21 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 17 Jun 2020 08:36:21 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 59558E027E; Wed, 17 Jun 2020 10:36:21 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: s390: reduce number of IO pins to 1
Date: Wed, 17 Jun 2020 10:36:20 +0200
Message-Id: <20200617083620.5409-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-16_13:2020-06-16,2020-06-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 phishscore=0
 mlxscore=0 priorityscore=1501 cotscore=-2147483648 malwarescore=0
 suspectscore=2 clxscore=1015 lowpriorityscore=0 mlxlogscore=999
 spamscore=0 impostorscore=0 bulkscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006170063
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current number of KVM_IRQCHIP_NUM_PINS results in an order 3
allocation (32kb) for each guest start/restart. This can result in OOM
killer activity even with free swap when the memory is fragmented
enough:

kernel: qemu-system-s39 invoked oom-killer: gfp_mask=0x440dc0(GFP_KERNEL_ACCOUNT|__GFP_COMP|__GFP_ZERO), order=3, oom_score_adj=0
kernel: CPU: 1 PID: 357274 Comm: qemu-system-s39 Kdump: loaded Not tainted 5.4.0-29-generic #33-Ubuntu
kernel: Hardware name: IBM 8562 T02 Z06 (LPAR)
kernel: Call Trace:
kernel: ([<00000001f848fe2a>] show_stack+0x7a/0xc0)
kernel:  [<00000001f8d3437a>] dump_stack+0x8a/0xc0
kernel:  [<00000001f8687032>] dump_header+0x62/0x258
kernel:  [<00000001f8686122>] oom_kill_process+0x172/0x180
kernel:  [<00000001f8686abe>] out_of_memory+0xee/0x580
kernel:  [<00000001f86e66b8>] __alloc_pages_slowpath+0xd18/0xe90
kernel:  [<00000001f86e6ad4>] __alloc_pages_nodemask+0x2a4/0x320
kernel:  [<00000001f86b1ab4>] kmalloc_order+0x34/0xb0
kernel:  [<00000001f86b1b62>] kmalloc_order_trace+0x32/0xe0
kernel:  [<00000001f84bb806>] kvm_set_irq_routing+0xa6/0x2e0
kernel:  [<00000001f84c99a4>] kvm_arch_vm_ioctl+0x544/0x9e0
kernel:  [<00000001f84b8936>] kvm_vm_ioctl+0x396/0x760
kernel:  [<00000001f875df66>] do_vfs_ioctl+0x376/0x690
kernel:  [<00000001f875e304>] ksys_ioctl+0x84/0xb0
kernel:  [<00000001f875e39a>] __s390x_sys_ioctl+0x2a/0x40
kernel:  [<00000001f8d55424>] system_call+0xd8/0x2c8

As far as I can tell s390x does not use the iopins as we bail our for
anything other than KVM_IRQ_ROUTING_S390_ADAPTER and the chip/pin is
only used for KVM_IRQ_ROUTING_IRQCHIP. So let us use a small number to
reduce the memory footprint.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/include/asm/kvm_host.h | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Add control register pinning tests
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11610903
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F15190
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 22:45:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DCBC20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 22:45:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726868AbgFQWpv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 18:45:51 -0400
Received: from mga05.intel.com ([192.55.52.43]:53485 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726758AbgFQWpv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 18:45:51 -0400
IronPort-SDR: 
 jE+3Zzy3UxOl0113uuOT4n62/KHMIkIt5VKr9DLphaJzvL5Tab2yA9sQwkE/FXHWfEUklkEg2y
 e1AevyLwEN1g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jun 2020 15:42:49 -0700
IronPort-SDR: 
 mATNKog+YMK35Q7xYUZBTY7Xqru1/CGKBn5q/XqFkJFc6SXEEyz9JCQwnr59GrPnJgG5aKf8R2
 /F8LTlOwQPyA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,523,1583222400";
   d="scan'208";a="263433428"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga008.fm.intel.com with ESMTP; 17 Jun 2020 15:42:48 -0700
From: John Andersen <john.s.andersen@intel.com>
To: corbet@lwn.net, pbonzini@redhat.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, shuah@kernel.org,
        sean.j.christopherson@intel.com, rick.p.edgecombe@intel.com,
        kvm@vger.kernel.org
Cc: john.s.andersen@intel.com, kernel-hardening@lists.openwall.com
Subject: [kvm-unit-tests PATCH] x86: Add control register pinning tests
Date: Wed, 17 Jun 2020 15:46:06 -0700
Message-Id: <20200617224606.27954-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paravirutalized control register pinning adds MSRs guests can use to
discover which bits in CR0/4 they may pin, and MSRs for activating
pinning for any of those bits.

We check that the bits allowed to be pinned for CR4 are UMIP, SMEP, and
SMAP. Only WP should be allowed to be pinned in CR0.

We turn on all of the allowed bits, pin them, then attempt to disable
them. We verify that the attempt to disable was unsuccessful, and that
it generated a general protection fault.

For nested, we check that for when pinning enabled in L1, changing
HOST_CR0/4 will not result in the un-setting of pinned bits. The VMX CR
pinning tests is it's own test so that the pinning doesn't potentially
affect other tests within the same .flat testing VM.

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 x86/Makefile.common |   3 +-
 lib/x86/desc.h      |   1 +
 lib/x86/msr.h       |   8 ++
 lib/x86/processor.h |   1 +
 lib/x86/desc.c      |   8 ++
 x86/cr_pin_high.c   | 185 ++++++++++++++++++++++++++++++++++++++++++++
 x86/cr_pin_low.c    |  55 +++++++++++++
 x86/pcid.c          |   8 --
 x86/vmx_tests.c     | 138 +++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |  16 +++-
 10 files changed, 413 insertions(+), 10 deletions(-)
 create mode 100644 x86/cr_pin_high.c
 create mode 100644 x86/cr_pin_low.c

```
#### [kvm-unit-tests PATCH] x86: fix build with GCC10
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11610143
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 950A813B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 15:21:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BA9820734
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 15:21:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NmkTCxE4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726761AbgFQPVd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 11:21:33 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:40299 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726491AbgFQPVd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Jun 2020 11:21:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592407291;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oLO6rZ7Kgav5d6Xjpk0xbKq2RZwg420FPPXpydpe5Bc=;
        b=NmkTCxE4M3X0vPRrNkpwPwKR4aaABixGgHCX+we5AZQAEkmQGdaJ6K1g+E+3Lv295bpGmu
        ndbrC9UUzT2Aij4rI65GxjOwMIXWIMys2+3HcRMcTnYzVt7RVl9JkDHVdS15r9lzYS1fuT
        DiB0dJflAq3Z1cTyZNEq3yEyjSJnqbw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-496-93NMQDC8Nr6RVG9W2nZ9-Q-1; Wed, 17 Jun 2020 11:21:29 -0400
X-MC-Unique: 93NMQDC8Nr6RVG9W2nZ9-Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2650C803302
        for <kvm@vger.kernel.org>; Wed, 17 Jun 2020 15:21:28 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.196.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A9DFE7CADF;
        Wed, 17 Jun 2020 15:21:25 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH] x86: fix build with GCC10
Date: Wed, 17 Jun 2020 17:21:24 +0200
Message-Id: <20200617152124.402765-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm-unit-tests fail to build with GCC10:

/usr/bin/ld: lib/libcflat.a(usermode.o):
  ./kvm-unit-tests/lib/x86/usermode.c:17:  multiple definition of `jmpbuf';
 lib/libcflat.a(fault_test.o):
  ./kvm-unit-tests/lib/x86/fault_test.c:3: first defined here

It seems that 'jmpbuf' doesn't need to be global in either of these files,
make it static in both.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 lib/x86/fault_test.c | 2 +-
 lib/x86/usermode.c   | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: skip hyperv_clock test when host clocksource is not TSC
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11610147
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1678F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 15:22:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F388620897
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 15:22:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bjX6oLqD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726886AbgFQPWI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 11:22:08 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:34213 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726815AbgFQPWH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 11:22:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592407320;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zVWEhzXPRli8YcvMsJuZOhmzlxl40/jDyj4c8Sv7fu4=;
        b=bjX6oLqDsLTtHZEK3XDRZd4NkoyqkFGxLB9fSjb1/XY7f0HDKo5UG3FhHh/kirpQ62aNjB
        +1/hs8wpn0mH13e1KTKKvd1+2+nC9mzKBghWqOqZp2QEVFL3hVkVULIDLrFgvnFw92tZZ2
        0gt+U8ghcaI1jMnXDyMp4Vm72pFVNqk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-294-IljxjI3PNjKj_CeWVvaEDw-1; Wed, 17 Jun 2020 11:21:57 -0400
X-MC-Unique: IljxjI3PNjKj_CeWVvaEDw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4E6C010AEA27
        for <kvm@vger.kernel.org>; Wed, 17 Jun 2020 15:21:41 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.196.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5465B75E11;
        Wed, 17 Jun 2020 15:21:40 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH] x86: skip hyperv_clock test when host
 clocksource is not TSC
Date: Wed, 17 Jun 2020 17:21:39 +0200
Message-Id: <20200617152139.402827-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-V TSC page clocksource is TSC based so it requires host to use TSC
for clocksource. While TSC is more or less standard for x86 hardware
nowadays, when kvm-unit-tests are run in a VM the clocksource tends to be
different (e.g. kvm-clock).

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/unittests.cfg | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: VMX: Remove vcpu_vmx's defunct copy of host_pkru
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11608977
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 62CF8913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 03:41:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C9B820870
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 03:41:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726795AbgFQDlZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 23:41:25 -0400
Received: from mga01.intel.com ([192.55.52.88]:52603 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726497AbgFQDlZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 23:41:25 -0400
IronPort-SDR: 
 dn648OMM6fiiGGXoX67YKFvqmLIsxO9YidWKl2N1+4pLfC5Kodvb19wA/6duW9kfOxm5L7mv31
 7v0aRtT2YhtQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Jun 2020 20:41:25 -0700
IronPort-SDR: 
 yD9c5qPCcw0nP5vDwu24s9gyXkO/DttkWnkRWj5wM2HuyxcvjgAB/UB7ij1AxJLzjfzqTRK9/w
 jcHjjDhLRfQA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,521,1583222400";
   d="scan'208";a="476681552"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 16 Jun 2020 20:41:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Remove vcpu_vmx's defunct copy of host_pkru
Date: Tue, 16 Jun 2020 20:41:23 -0700
Message-Id: <20200617034123.25647-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove vcpu_vmx.host_pkru, which got left behind when PKRU support was
moved to common x86 code.

No functional change intended.

Fixes: 37486135d3a7b ("KVM: x86: Fix pkru save/restore when guest CR4.PKE=0, move it to x86.c")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.h | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH 1/4] X86: Update mmu_cr4_features during feature identification
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11610449
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC34C13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 19:05:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F93B21789
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 19:05:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726867AbgFQTFK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 15:05:10 -0400
Received: from mga04.intel.com ([192.55.52.120]:48978 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726511AbgFQTFJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 15:05:09 -0400
IronPort-SDR: 
 AaiEpV1M2bHzO3SoB3gB0kDeMlLcmFiso+sqionkh6V0Y2sUWRjKZOjqQBSZhXw+wVZKAlu31Y
 MBkvjzRcaAIA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jun 2020 12:05:09 -0700
IronPort-SDR: 
 XaTM/0pxYcUKBtQfhnD+idd+M4VFhRN/WvrCorf4TvEgLkY2ri0Xu/TSQT3k5nLvh2ixTBEmy0
 BGSU6Y+wGWJA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,523,1583222400";
   d="scan'208";a="273609601"
Received: from gza.jf.intel.com ([10.54.75.28])
  by orsmga003.jf.intel.com with ESMTP; 17 Jun 2020 12:05:07 -0700
From: John Andersen <john.s.andersen@intel.com>
To: corbet@lwn.net, pbonzini@redhat.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        shuah@kernel.org, sean.j.christopherson@intel.com,
        liran.alon@oracle.com, drjones@redhat.com,
        rick.p.edgecombe@intel.com, kristen@linux.intel.com
Cc: vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, mchehab+huawei@kernel.org,
        gregkh@linuxfoundation.org, paulmck@kernel.org,
        pawan.kumar.gupta@linux.intel.com, jgross@suse.com,
        mike.kravetz@oracle.com, oneukum@suse.com, luto@kernel.org,
        peterz@infradead.org, fenghua.yu@intel.com,
        reinette.chatre@intel.com, vineela.tummalapalli@intel.com,
        dave.hansen@linux.intel.com, john.s.andersen@intel.com,
        arjan@linux.intel.com, caoj.fnst@cn.fujitsu.com, bhe@redhat.com,
        nivedita@alum.mit.edu, keescook@chromium.org,
        dan.j.williams@intel.com, eric.auger@redhat.com,
        aaronlewis@google.com, peterx@redhat.com,
        makarandsonare@google.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org,
        kernel-hardening@lists.openwall.com
Subject: [PATCH 1/4] X86: Update mmu_cr4_features during feature
 identification
Date: Wed, 17 Jun 2020 12:07:54 -0700
Message-Id: <20200617190757.27081-2-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20200617190757.27081-1-john.s.andersen@intel.com>
References: <20200617190757.27081-1-john.s.andersen@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In identify_cpu when setting up SMEP/SMAP/UMIP call
cr4_set_bits_and_update_boot instead of cr4_set_bits. This ensures that
mmu_cr4_features contains those bits, and does not disable those
protections when in hibernation asm.

setup_arch updates mmu_cr4_features to save what identified features are
supported for later use in hibernation asm when cr4 needs to be modified
to toggle PGE. cr4 writes happen in restore_image and restore_registers.
setup_arch occurs before identify_cpu, this leads to mmu_cr4_features
not containing some of the cr4 features which were enabled via
identify_cpu when hibernation asm is executed.

On CPU bringup when cr4_set_bits_and_update_boot is called
mmu_cr4_features will now be written to. For the boot CPU,
the __ro_after_init on mmu_cr4_features does not cause a fault. However,
__ro_after_init was removed due to it triggering faults on non-boot
CPUs.

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 arch/x86/kernel/cpu/common.c | 6 +++---
 arch/x86/kernel/setup.c      | 4 ++--
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v10 20/73] i386: convert to cpu_halted
##### From: Robert Foley <robert.foley@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Robert Foley <robert.foley@linaro.org>
X-Patchwork-Id: 11610561
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F00C814B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 21:03:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCBDD21883
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 21:03:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="R5z5IR5F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726949AbgFQVDs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 17:03:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35672 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726840AbgFQVDr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jun 2020 17:03:47 -0400
Received: from mail-qk1-x742.google.com (mail-qk1-x742.google.com
 [IPv6:2607:f8b0:4864:20::742])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 11849C06174E
        for <kvm@vger.kernel.org>; Wed, 17 Jun 2020 14:03:46 -0700 (PDT)
Received: by mail-qk1-x742.google.com with SMTP id b4so3456377qkn.11
        for <kvm@vger.kernel.org>; Wed, 17 Jun 2020 14:03:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Rba7pljRMVc6wa2lS86kVUPY7O/d9hkT9SFA7+vY6nY=;
        b=R5z5IR5FLnMnMqf2RggbF8wnsY2icPxT3w46kmMuEmy69k/4Mr4UNe+RuR+WiEPvG3
         9c8CJRRyY7m6nltryWkmWziQvRZfYasj4SE4VArK46KiVyJ+gazqevXOxXuZqTuDay8U
         9X86q5vyz5COzSuzfdMrSntdJ3rZjYQt7Eq5Lt1dQttkcMCrcVV8Vo1J9H6x1Btp9rjo
         6Sr1nzX1mKh5hhoW25c15laX42Nri5JALP/VjoR4EXVD56IZn2Zv6dyI+FR9L/LqrxXz
         fbXETyMyprillHLMW8zUjP4+c2fyHOBDmvmInXSFqQ+yIOGH5Gtlr4YE5cLe6r/hZBmA
         uerw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Rba7pljRMVc6wa2lS86kVUPY7O/d9hkT9SFA7+vY6nY=;
        b=ZcgoxfBSGK6CLSKG1iowRRDLLhX+bFbnKDzfHDnif1lHpjZKX6P+VqK6cp7VJHj3u5
         1iUfDCNr6w8uvFjNYiwYxyUqxz27hXMuScl0+glbder56WJspW/LajJPzy6UiutEkruu
         mzyZm4v49rJqBFudbr864+7IWY7UcgswWN+aOkhohZ3KbK8HfRkcLRC17z9NZmvbxw0w
         XUADZrGO9vPlOzCk9g8mnllKuLlzFJnUrIwqDZlrk9qT8EtXYTf7Qb21JBy5lxzQ2wY4
         zhZttN4Xjwdwfg3OqRHUO037RcKtG8rXkm4eamEwY29RMuLl8XjTNZHrz3kZePYYO0PC
         czyQ==
X-Gm-Message-State: AOAM533xFOp+gKwprksxSoLeRx5Y8028h1tWeqri3+RFpj3MLYyT0mTN
        b+wQ/Z2aBT8OjHyB0EI8QbMFKA==
X-Google-Smtp-Source: 
 ABdhPJzZuLORD87VxHFuUa7rIS/eYuoX8SDFPbCz5s962zeXaI0xoYOVy9OxMVd8SVfCrJEKucANOw==
X-Received: by 2002:a37:9684:: with SMTP id y126mr589113qkd.348.1592427825231;
        Wed, 17 Jun 2020 14:03:45 -0700 (PDT)
Received: from Rfoley-MA01.hsd1.ma.comcast.net
 ([2601:199:4480:60c0:fc79:714c:9711:2e9c])
        by smtp.gmail.com with ESMTPSA id
 w13sm997245qkb.91.2020.06.17.14.03.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 17 Jun 2020 14:03:44 -0700 (PDT)
From: Robert Foley <robert.foley@linaro.org>
To: qemu-devel@nongnu.org
Cc: alex.bennee@linaro.org, cota@braap.org, peter.puhov@linaro.org,
        robert.foley@linaro.org, Eduardo Habkost <ehabkost@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Wenchao Wang <wenchao.wang@intel.com>,
        Colin Xu <colin.xu@intel.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Sunil Muthuswamy <sunilmut@microsoft.com>,
        haxm-team@intel.com (open list:X86 HAXM CPUs),
        kvm@vger.kernel.org (open list:X86 KVM CPUs)
Subject: [PATCH v10 20/73] i386: convert to cpu_halted
Date: Wed, 17 Jun 2020 17:01:38 -0400
Message-Id: <20200617210231.4393-21-robert.foley@linaro.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200617210231.4393-1-robert.foley@linaro.org>
References: <20200617210231.4393-1-robert.foley@linaro.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Emilio G. Cota" <cota@braap.org>

Cc: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
Signed-off-by: Emilio G. Cota <cota@braap.org>
[RF: Converted new code in i386/hax-all.c to cpu_halted]
Signed-off-by: Robert Foley <robert.foley@linaro.org>
---
 target/i386/cpu.c         |  2 +-
 target/i386/cpu.h         |  2 +-
 target/i386/hax-all.c     |  6 +++---
 target/i386/helper.c      |  4 ++--
 target/i386/hvf/hvf.c     |  4 ++--
 target/i386/hvf/x86hvf.c  |  4 ++--
 target/i386/kvm.c         | 10 +++++-----
 target/i386/misc_helper.c |  2 +-
 target/i386/whpx-all.c    |  6 +++---
 9 files changed, 20 insertions(+), 20 deletions(-)

```
#### [PATCH v3 1/1] s390: virtio: let arch accept devices without IOMMU feature
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11609645
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D8AA138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 10:44:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F34B020FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 10:44:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726881AbgFQKoN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 06:44:13 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24094 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726845AbgFQKoN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Jun 2020 06:44:13 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05HAWLN0072005;
        Wed, 17 Jun 2020 06:44:06 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q6j0j2kg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 06:44:06 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05HAWXWI072752;
        Wed, 17 Jun 2020 06:44:06 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q6j0j2jd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 06:44:05 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05HAa12w018465;
        Wed, 17 Jun 2020 10:44:03 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma02fra.de.ibm.com with ESMTP id 31q6ckrbs2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Jun 2020 10:44:03 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05HAi0sn65733038
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 17 Jun 2020 10:44:00 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 42B2E5205A;
        Wed, 17 Jun 2020 10:44:00 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.186.32])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 6618852054;
        Wed, 17 Jun 2020 10:43:59 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v3 1/1] s390: virtio: let arch accept devices without IOMMU
 feature
Date: Wed, 17 Jun 2020 12:43:57 +0200
Message-Id: <1592390637-17441-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1592390637-17441-1-git-send-email-pmorel@linux.ibm.com>
References: <1592390637-17441-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-17_03:2020-06-17,2020-06-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 adultscore=0
 bulkscore=0 phishscore=0 priorityscore=1501 cotscore=-2147483648
 mlxlogscore=952 lowpriorityscore=0 mlxscore=0 suspectscore=1 clxscore=1015
 malwarescore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006170079
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture protecting the guest memory against unauthorized host
access may want to enforce VIRTIO I/O device protection through the
use of VIRTIO_F_IOMMU_PLATFORM.

Let's give a chance to the architecture to accept or not devices
without VIRTIO_F_IOMMU_PLATFORM.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 arch/s390/mm/init.c     |  6 ++++++
 drivers/virtio/virtio.c | 22 ++++++++++++++++++++++
 include/linux/virtio.h  |  2 ++
 3 files changed, 30 insertions(+)

```
#### [PATCH] target/arm/kvm: Check supported feature per accelerator (not per vCPU)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11609861
Return-Path: <SRS0=0NSc=76=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 803326A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 13:08:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5BFDC2158C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jun 2020 13:08:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RVHdz7kw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726454AbgFQNIJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jun 2020 09:08:09 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:59882 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726134AbgFQNII (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Jun 2020 09:08:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592399286;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=fCMg1kyMR7N+Ov+rmWJLbOZmzhhnmVRoJdGi9LpTDn0=;
        b=RVHdz7kwkzymeFnzd9yLewByyDGKGEfpZuH9TCvpMBFqC9zC7/AO/GmZYZlVSRFyg76GsS
        c9YzNg9tnbw2BRvwFTCXg5WR6x+qjR8g/Kb+e9CXsFRAH6Al47aMbNrIrQwOQtTLziAO8T
        jES857rfFE0/CSqIyoZXc7TrI4P4Wmc=
Received: from mail-ed1-f71.google.com (mail-ed1-f71.google.com
 [209.85.208.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-101-1bie_mK8NnK8pZITc4e_Qw-1; Wed, 17 Jun 2020 09:08:04 -0400
X-MC-Unique: 1bie_mK8NnK8pZITc4e_Qw-1
Received: by mail-ed1-f71.google.com with SMTP id bs22so844927edb.0
        for <kvm@vger.kernel.org>; Wed, 17 Jun 2020 06:08:04 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fCMg1kyMR7N+Ov+rmWJLbOZmzhhnmVRoJdGi9LpTDn0=;
        b=IvJgRFncpTEuFm4vkqv87NQvr6muCY0De+w1uYiwphltnilc8gw5xUJwtk28XPI1M5
         KsZa5kt5X7NQEsL14Bgp1nyl8JAfknP2lv18AZSFoTvIIjSKlqCplP8l9quYSCTSb0eN
         w+1NgqPD0vC6V9u2x2rVnreEh5UH1rx0D0DEKCIqpcbYz7U4w94702Vkmjm1MW2DKe1p
         a0t/Joa95XdXKapwJwOoa1KikMnGojCiKPo5Uq0gc3qflAEQHIk3ORu1Lngq/ndGtS+e
         O49ALrn/RGwH0k4AKv3JQ99rU1CdtlV4xqgCQUwd9cqhfqctBmAQ3Hl6aC2dIY4LLb7h
         WEXw==
X-Gm-Message-State: AOAM533L5AT9AVvtRJrVqjRGYdbPYpCHVm4zNObF6/KxbELI3luEB8U1
        +IW4SXcVAyIv+OL7S1hayOezs7BDhymUOCd65m+lZpd88FttWHLcYOdhTRS3gaNukBdwIpE2cf1
        VyvvfbdWxDfrY
X-Received: by 2002:a17:906:55c9:: with SMTP id
 z9mr7766498ejp.276.1592399283544;
        Wed, 17 Jun 2020 06:08:03 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzqGwZAlp1/5617vMNvkO75RiBgN5ywDU37uIBjmwAxJX74lr3MvZAKptbotXpKIAHgsvXJ8Q==
X-Received: by 2002:a17:906:55c9:: with SMTP id
 z9mr7766472ejp.276.1592399283279;
        Wed, 17 Jun 2020 06:08:03 -0700 (PDT)
Received: from x1w.redhat.com (93.red-83-59-160.dynamicip.rima-tde.net.
 [83.59.160.93])
        by smtp.gmail.com with ESMTPSA id
 ce23sm13475432ejc.53.2020.06.17.06.08.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 17 Jun 2020 06:08:02 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, qemu-arm@nongnu.org,
 kvm@vger.kernel.org, Peter Maydell <peter.maydell@linaro.org>,
 Andrew Jones <drjones@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Haibo Xu <haibo.xu@linaro.org>
Subject: [PATCH] target/arm/kvm: Check supported feature per accelerator (not
 per vCPU)
Date: Wed, 17 Jun 2020 15:08:00 +0200
Message-Id: <20200617130800.26355-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit d70c996df23f, when enabling the PMU we get:

  $ qemu-system-aarch64 -cpu host,pmu=on -M virt,accel=kvm,gic-version=3
  Segmentation fault (core dumped)

  Thread 1 "qemu-system-aar" received signal SIGSEGV, Segmentation fault.
  0x0000aaaaaae356d0 in kvm_ioctl (s=0x0, type=44547) at accel/kvm/kvm-all.c:2588
  2588        ret = ioctl(s->fd, type, arg);
  (gdb) bt
  #0  0x0000aaaaaae356d0 in kvm_ioctl (s=0x0, type=44547) at accel/kvm/kvm-all.c:2588
  #1  0x0000aaaaaae31568 in kvm_check_extension (s=0x0, extension=126) at accel/kvm/kvm-all.c:916
  #2  0x0000aaaaaafce254 in kvm_arm_pmu_supported (cpu=0xaaaaac214ab0) at target/arm/kvm.c:213
  #3  0x0000aaaaaafc0f94 in arm_set_pmu (obj=0xaaaaac214ab0, value=true, errp=0xffffffffe438) at target/arm/cpu.c:1111
  #4  0x0000aaaaab5533ac in property_set_bool (obj=0xaaaaac214ab0, v=0xaaaaac223a80, name=0xaaaaac11a970 "pmu", opaque=0xaaaaac222730, errp=0xffffffffe438) at qom/object.c:2170
  #5  0x0000aaaaab5512f0 in object_property_set (obj=0xaaaaac214ab0, v=0xaaaaac223a80, name=0xaaaaac11a970 "pmu", errp=0xffffffffe438) at qom/object.c:1328
  #6  0x0000aaaaab551e10 in object_property_parse (obj=0xaaaaac214ab0, string=0xaaaaac11b4c0 "on", name=0xaaaaac11a970 "pmu", errp=0xffffffffe438) at qom/object.c:1561
  #7  0x0000aaaaab54ee8c in object_apply_global_props (obj=0xaaaaac214ab0, props=0xaaaaac018e20, errp=0xaaaaabd6fd88 <error_fatal>) at qom/object.c:407
  #8  0x0000aaaaab1dd5a4 in qdev_prop_set_globals (dev=0xaaaaac214ab0) at hw/core/qdev-properties.c:1218
  #9  0x0000aaaaab1d9fac in device_post_init (obj=0xaaaaac214ab0) at hw/core/qdev.c:1050
  ...
  #15 0x0000aaaaab54f310 in object_initialize_with_type (obj=0xaaaaac214ab0, size=52208, type=0xaaaaabe237f0) at qom/object.c:512
  #16 0x0000aaaaab54fa24 in object_new_with_type (type=0xaaaaabe237f0) at qom/object.c:687
  #17 0x0000aaaaab54fa80 in object_new (typename=0xaaaaabe23970 "host-arm-cpu") at qom/object.c:702
  #18 0x0000aaaaaaf04a74 in machvirt_init (machine=0xaaaaac0a8550) at hw/arm/virt.c:1770
  #19 0x0000aaaaab1e8720 in machine_run_board_init (machine=0xaaaaac0a8550) at hw/core/machine.c:1138
  #20 0x0000aaaaaaf95394 in qemu_init (argc=5, argv=0xffffffffea58, envp=0xffffffffea88) at softmmu/vl.c:4348
  #21 0x0000aaaaaada3f74 in main (argc=<optimized out>, argv=<optimized out>, envp=<optimized out>) at softmmu/main.c:48

This is because in frame #2, cpu->kvm_state is still NULL
(the vCPU is not yet realized).

KVM has a hard requirement of all cores supporting the same
feature set. We only need to check if the accelerator supports
a feature, not each vCPU individually.

Fix by kvm_arm_<FEATURE>_supported() functions take a AccelState
argument (already realized/valid at this point) instead of a
CPUState argument.

Reported-by: Haibo Xu <haibo.xu@linaro.org>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 target/arm/kvm_arm.h | 25 +++++++++++++------------
 target/arm/cpu.c     |  2 +-
 target/arm/cpu64.c   | 10 +++++-----
 target/arm/kvm.c     |  4 ++--
 target/arm/kvm64.c   | 14 +++++---------
 5 files changed, 26 insertions(+), 29 deletions(-)

```
