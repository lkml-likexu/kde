#### [PATCH] KVM: x86: fix mmu_set_spte coding style warning
##### From: Yan Zhu <zhuyan34@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhu <zhuyan34@huawei.com>
X-Patchwork-Id: 11391351
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98E6B109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 12:51:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83B3C24654
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 12:51:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727597AbgBSMvE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 07:51:04 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10644 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727103AbgBSMvE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Feb 2020 07:51:04 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id ABEEFDECA7019B363D4E;
        Wed, 19 Feb 2020 20:51:00 +0800 (CST)
Received: from host-suse12sp4.huawei.com (10.67.133.175) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.439.0; Wed, 19 Feb 2020 20:50:51 +0800
From: Yan Zhu <zhuyan34@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>
CC: <tglx@linutronix.de>, <mingo@redhat.com>, <hpa@zytor.com>,
        <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <liucheng32@huawei.com>
Subject: [PATCH] KVM: x86: fix mmu_set_spte coding style warning
Date: Wed, 19 Feb 2020 20:50:51 +0800
Message-ID: <20200219125051.49529-1-zhuyan34@huawei.com>
X-Mailer: git-send-email 2.12.3
MIME-Version: 1.0
X-Originating-IP: [10.67.133.175]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

checkpatch.pl warns:

ERROR: code indent should use tabs where possible
+^I^I       ^Ibool speculative, bool host_writable)$

WARNING: please, no space before tabs
+^I^I       ^Ibool speculative, bool host_writable)$

This warning occurs because there is a space before the tab on this line.
Remove them so that the indentation is consistent with the Linux kernel
coding style

Fixes: 61524f1bccc0 ("KVM: x86: extend usage of RET_MMIO_PF_* constants")
Signed-off-by: Yan Zhu <zhuyan34@huawei.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/1] x86: Add control register pinning test
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11392269
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D0CE1138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:03:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B321024656
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:03:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726648AbgBSSDy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 13:03:54 -0500
Received: from mga18.intel.com ([134.134.136.126]:17830 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726598AbgBSSDx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Feb 2020 13:03:53 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 19 Feb 2020 10:03:51 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,461,1574150400";
   d="scan'208";a="436312513"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga006.fm.intel.com with ESMTP; 19 Feb 2020 10:03:50 -0800
From: John Andersen <john.s.andersen@intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: John Andersen <john.s.andersen@intel.com>
Subject: [PATCH 1/1] x86: Add control register pinning test
Date: Wed, 19 Feb 2020 10:04:36 -0800
Message-Id: <20200219180436.6580-2-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20200219180436.6580-1-john.s.andersen@intel.com>
References: <20200219180436.6580-1-john.s.andersen@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paravirutalized control register pinning adds MSRs guests can use to
discover which bits in CR0/4 they may pin, and MSRs for activating
pinning for any of those bits.

We check that the bits allowed to be pinned for CR4 are UMIP, SMEP, and
SMAP. Only WP should be allowed to be pinned in CR0.

We turn on all of the allowed bits, pin them, then attempt to disable
them. We verify that the attempt to disable was unsuccessful, and that
it generated a general protection fault.

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 x86/Makefile.common |   3 +-
 lib/x86/desc.h      |   1 +
 lib/x86/processor.h |   1 +
 lib/x86/desc.c      |   8 +++
 x86/cr_pin.c        | 163 ++++++++++++++++++++++++++++++++++++++++++++
 x86/pcid.c          |   8 ---
 x86/unittests.cfg   |   4 ++
 7 files changed, 179 insertions(+), 9 deletions(-)
 create mode 100644 x86/cr_pin.c

```
#### [PATCH v2] KVM: VMX: replace "fall through" with "return" to indicate different case
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11390281
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E64A930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 02:44:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F372D206EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 02:44:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728175AbgBSCoU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 21:44:20 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10214 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727187AbgBSCoU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 21:44:20 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id E49B176D5EFC7A29FE95;
        Wed, 19 Feb 2020 10:44:18 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.439.0; Wed, 19 Feb 2020
 10:44:13 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: VMX: replace "fall through" with "return" to indicate
 different case
Date: Wed, 19 Feb 2020 10:45:48 +0800
Message-ID: <1582080348-20827-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The second "/* fall through */" in rmode_exception() makes code harder to
read. Replace it with "return" to indicate they are different cases, only
the #DB and #BP check vcpu->guest_debug, while others don't care. And this
also improves the readability.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/7] vfio: Include optional device match in vfio_device_ops callbacks
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11392297
Return-Path: <SRS0=TgUu=4H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 751061580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:54:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 552602064C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Feb 2020 18:54:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Y2xUVvOp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726871AbgBSSyG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 13:54:06 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:54430 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726710AbgBSSyF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Feb 2020 13:54:05 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582138444;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/UO6irQAkGyQ/Cqy5oQ7oIcu+pBDHAQ9auYgdZN2lko=;
        b=Y2xUVvOp/9+g+L6qgrG6LDelto9x1PxePkZalsA/WinU035qnNeec/mTPMDQdF0bIP2ply
        Vox1rIvK3ipT2F4eazW/y0IXjJAFGXUCyqW302LeQO2AfT9K8MLtbMo7MDaZALDrsde34J
        dr/8NRJprlHM3F8bzSh23GoXeTRkSfY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-103-dP1tcruoOkKrpZ0JwaNrEw-1; Wed, 19 Feb 2020 13:54:00 -0500
X-MC-Unique: dP1tcruoOkKrpZ0JwaNrEw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BCA63107ACC5;
        Wed, 19 Feb 2020 18:53:58 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 92AAC8B561;
        Wed, 19 Feb 2020 18:53:55 +0000 (UTC)
Subject: [PATCH v2 1/7] vfio: Include optional device match in
 vfio_device_ops callbacks
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com
Date: Wed, 19 Feb 2020 11:53:55 -0700
Message-ID: <158213843517.17090.8104613366944906538.stgit@gimli.home>
In-Reply-To: <158213716959.17090.8399427017403507114.stgit@gimli.home>
References: <158213716959.17090.8399427017403507114.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow bus drivers to provide their own callback to match a device to
the user provided string.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c  |   20 ++++++++++++++++----
 include/linux/vfio.h |    4 ++++
 2 files changed, 20 insertions(+), 4 deletions(-)

```
