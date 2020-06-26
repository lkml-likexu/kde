#### [PATCH RFC 1/4] arm64: kernel: Handle disabled[(+)present] cpus in MADT/GICC during init
##### From: Salil Mehta <salil.mehta@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Salil Mehta <salil.mehta@huawei.com>
X-Patchwork-Id: 11625385
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E36F714B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:45:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA2D320781
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:45:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405181AbgFYNph (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 09:45:37 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:6827 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2405096AbgFYNph (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 09:45:37 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 52A299654FC5BEE3B867;
        Thu, 25 Jun 2020 21:43:55 +0800 (CST)
Received: from A190218597.china.huawei.com (10.47.76.118) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.487.0; Thu, 25 Jun 2020 21:43:48 +0800
From: Salil Mehta <salil.mehta@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>
CC: <maz@kernel.org>, <will@kernel.org>, <catalin.marinas@arm.com>,
        <christoffer.dall@arm.com>, <andre.przywara@arm.com>,
        <james.morse@arm.com>, <mark.rutland@arm.com>,
        <lorenzo.pieralisi@arm.com>, <sudeep.holla@arm.com>,
        <qemu-arm@nongnu.org>, <peter.maydell@linaro.org>,
        <richard.henderson@linaro.org>, <imammedo@redhat.com>,
        <mst@redhat.com>, <drjones@redhat.com>, <pbonzini@redhat.com>,
        <eric.auger@redhat.com>, <gshan@redhat.com>, <david@redhat.com>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linuxarm@huawei.com>, <mehta.salil.lnk@gmail.com>,
        Salil Mehta <salil.mehta@huawei.com>,
        "Xiongfeng Wang" <wangxiongfeng2@huawei.com>
Subject: [PATCH RFC 1/4] arm64: kernel: Handle disabled[(+)present] cpus in
 MADT/GICC during init
Date: Thu, 25 Jun 2020 14:37:54 +0100
Message-ID: <20200625133757.22332-2-salil.mehta@huawei.com>
X-Mailer: git-send-email 2.8.3
In-Reply-To: <20200625133757.22332-1-salil.mehta@huawei.com>
References: <20200625133757.22332-1-salil.mehta@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.47.76.118]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With ACPI enabled, cpus get identified by the presence of the GICC
entry in the MADT Table. Each GICC entry part of MADT presents cpu as
enabled or disabled. As of now, the disabled cpus are skipped as
physical cpu hotplug is not supported. These remain disabled even after
the kernel has booted.

To support virtual cpu hotplug(in which case disabled vcpus could be
hotplugged even after kernel has booted), QEMU will populate MADT Table
with appropriate details of GICC entry for each possible(present+disabled)
vcpu. Now, during the init time vcpus will be identified as present or
disabled. To achieve this, below changes have been made with respect to
the present/possible vcpu handling along with the mentioned reasoning:

1. Identify all possible(present+disabled) vcpus at boot/init time
   and set their present mask and possible mask. In the existing code,
   cpus are being marked present quite late within smp_prepare_cpus()
   function, which gets called in context to the kernel thread. Since
   the cpu hotplug is not supported, present cpus are always equal to
   the possible cpus. But with cpu hotplug enabled, this assumption is
   not true. Hence, present cpus should be marked while MADT GICC entries
   are bring parsed for each vcpu.
2. Set possible cpus to include disabled. This needs to be done now
   while parsing MADT GICC entries corresponding to each vcpu as the
   disabled vcpu info is available only at this point as for hotplug
   case possible vcpus is not equal to present vcpus.
3. We will store the parsed madt/gicc entry even for the disabled vcpus
   during init time. This is needed as some modules like PMU registers
   IRQs for each possible vcpus during init time. Therefore, a valid
   entry of the MADT GICC should be present for all possible vcpus.
4. Refactoring related to DT/OF is also done to align it with the init
   changes to support vcpu hotplug.

Signed-off-by: Salil Mehta <salil.mehta@huawei.com>
Signed-off-by: Xiongfeng Wang <wangxiongfeng2@huawei.com>
---
 arch/arm64/kernel/smp.c | 27 ++++++++++++++++++++-------
 1 file changed, 20 insertions(+), 7 deletions(-)

```
#### [PATCH 1/4] KVM: SVM: Rename struct nested_state to svm_nested_state
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11624745
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 750446C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 08:04:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E38052081A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 08:04:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390743AbgFYIEc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 04:04:32 -0400
Received: from 8bytes.org ([81.169.241.247]:48816 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390452AbgFYIDc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 04:03:32 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 9AD44249; Thu, 25 Jun 2020 10:03:30 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH 1/4] KVM: SVM: Rename struct nested_state to svm_nested_state
Date: Thu, 25 Jun 2020 10:03:22 +0200
Message-Id: <20200625080325.28439-2-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200625080325.28439-1-joro@8bytes.org>
References: <20200625080325.28439-1-joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Renaming is only needed in the svm.h header file.

No functional changes.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/svm.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests v2] x86: setup segment registers before percpu areas
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11624899
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EEB5A14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 11:13:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D5F7A206FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 11:13:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A6O7sDxL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404125AbgFYLNc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 07:13:32 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:26552 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2404042AbgFYLNc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 07:13:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593083611;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0dsCTG5l149JURh9HRnb5gcWP46PjgZEHPEl+fIj16g=;
        b=A6O7sDxLkFacO1sh3IY6Zu7ydp4oTe1P+T0KbafDW+VYNgLiKr3Ra03ZlGgubbuMFksnHG
        Qq0OhNme6kl+GersL1Am10LRNQie8XSfvLeUGrs/b/9C7j/zfIQsjfWRLjCN860FBUWjhP
        ITX0ZBdDlcZhiHIb0q+vE3iNqJ9yK90=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-446-R_7LxPF1PEiFYEnCFy--Zg-1; Thu, 25 Jun 2020 07:13:29 -0400
X-MC-Unique: R_7LxPF1PEiFYEnCFy--Zg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 54FE410059B9;
        Thu, 25 Jun 2020 11:13:28 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0FCA51010428;
        Thu, 25 Jun 2020 11:13:27 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: nadav.amit@gmail.com
Subject: [PATCH kvm-unit-tests v2] x86: setup segment registers before percpu
 areas
Date: Thu, 25 Jun 2020 07:13:27 -0400
Message-Id: <20200625111327.1509-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The base of the percpu area is stored in the %gs base, and writing
to %gs destroys it.  Move setup_segments earlier, before the %gs
base is written, and keep setup_percpu_area close so that the base
is updated close to the selector.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/cstart.S | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: fix stack pointer after call
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11624903
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 181CA913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 11:15:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E4C7C206FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 11:15:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AHf2BFLq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404206AbgFYLPb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 07:15:31 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:33819 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2404205AbgFYLPb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 07:15:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593083730;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Vdl4f8xTmP7RgRJTyPC0kZXaQsu6szqBFCZdWfmzvis=;
        b=AHf2BFLqREwo+zzLAGPG4MLZlJGWtCUdmeSW8BTEwHaSOWjpZEw7WtjK2MpYPcLhPJYMJ5
        bqcXwt36+kIv/+sowmkhsQEEaCXKaNMeVgL3/YvYGMwJ3zhdzfIXcuwoq0qU84CDzSWvlv
        Ohivr69FiYItE+Mx9X+veR1JdgtYykc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-401-LvUANXN8PqGkKfS86QrfYQ-1; Thu, 25 Jun 2020 07:15:28 -0400
X-MC-Unique: LvUANXN8PqGkKfS86QrfYQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 870C8107ACF3;
        Thu, 25 Jun 2020 11:15:27 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 22FCD61981;
        Thu, 25 Jun 2020 11:15:27 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: namit@vmware.com
Subject: [PATCH kvm-unit-tests] x86: fix stack pointer after call
Date: Thu, 25 Jun 2020 07:15:26 -0400
Message-Id: <20200625111526.1620-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since setup_multiboot has a C calling convention, the stack pointer must
be adjusted after the call.  Without this change, the bottom of the
percpu area would be 4 bytes below the bottom of the stack.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 x86/cstart.S | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH] kvm,x86: Exit to user space in case of page fault error
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11626143
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D960460D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 21:47:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA85820709
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 21:47:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Rtqf75KD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406949AbgFYVrN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 17:47:13 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:52041 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2406811AbgFYVrL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 17:47:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593121629;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=kgGg8jMkbvcZ8iFUP5N32zhARfU1/gNnbQngU0bR5Hg=;
        b=Rtqf75KD2dBvAoHzq1W9gc/MJmWZB7Fj4HbeESG85+0NdG5hUSC0wXV2WV97ziKV43O/vw
        lSuI8UJ3XePpWztwX9RHt3MrxIjuzcq6LSgBvqa9Qn21ISeW7KgJIyBfZEZh3hzy2TStC5
        BBCsRcUPwbFWN2TfBoUTfxIlQRiN2Ko=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-206-mZZ0iYCOMZ-QZKedegce-g-1; Thu, 25 Jun 2020 17:47:05 -0400
X-MC-Unique: mZZ0iYCOMZ-QZKedegce-g-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B53F4800C64;
        Thu, 25 Jun 2020 21:47:04 +0000 (UTC)
Received: from horse.redhat.com (ovpn-116-4.rdu2.redhat.com [10.10.116.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A9C915C240;
        Thu, 25 Jun 2020 21:47:01 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 4C3E6220244; Thu, 25 Jun 2020 17:47:01 -0400 (EDT)
Date: Thu, 25 Jun 2020 17:47:01 -0400
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs@redhat.com, vkuznets@redhat.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com
Subject: [RFC PATCH] kvm,x86: Exit to user space in case of page fault error
Message-ID: <20200625214701.GA180786@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page fault error handling behavior in kvm seems little inconsistent when
page fault reports error. If we are doing fault synchronously
then we capture error (-EFAULT) returned by __gfn_to_pfn_memslot() and
exit to user space and qemu reports error, "error: kvm run failed Bad address".

But if we are doing async page fault, then async_pf_execute() will simply
ignore the error reported by get_user_pages_remote() or
by kvm_mmu_do_page_fault(). It is assumed that page fault was successful
and either a page ready event is injected in guest or guest is brought
out of artificial halt state and run again. In both the cases when guest
retries the instruction, it takes exit again as page fault was not
successful in previous attempt. And then this infinite loop continues
forever.

Trying fault in a loop will make sense if error is temporary and will
be resolved on retry. But I don't see any intention in the code to
determine if error is temporary or not.  Whether to do fault synchronously
or asynchronously, depends on so many variables but none of the varibales
is whether error is temporary or not. (kvm_can_do_async_pf()).

And that makes it very inconsistent or unpredictable to figure out whether
kvm will exit to qemu with error or it will just retry and go into an
infinite loop.

This patch tries to make this behavior consistent. That is instead of
getting into infinite loop of retrying page fault, exit to user space
and stop VM if page fault error happens.

In future this can be improved by injecting errors into guest. As of
now we don't have any race free method to inject errors in guest.

When page fault error happens in async path save that pfn and when next
time guest retries, do a sync fault instead of async fault. So that if error
is encountered, we exit to qemu and avoid infinite loop.

As of now only one error pfn is stored and that means it could be
overwritten before next a retry from guest happens. But this is
just a hint and if we miss it, some other time we will catch it.
If this becomes an issue, we could maintain an array of error
gfn later to help ease the issue.

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/x86.c              | 14 +++++++++++---
 4 files changed, 14 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/2] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11625531
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12751913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 15:07:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02A7F20767
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 15:07:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405777AbgFYPHx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 11:07:53 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:12612 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2405765AbgFYPHx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 11:07:53 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05PF4pPJ100577;
        Thu, 25 Jun 2020 11:07:52 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31vbn79rrj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 11:07:50 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05PF4tID100780;
        Thu, 25 Jun 2020 11:07:50 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31vbn79rku-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 11:07:50 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05PF5jvJ008830;
        Thu, 25 Jun 2020 15:07:38 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma01wdc.us.ibm.com with ESMTP id 31uurtcwg9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Jun 2020 15:07:38 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 05PF7aCx48759278
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Jun 2020 15:07:36 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 796DCAC065;
        Thu, 25 Jun 2020 15:07:36 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 487CDAC064;
        Thu, 25 Jun 2020 15:07:36 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.202.75])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 25 Jun 2020 15:07:36 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v2 1/2] docs: kvm: add documentation for KVM_CAP_S390_DIAG318
Date: Thu, 25 Jun 2020 11:07:23 -0400
Message-Id: <20200625150724.10021-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200625150724.10021-1-walling@linux.ibm.com>
References: <20200625150724.10021-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-25_11:2020-06-25,2020-06-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 adultscore=0 impostorscore=0 mlxscore=0 phishscore=0 priorityscore=1501
 cotscore=-2147483648 suspectscore=8 bulkscore=0 clxscore=1015
 lowpriorityscore=0 mlxlogscore=999 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006250098
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Documentation for the s390 DIAGNOSE 0x318 instruction handling.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 Documentation/virt/kvm/api.rst | 20 ++++++++++++++++++++
 1 file changed, 20 insertions(+)

```
#### [PATCH v2] vfio/spapr_tce: convert get_user_pages() --> pin_user_pages()
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11624651
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D67866C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 06:37:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6B3B207E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 06:37:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="PzYJ3lae"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389951AbgFYGhV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 02:37:21 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:9181 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727999AbgFYGhU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Jun 2020 02:37:20 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ef446130000>; Wed, 24 Jun 2020 23:37:07 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Wed, 24 Jun 2020 23:37:20 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Wed, 24 Jun 2020 23:37:20 -0700
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 25 Jun
 2020 06:37:19 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 25 Jun 2020 06:37:20 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.59.206]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ef4461f0005>; Wed, 24 Jun 2020 23:37:20 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: LKML <linux-kernel@vger.kernel.org>
CC: John Hubbard <jhubbard@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>
Subject: [PATCH v2] vfio/spapr_tce: convert get_user_pages() -->
 pin_user_pages()
Date: Wed, 24 Jun 2020 23:37:17 -0700
Message-ID: <20200625063717.834923-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1593067027; bh=T8kM6kIhzYlig7AUGzoS+A4qc/UX6U40K3WHpkS7F4M=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Transfer-Encoding:
         Content-Type;
        b=PzYJ3lae3MPcCxOUNX59NTfx3uUcrmR2uRJaVRYyA3k0Wp4+0gX7xyZqXFse1JxWq
         0R9PMXLvoFGX731TeqEDRI/WZWNQUtRkW2t+mONUCcpiprl0dgUjuKXzrjsqZ8iceE
         8Y/Y6aU4kBZxJrs0CiS/pCXAxi11FP0ISPiAK8s39RzVzTr3nSJzR6wuEMIs4j9MMh
         HZ+87EQp1abZ2ixJK+7Olm10PPuvjY9TsJ5s4i/UrvkGe0WBGfh/BkgFcWbsi81xYb
         IdzPSrwWhvM6hdcsFyn9kMDPBZPYatjs8tJ4+dePb4XL2eiSN7rYDD6B3lIasQ1Ixn
         NOMJ8IW9Cg5Hg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This code was using get_user_pages*(), in a "Case 2" scenario
(DMA/RDMA), using the categorization from [1]. That means that it's
time to convert the get_user_pages*() + put_page() calls to
pin_user_pages*() + unpin_user_pages() calls.

There is some helpful background in [2]: basically, this is a small
part of fixing a long-standing disconnect between pinning pages, and
file systems' use of those pages.

[1] Documentation/core-api/pin_user_pages.rst

[2] "Explicit pinning of user-space pages":
    https://lwn.net/Articles/807108/

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---

Hi,

Changes since v1: rebased onto Linux-5.8-rc2.

thanks,
John Hubbard

 drivers/vfio/vfio_iommu_spapr_tce.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] vfio/pci: Fix SR-IOV VF handling with MMIO blockingFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11625763
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 14634618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 16:57:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF1A020791
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 16:57:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L/cdiRfU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403965AbgFYQ5Q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 12:57:16 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:27810 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390448AbgFYQ5Q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 12:57:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593104235;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=GF5LkOlnhTVNoedCdKoIYF7NkNTIxZXf2Tb7J0LGaQ4=;
        b=L/cdiRfUxVsivUDkBMKDfaB6n1++DKCrt1rXsnVN5nVzWDI9xwRXeg8QO60wo9NE+EVAKy
        e9wuEeS59H6oM+t4+ImN2qDrMeU8d8/j0ub+JnrD9oRIKxMbBIWJtJgNE+N9dvenGiYYvO
        YnnLrCiadGaoyWIv/JNIcCXJLd9cAK0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-200-wkv-tCLbMWuF2rp9omMg7w-1; Thu, 25 Jun 2020 12:57:12 -0400
X-MC-Unique: wkv-tCLbMWuF2rp9omMg7w-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0D636464;
        Thu, 25 Jun 2020 16:57:12 +0000 (UTC)
Received: from gimli.home (ovpn-112-156.phx2.redhat.com [10.3.112.156])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 08E855D9D3;
        Thu, 25 Jun 2020 16:57:03 +0000 (UTC)
Subject: [PATCH] vfio/pci: Fix SR-IOV VF handling with MMIO blocking
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        maxime.coquelin@redhat.com
Date: Thu, 25 Jun 2020 10:57:03 -0600
Message-ID: <159310421505.27590.16617666489295503039.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SR-IOV VFs do not implement the memory enable bit of the command
register, therefore this bit is not set in config space after
pci_enable_device().  This leads to an unintended difference
between PF and VF in hand-off state to the user.  We can correct
this by setting the initial value of the memory enable bit in our
virtualized config space.  There's really no need however to
ever fault a user on a VF though as this would only indicate an
error in the user's management of the enable bit, versus a PF
where the same access could trigger hardware faults.

Fixes: abafbc551fdd ("vfio-pci: Invalidate mmaps and block MMIO access on disabled memory")
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_config.c |   17 ++++++++++++++++-
 1 file changed, 16 insertions(+), 1 deletion(-)

```
#### [RFC 1/3] virtio-pci: use NUMA-aware memory allocation in probe
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Hajnoczi <stefanha@redhat.com>
X-Patchwork-Id: 11625405
Return-Path: <SRS0=Zyx7=AG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 115866C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:58:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB3A6206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 25 Jun 2020 13:58:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="a/wItYx+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405194AbgFYN6I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 25 Jun 2020 09:58:08 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:50936 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2404890AbgFYN6H (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Jun 2020 09:58:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593093485;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=I02RA+QYEkrvsrT/YPtoqYBWwQdCy39TUmoOUKOxREo=;
        b=a/wItYx+hLrle+LsB2fIkCtWyzfoIbFk9gIszn3n5aCLqGAjNxO4O6W+4V48GN+k02jbH3
        JX2krh4NLSnscjOkg/wrT0HjdqbFmhVM/Xbu9J8Io1CAp+n/2QD5EqEi6r/yScXYtGyFHR
        FjRQVLYrb5iIhgD+Z9Yhuc9BwkDp1PM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-253-K8C6TJENOjamXr91Nc0bMQ-1; Thu, 25 Jun 2020 09:58:03 -0400
X-MC-Unique: K8C6TJENOjamXr91Nc0bMQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 69B86804001;
        Thu, 25 Jun 2020 13:58:02 +0000 (UTC)
Received: from localhost (ovpn-115-49.ams2.redhat.com [10.36.115.49])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F94619D61;
        Thu, 25 Jun 2020 13:57:58 +0000 (UTC)
From: Stefan Hajnoczi <stefanha@redhat.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC 1/3] virtio-pci: use NUMA-aware memory allocation in probe
Date: Thu, 25 Jun 2020 14:57:50 +0100
Message-Id: <20200625135752.227293-2-stefanha@redhat.com>
In-Reply-To: <20200625135752.227293-1-stefanha@redhat.com>
References: <20200625135752.227293-1-stefanha@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allocate frequently-accessed data structures from the NUMA node
associated with this virtio-pci device. This avoids slow cross-NUMA node
memory accesses.

Only the following memory allocations are made NUMA-aware:

1. Called during probe. If called in the data path then hopefully we're
   executing on a CPU in the same NUMA node as the device. If the CPU is
   not in the right NUMA node then it's unclear whether forcing memory
   allocations to use the device's NUMA node will increase or decrease
   performance.

2. Memory will be frequently accessed from the data path. There is no
   need to worry about data that is not accessed from
   performance-critical code paths.

Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 drivers/virtio/virtio_pci_common.c | 16 ++++++++++++----
 1 file changed, 12 insertions(+), 4 deletions(-)

```
