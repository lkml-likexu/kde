

#### [RFC PATCH v7 00/22] virtio/vsock: introduce SOCK_SEQPACKET support
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
From patchwork Tue Mar 23 13:07:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12157747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2930C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:09:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6256B619B1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:09:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231328AbhCWNId (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 09:08:33 -0400
Received: from mx12.kaspersky-labs.com ([91.103.66.155]:27819 "EHLO
        mx12.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229675AbhCWNIE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 09:08:04 -0400
Received: from relay12.kaspersky-labs.com (unknown [127.0.0.10])
        by relay12.kaspersky-labs.com (Postfix) with ESMTP id 4FCA476822;
        Tue, 23 Mar 2021 16:07:52 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1616504872;
        bh=aZTGT42nNFVqXHiY0R+Kc311g1b5auR1pdmeShBhcvE=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=nXL3A/3IWN7Enxw6o30/DFDXAeCGnr3H2EYXH8FHmljGCTDo3fgCBnXcLdHjxF2v9
         g6bTuaq0M7lf42Y8ztTzqbDh9T+6ICDF/zawjl06l8C3AucHHVI2G/MmUMR8k9mqCV
         Vw5r1SKkQD6nSxQHMXLunI0YmImz7viwYUMqKdcnkDfIxe0YcNP4xbArrlex1qhGAj
         W+6Ii166bRXFg8dvthvtuGnHxwRJxfxTJGuoJmjvrrl3+/ipQ0ocXgKZg1UGq3LJWu
         d8z4QtQzqlRUBMDxDvIG/QFaQDeyOA7XKz75Y+auV6nLli5KqTTFGfdJEILVEXRtkK
         NHi4V6w1z54xw==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub12.kaspersky-labs.com (Postfix) with ESMTPS id 46298760AC;
        Tue, 23 Mar 2021 16:07:51 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.64.121) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2176.2; Tue, 23
 Mar 2021 16:07:50 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Jorgen Hansen <jhansen@vmware.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Norbert Slusarek <nslusarek@gmx.net>,
        Colin Ian King <colin.king@canonical.com>,
        Jeff Vander Stoep <jeffv@google.com>,
        Alexander Popov <alex.popov@linux.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <arseny.krasnov@kaspersky.com>,
        <oxffffaa@gmail.com>
Subject: [RFC PATCH v7 00/22] virtio/vsock: introduce SOCK_SEQPACKET support
Date: Tue, 23 Mar 2021 16:07:13 +0300
Message-ID: <20210323130716.2459195-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-Originating-IP: [10.64.64.121]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.20, Database issued on: 03/23/2021 12:55:25
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 162595 [Mar 23 2021]
X-KSE-AntiSpam-Info: LuaCore: 437 437 85ecb8eec06a7bf2f475f889e784f42bce7b4445
X-KSE-AntiSpam-Info: Version: 5.9.20.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;arseniy-pc.avp.ru:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 03/23/2021 12:58:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 23.03.2021 11:46:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/03/23 11:43:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/03/23 11:40:00 #16480199
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset implements support of SOCK_SEQPACKET for virtio
transport.
	As SOCK_SEQPACKET guarantees to save record boundaries, so to
do it, two new packet operations were added: first for start of record
 and second to mark end of record(SEQ_BEGIN and SEQ_END later). Also,
both operations carries metadata - to maintain boundaries and payload
integrity. Metadata is introduced by adding special header with two
fields - message id and message length:

	struct virtio_vsock_seq_hdr {
		__le32  msg_id;
		__le32  msg_len;
	} __attribute__((packed));

	This header is transmitted as payload of SEQ_BEGIN and SEQ_END
packets(buffer of second virtio descriptor in chain) in the same way as
data transmitted in RW packets. Payload was chosen as buffer for this
header to avoid touching first virtio buffer which carries header of
packet, because someone could check that size of this buffer is equal
to size of packet header. To send record, packet with start marker is
sent first(it's header carries length of record and id),then all data
is sent as usual 'RW' packets and finally SEQ_END is sent(it carries
id of message, which is equal to id of SEQ_BEGIN), also after sending
SEQ_END id is incremented. On receiver's side,size of record is known
from packet with start record marker. To check that no packets were
dropped by transport, 'msg_id's of two sequential SEQ_BEGIN and SEQ_END
are checked to be equal and length of data between two markers is
compared to then length in SEQ_BEGIN header.
	Now as  packets of one socket are not reordered neither on
vsock nor on vhost transport layers, such markers allows to restore
original record on receiver's side. If user's buffer is smaller that
record length, when all out of size data is dropped.
	Maximum length of datagram is not limited as in stream socket,
because same credit logic is used. Difference with stream socket is
that user is not woken up until whole record is received or error
occurred. Implementation also supports 'MSG_EOR' and 'MSG_TRUNC' flags.
	Tests also implemented.

	Thanks to stsp2@yandex.ru for encouragements and initial design
recommendations.

 Arseny Krasnov (22):
  af_vsock: update functions for connectible socket
  af_vsock: separate wait data loop
  af_vsock: separate receive data loop
  af_vsock: implement SEQPACKET receive loop
  af_vsock: separate wait space loop
  af_vsock: implement send logic for SEQPACKET
  af_vsock: rest of SEQPACKET support
  af_vsock: update comments for stream sockets
  virtio/vsock: set packet's type in virtio_transport_send_pkt_info()
  virtio/vsock: simplify credit update function API
  virtio/vsock: dequeue callback for SOCK_SEQPACKET
  virtio/vsock: fetch length for SEQPACKET record
  virtio/vsock: add SEQPACKET receive logic
  virtio/vsock: rest of SOCK_SEQPACKET support
  virtio/vsock: SEQPACKET support feature bit
  virtio/vsock: setup SEQPACKET ops for transport
  vhost/vsock: setup SEQPACKET ops for transport
  vsock/loopback: setup SEQPACKET ops for transport
  vhost/vsock: SEQPACKET feature bit support
  virtio/vsock: SEQPACKET feature bit support
  vsock_test: add SOCK_SEQPACKET tests
  virtio/vsock: update trace event for SEQPACKET

 drivers/vhost/vsock.c                        |  21 +-
 include/linux/virtio_vsock.h                 |  21 +
 include/net/af_vsock.h                       |   9 +
 .../events/vsock_virtio_transport_common.h   |  48 +-
 include/uapi/linux/virtio_vsock.h            |  19 +
 net/vmw_vsock/af_vsock.c                     | 581 +++++++++++------
 net/vmw_vsock/virtio_transport.c             |  17 +
 net/vmw_vsock/virtio_transport_common.c      | 379 +++++++++--
 net/vmw_vsock/vsock_loopback.c               |  12 +
 tools/testing/vsock/util.c                   |  32 +-
 tools/testing/vsock/util.h                   |   3 +
 tools/testing/vsock/vsock_test.c             | 126 ++++
 12 files changed, 1015 insertions(+), 253 deletions(-)

 v6 -> v7:
 General changelog:
 - virtio transport callback for message length now removed
   from transport. Length of record is returned by dequeue
   callback.

 - function which tries to get message length now returns 0
   when rx queue is empty. Also length of current message in
   progress is set to 0, when message processed or error
   happens.

 - patches for virtio feature bit moved after patches with
   transport ops.

 Per patch changelog:
  see every patch after '---' line.

 v5 -> v6:
 General changelog:
 - virtio transport specific callbacks which send SEQ_BEGIN or
   SEQ_END now hidden inside virtio transport. Only enqueue,
   dequeue and record length callbacks are provided by transport.

 - virtio feature bit for SEQPACKET socket support introduced:
   VIRTIO_VSOCK_F_SEQPACKET.

 - 'msg_cnt' field in 'struct virtio_vsock_seq_hdr' renamed to
   'msg_id' and used as id.

 Per patch changelog:
 - 'af_vsock: separate wait data loop':
    1) Commit message updated.
    2) 'prepare_to_wait()' moved inside while loop(thanks to
      Jorgen Hansen).
    Marked 'Reviewed-by' with 1), but as 2) I removed R-b.

 - 'af_vsock: separate receive data loop': commit message
    updated.
    Marked 'Reviewed-by' with that fix.

 - 'af_vsock: implement SEQPACKET receive loop': style fixes.

 - 'af_vsock: rest of SEQPACKET support':
    1) 'module_put()' added when transport callback check failed.
    2) Now only 'seqpacket_allow()' callback called to check
       support of SEQPACKET by transport.

 - 'af_vsock: update comments for stream sockets': commit message
    updated.
    Marked 'Reviewed-by' with that fix.

 - 'virtio/vsock: set packet's type in send':
    1) Commit message updated.
    2) Parameter 'type' from 'virtio_transport_send_credit_update()'
       also removed in this patch instead of in next.

 - 'virtio/vsock: dequeue callback for SOCK_SEQPACKET': SEQPACKET
    related state wrapped to special struct.

 - 'virtio/vsock: update trace event for SEQPACKET': format strings
    now not broken by new lines.

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
#### [RFC PATCH v5 00/10] KVM: selftests: some improvement and a new test
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Tue Mar 23 13:52:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12158015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 99E21C433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:53:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61009619C1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:53:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231603AbhCWNxC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 09:53:02 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:14854 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231362AbhCWNwr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 09:52:47 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4F4Xnd6vvQz92yY;
        Tue, 23 Mar 2021 21:50:45 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Tue, 23 Mar 2021 21:52:34 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kselftest@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Ben Gardon <bgardon@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Peter Xu <peterx@redhat.com>, "Ingo Molnar" <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v5 00/10] KVM: selftests: some improvement and a new test
 for kvm page table
Date: Tue, 23 Mar 2021 21:52:21 +0800
Message-ID: <20210323135231.24948-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v5 series can mainly include two parts.
Based on kvm queue branch: https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=queue

In the first part, all the known hugetlb backing src types specified
with different hugepage sizes are listed, so that we can specify use
of hugetlb source of the exact granularity that we want, instead of
the system default ones. And as all the known hugetlb page sizes are
listed, it's appropriate for all architectures. Besides, a helper that
can get granularity of different backing src types(anonumous/thp/hugetlb)
is added, so that we can use the accurate backing src granularity for
kinds of alignment or guest memory accessing of vcpus.

In the second part, a new test is added:
This test is added to serve as a performance tester and a bug reproducer
for kvm page table code (GPA->HPA mappings), it gives guidance for the
people trying to make some improvement for kvm. And the following explains
what we can exactly do through this test.

The function guest_code() can cover the conditions where a single vcpu or
multiple vcpus access guest pages within the same memory region, in three
VM stages(before dirty logging, during dirty logging, after dirty logging).
Besides, the backing src memory type(ANONYMOUS/THP/HUGETLB) of the tested
memory region can be specified by users, which means normal page mappings
or block mappings can be chosen by users to be created in the test.

If ANONYMOUS memory is specified, kvm will create normal page mappings
for the tested memory region before dirty logging, and update attributes
of the page mappings from RO to RW during dirty logging. If THP/HUGETLB
memory is specified, kvm will create block mappings for the tested memory
region before dirty logging, and split the blcok mappings into normal page
mappings during dirty logging, and coalesce the page mappings back into
block mappings after dirty logging is stopped.

So in summary, as a performance tester, this test can present the
performance of kvm creating/updating normal page mappings, or the
performance of kvm creating/splitting/recovering block mappings,
through execution time.

When we need to coalesce the page mappings back to block mappings after
dirty logging is stopped, we have to firstly invalidate *all* the TLB
entries for the page mappings right before installation of the block entry,
because a TLB conflict abort error could occur if we can't invalidate the
TLB entries fully. We have hit this TLB conflict twice on aarch64 software
implementation and fixed it. As this test can imulate process from dirty
logging enabled to dirty logging stopped of a VM with block mappings,
so it can also reproduce this TLB conflict abort due to inadequate TLB
invalidation when coalescing tables.

Links about the TLB conflict abort:
https://lore.kernel.org/lkml/20201201201034.116760-3-wangyanan55@huawei.com/
---

Change logs:

v4->v5:
- Use synchronization(sem_wait) for time measurement
- Add a new patch about TEST_ASSERT(patch 4)
- Address Andrew Jones's comments for v4 series
- Add Andrew Jones's R-b tags in some patches
- v4: https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

v3->v4:
- Add a helper to get system default hugetlb page size
- Add tags of Reviewed-by of Ben in the patches
- v3: https://lore.kernel.org/lkml/20210301065916.11484-1-wangyanan55@huawei.com/

v2->v3:
- Add tags of Suggested-by, Reviewed-by in the patches
- Add a generic micro to get hugetlb page sizes
- Some changes for suggestions about v2 series
- v2: https://lore.kernel.org/lkml/20210225055940.18748-1-wangyanan55@huawei.com/

v1->v2:
- Add a patch to sync header files
- Add helpers to get granularity of different backing src types
- Some changes for suggestions about v1 series
- v1: https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/

---

Yanan Wang (10):
  tools headers: sync headers of asm-generic/hugetlb_encode.h
  tools headers: Add a macro to get HUGETLB page sizes for mmap
  KVM: selftests: Use flag CLOCK_MONOTONIC_RAW for timing
  KVM: selftests: Print the errno besides error-string in TEST_ASSERT
  KVM: selftests: Make a generic helper to get vm guest mode strings
  KVM: selftests: Add a helper to get system configured THP page size
  KVM: selftests: Add a helper to get system default hugetlb page size
  KVM: selftests: List all hugetlb src types specified with page sizes
  KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
  KVM: selftests: Add a test for kvm page table code

 include/uapi/linux/mman.h                     |   2 +
 tools/include/asm-generic/hugetlb_encode.h    |   3 +
 tools/include/uapi/linux/mman.h               |   2 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        |   8 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  14 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +-
 .../testing/selftests/kvm/include/test_util.h |  21 +-
 .../selftests/kvm/kvm_page_table_test.c       | 512 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/assert.c      |   4 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  59 +-
 tools/testing/selftests/kvm/lib/test_util.c   | 163 +++++-
 tools/testing/selftests/kvm/steal_time.c      |   4 +-
 14 files changed, 739 insertions(+), 61 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
#### [PATCH v3 00/14] Embed struct vfio_device in all sub-structures
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Tue Mar 23 16:14:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12158679
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ACC0EC433C1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:16:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 77CF0619B8
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:16:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233062AbhCWQPc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 12:15:32 -0400
Received: from mail-mw2nam10on2048.outbound.protection.outlook.com
 ([40.107.94.48]:9569
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233118AbhCWQPL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 12:15:11 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=mq9tEAE9lyh4rvIZd4hkjyJ5vpCalmKWket4r+G0S5VCPwEs5mO6TekYUUV/A76svplRaCGnFeHrrGuDidY2USeBrdtE8KdetazoKQpVg3COIG8FeiHZuGOwW220UKreUfQOaRIY3AoqtCOuOUAN/onJ+dJWxfyjr6XQx3UP0s3OpYIlz38xyzYX4u1PYce48d0vNZbJOtWTner+92wGYERJb0n1XbVMU1jnZqLjggkQ95DTO+O7q6ZDkIsFBTij65QF1oPJLwS7RW5LWGjaNJJm5cFl44dFld2NUOMwmT+zWvASGa9wFYm/GmjhTXg2sCyCtP9+GFNZDEJ+Ve8PTw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jPMesbtEJoef/OEF6aKiGz53e7AWyoPvfx/uKZplaHM=;
 b=hadnfrvGaWA44J53qmfyv6W8umw3Id68U9CJINv0LfXmCNqdXt1/EKM/Fs8cG0Q1xVOdAcjiGP/vhNCxmRpYvmiR8MNoXR1K3LT+3GaIpmC0hSrGT8t7xCT5NIdFdvAAXsvvDJH1gSv26MV2+pLWeaMtw1OCt+JGvKO/+SbUerbl4KetkiJiwxM88uwj8qgRQ9XZZ30zfMzaPqVyvAGbnGaL74qeULFZP7ve38QRNEIjdFH6wvzNUNc5Z95mzxvhHL6MlL9CmCgqNxjLkPbUmtvNBJ3VoY48wCbzJ6m61j3CRVdYseXzyFtD2lEk8b4epRGdsv170fGxer4E2o6bHw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jPMesbtEJoef/OEF6aKiGz53e7AWyoPvfx/uKZplaHM=;
 b=Tpp0NW1DuhiHWUOTnNs74CPLc4lKuNHLlqEgb+l/fyUi2Jg6vosYxgetmCXp0zh6kwzo1Mt3hUEmkvWQqWOwIMr1O8sxSVqYxQ2v32m78dL+xvr6tppmNxTq725IGg2HjPqSB3BwMJEY+XSnYBciA7n/HA1CUtj5DUZEVGh4mZMzjrnr7ljJES8HUeVHfO+NEM7cAr4Gb0TJ+TAhwar2WjyrHBFXvK3cMnvdwnXX6UT3mMp2PBXMPzx7bctYBcwT+/E4YRD9M5EEKTvBSFWRUvYxE3v5b0tfFh2SczkKG+aL1q2kNvhXCbOtgzN/oAuq9C2U9sSa2upEA88ZSYvnUA==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR12MB2440.namprd12.prod.outlook.com (2603:10b6:4:b6::39) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3933.32; Tue, 23 Mar
 2021 16:15:08 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3955.027; Tue, 23 Mar 2021
 16:15:08 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Diana Craciun <diana.craciun@oss.nxp.com>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org,
        Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Bharat Bhushan <Bharat.Bhushan@nxp.com>,
        Christian Ehrhardt <christian.ehrhardt@canonical.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Daniel Vetter <daniel@ffwll.ch>,
        Christoph Hellwig <hch@lst.de>,
        Jike Song <jike.song@intel.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>,
        Liu Yi L <yi.l.liu@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Zhi Wang <zhi.a.wang@intel.com>
Subject: [PATCH v3 00/14] Embed struct vfio_device in all sub-structures
Date: Tue, 23 Mar 2021 13:14:52 -0300
Message-Id: <0-v3-225de1400dfc+4e074-vfio1_jgg@nvidia.com>
X-Originating-IP: [206.223.160.26]
X-ClientProxiedBy: MN2PR19CA0019.namprd19.prod.outlook.com
 (2603:10b6:208:178::32) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (206.223.160.26) by
 MN2PR19CA0019.namprd19.prod.outlook.com (2603:10b6:208:178::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Tue, 23 Mar 2021 16:15:07 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lOjgQ-001aCM-9T; Tue, 23 Mar 2021 13:15:06 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 22e52f60-0197-4766-02c5-08d8ee16d36f
X-MS-TrafficTypeDiagnostic: DM5PR12MB2440:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB2440653A003C886004198117C2649@DM5PR12MB2440.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4714;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ulJo4HeASzBmUefh8SVlb3gATJh2nG2Mq3C2jibQ/Vl/etwKzNSGRUn2/CA/AH84ofU/0XH4coLwoyufsRsZOuvNGJljUEjSTb1RGjXAy0cb8EFHcNynrkrYfNg/LIitzbi8sQoX9ShikzFTkAzQgYCZwqB9Mdcb7zjKhsNCJpVTU4GDPKricRnFaStvhezWkt2dZeEpgsYecENGjsrfSvbpm1wm/UUIBgbpAy0zR2UikXrsI6T80U8O5wB2dyngUHl2bLJn2I45PuHY9Pw+u7DdSeb1SbOfEr9oF3/wrdLHowQEZlm7WrxKzYGGeJ2F6zEMfWLdA14T2BiNYvt/JW8iQWEDg0XbZKCy8de6/rUCju3mWg1E1BjBcOL31bIi9g1Hb9pwleAFrm149QhKw8nxlKV/mFdp7jgaIS5lRDMGvsNNeFyoetvFKSvUOSMzLPBc/Wd+y86ZQOI2o9FAD6o5ql/z8XhzgDVa9ZhE11d4e/Kig5U9eibbexFdovCxhU1aiMrs3EQv+MvMTvqy/BH3QRK9SQTU6nFVpMKLQ0+uj7xEktRHoqx/QLZoHUyFmE8/beNf/N6NjtdEcp6/e68hhSotno09h4I2zLET8uR1XT8VY3eKN9/THZae6uZLIwXltVtiOpWXwHW9ESmI18ArTODUcOWM7iWj39JLgXTOM4Vz7TL+YDxV7lXTDViCTc3d1MvmeORQ62Z/kdb71UaDDbozpk7YQl9LTxNoqupkZnJvRRspTLzgxvkdn5gcdQJiyVnuf084zTScWoXVMQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(376002)(39860400002)(136003)(66476007)(66556008)(186003)(36756003)(966005)(6666004)(86362001)(38100700001)(66946007)(4326008)(7416002)(8936002)(54906003)(9746002)(26005)(478600001)(426003)(8676002)(9786002)(83380400001)(110136005)(2906002)(316002)(5660300002)(2616005)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 FxyUsTzlrrUgz5lDeW1O3G+zKAIqqwCOvDTQfQbBAM8sN7XNT7QKSyP6o3G9L3Bke1gxvS3ezryztU9pUNPjyKfVbNND+e3BwzDplRvxeu4p3S1MNPs8jdPPd+GK1PKFdFgtZ/R26zh1HC0gPt5RXL9Ds8IJYVd8NNoByxzv7lBsIVmuxEMh83wD2GwxMWEAxP0E7RAZZISTZPsjG+0S1FR/nVM/ohm5cCjuKayTVOduSjr+yUleDq+qDTCvE2LwbDVDuV0NmmPsjFj6LFTWGlQPT7BUnDtcJX0kZ0Ja5pivadjlxU1AmPS3ZugAF4/47YTOV1GyVZunsnALKcrCFJ3dJH5gaQ6SIS12W9LvlRMC6nKS+X1NTz4xcvot/rGsCjvQQV+NV39WAs0ly8P5USTuH6j5TBcMmAhVrQPstQNpHDnyskqdb51uhQRQ8CYjHbbFeQyy0P8F64xBa/TeMvp/DYaBUjwF/rqkrR8H1JS0NuIhaW8c0DQy5cPn8g3B9KSMarlRfISw9bwzVL2SEaQcF0em1vuirRVRIKzXW79ir8mJWTQm0d265a7pf4WLDHszYpuy+xipnMGspU06XQeAInUBsBO+uHbur4y36yIVdKf2jtIdODTy2YnG8FambgsI2KFF2LLCMgU4Fp62QgcGACGGLREB6Pe+l2/u8N3HLM17ZeR9l/p2OHFY8P5eBeGBftUwFCBqBylQGaZFWadiCx6JEGLpfHqrkhRHKBkyr4/53RhdpK5J4lW7yO0ey5mWkdzpSOkTQLKHbefDgMMDuYuPnoM7zjiDtWUd0Y1xZP1uJOwsWUWn1JTuIPExdU4JNcsBFSwdwcZQ5RJ+rv+g0MMPk3wb0Z9vFwc3uDm36sd3ctpBXsNS3TCRBocm+9BlRpzuZEtfLMkWIc7RMZWwS1rM1gprsFqCGov5w5ohxntCFjzrJkhgxMjtDLu+jOBSypxiba7KAACM29TZ+qRM9jTttp+CN8N8Y8MPqeRBWjYCUi5bf5QPCjjA0QbRTLIqMHWxUuConHQf0n33WrEnwAGRjHq53qMvPfijddwpXXh59AwKHClso+tjVlwE3BM/9xg2D8FhdxRk3XA/oDanJsNNW3CaJO9FkoUakN5i4yg+JxBR/d60xdE/R0uZkdCs89SdZ1hb3qKvEhvpol1i9Y6KKlA7BorVvsZqKyJBwb3q+cevgk86gwhdyDrDQ4Z16dh2g3kBTDzhqgbLTLlM2nei5BkfuDZ3+Cekjuo7B8DdloOwUpdFo1Az4Z50ttUqCJH8cJw1el7uq7CL8J+auE1rqxyqC3aM1G9RGEuJzwEgVnFjCMGQ37ewMCfu
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 22e52f60-0197-4766-02c5-08d8ee16d36f
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 16:15:07.8962
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 MjdfHtupLxQixeGUbeM7T0yeFDUHQdevO0oxOW4uodxyoa1uGwOGirauI4R16VsD
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB2440
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The main focus of this series is to make VFIO follow the normal kernel
convention of structure embedding for structure inheritance instead of
linking using a 'void *opaque'. Here we focus on moving the vfio_device to
be a member of every struct vfio_XX_device that is linked by a
vfio_add_group_dev().

In turn this allows 'struct vfio_device *' to be used everwhere, and the
public API out of vfio.c can be cleaned to remove places using 'struct
device *' and 'void *' as surrogates to refer to the device.

While this has the minor trade off of moving 'struct vfio_device' the
clarity of the design is worth it. I can speak directly to this idea, as
I've invested a fair amount of time carefully working backwards what all
the type-erased APIs are supposed to be and it is certainly not trivial or
intuitive.

When we get into mdev land things become even more inscrutable, and while
I now have a pretty clear picture, it was hard to obtain. I think this
agrees with the kernel style ideal of being explicit in typing and not
sacrificing clarity to create opaque structs.

After this series the general rules are:
 - Any vfio_XX_device * can be obtained at no cost from a vfio_device *
   using container_of(), and the reverse is possible by &XXdev->vdev

   This is similar to how 'struct pci_device' and 'struct device' are
   interrelated.

   This allows 'device_data' to be completely removed from the vfio.c API.

 - The drvdata for a struct device points at the vfio_XX_device that
   belongs to the driver that was probed. drvdata is removed from the core
   code, and only used as part of the implementation of the struct
   device_driver.

 - The lifetime of vfio_XX_device and vfio_device are identical, they are
   the same memory.

   This follows the existing model where vfio_del_group_dev() blocks until
   all vfio_device_put()'s are completed. This in turn means the struct
   device_driver remove() blocks, and thus under the driver_lock() a bound
   driver must have a valid drvdata pointing at both vfio device
   structs. A following series exploits this further.

Most vfio_XX_device structs have data that duplicates the 'struct
device *dev' member of vfio_device, a following series removes that
duplication too.

Thanks everyone for the reviews!

v3:
 - Fix typos in commit messages
 - Fix missed name change of vfio_group_create_device() in a comment
 - Remove wrong kfree(vdev->name) in vfio_platform
 - Keep dprc_scan_container() after vfio_add_group_dev()
 - Remove struct mdev_vfio_device
v2: https://lore.kernel.org/r/0-v2-20d933792272+4ff-vfio1_jgg@nvidia.com
 - Split the get/put changes out of "Simlpify the lifetime logic for
   vfio_device"
 - Add a patch to fix probe ordering in fsl-mc and remove FIXME
 - Add a patch to re-org pci probe
 - Add a patch to fix probe odering in pci and remove FIXME
 - Remove the **pf_dev output from get_pf_vdev()
v1: https://lore.kernel.org/r/0-v1-7355d38b9344+17481-vfio1_jgg@nvidia.com

Jason Gunthorpe (14):
  vfio: Remove extra put/gets around vfio_device->group
  vfio: Simplify the lifetime logic for vfio_device
  vfio: Split creation of a vfio_device into init and register ops
  vfio/platform: Use vfio_init/register/unregister_group_dev
  vfio/fsl-mc: Re-order vfio_fsl_mc_probe()
  vfio/fsl-mc: Use vfio_init/register/unregister_group_dev
  vfio/pci: Move VGA and VF initialization to functions
  vfio/pci: Re-order vfio_pci_probe()
  vfio/pci: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Make to_mdev_device() into a static inline
  vfio: Make vfio_device_ops pass a 'struct vfio_device *' instead of
    'void *'
  vfio/pci: Replace uses of vfio_device_data() with container_of
  vfio: Remove device_data from the vfio bus driver API

 Documentation/driver-api/vfio.rst             |  48 ++--
 drivers/vfio/fsl-mc/vfio_fsl_mc.c             | 127 +++++----
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h     |   1 +
 drivers/vfio/mdev/mdev_private.h              |   5 +-
 drivers/vfio/mdev/vfio_mdev.c                 |  53 ++--
 drivers/vfio/pci/vfio_pci.c                   | 253 ++++++++++--------
 drivers/vfio/pci/vfio_pci_private.h           |   1 +
 drivers/vfio/platform/vfio_amba.c             |   8 +-
 drivers/vfio/platform/vfio_platform.c         |  20 +-
 drivers/vfio/platform/vfio_platform_common.c  |  56 ++--
 drivers/vfio/platform/vfio_platform_private.h |   5 +-
 drivers/vfio/vfio.c                           | 210 +++++----------
 include/linux/vfio.h                          |  37 ++-
 13 files changed, 417 insertions(+), 407 deletions(-)
```
#### [PATCH 00/18] Make vfio_mdev type safe
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Tue Mar 23 17:55:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12158951
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69ADDC433FC
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:56:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47357619C3
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:56:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231441AbhCWR4Y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 13:56:24 -0400
Received: from mail-bn8nam12on2077.outbound.protection.outlook.com
 ([40.107.237.77]:36673
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231339AbhCWRzr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 13:55:47 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Gd9YSYbi24A8ZJ77mfUT+K2WxEEKXA2xOEcCdIppqUHaZhKvXsYFZ1Qj7LMc8wPmuKUtctYrWXePoMMVtk2O6TcIMGc7mfsA/lRyxl9/uFjNwUepWddqCn4QyovHK/E2BvZXlosnRiRmMehJdCbAW25fdrOpu/RB6aOuD+0STHQJ1ZSs+xeR2ByGtn27Szcmefx7JE/KAczFE8ErQZoFjv9tfY8foZR6I80RWT2lCgx5lzyEhemT2I+GEAhW62dzK3poQjMzucR/M+FJBEpFnDCddJd6sorYtcdtmM6YDqW/zwkED+YTRvWnSDS81nyk0Q4XggnrTSRgA7o00V3Igw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2cB46sAu2SciDQDzTmKXSxgAAyCiQmySsGT1aw/yhJo=;
 b=bhC1Gcn9HakhvHSYqPOwKWJK3BZOlsQ9W9L6ICK3HriuP43NCeY/lm6tvo8PXPseZfETKz4SgicoiVmsf2s0Qtmn+a4RRWycSpNE7kf7BVo5q3Zc0dfdh6z4dUbr606wunnEoYW4SecNlgaGsjbiDBo5K/RzogjInC9syilmMCcaGVt4wBODQsYj3/nlvtG0jSM1mdUjAcWgxKlozRAF5lD3QEHJHrQ5Z6U3qSZd6EeW5980aML4yVTQAbWhCKTvOIMsufjzeogTbYiVtFoyOceU2ZApluppnqK8QQmshwn+/jxhO3E8eUck/KnfIvoquFmG1y3exnvDkOUtdCBi7g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=2cB46sAu2SciDQDzTmKXSxgAAyCiQmySsGT1aw/yhJo=;
 b=YRnHheeU+Zm/So/cOl/qJMoHkYB/QGBhNNSmS4DGGNSn1/M6z5RS9YMwzEEW+CHwHJzgD1uEd4XFDiPuF6P00JsWYwxvZ4RNC50gmeWkocr4bFzXPEKZTxbepdDCJm6XRpwPqMZsdtVjOXzzVbD8bMh6VET7WFcbyLLBxju9dXgZjwUU5yPDqNUTI9laKOCwqNBPI3JWnyyn5T3ZLce1ZWmSs/7kPy/yPR/51/EAoEdmgzYOS/uERBkTUyibI4TO3eTMfZeHr608TyPerm4jYALTiXyrhgSRN5GRsfGWolIj4wQDgDgsi9P0JbCP5OZblSk9XlkTSD4OgJlf+Upyrw==
Authentication-Results: linux.ie; dkim=none (message not signed)
 header.d=none;linux.ie; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB4943.namprd12.prod.outlook.com (2603:10b6:5:1bc::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Tue, 23 Mar
 2021 17:55:44 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3955.027; Tue, 23 Mar 2021
 17:55:44 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org,
        Eric Farman <farman@linux.ibm.com>,
        Harald Freudenberger <freude@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Peter Oberparleiter <oberpar@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Zhi Wang <zhi.a.wang@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>,
        Neo Jia <cjia@nvidia.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Jike Song <jike.song@intel.com>,
        Gerd Hoffmann <kraxel@redhat.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH 00/18] Make vfio_mdev type safe
Date: Tue, 23 Mar 2021 14:55:17 -0300
Message-Id: <0-v1-7dedf20b2b75+4f785-vfio2_jgg@nvidia.com>
X-Originating-IP: [206.223.160.26]
X-ClientProxiedBy: BL0PR0102CA0030.prod.exchangelabs.com
 (2603:10b6:207:18::43) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (206.223.160.26) by
 BL0PR0102CA0030.prod.exchangelabs.com (2603:10b6:207:18::43) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Tue, 23 Mar 2021 17:55:41 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lOlFf-001cgN-4b; Tue, 23 Mar 2021 14:55:35 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: c95c21d7-1be6-4a9b-d7dc-08d8ee24dfc5
X-MS-TrafficTypeDiagnostic: DM6PR12MB4943:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB494349D76CDE94E9A4C36164C2649@DM6PR12MB4943.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 95OIdF3tDilJGswE5bYcVx4FnZGlswa+LJA+7F8vKcmP0uc8WrIaZd8mWfw21F8M4cjIT8gmsBzPMuw92tUB8WoHJ1GGF0OToGjc8CvZBzcn8Bk66Y4lhVx9otrlnUVrGi1B1iCENACIB8FS715B/EcIvGwzfhXEUOTsEYYdjnhvkGzzfmT7Tv35Wb1PWlG9R26n/CeQ5KudMiwPsEadaX08+CCtQDO6NseVxQl1SxD4l3saiDlth0Gf4hh3PoNzIo58pr+H7zSp2+CRpbbmXVg18Otx1kQpyokUbXgEb2CR4r404WaGWqIaeMNSNPCiJKgrPtJIAs/7JeLS9ntxi6fhOBWxQ4IQZa2wpUKXV6/wlij7L33UPjft6eoBoWVIYXGhuhNhcd5I4RUSXWtzgLlLm5/k4L7tWF7dXY7ZXh/4OAArDZd+8ufN0jyk7HkJVqjhmMbTk+FLou2Twrxt0KmMR7MWP437wxktr57VYxzmzEzd6uehxgjhVIAAWXLhOaqrQ8d0TO3naCLoNqD9ugqZQk9uMami7FAEx2MaffkLE0PudWq7yJZh0ib7BwSeRMkPCYawVq1eKAi92ImCjfVf9PjetJldoyerOLVM0sjarkeiQeME3wg0saECio7u1DFWYUmsCY0yL5Xa7GjvNvUE5SjNBnGN9PMJ+j0I5Ex03jSaS8vB9CixvK1j8a6q1EMBVnAd++Yw0ugpDO8N35J3AZt+edYNsHw5/Dbu8HEn6UZwgtqMsN+As8L4GXgYasJKjNVL3eKceHrGhiONnw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(136003)(376002)(366004)(346002)(66476007)(186003)(107886003)(6666004)(8936002)(110136005)(36756003)(426003)(86362001)(54906003)(83380400001)(2616005)(38100700001)(921005)(7406005)(7416002)(66946007)(5660300002)(478600001)(9746002)(66556008)(8676002)(4326008)(2906002)(26005)(316002)(966005)(9786002)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Barf92TEnVhxUlFj8VkY0tehCEbocCtWIFasMdTagPC7fvi402RbcB4sYMLrR3+b8DtagKJl29/bMI21ribFTLoN1s2ecg3kDWgt2i0EQT0nuwgBFMx7559S+ghMISTOgsNuXXgQzUDFlGyq4zYHAfbweyOKoxmpTdtKAGCRsq6rmxuZCqcc5wgmfPcfbRpmMc8NylZEuh1szk6a9p3Lu+fOUFuPES11rQMJEMZLdM3AL09qePUeqvrrT5lu8+3jpEWn8A3NLaAyGeEGcORKHbnhkDaqRMDZZH4QbHX38G6aE+FL/djDUzf622shvv5KZqxPaisckmN1p+CSo4o0OHUwPK9UPcWRub/ZYMDc5XiKYFMhy7SER+Spmc2avc+U7yUR644OoyWoi1Pz3xk32GXda9S32QHNwZPzxDLoGvdTTeD9dXQ/fc2tJk2I0+hDg6iEVQTkuxdAiWBX8oBOB6lXJAXyKtFykVUg1ltWCNaqp+3hG2fd8oHTfOegdpAw3PV6WIrB2Tv0jXePlJCEzJETlTqnQE/7r+496M+0LVFVu+LC9v9qEBJUPMNWCAV6+iuBe3okSEaNgx9FcCPt92DXTIMBxT57ORkvGMucFpqFosl3xjT35o/R7uDWyO5cGsxnZkYQSa0DvEMa4NvOxz7jz45/7nCw8dapJpAkLFnnJ1BZsxOKzHfjO5uyXj1+8Z8e41Qmow2Y2bK856ketiGmbUwdIRH767p3jm1+qr/CCiRYrBnjMXzOlWbWLzscxNDHfIwb8dAOMKlSp7j+Ao0K/UtAqVsUL1PuodYN4GHGh9xKBAu2J2pTdAWBOM9E+yaUBDkbSDkpRWdFUJ5Coy8ho53AZClIYuLHm7XrD0hx3ria3QM01KYxyPsTETAXrF6cWMg2HLRIPqn2sd0SK1hFECgZ6RAk/yZJNQp55AQUUzIaeP1zDZmOWyyMY2cGZoTw499iCpuhfhCLSHhmeAl8FWxOnWK/hB+2Zu1ba41oRfZfOnQC637YWVyU9Jp1ZityVXX7lRVXuCKvfHXlA18/woeAQmdd0oUCQQMh301NAkAkRuIdDi9wJHakswqDKXzjQrytUygItZqg7SuKqwCILIf6AVVt2C50hni80+F26tb8TigW+3SDjPn3ZjV8xosvoJXfCi4sW0A21UvQIYpE1wpXgVjDDrq+mR9VvX2tIlrP2Xkq4yy1qVMTIsMa5fcVH6BvCp3ecbEB+bKFfRi02Ca46AF7QksuaqHiGpt4iCUsaML8wifuXuA/CcJ93ORYhVk7NlU0TpqQ5448iaIwISZGe/Ois+OwxXd8m6au5WkdUragXfrGPZjR+0Yi
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c95c21d7-1be6-4a9b-d7dc-08d8ee24dfc5
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 17:55:41.5272
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 BipZJ1FNj4iKcf3aXT3x7UX9hZKdcNuxcW3+zKsbXYAtWbwyZReWnwwQhaFdLl/M
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4943
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prologue
========

This is series #2 in part of a larger work that arose from the minor
remark that the mdev_parent_ops indirection shim is useless and
complicates things.

It follows the "Embed struct vfio_device in all sub-structures" already
sent, and must be applied on top of it.

A preview of the future series's is here:
  https://github.com/jgunthorpe/linux/pull/3/commits

========
This series:

vfio_mdev has a number of different objects: mdev_parent, mdev_type and
mdev_device.

Unfortunately the types of these have been erased in various places
throughout the API, and this makes it very hard to understand this code or
maintain it by the time it reaches all of the drivers.

This series puts in all the types and aligns some of the design with the
driver core standard for a driver core bus driver:

 - Replace 'struct device *' with 'struct mdev_device *
 - Replace 'struct device *' with 'struct mdev_type *' and
   mtype_get_parent_dev()
 - Replace 'struct kobject *' with 'struct mdev_type *'

Now that types are clear it is easy to spot a few places that have
duplicated information.

More significantly we can now understand how to directly fix the
obfuscated 'kobj->name' matching by realizing the the kobj is a mdev_type,
which is linked to the supported_types_list provided by the driver, and
thus the core code can directly return the array indexes all the drivers
actually want.

Jason

Jason Gunthorpe (18):
  vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
  vfio/mdev: Add missing typesafety around mdev_device
  vfio/mdev: Simplify driver registration
  vfio/mdev: Use struct mdev_type in struct mdev_device
  vfio/mdev: Do not allow a mdev_type to have a NULL parent pointer
  vfio/mdev: Expose mdev_get/put_parent to mdev_private.h
  vfio/mdev: Add missing reference counting to mdev_type
  vfio/mdev: Reorganize mdev_device_create()
  vfio/mdev: Add missing error handling to dev_set_name()
  vfio/mdev: Remove duplicate storage of parent in mdev_device
  vfio/mdev: Add mdev/mtype_get_type_group_id()
  vfio/mtty: Use mdev_get_type_group_id()
  vfio/mdpy: Use mdev_get_type_group_id()
  vfio/mbochs: Use mdev_get_type_group_id()
  vfio/gvt: Make DRM_I915_GVT depend on VFIO_MDEV
  vfio/gvt: Use mdev_get_type_group_id()
  vfio/mdev: Remove kobj from mdev_parent_ops->create()
  vfio/mdev: Correct the function signatures for the
    mdev_type_attributes

 .../driver-api/vfio-mediated-device.rst       |   9 +-
 drivers/gpu/drm/i915/Kconfig                  |   1 +
 drivers/gpu/drm/i915/gvt/gvt.c                |  41 ++---
 drivers/gpu/drm/i915/gvt/gvt.h                |   4 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |   7 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  14 +-
 drivers/vfio/mdev/mdev_core.c                 | 160 ++++++------------
 drivers/vfio/mdev/mdev_driver.c               |  19 +--
 drivers/vfio/mdev/mdev_private.h              |  40 ++---
 drivers/vfio/mdev/mdev_sysfs.c                |  59 ++++---
 drivers/vfio/mdev/vfio_mdev.c                 |  29 ++--
 drivers/vfio/vfio_iommu_type1.c               |  25 +--
 include/linux/mdev.h                          |  80 ++++++---
 samples/vfio-mdev/mbochs.c                    |  55 +++---
 samples/vfio-mdev/mdpy.c                      |  56 +++---
 samples/vfio-mdev/mtty.c                      |  66 ++------
 17 files changed, 306 insertions(+), 376 deletions(-)
```
#### [PATCH 0/4 v5] nSVM: Test host RFLAGS.TF on VMRUN 
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Mar 23 17:50:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12159039
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B66B6C433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 18:39:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BA02619C9
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 18:39:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232010AbhCWSjH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 14:39:07 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:44762 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231751AbhCWSiq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 14:38:46 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12NIO312166594;
        Tue, 23 Mar 2021 18:38:43 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=i0rZyBtFwvRWoPFtdiQoUiYVgIC4WBy0rlBONSY8vK0=;
 b=S8WF1HOhLKjdw1D/G07x1kkOmdw8CYONqsUpBnQJA4dCvFR+WmTRWhFfD6EdQ/JPfPM/
 W/eNO9fCM6wOgsKBlbmIUN0EonHpsaODckB0jSl2HbEE7qO/glfTBGO5b+sJN3uYGFQh
 wRuUhvXU3hMdYCskLW6njq9/IOZ18hIahYNzp+H6AbAq/NvliS9aEq7DinO8gi/riYIo
 2uVuyvNA9qCo4W86FBn//DnywkZHoJXyRkFd4AAkTg0NS5YMJTgR1DNQMGBsFQ8RojCX
 NdeomLBXzi5VqDhCVu54D42uae+MdeDDjCMgZ257WXFnmzldcOnfe25MUVkMu+CWXp3Z gA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 37d9pn062v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Mar 2021 18:38:43 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12NIQPSt075647;
        Tue, 23 Mar 2021 18:38:42 GMT
Received: from nam11-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam11lp2168.outbound.protection.outlook.com [104.47.57.168])
        by aserp3020.oracle.com with ESMTP id 37dtxym90q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Mar 2021 18:38:42 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=GN7iwbxMZcDunRyUnOlyh34aHSSUbH4QxBxJY+F0pIgCShhqz0JBEA4MKcoIEDnJhDR3qGg27lW8m2zscrhwqtq3komn+gCvcOAn2tme3LpHnMPMrBf49w3oGpkTj0AB8VVma2mXlqyKxwPCA/GSiAWq+R7IivVq0Ekt9PevLTDYqemPoMN09lX28FbC5UGxF/wMzEfHOjqWoxMYfEQ4dsrUu74ZQpbI1/RZPQz5BdunoVHKgSjeIVR49yjBn8IN5KYPi1XCTyTAXsnEG0abFMgccdANT5xPlb2c3BCHfWniak4PQCllO088oWD7NIJG5i48OGgN1EFQIAkdPghJgw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=i0rZyBtFwvRWoPFtdiQoUiYVgIC4WBy0rlBONSY8vK0=;
 b=CA+4EcyV1ezQJXlqhIWzRwNWDpnj4luuSCxWSiCeJNW7j/IZmFJRgLfS7TYJ7w3FKaUafnO0//5DrCfA9sJiBNFqWm/pW7Vsi6ZKfDXP4Sn3n4QjOpJGVkdeKR/tkqPdLOEfxnVcq0rmyUYywKoCrWqCywemy4Sn2FgxBP7miit9Uhvxg97uHZxHNhxZpUszXNTtWoJqIiPtRmBZOOyVyIM2IVjUVRcZ7VLIEf0fr2mvirhQzzr3tnBc1wwD31aYVRuaaSYQ/feVIlIj205OMCBd1KU4h1ajrCBkQfyHoiMopGS0D5Ue0j4lWvbwC/eLGG12V9bdlaj1aWZdb4Fy/Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=i0rZyBtFwvRWoPFtdiQoUiYVgIC4WBy0rlBONSY8vK0=;
 b=ZAMjSQlE3GaRJgCoWs8AtORWMUHv4PrSZ5jsanVFjYMLrESkdfuric4+MAYPbumBegRgsXw+2FS5CweciTJA0+u2W7WxcLZl6IjIQuK/9ubaSam0qtsfXmU5ByLvuwXRX9heFiexg4+bD7Uac/zG18+0g0BzpIM9qN1u/P/n76k=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4508.namprd10.prod.outlook.com (2603:10b6:806:11d::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Tue, 23 Mar
 2021 18:38:40 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Tue, 23 Mar 2021
 18:38:40 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/4 v5] nSVM: Test host RFLAGS.TF on VMRUN 
Date: Tue, 23 Mar 2021 13:50:02 -0400
Message-Id: <20210323175006.73249-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BY5PR20CA0008.namprd20.prod.outlook.com
 (2603:10b6:a03:1f4::21) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BY5PR20CA0008.namprd20.prod.outlook.com (2603:10b6:a03:1f4::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24 via Frontend
 Transport; Tue, 23 Mar 2021 18:38:37 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 4c410bd3-649a-4e62-53da-08d8ee2adfd9
X-MS-TrafficTypeDiagnostic: SA2PR10MB4508:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB45085252B637B4E3509AD1BD81649@SA2PR10MB4508.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 DI8qMnFgbEwFbSZH5wRzRKlITWCh473KZy1Q8/K3+H1dnTZkdj1/XnPQIwZphyXzQX5/TIkmitFngGSITbCaDkba2u08/N0vNQv34Povc+7QVpfKCyI4V5DUn/4v4UejMHWDYVkC6Q8JirJbXyJV+Xu0WYTZqMA3Ey3vfQTTGK5pMTxLA7ZeBRFchyLZUxw2glFXz8Z0zR2L1aQYN+p/SZ5LnC8NNLf/7Q/ClmKAY5yUPa9B2QUeY9Da7A/jZOKvttS82m1zk6Bhv/m71GvNb4Mjj7XP64aJWwgeIiyhHk51//gEjEowlYEcS0qgzBNr8KKzub9WdJaq/eoNbF2eJPFuQ8KTa59vLuPDfmQlqS0smpLURt4g0ptvtqOo53b9pnxJFP3kljjOjcpzFmFYYMfDkvi8OvP37UOmRtKF4YBfQ+T2MDAVtBQJsft4paxUh2VIoSSUY8qq7I5VEr3VQJDKQODLVwAc33BL3puHwy6NWz5n5WEURQf9+0i5oyFSAduSzIUV39/DcdY0ycMZTZARmZ3GoxjxgFePaasSRg9iF5T7K2bUM7Xv6D74HR7qUenjtpZGPuC1qhppOqhPwbKMD4gG5h5yefcw6MkOrslRBGMCEcL79lM+wnsOVHHkID3NHC2X52hSvRhpo4e94A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(39860400002)(376002)(346002)(136003)(366004)(44832011)(1076003)(16526019)(2906002)(316002)(2616005)(6486002)(5660300002)(83380400001)(38100700001)(66556008)(478600001)(66476007)(8936002)(66946007)(36756003)(6916009)(7696005)(4743002)(86362001)(6666004)(8676002)(4326008)(52116002)(26005)(186003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 NaO8Y7Ljkre4tsbywWGrhSOjCSAStQ0yggONerKcEO86ZNZQp2gavQJFayRQ9FaTcWOntsRXkq4JxlsD4DHbirKc8jyOodIE6Kve6H99tCIrsS4la2AH2gEqnMXq+GB1NK2Hm5glrup0gPRw2GpbvUlI/ZHVVq1B6s3dlqE8gc9DOv9QVqZDd7WsIalIVLsaPia0i9WPD34uiKWVEq4wfAbKYkyMoMKYlBkd1fKd5AKSxfd9OW1N6S+uwbKBPQok2GUgnL1HioNdesqxfBwO8+Z3L+A62NHAXAbjA56vnaJwMfr2MUsrR7LBryEB4xL5RmBdwICdbl7x8OF0f/RsJ3wupIbQxKmzy4UFckFefpFGNSLVJpA0xEwLxcV/NRHEOvpthyEdVk5GjMfH0rKTvDqYa+DcXHM8is7/zTqXNnlcPXAyuBYOlOpvpdi2fpqF77vnaeYRoo7T4VB2JxXnlDRTEHKGlU/MTI/VMuOMnKK7IjOgtlkgrgfC2newOQA/SFhzu96uGU0AKzYXgwpCnfQ0DYrpGrJKCCZteboj64beM4YBSUmlz6OA27B2jj0UMYcZjQ8f+dCiINzJAcPjef167jiOn8QaT1ci5BjzFtTzEmE8YHoNpB4MdVqxcgZPmCiQB0ue4WrXml3xs01QOo9TlUPkm2uq6BmQuydTqCHrMXWIyY+J4UIQl+LbND31yWo/oxefe+eurmGMzQqWsqonkzJsB55aLTGKQjkjNxKZptfkhnsRBo4bLvJ5h0TQbS17zzw9LgKLkqXNuPpthzE9zdtZE8FqGH08IXY4mrn5OUyz6Yy0vinXzmz7NvdXN3EFhzEYaAXEkDStCBYnZ+Db8ERmxrDiavE1990ILhvjPXK9FmtSYMwgJTxnDo+7WdPTLbE8UBaLlP1U2GIqZe2jP52JM+rYaB09ogXfohrVERw1gqZAYgs+PjHDZ8ntYIEURuwincLqiawAGR9EZDcjWkIKMmIlC/rZcGht0nDoi6EtiXHYUK1CW43TWSGNfLaqB0aKUA5f8EWhUO+3+aHrhQo1eC/xq+z7yAmkzfmCWqQFJ9FXQhV5ELt0jcmjbEZ589ZStou/eC7L2EfxJSEduiBl4KkfiRO/BRpzfwtFNjVPPFrTUQtrBFCT/jZyy1kg/Sn8QOLw0uehnZw+UsclJZ+yNwkfzBoGj4KhaB6HfwRZ0jGe+t2ZEIklg21exFI82lpQZGDwV+0iHxqUFYBg4/VZD68zIjoMFD63JViCruhbHeRmtVlVeGVp03dITDfToPRW5IPwVNxPl7PpbDlYIp/1moMok8+NsjtpajQpy8xdBzY2MEziqQhg5DXF
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4c410bd3-649a-4e62-53da-08d8ee2adfd9
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 18:38:40.6011
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 S0u7nCOC/8XJEIf/TEV8ziShYK6jDCw2v4cj2jLCpeuXFBMFXkpm67uP2L2IlrHdwXxH/TOBb6jWicNF1bFUg9UD1u0K75HAYpiqTUA3TdQ=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4508
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9932
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxlogscore=970
 malwarescore=0 phishscore=0 bulkscore=0 mlxscore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103230135
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9932
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 phishscore=0
 mlxlogscore=999 priorityscore=1501 impostorscore=0 bulkscore=0 spamscore=0
 adultscore=0 clxscore=1015 malwarescore=0 mlxscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103230135
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4 -> v5:
        1. The fix in patch# 1 has been modified. We are queue'ing the
           pending #DB intercept via nested_svm_vmexit() if the VMRUN is
           found to be single-stepped.
        2. In patch# 3, the assembly label for tracking the VMRUN RIP has
           been changed to u64* from void*.

[PATCH 1/4 v5] KVM: nSVM: If VMRUN is single-stepped, queue the #DB
[PATCH 2/4 v5] KVM: X86: Add a utility function to read current RIP
[PATCH 3/4 v5] KVM: nSVM: Add assembly label to VMRUN instruction
[PATCH 4/4 v5] nSVM: Test effect of host RFLAGS.TF on VMRUN

 arch/x86/kvm/svm/nested.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

Krish Sadhukhan (1):
      KVM: nSVM: If VMRUN is single-stepped, queue the #DB intercept in nested_svm_vmexit()

 lib/x86/processor.h |   7 ++++
 x86/svm.c           |  16 ++++++--
 x86/svm_tests.c     | 115 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 134 insertions(+), 4 deletions(-)

Krish Sadhukhan (3):
      KVM: X86: Add a utility function to read current RIP
      KVM: nSVM: Add assembly label to VMRUN instruction
      nSVM: Test effect of host RFLAGS.TF on VMRUN
```
