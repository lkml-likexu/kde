#### [PATCH 2/4] vfio: vfio_pci_nvlink2: use mmgrab
##### From: Julia Lawall <Julia.Lawall@inria.fr>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Julia Lawall <julia.lawall@inria.fr>
X-Patchwork-Id: 11312247
Return-Path: <SRS0=Vudl=2T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC25514DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Dec 2019 16:19:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B82C920722
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Dec 2019 16:19:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726901AbfL2QTg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Dec 2019 11:19:36 -0500
Received: from mail3-relais-sop.national.inria.fr ([192.134.164.104]:38978
        "EHLO mail3-relais-sop.national.inria.fr" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726455AbfL2QTd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 29 Dec 2019 11:19:33 -0500
X-IronPort-AV: E=Sophos;i="5.69,372,1571695200";
   d="scan'208";a="334379017"
Received: from palace.rsr.lip6.fr (HELO palace.lip6.fr) ([132.227.105.202])
  by mail3-relais-sop.national.inria.fr with ESMTP/TLS/AES128-SHA256;
 29 Dec 2019 17:19:30 +0100
From: Julia Lawall <Julia.Lawall@inria.fr>
To: Alex Williamson <alex.williamson@redhat.com>
Cc: kernel-janitors@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 2/4] vfio: vfio_pci_nvlink2: use mmgrab
Date: Sun, 29 Dec 2019 16:42:56 +0100
Message-Id: <1577634178-22530-3-git-send-email-Julia.Lawall@inria.fr>
X-Mailer: git-send-email 1.9.1
In-Reply-To: <1577634178-22530-1-git-send-email-Julia.Lawall@inria.fr>
References: <1577634178-22530-1-git-send-email-Julia.Lawall@inria.fr>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mmgrab was introduced in commit f1f1007644ff ("mm: add new mmgrab()
helper") and most of the kernel was updated to use it. Update a
remaining file.

The semantic patch that makes this change is as follows:
(http://coccinelle.lip6.fr/)

<smpl>
@@ expression e; @@
- atomic_inc(&e->mm_count);
+ mmgrab(e);
</smpl>

Signed-off-by: Julia Lawall <Julia.Lawall@inria.fr>
---
 drivers/vfio/pci/vfio_pci_nvlink2.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
