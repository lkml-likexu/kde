#### [GIT PULL] KVM fixes for Linux 5.9-rc8
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11815143
Return-Path: <SRS0=VmrS=DK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8EB136CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 09:19:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71427206CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 09:19:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QplHiVXv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725783AbgJCJTA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 3 Oct 2020 05:19:00 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41326 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725730AbgJCJTA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 3 Oct 2020 05:19:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601716739;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Xaa+/b2Y/z1dPGM7nkR+iaYhP57s9DiHPFtFLQ2sRIw=;
        b=QplHiVXvKzfrDsflaVx0YZX7Um5q2X1OeODCCgq+KqXyltENdxVCq6pVTY7jNWpgwOY/rg
        k/SECEqz/mbrsnMSsCAkyulvFt76oyvLfWBBW5PnR65QfEtAvq7t2o4wAIhtpYEuRi5aJR
        znZg2XoH1erOIG7qdDSEbgdhefgytho=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-523-FMuPZXG4OWaNaYSX9yXZAQ-1; Sat, 03 Oct 2020 05:18:57 -0400
X-MC-Unique: FMuPZXG4OWaNaYSX9yXZAQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F0849100746F;
        Sat,  3 Oct 2020 09:18:55 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8D39A60C05;
        Sat,  3 Oct 2020 09:18:55 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for Linux 5.9-rc8
Date: Sat,  3 Oct 2020 05:18:54 -0400
Message-Id: <20201003091854.240100-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 4bb05f30483fd21ea5413eaf1182768f251cf625:

  KVM: SVM: Add a dedicated INVD intercept routine (2020-09-25 13:27:35 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e2e1a1c86bf32a8d7458b9024f518cf2434414c8:

  Merge tag 'kvmarm-fixes-5.9-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2020-10-03 05:07:59 -0400)

----------------------------------------------------------------
Two bugfix patches.

----------------------------------------------------------------
Marc Zyngier (1):
      KVM: arm64: Restore missing ISB on nVHE __tlb_switch_to_guest

Paolo Bonzini (2):
      KVM: VMX: update PFEC_MASK/PFEC_MATCH together with PF intercept
      Merge tag 'kvmarm-fixes-5.9-3' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

 arch/arm64/kvm/hyp/nvhe/tlb.c |  7 +++++++
 arch/x86/kvm/vmx/vmx.c        | 22 ++++++++++++----------
 2 files changed, 19 insertions(+), 10 deletions(-)
```
#### [PATCH] KVM: VMX: update PFEC_MASK/PFEC_MATCH together with PF intercept
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11815121
Return-Path: <SRS0=VmrS=DK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0341B6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 08:48:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB8C82067C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 08:48:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aIW8ak+e"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725804AbgJCIsw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 3 Oct 2020 04:48:52 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49747 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725601AbgJCIst (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 3 Oct 2020 04:48:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601714928;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JSzviH95g3Cg7Ab3hoyr0QKGSSvhU8NZpt80cGzHgMc=;
        b=aIW8ak+elp3jgELZccXdxqpPrqmykXS+Vl6LrG5r98R3cG1ziY4073OSzt6/Ic8MzQSmQG
        vcXCub2kGxdYznaTdAiyQ8nhH1NSgzv1PYaj+Gc/CBE2Hug/3wOqx+W1X6tJs1IJY1WUj2
        26MWW/zXEvZApYH99LFxONzaCQOR8KM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-543-_qK2yB6GOomSwg1G7JME1w-1; Sat, 03 Oct 2020 04:48:44 -0400
X-MC-Unique: _qK2yB6GOomSwg1G7JME1w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8686D80364D;
        Sat,  3 Oct 2020 08:48:43 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B02C760C05;
        Sat,  3 Oct 2020 08:48:36 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Qian Cai <cai@redhat.com>,
        Naresh Kamboju <naresh.kamboju@linaro.org>
Subject: [PATCH] KVM: VMX: update PFEC_MASK/PFEC_MATCH together with PF
 intercept
Date: Sat,  3 Oct 2020 04:48:35 -0400
Message-Id: <20201003084835.237833-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PFEC_MASK and PFEC_MATCH fields in the VMCS reverse the meaning of
the #PF intercept bit in the exception bitmap when they do not match.
This means that, if PFEC_MASK and/or PFEC_MATCH are set, the
hypervisor can get a vmexit for #PF exceptions even when the
corresponding bit is clear in the exception bitmap.

This is unexpected and is promptly detected by a WARN_ON_ONCE.
To fix it, reset PFEC_MASK and PFEC_MATCH when the #PF intercept
is disabled (as is common with enable_ept && !allow_smaller_maxphyaddr).

Reported-by: Qian Cai <cai@redhat.com>>
Reported-by: Naresh Kamboju <naresh.kamboju@linaro.org>
Tested-by: Naresh Kamboju <naresh.kamboju@linaro.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
#### [PATCH v3 1/3] vhost: Don't call access_ok() when using IOTLBFrom: Greg Kurz <groug@kaod.org>
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11815169
Return-Path: <SRS0=VmrS=DK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CCCD6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 10:02:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3021F206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  3 Oct 2020 10:02:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725842AbgJCKCC convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 3 Oct 2020 06:02:02 -0400
Received: from us-smtp-delivery-44.mimecast.com ([205.139.111.44]:24838 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725777AbgJCKCB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 3 Oct 2020 06:02:01 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-374-o1tP11ugOfO_vsKHpUl3HA-1; Sat, 03 Oct 2020 06:01:59 -0400
X-MC-Unique: o1tP11ugOfO_vsKHpUl3HA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BCE86802B75;
        Sat,  3 Oct 2020 10:01:57 +0000 (UTC)
Received: from bahia.lan (ovpn-112-192.ams2.redhat.com [10.36.112.192])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 148CB60C15;
        Sat,  3 Oct 2020 10:01:52 +0000 (UTC)
Subject: [PATCH v3 1/3] vhost: Don't call access_ok() when using IOTLB
From: Greg Kurz <groug@kaod.org>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        qemu-devel@nongnu.org, Laurent Vivier <laurent@vivier.eu>,
        David Gibson <david@gibson.dropbear.id.au>
Date: Sat, 03 Oct 2020 12:01:52 +0200
Message-ID: <160171931213.284610.2052489816407219136.stgit@bahia.lan>
In-Reply-To: <160171888144.284610.4628526949393013039.stgit@bahia.lan>
References: <160171888144.284610.4628526949393013039.stgit@bahia.lan>
User-Agent: StGit/0.21
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the IOTLB device is enabled, the vring addresses we get
from userspace are GIOVAs. It is thus wrong to pass them down
to access_ok() which only takes HVAs.

Access validation is done at prefetch time with IOTLB. Teach
vq_access_ok() about that by moving the (vq->iotlb) check
from vhost_vq_access_ok() to vq_access_ok(). This prevents
vhost_vring_set_addr() to fail when verifying the accesses.
No behavior change for vhost_vq_access_ok().

BugLink: https://bugzilla.redhat.com/show_bug.cgi?id=1883084
Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Cc: jasowang@redhat.com
CC: stable@vger.kernel.org # 4.14+
Signed-off-by: Greg Kurz <groug@kaod.org>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c |    9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
