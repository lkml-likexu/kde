#### [PATCH 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11497205
Return-Path: <SRS0=Tcga=6D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9ED1F913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Apr 2020 07:51:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8638E22209
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Apr 2020 07:51:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725964AbgDSHvT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 19 Apr 2020 03:51:19 -0400
Received: from out30-44.freemail.mail.aliyun.com ([115.124.30.44]:46496 "EHLO
        out30-44.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725903AbgDSHvT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 19 Apr 2020 03:51:19 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R181e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01f04427;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0Tvyj7vB_1587282668;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0Tvyj7vB_1587282668)
          by smtp.aliyun-inc.com(127.0.0.1);
          Sun, 19 Apr 2020 15:51:08 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
Date: Sun, 19 Apr 2020 15:51:00 +0800
Message-Id: <20200419075106.16248-2-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200419075106.16248-1-tianjia.zhang@linux.alibaba.com>
References: <20200419075106.16248-1-tianjia.zhang@linux.alibaba.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. Earlier than historical reasons, many kvm-related function
parameters retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time.
This patch does a unified cleanup of these remaining redundant parameters.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/s390/kvm/kvm-s390.c | 127 +++++++++++++++++++++------------------
 1 file changed, 67 insertions(+), 60 deletions(-)

```
#### [PATCH] KVM: X86: Fix compile error in svm/sev.c
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11497171
Return-Path: <SRS0=Tcga=6D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF1ED913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Apr 2020 07:31:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0E62221F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 19 Apr 2020 07:31:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725949AbgDSHa4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 19 Apr 2020 03:30:56 -0400
Received: from out30-132.freemail.mail.aliyun.com ([115.124.30.132]:35555
 "EHLO
        out30-132.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725446AbgDSHa4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 19 Apr 2020 03:30:56 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R131e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01358;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0TvywI99_1587281447;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TvywI99_1587281447)
          by smtp.aliyun-inc.com(127.0.0.1);
          Sun, 19 Apr 2020 15:30:48 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH] KVM: X86: Fix compile error in svm/sev.c
Date: Sun, 19 Apr 2020 15:30:47 +0800
Message-Id: <20200419073047.14413-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The compiler reported the following compilation errors:

arch/x86/kvm/svm/sev.c: In function ‘sev_pin_memory’:
arch/x86/kvm/svm/sev.c:361:3: error: implicit declaration of function
‘release_pages’ [-Werror=implicit-function-declaration]
   release_pages(pages, npinned);
   ^~~~~~~~~~~~~

The reason is that the 'pagemap.h' header file is not included.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/x86/kvm/svm/sev.c | 1 +
 1 file changed, 1 insertion(+)

```
