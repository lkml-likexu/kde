

#### [PATCH v2 0/8] tools/vhost: Reset virtqueue on tests
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Thu Apr 16 07:56:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
X-Patchwork-Id: 11492457
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B743186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 07:58:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 12F5420784
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 07:58:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HDkGgjg3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2440767AbgDPH6u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 03:58:50 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:31351 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2440765AbgDPH5A (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 03:57:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587023819;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=tgxXuDfLVs6iIVTGmU8+FmsYYfOK74J74eQhEPVIacc=;
        b=HDkGgjg3dVx8iwJBYbDMx8AftG6nTMeVBD2Etl7Lji9JcDBWwEh3CYBKzHwPB6y9Y33Vvd
        Ti37oopaVwIQTSkUqt6R7Cwkx+Thld9cKNUJFLRkoIYcm2krcpFqdYx+3EKRiglLQvx25d
        bTivJf/VIwzDfXspc0q9WuLUrXre49M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-460-MvXKLtxgOCKXkjX_gSKkhg-1; Thu, 16 Apr 2020 03:56:54 -0400
X-MC-Unique: MvXKLtxgOCKXkjX_gSKkhg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9252C8017F3;
        Thu, 16 Apr 2020 07:56:52 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-194.ams2.redhat.com
 [10.36.112.194])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0DD6F7E7C0;
        Thu, 16 Apr 2020 07:56:47 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Stephen Rothwell <sfr@canb.auug.org.au>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>, =?utf-8?q?Eugenio_P=C3=A9re?=
	=?utf-8?q?z?= <eperezma@redhat.com>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 kvm list <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [PATCH v2 0/8] tools/vhost: Reset virtqueue on tests
Date: Thu, 16 Apr 2020 09:56:35 +0200
Message-Id: <20200416075643.27330-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series add tests used to validate the "vhost: Reset batched
descriptors on SET_VRING_BASE call" series, with a few minor updates of
them.

They are based on the tests sent back them, the ones that were not
included (reasons in that thread). This series changes:

* Delete need to export the ugly function in virtio_ring, now all the
code is added in tools/virtio (except the one line fix).
* Add forgotten uses of vhost_vq_set_backend. Fix bad usage order in
vhost_test_set_backend.
* Drop random reset, not really needed.
* Minor changes.

This patchset commit messages contains references to commits under
"for_linus" tag and references to commits in for_linus..mst/vhost.
They are fixes, so probably it is better just to squash if possible:

("7c48601a3d4d tools/virtio: Add --reset=random"): Already in for_linus
("af3756cfed9a vhost: batching fetches"): Only in vhost branch, not in
for_linus.

Thanks!

Changes from v1:
* Different base, since branch was force-pushed.
* Using new vring_legacy_*, as base uses them now.

This serie is meant to be applied on top of
503b1b3efb47e267001beba8e0759c15fa3e9be7 in
git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git.

Eugenio Pérez (8):
  tools/virtio: fix virtio_test.c indentation
  vhost: Not cleaning batched descs in VHOST_SET_VRING_BASE ioctl
  vhost: Replace vq->private_data access by backend accesors
  vhost: Fix bad order in vhost_test_set_backend at enable
  tools/virtio: Use __vring_new_virtqueue in virtio_test.c
  tools/virtio: Extract virtqueue initialization in vq_reset
  tools/virtio: Reset index in virtio_test --reset.
  tools/virtio: Use tools/include/list.h instead of stubs

 drivers/vhost/test.c        |  8 ++---
 drivers/vhost/vhost.c       |  1 -
 tools/virtio/linux/kernel.h |  7 +----
 tools/virtio/linux/virtio.h |  5 ++--
 tools/virtio/virtio_test.c  | 58 +++++++++++++++++++++++++++----------
 tools/virtio/vringh_test.c  |  2 ++
 6 files changed, 51 insertions(+), 30 deletions(-)
```
#### [PATCH v2 0/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Thu Apr 16 08:38:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11492559
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BBE4112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 09:11:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8246B20784
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 09:11:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="cnL1v6V0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441438AbgDPIj2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 04:39:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38818 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2502679AbgDPIjE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 04:39:04 -0400
Received: from mail-wr1-x434.google.com (mail-wr1-x434.google.com
 [IPv6:2a00:1450:4864:20::434])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 05FA8C061A0C;
        Thu, 16 Apr 2020 01:39:03 -0700 (PDT)
Received: by mail-wr1-x434.google.com with SMTP id i10so3772092wrv.10;
        Thu, 16 Apr 2020 01:39:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xegz48JzyIZNPeJysw6oCGlOeYewFYMA4DWiAxaVcX4=;
        b=cnL1v6V0mAiUrW3HpV/SNZErA9/hfXwlD6+LKjoWASSYdeTwTi/CGEpGw8e2apDmlO
         oEDJUPBw2+uM2K/99VhpJc79CfeQMHrtOmGlYRiWXRPVfBwvqNlClQs+Q+wbnnu8qAXu
         rzMC8RFe+twveUeDz8NmhVh+wYhQAxEkqEpXPXNtdGsei+jze9RsCXNc9WFUCgKphDsq
         PJj2QbuXNtIhNt/KON/nyJCdxHUmUaDwEn3Vf9eUoh4cjDbqgBqbm6TPCmtwHkXWna86
         9PcqOyjXAxsd4YlCSklklOoDIQXRNf7fw67OX+h8BDVqchZUERYp7zr7GfysoDrbNZdh
         uGqA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xegz48JzyIZNPeJysw6oCGlOeYewFYMA4DWiAxaVcX4=;
        b=aRhGSliBGcPp0/DjfuMMDJxBZxoV6Kw+lH2+ztq++o6z9e1nKUohfW0HuG9bMWL36z
         vg2Qk0sx55ESftFni6lS3fXKU6fOSAKYhf8IrYDQevnGk01v+WRdJUvkODQXXROXvZYP
         tULucNQ7W77XcNWN6oiBg1NX/5VCUuo48HH/EqHuDpCLl689JhdLVvoTPIY+kL5Ch3aH
         2fZMRccggGtKXX+lGB8oCOLoInuPSpf6UkrgxpjabcuhImSldkQ6WjVvzCxVqGE505m+
         Lq2fiBapLjsCAddR3lS8/HlUzN3M/bqkB1qRbakguv+5UKlYsuNZHYDupyZ5LbRDW6qp
         7eLQ==
X-Gm-Message-State: AGi0PuZXS2lqFmKWkFcY7nv/mrIUQBYSPd4nmskZvHSnwNBdId84uiio
        RN4yhGCzY61LBKM1uXgW/NGs2Xz/nt63Jg==
X-Google-Smtp-Source: 
 APiQypLNCMBfbdp2NLlh1g2+MzQBltmBi7dDmCaJL/0QYAlJCtVNonYnhR5WDlSvOO7xFCPNcdWqbA==
X-Received: by 2002:adf:8563:: with SMTP id 90mr15614387wrh.202.1587026341881;
        Thu, 16 Apr 2020 01:39:01 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-55.inter.net.il. [84.229.155.55])
        by smtp.gmail.com with ESMTPSA id
 s12sm1256358wmc.7.2020.04.16.01.39.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 16 Apr 2020 01:39:01 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, rvkagan@yandex-team.ru,
        Jon Doron <arilou@gmail.com>
Subject: [PATCH v2 0/1] x86/kvm/hyper-v: Add support to SYNIC exit on EOM
Date: Thu, 16 Apr 2020 11:38:46 +0300
Message-Id: <20200416083847.1776387-1-arilou@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the TLFS:
"A write to the end of message (EOM) register by the guest causes the
hypervisor to scan the internal message buffer queue(s) associated with
the virtual processor.

If a message buffer queue contains a queued message buffer, the hypervisor
attempts to deliver the message.

Message delivery succeeds if the SIM page is enabled and the message slot
corresponding to the SINTx is empty (that is, the message type in the
header is set to HvMessageTypeNone).
If a message is successfully delivered, its corresponding internal message
buffer is dequeued and marked free.
If the corresponding SINTx is not masked, an edge-triggered interrupt is
delivered (that is, the corresponding bit in the IRR is set).

This register can be used by guests to poll for messages. It can also be
used as a way to drain the message queue for a SINTx that has
been disabled (that is, masked)."

So basically this means that we need to exit on EOM so the hypervisor
will have a chance to send all the pending messages regardless of the
SCONTROL mechnaisim.

v2:
Minor fixes from code review

Jon Doron (1):
  x86/kvm/hyper-v: Add support to SYNIC exit on EOM

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/hyperv.c           | 67 +++++++++++++++++++++++++++++----
 arch/x86/kvm/hyperv.h           |  1 +
 arch/x86/kvm/x86.c              |  5 +++
 include/uapi/linux/kvm.h        |  1 +
 5 files changed, 67 insertions(+), 8 deletions(-)
```
#### [RFC PATCH 0/3] kvm: x86: Cleanup and optimazation of switch_db_regs
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Thu Apr 16 10:15:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11492837
Return-Path: <SRS0=ZIlC=6A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A75F112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 11:46:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C9F021D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Apr 2020 11:46:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2506594AbgDPLqI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 07:46:08 -0400
Received: from mga01.intel.com ([192.55.52.88]:46605 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2505063AbgDPKd0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Apr 2020 06:33:26 -0400
IronPort-SDR: 
 qj6fw7nsAkLFIw6CQ46hLHVUHke4cwaqpbARTWcPrgHQ6cS4Qooqki5jwpsd1rcgSuQBFvZ6s/
 MP63fBKVMxBg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Apr 2020 03:33:25 -0700
IronPort-SDR: 
 vhzr2qoTpxKTwtiF8Qj7zuovZ5//O+5bjszfwZb2LMA9daDK6L8WDAMBSXR0wCXQTDZbkWfGnP
 LCfwj8KVclYw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,390,1580803200";
   d="scan'208";a="277947885"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.132])
  by fmsmga004.fm.intel.com with ESMTP; 16 Apr 2020 03:33:24 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: Nadav Amit <namit@cs.technion.ac.il>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [RFC PATCH 0/3] kvm: x86: Cleanup and optimazation of switch_db_regs
Date: Thu, 16 Apr 2020 18:15:06 +0800
Message-Id: <20200416101509.73526-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Through reading debug related codes in kvm/x86, I found the flags of
switch_db_regs is a little confusing (at least for me) and there is
something to improve. So this patchset comes. But it only go througg
compilation.

Xiaoyao Li (3):
  kvm: x86: Rename KVM_DEBUGREG_RELOAD to KVM_DEBUGREG_NEED_RELOAD
  kvm: x86: Use KVM_DEBUGREG_NEED_RELOAD instead of
    KVM_DEBUGREG_BP_ENABLED
  kvm: x86: skip DRn reload if previous VM exit is DR access VM exit

 arch/x86/include/asm/kvm_host.h |  3 +--
 arch/x86/kvm/svm/svm.c          |  8 +++++---
 arch/x86/kvm/vmx/vmx.c          |  8 +++++---
 arch/x86/kvm/x86.c              | 12 ++++++------
 4 files changed, 17 insertions(+), 14 deletions(-)
```
