

#### [PATCH 0/5] virtio/vsock: introduce SOCK_SEQPACKET support.
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Sun Jan  3 19:54:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 11995883
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D817C433DB
	for <kvm@archiver.kernel.org>; Sun,  3 Jan 2021 19:56:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C88A720B1F
	for <kvm@archiver.kernel.org>; Sun,  3 Jan 2021 19:56:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727180AbhACT4R (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 3 Jan 2021 14:56:17 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:13324 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725889AbhACT4Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 3 Jan 2021 14:56:16 -0500
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 5C1E55212AD;
        Sun,  3 Jan 2021 22:55:32 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1609703732;
        bh=wyaj2NkC6p89cfaO82BPGLPhVCBSFLTGN/jpX6R+zpg=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=V0WcAnczQgR9yZKK31UhIk2E3bW772wX3clSHrrX9u92EJBdbcx25CfV9bvkbZO3e
         dj3RhTtgaHnQGs0jcoKJX3G5bGQpH8DmZ5t3Bs1iH8hfqWrIxuE2970I26+6Y+dPYy
         89ihfYjQqbqQ2/fy/BZQcHAOHV0mP8Pmm0u6sJ5g=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 91E695212A2;
        Sun,  3 Jan 2021 22:55:31 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.128) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Sun, 3 Jan
 2021 22:55:30 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Colin Ian King <colin.king@canonical.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Arseniy Krasnov <oxffffaa@gmail.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Jeff Vander Stoep <jeffv@google.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <arseny.krasnov@kaspersky.com>
Subject: [PATCH 0/5] virtio/vsock: introduce SOCK_SEQPACKET support.
Date: Sun, 3 Jan 2021 22:54:52 +0300
Message-ID: <20210103195454.1954169-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.68.128]
X-ClientProxiedBy: hqmailmbx3.avp.ru (10.64.67.243) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 01/03/2021 19:44:23
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 160977 [Jan 03 2021]
X-KSE-AntiSpam-Info: LuaCore: 419 419 70b0c720f8ddd656e5f4eb4a4449cf8ce400df94
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, dbl_space}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;arseniy-pc.avp.ru:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 01/03/2021 19:46:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 03.01.2021 17:14:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/01/03 18:58:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/01/03 18:13:00 #16005632
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As SOCK_SEQPACKET guarantees to save record boundaries, so to
do it, new packet operation was added: it marks start of record (with
record length in header). To send record, packet with start marker is
sent first, then all data is transmitted as 'RW' packets. On receiver's
side, length of record is known from packet with start record marker.
Now as  packets of one socket are not reordered neither on vsock nor on
vhost transport layers, these marker allows to restore original record
on receiver's side. When each 'RW' packet is inserted to rx queue of
receiver, user is woken up, data is copied to user's buffer and credit
update message is sent. If there is no user waiting for data, credit
won't be updated and sender will wait. Also,  if user's buffer is full,
and record is bigger, all unneeded data will be dropped (with sending of
credit update message).
	'MSG_EOR' flag is implemented with special value of 'flags' field
in packet header. When record is received with such flags, 'MSG_EOR' is
set in 'recvmsg()' flags. 'MSG_TRUNC' flag is also supported.
	In this implementation maximum length of datagram is not limited
as in stream socket.

 drivers/vhost/vsock.c                   |   6 +-
 include/linux/virtio_vsock.h            |   7 +
 include/net/af_vsock.h                  |   4 +
 include/uapi/linux/virtio_vsock.h       |   9 +
 net/vmw_vsock/af_vsock.c                | 457 +++++++++++++++++++-----
 net/vmw_vsock/virtio_transport.c        |   3 +
 net/vmw_vsock/virtio_transport_common.c | 323 ++++++++++++++---
 7 files changed, 673 insertions(+), 136 deletions(-)
```
