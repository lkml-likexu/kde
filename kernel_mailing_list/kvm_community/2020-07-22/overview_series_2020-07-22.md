#### [PATCH v4 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11678627
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BC0313B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 15:09:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 048DA20717
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 15:09:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728640AbgGVPJf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 11:09:35 -0400
Received: from mga14.intel.com ([192.55.52.115]:33983 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726717AbgGVPJf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 11:09:35 -0400
IronPort-SDR: 
 U26Kuat8UbsNctz5Obv3eNfVmtVsie2tIVsHELHt5VZuzCMmrGpZ1fQJp1ubGhf7vjurV2WKOR
 37clq0+SVydQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="149513610"
X-IronPort-AV: E=Sophos;i="5.75,383,1589266800";
   d="scan'208";a="149513610"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 08:09:34 -0700
IronPort-SDR: 
 QQIs0lmO+pvASE4/O3i58DtNRukhEYFXW9K9oFZ84cibAlFQj6GX2EJp5dKOHlwNpuCEwZUmnJ
 nC2C6brPdpAA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,383,1589266800";
   d="scan'208";a="432407255"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.58.190])
  by orsmga004.jf.intel.com with ESMTP; 22 Jul 2020 08:09:31 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v4 1/4] vhost: convert VHOST_VSOCK_SET_RUNNING to a generic
 ioctl
Date: Wed, 22 Jul 2020 17:09:24 +0200
Message-Id: <20200722150927.15587-2-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200722150927.15587-1-guennadi.liakhovetski@linux.intel.com>
References: <20200722150927.15587-1-guennadi.liakhovetski@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VHOST_VSOCK_SET_RUNNING is used by the vhost vsock driver to perform
crucial VirtQueue initialisation, like assigning .private fields and
calling vhost_vq_init_access(), and clean up. However, this ioctl is
actually extremely useful for any vhost driver, that doesn't have a
side channel to inform it of a status change, e.g. upon a guest
reboot. This patch makes that ioctl generic, while preserving its
numeric value and also keeping the original alias.

Signed-off-by: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
---
 include/uapi/linux/vhost.h | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [patch V5 01/15] seccomp: Provide stub for __secure_computing()References: <20200722215954.464281930@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11679289
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CAF9B6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 22:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B1E2822B43
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 22:14:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="V+1Ckav1";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="EeJ7V0TR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733068AbgGVWL1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 18:11:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39130 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733042AbgGVWL0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 18:11:26 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1EEA2C0619E1;
        Wed, 22 Jul 2020 15:11:26 -0700 (PDT)
Message-Id: <20200722220519.404974280@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1595455883;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=V20TjmN1n9jq0pcYjqfVM1GUS2Jje/9aKzst9S90g0M=;
        b=V+1Ckav1bl2n3nhw2Dy7IetRojALQ0RML0iVbCWHR5tqcRMvDVODaR65R6XVMVggrYvYam
        4Z8es+jLyY58pTfgGe0usp5pEHmmbOzU9TAPnXR5doNaNITE+rWxaXerA5LSLnhMbHdiyc
        TGCX7Mstx88deWvr7MI9hNuQWC9pPheUfkOzAQRyQKHVvmxVMF2lV0c2A+hpO2+AZKrVMT
        3HgPU/z1oQaolmTtTzOxWdTiFMS/Sjpbr247ifjjHetYVnP7daOkUCz9ditlpu+ahsQoo8
        od5Wv0XrJ/LQ/XZJ8TM+nXqzqEizGV4xebVfXJuH/4qQlKxZ4og6p7a3pyGBGg==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1595455883;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=V20TjmN1n9jq0pcYjqfVM1GUS2Jje/9aKzst9S90g0M=;
        b=EeJ7V0TRXQTAq7HVtVDVgfGUCl9yNBv3qi+SMW0zk4jgVi6oI+bzn9f2JIrYs5xrk80gBl
        yRX2cEV3WGpTSuCg==
Date: Wed, 22 Jul 2020 23:59:55 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Gabriel Krisman Bertazi <krisman@collabora.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [patch V5 01/15] seccomp: Provide stub for __secure_computing()
References: <20200722215954.464281930@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

To avoid #ifdeffery in the upcoming generic syscall entry work code provide
a stub for __secure_computing() as this is preferred over
secure_computing() because the TIF flag is already evaluated.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Kees Cook <keescook@chromium.org>
---
V4: New patch
---
 include/linux/seccomp.h |    1 +
```
#### [PATCH V3 1/6] vhost: introduce vhost_vring_call
##### From: Zhu Lingshan <lingshan.zhu@live.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@live.com>
X-Patchwork-Id: 11678029
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC6A013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 09:53:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DD1B20729
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 09:53:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731629AbgGVJxL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 05:53:11 -0400
Received: from mga18.intel.com ([134.134.136.126]:63311 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731561AbgGVJxL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 05:53:11 -0400
IronPort-SDR: 
 P+X4izlAgIkDr8yuxWDb/1457zkaH+BNL4ZBjLUHys3Etmlys5QxEo7zxKXv2cJtTPzu6d5Q/o
 cz3Q2hiGExeg==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="137804230"
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="137804230"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 02:53:09 -0700
IronPort-SDR: 
 mB+rfWFeiRQEzremak0a2YtT3q+qmLrum5kwCitYG3VPFZUd7hq0Gru2Wimin1BrZ+o4YyTuWK
 lr6NBKFCk/tA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="487936075"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga006.fm.intel.com with ESMTP; 22 Jul 2020 02:53:06 -0700
From: Zhu Lingshan <lingshan.zhu@live.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>,
        lszhu <lszhu@localhost.localdomain>,
        Zhu Lingshan <lingshan.zhu@live.com>
Subject: [PATCH V3 1/6] vhost: introduce vhost_vring_call
Date: Wed, 22 Jul 2020 17:49:05 +0800
Message-Id: <20200722094910.218014-2-lingshan.zhu@live.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200722094910.218014-1-lingshan.zhu@live.com>
References: <20200722094910.218014-1-lingshan.zhu@live.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Zhu Lingshan <lingshan.zhu@intel.com>

This commit introduces struct vhost_vring_call which replaced
raw struct eventfd_ctx *call_ctx in struct vhost_virtqueue.
Besides eventfd_ctx, it contains a spin lock and an
irq_bypass_producer in its structure.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Signed-off-by: lszhu <lszhu@localhost.localdomain>
Signed-off-by: Zhu Lingshan <lingshan.zhu@live.com>
---
 drivers/vhost/vdpa.c  |  4 ++--
 drivers/vhost/vhost.c | 22 ++++++++++++++++------
 drivers/vhost/vhost.h |  9 ++++++++-
 3 files changed, 26 insertions(+), 9 deletions(-)

```
#### [PATCH V3 1/6] vhost: introduce vhost_vring_call
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11678089
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 79AFF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 10:13:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69EF5206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 10:13:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731809AbgGVKNI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 06:13:08 -0400
Received: from mga07.intel.com ([134.134.136.100]:37342 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731561AbgGVKNH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 06:13:07 -0400
IronPort-SDR: 
 KPvT9Nqc8fba1HVTp7V5Ig2I05gzalsbp9USUyexNLsDFHIhRRnOE9X4kfGGxjCuVYFE2KdaUL
 WdgL/vDdpXSA==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="214940289"
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="214940289"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 03:13:06 -0700
IronPort-SDR: 
 mlagXOH02rsRhyQAftlp0y5/ECqDBls1Rh20zk5X4cSZ7d3iTm7ipj28vhB2CPs51oUdhQ49iu
 1t2LWo1cDFeg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="392634878"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga001.fm.intel.com with ESMTP; 22 Jul 2020 03:13:03 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 1/6] vhost: introduce vhost_vring_call
Date: Wed, 22 Jul 2020 18:08:54 +0800
Message-Id: <20200722100859.221669-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200722100859.221669-1-lingshan.zhu@intel.com>
References: <20200722100859.221669-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduces struct vhost_vring_call which replaced
raw struct eventfd_ctx *call_ctx in struct vhost_virtqueue.
Besides eventfd_ctx, it contains a spin lock and an
irq_bypass_producer in its structure.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c  |  4 ++--
 drivers/vhost/vhost.c | 22 ++++++++++++++++------
 drivers/vhost/vhost.h |  9 ++++++++-
 3 files changed, 26 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: arm64: Prevent vcpu_has_ptrauth from generating OOL functions
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11678915
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A492713A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:23:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A1D8206C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:23:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1595434987;
	bh=JDuAd/IXbI8mLdXTBjc0KnzENivxsT/B90lZcHtXwho=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=Ym6lWciWgcPFHuPYc5GGsjA1ZMOHNWW2abDHL99bbzR6kzLd1d0lZNwk7fDqyeMGf
	 0TMmW0Eaqj8UAYtz26zvDT0wYaxBhGpLmBxAytNWE7Gk1bSFFuH7CwVZnlkD59juOC
	 LnCzQH/+W9sl4BU58c2eERY0RgDOU0JrIpnlhv1Y=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727044AbgGVQXG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 12:23:06 -0400
Received: from mail.kernel.org ([198.145.29.99]:46776 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726642AbgGVQXG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 12:23:06 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 983052065F;
        Wed, 22 Jul 2020 16:23:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1595434985;
        bh=JDuAd/IXbI8mLdXTBjc0KnzENivxsT/B90lZcHtXwho=;
        h=From:To:Cc:Subject:Date:From;
        b=udcoRBeZF9RGPjhoURMUpD3UOr/OOnpMCD9pTkbd3aDurKJl11MY/yzD6rpZoRjA6
         Z/t+wAijL9lSdZLAeCBTU4LBlpf4oj26sPVCr3uXmGNTNIZC46aunqF46m2n5U1Fnb
         T9gu5YQz2f6mdtoBlP32JjoZHYvc1cawuc1feO5c=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jyHWJ-00E1Ih-Uq; Wed, 22 Jul 2020 17:23:04 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu
Cc: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>, kernel-team@android.com,
        Nathan Chancellor <natechancellor@gmail.com>,
        Nick Desaulniers <ndesaulniers@google.com>
Subject: [PATCH] KVM: arm64: Prevent vcpu_has_ptrauth from generating OOL
 functions
Date: Wed, 22 Jul 2020 17:22:31 +0100
Message-Id: <20200722162231.3689767-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 will@kernel.org, kernel-team@android.com, natechancellor@gmail.com,
 ndesaulniers@google.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far, vcpu_has_ptrauth() is implemented in terms of system_supports_*_auth()
calls, which are declared "inline". In some specific conditions (clang
and SCS), the "inline" very much turns into an "out of line", which
leads to a fireworks when this predicate is evaluated on a non-VHE
system (right at the beginning of __hyp_handle_ptrauth).

Instead, make sure vcpu_has_ptrauth gets expanded inline by directly
using the cpus_have_final_cap() helpers, which are __always_inline,
generate much better code, and are the only thing that make sense when
running at EL2 on a nVHE system.

Fixes: 29eb5a3c57f7 ("KVM: arm64: Handle PtrAuth traps early")
Reported-by: Nathan Chancellor <natechancellor@gmail.com>
Reported-by: Nick Desaulniers <ndesaulniers@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/5] kvm: x86: refactor masterclock sync heuristics out of kvm_write_tsc
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11677191
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6852813B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 03:26:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 498B4207CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 03:26:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="iXEvVZny"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731962AbgGVD0p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 23:26:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33878 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731781AbgGVD0o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 23:26:44 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9AA62C061794
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 20:26:44 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id cq11so570188pjb.0
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 20:26:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=rBjLpJvTlzHOoYcg3+C8dCA5VSP3fypEK3RTeWQeLVI=;
        b=iXEvVZnyqqUIHuCxPhULMAKLJYa4b9Li0gVjxyIKBvyiU8p7SFA4cK9FT8uFcXaWPQ
         Fs8yFlNg5TQRfZ7+2e1X24q9NNBqY26TDNPDMUqx6g3RukK+W1NB1VUo2b88M32kG1C6
         rY3aulX1BV/zr5Vm7XwOBVn7WImptMB0ncUS0TcfiUUEBkLpRSJocskJGSATkDxavX7o
         +lLdzRiNfEOG//FfXQ2fxRCiwlpHQNnp/fZcD0bLH8vtYf/+mxbYOj6Pjpjqeu3EiIsS
         fGmRSeMfPkwuaeotZp4+6Kt4L5543u/fOxoUOPtkiMoZ75W+qDat2Ut+G75lNXqUSG5p
         cHxw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=rBjLpJvTlzHOoYcg3+C8dCA5VSP3fypEK3RTeWQeLVI=;
        b=ZDXV9i91LY/vT4ivo7VZ1QXuy73OcXwfRZIZkW7RMVs6TE8suWHHrGTJQiNdwocFxT
         3NnyVn5Lr2m+Uwr+8vBnH05RRZ+jd2c5fWcNswqShbV7Z74ZOEE7zbMVOjMhh+gStEVw
         yBlE06tP8fkFrMkIdUOYp39gdN9EtBbaozRQhWcIb+5wqQuC8gDBhnxJOBGDMDIcMtO0
         rPxMPjMTxJt83uYCszxwDLWEXxL6spcgROBSK3T33YNfposOPw9o+LuY6/fti3PI2y4v
         nBnHWyCXFDkKV77hFSHAPTSi4OexqPpYzGFyuTX2isRfXYCfkhxAZB1Kf0B/ai1vlSTI
         P7jw==
X-Gm-Message-State: AOAM532KyKu+tkZ3mvA0HGCGDydhgBZ55OWg5vsuW7ivAHNSXEgZzzsL
        HZ+WvnBNdg7aOexj7ZN61C+FTe/ucyf6DcOocMpc9L5g7DMaFnNJhgxCAMi0DllxbLQm4iEFyt+
        XmJsoOZLTSNznGDUofv4RML6B4cemOzpoYmN0g9zO4YofwjOuxd+pYbwKTw==
X-Google-Smtp-Source: 
 ABdhPJyEdiCwV7hm7tZ+J8ksVri4B4y0gGGlhc2SciNBoTbDcHlZ6JXXNaRofbv314Idp4PiLJXS/fXO8zg=
X-Received: by 2002:a17:90a:bd8b:: with SMTP id
 z11mr621949pjr.0.1595388403479;
 Tue, 21 Jul 2020 20:26:43 -0700 (PDT)
Date: Wed, 22 Jul 2020 03:26:25 +0000
In-Reply-To: <20200722032629.3687068-1-oupton@google.com>
Message-Id: <20200722032629.3687068-2-oupton@google.com>
Mime-Version: 1.0
References: <20200722032629.3687068-1-oupton@google.com>
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH v3 1/5] kvm: x86: refactor masterclock sync heuristics out of
 kvm_write_tsc
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Hornyack <peterhornyack@google.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_write_tsc() determines when the host or guest is attempting to
synchronize the TSCs and does some bookkeeping for tracking this. Retain
the existing sync checks (host is writing 0 or TSCs being written within
a second of one another) in kvm_write_tsc(), but split off the
bookkeeping and TSC offset write into a new function. This allows for a
new ioctl to be introduced, yielding control of the TSC offset field to
userspace in a manner that respects the existing masterclock heuristics.

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 98 +++++++++++++++++++++++++---------------------
 1 file changed, 54 insertions(+), 44 deletions(-)

```
#### [RFC PATCH v1 01/34] KVM: x86: export .get_vmfunc_status()
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11678825
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EED1014E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:01:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D68EB206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:01:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728579AbgGVQBe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 12:01:34 -0400
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:37824 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726938AbgGVQBe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Jul 2020 12:01:34 -0400
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 E33593016C4A;
        Wed, 22 Jul 2020 19:01:31 +0300 (EEST)
Received: from localhost.localdomain (unknown [91.199.104.6])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id D81173072785;
        Wed, 22 Jul 2020 19:01:31 +0300 (EEST)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Marian Rotariu <marian.c.rotariu@gmail.com>, =?utf-8?q?=C8=98tefan_=C8=98ic?=
	=?utf-8?q?leru?= <ssicleru@bitdefender.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
Subject: [RFC PATCH v1 01/34] KVM: x86: export .get_vmfunc_status()
Date: Wed, 22 Jul 2020 19:00:48 +0300
Message-Id: <20200722160121.9601-2-alazar@bitdefender.com>
In-Reply-To: <20200722160121.9601-1-alazar@bitdefender.com>
References: <20200722160121.9601-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marian Rotariu <marian.c.rotariu@gmail.com>

The introspection tool uses this function to check the hardware support
for VMFUNC, which can be used either to singlestep vCPUs
on a unprotected EPT view or to use #VE in order to filter out
VM-exits caused by EPT violations.

Signed-off-by: Marian Rotariu <marian.c.rotariu@gmail.com>
Co-developed-by: Ștefan Șicleru <ssicleru@bitdefender.com>
Signed-off-by: Ștefan Șicleru <ssicleru@bitdefender.com>
Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/vmx/vmx.c          | 6 ++++++
 2 files changed, 7 insertions(+)

```
