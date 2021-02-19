

#### [kvm-unit-tests PATCH 0/6] x86: nVMX: Unrestricted guest fix and
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Feb 18 00:22:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12092709
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 21624C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 00:23:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C70CF64E4B
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 00:23:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230021AbhBRAW6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 19:22:58 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34530 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230018AbhBRAW5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 19:22:57 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 69B37C061756
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 16:22:17 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id j4so569520ybt.23
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 16:22:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=IZw0ECVBlM9vyeDxDPM3cu3JxE36bgau1ZklK6oBKCM=;
        b=o//q+l0doxtqMPGEFqL/aFoXZ+/AZTyaoBBzkVBU48AKiEljEvZdMOQPZflMHfhxs6
         mVYP90gDcAUKdcknXIysP5uBenkZyzcDznZ6fN56LEWVgOW8gfpQlkyHP/co5Fc/+t8b
         T17ohirUpvdodKqqQOkTZ7Kk6Nd9jDN211M7zKy94fPRNombhl1QlwIiwG7y3v5Mz4qx
         EIRg/bCW+hDaQMU9vktK3PFCnZaTL1R8g2aY+6ka2KFRLt78xJH4jnFjtOA0HCJwyIFV
         1DJsvmO0rj9YutDoyoKfquzC5tF1mhXa8uNHBlS6qlpsFxvNGMEvLoy2K1dsxgWS+0IW
         qzOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=IZw0ECVBlM9vyeDxDPM3cu3JxE36bgau1ZklK6oBKCM=;
        b=SrBjvSOIbhe76YtWU9Jy0ssttPpEuXuuXtsRXMUUxGf6gOmeVRyRhhmJ2+iR2IlOeU
         SD9GE72Za+vxxidTL9o4MSMKiRAb6gmFhwmK2OSE0gH5BOwSWY70X8Qcmer2k3uBHPEs
         QThV56U+inw0Zz/1AJFZLLFVPNfNZ6atE18beqP6uFOftNDqqs2FUHjnkcUJijhDNQND
         OIAIM3l652fXa0JVmGpLUmkoVrtwWhI4QWPNX47k/OOG7QKZwrHoVYXLx6ASE8pMJH7S
         DtADakoAqd1UUktBhRYIx3rgZoYKK6uInmQvdQbpYamZjJyDDBedDomvuO1yXWHxhar0
         UTow==
X-Gm-Message-State: AOAM532Lk4OAVmTJlRyGb8TIOd5jli7S3UU+N5HDHsAU7AWfN7vkIJxb
        yzq6s+doqgpM22ttmH/AZbdR6z5/Bzs=
X-Google-Smtp-Source: 
 ABdhPJyuXxO6IJnmRblKWvsaOLykVraSs3serv70iFI92zddcWDm6sHWUmPMNzmuf/8vDSc6NXkpeNIq2KE=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:dc76:757f:9e9e:647c])
 (user=seanjc job=sendgmr) by 2002:a25:4a84:: with SMTP id
 x126mr2878599yba.408.1613607736656;
 Wed, 17 Feb 2021 16:22:16 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 17 Feb 2021 16:22:06 -0800
Message-Id: <20210218002212.2904647-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [kvm-unit-tests PATCH 0/6] x86: nVMX: Unrestricted guest fix and
 cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two fixes to skip (sub)tests that rely on unrestricted guest if URG isn't
supported, clean ups for related code to make triaging test failures a bit
easier. Ideally, even more info would be provided on failure, e.g. line
number, but that'd best be done as a (much) larger overhaul.

Sean Christopherson (6):
  x86: nVMX: Verify unrestricted guest is supported in segment tests
  x86: nVMX: Skip unrestricted guest (URG) test if URG isn't supported
  x86: nVMX: Improve report messages for segment selector tests
  x86: nVMX: Improve report messages for segment base tests
  x86: nVMX: Use more descriptive name for GDT/IDT limit tests
  x86: nVMX: Add an equals sign to show value assoc. in
    test_guest_state()

 x86/vmx_tests.c | 157 ++++++++++++++++++++++++------------------------
 1 file changed, 77 insertions(+), 80 deletions(-)
```
#### [RFC PATCH v5 00/19] virtio/vsock: introduce SOCK_SEQPACKET support
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Thu Feb 18 05:33:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12093143
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88547C433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 05:39:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2592C64E2E
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 05:39:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230412AbhBRFj3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 00:39:29 -0500
Received: from mx12.kaspersky-labs.com ([91.103.66.155]:46210 "EHLO
        mx12.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230403AbhBRFgC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 00:36:02 -0500
Received: from relay12.kaspersky-labs.com (unknown [127.0.0.10])
        by relay12.kaspersky-labs.com (Postfix) with ESMTP id 7190176173;
        Thu, 18 Feb 2021 08:34:38 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1613626478;
        bh=zjQ51jZUXzvMR8EhkOqDJtP7sC5BHnc4cQiyLmNBRIM=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=y+t4dZyo1n9g/Rw4Eid6NcD1wc14+1AM5WjZx7TPbmeBH1Dyvrx4U2KKO3OPlGlJB
         DeZleAy9t692BW//5VroKP+Bn41XskvPeGqFjnr/GmnKwzngJIXdbVJe9v61VTZH/E
         SBrrBhTcF52X7iWut9R+WcMLC0MKF+5XLwuNMeS3HlJZnF9y1kA5EUlL+I7oE/giZ5
         Q+r8GhS0H41rHvbCMHwdkr5vRB64GNU++TGoaQm0MhHCynvga49FXTF1+sbZ35ApUt
         HNqYkjYd4GfyAx3C3tP1haqGx6C+ciVasTbKcs8uk7rcdOiJljjGsLFxGVUw1kb4CI
         EUEb1V/b+yFGA==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub12.kaspersky-labs.com (Postfix) with ESMTPS id 8A56975E85;
        Thu, 18 Feb 2021 08:34:37 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.128) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Thu, 18
 Feb 2021 08:34:16 +0300
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
        Norbert Slusarek <nslusarek@gmx.net>,
        Colin Ian King <colin.king@canonical.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v5 00/19] virtio/vsock: introduce SOCK_SEQPACKET support
Date: Thu, 18 Feb 2021 08:33:44 +0300
Message-ID: <20210218053347.1066159-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.68.128]
X-ClientProxiedBy: hqmailmbx1.avp.ru (10.64.67.241) To hqmailmbx3.avp.ru
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
X-KSE-Antivirus-Info: Clean, bases: 06.02.2021 21:17:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/02/18 04:08:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/02/18 04:31:00 #16269527
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

 Arseny Krasnov (19):
  af_vsock: update functions for connectible socket
  af_vsock: separate wait data loop
  af_vsock: separate receive data loop
  af_vsock: implement SEQPACKET receive loop
  af_vsock: separate wait space loop
  af_vsock: implement send logic for SEQPACKET
  af_vsock: rest of SEQPACKET support
  af_vsock: update comments for stream sockets
  virtio/vsock: set packet's type in send
  virtio/vsock: simplify credit update function API
  virtio/vsock: dequeue callback for SOCK_SEQPACKET
  virtio/vsock: fetch length for SEQPACKET record
  virtio/vsock: add SEQPACKET receive logic
  virtio/vsock: rest of SOCK_SEQPACKET support
  virtio/vsock: setup SEQPACKET ops for transport
  vhost/vsock: setup SEQPACKET ops for transport
  vsock/loopback: setup SEQPACKET ops for transport
  vsock_test: add SOCK_SEQPACKET tests
  virtio/vsock: update trace event for SEQPACKET

 drivers/vhost/vsock.c                        |   8 +-
 include/linux/virtio_vsock.h                 |  14 +
 include/net/af_vsock.h                       |   9 +
 .../events/vsock_virtio_transport_common.h   |  48 +-
 include/uapi/linux/virtio_vsock.h            |  16 +
 net/vmw_vsock/af_vsock.c                     | 590 +++++++++++------
 net/vmw_vsock/virtio_transport.c             |   5 +
 net/vmw_vsock/virtio_transport_common.c      | 342 ++++++++--
 net/vmw_vsock/vsock_loopback.c               |   5 +
 tools/testing/vsock/util.c                   |  32 +-
 tools/testing/vsock/util.h                   |   3 +
 tools/testing/vsock/vsock_test.c             | 126 ++++
 12 files changed, 951 insertions(+), 247 deletions(-)

 v4 -> v5:
 - patches reorganized:
   1) Setting of packet's type in 'virtio_transport_send_pkt_info()'
      is moved to separate patch.
   2) Simplifying of 'virtio_transport_send_credit_update()' is
      moved to separate patch and before main virtio/vsock patches.
 - style problem fixed
 - in 'af_vsock: separate receive data loop' extra 'release_sock()'
   removed
 - added trace event fields for SEQPACKET
 - in 'af_vsock: separate wait data loop':
   1) 'vsock_wait_data()' removed 'goto out;'
   2) Comment for invalid data amount is changed.
 - in 'af_vsock: rest of SEQPACKET support', 'new_transport' pointer
   check is moved after 'try_module_get()'
 - in 'af_vsock: update comments for stream sockets', 'connect-oriented'
   replaced with 'connection-oriented'
 - in 'loopback/vsock: setup SEQPACKET ops for transport',
   'loopback/vsock' replaced with 'vsock/loopback'

 v3 -> v4:
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

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
```
#### [kvm-unit-tests PATCH v3 0/5] CSS Mesurement Block
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Feb 18 17:26:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12093847
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EBB36C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:30:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A11BE64E76
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:30:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231259AbhBRSaG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 13:30:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:36822 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232578AbhBRR1o (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 12:27:44 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHLk3r091642
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=w+dV+TFFLs0rNFFqR7W1VBHLOA/FfMn9YTisvNm65Os=;
 b=qwVeKl5Fgfv49+xQN2TR8RzJwqC50eS/rM+7FJLtM7W3+ZhUdE/3mu0actIkX32dx1ob
 P3/pDmm1Zzsm+9ojrhGefdwzBuRB4TaujVKENCeMxlbKidChGJ1G4qVkPJkdxMRr4c4G
 0o/C7cQC+uXA3yM6xqaCo0G2WagRaJ3aTNVQtl/zJaOvb06fqxi9UxvDSyd+nfg/3mbo
 bFVc7jLaUYgx2yYjfatBZ3IPDbz0imM67Y6kraFJL6fECX2W7iD2IepQoNnhFPfjvPZe
 uKjJjy8hYeRipm9qtaB0xp3RISrmRZz+pKoY5JeAONXpJYfnJ8YykZwxjFBNIbtf6VU2 cA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36suuc9gdv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:51 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11IHMQHs093200
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:26:50 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36suuc9gd6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 12:26:50 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHNmoN011291;
        Thu, 18 Feb 2021 17:26:49 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 36p6d8cvkr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 17:26:48 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11IHQk2s44433822
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 17:26:46 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 10758A4051;
        Thu, 18 Feb 2021 17:26:46 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B6241A404D;
        Thu, 18 Feb 2021 17:26:45 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.94.58])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Feb 2021 17:26:45 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 0/5] CSS Mesurement Block
Date: Thu, 18 Feb 2021 18:26:39 +0100
Message-Id: <1613669204-6464-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-18_08:2021-02-18,2021-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 clxscore=1015
 impostorscore=0 adultscore=0 priorityscore=1501 malwarescore=0
 lowpriorityscore=0 mlxscore=0 suspectscore=0 bulkscore=0 phishscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102180144
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We tests the update of the Mesurement Block (MB) format 0
and format 1 using a serie of senseid requests.

The MB format 1 is only provided if the Extended mesurement Block
feature is available.
This feature is exposed by the CSS characteristics general features
stored by the Store Channel Subsystem Characteristics CHSC command,
consequently, we implement the CHSC instruction call and the SCSC CHSC
command.

In order to ease the writing of new tests using:
- interrupt
- enablement of a subchannel
- multiple I/O on a subchannel

We do the following simplifications:
- we create a CSS initialization routine
- we register the I/O interrupt handler on CSS initialization
- we do not enable or disable a subchannel in the senseid test,
  assuming this test is done after the enable test, this allows
  to create traffic using the SSCH used by senseid.
- we add a css_enabled() function to test if a subchannel is enabled.

Regards,
Pierre

Pierre Morel (5):
  s390x: css: Store CSS Characteristics
  s390x: css: simplifications of the tests
  s390x: css: implementing Set CHannel Monitor
  s390x: css: testing measurement block format 0
  s390x: css: testing measurement block format 1

 lib/s390x/css.h     | 117 ++++++++++++++++++-
 lib/s390x/css_lib.c | 270 ++++++++++++++++++++++++++++++++++++++++++--
 s390x/css.c         | 214 +++++++++++++++++++++++++++++++----
 3 files changed, 568 insertions(+), 33 deletions(-)
```
#### [PATCH 0/1] css: SCHIB measurement block origin must be aligned
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Feb 18 17:33:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12093865
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B8C0DC433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:33:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6CD6E64EB8
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 18:33:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232452AbhBRScz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 13:32:55 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3132 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232130AbhBRRfC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Feb 2021 12:35:02 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHXxuV040499
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:34:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=fDmQsUKDrixNuqYATDnYtFrn46IuoVoX+WWxwtWfPJw=;
 b=bxtZ7akh5tGIjn2g1d/VVeJRbtIWJ02CBcsUUG21Nue3J6dSM76sB5hdA0UwSTE3Rt2j
 ausgV6e6Aon08KpPhvjAVcQ8OwuWbdFpKnC+nbknYfPQqsozJkUJh7rkbbLtoanXQBTT
 WVCPyGwnPTaowRtJB6rCtYnXqJeJrqr4unsjwflpwwMrjJVdhGGHq49lbj1zPOkMik47
 Moa+H9kOU/TufWS7b3HZNjozd7Su400GeUABOnoMk9c6GsAIVR0dGTE+HlE9FnFsrOmx
 6dIQiXT8UWLkmrII9TmjjJjciYxeH19tMyO+SCvffbP9ssvUZzupzD1lWHh1XiDyvOd9 bg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36sttvcsw5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:34:13 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11IHYCVa041784
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 12:34:12 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36sttvcsmn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 12:34:09 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11IHNqPQ013892;
        Thu, 18 Feb 2021 17:33:47 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 36rw3u9g41-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Feb 2021 17:33:47 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11IHXiO846006758
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Feb 2021 17:33:45 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BFE88A4060;
        Thu, 18 Feb 2021 17:33:44 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5F583A4054;
        Thu, 18 Feb 2021 17:33:44 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.94.58])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Feb 2021 17:33:44 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com, pasic@linux.ibm.com
Subject: [PATCH 0/1] css: SCHIB measurement block origin must be aligned
Date: Thu, 18 Feb 2021 18:33:42 +0100
Message-Id: <1613669623-7328-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-18_09:2021-02-18,2021-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 malwarescore=0
 priorityscore=1501 bulkscore=0 adultscore=0 clxscore=1015 spamscore=0
 phishscore=0 suspectscore=0 lowpriorityscore=0 impostorscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102180146
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

By testing Measurement with KVM unit tests I fall on this:
we forgot to test the alignment of the MBO for measurement format 1.

The MB must be aligned on 128bits otherwise an operand exception
is recognized.

Regards,
Pierre

Pierre Morel (1):
  css: SCHIB measurement block origin must be aligned

 target/s390x/ioinst.c | 6 ++++++
 1 file changed, 6 insertions(+)
```
#### [RFC 0/2] cgroup: New misc cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Thu Feb 18 19:55:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12094223
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B64F5C433E9
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 19:59:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5AD5260238
	for <kvm@archiver.kernel.org>; Thu, 18 Feb 2021 19:59:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230033AbhBRT7N (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Feb 2021 14:59:13 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59834 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230368AbhBRT4k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Feb 2021 14:56:40 -0500
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EF30FC0613D6
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 11:56:00 -0800 (PST)
Received: by mail-pl1-x649.google.com with SMTP id o8so1734725pls.7
        for <kvm@vger.kernel.org>; Thu, 18 Feb 2021 11:56:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=7bVBB7/eb43F7sJCb2A73jGKQH5d6crP4qDBABCXugI=;
        b=MSGiXWGc/XBlhRD4FT6+UEMZ+VJARxb3RibM8Xi7pgr9pz0bgTNlOAetGX3p8x57hC
         D9NGC/+GSPxXLIuX4N+ZhEma+EfYEksySW3hvgaO5RI92DO3YOkf+l3+Hz/4dRKkCJdf
         4cMVb+Q2gHQlbE6XqbqTxkfw4bfAhObx0/dyqaDQRbt5/srIvx75jQGbX1PbYcJkSlg8
         hI0qu06XNCzJQ1hwwZl3Vi7StUkGbOxBPOtK7067VGnDl7Ahv9l8EKanVlB9gfUPJ6gp
         ChDRajvVL/VyOf74x+UM1yxcIda7D3fmjy8aa7r0MT38Aa/sNHX4SLupLZYl1t5ZYLIJ
         5EvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=7bVBB7/eb43F7sJCb2A73jGKQH5d6crP4qDBABCXugI=;
        b=YuZcqUDHVi5XQvLfeqtzt/0QR8dq2KztWPctabIT62OldUyr7soSwQdq7RE91Gn2qr
         aQ0nQfsx+D+3cZffXr3X16GfEXFU4cILXaJEzyQ5dcatW1v0Y3EaT0TnvrjZ9O2jNQxT
         MqTpwn9J87V9Zr0AZEqdxpDoHsp6BFx8y7T3ifaQj+Mv3VQDFBvsReOXayJM8Ixi3rM2
         0sYI7k+5v22LQ7V0JB0W9bnafLMWP+bsZU4rqgbKYTkfqFpszuTpoXue/YK3S9/9r0fs
         GzWGLRBJ2aC/0nZzOsn5boNlKDoB7yljg666LFY0O3Fkq/M2suc3xl773F+5LvNh+Bj7
         aERA==
X-Gm-Message-State: AOAM531RJ4vaMopepzXyugiJRomZwUwoAjVvZhu8Hox9qE1BunKiiyjy
        McIPPd0s8A5XkKXCBK7ZbaELgShK2STx
X-Google-Smtp-Source: 
 ABdhPJwJ107wMcTLi0gXo6iW/YPA31DgLY3oqSY85ZPspZZPcWLIo/f/8WwkOevVbXHZFcJm+ZFZ40/7R3qQ
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:580f:a4a0:74ce:b3b4])
 (user=vipinsh job=sendgmr) by 2002:a62:6304:0:b029:1c0:d62d:d213 with SMTP id
 x4-20020a6263040000b02901c0d62dd213mr5825540pfb.79.1613678160277; Thu, 18 Feb
 2021 11:56:00 -0800 (PST)
Date: Thu, 18 Feb 2021 11:55:47 -0800
Message-Id: <20210218195549.1696769-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
Subject: [RFC 0/2] cgroup: New misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, thomas.lendacky@amd.com, brijesh.singh@amd.com,
        jon.grimm@amd.com, eric.vantassell@amd.com, pbonzini@redhat.com,
        hannes@cmpxchg.org, frankja@linux.ibm.com, borntraeger@de.ibm.com
Cc: corbet@lwn.net, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        gingell@google.com, rientjes@google.com, dionnaglaze@google.com,
        kvm@vger.kernel.org, x86@kernel.org, cgroups@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch is creating a new misc cgroup controller for allocation and
tracking of resources which are not abstract like other cgroup
controllers.

This controller was initially proposed as encryption_id but after
the feedbacks, it is now changed to misc cgroup.
https://lore.kernel.org/lkml/20210108012846.4134815-2-vipinsh@google.com/

Changes from the encryption_id controller are:
1. There are only 3 files misc.{capacity, max, current} for all
   resources compared to each resource having their own 3 files in
   encryption_id cgroup.
2. If a resource capacity is 0 then it is considered inactive and won't
   show up in control files.
2. This is a lockless implementation similar to page counter APIs
   compared to single lock implementation in encryption_id cgroup.

Please provide any feedback for this RFC or if it is good for
merging then I can send a patch for merging.

Thanks

Vipin Sharma (2):
  cgroup: sev: Add misc cgroup controller
  cgroup: sev: Miscellaneous cgroup documentation.

 Documentation/admin-guide/cgroup-v1/misc.rst |   1 +
 Documentation/admin-guide/cgroup-v2.rst      |  64 ++-
 arch/x86/kvm/svm/sev.c                       |  60 ++-
 arch/x86/kvm/svm/svm.h                       |   1 +
 include/linux/cgroup_subsys.h                |   4 +
 include/linux/misc_cgroup.h                  |  75 +++
 init/Kconfig                                 |  14 +
 kernel/cgroup/Makefile                       |   1 +
 kernel/cgroup/misc.c                         | 456 +++++++++++++++++++
 9 files changed, 664 insertions(+), 12 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/misc.rst
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c
```
