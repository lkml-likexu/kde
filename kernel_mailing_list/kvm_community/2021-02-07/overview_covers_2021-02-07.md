

#### [PATCH RFC 0/7] Introduce support for guest AMX feature 
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
From patchwork Sun Feb  7 15:42:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 12072545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-9.8 required=3.0 tests=BAYES_00,DATE_IN_FUTURE_06_12,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E27F2C433DB
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 06:56:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9BC4164D79
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 06:56:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229566AbhBGG4b (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 7 Feb 2021 01:56:31 -0500
Received: from mga07.intel.com ([134.134.136.100]:48424 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229445AbhBGG4a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Feb 2021 01:56:30 -0500
IronPort-SDR: 
 7AK9qFJphzwfb5iSFouiXArgqM45X/5WlOqSKoJ64tYImGZC6ssNPwcUdcjJtCJi7+zGH553sR
 xLJ7TXMgL1jw==
X-IronPort-AV: E=McAfee;i="6000,8403,9887"; a="245660840"
X-IronPort-AV: E=Sophos;i="5.81,159,1610438400";
   d="scan'208";a="245660840"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Feb 2021 22:54:44 -0800
IronPort-SDR: 
 9+/d+qukDvKe2A1bJDWND5CPkHOlOcEkCKHAeY/AO3xY+r6Y5WzIE15Xx431jwwhrlMrUzK8ch
 WsYMWqo9TCtQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,159,1610438400";
   d="scan'208";a="410376570"
Received: from vmmteam.bj.intel.com ([10.240.193.86])
  by fmsmga004.fm.intel.com with ESMTP; 06 Feb 2021 22:54:41 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, jing2.liu@intel.com
Subject: [PATCH RFC 0/7] Introduce support for guest AMX feature 
Date: Sun,  7 Feb 2021 10:42:49 -0500
Message-Id: <20210207154256.52850-1-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.18.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel introduces Advanced Matrix Extensions (AMX) [1] feature that
will be shipping soon. AMX consists of configurable two-dimensional
"TILE" registers and new accelerator instructions that operate on them.
TMUL (Tile matrix MULtiply) is the first accelerator instruction set
to use the new registers.

Intel AMX is XSAVE supported and XSAVE enabled. It is associated with
two state components, XTILECFG and XTILEDATA. The XTILEDATA state
component is very large so an XSAVE extension called extended feature
disable (XFD) is introduced to support dynamic usage. When XFD is
enabled for a state component, any instruction that would access
that state component does not execute and instead generates an #NM.
So Linux kernel arms XFD to monitor the first usage of AMX.

This patchset adds AMX and XFD support for guest: providing related
CPUID and MSRs to guest, adding extended XSAVE state context switch and
XFD MSRs switch during vmenter/vmexit. 

This RFC series is based on kernel AMX series v3 [2] in LKML though not
latest upstream commit and we'd looking forward for your comments.

[1]: Intel Architecture Instruction Set Extension Programming Reference
    https://software.intel.com/content/dam/develop/external/us/en/documents/architecture-instruction-set-extensions-programming-reference.pdf

[2]: AMX kernel series v3 https://lkml.org/lkml/2020/12/23/464


Jing Liu (7):
  kvm: x86: Expose XFD CPUID to guest
  kvm: x86: Introduce XFD MSRs as passthrough to guest
  kvm: x86: Dynamic XSAVE and XFD MSRs context switch
  kvm: x86: Add new ioctls for XSAVE extension
  kvm: x86: Revise CPUID.D.1.EBX for alignment rule
  kvm: x86: Add AMX_TILE, AMX_INT8 and AMX_BF16 support
  kvm: x86: AMX XCR0 support for guest

 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/include/uapi/asm/kvm.h |   5 ++
 arch/x86/kernel/fpu/init.c      |   1 +
 arch/x86/kernel/fpu/xstate.c    |   2 +
 arch/x86/kvm/cpuid.c            |  19 +++-
 arch/x86/kvm/vmx/vmx.c          | 114 ++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |   7 +-
 arch/x86/kvm/x86.c              | 153 ++++++++++++++++++++++++++------
 include/uapi/linux/kvm.h        |   8 ++
 9 files changed, 279 insertions(+), 33 deletions(-)
```
#### [RFC PATCH v4 00/17] virtio/vsock: introduce SOCK_SEQPACKET support
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Sun Feb  7 15:12:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12072977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3313C433DB
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 15:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 773A664DE3
	for <kvm@archiver.kernel.org>; Sun,  7 Feb 2021 15:14:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229618AbhBGPOb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 7 Feb 2021 10:14:31 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:14957 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229562AbhBGPO0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 7 Feb 2021 10:14:26 -0500
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 1B40C521741;
        Sun,  7 Feb 2021 18:13:40 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1612710820;
        bh=ZaB5mtKxQQQyCaLSzaN6kEXZ6e9pIf4MS9KtjmwiYRo=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=S+btfsoo52RV/lzh4RxiHhZXk9EDvgkRkG0PmbsmEuK/1MhnYVQ1ygJwPBFe9NiTo
         xGzSPIMwCuC+0EidXW1D6grZNGNF7EVKFpvH6GmAZFNyk6dVVo4455aaQREnYV5/e5
         hKd+5MtHa4IMh+V1gFIDN8UE8NPRYo9hs9N3De+E=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 1982752173B;
        Sun,  7 Feb 2021 18:13:39 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.64.121) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Sun, 7 Feb
 2021 18:13:38 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Colin Ian King <colin.king@canonical.com>,
        Alexander Popov <alex.popov@linux.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v4 00/17] virtio/vsock: introduce SOCK_SEQPACKET support
Date: Sun, 7 Feb 2021 18:12:56 +0300
Message-ID: <20210207151259.803917-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.64.121]
X-ClientProxiedBy: hqmailmbx3.avp.ru (10.64.67.243) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 02/06/2021 23:52:08
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 161679 [Feb 06 2021]
X-KSE-AntiSpam-Info: LuaCore: 422 422 763e61bea9fcfcd94e075081cb96e065bc0509b4
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 02/06/2021 23:55:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 2/6/2021 9:17:00 PM
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/02/07 14:21:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/02/07 10:49:00 #16133380
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset impelements support of SOCK_SEQPACKET for virtio
transport.
	As SOCK_SEQPACKET guarantees to save record boundaries, so to
do it, two new packet operations were added: first for start of record
 and second to mark end of record(SEQ_BEGIN and SEQ_END later). Also,
both operations carries metadata - to maintain boundaries and payload
integrity. Metadata is introduced by adding special header with two
fields - message count and message length:

	struct virtio_vsock_seq_hdr {
		__le32  msg_cnt;
		__le32  msg_len;
	} __attribute__((packed));

	This header is transmitted as payload of SEQ_BEGIN and SEQ_END
packets(buffer of second virtio descriptor in chain) in the same way as
data transmitted in RW packets. Payload was chosen as buffer for this
header to avoid touching first virtio buffer which carries header of
packet, because someone could check that size of this buffer is equal
to size of packet header. To send record, packet with start marker is
sent first(it's header contains length of record and counter), then
counter is incremented and all data is sent as usual 'RW' packets and
finally SEQ_END is sent(it also carries counter of message, which is
counter of SEQ_BEGIN + 1), also after sedning SEQ_END counter is
incremented again. On receiver's side, length of record is known from
packet with start record marker. To check that no packets were dropped
by transport, counters of two sequential SEQ_BEGIN and SEQ_END are
checked(counter of SEQ_END must be bigger that counter of SEQ_BEGIN by
1) and length of data between two markers is compared to length in
SEQ_BEGIN header.
	Now as  packets of one socket are not reordered neither on
vsock nor on vhost transport layers, such markers allows to restore
original record on receiver's side. If user's buffer is smaller that
record length, when all out of size data is dropped.
	Maximum length of datagram is not limited as in stream socket,
because same credit logic is used. Difference with stream socket is
that user is not woken up until whole record is received or error
occurred. Implementation also supports 'MSG_EOR' and 'MSG_TRUNC' flags.
	Tests also implemented.

 Arseny Krasnov (17):
  af_vsock: update functions for connectible socket
  af_vsock: separate wait data loop
  af_vsock: separate receive data loop
  af_vsock: implement SEQPACKET receive loop
  af_vsock: separate wait space loop
  af_vsock: implement send logic for SEQPACKET
  af_vsock: rest of SEQPACKET support
  af_vsock: update comments for stream sockets
  virtio/vsock: dequeue callback for SOCK_SEQPACKET
  virtio/vsock: fetch length for SEQPACKET record
  virtio/vsock: add SEQPACKET receive logic
  virtio/vsock: rest of SOCK_SEQPACKET support
  virtio/vsock: setup SEQPACKET ops for transport
  vhost/vsock: setup SEQPACKET ops for transport
  vsock_test: add SOCK_SEQPACKET tests
  loopback/vsock: setup SEQPACKET ops for transport
  virtio/vsock: simplify credit update function API

 drivers/vhost/vsock.c                   |   8 +-
 include/linux/virtio_vsock.h            |  15 +
 include/net/af_vsock.h                  |   9 +
 include/uapi/linux/virtio_vsock.h       |  16 +
 net/vmw_vsock/af_vsock.c                | 588 +++++++++++++++-------
 net/vmw_vsock/virtio_transport.c        |   5 +
 net/vmw_vsock/virtio_transport_common.c | 316 ++++++++++--
 net/vmw_vsock/vsock_loopback.c          |   5 +
 tools/testing/vsock/util.c              |  32 +-
 tools/testing/vsock/util.h              |   3 +
 tools/testing/vsock/vsock_test.c        | 126 +++++
 11 files changed, 895 insertions(+), 228 deletions(-)

 TODO:
 - What to do, when server doesn't support SOCK_SEQPACKET. In current
   implementation RST is replied in the same way when listening port
   is not found. I think that current RST is enough,because case when
   server doesn't support SEQ_PACKET is same when listener missed(e.g.
   no listener in both cases).

 v3 -> v4:
 - callbacks for loopback transport
 - SEQPACKET specific metadata moved from packet header to payload
   and called 'virtio_vsock_seq_hdr'
 - record integrity check:
   1) SEQ_END operation was added, which marks end of record.
   2) Both SEQ_BEGIN and SEQ_END carries counter which is incremented
      on every marker send.
 - af_vsock.c: socket operations for STREAM and SEQPACKET call same
   functions instead of having own "gates" differs only by names:
   'vsock_seqpacket/stream_getsockopt()' now replaced with
   'vsock_connectible_getsockopt()'.
 - af_vsock.c: 'seqpacket_dequeue' callback returns error and flag that
   record ready. There is no need to return number of copied bytes,
   because case when record received successfully is checked at virtio
   transport layer, when SEQ_END is processed. Also user doesn't need
   number of copied bytes, because 'recv()' from SEQPACKET could return
   error, length of users's buffer or length of whole record(both are
   known in af_vsock.c).
 - af_vsock.c: both wait loops in af_vsock.c(for data and space) moved
   to separate functions because now both called from several places.
 - af_vsock.c: 'vsock_assign_transport()' checks that 'new_transport'
   pointer is not NULL and returns 'ESOCKTNOSUPPORT' instead of 'ENODEV'
   if failed to use transport.
 - tools/testing/vsock/vsock_test.c: rename tests

 v2 -> v3:
 - patches reorganized: split for prepare and implementation patches
 - local variables are declared in "Reverse Christmas tree" manner
 - virtio_transport_common.c: valid leXX_to_cpu() for vsock header
   fields access
 - af_vsock.c: 'vsock_connectible_*sockopt()' added as shared code
   between stream and seqpacket sockets.
 - af_vsock.c: loops in '__vsock_*_recvmsg()' refactored.
 - af_vsock.c: 'vsock_wait_data()' refactored.

 v1 -> v2:
 - patches reordered: af_vsock.c related changes now before virtio vsock
 - patches reorganized: more small patches, where +/- are not mixed
 - tests for SOCK_SEQPACKET added
 - all commit messages updated
 - af_vsock.c: 'vsock_pre_recv_check()' inlined to
   'vsock_connectible_recvmsg()'
 - af_vsock.c: 'vsock_assign_transport()' returns ENODEV if transport
   was not found
 - virtio_transport_common.c: transport callback for seqpacket dequeue
 - virtio_transport_common.c: simplified
   'virtio_transport_recv_connected()'
 - virtio_transport_common.c: send reset on socket and packet type
			      mismatch.
```
