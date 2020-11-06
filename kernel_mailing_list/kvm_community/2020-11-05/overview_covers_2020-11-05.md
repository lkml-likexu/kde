

#### [RFC v3 0/7] KVM: PKS Virtualization support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Thu Nov  5 08:17:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11883483
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 344B1C4742C
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:15:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAD1B2083B
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 08:15:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728272AbgKEIPn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 03:15:43 -0500
Received: from mga04.intel.com ([192.55.52.120]:39805 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726152AbgKEIPm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 03:15:42 -0500
IronPort-SDR: 
 4iOIAbZ6xTBUpHyalZNa5KJttoor0+pnRggT0rRNnWIU3xY1nrBdMPzwRunqKVZw0pBU5zU19x
 AUvSnWscIZrA==
X-IronPort-AV: E=McAfee;i="6000,8403,9795"; a="166755691"
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="166755691"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:15:42 -0800
IronPort-SDR: 
 RH6MQYXqur+6PiFBZCIf9sVhu/Zlbxqbh609693aK753L2EJlnc0537WrsK3GbmDiQv6OXo7mH
 EoJmuZrnvOLA==
X-IronPort-AV: E=Sophos;i="5.77,453,1596524400";
   d="scan'208";a="539281365"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 00:15:39 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v3 0/7] KVM: PKS Virtualization support
Date: Thu,  5 Nov 2020 16:17:57 +0800
Message-Id: <20201105081805.5674-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Protection Keys for Supervisor Pages(PKS) is a feature that extends the
Protection Keys architecture to support thread-specific permission
restrictions on supervisor pages.

PKS works similar to an existing feature named PKU(protecting user pages).
They both perform an additional check after all legacy access
permissions checks are done. If violated, #PF occurs and PFEC.PK bit will
be set. PKS introduces MSR IA32_PKRS to manage supervisor protection key
rights. The MSR contains 16 pairs of ADi and WDi bits. Each pair
advertises on a group of pages with the same key which is set in the
leaf paging-structure entries(bits[62:59]). Currently, IA32_PKRS is not
supported by XSAVES architecture.

This patchset aims to add the virtualization of PKS in KVM. It
implemented PKS CPUID enumeration, vmentry/vmexit configuration, MSR
exposure, nested supported etc. Currently, PKS is not yet supported for
shadow paging. 

Detailed information about PKS can be found in the latest Intel 64 and
IA-32 Architectures Software Developer's Manual.
---

Changelogs:

v2->v3:
- No function changes since last submit
- rebase on the latest PKS kernel support:
  https://lore.kernel.org/lkml/20201102205320.1458656-1-ira.weiny@intel.com/
- add MSR_IA32_PKRS to the vmx_possible_passthrough_msrs[]
- RFC v2: https://lore.kernel.org/lkml/20201014021157.18022-1-chenyi.qiang@intel.com/

v1->v2:
- rebase on the latest PKS kernel support:
  https://github.com/weiny2/linux-kernel/tree/pks-rfc-v3
- add a kvm-unit-tests for PKS
- add the check in kvm_init_msr_list for PKRS
- place the X86_CR4_PKS in mmu_role_bits in kvm_set_cr4
- add the support to expose VM_{ENTRY, EXIT}_LOAD_IA32_PKRS in nested
  VMX MSR
- RFC v1: https://lore.kernel.org/lkml/20200807084841.7112-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (7):
  KVM: VMX: Introduce PKS VMCS fields
  KVM: VMX: Expose IA32_PKRS MSR
  KVM: MMU: Rename the pkru to pkr
  KVM: MMU: Refactor pkr_mask to cache condition
  KVM: MMU: Add support for PKS emulation
  KVM: X86: Expose PKS to guest and userspace
  KVM: VMX: Enable PKS for nested VM

 arch/x86/include/asm/kvm_host.h | 13 ++---
 arch/x86/include/asm/pkeys.h    |  1 +
 arch/x86/include/asm/vmx.h      |  6 +++
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/mmu.h              | 36 +++++++------
 arch/x86/kvm/mmu/mmu.c          | 78 +++++++++++++++-------------
 arch/x86/kvm/vmx/capabilities.h |  6 +++
 arch/x86/kvm/vmx/nested.c       | 38 +++++++++++++-
 arch/x86/kvm/vmx/vmcs.h         |  1 +
 arch/x86/kvm/vmx/vmcs12.c       |  2 +
 arch/x86/kvm/vmx/vmcs12.h       |  6 ++-
 arch/x86/kvm/vmx/vmx.c          | 91 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h          |  3 +-
 arch/x86/kvm/x86.c              |  9 +++-
 arch/x86/kvm/x86.h              |  6 +++
 arch/x86/mm/pkeys.c             |  6 +++
 include/linux/pkeys.h           |  4 ++
 17 files changed, 240 insertions(+), 69 deletions(-)
```
#### [PATCH 0/2] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Nov  5 17:15:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11884735
Return-Path: <SRS0=FTeU=EL=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A9603C55178
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 17:15:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52FCE2083B
	for <kvm@archiver.kernel.org>; Thu,  5 Nov 2020 17:15:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hkbcnv5S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731677AbgKERPa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 12:15:30 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:32324 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731595AbgKERP3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Nov 2020 12:15:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604596528;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZN6f9cdzyB53mwjnLkaf9hNEOsf9avkMMDM3/cvRSUU=;
        b=hkbcnv5SW0MnvTTNhagLeLa3tgKiQpn9JK61FonK+NSM1PuJBhC/3ymYTlKzlsSYj38QJn
        Tib4zZ4KkQwNTo++tzydFFLP3EICqpwFweNMOGbtSxGmoY7+jaa/zNnAe1qSG9h/YYlWN3
        +YTEobRFbXDMto+96eX0rAvKp7pc6eM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-132-m_NFKJiWP4i4i-7CuEbFow-1; Thu, 05 Nov 2020 12:15:26 -0500
X-MC-Unique: m_NFKJiWP4i4i-7CuEbFow-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5ACA5101F7A0;
        Thu,  5 Nov 2020 17:15:25 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0BECA6CE4F;
        Thu,  5 Nov 2020 17:15:24 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: yadong.qi@intel.com
Subject: [PATCH 0/2] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
Date: Thu,  5 Nov 2020 12:15:22 -0500
Message-Id: <20201105171524.650693-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch is new, the second is a rebase of Yadong's patch

Paolo Bonzini (1):
  KVM: x86: fix apic_accept_events vs check_nested_events

Yadong Qi (1):
  KVM: x86: emulate wait-for-SIPI and SIPI-VMExit

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  2 ++
 arch/x86/kvm/lapic.c            | 30 ++++++++++++++++---
 arch/x86/kvm/vmx/nested.c       | 53 ++++++++++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c          |  2 +-
 5 files changed, 69 insertions(+), 19 deletions(-)
```
