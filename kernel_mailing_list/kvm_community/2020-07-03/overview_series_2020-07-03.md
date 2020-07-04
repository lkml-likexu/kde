#### [PATCH 1/2] Documentation: virt: kvm/api: drop doubled words
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11642881
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DB4A739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EA24E20BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="Ohk6zx8U"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726960AbgGCV3U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 17:29:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51098 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726885AbgGCV3T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 17:29:19 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 18A1BC08C5DD;
        Fri,  3 Jul 2020 14:29:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=LEnyADWq/NophE7qSmBDDcjekGbN+O2yg5twkO086Ws=;
 b=Ohk6zx8UKR9hjpJwDA+AHyUcse
        0veg3vAUlr1Lou7KeF2FRi9/P+fF07lrd3F5dC+03oh6eoMKw+DgxtHKKEv7zdu4jos2gkz0zFGuH
        arNR1YP13zwB67hzPHIMGPyzBplFSesAC0NZx+ld0CH/eebc5S/np4OUBheEWSJpw9k9UonFjAxul
        Rz6gdNzE9j0880c3uyKVusR+9/juD6K5m7g6YAPDkNqGWjaJT8fpLJVdxeTc2pnKJp/HBaUbyLIKW
        5IWFcbSxkopPbeJC+tIC94OA+Wc4ej4Hoi9OgDJGQRqryTlnWiO64a0+F8s48MExSoUtplv9yC4qz
        5DVaz5jg==;
Received: from [2601:1c0:6280:3f0::19c2] (helo=smtpauth.infradead.org)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jrTFE-0006KB-O3; Fri, 03 Jul 2020 21:29:17 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Jonathan Corbet <corbet@lwn.net>, linux-doc@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH 1/2] Documentation: virt: kvm/api: drop doubled words
Date: Fri,  3 Jul 2020 14:29:06 -0700
Message-Id: <20200703212906.30655-3-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200703212906.30655-1-rdunlap@infradead.org>
References: <20200703212906.30655-1-rdunlap@infradead.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop multiple doubled words.

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: linux-doc@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 Documentation/virt/kvm/api.rst |   16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

--- linux-next-20200701.orig/Documentation/virt/kvm/api.rst
+++ linux-next-20200701/Documentation/virt/kvm/api.rst
@@ -65,7 +65,7 @@ not be freed until both the parent (orig
 put their references to the VM's file descriptor.
 
 Because a VM's resources are not freed until the last reference to its
-file descriptor is released, creating additional references to a VM via
+file descriptor is released, creating additional references to a VM
 via fork(), dup(), etc... without careful consideration is strongly
 discouraged and may have unwanted side effects, e.g. memory allocated
 by and on behalf of the VM's process may not be freed/unaccounted when
@@ -536,7 +536,7 @@ X86:
 	========= ===================================
 	  0       on success,
 	 -EEXIST  if an interrupt is already enqueued
-	 -EINVAL  the the irq number is invalid
+	 -EINVAL  the irq number is invalid
 	 -ENXIO   if the PIC is in the kernel
 	 -EFAULT  if the pointer is invalid
 	========= ===================================
@@ -3167,7 +3167,7 @@ not mandatory.
 
 The information returned by this ioctl can be used to prepare an instance
 of struct kvm_vcpu_init for KVM_ARM_VCPU_INIT ioctl which will result in
-in VCPU matching underlying host.
+VCPU matching underlying host.
 
 
 4.84 KVM_GET_REG_LIST
@@ -5855,7 +5855,7 @@ features of the KVM implementation.
 :Architectures: ppc
 
 This capability, if KVM_CHECK_EXTENSION indicates that it is
-available, means that that the kernel has an implementation of the
+available, means that the kernel has an implementation of the
 H_RANDOM hypercall backed by a hardware random-number generator.
 If present, the kernel H_RANDOM handler can be enabled for guest use
 with the KVM_CAP_PPC_ENABLE_HCALL capability.
@@ -5866,7 +5866,7 @@ with the KVM_CAP_PPC_ENABLE_HCALL capabi
 :Architectures: x86
 
 This capability, if KVM_CHECK_EXTENSION indicates that it is
-available, means that that the kernel has an implementation of the
+available, means that the kernel has an implementation of the
 Hyper-V Synthetic interrupt controller(SynIC). Hyper-V SynIC is
 used to support Windows Hyper-V based guest paravirt drivers(VMBus).
 
@@ -5881,7 +5881,7 @@ by the CPU, as it's incompatible with Sy
 :Architectures: ppc
 
 This capability, if KVM_CHECK_EXTENSION indicates that it is
-available, means that that the kernel can support guests using the
+available, means that the kernel can support guests using the
 radix MMU defined in Power ISA V3.00 (as implemented in the POWER9
 processor).
 
@@ -5891,7 +5891,7 @@ processor).
 :Architectures: ppc
 
 This capability, if KVM_CHECK_EXTENSION indicates that it is
-available, means that that the kernel can support guests using the
+available, means that the kernel can support guests using the
 hashed page table MMU defined in Power ISA V3.00 (as implemented in
 the POWER9 processor), including in-memory segment tables.
 
@@ -5996,7 +5996,7 @@ run->kvm_valid_regs or run->kvm_dirty_re
 
 If KVM_CAP_ARM_USER_IRQ is supported, the KVM_CHECK_EXTENSION ioctl returns a
 number larger than 0 indicating the version of this capability is implemented
-and thereby which bits in in run->s.regs.device_irq_level can signal values.
+and thereby which bits in run->s.regs.device_irq_level can signal values.
 
 Currently the following bits are defined for the device_irq_level bitmap::
 

From patchwork Fri Jul  3 21:29:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11642883
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 487CF739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3077220EDD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 21:29:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="iY3E+R1Q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726920AbgGCV3U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 17:29:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51086 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726379AbgGCV3Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 17:29:16 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9071BC061794;
        Fri,  3 Jul 2020 14:29:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:
        Content-Type:Content-ID:Content-Description;
        bh=hLwDdOODJNIyfxleejAgGycdJj0RksgBnWOZNon5m/A=;
 b=iY3E+R1QzCRyBz9MN3RAaHLWtP
        STJD+uqYF18028figPjwKWX13RtCe6UXaNaBFqrWMsJV/wTFvJJwnr5GwKBoxHEpy91xYYaI1G/1y
        OxAtaSnorTynqPx/dBGKjUf4osJMP8hHpqyPqI7iSWhvRBvQNKlLUW4g16SHdBkTMWJhIwKglyWT8
        7hqMUX5lc0WsaKwEuzC+xHw1HpPjm0Du5581+OaO25hIFozRAZ2Ouc+LyT+SviloJlWyLDEpRu4N4
        4mX+8F7KZMqW6xGIGgNYgK1En/hJBIz6nvR9b+F/egycfZDx2M/9LF311olP/IhYe6O3tY4p17Y7n
        AVU5eiuw==;
Received: from [2601:1c0:6280:3f0::19c2] (helo=smtpauth.infradead.org)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jrTFC-0006KB-7A; Fri, 03 Jul 2020 21:29:14 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Jonathan Corbet <corbet@lwn.net>, linux-doc@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH 2/2] Documentation: virt: kvm/s390-pv: drop doubled words
Date: Fri,  3 Jul 2020 14:29:05 -0700
Message-Id: <20200703212906.30655-2-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200703212906.30655-1-rdunlap@infradead.org>
References: <20200703212906.30655-1-rdunlap@infradead.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop the doubled word "the".

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: linux-doc@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 Documentation/virt/kvm/s390-pv.rst |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200701.orig/Documentation/virt/kvm/s390-pv.rst
+++ linux-next-20200701/Documentation/virt/kvm/s390-pv.rst
@@ -78,7 +78,7 @@ Register Save Area.
 Only GR values needed to emulate an instruction will be copied into this
 save area and the real register numbers will be hidden.
 
-The Interception Parameters state description field still contains the
+The Interception Parameters state description field still contains
 the bytes of the instruction text, but with pre-set register values
 instead of the actual ones. I.e. each instruction always uses the same
 instruction text, in order not to leak guest instruction text.
```
#### [PATCH v3 01/21] KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640581
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E403159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:36:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90763217A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:36:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726237AbgGCCgJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:36:09 -0400
Received: from mga11.intel.com ([192.55.52.93]:52027 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725937AbgGCCgG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:36:06 -0400
IronPort-SDR: 
 27aH5HFC4owY8cC8318GdmaeU6NMdOEdgWzEcV4Px2LgQUzOuhT8j9pRuNjMqI853p5YxcLlhT
 N0KOuVNM6bcA==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="145213958"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="145213958"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:36:05 -0700
IronPort-SDR: 
 Tf2UVjZ6SYjYNjI28qCvFsw5DIp+J6Bn7pYy33T3q37kSEk3EvDJqiJpYD3iFpyJbSP45UgECj
 mwXx+VAt2qiw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="278295718"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga003.jf.intel.com with ESMTP; 02 Jul 2020 19:36:04 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v3 01/21] KVM: x86/mmu: Track the associated kmem_cache in the
 MMU caches
Date: Thu,  2 Jul 2020 19:35:25 -0700
Message-Id: <20200703023545.8771-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200703023545.8771-1-sean.j.christopherson@intel.com>
References: <20200703023545.8771-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track the kmem_cache used for non-page KVM MMU memory caches instead of
passing in the associated kmem_cache when filling the cache.  This will
allow consolidating code and other cleanups.

No functional change intended.

Reviewed-by: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu/mmu.c          | 24 +++++++++++-------------
 2 files changed, 12 insertions(+), 13 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: access: Add test for illegal toggling of CR4.LA57 in 64-bit mode
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640575
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6ADA739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:19:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B82B2206CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:19:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726119AbgGCCTE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:19:04 -0400
Received: from mga17.intel.com ([192.55.52.151]:38213 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726032AbgGCCTE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:19:04 -0400
IronPort-SDR: 
 LQBAsIk+obZKU+etHK71/pUeCIbwTwtL4Hndhx2r/0TJKzyDoXP3mVrhyZndv1Cpqaheage2Ie
 JRVVNnrAoenA==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="127160652"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="127160652"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:19:03 -0700
IronPort-SDR: 
 rwiD6hnAhVwsbGcB0bSNGT0DXLgXfOkYL3SwozKBFASykmpt2/EzZWjR+d2tRRQsBWGGFRYXZ0
 CG+D4k0pEbAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="387503145"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 02 Jul 2020 19:19:03 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] x86: access: Add test for illegal toggling of
 CR4.LA57 in 64-bit mode
Date: Thu,  2 Jul 2020 19:19:03 -0700
Message-Id: <20200703021903.5683-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a test to verify that KVM correctly injects a #GP if the guest
attempts to toggle CR4.LA57 while 64-bit mode is active.  Use two
versions of the toggling, one to toggle only LA57 and a second to toggle
PSE in addition to LA57.  KVM doesn't intercept LA57, i.e. toggling only
LA57 effectively tests the CPU, not KVM.  Use PSE as the whipping boy as
it will not trigger a #GP on its own, is universally available, is
ignored in 64-bit mode, and most importantly is trapped by KVM.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 lib/x86/processor.h |  1 +
 x86/access.c        | 12 ++++++++++++
 2 files changed, 13 insertions(+)

```
#### [PATCH 1/2] KVM: x86: Mark CR4.TSD as being possibly owned by the guest
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640785
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B128A13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 04:04:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0D4C20B80
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 04:04:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726139AbgGCEE1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 00:04:27 -0400
Received: from mga06.intel.com ([134.134.136.31]:9178 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725972AbgGCEEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 00:04:24 -0400
IronPort-SDR: 
 TNFo0jCvEt1leNVMv8xG1NfSgGflZlFEqlZz59bSwa6dPmPG/aFuFvXTcmuOAMtqda7VvsOYeL
 wYYnUR3ttzeg==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="208604066"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="208604066"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 21:04:23 -0700
IronPort-SDR: 
 +ws7XUAIPTao+0J8/4eqJV3WVnxdMymWnm06JW1o0fjTGFZkI8cv/HynvXEOtSNCvZc8oRzRRo
 pgtC7yOfuHaQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="387520211"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 02 Jul 2020 21:04:23 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: Mark CR4.TSD as being possibly owned by the
 guest
Date: Thu,  2 Jul 2020 21:04:21 -0700
Message-Id: <20200703040422.31536-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200703040422.31536-1-sean.j.christopherson@intel.com>
References: <20200703040422.31536-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mark CR4.TSD as being possibly owned by the guest as that is indeed the
case on VMX.  Without TSD being tagged as possibly owned by the guest, a
targeted read of CR4 to get TSD could observe a stale value.  This bug
is benign in the current code base as the sole consumer of TSD is the
emulator (for RDTSC) and the emulator always "reads" the entirety of CR4
when grabbing bits.

Add a build-time assertion in to ensure VMX doesn't hand over more CR4
bits without also updating x86.

Fixes: 52ce3c21aec3 ("x86,kvm,vmx: Don't trap writes to CR4.TSD")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/kvm_cache_regs.h | 2 +-
 arch/x86/kvm/vmx/vmx.c        | 2 ++
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Inject #GP if guest attempts to toggle CR4.LA57 in 64-bit mode
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640573
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49411739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:17:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3B1FE206CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:17:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726106AbgGCCRQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:17:16 -0400
Received: from mga04.intel.com ([192.55.52.120]:21810 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726030AbgGCCRQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:17:16 -0400
IronPort-SDR: 
 bUvTDnkPh/59zNiuLnmEnkow26H7nX1LTZUYTzDsI1ZlX2ugG/TTPXrKyjXlU6hMF9bhTa7glH
 hINkzVGKTQAw==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="144590189"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="144590189"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:17:15 -0700
IronPort-SDR: 
 +3WoxbufimQHFebrJ3blixPWYmnB7hwijeZvQzzByt5Xe4sj4dygcx1PGO9r2az0zSkToIEfLE
 DBAeTeHCm8bA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="356637992"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga001.jf.intel.com with ESMTP; 02 Jul 2020 19:17:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Sebastien Boeuf <sebastien.boeuf@intel.com>
Subject: [PATCH] KVM: x86: Inject #GP if guest attempts to toggle CR4.LA57 in
 64-bit mode
Date: Thu,  2 Jul 2020 19:17:14 -0700
Message-Id: <20200703021714.5549-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Inject a #GP on MOV CR4 if CR4.LA57 is toggled in 64-bit mode, which is
illegal per Intel's SDM:

  CR4.LA57
    57-bit linear addresses (bit 12 of CR4) ... blah blah blah ...
    This bit cannot be modified in IA-32e mode.

Note, the pseudocode for MOV CR doesn't call out the fault condition,
which is likely why the check was missed during initial development.
This is arguably an SDM bug and will hopefully be fixed in future
release of the SDM.

Fixes: fd8cb433734ee ("KVM: MMU: Expose the LA57 feature to VM.")
Cc: stable@vger.kernel.org
Reported-by: Sebastien Boeuf <sebastien.boeuf@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: x86/mmu: Add capability to zap only sptes for the affected memslot
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640719
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0B6D618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:50:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A323C208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:50:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726367AbgGCCut (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:50:49 -0400
Received: from mga11.intel.com ([192.55.52.93]:53669 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726122AbgGCCut (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:50:49 -0400
IronPort-SDR: 
 Aav8GaqXIaqNER9VWFwb2NFsiCOth6Hqo+2nA4nYOa3ANCbXNn24UvtUvdHXqczpAPfDiB2LUB
 3y2FEe3hyuCw==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="145215352"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="145215352"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:50:48 -0700
IronPort-SDR: 
 Ryb+uzj/cdSPq8TexoPl9iNgw04qYNPy19LxT5VOX6zyKwUJoYX0+4sZNWy2y3R5g991PZRcnk
 2RCWfuWfRHnQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="296082778"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga002.jf.intel.com with ESMTP; 02 Jul 2020 19:50:48 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Xiong Zhang <xiong.y.zhang@intel.com>,
        Wayne Boyer <wayne.boyer@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Jun Nakajima <jun.nakajima@intel.com>
Subject: [PATCH] KVM: x86/mmu: Add capability to zap only sptes for the
 affected memslot
Date: Thu,  2 Jul 2020 19:50:47 -0700
Message-Id: <20200703025047.13987-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a new capability, KVM_CAP_MEMSLOT_ZAP_CONTROL, to allow
userspace to control the memslot zapping behavior on a per-VM basis.
x86's default behavior is to zap all SPTEs, including the root shadow
page, across all memslots.  While effective, the nuke and pave approach
isn't exactly performant, especially for large VMs and/or VMs that
heavily utilize RO memslots for MMIO devices, e.g. option ROMs.

On a vanilla VM with 6gb of RAM, the targeted zap reduces the number of
EPT violations during boot by ~14% with THP enabled in the host, and by
~7% with THP disabled in the host.  On a much more custom VM with 32gb
and a significant amount of memslot zapping, this can reduce the number
of EPT violations by 50% during guest boot, and improve boot time by
as much as 25%.

Keep the current x86 memslot zapping behavior as the default, as there's
an unresolved bug that pops up when zapping only the affected memslot,
and the exact conditions that trigger the bug are not fully known.  See
https://patchwork.kernel.org/patch/10798453 for details.

Implement the capability as a set of flags so that other architectures
might be able to use the capability without having to conform to x86's
semantics.

Cc: Xiong Zhang <xiong.y.zhang@intel.com>
Cc: Wayne Boyer <wayne.boyer@intel.com>
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: Jun Nakajima <jun.nakajima@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 Documentation/virt/kvm/api.rst  | 21 +++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu/mmu.c          | 21 ++++++++++++++++++++-
 arch/x86/kvm/x86.c              | 10 ++++++++++
 include/uapi/linux/kvm.h        |  4 ++++
 5 files changed, 57 insertions(+), 1 deletion(-)

```
#### [PULL 07/41] accel/kvm: Convert to ram_block_discard_disable()
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11641431
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 57CC292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 09:04:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D49720870
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 09:04:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Yh6jaUIx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726367AbgGCJD7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 05:03:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:36231 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725764AbgGCJD5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 05:03:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593767036;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=+xCzX5pjcy148tNCg3zvK7ruz7b/+qmBTdtfJlorfws=;
        b=Yh6jaUIx8sjqTg/oCQD/4z1J1e/dWNv0nyXvFZXHJZnBwZ1frgRNfD7GyqsmO/tLHJE02X
        nm0jjXhOBeqcgO4yRbwz4yWaVHPE24I7n4vpYqOrtaqCbVU4ws44j+9T3y0TUrRxh7YxtS
        QvW2WUMVLPpRHu7HllrDqg/M62Vs0ms=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-483-1YlxY1XUPsa7HeHOdMzYJA-1; Fri, 03 Jul 2020 05:03:52 -0400
X-MC-Unique: 1YlxY1XUPsa7HeHOdMzYJA-1
Received: by mail-wm1-f70.google.com with SMTP id v24so34593347wmh.3
        for <kvm@vger.kernel.org>; Fri, 03 Jul 2020 02:03:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=+xCzX5pjcy148tNCg3zvK7ruz7b/+qmBTdtfJlorfws=;
        b=ZVqyvVVcumT82V1WYDIR3V8vr7gz2W4A1dXOfa1VXdbE4Y9IUiLHuYMGc8AeC3oZFL
         FSW0YHbnri8xCqWLYlf1pzqgDhhznNqhjNFoOOohaUieg7a3cj8yPN+ATy1A5hBDCAJN
         1s/cGNqSBz+lrcB7n6p02Hig+Rvlyq17whZdn4NHfd6624gcIIGEEk+3XZKWowr7goF6
         4aZ8qYrtX+6OqNHQp5Ja+6zVA1DO2J/YCJ8wu7OTLnxxQzmy3woskWautbou8VFNksFS
         s8PjcV1MgQMr0tKoJEMXsVvDi5cCDYBxQJM3tYEUAFx6z+Pq0uVYTqzgCKgODJ89vZ+A
         KIMQ==
X-Gm-Message-State: AOAM533XghS+TbqWB8elZH67dn+iLT5g9SSmxN98UUoYVCnSuKqKaBWn
        62hsqXFzdQ7SXWR1VoEOUvIHscEEcbjVdYtB86h/E5+suS35PVPDuKud+W7dc2SpqaEA/ttqh9I
        AumFBsP6dNyvd
X-Received: by 2002:a7b:c14a:: with SMTP id z10mr34465105wmi.19.1593767030945;
        Fri, 03 Jul 2020 02:03:50 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxH6CgeufSo9JwIW+9iWhgBDRu9Y5rZ/6J6Jir103NVXBTOiQlnZIXgjcjYMvIQK8/q4Sijiw==
X-Received: by 2002:a7b:c14a:: with SMTP id z10mr34465084wmi.19.1593767030736;
        Fri, 03 Jul 2020 02:03:50 -0700 (PDT)
Received: from redhat.com (bzq-79-182-31-92.red.bezeqint.net. [79.182.31.92])
        by smtp.gmail.com with ESMTPSA id
 r1sm13030791wrt.73.2020.07.03.02.03.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 03 Jul 2020 02:03:50 -0700 (PDT)
Date: Fri, 3 Jul 2020 05:03:48 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
        David Hildenbrand <david@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PULL 07/41] accel/kvm: Convert to ram_block_discard_disable()
Message-ID: <20200703090252.368694-8-mst@redhat.com>
References: <20200703090252.368694-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200703090252.368694-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Hildenbrand <david@redhat.com>

Discarding memory does not work as expected. At the time this is called,
we cannot have anyone active that relies on discards to work properly.

Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
Message-Id: <20200626072248.78761-5-david@redhat.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 accel/kvm/kvm-all.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/4] lib/vmalloc: fix pages count local variable to be size_t
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11641751
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AE2760D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 11:51:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AE38207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 11:51:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726111AbgGCLvS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 07:51:18 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50924 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726063AbgGCLvR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 3 Jul 2020 07:51:17 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 063BWxVo087192
        for <kvm@vger.kernel.org>; Fri, 3 Jul 2020 07:51:17 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 320ss4wtrn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 03 Jul 2020 07:51:16 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 063BXb9a088923
        for <kvm@vger.kernel.org>; Fri, 3 Jul 2020 07:51:16 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 320ss4wtr0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 03 Jul 2020 07:51:16 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 063BpE1a000713;
        Fri, 3 Jul 2020 11:51:14 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma01fra.de.ibm.com with ESMTP id 321vnvg75f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 03 Jul 2020 11:51:13 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 063BpBFr55378056
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 3 Jul 2020 11:51:11 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9EC2D11C052;
        Fri,  3 Jul 2020 11:51:11 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3C2D311C050;
        Fri,  3 Jul 2020 11:51:11 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.164])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  3 Jul 2020 11:51:11 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH v1 1/4] lib/vmalloc: fix pages count local
 variable to be size_t
Date: Fri,  3 Jul 2020 13:51:06 +0200
Message-Id: <20200703115109.39139-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200703115109.39139-1-imbrenda@linux.ibm.com>
References: <20200703115109.39139-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-03_06:2020-07-02,2020-07-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 cotscore=-2147483648 spamscore=0 clxscore=1015 phishscore=0 adultscore=0
 priorityscore=1501 bulkscore=0 mlxlogscore=999 suspectscore=0 mlxscore=0
 impostorscore=0 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2007030078
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since size is of type size_t, size >> PAGE_SHIFT might still be too big
for a normal unsigned int.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/vmalloc.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL 1/1] vfio-ccw: Fix a build error due to missing include of linux/slab.h
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11641591
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5DF360D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 09:53:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C07F620723
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 09:53:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="E6tGMu8k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726396AbgGCJxG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 05:53:06 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:24495 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726129AbgGCJxG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 3 Jul 2020 05:53:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593769985;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=hai0dcPIMkcr5P0By/QJCXM4A0YP3MuE4H3RrpcA9h8=;
        b=E6tGMu8kbhfiaD3CGg19hxR+uH8tmq2SsoDhl3B4NaD2iZ4zCMmX/9hDjbVkb3H9zrK2va
        OfqhPLO5XvSO0geKJGWA60JOuOxSqnP6/Xvs9QgFcZCdvWhkMzXiO19dKg/MKoYS9voVO+
        ZJGCGCXmZwMlm38NmRNbhuliF/25Ca4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-491-8xVo53iVNJeXuDPjeleBZg-1; Fri, 03 Jul 2020 05:53:02 -0400
X-MC-Unique: 8xVo53iVNJeXuDPjeleBZg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 955F2800407;
        Fri,  3 Jul 2020 09:53:00 +0000 (UTC)
Received: from localhost (ovpn-113-54.ams2.redhat.com [10.36.113.54])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 388425D9CA;
        Fri,  3 Jul 2020 09:53:00 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PULL 1/1] vfio-ccw: Fix a build error due to missing include of
 linux/slab.h
Date: Fri,  3 Jul 2020 11:52:53 +0200
Message-Id: <20200703095253.620719-2-cohuck@redhat.com>
In-Reply-To: <20200703095253.620719-1-cohuck@redhat.com>
References: <20200703095253.620719-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Include linux/slab.h to fix a build error due to kfree() being undefined.

Fixes: 3f02cb2fd9d2 ("vfio-ccw: Wire up the CRW irq and CRW region")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Message-Id: <20200703022628.6036-1-sean.j.christopherson@intel.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_chp.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v1] virtio-mem: fix cross-compilation due to VIRTIO_MEM_USABLE_EXTENT
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11641667
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1283113B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 10:40:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EEDDA206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 10:40:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FEVMU99t"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726157AbgGCKki (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Jul 2020 06:40:38 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20327 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725984AbgGCKki (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Jul 2020 06:40:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593772837;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=jvOKeE9W3K+z4bWbP0gU4au5S8Ovk4stRWZMqPe80kQ=;
        b=FEVMU99t7w0LybYuikr76DdW2GEyhlVusAJEq/KtgglbBRidG1DjmIGOHxgDtIka1tJbOH
        7KBHUnLErKBdi+067TD+avM2u/hgXkX1NWuiV/ce99lmTmnR+l8HYgakf9gNr1MMe8SCbK
        KEr7OBKpJ1o3MwA/wG/P5cacA2TWCFE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-210-PchIVjkqNdqJHzcoi9aB7Q-1; Fri, 03 Jul 2020 06:40:35 -0400
X-MC-Unique: PchIVjkqNdqJHzcoi9aB7Q-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8784B800C60;
        Fri,  3 Jul 2020 10:40:34 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-0.ams2.redhat.com [10.36.114.0])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E095B7AC72;
        Fri,  3 Jul 2020 10:40:27 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, David Hildenbrand <david@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Subject: [PATCH v1] virtio-mem: fix cross-compilation due to
 VIRTIO_MEM_USABLE_EXTENT
Date: Fri,  3 Jul 2020 12:40:27 +0200
Message-Id: <20200703104027.30441-1-david@redhat.com>
In-Reply-To: <20200626072248.78761-1-david@redhat.com>
References: <20200626072248.78761-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The usable extend depends on the target, not on the destination. This
fixes cross-compilation on other architectures than x86-64.

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 hw/virtio/virtio-mem.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio-ccw: Fix a build error due to missing include of linux/slab.h
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11640577
Return-Path: <SRS0=xch8=AO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28CC7618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:26:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1AF5320781
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Jul 2020 02:26:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726053AbgGCC0b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 22:26:31 -0400
Received: from mga11.intel.com ([192.55.52.93]:51259 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725937AbgGCC0a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 22:26:30 -0400
IronPort-SDR: 
 O7lf2elbCikiZsf1mE15oQGKyA8B7OQ6nLVtCnPPdFHe3HdR/6PJdJ9a7JRxWwAtGU7I8cljYM
 zOYZu63i5z6w==
X-IronPort-AV: E=McAfee;i="6000,8403,9670"; a="145212917"
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="145212917"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Jul 2020 19:26:29 -0700
IronPort-SDR: 
 0Ve5FLC4SNoprdrxVntJ9NtWXdCSqMWN4SXOc6Mn+7Lvs65qxvNtZmIUGXSB1lmJ3/+3AL02E4
 8UAJk0IGGPuA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,306,1589266800";
   d="scan'208";a="455734093"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga005.jf.intel.com with ESMTP; 02 Jul 2020 19:26:29 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Eric Farman <farman@linux.ibm.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Peter Oberparleiter <oberpar@linux.ibm.com>
Cc: Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] vfio-ccw: Fix a build error due to missing include of
 linux/slab.h
Date: Thu,  2 Jul 2020 19:26:28 -0700
Message-Id: <20200703022628.6036-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Include linux/slab.h to fix a build error due to kfree() being undefined.

Fixes: 3f02cb2fd9d2d ("vfio-ccw: Wire up the CRW irq and CRW region")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Encountered this when cross-compiling with a pretty minimal config, didn't
bother digging into why the error only showed up in my environment.

 drivers/s390/cio/vfio_ccw_chp.c | 1 +
 1 file changed, 1 insertion(+)

```
