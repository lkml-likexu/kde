#### [PATCH 1/3] vsock/virtio: support for SOCK_SEQPACKET socket.
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 11992185
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 573A9C433E6
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 11:14:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2104620867
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 11:14:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726061AbgL2LNk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 29 Dec 2020 06:13:40 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:39609 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725866AbgL2LNk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Dec 2020 06:13:40 -0500
X-Greylist: delayed 434 seconds by postgrey-1.27 at vger.kernel.org;
 Tue, 29 Dec 2020 06:13:30 EST
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 4A167521328;
        Tue, 29 Dec 2020 14:05:34 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1609239934;
        bh=BPFcWUbu7Y3VPClFuN6RbAoZk3twKs6blUFKiJGS2/Y=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=Q/OdTb0KEvf2VQTeFVCfPgp8EndYSQHzJAszPDGQnLK77aaUhlxrkpXhF6ZuPiyKh
         DP8IhS1BXE17f/sq+KD8+/OpfDQRdY2EGqPhQYv9bSRFhMy2pNhLe+qTAQuzFxQEHm
         evDfjmxRymdIBU/cpd8WlNhHZk6HE9aoitGH89uw=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 8595652137D;
        Tue, 29 Dec 2020 14:05:33 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.129) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Tue, 29
 Dec 2020 14:05:32 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>
CC: <arseny.krasnov@kaspersky.com>,
        <virtualization@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH 1/3] vsock/virtio: support for SOCK_SEQPACKET socket.
Date: Tue, 29 Dec 2020 14:04:51 +0300
Message-ID: <20201229110452.274598-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.68.129]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 12/29/2020 10:50:58
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 160932 [Dec 29 2020]
X-KSE-AntiSpam-Info: LuaCore: 419 419 70b0c720f8ddd656e5f4eb4a4449cf8ce400df94
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 arseniy-pc.avp.ru:7.1.1;d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;kaspersky.com:7.1.1;127.0.0.199:7.1.2
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 12/29/2020 10:54:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 29.12.2020 9:12:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2020/12/29 10:34:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2020/12/29 09:12:00 #15977073
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To preserve message boundaries, new packet operation was added:
to mark start of record(with record length in header). To send record,
packet with start marker is sent first, then all data is transmitted as
'RW' packets.
        On receiver's side, length of record is known from packet with
start record marker. Now as  packets of one socket are not reordered
neither on vsock nor on vhost transport layers, these marker allow to
restore original record on receiver's side. When each 'RW' packet is
inserted to rx queue of receiver, user is woken up, data is copied to
user's buffer and credit update message is sent. If there is no user
waiting for data, credit won't be updated and sender will wait. Also,
if user's buffer is full, and record is bigger, all unneeded data will
be dropped(with credit update message).
	'MSG_EOR' flag is implemented with special value of 'flags'
field in packet header. When record is received with such flags,
'MSG_EOR' is set in 'recvmsg()' flags.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
---
 include/linux/virtio_vsock.h            |   7 +
 include/net/af_vsock.h                  |   4 +
 include/uapi/linux/virtio_vsock.h       |   9 +
 net/vmw_vsock/virtio_transport.c        |   3 +
 net/vmw_vsock/virtio_transport_common.c | 323 +++++++++++++++++++++---
 5 files changed, 305 insertions(+), 41 deletions(-)

```
#### [RFC 1/2] KVM: add initial support for KVM_SET_IOREGION
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 11992167
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5AA6EC433DB
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 10:10:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 19E53207BD
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 10:10:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726029AbgL2KJq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 29 Dec 2020 05:09:46 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46614 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725964AbgL2KJp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Dec 2020 05:09:45 -0500
Received: from mail-lf1-x131.google.com (mail-lf1-x131.google.com
 [IPv6:2a00:1450:4864:20::131])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B0543C0613D6
        for <kvm@vger.kernel.org>; Tue, 29 Dec 2020 02:09:04 -0800 (PST)
Received: by mail-lf1-x131.google.com with SMTP id h22so29767321lfu.2
        for <kvm@vger.kernel.org>; Tue, 29 Dec 2020 02:09:04 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=QMr7Y4pocQ02SfzVgMfLIYk7XhKNF3mLOqcY9N6asSw=;
        b=itD/4mYc2Ed03uN+7eAJ39cWXJo5K3AP1pTGhagF8fD7bD8uVlSlbRKvkpo2xR774r
         Qo/TUUe4hhW+sXNZCd47ZTAw9TECQEOSDoYYXiX1qWwWkzfdKyTdr1gwaWaZ+ZSVgAEH
         VwbxQZoQELAU6iUcpBYlSeSjE6bKhdoyiMy/zquaQqa8SJ6lNaAgPMBNerrwTAx1lnWK
         nHYeNsC2vFtHvQqK/MSlQiyz5McaV/IUybHFT/7IdDujFIkCHkcYfbFxsunJfgBTAck/
         wOJgPO7MRcu2NH0liHkzjuSMPW0E90I9SYDHbCyaY36uRRYlO669GwDvJo8tkqXv9/vd
         Br5w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=QMr7Y4pocQ02SfzVgMfLIYk7XhKNF3mLOqcY9N6asSw=;
        b=NBvIVR+JHa4arTASK8s2b/tJg2/Ynx3JVEDvDaFnku2ef/Y4GwaVHXzR+w6yHiLEDp
         XSOG0L58Lt8/AwXTTbUlsMNelm6+2icK7xV/rHSaJD4VwuCnq3VZZabQU53t8iAalBiU
         L0GZ5R/qj0vlV4GeE5HIyTDrkgPzPbU1UGw8TUgabqO/Dc1HrEsnSv3oQFl/QVuiPjik
         gtGB/8Dy43hM2cHO2fEpNoJnWYayY/6mSxKhHHGXZDhcAzDHR6pV26yRX/mrWSGOlb9F
         tXqqRwMqznmGHdaStm8AFVyoLxtOalPmlwdc9+9HlOg2hLanYpdTN2PuWa62yhpi6iHz
         Qm/Q==
X-Gm-Message-State: AOAM532WET2K174VApELmr3rb6xjZ6t5/OZEkv6K8x2DL/ODEwv8+RDf
        aip9cKLw55BQTFcwAxiPKVwFdm4X/UGSFUNE
X-Google-Smtp-Source: 
 ABdhPJz3CUFYNKHhk9BOCqTnmAaev0Dp1e2PyleM6we7if45ggnLMJCdabdUIeeR9vGqicbLhVmYKQ==
X-Received: by 2002:a2e:89ce:: with SMTP id
 c14mr22824980ljk.483.1609236542720;
        Tue, 29 Dec 2020 02:09:02 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 y13sm5612901lfg.189.2020.12.29.02.09.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 29 Dec 2020 02:09:02 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC 1/2] KVM: add initial support for KVM_SET_IOREGION
Date: Tue, 29 Dec 2020 13:02:43 +0300
Message-Id: 
 <d4af2bcbd2c6931a24ba99236248529c3bfb6999.1609231374.git.eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1609231373.git.eafanasova@gmail.com>
References: <cover.1609231373.git.eafanasova@gmail.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This vm ioctl adds or removes an ioregionfd MMIO/PIO region. Guest
read and write accesses are dispatched through the given ioregionfd
instead of returning from ioctl(KVM_RUN). Regions can be deleted by
setting fds to -1.

Signed-off-by: Elena Afanasova <eafanasova@gmail.com>
---
 arch/x86/kvm/Kconfig     |   1 +
 arch/x86/kvm/Makefile    |   1 +
 arch/x86/kvm/x86.c       |   1 +
 include/linux/kvm_host.h |  17 +++
 include/uapi/linux/kvm.h |  23 ++++
 virt/kvm/Kconfig         |   3 +
 virt/kvm/eventfd.c       |  25 +++++
 virt/kvm/eventfd.h       |  14 +++
 virt/kvm/ioregion.c      | 233 +++++++++++++++++++++++++++++++++++++++
 virt/kvm/ioregion.h      |  15 +++
 virt/kvm/kvm_main.c      |  20 +++-
 11 files changed, 350 insertions(+), 3 deletions(-)
 create mode 100644 virt/kvm/eventfd.h
 create mode 100644 virt/kvm/ioregion.c
 create mode 100644 virt/kvm/ioregion.h

```
#### [PATCH] KVM: x86/pmu: Fix UBSAN shift-out-of-bounds warning in intel_pmu_refresh()
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11992037
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3937CC433E0
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 07:19:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F2C72220F
	for <kvm@archiver.kernel.org>; Tue, 29 Dec 2020 07:19:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726173AbgL2HTK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 29 Dec 2020 02:19:10 -0500
Received: from mga04.intel.com ([192.55.52.120]:11855 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725767AbgL2HTK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Dec 2020 02:19:10 -0500
IronPort-SDR: 
 kJgi/DFXkXKTzu65gduZgNlOhGsHoRACROFXvp8dLh9jbqwt2sHuMZEmIiO69tPaiyK7UbjWAN
 Bob+yjabg4dQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9848"; a="173888152"
X-IronPort-AV: E=Sophos;i="5.78,457,1599548400";
   d="scan'208";a="173888152"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Dec 2020 23:17:25 -0800
IronPort-SDR: 
 QKCKIStYkeNmfJgKwwFY1lbNsImWFJP+blXuQKbjL2cbTrl2SQEqqYBlWswOBNA1LnXwYwDFyL
 u5/2oMz8bZjg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,457,1599548400";
   d="scan'208";a="347286495"
Received: from unknown (HELO clx-ap-likexu.sh.intel.com) ([10.239.48.105])
  by fmsmga008.fm.intel.com with ESMTP; 28 Dec 2020 23:17:23 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: syzkaller-bugs@googlegroups.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/pmu: Fix UBSAN shift-out-of-bounds warning in
 intel_pmu_refresh()
Date: Tue, 29 Dec 2020 15:11:44 +0800
Message-Id: <20201229071144.85418-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since we know vPMU will not work properly when the guest bit_width(s) of
the [gp|fixed] counters are greater than the host ones, so we can setup a
smaller left shift value and refresh the guest pmu cpuid entry, thus fixing
the following UBSAN shift-out-of-bounds warning:

shift exponent 197 is too large for 64-bit type 'long long unsigned int'

Call Trace:
 __dump_stack lib/dump_stack.c:79 [inline]
 dump_stack+0x107/0x163 lib/dump_stack.c:120
 ubsan_epilogue+0xb/0x5a lib/ubsan.c:148
 __ubsan_handle_shift_out_of_bounds.cold+0xb1/0x181 lib/ubsan.c:395
 intel_pmu_refresh.cold+0x75/0x99 arch/x86/kvm/vmx/pmu_intel.c:348
 kvm_vcpu_after_set_cpuid+0x65a/0xf80 arch/x86/kvm/cpuid.c:177
 kvm_vcpu_ioctl_set_cpuid2+0x160/0x440 arch/x86/kvm/cpuid.c:308
 kvm_arch_vcpu_ioctl+0x11b6/0x2d70 arch/x86/kvm/x86.c:4709
 kvm_vcpu_ioctl+0x7b9/0xdb0 arch/x86/kvm/../../../virt/kvm/kvm_main.c:3386
 vfs_ioctl fs/ioctl.c:48 [inline]
 __do_sys_ioctl fs/ioctl.c:753 [inline]
 __se_sys_ioctl fs/ioctl.c:739 [inline]
 __x64_sys_ioctl+0x193/0x200 fs/ioctl.c:739
 do_syscall_64+0x2d/0x70 arch/x86/entry/common.c:46
 entry_SYSCALL_64_after_hwframe+0x44/0xa9

Reported-by: syzbot+ae488dc136a4cc6ba32b@syzkaller.appspotmail.com
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 3 +++
 1 file changed, 3 insertions(+)

```
