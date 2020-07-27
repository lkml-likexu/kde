#### [PATCH 1/2] mm: make mm->locked_vm an atomic64 counter
##### From: Pengfei Li <fly@kernel.page>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pengfei Li <fly@kernel.page>
X-Patchwork-Id: 11685567
Return-Path: <SRS0=wNFu=BF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0EFAC13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 08:03:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E89B820738
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 08:03:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgGZIDD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jul 2020 04:03:03 -0400
Received: from relay11.mail.gandi.net ([217.70.178.231]:53873 "EHLO
        relay11.mail.gandi.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725848AbgGZIDD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jul 2020 04:03:03 -0400
Received: from localhost.localdomain (unknown [180.110.142.179])
        (Authenticated sender: fly@kernel.page)
        by relay11.mail.gandi.net (Postfix) with ESMTPSA id 76B41100004;
        Sun, 26 Jul 2020 08:02:48 +0000 (UTC)
From: Pengfei Li <fly@kernel.page>
To: akpm@linux-foundation.org
Cc: bmt@zurich.ibm.com, dledford@redhat.com, willy@infradead.org,
        vbabka@suse.cz, kirill.shutemov@linux.intel.com, jgg@ziepe.ca,
        alex.williamson@redhat.com, cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        Pengfei Li <fly@kernel.page>
Subject: [PATCH 1/2] mm: make mm->locked_vm an atomic64 counter
Date: Sun, 26 Jul 2020 16:02:23 +0800
Message-Id: <20200726080224.205470-1-fly@kernel.page>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Like commit 70f8a3ca68d3 ("mm: make mm->pinned_vm an atomic64 counter").

By making mm->locked_vm an atomic64 counter, we can safely modify it
without holding mmap_lock.

The reason for using atomic64 instead of atomic_long is to keep the same
as mm->pinned_vm, and there is no need to worry about overflow.

Signed-off-by: Pengfei Li <fly@kernel.page>
---
 drivers/infiniband/sw/siw/siw_verbs.c | 12 +++++++-----
 drivers/vfio/vfio_iommu_type1.c       |  6 ++++--
 fs/io_uring.c                         |  4 ++--
 fs/proc/task_mmu.c                    |  2 +-
 include/linux/mm_types.h              |  4 ++--
 kernel/fork.c                         |  2 +-
 mm/debug.c                            |  5 +++--
 mm/mlock.c                            |  4 ++--
 mm/mmap.c                             | 18 +++++++++---------
 mm/mremap.c                           |  6 +++---
 mm/util.c                             |  6 +++---
 11 files changed, 37 insertions(+), 32 deletions(-)

```
#### [PATCH v13 01/10] KVM: x86: Move common set/get handler of MSR_IA32_DEBUGCTLMSR to VMX
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11685885
Return-Path: <SRS0=wNFu=BF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 144A113A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 15:34:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0554A2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 15:34:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726887AbgGZPeo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jul 2020 11:34:44 -0400
Received: from mga03.intel.com ([134.134.136.65]:17603 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726065AbgGZPen (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jul 2020 11:34:43 -0400
IronPort-SDR: 
 ECY5LGkiLdUzWsO8mRFUWRz/kk3XSoYFko3mo3QIDVoS9P/Vz2NVKR4I2EXsTiVNrPnLzAmfpv
 emf6YvGMJjTA==
X-IronPort-AV: E=McAfee;i="6000,8403,9694"; a="150890960"
X-IronPort-AV: E=Sophos;i="5.75,399,1589266800";
   d="scan'208";a="150890960"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jul 2020 08:34:42 -0700
IronPort-SDR: 
 xBe0in7NsNEsZ7F3QCwY1vi0YOcZ1oSNWfNDlYpizimvoN59TFVVIOuZUpK5u4Z31jSsaE4Co5
 0wyQkgLgjfog==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,399,1589266800";
   d="scan'208";a="303177505"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 26 Jul 2020 08:34:40 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v13 01/10] KVM: x86: Move common set/get handler of
 MSR_IA32_DEBUGCTLMSR to VMX
Date: Sun, 26 Jul 2020 23:32:19 +0800
Message-Id: <20200726153229.27149-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200726153229.27149-1-like.xu@linux.intel.com>
References: <20200726153229.27149-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SVM already has specific handlers of MSR_IA32_DEBUGCTLMSR in the
svm_get/set_msr, so the x86 common part can be safely moved to VMX.

Add vmx_supported_debugctl() to refactor the throwing logic of #GP.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/capabilities.h |  5 +++++
 arch/x86/kvm/vmx/vmx.c          | 11 ++++++++---
 arch/x86/kvm/x86.c              | 13 -------------
 3 files changed, 13 insertions(+), 16 deletions(-)

```
#### [PATCH] kvm: mmu.h: delete duplicated word
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11685323
Return-Path: <SRS0=wNFu=BF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6263C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 00:18:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E0322074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 00:18:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="DQRW84hr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728005AbgGZASM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 25 Jul 2020 20:18:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50384 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726870AbgGZASM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 25 Jul 2020 20:18:12 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 54B9FC08C5C0;
        Sat, 25 Jul 2020 17:18:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:Content-Type:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=WiGs1qgslmQVm39ErD8FtEC6YDu9ozQcsFkJHMOI2oc=;
 b=DQRW84hrFK4kXvxMNHnKyNutab
        EAeTNO5IF3HDyRU/gtwUTgEnXmyYBs0F7ulun+eqn+rvpgVFe3Zye309sQiZaizSvtMjayUrF4wPi
        E32Ppo8mVSMFKfQJ9k0IxSLCJOGckkuQVQepBP+I951ek6K1oCb8DhhrAieXxDdaZt/qCzLDpeRCc
        LwJP0K34aD3h98ZAX6Jpdo/oq2UDgxpSRAEq7DkSvzIEg3qwcE/sqMCVgE6yfPPAzkw+cugpla97h
        qixj+GSy3RCRNunoC5Y7+tM/bCI75nj/L/A0j7V6S4SlyozmTxu6c58wZoLW6ySeOdWWy8+53gu4X
        TJT+ANIA==;
Received: from [2601:1c0:6280:3f0::19c2] (helo=smtpauth.infradead.org)
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jzUMk-0002ON-1A; Sun, 26 Jul 2020 00:18:10 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH] kvm: mmu.h: delete duplicated word
Date: Sat, 25 Jul 2020 17:18:06 -0700
Message-Id: <20200726001806.19600-1-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete the repeated word "is".

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 arch/x86/kvm/mmu.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200720.orig/arch/x86/kvm/mmu.h
+++ linux-next-20200720/arch/x86/kvm/mmu.h
@@ -191,7 +191,7 @@ static inline u8 permission_fault(struct
 		* PKRU defines 32 bits, there are 16 domains and 2
 		* attribute bits per domain in pkru.  pte_pkey is the
 		* index of the protection domain, so pte_pkey * 2 is
-		* is the index of the first bit for the domain.
+		* the index of the first bit for the domain.
 		*/
 		pkru_bits = (vcpu->arch.pkru >> (pte_pkey * 2)) & 3;
 
```
#### [PATCH] kvm: paging_tmpl.h: delete duplicated word
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 11685325
Return-Path: <SRS0=wNFu=BF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3BBC313B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 00:18:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 236802070E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 00:18:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="M0ADK4gR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728044AbgGZAS0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 25 Jul 2020 20:18:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50422 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726870AbgGZASZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 25 Jul 2020 20:18:25 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C41CBC08C5C0;
        Sat, 25 Jul 2020 17:18:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:Content-Type:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=VitMP7uQjz9q5/byuL/XQS+Y0BC50vmbZT4y0BkkwD4=;
 b=M0ADK4gRX5A4r5OV5jZ2QW0GHV
        juSj+uUzbgNE8I7St5aQ9h9n2jIGNybUom8yKMjh4zEhpxOBndNTTFj//fRu3f/cd8+geXpF6nJmF
        qUqynhovxvl2a0YRfKJeHh6JgRhC2YiKurcqIfrKjKZgwOeSOV2ElXRp1mTxuPnZx97LDVGIyGxfo
        Z887Mr2x+7RS1LN73XP/BVxpfxhRIC0p+VMqLajQr31+1+cXgsf9t+ZpNwjVspU3FoKGfBpgcUw52
        jqUB4JFxgS/9LvlwwiZqcD4hUqBRFvFVndJuJDcPlspcx4ex1uwqanp7VwhE0bv/Nef7WtOi3txY/
        YTQOfhew==;
Received: from [2601:1c0:6280:3f0::19c2] (helo=smtpauth.infradead.org)
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1jzUMx-0002Oz-OZ; Sun, 26 Jul 2020 00:18:24 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH] kvm: paging_tmpl.h: delete duplicated word
Date: Sat, 25 Jul 2020 17:18:20 -0700
Message-Id: <20200726001820.19653-1-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete the repeated word "to".

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 arch/x86/kvm/mmu/paging_tmpl.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200720.orig/arch/x86/kvm/mmu/paging_tmpl.h
+++ linux-next-20200720/arch/x86/kvm/mmu/paging_tmpl.h
@@ -478,7 +478,7 @@ error:
 
 #if PTTYPE == PTTYPE_EPT
 	/*
-	 * Use PFERR_RSVD_MASK in error_code to to tell if EPT
+	 * Use PFERR_RSVD_MASK in error_code to tell if EPT
 	 * misconfiguration requires to be injected. The detection is
 	 * done by is_rsvd_bits_set() above.
 	 *
```
#### [PATCH] target/i386: add -cpu,lbr=true support to enable guest LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11685911
Return-Path: <SRS0=wNFu=BF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AEDD17CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 15:35:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EFDFD2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Jul 2020 15:35:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726970AbgGZPes (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Jul 2020 11:34:48 -0400
Received: from mga03.intel.com ([134.134.136.65]:17603 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726065AbgGZPer (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Jul 2020 11:34:47 -0400
IronPort-SDR: 
 DWLr7vKMGPiADKniRIlTx4ae3ArcjaeC4Av5QrBzjVFT3sRssmPWYGx7bQwaiBKvUXPJgZliJB
 MtVnV7G1FkXg==
X-IronPort-AV: E=McAfee;i="6000,8403,9694"; a="150890963"
X-IronPort-AV: E=Sophos;i="5.75,399,1589266800";
   d="scan'208";a="150890963"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jul 2020 08:34:46 -0700
IronPort-SDR: 
 vxspwqeHLJVp8zYHCu9lL8ndMhtakzWTni51jaPdnDq9vBZ7qBOMTekiYhPw7To0chsq4p4TbB
 W9SnT/+3N38g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,399,1589266800";
   d="scan'208";a="303177524"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 26 Jul 2020 08:34:43 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Subject: [PATCH] target/i386: add -cpu,lbr=true support to enable guest LBR
Date: Sun, 26 Jul 2020 23:32:20 +0800
Message-Id: <20200726153229.27149-3-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200726153229.27149-1-like.xu@linux.intel.com>
References: <20200726153229.27149-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The LBR feature would be enabled on the guest if:
- the KVM is enabled and the PMU is enabled and,
- the msr-based-feature IA32_PERF_CAPABILITIES is supporterd and,
- the supported returned value for lbr_fmt from this msr is not zero.

The LBR feature would be disabled on the guest if:
- the msr-based-feature IA32_PERF_CAPABILITIES is unsupporterd OR,
- qemu set the IA32_PERF_CAPABILITIES msr feature without lbr_fmt values OR,
- the requested guest vcpu model doesn't support PDCM.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: qemu-devel@nongnu.org
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 hw/i386/pc.c      |  1 +
 target/i386/cpu.c | 24 ++++++++++++++++++++++--
 target/i386/cpu.h |  2 ++
 target/i386/kvm.c |  7 ++++++-
 4 files changed, 31 insertions(+), 3 deletions(-)

```
