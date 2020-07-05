#### [RFC v7 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11643431
Return-Path: <SRS0=yPgl=AP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADF1460D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:30:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 967E7208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:30:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727803AbgGDLaP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jul 2020 07:30:15 -0400
Received: from mga04.intel.com ([192.55.52.120]:61330 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727059AbgGDLaO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jul 2020 07:30:14 -0400
IronPort-SDR: 
 3MYiQ6BH/obnPju0sCApc0ApVckJvfNeQjyIFt7c8E/MXdbFGoBHikbbrdo/homZfTyIEceH+v
 YEffPHSCPAbA==
X-IronPort-AV: E=McAfee;i="6000,8403,9671"; a="144760853"
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="144760853"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jul 2020 04:30:14 -0700
IronPort-SDR: 
 laabPi6UmJFRKigo3OosnvuMx1BdGOVYaRXzXNKTsh6lZXXWFbTS8xaxAtgtrhb3mIFq33dFTH
 HzZ8BhM9wc6A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="266146757"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga007.fm.intel.com with ESMTP; 04 Jul 2020 04:30:13 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        jasowang@redhat.com, Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v7 01/25] scripts/update-linux-headers: Import iommu.h
Date: Sat,  4 Jul 2020 04:36:25 -0700
Message-Id: <1593862609-36135-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1593862609-36135-1-git-send-email-yi.l.liu@intel.com>
References: <1593862609-36135-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: arm64: PMU: Fix per-CPU access in preemptible context
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11643623
Return-Path: <SRS0=yPgl=AP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1998D60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 13:37:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 004DD20870
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 13:37:53 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1593869874;
	bh=pNwXVAMDXVJlIpm6TO8om9y6iGboItUmVHhsv43zIi0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=OJ+XraSbU7A3DiInmCi1pmwyhLBA3he8fOhFiqwdkIrgvZCtDX27cANkaqcrKeGxP
	 phKF/Ay22ePlyfWtz2Zu8o6Oxe7SyXMX+uuumIuYtYp0KwZC6F785KgdbvBbJQxbUr
	 AyftnGw+6Icw9MD4SkRpSCfi/fS7cePQNuItMLtI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727043AbgGDNhw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jul 2020 09:37:52 -0400
Received: from mail.kernel.org ([198.145.29.99]:43488 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726643AbgGDNhw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jul 2020 09:37:52 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9539020826;
        Sat,  4 Jul 2020 13:37:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1593869871;
        bh=pNwXVAMDXVJlIpm6TO8om9y6iGboItUmVHhsv43zIi0=;
        h=From:To:Cc:Subject:Date:From;
        b=yreCcty7LGBA5T6a7Ze4NTB5GSHk/LphvReviko9cP/XfSOd/Saz9yjRkY+UPH1aR
         YsAFhRdDj9CFlAxzgqh66MrC0LaQP1cfB3kNXPwiKZEBKf6NJ2KyTGhON09NOt69MR
         pc5uSp4PjmGKq/uH6V5nFurdtpwYNvXTKfFSwW38=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=wait-a-minute.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jriMX-008xsK-Tf; Sat, 04 Jul 2020 14:37:50 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: ascull@google.com, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, amurray@thegoodpenguin.co.uk
Subject: [PATCH] KVM: arm64: PMU: Fix per-CPU access in preemptible context
Date: Sat,  4 Jul 2020 14:37:41 +0100
Message-Id: <20200704133741.148094-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, ascull@google.com, mark.rutland@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, amurray@thegoodpenguin.co.uk
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 07da1ffaa137 ("KVM: arm64: Remove host_cpu_context
member from vcpu structure") has, by removing the host CPU
context pointer, exposed that kvm_vcpu_pmu_restore_guest
is called in preemptible contexts:

[  266.932442] BUG: using smp_processor_id() in preemptible [00000000] code: qemu-system-aar/779
[  266.939721] caller is debug_smp_processor_id+0x20/0x30
[  266.944157] CPU: 2 PID: 779 Comm: qemu-system-aar Tainted: G            E     5.8.0-rc3-00015-g8d4aa58b2fe3 #1374
[  266.954268] Hardware name: amlogic w400/w400, BIOS 2020.04 05/22/2020
[  266.960640] Call trace:
[  266.963064]  dump_backtrace+0x0/0x1e0
[  266.966679]  show_stack+0x20/0x30
[  266.969959]  dump_stack+0xe4/0x154
[  266.973338]  check_preemption_disabled+0xf8/0x108
[  266.977978]  debug_smp_processor_id+0x20/0x30
[  266.982307]  kvm_vcpu_pmu_restore_guest+0x2c/0x68
[  266.986949]  access_pmcr+0xf8/0x128
[  266.990399]  perform_access+0x8c/0x250
[  266.994108]  kvm_handle_sys_reg+0x10c/0x2f8
[  266.998247]  handle_exit+0x78/0x200
[  267.001697]  kvm_arch_vcpu_ioctl_run+0x2ac/0xab8

Note that the bug was always there, it is only the switch to
using percpu accessors that made it obvious.
The fix is to wrap these accesses in a preempt-disabled section,
so that we sample a coherent context on trap from the guest.

Fixes: 435e53fb5e21 ("arm64: KVM: Enable VHE support for :G/:H perf event modifiers")
Cc:: Andrew Murray <amurray@thegoodpenguin.co.uk>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/pmu.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v4 05/15] vfio: Add PASID allocation/free support
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11643399
Return-Path: <SRS0=yPgl=AP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 96EFD913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:20:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EA2620890
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:20:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727835AbgGDLT7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jul 2020 07:19:59 -0400
Received: from mga11.intel.com ([192.55.52.93]:48343 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727798AbgGDLT6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jul 2020 07:19:58 -0400
IronPort-SDR: 
 ezBkqkEXUC7SJF/Ha/2dlIk6Fw0ud6U3qCAyYQGESz6g5+wZuIrX3c8X85O65e3IE6uVDIQ1LR
 xdId+nExaQvA==
X-IronPort-AV: E=McAfee;i="6000,8403,9671"; a="145371345"
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="145371345"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jul 2020 04:19:53 -0700
IronPort-SDR: 
 Hv8xhD2RmKgSL4hwHKETP8C1RSMe6tz6TOun1t8IfWObX8tbG6ShKmLpPT8N6E8Hn16yP0dCjP
 Rzb70VVj859w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="282521424"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga006.jf.intel.com with ESMTP; 04 Jul 2020 04:19:52 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 05/15] vfio: Add PASID allocation/free support
Date: Sat,  4 Jul 2020 04:26:19 -0700
Message-Id: <1593861989-35920-6-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1593861989-35920-1-git-send-email-yi.l.liu@intel.com>
References: <1593861989-35920-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (a.k.a Shared Virtual Memory) allows sharing
multiple process virtual address spaces with the device for simplified
programming model. PASID is used to tag an virtual address space in DMA
requests and to identify the related translation structure in IOMMU. When
a PASID-capable device is assigned to a VM, we want the same capability
of using PASID to tag guest process virtual address spaces to achieve
virtual SVA (vSVA).

PASID management for guest is vendor specific. Some vendors (e.g. Intel
VT-d) requires system-wide managed PASIDs cross all devices, regardless
of whether a device is used by host or assigned to guest. Other vendors
(e.g. ARM SMMU) may allow PASIDs managed per-device thus could be fully
delegated to the guest for assigned devices.

For system-wide managed PASIDs, this patch introduces a vfio module to
handle explicit PASID alloc/free requests from guest. Allocated PASIDs
are associated to a process (or, mm_struct) in IOASID core. A vfio_mm
object is introduced to track mm_struct. Multiple VFIO containers within
a process share the same vfio_mm object.

A quota mechanism is provided to prevent malicious user from exhausting
available PASIDs. Currently the quota is a global parameter applied to
all VFIO devices. In the future per-device quota might be supported too.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
v3 -> v4:
*) fix lock leam in vfio_mm_get_from_task()
*) drop pasid_quota field in struct vfio_mm
*) vfio_mm_get_from_task() returns ERR_PTR(-ENOTTY) when !CONFIG_VFIO_PASID

v1 -> v2:
*) added in v2, split from the pasid alloc/free support of v1
---
 drivers/vfio/Kconfig      |   5 ++
 drivers/vfio/Makefile     |   1 +
 drivers/vfio/vfio_pasid.c | 152 ++++++++++++++++++++++++++++++++++++++++++++++
 include/linux/vfio.h      |  28 +++++++++
 4 files changed, 186 insertions(+)
 create mode 100644 drivers/vfio/vfio_pasid.c

```
#### [PULL v2 07/41] accel/kvm: Convert to ram_block_discard_disable()
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11643915
Return-Path: <SRS0=yPgl=AP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E36D6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 18:29:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E62220720
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 18:29:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aObAQF5O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726895AbgGDS3t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jul 2020 14:29:49 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:30469 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726682AbgGDS3s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jul 2020 14:29:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593887387;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=+xCzX5pjcy148tNCg3zvK7ruz7b/+qmBTdtfJlorfws=;
        b=aObAQF5Oo4qUkYlp5CR9FWcGAst/F+qrU5TgDJKIJSQTHWKOz3mJ5ITRe6sB2vNIWqdhF8
        QCECMx2QAlBvks3m83ci8MpPPuSu99dDnIL/g7ByobocyEbpb7Wlwnpq7zhPHXESYEQkFE
        v55LroSmwbyhVyfXf36fBst4BGlIKjU=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-20-bOvtBLJEOqihGnlzzpTAQg-1; Sat, 04 Jul 2020 14:29:45 -0400
X-MC-Unique: bOvtBLJEOqihGnlzzpTAQg-1
Received: by mail-wr1-f71.google.com with SMTP id z1so6560914wrn.18
        for <kvm@vger.kernel.org>; Sat, 04 Jul 2020 11:29:44 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=+xCzX5pjcy148tNCg3zvK7ruz7b/+qmBTdtfJlorfws=;
        b=onH46hDIr3joV+/4YseNhUpkXAx+ozvlZrtrrtljKXTnRtEgFePE+w9rahUmhlEE+v
         8uw5Y8GaOtgZTps19x/tDlYSBiTW+ter9GdYB7DjtLdvqAlo1ZScC3bw91OwK15EOnXJ
         5yyYl/+1mQ4CRkecXudHQ0F6Vlq2ZsZUdBCbBgUjtzLxahh8XzaFervRRYrIbIzyz6dD
         yPYFaV6ZemT6Er+DqI+rpl7YB4ZVJN7DT2Rjz+CQk7toerG77hNGSyWZFqul12CY3Yr1
         27wJ+fIt6RTUUsXVf/E/c/7LXiU9a0Kgw9CwaR2B9LYwcB+xhuSJqC6Dd320TVAEzI7Q
         vekQ==
X-Gm-Message-State: AOAM531/1Xq/DUwh6RRs2Hc0cB5sr9U4i7AJw+m2Z7xX6gYXXAL86721
        b8knn9Mk6eoHjcwKCzmxMKyMWT7EjUlgb1katkUiUonwgVs8gDazh3uAic5JUI78JZ9pBz7p1/2
        Q3FJIbPFsVCUZ
X-Received: by 2002:a7b:c5c4:: with SMTP id n4mr41024448wmk.67.1593887383900;
        Sat, 04 Jul 2020 11:29:43 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzyZyhovHtwPT8kE0hmJqiRfbF25fSUFZBtXZC1AiAdPjMmXjWkRVXCdBx0KDBob2c9vz1Gng==
X-Received: by 2002:a7b:c5c4:: with SMTP id n4mr41024439wmk.67.1593887383699;
        Sat, 04 Jul 2020 11:29:43 -0700 (PDT)
Received: from redhat.com (bzq-79-182-31-92.red.bezeqint.net. [79.182.31.92])
        by smtp.gmail.com with ESMTPSA id
 s203sm8617891wms.32.2020.07.04.11.29.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 04 Jul 2020 11:29:43 -0700 (PDT)
Date: Sat, 4 Jul 2020 14:29:41 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
        David Hildenbrand <david@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PULL v2 07/41] accel/kvm: Convert to ram_block_discard_disable()
Message-ID: <20200704182750.1088103-8-mst@redhat.com>
References: <20200704182750.1088103-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200704182750.1088103-1-mst@redhat.com>
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
#### [PATCH v4 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11643403
Return-Path: <SRS0=yPgl=AP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 70EEB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:20:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53E3020890
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jul 2020 11:20:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728020AbgGDLU0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jul 2020 07:20:26 -0400
Received: from mga11.intel.com ([192.55.52.93]:48338 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726667AbgGDLUZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jul 2020 07:20:25 -0400
IronPort-SDR: 
 a2gj+fkiDqA0DY5a0RW+pedL4MxPn4d62h+Lw3m+Bq0lh4WgOWIz1Q0mmk0IMtUw7+Nz5PTgbf
 r4Rjh0NkwkKg==
X-IronPort-AV: E=McAfee;i="6000,8403,9671"; a="145371335"
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="145371335"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jul 2020 04:19:53 -0700
IronPort-SDR: 
 RJe1zSbxFxR0ij0gpvc9x4ZATrx5EGqzy2YgoNH/VBsNYcGhJuo6KfeWjyVaD/2efef/P8wDWn
 +ZD/GcLq26eQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,311,1589266800";
   d="scan'208";a="282521408"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga006.jf.intel.com with ESMTP; 04 Jul 2020 04:19:52 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
Date: Sat,  4 Jul 2020 04:26:15 -0700
Message-Id: <1593861989-35920-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1593861989-35920-1-git-send-email-yi.l.liu@intel.com>
References: <1593861989-35920-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch refactors the vfio_iommu_type1_ioctl() to use switch instead of
if-else, and each cmd got a helper function.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Suggested-by: Christoph Hellwig <hch@infradead.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 392 ++++++++++++++++++++++------------------
 1 file changed, 213 insertions(+), 179 deletions(-)

```
