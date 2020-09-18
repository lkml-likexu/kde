

#### [PATCH 0/2] KVM: arm64: Add support for setting MPIDR
##### From: Ying Fang <fangying1@huawei.com>

```c
From patchwork Thu Sep 17 02:30:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ying Fang <fangying1@huawei.com>
X-Patchwork-Id: 11781307
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51190618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:47:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 42DF62075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:47:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726102AbgIQCq7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 22:46:59 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:60184 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726065AbgIQCq5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 22:46:57 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 646BEB1720B8D3657DCC;
        Thu, 17 Sep 2020 10:31:00 +0800 (CST)
Received: from localhost (10.174.185.104) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.487.0; Thu, 17 Sep 2020
 10:30:50 +0800
From: Ying Fang <fangying1@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <maz@kernel.org>
CC: <drjones@redhat.com>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <suzuki.poulose@arm.com>,
        <zhang.zhanghailiang@huawei.com>, <alex.chen@huawei.com>,
        Ying Fang <fangying1@huawei.com>
Subject: [PATCH 0/2] KVM: arm64: Add support for setting MPIDR
Date: Thu, 17 Sep 2020 10:30:31 +0800
Message-ID: <20200917023033.1337-1-fangying1@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.104]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MPIDR is used to show multiprocessor affinity on arm platform. It is
also used to provide an additional processor identification mechanism
for scheduling purposes. To add support for setting MPIDR from usersapce
an vcpu ioctl KVM_CAP_ARM_MP_AFFINITY is introduced. This patch series is
needed to help qemu to build the accurate cpu topology for arm.

Ying Fang (2):
  KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
  kvm/arm: Add mp_affinity for arm vcpu

 Documentation/virt/kvm/api.rst    |  8 ++++++++
 arch/arm64/include/asm/kvm_host.h |  5 +++++
 arch/arm64/kvm/arm.c              |  9 +++++++++
 arch/arm64/kvm/reset.c            | 11 +++++++++++
 arch/arm64/kvm/sys_regs.c         | 30 +++++++++++++++++++-----------
 include/uapi/linux/kvm.h          |  3 +++
 6 files changed, 55 insertions(+), 11 deletions(-)
```
#### [RFC PATCH 0/2] KVM: arm64: Add support for setting MPIDR
##### From: Ying Fang <fangying1@huawei.com>

```c
From patchwork Thu Sep 17 03:00:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ying Fang <fangying1@huawei.com>
X-Patchwork-Id: 11781317
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7ECA559D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:01:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65D2B2080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:01:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726097AbgIQDBJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 23:01:09 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:41532 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725886AbgIQDBI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 23:01:08 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 2924B8737466F9CFAE96;
        Thu, 17 Sep 2020 11:01:06 +0800 (CST)
Received: from localhost (10.174.185.104) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.487.0; Thu, 17 Sep 2020
 11:00:56 +0800
From: Ying Fang <fangying1@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <drjones@redhat.com>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <suzuki.poulose@arm.com>,
        <zhang.zhanghailiang@huawei.com>, <alex.chen@huawei.com>,
        Ying Fang <fangying1@huawei.com>
Subject: [RFC PATCH 0/2] KVM: arm64: Add support for setting MPIDR
Date: Thu, 17 Sep 2020 11:00:51 +0800
Message-ID: <20200917030053.1747-1-fangying1@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.104]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MPIDR is used to show multiprocessor affinity on arm platform. It is
also used to provide an additional processor identification mechanism
for scheduling purposes. To add support for setting MPIDR from usersapce
an vcpu ioctl KVM_CAP_ARM_MP_AFFINITY is introduced. This patch series is
needed to help qemu to build the accurate cpu topology for arm.

Ying Fang (2):
  KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
  kvm/arm: Add mp_affinity for arm vcpu

 Documentation/virt/kvm/api.rst    |  8 ++++++++
 arch/arm64/include/asm/kvm_host.h |  5 +++++
 arch/arm64/kvm/arm.c              |  9 +++++++++
 arch/arm64/kvm/reset.c            | 11 +++++++++++
 arch/arm64/kvm/sys_regs.c         | 30 +++++++++++++++++++-----------
 include/uapi/linux/kvm.h          |  3 +++
 6 files changed, 55 insertions(+), 11 deletions(-)
```
#### [PATCH v4 0/2] KVM: nSVM: ondemand nested state allocation
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Sep 17 10:10:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11782127
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F4E459D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 10:11:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F3222087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 10:11:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WZmVP78g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726609AbgIQKLH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 06:11:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:50707 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726549AbgIQKLC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 06:11:02 -0400
X-Greylist: delayed 1500 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 17 Sep 2020 06:11:02 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600337457;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/Hhy9FvabiDG5Ek4mu3Z7RZKm3yT/cj4T3OHkyQ6r2k=;
        b=WZmVP78gT2lIEe51OK/Xs+zlV7Tt2d3PdAZKmUhcUSc1Abceuhzlwsz4c7vYfDXC7IFZRu
        jdrV0FJmL2/U39RNHGsFsZgkZcD+KnoBykj394qOvN58l9ciCGusPa6HhEk1XYybTcEyCE
        GyOVRnn5S4pYn2TxFzORJQNcQN1/8Q0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-48-1yKMiu0XOV2XoIf9IxiM3g-1; Thu, 17 Sep 2020 06:10:56 -0400
X-MC-Unique: 1yKMiu0XOV2XoIf9IxiM3g-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3BC6664085;
        Thu, 17 Sep 2020 10:10:54 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.187])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 954451000239;
        Thu, 17 Sep 2020 10:10:50 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v4 0/2] KVM: nSVM: ondemand nested state allocation
Date: Thu, 17 Sep 2020 13:10:46 +0300
Message-Id: <20200917101048.739691-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is new version of ondemand nested state allocation.

In this version I dropped the changes to set_efer and instead
added a new request KVM_REQ_OUT_OF_MEMORY which makes the kvm
exit to userspace with KVM_EXIT_INTERNAL_ERROR

This request is used in (unlikely) case of memory allocation
failure.

Maxim Levitsky (2):
  KVM: add request KVM_REQ_OUT_OF_MEMORY
  KVM: nSVM: implement ondemand allocation of the nested state

 arch/x86/kvm/svm/nested.c | 42 ++++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c    | 54 ++++++++++++++++++++++-----------------
 arch/x86/kvm/svm/svm.h    |  7 +++++
 arch/x86/kvm/x86.c        |  7 +++++
 include/linux/kvm_host.h  |  1 +
 5 files changed, 87 insertions(+), 24 deletions(-)
```
#### [PATCH 0/1] KVM: correctly restore the TSC value on nested migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Sep 17 11:07:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11782263
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46BEA112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 11:08:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A99D2076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 11:08:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PiX70Qz3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726651AbgIQLIR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 07:08:17 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59548 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726625AbgIQLHm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 07:07:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600340852;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=kkPhCJgbEfe1snOxUIcIHLF53bSNUGZMiNRLxPCaeLg=;
        b=PiX70Qz38E5lMeqsonbSOM89n+elwJrw0mTqfEHErTTTFkp98SQVFqk2qjsdbClUJ++xav
        xCoMmT2uh+38EyFG/AbbhhaRx7iqsARdg0NHSI4M7jwldwcg8QAahu1rHKFZtFcp6clHBP
        1U+IyH1vTtefWj+6KefqZe9jbqqblsM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-410-32wzq0FnPZG_xa7NCuQrnA-1; Thu, 17 Sep 2020 07:07:31 -0400
X-MC-Unique: 32wzq0FnPZG_xa7NCuQrnA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4A33180EF8A;
        Thu, 17 Sep 2020 11:07:29 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.187])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4FA0875142;
        Thu, 17 Sep 2020 11:07:24 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/1] KVM: correctly restore the TSC value on nested migration
Date: Thu, 17 Sep 2020 14:07:22 +0300
Message-Id: <20200917110723.820666-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch is a result of a long investigation I made to understand
why the nested migration more often than not makes the nested guest hang.
Sometimes the nested guest recovers and sometimes it hangs forever.

The root cause of this is that reading MSR_IA32_TSC while nested guest is
running returns its TSC value, that is (assuming no tsc scaling)
host tsc + L1 tsc offset + L2 tsc offset.

This is correct but it is a result of a nice curiosity of X86 VMX
(and apparently SVM too, according to my tests) implementation:

As a rule MSR reads done by the guest should either trap to host, or just
return host value, and therefore kvm_get_msr and friends, should basically
always return the L1 value of any msr.

Well, MSR_IA32_TSC is an exception. Intel's PRM states that when you disable
its interception, then in guest mode the host adds the TSC offset to
the read value.

I haven't found anything like that in AMD's PRM but according to the few
tests I made, it behaves the same.

However, there is no such exception when writing MSR_IA32_TSC, and this
poses a problem for nested migration.

When MSR_IA32_TSC is read, we read L2 value (smaller since L2 is started
after L1), and when we restore it after migration, the value is interpreted
as L1 value, thus resulting in huge TSC jump backward which the guest usually
really doesn't like, especially on AMD with APIC deadline timer, which
usually just doesn't fire afterward sending the guest into endless wait for it.

The proposed patch fixes this by making read of MSR_IA32_TSC depend on
'msr_info->host_initiated'

If guest reads the MSR, we add the TSC offset, but when host's qemu reads
the msr we skip that silly emulation of TSC offset, and return the real value
for the L1 guest which is host tsc + L1 offset.

This patch was tested on both SVM and VMX, and on both it fixes hangs.
On VMX since it uses VMX preemption timer for APIC deadline, the guest seems
to recover after a while without that patch.

To make sure that the nested migration happens I usually used
-overcommit cpu_pm=on but I reproduced this with just running an endless loop
in L2.

This is tested both with and without -invtsc,tsc-frequency=...

The migration was done by saving the migration stream to a file, and then
loading the qemu with '-incoming'

Maxim Levitsky (1):
  KVM: x86: fix MSR_IA32_TSC read for nested migration

 arch/x86/kvm/x86.c | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)
```
#### [RFC v2 0/7] kvm: arm64: emulate ID registers
##### From: Peng Liang <liangpeng10@huawei.com>

```c
From patchwork Thu Sep 17 12:00:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11782415
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4ED586CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 12:57:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4109D21734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 12:57:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727124AbgIQM50 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 08:57:26 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:37178 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727057AbgIQM5U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Sep 2020 08:57:20 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 61C231A20D53158B4E33;
        Thu, 17 Sep 2020 20:09:19 +0800 (CST)
Received: from localhost.localdomain (10.175.104.175) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.487.0; Thu, 17 Sep 2020 20:09:10 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <drjones@redhat.com>, <zhang.zhanghailiang@huawei.com>,
        <xiexiangyou@huawei.com>, Peng Liang <liangpeng10@huawei.com>
Subject: [RFC v2 0/7] kvm: arm64: emulate ID registers
Date: Thu, 17 Sep 2020 20:00:54 +0800
Message-ID: <20200917120101.3438389-1-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-Originating-IP: [10.175.104.175]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In AArch64, guest will read the same values of the ID regsiters with
host.  Both of them read the values from arm64_ftr_regs.  This patch
series add support to emulate and configure ID registers so that we can
control the value of ID registers that guest read.

v1 -> v2:
 - save the ID registers in sysreg file instead of a new struct
 - apply a checker before setting the value to the register
 - add doc for new KVM_CAP_ARM_CPU_FEATURE

Peng Liang (7):
  arm64: add a helper function to traverse arm64_ftr_regs
  arm64: introduce check_features
  kvm: arm64: save ID registers to sys_regs file
  kvm: arm64: introduce check_user
  kvm: arm64: implement check_user for ID registers
  kvm: arm64: make ID registers configurable
  kvm: arm64: add KVM_CAP_ARM_CPU_FEATURE extension

 Documentation/virt/kvm/api.rst      |   8 +
 arch/arm64/include/asm/cpufeature.h |   4 +
 arch/arm64/include/asm/kvm_coproc.h |   2 +
 arch/arm64/include/asm/kvm_host.h   |   3 +
 arch/arm64/kernel/cpufeature.c      |  36 +++
 arch/arm64/kvm/arm.c                |   3 +
 arch/arm64/kvm/sys_regs.c           | 481 +++++++++++++++++++++++++++-
 arch/arm64/kvm/sys_regs.h           |   6 +
 include/uapi/linux/kvm.h            |   1 +
 9 files changed, 532 insertions(+), 12 deletions(-)
```
#### [PATCH v4 0/5] s390x/pci: Accomodate vfio DMA limiting
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Thu Sep 17 14:20:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11782667
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7A97618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 14:40:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A437220684
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 14:40:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="UK4j2/bd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726986AbgIQOjv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 10:39:51 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:35302 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727555AbgIQOiV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 10:38:21 -0400
X-Greylist: delayed 1029 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 17 Sep 2020 10:38:21 EDT
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08HE5J80048938;
        Thu, 17 Sep 2020 10:20:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=pp1;
 bh=pFzLdR4oh7vJzXza9CYBsTxnTeFiRc6b489PWMFCmhQ=;
 b=UK4j2/bdBgaFZJv32T9SHjYFfPMyUcaxDdZkfXW9A3hIj995knRWS7mknk/qRZLnoq90
 jQm38RneC+P/cMgAwaN10/fVg6CIo06K9u798TWvsemc7LElmm8C83txw1vtqFw6rYHa
 RVREWG+pEQk5mtLTXnPVN5qws9YWD2c5A3v+lTrt3qdDiAPIOWbfnI2l/D7tpjazWFvd
 AeIiXD8Skcx92vY1wZD1q5W2xq1qS8ED4Gseo6LgbImwPavjkGkWtZZ+jL7fbJ2Aox+J
 N9Hra2ZrdTk7XiiL8ajpdARHjHW/kkt3yVqMv9avxe929WcP+nWxeXUnB9x44v0tZyjJ Gw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33m92r8v30-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 10:20:54 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08HE5anx050067;
        Thu, 17 Sep 2020 10:20:54 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33m92r8v2h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 10:20:54 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08HEISc8021857;
        Thu, 17 Sep 2020 14:20:53 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma02wdc.us.ibm.com with ESMTP id 33k67c4w0e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 14:20:53 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 08HEKq7a55771482
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 17 Sep 2020 14:20:52 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A3DDAAC059;
        Thu, 17 Sep 2020 14:20:52 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6EFD1AC05B;
        Thu, 17 Sep 2020 14:20:49 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.85.51])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 17 Sep 2020 14:20:49 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, thuth@redhat.com, pasic@linux.ibm.com,
        borntraeger@de.ibm.com, mst@redhat.com, pbonzini@redhat.com,
        philmd@redhat.com, qemu-s390x@nongnu.org, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH v4 0/5] s390x/pci: Accomodate vfio DMA limiting
Date: Thu, 17 Sep 2020 10:20:40 -0400
Message-Id: <1600352445-21110-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-17_09:2020-09-16,2020-09-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 phishscore=0 malwarescore=0 mlxlogscore=999 priorityscore=1501
 impostorscore=0 clxscore=1015 suspectscore=0 adultscore=0
 lowpriorityscore=0 spamscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009170104
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Kernel commit 492855939bdb added a limit to the number of outstanding DMA
requests for a type1 vfio container.  However, lazy unmapping in s390 can 
in fact cause quite a large number of outstanding DMA requests to build up
prior to being purged, potentially the entire guest DMA space.  This
results in unexpected 'VFIO_MAP_DMA failed: No space left on device'
conditions seen in QEMU.

This patchset adds support to qemu to retrieve the number of allowable DMA
requests via the VFIO_IOMMU_GET_INFO ioctl.  The patches are separated into
vfio hits which add support for reading in VFIO_IOMMU_GET_INFO capability
chains and getting the per-container dma_avail value, and s390 hits to 
track DMA usage on a per-container basis.

Associated kernel patch:
https://marc.info/?l=kvm&m=160019703922812&w=2


Changes from v3:
- Patch 2,3: Added RBs provided (thank you!)
- Patch 4: retry the ioctl in the same manner as vfio_get_region_info
- Patch 5: switch to static inline functions
- Patch 5: relocate more code to s390-pci-vfio.*


Matthew Rosato (5):
  linux-headers: update against 5.9-rc5
  vfio: Create shared routine for scanning info capabilities
  vfio: Find DMA available capability
  s390x/pci: Add routine to get the vfio dma available count
  s390x/pci: Honor DMA limits set by vfio

 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  16 ++-
 hw/s390x/s390-pci-bus.h                            |   9 ++
 hw/s390x/s390-pci-inst.c                           |  45 ++++++-
 hw/s390x/s390-pci-inst.h                           |   3 +
 hw/s390x/s390-pci-vfio.c                           |  96 ++++++++++++++
 hw/s390x/s390-pci-vfio.h                           |  22 ++++
 hw/vfio/common.c                                   |  52 ++++++--
 include/hw/vfio/vfio-common.h                      |   2 +
 include/standard-headers/drm/drm_fourcc.h          | 140 +++++++++++++++++++++
 include/standard-headers/linux/ethtool.h           |  87 +++++++++++++
 include/standard-headers/linux/input-event-codes.h |   3 +-
 include/standard-headers/linux/vhost_types.h       |  11 ++
 include/standard-headers/linux/virtio_9p.h         |   4 +-
 include/standard-headers/linux/virtio_blk.h        |  26 ++--
 include/standard-headers/linux/virtio_config.h     |   8 +-
 include/standard-headers/linux/virtio_console.h    |   8 +-
 include/standard-headers/linux/virtio_net.h        |   6 +-
 include/standard-headers/linux/virtio_scsi.h       |  20 +--
 linux-headers/asm-generic/unistd.h                 |   6 +-
 linux-headers/asm-mips/unistd_n32.h                |   1 +
 linux-headers/asm-mips/unistd_n64.h                |   1 +
 linux-headers/asm-mips/unistd_o32.h                |   1 +
 linux-headers/asm-powerpc/kvm.h                    |   5 +
 linux-headers/asm-powerpc/unistd_32.h              |   1 +
 linux-headers/asm-powerpc/unistd_64.h              |   1 +
 linux-headers/asm-s390/kvm.h                       |   7 +-
 linux-headers/asm-s390/unistd_32.h                 |   1 +
 linux-headers/asm-s390/unistd_64.h                 |   1 +
 linux-headers/asm-x86/unistd_32.h                  |   1 +
 linux-headers/asm-x86/unistd_64.h                  |   1 +
 linux-headers/asm-x86/unistd_x32.h                 |   1 +
 linux-headers/linux/kvm.h                          |  10 +-
 linux-headers/linux/vfio.h                         |  17 ++-
 linux-headers/linux/vhost.h                        |   2 +
 35 files changed, 554 insertions(+), 62 deletions(-)
 create mode 100644 hw/s390x/s390-pci-vfio.c
 create mode 100644 hw/s390x/s390-pci-vfio.h
```
#### [PATCH 0/3 v4] x86: AMD: Don't flush cache if hardware enforces cache
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Sep 17 21:20:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11783581
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E464112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 21:24:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E2695208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 21:24:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="QGKNvmJb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726097AbgIQVX5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 17:23:57 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:35920 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725874AbgIQVX4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Sep 2020 17:23:56 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08HLExBO142522;
        Thu, 17 Sep 2020 21:22:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=t+VWV71FF9RYCPYbM3EXOGsdaz3UEhSiekOl2khfsVY=;
 b=QGKNvmJbNtVQYFLh6aAwH6JA+2NLEUUr4oTTdINcOSvvtVAozwuH7ZKgcFL4aZvoTlt9
 3l0DEcm2H44mlioxciQF77BCinAgyFBZPl65MFnx9BT+OZU1pjY+eolGF0HEcH8LVruu
 /OZDV7ZZkoUFCYmYRnMxaI5aThe/WhDYoUEiT3qxtnvSMdQFyeS0VLw1RNkn5FvlbnEc
 6D8XcY+CaPICmnU8IxgV4r/uUQnPGi2xVkleNlfumb1shvyzLArtQ9fyEunVh0vUNz2Q
 wyeEBVvWZJ60S2wRcN8DGt1yfgs5D+o5q/QFAqlw9atEilsBZ6MiBvrctpFJ6WXDfmPu yg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 33j91dwhmv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 17 Sep 2020 21:22:33 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08HLA5Y3133785;
        Thu, 17 Sep 2020 21:22:32 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 33khpnp2hh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 17 Sep 2020 21:22:32 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 08HLMPsW026926;
        Thu, 17 Sep 2020 21:22:25 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 17 Sep 2020 21:22:25 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, joro@8bytes.org,
        dave.hansen@linux.intel.com, luto@kernel.org, peterz@infradead.org,
        linux-kernel@vger.kernel.org, hpa@zytor.com
Subject: [PATCH 0/3 v4] x86: AMD: Don't flush cache if hardware enforces cache
 coherency across encryption domains
Date: Thu, 17 Sep 2020 21:20:35 +0000
Message-Id: <20200917212038.5090-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9747
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 suspectscore=1
 mlxlogscore=655 phishscore=0 mlxscore=0 adultscore=0 spamscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009170158
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9747
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 impostorscore=0
 priorityscore=1501 malwarescore=0 suspectscore=1 mlxlogscore=662
 clxscore=1015 adultscore=0 lowpriorityscore=0 spamscore=0 mlxscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009170158
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
	1. Patch# 1 from v3 has been dropped.
	2. The CPUID feature for hardware-enforced cache coherency has been
	   renamed.

[PATCH 1/3 v4] x86: AMD: Add hardware-enforced cache coherency as a
[PATCH 2/3 v4] x86: AMD: Don't flush cache if hardware enforces cache
[PATCH 3/3 v4] KVM: SVM: Don't flush cache if hardware enforces cache

 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 arch/x86/kvm/svm/sev.c             | 3 ++-
 arch/x86/mm/pat/set_memory.c       | 2 +-
 4 files changed, 5 insertions(+), 2 deletions(-)

Krish Sadhukhan (3):
      x86: AMD: Add hardware-enforced cache coherency as a CPUID feature
      x86: AMD: Don't flush cache if hardware enforces cache coherency across encryption domnains
      KVM: SVM: Don't flush cache if hardware enforces cache coherency across encryption domains
```
