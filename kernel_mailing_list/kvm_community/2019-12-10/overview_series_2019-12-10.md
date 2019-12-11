#### [RFC PATCH v9 1/8] arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11281263
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D66E3138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 03:40:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF84D2077B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 03:40:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726930AbfLJDkq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Dec 2019 22:40:46 -0500
Received: from foss.arm.com ([217.140.110.172]:55832 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726623AbfLJDkq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Dec 2019 22:40:46 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 848601045;
        Mon,  9 Dec 2019 19:40:45 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 C032A3F52E;
        Mon,  9 Dec 2019 19:40:39 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>
Subject: [RFC PATCH v9 1/8] arm/arm64: smccc/psci: add
 arm_smccc_1_1_get_conduit()
Date: Tue, 10 Dec 2019 11:40:19 +0800
Message-Id: <20191210034026.45229-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191210034026.45229-1-jianyong.wu@arm.com>
References: <20191210034026.45229-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mark Rutland <mark.rutland@arm.com>

SMCCC callers are currently amassing a collection of enums for the SMCCC
conduit, and are having to dig into the PSCI driver's internals in order
to figure out what to do.

Let's clean this up, with common SMCCC_CONDUIT_* definitions, and an
arm_smccc_1_1_get_conduit() helper that abstracts the PSCI driver's
internal state.

We can kill off the PSCI_CONDUIT_* definitions once we've migrated users
over to the new interface.

Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Acked-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Acked-by: Will Deacon <will.deacon@arm.com>
Signed-off-by: Catalin Marinas <catalin.marinas@arm.com>
---
 drivers/firmware/psci/psci.c | 15 +++++++++++++++
 include/linux/arm-smccc.h    | 16 ++++++++++++++++
 2 files changed, 31 insertions(+)

```
#### [PATCH] kvm: Refactor handling of VM debugfs files
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11282917
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9709138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 16:08:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 98D4B20828
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 16:08:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="Mh+0ErAW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727514AbfLJQIT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 11:08:19 -0500
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:7041 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727178AbfLJQIT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 11:08:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1575994097; x=1607530097;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=uvB7xnkSnsEw+GrrnNatJiopzdUBiH1mP8A1khdgfVI=;
  b=Mh+0ErAW8SdVRdQ4svgoU39+ylssuV0MFp1kNTCsyowgOuhXxy41fVzk
   sgTmsF2talYcmd+DJvpmHVT0tgRNiCc7Yf3XaUpy+M/EXmchZMjkKcM3t
   wYNkEhH8ZUfrGZGXLxZotdxItuXqJFXC+xecgFRwjbOcObFfqVpp0ujgd
   8=;
IronPort-SDR: 
 2VVPu23ZC1Ja977LBpFcQX7CisdfapsSVh/YguNp0QzWR639Z6+3Fvyz1Ocs4PG6vwoiLHz/is
 nJOZ+fxbVFQw==
X-IronPort-AV: E=Sophos;i="5.69,300,1571702400";
   d="scan'208";a="12699808"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-90c42d1d.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 10 Dec 2019 16:07:38 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-90c42d1d.us-west-2.amazon.com (Postfix) with
 ESMTPS id 3295FA0376;
        Tue, 10 Dec 2019 16:07:38 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.243) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Tue, 10 Dec 2019 16:07:37 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.162.171) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Tue, 10 Dec 2019 16:07:34 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH] kvm: Refactor handling of VM debugfs files
Date: Tue, 10 Dec 2019 17:07:24 +0100
Message-ID: <20191210160724.1030-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.171]
X-ClientProxiedBy: EX13D07UWB003.ant.amazon.com (10.43.161.66) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By storing kvm_stat_kind inside kvm_stat_data struct we can remove
duplicated code and remove usage of temporary kvm_stat_data struct
inside vm_stat_get et al.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
---
 include/linux/kvm_host.h |   1 +
 virt/kvm/kvm_main.c      | 118 +++++++++++++++++----------------------
 2 files changed, 53 insertions(+), 66 deletions(-)

```
#### [PATCH 1/4] KVM: x86: Don't let userspace set host-reserved cr4 bits
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11283365
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9CCCF138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 22:44:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 852772053B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 22:44:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729264AbfLJWoW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 17:44:22 -0500
Received: from mga09.intel.com ([134.134.136.24]:9123 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728333AbfLJWoU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 17:44:20 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Dec 2019 14:44:19 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,301,1571727600";
   d="scan'208";a="413279327"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 10 Dec 2019 14:44:18 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Jun Nakajima <jun.nakajima@intel.com>
Subject: [PATCH 1/4] KVM: x86: Don't let userspace set host-reserved cr4 bits
Date: Tue, 10 Dec 2019 14:44:13 -0800
Message-Id: <20191210224416.10757-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191210224416.10757-1-sean.j.christopherson@intel.com>
References: <20191210224416.10757-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Calculate the host-reserved cr4 bits at runtime based on the system's
capabilities (using logic similar to __do_cpuid_func()), and use the
dynamically generated mask for the reserved bit check in kvm_set_cr4()
instead using of the static CR4_RESERVED_BITS define.  This prevents
userspace from "enabling" features in cr4 that are not supported by the
system, e.g. by ignoring KVM_GET_SUPPORTED_CPUID and specifying a bogus
CPUID for the vCPU.

Allowing userspace to set unsupported bits in cr4 can lead to a variety
of undesirable behavior, e.g. failed VM-Enter, and in general increases
KVM's attack surface.  A crafty userspace can even abuse CR4.LA57 to
induce an unchecked #GP on a WRMSR.

On a platform without LA57 support:

  KVM_SET_CPUID2 // CPUID_7_0_ECX.LA57 = 1
  KVM_SET_SREGS  // CR4.LA57 = 1
  KVM_SET_MSRS   // KERNEL_GS_BASE = 0x0004000000000000
  KVM_RUN

leads to a #GP when writing KERNEL_GS_BASE into hardware:

  unchecked MSR access error: WRMSR to 0xc0000102 (tried to write 0x0004000000000000)
  at rIP: 0xffffffffa00f239a (vmx_prepare_switch_to_guest+0x10a/0x1d0 [kvm_intel])
  Call Trace:
   kvm_arch_vcpu_ioctl_run+0x671/0x1c70 [kvm]
   kvm_vcpu_ioctl+0x36b/0x5d0 [kvm]
   do_vfs_ioctl+0xa1/0x620
   ksys_ioctl+0x66/0x70
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x4c/0x170
   entry_SYSCALL_64_after_hwframe+0x44/0xa9
  RIP: 0033:0x7fc08133bf47

Note, the above sequence fails VM-Enter due to invalid guest state.
Userspace can allow VM-Enter to succeed (after the WRMSR #GP) by adding
a KVM_SET_SREGS w/ CR4.LA57=0 after KVM_SET_MSRS, in which case KVM will
technically leak the host's KERNEL_GS_BASE into the guest.  But, as
KERNEL_GS_BASE is a userspace-defined value/address, the leak is largely
benign as a malicious userspace would simply be exposing its own data to
the guest, and attacking a benevolent userspace would require multiple
bugs in the userspace VMM.

Cc: stable@vger.kernel.org
Cc: Jun Nakajima <jun.nakajima@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 35 ++++++++++++++++++++++++++++++++++-
 1 file changed, 34 insertions(+), 1 deletion(-)

```
#### [PATCH] tools/kvm_stat: Fix kvm_exit filter name
##### From: Gavin Shan <gshan@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Gavin Shan <gshan@redhat.com>
X-Patchwork-Id: 11281317
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9429E930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 04:48:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 722F020828
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 04:48:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Vi+WHZjd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726823AbfLJEsl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Dec 2019 23:48:41 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:21090 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726619AbfLJEsl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Dec 2019 23:48:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575953319;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=QympgZOxqEEUQUgiK/ImVQ4UaqIOxBVleuToewMy0Ek=;
        b=Vi+WHZjdh5n9KKRjqnnCklKQSioTCbB3vR33f4DxpSxq2XcSDn7/hKLaW5z4mBkrd2eDYJ
        uEYuDk2i6RopUqj8uBXy/YVX+njopOLCC+nXAIg3WZFaymh8rkT4GM3uqJAjrOd52OOgAu
        sqIy8qbkp3d/eU/o0gEE6pM/MykOJKU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-340-bktEsB10NHCGdS9KSGL7wA-1; Mon, 09 Dec 2019 23:48:38 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 91050800D54
        for <kvm@vger.kernel.org>; Tue, 10 Dec 2019 04:48:37 +0000 (UTC)
Received: from localhost.localdomain.com (vpn2-54-52.bne.redhat.com
 [10.64.54.52])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0E6181001925;
        Tue, 10 Dec 2019 04:48:32 +0000 (UTC)
From: Gavin Shan <gshan@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, drjones@redhat.com,
        gshan@redhat.com
Subject: [PATCH] tools/kvm_stat: Fix kvm_exit filter name
Date: Tue, 10 Dec 2019 15:48:29 +1100
Message-Id: <20191210044829.180122-1-gshan@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: bktEsB10NHCGdS9KSGL7wA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The filter name is fixed to "exit_reason" for some kvm_exit events, no
matter what architect we have. Actually, the filter name ("exit_reason")
is only applicable to x86, meaning it's broken on other architects
including aarch64.

This fixes the issue by providing various kvm_exit filter names, depending
on architect we're on. Afterwards, the variable filter name is picked and
applied through ioctl(fd, SET_FILTER).

Reported-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Gavin Shan <gshan@redhat.com>
---
 tools/kvm/kvm_stat/kvm_stat | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH net-next v2 1/6] vsock/virtio_transport_common: remove unused virtio header includes
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11281841
Return-Path: <SRS0=lHx3=2A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 023A8930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 10:43:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9F9C2073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Dec 2019 10:43:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AYo+84kf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727469AbfLJKnZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Dec 2019 05:43:25 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:50493 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726574AbfLJKnU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Dec 2019 05:43:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575974599;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=QeLkFWwrMkorI96amP0PUDWveJeOajJe9WkJWUSYsG8=;
        b=AYo+84kfjOg5tyPVCFIbqc5DC8Bigf3uQo7aKpwejlCa3vpcnYNLtx7Y0+dD8y76/pf+3Z
        nYFjhw1qzRgX19njbBLe9b+RPLWHes7vVbU6aVGGhTdaq8679ToLFGSrOl+Rrcldhu8Yua
        bUphTAhQgZLVgiIHf79sQlTK+Crl/jQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-T8h34d17OraQX2hFRsHDTg-1; Tue, 10 Dec 2019 05:43:16 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68AAD800D5E;
        Tue, 10 Dec 2019 10:43:15 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-168.ams2.redhat.com
 [10.36.117.168])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 65FAE60568;
        Tue, 10 Dec 2019 10:43:13 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org, davem@davemloft.net
Cc: Dexuan Cui <decui@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Stefano Garzarella <sgarzare@redhat.com>
Subject: [PATCH net-next v2 1/6] vsock/virtio_transport_common: remove unused
 virtio header includes
Date: Tue, 10 Dec 2019 11:43:02 +0100
Message-Id: <20191210104307.89346-2-sgarzare@redhat.com>
In-Reply-To: <20191210104307.89346-1-sgarzare@redhat.com>
References: <20191210104307.89346-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: T8h34d17OraQX2hFRsHDTg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can remove virtio header includes, because virtio_transport_common
doesn't use virtio API, but provides common functions to interface
virtio/vhost transports with the af_vsock core, and to handle
the protocol.

Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 3 ---
 1 file changed, 3 deletions(-)

```
