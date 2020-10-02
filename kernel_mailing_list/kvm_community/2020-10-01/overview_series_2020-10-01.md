#### [PATCH] Documentation: kvm: fix a typo
##### From: Li Qiang <liq3ea@163.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li Qiang <liq3ea@163.com>
X-Patchwork-Id: 11811255
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 16D6E112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 10:09:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8DC021707
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 10:09:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=163.com header.i=@163.com
 header.b="FrhotxVH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731839AbgJAKJa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 06:09:30 -0400
Received: from mail-m975.mail.163.com ([123.126.97.5]:58166 "EHLO
        mail-m975.mail.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725938AbgJAKJa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Oct 2020 06:09:30 -0400
X-Greylist: delayed 934 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 01 Oct 2020 06:09:29 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=163.com;
        s=s110527; h=From:Subject:Date:Message-Id:MIME-Version; bh=+4m/E
        60rd4MuVV6IHtmEXYYNuvcrK2YYQtFtbcmsOP4=; b=FrhotxVHrq4eURvN2ZD4q
        RCPQ/3jYiLQTL+dgyeO0KxUEPGPxSVQoCiHL11fFofSCEeMvsM3kBXAuJaXCmjDM
        h9Fri3aSaxO+VnT02/MqCOCNtMn+0qr0PoRWtGrAve+SZ9dZ6RHUJI3XnD2fVwYC
        zkR14cCw2syCJgz5ZClL+o=
Received: from ubuntu.localdomain (unknown [125.120.102.69])
        by smtp5 (Coremail) with SMTP id HdxpCgBnVQ8ep3Vf0ouQOw--.234S4;
        Thu, 01 Oct 2020 17:53:42 +0800 (CST)
From: Li Qiang <liq3ea@163.com>
To: pbonzini@redhat.com, corbet@lwn.net, lnowakow@eng.ucsd.edu,
        kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: liq3ea@gmail.com, Li Qiang <liq3ea@163.com>
Subject: [PATCH] Documentation: kvm: fix a typo
Date: Thu,  1 Oct 2020 02:53:33 -0700
Message-Id: <20201001095333.7611-1-liq3ea@163.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-CM-TRANSID: HdxpCgBnVQ8ep3Vf0ouQOw--.234S4
X-Coremail-Antispam: 1Uf129KBjvdXoW7Xw18Gw17Zr45Xw4rGFyDZFb_yoW3XrbE9r
        1DtFsYqr18tr1Sqw4UGFs5ZF13Xa1rCFyUCw1kArs5Aa4Ut395uFyDC3y2y345XFsxurZ8
        JFZxZrW5Jw129jkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUvcSsGvfC2KfnxnUUI43ZEXa7xRR75r3UUUUU==
X-Originating-IP: [125.120.102.69]
X-CM-SenderInfo: 5oltjvrd6rljoofrz/xtbBZgawbVaD6D9K2AAAst
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes: e287d6de62f74 ("Documentation: kvm: Convert cpuid.txt to .rst")
Signed-off-by: Li Qiang <liq3ea@163.com>
---
 Documentation/virt/kvm/cpuid.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### 
##### 

```c
```
#### [PATCH v7 1/4] KVM: x86: xen_hvm_config: cleanup return values
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11811329
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF8FE112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:30:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BF86721707
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:30:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LdMYSudr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731989AbgJALaU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 07:30:20 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:55744 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731983AbgJALaU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 07:30:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601551819;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=JIgAnG0/52jvsrYP8foGBjJHRYEGbPqwh/z1E5MmjGk=;
        b=LdMYSudrxnWrvSKk0ymiPJzg4P47kSeVFwYF7zIMQixY4hlMUKGt3lZacjqP+XolYWnlZp
        +pooBaeNynjE/2B363Lrhl9TGS1Stj8BZ0NfYbkjAeDaj0zMl5n4wWBH++YfAmXYbQZd7N
        yZLwPIsH8w5cvVIr3g7ikjUOey0n7+Y=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-595-yecq4e2ePqSmigsUkz0U4w-1; Thu, 01 Oct 2020 07:30:15 -0400
X-MC-Unique: yecq4e2ePqSmigsUkz0U4w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5EC231882FA0;
        Thu,  1 Oct 2020 11:30:13 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.29])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 67EF171775;
        Thu,  1 Oct 2020 11:30:09 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>, linux-kernel@vger.kernel.org,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v7 1/4] KVM: x86: xen_hvm_config: cleanup return values
Date: Thu,  1 Oct 2020 14:29:51 +0300
Message-Id: <20201001112954.6258-2-mlevitsk@redhat.com>
In-Reply-To: <20201001112954.6258-1-mlevitsk@redhat.com>
References: <20201001112954.6258-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Return 1 on errors that are caused by wrong guest behavior
(which will inject #GP to the guest)

And return a negative error value on issues that are
the kernel's fault (e.g -ENOMEM)

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 23 +++++++++--------------
 1 file changed, 9 insertions(+), 14 deletions(-)

```
#### [PATCH kvm-unit-tests] MAINTAINERS: Fix [An]drew's name
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11811343
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 088FD112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 12:02:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D492521481
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 12:02:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QSqhtui3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731936AbgJAMCa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 08:02:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:34749 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731670AbgJAMCa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 08:02:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601553749;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=il4T9+9ILkXtwEXPO9BKrKbTmlb2ckuffjzbILvxS14=;
        b=QSqhtui3C9B0i7USmjcaeOe/Oi2Ega4U9PaFXeQ5Z/+qIRzUsUXXEl8HF2mJGnRe0KD2Co
        fVuWuiL0dOMcn4GOTQstDXK+2Gd5ReEyuQDBXGcG0M6ERjWsOtXtA1XE3jKgIlgRCKSPwV
        RlofqW0Ql+fetPPwiF9/j0DIn1V4y2c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-131-__QUcEPJPo67Z-4xh9deBg-1; Thu, 01 Oct 2020 08:02:28 -0400
X-MC-Unique: __QUcEPJPo67Z-4xh9deBg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 09FBE1018F84
        for <kvm@vger.kernel.org>; Thu,  1 Oct 2020 12:02:27 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.100])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 216A255776;
        Thu,  1 Oct 2020 12:02:25 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] MAINTAINERS: Fix [An]drew's name
Date: Thu,  1 Oct 2020 14:02:24 +0200
Message-Id: <20201001120224.72090-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: x86: disconnect kvm_check_cpuid() from vcpu->arch.cpuid_entries
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11811431
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA69D174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 13:05:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE59F2068E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 13:05:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VyRbTIsP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732150AbgJANF4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 09:05:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35939 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732104AbgJANFz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 09:05:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601557553;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=X023FkD4CJHQd7Fpzt9OiSpx1o5f72B3yqJkQa1RT8k=;
        b=VyRbTIsPpPyV8zLWjdLsoRRFKQPUdMmJY285pFKjBJH6jv2wYtMx9Y95g9KvQMgFIcjHQO
        xmPyX9MWa/nXtrTca1uBgzI1sxNdK3abYpCqDzZM/nIP6cYGG0E+Twx5HBEQREMZzT7CH7
        yWwa2HZG7Ts1wWGcqAjd2HTWmD4lYf4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-473-pYKqZROSN3umcfMtjvlpLg-1; Thu, 01 Oct 2020 09:05:52 -0400
X-MC-Unique: pYKqZROSN3umcfMtjvlpLg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E673E1062724;
        Thu,  1 Oct 2020 13:05:50 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.161])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EFD705C1CF;
        Thu,  1 Oct 2020 13:05:45 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Wei Huang <whuang2@amd.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: x86: disconnect kvm_check_cpuid() from
 vcpu->arch.cpuid_entries
Date: Thu,  1 Oct 2020 15:05:39 +0200
Message-Id: <20201001130541.1398392-2-vkuznets@redhat.com>
In-Reply-To: <20201001130541.1398392-1-vkuznets@redhat.com>
References: <20201001130541.1398392-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a preparatory step to allocating vcpu->arch.cpuid_entries dynamically
make kvm_check_cpuid() check work with an arbitrary 'struct kvm_cpuid_entry2'
array.

Currently, when kvm_check_cpuid() fails we reset vcpu->arch.cpuid_nent to
0 and this is kind of weird, i.e. one would expect CPUIDs to remain
unchanged when KVM_SET_CPUID[2] call fails.

No functional change intended. It would've been possible to move the updated
kvm_check_cpuid() in kvm_vcpu_ioctl_set_cpuid2() and check the supplied
input before we start updating vcpu->arch.cpuid_entries/nent but we
can't do the same in kvm_vcpu_ioctl_set_cpuid() as we'll have to copy
'struct kvm_cpuid_entry' entries first. The change will be made when
vcpu->arch.cpuid_entries[] array becomes allocated dynamically.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/cpuid.c | 38 +++++++++++++++++++++++---------------
 1 file changed, 23 insertions(+), 15 deletions(-)

```
#### [RFC PATCH 01/22] x86/fpu/xstate: Modify area init helper prototypes to access all the possible areas
##### From: "Chang S. Bae" <chang.seok.bae@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Chang S. Bae" <chang.seok.bae@intel.com>
X-Patchwork-Id: 11812405
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61C3E6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 20:44:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B60B2085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 20:44:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733256AbgJAUoJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 16:44:09 -0400
Received: from mga11.intel.com ([192.55.52.93]:58726 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1733064AbgJAUnQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Oct 2020 16:43:16 -0400
IronPort-SDR: 
 fza0v1cjHYKP6SqAW60YTJKuwKoYpQuNhb/YIARKPxMNCjZvZ97rfWamEVkEjmbGwfHsVRVIJi
 nw37Acklo+2Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9761"; a="160170701"
X-IronPort-AV: E=Sophos;i="5.77,325,1596524400";
   d="scan'208";a="160170701"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Oct 2020 13:42:51 -0700
IronPort-SDR: 
 JT3cW7si4Isk6UuP3TJx5OsaCMJyGh1CNUi+kkrWKavd7ITA25Gy+gTjjqZWdjpg5JrNMIm9OC
 UKoMZJNULj8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,325,1596524400";
   d="scan'208";a="351297026"
Received: from chang-linux-3.sc.intel.com ([172.25.66.175])
  by FMSMGA003.fm.intel.com with ESMTP; 01 Oct 2020 13:42:51 -0700
From: "Chang S. Bae" <chang.seok.bae@intel.com>
To: tglx@linutronix.de, mingo@kernel.org, bp@suse.de, luto@kernel.org,
        x86@kernel.org
Cc: len.brown@intel.com, dave.hansen@intel.com, jing2.liu@intel.com,
        ravi.v.shankar@intel.com, linux-kernel@vger.kernel.org,
        chang.seok.bae@intel.com, kvm@vger.kernel.org
Subject: [RFC PATCH 01/22] x86/fpu/xstate: Modify area init helper prototypes
 to access all the possible areas
Date: Thu,  1 Oct 2020 13:38:52 -0700
Message-Id: <20201001203913.9125-2-chang.seok.bae@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201001203913.9125-1-chang.seok.bae@intel.com>
References: <20201001203913.9125-1-chang.seok.bae@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The xstate infrastructure is not flexible to support dynamic areas in
task->fpu. Change the fpstate_init() prototype to access task->fpu
directly. It treats a null pointer as indicating init_fpstate, as this
initial data does not belong to any task. For the compacted format,
fpstate_init_xstate() now accepts the state component bitmap to configure
XCOMP_BV.

No functional change.

Signed-off-by: Chang S. Bae <chang.seok.bae@intel.com>
Reviewed-by: Len Brown <len.brown@intel.com>
Cc: x86@kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org
---
 arch/x86/include/asm/fpu/internal.h |  6 +++---
 arch/x86/kernel/fpu/core.c          | 14 +++++++++++---
 arch/x86/kernel/fpu/init.c          |  2 +-
 arch/x86/kernel/fpu/regset.c        |  2 +-
 arch/x86/kernel/fpu/xstate.c        |  3 +--
 arch/x86/kvm/x86.c                  |  2 +-
 6 files changed, 18 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/7] travis.yml: Rework the x86 64-bit tests
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11811017
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7563592C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 07:22:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B20E21531
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 07:22:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IfOyB661"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731342AbgJAHWq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 03:22:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37377 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731330AbgJAHWo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Oct 2020 03:22:44 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601536962;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=3CD6D8u0IDtlVRO4Rki12jrlUun38FvaDxOMGSocPnA=;
        b=IfOyB6618ac/Qe29q1iWkTkFA/qawNs78n6ttAOrtusGhoU7zrhFdStHPQ5Ln62JiUG1RS
        sMhVRiL/JB1ctT2kJPZjrgKmx+MewdRCMX2Uf47zrbTD17/rFAhy7l8YMYLUCEp/dNDchY
        c0Pra7vlYMRnCcWxho4t8EGtqmDqnis=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-389-nN_utaYEMi64SBOmvLLDwQ-1; Thu, 01 Oct 2020 03:22:40 -0400
X-MC-Unique: nN_utaYEMi64SBOmvLLDwQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CCA6A873119
        for <kvm@vger.kernel.org>; Thu,  1 Oct 2020 07:22:39 +0000 (UTC)
Received: from thuth.com (ovpn-112-107.ams2.redhat.com [10.36.112.107])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8F57C60BF1;
        Thu,  1 Oct 2020 07:22:38 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, lvivier@redhat.com
Subject: [PATCH v2 1/7] travis.yml: Rework the x86 64-bit tests
Date: Thu,  1 Oct 2020 09:22:28 +0200
Message-Id: <20201001072234.143703-2-thuth@redhat.com>
In-Reply-To: <20201001072234.143703-1-thuth@redhat.com>
References: <20201001072234.143703-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently have three test jobs here:

1) gcc, in-tree build
2) gcc, out-of-tree build
3) clang, in-tree build

Keeping everything in perspective, it should be sufficient to only use two
build jobs for this, one in-tree with one compiler, and one out-of-tree
with the other compiler.
So let's re-order the jobs accordingly now. And while we're at it, make
sure that all additional tests that work with the newer QEMU from Ubuntu
Focal now are tested, too, and that we check all possible tests with
Clang.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 34 +++++++++++++++++-----------------
 1 file changed, 17 insertions(+), 17 deletions(-)

```
#### [PATCH v13 01/14] KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11810661
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC3C392C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 01:21:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 529582072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 01:21:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TKmUwDBP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729980AbgJABUy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Sep 2020 21:20:54 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:48739 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725372AbgJABUy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 30 Sep 2020 21:20:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601515253;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kX1VG8a6zkuD/3E46MJcm8aBltfxr0Y3fuQzYvb2RnM=;
        b=TKmUwDBPS2M3xeIMAxKsDbIESYX5qElwPSC8hD5J4DvNlUk58mX8CoNe2ibdA45TD8skag
        eOohQ+2aP9OPbyJDnWa581pLCXsZygscFl0HdFHdc6jtDc1WCWL4Q6wI2n4uzxul+/sK9i
        joHKcf9mBBns5PyN6lOEMrRJ/GBIauE=
Received: from mail-qk1-f198.google.com (mail-qk1-f198.google.com
 [209.85.222.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-zAUl30KKO96cVcPN1d584Q-1; Wed, 30 Sep 2020 21:20:51 -0400
X-MC-Unique: zAUl30KKO96cVcPN1d584Q-1
Received: by mail-qk1-f198.google.com with SMTP id m23so2096801qkh.10
        for <kvm@vger.kernel.org>; Wed, 30 Sep 2020 18:20:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=kX1VG8a6zkuD/3E46MJcm8aBltfxr0Y3fuQzYvb2RnM=;
        b=t7IuxQ9+UJMvEkQvKrNeHQamEmj/5158bqTCq3EM03/qjTvwdFP3W10MGgo4/T2bvp
         y7YSPFj4PKjZnpjmvkc2fYjwkOop5REFb1jgOd8K2AlST8wwnGogyMZZZ593raTsuoaY
         gLRseayoPKG/+mEwLnbbJSH+jUm8l+LVWXQew5ruhg5x76o227Q363vxnQdc34/3HI6L
         n7R5wwawz44/ThUDRZQnUEa2oNyZdMrwAKdUToUopWQXM6RwH22EV+pCkw7E8loH3A1D
         fqO8EVGYsEvoRvdbbTFejlX2zBAaRqZh9waK3ZBnTai6FxqBVWKqdhcNf8pUk8HloMD0
         Qk6w==
X-Gm-Message-State: AOAM531OR097aaHJ/hWL/9Wzxwbqgb6iguzfSqAkFLLAVHv4LgjGgW3x
        kgfPkNrpInqxpXTaNyhazYLfzDCXwSUvYnfrtExGrG5Rz48VP93Ud1kKRcTOoJNtSTw39CshwVi
        zEauntKMl9Rhn
X-Received: by 2002:aed:2767:: with SMTP id n94mr5503181qtd.237.1601515250589;
        Wed, 30 Sep 2020 18:20:50 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwexGjkpxAISmZJU5rHDeSyZUsxTAK15C0TBN2t67Ns3CGcsxJR+LE5yAdOAZa+v7XnrjZbYA==
X-Received: by 2002:aed:2767:: with SMTP id n94mr5503153qtd.237.1601515250368;
        Wed, 30 Sep 2020 18:20:50 -0700 (PDT)
Received: from localhost.localdomain
 (toroon474qw-lp130-09-184-147-14-204.dsl.bell.ca. [184.147.14.204])
        by smtp.gmail.com with ESMTPSA id
 y46sm4714478qtc.30.2020.09.30.18.20.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 30 Sep 2020 18:20:49 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v13 01/14] KVM: Documentation: Update entry for
 KVM_X86_SET_MSR_FILTER
Date: Wed, 30 Sep 2020 21:20:31 -0400
Message-Id: <20201001012044.5151-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201001012044.5151-1-peterx@redhat.com>
References: <20201001012044.5151-1-peterx@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It should be an accident when rebase, since we've already have section
8.25 (which is KVM_CAP_S390_DIAG318).  Fix the number.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: hide KVM options from menuconfig when KVM is not compiled
##### From: Matteo Croce <mcroce@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matteo Croce <mcroce@linux.microsoft.com>
X-Patchwork-Id: 11811311
Return-Path: <SRS0=iPdE=DI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0FC406CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:20:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED9012137B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  1 Oct 2020 11:20:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731816AbgJALU0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 1 Oct 2020 07:20:26 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:55235 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731134AbgJALU0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Oct 2020 07:20:26 -0400
Received: by mail-wm1-f68.google.com with SMTP id s13so2486034wmh.4;
        Thu, 01 Oct 2020 04:20:25 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=kZt2zy/Lwar12EpzsAU+4I+PUix2uePSQ1boZKXlZbM=;
        b=B+hp5AXvO+qvWEMhpHX10f+zMcOxZDHJvY+z8gF+vQLDc3H2wHIXZwC9jEDbZtvMtO
         WUyDG9eUlKGijywFeNxxJrs/iK0KyTSn3pF7KNjTxlHvBFafmA/zm6Qqyb/fClEmNtqe
         5HOtDO9mDFg3cPLt11QL5uFMNb/Si8H9pwrByx0WQ646hPJFsfetIwYd3ew8caGv1cCw
         IXAz5xMTKo4whPm4w0nM+Z+S7Y/m2aufogjGvwxiS6ef1S905/O7KUyg+6FE+Wh7YAwJ
         0n+uEw5s4v4c6g0IxilMpc5c1/MXCzJ64xUtpfq+u6Logkwbj2KF7qSZx88cC/JKg5lV
         rrrA==
X-Gm-Message-State: AOAM530V96R8dytvswaNBtmnMfvpbIG7vFrdLnHrAh6CmQuVxStZ3Qyz
        UbJqDmEWJP451oSMigD77xmCaks6Ppw=
X-Google-Smtp-Source: 
 ABdhPJxkB1EfFW+sdX3dph2xmIMIlse6uAZJ5j9V/jkkxdGL2OujglwQsUXsdaNBzRAi0Zsl1b3rfA==
X-Received: by 2002:a7b:c958:: with SMTP id i24mr8349585wml.50.1601551221189;
        Thu, 01 Oct 2020 04:20:21 -0700 (PDT)
Received: from msft-t490s.teknoraver.net
 (net-5-95-179-222.cust.vodafonedsl.it. [5.95.179.222])
        by smtp.gmail.com with ESMTPSA id
 r14sm8406689wrn.56.2020.10.01.04.20.20
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 01 Oct 2020 04:20:20 -0700 (PDT)
From: Matteo Croce <mcroce@linux.microsoft.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] x86/kvm: hide KVM options from menuconfig when KVM is not
 compiled
Date: Thu,  1 Oct 2020 13:20:14 +0200
Message-Id: <20201001112014.9561-1-mcroce@linux.microsoft.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matteo Croce <mcroce@microsoft.com>

Let KVM_WERROR depend on KVM, so it doesn't show in menuconfig alone.

Signed-off-by: Matteo Croce <mcroce@microsoft.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/Kconfig | 1 +
 1 file changed, 1 insertion(+)

```
