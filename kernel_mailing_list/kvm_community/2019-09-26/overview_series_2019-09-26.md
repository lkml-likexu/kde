#### [PATCH 1/2] kvm: x86: Improve emulation of CPUID leaves 0BH and 1FHFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11161749
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E53CF112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 00:05:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B8FE5208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 00:05:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FZ33j6yh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733311AbfIZAE3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 20:04:29 -0400
Received: from mail-qk1-f201.google.com ([209.85.222.201]:53767 "EHLO
        mail-qk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733141AbfIZAE2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 20:04:28 -0400
Received: by mail-qk1-f201.google.com with SMTP id g62so566908qkb.20
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 17:04:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=0aiAhoNw7rgiXm4ReXuu/I7OpOSCaP8Se4pfHqvUc7o=;
        b=FZ33j6yhM793vppuNUJ9eG0snnRS4NCqlhG5FAi4ykVYuzZIJU0X82/o4XRchT08q5
         hhvT1EE+SfGeuv04QsX2h08Clq95IfQZz4l5xfbnGT+ntVsR255IFyUIqiZTAMMlqcIJ
         0h6H15f+74Sj5CmhgSvdPYY+xYZP/sLwRmd/hTkjndwUf5/2SQtYz+61RF3cJeVNYN3o
         x46ChISCwdKDzhqxeKwhalNozHauDMkxiRaFztYT7/OpTTrsLJgk2EON40LIO8+rXJ1r
         UeZhqOrHSSsosQh0LNC8NIUXU63MGXtexfnM1tiEudCkd5DsQ5d28a8jo84IQe/iMTXv
         mXhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=0aiAhoNw7rgiXm4ReXuu/I7OpOSCaP8Se4pfHqvUc7o=;
        b=Wo1YGI0VKQ2uWFzt5cGbSryLEocxOMgkhJ0ykaV3eF2TGqfzFE78EUIIgt9Nb+Kkgy
         bOYYzc/edMVj7E7Mrzz1yz1Ct1SrzmSu5k48Ynor/sbhRwbkrs1097gWD/OCJL2difQ2
         GFt+c8I6m7Cl5CBu7yTJDvcmiOTfffKp4jGaMTW1jsH+etz6TGAXdxqTNvLXDgplIYOq
         oweovlL4DLVFcdHGiQeOCmkglXsiEXP1eJn+yyCnbeFCpGvPL3OK6iNBylqiGMn6cWx+
         Es4DGPDfvNYmmkSBjFem0hD0EXslRxpyiS0SEtR1R9v6qOL4tmpTNyzSYQKilQnJgTa9
         p2qA==
X-Gm-Message-State: APjAAAXZ67/j/rYw4Lq/6rf6eMbJN26V1LJ9R2r7n0Hz17Q3DarBocOF
        SQEI9VBVcTprS0fVfqquBcz68j8UUjyBKKq4sgMmjFjUC5z+MT6ffMCWVd/XEXR3JlRascaC/Lb
        9tzS/ugs2+P8uutwNJkOPS85um7eZ7Vir9cXC3wldXis4RBi8x4vWog1CDBpoaCY=
X-Google-Smtp-Source: 
 APXvYqwV/ff1pFk/QG7OJ4dfX+tMHLc3N+0sDlTyyzdy2GU5+St5jjQGj3Yin7FYJgTVbov9tmPmtH17c5EMdA==
X-Received: by 2002:ac8:7244:: with SMTP id l4mr1254814qtp.40.1569456267027;
 Wed, 25 Sep 2019 17:04:27 -0700 (PDT)
Date: Wed, 25 Sep 2019 17:04:17 -0700
Message-Id: <20190926000418.115956-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [PATCH 1/2] kvm: x86: Improve emulation of CPUID leaves 0BH and 1FH
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Marc Orr <marcorr@google.com>,
        Peter Shier <pshier@google.com>,
        Jacob Xu <jacobhxu@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For these CPUID leaves, the EDX output is not dependent on the ECX
input (i.e. the SIGNIFCANT_INDEX flag doesn't apply to
EDX). Furthermore, the low byte of the ECX output is always identical
to the low byte of the ECX input. KVM does not produce the correct ECX
and EDX outputs for any undefined subleaves beyond the first.

Special-case these CPUID leaves in kvm_cpuid, so that the ECX and EDX
outputs are properly generated for all undefined subleaves.

Fixes: 0771671749b59a ("KVM: Enhance guest cpuid management")
Fixes: a87f2d3a6eadab ("KVM: x86: Add Intel CPUID.1F cpuid emulation support")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jacob Xu <jacobhxu@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/cpuid.c | 83 +++++++++++++++++++++++++-------------------
 1 file changed, 47 insertions(+), 36 deletions(-)

```
#### [RFC PATCH v4 1/5] psci: Export psci_ops.conduit symbol as modules will use it.
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11162619
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3749F924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 11:42:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1FD15222C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 11:42:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726406AbfIZLm3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 07:42:29 -0400
Received: from foss.arm.com ([217.140.110.172]:47060 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726376AbfIZLm3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 07:42:29 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 8FBDD1570;
        Thu, 26 Sep 2019 04:42:28 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 06BB93F67D;
        Thu, 26 Sep 2019 04:42:23 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com,
        Will.Deacon@arm.com, suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v4 1/5] psci: Export psci_ops.conduit symbol as modules
 will use it.
Date: Thu, 26 Sep 2019 19:42:08 +0800
Message-Id: <20190926114212.5322-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190926114212.5322-1-jianyong.wu@arm.com>
References: <20190926114212.5322-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If arm_smccc_1_1_invoke used in modules, psci_ops.conduit should
be export.

Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 drivers/firmware/psci/psci.c | 6 ++++++
 include/linux/arm-smccc.h    | 2 +-
 include/linux/psci.h         | 1 +
 3 files changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: x86: assign two bits to track SPTE kinds
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11163043
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AAE413B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 17:18:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 131E3222C9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 17:18:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="hc4dBRiR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727729AbfIZRSe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 13:18:34 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:36926 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727591AbfIZRSd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 13:18:33 -0400
Received: by mail-wr1-f66.google.com with SMTP id i1so3676057wro.4;
        Thu, 26 Sep 2019 10:18:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=GkS5kuygwejg7PDcUIWyOZOfFuOcNn5PfD7h7RT01L8=;
        b=hc4dBRiR+3MmRXD2YSP7YYzYvRBEAnPNowN/puMUP1el9LVeDWcq967Jr0fVUCVshq
         93IAV5lc2ccJzqvpWXtUn5sheJLkI/RnfIbevezrSMAq/XNR37NJ6aaBhJ+t8SWc0sAI
         +9qVLstrNGSRxd8EXlK8qXcOWpbc/xrJe65m/fgY5eHBNjLqFciqSaYK+aixBOKKS3Wv
         1W00G87OZ3xCgzezwbzDkiZfyXCNrtTnVdk+NhDSDT6Pq1SmtFmbIlSyz9iFQsjymMLR
         FEoDkZkWJ2BtJ/mzXBKw25oYu4aHDgkAn6Sq8EBDD25wMsl4/LuYuz87uZegs2DrhCrG
         XFyA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=GkS5kuygwejg7PDcUIWyOZOfFuOcNn5PfD7h7RT01L8=;
        b=Hivn8XF2eijKGk25llm28AeXObGFByHl3izo2EpaffhIrwMNXY4JxUiqfhEofbywnI
         oASgGc3t/Y2ybhDlI1Zj++v7LAMCXiEF8nB5ez82nJVhBG5bmkPV4uatIXb3EK+Zrsnx
         r7oIiW0vmKAO8tpjn+HD0E3t/l493Ips75/BSgNhejH0iXCF1yetBksL+eAnsICjEXV7
         OnZVUlcUHcbgm/gY/NYvj2kDEd+YCupYpkMQ7TVIaep8FZEuc/0OldXOebVBtDK+gdY8
         h4JWn9MUQxlLnHJ4D/bNIGiYry1ibglgreA6ViHqjl+1BIxlR3iDV3vxwPyrp7xx9zjQ
         T1nw==
X-Gm-Message-State: APjAAAX/P+rs8B/pv34AwDdOW9pjZhYtKu9ZE4b4n/BTStpCarMjMoTL
        8RovfqMfsJpi9IM+wmeikxflE7Bt
X-Google-Smtp-Source: 
 APXvYqyalDAeXllKtzEFt9yvgqyJ7wKa7qILmmc3n0LyiYfUMGmBIHAkg/Gcn9RFmXVLspBWL7Opog==
X-Received: by 2002:a5d:42cb:: with SMTP id t11mr3658891wrr.99.1569518309883;
        Thu, 26 Sep 2019 10:18:29 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 v4sm4792782wrg.56.2019.09.26.10.18.29
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 26 Sep 2019 10:18:29 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH 1/3] KVM: x86: assign two bits to track SPTE kinds
Date: Thu, 26 Sep 2019 19:18:24 +0200
Message-Id: <1569518306-46567-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1569518306-46567-1-git-send-email-pbonzini@redhat.com>
References: <1569518306-46567-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we are overloading SPTE_SPECIAL_MASK to mean both
"A/D bits unavailable" and MMIO, where the difference between the
two is determined by mio_mask and mmio_value.

However, the next patch will need two bits to distinguish
availability of A/D bits from write protection.  So, while at
it give MMIO its own bit pattern, and move the two bits from
bit 62 to bits 52..53 since Intel is allocating EPT page table
bits from the top.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  7 -------
 arch/x86/kvm/mmu.c              | 28 ++++++++++++++++++----------
 2 files changed, 18 insertions(+), 17 deletions(-)

```
#### [PATCH 1/2] KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11163381
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9033A76
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 21:43:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 77A51222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 21:43:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726394AbfIZVnJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 17:43:09 -0400
Received: from mga07.intel.com ([134.134.136.100]:8270 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725943AbfIZVnF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 17:43:05 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Sep 2019 14:43:03 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,553,1559545200";
   d="scan'208";a="192958528"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga003.jf.intel.com with ESMTP; 26 Sep 2019 14:43:03 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reto Buerki <reet@codelabs.ch>
Subject: [PATCH 1/2] KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested
 VM-Enter
Date: Thu, 26 Sep 2019 14:43:01 -0700
Message-Id: <20190926214302.21990-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190926214302.21990-1-sean.j.christopherson@intel.com>
References: <20190926214302.21990-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Write the desired L2 CR3 into vmcs02.GUEST_CR3 during nested VM-Enter
isntead of deferring the VMWRITE until vmx_set_cr3().  If the VMWRITE
is deferred, then KVM can consume a stale vmcs02.GUEST_CR3 when it
refreshes vmcs12->guest_cr3 during nested_vmx_vmexit() if the emulated
VM-Exit occurs without actually entering L2, e.g. if the nested run
is squashed because L2 is being put into HLT.

In an ideal world where EPT *requires* unrestricted guest (and vice
versa), VMX could handle CR3 similar to how it handles RSP and RIP,
e.g. mark CR3 dirty and conditionally load it at vmx_vcpu_run().  But
the unrestricted guest silliness complicates the dirty tracking logic
to the point that explicitly handling vmcs02.GUEST_CR3 during nested
VM-Enter is a simpler overall implementation.

Cc: stable@vger.kernel.org
Reported-by: Reto Buerki <reet@codelabs.ch>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 8 ++++++++
 arch/x86/kvm/vmx/vmx.c    | 9 ++++++---
 2 files changed, 14 insertions(+), 3 deletions(-)

```
#### [RFC PATCH] KVM: VMX: Always sync CR3 to VMCS in nested_vmx_load_cr3
##### From: Reto Buerki <reet@codelabs.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Reto Buerki <reet@codelabs.ch>
X-Patchwork-Id: 11162819
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 505D41599
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 14:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 384EC222C5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 14:15:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727163AbfIZOP0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 10:15:26 -0400
Received: from mail.codelabs.ch ([109.202.192.35]:57710 "EHLO
 mail.codelabs.ch"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727158AbfIZOPZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 10:15:25 -0400
Received: from localhost (localhost [127.0.0.1])
        by mail.codelabs.ch (Postfix) with ESMTP id 49E7CA0167;
        Thu, 26 Sep 2019 16:05:52 +0200 (CEST)
Received: from mail.codelabs.ch ([127.0.0.1])
        by localhost (fenrir.codelabs.ch [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id h7q0wHkKej5w; Thu, 26 Sep 2019 16:05:50 +0200 (CEST)
Received: from skyhawk.codelabs.ch (unknown [192.168.10.191])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.codelabs.ch (Postfix) with ESMTPSA id 38CC8A0166;
        Thu, 26 Sep 2019 16:05:50 +0200 (CEST)
From: Reto Buerki <reet@codelabs.ch>
To: kvm@vger.kernel.org
Subject: [RFC PATCH] KVM: VMX: Always sync CR3 to VMCS in nested_vmx_load_cr3
Date: Thu, 26 Sep 2019 16:05:41 +0200
Message-Id: <20190926140541.15453-2-reet@codelabs.ch>
In-Reply-To: <20190926140541.15453-1-reet@codelabs.ch>
References: <20190926140541.15453-1-reet@codelabs.ch>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Required to make a Muen system work on KVM nested.

Signed-off-by: Reto Buerki <reet@codelabs.ch>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH net v2] vsock: Fix a lockdep warning in __vsock_release()Thread-Topic: [PATCH net v2] vsock: Fix a lockdep warning in __vsock_release()
##### From: Dexuan Cui <decui@microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dexuan Cui <decui@microsoft.com>
X-Patchwork-Id: 11161771
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD76C14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 01:11:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9E742222BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 01:11:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=microsoft.com header.i=@microsoft.com
 header.b="JxD1ijDT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729556AbfIZBLc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 21:11:32 -0400
Received: from mail-eopbgr680130.outbound.protection.outlook.com
 ([40.107.68.130]:42460
        "EHLO NAM04-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725943AbfIZBLc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 21:11:32 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gXs5Y6X8Muf9QDYugqPTjcIChuSZMOs4fP2GuvKQjCwk57LdKoGo/4b0V/0uJA9+d+ed4hGciuzFCHlBHVaN8Xzx6kj0DRdKkMPoE5TLrKe7UMBSDEEJbSn16S5GtGOvgCZIqx3jvpB2lppgY6i9WWNlv1m+5I6o3/RV/Ol+z/072iyjnN580HTdr5m8nFynOBScY1L5ZpwpTNzpCy+Mt94zfQEMvujS112Z5X7jcLbRuXctI8L6bBc5MTWajhk4g8E3mgC2kM+RFQCjhy8a6kvSf3M+Q0gl47gaFtMr1RSoqhA0sj96dM96qpyRXGMN5gEFLI9MQjlEmhRY11fxyQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kaSt70zK0SQxbnC2gp4oZ7f1ncDlx8JQAZhaoL/VWHI=;
 b=VkOKNsNG0sdT6V0FNxiZVED+wmWU60zSrrTytgHudHZl9Egp16c6+ULcGclF/qJiOVrxLLDewp/UizlIoLMVlIp/VtVrJELka7BDxXU1CEDubux3Gtl3NhQfHWwE5RXq5vhceMa8j+m9yPYYna3ugIiFCXl8KhgVhFNy4yv35hRQLEg1Hofv2gNm2oToEUBhFuE5AHpY/5Lfd6vxk49OIvRpQQi28hBb7TK8zK/4NzpM7OfYREhKxXSrj/HQNsJR7TJtQar5rYyL+J8HoEDGyG+iYiQbE6Tkkef6WU4uG+BUHG8Bm16j9w6ybkK1RZgqkOIjOr0jscpa4OY/dNYbDw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=microsoft.com; dmarc=pass action=none
 header.from=microsoft.com; dkim=pass header.d=microsoft.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kaSt70zK0SQxbnC2gp4oZ7f1ncDlx8JQAZhaoL/VWHI=;
 b=JxD1ijDTa1XQuiyc1pYCVItCE0CMvaWMJHZc7ymSYpjqREFlZum4R9EekZw5hBOz7rw4GvUt1+DAPzTGhUCJjangABLbpJzyLHG3SrU1chysBW7+35EdnAHPnfhL2QV3MVzISo5yWdFHt1yljTul961GRCjrJhwwe6Z56tnRRq8=
Received: from SN6PR2101MB0942.namprd21.prod.outlook.com (52.132.114.19) by
 SN6PR2101MB0974.namprd21.prod.outlook.com (52.132.114.27) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2327.6; Thu, 26 Sep 2019 01:11:27 +0000
Received: from SN6PR2101MB0942.namprd21.prod.outlook.com
 ([fe80::7d1a:ddb:3473:b383]) by SN6PR2101MB0942.namprd21.prod.outlook.com
 ([fe80::7d1a:ddb:3473:b383%9]) with mapi id 15.20.2327.004; Thu, 26 Sep 2019
 01:11:27 +0000
From: Dexuan Cui <decui@microsoft.com>
To: "davem@davemloft.net" <davem@davemloft.net>,
        KY Srinivasan <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        "sashal@kernel.org" <sashal@kernel.org>,
        "stefanha@redhat.com" <stefanha@redhat.com>,
        "gregkh@linuxfoundation.org" <gregkh@linuxfoundation.org>,
        "arnd@arndb.de" <arnd@arndb.de>,
        "deepa.kernel@gmail.com" <deepa.kernel@gmail.com>,
        Dexuan Cui <decui@microsoft.com>,
        "ytht.net@gmail.com" <ytht.net@gmail.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "netdev@vger.kernel.org" <netdev@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "virtualization@lists.linux-foundation.org"
        <virtualization@lists.linux-foundation.org>,
        Michael Kelley <mikelley@microsoft.com>,
        "sgarzare@redhat.com" <sgarzare@redhat.com>,
        "jhansen@vmware.com" <jhansen@vmware.com>
Subject: [PATCH net v2] vsock: Fix a lockdep warning in __vsock_release()
Thread-Topic: [PATCH net v2] vsock: Fix a lockdep warning in __vsock_release()
Thread-Index: AQHVdAdSHQkvUaSfZES8M2hNpnvQKg==
Date: Thu, 26 Sep 2019 01:11:27 +0000
Message-ID: <1569460241-57800-1-git-send-email-decui@microsoft.com>
Reply-To: Dexuan Cui <decui@microsoft.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MWHPR08CA0012.namprd08.prod.outlook.com
 (2603:10b6:301:5f::25) To SN6PR2101MB0942.namprd21.prod.outlook.com
 (2603:10b6:805:4::19)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=decui@microsoft.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 1.8.3.1
x-originating-ip: [13.77.154.182]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 7f6e13ac-ba2a-48c6-f94c-08d7421e74cb
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: SN6PR2101MB0974:|SN6PR2101MB0974:
x-ms-exchange-transport-forked: True
x-ms-exchange-purlcount: 1
x-microsoft-antispam-prvs: 
 <SN6PR2101MB0974D0D64A0501309E9947C0BF860@SN6PR2101MB0974.namprd21.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:1468;
x-forefront-prvs: 0172F0EF77
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(136003)(396003)(346002)(376002)(366004)(39860400002)(199004)(189003)(8936002)(66556008)(6436002)(81166006)(110136005)(81156014)(8676002)(2906002)(386003)(66946007)(6486002)(6506007)(476003)(66446008)(2201001)(66476007)(6306002)(10090500001)(52116002)(64756008)(7736002)(43066004)(50226002)(2616005)(4720700003)(22452003)(486006)(316002)(99286004)(14444005)(25786009)(66066001)(36756003)(5660300002)(1511001)(102836004)(86362001)(6116002)(3846002)(6512007)(71200400001)(14454004)(2501003)(966005)(256004)(3450700001)(71190400001)(186003)(26005)(10290500003)(305945005)(7416002)(478600001)(921003)(1121003);DIR:OUT;SFP:1102;SCL:1;SRVR:SN6PR2101MB0974;H:SN6PR2101MB0942.namprd21.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: microsoft.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 zDxKH2hFQEvMhjrZEF6zg0k78XYP2yRBjwo0c5xeoumDjIO7UQjo3yg+NrxpmhhhUxR3zLZsGsm4ZGF/qz63wNfy4whHhLE2uiQKiX8ggh0fJuq/pjajlYUGk9SZAF9v+DbIEa7ghUMxrLXO0EQioLqVi4nVuxuhzr6BFhhC9qzPSVFq2BvwOz2zM1rmVQIlbFqmHw7Xf/4tNEjoR9UJki6m+2AJ6726FcZphevqkHFlIdIb1cZftH6cmtqWRimebAnF7S9lhKxt8HrY3+jBdkq7E6yWHW2veIgtCTSQybX9QrL0hLzX14hqFeyOY/3Fry3dKPVJBsSPGsk5WEzkahztWO0T7ZfK0tfwoItYhS1Bxaivgm2wTa9ONAeMwS+YBu9ub6nnMhYSrn4fp1qfKpx6HPIyXOQR6xAi7mfCjj7GUVoZvvYGfxMc63n2USBTj20vVBshkLcYrtyvNwBLzQ==
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: microsoft.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7f6e13ac-ba2a-48c6-f94c-08d7421e74cb
X-MS-Exchange-CrossTenant-originalarrivaltime: 26 Sep 2019 01:11:27.5779
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 72f988bf-86f1-41af-91ab-2d7cd011db47
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 pDTK7QoOE/3Eq07vl5g7UEagi9bAe+QSzq43Uw/S5PYwHxGB8nniP05dIHeupm6dTXD990pv9/7oJs/YWKdH0w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR2101MB0974
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Lockdep is unhappy if two locks from the same class are held.

Fix the below warning for hyperv and virtio sockets (vmci socket code
doesn't have the issue) by using lock_sock_nested() when __vsock_release()
is called recursively:

============================================
WARNING: possible recursive locking detected
5.3.0+ #1 Not tainted
--------------------------------------------
server/1795 is trying to acquire lock:
ffff8880c5158990 (sk_lock-AF_VSOCK){+.+.}, at: hvs_release+0x10/0x120 [hv_sock]

but task is already holding lock:
ffff8880c5158150 (sk_lock-AF_VSOCK){+.+.}, at: __vsock_release+0x2e/0xf0 [vsock]

other info that might help us debug this:
 Possible unsafe locking scenario:

       CPU0
       ----
  lock(sk_lock-AF_VSOCK);
  lock(sk_lock-AF_VSOCK);

 *** DEADLOCK ***

 May be due to missing lock nesting notation

2 locks held by server/1795:
 #0: ffff8880c5d05ff8 (&sb->s_type->i_mutex_key#10){+.+.}, at: __sock_release+0x2d/0xa0
 #1: ffff8880c5158150 (sk_lock-AF_VSOCK){+.+.}, at: __vsock_release+0x2e/0xf0 [vsock]

stack backtrace:
CPU: 5 PID: 1795 Comm: server Not tainted 5.3.0+ #1
Call Trace:
 dump_stack+0x67/0x90
 __lock_acquire.cold.67+0xd2/0x20b
 lock_acquire+0xb5/0x1c0
 lock_sock_nested+0x6d/0x90
 hvs_release+0x10/0x120 [hv_sock]
 __vsock_release+0x24/0xf0 [vsock]
 __vsock_release+0xa0/0xf0 [vsock]
 vsock_release+0x12/0x30 [vsock]
 __sock_release+0x37/0xa0
 sock_close+0x14/0x20
 __fput+0xc1/0x250
 task_work_run+0x98/0xc0
 do_exit+0x344/0xc60
 do_group_exit+0x47/0xb0
 get_signal+0x15c/0xc50
 do_signal+0x30/0x720
 exit_to_usermode_loop+0x50/0xa0
 do_syscall_64+0x24e/0x270
 entry_SYSCALL_64_after_hwframe+0x49/0xbe
RIP: 0033:0x7f4184e85f31

Signed-off-by: Dexuan Cui <decui@microsoft.com>
---

NOTE: I only tested the code on Hyper-V. I can not test the code for
virtio socket, as I don't have a KVM host. :-( Sorry.

@Stefan, @Stefano: please review & test the patch for virtio socket,
and let me know if the patch breaks anything. Thanks!

Changes in v2:
  Avoid the duplication of code in v1: https://lkml.org/lkml/2019/8/19/1361
  Also fix virtio socket code.

 net/vmw_vsock/af_vsock.c                | 19 +++++++++++++++----
 net/vmw_vsock/hyperv_transport.c        |  2 +-
 net/vmw_vsock/virtio_transport_common.c |  2 +-
 3 files changed, 17 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: LAPIC: Loose fluctuation filter for auto tune lapic_timer_advance_ns
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11161769
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0246F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 00:54:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CE45621D7B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 00:54:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="CVS5CuuE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726988AbfIZAyJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 20:54:09 -0400
Received: from mail-pl1-f196.google.com ([209.85.214.196]:38052 "EHLO
        mail-pl1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725943AbfIZAyI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 20:54:08 -0400
Received: by mail-pl1-f196.google.com with SMTP id w10so483010plq.5;
        Wed, 25 Sep 2019 17:54:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=8Z6sKx/0P0u+Z8GgG8NcI3yZDJtsQNc+elyq5c7t7uY=;
        b=CVS5CuuEyeJ9AxOuRXwFQBHDKIpQVJlflZCXpP9w2R2qUkhxDWKw4PHYYDceTGzXIl
         aRf90qJvN0dXzDy0eFubAesTX38DEr/sQYiKVIyq9u/p2Az0mzbC2cRYIV+RWTEu8g49
         5EZ4mTZWj5XTCTMn/oRj9AAFcYoPzcF2/Etci9tqjz3ibvqKwn+4xt/tOnTSXFkZ+xGR
         e5FxqyI4Qz3yzZ+vpoERiACapz36J/iLqHDiwLmCPx3WOtrwSGJxNKqPzgTkkUyj1pmO
         fH7+Gn1hQu4vUqn0vkhoaZ7PToj6tpllTaxM8bbWJJxnFf7Y43mflhgHFopwYqoSnQxE
         VQ4A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=8Z6sKx/0P0u+Z8GgG8NcI3yZDJtsQNc+elyq5c7t7uY=;
        b=pM/WnwokbBLYamN/mO+16LGlnYao7B368U2g2Sbnuz3an3w3EtWRfHOTgYMwOM1aH8
         Al/XUfSq4vy3f/E07ja9Cj/BUvsU9rK3A8vnLXPucEeySa2+uEIsSYticm/KtZ+nmzLP
         R/kdQhNycFCU4JGASJDwCCA/iMtHEvSMMiTZD36kOKrIAVWoTT5ESHZTBZcqLDI+8JWx
         6zn4BzFKHfJ4iN4//YyeE0Fqr3XDXA/4NrW7oMknsowEzzi0xNB6YtudDYjALeuVmJur
         OQOuRu4eRyXrLSSt5CDa6QOH3Q2wDw5BIImBQ9RD31HIEWrirBOrGrmrUU2DVeeI3ht1
         HNiA==
X-Gm-Message-State: APjAAAUzdvQOCHkqsc9A69l49Pv9SfBzGrSyOraVKAnxzoTc9AqggpSI
        q/dwunzVwLXRHH0ZU91/yUZudHk4
X-Google-Smtp-Source: 
 APXvYqxIFnfj+RoZcEVjaRNZGH4fjsfzhfgirIv+2mKqixHQVmaVu6O+3sOeBAHs12+ULSak9LyvVw==
X-Received: by 2002:a17:902:36e:: with SMTP id
 101mr1372100pld.46.1569459247956;
        Wed, 25 Sep 2019 17:54:07 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 h4sm211320pgg.81.2019.09.25.17.54.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 25 Sep 2019 17:54:07 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: LAPIC: Loose fluctuation filter for auto tune
 lapic_timer_advance_ns
Date: Thu, 26 Sep 2019 08:54:03 +0800
Message-Id: <1569459243-21950-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

5000 guest cycles delta is easy to encounter on desktop, per-vCPU 
lapic_timer_advance_ns always keeps at 1000ns initial value, lets 
loose fluctuation filter a bit to make auto tune can make some 
progress.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * separate defines for ns vs cycles

 arch/x86/kvm/lapic.c | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [PATCH] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11161853
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66A731709
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 04:58:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 34D3A222BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 04:58:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388299AbfIZE6A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 00:58:00 -0400
Received: from mga03.intel.com ([134.134.136.65]:20004 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731361AbfIZE6A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 00:58:00 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 25 Sep 2019 21:57:59 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,550,1559545200";
   d="scan'208";a="180048349"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.73])
  by orsmga007.jf.intel.com with ESMTP; 25 Sep 2019 21:57:56 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH] vhost: introduce mdev based hardware backend
Date: Thu, 26 Sep 2019 12:54:27 +0800
Message-Id: <20190926045427.4973-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a mdev based hardware vhost backend.
This backend is built on top of the same abstraction used
in virtio-mdev and provides a generic vhost interface for
userspace to accelerate the virtio devices in guest.

This backend is implemented as a mdev device driver on top
of the same mdev device ops used in virtio-mdev but using
a different mdev class id, and it will register the device
as a VFIO device for userspace to use. Userspace can setup
the IOMMU with the existing VFIO container/group APIs and
then get the device fd with the device name. After getting
the device fd of this device, userspace can use vhost ioctls
to setup the backend.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
This patch depends on below series:
https://lkml.org/lkml/2019/9/24/357

RFC v4 -> v1:
- Implement vhost-mdev as a mdev device driver directly and
  connect it to VFIO container/group. (Jason);
- Pass ring addresses as GPAs/IOVAs in vhost-mdev to avoid
  meaningless HVA->GPA translations (Jason);

RFC v3 -> RFC v4:
- Build vhost-mdev on top of the same abstraction used by
  virtio-mdev (Jason);
- Introduce vhost fd and pass VFIO fd via SET_BACKEND ioctl (MST);

RFC v2 -> RFC v3:
- Reuse vhost's ioctls instead of inventing a VFIO regions/irqs
  based vhost protocol on top of vfio-mdev (Jason);

RFC v1 -> RFC v2:
- Introduce a new VFIO device type to build a vhost protocol
  on top of vfio-mdev;

 drivers/vhost/Kconfig      |   9 +
 drivers/vhost/Makefile     |   3 +
 drivers/vhost/mdev.c       | 381 +++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vhost.h |   8 +
 4 files changed, 401 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
#### [PATCH] vsock/virtio: add support for MSG_PEEK
##### From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
X-Patchwork-Id: 11163211
Return-Path: <SRS0=ErSa=XV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 36A8E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 18:24:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 13DDF222CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Sep 2019 18:24:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mlp9FZYj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728375AbfIZSYB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 14:24:01 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:35802 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728344AbfIZSYB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 14:24:01 -0400
Received: by mail-wm1-f67.google.com with SMTP id y21so3624667wmi.0;
        Thu, 26 Sep 2019 11:23:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=wFzdQhWIvc4o013rKOjzXnkI0hw4CN3pNRalveb6WiY=;
        b=mlp9FZYjOcggNH5ah+Qu7XKJxpriLOVjPbYSJUxzDQE8StmLy/n03BoLkT0LvUWjja
         e5tEkQoSBIZSG+LRNf2ZwwauoeqWgj1ej4+saLQORMZ/cUaMprLri8l9hro+6lK48We2
         0X27RKQomTIS4EI7rP9ZRw7nbZ+DscF2TqUY3402NDsR3nJPeMC3M4qfEos7bSQ2fQMe
         kWBPIELUdz2FEmQWBzI7PUxGCMld6sqKBPWf/P7pQ3ybgW0mL3SItSsOMhlNGgBcjEkG
         dFxwGjUZKZy4cLc8687J0pjtKJCc3j0YNLzVrewtKir/+eC/FtcwTQ14mBa+63qhAkbS
         jGrw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=wFzdQhWIvc4o013rKOjzXnkI0hw4CN3pNRalveb6WiY=;
        b=lJi49zV9u6O2a35dDSJjO+/WNb+MqqNfhRFVNir54o4DsqfII9Za+dsFkwMY3/4o+j
         fKOIFpZIzw9MXyNJg+llCFlnVr1QsQOGcsnHahNkRu8Il0aCS83bErvtEO2KXmokX7Z7
         cFJE4k7wGHfuyyJE/TTi8W+SgnE3ahPKaHH77HMIc0pa1ZG/J3QwGkagFs0rlOq/cGBq
         o4+Fdnimznt/p8Nd6Miu7FBObfJd+HWznZaI9IvMlWXRBBdjnQax0pZwA4rC2I2Tyu0v
         gaI30CzOok7EtsjzMkn7A48NPyXL1EKGX8H/gyMCDIVMPcNzYj1L2yNTPKzCCJIOuveV
         A54g==
X-Gm-Message-State: APjAAAXNckww9Xl36peVe5YQnywWYTQ0f6VVkcs5l5KHBud85qGEkVM0
        qQ4mIM73C7Q7g0o+1UTGMbM=
X-Google-Smtp-Source: 
 APXvYqy32luIXUjI1tWlLHkiv6GgGQPfBm9QTxPNQ0lhqDsuVqOaSF3mmVMHuM4QQNFD40ARFyIDag==
X-Received: by 2002:a7b:c10b:: with SMTP id w11mr3932165wmi.108.1569522238802;
        Thu, 26 Sep 2019 11:23:58 -0700 (PDT)
Received: from scw-93ddc8.cloud.online.net ([2001:bc8:4400:2400::302d])
        by smtp.googlemail.com with ESMTPSA id
 t13sm4890wra.70.2019.09.26.11.23.57
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 26 Sep 2019 11:23:57 -0700 (PDT)
From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
To: stefanha@redhat.com
Cc: davem@davemloft.net, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, matiasevara@gmail.com,
        sgarzare@redhat.com
Subject: [PATCH] vsock/virtio: add support for MSG_PEEK
Date: Thu, 26 Sep 2019 18:23:34 +0000
Message-Id: <1569522214-28223-1-git-send-email-matiasevara@gmail.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds support for MSG_PEEK. In such a case, packets are not
removed from the rx_queue and credit updates are not sent.

Signed-off-by: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
---
 net/vmw_vsock/virtio_transport_common.c | 50 +++++++++++++++++++++++++++++++--
 1 file changed, 47 insertions(+), 3 deletions(-)

```
