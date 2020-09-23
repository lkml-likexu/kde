#### [GIT PULL] Please pull my kvm-ppc-next-5.10-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11791481
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 365A4112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 04:19:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C51DA23A34
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 04:19:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="ds7Nn889"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726577AbgIVETh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 00:19:37 -0400
Received: from ozlabs.org ([203.11.71.1]:45417 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726098AbgIVETh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Sep 2020 00:19:37 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 4BwSkb5Dctz9sSC; Tue, 22 Sep 2020 14:19:35 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1600748375; bh=+TyuYYKH3sD47ZT12HOtuNmbIGXXMCkLfW/Ab3VHP3o=;
        h=Date:From:To:Cc:Subject:From;
        b=ds7Nn889CarZevU1lze3hhItrff7UpvSc+e2Mg6s+f7E+6qguTliRTIP5Nmp34zEF
         ehW5vwl5XZyZuz/UrY6g0xkiF6nlDjtFbYqNKwKTsai1NFDOcqUvhi63LJVIqiI6hb
         ZW/kzIPrNUbFIAwwRuBDLBcYG1oUo6KDRqQI+wmF79VSSDTaFDQArM/t8AD7ZpPAxn
         EHd9YNdlXIlMewwMvHlqLWJEL/DV03Kb4MKIDU3TuK8wf2rXK5qim7A75mTocky+Xu
         6/uneDBqqmox7xhf1AomJSbHHuHRyLu3dRrHjHab23UWNFteCmlUe6QptDlJoglQ7l
         DoVPGJBHBaOTg==
Date: Tue, 22 Sep 2020 14:19:30 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.10-1 tag
Message-ID: <20200922041930.GA531519@thinks.paulus.ozlabs.org>
MIME-Version: 1.0
Content-Disposition: inline
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-next-5.10-1 tag to get a PPC KVM
update for 5.10.  This is a small update with just some bug fixes and
no new features.

Thanks,
Paul.

The following changes since commit d012a7190fc1fd72ed48911e77ca97ba4521bccd:

  Linux 5.9-rc2 (2020-08-23 14:08:43 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.10-1

for you to fetch changes up to cf59eb13e151ef42c37ae31864046c17e481ed8f:

  KVM: PPC: Book3S: Fix symbol undeclared warnings (2020-09-22 11:53:55 +1000)

----------------------------------------------------------------
PPC KVM update for 5.10

- Fix for running nested guests with in-kernel IRQ chip
- Fix race condition causing occasional host hard lockup
- Minor cleanups and bugfixes

----------------------------------------------------------------
Fabiano Rosas (1):
      KVM: PPC: Book3S HV: Do not allocate HPT for a nested guest

Greg Kurz (2):
      KVM: PPC: Book3S HV: XICS: Replace the 'destroy' method by a 'release' method
      KVM: PPC: Don't return -ENOTSUPP to userspace in ioctls

Jing Xiangfeng (1):
      KVM: PPC: Book3S: Remove redundant initialization of variable ret

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Set LPCR[HDICE] before writing HDEC

Qinglang Miao (1):
      KVM: PPC: Book3S HV: XIVE: Convert to DEFINE_SHOW_ATTRIBUTE

Wang Wensheng (1):
      KVM: PPC: Book3S: Fix symbol undeclared warnings

 arch/powerpc/include/asm/kvm_host.h     |  1 +
 arch/powerpc/kvm/book3s.c               |  8 +--
 arch/powerpc/kvm/book3s_64_mmu_radix.c  |  2 +-
 arch/powerpc/kvm/book3s_64_vio.c        |  4 +-
 arch/powerpc/kvm/book3s_64_vio_hv.c     |  2 +-
 arch/powerpc/kvm/book3s_hv.c            | 22 +++++++--
 arch/powerpc/kvm/book3s_hv_interrupts.S |  9 ++--
 arch/powerpc/kvm/book3s_hv_nested.c     |  2 +-
 arch/powerpc/kvm/book3s_hv_rm_xics.c    |  2 +-
 arch/powerpc/kvm/book3s_pr.c            |  2 +-
 arch/powerpc/kvm/book3s_xics.c          | 86 ++++++++++++++++++++++++++-------
 arch/powerpc/kvm/book3s_xive_native.c   | 12 +----
 arch/powerpc/kvm/booke.c                |  6 +--
 13 files changed, 110 insertions(+), 48 deletions(-)
```
#### [PATCH] i386: Don't try to set MSR_KVM_ASYNC_PF_EN if kernel-irqchip=off
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11792729
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68CD0139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 15:15:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C2572399A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 15:15:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cn3i91cv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726673AbgIVPPM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 11:15:12 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:47610 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726650AbgIVPPL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 11:15:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600787710;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=hQSjgqVtilkBiWKNUMIsXVhf0Cxsgw+4bjov72hIPUQ=;
        b=cn3i91cvD4pHiQYZRpYq9dHVrMmz3Z3mv12lbYXFuUNacoZ3WKDwzmI6lFiIksavrdqnm4
        HgYKpAwsabibphLvKMC0Clb9LBUeaE84EPzHbpjZb+riEvG+XQmH/JbSyHneW5vOxET1Ac
        shd7hUU/tFmGG5TEnakcYvwdXwKqjoM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-236-TNCohAoeOT66zjxvPe1GZQ-1; Tue, 22 Sep 2020 11:15:01 -0400
X-MC-Unique: TNCohAoeOT66zjxvPe1GZQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 249311017DC9;
        Tue, 22 Sep 2020 15:15:00 +0000 (UTC)
Received: from localhost (unknown [10.10.67.5])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 930A673670;
        Tue, 22 Sep 2020 15:14:56 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        1896263@bugs.launchpad.net, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>
Subject: [PATCH] i386: Don't try to set MSR_KVM_ASYNC_PF_EN if
 kernel-irqchip=off
Date: Tue, 22 Sep 2020 11:14:55 -0400
Message-Id: <20200922151455.1763896-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This addresses the following crash when running Linux v5.8
with kernel-irqchip=off:

  qemu-system-x86_64: error: failed to set MSR 0x4b564d02 to 0x0
  qemu-system-x86_64: ../target/i386/kvm.c:2714: kvm_buf_set_msrs: Assertion `ret == cpu->kvm_msr_buf->nmsrs' failed.

There is a kernel-side fix for the issue too (kernel commit
d831de177217 "KVM: x86: always allow writing '0' to
MSR_KVM_ASYNC_PF_EN"), but it's nice to simply not trigger
the bug if running an older kernel.

Fixes: https://bugs.launchpad.net/bugs/1896263
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/kvm.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] i386/kvm: Require KVM_CAP_IRQ_ROUTING
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11793035
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4F48C59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:19:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23CEE23787
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:19:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KK3CueDH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726743AbgIVUTl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 16:19:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:42382 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726448AbgIVUTl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 16:19:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600805980;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gYUw7on53U22xygxI96tyg7A07dVivNHpOasjcBU6xE=;
        b=KK3CueDHnDmi1ASk9v5HnzGDDQRORg2sXQktK+g+b7nB8/2S9CgVIj7C12j/CCO9FCYhrq
        vTvzWHAMRMepVflcWhYILB7C4ggaG38QS/1N1qqXoiFxVA16jENmhjm1HMVsdgeRutUDEK
        qnyuPIifKKvmvGriUpGDCA8VyU/OpLk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-490-qWR7WA25Mr63xgyCP0dkpg-1; Tue, 22 Sep 2020 16:19:38 -0400
X-MC-Unique: qWR7WA25Mr63xgyCP0dkpg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0283C8B124D;
        Tue, 22 Sep 2020 20:19:37 +0000 (UTC)
Received: from localhost (unknown [10.10.67.5])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E406F5DD99;
        Tue, 22 Sep 2020 20:19:30 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sergio Lopez <slp@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <rth@twiddle.net>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 1/3] i386/kvm: Require KVM_CAP_IRQ_ROUTING
Date: Tue, 22 Sep 2020 16:19:20 -0400
Message-Id: <20200922201922.2153598-2-ehabkost@redhat.com>
In-Reply-To: <20200922201922.2153598-1-ehabkost@redhat.com>
References: <20200922201922.2153598-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_CAP_IRQ_ROUTING is available since 2009 (Linux v2.6.30), so
it's safe to just make it a requirement on x86.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/kvm.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v5 4/5] vfio/type1: Use iommu_aux_at(de)tach_group() APIs
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11791607
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BD9F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 06:27:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78C8C23A5C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 06:27:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729067AbgIVG05 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 02:26:57 -0400
Received: from mga12.intel.com ([192.55.52.136]:45992 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728136AbgIVG05 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Sep 2020 02:26:57 -0400
IronPort-SDR: 
 9jLNz8htZR2NY0oRVBIkcdeg99bP4u4HGcFb0COjA6t11BeQtAfQHONZ1hY/f2kQcttveiFpe0
 zRqela92PWjQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9751"; a="140023323"
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="140023323"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Sep 2020 23:17:07 -0700
IronPort-SDR: 
 7daS5tNwrWWqpl3taPoJ6/0qgFYro8nsiX7I+NgbHENCuINJfavq8dK3F4n2FXE0i0OMqRTjE+
 mTe4v5vFj90Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="334877460"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga004.fm.intel.com with ESMTP; 21 Sep 2020 23:17:03 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v5 4/5] vfio/type1: Use iommu_aux_at(de)tach_group() APIs
Date: Tue, 22 Sep 2020 14:10:41 +0800
Message-Id: <20200922061042.31633-5-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200922061042.31633-1-baolu.lu@linux.intel.com>
References: <20200922061042.31633-1-baolu.lu@linux.intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace iommu_aux_at(de)tach_device() with iommu_at(de)tach_subdev_group().

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 43 +++++----------------------------
 1 file changed, 6 insertions(+), 37 deletions(-)

```
#### [PATCH] kvm: Correct documentation of kvm_irqchip_*()
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eduardo Habkost <ehabkost@redhat.com>
X-Patchwork-Id: 11793063
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B184B1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:36:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8780A2376F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 20:36:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EdgZOUof"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726589AbgIVUgV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 16:36:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29068 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726179AbgIVUgV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 16:36:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600806979;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/uq1ydAD3WSjGkI4P2e9ZsRKctZ5UuVc07zSVeRW7bI=;
        b=EdgZOUofMcIb4zblp0tXorwxw6qZNEzAbqbzgx2vVEAZCL+BX4A5HD3Xveb4DGnpp08GON
        9wzQds/XZS3JhaSJwuRb8o8VAzQ6EHmf/x263xi9l2zztb7f8/4egkULUKykOgHlmm4Z91
        Vpz55HtahnpeMdvmzuJbkh2tnadJOU4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-337-stfvHO0ZOfqDt8Ev0brejQ-1; Tue, 22 Sep 2020 16:36:17 -0400
X-MC-Unique: stfvHO0ZOfqDt8Ev0brejQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7645C64086;
        Tue, 22 Sep 2020 20:36:16 +0000 (UTC)
Received: from localhost (unknown [10.10.67.5])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B35767367E;
        Tue, 22 Sep 2020 20:36:12 +0000 (UTC)
From: Eduardo Habkost <ehabkost@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, "Michael S. Tsirkin" <mst@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] kvm: Correct documentation of kvm_irqchip_*()
Date: Tue, 22 Sep 2020 16:36:12 -0400
Message-Id: <20200922203612.2178370-1-ehabkost@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When split irqchip support was introduced, the meaning of
kvm_irqchip_in_kernel() changed: now it only means the LAPIC is
in kernel.  The PIC, IOAPIC, and PIT might be in userspace if
irqchip=split was set.  Update the doc comment to reflect that.

While at it, remove the "the user asked us" part in
kvm_irqchip_is_split() doc comment.  That macro has nothing to do
with existence of explicit user-provided options.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 include/sysemu/kvm.h | 19 +++++++++----------
 1 file changed, 9 insertions(+), 10 deletions(-)

```
#### [PATCH v6 1/4] KVM: x86: xen_hvm_config: cleanup return values
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11793175
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B64659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 21:10:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 59D3E2371F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 21:10:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="h34blopn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726640AbgIVVKo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 17:10:44 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:44028 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726608AbgIVVKm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Sep 2020 17:10:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600809041;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=J4J8G6o2dkeXApdrpwNMYr32HCaxlIvTLSvlampSyz8=;
        b=h34blopni2cehWC+v0W6weyLjby3exOgrwj0h8v2jtVb3y6SA/doA3ec23YVVmmvteYSfT
        IfrLA3Rkq0VPVEEhMGnOBGcSN7nxePWpvU5J00dJAZvcClruq2StFhK5JHgKZoezvuEy9P
        62We4orISdqtm9kQtZHl+xlpRl4/AyQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-67-9sgPgTtBPaKfihsZ6OypDQ-1; Tue, 22 Sep 2020 17:10:37 -0400
X-MC-Unique: 9sgPgTtBPaKfihsZ6OypDQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F711106F71C;
        Tue, 22 Sep 2020 21:10:35 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.154])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A38E5577A;
        Tue, 22 Sep 2020 21:10:31 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v6 1/4] KVM: x86: xen_hvm_config: cleanup return values
Date: Wed, 23 Sep 2020 00:10:22 +0300
Message-Id: <20200922211025.175547-2-mlevitsk@redhat.com>
In-Reply-To: <20200922211025.175547-1-mlevitsk@redhat.com>
References: <20200922211025.175547-1-mlevitsk@redhat.com>
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
#### [RFC Patch 1/2] KVM: SVM: Create SEV cgroup controller.From: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11791315
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E738459D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 00:40:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BF18C23A1D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 00:40:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MrQrOaXm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729304AbgIVAkx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Sep 2020 20:40:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51142 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728911AbgIVAkw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Sep 2020 20:40:52 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D41C1C061755
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 17:40:52 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id s4so9313700pgk.17
        for <kvm@vger.kernel.org>; Mon, 21 Sep 2020 17:40:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=2bo/8biDCLvdc5lUd4pxIfX0ji8Irow1K8yrWLCkSEw=;
        b=MrQrOaXmVBsPDdbFCxn5Av9ptBV/TAKp8vJHFuZkt+J2XJOvvM1Q/F49uQwrOLVFUi
         sLCAcw5JyVAaGZjxOsWxrK3PlhT5jN2cDvEu5o95VeQwrDfIpssgqIaKLZtd8GZ7jSS3
         KPTx52/Dua+RFSpzYLsgoT7OWbg0l4mNy4CtSjLYHf9XGj6MwOsmBCApfvJmw5zFHrL4
         X/uNMJgHpKD5pCrZTPcU/haY7AOcZ5LQhVUjwZHWaomnOO92955x+tcfrbjt0/sJbLYR
         i/GL7zCrPtEp2IqZk9+NHjwztTJE64FrO1nUuBi6+N5FO7FrUPII+uVo8qr9Vm+/fxPd
         mDoA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=2bo/8biDCLvdc5lUd4pxIfX0ji8Irow1K8yrWLCkSEw=;
        b=Srrq0wCpLDtD+8/3sUyCNefyU6nUucnRph/1kdzWcti5/Fd0QZG+IGinLaQW3btnlB
         3Jbg3ulVt4XTKltGMx9ovgb/U+AMXHgpF+Oa2CbZYiM33F0twc1ZUiJFwPYuiQ82reJb
         fqJubl6E/7lWvbovCcUWPd1YEJtVUNYX7f3X1kCOQma+MgRwDMEcy/33bVdPL7RLCWal
         SS3ckmsZOfJnNapt5aCyCSa0BwUR8h9tIs+j8e7smtHxIYY9XXGZPrSgDz/JW74E/soi
         mTNhg15v9MEZt01B0LoVsLmRqDvr9WfupFL/HtFjAgejHXIwJDUr8qVJWDF/j72b8vtu
         S4HQ==
X-Gm-Message-State: AOAM532G5TjvHom2BttBkHupKz8/j87NQh8X7Z4vXA17pywUFNdB1qf1
        QY+YSR+bPN67KbTZ9dz50vaQJ9T9swfx
X-Google-Smtp-Source: 
 ABdhPJwwEskzYpOBo5WnGw2LW4mDawGLCStzqESTwLGyzmoPZTF8h2MYozyOU2GmWIl/kNqyXTmQkdGrp2P7
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a17:90b:1649:: with SMTP id
 il9mr1580586pjb.94.1600735252261; Mon, 21 Sep 2020 17:40:52 -0700 (PDT)
Date: Mon, 21 Sep 2020 17:40:23 -0700
In-Reply-To: <20200922004024.3699923-1-vipinsh@google.com>
Message-Id: <20200922004024.3699923-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20200922004024.3699923-1-vipinsh@google.com>
X-Mailer: git-send-email 2.28.0.681.g6f77f65b4e-goog
Subject: [RFC Patch 1/2] KVM: SVM: Create SEV cgroup controller.
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, tj@kernel.org, lizefan@huawei.com
Cc: joro@8bytes.org, corbet@lwn.net, brijesh.singh@amd.com,
        jon.grimm@amd.com, eric.vantassell@amd.com, gingell@google.com,
        rientjes@google.com, kvm@vger.kernel.org, x86@kernel.org,
        cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>,
        Dionna Glaze <dionnaglaze@google.com>,
        Erdem Aktas <erdemaktas@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Create SEV cgroup controller for SEV ASIDs on the AMD platform.

SEV ASIDs are used to encrypt virtual machines memory and isolate the
guests from the hypervisor. However, number of SEV ASIDs are limited on
a platform. This leads to the resource constraints and cause issues
like:

1. Some applications exhausting all of the SEV ASIDs and depriving
   others on a host.
2. No capability with the system admin to allocate and limit the number
   of SEV ASIDs used by tasks.
3. Difficult for the cloud service providers to optimally schedule VMs
   and sandboxes across its fleet without knowing the overall picture of
   SEV ASIDs usage.

SEV controller tracks the usage and provides capability to limit SEV
ASIDs used by tasks.

Controller is enabled by CGROUP_SEV config option, it is dependent on
KVM_AMD_SEV option in the config file.

SEV Controller has 3 interface files:

1. max - Sets the max limit of the SEV ASIDs in the cgroup.

2. current - Shows the current count of the SEV ASIDs in the cgroup.

3. events - Event file to show the SEV ASIDs allocation denied in the
	    cgroup.

When kvm-amd module is installed it calls SEV controller API and informs
how many SEV ASIDs are available on the platform. Controller use this
value to allocate an array which stores ASID to cgroup mapping.

New SEV ASID allocation gets charged to the task's SEV cgroup. Migration
of charge is not supported, so, a charged ASID remains charged to the
same cgroup until that SEV ASID is freed. This feature is similar to the
memory cgroup as it is a stateful resource

On deletion of an empty cgroup whose tasks have moved to some other
cgroup but a SEV ASID is still charged to it, the SEV ASID gets mapped
to the parent cgroup.

Mapping array tells which cgroup to uncharge, and update mapping when
the cgroup is deleted. Mapping array is freed when kvm-amd module is
unloaded.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
Reviewed-by: Dionna Glaze <dionnaglaze@google.com>
Reviewed-by: Erdem Aktas <erdemaktas@google.com>
---
 arch/x86/kvm/Makefile         |   1 +
 arch/x86/kvm/svm/sev.c        |  16 +-
 arch/x86/kvm/svm/sev_cgroup.c | 414 ++++++++++++++++++++++++++++++++++
 arch/x86/kvm/svm/sev_cgroup.h |  40 ++++
 include/linux/cgroup_subsys.h |   3 +
 init/Kconfig                  |  14 ++
 6 files changed, 487 insertions(+), 1 deletion(-)
 create mode 100644 arch/x86/kvm/svm/sev_cgroup.c
 create mode 100644 arch/x86/kvm/svm/sev_cgroup.h

```
#### [PATCH] KVM: SVM: Initialize ir_list and ir_list_lock regardless of AVIC enablement
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11791867
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1358116BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 08:41:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D3EAF23A5F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 08:41:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="p1Onw3yb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726430AbgIVIlh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 04:41:37 -0400
Received: from mail-dm6nam12on2053.outbound.protection.outlook.com
 ([40.107.243.53]:30817
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726341AbgIVIlh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Sep 2020 04:41:37 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ao77Psl9qOXnJSTRP31KKiBGln2SlqqdOPX2Y8PCYW3TSLGjFOQiX/RUjC4vMSqViCqvKEesJ9TcGvrhyw0xh/Jd2E+y/WCQxQ+e/4HJeALaRIrd7JZ4rWE9PDLp1fuPkmJkDn6xwUwXsTlPvie8AN5OhaS88nIe5Mr8wpPHTAEas3F8WqOYBMxXSn0pkqDoLfnrn/RD2CsDE8B5RgqMpwAEGLbov9T8ZisQodI+7jPggMTKXuuFh2iVNwStABotP/un05xAIT400pFyxNurkCsnCJewk+AbxwEEsw/Vgy9KdYaPYRle4mUQcOgYQubsPcFLrVEx1fGxS0mC5XvsZg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=49tKbKNAIe9+3qh3tvwC+6ucQ5TyssfwUhb9fEpUlf0=;
 b=WGh9qFVYvMg9fmtQklZi47GVvAMy7xnYOai/JE4jFngSx9PAWD8QIpaJ/izXBMIEXONQGDsqY3BAhzzf/M0ct3TD5QQmewOyk/cFBGghJPN9cZZUl/wH7fMtRPmy+GWMHA3eoMzhJEgUDQkLjh8Y8ERD6ZElDjM99Ln50gMRJQVIduqjfgk+zEZWhMj7TAWcmh17N/a30JaO3+Sfgabb0d+vSPUJscjngZ/zgBjwjNKWNDHSHzxsXGsia3YvS9tOo7j/GxNdaTeXHmVA1FLjjY/sovzV166KnRuSUMfddBjJ/gc7YWFQrUv1Odp+kkoZHvCp/q8sP042d+hbA0o3BA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=49tKbKNAIe9+3qh3tvwC+6ucQ5TyssfwUhb9fEpUlf0=;
 b=p1Onw3yboKdL0cKxgs5vwRt3uZX+49PD9BooIeFXn2xWEN5LFFyPGJQhJnfTzgn4/QR3xEAcaKrcdbthFPrKjZoGunp21ly90xSY+rIUpSVl84HQzq2TcL0OoQ7Xc/HXdkDrU62aBOrC2NafI1RS3scXQ7OX1bk99/t5FrA72dk=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM6PR12MB4337.namprd12.prod.outlook.com (2603:10b6:5:2a9::12) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.20; Tue, 22 Sep 2020 08:41:35 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::48cf:d69:d457:1b1e]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::48cf:d69:d457:1b1e%5]) with mapi id 15.20.3391.026; Tue, 22 Sep 2020
 08:41:34 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH] KVM: SVM: Initialize ir_list and ir_list_lock regardless of
 AVIC enablement
Date: Tue, 22 Sep 2020 08:44:46 +0000
Message-Id: <20200922084446.7218-1-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: SA9PR10CA0028.namprd10.prod.outlook.com
 (2603:10b6:806:a7::33) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ethanolx5673host.amd.com (165.204.78.2) by
 SA9PR10CA0028.namprd10.prod.outlook.com (2603:10b6:806:a7::33) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3391.11 via Frontend
 Transport; Tue, 22 Sep 2020 08:41:34 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 17382fb0-992c-43af-6fa8-08d85ed34fea
X-MS-TrafficTypeDiagnostic: DM6PR12MB4337:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB433753394393DE890FFF7E0AF33B0@DM6PR12MB4337.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3276;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 YOiISf4ksfpVHmg5p+2PS7TVZrS5Rs5oJNzGn8B/E+jIsc3fZRYsheO5OMVuqP1nJF/vrX9L/WDJe2zqIF5nvut4Zu8VunViF2U+E+AooOPDsGVikJ7IXyHUJMjEXeM69xWos16Ex66aQV9Dogl+slQZOSbx9e9TU1ASE3C7OHlqe/SUi3yKznYbpSE8pOxMaGaDwlHH1TgGLD7NaU2EXe9ebjUTlqjW/LbkLaiJCUknoSiXif92Nok0Vxb0aUyYmDf4nGpEQtQlTSJR0k/YM99iK39wZSvequNLuQMzEuy0qXtiIrejRKkA/7OcDWldg2boKkAt451iTrJ7MfpU2AEhnH8OLgCqsRKzdiXZE2IE/ONAP3CtUFyQCQgPKjnv
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(346002)(376002)(39860400002)(136003)(66946007)(66476007)(52116002)(7696005)(8676002)(66556008)(478600001)(4326008)(6486002)(83380400001)(1076003)(36756003)(6666004)(26005)(2616005)(956004)(44832011)(2906002)(186003)(316002)(86362001)(5660300002)(16526019)(8936002)(26953001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 2vIXUfZtWH5RBdtqXczYsbiBf9WUy651QWgbylcXiDmpqfGt4QvMB8CUMtzoTBb3yLGX6m/rSEDQSojtCq0BT4PG6ssEJ+aQCwSpJysGLtaT3L9fou80ALbR3bGEXDwlxGggUHJ6uOatv4DbgFmRB5WUGdXof95esBNCVTQg9FCK5FO6fNIXYFID7Z+Jj+3Z5BnZ2dmixAoqHFyxEoNm6SlfelNwjLIdbj0OkG7FMSrEDlAoJq9qQTgNfTH6Cr573faP5ufDVWFAPyuLfBWtDvNyuOYKinKwTpWjHzIKeaw+uK4/SIfaaKl75Gaxp+iGDPefp8hShlYTUbqyTBRDIMY5Z9dLRXrOw2ZF6kz2nf5awhQxRluZGZ2/M8PMQ+fgKTFDH4P9R/Vi5LCwasBTzpoN3LjHcSk66KB/Tr/DS4JVMR1LzKnNXHZQpPTR4CIGVjgsukaWA1YWr3LXUjFDZWfSi3+so2G28I/Z2KC2UQqjcSCG0u6+YOH5e2t8JoNGCSEWnlotbRbvkqjKcrMHgPCsg6t+FeD2yUGF6y+SyUpD6t2PJlQ3JOx/KB+G+08xfqcZPrjrCcvuHFPR8LjPWBVVt/jC8onpjCWfBlXSCg4PPY576RKZakEkhUASeDvlToe6n0lI9yRQyqD39dwbLg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 17382fb0-992c-43af-6fa8-08d85ed34fea
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1163.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Sep 2020 08:41:34.8218
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 /ulK1U2f9pZyaQ6JfSORleKiwvybqNANJTzH5n+X7ePRVsfmFITtU/j8FGp6eTBCJmIXbNhqskOcRNxu+RuziQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4337
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The struct vcpu_svm.ir_list and ir_list_lock are being accessed even when
AVIC is not enabled, while current code only initialize the list and
the lock only when AVIC is enabled. This ended up trigger NULL pointer
dereference bug in the function vm_ir_list_del with the following
call trace:

    svm_update_pi_irte+0x3c2/0x550 [kvm_amd]
    ? proc_create_single_data+0x41/0x50
    kvm_arch_irq_bypass_add_producer+0x40/0x60 [kvm]
    __connect+0x5f/0xb0 [irqbypass]
    irq_bypass_register_producer+0xf8/0x120 [irqbypass]
    vfio_msi_set_vector_signal+0x1de/0x2d0 [vfio_pci]
    vfio_msi_set_block+0x77/0xe0 [vfio_pci]
    vfio_pci_set_msi_trigger+0x25c/0x2f0 [vfio_pci]
    vfio_pci_set_irqs_ioctl+0x88/0xb0 [vfio_pci]
    vfio_pci_ioctl+0x2ea/0xed0 [vfio_pci]
    ? alloc_file_pseudo+0xa5/0x100
    vfio_device_fops_unl_ioctl+0x26/0x30 [vfio]
    ? vfio_device_fops_unl_ioctl+0x26/0x30 [vfio]
    __x64_sys_ioctl+0x96/0xd0
    do_syscall_64+0x37/0x80
    entry_SYSCALL_64_after_hwframe+0x44/0xa9

Therefore, move the initialziation code before checking for AVIC enabled
so that it is always excuted.

Fixes: dfa20099e26e ("KVM: SVM: Refactor AVIC vcpu initialization into avic_init_vcpu()")
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm/avic.c | 2 --
 arch/x86/kvm/svm/svm.c  | 3 +++
 2 files changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
##### From: yadong.qi@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Qi, Yadong" <yadong.qi@intel.com>
X-Patchwork-Id: 11791499
Return-Path: <SRS0=1lRY=C7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54B3B112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 05:24:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 387A923A84
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Sep 2020 05:24:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727724AbgIVFYM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Sep 2020 01:24:12 -0400
Received: from mga09.intel.com ([134.134.136.24]:52258 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726480AbgIVFYM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Sep 2020 01:24:12 -0400
IronPort-SDR: 
 TI61EL38lSyEmDgLt9vCJ9e4u84QVSV9VmyzU8tzuVK5RbBczKq0jqsZjdTmVHUidfzVSi6Ws0
 MfYlboYtwLUw==
X-IronPort-AV: E=McAfee;i="6000,8403,9751"; a="161461361"
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="161461361"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Sep 2020 22:24:10 -0700
IronPort-SDR: 
 wSghYfMgeWPRixBTxg/Sc0+nJsYHh64kCSQTy4iRzUezxa5temmtVTVztTaCbhfVvVAGgm7Vzm
 guejKspY+yDw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,289,1596524400";
   d="scan'208";a="334855355"
Received: from yadong-antec.sh.intel.com ([10.239.158.61])
  by fmsmga004.fm.intel.com with ESMTP; 21 Sep 2020 22:24:06 -0700
From: yadong.qi@intel.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, liran.alon@oracle.com,
        nikita.leshchenko@oracle.com, chao.gao@intel.com,
        kevin.tian@intel.com, luhai.chen@intel.com, bing.zhu@intel.com,
        kai.z.wang@intel.com, yadong.qi@intel.com
Subject: [PATCH] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
Date: Tue, 22 Sep 2020 13:23:43 +0800
Message-Id: <20200922052343.84388-1-yadong.qi@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yadong Qi <yadong.qi@intel.com>

Background: We have a lightweight HV, it needs INIT-VMExit and
SIPI-VMExit to wake-up APs for guests since it do not monitor
the Local APIC. But currently virtual wait-for-SIPI(WFS) state
is not supported in nVMX, so when running on top of KVM, the L1
HV cannot receive the INIT-VMExit and SIPI-VMExit which cause
the L2 guest cannot wake up the APs.

According to Intel SDM Chapter 25.2 Other Causes of VM Exits,
SIPIs cause VM exits when a logical processor is in
wait-for-SIPI state.

In this patch:
    1. introduce SIPI exit reason,
    2. introduce wait-for-SIPI state for nVMX,
    3. advertise wait-for-SIPI support to guest.

When L1 hypervisor is not monitoring Local APIC, L0 need to emulate
INIT-VMExit and SIPI-VMExit to L1 to emulate INIT-SIPI-SIPI for
L2. L2 LAPIC write would be traped by L0 Hypervisor(KVM), L0 should
emulate the INIT/SIPI vmexit to L1 hypervisor to set proper state
for L2's vcpu state.

Handle procdure:
Source vCPU:
    L2 write LAPIC.ICR(INIT).
    L0 trap LAPIC.ICR write(INIT): inject a latched INIT event to target
       vCPU.
Target vCPU:
    L0 emulate an INIT VMExit to L1 if is guest mode.
    L1 set guest VMCS, guest_activity_state=WAIT_SIPI, vmresume.
    L0 set vcpu.mp_state to INIT_RECEIVED if (vmcs12.guest_activity_state
       == WAIT_SIPI).

Source vCPU:
    L2 write LAPIC.ICR(SIPI).
    L0 trap LAPIC.ICR write(INIT): inject a latched SIPI event to traget
       vCPU.
Target vCPU:
    L0 emulate an SIPI VMExit to L1 if (vcpu.mp_state == INIT_RECEIVED).
    L1 set CS:IP, guest_activity_state=ACTIVE, vmresume.
    L0 resume to L2.
    L2 start-up.

Signed-off-by: Yadong Qi <yadong.qi@intel.com>
---
 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  2 ++
 arch/x86/kvm/lapic.c            |  5 ++--
 arch/x86/kvm/vmx/nested.c       | 53 ++++++++++++++++++++++++---------
 4 files changed, 45 insertions(+), 16 deletions(-)

```
