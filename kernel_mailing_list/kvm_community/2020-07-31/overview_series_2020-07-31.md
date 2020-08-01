#### [PATCH V5 1/6] vhost: introduce vhost_vring_call
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11694223
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FA1D722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:59:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 512EC2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:59:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731527AbgGaG7k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 02:59:40 -0400
Received: from mga09.intel.com ([134.134.136.24]:18704 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731515AbgGaG7j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 02:59:39 -0400
IronPort-SDR: 
 9RwZ8CBNLCli+v20FlPkSpSCx734LdLnYVZE+fi0g8P+R9LmVZ3ivnfqiGbGe/9q7v/64kS2yl
 QzO+BzaqY3iQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9698"; a="152949283"
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="152949283"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Jul 2020 23:59:39 -0700
IronPort-SDR: 
 Burx+Fr73C1no4aoCquRhHfstnFcTgeDCODWtT104MqAz7+iYtJ2y6LJsXiIDnlW9JVvQDow+M
 XjAAWuVVLQ/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,417,1589266800";
   d="scan'208";a="273136573"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga007.fm.intel.com with ESMTP; 30 Jul 2020 23:59:35 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V5 1/6] vhost: introduce vhost_vring_call
Date: Fri, 31 Jul 2020 14:55:28 +0800
Message-Id: <20200731065533.4144-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200731065533.4144-1-lingshan.zhu@intel.com>
References: <20200731065533.4144-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduces struct vhost_vring_call which replaced
raw struct eventfd_ctx *call_ctx in struct vhost_virtqueue.
Besides eventfd_ctx, it contains a spin lock and an
irq_bypass_producer in its structure.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Suggested-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c  |  4 ++--
 drivers/vhost/vhost.c | 22 ++++++++++++++++------
 drivers/vhost/vhost.h |  9 ++++++++-
 3 files changed, 26 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] scripts/runtime: Replace "|&" with "2>&1 |"
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11694131
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5A0113B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:09:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD00B2083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:09:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XjkTcV5y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731236AbgGaGJR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 02:09:17 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:28208 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731163AbgGaGJQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 31 Jul 2020 02:09:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596175755;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=xt0xwLPxB6x/Ia0P/cH9yWHtlLCZ5eOEcZLXWppsphM=;
        b=XjkTcV5ylu/BKodruIIpmnmFGGLm1BsKWV+Bb0oNKERyAkhL3QIPStNWgqC3q17GlxJQOY
        DJ9ekwk/QwFsSj7mJ09bXTn1GKSerKBDhkM+azbjgFwPRAD6aH9QJppeEsYVnPClHu5Hek
        EVG6iD+hdqloYpshvKq3P/UMgDHe3io=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-204-qjnOEAaxP06T1njFTjHKeA-1; Fri, 31 Jul 2020 02:09:13 -0400
X-MC-Unique: qjnOEAaxP06T1njFTjHKeA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A0ECE1DE0
        for <kvm@vger.kernel.org>; Fri, 31 Jul 2020 06:09:12 +0000 (UTC)
Received: from thuth.com (ovpn-112-153.ams2.redhat.com [10.36.112.153])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8FE99726BF;
        Fri, 31 Jul 2020 06:09:11 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com
Subject: [kvm-unit-tests PATCH] scripts/runtime: Replace "|&" with "2>&1 |"
Date: Fri, 31 Jul 2020 08:09:09 +0200
Message-Id: <20200731060909.1163-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "|&" only works with newer versions of the bash. For compatibility
with older versions, we should use "2>&1 |" instead.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### linux-next: manual merge of the kvm-arm tree with the kvm-fixes tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11694161
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52FB1722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:41:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3AC062173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 06:41:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="uS7CB3LW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731423AbgGaGlY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 31 Jul 2020 02:41:24 -0400
Received: from ozlabs.org ([203.11.71.1]:38869 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731369AbgGaGlX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 31 Jul 2020 02:41:23 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4BHyNZ6xtsz9sRN;
        Fri, 31 Jul 2020 16:41:17 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1596177680;
        bh=YiqLrRycvqLl4QUJsOXEjPkwKcEk/G+XXcaUYXrgJBE=;
        h=Date:From:To:Cc:Subject:From;
        b=uS7CB3LWcSRO5A3NOPyQbmC98LYlgrYkHkhyprR9Z1D+us23DsxZgnNBnz1JVB0kR
         JMEM/mX03jkm4uNQ8YNyr4b9LX8r57KAsxc99PDVOrRi84Ia5769oU6jyfFVNSwaUx
         nqwxdXUhgH8w1D7YKS/I3K04Q0ZiMXW49eos8bmPoSvTaubVc9tWKEjN3et1yGJ0tk
         cTwSpF2OCU2JNciaCFvy3hLaKdkcq5eRGN+b+tRRRZm9VINtLEENT6QkD2dml5+Bdd
         t1diSEqu3NX8ttdhwA/pvenENNBrlTwHtc7w5q9TefnMZtgLc2+0mx9L3mrLTkXYmx
         lVS+YUg9Qdw8A==
Date: Fri, 31 Jul 2020 16:41:17 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Christoffer Dall <cdall@cs.columbia.edu>,
        Marc Zyngier <maz@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: linux-next: manual merge of the kvm-arm tree with the kvm-fixes
 tree
Message-ID: <20200731164117.3ecb9791@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm-arm tree got a conflict in:

  arch/arm64/kvm/mmu.c

between commit:

  b757b47a2fcb ("KVM: arm64: Don't inherit exec permission across page-table levels")

from the kvm-fixes tree and commit:

  a0e50aa3f4a8 ("KVM: arm64: Factor out stage 2 page table data from struct kvm")

from the kvm-arm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [RFC PATCH 1/9] KVM:x86: Abstract sub functions from kvm_update_cpuid_runtime() and kvm_vcpu_after_set_cpuid()
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11693907
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A6BA46C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 02:42:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98D7821744
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 02:42:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731224AbgGaCmf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 22:42:35 -0400
Received: from mga12.intel.com ([192.55.52.136]:47518 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730820AbgGaCmf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 22:42:35 -0400
IronPort-SDR: 
 wbFsjgTSg0Io2CPp6ghQ5ZfggKDtOo4fycjdiP6oMOGAZL0txY5D6MVevSM9F0+skpxdYkBNrQ
 K/ytRzQgIKsg==
X-IronPort-AV: E=McAfee;i="6000,8403,9698"; a="131290113"
X-IronPort-AV: E=Sophos;i="5.75,416,1589266800";
   d="scan'208";a="131290113"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Jul 2020 19:42:34 -0700
IronPort-SDR: 
 gipBNjpKGibwZ96f9jHyvYi+u0BdmRvOkg8PISFMQIYTrJT2IGHSwCcBCaCFjMzE4WeAhdFUoy
 NYj/3sFegQdA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,416,1589266800";
   d="scan'208";a="304805950"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by orsmga002.jf.intel.com with ESMTP; 30 Jul 2020 19:42:32 -0700
From: Robert Hoo <robert.hu@linux.intel.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, xiaoyao.li@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org
Cc: robert.hu@intel.com, Robert Hoo <robert.hu@linux.intel.com>
Subject: [RFC PATCH 1/9] KVM:x86: Abstract sub functions from
 kvm_update_cpuid_runtime() and kvm_vcpu_after_set_cpuid()
Date: Fri, 31 Jul 2020 10:42:19 +0800
Message-Id: <1596163347-18574-2-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1596163347-18574-1-git-send-email-robert.hu@linux.intel.com>
References: <1596163347-18574-1-git-send-email-robert.hu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add below functions, whose aggregation equals kvm_update_cpuid_runtime() and
kvm_vcpu_after_set_cpuid().

void kvm_osxsave_update_cpuid(struct kvm_vcpu *vcpu, bool set)
void kvm_pke_update_cpuid(struct kvm_vcpu *vcpu, bool set)
void kvm_apic_base_update_cpuid(struct kvm_vcpu *vcpu, bool set)
void kvm_mwait_update_cpuid(struct kvm_vcpu *vcpu, bool set)
void kvm_xcr0_update_cpuid(struct kvm_vcpu *vcpu)
static void kvm_pv_unhalt_update_cpuid(struct kvm_vcpu *vcpu)
static void kvm_update_maxphyaddr(struct kvm_vcpu *vcpu)
static void kvm_update_lapic_timer_mode(struct kvm_vcpu *vcpu)

And, for some among the above, avoid double check set or clear inside function
body, but provided by caller.

Signed-off-by: Robert Hoo <robert.hu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 99 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/cpuid.h |  6 ++++
 2 files changed, 105 insertions(+)

```
#### [PATCH v3 1/3] KVM: LAPIC: Prevent setting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11693939
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60B4713B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 03:12:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48DE120829
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 03:12:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UOtVTTaO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731268AbgGaDMj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 23:12:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59786 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730820AbgGaDMi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 23:12:38 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EBC49C061574;
        Thu, 30 Jul 2020 20:12:37 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id c10so3273825pjn.1;
        Thu, 30 Jul 2020 20:12:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=CmJxc+XhZero9r+6q4uoOOTuXV90dMxdt2faOFzAcdY=;
        b=UOtVTTaOgPUCZucic0rjP7R/0UCYE1hGM2DtZQAZkSvbYgH4aiIUe1RSWRYIuyiPRr
         1bjNKVcYR6t8wIGGP/Yd/KsB1QZyAdmvYo0cxzRSMrXDs1YqOhOHbszlIls2r9wHBuqm
         93NrCV2rM6xN8UyPzE8Qyf0Bx6nQY1MNffIHzBovXdY2TQDIg4GI12h1d6+iML5KcjEc
         IR6NmTB0skdQ5226ijlQvdU+e6j1Q7U9hJT+3pFOMQ/r+xuWBOo82Ak0Pu/KE8JwXbuv
         VaBybxme7S/k31A/nOZGHtsu2TOdc4PE+fOcNNiEqpF2TVCZmNdXOZzB8GxX0I10/tN0
         HOyQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=CmJxc+XhZero9r+6q4uoOOTuXV90dMxdt2faOFzAcdY=;
        b=LZbVc3r/pC2rAT2cG/Y4aHtjMCjDvcz/+jIUraNlQ2HT4QFEoxQYfph8FLrnVir/lJ
         8n5SFPWj0o3I461k/U+S5GWc2y4D1VevynqJpbVyTG/JzPzInzhtTwUgN8DuE2fxOJvg
         D41Q5jnhxByC+qCVzZAJYFPJ1IzaeFoDAZQXJFQAbK+hHa/sl47poSNurskfgFsXC4hR
         jl0JEhagxs+wQSuh1qWMGoay2MZ5zXHpWXNqLbPT/E3M6iBi3Kr19kWmL/+QPgg6Ow8/
         1WSIVbBggEwbshKQcD0mGTomjTOtQV/WaZ+hsIhwgN97S/AiknuL+bGBia5TrBLs/ah4
         kjvg==
X-Gm-Message-State: AOAM532vhBTM9ZIaDzm6XOBoF52OZSuOBZ+pkn8NU3Tl3D86RCBHZ4WI
        owGiVrglF/kEKDN38WctJe7ef5wy
X-Google-Smtp-Source: 
 ABdhPJxh16+judrCc9+W6BGiAb8rYYh+q1qUJ3nANGdE5Ei1cEQokwGhGm9lfoBfIcMMCZ8hy4g3dQ==
X-Received: by 2002:a63:d446:: with SMTP id i6mr1696694pgj.438.1596165157234;
        Thu, 30 Jul 2020 20:12:37 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 t19sm8221961pfq.179.2020.07.30.20.12.34
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 30 Jul 2020 20:12:36 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, stable@vger.kernel.org
Subject: [PATCH v3 1/3] KVM: LAPIC: Prevent setting the tscdeadline timer if
 the lapic is hw disabled
Date: Fri, 31 Jul 2020 11:12:19 +0800
Message-Id: <1596165141-28874-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Prevent setting the tscdeadline timer if the lapic is hw disabled.

Fixes: bce87cce88 (KVM: x86: consolidate different ways to test for in-kernel LAPIC)
Cc: <stable@vger.kernel.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * add Fixes tag and cc stable

 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 2/3] KVM: LAPIC: Set the TDCR settable bits
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11693941
Return-Path: <SRS0=JHnX=BK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7DF5C1746
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 03:12:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6603920829
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 31 Jul 2020 03:12:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="FZ95jRAv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731289AbgGaDMn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jul 2020 23:12:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59792 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730820AbgGaDMk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jul 2020 23:12:40 -0400
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 65815C061574;
        Thu, 30 Jul 2020 20:12:40 -0700 (PDT)
Received: by mail-pj1-x1042.google.com with SMTP id e4so2781968pjd.0;
        Thu, 30 Jul 2020 20:12:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=n4jnMGbCRukfnq6mAWC7DIZwbVNmNRQBNC6Djiv/OMc=;
        b=FZ95jRAv43lUFjjKKZ5yU+PvIm34UyEsXv4FM5BpQp9BL7l/z5eVisL0lUqtQeqWl9
         GSFRF8lyuYD9evBme/Aho9gzt8cBU9EAJWJHErT0/o25GsuyTuYPzffbINcuV7FX4bdv
         vZGU1BtlWPk5cIqLSRsOE0bm1rDLAdtaxgrG04xMoQDSM+l+iFsxfTxuAK5oDvLclr0j
         6TygTREXdX5ZA1ckniL5mrjqcu+i8KovpttI2SjLbXf65PMCouuzzRQfymnqeLrwkLJo
         r025XcbOaBcSIX6ESx1wu3v9YidelyeQ+qrii+QS4qd0HwVsaBo5Lryv0L9hEr2VmqE1
         4LwA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=n4jnMGbCRukfnq6mAWC7DIZwbVNmNRQBNC6Djiv/OMc=;
        b=Vui8wFJO/GW0R+oAYB1s3eHeC5MNbHDORtb2YcnLfcpbE13qHu8MjUGp2GpOnhDcMm
         7KW/EEPFRMMSMGEU9KwE+XodYK5XQa9Str+Bk+hOKfivWKzw4FnnpjE16TIVax1fJD8N
         al0rgN8ZWpsCOB70u0vFr33KWukzu8NAZg6icYtNGwu6efa16w5OYiYEB8m2FkGfqxzZ
         6ejuhpHo1DU3U4RkWQfNMAfPn5TnRdIulrbjU7FhkD74yhC2YpU1cIuTO+SEUOaOfUqC
         mH7SNgzwIGKOEcYLNvehR2Seh5x7vYEUwfQ0nzqvGfH9bnglQqwlrAB+MQL24BmjwQbq
         YJhA==
X-Gm-Message-State: AOAM532ZjMqBQxPKRsZYJyT8PIfseQzWgJWD/VCpd9YZnYUlcGlGda0m
        n/oh7AwVrloDonmBzP/Z6KsocmFc
X-Google-Smtp-Source: 
 ABdhPJxBvOVyMFOZYiBnF5HqG3dQBBvFhUR/0+KGOEIZhFCN14A/LLvDtXKz8ET0a83yS9gXdcMclw==
X-Received: by 2002:a63:6fc7:: with SMTP id k190mr1782013pgc.54.1596165159782;
        Thu, 30 Jul 2020 20:12:39 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 t19sm8221961pfq.179.2020.07.30.20.12.37
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 30 Jul 2020 20:12:39 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v3 2/3] KVM: LAPIC: Set the TDCR settable bits
Date: Fri, 31 Jul 2020 11:12:20 +0800
Message-Id: <1596165141-28874-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1596165141-28874-1-git-send-email-wanpengli@tencent.com>
References: <1596165141-28874-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

It is a little different between Intel and AMD, Intel's bit 2
is 0 and AMD is reserved. On bare-metal, Intel will refuse to set
APIC_TDCR once bits except 0, 1, 3 are setting, however, AMD will
accept bits 0, 1, 3 and ignore other bits setting as patch does.
Before the patch, we can get back anything what we set to the
APIC_TDCR, this patch improves it.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * update patch description

 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
