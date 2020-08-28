#### [PATCH RFC 1/2] riscv/kvm: Fix use VSIP_VALID_MASK mask HIP register
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11740281
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DADC414E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:24:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C9E2320738
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:24:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728246AbgH0IXw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 04:23:52 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:45808 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726395AbgH0IXv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 04:23:51 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 6322BE11D85A99240666;
        Thu, 27 Aug 2020 16:23:48 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.487.0; Thu, 27 Aug 2020
 16:23:42 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <paul.walmsley@sifive.com>, <palmer@dabbelt.com>,
        <aou@eecs.berkeley.edu>, <anup.patel@wdc.com>,
        <alistair.francis@wdc.com>, <atish.patra@wdc.com>,
        <deepa.kernel@gmail.com>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-riscv@lists.infradead.org>, <linux-kernel@vger.kernel.org>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC 1/2] riscv/kvm: Fix use VSIP_VALID_MASK mask HIP register
Date: Thu, 27 Aug 2020 16:22:50 +0800
Message-ID: <20200827082251.1591-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20200827082251.1591-1-jiangyifei@huawei.com>
References: <20200827082251.1591-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The correct sip/sie 0x222 could mask wrong 0x000 by VSIP_VALID_MASK,
This patch fix it.

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Yipeng Yin <yinyipeng1@huawei.com>
---
 arch/riscv/kvm/vcpu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RFC v3 01/14] linux-header: Update linux/kvm.h
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11740347
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8818D739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 09:23:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 700A42177B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 09:23:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728324AbgH0JWj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 05:22:39 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:10271 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728241AbgH0JWh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 05:22:37 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id DD3CB5AA9F2509329753;
        Thu, 27 Aug 2020 17:22:34 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.487.0; Thu, 27 Aug 2020
 17:22:26 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v3 01/14] linux-header: Update linux/kvm.h
Date: Thu, 27 Aug 2020 17:21:24 +0800
Message-ID: <20200827092137.479-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20200827092137.479-1-jiangyifei@huawei.com>
References: <20200827092137.479-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update linux-headers/linux/kvm.h from https://github.com/kvm-riscv/linux.
Only use this header file, so here do not update all linux headers by
update-linux-headers.sh until above KVM series is accepted.

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Yipeng Yin <yinyipeng1@huawei.com>
---
 linux-headers/linux/kvm.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH 1/3] SVM: nSVM: correctly restore GIF on vmexit from nesting after migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741019
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CD86722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 16:27:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F60722CAF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 16:27:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Rx9e3Gcf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727064AbgH0Q1n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 12:27:43 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:40586 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726200AbgH0Q1m (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 12:27:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598545660;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=V71RRp7TnJ/MIg+3QA5K7sfS8dmsGyA9hhRFvDd6tOE=;
        b=Rx9e3GcfLrJwjlXsYdv04LlGuNuNwCnE4XAfa8S6iyyyv2fXxE//WfbbDTh41kzpCmTR/B
        EIu8rKG8iphLfb9jz+slVLzpz4YYXdHylPQ1TDacsLgD+cpCCb0Ljyu6Y0EkmVgB/CP/yF
        v+sI4o1siZSrenwXhZZKGbnOs0N/2po=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-476-P-f5qfj3PCWWsSTjTBaCqg-1; Thu, 27 Aug 2020 12:27:37 -0400
X-MC-Unique: P-f5qfj3PCWWsSTjTBaCqg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4894918BA288;
        Thu, 27 Aug 2020 16:27:35 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 286BB5C1C2;
        Thu, 27 Aug 2020 16:27:29 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/3] SVM: nSVM: correctly restore GIF on vmexit from nesting
 after migration
Date: Thu, 27 Aug 2020 19:27:18 +0300
Message-Id: <20200827162720.278690-2-mlevitsk@redhat.com>
In-Reply-To: <20200827162720.278690-1-mlevitsk@redhat.com>
References: <20200827162720.278690-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently code in svm_set_nested_state copies the current vmcb control
area to L1 control area (hsave->control), under assumption that
it mostly reflects the defaults that kvm choose, and later qemu
overrides  these defaults with L2 state using standard KVM interfaces,
like KVM_SET_REGS.

However nested GIF (which is AMD specific thing) is by default is true,
and it is copied to hsave area as such.

This alone is not a big deal since on VMexit, GIF is always set to false,
regardless of what it was on VM entry.

However in nested_svm_vmexit we were first were setting GIF to false,
but then we overwrite this with value from the hsave area.

Now on normal vm entry this is not a problem, since GIF is false
prior to normal vm entry,
and this is the value that copied to hsave, and then restored,
but this is not always the case when the nested state is loaded as
explained above.

Anyway to fix this issue, move svm_set_gif after we restore the L1 control
state in nested_svm_vmexit, so that even with wrong GIF in the
saved L1 control area, we still clear GIF as the spec says.

All of this is only relevant when GIF virtualization is enabled,
(otherwise nested GIF doesn't reside in the vmcb).

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741087
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A37D109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:04:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70B7A2177B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:04:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BL0CmQEx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbgH0REx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 13:04:53 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:39033 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726323AbgH0REs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Aug 2020 13:04:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598547887;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uchtyp5DVRtl0VqaI00HMpgs89YiVvUyiaRTklLzvhY=;
        b=BL0CmQExBTdyGge8kvt2gJySOuAWJb33hIchAC6og25uO6fEO+QVIuAhhbYwn/H8XYCSyl
        L6+ncOMD2k+2oTIln3OqH6Wr+ePAIe8kuWmx2Z8WGh18YZDMGNhGlVB7iivyErS1MNOIvN
        BCJtk9KOE0hpYSfc6+nGq03qEyPCI2w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-550-c_UqdJtcP4i5a4dCMJIU0Q-1; Thu, 27 Aug 2020 13:04:45 -0400
X-MC-Unique: c_UqdJtcP4i5a4dCMJIU0Q-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E8E251029D20;
        Thu, 27 Aug 2020 17:04:43 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 80A6219D7D;
        Thu, 27 Aug 2020 17:04:40 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
Date: Thu, 27 Aug 2020 20:04:27 +0300
Message-Id: <20200827170434.284680-2-mlevitsk@redhat.com>
In-Reply-To: <20200827170434.284680-1-mlevitsk@redhat.com>
References: <20200827170434.284680-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'page' is to hold the vcpu's vmcb so name it as such to
avoid confusion.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH v3 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741133
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B1FB413B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:12:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9895620737
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:12:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="er1QEuRP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727784AbgH0RMH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 13:12:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:32781 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727084AbgH0RMH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 13:12:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598548326;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uchtyp5DVRtl0VqaI00HMpgs89YiVvUyiaRTklLzvhY=;
        b=er1QEuRPHuLywTHB/SVDbxKutnoeriNLng13OTJoFe/WdG1YuCduMvrjsSKSLLr76Vz/By
        BfEtw2AjDLz8vAILjiQN2S0iqJrXEw5ya7+a49wY08iWID6WAoW7G2u8VyrSFimbUE/chU
        AInpE+GufF2Ouww9hu91HRzZYz+shrM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-524-Spc_LnLqN0aOBBtLmk_-XA-1; Thu, 27 Aug 2020 13:11:57 -0400
X-MC-Unique: Spc_LnLqN0aOBBtLmk_-XA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1CBFB10ABDD4;
        Thu, 27 Aug 2020 17:11:56 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 72FB15D9E8;
        Thu, 27 Aug 2020 17:11:50 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v3 1/8] KVM: SVM: rename a variable in the svm_create_vcpu
Date: Thu, 27 Aug 2020 20:11:38 +0300
Message-Id: <20200827171145.374620-2-mlevitsk@redhat.com>
In-Reply-To: <20200827171145.374620-1-mlevitsk@redhat.com>
References: <20200827171145.374620-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'page' is to hold the vcpu's vmcb so name it as such to
avoid confusion.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: refine delivery_mode check
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11740193
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F05D14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:01:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C6A922BF3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:01:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728367AbgH0IBh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 04:01:37 -0400
Received: from mx55.baidu.com ([61.135.168.55]:10274 "EHLO
        tc-sys-mailedm01.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726851AbgH0IBg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Aug 2020 04:01:36 -0400
X-Greylist: delayed 390 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 27 Aug 2020 04:01:35 EDT
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm01.tc.baidu.com (Postfix) with ESMTP id 478D8204005A;
        Thu, 27 Aug 2020 15:54:49 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: kvm@vger.kernel.org, x86@kernel.org
Subject: [PATCH] KVM: x86: refine delivery_mode check
Date: Thu, 27 Aug 2020 15:54:49 +0800
Message-Id: <1598514889-23810-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

delivery_mode of kvm_ioapic_redirect_entry, is 3 bits width
value, should be shifted 8bits when check with APIC_DM_FIXED
whose value bits are from bit 8 to bit 10. although it works
because APIC_DM_FIXED is zero

Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
 arch/x86/kvm/ioapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
