#### [PATCH v4 kvmtool 01/12] ioport: mmio: Use a mutex and reference counting for locking
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11549141
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 231DE59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 15:38:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07E1C2065D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 15:38:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727772AbgENPim (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 11:38:42 -0400
Received: from foss.arm.com ([217.140.110.172]:39144 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726056AbgENPil (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 11:38:41 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id DFC971045;
        Thu, 14 May 2020 08:38:40 -0700 (PDT)
Received: from e121566-lin.arm.com (unknown [10.57.31.200])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 A84523F71E;
        Thu, 14 May 2020 08:38:39 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com, maz@kernel.org
Subject: [PATCH v4 kvmtool 01/12] ioport: mmio: Use a mutex and reference
 counting for locking
Date: Thu, 14 May 2020 16:38:18 +0100
Message-Id: <1589470709-4104-2-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1589470709-4104-1-git-send-email-alexandru.elisei@arm.com>
References: <1589470709-4104-1-git-send-email-alexandru.elisei@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvmtool uses brlock for protecting accesses to the ioport and mmio
red-black trees. brlock allows concurrent reads, but only one writer, which
is assumed not to be a VCPU thread (for more information see commit
0b907ed2eaec ("kvm tools: Add a brlock)). This is done by issuing a
compiler barrier on read and pausing the entire virtual machine on writes.
When KVM_BRLOCK_DEBUG is defined, brlock uses instead a pthread read/write
lock.

When we will implement reassignable BARs, the mmio or ioport mapping will
be done as a result of a VCPU mmio access. When brlock is a pthread
read/write lock, it means that we will try to acquire a write lock with the
read lock already held by the same VCPU and we will deadlock. When it's
not, a VCPU will have to call kvm__pause, which means the virtual machine
will stay paused forever.

Let's avoid all this by using a mutex and reference counting the red-black
tree entries. This way we can guarantee that we won't unregister a node
that another thread is currently using for emulation.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 include/kvm/ioport.h          |   2 +
 include/kvm/rbtree-interval.h |   4 +-
 ioport.c                      |  85 ++++++++++++++++++++++-----------
 mmio.c                        | 107 ++++++++++++++++++++++++++++++++----------
 4 files changed, 143 insertions(+), 55 deletions(-)

```
#### [PATCH Kernel v20 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11549801
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54847697
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 21:11:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 32A90206F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 21:11:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Za9RhaWB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728290AbgENVLL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 17:11:11 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:11306 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728043AbgENVLL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 17:11:11 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebdb3a10000>; Thu, 14 May 2020 14:09:53 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 14 May 2020 14:11:09 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 14 May 2020 14:11:09 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 14 May
 2020 21:11:08 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 14 May 2020 21:11:02 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v20 1/8] vfio: UAPI for migration interface for device
 state
Date: Fri, 15 May 2020 02:07:40 +0530
Message-ID: <1589488667-9683-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589488667-9683-1-git-send-email-kwankhede@nvidia.com>
References: <1589488667-9683-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589490593; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=Za9RhaWBJIEHPTDn3wz7Zxvugojxj3pLFj1+KscuUb6AvM9P49c6tb+f9c4u1KsM4
         vZb5z5IAbsdI4YvvC+YfFUpt+O3GksB3diqS7IS5byw7oRew3dYl7x3gEYNa9yMWZP
         yEin1+OGaEJJpUnGKFi1tVyW5vMh0PcVQPPYFAL7k8ctqXK+DagiS0PkvN+TLp/YK9
         EgealmlljN9tPWR6AbzXLclyuvE2xKXJQGm0t9oTBftMoUvLhur9iIv1FLMFVT6kSk
         bqcnx55EnM94vcJzEVA5KMwfg9MFAqHNp/O1YEh7YeCu4XpBHXsdUiAsG9VY9q5S/F
         RdWGRa2fpSUuw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH v11 01/11] perf/x86: Fix variable types for LBR registers
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11548235
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 21F1560D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 08:31:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1512D2074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 08:31:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726126AbgENIbN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 04:31:13 -0400
Received: from mga18.intel.com ([134.134.136.126]:12082 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726032AbgENIbN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 04:31:13 -0400
IronPort-SDR: 
 FVEiGjUqFpGAyCGTGXEF1GEvM8h0rWuXHPn+J6NW4WIEhuGXGVQRjmCRx4f20E991guxNjqgyI
 AhZv081oGb6g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 May 2020 01:31:12 -0700
IronPort-SDR: 
 9XWc+sruIwRfNn7Rh1sIanPM0IFYR2MyJP81M69xvd01H9zD2Zl0evdC3JHt7+O9LQ5XXi4m9W
 G/sShjQvuirg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,390,1583222400";
   d="scan'208";a="341539917"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga001.jf.intel.com with ESMTP; 14 May 2020 01:31:09 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>, ak@linux.intel.com,
        wei.w.wang@intel.com
Subject: [PATCH v11 01/11] perf/x86: Fix variable types for LBR registers
Date: Thu, 14 May 2020 16:30:44 +0800
Message-Id: <20200514083054.62538-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200514083054.62538-1-like.xu@linux.intel.com>
References: <20200514083054.62538-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wei Wang <wei.w.wang@intel.com>

The msr variable type can be 'unsigned int', which uses less memory than
the longer 'unsigned long'. Fix 'struct x86_pmu' for that. The lbr_nr won't
be a negative number, so make it 'unsigned int' as well.

Cc: Peter Zijlstra (Intel) <peterz@infradead.org>
Suggested-by: Peter Zijlstra (Intel) <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvmtool] rtc: Generate fdt node for the real-time clock
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?q?Andr=C3=A9_Przywara?=
 <andre.przywara@arm.com>
X-Patchwork-Id: 11548415
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 84E19739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 09:46:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EA5F206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 09:46:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725976AbgENJqA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 05:46:00 -0400
Received: from foss.arm.com ([217.140.110.172]:33318 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725878AbgENJqA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 05:46:00 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A886431B;
        Thu, 14 May 2020 02:45:59 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.25])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 ACFCA3F305;
        Thu, 14 May 2020 02:45:58 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Sami Mujawar <sami.mujawar@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [PATCH kvmtool] rtc: Generate fdt node for the real-time clock
Date: Thu, 14 May 2020 10:45:53 +0100
Message-Id: <20200514094553.135663-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On arm and arm64 we expose the Motorola RTC emulation to the guest,
but never advertised this in the device tree.

EDK-2 seems to rely on this device, but on its hardcoded address. To
make this more future-proof, add a DT node with the address in it.
EDK-2 can then read the proper address from there, and we can change
this address later (with the flexible memory layout).

Please note that an arm64 Linux kernel is not ready to use this device,
there are some include files missing under arch/arm64 to compile the
driver. I hacked this up in the kernel, just to verify this DT snippet
is correct, but don't see much value in enabling this properly in
Linux.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 hw/rtc.c | 44 ++++++++++++++++++++++++++++++++++++++------
 1 file changed, 38 insertions(+), 6 deletions(-)

```
#### [PATCH RFC 1/5] KVM: rename labels in kvm_init()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11549459
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DC2414E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 18:06:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D03720675
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 18:06:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I8bxNCzY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726885AbgENSGA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 14:06:00 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:55248 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726444AbgENSF4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 May 2020 14:05:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589479555;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=j0jX4S3xcP8FeurtghgmIUcBDnvQJ3FkSTFSnx7A6Wo=;
        b=I8bxNCzYHhKKutJKdQchAz083oEtl8iw3ZBKvsIJf3CPkZ/poGaD4FxvzSM2gqYVuroSEr
        DNe5nt15g8fAxJsYkoDeEdYB2+/jQZ7OiUd3Hoy36BQgq1+UNWwr/iBRHtvgUSloBspTAB
        Gk6NdB9FFP1Cj+vnKUR5mqPZKwOO8GM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-291-I0NGR2hFPLyIEK5uTeGS9Q-1; Thu, 14 May 2020 14:05:52 -0400
X-MC-Unique: I0NGR2hFPLyIEK5uTeGS9Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B70FE107ACCD;
        Thu, 14 May 2020 18:05:50 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.178])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EB6705D9CA;
        Thu, 14 May 2020 18:05:47 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, x86@kernel.org
Subject: [PATCH RFC 1/5] KVM: rename labels in kvm_init()
Date: Thu, 14 May 2020 20:05:36 +0200
Message-Id: <20200514180540.52407-2-vkuznets@redhat.com>
In-Reply-To: <20200514180540.52407-1-vkuznets@redhat.com>
References: <20200514180540.52407-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Label names in kvm_init() are horrible, rename them to make it obvious
what we are going to do on the failure path.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 virt/kvm/kvm_main.c | 33 ++++++++++++++++-----------------
 1 file changed, 16 insertions(+), 17 deletions(-)

```
#### [kvm-unit-tests PATCH 01/11] x86/access: Fix phys-bits parameter
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11549595
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 562E6697
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 19:26:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38C702065F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 19:26:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="J/O/3AAw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727904AbgENT0r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 15:26:47 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:38448 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727869AbgENT0q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 May 2020 15:26:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589484405;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=rY2cYf+JQwIw292enk42+PfnTxsr6TeBeQ3Eoug1TqY=;
        b=J/O/3AAwz543qHavoGJOOZ6D57jMhbg7CYW0ri/TI3Z8PFYeLlzPS/TE8h4/8xPBhqS9JT
        WuUlahcQQz0ceEVBDQ2MgeoZy3uhqWpJbDTOfqGzcgaVtbb+sXlVEKZBnz10Ssug3USVam
        dtujEGjIpw0fySqtppbWylXi8lGq5fc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-438-3ZyGTTl2MNCVgZr3BK1Bpg-1; Thu, 14 May 2020 15:26:41 -0400
X-MC-Unique: 3ZyGTTl2MNCVgZr3BK1Bpg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CA108872FE0;
        Thu, 14 May 2020 19:26:40 +0000 (UTC)
Received: from thuth.com (ovpn-112-56.ams2.redhat.com [10.36.112.56])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5507C5C1D6;
        Thu, 14 May 2020 19:26:32 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>,
        Drew Jones <drjones@redhat.com>,
        Bill Wendling <morbo@google.com>
Subject: [kvm-unit-tests PATCH 01/11] x86/access: Fix phys-bits parameter
Date: Thu, 14 May 2020 21:26:16 +0200
Message-Id: <20200514192626.9950-2-thuth@redhat.com>
In-Reply-To: <20200514192626.9950-1-thuth@redhat.com>
References: <20200514192626.9950-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mohammed Gamal <mgamal@redhat.com>

Some QEMU versions don't support setting phys-bits argument directly.
This causes breakage to Travis CI. Work around the bug by setting
host-phys-bits=on

Fixes: 1a296ac170f ("x86: access: Add tests for reserved bits of guest physical address")

Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
Tested-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC 01/18] target/i386: sev: Remove unused QSevGuestInfoClass
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11548071
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05D66913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 06:41:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D98DC206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 06:41:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="UiBTk1Qb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726298AbgENGl5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 02:41:57 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46874 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726031AbgENGl3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 May 2020 02:41:29 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 422DAC061A0E
        for <kvm@vger.kernel.org>; Wed, 13 May 2020 23:41:29 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49N24j1TrSz9sRY; Thu, 14 May 2020 16:41:25 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1589438485;
        bh=ashVLzPUBifri1PsQalHIQvNrsJ7OliY+iJiflpx624=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=UiBTk1QbghtBjYM+WrQtIfWtFhpPd5X6iT0EF/7XMdBNfNEuR3wvJc171H5jBAZvN
         H/sCHg6g6uTIt1XvtIBhFUnoBXIKzvQsZqZ9onnPv/oPYhjqUnjr3yhzW7V1Gaw9PL
         Op7imZWHE2rboK07LAUL2RbBsiaDPtit+enovnCo=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, frankja@linux.ibm.com, pair@us.redhat.com,
        qemu-devel@nongnu.org, brijesh.singh@amd.com
Cc: kvm@vger.kernel.org, qemu-ppc@nongnu.org,
        David Gibson <david@gibson.dropbear.id.au>,
        Richard Henderson <rth@twiddle.net>, cohuck@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, qemu-devel@nongnu.-rg,
        mdroth@linux.vnet.ibm.com
Subject: [RFC 01/18] target/i386: sev: Remove unused QSevGuestInfoClass
Date: Thu, 14 May 2020 16:41:03 +1000
Message-Id: <20200514064120.449050-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200514064120.449050-1-david@gibson.dropbear.id.au>
References: <20200514064120.449050-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This structure is nothing but an empty wrapper around the parent class,
which by QOM conventions means we don't need it at all.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 target/i386/sev.c      | 1 -
 target/i386/sev_i386.h | 5 -----
 2 files changed, 6 deletions(-)

```
#### [PATCH 1/2] vfio: Introduce bus driver to IOMMU invalidation interface
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11549325
Return-Path: <SRS0=5r3a=64=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E98C618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 16:52:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17C2E2065F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 14 May 2020 16:52:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GgrahZ6C"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726067AbgENQwK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 14 May 2020 12:52:10 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:36641 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726046AbgENQwJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 May 2020 12:52:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589475127;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=0cBlEyN+N4Yp8SqlcEWmTzn29c4RHTyzWyxxzGkYcYs=;
        b=GgrahZ6CAmBuP9rirw6S42IoIiCp6ddEBRSNntyj9dc2KXLqcO5QpJqUWgfyo6l2I5C76e
        rnWkyXMfXwMQ+kEB9K55onBSMcLcA/tFFmo9EudJ/pL7TnajQV5WwkdFjU48zcEIbasxFR
        djGR2cCGytPXwIxYvMP2DPucb0bAS+I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-2XPFKq8ZNbqZt_HPQ1DmuA-1; Thu, 14 May 2020 12:52:05 -0400
X-MC-Unique: 2XPFKq8ZNbqZt_HPQ1DmuA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 61B4F1005510;
        Thu, 14 May 2020 16:52:04 +0000 (UTC)
Received: from gimli.home (ovpn-113-111.phx2.redhat.com [10.3.113.111])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AF9AF620AF;
        Thu, 14 May 2020 16:51:58 +0000 (UTC)
Subject: [PATCH 1/2] vfio: Introduce bus driver to IOMMU invalidation
 interface
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca,
        peterx@redhat.com
Date: Thu, 14 May 2020 10:51:58 -0600
Message-ID: <158947511830.12590.15083888449284990563.stgit@gimli.home>
In-Reply-To: <158947414729.12590.4345248265094886807.stgit@gimli.home>
References: <158947414729.12590.4345248265094886807.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VFIO bus drivers, like vfio-pci, can allow mmaps of non-page backed
device memory, such as MMIO regions of the device.  The user may then
map these ranges through the IOMMU, for example to enable peer-to-peer
DMA between devices.  When these ranges are zapped or removed from the
user, such as when the MMIO region is disabled or the device is
released, we should also remove the IOMMU mapping.  This provides
kernel level enforcement of the behavior we already see from userspace
drivers like QEMU, where these ranges are unmapped when they become
inaccessible.  This userspace behavior is still recommended as this
support only provides invalidation, dropping unmapped vmas.  Those
vmas are not automatically re-installed when re-mapped.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c         |   34 +++++++++-
 drivers/vfio/pci/vfio_pci_private.h |    1 
 drivers/vfio/vfio.c                 |   14 ++++
 drivers/vfio/vfio_iommu_type1.c     |  123 ++++++++++++++++++++++++++---------
 include/linux/vfio.h                |    5 +
 5 files changed, 142 insertions(+), 35 deletions(-)

```
