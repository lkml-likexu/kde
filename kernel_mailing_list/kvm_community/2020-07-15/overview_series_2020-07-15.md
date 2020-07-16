#### [PATCH v5 01/18] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11666129
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09B8C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 19:46:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D95DD20657
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 19:46:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="aNMRHLA2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727106AbgGOTq3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 15:46:29 -0400
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:5318 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726864AbgGOTqZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 15:46:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1594842381; x=1626378381;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=GEI2urm980GaJ1XePmpk1eAHnLHBFeD7rFchtFKK6p8=;
  b=aNMRHLA2i0mGrIbXhz/2ZbpPVZtLsZzl0gSI08eyJRrKLbn9lG96q6qf
   6yVIqfL6SAWA/ixsfscZrf35tS2sTYm7b5OfbGO4wmGlUpL/nvJMrl2s8
   r4XhpRD1DaEG/+nsrPoyYGDW7UaLzXO9J3EwGqzWjEGBWEdkX6KYfP8BH
   Q=;
IronPort-SDR: 
 wZIrdnLWtDtUCvAM7uwiSjajSUPqBzvq2BL/tWkcy59ikKiH+5Para3rHFhzdmIBM9xQBdfPDl
 LR4iRcDxPf+A==
X-IronPort-AV: E=Sophos;i="5.75,356,1589241600";
   d="scan'208";a="43560239"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-2b-81e76b79.us-west-2.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-6001.iad6.amazon.com with ESMTP;
 15 Jul 2020 19:46:18 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2b-81e76b79.us-west-2.amazon.com (Postfix) with
 ESMTPS id 581CCA180C;
        Wed, 15 Jul 2020 19:46:17 +0000 (UTC)
Received: from EX13D16EUB001.ant.amazon.com (10.43.166.28) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 15 Jul 2020 19:46:16 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.214) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 15 Jul 2020 19:45:56 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Alexander Graf <graf@amazon.com>
Subject: [PATCH v5 01/18] nitro_enclaves: Add ioctl interface definition
Date: Wed, 15 Jul 2020 22:45:23 +0300
Message-ID: <20200715194540.45532-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200715194540.45532-1-andraprs@amazon.com>
References: <20200715194540.45532-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.214]
X-ClientProxiedBy: EX13D46UWB002.ant.amazon.com (10.43.161.70) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
Changelog

v4 -> v5

* Add more details about the ioctl calls usage e.g. error codes, file
  descriptors used.
* Update the ioctl to set an enclave vCPU to not return a file
  descriptor.
* Add specific NE error codes.

v3 -> v4

* Decouple NE ioctl interface from KVM API.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.

v2 -> v3

* Remove the GPL additional wording as SPDX-License-Identifier is
  already in place.

v1 -> v2

* Add ioctl for getting enclave image load metadata.
* Update NE_ENCLAVE_START ioctl name to NE_START_ENCLAVE.
* Add entry in Documentation/userspace-api/ioctl/ioctl-number.rst for NE
  ioctls.
* Update NE ioctls definition based on the updated ioctl range for major
  and minor.
---
 .../userspace-api/ioctl/ioctl-number.rst      |   5 +-
 include/linux/nitro_enclaves.h                |  11 +
 include/uapi/linux/nitro_enclaves.h           | 244 ++++++++++++++++++
 3 files changed, 259 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

```
#### [PATCH 1/7] KVM: nVMX: Reset the segment cache when stuffing guest segs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11664111
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 433C914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:06:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31F6C206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:06:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728740AbgGOEGf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 00:06:35 -0400
Received: from mga17.intel.com ([192.55.52.151]:16670 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725831AbgGOEGC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 00:06:02 -0400
IronPort-SDR: 
 xXg0snEgwNOooD3gl0He6k3kv+5MTJ5k+0ZRgeEFwiAaCOyj3H80BS2AabZ2toRv4Sp+J1wiDy
 0szdY/OWY4qA==
X-IronPort-AV: E=McAfee;i="6000,8403,9682"; a="129167479"
X-IronPort-AV: E=Sophos;i="5.75,353,1589266800";
   d="scan'208";a="129167479"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Jul 2020 21:06:01 -0700
IronPort-SDR: 
 srxr9mmabrRkjfdIblyup+KNXo+ebb9ZuNfJP5MUwZb2yIPc2yFT256FCsO2zP0guShTbjdZJ3
 ioCZC3tIv9kw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,353,1589266800";
   d="scan'208";a="485587005"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga006.fm.intel.com with ESMTP; 14 Jul 2020 21:06:01 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH 1/7] KVM: nVMX: Reset the segment cache when stuffing guest
 segs
Date: Tue, 14 Jul 2020 21:05:51 -0700
Message-Id: <20200715040557.5889-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200715040557.5889-1-sean.j.christopherson@intel.com>
References: <20200715040557.5889-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly reset the segment cache after stuffing guest segment regs in
prepare_vmcs02_rare().  Although the cache is reset when switching to
vmcs02, there is nothing that prevents KVM from re-populating the cache
prior to writing vmcs02 with vmcs12's values.  E.g. if the vCPU is
preempted after switching to vmcs02 but before prepare_vmcs02_rare(),
kvm_arch_vcpu_put() will dereference GUEST_SS_AR_BYTES via .get_cpl()
and cache the stale vmcs02 value.  While the current code base only
caches stale data in the preemption case, it's theoretically possible
future code could read a segment register during the nested flow itself,
i.e. this isn't technically illegal behavior in kvm_arch_vcpu_put(),
although it did introduce the bug.

This manifests as an unexpected nested VM-Enter failure when running
with unrestricted guest disabled if the above preemption case coincides
with L1 switching L2's CPL, e.g. when switching from a L2 vCPU at CPL3
to to a L2 vCPU at CPL0.  stack_segment_valid() will see the new SS_SEL
but the old SS_AR_BYTES and incorrectly mark the guest state as invalid
due to SS.dpl != SS.rpl.

Don't bother updating the cache even though prepare_vmcs02_rare() writes
every segment.  With unrestricted guest, guest segments are almost never
read, let alone L2 guest segments.  On the other hand, populating the
cache requires a large number of memory writes, i.e. it's unlikely to be
a net win.  Updating the cache would be a win when unrestricted guest is
not supported, as guest_state_valid() will immediately cache all segment
registers.  But, nested virtualization without unrestricted guest is
dirt slow, saving some VMREADs won't change that, and every CPU
manufactured in the last decade supports unrestricted guest.  In other
words, the extra (minor) complexity isn't worth the trouble.

Note, kvm_arch_vcpu_put() may see stale data when querying guest CPL
depending on when preemption occurs.  This is "ok" in that the usage is
imperfect by nature, i.e. it's used heuristically to improve performance
but doesn't affect functionality.  kvm_arch_vcpu_put() could be "fixed"
by also disabling preemption while loading segments, but that's
pointless and misleading as reading state from kvm_sched_{in,out}() is
guaranteed to see stale data in one form or another.  E.g. even if all
the usage of regs_avail is fixed to call kvm_register_mark_available()
after the associated state is set, the individual state might still be
stale with respect to the overall vCPU state.  I.e. making functional
decisions in an asynchronous hook is doomed from the get go.  Thankfully
KVM doesn't do that.

Fixes: de63ad4cf4973 ("KVM: X86: implement the logic for spinlock optimization")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH] cstart64: do not assume CR4 should be zero
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11666297
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F17F4618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 20:56:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E433F20672
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 20:56:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726675AbgGOU4u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 16:56:50 -0400
Received: from mga04.intel.com ([192.55.52.120]:52919 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725917AbgGOU4u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 16:56:50 -0400
IronPort-SDR: 
 2/opewqulrN6hrLpyBM+HseJn1OgLCOiz4LQPoh3djJryVLQGmECKxLtTf+r61RrNVEwQf1dWy
 IK2YCP7ypluw==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="146778076"
X-IronPort-AV: E=Sophos;i="5.75,356,1589266800";
   d="scan'208";a="146778076"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 13:56:49 -0700
IronPort-SDR: 
 UKSxa/PxHAyPwbXxRbMPl3eug2mS0ifarNlwyIbQdNUWTxx6/uYeqduX89MCzO/zWYi9bVWwA3
 UUMs7b7kbqbA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,356,1589266800";
   d="scan'208";a="308388400"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 15 Jul 2020 13:56:49 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <nadav.amit@gmail.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] cstart64: do not assume CR4 should be zero
Date: Wed, 15 Jul 2020 13:52:35 -0700
Message-Id: <20200715205235.13113-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly zero cr4 in prepare_64() instead of "zeroing" it in the
common enter_long_mode().  Clobbering cr4 in enter_long_mode() breaks
switch_to_5level(), which sets cr4.LA57 before calling enter_long_mode()
and obviously expects cr4 to be preserved.

Fixes: d86ef58 ("cstart: do not assume CR4 starts as zero")
Cc: Nadav Amit <namit@vmware.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Nadav Amit <namit@vmware.com>
---

Two lines of code, two bugs.  I'm pretty sure Paolo should win some kind
of award. :-D

 x86/cstart64.S | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH 1/8] KVM: x86/mmu: Commit zap of remaining invalid pages when recovering lpages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11664167
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20611913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:27:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 080EE20720
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 04:27:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726938AbgGOE1a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 00:27:30 -0400
Received: from mga05.intel.com ([192.55.52.43]:59539 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726023AbgGOE11 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 00:27:27 -0400
IronPort-SDR: 
 rdKDBCCr0sQNNk++uBrIur9cfBae2UiSmnL9e3xxeXejqYE9kRMbeTOVZ6GPCp6NcD6hTmDA+k
 bBvehhDYzs1g==
X-IronPort-AV: E=McAfee;i="6000,8403,9682"; a="233936294"
X-IronPort-AV: E=Sophos;i="5.75,354,1589266800";
   d="scan'208";a="233936294"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Jul 2020 21:27:26 -0700
IronPort-SDR: 
 DNE1cujfr2YcOX6Y8wIRz+c51jOPkd1aM06hjDa0GiaU/wlWW0/H97wHq1+QkQ3uAJ/ShSDN6z
 Dj5rKSlifSMA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,354,1589266800";
   d="scan'208";a="308118775"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 14 Jul 2020 21:27:26 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Junaid Shahid <junaids@google.com>
Subject: [PATCH 1/8] KVM: x86/mmu: Commit zap of remaining invalid pages when
 recovering lpages
Date: Tue, 14 Jul 2020 21:27:18 -0700
Message-Id: <20200715042725.10961-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200715042725.10961-1-sean.j.christopherson@intel.com>
References: <20200715042725.10961-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Call kvm_mmu_commit_zap_page() after exiting the "prepare zap" loop in
kvm_recover_nx_lpages() to finish zapping pages in the unlikely event
that the loop exited due to lpage_disallowed_mmu_pages being empty.
Because the recovery thread drops mmu_lock() when rescheduling, it's
possible that lpage_disallowed_mmu_pages could be emptied by a different
thread without to_zap reaching zero despite to_zap being derived from
the number of disallowed lpages.

Fixes: 1aa9b9572b105 ("kvm: x86: mmu: Recovery of shattered NX large pages")
Cc: Junaid Shahid <junaids@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v7 1/2] virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11664423
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D24CB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 08:31:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C116320672
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 08:31:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728422AbgGOIbY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 04:31:24 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4290 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726971AbgGOIbY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 15 Jul 2020 04:31:24 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06F82j8q084016;
        Wed, 15 Jul 2020 04:31:18 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 329cuk68j6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 04:31:17 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06F82nk0084470;
        Wed, 15 Jul 2020 04:31:17 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 329cuk68gx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 04:31:17 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06F8Q8Tu028457;
        Wed, 15 Jul 2020 08:31:15 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 327527j4b5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 15 Jul 2020 08:31:14 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06F8VCAS44892268
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jul 2020 08:31:12 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F22C252050;
        Wed, 15 Jul 2020 08:31:11 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.79.52])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 16E0252052;
        Wed, 15 Jul 2020 08:31:11 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v7 1/2] virtio: let arch validate VIRTIO features
Date: Wed, 15 Jul 2020 10:31:08 +0200
Message-Id: <1594801869-13365-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594801869-13365-1-git-send-email-pmorel@linux.ibm.com>
References: <1594801869-13365-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-15_05:2020-07-15,2020-07-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 bulkscore=0
 adultscore=0 spamscore=0 priorityscore=1501 phishscore=0 malwarescore=0
 suspectscore=1 mlxlogscore=999 mlxscore=0 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007150063
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may need to validate the VIRTIO devices features
based on architecture specifics.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 2 files changed, 20 insertions(+)

```
#### [PATCH] vfio/pci: fix racy on error and request eventfd ctx
##### From: Zeng Tao <prime.zeng@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zengtao (B)" <prime.zeng@hisilicon.com>
X-Patchwork-Id: 11664365
Return-Path: <SRS0=KTGQ=A2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D51A1510
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 07:35:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D81C2072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jul 2020 07:35:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729369AbgGOHfy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 03:35:54 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:33218 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729038AbgGOHfy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 03:35:54 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id D798D686B4C2E6A3B5EA;
        Wed, 15 Jul 2020 15:35:50 +0800 (CST)
Received: from localhost.localdomain (10.67.165.24) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Wed, 15 Jul 2020 15:35:45 +0800
From: Zeng Tao <prime.zeng@hisilicon.com>
To: <alex.williamson@redhat.com>, <cai@lca.pw>
CC: Zeng Tao <prime.zeng@hisilicon.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Peter Xu <peterx@redhat.com>,
        "Andrew Morton" <akpm@linux-foundation.org>,
        Michel Lespinasse <walken@google.com>,
        Denis Efremov <efremov@linux.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] vfio/pci: fix racy on error and request eventfd ctx
Date: Wed, 15 Jul 2020 15:34:41 +0800
Message-ID: <1594798484-20501-1-git-send-email-prime.zeng@hisilicon.com>
X-Mailer: git-send-email 2.8.1
MIME-Version: 1.0
X-Originating-IP: [10.67.165.24]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_pci_release call will free and clear the error and request
eventfd ctx while these ctx could be in use at the same time in the
function like vfio_pci_request, and it's expected to protect them under
the vdev->igate mutex, which is missing in vfio_pci_release.

This issue is introduced since commit 1518ac272e78 ("vfio/pci: fix memory
leaks of eventfd ctx"),and since commit 5c5866c593bb ("vfio/pci: Clear
error and request eventfd ctx after releasing"), it's very easily to
trigger the kernel panic like this:

[ 9513.904346] Unable to handle kernel NULL pointer dereference at virtual address 0000000000000008
[ 9513.913091] Mem abort info:
[ 9513.915871]   ESR = 0x96000006
[ 9513.918912]   EC = 0x25: DABT (current EL), IL = 32 bits
[ 9513.924198]   SET = 0, FnV = 0
[ 9513.927238]   EA = 0, S1PTW = 0
[ 9513.930364] Data abort info:
[ 9513.933231]   ISV = 0, ISS = 0x00000006
[ 9513.937048]   CM = 0, WnR = 0
[ 9513.940003] user pgtable: 4k pages, 48-bit VAs, pgdp=0000007ec7d12000
[ 9513.946414] [0000000000000008] pgd=0000007ec7d13003, p4d=0000007ec7d13003, pud=0000007ec728c003, pmd=0000000000000000
[ 9513.956975] Internal error: Oops: 96000006 [#1] PREEMPT SMP
[ 9513.962521] Modules linked in: vfio_pci vfio_virqfd vfio_iommu_type1 vfio hclge hns3 hnae3 [last unloaded: vfio_pci]
[ 9513.972998] CPU: 4 PID: 1327 Comm: bash Tainted: G        W         5.8.0-rc4+ #3
[ 9513.980443] Hardware name: Huawei TaiShan 2280 V2/BC82AMDC, BIOS 2280-V2 CS V3.B270.01 05/08/2020
[ 9513.989274] pstate: 80400089 (Nzcv daIf +PAN -UAO BTYPE=--)
[ 9513.994827] pc : _raw_spin_lock_irqsave+0x48/0x88
[ 9513.999515] lr : eventfd_signal+0x6c/0x1b0
[ 9514.003591] sp : ffff800038a0b960
[ 9514.006889] x29: ffff800038a0b960 x28: ffff007ef7f4da10
[ 9514.012175] x27: ffff207eefbbfc80 x26: ffffbb7903457000
[ 9514.017462] x25: ffffbb7912191000 x24: ffff007ef7f4d400
[ 9514.022747] x23: ffff20be6e0e4c00 x22: 0000000000000008
[ 9514.028033] x21: 0000000000000000 x20: 0000000000000000
[ 9514.033321] x19: 0000000000000008 x18: 0000000000000000
[ 9514.038606] x17: 0000000000000000 x16: ffffbb7910029328
[ 9514.043893] x15: 0000000000000000 x14: 0000000000000001
[ 9514.049179] x13: 0000000000000000 x12: 0000000000000002
[ 9514.054466] x11: 0000000000000000 x10: 0000000000000a00
[ 9514.059752] x9 : ffff800038a0b840 x8 : ffff007ef7f4de60
[ 9514.065038] x7 : ffff007fffc96690 x6 : fffffe01faffb748
[ 9514.070324] x5 : 0000000000000000 x4 : 0000000000000000
[ 9514.075609] x3 : 0000000000000000 x2 : 0000000000000001
[ 9514.080895] x1 : ffff007ef7f4d400 x0 : 0000000000000000
[ 9514.086181] Call trace:
[ 9514.088618]  _raw_spin_lock_irqsave+0x48/0x88
[ 9514.092954]  eventfd_signal+0x6c/0x1b0
[ 9514.096691]  vfio_pci_request+0x84/0xd0 [vfio_pci]
[ 9514.101464]  vfio_del_group_dev+0x150/0x290 [vfio]
[ 9514.106234]  vfio_pci_remove+0x30/0x128 [vfio_pci]
[ 9514.111007]  pci_device_remove+0x48/0x108
[ 9514.115001]  device_release_driver_internal+0x100/0x1b8
[ 9514.120200]  device_release_driver+0x28/0x38
[ 9514.124452]  pci_stop_bus_device+0x68/0xa8
[ 9514.128528]  pci_stop_and_remove_bus_device+0x20/0x38
[ 9514.133557]  pci_iov_remove_virtfn+0xb4/0x128
[ 9514.137893]  sriov_disable+0x3c/0x108
[ 9514.141538]  pci_disable_sriov+0x28/0x38
[ 9514.145445]  hns3_pci_sriov_configure+0x48/0xb8 [hns3]
[ 9514.150558]  sriov_numvfs_store+0x110/0x198
[ 9514.154724]  dev_attr_store+0x44/0x60
[ 9514.158373]  sysfs_kf_write+0x5c/0x78
[ 9514.162018]  kernfs_fop_write+0x104/0x210
[ 9514.166010]  __vfs_write+0x48/0x90
[ 9514.169395]  vfs_write+0xbc/0x1c0
[ 9514.172694]  ksys_write+0x74/0x100
[ 9514.176079]  __arm64_sys_write+0x24/0x30
[ 9514.179987]  el0_svc_common.constprop.4+0x110/0x200
[ 9514.184842]  do_el0_svc+0x34/0x98
[ 9514.188144]  el0_svc+0x14/0x40
[ 9514.191185]  el0_sync_handler+0xb0/0x2d0
[ 9514.195088]  el0_sync+0x140/0x180
[ 9514.198389] Code: b9001020 d2800000 52800022 f9800271 (885ffe61)
[ 9514.204455] ---[ end trace 648de00c8406465f ]---
[ 9514.212308] note: bash[1327] exited with preempt_count 1

Cc: Qian Cai <cai@lca.pw>
Cc: Alex Williamson <alex.williamson@redhat.com>
Fixes: 1518ac272e78 ("vfio/pci: fix memory leaks of eventfd ctx")
Signed-off-by: Zeng Tao <prime.zeng@hisilicon.com>
---
 drivers/vfio/pci/vfio_pci.c | 5 +++++
 1 file changed, 5 insertions(+)

```
